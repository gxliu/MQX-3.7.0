/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
* All Rights Reserved
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: flash_mcf52xx.c$
* $Version : 3.6.16.0$
* $Date    : Aug-31-2010$
*
* Comments:
*
*   The file contains functions for internal flash read, write, erase 
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "fio.h"

#include "flashx.h"
#include "flash_mcf52xx.h"
   
/* Internal function definitions */
static void mcf52xx_ram_function( volatile uchar_ptr ); 
static void mcf52xx_ram_function_end (void);

uchar_ptr mcf52xx_init_ram_function( void );

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf52xx_internal_flash_install
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install a internal flash device.
*
*END*----------------------------------------------------------------------*/
uint_32 mcf52xx_internal_flash_install(
    /* [IN] A string that identifies the device for fopen */
    char_ptr           identifier,
    uint_32            flashx_size
) 
{ /* Body */
    static FLASHX_BLOCK_INFO_STRUCT _mcf52xx_flashx_block_map[2];
    FLASHX_INIT_STRUCT init_structure;

    /* prepare flash sector/block map based on LCF data */
    _mcf52xx_flashx_block_map[0].NUM_SECTORS = flashx_size / FLASHX_SECT_SIZE;
    _mcf52xx_flashx_block_map[0].START_ADDR = 0;
    _mcf52xx_flashx_block_map[0].SECT_SIZE =  FLASHX_SECT_SIZE;
    _mcf52xx_flashx_block_map[1].NUM_SECTORS = 0;
    _mcf52xx_flashx_block_map[1].START_ADDR = 0;
    _mcf52xx_flashx_block_map[1].SECT_SIZE = 0;

    if(!flashx_size || (FLASHX_END_ADDR - FLASHX_START_ADDR) < flashx_size )
        return FLASHXERR_INVALID_SIZE;  
    
    /* set the timer prescaller for flash opperations */
    _mcf52xx_set_cfmclkd();
    
    /* prepare flashx initialization structure */
    init_structure.ID_PTR = identifier;
    init_structure.SECTOR_ERASE = (boolean (_CODE_PTR_)(IO_FLASHX_STRUCT_PTR, uchar_ptr,
      _mem_size))mcf52xx_erase_sector; 
    init_structure.SECTOR_PROGRAM = (boolean (_CODE_PTR_)(IO_FLASHX_STRUCT_PTR, 
      uchar_ptr, uchar_ptr, _mem_size))mcf52xx_write_sector;
    init_structure.CHIP_ERASE = (boolean(_CODE_PTR_)(IO_FLASHX_STRUCT_PTR))mcf52xx_erase_flash;  
    init_structure.INIT = mcf_52xx_flash_init;
    init_structure.DEINIT = mcf_52xx_flash_deinit;
    init_structure.WRITE_PROTECT = NULL;
    init_structure.MAP_PTR = _mcf52xx_flashx_block_map;
    init_structure.BASE_ADDR = (void *)FLASHX_START_ADDR; // defined in lcf file
    init_structure.WIDTH = 32;
    init_structure.DEVICES = 1;
    init_structure.WRITE_VERIFY = 0;
    init_structure.IOCTL = NULL;
    
    return _io_flashx_install(&init_structure);
    
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf52xx_set_cfmclkd
* Returned Value   : none
* Comments         :
*    Set the CFMCLKD register.
*
*END*----------------------------------------------------------------------*/
void _mcf52xx_set_cfmclkd()
{
    #define PRDIV8_LIMIT_FREQ   12800000L // limit freq. for using PRDIV8_PRSC
    #define FLASH_FREQ          200000L   // 200 kHz program frequency
    #define PRDIV8_PRSC         8         // prescaller 8
    
    VMCF52XX_CFM_STRUCT_PTR  cfm_ptr;
    
    cfm_ptr = _bsp_get_cfm_address();
    
    if(BSP_BUS_CLOCK > PRDIV8_LIMIT_FREQ)
    {
        cfm_ptr->CFMCLKD = MCF52XX_CFM_CFMCLKD_PRDIV8 | MCF52XX_CFM_CFMCLKD_DIV((BSP_BUS_CLOCK+PRDIV8_PRSC*FLASH_FREQ-1) / (PRDIV8_PRSC * FLASH_FREQ) -1);
    }
    else
    {
        cfm_ptr->CFMCLKD = MCF52XX_CFM_CFMCLKD_DIV((BSP_BUS_CLOCK+FLASH_FREQ-1) / FLASH_FREQ -1);
    }       
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf_52xx_flash_init
* Returned Value   : 
* Comments         :
*   Erase a flash memory block  
*
*END*----------------------------------------------------------------------*/
boolean mcf_52xx_flash_init( IO_FLASHX_STRUCT_PTR flash_ptr )
{
    INTERNAL_52XX_STRUCT        dev_spec_struct;
    INTERNAL_52XX_STRUCT_PTR    dev_spec_ptr;
    VMCF52XX_CFM_STRUCT_PTR     cfm_ptr;

    dev_spec_ptr = _mem_alloc(sizeof(dev_spec_struct));
    /* test for correct memory allocation */
    if( dev_spec_ptr == NULL){
        return FALSE;
    }
    flash_ptr->DEVICE_SPECIFIC_DATA = dev_spec_ptr;
        
    /* get the pointer to cfm registers structure */
    cfm_ptr = _bsp_get_cfm_address();
    dev_spec_ptr->cfm_ptr = (vuchar_ptr)cfm_ptr;
    /* save pointer to function in ram */
    dev_spec_ptr->flash_execute_code_ptr = mcf52xx_init_ram_function();
    
    return TRUE;    
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf52xx_flash_deinit
* Returned Value   : 
* Comments         :
*     
*
*END*----------------------------------------------------------------------*/
void mcf_52xx_flash_deinit( IO_FLASHX_STRUCT_PTR flash_ptr )
{
    INTERNAL_52XX_STRUCT_PTR    dev_spec_ptr;
    
    dev_spec_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;
    
    /* de-allocate the ram function buffer */
    if(dev_spec_ptr->flash_execute_code_ptr){
        _mem_free(dev_spec_ptr->flash_execute_code_ptr);
    }
    dev_spec_ptr->flash_execute_code_ptr = NULL;
    /* de-allocate the device specific structure */
    _mem_free(flash_ptr->DEVICE_SPECIFIC_DATA);
    flash_ptr->DEVICE_SPECIFIC_DATA = NULL;
}   

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf51xx_init_ram_function
* Returned Value   : pointer to allocated RAM function
* Comments         :
*   allocate and copy flash RAM function  
*
*END*----------------------------------------------------------------------*/
uchar_ptr mcf52xx_init_ram_function()
{
    uchar_ptr ram_code_ptr;
    
    /* Allocate space on stack to run flash command out of SRAM */
    ram_code_ptr = _mem_alloc((char*)mcf52xx_ram_function_end  - 
        (char*)mcf52xx_ram_function);   
    /* copy code to RAM buffer */
    _mem_copy((void*)mcf52xx_ram_function, ram_code_ptr, 
        (char*)mcf52xx_ram_function_end  - (char*)mcf52xx_ram_function);

    return ram_code_ptr;               
}
    
/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf52xx_erase_sector
* Returned Value   : true if success, or false
* Comments         :
*   Erase a flash memory block  
*
*END*----------------------------------------------------------------------*/
boolean mcf52xx_erase_sector(IO_FLASHX_STRUCT_PTR flash_ptr, uchar_ptr from,
      _mem_size size)
{
    
    VMCF52XX_CFM_STRUCT_PTR  cfm_ptr;
    INTERNAL_52XX_STRUCT_PTR    dev_spec_struct_ptr;
    int (*RunInRAM)( uchar_ptr );
    typedef int (* RAMCODE_PTR)(void);
    uint_32 temp;
        
    dev_spec_struct_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;
    /* get pointer to RunInRAM function */
    RunInRAM = (int(*)( uchar_ptr ))dev_spec_struct_ptr->flash_execute_code_ptr;
    
    /* get the pointer to cfm registers structure */
    cfm_ptr = (VMCF52XX_CFM_STRUCT_PTR)dev_spec_struct_ptr->cfm_ptr;
    
    _int_disable();
    /* prepare flash write operation, clear flags and wait for ready state */
    cfm_ptr->CFMUSTAT = (MCF52XX_CFM_CFMUSTAT_PVIOL | MCF52XX_CFM_CFMUSTAT_ACCERR);
    while (!(cfm_ptr->CFMUSTAT & MCF52XX_CFM_CFMUSTAT_CBEIF)){
        /* wait */
    };

    /* latch address in Flash */    
    (*(volatile vuint_32 *)(FLASH_START_ADDRESS+from)) = (vuint_32)-1;
    
    /* issue erase command */
    cfm_ptr->CFMCMD = MCF52XX_CFM_CFMCMD_PAGE_ERASE;
    
    /* run command and wait for it to finish (must execute from RAM) */ 
    temp = _psp_get_sr();
    _psp_set_sr(temp | 0x0700);
    RunInRAM( (uchar_ptr)&cfm_ptr->CFMUSTAT );
    _psp_set_sr(temp);  
    
    if (cfm_ptr->CFMUSTAT & (MCF52XX_CFM_CFMUSTAT_ACCERR | MCF52XX_CFM_CFMUSTAT_PVIOL)) {
        _int_enable();
        return FALSE;
    }
    
    _int_enable();
    return(TRUE);   

}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf52xx_write_sector
* Returned Value   : true if success, or false
* Comments         :
*   Performs a write into flash memory  
*
*END*----------------------------------------------------------------------*/
boolean mcf52xx_write_sector(IO_FLASHX_STRUCT_PTR flash_ptr, 
      uchar_ptr from_ptr, uchar_ptr to_ptr, _mem_size size) 
{

    #define BYTES_IN_WORD   4
    #define WRITED_BYTES    4
    
    VMCF52XX_CFM_STRUCT_PTR  cfm_ptr;
    INTERNAL_52XX_STRUCT_PTR    dev_spec_struct_ptr;    
    int (*RunInRAM)( uchar_ptr );
        
    uint_32 temp, temp_data = 0xFFFFFFFF;
    uchar_ptr temp_data_ptr;
    uchar byte_data_counter = 0;
        
    /* get the offset in write word */
    uint_32 offset = (uint_32)to_ptr & 0x00000003;;

    temp_data_ptr =  (uchar_ptr)&temp_data;
    
    dev_spec_struct_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;    
    /* select the proper ramcode function */
    RunInRAM = (int(*)( uchar_ptr ))dev_spec_struct_ptr->flash_execute_code_ptr;

    /* get the pointer to cfm registers structure */
    cfm_ptr = (VMCF52XX_CFM_STRUCT_PTR)dev_spec_struct_ptr->cfm_ptr;
    /* Clear any errors */
    _int_disable();
    cfm_ptr->CFMUSTAT = (MCF52XX_CFM_CFMUSTAT_PVIOL | MCF52XX_CFM_CFMUSTAT_ACCERR); 
    
    /* if the start address !=  doesn't correspond with hardware, prepare
       variables for 1st word write */
    if(offset){
        /* Align pointer to writable address */
        to_ptr -= offset;
        /* jump over old data */
        byte_data_counter = offset; 
    }
    /* while are some data to write */
    while(size){
        /* move data to write word */       
        while( byte_data_counter < BYTES_IN_WORD && size ){
            *(uchar_ptr)(temp_data_ptr+byte_data_counter) = *from_ptr++;
            byte_data_counter++;
            size--;
        }
        /* move write data to register */
        (*(volatile vuint_32 *)(FLASH_START_ADDRESS + (uint_32)to_ptr)) = temp_data;
        /* init variables for next loop */
        to_ptr += WRITED_BYTES;
        byte_data_counter = 0;
        temp_data = 0xFFFFFFFF;
        /* write command to CFMCMD */
        cfm_ptr->CFMCMD = MCF52XX_CFM_CFMCMD_WORD_PROGRAM;
        
        /* run command and wait for it to finish (must execute from RAM) */     
        temp = _psp_get_sr();
        _psp_set_sr(temp | 0x0700);
        RunInRAM( (uchar_ptr)&cfm_ptr->CFMUSTAT);                           
        _psp_set_sr(temp);
        
        /* Check for Errors */
        if (cfm_ptr->CFMUSTAT & (MCF52XX_CFM_CFMUSTAT_PVIOL | MCF52XX_CFM_CFMUSTAT_ACCERR)) {
            _int_enable();
            return (FALSE);
        }
    }
    _int_enable();
    return (TRUE);  
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf52xx_erase_flash
* Returned Value   : true if success, or false
* Comments         :
*   Erase a flash memory  
*
*END*----------------------------------------------------------------------*/
boolean mcf52xx_erase_flash(IO_FLASHX_STRUCT_PTR flash_ptr)
{
    int i, j;
    FLASHX_BLOCK_INFO_STRUCT_PTR   block_info_ptr;
    _mqx_uint sectors_num;
    uchar_ptr erase_sector_ptr = flash_ptr->BASE_ADDR;
    
    block_info_ptr = flash_ptr->BLOCK_INFO_PTR;
    sectors_num = block_info_ptr->NUM_SECTORS;
    
    for(j = 0; j< flash_ptr->BLOCK_GROUPS; j++)
    {
        for(i = 0; i < sectors_num; i++)
        {
            if( mcf52xx_erase_sector( flash_ptr, erase_sector_ptr, 0 ) == FALSE)
            {
                return (FALSE);
            }
            erase_sector_ptr += block_info_ptr->SECT_SIZE;  
        }
    }
    return(TRUE);       
}

/********************************************************************/
/*
 *  Code required to run in SRAM to perform flash commands. 
 *  All else can be run in flash.
 *  In p_reg we need address of CFMUSTAT register.
 *
 ********************************************************************/ 
static void mcf52xx_ram_function( volatile uchar_ptr cfmustat_ptr) 
{
      /* start flash write */
      *cfmustat_ptr |= MCF52XX_CFM_CFMUSTAT_CBEIF;   
      /* wait until execution complete */
      while (!( *cfmustat_ptr & MCF52XX_CFM_CFMUSTAT_CCIF)){
      };
}
       
          
static void mcf52xx_ram_function_end (void){} 

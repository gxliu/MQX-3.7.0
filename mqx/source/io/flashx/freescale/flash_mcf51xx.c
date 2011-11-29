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
* $FileName: flash_mcf51xx.c$
* $Version : 3.6.17.0$
* $Date    : Jun-15-2010$
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

#include "flash_mcf51xx.h"
   
/* Internal function definitions */
static void mcf51xx_ram_function( volatile uchar_ptr ); 
static void mcf51xx_ram_function_end (void);

uchar_ptr mcf51xx_init_ram_function( void );

#ifndef PSP_HAS_DUAL_FLASH
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf51xx_internal_flash_install
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install a internal flash device.
*
*END*----------------------------------------------------------------------*/
uint_32 mcf51xx_internal_flash_install(
    /* [IN] A string that identifies the device for fopen */
    char_ptr           identifier,
    uint_32            flashx_size
) 
{ /* Body */
    static FLASHX_BLOCK_INFO_STRUCT _mcf51xx_flashx_block_map[2];
    FLASHX_INIT_STRUCT init_structure;

    /* prepare flash sector/block map based on LCF data */
    _mcf51xx_flashx_block_map[0].NUM_SECTORS = flashx_size / FLASHX_SECT_SIZE;
    _mcf51xx_flashx_block_map[0].START_ADDR = 0;
    _mcf51xx_flashx_block_map[0].SECT_SIZE =  FLASHX_SECT_SIZE;
    _mcf51xx_flashx_block_map[1].NUM_SECTORS = 0;
    _mcf51xx_flashx_block_map[1].START_ADDR = 0;
    _mcf51xx_flashx_block_map[1].SECT_SIZE = 0;

    if(!flashx_size || (FLASHX_END_ADDR - FLASHX_START_ADDR) < flashx_size )
        return FLASHXERR_INVALID_SIZE;  
    
    /* set the timer prescaller for flash opperations */
    _mcf51xx_set_cfmclkd();
    
    /* prepare flashx initialization structure */
    init_structure.ID_PTR = identifier;
    init_structure.SECTOR_ERASE = (boolean (_CODE_PTR_)(IO_FLASHX_STRUCT_PTR, uchar_ptr,
      _mem_size))mcf51xx_erase_sector; 
    init_structure.SECTOR_PROGRAM = (boolean (_CODE_PTR_)(IO_FLASHX_STRUCT_PTR, 
      uchar_ptr, uchar_ptr, _mem_size))mcf51xx_write_sector;
    init_structure.CHIP_ERASE = (boolean(_CODE_PTR_)(IO_FLASHX_STRUCT_PTR))mcf51xx_erase_flash;  
    init_structure.INIT = mcf_51xx_flash_init;
    init_structure.DEINIT = mcf_51xx_flash_deinit;
    init_structure.WRITE_PROTECT = NULL;
    init_structure.MAP_PTR = _mcf51xx_flashx_block_map;
    init_structure.BASE_ADDR = (void *)FLASHX_START_ADDR; // defined in lcf file
    init_structure.WIDTH = 32;
    init_structure.DEVICES = 1;
    init_structure.WRITE_VERIFY = 0;
    init_structure.IOCTL = NULL;
    
    return _io_flashx_install(&init_structure);
    
} /* Endbody */
#endif

#ifdef PSP_HAS_DUAL_FLASH
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf51xx_internal_flash_array1_install
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install a internal flash device to memory array 1.
*
*END*----------------------------------------------------------------------*/
uint_32 mcf51xx_internal_flash_array1_install(
    /* [IN] A string that identifies the device for fopen */
    char_ptr           identifier,
    uint_32            flashx_size
) 
{ /* Body */
    static FLASHX_BLOCK_INFO_STRUCT _mcf51xx_flashx_block_map[2];
    FLASHX_INIT_STRUCT init_structure;

    /* prepare flash sector/block map based on LCF data */
    _mcf51xx_flashx_block_map[0].NUM_SECTORS = flashx_size / FLASHX_SECT_SIZE;
    _mcf51xx_flashx_block_map[0].START_ADDR = 0;
    _mcf51xx_flashx_block_map[0].SECT_SIZE =  FLASHX_SECT_SIZE;
    _mcf51xx_flashx_block_map[1].NUM_SECTORS = 0;
    _mcf51xx_flashx_block_map[1].START_ADDR = 0;
    _mcf51xx_flashx_block_map[1].SECT_SIZE = 0;

    if(!flashx_size || (FLASHX_ARRAY1_END_ADDR - FLASHX_ARRAY1_START_ADDR) < flashx_size )
        return FLASHXERR_INVALID_SIZE;  
    
    /* set the timer prescaller for flash opperations */
    _mcf51xx_set_cfmclkd_mem_array_1();
    
    /* prepare flashx initialization structure */
    init_structure.ID_PTR = identifier;
    init_structure.SECTOR_ERASE = (boolean (_CODE_PTR_)(IO_FLASHX_STRUCT_PTR, uchar_ptr,
      _mem_size))mcf51xx_erase_sector; 
    init_structure.SECTOR_PROGRAM = (boolean (_CODE_PTR_)(IO_FLASHX_STRUCT_PTR, 
      uchar_ptr, uchar_ptr, _mem_size))mcf51xx_write_sector;
    init_structure.CHIP_ERASE = (boolean(_CODE_PTR_)(IO_FLASHX_STRUCT_PTR))mcf51xx_erase_flash;  
    init_structure.INIT = mcf_51xx_flash_array1_init;
    init_structure.DEINIT = mcf_51xx_flash_deinit;
    init_structure.WRITE_PROTECT = NULL;
    init_structure.MAP_PTR = _mcf51xx_flashx_block_map;
    init_structure.BASE_ADDR = (void *)FLASHX_ARRAY1_START_ADDR; // defined in lcf file
    init_structure.WIDTH = 32;
    init_structure.DEVICES = 1;
    init_structure.WRITE_VERIFY = 0;
    init_structure.IOCTL = _io_mcf51xx_ioctl;
    return _io_flashx_install(&init_structure);
    
} /* Endbody */
#endif

#ifdef PSP_HAS_DUAL_FLASH
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf51xx_internal_flash_array2_install
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install a internal flash device to memory array 2. 
*    Flash size is always full-flash array size
*
*END*----------------------------------------------------------------------*/
uint_32 mcf51xx_internal_flash_array2_install(
    /* [IN] A string that identifies the device for fopen */
    char_ptr           identifier,
    uint_32            flashx_size
) 
{ /* Body */
    static FLASHX_BLOCK_INFO_STRUCT _mcf51xx_flashx_block_map[2];
    FLASHX_INIT_STRUCT init_structure;

    /* prepare flash sector/block map based on LCF data */
    _mcf51xx_flashx_block_map[0].NUM_SECTORS = flashx_size / FLASHX_SECT_SIZE;
    _mcf51xx_flashx_block_map[0].START_ADDR = 0;
    _mcf51xx_flashx_block_map[0].SECT_SIZE =  FLASHX_SECT_SIZE;
    _mcf51xx_flashx_block_map[1].NUM_SECTORS = 0;
    _mcf51xx_flashx_block_map[1].START_ADDR = 0;
    _mcf51xx_flashx_block_map[1].SECT_SIZE = 0;

    if(!flashx_size || (FLASHX_ARRAY2_END_ADDR - FLASHX_ARRAY2_START_ADDR) < flashx_size )
        return FLASHXERR_INVALID_SIZE;  
    
    /* set the timer prescaller for flash opperations */
    _mcf51xx_set_cfmclkd_mem_array_2();
    
    /* prepare flashx initialization structure */
    init_structure.ID_PTR = identifier;
    init_structure.SECTOR_ERASE = (boolean (_CODE_PTR_)(IO_FLASHX_STRUCT_PTR, uchar_ptr,
      _mem_size))mcf51xx_erase_sector; 
    init_structure.SECTOR_PROGRAM = (boolean (_CODE_PTR_)(IO_FLASHX_STRUCT_PTR, 
      uchar_ptr, uchar_ptr, _mem_size))mcf51xx_write_sector;
    init_structure.CHIP_ERASE = (boolean(_CODE_PTR_)(IO_FLASHX_STRUCT_PTR))mcf51xx_erase_flash;  
    init_structure.INIT = mcf_51xx_flash_array2_init;
    init_structure.DEINIT = mcf_51xx_flash_deinit;
    init_structure.WRITE_PROTECT = NULL;
    init_structure.MAP_PTR = _mcf51xx_flashx_block_map;
    init_structure.BASE_ADDR = (void *)FLASHX_ARRAY2_START_ADDR; // defined in lcf file
    init_structure.WIDTH = 32;
    init_structure.DEVICES = 1;
    init_structure.WRITE_VERIFY = 0;
    init_structure.IOCTL = _io_mcf51xx_ioctl;
    
    return _io_flashx_install(&init_structure);
    
} /* Endbody */
#endif

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf51xx_set_cfmclkd
* Returned Value   : none
* Comments         :
*    Set the CFMCLKD register. Used for mcf51cn
*
*END*----------------------------------------------------------------------*/
void _mcf51xx_set_cfmclkd()
{
    _mcf51xx_set_cfmclkd_ext( MEMORY_ARRAY_STD );   
}

#ifdef PSP_HAS_DUAL_FLASH
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf51xx_set_cfmclkd_mem_array_1
* Returned Value   : none
* Comments         :
*    Set the CFMCLKD register. Used for mcf51em
*    flash Array 1 works with addresses 0x0
*
*END*----------------------------------------------------------------------*/
void _mcf51xx_set_cfmclkd_mem_array_1()
{
    /* RTC_CFG_DATA[CFG0] = 0 : FSTR1 => 0x00000000 */ 
    if( _mcf51_get_rtc_cfg_state() ){
        _mcf51xx_set_cfmclkd_ext( MEMORY_ARRAY_2 );   
    } else {
        _mcf51xx_set_cfmclkd_ext( MEMORY_ARRAY_1 );
    }
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf51xx_set_cfmclkd_mem_array_2
* Returned Value   : none
* Comments         :
*    Set the CFMCLKD register. Used for mcf51em
*    flash Array 2 works with upper memory bank
*
*END*----------------------------------------------------------------------*/
void _mcf51xx_set_cfmclkd_mem_array_2()
{
    /* IRTC_CFG_DATA[CFG0] = 1 : FSTR2 => 0x00000000 */ 
    if( _mcf51_get_rtc_cfg_state() ){
        _mcf51xx_set_cfmclkd_ext( MEMORY_ARRAY_1 );   
    } else {
        _mcf51xx_set_cfmclkd_ext( MEMORY_ARRAY_2 );
    }  
}
#endif

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf51xx_set_cfmclkd_ext
* Returned Value   : none
* Comments         :
*    Set the CFMCLKD register.
*
*END*----------------------------------------------------------------------*/
void _mcf51xx_set_cfmclkd_ext( uchar mem_array ){
    
    #define PRDIV8_LIMIT_FREQ   12800000L // limit freq. for using PRDIV8_PRSC
    #define FLASH_FREQ          200000L   // 190 kHz program frequency
    #define PRDIV8_PRSC         8         // prescaller 8
    
    VMCF51XX_FTSR_STRUCT_PTR  ftsr_ptr;
    
    ftsr_ptr = _bsp_get_cfm_address( mem_array );
    
    if(BSP_BUS_CLOCK > PRDIV8_LIMIT_FREQ)
    {
        ftsr_ptr->FCDIV = MCF51XX_FTSR_FCDIV_PRDIV8 | MCF51XX_FTSR_FCDIV_FDIV((BSP_BUS_CLOCK+PRDIV8_PRSC*FLASH_FREQ-1) / (PRDIV8_PRSC * FLASH_FREQ) -1);
    }
    else
    {
        ftsr_ptr->FCDIV = MCF51XX_FTSR_FCDIV_FDIV((BSP_BUS_CLOCK+FLASH_FREQ-1) / FLASH_FREQ -1);
    }
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf_51xx_flash_init
* Returned Value   : 
* Comments         :
*   Init flash - store the FSTAT register  
*
*END*----------------------------------------------------------------------*/
boolean mcf_51xx_flash_init( IO_FLASHX_STRUCT_PTR flash_ptr )
{
    VMCF51XX_FTSR_STRUCT_PTR    ftsr_ptr;
    INTERNAL_51XX_STRUCT        dev_spec_struct;
    INTERNAL_51XX_STRUCT_PTR    dev_spec_ptr;
    
    dev_spec_ptr = _mem_alloc(sizeof(dev_spec_struct));
    /* test for correct memory allocation */
    if( dev_spec_ptr == NULL){
        return FALSE;
    }
    /* get the pointer to cfm registers structure */
    ftsr_ptr = _bsp_get_cfm_address( MEMORY_ARRAY_STD );
    dev_spec_ptr->ftsr_ptr = (vuchar_ptr)ftsr_ptr;
    flash_ptr->DEVICE_SPECIFIC_DATA = dev_spec_ptr;
    
    /* save pointer to function in ram - this is the default settings  */
    dev_spec_ptr->flash_execute_code_ptr = mcf51xx_init_ram_function();
    
    return TRUE;
}

#ifdef PSP_HAS_DUAL_FLASH
/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf_51xx_flash_array1_init
* Returned Value   : 
* Comments         :
*   Init flash - store the FSTAT register  
*
*END*----------------------------------------------------------------------*/
boolean mcf_51xx_flash_array1_init( IO_FLASHX_STRUCT_PTR flash_ptr )
{
    VMCF51XX_FTSR_STRUCT_PTR    ftsr_ptr;
    INTERNAL_51XX_STRUCT        dev_spec_struct;
    INTERNAL_51XX_STRUCT_PTR    dev_spec_ptr;

    dev_spec_ptr = _mem_alloc(sizeof(dev_spec_struct));
    /* test for correct memory allocation */
    if( dev_spec_ptr == NULL){
        return FALSE;
    }
    /* get the pointer to cfm registers structure */
    /* RTC_CFG_DATA[CFG0] = 0 : FSTR1 => 0x00000000 - see Flash Array Base Address table */
    ftsr_ptr = ( _mcf51_get_rtc_cfg_state() == 1 ) ? _bsp_get_cfm_address( MEMORY_ARRAY_2 ) : 
        _bsp_get_cfm_address( MEMORY_ARRAY_1 );
    dev_spec_ptr->ftsr_ptr = (vuchar_ptr)ftsr_ptr;
    flash_ptr->DEVICE_SPECIFIC_DATA = dev_spec_ptr;
    
    /* save pointer to function in ram - this is the default settings  */
    dev_spec_ptr->flash_execute_code_ptr = mcf51xx_init_ram_function();         
    
    return TRUE;    
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf_51xx_flash_array2_init
* Returned Value   : 
* Comments         :
*   Init flash - store the FSTAT register  
*
*END*----------------------------------------------------------------------*/
boolean mcf_51xx_flash_array2_init( IO_FLASHX_STRUCT_PTR flash_ptr )
{
    VMCF51XX_FTSR_STRUCT_PTR    ftsr_ptr;
    INTERNAL_51XX_STRUCT        dev_spec_struct;
    INTERNAL_51XX_STRUCT_PTR    dev_spec_ptr;

    dev_spec_ptr = _mem_alloc(sizeof(dev_spec_struct));
    /* test for correct memory allocation */
    if( dev_spec_ptr == NULL){
        return FALSE;
    }
    /* get the pointer to cfm registers structure */
    /* RTC_CFG_DATA[CFG0] = 0 : FSTR1 => 0x00000000 - see Flash Array Base Address table */
    ftsr_ptr = ( _mcf51_get_rtc_cfg_state() == 1 ) ? _bsp_get_cfm_address( MEMORY_ARRAY_1 ) : 
        _bsp_get_cfm_address( MEMORY_ARRAY_2 );
    dev_spec_ptr->ftsr_ptr = (vuchar_ptr)ftsr_ptr;
    flash_ptr->DEVICE_SPECIFIC_DATA = dev_spec_ptr;
    
    /* save pointer to function in ram - this is the default settings  */
    dev_spec_ptr->flash_execute_code_ptr = mcf51xx_init_ram_function();         
    
    return TRUE;    
}
#endif

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf51xx_flash_deinit
* Returned Value   : 
* Comments         :
*    release used memory      
*
*END*----------------------------------------------------------------------*/
void mcf_51xx_flash_deinit( IO_FLASHX_STRUCT_PTR flash_ptr )
{

    INTERNAL_51XX_STRUCT_PTR    dev_spec_ptr;
    
    dev_spec_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;

    /* if the flash write,erase code run form RAM, free memory */
    if ( flash_ptr->FLAGS & FLASHX_WR_ERASE_FROM_FLASH_ENABLED == 0 ){              
        /* de-allocate the ram function buffer */
        if(dev_spec_ptr->flash_execute_code_ptr){
            _mem_free(dev_spec_ptr->flash_execute_code_ptr);
        }
    }
    dev_spec_ptr->flash_execute_code_ptr = NULL;
    /* de-allocate device specific structure */
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
uchar_ptr mcf51xx_init_ram_function()
{
    uchar_ptr ram_code_ptr;
    
    /* Allocate space on stack to run flash command out of SRAM */
    ram_code_ptr = _mem_alloc((char*)mcf51xx_ram_function_end  - 
        (char*)mcf51xx_ram_function);   
    /* copy code to RAM buffer */
    _mem_copy((void*)mcf51xx_ram_function, ram_code_ptr, 
        (char*)mcf51xx_ram_function_end  - (char*)mcf51xx_ram_function);

    return ram_code_ptr;               
}
    
/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf51xx_erase_sector_ext
* Returned Value   : true if success, or false
* Comments         :
*   Erase a flash memory block  
*
*END*----------------------------------------------------------------------*/
boolean mcf51xx_erase_sector(IO_FLASHX_STRUCT_PTR flash_ptr, uchar_ptr from,
      _mem_size size )
{
    
    VMCF51XX_FTSR_STRUCT_PTR    ftsr_ptr;
    INTERNAL_51XX_STRUCT_PTR    dev_spec_struct_ptr;
    int (*RunInRAM)( uchar_ptr );
    uint_32 temp;

    dev_spec_struct_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;    
    /* select the proper ramcode function */
    *RunInRAM = (int(*)( uchar_ptr ))dev_spec_struct_ptr->flash_execute_code_ptr;
    
    /* get the pointer to cfm registers structure */
    ftsr_ptr = (VMCF51XX_FTSR_STRUCT_PTR)dev_spec_struct_ptr->ftsr_ptr;   
    
    _int_disable();
    /* prepare flash write operation, clear flags and wait for ready state */
    ftsr_ptr->FSTAT = (MCF51XX_FTSR_FSTAT_FPVIOL | MCF51XX_FTSR_FSTAT_FACCERR);
    while (!(ftsr_ptr->FSTAT & MCF51XX_FTSR_FSTAT_FCBEF)){
        /* wait */
    };

    /* latch address in Flash */
    (*(volatile vuint_32 *)(from)) = (vuint_32)-1;  
    
    /* issue erase command */
    ftsr_ptr->FCMD = MCF51XX_FTSR_FCMD_SECTOR_ERASE;
    
    /* run command and wait for it to finish (must execute from RAM) */ 
    temp = _psp_get_sr();
    _psp_set_sr(temp | 0x0700);
    RunInRAM( (volatile uchar_ptr)&ftsr_ptr->FSTAT );    
    _psp_set_sr(temp);
    
    if (ftsr_ptr->FSTAT & (MCF51XX_FTSR_FSTAT_FACCERR | MCF51XX_FTSR_FSTAT_FPVIOL)) {
        _int_enable();
        return FALSE;
    }
        
    _int_enable();
    return(TRUE);   
         
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf51xx_write_sector
* Returned Value   : true if success, or false
* Comments         :
*   Performs a write into flash memory  
*
*END*----------------------------------------------------------------------*/
boolean mcf51xx_write_sector(IO_FLASHX_STRUCT_PTR flash_ptr, 
      uchar_ptr from_ptr, uchar_ptr to_ptr, _mem_size size ) 
{

    #define BYTES_IN_WORD   4
    
    VMCF51XX_FTSR_STRUCT_PTR    ftsr_ptr;
    VMCF51XX_PMC_STRUCT_PTR     pmc_ptr; 
    INTERNAL_51XX_STRUCT_PTR    dev_spec_struct_ptr; 
        
    int (*RunInRAM)( uchar_ptr );
    uint_32 temp, temp_data = 0xFFFFFFFF;
    uchar_ptr temp_data_ptr;
    uchar byte_data_counter = 0;
    /* get the offset in write word */
    uint_32 offset = (uint_32)to_ptr & 0x00000003;;

    (uint_32_ptr)temp_data_ptr =  &temp_data;

    dev_spec_struct_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;    
    /* select the proper ramcode function */
    *RunInRAM = (int(*)( uchar_ptr ))dev_spec_struct_ptr->flash_execute_code_ptr;

    /* get the pointer to cfm registers structure */
    ftsr_ptr = (VMCF51XX_FTSR_STRUCT_PTR)dev_spec_struct_ptr->ftsr_ptr;
    
    /* get the pointer to pmc registers structure */
    pmc_ptr = _bsp_get_pmc_address();    
    /* Clear any errors */
    _int_disable();
    ftsr_ptr->FSTAT = (MCF51XX_FTSR_FSTAT_FPVIOL | MCF51XX_FTSR_FSTAT_FACCERR); 
    
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
            *(temp_data_ptr+byte_data_counter) = *from_ptr++;
            byte_data_counter++;
            size--;
        }
        /* test the LVDF flag - if 1, we need to write data in 2 steps */
        if( pmc_ptr->SPMSC1 & MCF51XX_PMC_SPMSC1_LVDF) {
            /* write odd bytes */
            (*(vuint_32 *)(to_ptr)) = temp_data | 0x00FF00FF;
            /* write command to CFMCMD */
            ftsr_ptr->FCMD = MCF51XX_FTSR_FCMD_BURST_PROGRAM;
            /* run command and wait for it to finish (must execute from RAM) */     
            temp = _psp_get_sr();
            _psp_set_sr(temp | 0x0700);
            RunInRAM( (volatile uchar_ptr)&ftsr_ptr->FSTAT );
            _psp_set_sr(temp);
            /* write even bytes */              
            (*(vuint_32 *)(to_ptr)) = temp_data | 0xFF00FF00;
            /* write command to CFMCMD */
            ftsr_ptr->FCMD = MCF51XX_FTSR_FCMD_BURST_PROGRAM;
            /* run command and wait for it to finish (must execute from RAM) */     
            temp = _psp_get_sr();
            _psp_set_sr(temp | 0x0700);
            RunInRAM( (volatile uchar_ptr)&ftsr_ptr->FSTAT );
            _psp_set_sr(temp);
        } 
        else {  
            /* move write data to register */
            (*(vuint_32 *)(to_ptr)) = temp_data;
            
            /* write command to CFMCMD */
            ftsr_ptr->FCMD = MCF51XX_FTSR_FCMD_BURST_PROGRAM;
            /* run command and wait for it to finish (must execute from RAM) */     
            temp = _psp_get_sr();
            _psp_set_sr(temp | 0x0700);
            RunInRAM( (volatile uchar_ptr)&ftsr_ptr->FSTAT );                
            _psp_set_sr(temp);
        }
        /* Check for Errors */
        if (ftsr_ptr->FSTAT & (MCF51XX_FTSR_FSTAT_FPVIOL | MCF51XX_FTSR_FSTAT_FACCERR)) {
            _int_enable();
            return (FALSE);
        }
        
        /* init variables for next loop */
        to_ptr += BYTES_IN_WORD;
        byte_data_counter = 0;
        temp_data = 0xFFFFFFFF;
    }
    _int_enable();
    return (TRUE);  
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf51xx_erase_flash
* Returned Value   : true if success, or false
* Comments         :
*   Erase a flash memory  
*
*END*----------------------------------------------------------------------*/
boolean mcf51xx_erase_flash( IO_FLASHX_STRUCT_PTR flash_ptr )
{
    int i, j;
    FLASHX_BLOCK_INFO_STRUCT_PTR   block_info_ptr;
    _mqx_uint sectors_num;
    _mqx_uint block_groups = flash_ptr->BLOCK_GROUPS;
    uchar_ptr erase_sector_ptr = flash_ptr->BASE_ADDR;
    
    block_info_ptr = flash_ptr->BLOCK_INFO_PTR;
    sectors_num = block_info_ptr->NUM_SECTORS;
    
    for(j = 0; j< flash_ptr->BLOCK_GROUPS; j++)
    {
        for(i = 0; i < sectors_num; i++)
        {
            if( mcf51xx_erase_sector( flash_ptr, erase_sector_ptr, 0 ) == FALSE)
            {
                return (FALSE);
            }
            erase_sector_ptr += block_info_ptr->SECT_SIZE;  
        }
    }
    return(TRUE);       
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_mcf51xx_ioctl
* Returned Value   : TRUE if successful
* Comments         : 
*    flash ioctl function
* 
*END*----------------------------------------------------------------------*/
_mqx_int _io_mcf51xx_ioctl
   (
      /* [IN] the handle returned from _fopen */
      IO_FLASHX_STRUCT_PTR handle_ptr,

      /* [IN] the ioctl command */
      _mqx_uint              cmd,

      /* [IN] the ioctl parameters */
      pointer                param_ptr
   )
{ /* Body */
    
    INTERNAL_51XX_STRUCT_PTR    dev_spec_ptr;
    _mqx_uint   result = MQX_OK;
    
    switch(cmd) {
        case FLASH_IOCTL_SWAP_FLASH_AND_RESET:
            #ifdef PSP_HAS_DUAL_FLASH
            _mcf51_swap_flash_and_reset();
            #endif
            break;
            
        case FLASH_IOCTL_WRITE_ERASE_CMD_FROM_FLASH_ENABLE:
            handle_ptr->FLAGS |= FLASHX_WR_ERASE_FROM_FLASH_ENABLED; 
            dev_spec_ptr = handle_ptr->DEVICE_SPECIFIC_DATA;
            if(dev_spec_ptr->flash_execute_code_ptr){
                _mem_free(dev_spec_ptr->flash_execute_code_ptr);
            }
            dev_spec_ptr->flash_execute_code_ptr = (uchar_ptr)mcf51xx_ram_function;
            break;
            
        case FLASH_IOCTL_WRITE_ERASE_CMD_FROM_FLASH_DISABLE:
            handle_ptr->FLAGS &= ~FLASHX_WR_ERASE_FROM_FLASH_ENABLED;
            dev_spec_ptr = handle_ptr->DEVICE_SPECIFIC_DATA;
            dev_spec_ptr->flash_execute_code_ptr = mcf51xx_init_ram_function();
            break;
            
        default:
            break;
    }
    return result;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf51xx_ram_function
* Returned Value   : 
* Comments         : 
*    Launch the program command and wait until execution complete. This code
*    is required to run in SRAM, 
*    unless FLASH_IOCTL_WRITE_ERASE_CMD_FROM_FLASH_ENABLE ioctl command is
*    applied to allow the low level flash write and erase routines being run
*    from internal flash memory (works only with the dual flash memory 
*    controllers).
*    
*END*----------------------------------------------------------------------*/
static void mcf51xx_ram_function( volatile uchar_ptr fstat_ptr ) 
{
    /* Clear the FCBEF flag in the FSTAT register by writing a 1 */
    /* to FCBEF to launch the program command. */
    *fstat_ptr |= MCF51XX_FTSR_FSTAT_FCBEF;   
    /* wait until execution complete */
    while (!( *fstat_ptr & MCF51XX_FTSR_FSTAT_FCCF)){
    };
}


static void mcf51xx_ram_function_end (void){} 

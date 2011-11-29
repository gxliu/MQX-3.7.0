/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
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
* $FileName: flash_kinetis.c$
* $Version : 3.7.10.2$
* $Date    : Mar-30-2011$
*
* Comments:
*
*   The file contains functions for internal flash read, write, erase 
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "fio.h"
#include "flash_kinetis.h"

static void kinetis_ram_function (volatile uchar_ptr); 
static void kinetis_ram_function_end (void);
uchar_ptr   kinetis_init_ram_function ( uchar_ptr );

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : kinetis_flash_command_sequence
* Returned Value   : uint_32 an error code
* Comments         :
*    Run command in FTFL device.
*
*END*----------------------------------------------------------------------*/
static uint_32 kinetis_flash_command_sequence
(                                                
    /* [IN] Flash specific structure */
    KINETIS_FLASH_INTERNAL_STRUCT_PTR dev_spec_ptr,
   
    /* [IN] Command byte array */
    uint_8_ptr                        command_array,
      
    /* [IN] Number of values in the array */
    uint_8                            count,
    
    boolean read
)
{
    uint_8  fstat;
    uint_32 result;
    void (* RunInRAM)(uchar_ptr);
    FTFL_MemMapPtr ftfl_ptr;
    _mqx_uint cnt = count;
    
    ftfl_ptr = (FTFL_MemMapPtr)dev_spec_ptr->ftfl_ptr;

    /* get pointer to RunInRAM function */
    RunInRAM = (void(*)(uchar_ptr))((uchar_ptr)dev_spec_ptr->flash_execute_code_ptr);
    
    /* set the default return as FTFL_OK */
    result = FTFL_OK;
    
    /* check CCIF bit of the flash status register */
    while (0 == (ftfl_ptr->FSTAT & FTFL_FSTAT_CCIF_MASK))
        { };
    
    /* clear RDCOLERR & ACCERR & FPVIOL error flags in flash status register */
    if (ftfl_ptr->FSTAT & FTFL_FSTAT_RDCOLERR_MASK) 
    {
        ftfl_ptr->FSTAT |= FTFL_FSTAT_RDCOLERR_MASK;
    }
    if (ftfl_ptr->FSTAT & FTFL_FSTAT_ACCERR_MASK) 
    {
        ftfl_ptr->FSTAT |= FTFL_FSTAT_ACCERR_MASK;
    }
    if (ftfl_ptr->FSTAT & FTFL_FSTAT_FPVIOL_MASK) 
    {
        ftfl_ptr->FSTAT |= FTFL_FSTAT_FPVIOL_MASK;
    }
    
    switch (cnt)
    {
        case 12: ftfl_ptr->FCCOBB = command_array[--cnt];
        case 11: ftfl_ptr->FCCOBA = command_array[--cnt];
        case 10: ftfl_ptr->FCCOB9 = command_array[--cnt];
        case 9: ftfl_ptr->FCCOB8 = command_array[--cnt];
        case 8: ftfl_ptr->FCCOB7 = command_array[--cnt];
        case 7: ftfl_ptr->FCCOB6 = command_array[--cnt];
        case 6: ftfl_ptr->FCCOB5 = command_array[--cnt];
        case 5: ftfl_ptr->FCCOB4 = command_array[--cnt];
        case 4: ftfl_ptr->FCCOB3 = command_array[--cnt];
        case 3: ftfl_ptr->FCCOB2 = command_array[--cnt];
        case 2: ftfl_ptr->FCCOB1 = command_array[--cnt];
        case 1: ftfl_ptr->FCCOB0 = command_array[--cnt];
        default: break;
    }
    
    __disable_interrupt ();

    /* run command and wait for it to finish (must execute from RAM) */ 
    RunInRAM ((uchar_ptr)&ftfl_ptr->FSTAT);

    __enable_interrupt ();    
    
    if (read) {
        cnt = count;
        switch (cnt)
        {
            case 12: command_array[--cnt] = ftfl_ptr->FCCOBB;
            case 11: command_array[--cnt] = ftfl_ptr->FCCOBA;
            case 10: command_array[--cnt] = ftfl_ptr->FCCOB9;
            case 9: command_array[--cnt] = ftfl_ptr->FCCOB8;
            case 8: command_array[--cnt] = ftfl_ptr->FCCOB7;
            case 7: command_array[--cnt] = ftfl_ptr->FCCOB6;
            case 6: command_array[--cnt] = ftfl_ptr->FCCOB5;
            case 5: command_array[--cnt] = ftfl_ptr->FCCOB4;
            case 4: command_array[--cnt] = ftfl_ptr->FCCOB3;
            case 3: command_array[--cnt] = ftfl_ptr->FCCOB2;
            case 2: command_array[--cnt] = ftfl_ptr->FCCOB1;
            case 1: command_array[--cnt] = ftfl_ptr->FCCOB0;
            default: break;
        }
    }
    
    /* get flash status register value */
    fstat = ftfl_ptr->FSTAT;

    /* invalidate flash cache to expose flash changes */
    kinetis_flash_invalidate_cache (FLASHX_INVALIDATE_CACHE_ALL);
   
    /* checking access error */
    if (0 != (fstat & FTFL_FSTAT_ACCERR_MASK))
    {
        /* return an error code FTFL_ERR_ACCERR */
        result = FTFL_ERR_ACCERR;
    }
    /* checking protection error */
    else if (0 != (fstat & FTFL_FSTAT_FPVIOL_MASK))
    {
        /* return an error code FTFL_ERR_PVIOL */
        result = FTFL_ERR_PVIOL;
    }
    /* checking MGSTAT0 non-correctable error */
    else if (0 != (fstat & FTFL_FSTAT_MGSTAT0_MASK))
    {
        /* return an error code FTFL_ERR_MGSTAT0 */
        result = FTFL_ERR_MGSTAT0;
    }
    
    return result;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : kinetis_flash_install_internal
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install an internal flash device.
*
*END*----------------------------------------------------------------------*/
uint_32 kinetis_flash_install_internal 
(
    /* [IN] A string that identifies the device for fopen */
    char_ptr           identifier,

    /* [IN] Size of internal flash in bytes */
    uint_32            flashx_size
) 
{
    static FLASHX_BLOCK_INFO_STRUCT _kinetis_flashx_block_map[3];
    FLASHX_INIT_STRUCT init_structure;

    /* prepare flash sector/block map based on LCF data */
    _kinetis_flashx_block_map[0].NUM_SECTORS = flashx_size / FLASHX_SECT_SIZE;
    _kinetis_flashx_block_map[0].START_ADDR = 0;
    _kinetis_flashx_block_map[0].SECT_SIZE =  FLASHX_SECT_SIZE;
    
    _kinetis_flashx_block_map[1].NUM_SECTORS = INTERNAL_FLEXNVM_SIZE / FLASHX_SECT_SIZE;
    _kinetis_flashx_block_map[1].START_ADDR = INTERNAL_FLEXNVM_BASE - (uint_32)FLASHX_START_ADDR;
    _kinetis_flashx_block_map[1].SECT_SIZE = FLASHX_SECT_SIZE;

    _kinetis_flashx_block_map[2].NUM_SECTORS = 0;
    _kinetis_flashx_block_map[2].START_ADDR = 0;
    _kinetis_flashx_block_map[2].SECT_SIZE = 0;

    if(!flashx_size || (FLASHX_END_ADDR - FLASHX_START_ADDR) < flashx_size )
    {
        return FLASHXERR_INVALID_SIZE;  
    }
    
    /* prepare flashx initialization structure */
    init_structure.ID_PTR = identifier;
    init_structure.SECTOR_ERASE = kinetis_flash_erase_sector; 
    init_structure.SECTOR_PROGRAM = kinetis_flash_write_sector;
    init_structure.CHIP_ERASE = kinetis_flash_erase;  
    init_structure.INIT = kinetis_flash_init;
    init_structure.DEINIT = kinetis_flash_deinit;
    init_structure.WRITE_PROTECT = NULL;
    init_structure.MAP_PTR = _kinetis_flashx_block_map;
    init_structure.BASE_ADDR = (pointer)FLASHX_START_ADDR;
    init_structure.WIDTH = 32;
    init_structure.DEVICES = 1;
    init_structure.WRITE_VERIFY = 0;
    init_structure.IOCTL = kinetis_flash_ioctl;
    
    return _io_flashx_install(&init_structure);
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : kinetis_flash_init
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*   Initialize flash specific information.
*
*END*----------------------------------------------------------------------*/
boolean kinetis_flash_init 
(
    /* [IN] Flash info structure */
    IO_FLASHX_STRUCT_PTR flash_ptr
)
{
    KINETIS_FLASH_INTERNAL_STRUCT_PTR dev_spec_ptr;
    FTFL_MemMapPtr                    ftfl_ptr;
    uchar_ptr                         ram_code_ptr;

    /* allocate internal structure */
    dev_spec_ptr = _mem_alloc (sizeof (KINETIS_FLASH_INTERNAL_STRUCT));
    if( dev_spec_ptr == NULL)
    {
        return FALSE;
    }
    flash_ptr->DEVICE_SPECIFIC_DATA = dev_spec_ptr;
        
    /* get the pointer to ftfl registers structure */
    ftfl_ptr = _bsp_get_ftfl_address ();
    dev_spec_ptr->ftfl_ptr = (vuchar_ptr)ftfl_ptr;
    
    /* save pointer to function in ram */
    ram_code_ptr = _mem_alloc ((char_ptr)kinetis_ram_function_end  - (char_ptr)kinetis_ram_function + 3);
    dev_spec_ptr->ramfcn_memaloc_ptr = ram_code_ptr;
    dev_spec_ptr->flash_execute_code_ptr = kinetis_init_ram_function ( ram_code_ptr );
        
    return TRUE;    
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : kinetis_flash_deinit
* Returned Value   : none
* Comments         :
*   Release flash specific information.  
*
*END*----------------------------------------------------------------------*/
void kinetis_flash_deinit 
( 
    /* [IN] Flash info structure */
    IO_FLASHX_STRUCT_PTR flash_ptr 
)
{
    KINETIS_FLASH_INTERNAL_STRUCT_PTR    dev_spec_ptr;
    
    dev_spec_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;
    
    /* de-allocate the ram function buffer */
    if(dev_spec_ptr->flash_execute_code_ptr)
    {
        _mem_free(dev_spec_ptr->ramfcn_memaloc_ptr);
    }
    dev_spec_ptr->flash_execute_code_ptr = NULL;

    /* de-allocate the device specific structure */
    _mem_free(flash_ptr->DEVICE_SPECIFIC_DATA);
    flash_ptr->DEVICE_SPECIFIC_DATA = NULL;
}   

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : kinetis_init_ram_function
* Returned Value   : pointer to allocated RAM function
* Comments         :
*   Allocate and copy flash RAM function.
*
*END*----------------------------------------------------------------------*/
uchar_ptr kinetis_init_ram_function
(
    uchar_ptr ram_code_ptr
)
{    
    uint_32 fcn_thumb_flag;
    uint_32 fcn_rom_addr;
    uint_32 fcn_ram_addr;
  
    /* 
    * Copy kinetis_ram_function() function to stack @ function_copy address 
    * Because Thumb-2 instruction mode is used its necessary to set 
    * bit[0] correctly to represent the opcode type of the branch target.
    * For details see:
    * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka12545.html
    */
    fcn_thumb_flag = (uint_32)kinetis_ram_function & 0x01;
    fcn_rom_addr = (uint_32)kinetis_ram_function & ~(uint_32)0x01;
    fcn_ram_addr = (uint_32)ram_code_ptr | (fcn_rom_addr & 0x02);
    
    _mem_copy ((pointer)fcn_rom_addr, (pointer)fcn_ram_addr, (char_ptr)kinetis_ram_function_end  - (char_ptr)kinetis_ram_function );
                 
    return (uchar_ptr)(fcn_ram_addr | fcn_thumb_flag);
}
    
/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : kinetis_flash_erase_sector
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*   Erase a flash memory block.
*
*END*----------------------------------------------------------------------*/
boolean kinetis_flash_erase_sector
(
    /* [IN] Flash info structure */
    IO_FLASHX_STRUCT_PTR flash_ptr, 

    /* [IN] Erased sector address */
    uchar_ptr            from_ptr,

    /* [IN] Erased sector size */
    _mem_size            size
)
{
    KINETIS_FLASH_INTERNAL_STRUCT_PTR dev_spec_ptr;
    FTFL_MemMapPtr                    ftfl_ptr;
    uint_8                            command_array[4];

    dev_spec_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;

    /* get the pointer to ftfl registers structure */
    ftfl_ptr = (FTFL_MemMapPtr)dev_spec_ptr->ftfl_ptr;

    /* check if the destination address is sector aligned or not */
    if (0 != ((uint_32)from_ptr % FLASHX_SECT_SIZE))
    {
        return FALSE;
    }

    /* check if the size is sector aligned or not */
    if (0 != (size % FLASHX_SECT_SIZE))
    {
        return FALSE;
    }

    /* check for valid range of the target addresses */
    /*if ((from_ptr < FLASHX_START_ADDR) || (from_ptr + size >= FLASHX_END_ADDR))
    {
        return FALSE;
    }*/

    /* preparing passing parameter to erase a flash block */
    command_array[0] = FTFL_ERASE_SECTOR;
    command_array[1] = (uint_8)((uint_32)from_ptr >> 16);
    command_array[2] = (uint_8)(((uint_32)from_ptr >> 8) & 0xFF);
    command_array[3] = (uint_8)((uint_32)from_ptr & 0xFF);

    /* call flash command sequence function to execute the command */
    if (FTFL_OK != kinetis_flash_command_sequence (dev_spec_ptr, command_array, 4, FALSE))
    {
        return FALSE;
    }

    return TRUE;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : kinetis_flash_write_sector
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*   Performs a write into flash memory.
*
*END*----------------------------------------------------------------------*/
boolean kinetis_flash_write_sector
(
    /* [IN] Flash info structure */
    IO_FLASHX_STRUCT_PTR flash_ptr,

    /* [IN] Source address */
    uchar_ptr            from_ptr,

    /* [IN] Destination address */
    uchar_ptr            to_ptr,

    /* [IN] Number of bytes to write */
    _mem_size            size
) 
{
    KINETIS_FLASH_INTERNAL_STRUCT_PTR dev_spec_ptr;
    FTFL_MemMapPtr                    ftfl_ptr;
    uint_8                            command_array[8];
    uint_32                           temp_data = 0xFFFFFFFF;
    uchar_ptr                         temp_data_ptr = (uchar_ptr)&temp_data;
    uchar                             byte_data_counter = 0;
    uint_32                           offset = ((uint_32)to_ptr) & 0x00000003;

    dev_spec_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;

    /* get the pointer to ftfl registers structure */
    ftfl_ptr = (FTFL_MemMapPtr)dev_spec_ptr->ftfl_ptr;    

    /* write to address mod 4 correction */
    if (offset)
    {
        /* align pointer to writable address */
        to_ptr -= offset;
        
        /* jump over old data */
        byte_data_counter = offset; 
    }

    /* check boundaries */
    if ((to_ptr < FLASHX_START_ADDR) || (to_ptr + size >= FLASHX_END_ADDR))
    {
        return FALSE;
    }
    
    while (size)
    {
        /* move data to aligned long word */       
        while ((byte_data_counter < 4) && size)
        {
            *(uchar_ptr)(temp_data_ptr + byte_data_counter) = *from_ptr++;
            byte_data_counter++;
            size--;
        }
        
        /* prepare parameters to program the flash block */
        command_array[0] = FTFL_PROGRAM_LONGWORD;
        command_array[1] = (uint_8)((uint_32)to_ptr >> 16);
        command_array[2] = (uint_8)(((uint_32)to_ptr >> 8) & 0xFF);
        command_array[3] = (uint_8)((uint_32)to_ptr & 0xFF);
        
        command_array[4] = temp_data_ptr[3];
        command_array[5] = temp_data_ptr[2];
        command_array[6] = temp_data_ptr[1];
        command_array[7] = temp_data_ptr[0];
                
        /* call flash command sequence function to execute the command */
        if (FTFL_OK != kinetis_flash_command_sequence (dev_spec_ptr, command_array, 8, FALSE))
        {
            return FALSE;
        }
               
        /* update destination address for next iteration */
        to_ptr += FTFL_LONGWORD_SIZE;

        /* init variables for next loop */
        byte_data_counter = 0;
        temp_data = 0xFFFFFFFF;
    }
    
    return TRUE;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : kinetis_flash_erase
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*   Erase the whole flash memory.
*
*END*----------------------------------------------------------------------*/
boolean kinetis_flash_erase 
(
    /* [IN] Flash info structure */
    IO_FLASHX_STRUCT_PTR flash_ptr
)
{
    int i, j;
    FLASHX_BLOCK_INFO_STRUCT_PTR   block_info_ptr;
    _mqx_uint block;
    uint_32 erase_sector;
    
    block_info_ptr = flash_ptr->BLOCK_INFO_PTR;
        
    for (j = 0; j < flash_ptr->BLOCK_GROUPS; j++, block_info_ptr++)
    {
        erase_sector = (uint_32)(block_info_ptr->START_ADDR + flash_ptr->BASE_ADDR) & 0xffffff;
        
        /* bank 1 - FLEXNVM */
        if (j)
        {
            erase_sector += (1 << 23);
        }
        
        for (i = 0; i < block_info_ptr->NUM_SECTORS; i++)
        {
            if (! kinetis_flash_erase_sector (flash_ptr, (uchar_ptr)erase_sector, 0))
            {
                return FALSE;
            }
            erase_sector += block_info_ptr->SECT_SIZE;
        }
    }
    
    return TRUE;
}

/********************************************************************
*
*  Code required to run in SRAM to perform flash commands. 
*  All else can be run in flash.
*  Parameter is an address of flash status register.
*
********************************************************************/ 
static void kinetis_ram_function
( 
    /* [IN] Flash info structure */
    volatile uchar_ptr ftfl_fstat_ptr
) 
{
    /* start flash write */
    *ftfl_fstat_ptr |= FTFL_FSTAT_CCIF_MASK;
    
    /* wait until execution complete */
    while (0 == ((*ftfl_fstat_ptr) & FTFL_FSTAT_CCIF_MASK))
        { };
}
         
static void kinetis_ram_function_end
(
    void
)
{
} 

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : kinetis_flash_erase_sector
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*   Program Partition Command
*
*END*----------------------------------------------------------------------*/
boolean kinetis_flexnvm_read_resource(IO_FLASHX_STRUCT_PTR flash_ptr, FLEXNVM_READ_RSRC_STRUCT_PTR param_ptr) {
    KINETIS_FLASH_INTERNAL_STRUCT_PTR dev_spec_ptr;
    FTFL_MemMapPtr ftfl_ptr;
    uint_8 command_array[9];

    dev_spec_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;

    /* get the pointer to ftfl registers structure */
    ftfl_ptr = (FTFL_MemMapPtr)dev_spec_ptr->ftfl_ptr;

    /* preparing passing parameter to erase a flash block */
    command_array[0] = FTFL_RDRSRC;
    command_array[1] = (uint_8)((param_ptr->ADDR >> 16) & 0xFF);
    command_array[2] = (uint_8)((param_ptr->ADDR >> 8) & 0xFF);
    command_array[3] = (uint_8)(param_ptr->ADDR & 0xFF);
    
    command_array[8] = (uint_8)(param_ptr->RSRC_CODE);

    /* call flash command sequence function to execute the command */
    if (FTFL_OK != kinetis_flash_command_sequence(dev_spec_ptr, command_array, 9, TRUE)) {
        return FALSE;
    }
    
    param_ptr->RD_DATA = *(uint_32*)(&command_array[4]);

    return TRUE;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : kinetis_flash_erase_sector
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*   Program Partition Command
*
*END*----------------------------------------------------------------------*/
boolean kinetis_flexnvm_prog_part(IO_FLASHX_STRUCT_PTR flash_ptr, FLEXNVM_PROG_PART_STRUCT_PTR param_ptr) {
    KINETIS_FLASH_INTERNAL_STRUCT_PTR dev_spec_ptr;
    FTFL_MemMapPtr ftfl_ptr;
    uint_8 command_array[6];

    dev_spec_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;

    /* get the pointer to ftfl registers structure */
    ftfl_ptr = (FTFL_MemMapPtr)dev_spec_ptr->ftfl_ptr;



    /* preparing passing parameter to erase a flash block */
    command_array[0] = FTFL_PGMPART;
    command_array[1] = 0;
    command_array[2] = 0;
    command_array[3] = 0;
    command_array[4] = param_ptr->EE_DATA_SIZE_CODE;
    command_array[5] = param_ptr->FLEXNVM_PART_CODE;

    /* call flash command sequence function to execute the command */
    if (FTFL_OK != kinetis_flash_command_sequence(dev_spec_ptr, command_array, 6, FALSE)) {
        return FALSE;
    }

    return TRUE;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : kinetis_flash_erase_sector
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*   Program Partition Command
*
*END*----------------------------------------------------------------------*/
boolean kinetis_flexnvm_set_flexram(IO_FLASHX_STRUCT_PTR flash_ptr, uchar ctrl_code) {
    KINETIS_FLASH_INTERNAL_STRUCT_PTR dev_spec_ptr;
    FTFL_MemMapPtr ftfl_ptr;
    uint_8 command_array[2];

    dev_spec_ptr = flash_ptr->DEVICE_SPECIFIC_DATA;

    /* get the pointer to ftfl registers structure */
    ftfl_ptr = (FTFL_MemMapPtr)dev_spec_ptr->ftfl_ptr;



    /* preparing passing parameter to erase a flash block */
    command_array[0] = FTFL_SET_RAM;
    command_array[1] = ctrl_code;


    /* call flash command sequence function to execute the command */
    if (FTFL_OK != kinetis_flash_command_sequence (dev_spec_ptr, command_array, 2, FALSE)) {
        return FALSE;
    }

    return TRUE;
}

_mqx_int kinetis_flash_ioctl(IO_FLASHX_STRUCT_PTR handle_ptr, _mqx_uint cmd, pointer param_ptr)
{
    _mqx_int result = IO_OK;
    
    switch (cmd) {
        case FLEXNVM_IOCTL_READ_RESOURCE:
            kinetis_flexnvm_read_resource(handle_ptr, (FLEXNVM_READ_RSRC_STRUCT_PTR)param_ptr);
            break;
        case FLEXNVM_IOCTL_GET_PARTITION_CODE: {
                FLEXNVM_READ_RSRC_STRUCT rsrc_param;
                
                rsrc_param.ADDR = 0x8000fc;
                rsrc_param.RSRC_CODE = 0;
                
                if (kinetis_flexnvm_read_resource(handle_ptr, &rsrc_param) && NULL != param_ptr) {
                    ((FLEXNVM_PROG_PART_STRUCT_PTR)param_ptr)->EE_DATA_SIZE_CODE = (rsrc_param.RD_DATA >> 8) & (FLEXNVM_EE_SPLIT_MASK | FLEXNVM_EE_SIZE_MASK);
                    ((FLEXNVM_PROG_PART_STRUCT_PTR)param_ptr)->FLEXNVM_PART_CODE = rsrc_param.RD_DATA & FLEXNVM_PART_CODE_MASK;
                }
                else {
                    result = IO_ERROR_READ;
                }

                break;
            }
        case FLEXNVM_IOCTL_SET_PARTITION_CODE:
            kinetis_flexnvm_prog_part(handle_ptr, (FLEXNVM_PROG_PART_STRUCT_PTR)param_ptr);
            break;
        case FLEXNVM_IOCTL_SET_FLEXRAM_FN:
            kinetis_flexnvm_set_flexram(handle_ptr, *(uchar*)param_ptr);
            break;
        case FLEXNVM_IOCTL_WAIT_EERDY: {
                KINETIS_FLASH_INTERNAL_STRUCT_PTR dev_spec_ptr = handle_ptr->DEVICE_SPECIFIC_DATA;
                FTFL_MemMapPtr ftfl_ptr = (FTFL_MemMapPtr)dev_spec_ptr->ftfl_ptr;
            
                while (!(ftfl_ptr->FCNFG & FTFL_FCNFG_EEERDY_MASK)){}
                
                break;
            }
        case FLEXNVM_IOCTL_GET_EERDY: {
                KINETIS_FLASH_INTERNAL_STRUCT_PTR dev_spec_ptr = handle_ptr->DEVICE_SPECIFIC_DATA;
                FTFL_MemMapPtr ftfl_ptr = (FTFL_MemMapPtr)dev_spec_ptr->ftfl_ptr;
                
                if (NULL != param_ptr)
                    *(uint_32*)param_ptr = (ftfl_ptr->FCNFG & FTFL_FCNFG_EEERDY_MASK);
                
                break;
            }
        default:
            result = IO_ERROR_INVALID_IOCTL_CMD;
            break;
    }
          
    return result;
}

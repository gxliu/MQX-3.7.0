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
* $FileName: flash_mcf51xx.h$
* $Version : 3.7.9.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   The file contains functions prototype, defines for the internal 
*   flash driver
*
*END************************************************************************/

#ifndef __INT_FLASH_MCF51XX_H__
#define __INT_FLASH_MCF51XX_H__


#define CFM_IPS_FLASH_ADDR              0x44000000

/* address in memory map to write in FLASH */
#define FLASH_START_ADDRESS  CFM_IPS_FLASH_ADDR

/* End address for region of flash */
#define FLASH_END_ADDRESS   (vuint32)&__FLASH_SIZE

#define FSTR_SET_STD    0
#define FSTR_SET_1      1
#define FSTR_SET_2      2

#define MEMORY_ARRAY_STD    0
#define MEMORY_ARRAY_1      1
#define MEMORY_ARRAY_2      2
#define MEMORY_ARRAY_1_FLASH 3
#define MEMORY_ARRAY_2_FLASH 4


typedef struct internal_51xx_struct 
{
    vuchar_ptr   ftsr_ptr;  /* pointer to proper FSTAT register */
    uchar_ptr   flash_execute_code_ptr; /* pointer to flash write and erase code */
        
} INTERNAL_51XX_STRUCT, _PTR_ INTERNAL_51XX_STRUCT_PTR;
/*----------------------------------------------------------------------*/
/*
**                    FUNCTION PROTOTYPES
*/

//pointer _bsp_get_cfm_address( uchar );
void    _mcf51xx_set_cfmclkd();
void _mcf51xx_set_cfmclkd_ext( uchar );
#ifdef PSP_HAS_DUAL_FLASH
void _mcf51xx_set_cfmclkd_mem_array_1();
void _mcf51xx_set_cfmclkd_mem_array_2();
#endif
boolean mcf_51xx_flash_init( IO_FLASHX_STRUCT_PTR );
void mcf_51xx_flash_deinit( IO_FLASHX_STRUCT_PTR );
boolean mcf51xx_erase_sector( IO_FLASHX_STRUCT_PTR, uchar_ptr, _mem_size );
boolean mcf51xx_write_sector( IO_FLASHX_STRUCT_PTR, uchar_ptr, uchar_ptr, _mem_size );
boolean mcf51xx_erase_flash( IO_FLASHX_STRUCT_PTR );
#ifdef PSP_HAS_DUAL_FLASH
uint_32 mcf51xx_internal_flash_array1_install( char_ptr, uint_32 );
uint_32 mcf51xx_internal_flash_array2_install( char_ptr, uint_32 );
boolean mcf_51xx_flash_array1_init( IO_FLASHX_STRUCT_PTR );
boolean mcf_51xx_flash_array2_init(IO_FLASHX_STRUCT_PTR );
#else
uint_32 mcf51xx_internal_flash_install( char_ptr, uint_32 );
#endif
_mqx_int _io_mcf51xx_ioctl( IO_FLASHX_STRUCT_PTR, _mqx_uint, pointer );
void _mcf51_swap_flash_and_reset();
/********************************************************************/
#endif /* __INT_FLASH_MCF51XX_H__ */

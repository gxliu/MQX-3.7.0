#ifndef __flash_kinetis_h__
#define __flash_kinetis_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: flash_kinetis.h$
* $Version : 3.7.4.2$
* $Date    : Mar-30-2011$
*
* Comments:
*
*   The file contains function prototypes and defines for the internal 
*   flash driver.
*
*END************************************************************************/

#include "flashx.h"

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

/* FTFL commands */
#define FTFL_VERIFY_BLOCK              0x00
#define FTFL_VERIFY_SECTION            0x01
#define FTFL_PROGRAM_CHECK             0x02
#define FTFL_RDRSRC                    0x03
#define FTFL_PROGRAM_LONGWORD          0x06
#define FTFL_ERASE_BLOCK               0x08
#define FTFL_ERASE_SECTOR              0x09
#define FTFL_PROGRAM_SECTION           0x0B
#define FTFL_VERIFY_ALL_BLOCK          0x40
#define FTFL_READ_ONCE                 0x41
#define FTFL_PROGRAM_ONCE              0x43
#define FTFL_ERASE_ALL_BLOCK           0x44
#define FTFL_SECURITY_BY_PASS          0x45
#define FTFL_PGMPART                   0x80     // Program Partition Command
#define FTFL_SET_RAM                   0x81     // Set FlexRAM Function Command

/* FTFL margin read settings */
#define FTFL_MARGIN_NORMAL             0x0000
#define FTFL_USER_MARGIN_LEVEL1        0x0001
#define FTFL_USER_MARGIN_LEVEL0        0x0002
#define FTFL_FACTORY_MARGIN_LEVEL0     0x0003
#define FTFL_FACTORY_MARGIN_LEVEL1     0x0004

/* FTFL sizes */
#define FTFL_WORD_SIZE                 0x0002
#define FTFL_LONGWORD_SIZE             0x0004
#define FTFL_PHRASE_SIZE               0x0008

/* FTFL error codes */
#define FTFL_OK                        0x0000
#define FTFL_ERR_SIZE                  0x0001
#define FTFL_ERR_RANGE                 0x0002
#define FTFL_ERR_ACCERR                0x0004
#define FTFL_ERR_PVIOL                 0x0008
#define FTFL_ERR_MGSTAT0               0x0010
#define FTFL_ERR_CHANGEPROT            0x0020
#define FTFL_ERR_EEESIZE               0x0040
#define FTFL_ERR_EFLASHSIZE            0x0080
#define FTFL_ERR_ADDR                  0x0100
#define FTFL_ERR_NOEEE                 0x0200
#define FTFL_ERR_EFLASHONLY            0x0400
#define FTFL_ERR_DFLASHONLY            0x0800
#define FTFL_ERR_RDCOLERR              0x1000
#define FTFL_ERR_RAMRDY                0x2000

/* Start and End Address of PFlash IFR and DFlash IFR */
#define PFLASH_IFR_START_ADDRESS       0x000000
#define PFLASH_IFR_END_ADDRESS         0x0000FF
#define DFLASH_IFR_START_ADDRESS       0x800000
#define DFLASH_IFR_END_ADDRESS         0x8000FF
#define DFLASH_IFR_LONGWORD_ADDRESS    0x8000FC

#define FLASHX_INVALIDATE_CACHE_ALL    0xFFFFFFFF
#define FLASHX_INVALIDATE_CACHE_BLOCK0 0x00000001
#define FLASHX_INVALIDATE_CACHE_BLOCK1 0x00000002


#define FLEXNVM_IOCTL_READ_RESOURCE         _IO(IO_TYPE_FLASH, 0x14)
#define FLEXNVM_IOCTL_GET_PARTITION_CODE    _IO(IO_TYPE_FLASH, 0x15)
#define FLEXNVM_IOCTL_SET_PARTITION_CODE    _IO(IO_TYPE_FLASH, 0x16)
#define FLEXNVM_IOCTL_GET_FLEXRAM_FN        _IO(IO_TYPE_FLASH, 0x17)
#define FLEXNVM_IOCTL_SET_FLEXRAM_FN        _IO(IO_TYPE_FLASH, 0x18)
#define FLEXNVM_IOCTL_WAIT_EERDY            _IO(IO_TYPE_FLASH, 0x19)
#define FLEXNVM_IOCTL_GET_EERDY             _IO(IO_TYPE_FLASH, 0x1a)


/* FlexNVM partition code bit mask */
#define FLEXNVM_PART_CODE_MASK              (0x0f)

/* FlexNVM partition code values */
#define FLEXNVM_PART_CODE_DATA256_EE0       (0)
#define FLEXNVM_PART_CODE_DATA224_EE32      (3)
#define FLEXNVM_PART_CODE_DATA192_EE64      (4)
#define FLEXNVM_PART_CODE_DATA128_EE128     (5)
#define FLEXNVM_PART_CODE_DATA32_EE224      (0x0b)
#define FLEXNVM_PART_CODE_DATA64_EE192      (0x0c)
#define FLEXNVM_PART_CODE_DATA0_EE256       (8)
#define FLEXNVM_PART_CODE_NOPART            (0x0f)


/* FlexNVM split bit mask */
#define FLEXNVM_EE_SPLIT_MASK               (0x30)

/* FlexNVM split values */
#define FLEXNVM_EE_SPLIT_1_7                (0)
#define FLEXNVM_EE_SPLIT_1_3                (0x10)
#define FLEXNVM_EE_SPLIT_1_1                (0x30)


/* FlexNVM EEPROM size bit mask */
#define FLEXNVM_EE_SIZE_MASK                (0x0f)

/* FlexNVM EEPROM size values */
#define FLEXNVM_EE_SIZE_4096                (2)
#define FLEXNVM_EE_SIZE_2048                (3)
#define FLEXNVM_EE_SIZE_1024                (4)
#define FLEXNVM_EE_SIZE_512                 (5)
#define FLEXNVM_EE_SIZE_256                 (6)
#define FLEXNVM_EE_SIZE_128                 (7)
#define FLEXNVM_EE_SIZE_64                  (8)
#define FLEXNVM_EE_SIZE_32                  (9)
#define FLEXNVM_EE_SIZE_0                   (0x0f)


#define FLEXNVM_FLEXRAM_RAM                 (0xff)
#define FLEXNVM_FLEXRAM_EE                  (0)


#define FLEXNVM_WAIT_EERDY()  \
    { while (!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK)) {asm("nop"); }; }

#define FLEXNVM_EE_WRITE(addr, val) \
    { FLEXNVM_WAIT_EERDY(); *(addr) = (val); }


/*----------------------------------------------------------------------*/
/*
**                    Structure Definitions
*/

typedef struct kinetis_flash_internal_struct 
{
    vuchar_ptr  ftfl_ptr;
    uchar_ptr   flash_execute_code_ptr; /* pointer to executable code in RAM */
    uchar_ptr   ramfcn_memaloc_ptr;     /* pointer to RAM allocated memory */
        
} KINETIS_FLASH_INTERNAL_STRUCT, _PTR_ KINETIS_FLASH_INTERNAL_STRUCT_PTR;

typedef struct kinetis_flexnvm_prog_part_struct {
    uint_8 EE_DATA_SIZE_CODE;
    uint_8 FLEXNVM_PART_CODE;
} FLEXNVM_PROG_PART_STRUCT, _PTR_ FLEXNVM_PROG_PART_STRUCT_PTR;

typedef struct kinetis_flexnvm_read_rsrc_struct {
    uint_32 ADDR;
    uint_8 RSRC_CODE;
    uint_32 RD_DATA;
} FLEXNVM_READ_RSRC_STRUCT, _PTR_ FLEXNVM_READ_RSRC_STRUCT_PTR;

/*----------------------------------------------------------------------*/
/*
**                    FUNCTION PROTOTYPES
*/

pointer _bsp_get_ftfl_address (void);
boolean kinetis_flash_init (IO_FLASHX_STRUCT_PTR);
void    kinetis_flash_deinit (IO_FLASHX_STRUCT_PTR);
boolean kinetis_flash_erase_sector (IO_FLASHX_STRUCT_PTR, uchar_ptr, _mem_size);
boolean kinetis_flash_write_sector (IO_FLASHX_STRUCT_PTR, uchar_ptr, uchar_ptr, _mem_size);
boolean kinetis_flash_erase (IO_FLASHX_STRUCT_PTR);
uint_32 kinetis_flash_install_internal (char_ptr, uint_32);
void    kinetis_flash_invalidate_cache (uint_32);

_mqx_int kinetis_flash_ioctl(IO_FLASHX_STRUCT_PTR handle_ptr, _mqx_uint cmd, pointer param_ptr);

#endif

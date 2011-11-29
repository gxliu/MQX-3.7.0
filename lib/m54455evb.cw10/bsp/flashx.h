#ifndef _flashx_h_
#define _flashx_h_
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
* $FileName: flashx.h$
* $Version : 3.6.13.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   The file contains functions prototype, defines, structure 
*   definitions specific for the flash drivers
*
*END************************************************************************/

#include "ioctl.h"

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

/*
** Flash IOCTL calls
*/
#define FLASH_IOCTL_GET_BASE_ADDRESS     _IO(IO_TYPE_FLASH,0x01)
#define FLASH_IOCTL_GET_NUM_SECTORS      _IO(IO_TYPE_FLASH,0x02)
#define FLASH_IOCTL_GET_SECTOR_SIZE      _IO(IO_TYPE_FLASH,0x03)
#define FLASH_IOCTL_GET_WIDTH            _IO(IO_TYPE_FLASH,0x04)
#define FLASH_IOCTL_GET_SECTOR_BASE      _IO(IO_TYPE_FLASH,0x05)
#define FLASH_IOCTL_GET_BLOCK_GROUPS     _IO(IO_TYPE_FLASH,0x06)
#define FLASH_IOCTL_GET_BLOCK_MAP        _IO(IO_TYPE_FLASH,0x07)
#define FLASH_IOCTL_FLUSH_BUFFER         _IO(IO_TYPE_FLASH,0x08)
#define FLASH_IOCTL_ENABLE_BUFFERING     _IO(IO_TYPE_FLASH,0x09)
#define FLASH_IOCTL_DISABLE_BUFFERING    _IO(IO_TYPE_FLASH,0x0A)
#define FLASH_IOCTL_ERASE_SECTOR         _IO(IO_TYPE_FLASH,0x0B)
#define FLASH_IOCTL_ERASE_CHIP           _IO(IO_TYPE_FLASH,0x0C)
#define FLASH_IOCTL_ENABLE_SECTOR_CACHE  _IO(IO_TYPE_FLASH,0x0D)
#define FLASH_IOCTL_DISABLE_SECTOR_CACHE _IO(IO_TYPE_FLASH,0x0E)
#define FLASH_IOCTL_WRITE_PROTECT        _IO(IO_TYPE_FLASH,0x0F)
#define FLASH_IOCTL_GET_WRITE_PROTECT    _IO(IO_TYPE_FLASH,0x10)
#define FLASH_IOCTL_SWAP_FLASH_AND_RESET _IO(IO_TYPE_FLASH,0x11)
#define FLASH_IOCTL_WRITE_ERASE_CMD_FROM_FLASH_ENABLE   _IO(IO_TYPE_FLASH,0x12) 
#define FLASH_IOCTL_WRITE_ERASE_CMD_FROM_FLASH_DISABLE  _IO(IO_TYPE_FLASH,0x13) 
 
/*
** Flash Error Codes 
*/

#define FLASHXERR_NO_ERROR                (0)
#define FLASHXERR_INVALID_SIZE             (FLASHX_ERROR_BASE | 0x01)

/*----------------------------------------------------------------------*/
/*
**                    DATATYPE DEFINITIONS
*/
#define FLASHX_FLASH_BUFFER_ENABLED      (0x00000001)
#define FLASHX_SECTOR_CACHE_ENABLED      (0x00000002)
#define FLASHX_WR_ERASE_FROM_FLASH_ENABLED  (0x00000004)

/*----------------------------------------------------------------------*/
/*
**                    Structure Definitions
*/

/*
** BLOCK INFO STRUCT
**
** This structure is used to map the blocks of odd size sectors on a flash chip
*/

typedef struct flashx_block_info_struct
{
   /* The number of sectors with the same size in this block */
   _mqx_uint        NUM_SECTORS;
   
   /* Start address of the block of same size sectors */
   _mem_size        START_ADDR;

   /* The size of the sectors in this block */
   _mem_size        SECT_SIZE;

} FLASHX_BLOCK_INFO_STRUCT, _PTR_ FLASHX_BLOCK_INFO_STRUCT_PTR;

/*
** FLASHX STRUCT
**
** The address of this structure is used to maintain flash specific 
** information.
*/

typedef struct io_flashx_struct
{
   /* The function to call to erase a sector on the device */
   boolean (_CODE_PTR_           SECTOR_ERASE)(struct io_flashx_struct _PTR_, 
      uchar_ptr, _mem_size);

   /* The function to call to program a sector on the device */
   boolean (_CODE_PTR_           SECTOR_PROGRAM)(struct io_flashx_struct _PTR_, 
      uchar_ptr, uchar_ptr, _mem_size);
   
   /* The function to call to erase the entire device */
   boolean (_CODE_PTR_           CHIP_ERASE)(struct io_flashx_struct _PTR_);
   
   /* The function to call to initialize the device */
   boolean (_CODE_PTR_           INIT)(struct io_flashx_struct _PTR_);
   
   /* The function to call to disable the device */
   void (_CODE_PTR_              DEINIT)(struct io_flashx_struct _PTR_);
   
   /* The function to call to write enable or protect the device */
   boolean (_CODE_PTR_           WRITE_PROTECT)(struct io_flashx_struct _PTR_, 
      _mqx_uint);
   
   /* This struture provides a mapping of the blocks on the flash device */ 
   FLASHX_BLOCK_INFO_STRUCT_PTR  BLOCK_INFO_PTR;
   
   /* Address of the flash device */
   uchar_ptr                     BASE_ADDR;
   
   /* The number of blocks of sectors of a common size on the device */
   _mqx_uint                     BLOCK_GROUPS;
   
   /* The maximum sector size of this device */
   _mem_size                     MAX_SECT_SIZE;
   
   /* The total size of the device */
   _mem_size                     TOTAL_SIZE;
   
   /* The width of the device */
   _mqx_uint                     WIDTH;
   
   /* The number of parallel devices */
   _mqx_uint                     DEVICES;
   
   /* When finished programming, should a comparison of data be made
   ** to verify that the write worked correctly.
   */
   _mqx_uint                     WRITE_VERIFY;

   /* Next three are needed for buffering data */
   _mqx_uint                     DIRTY_DATA;
   _mqx_uint                     CURRENT_BLOCK;
   _mqx_uint                     CURRENT_SECTOR;
   
   /* Light weight semaphore struct */
   LWSEM_STRUCT                  LWSEM;
   
   /* The address of temp buffer */
   pointer                       TEMP_PTR;
   
   /* The address of erase check array */
   _mqx_uint_ptr                 ERASE_ARRAY;
   
   /* The size of the erase array */
   _mqx_uint                     ERASE_ARRAY_SIZE;
   
   /* The current error code for the device */
   _mqx_uint                     ERROR_CODE;
   
   /* The number of tasks which have access to the flash device */
   _mqx_uint                     COUNT;
   
   /* Flags */
   _mqx_uint                     FLAGS;
   
   /* The ioctl function to call */
   _mqx_int (_CODE_PTR_           IOCTL)(struct io_flashx_struct _PTR_, 
      _mqx_uint, pointer);
    /* The address of device specific structure */ 
    pointer                      DEVICE_SPECIFIC_DATA;

} IO_FLASHX_STRUCT, _PTR_ IO_FLASHX_STRUCT_PTR;


/* 
** FLASHX INIT STRUCT
**
** This structure is used to initialize a flash device.
*/

typedef struct flashx_init_struct
{

   /* A pointer to a string that identifies the device for fopen */
   char_ptr                      ID_PTR;
   
   /* The function to call to erase a flashx block */
   boolean (_CODE_PTR_           SECTOR_ERASE)(IO_FLASHX_STRUCT_PTR, uchar_ptr,
      _mem_size);

   /* The function to call to program a flash block */
   boolean (_CODE_PTR_           SECTOR_PROGRAM)(IO_FLASHX_STRUCT_PTR, 
      uchar_ptr, uchar_ptr, _mem_size);

   /* The function to call to erase the entire flash chip */
   boolean (_CODE_PTR_           CHIP_ERASE)(IO_FLASHX_STRUCT_PTR);

   /* The function to call to initialize the flash device, if needed */
   boolean (_CODE_PTR_           INIT)(IO_FLASHX_STRUCT_PTR);

   /* The function to call to disable the flash device, if needed */
   void (_CODE_PTR_              DEINIT)(IO_FLASHX_STRUCT_PTR);
   
   /* The function to call to enable or disable writing to the flash device */
   boolean (_CODE_PTR_           WRITE_PROTECT)(IO_FLASHX_STRUCT_PTR, 
      _mqx_uint);
   
   /* Pointer to an array of mappings for blocks and their sizes */
   FLASHX_BLOCK_INFO_STRUCT_PTR  MAP_PTR;
   
   /* the address of the flash */
   pointer                       BASE_ADDR; 
   
   /* the width of the device in bytes */
   _mqx_uint                     WIDTH;

   /* the number of devices in parallel */
   _mqx_uint                     DEVICES;

   /* When finished programming, should a comparison of data be made
   ** to verify that the write worked correctly.
   */
   _mqx_uint                     WRITE_VERIFY;
   
   /* The ioctl function to call */
   _mqx_int (_CODE_PTR_           IOCTL)(IO_FLASHX_STRUCT_PTR, 
      _mqx_uint, pointer);

} FLASHX_INIT_STRUCT, _PTR_ FLASHX_INIT_STRUCT_PTR;


/*----------------------------------------------------------------------*/
/*
**                    FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif
  
extern _mqx_uint _io_flashx_install(FLASHX_INIT_STRUCT _PTR_);
extern _mqx_int  _io_flashx_uninstall(IO_DEVICE_STRUCT_PTR);
extern _mqx_int _io_flashx_write(MQX_FILE_PTR , char_ptr, _mqx_int );

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

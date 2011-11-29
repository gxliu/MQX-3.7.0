#ifndef _apcflshpr_h_
#define _apcflshpr_h_
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
* $FileName: apcflshpr.h$
* $Version : 3.6.5.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   The file contains functions prototype, defines, structure 
*   definitions private to the advanced PC Card flash drivers
*
*END************************************************************************/

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

/* Error codes from lower layers */
#define PCFLASH_NO_ERROR             (0)
#define PCFLASH_ERROR_NO_CARD        (PCFLASH_ERROR_BASE | 0x01)
#define PCFLASH_INVALID_SECTOR       (PCFLASH_ERROR_BASE | 0x02)
#define PCFLASH_INVALID_CARD         (PCFLASH_ERROR_BASE | 0x03)
#define PCFLASH_INVALID_DRIVE        (PCFLASH_ERROR_BASE | 0x04)
#define PCFLASH_INVALID_VOLTAGE      (PCFLASH_ERROR_BASE | 0x05)
#define PCFLASH_INVALID_HANDLE       (PCFLASH_ERROR_BASE | 0x06)
#define PCFLASH_HARDWARE_ERROR       (PCFLASH_ERROR_BASE | 0x07)
#define PCFLASH_READ_ERROR           (PCFLASH_ERROR_BASE | 0x08)
#define PCFLASH_WRITE_ERROR          (PCFLASH_ERROR_BASE | 0x09)

/*----------------------------------------------------------------------*/
/*
**                    DATATYPE DEFINITIONS
*/


/*
** PC_FLASH_INFO_STRUCT
** Run time state information for each PC Card Flash device
*/
typedef struct io_pcflash_info_struct
{
   /* Handle for PCCard calls */
   MQX_FILE_PTR  PCCARD_STREAM;

   /* Drive number to associate with this slot */
   uint_32       DRIVE;         

   /* Sector size in bytes */
   uint_32       SECTOR_SIZE;   

   /* The total number of sectors in the device */
   uint_32       NUM_SECTORS;

   /* Total size of flash card in bytes */
   uint_32       SIZE;          

   /* The number of heads as reported by the ATA ident command */
   uint_32       NUMBER_OF_HEADS;          

   /* The number of tracks as reported by the ATA ident command */
   uint_32       NUMBER_OF_TRACKS;

   /* The number of sectos per cylinder as reported by the ATA ident command */
   uint_32       SECTORS_PER_TRACK;

   /* ATA Register location */
   uchar_ptr     ATA_REG_PTR;

   /* ATA Data Register location */
   uint_16_ptr   ATA_DATA_PTR;
     
   /* Light weight semaphore struct */
   LWSEM_STRUCT  LWSEM;
   
   /* The address of temp buffer */
   uchar_ptr     TEMP_BUFF_PTR;

   /* The current error code for the device */
   uint_32       ERROR_CODE;

   /* Start CR 812 */
   /* Indicates if the device is running in block mode or character mode */
   boolean       BLOCK_MODE;
   /* End   CR 812 */


} IO_PCFLASH_STRUCT, _PTR_ IO_PCFLASH_STRUCT_PTR;

#ifdef __cplusplus
extern "C" {
#endif

extern _mqx_int _io_apcflash_open(FILE_DEVICE_STRUCT_PTR, char _PTR_, char _PTR_);
extern _mqx_int _io_apcflash_close(FILE_DEVICE_STRUCT_PTR);
extern _mqx_int _io_apcflash_read (FILE_DEVICE_STRUCT_PTR, char_ptr, _mqx_int);
extern _mqx_int _io_apcflash_write(FILE_DEVICE_STRUCT_PTR, char_ptr, _mqx_int);
extern _mqx_int _io_apcflash_ioctl(FILE_DEVICE_STRUCT_PTR, _mqx_uint, pointer);

extern uint_32 _io_apcflash_read_sector(IO_PCFLASH_STRUCT_PTR, uint_32, 
   uchar_ptr);
extern int_32  _io_apcflash_read_partial_sector(FILE_DEVICE_STRUCT_PTR, uint_32, 
   uint_32, uint_32, uchar_ptr);
extern uint_32 _io_apcflash_write_sector(IO_PCFLASH_STRUCT_PTR, uint_32, 
   uchar_ptr);
extern int_32  _io_apcflash_write_partial_sector(FILE_DEVICE_STRUCT_PTR, 
   uint_32, uint_32, uint_32, uchar_ptr);
extern uint_32 _io_apcflash_identify_device(IO_PCFLASH_STRUCT_PTR, uchar_ptr);
extern uint_32 _io_apcflash_reset(IO_PCFLASH_STRUCT_PTR);
extern boolean _io_apcflash_bsy_timeout(volatile uchar _PTR_, uint_32);
/* Start CR 812 */
extern _mqx_int _io_apcflash_read_write_blocks(FILE_DEVICE_STRUCT_PTR, 
   IO_PCFLASH_STRUCT_PTR, char_ptr, _mqx_int, boolean);
/* End   CR 812 */

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

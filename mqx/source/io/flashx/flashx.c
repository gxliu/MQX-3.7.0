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
* $FileName: flashx.c$
* $Version : 3.7.15.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains generic flash driver functions to deal with odd
*   size flash blocks.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "fio.h"
#include "fio_prv.h"
#include "io.h"
#include "io_prv.h"
#include "flashx.h"
#include "flashxprv.h"

#define MFS_SECTOR_SIZE 512

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_install
* Returned Value   : _mqx_uint a task error code or MQX_OK
* Comments         :
*    Install a flash driver.
*
*END*----------------------------------------------------------------------*/

_mqx_uint _io_flashx_install
   (
      /* [IN] The initialization structure for the device */
      FLASHX_INIT_STRUCT _PTR_  init_ptr
   )
{ /* Body */
   IO_FLASHX_STRUCT_PTR           dev_ptr;
   FLASHX_BLOCK_INFO_STRUCT_PTR   block_info_ptr;
   _mem_size                      total_size = 0;
  
   dev_ptr = (IO_FLASHX_STRUCT_PTR)_mem_alloc_system_zero(
      (_mem_size)sizeof(IO_FLASHX_STRUCT));

#if MQX_CHECK_MEMORY_ALLOCATION_ERRORS
   if (dev_ptr == NULL) {
      return MQX_OUT_OF_MEMORY;
   } /* Endif */
#endif

   block_info_ptr = init_ptr->MAP_PTR;

   dev_ptr->SECTOR_ERASE   = init_ptr->SECTOR_ERASE;
   dev_ptr->SECTOR_PROGRAM = init_ptr->SECTOR_PROGRAM;
   dev_ptr->CHIP_ERASE     = init_ptr->CHIP_ERASE;
   dev_ptr->INIT           = init_ptr->INIT;
   dev_ptr->DEINIT         = init_ptr->DEINIT;
   dev_ptr->WRITE_PROTECT  = init_ptr->WRITE_PROTECT;
   dev_ptr->BLOCK_INFO_PTR = block_info_ptr;
   dev_ptr->BASE_ADDR      = init_ptr->BASE_ADDR;
   dev_ptr->WIDTH          = init_ptr->WIDTH;
   dev_ptr->DEVICES        = init_ptr->DEVICES;
   dev_ptr->WRITE_VERIFY   = init_ptr->WRITE_VERIFY;
   dev_ptr->DIRTY_DATA     = FALSE;
   dev_ptr->IOCTL          = init_ptr->IOCTL;

   /* 
   ** Determine the max sector size, total size and the number of common sized
   ** blocks
   */
   while (block_info_ptr->NUM_SECTORS) {
      if (block_info_ptr->SECT_SIZE > dev_ptr->MAX_SECT_SIZE) {
         dev_ptr->MAX_SECT_SIZE = block_info_ptr->SECT_SIZE;
      } /* Endif */
      total_size += (block_info_ptr->SECT_SIZE * block_info_ptr->NUM_SECTORS);
      dev_ptr->BLOCK_GROUPS++;
      block_info_ptr++;
   } /* Endwhile */

   dev_ptr->TOTAL_SIZE = total_size;
   
   _lwsem_create(&dev_ptr->LWSEM, 1);
    
   return (_io_dev_install_ext(
      init_ptr->ID_PTR,
      _io_flashx_open,
      _io_flashx_close,
      _io_flashx_read,
      _io_flashx_write,
      _io_flashx_ioctl,
      _io_flashx_uninstall, 
      (pointer)dev_ptr)); 

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_uninstall
* Returned Value   : _mqx_uint a task error code or MQX_OK
* Comments         :
*    Uninstalls a flash driver.
*
*END*----------------------------------------------------------------------*/

_mqx_int _io_flashx_uninstall
   (
      /* [IN] The IO device structure for the device */
      IO_DEVICE_STRUCT_PTR   io_dev_ptr
   )
{ /* Body */
   IO_FLASHX_STRUCT_PTR handle_ptr = 
      (IO_FLASHX_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;

   if (handle_ptr->COUNT == 0) {
      _mem_free((pointer)handle_ptr);
      io_dev_ptr->DRIVER_INIT_PTR = NULL;
      return IO_OK;
   } else {
      return IO_ERROR_DEVICE_BUSY;
   } /* Endif */  
   
}  /* Endbody */    


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_open
* Returned Value   : _mqx_uint a task error code or MQX_OK
* Comments         : Opens and initializes flash driver.
* 
*END*----------------------------------------------------------------------*/

_mqx_int _io_flashx_open
   (
      /* [IN] the file handle for the device being opened */
      MQX_FILE_PTR fd_ptr,
      
      /* [IN] the remaining portion of the name of the device */
      char_ptr   open_name_ptr,

      /* [IN] the flags to be used during operation: */
      char_ptr   flags
   )
{ /* Body */
   IO_DEVICE_STRUCT_PTR io_dev_ptr = fd_ptr->DEV_PTR;
   IO_FLASHX_STRUCT_PTR handle_ptr = 
      (IO_FLASHX_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
   _mqx_uint_ptr        erase_ptr;
   _mqx_uint            num_sectors = 0;
   _mqx_int             result;
   _mqx_uint            erase_array_size;
   boolean              chip_initialized = TRUE;
   _mqx_uint            i;
   
   if (handle_ptr->COUNT) {
      /* Device is already opened */
      result = _io_flashx_flush_buffer(handle_ptr);
      
      fd_ptr->FLAGS = handle_ptr->FLAGS;
      if (result != IO_ERROR) {
         handle_ptr->COUNT++;
         result = MQX_OK;
      } /* Endif */
      return result;
   } /* Endif */
      
   if (handle_ptr->INIT) {
      chip_initialized = (*handle_ptr->INIT)(handle_ptr);
   }/* Endif */

#if MQX_CHECK_ERRORS
   if (!chip_initialized) {
      return(IO_ERROR);
   } /* Endif */
#endif   
   
   for ( i = 0; i < handle_ptr->BLOCK_GROUPS; i++ ) {
      num_sectors += handle_ptr->BLOCK_INFO_PTR[i].NUM_SECTORS;
   } /* Endfor */
   erase_array_size = (num_sectors + MQX_INT_SIZE_IN_BITS) / MQX_INT_SIZE_IN_BITS;
   
   erase_ptr = (_mqx_uint_ptr)_mem_alloc_system((_mem_size)(erase_array_size * 
      sizeof(_mqx_uint)));
      
#if MQX_CHECK_MEMORY_ALLOCATION_ERRORS
    if(erase_ptr == NULL){
        return((_mqx_int)MQX_OUT_OF_MEMORY);
    }
#endif   
   
   for ( i = 0; i < erase_array_size; i++ ) {
      erase_ptr[i] = MAX_MQX_UINT;
   } /* Endfor */
   
   handle_ptr->ERASE_ARRAY_SIZE = erase_array_size;
   handle_ptr->ERASE_ARRAY      = erase_ptr;
   
   _mem_set_type(handle_ptr->ERASE_ARRAY,MEM_TYPE_IO_FLASHX_SECTOR_MAP);    
   
   handle_ptr->COUNT++;   
      
   return MQX_OK;  

} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_close
* Returned Value   : MQX_OK
* Comments         : Closes flash driver
* 
*END*----------------------------------------------------------------------*/

_mqx_int _io_flashx_close
   (
      /* [IN] the file handle for the device being closed */
      MQX_FILE_PTR fd_ptr
   )
{ /* Body */
   IO_DEVICE_STRUCT_PTR io_dev_ptr = fd_ptr->DEV_PTR;
   IO_FLASHX_STRUCT_PTR handle_ptr = 
      (IO_FLASHX_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
   
   if (--handle_ptr->COUNT == 0) {
      if (handle_ptr->FLAGS & FLASHX_FLASH_BUFFER_ENABLED) {
         _io_flashx_flush_buffer(handle_ptr);
      } /* Endif */
      
      if (handle_ptr->DEINIT) {
         (*handle_ptr->DEINIT)(handle_ptr);
      } /* Endif */

      _mem_free((pointer)handle_ptr->ERASE_ARRAY);
      
      if( handle_ptr->TEMP_PTR ){
        _mem_free(handle_ptr->TEMP_PTR);
        handle_ptr->TEMP_PTR = NULL;
      }
          
   } /* Endif */

   return MQX_OK;  
   
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _allocate_sector_cache
* Returned Value   : True, False
* Comments         : Allocate the flash sector cache
* 
*END*----------------------------------------------------------------------*/
boolean _allocate_sector_cache( IO_FLASHX_STRUCT_PTR handle_ptr ) 
{
    /* test for sector cache enable */
    if( !(handle_ptr->FLAGS & FLASHX_SECTOR_CACHE_ENABLED) )
        return ( FALSE );
    
    if( handle_ptr->TEMP_PTR == NULL ){
        handle_ptr->TEMP_PTR  = _mem_alloc_system(handle_ptr->MAX_SECT_SIZE);
        /* test for memory allocation */
        if(handle_ptr->TEMP_PTR == NULL)
            return (FALSE);
        _mem_set_type(handle_ptr->TEMP_PTR,MEM_TYPE_IO_FLASHX_SECTOR_CACHE);    
    }
    return ( TRUE );
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_read
* Returned Value   : number of characters read
* Comments         : Reads data from flash driver
* 
*END*----------------------------------------------------------------------*/

_mqx_int _io_flashx_read
   (
      /* [IN] the file handle for the device */
      MQX_FILE_PTR fd_ptr,
   
      /* [IN] where the characters are to be stored */
      char_ptr   data_ptr,
   
      /* [IN] the number of characters to input */
      _mqx_int num
   )
{ /* Body */
   IO_DEVICE_STRUCT_PTR io_dev_ptr = fd_ptr->DEV_PTR;
   IO_FLASHX_STRUCT_PTR handle_ptr  = 
      (IO_FLASHX_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
   uchar_ptr            src_ptr;
     
   _lwsem_wait(&handle_ptr->LWSEM);
                             
   if ( fd_ptr->LOCATION >= handle_ptr->TOTAL_SIZE ) {
      fd_ptr->ERROR = IO_ERROR_READ_ACCESS;
      _lwsem_post(&handle_ptr->LWSEM);
      return IO_ERROR;
   } /* Endif */
  
   if (handle_ptr->FLAGS & FLASHX_FLASH_BUFFER_ENABLED) {
      _io_flashx_flush_buffer(handle_ptr);
   }/* Endif */     
   
   if ( (num + fd_ptr->LOCATION) > handle_ptr->TOTAL_SIZE ) {
      fd_ptr->ERROR = IO_ERROR_READ_ACCESS;
      num = (_mqx_int)(handle_ptr->TOTAL_SIZE - fd_ptr->LOCATION + 1);
   } /* Endif */
   
   src_ptr = handle_ptr->BASE_ADDR + fd_ptr->LOCATION;
   _mem_copy((pointer)src_ptr, (pointer)data_ptr, (_mem_size)num);
   fd_ptr->LOCATION += num;
   _lwsem_post(&handle_ptr->LWSEM);

   return num;
      
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_erase_sector
* Returned Value   : boolean, TRUE upon success
* Comments         : Although it seems counter-intuitive, we actually set the 
*                    DIRTY DATA bit here, or leave it set if it was set 
*                    previously.  This is to reduce code size. This function
*                    is only called before a write occurs, so the sector will
*                    be dirty again after the write finishes.
* 
*END*----------------------------------------------------------------------*/

boolean _io_flashx_erase_sector
   (
      /* [IN] The device handle */
      IO_FLASHX_STRUCT_PTR  handle_ptr,
   
      /* Absolute sector number */
      _mqx_uint             absolute_sector_num,
   
      /* [IN] The block of sectors to write to */
      _mqx_uint             block_number,
   
      /* [IN] The sector number within the block */
      _mqx_uint             sector_number
   )
{ /* Body */
   _mqx_uint  array_offset;
   _mqx_uint  erase_mask;
   boolean    result = TRUE;
   uchar_ptr  dest_ptr;
   
   array_offset = absolute_sector_num / MQX_INT_SIZE_IN_BITS;
   erase_mask = 0x1 << (absolute_sector_num % MQX_INT_SIZE_IN_BITS); 
   
   if (handle_ptr->ERASE_ARRAY[array_offset] & erase_mask) {
      dest_ptr = handle_ptr->BASE_ADDR + 
         (_mem_size)handle_ptr->BLOCK_INFO_PTR[block_number].START_ADDR + 
         (handle_ptr->BLOCK_INFO_PTR[block_number].SECT_SIZE * sector_number);
      if (handle_ptr->SECTOR_ERASE) {
         result = (*handle_ptr->SECTOR_ERASE)(handle_ptr, dest_ptr, 
            handle_ptr->BLOCK_INFO_PTR[block_number].SECT_SIZE);
      } /* Endif */   
      
   } else  {
      /*
      ** We are setting the dirty sector bit right after we have erased the 
      ** sector in order to keep the code size down.  This function is only 
      ** called right before we call the program function, so the sector will 
      ** no longer be clean when the write function exits.  
      */
      handle_ptr->ERASE_ARRAY[array_offset] |= erase_mask;
   }/* Endif */ 
   
   return  result;

} /* Endbody */  


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_find_correct_sectors
* Returned Value   : void
* Comments         : Sets the start and end block, start and end sectors 
*                    relative to these blocks, and sets the absolute start 
*                    sector.
* 
*END*----------------------------------------------------------------------*/

void _io_flashx_find_correct_sectors
   (
      /* [IN] The device handle */
      IO_FLASHX_STRUCT_PTR handle_ptr,
   
      /* [IN] The location within the device we want to set our variables to */
      _mqx_int           location,
   
      /* [IN] The size of the potential write */
      _mem_size            size, 
   
      /* [IN/OUT] The start block for the write */
      _mqx_uint _PTR_      start_block_ptr, 
   
      /* [IN/OUT] The start sector, offset from the start block */
      _mqx_uint _PTR_      start_sector_ptr,
   
      /* [IN/OUT] The end block for the write */
      _mqx_uint _PTR_      end_block_ptr,
   
      /* [IN/OUT] The end sector, offset from the end block */
      _mqx_uint _PTR_      end_sector_ptr,
   
      /* [IN/OUT] The absolute sector number from the start of the device */ 
      _mqx_uint _PTR_      absolute_sector_num_ptr
   )
{  /* Body */
   _mqx_uint i, j;
   uchar_ptr current_loc = NULL;
   boolean   start_set   = FALSE;
        
   *absolute_sector_num_ptr = 0;
   for ( i = 0; i < handle_ptr->BLOCK_GROUPS; i++ ) { 
      for ( j = 0; j < handle_ptr->BLOCK_INFO_PTR[i].NUM_SECTORS; j++) {
         if ( !start_set ) {
            (*absolute_sector_num_ptr)++;
         }/* Endif */
         current_loc += handle_ptr->BLOCK_INFO_PTR[i].SECT_SIZE;
         if ((current_loc > (uchar_ptr)location) && !start_set ) {
            (*absolute_sector_num_ptr)--;
            *start_block_ptr = i;
            *start_sector_ptr = j;
            start_set = TRUE;
            if ( !size ) {
               *end_block_ptr = i;
               *end_sector_ptr = j;
               return;
            }/* Endif */
         }/* Endif */
         if ( current_loc > (uchar_ptr)(location + size - 1) && size > 0 ) {
            *end_block_ptr = i;
            *end_sector_ptr = j;
            return;
         }/* Endif */
      } /* Endfor */
   } /* Endfor */
   /* This is in case num ends on the last byte and end_sector isn't set */ 
   *end_block_ptr  = i - 1;
   *end_sector_ptr = j - 1;
   
} /* Endbody */    


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_flush_buffer
* Returned Value   : number of characters written
* Comments         : Flushes the flash buffer. This is used only privately 
*                    within the flashx.c file.  If it is used, there MUST be
*                    a prior check that DIRTY_DATA is true before this function
*                    is called.
* 
*END*----------------------------------------------------------------------*/

_mqx_int _io_flashx_flush_buffer 
   (
      /* [IN] The device handle */
      IO_FLASHX_STRUCT_PTR handle_ptr
   ) 
{ /* Body */
    _mqx_uint  start_block, end_block, start_sector, end_sector, absolute_sector;
    _mqx_int   dest_ptr, error = MQX_OK;
   
    /* If the Ram cache is disabled, return error */
    if (!(handle_ptr->FLAGS & FLASHX_SECTOR_CACHE_ENABLED) )
        return IO_ERROR;    
   
    if (handle_ptr->DIRTY_DATA) {
        start_block  = handle_ptr->CURRENT_BLOCK;
        start_sector = handle_ptr->CURRENT_SECTOR;

        dest_ptr = (_mqx_int)(handle_ptr->BLOCK_INFO_PTR[start_block].START_ADDR
         + (handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE * start_sector));    

        _io_flashx_find_correct_sectors(handle_ptr, dest_ptr, 0, &start_block, 
         &start_sector, &end_block, &end_sector, &absolute_sector);

        if (!_io_flashx_erase_sector(handle_ptr, absolute_sector, start_block, 
         start_sector)) 
        {
            return(IO_ERROR);
        }/* Endif */

        dest_ptr += (_mqx_int)handle_ptr->BASE_ADDR;
        
        /* allocate sector cache */
        if ( !(_allocate_sector_cache(handle_ptr)) )
            return IO_ERROR;
        
        if ( (*handle_ptr->SECTOR_PROGRAM)(handle_ptr, handle_ptr->TEMP_PTR, 
            (uchar_ptr)dest_ptr, 
            handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE)) 
        {
            error = handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE;
        } else {
            error = IO_ERROR;
        } /* Endif */
        handle_ptr->DIRTY_DATA = FALSE;
    } /* Endif */

   return error;
   
} /* Endbody */

 
/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_write
* Returned Value   : number of characters written
* Comments         : Writes data to the flash device
* 
*END*----------------------------------------------------------------------*/

_mqx_int _io_flashx_write
   (
      /* [IN] the file handle for the device */
      MQX_FILE_PTR fd_ptr,
   
      /* [IN] where the characters are */
      char_ptr   data_ptr,
   
      /* [IN] the number of characters to output */
      _mqx_int num
   )
{ /* Body */
   IO_DEVICE_STRUCT_PTR  io_dev_ptr = fd_ptr->DEV_PTR;
   IO_FLASHX_STRUCT_PTR  handle_ptr = 
      (IO_FLASHX_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
   uchar_ptr             dest_ptr, src_ptr;
   _mem_size             results, temp_num, size, offset, remains;
   _mqx_uint             start_sector, end_sector, start_block;
   _mqx_uint             sector_num, end_block;

   _lwsem_wait(&handle_ptr->LWSEM);

   /* Is the start possition in space ? */  
   if ( fd_ptr->LOCATION >= handle_ptr->TOTAL_SIZE ) {
      fd_ptr->ERROR = IO_ERROR_WRITE_ACCESS;
      _lwsem_post(&handle_ptr->LWSEM);
      return IO_ERROR;
   } /* Endif */
   
   /* Is the end possition in space? */
   if ( (num + fd_ptr->LOCATION) > handle_ptr->TOTAL_SIZE ) {
       fd_ptr->ERROR = IO_ERROR_WRITE_ACCESS;
       num = (_mqx_int)(handle_ptr->TOTAL_SIZE - fd_ptr->LOCATION + 1);
   } /* Endif */
   
   /* Set the start block, end block, start sector, end sector pointer */
   temp_num = (_mem_size)num;
   _io_flashx_find_correct_sectors(handle_ptr, fd_ptr->LOCATION, temp_num, 
      &start_block, &start_sector, &end_block, &end_sector, &sector_num);
                         
   
   src_ptr  = (uchar_ptr)data_ptr;
      
   /*
   ** We have four conditions:
   **   1. The write is contained in one flash sector
   **   2. The write is contained in two adjacent flash sectors
   **   3. The write spans many flash sectors within a single block 
   **   4. The write spans many blocks  
   **
   ** In case 1, it is possible to have a partial flash sector. 
   ** In case 2, it is possible that both the end and the start are only 
   **  partial flash sectors.
   ** In case 3(really a subset of case 2), the start and end may be partial
   **  but the others will all be complete flash sectors.
   ** In case 4, (subset of case 3) the start and end may be partial, but
   **  the others will complete sectors within a block
   */
      
   offset = fd_ptr->LOCATION - 
      (handle_ptr->BLOCK_INFO_PTR[start_block].START_ADDR + 
      (handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE * start_sector));
   
   /* if we write not at start sector */      
   if ( offset > 0 ) {
      remains = 
         handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE - 
         offset;
      if ( remains > temp_num ) {
         remains = temp_num;
      } /* Endif */
      results = _io_flashx_write_partial_sector(fd_ptr, start_block, 
         start_sector, offset, remains, sector_num, src_ptr);
      if ((_mqx_int)results == IO_ERROR ) {
         fd_ptr->ERROR = IO_ERROR_WRITE;
         _lwsem_post(&handle_ptr->LWSEM);
         return ((_mqx_int)results);
      } /* Endif */
      
      /* mark the sector need erase before another write */
      /* handle_ptr->ERASE_ARRAY[array_offset] |= erase_mask */
      handle_ptr->ERASE_ARRAY[sector_num/MQX_INT_SIZE_IN_BITS] |= 
        (0x1 << (sector_num % MQX_INT_SIZE_IN_BITS));
      fd_ptr->LOCATION += results;
      src_ptr           = (uchar_ptr)data_ptr + results;
      temp_num         -= results;
      sector_num++;
      start_sector++;
   }/* Endif */
     
   while ( start_block < end_block ) {
      size = handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE;
             
      while ( start_sector < 
              handle_ptr->BLOCK_INFO_PTR[start_block].NUM_SECTORS ) 
      {
         if ((handle_ptr->FLAGS & FLASHX_FLASH_BUFFER_ENABLED) &&
             (handle_ptr->CURRENT_BLOCK == start_block) && 
             (handle_ptr->CURRENT_SECTOR == start_sector)) 
         {
            handle_ptr->DIRTY_DATA = FALSE;   
         }/* Endif */
                    
         dest_ptr = handle_ptr->BLOCK_INFO_PTR[start_block].START_ADDR + 
            (handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE * 
            start_sector) + handle_ptr->BASE_ADDR;
            
         _io_flashx_erase_sector(handle_ptr, sector_num, start_block, 
            start_sector);
         /* 
         ** We are calling the write function for the specific chip here.
         ** This writes a single full sector.
         */
         if((*handle_ptr->SECTOR_PROGRAM)(handle_ptr, src_ptr, dest_ptr, size)){
            /* mark the sector need erase before another write */
            /* handle_ptr->ERASE_ARRAY[array_offset] |= erase_mask */
            handle_ptr->ERASE_ARRAY[sector_num/MQX_INT_SIZE_IN_BITS] |= 
                (0x1 << (sector_num % MQX_INT_SIZE_IN_BITS));
            fd_ptr->LOCATION += size;
            src_ptr += size;
            temp_num -= size;
            sector_num++;
            start_sector++;
         } else {
            fd_ptr->ERROR = IO_ERROR_WRITE;
            _lwsem_post(&handle_ptr->LWSEM);
            return(IO_ERROR);
         }/* Endif */
      } /* Endwhile */
      start_block++;
      start_sector = 0;
   } /* Endwhile */
      
   size = handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE;
   while ( start_sector < end_sector ) {
      /* Write the remaining flash sectors of the last block (if any) */
      if ((handle_ptr->FLAGS & FLASHX_FLASH_BUFFER_ENABLED) &&
          (handle_ptr->CURRENT_BLOCK == start_block) && 
          (handle_ptr->CURRENT_SECTOR == start_sector)) 
      {
         handle_ptr->DIRTY_DATA = FALSE;   
      } /* Endif */

      dest_ptr = handle_ptr->BLOCK_INFO_PTR[start_block].START_ADDR +
         (handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE * 
         start_sector) + handle_ptr->BASE_ADDR;
          
      _io_flashx_erase_sector(handle_ptr, sector_num, start_block, 
         start_sector);
      /* 
      ** We are calling the write function for the specific chip here.
      ** This writes a single full sector.
      */
      if ( (*handle_ptr->SECTOR_PROGRAM)(handle_ptr, src_ptr, dest_ptr, size) ){
         /* mark the sector need erase before another write */
         /* handle_ptr->ERASE_ARRAY[array_offset] |= erase_mask */
         handle_ptr->ERASE_ARRAY[sector_num/MQX_INT_SIZE_IN_BITS] |= 
            (0x1 << (sector_num % MQX_INT_SIZE_IN_BITS));
         fd_ptr->LOCATION += size;
         src_ptr += size;
         temp_num -= size;
         sector_num++;
         start_sector++;
      } else {
         fd_ptr->ERROR = IO_ERROR_WRITE;
         _lwsem_post(&handle_ptr->LWSEM);
         return(IO_ERROR);
      }/* Endif */
   } /* Endwhile */
  
   if ( start_sector == end_sector ) {
      /* Write the last flash sector */
      remains = temp_num;
      results  = _io_flashx_write_partial_sector(fd_ptr, end_block, end_sector, 
                 0, remains, sector_num, src_ptr);
      if ((int_32)results == IO_ERROR )  {
         fd_ptr->ERROR = IO_ERROR_WRITE;
         _lwsem_post(&handle_ptr->LWSEM);
         return results;
      } else {
         /* mark the sector need erase before another write */
         /* handle_ptr->ERASE_ARRAY[array_offset] |= erase_mask */
         handle_ptr->ERASE_ARRAY[sector_num/MQX_INT_SIZE_IN_BITS] |= 
            (0x1 << (sector_num % MQX_INT_SIZE_IN_BITS));
         fd_ptr->LOCATION += results;
      } /* Endif */
   } /* Endif */
   
   _lwsem_post(&handle_ptr->LWSEM);
   return(num);

} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_write_partial_sector
* Returned Value   : _mem_size - number of bytes written if successfully,
*                    0 otherwise
* Comments         : Writes a partial flash sector while preserving contents of
*                    unused portions of the sector
* 
*END*----------------------------------------------------------------------*/
_mem_size _io_flashx_write_partial_sector
   (
       /* [IN] the file handle for the device */
      MQX_FILE_PTR fd_ptr,
   
      /* [IN] The block of sectors to write to */
      _mqx_uint  block_number,
   
      /* [IN] The sector number within the block */
      _mqx_uint  sector_number,
   
      /* [IN] The start offset within the sector */
      _mem_size  offset_in_sector,
   
      /* [IN] The number of bytes to write */
      _mem_size  bytes_to_write,
   
      /* [IN] The actual sector we are writing to */
      _mqx_uint  absolute_sector_number,
   
      /* [IN] The data to write */
      uchar_ptr  src_ptr
   )
{ /* Body */
   IO_DEVICE_STRUCT_PTR  io_dev_ptr = fd_ptr->DEV_PTR;
   IO_FLASHX_STRUCT_PTR  handle_ptr  = 
      (IO_FLASHX_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
   _mem_size             sector_size;
   uchar_ptr             sector_dest_ptr;
   uchar_ptr             data_dest_ptr;
   _mem_size             num_data_before_write;
   _mem_size             num_data_after_write;  
   
   /* Get the sector size */
   sector_size = handle_ptr->BLOCK_INFO_PTR[block_number].SECT_SIZE;
   /* Get the pointer to sector start */
   sector_dest_ptr = handle_ptr->BASE_ADDR + 
      handle_ptr->BLOCK_INFO_PTR[block_number].START_ADDR + 
      (handle_ptr->BLOCK_INFO_PTR[block_number].SECT_SIZE *
      sector_number);
   /* Get the pointer to start data write */ 
   data_dest_ptr = sector_dest_ptr + offset_in_sector;     

   if ((handle_ptr->FLAGS & FLASHX_FLASH_BUFFER_ENABLED) && 
       (handle_ptr->FLAGS & FLASHX_SECTOR_CACHE_ENABLED) ) {  
      
      /* allocate sector cache */
      if ( !(_allocate_sector_cache(handle_ptr)) )
        return (_mem_size)IO_ERROR; 
      
      if (handle_ptr->DIRTY_DATA) {
         if (handle_ptr->CURRENT_BLOCK != block_number || 
             handle_ptr->CURRENT_SECTOR != sector_number) 
         {
            _io_flashx_flush_buffer(handle_ptr);
            /* Read the sector to do the partial write into ram */
            _mem_copy((pointer)sector_dest_ptr, handle_ptr->TEMP_PTR, sector_size);
         } /* Endif */
      } else  {
         _mem_copy((pointer)sector_dest_ptr, handle_ptr->TEMP_PTR, sector_size); 
      } /* Endif */
 
      /* 
      ** Please don't move the following two assignments. 
      ** We need to initialize these on the very first write, not on 
      ** initialization. 
      */
      handle_ptr->CURRENT_BLOCK  = block_number;
      handle_ptr->CURRENT_SECTOR = sector_number;
      /* Write new data into ram copy sector */
      _mem_copy((pointer)src_ptr, (pointer)((uchar_ptr)handle_ptr->TEMP_PTR + 
         offset_in_sector), bytes_to_write);
      handle_ptr->DIRTY_DATA = TRUE;
      return(bytes_to_write);
   } /* Endif */


      
    /* Is the write area erased? */ 
    if(!_io_flashx_check_free_space( data_dest_ptr, bytes_to_write ) ) {
        /* Yes, write data */
        if ((*handle_ptr->SECTOR_PROGRAM)(handle_ptr, src_ptr, data_dest_ptr, bytes_to_write)) 
        {
            /* Return remains space in sector */
            return bytes_to_write;
        } else {
            return (_mem_size)IO_ERROR;
        } /* Endif */           
    }
        
    /* Are data before write area ? */
    num_data_before_write = _io_flashx_check_free_space( sector_dest_ptr, 
        offset_in_sector ); 
    /* Are some data behind new data? */
    num_data_after_write = _io_flashx_check_free_space( data_dest_ptr + bytes_to_write, 
        sector_size - offset_in_sector - bytes_to_write );

    /* If we have some data to store, we copy data to ram */
    if( num_data_before_write || num_data_after_write )
    {
        /* If the dynamic memory alocation disabled, return error */
        if( !(handle_ptr->FLAGS & FLASHX_SECTOR_CACHE_ENABLED ) )
            return (_mem_size)IO_ERROR;
        
        /* allocate sector cache */
        if ( !(_allocate_sector_cache(handle_ptr)) )
            return (_mem_size)IO_ERROR;
        
        /* Read the sector to do the partial write into ram */
        _mem_copy((pointer)sector_dest_ptr, handle_ptr->TEMP_PTR, sector_size);
        /* Write new data into ram copy sector */
        _mem_copy((pointer)src_ptr, (pointer)((uchar_ptr)handle_ptr->TEMP_PTR + 
          offset_in_sector), bytes_to_write);
        /* erase sector */
        _io_flashx_erase_sector(handle_ptr, absolute_sector_number, block_number, 
          sector_number);
        /* Write the newly modified ram sector back into flash */
        if ((*handle_ptr->SECTOR_PROGRAM)(handle_ptr, handle_ptr->TEMP_PTR, sector_dest_ptr, sector_size)) 
        {
          return bytes_to_write;
        } else {
          return (_mem_size)IO_ERROR;
        } /* Endif */
    }
    /* Otherwise we do not need to store old data, we only erase sector and write 
       new data */
    else
    {
        _io_flashx_erase_sector(handle_ptr, absolute_sector_number, block_number, 
          sector_number);
        if ((*handle_ptr->SECTOR_PROGRAM)(handle_ptr, src_ptr, data_dest_ptr, bytes_to_write)) 
        {
            /* Return remains space in sector */
            return bytes_to_write;
        } else {
            return (_mem_size)IO_ERROR;
        } /* Endif */       
    }
}


/*FUNCTION*****************************************************************
*
* Function Name    : _io_flashx_check_free_space
* Returned Value   : _mem_size
* Comments         :
*    Return position of last used byte in tested area.
*
*END*********************************************************************/
_mem_size _io_flashx_check_free_space(
    /* [IN] source pointer */
    uchar_ptr   src_ptr,
    /* [IN] number of bytes to check */
    _mem_size   num_bytes_to_check
)
{
    #define BLANK_MEM 0xFF
    uint_32 used_mem_position;
    
    /* Is the write area erased ? */
    for(used_mem_position = num_bytes_to_check; 
        used_mem_position>0; used_mem_position--)
    {
        if(*(src_ptr + used_mem_position-1) != BLANK_MEM)
            /* return last non-free byte possition */
            return(used_mem_position);    
    }
    /* space is free */
    return 0;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _io_flashx_ioctl
* Returned Value   : int_32
* Comments         :
*    Returns result of ioctl operation.
*
*END*********************************************************************/

_mqx_int _io_flashx_ioctl
   (
      /* [IN] the file handle for the device */
      MQX_FILE_PTR fd_ptr,
   
      /* [IN] the ioctl command */
      _mqx_uint  cmd,
   
      /* [IN/OUT] the ioctl parameters */
      pointer    param_ptr
   )
{ /* Body */
   IO_DEVICE_STRUCT_PTR               io_dev_ptr = fd_ptr->DEV_PTR;
   IO_FLASHX_STRUCT_PTR               handle_ptr = 
      (IO_FLASHX_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
   _mqx_int                           result = MQX_OK;
   _mqx_uint                          erase_mask;
   _mqx_uint                          i, j;
   _mqx_uint                          array_offset;
   _mqx_uint                          char_offset;
   _mqx_uint                          start_block, start_sector;
   _mqx_uint                          end_block, end_sector;
   _mqx_uint                          sector_num;
   _mqx_uint                          current_val = 0;
   uchar_ptr                          temp_ptr;
   pointer _PTR_                      pparam_ptr;
   _mqx_uint_ptr                      uparam_ptr;
   _mem_size_ptr                      mparam_ptr;
   FLASHX_BLOCK_INFO_STRUCT_PTR _PTR_ fparam_ptr;
   uint_32                            total_size;   
   
   switch (cmd) {
      case FLASH_IOCTL_GET_BASE_ADDRESS:
         pparam_ptr = (pointer _PTR_)param_ptr;
         *pparam_ptr = (pointer)handle_ptr->BASE_ADDR;
         break;

      case FLASH_IOCTL_GET_BLOCK_GROUPS:
         uparam_ptr = (_mqx_uint_ptr)param_ptr;
         *uparam_ptr = handle_ptr->BLOCK_GROUPS;
         break;   

      case IO_IOCTL_GET_NUM_SECTORS:
         /* get the num sectors for MFS device */
         total_size = 0;
         /* get total size */
         for ( i = 0; i < handle_ptr->BLOCK_GROUPS; i++ ) {
             total_size += (handle_ptr->BLOCK_INFO_PTR[i].SECT_SIZE * handle_ptr->BLOCK_INFO_PTR[i].NUM_SECTORS);
         } /* Endfor */      
         *(uint_32_ptr)param_ptr = total_size / MFS_SECTOR_SIZE;
         break;
      case FLASH_IOCTL_GET_NUM_SECTORS:
         for ( i = 0; i < handle_ptr->BLOCK_GROUPS; i++ ) {
            current_val += handle_ptr->BLOCK_INFO_PTR[i].NUM_SECTORS;
         } /* Endfor */
         uparam_ptr = (_mqx_uint_ptr)param_ptr;
         *uparam_ptr = current_val;
         break;

      case FLASH_IOCTL_GET_WIDTH: 
         uparam_ptr = (_mqx_uint_ptr)param_ptr;
         *uparam_ptr = handle_ptr->WIDTH;
         break;

      case IO_IOCTL_DEVICE_IDENTIFY:
         /* 
         ** This is to let the upper layer know what kind of device this is.
         ** It's a physical flash device, capable of being erased, read, seeked, 
         ** and written. Flash devices are not interrupt driven, so 
         ** IO_DEV_ATTR_POLL is included.
         */   
         uparam_ptr = (_mqx_uint_ptr)param_ptr;
         uparam_ptr[0] = IO_DEV_TYPE_PHYS_FLASHX;
         uparam_ptr[1] = IO_DEV_TYPE_LOGICAL_MFS;
         uparam_ptr[2] = IO_DEV_ATTR_ERASE | IO_DEV_ATTR_POLL
                          | IO_DEV_ATTR_READ | IO_DEV_ATTR_SEEK | 
                          IO_DEV_ATTR_WRITE;
         break; 
 
      case IO_IOCTL_GET_BLOCK_SIZE:
         /* returns the fixed size for MFS sector size */
         *(uint_32_ptr)param_ptr = MFS_SECTOR_SIZE;
         break;
    
      case FLASH_IOCTL_GET_SECTOR_SIZE:       
         /* 
         ** This returns the size of the sector after a user does an 
         ** fseek to the location he/she wants to know the sector size of.
         */
         _io_flashx_find_correct_sectors(handle_ptr, fd_ptr->LOCATION, 0, 
            &start_block, &start_sector, &end_block, &end_sector, &sector_num);
         mparam_ptr = (_mem_size_ptr)param_ptr;
         *mparam_ptr = handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE;
         break;

      case FLASH_IOCTL_GET_SECTOR_BASE:
         /* 
         ** This returns the start address of the sector after a user does an 
         ** fseek to the sector he/she wants know the start of.
         */
         _io_flashx_find_correct_sectors(handle_ptr, fd_ptr->LOCATION, 0, 
            &start_block, &start_sector, &end_block, &end_sector, &sector_num);
         mparam_ptr = (_mem_size_ptr)param_ptr;
         *mparam_ptr = handle_ptr->BLOCK_INFO_PTR[start_block].START_ADDR +
            (handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE *           
            start_sector);
         break;

      case FLASH_IOCTL_GET_BLOCK_MAP:
         fparam_ptr = (FLASHX_BLOCK_INFO_STRUCT_PTR _PTR_)param_ptr;  
         *fparam_ptr = handle_ptr->BLOCK_INFO_PTR;
         break;

      case  FLASH_IOCTL_FLUSH_BUFFER: 
         result = _io_flashx_flush_buffer( handle_ptr );
         if (result != IO_ERROR) {
            result = MQX_OK;
         } /* Endif */
         break;   
 
      case FLASH_IOCTL_ENABLE_BUFFERING:
         /* if RAM cache is enabled, enable buffer */
         if(handle_ptr->FLAGS & FLASHX_SECTOR_CACHE_ENABLED)
         {
            handle_ptr->FLAGS |= FLASHX_FLASH_BUFFER_ENABLED;
            result = MQX_OK;
         }
         /* else return error */
         else
            result = IO_ERROR;          
         break;          

      case FLASH_IOCTL_DISABLE_BUFFERING: 
         result = _io_flashx_flush_buffer(handle_ptr);
         if (result != IO_ERROR) {
            result = MQX_OK;
         } /* Endif */
         handle_ptr->FLAGS &= ~FLASHX_FLASH_BUFFER_ENABLED;
         break;   

      case FLASH_IOCTL_ENABLE_SECTOR_CACHE:
         /* Set ram cache flag */
         handle_ptr->FLAGS |= FLASHX_SECTOR_CACHE_ENABLED;
         break; 

      case FLASH_IOCTL_DISABLE_SECTOR_CACHE:
         /* Disable buffering first */
         if(handle_ptr->FLAGS & FLASHX_FLASH_BUFFER_ENABLED){
            result = _io_flashx_flush_buffer(handle_ptr);
            if (result != IO_ERROR) {
                result = MQX_OK;
            } /* Endif */
            handle_ptr->FLAGS &= ~FLASHX_FLASH_BUFFER_ENABLED;
         }
         /* clear ram cache flag */
         handle_ptr->FLAGS &= ~FLASHX_SECTOR_CACHE_ENABLED;              
         break; 

      case FLASH_IOCTL_ERASE_SECTOR:
         /* 
         ** This erases the sector after a user does an 
         ** fseek to the location of the sector he/she wants to erase.
         */
         if (!handle_ptr->SECTOR_ERASE) {
            result = IO_ERROR_INVALID_IOCTL_CMD;
            break;
         } /* Endif */   
         _io_flashx_find_correct_sectors(handle_ptr, fd_ptr->LOCATION, 0, 
            &start_block, &start_sector, &end_block, &end_sector, &sector_num);
         temp_ptr = handle_ptr->BLOCK_INFO_PTR[start_block].START_ADDR +
            (handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE *           
            start_sector) + handle_ptr->BASE_ADDR;

         if ((*handle_ptr->SECTOR_ERASE)(handle_ptr, temp_ptr,
            handle_ptr->BLOCK_INFO_PTR[start_block].SECT_SIZE)) {
            array_offset = sector_num/MQX_INT_SIZE_IN_BITS;
            char_offset  = sector_num % MQX_INT_SIZE_IN_BITS;
            erase_mask = 0x1 << char_offset; 
            handle_ptr->ERASE_ARRAY[array_offset] &= ~erase_mask;
         }/* Endif */
         if ((start_block == handle_ptr->CURRENT_BLOCK) && (start_sector == 
            handle_ptr->CURRENT_SECTOR))
         {
            handle_ptr->DIRTY_DATA = FALSE;
         }/* Endif */
         break;

      case FLASH_IOCTL_ERASE_CHIP: 
         if (handle_ptr->CHIP_ERASE) {
            if ((*handle_ptr->CHIP_ERASE)(handle_ptr))
               result = MQX_OK;
            else {
               result = IO_ERROR;
               break;
            } /* Endif */
         } else if (!handle_ptr->SECTOR_ERASE) {
            result = IO_ERROR_INVALID_IOCTL_CMD;
            break;
         } else { 
            temp_ptr = handle_ptr->BASE_ADDR;
            for (i = 0; i < handle_ptr->BLOCK_GROUPS; i++) {
               for (j = 0; j < handle_ptr->BLOCK_INFO_PTR[i].NUM_SECTORS; j++){          
                  if((*handle_ptr->SECTOR_ERASE)(handle_ptr, 
                     temp_ptr, handle_ptr->BLOCK_INFO_PTR[i].SECT_SIZE))
                     result = MQX_OK;
                  else {
                     result = IO_ERROR;
                     break;
                  } /* Endif */
                  temp_ptr += handle_ptr->BLOCK_INFO_PTR[i].SECT_SIZE;      
               } /* Endfor */
            } /* Endfor */
         }/* Endif */
         
         for (i = 0; i < handle_ptr->ERASE_ARRAY_SIZE; i++) {
            handle_ptr->ERASE_ARRAY[i] = 0x0;
         } /* Endfor */
         handle_ptr->DIRTY_DATA = FALSE;
         break;
      
      case FLASH_IOCTL_WRITE_PROTECT:
         if (handle_ptr->WRITE_PROTECT != NULL)
         {
            result = (*handle_ptr->WRITE_PROTECT)(handle_ptr, *(_mqx_uint_ptr)param_ptr);
         }
         break; 
      
      default:
         if(handle_ptr->IOCTL != NULL){
            result = (*handle_ptr->IOCTL)(handle_ptr, cmd, param_ptr);
         }
         else {
            result = IO_ERROR_INVALID_IOCTL_CMD;    
         }         
         break;
   } /* Endswitch */
   return result;

} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_flashx_wait_us
* Returned Value   : none
* Comments         : 
*    This function waits at least the given amount of us, but it is possible
*    to wait longer
* 
*END*----------------------------------------------------------------------*/

void _io_flashx_wait_us
   (
      /* [IN] the time to spin wait for */
      _mqx_int wait_us
   ) 
{/* Body */
   _mqx_int total_us = 0;
   _mqx_int start_us;
   _mqx_int end_us;
     
   start_us = (int_32) _time_get_microseconds();
   while (total_us < wait_us) {
      end_us = (int_32) _time_get_microseconds();
      if (end_us > start_us) {
         total_us += (end_us - start_us);
      } /* Endif */
      start_us = end_us;
   } /* Endwhile */

} /* Endbody */

/* EOF */

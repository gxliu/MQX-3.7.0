/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: flash_demo.c$
* $Version : 3.7.22.0$
* $Date    : Mar-23-2011$
*
* Comments:
*
*   This file contains the source for the hello example program.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include <string.h>


#if BSP_M5329EVB || BSP_M53015EVB || BSP_M52277EVB ||BSP_M5208EVB
    #if ! BSPCFG_ENABLE_EXT_FLASH
    #error This application requires BSPCFG_ENABLE_EXT_FLASHX defined non-zero in user_config.h. Please recompile BSP with this option.
    #endif
    /* external flash name */
    #define         FLASH_NAME "flash:"
    #define         WRITE_PROTECT_TEST 1
#elif BSP_M54455EVB
    #if ! BSPCFG_ENABLE_EXT_FLASH1
    #error This application requires BSPCFG_ENABLE_EXT_FLASH1 defined non-zero in user_config.h. Please recompile BSP with this option.
    #endif
    /* external flash name */
    #define         FLASH_NAME "flash1:"
    #define         WRITE_PROTECT_TEST 1
#elif BSP_M51EMDEMO
    /* external flash name */
    #define         FLASH_NAME "flashx1:"
    #define         WRITE_PROTECT_TEST 0
#else
    #if ! BSPCFG_ENABLE_FLASHX
    #error This application requires BSPCFG_ENABLE_FLASHX defined non-zero in user_config.h. Please recompile BSP with this option.
    #endif
    /* internal flash name */
    #define         FLASH_NAME "flashx:"
    #define         WRITE_PROTECT_TEST 0
#endif

/* Task IDs */
#define NILL_TASK 7

/* Set to 1 to test the entire chip */
#define FLASH_TEST_ENTIRE_CHIP   (1)
/* Set to 1 to call FLASH_IOCTL_ERASE_CHIP if chip erase function is present */
#define FLASH_TEST_ERASE_CHIP    (1)
#define NUM_LOOPS                (7)

/* function prototypes */
MQX_FILE_PTR flash_open(char_ptr name);
void flash_close(MQX_FILE_PTR flash);
uchar_ptr allocate_buffer(_mem_size buffer_size, _mqx_uint k, char_ptr string);
void size_compare( MQX_FILE_PTR flash_hdl, _mqx_int i, _mqx_int read_write_size );
void compare_test( uchar_ptr write_buffer, uchar_ptr read_buffer, _mem_size read_write_size);
void read_and_test_data(MQX_FILE_PTR flash_hdl,_mqx_int read_write_size, uchar_ptr write_buffer, uchar_ptr read_buffer, _mem_size seek_location);
extern void nill_task(uint_32);




const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{ 
   /* Task Index,   Function,   Stack,  Priority,   Name,   Attributes,          Param, Time Slice */ 
    { NILL_TASK,    nill_task,  4000,   8,          "nill", MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

/*FUNCTION*-----------------------------------------------------
* 
* Task Name    : flash_open
* Comments     :
*    Open the flash device
*
*END*-----------------------------------------------------*/
MQX_FILE_PTR flash_open(char_ptr name) 
{
    MQX_FILE_PTR flash_hdl = NULL;
    
    /* Open the flash device */
    flash_hdl = fopen(name, NULL);
    if (flash_hdl == NULL) {
        printf("\nUnable to open flash device %s", name);
        _task_block();
    } /* Endif */
    printf("\nFlash device %s opened", name);       
    return flash_hdl;
}

/*FUNCTION*-----------------------------------------------------
* 
* Task Name    : flash_close
* Comments     :
*    Close the flash device
*
*END*-----------------------------------------------------*/
void flash_close(MQX_FILE_PTR flash)
{
    fclose(flash);
    printf("\n\rFlash closed.");    
}

/*FUNCTION*-----------------------------------------------------
* 
* Task Name    : allocate_buffer
* Comments     :
*    Allocate the buffer
*
*END*-----------------------------------------------------*/
uchar_ptr allocate_buffer(_mem_size buffer_size, _mqx_uint k,
    char_ptr string) 
{
    uchar_ptr buffer_ptr;
    
    buffer_ptr = _mem_alloc_zero(buffer_size);
    if (buffer_ptr == NULL) {
        if ( k > 2 ) {
            printf("\n Insufficient memory to continue. %d loops passed.", k);
        } /* Endif */
        printf("\nFailed to get %s buffer", string);
        _task_block();
    } /* Endif */
    return buffer_ptr;          
}

/*FUNCTION*-----------------------------------------------------
* 
* Task Name    : compare_test
* Comments     :
*    function compare write_buffer and read_buffer
*
*END*-----------------------------------------------------*/
void compare_test( uchar_ptr write_buffer, uchar_ptr read_buffer, _mem_size read_write_size) 
{
    if (memcmp(write_buffer, read_buffer, read_write_size)) {
         printf("\nFailed to read back flash as written\n");
         _task_block();
    } 
    else {
        printf("\nCompare OK\n\r");
    }
}

/*FUNCTION*-----------------------------------------------------
* 
* Task Name    : size_compare
* Comments     :
*    function compare i and read_write_size
*
*END*-----------------------------------------------------*/
void size_compare( MQX_FILE_PTR flash_hdl, _mqx_int i, _mqx_int read_write_size )
{
    if (i != read_write_size ) {
        printf("\nFailed to write flash, size returned:%d expected %d", i,
        read_write_size);
        printf("\nTEC:0x%X FERROR:0x%X", _task_get_error(), ferror(flash_hdl));
        _task_block();
    } /* Endif */   
}

/*FUNCTION*-----------------------------------------------------
* 
* Task Name    : read_and_test_data
* Comments     :
*    function read data and make compare test
*
*END*-----------------------------------------------------*/
void read_and_test_data(MQX_FILE_PTR flash_hdl,_mqx_int read_write_size, 
    uchar_ptr write_buffer, uchar_ptr read_buffer, _mem_size seek_location)
{
    _mqx_int i;
    fseek(flash_hdl, seek_location, IO_SEEK_SET);
    i = read(flash_hdl, read_buffer, read_write_size);
    compare_test(write_buffer, read_buffer, read_write_size);   
}

#if WRITE_PROTECT_TEST 

/*FUNCTION*-----------------------------------------------------
* 
* Task Name    : flash_write_ptotect_test
* Comments     :
*    function lock and unlock flash for write, and write result
*
*END*-----------------------------------------------------*/
static void flash_write_ptotect_test(MQX_FILE_PTR flash_hdl)
{
    _mqx_uint      wp_stat;
    _mqx_uint_ptr  ptr_wp_stat = &wp_stat;
    _mqx_uint      error_code;
    boolean        write_protect;
    char           steps;       
   
    wp_stat = 1;
    for(steps = 1; steps < 3; steps++){
        /* lock/unlock flash for write */
        printf("Changing the write protect status to %d. (may take a while)\n", wp_stat);
        _io_ioctl(flash_hdl, FLASH_IOCTL_WRITE_PROTECT, ptr_wp_stat);
        /* get the flash write protect status */
        error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_WRITE_PROTECT, &write_protect);
        /* print the result */
        printf("Write protect status: %d\n", write_protect);
        /* change mode from write protect to write free */
        wp_stat--;
   }   
}

#endif

/*TASK*-----------------------------------------------------
* 
* Task Name    : nill_task
* Comments     :
*    This task does nothing
*
*END*-----------------------------------------------------*/
void nill_task
   (
      uint_32 initial_data
   )
{
   #define      TEST_STRUCT_SIZE 41
  
 
   FLASHX_BLOCK_INFO_STRUCT_PTR info_ptr;
   MQX_FILE_PTR   flash_hdl;
   _mqx_uint      error_code;
   _mem_size      base_addr;
   _mem_size      sector_size;
   _mqx_uint      num_sectors;
   _mqx_uint      test_val;
   _mqx_uint      num_blocks;
   _mqx_uint      width;
   _mem_size      total_size = 0;
   uchar_ptr       write_buffer;
   uchar_ptr       read_buffer;
   uchar_ptr       old_buffer;
   _mqx_int       i, test_block;
   _mqx_uint      j, k, n;
   _mem_size      seek_location;
   _mem_size      read_write_size = 0;
   _mqx_uint      ident_arr[3];
   boolean        test_completed = FALSE;      

   _int_install_unexpected_isr();

   puts("\n\nMQX Flash Test Program");
   puts("\nBeginning read/write tests");
   
   /* Open the flash device */
   flash_hdl = flash_open(FLASH_NAME);
   
    /* Enable sector cache */
   _io_ioctl(flash_hdl, FLASH_IOCTL_ENABLE_SECTOR_CACHE, NULL); 

   _io_ioctl(flash_hdl, IO_IOCTL_DEVICE_IDENTIFY, &ident_arr[0]);
   printf("\nFlash Device Identity: %#010x, %#010x, %#010x",
             ident_arr[0], ident_arr[1], ident_arr[2]);
      
   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_BASE_ADDRESS, &base_addr);
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_BASE_ADDRESS failed.");
      _task_block();
   } else {
      printf("\nThe BASE_ADDRESS: 0x%x", base_addr);
   } /* Endif */
     
   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_NUM_SECTORS, &num_sectors);
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_NUM_SECTORS failed.");
      _task_block();
   } else {
      printf("\nNumber of sectors: %d", num_sectors);
   } /* Endif */

   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_WIDTH, &width);
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_WIDTH failed.");
      _task_block();
   } else {
      printf("\nThe WIDTH: %d", width);
   } /* Endif */

   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_BLOCK_MAP, 
      (uint_32 _PTR_)&info_ptr);      
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_BLOCK_MAP failed.");
      _task_block();
   } /* Endif */
            
   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_BLOCK_GROUPS, &num_blocks);
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_NUM_BLOCKS failed");
      _task_block();
   } /* Endif */

   for ( i = 0; i < num_blocks; i++ ) {
       printf("\nThere are %d sectors in Block %d", info_ptr[i].NUM_SECTORS, 
          (i + 1));
       printf("\nBlock %d Sector Size: %d (0x%x)", (i + 1),
          info_ptr[i].SECT_SIZE, info_ptr[i].SECT_SIZE);
       total_size += (info_ptr[i].SECT_SIZE * info_ptr[i].NUM_SECTORS);
   } /* Endfor */
      
   printf("\nTotal size of the Flash device is: %d (0x%x)", total_size,
      total_size); 
   
   #if WRITE_PROTECT_TEST
        flash_write_ptotect_test(flash_hdl);   
   #endif
      
   i = write(flash_hdl, "abc", 3 );
   i = write(flash_hdl, "def", 3 );   
       

   /*
   ** We are testing the flash device in the following way:
   ** 1st. We do a single partial write in a single sector.
   ** 2nd. We overlap the write over two sectors, both partial.   
   ** 3rd. We write one full sector.
   ** 4th. We write 3 sectors, all full sectors. (one case may write the last 
   **      one partial)
   ** 5th. We write 4 sectors, 1st and 4th partial.   
   ** 6th. We write across 2 blocks, both partial writes.
   ** 7th. We write across 3 blocks, if they exist, two if possible, or 
   **      bypass this test if the sector sizes are all the same.
   **
   ** Alternately, we can bypass this and do a single sector test to avoid 
   ** overwriting any onboard monitors which may reside on the flash.
   */   
      
   for ( k = 0; k < NUM_LOOPS; k++) {
#if (FLASH_TEST_ENTIRE_CHIP)
         switch ( k ) {
            case 0: 
               /* 
               ** Start at the third sector, some flash devices are 
               ** read only in the first one or two. 
               */ 

#if (FLASH_TEST_ERASE_CHIP)         
               // Available to test erase_chip if device supports this, 
               // otherwise it just uses erase_sector in a loop  
               printf("\nErasing entire chip (this will take a while)");            
               error_code = _io_ioctl(flash_hdl, FLASH_IOCTL_ERASE_CHIP, NULL);
               if (error_code != MQX_OK) {
                  printf("\nFLASH_IOCTL_ERASE_CHIP failed.");
                  _task_block();
               } /* Endif */
#endif
               
               j = 0;
               for ( test_block = 0; test_block < num_blocks; test_block++ ) {
                  if ( info_ptr[test_block].NUM_SECTORS >= (3 - j)) {
                     read_write_size = info_ptr[test_block].SECT_SIZE/2;
                     /* 1/4 of the way in, write to half of the sector */
                     seek_location = (uint_32)(info_ptr[test_block].START_ADDR + 
                        (info_ptr[test_block].SECT_SIZE * ((3 - j) - 1)) + 
                        (info_ptr[test_block].SECT_SIZE/4));
                     break;    
                  } else  {
                     j += info_ptr[test_block].NUM_SECTORS;
                  }/* Endif */ 
               } /* Endfor */
               /* If for loop fails, write to last sector in the first block (0) */
               if ( !read_write_size ) {
                   read_write_size = info_ptr[0].SECT_SIZE/2;
                   seek_location = (uint_32)((info_ptr[0].SECT_SIZE/4) + 
                      info_ptr[0].START_ADDR + 
                      (info_ptr[0].SECT_SIZE * (info_ptr[0].NUM_SECTORS - 1)));
               }/* Endif */ 
               break;
            case 1:
               /* 
               ** Using the same start point, write over two sectors, and test
               ** buffering of flash. 
               */ 
               error_code = ioctl(flash_hdl, FLASH_IOCTL_ENABLE_BUFFERING, 
                  &test_val);      
               if (error_code != MQX_OK) {
                  printf("\nFLASH_IOCTL_ENABLE_BUFFERING failed.");
                  _task_block();
               } /* Endif */
               read_write_size = info_ptr[test_block].SECT_SIZE;
               break;
            case 2: 
               /* Write a single, full sector */
               seek_location = (uint_32)(info_ptr[test_block].START_ADDR + 
                  (info_ptr[test_block].SECT_SIZE * (info_ptr[test_block].NUM_SECTORS - 1))); 
               break;
            case 3: 
               /* Write three full sectors, if possible */
               n = test_block;
               for ( i = 0; i < 2; i++ ) {
                  read_write_size += info_ptr[n].SECT_SIZE;
                  if ( n < num_blocks ) {
                     if ((seek_location + read_write_size) >= 
                          (uint_32)info_ptr[n + 1].START_ADDR) 
                     { /* We're stepping into the next block */
                        if ((seek_location + read_write_size) > 
                             (uint_32)info_ptr[n + 1].START_ADDR ) 
                        { /* 
                          ** We were at the last sector of the block already and 
                          ** stepped too far, reduce the size 
                          */
                          read_write_size -= info_ptr[n].SECT_SIZE;
                          i--;
                        } /* Endif */
                        n++;
                     }/* Endif */
                  } else  {
                     /* We're in the last block */
                     if ((seek_location + read_write_size + 
                         info_ptr[n].SECT_SIZE) > total_size) 
                     {
                        break;
                     } /* Endif */
                  }/* Endif */
               } /* Endfor */
               break;
            case 4: 
               /* Disable the buffering for the remainder of the tests */
               error_code = ioctl(flash_hdl, FLASH_IOCTL_DISABLE_BUFFERING, 
                  &test_val);      
               if (error_code != MQX_OK) {
                  printf("\nFLASH_IOCTL_DISABLE_BUFFERING failed (0x%X).", error_code);
                  _task_block();
               } /* Endif */
               /* Write four sectors, first and last partial, if possible */
               seek_location = (uint_32)(info_ptr[test_block].START_ADDR + 
                        (info_ptr[test_block].SECT_SIZE * ((3 - j) - 1)) + 
                        (info_ptr[test_block].SECT_SIZE/2)); 
               n = test_block;
               read_write_size = info_ptr[test_block].SECT_SIZE/2;
               for ( i = 0; i < 3; i++ ) {
                  if ( i == 2 ) {
                     /* To make the last sector a partial write */
                     read_write_size += info_ptr[n].SECT_SIZE/2;
                  } else  {
                     read_write_size += info_ptr[n].SECT_SIZE;
                  } /* Endif */
                  if ( n < num_blocks ) {
                     if ((seek_location + read_write_size) >= 
                          (uint_32)info_ptr[n + 1].START_ADDR ) 
                     { /* We're stepping into the next block */
                        if ((seek_location + read_write_size) > 
                             (uint_32)info_ptr[n + 1].START_ADDR ) 
                        { /* 
                          ** We were at the last sector of the block already and 
                          ** stepped too far, reduce the size 
                          */
                          if ( i == 2 ) {
                             read_write_size -= info_ptr[n].SECT_SIZE/2;
                          } else  {
                             read_write_size -= info_ptr[n].SECT_SIZE;
                          }/* Endif */
                          i--;
                        } /* Endif */
                        n++;
                     }/* Endif */
                  } else  {
                     /* We're in the last block */
                     if (((i == 2) && ((seek_location + read_write_size + 
                         (info_ptr[n].SECT_SIZE/2)) > total_size)) ||
                         ((seek_location + read_write_size + 
                         info_ptr[n].SECT_SIZE) > total_size)) 
                     {
                        break;
                     }/* Endif */
                  }/* Endif */
               } /* Endfor */
               break;
            case 5:
               if ( num_blocks == 1 ) {
                  test_completed = TRUE;
                  break;
               }/* Endif */    
               /* Write two sectors over a block boundary, both partial writes*/
               if ((test_block + 1) == num_blocks ) {
                  /* We're in the last block, back up one block */
                  test_block--;               
               }/* Endif */
               seek_location = (uint_32)(info_ptr[test_block].START_ADDR + 
                  (info_ptr[test_block].SECT_SIZE * (info_ptr[test_block].NUM_SECTORS - 1)) + 
                  (info_ptr[test_block].SECT_SIZE/2)); 
               read_write_size = (info_ptr[test_block].SECT_SIZE/2) + 
                                 (info_ptr[test_block + 1].SECT_SIZE/2);
               break;
            case 6: 
               /* 
               ** Write across 3 blocks, if they exist, two if possible, or 
               ** bypass this test if the sector sizes are all the same.
               */
               read_write_size = 0;
               for ( i = 0; i < num_blocks; i++ ) {
                  if ( read_write_size > 
                      (info_ptr[i].SECT_SIZE * info_ptr[i].NUM_SECTORS)) 
                  {
                     test_block = i;
                     read_write_size = info_ptr[test_block].SECT_SIZE * 
                                       info_ptr[test_block].NUM_SECTORS;
                  }/* Endif */
               } /* Endfor */            
               if ( test_block > 0 ) {
                  seek_location = (uint_32)(info_ptr[test_block - 1].START_ADDR + 
                  (info_ptr[test_block - 1].SECT_SIZE * (info_ptr[test_block - 1].NUM_SECTORS - 1)) + 
                  (info_ptr[test_block - 1].SECT_SIZE/2)); 
                  read_write_size += (info_ptr[test_block - 1].SECT_SIZE/2) + 
                                     (info_ptr[test_block + 1].SECT_SIZE/2);
               } else  {
                  /* We'd just be repeating the case 5 test, so quit */
                  test_completed = TRUE;
               }/* Endif */
               break;               
            default:
               /* Break out of the for loop, we're finished */
               k = NUM_LOOPS + 1;
               break;
         } /* Endswitch */
         if ( test_completed ) {
            break;
         }/* Endif */
         /* In case the above logic breaks, use this as a default */
         if ((seek_location + read_write_size) > total_size) {
            seek_location = total_size - read_write_size - 1;
         } /* Endif */
         
#else
         /* There may be a monitor in the flash, only want to test one sector */
#ifdef FLASH_TEST_SECTOR
         num_sectors = 0;
         for ( test_block = 0; test_block < num_blocks; test_block++ ) {
            num_sectors += info_ptr[test_block].NUM_SECTORS;
            if ( num_sectors >= FLASH_TEST_SECTOR ) {
               break;
            }/* Endif */
         } /* Endfor */
         num_sectors -= info_ptr[test_block].NUM_SECTORS;
         offset = (FLASH_TEST_SECTOR - num_sectors) - 1;         
         read_write_size = info_ptr[test_block].SECT_SIZE;
         seek_location = info_ptr[test_block].START_ADDR + info_ptr[test_block].SECT_SIZE * offset;
         

#endif
#ifdef FLASH_TEST_ADDR
         if ( FLASH_TEST_ADDR >= total_size ) {
            printf("\n\nERROR: FLASH_TEST_ADDR %x exceeds total size of flash.", 
                   FLASH_TEST_ADDR);
            _task_block();
         }/* Endif */
         seek_location = 0;
         for ( test_block = 0; test_block < num_blocks; test_block++ ) {
            seek_location += (info_ptr[test_block].NUM_SECTORS * info_ptr[test_block].SECT_SIZE);
            if ( seek_location >= FLASH_TEST_ADDR ) {
               break;
            }/* Endif */
         } /* Endfor */
         seek_location = info_ptr[test_block].START_ADDR;
         for ( j = 0; j < info_ptr[test_block].NUM_SECTORS; j++ ) {
            seek_location += info_ptr[test_block].SECT_SIZE;
            if ( seek_location >= FLASH_TEST_ADDR ) {
               break;
            }/* Endif */
         } /* Endfor */
         read_write_size = info_ptr[test_block].SECT_SIZE - 
                           (FLASH_TEST_ADDR - seek_location);
         seek_location = FLASH_TEST_ADDR;
         
#endif
#endif

      printf("\n\nTesting with %d (0x%x) byte buffer, block %d, sector %d (0x%x)",
         read_write_size, read_write_size, test_block, seek_location, seek_location);

     write_buffer = allocate_buffer(read_write_size, k, "write");
     read_buffer = allocate_buffer(read_write_size, k, "read");
     old_buffer = allocate_buffer(read_write_size, k, "old");   
     
     /* fill data to write buffer */
      for ( i = 0; i < read_write_size; i++ ) {  
         write_buffer[i] = i % 256;
      } /* Endfor */

      /* Seek to sector, and read it */
      fseek(flash_hdl, seek_location, IO_SEEK_SET);
      i = read(flash_hdl, old_buffer, read_write_size);
      size_compare(flash_hdl, i, read_write_size);      
      
      /* Seek to a location and check IOCTL sector size and base */      
      fseek(flash_hdl, seek_location, IO_SEEK_SET);
      error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_BLOCK_MAP,(uint_32 _PTR_)&info_ptr);      
      if (error_code != MQX_OK) {
         printf("\nFLASH_IOCTL_GET_BLOCK_MAP failed.");
         _task_block();
      } /* Endif */
      error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_SECTOR_SIZE, &sector_size);
      if (error_code != MQX_OK) {
         printf("\nFLASH_IOCTL_GET_SECTOR_SIZE failed.");
         _task_block();
      } /* Endif */
      if (info_ptr[test_block].SECT_SIZE != sector_size) {
         printf("\nioctl GET_SECTOR_SIZE returned: 0x%x  Sector size is: 0x%x",
                sector_size, info_ptr[test_block].SECT_SIZE);
      } /* Endif */
      
      /* Check IOCTL sector base for the seek location */
      error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_SECTOR_BASE, &base_addr);
      if (error_code != MQX_OK) {
         printf("\nCall to FLASH_IOCTL_GET_SECTOR_BASE failed.");
         _task_block();
      } /* Endif */
      /* The seek location should fall between the base and base+size of the sector */
      if (!(base_addr <= seek_location <= (base_addr + info_ptr[test_block].SECT_SIZE -1))) {
         printf("\nError: ioctl FLASH_IOCTL_GET_SECTOR_BASE returned: 0x%x  Seek location is: 0x%x",
                 base_addr, seek_location);
         _task_block();
         }

      
      if (k == 2 || k == 3) { /* Test erase on full sectors only */
         /* Seek to sector, and erase it */
         printf("\nTesting _io_ioctl erase_sector: %d (0x%x)", seek_location, seek_location);
         fseek(flash_hdl, seek_location, IO_SEEK_SET);
         error_code = _io_ioctl(flash_hdl, FLASH_IOCTL_ERASE_SECTOR, NULL);
         if (error_code != MQX_OK) {
            printf("\nFLASH_IOCTL_ERASE_SECTOR failed.");
            _task_block();
         } /* Endif */
      
         /* Seek to erased sector, and read it */
         fseek(flash_hdl, seek_location, IO_SEEK_SET);
         i = read(flash_hdl, read_buffer, read_write_size);
         if (i != read_write_size ) {
            printf("\nFailed to read flash, 0x%x", _task_get_error());
         } /* Endif */
         /* Check if all ff's */
         for ( i = 0; i < read_write_size; i++ ) {  
            if (read_buffer[i] != 0xff) {
               printf("\nFailed to erase flash at index %d  Seek location %d (0x%x)", i, seek_location, seek_location);
               _task_block();
            } /* Endif */
         } /* Endfor */
      } /* Endif */
      
      /* Seek to sector and modify it */
      printf("\nSeek to sector and modify (may take a while)");
      fseek(flash_hdl, seek_location, IO_SEEK_SET);
      i = write(flash_hdl, write_buffer, read_write_size );
      size_compare(flash_hdl, i, read_write_size);
      /* Seek to sector, and read it */
      fseek(flash_hdl, seek_location, IO_SEEK_SET);
      i = read(flash_hdl, read_buffer, read_write_size);
      if (i != read_write_size ) {
         printf("\nFailed to read flash, 0x%x", _task_get_error());
      } /* Endif */
      /* compare buffers */
      compare_test(write_buffer, read_buffer, read_write_size); 

      fseek(flash_hdl, seek_location, IO_SEEK_SET);
      i = write(flash_hdl, old_buffer, read_write_size);
      if (i != read_write_size) {
         printf("\nFailed to write original data to flash, 0x%x", 
            _task_get_error());
         _task_block();
      } /* Endif */
      if (_mem_free(write_buffer) != MQX_OK) {
         printf("\nFailed to free memory - buffer");
         _task_block();
      } /* Endif */
      if (_mem_free(read_buffer) != MQX_OK) {
         printf("\nFailed to free memory - read_buffer");
         _task_block();
      } /* Endif */
      if (_mem_free(old_buffer) != MQX_OK) {
         printf("\nFailed to free memory - old_buffer");
         _task_block();
      } /* Endif */
   } /* Endfor */

    /* Additional features for sector write */
    /* Close device */
    flash_close(flash_hdl);
    /* Open device */
    flash_hdl = flash_open(FLASH_NAME);
    /* disable sector cache */
    _io_ioctl(flash_hdl, FLASH_IOCTL_DISABLE_SECTOR_CACHE, NULL);
    printf("\n\rSector cache disabled.");
    
    read_write_size = TEST_STRUCT_SIZE;
    /* allocate buffers */
    write_buffer = allocate_buffer(read_write_size, k, "write");
    read_buffer = allocate_buffer(read_write_size, k, "read");
    /* Generate data - structure with non aligned to write length */ 
    for ( i = 0; i < read_write_size; i++ ) {  
         write_buffer[i] = i;
    } 
    /* write strucuture */
    printf("\n\nTesting with %d (0x%x) byte buffer, block %d, sector %d (0x%x)",
         read_write_size, read_write_size, 0, seek_location, seek_location);
    seek_location = info_ptr[0].START_ADDR;
    fseek(flash_hdl, seek_location, IO_SEEK_SET);
    i = write(flash_hdl, write_buffer, read_write_size );
    size_compare(flash_hdl, i, read_write_size);
    /* check write */   
    read_and_test_data(flash_hdl, read_write_size, write_buffer, read_buffer, 
        seek_location);
    /* modify structure */
    printf("\n\rWrite %d bytes to to same place without cache", read_write_size);
    for ( i = 0; i < read_write_size; i++ ) {  
         write_buffer[i] = 0xaa;
    } 
    /* write structure to same place */
    fseek(flash_hdl, seek_location, IO_SEEK_SET);
    i = write(flash_hdl, write_buffer, read_write_size );
    size_compare(flash_hdl, i, read_write_size);
    /* check write */
    read_and_test_data(flash_hdl, read_write_size, write_buffer, read_buffer, 
        seek_location);
    /* enable ram cache */
    _io_ioctl(flash_hdl, FLASH_IOCTL_ENABLE_SECTOR_CACHE, NULL);
    printf("\n\rSector cache enabled.");
    seek_location = info_ptr[0].START_ADDR + read_write_size;
    printf("\n\rTesting with 41 byte buffer, write to address 0x%x ",seek_location );
    /* Generate data - structure with non aligned to write length */ 
    for ( i = 0; i < read_write_size; i++ ) {  
         write_buffer[i] = i;
    }
        
    /* write add data to sector */
    i = write(flash_hdl, write_buffer, read_write_size );
    size_compare(flash_hdl, i, read_write_size);
    /* check write */
    read_and_test_data(flash_hdl, read_write_size, write_buffer, read_buffer, 
        seek_location);
    /* disable ram cache */
    _io_ioctl(flash_hdl, FLASH_IOCTL_DISABLE_SECTOR_CACHE, NULL);
    printf("\n\rSector cache disabled.");
    seek_location = info_ptr[0].START_ADDR + read_write_size;
    fseek(flash_hdl, seek_location, IO_SEEK_SET);
    /* rewrite data */
    printf("\n\rTesting with 41 byte buffer, write to address 0x%x\n",seek_location );
    printf("\n*** This test should end with error ***\n");
    i = write(flash_hdl, write_buffer, read_write_size );
    size_compare(flash_hdl, i, read_write_size);
    /* end */
    printf("\nProgram finshed");

   _mqx_exit(0);

}

/* EOF */

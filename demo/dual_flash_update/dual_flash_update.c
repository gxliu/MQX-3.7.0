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
* $FileName: dual_flash_update.c$
* $Version : 3.7.3.1$
* $Date    : Mar-30-2011$
*
* Comments:
*
*   This file contains the source for demonstrating how to execute code from one flash array
*     while programming the other, and then swap the arrays. 
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include <string.h>

#if BSP_M51EMDEMO
    #if ! ( BSPCFG_ENABLE_FLASHX2 )
    #error This application requires BSPCFG_ENABLE_FLASHX2 defined non-zero in user_config.h. Please recompile BSP with this option.
    #endif
    /* external flash name */
    #define         FLASH_NAME "flashx2:"
    #define         WRITE_PROTECT_TEST 0    
#endif

#pragma define_section text_array1 ".text_array1" far_absolute RW
#pragma define_section text_array2 ".text_array2" far_absolute RW

/* This array is in flash1, see the LCF file */
__declspec(text_array1) volatile uchar textstring1[] = "This text was originally at 0x0001FEFF (flash array 1)";
/* This array is in flash2, see the LCF file */
__declspec(text_array2) volatile uchar textstring2[] = "This text was originally at 0x0003FEFF (flash array 2)";

/* Task IDs */
#define FLASH_TASK 7

/* Set to 1 to test the entire chip */
#define FLASH_TEST_ENTIRE_CHIP   (1)
/* Set to 1 to call FLASH_IOCTL_ERASE_CHIP if chip erase function is present */
#define FLASH_TEST_ERASE_CHIP    (1)
#define NUM_LOOPS                (7)

/* function prototypes */
MQX_FILE_PTR flash_open(char_ptr name);
void flash_close(MQX_FILE_PTR flash);
uchar_ptr allocate_buffer(_mem_size buffer_size, char_ptr string);
extern void flash_task(uint_32);

extern uchar _CODE_END[];

#define CODE_END    ((uint_32)_CODE_END)
#define BUFFER_SIZE 0x1000

/* GPIO variables */
MQX_FILE_PTR port_file;

GPIO_PIN_STRUCT input_pins[] = {
  BSP_BUTTON1,
  GPIO_LIST_END
};


const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{ 
   /* Task Index,   Function,   Stack,  Priority,   Name,   Attributes,          Param, Time Slice */ 
    { FLASH_TASK,   flash_task, 4000,   8,          "Dual Flash Task", MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};


/*TASK*-----------------------------------------------------
* 
* Task Name    : Flash Task
* Comments     :
*    This task opens up the secondary flash array at 0x(00)02_0000 for writing,
*     copies the currently executing code to the secondary flash array, 
*     swaps the arrays, and then resets the processor. 
*
*    This code should not be run with the debugger because it will not preform a software reset
*    properly while in debug mode
*
*END*-----------------------------------------------------*/
void flash_task(uint_32 initial_data)
{
  
  MQX_FILE_PTR   flash_hdl;
  uchar_ptr      write_buffer;
  _mqx_int       i;
  uchar_ptr      address_ptr = 0; 
  char           pressed=0;

  _int_install_unexpected_isr();

  printf("\n\n\n*******************************************\n");
  printf(" Flash Swap Demo\n");
  printf("*******************************************\n"); 

  printf("\nFor proper operation, power down and then power back up the board\n");
  printf("after programming to ensure the debugger is not active,\n");

  
  /* Open flashx2, defined in the BSP as starting at 0x0002_0000 */
  flash_hdl = flash_open(FLASH_NAME);
   
    /* Enable sector cache */
  _io_ioctl(flash_hdl, FLASH_IOCTL_ENABLE_SECTOR_CACHE, NULL);  

  /* Open GPIO */
  if (NULL == (port_file = fopen("gpio:read", (char_ptr) &input_pins )))
  {
    printf("Opening file GPIO with associated pins failed.\n");
    _mqx_exit(-1);
  }
 
  /* array1 and array2 swap locations when the flash arrays are swapped */
  printf("\nData at 0x0001_FEFF: %s\n", textstring1);
  printf("Data at 0x0003_FEFF: %s\n", textstring2);
        
  /* Looks at IRTC_CFG_DATA[CFG0] to determine which array is at 0x(00)00_0000. That 
       is the one currently executing code */     
  if (_mcf51_get_rtc_cfg_state() == 0)
  {
    printf("\nCode is running from Flash Memory Array 1\n");       
  } 
  else 
  {
    printf("\nCode is running from Flash Memory Array 2\n");
  }   

  printf("\nPress SW1 to swap arrays and restart\n");
 
  /* Look for SW1 press */
  while(!pressed) 
  {
    /* read the current pin status into the pin list */
    if (IO_OK != ioctl(port_file, GPIO_IOCTL_READ, (char_ptr) &input_pins))
    {
      printf("Reading pin status failed.\n");
      _mqx_exit(-1);
    }
       
    /* Determine status of pin */      
    pressed=((input_pins[0] & GPIO_PIN_STATUS)==0);
  }
 
    
  /* Copy the code that is currently running (starting at 0x0000_0000)
     to the secondary flash array at 0x(00)02_0000. */ 
  printf("\nCopying code to secondary flash array\n");   
  write_buffer = allocate_buffer( BUFFER_SIZE, "write"); //create a buffer to copy code to
  for( i=0; i < (CODE_END/BUFFER_SIZE)+1; i++)
  {
    _mem_copy( address_ptr, write_buffer, BUFFER_SIZE);  //copy code to buffer
    write(flash_hdl, write_buffer, BUFFER_SIZE);         //write buffer to the secondary flash array
    address_ptr += BUFFER_SIZE;    
  }

  /* Swap the flash arrays and restart the microprocessor */
  printf("Swapping flash arrays and restarting processor\n\n");
  _io_ioctl(flash_hdl,  FLASH_IOCTL_SWAP_FLASH_AND_RESET, NULL);

  /* Should never reach here */
  _mqx_exit(0);
}

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
uchar_ptr allocate_buffer(_mem_size buffer_size, char_ptr string) 
{
    uchar_ptr buffer_ptr;
    
    buffer_ptr = _mem_alloc_zero(buffer_size);
    if (buffer_ptr == NULL) {
        printf("\nFailed to get %s buffer", string);
        _task_block();
    } /* Endif */
    return buffer_ptr;          
}

/* EOF */

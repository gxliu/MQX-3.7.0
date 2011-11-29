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
* $FileName: hello.c$
* $Version : 3.7.16.0$
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


#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


/* Task IDs */
#define HELLO_TASK 5

extern void hello_task(uint_32);


const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{ 
   /* Task Index,   Function,   Stack,  Priority, Name,     Attributes,          Param, Time Slice */
    { HELLO_TASK,   hello_task, 1500,   8,        "hello",  MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

/*TASK*-----------------------------------------------------
* 
* Task Name    : hello_task
* Comments     :
*    This task prints " Hello World "
*
*END*-----------------------------------------------------*/
void hello_task
   (
      uint_32 initial_data
   )
{
   printf("Hello World\n"); 
   
   /* 
   ** This example uses polled serial I/O by default. Should it be modified
   ** to use interrupt driven serial drivers, you will need to uncomment the
   ** following delay code to insure serial communication completes before 
   ** _mqx_exit() disables all interrupts.
   */
  _time_delay(200);
   
   _mqx_exit(0);

}

/* EOF */

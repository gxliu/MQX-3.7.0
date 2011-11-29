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
* $FileName: test.c$
* $Version : 3.4.9.0$
* $Date    : Sep-17-2009$
*
* Comments:
*
*   This file contains the source for the test example program.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include <event.h>
#include <log.h>
#include <lwevent.h>
#include <lwlog.h>
#include <lwmem.h>
#include <lwtimer.h>
#include <message.h>
#include <mutex.h>
#include <name.h>
#include <part.h>
#include <sem.h>
#include <timer.h>
#include <watchdog.h>


#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


extern void background_test_task(uint_32);

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
   /* Task Index, Function,             Stack,  Priority,   Name,     Attributes,          Param, Time Slice */
    { 10,         background_test_task, 2000,   8,          "Main",   MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

/*TASK*----------------------------------------------------------
*
* Task Name : background_test_task
* Comments  :
*   This task is meant to run in the background testing for
* integrity of MQX component datastructures.
*END*-----------------------------------------------------------*/

void background_test_task
   (
      uint_32  parameter
   )
{
   _partition_id  partition;
   _lwmem_pool_id lwmem_pool_id;
   pointer        error_ptr;
   pointer        error2_ptr;
   _mqx_uint      error;
   _mqx_uint      result;

   while (TRUE) {
      result = _event_test(&error_ptr);
      if (result != MQX_OK){
         printf("\nFailed _event_test: 0x%X.", result);
         _mqx_exit(1);
      } 
      result = _log_test(&error);
      if (result != MQX_OK){
         printf("\nFailed _log_test: 0x%X.", result);
         _mqx_exit(2);
      }
      result = _lwevent_test(&error_ptr, &error2_ptr);
      if (result != MQX_OK){
         printf("\nFailed _lwevent_test: 0x%X.", result);
         _mqx_exit(3);
      }
      result = _lwlog_test(&error);
      if (result != MQX_OK){
         printf("\nFailed _lwlog_test: 0x%X.", result);
         _mqx_exit(4);
      }
      result = _lwsem_test(&error_ptr, &error2_ptr);
      if (result != MQX_OK){
         printf("\nFailed _lwsem_test: 0x%X.", result);
         _mqx_exit(5);
      }
      result = _lwmem_test(&lwmem_pool_id, &error_ptr);
      if (result != MQX_OK){
         printf("\nFailed _lwmem_test: 0x%X.", result);
         _mqx_exit(6);
      }
      result = _lwtimer_test(&error_ptr, &error2_ptr);
      if (result != MQX_OK){
         printf("\nFailed _lwtimer_test: 0x%X.", result);
         _mqx_exit(7);
      }
      
#if ! MQX_USE_LWMEM_ALLOCATOR      
      result = _mem_test_all(&error_ptr);
      if (result != MQX_OK){
         printf("\nFailed _mem_test_all,");
         printf("\nError = 0x%X, pool = 0x%X.", result,
            (_mqx_uint)error_ptr);
         _mqx_exit(8);
      }
#endif
      
      /*
      ** Create the message component.
      ** Verify the integrity of message pools and message queues.
      */
      if (_msg_create_component() != MQX_OK){
         printf("\nError creating the message component.");
         _mqx_exit(9);
      }
      if (_msgpool_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _msgpool_test.");
         _mqx_exit(10);
      }
      if (_msgq_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _msgq_test.");
         _mqx_exit(11);
      }
      if (_mutex_test(&error_ptr) != MQX_OK){
         printf("\nFailed _mutex_test.");
         _mqx_exit(12);
      }
      if (_name_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _name_test.");
         _mqx_exit(13);
      }
      if (_partition_test(&partition, &error_ptr, &error2_ptr) 
         != MQX_OK)
      {
         printf("\nFailed _partition_test.");
         _mqx_exit(14);
      }
      if (_sem_test(&error_ptr) != MQX_OK){
         printf("\nFailed _sem_test.");
         _mqx_exit(15);
      }
      if (_taskq_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _takq_test.");
         _mqx_exit(16);
      }
      if (_timer_test(&error_ptr) != MQX_OK){
         printf("\nFailed _timer_test.");
         _mqx_exit(17);
      }
      if (_watchdog_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _watchlog_test.");
         _mqx_exit(18);
      }
      printf("All tests passed.");
      _mqx_exit(0);
   }

}

/* EOF */

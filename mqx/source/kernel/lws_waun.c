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
* $FileName: lws_waun.c$
* $Version : 3.5.6.0$
* $Date    : Dec-8-2009$
*
* Comments:
*
*   This file contains the functions for manipulating the 
*   light weight semaphores.  These semaphores have low memory
*   requirements, and no extra features.  Tasks are suspended
*   in fifo order while waiting for a post.  No limits on values
*   are imposed.
*
*END************************************************************************/

#include "mqx_inc.h"
#if MQX_HAS_TICK

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _lwsem_wait_until
* Returned Value   : an error code
*   queue
* Comments         :
*   This function obtains a semaphore from the lwsem.  If one is not
* available, the task waits (in a FIFO order) or until a specified time
* has been reached.
*
*END*----------------------------------------------------------------------*/

_mqx_uint _lwsem_wait_until
   (
      /* [IN] the semaphore address */
      LWSEM_STRUCT_PTR sem_ptr,

      /* [IN] the time to delay until */
      MQX_TICK_STRUCT_PTR ticks
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR kernel_data;
   TD_STRUCT_PTR          td_ptr;
   _mqx_uint              result;

   _GET_KERNEL_DATA(kernel_data);

   _KLOGE3(KLOG_lwsem_wait_until, sem_ptr, ticks);

#if MQX_CHECK_ERRORS
   if (kernel_data->IN_ISR) {
      _KLOGX2(KLOG_lwsem_wait_until, MQX_CANNOT_CALL_FUNCTION_FROM_ISR);
      return(MQX_CANNOT_CALL_FUNCTION_FROM_ISR);
   } /* Endif */
#endif
#if MQX_CHECK_VALIDITY
   if (sem_ptr->VALID != LWSEM_VALID) {
      _KLOGX2(KLOG_lwsem_wait_until, MQX_INVALID_LWSEM);
      return(MQX_INVALID_LWSEM);
   } /* Endif */
#endif

   _INT_DISABLE();
   if (sem_ptr->VALUE <= 0) {
      td_ptr = kernel_data->ACTIVE_PTR;
      td_ptr->TIMEOUT = *ticks;
      result = _lwsem_wait_timed_internal(sem_ptr, td_ptr);
   } else {
      --sem_ptr->VALUE;
      /* Start CR 788 */
      result = MQX_OK;
      /* End  CR 788 */
   } /* Endif */

//#if MQX_COMPONENT_DESTRUCTION
   /* We must check for component destruction */
   if (sem_ptr->VALID != LWSEM_VALID) {
      _int_enable();
      /* The semaphore has been deleted */
      _KLOGX2(KLOG_lwsem_wait_until, MQX_INVALID_LWSEM);
      return(MQX_INVALID_LWSEM);
   } /* Endif */
//#endif

   _INT_ENABLE();

   _KLOGX2(KLOG_lwsem_wait_until, result);

   return(result);
   
} /* Endbody */
#endif
/* EOF */

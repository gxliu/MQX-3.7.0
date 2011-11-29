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
* $FileName: lwe_dest.c$
* $Version : 3.0.4.0$
* $Date    : Nov-21-2008$
*
* Comments:
*
*   This file contains the function for destroying a light weight event.
*
*END************************************************************************/

#include "mqx_inc.h"
#if MQX_USE_LWEVENTS
#include "lwevent.h"
#include "lwe_prv.h"

/*FUNCTION*------------------------------------------------------------
* 
* Function Name    : _lwevent_destroy
* Returned Value   : 
*   Returns MQX_OK upon success, a Task Error code or an error code:
* Comments         :
*    Used by a task to destroy an instance of a light weight event
*
* 
*END*------------------------------------------------------------------*/

_mqx_uint _lwevent_destroy
   (
      /* [IN] the location of the event */
      LWEVENT_STRUCT_PTR event_ptr
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR kernel_data;
#if MQX_COMPONENT_DESTRUCTION
   TD_STRUCT_PTR          td_ptr;
#endif

   _GET_KERNEL_DATA(kernel_data);                                         

   _KLOGE2(KLOG_lwevent_destroy, event_ptr);
   
#if MQX_COMPONENT_DESTRUCTION

#if MQX_CHECK_ERRORS
   if (kernel_data->IN_ISR) {
      _KLOGX2(KLOG_lwevent_destroy, MQX_CANNOT_CALL_FUNCTION_FROM_ISR);
      return(MQX_CANNOT_CALL_FUNCTION_FROM_ISR);
   } /* Endif */
#endif

   _int_disable();
#if MQX_CHECK_VALIDITY
   if (event_ptr->VALID != LWEVENT_VALID) {
      _int_enable();
      _KLOGX2(KLOG_lwevent_destroy, MQX_LWEVENT_INVALID);
      return(MQX_LWEVENT_INVALID);
   } /* Endif */
#endif

   /* Effectively stop all access to the event */
   event_ptr->VALID = 0;
   while (_QUEUE_GET_SIZE(&event_ptr->WAITING_TASKS)) {
      _QUEUE_DEQUEUE(&event_ptr->WAITING_TASKS, td_ptr);
      _BACKUP_POINTER(td_ptr, TD_STRUCT, AUX_QUEUE);
      _TIME_DEQUEUE(td_ptr, kernel_data);
      _TASK_READY(td_ptr, kernel_data);
   } /* Endwhile */   
 
   /* remove event from kernel LWEVENTS queue */
   _QUEUE_REMOVE(&kernel_data->LWEVENTS, event_ptr);

   _int_enable();

   /* May need to let higher priority task run */
   _CHECK_RUN_SCHEDULER();
#endif

   _KLOGX2(KLOG_lwevent_destroy, MQX_OK);
   return(MQX_OK);
   
} /* Endbody */   
#endif /* MQX_USE_LWEVENTS */

/* EOF */

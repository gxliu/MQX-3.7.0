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
* $FileName: lwe_crea.c$
* $Version : 3.0.5.0$
* $Date    : Jun-8-2009$
*
* Comments:
*
*   This file contains the functions for creating a light weight event.
*
*END************************************************************************/

#include "mqx_inc.h"
#if MQX_USE_LWEVENTS
#include "lwevent.h"
#include "lwe_prv.h"

/*FUNCTION*------------------------------------------------------------
* 
* Function Name    : _lwevent_create
* Returned Value   : 
*   Returns MQX_OK upon success, or an error code
* Comments         :
*    Used by a task to create an instance of an light weight event.
*
* 
*END*------------------------------------------------------------------*/

_mqx_uint _lwevent_create
   (
      /* [IN] the location of the event */
      LWEVENT_STRUCT_PTR event_ptr,
      
      /* [IN] flags for the light weight event */
      _mqx_uint          flags
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR kernel_data;
/* START CR 1896 */
   LWEVENT_STRUCT_PTR     event_chk_ptr;
/* END CR 1896 */
   
   _GET_KERNEL_DATA(kernel_data);                                         

   _KLOGE2(KLOG_lwevent_create, event_ptr);

   _QUEUE_INIT(&event_ptr->WAITING_TASKS, 0);
   event_ptr->VALUE = 0;
   event_ptr->FLAGS = flags;

   if (flags & LWEVENT_AUTO_CLEAR)
      event_ptr->AUTO = ~0;
   else
      event_ptr->AUTO = 0;

   _int_disable();
   if (kernel_data->LWEVENTS.NEXT == NULL) {
      /* Initialize the light weight event queue */
      _QUEUE_INIT(&kernel_data->LWEVENTS, 0);
   } /* Endif */
   event_ptr->VALID = LWEVENT_VALID;

/* START CR 1896 */
#if MQX_CHECK_ERRORS
   /* Check if lwevent is already initialized */
   event_chk_ptr = (LWEVENT_STRUCT_PTR)((pointer)kernel_data->LWEVENTS.NEXT);
   while (event_chk_ptr != (LWEVENT_STRUCT_PTR)((pointer)&kernel_data->LWEVENTS)) {
      if (event_chk_ptr == event_ptr) {
         _int_enable();
         _KLOGX2(KLOG_lwevent_create, MQX_EINVAL);
         return(MQX_EINVAL);
      } /* Endif */
      event_chk_ptr = (LWEVENT_STRUCT_PTR)((pointer)event_chk_ptr->LINK.NEXT);
   } /* Endwhile */
#endif
/* END CR 1896 */

   _QUEUE_ENQUEUE(&kernel_data->LWEVENTS, &event_ptr->LINK);
   _int_enable();

   _KLOGX2(KLOG_lwevent_create, MQX_OK);
   return(MQX_OK);

} /* Endbody */
#endif /* MQX_USE_LWEVENTS */

/* EOF */

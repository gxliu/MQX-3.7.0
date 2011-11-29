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
* $FileName: lwe_sac.c$
* $Version : 3.5.3.0$
* $Date    : Jan-13-2010$
*
* Comments:
*
*   This file contains the function for setting the event.
*
*END************************************************************************/

#include "mqx_inc.h"
#if MQX_USE_LWEVENTS
#include "lwevent.h"
#include "lwe_prv.h"

/*FUNCTION*------------------------------------------------------------
* 
* Function Name    : _lwevent_set_auto_clear
* Returned Value   : 
*   Returns MQX_OK upon success, a Task Error code or an error code:
* Comments         :
*    Used by a task to set functionality of the specified bits in an event 
*    to automatic / manual (1 = auto, 0 = manu)
* 
*END*------------------------------------------------------------------*/

_mqx_uint _lwevent_set_auto_clear
   (
      /* [IN] - The address of the light weight event */
      LWEVENT_STRUCT_PTR   event_ptr, 

      /* [IN] - bit mask, each bit of which represents an event. */
      _mqx_uint            auto_mask
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR      kernel_data;
            
   _GET_KERNEL_DATA(kernel_data);

   _KLOGE3(KLOG_lwevent_set_auto_clear, event_ptr, auto_mask);

   _INT_DISABLE();
#if MQX_CHECK_VALIDITY
   if (event_ptr->VALID != LWEVENT_VALID) {
      _int_enable();
      _KLOGX2(KLOG_lwevent_set, MQX_LWEVENT_INVALID);
      return(MQX_LWEVENT_INVALID);
   } /* Endif */
#endif

   event_ptr->AUTO = auto_mask;

   _INT_ENABLE();

   _KLOGX2(KLOG_lwevent_set_auto_clear, MQX_OK);
   return(MQX_OK);
         
} /* Endbody */
#endif /* MQX_USE_LWEVENTS */

/* EOF */

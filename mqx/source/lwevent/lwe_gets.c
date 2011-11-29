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
* $FileName: lwe_gets.c$
* $Version : 3.5.3.0$
* $Date    : Feb-2-2010$
*
* Comments:
*
*   This file contains the function for getting last wait operation bit mask.
*
*END************************************************************************/

#include "mqx_inc.h"
#if MQX_USE_LWEVENTS
#include "lwevent.h"
#include "lwe_prv.h"

/*FUNCTION*------------------------------------------------------------
* 
* Function Name    : _lwevent_get_signalled
* Returned Value   : 
*   Returns the lwevent mask that unblocked task in last _lwevent_wait_*
* 
*END*------------------------------------------------------------------*/

_mqx_uint _lwevent_get_signalled
   (
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR      kernel_data;
   _mqx_uint                   value;
            
   _GET_KERNEL_DATA(kernel_data);

   _KLOGE1(KLOG_lwevent_get_signalled);

   value = kernel_data->ACTIVE_PTR->LWEVENT_BITS;

   _KLOGX2(KLOG_lwevent_get_signalled, value);
   return(value);

} /* Endbody */
#endif /* MQX_USE_LWEVENTS */

/* EOF */

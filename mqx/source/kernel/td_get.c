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
* $FileName: td_get.c$
* $Version : 3.0.3.0$
* $Date    : Nov-21-2008$
*
* Comments:
*
*   This file contains the function that returns the task descriptor
*   address for a given task id.
*
*END************************************************************************/

#include "mqx_inc.h"

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _task_get_td
* Returned Value   : pointer to task descriptor
* Comments         :
*   This function takes a task-id, and converts it to the address
*   of the associated task descriptor.  It returns NULL if an invalid
*   task_id is presented.
*
*END*----------------------------------------------------------------------*/

pointer _task_get_td
   (
      /* [IN] the task id whose task descriptor address is required */
      _task_id task_id
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR  kernel_data;
   TD_STRUCT_PTR           td_ptr;
   _mqx_uint               size;

   _GET_KERNEL_DATA(kernel_data);
   if (task_id == MQX_NULL_TASK_ID) {
      return((pointer)kernel_data->ACTIVE_PTR);
   } /* Endif */

   /* SPR P171-0022-01 Use int disable, not a semaphore */
   _INT_DISABLE();
   /* END SPR */

   td_ptr = (TD_STRUCT_PTR)((uchar_ptr)kernel_data->TD_LIST.NEXT -
      FIELD_OFFSET(TD_STRUCT,TD_LIST_INFO));
   /* SPR P171-0023-01 use pre-decrement on while loop */
   size   = _QUEUE_GET_SIZE(&kernel_data->TD_LIST) + 1;
   while (--size) {
   /* END SPR */
      if (td_ptr->TASK_ID == task_id) {
         /* SPR P171-0022-01 Use int disable, not a semaphore */
         _INT_ENABLE();
         /* END SPR */
         return (pointer)td_ptr;
      } /* Endif */
      td_ptr = (TD_STRUCT_PTR)((uchar_ptr)td_ptr->TD_LIST_INFO.NEXT -
         FIELD_OFFSET(TD_STRUCT,TD_LIST_INFO));
   } /* Endwhile */

   /* SPR P171-0022-01 Use int disable, not a semaphore */
   _int_enable();
   /* END SPR */

   return NULL;

} /* Endbody */

/* EOF */

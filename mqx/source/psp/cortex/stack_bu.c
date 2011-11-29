/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor
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
* $FileName: stack_bu.c$
* $Version : 3.7.3.0$
* $Date    : Feb-7-2011$
*
* Comments:
*   This file contains the functions for manipulating the user
*	context on the stack.
*
*END************************************************************************/

#include "mqx_inc.h"

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _psp_build_stack_frame
* Returned Value   : none
* Comments         :
*
*   This function sets up the stack frame of a new task descriptor.
*
*END*----------------------------------------------------------------------*/

void _psp_build_stack_frame
   (
      /* [IN] the address of the task descriptor */
      TD_STRUCT_PTR    td_ptr,

      /* [IN] the address of the stack memory block */
      pointer          stack_ptr,

      /* [IN] the size of the stack */
      _mem_size            stack_size,

      /* [IN] the task's template */
      TASK_TEMPLATE_STRUCT_PTR template_ptr,

      /* [IN] the status register to use in creating the task */
      _mqx_uint         status_register,

      /* [IN] the task creation parameter */
      uint_32     create_parameter
   )
{ /* Body */
   uchar_ptr                  stack_base_ptr;
   PSP_STACK_START_STRUCT_PTR stack_start_ptr;
   uint_32                    reg_val;

   stack_base_ptr  = (uchar_ptr)_GET_STACK_BASE(stack_ptr, stack_size);
   stack_start_ptr = (PSP_STACK_START_STRUCT_PTR)(stack_base_ptr - sizeof(PSP_STACK_START_STRUCT));

   td_ptr->STACK_BASE  = (pointer)stack_base_ptr;
   td_ptr->STACK_LIMIT = _GET_STACK_LIMIT(stack_ptr, stack_size);
   td_ptr->STACK_PTR   = stack_start_ptr;

   /*
   ** Build the task's initial stack frame. This contains the initialized
   ** registers, and an exception frame which will cause the task to 
   ** "return" to the start of the task when it is dispatched.
   */
   _mem_zero(stack_start_ptr, (_mem_size)sizeof(PSP_STACK_START_STRUCT));

    // TODO disable int - set BASEPRI, PRIMASK, FAULTMASK
   stack_start_ptr->INITIAL_CONTEXT.PENDSVPRIOR = 0;//(status_register - (1 << CORTEX_PRIOR_SHIFT)) & CORTEX_PRIOR_MASK;
   stack_start_ptr->INITIAL_CONTEXT.BASEPRI = status_register;

#if 0   
   _PSP_GET_CPSR(reg_val);
   if (status_register) {
      reg_val |= (PSP_PSR_CTRL_DIS_IRQ | PSP_PSR_CTRL_DIS_FIQ);
   } else {
      reg_val &= ~(PSP_PSR_CTRL_DIS_IRQ | PSP_PSR_CTRL_DIS_FIQ);
   } /* Endif */

/* START - CR#1810 */
#if !(defined(__thumb) || defined (_THUMB)) /* ARM version */                
   stack_start_ptr->INITIAL_CONTEXT.PSR = reg_val;
#else  /* Thumb version */
   stack_start_ptr->INITIAL_CONTEXT.PSR = reg_val | PSP_PSR_CTRL_THUMB_INST;   
#endif   
/* END - CR#1810 */

   stack_start_ptr->INITIAL_CONTEXT.FP = (uint_32)&stack_start_ptr->ZERO_STACK_POINTER;

   stack_start_ptr->INITIAL_CONTEXT.RETURN_ADDRESS = template_ptr->TASK_ADDRESS;

   stack_start_ptr->INITIAL_CONTEXT.LR = (uint_32)_task_exit_function_internal;

   stack_start_ptr->INITIAL_CONTEXT.A1 = (uint_32)create_parameter;

   stack_start_ptr->PREVIOUS_STACK_POINTER = (pointer)&stack_start_ptr->ZERO_STACK_POINTER;
      
   stack_start_ptr->EXIT_ADDRESS = _task_exit_function_internal;
   stack_start_ptr->PARAMETER    = create_parameter;
#endif   
   stack_start_ptr->INITIAL_CONTEXT.LR = (uint_32)_task_exit_function_internal;
   stack_start_ptr->INITIAL_CONTEXT.R0 = (uint_32)create_parameter;
   stack_start_ptr->INITIAL_CONTEXT.PC = (uint_32)(template_ptr->TASK_ADDRESS) | 1;
   stack_start_ptr->INITIAL_CONTEXT.PSR = 0x01000000;
   stack_start_ptr->INITIAL_CONTEXT.LR2 = 0xfffffffd;
}

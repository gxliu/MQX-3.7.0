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
* $FileName: cmcf5227.c$
* $Version : 3.0.3.0$
* $Date    : Nov-21-2008$
*
* Comments:
*
*   This file contains definitions for the MFC5227 interrupt controller
*   functions.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h"

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : compute_icntl_registers
* Returned Value  : uint_32
* Comments        :
*   Compute which registers to touch for the given interrupt number
*
*END*---------------------------------------------------------------------*/

static boolean compute_icntl_registers
   (
      /* [IN] Interrupt number */
      PSP_INTERRUPT_TABLE_INDEX irq,

      /* [OUT] Interrupt control register */
      volatile uchar _PTR_ _PTR_    ictlr,

      /* [OUT] Interrupt mask register */
      volatile uint_32 _PTR_ _PTR_  maskr,

      /* [OUT] Interrupt mask register bit */
      uint_32_ptr                   bit,

      /* [OUT] Interrupt clear mask */
      uint_32_ptr                   clear
   )
{ /* Body */
   VMCF5227_ICTRL_STRUCT_PTR  ictrl;

   if (irq >= PSP_INT_FIRST_EXTERNAL) {
      uint_32 index = irq - PSP_INT_FIRST_EXTERNAL;
      
    
      if (index < 32) {
         ictrl = PSP_GET_ICTRL0_BASE();
         *ictlr = &ictrl->ICR[index];
         *maskr = &ictrl->IMRL;
         *bit = 1 << index;
         *clear = 0;
         return TRUE;
      } /* Endif */

      if (index < 64) {
         ictrl = PSP_GET_ICTRL0_BASE();
         *ictlr = &ictrl->ICR[index];
         *maskr = &ictrl->IMRH;
         *bit = 1 << (index - 32);
         *clear = 0;
         return TRUE;
      } /* Endif */  

      index = index - 64;
  
      if (index < 32) {
         ictrl = PSP_GET_ICTRL1_BASE();
         *ictlr = &ictrl->ICR[index];
         *maskr = &ictrl->IMRL;
         *bit = 1 << (index);
         *clear = 0;
         return TRUE;
      } /* Endif */  

      if (index < 64) {
         ictrl = PSP_GET_ICTRL1_BASE();
         *ictlr = &ictrl->ICR[index];
         *maskr = &ictrl->IMRH;
         *bit = 1 << (index - 32);
         *clear = 0;
         return TRUE;
      } /* Endif */  

   } /* Endif */

   return FALSE;

} /* Endbody */


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5227_int_init
* Returned Value  : uint_32
* Comments        :
*   Initialize a specific interrupt in the proper interrupt controller
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5227_int_init
   (
      // [IN] Interrupt number
      PSP_INTERRUPT_TABLE_INDEX irq,

      // [IN] Interrupt priority level
      _int_level                level,

      // [IN] Unmask the interrupt now?
      boolean                   unmask
   )
{ /* Body */

   volatile uchar _PTR_   ictrl;
   volatile uint_32 _PTR_ maskr;
   uint_32 bit, clear, mask;
   uint_32 temp;

   if (compute_icntl_registers(irq, &ictrl, &maskr, &bit, &clear)) {
      temp = _psp_get_sr();
      _psp_set_sr(temp | 0x0700);
      mask = *maskr & ~clear;
      if (!unmask)
         *maskr = mask | bit;
      *ictrl = level & 7;
      if (unmask)
         *maskr = mask & ~bit;
      _psp_set_sr(temp);
      return MQX_OK;
   } /* Endif */

   return MQX_INVALID_PARAMETER;

} /* Endbody */


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5227_int_unmask
* Returned Value  : uint_32
* Comments        :
*   Clear the mask bit that inhibits the interrupt
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5227_int_unmask
   (
      // [IN] Interrupt number
      PSP_INTERRUPT_TABLE_INDEX irq
   )
{ /* Body */

   volatile uchar _PTR_   ictrl;
   volatile uint_32 _PTR_ maskr;
   uint_32 bit, clear, mask;

   if (compute_icntl_registers(irq, &ictrl, &maskr, &bit, &clear)) {
      mask = *maskr & ~clear;
      *maskr = mask & ~bit;
      return MQX_OK;
   } /* Endif */

   return MQX_INVALID_PARAMETER;

} /* Endbody */

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5227_int_mask
* Returned Value  : uint_32
* Comments        :
*   Set the mask bit that inhibits the interrupt
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5227_int_mask
   (
      // [IN] Interrupt number
      PSP_INTERRUPT_TABLE_INDEX irq
   )
{ /* Body */

   volatile uchar _PTR_   ictrl;
   volatile uint_32 _PTR_ maskr;
   uint_32 bit, clear, mask;

   if (compute_icntl_registers(irq, &ictrl, &maskr, &bit, &clear)) {
      mask = *maskr & ~clear;
      *maskr = mask | bit;
      return MQX_OK;
   } /* Endif */

   return MQX_INVALID_PARAMETER;

} /* Endbody */

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5227_int_mask_all
* Returned Value  : void
* Comments        :
*   Mask all external interrupts
*
*END*---------------------------------------------------------------------*/

void  _mcf5227_int_mask_all
   (
      void
   )
{ /* Body */

   /* Mask all the interrupt requests by writing a data value greater than 63 */
   PSP_GET_ICTRL0_BASE()->SIMR = 64;
   PSP_GET_ICTRL1_BASE()->SIMR = 64;

} /* Endbody */

/* EOF */

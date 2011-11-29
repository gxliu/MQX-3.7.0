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
* $FileName: int_ctrl_mcf532.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains definitions for the MFC5329 interrupt controller
*   functions.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h"

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5329_int_init
* Returned Value  : uint_32
* Comments        :
*   Initialize a specific interrupt in the proper interrupt controller
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5329_int_init
   (
      /* [IN} Interrupt number */
      PSP_INTERRUPT_TABLE_INDEX irq,

      /* [IN} Interrupt priority level */
      _int_level                level,

      /* [IN} Unmask the interrupt now? */
      boolean                   unmask
   )
{
    _mqx_int idx;
    uint_32 temp;

    if (irq >= PSP_INT_FIRST_EXTERNAL) {
        idx = irq - PSP_INT_FIRST_EXTERNAL;
   
        temp = _psp_get_sr();
        _psp_set_sr(temp | 0x0700);
        
        if (idx < 64) {
            PSP_GET_ICTRL0_BASE()->ICR[idx] = level & 7;
            
            if (unmask)
                PSP_GET_ICTRL0_BASE()->CIMR = MCF53XX_ICTRL_IMR_N(idx);
            else
                PSP_GET_ICTRL0_BASE()->SIMR = MCF53XX_ICTRL_IMR_N(idx);
        }
        else {
            idx -= 64;
            PSP_GET_ICTRL1_BASE()->ICR[idx] = level & 7;
            
            if (unmask)
                PSP_GET_ICTRL1_BASE()->CIMR = MCF53XX_ICTRL_IMR_N(idx);
            else
                PSP_GET_ICTRL1_BASE()->SIMR = MCF53XX_ICTRL_IMR_N(idx);
        }
        
        _psp_set_sr(temp);
    
        return MQX_OK;
    }
    
    return MQX_INVALID_PARAMETER;

}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5329_int_unmask
* Returned Value  : uint_32
* Comments        :
*   Clear the mask bit that inhibits the interrupt
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5329_int_unmask
   (
      /* [IN} Interrupt number */
      PSP_INTERRUPT_TABLE_INDEX irq
   )
{ /* Body */
    _mqx_int idx;

    if (irq >= PSP_INT_FIRST_EXTERNAL) {
        idx = irq - PSP_INT_FIRST_EXTERNAL;
   
        if (idx < 64) {
            PSP_GET_ICTRL0_BASE()->CIMR = MCF53XX_ICTRL_IMR_N(idx);
        }
        else {
            PSP_GET_ICTRL1_BASE()->CIMR = MCF53XX_ICTRL_IMR_N(idx - 64);
        }
    
        return MQX_OK;
    }
    
    return MQX_INVALID_PARAMETER;
} /* Endbody */


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5329_int_mask
* Returned Value  : uint_32
* Comments        :
*   Set the mask bit that inhibits the interrupt
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5329_int_mask
   (
      /* [IN} Interrupt number */
      PSP_INTERRUPT_TABLE_INDEX irq
   )
{
    _mqx_int idx;

    if (irq >= PSP_INT_FIRST_EXTERNAL) {
        idx = irq - PSP_INT_FIRST_EXTERNAL;
   
        if (idx < 64) {
            PSP_GET_ICTRL0_BASE()->SIMR = MCF53XX_ICTRL_IMR_N(idx);
        }
        else {
            PSP_GET_ICTRL1_BASE()->SIMR = MCF53XX_ICTRL_IMR_N(idx - 64);
        }
    
        return MQX_OK;
    }
    
    return MQX_INVALID_PARAMETER;
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5329_int_mask_all
* Returned Value  : void
* Comments        :
*   Mask all external interrupts
*
*END*---------------------------------------------------------------------*/

void  _mcf5329_int_mask_all
   (
      void
   )
{ /* Body */

   PSP_GET_ICTRL0_BASE()->SIMR = MCF53XX_ICTRL_IMR_ALL;
   PSP_GET_ICTRL1_BASE()->SIMR = MCF53XX_ICTRL_IMR_ALL;

} /* Endbody */

/* EOF */

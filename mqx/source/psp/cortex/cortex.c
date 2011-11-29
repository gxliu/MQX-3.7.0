/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
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
* $FileName: cortex.c$
* $Version : 3.7.6.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the type definitions for the ARM Cortex processors.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "cortex.h"

#if !MQX_USE_IDLE_TASK
#error "MQX for ARM Cortex M require enabled MQX_USE_IDLE_TASK !!!"
#endif

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _cortex_int_init
* Returned Value  : uint_32
* Comments        :
*  	Initialize a specific interrupt in the cortex core nvic
*
*END*---------------------------------------------------------------------*/

uint_32 _cortex_int_init
   (
      // [IN} Interrupt number
      _mqx_uint     irq,

      // [IN} Interrupt priority
      _int_priority prior,

      // [IN] enable the interrupt now?
      boolean       enable
   )
{
	VCORTEX_NVIC_STRUCT_PTR nvic = (VCORTEX_NVIC_STRUCT_PTR)&(((CORTEX_SCS_STRUCT_PTR)CORTEX_PRI_PERIPH_IN_BASE)->NVIC);
        uint_32 mask, ext_irq_no = irq - 16;

	if (irq >= PSP_INT_FIRST_INTERNAL && irq <= PSP_INT_LAST_INTERNAL) {
		nvic->PRIORITY[ext_irq_no >> 2] = (nvic->PRIORITY[ext_irq_no >> 2] & ~(0xff << ((ext_irq_no & 3) * 8))) | (((prior << CORTEX_PRIOR_SHIFT) & CORTEX_PRIOR_MASK) << ((ext_irq_no & 3) * 8));

		if (enable)
			_cortex_int_enable(irq);
		else
			_cortex_int_disable(irq);

    }
    else
        return MQX_INVALID_PARAMETER;
        
    return MQX_OK;
}

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _cortex_int_enable
* Returned Value  : uint_32
* Comments        :
* 	Enable interrupt on cortex core NVIC
*
*END*---------------------------------------------------------------------*/
uint_32 _cortex_int_enable
   (
      // [IN] Interrupt number
      _mqx_uint  irq
   )
{
    VCORTEX_NVIC_STRUCT_PTR nvic = (VCORTEX_NVIC_STRUCT_PTR)&(((CORTEX_SCS_STRUCT_PTR)CORTEX_PRI_PERIPH_IN_BASE)->NVIC);
    uint_32 ext_irq_no = irq - 16;

    if (ext_irq_no >= PSP_INT_FIRST_INTERNAL && ext_irq_no <= PSP_INT_LAST_INTERNAL) {
        nvic->ENABLE[ext_irq_no >> 5] = 1 << (ext_irq_no & 0x1f);
    }
    else
        return MQX_INVALID_PARAMETER;

    return MQX_OK;
}

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _cortex_int_disable
* Returned Value  : uint_32
* Comments        :
* 	Disable interrupt on cortex core NVIC
*
*END*---------------------------------------------------------------------*/

uint_32 _cortex_int_disable
   (
      // [IN] Interrupt number
      _mqx_uint  irq
   )
{
    VCORTEX_NVIC_STRUCT_PTR nvic = (VCORTEX_NVIC_STRUCT_PTR)&(((CORTEX_SCS_STRUCT_PTR)CORTEX_PRI_PERIPH_IN_BASE)->NVIC);
    uint_32 ext_irq_no = irq - 16;

    if (ext_irq_no >= PSP_INT_FIRST_INTERNAL && ext_irq_no <= PSP_INT_LAST_INTERNAL) {
        nvic->DISABLE[ext_irq_no >> 5] = 1 << (ext_irq_no & 0x1f);
    }
    else
        return MQX_INVALID_PARAMETER;
        
    return MQX_OK;
}

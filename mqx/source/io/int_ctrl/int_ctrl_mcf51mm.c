/**HEADER********************************************************************
* 
* Copyright (c) 2009 Freescale Semiconductor;
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
* $FileName: int_ctrl_mcf51mm.c$
* $Version : 3.6.2.0$
* $Date    : Jun-7-2010$
*
* Comments:
*
*   This file contains definitions for the MFC51MM interrupt controller
*   functions.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h"

static uint_16 irq_levels_sw_stack;


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf51MM_int_mask_all
* Returned Value  : void
* Comments        :
*   Mask all interrupts (setting actual int level to 7)
*
*END*---------------------------------------------------------------------*/

void  _mcf51MM_int_mask_all
   (
      void
   )
{ /* Body */
   irq_levels_sw_stack = _psp_get_sr();
   _psp_set_sr(0x2700);
} /* Endbody */

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf51ac_int_unmask_all
* Returned Value  : void
* Comments        :
*   Unmask all interrupts (restoring actual int level from 7)
*
*END*---------------------------------------------------------------------*/

void  _mcf51MM_int_unmask_all
   (
      void
   )
{ /* Body */
   _psp_set_sr(irq_levels_sw_stack);
} /* Endbody */

/*FUNCTION****************************************************************
* 
* Function Name    : _bsp_get_int_base_address
* Returned Value   : pointer to base of INTC registers
* Comments         :
*    This function returns base address of INT related register space.
*
*END*********************************************************************/
pointer _bsp_get_int_base_address 
(
    void
)
{
    return (pointer) 0xFFFFFFC0;
}

/* EOF */

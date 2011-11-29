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
* $FileName: int_ctrl_mcf51jm.c$
* $Version : 3.6.3.0$
* $Date    : Jun-7-2010$
*
* Comments:
*
*   This file contains definitions for the MFC51JM interrupt controller
*   functions.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h"

static uint_16 irq_levels_sw_stack;


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf51jm_software_int
* Returned Value  : void
* Comments        :
*   Mask all interrupts (setting actual int level to 7)
*
*END*---------------------------------------------------------------------*/

void  _mcf51JM_int_mask_all
   (
      void
   )
{ /* Body */
   irq_levels_sw_stack = _psp_get_sr();
   _psp_set_sr(0x2700);
} /* Endbody */

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf51jm_int_unmask_all
* Returned Value  : void
* Comments        :
*   Unmask all interrupts (restoring actual int level from 7)
*
*END*---------------------------------------------------------------------*/

void  _mcf51JM_int_unmask_all
   (
      void
   )
{ /* Body */
   _psp_set_sr(irq_levels_sw_stack);
} /* Endbody */

/* EOF */

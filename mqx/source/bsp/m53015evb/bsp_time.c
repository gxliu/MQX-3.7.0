/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: bsp_time.c$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*   This file contains MCF5301x time utility functions
*   $Header:bsp_time.c, 2, 9/9/2004 2:44:36 PM, Goutham D. R.$
*   $NoKeywords$
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_elapsed_time
* Returned Value   : none
* Comments         :
*
*END*----------------------------------------------------------------------*/

void _bsp_spin_time
   (
      /* [IN] number of microseconds to wait */
      uint_32 us
   )
{ /* Body */

   uint_32 inst_per_us = BSP_SYSTEM_CLOCK / 1000000;
   uint_32 inst_to_exec = us * inst_per_us;

   /*
   ** This is actually too long.  The nop is serializing
   ** so we'll only perform 1 then sync the entire pipeline.
   ** So if the pipeline is 6 deep then this loop is 6 times
   ** longer than the user requested.  The PowerPC had a
   ** timebase register that we could really be wall clock
   ** accurate with.  We need something like that here.
   */
   for (; inst_to_exec != 0; inst_to_exec--) {
      _ASM_NOP();
   } /* Endfor */

} /* Endbody */

/* EOF */

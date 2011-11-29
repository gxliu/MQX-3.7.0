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
* $FileName: timer_mcf532.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains definitions for the MCF5329 programmable
*   interrupt timer utility functions.
*
*END************************************************************************/

#ifndef __timer_mcf532_h__
#define __timer_mcf532_h__

#ifndef __int_ctrl_mcf532_h__
#include <int_ctrl_mcf532.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                      DEFINITIONS
*/

typedef struct mcf5329_timer_init_struct {
   MCF5329_INTERRUPT_TABLE_INDEX	INTERRUPT;
   mcf5329_int_priority				LEVEL;
/*   mcf5329_int_subpriority			SUBLEVEL;*/
} MCF5329_TIMER_INIT_STRUCT, _PTR_ MCF5329_TIMER_INIT_STRUCT_PTR;

#define _mcf5329_timer_mask_int(timer)      _mcf5329_int_mask(_bsp_timers[timer].INTERRUPT)
#define _mcf5329_timer_unmask_int(timer)    _mcf5329_int_unmask(_bsp_timers[timer].INTERRUPT)

#define _mcf5329_timer_clear_int(timer) {                       \
   VMCF5329_STRUCT_PTR    _reg_ptr = _PSP_GET_IPSBAR();         \
   volatile uint_16 _PTR_ _pcsr = &_reg_ptr->PIT[timer].PCSR;   \
   *_pcsr |= MCF5XXX_PIT_PCSR_PIF; }                            \
   /* END OF _mcf5329_timer_clear_int */


/*-----------------------------------------------------------------------*/
/*                      FUNCTION PROTOTYPES
*/

extern const MCF5329_TIMER_INIT_STRUCT _bsp_timers[];

extern uint_32 _mcf5329_timer_init_freq(_mqx_uint, uint_32, uint_32, boolean unmask);
extern uint_32 _mcf5329_timer_init_int(_mqx_uint, uint_32, uint_32, boolean unmask);
extern uint_32 _mcf5329_get_hwticks(_mqx_uint);
extern uint_32 _mcf5329_timer_get_nsec(_mqx_uint, uint_32);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

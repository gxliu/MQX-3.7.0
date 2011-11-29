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
* $FileName: timer_mcf5227.h$
* $Version : 3.6.5.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains definitions for the MCF5227 programmable
*   interrupt timer utility functions.
*
*END************************************************************************/

#ifndef __timer_mcf5227_h__
#define __timer_mcf5227_h__

#ifndef __timer_h__
#include <timer.h>
#endif

#ifndef __int_ctrl_mcf5227_h__
#include <int_ctrl_mcf5227.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                      DEFINITIONS

#define MCF5227_PIT_PCSR_PRESCALE_SHIFT 8
#define MCF5227_PIT_PCSR_DOZE           (1<<6)
#define MCF5227_PIT_PCSR_HALTED         (1<<5)
#define MCF5227_PIT_PCSR_OVW            (1<<4)
#define MCF5227_PIT_PCSR_PIE            (1<<3)
#define MCF5227_PIT_PCSR_PIF            (1<<2)
#define MCF5227_PIT_PCSR_RLD            (1<<1)
#define MCF5227_PIT_PCSR_EN             (1<<0)
*/
typedef struct mpc5227_timer_init_struct {
   MCF5227_INTERRUPT_TABLE_INDEX INTERRUPT;
   mcf5227_int_priority          LEVEL;
} MPC5227_TIMER_INIT_STRUCT, _PTR_ MPC5227_TIMER_INIT_STRUCT_PTR;

#define _mcf5227_timer_mask_int(timer) \
   _mcf5227_int_mask(_bsp_timers[timer].INTERRUPT)

#define _mcf5227_timer_unmask_int(timer) \
   _mcf5227_int_unmask(_bsp_timers[timer].INTERRUPT)

#define _mcf5227_timer_clear_int(timer) {                       \
   VMCF5227_STRUCT_PTR    _reg_ptr = _PSP_GET_MBAR();           \
   volatile uint_16 _PTR_ _pcsr = &_reg_ptr->PIT[timer].PCSR;   \
   *_pcsr |= MCF5XXX_PIT_PCSR_PIF; }                            \
   /* END OF _mcf5227_timer_clear_int */


/*-----------------------------------------------------------------------*/
/*                      FUNCTION PROTOTYPES
*/

extern MPC5227_TIMER_INIT_STRUCT _bsp_timers[];

extern uint_32 _mcf5227_timer_init_freq(_timer_id, uint_32, uint_32, boolean);
extern uint_32 _mcf5227_timer_init_int(_timer_id, uint_32, uint_32, boolean);
extern uint_32 _mcf5227_get_hwticks(_timer_id);
extern uint_32 _mcf5227_timer_get_nsec(_timer_id, uint_32);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

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
* $FileName: timer_mcf51em.h$
* $Version : 3.4.1.0$
* $Date    : Oct-16-2009$
*
* Comments:
*
*   This file contains definitions for the MCF51EM programmable
*   interrupt timer utility functions.
*
*END************************************************************************/

#ifndef __timer_mcf51em_h__
#define __timer_mcf51em_h__

#ifndef __int_ctrl_mcf51em_h__
#include <int_ctrl_mcf51em.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                      DEFINITIONS
*/

         
#define _mcf51EM_timer_mask_int(timer) {             \
   MCF51EM_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();    \
   if(timer == 0)                                    \
     reg_ptr->MTIM1.MTIMSC = 0;                      \
   else                                              \
     reg_ptr->MTIM2.MTIMSC = 0;}                     \

#define _mcf51EM_timer_unmask_int(timer) {           \
   MCF51EM_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();    \
   if(timer == 0)                                    \
     reg_ptr->MTIM1.MTIMSC = MCF51XX_MTIMSC_TRST_MASK | MCF51XX_MTIMSC_TOIE_MASK;\
   else                                              \
     reg_ptr->MTIM2.MTIMSC = MCF51XX_MTIMSC_TRST_MASK | MCF51XX_MTIMSC_TOIE_MASK;}\



#define _mcf51EM_timer_clear_int(timer) {              \
   MCF51EM_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();      \
   if(timer == 0)                                      \
     reg_ptr->MTIM1.MTIMSC &= ~MCF51XX_MTIMSC_TOF_MASK;\
   else                                                \
     reg_ptr->MTIM2.MTIMSC &= ~MCF51XX_MTIMSC_TOF_MASK;\
}\
/* END OF _mcf51EM_timer_clear_int */


/*-----------------------------------------------------------------------*/
/*                      FUNCTION PROTOTYPES
*/


extern uint_32 _mcf51EM_timer_init_freq(_mqx_uint, uint_32, boolean unmask);
extern uint_32 _mcf51EM_timer_init_int(_mqx_uint, uint_32, boolean unmask);
extern uint_32 _mcf51EM_get_hwticks(_mqx_uint);
extern uint_32 _mcf51EM_timer_get_nsec(_mqx_uint, uint_32);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

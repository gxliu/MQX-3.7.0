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
* $FileName: timer_mcf51ac.h$
* $Version : 3.6.1.0$
* $Date    : May-18-2010$
*
* Comments:
*
*   This file contains definitions for the MCF51CN programmable
*   interrupt timer utility functions.
*
*END************************************************************************/

#ifndef __timer_mcf51ac_h__
#define __timer_mcf51ac_h__

#ifndef __int_ctrl_mcf51ac_h__
#include <int_ctrl_mcf51ac.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                      DEFINITIONS
*/

         
#define _mcf51AC_timer_mask_int(timer) {             \
   MCF51AC_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();    \
     reg_ptr->TPM3.TPMxSC &= 3f;  \
}

#define _mcf51AC_timer_unmask_int(timer) {           \
   MCF51AC_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();    \
     reg_ptr->TPM3.TPMxSC |= MCF51XX_TPMxSC_TOIE_MASK ; \
}

#define _mcf51AC_timer_clear_int(timer) {              \
   MCF51AC_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();      \
     reg_ptr->TPM3.TPMxSC &= ~MCF51XX_TPMxSC_TOF_MASK;\
}
/* END OF _mcf51JM_timer_clear_int */


/*-----------------------------------------------------------------------*/
/*                      FUNCTION PROTOTYPES
*/


extern uint_32 _mcf51AC_timer_init_freq(_mqx_uint, uint_32, boolean unmask);
extern uint_32 _mcf51AC_timer_init_int(_mqx_uint, uint_32, boolean unmask);
extern uint_32 _mcf51AC_get_hwticks(_mqx_uint);
extern uint_32 _mcf51AC_timer_get_nsec(_mqx_uint, uint_32);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

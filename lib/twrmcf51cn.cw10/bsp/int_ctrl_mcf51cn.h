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
* $FileName: int_ctrl_mcf51cn.h$
* $Version : 3.0.4.0$
* $Date    : Apr-22-2009$
*
* Comments:
*
*   This file contains definitions for the Coldfire interrupt
*   controller in the MCF51CN.
*
*END************************************************************************/
#ifndef __int_ctrl_mcf51cn_h__
#define __int_ctrl_mcf51cn_h__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*
**                       TYPE DEFINITIONS
**
** The PSP must provide a type or define:
**
**   PSP_INTERRUPT_TABLE_INDEX  - Defines the interrupt table indexes.
**   PSP_INT_FIRST_EXTERNAL     - First external interrupt number used by
**                                this interrupt controller as ICR00.
*/

#define PSP_INTERRUPT_TABLE_INDEX  MCF51CN_INTERRUPT_TABLE_INDEX
#define PSP_INT_FIRST_EXTERNAL     MCF51CN_INT_FIRST_EXTERNAL

/* Interrupt level */
typedef uchar _int_level;

/* Interrupt Acknowledge Level and Priority Register
**
** Interrupt priority can range 0 (lowest) to 7 (highest priority) and
** a special value 8 (mid-point) for fixed level interrupts
*/
typedef uchar _int_priority;


/*****************************************************************************/
/*
**                      FUNCTION PROTOTYPES
*/


extern void    _mcf51CN_int_unmask_all(void);
extern void    _mcf51CN_int_mask_all(void);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

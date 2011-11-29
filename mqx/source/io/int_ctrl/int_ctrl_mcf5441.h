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
* $FileName: int_ctrl_mcf5441.h$
* $Version : 3.6.3.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains definitions for the Coldfire interrupt
*   controller in the MCF5445.
*
*END************************************************************************/
#ifndef __int_ctrl_mcf5441_h__
#define __int_ctrl_mcf5441_h__

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

#define mcf5441_int_priority       _int_level
#define PSP_INTERRUPT_TABLE_INDEX  MCF5441_INTERRUPT_TABLE_INDEX
#define PSP_INT_FIRST_EXTERNAL     MCF5441_INT_FIRST_EXTERNAL

/* Interrupt level */
typedef uchar _int_level;

/* Interrupt Acknowledge Level and Priority Register
**
** Interrupt priority can range 0 (lowest) to 7 (highest priority) and
** a special value 8 (mid-point) for fixed level interrupts
*/
typedef uchar _int_priority;

#define _interrupt_controller_mask(irq)     _mcf5441_int_mask(irq)
#define _interrupt_controller_unmask(irq)   _mcf5441_int_unmask(irq)

/*****************************************************************************/
/*
**                      FUNCTION PROTOTYPES
*/

uint_32 _mcf5441_int_init(PSP_INTERRUPT_TABLE_INDEX, _int_level, boolean unmask);
uint_32 _mcf5441_int_unmask(PSP_INTERRUPT_TABLE_INDEX);
uint_32 _mcf5441_int_mask(PSP_INTERRUPT_TABLE_INDEX);
void    _mcf5441_int_mask_all(void);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

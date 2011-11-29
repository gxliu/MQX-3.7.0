/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: mcf5xxx_pit.h$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf522xx PIT module.
*
*END************************************************************************/

#ifndef __mcf5xxx_pit_h__
#define __mcf5xxx_pit_h__

#define __mcf5xxx_pit_h__version "$Version:3.6.2.0$"
#define __mcf5xxx_pit_h__date    "$Date:Jun-4-2010$"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
** PIT  registers bit set.
*/

/* Bit definitions and macros for MCF54XX_PIT_PCSR */


#define MCF5XXX_PIT_PCSR_EN                      (0x1)
#define MCF5XXX_PIT_PCSR_RLD                     (0x2)
#define MCF5XXX_PIT_PCSR_PIF                     (0x4)
#define MCF5XXX_PIT_PCSR_PIE                     (0x8)
#define MCF5XXX_PIT_PCSR_PRESCALE_SHIFT           8
#define MCF5XXX_PIT_PCSR_OVW                     (0x10)
#define MCF5XXX_PIT_PCSR_DBG                     (0x20)
#define MCF5XXX_PIT_PCSR_HALTED                  (1<<5)
#define MCF5XXX_PIT_PCSR_DOZE                    (0x40)
#define MCF5XXX_PIT_PCSR_PRE(x)                  (((x) & 0xF) << 8)

/* Bit definitions and macros for MCF5XXX_PIT_PMR */
#define MCF5XXX_PIT_PMR_PM(x)                    (((x)&0xFFFF) << 0)

/* Bit definitions and macros for MCF5XXX_PIT_PCNTR */
#define MCF5XXX_PIT_PCNTR_PC(x)                  (((x)&0xFFFF) << 0)

/*
** MCF5XXX_PIT_STRUCT                                                                  
** Programmable interrupt timer
*/
typedef struct mcf5xxx_pit_struct
{
   uint_16  PCSR;           // PIT control and status register
   uint_16  PMR;            // PIT modulus register
   uint_16  PCNTR;          // PIT count register
   uchar    filler[0x3FFA];
} MCF5XXX_PIT_STRUCT, _PTR_ MCF5XXX_PIT_STRUCT_PTR;
typedef volatile struct mcf5xxx_pit_struct _PTR_ VMCF5XXX_PIT_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif  //__mcf5xxx_pit_h__

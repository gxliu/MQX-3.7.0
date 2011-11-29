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
* $FileName: mcf51xx_ictl.h$
* $Version : 3.5.3.0$
* $Date    : Feb-24-2010$
*
* Comments:
*
*   This file contains the interrupt controller type definitions for
*   the mcf51xx processor.  It has been split out into a separate header
*   file to share with other Coldfire PSP's.
*
*END************************************************************************/

#ifndef __mcf51xx_ictl_h__
#define __mcf51xx_ictl_h__

#define __mcf51xx_ictl_h__version "$Version:3.5.3.0$"
#define __mcf51xx_ictl_h__date    "$Date:Feb-24-2010$"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------------------------------------*/
/*
** Interrupt definitions
*/

#define MCF51XX_INTC_ORMR_FECDO              (0x80)
#define MCF51XX_INTC_ORMR_SCI3DO             (0x20)

#define MCF51XX_INTC_FRC_LVL1                (0x40)
#define MCF51XX_INTC_FRC_LVL2                (0x20)
#define MCF51XX_INTC_FRC_LVL3                (0x10)
#define MCF51XX_INTC_FRC_LVL4                (0x08)
#define MCF51XX_INTC_FRC_LVL5                (0x04)
#define MCF51XX_INTC_FRC_LVL6                (0x02)
#define MCF51XX_INTC_FRC_LVL7                (0x01)

#define MCF51XX_INTC_WCR_ENB                 (0x80)
#define MCF51XX_INTC_WCR_MASK                (0x07)

#define MCF51XX_INTC_SFRC_LVL1               (0x3E)
#define MCF51XX_INTC_SFRC_LVL2               (0x3D)
#define MCF51XX_INTC_SFRC_LVL3               (0x3C)
#define MCF51XX_INTC_SFRC_LVL4               (0x3B)
#define MCF51XX_INTC_SFRC_LVL5               (0x3A)
#define MCF51XX_INTC_SFRC_LVL6               (0x39)
#define MCF51XX_INTC_SFRC_LVL7               (0x38)

#define MCF51XX_INTC_CFRC_LVL1               (0x3E)
#define MCF51XX_INTC_CFRC_LVL2               (0x3D)
#define MCF51XX_INTC_CFRC_LVL3               (0x3C)
#define MCF51XX_INTC_CFRC_LVL4               (0x3B)
#define MCF51XX_INTC_CFRC_LVL5               (0x3A)
#define MCF51XX_INTC_CFRC_LVL6               (0x39)
#define MCF51XX_INTC_CFRC_LVL7               (0x38)

/*
** Interrupt controller
*/
typedef struct mcf51xx_int_ctrl_struct
{
   uint_8  reserved00[0x0D];
   uint_8  ORMR;                // OR / Mask register
   uint_8  reserved01[5];
   uint_8  FRC;                 // Force interrupt register
   uint_8  reserved02[4];
   uint_8  PL6P7;               // Level 6, Priority 7 IRQ Register
   uint_8  PL6P6;               // Level 6, Priority 5 IRQ Register
   uint_8  reserved03[1];
   uint_8  WCR;                 // Wake-up Control Register
   uint_8  reserved04[2];
   uint_8  SFRC;                // Set Interrupt Force Register
   uint_8  CFRC;                // Clear Interrupt Force Register
   uint_8  SWIACK;              // Software Interrupt Acknowledge
   uint_8  reserved05[3];
   uint_8  LVL1IACK;            // Level 1 Interrupt Acknowledge
   uint_8  reserved06[3];
   uint_8  LVL2IACK;            // Level 2 Interrupt Acknowledge
   uint_8  reserved07[3];
   uint_8  LVL3IACK;            // Level 3 Interrupt Acknowledge
   uint_8  reserved08[3];
   uint_8  LVL4IACK;            // Level 4 Interrupt Acknowledge
   uint_8  reserved09[3];
   uint_8  LVL5IACK;            // Level 5 Interrupt Acknowledge
   uint_8  reserved10[3];
   uint_8  LVL6IACK;            // Level 6 Interrupt Acknowledge
   uint_8  reserved11[3];
   uint_8  LVL7IACK;            // Level 7 Interrupt Acknowledge
} MCF51XX_INT_CTRL_STRUCT, _PTR_ MCF51XX_INT_CTRL_STRUCT_PTR;
typedef volatile struct mcf51xx_int_ctrl_struct _PTR_ VMCF51XX_INT_CTRL_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif /* __mcf51xx_ictl_h__ */
/* EOF */

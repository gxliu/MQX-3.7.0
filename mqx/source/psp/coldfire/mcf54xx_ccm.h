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
* $FileName: mcf54xx_ccm.h$
* $Version : 3.5.9.0$
* $Date    : Feb-24-2010$
*
* Comments:
*
*   This file contains the SCM type definitions for the mcf54xx processor.
*   It has been split out into a separate header file to share with 
*   other Coldfire PSP's.
*
*END************************************************************************/

#ifndef __mcf54xx_ccm_h__
#define __mcf54xx_ccm_h__

#define __mcf54xx_ccm_h__version "$Version:3.5.9.0$"
#define __mcf54xx_ccm_h__date    "$Date:Feb-24-2010$"

#ifdef __cplusplus
extern "C" {
#endif

#define MCF54XX_CCM_MISCCR_USBSRC               (0x1)
#define MCF54XX_CCM_MISCCR_USBOC                (0x2)
#define MCF54XX_CCM_MISCCR_USBPUE               (0x4)
#define MCF54XX_CCM_MISCCR_SSISRC               (0x10)
#define MCF54XX_CCM_MISCCR_TIMDMA               (0x20)
#define MCF54XX_CCM_MISCCR_SSIPUS               (0x40)
#define MCF54XX_CCM_MISCCR_SSIPUE               (0x80)
#define MCF54XX_CCM_MISCCR_BMT(x)               (((x) & 7) << 8)
#define MCF54XX_CCM_MISCCR_BMT_65536            (0)
#define MCF54XX_CCM_MISCCR_BMT_32768            (0x100)
#define MCF54XX_CCM_MISCCR_BMT_16384            (0x200)
#define MCF54XX_CCM_MISCCR_BMT_8192             (0x300)
#define MCF54XX_CCM_MISCCR_BMT_4096             (0x400)
#define MCF54XX_CCM_MISCCR_BMT_2048             (0x500)
#define MCF54XX_CCM_MISCCR_BMT_1024             (0x600)
#define MCF54XX_CCM_MISCCR_BMT_512              (0x700)
#define MCF54XX_CCM_MISCCR_BME                  (0x800)
#define MCF54XX_CCM_MISCCR_LIMP                 (0x1000)
#define MCF54XX_CCM_MISCCR_PLL_LOCK             (1 << 13)

/*
** MCF54XX_CCM_STRUCT
** ColdFire Integration Module
*/
typedef struct mcf54xx_ccm_struct {
#if PSP_MQX_CPU_IS_MCF5441X
    uchar   RCR;
    uchar   RSR;
    uchar   filler1[2];
#else // !PSP_MQX_CPU_IS_MCF5441X
    uchar   filler1[4];
#endif
    uint_16 CCR;            // Chip Configuration Register
    uint_16 filler2;
    uint_16 RCON;           // Reset Configuration Register
    uint_16 CIR;            // Chip Identification Register
#if PSP_MQX_CPU_IS_MCF5441X
    uchar   filler3[2];
    uint_16 MISCCR;         // Miscellaneous Control Register
    uint_16 CDRH;           // Clock Divider Register
    uint_16 CDRL;           // Clock Divider Register
    uint_16 UOCSR;          // USB On-the-Go Controller Status Register
    uint_16 UHCSR;          // USB Host Controller Status Register
    uint_16 MISCCR3;        // Miscellaneous control register 3
    uint_16 MISCCR2;        // Miscellaneous control register 2
    uint_16 ADCTSR;         // ADC trigger select register
    uint_16 DACTSR;         // DAC trigger select register
    uint_16 SBFSR;          // Serial boot facility status register
    uint_16 SBFCR;          // Serial boot facility control register
    uint_16 FNACR;          // FlexBus/NAND flash arbiter control register
#else  // !PSP_MQX_CPU_IS_MCF5441X
    uchar   filler3[4];
    uint_16 MISCCR;         // Miscellaneous Control Register
    uint_16 CDR;            // Clock Divider Register
    uint_16 UOCSR;          // USB On-the-Go Controller Status Register
    uint_8  filler4[2];
    uint_16 SBFSR;          // Serial Boot Facility Status Register
    uint_16 SBFCR;          // Serial Boot Facility Control Register
#endif
} MCF54XX_CCM_STRUCT, _PTR_ MCF54XX_CCM_STRUCT_PTR;
typedef volatile struct mcf54xx_ccm_struct _PTR_ VMCF54XX_CCM_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif /* __mcf54xx_ccm_h__ */

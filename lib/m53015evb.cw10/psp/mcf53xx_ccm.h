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
* $FileName: mcf53xx_ccm.h$
* $Version : 3.7.3.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the SCM type definitions for the mcf53xx processor.
*   It has been split out into a separate header file to share with 
*   other Coldfire PSP's.
*
*END************************************************************************/

#ifndef __mcf53xx_ccm_h__
#define __mcf53xx_ccm_h__

#define __mcf53xx_ccm_h__version "$Version:3.7.3.0$"
#define __mcf53xx_ccm_h__date    "$Date:Feb-7-2011$"

#ifdef __cplusplus
extern "C" {
#endif

#define MCF53XX_CCM_MISCCR_USBSRC               (0x1)
#define MCF53XX_CCM_MISCCR_USBPUE               (0x2)
#define MCF53XX_CCM_MISCCR_USBOOC               (0x4)
#define MCF53XX_CCM_MISCCR_USBHOC               (0x8)
#define MCF53XX_CCM_MISCCR_SSISRC               (0x10)
#define MCF53XX_CCM_MISCCR_TIMDMA               (0x20)
#define MCF53XX_CCM_MISCCR_BMT(x)               (((x) & 7) << 8)
#define MCF53XX_CCM_MISCCR_BMT_65536            (0)
#define MCF53XX_CCM_MISCCR_BMT_32768            (0x100)
#define MCF53XX_CCM_MISCCR_BMT_16384            (0x200)
#define MCF53XX_CCM_MISCCR_BMT_8192             (0x300)
#define MCF53XX_CCM_MISCCR_BMT_4096             (0x400)
#define MCF53XX_CCM_MISCCR_BMT_2048             (0x500)
#define MCF53XX_CCM_MISCCR_BMT_1024             (0x600)
#define MCF53XX_CCM_MISCCR_BMT_512              (0x700)
#define MCF53XX_CCM_MISCCR_BME                  (0x800)
#define MCF53XX_CCM_MISCCR_LIMP                 (0x1000)
#define MCF53XX_CCM_MISCCR_PLL_LOCK             (1 << 13)
#define MCF53XX_CCM_MISCCR_CDCSRC               (0x4000)
#define MCF53XX_CCM_MISCCR_FECM                 (0x8000)

#define MCF53XX_CCM_UOCSR_XPDE                  (0x01)
#define MCF53XX_CCM_UOCSR_UOMIE                 (0x02)
#define MCF53XX_CCM_UOCSR_PWRFLT                (0x08)
#define MCF53XX_CCM_UOCSR_SEND                  (0x10)
#define MCF53XX_CCM_UOCSR_VVLD                  (0x20)
#define MCF53XX_CCM_UOCSR_BVLD                  (0x40)
#define MCF53XX_CCM_UOCSR_AVLD                  (0x80)
#define MCF53XX_CCM_UOCSR_DRVVBUS               (1 << 11)
/*
** MCF53XX_CCM_STRUCT
** ColdFire Integration Module
*/
typedef struct mcf53xx_ccm_struct {
#if PSP_MQX_CPU_IS_MCF5301X
    uchar   RCR;
    uchar   RSR;
    uchar   filler1[2];
#else /* !PSP_MQX_CPU_IS_MCF5301X */
    uchar   filler1[4];
#endif
    uint_16 CCR;            /* Chip Configuration Register */
    uint_16 filler2;
    uint_16 RCON;           /* Reset Configuration Register */
    uint_16 CIR;            /* Chip Identification Register */
#if PSP_MQX_CPU_IS_MCF5301X
    uchar   filler3[4];
    uint_16 MISCCR;         /* Miscellaneous Control Register */
    uint_16 CDR;            /* Clock Divider Register */
    uint_16 UOCSR;          /* USB On-the-Go Controller Status Register */
    uint_16 UHCSR;          /* USB Host Controller Status Register */
    uchar   filler4[2];
    uint_16 CODCR;          /* Codec Control Register */
    uint_16 MISCCR2;        /* Miscellaneous control register 2 */

#else  /* !PSP_MQX_CPU_IS_MCF5301X */
    uchar   filler3[4];
    uint_16 MISCCR;         /* Miscellaneous Control Register */
    uint_16 CDR;            /* Clock Divider Register */
#if PSP_MQX_CPU_IS_MCF532X
    uint_16 UHCSR;          /* USB Host Controller Status Register */
    uint_16 UOCSR;          /* USB On-the-Go Controller Status Register */
#else
    uint_16 UOCSR;          /* USB On-the-Go Controller Status Register */
#endif
    uint_8  filler4[2];
    uint_16 SBFSR;          /* Serial Boot Facility Status Register */
    uint_16 SBFCR;          /* Serial Boot Facility Control Register */
#endif
} MCF53XX_CCM_STRUCT, _PTR_ MCF53XX_CCM_STRUCT_PTR;
typedef volatile struct mcf53xx_ccm_struct _PTR_ VMCF53XX_CCM_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif /* __mcf53xx_ccm_h__ */

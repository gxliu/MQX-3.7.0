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
* $FileName: mcf51JM.h$
* $Version : 3.7.9.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the type definitions for the mcf5225x processors.
*
*END************************************************************************/

#ifndef __mcf51jm_h__
#define __mcf51jm_h__

#define __mcf51jm_h__version "$Version:3.7.9.0$"
#define __mcf51jm_h__date    "$Date:Feb-7-2011$"

#ifndef __ASM__
/* Include registers for modules common to all Coldfire processors */
#include <mcf51xx_ictl.h>       /* CTRL */   
#include <mcf51xx_sci.h>          /* SCI */
#include <mcf51xx_i2c.h>          /* I2C */
#include <mcf51ac_adc.h>
#include <mcf51xx_rtc.h>
#include <mcf5xxx_spi16.h>
#include <mcf51xx_ftsr.h> 
#include <mcf51xx_pmc.h> 
#include <mcf522x_usbotg.h>
#endif // __ASM__

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* Indicate processor type */
#define PSP_MCF51JM                         1

#define PSP_HAS_DSP                         0
#define PSP_HAS_EMAC                        0

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  0
#define PSP_HAS_DATA_CACHE                  0
//#define PSP_CACHE_LINE_SIZE                 (0x10)
#define PSP_STOP_ON_IDLE                    0

/*
/** Test for disable cpu wait mode macro.
*/
#if PSP_STOP_ON_IDLE
   #warning "With PSP_STOP_ON_IDLE and no idle_task USB doesn't recover from wait mode"
#endif

#ifndef __ASM__

#define MCF51JM_NUM_ACRS                    (2)

/* Do you want to verify kernel data can be read and written correctly */
#define PSP_KERNEL_DATA_VERIFY_ENABLE       ((uint_32)__KERNEL_DATA_VERIFY_ENABLE)

/*
** Standard cache macros
*/
#define _DCACHE_FLUSH()
#define _DCACHE_FLUSH_LINE(p)
#define _DCACHE_FLUSH_MBYTES(p, m)
#define _DCACHE_INVALIDATE()
#define _DCACHE_INVALIDATE_LINE(p)
#define _DCACHE_INVALIDATE_MBYTES(p, m)

#define _CACHE_ENABLE(n)
#define _CACHE_DISABLE()

#define _ICACHE_INVALIDATE()
#define _ICACHE_INVALIDATE_LINE(p)
#define _ICACHE_INVALIDATE_MBYTES(p, m)

/*
** Configuration information
*/
#define MCF51JM_NUM_TIMERS                (2) /* MTIM */

#define MCF51XX_SOPT3_PCS0_MASK                 1
#define MCF51XX_SOPT3_PCS1_MASK                 2
#define MCF51XX_SOPT3_CS0_MASK                  4
#define MCF51XX_SOPT3_CS1_MASK                  8
#define MCF51XX_SOPT3_CS2_MASK                  16
#define MCF51XX_SOPT3_PCS_MASK                  3
#define MCF51XX_SOPT3_PCS_BITNUM                0
#define MCF51XX_SOPT3_CS_MASK                   28
#define MCF51XX_SOPT3_CS_BITNUM                 2

#define MCF51XX_SOPT1_COPW_MASK                 1
#define MCF51XX_SOPT1_COPCLKS_MASK              2
#define MCF51XX_SOPT1_COPT0_MASK                4
#define MCF51XX_SOPT1_COPT1_MASK                8
#define MCF51XX_SOPT1_WAITE_MASK                16
#define MCF51XX_SOPT1_STOPE_MASK                32
#define MCF51XX_SOPT1_SL_MASK                   64
#define MCF51XX_SOPT1_COPT_MASK                 12
#define MCF51XX_SOPT1_COPT_BITNUM               2

#define MCF51XX_SRS_LVD_MASK                    2
#define MCF51XX_SRS_LOC_MASK                    4
#define MCF51XX_SRS_ILAD_MASK                   8
#define MCF51XX_SRS_ILOP_MASK                   16
#define MCF51XX_SRS_COP_MASK                    32
#define MCF51XX_SRS_PIN_MASK                    64
#define MCF51XX_SRS_POR_MASK                    128


/*
** Interrupt vector table
*/
typedef enum mcf51jm_interrupt_table_index {
  MCF51JM_INT_INITSP      =       0,
  MCF51JM_INT_INITPC      =       1,
  MCF51JM_INT_Vaccerr     =       2,
  MCF51JM_INT_Vadderr     =       3,
  MCF51JM_INT_Viinstr     =       4,
  MCF51JM_INT_VReserved5  =       5,
  MCF51JM_INT_VReserved6  =       6,
  MCF51JM_INT_VReserved7  =       7,
  MCF51JM_INT_Vprviol     =       8,
  MCF51JM_INT_Vtrace      =       9,
  MCF51JM_INT_Vunilaop    =       10,
  MCF51JM_INT_Vunilfop    =       11,
  MCF51JM_INT_Vdbgi       =       12,
  MCF51JM_INT_VReserved13 =       13,
  MCF51JM_INT_Vferror     =       14,
  MCF51JM_INT_VReserved15 =       15,
  MCF51JM_INT_VReserved16 =       16,
  MCF51JM_INT_VReserved17 =       17,
  MCF51JM_INT_VReserved18 =       18,
  MCF51JM_INT_VReserved19 =       19,
  MCF51JM_INT_VReserved20 =       20,
  MCF51JM_INT_VReserved21 =       21,
  MCF51JM_INT_VReserved22 =       22,
  MCF51JM_INT_VReserved23 =       23,
  MCF51JM_INT_Vspuri      =       24,
  MCF51JM_INT_VReserved25 =       25,
  MCF51JM_INT_VReserved26 =       26,
  MCF51JM_INT_VReserved27 =       27,
  MCF51JM_INT_VReserved28 =       28,
  MCF51JM_INT_VReserved29 =       29,
  MCF51JM_INT_VReserved30 =       30,
  MCF51JM_INT_VReserved31 =       31,
  MCF51JM_INT_Vtrap0      =       32,
  MCF51JM_INT_Vtrap1      =       33,
  MCF51JM_INT_Vtrap2      =       34,
  MCF51JM_INT_Vtrap3      =       35,
  MCF51JM_INT_Vtrap4      =       36,
  MCF51JM_INT_Vtrap5      =       37,
  MCF51JM_INT_Vtrap6      =       38,
  MCF51JM_INT_Vtrap7      =       39,
  MCF51JM_INT_Vtrap8      =       40,
  MCF51JM_INT_Vtrap9      =       41,
  MCF51JM_INT_Vtrap10     =       42,
  MCF51JM_INT_Vtrap11     =       43,
  MCF51JM_INT_Vtrap12     =       44,
  MCF51JM_INT_Vtrap13     =       45,
  MCF51JM_INT_Vtrap14     =       46,
  MCF51JM_INT_Vtrap15     =       47,
  MCF51JM_INT_VReserved48 =       48,
  MCF51JM_INT_VReserved49 =       49,
  MCF51JM_INT_VReserved50 =       50,
  MCF51JM_INT_VReserved51 =       51,
  MCF51JM_INT_VReserved52 =       52,
  MCF51JM_INT_VReserved53 =       53,
  MCF51JM_INT_VReserved54 =       54,
  MCF51JM_INT_VReserved55 =       55,
  MCF51JM_INT_VReserved56 =       56,
  MCF51JM_INT_VReserved57 =       57,
  MCF51JM_INT_VReserved58 =       58,
  MCF51JM_INT_VReserved59 =       59,
  MCF51JM_INT_VReserved60 =       60,
  MCF51JM_INT_Vunsinstr   =       61,
  MCF51JM_INT_VReserved62 =       62,
  MCF51JM_INT_VReserved63 =       63,
  MCF51JM_INT_Virq        =       64,
  MCF51JM_INT_Vlvd        =       65,
  MCF51JM_INT_Vlol        =       66,
  MCF51JM_INT_Vspi1       =       67,
  MCF51JM_INT_Vspi2       =       68,
  MCF51JM_INT_Vusb        =       69,
  MCF51JM_INT_VReserved70 =       70,  
  MCF51JM_INT_Vtpm1ch0    =       71,
  MCF51JM_INT_Vtpm1ch1    =       72,
  MCF51JM_INT_Vtpm1ch2    =       73,
  MCF51JM_INT_Vtpm1ch3    =       74,  
  MCF51JM_INT_Vtpm1ch4    =       75,
  MCF51JM_INT_Vtpm1ch5    =       76,
  MCF51JM_INT_Vtpm1ovf    =       77,
  MCF51JM_INT_Vtpm2ch0    =       78,
  MCF51JM_INT_Vtpm2ch1    =       79,
  MCF51JM_INT_Vtpm2ovf    =       80,
  MCF51JM_INT_Vsci1err    =       81,
  MCF51JM_INT_Vsci1rx     =       82,
  MCF51JM_INT_Vsci1tx     =       83,
  MCF51JM_INT_Vsci2err    =       84,
  MCF51JM_INT_Vsci2rx     =       85,
  MCF51JM_INT_Vsci2tx     =       86,
  MCF51JM_INT_Vkeyboard   =       87,
  MCF51JM_INT_Vadc        =       88,  
  MCF51JM_INT_Vacmp       =       89,  
  MCF51JM_INT_Viic1       =       90,
  MCF51JM_INT_Vrtc        =       91,  
  MCF51JM_INT_Viic2       =       92,
  MCF51JM_INT_Vcmt        =       93,
  MCF51JM_INT_Vcanwu      =       94,
  MCF51JM_INT_Vcanerr     =       95,
  MCF51JM_INT_Vcanrx      =       96,
  MCF51JM_INT_Vcantx      =       97,
  MCF51JM_INT_Vrnga       =       98,    
  MCF51JM_INT_VReserved99 =       99,  
  MCF51JM_INT_VReserved100 =      100,  
  MCF51JM_INT_VReserved101 =      101,  
  MCF51JM_INT_VReserved102 =      102,  
  MCF51JM_INT_VReserved103 =      103,  
  MCF51JM_INT_VL7swi      =       104,
  MCF51JM_INT_VL6swi      =       105,
  MCF51JM_INT_VL5swi      =       106,
  MCF51JM_INT_VL4swi      =       107,
  MCF51JM_INT_VL3swi      =       108,
  MCF51JM_INT_VL2swi      =       109,
  MCF51JM_INT_VL1swi      =       110
} MCF51JM_INTERRUPT_TABLE_INDEX;//, PSP_INTERRUPT_TABLE_INDEX;


/*------------------------------------------------------------------------*/
/*
** MTIM Modulo Timer
*/

#define MCF51XX_TPMxSC_TOIE_MASK               0x40
#define MCF51XX_TPMxSC_TOF_MASK                0x80

#define MCF51XX_TPMxSC_CLK_BUSCLK              0x08
#define MCF51XX_TPMxSC_CLK_SYSCLK              0x10


#define MCF51XX_MTIMSC_TSTP_MASK               16
#define MCF51XX_MTIMSC_TRST_MASK               32
#define MCF51XX_MTIMSC_TOIE_MASK               64
#define MCF51XX_MTIMSC_TOF_MASK                128

#define MCF51XX_MTIMCLK_PS0_MASK               1
#define MCF51XX_MTIMCLK_PS1_MASK               2
#define MCF51XX_MTIMCLK_PS2_MASK               4
#define MCF51XX_MTIMCLK_PS3_MASK               8
#define MCF51XX_MTIMCLK_CLKS0_MASK             16
#define MCF51XX_MTIMCLK_CLKS1_MASK             32
#define MCF51XX_MTIMCLK_PS_MASK                15
#define MCF51XX_MTIMCLK_PS_BITNUM              0
#define MCF51XX_MTIMCLK_CLKS_MASK              48
#define MCF51XX_MTIMCLK_CLKS_BITNUM            4

/*------------------------------------------------------------------------*/
/*
** SCGC System Clock Gating Control
*/

#define MCF51XX_SCGC1_SCI1_MASK                 1
#define MCF51XX_SCGC1_SCI2_MASK                 2
#define MCF51XX_SCGC1_IIC1_MASK                 4
#define MCF51XX_SCGC1_IIC2_MASK                 8
#define MCF51XX_SCGC1_ADC_MASK                  16
#define MCF51XX_SCGC1_TPM1_MASK                 32
#define MCF51XX_SCGC1_TPM2_MASK                 64
#define MCF51XX_SCGC1_MTIM1_MASK                128
#define MCF51XX_SCGC1_SCI_1_MASK                3
#define MCF51XX_SCGC1_SCI_1_BITNUM              0
#define MCF51XX_SCGC1_IIC_1_MASK                12
#define MCF51XX_SCGC1_IIC_1_BITNUM              2
#define MCF51XX_SCGC1_TPM_1_MASK                96
#define MCF51XX_SCGC1_TPM_1_BITNUM              5

#define MCF51XX_SCGC2_SPI1_MASK                 1
#define MCF51XX_SCGC2_SPI2_MASK                 2
#define MCF51XX_SCGC2_RTC_MASK                  4
#define MCF51XX_SCGC2_KBI1_MASK                 8
#define MCF51XX_SCGC2_KBI2_MASK                 16
#define MCF51XX_SCGC2_IRQ_MASK                  32
#define MCF51XX_SCGC2_FTSR_MASK                 64
#define MCF51XX_SCGC2_USB_MASK                 128
#define MCF51XX_SCGC2_SPI_1_MASK                3
#define MCF51XX_SCGC2_SPI_1_BITNUM              0
#define MCF51XX_SCGC2_KBI_1_MASK                24
#define MCF51XX_SCGC2_KBI_1_BITNUM              3

#define MCF51XX_SCGC3_PTA_MASK                  1
#define MCF51XX_SCGC3_PTB_MASK                  2
#define MCF51XX_SCGC3_PTC_MASK                  4
#define MCF51XX_SCGC3_PTD_MASK                  8
#define MCF51XX_SCGC3_PTE_MASK                  16
#define MCF51XX_SCGC3_PTF_MASK                  32
#define MCF51XX_SCGC3_PTG_MASK                  64
#define MCF51XX_SCGC3_PTH_MASK                  128

#define MCF51XX_SCGC4_PTJ_MASK                  1
#define MCF51XX_SCGC4_FEC_MASK                  2
#define MCF51XX_SCGC4_MB_MASK                   4
#define MCF51XX_SCGC4_MC_MASK                   8
#define MCF51XX_SCGC4_MTIM2_MASK                16


/*------------------------------------------------------------------------*/
/*
** mux registers
*/

/* PTXPF registers */
#define MCF51XX_PTXPF_X0_MASK                  0x0003
#define MCF51XX_PTXPF_X1_MASK                  0x000c
#define MCF51XX_PTXPF_X2_MASK                  0x0030
#define MCF51XX_PTXPF_X3_MASK                  0x00c0
#define MCF51XX_PTXPF_X4_MASK                  0x0300
#define MCF51XX_PTXPF_X5_MASK                  0x0c00
#define MCF51XX_PTXPF_X6_MASK                  0x3000
#define MCF51XX_PTXPF_X7_MASK                  0xc000

#define MCF51XX_PTXPF_MASK_ALL                 0xFFFF


#define MCF51XX_PTDPA_X0_PHYCLK                0x0001
#define MCF51XX_PTDPA_X1_MII_MDIO              0x0004
#define MCF51XX_PTDPA_X2_MII_MDC               0x0010
#define MCF51XX_PTDPA_X3_MII_RXD3              0x0040
#define MCF51XX_PTDPA_X4_MII_RXD2              0x0100
#define MCF51XX_PTDPA_X5_MII_RXD1              0x0400
#define MCF51XX_PTDPA_X6_MII_RXD0              0x1000
#define MCF51XX_PTDPA_X7_MII_RX_DV             0x4000

#define MCF51XX_PTDPA_MII_SIGNALS              (MCF51XX_PTDPA_X0_PHYCLK | MCF51XX_PTDPA_X1_MII_MDIO | MCF51XX_PTDPA_X2_MII_MDC | \
                                               MCF51XX_PTDPA_X3_MII_RXD3 | MCF51XX_PTDPA_X4_MII_RXD2 | MCF51XX_PTDPA_X5_MII_RXD1 | \
                                               MCF51XX_PTDPA_X6_MII_RXD0 | MCF51XX_PTDPA_X7_MII_RX_DV)
#define MCF51XX_PTDPA_MII_MASK                 MCF51XX_PTXPF_MASK_ALL                                             

#define MCF51XX_PTDPB_X0_MII_RX_CLK            0x0001
#define MCF51XX_PTDPB_X1_MII_RX_ER             0x0004
#define MCF51XX_PTDPB_X2_MII_TX_ER             0x0010
#define MCF51XX_PTDPB_X3_MII_TX_CLK            0x0040
#define MCF51XX_PTDPB_X4_MII_TX_EN             0x0100
#define MCF51XX_PTDPB_X5_MII_TXD0              0x0400
#define MCF51XX_PTDPB_X6_MII_TXD1              0x1000
#define MCF51XX_PTDPB_X7_MII_TXD2              0x4000

#define MCF51XX_PTDPB_MII_SIGNALS              (MCF51XX_PTDPB_X0_MII_RX_CLK | MCF51XX_PTDPB_X1_MII_RX_ER | MCF51XX_PTDPB_X2_MII_TX_ER | \
                                               MCF51XX_PTDPB_X3_MII_TX_CLK | MCF51XX_PTDPB_X4_MII_TX_EN | MCF51XX_PTDPB_X5_MII_TXD0 | \
                                               MCF51XX_PTDPB_X6_MII_TXD1 | MCF51XX_PTDPB_X7_MII_TXD2)
#define MCF51XX_PTDPB_MII_MASK                 MCF51XX_PTXPF_MASK_ALL                                             

#define MCF51XX_PTDPC_X0_MII_TXD3              0x0001
#define MCF51XX_PTDPC_X1_MII_COL               0x0004
#define MCF51XX_PTDPC_X2_MII_CRS               0x0010

#define MCF51XX_PTDPC_MII_SIGNALS              (MCF51XX_PTDPC_X0_MII_TXD3 | MCF51XX_PTDPC_X1_MII_COL | MCF51XX_PTDPC_X2_MII_CRS)
#define MCF51XX_PTDPC_MII_MASK                 (MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK | MCF51XX_PTXPF_X2_MASK)                                             

#define MCF51XX_PTEPF_X3_MB_CLKOUT             0x0200
#define MCF51XX_PTEPF_X6_MB_FB_D0              0x2000
#define MCF51XX_PTEPF_X7_MB_FB_CS0             0x8000

#define MCF51XX_PTEPF_MB_MUX_SIGNALS           (MCF51XX_PTEPF_X3_MB_CLKOUT | MCF51XX_PTEPF_X7_MB_FB_CS0)   
#define MCF51XX_PTEPF_MB_MUX_MASK              (MCF51XX_PTXPF_X4_MASK | MCF51XX_PTXPF_X7_MASK) 

#define MCF51XX_PTDPF_X0_TXD1                  0x0002
#define MCF51XX_PTDPF_X1_RXD1                  0x0008
#define MCF51XX_PTDPF_X2_TXD2                  0x0020
#define MCF51XX_PTDPF_X3_RXD2                  0x0080

#define MCF51XX_PTEPF_X6_TXD3                  0x3000
#define MCF51XX_PTEPF_X7_RXD3                  0xc000

#define MCF51XX_PTFPF_X0_MB_FB_AD19            0x0002
#define MCF51XX_PTFPF_X1_MB_FB_AD18            0x0008
#define MCF51XX_PTFPF_X2_MB_FB_AD17            0x0020
#define MCF51XX_PTFPF_X3_MB_FB_AD16            0x0080
#define MCF51XX_PTFPF_X6_MB_FB_AD14            0x2000
#define MCF51XX_PTFPF_X0_MB_FB_AD13            0x8000

#define MCF51XX_PTFPF_MB_MUX_SIGNALS           (MCF51XX_PTFPF_X0_MB_FB_AD19 | MCF51XX_PTFPF_X1_MB_FB_AD18 | MCF51XX_PTFPF_X2_MB_FB_AD17 | \
                                               MCF51XX_PTFPF_X3_MB_FB_AD16 | MCF51XX_PTFPF_X6_MB_FB_AD14 | MCF51XX_PTFPF_X0_MB_FB_AD13) 
#define MCF51XX_PTFPF_MB_MUX_MASK              (MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK | MCF51XX_PTXPF_X2_MASK | \
                                               MCF51XX_PTXPF_X3_MASK | MCF51XX_PTXPF_X6_MASK | MCF51XX_PTXPF_X7_MASK )

#define MCF51XX_PTGPF_X0_MB_FB_AD8             0x0002
#define MCF51XX_PTGPF_X1_MB_FB_AD7             0x0008
#define MCF51XX_PTGPF_X2_MB_FB_AD6             0x0020
#define MCF51XX_PTGPF_X3_MB_FB_AD5             0x0080
#define MCF51XX_PTGPF_X4_MB_FB_RW              0x0200

#define MCF51XX_PTGPF_MB_MUX_SIGNALS           (MCF51XX_PTGPF_X0_MB_FB_AD8 | MCF51XX_PTGPF_X1_MB_FB_AD7 | MCF51XX_PTGPF_X2_MB_FB_AD6 | \
                                               MCF51XX_PTGPF_X3_MB_FB_AD5 | MCF51XX_PTGPF_X4_MB_FB_RW )
#define MCF51XX_PTGPF_MB_MUX_MASK              (MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK | MCF51XX_PTXPF_X2_MASK | \
                                               MCF51XX_PTXPF_X3_MASK | MCF51XX_PTXPF_X4_MASK)                                               

#define MCF51XX_PTHPF_X0_MB_FB_AD15            0x0002
#define MCF51XX_PTHPF_X1_MB_FB_OE              0x0008
#define MCF51XX_PTHPF_X4_MB_FB_AD12            0x0200
#define MCF51XX_PTHPF_X5_MB_FB_AD11            0x0800
#define MCF51XX_PTHPF_X6_MB_FB_AD10            0x2000
#define MCF51XX_PTHPF_X7_MB_FB_AD9             0x8000

#define MCF51XX_PTHPF_MB_MUX_SIGNALS           (MCF51XX_PTHPF_X0_MB_FB_AD15 | MCF51XX_PTHPF_X1_MB_FB_OE | MCF51XX_PTHPF_X4_MB_FB_AD12 | \
                                               MCF51XX_PTHPF_X5_MB_FB_AD11 | MCF51XX_PTHPF_X6_MB_FB_AD10 | MCF51XX_PTHPF_X7_MB_FB_AD9 )
                                               
                                               
#define MCF51XX_PTHPF_MB_MUX_MASK              (MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK | MCF51XX_PTXPF_X2_MASK | \
                                               MCF51XX_PTXPF_X3_MASK | MCF51XX_PTXPF_X4_MASK)

#define MCF51XX_PTJPF_X0_MB_ALE                0x0001
#define MCF51XX_PTJPF_X1_MB_FB_AD4             0x0008
#define MCF51XX_PTJPF_X2_MB_FB_AD3             0x0020
#define MCF51XX_PTJPF_X3_MB_FB_AD2             0x0080
#define MCF51XX_PTJPF_X4_MB_FB_AD1             0x0200
#define MCF51XX_PTJPF_X5_MB_FB_AD0             0x0800

#define MCF51XX_PTJPF_MB_MUX_SIGNALS           (MCF51XX_PTJPF_X0_MB_ALE | MCF51XX_PTJPF_X1_MB_FB_AD4 | MCF51XX_PTJPF_X2_MB_FB_AD3 | \
                                               MCF51XX_PTJPF_X3_MB_FB_AD2 | MCF51XX_PTJPF_X4_MB_FB_AD1 | MCF51XX_PTJPF_X5_MB_FB_AD0 )
#define MCF51XX_PTJPF_MB_MUX_MASK              (MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK | MCF51XX_PTXPF_X2_MASK | \
                                               MCF51XX_PTXPF_X3_MASK | MCF51XX_PTXPF_X4_MASK | MCF51XX_PTXPF_X5_MASK)

#define MCF51XX_PTXPF_X0_BITNUM                0
#define MCF51XX_PTXPF_X1_BITNUM                2
#define MCF51XX_PTXPF_X2_BITNUM                4
#define MCF51XX_PTXPF_X3_BITNUM                6
#define MCF51XX_PTXPF_X4_BITNUM                8
#define MCF51XX_PTXPF_X5_BITNUM                10
#define MCF51XX_PTXPF_X6_BITNUM                12
#define MCF51XX_PTXPF_X7_BITNUM                14

#define MCF51XX_PTXDD_PTXDD0_MASK               1
#define MCF51XX_PTXDD_PTXDD1_MASK               2
#define MCF51XX_PTXDD_PTXDD2_MASK               4
#define MCF51XX_PTXDD_PTXDD3_MASK               8
#define MCF51XX_PTXDD_PTXDD4_MASK               16
#define MCF51XX_PTXDD_PTXDD5_MASK               32
#define MCF51XX_PTXDD_PTXDD6_MASK               64
#define MCF51XX_PTXDD_PTXDD7_MASK               128

#define MCF51XX_KBIXSC_KBIMOD                   1
#define MCF51XX_KBIXSC_KBIE                     2
#define MCF51XX_KBIXSC_KBACK                    4
#define MCF51XX_KBIXSC_KBF                      8

/*------------------------------------------------------------------------*/
/*
** MCG registers - multi clock generator
*/


#define MCF51XX_MCGC1_IREFSTEN_MASK             1
#define MCF51XX_MCGC1_IRCLKEN_MASK              2
#define MCF51XX_MCGC1_IREFS_MASK                4
#define MCF51XX_MCGC1_RDIV0_MASK                8
#define MCF51XX_MCGC1_RDIV1_MASK                16
#define MCF51XX_MCGC1_RDIV2_MASK                32
#define MCF51XX_MCGC1_CLKS0_MASK                64
#define MCF51XX_MCGC1_CLKS1_MASK                128
#define MCF51XX_MCGC1_RDIV_MASK                 56
#define MCF51XX_MCGC1_RDIV_BITNUM               3
#define MCF51XX_MCGC1_CLKS_MASK                 192
#define MCF51XX_MCGC1_CLKS_BITNUM               6

#define MCF51XX_MCGSC_FTRIM_MASK                1
#define MCF51XX_MCGSC_OSCINIT_MASK              2
#define MCF51XX_MCGSC_CLKST0_MASK               4
#define MCF51XX_MCGSC_CLKST1_MASK               8
#define MCF51XX_MCGSC_IREFST_MASK               16
#define MCF51XX_MCGSC_PLLST_MASK                32
#define MCF51XX_MCGSC_LOCK_MASK                 64
#define MCF51XX_MCGSC_LOLS_MASK                 128
#define MCF51XX_MCGSC_CLKST_MASK                12
#define MCF51XX_MCGSC_CLKST_BITNUM              2

#define MCF51XX_MCGC4_DRST_DRS0_MASK            1
#define MCF51XX_MCGC4_DRST_DRS1_MASK            2
#define MCF51XX_MCGC4_DMX32_MASK                32
#define MCF51XX_MCGC4_DRST_DRS_MASK             3
#define MCF51XX_MCGC4_DRST_DRS_BITNUM           0

#define MCF51XX_MCGC2_EREFSTEN_MASK             1
#define MCF51XX_MCGC2_ERCLKEN_MASK              2
#define MCF51XX_MCGC2_EREFS_MASK                4
#define MCF51XX_MCGC2_LP_MASK                   8
#define MCF51XX_MCGC2_HGO_MASK                  16
#define MCF51XX_MCGC2_RANGE_MASK                32
#define MCF51XX_MCGC2_BDIV0_MASK                64
#define MCF51XX_MCGC2_BDIV1_MASK                128
#define MCF51XX_MCGC2_BDIV_MASK                 192
#define MCF51XX_MCGC2_BDIV_BITNUM               6

#define MCF51XX_MCGC3_VDIV0_MASK                1
#define MCF51XX_MCGC3_VDIV1_MASK                2
#define MCF51XX_MCGC3_VDIV2_MASK                4
#define MCF51XX_MCGC3_VDIV3_MASK                8
#define MCF51XX_MCGC3_DIV32_MASK                16
#define MCF51XX_MCGC3_CME_MASK                  32
#define MCF51XX_MCGC3_PLLS_MASK                 64
#define MCF51XX_MCGC3_LOLIE_MASK                128
#define MCF51XX_MCGC3_VDIV_MASK                 15
#define MCF51XX_MCGC3_VDIV_BITNUM               0


#define MCF51XX_SOPT2_BIGEND_MASK               0x20

/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/
/*
** MCF51JM_pmc_struct
** This structure defines PMC registers
*/ 
typedef struct MCF51JM_pmc_struct
{
  uchar  SPMSC1;    /*** SPMSC1 - System Power Management Status and Control Register 1; 0xFFFF8120 ***/
  uchar  SPMSC2;    /*** SPMSC2 - System Power Management Status and Control Register 2; 0xFFFF8121 ***/
} MCF51JM_PMC_STRUCT, _PTR_ MCF51JM_PMC_STRUCT_PTR;
typedef volatile struct MCF51JM_pmc_struct _PTR_ VMCF51JM_PMC_STRUCT_PTR;

/*
** MCF51JM_cmt_struct
** This structure defines CMT registers
*/ 
typedef struct MCF51JM_cmt_struct
{
    uchar CMTCGH1;
    uchar CMTCGL1;
    uchar CMTCGH2;
    uchar CMTCGL2;
    uchar CMTOC;
    uchar CMTMSC;
    uchar CMTCMD1;
    uchar CMTCMD2;
    uchar CMTCMD3;
    uchar CMTCMD4;
} MCF51JM_CMT_STRUCT, _PTR_ MCF51JM_CMT_STRUCT_PTR;
typedef volatile struct MCF51JM_cmt_struct _PTR_ VMCF51JM_CMT_STRUCT_PTR;

/*
** MCF51JM_can_struct
** This structure defines CAN registers
*/ 
typedef struct MCF51JM_can_struct
{
    uchar CANCTL0;
    uchar CANCTL1;
    uchar CANBTR0;
    uchar CANBTR1;
    uchar CANRFLG;
    uchar CANRIER;
    uchar CANTFLG;
    uchar CANTIER;
    uchar CANTARQ;
    uchar CANTAAK;
    uchar CANTBSEL;
    uchar CANIDAC;
    uchar reserved01;
    uchar CANMISC;
    uchar CANRXERR;
    uchar CANTXERR;
    uchar CANIDAR0;
    uchar CANIDAR1;
    uchar CANIDAR2;
    uchar CANIDAR3;
    uchar CANIDMR0;
    uchar CANIDMR1;
    uchar CANIDMR2;
    uchar CANIDMR3;
    uchar CANIDAR4;
    uchar CANIDAR5;
    uchar CANIDAR6;
    uchar CANIDAR7;
    uchar CANIDMR4;
    uchar CANIDMR5;
    uchar CANIDMR6;
    uchar CANIDMR7;
    uchar CANRIDR0;
    uchar CANRIDR1;
    uchar CANRIDR2;
    uchar CANRIDR3;
    uchar CANRDSR0;
    uchar CANRDSR1;
    uchar CANRDSR2;
    uchar CANRDSR3;
    uchar CANRDSR4;
    uchar CANRDSR5;
    uchar CANRDSR6;
    uchar CANRDSR7;
    uchar CANRDLR;
    uchar CANTBPR;
    uchar CANRTSRH;
    uchar CANRTSRL;
    uchar CANTIDR0;
    uchar CANTIDR1;
    uchar CANTIDR2;
    uchar CANTIDR3;
    uchar CANTIDSR0;
    uchar CANTIDSR1;
    uchar CANTIDSR2;
    uchar CANTIDSR3;
    uchar CANTIDSR4;
    uchar CANTIDSR5;
    uchar CANTIDSR6;
    uchar CANTIDSR7;
    uchar CANTDLR;
    uchar CANTTBPR;
    uchar CANTTSRH;
    uchar CANTTSRL;
} MCF51JM_CAN_STRUCT, _PTR_ MCF51JM_CAN_STRUCT_PTR;
typedef volatile struct MCF51JM_can_struct _PTR_ VMCF51JM_CAN_STRUCT_PTR;

/*
** MCF51JM_rng_struct
** This structure defines RNG registers
*/  
typedef struct MCF51JM_rng_struct
{
    uint_32 RNGCR;
    uint_32 RNGSR;
    uint_32 RNGER;
    uint_32 RNGOUT;
} MCF51JM_RNG_STRUCT, _PTR_ MCF51JM_RNG_STRUCT_PTR;
typedef volatile struct MCF51JM_rng_struct _PTR_ VMCF51JM_RNG_STRUCT_PTR;

/* This structure defines (Rapid) General Purpose I/O registers (APPROACH #2) */

typedef struct MCF51JM_gpio_data_struct
{
   uchar  PTxD;      /*** Port Data ***/
   uchar  PTxDD;     /*** Port Data Direction ***/
} MCF51JM_GPIO_DATA_STRUCT, _PTR_ MCF51JM_GPIO_DATA_STRUCT_PTR;
typedef volatile struct MCF51JM_gpio_data_struct _PTR_ VMCF51JM_GPIO_DATA_STRUCT_PTR;

typedef struct MCF51JM_gpio_struct
{
   uchar  PTxPE;     /*** Port Pull-Up Enable ***/
   uchar  PTxSE;     /*** Port Slew Rate Control ***/
   uchar  PTxDS;     /*** Port Drive Strength Control ***/
   uchar  PTxIFE;    /*** Port Input Filter Control ***/

} MCF51JM_GPIO_STRUCT, _PTR_ MCF51JM_GPIO_STRUCT_PTR;
typedef volatile struct MCF51JM_gpio_struct _PTR_ VMCF51JM_GPIO_STRUCT_PTR;

typedef enum {
   GPIO_PORT_A = 0,
   GPIO_PORT_B,
   GPIO_PORT_C,
   GPIO_PORT_D,
   GPIO_PORT_E,
   GPIO_PORT_F,
   GPIO_PORT_G,
   GPIO_PORT_H,
   GPIO_PORT_J,
   GPIO_PORT_MAX
} gpio_port_t;


/*
** MCF51JM_irq_struct
** This structure defines Interrupt registers
*/

typedef struct MCF51JM_irq_struct
{
  uchar  IRQSC;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
} MCF51JM_IRQ_STRUCT, _PTR_ MCF51JM_IRQ_STRUCT_PTR;
typedef volatile struct MCF51JM_irq_struct _PTR_ VMCF51JM_IRQ_STRUCT_PTR;


typedef struct MCF51JM_tpm_channel_struct
{
  uchar    TPMxCySC;
  uint_16  TPMxCyV; //TPMxCyVH and TPMxCyVL registers
} MCF51JM_TPM_CHANNEL_STRUCT, _PTR_ MCF51JM_TPM_CHANNEL_STRUCT_PTR;
typedef volatile struct MCF51JM_tpm_channel_struct _PTR_ VMCF51JM_TPM_CHANNEL_STRUCT_PTR;

/*
** MCF51JM_tpm_struct
** This structure defines Interrupt registers
*/

typedef struct MCF51JM_tpm1_struct
{
  uchar    TPMxSC; 
  uint_16  TPMxCNT; //TPMxCNTH and TPMxCNTL registers
  uint_16  TPMxMOD; //TPMxMODH and TPMxMODL registers  
  MCF51JM_TPM_CHANNEL_STRUCT TPMxC[6];
} MCF51JM_TPM1_STRUCT, _PTR_ MCF51JM_TPM1_STRUCT_PTR;
typedef volatile struct MCF51JM_tpm1_struct _PTR_ VMCF51JM_TPM1_STRUCT_PTR;

typedef struct MCF51JM_tpm2_struct
{
  uchar    TPMxSC; 
  uint_16  TPMxCNT;  //TPMxCNTH and TPMxCNTL registers
  uint_16  TPMxMOD;  //TPMxMODH and TPMxMODL registers
  MCF51JM_TPM_CHANNEL_STRUCT TPMxC[2];
} MCF51JM_TPM2_STRUCT, _PTR_ MCF51JM_TPM2_STRUCT_PTR;
typedef volatile struct MCF51JM_tpm2_struct _PTR_ VMCF51JM_TPM2_STRUCT_PTR;

/*
** MCF51JM_kbi_struct
** This structure defines Interrupt registers
*/

typedef struct MCF51JM_kbi_struct
{
  uchar  KBI1SC;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
  uchar  KBI1PE;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
  uchar  KBI1ES;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
} MCF51JM_KBI_STRUCT, _PTR_ MCF51JM_KBI_STRUCT_PTR;
typedef volatile struct MCF51JM_kbi_struct _PTR_ VMCF51JM_KBI_STRUCT_PTR;


/*
** MCF51JM_MTIM_STRUCT
** Programmable interrupt timer
*/
typedef struct MCF51JM_mtim_struct
{
   uchar MTIMSC;     /*** MTIMCG - MTIM1 Clock Configuration Register; 0xFFFF82A0 ***/
   uchar MTIMCLK;    /*** MTIMCLK - MTIM1 Clock Configuration Register; 0xFFFF82A1 ***/
   uchar MTIMCNT;    /*** MTIMCNT - MTIM1 Counter Register; 0xFFFF82A2 ***/
   uchar MTIMMOD;   /*** MTIMMOD - MTIM1 Modulo Register; 0xFFFF82A3 ***/   
   
} MCF51JM_MTIM_STRUCT, _PTR_ MCF51JM_MTIM_STRUCT_PTR;
typedef volatile struct MCF51JM_mtim_struct _PTR_ VMCF51JM_MTIM_STRUCT_PTR;

/*
** MCF51JM_MCG_STRUCT
** Multi clock generator module
*/
typedef struct MCF51JM_mcg_struct
{
  uchar MCGC1;  /*** MCGC1 - MCG Control Register 1; 0xFFFF8240 ***/
  uchar MCGC2;  /*** MCGC2 - MCG Control Register 2; 0xFFFF8241 ***/
  uchar MCGTRM; /*** MCGTRM - MCG Trim Register; 0xFFFF8242 ***/
  uchar MCGSC;  /*** MCGSC - MCG Status and Control Register; 0xFFFF8243 ***/
  uchar MCGC3;  /*** MCGC3 - MCG Control Register 3; 0xFFFF8244 ***/
  uchar MCGC4;  /*** MCGC4 - MCG Control Register 4; 0xFFFF8245 ***/
} MCF51JM_MCG_STRUCT, _PTR_ MCF51JM_MCG_STRUCT_PTR;
typedef volatile struct MCF51JM_mcg_struct _PTR_ VMCF51JM_MCG_STRUCT_PTR;

/*
** MCF51JM_sim_struct
** This structure defines System Integration Module registers
*/
typedef struct MCF51JM_sim_struct
{
   uchar SRS;
   uchar reserved0A;
   uchar SOPT1;
   uchar SOPT2;
   uchar reserved0B[2];
   uchar SDIDH;
   uchar SDIDL;
} MCF51JM_SIM_STRUCT, _PTR_ MCF51JM_SIM_STRUCT_PTR;
typedef volatile struct MCF51JM_sim_struct _PTR_ VMCF51JM_SIM_STRUCT_PTR;

typedef struct MCF51JM_simx_struct
{   
   uchar SCGC1;
   uchar SCGC2;
   uchar SCGC3;
   uchar SOPT3;
   uchar SOPT4;
} MCF51JM_SIMX_STRUCT, _PTR_ MCF51JM_SIMX_STRUCT_PTR;
typedef volatile struct MCF51JM_simx_struct _PTR_ VMCF51JM_SIMX_STRUCT_PTR;

#define ALIGN_TO(x) (x)
#define USE_REFERENCE(x) -sizeof(x)
#define AT_ADDRESS(x)   -x
typedef struct MCF51JM_struct
{
   MCF51JM_GPIO_DATA_STRUCT   GPIO_A_G[GPIO_PORT_G+1];
   uchar ACMPSC; 
   uchar reserved01;   
   MCF51AC_ADC_STRUCT    ADC; 
   uchar reserved02[0x801B - 0x8010 - sizeof(MCF51AC_ADC_STRUCT)];
   MCF51JM_IRQ_STRUCT    IRQ;
   MCF51JM_KBI_STRUCT    KBI;
   uchar reserved03[0x8020 - 0x801C - sizeof(MCF51JM_KBI_STRUCT)];
   MCF51JM_TPM1_STRUCT   TPM1;
   uchar reserved04[0x8038 - 0x8020 - sizeof(MCF51JM_TPM1_STRUCT)];
   MCF51XX_SCI_STRUCT    SCI1;
   MCF51XX_SCI_STRUCT    SCI2;
   MCF51JM_MCG_STRUCT    MCG;
   uchar reserved05[0x8050 - 0x8048 - sizeof(MCF51JM_MCG_STRUCT)];
   MCF5XXX_SPI16_NO_FIFO_STRUCT  SPI1;   
   MCF51XX_I2C_STRUCT    I2C1;
   uchar reserved06[0x8060 - 0x8058 - sizeof(MCF51XX_I2C_STRUCT)];
   MCF51JM_TPM2_STRUCT   TPM2;
   uchar reserved07[0x806C - 0x8060 - sizeof(MCF51JM_TPM2_STRUCT)];
   MCF51XX_RTC_STRUCT    RTC;
   uchar reserved08[0x8070 - 0x806C - sizeof(MCF51XX_RTC_STRUCT)];
   MCF5XXX_SPI16_STRUCT  SPI2;
   uchar reserved09[0x9800-0x8070 - sizeof(MCF5XXX_SPI16_STRUCT)];
   MCF51JM_SIM_STRUCT SIM;
   uchar reserved0A[0x9809-0x9800 - sizeof(MCF51JM_SIM_STRUCT)];
   MCF51JM_PMC_STRUCT PMC;
   MCF51JM_SIMX_STRUCT SIMX;  
   uchar reserved0B[0x9820-0x980B - sizeof(MCF51JM_SIMX_STRUCT)];
   MCF51XX_FTSR_STRUCT FTSR;
   uchar reserved0C[0x9838-0x9820 - sizeof(MCF51XX_FTSR_STRUCT)];
   MCF51XX_I2C_STRUCT    I2C2;
   uchar reserved0D[0x9840-0x9838 - sizeof(MCF51XX_I2C_STRUCT)];
   MCF51JM_GPIO_STRUCT GPIO_P[GPIO_PORT_MAX]; //i.e. GPIO_PORT_J + 1
   uchar reserved0E[0x9868-0x9840 - (sizeof(MCF51JM_GPIO_STRUCT)*GPIO_PORT_MAX)];      
   MCF51JM_CMT_STRUCT CMT; 
   uchar reserved0F[0x9874-0x9868 - sizeof(MCF51JM_CMT_STRUCT)];
   MCF51JM_GPIO_DATA_STRUCT   GPIO_H_J[GPIO_PORT_MAX-GPIO_PORT_H];
   uchar reserved10[0x9880-0x9874 - (sizeof(MCF51JM_GPIO_DATA_STRUCT)*(GPIO_PORT_MAX-GPIO_PORT_H))]; 
   MCF51JM_CAN_STRUCT CAN;
   MCF51JM_RNG_STRUCT RNG;
   uchar reserved11[0x9A00-0x98C0 - sizeof(MCF51JM_RNG_STRUCT)];
   USB_MemMap         USBOTG;
   uchar reserved12[0xFFC0 - 0x9A00 - sizeof(USB_MemMap)]; 
   MCF51XX_INT_CTRL_STRUCT  INTC;   /* interrupt controller */
} MCF51JM_STRUCT, _PTR_ MCF51JM_STRUCT_PTR;
typedef volatile struct MCF51JM_struct _PTR_ VMCF51JM_STRUCT_PTR;

/*
** PSP_SUPPORT_STRUCT
** This structure is used to maintain the PSP support information
*/
typedef struct psp_support_struct
{
   uint_32 ACR_COUNT;   // How many ACRs set so far
   uint_32 Reserved;

} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;




/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_cacr;
extern volatile uint_32 _psp_saved_acr0;
extern volatile uint_32 _psp_saved_acr1;
extern          uchar   __KERNEL_DATA_VERIFY_ENABLE[]; // CR1327

extern pointer _mcf51JM_get_ipsbar(void);
extern void    _mcf51JM_initialize_support(uint_32);

extern void    _mcf51JM_cache_enable(uint_32);
extern void    _mcf51JM_cache_disable(void);
extern void    _mcf51JM_icache_invalidate(void);
extern void    _mcf51JM_dcache_invalidate(void);

extern void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
extern void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

extern void    _mcf51JM_mmu_init(uint_32);
extern uint_32 _mcf51JM_mmu_enable(void);
extern uint_32 _mcf51JM_mmu_disable(void);
extern uint_32 _mcf51JM_mmu_add_region(pointer,uint_32,uint_32);

extern void    __psp_enable_acrs(uint_32_ptr);
extern void    __psp_clear_acrs(void);
extern void    __psp_dcache_flush(uint_32,uint_32,uint_32);

#endif //__ASM__

#ifdef __cplusplus
}
#endif


#endif // __mcf51JM_h__
/* EOF */

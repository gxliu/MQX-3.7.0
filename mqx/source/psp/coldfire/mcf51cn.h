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
* $FileName: mcf51CN.h$
* $Version : 3.6.27.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf5225x processors.
*
*END************************************************************************/

#ifndef __mcf51cn_h__
#define __mcf51cn_h__

#define __mcf51cn_h__version "$Version:3.6.27.0$"
#define __mcf51cn_h__date    "$Date:Jun-4-2010$"

#ifndef __ASM__
/* Include registers for modules common to all Coldfire processors */
#include <mcf51xx_ictl.h>       /* CTRL */   
#include <mcf5xxx_fec.h>              /* FEC */
#include <mcf51xx_sci.h>          /* SCI */
#include <mcf51xx_i2c.h>          /* I2C */
#include <mcf51xx_adc.h>
#include <mcf51xx_rtc.h>
#include <mcf5xxx_spi8.h>
#include <mcf51xx_ftsr.h> 
#include <mcf51xx_pmc.h>
#include <mcf5xxx_minifb.h> 
#endif // __ASM__

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* Indicate processor type */
#define PSP_MCF51CN                         1

#define PSP_HAS_DSP                         0
#define PSP_HAS_EMAC                        0

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  0
#define PSP_HAS_DATA_CACHE                  0
//#define PSP_CACHE_LINE_SIZE                 (0x10)

#ifndef __ASM__

#define MCF51CN_NUM_ACRS                    (2)

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
#define MCF51CN_NUM_TIMERS                (2) /* MTIM */

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
typedef enum mcf51cn_interrupt_table_index {
  MCF51CN_INT_INITSP      =       0,
  MCF51CN_INT_INITPC      =       1,
  MCF51CN_INT_Vaccerr     =       2,
  MCF51CN_INT_Vadderr     =       3,
  MCF51CN_INT_Viinstr     =       4,
  MCF51CN_INT_VReserved5  =       5,
  MCF51CN_INT_VReserved6  =       6,
  MCF51CN_INT_VReserved7  =       7,
  MCF51CN_INT_Vprviol     =       8,
  MCF51CN_INT_Vtrace      =       9,
  MCF51CN_INT_Vunilaop    =       10,
  MCF51CN_INT_Vunilfop    =       11,
  MCF51CN_INT_Vdbgi       =       12,
  MCF51CN_INT_VReserved13 =       13,
  MCF51CN_INT_Vferror     =       14,
  MCF51CN_INT_VReserved15 =       15,
  MCF51CN_INT_VReserved16 =       16,
  MCF51CN_INT_VReserved17 =       17,
  MCF51CN_INT_VReserved18 =       18,
  MCF51CN_INT_VReserved19 =       19,
  MCF51CN_INT_VReserved20 =       20,
  MCF51CN_INT_VReserved21 =       21,
  MCF51CN_INT_VReserved22 =       22,
  MCF51CN_INT_VReserved23 =       23,
  MCF51CN_INT_Vspuri      =       24,
  MCF51CN_INT_VReserved25 =       25,
  MCF51CN_INT_VReserved26 =       26,
  MCF51CN_INT_VReserved27 =       27,
  MCF51CN_INT_VReserved28 =       28,
  MCF51CN_INT_VReserved29 =       29,
  MCF51CN_INT_VReserved30 =       30,
  MCF51CN_INT_VReserved31 =       31,
  MCF51CN_INT_Vtrap0      =       32,
  MCF51CN_INT_Vtrap1      =       33,
  MCF51CN_INT_Vtrap2      =       34,
  MCF51CN_INT_Vtrap3      =       35,
  MCF51CN_INT_Vtrap4      =       36,
  MCF51CN_INT_Vtrap5      =       37,
  MCF51CN_INT_Vtrap6      =       38,
  MCF51CN_INT_Vtrap7      =       39,
  MCF51CN_INT_Vtrap8      =       40,
  MCF51CN_INT_Vtrap9      =       41,
  MCF51CN_INT_Vtrap10     =       42,
  MCF51CN_INT_Vtrap11     =       43,
  MCF51CN_INT_Vtrap12     =       44,
  MCF51CN_INT_Vtrap13     =       45,
  MCF51CN_INT_Vtrap14     =       46,
  MCF51CN_INT_Vtrap15     =       47,
  MCF51CN_INT_VReserved48 =       48,
  MCF51CN_INT_VReserved49 =       49,
  MCF51CN_INT_VReserved50 =       50,
  MCF51CN_INT_VReserved51 =       51,
  MCF51CN_INT_VReserved52 =       52,
  MCF51CN_INT_VReserved53 =       53,
  MCF51CN_INT_VReserved54 =       54,
  MCF51CN_INT_VReserved55 =       55,
  MCF51CN_INT_VReserved56 =       56,
  MCF51CN_INT_VReserved57 =       57,
  MCF51CN_INT_VReserved58 =       58,
  MCF51CN_INT_VReserved59 =       59,
  MCF51CN_INT_VReserved60 =       60,
  MCF51CN_INT_Vunsinstr   =       61,
  MCF51CN_INT_VReserved62 =       62,
  MCF51CN_INT_VReserved63 =       63,
  MCF51CN_INT_Virq        =       64,
  MCF51CN_INT_Vlvd        =       65,
  MCF51CN_INT_Vlol        =       66,
  MCF51CN_INT_Vtpm1ch0    =       67,
  MCF51CN_INT_Vtpm1ch1    =       68,
  MCF51CN_INT_Vtpm1ch2    =       69,
  MCF51CN_INT_Vtpm1ovf    =       70,
  MCF51CN_INT_Vmtim1      =       71,
  MCF51CN_INT_Vtpm2ch0    =       72,
  MCF51CN_INT_Vtpm2ch1    =       73,
  MCF51CN_INT_Vtpm2ch2    =       74,
  MCF51CN_INT_Vtpm2ovf    =       75,
  MCF51CN_INT_Vspi1       =       76,
  MCF51CN_INT_Vspi2       =       77,
  MCF51CN_INT_Vmtim2      =       78,
  MCF51CN_INT_Vsci1err    =       79,
  MCF51CN_INT_Vsci1rx     =       80,
  MCF51CN_INT_Vsci1tx     =       81,
  MCF51CN_INT_Vsci2err    =       82,
  MCF51CN_INT_Vsci2rx     =       83,
  MCF51CN_INT_Vsci2tx     =       84,
  MCF51CN_INT_Vsci3or     =       85,
  MCF51CN_INT_Vfectxf     =       86,
  MCF51CN_INT_Vfecrxf     =       87,
  MCF51CN_INT_Vfecother   =       88,
  MCF51CN_INT_Vfechberr   =       89,
  MCF51CN_INT_Vfecbabr    =       90,
  MCF51CN_INT_Vfecbabt    =       91,
  MCF51CN_INT_Vfecgra     =       92,
  MCF51CN_INT_Vfectxb     =       93,
  MCF51CN_INT_Vfecrxb     =       94,
  MCF51CN_INT_Vfecmii     =       95,
  MCF51CN_INT_Vfeceberr   =       96,
  MCF51CN_INT_Vfeclc      =       97,
  MCF51CN_INT_Vfecrl      =       98,
  MCF51CN_INT_Vfecun      =       99,
  MCF51CN_INT_Vsci3err    =       100,
  MCF51CN_INT_Vsci3rx     =       101,
  MCF51CN_INT_Vsci3tx     =       102,
  MCF51CN_INT_VL7swi      =       103,
  MCF51CN_INT_VL6swi      =       104,
  MCF51CN_INT_VL5swi      =       105,
  MCF51CN_INT_VL4swi      =       106,
  MCF51CN_INT_VL3swi      =       107,
  MCF51CN_INT_VL2swi      =       108,
  MCF51CN_INT_VL1swi      =       109,
  MCF51CN_INT_Viic1       =       110,
  MCF51CN_INT_Viic2       =       111,
  MCF51CN_INT_Vadc        =       112,
  MCF51CN_INT_Vkeyboard   =       113,
  MCF51CN_INT_Vrtc        =       114
} MCF51CN_INTERRUPT_TABLE_INDEX;//, PSP_INTERRUPT_TABLE_INDEX;


/*------------------------------------------------------------------------*/
/*
** MTIM Modulo Timer
*/

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
#define MCF51XX_SCGC2_SCI3_MASK                 128
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

/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/

/*
** MCF51CN_gpio_struct
** This structure defines (Rapid) General Purpose I/O registers (APPROACH #1)
*/

typedef struct MCF51CN_gpio_port_struct {

   uchar  PTxD;      /*** Port Data ***/
   uchar  PTxDD;     /*** Port Data Direction ***/
   uchar  reserved00[6];
   uchar  PTxPE;     /*** Port Pull-Up Enable ***/
   uchar  PTxSE;     /*** Port Slew Rate Control ***/
   uchar  PTxDS;     /*** Port Drive Strength Control ***/
   uchar  PTxIFE;    /*** Port Input Filter Control ***/
   uchar  reserved01[4];
} MCF51CN_GPIO_PORT_STRUCT, _PTR_ MCF51CN_GPIO_PORT_STRUCT_PTR;

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

typedef struct MCF51CN_gpio_ports_struct
{
   MCF51CN_GPIO_PORT_STRUCT PORT[GPIO_PORT_MAX];
   uchar  reserved[48];
   uint_16  PTxPF[GPIO_PORT_MAX];  /*** Port Peripheral Select ***/
} MCF51CN_GPIO_PORTS_STRUCT, _PTR_ MCF51CN_GPIO_PORTS_STRUCT_PTR;
typedef volatile struct MCF51CN_gpio_ports_struct _PTR_ VMCF51CN_GPIO_PORTS_STRUCT_PTR;

/* This structure defines (Rapid) General Purpose I/O registers (APPROACH #2) */

typedef struct MCF51CN_gpio_struct
{
   uchar  PTAD;      /*** Port Data ***/
   uchar  PTADD;     /*** Port Data Direction ***/
   uchar  reserved00[6];
   uchar  PTAPE;     /*** Port Pull-Up Enable ***/
   uchar  PTASE;     /*** Port Slew Rate Control ***/
   uchar  PTADS;     /*** Port Drive Strength Control ***/
   uchar  PTAIFE;    /*** Port Input Filter Control ***/
   uchar  reserved01[4];
   uchar  PTBD;      /*** Port Data ***/
   uchar  PTBDD;     /*** Port Data Direction ***/
   uchar  reserved02[6];
   uchar  PTBPE;     /*** Port Pull-Up Enable ***/
   uchar  PTBSE;     /*** Port Slew Rate Control ***/
   uchar  PTBDS;     /*** Port Drive Strength Control ***/
   uchar  PTBIFE;    /*** Port Input Filter Control ***/
   uchar  reserved03[4];
   uchar  PTCD;      /*** Port Data ***/
   uchar  PTCDD;     /*** Port Data Direction ***/
   uchar  reserved04[6];
   uchar  PTCPE;     /*** Port Pull-Up Enable ***/
   uchar  PTCSE;     /*** Port Slew Rate Control ***/
   uchar  PTCDS;     /*** Port Drive Strength Control ***/
   uchar  PTCIFE;    /*** Port Input Filter Control ***/
   uchar  reserved05[4];
   uchar  PTDD;      /*** Port Data ***/
   uchar  PTDDD;     /*** Port Data Direction ***/
   uchar  reserved06[6];
   uchar  PTDPE;     /*** Port Pull-Up Enable ***/
   uchar  PTDSE;     /*** Port Slew Rate Control ***/
   uchar  PTDDS;     /*** Port Drive Strength Control ***/
   uchar  PTDIFE;    /*** Port Input Filter Control ***/
   uchar  reserved07[4];
   uchar  PTED;      /*** Port Data ***/
   uchar  PTEDD;     /*** Port Data Direction ***/
   uchar  reserved08[6];
   uchar  PTEPE;     /*** Port Pull-Up Enable ***/
   uchar  PTESE;     /*** Port Slew Rate Control ***/
   uchar  PTEDS;     /*** Port Drive Strength Control ***/
   uchar  PTEIFE;    /*** Port Input Filter Control ***/
   uchar  reserved09[4];
   uchar  PTFD;      /*** Port Data ***/
   uchar  PTFDD;     /*** Port Data Direction ***/
   uchar  reserved0A[6];
   uchar  PTFPE;     /*** Port Pull-Up Enable ***/
   uchar  PTFSE;     /*** Port Slew Rate Control ***/
   uchar  PTFDS;     /*** Port Drive Strength Control ***/
   uchar  PTFIFE;    /*** Port Input Filter Control ***/
   uchar  KBI2SC;    /*** KBI2 Status & Control Register ***/
   uchar  KBI2PE;    /*** KBI2 Pin Select Register ***/
   uchar  KBI2ES;    /*** KBI2 Interrupt Edge Select Register ***/   
   uchar  reserved0B[1];
   uchar  PTGD;      /*** Port Data ***/
   uchar  PTGDD;     /*** Port Data Direction ***/
   uchar  reserved0C[6];
   uchar  PTGPE;     /*** Port Pull-Up Enable ***/
   uchar  PTGSE;     /*** Port Slew Rate Control ***/
   uchar  PTGDS;     /*** Port Drive Strength Control ***/
   uchar  PTGIFE;    /*** Port Input Filter Control ***/
   uchar  KBI1SC;    /*** KBI1 Status & Control Register ***/
   uchar  KBI1PE;    /*** KBI1 Pin Select Register ***/
   uchar  KBI1ES;    /*** KBI1 Interrupt Edge Select Register ***/  
   uchar  reserved0D[1];
   uchar  PTHD;      /*** Port Data ***/
   uchar  PTHDD;     /*** Port Data Direction ***/
   uchar  reserved0E[6];
   uchar  PTHPE;     /*** Port Pull-Up Enable ***/
   uchar  PTHSE;     /*** Port Slew Rate Control ***/
   uchar  PTHDS;     /*** Port Drive Strength Control ***/
   uchar  PTHIFE;    /*** Port Input Filter Control ***/
   uchar  reserved0F[4];
   uchar  PTJD;      /*** Port Data ***/
   uchar  PTJDD;     /*** Port Data Direction ***/
   uchar  reserved0G[6];
   uchar  PTJPE;     /*** Port Pull-Up Enable ***/
   uchar  PTJSE;     /*** Port Slew Rate Control ***/
   uchar  PTJDS;     /*** Port Drive Strength Control ***/
   uchar  PTJIFE;    /*** Port Input Filter Control ***/
   uchar  reserved0H[52];
   uint_16  PTAPF;  /*** Port Peripheral Select ***/
   uint_16  PTBPF;  /*** Port Peripheral Select ***/
   uint_16  PTCPF;  /*** Port Peripheral Select ***/
   uint_16  PTDPF;  /*** Port Peripheral Select ***/
   uint_16  PTEPF;  /*** Port Peripheral Select ***/
   uint_16  PTFPF;  /*** Port Peripheral Select ***/
   uint_16  PTGPF;  /*** Port Peripheral Select ***/
   uint_16  PTHPF;  /*** Port Peripheral Select ***/
   uint_16  PTJPF;  /*** Port Peripheral Select ***/
} MCF51CN_GPIO_STRUCT, _PTR_ MCF51CN_GPIO_STRUCT_PTR;
typedef volatile struct MCF51CN_gpio_struct _PTR_ VMCF51CN_GPIO_STRUCT_PTR;


/*
** MCF51CN_irq_struct
** This structure defines Interrupt registers
*/

typedef struct MCF51CN_irq_struct
{
  uchar  IRQSC;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
} MCF51CN_IRQ_STRUCT, _PTR_ MCF51CN_IRQ_STRUCT_PTR;
typedef volatile struct MCF51CN_irq_struct _PTR_ VMCF51CN_IRQ_STRUCT_PTR;

/*
** MCF51CN_sim_struct
** This structure defines System Integration Module registers
*/

typedef struct MCF51CN_sim_struct
{
  uchar  SRS;       /*** SRS - System Reset Status Register; 0xFFFF8100 ***/
  uchar  SOPT1;     /*** SOPT1 - System Options Register 1; 0xFFFF8101 ***/
  uchar  SOPT2;     /*** SOPT2 - System Options Register 2; 0xFFFF8102 ***/
  uchar  SOPT3;     /*** SOPT3 - SIM Options Register 3; 0xFFFF8103 ***/
  uchar  reserved00[2];
  uchar  SDIDH;     /*** SDIDH - System Device Identification Register High; 0xFFFF8106 ***/
  uchar  SDIDL;     /*** SDIDL - System Device Identification Register Low; 0xFFFF8107 ***/
  uchar  SCGC1;     /*** SCGC1 - System Clock Gating Control 1 Register; 0xFFFF8108 ***/
  uchar  SCGC2;     /*** SCGC2 - System Clock Gating Control 2 Register; 0xFFFF8109 ***/
  uchar  SCGC3;     /*** SCGC3 - System Clock Gating Control 3 Register; 0xFFFF810A ***/
  uchar  SCGC4;     /*** SCGC4 - System Clock Gating Control 4 Register; 0xFFFF810B ***/
  uchar  SIMIPS;    /*** SIMIPS - SIM Internal Peripheral Select Register; 0xFFFF810C ***/
} MCF51CN_SIM_STRUCT, _PTR_ MCF51CN_SIM_STRUCT_PTR;
typedef volatile struct MCF51CN_sim_struct _PTR_ VMCF51CN_SIM_STRUCT_PTR;

/*
** MCF51CN_MTIM_STRUCT
** Programmable interrupt timer
*/
typedef struct MCF51CN_mtim_struct
{
   uchar MTIMSC;     /*** MTIMCG - MTIM1 Clock Configuration Register; 0xFFFF82A0 ***/
   uchar MTIMCLK;    /*** MTIMCLK - MTIM1 Clock Configuration Register; 0xFFFF82A1 ***/
   uchar MTIMCNT;    /*** MTIMCNT - MTIM1 Counter Register; 0xFFFF82A2 ***/
   uchar MTIMMOD;   /*** MTIMMOD - MTIM1 Modulo Register; 0xFFFF82A3 ***/   
   
} MCF51CN_MTIM_STRUCT, _PTR_ MCF51CN_MTIM_STRUCT_PTR;
typedef volatile struct MCF51CN_mtim_struct _PTR_ VMCF51CN_MTIM_STRUCT_PTR;

/*
** MCF51CN_MCG_STRUCT
** Multi clock generator module
*/
typedef struct MCF51CN_mcg_struct
{
  uchar MCGC1;  /*** MCGC1 - MCG Control Register 1; 0xFFFF8240 ***/
  uchar MCGC2;  /*** MCGC2 - MCG Control Register 2; 0xFFFF8241 ***/
  uchar MCGTRM; /*** MCGTRM - MCG Trim Register; 0xFFFF8242 ***/
  uchar MCGSC;  /*** MCGSC - MCG Status and Control Register; 0xFFFF8243 ***/
  uchar MCGC3;  /*** MCGC3 - MCG Control Register 3; 0xFFFF8244 ***/
  uchar MCGC4;  /*** MCGC4 - MCG Control Register 4; 0xFFFF8245 ***/
} MCF51CN_MCG_STRUCT, _PTR_ MCF51CN_MCG_STRUCT_PTR;
typedef volatile struct MCF51CN_mcg_struct _PTR_ VMCF51CN_MCG_STRUCT_PTR;

#define ALIGN_TO(x) (x)
#define USE_REFERENCE(x) -sizeof(x)
#define AT_ADDRESS(x)   -x
typedef struct MCF51CN_struct
{
   MCF51CN_GPIO_STRUCT   GPIO;   
   uchar     reserved01[0x80E0 - 0x8000 - sizeof(MCF51CN_GPIO_STRUCT)];   
   MCF51CN_IRQ_STRUCT    IRQ;
   uchar         reserved02[0x8100 - 0x80E0 - sizeof(MCF51CN_IRQ_STRUCT)];
   MCF51CN_SIM_STRUCT    SIM;
   uchar         reserved03[0x8120 - 0x8100 - sizeof(MCF51CN_SIM_STRUCT)];
   MCF51XX_PMC_STRUCT    PMC;
   uchar         reserved04[0x8140 - 0x8120 - sizeof(MCF51XX_PMC_STRUCT)];
   MCF51CN_ADC_STRUCT    ADC;
   uchar         reserved05[0x8160 - 0x8140 - sizeof(MCF51CN_ADC_STRUCT)];
   MCF51XX_SCI_STRUCT    SCI1;
   uchar         reserved06[0x8180 - 0x8160 - sizeof(MCF51XX_SCI_STRUCT)];
   MCF51XX_SCI_STRUCT    SCI2;
   uchar         reserved07[0x81A0 - 0x8180 - sizeof(MCF51XX_SCI_STRUCT)];
   MCF51XX_SCI_STRUCT    SCI3;
   uchar         reserved08[0x81C0 - 0x81A0 - sizeof(MCF51XX_SCI_STRUCT)];
   MCF5XXX_SPI8_STRUCT   SPI1;
   uchar         reserved09[0x81E0 - 0x81C0 - sizeof(MCF5XXX_SPI8_STRUCT)];
   MCF5XXX_SPI8_STRUCT   SPI2;
   uchar         reserved10[0x8200 - 0x81E0 - sizeof(MCF5XXX_SPI8_STRUCT)];
   MCF51XX_I2C_STRUCT    I2C1;
   uchar         reserved11[0x8220 - 0x8200 - sizeof(MCF51XX_I2C_STRUCT)];
   MCF51XX_I2C_STRUCT    I2C2;
   uchar         reserved12[0x8240 - 0x8220 - sizeof(MCF51XX_I2C_STRUCT)];
   MCF51CN_MCG_STRUCT  MCG;    
   uchar         reserved13[0x82A0 - 0x8240 - sizeof(MCF51CN_MCG_STRUCT)];
   MCF51CN_MTIM_STRUCT   MTIM1;
   uchar     reserved14[0x82C0 - 0x82A0 - sizeof(MCF51CN_MTIM_STRUCT)];
   MCF51XX_RTC_STRUCT   RTC;
   uchar     reserved15[0x82E0 - 0x82C0 - sizeof(MCF51XX_RTC_STRUCT)];
   MCF51XX_FTSR_STRUCT  FTSR;
   uchar     reserved16[0x8300 - 0x82E0 - sizeof(MCF51XX_FTSR_STRUCT)];
   MCF51CN_MTIM_STRUCT   MTIM2;
   uchar     reserved17[0xe000 - 0x8300 - sizeof(MCF51CN_MTIM_STRUCT)];
   MCF5XXX_FEC_STRUCT        FEC;
//   uchar     reserved18[0xE800 - 0xE000 - sizeof(MCF5XXX_FEC_STRUCT)];
   MCF5XXX_MINIFB_STRUCT    MB;
} MCF51CN_STRUCT, _PTR_ MCF51CN_STRUCT_PTR;
typedef volatile struct MCF51CN_struct _PTR_ VMCF51CN_STRUCT_PTR;

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

extern pointer _mcf51CN_get_ipsbar(void);
extern void    _mcf51CN_initialize_support(uint_32);

extern void    _mcf51CN_cache_enable(uint_32);
extern void    _mcf51CN_cache_disable(void);
extern void    _mcf51CN_icache_invalidate(void);
extern void    _mcf51CN_dcache_invalidate(void);

extern void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
extern void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

extern void    _mcf51CN_mmu_init(uint_32);
extern uint_32 _mcf51CN_mmu_enable(void);
extern uint_32 _mcf51CN_mmu_disable(void);
extern uint_32 _mcf51CN_mmu_add_region(pointer,uint_32,uint_32);

extern void    __psp_enable_acrs(uint_32_ptr);
extern void    __psp_clear_acrs(void);
extern void    __psp_dcache_flush(uint_32,uint_32,uint_32);

#endif //__ASM__

#ifdef __cplusplus
}
#endif


#endif // __mcf51CN_h__
/* EOF */

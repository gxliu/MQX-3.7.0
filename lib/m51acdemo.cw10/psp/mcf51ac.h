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
* $FileName: mcf51ac.h$
* $Version : 3.6.1.0$
* $Date    : May-18-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf5225x processors.
*
*END************************************************************************/

#ifndef __mcf51ac_h__
#define __mcf51ac_h__

#define __mcf51ac_h__version "$Version:3.6.1.0$"
#define __mcf51ac_h__date    "$Date:May-18-2010$"

#ifndef __ASM__
/* Include registers for modules common to all Coldfire processors */
#include <mcf51xx_ictl.h>       /* CTRL */   
#include <mcf51xx_sci.h>        /* SCI */
#include <mcf51ac_adc.h>        /* ADC */
#include <mcf51ac_i2c.h>        /* I2C */
#include <mcf5xxx_spi8.h>
#include <mcf5xxx_spi16.h>
#include <mcf51xx_ftsr.h> 
#include <mcf51xx_pmc.h> 

#endif /* __ASM__ */

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* Indicate processor type */
#define PSP_MCF51AC                         1

#define PSP_HAS_DSP                         0
#define PSP_HAS_EMAC                        0

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  0
#define PSP_HAS_DATA_CACHE                  0


#ifndef __ASM__

#define MCF51AC_NUM_ACRS                    (2)

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
#define MCF51AC_NUM_TIMERS                (1)

#define MCF51XX_SOPT1_WAITE_MASK                16
#define MCF51XX_SOPT1_STOPE_MASK                32
#define MCF51XX_SOPT1_COPT_MASK                 64
#define MCF51XX_SOPT1_COPT_BITNUM               6
#define MCF51XX_SOPT1_COPE_MASK                 128
#define MCF51XX_SOPT1_COPE_BITNUM               7


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
typedef enum mcf51ac_interrupt_table_index {
  MCF51AC_INT_INITSP      =       0,
  MCF51AC_INT_INITPC      =       1,
  MCF51AC_INT_Vaccerr     =       2,
  MCF51AC_INT_Vadderr     =       3,
  MCF51AC_INT_Viinstr     =       4,
  MCF51AC_INT_VReserved5  =       5,
  MCF51AC_INT_VReserved6  =       6,
  MCF51AC_INT_VReserved7  =       7,
  MCF51AC_INT_Vprviol     =       8,
  MCF51AC_INT_Vtrace      =       9,
  MCF51AC_INT_Vunilaop    =       10,
  MCF51AC_INT_Vunilfop    =       11,
  MCF51AC_INT_Vdbgi       =       12,
  MCF51AC_INT_VReserved13 =       13,
  MCF51AC_INT_Vferror     =       14,
  MCF51AC_INT_VReserved15 =       15,
  MCF51AC_INT_VReserved16 =       16,
  MCF51AC_INT_VReserved17 =       17,
  MCF51AC_INT_VReserved18 =       18,
  MCF51AC_INT_VReserved19 =       19,
  MCF51AC_INT_VReserved20 =       20,
  MCF51AC_INT_VReserved21 =       21,
  MCF51AC_INT_VReserved22 =       22,
  MCF51AC_INT_VReserved23 =       23,
  MCF51AC_INT_Vspuri      =       24,
  MCF51AC_INT_VReserved25 =       25,
  MCF51AC_INT_VReserved26 =       26,
  MCF51AC_INT_VReserved27 =       27,
  MCF51AC_INT_VReserved28 =       28,
  MCF51AC_INT_VReserved29 =       29,
  MCF51AC_INT_VReserved30 =       30,
  MCF51AC_INT_VReserved31 =       31,
  MCF51AC_INT_Vtrap0      =       32,
  MCF51AC_INT_Vtrap1      =       33,
  MCF51AC_INT_Vtrap2      =       34,
  MCF51AC_INT_Vtrap3      =       35,
  MCF51AC_INT_Vtrap4      =       36,
  MCF51AC_INT_Vtrap5      =       37,
  MCF51AC_INT_Vtrap6      =       38,
  MCF51AC_INT_Vtrap7      =       39,
  MCF51AC_INT_Vtrap8      =       40,
  MCF51AC_INT_Vtrap9      =       41,
  MCF51AC_INT_Vtrap10     =       42,
  MCF51AC_INT_Vtrap11     =       43,
  MCF51AC_INT_Vtrap12     =       44,
  MCF51AC_INT_Vtrap13     =       45,
  MCF51AC_INT_Vtrap14     =       46,
  MCF51AC_INT_Vtrap15     =       47,
  MCF51AC_INT_VReserved48 =       48,
  MCF51AC_INT_VReserved49 =       49,
  MCF51AC_INT_VReserved50 =       50,
  MCF51AC_INT_VReserved51 =       51,
  MCF51AC_INT_VReserved52 =       52,
  MCF51AC_INT_VReserved53 =       53,
  MCF51AC_INT_VReserved54 =       54,
  MCF51AC_INT_VReserved55 =       55,
  MCF51AC_INT_VReserved56 =       56,
  MCF51AC_INT_VReserved57 =       57,
  MCF51AC_INT_VReserved58 =       58,
  MCF51AC_INT_VReserved59 =       59,
  MCF51AC_INT_VReserved60 =       60,
  MCF51AC_INT_Vunsinstr   =       61,
  MCF51AC_INT_VReserved62 =       62,
  MCF51AC_INT_VReserved63 =       63,
  MCF51AC_INT_Virq        =       64,
  MCF51AC_INT_Vlvd        =       65,
  MCF51AC_INT_Vmcglock    =       66,
  MCF51AC_INT_Vftm1ch0    =       67,
  MCF51AC_INT_Vftm1ch1    =       68,
  MCF51AC_INT_Vftm1ch2    =       69,
  MCF51AC_INT_Vftm1ch3    =       70,  
  MCF51AC_INT_Vftm1ch4    =       71,
  MCF51AC_INT_Vftm1ch5    =       72,
  MCF51AC_INT_Vfpm1ovf    =       73,
  MCF51AC_INT_Vftm2ch0    =       74,
  MCF51AC_INT_Vftm2ch1    =       75,
  MCF51AC_INT_Vftm2ch2    =       76,
  MCF51AC_INT_Vftm2ch3    =       77,  
  MCF51AC_INT_Vftm2ch4    =       78,
  MCF51AC_INT_Vftm2ch5    =       79,
  MCF51AC_INT_Vftm2ovf    =       80,
  MCF51AC_INT_Vspi1       =       81,  
  MCF51AC_INT_Vsci1err    =       82,
  MCF51AC_INT_Vsci1rx     =       83,
  MCF51AC_INT_Vsci1tx     =       84,
  MCF51AC_INT_Vsci2err    =       85,
  MCF51AC_INT_Vsci2rx     =       86,
  MCF51AC_INT_Vsci2tx     =       87,
  MCF51AC_INT_Vkeyboard  =        88,
  MCF51AC_INT_Vadc        =       89,  
  MCF51AC_INT_Viic1       =       90,
  MCF51AC_INT_Vrti        =       91,  
  MCF51AC_INT_Vtmp3ch0    =       92,
  MCF51AC_INT_Vtmp3ch1    =       93,
  MCF51AC_INT_VReserved94 =       94,
  MCF51AC_INT_VReserved95 =       95,
  MCF51AC_INT_VReserved96 =       96,
  MCF51AC_INT_VReserved97 =       97,
  MCF51AC_INT_VReserved98 =       98,    
  MCF51AC_INT_VReserved99 =       99,  
  MCF51AC_INT_VReserved100 =      100,  
  MCF51AC_INT_VReserved101 =      101,  
  MCF51AC_INT_VReserved102 =      102,    
  MCF51AC_INT_VL7swi      =       103,
  MCF51AC_INT_VL6swi      =       104,
  MCF51AC_INT_VL5swi      =       105,
  MCF51AC_INT_VL4swi      =       106,
  MCF51AC_INT_VL3swi      =       107,
  MCF51AC_INT_VL2swi      =       108,
  MCF51AC_INT_VL1swi      =       109,
  MCF51AC_INT_Vtpm3ovf    =       110,
  MCF51AC_INT_Vspi2       =       111,    
  MCF51AC_INT_Vftm1flt    =       112,
  MCF51AC_INT_Vftm2flt    =       113,
  MCF51AC_INT_Vcanwu      =       114,          
  MCF51AC_INT_Vcanerr     =       115,
  MCF51AC_INT_Vcanrx      =       116,
  MCF51AC_INT_Vcantx      =       117,
  MCF51AC_INT_Vacmp1      =       118,
  MCF51AC_INT_Vacmp2      =       119  
} MCF51AC_INTERRUPT_TABLE_INDEX;//, PSP_INTERRUPT_TABLE_INDEX;


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
#define MCF51XX_SCGC1_IIC_MASK                  4
#define MCF51XX_SCGC1_CAN_MASK                  8
#define MCF51XX_SCGC1_ADC_MASK                  16
#define MCF51XX_SCGC1_FTM1_MASK                 32
#define MCF51XX_SCGC1_FTM2_MASK                 64
#define MCF51XX_SCGC1_TPM3_MASK                128
#define MCF51XX_SCGC1_SCI_1_MASK                3
#define MCF51XX_SCGC1_SCI_1_BITNUM              0
#define MCF51XX_SCGC1_IIC_BITNUM                2
#define MCF51XX_SCGC1_CAN_BITNUM                3
#define MCF51XX_SCGC1_ADC_BITNUM                4
#define MCF51XX_SCGC1_FTM_1_MASK                96
#define MCF51XX_SCGC1_FTM_1_BITNUM              5
#define MCF51XX_SCGC1_TMP3_BITNUM               7

#define MCF51XX_SCGC2_SPI1_MASK                 1
#define MCF51XX_SCGC2_SPI2_MASK                 2
#define MCF51XX_SCGC2_RTI_MASK                  4
#define MCF51XX_SCGC2_ACMPx_MASK                 8
#define MCF51XX_SCGC2_KBIx_MASK                 16
#define MCF51XX_SCGC2_IRQ_MASK                  32
#define MCF51XX_SCGC2_FTSR_MASK                 64
#define MCF51XX_SCGC2_CRC_MASK                 128
#define MCF51XX_SCGC2_SPI_1_MASK                3
#define MCF51XX_SCGC2_SPI_1_BITNUM              0
#define MCF51XX_SCGC1_RTI_BITNUM               2
#define MCF51XX_SCGC1_ACMPx_BITNUM               3
#define MCF51XX_SCGC1_KBIx_BITNUM               4
#define MCF51XX_SCGC1_IRQ_BITNUM               5
#define MCF51XX_SCGC1_FLS_BITNUM               6
#define MCF51XX_SCGC1_CRC_BITNUM               7
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


#define MCF51XX_SOPT2_BIG_END                   0x20

/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/

/*
** MCF51AC_ftm_struct
** This structure defines FTM registers
*/ 

typedef enum {
    FTM_CHANNEL_0 = 0,
    FTM_CHANNEL_1,
    FTM_CHANNEL_2,
    FTM_CHANNEL_3,
    FTM_CHANNEL_4,
    FTM_CHANNEL_5,
    FTM_CHANNEL_MAX
} ftm_channel_t;

typedef struct _ftm_channel_struct
{
    uint_8  FTMxCySC;           /* FTM Status and Control                           */
    uint_16 FTMxCyV;            /* FTM Channel Value                                */
} FTM_CHANNEL_STRUCT, _PTR_ FTM_CHANNEL_STRUCT_PTR;

typedef struct MCF51AC_ftm_struct
{
    uint_8  FTMxSC;             /* FTM Status and Control                           */
    uint_16 FTMxCNT;            /* FTM Counter Register                             */
    uint_16 FTMxMOD;            /* FTM Counter Modulo                               */
    FTM_CHANNEL_STRUCT FTMxC[FTM_CHANNEL_MAX];  /* FTM Channel Structure            */   
    FTM_CHANNEL_STRUCT FTMxC_reserved[2];
    uint_16 FTMxCNTIN;          /* FTM Counter Initial Value                        */
    uint_8  FTMxSTATUS;         /* FTM Capture and Compare Status                   */
    uint_8  FTMxMODE;           /* FTM Features Mode Selection                      */
    uint_8  FTMxSYNC;           /* FTM Synchronization                              */
    uint_8  FTMxOUTINIT;        /* FTM Initial State for Channels Output            */
    uint_8  FTMxOUTMASK;        /* FTM Output Mask                                  */
    uint_8  FTMxCOMBINE[FTM_CHANNEL_MAX / 2]; /* FTM Function For Linked Channels   */
    uint_8  FTMxCOMBINE_reserved[1];          /* FTM Function For Linked Channels   */
    uint_8  FTMxDEADTIME;       /* FTM Deadtime Insertion Control                   */
    uint_8  FTMxEXTTRIG;        /* FTM External Trigger                             */
    uint_8  FTMxPOL;            /* FTM Channels Polarity                            */
    uint_8  FTMxFMS;            /* FTM Fault Mode Status                            */
    uint_8  FTMxFILTER[2];      /* FTM Input Capture Filter Control                 */
    uint_8  FTMxFLTFILTER;      /* FTM Fault Input Filter Control                   */
    uint_8  FTMxRFU;            /* FTM Register for Future Use                      */
} MCF51AC_FTM_STRUCT, _PTR_ MCF51AC_FTM_STRUCT_PTR;
typedef volatile struct MCF51AC_ftm_struct _PTR_ VMCF51AC_FTM_STRUCT_PTR;

/*
** MCF51AC_can_struct
** This structure defines CAN registers
*/ 
typedef struct MCF51AC_can_struct
{
    uint_8 CANCTL0;
    uint_8 CANCTL1;
    uint_8 CANBTR0;
    uint_8 CANBTR1;
    uint_8 CANRFLG;
    uint_8 CANRIER;
    uint_8 CANTFLG;
    uint_8 CANTIER;
    uint_8 CANTARQ;
    uint_8 CANTAAK;
    uint_8 CANTBSEL;
    uint_8 CANIDAC;
    uint_8 reserved01;
    uint_8 CANMISC;
    uint_8 CANRXERR;
    uint_8 CANTXERR;
    uint_8 CANIDAR0;
    uint_8 CANIDAR1;
    uint_8 CANIDAR2;
    uint_8 CANIDAR3;
    uint_8 CANIDMR0;
    uint_8 CANIDMR1;
    uint_8 CANIDMR2;
    uint_8 CANIDMR3;
    uint_8 CANIDAR4;
    uint_8 CANIDAR5;
    uint_8 CANIDAR6;
    uint_8 CANIDAR7;
    uint_8 CANIDMR4;
    uint_8 CANIDMR5;
    uint_8 CANIDMR6;
    uint_8 CANIDMR7;
    uint_8 MSCAN_RX_BUF[0x10];
    uint_8 MSCAN_TX_BUF[0x10];
} MCF51AC_CAN_STRUCT, _PTR_ MCF51AC_CAN_STRUCT_PTR;
typedef volatile struct MCF51AC_can_struct _PTR_ VMCF51AC_CAN_STRUCT_PTR;

/* This structure defines (Rapid) General Purpose I/O registers (APPROACH #2) */

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

typedef struct MCF51AC_gpio_data_struct
{
   uint_8  PTxD;      /*** Port Data ***/
   uint_8  PTxDD;     /*** Port Data Direction ***/
} MCF51AC_GPIO_DATA_STRUCT, _PTR_ MCF51AC_GPIO_DATA_STRUCT_PTR;
typedef volatile struct MCF51AC_gpio_data_struct _PTR_ VMCF51AC_GPIO_DATA_STRUCT_PTR;

typedef struct MCF51AC_gpio_struct
{
   uint_8  PTxPE;     /*** Port Pull-Up Enable ***/
   uint_8  PTxSE;     /*** Port Slew Rate Control ***/
   uint_8  PTxDS;     /*** Port Drive Strength Control ***/
   uint_8  reserved01;
} MCF51AC_GPIO_STRUCT, _PTR_ MCF51AC_GPIO_STRUCT_PTR;
typedef volatile struct MCF51AC_gpio_struct _PTR_ VMCF51AC_GPIO_STRUCT_PTR;

/*
** MCF51AC_irq_struct
** This structure defines Interrupt registers
*/
typedef struct MCF51AC_irq_struct
{
  uint_8  IRQSC;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
} MCF51AC_IRQ_STRUCT, _PTR_ MCF51AC_IRQ_STRUCT_PTR;
typedef volatile struct MCF51AC_irq_struct _PTR_ VMCF51AC_IRQ_STRUCT_PTR;

/*
** MCF51AC_crc_struct
** This structure defines CRC registers
*/
typedef struct MCF51AC_crc_struct
{
  uint_8 CRCH;
  uint_8 CRCL;
} MCF51AC_CRC_STRUCT, _PTR_ MCF51AC_CRC_STRUCT_PTR;
typedef volatile struct MCF51AC_crc_struct _PTR_ VMCF51AC_CRC_STRUCT_PTR;

typedef struct MCF51AC_tpm_channel_struct
{
  uint_8    TPMxCySC;
  uint_16  TPMxCyV; //TPMxCyVH and TPMxCyVL registers
} MCF51AC_TPM_CHANNEL_STRUCT, _PTR_ MCF51AC_TPM_CHANNEL_STRUCT_PTR;
typedef volatile struct MCF51AC_tpm_channel_struct _PTR_ VMCF51AC_TPM_CHANNEL_STRUCT_PTR;

typedef struct MCF51AC_tpm_struct
{
  uint_8   TPMxSC; 
  uint_16  TPMxCNT;  //TPMxCNTH and TPMxCNTL registers
  uint_16  TPMxMOD;  //TPMxMODH and TPMxMODL registers
  MCF51AC_TPM_CHANNEL_STRUCT TPMxC[2];
} MCF51AC_TPM_STRUCT, _PTR_ MCF51AC_TPM_STRUCT_PTR;
typedef volatile struct MCF51AC_tpm_struct _PTR_ VMCF51AC_TPM_STRUCT_PTR;

/*
** MCF51AC_kbi_struct
** This structure defines Interrupt registers
*/

typedef struct MCF51AC_kbi_struct
{
  uint_8  KBIxSC;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
  uint_8  KBIxPE;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
} MCF51AC_KBI_STRUCT, _PTR_ MCF51AC_KBI_STRUCT_PTR;
typedef volatile struct MCF51AC_kbi_struct _PTR_ VMCF51AC_KBI_STRUCT_PTR;


/*
** MCF51AC_MCG_STRUCT
** Multi clock generator module
*/
typedef struct MCF51AC_mcg_struct
{
  uint_8 MCGC1;  /*** MCGC1 - MCG Control Register 1; 0xFFFF8048 ***/
  uint_8 MCGC2;  /*** MCGC2 - MCG Control Register 2; 0xFFFF8049 ***/
  uint_8 MCGTRM; /*** MCGTRM - MCG Trim Register; 0xFFFF804A ***/
  uint_8 MCGSC;  /*** MCGSC - MCG Status and Control Register; 0xFFFF804B ***/
  uint_8 MCGC3;  /*** MCGC3 - MCG Control Register 3; 0xFFFF804C ***/
  uint_8 MCGC4;  /*** MCGC4 - MCG Control Register 4; 0xFFFF804D ***/
  uint_8 reserved01; /*** MCGT - MCG Test Register; 0xFFFF804E; reserved for factory use ***/ 
} MCF51AC_MCG_STRUCT, _PTR_ MCF51AC_MCG_STRUCT_PTR;
typedef volatile struct MCF51AC_mcg_struct _PTR_ VMCF51AC_MCG_STRUCT_PTR;

/*
** MCF51AC_sim_struct
** This structure defines System Integration Module registers
*/
typedef struct MCF51AC_sim_struct
{
   uint_8 SRS;
   uint_8 reserved01;
   uint_8 SOPT;
   uint_8 SMCLK;
   uint_8 reserved02[2];
   uint_8 SDIDH;
   uint_8 SDIDL;
   uint_8 SRTISC;
   uint_8 SPMSC1;
   uint_8 SPMSC2;
   uint_8 reserved03;
   uint_8 SOPT2;
   uint_8 SCGC1;
   uint_8 SCGC2;
}MCF51AC_SIM_STRUCT, _PTR_ MCF51AC_SIM_STRUCT_PTR;
typedef volatile struct MCF51AC_sim_struct _PTR_ VMCF51AC_SIM_STRUCT_PTR;

typedef struct MCF51AC_acpm_struct
{
   uint_8 ACPMxSC;
} MCF51AC_ACPM_STRUCT, _PTR_ MCF51AC_ACPM_STRUCT_PTR;
typedef volatile struct MCF51AC_acpm_struct _PTR_ VMCF51AC_ACPM_STRUCT_PTR;

#define ALIGN_TO(x) (x)
#define USE_REFERENCE(x) -sizeof(x)
#define AT_ADDRESS(x)   -x
typedef struct MCF51AC_struct
{   
    MCF51AC_GPIO_DATA_STRUCT GPIO_A;        /* 0x8000 - 0x800F */
    MCF51AC_GPIO_DATA_STRUCT GPIO_B;
    MCF51AC_GPIO_DATA_STRUCT GPIO_C;
    MCF51AC_GPIO_DATA_STRUCT GPIO_D;
    MCF51AC_GPIO_DATA_STRUCT GPIO_E;
    MCF51AC_GPIO_DATA_STRUCT GPIO_F;
    MCF51AC_GPIO_DATA_STRUCT GPIO_G;
    MCF51AC_GPIO_DATA_STRUCT GPIO_H;   
    MCF51AC_ADC_STRUCT       ADC;           /* 0x8010 - 0x8019 */ 
    MCF51AC_GPIO_DATA_STRUCT GPIO_J;        /* 0x801A - 0x801B */   
    MCF51AC_IRQ_STRUCT       IRQ;           /* 0x801C */
    uint_8 reserved01[0x801E - 0x801C - sizeof(MCF51AC_IRQ_STRUCT)];   
    MCF51AC_KBI_STRUCT       KBI;           /* 0x801E - 0x801F */
    uint_8 reserved02[0x8038-0x801E - sizeof(MCF51AC_KBI_STRUCT)];   
    MCF51XX_SCI_STRUCT       SCI1;          /* 0x8038 - 0x8047 */
    MCF51XX_SCI_STRUCT       SCI2;   
    MCF51AC_MCG_STRUCT       MCG;           /* 0x8048 - 0x804E */   
    uint_8 reserved03[0x8050 - 0x8048 - sizeof(MCF51AC_MCG_STRUCT)];
    MCF5XXX_SPI8_STRUCT      SPI1;          /* 0x8050 - 0x8055 */
    uint_8 reserved04[ 0x8058 - 0x8050 - sizeof(MCF5XXX_SPI8_STRUCT)];   
    MCF51AC_I2C_STRUCT       I2C1;          /* 0x8058 - 0x805D */
    MCF51AC_ACPM_STRUCT      ACMP1;         /* 0x805E */
    MCF51AC_ACPM_STRUCT      ACMP2;         /* 0x805F */
    uint_8 reserved05[0x8080-0x805F - sizeof(MCF51AC_ACPM_STRUCT)];
    MCF51AC_FTM_STRUCT       FTM1;          /* 0x8080 - 0x80AD */
    uint_8 reserved06[0x80C0- 0x8080 - sizeof(MCF51AC_FTM_STRUCT)];
    MCF51AC_FTM_STRUCT       FTM2;          /* 0x80C0 - 0x80ED */
    uint_8 reserved07[0x9800-0x80C0 - sizeof(MCF51AC_FTM_STRUCT)];  
    MCF51AC_SIM_STRUCT       SIM;           /* 0x9800 - 0x980E */
    uint_8 reserved08[0x9820-0x9800 - sizeof(MCF51AC_SIM_STRUCT)];
    MCF51XX_FTSR_STRUCT      FTSR;          /* 0x9820 - 0x9826 */
    MCF51AC_TPM_STRUCT       TPM3;          /* 0x9830 - 0x983A */
    uint_8 reserved10[0x9840 - 0x9830 - sizeof(MCF51AC_TPM_STRUCT)];
    MCF51AC_GPIO_STRUCT      GPIO_SET_A;
    MCF51AC_GPIO_STRUCT      GPIO_SET_B;
    MCF51AC_GPIO_STRUCT      GPIO_SET_C;
    MCF51AC_GPIO_STRUCT      GPIO_SET_D;
    MCF51AC_GPIO_STRUCT      GPIO_SET_E;
    MCF51AC_GPIO_STRUCT      GPIO_SET_F;
    MCF51AC_GPIO_STRUCT      GPIO_SET_G;
    MCF51AC_GPIO_STRUCT      GPIO_SET_H; 
    MCF51AC_GPIO_STRUCT      GPIO_SET_J;   
    uint_8 reserved11[0x9868 - 0x9840 -(sizeof(MCF51AC_GPIO_STRUCT) * GPIO_PORT_MAX )];
    MCF5XXX_SPI16_STRUCT     SPI2;
    uint_8 reserved12[0x9880 - 0x9868 - sizeof(MCF5XXX_SPI16_STRUCT)];
    MCF51AC_CAN_STRUCT       CAN;
    MCF51AC_CRC_STRUCT       CRC;
    uint_8 reserved0B[2];
    uint_8 CRCL[4];
    uint_8 reserved0C[0x98CF-0x98C7];
} MCF51AC_STRUCT, _PTR_ MCF51AC_STRUCT_PTR;
typedef volatile struct MCF51AC_struct _PTR_ VMCF51AC_STRUCT_PTR;


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
extern          uint_8   __KERNEL_DATA_VERIFY_ENABLE[]; // CR1327

extern pointer _mcf51AC_get_ipsbar(void);
extern void    _mcf51AC_initialize_support(uint_32);

extern void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
extern void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

extern void    __psp_enable_acrs(uint_32_ptr);
extern void    __psp_clear_acrs(void);
extern void    __psp_dcache_flush(uint_32,uint_32,uint_32);

#endif //__ASM__

#ifdef __cplusplus
}
#endif


#endif // __mcf51AC_h__
/* EOF */

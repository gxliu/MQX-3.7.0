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
* $FileName: mcf51ag.h$
* $Version : 3.7.3.0$
* $Date    : Feb-22-2011$
*
* Comments:
*
*   This file contains the type definitions for the mcf5225x processors.
*
*END************************************************************************/

#ifndef __mcf51ag_h__
#define __mcf51ag_h__

#define __mcf51ag_h__version "$Version:3.7.3.0$"
#define __mcf51ag_h__date    "$Date:Feb-22-2011$"

#ifndef __ASM__
/* Include registers for modules common to all Coldfire processors */
#include <mcf51xx_ictl.h>         /* CTRL */
#include <mcf51xx_sci.h>          /* SCI */
#include <mcf51xx_i2c.h>          /* I2C */
#include <mcf51ag_adc.h>
#include <mcf51xx_rtc.h>
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
#define PSP_MCF51AG                         1

#define PSP_HAS_DSP                         0
#define PSP_HAS_EMAC                        0

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  0
#define PSP_HAS_DATA_CACHE                  0

#ifndef __ASM__

#define MCF51AG_NUM_ACRS                    (2)

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
#define MCF51AG_NUM_TIMERS                (1) /* TPM3 */

#define MCF51XX_SOPT1_WAITE_MASK                           16
#define MCF51XX_SOPT1_STOPE_MASK                           32

#define MCF51XX_SRS_LVD_MASK                               2
#define MCF51XX_SRS_LOC_MASK                               4
#define MCF51XX_SRS_ILAD_MASK                              8
#define MCF51XX_SRS_ILOP_MASK                              16
#define MCF51XX_SRS_COP_MASK                               32
#define MCF51XX_SRS_PIN_MASK                               64
#define MCF51XX_SRS_POR_MASK                               128

#define MCF51XX_WDOG_UNLOCK_LVD_MASK                       2
#define MCF51XX_WDOG_UNLOCK_LOC_MASK                       4
#define MCF51XX_WDOG_UNLOCK_ILAD_MASK                      8
#define MCF51XX_WDOG_UNLOCK_ILOP_MASK                      16
#define MCF51XX_WDOG_UNLOCK_COP_MASK                       32
#define MCF51XX_WDOG_UNLOCK_PIN_MASK                       64
#define MCF51XX_WDOG_UNLOCK_POR_MASK                       128

#define MCF51XX_WDOG_ST_CTRL_H_WDOC_EN_MASK                1
#define MCF51XX_WDOG_ST_CTRL_H_CLK_SRC_MASK                2
#define MCF51XX_WDOG_ST_CTRL_H_IRQ_RST_EN_MASK             4
#define MCF51XX_WDOG_ST_CTRL_H_WIN_EN_MASK                 8
#define MCF51XX_WDOG_ST_CTRL_H_ALLOW_UPDATE_MASK           16
#define MCF51XX_WDOG_ST_CTRL_H_DBG_EN_MASK                 32
#define MCF51XX_WDOG_ST_CTRL_H_STOP_EN_MASK                64
#define MCF51XX_WDOG_ST_CTRL_H_WAIT_EN_MASK                128
#define MCF51XX_WDOG_ST_CTRL_H_TESTWDOG_MASK               1024
#define MCF51XX_WDOG_ST_CTRL_H_TESTSEL_MASK                2048
#define MCF51XX_WDOG_ST_CTRL_H_BYTESEL0_MASK               4096
#define MCF51XX_WDOG_ST_CTRL_H_BYTESEL1_MASK               8192
#define MCF51XX_WDOG_ST_CTRL_H_DISABLE_TESTWDOG_MASK       16384

#define MCF51XX_SPMSC1_BGBE_MASK                           1
#define MCF51XX_SPMSC1_LVDE_MASK                           4
#define MCF51XX_SPMSC1_LVDSE_MASK                          8
#define MCF51XX_SPMSC1_LVDRE_MASK                          16
#define MCF51XX_SPMSC1_LVWIE_MASK                          32
#define MCF51XX_SPMSC1_LVWACK_MASK                         64
#define MCF51XX_SPMSC1_LVWF_MASK                           128

#define MCF51XX_SPMSC2_PPDC_MASK                           1
#define MCF51XX_SPMSC2_PPDACK_MASK                         4
#define MCF51XX_SPMSC2_PPDF_MASK                           8
#define MCF51XX_SPMSC2_LVWV_MASK                           16
#define MCF51XX_SPMSC2_LVDV_MASK                           32

#define MCF51XX_SMCLK_MCSEL0_MASK                          1
#define MCF51XX_SMCLK_MCSEL1_MASK                          2
#define MCF51XX_SMCLK_MCSEL2_MASK                          4
#define MCF51XX_SMCLK_MCSEL_MASK                           7
#define MCF51XX_SMCLK_MCSEL_BITNUM                         0
#define MCF51XX_SMCLK_MPE_MASK                             16
 /*
** Interrupt vector table
*/
typedef enum mcf51ag_interrupt_table_index {
  MCF51AG_INT_INITSP      =       0,
  MCF51AG_INT_INITPC      =       1,
  MCF51AG_INT_Vaccerr     =       2,
  MCF51AG_INT_Vadderr     =       3,
  MCF51AG_INT_Viinstr     =       4,
  MCF51AG_INT_VReserved5  =       5,
  MCF51AG_INT_VReserved6  =       6,
  MCF51AG_INT_VReserved7  =       7,
  MCF51AG_INT_Vprviol     =       8,
  MCF51AG_INT_Vtrace      =       9,
  MCF51AG_INT_Vunilaop    =       10,
  MCF51AG_INT_Vunilfop    =       11,
  MCF51AG_INT_Vdbgi       =       12,
  MCF51AG_INT_VReserved13 =       13,
  MCF51AG_INT_Vferror     =       14,
  MCF51AG_INT_VReserved15 =       15,
  MCF51AG_INT_VReserved16 =       16,
  MCF51AG_INT_VReserved17 =       17,
  MCF51AG_INT_VReserved18 =       18,
  MCF51AG_INT_VReserved19 =       19,
  MCF51AG_INT_VReserved20 =       20,
  MCF51AG_INT_VReserved21 =       21,
  MCF51AG_INT_VReserved22 =       22,
  MCF51AG_INT_VReserved23 =       23,
  MCF51AG_INT_Vspuri      =       24,
  MCF51AG_INT_VReserved25 =       25,
  MCF51AG_INT_VReserved26 =       26,
  MCF51AG_INT_VReserved27 =       27,
  MCF51AG_INT_VReserved28 =       28,
  MCF51AG_INT_VReserved29 =       29,
  MCF51AG_INT_VReserved30 =       30,
  MCF51AG_INT_VReserved31 =       31,
  MCF51AG_INT_Vtrap0      =       32,
  MCF51AG_INT_Vtrap1      =       33,
  MCF51AG_INT_Vtrap2      =       34,
  MCF51AG_INT_Vtrap3      =       35,
  MCF51AG_INT_Vtrap4      =       36,
  MCF51AG_INT_Vtrap5      =       37,
  MCF51AG_INT_Vtrap6      =       38,
  MCF51AG_INT_Vtrap7      =       39,
  MCF51AG_INT_Vtrap8      =       40,
  MCF51AG_INT_Vtrap9      =       41,
  MCF51AG_INT_Vtrap10     =       42,
  MCF51AG_INT_Vtrap11     =       43,
  MCF51AG_INT_Vtrap12     =       44,
  MCF51AG_INT_Vtrap13     =       45,
  MCF51AG_INT_Vtrap14     =       46,
  MCF51AG_INT_Vtrap15     =       47,
  MCF51AG_INT_VReserved48 =       48,
  MCF51AG_INT_VReserved49 =       49,
  MCF51AG_INT_VReserved50 =       50,
  MCF51AG_INT_VReserved51 =       51,
  MCF51AG_INT_VReserved52 =       52,
  MCF51AG_INT_VReserved53 =       53,
  MCF51AG_INT_VReserved54 =       54,
  MCF51AG_INT_VReserved55 =       55,
  MCF51AG_INT_VReserved56 =       56,
  MCF51AG_INT_VReserved57 =       57,
  MCF51AG_INT_VReserved58 =       58,
  MCF51AG_INT_VReserved59 =       59,
  MCF51AG_INT_VReserved60 =       60,
  MCF51AG_INT_Vunsinstr   =       61,
  MCF51AG_INT_VReserved62 =       62,
  MCF51AG_INT_VReserved63 =       63,
  MCF51AG_INT_Virq        =       64,
  MCF51AG_INT_Vlvd        =       65,
  MCF51AG_INT_VReserved66 =       66,
  MCF51AG_INT_VReserved67 =       67,
  MCF51AG_INT_Vdmach0      =       68,
  MCF51AG_INT_Vdmach1      =       69,
  MCF51AG_INT_Vdmach2      =       70,
  MCF51AG_INT_Vdmach3      =       71,
  MCF51AG_INT_Vieventch0   =       72,
  MCF51AG_INT_Vftm1f       =       73,
  MCF51AG_INT_Vftm1ch0     =       74,
  MCF51AG_INT_Vftm1ch1     =       75,
  MCF51AG_INT_Vftm1ch2     =       76,
  MCF51AG_INT_Vftm1ch3     =       77,
  MCF51AG_INT_Vftm1ch4     =       78,
  MCF51AG_INT_Vftm1ch5     =       79,
  MCF51AG_INT_Vftm2f       =       80,
  MCF51AG_INT_Vftm2ch0     =       81,
  MCF51AG_INT_Vftm2ch1     =       82,
  MCF51AG_INT_Vftm2ch2     =       83,
  MCF51AG_INT_Vftm2ch3     =       84,
  MCF51AG_INT_Vftm2ch4     =       85,
  MCF51AG_INT_Vftm2ch5     =       86,
   
  MCF51AG_INT_Vtpm3ovf     =       87,
  MCF51AG_INT_Vtpm3ch0     =       88,  
  MCF51AG_INT_Vtpm3ch1     =       89,  
  MCF51AG_INT_Vadc         =       90,
  MCF51AG_INT_Vhscmp       =       91,  
  MCF51AG_INT_Vhscmp2      =       92,
  MCF51AG_INT_Vieventch1   =       93,
  MCF51AG_INT_Vspi1        =       94,
  MCF51AG_INT_Vspi2        =       95,
  MCF51AG_INT_Vsci1err     =       96,
  MCF51AG_INT_Vsci1rx      =       97,
  MCF51AG_INT_Vsci1tx      =       98,
  MCF51AG_INT_Viic         =       99,
  MCF51AG_INT_Vieventch2   =       100,
  MCF51AG_INT_Vsci2err     =       101,
  MCF51AG_INT_Vsci2rx      =       102,
  MCF51AG_INT_VL7swi       =       103,
  MCF51AG_INT_VL6swi       =       104,
  MCF51AG_INT_VL5swi       =       105,
  MCF51AG_INT_VL4swi       =       106,
  MCF51AG_INT_VL3swi       =       107,
  MCF51AG_INT_VL2swi       =       108,
  MCF51AG_INT_VL1swi       =       109,
  MCF51AG_INT_Vsci2tx      =       110,
  MCF51AG_INT_Vkbiae       =       111,
  MCF51AG_INT_Vkbifj       =       112,
  MCF51AG_INT_Vrtc         =       113,
  MCF51AG_INT_Vieventch3   =       114

} MCF51AG_INTERRUPT_TABLE_INDEX; /*, PSP_INTERRUPT_TABLE_INDEX;  */

/*------------------------------------------------------------------------*/
/*
** PDB
*/
#define MCF51AG_PDB_SCR_PADEN                   (0x0080)
#define MCF51AG_PDB_SCR_PDBEN                   (0x0040)
#define MCF51AG_PDB_SCR_COF                     (0x0020)
#define MCF51AG_PDB_SCR_COIE                    (0x0010)
#define MCF51AG_PDB_SCR_DBF                     (0x0008)
#define MCF51AG_PDB_SCR_DBIE                    (0x0004)
#define MCF51AG_PDB_SCR_DAF                     (0x0002)
#define MCF51AG_PDB_SCR_DAIE                    (0x0001)

#define MCF51AG_PDB_CTRL1_LDMOD                 (0x80)
#define MCF51AG_PDB_CTRL1_BOS(x)                ((x << 0x05) & 0x60)
#define MCF51AG_PDB_CTRL1_BOS_B                 (0x20)
#define MCF51AG_PDB_CTRL1_BOS_MASK              (0x60)
#define MCF51AG_PDB_CTRL1_ENB                   (0x10)
#define MCF51AG_PDB_CTRL1_AOS(x)                ((x << 0x02) & 0x0C)
#define MCF51AG_PDB_CTRL1_AOS_A                 (0x04)
#define MCF51AG_PDB_CTRL1_AOS_MASK              (0x0C)
#define MCF51AG_PDB_CTRL1_ENA                   (0x02)
#define MCF51AG_PDB_CTRL1_LDOK                  (0x01)

#define MCF51AG_PDB_CTRL2_PRESCALER_BITNUM      (0x05)
#define MCF51AG_PDB_CTRL2_PRESCALER(x)          ((x << MCF51AG_PDB_CTRL2_PRESCALER_BITNUM) & 0xE0)
#define MCF51AG_PDB_CTRL2_TRIGSEL_BITNUM        2
#define MCF51AG_PDB_CTRL2_TRIGSEL_TRIGGERIN0    (0 << MCF51AG_PDB_CTRL2_TRIGSEL_BITNUM)
#define MCF51AG_PDB_CTRL2_TRIGSEL_TRIGGERIN1    (1 << MCF51AG_PDB_CTRL2_TRIGSEL_BITNUM)
#define MCF51AG_PDB_CTRL2_TRIGSEL_TRIGGERIN2    (2 << MCF51AG_PDB_CTRL2_TRIGSEL_BITNUM)
#define MCF51AG_PDB_CTRL2_TRIGSEL_TRIGGERIN3    (3 << MCF51AG_PDB_CTRL2_TRIGSEL_BITNUM)
#define MCF51AG_PDB_CTRL2_TRIGSEL_TRIGGERIN4    (4 << MCF51AG_PDB_CTRL2_TRIGSEL_BITNUM)
#define MCF51AG_PDB_CTRL2_TRIGSEL_TRIGGERIN5    (5 << MCF51AG_PDB_CTRL2_TRIGSEL_BITNUM)
#define MCF51AG_PDB_CTRL2_TRIGSEL_TRIGGERIN6    (6 << MCF51AG_PDB_CTRL2_TRIGSEL_BITNUM)
#define MCF51AG_PDB_CTRL2_TRIGSEL_SWTRIG        (7 << MCF51AG_PDB_CTRL2_TRIGSEL_BITNUM)
#define MCF51AG_PDB_CTRL2_TRIGSEL(x)            ((x << 0x02) & 0x1C)
#define MCF51AG_PDB_CTRL2_TRIGSEL_MASK          (0x1C)
#define MCF51AG_PDB_CTRL2_CONT                  (0x02)
#define MCF51AG_PDB_CTRL2_SWTRIG                (0x01)


/*------------------------------------------------------------------------*/
/*
** Modulo Timer
*/
#define MCF51XX_TPMxSC_TOIE_MASK                0x40
#define MCF51XX_TPMxSC_TOF_MASK                 0x80
                                                
#define MCF51XX_TPMxSC_CLK_BUSCLK               0x08
#define MCF51XX_TPMxSC_CLK_SYSCLK               0x10

/*------------------------------------------------------------------------*/
/*
/*
** SCGC System Clock Gating Control
*/
#define MCF51XX_SCGC1_SCI1_MASK                 1
#define MCF51XX_SCGC1_SCI2_MASK                 2
#define MCF51XX_SCGC1_IIC_MASK                  4
#define MCF51XX_SCGC1_DMA_MASK                  8
#define MCF51XX_SCGC1_ADC_MASK                  16
#define MCF51XX_SCGC1_FTM1_MASK                 32
#define MCF51XX_SCGC1_FTM2_MASK                 64
#define MCF51XX_SCGC1_TPM3_MASK                 128

#define MCF51XX_SCGC2_SPI1_MASK                 1
#define MCF51XX_SCGC2_SPI2_MASK                 2
#define MCF51XX_SCGC2_RTC_MASK                  4
#define MCF51XX_SCGC2_IEVT_MASK                 8
#define MCF51XX_SCGC2_PDB_MASK                  16
#define MCF51XX_SCGC2_IRQ_MASK                  32
#define MCF51XX_SCGC2_FLS_MASK                  64
#define MCF51XX_SCGC2_CRC_MASK                  128

#define MCF51XX_SCGC3_EWM_MASK                  1
#define MCF51XX_SCGC3_DAC1_MASK                 2
#define MCF51XX_SCGC3_DAC2_MASK                 4
#define MCF51XX_SCGC3_HSCMP1_MASK               8
#define MCF51XX_SCGC3_HSCMP2_MASK               16
/*------------------------------------------------------------------------*/
/*
** mux registers
*/
/* PTXPF registers */
#define MCF51XX_PTXPF_X0_MASK                   0x0003
#define MCF51XX_PTXPF_X1_MASK                   0x000c
#define MCF51XX_PTXPF_X2_MASK                   0x0030
#define MCF51XX_PTXPF_X3_MASK                   0x00c0
#define MCF51XX_PTXPF_X4_MASK                   0x0300
#define MCF51XX_PTXPF_X5_MASK                   0x0c00
#define MCF51XX_PTXPF_X6_MASK                   0x3000
#define MCF51XX_PTXPF_X7_MASK                   0xc000

#define MCF51XX_PTXPF_MASK_ALL                  0xFFFF
                                                
#define MCF51XX_PTDPA_X0_PHYCLK                 0x0001
                                                
#define MCF51XX_PTEPF_X3_MB_CLKOUT              0x0200
#define MCF51XX_PTEPF_X6_MB_FB_D0               0x2000
#define MCF51XX_PTEPF_X7_MB_FB_CS0              0x8000

#define MCF51XX_PTEPF_MB_MUX_SIGNALS            (MCF51XX_PTEPF_X3_MB_CLKOUT | MCF51XX_PTEPF_X7_MB_FB_CS0)   
#define MCF51XX_PTEPF_MB_MUX_MASK               (MCF51XX_PTXPF_X4_MASK | MCF51XX_PTXPF_X7_MASK) 

#define MCF51XX_PTDPF_X0_TXD1                   0x0002
#define MCF51XX_PTDPF_X1_RXD1                   0x0008
#define MCF51XX_PTDPF_X2_TXD2                   0x0020
#define MCF51XX_PTDPF_X3_RXD2                   0x0080

#define MCF51XX_PTEPF_X6_TXD3                   0x3000
#define MCF51XX_PTEPF_X7_RXD3                   0xc000

#define MCF51XX_PTFPF_X0_MB_FB_AD19             0x0002
#define MCF51XX_PTFPF_X1_MB_FB_AD18             0x0008
#define MCF51XX_PTFPF_X2_MB_FB_AD17             0x0020
#define MCF51XX_PTFPF_X3_MB_FB_AD16             0x0080
#define MCF51XX_PTFPF_X6_MB_FB_AD14             0x2000
#define MCF51XX_PTFPF_X0_MB_FB_AD13             0x8000

#define MCF51XX_PTFPF_MB_MUX_SIGNALS            (MCF51XX_PTFPF_X0_MB_FB_AD19 | MCF51XX_PTFPF_X1_MB_FB_AD18 | MCF51XX_PTFPF_X2_MB_FB_AD17 | \
                                                MCF51XX_PTFPF_X3_MB_FB_AD16 | MCF51XX_PTFPF_X6_MB_FB_AD14 | MCF51XX_PTFPF_X0_MB_FB_AD13) 
#define MCF51XX_PTFPF_MB_MUX_MASK               (MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK | MCF51XX_PTXPF_X2_MASK | \
                                                MCF51XX_PTXPF_X3_MASK | MCF51XX_PTXPF_X6_MASK | MCF51XX_PTXPF_X7_MASK )

#define MCF51XX_PTGPF_X0_MB_FB_AD8              0x0002
#define MCF51XX_PTGPF_X1_MB_FB_AD7              0x0008
#define MCF51XX_PTGPF_X2_MB_FB_AD6              0x0020
#define MCF51XX_PTGPF_X3_MB_FB_AD5              0x0080
#define MCF51XX_PTGPF_X4_MB_FB_RW               0x0200

#define MCF51XX_PTGPF_MB_MUX_SIGNALS            (MCF51XX_PTGPF_X0_MB_FB_AD8 | MCF51XX_PTGPF_X1_MB_FB_AD7 | MCF51XX_PTGPF_X2_MB_FB_AD6 | \
                                                MCF51XX_PTGPF_X3_MB_FB_AD5 | MCF51XX_PTGPF_X4_MB_FB_RW )
#define MCF51XX_PTGPF_MB_MUX_MASK               (MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK | MCF51XX_PTXPF_X2_MASK | \
                                                MCF51XX_PTXPF_X3_MASK | MCF51XX_PTXPF_X4_MASK)                                               

#define MCF51XX_PTHPF_X0_MB_FB_AD15             0x0002
#define MCF51XX_PTHPF_X1_MB_FB_OE               0x0008
#define MCF51XX_PTHPF_X4_MB_FB_AD12             0x0200
#define MCF51XX_PTHPF_X5_MB_FB_AD11             0x0800
#define MCF51XX_PTHPF_X6_MB_FB_AD10             0x2000
#define MCF51XX_PTHPF_X7_MB_FB_AD9              0x8000

#define MCF51XX_PTHPF_MB_MUX_SIGNALS           (MCF51XX_PTHPF_X0_MB_FB_AD15 | MCF51XX_PTHPF_X1_MB_FB_OE | MCF51XX_PTHPF_X4_MB_FB_AD12 | \
                                               MCF51XX_PTHPF_X5_MB_FB_AD11 | MCF51XX_PTHPF_X6_MB_FB_AD10 | MCF51XX_PTHPF_X7_MB_FB_AD9 )
                                               
                                               
#define MCF51XX_PTHPF_MB_MUX_MASK              (MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK | MCF51XX_PTXPF_X2_MASK | \
                                               MCF51XX_PTXPF_X3_MASK | MCF51XX_PTXPF_X4_MASK)

#define MCF51XX_PTJPF_X0_MB_ALE                 0x0001
#define MCF51XX_PTJPF_X1_MB_FB_AD4              0x0008
#define MCF51XX_PTJPF_X2_MB_FB_AD3              0x0020
#define MCF51XX_PTJPF_X3_MB_FB_AD2              0x0080
#define MCF51XX_PTJPF_X4_MB_FB_AD1              0x0200
#define MCF51XX_PTJPF_X5_MB_FB_AD0              0x0800

#define MCF51XX_PTJPF_MB_MUX_SIGNALS            (MCF51XX_PTJPF_X0_MB_ALE | MCF51XX_PTJPF_X1_MB_FB_AD4 | MCF51XX_PTJPF_X2_MB_FB_AD3 | \
                                                MCF51XX_PTJPF_X3_MB_FB_AD2 | MCF51XX_PTJPF_X4_MB_FB_AD1 | MCF51XX_PTJPF_X5_MB_FB_AD0 )
#define MCF51XX_PTJPF_MB_MUX_MASK               (MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK | MCF51XX_PTXPF_X2_MASK | \
                                                MCF51XX_PTXPF_X3_MASK | MCF51XX_PTXPF_X4_MASK | MCF51XX_PTXPF_X5_MASK)

#define MCF51XX_PTXPF_X0_BITNUM                 0
#define MCF51XX_PTXPF_X1_BITNUM                 2
#define MCF51XX_PTXPF_X2_BITNUM                 4
#define MCF51XX_PTXPF_X3_BITNUM                 6
#define MCF51XX_PTXPF_X4_BITNUM                 8
#define MCF51XX_PTXPF_X5_BITNUM                 10
#define MCF51XX_PTXPF_X6_BITNUM                 12
#define MCF51XX_PTXPF_X7_BITNUM                 14

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

#define MCF51XX_SOPT2_ADHWTS0_MASK              1
#define MCF51XX_SOPT2_ADHWTS1_MASK              2
#define MCF51XX_SOPT2_ADHWTS_MASK               3
#define MCF51XX_SOPT2_ADHWTS_BITNUM             0
#define MCF51XX_SOPT2_ACIC1_MASK                4
#define MCF51XX_SOPT2_TPMCCFG_MASK              8
#define MCF51XX_SOPT2_ACIC2_MASK                16
#define MCF51XX_SOPT2_FTM1SYNC_MASK             32
#define MCF51XX_SOPT2_FTM2SYNC_MASK             64
#define MCF51XX_SOPT2_CME_MASK                  128
/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/
/* This structure defines (Rapid) General Purpose I/O registers (APPROACH #2) */

typedef struct MCF51AG_gpio_data_struct
{
   uchar  PTxD;      /*** Port Data ***/
   uchar  PTxDD;     /*** Port Data Direction ***/
   uchar  PTxPV;     /*** Port Pin Value Register ***/
   uchar  reserved  ;
} MCF51AG_GPIO_DATA_STRUCT, _PTR_ MCF51AG_GPIO_DATA_STRUCT_PTR;
typedef volatile struct MCF51AG_gpio_data_struct _PTR_ VMCF51AG_GPIO_DATA_STRUCT_PTR;

typedef struct MCF51AG_gpio_struct
{
   uchar  PTxPUE;         /*** Port Pulling Enable Register ***/ 
   uchar  PTxPUS;         /*** PortPullup/Pulldown Select Register ***/
   uchar  PTxDS ;         /*** Port Drive Strength Control Register ***/
   uchar  PTxSRE ;        /*** Port Slew Rate Enable Register ***/
   uchar  PTxPFE ;        /*** Port Passive Filter Enable Register ***/
   uchar  PTxIC  ;        /*** Port Interrupt Control Register ***/
   uchar  PTxIPE ;        /*** Port Interrupt Pin Enable Register ***/
   uchar  PTxIF ;         /*** Port Interrupt Flag Register ***/
   uchar  PTxIES ;        /*** Port Interrupt Edge Select Register ***/
   uchar  PTxDFE ;        /*** Port Digital Filter Enable Register ***/
   uchar  PTxDFC  ;       /*** Port Digital Filter Control Register ***/
   uchar  reserved08[5]  ;

} MCF51AG_GPIO_STRUCT, _PTR_ MCF51AG_GPIO_STRUCT_PTR;
typedef volatile struct MCF51AG_gpio_struct _PTR_ VMCF51AG_GPIO_STRUCT_PTR;

 typedef struct MCF51AG_ics_struct
{  
   uchar ICSC1; 
   uchar ICSC2;
   uchar ICSTRM;
   uchar ICSSC;
} MCF51AG_ICS_STRUCT, _PTR_ MCF51AG_ICS_STRUCT_PTR;
typedef volatile struct MCF51AG_ics_struct _PTR_ VMCF51AG_ICS_STRUCT_PTR;

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

typedef struct MCF51AG_rtc_struct
{
  uchar RTCSC;      /*** RTCSC - RTC Status and Control Register; 0xFFFF8028 ***/
  uchar RTCCNT;     /*** RTCCNT - RTC Counter Register; 0xFFFF8029 ***/
  uchar RTCMOD;     /*** RTCMOD - RTC Modulo Register; 0xFFFF802A ***/
  uchar RTCSC1;     /*** RTCSC1 - RTC DMA Enable Register; 0xFFFF802B ***/
} MCF51AG_RTC_STRUCT, _PTR_ MCF51AG_RTC_STRUCT_PTR;
typedef volatile struct MCF51AG_rtc_struct _PTR_ VMCF51AG_RTC_STRUCT_PTR;
/*
** MCF51AG_dac_struct
** This structure defines digital to analog converter
*/

typedef struct MCF51AG_dac_struct
{
  uchar    DAC1CTRL; 
  uchar    DAC2CTRL;  /* TPMxCyVH and TPMxCyVL registers */
} MCF51AG_DAC_STRUCT, _PTR_ MCF51AG_DAC_STRUCT_PTR;
typedef volatile struct MCF51AG_dac_struct _PTR_ VMCF51AG_DAC_STRUCT_PTR;
/*
** MCF51AG_adc_struct
** This structure defines analog to digital converter
*/
typedef enum {
    ADC_1 = 0,
    ADC_MAX_MODULES
} acd_t;

typedef enum 
{
    ADC_A = 0,
    ADC_B,
    ADC_MAX_HW_CHANNELS
} adc_channel_t;

typedef struct MCF51AG_adc_struct
{
  uchar    ADCSC1A;     /* Status and Control Register */
  uchar  reserved02[1] ;
  uchar    ADCSC2;     /* Status and Control Register 2 */
  uchar  reserved03[9] ;
  uchar    ADCCFG;     /* Data Result High Register */
  uchar  reserved04[7] ;
  uchar    ADCSC1B; 
  uint_16  ADCRA;
  uint_16  ADCRB;
  
} MCF51AG_ADC_STRUCT, _PTR_ MCF51AG_ADC_STRUCT_PTR;
typedef volatile struct MCF51AG_adc_struct _PTR_ VMCF51AG_ADC_STRUCT_PTR;


typedef struct MCF51AG_tpm_channel_struct
{
  uchar    TPMxCySC;
  uint_16  TPMxCyV; /* TPMxCyVH and TPMxCyVL registers */
} MCF51AG_TPM_CHANNEL_STRUCT, _PTR_ MCF51AG_TPM_CHANNEL_STRUCT_PTR;
typedef volatile struct MCF51AG_tpm_channel_struct _PTR_ VMCF51AG_TPM_CHANNEL_STRUCT_PTR;

/*
** MCF51AG_tpm_struct
** This structure defines Timer/Pwm Module registers
*/

typedef struct MCF51AG_tpm3_struct
{
  uchar    TPMxSC; 
  uint_16  TPMxCNT; /*  CNTH and TPMxCNTL registers */
  uint_16  TPMxMOD; /* TPMxMODH and TPMxMODL registers  */
  MCF51AG_TPM_CHANNEL_STRUCT TPMxC[2];
} MCF51AG_TPM3_STRUCT, _PTR_ MCF51AG_TPM3_STRUCT_PTR;
typedef volatile struct MCF51AG_tpm3_struct _PTR_ VMCF51AG_TPM3_STRUCT_PTR;

/*
** MCF51AG_ftm_struct
** This structure defines Flex Timer Module registers
*/

typedef struct MCF51AG_ftm_channel_struct
{
   uchar    FTMyCxSC;
   uint_16  FTMyCxV;
   
} MCF51AG_FTM_CHANNEL_STRUCT, _PTR_ MCF51AG_FTM_CHANNEL_STRUCT_PTR;
typedef volatile struct MCF51AG_ftm_channel_struct _PTR_ VMCF51AG_FTM_CHANNEL_STRUCT_PTR;


typedef struct MCF51AG_ftm_struct
{
   uchar    FTMySC;
   uint_16  FTMyCNT;
   uint_16  FTMyMOD;
   MCF51AG_FTM_CHANNEL_STRUCT FTMyC[6];
   uchar  Reserved[9];
   uint_16  FTMyCNTIN;
   uchar  FTMySTATUS;
   uchar  FTMyMODE;
   uchar  FTMYSYNC;
   uchar  FTMyOUTINIT;
   uchar  FTMyMASK;
   uchar  FTMyCOMBINE0;
   uchar  FTMyCOMBINE1;
   uchar  FTMyCOMBINE2;
   uchar  Reserved07[1];
   uchar  FTMyDEADTIME;
   uchar  FTMyEXTTRIG;
   uchar  FTMyPOL;
   uchar  FTMyFSM;
   uchar  FTMyFILTER0;
   uchar  FTMyFILTER1;
   uchar  FTMyFLTFILTER;
   uchar  FTMyFLTCTRL;
   
} MCF51AG_FTM_STRUCT, _PTR_ MCF51AG_FTM_STRUCT_PTR;
typedef volatile struct MCF51AG_ftm_struct _PTR_ VMCF51AG_FTM_STRUCT_PTR;

/*
** MCF51AG_hsc_struct
** This structure defines System Integration Module registers
*/

typedef struct MCF51AG_hsc_struct
{
   uchar HSCMPCR0;
   uchar HSCMPCR1;
   uchar HSCMPFPR;
   uchar HSCMPSCR;
   uchar HSCMPPCR;
} MCF51AG_HSC_STRUCT, _PTR_ MCF51AG_HSC_STRUCT_PTR;
typedef volatile struct MCF51AG_hsc_struct _PTR_ VMCF51AG_HSC_STRUCT_PTR;

/*
** MCF51AG_sim_struct
** This structure defines System Integration Module registers
*/
typedef struct MCF51AG_sim_struct
{
  uchar SRS;
  uchar SIMC;
  uchar SOPT1;
  uchar SMCLK;
  uchar reserved0B[2];
  uchar SDIDH;
  uchar SDIDL;
} MCF51AG_SIM_STRUCT, _PTR_ MCF51AG_SIM_STRUCT_PTR;
typedef volatile struct MCF51AG_sim_struct _PTR_ VMCF51AG_SIM_STRUCT_PTR;

typedef struct MCF51AG_pmc_struct
{
  uchar  SPMSC1;    /*** SPMSC1 - System Power Management Status and Control Register 1; 0xFFFF8120 ***/
  uchar  SPMSC2;    /*** SPMSC2 - System Power Management Status and Control Register 2; 0xFFFF8121 ***/
} MCF51AG_PMC_STRUCT, _PTR_ MCF51AG_PMC_STRUCT_PTR;
typedef volatile struct MCF51AG_pmc_struct _PTR_ VMCF51AG_PMC_STRUCT_PTR;

 typedef struct MCF51AG_simx_struct
{  
   uchar SOPT2; 
   uchar SCGC1;
   uchar SCGC2;
   uchar SCGC3;
} MCF51AG_SIMX_STRUCT, _PTR_ MCF51AG_SIMX_STRUCT_PTR;
typedef volatile struct MCF51AG_simx_struct _PTR_ VMCF51AG_SIMX_STRUCT_PTR;

typedef struct MCF51AG_simpx_struct
{
   uchar SAPE1;
   uchar SAPE2;
   uchar SAPE3;
   uchar SEIS1;
   uchar SEIS2;
   uchar SPINPS;
   uchar SIMPTA;
   uchar SIMPTB;
   uchar SIMPTC;
   uchar SIMPTD;
   uchar SIMPTE;
   uchar SIMPTF;
   uchar SIMPTG;
   uchar SIMPTH;
   uchar SIMPTJ;
} MCF51AG_SIMPX_STRUCT, _PTR_ MCF51AG_SIMPX_STRUCT_PTR;
typedef volatile struct MCF51AG_simpx_struct _PTR_ VMCF51AG_SIMPX_STRUCT_PTR;

 /*
** MCF51AG_ewm_struct
** This structure defines External WatchDog Monitor register
*/
typedef struct MCF51AG_ewm_struct
{
  uchar  EWMCTRL;
  uchar  EWMSERV;
  uchar  EWMCMPL;
  uchar  EWMCMPH;
} MCF51AG_EWM_STRUCT, _PTR_ MCF51AG_EWM_STRUCT_PTR;
typedef volatile struct MCF51AG_ewm_struct _PTR_ VMCF51AG_EWM_STRUCT_PTR;
/*
** MCF51AG_irq_struct
** This structure defines Interrupt registers
*/
typedef struct MCF51AG_irq_struct
{
  uchar  IRQSC;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
} MCF51AG_IRQ_STRUCT, _PTR_ MCF51AG_IRQ_STRUCT_PTR;
typedef volatile struct MCF51AG_irq_struct _PTR_ VMCF51AG_IRQ_STRUCT_PTR;

/*
** MCF51AG_crc_struct
** This structure defines Cyclic Redundancy Check Registers
*/
typedef struct MCF51AG_crc_struct
{
   uchar CRCH;
   uchar CRCL;
   uchar Transpose;
   uchar reserved11[1];
   uchar CRCL0;
   uchar CRCL1;
   uchar CRCL2;
   uchar CRCL3;
} MCF51AG_CRC_STRUCT, _PTR_ MCF51AG_CRC_STRUCT_PTR;
typedef volatile struct MCF51AG_crc_struct _PTR_ VMCF51AG_CRC_STRUCT_PTR;

/*
** MCF51AG_pdb_struct
** This structure defines System Programmable Delay Block Registers
*/

typedef struct MCF51AG_pdb_struct
{
   uchar    PDBC1;
   uchar    PDBC2;
   uint_16  DEL[ADC_MAX_HW_CHANNELS];
   uint_16  MOD;
   uint_16  CNT;
   uchar    SCR;
} MCF51AG_PDB_STRUCT, _PTR_ MCF51AG_PDB_STRUCT_PTR;
typedef volatile struct MCF51AG_pdb_struct _PTR_ VMCF51AG_PDB_STRUCT_PTR;

/*
** MCF51AG_wdog_struct
** This structure defines Generation WatchDog Timer Registers
*/
typedef struct MCF51AG_wdog_struct
{
   uint_16 WDOG_ST_CTRL_H;
   uint_16 WDOG_ST_CTRL_L;
   uint_16 WDOG_TO_VAL_H;
   uint_16 WDOG_TO_VAL_L;
   uint_16 WDOG_WIN_H;
   uint_16 WDOG_WIN_L;
   uint_16 WDOG_REFRESH;
   uint_16 WDOG_UNLOCK;
   uint_16 WDOG_TIMEOUT_H;
   uint_16 WDOG_TIMEOUT_L;
   uint_16 WDOG_RST_CNT;
} MCF51AG_WDOG_STRUCT, _PTR_ MCF51AG_WDOG_STRUCT_PTR;
typedef volatile struct MCF51AG_wdog_struct _PTR_ VMCF51AG_wdog_STRUCT_PTR;

/*
** MCF51AG_ieventD_struct
** This structure defines Itelligent Event Controller Registers
*/

typedef struct MCF51AG_ieventd_struct
{
   uchar IEVENT_DRx;
} MCF51AG_IEVENTD_STRUCT, _PTR_ MCF51AG_IEVENTD_STRUCT_PTR;
typedef volatile struct MCF51AG_ieventd_struct _PTR_ VMCF51AG_iventd_STRUCT_PTR;
/*
** MCF51AG_ievent_struct
** This structure defines Itelligent Event Controller regiser
*/
typedef struct MCF51AG_ieventc_struct
{
   uchar IEVENT_CRx;
} MCF51AG_IEVENTC_STRUCT, _PTR_ MCF51AG_IEVENTC_STRUCT_PTR;
typedef volatile struct MCF51AG_ieventc_struct _PTR_ VMCF51AG_iventc_STRUCT_PTR;
/*
** MCF51AG_ievent_struct
** This structure defines Itelligent iEvent Boolean function evaluation configution register
*/
typedef struct MCF51AG_ieventx_struct
{
   uint_32 IEVENT_IMXCRx;
   uint_32 IEVENT_BFECRx;
} MCF51AG_IEVENTX_STRUCT, _PTR_ MCF51AG_IEVENTX_STRUCT_PTR;
typedef volatile struct MCF51AG_ieventx_struct _PTR_ VMCF51AG_iventx_STRUCT_PTR;

/*
** Interrupt controller
*/
typedef struct MCF51AG_int_ctrl_struct
{
   uint_8  reserved00[0x08];
   uint_32 IMRH;
   uint_32 IMRL;
   uint_8  FRC;                 /* Force interrupt register */
   uint_8  reserved02[7];         
   uint_8  PL6P7;               /* Level 6, Priority 7 IRQ Register */
   uint_8  PL6P6;               /* Level 6, Priority 5 IRQ Register */
   uint_8  reserved03[1];         
   uint_8  WCR;                 /* Wake-up Control Register */
   uint_8  reserved04[2];         
   uint_8  SFRC;                /* Set Interrupt Force Register */
   uint_8  CFRC;                /* Clear Interrupt Force Register */
   uint_8  SWIACK;              /* Software Interrupt Acknowledge */
   uint_8  reserved05[3];         
   uint_8  LVL1IACK;            /* Level 1 Interrupt Acknowledge */
   uint_8  reserved06[3];         
   uint_8  LVL2IACK;            /* Level 2 Interrupt Acknowledge */
   uint_8  reserved07[3];         
   uint_8  LVL3IACK;            /* Level 3 Interrupt Acknowledge */
   uint_8  reserved08[3];         
   uint_8  LVL4IACK;            /* Level 4 Interrupt Acknowledge */
   uint_8  reserved09[3];         
   uint_8  LVL5IACK;            /* Level 5 Interrupt Acknowledge */
   uint_8  reserved10[3];         
   uint_8  LVL6IACK;            /* Level 6 Interrupt Acknowledge */
   uint_8  reserved11[3];         
   uint_8  LVL7IACK;            /* Level 7 Interrupt Acknowledge */
} MCF51AG_INT_CTRL_STRUCT, _PTR_ MCF51AG_INT_CTRL_STRUCT_PTR;
typedef volatile struct MCF51AG_int_ctrl_struct _PTR_ VMCF51AG_INT_CTRL_STRUCT_PTR;

#define ALIGN_TO(x) (x)
#define USE_REFERENCE(x) -sizeof(x)
#define AT_ADDRESS(x)   -x
typedef struct MCF51AG_struct
{
   MCF51AG_GPIO_DATA_STRUCT GPIO_A_G[GPIO_PORT_G+1];
   MCF51AG_GPIO_DATA_STRUCT GPIO_H_J[GPIO_PORT_MAX-GPIO_PORT_H];
   
   MCF51AG_ICS_STRUCT    ICS;
   MCF51AG_RTC_STRUCT    RTC;
   uchar reserved02[0x802D - 0x8028 - sizeof(MCF51AG_RTC_STRUCT)];
   MCF51AG_DAC_STRUCT    DAC;
   uchar reserved03[0x8031 - 0x802D - sizeof(MCF51AG_DAC_STRUCT)];
   MCF51AG_ADC_STRUCT    ADC; 
   uchar reserved04[0x8050 - 0x8031 - sizeof(MCF51AG_ADC_STRUCT)];
   MCF51XX_SCI_STRUCT    SCI1;
   uchar reserved05[0x8060 - 0x8050 - sizeof(MCF51XX_SCI_STRUCT)];
   MCF51XX_SCI_STRUCT    SCI2;
   uchar reserved06[0x8070 - 0x8060 - sizeof(MCF51XX_SCI_STRUCT)];
   MCF51AG_TPM3_STRUCT   TPM3;
   uchar reserved07[0x8080 - 0x8070 - sizeof(MCF51AG_TPM3_STRUCT)];
   MCF51AG_FTM_STRUCT    FTM1;
   uchar reserved08[0x80C0 - 0x8080 - sizeof(MCF51AG_FTM_STRUCT)];
   MCF51AG_FTM_STRUCT    FTM2;
   uchar reserved09[0x8100 - 0x80C0 - sizeof(MCF51AG_FTM_STRUCT)];
   MCF51AG_GPIO_STRUCT GPIO_P[GPIO_PORT_MAX];     
   MCF51XX_I2C_STRUCT    I2C;
   uchar reserved0B[0x81A0 - 0x8190 - sizeof(MCF51XX_I2C_STRUCT)];
   MCF5XXX_SPI16_NO_FIFO_STRUCT  SPI1;
   MCF5XXX_SPI16_NO_FIFO_STRUCT  SPI2;
   MCF51AG_HSC_STRUCT    HSC1;
   uchar reserved0C[0x81B8 - 0x81B0 - sizeof(MCF51AG_HSC_STRUCT)];
   MCF51AG_HSC_STRUCT    HSC2;
   uchar reserved0D[0x9800 - 0x81B8 - sizeof(MCF51AG_HSC_STRUCT)];
   MCF51AG_SIM_STRUCT SIM;
   uchar reserved0E[0x9809-0x9800 - sizeof(MCF51AG_SIM_STRUCT)];
   MCF51AG_PMC_STRUCT PMC;
   uchar reserved0F[0x980C-0x9809 - sizeof(MCF51AG_PMC_STRUCT)];
   MCF51AG_SIMX_STRUCT SIMX;  
   uchar reserved10[0x9820-0x980C - sizeof(MCF51AG_SIMX_STRUCT)];
   MCF51XX_FTSR_STRUCT  FTSR;
   uchar reserved11[0x9831-0x9820 - sizeof(MCF51XX_FTSR_STRUCT)];
   MCF51AG_SIMPX_STRUCT  SIMPX;  
   MCF51AG_EWM_STRUCT   EWM;
   MCF51AG_IRQ_STRUCT   IRQ;   
   uchar reserved12[0x9850-0x9844 - sizeof(MCF51AG_IRQ_STRUCT)];
   MCF51AG_CRC_STRUCT   CRC;   
   uchar reserved13[0x9860-0x9850 - sizeof(MCF51AG_CRC_STRUCT)];
   MCF51AG_PDB_STRUCT   PDB;   
   uchar reserved14[0x9880-0x9860 - sizeof(MCF51AG_PDB_STRUCT)];
   MCF51AG_WDOG_STRUCT   WDOG;   
   uchar reserved15[0x9A00-0x9880 - sizeof(MCF51AG_WDOG_STRUCT)];
   
   MCF51AG_IEVENTD_STRUCT    IEVENT_DR[6];
   uchar reserved16[0x9A80-0x9A00 - sizeof(MCF51AG_IEVENTD_STRUCT)*6];

   MCF51AG_IEVENTC_STRUCT    IEVENT_CR[6];
   uchar reserved17[0x9B00-0x9A80 - sizeof(MCF51AG_IEVENTC_STRUCT)*6];
   MCF51AG_IEVENTX_STRUCT    IEVENT_yCR[6]; 
   uchar reserved18[0xFFC0-0x9B00 - sizeof(MCF51AG_IEVENTX_STRUCT)*6];
   MCF51AG_INT_CTRL_STRUCT  INTC;
   } MCF51AG_STRUCT, _PTR_ MCF51AG_STRUCT_PTR;
typedef volatile struct MCF51AG_struct _PTR_ VMCF51AG_STRUCT_PTR;

/*
** PSP_SUPPORT_STRUCT
** This structure is used to maintain the PSP support information
*/
typedef struct psp_support_struct
{
   uint_32 ACR_COUNT;   /* How many ACRs set so far*/
   uint_32 Reserved;

} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;

/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_cacr;
extern volatile uint_32 _psp_saved_acr0;
extern volatile uint_32 _psp_saved_acr1;
extern          uchar   __KERNEL_DATA_VERIFY_ENABLE[]; /* CR1327  */

extern pointer _mcf51AG_get_ipsbar(void);
extern void    _mcf51AG_initialize_support(uint_32);

extern void    _mcf51AG_cache_enable(uint_32);
extern void    _mcf51AG_cache_disable(void);
extern void    _mcf51AG_icache_invalidate(void);
extern void    _mcf51AG_dcache_invalidate(void);

extern void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
extern void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

extern void    _mcf51AG_mmu_init(uint_32);
extern uint_32 _mcf51AG_mmu_enable(void);
extern uint_32 _mcf51AG_mmu_disable(void);
extern uint_32 _mcf51AG_mmu_add_region(pointer,uint_32,uint_32);

extern void    __psp_enable_acrs(uint_32_ptr);
extern void    __psp_clear_acrs(void);
extern void    __psp_dcache_flush(uint_32,uint_32,uint_32);

#endif /*__ASM__*/

#ifdef __cplusplus
}
#endif

#endif /* __mcf51AG_h__*/
/* EOF */

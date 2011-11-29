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
* $FileName: mcf51je.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the type definitions for the MCF51JE microcontrollers.
*
*END************************************************************************/

#ifndef __mcf51je_h__
#define __mcf51je_h__

#define __mcf51je_h__version "$Version:3.7.2.0$"
#define __mcf51je_h__date    "$Date:Feb-7-2011$"

#ifndef __ASM__
/* Include registers for modules common to all Coldfire processors */
#include <mcf51xx_ictl.h>  /* CTRL */   
#include <mcf51xx_sci.h>   /* Serial Communication Interface */
#include <mcf51xx_i2c.h>   /* Inter Integrated Circuit */
#include <mcf51xx_tod.h>   /* Time of Day Module */
#include <mcf5xxx_spi16.h> /* Serial Peripheral Interface */
#include <mcf5xxx_spi8.h>  /* Serial Peripheral Interface */
#include <mcf51xx_ftsr.h>  /* Flash Controller */
#include <mcf51xx_pmc.h>   /* Power management Controller */
#include <mcf5xxx_minifb.h>/* Mini Flex Bus */ 
#include <mcf522x_usbotg.h>/* Universal Serial bus - On The Go */ 
#endif /* __ASM__ */

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

/**********************************************************************************
**                    CONSTANT DEFINITIONS
*/

#define PSP_HAS_DSP                         0
#define PSP_HAS_EMAC                        0

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  0
#define PSP_HAS_DATA_CACHE                  0
#define PSP_STOP_ON_IDLE                    0

/*
/** Test for disable cpu wait mode macro.
*/
#if PSP_STOP_ON_IDLE
    #warning "With PSP_STOP_ON_IDLE and no idle_task USB doesn't recover from wait mode"
#endif

#ifndef __ASM__

#define MCF51JE_NUM_ACRS                    (2)

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
#define MCF51JE_NUM_TIMERS                  (2) /* TPM */

#define MCF51XX_SRS_LVD_MASK                2
#define MCF51XX_SRS_LOC_MASK                4
#define MCF51XX_SRS_ILAD_MASK               8
#define MCF51XX_SRS_ILOP_MASK               16
#define MCF51XX_SRS_COP_MASK                32
#define MCF51XX_SRS_PIN_MASK                64
#define MCF51XX_SRS_POR_MASK                128

#define MCF51XX_SOPT1_RSTPE_MASK            1
#define MCF51XX_SOPT1_BKGDPE_MASK           2
#define MCF51XX_SOPT1_MBSL_MASK             4
#define MCF51XX_SOPT1_BLMSS_MASK            8
#define MCF51XX_SOPT1_WAITE_MASK            16
#define MCF51XX_SOPT1_STOPE_MASK            32
#define MCF51XX_SOPT1_COPT_MASK             192
#define MCF51XX_SOPT1_COPT_BITNUM           6

#define MCF51XX_SOPT2_ACIC_MASK             1
#define MCF51XX_SOPT2_CMT_CLK_SEL_MASK      8
#define MCF51XX_SOPT2_CLKOUT_EN_MASK        16
#define MCF51XX_SOPT2_USB_BIGEND_MASK       32
#define MCF51XX_SOPT2_COPW_MASK             64
#define MCF51XX_SOPT2_COPCLKS_MASK          128
#define MCF51XX_SOPT2_BIG_END               0x20


#define MCF51XX_SOPT3_CMT_PAD_MASK          1
#define MCF51XX_SOPT3_SCI1_PAD_MASK         2
#define MCF51XX_SOPT3_ARRAYSEL_MASK         4
#define MCF51XX_SOPT3_MB_DATA_MASK          8
#define MCF51XX_SOPT3_USB_PS_MASK           16
#define MCF51XX_SOPT3_IICPS_MASK            32
#define MCF51XX_SOPT3_SCI1PS_MASK           64
#define MCF51XX_SOPT3_SCI2PS_MASK           128

#define MCF51XX_SOPT4_IRODSE_MASK           1
#define MCF51XX_SOPT4_IROSRE_MASK           2
#define MCF51XX_SOPT4_FBAD12DSE_MASK        4
#define MCF51XX_SOPT4_FBAD12SRE_MASK        8
#define MCF51XX_SOPT4_FBAD12PUE_MASK        16
#define MCF51XX_SOPT4_FBAD12IFE_MASK        32
#define MCF51XX_SOPT4_FBALEEN_MASK          64

#define MCF51XX_SOPT5_PMC_LVD_TRIM_MASK     31
#define MCF51XX_SOPT5_PMC_LVD_TRIM_BITNUM   0

#define MCF51XX_SIMCO_CS_MASK               3
#define MCF51XX_SIMCO_CS_BITNUM             0

/**********************************************************************************
** MCG registers - multi clock generator
*/
#define MCF51XX_CCSCTRL_SEL_MASK                1
#define MCF51XX_CCSCTRL_TEST_MASK               2
#define MCF51XX_CCSCTRL_EN_MASK                 4
#define MCF51XX_CCSCTRL_EREFS1_MASK             8
#define MCF51XX_CCSCTRL_OSCINIT1_MASK          16
#define MCF51XX_CCSCTRL_ERCLKEN1_MASK          32
#define MCF51XX_CCSCTRL_HGO1_MASK              64
#define MCF51XX_CCSCTRL_RANGE1_MASK           128

#define MCF51XX_MCGSC_FTRIM_MASK                1
#define MCF51XX_MCGSC_OSCINIT_MASK              2
#define MCF51XX_MCGSC_CLKST0_MASK               4
#define MCF51XX_MCGSC_CLKST1_MASK               8
#define MCF51XX_MCGSC_IREFST_MASK              16
#define MCF51XX_MCGSC_PLLST_MASK               32
#define MCF51XX_MCGSC_LOCK_MASK                64
#define MCF51XX_MCGSC_LOLS_MASK               128
#define MCF51XX_MCGSC_CLKST_MASK               12
#define MCF51XX_MCGSC_CLKST_BITNUM              2

#define MCF51XX_MCGC1_IREFSTEN_MASK             1
#define MCF51XX_MCGC1_IRCLKEN_MASK              2
#define MCF51XX_MCGC1_IREFS_MASK                4
#define MCF51XX_MCGC1_RDIV0_MASK                8
#define MCF51XX_MCGC1_RDIV1_MASK               16
#define MCF51XX_MCGC1_RDIV2_MASK               32
#define MCF51XX_MCGC1_CLKS0_MASK               64
#define MCF51XX_MCGC1_CLKS1_MASK              128
#define MCF51XX_MCGC1_RDIV_MASK                56
#define MCF51XX_MCGC1_RDIV_BITNUM               3
#define MCF51XX_MCGC1_CLKS_MASK               192
#define MCF51XX_MCGC1_CLKS_BITNUM               6

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

#define MCF51XX_MCGC4_DRST_DRS0_MASK            1
#define MCF51XX_MCGC4_DRST_DRS1_MASK            2
#define MCF51XX_MCGC4_DMX32_MASK                32
#define MCF51XX_MCGC4_DRST_DRS_MASK             3
#define MCF51XX_MCGC4_DRST_DRS_BITNUM           0


/******************************************************************************
** Timer/Pulse Width Modulator
*/

#define MCF51XX_TPMxSC_TOIE_MASK               0x40
#define MCF51XX_TPMxSC_TOF_MASK                0x80

#define MCF51XX_TPMxSC_CLK_BUSCLK              0x08
#define MCF51XX_TPMxSC_CLK_SYSCLK              0x10

/******************************************************************************
** SCGC System Clock Gating Control
*/

#define MCF51XX_SCGC1_SCI1_MASK                 1
#define MCF51XX_SCGC1_SCI2_MASK                 2
#define MCF51XX_SCGC1_IIC1_MASK                 4
#define MCF51XX_SCGC1_DAC_MASK                  8
#define MCF51XX_SCGC1_ADC_MASK                  16
#define MCF51XX_SCGC1_TPM1_MASK                 32
#define MCF51XX_SCGC1_TPM2_MASK                 64
#define MCF51XX_SCGC1_CMT_MASK                  128

#define MCF51XX_SCGC2_SPI1_MASK                 1
#define MCF51XX_SCGC2_SPI2_MASK                 2
#define MCF51XX_SCGC2_MFB_MASK                  4
#define MCF51XX_SCGC2_PRACMP_MASK               8
#define MCF51XX_SCGC2_KBI_MASK                  16
#define MCF51XX_SCGC2_IRQ_MASK                  32
#define MCF51XX_SCGC2_PDB_MASK                  64
#define MCF51XX_SCGC2_USB_MASK                  128

#define MCF51XX_SCGC3_GPOA1_MASK                1
#define MCF51XX_SCGC3_GPOA2_MASK                2
#define MCF51XX_SCGC3_TRIAMP1_MASK              4
#define MCF51XX_SCGC3_TRIAMP2_MASK              8
#define MCF51XX_SCGC3_FLS1_MASK                 16
#define MCF51XX_SCGC3_FLS2_MASK                 32
#define MCF51XX_SCGC3_CRC_MASK                  64
#define MCF51XX_SCGC3_VREF_MASK                 128

#define MCF51XX_SIMIPS_MODTX1_MASK              0x01
#define MCF51XX_SIMIPS_MTBASE1(x)               ((x & 0x3) << 2)
#define MCF51XX_SIMIPS_RX1IN_MASK               0x40
#define MCF51XX_SIMIPS_ADCTRS_MASK              0x80


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

/**********************************************************************************
** ADC registers
*/
#define MCF51JE_ADC_CFG1_ADICLK_MASK           (0x0003)
#define MCF51JE_ADC_CFG1_ADICLK_BUSCLK         (0x0000)
#define MCF51JE_ADC_CFG1_ADICLK_BUSCLK2        (0x0001)
#define MCF51JE_ADC_CFG1_ADICLK_ALTCLK         (0x0002)
#define MCF51JE_ADC_CFG1_ADICLK_ADACK          (0x0003)
#define MCF51JE_ADC_CFG1_MODE_MASK             (0x000C)
#define MCF51JE_ADC_CFG1_MODE_8BIT             (0x0000)
#define MCF51JE_ADC_CFG1_MODE_12BIT            (0x0004)
#define MCF51JE_ADC_CFG1_MODE_10BIT            (0x0008)
#define MCF51JE_ADC_CFG1_MODE_16BIT            (0x000C)
#define MCF51JE_ADC_CFG1_ADLSMP                (0x0010)
#define MCF51JE_ADC_CFG1_ADIV_MASK             (0x0060)
#define MCF51JE_ADC_CFG1_ADIV(x)               ((x) << 5)
#define MCF51JE_ADC_CFG1_ADIV_1                (0x0000)
#define MCF51JE_ADC_CFG1_ADIV_2                (0x0020)
#define MCF51JE_ADC_CFG1_ADIV_4                (0x0040)
#define MCF51JE_ADC_CFG1_ADIV_8                (0x0060)
#define MCF51JE_ADC_CFG1_ADLPC                 (0x0080)

#define MCF51JE_ADC_CFG2_ADLSTS_MASK           (0x0003)
#define MCF51JE_ADC_CFG2_ADLSTS_20             (0x0000)
#define MCF51JE_ADC_CFG2_ADLSTS_12             (0x0001)
#define MCF51JE_ADC_CFG2_ADLSTS_6              (0x0002)
#define MCF51JE_ADC_CFG2_ADLSTS_2              (0x0003)
#define MCF51JE_ADC_CFG2_ADLSTS_DEFAULT        (MCF51JE_ADC_CFG2_ADLSTS_20)
#define MCF51JE_ADC_CFG2_ADHSC                 (0x0004)
#define MCF51JE_ADC_CFG2_ADACKEN               (0x0008)

#define MCF51JE_ADC_SC1_ADCCH_MASK             (0x001F)
#define MCF51JE_ADC_SC1_DIFF                   (0x0020)
#define MCF51JE_ADC_SC1_AIEN                   (0x0040)
#define MCF51JE_ADC_SC1_COCO                   (0x0080)

#define MCF51JE_ADC_SC2_REFSL_MASK             (0x0003)
#define MCF51JE_ADC_SC2_REFSL_VREF             (0x0000)
#define MCF51JE_ADC_SC2_REFSL_VALT             (0x0001)
#define MCF51JE_ADC_SC2_REFSL_VBG              (0x0002)
#define MCF51JE_ADC_SC2_ACREN                  (0x0008)
#define MCF51JE_ADC_SC2_ACFGT                  (0x0010)
#define MCF51JE_ADC_SC2_ACFE                   (0x0020)
#define MCF51JE_ADC_SC2_ADTRG                  (0x0040)
#define MCF51JE_ADC_SC2_ADACT                  (0x0080)

#define MCF51JE_ADC_SC3_AVGS_MASK              (0x0003)
#define MCF51JE_ADC_SC3_AVGS_4                 (0x0000)
#define MCF51JE_ADC_SC3_AVGS_8                 (0x0001)
#define MCF51JE_ADC_SC3_AVGS_16                (0x0002)
#define MCF51JE_ADC_SC3_AVGS_32                (0x0003)
#define MCF51JE_ADC_SC3_AVGE                   (0x0004)
#define MCF51JE_ADC_SC3_ADCO                   (0x0008)
#define MCF51JE_ADC_SC3_CALF                   (0x0040)
#define MCF51JE_ADC_SC3_CAL                    (0x0080)


/******************************************************************************
** PDB registers
*/
#define MCF51JE_PDB_PDBSC_PDBEN                 0x80
#define MCF51JE_PDB_PDBSC_PDBIF                 0x40
#define MCF51JE_PDB_PDBSC_PDBIE                 0x20
#define MCF51JE_PDB_PDBSC_LDMOD                 0x10

#define MCF51JE_PDB_PDBSC_TOS_BITNUM            2
#define MCF51JE_PDB_PDBSC_TOS_BYPASS            (0x00 << MCF51JE_PDB_PDBSC_TOS_BITNUM)
#define MCF51JE_PDB_PDBSC_TOS_NORM              (0x01 << MCF51JE_PDB_PDBSC_TOS_BITNUM)
#define MCF51JE_PDB_PDBSC_TOS_OR                (0x02 << MCF51JE_PDB_PDBSC_TOS_BITNUM)
#define MCF51JE_PDB_PDBSC_TOS(x)                ((x & 0x03) << MCF51JE_PDB_PDBSC_TOS_BITNUM)
#define MCF51JE_PDB_PDBSC_DACTOE                0x02
#define MCF51JE_PDB_PDBSC_LDOK                  0x01
                                              

#define MCF51JE_PDB_PDBC1_MULT                  0x01
#define MCF51JE_PDB_PDBC1_CONT                  0x02
#define MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM        2
#define MCF51JE_PDB_PDBC1_TRIGSEL_TRIGGERIN0    (0 << MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM)
#define MCF51JE_PDB_PDBC1_TRIGSEL_TRIGGERIN1    (1 << MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM)
#define MCF51JE_PDB_PDBC1_TRIGSEL_TRIGGERIN2    (2 << MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM)
#define MCF51JE_PDB_PDBC1_TRIGSEL_TRIGGERIN3    (3 << MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM)
#define MCF51JE_PDB_PDBC1_TRIGSEL_TRIGGERIN4    (4 << MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM)
#define MCF51JE_PDB_PDBC1_TRIGSEL_TRIGGERIN5    (5 << MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM)
#define MCF51JE_PDB_PDBC1_TRIGSEL_TRIGGERIN6    (6 << MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM)
#define MCF51JE_PDB_PDBC1_TRIGSEL_SWTRIG        (7 << MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM)
#define MCF51JE_PDB_PDBC1_TRIGSEL(x)            (( x & 0x07) << MCF51JE_PDB_PDBC1_TRIGSEL_BITNUM)
#define MCF51JE_PDB_PDBC1_PRESCALER_BITNUM      5
#define MCF51JE_PDB_PDBC1_PRESCALER(x)          (( x & 0x07) << MCF51JE_PDB_PDBC1_PRESCALER_BITNUM)

#define MCF51JE_PDB_PDBC2_SWTRIG                0x01
#define MCF51JE_PDB_PDBC2_BB_BITNUM             1
#define MCF51JE_PDB_PDBC1_BB(x)                 (( x & 0x07) << MCF51JE_PDB_PDBC2_BB_BITNUM)



/******************************************************************************
** Interrupt vector table
*/
typedef enum mcf51je_interrupt_table_index {
    MCF51JE_INT_INITSP      =       0,
    MCF51JE_INT_INITPC      =       1,
    MCF51JE_INT_Vaccerr     =       2,
    MCF51JE_INT_Vadderr     =       3,
    MCF51JE_INT_Viinstr     =       4,
    MCF51JE_INT_VReserved5  =       5,
    MCF51JE_INT_VReserved6  =       6,
    MCF51JE_INT_VReserved7  =       7,
    MCF51JE_INT_Vprviol     =       8,
    MCF51JE_INT_Vtrace      =       9,
    MCF51JE_INT_Vunilaop    =       10,
    MCF51JE_INT_Vunilfop    =       11,
    MCF51JE_INT_Vdbgi       =       12,
    MCF51JE_INT_VReserved13 =       13,
    MCF51JE_INT_Vferror     =       14,
    MCF51JE_INT_VReserved15 =       15,
    MCF51JE_INT_VReserved16 =       16,
    MCF51JE_INT_VReserved17 =       17,
    MCF51JE_INT_VReserved18 =       18,
    MCF51JE_INT_VReserved19 =       19,
    MCF51JE_INT_VReserved20 =       20,
    MCF51JE_INT_VReserved21 =       21,
    MCF51JE_INT_VReserved22 =       22,
    MCF51JE_INT_VReserved23 =       23,
    MCF51JE_INT_Vspuri      =       24,
    MCF51JE_INT_VReserved25 =       25,
    MCF51JE_INT_VReserved26 =       26,
    MCF51JE_INT_VReserved27 =       27,
    MCF51JE_INT_VReserved28 =       28,
    MCF51JE_INT_VReserved29 =       29,
    MCF51JE_INT_VReserved30 =       30,
    MCF51JE_INT_VReserved31 =       31,
    MCF51JE_INT_Vtrap0      =       32,
    MCF51JE_INT_Vtrap1      =       33,
    MCF51JE_INT_Vtrap2      =       34,
    MCF51JE_INT_Vtrap3      =       35,
    MCF51JE_INT_Vtrap4      =       36,
    MCF51JE_INT_Vtrap5      =       37,
    MCF51JE_INT_Vtrap6      =       38,
    MCF51JE_INT_Vtrap7      =       39,
    MCF51JE_INT_Vtrap8      =       40,
    MCF51JE_INT_Vtrap9      =       41,
    MCF51JE_INT_Vtrap10     =       42,
    MCF51JE_INT_Vtrap11     =       43,
    MCF51JE_INT_Vtrap12     =       44,
    MCF51JE_INT_Vtrap13     =       45,
    MCF51JE_INT_Vtrap14     =       46,
    MCF51JE_INT_Vtrap15     =       47,
    MCF51JE_INT_VReserved48 =       48,
    MCF51JE_INT_VReserved49 =       49,
    MCF51JE_INT_VReserved50 =       50,
    MCF51JE_INT_VReserved51 =       51,
    MCF51JE_INT_VReserved52 =       52,
    MCF51JE_INT_VReserved53 =       53,
    MCF51JE_INT_VReserved54 =       54,
    MCF51JE_INT_VReserved55 =       55,
    MCF51JE_INT_VReserved56 =       56,
    MCF51JE_INT_VReserved57 =       57,
    MCF51JE_INT_VReserved58 =       58,
    MCF51JE_INT_VReserved59 =       59,
    MCF51JE_INT_VReserved60 =       60,
    MCF51JE_INT_Vunsinstr   =       61,
    MCF51JE_INT_VReserved62 =       62,
    MCF51JE_INT_VReserved63 =       63,
    MCF51JE_INT_Virq        =       64,
    MCF51JE_INT_Vlvd        =       65,
    MCF51JE_INT_Vlol        =       66,

#if MCF51JE_REV2_USB_PATCH
    MCF51JE_INT_Vusb        =       67,
#else
    MCF51JE_INT_VReserved67 =       67,
#endif    
    MCF51JE_INT_Vpdb        =       68,         
    MCF51JE_INT_Vdac        =       69,
    MCF51JE_INT_Vspi1       =       70,
    MCF51JE_INT_Vadc        =       71,

#if MCF51JE_REV2_USB_PATCH
    MCF51JE_INT_VReserved72 =       72,
#else
    MCF51JE_INT_Vusb        =       72,
#endif    
    MCF51JE_INT_Vtpm1ch0    =       73,
    MCF51JE_INT_Vtpm1ch1    =       74,
    MCF51JE_INT_Vtpm1ch2    =       75,
    MCF51JE_INT_Vtpm1ch3    =       76,  
    MCF51JE_INT_Vtpm1ovf    =       77,
    MCF51JE_INT_Vspi2       =       78, 
    MCF51JE_INT_Vcmt        =       79,
    MCF51JE_INT_Vtpm2ch0    =       80,
    MCF51JE_INT_Vtpm2ch1    =       81,
    MCF51JE_INT_Vtpm2ch2    =       82,
    MCF51JE_INT_Vtpm2ch3    =       83,  
    MCF51JE_INT_Vtpm2ovf    =       84,
    MCF51JE_INT_Viic1       =       85,  
    MCF51JE_INT_pracmp      =       86,
    MCF51JE_INT_Vsci1err    =       87,
    MCF51JE_INT_Vsci1rx     =       88,
    MCF51JE_INT_Vsci1tx     =       89,
    MCF51JE_INT_Vsci2err    =       90,
    MCF51JE_INT_Vsci2rx     =       91,
    MCF51JE_INT_Vsci2tx     =       92,
    MCF51JE_INT_expansion1  =       93,
    MCF51JE_INT_expansion2  =       94,  
    MCF51JE_INT_Vkeyboard1  =       95,
    MCF51JE_INT_Vkeyboard2  =       96,
    MCF51JE_INT_tod         =       97,
    MCF51JE_INT_expansion3  =       98,
    MCF51JE_INT_expansion4  =       99,  
    MCF51JE_INT_expansion5  =       100,
    MCF51JE_INT_expansion6  =       101,  
    MCF51JE_INT_expansion7  =       102,
    MCF51JE_INT_VL7swi      =       103,
    MCF51JE_INT_VL6swi      =       104,
    MCF51JE_INT_VL5swi      =       105,
    MCF51JE_INT_VL4swi      =       106,
    MCF51JE_INT_VL3swi      =       107,
    MCF51JE_INT_VL2swi      =       108,
    MCF51JE_INT_VL1swi      =       109,
    MCF51JE_INT_expansion8  =       110,  
    MCF51JE_INT_expansion9  =       111,
    MCF51JE_INT_ftsr1       =       112,
    MCF51JE_INT_ftsr2       =       113,
    MCF51JE_INT_expansion10 =       114
} MCF51JE_INTERRUPT_TABLE_INDEX;

/******************************************************************************
** DAC_MemMap
** This structure defines Digital to Analog Converter registers
*/ 

#define DAC_COUNT               1

typedef struct DAC_MemMap {
    uint_16 DAT[16];
    uint_8 SR;         /* 0x20 */
    uint_8 C0;         /* 0x21 */
    uint_8 C1;         /* 0x22 */
    uint_8 C2;         /* 0x23 */
} DAC_MemMap;
typedef volatile struct DAC_MemMap * DAC_MemMapPtr;

#define DAC_DAT_REG(base,index)  ((base)->DAT[index])
#define DAC_SR_REG(base) ((base)->SR)
#define DAC_C0_REG(base) ((base)->C0)
#define DAC_C1_REG(base) ((base)->C1)
#define DAC_C2_REG(base) ((base)->C2)

/* DATL */
#define DAC_DATL_DATA_MASK      0x00FFu
#define DAC_DATL_DATA_SHIFT     0

/* DATH */
#define DAC_DATH_DATA_MASK      0x0F00u
#define DAC_DATH_DATA_SHIFT     8

/* SR */
#define DAC_SR_DACBFRPBF_MASK   0x1u
#define DAC_SR_DACBFRPBF_SHIFT  0
#define DAC_SR_DACBFRPTF_MASK   0x2u
#define DAC_SR_DACBFRPTF_SHIFT  1
#define DAC_SR_DACBFWMF_MASK    0x4u
#define DAC_SR_DACBFWMF_SHIFT   2

/* C0 */
#define DAC_C0_DACBBIEN_MASK    0x1u
#define DAC_C0_DACBBIEN_SHIFT   0
#define DAC_C0_DACBTIEN_MASK    0x2u
#define DAC_C0_DACBTIEN_SHIFT   1
#define DAC_C0_DACBWIEN_MASK    0x4u
#define DAC_C0_DACBWIEN_SHIFT   2
#define DAC_C0_LPEN_MASK        0x8u
#define DAC_C0_LPEN_SHIFT       3
#define DAC_C0_DACSWTRG_MASK    0x10u
#define DAC_C0_DACSWTRG_SHIFT   4
#define DAC_C0_DACTRGSEL_MASK   0x20u
#define DAC_C0_DACTRGSEL_SHIFT  5
#define DAC_C0_DACRFS_MASK      0x40u
#define DAC_C0_DACRFS_SHIFT     6
#define DAC_C0_DACEN_MASK       0x80u
#define DAC_C0_DACEN_SHIFT      7

/* C1 */
#define DAC_C1_DACBFEN_MASK     0x1u
#define DAC_C1_DACBFEN_SHIFT    0
#define DAC_C1_DACBFMD_MASK     0x6u
#define DAC_C1_DACBFMD_SHIFT    1
#define DAC_C1_DACBFWM_MASK     0x18u
#define DAC_C1_DACBFWM_SHIFT    3
#define DAC_C1_DMAEN_MASK       0x80u
#define DAC_C1_DMAEN_SHIFT      7

/* C2 */
#define DAC_C2_DACBFUP_MASK     0xFu
#define DAC_C2_DACBFUP_SHIFT    0
#define DAC_C2_DACBFRP_MASK     0xF0u
#define DAC_C2_DACBFRP_SHIFT    4

/******************************************************************************
** MCF51JE_pracmp_struct
** This structure defines Programmable Analog Comparator registers
*/ 
typedef struct MCF51JE_pracmp_struct
{
    uchar PRACMPCS;
    uchar PRACMPC0;
    uchar PRACMPC1;
    uchar PRACMPC2;
} MCF51JE_PRACMP_STRUCT, _PTR_ MCF51JE_PRACMP_STRUCT_PTR;
typedef volatile struct MCF51JE_pracmp_struct _PTR_ VMCF51JE_PRACMP_STRUCT_PTR;

/******************************************************************************
** MCF51JE_MCG_STRUCT
** Multi clock generator module
*/
typedef struct MCF51JE_mcg_struct
{
    uchar MCGC1;    /* MCGC1 - MCG Control Register 1;                      */
    uchar MCGC2;    /* MCGC2 - MCG Control Register 2;                      */
    uchar MCGTRM;   /* MCGTRM - MCG Trim Register;                          */
    uchar MCGSC;    /* MCGSC - MCG Status and Control Register;             */
    uchar MCGC3;    /* MCGC3 - MCG Control Register 3;                      */
    uchar MCGC4;    /* MCGC4 - MCG Control Register 4;                      */
    uchar MCGT;     /* MCGC4 - MCG Test Register;                           */
} MCF51JE_MCG_STRUCT, _PTR_ MCF51JE_MCG_STRUCT_PTR;
typedef volatile struct MCF51JE_mcg_struct _PTR_ VMCF51JE_MCG_STRUCT_PTR;

/******************************************************************************
** MCF51JE_adc_struct
** This structure defines first few Analog to Digital Converter registers
*/ 

typedef enum {
    ADC_1 = 0,
    ADC_2,
    ADC_3,
    ADC_4,
    ADC_MAX_MODULES
} adc_t;

typedef enum 
{
    ADC_A = 0,
    ADC_B,
    ADC_C,
    ADC_D,
    ADC_E,
    ADC_F,
    ADC_G,
    ADC_H,
    ADC_MAX_HW_CHANNELS
} adc_channel_t;

typedef struct MCF51JE_adc_struct
{
    uchar   ADCSC1[ADC_H + 1];  /* status and control registers 1           */
    uchar   ADCCFG1;            /* configuration register 1                 */
    uchar   ADCCFG2;            /* configuration register 2                 */
    uint_16 ADCR[ADC_H + 1];    /* both high and low data result registers  */
} MCF51JE_ADC_STRUCT, _PTR_ MCF51JE_ADC_STRUCT_PTR;
typedef volatile struct MCF51JE_adc_struct _PTR_ VMCF51JE_ADC_STRUCT_PTR;


/*
** MCF51JE_adcx_struct
** This structure defines rest of Analog to Digital Converter registers
*/ 
typedef struct MCF51JE_adcx_struct
{
    
    uint_16 ADCCV[2];   /* both high and low compare value registers        */ 
    uchar   ADCSC2;     /* status and control register 2                    */
    uchar   ADCSC3;     /* status and control register 3                    */
    uint_16 ADCOFS;     /* both high and low offset correction register     */
    uint_16 ADCPG;      /* both high and low plus side gain register        */
    uint_16 ADCMG;      /* both high and low minus side gain register       */
    uchar   ADCCLPD;    /* plus side general calibration value register     */
    uchar   ADCCLPS;
    uint_16 ADCCLP4;    /* both high and low regs                           */
    uint_16 ADCCLP3;    /* both high and low regs                           */    
    uchar   ADCCLP2;
    uchar   ADCCLP1;
    uchar   ADCCLP0;
    uchar   ADCTST;     /* ADC TEST register                                */
    uchar   ADCCLMD;    /* minus side general calibration value register    */
    uchar   ADCCLMS;
    uint_16 ADCCLM4;    /* both high and low regs                           */    
    uint_16 ADCCLM3;    /* both high and low regs                           */    
    uchar   ADCCLM2;
    uchar   ADCCLM1;
    uchar   ADCCLM0;
    uchar   APCTL1;     /* Pin Control registers                            */
    uchar   APCTL2;
    uchar   APCTL3;
    uchar   APCTL4; 
} MCF51JE_ADCX_STRUCT, _PTR_ MCF51JE_ADCX_STRUCT_PTR;
typedef volatile struct MCF51JE_adcx_struct _PTR_ VMCF51JE_ADCX_STRUCT_PTR;

/******************************************************************************
** MCF51JE_vrm_struct
** This structure defines Voltage Reference Module registers
*/ 
typedef struct MCF51JE_vrm_struct
{
    uchar   VREFTRM;    /* trim register                                    */
    uchar   VREFSC;     /* status and control register                      */
} MCF51JE_VRM_STRUCT, _PTR_ MCF51JE_VRM_STRUCT_PTR;
typedef volatile struct MCF51JE_vrm_struct _PTR_ VMCF51JE_VRM_STRUCT_PTR;

/******************************************************************************
** MCF51JE_irq_struct
** This structure defines Interrupt registers
*/
typedef struct MCF51JE_irq_struct
{
    uchar  IRQSC;       /* IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 */
} MCF51JE_IRQ_STRUCT, _PTR_ MCF51JE_IRQ_STRUCT_PTR;
typedef volatile struct MCF51JE_irq_struct _PTR_ VMCF51JE_IRQ_STRUCT_PTR;

/******************************************************************************
** MCF51JE_kbi_struct
** This structure defines Interrupt registers
*/
typedef struct MCF51JE_kbi_struct
{
    uchar  KBISC;       /* interrupt status and control register            */
    uchar  KBIPE;       /* interrupt pin select register                    */
    uchar  KBIES;       /* interrupt edge select register                   */
} MCF51JE_KBI_STRUCT, _PTR_ MCF51JE_KBI_STRUCT_PTR;
typedef volatile struct MCF51JE_kbi_struct _PTR_ VMCF51JE_KBI_STRUCT_PTR;

/******************************************************************************
** MCF51JE_sim_struct
** This structure defines first few System Integration Module registers
*/
typedef struct MCF51JE_sim_struct
{
    uchar SRS;              /* System Reset Status Register                 */
    uchar reserved00;
    uchar SOPT1;            /* System Options Register 1                    */
    uchar SOPT2;            /* System Options Register 2                    */
    uchar SIMTCSC;
    uchar SIMCSS;
    uchar SDIDH;            /* System Device Identification Register High   */
    uchar SDIDL;            /* System Device Identification Register Low    */
    uchar SCGC1;            /* System Clock Gating Control 1 Register       */
    uchar SCGC2;            /* System Clock Gating Control 2 Register       */
    uchar SCGC3;            /* System Clock Gating Control 3 Register       */
    uchar SOPT3;            /* SIM Options Register 3                       */
    uchar SOPT4;            /* SIM Options Register 4                       */
    uchar SOPT5;            /* SIM Options Register 5                       */
    uchar SIMIPS;           /* SIM internal peripheral select register      */
    uchar SIGNATURE;                                                        
} MCF51JE_SIM_STRUCT, _PTR_ MCF51JE_SIM_STRUCT_PTR;
typedef volatile struct MCF51JE_sim_struct _PTR_ VMCF51JE_SIM_STRUCT_PTR;

/******************************************************************************
** MCF51JE_mcg_ccs_struct
** This structure defines Multipurpose 
** Clock Generator's Clock Check and Select registers
*/
typedef struct MCF51JE_mcg_ccs_struct
{
    uchar  CCSCTRL;     /* clock check and select control register      */
    uchar  CCSTMR1;     /* CCS XOSC1 Timer register                     */
    uchar  CCSTMR2;     /* CCS XOSC2 Timer register                     */
    uchar  CCSTMRIR;    /* CCS Internal Reference Clock Timer register  */
} MCF51JE_MCG_CCS_STRUCT, _PTR_ MCF51JE_MCG_CCS_STRUCT_PTR;
typedef volatile struct MCF51JE_mcg_ccs_struct _PTR_ VMCF51JE_MCG_CCS_STRUCT_PTR;

/******************************************************************************
** MCF51JE_simx_struct
** This structure defines rest of the System Integration Module registers
*/ 
typedef struct MCF51JE_simx_struct
{
    uchar   FPROTD;     /* Flash Protection Disable Register    */
    uchar   MFBPC1;     /* Mini FlexBus Pin Control 1 Register  */
    uchar   MFBPC2;     /* Mini FlexBus Pin Control 2 Register  */
    uchar   MFBPC3;     /* Mini FlexBus Pin Control 3 Register  */
    uchar   MFBPC4;     /* Mini FlexBus Pin Control 4 Register  */
    uchar   SIMCO;      /* SIM Clock Set and Select Register    */
} MCF51JE_SIMX_STRUCT, _PTR_ MCF51JE_SIMX_STRUCT_PTR;
typedef volatile struct MCF51JE_simx_struct _PTR_ VMCF51JE_SIMX_STRUCT_PTR;

/******************************************************************************
** General Purpose I/O registers
*/

#define MCF51JE_BASE_PTR        ((VMCF51JE_STRUCT_PTR)0xFFFF8000)

#define MCF51XX_PTX0_SHIFT      0
#define MCF51XX_PTX1_SHIFT      1
#define MCF51XX_PTX2_SHIFT      2
#define MCF51XX_PTX3_SHIFT      3
#define MCF51XX_PTX4_SHIFT      4
#define MCF51XX_PTX5_SHIFT      5
#define MCF51XX_PTX6_SHIFT      6
#define MCF51XX_PTX7_SHIFT      7

#define MCF51XX_PTX0_MASK       (1 << MCF51XX_PTX0_SHIFT)
#define MCF51XX_PTX1_MASK       (1 << MCF51XX_PTX1_SHIFT)
#define MCF51XX_PTX2_MASK       (1 << MCF51XX_PTX2_SHIFT)
#define MCF51XX_PTX3_MASK       (1 << MCF51XX_PTX3_SHIFT)
#define MCF51XX_PTX4_MASK       (1 << MCF51XX_PTX4_SHIFT)
#define MCF51XX_PTX5_MASK       (1 << MCF51XX_PTX5_SHIFT)
#define MCF51XX_PTX6_MASK       (1 << MCF51XX_PTX6_SHIFT)
#define MCF51XX_PTX7_MASK       (1 << MCF51XX_PTX7_SHIFT)

#define MCF51XX_KBIX_P0_SHIFT   0
#define MCF51XX_KBIX_P1_SHIFT   1
#define MCF51XX_KBIX_P2_SHIFT   2
#define MCF51XX_KBIX_P3_SHIFT   3
#define MCF51XX_KBIX_P4_SHIFT   4
#define MCF51XX_KBIX_P5_SHIFT   5
#define MCF51XX_KBIX_P6_SHIFT   6
#define MCF51XX_KBIX_P7_SHIFT   7

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

typedef struct MCF51JE_gpio_data_struct
{
    uchar  PTxD;        /* Port Data                            */
    uchar  PTxDD;       /* Port Data Direction                  */
} MCF51JE_GPIO_DATA_STRUCT, _PTR_ MCF51JE_GPIO_DATA_STRUCT_PTR;
typedef volatile struct MCF51JE_gpio_data_struct _PTR_ VMCF51JE_GPIO_DATA_STRUCT_PTR;

typedef struct MCF51JE_gpio_struct
{
    uchar  PTxPE;       /* Port Pull-Up Enable                  */
    uchar  PTxSE;       /* Port Slew Rate Control               */
    uchar  PTxDS;       /* Port Drive Strength Control          */
    uchar  PTxIFE;      /* Port Input Filter Control            */
} MCF51JE_GPIO_STRUCT, _PTR_ MCF51JE_GPIO_STRUCT_PTR;
typedef volatile struct MCF51JE_gpio_struct _PTR_ VMCF51JE_GPIO_STRUCT_PTR;

/******************************************************************************
** MCF51JE_tiamp_struct
** This structure defines Trans-Impedance Amplifier registers
*/
typedef struct MCF51JE_tiamp_struct
{
    uchar  TIAMPC0;     /* TiAMP Control Register 0             */
    uchar  reserved;
} MCF51JE_TIAMP_STRUCT, _PTR_ MCF51JE_TIAMP_STRUCT_PTR;
typedef volatile struct MCF51JE_tiamp_struct _PTR_ VMCF51JE_TIAMP_STRUCT_PTR;

/******************************************************************************
** MCF51JE_cmt_struct
** This structure defines CMT registers
*/ 
typedef struct MCF51JE_cmt_struct
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
} MCF51JE_CMT_STRUCT, _PTR_ MCF51JE_CMT_STRUCT_PTR;
typedef volatile struct MCF51JE_cmt_struct _PTR_ VMCF51JE_CMT_STRUCT_PTR;

/******************************************************************************
** MCF51JE_gpamp_struct
** This structure defines General Purpose Operational Amplifier registers
*/
typedef struct MCF51JE_gpamp_struct
{
    uchar  GPAMPC0;         /* Control Register 0   */
    uchar  GPAMPC1;         /* Control Register 1   */
    uchar  GPAMPC2;         /* Control Register 2   */
    uchar reserved;
} MCF51JE_GPAMP_STRUCT, _PTR_ MCF51JE_GPAMP_STRUCT_PTR;
typedef volatile struct MCF51JE_gpamp_struct _PTR_ VMCF51JE_GPAMP_STRUCT_PTR;

/******************************************************************************
** MCF51JE_crc_struct
** This structure defines Cyclic Redundancy Check registers
*/
typedef struct MCF51JE_crc_struct
{
    uchar  CRCH;            /* CRC High Register    */
    uchar  CRCL;            /* CRC Low Register     */
    uchar  TRANSPOSE;       /* transpose register   */
} MCF51JE_CRC_STRUCT, _PTR_ MCF51JE_CRC_STRUCT_PTR;
typedef volatile struct MCF51JE_crc_struct _PTR_ VMCF51JE_CRC_STRUCT_PTR;

/******************************************************************************
** MCF51JE_tpm_struct
** This structure defines Timer/Pulse Width Modulator registers
*/
typedef struct MCF51JE_tpm_channel_struct
{
    uchar    TPMxCySC; /* TPM Channel n Status and Control Registers          */
    uint_16  TPMxCyV;  /* TPM Channel Value Registers : TPMxCnVH and TPMxCnVL */
} MCF51JE_TPM_CHANNEL_STRUCT, _PTR_ MCF51JE_TPM_CHANNEL_STRUCT_PTR;
typedef volatile struct MCF51JE_tpm_channel_struct _PTR_ VMCF51JE_TPM_CHANNEL_STRUCT_PTR;

typedef struct MCF51JE_tpm_struct
{
    uchar                      TPMxSC;  /* TPM Status and Control Register                      */
    uint_16                    TPMxCNT; /* TPM Counter Registers : TPMxCNTH and TPMxCNTL        */
    uint_16                    TPMxMOD; /* TPM Counter Modulo Registers : TPMxMODH and TPMxMODL */
    MCF51JE_TPM_CHANNEL_STRUCT TPMxC[4];
} MCF51JE_TPM_STRUCT, _PTR_ MCF51JE_TPM_STRUCT_PTR;
typedef volatile struct MCF51JE_tpm_struct _PTR_ VMCF51JE_TPM_STRUCT_PTR;

/******************************************************************************
** MCF51JE_pdb_struct
** This structure defines Programmable Delay Block - Measurement Engine Registers
*/
typedef struct MCF51JE_pdb_struct
{
    uchar   PDBSC;                      /* PDB Status and Control Register  */
    uchar   PDBC1;                      /* PDB Control Register 1           */
    uchar   PDBC2;                      /* PDB Control Register 2           */
    uchar   PDBCHEN;                    /* PDB Channel Enable Register      */
    uint_16 MOD;                        /* PDB Modulus Register             */
    uint_16 COUNT;                      /* PDB Counter Registers            */
    uint_16 IDELAY;                     /* PDB Interrupt Delay Register     */
    uint_16 DACINT;                     /* DAC Interval Registers           */
    uint_16 DEL[ADC_MAX_HW_CHANNELS];   /* Eight PDB Delay Registers        */
} MCF51JE_PDB_STRUCT, _PTR_ MCF51JE_PDB_STRUCT_PTR;
typedef volatile struct MCF51JE_pdb_struct _PTR_ VMCF51JE_PDB_STRUCT_PTR;

/******************************************************************************
** MCF51JE_int_struct
** This structure defines Interrupt Controller
*/
typedef struct MCF51JE_int_struct
{
    uint_8  reserved01[0x10];
    uint_8  INTC_FRC;
    uint_8  reserved02[0x07];
    uint_8  INTC_PL6P7;
    uint_8  INTC_PL6P6;
    uint_8  reserved03[1];
    uint_8  INTC_WCR;
    uint_8  reserved04[2];
    uint_8  INTC_SFRC;
    uint_8  INTC_CFRC;
    uint_8  INTC_SWIACK;
    uint_8  reserved05[3];
    uint_8  INTC_LVL1IACK;
    uint_8  reserved06[3];
    uint_8  INTC_LVL2IACK;
    uint_8  reserved07[3];
    uint_8  INTC_LVL3IACK;
    uint_8  reserved08[3];
    uint_8  INTC_LVL4IACK;
    uint_8  reserved09[3];
    uint_8  INTC_LVL5IACK;
    uint_8  reserved0A[3];
    uint_8  INTC_LVL6IACK;
    uint_8  reserved0B[3];
    uint_8  INTC_LVL7IACK;
} MCF51JE_INT_STRUCT, _PTR_ MCF51JE_INT_STRUCT_PTR;
typedef volatile struct MCF51JE_int_struct _PTR_ VMCF51JE_INT_STRUCT_PTR;

#define ALIGN_TO(x) (x)
#define USE_REFERENCE(x) -sizeof(x)
#define AT_ADDRESS(x)   -x

typedef struct MCF51JE_struct
{    
    MCF51JE_GPIO_DATA_STRUCT  GPIO_DATA_A; 
    MCF51JE_GPIO_DATA_STRUCT  GPIO_DATA_B;
    MCF51JE_GPIO_DATA_STRUCT  GPIO_DATA_C;
    MCF51JE_GPIO_DATA_STRUCT  GPIO_DATA_D;
    uchar                     reserved01[0x8010 - 0x8006 - sizeof(MCF51JE_GPIO_DATA_STRUCT) ]; 
    /* DAC memory map from PE */
    DAC_MemMap                DAC;
    MCF51JE_PRACMP_STRUCT     PRACMP;
    MCF51JE_MCG_STRUCT        MCG;
    uchar                     reserved02[ 0x8040 - 0x8038 - sizeof(MCF51JE_MCG_STRUCT) ];   
    MCF51JE_ADC_STRUCT        ADC; 
    uchar                     reserved03[ 0x805C - 0x8040 - sizeof(MCF51JE_ADC_STRUCT) ];
    MCF51JE_VRM_STRUCT        VRM;
    uchar                     reserved04[ 0x805F - 0x805C - sizeof(MCF51JE_VRM_STRUCT) ];
    MCF51JE_IRQ_STRUCT        IRQ;
    MCF51XX_I2C_STRUCT        I2C1;
    uchar                     reserved05[ 0x806C - 0x8060 - sizeof(MCF51XX_I2C_STRUCT) ];
    MCF51JE_KBI_STRUCT        KBI1;
    uchar                     reserved06[ 0x8070 - 0x806C - sizeof(MCF51JE_KBI_STRUCT) ];
    MCF5XXX_SPI16_STRUCT      SPI1;
    uchar                     reserved07[ 0x807C - 0x8070 - sizeof(MCF5XXX_SPI16_STRUCT) ];
    MCF51JE_KBI_STRUCT        KBI2;
    uchar                     reserved08[ 0x9800 - 0x807C - sizeof(MCF51JE_KBI_STRUCT) ];
    MCF51JE_SIM_STRUCT        SIM;
    MCF51JE_MCG_CCS_STRUCT    MCG_CCS;
    MCF51JE_SIMX_STRUCT       SIMX;  
    uchar                     reserved09[ 0x981C - 0x9814 - sizeof(MCF51JE_SIMX_STRUCT) ];
    MCF51XX_PMC_STRUCT        PMC;
    uchar                     reserved0A[ 0x9830 - 0x981C - sizeof(MCF51XX_PMC_STRUCT) ];
    MCF51JE_GPIO_DATA_STRUCT  GPIO_DATA_E;
    MCF51JE_GPIO_DATA_STRUCT  GPIO_DATA_F;
    /* USBPHY register not mapped */
    uchar                     reserved0B[ 0x9838 - 0x9832 - sizeof(MCF51JE_GPIO_DATA_STRUCT) ];
    MCF51XX_SCI_STRUCT        SCI2;
    MCF5XXX_SPI8_STRUCT       SPI2;
    /* SPIMR */ 
    uchar                     reserved_new_feature_spi[2]; 
    MCF51JE_GPIO_DATA_STRUCT  GPIO_DATA_G;
    uchar                     reserved0C[ 0x9850 - 0x9848 - sizeof(MCF51JE_GPIO_DATA_STRUCT) ];
    MCF51JE_GPIO_STRUCT       GPIO_A_G[GPIO_PORT_G-GPIO_PORT_A+1];
    MCF51JE_TIAMP_STRUCT      TIAMP1;
    MCF51JE_TIAMP_STRUCT      TIAMP2;
    MCF51JE_CMT_STRUCT        CMT;
    uchar                     reserved0E[ 0x987C - 0x9870 - sizeof(MCF51JE_CMT_STRUCT) ];
    MCF51JE_GPAMP_STRUCT      GPAMP1;
    uchar                     reserved0F[ 0x9890 - 0x987C - sizeof(MCF51JE_GPAMP_STRUCT) ];
    MCF51JE_CRC_STRUCT        CRC;
    uchar                     reserved10[ 0x9898 - 0x9890 - sizeof(MCF51JE_CRC_STRUCT) ];
    MCF51JE_GPAMP_STRUCT      GPAMP2;
    MCF51XX_TOD_STRUCT        TOD;
    MCF51JE_TPM_STRUCT        TPM2;
    uchar                     reserved11[ 0x98B8 - 0x98A0 - sizeof(MCF51JE_TPM_STRUCT) ]; 
    MCF51XX_SCI_STRUCT        SCI1;
    MCF51JE_PDB_STRUCT        PDB;
    uchar                     reserved12[ 0x98E0 - 0x98C0 - sizeof(MCF51JE_PDB_STRUCT) ];
    MCF51JE_TPM_STRUCT        TPM1;
    uchar                     reserved13[ 0x98F8 - 0x98E0 - sizeof(MCF51JE_TPM_STRUCT) ];
    MCF51JE_ADCX_STRUCT       ADCX;
    uchar                     reserved14[ 0x9920 - 0x98F8 - sizeof(MCF51JE_ADCX_STRUCT) ];
    MCF51XX_FTSR_STRUCT       FTSR1;
    MCF51XX_FTSR_STRUCT       FTSR2;   

    MCF51JE_GPIO_DATA_STRUCT  GPIO_DATA_H;
    MCF51JE_GPIO_DATA_STRUCT  GPIO_DATA_J;
    uchar                     reserved15[ 0x9948 - 0x9942 - sizeof(MCF51JE_GPIO_DATA_STRUCT) ];
    MCF51JE_GPIO_STRUCT       GPIO_H;
    MCF51JE_GPIO_STRUCT       GPIO_J;
    uchar                     reserved16[ 0x9A00 - 0x994C - sizeof(MCF51JE_GPIO_STRUCT) ];
    USB_MemMap                USBOTG;
    uchar                     reserved17[ 0xE800 - 0x9A00 - sizeof(USB_MemMap) ];
    MCF5XXX_MINIFB_STRUCT     MB;
} MCF51JE_STRUCT, _PTR_ MCF51JE_STRUCT_PTR;
typedef volatile struct MCF51JE_struct _PTR_ VMCF51JE_STRUCT_PTR;

/******************************************************************************
** PSP_SUPPORT_STRUCT
** This structure is used to maintain the PSP support information
*/

typedef struct psp_support_struct
{
   uint_32 ACR_COUNT;   /* How many ACRs set so far */
   uint_32 Reserved;

} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;

/******************************************************************************
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_cacr;
extern          uchar   __KERNEL_DATA_VERIFY_ENABLE[];

#if MCF51JE_REV2_USB_PATCH
    #define USB_STAT          0xFFFF9A90
    #define USB_INT_ENB       0xFFFF9A84
    #define USB_INT_STAT      0xFFFF9A80
    #define INT_SFRC          0xFFFFFFDE
    #define INT_CFRC          0xFFFFFFDF
    #define INT_SFRC_L6       (0x39)
    #define INT_CFRC_L6       (0x39)
    extern volatile boolean   usb_nmi_event;
    extern volatile uint_8    usb_stat_shadow;
    extern volatile uint_8    usb_int_stat_shadow;
    
    extern void USB_NMI_clr_int_stat_shadow(uint_8 bit_num);
    extern void USB_NMI_clr_int_enb(uint_8 bit_num);
    extern void USB_NMI_set_int_enb(uint_8 bit_num);
    extern void USB_NMI_Handler(void);
#endif

extern void    _mcf51JE_initialize_support(uint_32);

#endif /*__ASM__ */

#ifdef __cplusplus
}
#endif


#endif /* __mcf51JE_h__ */
/* EOF */

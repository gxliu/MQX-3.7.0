#ifndef __mpc5125_ccm_h__
#define __mpc5125_ccm_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
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
* $FileName: mpc512x_ccm.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/




#define MPC5125_CCM_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->CCM)


#define CCM_SPMR_SPMF_MASK            0x0F000000
#define CCM_SPMR_SPMF_SHIFT           24
#define CCM_SPMR_CPMF_MASK            0x000F0000
#define CCM_SPMR_CPMF_SHIFT           16

#define CCM_SCCR1_ALL_MASK            0xFFFFFE00
#define CCM_SCCR1_ALL_SHIFT           9
#define CCM_SCCR1_CFG_EN_MASK         0x80000000
#define CCM_SCCR1_CFG_EN_SHIFT        31
#define CCM_SCCR1_LPC_EN_MASK         0x40000000
#define CCM_SCCR1_LPC_EN_SHIFT        30
#define CCM_SCCR1_NFC_EN_MASK         0x20000000
#define CCM_SCCR1_NFC_EN_SHIFT        29
#define CCM_SCCR1_PSC0_EN_MASK        0x08000000
#define CCM_SCCR1_PSC0_EN_SHIFT       27
#define CCM_SCCR1_PSC1_EN_MASK        0x04000000
#define CCM_SCCR1_PSC1_EN_SHIFT       26
#define CCM_SCCR1_PSC2_EN_MASK        0x02000000
#define CCM_SCCR1_PSC2_EN_SHIFT       25
#define CCM_SCCR1_PSC3_EN_MASK        0x01000000
#define CCM_SCCR1_PSC3_EN_SHIFT       24
#define CCM_SCCR1_PSC4_EN_MASK        0x00800000
#define CCM_SCCR1_PSC4_EN_SHIFT       23
#define CCM_SCCR1_PSC5_EN_MASK        0x00400000
#define CCM_SCCR1_PSC5_EN_SHIFT       22
#define CCM_SCCR1_PSC6_EN_MASK        0x00200000
#define CCM_SCCR1_PSC6_EN_SHIFT       21
#define CCM_SCCR1_PSC7_EN_MASK        0x00100000
#define CCM_SCCR1_PSC7_EN_SHIFT       20
#define CCM_SCCR1_PSC8_EN_MASK        0x00080000
#define CCM_SCCR1_PSC8_EN_SHIFT       19
#define CCM_SCCR1_PSC9_EN_MASK        0x00040000
#define CCM_SCCR1_PSC9_EN_SHIFT       18
#define CCM_SCCR1_PSCFIFO_EN_MASK     0x00008000
#define CCM_SCCR1_PSCFIFO_EN_SHIFT    15
#define CCM_SCCR1_FEC1_EN_MASK        0x00002000
#define CCM_SCCR1_FEC1_EN_SHIFT       13
#define CCM_SCCR1_TPR_EN_MASK         0x00001000
#define CCM_SCCR1_TPR_EN_SHIFT        12
#define CCM_SCCR1_DDR_EN_MASK         0x00000400
#define CCM_SCCR1_DDR_EN_SHIFT        10
#define CCM_SCCR1_FEC2_EN_MASK        0x00000200
#define CCM_SCCR1_FEC2_EN_SHIFT       9

#define CCM_SCCR2_ALL_MASK            0xFFFE0000
#define CCM_SCCR2_ALL_SHIFT           17
#define CCM_SCCR2_DIU_EN_MASK         0x80000000
#define CCM_SCCR2_DIU_EN_SHIFT        31
#define CCM_SCCR2_MEM_EN_MASK         0x20000000
#define CCM_SCCR2_MEM_EN_SHIFT        29
#define CCM_SCCR2_USB1_EN_MASK        0x10000000
#define CCM_SCCR2_USB1_EN_SHIFT       28
#define CCM_SCCR2_USB2_EN_MASK        0x08000000
#define CCM_SCCR2_USB2_EN_SHIFT       27
#define CCM_SCCR2_I2C_EN_MASK         0x04000000
#define CCM_SCCR2_I2C_EN_SHIFT        26
#define CCM_SCCR2_AUTO_EN_MASK        0x02000000
#define CCM_SCCR2_AUTO_EN_SHIFT       25
#define CCM_SCCR2_BDLC_EN_MASK        0x02000000
#define CCM_SCCR2_BDLC_EN_SHIFT       25
#define CCM_SCCR2_SDHC1_EN_MASK       0x01000000
#define CCM_SCCR2_SDHC1_EN_SHIFT      24
#define CCM_SCCR2_IIM_EN_MASK         0x00080000
#define CCM_SCCR2_IIM_EN_SHIFT        19
#define CCM_SCCR2_SDHC2_EN_MASK       0x00020000
#define CCM_SCCR2_SDHC2_EN_SHIFT      17

#define CCM_SCFR1_IPS_DIV_MASK        0x03800000
#define CCM_SCFR1_IPS_DIV_SHIFT       23
#define CCM_SCFR1_LPC_DIV_MASK        0x00003800
#define CCM_SCFR1_LPC_DIV_SHIFT       11
#define CCM_SCFR1_DIU_DIV_MASK        0x000000FF
#define CCM_SCFR1_DIU_DIV_SHIFT       0
#define CCM_SCFR1_DIU_RATIO_MASK      0x0000001C
#define CCM_SCFR1_DIU_RATIO_SHIFT     2

#define CCM_SCFR2_SYS_DIV_MASK        0xFC000000
#define CCM_SCFR2_SYS_DIV_SHIFT       26
#define CCM_SCFR2_SDHC2_DIV_MASK      0x0000FF00
#define CCM_SCFR2_SDHC2_DIV_SHIFT     8
#define CCM_SCFR2_SDHC1_DIV_MASK      0x000000FF
#define CCM_SCFR2_SDHC1_DIV_SHIFT     0

#define CCM_SCFR2S_SYS_DIV_MASK       0xFC000000
#define CCM_SCFR2S_SYS_DIV_SHIFT      26

#define CCM_BCR_BCR_MASK              0xFFFFFFFF
#define CCM_BCR_BCR_SHIFT             0

#define CCM_P0CCR_PSC0_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P0CCR_PSC0_MCLK_DIV_SHIFT         17
#define CCM_P0CCR_MCLK_0_EN_MASK              0x00010000
#define CCM_P0CCR_MCLK_0_EN_SHIFT             16
#define CCM_P0CCR_PSC0_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P0CCR_PSC0_MCLK_0_SRC_SHIFT       14
#define CCM_P0CCR_PSC0_MCLK_1_SRC_MASK        0x00000080
#define CCM_P0CCR_PSC0_MCLK_1_SRC_SHIFT       7

#define CCM_P1CCR_PSC1_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P1CCR_PSC1_MCLK_DIV_SHIFT         17
#define CCM_P1CCR_MCLK_1_EN_MASK              0x00010000
#define CCM_P1CCR_MCLK_1_EN_SHIFT             16
#define CCM_P1CCR_PSC1_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P1CCR_PSC1_MCLK_0_SRC_SHIFT       14
#define CCM_P1CCR_PSC1_MCLK_1_SRC_MASK        0x00000080
#define CCM_P1CCR_PSC1_MCLK_1_SRC_SHIFT       7

#define CCM_P2CCR_PSC2_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P2CCR_PSC2_MCLK_DIV_SHIFT         17
#define CCM_P2CCR_MCLK_2_EN_MASK              0x00010000
#define CCM_P2CCR_MCLK_2_EN_SHIFT             16
#define CCM_P2CCR_PSC2_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P2CCR_PSC2_MCLK_0_SRC_SHIFT       14
#define CCM_P2CCR_PSC2_MCLK_1_SRC_MASK        0x00000080
#define CCM_P2CCR_PSC2_MCLK_1_SRC_SHIFT       7

#define CCM_P3CCR_PSC3_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P3CCR_PSC3_MCLK_DIV_SHIFT         17
#define CCM_P3CCR_MCLK_3_EN_MASK              0x00010000
#define CCM_P3CCR_MCLK_3_EN_SHIFT             16
#define CCM_P3CCR_PSC3_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P3CCR_PSC3_MCLK_0_SRC_SHIFT       14
#define CCM_P3CCR_PSC3_MCLK_1_SRC_MASK        0x00000080
#define CCM_P3CCR_PSC3_MCLK_1_SRC_SHIFT       7

#define CCM_P4CCR_PSC4_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P4CCR_PSC4_MCLK_DIV_SHIFT         17
#define CCM_P4CCR_MCLK_4_EN_MASK              0x00010000
#define CCM_P4CCR_MCLK_4_EN_SHIFT             16
#define CCM_P4CCR_PSC4_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P4CCR_PSC4_MCLK_0_SRC_SHIFT       14
#define CCM_P4CCR_PSC4_MCLK_1_SRC_MASK        0x00000080
#define CCM_P4CCR_PSC4_MCLK_1_SRC_SHIFT       7

#define CCM_P5CCR_PSC5_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P5CCR_PSC5_MCLK_DIV_SHIFT         17
#define CCM_P5CCR_MCLK_5_EN_MASK              0x00010000
#define CCM_P5CCR_MCLK_5_EN_SHIFT             16
#define CCM_P5CCR_PSC5_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P5CCR_PSC5_MCLK_0_SRC_SHIFT       14
#define CCM_P5CCR_PSC5_MCLK_1_SRC_MASK        0x00000080
#define CCM_P5CCR_PSC5_MCLK_1_SRC_SHIFT       7

#define CCM_P6CCR_PSC6_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P6CCR_PSC6_MCLK_DIV_SHIFT         17
#define CCM_P6CCR_MCLK_6_EN_MASK              0x00010000
#define CCM_P6CCR_MCLK_6_EN_SHIFT             16
#define CCM_P6CCR_PSC6_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P6CCR_PSC6_MCLK_0_SRC_SHIFT       14
#define CCM_P6CCR_PSC6_MCLK_1_SRC_MASK        0x00000080
#define CCM_P6CCR_PSC6_MCLK_1_SRC_SHIFT       7

#define CCM_P7CCR_PSC7_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P7CCR_PSC7_MCLK_DIV_SHIFT         17
#define CCM_P7CCR_MCLK_7_EN_MASK              0x00010000
#define CCM_P7CCR_MCLK_7_EN_SHIFT             16
#define CCM_P7CCR_PSC7_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P7CCR_PSC7_MCLK_0_SRC_SHIFT       14
#define CCM_P7CCR_PSC7_MCLK_1_SRC_MASK        0x00000080
#define CCM_P7CCR_PSC7_MCLK_1_SRC_SHIFT       7

#define CCM_P8CCR_PSC8_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P8CCR_PSC8_MCLK_DIV_SHIFT         17
#define CCM_P8CCR_MCLK_8_EN_MASK              0x00010000
#define CCM_P8CCR_MCLK_8_EN_SHIFT             16
#define CCM_P8CCR_PSC8_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P8CCR_PSC8_MCLK_0_SRC_SHIFT       14
#define CCM_P8CCR_PSC8_MCLK_1_SRC_MASK        0x00000080
#define CCM_P8CCR_PSC8_MCLK_1_SRC_SHIFT       7

#define CCM_P9CCR_PSC9_MCLK_DIV_MASK          0xFFFE0000
#define CCM_P9CCR_PSC9_MCLK_DIV_SHIFT         17
#define CCM_P9CCR_MCLK_9_EN_MASK              0x00010000
#define CCM_P9CCR_MCLK_9_EN_SHIFT             16
#define CCM_P9CCR_PSC9_MCLK_0_SRC_MASK        0x0000C000
#define CCM_P9CCR_PSC9_MCLK_0_SRC_SHIFT       14
#define CCM_P9CCR_PSC9_MCLK_1_SRC_MASK        0x00000080
#define CCM_P9CCR_PSC9_MCLK_1_SRC_SHIFT       7

#define CCM_DCCR_DLY_NUM_MASK                 0xC0000000
#define CCM_DCCR_DLY_NUM_SHIFT                30
#define CCM_DCCR_CLK_INV_MASK                 0x01000000
#define CCM_DCCR_CLK_INV_SHIFT                24

#define CCM_M1CCR_MSCAN1_CLK_DIV_MASK         0xFFFE0000
#define CCM_M1CCR_MSCAN1_CLK_DIV_SHIFT        17
#define CCM_M1CCR_MSCAN1_EN_MASK              0x00010000
#define CCM_M1CCR_MSCAN1_EN_SHIFT             16
#define CCM_M1CCR_MSCAN1_CLK_SRC_MASK         0x0000C000
#define CCM_M1CCR_MSCAN1_CLK_SRC_SHIFT        14

#define CCM_M2CCR_MSCAN2_CLK_DIV_MASK         0xFFFE0000
#define CCM_M2CCR_MSCAN2_CLK_DIV_SHIFT        17
#define CCM_M2CCR_MSCAN2_EN_MASK              0x00010000
#define CCM_M2CCR_MSCAN2_EN_SHIFT             16
#define CCM_M2CCR_MSCAN2_CLK_SRC_MASK         0x0000C000
#define CCM_M2CCR_MSCAN2_CLK_SRC_SHIFT        14

#define CCM_M3CCR_MSCAN3_CLK_DIV_MASK         0xFFFE0000
#define CCM_M3CCR_MSCAN3_CLK_DIV_SHIFT        17
#define CCM_M3CCR_MSCAN3_EN_MASK              0x00010000
#define CCM_M3CCR_MSCAN3_EN_SHIFT             16
#define CCM_M3CCR_MSCAN3_CLK_SRC_MASK         0x0000C000
#define CCM_M3CCR_MSCAN3_CLK_SRC_SHIFT        14

#define CCM_M4CCR_MSCAN4_CLK_DIV_MASK         0xFFFE0000
#define CCM_M4CCR_MSCAN4_CLK_DIV_SHIFT        17
#define CCM_M4CCR_MSCAN4_EN_MASK              0x00010000
#define CCM_M4CCR_MSCAN4_EN_SHIFT             16
#define CCM_M4CCR_MSCAN4_CLK_SRC_MASK         0x0000C000
#define CCM_M4CCR_MSCAN4_CLK_SRC_SHIFT        14

#define CCM_OUT0CCR_OUT0_DIV_MASK             0xFFFE0000
#define CCM_OUT0CCR_OUT0_DIV_SHIFT            17
#define CCM_OUT0CCR_OUT0_EN_MASK              0x00010000
#define CCM_OUT0CCR_OUT0_EN_SHIFT             16
#define CCM_OUT0CCR_OUT0_CLK_SRC_MASK         0x0000C000
#define CCM_OUT0CCR_OUT0_CLK_SRC_SHIFT        14

#define CCM_OUT1CCR_OUT1_DIV_MASK             0xFFFE0000
#define CCM_OUT1CCR_OUT1_DIV_SHIFT            17
#define CCM_OUT1CCR_OUT1_EN_MASK              0x00010000
#define CCM_OUT1CCR_OUT1_EN_SHIFT             16
#define CCM_OUT1CCR_OUT1_CLK_SRC_MASK         0x0000C000
#define CCM_OUT1CCR_OUT1_CLK_SRC_SHIFT        14

#define CCM_OUT2CCR_OUT2_DIV_MASK             0xFFFE0000
#define CCM_OUT2CCR_OUT2_DIV_SHIFT            17
#define CCM_OUT2CCR_OUT2_EN_MASK              0x00010000
#define CCM_OUT2CCR_OUT2_EN_SHIFT             16
#define CCM_OUT2CCR_OUT2_CLK_SRC_MASK         0x0000C000
#define CCM_OUT2CCR_OUT2_CLK_SRC_SHIFT        14

#define CCM_OUT3CCR_OUT3_DIV_MASK             0xFFFE0000
#define CCM_OUT3CCR_OUT3_DIV_SHIFT            17
#define CCM_OUT3CCR_OUT3_EN_MASK              0x00010000
#define CCM_OUT3CCR_OUT3_EN_SHIFT             16
#define CCM_OUT3CCR_OUT3_CLK_SRC_MASK         0x0000C000
#define CCM_OUT3CCR_OUT3_CLK_SRC_SHIFT        14

#define CCM_SCFR3_NFC_DIV_MASK                0xFFFF0000
#define CCM_SCFR3_NFC_DIV_SHIFT               16
#define CCM_SCFR3_NFC_RATIO_H_MASK            0xFF000000
#define CCM_SCFR3_NFC_RATIO_H_SHIFT           24
#define CCM_SCFR3_NFC_RATIO_L_MASK            0x00FF0000
#define CCM_SCFR3_NFC_RATIO_L_SHIFT           16

#define CCM_SPLL_LOCK_CNT_SYSPLL_LOCK_STATUS_MASK     0x00040000
#define CCM_SPLL_LOCK_CNT_SYSPLL_LOCK_STATUS_SHIFT    18
#define CCM_SPLL_LOCK_CNT_SYSPLL_UNLOCK_MASK          0x00020000
#define CCM_SPLL_LOCK_CNT_SYSPLL_UNLOCK_SHIFT         17
#define CCM_SPLL_LOCK_CNT_SYSPLL_LOCK_MASK            0x00010000
#define CCM_SPLL_LOCK_CNT_SYSPLL_LOCK_SHIFT           16
#define CCM_SPLL_LOCK_CNT_SYSPLL_LOCK_CNT_MASK        0x0000FFFF
#define CCM_SPLL_LOCK_CNT_SYSPLL_LOCK_CNT_SHIFT       0


#define CCM_SCCR1_PSCx_EN_MASK     (0x0ffc0000)
#define CCM_SCCR1_PSC0_BIT_POSITION (27)

#define CCM_SCCR1_CFG_EN   (1<<31)
#define CCM_SCCR1_LPC_EN   (1<<30)
#define CCM_SCCR1_NFC_EN   (1<<29)
#define CCM_SCCR1_PSC0_EN  (1<<27)
#define CCM_SCCR1_PSC1_EN  (1<<26)
#define CCM_SCCR1_PSC2_EN  (1<<25)
#define CCM_SCCR1_PSC3_EN  (1<<24)
#define CCM_SCCR1_PSC4_EN  (1<<23)
#define CCM_SCCR1_PSC5_EN  (1<<22)
#define CCM_SCCR1_PSC6_EN  (1<<21)
#define CCM_SCCR1_PSC7_EN  (1<<20)
#define CCM_SCCR1_PSC8_EN  (1<<19)
#define CCM_SCCR1_PSC9_EN  (1<<18)
#define CCM_SCCR1_FIFOC_EN (1<<15)
#define CCM_SCCR1_FEC1_EN  (1<<13)
#define CCM_SCCR1_DDR_EN   (1<<10)
#define CCM_SCCR1_FEC2_EN  (1<<9)

#define CCM_SCCR2_DIU_EN   (1<<31)
#define CCM_SCCR2_MEM_EN   (1<<29)
#define CCM_SCCR2_USB1_EN  (1<<28)
#define CCM_SCCR2_USB2_EN  (1<<27)
#define CCM_SCCR2_I2C_EN   (1<<26)
#define CCM_SCCR2_AUTO_EN  (1<<25)
#define CCM_SCCR2_SDHC1_EN (1<<24)
#define CCM_SCCR2_IMM_EN   (1<<19)
#define CCM_SCCR2_SDHC2_EN (1<<17)


#define CDM_EXT_48MHZ_EN_USB_EXT        0x02
#define CDM_EXT_48MHZ_EN_PSC6_EXT       0x01
#define CDM_MCLKEN_DIV_PSC_ENABLE       0x8000


#define CCM_MxCCR_MSCANx_CLK_SRC_SYS_CLK     0
#define CCM_MxCCR_MSCANx_CLK_SRC_REF_CLK     1
#define CCM_MxCCR_MSCANx_CLK_SRC_PSC_MCLK_IN 2
#define CCM_MxCCR_MSCANx_CLK_SRC_CAN_CLK_IN  3

// 5.3  Clock Control Module (CCM)
typedef volatile struct mpc5125_ccm_struct {
   vuint_32 SPMR;           // 0x00 System PLL Mode Register (SPMR) R
   vuint_32 SCCR1;          // 0x04 System Clock Control Register 1 (SCCR1) R/W
   vuint_32 SCCR2;          // 0x08 System Clock Control Register 2 (SCCR2) R/W
   vuint_32 SCFR1;          // 0x0C System Clock Frequency Register 1 (SCFR1) R/W
   vuint_32 SCFR2;          // 0x10 System Clock Frequency Register 2 (SCFR2) R/W
   vuint_32 SCFR2S;         // 0x14 System Clock Frequency Shadow Register 2 (SCFR2S) R/W
   vuint_32 BCR;            // 0x18 Bread Crumb Register (BCR) R/W
   vuint_32 P0CCR;          // 0x1C PSC0 Clock Control Register (P0CCR) R/W
   vuint_32 P1CCR;          // 0x20 PSC1 Clock Control Register (P1CCR) R/W
   vuint_32 P2CCR;          // 0x24 PSC2 Clock Control Register (P2CCR) R/W
   vuint_32 P3CCR;          // 0x28 PSC3 Clock Control Register (P3CCR) R/W
   vuint_32 P4CCR;          // 0x2C PSC4 Clock Control Register (P4CCR) R/W
   vuint_32 P5CCR;          // 0x30 PSC5 Clock Control Register (P5CCR) R/W
   vuint_32 P6CCR;          // 0x34 PSC6 Clock Control Register (P6CCR) R/W
   vuint_32 P7CCR;          // 0x38 PSC7 Clock Control Register (P7CCR) R/W
   vuint_32 P8CCR;          // 0x3C PSC8 Clock Control Register (P8CCR) R/W
   vuint_32 P9CCR;          // 0x40 PSC9 Clock Control Register (P9CCR) R/W
   RESERVED_REGISTER(0x44,0x54);
   vuint_32 DCCR;           // 0x54 DIU Clock Config Register (DCCR) R/W
   vuint_32 M1CCR;          // 0x58 MSCAN1 Clock Control Register (M1CCR) R/W
   vuint_32 M2CCR;          // 0x5C MSCAN2 Clock Control Register (M2CCR) R/W
   vuint_32 M3CCR;          // 0x60 MSCAN3 Clock Control Register (M3CCR) R/W
   vuint_32 M4CCR;          // 0x64 MSCAN4 Clock Control Register (M4CCR) R/W
   vuint_32 OUT0CCR;        // 0x68 OUT CLK0 Clock Configure Register (OUT0CCR) R/W
   vuint_32 OUT1CCR;        // 0x6C OUT CLK1 Clock Configure Register (OUT1CCR) R/W
   vuint_32 OUT2CCR;        // 0x70 OUT CLK2 Clock Configure Register (OUT2CCR) R/W
   vuint_32 OUT3CCR;        // 0x74 OUT CLK3 Clock Configure Register (OUT3CCR) R/W
   RESERVED_REGISTER(0x78,0x80);
   vuint_32 SCFR3;          // 0x80 System Clock Frequency Register 3 (SCFR3) R/W
   RESERVED_REGISTER(0x84,0x90);
   vuint_32 SPLL_LOCK_CNT;  // 0x90 System PLL lock counter (SPLL_LOCK_CNT) R
   RESERVED_REGISTER(0x94,0x100);
} MPC5125_CCM_STRUCT, _PTR_ MPC5125_CCM_STRUCT_PTR;

#endif

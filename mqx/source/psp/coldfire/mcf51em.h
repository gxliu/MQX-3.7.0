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
* $FileName: mcf51em.h$
* $Version : 3.6.19.0$
* $Date    : May-18-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf5225x processors.
*
*END************************************************************************/

#ifndef __mcf51em_h__
#define __mcf51em_h__

#define __mcf51em_h__version "$Version:3.6.19.0$"
#define __mcf51em_h__date    "$Date:May-18-2010$"

#ifndef __ASM__
/* Include registers for modules common to all Coldfire processors       */
#include "mcf51xx_sci.h"        /* SCI module                            */
#include "mcf51xx_i2c.h"        /* I2C  module                           */
#include "mcf5xxx_spi8.h"       /* SPI8 module                           */
#include "mcf5xxx_spi16.h"      /* SPI16 module                          */
#include "mcf51xx_ftsr.h"       /* Flash registers                       */
#include "mcf51xx_pmc.h"        /* Power Management Control Module       */
#include "mcf51em_irtc.h"       /* Independent Real Time Counter Module  */
#endif /* __ASM__ */

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* Indicate processor type */
#define PSP_MCF51EM                         1

#define PSP_HAS_DSP                         0
#define PSP_HAS_EMAC                        0
#define PSP_HAS_DUAL_FLASH                  1
#define PSP_HAS_IRTC                        1

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  0
#define PSP_HAS_DATA_CACHE                  0

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


#ifndef __ASM__

#define MCF51EM_NUM_ACRS                        (2)

/* Do you want to verify kernel data can be read and written correctly */
#define PSP_KERNEL_DATA_VERIFY_ENABLE       ((uint_32)__KERNEL_DATA_VERIFY_ENABLE)


/*
** Configuration information
*/
#define MCF51EM_NUM_TIMERS                      (2) /* MTIM */

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

typedef enum mcf51em_interrupt_table_index {
    MCF51EM_INT_INITSP        =       0,
    MCF51EM_INT_INITPC        =       1,
    MCF51EM_INT_Vaccerr       =       2,
    MCF51EM_INT_Vadderr       =       3,
    MCF51EM_INT_Viinstr       =       4,
    MCF51EM_INT_VReserved5    =       5,
    MCF51EM_INT_VReserved6    =       6,
    MCF51EM_INT_VReserved7    =       7,
    MCF51EM_INT_Vprviol       =       8,
    MCF51EM_INT_Vtrace        =       9,
    MCF51EM_INT_Vunilaop      =       10,
    MCF51EM_INT_Vunilfop      =       11,
    MCF51EM_INT_Vdbgi         =       12,
    MCF51EM_INT_VReserved13   =       13,
    MCF51EM_INT_Vferror       =       14,
    MCF51EM_INT_VReserved15   =       15,
    MCF51EM_INT_VReserved16   =       16,
    MCF51EM_INT_VReserved17   =       17,
    MCF51EM_INT_VReserved18   =       18,
    MCF51EM_INT_VReserved19   =       19,
    MCF51EM_INT_VReserved20   =       20,
    MCF51EM_INT_VReserved21   =       21,
    MCF51EM_INT_VReserved22   =       22,
    MCF51EM_INT_VReserved23   =       23,
    MCF51EM_INT_Vspuri        =       24,
    MCF51EM_INT_VReserved25   =       25,
    MCF51EM_INT_VReserved26   =       26,
    MCF51EM_INT_VReserved27   =       27,
    MCF51EM_INT_VReserved28   =       28,
    MCF51EM_INT_VReserved29   =       29,
    MCF51EM_INT_VReserved30   =       30,
    MCF51EM_INT_VReserved31   =       31,
    MCF51EM_INT_Vtrap0        =       32,
    MCF51EM_INT_Vtrap1        =       33,
    MCF51EM_INT_Vtrap2        =       34,
    MCF51EM_INT_Vtrap3        =       35,
    MCF51EM_INT_Vtrap4        =       36,
    MCF51EM_INT_Vtrap5        =       37,
    MCF51EM_INT_Vtrap6        =       38,
    MCF51EM_INT_Vtrap7        =       39,
    MCF51EM_INT_Vtrap8        =       40,
    MCF51EM_INT_Vtrap9        =       41,
    MCF51EM_INT_Vtrap10       =       42,
    MCF51EM_INT_Vtrap11       =       43,
    MCF51EM_INT_Vtrap12       =       44,
    MCF51EM_INT_Vtrap13       =       45,
    MCF51EM_INT_Vtrap14       =       46,
    MCF51EM_INT_Vtrap15       =       47,
    MCF51EM_INT_VReserved48   =       48,
    MCF51EM_INT_VReserved49   =       49,
    MCF51EM_INT_VReserved50   =       50,
    MCF51EM_INT_VReserved51   =       51,
    MCF51EM_INT_VReserved52   =       52,
    MCF51EM_INT_VReserved53   =       53,
    MCF51EM_INT_VReserved54   =       54,
    MCF51EM_INT_VReserved55   =       55,
    MCF51EM_INT_VReserved56   =       56,
    MCF51EM_INT_VReserved57   =       57,
    MCF51EM_INT_VReserved58   =       58,
    MCF51EM_INT_VReserved59   =       59,
    MCF51EM_INT_VReserved60   =       60,
    MCF51EM_INT_Vunsinstr     =       61,
    MCF51EM_INT_VReserved62   =       62,
    MCF51EM_INT_VReserved63   =       63,
    MCF51EM_INT_Virq          =       64,
    MCF51EM_INT_Vlvd          =       65,
    MCF51EM_INT_VReserved66   =       66,
    MCF51EM_INT_Vpdb_err      =       67,
    MCF51EM_INT_Vpdb          =       68,
    MCF51EM_INT_Vtpm1ch0      =       69,
    MCF51EM_INT_Vtpm1ch1      =       70,
    MCF51EM_INT_Vtpm1ovf      =       71,
    MCF51EM_INT_VReserved72   =       72,
    MCF51EM_INT_Vmtim2        =       73,
    MCF51EM_INT_Vmtim3        =       74,
    MCF51EM_INT_Vmtim1        =       75,
    MCF51EM_INT_Vadc4         =       76,
    MCF51EM_INT_Vadc3         =       77,
    MCF51EM_INT_Vadc2         =       78,
    MCF51EM_INT_Vadc1         =       79,
    MCF51EM_INT_Vspi1         =       80,
    MCF51EM_INT_Vspi2         =       81,
    MCF51EM_INT_Vspi3         =       82,
    MCF51EM_INT_Vsci1err      =       83,
    MCF51EM_INT_Vsci1rx       =       84,
    MCF51EM_INT_Vsci1tx       =       85,
    MCF51EM_INT_VReserved86   =       86,
    MCF51EM_INT_Vsci2err      =       87,
    MCF51EM_INT_Vsci2rx       =       88,
    MCF51EM_INT_Vsci2tx       =       89,
    MCF51EM_INT_Vsci3err      =       90,
    MCF51EM_INT_Vsci3rx       =       91,
    MCF51EM_INT_Vsci3tx       =       92,
    MCF51EM_INT_VReserved93   =       93,
    MCF51EM_INT_VReserved94   =       94,
    MCF51EM_INT_Viic          =       95,
    MCF51EM_INT_Vcmp1         =       96,
    MCF51EM_INT_Vcmp2         =       97,
    MCF51EM_INT_VReserved98   =       98,
    MCF51EM_INT_Vkeyboard1    =       99,
    MCF51EM_INT_Vkeyboard2    =       100,
    MCF51EM_INT_VReserved101  =       101,
    MCF51EM_INT_Vrtc          =       102,
    MCF51EM_INT_VL7swi        =       103,
    MCF51EM_INT_VL6swi        =       104,
    MCF51EM_INT_VL5swi        =       105,
    MCF51EM_INT_VL4swi        =       106,
    MCF51EM_INT_VL3swi        =       107,
    MCF51EM_INT_VL2swi        =       108,
    MCF51EM_INT_VL1swi        =       109,
    MCF51EM_INT_Vlcd          =       110,
    MCF51EM_INT_VReserved111  =       111,
    MCF51EM_INT_Vtsr1         =       112,
    MCF51EM_INT_Vtsr2         =       113,
    MCF51EM_INT_VReserved114  =       114
} MCF51EM_INTERRUPT_TABLE_INDEX;


/*------------------------------------------------------------------------*/
/*
** MTIM Modulo Timer (both 8, 16-bit versions)
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
** SCGC System Clock Gating Control registers
*/


/* System Clock Gating Control 1 Register (SCGC1) 0xFFFF8286 */
#define MCF51EM_SCGC1_SCI1_MASK                 1
#define MCF51EM_SCGC1_SCI2_MASK                 2
#define MCF51EM_SCGC1_SCI3_MASK                 4
#define MCF51EM_SCGC1_IIC_MASK                  8
#define MCF51EM_SCGC1_ADC1_MASK                 16
#define MCF51EM_SCGC1_ADC2_MASK                 32
#define MCF51EM_SCGC1_ADC3_MASK                 64
#define MCF51EM_SCGC1_ADC4_MASK                 128

#define MCF51EM_SCGC1_SCI1_BITNUM               0
#define MCF51EM_SCGC1_SCI2_BITNUM               1
#define MCF51EM_SCGC1_SCI3_BITNUM               2
#define MCF51EM_SCGC1_IIC_BITNUM                3
#define MCF51EM_SCGC1_ADC1_BITNUM               4
#define MCF51EM_SCGC1_ADC2_BITNUM               5
#define MCF51EM_SCGC1_ADC3_BITNUM               6
#define MCF51EM_SCGC1_ADC4_BITNUM               7

/* System Clock Gating Control 2 Register (SCGC2) 0xFFFF8287 */
#define MCF51EM_SCGC2_SPI1_MASK                 1
#define MCF51EM_SCGC2_SPI2_MASK                 2
#define MCF51EM_SCGC2_SPI3_MASK                 4
#define MCF51EM_SCGC2_LCD_MASK                  8
#define MCF51EM_SCGC2_IRQ_MASK                  16
#define MCF51EM_SCGC2_VREF_MASK                 32
#define MCF51EM_SCGC2_CMP1_MASK                 64
#define MCF51EM_SCGC2_CMP2_MASK                 128

#define MCF51EM_SCGC2_SPI1_BITNUM               0
#define MCF51EM_SCGC2_SPI2_BITNUM               1
#define MCF51EM_SCGC2_SPI3_BITNUM               2
#define MCF51EM_SCGC2_LCD_BITNUM                3
#define MCF51EM_SCGC2_IRQ_BITNUM                4
#define MCF51EM_SCGC2_VREF_BITNUM               5
#define MCF51EM_SCGC2_CMP1_BITNUM               6
#define MCF51EM_SCGC2_CMP2_BITNUM               7

/* System Clock Gating Control 3 Register (SCGC3) 0xFFFF8288 */
#define MCF51EM_SCGC3_PTA_MASK                  1
#define MCF51EM_SCGC3_PTB_MASK                  2
#define MCF51EM_SCGC3_PTC_MASK                  4
#define MCF51EM_SCGC3_PTD_MASK                  8
#define MCF51EM_SCGC3_PTE_MASK                  16
#define MCF51EM_SCGC3_PTF_MASK                  32
#define MCF51EM_SCGC3_KBI1_MASK                 64
#define MCF51EM_SCGC3_KBI2_MASK                 128

#define MCF51EM_SCGC3_PTA_BITNUM                0
#define MCF51EM_SCGC3_PTB_BITNUM                1  
#define MCF51EM_SCGC3_PTC_BITNUM                2  
#define MCF51EM_SCGC3_PTD_BITNUM                3  
#define MCF51EM_SCGC3_PTE_BITNUM                4  
#define MCF51EM_SCGC3_PTF_BITNUM                5  
#define MCF51EM_SCGC3_KBI1_BITNUM               6  
#define MCF51EM_SCGC3_KBI2_BITNUM               7

/* System Clock Gating Control 4 Register (SCGC4) 0xFFFF8289 */
#define MCF51EM_SCGC4_MTIM1_MASK                1
#define MCF51EM_SCGC4_MTIM2_MASK                2
#define MCF51EM_SCGC4_MTIM3_MASK                4
#define MCF51EM_SCGC4_PDB_MASK                  8
#define MCF51EM_SCGC4_TPM_MASK                  16
#define MCF51EM_SCGC4_CRC_MASK                  32
#define MCF51EM_SCGC4_PM_MASK                   64

#define MCF51EM_SCGC4_MTIM1_BITNUM              0
#define MCF51EM_SCGC4_MTIM2_BITNUM              1
#define MCF51EM_SCGC4_MTIM3_BITNUM              2
#define MCF51EM_SCGC4_PDB_BITNUM                3
#define MCF51EM_SCGC4_TPM_BITNUM                4
#define MCF51EM_SCGC4_CRC_BITNUM                5
#define MCF51EM_SCGC4_PM_BITNUM                 6

/* System Clock Gating Control 5 Register (SCGC5) 0xFFFF828A */
#define MCF51EM_SCGC5_FTSR1_MASK                1
#define MCF51EM_SCGC5_FTSR2_MASK                2

#define MCF51EM_SCGC5_FTSR1_BITNUM              0
#define MCF51EM_SCGC5_FTSR2_BITNUM              1




/*------------------------------------------------------------------------*/
/*
** Mux registers
*/

/* MUX masks and bitnumbers */
#define MCF51XX_MUXPF_X0_BITNUM              0
#define MCF51XX_MUXPF_X1_BITNUM              2
#define MCF51XX_MUXPF_X2_BITNUM              4
#define MCF51XX_MUXPF_X3_BITNUM              6
#define MCF51XX_MUXPF_X4_BITNUM              8
#define MCF51XX_MUXPF_X5_BITNUM              10
#define MCF51XX_MUXPF_X6_BITNUM              12
#define MCF51XX_MUXPF_X7_BITNUM              14

#define MCF51XX_MUXPF_X0_MASK                (0x03 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51XX_MUXPF_X1_MASK                (0x03 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51XX_MUXPF_X2_MASK                (0x03 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51XX_MUXPF_X3_MASK                (0x03 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51XX_MUXPF_X4_MASK                (0x03 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51XX_MUXPF_X5_MASK                (0x03 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51XX_MUXPF_X6_MASK                (0x03 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51XX_MUXPF_X7_MASK                (0x03 << MCF51XX_MUXPF_X7_BITNUM)

#define MCF51XX_MUXPF_MASK_ALL               0xFFFF


/* Port A Pin Function Register (PTAPF)      0xFFFF8200 */

/* Port A7 Pin Mux Controls */
#define MCF51EM_PTAPF_A7_PTA7                (0x00 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTAPF_A7_TPMCLK              (0x01 << MCF51XX_MUXPF_X7_BITNUM) 
#define MCF51EM_PTAPF_A7_CMP1P3              (0x02 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTAPF_A7_AD13                (0x03 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTAPF_A7_MASK                (MCF51XX_MUXPF_X7_MASK)

/* Port A6 Pin Mux Controls */
#define MCF51EM_PTAPF_A6_PTA6                (0x00 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTAPF_A6_TPMCH1              (0x01 << MCF51XX_MUXPF_X6_BITNUM)  
#define MCF51EM_PTAPF_A6_RESERVED            (0x02 << MCF51XX_MUXPF_X6_BITNUM)  
#define MCF51EM_PTAPF_A6_AD12                (0x03 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTAPF_A6_MASK                (MCF51XX_MUXPF_X6_MASK)

/* Port A5 Pin Mux Controls */                                          
#define MCF51EM_PTAPF_A5_PTA5                (0x00 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTAPF_A5_TPMCH0              (0x01 << MCF51XX_MUXPF_X5_BITNUM) 
#define MCF51EM_PTAPF_A5_RESERVED            (0x02 << MCF51XX_MUXPF_X5_BITNUM)  
#define MCF51EM_PTAPF_A5_AD11                (0x03 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTAPF_A5_MASK                (MCF51XX_MUXPF_X5_MASK)

/* Port A4 Pin Mux Controls */
#define MCF51EM_PTAPF_A4_PTA4                (0x00 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTAPF_A4_SSB1                (0x01 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTAPF_A4_RESERVED_1          (0x02 << MCF51XX_MUXPF_X4_BITNUM)  
#define MCF51EM_PTAPF_A4_RESERVED_2          (0x03 << MCF51XX_MUXPF_X4_BITNUM)  
#define MCF51EM_PTAPF_A4_MASK                (MCF51XX_MUXPF_X4_MASK)

/* Port A3 Pin Mux Controls */
#define MCF51EM_PTAPF_A3_PTA3                (0x00 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTAPF_A3_SCLK1               (0x01 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTAPF_A3_RESERVED_1          (0x02 << MCF51XX_MUXPF_X3_BITNUM)  
#define MCF51EM_PTAPF_A3_RESERVED_2          (0x03 << MCF51XX_MUXPF_X3_BITNUM)  
#define MCF51EM_PTAPF_A3_MASK                (MCF51XX_MUXPF_X3_MASK)

/* Port A2 Pin Mux Controls */
#define MCF51EM_PTAPF_A2_PTA2                (0x00 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTAPF_A2_MISO1               (0x01 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTAPF_A2_RESERVED            (0x02 << MCF51XX_MUXPF_X2_BITNUM)  
#define MCF51EM_PTAPF_A2_AD10                (0x03 << MCF51XX_MUXPF_X2_BITNUM)    
#define MCF51EM_PTAPF_A2_MASK                (MCF51XX_MUXPF_X2_MASK)

/* Port A1 Pin Mux Controls */
#define MCF51EM_PTAPF_A1_PTA1                (0x00 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTAPF_A1_MOSI1               (0x01 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTAPF_A1_RESERVED_1          (0x02 << MCF51XX_MUXPF_X1_BITNUM)  
#define MCF51EM_PTAPF_A1_RESERVED_2          (0x03 << MCF51XX_MUXPF_X1_BITNUM)  
#define MCF51EM_PTAPF_A1_MASK                (MCF51XX_MUXPF_X1_MASK)

/* Port A0 Pin Mux Controls */
#define MCF51EM_PTAPF_A0_PTA0                (0x00 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTAPF_A0_IRQ                 (0x01 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTAPF_A0_CLKO                (0x02 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTAPF_A0_RESERVED            (0x03 << MCF51XX_MUXPF_X0_BITNUM)                   
#define MCF51EM_PTAPF_A0_MASK                (MCF51XX_MUXPF_X0_MASK)

#define MCF51EM_PTAPF_MASK_ALL               (MCF51XX_MUXPF_MASK_ALL)


/* Port B Pin Function Register (PTBPF)       0xFFFF8202 */
/* Port B7 Pin Mux Controls */
#define MCF51EM_PTBPF_B7_PTB7                (0x00 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTBPF_B7_KBI1P5              (0x01 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTBPF_B7_TMRCLK2             (0x02 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTBPF_B7_AD15                (0x03 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTBPF_B7_MASK                (MCF51XX_MUXPF_X7_MASK)

/* Port B6 Pin Mux Controls */
#define MCF51EM_PTBPF_B6_PTB6                (0x00 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTBPF_B6_KBI1P4              (0x01 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTBPF_B6_TMRCLK1             (0x02 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTBPF_B6_AD14                (0x03 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTBPF_B6_MASK                (MCF51XX_MUXPF_X6_MASK)

/* Port B5 Pin Mux Controls */
#define MCF51EM_PTBPF_B5_PTB5                (0x00 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTBPF_B5_SDA                 (0x01 << MCF51XX_MUXPF_X5_BITNUM) 
#define MCF51EM_PTBPF_B5_CMP2P4              (0x02 << MCF51XX_MUXPF_X5_BITNUM)  
#define MCF51EM_PTBPF_B5_RESERVED            (0x03 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTBPF_B5_MASK                (MCF51XX_MUXPF_X5_MASK)

/* Port B4 Pin Mux Controls */
#define MCF51EM_PTBPF_B4_PTB4                (0x00 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTBPF_B4_SCL                 (0x01 << MCF51XX_MUXPF_X4_BITNUM)  
#define MCF51EM_PTBPF_B4_CMP2P3              (0x02 << MCF51XX_MUXPF_X4_BITNUM)  
#define MCF51EM_PTBPF_B4_RESERVED            (0x03 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTBPF_B4_MASK                (MCF51XX_MUXPF_X4_MASK)

/* Port B3 Pin Mux Controls */
#define MCF51EM_PTBPF_B3_PTB3                (0x00 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTBPF_B3_KBI1P3              (0x01 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTBPF_B3_CMP2P2              (0x02 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTBPF_B3_TX1                 (0x03 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTBPF_B3_MASK                (MCF51XX_MUXPF_X3_MASK)

/* Port B2 Pin Mux Controls */
#define MCF51EM_PTBPF_B2_PTB2                (0x00 << MCF51XX_MUXPF_X2_BITNUM)                      
#define MCF51EM_PTBPF_B2_KBI1P2              (0x01 << MCF51XX_MUXPF_X2_BITNUM) 
#define MCF51EM_PTBPF_B2_CMP2P1              (0x02 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTBPF_B2_RX1                 (0x03 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTBPF_B2_MASK                (MCF51XX_MUXPF_X2_MASK)

/* Port B1 Pin Mux Controls */
#define MCF51EM_PTBPF_B1_PTB1                (0x00 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTBPF_B1_KBI1P1              (0x01 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTBPF_B1_SSB3                (0x02 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTBPF_B1_TX2                 (0x03 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTBPF_B1_MASK                (MCF51XX_MUXPF_X1_MASK)

/* Port B0 Pin Mux Controls */
#define MCF51EM_PTBPF_B0_PTB0                (0x00 << MCF51XX_MUXPF_X0_BITNUM)                             
#define MCF51EM_PTBPF_B0_KBI1P0              (0x01 << MCF51XX_MUXPF_X0_BITNUM)                           
#define MCF51EM_PTBPF_B0_CMP1P1              (0x02 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTBPF_B0_RX2                 (0x03 << MCF51XX_MUXPF_X0_BITNUM)  
#define MCF51EM_PTBPF_B0_MASK                (MCF51XX_MUXPF_X0_MASK)

#define MCF51EM_PTBPF_MASK_ALL               (MCF51XX_MUXPF_MASK_ALL)

                                                              
/* Port C Pin Function Register  (PTCPF)      0xFFFF8204 */
/* Port C7 Pin Mux Controls */
#define MCF51EM_PTCPF_C7_PTC7                (0x00 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTCPF_C7_LCD4                (0x01 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTCPF_C7_RESERVED_1          (0x02 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTCPF_C7_RESERVED_2          (0x03 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTCPF_C7_MASK                (MCF51XX_MUXPF_X7_MASK)

/* Port C6 Pin Mux Controls */
#define MCF51EM_PTCPF_C6_PTC6                (0x00 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTCPF_C6_LCD3                (0x01 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTCPF_C6_CMP2P5              (0x02 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTCPF_C6_RESERVED            (0x03 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTCPF_C6_MASK                (MCF51XX_MUXPF_X6_MASK)

/* Port C5 Pin Mux Controls */
#define MCF51EM_PTCPF_C5_PTC5                (0x00 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTCPF_C5_LCD2                (0x01 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTCPF_C5_RESERVED            (0x02 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTCPF_C5_CMP1P5              (0x03 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTCPF_C5_MASK                (MCF51XX_MUXPF_X5_MASK)

/* Port C4 Pin Mux Controls */
#define MCF51EM_PTCPF_C4_PTC4                (0x00 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTCPF_C4_LCD1                (0x01 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTCPF_C4_CMP2O               (0x02 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTCPF_C4_RESERVED            (0x03 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTCPF_C4_MASK                (MCF51XX_MUXPF_X4_MASK)

/* Port C3 Pin Mux Controls */
#define MCF51EM_PTCPF_C3_PTC3                (0x00 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTCPF_C3_LCD0                (0x01 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTCPF_C3_CMP1O               (0x02 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTCPF_C3_RESERVED            (0x03 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTCPF_C3_MASK                (MCF51XX_MUXPF_X3_MASK)

/* Port C2 Pin Mux Controls */
#define MCF51EM_PTCPF_C2_BKGD                (0x00 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTCPF_C2_PTC2                (0x01 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTCPF_C2_RESERVED_1          (0x02 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTCPF_C2_RESERVED_2          (0x03 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTCPF_C2_MASK                (MCF51XX_MUXPF_X2_MASK)

/* Port C1 Pin Mux Controls */
#define MCF51EM_PTCPF_C1_PTC1                (0x00 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTCPF_C1_KBI1P7              (0x01 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTCPF_C1_XTAL2               (0x02 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTCPF_C1_TX3                 (0x03 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTCPF_C1_MASK                (MCF51XX_MUXPF_X1_MASK)

/* Port C0 Pin Mux Controls */
#define MCF51EM_PTCPF_C0_PTC0                (0x00 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTCPF_C0_KBI1P6              (0x01 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTCPF_C0_EXTAL2              (0x02 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTCPF_C0_RX3                 (0x03 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTCPF_C0_MASK                (MCF51XX_MUXPF_X0_MASK)

#define MCF51EM_PTCPF_MASK_ALL               (MCF51XX_MUXPF_MASK_ALL)


/* Port D Pin Function Register  (PTDPF)      0xFFFF8206 */
/* Port D7 Pin Mux Controls */
#define MCF51EM_PTDPF_D7_PTD7                (0x00 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTDPF_D7_LCD34               (0x01 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTDPF_D7_KBI2P7              (0x02 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTDPF_D7_RESERVED            (0x03 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTDPF_D7_MASK                (MCF51XX_MUXPF_X7_MASK)

/* Port D6 Pin Mux Controls */
#define MCF51EM_PTDPF_D6_PTD6                (0x00 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTDPF_D6_LCD33               (0x01 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTDPF_D6_KBI2P6              (0x02 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTDPF_D6_CMP2P5              (0x03 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTDPF_D6_MASK                (MCF51XX_MUXPF_X6_MASK)

/* Port D5 Pin Mux Controls */
#define MCF51EM_PTDPF_D5_PTD5                (0x00 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTDPF_D5_LCD32               (0x01 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTDPF_D5_KBI2P5              (0x02 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTDPF_D5_TMRCLK2             (0x03 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTDPF_D5_MASK                (MCF51XX_MUXPF_X5_MASK)

/* Port D4 Pin Mux Controls */
#define MCF51EM_PTDPF_D4_PTD4                (0x00 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTDPF_D4_LCD31               (0x01 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTDPF_D4_KBI2P4              (0x02 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTDPF_D4_TMRCLK1             (0x03 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTDPF_D4_MASK                (MCF51XX_MUXPF_X4_MASK)

/* Port D3 Pin Mux Controls */
#define MCF51EM_PTDPF_D3_PTD3                (0x00 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTDPF_D3_LCD30               (0x01 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTDPF_D3_KBI2P3              (0x02 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTDPF_D3_RESERVED            (0x03 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTDPF_D3_MASK                (MCF51XX_MUXPF_X3_MASK)

/* Port D2 Pin Mux Controls */
#define MCF51EM_PTDPF_D2_PTD2                (0x00 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTDPF_D2_LCD29               (0x01 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTDPF_D2_KBI2P2              (0x02 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTDPF_D2_RESERVED            (0x03 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTDPF_D2_MASK                (MCF51XX_MUXPF_X2_MASK)

/* Port D1 Pin Mux Controls */
#define MCF51EM_PTDPF_D1_PTD1                (0x00 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTDPF_D1_LCD28               (0x01 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTDPF_D1_KBI2P1              (0x02 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTDPF_D1_RESERVED            (0x03 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTDPF_D1_MASK                (MCF51XX_MUXPF_X1_MASK)

/* Port D0 Pin Mux Controls */
#define MCF51EM_PTDPF_D0_PTD0                (0x00 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTDPF_D0_LCD27               (0x01 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTDPF_D0_KBI2P0              (0x02 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTDPF_D0_RESERVED            (0x03 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTDPF_D0_MASK                (MCF51XX_MUXPF_X0_MASK)

#define MCF51EM_PTDPF_MASK_ALL               (MCF51XX_MUXPF_MASK_ALL)


/* Port E Pin Function Register  (PTEPF)      0xFFFF8208 */
/* Port E7 Pin Mux Controls */
#define MCF51EM_PTEPF_E7_PTE7                (0x00 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTEPF_E7_LCD5                (0x01 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTEPF_E7_RESERVED_1          (0x02 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTEPF_E7_RESERVED_2          (0x03 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTEPF_E7_MASK                (MCF51XX_MUXPF_X7_MASK)

/* Port E6 Pin Mux Controls */
#define MCF51EM_PTEPF_E6_PTE6                (0x00 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTEPF_E6_SSB3                (0x01 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTEPF_E6_SSB3_1              (0x01 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTEPF_E6_SSB3_2              (0x02 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTEPF_E6_TX2                 (0x03 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_PTEPF_E6_MASK                (MCF51XX_MUXPF_X6_MASK)

/* Port E5 Pin Mux Controls */
#define MCF51EM_PTEPF_E5_PTE5                (0x00 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTEPF_E5_SCLK3               (0x01 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTEPF_E5_SCLK3_1             (0x01 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTEPF_E5_SCLK3_2             (0x02 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTEPF_E5_RESERVED            (0x03 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_PTEPF_E5_MASK                (MCF51XX_MUXPF_X5_MASK)          

/* Port E4 Pin Mux Controls */
#define MCF51EM_PTEPF_E4_PTE4                (0x00 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTEPF_E4_MISO3               (0x01 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTEPF_E4_MOSI3               (0x02 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTEPF_E4_RESERVED            (0x03 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTEPF_E4_MASK                (MCF51XX_MUXPF_X4_MASK)          

/* Port E3 Pin Mux Controls */
#define MCF51EM_PTEPF_E3_PTE3                (0x00 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTEPF_E3_MOSI3               (0x01 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTEPF_E3_MISO3               (0x02 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTEPF_E3_RESERVED            (0x03 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTEPF_E3_MASK                (MCF51XX_MUXPF_X3_MASK)          

/* Port E2 Pin Mux Controls */
#define MCF51EM_PTEPF_E2_PTE2                (0x00 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTEPF_E2_RESERVED_1          (0x01 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTEPF_E2_CMP1P2              (0x02 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTEPF_E2_RESERVED_2          (0x03 << MCF51XX_MUXPF_X2_BITNUM)
#define MCF51EM_PTEPF_E2_MASK                (MCF51XX_MUXPF_X2_MASK)

/* Port E1 Pin Mux Controls */
#define MCF51EM_PTEPF_E1_PTE1                (0x00 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTEPF_E1_RESERVED            (0x01 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTEPF_E1_CMP1P4              (0x02 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTEPF_E1_AD9                 (0x03 << MCF51XX_MUXPF_X1_BITNUM)
#define MCF51EM_PTEPF_E1_MASK                (MCF51XX_MUXPF_X1_MASK)

/* Port E0 Pin Mux Controls */
#define MCF51EM_PTEPF_E0_PTE0                (0x00 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTEPF_E0_RESERVED            (0x01 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTEPF_E0_CMP1O               (0x02 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTEPF_E0_AD8                 (0x03 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTEPF_E0_MASK                (MCF51XX_MUXPF_X0_MASK)

#define MCF51EM_PTEPF_MASK_ALL               (MCF51XX_MUXPF_MASK_ALL)


/* Port F Pin Function Register  (PTFPF)      0xFFFF820A */
/* Port F7 Pin Mux Controls */
#define MCF51EM_PTFPF_F7_PTF7                (0x00 << MCF51XX_MUXPF_X7_BITNUM) 
#define MCF51EM_PTFPF_F7_LCD43               (0x01 << MCF51XX_MUXPF_X7_BITNUM)  
#define MCF51EM_PTFPF_F7_RESERVED            (0x02 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTFPF_F7_AD19                (0x03 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_PTFPF_F7_MASK                (MCF51XX_MUXPF_X7_MASK)

/* Port F6 Pin Mux Controls */
#define MCF51EM_PTFPF_F6_PTF6                (0x00 << MCF51XX_MUXPF_X6_BITNUM) 
#define MCF51EM_PTFPF_F6_LCD42               (0x01 << MCF51XX_MUXPF_X6_BITNUM)  
#define MCF51EM_PTFPF_F6_RESERVED            (0x02 << MCF51XX_MUXPF_X6_BITNUM) 
#define MCF51EM_PTFPF_F6_AD18                (0x03 << MCF51XX_MUXPF_X6_BITNUM) 
#define MCF51EM_PTFPF_F6_MASK                (MCF51XX_MUXPF_X6_MASK)

/* Port F5 Pin Mux Controls */                                          
#define MCF51EM_PTFPF_F5_PTF5                (0x00 << MCF51XX_MUXPF_X5_BITNUM) 
#define MCF51EM_PTFPF_F5_LCD41               (0x01 << MCF51XX_MUXPF_X5_BITNUM)  
#define MCF51EM_PTFPF_F5_RESERVED            (0x02 << MCF51XX_MUXPF_X5_BITNUM) 
#define MCF51EM_PTFPF_F5_AD17                (0x03 << MCF51XX_MUXPF_X5_BITNUM) 
#define MCF51EM_PTFPF_F5_MASK                (MCF51XX_MUXPF_X5_MASK)
  
/* Port F4 Pin Mux Controls */
#define MCF51EM_PTFPF_F4_PTF4                (0x00 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_PTFPF_F4_RESERVED            (0x01 << MCF51XX_MUXPF_X4_BITNUM)     
#define MCF51EM_PTFPF_F4_LCD40               (0x02 << MCF51XX_MUXPF_X4_BITNUM)  
#define MCF51EM_PTFPF_F4_AD16                (0x03 << MCF51XX_MUXPF_X4_BITNUM) 
#define MCF51EM_PTFPF_F4_MASK                (MCF51XX_MUXPF_X4_MASK) 

/* Port F3 Pin Mux Controls */
#define MCF51EM_PTFPF_F3_PTF3                (0x00 << MCF51XX_MUXPF_X3_BITNUM) 
#define MCF51EM_PTFPF_F3_LCD39               (0x01 << MCF51XX_MUXPF_X3_BITNUM)
#define MCF51EM_PTFPF_F3_RESERVED            (0x02 << MCF51XX_MUXPF_X3_BITNUM)                      
#define MCF51EM_PTFPF_F3_TX3                 (0x03 << MCF51XX_MUXPF_X3_BITNUM) 
#define MCF51EM_PTFPF_F3_MASK                (MCF51XX_MUXPF_X3_MASK)  
                                         
/* Port F2 Pin Mux Controls */
#define MCF51EM_PTFPF_F2_PTF2                (0x00 << MCF51XX_MUXPF_X2_BITNUM) 
#define MCF51EM_PTFPF_F2_LCD38               (0x01 << MCF51XX_MUXPF_X2_BITNUM) 
#define MCF51EM_PTFPF_F2_RESERVED            (0x02 << MCF51XX_MUXPF_X2_BITNUM)                      
#define MCF51EM_PTFPF_F2_RX3                 (0x03 << MCF51XX_MUXPF_X2_BITNUM) 
#define MCF51EM_PTFPF_F2_MASK                (MCF51XX_MUXPF_X2_MASK)  
                 
/* Port F1 Pin Mux Controls */
#define MCF51EM_PTFPF_F1_PTF1                (0x00 << MCF51XX_MUXPF_X1_BITNUM) 
#define MCF51EM_PTFPF_F1_LCD37               (0x01 << MCF51XX_MUXPF_X1_BITNUM) 
#define MCF51EM_PTFPF_F1_RESERVED            (0x02 << MCF51XX_MUXPF_X1_BITNUM)                      
#define MCF51EM_PTFPF_F1_EXTRIG              (0x03 << MCF51XX_MUXPF_X1_BITNUM) 
#define MCF51EM_PTFPF_F1_MASK                (MCF51XX_MUXPF_X1_MASK)  

/* Port F0 Pin Mux Controls */
#define MCF51EM_PTFPF_F0_PTF0                (0x00 << MCF51XX_MUXPF_X0_BITNUM) 
#define MCF51EM_PTFPF_F0_LCD36               (0x01 << MCF51XX_MUXPF_X0_BITNUM) 
#define MCF51EM_PTFPF_F0_RESERVED_1          (0x02 << MCF51XX_MUXPF_X0_BITNUM)
#define MCF51EM_PTFPF_F0_RESERVED_2          (0x03 << MCF51XX_MUXPF_X0_BITNUM) 
#define MCF51EM_PTFPF_F0_MASK                (MCF51XX_MUXPF_X0_MASK)

#define MCF51EM_PTFPF_MASK_ALL               (MCF51XX_MUXPF_MASK_ALL)


/* LCD Pin Function Register (LCDPF)          0xFFFF820C */
/* LCD9 Mux Control */                        
#define MCF51EM_LCDPF_LCD9_LCD9              (0x00 << MCF51XX_MUXPF_X7_BITNUM)   
#define MCF51EM_LCDPF_LCD9_SSB2              (0x01 << MCF51XX_MUXPF_X7_BITNUM) 
#define MCF51EM_LCDPF_LCD9_RESERVED_1        (0x02 << MCF51XX_MUXPF_X7_BITNUM) 
#define MCF51EM_LCDPF_LCD9_RESERVED_2        (0x03 << MCF51XX_MUXPF_X7_BITNUM)
#define MCF51EM_LCDPF_LCD9_MASK              (MCF51XX_MUXPF_X7_MASK)

/* LCD8 Mux Control */
#define MCF51EM_LCDPF_LCD8_LCD8              (0x00 << MCF51XX_MUXPF_X6_BITNUM) 
#define MCF51EM_LCDPF_LCD8_SCLK2             (0x01 << MCF51XX_MUXPF_X6_BITNUM) 
#define MCF51EM_LCDPF_LCD8_RESERVED_1        (0x02 << MCF51XX_MUXPF_X6_BITNUM) 
#define MCF51EM_LCDPF_LCD8_RESERVED_2        (0x03 << MCF51XX_MUXPF_X6_BITNUM)
#define MCF51EM_LCDPF_LCD8_MASK              (MCF51XX_MUXPF_X6_MASK)

/* LCD7 Mux Control */                                                  
#define MCF51EM_LCDPF_LCD7_LCD7              (0x00 << MCF51XX_MUXPF_X5_BITNUM) 
#define MCF51EM_LCDPF_LCD7_MISO2             (0x01 << MCF51XX_MUXPF_X5_BITNUM) 
#define MCF51EM_LCDPF_LCD7_RESERVED_1        (0x02 << MCF51XX_MUXPF_X5_BITNUM) 
#define MCF51EM_LCDPF_LCD7_RESERVED_2        (0x03 << MCF51XX_MUXPF_X5_BITNUM)
#define MCF51EM_LCDPF_LCD7_MASK              (MCF51XX_MUXPF_X5_MASK)

/* LCD6 Mux Control */
#define MCF51EM_LCDPF_LCD6_LCD6              (0x00 << MCF51XX_MUXPF_X4_BITNUM) 
#define MCF51EM_LCDPF_LCD6_MOSI2             (0x01 << MCF51XX_MUXPF_X4_BITNUM) 
#define MCF51EM_LCDPF_LCD6_RESERVED_1        (0x02 << MCF51XX_MUXPF_X4_BITNUM) 
#define MCF51EM_LCDPF_LCD6_RESERVED_2        (0x03 << MCF51XX_MUXPF_X4_BITNUM)
#define MCF51EM_LCDPF_LCD6_MASK              (MCF51XX_MUXPF_X4_MASK) 

/* LCD35 Mux Control */
#define MCF51EM_LCDPF_LCD35_LCD35            (0x00 << MCF51XX_MUXPF_X0_BITNUM) 
#define MCF51EM_LCDPF_LCD35_CLKO             (0x01 << MCF51XX_MUXPF_X0_BITNUM) 
#define MCF51EM_LCDPF_LCD35_RESERVED_1       (0x02 << MCF51XX_MUXPF_X0_BITNUM) 
#define MCF51EM_LCDPF_LCD35_RESERVED_2       (0x03 << MCF51XX_MUXPF_X0_BITNUM) 
#define MCF51EM_LCDPF_LCD35_MASK             (MCF51XX_MUXPF_X0_MASK)  


/* KBI Status Register Masks */
#define MCF51XX_KBIXSC_KBIMOD_MASK           1
#define MCF51XX_KBIXSC_KBIE_MASK             2
#define MCF51XX_KBIXSC_KBACK_MASK            4
#define MCF51XX_KBIXSC_KBF_MASK              8



/*------------------------------------------------------------------------*/
/*
** ICSC1 - Control Register 1 mask definitions                    
*/

#define MCF51EM_ICSC1_CLKS_BIT(x)         (x    << 6)
#define MCF51EM_ICSC1_RDIV_BIT(x)         (x    << 3)
#define MCF51EM_ICSC1_IREFS_BIT           (0x01 << 2)
#define MCF51EM_ICSC1_IRCLKEN_BIT         (0x01 << 1)
#define MCF51EM_ICSC1_IREFSTEN_BIT        (0x01 << 0)

#define MCF51EM_ICSC1_IRCLKEN_MASK              2
#define MCF51EM_ICSC1_IREFS_MASK                4
#define MCF51EM_ICSC1_RDIV0_MASK                8
#define MCF51EM_ICSC1_RDIV1_MASK                16
#define MCF51EM_ICSC1_RDIV2_MASK                32
#define MCF51EM_ICSC1_CLKS0_MASK                64
#define MCF51EM_ICSC1_CLKS1_MASK                128
#define MCF51EM_ICSC1_RDIV_MASK                 56
#define MCF51EM_ICSC1_RDIV_BITNUM               3
#define MCF51EM_ICSC1_CLKS_MASK                 192
#define MCF51EM_ICSC1_CLKS_BITNUM               6


/*------------------------------------------------------------------------*/
/*
** ICSC2 - Control Register 2 mask definitions                    
*/

#define MCF51EM_ICSC2_BDIV_BIT(x)         (x    << 6)
#define MCF51EM_ICSC2_RANGE_BIT           (0x01 << 5)
#define MCF51EM_ICSC2_HGO_BIT             (0x01 << 4) 
#define MCF51EM_ICSC2_LP_BIT              (0x01 << 3)
#define MCF51EM_ICSC2_EREFS_BIT           (0x01 << 2)
#define MCF51EM_ICSC2_ERCLKEN_BIT         (0x01 << 1) 
#define MCF51EM_ICSC2_EREFSTEN_BIT        (0x01 << 0)

#define MCF51EM_ICSC2_EREFSTEN_MASK             1
#define MCF51EM_ICSC2_ERCLKEN_MASK              2
#define MCF51EM_ICSC2_EREFS_MASK                4
#define MCF51EM_ICSC2_LP_MASK                   8
#define MCF51EM_ICSC2_HGO_MASK                  16
#define MCF51EM_ICSC2_RANGE_MASK                32
#define MCF51EM_ICSC2_BDIV0_MASK                64
#define MCF51EM_ICSC2_BDIV1_MASK                128
#define MCF51EM_ICSC2_BDIV_MASK                 192
#define MCF51EM_ICSC2_BDIV_BITNUM               6


 
/*------------------------------------------------------------------------*/
/*
** ICSSC - Status and Control Register mask definitions                   
*/

#define MCF51EM_ICSSC_DRST_BIT(x)         (x    << 6)
#define MCF51EM_ICSSC_DRS_BIT(x)          (x    << 6)
#define MCF51EM_ICSSC_DMX32_BIT           (0x01 << 5) 
#define MCF51EM_ICSSC_IREFST_BIT          (0x01 << 4)
#define MCF51EM_ICSSC_CLKST_BIT(x)        (x    << 2)
#define MCF51EM_ICSSC_OSCINIT_BIT         (0x01 << 1)
#define MCF51EM_ICSSC_FTRIM_BIT           (0x01 << 0)  

#define MCF51EM_ICSSC_FTRIM_MASK                1
#define MCF51EM_ICSSC_OSCINIT_MASK              2
#define MCF51EM_ICSSC_CLKST0_MASK               4
#define MCF51EM_ICSSC_CLKST1_MASK               8
#define MCF51EM_ICSSC_CLKST_MASK                12
#define MCF51EM_ICSSC_CLKST_BITNUM              2
#define MCF51EM_ICSSC_IREFST_MASK               16
#define MCF51EM_ICSSC_DMX32_MASK                32
#define MCF51EM_ICSSC_DRST_DRS0_MASK            64
#define MCF51EM_ICSSC_DRST_DRS1_MASK            128
#define MCF51EM_ICSSC_DRST_DRS_MASK             192

#define MCF51EM_ICSSC_DRST_DRS_BITNUM           6

/*------------------------------------------------------------------------*/
/*
** CCS registers - Clock Check & Select Control (CCSCTRL)  0xFFFF8240
*/

#define MCF51EM_CCSCTRL_SEL_MASK                1
#define MCF51EM_CCSCTRL_TEST_MASK               2
#define MCF51EM_CCSCTRL_EN_MASK                 4
#define MCF51EM_CCSCTRL_SEL_BITNUM              0
#define MCF51EM_CCSCTRL_TEST_BITNUM             1
#define MCF51EM_CCSCTRL_EN_BITNUM               2
#define MCF51EM_CCSCTRL_EN_BIT            (0x01 << 0)
#define MCF51EM_CCSCTRL_TEST_BIT          (0x01 << 0)
#define MCF51EM_CCSCTRL_SEL_BIT           (0x01 << 0)    

/*------------------------------------------------------------------------*/
/*
** PDB registers
*/
#define MCF51EM_PDB_SCR_EN                     (0x0001)
#define MCF51EM_PDB_SCR_IE                     (0x0002)
#define MCF51EM_PDB_SCR_TRIGSEL_MASK           (0x0007 << 2)
#define MCF51EM_PDB_SCR_TRIGSEL_1              (0x0000 << 2)
#define MCF51EM_PDB_SCR_TRIGSEL_2              (0x0001 << 2)
#define MCF51EM_PDB_SCR_TRIGSEL_EXTRIG         (0x0004 << 2)
#define MCF51EM_PDB_SCR_TRIGSEL_SWTRIG         (0x0007 << 2)
#define MCF51EM_PDB_SCR_SWTRIG                 (0x0020)
#define MCF51EM_PDB_SCR_CONT                   (0x0040)
#define MCF51EM_PDB_SCR_IF                     (0x0080)
#define MCF51EM_PDB_SCR_PRESCALER_MASK         (0xE000)
#define MCF51EM_PDB_SCR_PRESCALER_BITNUM       (13)

#define MCF51EM_PDB_CHCR_ENB                   (0x0001)
#define MCF51EM_PDB_CHCR_ENA                   (0x0002)
#define MCF51EM_PDB_CHCR_BOS_MASK              (0x000C)
#define MCF51EM_PDB_CHCR_BOS_0                 (0x0000)
#define MCF51EM_PDB_CHCR_BOS_B                 (0x0004)
#define MCF51EM_PDB_CHCR_BOS_AB                (0x0008)
#define MCF51EM_PDB_CHCR_BOS_PULSE             (0x000C)
#define MCF51EM_PDB_CHCR_AOS_MASK              (0x0030)
#define MCF51EM_PDB_CHCR_AOS_0                 (0x0000)
#define MCF51EM_PDB_CHCR_AOS_A                 (0x0010)
#define MCF51EM_PDB_CHCR_AOS_AB                (0x0020)
#define MCF51EM_PDB_CHCR_AOS_PULSE             (0x0030)
#define MCF51EM_PDB_CHCR_ERRB                  (0x4000)
#define MCF51EM_PDB_CHCR_ERRA                  (0x8000)

/*------------------------------------------------------------------------*/
/*
** ADC registers
*/
#define MCF51EM_ADC_CFG1_ADICLK_MASK           (0x0003)
#define MCF51EM_ADC_CFG1_ADICLK_BUSCLK         (0x0000)
#define MCF51EM_ADC_CFG1_ADICLK_BUSCLK2        (0x0001)
#define MCF51EM_ADC_CFG1_ADICLK_ALTCLK         (0x0002)
#define MCF51EM_ADC_CFG1_ADICLK_ADACK          (0x0003)
#define MCF51EM_ADC_CFG1_MODE_MASK             (0x000C)
#define MCF51EM_ADC_CFG1_MODE_8BIT             (0x0000)
#define MCF51EM_ADC_CFG1_MODE_12BIT            (0x0004)
#define MCF51EM_ADC_CFG1_MODE_10BIT            (0x0008)
#define MCF51EM_ADC_CFG1_MODE_16BIT            (0x000C)
#define MCF51EM_ADC_CFG1_ADLSMP                (0x0010)
#define MCF51EM_ADC_CFG1_ADIV_MASK             (0x0060)
#define MCF51EM_ADC_CFG1_ADIV(x)               ((x) << 5)
#define MCF51EM_ADC_CFG1_ADIV_1                (0x0000)
#define MCF51EM_ADC_CFG1_ADIV_2                (0x0020)
#define MCF51EM_ADC_CFG1_ADIV_4                (0x0040)
#define MCF51EM_ADC_CFG1_ADIV_8                (0x0060)
#define MCF51EM_ADC_CFG1_ADLPC                 (0x0080)

#define MCF51EM_ADC_CFG2_ADLSTS_MASK           (0x0003)
#define MCF51EM_ADC_CFG2_ADLSTS_20             (0x0000)
#define MCF51EM_ADC_CFG2_ADLSTS_12             (0x0001)
#define MCF51EM_ADC_CFG2_ADLSTS_6              (0x0002)
#define MCF51EM_ADC_CFG2_ADLSTS_2              (0x0003)
#define MCF51EM_ADC_CFG2_ADLSTS_DEFAULT        (MCF51EM_ADC_CFG2_ADLSTS_20)
#define MCF51EM_ADC_CFG2_ADHSC                 (0x0004)
#define MCF51EM_ADC_CFG2_ADACKEN               (0x0008)

#define MCF51EM_ADC_SC1_ADCCH_MASK             (0x001F)
#define MCF51EM_ADC_SC1_DIFF                   (0x0020)
#define MCF51EM_ADC_SC1_AIEN                   (0x0040)
#define MCF51EM_ADC_SC1_COCO                   (0x0080)

#define MCF51EM_ADC_SC2_REFSL_MASK             (0x0003)
#define MCF51EM_ADC_SC2_REFSL_VREF             (0x0000)
#define MCF51EM_ADC_SC2_REFSL_VALT             (0x0001)
#define MCF51EM_ADC_SC2_REFSL_VBG              (0x0002)
#define MCF51EM_ADC_SC2_ACREN                  (0x0008)
#define MCF51EM_ADC_SC2_ACFGT                  (0x0010)
#define MCF51EM_ADC_SC2_ACFE                   (0x0020)
#define MCF51EM_ADC_SC2_ADTRG                  (0x0040)
#define MCF51EM_ADC_SC2_ADACT                  (0x0080)

#define MCF51EM_ADC_SC3_AVGS_MASK              (0x0003)
#define MCF51EM_ADC_SC3_AVGS_4                 (0x0000)
#define MCF51EM_ADC_SC3_AVGS_8                 (0x0001)
#define MCF51EM_ADC_SC3_AVGS_16                (0x0002)
#define MCF51EM_ADC_SC3_AVGS_32                (0x0003)
#define MCF51EM_ADC_SC3_AVGE                   (0x0004)
#define MCF51EM_ADC_SC3_ADCO                   (0x0008)
#define MCF51EM_ADC_SC3_CALF                   (0x0040)
#define MCF51EM_ADC_SC3_CAL                    (0x0080)


/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/

/*
** MCF51EM_gpio_struct
** This structure defines (Rapid) General Purpose I/O registers (APPROACH #1)
*/

typedef struct MCF51EM_gpio_port_struct {

    uint_8  PTxD;             /*** Port Data                    ***/
    uint_8  PTxDD;            /*** Port Data Direction          ***/
    uint_8  PTxSET;           /*** Port Set                     ***/
    uint_8  PTxCLR;           /*** Port Clear                   ***/
    uint_8  PTxTOG;           /*** Port Toggle                  ***/
    uint_8  reserved00[0x03];
    uint_8  PTxPE;            /*** Port Pull-Up Enable          ***/
    uint_8  PTxSE;            /*** Port Slew Rate Control       ***/
    uint_8  PTxDS;            /*** Port Drive Strength Control  ***/
    uint_8  PTxIFE;           /*** Port Input Filter Control    ***/
    uint_8  reserved01[0x34];
} MCF51EM_GPIO_PORT_STRUCT, _PTR_ MCF51EM_GPIO_PORT_STRUCT_PTR;
typedef volatile struct MCF51EM_gpio_port_struct  _PTR_ VMCF51EM_GPIO_PORT_STRUCT_PTR;


typedef enum {
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_MAX
} gpio_port_t;


typedef struct MCF51EM_gpio_ports_struct
{
   MCF51EM_GPIO_PORT_STRUCT PORT[GPIO_PORT_MAX];
   uint_8  reserved0D[0x1D];
   uint_8  IRQSC;                 /*** Interrupt Pin Request S&C    0xFFFF81C0 ***/
   uint_8  reserved0E[0x3F];
   uint_16 PTxPF[GPIO_PORT_MAX];  /*** Port Peripheral Select       0xFFFF8200 ***/
   uint_16 LCDPF;                 /*** LCD Peripheral Select        0xFFFF820C ***/
} MCF51EM_GPIO_PORTS_STRUCT, _PTR_ MCF51EM_GPIO_PORTS_STRUCT_PTR;
typedef volatile struct MCF51EM_gpio_ports_struct _PTR_ VMCF51EM_GPIO_PORTS_STRUCT_PTR;

/*
** MCF51EM_gpio_struct
** This structure defines (Rapid) General Purpose I/O registers (APPROACH #2)
*/

typedef struct MCF51EM_gpio_struct
{
    uint_8  PTAD;           /*** Port Data                    0xFFFF8000 ***/
    uint_8  PTADD;          /*** Port Data Direction          0xFFFF8001 ***/
    uint_8  PTASET;         /*** Port Set                     0xFFFF8002 ***/
    uint_8  PTACLR;         /*** Port Clear                   0xFFFF8003 ***/
    uint_8  PTATOG;         /*** Port Toggle                  0xFFFF8004 ***/
    uint_8  reserved00[0x03];
    uint_8  PTAPE;          /*** Port Pull-Up Enable          0xFFFF8008 ***/      
    uint_8  PTASE;          /*** Port Slew Rate Control       0xFFFF8009 ***/      
    uint_8  PTADS;          /*** Port Drive Strength Control  0xFFFF800A ***/      
    uint_8  PTAIFE;         /*** Port Input Filter Control    0xFFFF800B ***/      
    uint_8  reserved01[0x34];
    uint_8  PTBD;           /*** Port Data                    0xFFFF8040 ***/
    uint_8  PTBDD;          /*** Port Data Direction          0xFFFF8041 ***/
    uint_8  PTBSET;         /*** Port Set                     0xFFFF8042 ***/
    uint_8  PTBCLR;         /*** Port Clear                   0xFFFF8043 ***/
    uint_8  PTBTOG;         /*** Port Toggle                  0xFFFF8044 ***/
    uint_8  reserved02[0x03];
    uint_8  PTBPE;          /*** Port Pull-Up Enable          0xFFFF8048 ***/
    uint_8  PTBSE;          /*** Port Slew Rate Control       0xFFFF8049 ***/
    uint_8  PTBDS;          /*** Port Drive Strength Control  0xFFFF804A ***/
    uint_8  PTBIFE;         /*** Port Input Filter Control    0xFFFF804B ***/
    uint_8  reserved03[0x34];
    uint_8  PTCD;           /*** Port Data                    0xFFFF8080 ***/
    uint_8  PTCDD;          /*** Port Data Direction          0xFFFF8081 ***/
    uint_8  PTCSET;         /*** Port Set                     0xFFFF8082 ***/
    uint_8  PTCCLR;         /*** Port Clear                   0xFFFF8083 ***/
    uint_8  PTCTOG;         /*** Port Toggle                  0xFFFF8084 ***/
    uint_8  reserved04[0x03];
    uint_8  PTCPE;          /*** Port Pull-Up Enable          0xFFFF8088 ***/
    uint_8  PTCSE;          /*** Port Slew Rate Control       0xFFFF8089 ***/
    uint_8  PTCDS;          /*** Port Drive Strength Control  0xFFFF808A ***/
    uint_8  PTCIFE;         /*** Port Input Filter Control    0xFFFF808B ***/
    uint_8  reserved05[0x34];
    uint_8  PTDD;           /*** Port Data                    0xFFFF80C0 ***/
    uint_8  PTDDD;          /*** Port Data Direction          0xFFFF80C1 ***/
    uint_8  PTDSET;         /*** Port Set                     0xFFFF80C2 ***/
    uint_8  PTDCLR;         /*** Port Clear                   0xFFFF80C3 ***/
    uint_8  PTDTOG;         /*** Port Toggle                  0xFFFF80C4 ***/
    uint_8  reserved06[0x03];
    uint_8  PTDPE;          /*** Port Pull-Up Enable          0xFFFF80C8 ***/
    uint_8  PTDSE;          /*** Port Slew Rate Control       0xFFFF80C9 ***/
    uint_8  PTDDS;          /*** Port Drive Strength Control  0xFFFF80CA ***/
    uint_8  PTDIFE;         /*** Port Input Filter Control    0xFFFF80CB ***/
    uint_8  reserved07[0x34];
    uint_8  PTED;           /*** Port Data                    0xFFFF8100 ***/
    uint_8  PTEDD;          /*** Port Data Direction          0xFFFF8101 ***/
    uint_8  PTESET;         /*** Port Set                     0xFFFF8102 ***/
    uint_8  PTECLR;         /*** Port Clear                   0xFFFF8103 ***/
    uint_8  PTETOG;         /*** Port Toggle                  0xFFFF8104 ***/
    uint_8  reserved08[0x03];
    uint_8  PTEPE;          /*** Port Pull-Up Enable          0xFFFF8108 ***/
    uint_8  PTESE;          /*** Port Slew Rate Control       0xFFFF8109 ***/
    uint_8  PTEDS;          /*** Port Drive Strength Control  0xFFFF810A ***/
    uint_8  PTEIFE;         /*** Port Input Filter Control    0xFFFF810B ***/
    uint_8  reserved09[0x34];
    uint_8  PTFD;           /*** Port Data                    0xFFFF8140 ***/
    uint_8  PTFDD;          /*** Port Data Direction          0xFFFF8141 ***/
    uint_8  PTFSET;         /*** Port Set                     0xFFFF8142 ***/
    uint_8  PTFCLR;         /*** Port Clear                   0xFFFF8143 ***/
    uint_8  PTFTOG;         /*** Port Toggle                  0xFFFF8144 ***/
    uint_8  reserved0A[0x03];
    uint_8  PTFPE;          /*** Port Pull-Up Enable          0xFFFF8148 ***/
    uint_8  PTFSE;          /*** Port Slew Rate Control       0xFFFF8149 ***/
    uint_8  PTFDS;          /*** Port Drive Strength Control  0xFFFF814A ***/
    uint_8  PTFIFE;         /*** Port Input Filter Control    0xFFFF814B ***/
    uint_8  reserved0B[0x34];
    uint_8  KBI1SC;         /*** Status & Control             0xFFFF8180 ***/
    uint_8  KBI1PE;         /*** Pin Select                   0xFFFF8181 ***/
    uint_8  KBI1ES;         /*** Interrupt Edge Select        0xFFFF8182 ***/   
    uint_8  reserved0C[0x1D];
    uint_8  KBI2SC;         /*** Status & Control             0xFFFF81A0 ***/
    uint_8  KBI2PE;         /*** Pin Select                   0xFFFF81A1 ***/
    uint_8  KBI2ES;         /*** Interrupt Edge Select        0xFFFF81A2 ***/
    uint_8  reserved0D[0x1D];
    uint_8  IRQSC;          /*** External Interrupt Module    0xFFFF81C0 ***/
    uint_8  reserved0E[0x3F];
    uint_16 PTAPF;          /*** Port Peripheral Select       0xFFFF8200 ***/
    uint_16 PTBPF;          /*** Port Peripheral Select       0xFFFF8202 ***/
    uint_16 PTCPF;          /*** Port Peripheral Select       0xFFFF8204 ***/
    uint_16 PTDPF;          /*** Port Peripheral Select       0xFFFF8206 ***/
    uint_16 PTEPF;          /*** Port Peripheral Select       0xFFFF8208 ***/
    uint_16 PTFPF;          /*** Port Peripheral Select       0xFFFF820A ***/
    uint_16 LCDPF;          /*** LCD  Peripheral Select       0xFFFF820C ***/
} MCF51EM_GPIO_STRUCT, _PTR_ MCF51EM_GPIO_STRUCT_PTR;
typedef volatile struct MCF51EM_gpio_struct _PTR_ VMCF51EM_GPIO_STRUCT_PTR;

/*
** MCF51EM_ICS_STRUCT
** Internal clock source module
*/
typedef struct MCF51EM_ics_struct
{
  uint_8 ICSC1;
  uint_8 ICSC2;
  uint_8 ICSTRM;
  uint_8 ICSSC;
  uint_8 reserved00[0x1C];
  uint_8 CCSCTRL;  /*** 0xFFFF8240 ICS Clock Check & Select Control Register;           ***/
  uint_8 CCSTMR1;  /*** 0xFFFF8241 ICS 8-bit counter incremented by XOSC1 timebase;     ***/
  uint_8 CCSTMR2;  /*** 0xFFFF8242 ICS 8-bit counter incremented by XOSC2 timebase;     ***/
  uint_8 CCSTMRIR; /*** 0xFFFF8243 ICS 8-bit counter incremented via IR clock timebase; ***/
} MCF51EM_ICS_STRUCT, _PTR_ MCF51EM_ICS_STRUCT_PTR;
typedef volatile struct MCF51EM_ics_struct _PTR_ VMCF51EM_ICS_STRUCT_PTR;


/*
** MCF51EM_irq_struct
** This structure defines Interrupt registers
*/

typedef struct MCF51EM_irq_struct
{
  uint_8  IRQSC;       /*** IRQSC - Interrupt Pin Request Status and Control Register; 0xFFFF80E0 ***/
} MCF51EM_IRQ_STRUCT, _PTR_ MCF51EM_IRQ_STRUCT_PTR;
typedef volatile struct MCF51EM_irq_struct _PTR_ VMCF51EM_IRQ_STRUCT_PTR;

/*
** MCF51EM_sim_struct
** This structure defines System Integration Module registers
*/

typedef struct MCF51EM_sim_struct
{
  uint_8  SRS;       /*** System Reset Status Register;                0xFFFF8280 ***/
  uint_8  SOPT1;     /*** System Options Register 1;                   0xFFFF8281 ***/
  uint_8  reserved00[0x02];
  uint_8  SDIDH;     /*** System Device Identification Register High;  0xFFFF8284 ***/
  uint_8  SDIDL;     /*** System Device Identification Register Low;   0xFFFF8285 ***/
  uint_8  SCGC1;     /*** System Clock Gating Control 1 Register;      0xFFFF8286 ***/
  uint_8  SCGC2;     /*** System Clock Gating Control 2 Register;      0xFFFF8287 ***/
  uint_8  SCGC3;     /*** System Clock Gating Control 3 Register;      0xFFFF8288 ***/
  uint_8  SCGC4;     /*** System Clock Gating Control 4 Register;      0xFFFF8289 ***/
  uint_8  SCGC5;     /*** System Clock Gating Control 5 Register;      0xFFFF828A ***/
  uint_8  SIMCO;     /*** System Clock Options Register;               0xFFFF828B ***/
  uint_8  SIMIPS1;   /*** Internal Peripheral Select Register 1;       0xFFFF828D ***/
  uint_8  SIMIPS2;   /*** Internal Peripheral Select Register 2;       0xFFFF828E ***/
} MCF51EM_SIM_STRUCT, _PTR_ MCF51EM_SIM_STRUCT_PTR;
typedef volatile struct MCF51EM_sim_struct _PTR_ VMCF51EM_SIM_STRUCT_PTR;

/*
** MCF51EM_mtim_struct
** Modulo Timer
*/
typedef struct MCF51EM_mtim_struct
{
   uint_8 MTIMSC;     /*** Modulo Timer Clock Configuration Register;   ***/
   uint_8 MTIMCLK;    /*** Modulo Timer Clock Configuration Register;   ***/
   uint_8 MTIMCNT;    /*** Modulo Timer Counter Register;               ***/
   uint_8 MTIMMOD;    /*** Modulo Timer Modulo Register;                ***/   
   
} MCF51EM_MTIM_STRUCT, _PTR_ MCF51EM_MTIM_STRUCT_PTR;
typedef volatile struct MCF51EM_mtim_struct _PTR_ VMCF51EM_MTIM_STRUCT_PTR;

/*
** MCF51EM_mtim16_struct
** Modulo Timer
*/
typedef struct MCF51EM_mtim16_struct
{
   uint_8  MTIMSC;     /*** Modulo Timer Clock Configuration Register;  ***/
   uint_8  MTIMCLK;    /*** Modulo Timer Clock Configuration Register;  ***/
   uint_16 MTIMCNT;    /*** Modulo Timer Counter Register;              ***/
   uint_16 MTIMMOD;    /*** Modulo Timer Modulo Register;               ***/   
   
} MCF51EM_MTIM16_STRUCT, _PTR_ MCF51EM_MTIM16_STRUCT_PTR;
typedef volatile struct MCF51EM_mtim16_struct _PTR_ VMCF51EM_MTIM16_STRUCT_PTR;


/*
** MCF51EM_VREF_STRUCT
** Internal voltage reference
*/
typedef struct MCF51EM_vref_struct
{
  uint_8 VREFTRM;      /*** VREF Trim Register      ***/
  uint_8 VREFSC;       /*** VREF Control Register   ***/
} MCF51EM_VREF_STRUCT, _PTR_ MCF51EM_VREF_STRUCT_PTR;
typedef volatile struct MCF51EM_vref_struct _PTR_ VMCF51EM_VREF_STRUCT_PTR;


/*
** MCF51EM_adc16_struct
** 16-bit Analog-to-Digital Converter
*/

typedef enum {
    ADC_1 = 0,
    ADC_2,
    ADC_3,
    ADC_4,
    ADC_MAX_MODULES
} acd_t;

typedef enum 
{
    ADC_A = 0,
    ADC_B,
    ADC_MAX_HW_CHANNELS
} adc_channel_t;

typedef struct MCF51EM_adc16_struct
{
  uint_8  ADCSC1[ADC_MAX_HW_CHANNELS]; /*** Status and Channel Control Register ***/
  uint_8  ADCCFG1;    /*** Configuration Register 1                          ***/
  uint_8  ADCCFG2;    /*** Configuration Register 2                          ***/ 
  uint_16 ADCR[ADC_MAX_HW_CHANNELS];   /*** Data result register A           ***/
  uint_16 ADCCV1;     /*** Compare value register 1                          ***/
  uint_16 ADCCV2;     /*** Compare value register 2                          ***/
  uint_8  ADCSC2;     /*** General status and control register 2             ***/
  uint_8  ADCSC3;     /*** General status and control register 3             ***/
  uint_16 ADCOFS;     /*** Offset Correction Register                        ***/
  uint_16 ADCPG;      /*** Plus-Side Gain Register                           ***/                     
  uint_16 ADCMG;      /*** Minus-Side Gain Register                          ***/
  uint_8  ADCCLPD;    /*** Plus-Side General Calibration Value Register D    ***/
  uint_8  ADCCLPS;    /*** Plus-Side General Calibration Value Register S    ***/
  uint_16 ADCCLP4;    /*** Plus-Side General Calibration Value Register 4    ***/
  uint_16 ADCCLP3;    /*** Plus-Side General Calibration Value Register 3    ***/
  uint_8  ADCCLP2;    /*** Plus-Side General Calibration Value Register 2    ***/
  uint_8  ADCCLP1;    /*** Plus-Side General Calibration Value Register 1    ***/
  uint_8  ADCCLP0;    /*** Plus-Side General Calibration Value Register 0    ***/
  uint_8  ADCTST;     /*** Test Register                                     ***/
  uint_8  ADCCLMD;    /*** Minus-Side General Calibration Value Register D   ***/
  uint_8  ADCCLMS;    /*** Minus-Side General Calibration Value Register S   ***/
  uint_16 ADCCLM4;    /*** Minus-Side General Calibration Value Register 4   ***/
  uint_16 ADCCLM3;    /*** Minus-Side General Calibration Value Register 3   ***/
  uint_8  ADCCLM2;    /*** Minus-Side General Calibration Value Register 2   ***/
  uint_8  ADCCLM1;    /*** Minus-Side General Calibration Value Register 1   ***/
  uint_8  ADCCLM0;    /*** Minus-Side General Calibration Value Register 0   ***/
  uint_8  ADCAPCTL1;  /*** Pin Control 1 Register                            ***/
  uint_8  ADCAPCTL2;  /*** Pin Control 2 Register                            ***/
  uint_8  ADCAPCTL3;  /*** Pin Control 3 Register                            ***/
  uint_8  ADCAPCTL4;  /*** Pin Control 4 Register                            ***/
  uint_8  reserved00[0x15];                                                   
} MCF51EM_ADC_STRUCT, _PTR_ MCF51EM_ADC_STRUCT_PTR;                           
typedef volatile struct MCF51EM_adc16_struct _PTR_ VMCF51EM_ADC_STRUCT_PTR;     
                                                                              
/*
** MCF51EM_PRACMP_STRUCT
** Programmable analog comparator
*/
typedef struct MCF51EM_pracmp_struct
{
  uint_8 CMPxCS;                   /*** Control and Status Register                  ***/
  uint_8 CMPxC0;                   /*** Control Register 0                           ***/
  uint_8 CMPxC1;                   /*** Control Register 1                           ***/
  uint_8 CMPxC2;                   /*** Control Register 2                           ***/
} MCF51EM_PRACMP_STRUCT, _PTR_ MCF51EM_PRACMP_STRUCT_PTR;
typedef volatile struct MCF51EM_pracmp_struct _PTR_ VMCF51EM_PRACMP_STRUCT_PTR;

/*
** MCF51EM_CRC_STRUCT
** CRC16 module
*/
typedef struct MCF51EM_crc_struct
{
  uint_16 CRC;                    /*** CRC Register                                ***/
  uint_8  TRANSPOSE;              /*** Transpose Register Register                 ***/
} MCF51EM_CRC_STRUCT, _PTR_ MCF51EM_CRC_STRUCT_PTR;
typedef volatile struct MCF51EM_crc_struct _PTR_ VMCF51EM_CRC_STRUCT_PTR;


/*
** MCF51EM_tpm_struct
** 2-channel Timer / PWM Module
*/

typedef struct MCF51EM_tpmch_struct
{
  uint_8  TPMCxSC;                /*** Channel Status and Control Register          ***/
  uint_16 TPMCxV;                 /*** Channel Value Register                       ***/
} MCF51EM_TPMCH_STRUCT, _PTR_ MCF51EM_TPMCH_STRUCT_PTR;

typedef enum {
    TPM_CH1 = 0,
    TPM_CH2,
    TPM_MAX
} tpm_ch_t;


typedef struct MCF51EM_tpm_struct
{
  uint_8  TPMSC;                    /*** Status and Control Register                ***/
  uint_16 TPMCNT;                   /*** Counter Register                           ***/
  uint_16 TPMMOD;                   /*** Counter Modulo Registers                   ***/   
  MCF51EM_TPMCH_STRUCT CH[TPM_MAX]; /*** Channel Registers                          ***/   
   
} MCF51EM_TPM_STRUCT, _PTR_ MCF51EM_TPM_STRUCT_PTR;
typedef volatile struct MCF51EM_tpm_struct _PTR_ VMCF51EM_TPM_STRUCT_PTR;



/*
** MCF51EM_lcd_struct
** LCD Module
*/

typedef struct MCF51EM_lcd_struct
{
  uint_8  LCDC0;                  /*** LCD Control Register 0                       ***/
  uint_8  LCDC1;                  /*** LCD Control Register 1                       ***/
  uint_8  LCDSUPPLY;              /*** LCD Voltage Supply Register                  ***/
  uint_8  LCDRVC;                 /*** LCD Regulated Voltage Control Register       ***/
  uint_8  LCDBCTL;                /*** LCD Blink Control Register                   ***/
  uint_8  LCDS;                   /*** LCD Status Register                          ***/
  uint_8  LCDPEN[6];              /*** LCD Pin Enable Registers 0-5                 ***/
  uint_8  reserved01[2];
  uint_8  LCDBPEN[6];             /*** LCD Backplane Enable Registers 0-5           ***/
  uint_8  reserved02[2];
  uint_8  LCDWF[44];              /*** LCD Waveform Registers 0-43                  ***/
  uint_8  reserved03[20];
} MCF51EM_LCD_STRUCT, _PTR_ MCF51EM_LCD_STRUCT_PTR;

/*
** MCF51EM_pdb_struct
** 4-channel PDB Module
*/

typedef struct MCF51EM_pdbch_struct
{
  uint_16 CR;                     /*** Channel Control Register                     ***/
  uint_16 DEL[ADC_MAX_HW_CHANNELS]; /*** Channel Delay Registers                    ***/
  uint_16 RESERVED;               /*** RESERVED for future use                      ***/
} MCF51EM_PDBCH_STRUCT, _PTR_ MCF51EM_PDBCH_STRUCT_PTR;


typedef enum {
    PDB_CH1 = 0,
    PDB_CH2,
    PDB_CH3,
    PDB_CH4,
    PDB_CHMAX
} pdb_ch_t;

typedef struct MCF51EM_pdb_struct
{
  uint_16 SCR;                    /*** 0x00 Status & Control Register               ***/
  uint_16 MOD;                    /*** 0x02 Counter Modulus Register                ***/
  uint_16 COUNT;                  /*** 0x04 Counter Value (READ ONLY) Register      ***/   
  uint_16 IDELAY;                 /*** 0x06 Comparison Value for Interrupt Timer    ***/
  MCF51EM_PDBCH_STRUCT CH[PDB_CHMAX];
   
} MCF51EM_PDB_STRUCT, _PTR_ MCF51EM_PDB_STRUCT_PTR;
typedef volatile struct MCF51EM_pdb_struct _PTR_ VMCF51EM_PDB_STRUCT_PTR;

/*
** MCF51EM_INTC_STRUCT
** Interrupt controller module
*/

typedef struct MCF51EM_intc_struct
{
  uint_8 reserved01[0x10];
  uint_8 FRC;                      /* 0x10 Force Interrupt Register                   ***/
  uint_8 reserved02[0x07];
  uint_8 PL6P7;                    /* 0x18 Programmable Level 6, Priority 7 Registers ***/
  uint_8 PL6P6;                    /* 0x19 Programmable Level 6, Priority 6 Registers ***/
  uint_8 reserved03;
  uint_8 WCR;                      /* 0x1B Wake-up Control Register                   ***/ 
  uint_8 reserved04[0x02];
  uint_8 SFRC;                     /* 0x1E Set Interrupt Force Register              ***/
  uint_8 CFRC;                     /* 0x1F Clear Interrupt Force Register */
  uint_8 SWIACK;                   /* 0x20 Software Interrupt Acknowledge Register   ***/
  uint_8 reserved05[0x03];
  uint_8 LVL1IACK;                 /* 0x24 Level 1 Interrupt Acknowledge Register    ***/
  uint_8 reserved06[0x03];
  uint_8 LVL2IACK;                 /* 0x28 Level 2 Interrupt Acknowledge Register    ***/
  uint_8 reserved07[0x03];
  uint_8 LVL3IACK;                 /* 0x2C Level 3 Interrupt Acknowledge Register    ***/
  uint_8 reserved08[0x03];
  uint_8 LVL4IACK;                 /* 0x30 Level 4 Interrupt Acknowledge Register    ***/
  uint_8 reserved09[0x03];
  uint_8 LVL5IACK;                 /* 0x34 Level 5 Interrupt Acknowledge Register    ***/
  uint_8 reserved10[0x03];
  uint_8 LVL6IACK;                 /* 0x38 Level 6 Interrupt Acknowledge Register    ***/
  uint_8 reserved11[0x03];
  uint_8 LVL7IACK;                 /* 0x3C Level 7 Interrupt Acknowledge Register    ***/
} MCF51EM_INTC_STRUCT, _PTR_ MCF51EM_INTC_STRUCT_PTR;
typedef volatile struct MCF51EM_intc_struct _PTR_ VMCF51EM_INTC_STRUCT_PTR;


#define ALIGN_TO(x) (x)
#define USE_REFERENCE(x) -sizeof(x)
#define AT_ADDRESS(x)   -x
typedef struct MCF51EM_struct
{
   
    MCF51EM_GPIO_STRUCT  GPIO;      /*** GPIO Module with Set/Clear/Toggle   0xFFFF8000 ***/
    uint_8     reserved00[0x8220 - 0x8000 - sizeof(MCF51EM_GPIO_STRUCT)];   
    MCF51EM_ICS_STRUCT   ICS;       /*** Internal Clock Source                0xFFFF8220 ***/
    uint_8        reserved01[0x8280 - 0x8220 - sizeof(MCF51EM_ICS_STRUCT)];   
    MCF51EM_SIM_STRUCT   SIM;       /*** System Integration Module            0xFFFF8280 ***/
    uint_8        reserved02[0x82A0 - 0x8280 - sizeof(MCF51EM_SIM_STRUCT)];
    MCF51XX_PMC_STRUCT   PMC;       /*** Power Management Controller          0xFFFF82A0 ***/
    uint_8        reserved03[0x82C0 - 0x82A0 - sizeof(MCF51XX_PMC_STRUCT)];
    MCF51XX_SCI_STRUCT   SCI1;      /*** Serial Communications Interface 1    0xFFFF82C0 ***/
    uint_8        reserved04[0x82E0 - 0x82C0 - sizeof(MCF51XX_SCI_STRUCT)];
    MCF51XX_SCI_STRUCT   SCI2;      /*** Serial Communications Interface 2    0xFFFF82E0 ***/
    uint_8        reserved05[0x8300 - 0x82E0 - sizeof(MCF51XX_SCI_STRUCT)];
    MCF51XX_SCI_STRUCT   SCI3;      /*** Serial Communications Interface 3    0xFFFF8300 ***/
    uint_8        reserved06[0x8320 - 0x8300 - sizeof(MCF51XX_SCI_STRUCT)];
    MCF5XXX_SPI16_STRUCT SPI1;      /*** Serial Peripheral Interface 1        0xFFFF8320 ***/
    uint_8        reserved07[0x8340 - 0x8320 - sizeof(MCF5XXX_SPI16_STRUCT)];
    MCF5XXX_SPI8_STRUCT   SPI2;      /*** Serial Peripheral Interface 2        0xFFFF8340 ***/
    uint_8        reserved08[0x8360 - 0x8340 - sizeof(MCF5XXX_SPI8_STRUCT)];
    MCF5XXX_SPI8_STRUCT   SPI3;      /*** Serial Peripheral Interface 3        0xFFFF8360 ***/
    uint_8        reserved09[0x8380 - 0x8360 - sizeof(MCF5XXX_SPI8_STRUCT)];
    MCF51XX_I2C_STRUCT   I2C;       /*** Inter-Integrated IC                  0xFFFF8380 ***/
    uint_8        reserved10[0x83C0 - 0x8380 - sizeof(MCF51XX_I2C_STRUCT)];
    MCF51EM_VREF_STRUCT VREF;       /*** Programmable Voltage Reference       0xFFFF83C0 ***/
    uint_8        reserved11[0x8400 - 0x83C0 - sizeof(MCF51EM_VREF_STRUCT)];
    /*** 16-Bit SAR AD Converters             0xFFFF8400 ***/    
    MCF51EM_ADC_STRUCT   ADC[ADC_MAX_MODULES];
    uint_8        reserved12[0x8520 - 0x8400 - ADC_MAX_MODULES * sizeof(MCF51EM_ADC_STRUCT)];
    /*** Programmable Reference Analog Comparator 1    0xFFFF8520 ***/
    MCF51EM_PRACMP_STRUCT  CMP1;    
    uint_8        reserved13[0x8540 - 0x8520 - sizeof(MCF51EM_PRACMP_STRUCT)];
    /*** Programmable Reference Analog Comparator 2    0xFFFF8540 ***/
    MCF51EM_PRACMP_STRUCT  CMP2;    
    uint_8        reserved14[0x8560 - 0x8540 - sizeof(MCF51EM_PRACMP_STRUCT)];
    MCF51EM_MTIM_STRUCT  MTIM1;     /*** 8-Bit Modulo Timer 1                 0xFFFF8560 ***/
    uint_8        reserved15[0x8580 - 0x8560 - sizeof(MCF51EM_MTIM_STRUCT)];
    MCF51EM_MTIM_STRUCT  MTIM2;     /*** 8-Bit Modulo Timer 2                 0xFFFF8580 ***/
    uint_8        reserved16[0x85A0 - 0x8580 - sizeof(MCF51EM_MTIM_STRUCT)];
    MCF51EM_MTIM16_STRUCT  MTIM3;   /*** 16-Bit Modulo Timer 3                0xFFFF85A0 ***/
    uint_8        reserved17[0x85C0 - 0x85A0 - sizeof(MCF51EM_MTIM16_STRUCT)];
    MCF51EM_CRC_STRUCT    CRC;      /*** Cyclic Redundancy Check Generator    0xFFFF85C0 ***/
    uint_8        reserved18[0x8600 - 0x85C0 - sizeof(MCF51EM_CRC_STRUCT)];
    MCF51EM_TPM_STRUCT    TPM;      /*** 2-channel Timer / PWM Module         0xFFFF8600 ***/
    uint_8        reserved19[0x8640 - 0x8600 - sizeof(MCF51EM_TPM_STRUCT)];
    MCF51EM_RTC_STRUCT    RTC;      /*** Real Time Counter                    0xFFFF8640 ***/
    uint_8        reserved20[0x8700 - 0x8640 - sizeof(MCF51EM_RTC_STRUCT)];
    MCF51EM_LCD_STRUCT    LCD;      /*** LCD Module                           0xFFFF8700 ***/
    uint_8        reserved21[0x8780 - 0x8700 - sizeof(MCF51EM_LCD_STRUCT)];
    MCF51XX_FTSR_STRUCT   FTSR1;    /*** Flash Wrapper 1                      0xFFFF8780 ***/
    uint_8        reserved22[0x87A0 - 0x8780 - sizeof(MCF51XX_FTSR_STRUCT)];
    MCF51XX_FTSR_STRUCT   FTSR2;    /*** Flash Wrapper 2                      0xFFFF87A0 ***/
    uint_8        reserved23[0xE000 - 0x87A0 - sizeof(MCF51XX_FTSR_STRUCT)];
    MCF51EM_PDB_STRUCT    PDB;      /*** Programmable Delay Block             0xFFFFE000 ***/
    uint_8        reserved24[0xFFC0 - 0xE000 - sizeof(MCF51EM_PDB_STRUCT)];
    MCF51EM_INTC_STRUCT   INTC;     /*** V1 ColdFire Interrupt Controller     0xFFFFFFC0 ***/
} MCF51EM_STRUCT, _PTR_ MCF51EM_STRUCT_PTR;
typedef volatile struct MCF51EM_struct _PTR_ VMCF51EM_STRUCT_PTR;


/*
** PSP_SUPPORT_STRUCT
** This structure is used to maintain the PSP support information
*/
typedef struct psp_support_struct
{
   uint_32 ACR_COUNT;   /* How many ACRs set so far */
   uint_32 Reserved;

} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;




/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_cacr;
extern          uint_8   __KERNEL_DATA_VERIFY_ENABLE[]; // CR1327

extern void    _mcf51EM_initialize_support(uint_32);

#endif /*__ASM__ */

#ifdef __cplusplus
}
#endif


#endif /* __mcf51em_h__ */
/* EOF */

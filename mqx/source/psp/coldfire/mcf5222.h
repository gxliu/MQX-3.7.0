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
* $FileName: mcf5222.h$
* $Version : 3.7.28.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the type definitions for the mcf5222 processor.
*
*END************************************************************************/

#ifndef __mcf5222_h__
#define __mcf5222_h__

#define __mcf5222_h__version "$Version:3.7.28.0$"
#define __mcf5222_h__date    "$Date:Feb-7-2011$"

#ifndef __ASM__

/* Include registers for modules common to all Coldfire processors */
#include <mcf52xx_ictl.h>       /* CTRL */   
#include <mcf522x_usbotg.h>     /* USBOTG */
#include <mcf52xx_uart.h>       /* UART */
#include <mcf5xxx_qspi.h>       /* QSPI */
#include <mcf52xx_i2c.h>        /* I2C */
#include <mcf52xx_rtc.h>        /* RTC */
#include <mcf522xx_adc.h>
#include <mcf522xx_pit.h>
#include <mcf52xx_cfm.h>        /* CFM */
#include <mcf522xx_eport.h>

#endif // __ASM__

#ifdef __cplusplus
extern "C" {
#endif



/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* Indicate processor type */
#define PSP_MCF5222                         1

#define PSP_HAS_DSP                         1
#define PSP_HAS_EMAC                        0

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  0
#define PSP_HAS_DATA_CACHE                  0
// #define PSP_CACHE_LINE_SIZE                 (0x10)

#ifdef __CODEWARRIOR__
#define NEED_MODF
#endif

#ifndef __ASM__
#define MCF5222_NUM_ACRS                    (2)

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
#define MCF5222_NUM_TIMERS                  (2) /* PIT */
#define MCF5222_NUM_UARTS                   (3)
#define MCF5222_NUM_DMAS                    (4)


/*
** Interrupt definitions
*/
#define MCF5222_ICTRL_MASKALL   1
#define MCF5222_ICTRL0_BASEx    64
//#define MCF5222_ICTRL1_BASEx  128

/*
** Interrupt vector table
*/
typedef enum mcf5222_interrupt_table_index {
   MCF5222_boot_stack_pointer,
   MCF5222_boot_program_counter,
   MCF5222_EXC_ACCESS_ERROR,
   MCF5222_EXC_ADDRESS_ERROR,
   MCF5222_EXC_ILLEGAL_INSTRUCTION,
   MCF5222_EXC_DIVIDE_BY_ZERO,
   MCF5222_EXC_rsvd6,
   MCF5222_EXC_rsvd7,
   MCF5222_EXC_PRIVILEGE_VIOLATION,
   MCF5222_EXC_NEXT_TRACE,
   MCF5222_EXC_UNIMPLEMENTED_LINE_A_OPCODE,
   MCF5222_EXC_UNIMPLEMENTED_LINE_F_OPCODE,
   MCF5222_EXC_DEBUG,
   MCF5222_EXC_rsvd13,
   MCF5222_EXC_FORMAT_ERROR,
   MCF5222_EXC_rsvd15,
   MCF5222_EXC_rsvd16,
   MCF5222_EXC_rsvd17,
   MCF5222_EXC_rsvd18,
   MCF5222_EXC_rsvd19,
   MCF5222_EXC_rsvd20,
   MCF5222_EXC_rsvd21,
   MCF5222_EXC_rsvd22,
   MCF5222_EXC_rsvd23,
   MCF5222_EXC_SPURIOUS,
   MCF5222_EXC_rsvd25,
   MCF5222_EXC_rsvd26,
   MCF5222_EXC_rsvd27,
   MCF5222_EXC_rsvd28,
   MCF5222_EXC_rsvd29,
   MCF5222_EXC_rsvd30,
   MCF5222_EXC_rsvd31,
   MCF5222_EXC_TRAP0,
   MCF5222_EXC_TRAP1,
   MCF5222_EXC_TRAP2,
   MCF5222_EXC_TRAP3,
   MCF5222_EXC_TRAP4,
   MCF5222_EXC_TRAP5,
   MCF5222_EXC_TRAP6,
   MCF5222_EXC_TRAP7,
   MCF5222_EXC_TRAP8,
   MCF5222_EXC_TRAP9,
   MCF5222_EXC_TRAP10,
   MCF5222_EXC_TRAP11,
   MCF5222_EXC_TRAP12,
   MCF5222_EXC_TRAP13,
   MCF5222_EXC_TRAP14,
   MCF5222_EXC_TRAP15,
   MCF5222_EXC_rsvd48,
   MCF5222_EXC_rsvd49,
   MCF5222_EXC_rsvd50,
   MCF5222_EXC_rsvd51,
   MCF5222_EXC_rsvd52,
   MCF5222_EXC_rsvd53,
   MCF5222_EXC_rsvd54,
   MCF5222_EXC_rsvd55,
   MCF5222_EXC_rsvd56,
   MCF5222_EXC_rsvd57,
   MCF5222_EXC_rsvd58,
   MCF5222_EXC_rsvd59,
   MCF5222_EXC_rsvd60,
   MCF5222_EXC_rsvd61,
   MCF5222_EXC_rsvd62,
   MCF5222_EXC_rsvd63,
   MCF5222_INT_FIRST_EXTERNAL,
   /* Interrupt Controller 0 */
   MCF5222_INT_EPORT0_EPF1,     //  1 Edge port flag 1
   MCF5222_INT_EPORT0_EPF2,     //  2 Edge port flag 2
   MCF5222_INT_EPORT0_EPF3,     //  3 Edge port flag 3
   MCF5222_INT_EPORT0_EPF4,     //  4 Edge port flag 4
   MCF5222_INT_EPORT0_EPF5,     //  5 Edge port flag 5
   MCF5222_INT_EPORT0_EPF6,     //  6 Edge port flag 6
   MCF5222_INT_EPORT0_EPF7,     //  7 Edge port flag 7
   MCF5222_INT_SWT,             //  8 Software watchdog timeout
   MCF5222_INT_DMA0,            //  9 DMA Channel 0 transfer complete
   MCF5222_INT_DMA1,            // 10 DMA Channel 1 transfer complete
   MCF5222_INT_DMA2,            // 11 DMA Channel 2 transfer complete
   MCF5222_INT_DMA3,            // 12 DMA Channel 3 transfer complete
   MCF5222_INT_UART0,           // 13 UART0 interrupt
   MCF5222_INT_UART1,           // 14 UART1 interrupt
   MCF5222_INT_UART2,           // 15 UART2 interrupt
   MCF5222_INT_rsvd16,          // 16 not used
   MCF5222_INT_I2C,             // 17 I2C interrupt
   MCF5222_INT_QSPI,            // 18 QSPI interrupt
   MCF5222_INT_DTIM0,           // 19 TMR0 interrupt
   MCF5222_INT_DTIM1,           // 20 TMR1 interrupt
   MCF5222_INT_DTIM2,           // 21 TMR2 interrupt
   MCF5222_INT_DTIM3,           // 22 TMR3 interrupt
   MCF5222_INT_rsvd23,          // 23 Transmit frame interrupt
   MCF5222_INT_rsvd24,          // 24 not used
   MCF5222_INT_rsvd25,          // 25 not used
   MCF5222_INT_rsvd26,          // 26 not used
   MCF5222_INT_rsvd27,          // 27 not used
   MCF5222_INT_rsvd28,          // 28 not used
   MCF5222_INT_rsvd29,          // 29 not used
   MCF5222_INT_rsvd30,          // 30 not used
   MCF5222_INT_rsvd31,          // 31 not used
   MCF5222_INT_rsvd32,          // 32 not used
   MCF5222_INT_rsvd33,          // 33 not used
   MCF5222_INT_rsvd34,          // 34 not used
   MCF5222_INT_rsvd35,          // 35 not used
   MCF5222_INT_rsvd36,          // 36 not used
   MCF5222_INT_rsvd37,          // 37 not used
   MCF5222_INT_rsvd38,          // 38 not used
   MCF5222_INT_rsvd39,          // 39 not used
   MCF5222_INT_rsvd40,          // 40 not used
   MCF5222_INT_TIMA_TOF,        // 41 Timer overflow
   MCF5222_INT_TIMA_PAIF,       // 42 Pulse accumulator input
   MCF5222_INT_TIMA_PAOVF,      // 43 Pulse accumulator overflow
   MCF5222_INT_TIMA_C0F,        // 44 Timer Channel 0
   MCF5222_INT_TIMA_C1F,        // 45 Timer Channel 1
   MCF5222_INT_TIMA_C2F,        // 46 Timer Channel 2
   MCF5222_INT_TIMA_C3F,        // 47 Timer Channel 3
   MCF5222_INT_PMM,             // 48 Low-voltage detect flag
   MCF5222_INT_ADC_ADCA,        // 49 ADCA conversion complete
   MCF5222_INT_ADC_ADCB,        // 50 ADCB conversion complete
   MCF5222_INT_ADC_ADCINT,      // 51 ADC interrupt
   MCF5222_INT_PWM,             // 52 Pulse width modulation interrupt
   MCF5222_INT_USB,             // 53 USB interrupt
   MCF5222_INT_rsvd54,          // 54 not used
   MCF5222_INT_PIT0,            // 55 PIT0 PIF PIT interrupt flag
   MCF5222_INT_PIT1,            // 56 PIT1 PIF PIT interrupt flag
   MCF5222_INT_rsvd57,          // 57 not used
   MCF5222_INT_rsvd58,          // 58 not used
   MCF5222_INT_CFM_CBEIF,       // 59 Command buffer empty interrupt
   MCF5222_INT_CFM_CCIF,        // 60 Command complete interrupt
   MCF5222_INT_CFM_PVIF,        // 61 Protection violation interrupt
   MCF5222_INT_CFM_AEIF,        // 62 Access error interrupt
   MCF5222_INT_RTC              // 63 RTC interrupt 
} MCF5222_INTERRUPT_TABLE_INDEX;


/*------------------------------------------------------------------------*/
/*
** SCM System control module
*/

/* Bit definitions and macros for IPSBAR */
#define MCF5222_SCM_IPSBAR_BA(x)                ((x)&0xC0000000)
#define MCF5222_SCM_IPSBAR_V                    (0x00000001)

/* Bit definitions and macros for RAMBAR */
#define MCF5222_SCM_RAMBAR_BA(x)                ((x)&0xFFFF0000)
#define MCF5222_SCM_RAMBAR_BDE                  (0x00000200)

/* Bit definitions and macros for FLASHBAR */
#define MCF5222_SCM_FLASHBAR_BA(x)              ((x)&0xFFF80000)
#define MCF5222_SCM_FLASHBAR_BDE                (0x00000200)

/* Bit definitions and macros for CRSR */
#define MCF5222_SCM_CRSR_EXT                    (0x80)
#define MCF5222_SCM_CRSR_CWDR                   (0x20)

/* Bit definitions and macros for CWCR */
#define MCF5222_SCM_CWCR_CWE                    (0x80)
#define MCF5222_SCM_CWCR_CWRI                   (0x40)
#define MCF5222_SCM_CWCR_CWT(x)                 (((x)&0x07)<<3)
#define MCF5222_SCM_CWCR_CWTA                   (0x04)
#define MCF5222_SCM_CWCR_CWTAVAL                (0x02)
#define MCF5222_SCM_CWCR_CWTIC                  (0x01)

/* Bit definitions and macros for LPICR */
#define MCF5222_SCM_LPICR_ENBSTOP               (0x80)
#define MCF5222_SCM_LPICR_XSTOP_IPL(x)          (((x)&0x07)<<4)

/* Bit definitions and macros for CWSR */
#define MCF5222_SCM_CWSR_SEQ1                   (0x55)
#define MCF5222_SCM_CWSR_SEQ2                   (0xAA)

/* Bit definitions and macros for PPMRH */
#define MCF5222_SCM_PPMRH_CDPORTS               (0x00000001)
#define MCF5222_SCM_PPMRH_CDEPORT               (0x00000002)
#define MCF5222_SCM_PPMRH_CDPIT0                (0x00000008)
#define MCF5222_SCM_PPMRH_CDPIT1                (0x00000010)
#define MCF5222_SCM_PPMRH_CDADC                 (0x00000080)
#define MCF5222_SCM_PPMRH_CDGPT                 (0x00000100)
#define MCF5222_SCM_PPMRH_CDPWN                 (0x00000200)
#define MCF5222_SCM_PPMRH_CDFCAN                (0x00000400)
#define MCF5222_SCM_PPMRH_CDCFM                 (0x00000800)

/* Bit definitions and macros for PPMRL */
#define MCF5222_SCM_PPMRL_CDG                   (0x00000002)
#define MCF5222_SCM_PPMRL_CDEIM                 (0x00000008)
#define MCF5222_SCM_PPMRL_CDDMA                 (0x00000010)
#define MCF5222_SCM_PPMRL_CDUART0               (0x00000020)
#define MCF5222_SCM_PPMRL_CDUART1               (0x00000040)
#define MCF5222_SCM_PPMRL_CDUART2               (0x00000080)
#define MCF5222_SCM_PPMRL_CDI2C                 (0x00000200)
#define MCF5222_SCM_PPMRL_CDQSPI                (0x00000400)
#define MCF5222_SCM_PPMRL_CDDTIM0               (0x00002000)
#define MCF5222_SCM_PPMRL_CDDTIM1               (0x00004000)
#define MCF5222_SCM_PPMRL_CDDTIM2               (0x00008000)
#define MCF5222_SCM_PPMRL_CDDTIM3               (0x00010000)
#define MCF5222_SCM_PPMRL_CDINTC0               (0x00020000)

/* Bit definitions and macros for PPMRS */
#define MCF5222_SCM_PPMRS_DISABLE_ALL           (64)
#define MCF5222_SCM_PPMRS_DISABLE_CFM           (43)
#define MCF5222_SCM_PPMRS_DISABLE_CAN           (42)
#define MCF5222_SCM_PPMRS_DISABLE_PWM           (41)
#define MCF5222_SCM_PPMRS_DISABLE_GPT           (40)
#define MCF5222_SCM_PPMRS_DISABLE_ADC           (39)
#define MCF5222_SCM_PPMRS_DISABLE_PIT1          (36)
#define MCF5222_SCM_PPMRS_DISABLE_PIT0          (35)
#define MCF5222_SCM_PPMRS_DISABLE_EPORT         (33)
#define MCF5222_SCM_PPMRS_DISABLE_PORTS         (32)
#define MCF5222_SCM_PPMRS_DISABLE_INTC          (17)
#define MCF5222_SCM_PPMRS_DISABLE_DTIM3         (16)
#define MCF5222_SCM_PPMRS_DISABLE_DTIM2         (15)
#define MCF5222_SCM_PPMRS_DISABLE_DTIM1         (14)
#define MCF5222_SCM_PPMRS_DISABLE_DTIM0         (13)
#define MCF5222_SCM_PPMRS_DISABLE_QSPI          (10)
#define MCF5222_SCM_PPMRS_DISABLE_I2C           (9)
#define MCF5222_SCM_PPMRS_DISABLE_UART2         (7)
#define MCF5222_SCM_PPMRS_DISABLE_UART1         (6)
#define MCF5222_SCM_PPMRS_DISABLE_UART0         (5)
#define MCF5222_SCM_PPMRS_DISABLE_DMA           (4)
#define MCF5222_SCM_PPMRS_SET_CDG               (1)

/* Bit definitions and macros for PPMRC */
#define MCF5222_SCM_PPMRC_ENABLE_ALL            (64)
#define MCF5222_SCM_PPMRC_ENABLE_CFM            (43)
#define MCF5222_SCM_PPMRC_ENABLE_CAN            (42)
#define MCF5222_SCM_PPMRC_ENABLE_PWM            (41)
#define MCF5222_SCM_PPMRC_ENABLE_GPT            (40)
#define MCF5222_SCM_PPMRC_ENABLE_ADC            (39)
#define MCF5222_SCM_PPMRC_ENABLE_PIT1           (36)
#define MCF5222_SCM_PPMRC_ENABLE_PIT0           (35)
#define MCF5222_SCM_PPMRC_ENABLE_EPORT          (33)
#define MCF5222_SCM_PPMRC_ENABLE_PORTS          (32)
#define MCF5222_SCM_PPMRC_ENABLE_INTC           (17)
#define MCF5222_SCM_PPMRC_ENABLE_DTIM3          (16)
#define MCF5222_SCM_PPMRC_ENABLE_DTIM2          (15)
#define MCF5222_SCM_PPMRC_ENABLE_DTIM1          (14)
#define MCF5222_SCM_PPMRC_ENABLE_DTIM0          (13)
#define MCF5222_SCM_PPMRC_ENABLE_QSPI           (10)
#define MCF5222_SCM_PPMRC_ENABLE_I2C            (9)
#define MCF5222_SCM_PPMRC_ENABLE_UART2          (7)
#define MCF5222_SCM_PPMRC_ENABLE_UART1          (6)
#define MCF5222_SCM_PPMRC_ENABLE_UART0          (5)
#define MCF5222_SCM_PPMRC_ENABLE_DMA            (4)
#define MCF5222_SCM_PPMRC_CLEAR_CDG             (1)


/*------------------------------------------------------------------------*/
/*
** General Purpose I/O (GPIO) Module
*/

#define MCF5222_GPIO_PORTx7                     (0x80)
#define MCF5222_GPIO_PORTx6                     (0x40)
#define MCF5222_GPIO_PORTx5                     (0x20)
#define MCF5222_GPIO_PORTx4                     (0x10)
#define MCF5222_GPIO_PORTx3                     (0x08)
#define MCF5222_GPIO_PORTx2                     (0x04)
#define MCF5222_GPIO_PORTx1                     (0x02)
#define MCF5222_GPIO_PORTx0                     (0x01)
#define MCF5222_GPIO_PORTx(x)                   (0x01<<x)

#define MCF5222_GPIO_DDRx7                      (0x80)
#define MCF5222_GPIO_DDRx6                      (0x40)
#define MCF5222_GPIO_DDRx5                      (0x20)
#define MCF5222_GPIO_DDRx4                      (0x10)
#define MCF5222_GPIO_DDRx3                      (0x08)
#define MCF5222_GPIO_DDRx2                      (0x04)
#define MCF5222_GPIO_DDRx1                      (0x02)
#define MCF5222_GPIO_DDRx0                      (0x01)
#define MCF5222_GPIO_DDRx(x)                    (0x01<<x)

#define MCF5222_GPIO_PORTxP7                    (0x80)
#define MCF5222_GPIO_PORTxP6                    (0x40)
#define MCF5222_GPIO_PORTxP5                    (0x20)
#define MCF5222_GPIO_PORTxP4                    (0x10)
#define MCF5222_GPIO_PORTxP3                    (0x08)
#define MCF5222_GPIO_PORTxP2                    (0x04)
#define MCF5222_GPIO_PORTxP1                    (0x02)
#define MCF5222_GPIO_PORTxP0                    (0x01)
#define MCF5222_GPIO_PORTxP(x)                  (0x01<<x)

#define MCF5222_GPIO_SETx7                      (0x80)
#define MCF5222_GPIO_SETx6                      (0x40)
#define MCF5222_GPIO_SETx5                      (0x20)
#define MCF5222_GPIO_SETx4                      (0x10)
#define MCF5222_GPIO_SETx3                      (0x08)
#define MCF5222_GPIO_SETx2                      (0x04)
#define MCF5222_GPIO_SETx1                      (0x02)
#define MCF5222_GPIO_SETx0                      (0x01)
#define MCF5222_GPIO_SETx(x)                    (0x01<<x)

#define MCF5222_GPIO_CLRx7                      (0x80)
#define MCF5222_GPIO_CLRx6                      (0x40)
#define MCF5222_GPIO_CLRx5                      (0x20)
#define MCF5222_GPIO_CLRx4                      (0x10)
#define MCF5222_GPIO_CLRx3                      (0x08)
#define MCF5222_GPIO_CLRx2                      (0x04)
#define MCF5222_GPIO_CLRx1                      (0x02)
#define MCF5222_GPIO_CLRx0                      (0x01)
#define MCF5222_GPIO_CLRx(x)                    (0x01<<x)

#define MCF5222_GPIO_PBCDPAR_PBPA               (0x80)
#define MCF5222_GPIO_PBCDPAR_PCDPA              (0x40)

#define MCF5222_GPIO_PEPAR_PEPA7                (0x4000)
#define MCF5222_GPIO_PEPAR_PEPA6                (0x1000)
#define MCF5222_GPIO_PEPAR_PEPA5                (0x0400)
#define MCF5222_GPIO_PEPAR_PEPA4                (0x0100)
#define MCF5222_GPIO_PEPAR_PEPA3                (0x0040)
#define MCF5222_GPIO_PEPAR_PEPA2                (0x0010)
#define MCF5222_GPIO_PEPAR_PEPA1(x)             (((x)&0x3)<<2)
#define MCF5222_GPIO_PEPAR_PEPA0(x)             (((x)&0x3))

#define MCF5222_GPIO_PFPAR_PFPA7                (0x80)
#define MCF5222_GPIO_PFPAR_PFPA6                (0x40)
#define MCF5222_GPIO_PFPAR_PFPA5                (0x20)

#define MCF5222_GPIO_PJPAR_PJPA7                (0x80)
#define MCF5222_GPIO_PJPAR_PJPA6                (0x40)
#define MCF5222_GPIO_PJPAR_PJPA5                (0x20)
#define MCF5222_GPIO_PJPAR_PJPA4                (0x10)
#define MCF5222_GPIO_PJPAR_PJPA3                (0x08)
#define MCF5222_GPIO_PJPAR_PJPA2                (0x04)
#define MCF5222_GPIO_PJPAR_PJPA1                (0x02)
#define MCF5222_GPIO_PJPAR_PJPA0                (0x01)
#define MCF5222_GPIO_PJPAR_PJPA(x)              (0x01<<x)

#define MCF5222_GPIO_PSDPAR_PSDPA               (0x80)

#define MCF5222_GPIO_PASPAR_PASPA1(x)           (((x)&0x3)<<2)
#define MCF5222_GPIO_PASPAR_PASPA0(x)           (((x)&0x3))

#define MCF5222_GPIO_PEHLPAR_PEHPA              (0x80)
#define MCF5222_GPIO_PEHLPAR_PELPA              (0x40)

/*
#define MCF5222_GPIO_PQSPAR_PQSPA6              (0x40)
#define MCF5222_GPIO_PQSPAR_PQSPA5              (0x20)
#define MCF5222_GPIO_PQSPAR_PQSPA4              (0x10)
#define MCF5222_GPIO_PQSPAR_PQSPA3              (0x08)
#define MCF5222_GPIO_PQSPAR_PQSPA2              (0x04)
#define MCF5222_GPIO_PQSPAR_PQSPA1              (0x02)
#define MCF5222_GPIO_PQSPAR_PQSPA0              (0x01)
#define MCF5222_GPIO_PQSPAR_PQSPA(x)            (0x01<<x)
*/

/* Bit definitions and macros for MCF5222_GPIO_PQSPAR */
#define MCF5222_GPIO_PQSPAR_PQSPA6(x)           (((x)&0x0003)<<12)
#define MCF5222_GPIO_PQSPAR_PQSPA5(x)           (((x)&0x0003)<<10)
#define MCF5222_GPIO_PQSPAR_PQSPA4(x)           (((x)&0x0003)<<8)
#define MCF5222_GPIO_PQSPAR_PQSPA3(x)           (((x)&0x0003)<<6)
#define MCF5222_GPIO_PQSPAR_PQSPA2(x)           (((x)&0x0003)<<4)
#define MCF5222_GPIO_PQSPAR_PQSPA1(x)           (((x)&0x0003)<<2)
#define MCF5222_GPIO_PQSPAR_PQSPA0(x)           (((x)&0x0003)<<0)


#define MCF5222_GPIO_PTCPAR_PTCPA3(x)           (((x)&0x3)<<6)
#define MCF5222_GPIO_PTCPAR_PTCPA2(x)           (((x)&0x3)<<4)
#define MCF5222_GPIO_PTCPAR_PTCPA1(x)           (((x)&0x3)<<2)
#define MCF5222_GPIO_PTCPAR_PTCPA0(x)           (((x)&0x3))

#define MCF5222_GPIO_PTDPAR_PTDPA3(x)           (((x)&0x3)<<6)
#define MCF5222_GPIO_PTDPAR_PTDPA2(x)           (((x)&0x3)<<4)
#define MCF5222_GPIO_PTDPAR_PTDPA1(x)           (((x)&0x3)<<2)
#define MCF5222_GPIO_PTDPAR_PTDPA0(x)           (((x)&0x3))

#define MCF5222_GPIO_PUAPAR_PUAPA3              (0x08)
#define MCF5222_GPIO_PUAPAR_PUAPA2              (0x04)
#define MCF5222_GPIO_PUAPAR_PUAPA1              (0x02)
#define MCF5222_GPIO_PUAPAR_PUAPA0              (0x01)

/* Bit definitions and macros for MCF5222_GPIO_PUAPAR */
#define MCF5222_GPIO_PUAPAR_PUAPAR0(x)          (((x)&0x03)<<0)
#define MCF5222_GPIO_PUAPAR_PUAPAR1(x)          (((x)&0x03)<<2)
#define MCF5222_GPIO_PUAPAR_PUAPAR2(x)          (((x)&0x03)<<4)
#define MCF5222_GPIO_PUAPAR_PUAPAR3(x)          (((x)&0x03)<<6)
#define MCF5222_GPIO_PUAPAR_TXD0_TXD0           (0x01)
#define MCF5222_GPIO_PUAPAR_RXD0_RXD0           (0x04)
#define MCF5222_GPIO_PUAPAR_RTS0_RTS0           (0x10)
#define MCF5222_GPIO_PUAPAR_CTS0_CTS0           (0x40)
#define MCF5222_GPIO_PUAPAR_RTS0_CANTX          (0x20)
#define MCF5222_GPIO_PUAPAR_CTS0_CANRX          (0x80)

/* Bit definitions and macros for PUBPAR */
#define MCF5222_GPIO_PUBPAR_PUBPAR0(x)          (((x)&0x03)<<0)
#define MCF5222_GPIO_PUBPAR_PUBPAR1(x)          (((x)&0x03)<<2)
#define MCF5222_GPIO_PUBPAR_PUBPAR2(x)          (((x)&0x03)<<4)
#define MCF5222_GPIO_PUBPAR_PUBPAR3(x)          (((x)&0x03)<<6)
#define MCF5222_GPIO_PUBPAR_TXD1_TXD1           (0x01)
#define MCF5222_GPIO_PUBPAR_RXD1_RXD1           (0x04)
#define MCF5222_GPIO_PUBPAR_RTS1_RTS1           (0x10)
#define MCF5222_GPIO_PUBPAR_CTS1_CTS1           (0x40)
#define MCF5222_GPIO_PUBPAR_RTS1_SYNCB          (0x20)
#define MCF5222_GPIO_PUBPAR_CTS1_SYNCA          (0x80)
#define MCF5222_GPIO_PUBPAR_RTS1_TXD2           (0x30)
#define MCF5222_GPIO_PUBPAR_CTS1_RXD2           (0xC0)

/* Bit definitions and macros for PUCPAR */
#define MCF5222_GPIO_PUCPAR_PUCPAR0(x)          (((x)&0x03)<<0)
#define MCF5222_GPIO_PUCPAR_PUCPAR1(x)          (((x)&0x03)<<2)
#define MCF5222_GPIO_PUCPAR_PUCPAR2(x)          (((x)&0x03)<<4)
#define MCF5222_GPIO_PUCPAR_PUCPAR3(x)          (((x)&0x03)<<6)
#define MCF5222_GPIO_PUCPAR_TXD2_TXD2           (0x01)
#define MCF5222_GPIO_PUCPAR_RXD2_RXD2           (0x04)
#define MCF5222_GPIO_PUCPAR_RTS2_RTS2           (0x10)
#define MCF5222_GPIO_PUCPAR_CTS2_CTS2           (0x40)
#define MCF5222_GPIO_PUCPAR_TXD2_USBSE0         (0x03)
#define MCF5222_GPIO_PUCPAR_RXD2_USBDATA        (0x0C)
#define MCF5222_GPIO_PUCPAR_RTS2_USBVBUSDIS     (0x30)
#define MCF5222_GPIO_PUCPAR_CTS2_USBVBUSCHG     (0xC0)

/* Bit definitions and macros for PDDPAR */
#define MCF5222_GPIO_PDDPAR_PST                 (0x0F)


/*------------------------------------------------------------------------*/
/*
** Chip select macros
*/

#define MCF5222_CS_CSAR_BA(a)                   (uint_16)(((a)&0xFFFF0000)>>16)

#define MCF5222_CS_CSMR_BAM_4G                  (0xFFFF0000)
#define MCF5222_CS_CSMR_BAM_2G                  (0x7FFF0000)
#define MCF5222_CS_CSMR_BAM_1G                  (0x3FFF0000)
#define MCF5222_CS_CSMR_BAM_1024M               (0x3FFF0000)
#define MCF5222_CS_CSMR_BAM_512M                (0x1FFF0000)
#define MCF5222_CS_CSMR_BAM_256M                (0x0FFF0000)
#define MCF5222_CS_CSMR_BAM_128M                (0x07FF0000)
#define MCF5222_CS_CSMR_BAM_64M                 (0x03FF0000)
#define MCF5222_CS_CSMR_BAM_32M                 (0x01FF0000)
#define MCF5222_CS_CSMR_BAM_16M                 (0x00FF0000)
#define MCF5222_CS_CSMR_BAM_8M                  (0x007F0000)
#define MCF5222_CS_CSMR_BAM_4M                  (0x003F0000)
#define MCF5222_CS_CSMR_BAM_2M                  (0x001F0000)
#define MCF5222_CS_CSMR_BAM_1M                  (0x000F0000)
#define MCF5222_CS_CSMR_BAM_1024K               (0x000F0000)
#define MCF5222_CS_CSMR_BAM_512K                (0x00070000)
#define MCF5222_CS_CSMR_BAM_256K                (0x00030000)
#define MCF5222_CS_CSMR_BAM_128K                (0x00010000)
#define MCF5222_CS_CSMR_BAM_64K                 (0x00000000)
#define MCF5222_CS_CSMR_WP                      (0x00000100)
#define MCF5222_CS_CSMR_AM                      (0x00000040)
#define MCF5222_CS_CSMR_CI                      (0x00000020)
#define MCF5222_CS_CSMR_SC                      (0x00000010)
#define MCF5222_CS_CSMR_SD                      (0x00000008)
#define MCF5222_CS_CSMR_UC                      (0x00000004)
#define MCF5222_CS_CSMR_UD                      (0x00000002)
#define MCF5222_CS_CSMR_V                       (0x00000001)

#define MCF5222_CS_CSCR_WS(x)                   (((x)&0x0F)<<10)
#define MCF5222_CS_CSCR_AA                      (0x0100)
#define MCF5222_CS_CSCR_PS_8                    (0x0040)
#define MCF5222_CS_CSCR_PS_16                   (0x0080)
#define MCF5222_CS_CSCR_PS_32                   (0x0000)
#define MCF5222_CS_CSCR_BEM                     (0x0020)
#define MCF5222_CS_CSCR_BSTR                    (0x0010)
#define MCF5222_CS_CSCR_BSTW                    (0x0008)


/*------------------------------------------------------------------------*/
/*
** Clock definitions
*/

/* Bit definitions and macros for SYNCR */
#define MCF5222_CLOCK_SYNCR_LOLRE               (0x8000)
#define MCF5222_CLOCK_SYNCR_MFD(x)              (((x)&0x0007)<<12)
#define MCF5222_CLOCK_SYNCR_LOCRE               (0x0800)
#define MCF5222_CLOCK_SYNCR_RFD(x)              (((x)&0x0007)<<8)
#define MCF5222_CLOCK_SYNCR_LOCEN               (0x0080)
#define MCF5222_CLOCK_SYNCR_DISCLK              (0x0040)
#define MCF5222_CLOCK_SYNCR_FWKUP               (0x0020)
#define MCF5222_CLOCK_SYNCR_CLKSRC              (0x0004)
#define MCF5222_CLOCK_SYNCR_PLLMODE             (0x0002)
#define MCF5222_CLOCK_SYNCR_PLLEN               (0x0001)

/* Bit definitions and macros for SYNSR */
#define MCF5222_CLOCK_SYNSR_LOCKS               (0x10)
#define MCF5222_CLOCK_SYNSR_LOCK                (0x08)
#define MCF5222_CLOCK_SYNSR_LOCS                (0x04)

/* Bit definitions and macros for LPCR */
#define MCF5222_CLOCK_LPCR_LPD(x)               (((x)&0x0F)<<0)

/* Bit definitions and macros for CCHR */
#define MCF5222_CLOCK_CCHR_PFD(x)               (((x)&0x07)<<0)

/* Bit definitions and macros for RTCDR */
#define MCF5222_CLOCK_RTCDR_RTCDF(x)            (((x)&0xFFFFFFFF)<<0)

/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/


/*
** MCF5222_SCM_STRUCT
** System control module                                                                                                    
*/
typedef struct mcf5222_scm_struct
{
   uint_32  IPSBAR;         // Module base address register
   uint_32  filler1;        // FLASH base address register   
   uint_32  RAMBAR;         // RAM base address register
   uint_32  PPMRH;          // Peripheral Power Management Register High
   uchar    CRSR;           // Core reset status register
   uchar    CWCR;           // Core watchdog control register
   uchar    LPICR;          // Low Power Interrupt Control Register
   uchar    CWSR;           // Core watchdog service register
   uint_32  DMAREQC;        // DMA Request Control Register
   uint_32  PPMRL;          // Peripheral Power Management Register - Low
   uint_32  MPARK;         // Default Bus Master Park Register
   uchar    MPR;            // Master Privilege Register
   uchar    filler2[3];
   uchar    PACR0;          // Peripheral Access Control Register 0
   uchar    PACR1;          // Peripheral Access Control Register 1
   uchar    PACR2;          // Peripheral Access Control Register 2
   uchar    PACR3;          // Peripheral Access Control Register 3
   uchar    PACR4;          // Peripheral Access Control Register 4
   uchar    PACR5;          // Peripheral Access Control Register 5
   uchar    PACR6;          // Peripheral Access Control Register 6
   uchar    PACR7;          // Peripheral Access Control Register 7
   uchar    PACR8;          // Peripheral Access Control Register 8 
   uchar    filler[3];
   uchar    GPACR0;         // Grouped Peripheral Access Control Register 0 
   uchar    GPACR1;         // Grouped Peripheral Access Control Register 1
   uchar    filler3[0x0040 - 0x0031 - 1];
 } MCF5222_SCM_STRUCT, _PTR_ MCF5222_SCM_STRUCT_PTR;
typedef volatile struct mcf5222_scm_struct _PTR_ VMCF5222_SCM_STRUCT_PTR;


/*
** MCF5222_DMA_STRUCT
** This structure defines what one DMA registers look like                                                             
*/
typedef struct mcf5222_dma_struct
{
   uint_32  SAR;            // DMA Source address register
   uint_32  DAR;            // DMA Destination address register
   uint_32  BCR;            // DMA status register
   uint_32  DCR;            // DMA control register
} MCF5222_DMA_STRUCT, _PTR_ MCF5222_DMA_STRUCT_PTR;
typedef volatile struct mcf5222_dma_struct _PTR_ VMCF5222_DMA_STRUCT_PTR;

#define DMA_BYTE_COUNT(reg_ptr) (reg_ptr->DSR & 0x00FFFFFF)                    


/*
** MCF5222_DMA_STRUCT
** This structure defines what one timer register look like                         
*/
typedef struct mcf5222_dma_timer_struct
{
   uint_16  DTMR;           // DMA Timer mode register
   uchar    DTXTMR;         // DMA Timer extended mode register
   uchar    DTER;           // DMA Timer event register
   uint_32  DTRR;           // DMA Timer reference register
   uint_32  DTCR;           // DMA Timer capture register
   uint_32  DTCN;           // DMA Timer counter register
   uchar    filler1[0x30];
} MCF5222_DMA_TIMER_STRUCT, _PTR_ MCF5222_DMA_TIMER_STRUCT_PTR;
typedef volatile struct mcf5222_dma_timer_struct _PTR_ VMCF5222_DMA_TIMER_STRUCT_PTR;

 
#define PSP_GET_ICTRL0_BASE()   (&((VMCF5222_STRUCT_PTR)_PSP_GET_IPSBAR())->ICTRL0)

/*
** MCF5222_GPIO_STRUCT
** GPIO Registers                                                                         
*/                                                                                                                                            
typedef struct mcf5222_gpio_struct
{
   /* Port Output Data Registers */
   uchar    filler1[8];
   uchar    PORTNQ, filler2, PORTAN, PORTAS;
   uchar    PORTQS, filler3, PORTTA, PORTTC;
   uchar    filler3_1, PORTUA, PORTUB, PORTUC;
   uchar    PORTDD, filler4[3];
   /* Port Data Direction Registers */
   uchar    filler5[8];
   uchar    DDRNQ, filler6, DDRAN, DDRAS;
   uchar    DDRQS, filler7, DDRTA, DDRTC;
   uchar    filler7_1, DDRUA, DDRUB, DDRUC;
   uchar    DDRDD,  filler8[3];
   /* Port Pin Data/Set Data Registers */
   uchar    filler9[8];
   uchar    PORTNQP_SETNQ, filler10, PORTANP_SETAN, PORTASP_SETAS;  
   uchar    PORTQSP_SETQS, filler11, PORTTAP_SETTA, PORTTCP_SETTC;
   uchar    filler11_1, PORTUAP_SETUA, PORTUBP_SETUB, PORTUCP_SETUC;
   uchar    PORTDDP_SETDD, filler12[3];
   /* Port Clear Output Data Registers */
   uchar    filler13[8];
   uchar    CLRNQ, filler14, CLRAN, CLRAS;
   uchar    CLRQS, filler15, CLRTA, CLRTC;
   uchar    filler13_1, CLRUA, CLRUB, CLRUC;
   uchar    CLRDD,  filler16[3];
   /* Port Pin Assignment Registers */
   uchar    filler17[8];
   uint_16  PNQPAR;
   uchar    PANPAR, PASPAR;
   uint_16  PQSPAR;
   uchar    PTAPAR, PTCPAR; 
   uchar    filler17_1, PUAPAR, PUBPAR, PUCPAR;
   uchar    PDDPAR,  filler18[3];
   /* Port Pad Control Registers */
   uint_32  PSRR;                   // Pin Slew Rate Register [31:0]   
   uint_32  PDSR;                   // Pin Drive Strength Register [31:0]
   uchar    filler19[0xFF80];
}  MCF5222_GPIO_STRUCT, _PTR_ MCF5222_GPIO_STRUCT_PTR;
typedef volatile struct mcf5222_gpio_struct _PTR_ VMCF5222_GPIO_STRUCT_PTR;


/*
** MCF5222_CIM_STRUCT
** ColdFire Integration Module                                            
*/
typedef struct mcf5222_cim_struct
{
   uchar    RCR;            // Reset control register
   uchar    RSR;            // Reset status register
   uchar    filler1[2];
   uint_16  CCR;            // Chip configuration register
   uchar    filler2;
   uchar    LPCR;           // Low power control register
   uint_16  RCON;           // Reset configuration register
   uint_16  CIR;            // Chip identification register
   uchar    filler3[0xFFF4];
} MCF5222_CIM_STRUCT, _PTR_ MCF5222_CIM_STRUCT_PTR;
typedef volatile struct mcf5222_cim_struct _PTR_ VMCF5222_CIM_STRUCT_PTR;


/*
** MCF5222_CLK_STRUCT
** Clock module registers
*/
typedef struct mcf5222_clk_struct
{
   uint_16  SYNCR;          // Synthesizer control register
   uint_8   SYNSR;          // Synthesizer status register
   uint_8   filler0;
   uint_16  ROCR;            // Relaxation Oscillator Control Register
   uint_8   filler1;
   uint_8   LPDR;            // Low Power Divider Register                                               
   uchar    CCHR;            // Clock Control High Register
   uchar    CCLR;            // Clock Control Low Register
   uchar    OCHR;            // Oscillator Control High Register
   uchar    OCLR;            // Oscillator Control Low Register
   uint_32  RTCDR;          // Real time clock divide register   
   uchar    filler3[0xFFEF];
} MCF5222_CLK_STRUCT, _PTR_ MCF5222_CLK_STRUCT_PTR;
typedef volatile struct mcf5222_clk_struct _PTR_ VMCF5222_CLK_STRUCT_PTR;

/*
** MCF5222_WATCHDOG_STRUCT
** Watchdog timer
*/
typedef struct mcf5222_watchdog_struct
{
   uint_16  WCR;            // Watchdog control register
   uint_16  WMR;            // Watchdog modulus register
   uint_16  WCNTR;          // Watchdog count register
   uint_16  WSR;            // Watchdog service register
   uchar   filler[0xFFF8];
} MCF5222_WATCHDOG_STRUCT, _PTR_ MCF5222_WATCHDOG_STRUCT_PTR;
typedef volatile struct mcf5222_watchdog_struct _PTR_ VMCF5222_WATCHDOG_STRUCT_PTR;

/*
** MCF5222_GPT_STRUCT        
** Programmable interrupt timer
*/
typedef struct mcf5222_gpt_struct
{   
   uchar    GPTIOS;         // GPT IC/OC Select Register
   uchar    GPTCFORC;       // GPT Compare Force Register      
   uchar    GPTOC3M;        // GPT Output Compare 3 Mask Register
   uchar    GPTOC3D;        // GPT Output Compare 3 Data Register
   uint_16  GPTCNT;         // GPT Counter Register
   uchar    GPTSCR1;        // GPT System Control Register 1
   uchar    filler1;
   uchar    GPTTOV;         // GPT Toggle-on-Overflow Register
   uchar    GPTCTL1;        // GPT Control Register 1
   uchar    filler2;
   uchar    GPTCTL2;        // GPT Control Register 2
   uchar    GPTIE;          // GPT Interrupt Enable Register
   uchar    GPTSCR2;        // GPT System Control Register 2
   uchar    GPTFLG1;        // GPT Flag Register 1
   uchar    GPTAFLG2;       // GPT Flag Register 2
   uint_16  GPTC0;          // GPT Channel 0 Register
   uint_16  GPTC1;          // GPT Channel 1 Register
   uint_16  GPTC2;          // GPT Channel 2 Register
   uint_16  GPTC3;          // GPT Channel 3 Register
   uchar    GPTPACTL;       // Pulse Accumulator Control Register
   uchar    GPTPAFLG;       // Pulse Accumulator Flag Register
   uint_16  GPTPACNT;       // Pulse Accumulator Counter Register
   uchar    filler3;
   uchar    GPTPORT;        // GPT Port Data Register
   uchar    GPTDDR;         // GPT Port Data Direction Register   
   uchar    filler[0xFFE0];
} MCF5222_GPT_STRUCT, _PTR_ MCF5222_GPT_STRUCT_PTR;
typedef volatile struct mcf5222_gpt_struct _PTR_ VMCF5222_GPT_STRUCT_PTR;


/*
** MCF5222_PWM_STRUCT           
** Programmable interrupt timer
*/
typedef struct mcf5222_pwm_struct
{   
   uchar    PWME;            // PWM Enable Register
   uchar    PWMPOL;          // PWM Polarity Register
   uchar    PWMCLK;          // PWM Clock Select Register
   uchar    PWMPRCLK;        // PWM Prescale Clock Select Register
   uchar    PWMCAE;          // PWM Center Align Enable Register
   uchar    PWMCTL;          // PWM Control Register
   uchar    filler1[2];
   uchar    PWMSCLA;         // PWM Scale A Register
   uchar    PWMSCLB;         // PWM Scale B Register
   uchar    filler2[2];
   uchar    PWMCNT[8];         // PWM Channel Counter Registers (0-7)
   uchar    PWMPER[8];         // PWM Channel Period Registers (0-7)
   uchar    PWMDTY[8];         // PWM Channel Duty Register (0-7)
   uchar    PWMSDN;          // PWM Shutdown Register
   uchar    filler[0xffdb];   
} MCF5222_PWM_STRUCT, _PTR_ MCF5222_PWM_STRUCT_PTR;
typedef volatile struct mcf5222_pwm_struct _PTR_ VMCF5222_PWM_STRUCT_PTR;

/*
** MCF5222_STRUCT
** This structure defines the memory/registers provided by the MCF5222
*/
typedef struct mcf5222_struct
{
   MCF5222_SCM_STRUCT       SCM;                        // System Control Module
   uchar                    filler1[64];
   uchar                    filler2[128];
   MCF5222_DMA_STRUCT       DMA[MCF5222_NUM_DMAS];      // DMA Channels
   uchar                    filler3[192];
   MCF52XX_UART_STRUCT      UART[MCF5222_NUM_UARTS];    // UART
   uchar                   filler4[64];
   MCF52XX_I2C_STRUCT       I2C;                        // I2C
   MCF5XXX_QSPI_STRUCT      QSPI;                       // QSPI
   uchar                    filler5[64];
   MCF52XX_RTC_STRUCT       RTC;                        // RTC
   MCF5222_DMA_TIMER_STRUCT DMA_TIMER[MCF5222_NUM_DMAS];// DMA Timers   
   uchar                   filler6[1792];
   MCF52XX_ICTRL0_STRUCT    ICTRL0;                     // Interrupt Controller                 
   uchar                   filler7[736/*512*/];
   MCF52XX_GIACK_STRUCT    GIACK;
   uchar                   filler9[0xFF000];
   MCF5222_GPIO_STRUCT      GPIO;                       // Ports
   MCF5222_CIM_STRUCT       CIM;                        // ColdFire Integration Module
   MCF5222_CLK_STRUCT       CLK;                        // Clock Module registers
   MCF522XX_EPORT_STRUCT        EPORT;                      // Edge Port 0
   MCF5222_WATCHDOG_STRUCT WATCHDOG;                   // backup watchdog registers
  // uchar                   filler10[0xFFFF];
   MCF522XX_PIT_STRUCT      PIT[MCF5222_NUM_TIMERS];    // Programmable Interrupt Timers
   uchar                   filler11[0x10000];
   uchar                   filler12[0x10000];
   MCF522XX_ADC_STRUCT      ADC;                        // A/D Converter
   MCF5222_GPT_STRUCT       GPT;                        // General Purpose Timer 
   MCF5222_PWM_STRUCT       PWM;                        // General Purpose Timer 
   USB_MemMap               USBOTG;                     // USB
   uchar                   filler13[0x1D0000 - 0x1C0000 - sizeof(USB_MemMap)];
   MCF52XX_CFM_STRUCT      CFM;   

} MCF5222_STRUCT, _PTR_ MCF5222_STRUCT_PTR;
typedef volatile struct mcf5222_struct _PTR_ VMCF5222_STRUCT_PTR;

/*
** PSP_SUPPORT_STRUCT
** This structure is used to maintain the PSP support information
*/
typedef struct psp_support_struct
{
   uint_32 ACR_COUNT;   // How many ACRs set so far
   uint_32 reserved;

} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;

/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_cacr;
extern volatile uint_32 _psp_saved_acr0;
extern volatile uint_32 _psp_saved_acr1;
extern          uchar   __KERNEL_DATA_VERIFY_ENABLE[]; // CR1327

extern pointer _mcf5222_get_ipsbar(void);
extern void    _mcf5222_initialize_support(uint_32);

extern void    _mcf5222_cache_enable(uint_32);
extern void    _mcf5222_cache_disable(void);
extern void    _mcf5222_icache_invalidate(void);
extern void    _mcf5222_dcache_invalidate(void);

extern void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
extern void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

extern void    _mcf5222_mmu_init(uint_32);
extern uint_32 _mcf5222_mmu_enable(void);
extern uint_32 _mcf5222_mmu_disable(void);
extern uint_32 _mcf5222_mmu_add_region(pointer,uint_32,uint_32);

extern void    __psp_enable_acrs(uint_32_ptr);
extern void    __psp_clear_acrs(void);
extern void    __psp_dcache_flush(uint_32,uint_32,uint_32);

#endif //__ASM__

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

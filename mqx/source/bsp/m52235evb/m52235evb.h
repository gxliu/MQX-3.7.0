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
* $FileName: m52235evb.h$
* $Version : 3.6.30.0$
* $Date    : Dec-3-2010$
*
* Comments:
*
*   This include file is used to provide information needed by
*   an application program using the kernel running on the
*   Freescale M52235EVB Evaluation board.
*
*END************************************************************************/

#ifndef _m52235evb_h_
#define _m52235evb_h_ 1

/*
** Get MQX configuration (also gets user_config.h)
*/
#include "mqx_cnfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------
**                  HARDWARE INITIALIZATION DEFINITIONS
*/

/*
** Define the board type
*/
#define BSP_M52235EVB 1

/*
** PROCESSOR MEMORY BOUNDS
*/
extern uchar __INTERNAL_SRAM_BASE[],  __INTERNAL_SRAM_SIZE[];
extern uchar __INTERNAL_FLASH_BASE[], __INTERNAL_FLASH_SIZE[];
extern uchar __IPSBAR[];

#define BSP_IPSBAR                  ((uint_32)__IPSBAR)
#define BSP_INTERNAL_SRAM_BASE      ((pointer)__INTERNAL_SRAM_BASE)
#define BSP_INTERNAL_SRAM_SIZE      ((uint_32)__INTERNAL_SRAM_SIZE)
#define BSP_INTERNAL_FLASH_BASE     ((pointer)__INTERNAL_FLASH_BASE)
#define BSP_INTERNAL_FLASH_SIZE     ((uint_32)__INTERNAL_FLASH_SIZE)

#define MCF_FBCS_CSMR_BAM_64K                (0)

/*
** The timer MQX uses
*/
#define BSP_FIRST_TIMER                               (0) /* PIT0 */
#define BSP_LAST_TIMER                                (1) /* PIT1 */
#define BSP_TIMER                                     BSP_FIRST_TIMER
#define BSP_ADC_TIMER                                 BSP_LAST_TIMER

/*
** Core Watchdog Control Register (CWCR)
*/
#define BSP_WATCHDOG_DISABLED   0
#define BSP_WATCHDOG_RESET  1
#define BSP_WATCHDOG_INTERRUPT  2
#define BSP_WATCHDOG_DELAY  7 /* watchdog timing delay = 2^31 * bus clock frq */
#define BSP_WATCHDOG_INITIALIZATION BSP_WATCHDOG_INTERRUPT

/*
** The timer interrupt level and vector.
*/
#define BSP_PIT0_INT_LEVEL                            (2)
#define BSP_PIT0_INT_SUBLEVEL                         (4)
#define BSP_PIT1_INT_LEVEL                            (2)
#define BSP_PIT1_INT_SUBLEVEL                         (3)
#define BSP_PIT0_INT_VECTOR                           (MCF5223_INT_PIT0)
#define BSP_PIT1_INT_VECTOR                           (MCF5223_INT_PIT1)

#define BSP_TIMER_INTERRUPT_LEVEL                     (BSP_PIT0_INT_LEVEL)
#define BSP_TIMER_INTERRUPT_SUBLEVEL                  (BSP_PIT0_INT_SUBLEVEL)
#define BSP_TIMER_INTERRUPT_VECTOR                    (BSP_PIT0_INT_VECTOR)

#define BSP_ADC_TIMER_INTERRUPT_LEVEL                 (BSP_PIT1_INT_LEVEL)
#define BSP_ADC_TIMER_INTERRUPT_SUBLEVEL              (BSP_PIT1_INT_SUBLEVEL)
#define BSP_ADC_TIMER_INTERRUPT_VECTOR                (BSP_PIT1_INT_VECTOR)

#define BSP_ADC_INTERRUPT_LEVEL                       (BSP_ADC_TIMER_INTERRUPT_LEVEL + 1) /* cannot be interrupted by timer */
#define BSP_ADC_INTERRUPT_SUBLEVEL                    (2)
#define BSP_ADC_INTERRUPT_VECTOR                      (MCF5223_INT_ADC_ADCA)

/*
** The clock tick rate in number of ticks per second
*/
#ifndef BSP_ALARM_FREQUENCY
#define BSP_ALARM_FREQUENCY                           (200)
#endif

/*
** Old clock rate definition in milliseconds per tick for compatibility
*/
#define BSP_ALARM_RESOLUTION                          (1000 / BSP_ALARM_FREQUENCY)

/*
** CLKIN speed
*/
#define BSP_SYSTEM_CLOCK                              (60000000L)
#define BSP_BUS_CLOCK                                 (BSP_SYSTEM_CLOCK/2)

/*
** System Bus Clock Info
*/
#define SYSTEM_CLOCK                    (BSP_SYSTEM_CLOCK/1000000)       /* system bus frequency in MHz */
#define SYSTEM_CLK_PERIOD               (1000000000/(BSP_SYSTEM_CLOCK))  /* system bus period in ns */


/*
** The RTC interrupt level and vector.
*/
#define BSP_RTC_INT_LEVEL                         (7)
#define BSP_RTC_INT_SUBLEVEL                      (7)

/*
** The I2C stuff.
*/
#define BSP_I2C_CLOCK                                 (BSP_BUS_CLOCK)
#define BSP_I2C0_ADDRESS                              (0x6E)
#define BSP_I2C0_BAUD_RATE                            (100000)
#define BSP_I2C0_MODE                                 (I2C_MODE_MASTER)
#define BSP_I2C0_INT_LEVEL                            (1)
#define BSP_I2C0_INT_SUBLEVEL                         (0)
#define BSP_I2C0_RX_BUFFER_SIZE                       (64)
#define BSP_I2C0_TX_BUFFER_SIZE                       (64)

/*
** The SPI settings.
*/
#define BSP_QSPI_RX_BUFFER_SIZE                       (32)
#define BSP_QSPI_TX_BUFFER_SIZE                       (32)
#define BSP_QSPI_BAUDRATE                             (1000000)
#define BSP_QSPI_INT_LEVEL                            (4)
#define BSP_QSPI_INT_SUBLEVEL                         (0)

/*
** The ethernet PHY device number 0..31
*/
#ifndef BSP_ENET0_PHY_ADDR
#define BSP_ENET0_PHY_ADDR                                  1
#endif

/*
** PHY MII Speed (MDC - Management Data Clock)
*/
#define BSP_ENET0_PHY_MII_SPEED                             (2500000L)



/*
** GPIO board specifications
*/
#define BSP_LED1    (GPIO_PORT_TC | GPIO_PIN0)
#define BSP_LED2    (GPIO_PORT_TC | GPIO_PIN1)
#define BSP_LED3    (GPIO_PORT_TC | GPIO_PIN2)
#define BSP_LED4    (GPIO_PORT_TC | GPIO_PIN3)
#define BSP_SW1     (GPIO_PORT_NQ | GPIO_PIN4)
#define BSP_SW2     (GPIO_PORT_GP | GPIO_PIN3)
#define BSP_SW3     (GPIO_PORT_NQ | GPIO_PIN1)

/* definitions for user applications */
#define BSP_BUTTON1   BSP_SW1
#define BSP_BUTTON2   BSP_SW2
#define BSP_BUTTON3   BSP_SW3

/*
** ADC channels
*/
#define BSP_ADC_CH_POT      (ADC_SOURCE_AN0)

/********************************************************************/

/*
** Define the location of the hardware interrupt vector table
*/
extern uchar __VECTOR_TABLE_ROM_START[]; // defined in linker command file
extern uchar __VECTOR_TABLE_RAM_START[]; // defined in linker command file

#if MQX_ROM_VECTORS
    #define BSP_INTERRUPT_VECTOR_TABLE                    ((uint_32)__VECTOR_TABLE_ROM_START)
#else
    #define BSP_INTERRUPT_VECTOR_TABLE                    ((uint_32)__VECTOR_TABLE_RAM_START)
#endif

/*
** UART interrupt levels and vectors
*/

#define BSP_UART0_INT_LEVEL                           (5)
#define BSP_UART0_INT_SUBLEVEL                        (3)
#define BSP_UART1_INT_LEVEL                           (5)
#define BSP_UART1_INT_SUBLEVEL                        (2)
#define BSP_UART2_INT_LEVEL                           (5)
#define BSP_UART2_INT_SUBLEVEL                        (1)
#define BSP_UART0_INT_VECTOR                          (MCF5223_INT_UART0)
#define BSP_UART1_INT_VECTOR                          (MCF5223_INT_UART1)
#define BSP_UART2_INT_VECTOR                          (MCF5223_INT_UART2)

/* EPORT interrupts levels
** Note:
** EPORT interrupt sublevel (or priority within level) is hardware-wired to midpoint,
** EPORT interrupt level is hardware-wired to the values below.
** DON'T CHANGE THESE CONSTANTS AS IT'S POINTLESS.
*/ 
#define BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT          (3) /* in fact, it is value between 3 and 4 */
#define BSP_EPORT0_EPF1_INT_LEVEL                     (1)
#define BSP_EPORT0_EPF1_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT0_EPF2_INT_LEVEL                     (2)
#define BSP_EPORT0_EPF2_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT0_EPF3_INT_LEVEL                     (3)
#define BSP_EPORT0_EPF3_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT0_EPF4_INT_LEVEL                     (4)
#define BSP_EPORT0_EPF4_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT0_EPF5_INT_LEVEL                     (5)
#define BSP_EPORT0_EPF5_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT0_EPF6_INT_LEVEL                     (6)
#define BSP_EPORT0_EPF6_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT0_EPF7_INT_LEVEL                     (7)
#define BSP_EPORT0_EPF7_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT1_EPF0_INT_LEVEL                     (0)
#define BSP_EPORT1_EPF0_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT1_EPF1_INT_LEVEL                     (1)
#define BSP_EPORT1_EPF1_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT1_EPF2_INT_LEVEL                     (2)
#define BSP_EPORT1_EPF2_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT1_EPF3_INT_LEVEL                     (3)
#define BSP_EPORT1_EPF3_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT1_EPF4_INT_LEVEL                     (4)
#define BSP_EPORT1_EPF4_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT1_EPF5_INT_LEVEL                     (5)
#define BSP_EPORT1_EPF5_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT1_EPF6_INT_LEVEL                     (6)
#define BSP_EPORT1_EPF6_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)
#define BSP_EPORT1_EPF7_INT_LEVEL                     (7)
#define BSP_EPORT1_EPF7_INT_SUBLEVEL                  (BSP_EPORT_EPFX_INT_SUBLEVEL_MIDPOINT)

/*
** Define the range of interrupts for which the application can install
** isrs.
*/ 
#ifndef BSP_FIRST_INTERRUPT_VECTOR_USED                                                 
   #define BSP_FIRST_INTERRUPT_VECTOR_USED              MCF5223_INT_FIRST_EXTERNAL   
#endif

#ifndef BSP_LAST_INTERRUPT_VECTOR_USED                                                 
   #define BSP_LAST_INTERRUPT_VECTOR_USED               MCF5223_INT_EPORT1_EPF7
#endif

/*
** FEC interrupt levels and vectors
*/
#define BSP_ENET_DEVICE_COUNT                          MCF5XXX_FEC_DEVICE_COUNT



#define BSP_FEC_INT_TX_LEVEL                          (4)
#define BSP_FEC_INT_TX_SUBLEVEL                       (0)
#define BSP_FEC_INT_RX_LEVEL                          (3)
#define BSP_FEC_INT_RX_SUBLEVEL                       (0)


#define BSP_DEFAULT_ENET_DEVICE  0
#define BSP_DEFAULT_ENET_OUI     { 0x00, 0x00, 0x5E, 0, 0, 0 }
#ifndef BSPCFG_RX_RING_LEN
  #define BSPCFG_RX_RING_LEN             3 // Number of receive BD's
#endif

#ifndef BSPCFG_TX_RING_LEN
  #define BSPCFG_TX_RING_LEN             3 // Number of transmit BD's
#endif


#ifndef BSPCFG_ENABLE_ENET_MULTICAST
   #define BSPCFG_ENABLE_ENET_MULTICAST  1
#endif

#ifndef BSPCFG_ENABLE_ENET_STATS
   #define BSPCFG_ENABLE_ENET_STATS  1
#endif


#ifndef BSPCFG_ENET_RESTORE
   #define BSPCFG_ENET_RESTORE  1
#endif


#ifndef BSPCFG_ENABLE_CPP
   #define BSPCFG_ENABLE_CPP    0
#endif

/*----------------------------------------------------------------------
**                  IO DEVICE DRIVERS CONFIGURATION
*/

#ifndef BSPCFG_ENABLE_IO_SUBSYSTEM
   #define BSPCFG_ENABLE_IO_SUBSYSTEM  1
#endif

/* polled TTY device (UART0) */
#ifndef BSPCFG_ENABLE_TTYA
#define BSPCFG_ENABLE_TTYA  1
#endif

/* polled TTY device (UART1) */
#ifndef BSPCFG_ENABLE_TTYB
#define BSPCFG_ENABLE_TTYB  1
#endif

/* polled TTY device (UART2) */
#ifndef BSPCFG_ENABLE_TTYC
#define BSPCFG_ENABLE_TTYC  0
#endif

/* interrupt-driven TTY device (UART0) */
#ifndef BSPCFG_ENABLE_ITTYA
#define BSPCFG_ENABLE_ITTYA 0
#endif

/* interrupt-driven TTY device (UART1) */
#ifndef BSPCFG_ENABLE_ITTYB
#define BSPCFG_ENABLE_ITTYB 1
#endif

/* interrupt-driven TTY device (UART2) */
#ifndef BSPCFG_ENABLE_ITTYC
#define BSPCFG_ENABLE_ITTYC 0
#endif

/* TTY device HW signals (UART0) */
#ifndef BSPCFG_ENABLE_TTYA_HW_SIGNALS
#define BSPCFG_ENABLE_TTYA_HW_SIGNALS 0
#endif

/* TTY device HW signals (UART1) */
#ifndef BSPCFG_ENABLE_TTYB_HW_SIGNALS
#define BSPCFG_ENABLE_TTYB_HW_SIGNALS 0
#endif

/* TTY device HW signals (UART2) */
#ifndef BSPCFG_ENABLE_TTYC_HW_SIGNALS
#define BSPCFG_ENABLE_TTYC_HW_SIGNALS 0
#endif

/* TTYA and ITTYA baud rate */
#ifndef BSPCFG_UART0_BAUD_RATE
#define BSPCFG_UART0_BAUD_RATE 115200
#endif

/* TTYB and ITTYB baud rate */
#ifndef BSPCFG_UART1_BAUD_RATE
#define BSPCFG_UART1_BAUD_RATE 115200
#endif

/* TTYC and ITTYC baud rate */
#ifndef BSPCFG_UART2_BAUD_RATE
#define BSPCFG_UART2_BAUD_RATE 115200
#endif

/* TTYA and ITTYA buffer size */
#ifndef BSPCFG_UART0_QUEUE_SIZE
#define BSPCFG_UART0_QUEUE_SIZE 64
#endif

/* TTYB and ITTYB buffer size */
#ifndef BSPCFG_UART1_QUEUE_SIZE
#define BSPCFG_UART1_QUEUE_SIZE 64
#endif

/* TTYC and ITTYC buffer size */
#ifndef BSPCFG_UART2_QUEUE_SIZE
#define BSPCFG_UART2_QUEUE_SIZE 64
#endif

/* polled I2C0 device */
#ifndef BSPCFG_ENABLE_I2C0
#define BSPCFG_ENABLE_I2C0 1
#endif

/* int I2C0 device */
#ifndef BSPCFG_ENABLE_II2C0
#define BSPCFG_ENABLE_II2C0 0
#endif

/* polled SPI */
#ifndef BSPCFG_ENABLE_SPI0
#define BSPCFG_ENABLE_SPI0 0
#endif

/* int SPI */
#ifndef BSPCFG_ENABLE_ISPI0
#define BSPCFG_ENABLE_ISPI0 0
#endif

/* RTC device */
#ifndef BSPCFG_ENABLE_RTCDEV
#define BSPCFG_ENABLE_RTCDEV  1
#endif

/* CFM */
#ifndef BSPCFG_ENABLE_FLASHX
#define BSPCFG_ENABLE_FLASHX  1 
#endif

/*----------------------------------------------------------------------
**                  DEFAULT MQX INITIALIZATION DEFINITIONS
*/

/* Defined in link.xxx */
extern uchar __KERNEL_DATA_START[];
extern uchar __KERNEL_DATA_END[];
extern uchar __DEFAULT_PROCESSOR_NUMBER[];
extern uchar __DEFAULT_INTERRUPT_STACK_SIZE[];

#define BSP_DEFAULT_START_OF_KERNEL_MEMORY            ((pointer)__KERNEL_DATA_START)
#define BSP_DEFAULT_END_OF_KERNEL_MEMORY              ((pointer)__KERNEL_DATA_END)
#define BSP_DEFAULT_PROCESSOR_NUMBER                  ((uint_32)__DEFAULT_PROCESSOR_NUMBER)

#ifndef BSP_DEFAULT_INTERRUPT_STACK_SIZE
   #define BSP_DEFAULT_INTERRUPT_STACK_SIZE              ((uint_32)__DEFAULT_INTERRUPT_STACK_SIZE)
#endif

#ifndef BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX
   #define BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX  (6L)
#endif

#ifndef BSP_DEFAULT_MAX_MSGPOOLS
   #define BSP_DEFAULT_MAX_MSGPOOLS                      (2L)
#endif

#ifndef BSP_DEFAULT_MAX_MSGQS
   #define BSP_DEFAULT_MAX_MSGQS                         (16L)
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL
   #if BSPCFG_ENABLE_TTYA
      #define BSP_DEFAULT_IO_CHANNEL                        "ttya:"
      #define BSP_DEFAULT_IO_CHANNEL_DEFINED
   #else
      #define BSP_DEFAULT_IO_CHANNEL                        NULL
   #endif
#endif

#ifndef BSP_DEFAULT_IO_OPEN_MODE
   #define BSP_DEFAULT_IO_OPEN_MODE                      (pointer) (IO_SERIAL_XON_XOFF | IO_SERIAL_TRANSLATION | IO_SERIAL_ECHO)
#endif

/* 
** CFM internal flash
*/
#if BSPCFG_ENABLE_FLASHX
    #ifndef BSPCFG_FLASHX_SIZE
    #define BSPCFG_FLASHX_SIZE      0x4000
    #endif
#else
    #undef  BSPCFG_FLASHX_SIZE
    #define BSPCFG_FLASHX_SIZE      0x0
#endif


#ifdef __cplusplus
}
#endif

#endif
/* EOF */

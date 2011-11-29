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
* $FileName: twrmcf54418.h$
* $Version : 3.6.30.0$
* $Date    : Feb-10-2011$
*
* Comments:
*
*   This include file is used to provide information needed by
*   an application program using the kernel running 
*   on the Freescale TWR MCF5441X Evaluation board.
*
*END************************************************************************/

#ifndef __m54418_h_
    #define __m54418_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
**                  HARDWARE INITIALIZATION DEFINITIONS
*/

/*
** Define the board type
*/
#define BSP_TWRMCF54418                     1

/* defined this macro if PEG is used with PCI */
#define BSP_PEG_PCI_ENABLE                  1

/*
** PROCESSOR MEMORY BOUNDS
*/
extern uchar __EXTERNAL_SDRAM_BASE[],       __EXTERNAL_SDRAM_SIZE[];
extern uchar __INTERNAL_SRAM_BASE[],        __INTERNAL_SRAM_SIZE[];
extern uchar __EXTERNAL_MRAM_BASE[],        __EXTERNAL_MRAM_SIZE[];
extern uchar __EXTERNAL_MRAM_ROM_BASE[],    __EXTERNAL_MRAM_ROM_SIZE[];
extern uchar __EXTERNAL_MRAM_RAM_BASE[],    __EXTERNAL_MRAM_RAM_SIZE[];

extern uchar __VECTOR_TABLE_START[];

extern uchar __CACHED_CODE_START[],         __CACHED_CODE_END[];
extern uchar __CACHED_DATA_START[],         __CACHED_DATA_END[];
extern uchar __UNCACHED_DATA_START[],       __UNCACHED_DATA_END[];

extern uchar __VECTOR_TABLE_RAM_START[];
extern uchar __VECTOR_TABLE_ROM_START[];

#define BSP_RAM_BASE                        (__EXTERNAL_SDRAM_BASE)
#define BSP_RAM_SIZE                        ((uint_32)__EXTERNAL_SDRAM_SIZE)
#define BSP_INTERNAL_SRAM0                  ((pointer)__INTERNAL_SRAM_BASE)
#define BSP_INTERNAL_SRAM0_SIZE             (32 * 1024)

#define BSP_FLASH_BASE                      ((pointer)0x0) /* block #0 */
#define BSP_FLASH_SIZE                      (0x400000)
#define BSP_FLASH_WIDTH                     (16)
#define BSP_FLASH_DEVICES                   (1)
#define BSP_VIRTUAL_PAGE_SIZE               (512)
#define BSP_ECC_SIZE                        (4) /* 4-error correction bits (8 ECC bytes) */

#define BSP_EXTERNAL_MRAM_BASE              ((pointer)__EXTERNAL_MRAM_BASE)
#define BSP_EXTERNAL_MRAM_SIZE              ((uint_32)__EXTERNAL_MRAM_SIZE)
#define BSP_EXTERNAL_MRAM_ROM_BASE          ((pointer)__EXTERNAL_MRAM_ROM_BASE)
#define BSP_EXTERNAL_MRAM_ROM_SIZE          ((uint_32)__EXTERNAL_MRAM_ROM_SIZE)
#define BSP_EXTERNAL_MRAM_RAM_BASE          ((pointer)__EXTERNAL_MRAM_RAM_BASE)
#define BSP_EXTERNAL_MRAM_RAM_SIZE          ((uint_32)__EXTERNAL_MRAM_RAM_SIZE)

/* Compact Flash card base address */
#define BSP_CFCARD_BASE                     ((pointer)0x30010000)

#define BSP_DMA_CODE_BASE                   (__DMA_CODE_START)

extern uchar __INTERRUPT_STACK_BASE[];
#define BSP_INTERRUPT_STACK_LOCATION        (__INTERRUPT_STACK_BASE)

/*
** Define the location of the hardware interrupt vector table
*/
#define BSP_BOOT_INTERRUPT_VECTOR_TABLE     ((uint_32)__VECTOR_TABLE_START)
#define BSP_RAM_INTERRUPT_VECTOR_TABLE      ((uint_32)__VECTOR_TABLE_RAM_START)

/*-----------------------------------------------------------------------------
**                  BSP Timers and Scheduling
*/

/*
** The timer interrupt level and vector.
*/
#define BSP_PIT0_INT_LEVEL                  (3)
#define BSP_PIT0_INT_VECTOR                 (MCF5441_INT_PIT0)

#define BSP_PIT1_INT_LEVEL                  (3)
#define BSP_PIT1_INT_VECTOR                 (MCF5441_INT_PIT1)

#define BSP_PIT2_INT_LEVEL                  (3)
#define BSP_PIT2_INT_VECTOR                 (MCF5441_INT_PIT2)

#define BSP_PIT3_INT_LEVEL                  (3)
#define BSP_PIT3_INT_VECTOR                 (MCF5441_INT_PIT3)

#define BSP_ADC_TIMER_INTERRUPT_LEVEL       (BSP_PIT1_INT_LEVEL)
#define BSP_ADC_TIMER_INTERRUPT_VECTOR      (BSP_PIT1_INT_VECTOR)

/* cannot be interrupted by timer */
#define BSP_ADC_INTERRUPT_LEVEL             (BSP_ADC_TIMER_INTERRUPT_LEVEL + 1) 
#define BSP_ADC_INTERRUPT_VECTOR            (MCF5441_INT_ADC_SR_EOSI0)

/*
** The timer MQX uses
*/
#define BSP_FIRST_TIMER                     (0) /* PIT0 */
#define BSP_LAST_TIMER                      (1) /* PIT1 */
#define BSP_TIMER                           BSP_FIRST_TIMER
#define BSP_ADC_TIMER                       BSP_LAST_TIMER

#define BSP_TIMER_INTERRUPT_LEVEL           (BSP_PIT0_INT_LEVEL)
#define BSP_TIMER_INTERRUPT_VECTOR          (BSP_PIT0_INT_VECTOR)

/*
** The clock tick rate in number of ticks per second
*/
#ifndef BSP_ALARM_FREQUENCY
    #define BSP_ALARM_FREQUENCY             (200)
#endif

/*
** Old clock rate definition in milliseconds per tick for compatibility
*/
#define BSP_ALARM_RESOLUTION                (1000 / BSP_ALARM_FREQUENCY)

#define BSP_ADC_CH_POT                      (ADC_SOURCE_AN4)

/*-----------------------------------------------------------------------------
**                  USB Configuration
*/

#define USBCFG_MAX_DRIVERS                  (2)

enum {
    USBCFG_CONTROLLER_OTG = 0,
    USBCFG_CONTROLLER_HOST
};

#define USBCFG_CONNECTOR_STANDARD           0
#define USBCFG_CONNECTOR_ULPI               1

#define USBCFG_USBOTG_CONNECTOR             USBCFG_CONNECTOR_ULPI
#define USBCFG_USBHOST_CONNECTOR            USBCFG_CONNECTOR_STANDARD

#if USBCFG_USBOTG_CONNECTOR != USBCFG_CONNECTOR_ULPI
    #error USB OTG peripheral on tower board has the physical connection only to ULPI
#endif
#if USBCFG_USBHOST_CONNECTOR != USBCFG_CONNECTOR_STANDARD
    #error USB HOST peripheral on tower board has the physical connection only to OCT terminals
#endif

#define USBCFG_DEFAULT_HOST_CONTROLLER      USBCFG_CONTROLLER_OTG
#define USBCFG_DEFAULT_DEVICE_CONTROLLER    USBCFG_CONTROLLER_OTG

#define USBCFG_EHCI                         1

/*-----------------------------------------------------------------------------
**                      Ethernet Info
*/
#define BSP_ENET_DEVICE_COUNT               MACNET_DEVICE_COUNT

/*
** MACNET interrupt levels and vectors
*/
#define BSP_MACNET0_INT_TX_LEVEL           (4)
#define BSP_MACNET0_INT_RX_LEVEL           (3)

#define BSP_MACNET1_INT_TX_LEVEL           (4)
#define BSP_MACNET1_INT_RX_LEVEL           (3)

#define BSP_DEFAULT_ENET_DEVICE             0
#define BSP_DEFAULT_ENET_OUI                { 0x00, 0x00, 0x5E, 0, 0, 0 }

/*
** The ethernet PHY device number 0..31
*/
#ifndef BSP_ENET0_PHY_ADDR
#define BSP_ENET0_PHY_ADDR                  0
#endif

#ifndef BSP_ENET1_PHY_ADDR
#define BSP_ENET1_PHY_ADDR                  1
#endif

/*
** PHY MII Speed (MDC - Management Data Clock)
*/
#define BSP_ENET0_PHY_MII_SPEED             (5000000L)
#define BSP_ENET1_PHY_MII_SPEED             (5000000L)

/*-----------------------------------------------------------------------------
**                      System Clocks Info
*/

extern uchar __SYSCLK[], __SYSCLKM[];

/* CLKIN speed */
#define BSP_SYSTEM_CLOCK                    ((uint_32)250000000)
#define BSP_BUS_CLOCK                       ((uint_32)(BSP_SYSTEM_CLOCK / 2))

/* System bus frequency in MHz */
#define SYSTEM_CLOCK                        (BSP_SYSTEM_CLOCK / 1000000)
/* system bus period in ns */
#define SYSTEM_CLK_PERIOD                   (1000000000 / (BSP_SYSTEM_CLOCK))   

/*
** UART interrupt levels and vectors
*/
#define BSP_UART0_INT_LEVEL                 (5)
#define BSP_UART0_INT_VECTOR                (MCF5441_INT_UART0)
#define BSP_UART2_INT_LEVEL                 (5)
#define BSP_UART2_INT_VECTOR                (MCF5441_INT_UART2)
#define BSP_UART4_INT_LEVEL                 (5)
#define BSP_UART4_INT_VECTOR                (MCF5441_INT_UART4)
#define BSP_UART5_INT_LEVEL                 (5)
#define BSP_UART5_INT_VECTOR                (MCF5441_INT_UART5)
#define BSP_UART6_INT_LEVEL                 (5)
#define BSP_UART6_INT_VECTOR                (MCF5441_INT_UART6)

/*
** The RTC interrupt level and vector.
*/
#define BSP_RTC_INT_LEVEL                   (5)
#define BSP_RTC_INT_VECTOR                  (MCF5441_INT_Robust_RTC)

/*
** The I2C stuff.
*/
#define BSP_I2C_CLOCK                       (BSP_BUS_CLOCK)
#define BSP_I2C0_ADDRESS                    (0x6E)
#define BSP_I2C0_BAUD_RATE                  (100000)
#define BSP_I2C0_MODE                       (I2C_MODE_MASTER)
#define BSP_I2C0_INT_LEVEL                  (1)
#define BSP_I2C0_RX_BUFFER_SIZE             (64)
#define BSP_I2C0_TX_BUFFER_SIZE             (64)

#define BSP_I2C5_ADDRESS                    (0x6F)
#define BSP_I2C5_BAUD_RATE                  (100000)
#define BSP_I2C5_MODE                       (I2C_MODE_MASTER)
#define BSP_I2C5_INT_LEVEL                  (1)
#define BSP_I2C5_RX_BUFFER_SIZE             (64)
#define BSP_I2C5_TX_BUFFER_SIZE             (64)
                                            
/*
** The SPI settings.
*/
#define BSP_DSPI_RX_BUFFER_SIZE              (32)
#define BSP_DSPI_TX_BUFFER_SIZE              (32)
#define BSP_DSPI_BAUDRATE                    (1000000)
#define BSP_DSPI_INT_LEVEL                   (4)
                                             
/*                                           
** The SDCARD settings.
*/
#define BSP_SDCARD_ESDHC_CHANNEL            "esdhc:"
#define BSP_SDCARD_GPIO_DETECT              (GPIO_PORT_C | GPIO_PIN6)
#define BSP_SDCARD_GPIO_PROTECT             (GPIO_PORT_G | GPIO_PIN1)

/*
** Define the range of interrupts for which the application can install
** isrs.
*/
#ifndef BSP_FIRST_INTERRUPT_VECTOR_USED                                                 
    #define BSP_FIRST_INTERRUPT_VECTOR_USED MCF5441_INT_FIRST_EXTERNAL
#endif

#ifndef BSP_LAST_INTERRUPT_VECTOR_USED                                                 
    #define BSP_LAST_INTERRUPT_VECTOR_USED  MCF5441_INT_ENET1_EIR_PLR
#endif

/*
** ENET default settings
*/
#ifndef BSPCFG_RX_RING_LEN
    #define BSPCFG_RX_RING_LEN              20 /* Number of receive BD's */
#endif

#ifndef BSPCFG_TX_RING_LEN
    #define BSPCFG_TX_RING_LEN              20 /* Number of transmit BD's */
#endif


#ifndef BSPCFG_ENABLE_ENET_MULTICAST
    #define BSPCFG_ENABLE_ENET_MULTICAST    1
#endif

#ifndef BSPCFG_ENABLE_ENET_STATS
    #define BSPCFG_ENABLE_ENET_STATS        1
#endif


#ifndef BSPCFG_ENET_RESTORE
    #define BSPCFG_ENET_RESTORE             1
#endif


#ifndef BSPCFG_ENABLE_CPP
    #define BSPCFG_ENABLE_CPP               0
#endif

/*
** GPIO board specifications
*/
#define BSP_LED1                            (GPIO_PORT_G | GPIO_PIN0)
#define BSP_LED2                            (GPIO_PORT_G | GPIO_PIN1)
#define BSP_LED3                            (GPIO_PORT_G | GPIO_PIN2)
#define BSP_LED4                            (GPIO_PORT_G | GPIO_PIN3)

#define BSP_SW3                             (GPIO_PORT_C | GPIO_PIN1)
#define BSP_SW5                             (GPIO_PORT_C | GPIO_PIN2)
#define BSP_BUTTON1                         BSP_SW3
#define BSP_BUTTON2                         BSP_SW5


/* EPORT interrupts levels
** Note:
** EPORT interrupt sublevel (or priority within level) is hardware-wired to midpoint,
** EPORT interrupt level is hardware-wired to the values below.
** DON'T CHANGE THESE CONSTANTS AS IT'S POINTLESS.
*/ 
#define BSP_EPORT_EPF1_INT_LEVEL                     (1)
#define BSP_EPORT_EPF2_INT_LEVEL                     (2)
#define BSP_EPORT_EPF3_INT_LEVEL                     (3)
#define BSP_EPORT_EPF4_INT_LEVEL                     (4)
#define BSP_EPORT_EPF5_INT_LEVEL                     (5)
#define BSP_EPORT_EPF6_INT_LEVEL                     (6)
#define BSP_EPORT_EPF7_INT_LEVEL                     (7)

/*----------------------------------------------------------------------
**                  IO DEVICE DRIVERS CONFIGURATION
*/

#ifndef BSPCFG_ENABLE_IO_SUBSYSTEM
    #define BSPCFG_ENABLE_IO_SUBSYSTEM      1
#endif

/* polled TTY device (UART0) */
#ifndef BSPCFG_ENABLE_TTYA
    #define BSPCFG_ENABLE_TTYA              1
#endif

/* polled TTY device (UART2) */
#ifndef BSPCFG_ENABLE_TTYB
    #define BSPCFG_ENABLE_TTYB              0
#endif

/* polled TTY device (UART4) */
#ifndef BSPCFG_ENABLE_TTYC
    #define BSPCFG_ENABLE_TTYC              0
#endif

/* polled TTY device (UART5) */
#ifndef BSPCFG_ENABLE_TTYD
    #define BSPCFG_ENABLE_TTYD              1
#endif

/* polled TTY device (UART6) */
#ifndef BSPCFG_ENABLE_TTYE
    #define BSPCFG_ENABLE_TTYE              0
#endif

/* interrupt-driven TTY device (UART0) */
#ifndef BSPCFG_ENABLE_ITTYA
    #define BSPCFG_ENABLE_ITTYA             1
#endif

/* interrupt-driven TTY device (UART2) */
#ifndef BSPCFG_ENABLE_ITTYB
    #define BSPCFG_ENABLE_ITTYB             0
#endif

/* interrupt-driven TTY device (UART4) */
#ifndef BSPCFG_ENABLE_ITTYC
    #define BSPCFG_ENABLE_ITTYC             0
#endif

/* interrupt-driven TTY device (UART5) */
#ifndef BSPCFG_ENABLE_ITTYD
    #define BSPCFG_ENABLE_ITTYD             1
#endif

/* interrupt-driven TTY device (UART6) */
#ifndef BSPCFG_ENABLE_ITTYE
    #define BSPCFG_ENABLE_ITTYE             0
#endif

/* TTY device HW signals (UART0) */
#ifndef BSPCFG_ENABLE_TTYA_HW_SIGNALS
#define BSPCFG_ENABLE_TTYA_HW_SIGNALS 0
#endif

/* TTY device HW signals (UART1) */
#ifndef BSPCFG_ENABLE_TTYB_HW_SIGNALS
#define BSPCFG_ENABLE_TTYB_HW_SIGNALS 0
#endif

/* TTYA and ITTYA baud rate */
#ifndef BSPCFG_UART0_BAUD_RATE
    #define BSPCFG_UART0_BAUD_RATE          115200
#endif

/* TTYB and ITTYB baud rate */
#ifndef BSPCFG_UART2_BAUD_RATE
    #define BSPCFG_UART2_BAUD_RATE          115200
#endif

/* TTYC and ITTYC baud rate */
#ifndef BSPCFG_UART4_BAUD_RATE
    #define BSPCFG_UART4_BAUD_RATE          115200
#endif

/* TTYD and ITTYD baud rate */
#ifndef BSPCFG_UART5_BAUD_RATE
    #define BSPCFG_UART5_BAUD_RATE          115200
#endif

/* TTYE and ITTYE baud rate */
#ifndef BSPCFG_UART6_BAUD_RATE
    #define BSPCFG_UART6_BAUD_RATE          115200
#endif


/* TTYA and ITTYA buffer size */
#ifndef BSPCFG_UART0_QUEUE_SIZE
    #define BSPCFG_UART0_QUEUE_SIZE         64
#endif

/* TTYB and ITTYB buffer size */
#ifndef BSPCFG_UART2_QUEUE_SIZE
    #define BSPCFG_UART2_QUEUE_SIZE         64
#endif

/* TTYC and ITTYC buffer size */
#ifndef BSPCFG_UART4_QUEUE_SIZE
    #define BSPCFG_UART4_QUEUE_SIZE         64
#endif

/* TTYD and ITTYD buffer size */
#ifndef BSPCFG_UART5_QUEUE_SIZE
    #define BSPCFG_UART5_QUEUE_SIZE         64
#endif

/* TTYE and ITTYE buffer size */
#ifndef BSPCFG_UART6_QUEUE_SIZE
    #define BSPCFG_UART6_QUEUE_SIZE         64
#endif


/* RTC device */
#ifndef BSPCFG_ENABLE_RTCDEV
    #define BSPCFG_ENABLE_RTCDEV            1   
#endif

/* polled I2C0 device */
#ifndef BSPCFG_ENABLE_I2C0
    #define BSPCFG_ENABLE_I2C0              1
#endif

/* int I2C0 device */
#ifndef BSPCFG_ENABLE_II2C0
    #define BSPCFG_ENABLE_II2C0             0
#endif

/* polled I2C1 device */
#ifndef BSPCFG_ENABLE_I2C5
    #define BSPCFG_ENABLE_I2C5              0
#endif

/* int I2C1 device */
#ifndef BSPCFG_ENABLE_II2C5
    #define BSPCFG_ENABLE_II2C5             0
#endif

/* polled SPI0 device */
#ifndef BSPCFG_ENABLE_SPI0
    #define BSPCFG_ENABLE_SPI0              1
#endif

/* interrupt SPI0 device */
#ifndef BSPCFG_ENABLE_ISPI0
    #define BSPCFG_ENABLE_ISPI0             0
#endif

/* polled SPI1 device */
#ifndef BSPCFG_ENABLE_SPI1
    #define BSPCFG_ENABLE_SPI1              0
#endif

/* interrupt SPI1 device */
#ifndef BSPCFG_ENABLE_ISPI1
    #define BSPCFG_ENABLE_ISPI1             0
#endif

/* NAND Flash */
#ifndef BSPCFG_ENABLE_NANDFLASH
    #define BSPCFG_ENABLE_NANDFLASH         1
#endif

/* PCFLASH device */
#ifndef BSPCFG_ENABLE_PCFLASH
    #define BSPCFG_ENABLE_PCFLASH           1
#endif

/* ESDHC device */
#ifndef BSPCFG_ENABLE_ESDHC
    #define BSPCFG_ENABLE_ESDHC             1
#endif

/*-----------------------------------------------------------------------------
**                  DEFAULT MQX INITIALIZATION DEFINITIONS
*/

/* Defined in link.xxx */
extern uchar __KERNEL_DATA_START[];
extern uchar __KERNEL_DATA_END[];
extern uchar __DEFAULT_PROCESSOR_NUMBER[];
extern uchar __DEFAULT_INTERRUPT_STACK_SIZE[];

#define BSP_DEFAULT_START_OF_KERNEL_MEMORY                  ((pointer)__KERNEL_DATA_START)
#define BSP_DEFAULT_END_OF_KERNEL_MEMORY                    ((pointer)__KERNEL_DATA_END)
#define BSP_DEFAULT_PROCESSOR_NUMBER                        ((uint_32)__DEFAULT_PROCESSOR_NUMBER)

#ifndef BSP_DEFAULT_INTERRUPT_STACK_SIZE
    #define BSP_DEFAULT_INTERRUPT_STACK_SIZE                ((uint_32)__DEFAULT_INTERRUPT_STACK_SIZE)
#endif

#ifndef BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX
    #define BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX    (6L)
#endif

#ifndef BSP_DEFAULT_MAX_MSGPOOLS
    #define BSP_DEFAULT_MAX_MSGPOOLS                        (16L)
#endif

#ifndef BSP_DEFAULT_MAX_MSGQS
    #define BSP_DEFAULT_MAX_MSGQS                           (128L)
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL
    #if BSPCFG_ENABLE_TTYD
        #define BSP_DEFAULT_IO_CHANNEL                      "ttyd:"
        #define BSP_DEFAULT_IO_CHANNEL_DEFINED
    #else
        #define BSP_DEFAULT_IO_CHANNEL                      NULL
    #endif
#endif

#ifndef BSP_DEFAULT_IO_OPEN_MODE
    #define BSP_DEFAULT_IO_OPEN_MODE                        (pointer)(IO_SERIAL_XON_XOFF    | \
                                                                      IO_SERIAL_TRANSLATION | \
                                                                      IO_SERIAL_ECHO)
#endif


#ifdef __cplusplus
}
#endif

#endif /* __m54418_h_ */
/* EOF */

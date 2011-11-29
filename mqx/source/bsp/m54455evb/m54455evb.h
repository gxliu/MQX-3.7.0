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
* $FileName: m54455evb.h$
* $Version : 3.7.30.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This include file is used to provide information needed by
*   an application program using the kernel running on the
*   MOTOROLA MCF5480 Evaluation board.
*   $Header:mclog548x.h, 12, 3/15/2007 12:23:44 PM, Jim Gard$
*   $NoKeywords$
*
*END************************************************************************/
#ifndef _m54455_h_
#define _m54455_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
**                  HARDWARE INITIALIZATION DEFINITIONS
*/

/*
** Define the board type
*/
#define BSP_M54455EVB           1

/* defined this macro if PEG is used with PCI */
#define BSP_PEG_PCI_ENABLE      1

/*
** PROCESSOR MEMORY BOUNDS
*/
extern uchar __EXTERNAL_SDRAM_BASE[], __EXTERNAL_SDRAM_SIZE[];
extern uchar __INTERNAL_SRAM_BASE[],  __INTERNAL_SRAM_SIZE[];
extern uchar __FLASH0_BASE[];
extern uchar __FLASH1_BASE[];
//extern uchar __DMA_CODE_START[];
extern uchar __VECTOR_TABLE_START[];

extern uchar __CACHED_CODE_START[], __CACHED_CODE_END[];
extern uchar __CACHED_DATA_START[], __CACHED_DATA_END[];
extern uchar __UNCACHED_DATA_START[], __UNCACHED_DATA_END[];

extern uchar __VECTOR_TABLE_RAM_START[];
extern uchar __VECTOR_TABLE_ROM_START[];

#define BSP_RAM_BASE                    (__EXTERNAL_SDRAM_BASE)
#define BSP_RAM_SIZE                    ((uint_32)__EXTERNAL_SDRAM_SIZE)
#define BSP_INTERNAL_SRAM0              ((pointer)__INTERNAL_SRAM_BASE)
#define BSP_INTERNAL_SRAM0_SIZE         (32 * 1024)

/*
** The board has the AT49BV040 part installed.
*/
#define BSP_FLASH0_BASE                 (__FLASH0_BASE)
#define BSP_FLASH0_WIDTH                (1)
#define BSP_FLASH0_DEVICES              (1)
#define BSP_BOOT_NUM_FLASH_BLOCKS       (1)
#define BSP_FLASH0_SIZE                 (512 * 1024)    /* 512kB */
#define BSP_FLASH0_BLOCK_SIZE           (BSP_FLASH0_SIZE / BSP_BOOT_NUM_FLASH_BLOCKS)

/*
** The board has the JS28F128J3D-75 part installed.
*/
#define BSP_FLASH1_BASE                 (__FLASH1_BASE)
#define BSP_FLASH1_WIDTH                (1)
#define BSP_FLASH1_DEVICES              (1)
#define BSP_USER_NUM_FLASH_BLOCKS       (128)
#define BSP_FLASH1_SIZE                 (16 * 1024 * 1024)  /* 16 Meg */
#define BSP_FLASH1_BLOCK_SIZE           (BSP_FLASH1_SIZE / BSP_USER_NUM_FLASH_BLOCKS)

#define BSP_DMA_CODE_BASE               (__DMA_CODE_START)

extern uchar __INTERRUPT_STACK_BASE[];
#define BSP_INTERRUPT_STACK_LOCATION    (__INTERRUPT_STACK_BASE)

/*
** Define the location of the hardware interrupt vector table
*/
#define BSP_BOOT_INTERRUPT_VECTOR_TABLE ((uint_32)__VECTOR_TABLE_START)
#define BSP_RAM_INTERRUPT_VECTOR_TABLE  ((uint_32)__VECTOR_TABLE_RAM_START)

/*-----------------------------------------------------------------------------
**                  BSP Timers and Scheduling
*/

/*
** The timer interrupt level and vector.
*/
#define BSP_PIT0_INT_LEVEL              (3)
#define BSP_PIT0_INT_VECTOR             (MCF5445_INT_PIT0)

#define BSP_PIT1_INT_LEVEL              (3)
#define BSP_PIT1_INT_VECTOR             (MCF5445_INT_PIT1)

#define BSP_PIT2_INT_LEVEL              (3)
#define BSP_PIT2_INT_VECTOR             (MCF5445_INT_PIT2)

#define BSP_PIT3_INT_LEVEL              (3)
#define BSP_PIT3_INT_VECTOR             (MCF5445_INT_PIT3)

/*
** The timer MQX uses
*/
#define BSP_FIRST_TIMER                               (0) /* PIT0 */
#define BSP_LAST_TIMER                                (1) /* PIT1 */
#define BSP_TIMER                                     BSP_FIRST_TIMER

#define BSP_TIMER_INTERRUPT_LEVEL                     (BSP_PIT0_INT_LEVEL)
#define BSP_TIMER_INTERRUPT_VECTOR                    (BSP_PIT0_INT_VECTOR)

/*
** The clock tick rate in number of ticks per second
*/
#ifndef BSP_ALARM_FREQUENCY
#define BSP_ALARM_FREQUENCY             (200)
#endif

/*
** Old clock rate definition in milliseconds per tick for compatibility
*/
#define BSP_ALARM_RESOLUTION            (1000 / BSP_ALARM_FREQUENCY)


/*-----------------------------------------------------------------------------
**                  USB Configuration
*/

#define USBCFG_CONNECTOR_STANDARD 0
#define USBCFG_CONNECTOR_ULPI     1

#define USBCFG_USBOTG_CONNECTOR   USBCFG_CONNECTOR_STANDARD

#define USBCFG_EHCI         1

/*-----------------------------------------------------------------------------
**                      Ethernet Info
*/
#define BSP_ENET_DEVICE_COUNT                          MCF5XXX_FEC_DEVICE_COUNT

/*
** FEC interrupt levels and vectors
*/
#define BSP_FEC0_INT_TX_LEVEL           (4)
#define BSP_FEC0_INT_RX_LEVEL           (3)

#define BSP_FEC1_INT_TX_LEVEL           (4)
#define BSP_FEC1_INT_RX_LEVEL           (3)

#define BSP_DEFAULT_ENET_DEVICE         0
#define BSP_DEFAULT_ENET_OUI            { 0x00, 0x00, 0x5E, 0, 0, 0 }

/*
** The ethernet PHY device number 0..31
*/
#ifndef BSP_ENET0_PHY_ADDR
#define BSP_ENET0_PHY_ADDR                      0
#endif

#ifndef BSP_ENET1_PHY_ADDR
#define BSP_ENET1_PHY_ADDR                      1
#endif

/*
** PHY MII Speed (MDC - Management Data Clock)
*/
#define BSP_ENET0_PHY_MII_SPEED                             (2500000L)
#define BSP_ENET1_PHY_MII_SPEED                             (2500000L)

/*-----------------------------------------------------------------------------
**                      System Clocks Info
*/

extern uchar __SYSCLK[], __SYSCLKM[];

// CLKIN speed
#define BSP_SYSTEM_CLOCK    ((uint_32)266000000)
#define BSP_BUS_CLOCK       ((uint_32)(BSP_SYSTEM_CLOCK / 2))

#define SYSTEM_CLOCK        (BSP_SYSTEM_CLOCK / 1000000)        // system bus frequency in MHz
#define SYSTEM_CLK_PERIOD   (1000000000 / (BSP_SYSTEM_CLOCK))   // system bus period in ns

/*
** UART interrupt levels and vectors
*/
#define BSP_UART0_INT_LEVEL             (5)
#define BSP_UART1_INT_LEVEL             (5)
#define BSP_UART2_INT_LEVEL             (5)
#define BSP_UART0_INT_VECTOR            (MCF5445_INT_UART0)
#define BSP_UART1_INT_VECTOR            (MCF5445_INT_UART1)
#define BSP_UART2_INT_VECTOR            (MCF5445_INT_UART2)

/*
** The RTC interrupt level and vector.
*/
#define BSP_RTC_INT_LEVEL               (4)
#define BSP_RTC_PRESCALER_GOCU          (0x0000)
#define BSP_RTC_PRESCALER_GOCL          (0x8000)

/*
** The I2C stuff.
*/
#define BSP_I2C_CLOCK                   (BSP_BUS_CLOCK)
#define BSP_I2C0_ADDRESS                (0x6E)
#define BSP_I2C0_BAUD_RATE              (100000)
#define BSP_I2C0_MODE                   (I2C_MODE_MASTER)
#define BSP_I2C0_INT_LEVEL              (1)
#define BSP_I2C0_RX_BUFFER_SIZE         (64)
#define BSP_I2C0_TX_BUFFER_SIZE         (64)

/*
** The SPI settings.
*/
#define BSP_DSPI_RX_BUFFER_SIZE          (32)
#define BSP_DSPI_TX_BUFFER_SIZE          (32)
#define BSP_DSPI_BAUDRATE                (1000000)
#define BSP_DSPI_INT_LEVEL               (4)

/*
** Define the range of interrupts for which the application can install
** isrs.
*/
#ifndef BSP_FIRST_INTERRUPT_VECTOR_USED                                                 
    #define BSP_FIRST_INTERRUPT_VECTOR_USED             MCF5445_INT_FIRST_EXTERNAL
#endif

#ifndef BSP_LAST_INTERRUPT_VECTOR_USED                                                 
    #define BSP_LAST_INTERRUPT_VECTOR_USED              MCF5445_INT_PLL
#endif

/*
** ENET default settings
*/
#ifndef BSPCFG_RX_RING_LEN
  #define BSPCFG_RX_RING_LEN            40 // Number of receive BD's
#endif

#ifndef BSPCFG_TX_RING_LEN
  #define BSPCFG_TX_RING_LEN            20 // Number of transmit BD's
#endif


#ifndef BSPCFG_ENABLE_ENET_MULTICAST
   #define BSPCFG_ENABLE_ENET_MULTICAST 1
#endif

#ifndef BSPCFG_ENABLE_ENET_STATS
   #define BSPCFG_ENABLE_ENET_STATS     1
#endif


#ifndef BSPCFG_ENET_RESTORE
   #define BSPCFG_ENET_RESTORE          1
#endif


#ifndef BSPCFG_ENABLE_CPP
   #define BSPCFG_ENABLE_CPP            0
#endif

/*----------------------------------------------------------------------
**                  IO DEVICE DRIVERS CONFIGURATION
*/

#ifndef BSPCFG_ENABLE_IO_SUBSYSTEM
   #define BSPCFG_ENABLE_IO_SUBSYSTEM   1
#endif

/* polled TTY device (UART0) */
#ifndef BSPCFG_ENABLE_TTYA
#define BSPCFG_ENABLE_TTYA              1
#endif

/* polled TTY device (UART1) */
#ifndef BSPCFG_ENABLE_TTYB
#define BSPCFG_ENABLE_TTYB              1
#endif

/* polled TTY device (UART2) */
#ifndef BSPCFG_ENABLE_TTYC
#define BSPCFG_ENABLE_TTYC              0
#endif

/* interrupt-driven TTY device (UART0) */
#ifndef BSPCFG_ENABLE_ITTYA
#define BSPCFG_ENABLE_ITTYA             0
#endif

/* interrupt-driven TTY device (UART1) */
#ifndef BSPCFG_ENABLE_ITTYB
#define BSPCFG_ENABLE_ITTYB             1
#endif

/* interrupt-driven TTY device (UART2) */
#ifndef BSPCFG_ENABLE_ITTYC
#define BSPCFG_ENABLE_ITTYC             0
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
#ifndef BSPCFG_UART1_BAUD_RATE
#define BSPCFG_UART1_BAUD_RATE          115200
#endif

/* TTYC and ITTYC baud rate */
#ifndef BSPCFG_UART2_BAUD_RATE
#define BSPCFG_UART2_BAUD_RATE          115200
#endif

/* TTYA and ITTYA buffer size */
#ifndef BSPCFG_UART0_QUEUE_SIZE
#define BSPCFG_UART0_QUEUE_SIZE         64
#endif

/* TTYB and ITTYB buffer size */
#ifndef BSPCFG_UART1_QUEUE_SIZE
#define BSPCFG_UART1_QUEUE_SIZE         64
#endif

/* TTYC and ITTYC buffer size */
#ifndef BSPCFG_UART2_QUEUE_SIZE
#define BSPCFG_UART2_QUEUE_SIZE         64
#endif

/* RTC device */
#ifndef BSPCFG_ENABLE_RTCDEV
#define BSPCFG_ENABLE_RTCDEV            1
#endif

/* external flash0 */
#ifndef BSPCFG_ENABLE_EXT_FLASH0
#define BSPCFG_ENABLE_EXT_FLASH0        1 
#endif

/* external flash1 */
#ifndef BSPCFG_ENABLE_EXT_FLASH1
#define BSPCFG_ENABLE_EXT_FLASH1        1 
#endif

/* polled I2C0 device */
#ifndef BSPCFG_ENABLE_I2C0
#define BSPCFG_ENABLE_I2C0              1
#endif

/* int I2C0 device */
#ifndef BSPCFG_ENABLE_II2C0
#define BSPCFG_ENABLE_II2C0             0
#endif

/* polled SPI0 device */
#ifndef BSPCFG_ENABLE_SPI0
#define BSPCFG_ENABLE_SPI0              1
#endif

/* interrupt SPI0 device */
#ifndef BSPCFG_ENABLE_ISPI0
#define BSPCFG_ENABLE_ISPI0             0
#endif

/*-----------------------------------------------------------------------------
**                  DEFAULT MQX INITIALIZATION DEFINITIONS
*/

/* Defined in link.xxx */
extern uchar __KERNEL_DATA_START[];
extern uchar __KERNEL_DATA_END[];
extern uchar __DEFAULT_PROCESSOR_NUMBER[];
extern uchar __DEFAULT_INTERRUPT_STACK_SIZE[];

#define BSP_DEFAULT_START_OF_KERNEL_MEMORY              ((pointer)__KERNEL_DATA_START)
#define BSP_DEFAULT_END_OF_KERNEL_MEMORY                ((pointer)__KERNEL_DATA_END)
#define BSP_DEFAULT_PROCESSOR_NUMBER                    ((uint_32)__DEFAULT_PROCESSOR_NUMBER)

#ifndef BSP_DEFAULT_INTERRUPT_STACK_SIZE
   #define BSP_DEFAULT_INTERRUPT_STACK_SIZE             ((uint_32)__DEFAULT_INTERRUPT_STACK_SIZE)
#endif

#ifndef BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX
   #define BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX (6L)
#endif

#ifndef BSP_DEFAULT_MAX_MSGPOOLS
   #define BSP_DEFAULT_MAX_MSGPOOLS                     (16L)
#endif

#ifndef BSP_DEFAULT_MAX_MSGQS
   #define BSP_DEFAULT_MAX_MSGQS                        (128L)
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL
    #if BSPCFG_ENABLE_TTYA
        #define BSP_DEFAULT_IO_CHANNEL                  "ttya:"
        #define BSP_DEFAULT_IO_CHANNEL_DEFINED
    #else
        #define BSP_DEFAULT_IO_CHANNEL                  NULL
    #endif
#endif

#ifndef BSP_DEFAULT_IO_OPEN_MODE
    #define BSP_DEFAULT_IO_OPEN_MODE                    (pointer)(IO_SERIAL_XON_XOFF | IO_SERIAL_TRANSLATION | IO_SERIAL_ECHO)
#endif

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

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
* $FileName: twrmcf51mm.h$
* $Version : 3.6.7.0$
* $Date    : Nov-3-2010$
*
* Comments:
*
*   This include file is used to provide information needed by
*   an application program using the kernel running on the
*   Freescale MM256 Tower board.
*
*END************************************************************************/

#ifndef _twrmcf51mm_h_
#define _twrmcf51mm_h_ 1

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
#define BSP_TWRMCF51MM  1



/* 
** Workaround of USB NMI issue for MCF51MM256 0M79V and 1M79V masks 
** To apply USB NMI workaround #define MCF51MM_REV2_USB_PATCH   1 in user_config.h
** and rebuild PSP, BSP and USB libraries.
*/
#ifndef MCF51MM_REV2_USB_PATCH
    #define MCF51MM_REV2_USB_PATCH         0
#endif

/*
** PROCESSOR MEMORY BOUNDS
*/
extern uchar __IPSBAR[];
extern uchar __INTERNAL_SRAM_BASE[],  __INTERNAL_SRAM_SIZE[];
extern uchar __INTERNAL_FLASH_BASE[], __INTERNAL_FLASH_SIZE[];
extern uchar __EXTERNAL_MRAM_BASE[],  __EXTERNAL_MRAM_SIZE[];
extern uchar __EXTERNAL_MRAM_ROM_BASE[],  __EXTERNAL_MRAM_ROM_SIZE[];
extern uchar __EXTERNAL_MRAM_RAM_BASE[],  __EXTERNAL_MRAM_RAM_SIZE[];

#define BSP_IPSBAR                  ((uint_32)__IPSBAR)
#define BSP_INTERNAL_SRAM_BASE      ((pointer)__INTERNAL_SRAM_BASE)
#define BSP_INTERNAL_SRAM_SIZE      ((uint_32)__INTERNAL_SRAM_SIZE)
#define BSP_INTERNAL_FLASH_BASE     ((pointer)__INTERNAL_FLASH_BASE)
#define BSP_INTERNAL_FLASH_SIZE     ((uint_32)__INTERNAL_FLASH_SIZE)
#define BSP_EXTERNAL_MRAM_BASE      ((pointer)__EXTERNAL_MRAM_BASE)
#define BSP_EXTERNAL_MRAM_SIZE      ((uint_32)__EXTERNAL_MRAM_SIZE)
#define BSP_EXTERNAL_MRAM_ROM_BASE  ((pointer)__EXTERNAL_MRAM_ROM_BASE)
#define BSP_EXTERNAL_MRAM_ROM_SIZE  ((uint_32)__EXTERNAL_MRAM_ROM_SIZE)
#define BSP_EXTERNAL_MRAM_RAM_BASE  ((pointer)__EXTERNAL_MRAM_RAM_BASE)
#define BSP_EXTERNAL_MRAM_RAM_SIZE  ((uint_32)__EXTERNAL_MRAM_RAM_SIZE)

/* Compact Flash Card base address */
#define BSP_CFCARD_BASE             ((pointer)0x00500000)

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

/* (1000 / BSP_ALARM_FREQUENCY) should be divisible without reminder.
** otherwise performance could be degraded - functions for obtaining exact time
** has to calculate with 64bit variables.. e.g _psp_get_elapsed_milliseconds() */
#if BSP_ALARM_RESOLUTION*BSP_ALARM_FREQUENCY != 1000
#warning Bsp Alarm Frequency in milliseconds is not whole number - performance can be degraded 
#endif 


/*
** CLKIN speed
*/

#if (BSPCFG_USE_32KHZ_XTAL == 1)
    #define BSP_SYSTEM_CLOCK                (50331648L)
#elif (BSPCFG_USE_16MHZ_XTAL == 1)
    #define BSP_SYSTEM_CLOCK                (48000000L)
#endif


#define BSP_BUS_CLOCK                       (BSP_SYSTEM_CLOCK/2)

 /********************************************************************/
/*
 * System Bus Clock Info
 */
#define SYSTEM_CLOCK                    (BSP_SYSTEM_CLOCK/1000000)       /* system bus frequency in MHz */
#define SYSTEM_CLK_PERIOD               (1000000000/(BSP_SYSTEM_CLOCK))  /* system bus period in ns */

/*
** The timer MQX uses
*/
#define BSP_FIRST_TIMER                               (0) /* TPM1 */
#define BSP_LAST_TIMER                                (1) /* TPM2 */
#define BSP_TIMER                                     BSP_FIRST_TIMER

/*
** 8.4.4 Core Watchdog Control Register 
*/
#define MCF51MM_WATCHDOG_DISABLED         0
#define MCF51MM_WATCHDOG_INITIALIZATION MCF51MM_WATCHDOG_DISABLED


#if BSP_TIMER == BSP_FIRST_TIMER                               
    #define BSP_TIMER_INTERRUPT_VECTOR                    (MCF51MM_INT_Vtpm1ovf) 
#else
    #define BSP_TIMER_INTERRUPT_VECTOR                    (MCF51MM_INT_Vtpm2ovf) 
#endif
/*
** The I2C settings. 
*/
#define BSP_I2C_CLOCK                                 (BSP_BUS_CLOCK)
#define BSP_I2C_MULT_VAL                              MCF51XX_IIC_MUL_1
#define BSP_I2C_MULT_IICF_BITS                        MCF51XX_IIC_IICF_MUL_1
#define BSP_I2C0_ADDRESS                              (0x6E)
#define BSP_I2C0_BAUD_RATE                            (100000)
#define BSP_I2C0_MODE                                 I2C_MODE_MASTER
#define BSP_I2C0_RX_BUFFER_SIZE                       (64)
#define BSP_I2C0_TX_BUFFER_SIZE                       (64)

/*
** The SPI settings.
*/
#define BSP_SPI_RX_BUFFER_SIZE          (32)
#define BSP_SPI_TX_BUFFER_SIZE          (32)
#define BSP_SPI_BAUDRATE                (1000000)
#define BSP_SPI0_GPIO_CHIP_SELECT       (GPIO_PORT_TA | GPIO_PIN0)
#define BSP_SPI1_GPIO_CHIP_SELECT       (GPIO_PORT_TC | GPIO_PIN3)
#define BSP_SPI_MEMORY_SPI_CS           (MCF5XXX_SPI16_CS0)
#define BSP_SPI_MEMORY_GPIO_CS          (BSP_SPI0_GPIO_CHIP_SELECT)

/*
** The SDCARD settings.
*/
#define BSP_SDCARD_SPI_CHANNEL          "spi0:"
#define BSP_SDCARD_SPI_CS               (MCF5XXX_SPI16_CS0)
#define BSP_SDCARD_GPIO_CS              (BSP_SPI0_GPIO_CHIP_SELECT)
#define BSP_SDCARD_GPIO_DETECT          (GPIO_PORT_TA | GPIO_PIN2)

/*
** GPIO board specifications
*/
#define BSP_LED1    (GPIO_PORT_TF | GPIO_PIN2) //its D9 on board
#define BSP_LED2    (GPIO_PORT_TF | GPIO_PIN1) //its D10 on board
#define BSP_LED3    (GPIO_PORT_TF | GPIO_PIN0) //its D11 on board
#define BSP_LED4    (GPIO_PORT_TE | GPIO_PIN7) //its D12 on board
#define BSP_POT     (GPIO_PORT_TA | GPIO_PIN2)

#define BSP_SW1     (GPIO_PORT_TC | GPIO_PIN6) //its actually SW2 on board
#define BSP_SW2     (GPIO_PORT_TE | GPIO_PIN4) //its actually SW4 on board
#define BSP_SW3     (GPIO_PORT_TA | GPIO_PIN5) //its actually SW3 on board, between 1 and 4 terminal
#define BSP_SW4     (GPIO_PORT_TB | GPIO_PIN1) //its actually SW2 on board, between 2 and 3 terminal

/* definitions for user applications */
#define BSP_BUTTON1   BSP_SW1
#define BSP_BUTTON2   BSP_SW2
#define BSP_SWITCH1_1 BSP_SW3
#define BSP_SWITCH1_2 BSP_SW4

/*
** ADC channels
*/
#define BSP_ADC_CH_POT      (ADC_SOURCE_AD4)

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
** Define the range of interrupts for which the application can install
** isrs.
*/ 
#ifndef BSP_FIRST_INTERRUPT_VECTOR_USED                                                 
   #define BSP_FIRST_INTERRUPT_VECTOR_USED              MCF51MM_INT_Vaccerr   
#endif

#ifndef BSP_LAST_INTERRUPT_VECTOR_USED                                                 
   #define BSP_LAST_INTERRUPT_VECTOR_USED               MCF51MM_INT_expansion10
#endif

#define BSP_ADC_INTERRUPT_VECTOR                (MCF51MM_INT_Vadc)
#define BSP_USB_INTERRUPT_VECTOR                (MCF51MM_INT_Vusb)


#ifndef BSPCFG_ENABLE_CPP
   #define BSPCFG_ENABLE_CPP    0
#endif


/*----------------------------------------------------------------------
**                  IO DEVICE DRIVERS CONFIGURATION
*/

#ifndef BSPCFG_ENABLE_IO_SUBSYSTEM
   #define BSPCFG_ENABLE_IO_SUBSYSTEM  1
#endif

/* polled TTY device (SCI0) */
#ifndef BSPCFG_ENABLE_TTYA
#define BSPCFG_ENABLE_TTYA  1
#endif

/* polled TTY device (SCI1) */
#ifndef BSPCFG_ENABLE_TTYB
#define BSPCFG_ENABLE_TTYB  0
#endif

/* interrupt-driven TTY device (SCI0) */
#ifndef BSPCFG_ENABLE_ITTYA
#define BSPCFG_ENABLE_ITTYA 0
#endif

/* interrupt-driven TTY device (SCI1) */
#ifndef BSPCFG_ENABLE_ITTYB
#define BSPCFG_ENABLE_ITTYB 1
#endif

/* TTYA and ITTYA baud rate */
#ifndef BSPCFG_SCI0_BAUD_RATE
#define BSPCFG_SCI0_BAUD_RATE 115200
#endif

/* TTYB and ITTYB baud rate */
#ifndef BSPCFG_SCI1_BAUD_RATE
#define BSPCFG_SCI1_BAUD_RATE 115200
#endif

/* TTYA and ITTYA buffer size */
#ifndef BSPCFG_SCI0_QUEUE_SIZE
#define BSPCFG_SCI0_QUEUE_SIZE 64
#endif

/* TTYB and ITTYB buffer size */
#ifndef BSPCFG_SCI1_QUEUE_SIZE
#define BSPCFG_SCI1_QUEUE_SIZE 64
#endif

/* polled I2C0 device */
#ifndef BSPCFG_ENABLE_I2C0
#define BSPCFG_ENABLE_I2C0 1
#endif

/* int I2C0 device */
#ifndef BSPCFG_ENABLE_II2C0
#define BSPCFG_ENABLE_II2C0 0
#endif

/* GPIO device */
#ifndef BSPCFG_ENABLE_GPIODEV
#define BSPCFG_ENABLE_GPIODEV  1
#endif

/* PCFLASH device */
#ifndef BSPCFG_ENABLE_PCFLASH
#define BSPCFG_ENABLE_PCFLASH  1
#endif

/* polled SPI0 device */
#ifndef BSPCFG_ENABLE_SPI0
#define BSPCFG_ENABLE_SPI0 1
#endif

/* interrupt SPI0 device */
#ifndef BSPCFG_ENABLE_ISPI0
#define BSPCFG_ENABLE_ISPI0 0
#endif

/* polled SPI1 device */
#ifndef BSPCFG_ENABLE_SPI1
#define BSPCFG_ENABLE_SPI1 0
#endif

/* interrupt SPI1 device */
#ifndef BSPCFG_ENABLE_ISPI1
#define BSPCFG_ENABLE_ISPI1 0
#endif

/* CFM */
#ifndef BSPCFG_ENABLE_FLASHX
#define BSPCFG_ENABLE_FLASHX 1 
#endif

/* PCFLASH device */
#ifndef BSPCFG_ENABLE_PCFLASH
#define BSPCFG_ENABLE_PCFLASH  1
#endif


/* CFM */
#ifndef BSPCFG_ENABLE_USB
#define BSPCFG_ENABLE_USB 1 
#endif

#define USBCFG_KHCI 1
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
   #define BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX  (7L) 
#endif

#ifndef BSP_DEFAULT_MAX_MSGPOOLS
   #define BSP_DEFAULT_MAX_MSGPOOLS                      (2L)
#endif

#ifndef BSP_DEFAULT_MAX_MSGQS
   #define BSP_DEFAULT_MAX_MSGQS                         (16L)
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL
   #if BSPCFG_ENABLE_TTYB
      #define BSP_DEFAULT_IO_CHANNEL                        "ttyb:"
      #define BSP_DEFAULT_IO_CHANNEL_DEFINED
   #elif BSPCFG_ENABLE_TTYA 
      #define BSP_DEFAULT_IO_CHANNEL                        "ttya:"
      #define BSP_DEFAULT_IO_CHANNEL_DEFINED
   #elif BSPCFG_ENABLE_ITTYB 
      #define BSP_DEFAULT_IO_CHANNEL                        "ittyb:"
      #define BSP_DEFAULT_IO_CHANNEL_DEFINED
   #elif BSPCFG_ENABLE_ITTYA 
      #define BSP_DEFAULT_IO_CHANNEL                        "ittya:"
      #define BSP_DEFAULT_IO_CHANNEL_DEFINED
   #else
         #define BSP_DEFAULT_IO_CHANNEL                      NULL
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

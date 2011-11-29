#ifndef _twrmpc5125_h_
#define _twrmpc5125_h_ 
/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $FileName: twrmpc5125.h$
* $Version : 3.7.8.1$
* $Date    : Apr-5-2011$
*
* Comments:
* 
*    This file contains the definitions for the TWRMPC5125 BSP.
*
*END***********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*
** Define the board type
*/
#define BSP_TWRMPC5125               1

/* Set to 1 if you want to use MMU page tables instead of just the BATs.
** It is more expensive in time & memory to use page tables, but each
** task can have its own virtual context that is protected from other
** tasks.
*/
#ifndef BSPCFG_USE_PAGE_TABLES
   #define BSPCFG_USE_PAGE_TABLES    0
#endif

#ifndef BSP_TRAP_EXCEPTIONS
   #define BSP_TRAP_EXCEPTIONS       0
#endif

#ifndef BSPCFG_ICACHE_INHIBIT
   #define BSPCFG_ICACHE_INHIBIT     0
#endif

#ifndef BSPCFG_DCACHE_INHIBIT
   #define BSPCFG_DCACHE_INHIBIT     1
#endif



/*----------------------------------------------------------------------
**                  HARDWARE INITIALIZATION DEFINITIONS
*/

/* The following definitions come from the lilnker command file. */
extern uchar __SDRAM_BASE[];
extern uchar __SDRAM_SIZE[];
#define BSP_RAM_BASE                ((uchar_ptr)__SDRAM_BASE)
#define BSP_RAM_SIZE                ((uint_32)__SDRAM_SIZE)

extern uchar __SRAM_BASE[];      
extern uchar __SRAM_SIZE[];     
#define BSP_SRAM_BASE               ((uchar_ptr)__SRAM_BASE)
#define BSP_SRAM_SIZE               ((uint_32)__SRAM_SIZE)

extern uchar __CACHED_DATA_START[];    
extern uchar __CACHED_DATA_SIZE[];    
extern uchar __CACHED_DATA_END[];     
#define BSP_CACHED_RAM_BASE         ((uchar_ptr)__CACHED_DATA_START)
#define BSP_CACHED_RAM_SIZE         ((uint_32)__CACHED_DATA_SIZE)
#define BSP_CACHED_RAM_END          ((uchar_ptr)__CACHED_DATA_END)

extern uchar __UNCACHED_DATA_START[];
extern uchar __UNCACHED_DATA_SIZE[];
extern uchar __UNCACHED_DATA_END[];
#define BSP_UNCACHED_RAM_BASE       ((uchar_ptr)__UNCACHED_DATA_START)
#define BSP_UNCACHED_RAM_SIZE       ((uint_32)__UNCACHED_DATA_SIZE)
#define BSP_UNCACHED_RAM_END        ((uchar_ptr)__UNCACHED_DATA_END)


extern uchar __IMMR_BASE[];
extern uchar __IMMR_SIZE[];
#define BSP_IMMR_BASE               ((uchar_ptr)__IMMR_BASE)
#define BSP_IMMR_SIZE               ((uint_32)__IMMR_SIZE)

extern uchar __KERNEL_DATA_START[];
extern uchar __KERNEL_DATA_END[];
extern uchar __DEFAULT_PROCESSOR_NUMBER[];
extern uchar __DEFAULT_INTERRUPT_STACK_SIZE[];


/*
** The clock tick rate in number of ticks per second
*/
#ifndef  BSP_ALARM_FREQUENCY
   #define BSP_ALARM_FREQUENCY             (200)
#endif

/*
** Old clock rate definition in milliseconds per tick for compatibility
*/
#define BSP_ALARM_RESOLUTION               (1000 / BSP_ALARM_FREQUENCY)


/* Set to GPT channel to use. If not defined, BSP will use decrementer */
//#define BSPCFG_TIMER_GPT_CHANNEL            0

#ifdef BSPCFG_TIMER_GPT_CHANNEL
   #define BSPCFG_TIMER_USES_GPT            1
   /* Set the timer vector - unfortunately, not a linear mapping. */
   #if BSPCFG_TIMER_GPT_CHANNEL==0
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT0_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==1
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT1_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==2
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT2_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==3
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT3_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==4
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT4_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==5
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT5_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==6
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT6_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==7
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT7_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==8
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT8_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==9
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT9_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==10
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT10_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==11
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT11_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==12
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT12_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==13
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT13_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==14
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT14_VECTOR
   #elif BSPCFG_TIMER_GPT_CHANNEL==15
      #define BSP_TIMER_INTERRUPT_VECTOR      MPC5125_GPT15_VECTOR
   #else
      #error Invalid value for BSPCFG_TIMER_GPT_CHANNEL
   #endif   
#else
   #define BSPCFG_TIMER_USES_DECREMENTER      1
   #define BSP_TIMER_INTERRUPT_VECTOR         PSP_EXCPT_DECREMENTER
#endif

/*
** The processor clock speed
*/
extern char __EXTERNAL_CLOCK_SPEED[];
#define BSP_EXCLK_CLOCK                 ((uint_32)__EXTERNAL_CLOCK_SPEED)
#define BSP_SYSTEM_CLOCK                _mpc5125_get_sys_clock(BSP_EXCLK_CLOCK)
#define BSP_PSC_MCLK_CLOCK              10000000 /* 10 MHz */

/*
** Programmable Serial Controller (PSC) I/O Controller pin mapping
** NOTE: Only one option per PSCx should be enabled. If multiple options
** for a single PSC are enabled, only the first will take effect.
*/
#define BSPCFG_PCS0_USES_PSC0           1
#define BSPCFG_PCS0_USES_FEC1           0
#define BSPCFG_PCS1_USES_PSC1           1
#define BSPCFG_PCS1_USES_USB1           0
#define BSPCFG_PCS2_USES_EMB            0
#define BSPCFG_PCS2_USES_FEC1           1    /* PSC2 spi mode */
#define BSPCFG_PCS3_USES_LPC_EMB        1 
#define BSPCFG_PCS3_USES_FEC1           0
#define BSPCFG_PCS4_USES_DUI            0
#define BSPCFG_PCS4_USES_USB1           0
#define BSPCFG_PCS5_USES_DIU            0
#define BSPCFG_PCS5_USES_SDHC1          1
#define BSPCFG_PCS6_USES_DIU            0
#define BSPCFG_PCS7_USES_DIU            0
#define BSPCFG_PCS8_USES_DIU_I2C        0
#define BSPCFG_PCS9_USES_CAN            0    
#define BSPCFG_PCS9_USES_I2C1           1   /* Tower just uses RX and TX data */
#define BSPCFG_PCS9_USES_I2C2           0  


#define BSPCFG_PSC_DEFAULT_QUEUE_SIZE           256 
#define BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE     (BSPCFG_PSC_DEFAULT_QUEUE_SIZE*3/4)
#define BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE    (BSPCFG_PSC_DEFAULT_QUEUE_SIZE*1/4)
#define BSPCFG_PSC_DEFAULT_BAUD_RATE            115200

/* on board serial console (PCS0) connected over JM60 */
#ifndef BSPCFG_ENABLE_TTYB
   #define BSPCFG_ENABLE_TTYB 1
#endif
#ifndef BSPCFG_ENABLE_ITTYB
   #define BSPCFG_ENABLE_ITTYB 1
#endif

/* TWR-SER serial console (PCS9) */
#ifndef BSPCFG_ENABLE_TTYJ
   #define BSPCFG_ENABLE_TTYJ 1
#endif
#ifndef BSPCFG_ENABLE_ITTYJ
   #define BSPCFG_ENABLE_ITTYJ 1
#endif

/* SPI configuration */
#define BSP_SPI_BAUDRATE                (1000000)
#define BSP_SPI_RX_BUFFER_SIZE          (32)
#define BSP_SPI_TX_BUFFER_SIZE          (32)
#define BSP_SPI_MEMORY_SPI_CS           (MPC512X_SPI_CS2)
#define BSP_SPI_MEMORY_GPIO_CS          (1)

#ifndef BSPCFG_ENABLE_SPI0
   #define BSPCFG_ENABLE_SPI0 0
#endif

#ifndef BSPCFG_ENABLE_SPI1
   #define BSPCFG_ENABLE_SPI1 0
#endif

#ifndef BSPCFG_ENABLE_SPI2
   #define BSPCFG_ENABLE_SPI2 0
#endif

#ifndef BSPCFG_ENABLE_SPI3
   #define BSPCFG_ENABLE_SPI3 0
#endif

#ifndef BSPCFG_ENABLE_SPI4
   #define BSPCFG_ENABLE_SPI4 0
#endif

#ifndef BSPCFG_ENABLE_SPI5
   #define BSPCFG_ENABLE_SPI5 0
#endif

#ifndef BSPCFG_ENABLE_SPI6
   #define BSPCFG_ENABLE_SPI6 0
#endif

#ifndef BSPCFG_ENABLE_SPI7
   #define BSPCFG_ENABLE_SPI7 0
#endif

#ifndef BSPCFG_ENABLE_SPI8
   #define BSPCFG_ENABLE_SPI8 0
#endif

#ifndef BSPCFG_ENABLE_SPI9
   #define BSPCFG_ENABLE_SPI9 0
#endif
/* I2C configuration */
#ifndef BSPCFG_ENABLE_I2C0
   #define BSPCFG_ENABLE_I2C0 0
#endif

#ifndef BSPCFG_ENABLE_II2C0
   #define BSPCFG_ENABLE_II2C0 0
#endif

/* Compact Flash Card base address */
#define BSP_CFCARD_BASE                 ((pointer)0x10000000)  
/* Compact Nand Flash base address */
#define BSP_NANDFLASH_BASE              ((pointer)0x40000000)
/*
**  USB Configuration
*/
#define USBCFG_CONTROLLER_OTG       (0)
#define USBCFG_CONTROLLER_HOST      (1)
#define USBCFG_EHCI   

/*
**  Ethernet Device Configuration
*/
#define BSP_ENET_DEVICE_COUNT             MPC512X_FEC_DEVICE_COUNT
#define BSP_DEFAULT_ENET_DEVICE           0
#define BSP_DEFAULT_ENET_OUI              { 0x00, 0x00, 0x5E, 0, 0, 0 }

#define BSP_ENET0_INTERFACE_OPTION        ENET_OPTION_RMII
#define BSP_ENET1_INTERFACE_OPTION        ENET_OPTION_RMII

/*
** The ethernet PHY device number 0..31
*/
#ifndef BSP_ENET0_PHY_ADDR
#define BSP_ENET0_PHY_ADDR                1
#endif

#ifndef BSP_ENET1_PHY_ADDR
#define BSP_ENET1_PHY_ADDR                0
#endif

/*
** The I2C stuff.
*/
#define BSP_I2C_CLOCK                   (((uint_32)66666666))
#define BSP_I2C0_ADDRESS                (0xA0)
#define BSP_I2C0_BAUD_RATE              (26000)
#define BSP_I2C0_MODE                   (I2C_MODE_MASTER)
#define BSP_I2C0_INT_LEVEL              (1)
#define BSP_I2C0_RX_BUFFER_SIZE         (64)
#define BSP_I2C0_TX_BUFFER_SIZE         (64)

/*
** Nand Flash
*/
#define BSP_FLASH_BASE                  ((pointer)0x0) /* block #0 */
#define BSP_FLASH_SIZE                  (0x400000)
#define	BSP_FLASH_WIDTH                 (8)
#define BSP_FLASH_DEVICES               (1)
#define BSP_VIRTUAL_PAGE_SIZE           (2048)
#define BSP_ECC_SIZE                    (32) /* 32-error correction bits (60 ECC bytes) */

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
   #define BSPCFG_ENABLE_ENET_MULTICAST   1
#endif

#ifndef BSPCFG_ENABLE_ENET_STATS
   #define BSPCFG_ENABLE_ENET_STATS       1
#endif


#ifndef BSPCFG_ENET_RESTORE
   #define BSPCFG_ENET_RESTORE            1
#endif

#ifndef BSPCFG_ENABLE_GPIODEV
   #define BSPCFG_ENABLE_GPIODEV          0
#endif


/* DIU HDMI Interface chip */
/* #define BSP_HDMI_SIL9034                /* define for rev 1 board */
#define BSP_HDMI_SIL9022                  /* define for rev 2 board */



#ifndef BSPCFG_ENABLE_RTCDEV
   #define BSPCFG_ENABLE_RTCDEV           0
#endif


/* No ADC available */
#define BSPCFG_ENABLE_ADC                 0

#ifndef BSPCFG_ENABLE_IO_SUBSYSTEM
   #define BSPCFG_ENABLE_IO_SUBSYSTEM     1
#endif


#ifndef BSPCFG_MSCAN1_USES_MSCAN1
   #define BSPCFG_MSCAN1_USES_MSCAN1      1
#endif

#ifndef BSPCFG_MSCAN2_USES_MSCAN2
   #define BSPCFG_MSCAN2_USES_MSCAN2      1
#endif

/* SDHC device */
#ifndef BSPCFG_ENABLE_SDHC
#define BSPCFG_ENABLE_SDHC             1
#endif  
/*
** The SDCARD settings.
*/
#define BSP_SDCARD_SDHC_CHANNEL         "sdhc:"


extern const ENET_IF_STRUCT ENET_0;
extern const ENET_IF_STRUCT ENET_1;

/*
** INTERRUPT DEFINITIONS
*/

/* Define the range of interrupts for which the application can
** install ISRs.
*/
#define BSP_FIRST_INTERRUPT_VECTOR_USED   PSP_EXCPT_MACHINE_CHECK
#define BSP_LAST_INTERRUPT_VECTOR_USED    MPC5125_LAST_ICTL

/*
** The following macros are needed by the i/o drivers to prevent
** pipeline side effects
*/
#define _BSP_IO_EIEIO _PSP_EIEIO()
#define _BSP_IO_SYNC  _PSP_SYNC()
#define _BSP_IO_ISYNC _PSP_ISYNC()


/*----------------------------------------------------------------------
**                  DEFAULT MQX INITIALIZATION DEFINITIONS
*/


#define BSP_DEFAULT_START_OF_KERNEL_MEMORY           (pointer)__KERNEL_DATA_START
#define BSP_DEFAULT_END_OF_KERNEL_MEMORY             (pointer)__KERNEL_DATA_END
#define BSP_DEFAULT_PROCESSOR_NUMBER                 (uint_32)__DEFAULT_PROCESSOR_NUMBER
#define BSP_DEFAULT_INTERRUPT_STACK_SIZE             (uint_32)__DEFAULT_INTERRUPT_STACK_SIZE
#define BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX (6L)
#define BSP_DEFAULT_MAX_MSGPOOLS                     (16L)
#define BSP_DEFAULT_MAX_MSGQS                        (128L)

#ifndef BSP_DEFAULT_IO_CHANNEL
    #define BSP_DEFAULT_IO_CHANNEL                   "ttyb:" 
    #define BSP_DEFAULT_IO_CHANNEL_DEFINED           1
#endif

#define BSP_DEFAULT_IO_OPEN_MODE                     (pointer)(IO_SERIAL_XON_XOFF | IO_SERIAL_TRANSLATION | IO_SERIAL_ECHO)


#ifndef BSPCFG_PSC0_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC0_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC0_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC0_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC0_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC0_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC0_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC0_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif


#ifndef BSPCFG_PSC1_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC1_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC1_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC1_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC1_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC1_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC1_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC1_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif


#ifndef BSPCFG_PSC2_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC2_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC2_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC2_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC2_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC2_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC2_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC2_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif


#ifndef BSPCFG_PSC3_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC3_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC3_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC3_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC3_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC3_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC3_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC3_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif


#ifndef BSPCFG_PSC4_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC4_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC4_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC4_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC4_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC4_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC4_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC4_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif


#ifndef BSPCFG_PSC5_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC5_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC5_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC5_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC5_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC5_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC5_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC5_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif


#ifndef BSPCFG_PSC6_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC6_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC6_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC6_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC6_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC6_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC6_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC6_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif


#ifndef BSPCFG_PSC7_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC7_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC7_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC7_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC7_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC7_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC7_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC7_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif


#ifndef BSPCFG_PSC8_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC8_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC8_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC8_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC8_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC8_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC8_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC8_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif


#ifndef BSPCFG_PSC9_DEFAULT_QUEUE_SIZE
   #define BSPCFG_PSC9_DEFAULT_QUEUE_SIZE BSPCFG_PSC_DEFAULT_QUEUE_SIZE
#endif
#ifndef BSPCFG_PSC9_DEFAULT_INPUT_ALARM_SIZE
   #define BSPCFG_PSC9_DEFAULT_INPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_INPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC9_DEFAULT_OUTPUT_ALARM_SIZE
   #define BSPCFG_PSC9_DEFAULT_OUTPUT_ALARM_SIZE BSPCFG_PSC_DEFAULT_OUTPUT_ALARM_SIZE
#endif
#ifndef BSPCFG_PSC9_DEFAULT_BAUD_RATE
   #define BSPCFG_PSC9_DEFAULT_BAUD_RATE BSPCFG_PSC_DEFAULT_BAUD_RATE
#endif

   
#ifdef __cplusplus
}
#endif

#endif

/* EOF */

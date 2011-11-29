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
* $FileName: init_bsp.c$
* $Version : 3.6.18.0$
* $Date    : Sep-22-2010$
*
* Comments:
*
*   This file contains the source functions for functions required to
*   specifically initialize the card.
*   $Header:init_bsp.c, 7, 3/15/2007 11:39:41 AM, Jim Gard$
*   $NoKeywords$
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h"
#include "bsp_prv.h"
#include "mmu.h"

#undef  _NELEM
#define _NELEM(ary)     (sizeof(ary) / sizeof(ary[0]))

const char _PTR_ _mqx_bsp_revision = REAL_NUM_TO_STR(BSP_REVISION);
const char _PTR_ _mqx_io_revision  = REAL_NUM_TO_STR(IO_REVISION);

#define DMA_CHANNEL_TDB         0xFFFF

// Specify MQX_MONITOR_TYPE_BDM while debugging with JTAG to
// disable cache and MMU which interfere with debugging.
// volatile uint_32 _mqx_monitor_type = MQX_MONITOR_TYPE_BDM;
// #define BSP_TRAP_EXCEPTIONS  1

static uint_32 _bsp_get_hwticks(pointer);

static uint_32 _bsp_get_hwticks(pointer param);
static void    _bsp_setup_watchdog(void);

const MCF5441_TIMER_INIT_STRUCT _bsp_timers[MCF5441_NUM_TIMERS] = {
    { BSP_PIT0_INT_VECTOR, BSP_PIT0_INT_LEVEL },
    { BSP_PIT1_INT_VECTOR, BSP_PIT1_INT_LEVEL },
    { BSP_PIT2_INT_VECTOR, BSP_PIT2_INT_LEVEL },
    { BSP_PIT3_INT_VECTOR, BSP_PIT3_INT_LEVEL }
};


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_enable_card
* Returned Value   : uint_32 result
* Comments         :
*   This function sets up operation of the card.
*
*END*----------------------------------------------------------------------*/

uint_32 _bsp_enable_card
   (
      void
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR kernel_data;
   uint_32                result;
   _mqx_int               i;


/* fixme */
VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

   /* Set the CPU type */
   _mqx_set_cpu_type(MQX_CPU);

   /* Set the bsp exit handler, called by _mqx_exit */
   _mqx_set_exit_handler(_bsp_exit_handler);

   /* Initialize the MCF548x support functions */
   _mcf5441_initialize_support(0);

   /*
   ** Initialize the interrupt handling
   */
   _int_set_vector_table(BSP_RAM_INTERRUPT_VECTOR_TABLE);

   result =  _psp_int_init(BSP_FIRST_INTERRUPT_VECTOR_USED, BSP_LAST_INTERRUPT_VECTOR_USED);
   if (result != MQX_OK) {
      return result;
   } /* Endif */

    /* Initialize the timer interrupt */
    _time_set_timer_vector(BSP_TIMER_INTERRUPT_VECTOR);
    if (_int_install_isr(BSP_TIMER_INTERRUPT_VECTOR, (void (_CODE_PTR_)(pointer))_bsp_timer_isr, NULL) == NULL) {
        return MQX_TIMER_ISR_INSTALL_FAIL;
    } /* Endif */

    _GET_KERNEL_DATA(kernel_data);

    // Initialize the slice timer to interrupt the specified
    // number of times per second
    kernel_data->TIMER_HW_REFERENCE = _mcf5441_timer_init_freq(BSP_TIMER, BSP_ALARM_FREQUENCY, BSP_SYSTEM_CLOCK, FALSE);    

   _time_set_hwtick_function(_bsp_get_hwticks, 0);
   _time_set_hwticks_per_tick(kernel_data->TIMER_HW_REFERENCE);
   _time_set_ticks_per_sec(BSP_ALARM_FREQUENCY);

   // Initialize and enable the timer interrupt
   _mcf5441_int_init(BSP_TIMER_INTERRUPT_VECTOR, BSP_TIMER_INTERRUPT_LEVEL, /*BSP_SLICE_TIMER0_INT_PRIORITY, */TRUE);

   // Initialize and enable the serial UART interrupts
   _mcf5441_int_init(BSP_UART0_INT_VECTOR, BSP_UART0_INT_LEVEL, TRUE);
   _mcf5441_int_init(BSP_UART2_INT_VECTOR, BSP_UART2_INT_LEVEL, TRUE);
   _mcf5441_int_init(BSP_UART4_INT_VECTOR, BSP_UART4_INT_LEVEL, TRUE);
   _mcf5441_int_init(BSP_UART6_INT_VECTOR, BSP_UART6_INT_LEVEL, TRUE);

   // Install and mask the DMA interrupt handler
/*   
   _int_install_isr(BSP_ENET_DMA_INTERRUPT, _mcf5445_dma_isr, (pointer)0);
   _mcf5445_int_init(BSP_ENET_DMA_INTERRUPT, BSP_ENET_DMA_INT_LEVEL, BSP_ENET_DMA_INT_PRIORITY, FALSE);
*/

   // Initialize and disable the security engine interrupt
   // _mcf54xx_int_init(MCF548x_INT_SEC, BSP_SEC_INT_LEVEL, /*BSP_SEC_INT_PRIORITY, */FALSE);

#if BSP_TRAP_EXCEPTIONS
   _int_install_unexpected_isr();
#endif

   // Always invalidate the caches even if not enabled.  This allows
   // us to flush the cache always.  If we flush before invalidating
   // very bad things happen.
   _ICACHE_INVALIDATE();
   _DCACHE_INVALIDATE();

   if (_mqx_monitor_type == MQX_MONITOR_TYPE_NONE) {

      static const PSP_MMU_INIT_STRUCT mmu_init = {
         /* We define the default cacheability of non-ACR mapped regions */
         /* as non-cacheable and unbuffered */
         MCF54XX_CACR_DDCM(MCF54XX_CACHE_NONCACHEABLE_UNBUFFERED)
      };        

      /* Initialize Cache Control Register CACR */
      _mmu_init((pointer)&mmu_init);

      /* Set up 1 instruction and 1 data ACR in two separate SDRAM areas */
      /* Caution: Consider memory map in linker command file before changing regions */
      /* Note: Second arg to _mmu_add_region is used in mask value in ACR */
      
      result = _mmu_add_region(__CACHED_CODE_START, __CACHED_CODE_END - __CACHED_CODE_START, PSP_MMU_EXEC_ALLOWED);
      if (result != MQX_OK) return result; 
 
      result = _mmu_add_region(__CACHED_DATA_START, __CACHED_DATA_END - __CACHED_DATA_START, PSP_MMU_WRITE_THROUGH);
      if (result != MQX_OK) return result;
 
      /* Copy ACR table into ACR registers */
      _MMU_ENABLE();
      
      /* Enable instruction cache and branch history cache in CACR */
      _ICACHE_ENABLE(MCF54XX_CACR_IEC | MCF54XX_CACR_BEC); 
   
      /* Enable data cache bit in CACR */
      _DCACHE_ENABLE(0);
    
   } /* Endif */

#if BSPCFG_ENABLE_CPP
    /* initialize C++ constructors */
    __cpp_init();
#endif

   /* Initialize RTC and MQX time */
#if BSPCFG_ENABLE_RTCDEV
   _bsp_rtc_io_init ();
   _rtc_init (RTC_INIT_FLAG_ENABLE);
   _rtc_sync_with_mqx (TRUE);
#endif

#if BSPCFG_ENABLE_IO_SUBSYSTEM
   /* Initialize the I/O Sub-system */
   result = _io_init();
   if (result != MQX_OK) {
      return result;
   } /* Endif */

  
#if BSPCFG_ENABLE_TTYA
    _mcf54xx_uart_serial_polled_install("ttya:", &_bsp_uart0_init, _bsp_uart0_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_TTYB
    _mcf54xx_uart_serial_polled_install("ttyb:", &_bsp_uart2_init, _bsp_uart2_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_TTYC
    _mcf54xx_uart_serial_polled_install("ttyc:", &_bsp_uart4_init, _bsp_uart4_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_TTYD
    _mcf54xx_uart_serial_polled_install("ttyd:", &_bsp_uart5_init, _bsp_uart5_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_TTYE
    _mcf54xx_uart_serial_polled_install("ttye:", &_bsp_uart6_init, _bsp_uart6_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_ITTYA
    _mcf54xx_uart_serial_int_install("ittya:", &_bsp_uart0_init, _bsp_uart0_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_ITTYB
    _mcf54xx_uart_serial_int_install("ittyb:", &_bsp_uart2_init, _bsp_uart2_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_ITTYC
    _mcf54xx_uart_serial_int_install("ittyc:", &_bsp_uart4_init, _bsp_uart4_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_ITTYD
    _mcf54xx_uart_serial_int_install("ittyd:", &_bsp_uart5_init, _bsp_uart5_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_ITTYE
    _mcf54xx_uart_serial_int_install("ittye:", &_bsp_uart6_init, _bsp_uart6_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_SPI0
    _mcf5xxx_dspi_polled_install("spi0:", &_bsp_dspi0_init);
#endif

#if BSPCFG_ENABLE_ISPI0
    _mcf5xxx_dspi_int_install("ispi0:", &_bsp_dspi0_init);
#endif

#if BSPCFG_ENABLE_SPI1
    _mcf5xxx_dspi_polled_install("spi1:", &_bsp_dspi1_init);
#endif

#if BSPCFG_ENABLE_ISPI1
    _mcf5xxx_dspi_int_install("ispi1:", &_bsp_dspi1_init);
#endif

#if BSPCFG_ENABLE_I2C0
    _mcf54xx_i2c_polled_install("i2c0:", &_bsp_i2c0_init);
#endif

#if BSPCFG_ENABLE_II2C0
    _mcf54xx_i2c_int_install("ii2c0:", &_bsp_i2c0_init);
#endif

#if BSPCFG_ENABLE_I2C5
    _mcf54xx_i2c_polled_install("i2c5:", &_bsp_i2c5_init);
#endif

#if BSPCFG_ENABLE_II2C5
    _mcf54xx_i2c_int_install("ii2c5:", &_bsp_i2c5_init);
#endif

   /* Install the PCCard Flash drivers */
#if BSPCFG_ENABLE_PCFLASH   
   _io_pccardflexbus_install("pccarda:", (PCCARDFLEXBUS_INIT_STRUCT _PTR_) &_bsp_cfcard_init);
   _io_apcflash_install("pcflasha:");
#endif

/* install the GPIO driver */
#if BSPCFG_ENABLE_GPIODEV   
   _io_gpio_install("gpio:");
#endif

/* install external flash */
#if BSPCFG_ENABLE_NANDFLASH
    result = _io_nandflash_install(&_bsp_nandflash_init);
#endif

/* ADC initialization */
#if BSPCFG_ENABLE_ADC
   _io_adc_install("adc:", NULL);
   reg_ptr->SCM_PMM.PMM.PPMCR0 = 37;   // clk enable ADC
#endif

#if BSPCFG_ENABLE_ESDHC
    _esdhc_install ("esdhc:", &_bsp_esdhc0_init);
#endif

   /* Initialize the default serial I/O */
   _io_serial_default_init();

#endif /* BSPCFG_ENABLE_IO_SUBSYSTEM */
   
    return MQX_OK;

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_exit_handler
* Returned Value   : none
* Comments         :
*    This function is called when MQX exits
*
*END*----------------------------------------------------------------------*/

void _bsp_exit_handler
   (
      void
   )
{ /* Body */

   _mcf5441_int_mask_all();
   _DCACHE_DISABLE();
   _ICACHE_DISABLE();
   _MMU_DISABLE();

} /* Endbody */


/*ISR*********************************************************************
*
* Function Name    : _bsp_timer_isr
* Returned Value   : void
* Comments         :
*    The timer ISR is the interrupt handler for the clock tick.
*
*END**********************************************************************/

void _bsp_timer_isr
   (
      pointer dummy
   )
{ /* Body */

   // Acknowlege the interrupt to clear it
   _mcf5441_timer_clear_int(BSP_TIMER);

   _time_notify_kernel();

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_hwticks
* Returned Value   : uint_32
* Comments         :
*    This function returns the number of hw ticks that have elapsed
* since the last interrupt
*
*END*----------------------------------------------------------------------*/

static uint_32 _bsp_get_hwticks(pointer unused_param) {
   return _mcf5441_get_hwticks(BSP_TIMER);
}

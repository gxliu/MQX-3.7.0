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
* $FileName: init_bsp.c$
* $Version : 3.6.7.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the source functions for functions required to
*   specifically initialize the card.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h"
#include "bsp_prv.h"


const char _PTR_ _mqx_bsp_revision = REAL_NUM_TO_STR(BSP_REVISION);
const char _PTR_ _mqx_io_revision  = REAL_NUM_TO_STR(IO_REVISION);

static uint_32 _bsp_get_hwticks(pointer param);
static void    _bsp_setup_watchdog(void);

extern boolean _bsp_timer_sw_prescaller_check();


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
   KERNEL_DATA_STRUCT_PTR   kernel_data;
   uint_32                  result;
   
   _GET_KERNEL_DATA(kernel_data);

   /* Set the CPU type */
     /* Set the CPU type */
   _mqx_set_cpu_type(MQX_CPU);

#if MQX_EXIT_ENABLED
   /* Set the bsp exit handler, called by _mqx_exit */
   _mqx_set_exit_handler(_bsp_exit_handler);
#endif

   /* Initialize the MCF51CN support functions */
   _mcf51EM_initialize_support(0);
 
   /*
   ** Initialize the interrupt handling
   */
   /* Mask all interrupts */
   _mcf51EM_int_mask_all();
   
   _int_set_vector_table(BSP_INTERRUPT_VECTOR_TABLE);

   result =  _psp_int_init(BSP_FIRST_INTERRUPT_VECTOR_USED,
      BSP_LAST_INTERRUPT_VECTOR_USED);
      
   if (result != MQX_OK) {
      return result;
   } /* Endif */

   /* Initialize the timer interrupt */
   _time_set_timer_vector(BSP_TIMER_INTERRUPT_VECTOR);
   if (_int_install_isr(BSP_TIMER_INTERRUPT_VECTOR,
      (void (_CODE_PTR_)(pointer))_bsp_timer_isr, NULL) == NULL)
   {
      return MQX_TIMER_ISR_INSTALL_FAIL;
   } /* Endif */


   kernel_data->TIMER_HW_REFERENCE = _mcf51EM_timer_init_freq(BSP_TIMER,
                             BSP_BUS_CLOCK / BSP_ALARM_FREQUENCY, FALSE);

   _time_set_hwtick_function(_bsp_get_hwticks,
      (pointer)kernel_data->TIMER_HW_REFERENCE);
   _time_set_hwticks_per_tick(kernel_data->TIMER_HW_REFERENCE);
   _time_set_ticks_per_sec(BSP_ALARM_FREQUENCY);
   _mcf51EM_timer_unmask_int(BSP_TIMER);

#if BSPCFG_ENABLE_CPP
/* initialize C++ constructors */
   __cpp_init();
#endif

/* Initialize RTC and MQX time */
#if BSPCFG_ENABLE_RTCDEV
   _bsp_rtc_io_init ();
   _rtc_sync_with_mqx (TRUE);
#endif

#if BSPCFG_ENABLE_IO_SUBSYSTEM
   /* Initialize the I/O Sub-system */
   result = _io_init();
   if (result != MQX_OK) {
      return result;
   } /* Endif */

/* Install device drivers */
#if BSPCFG_ENABLE_TTYA
   _mcf51xx_sci_polled_install("ttya:", &_bsp_sci0_init,
      _bsp_sci0_init.QUEUE_SIZE);
#endif
#if BSPCFG_ENABLE_TTYB
   _mcf51xx_sci_polled_install("ttyb:", &_bsp_sci1_init,
      _bsp_sci1_init.QUEUE_SIZE);
#endif
#if BSPCFG_ENABLE_TTYC
   _mcf51xx_sci_polled_install("ttyc:", &_bsp_sci2_init,
      _bsp_sci2_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_ITTYA
   _mcf51xx_sci_int_install("ittya:", &_bsp_sci0_init,
      _bsp_sci0_init.QUEUE_SIZE);
#endif
#if BSPCFG_ENABLE_ITTYB
   _mcf51xx_sci_int_install("ittyb:", &_bsp_sci1_init,
      _bsp_sci1_init.QUEUE_SIZE);
#endif
#if BSPCFG_ENABLE_ITTYC
   _mcf51xx_sci_int_install("ittyc:", &_bsp_sci2_init,
      _bsp_sci2_init.QUEUE_SIZE);
#endif

/* Initialize the default serial I/O */
_io_serial_default_init();

#if BSPCFG_ENABLE_I2C0
   _mcf51xx_i2c_polled_install("i2c0:", &_bsp_i2c0_init);
#endif
#if BSPCFG_ENABLE_II2C0
   _mcf51xx_i2c_int_install("ii2c0:", &_bsp_i2c0_init);
#endif

   /* Install the GPIO driver */
#if BSPCFG_ENABLE_GPIODEV   
   _io_gpio_install("gpio:");
#endif

    /* Install the LCD driver */
#if BSPCFG_ENABLE_LCD
    _bsp_lcd_io_init();
#endif

/* Install ADC driver */
#if BSPCFG_ENABLE_ADC1
   _io_adc_install("adc1:", &_bsp_adc1_init);
#endif

#if BSPCFG_ENABLE_ADC2
   _io_adc_install("adc2:", &_bsp_adc2_init);
#endif

#if BSPCFG_ENABLE_ADC3
   _io_adc_install("adc3:", &_bsp_adc3_init);
#endif

#if BSPCFG_ENABLE_ADC4
   _io_adc_install("adc4:", &_bsp_adc4_init);
#endif


#if BSPCFG_ENABLE_SPI0
   _mcf5xxx_spi16_polled_install("spi0:", &_bsp_spi0_init);
#endif

#if BSPCFG_ENABLE_ISPI0
   _mcf5xxx_spi16_int_install("ispi0:", &_bsp_spi0_init);
#endif

#if BSPCFG_ENABLE_SPI1
   _mcf5xxx_spi8_polled_install("spi1:", &_bsp_spi1_init);
#endif

#if BSPCFG_ENABLE_ISPI1
   _mcf5xxx_spi8_int_install("ispi1:", &_bsp_spi1_init);
#endif

#if BSPCFG_ENABLE_SPI2
   _mcf5xxx_spi8_polled_install("spi2:", &_bsp_spi2_init);
#endif

#if BSPCFG_ENABLE_ISPI2
   _mcf5xxx_spi8_int_install("ispi2:", &_bsp_spi2_init);
#endif



/* install internal flash */
/* FLASHX1 array1 always start at address 0x00 to 0x1FFFF */
#if BSPCFG_ENABLE_FLASHX1
    _mcf51em_internal_flash_array1_install("flashx1:", BSPCFG_FLASHX_SIZE1);
#endif

/* FLASHX2 array2 always start at address 0x20000 to 0x3FFFF */
#if BSPCFG_ENABLE_FLASHX2
    _mcf51em_internal_flash_array2_install("flashx2:", BSPCFG_FLASHX_SIZE2);
#endif

#endif

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
   uint_16   temp;

   temp = _psp_set_sr(0x2700);
   _mcf51EM_int_mask_all();

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
 
#if BSP_WATCHDOG_INITIALIZATION != BSP_WATCHDOG_DISABLED
   // Service the watchdog timer to verify we are still in control
   // TODO - Not supported yet
#endif
   
   _mcf51EM_timer_clear_int(BSP_TIMER);

   /* apply sw prescaller - do not react on every timer isr */
   if(_bsp_timer_sw_prescaller_check() == TRUE){
      _time_notify_kernel();
   }
   
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


static uint_32 _bsp_get_hwticks
   (
      pointer param
   )
{ /* Body */
   
   return _mcf51EM_get_hwticks(BSP_TIMER); 

} /* Endbody */



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_setup_watchdog
* Returned Value   : uint_32
* Comments         :
*    This function initializes the watchdog timer according to the definition
* BSP_WATCHDOG_INITIALIZATION in <BOARD_NAME>.h
*
*END*----------------------------------------------------------------------*/

static void _bsp_setup_watchdog
   (
      void
   )
{ /* Body */
// TODO Not supported yet
} /* Endbody */


/* EOF */

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
* $Version : 3.7.4.0$
* $Date    : Mar-10-2011$
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
#include "io_rev.h"
#include "bsp_rev.h"
#include "mmu.h"

const char _PTR_ _mqx_bsp_revision = REAL_NUM_TO_STR(BSP_REVISION);
const char _PTR_ _mqx_io_revision  = REAL_NUM_TO_STR(IO_REVISION);


/*
** Specify MQX_MONITOR_TYPE_BDM while debugging with JTAG to
** disable cache and MMU which interfere with debugging.
*/
/* volatile uint_32 _mqx_monitor_type = MQX_MONITOR_TYPE_BDM; */

static uint_32 _bsp_get_hwticks(pointer param);
static void    _bsp_setup_watchdog(void);

MPC5208_TIMER_INIT_STRUCT _bsp_timers[MCF5208_NUM_TIMERS] = {
   {MCF5208_INT_PIT0, BSP_PIT0_INT_LEVEL},
   {MCF5208_INT_PIT1, BSP_PIT1_INT_LEVEL}
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
   
   /* Set the CPU type */
   _mqx_set_cpu_type(MQX_CPU);

   /* Set the bsp exit handler, called by _mqx_exit */
   _mqx_set_exit_handler(_bsp_exit_handler);

   /* Initialize the MCF5227 support functions */
   _mcf5208_initialize_support(0);

   /*
   ** Initialize the interrupt handling
   */
   /* Mask all interrupts */
   _mcf5208_int_mask_all();
  
   _int_set_vector_table(BSP_RAM_INTERRUPT_VECTOR_TABLE);

   result =  _psp_int_init(BSP_FIRST_INTERRUPT_VECTOR_USED, BSP_LAST_INTERRUPT_VECTOR_USED);
   if (result != MQX_OK) {
      return result;
   } /* Endif */

   /* Initialize the timer interrupt */
   _time_set_timer_vector(BSP_TIMER_INTERRUPT_VECTOR);
   if (_int_install_isr(BSP_TIMER_INTERRUPT_VECTOR, (void (_CODE_PTR_)(pointer))_bsp_timer_isr, NULL) == NULL)
   {
      return MQX_TIMER_ISR_INSTALL_FAIL;
   } /* Endif */

   _GET_KERNEL_DATA(kernel_data);

   kernel_data->TIMER_HW_REFERENCE = _mcf5208_timer_init_freq(BSP_TIMER, BSP_ALARM_FREQUENCY, BSP_SYSTEM_CLOCK/2, FALSE);
   _time_set_hwtick_function(_bsp_get_hwticks, (pointer)kernel_data->TIMER_HW_REFERENCE);
   _time_set_hwticks_per_tick(kernel_data->TIMER_HW_REFERENCE);
   _time_set_ticks_per_sec(BSP_ALARM_FREQUENCY);

   _mcf5208_timer_unmask_int(BSP_TIMER);


#if BSPCFG_ENABLE_CPP
   /* initialize C++ constructors */
   __cpp_init();
#endif


#if BSPCFG_ENABLE_IO_SUBSYSTEM
   /* Initialize the I/O Sub-system */
   result = _io_init();
   if (result != MQX_OK) {
      return result;
   } /* Endif */


#if BSPCFG_ENABLE_TTYA
   _mcf52xx_uart_serial_polled_install("ttya:", &_bsp_uart0_init, _bsp_uart0_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_TTYB
   _mcf52xx_uart_serial_polled_install("ttyb:", &_bsp_uart1_init, _bsp_uart1_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_ITTYA
   _mcf52xx_uart_serial_int_install("ittya:", &_bsp_uart0_init, _bsp_uart0_init.QUEUE_SIZE);
#endif

#if BSPCFG_ENABLE_ITTYB
   _mcf52xx_uart_serial_int_install("ittyb:", &_bsp_uart1_init, _bsp_uart1_init.QUEUE_SIZE);
#endif   

#if BSPCFG_ENABLE_I2C0
   _mcf52xx_i2c_polled_install("i2c0:", &_bsp_i2c0_init);
#endif

#if BSPCFG_ENABLE_II2C0
   _mcf52xx_i2c_int_install("ii2c0:", &_bsp_i2c0_init);
#endif

#if BSPCFG_ENABLE_SPI0
   _mcf5xxx_qspi_polled_install("spi0:", &_bsp_qspi0_init);
#endif

#if BSPCFG_ENABLE_ISPI0
   _mcf5xxx_qspi_int_install("ispi0:", &_bsp_qspi0_init);
#endif


#if BSPCFG_ENABLE_EXT_FLASH
    result = _io_flashx_install(&_bsp_flashx_init);
#endif 

   /* Initialize the default serial I/O */
   _io_serial_default_init();
   
   /* Install the GPIO driver */
#if BSPCFG_ENABLE_GPIODEV   
   _io_gpio_install("gpio:");
#endif

#endif /* BSPCFG_ENABLE_IO_SUBSYSTEM */

   /* Enable/disable the watchdog timer */
   _bsp_setup_watchdog(); 

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
   _mcf5208_int_mask_all();

   _DCACHE_FLUSH();
   _CACHE_DISABLE();
/*   _mcf5227_mmu_disable(); */

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

#if MCF5208_WATCHDOG_INITIALIZATION != MCF5208_WATCHDOG_DISABLED
   /* Service the watchdog timer to verify we are still in control */
   VMCF5208_STRUCT_PTR mcf5208_ptr = _PSP_GET_MBAR();
   
   mcf5208_ptr->SCM_POWER.CWSR = 0x55;
   mcf5208_ptr->SCM_POWER.CWSR = 0xAA;
#endif

   _mcf5208_timer_clear_int(BSP_TIMER);

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

   return _mcf5208_get_hwticks(BSP_TIMER);

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_setup_watchdog
* Returned Value   : none
* Comments         :
*    This function setups the watchdog timer
*
*END*----------------------------------------------------------------------*/

static void _bsp_setup_watchdog
   (
      void
   )
{ /* Body */

   VMCF5208_STRUCT_PTR mcf5208_ptr = _PSP_GET_MBAR();

   mcf5208_ptr->SCM_POWER.CWCR = 0;

   if (mcf5208_ptr->SCM_POWER.CWCR & MCF5208_SCM_CWCR_CWTAVAL) {
      mcf5208_ptr->SCM_POWER.CWCR = MCF5208_SCM_CWCR_CWTAVAL;
   } /* Endif */
   if (mcf5208_ptr->SCM_POWER.CWCR & MCF5208_SCM_CWCR_CWTIC) {
      mcf5208_ptr->SCM_POWER.CWCR = MCF5208_SCM_CWCR_CWTIC;
   } /* Endif */

   /* Clear the watchdog count */
   mcf5208_ptr->SCM_POWER.CWSR = 0x55;
   mcf5208_ptr->SCM_POWER.CWSR = 0xAA;

#if MCF5208_WATCHDOG_INITIALIZATION != MCF5208_WATCHDOG_DISABLED
   mcf5208_ptr->SCM_POWER.CWCR = 0
# if MCF5208_WATCHDOG_INITIALIZATION == MCF5208_WATCHDOG_RESET
# error Watchdog resets immediately for some reason
      | MCF5208_SCM_CWCR_CWRI
# endif
      | MCF5208_SCM_CWCR_CWE
      | MCF5208_SCM_CWCR_CWT(MCF5208_WATCHDOG_DELAY);
#endif

} /* Endbody */

/* EOF */
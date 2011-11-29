/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: serl_int_mpc5125.c$
* $Version : 3.7.4.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the driver functions for the MPC5125
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "io_prv.h"
#include "charq.h"
#include "fio_prv.h"
#include "serinprv.h"


extern _mqx_uint _mpc5125_serial_ioctl(MPC5125_SERIAL_INFO_STRUCT_PTR, _mqx_uint, pointer);
extern _mqx_uint _mpc5125_serial_polled_init(MPC5125_SERIAL_INIT_STRUCT_PTR, pointer _PTR_, char_ptr);
extern _mqx_uint _mpc5125_serial_polled_deinit(MPC5125_SERIAL_INIT_STRUCT_PTR, MPC5125_SERIAL_INFO_STRUCT_PTR );


static uint_32 _mpc5125_uart_serial_int_init( IO_SERIAL_INT_DEVICE_STRUCT_PTR, char_ptr);
static uint_32 _mpc5125_uart_serial_int_deinit( MPC5125_SERIAL_INIT_STRUCT_PTR,MPC5125_SERIAL_INFO_STRUCT_PTR);
uint_32 _mpc5125_uart_serial_int_enable( MPC5125_SERIAL_INFO_STRUCT_PTR);
static void _mpc5125_psc_fifo_int_isr(pointer);
static void _mpc5125_uart_serial_int_isr(pointer);
static void _mpc5125_uart_serial_int_putc( IO_SERIAL_INT_DEVICE_STRUCT_PTR,char);


const uint_32 _mpc5125_psc_vector[MPC5125_NUM_PSC] = {
   MPC5125_PSC0_VECTOR,
   MPC5125_PSC1_VECTOR,
   MPC5125_PSC2_VECTOR,
   MPC5125_PSC3_VECTOR,
   MPC5125_PSC4_VECTOR,
   MPC5125_PSC5_VECTOR,
   MPC5125_PSC6_VECTOR,
   MPC5125_PSC7_VECTOR,
   MPC5125_PSC8_VECTOR,
   MPC5125_PSC9_VECTOR
};

// move to PSP support struct
static uint_32 _mpc5125_psc_fifo_int_enable = 0;


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_uart_serial_int_install
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install an interrupt driven uart serial device.
*
*END*----------------------------------------------------------------------*/

uint_32 _mpc5125_serial_int_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr identifier,

      /* [IN] The I/O init data pointer */
      const MPC5125_SERIAL_INIT_STRUCT _PTR_ init_data_ptr
   )
{ 
   return _io_serial_int_install(identifier,
      (uint_32 (_CODE_PTR_)(pointer, char _PTR_))_mpc5125_uart_serial_int_init,
      (uint_32 (_CODE_PTR_)(pointer))_mpc5125_uart_serial_int_enable,
      (uint_32 (_CODE_PTR_)(pointer,pointer))_mpc5125_uart_serial_int_deinit,
      (void    (_CODE_PTR_)(pointer, char))_mpc5125_uart_serial_int_putc,
      (uint_32 (_CODE_PTR_)(pointer, uint_32, pointer))_mpc5125_serial_ioctl,
      (pointer)init_data_ptr, 
      init_data_ptr->QUEUE_SIZE);
} 


/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_uart_serial_int_init
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    This function initializes the UART in interrupt mode.
*
*END*********************************************************************/

static uint_32 _mpc5125_uart_serial_int_init
   (
      /* [IN] the interrupt I/O initialization information */
      IO_SERIAL_INT_DEVICE_STRUCT_PTR int_io_dev_ptr,

      /* [IN] the rest of the name of the device opened */
      char_ptr                        open_name_ptr
   )
{ 
   MPC5125_SERIAL_INFO_STRUCT_PTR uart_info_ptr;
   MPC5125_SERIAL_INIT_STRUCT_PTR uart_init_ptr;
   uint_32                        result,vector;

   uart_init_ptr = int_io_dev_ptr->DEV_INIT_DATA_PTR;
   result = _mpc5125_serial_polled_init((pointer)uart_init_ptr,
      &int_io_dev_ptr->DEV_INFO_PTR, open_name_ptr);
   if (result != MQX_OK) {
      return(result);
   }

   vector = _mpc5125_psc_vector[uart_init_ptr->DEVICE];
   uart_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
   uart_info_ptr->VECTOR = vector;
   uart_info_ptr->OLD_ISR_DATA = _int_get_isr_data(vector);
   uart_info_ptr->OLD_ISR_EXCEPTION_HANDLER = _int_get_exception_handler(vector);
   uart_info_ptr->OLD_ISR = _int_install_isr(vector, _mpc5125_uart_serial_int_isr, int_io_dev_ptr);


    _int_install_isr(MPC5125_FIFOC_VECTOR, _mpc5125_psc_fifo_int_isr, NULL);

   return(MQX_OK);

} 


/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_uart_serial_int_deinit
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    This function de-initializes the UART in interrupt mode.
*
*END*********************************************************************/

static uint_32 _mpc5125_uart_serial_int_deinit
   (
      /* [IN] the interrupt I/O initialization information */
      MPC5125_SERIAL_INIT_STRUCT_PTR io_init_ptr,

      /* [IN] the address of the device specific information */
      MPC5125_SERIAL_INFO_STRUCT_PTR io_info_ptr
   )
{ 
   MPC5125_PSC_STRUCT_PTR psc_ptr = io_info_ptr->UART_PTR;

   psc_ptr->IMR = 0; // Mask all interrupts
   
   _mpc5125_disable_interrupt(io_info_ptr->VECTOR);

   // disable PSC FIFO interrupt processing for this PSC.
   _mpc5125_psc_fifo_int_enable &= ~(1<<io_info_ptr->INIT.DEVICE);
   if (_mpc5125_psc_fifo_int_enable==0) {
      _mpc5125_disable_interrupt(MPC5125_FIFOC_VECTOR);
   }

   _mpc5125_serial_polled_deinit(io_init_ptr, io_info_ptr);
   _int_install_isr(io_info_ptr->VECTOR, io_info_ptr->OLD_ISR, io_info_ptr->OLD_ISR_DATA);

   return(MQX_OK);
} 


/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_uart_serial_int_enable
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    This function enables the UART interrupts mode.
*
*END*********************************************************************/

uint_32 _mpc5125_uart_serial_int_enable
   (
      /* [IN] the address of the device specific information */
      MPC5125_SERIAL_INFO_STRUCT_PTR io_info_ptr
   )
{ 
   MPC5125_PSC_STRUCT_PTR psc_ptr = io_info_ptr->UART_PTR;

   psc_ptr->IMR = 0;
   psc_ptr->RX_IMR = PSC_FIFO_IMR_DATA_READY;
   psc_ptr->TX_IMR = PSC_FIFO_IMR_EMPTY;

   _mpc5125_psc_fifo_int_enable |= 1<<io_info_ptr->INIT.DEVICE;
   _mpc5125_enable_interrupt(MPC5125_FIFOC_VECTOR);

   return MQX_OK;
} 


/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_psc_fifo_int_isr
* Returned Value   : none
* Comments         :
*   interrupt handler for the serial I/O interrupts.
*
*************************************************************************/

static void _mpc5125_psc_fifo_int_isr
   (
      /* [IN] the address of the device specific information */
      pointer parameter
   )
{ 
   MPC5125_PSC_FIFO_CONTROLLER_PTR  psc_fifo_ptr = MPC5125_PSC_FIFO_DEVICE_ADDRESS();
   void                 (_CODE_PTR_ isr)(pointer);
   pointer                          isr_data;
   uint_32                          i;
   
   for (i=0;i<MPC5125_NUM_PSC;i++) {
      if (psc_fifo_ptr->INTERRUPT_STATUS & (0x00010001<<i)) {
         // fifo has pending interrupt request
         if (   _mpc5125_psc_fifo_int_enable  & 1<<i) {
            isr_data= _int_get_isr_data(_mpc5125_psc_vector[i]);
            isr= _int_get_isr(_mpc5125_psc_vector[i]);
            if (isr) {
               (*isr)(isr_data);
            }
         }            
      }
   }
}

/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_uart_serial_int_isr
* Returned Value   : none
* Comments         :
*   interrupt handler for the serial I/O interrupts.
*
*************************************************************************/
static void _mpc5125_uart_serial_int_isr
   (
      /* [IN] the address of the device specific information */
      pointer parameter
   )
{ 
   IO_SERIAL_INT_DEVICE_STRUCT_PTR     int_io_dev_ptr = parameter;
   MPC5125_SERIAL_INFO_STRUCT_PTR      uart_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
   MPC5125_PSC_STRUCT_PTR              psc_ptr = uart_info_ptr->UART_PTR;
   int_32                              c;
   uint_16                             stat;


   uart_info_ptr->INTERRUPTS++;

   // Handle receive
   psc_ptr->RX_ISR |= PSC_FIFO_SR_DATA_READY;

   while (psc_ptr->RX_COUNT) {
      c = *((uchar_ptr)&psc_ptr->RX_DATA);

      stat = psc_ptr->SR;
      if (stat & (PSC_SR_ORERR|PSC_SR_RB|PSC_SR_FE|PSC_SR_PE)) {
         if (stat & PSC_SR_RB) {
            ++uart_info_ptr->RX_BREAKS;
            c = *((uchar_ptr)&psc_ptr->RX_DATA);
             psc_ptr->CR = PSC_CR_RESET_BREAK;
         } 
         if (stat & PSC_SR_ORERR) {
            ++uart_info_ptr->RX_OVERRUNS;
         } 
         if (stat & PSC_SR_FE) {
            ++uart_info_ptr->RX_OVERRUNS;
         } 
         if (stat & PSC_SR_PE) {
            ++uart_info_ptr->RX_FRAMING_ERRORS;
         } 
          psc_ptr->CR = PSC_CR_RESET_ERROR;
      } 

      uart_info_ptr->RX_CHARS++;

      if (!_io_serial_int_addc(int_io_dev_ptr, c)) {
         uart_info_ptr->RX_DROPPED_INPUT++;
      } 
   } 


   // Handle Transmit
   if ((psc_ptr->TX_IMR & PSC_FIFO_IMR_EMPTY)&&(psc_ptr->TX_ISR & PSC_FIFO_IMR_EMPTY)) {
      psc_ptr->TX_ISR |= PSC_FIFO_IMR_EMPTY;
      psc_ptr->TX_IMR &= ~PSC_FIFO_IMR_EMPTY;
   }
   
   while ((psc_ptr->TX_ISR & PSC_FIFO_IMR_FULL)==0)  { 
   
      c = _io_serial_int_nextc(int_io_dev_ptr);
      if (c < 0) {
         break;
      }
      psc_ptr->TX_IMR = PSC_FIFO_IMR_EMPTY;
    
      *((uchar_ptr)&psc_ptr->TX_DATA) = c;
   } 
} 


/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_uart_serial_int_putc
* Returned Value   : none
* Comments         :
*   This function is called to write out the first character, when
* the output serial device and output ring buffers are empty.
*
*END*********************************************************************/

static void _mpc5125_uart_serial_int_putc
   (
      /* [IN] the address of the device specific information */
      IO_SERIAL_INT_DEVICE_STRUCT_PTR int_io_dev_ptr,

      /* [IN] the character to write out now */
      char                       c
   )
{ 
   MPC5125_SERIAL_INFO_STRUCT_PTR             uart_info_ptr;
   MPC5125_PSC_STRUCT_PTR psc_ptr;

   uart_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
   psc_ptr = uart_info_ptr->UART_PTR;

   while ((psc_ptr->SR & PSC_SR_TxEMP)==0) {} 
   *((uchar_ptr)&psc_ptr->TX_DATA) = c;

   // Interrupt when character has been sent
   psc_ptr->TX_IMR = PSC_FIFO_IMR_EMPTY;
} 

/* EOF */

/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
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
* $FileName: serl_int_kuart.c$
* $Version : 3.7.3.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the low level functions for the interrupt driven
*   serial I/O for the MCF51XX SCI.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "io_prv.h"
#include "charq.h"
#include "fio_prv.h"
#include "serinprv.h"

/* Polled functions used */
extern uint_32 _kuart_polled_init(KUART_INIT_STRUCT_PTR, pointer _PTR_, char _PTR_);
extern uint_32 _kuart_polled_deinit(KUART_INIT_STRUCT_PTR, KUART_INFO_STRUCT_PTR);
extern uint_32 _kuart_polled_ioctl(KUART_INFO_STRUCT_PTR, uint_32, uint_32_ptr);

/* Interrupt driver functions */

extern void    _kuart_int_putc(IO_SERIAL_INT_DEVICE_STRUCT_PTR, char);
extern uint_32 _kuart_int_init(IO_SERIAL_INT_DEVICE_STRUCT_PTR, char _PTR_);
extern uint_32 _kuart_int_deinit(KUART_INIT_STRUCT_PTR, KUART_INFO_STRUCT_PTR);
extern uint_32 _kuart_int_enable(KUART_INFO_STRUCT_PTR);
extern void    _kuart_int_err_isr(pointer);
extern void    _kuart_int_rx_tx_isr(pointer);


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _kuart_int_install
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install an interrupt driven uart serial device.
*
*END*----------------------------------------------------------------------*/

uint_32 _kuart_int_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr identifier,

      /* [IN] The I/O init data pointer */
      KUART_INIT_STRUCT_CPTR  init_data_ptr,

      /* [IN] The I/O queue size to use */
      uint_32  queue_size
   )
{ /* Body */

   return _io_serial_int_install(identifier,
      (uint_32 (_CODE_PTR_)(pointer, char _PTR_))_kuart_int_init,
      (uint_32 (_CODE_PTR_)(pointer))_kuart_int_enable,
      (uint_32 (_CODE_PTR_)(pointer,pointer))_kuart_int_deinit,
      (void    (_CODE_PTR_)(pointer, char))_kuart_int_putc,
      (uint_32 (_CODE_PTR_)(pointer, uint_32, pointer))_kuart_polled_ioctl,
      (pointer)init_data_ptr, queue_size);

} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _kuart_int_init
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    This function initializes the SCI in interrupt mode.
*
*END*********************************************************************/

uint_32 _kuart_int_init
   (
      /* [IN] the interrupt I/O initialization information */
      IO_SERIAL_INT_DEVICE_STRUCT_PTR int_io_dev_ptr,

      /* [IN] the rest of the name of the device opened */
      char _PTR_                      open_name_ptr
   )
{ /* Body */
    KUART_INFO_STRUCT_PTR sci_info_ptr;
    KUART_INIT_STRUCT_PTR sci_init_ptr;
    uint_32                     result;

    sci_init_ptr = int_io_dev_ptr->DEV_INIT_DATA_PTR;
    result = _kuart_polled_init((pointer)sci_init_ptr, &int_io_dev_ptr->DEV_INFO_PTR, open_name_ptr);
    if (result != MQX_OK) {
        return(result);
    }/* Endif */

    sci_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;

    sci_info_ptr->OLD_ISR_DATA = _int_get_isr_data(sci_init_ptr->RX_TX_VECTOR);
    sci_info_ptr->OLD_ISR_EXCEPTION_HANDLER = _int_get_exception_handler(sci_init_ptr->RX_TX_VECTOR);

    /* Init RX/TX interrupt vector */
    sci_info_ptr->OLD_ISR =
      _int_install_isr(sci_init_ptr->RX_TX_VECTOR, _kuart_int_rx_tx_isr, int_io_dev_ptr);
      
    /* Init RX interrupt vector */
    sci_info_ptr->OLD_ISR =
      _int_install_isr(sci_init_ptr->ERR_VECTOR, _kuart_int_err_isr, int_io_dev_ptr); 
    
    _bsp_int_init(sci_init_ptr->RX_TX_VECTOR, sci_init_ptr->RX_TX_PRIORITY, 0, TRUE);
    _bsp_int_init(sci_init_ptr->ERR_VECTOR, sci_init_ptr->ERR_PRIORITY, 0, TRUE);

    return(MQX_OK);

} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _kuart_int_deinit
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    This function de-initializes the UART in interrupt mode.
*
*END*********************************************************************/

uint_32 _kuart_int_deinit
   (
      /* [IN] the interrupt I/O initialization information */
      KUART_INIT_STRUCT_PTR io_init_ptr,

      /* [IN] the address of the device specific information */
      KUART_INFO_STRUCT_PTR io_info_ptr
   )
{ /* Body */
   UART_MemMapPtr sci_ptr = io_info_ptr->SCI_PTR;

   sci_ptr->C2 = 0; /* Disable interrupts, transmiter, receiver */ 
   _kuart_polled_deinit(io_init_ptr, io_info_ptr);

   _int_install_isr(io_init_ptr->RX_TX_VECTOR, io_info_ptr->OLD_ISR, io_info_ptr->OLD_ISR_DATA);

   return(MQX_OK);

} /* Endbody */

/*FUNCTION****************************************************************
*
* Function Name    : _kuart_int_enable
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    This function enables the UART interrupts mode.
*
*END*********************************************************************/

uint_32 _kuart_int_enable
   (
      /* [IN] the address of the device specific information */
      KUART_INFO_STRUCT_PTR io_info_ptr
   )
{ /* Body */

     UART_MemMapPtr sci_ptr = io_info_ptr->SCI_PTR;
    
    /* enable only recieve interrupt, transmit will be enabled during sending first character */      
    sci_ptr->C2 |= UART_C2_RIE_MASK | UART_C2_RE_MASK | UART_C2_TE_MASK ; 

    return MQX_OK;

} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _kuart_int_err_isr
* Returned Value   : none
* Comments         :
*   interrupt handler for the serial error interrupts.
*
*************************************************************************/

void _kuart_int_err_isr
   (
      /* [IN] the address of the device specific information */
      pointer parameter
   )
{ /* Body */

    IO_SERIAL_INT_DEVICE_STRUCT_PTR        int_io_dev_ptr = parameter;
    KUART_INFO_STRUCT_PTR                  sci_info_ptr;
    UART_MemMapPtr                         sci_ptr;
    volatile int_32                        c;
    uint_16                                stat;

    sci_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
    sci_ptr = sci_info_ptr->SCI_PTR;

    ++sci_info_ptr->INTERRUPTS;
    stat = sci_ptr->S1;

    if(stat & UART_S1_OR_MASK) {
       ++sci_info_ptr->RX_OVERRUNS; 
    }
    if(stat & UART_S1_PF_MASK) {
       ++sci_info_ptr->RX_PARITY_ERRORS; 
    }
    if(stat & UART_S1_NF_MASK) {
       ++sci_info_ptr->RX_NOISE_ERRORS; 
    }
    if(stat & UART_S1_FE_MASK) {
       ++sci_info_ptr->RX_FRAMING_ERRORS; 
    }
}  /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _kuart_int_rx_tx_isr
* Returned Value   : none
* Comments         :
*   interrupt handler for the serial input interrupts.
*
*************************************************************************/

void _kuart_int_rx_tx_isr
   (
      /* [IN] the address of the device specific information */
      pointer parameter
   )
{ /* Body */
   IO_SERIAL_INT_DEVICE_STRUCT_PTR        int_io_dev_ptr = parameter;
   KUART_INFO_STRUCT_PTR                  sci_info_ptr;
   UART_MemMapPtr                         sci_ptr;
   volatile int_32                        c;

   sci_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
   sci_ptr = sci_info_ptr->SCI_PTR;

   ++sci_info_ptr->INTERRUPTS;
    
   /* try if RX buffer has some characters */
   if (sci_ptr->S1 & UART_S1_RDRF_MASK) {
      c = sci_ptr->D;
      if (!_io_serial_int_addc(int_io_dev_ptr, c)) {
          sci_info_ptr->RX_DROPPED_INPUT++;
      }
      sci_info_ptr->RX_CHARS++; 
   }

   /* try if TX buffer is still not full */
   if (sci_ptr->S1 & UART_S1_TDRE_MASK) {
      c = _io_serial_int_nextc(int_io_dev_ptr);
      if (c >= 0) {
          sci_ptr->D = c;
          sci_info_ptr->TX_CHARS++; 
      } else {
         /* All data sent, disable transmit interrupt */
         sci_ptr->C2 &= ~UART_C2_TIE_MASK; 
      }
   }
    
}  /* Endbody */

/*FUNCTION****************************************************************
*
* Function Name    : _kuart_int_putc
* Returned Value   : none
* Comments         :
*   This function is called to write out the first character, when
* the output serial device and output ring buffers are empty.
*
*END*********************************************************************/

void _kuart_int_putc
   (
      /* [IN] the address of the device specific information */
      IO_SERIAL_INT_DEVICE_STRUCT_PTR int_io_dev_ptr,

      /* [IN] the character to write out now */
      char                       c
   )
{ /* Body */
   KUART_INFO_STRUCT_PTR                  sci_info_ptr;
   UART_MemMapPtr                         sci_ptr;

   sci_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
   sci_ptr = sci_info_ptr->SCI_PTR;

   while (!(sci_ptr->S1 & UART_S1_TDRE_MASK)) {
      /* Wait while buffer is full */
   } /* Endwhile */

   sci_ptr->D = c;

   /* Enable transmit iterrupt */
   sci_ptr->C2 |= UART_C2_TIE_MASK;   

} /* Endbody */

/* EOF */

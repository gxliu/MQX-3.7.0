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
* $FileName: serl_pol_kuart.c$
* $Version : 3.7.4.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the functions for the polled serial I/O
*   low level functions for the MCF51XX SCI.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "io_prv.h"
#include "charq.h"
#include "fio_prv.h"
#include "serplprv.h"


/* Polled driver functions */
extern char    _kuart_polled_getc(KUART_INFO_STRUCT_PTR);
extern void    _kuart_polled_putc(KUART_INFO_STRUCT_PTR, char);
extern boolean _kuart_polled_status(KUART_INFO_STRUCT_PTR);
extern uint_32 _kuart_polled_ioctl(KUART_INFO_STRUCT_PTR, uint_32, uint_32_ptr);
extern uint_32 _kuart_polled_init(KUART_INIT_STRUCT_PTR, pointer _PTR_, char _PTR_);
extern uint_32 _kuart_polled_deinit(KUART_INIT_STRUCT_PTR, KUART_INFO_STRUCT_PTR);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _kuart_polled_install
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install a polled sci device.
*
*END*----------------------------------------------------------------------*/

uint_32 _kuart_polled_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr           identifier,

      /* [IN] The I/O init data pointer */
      KUART_INIT_STRUCT_CPTR            init_data_ptr,

      /* [IN] The I/O queue size to use */
      uint_32            queue_size
   )
{ /* Body */
 
#if PE_LDD_VERSION
    if (PE_PeripheralUsed((uint_32)_bsp_get_serial_base_address(init_data_ptr->DEVICE)))
    {
        return IO_ERROR;
    }
#endif
    
    return _io_serial_polled_install(identifier,
      (uint_32 (_CODE_PTR_)(pointer, pointer _PTR_, char _PTR_))_kuart_polled_init,
      (uint_32 (_CODE_PTR_)(pointer, pointer))_kuart_polled_deinit,
      (char    (_CODE_PTR_)(pointer))_kuart_polled_getc,
      (void    (_CODE_PTR_)(pointer, char))_kuart_polled_putc,
      (boolean (_CODE_PTR_)(pointer))_kuart_polled_status,
      (uint_32 (_CODE_PTR_)(pointer, uint_32, pointer))_kuart_polled_ioctl,
      (pointer)init_data_ptr, queue_size);

} /* Endbody */



/*FUNCTION****************************************************************
*
* Function Name    : _kuart_polled_init
* Returned Value   : MQX_OK or a MQX error code.
* Comments         :
*    This function initializes the SCI
*
*END*********************************************************************/

uint_32 _kuart_polled_init
   (
      /* [IN] the initialization information for the device being opened */
      KUART_INIT_STRUCT_PTR               io_init_ptr,

      /* [OUT] the address to store device specific information */
      pointer _PTR_                       io_info_ptr_ptr,

      /* [IN] the rest of the name of the device opened */
      char _PTR_                          open_name_ptr
   )
{ /* Body */
   UART_MemMapPtr                       sci_ptr;
   KUART_INFO_STRUCT_PTR                sci_info_ptr;
   uint_32                              channel;
   uint_32                              baud_divisor;

   sci_info_ptr = _mem_alloc_system_zero((uint_32)sizeof(KUART_INFO_STRUCT));

#if MQX_CHECK_MEMORY_ALLOCATION_ERRORS
   if ( sci_info_ptr == NULL ) {
      return MQX_OUT_OF_MEMORY;
   }/* Endif */
#endif

   /* Get peripheral address */
   channel = io_init_ptr->DEVICE;

   sci_ptr = _bsp_get_serial_base_address(channel);
   if (sci_ptr == NULL) {
      return KUART_IO_INVALID_CHANNEL;
   }

   *io_info_ptr_ptr = sci_info_ptr;

   /* Save initialization values */
   sci_info_ptr->INIT = *io_init_ptr;

   // init GPIO and clock GATING
   _bsp_serial_io_init(channel);
   
   sci_info_ptr->SCI_PTR = sci_ptr;

   /* Calculate baud settings */
   /* baud_divisor = clock_speed/ baudrate + 0.5 */
   baud_divisor = (sci_info_ptr->INIT.CLOCK_SPEED + (8 * sci_info_ptr->INIT.BAUD_RATE))/ (16 * sci_info_ptr->INIT.BAUD_RATE);
   if (baud_divisor > 0x1fff)
      return IO_ERROR;
      sci_ptr->BDH = (uchar)((baud_divisor >> 8) & 0xFF);
   sci_ptr->BDL = (uchar)(baud_divisor & 0xFF);

   /* 8-bit mode. Normal operation */
   sci_ptr->C1 = 0;

   /* Transmitter and receiver enable */
   sci_ptr->C2 = UART_C2_RE_MASK + UART_C2_TE_MASK;

   /* Disable all errors interrupts */ 
   sci_ptr->C3 = 0;

   /* set watermark in the almost full TX buffer */
   if (((sci_ptr->PFIFO & UART_PFIFO_TXFIFOSIZE_MASK) >> UART_PFIFO_TXFIFOSIZE_SHIFT) == 0) {
      /* 1 dataword in D */
      sci_ptr->TWFIFO = UART_TWFIFO_TXWATER(0);
   }
   else {
      uint_8 txsize = 1 << (((sci_ptr->PFIFO & UART_PFIFO_TXFIFOSIZE_MASK) >> UART_PFIFO_TXFIFOSIZE_SHIFT) + 1);

      /* watermark for TX buffer generates interrupts below & equal to watermark */
      sci_ptr->TWFIFO = UART_TWFIFO_TXWATER(txsize - 1);
   }

   /* watermark for RX buffer generates interrupts above & equal to watermark */
   sci_ptr->RWFIFO = UART_RWFIFO_RXWATER(1);

   /* Flush RX / TX buffers */   
   sci_ptr->CFIFO |= UART_CFIFO_RXFLUSH_MASK | UART_CFIFO_TXFLUSH_MASK;

   /* Enable TX FIFO, enable RX FIFO */
   sci_ptr->PFIFO |= UART_PFIFO_TXFE_MASK | UART_PFIFO_RXFE_MASK; 

   return MQX_OK;
} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _kuart_polled_deinit
* Returned Value   : MQX_OK or a mqx error code.
* Comments         :
*    This function de-initializes the SCI.
*
*END*********************************************************************/

uint_32 _kuart_polled_deinit
   (
      /* [IN] the initialization information for the device being opened */
      KUART_INIT_STRUCT_PTR io_init_ptr,

      /* [IN] the address of the device specific information */
      KUART_INFO_STRUCT_PTR io_info_ptr
   )
{ /* Body */

   _mem_free(io_info_ptr);

   return(MQX_OK);

} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _kuart_polled_getc
* Returned Value   : char
* Comments         :
*   Return a character when it is available.  This function polls the
* device for input.
*
*************************************************************************/

char _kuart_polled_getc
   (
      /* [IN] the address of the device specific information */
      KUART_INFO_STRUCT_PTR io_info_ptr
   )
{ /* Body */
    UART_MemMapPtr sci_ptr = io_info_ptr->SCI_PTR;
    
   /* Wait while buffer is empty */
   while (!(sci_ptr->S1 & UART_S1_RDRF_MASK)) {
      /* Wait while buffer is empty */
   } /* Endwhile */

   io_info_ptr->RX_CHARS++;

   return sci_ptr->D;
} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _kuart_polled_putc
* Returned Value   : void
* Comments         :
*   Writes the provided character.
*
*END*********************************************************************/

void _kuart_polled_putc
   (
      /* [IN] the address of the device specific information */
      KUART_INFO_STRUCT_PTR io_info_ptr,

      /* [IN] the character to write */
      char                               c
   )
{
   UART_MemMapPtr sci_ptr = io_info_ptr->SCI_PTR;

   while (!(sci_ptr->S1 & UART_S1_TDRE_MASK)) {
      /* Wait while buffer is full */
   } /* Endwhile */

   sci_ptr->D = c;
   
   io_info_ptr->TX_CHARS++;
}


/*FUNCTION****************************************************************
*
* Function Name    : _kuart_polled_status
* Returned Value   : boolean
* Comments         :
*            This function returns TRUE if a character is available
*            on the on I/O device, otherwise it returns FALSE.
*
*END*********************************************************************/

boolean _kuart_polled_status
   (
      /* [IN] the address of the device specific information */
      KUART_INFO_STRUCT_PTR io_info_ptr
   )
{ /* Body */
   UART_MemMapPtr sci_ptr = io_info_ptr->SCI_PTR;
   if( (sci_ptr->SFIFO & UART_SFIFO_RXEMPT_MASK) == 0 )
        return TRUE;
   else
        return FALSE; 
} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _kuart_polled_ioctl
* Returned Value   : uint_32 MQX_OK or a mqx error code.
* Comments         :
*    This function performs miscellaneous services for
*    the I/O device.
*
*END*********************************************************************/

uint_32 _kuart_polled_ioctl
   (
      /* [IN] the address of the device specific information */
      KUART_INFO_STRUCT_PTR io_info_ptr,

      /* [IN] The command to perform */
      uint_32                    cmd,

      /* [IN] Parameters for the command */
      uint_32_ptr                param_ptr
   )
{ /* Body */
   UART_MemMapPtr sci_ptr = io_info_ptr->SCI_PTR;
   uint_32                  baud, tmp;
   
   switch (cmd) {     
      case IO_IOCTL_SERIAL_GET_DATA_BITS:
         tmp = sci_ptr->C1 & UART_C1_M_MASK;
         *param_ptr = (tmp >> UART_C1_M_SHIFT) + 8;
         /* return 8 or 9 */
         break;
         
      case IO_IOCTL_SERIAL_SET_DATA_BITS:
         /* set the 8 bit mode M = 0*/
         tmp = sci_ptr->C1 & ~UART_C1_M_MASK;
         if(*param_ptr == 9)
             tmp |= UART_C1_M_MASK; 
         /* Write back C1 value */
         sci_ptr->C1 = (uint_8) tmp;
         break;
         
      case IO_IOCTL_SERIAL_GET_BAUD:
         *param_ptr = io_info_ptr->INIT.BAUD_RATE;
         break;
         
      case IO_IOCTL_SERIAL_SET_BAUD: 
         /* baud_divisor = clock_speed / baudrate + 0.5 */  
         baud = (io_info_ptr->INIT.CLOCK_SPEED + (8 * (*param_ptr))) / (16 * (*param_ptr));
         if (baud > (UART_BDH_SBR_MASK << 8))
             return IO_ERROR_INVALID_IOCTL_CMD;
         io_info_ptr->INIT.BAUD_RATE = *param_ptr;       
         sci_ptr->BDH = (uchar)((baud >> 8) & UART_BDH_SBR_MASK);
         sci_ptr->BDL = (uchar)(baud & UART_BDL_SBR_MASK);      
         break;
         
      case IO_IOCTL_SERIAL_GET_STATS:
         *param_ptr++ = io_info_ptr->INTERRUPTS;
         *param_ptr++ = io_info_ptr->RX_CHARS;
         *param_ptr++ = io_info_ptr->TX_CHARS;
         *param_ptr++ = io_info_ptr->RX_BREAKS;
         *param_ptr++ = io_info_ptr->RX_PARITY_ERRORS;
         *param_ptr++ = io_info_ptr->RX_FRAMING_ERRORS;
         *param_ptr++ = io_info_ptr->RX_OVERRUNS;
         *param_ptr++ = io_info_ptr->RX_DROPPED_INPUT;
         break;
         
      case IO_IOCTL_SERIAL_CLEAR_STATS:
         io_info_ptr->INTERRUPTS = 0;
         io_info_ptr->RX_CHARS = 0;
         io_info_ptr->TX_CHARS = 0;
         io_info_ptr->RX_BREAKS = 0;
         io_info_ptr->RX_PARITY_ERRORS = 0;
         io_info_ptr->RX_FRAMING_ERRORS = 0;
         io_info_ptr->RX_OVERRUNS = 0;
         io_info_ptr->RX_DROPPED_INPUT = 0;
         break;
         
      case IO_IOCTL_SERIAL_CAN_TRANSMIT:
         *param_ptr = sci_ptr->S1 & UART_S1_TDRE_MASK ? 1 : 0;
         break;
         
      case IO_IOCTL_SERIAL_CAN_RECEIVE:
         *param_ptr = sci_ptr->S1 & UART_S1_RDRF_MASK ? 1 : 0;
         break;
         
      case IO_IOCTL_SERIAL_GET_PARITY:
         tmp = IO_SERIAL_PARITY_NONE;
         if (sci_ptr->C1 & UART_C1_PE_MASK) {
            if (sci_ptr->C1 & UART_C1_PT_MASK) {
               tmp = IO_SERIAL_PARITY_ODD;
            } else {
               tmp = IO_SERIAL_PARITY_EVEN;
            }
         }
         *param_ptr = tmp;
         break;
         
      case IO_IOCTL_SERIAL_SET_PARITY:
         tmp = sci_ptr->C1 & ~(UART_C1_PE_MASK | UART_C1_PT_MASK);
         switch (*param_ptr) {
            case IO_SERIAL_PARITY_NONE:
               break;
            case IO_SERIAL_PARITY_ODD:
               tmp |= UART_C1_PE_MASK | UART_C1_PT_MASK;
               break;
            case IO_SERIAL_PARITY_EVEN:
               tmp |= UART_C1_PE_MASK;
               break;
            default:
               return MQX_INVALID_PARAMETER;
         }
         sci_ptr->C1 = (uint_8) tmp;
         break;
         
      case IO_IOCTL_SERIAL_SET_FLAGS:
         /* automatic HW flow control in polled mode only */
         if (0 == (sci_ptr->C2 & UART_C2_RIE_MASK)) {
            if (*param_ptr & IO_SERIAL_HW_FLOW_CONTROL) {
               sci_ptr->MODEM |= (UART_MODEM_RXRTSE_MASK | UART_MODEM_TXCTSE_MASK);
            } else {
               sci_ptr->MODEM &= (~ (UART_MODEM_RXRTSE_MASK | UART_MODEM_TXCTSE_MASK));
            }            
         }
         if( *param_ptr & IO_SERIAL_HW_485_FLOW_CONTROL )
         {           
            /* get serial device index and set GPIO pin functionality to RTS */
            _bsp_serial_rts_init( io_info_ptr->INIT.DEVICE );
            /* enable hardware support for 485 RTS pin drive */
            sci_ptr->MODEM |= UART_MODEM_TXRTSE_MASK;
         }
         break; 
       
      case IO_IOCTL_SERIAL_DISABLE_RX:
         if( *(boolean _PTR_)param_ptr == TRUE )
         {
            /* disable receiver */
            sci_ptr->C2 &=~UART_C2_RE_MASK;
         }
         else
         {
            /* enable receiver */
            sci_ptr->C2 |= UART_C2_RE_MASK;               
         }
         break;
         
      case IO_IOCTL_SERIAL_WAIT_FOR_TC:
         /* wait for transmission end signal */
         while( ! sci_ptr->S1 & UART_S1_TC_MASK )
         {
         }
         break;

      default:
         return IO_ERROR_INVALID_IOCTL_CMD;
   } /* Endswitch */

   return (MQX_OK);

} /* Endbody */

/* EOF */

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
* $FileName: serl_pol_mcf51xx.c$
* $Version : 3.7.19.0$
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
extern char    _mcf51xx_sci_polled_getc(MCF51XX_SCI_INFO_STRUCT_PTR);
extern void    _mcf51xx_sci_polled_putc(MCF51XX_SCI_INFO_STRUCT_PTR, char);
extern boolean _mcf51xx_sci_polled_status(MCF51XX_SCI_INFO_STRUCT_PTR);
extern uint_32 _mcf51xx_sci_polled_ioctl(MCF51XX_SCI_INFO_STRUCT_PTR, uint_32,
   uint_32_ptr);
extern uint_32 _mcf51xx_sci_polled_init(MCF51XX_SCI_INIT_STRUCT_PTR,
   pointer _PTR_, char _PTR_);
extern uint_32 _mcf51xx_sci_polled_deinit(MCF51XX_SCI_INIT_STRUCT_PTR,
   MCF51XX_SCI_INFO_STRUCT_PTR);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf51xx_sci_polled_install
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install a polled sci device.
*
*END*----------------------------------------------------------------------*/

uint_32 _mcf51xx_sci_polled_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr           identifier,

      /* [IN] The I/O init data pointer */
      MCF51XX_SCI_INIT_STRUCT_CPTR            init_data_ptr,

      /* [IN] The I/O queue size to use */
      uint_32            queue_size
   )
{ /* Body */

   return _io_serial_polled_install(identifier,
      (uint_32 (_CODE_PTR_)(pointer, pointer _PTR_, char _PTR_))_mcf51xx_sci_polled_init,
      (uint_32 (_CODE_PTR_)(pointer, pointer))_mcf51xx_sci_polled_deinit,
      (char    (_CODE_PTR_)(pointer))_mcf51xx_sci_polled_getc,
      (void    (_CODE_PTR_)(pointer, char))_mcf51xx_sci_polled_putc,
      (boolean (_CODE_PTR_)(pointer))_mcf51xx_sci_polled_status,
      (uint_32 (_CODE_PTR_)(pointer, uint_32, pointer))_mcf51xx_sci_polled_ioctl,
      (pointer)init_data_ptr, queue_size);

} /* Endbody */



/*FUNCTION****************************************************************
*
* Function Name    : _mcf51xx_sci_polled_init
* Returned Value   : MQX_OK or a MQX error code.
* Comments         :
*    This function initializes the SCI
*
*END*********************************************************************/

uint_32 _mcf51xx_sci_polled_init
   (
      /* [IN] the initialization information for the device being opened */
      MCF51XX_SCI_INIT_STRUCT_PTR io_init_ptr,

      /* [OUT] the address to store device specific information */
      pointer _PTR_                       io_info_ptr_ptr,

      /* [IN] the rest of the name of the device opened */
      char _PTR_                          open_name_ptr
   )
{ /* Body */
   volatile MCF51XX_SCI_STRUCT _PTR_    sci_ptr;
   MCF51XX_SCI_INFO_STRUCT _PTR_        sci_info_ptr;
   uint_32                              channel;
   uint_32                              baud_divisor;

   sci_info_ptr = _mem_alloc_system_zero((uint_32)
      sizeof(MCF51XX_SCI_INFO_STRUCT));

#if MQX_CHECK_MEMORY_ALLOCATION_ERRORS
   if ( sci_info_ptr == NULL ) {
        return(MQX_OUT_OF_MEMORY);
   }/* Endif */
#endif

   *io_info_ptr_ptr = sci_info_ptr;

   /* Save initialization values */
   sci_info_ptr->INIT = *io_init_ptr;

   channel = sci_info_ptr->INIT.DEVICE;

   // init GPIO and clock GATING
   _bsp_serial_io_init(channel);
   
   // get sci address
   sci_ptr = _bsp_get_serial_base_address(channel);
   sci_info_ptr->SCI_PTR = (MCF51XX_SCI_STRUCT_PTR)sci_ptr;

   /* Calculate baud settings */
   /* baud_divisor = clock_speed/ baudrate + 0.5 */
   baud_divisor = (sci_info_ptr->INIT.CLOCK_SPEED + (8 * sci_info_ptr->INIT.BAUD_RATE))/ (16 * sci_info_ptr->INIT.BAUD_RATE);
   if (baud_divisor > 0x1fff)
      return IO_ERROR;
      sci_ptr->SCIBDH = (uchar)((baud_divisor >> 8) & 0xFF);
   sci_ptr->SCIBDL = (uchar)(baud_divisor & 0xFF);

   /* 8-bit mode. Normal operation */
   sci_ptr->SCIC1 = 0;

   /* Receiver interrupt enable. Transmitter and receiver enable */
   sci_ptr->SCIC2 = MCF51XX_SCIC2_RE_MASK + MCF51XX_SCIC2_TE_MASK;

   /* Disable all errors interrupts */ 
   sci_ptr->SCIC3 = 0;

   return( MQX_OK );

} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _mcf51xx_sci_polled_deinit
* Returned Value   : MQX_OK or a mqx error code.
* Comments         :
*    This function de-initializes the SCI.
*
*END*********************************************************************/

uint_32 _mcf51xx_sci_polled_deinit
   (
      /* [IN] the initialization information for the device being opened */
      MCF51XX_SCI_INIT_STRUCT_PTR io_init_ptr,

      /* [IN] the address of the device specific information */
      MCF51XX_SCI_INFO_STRUCT_PTR io_info_ptr
   )
{ /* Body */

   _mem_free(io_info_ptr);

   return(MQX_OK);

} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _mcf51xx_sci_polled_getc
* Returned Value   : char
* Comments         :
*   Return a character when it is available.  This function polls the
* device for input.
*
*************************************************************************/

char _mcf51xx_sci_polled_getc
   (
      /* [IN] the address of the device specific information */
      MCF51XX_SCI_INFO_STRUCT_PTR io_info_ptr
   )
{ /* Body */
   volatile MCF51XX_SCI_STRUCT _PTR_ sci_ptr = io_info_ptr->SCI_PTR;
    
   /* Wait until a character is available */
   while ( !(sci_ptr->SCIS1 & MCF51XX_SCIS1_RDRF_MASK) ) {
   } /* Endwhile */
   return sci_ptr->SCID;
} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _mcf51xx_sci_polled_putc
* Returned Value   : void
* Comments         :
*   Writes the provided character.
*
*END*********************************************************************/

void _mcf51xx_sci_polled_putc
   (
      /* [IN] the address of the device specific information */
      MCF51XX_SCI_INFO_STRUCT_PTR io_info_ptr,

      /* [IN] the character to write */
      char                               c
   )
{ /* Body */
   volatile MCF51XX_SCI_STRUCT _PTR_ sci_ptr = io_info_ptr->SCI_PTR;

   /* Wait until free to send a character */
   while ( !(sci_ptr->SCIS1 & MCF51XX_SCIS1_TDRE_MASK) ) {
   } /* Endwhile */

   sci_ptr->SCID = c;

} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _mcf51xx_sci_polled_status
* Returned Value   : boolean
* Comments         :
*            This function returns TRUE if a character is available
*            on the on I/O device, otherwise it returns FALSE.
*
*END*********************************************************************/

boolean _mcf51xx_sci_polled_status
   (
      /* [IN] the address of the device specific information */
      MCF51XX_SCI_INFO_STRUCT_PTR io_info_ptr
   )
{ /* Body */
   volatile MCF51XX_SCI_STRUCT _PTR_ sci_ptr = io_info_ptr->SCI_PTR;
   if( sci_ptr->SCIS1 & MCF51XX_SCIS1_RDRF_MASK )
        return(TRUE);
   else
        return (FALSE); 
} /* Endbody */


/*FUNCTION****************************************************************
*
* Function Name    : _mcf51xx_sci_polled_ioctl
* Returned Value   : uint_32 MQX_OK or a mqx error code.
* Comments         :
*    This function performs miscellaneous services for
*    the I/O device.
*
*END*********************************************************************/

uint_32 _mcf51xx_sci_polled_ioctl
   (
      /* [IN] the address of the device specific information */
      MCF51XX_SCI_INFO_STRUCT_PTR io_info_ptr,

      /* [IN] The command to perform */
      uint_32                    cmd,

      /* [IN] Parameters for the command */
      uint_32_ptr                param_ptr
   )
{ /* Body */
   volatile MCF51XX_SCI_STRUCT _PTR_  sci_ptr = io_info_ptr->SCI_PTR;
   uint_32                            baud,tmp;

   switch (cmd) {     
      case IO_IOCTL_SERIAL_GET_DATA_BITS:
         tmp = io_info_ptr->INIT.SCIC1_VALUE & MCF51XX_SCIC1_M_MASK;
         *param_ptr = (tmp >> 4) + 8;
         /* return 8 or 9 */
         break;
      case IO_IOCTL_SERIAL_SET_DATA_BITS:
         /* set the 8 bit mode M = 0*/
         tmp = io_info_ptr->INIT.SCIC1_VALUE & ~MCF51XX_SCIC1_M_MASK;
         if(*param_ptr == 9)
             tmp |= MCF51XX_SCIC1_M_MASK;
         io_info_ptr->INIT.SCIC1_VALUE = tmp;
         /* Write back C1 value */
         sci_ptr->SCIC1 = (uint_8) tmp;
         break;
      case IO_IOCTL_SERIAL_GET_BAUD:
         *param_ptr = io_info_ptr->INIT.BAUD_RATE;
         break;
      case IO_IOCTL_SERIAL_SET_BAUD: 
         /* baud_divisor = clock_speed / baudrate + 0.5 */  
         baud = (io_info_ptr->INIT.CLOCK_SPEED + (8 * (*param_ptr))) / (16 * (*param_ptr));
         if (baud > 0x1fff)
             return IO_ERROR_INVALID_IOCTL_CMD;
         io_info_ptr->INIT.BAUD_RATE = *param_ptr;       
         sci_ptr->SCIBDH = (uchar)((baud >> 8) & 0xFF);
         sci_ptr->SCIBDL = (uchar)(baud & 0xFF);      
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
         *param_ptr = sci_ptr->SCIS1 & MCF51XX_SCIS1_TDRE_MASK ? 1 : 0;
         break;
      case IO_IOCTL_SERIAL_CAN_RECEIVE:
         *param_ptr = sci_ptr->SCIS1 & MCF51XX_SCIS1_RDRF_MASK ? 1 : 0;
         break;
      case IO_IOCTL_SERIAL_GET_PARITY:
         tmp = IO_SERIAL_PARITY_NONE;
         if (io_info_ptr->INIT.SCIC1_VALUE & MCF51XX_SCIC1_PE_MASK) {
            if (io_info_ptr->INIT.SCIC1_VALUE & MCF51XX_SCIC1_PT_MASK) {
               tmp = IO_SERIAL_PARITY_ODD;
            } else {
               tmp = IO_SERIAL_PARITY_EVEN;
            }
         }
         *param_ptr = tmp;
         break;
      case IO_IOCTL_SERIAL_SET_PARITY:
         tmp = io_info_ptr->INIT.SCIC1_VALUE & ~(MCF51XX_SCIC1_PT_MASK | MCF51XX_SCIC1_PE_MASK);
         switch (*param_ptr) {
            case IO_SERIAL_PARITY_NONE:
               break;
            case IO_SERIAL_PARITY_ODD:
               tmp |= MCF51XX_SCIC1_PT_MASK | MCF51XX_SCIC1_PE_MASK;
               break;
            case IO_SERIAL_PARITY_EVEN:
               tmp |= MCF51XX_SCIC1_PE_MASK;
               break;
            default:
               return MQX_INVALID_PARAMETER;
         }
         io_info_ptr->INIT.SCIC1_VALUE = tmp;
         sci_ptr->SCIC1 = (uint_8) tmp;      
         break;
       case IO_IOCTL_SERIAL_SET_FLAGS:
         break;
      default:
         return IO_ERROR_INVALID_IOCTL_CMD;
   } /* Endswitch */

   return (MQX_OK);

} /* Endbody */

/* EOF */

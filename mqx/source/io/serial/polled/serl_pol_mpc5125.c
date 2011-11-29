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
* $FileName: serl_pol_mpc5125.c$
* $Version : 3.6.3.0$
* $Date    : Dec-3-2010$
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
#include "serplprv.h"

extern _mqx_uint _mpc5125_serial_polled_init(MPC5125_SERIAL_INIT_STRUCT_PTR, pointer _PTR_, char_ptr);
extern _mqx_uint _mpc5125_serial_polled_deinit(MPC5125_SERIAL_INIT_STRUCT_PTR, MPC5125_SERIAL_INFO_STRUCT_PTR );
static char      _mpc5125_serial_getc(MPC5125_SERIAL_INFO_STRUCT_PTR);
static void      _mpc5125_serial_putc(MPC5125_SERIAL_INFO_STRUCT_PTR, char);
static boolean   _mpc5125_serial_status(MPC5125_SERIAL_INFO_STRUCT_PTR);
extern _mqx_uint _mpc5125_serial_ioctl(MPC5125_SERIAL_INFO_STRUCT_PTR, _mqx_uint, pointer);

#define SERIAL_ERROR_UNABLE_TO_ALLOCATE_FIFO_SLICE  999


const uint_32 _mpc5125_psc_address[] = 
{
   MPC5125_PSC_UART0_OFFSET,
   MPC5125_PSC_UART1_OFFSET,
   MPC5125_PSC_UART2_OFFSET,
   MPC5125_PSC_UART3_OFFSET,
   MPC5125_PSC_UART4_OFFSET,
   MPC5125_PSC_UART5_OFFSET,
   MPC5125_PSC_UART6_OFFSET,
   MPC5125_PSC_UART7_OFFSET,
   MPC5125_PSC_UART8_OFFSET,
   MPC5125_PSC_UART9_OFFSET
};


         




/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_uart_serial_polled_install
* Returned Value   : _mqx_uint a task error code or MQX_OK
* Comments         :
*    Install a polled psc_ptr serial device.
*
*END*----------------------------------------------------------------------*/

_mqx_uint _mpc5125_serial_polled_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr           identifier,

      /* [IN] The I/O init data pointer */
      const MPC5125_SERIAL_INIT_STRUCT _PTR_ init_data_ptr
   )
{

   return _io_serial_polled_install(identifier,
      (_mqx_uint (_CODE_PTR_)(pointer, pointer _PTR_, char _PTR_))  _mpc5125_serial_polled_init,
      (_mqx_uint (_CODE_PTR_)(pointer, pointer))  _mpc5125_serial_polled_deinit,
      (char (_CODE_PTR_)(pointer)) _mpc5125_serial_getc,
      (void (_CODE_PTR_)(pointer, char)) _mpc5125_serial_putc,
      (boolean (_CODE_PTR_)(pointer)) _mpc5125_serial_status,
      (_mqx_uint (_CODE_PTR_)(pointer, _mqx_uint, pointer)) _mpc5125_serial_ioctl,
      (pointer)init_data_ptr, init_data_ptr->QUEUE_SIZE);
} 


extern uint_32 _mpc5125_uart_serial_int_enable(MPC5125_SERIAL_INFO_STRUCT_PTR io_info_ptr);

static uint_32 _mpc5125_serial_reconfigure
   (
      MPC5125_SERIAL_INFO_STRUCT_PTR io_info_ptr
   )
{ 
   MPC5125_PSC_STRUCT_PTR psc_ptr = io_info_ptr->UART_PTR;
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   uint_32 t_slice, r_slice;  
   uint_32 t;
   uint_8  mode;

 
   // turn on PSCx Clock and FIFO Control Clock 
   // The enables are a bit mask (in inverted order) in the SCCR1 reg
   ccm_ptr->SCCR1 |= CCM_SCCR1_FIFOC_EN | (CCM_SCCR1_PSCx_EN_MASK & (1<<(CCM_SCCR1_PSC0_BIT_POSITION-io_info_ptr->INIT.DEVICE)));
   _PSP_SYNC();
  
   // Configuration Sequence for UART Mode
   psc_ptr->CR = PSC_CR_TX_DISABLE | PSC_CR_RX_DISABLE;

   _mpc5125_psc_fifo_slice_free(io_info_ptr->INIT.DEVICE);
  
   t_slice = _mpc5125_psc_fifo_slice_alloc(io_info_ptr->INIT.DEVICE, io_info_ptr->INIT.QUEUE_SIZE);
   r_slice = _mpc5125_psc_fifo_slice_alloc(io_info_ptr->INIT.DEVICE, io_info_ptr->INIT.QUEUE_SIZE);
   if ((t_slice == IO_ERROR) || (r_slice == IO_ERROR)) {
     _mpc5125_psc_fifo_slice_free(io_info_ptr->INIT.DEVICE);
     return SERIAL_ERROR_UNABLE_TO_ALLOCATE_FIFO_SLICE;
   }
   
   psc_ptr->TX_CMD = PSC_FIFO_CMD_RESET_SLICE;
   psc_ptr->RX_CMD = PSC_FIFO_CMD_RESET_SLICE;
   
   psc_ptr->RX_SIZE = io_info_ptr->INIT.QUEUE_SIZE | (r_slice<<16); 
   psc_ptr->TX_SIZE = io_info_ptr->INIT.QUEUE_SIZE | (t_slice<<16);

   psc_ptr->RX_ALARM = min(io_info_ptr->INIT.RX_QUEUE_ALARM,io_info_ptr->INIT.QUEUE_SIZE);
   psc_ptr->TX_ALARM = min(io_info_ptr->INIT.TX_QUEUE_ALARM,io_info_ptr->INIT.QUEUE_SIZE);

   psc_ptr->TX_CMD = PSC_FIFO_CMD_SLICE_EN;
   psc_ptr->RX_CMD = PSC_FIFO_CMD_SLICE_EN;
   _PSP_SYNC();
   
  
   // Select IPB clock source with a 16x sample rate for both Rx and Tx.
   psc_ptr->CSR = PSC_CSR_RCS_IPB_16X|PSC_CSR_TCS_IPB_16X;
   
   // Select UART mode
   psc_ptr->SICR = PSC_SICR_SIM_UART;

   switch (io_info_ptr->INIT.PARITY) {
      case IO_SERIAL_EVEN_PARITY:
         mode = PSC_MR1_PM_WITH_PARITY | PSC_MR1_PT_EVEN;
         break;
      case IO_SERIAL_ODD_PARITY:
         mode = PSC_MR1_PM_WITH_PARITY | PSC_MR1_PT_ODD;
         break;
      case IO_SERIAL_NO_PARITY:
      default:
         mode = PSC_MR1_PM_NO_PARITY;
         break;
   } 

   switch (io_info_ptr->INIT.BITS_PER_CHARACTER) {
      case 5:
         mode |= PSC_MR1_BC_5;
         break;
      case 6:
         mode |= PSC_MR1_BC_6;
         break;
      case 7:
         mode |= PSC_MR1_BC_7;
         break;
      case 8:
      default:
         mode |= PSC_MR1_BC_8;
         break;
   } 

   if (io_info_ptr->CONTROL_BITS & IO_SERIAL_HW_FLOW_CONTROL) {
      mode |= PSC_MR1_RxRTS;
   }

   psc_ptr->MR1 = mode;

   mode = PSC_MR2_CM_NORMAL;

   switch (io_info_ptr->INIT.STOP_BITS)
   {
      case IO_SERIAL_1_5_STOP_BITS:
         if (io_info_ptr->INIT.BITS_PER_CHARACTER == 5) {
            mode |= PSC_MR2_SB_BC5_1_5;
         } else {
            mode |= PSC_MR2_SB_BC58_1_5;
         }
         break;

      case IO_SERIAL_2_STOP_BITS:
         mode |= PSC_MR2_SB_BC58_2;
         break;

      case IO_SERIAL_1_STOP_BIT:
      default:
         if (io_info_ptr->INIT.BITS_PER_CHARACTER == 5) {
            mode |= PSC_MR2_SB_BC5_1;
         } else {
            mode |= PSC_MR2_SB_BC68_1;
         }
         break;
   } 
   
   if (io_info_ptr->CONTROL_BITS & IO_SERIAL_HW_FLOW_CONTROL) {
      mode |= PSC_MR2_TxCTS;
   }
   
   psc_ptr->MR2 = mode;

   // Calculate baud rate
   t = io_info_ptr->INIT.BAUD_RATE  * 16;
   t = io_info_ptr->INIT.CLOCK_SPEED() / t;

   psc_ptr->CTLR = t & 0xff;
   psc_ptr->CTUR = (t & 0xff00) >> 8;

   // Disable interrupts
   psc_ptr->IMR = 0x0000;

   psc_ptr->CR = PSC_CR_RESET_RECEIVER;
   psc_ptr->CR = PSC_CR_RESET_TRANSMITTER;
   psc_ptr->CR = PSC_CR_RESET_ERROR;
   psc_ptr->CR = PSC_CR_RESET_BREAK;

   _bsp_serial_io_init(io_info_ptr->INIT.DEVICE);

   // Enable Tx and Rx
   psc_ptr->CR = PSC_CR_TX_ENABLE | PSC_CR_RX_ENABLE;

   return MQX_OK;
} 



/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_serial_polled_init
* Returned Value   : MQX_OK or a MQX error code.
* Comments         :
*    This function initializes the psc_ptr
*
*END*********************************************************************/

uint_32 _mpc5125_serial_polled_init
   (
      /* [IN] the initialization information for the device being opened */
      MPC5125_SERIAL_INIT_STRUCT_PTR io_init_ptr,

      /* [OUT] the address to store device specific information */
      pointer _PTR_                  io_info_ptr_ptr,

      /* [IN] the rest of the name of the device opened */
      char_ptr                       open_name_ptr
   )
{ 
   MPC5125_SERIAL_INFO_STRUCT_PTR  io_info_ptr;
   MPC5125_PSC_STRUCT_PTR psc_ptr;

   io_info_ptr  = (MPC5125_SERIAL_INFO_STRUCT_PTR)_mem_alloc_system_zero(
      (_mem_size)sizeof(MPC5125_SERIAL_INFO_STRUCT));
#if MQX_CHECK_MEMORY_ALLOCATION_ERRORS
   if (!io_info_ptr) {
      return(MQX_OUT_OF_MEMORY);
   } /* Endif */
#endif

   psc_ptr = MPC5125_PSC_UART_DEVICE_ADDRESS(io_init_ptr->DEVICE);

   *io_info_ptr_ptr      = io_info_ptr;

   io_info_ptr->INIT     = *io_init_ptr;
   io_info_ptr->UART_PTR = psc_ptr;

   return _mpc5125_serial_reconfigure(io_info_ptr);
} 


/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_serial_polled_deinit
* Returned Value   : MQX_OK or a mqx error code.
* Comments         :
*    This function de-initializes the UART
*
*END*********************************************************************/

_mqx_uint _mpc5125_serial_polled_deinit
   (
      /* [IN] the initialization information for the device being opened */
      MPC5125_SERIAL_INIT_STRUCT_PTR io_init_ptr,

      /* [IN] the address of the device specific information */
      MPC5125_SERIAL_INFO_STRUCT_PTR io_info_ptr
   )
{ 
   _mem_free((pointer)io_info_ptr);

   return MQX_OK;
} 



/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_serial_getc
* Returned Value   : char
* Comments         :
*   Return a character when it is available.  This function polls the
* device for input.
*
*************************************************************************/

static char _mpc5125_serial_getc
   (
      /* [IN] the address of the device specific information */
      MPC5125_SERIAL_INFO_STRUCT_PTR io_info_ptr
   )
{ 
   MPC5125_PSC_STRUCT_PTR psc_ptr = io_info_ptr->UART_PTR;
   uchar data;

   while ((psc_ptr->RX_STAT & PSC_FIFO_SR_DATA_READY) == 0) {} 

   data = *((uchar_ptr)&psc_ptr->RX_DATA);

   io_info_ptr->RX_CHARS++;

   return (char)data;
} 



/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_serial_putc
* Returned Value   : void
* Comments         :
*   Writes the provided character.
*
*END*********************************************************************/

static void _mpc5125_serial_putc
   (
      /* [IN] the address of the device specific information */
      MPC5125_SERIAL_INFO_STRUCT_PTR io_info_ptr,

      /* [IN] the character to write */
      char                           c
   )
{ 
   MPC5125_PSC_STRUCT_PTR psc_ptr = io_info_ptr->UART_PTR;

   while ((psc_ptr->SR & PSC_SR_TxEMP)==0) {} 
   *((uchar_ptr)&psc_ptr->TX_DATA) = c;

   io_info_ptr->TX_CHARS++;
} 


/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_serial_status
* Returned Value   : boolean
* Comments         :
*            This function returns TRUE if a character is available
*            on the on I/O device, otherwise it returns FALSE.
*
*END*********************************************************************/

static boolean _mpc5125_serial_status
   (
      /* [IN] the address of the device specific information */
      MPC5125_SERIAL_INFO_STRUCT_PTR io_info_ptr
   )
{ 
   MPC5125_PSC_STRUCT_PTR psc_ptr = io_info_ptr->UART_PTR;

   return (psc_ptr->RX_STAT & PSC_FIFO_SR_DATA_READY) != 0;
} 


/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_serial_ioctl
* Returned Value   : uint_32 MQX_OK or a mqx error code.
* Comments         :
*    This function performs miscellaneous services for
*    the I/O device.
*
*END*********************************************************************/

uint_32 _mpc5125_serial_ioctl
   (
      /* [IN] the address of the device specific information */
      MPC5125_SERIAL_INFO_STRUCT_PTR io_info_ptr,

      /* [IN] The command to perform */
      _mqx_uint                      cmd,

      /* [IN] Parameters for the command */
      pointer                        param_ptr
   )
{ 
   uint_32_ptr u32_ptr = (uint_32_ptr)param_ptr;
   MPC5125_SERIAL_INIT_STRUCT_PTR io_init_ptr;
   uint_32 tmp;

   switch (cmd) {
   case IO_IOCTL_SERIAL_GET_STOP_BITS:
      *u32_ptr = (io_info_ptr->INIT.STOP_BITS == IO_SERIAL_1_STOP_BIT) ? 1 : 2;
      return MQX_OK;
   case IO_IOCTL_SERIAL_SET_STOP_BITS:
      switch (*u32_ptr) {
         case IO_SERIAL_STOP_BITS_1_5:
            io_info_ptr->INIT.STOP_BITS = IO_SERIAL_1_5_STOP_BITS;
            break;
         case IO_SERIAL_STOP_BITS_2:
            io_info_ptr->INIT.STOP_BITS = IO_SERIAL_2_STOP_BITS;
            break;
         default:
            io_info_ptr->INIT.STOP_BITS = IO_SERIAL_1_STOP_BIT;
            break;
      } /* Endswitch */
      return _mpc5125_serial_reconfigure(io_info_ptr);

   case IO_IOCTL_SERIAL_GET_DATA_BITS:
      *u32_ptr = io_info_ptr->INIT.BITS_PER_CHARACTER;
      return MQX_OK;
   case IO_IOCTL_SERIAL_SET_DATA_BITS:
      io_info_ptr->INIT.BITS_PER_CHARACTER = *u32_ptr;
      return _mpc5125_serial_reconfigure(io_info_ptr);

   case IO_IOCTL_SERIAL_GET_BAUD:
      *u32_ptr = io_info_ptr->INIT.BAUD_RATE;
      return MQX_OK;
   case IO_IOCTL_SERIAL_SET_BAUD:
      io_info_ptr->INIT.BAUD_RATE = *u32_ptr;
      return _mpc5125_serial_reconfigure(io_info_ptr);

   case IO_IOCTL_SERIAL_GET_STATS:
      *u32_ptr++ = io_info_ptr->RX_DROPPED_INPUT;
      *u32_ptr++ = io_info_ptr->INTERRUPTS;
      *u32_ptr++ = io_info_ptr->RX_GOOD_CHARS;
      *u32_ptr++ = io_info_ptr->RX_CHARS;
      *u32_ptr++ = io_info_ptr->TX_CHARS;
      *u32_ptr++ = io_info_ptr->RX_PARITY_ERRORS;
      *u32_ptr++ = io_info_ptr->RX_FRAMING_ERRORS;
      *u32_ptr++ = io_info_ptr->RX_OVERRUNS;
      *u32_ptr++ = io_info_ptr->RX_BREAKS;
      break;

   case IO_IOCTL_SERIAL_CLEAR_STATS:
      io_info_ptr->RX_DROPPED_INPUT  = 0;
      io_info_ptr->INTERRUPTS        = 0;
      io_info_ptr->RX_GOOD_CHARS     = 0;
      io_info_ptr->RX_CHARS          = 0;
      io_info_ptr->TX_CHARS          = 0;
      io_info_ptr->RX_PARITY_ERRORS  = 0;
      io_info_ptr->RX_FRAMING_ERRORS = 0;
      io_info_ptr->RX_OVERRUNS       = 0;
      io_info_ptr->RX_BREAKS         = 0;
      break;

   case IO_IOCTL_SERIAL_GET_CONFIG: 
      io_init_ptr = (MPC5125_SERIAL_INIT_STRUCT_PTR)param_ptr;
      *io_init_ptr = io_info_ptr->INIT;
      break;
      
   case IO_IOCTL_SERIAL_GET_PARITY:
      *(uint_32_ptr)param_ptr = io_info_ptr->INIT.PARITY;
      break;
   case IO_IOCTL_SERIAL_SET_PARITY:
      switch (*(uint_32_ptr)param_ptr) {
         case IO_SERIAL_PARITY_NONE:
         case IO_SERIAL_PARITY_ODD:
         case IO_SERIAL_PARITY_EVEN:
            break;
         default:
            return MQX_INVALID_PARAMETER;
      }
      io_info_ptr->INIT.PARITY = *(uint_32_ptr)param_ptr;
      return _mpc5125_serial_reconfigure(io_info_ptr);
   case IO_IOCTL_SERIAL_GET_HW_SIGNAL:
      tmp = 0;
      if (0 == (io_info_ptr->UART_PTR->IPCR & PSC_IPCR_CTS)) {
         tmp |= IO_SERIAL_CTS;
      }
      if (0 == (io_info_ptr->UART_PTR->IPCR & PSC_IPCR_DCD)) {
         tmp |= IO_SERIAL_DCD;
      }
      if (io_info_ptr->CONTROL_BITS & PSC_OP_RTS) {
         tmp |= IO_SERIAL_RTS;
      }
      *(uint_32_ptr)param_ptr = tmp;
      break;
   case IO_IOCTL_SERIAL_SET_HW_SIGNAL:  /* Assert */
      if ((*(uint_32_ptr)param_ptr) & IO_SERIAL_RTS) {
         if (io_info_ptr->CONTROL_BITS & IO_SERIAL_HW_FLOW_CONTROL) {
            return MQX_IO_OPERATION_NOT_AVAILABLE;
         }
         io_info_ptr->CONTROL_BITS |= PSC_OP_RTS;
      }
      else {
         return MQX_INVALID_PARAMETER;
      }
      io_info_ptr->UART_PTR->OP1 = PSC_OP_RTS;
      break;
   case IO_IOCTL_SERIAL_CLEAR_HW_SIGNAL:  /* Negate */
      if ((*(uint_32_ptr)param_ptr) & IO_SERIAL_RTS) {
         if (io_info_ptr->CONTROL_BITS & IO_SERIAL_HW_FLOW_CONTROL) {
            return MQX_IO_OPERATION_NOT_AVAILABLE;
         }
         io_info_ptr->CONTROL_BITS &= (~PSC_OP_RTS);
      }
      else {
         return MQX_INVALID_PARAMETER;
      }
      io_info_ptr->UART_PTR->OP0 = PSC_OP_RTS;
      break;         
   case IO_IOCTL_SERIAL_SET_FLAGS:
      /* automatic HW flow control in polled mode only */
      if (0 == io_info_ptr->VECTOR) {
         io_info_ptr->CONTROL_BITS &= (~IO_SERIAL_HW_FLOW_CONTROL);
         io_info_ptr->CONTROL_BITS |= ((*(uint_32_ptr)param_ptr) & IO_SERIAL_HW_FLOW_CONTROL);
         return _mpc5125_serial_reconfigure(io_info_ptr);
      }
      break;
   }

   return IO_ERROR_INVALID_IOCTL_CMD;

} 

/*FUNCTION****************************************************************
*
* Function Name    : _mpc5125_serial_display_registers
* Returned Value   : uint_32 MQX_OK or a mqx error code.
* Comments         :
*    This function performs miscellaneous services for
*    the I/O device.
*
*END*********************************************************************/

uint_32 _mpc5125_serial_display_registers(uint_32 dev)
{
   MPC5125_PSC_STRUCT_PTR psc_ptr = MPC5125_PSC_UART_DEVICE_ADDRESS(dev);

   printf("0x%08x: 0x%08x Mode Register 1\n", &psc_ptr->MR1, psc_ptr->MR1);   
   printf("0x%08x: 0x%08x Mode Register 2\n", &psc_ptr->MR2, psc_ptr->MR2);   
   printf("0x%08x: 0x%08x Status Register\n", &psc_ptr->SR, psc_ptr->SR);    
   printf("0x%08x: 0x%08x Command Register\n", &psc_ptr->CSR, psc_ptr->CSR);   
   printf("0x%08x: 0x%08x Command Register\n", &psc_ptr->CR, psc_ptr->CR);    
   printf("0x%08x: 0x%08x Rx Buffer Register\n", &psc_ptr->buffer,  psc_ptr->buffer);       
   printf("0x%08x: 0x%08x Input Port Change Register\n", &psc_ptr->IPCR,psc_ptr->IPCR);  
   printf("0x%08x: 0x%08x Input Port Change Register\n", &psc_ptr->ACR, psc_ptr->ACR);   
   printf("0x%08x: 0x%08x Interrupt Status Register\n", &psc_ptr->ISR, psc_ptr->ISR);   
   printf("0x%08x: 0x%08x Interrupt Mask Register\n", &psc_ptr->IMR, psc_ptr->IMR);   
   printf("0x%08x: 0x%08x Counter Timer Upper Register\n", &psc_ptr->CTUR,psc_ptr->CTUR);  
   printf("0x%08x: 0x%08x Counter Timer Lower Register\n", &psc_ptr->CTLR,psc_ptr->CTLR);  
   printf("0x%08x: 0x%08x Codec Clock Register\n", &psc_ptr->CCR, psc_ptr->CCR);   
   printf("0x%08x: 0x%08x Input Port Register\n", &psc_ptr->IP,  psc_ptr->IP);    
   printf("0x%08x: 0x%08x Output Port 1 Bit Set\n", &psc_ptr->OP1, psc_ptr->OP1);   
   printf("0x%08x: 0x%08x Output Port 0 Bit Set\n", &psc_ptr->OP0, psc_ptr->OP0);   
   printf("0x%08x: 0x%08x PSC Control Register\n", &psc_ptr->SICR, psc_ptr->SICR);  
   printf("0x%08x: 0x%08x TX Command register\n", &psc_ptr->TX_CMD, psc_ptr->TX_CMD);       
   printf("0x%08x: 0x%08x TX Alarm level\n", &psc_ptr->TX_ALARM, psc_ptr->TX_ALARM);     
   printf("0x%08x: 0x%08x TX Status register\n", &psc_ptr->TX_SR, psc_ptr->TX_SR); 
   printf("0x%08x: 0x%08x TX Interrupt status register\n", &psc_ptr->TX_ISR, psc_ptr->TX_ISR);       
   printf("0x%08x: 0x%08x TX Interrupt mask register\n", &psc_ptr->TX_IMR, psc_ptr->TX_IMR);       
   printf("0x%08x: 0x%08x TX FIFO count\n", &psc_ptr->TX_COUNT, psc_ptr->TX_COUNT);     
   printf("0x%08x: 0x%08x TX TX FIFO pointer\n", &psc_ptr->TX_POINTER, psc_ptr->TX_POINTER);   
   printf("0x%08x: 0x%08x TX FIFO size register\n", &psc_ptr->TX_SIZE, psc_ptr->TX_SIZE);      
   printf("0x%08x: 0x%08x TX FIFO data register\n", &psc_ptr->TX_DATA, psc_ptr->TX_DATA);      
   printf("0x%08x: 0x%08x RX Command register\n", &psc_ptr->RX_CMD, psc_ptr->RX_CMD);       
   printf("0x%08x: 0x%08x RX Alarm level\n", &psc_ptr->RX_ALARM, psc_ptr->RX_ALARM);     
   printf("0x%08x: 0x%08x RX Status register\n", &psc_ptr->RX_STAT, psc_ptr->RX_STAT);      
   printf("0x%08x: 0x%08x RX Interrupt status register\n", &psc_ptr->RX_ISR, psc_ptr->RX_ISR);       
   printf("0x%08x: 0x%08x RX Interrupt mask register\n", &psc_ptr->RX_IMR, psc_ptr->RX_IMR);       
   printf("0x%08x: 0x%08x RX FIFO count\n", &psc_ptr->RX_COUNT,  psc_ptr->RX_COUNT);     
   printf("0x%08x: 0x%08x RX FIFO pointer\n", &psc_ptr->RX_POINTER, psc_ptr->RX_POINTER);   
   printf("0x%08x: 0x%08x RX FIFO size register\n", &psc_ptr->RX_SIZE, psc_ptr->RX_SIZE);      
   printf("0x%08x: 0x%08x RX FIFO data register\n", &psc_ptr->RX_DATA, psc_ptr->RX_DATA);      
} 

/* EOF */

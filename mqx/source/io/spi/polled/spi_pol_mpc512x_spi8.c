/**HEADER********************************************************************
* 
* Copyright (c) 2009 Freescale Semiconductor;
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
* $FileName: spi_pol_mpc512x_spi8.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   The file contains low level SPI driver functions for 51xx Coldfire family.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <io_prv.h>
#include <fio_prv.h>
#include "spi.h"
#include "spi_pol_prv.h"
#include "spi_mpc512x_prv.h"

#define SET_BAUDRATE_FAIL                        998
#define SPI_ERROR_UNABLE_TO_ALLOCATE_FIFO_SLICE  999


uint_32 _mpc512x_spi_polled_init(MPC512X_SPI_INIT_STRUCT_PTR, pointer _PTR_, char_ptr);
uint_32 _mpc512x_spi_polled_ioctl(MPC512X_SPI_INFO_STRUCT_PTR, uint_32, uint_32_ptr, uint_32);

static uint_32 _mpc512x_spi_polled_deinit(IO_SPI_POLLED_DEVICE_STRUCT_PTR, MPC512X_SPI_INFO_STRUCT_PTR);
static uint_32 _mpc512x_spi_polled_rx(IO_SPI_POLLED_DEVICE_STRUCT_PTR, uchar_ptr, uint_32);
static uint_32 _mpc512x_spi_polled_tx(IO_SPI_POLLED_DEVICE_STRUCT_PTR, uchar_ptr, uint_32);
static uint_8  _mpc512x_spi_polled_tx_rx(MPC512X_SPI_INFO_STRUCT_PTR, uint_8, uint_8);
      
/*FUNCTION****************************************************************
* 
* Function Name    : _mpc512x_spi_polled_install
* Returned Value   : MQX error code
* Comments         :
*    Install an SPI device.
*
*END*********************************************************************/
uint_32 _mpc512x_spi_polled_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr           identifier,
  
      /* [IN] The I/O init data pointer */
      MPC512X_SPI_INIT_STRUCT_CPTR init_data_ptr
   )
{ /* Body */
   return _io_spi_polled_install(identifier,
      (uint_32 (_CODE_PTR_)(pointer, pointer _PTR_, char_ptr))_mpc512x_spi_polled_init,
      (uint_32 (_CODE_PTR_)(pointer, pointer))_mpc512x_spi_polled_deinit,
      (_mqx_int (_CODE_PTR_)(pointer, char_ptr, int_32))_mpc512x_spi_polled_rx,
      (_mqx_int (_CODE_PTR_)(pointer, char_ptr, int_32))_mpc512x_spi_polled_tx,
      (_mqx_int (_CODE_PTR_)(pointer, uint_32, _mqx_uint_ptr, _mqx_uint))_mpc512x_spi_polled_ioctl, 
      (pointer)init_data_ptr);
} /* EndBody */

/*FUNCTION****************************************************************
* 
* Function Name    : _mpc5125_spi_configure  
* Returned Value   : MQX error code
* Comments         :
*    
*
*END*********************************************************************/
static uint_32 _mpc5125_spi_configure
   (
      MPC512X_SPI_INFO_STRUCT_PTR spi_info_ptr
   )
{ /* Body */
   MPC5125_PSC_STRUCT_PTR psc_ptr = spi_info_ptr->SPI_PTR;
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   uint_32 t_slice, r_slice;  
   uint_32 t;
   uint_32 SICR;   
 
   /* turn on PSCx Clock and FIFO Control Clock */
   /* The enables are a bit mask (in inverted order) in the SCCR1 reg */
   ccm_ptr->SCCR1 |= CCM_SCCR1_FIFOC_EN | (CCM_SCCR1_PSCx_EN_MASK & (1<<(CCM_SCCR1_PSC0_BIT_POSITION-spi_info_ptr->INIT.CHANNEL)));
   _PSP_SYNC();
  
   // Configuration Sequence for UART Mode
   psc_ptr->CR = PSC_CR_TX_DISABLE | PSC_CR_RX_DISABLE;

   _mpc5125_psc_fifo_slice_free(spi_info_ptr->INIT.CHANNEL);
  
   t_slice = _mpc5125_psc_fifo_slice_alloc(spi_info_ptr->INIT.CHANNEL, spi_info_ptr->INIT.QUEUE_SIZE);
   r_slice = _mpc5125_psc_fifo_slice_alloc(spi_info_ptr->INIT.CHANNEL, spi_info_ptr->INIT.QUEUE_SIZE);
   if ((t_slice == IO_ERROR) || (r_slice == IO_ERROR)) {
     _mpc5125_psc_fifo_slice_free(spi_info_ptr->INIT.CHANNEL);
     return SPI_ERROR_UNABLE_TO_ALLOCATE_FIFO_SLICE;
   }
   
   psc_ptr->TX_CMD = PSC_FIFO_CMD_RESET_SLICE;
   psc_ptr->RX_CMD = PSC_FIFO_CMD_RESET_SLICE;
   
   psc_ptr->RX_SIZE = spi_info_ptr->INIT.QUEUE_SIZE | (r_slice<<16); 
   psc_ptr->TX_SIZE = spi_info_ptr->INIT.QUEUE_SIZE | (t_slice<<16);

   psc_ptr->RX_ALARM = min(spi_info_ptr->INIT.RX_QUEUE_ALARM,spi_info_ptr->INIT.QUEUE_SIZE);
   psc_ptr->TX_ALARM = min(spi_info_ptr->INIT.TX_QUEUE_ALARM,spi_info_ptr->INIT.QUEUE_SIZE);

   psc_ptr->TX_CMD = PSC_FIFO_CMD_SLICE_EN;
   psc_ptr->RX_CMD = PSC_FIFO_CMD_SLICE_EN;
   _PSP_SYNC();
   
   SICR = PSC_SICR_SIM_CODEC_8 | PSC_SICR_SPI | PSC_SICR_GenClk ;
   /* Set transfer mode */
   if (spi_info_ptr->INIT.TRANSFER_MODE == SPI_DEVICE_SLAVE_MODE)
   {
       SICR &= ~ PSC_SICR_MSTR;
   }
   else if (spi_info_ptr->INIT.TRANSFER_MODE == SPI_DEVICE_MASTER_MODE)
   {
      SICR |= PSC_SICR_MSTR;
   }
   else
      return SPI_ERROR_MODE_INVALID; 
   
   /* Set up SPI clock polarity and phase */
   switch (spi_info_ptr->INIT.CLOCK_POL_PHASE)
   {
   case (SPI_CLK_POL_PHA_MODE0):
       /* Inactive state of SPI_CLK = logic 0 */
        SICR &= (~ PSC_SICR_CPOL);
       /* SPI_CLK transitions middle of bit timing */
        SICR &= (~ PSC_SICR_CPHA);
      break;
   case (SPI_CLK_POL_PHA_MODE1):
       /* Inactive state of SPI_CLK = logic 0 */
        SICR &= (~ PSC_SICR_CPOL);
       /* SPI_CLK transitions begining of bit timing */
        SICR |= PSC_SICR_CPHA;
      break;
   case (SPI_CLK_POL_PHA_MODE2):
       /* Inactive state of SPI_CLK = logic 1 */
        SICR |= PSC_SICR_CPOL;
       /* SPI_CLK transitions middle of bit timing */
        SICR &= (~ PSC_SICR_CPHA);
      break;
   case (SPI_CLK_POL_PHA_MODE3):
       /* Inactive state of SPI_CLK = logic 1 */
        SICR |= PSC_SICR_CPOL;
       /* SPI_CLK transitions begining of bit timing */
        SICR |= PSC_SICR_CPHA;
      break;
   default:
      return SPI_ERROR_MODE_INVALID;       
   }
      
   psc_ptr->SICR = SICR;
                                 
   _bsp_set_psc_clock(spi_info_ptr->INIT.CHANNEL, BSP_PSC_MCLK_CLOCK);
   
   psc_ptr->MR2 = PSC_MR2_CM_NORMAL;

   /* Calculate baud rate */
   t = spi_info_ptr->INIT.BAUD_RATE;
   t = (spi_info_ptr->INIT.CLOCK_SPEED / t) - 1;
   if(t < 3) {
      return SET_BAUDRATE_FAIL;
   }

   psc_ptr->CCR = (t << 8) & 0xFFFF00;
   psc_ptr->CTUR = 0x00;
   psc_ptr->CTLR = 0x84;
   /* Disable interrupts */
   psc_ptr->IMR = 0x0000;

   psc_ptr->CR = PSC_CR_RESET_RECEIVER;
   psc_ptr->CR = PSC_CR_RESET_TRANSMITTER;
   psc_ptr->CR = PSC_CR_RESET_ERROR;
   psc_ptr->CR = PSC_CR_RESET_BREAK;

   _bsp_spi_io_init(spi_info_ptr->INIT.CHANNEL);

   /* Enable Tx and Rx */
   psc_ptr->CR = PSC_CR_TX_ENABLE | PSC_CR_RX_ENABLE;

   return MQX_OK;
} /* EndBody */

/*FUNCTION****************************************************************
* 
* Function Name    : _mpc512x_spi_polled_init  
* Returned Value   : MQX error code
* Comments         :
*    This function initializes the SPI module 
*
*END*********************************************************************/
uint_32 _mpc512x_spi_polled_init
(
   /* [IN] The initialization information for the device being opened */
   MPC512X_SPI_INIT_STRUCT_PTR  spi_init_ptr,

   /* [OUT] The address to store device specific information */
   pointer _PTR_                 io_info_ptr_ptr,  

   /* [IN] The rest of the name of the device opened */
   char_ptr                      open_name_ptr
)
{ /* Body */
   
   MPC512X_SPI_INFO_STRUCT_PTR    io_info_ptr;
   MPC5125_PSC_STRUCT_PTR         spi_ptr;
   uint_32                        i;
   
   spi_ptr = MPC5125_PSC_UART_DEVICE_ADDRESS(spi_init_ptr->CHANNEL);
   
   if (_bsp_spi_io_init (spi_init_ptr->CHANNEL) == -1)
   {
      return SPI_ERROR_CHANNEL_INVALID;
   }
   
   /* Initialize internal data */
   io_info_ptr = (MPC512X_SPI_INFO_STRUCT _PTR_)_mem_alloc_system_zero((uint_32)sizeof(MPC512X_SPI_INFO_STRUCT));
   if (io_info_ptr == NULL) 
   {
      return MQX_OUT_OF_MEMORY;
   }
   _mem_set_type(io_info_ptr,MEM_TYPE_IO_SPI_INFO_STRUCT);

   *io_info_ptr_ptr = io_info_ptr;
   
   io_info_ptr->SPI_PTR            = spi_ptr;
   io_info_ptr->INIT               = *spi_init_ptr;
   io_info_ptr->RECEIVING          = 0;
   io_info_ptr->ONTHEWAY           = 0;
   io_info_ptr->RX_REQUEST         = 0;
   io_info_ptr->RX_BUFFER          = NULL;
   io_info_ptr->RX_IN              = 0;
   io_info_ptr->RX_OUT             = 0;
   io_info_ptr->TX_BUFFER          = NULL;
   io_info_ptr->TX_IN              = 0;
   io_info_ptr->TX_OUT             = 0;
   io_info_ptr->STATS.INTERRUPTS   = 0;
   io_info_ptr->STATS.RX_PACKETS   = 0;
   io_info_ptr->STATS.RX_OVERFLOWS = 0;
   io_info_ptr->STATS.TX_PACKETS   = 0;
   io_info_ptr->STATS.TX_ABORTS    = 0;
   io_info_ptr->STATS.TX_UNDERFLOWS= 0;
   io_info_ptr->CS                 = spi_init_ptr->CS;
   io_info_ptr->CS_ACTIVE          = 0;
   for (i = 0; i < MPC512X_SPI_CS_COUNT; i++)
   {
      io_info_ptr->CS_CALLBACK[i] = NULL;
      io_info_ptr->CS_USERDATA[i] = NULL;
   }
   if(MQX_OK != _mpc5125_spi_configure(io_info_ptr)) { 
      _lwmem_free(*io_info_ptr_ptr);
      *io_info_ptr_ptr = NULL;
      return SPI_ERROR_TRANSFER_MODE_INVALID;
   };
 } /* EndBody */

/*FUNCTION****************************************************************
* 
* Function Name    : _mpc512x_spi_polled_deinit  
* Returned Value   : MQX error code
* Comments         :
*    This function de-initializes the SPI module 
*
*END*********************************************************************/
static uint_32 _mpc512x_spi_polled_deinit
   (
      /* [IN] The device information */
      IO_SPI_POLLED_DEVICE_STRUCT_PTR io_dev_ptr,

      /* [IN] The address of the device specific information */
      MPC512X_SPI_INFO_STRUCT_PTR    io_info_ptr
   )
{ /* Body */
   MPC5125_PSC_STRUCT_PTR             spi_ptr;
   uint_32                            index;

   if ((NULL == io_info_ptr) || (NULL == io_dev_ptr)) 
   {
      return SPI_ERROR_DEINIT_FAILED;
   }

   /* Disable the SPI */
   spi_ptr = io_info_ptr->SPI_PTR;
   spi_ptr->CR = PSC_CR_TX_DISABLE | PSC_CR_RX_DISABLE;

   /* Disable all chip selects */
   if (spi_ptr->SICR & PSC_SICR_MSTR) 
   {
      for (index = 0; index < MPC512X_SPI_CS_COUNT; index++)
      {
         if ((NULL != io_info_ptr->CS_CALLBACK[index]) && (0 != (io_info_ptr->CS_ACTIVE & (1 << index))))
         {
            io_info_ptr->CS_CALLBACK[index] (1 << index, 1, io_info_ptr->CS_USERDATA[index]);
         }                
      }
      io_info_ptr->CS_ACTIVE = 0;
   }
   
   _mem_free(io_dev_ptr->DEV_INFO_PTR);
   io_dev_ptr->DEV_INFO_PTR = NULL;
   return SPI_OK;
} /* EndBody */

/*FUNCTION****************************************************************
* 
* Function Name    : _mpc512x_spi_polled_ioctl
* Returned Value   : MQX error code
* Comments         : 
*    This function performs miscellaneous services for
*    the SPI I/O device.  
*
*END*********************************************************************/
uint_32 _mpc512x_spi_polled_ioctl
   (
      /* [IN] The address of the device specific information */
      MPC512X_SPI_INFO_STRUCT_PTR io_info_ptr,

      /* [IN] The command to perform */
      uint_32                     cmd,

      /* [IN/OUT] Parameters for the command */
      uint_32_ptr                 param_ptr,
      
      /* [IN] Opening flags */
      uint_32                     flags
   )
{ /* Body */   
   MPC5125_PSC_STRUCT_PTR         spi_ptr;
   SPI_CS_CALLBACK_STRUCT_PTR     callbacks;
   uint_32                        index;
   uint_32                        result = SPI_OK;
   uint_32                        val, num, size;
   SPI_READ_WRITE_STRUCT_PTR      rw_ptr;
   uchar_ptr                      input, output;
  
   spi_ptr = io_info_ptr->SPI_PTR;
   switch (cmd) 
   {
      case IO_IOCTL_SPI_GET_BAUD:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            uint_32 bdiv;
            bdiv = (spi_ptr->CCR & 0x00FF00) >> 8;
            *param_ptr = (uint_32)((io_info_ptr->INIT.CLOCK_SPEED) / (bdiv + 1));
         }
         break;
      case IO_IOCTL_SPI_SET_BAUD:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else if (0 == (*param_ptr)) 
         {
            result = SPI_ERROR_BAUD_RATE_INVALID;
         } 
         else 
         {
            io_info_ptr->INIT.BAUD_RATE = *param_ptr;
            if(MQX_OK != _mpc5125_spi_configure(io_info_ptr)) {            
               return SET_BAUDRATE_FAIL;
            }
         }
         break;
     case IO_IOCTL_SPI_GET_MODE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else
         {
            if (spi_ptr->SICR & PSC_SICR_CPOL)
            {
               if (spi_ptr->SICR & PSC_SICR_CPHA)
               {
                  *param_ptr = SPI_CLK_POL_PHA_MODE3;
               }
               else
               {
                  *param_ptr = SPI_CLK_POL_PHA_MODE2;
               }
            }
            else
            {
               if (spi_ptr->SICR & PSC_SICR_CPHA)
               {
                  *param_ptr = SPI_CLK_POL_PHA_MODE1;
               }
               else
               {
                  *param_ptr = SPI_CLK_POL_PHA_MODE0;
               }
            }
         }
         break;
      case IO_IOCTL_SPI_SET_MODE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else
         {
            /* Disable SPI module */
            spi_ptr->CR = PSC_CR_TX_DISABLE | PSC_CR_RX_DISABLE;
            switch (*param_ptr)
            {
               case (SPI_CLK_POL_PHA_MODE0):
                  /* Inactive state of SPI_CLK = logic 0 */
                  spi_ptr->SICR &= (~ PSC_SICR_CPOL);
                  /* SPI_CLK transitions middle of bit timing */
                  spi_ptr->SICR &= (~ PSC_SICR_CPHA);
                  break;
               case (SPI_CLK_POL_PHA_MODE1):
                  /* Inactive state of SPI_CLK = logic 0 */
                  spi_ptr->SICR &= (~ PSC_SICR_CPOL);
                  /* SPI_CLK transitions begining of bit timing */
                  spi_ptr->SICR |= PSC_SICR_CPHA;
                  break;
               case (SPI_CLK_POL_PHA_MODE2):
                  /* Inactive state of SPI_CLK = logic 1 */
                  spi_ptr->SICR |= PSC_SICR_CPOL;
                  /* SPI_CLK transitions middle of bit timing */
                  spi_ptr->SICR &= (~ PSC_SICR_CPHA);
                  break;
               case (SPI_CLK_POL_PHA_MODE3):
                  /* Inactive state of SPI_CLK = logic 1 */
                  spi_ptr->SICR |= PSC_SICR_CPOL;
                  /* SPI_CLK transitions begining of bit timing */
                  spi_ptr->SICR |= PSC_SICR_CPHA;
                  break;
               default:
                  result = SPI_ERROR_MODE_INVALID;
                  break;
             }
             /* Enable SPI module */
             spi_ptr->CR = PSC_CR_TX_ENABLE | PSC_CR_RX_ENABLE;
         }
         break;
      case IO_IOCTL_SPI_GET_TRANSFER_MODE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else
         {
            if (spi_ptr->SICR & PSC_SICR_MSTR) 
            {
               *param_ptr = SPI_DEVICE_MASTER_MODE;
            }
            else 
            {
               *param_ptr = SPI_DEVICE_SLAVE_MODE;
            }
         }
         break;
      case IO_IOCTL_SPI_SET_TRANSFER_MODE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else
         {
            /* Disable SPI module */
            spi_ptr->CR = PSC_CR_TX_DISABLE | PSC_CR_RX_DISABLE;
            switch (*param_ptr)
            {
               case SPI_DEVICE_SLAVE_MODE:
                  spi_ptr->SICR &= ~ PSC_SICR_MSTR;
                  break;
               case SPI_DEVICE_MASTER_MODE:
                  spi_ptr->SICR |= PSC_SICR_MSTR;
                  break;
               default:
                  result = SPI_ERROR_TRANSFER_MODE_INVALID;            
                  break;
            }
            /* Enable SPI module */ 
            spi_ptr->CR = PSC_CR_TX_ENABLE | PSC_CR_RX_ENABLE;         
         }
         break;
      case IO_IOCTL_SPI_GET_ENDIAN:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else if (spi_ptr->SICR & PSC_SICR_SHDIR_LSB)
         {
            *param_ptr = SPI_DEVICE_LITTLE_ENDIAN;   
         }
         else
         {
            *param_ptr = SPI_DEVICE_BIG_ENDIAN; 
         }
         break;
      case IO_IOCTL_SPI_SET_ENDIAN:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else if (*param_ptr == SPI_DEVICE_LITTLE_ENDIAN)
         {
            spi_ptr->SICR |= PSC_SICR_SHDIR_LSB;
         }
         else if (*param_ptr == SPI_DEVICE_BIG_ENDIAN)
         {
            spi_ptr->SICR &= ~ PSC_SICR_SHDIR_LSB;
         }
         else
         {
            result = SPI_ERROR_ENDIAN_INVALID;
         }
         break;
      case IO_IOCTL_SPI_GET_STATS:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            *((SPI_STATISTICS_STRUCT_PTR)param_ptr) = io_info_ptr->STATS;
         }
         break;
      case IO_IOCTL_SPI_CLEAR_STATS:
         io_info_ptr->STATS.INTERRUPTS    = 0;
         io_info_ptr->STATS.RX_PACKETS    = 0;
         io_info_ptr->STATS.RX_OVERFLOWS  = 0;
         io_info_ptr->STATS.TX_PACKETS    = 0;
         io_info_ptr->STATS.TX_ABORTS     = 0;
         io_info_ptr->STATS.TX_UNDERFLOWS = 0;
         break;
      case IO_IOCTL_FLUSH_OUTPUT:
      case IO_IOCTL_SPI_FLUSH_DEASSERT_CS:
         if ((0 == (flags & SPI_FLAG_NO_DEASSERT_ON_FLUSH)) || (IO_IOCTL_SPI_FLUSH_DEASSERT_CS == cmd))
         {
            /* Deassert all chip selects */
            if (spi_ptr->SICR & PSC_SICR_MSTR) 
            {
               for (index = 0; index < MPC512X_SPI_CS_COUNT; index++)
               {
                  if ((NULL != io_info_ptr->CS_CALLBACK[index]) && (0 != (io_info_ptr->CS_ACTIVE & (1 << index))))
                  {
                     io_info_ptr->CS_CALLBACK[index] (1 << index, 1, io_info_ptr->CS_USERDATA[index]);
                  }                
               }
               io_info_ptr->CS_ACTIVE = 0;
            }
         }
         break;
      case IO_IOCTL_SPI_GET_FRAMESIZE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            *param_ptr = 8;
         }
         break;
      case IO_IOCTL_SPI_SET_FRAMESIZE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            if (8 != *param_ptr)
            {
               result = MQX_IO_OPERATION_NOT_AVAILABLE;
            }
         }
         break;
      case IO_IOCTL_SPI_GET_CS:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            *param_ptr = io_info_ptr->CS;
         }
         break;
      case IO_IOCTL_SPI_SET_CS:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            io_info_ptr->CS = *param_ptr;
         }
         break;
      case IO_IOCTL_SPI_SET_CS_CALLBACK:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            callbacks = (SPI_CS_CALLBACK_STRUCT_PTR)(param_ptr);
            for (index = 0; index < MPC512X_SPI_CS_COUNT; index++)
            {
               if (0 != (callbacks->MASK & (1 << index)))
               {
                  io_info_ptr->CS_CALLBACK[index] = callbacks->CALLBACK;
                  io_info_ptr->CS_USERDATA[index] = callbacks->USERDATA;
               }                
            }
         }
         break;
      case IO_IOCTL_SPI_READ_WRITE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else if (NULL != io_info_ptr->RX_BUFFER) 
         {
            result = MQX_IO_OPERATION_NOT_AVAILABLE;
         } 
         else 
         {
            rw_ptr = (SPI_READ_WRITE_STRUCT_PTR)(param_ptr);
            size = rw_ptr->BUFFER_LENGTH;
            input = (uchar_ptr)rw_ptr->WRITE_BUFFER;
            output = (uchar_ptr)rw_ptr->READ_BUFFER;            
   
            for (num = 0; num < size; num++)
            {
               *output++ = _mpc512x_spi_polled_tx_rx (io_info_ptr, *input++, 1);
               io_info_ptr->STATS.RX_PACKETS++;
               io_info_ptr->STATS.TX_PACKETS++;
            }
         }
         break;
      case IO_IOCTL_SPI_KEEP_QSPI_CS_ACTIVE:
         result = MQX_IO_OPERATION_NOT_AVAILABLE;
         break;
      default:
         result = IO_ERROR_INVALID_IOCTL_CMD;
         break;
   }
   return result;
} /* EndBody */

/*FUNCTION****************************************************************
* 
* Function Name    : _mpc512x_spi_polled_tx_rx
* Returned Value   : byte received   
* Comments         : 
*   Actual transmit and receive function.
*
*END*********************************************************************/
static uint_8 _mpc512x_spi_polled_tx_rx 
   (
      /* [IN] The address of the device registers */
      MPC512X_SPI_INFO_STRUCT_PTR  io_info_ptr, 
      
      /* [IN] Transmitted byte */
      uint_8                      output, 
      
      /* [IN] Flag to bypass transmit for slave configuration */
      uint_8                      flag
   ) 
{ /* Body */
   uint_32                 index;
   uint_8                  rx_data;
   MPC5125_PSC_STRUCT_PTR  spi_ptr = io_info_ptr->SPI_PTR;
   
   /* Assert actual chip select */ 
   if (spi_ptr->SICR & PSC_SICR_MSTR) 
   {
     if (io_info_ptr->CS ^ io_info_ptr->CS_ACTIVE)
     {
        for (index = 0; index < MPC512X_SPI_CS_COUNT; index++)
        {
           if ((0 != ((io_info_ptr->CS ^ io_info_ptr->CS_ACTIVE) & (1 << index))) && (NULL != io_info_ptr->CS_CALLBACK[index]))
           {
              io_info_ptr->CS_CALLBACK[index] (1 << index, (io_info_ptr->CS_ACTIVE >> index) & 1, io_info_ptr->CS_USERDATA[index]);
           }
        }
        io_info_ptr->CS_ACTIVE = io_info_ptr->CS;
     }
   }
      
   if (flag)
   {
      /* Wait write buffer empty */      
      *((uint_8_ptr)&spi_ptr->TX_DATA) = output;
      while ((spi_ptr->TX_SR & PSC_FIFO_SR_EMPTY) == 1) {}
   }
   /* Wait read buffer full flag */
   while ((spi_ptr->RX_STAT & PSC_FIFO_SR_DATA_READY) == 0) {}
   rx_data = *((uint_8_ptr)&spi_ptr->RX_DATA);
   return rx_data;
} /* EndBody */

/*FUNCTION****************************************************************
* 
* Function Name    : _mpc512x_spi_polled_rx
* Returned Value   : Returns the number of bytes received
* Comments         : 
*   Reads the data into provided array.
*
*END*********************************************************************/
static uint_32 _mpc512x_spi_polled_rx
   (
      /* [IN] The device information */
      IO_SPI_POLLED_DEVICE_STRUCT_PTR io_dev_ptr,

      /* [IN] The array characters are to be read from */
      uchar_ptr                       buffer,
      
      /* [IN] Number of chars to transmit */
      uint_32                         size
   )
{ /* Body */
   MPC512X_SPI_INFO_STRUCT_PTR        io_info_ptr;
   MPC5125_PSC_STRUCT_PTR             spi_ptr;
   uint_32                            index, num = 0;
   uint_8                             master, full;
   
   io_info_ptr  = io_dev_ptr->DEV_INFO_PTR;
   spi_ptr = io_info_ptr->SPI_PTR;
 
   if(spi_ptr->SICR & PSC_SICR_MSTR)
      master = 1;
   else 
      master = 0;
   if(io_dev_ptr->FLAGS & SPI_FLAG_FULL_DUPLEX)
      full = 1;
   else 
      full = 0;
   
   for (num = 0; num < size; num++)
   {      
      *buffer = _mpc512x_spi_polled_tx_rx (io_info_ptr, *buffer, master | full);
      if (0 != full) 
      {
         io_info_ptr->STATS.TX_PACKETS++;
      }
      buffer++;
      io_info_ptr->STATS.RX_PACKETS++;   
   }
   return num;
} /* EndBody */

/*FUNCTION****************************************************************
* 
* Function Name    : _mcf5x_spi_polled_tx
* Returned Value   : return number of bytes transmitted
* Comments         : 
*   Writes the provided data buffer and loops until transmission complete
*
*END*********************************************************************/
static uint_32 _mpc512x_spi_polled_tx
   (
      /* [IN] The device information */
      IO_SPI_POLLED_DEVICE_STRUCT_PTR io_dev_ptr,

      /* [IN] The array to store data */
      uchar_ptr                       buffer,
      
      /* [IN] Number of chars to transmit */
      uint_32                         size
   )
{ /* Body */
   MPC512X_SPI_INFO_STRUCT_PTR        io_info_ptr;
   MPC5125_PSC_STRUCT_PTR            spi_ptr;
   uint_32                            num;
   uint_8                             tmp;

   io_info_ptr  = io_dev_ptr->DEV_INFO_PTR;
   spi_ptr = io_info_ptr->SPI_PTR;
   
   for (num = 0; num < size; num++)
   {
      tmp = _mpc512x_spi_polled_tx_rx (io_info_ptr, *buffer, 1);
      buffer++;
      io_info_ptr->STATS.TX_PACKETS++;
   }

   return num;
} /* EndBody */

/* EOF */

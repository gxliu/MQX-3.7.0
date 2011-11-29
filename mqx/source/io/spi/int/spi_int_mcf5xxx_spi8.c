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
* $FileName: spi_int_mcf5xxx_spi8.c$
* $Version : 3.6.13.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   The file contains low level SPI interrupt driver functions.
*
*END************************************************************************/
#include <mqx.h>
#include <bsp.h>
#include <io_prv.h>
#include <fio_prv.h>
#include "spi.h"
#include "spi_pol_prv.h"
#include "spi_int_prv.h"
#include "spi_mcf5xxx_spi8_prv.h"

extern uint_32 _mcf5xxx_spi8_polled_init(MCF5XXX_SPI8_INIT_STRUCT_PTR, pointer _PTR_, char_ptr);
extern uint_32 _mcf5xxx_spi8_polled_ioctl(MCF5XXX_SPI8_INFO_STRUCT_PTR, uint_32, uint_32_ptr, uint_32);

static uint_32 _mcf5xxx_spi8_int_init(IO_SPI_INT_DEVICE_STRUCT_PTR, char_ptr);
static uint_32 _mcf5xxx_spi8_int_deinit(IO_SPI_INT_DEVICE_STRUCT_PTR, MCF5XXX_SPI8_INFO_STRUCT_PTR);
static uint_32 _mcf5xxx_spi8_int_rx(IO_SPI_INT_DEVICE_STRUCT_PTR, uchar_ptr, int_32);
static uint_32 _mcf5xxx_spi8_int_tx(IO_SPI_INT_DEVICE_STRUCT_PTR, uchar_ptr, int_32);
static uint_32 _mcf5xxx_spi8_int_enable(MCF5XXX_SPI8_INFO_STRUCT_PTR io_info_ptr);
static void _mcf5xxx_spi8_int_isr(pointer parameter);
                       
/*FUNCTION****************************************************************
* 
* Function Name    : _MCF5XXX_SPI8_int_install
* Returned Value   : MQX error code
* Comments         :
*    Install an SPI device.
*
*END*********************************************************************/
uint_32 _mcf5xxx_spi8_int_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr           identifier,
  
      /* [IN] The I/O init data pointer */
      MCF5XXX_SPI8_INIT_STRUCT_CPTR            init_data_ptr
   )
{
   return _io_spi_int_install(identifier,
      (uint_32 (_CODE_PTR_)(pointer,char_ptr))_mcf5xxx_spi8_int_init,
      (uint_32 (_CODE_PTR_)(pointer))_mcf5xxx_spi8_int_enable,
      (uint_32 (_CODE_PTR_)(pointer, pointer))_mcf5xxx_spi8_int_deinit,
      (_mqx_int (_CODE_PTR_)(pointer, char_ptr, int_32))_mcf5xxx_spi8_int_rx,
      (_mqx_int (_CODE_PTR_)(pointer, char_ptr, int_32))_mcf5xxx_spi8_int_tx,
      (_mqx_int (_CODE_PTR_)(pointer, uint_32, _mqx_uint_ptr, _mqx_uint))_mcf5xxx_spi8_polled_ioctl, 
      (pointer)init_data_ptr);
}

/*FUNCTION****************************************************************
* 
* Function Name    : _MCF5XXX_SPI8_int_init  
* Returned Value   : MQX error code
* Comments         :
*    This function initializes the SPI module 
*
*END*********************************************************************/
static uint_32 _mcf5xxx_spi8_int_init
  (
     /* [IN] The address of the device specific information */
     IO_SPI_INT_DEVICE_STRUCT_PTR int_io_dev_ptr,

     /* [IN] The rest of the name of the device opened */
     char_ptr                     open_name_ptr
  )
{
   VMCF5XXX_SPI8_STRUCT_PTR        spi_ptr;
   MCF5XXX_SPI8_INFO_STRUCT_PTR   io_info_ptr;
   MCF5XXX_SPI8_INIT_STRUCT_PTR    spi_init_ptr;
   uint_32                        result = SPI_OK;

   spi_init_ptr = (MCF5XXX_SPI8_INIT_STRUCT_PTR)(int_io_dev_ptr->DEV_INIT_DATA_PTR);
   result = _mcf5xxx_spi8_polled_init(spi_init_ptr,
                                     &(int_io_dev_ptr->DEV_INFO_PTR),
                                     open_name_ptr);
   if (result)
   {
      return result;
   }
   
   io_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
   spi_ptr = io_info_ptr->SPI_PTR;
   
   io_info_ptr->RX_BUFFER = (pointer)_mem_alloc_system(spi_init_ptr->RX_BUFFER_SIZE);
   if (NULL == io_info_ptr->RX_BUFFER) 
   {
      _mem_free (int_io_dev_ptr->DEV_INFO_PTR);
      int_io_dev_ptr->DEV_INFO_PTR = NULL;
      return MQX_OUT_OF_MEMORY;
   }
   io_info_ptr->TX_BUFFER = (pointer)_mem_alloc_system(spi_init_ptr->TX_BUFFER_SIZE);
   if (NULL == io_info_ptr->TX_BUFFER) 
   {
      _mem_free (int_io_dev_ptr->DEV_INFO_PTR);
      int_io_dev_ptr->DEV_INFO_PTR = NULL;
      _mem_free (io_info_ptr->RX_BUFFER);
      io_info_ptr->RX_BUFFER = NULL;
      return MQX_OUT_OF_MEMORY;
   }
   _mem_set_type(io_info_ptr->RX_BUFFER,MEM_TYPE_IO_SPI_IN_BUFFER);       
   _mem_set_type(io_info_ptr->TX_BUFFER,MEM_TYPE_IO_SPI_OUT_BUFFER);       

   io_info_ptr->OLD_ISR_DATA = _int_get_isr_data(spi_init_ptr->VECTOR);
   io_info_ptr->OLD_ISR = _int_install_isr(spi_init_ptr->VECTOR, _mcf5xxx_spi8_int_isr, int_io_dev_ptr);
   
   return SPI_OK; 
}

/*FUNCTION****************************************************************
* 
* Function Name    : _MCF5XXX_SPI8_int_deinit  
* Returned Value   : MQX error code
* Comments         :
*    This function de-initializes the SPI module 
*
*END*********************************************************************/
static uint_32 _mcf5xxx_spi8_int_deinit
   (
      /* [IN] The address of the device specific information */
      IO_SPI_INT_DEVICE_STRUCT_PTR int_io_dev_ptr,

      /* [IN] The address of the channel specific information */
      MCF5XXX_SPI8_INFO_STRUCT_PTR  io_info_ptr
   )
{
   VMCF5XXX_SPI8_STRUCT_PTR        spi_ptr;
   MCF5XXX_SPI8_INIT_STRUCT_PTR     spi_init_ptr;
   uint_32                         index;
   
   if ((NULL == io_info_ptr) || (NULL == int_io_dev_ptr)) 
   {
      return SPI_ERROR_DEINIT_FAILED;
   }
   
   /* Disable the SPI and its interrupts */
   spi_ptr = io_info_ptr->SPI_PTR;
   index = spi_ptr->SPIC1 & MCF5XXX_SPI8_SPIC1_MSTR;
   spi_ptr->SPIC1 &= (~ (MCF5XXX_SPI8_SPIC1_SPE | MCF5XXX_SPI8_SPIC1_SPIE | MCF5XXX_SPI8_SPIC1_SPTIE));

   /* Disable all chip selects */
   if (0 != index) 
   {
      for (index = 0; index < MCF5XXX_SPI8_CS_COUNT; index++)
      {
         if ((NULL != io_info_ptr->CS_CALLBACK[index]) && (0 != (io_info_ptr->CS_ACTIVE & (1 << index))))
         {
            io_info_ptr->CS_CALLBACK[index] (1 << index, 1, io_info_ptr->CS_USERDATA[index]);
         }                
      }
      io_info_ptr->CS_ACTIVE = 0;
   }
   
   /* Return original interrupt vector */
   spi_init_ptr = (MCF5XXX_SPI8_INIT_STRUCT_PTR)(int_io_dev_ptr->DEV_INIT_DATA_PTR);
   _int_install_isr(spi_init_ptr->VECTOR, io_info_ptr->OLD_ISR, io_info_ptr->OLD_ISR_DATA);

   /* Release the buffers */   
   _mem_free(int_io_dev_ptr->DEV_INFO_PTR);
   int_io_dev_ptr->DEV_INFO_PTR = NULL;
   _mem_free(io_info_ptr->RX_BUFFER);
   io_info_ptr->RX_BUFFER = NULL;
   _mem_free(io_info_ptr->TX_BUFFER);
   io_info_ptr->TX_BUFFER = NULL;
       
   return SPI_OK;
}

/*FUNCTION****************************************************************
*
* Function Name    : _MCF5XXX_SPI8_int_enable
* Returned Value   : MQX error code
* Comments         :
*    This function enables receive and error interrupt.
*
*END*********************************************************************/
static uint_32 _mcf5xxx_spi8_int_enable
   ( 
   /* [IN] The address of the channel specific information */
      MCF5XXX_SPI8_INFO_STRUCT_PTR io_info_ptr
   )
{
   VMCF5XXX_SPI8_STRUCT_PTR       spi_ptr;

   if (NULL == io_info_ptr)   
   {
      return SPI_ERROR_INVALID_PARAMETER;   
   }
   spi_ptr = io_info_ptr->SPI_PTR;
   spi_ptr->SPIC1 |= MCF5XXX_SPI8_SPIC1_SPIE;
   return SPI_OK;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _MCF5XXX_SPI8_int_rx
* Returned Value   : Returns the number of bytes received
* Comments         : 
*   Reads the data into provided array.
*
*END*********************************************************************/
static uint_32 _mcf5xxx_spi8_int_rx
   (
      /* [IN] The address of the device specific information */
      IO_SPI_INT_DEVICE_STRUCT_PTR int_io_dev_ptr,

      /* [IN] The array characters are to be read from */
      uchar_ptr                    buffer,
      
      /* [IN] Number of char's to transmit */
      int_32                       size
   )
{
   MCF5XXX_SPI8_INFO_STRUCT_PTR     io_info_ptr;
   VMCF5XXX_SPI8_STRUCT_PTR        spi_ptr;
   MCF5XXX_SPI8_INIT_STRUCT_PTR     spi_init_ptr;
   uint_32                         num, index;
   uchar_ptr                       rx_ptr;

   io_info_ptr  = int_io_dev_ptr->DEV_INFO_PTR;
   spi_ptr = io_info_ptr->SPI_PTR;
   spi_init_ptr = &(io_info_ptr->INIT);
     
   /* Check buffer for any new data */
   rx_ptr = (uchar_ptr)(io_info_ptr->RX_BUFFER);
   for (num = 0; num < size; num++) 
   {
      index = io_info_ptr->RX_OUT;
      if (index == (volatile uint_32)io_info_ptr->RX_IN) break;
      *buffer++ = rx_ptr[index++];
      if (index >= io_info_ptr->INIT.RX_BUFFER_SIZE) index = 0;
      io_info_ptr->RX_OUT = index;
   }
   index = size - num;

   if (0 != index)
   {
      /* Not enough data, assert chip selects and enable further transfer */
      io_info_ptr->RX_REQUEST = (volatile uint_32)index;
      
      if (spi_ptr->SPIC1 & MCF5XXX_SPI8_SPIC1_MSTR) 
      {
         if (io_info_ptr->CS ^ io_info_ptr->CS_ACTIVE)
         {
           for (index = 0; index < MCF5XXX_SPI8_CS_COUNT; index++)
           {
              if ((0 != ((io_info_ptr->CS ^ io_info_ptr->CS_ACTIVE) & (1 << index))) && (NULL != io_info_ptr->CS_CALLBACK[index]))
              {
                 io_info_ptr->CS_CALLBACK[index] (1 << index, (io_info_ptr->CS_ACTIVE >> index) & 1, io_info_ptr->CS_USERDATA[index]);
              }
           }
           io_info_ptr->CS_ACTIVE = io_info_ptr->CS;
         }
      }
      spi_ptr->SPIC1 |= MCF5XXX_SPI8_SPIC1_SPTIE;
   }
   return num;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _MCF5XXX_SPI8_int_tx
* Returned Value   : return number of byte transmitted
* Comments         : 
*   Writes the provided data into trasmit buffer
*
*END*********************************************************************/
static uint_32 _mcf5xxx_spi8_int_tx
   (
      /* [IN] The address of the device specific information */
      IO_SPI_INT_DEVICE_STRUCT_PTR int_io_dev_ptr,

      /* [IN] The array to store data */
      uchar_ptr                    buffer,
      
      /* [IN] Number of char's to transmit */
      int_32                       size
   )
{
   MCF5XXX_SPI8_INFO_STRUCT_PTR     io_info_ptr;
   VMCF5XXX_SPI8_STRUCT_PTR        spi_ptr;
   MCF5XXX_SPI8_INIT_STRUCT_PTR     spi_init_ptr;
   uint_32                         num, index, tmp;
   uchar_ptr                       tx_ptr;
    
   io_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
   spi_ptr = io_info_ptr->SPI_PTR;
   spi_init_ptr = &(io_info_ptr->INIT);

   /* Fill new data into transmit buffer */
   tx_ptr = (uchar_ptr)(io_info_ptr->TX_BUFFER);
   index = io_info_ptr->TX_IN;
   for (num = 0; num < size; num++) 
   {
      tmp = index + 1;
      if (tmp >= io_info_ptr->INIT.TX_BUFFER_SIZE) tmp = 0;
      if (tmp == io_info_ptr->TX_OUT) break;
      tx_ptr[index] = *buffer++;
      index = tmp;
   }
   io_info_ptr->TX_IN = index;
   
   if (0 != num) 
   {
      /* At least one byte to transmit, assert chip selects and enable transfer */
      if (spi_ptr->SPIC1 & MCF5XXX_SPI8_SPIC1_MSTR) 
      {
         if (io_info_ptr->CS ^ io_info_ptr->CS_ACTIVE)
         {
           for (index = 0; index < MCF5XXX_SPI8_CS_COUNT; index++)
           {
              if ((0 != ((io_info_ptr->CS ^ io_info_ptr->CS_ACTIVE) & (1 << index))) && (NULL != io_info_ptr->CS_CALLBACK[index]))
              {
                 io_info_ptr->CS_CALLBACK[index] (1 << index, (io_info_ptr->CS_ACTIVE >> index) & 1, io_info_ptr->CS_USERDATA[index]);
              }
           }
           io_info_ptr->CS_ACTIVE = io_info_ptr->CS;
         }
      }
      spi_ptr->SPIC1 |= MCF5XXX_SPI8_SPIC1_SPTIE;
   }
   return num;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _MCF5XXX_SPI8_int_isr
* Returned Value   : SPI interrupt routine
* Comments         : 
*   Reads/writes bytes transmitted from/to buffers.
*
*END*********************************************************************/
static void _mcf5xxx_spi8_int_isr
   (
      /* [IN] The address of the device specific information */
      pointer                  parameter
   )
{
   MCF5XXX_SPI8_INFO_STRUCT_PTR io_info_ptr;
   VMCF5XXX_SPI8_STRUCT_PTR    spi_ptr;
   volatile uint_8             spis, tmp;
   uint_8                      index;
   boolean                     tx_and_rx;
   
   tx_and_rx = (((IO_SPI_INT_DEVICE_STRUCT_PTR)parameter)->FLAGS & SPI_FLAG_FULL_DUPLEX) != 0;
   io_info_ptr = ((IO_SPI_INT_DEVICE_STRUCT_PTR)parameter)->DEV_INFO_PTR;
   spi_ptr = (VMCF5XXX_SPI8_STRUCT_PTR)(io_info_ptr->SPI_PTR);
   
   /* Read interrupt status */
   spis = spi_ptr->SPIS;
   io_info_ptr->STATS.INTERRUPTS++;
  
   /* Master mode fault, switch to slave */
   if (spis & MCF5XXX_SPI8_SPIS_MODF)
   {
      spi_ptr->SPIC1 &= (~ MCF5XXX_SPI8_SPIC1_MSTR);
      io_info_ptr->STATS.TX_ABORTS++;
   }

   /* Receive is temporarily disabled during read */
   if (spis & MCF5XXX_SPI8_SPIS_SPRF)
   {
      /* Always clear receive int flag when enabled */
      tmp = spi_ptr->SPID;
      if (io_info_ptr->ONTHEWAY > 0) io_info_ptr->ONTHEWAY--;

      /* If request for receive and receive allowed (full duplex or first byte skipped already) */
      if (((tx_and_rx) || (1 == io_info_ptr->RECEIVING)) && (io_info_ptr->RX_REQUEST > 0))
      {
         /* Actual receive into buffer, if overflow, incoming bytes are thrown away */
         index = io_info_ptr->RX_IN + 1;
         if (index >= io_info_ptr->INIT.RX_BUFFER_SIZE) index = 0;
         if (index != io_info_ptr->RX_OUT) 
         {
            io_info_ptr->RX_BUFFER[io_info_ptr->RX_IN] = tmp;
            io_info_ptr->RX_IN = index;
            io_info_ptr->STATS.RX_PACKETS++;
         } else {
            io_info_ptr->STATS.RX_OVERFLOWS++;
         }
         if (--io_info_ptr->RX_REQUEST == 0) 
         {
            io_info_ptr->RECEIVING = 0;
         }
      } 

      /* Skipping bytes sent before receive */
      if (io_info_ptr->RECEIVING > 1) io_info_ptr->RECEIVING--;
   }

   /* Transmit is disabled when idle */
   if ((spi_ptr->SPIC1 & MCF5XXX_SPI8_SPIC1_SPTIE) && (spis & MCF5XXX_SPI8_SPIS_SPTEF))
   {
      index = io_info_ptr->RX_IN + 1;
      if (index >= io_info_ptr->INIT.RX_BUFFER_SIZE) index = 0;
      if ((tx_and_rx) || (io_info_ptr->RECEIVING == 0)) 
      {
         if (io_info_ptr->TX_OUT != io_info_ptr->TX_IN)
         {
            /* Change pin direction to output in single wire mode */
            if (spi_ptr->SPIC2 & MCF5XXX_SPI8_SPIC2_SPC0)
            {
               spi_ptr->SPIC2 |= MCF5XXX_SPI8_SPIC2_BIDIROE;   
            }
            /* Actual transmit */
            spi_ptr->SPID = io_info_ptr->TX_BUFFER[io_info_ptr->TX_OUT++];
            if (io_info_ptr->TX_OUT >= io_info_ptr->INIT.TX_BUFFER_SIZE) io_info_ptr->TX_OUT = 0;
            io_info_ptr->STATS.TX_PACKETS++;
            io_info_ptr->ONTHEWAY++;
         } 
         else 
         {
            /* Nothing to transmit, change pin direction to input in single wire mode */
            if (spi_ptr->SPIC2 & MCF5XXX_SPI8_SPIC2_SPC0)
            {
               spi_ptr->SPIC2 &= (~ MCF5XXX_SPI8_SPIC2_BIDIROE);
            }
            if ((index != io_info_ptr->RX_OUT) && (io_info_ptr->RX_REQUEST > 0))
            {
               /* Dummy transmit, setup receive */
               spi_ptr->SPID = 0xFF;
               io_info_ptr->ONTHEWAY++;
               io_info_ptr->RECEIVING = io_info_ptr->ONTHEWAY;
            } 
            else
            {
               /* No reason for transmit, block transmit interrupt */
               spi_ptr->SPIC1 &= (~ MCF5XXX_SPI8_SPIC1_SPTIE);
            }
         }
      } 
      else 
      {
         if ((index != io_info_ptr->RX_OUT) && (io_info_ptr->RX_REQUEST > io_info_ptr->ONTHEWAY - (io_info_ptr->RECEIVING - 1)))
         {
            /* Dummy transmit for receiving */
            spi_ptr->SPID = 0xFF;
            io_info_ptr->ONTHEWAY++;
         } 
         else
         {
            /* No reason for transmit, block transmit interrupt */
            spi_ptr->SPIC1 &= (~ MCF5XXX_SPI8_SPIC1_SPTIE);
         }
      }
   }
}
/* EOF */

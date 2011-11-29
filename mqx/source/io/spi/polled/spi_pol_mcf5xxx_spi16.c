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
* $FileName: spi_pol_mcf5xxx_spi16.c$
* $Version : 3.6.7.0$
* $Date    : Jun-23-2010$
*
* Comments:
*
*   The file contains low level SPI driver functions for 5xxx Coldfire family.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <io_prv.h>
#include <fio_prv.h>
#include "spi.h"
#include "spi_pol_prv.h"
#include "spi_mcf5xxx_spi16_prv.h"

uint_32 _mcf5xxx_spi16_polled_init(MCF5XXX_SPI16_INIT_STRUCT_PTR, pointer _PTR_, char_ptr);
uint_32 _mcf5xxx_spi16_polled_ioctl(MCF5XXX_SPI16_INFO_STRUCT_PTR, uint_32, uint_32_ptr, uint_32);

static uint_32 _mcf5xxx_spi16_polled_deinit(IO_SPI_POLLED_DEVICE_STRUCT_PTR, MCF5XXX_SPI16_INFO_STRUCT_PTR);
static uint_32 _mcf5xxx_spi16_polled_rx(IO_SPI_POLLED_DEVICE_STRUCT_PTR, uchar_ptr, uint_32);
static uint_32 _mcf5xxx_spi16_polled_tx(IO_SPI_POLLED_DEVICE_STRUCT_PTR, uchar_ptr, uint_32);
static uint_16 _mcf5xxx_spi16_polled_tx_rx(MCF5XXX_SPI16_INFO_STRUCT_PTR, uint_16, uint_8);

/*FUNCTION****************************************************************
* 
* Function Name    : _mcf5xxx_spi16_find_baudrate
* Returned Value   : uint_8 divider register setting
* Comments         :
*    Find closest setting of divider register for given baudrate.
*
*END*********************************************************************/
static uint_8 _mcf5xxx_spi16_find_baudrate 
   (
      /* [IN] Module input clock in Hz */
      uint_32 clock, 

      /* [IN] Desired baudrate in Hz */
      uint_32 baudrate
   ) 
{
  uint_32 sppr, spr, div, pres, min, tmp;
  int_32 val;
  
  spr = 8;
  sppr = 8;
  min = (uint_32)-1;
  for (pres = 1; pres <= 8; pres++) {
    for (div = 1; div <= 9; div++) {
      val = (pres << div) * baudrate - clock;
      if (val < 0) val = -val;
      if (min > val) {
        min = val;
        spr = div;
        sppr = pres;
      }
    }
  }
  return (uint_8)(((sppr - 1) << 4) | (spr - 1));
}
                      
/*FUNCTION****************************************************************
* 
* Function Name    : _mcf5xxx_spi16_polled_install
* Returned Value   : MQX error code
* Comments         :
*    Install an SPI device.
*
*END*********************************************************************/
uint_32 _mcf5xxx_spi16_polled_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr           identifier,
  
      /* [IN] The I/O init data pointer */
      MCF5XXX_SPI16_INIT_STRUCT_CPTR    init_data_ptr
   )
{
   return _io_spi_polled_install(identifier,
      (uint_32 (_CODE_PTR_)(pointer, pointer _PTR_, char_ptr))_mcf5xxx_spi16_polled_init,
      (uint_32 (_CODE_PTR_)(pointer, pointer))_mcf5xxx_spi16_polled_deinit,
      (_mqx_int (_CODE_PTR_)(pointer, char_ptr, int_32))_mcf5xxx_spi16_polled_rx,
      (_mqx_int (_CODE_PTR_)(pointer, char_ptr, int_32))_mcf5xxx_spi16_polled_tx,
      (_mqx_int (_CODE_PTR_)(pointer, uint_32, _mqx_uint_ptr, _mqx_uint))_mcf5xxx_spi16_polled_ioctl, 
      (pointer)init_data_ptr);
}

/*FUNCTION****************************************************************
* 
* Function Name    : _mcf5xxx_spi16_polled_init  
* Returned Value   : MQX error code
* Comments         :
*    This function initializes the SPI module 
*
*END*********************************************************************/
uint_32 _mcf5xxx_spi16_polled_init
(
   /* [IN] The initialization information for the device being opened */
   MCF5XXX_SPI16_INIT_STRUCT_PTR spi_init_ptr,

   /* [OUT] The address to store device specific information */
   pointer _PTR_                 io_info_ptr_ptr,  

   /* [IN] The rest of the name of the device opened */
   char_ptr                      open_name_ptr
)
{
   VMCF5XXX_SPI16_STRUCT_PTR     spi_ptr;
   MCF5XXX_SPI16_INFO_STRUCT_PTR io_info_ptr;
   uint_8                        SPIC1,SPIC2;
   uint_32                       i;

   /* Check channel */
   spi_ptr = _bsp_get_spi_base_address (spi_init_ptr->CHANNEL);
   if (NULL == spi_ptr)
   {
      return SPI_ERROR_CHANNEL_INVALID;
   }

   if (_bsp_spi_io_init (spi_init_ptr->CHANNEL) == -1)
   {
      return SPI_ERROR_CHANNEL_INVALID;
   }

   /* Disable SPI */
   spi_ptr->SPIC1 = 0;
   
   /* Initialize internal data */
   io_info_ptr = (MCF5XXX_SPI16_INFO_STRUCT _PTR_)_mem_alloc_system_zero((uint_32)sizeof(MCF5XXX_SPI16_INFO_STRUCT));
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
   for (i = 0; i < MCF5XXX_SPI16_CS_COUNT; i++)
   {
      io_info_ptr->CS_CALLBACK[i] = NULL;
      io_info_ptr->CS_USERDATA[i] = NULL;
   }

   /* Set transfer mode */
   if (spi_init_ptr->TRANSFER_MODE == SPI_DEVICE_SLAVE_MODE)
   {
      SPIC1 = 0;
      SPIC2 = 0;
   }
   else if (spi_init_ptr->TRANSFER_MODE == SPI_DEVICE_MASTER_MODE)
   {
      SPIC1 = MCF5XXX_SPI16_SPIC1_MSTR | MCF5XXX_SPI16_SPIC1_SSOE;
      SPIC2 = 0;
   }
   else if (spi_init_ptr->TRANSFER_MODE == SPI_DEVICE_BIO_MASTER_MODE)
   {
      SPIC1 = MCF5XXX_SPI16_SPIC1_MSTR;
      SPIC2 = MCF5XXX_SPI16_SPIC2_SPC0;
   }
   else if (spi_init_ptr->TRANSFER_MODE == SPI_DEVICE_BIO_SLAVE_MODE)
   {
      SPIC1 = 0;
      SPIC2 = MCF5XXX_SPI16_SPIC2_SPC0;
   }   
   else
   {
      _mem_free (*io_info_ptr_ptr);
      *io_info_ptr_ptr = NULL;
      return SPI_ERROR_TRANSFER_MODE_INVALID;
   }

   /* Set the SPI clock baud rate divider */
   spi_ptr->SPIBR = _mcf5xxx_spi16_find_baudrate (spi_init_ptr->CLOCK_SPEED, spi_init_ptr->BAUD_RATE);

   /* Set up SPI clock polarity and phase */
   switch (spi_init_ptr->CLOCK_POL_PHASE)
   {
   case (SPI_CLK_POL_PHA_MODE0):
       /* Inactive state of SPI_CLK = logic 0 */
      SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_CPOL);
       /* SPI_CLK transitions middle of bit timing */
        SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_CPHA);
      break;
   case (SPI_CLK_POL_PHA_MODE1):
       /* Inactive state of SPI_CLK = logic 0 */
      SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_CPOL);
       /* SPI_CLK transitions begining of bit timing */
        SPIC1 |= MCF5XXX_SPI16_SPIC1_CPHA;
      break;
   case (SPI_CLK_POL_PHA_MODE2):
       /* Inactive state of SPI_CLK = logic 1 */
      SPIC1 |= MCF5XXX_SPI16_SPIC1_CPOL;
       /* SPI_CLK transitions middle of bit timing */
        SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_CPHA);
      break;
   case (SPI_CLK_POL_PHA_MODE3):
       /* Inactive state of SPI_CLK = logic 1 */
      SPIC1 |= MCF5XXX_SPI16_SPIC1_CPOL;
       /* SPI_CLK transitions begining of bit timing */
        SPIC1 |= MCF5XXX_SPI16_SPIC1_CPHA;
      break;
   default:
      _mem_free (*io_info_ptr_ptr);
      *io_info_ptr_ptr = NULL;
      return SPI_ERROR_MODE_INVALID;       
   }

   /* Default: master mode, SSOE = 1, MODFEN = 0, clock stops in stop mode */
   spi_ptr->SPIC2 = SPIC2 | MCF5XXX_SPI16_SPIC2_SPISWAI;
   spi_ptr->SPIC1 = SPIC1 | MCF5XXX_SPI16_SPIC1_SPE | MCF5XXX_SPI16_SPIC1_SSOE;
   return SPI_OK;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _mcf5xxx_spi16_polled_deinit  
* Returned Value   : MQX error code
* Comments         :
*    This function de-initializes the SPI module 
*
*END*********************************************************************/
static uint_32 _mcf5xxx_spi16_polled_deinit
   (
      /* [IN] The device information */
      IO_SPI_POLLED_DEVICE_STRUCT_PTR io_dev_ptr,

      /* [IN] The address of the device specific information */
      MCF5XXX_SPI16_INFO_STRUCT_PTR   io_info_ptr
   )
{
   VMCF5XXX_SPI16_STRUCT_PTR          spi_ptr;
   uint_32                            index;

   if ((NULL == io_info_ptr) || (NULL == io_dev_ptr)) 
   {
      return SPI_ERROR_DEINIT_FAILED;
   }

   /* Disable the SPI */
   spi_ptr = io_info_ptr->SPI_PTR;
   spi_ptr->SPIC1 &= (~MCF5XXX_SPI16_SPIC1_SPE);

   /* Disable all chip selects */
   if (spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_MSTR) 
   {
      for (index = 0; index < MCF5XXX_SPI16_CS_COUNT; index++)
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
}

/*FUNCTION****************************************************************
* 
* Function Name    : _mcf5xxx_spi16_polled_ioctl
* Returned Value   : MQX error code
* Comments         : 
*    This function performs miscellaneous services for
*    the SPI I/O device.  
*
*END*********************************************************************/
uint_32 _mcf5xxx_spi16_polled_ioctl
   (
      /* [IN] The address of the device specific information */
      MCF5XXX_SPI16_INFO_STRUCT_PTR io_info_ptr,

      /* [IN] The command to perform */
      uint_32                       cmd,

      /* [IN] Parameters for the command */
      uint_32_ptr                   param_ptr,
      
      /* [IN] Opening flags */
      uint_32                       flags
   )
{
   VMCF5XXX_SPI16_STRUCT_PTR        spi_ptr;
   SPI_CS_CALLBACK_STRUCT_PTR       callbacks;
   uint_32                          index;
   uint_32                          result = SPI_OK;
   uint_32                          val, num, size;
   SPI_READ_WRITE_STRUCT_PTR        rw_ptr;
   uchar_ptr                        input, output;
   uint_16                          data;
  
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
            uint_32 sppr,spr, div;
            sppr = (uint_32)((uint_8)(spi_ptr->SPIBR)>>4) + 1;
            spr = (uint_32)((uint_8)(spi_ptr->SPIBR) & 0x0F) + 1;
            div = sppr * ((uint_32)0x0001 << spr);
            *param_ptr = (uint_32)((io_info_ptr->INIT.CLOCK_SPEED) / div);
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
            uint_8 val = _mcf5xxx_spi16_find_baudrate (io_info_ptr->INIT.CLOCK_SPEED, *param_ptr);
            /* Disable SPI module */
            spi_ptr->SPIC1 &= (~MCF5XXX_SPI16_SPIC1_SPE);
            /* Set the frequency divider */
            spi_ptr->SPIBR = val;
            /* Enable SPI module */
            spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SPE;
         }
         break;
      case IO_IOCTL_SPI_DEVICE_DISABLE:
         spi_ptr->SPIC1 &= (~MCF5XXX_SPI16_SPIC1_SPE);
         break;
      case IO_IOCTL_SPI_DEVICE_ENABLE:
         spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SPE;
         break;
      case IO_IOCTL_SPI_GET_MODE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else
         {
            if (spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_CPOL)
            {
               if (spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_CPHA)
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
               if (spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_CPHA)
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
            spi_ptr->SPIC1 &= (~MCF5XXX_SPI16_SPIC1_SPE);
            switch (*param_ptr)
            {
               case (SPI_CLK_POL_PHA_MODE0):
                  /* Inactive state of SPI_CLK = logic 0 */
                  spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_CPOL);
                  /* SPI_CLK transitions middle of bit timing */
                  spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_CPHA);
                  break;
               case (SPI_CLK_POL_PHA_MODE1):
                  /* Inactive state of SPI_CLK = logic 0 */
                  spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_CPOL);
                  /* SPI_CLK transitions begining of bit timing */
                  spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_CPHA;
                  break;
               case (SPI_CLK_POL_PHA_MODE2):
                  /* Inactive state of SPI_CLK = logic 1 */
                  spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_CPOL;
                  /* SPI_CLK transitions middle of bit timing */
                  spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_CPHA);
                  break;
               case (SPI_CLK_POL_PHA_MODE3):
                  /* Inactive state of SPI_CLK = logic 1 */
                  spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_CPOL;
                  /* SPI_CLK transitions begining of bit timing */
                  spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_CPHA;
                  break;
               default:
                  result = SPI_ERROR_MODE_INVALID;
                  break;
             }
             /* Enable SPI module */
             spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SPE;         
         }
         break;
      case IO_IOCTL_SPI_GET_TRANSFER_MODE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else
         {
            if (spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_MSTR) 
            {
               if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPC0) 
               {
                  *param_ptr = SPI_DEVICE_BIO_MASTER_MODE; 
               }
               else 
               {
                  *param_ptr = SPI_DEVICE_MASTER_MODE;
               }
            }
            else 
            {
               if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPC0) 
               {
                  *param_ptr = SPI_DEVICE_BIO_SLAVE_MODE; 
               } 
               else 
               {
                  *param_ptr = SPI_DEVICE_SLAVE_MODE;
               }
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
            spi_ptr->SPIC1 &= (~MCF5XXX_SPI16_SPIC1_SPE);
            switch (*param_ptr)
            {
               case SPI_DEVICE_BIO_SLAVE_MODE:
                  spi_ptr->SPIC1 &= (~ (MCF5XXX_SPI16_SPIC1_MSTR | MCF5XXX_SPI16_SPIC1_SSOE));
                  spi_ptr->SPIC2 |= MCF5XXX_SPI16_SPIC2_SPC0;
                  break;
               case SPI_DEVICE_SLAVE_MODE:
                  spi_ptr->SPIC1 &= (~ (MCF5XXX_SPI16_SPIC1_MSTR | MCF5XXX_SPI16_SPIC1_SSOE));
                  spi_ptr->SPIC2 &= (~ MCF5XXX_SPI16_SPIC2_SPC0);
                  break;
               case SPI_DEVICE_BIO_MASTER_MODE:
                  spi_ptr->SPIC1 |= (MCF5XXX_SPI16_SPIC1_MSTR | MCF5XXX_SPI16_SPIC1_SSOE);
                  spi_ptr->SPIC2 |= MCF5XXX_SPI16_SPIC2_SPC0;
                  break;
               case SPI_DEVICE_MASTER_MODE:
                  spi_ptr->SPIC1 |= (MCF5XXX_SPI16_SPIC1_MSTR | MCF5XXX_SPI16_SPIC1_SSOE);
                  spi_ptr->SPIC2 &= (~ MCF5XXX_SPI16_SPIC2_SPC0);
                  break;
               default:
                  result = SPI_ERROR_TRANSFER_MODE_INVALID;            
                  break;
            }
            /* Enable SPI module */
            spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SPE;               
         }
         break;
      case IO_IOCTL_SPI_GET_ENDIAN:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else if (spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_LSBFE)
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
            spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_LSBFE;
         }
         else if (*param_ptr == SPI_DEVICE_BIG_ENDIAN)
         {
            spi_ptr->SPIC1 &= (~MCF5XXX_SPI16_SPIC1_LSBFE);
         }
         else
         {
            result = SPI_ERROR_ENDIAN_INVALID;
         }
         break;
      case IO_IOCTL_SPI_ENABLE_MODF:
         /* Disable SPI module */
         spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_SPE);
         /* Enable to MODF mode */
         spi_ptr->SPIC2 |= MCF5XXX_SPI16_SPIC2_MODFEN;
         spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SSOE;
         /* Enable SPI module */
         spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SPE;                 
         break;
      case IO_IOCTL_SPI_DISABLE_MODF:
         /* Disable SPI module */
         spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_SPE);
         /* Disable MODF mode */
         spi_ptr->SPIC2 &= (~ MCF5XXX_SPI16_SPIC2_MODFEN);
         spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SSOE;
         /* Enable SPI module */
         spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SPE;  
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
         while ((0 != io_info_ptr->RECEIVING) || (0 != io_info_ptr->ONTHEWAY) || (spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_SPTIE)) 
            { };    /* Waiting for completion */
            
         if ((0 == (flags & SPI_FLAG_NO_DEASSERT_ON_FLUSH)) || (IO_IOCTL_SPI_FLUSH_DEASSERT_CS == cmd))
         {
            /* Deassert all chip selects */
            if (spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_MSTR) 
            {
               for (index = 0; index < MCF5XXX_SPI16_CS_COUNT; index++)
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
            if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPIMODE) 
            {
              *param_ptr = 16;
            } 
            else 
            {
              *param_ptr = 8;
            }
         }
         break;
      case IO_IOCTL_SPI_SET_FRAMESIZE:
         if (NULL == param_ptr) 
         {
            result = SPI_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            if (8 == *param_ptr)
            {
               /* Disable SPI module */
               spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_SPE);
               /* Set 8 bit mode */
               spi_ptr->SPIC2 &= (~ MCF5XXX_SPI16_SPIC2_SPIMODE);
               /* Enable SPI module */
               spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SPE;  
            } 
            else if (16 == *param_ptr)
            {
               /* Disable SPI module */
               spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_SPE);
               /* Set 8 bit mode */
               spi_ptr->SPIC2 |= MCF5XXX_SPI16_SPIC2_SPIMODE;
               /* Enable SPI module */
               spi_ptr->SPIC1 |= MCF5XXX_SPI16_SPIC1_SPE;  
            } 
            else 
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
            for (index = 0; index < MCF5XXX_SPI16_CS_COUNT; index++)
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
   
            if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPC0)
            {
               spi_ptr->SPIC2 |= MCF5XXX_SPI16_SPIC2_BIDIROE;   
            }

            for (num = 0; num < size; num++)
            {
               /* If MSTR = MOFEN = 1, SSOE = 0, should check whether fault has occurred */
               if (spi_ptr->SPIS & MCF5XXX_SPI16_SPIS_MODF)
               {  
                  spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_MSTR);
                  io_info_ptr->STATS.TX_ABORTS++;
                  break;
               }
               data = input[0];
               input++;
               if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPIMODE) 
               {
                  data = (data << 8) | input[1];
                  input++;
               }
               data = _mcf5xxx_spi16_polled_tx_rx (io_info_ptr, data, 1);
               if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPIMODE) 
               {
                  output[0] = (uint_8)(data >> 8);
                  output++;
               }
               output[0] = (uint_8)data;
               output++;
               io_info_ptr->STATS.RX_PACKETS++;
               io_info_ptr->STATS.TX_PACKETS++;
            }

            if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPC0)
            {
               spi_ptr->SPIC2 &= (~ MCF5XXX_SPI16_SPIC2_BIDIROE);
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
}

/*FUNCTION****************************************************************
* 
* Function Name    : _mcf5xxx_spi16_polled_tx_rx
* Returned Value   : byte received   
* Comments         : 
*   Actual transmit and receive function.
*
*END*********************************************************************/
static uint_16 _mcf5xxx_spi16_polled_tx_rx 
   (
      /* [IN] The address of the device registers */
      MCF5XXX_SPI16_INFO_STRUCT_PTR io_info_ptr, 
      
      /* [IN] Transmitted byte */
      uint_16                       output, 
      
      /* [IN] Flag to bypass transmit for slave configuration */
      uint_8                        flag
   )
{
   uint_32                          index;
   VMCF5XXX_SPI16_STRUCT_PTR        spi_ptr = io_info_ptr->SPI_PTR;
   
   /* Assert actual chip select */ 
   if (spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_MSTR) 
   {
     if (io_info_ptr->CS ^ io_info_ptr->CS_ACTIVE)
     {
        for (index = 0; index < MCF5XXX_SPI16_CS_COUNT; index++)
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
      /* Wait write buffer empty flag */
      while (! (spi_ptr->SPIS & MCF5XXX_SPI16_SPIS_SPTEF)) 
         { };
      spi_ptr->SPID = output;
   }
   
   /* Wait read buffer full flag */
   while (! (spi_ptr->SPIS & MCF5XXX_SPI16_SPIS_SPRF)) 
      { };
   return spi_ptr->SPID;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _mcf5xxx_spi16_polled_rx
* Returned Value   : Returns the number of bytes received
* Comments         : 
*   Reads the data into provided array.
*
*END*********************************************************************/
static uint_32 _mcf5xxx_spi16_polled_rx
   (
      /* [IN] The device information */
      IO_SPI_POLLED_DEVICE_STRUCT_PTR io_dev_ptr,

      /* [IN] The array characters are to be read from */
      uchar_ptr                       buffer,
      
      /* [IN] Number of chars to transmit */
      uint_32                         size
   )
{
   MCF5XXX_SPI16_INFO_STRUCT_PTR      io_info_ptr;
   VMCF5XXX_SPI16_STRUCT_PTR          spi_ptr;
   uint_32                            index, num = 0;
   uint_16                            data;
   uint_8                             master, full;
   
   io_info_ptr  = io_dev_ptr->DEV_INFO_PTR;
   spi_ptr = io_info_ptr->SPI_PTR;
   
   if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPC0)
   {
      spi_ptr->SPIC2 &= (~ MCF5XXX_SPI16_SPIC2_BIDIROE);
   }
   
   master = spi_ptr->SPIC1 & MCF5XXX_SPI16_SPIC1_MSTR;
   full = io_dev_ptr->FLAGS & SPI_FLAG_FULL_DUPLEX;
   
   for (num = 0; num < size; num++)
   {
      /* If MSTR = MOFEN = 1, SSOE = 0, should check whether fault has occurred */
      if (spi_ptr->SPIS & MCF5XXX_SPI16_SPIS_MODF)
      {
         spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_MSTR);
         io_info_ptr->STATS.TX_ABORTS++;
         break;
      }
      
      data = buffer[0];
      if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPIMODE) 
      {
         data = (data << 8) | buffer[1];
      }
      data = _mcf5xxx_spi16_polled_tx_rx (io_info_ptr, data, master | full);
      if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPIMODE) 
      {
         buffer[0] = (uint_8)(data >> 8);
         buffer++;
         num++;
      }
      buffer[0] = (uint_8)data;
      buffer++;
      if (0 != full) 
      {
         io_info_ptr->STATS.TX_PACKETS++;
      }
      io_info_ptr->STATS.RX_PACKETS++;   
   }
   return num;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _mcf51_spi_polled_tx
* Returned Value   : return number of bytes transmitted
* Comments         : 
*   Writes the provided data buffer and loops until transmission complete
*
*END*********************************************************************/
static uint_32 _mcf5xxx_spi16_polled_tx
   (
      /* [IN] The device information */
      IO_SPI_POLLED_DEVICE_STRUCT_PTR io_dev_ptr,

      /* [IN] The array to store data */
      uchar_ptr                       buffer,
      
      /* [IN] Number of chars to transmit */
      uint_32                         size
   )
{
   MCF5XXX_SPI16_INFO_STRUCT_PTR      io_info_ptr;
   VMCF5XXX_SPI16_STRUCT_PTR          spi_ptr;
   uint_32                            num;
   uint_16                            data;

   io_info_ptr  = io_dev_ptr->DEV_INFO_PTR;
   spi_ptr = io_info_ptr->SPI_PTR;
   
   if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPC0)
   {
      spi_ptr->SPIC2 |= MCF5XXX_SPI16_SPIC2_BIDIROE;   
   }
   
   for (num = 0; num < size; num++)
   {
      /* If MSTR = MOFEN = 1, SSOE = 0, should check whether fault has occurred */
      if (spi_ptr->SPIS & MCF5XXX_SPI16_SPIS_MODF)
      {  
         spi_ptr->SPIC1 &= (~ MCF5XXX_SPI16_SPIC1_MSTR);
         io_info_ptr->STATS.TX_ABORTS++;
         break;
      }
      
      data = buffer[0];
      buffer++;
      if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPIMODE) 
      {
         data = (data << 8) | buffer[0];
         buffer++;
         num++;
      }
      data = _mcf5xxx_spi16_polled_tx_rx (io_info_ptr, data, 1);
      io_info_ptr->STATS.TX_PACKETS++;
   }

   if (spi_ptr->SPIC2 & MCF5XXX_SPI16_SPIC2_SPC0)
   {
      spi_ptr->SPIC2 &= (~ MCF5XXX_SPI16_SPIC2_BIDIROE);
   }
   return num;
}
/* EOF */

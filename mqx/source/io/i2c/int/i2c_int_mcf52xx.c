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
* $FileName: i2c_int_mcf52xx.c$
* $Version : 3.6.5.0$
* $Date    : Apr-22-2010$
*
* Comments:
*
*   This file contains low level functions for the I2C interrupt device driver
*   for 52XX Coldfire family.
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include <io_prv.h>
#include <fio_prv.h>
#include "i2c.h"
#include "i2c_int_prv.h"
#include "i2c_mcf52xx_prv.h"


extern uint_32 _mcf52xx_i2c_polled_init (MCF52XX_I2C_INIT_STRUCT_PTR, pointer _PTR_, char_ptr);
extern uint_32 _mcf52xx_i2c_polled_ioctl (MCF52XX_I2C_INFO_STRUCT_PTR, uint_32, uint_32_ptr);

extern uint_32 _mcf52xx_i2c_int_init (IO_I2C_INT_DEVICE_STRUCT_PTR, char_ptr);
extern uint_32 _mcf52xx_i2c_int_deinit (IO_I2C_INT_DEVICE_STRUCT_PTR, MCF52XX_I2C_INFO_STRUCT_PTR);
extern uint_32 _mcf52xx_i2c_int_rx (IO_I2C_INT_DEVICE_STRUCT_PTR, uchar_ptr, uint_32);
extern uint_32 _mcf52xx_i2c_int_tx (IO_I2C_INT_DEVICE_STRUCT_PTR, uchar_ptr, uint_32);
static void    _mcf52xx_i2c_isr (pointer);


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf52xx_i2c_int_install
* Returned Value   : MQX error code
* Comments         :
*    Install an I2C device.
*
*END*********************************************************************/

uint_32 _mcf52xx_i2c_int_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr           identifier,
  
      /* [IN] The I/O init data pointer */
      MCF52XX_I2C_INIT_STRUCT_CPTR  init_data_ptr
   )
{ /* Body */

   return _io_i2c_int_install(identifier,
      (uint_32 (_CODE_PTR_)(pointer, char_ptr))_mcf52xx_i2c_int_init,
      (uint_32 (_CODE_PTR_)(pointer, pointer))_mcf52xx_i2c_int_deinit,
      (int_32 (_CODE_PTR_)(pointer, char_ptr, int_32))_mcf52xx_i2c_int_rx,
      (int_32 (_CODE_PTR_)(pointer, char_ptr, int_32))_mcf52xx_i2c_int_tx,
      (int_32 (_CODE_PTR_)(pointer, uint_32, uint_32_ptr))_mcf52xx_i2c_polled_ioctl, 
      (pointer)init_data_ptr);

} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf52xx_i2c_int_init
* Returned Value   : MQX error code
* Comments         :
*    This function initializes an I2C device.
*
*END*********************************************************************/

uint_32 _mcf52xx_i2c_int_init
   (
      /* [IN] Initialization information for the device being opened */
      IO_I2C_INT_DEVICE_STRUCT_PTR  int_io_dev_ptr,

      /* [IN] The rest of the name of the device opened */
      char_ptr                      open_name_ptr

   )
{ /* Body */
   VMCF52XX_I2C_STRUCT_PTR          i2c_ptr;
   MCF52XX_I2C_INFO_STRUCT_PTR      io_info_ptr;
   MCF52XX_I2C_INIT_STRUCT_PTR      i2c_init_ptr;
   uint_32                          vector, result;

   i2c_init_ptr = (MCF52XX_I2C_INIT_STRUCT_PTR)(int_io_dev_ptr->DEV_INIT_DATA_PTR);
   result = _mcf52xx_i2c_polled_init (i2c_init_ptr,
                                     &(int_io_dev_ptr->DEV_INFO_PTR),
                                     open_name_ptr);
   if (result)
   {
      return result;
   }
   
   io_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
   i2c_ptr = io_info_ptr->I2C_PTR;
   vector = _bsp_get_i2c_vector (i2c_init_ptr->CHANNEL);
   if (0 == vector)
   {
      return I2C_ERROR_CHANNEL_INVALID;
   }

   /* Allocate buffers */
   io_info_ptr->RX_BUFFER = (pointer)_mem_alloc_system (i2c_init_ptr->RX_BUFFER_SIZE);
   if (NULL == io_info_ptr->RX_BUFFER) 
   {
      return MQX_OUT_OF_MEMORY;
   }
   io_info_ptr->TX_BUFFER = (pointer)_mem_alloc_system (i2c_init_ptr->TX_BUFFER_SIZE);
   if (NULL == io_info_ptr->TX_BUFFER) 
   {
      _mem_free (io_info_ptr->RX_BUFFER);
      io_info_ptr->RX_BUFFER = NULL;
      return MQX_OUT_OF_MEMORY;
   }
   _mem_set_type (io_info_ptr->RX_BUFFER, MEM_TYPE_IO_I2C_IN_BUFFER);       
   _mem_set_type (io_info_ptr->TX_BUFFER, MEM_TYPE_IO_I2C_OUT_BUFFER);       

   /* Install new vectors and backup the old ones */
   io_info_ptr->OLD_ISR_DATA = _int_get_isr_data (vector);
   io_info_ptr->OLD_ISR = _int_install_isr (vector, _mcf52xx_i2c_isr, io_info_ptr);
   _mcf52xx_int_init((PSP_INTERRUPT_TABLE_INDEX)vector, io_info_ptr->INIT.LEVEL, io_info_ptr->INIT.SUBLEVEL, TRUE);

   /* Enable I2C interrupts */
   i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_IIEN;

   return result;
} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf52xx_i2c_int_deinit
* Returned Value   : MQX error code
* Comments         :
*    This function de-initializes an I2C device.
*
*END*********************************************************************/

uint_32 _mcf52xx_i2c_int_deinit
   (
      /* [IN] the initialization information for the device being opened */
      IO_I2C_INT_DEVICE_STRUCT_PTR  int_io_dev_ptr,

      /* [IN] the address of the device specific information */
      MCF52XX_I2C_INFO_STRUCT_PTR   io_info_ptr
   )
{ /* Body */
   VMCF52XX_I2C_STRUCT_PTR          i2c_ptr;
   MCF52XX_I2C_INIT_STRUCT_PTR      i2c_init_ptr;
      
   if ((NULL == io_info_ptr) || (NULL == int_io_dev_ptr)) 
   {
      return I2C_ERROR_INVALID_PARAMETER;
   }

   i2c_ptr = io_info_ptr->I2C_PTR;
   if (i2c_ptr->I2SR & MCF52XX_I2C_I2SR_IBB) 
   {
      return I2C_ERROR_DEVICE_BUSY;
   }
   
   /* Disable the I2C */
   i2c_ptr->I2CR    = 0x00;

   /* Clear the I2C events */
   i2c_ptr->I2SR    = 0x00; 
 
   /* Install original vectors */
   i2c_init_ptr = (MCF52XX_I2C_INIT_STRUCT_PTR)(int_io_dev_ptr->DEV_INIT_DATA_PTR);
   _mcf52xx_int_init(_bsp_get_i2c_vector (i2c_init_ptr->CHANNEL), io_info_ptr->INIT.LEVEL, io_info_ptr->INIT.SUBLEVEL, FALSE);
   _int_install_isr (_bsp_get_i2c_vector (i2c_init_ptr->CHANNEL), io_info_ptr->OLD_ISR, io_info_ptr->OLD_ISR_DATA);
   
   /* Free buffers and info struct */
   _mem_free (int_io_dev_ptr->DEV_INFO_PTR);
   int_io_dev_ptr->DEV_INFO_PTR = NULL;
   _mem_free (io_info_ptr->RX_BUFFER);
   io_info_ptr->RX_BUFFER = NULL;
   _mem_free (io_info_ptr->TX_BUFFER);
   io_info_ptr->TX_BUFFER = NULL;

   return I2C_OK;
} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf52xx_i2c_int_rx
* Returned Value   : number of bytes read
* Comments         : 
*   Returns the number of bytes received.
*   Reads the data into provided array when data is available.
*
*END*********************************************************************/

uint_32 _mcf52xx_i2c_int_rx
   (
      /* [IN] the address of the device specific information */
      IO_I2C_INT_DEVICE_STRUCT_PTR   int_io_dev_ptr,

      /* [IN] The array to copy data into */
      uchar_ptr                      buffer,
      
      /* [IN] number of bytes to read */
      uint_32                        length
   )
{ /* Body */
   MCF52XX_I2C_INFO_STRUCT_PTR       io_info_ptr;
   VMCF52XX_I2C_STRUCT_PTR           i2c_ptr;   
   uint_32                           num;
   volatile uint_8                   tmp;
         
   io_info_ptr = int_io_dev_ptr->DEV_INFO_PTR;
   i2c_ptr = io_info_ptr->I2C_PTR;

   /* Interrupt double disable - avoid spurious interrupt  */
   _int_disable();
   i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_IIEN);
   _int_enable();

   /* Get data from input buffer */
   for (num = 0; num < length; num++)
   {
      if (io_info_ptr->RX_OUT == io_info_ptr->RX_IN) break;
      *buffer++ = io_info_ptr->RX_BUFFER[io_info_ptr->RX_OUT++];
      if (io_info_ptr->RX_OUT >= io_info_ptr->INIT.RX_BUFFER_SIZE) io_info_ptr->RX_OUT = 0;
   }

   /* If beginning of transmission, set state and send address (master only) */
   tmp = io_info_ptr->STATE;
   if ((I2C_STATE_READY == tmp) || (I2C_STATE_REPEATED_START == tmp))
   {
      io_info_ptr->STATE = I2C_STATE_RECEIVE;
      if (I2C_MODE_MASTER == io_info_ptr->MODE)
      {
         i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_MTX;
         if (I2C_STATE_REPEATED_START == tmp)
         {
            i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
            i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_RSTA;
            while (0 == (i2c_ptr->I2SR & MCF52XX_I2C_I2SR_ICF)) 
               { };   // wait for completion
         }
         else
         {
            i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_MSTA;
         }
         io_info_ptr->ONTHEWAY = TRUE;
         i2c_ptr->I2DR = (io_info_ptr->ADDRESSEE << 1) | I2C_OPERATION_READ;
         io_info_ptr->STATISTICS.TX_PACKETS++;
      }
   }
   
   /* Interrupt enable - end of critical section */
   i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_IIEN;
      
   return num;
   
} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf52xx_i2c_int_tx
* Returned Value   : number of bytes written
* Comments         : 
*   Returns the number of bytes written.
*   Writes the data provided into transmition buffer if available.
*
*END*********************************************************************/

uint_32 _mcf52xx_i2c_int_tx
   (
      /* [IN] the address of the device specific information */
      IO_I2C_INT_DEVICE_STRUCT_PTR    int_io_dev_ptr,

      /* [IN] The array characters are to be read from */
      uchar_ptr                       buffer,
      
      /* [IN] number of bytes to output */
      uint_32                         length
   )
{ /* Body */
   MCF52XX_I2C_INFO_STRUCT_PTR        io_info_ptr;
   VMCF52XX_I2C_STRUCT_PTR            i2c_ptr;   
   uint_32                            num, tmp;
   
   io_info_ptr  = int_io_dev_ptr->DEV_INFO_PTR;
   i2c_ptr = io_info_ptr->I2C_PTR;

   /* Interrupt double disable - avoid spurious interrupt  */
   _int_disable();
   i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_IIEN);
   _int_enable();

   /* Fill in the output buffer  */
   for (num = 0; num < length; num++)
   {
      tmp = io_info_ptr->TX_IN + 1;
      if (tmp >= io_info_ptr->INIT.TX_BUFFER_SIZE) tmp = 0;
      if (tmp == io_info_ptr->TX_OUT) break;
      io_info_ptr->TX_BUFFER[io_info_ptr->TX_IN] = *buffer++;
      io_info_ptr->TX_IN = tmp;
   }
   
   /* If beginning of transmission, set state and send address (master only) */
   tmp = io_info_ptr->STATE;
   if ((I2C_STATE_READY == tmp) || (I2C_STATE_REPEATED_START == tmp))
   {
      io_info_ptr->STATE = I2C_STATE_TRANSMIT;
      if (I2C_MODE_MASTER == io_info_ptr->MODE)
      {
         i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_MTX;
         if (I2C_STATE_REPEATED_START == tmp)
         {
            i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
            i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_RSTA;
            while (0 == (i2c_ptr->I2SR & MCF52XX_I2C_I2SR_ICF))
               { };   // wait for completion
         }
         else
         {
            i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_MSTA;
         }
         io_info_ptr->ONTHEWAY = TRUE;
         i2c_ptr->I2DR = (io_info_ptr->ADDRESSEE << 1) | I2C_OPERATION_WRITE;
         io_info_ptr->STATISTICS.TX_PACKETS++;
      }
   }
   
   /* Interrupt enable - end of critical section */
   i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_IIEN;

   return num;

} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    :_mcf52xx_i2c_isr
* Returned Value   : none   
*
*END*********************************************************************/
static void _mcf52xx_i2c_isr
   (
      pointer                  parameter
   )
{ /* Body */
   MCF52XX_I2C_INFO_STRUCT_PTR io_info_ptr = parameter;
   VMCF52XX_I2C_STRUCT_PTR     i2c_ptr = io_info_ptr->I2C_PTR;
   uint_8                      i2csr;
   volatile uint_8             tmp;

   i2csr = i2c_ptr->I2SR;
   io_info_ptr->ONTHEWAY = FALSE;
   io_info_ptr->STATISTICS.INTERRUPTS++;
   
   /* Master */
   if (i2c_ptr->I2CR & MCF52XX_I2C_I2CR_MSTA)
   {
      /* Transmit */
      if (i2c_ptr->I2CR & MCF52XX_I2C_I2CR_MTX)
      {
         /* Not ack */
         if (i2csr & MCF52XX_I2C_I2SR_RXAK)
         {
            i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
            i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_MTX);
            io_info_ptr->STATISTICS.TX_NAKS++;
            io_info_ptr->STATE = I2C_STATE_FINISHED;
         }
         /* Ack */
         else
         {
            /* Transmit requested */
            if (I2C_STATE_TRANSMIT == io_info_ptr->STATE)
            {
               /* Anything to transmit? */
               if (io_info_ptr->TX_IN == io_info_ptr->TX_OUT)
               {
                  i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_IIEN);
               }
               else
               {
                  i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
                  io_info_ptr->ONTHEWAY = TRUE;
                  i2c_ptr->I2DR = io_info_ptr->TX_BUFFER[io_info_ptr->TX_OUT++];   // transmit data
                  if (io_info_ptr->TX_OUT >= io_info_ptr->INIT.TX_BUFFER_SIZE) io_info_ptr->TX_OUT = 0;
                  io_info_ptr->STATISTICS.TX_PACKETS++;
               }
            }
            /* Receive requested */
            else if (I2C_STATE_RECEIVE == io_info_ptr->STATE)
            {
               i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
               i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_MTX);
               if (1 == io_info_ptr->RX_REQUEST)
               {
                  i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_TXAK;
               }
               if (0 == io_info_ptr->RX_REQUEST)
               {
                  i2c_ptr->I2CR &= (~ (MCF52XX_I2C_I2CR_MSTA | MCF52XX_I2C_I2CR_MTX | MCF52XX_I2C_I2CR_TXAK));
                  io_info_ptr->STATE = I2C_STATE_FINISHED;
               }
               else
               {
                  io_info_ptr->ONTHEWAY = TRUE;
                  tmp = i2c_ptr->I2DR;   // dummy read to clock in 1st byte
               }
            }
            /* Others are unwanted/not handled states */
            else
            {
               i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
            }
         }
      }
      /* Receive */
      else
      {
         /* Receive requested */
         if ((I2C_STATE_RECEIVE == io_info_ptr->STATE) && (0 != io_info_ptr->RX_REQUEST))
         {
            tmp = io_info_ptr->RX_IN + 1;
            if (tmp >= io_info_ptr->INIT.RX_BUFFER_SIZE) tmp = 0;
            /* Buffer full */
            if (tmp == io_info_ptr->RX_OUT)
            {
               i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_IIEN);
            }
            /* Buffer not full */
            else
            {
               i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
               io_info_ptr->RX_REQUEST--;
               if (0 == io_info_ptr->RX_REQUEST)
               {
                  i2c_ptr->I2CR &= (~ (MCF52XX_I2C_I2CR_MSTA | MCF52XX_I2C_I2CR_MTX | MCF52XX_I2C_I2CR_TXAK));
                  io_info_ptr->STATE = I2C_STATE_FINISHED;
               }
               else
               {
                  io_info_ptr->ONTHEWAY = TRUE;
               }
               if (1 == io_info_ptr->RX_REQUEST)
               {
                  i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_TXAK;
               }
               io_info_ptr->RX_BUFFER[io_info_ptr->RX_IN] = i2c_ptr->I2DR;   // receive data
               io_info_ptr->RX_IN = tmp;
               io_info_ptr->STATISTICS.RX_PACKETS++;
            }
         }
         /* Others are unwanted/not handled states */
         else
         {
            i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
         }
      }
   }
   /* Slave */
   else
   {
      /* Master arbitration lost */
      if (i2csr & MCF52XX_I2C_I2SR_IAL)
      {
         i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IAL);
         io_info_ptr->TX_OUT = io_info_ptr->TX_IN;
         io_info_ptr->RX_IN = io_info_ptr->RX_OUT;
         io_info_ptr->STATISTICS.TX_LOST_ARBITRATIONS++;
         io_info_ptr->STATE = I2C_STATE_LOST_ARBITRATION;
      }
      /* Adressed as slave */
      if (i2csr & MCF52XX_I2C_I2SR_IAAS)
      {
         if (I2C_MODE_MASTER == io_info_ptr->MODE)
         {
            io_info_ptr->TX_OUT = io_info_ptr->TX_IN;
            io_info_ptr->RX_IN = io_info_ptr->RX_OUT;
            io_info_ptr->STATISTICS.TX_ADDRESSED_AS_SLAVE++;
         }
         /* Transmit requested */
         if (i2csr & MCF52XX_I2C_I2SR_SRW)
         {
            if ((I2C_STATE_TRANSMIT != io_info_ptr->STATE) && (I2C_STATE_ADDRESSED_AS_SLAVE_TX != io_info_ptr->STATE))
            {
               io_info_ptr->TX_OUT = io_info_ptr->TX_IN;
               io_info_ptr->RX_IN = io_info_ptr->RX_OUT;
            }
            i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_MTX;
            io_info_ptr->STATE = I2C_STATE_ADDRESSED_AS_SLAVE_TX;
            if (io_info_ptr->TX_IN == io_info_ptr->TX_OUT)
            {
               i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_IIEN);
            }
            else
            {
               i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
               io_info_ptr->ONTHEWAY = TRUE;
               i2c_ptr->I2DR = io_info_ptr->TX_BUFFER[io_info_ptr->TX_OUT++];   // transmit data
               if (io_info_ptr->TX_OUT >= io_info_ptr->INIT.TX_BUFFER_SIZE) io_info_ptr->TX_OUT = 0;
               io_info_ptr->STATISTICS.TX_PACKETS++;
            }
         }
         /* Receive requested */
         else
         {
            i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
            i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_MTX);
            if ((I2C_STATE_RECEIVE != io_info_ptr->STATE) && (I2C_STATE_ADDRESSED_AS_SLAVE_RX != io_info_ptr->STATE))
            {
               io_info_ptr->TX_OUT = io_info_ptr->TX_IN;
               io_info_ptr->RX_IN = io_info_ptr->RX_OUT;
            }
            else
            {
               if (1 == io_info_ptr->RX_REQUEST)
               {
                  i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_TXAK;
               }
            }
            io_info_ptr->STATE = I2C_STATE_ADDRESSED_AS_SLAVE_RX;
            io_info_ptr->ONTHEWAY = TRUE;
            tmp = i2c_ptr->I2DR;   // dummy read to release bus
         }
      }
      /* Normal slave operation */
      else
      {
         /* No master arbitration lost */
         if (! (i2csr & MCF52XX_I2C_I2SR_IAL))
         {
            /* Transmit */
            if (i2c_ptr->I2CR & MCF52XX_I2C_I2CR_MTX)
            {
               /* Not ack */
               if (i2csr & MCF52XX_I2C_I2SR_RXAK)
               {
                  i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
                  i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_MTX);
                  tmp = i2c_ptr->I2DR;   // dummy read to release bus
                  io_info_ptr->STATISTICS.TX_NAKS++;
                  io_info_ptr->STATE = I2C_STATE_FINISHED;
               }
               /* Ack */
               else
               {
                  /* Transmit requested */
                  if ((I2C_STATE_TRANSMIT == io_info_ptr->STATE) || (I2C_STATE_ADDRESSED_AS_SLAVE_TX == io_info_ptr->STATE))
                  {
                     if (io_info_ptr->TX_IN == io_info_ptr->TX_OUT)
                     {
                        i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_IIEN);
                     }
                     else
                     {
                        i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
                        io_info_ptr->ONTHEWAY = TRUE;
                        i2c_ptr->I2DR = io_info_ptr->TX_BUFFER[io_info_ptr->TX_OUT++];   // transmit data
                        if (io_info_ptr->TX_OUT >= io_info_ptr->INIT.TX_BUFFER_SIZE) io_info_ptr->TX_OUT = 0;
                        io_info_ptr->STATISTICS.TX_PACKETS++;
                     }
                  }
                  else
                  {
                     i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_IIEN);
                  }
               }
            }
            /* Receive */
            else
            {
               /* Receive requested */
               if (((I2C_STATE_RECEIVE == io_info_ptr->STATE) || (I2C_STATE_ADDRESSED_AS_SLAVE_RX == io_info_ptr->STATE)) && (0 != io_info_ptr->RX_REQUEST))
               {
                  tmp = io_info_ptr->RX_IN++;
                  if (tmp >= io_info_ptr->INIT.RX_BUFFER_SIZE) tmp = 0;
                  if (tmp == io_info_ptr->RX_OUT)
                  {
                     i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_IIEN);
                  }
                  else
                  {
                     i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
                     io_info_ptr->RX_REQUEST--;
                     if (1 == io_info_ptr->RX_REQUEST)
                     {
                        i2c_ptr->I2CR |= MCF52XX_I2C_I2CR_TXAK;
                     }
                     io_info_ptr->ONTHEWAY = TRUE;
                     io_info_ptr->RX_BUFFER[io_info_ptr->RX_IN] = i2c_ptr->I2DR;   // receive data
                     io_info_ptr->RX_IN = tmp;
                     io_info_ptr->STATISTICS.RX_PACKETS++;
                  }
               }
               else
               {
                  i2c_ptr->I2CR &= (~ MCF52XX_I2C_I2CR_IIEN);
               }
            }
         }
         else
         {
            i2c_ptr->I2SR &= (~ MCF52XX_I2C_I2SR_IIF);
         }
      }
   }
} /* Endbody */

/* EOF */

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
* $FileName: i2c_pol_mcf51xx.c$
* $Version : 3.7.15.0$
* $Date    : Feb-22-2011$
*
* Comments:
*
*   This file contains low level functions for the I2C polled device driver
*   for 51XX Coldfire family.
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include <io_prv.h>
#include <fio_prv.h>
#include "i2c.h"
#include "i2c_pol_prv.h"
#include "i2c_mcf51xx_prv.h"


extern uint_32 _mcf51xx_i2c_polled_init (MCF51XX_I2C_INIT_STRUCT_PTR, pointer _PTR_, char_ptr);
extern uint_32 _mcf51xx_i2c_polled_deinit (IO_I2C_POLLED_DEVICE_STRUCT_PTR, MCF51XX_I2C_INFO_STRUCT_PTR);
extern uint_32 _mcf51xx_i2c_polled_rx (IO_I2C_POLLED_DEVICE_STRUCT_PTR, uchar_ptr, uint_32);
extern uint_32 _mcf51xx_i2c_polled_tx (IO_I2C_POLLED_DEVICE_STRUCT_PTR, uchar_ptr, uint_32);
extern uint_32 _mcf51xx_i2c_polled_ioctl (MCF51XX_I2C_INFO_STRUCT_PTR, uint_32, uint_32_ptr);
static uint_8  _mcf51xx_i2c_find_baud_index (uint_32);
static uint_32 _mcf51xx_i2c_polled_rx_tx (VMCF51XX_I2C_STRUCT_PTR, MCF51XX_I2C_INFO_STRUCT_PTR, uchar_ptr, uint_32);


/* I2C frequency divider values */
                  
/************************************************************************** 
IIC baud rate = bus speed (Hz)/(mul * SCL divider)
IIC baud rate = bus speed (Hz)/(mul * SCL divider)
SCL Start hold time = bus period (s) * mul * Start value
SCL Stop hold time = bus period (s) * mul *  Stop  value
***************************************************************************/
/* duplicated items are commented out, if commented out value is wanted, uncoment it,
   comment out duplicated and rebuilt bsp */
static const MCF51XX_I2C_BAUDRATE_STRUCT _i2c_baudrate_tbl[] = {
/*                                 SCL   ICR   SDA Hold Start  Stop
                                divider (hex)     value value  value*/
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/3840, 0x3F},    //513  1918  1921
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/3072, 0x3E},    //513  1534  1537
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/2560, 0x3D},    //385  1278  1281
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/2304, 0x3C},    //385  1150  1153
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/2048, 0x3B},    //257  1022  1025
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/1920, 0x37},    //257  958   961
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/1792, 0x3A},    //257  894   897
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/1536, 0x36},    //257  766   769
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/1536, 0x39},    //129  766   769
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/1280, 0x35},    //193  638   641
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/1280, 0x38},    //129  638   641
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/1151, 0x34},    //193  574   577
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/1024, 0x33},    //129  510   513
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/960 , 0x2F},    //129  478   481
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/896 , 0x32},    //129  446   449
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/768 , 0x2E},    //129  382   385
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/768 , 0x31},    //65   382   385
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/640 , 0x2D},    //97   318   321
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/640 , 0x30},    //65   318   321
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/576 , 0x2C},    //97   286   289
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/512 , 0x2B},    //65   254   257
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/480 , 0x27},    //65   238   241
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/448 , 0x2A},    //65   222   225
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/384 , 0x26},    //65   190   193
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/384 , 0x29},    //33   190   193
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/320 , 0x25},    //49   158   161
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/320 , 0x28},    //33   158   161
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/288 , 0x24},    //49   142   145
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/256 , 0x23},    //33   126   129
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/240 , 0x1F},    //33   118   121
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/224 , 0x22},    //33   110   113
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/192 , 0x21},    //17   094   97
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/192 , 0x1E},    //33   094   97
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/160 , 0x1D},    //25   078   81
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/160 , 0x20},    //17   078   81
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/144 , 0x1C},    //25   070   73
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/128 , 0x17},    //21   058   65
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/128 , 0x1B},    //17   062   65
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/112 , 0x1A},    //17   054   57
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/104 , 0x16},    //21   046   53
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/96  , 0x19},    //09   046   49
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/88  , 0x15},    //17   038   45
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/80  , 0x14},    //17   034   41
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/80  , 0x18},    //09   038   41
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/72  , 0x13},    //13   030   37
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/68  , 0x0F},    //13   030   35
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/64  , 0x12},    //13   026   33
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/56  , 0x0E},    //13   024   29
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/56  , 0x11},    //09   022   29
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/48  , 0x0D},    //11   020   25
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/48  , 0x10},    //09   018   25
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/44  , 0x0C},    //11   018   23
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/40  , 0x07},    //10   016   21
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/40  , 0x0B},    //09   016   21
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/36  , 0x0A},    //09   014   19
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/34  , 0x06},    //10   013   18
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/32  , 0x09},    //07   012   17
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/30  , 0x05},    //09   011   16
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/28  , 0x04},    //09   010   15
//{BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/28  , 0x08},    //07   010   15
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/26  , 0x03},    //08   009   14
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/24  , 0x02},    //08   008   13
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/22  , 0x01},    //07   007   12
  {BSP_I2C_CLOCK/BSP_I2C_MULT_VAL/20  , 0x00},    //07   006   110
};
              

/*FUNCTION****************************************************************
* 
* Function Name    : _mcf51xx_i2c_find_baud_index
* Returned Value   : index into table of baudrate dividers
* Comments         :
*    Find best I2C setting for given baudrate.
*
*END*********************************************************************/
              
static uint_8 _mcf51xx_i2c_find_baud_index 
   (
      /* [IN] A baud rate to find divider for */
      uint_32 input_baud
   )
{
   uint_8 low, high, i;
   
   low = 0; high = sizeof (_i2c_baudrate_tbl) / sizeof (MCF51XX_I2C_BAUDRATE_STRUCT) - 1;
   
   do 
   {
      i = (low + high) >> 1;
      if (input_baud < _i2c_baudrate_tbl[i].BAUD_RATE)
      {
         high = i - 1;
      } else {
         low = i + 1;
      }
   } while ((_i2c_baudrate_tbl[i].BAUD_RATE != input_baud) && (high >= low));
   
   /* in case we did not found exact BAUD rate use nearest slower settings than requested */
   if ((_i2c_baudrate_tbl[i].BAUD_RATE > input_baud) && (i != 0))
   {
      i--;
   }
   
   return i;
}


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf51xx_i2c_polled_install
* Returned Value   : MQX error code
* Comments         :
*    Install an I2C device.
*
*END*********************************************************************/

uint_32 _mcf51xx_i2c_polled_install
   (
      /* [IN] A string that identifies the device for fopen */
      char_ptr           identifier,
  
      /* [IN] The I/O init data pointer */
      MCF51XX_I2C_INIT_STRUCT_CPTR  init_data_ptr
   )
{ /* Body */

   return _io_i2c_polled_install(identifier,
      (uint_32 (_CODE_PTR_)(pointer, pointer _PTR_, char_ptr))_mcf51xx_i2c_polled_init,
      (uint_32 (_CODE_PTR_)(pointer, pointer))_mcf51xx_i2c_polled_deinit,
      (int_32 (_CODE_PTR_)(pointer, char_ptr, int_32))_mcf51xx_i2c_polled_rx,
      (int_32 (_CODE_PTR_)(pointer, char_ptr, int_32))_mcf51xx_i2c_polled_tx,
      (int_32 (_CODE_PTR_)(pointer, uint_32, uint_32_ptr))_mcf51xx_i2c_polled_ioctl, 
      (pointer)init_data_ptr);

} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf51xx_i2c_polled_init
* Returned Value   : MQX error code
* Comments         :
*    This function initializes an I2C device.
*
*END*********************************************************************/

uint_32 _mcf51xx_i2c_polled_init
   (
      /* [IN] Initialization information for the device being opened */
      MCF51XX_I2C_INIT_STRUCT_PTR   io_init_ptr,

      /* [OUT] Address to store device specific information */
      pointer _PTR_                 io_info_ptr_ptr,
       
      /* [IN] The rest of the name of the device opened */
      char_ptr                      open_name_ptr

   )
{ /* Body */
   VMCF51XX_I2C_STRUCT_PTR          i2c_ptr;
   MCF51XX_I2C_INFO_STRUCT_PTR      io_info_ptr;

   i2c_ptr = _bsp_get_i2c_base_address (io_init_ptr->CHANNEL);
   if (NULL == i2c_ptr)
   {
        return I2C_ERROR_CHANNEL_INVALID;
   }
  
   io_info_ptr = (MCF51XX_I2C_INFO_STRUCT_PTR)_mem_alloc_system_zero ((uint_32)sizeof (MCF51XX_I2C_INFO_STRUCT));
   if (NULL == io_info_ptr) 
   {
      return MQX_OUT_OF_MEMORY;
   }
   _mem_set_type (io_info_ptr, MEM_TYPE_IO_I2C_INFO_STRUCT);

   /* I2C board specific initialization */
   _bsp_i2c_io_init (io_init_ptr->CHANNEL);

   *io_info_ptr_ptr = io_info_ptr;
   io_info_ptr->INIT                             = *io_init_ptr;
   io_info_ptr->I2C_PTR                          = i2c_ptr;
   io_info_ptr->MODE                             = io_init_ptr->MODE;
   io_info_ptr->STATE                            = I2C_STATE_READY;
   io_info_ptr->ADDRESSEE                        = 0;
   io_info_ptr->ONTHEWAY                         = FALSE;
   io_info_ptr->RX_REQUEST                       = 0;
   io_info_ptr->RX_BUFFER                        = NULL;
   io_info_ptr->RX_IN                            = 0;
   io_info_ptr->RX_OUT                           = 0;
   io_info_ptr->TX_BUFFER                        = NULL;
   io_info_ptr->TX_IN                            = 0;
   io_info_ptr->TX_OUT                           = 0;
   io_info_ptr->STATISTICS.INTERRUPTS            = 0;
   io_info_ptr->STATISTICS.RX_PACKETS            = 0;
   io_info_ptr->STATISTICS.TX_PACKETS            = 0;
   io_info_ptr->STATISTICS.TX_LOST_ARBITRATIONS  = 0;
   io_info_ptr->STATISTICS.TX_ADDRESSED_AS_SLAVE = 0;
   io_info_ptr->STATISTICS.TX_NAKS               = 0;

   /* Disable and clear I2C before initializing it */
   i2c_ptr->IICC1 = 0;
   i2c_ptr->IICC2 = 0;
#if I2C_SMB_SUPPORT    
   i2c_ptr->IICSMB = 0;
   i2c_ptr->IICSLTL = 0;
   i2c_ptr->IICSLTH = 0;
   i2c_ptr->IICFLT = 0;
#endif       
   /* Clear out all I2C events */
   i2c_ptr->IICS = 0;

   /* Set the station address for SLAVE receive operations */      
   i2c_ptr->IICA1 = io_init_ptr->STATION_ADDRESS << 1;
#if I2C_SMB_SUPPORT      
   i2c_ptr->IICA2 = 0;
#endif   

   /* Set the frequency divider for the nearest found baud rate */
   io_info_ptr->BAUD_INDEX = _mcf51xx_i2c_find_baud_index (io_init_ptr->BAUD_RATE);
   i2c_ptr->IICF = MCF51XX_IICF_SET(BSP_I2C_MULT_IICF_BITS, _i2c_baudrate_tbl[io_info_ptr->BAUD_INDEX].ICR);
  
   /* Enable I2C */
   i2c_ptr->IICC1 |= MCF51XX_IICC1_IICEN_MASK;

   return I2C_OK;
   
} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf51xx_i2c_polled_deinit
* Returned Value   : MQX error code
* Comments         :
*    This function de-initializes an I2C device.
*
*END*********************************************************************/

uint_32 _mcf51xx_i2c_polled_deinit
   (
      /* [IN] the initialization information for the device being opened */
      IO_I2C_POLLED_DEVICE_STRUCT_PTR pol_io_dev_ptr,

      /* [IN] the address of the device specific information */
      MCF51XX_I2C_INFO_STRUCT_PTR     io_info_ptr
   )
{ /* Body */
   VMCF51XX_I2C_STRUCT_PTR            i2c_ptr;

   if ((NULL == io_info_ptr) || (NULL == pol_io_dev_ptr)) 
   {
      return I2C_ERROR_INVALID_PARAMETER;
   }
   
   i2c_ptr = io_info_ptr->I2C_PTR;

   if (i2c_ptr->IICS & MCF51XX_IICS_BUSY_MASK) 
   {
      return I2C_ERROR_DEVICE_BUSY;
   }
   
   /* Disable the I2C */
   i2c_ptr->IICC1 = 0;

   /* Clear the I2C events */
   i2c_ptr->IICS = 0; 
 
   /* Free info struct */
   _mem_free (pol_io_dev_ptr->DEV_INFO_PTR);
   pol_io_dev_ptr->DEV_INFO_PTR = NULL;

   return MQX_OK;

} /* Endbody */

 
/*FUNCTION****************************************************************
* 
* Function Name    : _mcf51xx_i2c_polled_ioctl
* Returned Value   : MQX error code.
* Comments         : 
*    This function performs miscellaneous services for
*    the I2C I/O device.  
*
*END*********************************************************************/

uint_32 _mcf51xx_i2c_polled_ioctl
   (
      /* [IN] the address of the device specific information */
      MCF51XX_I2C_INFO_STRUCT_PTR io_info_ptr,

      /* [IN] The command to perform */
      uint_32                     cmd,

      /* [IN] Parameters for the command */
      uint_32_ptr                 param_ptr
   )
{ /* Body */
   VMCF51XX_I2C_STRUCT_PTR        i2c_ptr;
   uint_32                        result = MQX_OK;
   volatile uint_8                tmp, state;
  
   i2c_ptr = io_info_ptr->I2C_PTR;
   
   switch (cmd) 
   {
      case IO_IOCTL_FLUSH_OUTPUT:
         do 
         {
            tmp = i2c_ptr->IICS;
         } while ((0 == (tmp & MCF51XX_IICS_TCF_MASK)) || (io_info_ptr->ONTHEWAY) || ((i2c_ptr->IICC1 & MCF51XX_IICC1_TX_MASK) && (io_info_ptr->TX_IN != io_info_ptr->TX_OUT)));
         if (NULL != param_ptr) 
         {
            *param_ptr = tmp & MCF51XX_IICS_RXAK_MASK;
         }
         break;
      case IO_IOCTL_I2C_REPEATED_START:
         if (i2c_ptr->IICC1 & MCF51XX_IICC1_MST_MASK)
         {
            if ((I2C_STATE_TRANSMIT == io_info_ptr->STATE) || (I2C_STATE_RECEIVE == io_info_ptr->STATE) || (I2C_STATE_FINISHED == io_info_ptr->STATE))
            {
               io_info_ptr->STATE = I2C_STATE_REPEATED_START;
               io_info_ptr->TX_IN = io_info_ptr->TX_OUT;
               io_info_ptr->RX_OUT = io_info_ptr->RX_IN;
               io_info_ptr->RX_REQUEST = 0;
            }
         }
         break;
      case IO_IOCTL_I2C_STOP:
         i2c_ptr->IICC1 &= (~ (MCF51XX_IICC1_TX_MASK | MCF51XX_IICC1_TXAK_MASK));
         if (! (i2c_ptr->IICC1 & MCF51XX_IICC1_MST_MASK))
         {
            tmp = i2c_ptr->IICD;
         }
         i2c_ptr->IICS |= (MCF51XX_IICS_ARBL_MASK | MCF51XX_IICS_IICIF_MASK);
         i2c_ptr->IICC1 &= (~ MCF51XX_IICC1_MST_MASK);
         io_info_ptr->TX_IN = io_info_ptr->TX_OUT;
         io_info_ptr->RX_OUT = io_info_ptr->RX_IN;
         io_info_ptr->RX_REQUEST = 0;
         io_info_ptr->STATE = I2C_STATE_READY;
         while (i2c_ptr->IICS & MCF51XX_IICS_BUSY_MASK)
            { };   // wait for completion
         break;
        case IO_IOCTL_I2C_SET_RX_REQUEST:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            io_info_ptr->RX_REQUEST = *param_ptr;
         }
           break;
      case IO_IOCTL_I2C_DISABLE_DEVICE:
         i2c_ptr->IICC1 &= (~ MCF51XX_IICC1_IICEN_MASK);
         break;
      case IO_IOCTL_I2C_ENABLE_DEVICE:
         i2c_ptr->IICC1 |= MCF51XX_IICC1_IICEN_MASK;
         break;
      case IO_IOCTL_I2C_SET_MASTER_MODE:
         if (I2C_STATE_READY != io_info_ptr->STATE) 
         {
            result = I2C_ERROR_DEVICE_BUSY;
         } 
         else 
         {
            io_info_ptr->MODE = I2C_MODE_MASTER;
         }
         break;
      case IO_IOCTL_I2C_SET_SLAVE_MODE:
         if (I2C_STATE_READY != io_info_ptr->STATE) 
         {
            result = I2C_ERROR_DEVICE_BUSY;
         } 
         else 
         {
            io_info_ptr->MODE = I2C_MODE_SLAVE;
         }
         break;
      case IO_IOCTL_I2C_GET_MODE:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            *param_ptr = io_info_ptr->MODE;
         }
         break;
      case IO_IOCTL_I2C_SET_BAUD:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else if (I2C_STATE_READY != io_info_ptr->STATE) 
         {
            result = I2C_ERROR_DEVICE_BUSY;
         } 
         else 
         {
            io_info_ptr->BAUD_INDEX = _mcf51xx_i2c_find_baud_index (*param_ptr);
            i2c_ptr->IICF = MCF51XX_IICF_SET(BSP_I2C_MULT_IICF_BITS, _i2c_baudrate_tbl[io_info_ptr->BAUD_INDEX].ICR);
         }
         break;
      case IO_IOCTL_I2C_GET_BAUD:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            *param_ptr = _i2c_baudrate_tbl[io_info_ptr->BAUD_INDEX].BAUD_RATE;
         }
         break;
      case IO_IOCTL_I2C_SET_DESTINATION_ADDRESS:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            io_info_ptr->ADDRESSEE = *param_ptr;
         }
         break;
      case IO_IOCTL_I2C_GET_DESTINATION_ADDRESS:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            *param_ptr = io_info_ptr->ADDRESSEE;
         }
         break;
      case IO_IOCTL_I2C_SET_STATION_ADDRESS:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            i2c_ptr->IICA1 = (*param_ptr) << 1;
         }
         break;
      case IO_IOCTL_I2C_GET_STATION_ADDRESS:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            *param_ptr = i2c_ptr->IICA1 >> 1;
         }
         break;
      case IO_IOCTL_I2C_GET_STATE:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            *param_ptr = io_info_ptr->STATE;
         }
         break;
      case IO_IOCTL_I2C_GET_STATISTICS:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            *((I2C_STATISTICS_STRUCT_PTR)param_ptr) = io_info_ptr->STATISTICS;
         }
         break;         
      case IO_IOCTL_I2C_CLEAR_STATISTICS:
         io_info_ptr->STATISTICS.INTERRUPTS = 0;
         io_info_ptr->STATISTICS.RX_PACKETS = 0;
         io_info_ptr->STATISTICS.TX_PACKETS = 0;
         io_info_ptr->STATISTICS.TX_LOST_ARBITRATIONS = 0;
         io_info_ptr->STATISTICS.TX_ADDRESSED_AS_SLAVE = 0;
         io_info_ptr->STATISTICS.TX_NAKS = 0;
         break;
      case IO_IOCTL_I2C_GET_BUS_AVAILABILITY:
         if (NULL == param_ptr) 
         {
            result = I2C_ERROR_INVALID_PARAMETER;
         } 
         else 
         {
            if (i2c_ptr->IICS & MCF51XX_IICS_BUSY_MASK) 
            {
                *param_ptr = I2C_BUS_BUSY;
            } 
            else 
            {
                *param_ptr = I2C_BUS_IDLE;
            }
         }
         break;
      default:
         break;
   }
   return result;
} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf51xx_i2c_polled_rx
* Returned Value   : number of bytes read
* Comments         : 
*   Returns the number of bytes received.
*   Reads the data into provided array when data is available.
*
*END*********************************************************************/

uint_32 _mcf51xx_i2c_polled_rx
   (
      /* [IN] the address of the device specific information */
      IO_I2C_POLLED_DEVICE_STRUCT_PTR pol_io_dev_ptr,

      /* [IN] The array to copy data into */
      uchar_ptr                       buffer,
      
      /* [IN] number of bytes to read */
      uint_32                         length
   )
{ /* Body */
   MCF51XX_I2C_INFO_STRUCT_PTR        io_info_ptr;
   VMCF51XX_I2C_STRUCT_PTR            i2c_ptr;   
   uint_8                             tmp;
         
   io_info_ptr = pol_io_dev_ptr->DEV_INFO_PTR;
   i2c_ptr = io_info_ptr->I2C_PTR;

   /* If beginning of transmission, set state and send address (master only) */
   tmp = io_info_ptr->STATE;
   if ((I2C_STATE_READY == tmp) || (I2C_STATE_REPEATED_START == tmp))
   {
      io_info_ptr->STATE = I2C_STATE_RECEIVE;
      if (I2C_MODE_MASTER == io_info_ptr->MODE)
      {
         i2c_ptr->IICC1 |= MCF51XX_IICC1_TX_MASK;
         if (I2C_STATE_REPEATED_START == tmp)
         {
            i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
            i2c_ptr->IICC1 |= MCF51XX_IICC1_RSTA_MASK;
            while (0 == (i2c_ptr->IICS & MCF51XX_IICS_TCF_MASK)) 
               { };   // wait for completion
         }
         else
         {
            i2c_ptr->IICC1 |= MCF51XX_IICC1_MST_MASK;
         }
         io_info_ptr->ONTHEWAY = TRUE;
         i2c_ptr->IICD = (io_info_ptr->ADDRESSEE << 1) | I2C_OPERATION_READ;
         io_info_ptr->STATISTICS.TX_PACKETS++;
      }
   }

   return _mcf51xx_i2c_polled_rx_tx (i2c_ptr, io_info_ptr, buffer, length);
} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf51xx_i2c_polled_tx
* Returned Value   : number of bytes transmitted
* Comments         : 
*   Writes the provided data buffer and loops until transmission complete.
*
*END*********************************************************************/

uint_32 _mcf51xx_i2c_polled_tx
   (
      /* [IN] the address of the device specific information */
      IO_I2C_POLLED_DEVICE_STRUCT_PTR pol_io_dev_ptr,

      /* [IN] The array characters are to be read from */
      uchar_ptr                       buffer,
      
      /* [IN] number of bytes to output */
      uint_32                         length
   )
{ /* Body */
   MCF51XX_I2C_INFO_STRUCT_PTR        io_info_ptr;
   VMCF51XX_I2C_STRUCT_PTR            i2c_ptr;   
   uint_8                             tmp;
   
   io_info_ptr  = pol_io_dev_ptr->DEV_INFO_PTR;
   i2c_ptr = io_info_ptr->I2C_PTR;

   /* If beginning of transmission, set state and send address (master only) */
   tmp = io_info_ptr->STATE;
   if ((I2C_STATE_READY == tmp) || (I2C_STATE_REPEATED_START == tmp))
   {
      io_info_ptr->STATE = I2C_STATE_TRANSMIT;
      if (I2C_MODE_MASTER == io_info_ptr->MODE)
      {
         i2c_ptr->IICC1 |= MCF51XX_IICC1_TX_MASK;
         if (I2C_STATE_REPEATED_START == tmp)
         {
            i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
            i2c_ptr->IICC1 |= MCF51XX_IICC1_RSTA_MASK;
            while (0 == (i2c_ptr->IICS & MCF51XX_IICS_TCF_MASK))
               { };   // wait for completion
         }
         else
         {
            i2c_ptr->IICC1 |= MCF51XX_IICC1_MST_MASK;
         }
         io_info_ptr->ONTHEWAY = TRUE;
         i2c_ptr->IICD = (io_info_ptr->ADDRESSEE << 1) | I2C_OPERATION_WRITE;
         io_info_ptr->STATISTICS.TX_PACKETS++;
      }
   }

   return _mcf51xx_i2c_polled_rx_tx (i2c_ptr, io_info_ptr, buffer, length);
} /* Endbody */


/*FUNCTION****************************************************************
* 
* Function Name    : _mcf51xx_i2c_polled_rx_tx
* Returned Value   : number of bytes processed
* Comments         : 
*   Actual data transfer on I2C bus.
*
*END*********************************************************************/

static uint_32 _mcf51xx_i2c_polled_rx_tx
   (
      /* [IN] I2C register structure */
      VMCF51XX_I2C_STRUCT_PTR     i2c_ptr,

      /* [IN] I2C state structure */
      MCF51XX_I2C_INFO_STRUCT_PTR io_info_ptr,
      
      /* [IN] The buffer for IO operation */
      uchar_ptr                   buffer,
      
      /* [IN] Number of bytes in buffer */
      uint_32                     length
   )
{ /* Body */
   uint_32                        i;
   uint_8                         i2csr;
   volatile uint_8                tmp;

   for (i = 0; i <= length; i++)
   {
      do 
      {
         i2csr = i2c_ptr->IICS;
      } while (0 == (i2csr & MCF51XX_IICS_IICIF_MASK));
      io_info_ptr->ONTHEWAY = FALSE;
   
      /* Master */
      if (i2c_ptr->IICC1 & MCF51XX_IICC1_MST_MASK)
      {
         /* Transmit */
         if (i2c_ptr->IICC1 & MCF51XX_IICC1_TX_MASK)
         {
            /* Not ack */
            if (i2csr & MCF51XX_IICS_RXAK_MASK)
            {
               i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
               i2c_ptr->IICC1 &= (~ MCF51XX_IICC1_TX_MASK);
               io_info_ptr->STATISTICS.TX_NAKS++;
               io_info_ptr->STATE = I2C_STATE_FINISHED;
               length = i;
            }
            /* Ack */
            else
            {
               /* Transmit requested */
               if (I2C_STATE_TRANSMIT == io_info_ptr->STATE)
               {
                  /* Anything to transmit? */
                  if (i < length)
                  {
                     i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
                     io_info_ptr->ONTHEWAY = TRUE;
                     i2c_ptr->IICD = *buffer++;   // transmit data
                     io_info_ptr->STATISTICS.TX_PACKETS++;
                  }
               }
               /* Receive requested */
               else if (I2C_STATE_RECEIVE == io_info_ptr->STATE)
               {
                  i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
                  i2c_ptr->IICC1 &= (~ MCF51XX_IICC1_TX_MASK);
                  if (1 == io_info_ptr->RX_REQUEST)
                  {
                     i2c_ptr->IICC1 |= MCF51XX_IICC1_TXAK_MASK;
                  }
                  if (0 == io_info_ptr->RX_REQUEST)
                  {
                     i2c_ptr->IICC1 &= (~ (MCF51XX_IICC1_MST_MASK | MCF51XX_IICC1_TX_MASK | MCF51XX_IICC1_TXAK_MASK));
                     io_info_ptr->STATE = I2C_STATE_FINISHED;
                     length = i;
                  }
                  else
                  {
                     io_info_ptr->ONTHEWAY = TRUE;
                     tmp = i2c_ptr->IICD;   // dummy read to clock in 1st byte
                     i--;
                  }
               }
               else
               {
                  i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
                  length = i;
               }
            }
         }
         /* Receive */
         else
         {
            /* Receive requested */
            if ((I2C_STATE_RECEIVE == io_info_ptr->STATE) && (0 != io_info_ptr->RX_REQUEST))
            {
               if (i < length)
               {
                  i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
                  io_info_ptr->RX_REQUEST--;
                  if (0 == io_info_ptr->RX_REQUEST)
                  {
                     i2c_ptr->IICC1 &= (~ (MCF51XX_IICC1_MST_MASK | MCF51XX_IICC1_TX_MASK | MCF51XX_IICC1_TXAK_MASK));
                     io_info_ptr->STATE = I2C_STATE_FINISHED;
                     length = i + 1;
                     i = length;
                  }
                  else
                  {
                     io_info_ptr->ONTHEWAY = TRUE;
                  }
                  if (1 == io_info_ptr->RX_REQUEST)
                  {
                     i2c_ptr->IICC1 |= MCF51XX_IICC1_TXAK_MASK;
                  }
                  *buffer++ = i2c_ptr->IICD;   // receive data
                  io_info_ptr->STATISTICS.RX_PACKETS++;
               }
            }
            else 
            {
               i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
               length = i;
            }
         }
      }
      /* Slave */
      else
      {
         /* Master arbitration lost */
         if (i2csr & MCF51XX_IICS_ARBL_MASK)
         {
            i2c_ptr->IICS |= MCF51XX_IICS_ARBL_MASK;
            length = i;
            io_info_ptr->STATISTICS.TX_LOST_ARBITRATIONS++;
            io_info_ptr->STATE = I2C_STATE_LOST_ARBITRATION;
         }
         /* Adressed as slave */
         if (i2csr & MCF51XX_IICS_IAAS_MASK)
         {
            if (I2C_MODE_MASTER == io_info_ptr->MODE)
            {
               length = i;
               io_info_ptr->STATISTICS.TX_ADDRESSED_AS_SLAVE++;
            }
            /* Transmit requested */
            if (i2csr & MCF51XX_IICS_SRW_MASK)
            {  
               if ((I2C_STATE_TRANSMIT != io_info_ptr->STATE) && (I2C_STATE_ADDRESSED_AS_SLAVE_TX != io_info_ptr->STATE))
               {
                  length = i;
               }
               i2c_ptr->IICC1 |= MCF51XX_IICC1_TX_MASK;
               io_info_ptr->STATE = I2C_STATE_ADDRESSED_AS_SLAVE_TX;
               if (i < length)
               {
                  i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
                  io_info_ptr->ONTHEWAY = TRUE;
                  i2c_ptr->IICD = *buffer++;   // transmit data
                  io_info_ptr->STATISTICS.TX_PACKETS++;
               }
            }
            /* Receive requested */
            else
            {
               i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
               i2c_ptr->IICC1 &= (~ MCF51XX_IICC1_TX_MASK);
               if ((I2C_STATE_RECEIVE != io_info_ptr->STATE) && (I2C_STATE_ADDRESSED_AS_SLAVE_RX != io_info_ptr->STATE))
               {
                  length = i;
               }
               else
               {
                  if (1 == io_info_ptr->RX_REQUEST)
                  {
                     i2c_ptr->IICC1 |= MCF51XX_IICC1_TXAK_MASK;
                  }
               }
               io_info_ptr->STATE = I2C_STATE_ADDRESSED_AS_SLAVE_RX;
               io_info_ptr->ONTHEWAY = TRUE;
               tmp = i2c_ptr->IICD;   // dummy read to release bus
               i--;
            }
         }
         /* Normal slave operation */
         else
         {
            /* No master arbitration lost */
            if (! (i2csr & MCF51XX_IICS_ARBL_MASK))
            {
               /* Transmit */
               if (i2c_ptr->IICC1 & MCF51XX_IICC1_TX_MASK)
               {
                  /* Not ack */
                  if (i2csr & MCF51XX_IICS_RXAK_MASK)
                  {
                     i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
                     i2c_ptr->IICC1 &= (~ MCF51XX_IICC1_TX_MASK);
                     tmp = i2c_ptr->IICD;   // dummy read to release bus
                     io_info_ptr->STATISTICS.TX_NAKS++;
                     io_info_ptr->STATE = I2C_STATE_FINISHED;
                     length = i;
                  }
                  /* Ack */
                  else
                  {
                     /* Transmit requested */
                     if ((I2C_STATE_TRANSMIT == io_info_ptr->STATE) || (I2C_STATE_ADDRESSED_AS_SLAVE_TX == io_info_ptr->STATE))
                     {
                        if (i < length)
                        {
                           i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
                           io_info_ptr->ONTHEWAY = TRUE;
                           i2c_ptr->IICD = *buffer++;   // transmit data
                           io_info_ptr->STATISTICS.TX_PACKETS++;
                        }
                     }
                     else
                     {
                        length = i;
                     }
                  }
               }
               /* Receive */
               else
               {
                  /* Receive requested */
                  if (((I2C_STATE_RECEIVE == io_info_ptr->STATE) || (I2C_STATE_ADDRESSED_AS_SLAVE_RX == io_info_ptr->STATE)) && (0 != io_info_ptr->RX_REQUEST))
                  {
                     if (i < length)
                     {
                        i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
                        io_info_ptr->RX_REQUEST--;
                        if (1 == io_info_ptr->RX_REQUEST)
                        {
                           i2c_ptr->IICC1 |= MCF51XX_IICC1_TXAK_MASK;
                        }
                        io_info_ptr->ONTHEWAY = TRUE;
                        *buffer++ = i2c_ptr->IICD;   // receive data
                        io_info_ptr->STATISTICS.RX_PACKETS++;
                     }
                  }
                  else
                  {
                     length = i;
                  }
               }
            }
            else
            {
               i2c_ptr->IICS |= MCF51XX_IICS_IICIF_MASK;
            }
         }
      }
   }
   return length;
} /* Endbody */

/* EOF */

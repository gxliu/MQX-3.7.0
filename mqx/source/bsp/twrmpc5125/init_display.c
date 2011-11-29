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
* $FileName: init_display.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the source functions for functions required to
*   specifically initialize the display.
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>


/*----------------------------------------------------------------------------------------------------*/
#pragma mark    -
#pragma mark    I2C Functions - to be replaced with I2C Driver
#pragma mark    -
/*----------------------------------------------------------------------------------------------------*/



static int i2c_transmit(MPC5125_I2C_MODULE_STRUCT_PTR i2cm_ptr, uchar data, boolean ack)
{
   int timeout=5000; 
   uint_32  csr;
    
   // Start I2C Module
   i2cm_ptr->MCR |= I2C_MCR_EN_MASK | I2C_MCR_STA_MASK | I2C_MCR_TX_MASK;

   // writing data into the data register initiates a data transfer
   i2cm_ptr->MDR = data<<24;

   // After transmission the I2C module waits till it recieves an acknowledgement 
   // from the slave before it can transmit next data byte.
   // RXAK Receive Acknowledge. 
   // If bit is low,it indicates an acknowledge signal was received after completion of 
   // 8 bits of data transmission on the bus.
   // If bit is high,it means no acknowledge signal is detected at the 9th clock pulse 
   // on the data line.
   while(!(i2cm_ptr->MSR & I2C_MSR_IF_MASK) && (--timeout))  {};

   csr = i2cm_ptr->MSR;
   //Clear the interrupt status
   i2cm_ptr->MSR |= I2C_MSR_IF_MASK;
   _PSP_SYNC();
     
   if (ack) {
      if (csr & I2C_MSR_RXAK_MASK) {
         while (( i2cm_ptr->MSR & I2C_MSR_RXAK_MASK ) && (--timeout)) {}
      }
   }
  
   _time_delay(1);
  
  if(timeout==0)
  {
      //printf(" i2c_transmit: No Ack received for data byte 0x%x sent\n", data);
      return IO_ERROR;
  }
  else
  {
    return MQX_OK;
  }
}

static int i2c_receive(MPC5125_I2C_MODULE_STRUCT_PTR i2cm_ptr, uchar_ptr data_ptr, uint_32 bytes)
{
   int timeout=5000,i; 
   uint_32  data;
    
    // Start I2C Module
    for  (i=(int)bytes;i>0;i--) {
      while(!(i2cm_ptr->MSR & I2C_MSR_IF_MASK) && (--timeout))  {};
     
        if (i==2) 
           i2cm_ptr->MCR |= I2C_MCR_TXAK_MASK;

        if (i==1) 
           i2cm_ptr->MCR &= ~I2C_MCR_STA_MASK;

      data = i2cm_ptr->MDR;
    *data_ptr++ = (data>>24);
    
      //Clear the interrupt status
      i2cm_ptr->MSR |= I2C_MSR_IF_MASK;

      if(timeout==0)
      {
         return IO_ERROR;
      }
   }
   return MQX_OK;
}


static void i2c_init(MPC5125_I2C_MODULE_STRUCT_PTR i2cm_ptr, uint_32 self_address,uint_32 fdr_value)
{
   MPC5125_I2C_STRUCT_PTR  i2c_ptr = MPC5125_I2C_ADDR();

    //disable the I2C module
    i2cm_ptr->MCR = 0x00000000;

    //put the address here when this module is addressed as slave
    i2cm_ptr->MADR = self_address;

    //set the frequency register to the desired frequency
    i2cm_ptr->MFDR = fdr_value;

    //enable the I2C module
    i2cm_ptr->MCR |= I2C_MCR_EN_MASK;
    
    // Reset all the bits in the status register.
    // This is done to make sure that all the status bits show information about the present module.
    i2cm_ptr->MSR = 0;
    
    i2c_ptr->ICR = 0;
    i2c_ptr->MIFR = 0;
    
}


static int i2c_write_byte(MPC5125_I2C_MODULE_STRUCT_PTR i2cm_ptr,uchar i2c_addr, uchar addr, uchar data)
{
   uint_32 result=0,timeout = 500;
   
   while (timeout-- && (i2cm_ptr->MSR & I2C_MSR_BB_MASK)) { 
      _time_delay(1);
   }
   
   if (timeout!=0) {
    i2cm_ptr->MCR |= I2C_MCR_EN_MASK | I2C_MCR_STA_MASK | I2C_MCR_TX_MASK;


      
      i2c_addr = (i2c_addr<<1);
    // Transmitting slave address
    if (i2c_transmit(i2cm_ptr, i2c_addr, TRUE )==MQX_OK) {
        // Transmitting write address location in slave
        if (i2c_transmit(i2cm_ptr, addr, TRUE )==MQX_OK) {
            // Transmitting Data
            if (i2c_transmit(i2cm_ptr, data, FALSE)==MQX_OK) {
               result = 1;
            }
        }
    }
    i2cm_ptr->MCR &= ~(I2C_MCR_STA_MASK|I2C_MCR_TX_MASK);
    _time_delay(1);
   }
    
    //if (!result) puts("Error writing data to I2C.\n");
    return result;
}

static int i2c_read(MPC5125_I2C_MODULE_STRUCT_PTR i2cm_ptr,uchar i2c_addr, uchar addr, uchar_ptr data_ptr, uint_32 count)
{
   uint_32 result=0,timeout = 500;

   while (timeout-- && (i2cm_ptr->MSR & I2C_MSR_BB_MASK)) { 
      _time_delay(1);
   }
   
   if (timeout!=0) {
    i2cm_ptr->MCR |= I2C_MCR_EN_MASK | I2C_MCR_STA_MASK | I2C_MCR_TX_MASK;

      i2c_addr = (i2c_addr<<1) | 1;
    // Transmitting slave address
    if (i2c_transmit(i2cm_ptr, i2c_addr, TRUE)==MQX_OK) {
       _time_delay(1);
        // Transmitting read address location in slave
        if (i2c_transmit(i2cm_ptr, addr, TRUE)==MQX_OK) {
            _time_delay(1);
            i2cm_ptr->MCR &= I2C_MCR_TX_MASK;

            // Receiving Data
            if (i2c_receive(i2cm_ptr, data_ptr, count)==MQX_OK) {
                   result = count;
            }
        }
    }
      i2cm_ptr->MCR &= I2C_MCR_STA_MASK;
      _time_delay(1);
   }
   // if (result != count)  puts("Error reading data from I2C.\n");
   return result;
}


/* Default setting */
uint_32 prioman_setting0[23] = {0x000777aa, // PRIOMAN CONFIG1
                            0x00000055, // PRIOMAN CONFIG2
                            0x00000000, // HIPRIO CONFIG
                            0x11111117, // LUT0 MAIN UP
                            0x444eeeee, // LUT1 MAIN UP
                            0x44444444, // LUT2 MAIN UP
                            0x55555555, // LUT3 MAIN UP
                            0x11111111, // LUT4 MAIN UP
                            0x7777777a, // LUT0 MAIN LOW
                            0xeeeeeeee, // LUT1 MAIN LOW
                            0x44444444, // LUT2 MAIN LOW
                            0x55555558, // LUT3 MAIN LOW
                            0x1111117c, // LUT4 MAIN LOW
                            0x33333377, // LUT0 ALTE UP
                            0x11111111, // LUT1 ALTE UP
                            0x11111111, // LUT2 ALTE UP
                            0x11111111, // LUT3 ALTE UP
                            0x11111111, // LUT4 ALTE UP
                            0x7777eeee, // LUT0 ALTE LOW
                            0x11111111, // LUT1 ALTE LOW
                            0x11111111, // LUT2 ALTE LOW
                            0x11111111, // LUT3 ALTE LOW
                            0x11111111};// LUT4 ALTE LOW

_mqx_int _bsp_hdmi_io_init( void )
{
   return _bsp_i2c_io_init(0);
}

int _bsp_diu_init(void)
{
   MPC5125_I2C_MODULE_STRUCT_PTR i2cm_ptr =  MPC5125_I2C_MODULE_ADDR(0);
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   // uint_32  fdr;
    

   _mpc5125_prioman_config(prioman_setting0);
   _bsp_diu_io_init();
   _bsp_hdmi_io_init();

   _mpc5125_enable_i2c_clock();

   //fdr = mpc5125_i2c_calculate_fdr(100000);
   //i2c_init(i2cm_ptr, 0xB4000000,fdr<<24);
   i2c_init(i2cm_ptr, 0xB4000000,0x5a000000);

   #ifdef BSP_TWRMPC5125   
   #ifdef BSP_HDMI_SIL9034
    i2c_write_byte(i2cm_ptr, 0x39, 0x08, 0x36);
    i2c_write_byte(i2cm_ptr, 0x39, 0x0c, 0x3);
      i2c_write_byte(i2cm_ptr, 0x39, 0x0f, 0x4);
    i2c_write_byte(i2cm_ptr, 0x39, 0x33, 0x30);
    i2c_write_byte(i2cm_ptr, 0x39, 0x34, 0x0);
    i2c_write_byte(i2cm_ptr, 0x39, 0x08, 0x37);
   #endif
   #ifdef BSP_HDMI_SIL9022
      i2c_write_byte(i2cm_ptr, 0x39, 0xc7, 0x00);
      i2c_write_byte(i2cm_ptr, 0x39, 0x1a, 0x10);
      i2c_write_byte(i2cm_ptr, 0x39, 0x1e, 0x00);
      i2c_write_byte(i2cm_ptr, 0x39, 0x1a, 0x00);  
   #endif
   #endif

   #ifdef BSP_MPC5125ADS   
    i2c_write_byte(i2cm_ptr, 0x38, 0x08, 0xBF);
    i2c_write_byte(i2cm_ptr, 0x38, 0x0A, 0x10);
   #endif   
}


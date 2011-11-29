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
* $FileName: i2c.c$
* $Version : 3.7.19.0$
* $Date    : Feb-22-2011$
*
* Comments:
*
*   This file contains the source for a simple example of an
*   an application that writes and reads the Microchip 24LC16 EEPROMs
*   using I2C driver.
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include <i2c.h>
#include "eeprom.h"


#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


#if ! BSPCFG_ENABLE_I2C0
#error This application requires BSPCFG_ENABLE_I2C0 defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#define RECV_BUFFER_SIZE 256


#define TEST_STRING "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"


extern void main_task(uint_32);


const TASK_TEMPLATE_STRUCT MQX_template_list[] = 
{
  /* Task Index,   Function,  Stack,  Priority, Name,   Attributes,          Param, Time Slice */
   { 10,           main_task, 2000L,    8L,     "Main", MQX_AUTO_START_TASK, 0,     0 },
   { 0 }
};

      
/*TASK*-------------------------------------------------------------------
* 
* Task Name : main_task
* Comments  :
*
*END*----------------------------------------------------------------------*/

void main_task
   (
      uint_32 dummy
   )
{
   MQX_FILE_PTR                 fd;
   uint_32                      param, result;
   I2C_STATISTICS_STRUCT        stats;
   uchar_ptr                    recv_buffer;

   /* Allocate receive buffer */
   recv_buffer = _mem_alloc_zero (RECV_BUFFER_SIZE);
   if (recv_buffer == NULL) 
   {
      printf ("ERROR getting receive buffer!\n");
      _task_block ();
   }

   printf ("\n\n-------------- Polled I2C EEPROM example --------------\n\n");

   /* Open the I2C driver */         
   fd = fopen ("i2c0:", NULL);
   if (fd == NULL) 
   {
      printf ("ERROR opening the I2C driver!\n");
      _time_delay (200L);
      _mqx_exit (1L);
   }

   /* Test ioctl commands */
   param = 100000;
   printf ("Set current baud rate to %d ... ", param);
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_SET_BAUD, &param))
   {
      printf ("OK\n");
   } else {
      printf ("ERROR\n");
   }

   printf ("Get current baud rate ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_BAUD, &param))
   {
      printf ("%d\n", param);
   } else {
      printf ("ERROR\n");
   }

   printf ("Set master mode ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_SET_MASTER_MODE, NULL))
   {
      printf ("OK\n");
   } else {
      printf ("ERROR\n");
   }

   printf ("Get current mode ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_MODE, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }
   
   param = 0x60;
   printf ("Set station address to 0x%02x ... ", param);
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_SET_STATION_ADDRESS, &param))
   {
      printf ("OK\n");
   } else {
      printf ("ERROR\n");
   }
   
   param = 0x00;
   printf ("Get station address ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATION_ADDRESS, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }

   printf ("Clear statistics ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_CLEAR_STATISTICS, NULL))
   {
      printf ("OK\n");
   } else {
      printf ("ERROR\n");
   }
   
   printf ("Get statistics ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATISTICS, (pointer)&stats))
   {
      printf ("\n  Interrupts:  %d\n", stats.INTERRUPTS);
      printf ("  Rx packets:  %d\n", stats.RX_PACKETS);
      printf ("  Tx packets:  %d\n", stats.TX_PACKETS);
      printf ("  Tx lost arb: %d\n", stats.TX_LOST_ARBITRATIONS);
      printf ("  Tx as slave: %d\n", stats.TX_ADDRESSED_AS_SLAVE);
      printf ("  Tx naks:     %d\n", stats.TX_NAKS);
   } else {
      printf ("ERROR\n");
   }

   printf ("Get current state ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATE, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }
   
   param = I2C_EEPROM_ADDRESS;
   printf ("Set destination address to 0x%02x ... ", param);
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &param))
   {
      printf ("OK\n");
   } else {
      printf ("ERROR\n");
   }
   
   param = 0x00;
   printf ("Get destination address ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_DESTINATION_ADDRESS, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }
   /* Test request 1 byte, read 1 byte */
   printf ("Test request 1 byte, read 1 byte ... ");
   param = 1;
   if (I2C_OK != ioctl (fd, IO_IOCTL_I2C_SET_RX_REQUEST, &param))
   {
      printf ("\n  ERROR during set rx request\n");
   }
   result = fread (&param, 1, 1, fd);
   if (I2C_OK != ioctl (fd, IO_IOCTL_FLUSH_OUTPUT, &param))
   {
      printf ("\n  ERROR during flush\n");
   }
   if (I2C_OK != ioctl (fd, IO_IOCTL_I2C_STOP, NULL))
   {
      printf ("\n  ERROR during stop\n");
   }
   printf ("done\n");

   /* Test EEPROM communication */
   i2c_write_eeprom_polled (fd, I2C_EEPROM_ADDRESS_1, (uchar_ptr)TEST_STRING, 0);
   i2c_read_eeprom_polled (fd, I2C_EEPROM_ADDRESS_1, recv_buffer, 0);

   i2c_write_eeprom_polled (fd, I2C_EEPROM_ADDRESS_1, (uchar_ptr)TEST_STRING, 1);
   i2c_read_eeprom_polled (fd, I2C_EEPROM_ADDRESS_1, recv_buffer, 1);
   printf ("Received: %c\n", recv_buffer[0]);
   
   i2c_write_eeprom_polled (fd, I2C_EEPROM_ADDRESS_2, (uchar_ptr)TEST_STRING, sizeof(TEST_STRING));
   i2c_read_eeprom_polled (fd, I2C_EEPROM_ADDRESS_2 - 10, recv_buffer, sizeof(TEST_STRING) + 11);
   printf ("Received: ");
   for (result = 0; result < sizeof(TEST_STRING) + 11; result++)
   {
      printf ("%c", recv_buffer[result]);
   }
   printf ("\n");
   
   printf ("Get statistics ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATISTICS, (pointer)&stats))
   {
      printf ("\n  Interrupts:  %d\n", stats.INTERRUPTS);
      printf ("  Rx packets:  %d\n", stats.RX_PACKETS);
      printf ("  Tx packets:  %d\n", stats.TX_PACKETS);
      printf ("  Tx lost arb: %d\n", stats.TX_LOST_ARBITRATIONS);
      printf ("  Tx as slave: %d\n", stats.TX_ADDRESSED_AS_SLAVE);
      printf ("  Tx naks:     %d\n", stats.TX_NAKS);
   } else {
      printf ("ERROR\n");
   }

   printf ("Get current state ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATE, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }

   /* Close the driver */
   result = fclose (fd);
   if (result) 
   {
      printf ("ERROR during close, returned: %d\n", result);
   }



#if BSPCFG_ENABLE_II2C0

   printf ("\n\n-------------- Interrupt I2C EEPROM example --------------\n\n");
  
   /* Open the I2C driver */         
   fd = fopen ("ii2c0:", NULL);
   if (fd == NULL) 
   {
      printf ("Failed to open the I2C driver!\n");
      _time_delay (200L);
      _mqx_exit (1L);
   }

   /* Test ioctl commands */
   printf ("Get current baud rate ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_BAUD, &param))
   {
      printf ("%d\n", param);
   } else {
      printf ("ERROR\n");
   }

   printf ("Set master mode ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_SET_MASTER_MODE, NULL))
   {
      printf ("OK\n");
   } else {
      printf ("ERROR\n");
   }
   
   printf ("Get current mode ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_MODE, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }
   
   param = 0x60;
   printf ("Set station address to 0x%02x ... ", param);
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_SET_STATION_ADDRESS, &param))
   {
      printf ("OK\n");
   } else {
      printf ("ERROR\n");
   }
   
   param = 0x00;
   printf ("Get station address ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATION_ADDRESS, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }

   printf ("Clear statistics ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_CLEAR_STATISTICS, NULL))
   {
      printf ("OK\n");
   } else {
      printf ("ERROR\n");
   }
   
   printf ("Get statistics ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATISTICS, (pointer)&stats))
   {
      printf ("\n  Interrupts:  %d\n", stats.INTERRUPTS);
      printf ("  Rx packets:  %d\n", stats.RX_PACKETS);
      printf ("  Tx packets:  %d\n", stats.TX_PACKETS);
      printf ("  Tx lost arb: %d\n", stats.TX_LOST_ARBITRATIONS);
      printf ("  Tx as slave: %d\n", stats.TX_ADDRESSED_AS_SLAVE);
      printf ("  Tx naks:     %d\n", stats.TX_NAKS);
   } else {
      printf ("ERROR\n");
   }

   printf ("Get current state ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATE, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }
   
   param = I2C_EEPROM_ADDRESS;
   printf ("Set destination address to 0x%02x ... ", param);
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &param))
   {
      printf ("OK\n");
   } else {
      printf ("ERROR\n");
   }
   
   param = 0x00;
   printf ("Get destination address ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_DESTINATION_ADDRESS, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }
   /* Test request 1 byte, read 1 byte */
   printf ("Test request 1 byte, read 1 byte ... ");
   param = 1;
   if (I2C_OK != ioctl (fd, IO_IOCTL_I2C_SET_RX_REQUEST, &param))
   {
      printf ("\n  ERROR during set rx request\n");
   }
   do 
   {
      result = fread (&param, 1, 1, fd);
      if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATE, &param))
      {
         if (I2C_STATE_RECEIVE != param) break;
      }
   } while (result < 1);
   if (I2C_OK != ioctl (fd, IO_IOCTL_FLUSH_OUTPUT, &param))
   {
      printf ("\n  ERROR during flush\n");
   }
   if (I2C_OK != ioctl (fd, IO_IOCTL_I2C_STOP, NULL))
   {
      printf ("\n  ERROR during stop\n");
   }
   printf ("done\n");

   /* Test EEPROM communication */
   i2c_write_eeprom_interrupt (fd, I2C_EEPROM_ADDRESS_1, (uchar_ptr)TEST_STRING, 0);
   i2c_read_eeprom_interrupt (fd, I2C_EEPROM_ADDRESS_1, recv_buffer, 0);

   i2c_write_eeprom_interrupt (fd, I2C_EEPROM_ADDRESS_1, (uchar_ptr)TEST_STRING, 1);
   i2c_read_eeprom_interrupt (fd, I2C_EEPROM_ADDRESS_1, recv_buffer, 1);
   printf ("Received: %c\n", recv_buffer[0]);
   
   i2c_write_eeprom_interrupt (fd, I2C_EEPROM_ADDRESS_2, (uchar_ptr)TEST_STRING, sizeof(TEST_STRING));
   i2c_read_eeprom_interrupt (fd, I2C_EEPROM_ADDRESS_2 - 10, recv_buffer, sizeof(TEST_STRING) + 11);
   printf ("Received: ");
   for (result = 0; result < sizeof(TEST_STRING) + 11; result++)
   {
      printf ("%c", recv_buffer[result]);
   }
   printf ("\n");
   
   printf ("Get statistics ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATISTICS, (pointer)&stats))
   {
      printf ("\n  Interrupts:  %d\n", stats.INTERRUPTS);
      printf ("  Rx packets:  %d\n", stats.RX_PACKETS);
      printf ("  Tx packets:  %d\n", stats.TX_PACKETS);
      printf ("  Tx lost arb: %d\n", stats.TX_LOST_ARBITRATIONS);
      printf ("  Tx as slave: %d\n", stats.TX_ADDRESSED_AS_SLAVE);
      printf ("  Tx naks:     %d\n", stats.TX_NAKS);
   } else {
      printf ("ERROR\n");
   }

   printf ("Get current state ... ");
   if (I2C_OK == ioctl (fd, IO_IOCTL_I2C_GET_STATE, &param))
   {
      printf ("0x%02x\n", param);
   } else {
      printf ("ERROR\n");
   }

   /* Close the driver */
   result = fclose (fd);
   if (result) 
   {
      printf ("ERROR during close, returned: %d\n", result);
   }

#endif



   /* Free buffer */
   _mem_free (recv_buffer);
      
   _mqx_exit (0);
 
} /* Endbody */

/* EOF */

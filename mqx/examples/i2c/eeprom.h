#ifndef __eeprom_h__
#define __eeprom_h__
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
* $FileName: eeprom.h$
* $Version : 3.6.3.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*   This file contains definitions for the I2C EEPROM example.
*
*END************************************************************************/

#if defined(BSP_M53015EVB)
#define I2C_EEPROM_ADDRESS_1 0x00FA
#define I2C_EEPROM_ADDRESS_2 0x00C0
#define I2C_EEPROM_ADDRESS   0x50     /* I2C bus address of EEPROM */
#define I2C_EEPROM_PAGE_SIZE 0x08     /* maximum bytes per write */
#else
/* The I2C EEPROM test addresses */

#define I2C_EEPROM_ADDRESS_1 0x00FA
#define I2C_EEPROM_ADDRESS_2 0x01FA

/* The 24LC16 I2C EEPROM parameters */

#define I2C_EEPROM_ADDRESS   0x50     /* I2C bus address of EEPROM */
#define I2C_EEPROM_PAGE_SIZE 0x10     /* maximum bytes per write */

#endif
/* Funtion prototypes */

extern void i2c_write_eeprom_polled (MQX_FILE_PTR, uint_32, uchar_ptr, uint_32);
extern void i2c_read_eeprom_polled (MQX_FILE_PTR, uint_32, uchar_ptr, uint_32);
extern void i2c_write_eeprom_interrupt (MQX_FILE_PTR, uint_32, uchar_ptr, uint_32);
extern void i2c_read_eeprom_interrupt (MQX_FILE_PTR, uint_32, uchar_ptr, uint_32);

#endif
/* EOF */

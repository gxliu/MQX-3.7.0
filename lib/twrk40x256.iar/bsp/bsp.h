/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
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
* $FileName: bsp.h$
* $Version : 3.7.13.0$
* $Date    : Mar-16-2011$
*
* Comments:
*
*   This file includes all include files specific to this target system.
*
*END************************************************************************/

#ifndef _bsp_h_
#define _bsp_h_ 1

#include <bsp_rev.h>
#include <psp.h>
#include <PE_LDD.h>
#include <twrk40x256.h>
#include <fio.h>
#include <io.h>
#include <serial.h>
#include <serl_kuart.h>
#include <spi.h>
#include <spi_dspi.h>
#include <i2c.h>
#include <i2c_ki2c.h>
#include <io_mem.h>
#include <io_null.h>
#include <lwgpio_kgpio.h>
#include <lwgpio.h>
#include <io_gpio.h>
#include <esdhc.h>
#include <sdcard.h>
#include <sdcard_spi.h>   
#include <sdcard_esdhc.h> 
#include <adc.h>
#include <kinetis_fcan.h>
#include <kflexcan.h>
#include <flashx.h>
#include <flash_kinetis.h>
#include <flash_mk40.h>
#include <lcd_twrk40x256.h>
#include <krtc.h> 
#include <rtc.h>
#include <tchres.h>

extern _mqx_int _bsp_serial_io_init (uint_8);
extern _mqx_int _bsp_adc_io_init(_mqx_uint adc_num);
extern _mqx_int _bsp_adc_channel_io_init(uint_16 source);
extern _mqx_int _bsp_dspi_io_init(uint_32 dev_num);
extern _mqx_int _bsp_flexcan_io_init (uint_8);
extern _mqx_int _bsp_i2c_io_init( uint_32 );
extern _mqx_int _bsp_gpio_io_init( void ); 
extern _mqx_int _bsp_esdhc_io_init (uint_8, uint_16);
extern _mqx_int _bsp_rtc_io_init( void );
extern _mqx_int _bsp_usb_io_init(void);
extern _mqx_int _bsp_serial_rts_init( uint_32 );
extern _mqx_int _bsp_lcd_io_init( void );

extern const SDCARD_INIT_STRUCT _bsp_sdcard0_init;

#define _bsp_int_init(num, prior, subprior, enable)     _cortex_int_init(num, prior, enable)
#define _bsp_int_enable(num)    _cortex_int_enable(num)
#define _bsp_int_disable(num)   _cortex_int_disable(num)

#endif  /* _bsp_h_ */
/* EOF */

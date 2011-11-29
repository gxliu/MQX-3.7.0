/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: bsp.h$
* $Version : 3.7.19.0$
* $Date    : Jan-13-2011$
*
* Comments:
*
*   This file includes all include files specific to this target system.
*   $Header:bsp.h, 5, 3/15/2007 11:18:32 AM, Jim Gard$
*   $NoKeywords$
*
*END************************************************************************/
#ifndef _bsp_h_
#define _bsp_h_ 1

#include <bsp_rev.h>
#include <psp.h>
#include <fio.h>
#include <io.h>
#include <twrmcf54418.h>       /* Target definitions */
#include <timer_mcf5441.h>     /* Timer */
#include <int_ctrl_mcf5441.h>  /* Interrupt controller */
#include <enet.h>              /* Ethernet */
#include <macnet_mcf5441.h>    /* Underlying Ethernet device */
#include <phy_dp83xxx.h>       /* Ethernet Physical Interface */
#include <serial.h>            /* Serial */
#include <serl_mcf54xx.h>      /* Serial */
#include <i2c.h>               /* I2C */
#include <i2c_mcf54xx.h>       /* I2C */
#include <spi.h>               /* SPI */
#include <spi_mcf5xxx_dspi.h>  /* SPI */
#include <apccard.h>           /* CFCARD */
#include <pccardflexbus.h>     /* CFCARD */
#include <pcflash.h>           /* CFCARD */
#include <sdcard.h>            /* SDCARD */
#include <sdcard_spi.h>        /* SDCARD */
#include <io_gpio.h>           /* GPIODEV */
#include <adc.h>               /* ADC */
#include <esdhc.h>             /* ESDHC */
#include <irtc_mcf5xxx.h>      /* Independent Real Time Clock IRTC     */
#include <irtc_mcf5441x.h>     /* IRTC platform specific functions     */


#include <pcb.h>
#include <io_mem.h>
#include <io_null.h>

#include <nandflash.h>          /* external flash */
#include <nfc.h>                /* NAND Flash Controller */

#define _mcf54xx_int_init     _mcf5441_int_init
#define _mcf54xx_int_unmask   _mcf5441_int_unmask
#define _mcf54xx_int_mask     _mcf5441_int_mask
#define _mcf54xx_int_mask_all _mcf5441_int_mask_all

#define _bsp_int_init(irq, level, sublevel, unmask)         _mcf5441_int_init(irq, level, unmask)
#define _bsp_int_enable(num)    _mcf5441_int_unmask(num)
#define _bsp_int_disable(num)   _mcf5441_int_mask(num)

typedef enum usb_interface {
    USB_CONNECTOR_STANDARD = 0,
    USB_CONNECTOR_ULPI
} usb_interface_t;

typedef enum usb_mode {
    USB_MODE_DEVICE = 0,
    USB_MODE_HOST,
    USB_MODE_OTG
} usb_mode_t;

_mqx_int _bsp_serial_io_init(uint_8);
void     _bsp_rtc_io_init (void);
 void    _bsp_flexbus_io_init (void);
_mqx_int _bsp_i2c_io_init (uint_8);
_mqx_int _bsp_dspi_io_init (uint_8);
void     _bsp_usb_io_init (usb_interface_t, usb_mode_t);
_mqx_int _bsp_flexcan_io_init (uint_8);
_mqx_int _bsp_adc_io_init(_mqx_uint);
_mqx_int _bsp_adc_enable_clock( void );
_mqx_int _bsp_esdhc_io_init (uint_8, uint_16);
void     _bsp_enet_io_init(_mqx_uint);
boolean  _bsp_get_mac_address(uint_32,uint_32,_enet_address);
_mqx_int _bsp_dtimer_gpio_init(uint_8 dev_num);

extern const SDCARD_INIT_STRUCT _bsp_sdcard0_init;

#endif
/* EOF */

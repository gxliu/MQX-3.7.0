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
* $Version : 3.7.5.0$
* $Date    : Feb-3-2011$
*
* Comments:
*
*   This file includes all include files specific to this target system.
*   $Header:bsp.h, 5, 3/15/2007 11:18:32 AM, Jim Gard$
*   $NoKeywords$
*
*END************************************************************************/
#ifndef _bsp_h_
#define _bsp_h_

#include <bsp_rev.h>
#include <psp.h>
#include <fio.h>
#include <io.h>
#include <m53015evb.h>         /* Target definitions */
#include <timer_mcf5301.h>     /* Timer */
#include <int_ctrl_mcf5301.h>  /* Interrupt controller */
#include <serial.h>            /* Serial */
#include <serl_mcf53xx.h>      /* Serial */
#include <enet.h>              /* Ethernet */
#include <mcf5301_fec.h>       /* Underlying Ethernet device */
#include <phy_dp83xxx.h>       /* Ethernet Physical Interface */
#include <i2c.h>               /* I2C  */
#include <i2c_mcf53xx.h>       /* I2C  */
#include <io_gpio.h>		       /* GPIO */
#include <spi.h>               /* SPI  */
#include <spi_mcf5xxx_dspi.h>  /* SPI  */
#include <pcb.h>
#include <io_mem.h>
#include <io_null.h>

#include <flashx.h>            /* external flash */
#include <sdcard.h>
#include <esdhc.h>             /* ESDHC  */
#include <29wsxxxN.h>
#include <rtc_mcf53xx.h>
#include <rtc.h>

#define _mcf53xx_int_init     _mcf5301_int_init
#define _bsp_int_init(irq, level, sublevel, unmask)         _mcf5301_int_init(irq, level, unmask)
#define _mcf53xx_int_unmask   _mcf5301_int_unmask
#define _mcf53xx_int_mask     _mcf5301_int_mask
#define _mcf53xx_int_mask_all _mcf5301_int_mask_all

_mqx_int _bsp_serial_io_init(uint_8);

typedef enum usb_interface {
 
    USB_CONNECTOR_OTG   =0,
    USB_CONNECTOR_STANDARD
    
} usb_interface_t;

void _bsp_rtc_io_init (void);
_mqx_int _bsp_i2c_io_init (uint_8);
_mqx_int _bsp_dspi_io_init (uint_8);
void _bsp_usb_io_init (usb_interface_t);
void _bsp_enet_io_init(_mqx_uint);
extern _mqx_int _bsp_esdhc_io_init (uint_8, uint_16);
boolean  _bsp_get_mac_address(uint_32,uint_32,_enet_address);
extern const SDCARD_INIT_STRUCT _bsp_sdcard0_init;
#endif
/* EOF */

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
* $FileName: bsp.h$
* $Version : 3.7.28.0$
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
#include <fio.h>
#include <io.h>
#include <m52259demo.h>           // Target definitions
#include <timer_mcf5225.h>        // Timer
#include <int_ctrl_mcf5225.h>     // Interrupt controller
#include <enet.h>              // Generic Ethernet Driver Interface
#include <mcf5225_fec.h>       // Underlying Ethernet device
#include <phy_ksz8041.h>       // Ethernet Physical Interface

#include <serial.h>               // Serial
#include <serl_mcf52xx.h>         // Serial
#include <pcb.h>
#include <io_mem.h>
#include <io_null.h>
#include <io_gpio.h>
#include <lwgpio_mcf5225.h>
#include <lwgpio.h>

#include <i2c.h>
#include <i2c_mcf52xx.h>
#include <spi.h>
#include <spi_mcf5xxx_qspi.h>
#include <adc.h>
#include <flashx.h>               // internal flash
#include <flash_mcf5225.h>
#include <rtc_mcf52xx.h> 
#include <rtc.h>

#define _mcf52xx_int_init     _mcf5225_int_init
#define _bsp_int_init         _mcf52xx_int_init
#define _mcf52xx_int_unmask   _mcf5225_int_unmask
#define _mcf52xx_int_mask     _mcf5225_int_mask
#define _mcf52xx_int_mask_all _mcf5225_int_mask_all

extern _mqx_int _bsp_serial_io_init (uint_8);
extern void     _bsp_usb_io_init (void);
extern void     _bsp_rtc_io_init (void);
extern _mqx_int _bsp_flexcan_io_init (uint_8);
extern _mqx_int _bsp_i2c_io_init (uint_8);
extern _mqx_int _bsp_qspi_io_init (uint_8);
extern _mqx_int _bsp_adc_io_init(_mqx_uint);
extern void     _bsp_enet_io_init(_mqx_uint);
extern boolean  _bsp_get_mac_address(uint_32,uint_32,_enet_address);
   
extern const ENET_IF_STRUCT ENET_0;

#endif
/* EOF */

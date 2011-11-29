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
* $Version : 3.7.3.0$
* $Date    : Feb-7-2011$
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
#include <m5208evb.h>         /* Target definitions */
#include <timer_mcf520.h>     /* Timer */
#include <int_ctrl_mcf520.h>  /* Interrupt controller */

#include <enet.h>              /* Generic Ethernet Driver Interface */
#include <mcf520_fec.h>       /* Underlying Ethernet device */
#include <phy_dp83xxx.h>       /* Ethernet Physical Interface */

#include <spi.h>               /* SPI */
#include <spi_mcf5xxx_qspi.h>  /* SPI */
#include <pcb.h>
#include <io_mem.h>
#include <io_null.h>
#include <mcf52xx_uart.h>
#include <serial.h>
#include <serl_mcf52xx.h>      /* Serial */
#include <i2c.h>
#include <i2c_mcf52xx.h>
#include <io_gpio.h>           /* gpio  */

#include <flashx.h>            /* external flash driver */
#include <29wsxxxN.h>          /* spansion flash */

#define _mcf52xx_int_init(irq,level,sublevel,unmask)     _mcf5208_int_init(irq,level,unmask)
#define _bsp_int_init(irq,level,sublevel,unmask)         _mcf52xx_int_init(irq,level,sublevel,unmask)
#define _mcf52xx_int_unmask   _mcf5208_int_unmask
#define _mcf52xx_int_mask     _mcf5208_int_mask
#define _mcf52xx_int_mask_all _mcf5208_int_mask_all

extern _mqx_int _bsp_serial_io_init (uint_8);
extern _mqx_int _bsp_i2c_io_init (uint_8);
extern _mqx_int _bsp_qspi_io_init (uint_8);
extern void     _bsp_enet_io_init(_mqx_uint);
extern boolean  _bsp_get_mac_address(uint_32,uint_32,_enet_address);

#endif
/* EOF */

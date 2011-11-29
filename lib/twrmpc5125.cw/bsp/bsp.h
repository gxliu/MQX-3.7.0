/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved                       
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
* All Rights Reserved

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
* $Version : 3.7.7.0$
* $Date    : Feb-14-2011$
*
* Comments:
*
*   This file includes all include files specific to this target system.
*
*END************************************************************************/

#ifndef __bsp_h__
    #define __bsp_h__ 1

#include <bsp_rev.h>
#include <psp.h>              /* Processor specific files */
#include <mpc5125.h>
#include <fio.h>              /* I/O System */
#include <io.h>
#include <io_mem.h>           /* Memory Driver (generic) */
#include <io_null.h>          /* Null Driver (generic) */
#include <serial.h>           /* Serial Driver (generic) */

#include <irtc_mpc512x.h>     /* RTC Driver */
#include <rtc.h>               

#include <int_ctrl_mpc5125.h> /* Interrupt controller */

#include <timer_mpc512x.h>    /* Timers */
#include <timer_e300dec.h>    /* Timers */

#include <serl_mpc5125.h>     /* Serial ports */

#include <enet.h>             /* Ethernet (generic) */
#include <mpc5125_fec.h>      /* Ethernet FEC device driver */
#include <phy_lan8710.h>      /* Ethernet PHY device driver */
#include <phy_ksz8041.h>      /* Ethernet PHY device driver */

#include <display.h>          /* Display driver (generic) */
#include <diu.h>              /* Display device driver */

#include <mscan.h>            /* Display driver (generic) */
#include <mscan_mpc5125.h>    /* Display device driver */
#include <i2c.h>
#include <i2c_mpc512x.h>      /* I2C  */
#include <twrmpc5125.h>

/* CF Card Driver */
#include <apccard_mpc5125.h>     
#include <pccardlpc_mpc5125.h>
#include <pcflash_mpc5125.h>

#include <nandflash.h>        /* external flash */
#include <nfc.h>              /* NAND Flash Controller */
#include <spi_mpc512x.h>
#include <spi.h>

/* SDHC Module */
#include <sdcard.h>
#include <sdhc.h>   

typedef enum usb_interface {
 
    USB_CONNECT_ULPI1   =0,   /* Use ULPI1*/
    USB_CONNECT_ULPI2         /* Use ULPI2*/
    
} usb_interface_t;

extern const SDCARD_INIT_STRUCT _bsp_sdcard0_init;
extern void bootstrap_ddr_to_nand(void);

#endif /* __bsp_h__ */

/* EOF */

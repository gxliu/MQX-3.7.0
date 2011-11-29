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
* $Version : 3.7.3.0$
* $Date    : Feb-22-2011$
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
#include <twrmcf51ag.h>           /* Target definitions   */
#include <timer_mcf51ag.h>        /* Timer        */
#include <int_ctrl_mcf51ag.h>     /* Interrupt controller   */
#include <serial.h>               /* Serial              */
#include <serl_mcf51xx.h>         /* Serial               */
#include <i2c.h>                  /* I2C                   */
#include <i2c_mcf51xx.h>          /* I2C                   */
#include <rtc_mcf51xx.h>          /* RTC                   */
#include <rtc.h>                  /* Real Time Clock      */
#include <spi.h>                  /* SPI                   */
#include <spi_mcf5xxx_spi16.h>    /* SPI                  */
#include <flashx.h>               /* internal flash         */
#include <flash_mcf51ag.h>        /* internal flash               */
#include <adc.h> 

#include <io_mem.h>
#include <io_null.h>
#include <io_gpio.h>


#define _mcf51xx_int_mask_all _mcf51AG_int_mask_all

extern _mqx_int _bsp_serial_io_init (uint_8);

extern _mqx_int _bsp_rtc_io_init (void);
extern _mqx_int _bsp_i2c_io_init (uint_8);
extern _mqx_int _bsp_adc_io_init(_mqx_uint);
extern _mqx_int _bsp_spi_io_init (uint_8);


#endif

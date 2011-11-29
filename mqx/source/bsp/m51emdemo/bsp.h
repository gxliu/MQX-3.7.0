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
* $Version : 3.7.9.0$
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
#include <m51emdemo.h>          /* Target definitions                   */
#include <timer_mcf51em.h>      /* Timer                                */
#include <int_ctrl_mcf51em.h>   /* Interrupt controller                 */
#include <serial.h>             /* Serial                               */
#include <serl_mcf51xx.h>       /* Serial                               */
#include <i2c.h>                /* I2C                                  */
#include <i2c_mcf51xx.h>        /* I2C                                  */
#include <irtc_mcf5xxx.h>       /* Independent Real Time Clock IRTC     */
#include <irtc_mcf51em.h>       /* IRTC platform specific functions     */
#include <lcd_m51emdemo.h>      /* GD3980P LCD driver                   */
#include <spi.h>                /* SPI                                  */
#include <spi_mcf5xxx_spi8.h>   /* SPI                                  */
#include <spi_mcf5xxx_spi16.h>  /* SPI16                                */
#include <flashx.h>             /* internal flash                       */
#include <flash_mcf51em.h>      /* internal flash                       */
#include <io_mem.h>
#include <io_null.h>
#include <io_gpio.h>
#include <adc.h>


#define _mcf51xx_int_mask_all       _mcf51EM_int_mask_all

#define MCF5XXX_IRTC_STRUCT         MCF51EM_RTC_STRUCT
#define MCF5XXX_IRTC_STRUCT_PTR     MCF51EM_RTC_STRUCT_PTR
#define VMCF5XXX_IRTC_STRUCT_PTR    VMCF51EM_RTC_STRUCT_PTR

/* V1 platform can not work with irq level or sublevel, we can only unmask all interrupts */
#define _bsp_int_init(irq, level, sublevel, unmask) _mcf51EM_int_unmask_all( void )

extern _mqx_int _bsp_serial_io_init (uint_8);
extern void     _bsp_rtc_io_init    (void);
extern _mqx_int _bsp_lcd_io_init    (void);
extern _mqx_int _bsp_i2c_io_init    (uint_8);
extern _mqx_int _bsp_spi_io_init    (uint_8);
extern _mqx_int _bsp_adc_io_init    (_mqx_uint);


#endif

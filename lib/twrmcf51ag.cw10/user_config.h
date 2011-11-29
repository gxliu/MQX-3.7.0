/*
**
**  !!! GENERATED FILE !!! DO NOT CHANGE !!!
**
*/

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
* $FileName: user_config.h$
* $Version : 3.7.3.0$
* $Date    : Feb-24-2011$
*
* Comments:
*
*   User configuration for MQX components
*
*END************************************************************************/

#ifndef __user_config_h__
#define __user_config_h__

/* mandatory CPU identification */
#define MQX_CPU                     PSP_CPU_MCF51AG128   

/* Determine which clock source is used. Only one xtal must be selected */

#define BSPCFG_USE_INTCLK           0   /*             internal oscillator       */
#define BSPCFG_USE_Y1CLK            1   /* 32.768 kHz  low-frequency crystal  Y1 */

/*
** BSP settings
*/

#define BSPCFG_ENABLE_RTCDEV        1
#define BSPCFG_ENABLE_TTYA          1
#define BSPCFG_ENABLE_TTYB          0
#define BSPCFG_ENABLE_ITTYA         0
#define BSPCFG_ENABLE_ITTYB         0
#define BSPCFG_ENABLE_I2C0          0
#define BSPCFG_ENABLE_I2C1          0
#define BSPCFG_ENABLE_II2C0         0
#define BSPCFG_ENABLE_II2C1         0
#define BSPCFG_ENABLE_GPIODEV       1
#define BSPCFG_ENABLE_ADC           0
#define BSPCFG_ENABLE_SPI0          1
#define BSPCFG_ENABLE_ISPI0         0
#define BSPCFG_ENABLE_SPI1          0
#define BSPCFG_ENABLE_ISPI1         0
#define BSPCFG_ENABLE_FLASHX        0
#define BSPCFG_ENABLE_IO_SUBSYSTEM  1

/*
** board-specific MQX settings
*/

#define MQX_COMPONENT_DESTRUCTION   0
#define MQX_CHECK_ERRORS            0
         
/*
** board-specific Shell settings
*/

#define SHELLCFG_USES_RTCS          0        
 
/*
** include common settings
*/

/* use the rest of defaults from small-RAM-device profile */
#include "small_ram_config.h"

/* and enable verification checks in kernel */
#include "verif_enabled_config.h"

#endif
/* EOF */

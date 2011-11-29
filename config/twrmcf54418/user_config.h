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
* $Version : 3.6.15.0$
* $Date    : Sep-22-2010$
*
* Comments:
*
*   User configuration for MQX components
*
*END************************************************************************/

#ifndef __user_config_h__
#define __user_config_h__

/* mandatory CPU identification */
#define MQX_CPU                 PSP_CPU_MCF54418

/*
** BSP settings - for defaults see mqx\source\bsp\<board_name>\<board_name>.h
*/

/*
** board-specific MQX settings - see for defaults mqx\source\include\mqx_cnfg.h
*/

#define BSPCFG_ENABLE_TTYA          1
#define BSPCFG_ENABLE_TTYB          1
#define BSPCFG_ENABLE_TTYC          1   
#define BSPCFG_ENABLE_TTYD          1
#define BSPCFG_ENABLE_TTYE          1
#define BSPCFG_ENABLE_ITTYA         0
#define BSPCFG_ENABLE_ITTYB         0
#define BSPCFG_ENABLE_ITTYC         0
#define BSPCFG_ENABLE_ITTYD         0
#define BSPCFG_ENABLE_ITTYE         0
#define BSPCFG_ENABLE_SPI0          1
#define BSPCFG_ENABLE_ISPI0         1
#define BSPCFG_ENABLE_SPI1          0
#define BSPCFG_ENABLE_ISPI1         0
#define BSPCFG_ENABLE_I2C0          1
#define BSPCFG_ENABLE_II2C0         0
#define BSPCFG_ENABLE_I2C5          0
#define BSPCFG_ENABLE_II2C5         0
#define BSPCFG_ENABLE_GPIODEV       1
#define BSPCFG_ENABLE_NANDFLASH     1
#define BSPCFG_ENABLE_ADC           0
#define BSPCFG_ENABLE_ESDHC         1
#define BSPCFG_ENABLE_PCFLASH       0
#define BSPCFG_ENABLE_RTCDEV        1

   
/*
** include common settings
*/

/*
** board-specific MFS settings
*/

/*
** board-specific RTCS settings
*/

#define RTCSCFG_ENABLE_LWDNS    1

/* and enable verification checks in kernel */
#include "verif_enabled_config.h"

#endif
/* EOF */

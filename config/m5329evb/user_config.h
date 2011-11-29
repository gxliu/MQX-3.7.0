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
* $Version : 3.7.4.0$
* $Date    : Feb-21-2011$
*
* Comments:
*
*   User configuration for MQX components
*
*END************************************************************************/

#ifndef __user_config_h__
#define __user_config_h__

/* mandatory CPU identification */
#define MQX_CPU                 PSP_CPU_MCF5329

/*
** BSP settings - for defaults see mqx\source\bsp\<board_name>\<board_name>.h
*/
#define BSPCFG_ENABLE_TTYA       1
#define BSPCFG_ENABLE_ITTYA      0
#define BSPCFG_ENABLE_TTYB       0
#define BSPCFG_ENABLE_ITTYB      0
#define BSPCFG_ENABLE_TTYC       0
#define BSPCFG_ENABLE_ITTYC      0
#define BSPCFG_ENABLE_GPIODEV    1
#define BSPCFG_ENABLE_RTCDEV     0
#define BSPCFG_ENABLE_I2C0       0
#define BSPCFG_ENABLE_SPI0       0
#define BSPCFG_ENABLE_EXT_FLASH  0
#define BSPCFG_ENABLE_PCFLASH    0
#define BSPCFG_ENABLE_NANDFLASH  0

/*
** board-specific RTCS settings - see for defaults rtcs\source\include\rtcscfg.h
*/
#define RTCSCFG_ENABLE_DNS       0

/*
** include common settings
*/

/* and enable verification checks in kernel */
#include "verif_enabled_config.h"

#endif
/* EOF */

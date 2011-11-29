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
* $Version : 3.7.7.0$
* $Date    : Mar-23-2011$
*
* Comments:
*
*   User configuration for MQX components
*
*END************************************************************************/

#ifndef __user_config_h__
#define __user_config_h__

/* mandatory CPU identification */
#define MQX_CPU                        PSP_CPU_MPC5125

/* ttyb - on board serial console (PCS0) connected over JM60 (DEFAULT) */
/* ttyj - TWR-SER RS232 serial console (PCS9)                          */          
#define BSP_DEFAULT_IO_CHANNEL             "ttyb:"
#define BSP_DEFAULT_IO_CHANNEL_DEFINED      1

#define BSPCFG_ENABLE_ENET_STATS          1
#define BSPCFG_ENABLE_ENET_MULTICAST      1
#define BSPCFG_ENABLE_CPP                 1
#define BSPCFG_ENABLE_TTYA                0 
#define BSPCFG_ENABLE_ITTYA               0               
#define BSPCFG_ENABLE_TTYB                1
#define BSPCFG_ENABLE_ITTYB               0
#define BSPCFG_ENABLE_TTYC                0
#define BSPCFG_ENABLE_ITTYC               0
#define BSPCFG_ENABLE_TTYD                0
#define BSPCFG_ENABLE_ITTYD               0
#define BSPCFG_ENABLE_TTYE                0
#define BSPCFG_ENABLE_ITTYE               0
#define BSPCFG_ENABLE_TTYF                0
#define BSPCFG_ENABLE_ITTYF               0
#define BSPCFG_ENABLE_TTYG                0
#define BSPCFG_ENABLE_ITTYG               0
#define BSPCFG_ENABLE_TTYH                0
#define BSPCFG_ENABLE_ITTYH               0
#define BSPCFG_ENABLE_TTYI                0
#define BSPCFG_ENABLE_ITTYI               0
#define BSPCFG_ENABLE_TTYJ                1
#define BSPCFG_ENABLE_ITTYJ               0

#define BSPCFG_ENABLE_SPI0                0 
#define BSPCFG_ENABLE_ISPI0               0               
#define BSPCFG_ENABLE_SPI1                0
#define BSPCFG_ENABLE_ISPI1               0
#define BSPCFG_ENABLE_SPI2                1
#define BSPCFG_ENABLE_ISPI2               0
#define BSPCFG_ENABLE_SPI3                0
#define BSPCFG_ENABLE_ISPI3               0
#define BSPCFG_ENABLE_SPI4                0
#define BSPCFG_ENABLE_ISPI4               0
#define BSPCFG_ENABLE_SPI5                0
#define BSPCFG_ENABLE_ISPI5               0
#define BSPCFG_ENABLE_SPI6                0
#define BSPCFG_ENABLE_ISPI6               0
#define BSPCFG_ENABLE_SPI7                0
#define BSPCFG_ENABLE_ISPI7               0
#define BSPCFG_ENABLE_SPI8                0
#define BSPCFG_ENABLE_ISPI8               0
#define BSPCFG_ENABLE_SPI9                0
#define BSPCFG_ENABLE_ISPI9               0

#define BSPCFG_ENABLE_NANDFLASH           1
#define BSPCFG_ENABLE_GPIODEV             0
#define BSPCFG_ENABLE_RTCDEV              1
#define BSPCFG_ENABLE_PCFLASH             0
#define BSPCFG_ENABLE_SDHC                0
#define BSPCFG_ENABLE_I2C0                1
#define BSPCFG_ENABLE_II2C0               0
/*
** board-specific MQX settings - see for defaults mqx\source\include\mqx_cnfg.h
*/

#define MQXCFG_ENABLE_FP                  1
#define MQX_INCLUDE_FLOATING_POINT_IO     1

/*
** board-specific RTCS settings - see for defaults rtcs\source\include\rtcscfg.h
*/

#define RTCSCFG_ENABLE_LWDNS              1 
#define TELNETDCFG_NOWAIT                 FALSE 

/*
** include common settings
*/

/* Use for USB deviece */
#define BSPCFG_USB_DEV_GBOBE              1

/* and enable verification checks in kernel */
#include "verif_enabled_config.h"

#endif
/* EOF */

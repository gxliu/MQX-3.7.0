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
* $FileName: mcf51xx_tod.h$
* $Version : 3.6.1.0$
* $Date    : May-18-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf51xx TOD module.
*
*END************************************************************************/

#ifndef __mcf51xx_tod_h__
#define __mcf51xx_tod_h__

#define __mcf51xx_tod_h__version "$Version:3.6.1.0$"
#define __mcf51xx_tod_h__date    "$Date:May-18-2010$"

#ifdef __cplusplus
extern "C" {
#endif

// RTC status bits

#define MCF51XX_RTC_RTCISR_SW                       (1<<0)
#define MCF51XX_RTC_RTCISR_MIN                      (1<<1)
#define MCF51XX_RTC_RTCISR_ALM                      (1<<2)
#define MCF51XX_RTC_RTCISR_DAY                      (1<<3)
#define MCF51XX_RTC_RTCISR_1HZ                      (1<<4)
#define MCF51XX_RTC_RTCISR_HR                       (1<<5)
#define MCF51XX_RTC_RTCISR_EN                       (1<<31)
#define MCF51XX_RTC_RTCIENR_SW                      (1<<0)
#define MCF51XX_RTC_RTCIENR_MIN                     (1<<1)
#define MCF51XX_RTC_RTCIENR_ALM                     (1<<2)
#define MCF51XX_RTC_RTCIENR_DAY                     (1<<3)
#define MCF51XX_RTC_RTCIENR_1HZ                     (1<<4)
#define MCF51XX_RTC_RTCIENR_HR                      (1<<5)
#define MCF51XX_RTC_STPWCH_CNT(x)                   ((x)&0x1F)

// RTC status bits
#define MCF51XX_RTC_RTCISR_SW                       (1<<0)
#define MCF51XX_RTC_RTCISR_MIN                      (1<<1)
#define MCF51XX_RTC_RTCISR_ALM                      (1<<2)
#define MCF51XX_RTC_RTCISR_DAY                      (1<<3)
#define MCF51XX_RTC_RTCISR_1HZ                      (1<<4)
#define MCF51XX_RTC_RTCISR_HR                       (1<<5)
#define MCF51XX_RTC_RTCISR_EN                       (1<<31)
#define MCF51XX_RTC_RTCIENR_SW                      (1<<0)
#define MCF51XX_RTC_RTCIENR_MIN                     (1<<1)
#define MCF51XX_RTC_RTCIENR_ALM                     (1<<2)
#define MCF51XX_RTC_RTCIENR_DAY                     (1<<3)
#define MCF51XX_RTC_RTCIENR_1HZ                     (1<<4)
#define MCF51XX_RTC_RTCIENR_HR                      (1<<5)
#define MCF51XX_RTC_STPWCH_CNT(x)                   ((x)&0x1F)

#define TODC_TODPS0_MASK                1
#define TODC_TODPS1_MASK                2
#define TODC_TODPS2_MASK                4
#define TODC_TODCLKEN_MASK              8
#define TODC_TODR_MASK                  16
#define TODC_TODCLKS0_MASK              32
#define TODC_TODCLKS1_MASK              64
#define TODC_TODEN_MASK                 128
#define TODC_TODPS_MASK                 7
#define TODC_TODPS_BITNUM               0
#define TODC_TODCLKS_MASK               96
#define TODC_TODCLKS_BITNUM             5

#define TODSC_MTCHWC_MASK               1
#define TODSC_MTCHEN_MASK               2
#define TODSC_MTCHIE_MASK               4
#define TODSC_SECIE_MASK                8
#define TODSC_QSECIE_MASK               16
#define TODSC_MTCHF_MASK                32
#define TODSC_SECF_MASK                 64
#define TODSC_QSECF_MASK                128


#define TODM_MQSEC0_MASK                1
#define TODM_MQSEC1_MASK                2
#define TODM_TODM0_MASK                 4
#define TODM_TODM1_MASK                 8
#define TODM_TODM2_MASK                 16
#define TODM_TODM3_MASK                 32
#define TODM_TODM4_MASK                 64
#define TODM_TODM5_MASK                 128
#define TODM_MQSEC_MASK                 3
#define TODM_MQSEC_BITNUM               0
#define TODM_TODM_MASK                  252
#define TODM_TODM_BITNUM                2

/*
** MCF51XX_tod_struct
** This structure defines Time of Day registers
*/
typedef struct MCF51XX_tod_struct
{
    uchar  TODC;    /* TOD Control register             */
    uchar  TODSC;   /* TOD Status and Control Register  */
    uchar  TODM;    /* TOD Match register               */
    uchar  TODCNT;  /* TOD Counter Register             */
} MCF51XX_TOD_STRUCT, _PTR_ MCF51XX_TOD_STRUCT_PTR;
typedef volatile struct MCF51XX_tod_struct _PTR_ VMCF51XX_TOD_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif

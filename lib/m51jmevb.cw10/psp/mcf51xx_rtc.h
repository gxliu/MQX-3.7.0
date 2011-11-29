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
* $FileName: mcf51xx_rtc.h$
* $Version : 3.0.3.0$
* $Date    : Apr-15-2009$
*
* Comments:
*
*   This file contains the type definitions for the mcf51xx RTC module.
*
*END************************************************************************/

#ifndef __mcf51xx_rtc_h__
#define __mcf51xx_rtc_h__

#define __mcf51xx_rtc_h__version "$Version:3.0.3.0$"
#define __mcf51xx_rtc_h__date    "$Date:Apr-15-2009$"

#ifdef __cplusplus
extern "C" {
#endif

// RTC register masks

#define MCF51XX_RTC_RTCSC_RTIF                      (1<<7)
#define MCF51XX_RTC_RTCSC_RTCLKS(x)                 (((x)&0x03)<<5)
#define MCF51XX_RTC_RTCSC_RTIE                      (1<<4)
#define MCF51XX_RTC_RTCSC_RTCPS(x)                  ((x)&0x0F)

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

// RTC register structure

typedef struct mcf51xx_rtc_struct
{
  uchar RTCSC;   /*** RTCSC - RTC Status and Control Register; 0xFFFF82C0 ***/
  uchar RTCCNT;  /*** RTCCNT - RTC Counter Register; 0xFFFF82C1 ***/
  uchar RTCMOD;  /*** RTCMOD - RTC Modulo Register; 0xFFFF82C2 ***/
} MCF51XX_RTC_STRUCT, _PTR_ MCF51XX_RTC_STRUCT_PTR;
typedef volatile struct mcf51xx_rtc_struct _PTR_ VMCF51XX_RTC_STRUCT_PTR;


#ifdef __cplusplus
}
#endif

#endif

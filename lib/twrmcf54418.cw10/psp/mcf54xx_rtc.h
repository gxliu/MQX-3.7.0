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
* $FileName: mcf5445x_rtc.h$
* $Version : 3.0.3.0$
* $Date    : Jun-11-2009$
*
* Comments:
*
*   This file contains the type definitions for the mcf54xx RTC module.
*
*END************************************************************************/

#ifndef __mcf54xx_rtc_h__
#define __mcf54xx_rtc_h__

#define __mcf54xx_rtc_h__version "$Version:3.0.3.0$"
#define __mcf54xx_rtc_h__date    "$Date:Jun-11-2009$"

#ifdef __cplusplus
extern "C" {
#endif


#define MCF54XX_RTC_HOURMIN_HOURS_WRITE(x)          (((x)&0x1F)<<0x08)
#define MCF54XX_RTC_HOURMIN_HOURS_READ(x)           (((x)>>0x08)&0x1F)
#define MCF54XX_RTC_HOURMIN_MINUTES_WRITE(x)        ((x)&0x3F)
#define MCF54XX_RTC_HOURMIN_MINUTES_READ(x)         ((x)&0x3F)
#define MCF54XX_RTC_SECONDS_WRITE(x)                ((x)&0x3F)
#define MCF54XX_RTC_SECONDS_READ(x)                 ((x)&0x3F)
#define MCF54XX_RTC_ALRM_HM_HOURS_WRITE(x)          (((x)&0x1F)<<0x08)
#define MCF54XX_RTC_ALRM_HM_HOURS_READ(x)           (((x)>>0x08)&0x1F)
#define MCF54XX_RTC_ALRM_HM_MINUTES_WRITE(x)        ((x)&0x3F)
#define MCF54XX_RTC_ALRM_HM_MINUTES_READ(x)         ((x)&0x3F)
#define MCF54XX_RTC_ALRM_SEC_WRITE(x)               ((x)&0x3F)
#define MCF54XX_RTC_ALRM_SEC_READ(x)                ((x)&0x3F)
#define MCF54XX_RTC_CR_EN                           (1<<7)
#define MCF54XX_RTC_CR_SWR                          (1<<0)
#define MCF54XX_RTC_ISR_SW                          (1<<0)
#define MCF54XX_RTC_ISR_MIN                         (1<<1)
#define MCF54XX_RTC_ISR_ALM                         (1<<2)
#define MCF54XX_RTC_ISR_DAY                         (1<<3)
#define MCF54XX_RTC_ISR_1HZ                         (1<<4)
#define MCF54XX_RTC_ISR_HR                          (1<<5)
#define MCF54XX_RTC_ISR_2HZ                         (1<<7)
#define MCF54XX_RTC_ISR_SAM0                        (1<<8)
#define MCF54XX_RTC_ISR_SAM1                        (1<<9)
#define MCF54XX_RTC_ISR_SAM2                        (1<<10)
#define MCF54XX_RTC_ISR_SAM3                        (1<<11)
#define MCF54XX_RTC_ISR_SAM4                        (1<<12)
#define MCF54XX_RTC_ISR_SAM5                        (1<<13)
#define MCF54XX_RTC_ISR_SAM6                        (1<<14)
#define MCF54XX_RTC_ISR_SAM7                        (1<<15)
#define MCF54XX_RTC_ISR_EN                          (1<<31)
#define MCF54XX_RTC_IER_SW                          (1<<0)
#define MCF54XX_RTC_IER_MIN                         (1<<1)
#define MCF54XX_RTC_IER_ALM                         (1<<2)
#define MCF54XX_RTC_IER_DAY                         (1<<3)
#define MCF54XX_RTC_IER_1HZ                         (1<<4)
#define MCF54XX_RTC_IER_HR                          (1<<5)
#define MCF54XX_RTC_ISR_2HZ                         (1<<7)
#define MCF54XX_RTC_IER_SAM0                        (1<<8)
#define MCF54XX_RTC_IER_SAM1                        (1<<9)
#define MCF54XX_RTC_IER_SAM2                        (1<<10)
#define MCF54XX_RTC_IER_SAM3                        (1<<11)
#define MCF54XX_RTC_IER_SAM4                        (1<<12)
#define MCF54XX_RTC_IER_SAM5                        (1<<13)
#define MCF54XX_RTC_IER_SAM6                        (1<<14)
#define MCF54XX_RTC_IER_SAM7                        (1<<15)
#define MCF54XX_RTC_STPWCH_CNT(x)                   ((x)&0x1F)
#define MCF54XX_RTC_DAYS(x)                         ((x)&0xFFFF)
#define MCF54XX_RTC_ALRM_DAY(x)                     ((x)&0xFFFF)


/*
** MCF54XX_RTC_STRUCT
** Real Time Clock                                                                   
*/
typedef struct mcf54xx_rtc_struct
{
   uint_32  RTC_HOURMIN;        // RTC Hours and Minutes Counter Register
   uint_32  RTC_SECONDS;        // RTC Seconds Counter Register
   uint_32  RTC_ALRM_HM;        // RTC Hours and Minutes Alarm Register
   uint_32  RTC_ALRM_SEC;       // RTC Seconds Alarm Register
   uint_32  RTC_CR;             // RTC Control Register
   uint_32  RTC_ISR;            // RTC Interrupt Status Register
   uint_32  RTC_IER;            // RTC Interrupt Enable Register
   uint_32  RTC_STPWCH;         // Stopwatch Minutes Register
   uint_16  filler1;
   uint_16  RTC_DAYS;           // RTC Days Counter Register
   uint_16  filler2;
   uint_16  RTC_ALRM_DAY;       // RTC Days Alarm Register
   uint_32  filler3[3];
   uint_32  RTC_GOCU;           // RTC General Oscillator Count Upper Register
   uint_32  RTC_GOCL;           // RTC General Oscillator Count Lower Register
   
} MCF54XX_RTC_STRUCT, _PTR_ MCF54XX_RTC_STRUCT_PTR;
typedef volatile struct mcf54xx_rtc_struct _PTR_ VMCF54XX_RTC_STRUCT_PTR;


#ifdef __cplusplus
}
#endif

#endif

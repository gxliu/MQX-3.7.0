#ifndef __mpc5125_rtc_h__
#define __mpc5125_rtc_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
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
* $FileName: mpc512x_rtc.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define MPC5125_RTC_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->RTC)

#define MPC5125_RTC_TSR_HOUR_MASK      (0x001f0000)
#define MPC5125_RTC_TSR_HOUR_SHIFT     (16)
#define MPC5125_RTC_TSR_MINUTE_MASK    (0x00003f00)
#define MPC5125_RTC_TSR_MINUTE_SHIFT   (8)
#define MPC5125_RTC_TSR_SECOND_MASK    (0x0000003f)
#define MPC5125_RTC_TSR_SECOND_SHIFT   (0)
#define MPC5125_RTC_TSR_PAUSE_TIME     (0x01000000)
#define MPC5125_RTC_TSR_SET_TIME       (0x02000000)
#define MPC5125_RTC_TSR_SLC_HOUR       (0x00200000)

#define MPC5125_RTC_DSR_MONTH_MASK     (0x001f0000)
#define MPC5125_RTC_DSR_MONTH_SHIFT    (16)
#define MPC5125_RTC_DSR_WEEKDAY_MASK   (0x00003f00)
#define MPC5125_RTC_DSR_WEEKDAY_SHIFT  (8)
#define MPC5125_RTC_DSR_DATE_MASK      (0x0000003f)
#define MPC5125_RTC_DSR_DATE_SHIFT     (0)
#define MPC5125_RTC_DSR_PAUSE_TIME     (0x01000000)
#define MPC5125_RTC_DSR_SET_TIME       (0x02000000)

#define MPC5125_RTC_YEAR_MASK          (0x00000fff)
#define MPC5125_RTC_STP_SW_SHIFT       (16)
#define MPC5125_RTC_STP_SW_MASK        (0x00ff0000)
#define MPC5125_RTC_STP_WRITE_SW       (0x01000000)

#define MPC5125_RTC_CTR_HOUR_MASK      (0x001f0000)
#define MPC5125_RTC_CTR_HOUR_SHIFT     (16)
#define MPC5125_RTC_CTR_MINUTE_MASK    (0x00003f00)
#define MPC5125_RTC_CTR_MINUTE_SHIFT   (8)
#define MPC5125_RTC_CTR_SECOND_MASK    (0x0000003f)
#define MPC5125_RTC_CTR_SECOND_SHIFT   (0)

#define MPC5125_RTC_CDR_MONTH_MASK     (0x0f000000)
#define MPC5125_RTC_CDR_MONTH_SHIFT    (24)
#define MPC5125_RTC_CDR_WEEKDAY_MASK   (0x00e00000)
#define MPC5125_RTC_CDR_WEEKDAY_SHIFT  (21)
#define MPC5125_RTC_CDR_DATE_MASK      (0x001f0000)
#define MPC5125_RTC_CDR_DATE_SHIFT     (16)
#define MPC5125_RTC_CDR_YEAR_MASK      (0x00000fff)
#define MPC5125_RTC_CDR_YEAR_SHIFT     (0)


typedef volatile struct
{
   vuint_32 TSR;             // 0x00 RTC_TSR RTC Time Set Register                              R/W 0x0000_0000 27.3.2.1/27-4
   vuint_32 DSR;             // 0x04 RTC_DSR RTC Date Set Register                              R/W 0x0000_0000 27.3.2.2/27-6
   vuint_32 NY_STP;          // 0x08 RTC_NY_STP RTC New Year and Stopwatch Register             R/W 0x0000_0000 27.3.2.3/27-7
   vuint_32 ALM_IE;          // 0x0C RTC_ALM_IE RTC Alarm and Interrupt Enable Register         R/W 0x0000_0008 27.3.2.4/27-8
   vuint_32 CTR;             // 0x10 RTC_CTR RTC Current Time Register                          R   0x0000_0000 27.3.2.5/27-9
   vuint_32 CDR;             // 0x14 RTC_CDR RTC Current Date Register                          R   0x0000_0000 27.3.2.6/27-9
   vuint_32 ALM_STP_INT;     // 0x18 RTC_ALM_STP_INT RTC Alarm and Stopwatch Interrupt Register R/W 0x0000_0000 27.3.2.7/27-10
   vuint_32 PI_BE;           // 0x1C RTC_PI_BE RTC Periodic Interrupt and Bus Error Register    R/W 0x0000_0000 27.3.2.8/27-11
   vuint_32 TTR;             // 0x20 RTC_TTR RTC Target Time Register                           R/W 0x0000_0000 27.3.2.9/27-11
   vuint_32 ATC;             // 0x24 RTC_ATC RTC Actual Time Counter Register                   R   0xFFFF_FFFE 27.3.2.10/27-12
   vuint_32 KAR;             // 0x28 RTC_KAR RTC Keep Alive Register                            R/W 0x0000_0087 27.3.2.11/27-13
   RESERVED_REGISTER(0x2C,0x100);              
} MPC5125_REAL_TIME_CLOCK, _PTR_ MPC5125_REAL_TIME_CLOCK_PTR;



#endif
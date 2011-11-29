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
* $FileName: mcf5xxx_irtc.h$
* $Version : 3.6.2.0$
* $Date    : Apr-15-2010$
*
* Comments:
*
*   This file contains the SDRAM controler type definitions for the 
*   mcf54xx processor. It has been split out into a separate header 
*   file to share with other Coldfire PSP's.
*
*END************************************************************************/

#ifndef __mcf5xxx_irtc_h__
    #define __mcf5xxx_irtc_h__

#define __mcf5xxx_irtc_h__version "$Version:3.6.2.0$"
#define __mcf5xxx_irtc_h__date    "$Date:Apr-15-2010$"


#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
 * interrupt masks definitions (RTC_ISR and RTC_IER registers)                *
 ******************************************************************************/  

#define MCF5XXX_RTC_INT_STW_MASK        (0x0001 << 1) 
#define MCF5XXX_RTC_INT_ALM_MASK        (0x0001 << 2)
#define MCF5XXX_RTC_INT_DAY_MASK        (0x0001 << 3)
#define MCF5XXX_RTC_INT_HR_MASK         (0x0001 << 4)
#define MCF5XXX_RTC_INT_MIN_MASK        (0x0001 << 5)
#define MCF5XXX_RTC_INT_1HZ_MASK        (0x0001 << 6)
#define MCF5XXX_RTC_INT_2HZ_MASK        (0x0001 << 7)
#define MCF5XXX_RTC_INT_SAM0_MASK       (0x0001 << 8)
#define MCF5XXX_RTC_INT_SAM1_MASK       (0x0001 << 9)
#define MCF5XXX_RTC_INT_SAM2_MASK       (0x0001 <<10) 
#define MCF5XXX_RTC_INT_SAM3_MASK       (0x0001 <<11) 
#define MCF5XXX_RTC_INT_SAM4_MASK       (0x0001 <<12)  
#define MCF5XXX_RTC_INT_SAM5_MASK       (0x0001 <<13) 
#define MCF5XXX_RTC_INT_SAM6_MASK       (0x0001 <<14) 
#define MCF5XXX_RTC_INT_SAM7_MASK       (0x0001 <<15) 
#define MCF5XXX_RTC_INT_ALL_MASK        (0xFFFF) 


typedef struct MCF5XXX_irtc_struct
{
    int_8   RTC_YEAR;               /* 0x00 Year Counter Register                   */
    uint_8  RTC_MONTH;              /* 0x01 Month Counter Register                  */
    uint_8  RTC_DAY_OF_WEEK;        /* 0x02 Day-of-Week Counter Register            */
    uint_8  RTC_DAYS;               /* 0x03 Day Counter Register                    */
    uint_8  RTC_HOURS;              /* 0x04 Hour Counter Register                   */
    uint_8  RTC_MINUTES;            /* 0x05 Minute Counter Register                 */
    uint_8  reserved01;             /* 0x06                                         */
    uint_8  RTC_SECONDS;            /* 0x07 Seconds Counter Register reserved       */
    int_8   RTC_ALM_YEAR;           /* 0x08 Year Alarm Register                     */
    uint_8  RTC_ALM_MONTH;          /* 0x09 Month Alarm Register                    */
    uint_8  reserved02;             /* 0x0A                                         */
    uint_8  RTC_ALM_DAYS;           /* 0x0B Days Alarm Register                     */
    uint_8  RTC_ALM_HOURS;          /* 0x0C HOURS Alarm Register                    */
    uint_8  RTC_ALM_MINUTES;        /* 0x0D Minutes Alarm Register                  */
    uint_16 RTC_ALM_SEC;            /* 0x0E Seconds Alarm Register                  */
    uint_16 RTC_CTRL;               /* 0x10 Control Register                        */
    uint_8  reserved03;             /* 0x12                                         */
    uint_8  RTC_STATUS;             /* 0x13 Status Register                         */
    uint_16 RTC_ISR;                /* 0x14 Interrupt Status Register               */
    uint_16 RTC_IER;                /* 0x16 Interrupt Enable Register               */
    uint_16 RTC_COUNTDOWN_COUNT;    /* 0x18 Countdown (Minutes) Timer Register      */
    uint_8  reserved05[0x05];       
    uint_16 RTC_CFG_DATA;           /* 0x20 Configuration Data Register             */
    uint_8  RTC_DST_START_HOUR;     /* 0x22 Daylight Saving Hour Register           */
    uint_8  RTC_DST_END_HOUR;       /* 0x23 Daylight Saving Hour Register           */
    uint_8  RTC_DST_START_MONTH;    /* 0x24 Daylight Saving Month Register          */
    uint_8  RTC_DST_END_MONTH;      /* 0x25 Daylight Saving Month Register          */
    uint_8  RTC_DST_START_DAY;      /* 0x26 Daylight Saving Day Register            */
    uint_8  RTC_DST_END_DAY;        /* 0x27 Daylight Saving Day Register            */
    uint_8  RTC_COMPEN_INTERVAL;    /* 0x28 Compensation Interval Register          */
    uint_8  RTC_COMPEN_VALUE;       /* 0x29 Compensation Interval Register          */
    uint_8  reserved06[8];          /* 0x2C                                         */
    uint_16 RTC_UP_CNTR_H;          /* 0x32 Counter Register High                   */
    uint_16 RTC_UP_CNTR_L;          /* 0x34 Counter Register Low                    */
    uint_8  reserved07[10];
    uint_8  RTC_STAND_BY_RAM[1985]; /* 0x40 Stand-by RAM                            */           
} MCF5XXX_IRTC_STRUCT, _PTR_ MCF5XXX_IRTC_STRUCT_PTR;

typedef volatile struct MCF5XXX_irtc_struct _PTR_ VMCF5XXX_IRTC_STRUCT_PTR;           


#ifdef __cplusplus
}
#endif

#endif /* __mcf5xxx_irtc_h__ */

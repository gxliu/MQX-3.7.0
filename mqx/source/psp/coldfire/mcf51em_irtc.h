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
* $FileName: mcf51em_irtc.h$
* $Version : 3.6.2.0$
* $Date    : Apr-29-2010$
*
* Comments:
*   File contains definition of IRTC (independent real-time clock) 
*   registers and masks for MCF51EM microcontroller.
*   It provides an independent time-base with optional interrupt, 
*   battery backup and tamper protection.
*
*END************************************************************************/

#ifndef __mcf51em_irtc_h__
    #define __mcf51em_irtc_h__

#define __mcf51em_irtc_h__version "$Version:3.6.2.0$"
#define __mcf51em_irtc_h__date    "$Date:Apr-29-2010$"


#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * interrupt masks definitions (RTC_ISR and RTC_IER registers)                *
 ******************************************************************************/  

#define MCF51EM_RTC_INT_TMPR_MASK       (1 <<  0)
#define MCF51EM_RTC_INT_STW_MASK        (1 <<  1) 
#define MCF51EM_RTC_INT_ALM_MASK        (1 <<  2)
#define MCF51EM_RTC_INT_DAY_MASK        (1 <<  3)
#define MCF51EM_RTC_INT_HR_MASK         (1 <<  4)
#define MCF51EM_RTC_INT_MIN_MASK        (1 <<  5)
#define MCF51EM_RTC_INT_1HZ_MASK        (1 <<  6)
#define MCF51EM_RTC_INT_2HZ_MASK        (1 <<  7)
#define MCF51EM_RTC_INT_SAM0_MASK       (1 <<  8)
#define MCF51EM_RTC_INT_SAM1_MASK       (1 <<  9)
#define MCF51EM_RTC_INT_SAM2_MASK       (1 << 10) 
#define MCF51EM_RTC_INT_SAM3_MASK       (1 << 11) 
#define MCF51EM_RTC_INT_SAM4_MASK       (1 << 12)  
#define MCF51EM_RTC_INT_SAM5_MASK       (1 << 13) 
#define MCF51EM_RTC_INT_SAM6_MASK       (1 << 14) 
#define MCF51EM_RTC_INT_SAM7_MASK       (1 << 15) 
#define MCF51EM_RTC_INT_ALL_MASK        (0xFFFF) 


#define MCF5XXX_RTC_INT_STW_MASK        MCF51EM_RTC_INT_STW_MASK  
#define MCF5XXX_RTC_INT_ALM_MASK        MCF51EM_RTC_INT_ALM_MASK 
#define MCF5XXX_RTC_INT_DAY_MASK        MCF51EM_RTC_INT_DAY_MASK 
#define MCF5XXX_RTC_INT_HR_MASK         MCF51EM_RTC_INT_HR_MASK  
#define MCF5XXX_RTC_INT_MIN_MASK        MCF51EM_RTC_INT_MIN_MASK 
#define MCF5XXX_RTC_INT_1HZ_MASK        MCF51EM_RTC_INT_1HZ_MASK 
#define MCF5XXX_RTC_INT_2HZ_MASK        MCF51EM_RTC_INT_2HZ_MASK 
#define MCF5XXX_RTC_INT_SAM0_MASK       MCF51EM_RTC_INT_SAM0_MASK
#define MCF5XXX_RTC_INT_SAM1_MASK       MCF51EM_RTC_INT_SAM1_MASK
#define MCF5XXX_RTC_INT_SAM2_MASK       MCF51EM_RTC_INT_SAM2_MASK
#define MCF5XXX_RTC_INT_SAM3_MASK       MCF51EM_RTC_INT_SAM3_MASK
#define MCF5XXX_RTC_INT_SAM4_MASK       MCF51EM_RTC_INT_SAM4_MASK
#define MCF5XXX_RTC_INT_SAM5_MASK       MCF51EM_RTC_INT_SAM5_MASK
#define MCF5XXX_RTC_INT_SAM6_MASK       MCF51EM_RTC_INT_SAM6_MASK
#define MCF5XXX_RTC_INT_SAM7_MASK       MCF51EM_RTC_INT_SAM7_MASK
#define MCF5XXX_RTC_INT_ALL_MASK        MCF51EM_RTC_INT_ALL_MASK 



#define RTC_CFG_DATA_CFG0               (1 <<  0)
#define RTC_CFG_DATA_CFG1               (1 <<  1)
#define RTC_CFG_DATA_CFG2               (1 <<  2)
#define RTC_CFG_DATA_CFG3               (1 <<  3)
#define RTC_CFG_DATA_CFG4               (1 <<  4)
#define RTC_CFG_DATA_CFG5               (1 <<  5)
#define RTC_CFG_DATA_CFG6               (1 <<  6)
#define RTC_CFG_DATA_CFG7               (1 <<  7)


/* 
** The RTC module base address is 0xFFFF8640
*/
typedef struct MCF51EM_rtc_struct
{
    int_8   RTC_YEAR;               /*** 0x00 Year Counter Register                   ***/
    uint_8  RTC_MONTH;              /*** 0x01 Month Counter Register                  ***/
    uint_8  RTC_DAY_OF_WEEK;        /*** 0x02 Day-of-Week Counter Register            ***/
    uint_8  RTC_DAYS;               /*** 0x03 Day Counter Register                    ***/
    uint_8  RTC_HOURS;              /*** 0x04 Hour Counter Register                   ***/
    uint_8  RTC_MINUTES;            /*** 0x05 Minute Counter Register                 ***/
    uint_8  reserved01;             /*** 0x06                                         ***/
    uint_8  RTC_SECONDS;            /*** 0x07 Seconds Counter Register reserved       ***/
    int_8   RTC_ALM_YEAR;           /*** 0x08 Year Alarm Register                     ***/
    uint_8  RTC_ALM_MONTH;          /*** 0x09 Month Alarm Register                    ***/
    uint_8  reserved02;             /*** 0x0A                                         ***/
    uint_8  RTC_ALM_DAYS;           /*** 0x0B Days Alarm Register                     ***/
    uint_8  RTC_ALM_HOURS;          /*** 0x0C HOURS Alarm Register                    ***/
    uint_8  RTC_ALM_MINUTES;        /*** 0x0D Minutes Alarm Register                  ***/
    uint_16 RTC_ALM_SEC;            /*** 0x0E Seconds Alarm Register                  ***/
    uint_16 RTC_CTRL;               /*** 0x10 Control Register                        ***/
    uint_8  reserved03;             /*** 0x12                                         ***/
    uint_8  RTC_STATUS;             /*** 0x13 Status Register                         ***/
    uint_16 RTC_ISR;                /*** 0x14 Interrupt Status Register               ***/
    uint_16 RTC_IER;                /*** 0x16 Interrupt Enable Register               ***/
    uint_8  reserved04;             /*** 0x18                                         ***/
    uint_8  RTC_COUNTDOWN_COUNT;    /*** 0x19 Countdown (Minutes) Timer Register      ***/
    uint_8  reserved05[0x07];       /*** 0x20                                         ***/
    uint_8  RTC_CFG_DATA;           /*** 0x21 Configuration Data Register             ***/
    uint_8  RTC_DST_START_HOUR;     /*** 0x22 Daylight Saving Hour Register           ***/
    uint_8  RTC_DST_END_HOUR;       /*** 0x23 Daylight Saving Hour Register           ***/
    uint_8  RTC_DST_START_MONTH;    /*** 0x24 Daylight Saving Month Register          ***/
    uint_8  RTC_DST_END_MONTH;      /*** 0x25 Daylight Saving Month Register          ***/
    uint_8  RTC_DST_START_DAY;      /*** 0x26 Daylight Saving Day Register            ***/
    uint_8  RTC_DST_END_DAY;        /*** 0x27 Daylight Saving Day Register            ***/
    uint_8  RTC_COMPEN_INTERVAL;    /*** 0x28 Compensation Interval Register          ***/
    uint_8  RTC_COMPEN_VALUE;       /*** 0x29 Compensation Interval Register          ***/
    int_8   RTC_TIME_STAMP_YEAR;    /*** 0x2A Tamper Time Stamp Year Register         ***/
    uint_8  RTC_TIME_STAMP_MONTHS;  /*** 0x2B Tamper Time Stamp Month Register        ***/
    uint_8  reserved06;             /*** 0x2C                                         ***/
    uint_8  RTC_TIME_STAMP_DAY;     /*** 0x2D Tamper Time Stamp Day Register          ***/
    uint_8  RTC_TIME_STAMP_HOURS;   /*** 0x2E Tamper Time Stamp Hours Register        ***/
    uint_8  RTC_TIME_STAMP_MINUTES; /*** 0x2F Tamper Time Stamp Minutes Register      ***/
    uint_8  RTC_TIME_STAMP_STATUS;  /*** 0x30 Tamper Time Stamp Status Register       ***/
    uint_8  RTC_TIME_STAMP_SECONDS; /*** 0x31 Tamper Time Stamp Seconds Register      ***/
    uint_16 RTC_UP_CNTR_H;          /*** 0x32 Counter Register High                   ***/
    uint_16 RTC_UP_CNTR_L;          /*** 0x34 Counter Register Low                    ***/
    uint_8  reserved07[10];
    uint_8  RTC_STAND_BY_RAM[32];   /*** 0x40 Stand-by RAM                            ***/           
} MCF51EM_RTC_STRUCT, _PTR_ MCF51EM_RTC_STRUCT_PTR;

typedef volatile struct MCF51EM_rtc_struct _PTR_ VMCF51EM_RTC_STRUCT_PTR;           


#ifdef __cplusplus
}
#endif

#endif /* __mcf51em_irtc_h__ */

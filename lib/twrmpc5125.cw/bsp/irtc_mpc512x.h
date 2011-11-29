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
* $FileName: irtc_mpc512x.h$
* $Version : 3.6.5.0$
* $Date    : Nov-8-2010$
*
* Comments:
*
*   Processor family specific file needed for RTC module.
*
*END************************************************************************/

#ifndef __irtc_mpc512x_h__
#define __irtc_mpc512x_h__


#define DEVSPEC_RTC_RTCISR_SW       2
#define DEVSPEC_RTC_RTCISR_ALM      2
#define DEVSPEC_RTC_RTCIENR_SW      4
#define DEVSPEC_RTC_RTCIENR_ALM     4

#define DEVSPEC_RTC_INT_ALL_MASK    (DEVSPEC_RTC_RTCIENR_SW | DEVSPEC_RTC_RTCIENR_ALM)



/******************************************************************************
 * interrupt masks definitions (RTC_ISR and RTC_IER registers)                *
 ******************************************************************************/  


/* IRTC time reperesentation */
typedef struct rtc_time_struct
{
    uint_8  seconds;
    uint_8  minutes;
    uint_8  hours;
    uint_8  days;
    uint_8  wday;
    uint_8  month;
    uint_16 year;
} RTC_TIME_STRUCT, _PTR_ RTC_TIME_STRUCT_PTR;

/* IRTC generic functions */

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_set_time
* Returned Value   : none
* Comments         :
*    This function sets the RTC time according to given time struct.
*
*END*********************************************************************/

extern void     _rtc_set_time (RTC_TIME_STRUCT_PTR time);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_get_time
* Returned Value   : none
* Comments         :
*    This function gets the RTC time and stores it in given time struct.
*
*END*********************************************************************/

extern void     _rtc_get_time (RTC_TIME_STRUCT_PTR time);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_set_alarm
* Returned Value   : none
* Comments         :
*    This function sets RTC alarm time according to given time struct.
*    Alarm happens a half second after match.
*
*END*********************************************************************/

extern void     _rtc_set_alarm (RTC_TIME_STRUCT_PTR time);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_get_alarm
* Returned Value   : none
* Comments         :
*    This function gets the RTC alarm time and stores it in given time struct.
*
*END*********************************************************************/

extern void     _rtc_get_alarm (RTC_TIME_STRUCT_PTR time);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_set_stopwatch
* Returned Value   : none
* Comments         :
*    This function sets the RTC stopwatch decrementer value (minutes).
*    Stopwatch decrements each new RTC minute and stops (disables) at -1.
*
*END*********************************************************************/

extern void     _rtc_set_stopwatch (uint_32 minutes);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_get_stopwatch
* Returned Value   : actual RTC minute stopwatch counter value
* Comments         :
*    This function returns the actual value of RTC stopwatch decrementer.
*
*END*********************************************************************/

extern uint_32  _rtc_get_stopwatch (void);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_time_to_mqx_time
* Returned Value   : none
* Comments         :
*    This function transforms RTC time format to MQX time format.
*    RTC time range is wider (65536 days vs. 49710 days), overflow is not checked,
*    miliseconds are set to 0.
*
*END*********************************************************************/
extern void _rtc_time_to_mqx_time 
(
    /* [IN] RTC time representation */
    RTC_TIME_STRUCT_PTR rtc_time, 
    /* [OUT] MQX time representation */
    TIME_STRUCT_PTR     mqx_time
);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_time_from_mqx_time
* Returned Value   : none
* Comments         :
*    This function transforms MQX time format to RTC time format.
*    MQX time range is shorter (49710 days vs. 65536 days), miliseconds are ignored.
*
*END*********************************************************************/

extern void _rtc_time_from_mqx_time
(
    /* [IN] MQX time representation */
    TIME_STRUCT_PTR     mqx_time, 
    /* [OUT] RTC time representation */
    RTC_TIME_STRUCT_PTR rtc_time
);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_time_to_mqx_date
* Returned Value   : none
* Comments         :
*    This function transforms RTC time format to MQX date format.
*    Miliseconds are set to 0.
*
*END*********************************************************************/

extern void _rtc_time_to_mqx_date 
(
    /* [IN] RTC time representation */
    RTC_TIME_STRUCT_PTR rtc_time, 
    /* [OUT] MQX date representation */
    DATE_STRUCT_PTR     mqx_date
);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_time_from_mqx_date
* Returned Value   : none
* Comments         :
*    This function transforms MQX date format to RTC time format.
*    Miliseconds are ignored.
*
*END*********************************************************************/


extern void _rtc_time_from_mqx_date
(
    /* [IN] MQX date representation */
    DATE_STRUCT_PTR     mqx_date, 
    /* [OUT] RTC time representation */
    RTC_TIME_STRUCT_PTR rtc_time
);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_sync_with_mqx
* Returned Value   : none
* Comments         :
*    This function synchronizes RTC time with MQX date.
*
*END*********************************************************************/

extern _mqx_int _rtc_sync_with_mqx
(
    /* [IN] whether to update MQX time (source is RTC) or RTC time (source is MQX) */
    boolean update_mqx
);


#endif   /* __irtc_mpc512x_h__ */

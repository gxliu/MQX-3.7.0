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
* $FileName: irtc_mpc512x.c$
* $Version : 3.6.5.0$
* $Date    : Nov-2-2010$
*
* Comments:
*
*   Processor family specific file needed for RTC module.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>


/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_set_time
* Returned Value   : none
* Comments         :
*    This function sets the RTC time according to given time struct.
*
*END*********************************************************************/

void _rtc_set_time 
(
    /* [IN] given time to be set as RTC time */
    RTC_TIME_STRUCT_PTR time
)
{
    MPC5125_REAL_TIME_CLOCK_PTR rtc = (MPC5125_REAL_TIME_CLOCK_PTR) _bsp_get_rtc_base_address();
    uint_32 tsr,dsr; 
    _int_disable(); 

    tsr = ((time->hours   << MPC5125_RTC_TSR_HOUR_SHIFT  ) & MPC5125_RTC_TSR_HOUR_MASK)   |
          ((time->minutes << MPC5125_RTC_TSR_MINUTE_SHIFT) & MPC5125_RTC_TSR_MINUTE_MASK) |
          ((time->seconds << MPC5125_RTC_TSR_SECOND_SHIFT) & MPC5125_RTC_TSR_SECOND_MASK);
          
    rtc->TSR = tsr | MPC5125_RTC_TSR_PAUSE_TIME;
    _PSP_SYNC();
    rtc->TSR = tsr | MPC5125_RTC_TSR_PAUSE_TIME | MPC5125_RTC_TSR_SET_TIME;
    _PSP_SYNC();
    rtc->TSR = tsr | MPC5125_RTC_TSR_PAUSE_TIME;
    _PSP_SYNC();
    rtc->TSR = tsr;
    _PSP_SYNC();
             
    dsr = ((time->month << MPC5125_RTC_DSR_MONTH_SHIFT  ) & MPC5125_RTC_DSR_MONTH_MASK)   |
          ((time->wday  << MPC5125_RTC_DSR_WEEKDAY_SHIFT) & MPC5125_RTC_DSR_WEEKDAY_MASK) |
          ((time->days  << MPC5125_RTC_DSR_DATE_SHIFT   ) & MPC5125_RTC_DSR_DATE_MASK);
          
    rtc->DSR = dsr | MPC5125_RTC_DSR_PAUSE_TIME;
    _PSP_SYNC();
    rtc->NY_STP = time->year & MPC5125_RTC_YEAR_MASK;
    _PSP_SYNC();
    rtc->DSR = dsr | MPC5125_RTC_DSR_PAUSE_TIME | MPC5125_RTC_DSR_SET_TIME;
    _PSP_SYNC();
    rtc->NY_STP = time->year & MPC5125_RTC_YEAR_MASK;
    _PSP_SYNC();
    rtc->DSR = dsr | MPC5125_RTC_DSR_PAUSE_TIME;
    _PSP_SYNC();
    rtc->NY_STP = time->year & MPC5125_RTC_YEAR_MASK;
    _PSP_SYNC();
    rtc->DSR = dsr;
    _PSP_SYNC();
    rtc->NY_STP = time->year & MPC5125_RTC_YEAR_MASK;
    _PSP_SYNC();
             
    _int_enable(); 
}



/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_get_time
* Returned Value   : none
* Comments         :
*    This function gets the RTC time and stores it in given time struct.
*
*END*********************************************************************/
void _rtc_get_time 
(
    /* [OUT] this parameter gets actual RTC time */
    RTC_TIME_STRUCT_PTR time
)
{
    MPC5125_REAL_TIME_CLOCK_PTR rtc = (MPC5125_REAL_TIME_CLOCK_PTR) _bsp_get_rtc_base_address();
    uint_32 cd1 =  rtc->CDR;
    uint_32 ct1 =  rtc->CTR;
    uint_32 cd2 =  rtc->CDR;
    uint_32 ct2 =  rtc->CTR;
    uint_32 max_loops = 100;

    while (max_loops-- && ((cd1!=cd2) || (ct1!=ct2))) {
        cd1 =  rtc->CDR;
        ct1 =  rtc->CTR;
        cd2 =  rtc->CDR;
        ct2 =  rtc->CTR;
    } 

    time->year    = (cd1 &MPC5125_RTC_CDR_YEAR_MASK   ) >> MPC5125_RTC_CDR_YEAR_SHIFT;
    time->month   = (cd1 &MPC5125_RTC_CDR_MONTH_MASK  ) >> MPC5125_RTC_CDR_MONTH_SHIFT;    
    time->days    = (cd1 &MPC5125_RTC_CDR_DATE_MASK   ) >> MPC5125_RTC_CDR_DATE_SHIFT;     
    time->wday    = (cd1 &MPC5125_RTC_CDR_WEEKDAY_MASK) >> MPC5125_RTC_CDR_WEEKDAY_SHIFT;
    time->hours   = (ct1 &MPC5125_RTC_CTR_HOUR_MASK   ) >> MPC5125_RTC_CTR_HOUR_SHIFT;
    time->minutes = (ct1 &MPC5125_RTC_CTR_MINUTE_MASK ) >> MPC5125_RTC_CTR_MINUTE_SHIFT;  
    time->seconds = (ct1 &MPC5125_RTC_CTR_SECOND_MASK ) >> MPC5125_RTC_CTR_SECOND_SHIFT;  
}


/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_set_alarm
* Returned Value   : none
* Comments         :
*    This function sets RTC alarm time according to given time struct.
*    Alarm happens a half second after match.
*
*END*********************************************************************/
void _rtc_set_alarm 
(
    /* [IN] time to be set as RTC alarm time */
    RTC_TIME_STRUCT_PTR time
)
{
    MPC5125_REAL_TIME_CLOCK_PTR rtc = (MPC5125_REAL_TIME_CLOCK_PTR) _bsp_get_rtc_base_address();

    _int_disable();

#if 0
    rtc->RTC_ALM_YEAR        = (int_8)((uint_16)time->year-RTC_BASE_YEAR);  
    rtc->RTC_ALM_MONTH       = (uint_8)time->month;
    rtc->RTC_ALM_DAYS        = (uint_8)time->days;
    rtc->RTC_ALM_HOURS       = (uint_8)time->hours;
    rtc->RTC_ALM_MINUTES     = (uint_8)time->minutes;
    rtc->RTC_ALM_SEC         = (uint_8)time->seconds;
#endif    
    
    _int_enable();
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_get_alarm
* Returned Value   : none
* Comments         :
*    This function gets the RTC alarm time and stores it in given time struct.
*
*END*********************************************************************/
void _rtc_get_alarm 
(
    /* [OUT] this parameter gets the RTC alarm time */
    RTC_TIME_STRUCT_PTR time
)
{
    MPC5125_REAL_TIME_CLOCK_PTR rtc = (MPC5125_REAL_TIME_CLOCK_PTR) _bsp_get_rtc_base_address();
    
#if 0
    time->year    = rtc->RTC_ALM_YEAR + RTC_BASE_YEAR;
    time->month   = rtc->RTC_ALM_MONTH;       
    time->days    = rtc->RTC_ALM_DAYS;        
    time->hours   = rtc->RTC_ALM_HOURS;       
    time->minutes = rtc->RTC_ALM_MINUTES;     
    time->seconds = rtc->RTC_ALM_SEC;  
#endif    
}


/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_set_stopwatch
* Returned Value   : none
* Comments         :
*    This function sets the RTC stopwatch decrementer value (minutes).
*    Stopwatch decrements each new RTC minute and stops (disables) at -1.
*
*END*********************************************************************/
void _rtc_set_stopwatch 
(
    /* [IN] number of minutes to countdown */
    uint_32 minutes
)
{
    MPC5125_REAL_TIME_CLOCK_PTR rtc = (MPC5125_REAL_TIME_CLOCK_PTR) _bsp_get_rtc_base_address();

    _int_disable();

     rtc->NY_STP = MPC5125_RTC_STP_WRITE_SW | ((minutes<<MPC5125_RTC_STP_SW_SHIFT)&MPC5125_RTC_STP_SW_MASK);

    _int_enable();  
}


/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_get_stopwatch
* Returned Value   : actual RTC minute stopwatch counter value
* Comments         :
*    This function returns the actual value of RTC stopwatch decrementer.
*
*END*********************************************************************/

uint_32 _rtc_get_stopwatch 
(
    void
)
{
    MPC5125_REAL_TIME_CLOCK_PTR rtc = (MPC5125_REAL_TIME_CLOCK_PTR) _bsp_get_rtc_base_address();

    return (rtc->NY_STP&MPC5125_RTC_STP_SW_MASK)>>MPC5125_RTC_STP_SW_SHIFT;
}


/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_sync_with_mqx
* Returned Value   : none
* Comments         :
*    This function synchronizes RTC time with MQX date.
*
*END*********************************************************************/

_mqx_int _rtc_sync_with_mqx
(
    /* [IN] whether to update MQX time (source is RTC) or RTC time (source is MQX) */
    boolean update_mqx
)
{
    RTC_TIME_STRUCT rtc_time;
    DATE_STRUCT     mqx_date;
    TIME_STRUCT     mqx_time;
    
    if (update_mqx == TRUE) 
    {
        _rtc_get_time (&rtc_time);
        _rtc_time_to_mqx_date (&rtc_time, &mqx_date);
        _time_from_date(&mqx_date, &mqx_time);
        _time_set (&mqx_time);
    }
    else
    {
        _time_get (&mqx_time);
        _time_to_date(&mqx_time, &mqx_date);
        _rtc_time_from_mqx_date (&mqx_date, &rtc_time);
        _rtc_set_time (&rtc_time);
    }
    return MQX_OK;
}

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

void _rtc_time_to_mqx_time 
(
    /* [IN] RTC time representation */
    RTC_TIME_STRUCT_PTR rtc_time, 
    /* [OUT] MQX time representation */
    TIME_STRUCT_PTR     mqx_time
)
{

    DATE_STRUCT     mqx_date;
    
    _rtc_time_to_mqx_date (rtc_time, &mqx_date);
    _time_from_date(&mqx_date, mqx_time);
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_time_from_mqx_time
* Returned Value   : none
* Comments         :
*    This function transforms MQX time format to RTC time format.
*    MQX time range is shorter (49710 days vs. 65536 days), miliseconds are ignored.
*
*END*********************************************************************/

void _rtc_time_from_mqx_time
(
    /* [IN] MQX time representation */
    TIME_STRUCT_PTR     mqx_time, 
    /* [OUT] RTC time representation */
    RTC_TIME_STRUCT_PTR rtc_time
)
{
    DATE_STRUCT     mqx_date;

    _time_to_date(mqx_time, &mqx_date);
    _rtc_time_from_mqx_date (&mqx_date, rtc_time);

}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_time_to_mqx_date
* Returned Value   : none
* Comments         :
*    This function transforms RTC time format to MQX date format.
*    Miliseconds are set to 0.
*
*END*********************************************************************/

void _rtc_time_to_mqx_date 
(
    /* [IN] RTC time representation */
    RTC_TIME_STRUCT_PTR rtc_time, 
    /* [OUT] MQX date representation */
    DATE_STRUCT_PTR     mqx_date
)
{
    mqx_date->MILLISEC =  0;
    mqx_date->SECOND   =  rtc_time->seconds;
    mqx_date->MINUTE   =  rtc_time->minutes;
    mqx_date->HOUR     =  rtc_time->hours;
    mqx_date->DAY      =  rtc_time->days;
    mqx_date->MONTH    =  rtc_time->month;
    mqx_date->YEAR     =  rtc_time->year;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_time_from_mqx_date
* Returned Value   : none
* Comments         :
*    This function transforms MQX date format to RTC time format.
*    Miliseconds are ignored.
*
*END*********************************************************************/

void _rtc_time_from_mqx_date
(
    /* [IN] MQX date representation */
    DATE_STRUCT_PTR     mqx_date, 
    /* [OUT] RTC time representation */
    RTC_TIME_STRUCT_PTR rtc_time
)
{
    rtc_time->seconds   = mqx_date->SECOND;   
    rtc_time->minutes   = mqx_date->MINUTE;    
    rtc_time->hours     = mqx_date->HOUR;      
    rtc_time->days      = mqx_date->DAY;       
    rtc_time->month     = mqx_date->MONTH;     
    rtc_time->year      = mqx_date->YEAR;      
}

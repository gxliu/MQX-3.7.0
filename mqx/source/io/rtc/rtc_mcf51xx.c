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
* $FileName: rtc_mcf51xx.c$
* $Version : 3.7.12.0$
* $Date    : Mar-16-2011$
*
* Comments:
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>

static RTC_TIME_STRUCT real_time = {0};
static RTC_TIME_STRUCT alarm_time = {0};
static uint_32 stopwatch = 0;
static uint_32 user_enables = 0;
static uint_32 user_requests = 0;
void (_CODE_PTR_ user_isr)(pointer) = NULL;

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_init
* Returned Value   : MQX error code
* Comments         :
*    This function (re)initializes/clears/enables RTC module.
*    If cleared, alarm happens after RTC overflow, stopwatch happens next minute.
*    Reset disables and clears all interrupts and stopwatch (even if cleared).
*
*END*********************************************************************/
uint_32 _rtc_init 
(
    /* [IN] flags identifying init operations */
    uint_32 flags
)
{
    uint_32 result = MQX_OK;
    VMCF51XX_RTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();
    rtc->RTCSC = MCF51XX_RTC_RTCSC_RTCLKS(0) | MCF51XX_RTC_RTCSC_RTCPS(0x0F);  // clear the interrupt flag, 1kHz internal clock,1s interval
    rtc->RTCMOD = 0;             // 1s interrupt

    // clear time, alarm and stopwatch, if requested
    if (flags & RTC_INIT_FLAG_CLEAR) {      
      real_time.seconds = 0;
      real_time.minutes = 0;
      real_time.hours = 0;
      real_time.days = 0;
      alarm_time.seconds = 0;
      alarm_time.minutes = 0;
      alarm_time.hours = 0;
      alarm_time.days = 0;
      stopwatch = 0;
    }

    // reset current user interrupt state and callback, if requested
    if (flags & RTC_INIT_FLAG_RESET) {
      user_requests = 0;
      user_enables = 0;
      user_isr = NULL;
      stopwatch = (uint_32)-1;
    }

    // install HW interrupt and run the RTC, if requested
    if (flags & RTC_INIT_FLAG_ENABLE) {
      if (NULL == _int_install_isr (_bsp_get_rtc_vector (), (void (_CODE_PTR_))_rtc_isr, (pointer)rtc)) result = _task_get_error ();
      if (MQX_OK == result) {
        rtc->RTCSC |= MCF51XX_RTC_RTCSC_RTIE;
      }
    }

    return result;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_isr
* Returned Value   : none
* Comments         :
*    This is ISR for RTC module, triggered each second.
*
*END*********************************************************************/
void _rtc_isr 
(
    /* [IN] rtc module pointer passed to interrupt */
    pointer ptr
)
{
    VMCF51XX_RTC_STRUCT_PTR rtc = (VMCF51XX_RTC_STRUCT_PTR)ptr;
    
    rtc->RTCSC |= MCF51XX_RTC_RTCSC_RTIF;   // clear interrupt flag

    user_requests |= MCF51XX_RTC_RTCISR_1HZ;   // second boundary
    real_time.seconds++;
    if (real_time.seconds > 59)   // minute boundary
    {
        real_time.seconds = 0;
        user_requests |= MCF51XX_RTC_RTCISR_MIN;
        if (stopwatch != (uint_32)-1) {   // stopwatch decrementer
          stopwatch--;
          if (stopwatch == (uint_32)-1) {
            user_requests |= MCF51XX_RTC_RTCISR_SW;
          }
        }          
        real_time.minutes++;
        if (real_time.minutes > 59)   // hour boundary
        {
            real_time.minutes = 0;
            user_requests |= MCF51XX_RTC_RTCISR_HR;
            real_time.hours++;
            if (real_time.hours > 23)   // days boundary
            {
                real_time.hours = 0;
                user_requests |= MCF51XX_RTC_RTCISR_DAY;
                real_time.days++;
            }    
        }    
    }
    // alarm checking
    if ((real_time.seconds == alarm_time.seconds) && (real_time.minutes == alarm_time.minutes) && (real_time.hours == alarm_time.hours) && (real_time.days == alarm_time.days)) {
      user_requests |= MCF51XX_RTC_RTCISR_ALM;
    }
    // user callback triggering
    if ((NULL != user_isr) && (user_requests & user_enables)) user_isr ((pointer)rtc);
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_int_install
* Returned Value   : MQX error code
* Comments         :
*    This function installs given user callback for RTC module.
*
*END*********************************************************************/
uint_32 _rtc_int_install 
(
    /* [IN] pointer to user ISR code */
    pointer isr
)
{
    user_isr = isr;
    return MQX_OK;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_int_enable
* Returned Value   : bitmask of new int enable state
* Comments         :
*    This function enables/disables RTC interrupts according to specified bitmask.
*
*END*********************************************************************/
uint_32 _rtc_int_enable 
(
    /* [IN] whether to enable or disable interrupts */
    boolean enable, 
    /* [IN] bitmask of affected interrupts */
    uint_32 bitmask
)
{
    if (enable){
      user_enables |= bitmask;
    } else {
      user_enables &= (~ bitmask);
    }
    return user_enables;
}
                              
/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_clear_requests
* Returned Value   : none
* Comments         :
*    This function clears RTC interrupt requests according to given bitmask.
*
*END*********************************************************************/
void _rtc_clear_requests 
(
    /* [IN] bitmask of affected interrupts */
    uint_32 bitmask
)
{
    user_requests &= (~ bitmask);
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_get_status
* Returned Value   : bitmask of actual RTC interrupt requests + RTC enabled bit
* Comments         :
*    This function returns bitmask of pending RTC interrupt requests along
*    with RTC enabled bit (bit MCF51XX_RTC_RTCISR_EN).
*
*END*********************************************************************/
uint_32 _rtc_get_status 
(
    void
)
{
    VMCF51XX_RTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();
    uint_32 result = user_requests;
    if (rtc->RTCSC & MCF51XX_RTC_RTCSC_RTIE) result |= MCF51XX_RTC_RTCISR_EN;
    return result;
}

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
    VMCF51XX_RTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();
    uint_8 tmp = rtc->RTCSC & MCF51XX_RTC_RTCSC_RTIE;   
    rtc->RTCSC &= (~ MCF51XX_RTC_RTCSC_RTIE);             // disable RTC
    real_time = *time;                                    // set new time
    if (real_time.seconds > 59) real_time.seconds = 59;   // correct time
    if (real_time.minutes > 59) real_time.minutes = 59;
    if (real_time.hours > 23) real_time.hours = 23;
    rtc->RTCSC |= MCF51XX_RTC_RTCSC_RTIF;                 // clear RTC request
    rtc->RTCSC |= tmp;                                    // restore RTC state
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
    RTC_TIME_STRUCT tmp;  
    time->hours = 0xFF;
    do   // loop until same time is read twice - keeping time integrity
    {
      tmp = *time;
      *time = real_time;
    } while ((tmp.seconds != time->seconds) || (tmp.minutes != time->minutes) || (tmp.hours != time->hours) || (tmp.days != time->days));
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_set_alarm
* Returned Value   : none
* Comments         :
*    This function sets RTC alarm time according to given time struct.
*    Alarm happens immediately after match.
*
*END*********************************************************************/
void _rtc_set_alarm 
(
    /* [IN] time to be set as RTC alarm time */
    RTC_TIME_STRUCT_PTR time
)
{
    uint_32 enables = user_enables & MCF51XX_RTC_RTCIENR_ALM;
    user_enables &= (~ MCF51XX_RTC_RTCIENR_ALM);            // disable alarm interrupt
    alarm_time = *time;                                     // set new alarm time
    if (alarm_time.seconds > 59) alarm_time.seconds = 59;   // correct alarm time
    if (alarm_time.minutes > 59) alarm_time.minutes = 59;
    if (alarm_time.hours > 23) alarm_time.hours = 23;
    user_requests &= (~ MCF51XX_RTC_RTCISR_ALM);            // clear alarm interrupt
    user_enables |= enables;                                // restore alarm interrupt state
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
    *time = alarm_time;
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
    uint_32 enables = user_enables & MCF51XX_RTC_RTCIENR_SW;
    user_enables &= (~ MCF51XX_RTC_RTCIENR_SW);            // disable stopwatch interrupt
    stopwatch = MCF51XX_RTC_STPWCH_CNT(minutes);           // set new stopwatch
    user_requests &= (~ MCF51XX_RTC_RTCISR_SW);            // clear stopwatch interrupt
    user_enables |= enables;                               // restore stopwatch interrupt state
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
    return stopwatch;
}
/* EOF */


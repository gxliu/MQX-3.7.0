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
* $FileName: tod_mcf51xx.c$
* $Version : 3.6.5.0$
* $Date    : Nov-2-2010$
*
* Comments:
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <rtc.h>



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
    
    VMCF51XX_TOD_STRUCT_PTR tod = _bsp_get_rtc_base_address ();


#if BSPCFG_USE_32KHZ_XTAL == 1
    /* Clear the interrupt flag, 32.768kHz external clock, 1s interval */
    tod->TODC   = TODC_TODPS0_MASK;
#elif BSPCFG_USE_16MHZ_XTAL == 1
    /* Setup for 16MHz clock source */
    tod->TODC   = TODC_TODPS2_MASK | TODC_TODPS1_MASK |TODC_TODPS0_MASK;
#endif
    tod->TODSC  = TODSC_SECF_MASK | TODSC_SECIE_MASK ;
    tod->TODC  |= TODC_TODEN_MASK;


    /* Clear time, alarm and stopwatch, if requested */
    if (flags & RTC_INIT_FLAG_CLEAR)    {      
        
        real_time.seconds   = 0;
        real_time.minutes   = 0;
        real_time.hours     = 0;
        real_time.days      = 0;
        
        alarm_time.seconds  = 0;
        alarm_time.minutes  = 0;
        alarm_time.hours    = 0;
        alarm_time.days     = 0;
        
        stopwatch           = 0;
    }

    /* Reset current user interrupt state and callback, if requested */
    if (flags & RTC_INIT_FLAG_RESET)    {
        user_requests = 0;
        user_enables = 0;
        user_isr = NULL;
        stopwatch = (uint_32) - 1;
    }

    /* Install HW interrupt and run the RTC, if requested */
    if (flags & RTC_INIT_FLAG_ENABLE) {
    
        if (NULL == _int_install_isr ( _bsp_get_rtc_vector (), 
                                      (void (_CODE_PTR_))_rtc_isr, 
                                      (pointer)tod)) 
        {
            result = _task_get_error ();
        }
        
        if (MQX_OK == result) {
            
            /* Clear TOD second interrupt flag */
            tod->TODSC |= TODSC_SECF_MASK;
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

    VMCF51XX_TOD_STRUCT_PTR tod = (VMCF51XX_TOD_STRUCT_PTR)ptr;
    

    /* Clear TOD second interrupt flag */
    tod->TODSC |= TODSC_SECF_MASK;

    user_requests |= MCF51XX_RTC_RTCISR_1HZ;   // second boundary
    
    real_time.seconds++;
    
    /* check minute boundary */
    if (real_time.seconds > 59)
    {
        real_time.seconds = 0;
        user_requests |= MCF51XX_RTC_RTCISR_MIN;
        
        
        if (stopwatch != (uint_32)-1) 
        {   
            /* stopwatch decrementer */
            stopwatch--;
            if (stopwatch == (uint_32)-1) {
               user_requests |= MCF51XX_RTC_RTCISR_SW;
            }
        }          
        
        real_time.minutes++;
        
        /* check hour boundary */
        if (real_time.minutes > 59)   
        {
            real_time.minutes = 0;
            user_requests |= MCF51XX_RTC_RTCISR_HR;
            real_time.hours++;
            
            /* check day boundary */
            if (real_time.hours > 23)
            {
                real_time.hours = 0;
                user_requests |= MCF51XX_RTC_RTCISR_DAY;
                real_time.days++;
            }    
        }    
    }
    
    /* alarm checking */
    if (    (real_time.seconds == alarm_time.seconds) 
         && (real_time.minutes == alarm_time.minutes) 
         && (real_time.hours   == alarm_time.hours) 
         && (real_time.days    == alarm_time.days)) 
    {
        user_requests |= MCF51XX_RTC_RTCISR_ALM;
    }
    
    /* user callback triggering */
    if (    (NULL != user_isr) 
         && (user_requests & user_enables)) {
        
        user_isr ((pointer)tod);
    }
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
    VMCF51XX_TOD_STRUCT_PTR tod    = _bsp_get_rtc_base_address ();
    uint_32                 result = user_requests;
    
    if (tod->TODSC & TODSC_SECIE_MASK) result |= MCF51XX_RTC_RTCISR_EN;
    
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
    VMCF51XX_TOD_STRUCT_PTR tod = _bsp_get_rtc_base_address ();
    uint_8                  tmp; 
    
    /* Store TODSC second interrupt mask */
    tmp = tod->TODSC & TODSC_SECIE_MASK;
    
    /* Disable TODSC second interrupt */
    tod->TODSC &= ~TODSC_SECIE_MASK;
    
    /* Set new time */
    real_time = *time;
    
    /* Correct time */
    if (real_time.seconds > 59) real_time.seconds = 59;
    if (real_time.minutes > 59) real_time.minutes = 59;
    if (real_time.hours   > 23) real_time.hours   = 23;
                          
    /* Clear TOD second flag */
    tod->TODSC |= TODSC_SECF_MASK;
    
    /* Restore TOD state */
    tod->TODSC |= tmp;                                    
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
    
    time->hours     = 0xFF;
    
    /* loop until same time is read twice to keep time integrity */
    do   
    {
        tmp = *time;
        *time = real_time;
    } while (    (tmp.seconds != time->seconds) 
              || (tmp.minutes != time->minutes) 
              || (tmp.hours   != time->hours) 
              || (tmp.days    != time->days));
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
    
    /* Disable stopwatch interrupt */
    user_enables &= (~ MCF51XX_RTC_RTCIENR_SW);            
    
    /* Set new stopwatch */
    stopwatch = MCF51XX_RTC_STPWCH_CNT(minutes);
    
    /* Clear stopwatch interrupt */
    user_requests &= (~ MCF51XX_RTC_RTCISR_SW);           
    
    /* Restore stopwatch interrupt state */
    user_enables |= enables;
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


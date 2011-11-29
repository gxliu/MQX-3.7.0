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
* $FileName: adt_lwtimer.c$
* $Version : 3.6.7.0$
* $Date    : Sep-8-2010$
*
* Comments:
*
*   This file contains the ADC driver CPU specific functions
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include <fio_prv.h>
#include "io.h"
#include "adc.h"
#include "adc_prv.h"
#include "adc_conf.h"
#include <lwtimer.h>


/* State values for timer */
static struct 
{
    _mqx_uint time, wait, last;
    LWTIMER_STRUCT_PTR timer;
    LWTIMER_PERIOD_STRUCT tm_que;
    ADC_DRIVER_BUNDLE_PTR adc_d_bundle;
    uint_32  running_mask;
} adt_internal = { 0 };

/* Declarations of internal static functions */
static void adt_hw_tick(pointer data_ptr);
static void _adt_scheduler(_mqx_uint time);

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_ioctl
* Returned Value   : _mqx_int
* Comments         :
*    Returns result of ioctl operation.
*
*END*********************************************************************/
_mqx_int _adt_hw_ioctl(MQX_FILE_PTR f, _mqx_uint cmd, pointer param_ptr)
{
    return IO_ERROR_INVALID_IOCTL_CMD;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_install
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific initialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adt_hw_install(char_ptr driver_name, ADC_DRIVER_BUNDLE_PTR adc_driver_bundle, pointer p)
{
    adt_internal.adc_d_bundle = adc_driver_bundle; /* store driver bundle struct pointer locally */
    return IO_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_init
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific initialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adt_hw_init(MQX_FILE_PTR f, ADT_PTR adt)
{ /* Body */
    if (_lwtimer_create_periodic_queue(&adt_internal.tm_que, 1, 0) != MQX_OK)
        return ADC_ERROR_LWTIMER;
    
    adt_internal.timer = (LWTIMER_STRUCT_PTR)_mem_alloc(sizeof(LWTIMER_STRUCT));
    if (!adt_internal.timer)
        return ADC_ERROR_ALLOC;

    return ADC_OK;
} /* Endbody */

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_deinit
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific deinitialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adt_hw_deinit(MQX_FILE_PTR f, ADT_PTR adt)
{
    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_channel_init
* Returned Value   : int_32
* Comments         :
*    Returns result of HW channel initialization
*
*END*********************************************************************/
_mqx_int _adt_hw_channel_init(MQX_FILE_PTR f, ADT_CHANNEL_PTR adt_ch)
{
    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_channel_deinit
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific deinitialization for ADC channel
*
*END*********************************************************************/
_mqx_int _adt_hw_channel_deinit(MQX_FILE_PTR f, ADT_CHANNEL_PTR adt_ch)
{
    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_set_wait
* Returned Value   : void
* Comments         : sets the timer to elapse (to call dispatcher) in 'time'
*
*END**********************************************************************/
void _adt_hw_set_wait(uint_32 time)
{
    adt_internal.wait = (time * _time_get_ticks_per_sec()) / 1000000;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_get_time
* Returned Value   : uint_32 - actual absolute time
* Comments         : 
*
*END**********************************************************************/
uint_32 _adt_hw_get_time()
{
    return adt_internal.time * (1000000 / _time_get_ticks_per_sec());
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_run
* Returned Value   : void
* Comments         : starts timer
*
*END*********************************************************************/
_mqx_int _adt_hw_run()
{
    return _lwtimer_add_timer_to_queue(&adt_internal.tm_que, adt_internal.timer, 0, adt_hw_tick, (pointer)&adt_internal.time);
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_stop
* Returned Value   : void
* Comments         : stops timer
*
*END*********************************************************************/
_mqx_int _adt_hw_stop()
{
    return _lwtimer_cancel_timer(adt_internal.timer);
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_tick
* Returned Value   : void
* Comments         : handles one tick from timer
*
*END*********************************************************************/
static void adt_hw_tick(pointer data_ptr)
{
    adt_internal.time++;
    
    if (adt_internal.last + adt_internal.wait <= adt_internal.time) {
        adt_internal.last = adt_internal.time;
        _adt_scheduler(adt_internal.time * (1000000 / _time_get_ticks_per_sec()));
    }
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_scheduler
* Returned Value   : 
* Comments         : Schedules next ADC conversion and informs low-level
*                    driver about that time. Low-level driver must call
*                    this scheduler in that time.
*                    This function can run in interrupt (depends on
                     SW timer implementation)
*END*********************************************************************/
static void _adt_scheduler(_mqx_uint time)
{ /* gets actual time as parameter */
    ADT_CHANNEL_PTR *adt_ch = adt_internal.adc_d_bundle->adt_ch;
    ADC_CHANNEL_PTR *adc_ch = adt_internal.adc_d_bundle->adc_ch;
    _mqx_int i;
    _mqx_uint wait;
    _mqx_int rem;

    if (adt_internal.running_mask) { /* if there is any channel in the mask for measurement */
        _adc_hw_measure(adt_internal.running_mask); /* measure channels */

        for (i = 0; i < ADC_MAX_CHANNELS; i++) { /* update time of last measurement in channels */
            if (!adt_ch[i] || !(adt_internal.running_mask & (1 << adc_ch[i]->g.source)))
                continue;
            
            adt_ch[i]->g.time = time;
        }
    }
    
    /* look for closest AD conversion */
    for (i = 0, wait = -1, adt_internal.running_mask = 0; i < ADC_MAX_CHANNELS; i++) {
        if (adt_ch[i] && adt_ch[i]->g.runtime_flags & ADC_CHANNEL_RUNNING) {
            /* compute remaining time to next measurement:
            ** elapsed time from last measurement: time - adc_ch[i]->time
            ** remaining time to next measurement: adc_ch[i]->period - elapsed
            */
            rem = adt_ch[i]->g.period - (time - adt_ch[i]->g.time);
        
            if (rem < 0)
                rem = 0;
        
            if (rem < wait) {
                wait = rem;
                adt_internal.running_mask = (1 << adc_ch[i]->g.source);
            }
            else if (rem == wait) {
                adt_internal.running_mask |= (1 << adc_ch[i]->g.source);
            }
        }
    }
    
    /* test if any conversion should be performed next time */
    if (adt_internal.running_mask) {
        if (!adt_internal.adc_d_bundle->adt->g.run) {
            _adt_hw_run();
            adt_internal.adc_d_bundle->adt->g.run = 1;
        }
    }
    else {
        _adt_hw_stop();
        adt_internal.adc_d_bundle->adt->g.run = 0;
    }

    /* inform low level driver that next dispatch call should be done in 'wait' time */
    _adt_hw_set_wait(wait);
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_trigger
* Returned Value   : IO_OK
* Comments         : Starts channel measurement or more channels defined
*                    by trigger mask
*
*END*********************************************************************/
_mqx_int _adt_trigger(MQX_FILE_PTR f, ADT_CHANNEL_GENERIC_PTR channel, ADT_TRIGGER_MASK mask)
{
    ADT_CHANNEL_PTR *adt_ch = adt_internal.adc_d_bundle->adt_ch;
    _mqx_int i;
    _mqx_uint time;

    _int_disable();
    time = _adt_hw_get_time();
    
    if (channel) {
        channel->time = time + channel->offset;
        channel->samples = channel->samples_preset;
        channel->runtime_flags |= ADC_CHANNEL_RUNNING | ADC_CHANNEL_RESUMED;
    }
    else {
        for (i = 0; i < ADC_MAX_CHANNELS; i++) {
            if (adt_ch[i] && (adt_ch[i]->g.trigger & mask)) {
                adt_ch[i]->g.time = time + adt_ch[i]->g.offset;
                /* period was subtracted because next scheduling will add it */
                adt_ch[i]->g.samples = adt_ch[i]->g.samples_preset;
                adt_ch[i]->g.runtime_flags |= ADC_CHANNEL_RUNNING | ADC_CHANNEL_RESUMED;
            }
        }
    }
    
    adt_internal.running_mask = 0;
    _adt_scheduler(time);

    _int_enable();
    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_pause
* Returned Value   : IO_OK
* Comments         : Pauses measurement of single channel, or more channels
*                    defined by trigger mask
*
*END*********************************************************************/
_mqx_int _adt_pause(MQX_FILE_PTR f, ADT_CHANNEL_GENERIC_PTR channel, ADT_TRIGGER_MASK mask) {
    ADT_CHANNEL_PTR *adt_ch = adt_internal.adc_d_bundle->adt_ch;
    _mqx_int i;
    _mqx_uint time;

    _int_disable();

    if (channel) {
        channel->runtime_flags &= ~ADC_CHANNEL_RESUMED;
    }
    else {
        for (i = 0; i < ADC_MAX_CHANNELS; i++) {
            if (adt_ch[i] && (adt_ch[i]->g.trigger & mask)) {
                adt_ch[i]->g.runtime_flags &= ~ADC_CHANNEL_RESUMED;
            }
        }
    }

    _int_enable();
    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_resume
* Returned Value   : IO_OK
* Comments         : Resumes measurement of single paused channel, or more
*                    channels defined by trigger mask
*
*END*********************************************************************/
_mqx_int _adt_resume(MQX_FILE_PTR f, ADT_CHANNEL_GENERIC_PTR channel, ADT_TRIGGER_MASK mask)
{
    ADT_CHANNEL_PTR *adt_ch = adt_internal.adc_d_bundle->adt_ch;
    _mqx_int i;

    _int_disable();

    if (channel) {
        channel->runtime_flags |= ADC_CHANNEL_RESUMED;
    }
    else {
        for (i = 0; i < ADC_MAX_CHANNELS; i++) {
            if (adt_ch[i] && (adt_ch[i]->g.trigger & mask)) {
                adt_ch[i]->g.runtime_flags |= ADC_CHANNEL_RESUMED;
            }
        }
    }

    _int_enable();
    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_stop
* Returned Value   : IO_OK
* Comments         : Stops (resets) measurement of single channel, or more
*                    channels defined by trigger mask
*
*END*********************************************************************/
_mqx_int _adt_stop(MQX_FILE_PTR f, ADT_CHANNEL_GENERIC_PTR channel, ADT_TRIGGER_MASK mask)
{
    ADT_CHANNEL_PTR *adt_ch = adt_internal.adc_d_bundle->adt_ch;
    _mqx_int i;
    _mqx_uint time;

    _int_disable();
    time = _adt_hw_get_time();
        
    if (channel) {
        channel->runtime_flags &= ~ADC_CHANNEL_RUNNING;
    }
    else {
        for (i = 0; i < ADC_MAX_CHANNELS; i++) {
            if (adt_ch[i] && (adt_ch[i]->g.trigger & mask)) {
                    adt_ch[i]->g.runtime_flags &= ~ADC_CHANNEL_RUNNING;
            }
        }
    }
    
    adt_internal.running_mask = 0;
    _adt_scheduler(time);

    _int_enable();
    return ADC_OK;
}

/* EOF */

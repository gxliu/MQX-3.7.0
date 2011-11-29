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
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
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

#if BSPCFG_ENABLE_ADC

static LWTIMER_PERIOD_STRUCT tm_que;
static _mqx_uint g_time = 0, g_wait = 0, g_last = 0;
static LWTIMER_STRUCT_PTR timer;

/* Declarations of internal static functions */
static void _adt_hw_tick(pointer data_ptr);

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_install
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific initialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adt_hw_install(char_ptr, ADC_DRIVER_BUNDLE_PTR, pointer);
{
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
_mqx_int _adt_hw_init(ADT_PTR)
{ /* Body */
    if (_lwtimer_create_periodic_queue(&tm_que, 1, 0) != MQX_OK)
        return IO_ERROR;
    
    timer = (LWTIMER_STRUCT_PTR)_mem_alloc(sizeof(LWTIMER_STRUCT));
    if (!timer)
        return IO_ERROR;

    return IO_OK;
} /* Endbody */

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_deinit
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific deinitialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adt_hw_deinit(ADT_PTR) {
    return IO_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_channel_init
* Returned Value   : int_32
* Comments         :
*    Returns result of HW channel initialization
*
*END*********************************************************************/
_mqx_int _adt_hw_channel_init(ADT_CHANNEL_PTR)
{
    return IO_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_channel_deinit
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific deinitialization for ADC channel
*
*END*********************************************************************/
_mqx_int _adt_hw_channel_deinit(ADT_CHANNEL_PTR) {
    return IO_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_set_wait
* Returned Value   : void
* Comments         : sets the timer to elapse (to call dispatcher) in 'time'
*
*END**********************************************************************/
void _adt_hw_set_wait(uint_32 time) {
    g_wait = (time * _time_get_ticks_per_sec()) / 1000000;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_get_time
* Returned Value   : uint_32 - actual absolute time
* Comments         : 
*
*END**********************************************************************/
uint_32 _adt_hw_get_time() {
    return g_time * (1000000 / _time_get_ticks_per_sec());
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_run
* Returned Value   : void
* Comments         : starts timer
*
*END*********************************************************************/
_mqx_int _adt_hw_run() {
    return _lwtimer_add_timer_to_queue(&tm_que, timer, 0, _adt_hw_tick, (pointer)&g_time);
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_stop
* Returned Value   : void
* Comments         : stops timer
*
*END*********************************************************************/
_mqx_int _adt_hw_stop() {
    return _lwtimer_cancel_timer(timer);
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adt_hw_tick
* Returned Value   : void
* Comments         : handles one tick from timer
*
*END*********************************************************************/
static void _adt_hw_tick(pointer data_ptr) {
    g_time++;
    
    if (g_last + g_wait <= g_time) {
        g_last = g_time;
        _adt_g_scheduler(g_time * (1000000 / _time_get_ticks_per_sec()));
    }
}

#endif // BSPCFG_ENABLE_ADC
/* EOF */

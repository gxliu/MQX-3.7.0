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
* $FileName: adc_mcf51mm_prv.h$
* $Version : 3.6.3.0$
* $Date    : Aug-24-2010$
*
* Comments:
*
*   CPU specific ADC driver header file
*
*END************************************************************************/
#ifndef __adc_mcf51xx_prv_h__
#define __adc_mcf51xx_prv_h__

#include "adc.h"
#include "adc_prv.h"
#include "adc_conf.h"

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_MAX_FREQUENCY 5000000 /* 5 MHz for ADC clock source is maximum */

#ifndef ADC_MAX_SW_CHANNELS
    #define ADC_MAX_CHANNELS ADC_MAX_HW_CHANNELS
#else
    #if (ADC_MAX_HW_CHANNELS > ADC_MAX_SW_CHANNELS)
        #define ADC_MAX_CHANNELS ADC_MAX_SW_CHANNELS
    #else
        #define ADC_MAX_CHANNELS ADC_MAX_HW_CHANNELS
    #endif
#endif

/* Structure holding ADC driver settings */
typedef struct adc {
    ADC_GENERIC           g; /* this must be included as the first member at the beginning of structure */
    /* below, CPU specific members are used */
    pointer old_isr;
    pointer old_isr_data;
} ADC, _PTR_ ADC_PTR;

/* Structure holding ADC driver settings */
typedef struct adt {
    ADT_GENERIC           g; /* this must be included as the first item at the beginning of structure */
} ADT, _PTR_ ADT_PTR;

/* Structure holding ADC driver channel settings */
typedef struct adc_channel {
    ADC_CHANNEL_GENERIC   g; /* this must be included as the first member at the beginning of structure */
    /* below, CPU specific members are used */
    struct adc_channel_bundle *b;
} ADC_CHANNEL, _PTR_ ADC_CHANNEL_PTR;

/* Structure holding ADT driver channel settings, must be declared */
typedef struct adt_channel {
   ADT_CHANNEL_GENERIC   g; /* this must be included as the first member at the beginning of structure */
   /* below, CPU specific members are used */
   struct adc_channel_bundle *b;
   /* All ADT channels use one common HW trigger settings. Only delay is per - channel set */
} ADT_CHANNEL, _PTR_ ADT_CHANNEL_PTR;

/* ADC converter + trigger channel bundle structure */
typedef struct adc_channel_bundle {
    ADC_CHANNEL_PTR  adc_ch;
    ADT_CHANNEL_PTR  adt_ch;
    /* below, CPU specific members are used */
    _mqx_int         ch_num; /* this channel is A or B (0 or 1) ? */
    _mqx_int         periods_preset; /* how many dummy PDB periods must pass to readout result data */
    _mqx_int         periods;        /* how many dummy PDB periods elapsed */
    boolean          waste_channel;  /* workaround to waste all channel results */
} ADC_CHANNEL_BUNDLE, _PTR_ ADC_CHANNEL_BUNDLE_PTR;

/* ADC converter + trigger driver bundle structure */
typedef struct adc_driver_bundle {
    ADC_PTR          adc;                      /* ADC driver status information (generic + HW specific) */
    ADT_PTR          adt;                      /* ADT driver status information (generic + HW specific) */
    ADC_CHANNEL_PTR  adc_ch[ADC_MAX_CHANNELS];
    ADT_CHANNEL_PTR  adt_ch[ADC_MAX_CHANNELS];
    uchar_ptr        adc_name[ADC_MAX_CHANNELS]; /* filename of channel(s) */
    /* below, CPU specific members are used */
    MCF51MM_ADC_INIT_STRUCT_PTR init;
} ADC_DRIVER_BUNDLE, _PTR_ ADC_DRIVER_BUNDLE_PTR;

typedef struct adc_bundle {
/* Following must be defined, because following values should be written in one uninterruptable block of code, so we cannot
** split IOCTL command to ADC and ADT. There is posibility that ADC module disables interrupts and ADT module enables interrupt,
** but that's not the right solution.
*/
    uint_32 late_process; /* This is mask of late processing channel, constrained to 32 channels. */
} ADC_BUNDLE, ADC_BUNDLE_PTR;

_mqx_int _adc_hw_install(char_ptr, ADC_DRIVER_BUNDLE_PTR, pointer);
_mqx_int _adt_hw_install(char_ptr, ADC_DRIVER_BUNDLE_PTR, pointer);
_mqx_int _adc_hw_init(MQX_FILE_PTR, ADC_PTR);
_mqx_int _adt_hw_init(MQX_FILE_PTR, ADT_PTR);
_mqx_int _adc_hw_deinit(MQX_FILE_PTR, ADC_PTR);
_mqx_int _adt_hw_deinit(MQX_FILE_PTR, ADT_PTR);
_mqx_int _adc_hw_channel_init(MQX_FILE_PTR, ADC_CHANNEL_PTR);
_mqx_int _adt_hw_channel_init(MQX_FILE_PTR, ADT_CHANNEL_PTR);
_mqx_int _adc_hw_channel_deinit(MQX_FILE_PTR, ADC_CHANNEL_PTR);
_mqx_int _adt_hw_channel_deinit(MQX_FILE_PTR, ADT_CHANNEL_PTR);
_mqx_int _adc_hw_ioctl(MQX_FILE_PTR, _mqx_uint, pointer);
_mqx_int _adt_hw_ioctl(MQX_FILE_PTR, _mqx_uint, pointer);

void _adc_hw_measure(ADC_HW_CHANNEL_MASK);
_mqx_int _adt_hw_run();
_mqx_int _adt_hw_stop();
void _adt_hw_set_wait(uint_32);
uint_32 _adt_hw_get_time();

void adc_process_all_data();

#ifdef __cplusplus
}
#endif

#endif

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
* $FileName: Security_IO.c$
* $Version : 3.7.17.1$
* $Date    : Apr-4-2011$
*
* Comments:
*
*   
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <string.h>
#include "security_private.h"

#define DOOR_STATE      BSP_BUTTON1
#define WINDOW_STATE    BSP_BUTTON2

#define LED_1   BSP_LED1
#define LED_2   BSP_LED2
#define LED_3   BSP_LED3
#define LED_4   BSP_LED4

#if defined BSP_ADC_CH_ACCEL_X && defined BSP_ADC_CH_ACCEL_Y && defined BSP_ADC_CH_ACCEL_Z
    #define ADC_CH_COUNT    4
#else
    #define ADC_CH_COUNT    1
#endif //defined BSP_ADC_CH_ACCEL_X && defined BSP_ADC_CH_ACCEL_Y && defined BSP_ADC_CH_ACCEL_Z

const char_ptr SEC_OutputName[] = { "LED1","LED2","Entry Open","Movement Detected" };

boolean SEC_OutputState[SEC_MAX_OUTPUTS] ={0};

static MQX_FILE_PTR input_port=NULL, output_port=NULL;
  
boolean SEC_InitializeIO(void) 
{
    const uint_32 output_set[] = {
        LED_1 | GPIO_PIN_STATUS_0,
        LED_2 | GPIO_PIN_STATUS_0,
        LED_3 | GPIO_PIN_STATUS_0,
        LED_4 | GPIO_PIN_STATUS_0,
        GPIO_LIST_END
    };

    const uint_32 input_set[] = {
        DOOR_STATE,
        WINDOW_STATE,
        GPIO_LIST_END
    };

    /* Open and set port TC as output to drive LEDs (LED10 - LED13) */
    output_port = fopen("gpio:write", (char_ptr) &output_set);

    /* Open and set port DD as input to read value from switches */
    input_port = fopen("gpio:read", (char_ptr) &input_set);
    
    return (input_port != NULL) && (output_port != NULL);
}
     
      
void SEC_ResetOutputs(void) 
{
   SEC_Output_t i;
   
   for (i=SEC_LED1_OUTPUT;i<SEC_MAX_OUTPUTS;i++) {
      SEC_SetOutput(i,FALSE);
   }
}

  
void SEC_SetOutput(SEC_Output_t signal,boolean state) 
{
   uint_32  set_value=0;
   static const uint_32 led1[] = {
    LED_1,
    GPIO_LIST_END
   };
   static const uint_32 led2[] = {
    LED_2,
    GPIO_LIST_END
   };
   static const uint_32 led3[] = {
    LED_3,
    GPIO_LIST_END
   };
   static const uint_32 led4[] = {
    LED_4,
    GPIO_LIST_END
   };

    
   if (SEC_OutputState[signal] != state) {
      SEC_OutputState[signal] = state;

      if (output_port) {
         set_value = (state) ? GPIO_IOCTL_WRITE_LOG1 : GPIO_IOCTL_WRITE_LOG0;
         switch (signal) {
             case SEC_LED1_OUTPUT:
                ioctl(output_port, set_value, (pointer) &led1);
                break;
             case SEC_LED2_OUTPUT:
                ioctl(output_port, set_value, (pointer) &led2);
                break;
             case SEC_LED3_OUTPUT:
                ioctl(output_port, set_value, (pointer) &led3);
                break;
             case SEC_OPEN_OUTPUT:
                ioctl(output_port, set_value, (pointer) &led4);
                break;
         }
      }
   }
}

 
boolean SEC_GetOutput(SEC_Output_t signal)
{
   return SEC_OutputState[signal];
} 

char_ptr SEC_GetOutputName(SEC_Output_t signal)
{
   return SEC_OutputName[signal];
} 
 
   
boolean SEC_GetInput(SEC_Input_t signal)
{
   boolean  value=FALSE;
   
   static uint_32 data[] = {
        DOOR_STATE,
        WINDOW_STATE,
        GPIO_LIST_END
    };

   if (input_port) {
      ioctl(input_port, GPIO_IOCTL_READ,  &data);
   }

   switch (signal) {
      case SEC_DOOR_INPUT:
         value = (data[0] & GPIO_PIN_STATUS)==0;
         break;
 
      case SEC_WINDOW_INPUT:
         value = (data[1] & GPIO_PIN_STATUS)==0;
         break;
   }

  return value;
}

const ADC_INIT_STRUCT adc_init = {
    ADC_RESOLUTION_DEFAULT,     /* resolution */
};

const ADC_INIT_CHANNEL_STRUCT adc_ch_param[ADC_CH_COUNT] = {
    {
        BSP_ADC_CH_POT,
        ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_NOW,
        10,            /* number of samples in one run sequence */
        0,             /* time offset from trigger point in ns */
        50000,     /* period in us (50ms) */
        0x10000,       /* scale range of result (not used now) */
        1,          /* circular buffer size (sample count) */
        MY_TRIGGER  /* logical trigger ID that starts this ADC channel */
    },
#if defined BSP_ADC_CH_ACCEL_X && defined BSP_ADC_CH_ACCEL_Y && defined BSP_ADC_CH_ACCEL_Z
    {
        BSP_ADC_CH_ACCEL_X,
        ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_NOW,
        10,            /* number of samples in one run sequence */
        0,             /* time offset from trigger point in ns */
        50000,     /* period in us (50ms) */
        0x10000,       /* scale range of result (not used now) */
        1,          /* circular buffer size (sample count) */
        MY_TRIGGER  /* logical trigger ID that starts this ADC channel */
    },
    {
        BSP_ADC_CH_ACCEL_Y,
        ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_NOW,
        10,            /* number of samples in one run sequence */
        0,             /* time offset from trigger point in ns */
        50000,     /* period in us (50ms) */
        0x10000,       /* scale range of result (not used now) */
        1,          /* circular buffer size (sample count) */
        MY_TRIGGER  /* logical trigger ID that starts this ADC channel */
    },
    {
        BSP_ADC_CH_ACCEL_Z,
        ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_NOW,
        10,            /* number of samples in one run sequence */
        0,             /* time offset from trigger point in ns */
        50000,     /* period in us (50ms) */
        0x10000,       /* scale range of result (not used now) */
        1,          /* circular buffer size (sample count) */
        MY_TRIGGER  /* logical trigger ID that starts this ADC channel */
    }
#endif // defined BSP_ADC_CH_ACCEL_X && defined BSP_ADC_CH_ACCEL_Y && defined BSP_ADC_CH_ACCEL_Z
};

static MQX_FILE_PTR fd_adc, fd_ch[ADC_CH_COUNT];

/*
 *  Setup ADC module to read in accelerometer and potentiometer values
 */   
void SEC_InitializeADC(void) {
    _mqx_int i;
    char dev_name[10];
    
    fd_adc = fopen(MY_ADC, (const char*)&adc_init);
    if (NULL == fd_adc) {    
        printf("ADC device open failed\n");
        _task_block();
    }
    
    for (i = 0; i < ADC_CH_COUNT; i++) {
        sprintf(dev_name, "%s%d", MY_ADC, i);
        fd_ch[i] = fopen(dev_name, (const char*)&adc_ch_param[i]);
        if (NULL == fd_ch[i]) {    
            printf("%s%d channel open failed\n", MY_ADC, i);
            _task_block();
        }
    }
    
    _time_delay (100);

#if ADC_CH_COUNT > 1
    for (i = 0; i < 3; i++) {
      SEC_Params.last[i] = ReadADC(ADC_ACCX + i);
    }
    
    SEC_Params.flat=SEC_Params.last[ACCY];
#endif

    _time_delay (200);
}

/*
 *  Read in ADC value on the channel given
 */
_mqx_int ReadADC(_mqx_int channel) {
    ADC_RESULT_STRUCT adc_res;
    _mqx_int read_bytes;

    if (channel < ADC_CH_COUNT) {
        read_bytes = read(fd_ch[channel], &adc_res, sizeof(adc_res));
        if (read_bytes == 0)
            adc_res.result = 0; 
    }
    else
        adc_res.result = 0; 
    
    return (_mqx_int) adc_res.result;
}

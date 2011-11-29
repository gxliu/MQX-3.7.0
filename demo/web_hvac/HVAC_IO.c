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
* $FileName: HVAC_IO.c$
* $Version : 3.7.20.0$
* $Date    : Feb-22-2011$
*
* Comments:
*
*   
*
*END************************************************************************/


#include "hvac.h"
#include "hvac_public.h"
#include "hvac_private.h"
#include <io_gpio.h>

#if defined(BSP_BUTTON1) && defined(BSP_BUTTON2)
   #define TEMP_PLUS  BSP_BUTTON1
   #define TEMP_MINUS BSP_BUTTON2
   #define BUTTONS   1
#else 
   #warning "Buttons are not available in this BSP"
#endif   

#if defined(BSP_BUTTON3)
#define FAN_ON_OFF BSP_BUTTON3
#endif

#define LED_1 BSP_LED1
#define LED_2 BSP_LED2
#define LED_3 BSP_LED3
#define LED_4 BSP_LED4

const char_ptr HVAC_OutputName[] = { "Fan", "Furnace", "A/C", "HeartBeat" };

boolean HVAC_OutputState[HVAC_MAX_OUTPUTS] ={0};


static MQX_FILE_PTR input_port=NULL, output_port=NULL;


boolean HVAC_InitializeIO(void) 
{
    const uint_32 output_set[] = {
        LED_1 | GPIO_PIN_STATUS_0,
        LED_2 | GPIO_PIN_STATUS_0,
        LED_3 | GPIO_PIN_STATUS_0,
        LED_4 | GPIO_PIN_STATUS_0,
        GPIO_LIST_END
    };

#if BUTTONS
    const uint_32 input_set[] = {
        TEMP_PLUS,
        TEMP_MINUS,
#if defined(FAN_ON_OFF)
        FAN_ON_OFF,
#endif
        GPIO_LIST_END
    };
#endif

    /* Open and set port TC as output to drive LEDs (LED10 - LED13) */
    output_port = fopen("gpio:write", (char_ptr) &output_set);

#if BUTTONS
    /* Open and set port DD as input to read value from switches */
    input_port = fopen("gpio:read", (char_ptr) &input_set);
#endif    
    if (output_port)
        ioctl(output_port, GPIO_IOCTL_WRITE_LOG0, NULL);    
#if BUTTONS
    return (input_port!=NULL) && (output_port!=NULL);
#else
   return (output_port!=NULL);
#endif   
       
}


void HVAC_ResetOutputs(void) 
{
   uint_32 i;
   
   for (i=0;i<HVAC_MAX_OUTPUTS;i++) {
      HVAC_SetOutput((HVAC_Output_t)i,FALSE);
   }
}


void HVAC_SetOutput(HVAC_Output_t signal,boolean state) 
{
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
    
   if (HVAC_OutputState[signal] != state) {
      HVAC_OutputState[signal] = state;

      if (output_port) {
         switch (signal) {
             case HVAC_FAN_OUTPUT:
                ioctl(output_port, (state) ? GPIO_IOCTL_WRITE_LOG1 : GPIO_IOCTL_WRITE_LOG0, (pointer) &led1);
                break;
             case HVAC_HEAT_OUTPUT:
                ioctl(output_port, (state) ? GPIO_IOCTL_WRITE_LOG1 : GPIO_IOCTL_WRITE_LOG0, (pointer) &led2);
                break;
             case HVAC_COOL_OUTPUT:
                ioctl(output_port, (state) ? GPIO_IOCTL_WRITE_LOG1 : GPIO_IOCTL_WRITE_LOG0, (pointer) &led3);
                break;
             case HVAC_ALIVE_OUTPUT:
                ioctl(output_port, (state) ? GPIO_IOCTL_WRITE_LOG1 : GPIO_IOCTL_WRITE_LOG0, (pointer) &led4);
                break;
         }
      }
   }
}


boolean HVAC_GetOutput(HVAC_Output_t signal)
{
   return HVAC_OutputState[signal];
} 


char_ptr HVAC_GetOutputName(HVAC_Output_t signal)
{
   return HVAC_OutputName[signal];
} 


boolean HVAC_GetInput(HVAC_Input_t signal)
{
   boolean  value=FALSE;
#if BUTTONS
   static uint_32 data[] = {
        TEMP_PLUS,
        TEMP_MINUS,
#if defined(FAN_ON_OFF)
        FAN_ON_OFF,
#endif
        GPIO_LIST_END
    };

   if (input_port) {
      ioctl(input_port, GPIO_IOCTL_READ,  &data);
   }

   switch (signal) {
      case HVAC_TEMP_UP_INPUT:
         value = (data[0] & GPIO_PIN_STATUS)==0;
         break;
 
      case HVAC_TEMP_DOWN_INPUT:
         value = (data[1] & GPIO_PIN_STATUS)==0;
         break;

#if defined(FAN_ON_OFF)
      case HVAC_FAN_ON_INPUT:
         value = (data[2] & GPIO_PIN_STATUS)==0;
         break;
#endif
   }
#endif
   return value;
}



static uint_32 AmbientTemperature = 200; // 20.0 degrees celsius, 68.0 degrees fahrenheit
static TIME_STRUCT LastUpdate  = {0,0};

uint_32 HVAC_GetAmbientTemperature(void)
{
   return AmbientTemperature;
}

void HVAC_ReadAmbientTemperature(void)
{
   TIME_STRUCT time;
   
   _time_get(&time);
   if (time.SECONDS>=(LastUpdate.SECONDS+HVAC_TEMP_UPDATE_RATE)) {
      LastUpdate=time;
      if (HVAC_GetOutput(HVAC_HEAT_OUTPUT)) {
         AmbientTemperature += HVAC_TEMP_UPD_DELTA;
      } else if (HVAC_GetOutput(HVAC_COOL_OUTPUT)) {
         AmbientTemperature -= HVAC_TEMP_UPD_DELTA;
      }
   }
}

#if ENABLE_ADC

static MQX_FILE_PTR fd_adc, fd_ch = NULL;

const ADC_INIT_STRUCT adc_init = {
    ADC_RESOLUTION_DEFAULT,     /* resolution */
};

const ADC_INIT_CHANNEL_STRUCT adc_ch_param = {
    ADC_CH_HEART,
    ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_NOW,
    10,            /* number of samples in one run sequence */
    0,             /* time offset from trigger point in ns */
    50000,         /* period in us (50ms) */
    0x10000,       /* scale range of result (not used now) */
    1,             /* circular buffer size (sample count) */
    MY_TRIGGER,    /* logical trigger ID that starts this ADC channel */
    NULL,          /* no lwevent used */
    0              /* lwevent bits */
};

/*
 *  Setup ADC module to read in accelerometer and potentiometer values
 */   
void HVAC_InitializeADC(void) {
    fd_adc = fopen(MY_ADC, (const char*)&adc_init);
    if (NULL == fd_adc) {    
        printf("ADC device open failed\n");
        return;
    }
    
    fd_ch = fopen(MY_ADC"0", (const char*)&adc_ch_param);
    if (fd_ch == NULL) {    
        printf("%s0 channel open failed\n", MY_ADC);
        return;
    }
}

/*
 *  Read in ADC value on the channel given
 */
_mqx_int ReadADC(void) {
    ADC_RESULT_STRUCT val;
    
    if (fd_ch == NULL)
        return 0;
    read(fd_ch, &val, sizeof(val));
    return (_mqx_int) val.result;
}

#endif // ENABLE_ADC

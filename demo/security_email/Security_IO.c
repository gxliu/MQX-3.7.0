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
* $Version : 3.7.11.1$
* $Date    : Apr-1-2011$
*
* Comments:
*
*   
*
*END************************************************************************/

#include "security_public.h"
#include "security_private.h"
#include <bsp.h>
#include <io_gpio.h>
#include <string.h>

#define DOOR_STATE      BSP_BUTTON1
#define WINDOW_STATE    BSP_BUTTON2

#define LED_1   BSP_LED1
#define LED_2   BSP_LED2
#define LED_3   BSP_LED3
#define LED_4   BSP_LED4


const char_ptr SEC_OutputName[] = { "LED1","LED2","Entry Open","Movement Detected" };

boolean SEC_OutputState[SEC_MAX_OUTPUTS] ={0};


static MQX_FILE_PTR input_port=NULL, output_port=NULL;
static void kbi_callback(pointer kbi_param_ptr);


static void kbi_callback(pointer kbi_param_ptr) 
{
    /* Determine if it was SW2 or SW3 that caused interrupt */
    if (SEC_GetInput(SEC_DOOR_INPUT) == OPENED) {
        SEC_Params.Status = SEC_DOOR_OPEN_STATUS;
        SEC_SetOutput(SEC_OPEN_OUTPUT, 1); 
    } 
     
    if (SEC_GetInput(SEC_WINDOW_INPUT) == OPENED) {
        SEC_Params.Status = SEC_WINDOW_OPEN_STATUS;
        SEC_SetOutput(SEC_OPEN_OUTPUT, 1); 
    }  
}

boolean SEC_InitializeIO(void) 
{
    const uint_32 output_set[] = {
        LED_1 | GPIO_PIN_STATUS_0,
        LED_2 | GPIO_PIN_STATUS_0,
        LED_3 | GPIO_PIN_STATUS_0,
        LED_4 | GPIO_PIN_STATUS_0,
        GPIO_LIST_END
    };
    
#ifdef SECEMAIL_TWRMCF51CN_STOP_ENABLED
    const uint_32 input_set[] = {
        DOOR_STATE | GPIO_PIN_IRQ,
        WINDOW_STATE | GPIO_PIN_IRQ_FALLING,
        GPIO_LIST_END
    };
#else    
    const uint_32 input_set[] = {
        DOOR_STATE,
        WINDOW_STATE,
        GPIO_LIST_END
    };
#endif

    /* Open and set port TC as output to drive LEDs (LED10 - LED13) */
    output_port = fopen("gpio:write", (char_ptr) &output_set);

    /* Open and set port DD as input to read value from switches */
    input_port = fopen("gpio:read", (char_ptr) &input_set);

    ioctl(input_port, GPIO_IOCTL_SET_IRQ_FUNCTION, (pointer) &kbi_callback);
    
    return (input_port!=NULL) && (output_port!=NULL);
}
     
      
void SEC_ResetOutputs(void) 
{
   uint_32 i;
   
   for (i=0;i<SEC_MAX_OUTPUTS;i++) {
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
             case SEC_OPEN_OUTPUT:
                ioctl(output_port, set_value, (pointer) &led3);
                break;
             case SEC_MOVEMENT_OUTPUT:
                ioctl(output_port, set_value, (pointer) &led4);
                break;
         }
      }
   }
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
 

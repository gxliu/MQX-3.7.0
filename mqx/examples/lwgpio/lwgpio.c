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
* $FileName: lwgpio.c$
* $Version : 3.7.2.0$
* $Date    : Mar-8-2011$
*
* Comments:
*
*   This file contains the source for the lwgpio example program.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>

/* Function prototypes */
void main_task(uint_32);
void int_service_routine(void *);

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
    /* Task Index, Function, Stack, Priority,   Name,          Attributes, Param, Time Slice */ 
    { 1,          main_task,  1500,        8, "main", MQX_AUTO_START_TASK,     0,          0 },
    { 0 }
};

volatile uint_32 int_counter;

void int_service_routine(void *pin) 
{
    int_counter++;
    lwgpio_int_clear_flag((LWGPIO_STRUCT_PTR) pin);
}

/*TASK*-----------------------------------------------------
* 
* Task Name    : main_task
* Comments     :
* This task executes 3 steps
* 1) set BSP_LED1 on and off if BSP_LED1 available
* 2) configure BSP_BUTTON1 for interrupt if possible and wait
*    for 5 interrupt calls
* 3) Drives BSP_LED1 according read from BSP_BUTTON1 or
*    drives BSP_LED1 automatically if BSP_BUTTON1 not available
*END*-----------------------------------------------------*/

void main_task 
   (
      uint_32 initial_data
   )
{
    /* Structures holding information about specific pin */
    LWGPIO_STRUCT led1, btn1;

#if defined BSP_LED1
/************************************************
 Open BSP_LED1 as output, drive the output level.
************************************************/   
   /* open file containing pin1 set of pins/signals */
    if (!lwgpio_init(&led1, BSP_LED1, LWGPIO_DIR_OUTPUT, LWGPIO_VALUE_NOCHANGE))
    {
        printf("Initializing LED1 GPIO as output failed.\n");
        _mqx_exit(-1);
    }
    lwgpio_set_functionality(&led1, BSP_LED1_MUX_GPIO);

    /* write logical 1 to all signals in the file (fast) */
    lwgpio_set_value(&led1, LWGPIO_VALUE_HIGH);
    lwgpio_set_value(&led1, LWGPIO_VALUE_LOW);
#endif //BSP_LED1

#if defined BSP_BUTTON1
/************************************************
 Open BSP_BTN1 as input, initialize interrupt on
 it and set interrupt handler. Wait until five
 calls of handler were called.
 ***********************************************/  
    /* opening pins/signals for input */
    if (!lwgpio_init(&btn1, BSP_BUTTON1, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE))
    {
        printf("Initializing button GPIO as input failed.\n");
        _mqx_exit(-1);
    }

#ifdef BSP_BUTTON1_MUX_IRQ
    /* Some peripherals require to setup MUX to IRQ functionality */
    lwgpio_set_functionality(&btn1, BSP_BUTTON1_MUX_IRQ);
#endif

    if (!lwgpio_int_init(&btn1, LWGPIO_INT_MODE_FALLING))
    {
        printf("Initializing button GPIO for interrupt failed.\n");
    }
    else
    {
        printf("Button configured for interrupt, waiting 5 interrupt callbacks.\n");

        /* install gpio interrupt service routine */
        _int_install_isr(lwgpio_int_get_vector(&btn1), int_service_routine, (void *) &btn1);
        _bsp_int_init(lwgpio_int_get_vector(&btn1), 3, 0, TRUE);
        lwgpio_int_enable(&btn1, TRUE);

        while (int_counter < 5)
        { /* Wait till 5 button pushes were made */ }

        lwgpio_int_enable(&btn1, FALSE);
    }

#endif //BSP_BUTTON1

#if defined BSP_BUTTON1
/************************************************
 Open BSP_BTN1 as input and read value from it.
 Note that in previous test, the pin was 
 configured as interrupt and that is why it must
 be reconfigured as standard GPIO.
 ***********************************************/  

    /* opening pins/signals for input */
    if (!lwgpio_init(&btn1, BSP_BUTTON1, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE))
    {
        printf("Initializing button GPIO as input failed.\n");
        _mqx_exit(-1);
    }
    lwgpio_set_functionality(&btn1, BSP_LED1_MUX_GPIO);

    /* It is not easy to generalize switch: every board has its own switch names */
    printf("Use SWITCH on board to switch LED on or off\n");
    while (TRUE)
    {
        /* read pin/signal status to pin list */
        if (LWGPIO_VALUE_HIGH == lwgpio_get_value(&btn1))
        {
            printf("LED OFF.\n"); 
#if defined BSP_LED1
            /* clear pin to 0 (fast) */
            lwgpio_set_value(&led1, LWGPIO_VALUE_LOW);
#endif //BSP_LED1
        }
        else 
        {
            printf("LED ON.\n");
#if defined BSP_LED1
            /* set pin to 1 (fast) */
            lwgpio_set_value(&led1, LWGPIO_VALUE_HIGH);
#endif //BSP_LED1
        }
   }

#elif defined BSP_LED1

/************************************************
 In case board does not have BUTTONS, 
 Only blink with LED.
************************************************/    

    /* It is not easy to generalize LED: every board has its own LED names */
    printf("Going to blink with LED\n");
    while (TRUE)
    {
        /* write logical 0 to the pin */
        lwgpio_set_value(&led1, LWGPIO_VALUE_LOW);
        _time_delay(1000);
        /* write logical 1 to the pin */
        lwgpio_set_value(&led1, LWGPIO_VALUE_HIGH);
        _time_delay(1000);
    }
#else //BSP_LED1, BSP_BUTTON1

    printf("Cannot show demo, no BSP_LED1 nor BSP_BUTTON1 defined for board.");

#endif //BSP_LED1, BSP_BUTTON1

}  

/* EOF */

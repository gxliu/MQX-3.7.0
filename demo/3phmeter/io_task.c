/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
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
* $FileName: io_task.c$
* $Version : 3.6.7.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the source for the ADC example program.
*   Two channels are running, one is running in loop, the second one
*   only once.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <string.h>
#include "meter_config.h"
#include "task_template_list.h"

typedef enum  
{
    SW1 = 0,
    SW2,
    SW3,
    SW4,
    SWITCH_LAST
}  eSwitches;

/* local variables */
static MQX_FILE_PTR file_switches;
static MQX_FILE_PTR file_leds;

static GPIO_PIN_STRUCT switches[] = {
    BSP_SW1,
    BSP_SW2,
    BSP_SW3,
    BSP_SW4,
    GPIO_LIST_END
};

static GPIO_PIN_STRUCT leds[] = {
    BSP_LED1 | GPIO_PIN_STATUS_1,
    GPIO_LIST_END
};

static uint_32 timeout;

/* local function prototypes */
static void io_init(void);
static void switch_poll(void);
       
/*TASK******************************************************
** 
** Task Name    : io_task
** Comments     :
**
*END*******************************************************/

void io_task
   (
      uint_32 initial_data
   )
{
    
    puts("*****************************\n");
    puts("IO Task running\n");

    io_init();

    /* Run in 100ms loop to read buttons state  */
    while(1)
    {
    
       /* IO Task is running, wait for timeout */
        _time_delay(100);
    
        switch_poll();
        
        /* blink by LED1 to signalize io_task is running */
        if(timeout == 0) {
            timeout = 1;
            ioctl(file_leds, GPIO_IOCTL_WRITE_LOG1, NULL);
        }
        else {
            timeout = 0;
            ioctl(file_leds, GPIO_IOCTL_WRITE_LOG0, NULL);
        } 
    }
}


/*FUNCTION****************************************************************
** 
** Task Name        : io_init
** Returned Value   : void
** Comments         :
**
*END*********************************************************************/

static void io_init(void)
{
    /* open file containing set of pins/signals for switches */
    if (NULL == (file_switches = fopen("gpio:read", (char_ptr) &switches))) 
    {
        printf("Opening file_switches failed.\n");
        _task_block();
    }

    /* open file containing set of pins/signals for leds */
    if (NULL == (file_leds = fopen("gpio:write", (char_ptr) &leds))) 
    {
        printf("Opening file_leds failed.\n");
        _task_block();
    }
}



/*FUNCTION****************************************************************
** 
** Task Name        : io_init
** Returned Value   : void
** Comments         :
**
*END*********************************************************************/


uint_32 switch_state = 0;

void switch_poll(void)
{
    
    /* Read pin status to switches list */
    if (IO_OK != ioctl(file_switches, GPIO_IOCTL_READ, (char_ptr) &switches))
    {
        _task_block();
    }

    
    /* Test if SW1 was pressed */
    if (((switches[SW1] & GPIO_PIN_STATUS) == 0))   { 
        if ((switch_state & IO_SW1_MASK) == 0)  {
            switch_state |= IO_SW1_MASK;
            _lwevent_set(&meter_shared_event, IO_SW1_MASK);
        }
    }
    else  {
        switch_state &= ~IO_SW1_MASK;
    } 

    /* Test if SW2 was pressed */
    if (((switches[SW2] & GPIO_PIN_STATUS) == 0))   { 
        if ((switch_state & IO_SW2_MASK) == 0)  {
            switch_state |= IO_SW2_MASK;
            /* Set SW2 click mask */
            _lwevent_set(&meter_shared_event, IO_SW2_MASK);
        }
    }
    else  {
        switch_state &= ~IO_SW2_MASK;
    } 

    /* Test if SW3 was pressed */
    if (((switches[SW3] & GPIO_PIN_STATUS) == 0))   { 
        if ((switch_state & IO_SW3_MASK) == 0)  {
            switch_state |= IO_SW3_MASK;
            /* Set SW2 click mask */
            _lwevent_set(&meter_shared_event, IO_SW3_MASK);
        }
    }
    else  {
        switch_state &= ~IO_SW3_MASK;
    } 
 
    /* Test if SW4 was pressed */
    if (((switches[SW4] & GPIO_PIN_STATUS) == 0))   { 
        if ((switch_state & IO_SW4_MASK) == 0)  {
            switch_state |= IO_SW4_MASK;
            /* Set SW2 click mask */
            _lwevent_set(&meter_shared_event, IO_SW4_MASK);
        }
    }
    else  {
        switch_state &= ~IO_SW4_MASK;
    } 
}
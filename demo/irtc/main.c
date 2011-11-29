/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved                       
*
* Copyright (c) 1989-2008 ARC International;
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
* $FileName: main.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the source for the RTC example program.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <main.h>


#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


#if ! BSPCFG_ENABLE_RTCDEV
#error This application requires BSPCFG_ENABLE_RTCDEV defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#if defined(BSP_TWRMCF51CN)
    #define RTC_RTCISR_SW       MCF51XX_RTC_RTCISR_SW
    #define RTC_RTCISR_ALM      MCF51XX_RTC_RTCISR_ALM
    #define RTC_RTCIENR_SW      MCF51XX_RTC_RTCIENR_SW
    #define RTC_RTCIENR_ALM     MCF51XX_RTC_RTCIENR_ALM
#elif defined(BSP_M51EMDEMO)
    #
#elif defined(BSP_M54455EVB)
    #define RTC_RTCISR_SW       MCF54XX_RTC_ISR_SW
    #define RTC_RTCISR_ALM      MCF54XX_RTC_ISR_ALM
    #define RTC_RTCIENR_SW      MCF54XX_RTC_IER_SW
    #define RTC_RTCIENR_ALM     MCF54XX_RTC_IER_ALM
#else
    #define RTC_RTCISR_SW       MCF52XX_RTC_RTCISR_SW
    #define RTC_RTCISR_ALM      MCF52XX_RTC_RTCISR_ALM
    #define RTC_RTCIENR_SW      MCF52XX_RTC_RTCIENR_SW
    #define RTC_RTCIENR_ALM     MCF52XX_RTC_RTCIENR_ALM
#endif


extern void main_task(uint_32);


const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
   /* Task Index,   Function,   Stack,  Priority,   Name,   Attributes,          Param, Time Slice */
    { 10,           main_task,  2000,   8,          "Main", MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};   



/* Macro for detecting button press */
#define SW1_CLICK()   clickButton(0,&memory_sw1)
#define SW2_CLICK()   clickButton(1,&memory_sw2)
#define SW3_CLICK()   clickButton(2,&memory_sw3)
#define SW4_CLICK()   clickButton(3,&memory_sw4)



/*TASK*-----------------------------------------------------
* 
* Task Name    : main_task
* Comments     : 
*      Demo of the IRTC module
*
*END*-----------------------------------------------------*/
void main_task(uint_32 initial_data)
{
  int i;
    RTC_TIME_STRUCT time_rtc;
    TIME_STRUCT     time_mqx;
  VMCF51EM_RTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();

    
  char LCD_buffer[20];  
  DATE_STRUCT date;
 
  /* Display the time on the LCD screen by default */
  char display=TIME;  

  /* Open GPIO */
  if (NULL == (port_file = fopen("gpio:read", (char_ptr) &input_pins )))
  {
    printf("Opening file GPIO with associated pins failed.\n");
    _mqx_exit(-1);
  }

  /* Initialize LCD */
  _lcd_init();
  
  /* Turn on Freescale symbol */
  _lcd_symbol(LCD_FREESCALE, TRUE); 
  
  /* Get the date stored in the RTC registers */
    _rtc_get_time(&time_rtc);
    
    /* If RTC time is set to default date, initialize time */   
  if(time_rtc.year==2112) 
    {   
    /* Set RTC registers to an initial date */
    _rtc_set_time(&initial_rtc);
    }

  /* Set the MQX time to the time defined by the RTC registers */
  _rtc_sync_with_mqx(TRUE);


  /* Clear history log */
  for(i=0;i<MAX_QUEUE;i++) 
  {
    History[i].tamper_type=RTC_TMPR_CLEAR;
  }
  HistoryIndex=0;

  while(1) 
  {  
    /* Get the current time */
      _time_get (&time_mqx);  
      _rtc_time_from_mqx_time (&time_mqx, &time_rtc);
    
    /* Get the current time in MQX date format */   
      _time_to_date(&time_mqx,&date);
    
      /* If displaying the time... */
      if(display==TIME) 
      { 
        /* Turn on the TIME symbol on LCD and turn off DATE symbol */
        _lcd_symbol(LCD_TIME, TRUE);       
        _lcd_symbol(LCD_DATE, FALSE);
        
        /* Print out the hours, minutes, and seconds to LCD */
      sprintf(&LCD_buffer[0],"h%002i %002i %002i", time_rtc.hours, time_rtc.minutes, time_rtc.seconds);
      _lcd_home();
      _lcd_puts(LCD_buffer);
      
      /* Print out time to serial port */
          //printf ("MQX: %d s, %d ms\n", time_mqx.SECONDS, time_mqx.MILLISECONDS);
        //printf ("    (%d hr, %d m, %d s)\n", time_rtc.hours, time_rtc.minutes, time_rtc.seconds);
      
        /* If detect SW2 button push, increment the hours */
        if(SW2_CLICK()) 
      {  
        printf("Increment Hour\n"); 
        date.HOUR++;
        if(date.HOUR>24)
          date.HOUR=0;
        _time_from_date(&date, &time_mqx);
        _time_set(&time_mqx);
        
        /* Write the MQX BSP time to the RTC registers */
        _rtc_sync_with_mqx(FALSE);        
      }   

        /* If detect SW3 button push, increment the minutes */    
      if(SW3_CLICK()) 
      {  
        printf("Increment Minute\n"); 
        date.MINUTE++;
        if(date.MINUTE>59)
          date.MINUTE=0;
        _time_from_date(&date, &time_mqx);
        _time_set(&time_mqx);
        
        /* Write the MQX BSP time to the RTC registers */
        _rtc_sync_with_mqx(FALSE);        
      }      

        /* If detect SW4 button push, increment the seconds */    
      if(SW4_CLICK()) 
      {  
        printf("Increment Second\n"); 
        date.SECOND++;
        if(date.SECOND>59)
          date.SECOND=0;
        _time_from_date(&date, &time_mqx);
        _time_set(&time_mqx);
        
        /* Write the MQX BSP time to the RTC registers */
        _rtc_sync_with_mqx(FALSE);
      }       
    } 
    /* Else if displaying the date... */
    else 
      {
        /* Turn off the TIME symbol on LCD and turn on DATE symbol */     
        _lcd_symbol(LCD_TIME, FALSE);  
        _lcd_symbol(LCD_DATE, TRUE); 

        /* Print out the day, month, and year to LCD */   
      sprintf(&LCD_buffer[0],"d%002i %002i %002i",time_rtc.days, time_rtc.month, (time_rtc.year-2000));
      _lcd_home();
      _lcd_puts(LCD_buffer);   
      
      /* Print out the date to the serial port */
          //printf ("MQX: %d s, %d ms\n", time_mqx.SECONDS, time_mqx.MILLISECONDS);
        //printf ("    (%d day, %d month, %d year)\n", time_rtc.days, time_rtc.month, time_rtc.year);   
      
        /* If detect SW2 button push, increment the year */ 
        if(SW2_CLICK()) 
      {  
        printf("Increment Year\n"); 
        date.YEAR++;
        _time_from_date(&date, &time_mqx);
        _time_set(&time_mqx);
        
        /* Write the MQX BSP time to the RTC registers */
        _rtc_sync_with_mqx(FALSE);
      }   

        /* If detect SW2 button push, increment the month */     
        if(SW3_CLICK()) 
      {  
        printf("Increment Month\n"); 
        date.MONTH++;
        if(date.MONTH>12)
          date.MONTH=1;
        _time_from_date(&date, &time_mqx);
        _time_set(&time_mqx);

        /* Write the MQX BSP time to the RTC registers */
        _rtc_sync_with_mqx(FALSE);
      }      

        /* If detect SW2 button push, increment the day */    
        if(SW4_CLICK()) 
      {  
        printf("Increment Day\n"); 
        date.DAY++;
        if(date.DAY>31)
          date.DAY=1;
        _time_from_date(&date, &time_mqx);
        _time_set(&time_mqx);

        /* Write the MQX BSP time to the RTC registers */
        _rtc_sync_with_mqx(FALSE);
      }           
      }  
 
      /* SW1 toggles displaying date or time */
    if(SW1_CLICK()) 
    {       
      printf("Switch Display\n"); 
      if(display==TIME)
        display=DATE;
      else
        display=TIME;    
    }
    
    /* Check for tampering */
    DetectTamper();
  }
}


void DetectTamper() 
{
    RTC_TIME_STRUCT tamper_time;
    
    tamper_status=_rtc_get_tamper_status();
   
    /* If detect a new tamper event... */
    if(previous_tamper!= tamper_status) 
    {
      printf("\n\n");
      
      /* Determine type of tamper event */
      if(tamper_status==RTC_TMPR_CLEAR) 
      {  
        printf("Tamper Cleared\n");
      }
      else 
      {   
        printf("Tamper Event Detected!!!\n");
        if(tamper_status==RTC_TMPR_PIN) 
        {  
          printf("Tamper Type: Tamper Pin Low\n");
        }
        else if(tamper_status==RTC_TMPR_BATTERY_VDDON) 
        {  
          printf("Tamper Type: Battery disconnected while power on\n");        
        }
        else if(tamper_status==RTC_TMPR_BATTERY_VDDOFF) 
        {  
          printf("Tamper Type: Battery disconnected while power off\n"); 
        }
      
        /* Get the time the latest tamper event occured */
        _rtc_get_tamper_timestamp(&tamper_time);
       
        printf ("Tamper event time: %02d/%02d/%02d, %02d:%02d:%02d\n", tamper_time.days, tamper_time.month, tamper_time.year, tamper_time.hours, tamper_time.minutes, tamper_time.seconds);
      
        /* Print out previous tamper events */
        printf("Previous tamper events since bootup: \n");
        DisplayLog();
        
        /* Add this event to the log */
        AddLog(tamper_status,tamper_time);
      }
    }
    
    /* Record the current tamper status for comparison above */
    previous_tamper=tamper_status;
    
    /* Clear the tamper flag */
    _rtc_clear_requests(RTC_INT_TMPR_MASK); 

}
  

/*FUNCTION****************************************************************
* 
* Function Name    : AddLog
* Returned Value   : None
* Comments         :
*    Add tamper events to the log
*
*END*********************************************************************/
void AddLog(uchar event, RTC_TIME_STRUCT tamper_time)
{    
    /* Add new event to ring buffer*/
  History[HistoryIndex].tamper_type=event;
    History[HistoryIndex++].tamper_time=tamper_time;
     
    /* If reached end of queue, loop back to beginning */   
    if (HistoryIndex >= MAX_QUEUE) 
       HistoryIndex = 0; 
}

/*FUNCTION****************************************************************
* 
* Function Name    : DisplayLog
* Returned Value   : None
* Comments         :
*    Display the tamper event log
*
*END*********************************************************************/
void DisplayLog() 
{
  int i;
  TAMPER_HIST hist;
  RTC_TIME_STRUCT tamper_time;

  /* Print out last MAX_QUEUE events */
  for(i = (MAX_QUEUE - 1);i >= 0;i--)
  {
    /* Determine latest event */
    hist = (History[(i+HistoryIndex)%MAX_QUEUE]);
    
    /* If a valid entry...*/
    if(hist.tamper_type!=RTC_TMPR_CLEAR) 
    {
      /* Display time */
      tamper_time=hist.tamper_time;
      printf("\t%02d/%02d/%02d, %02d:%02d:%02d",tamper_time.days, tamper_time.month, tamper_time.year, tamper_time.hours, tamper_time.minutes, tamper_time.seconds );
      
      /* Display the type of tamper event */
      if(hist.tamper_type==RTC_TMPR_PIN) 
        printf(" Tamper Pin Low\n");
      else if (hist.tamper_type==RTC_TMPR_BATTERY_VDDON)
        printf(" Battery disconnected while power on\n");
      else if (hist.tamper_type==RTC_TMPR_BATTERY_VDDOFF)
        printf(" Battery disconnected while power off\n");
    }
  }  
}


/*FUNCTION****************************************************************
* 
* Function Name    : clickButton
* Returned Value   : If button was pressed or not
* Comments         :
*    Compares current button status against the previous status to 
*    determine a rising edge
*
*END*********************************************************************/
unsigned short  clickButton(char button,unsigned char *previous) 
{
  unsigned short value;
  unsigned short result=0;
        
  /* read the current pin status into the pin list */
  if (IO_OK != ioctl(port_file, GPIO_IOCTL_READ, (char_ptr) &input_pins))
  {
    printf("Reading pin status failed.\n");
    _mqx_exit(-1);
  }
       
  /* Determine status of pin */      
  value= (input_pins[button] & GPIO_PIN_STATUS)==0;
  
  /* If previous value was 0 and new value is 1, then detected a rising edge, and return 1 */
  if (value==1 && *previous==0) 
    result = 1;
  
  /* Store previous value */
  *previous = value;
   
  return result;    

}
/* EOF */

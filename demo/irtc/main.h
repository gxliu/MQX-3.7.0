#ifndef _main_h_
#define _main_h_
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
* $FileName: main.h$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*   The main configuration file for IRTC demo
*
*END************************************************************************/

#define TIME 0
#define DATE 1


/* Tamper history structure */
typedef struct {
   uchar              tamper_type;
   RTC_TIME_STRUCT    tamper_time;
} TAMPER_HIST, * TAMPER_HIST_PTR;



/* Variables for keeping tamper history */
#define MAX_QUEUE            10
_mqx_int       HistoryIndex=0;
TAMPER_HIST    History[MAX_QUEUE];

void AddLog(uchar event, RTC_TIME_STRUCT tamper_time);
void DisplayLog();

void DetectTamper();
char tamper_status, previous_tamper;

/* GPIO variables */
MQX_FILE_PTR port_file;

GPIO_PIN_STRUCT input_pins[] = {
  BSP_BUTTON1,
  BSP_BUTTON2,
  BSP_BUTTON3,
  BSP_BUTTON4,
  GPIO_LIST_END
};


/* Stores previous value of button */
unsigned char memory_sw1=1;
unsigned char memory_sw2=1;
unsigned char memory_sw3=1;
unsigned char memory_sw4=1;

unsigned short  clickButton(char button,unsigned char *previous); 


RTC_TIME_STRUCT initial_rtc={45,58,23,31,4,12,2009}; //Thursday, December 31, 2009 23:58:45 
                            //seconds, minutes, hours, day, wday, month, year
                            
#endif                            
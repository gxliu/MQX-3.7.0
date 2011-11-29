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
* $FileName: display_task.c$
* $Version : 3.5.11.0$
* $Date    : Jan-20-2010$
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
#include "meter_config.h"
#include "metering_algorithms.h"
#include "task_template_list.h"
#include "tad.h"

typedef enum 
{
    DISPLAY_NONE = 0,
    DISPLAY_V,    /* Voltage        */ 
    DISPLAY_I,    /* Current        */ 
    DISPLAY_PF,   /* Power Factor   */ 
    DISPLAY_ET,   /* Active Energy  */ 
    DISPLAY_PT,   /* Active Power   */ 
    DISPLAY_RPT,  /* Reactive Power */ 
    DISPLAY_APT,  /* Apparent Power */ 
    DISPLAY_TIME, /* Actual Time    */ 
    DISPLAY_DATE, /* Actual Date    */ 
    DISPLAY_LAST
} eDisplay;


typedef enum 
{
    PHASE_NONE = -1,
    PHASE_L1,  /* L1 Phase   */ 
    PHASE_L2,  /* L2 Phase   */ 
    PHASE_L3,  /* L3 Phase   */ 
    PHASE_ALL, /* All Phases */ 
    PHASE_LAST
} ePhase;

/* local variables */
static char  aLDC_buffer[20];
static RTC_TIME_STRUCT time;

/* local function prototypes */
static void switch_display(eDisplay display, ePhase phase);

/* extern variables */
extern Power_vec    Power[4];
       
/*TASK******************************************************
** 
** Task Name    : display_task
** Comments     :
**
*END*******************************************************/
void display_task
   (
      uint_32 initial_data
   )
{
    
    eDisplay display_index;
    ePhase   phase_index;
    
    
    puts("*****************************\n");
    puts("Display Task running\n");
    
    _lcd_init();                       
    _lcd_symbol(LCD_FREESCALE, TRUE); 

    display_index =  DISPLAY_V;
    phase_index   =  PHASE_L1;

    /* 
    ** Refresh display in 500ms
    */
    while(1)
    {

        switch (_lwevent_wait_ticks (
                &meter_shared_event, 
                IO_SW1_MASK | IO_SW2_MASK | IO_SW3_MASK | IO_SW4_MASK, 
                FALSE, 
                200       /* 200 ticks timeout */
            )) 
        {    
            
            /* lwevent caused by switches */
            case MQX_OK:
                {                                                         
                    
                    /* Copy event masks into temporary variable */
                    _mqx_uint event_value = meter_shared_event.VALUE;
                    
                    /* Clear events caused by SW2, SW3, SW4 switches */
                    _lwevent_clear (
                            &meter_shared_event,
                            event_value & (IO_SW1_MASK | IO_SW2_MASK | IO_SW3_MASK | IO_SW4_MASK)
                        );

                    /*
                    **  SWI pressed: not used now, user can add its own button handler
                    */
                    if (event_value & IO_SW1_MASK)
                    {
                    }


                    /*
                    ** Roll display by SW2
                    ** V->I->PF->ET->PT->RPT->APT->TIME->DATE
                    */
                    if (event_value & IO_SW2_MASK)
                    {
                        display_index++;
                        if (display_index >= DISPLAY_LAST)  
                        {
                            display_index  = DISPLAY_NONE + 1;
                        }

                        if  (  (    (display_index == DISPLAY_V) 
                                 || (display_index == DISPLAY_I)
                             &&(phase_index ==  PHASE_ALL)
                            )) 
                        {    
                            phase_index = PHASE_L1;
                        }


                    }
                    /*
                    ** Roll phases back by SW3
                    ** L3->L2->L1 wrap around to L3
                    ** Default state is L1
                    */
                    if (event_value & IO_SW3_MASK)
                    {

                        phase_index--;

                        if  (    (display_index == DISPLAY_V) 
                              || (display_index == DISPLAY_I)
                            )   
                        {
                            if (phase_index <= PHASE_NONE)
                                phase_index  = PHASE_L3;
                        } 
                        else    
                        {      
                            if (phase_index <= PHASE_NONE)
                                phase_index  = PHASE_ALL;
                        }
                    }

                    /*
                    ** Roll phases forward by SW4
                    ** L1->L2->L3 ->wrap back around to L1
                    ** Default state is L1
                    */
                    if (event_value & IO_SW4_MASK)
                    {
                        phase_index++;
                        
                        if  (    (display_index == DISPLAY_V) 
                              || (display_index == DISPLAY_I)
                            )   
                        {
                            if (phase_index >= PHASE_ALL)
                                phase_index  = PHASE_L1;
                        } 
                        else    
                        {      
                            if (phase_index >= PHASE_LAST)
                                phase_index  = PHASE_L1;
                        }

                    }                    
                }
                /* fall through to next case to update display */
            
           
            /* lwevent timeout */
            case LWEVENT_WAIT_TIMEOUT:
                    
                    /* Calculate power metering algorithms neede to be proceed each period */
                    Power_Calc2((int_16 *) vL1_buff, (int_16 *) iL1_buff, &Power[0]);
                    Power_Calc2((int_16 *) vL2_buff, (int_16 *) iL2_buff, &Power[1]);
                    Power_Calc2((int_16 *) vL3_buff, (int_16 *) iL3_buff, &Power[2]);
                    Power3_Calc2(Power);

                    switch_display(display_index, phase_index);
                
                break;
        
            default:
                
                puts("Error in lw_event! Blocking task.\n");
                _task_block();
                break;
        }                
    }
}

/*FUNCTION****************************************************************
* 
* Function Name    : switch_display
* Returned Value   : void
* Comments         :
*
*
*   SW2 toggles through all the available measurements: 
*    V->I->EF->PT->RPT->APT->DATE->TIME
*    
*    SW3 and SW4 change ADC channels up or down, respectively.  
*    
*    SW3 : L1->L3->L2->TOTAL wrap around to L1
*
*    If start on V1, SW3 wraps back around to V3, SW4 move us down to V2.  
*    
*    For the energy and power measurements (PF, ET, PT, RPT, APT), 
*    use these switches to toggle between ADC channels 1, 2, 3, 
*    and then the total power/energy “T”. 
*
*END*********************************************************************/

#define FORMAT0_4   "%4i"          
#define FORMAT0_6   "%6i"
#define FORMAT4_2   "%4i%02i"
#define FORMAT3_3   "%3i%03i"

#define PREFORMAT0_4(value) value
#define PREFORMAT0_6(value) value
#define PREFORMAT4_2(value) value / 100, value %100
#define PREFORMAT3_3(value) value / 1000, value %1000

void switch_display
    (
        /* [IN] display index to be shown on LCD */
        eDisplay display_index,
        
        /* [IN] phase index to be shown on LCD */
        ePhase   phase_index
    )
{
    /* We have to follow rules for voltage and current display values.
    ** The transformation constant is computed from:
    ** voltage: 32768 => 512V 
    ** current: 32768 => 64A
    ** power: 32768 * 32768 => 512 * 64VA = 32768VA
    ** energy: (32768 * 32768) / 65536 * 1s => 512 * 64VAs = 32768Ws = 9.10222 Wh = 0.00910222 kWh
    ** PF: 65535 => 1.000
    */

    static const char * const PhaseStr[]     = {"1", "2", "3", "T"};
    static const char * const DayOfWeekStr[] = {"SU", "MO", "TU", "WE", "TH", "FR", "SA"};

    uint_32 value;
    aLDC_buffer[3] = aLDC_buffer[4] = aLDC_buffer[5] = aLDC_buffer[6] = aLDC_buffer[7] = aLDC_buffer[8] = aLDC_buffer[9] = ' ';
    
    switch(display_index)
    {
        /* 
        ** RMS Voltage  
        */ 
        case DISPLAY_V :
            /* Turn off Date display symbols */
            _lcd_symbol(LCD_DATE, FALSE);
            _lcd_symbol(LCD_COL2, FALSE); 
            _lcd_symbol(LCD_COL3, FALSE); 
            _lcd_symbol(LCD_DT5,  FALSE); 
            _lcd_symbol(LCD_DT7,  FALSE); 

            value = (Power[phase_index].Vrms * 51200) / 32768; /* display 65536 as 512.00V */
            
            /* Prepare Vrms string */
            sprintf (
                    aLDC_buffer,
                    "V%s "FORMAT4_2, 
                    PhaseStr[phase_index], 
                    PREFORMAT4_2(value)
                );
            
            /* Turn on Vrms display symbols */
            _lcd_symbol(LCD_DT7,   TRUE);
            _lcd_symbol(LCD_VOLTS, TRUE);
            
            break;            
        
        /* 
        ** RMS Current  
        */ 
        case DISPLAY_I :
            /* Turn off Vrms display symbols */
            _lcd_symbol(LCD_VOLTS, FALSE);
            _lcd_symbol(LCD_DT7,   FALSE);
            
            value = ((uint_32) Power[phase_index].Irms * 64000) / 32768; /* display 32768 as 64.000A */
            
            /* Prepare Irms string */ 
            sprintf (
                    aLDC_buffer,
                    "I%s "FORMAT4_2, 
                    PhaseStr[phase_index], 
                    PREFORMAT4_2(value)
                );
            
            /* Turn on Irms display symbols */
            _lcd_symbol(LCD_DT6,  TRUE);
            _lcd_symbol(LCD_AMPS, TRUE);
            
            break;            

        /* 
        ** Power Factor
        */ 
        case DISPLAY_PF :
            
             /* Turn off Irms display symbols */
            _lcd_symbol(LCD_DT6,  FALSE);
            _lcd_symbol(LCD_AMPS, FALSE);
            
            value = ((uint_32) Power[phase_index].Pwr_fct * 1000) / 65535; /* display 65535 as 1.000 */

            sprintf (
                    aLDC_buffer,
                    "PF%s"FORMAT3_3, 
                    PhaseStr[phase_index], 
                    PREFORMAT3_3(value)
                );
            
            _lcd_symbol(LCD_DT6,  TRUE);
            
            break;

        /* 
        ** Active Energy
        */ 
        case DISPLAY_ET :
            
            _lcd_symbol(LCD_DT6,  FALSE);
            
            // value = (Power[phase_index].Act_Eng * 0.00910222 / 16384);
            value = Power[phase_index].Act_Eng * 596 / 65536 / 16384;

            sprintf (
                    aLDC_buffer,
                    "E%s "FORMAT0_6,
                    PhaseStr[phase_index], 
                    PREFORMAT0_6(value)
                );

            _lcd_symbol(LCD_KWHr, TRUE);
            
            break;            

        /* 
        ** Active Power
        */ 
        case DISPLAY_PT :
            
            _lcd_symbol(LCD_KWHr, FALSE);

            // value = Power[phase_index].Act_Pwr * 32768 / 32768 / 32768;
            if (Power[phase_index].Act_Pwr < 0)
                value = -Power[phase_index].Act_Pwr / 32768;
            else
                value = Power[phase_index].Act_Pwr / 32768;
            
            sprintf (
                    aLDC_buffer,
                    "P%s "FORMAT0_6, 
                    PhaseStr[phase_index], 
                    PREFORMAT0_6(value)
                );
            
            break;
        
        /* 
        ** Reactive Power 
        */ 
        case DISPLAY_RPT :
            
            //value = Power[phase_index].React_Pwr * 32768 / 32768 / 32768;
            value = Power[phase_index].React_Pwr / 32768;

            sprintf (
                    aLDC_buffer,
                    "RP%s"FORMAT0_6,
                    PhaseStr[phase_index], 
                    PREFORMAT0_6(value)
                );
            break;            

        /* 
        ** Apparent Power
        */ 
        case DISPLAY_APT :
        
            //value = Power[phase_index].Apr_Pwr * 32768 / 32768 / 32768;
            value = Power[phase_index].Apr_Pwr / 32768;
            
            sprintf (
                    aLDC_buffer,
                    "AP%s"FORMAT0_6, 
                    PhaseStr[phase_index], 
                    PREFORMAT0_6(value)
                );

            
            
            break;
        /*
        **  Display actual time on LCD in format "HR:MIN:SEC" 
        **  together with TIME symbol
        **      "HR"  = Hours 
        **      "MIN" = Minutes 
        **      "SEC" = Seconds  
        **  Example: "  12.25.59"
        */
        case DISPLAY_TIME:

                _rtc_get_time(&time);

                /* preformat time */
                sprintf (
                        aLDC_buffer,
                        "T  %2i%02i%02i",
                        time.hours, 
                        time.minutes, 
                        time.seconds
                    );

                if (time.hours >= 12)    {
                    _lcd_symbol(LCD_PM, TRUE);
                }
                else {
                    _lcd_symbol(LCD_AM, TRUE);
                }

                _lcd_symbol(LCD_TIME, TRUE);
                _lcd_symbol(LCD_COL2, TRUE); 
                _lcd_symbol(LCD_COL3, TRUE); 

            break;
        /*
        **  Display actual date on LCD in format "WD-DD.MM.YY" 
        **  together with DATE symbol
        **      "WD" = Day of Week 
        **      "DD" = Day 
        **      "MM" = Month  
        **      "YY" = Year
        **  Example: "TH-21.01.10"
        */
        case DISPLAY_DATE:

                _rtc_get_time(&time);
                
                _lcd_symbol(LCD_TIME, FALSE);
                _lcd_symbol(LCD_COL2, FALSE); 
                _lcd_symbol(LCD_COL3, FALSE); 
                _lcd_symbol(LCD_AM,   FALSE);
                _lcd_symbol(LCD_PM,   FALSE);


                /* preformat date */
                sprintf (
                        aLDC_buffer,
                        "%s-%02i%02i%02i",
                        DayOfWeekStr[time.wday], 
                        time.days, 
                        time.month, 
                        time.year-2000
                    );
                
                _lcd_symbol(LCD_DATE, TRUE);
                _lcd_symbol(LCD_DT5,  TRUE); 
                _lcd_symbol(LCD_DT7,  TRUE); 

            break;
    }

    
    /* 
    ** Print data from aLDC_buffer on LCD display 
    */
    _lcd_home();
    _lcd_puts(aLDC_buffer);
    
    /* Uncomment following lines to send data to the stdout */
    // puts(aLDC_buffer);
    // puts("\n");
}
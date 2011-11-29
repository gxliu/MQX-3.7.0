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
* $FileName: lcd.c$
* $Version : 3.7.3.0$
* $Date    : Mar-23-2011$
*
* Comments:
*
*   This file contains the source for the hello example program.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h> 
#include <fio.h>
#include <string.h>


#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


/* Task IDs */
#define LCD_TASK 5

extern void lcd_task(uint_32);


const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{ 
   /* Task Index, Function,   Stack,  Priority, Name,       Attributes,          Param, Time Slice */
    { LCD_TASK,   lcd_task,   1500,   8,        "LCD Task", MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

char lcd_bufer[10];


/*TASK********************************************************************
* 
* Function Name    : lcd_task
* Returned Value   : void
* Comments         :
*   Demonstrate LCD driver features.
*
*END*********************************************************************/


void lcd_task
   (
      uint_32 initial_data
   )
{

    eLCD_Symbols lcd_symbol;
    uint_16      delay = 500; /* 500ms delay */
    int_16       i;

    (void)_lcd_init();


    while (1) 
    {
        /* Turn all segments on display on */        
        _lcd_segments(TRUE);
        
        _time_delay(delay);        
        
        /* Turn all segments on display off */                
        _lcd_segments(FALSE);


        /* display all special symbols on display */
        for (lcd_symbol = LCD_FREESCALE; lcd_symbol < LCD_LAST_SYMBOL; lcd_symbol++)
        {
            (void)_lcd_symbol(lcd_symbol, TRUE);
            _time_delay(delay / 10);
        } 

        for (lcd_symbol = LCD_FREESCALE; lcd_symbol < LCD_LAST_SYMBOL; lcd_symbol++)
        {
           (void)_lcd_symbol(lcd_symbol, FALSE);
           _time_delay(delay / 10);
        } 

        _lcd_symbol(LCD_DT7, FALSE);
        
        /* Display text messages */
        _lcd_home();
        _lcd_puts("Hallo");
        _time_delay(delay);    

        _lcd_home();
        _lcd_puts("World");
        _time_delay(delay);    
        
        /* Display numbers */
        _lcd_symbol(LCD_DT4, TRUE);        
        i = -100;
        while (i < 100)
        {
            sprintf(lcd_bufer, "i=%+04i", i++);     
            _lcd_home();
            _lcd_puts(lcd_bufer);
            _time_delay(delay / 10);
        }
        _lcd_symbol(LCD_DT4, FALSE);        

        /* Display special characters */
        _lcd_home();
        _lcd_puts("+-/\\>=<");
        _time_delay(delay * 4); 


        /* Turn segments on display off */        
        _lcd_segments(FALSE);
        _time_delay(delay);    
    }
   
    _mqx_exit(0);

}

/* EOF */

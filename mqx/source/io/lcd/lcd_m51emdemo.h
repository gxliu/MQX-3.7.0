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
* $FileName: lcd_m51emdemo.h$
* $Version : 3.7.4.0$
* $Date    : Feb-16-2011$
*
* Comments:
*
* Freescale GD3980P display public types and function prototypes.
*
*END************************************************************************/

#ifndef __LCD_M51EMDEMO_H
    #define __LCD_M51EMDEMO_H


/**********************************************************************
**
** Enumeration type for symbols of Freescale GD3980P display
**
*/                                                                                                                                

typedef enum  
{
    LCD_FREESCALE,
    LCD_FIRE,
    LCD_SNOW,
    LCD_CLOCK,
    LCD_BATT,
    LCD_BATT_T1,
    LCD_BATT_T2,
    LCD_BATT_T3,
    LCD_BATT_T4,
    LCD_POWER_SAVE,
    LCD_VOL,
    LCD_VOL_V1,
    LCD_VOL_V2,
    LCD_VOL_V3,
    LCD_VOL_V4,
    LCD_VOL_V5,
    LCD_KWHr,
    LCD_AMPS,
    LCD_VOLTS,
    LCD_AM,
    LCD_PM,
    LCD_OHM,
    LCD_MINUS,
    LCD_DT1,
    LCD_DT2,
    LCD_DT3,
    LCD_DT4,
    LCD_DT5,
    LCD_DT6,
    LCD_DT7,
    LCD_DT8,
    LCD_DT9,
    LCD_COL1,
    LCD_COL2,
    LCD_COL3,
    LCD_COL4,
    LCD_TIME,
    LCD_DATE,
    LCD_TEMP,
    LCD_VOLUME,    
    LCD_CONTRAST,
    LCD_MODE,
    LCD_PROGRAM,
    LCD_LAST_SYMBOL
}  eLCD_Symbols;

/********************************************************************** 
**
** Public function prototypes
**
*/ 
extern int_32 _lcd_init(void);
extern uint_8 _lcd_home (void);
extern void   _lcd_segments (boolean state) ;
extern int_32 _lcd_symbol(eLCD_Symbols symbol_index, boolean state);
extern int_32 _lcd_decimal_point(uint_8 position, boolean state);
extern uint_8 _lcd_putchar (char c);
extern void   _lcd_puts(const char * pString);

#endif /* __LCD_M51EMDEMO_H */

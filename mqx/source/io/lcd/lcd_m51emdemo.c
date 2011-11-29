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
* $FileName: lcd_m51emdemo.c$
* $Version : 3.7.8.0$
* $Date    : Mar-9-2011$
*
* Comments:
*
*   This file contains the GD3980P display driver functions
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>                    


#include "lcd_m51emdemo_prv.h"


/* LCD symbol structure */
typedef struct lcd_symbol_struct 
{
    /* register index */
    uint_8 index;
    /* mask */
    uint_8 mask;
} LCD_SYMBOL_STRUCT; 


/* convert character to upper case */
#define _TOUPPER(c)     (((c)>='a' && (c)<='z') ? ((c)+'A'-'a') : (c)) 
#define _TOALFANUM(c)   (((c)>='0' && (c)<='Z') ? (c) : ':')
#define FP_MASK(com)    (1 << (com)) 

/*
** Ascii table 
*/
typedef enum  
{
    E_0,
    E_1,
    E_2,
    E_3,
    E_4,
    E_5,
    E_6,
    E_7,
    E_8,
    E_9,
    E_AllOff,
    E_SemiColon,
    E_MinusThan,
    E_Equal,
    E_GreaterThan,
    E_Question,
    E_AllOn,
    E_A,
    E_B,
    E_C,
    E_D,
    E_E,
    E_F,
    E_G,
    E_H,
    E_I,
    E_J,
    E_K,
    E_L,
    E_M,
    E_N,
    E_O,
    E_P,
    E_Q,
    E_R,
    E_S,
    E_T,
    E_U,
    E_V,
    E_W,
    E_X,
    E_Y,
    E_Z,
    E_Slash,
    E_BackSlash,
    E_Plus,
    E_Minus
}  eAscii;

/*
** Ascii table 
*/
static const char aAscii [ ] =
{
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    _AllOff,
    _SemiColon,
    _MinusThan,
    _Equal,
    _GreaterThan,
    _Question,
    _AllOn,
    _A,
    _B,
    _C,
    _D,
    _E,
    _F,
    _G,
    _H,
    _I,
    _J,
    _K,
    _L,
    _M,
    _N,
    _O,
    _P,
    _Q,
    _R,
    _S,
    _T,
    _U,
    _V,
    _W,
    _X,
    _Y,
    _Z,
    _Slash,
    _BackSlash,
    _Plus,
    _Minus        
};

/*
** LCD waveform for each alphanumeric 
*/
static const uint_8 aPlace [ ] =
{
    CHAR1A,     /* LCD4  --- Pin: 5 */
    CHAR1B,     /* LCD5  --- Pin: 6 */
    CHAR1C,     /* LCD6  --- Pin: 7 */
    CHAR1D,     /* LCD7  --- Pin: 8 */
    CHAR2A,     /* LCD8  --- Pin: 9 */
    CHAR2B,     /* LCD9  --- Pin:10 */
    CHAR2C,     /* LCD10 --- Pin:11 */
    CHAR2D,     /* LCD11 --- Pin:12 */
    CHAR3A,     /* LCD12 --- Pin:44 */
    CHAR3B,     /* LCD13 --- Pin:43 */
    CHAR3C,     /* LCD14 --- Pin:42 */
    CHAR3D,     /* LCD15 --- Pin:41 */
    CHAR4A,     /* LCD16 --- Pin:40 */
    CHAR4B,     /* LCD17 --- Pin:39 */
    CHAR4C,     /* LCD18 --- Pin:38 */
    CHAR4D,     /* LCD19 --- Pin:37 */
    CHAR5A,     /* LCD20 --- Pin:36 */
    CHAR5B,     /* LCD21 --- Pin:35 */
    CHAR5C,     /* LCD22 --- Pin:34 */
    CHAR5D,     /* LCD23 --- Pin:33 */
    CHAR6A,     /* LCD24 --- Pin:32 */
    CHAR6B,     /* LCD25 --- Pin:31 */
    CHAR6C,     /* LCD26 --- Pin:30 */
    CHAR6D,     /* LCD27 --- Pin:29 */
    CHAR7A,     /* LCD28 --- Pin:13 */
    CHAR7B,     /* LCD29 --- Pin:14 */
    CHAR7C,     /* LCD30 --- Pin:15 */
    CHAR7D,     /* LCD31 --- Pin:16 */
    CHAR8A,     /* LCD32 --- Pin:17 */
    CHAR8B,     /* LCD33 --- Pin:18 */
    CHAR8C,     /* LCD34 --- Pin:19 */
    CHAR8D,     /* LCD35 --- Pin:20 */
    CHAR9A,     /* LCD36 --- Pin:21 */
    CHAR9B,     /* LCD37 --- Pin:22 */
    CHAR9C,     /* LCD38 --- Pin:23 */
    CHAR9D      /* LCD39 --- Pin:24 */
};      



static const uint_8 aSymbolMask[] = {
    0x00, 0x00, 0x08, 0x0C
};

/* 
** The GD3980P display is connected to MC51EM256 so that it  
** uses 4 backplanes COM1-COM4 (display pins 1 - 4) connected to LCD[0:3].
** and 39 frontplanes          (display pins 5 -44) connected to LCD[4:43]
*/
static uint_8  aShadow[44];
static vuint_8 bLCD_CharPosition;

/* local function prototypes */
static void _lcd_enable_pins (void);
static void _lcd_set_backplanes(void);
static void _lcd_enable_backplanes (void);
static pointer _bsp_get_lcd_base_address (void);



static LCD_SYMBOL_STRUCT lcd_symbol_table[] = {

                       /* fp, frontplane_mask */
/* LCD_FREESCALE    */  { 14, FP_MASK(3) },
/* LCD_FIRE,        */  { 15, FP_MASK(3) }, 
/* LCD_SNOW,        */  { 19, FP_MASK(3) }, 
/* LCD_CLOCK,       */  { 26, FP_MASK(3) }, 
/* LCD_BATT,        */  { 27, FP_MASK(3) }, 
/* LCD_BATT_T1,     */  { 43, FP_MASK(3) }, 
/* LCD_BATT_T2,     */  { 43, FP_MASK(2) }, 
/* LCD_BATT_T3,     */  { 43, FP_MASK(1) }, 
/* LCD_BATT_T4,     */  { 43, FP_MASK(0) }, 
/* LCD_POWER_SAVE,  */  { 30, FP_MASK(3) }, 
/* LCD_VOL,         */  { 42, FP_MASK(0) }, 
/* LCD_VOL_V1,      */  { 39, FP_MASK(3) }, 
/* LCD_VOL_V2,      */  { 40, FP_MASK(0) }, 
/* LCD_VOL_V3,      */  { 42, FP_MASK(1) }, 
/* LCD_VOL_V4,      */  { 42, FP_MASK(2) }, 
/* LCD_VOL_V5,      */  { 42, FP_MASK(3) }, 
/* LCD_KWHr,        */  { 41, FP_MASK(0) }, 
/* LCD_AMPS,        */  { 41, FP_MASK(1) }, 
/* LCD_VOLTS,       */  { 41, FP_MASK(2) }, 
/* LCD_AM,          */  { 40, FP_MASK(1) }, 
/* LCD_PM,          */  { 40, FP_MASK(2) }, 
/* LCD_OHM,         */  { 40, FP_MASK(3) }, 
/* LCD_MINUS,       */  {  7, FP_MASK(3) }, 
/* LCD_DT1,         */  {  7, FP_MASK(2) }, 
/* LCD_DT2,         */  { 11, FP_MASK(3) }, 
/* LCD_DT3,         */  { 15, FP_MASK(2) }, 
/* LCD_DT4,         */  { 19, FP_MASK(2) }, 
/* LCD_DT5,         */  { 23, FP_MASK(3) }, 
/* LCD_DT6,         */  { 27, FP_MASK(2) }, 
/* LCD_DT7,         */  { 31, FP_MASK(3) }, 
/* LCD_DT8,         */  { 35, FP_MASK(2) }, 
/* LCD_DT9,         */  { 39, FP_MASK(2) }, 
/* LCD_COL1,        */  { 11, FP_MASK(2) }, 
/* LCD_COL2,        */  { 23, FP_MASK(2) }, 
/* LCD_COL3,        */  { 31, FP_MASK(2) }, 
/* LCD_COL4,        */  { 38, FP_MASK(3) }, 
/* LCD_TIME,        */  {  6, FP_MASK(3) }, 
/* LCD_DATE,        */  { 10, FP_MASK(3) }, 
/* LCD_TEMP,        */  { 18, FP_MASK(3) }, 
/* LCD_VOLUME,      */  { 22, FP_MASK(3) }, 
/* LCD_CONTRAST,    */  { 34, FP_MASK(3) }, 
/* LCD_MODE,        */  { 35, FP_MASK(3) }, 
/* LCD_PROGRAM,     */  { 41, FP_MASK(3) }  
};
                              

/*FUNCTION****************************************************************
*                             
* Function Name    : _lcd_init
* Returned Value   : MQX error code
* Comments         :
*    This function (re)initializes/clears/enables LCD module.
*
*END*********************************************************************/

#define LCD_LCDC0_LCDEN_MASK    0x80
#define LCD_LCDC0_SOURCE_MASK   0x40

int_32 _lcd_init(void)                                                                                                          
{                                                                                                                               
                                                                                                                                
    MCF51EM_LCD_STRUCT_PTR   lcd = _bsp_get_lcd_base_address();

    /* Disable LCD frame frequency interrupt and configure LCD Module 
    ** to continue running during wait and stop3 mode
    */
    lcd->LCDC1 = 0x00;

    _ASM_NOP();  

    /*
    ** Configures 1/4 duty cycle and 128 as LCD clock input divider (LCLK=3)
    ** LCD Waveform Base Clock = 256 Hz
    */

    lcd->LCDC0 = 0x1B;
    _ASM_NOP();  

    /* 
    ** Enable charge pump (The internal 1/3-bias is forced) 
    */
    lcd->LCDSUPPLY |= 0x80;
    _ASM_NOP();  

    /*
    ** Configures 2 Hz as LCD blink frequency 
    ** (blink only individual LCD segments)
    */
    lcd->LCDBCTL = 0x02;
    _ASM_NOP();  

    /*
    ** Enable pins used for GD3890P LCD display.
    ** The LCD driver uses all pins LCD[0:43].
    ** Pin multiplexer is set for LCD functionality 
    ** in _bsp_lcd_io_init() function
    */
    _lcd_enable_pins();

    /*
    ** LCD[0:3]  controls  4 backplane signals
    ** LCD[4:43] controls 39 frontplane signals
    */
    
    _lcd_enable_backplanes();
    _lcd_set_backplanes();

    /*
    ** Enable LCD driver module
    */
    lcd->LCDC0  |= LCD_LCDC0_LCDEN_MASK;
    _ASM_NOP();  

    return MQX_OK;
}


/*FUNCTION****************************************************************
* 
* Function Name    : _lcd_enable_pins
* Returned Value   : void
* Comments         :
*    Enables all pins connected to the LCD
*
*END*********************************************************************/

static void _lcd_enable_pins (void)
{

    MCF51EM_LCD_STRUCT_PTR   lcd = _bsp_get_lcd_base_address();

    /* enable backplane pins */
    lcd->LCDBPEN[0] = 0x0F;
    _ASM_NOP();
    
    lcd->LCDPEN[0] = 0xFF;
    _ASM_NOP();  
    lcd->LCDPEN[1] = 0xFF;
    _ASM_NOP();  
    lcd->LCDPEN[2] = 0xFF;
    _ASM_NOP();  
    lcd->LCDPEN[3] = 0xFF;
    _ASM_NOP();  
    lcd->LCDPEN[4] = 0xFF;
    _ASM_NOP();  
    lcd->LCDPEN[5] = 0x0F;
    _ASM_NOP();  
}

/*FUNCTION****************************************************************
* 
* Function Name    : _lcd_enable_backplanes
* Returned Value   : none
* Comments         :
*    This function configures specified pin as backplane.
*
*END*********************************************************************/

static void _lcd_enable_backplanes (void)
{

    MCF51EM_LCD_STRUCT_PTR   lcd = _bsp_get_lcd_base_address();
    
    lcd->LCDBPEN[0] = 0x0F;
}
  
/*FUNCTION****************************************************************
* 
* Function Name    : _lcd_set_backplanes
* Returned Value   : none
* Comments         :
*    Assign the number of COM to waveform register
*
*END*********************************************************************/

static void _lcd_set_backplanes(void)
{

    MCF51EM_LCD_STRUCT_PTR   lcd = _bsp_get_lcd_base_address();

    lcd->LCDWF[0] = 1;  /* COM1 */
    _ASM_NOP();  
    lcd->LCDWF[1] = 2;  /* COM2 */
    _ASM_NOP();  
    lcd->LCDWF[2] = 4;  /* COM3 */
    _ASM_NOP();  
    lcd->LCDWF[3] = 8;  /* COM4 */
    _ASM_NOP();  
}

/*FUNCTION****************************************************************
* 
* Function Name    : _lcd_segments
* Returned Value   : none
* Comments         :
*   Functin controls graphical symbols on Freescale GD3980P LCD display.
*   If (state = TRUE)  all segments on display are turned on
*   else if (state = FALSE) all segments on display are turned off
*
*END**********************************************************************/

void _lcd_segments (boolean state) 
{

    MCF51EM_LCD_STRUCT_PTR  lcd_ptr = _bsp_get_lcd_base_address();
    uint_32                 lbCounter = 44;

    
    while (--lbCounter >= 4)
    {
        lcd_ptr->LCDWF[lbCounter] = aShadow[lbCounter] = (state == FALSE ? 0 : 0x0F);
    }
}

/*FUNCTION****************************************************************
* 
* Function Name    : _lcd_symbol
* Returned Value   : none
* Comments         :
*    Functin controls graphical symbols on Freescale GD3980P LCD display.
*
*END**********************************************************************/


int_32 _lcd_symbol(eLCD_Symbols symbol_index, boolean state)
{                                                         
    MCF51EM_LCD_STRUCT_PTR  lcd_ptr = _bsp_get_lcd_base_address();
    uint_32                 lbIndex;    
    uint_8                  lbMask;
    
    /* check if requested symbol is in table */
    if (  (symbol_index >= LCD_FREESCALE)
        &&(symbol_index <  LCD_LAST_SYMBOL))
    {    
        /* Get mask for specified symbol from symbol table */
        lbMask  = lcd_symbol_table[symbol_index].mask;
        
        /* Get index of LCDWF register */
        lbIndex = lcd_symbol_table[symbol_index].index;        
        
        if (state == TRUE)  { /* turn symbol ON */
            /* update LCD shadow field with new frontplane mask */
            lbMask = aShadow[lbIndex] |= lbMask;
        }
        else { /* turn symbol OFF */
            /* update LCD shadow field with new frontplane mask */
            lbMask = aShadow[lbIndex] &= ~lbMask;
        }
        
        /* Write new mask into registers */
        lcd_ptr->LCDWF[lbIndex] = lbMask;
        
        /* symbol succesfully displayed */
        return MQX_OK;
    }
    else
    {
        /* LCD symbol index does out of range */
        return -1;
    }    
}


/*FUNCTION****************************************************************
* 
* Function Name    : _lcd_decimal_point
* Returned Value   : MQX error code
* Comments         :
*    This function displays decimal point on specified position.
*
*END*********************************************************************/

int_32 _lcd_decimal_point(uint_8 position, boolean state)
{
    if((position >= 0) && (position <= (LCD_DT9 - LCD_DT1)))   {
        (void)_lcd_symbol(LCD_DT1 + position, state);
        return MQX_OK;
    }
    else {
        return -1;
    }    
}

/*FUNCTION****************************************************************
* 
* Function Name    : _lcd_home
* Returned Value   : none
* Comments         :
*   Reset the counter to the home position
*
*END*********************************************************************/

uint_8 _lcd_home (void)
{
    return bLCD_CharPosition =  0;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _lcd_putchar
* Returned Value   : position on display where character was printed
* Comments         :
*   Write new ASCII character after the last one on LCD display.
*   All characters are converted to upper-case.
*
*   '@' character turns all segments on current position ON
*   ':' character turns all segments on current position OFF 
*
*END*********************************************************************/

static char bLastChar = 0;

uint_8 _lcd_putchar 
(
    /* [IN] character to be printed on current display position */
    char c
)
{
    uint_8_ptr lbpLCDWF;
    uint_32    lbCounter;
    uint_8     lbShadow;
    uint_32    lbIndex;
    uint_32    lbValue;
    
    MCF51EM_LCD_STRUCT_PTR   lcd = _bsp_get_lcd_base_address();
 
    switch(c)
    {
        case '+':
            lbValue = E_Plus;
            break;

        case '-':
            lbValue = E_Minus;
            break;
    
        case '/':
            lbValue = E_Slash;
            break;

        case  '\\':
            lbValue = E_BackSlash;
            break;

        case '<':
            lbValue = E_MinusThan;
            break;
    
        case '=':
            lbValue = E_Equal;
            break;

        case '>':
            lbValue = E_GreaterThan;
            break;
    
        default :
            
            /* Convert to upper-case */
            lbValue = _TOUPPER(c);

            /* Filter alfanumeric symbols. Other symbols are displayed as space */
            lbValue = _TOALFANUM(lbValue);
        
            /* Remove the offset to search in the ASCII table */
            lbValue  -= '0';    
 
            break;
    }
    
    
    /* Compensate the matrix offset */
    lbValue  *= _LCDTYPE;   
    
    /* Set the number of writings to complete one char */
    lbCounter = _LCDTYPE;   


    while (lbCounter--  && bLCD_CharPosition < _CHARNUM )
    {
        /* Get index of waveform register to write mask */
        lbIndex = aPlace[(lbCounter + bLCD_CharPosition * _LCDTYPE)];
        
        /* Get shadow mask */
        lbShadow  = aShadow[lbIndex];
        
        /* Mask alfanumeric segments to clear */
        lbShadow &= aSymbolMask[lbCounter];
        
        /* Add character mask from ASCII table */
        lbShadow |= aAscii[lbValue + lbCounter];
        
        /* Backup mask */
        aShadow[lbIndex] = lbShadow;
         
        /* Update waveform register */
        lcd->LCDWF[lbIndex] = lbShadow;
    }
    
    /* Save last displayed character */
    bLastChar = c;
    /* point to next char position to write */
    return bLCD_CharPosition++;
}


/*FUNCTION****************************************************************
* 
* Function Name    : _lcd_puts
* Returned Value   : none
* Comments         : The _lcd_puts() writes string pointed by pString
*                    to LCD display
*
*END*********************************************************************/

void _lcd_puts
(
    /* [IN] the string to be printed out. */
    const char * pString
)
{
    uint_8  lbPosition;
    uint_32 lbSize     = 0;          
    
    while (lbSize < _CHARNUM && *pString) 
    {
        lbPosition = _lcd_putchar (*pString++);
        lbSize++;    
    }

    if (lbSize < _CHARNUM) {

        /* complete data with blanks */
        while (lbSize++< _CHARNUM) _lcd_putchar (':');
    }
    
    bLCD_CharPosition = 0;
}


/*FUNCTION****************************************************************
* 
* Function Name    : _bsp_get_lcd_base_address
* Returned Value   : pointer to base of LCD registers
* Comments         :
*    This function returns base address of LCD related register space.
*
*END*********************************************************************/
pointer _bsp_get_lcd_base_address 
(
    void
)
{
    return (pointer)(&((VMCF51EM_STRUCT_PTR)BSP_IPSBAR)->LCD);
}

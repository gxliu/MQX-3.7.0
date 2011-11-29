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
* $FileName: lcd_twrk40x256.h$
* $Version : 3.7.2.0$
* $Date    : Feb-16-2011$
*
* Comments:
*
* Freescale TWRPI-SLCD display public types and function prototypes
*
*END************************************************************************/

#ifndef __LCD_TWRK40X256_H
    #define __LCD_TWRK40X256_H


/**********************************************************************
**
** Enumeration type for symbols of Freescale TWRPI-SLCD display.
**
*/                                                                                                                                

typedef enum  
{
    LCD_FREESCALE,
    LCD_AM,
    LCD_PM,
    LCD_DEGREES,
    LCD_PERCENT,
    LCD_COL1,
    LCD_ONE,
    LCD_LAST_SYMBOL
}  eLCD_Symbols;

/********************************************************************** 
**
** Public function prototypes
**
*/ 

extern int_32 _lcd_init(void);
extern void   _lcd_segments(boolean state); 
extern int_32 _lcd_symbol(eLCD_Symbols symbol_index, boolean state);
extern void   _lcd_puts(const char * pString);

#endif /* __LCD_TWRK40X256_H */

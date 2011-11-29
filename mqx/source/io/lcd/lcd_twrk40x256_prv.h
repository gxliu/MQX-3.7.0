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
* $FileName: lcd_twrk40x256_prv.h$
* $Version : 3.7.2.0$
* $Date    : Feb-16-2011$
*
* Comments:
*
*   This file contains the private LCD driver definitions and types
*
*END************************************************************************/

#ifndef __LCD_TWRK40X256_PRV_H
    #define __LCD_TWRK40X256_PRV_H

/* 
** Map segment to COM mask 
*/
#define  SEGA   0x01
#define  SEGB   0x02
#define  SEGC   0x04
#define  SEGD   0x08

#define  SEGE   0x04
#define  SEGF   0x01
#define  SEGG   0x02

#define SEG_AD_MASK  (SEGA | SEGB | SEGC | SEGD)
#define SEG_EG_MASK  (SEGE | SEGF | SEGG)

/* 
** definition of segment masks for specific character
*/  
/*           segment A-D drive pin      segment E-G drive pin mask */
#define  _0 ( SEGA| SEGB| SEGC| SEGD) , ( SEGE| SEGF )
#define  _1 ( SEGB| SEGC )            , ( 0x00 )
#define  _2 ( SEGA| SEGB| SEGD )      , ( SEGG| SEGE )
#define  _3 ( SEGA| SEGB| SEGC| SEGD) , ( SEGG )
#define  _4 ( SEGB| SEGC )            , ( SEGF | SEGG )
#define  _5 ( SEGA| SEGC| SEGD )      , ( SEGF| SEGG )
#define  _6 ( SEGA| SEGC| SEGD )      , ( SEGF| SEGE| SEGG )
#define  _7 ( SEGA| SEGB| SEGC )      , ( 0x00 )
#define  _8 ( SEGA| SEGB| SEGC| SEGD) , ( SEGE| SEGF| SEGG )
#define  _9 ( SEGA| SEGB| SEGC| SEGD) , ( SEGF| SEGG )
#define  _A ( SEGA| SEGB| SEGC )      , ( SEGE| SEGF| SEGG )
#define  _B ( SEGC| SEGD )            , ( SEGE| SEGF| SEGG )
#define  _C ( SEGA| SEGD )            , ( SEGE| SEGF )
#define  _D ( SEGB| SEGC| SEGD )      , ( SEGE| SEGG )
#define  _E ( SEGA| SEGD )            , ( SEGE| SEGF| SEGG )
#define  _F ( SEGA )                  , ( SEGE| SEGF| SEGG )
#define  _END_OF_LIST   31

#define AD_POS 		0
#define EG_POS 		1

#define DIGITS_NUM	4

typedef struct lcd_symbol_struct
{
   uint_32 volatile *   WF_REG;
   uint_32  MASK;
} LCD_SYMBOL_STRUCT, _PTR_ LCD_SYMBOL_STRUCT_PTR;


typedef struct lcd_pin_reg_struct
{
   uint_32 volatile *  WF_REG;
   uint_32  SHIFT;
} LCD_PIN_REG_STRUCT, _PTR_ LCD_PIN_REG_STRUCT_PTR;

#endif /* __LCD_TWRK40X256_PRV_H */

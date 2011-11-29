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
* $FileName: lcd_m51emdemo_prv.h$
* $Version : 3.7.5.0$
* $Date    : Feb-16-2011$
*
* Comments:
*
*   This file contains the private LCD driver definitions and types
*
*END************************************************************************/

#ifndef __LCD_M51EMDEMO_PRV_H
    #define __LCD_M51EMDEMO_PRV_H

#define _CHARNUM (9)
#define _LCDTYPE (4)  /* 4 bytes to complete one character  */


/*
** Character place
** This macro defines the LDCWavefroms directions needed for write the alphanumerics        
** param:  LCDpin --- LCDn number of pin that its connected 
*/
#define   CHAR1A        (4)     /* LCD Pin 5    */
#define   CHAR1B        (5)     /* LCD Pin 6    */
#define   CHAR1C        (6)     /* LCD Pin 7    */
#define   CHAR1D        (7)     /* LCD Pin 8    */
#define   CHAR2A        (8)     /* LCD Pin 9    */
#define   CHAR2B        (9)     /* LCD Pin 10   */
#define   CHAR2C        (10)    /* LCD Pin 11   */
#define   CHAR2D        (11)    /* LCD Pin 12   */
#define   CHAR3A        (12)    /* LCD Pin 44   */
#define   CHAR3B        (13)    /* LCD Pin 43   */
#define   CHAR3C        (14)    /* LCD Pin 42   */
#define   CHAR3D        (15)    /* LCD Pin 41   */
#define   CHAR4A        (16)    /* LCD Pin 40   */
#define   CHAR4B        (17)    /* LCD Pin 39   */
#define   CHAR4C        (18)    /* LCD Pin 38   */
#define   CHAR4D        (19)    /* LCD Pin 37   */
#define   CHAR5A        (20)    /* LCD Pin 36   */
#define   CHAR5B        (21)    /* LCD Pin 35   */
#define   CHAR5C        (22)    /* LCD Pin 34   */
#define   CHAR5D        (23)    /* LCD Pin 33   */
#define   CHAR6A        (24)    /* LCD Pin 32   */
#define   CHAR6B        (25)    /* LCD Pin 31   */
#define   CHAR6C        (26)    /* LCD Pin 30   */
#define   CHAR6D        (27)    /* LCD Pin 29   */
#define   CHAR7A        (28)    /* LCD Pin 13   */
#define   CHAR7B        (29)    /* LCD Pin 14   */
#define   CHAR7C        (30)    /* LCD Pin 15   */
#define   CHAR7D        (31)    /* LCD Pin 16   */
#define   CHAR8A        (32)    /* LCD Pin 17   */
#define   CHAR8B        (33)    /* LCD Pin 18   */
#define   CHAR8C        (34)    /* LCD Pin 19   */
#define   CHAR8D        (35)    /* LCD Pin 20   */
#define   CHAR9A        (36)    /* LCD Pin 21   */
#define   CHAR9B        (37)    /* LCD Pin 22   */
#define   CHAR9C        (38)    /* LCD Pin 23   */
#define   CHAR9D        (39)    /* LCD Pin 24   */

/* 
** Map segment to COM mask 
*/
#define  SEGB   0x01
#define  SEGC   0x02

#define  SEGH   0x01
#define  SEGF   0x02
#define  SEGE   0x04
#define  SEGN   0x08

#define  SEGA   0x01
#define  SEGJ   0x02
#define  SEGG   0x04
#define  SEGM   0x08

#define  SEGK   0x01
#define  SEGL   0x02
#define  SEGD   0x04


/* 
** definition of segment masks for specific character
*/                                                
#define  _0            ( SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+ SEGK) , ( SEGC+ SEGB)     //Char = 0,   offset=0
#define  _1            (!SEGN+!SEGE+!SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = 1,   offset=4
#define  _2            (!SEGN+ SEGE+!SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , (!SEGC+ SEGB)     //Char = 2,   offset=8
#define  _3            (!SEGN+!SEGE+!SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = 3,   offset=12
#define  _4            (!SEGN+!SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+!SEGA) , (!SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = 4,   offset=16
#define  _5            (!SEGN+!SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+!SEGB)     //Char = 5,   offset=20
#define  _6            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+!SEGB)     //Char = 6,   offset=24
#define  _7            (!SEGN+!SEGE+!SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+ SEGA) , (!SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = 7,   offset=28
#define  _8            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = 8,   offset=32
#define  _9            (!SEGN+!SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = 9,   offset=36
#define  _AllOff       (!SEGN+!SEGE+!SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = 2Points,   offset=40
#define  _SemiColon    (!SEGN+!SEGE+!SEGF+!SEGH) , ( SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+ SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = Semicolon,   offset=44
#define  _MinusThan    ( SEGN+!SEGE+!SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , ( SEGD+!SEGL+ SEGK) , (!SEGC+!SEGB)     //Char = LessThan,   offset=48
#define  _Equal        (!SEGN+!SEGE+!SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+!SEGA) , ( SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = Equal,   offset=52
#define  _GreaterThan  (!SEGN+!SEGE+!SEGF+ SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , ( SEGD+ SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = GreaterThan,   offset=56
#define  _Question     ( SEGN+!SEGE+!SEGF+ SEGH) , (!SEGM+!SEGG+!SEGJ+ SEGA) , (!SEGD+!SEGL+ SEGK) , (!SEGC+!SEGB)     //Char = Question,   offset=60
#define  _AllOn        ( SEGN+ SEGE+ SEGF+ SEGH) , ( SEGM+ SEGG+ SEGJ+ SEGA) , ( SEGD+ SEGL+ SEGK) , ( SEGC+ SEGB)     //Char = At,  offset=64
#define  _A            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , (!SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = A,   offset=68
#define  _B            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+!SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+!SEGB)     //Char = B,   offset=72
#define  _C            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = C,   offset=76
#define  _D            (!SEGN+ SEGE+!SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+!SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = D,   offset=80
#define  _E            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = E,   offset=84
#define  _F            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , (!SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = F,   offset=88
#define  _G            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+!SEGB)     //Char = G,   offset=92
#define  _H            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+!SEGA) , (!SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = H,   offset=96
#define  _I            (!SEGN+!SEGE+!SEGF+!SEGH) , ( SEGM+!SEGG+ SEGJ+!SEGA) , (!SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = I,   offset=100
#define  _J            (!SEGN+ SEGE+!SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = J,   offset=104
#define  _K            (!SEGN+!SEGE+!SEGF+!SEGH) , ( SEGM+!SEGG+ SEGJ+!SEGA) , (!SEGD+ SEGL+ SEGK) , (!SEGC+!SEGB)     //Char = K,   offset=108
#define  _L            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , ( SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = L,   offset=112
#define  _M            (!SEGN+ SEGE+ SEGF+ SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+!SEGL+ SEGK) , ( SEGC+ SEGB)     //Char = M,   offset=116
#define  _N            (!SEGN+ SEGE+ SEGF+ SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+ SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = N,   offset=120
#define  _O            (!SEGN+ SEGE+!SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+!SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+!SEGB)     //Char = O,   offset=124
#define  _P            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , (!SEGD+!SEGL+!SEGK) , (!SEGC+ SEGB)     //Char = P,   offset=128
#define  _Q            (!SEGN+!SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = Q,   offset=132
#define  _R            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , (!SEGD+ SEGL+!SEGK) , (!SEGC+ SEGB)     //Char = R,   offset=136
#define  _S            (!SEGN+!SEGE+ SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+!SEGB)     //Char = S,   offset=140
#define  _T            (!SEGN+!SEGE+!SEGF+!SEGH) , ( SEGM+!SEGG+ SEGJ+ SEGA) , (!SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = T,   offset=144
#define  _U            (!SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , ( SEGD+!SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = U,   offset=148
#define  _V            ( SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+!SEGL+ SEGK) , (!SEGC+!SEGB)
//Char = V,   offset=152
#define  _W            ( SEGN+ SEGE+ SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+ SEGL+!SEGK) , ( SEGC+ SEGB)     //Char = W,   offset=156
#define  _X            ( SEGN+!SEGE+!SEGF+ SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+ SEGL+ SEGK) , (!SEGC+!SEGB)     //Char = X,   offset=160
#define  _Y            (!SEGN+!SEGE+!SEGF+ SEGH) , ( SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+!SEGL+ SEGK) , (!SEGC+!SEGB)     //Char = Y,   offset=164
#define  _Z            ( SEGN+!SEGE+!SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+ SEGA) , ( SEGD+!SEGL+ SEGK) , (!SEGC+!SEGB)     //Char = Z,   offset=168
#define  _Slash        ( SEGN+!SEGE+!SEGF+!SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+!SEGL+ SEGK) , (!SEGC+!SEGB)     //Char = /,   offset=172
#define  _BackSlash    (!SEGN+!SEGE+!SEGF+ SEGH) , (!SEGM+!SEGG+!SEGJ+!SEGA) , (!SEGD+ SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = \,   offset=176
#define  _Plus         (!SEGN+!SEGE+!SEGF+!SEGH) , ( SEGM+ SEGG+ SEGJ+!SEGA) , (!SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = +,   offset=180
#define  _Minus        (!SEGN+!SEGE+!SEGF+!SEGH) , (!SEGM+ SEGG+!SEGJ+!SEGA) , (!SEGD+!SEGL+!SEGK) , (!SEGC+!SEGB)     //Char = -,   offset=184

#endif /* __LCD_M51EMDEMO_PRV_H */
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
* $FileName: init_tchres.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the definition for the baud rate for the I2C
*   channel
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"

#define FULL_SCALE 0x0FFF  

/* Initialization structure */
TCHRES_INIT_STRUCT _bsp_tchscr_resisitve_init = {
    /* structure with pins connected to touch_screen detection */
    {
      BSP_LCD_TCHRES_X_PLUS,       /* x + gpio pin definition */
      BSP_LCD_TCHRES_X_MINUS,      /* x - gpio pin definition */
      BSP_LCD_TCHRES_Y_PLUS,       /* y + gpio pin definition */
      BSP_LCD_TCHRES_Y_MINUS,      /* y - gpio pin definition */
      BSP_LCD_X_PLUS_ADC_CHANNEL, /* X+ ADC channel */
      BSP_LCD_Y_PLUS_ADC_CHANNEL, /* Y+ ADC channel */
   },
   
   /* Adc limits struct */
   {
       FULL_SCALE,           /* FULL_SCALE */
       (FULL_SCALE / 6),     /* X_TOUCH_MIN */
       (FULL_SCALE / 6),     /* Y_TOUCH_MIN  */
       (FULL_SCALE * 4 / 2), /* X_TOUCH_MAX */
       (FULL_SCALE * 4 / 2), /* Y_TOUCH_MAX */
   },
};
/* EOF */

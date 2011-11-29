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
* $FileName: init_i2c5.c$
* $Version : 3.5.1.0$
* $Date    : Nov-30-2009$
*
* Comments:
*
*   This file contains the definition for the baud rate for the I2C
*   channel
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"

const MCF54XX_I2C_INIT_STRUCT _bsp_i2c5_init = {
   5,                      /* I2C channel    */
   BSP_I2C5_MODE,          /* I2C mode       */ 
   BSP_I2C5_ADDRESS,       /* I2C address    */ 
   BSP_I2C5_BAUD_RATE,     /* I2C baud rate  */ 
   BSP_I2C5_INT_LEVEL,     /* I2C int level  */ 
   BSP_I2C5_TX_BUFFER_SIZE,/* I2C int tx buf */
   BSP_I2C5_RX_BUFFER_SIZE /* I2C int rx buf */
};

/* EOF */
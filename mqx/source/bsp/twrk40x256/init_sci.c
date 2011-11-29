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
* $FileName: init_sci.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the definition for the baud rate for the serial
*   channel
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
//#include <mcf51xx_sci.h>          /* SCI */

const KUART_INIT_STRUCT _bsp_sci0_init = {
   /* queue size         */ BSPCFG_SCI0_QUEUE_SIZE,
   /* Channel            */ 0,
   /* Clock Speed        */ BSP_SYSTEM_CLOCK,       // only SCI0 operate on core clock
   /* Baud rate          */ BSPCFG_SCI0_BAUD_RATE,
   /* RX/TX Int vect     */ INT_UART0_RX_TX,
   /* ERR Int vect       */ INT_UART0_ERR,
   /* RX/TX priority     */ 3,
   /* ERR priority       */ 4
};

const KUART_INIT_STRUCT _bsp_sci1_init = {
   /* queue size         */ BSPCFG_SCI1_QUEUE_SIZE,
   /* Channel            */ 1,
   /* Clock Speed        */ BSP_BUS_CLOCK,       // only SCI0 operate on core clock
   /* Baud rate          */ BSPCFG_SCI1_BAUD_RATE,
   /* RX/TX Int vect     */ INT_UART1_RX_TX,
   /* ERR Int vect       */ INT_UART1_ERR,
   /* RX/TX priority     */ 3,
   /* ERR priority       */ 4
};

const KUART_INIT_STRUCT _bsp_sci2_init = {
   /* queue size         */ BSPCFG_SCI2_QUEUE_SIZE,
   /* Channel            */ 2,
   /* Clock Speed        */ BSP_BUS_CLOCK,       // only SCI0 operate on core clock
   /* Baud rate          */ BSPCFG_SCI2_BAUD_RATE,
   /* RX/TX Int vect     */ INT_UART2_RX_TX,
   /* ERR Int vect       */ INT_UART2_ERR,
   /* RX/TX priority     */ 3,
   /* ERR priority       */ 4
};

const KUART_INIT_STRUCT _bsp_sci3_init = {
   /* queue size         */ BSPCFG_SCI3_QUEUE_SIZE,
   /* Channel            */ 3,
   /* Clock Speed        */ BSP_BUS_CLOCK,       // only SCI0 operate on core clock
   /* Baud rate          */ BSPCFG_SCI3_BAUD_RATE,
   /* RX/TX Int vect     */ INT_UART3_RX_TX,
   /* ERR Int vect       */ INT_UART3_ERR,
   /* RX/TX priority     */ 3,
   /* ERR priority       */ 4
};

const KUART_INIT_STRUCT _bsp_sci4_init = {
   /* queue size         */ BSPCFG_SCI4_QUEUE_SIZE,
   /* Channel            */ 4,
   /* Clock Speed        */ BSP_BUS_CLOCK,       // only SCI0 operate on core clock
   /* Baud rate          */ BSPCFG_SCI4_BAUD_RATE,
   /* RX/TX Int vect     */ INT_UART4_RX_TX,
   /* ERR Int vect       */ INT_UART4_ERR,
   /* RX/TX priority     */ 3,
   /* ERR priority       */ 4
};

const KUART_INIT_STRUCT _bsp_sci5_init = {
   /* queue size         */ BSPCFG_SCI5_QUEUE_SIZE,
   /* Channel            */ 5,
   /* Clock Speed        */ BSP_BUS_CLOCK,       // only SCI0 operate on core clock
   /* Baud rate          */ BSPCFG_SCI5_BAUD_RATE,
   /* RX/TX Int vect     */ INT_UART5_RX_TX,
   /* ERR Int vect       */ INT_UART5_ERR,
   /* RX/TX priority     */ 3,
   /* ERR priority       */ 4
};

/* EOF */

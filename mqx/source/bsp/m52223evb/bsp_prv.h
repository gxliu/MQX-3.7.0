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
* $FileName: bsp_prv.h$
* $Version : 3.4.7.0$
* $Date    : Aug-24-2009$
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for initialization of the card.
*
*END************************************************************************/

#ifndef _bsp_prv_h_
#define _bsp_prv_h_

#ifdef __cplusplus
extern "C" {
#endif


/*
**  FUNCTION PROTOTYPES
*/

extern void mcf5222_init(void);

extern void __cpp_init(void);

extern void _bsp_exit_handler(void);
extern void _bsp_timer_isr(pointer);


/* I/O initialization controlled by initialization structures for each
** channel
*/

extern MCF52XX_UART_SERIAL_INIT_STRUCT  _bsp_uart0_init;
extern MCF52XX_UART_SERIAL_INIT_STRUCT  _bsp_uart1_init;
extern MCF52XX_UART_SERIAL_INIT_STRUCT  _bsp_uart2_init;

extern MCF52XX_I2C_INIT_STRUCT _bsp_i2c0_init;

extern MCF5XXX_QSPI_INIT_STRUCT _bsp_qspi0_init;

#ifdef __cplusplus
}
#endif

#endif
/* EOF */


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
* $Version : 3.5.28.0$
* $Date    : Dec-10-2009$
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

extern void mcf5225_init(void);

#if BSPCFG_ENABLE_CPP
extern void __cpp_init(void);
#endif

#if MQX_EXIT_ENABLED
extern void _bsp_exit_handler(void);
#endif
extern void _bsp_timer_isr(pointer);


/* I/O initialization controlled by initialization structures for each
** channel
*/

extern const MCF52XX_UART_SERIAL_INIT_STRUCT  _bsp_uart0_init;
extern const MCF52XX_UART_SERIAL_INIT_STRUCT  _bsp_uart1_init;
extern const MCF52XX_UART_SERIAL_INIT_STRUCT  _bsp_uart2_init;

extern const MCF52XX_I2C_INIT_STRUCT _bsp_i2c0_init;
extern const MCF52XX_I2C_INIT_STRUCT _bsp_i2c1_init;

extern const MCF5XXX_QSPI_INIT_STRUCT _bsp_qspi0_init;

extern const PCCARDFLEXBUS_INIT_STRUCT  _bsp_cfcard_init;

extern void _bsp_flexbus_pccard_setup (const uint_32 base_address);


#ifdef __cplusplus
}
#endif

#endif
/* EOF */


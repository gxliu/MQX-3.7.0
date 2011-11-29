/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved                       
*
* Copyright (c) 1989-2008 ARC International;
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
* $Version : 3.5.10.0$
* $Date    : Oct-29-2009$
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for initialization of the card.
*   $Header:bsp_prv.h, 4, 3/15/2007 11:19:19 AM, Jim Gard$
*   $NoKeywords$
*
*END************************************************************************/

#ifndef _bsp_prv_h_
#define _bsp_prv_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

/*
**  FUNCTION PROTOTYPES
*/
void mcf5445_init(void);

#if BSPCFG_ENABLE_CPP
extern void    __cpp_init(void);
#endif
//extern void    _ExitProcess(void); /* Codewarrior */

extern void    _bsp_enet_gpio_init(uint_32 fecnum, uint_32 flags);
extern void    _bsp_dspi_gpio_init(void);
extern void    _bsp_exit_handler(void);
extern void    _bsp_timer_isr(pointer);
extern uint_32 _bsp_uart_frequency(void);

extern void _bsp_spin_time(uint_32);    // Wait by spinning for N microseconds

/* I/O initialization controlled by initialization structures for each
** channel
*/

extern MCF54XX_UART_SERIAL_INIT_STRUCT  _bsp_uart0_init;
extern MCF54XX_UART_SERIAL_INIT_STRUCT  _bsp_uart1_init;
extern MCF54XX_UART_SERIAL_INIT_STRUCT  _bsp_uart2_init;

extern MCF54XX_I2C_INIT_STRUCT _bsp_i2c0_init;

extern MCF5XXX_DSPI_INIT_STRUCT _bsp_dspi0_init;

//extern PSC_SERIAL_INIT_STRUCT _bsp_psc0_init, _bsp_psc1_init;
extern FLASHX_INIT_STRUCT _bsp_flashx0_init;
extern FLASHX_INIT_STRUCT _bsp_flashx1_init;


#ifdef __cplusplus
}
#endif

#endif
/* EOF */


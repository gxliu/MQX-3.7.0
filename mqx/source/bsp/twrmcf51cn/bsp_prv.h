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
* $Version : 3.7.9.0$
* $Date    : Mar-23-2011$
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

extern void mcf51CNxx_init(void);

extern void __cpp_init(void);

extern void _bsp_exit_handler(void);
extern void _bsp_timer_isr(pointer);

extern boolean _bsp_enet_init(uint_32);
extern uint_32 _bsp_enet_get_speed(uint_32);
extern boolean _bsp_enet_get_link_status(uint_32);
extern void _bsp_flexbus_lcd_setup (const uint_32 base_address);
 
/* I/O initialization controlled by initialization structures for each
** channel
*/

extern MCF51XX_SCI_INIT_STRUCT _bsp_sci0_init;
extern MCF51XX_SCI_INIT_STRUCT _bsp_sci1_init;
extern MCF51XX_SCI_INIT_STRUCT _bsp_sci2_init;

extern MCF51XX_I2C_INIT_STRUCT _bsp_i2c0_init;
extern MCF51XX_I2C_INIT_STRUCT _bsp_i2c1_init;

extern MCF5XXX_SPI8_INIT_STRUCT _bsp_spi0_init;
extern MCF5XXX_SPI8_INIT_STRUCT _bsp_spi1_init;

extern const PCCARDFLEXBUS_INIT_STRUCT  _bsp_cfcard_init;

extern void _bsp_flexbus_pccard_setup (const uint_32 base_address);
/* to be used in next MQX version
** extern TCHRES_INIT_STRUCT _bsp_tchscr_resisitve_init;
*/
#ifdef __cplusplus
}
#endif

#endif
/* EOF */


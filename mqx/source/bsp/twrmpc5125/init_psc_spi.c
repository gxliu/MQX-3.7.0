/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved                       
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $FileName: init_psc_spi.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the initialization parameters for the serial port.
*
*END************************************************************************/



#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"

const MPC512X_SPI_INIT_STRUCT _bsp_spi0_init = {
   /* Channel #                         */ 0,
   /* Chip select                       */ MPC512X_SPI_CS0,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC0_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC0_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC0_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC0_DEFAULT_OUTPUT_ALARM_SIZE
};

const MPC512X_SPI_INIT_STRUCT _bsp_spi1_init = {
   /* Channel #                         */ 1,
   /* Chip select                       */ MPC512X_SPI_CS1,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC1_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC1_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC1_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC1_DEFAULT_OUTPUT_ALARM_SIZE
};

const MPC512X_SPI_INIT_STRUCT _bsp_spi2_init = {
   /* Channel #                         */ 2,
   /* Chip select                       */ MPC512X_SPI_CS2,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC2_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC2_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC2_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC2_DEFAULT_OUTPUT_ALARM_SIZE
};

const MPC512X_SPI_INIT_STRUCT _bsp_spi3_init = {
   /* Channel #                         */ 3,
   /* Chip select                       */ MPC512X_SPI_CS3,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC3_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC3_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC3_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC3_DEFAULT_OUTPUT_ALARM_SIZE
};

const MPC512X_SPI_INIT_STRUCT _bsp_spi4_init = {
   /* Channel #                         */ 4,
   /* Chip select                       */ MPC512X_SPI_CS4,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC4_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC4_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC4_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC4_DEFAULT_OUTPUT_ALARM_SIZE
};

const MPC512X_SPI_INIT_STRUCT _bsp_spi5_init = {
   /* Channel #                         */ 5,
   /* Chip select                       */ MPC512X_SPI_CS5,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC5_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC5_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC5_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC5_DEFAULT_OUTPUT_ALARM_SIZE
};

const MPC512X_SPI_INIT_STRUCT _bsp_spi6_init = {
   /* Channel #                         */ 6,
   /* Chip select                       */ MPC512X_SPI_CS6,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC6_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC6_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC6_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC6_DEFAULT_OUTPUT_ALARM_SIZE
};

const MPC512X_SPI_INIT_STRUCT _bsp_spi7_init = {
   /* Channel #                         */ 7,
   /* Chip select                       */ MPC512X_SPI_CS7,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC7_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC7_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC7_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC7_DEFAULT_OUTPUT_ALARM_SIZE
};

const MPC512X_SPI_INIT_STRUCT _bsp_spi8_init = {
   /* Channel #                         */ 8,
   /* Chip select                       */ MPC512X_SPI_CS8,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC8_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC8_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC8_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC8_DEFAULT_OUTPUT_ALARM_SIZE
};

const MPC512X_SPI_INIT_STRUCT _bsp_spi9_init = {
   /* Channel #                         */ 9,
   /* Chip select                       */ MPC512X_SPI_CS9,
   /* Transfer mode                     */ SPI_DEVICE_MASTER_MODE,
   /* Baud rate for the channel         */ BSP_SPI_BAUDRATE,
   /* Clock speed of MCLK               */ BSP_PSC_MCLK_CLOCK,
   /* SPI clock phase                   */ SPI_CLK_POL_PHA_MODE0,
   /* Maximum size of each receive      */ BSP_SPI_RX_BUFFER_SIZE,
   /* Maximum size of each transmit     */ BSP_SPI_TX_BUFFER_SIZE,
   /* Interrupt vector                  */ MPC5125_PSC9_VECTOR,
   /* Queue Size                        */ BSPCFG_PSC9_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size                  */ BSPCFG_PSC9_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size                 */ BSPCFG_PSC9_DEFAULT_OUTPUT_ALARM_SIZE
};

/* EOF */

/**HEADER********************************************************************
* 
* Copyright (c) 2009 Freescale Semiconductor;
* All Rights Reserved                       
*
* Copyright (c) 1989-2009 ARC International;
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
* $FileName: init_spi0.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the definition for the baud rate for the SPI
*   channel
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>

/*
** parameters of spi0 initialization
*/

const MCF5XXX_SPI8_INIT_STRUCT _bsp_spi0_init = { 
   0,                            /* SPI channel                     */    
   MCF5XXX_SPI8_CS0,             /* Default chip select             */   
   BSP_BUS_CLOCK,                /* Clock Speed                     */         
   BSP_SPI_BAUDRATE,             /* SPI Baud rate register value    */ 
   BSP_SPI_RX_BUFFER_SIZE,       /* Rx Buffer Size (interrupt only) */ 
   BSP_SPI_TX_BUFFER_SIZE,       /* Tx Buffer Size (interrupt only) */ 
   MCF51AC_INT_Vspi1,            /* Int Vector                      */
   SPI_DEVICE_MASTER_MODE,       /* Transfer mode                   */  
   SPI_CLK_POL_PHA_MODE0         /* SPI clock phase                 */   
};

/* EOF */
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
* $FileName: init_spi0.c$
* $Version : 3.7.2.0$
* $Date    : Dec-6-2010$
*
* Comments:
*
*   This file contains the initialization definition for QSPI driver
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <spi.h>
#include <spi_mcf5xxx_qspi.h>

/*
** parameters of spi0 initialization
*/

const MCF5XXX_QSPI_INIT_STRUCT _bsp_qspi0_init = { 
   0,                            /* SPI channel                     */
   MCF5XXX_QSPI_QDR_QSPI_CS0,    /* Chip Select 0                   */
   SPI_DEVICE_MASTER_MODE,       /* Transfer mode                   */
   BSP_QSPI_BAUDRATE,            /* SPI Baud rate register value    */
   BSP_SYSTEM_CLOCK,             /* Clock Speed                     */
   SPI_CLK_POL_PHA_MODE0,        /* SPI clock phase                 */
   BSP_QSPI_RX_BUFFER_SIZE,      /* Rx Buffer Size (interrupt only) */
   BSP_QSPI_TX_BUFFER_SIZE       /* Tx Buffer Size (interrupt only) */
};

#ifndef __spi_dspi_prv_h__ 
#define __spi_dspi_prv_h__
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
* $FileName: spi_dspi_prv.h$
* $Version : 3.7.3.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains definitions private to the SPI driver.
*
*END************************************************************************/

#include "spi.h"
#include "spi_dspi.h"

/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

/*
** MCF5XXX_DSPI_INFO_STRUCT
** Run time state information for each spi channel
*/
typedef struct dspi_info_struct
{
   /* The spi device register */
   SPI_MemMapPtr                     DSPI_PTR;

   /* The current init values for this port */
   DSPI_INIT_STRUCT                  INIT;

   /* The previous vector, interrupt handler and data */
   void                  (_CODE_PTR_ OLD_ISR)(pointer);
   pointer                           OLD_ISR_DATA;

   /* Receive/transmit flag */
   uint_16                           RECEIVING;
   
   /* Difference between transmitted and received bytes */
   uint_16                           ONTHEWAY;
   
   /* Number of bytes requested to receive */
   uint_32                           RX_REQUEST;
  
   /* Pointer to the buffer to use for Tx/Rx data */
   uchar_ptr                         RX_BUFFER;

   /* Rx write index */
   volatile uint_32                  RX_IN;

   /* Rx read index */
   volatile uint_32                  RX_OUT;

   /* Pointer to the buffer to use for current Tx data */
   uchar_ptr                         TX_BUFFER;

   /* Tx write index */
   uint_32                           TX_IN;

   /* Tx read index */
   uint_32                           TX_OUT;
   
   /* Chip select used during transfers */
   uint_32                           CS;

   /* Previous state of chip select */
   uint_32                           CS_ACTIVE;

   /* Chip select set callback */
   SPI_CS_CALLBACK                   CS_CALLBACK[DSPI_CS_COUNT];

   /* User data for callback */
   pointer                           CS_USERDATA[DSPI_CS_COUNT];

   /* Statistical information */
   SPI_STATISTICS_STRUCT             STATS;

} DSPI_INFO_STRUCT, _PTR_ DSPI_INFO_STRUCT_PTR;


#define SPI_CTAR_FMSZ_GET(x)    (((x) & SPI_CTAR_FMSZ_MASK) >> SPI_CTAR_FMSZ_SHIFT)
#define SPI_CTAR_PBR_GET(x)     (((x) & SPI_CTAR_PBR_MASK) >> SPI_CTAR_PBR_SHIFT)
#define SPI_CTAR_BR_GET(x)      (((x) & SPI_CTAR_BR_MASK) >> SPI_CTAR_BR_SHIFT)
#define SPI_SR_TXCTR_GET(x)     (((x) & SPI_SR_TXCTR_MASK) >> SPI_SR_TXCTR_SHIFT)
#define SPI_PUSHR_PCS_GET(x)    (((x) & SPI_PUSHR_PCS_MASK) >> SPI_PUSHR_PCS_SHIFT)
#define SPI_PUSHR_CTAS_GET(x)   (((x) & SPI_PUSHR_CTAS_MASK) >> SPI_PUSHR_CTAS_SHIFT)
#define SPI_PUSHR_TXDATA_GET(x) (((x) & SPI_PUSHR_TXDATA_MASK) >> SPI_PUSHR_TXDATA_SHIFT)
#define SPI_MCR_PCSIS_GET(x)    (((x) & SPI_MCR_PCSIS_MASK) >> SPI_MCR_PCSIS_SHIFT)
#define SPI_POPR_RXDATA_GET(x)  (((x) & SPI_POPR_RXDATA_MASK) >> SPI_POPR_RXDATA_SHIFT) 


#endif
/* EOF */

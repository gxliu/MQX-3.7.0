#ifndef __spi_mcf5xxx_dspi_h__
#define __spi_mcf5xxx_dspi_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2009 Freescale Semiconductor;
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
* $FileName: spi_mcf5xxx_dspi.h$
* $Version : 3.6.8.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for the SPI driver
*
*END************************************************************************/


/*--------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

#define MCF5XXX_DSPI_INT_GLOBAL     (0) // Logical or of all following
#define MCF5XXX_DSPI_INT_EOQF       (1) // End of queue interrupt
#define MCF5XXX_DSPI_INT_TFFF       (2) // Transmit FIFO fill interrupt
#define MCF5XXX_DSPI_INT_TCF        (3) // Transfer complete interrupt
#define MCF5XXX_DSPI_INT_TFUF       (4) // Transmit FIFO underflow interrupt
#define MCF5XXX_DSPI_INT_RFDF       (5) // Receive FIFO not empty interrupt
#define MCF5XXX_DSPI_INT_RFOF       (6) // Receive FIFO overflow interrupt
#define MCF5XXX_DSPI_INT_RFOF_TFUF  (7) // Receive FIFO overflow or transmit FIFO underflow interrupt

#define MCF5XXX_DSPI_CS_COUNT       (8)


/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

/*
** MCF5XXX_DSPI_INIT_STRUCT
**
** This structure defines the initialization parameters to be used
** when a spi port is initialized.
*/
typedef struct mcf5xxx_dspi_init_struct
{
   /* spi channel number */
   uint_32 CHANNEL;

   /* The SPI default chip select */
   uint_32 CS; 
   
   /* The SPI transfer mode */
   uint_32 TRANSFER_MODE;

   /* The Baud rate for the channel */
   uint_32 BAUD_RATE;

   /* The clock speed of CPU */
   uint_32 CLOCK_SPEED;

   /* The SPI clock phase and polarity mode */
   uint_32 CLOCK_POL_PHASE; 

   /* The maximum size of each receive */
   uint_32 RX_BUFFER_SIZE;

   /* The maximum size of each transmit */
   uint_32 TX_BUFFER_SIZE;
   
} MCF5XXX_DSPI_INIT_STRUCT, _PTR_ MCF5XXX_DSPI_INIT_STRUCT_PTR;

typedef const MCF5XXX_DSPI_INIT_STRUCT _PTR_ MCF5XXX_DSPI_INIT_STRUCT_CPTR;


/*--------------------------------------------------------------------------*/
/* 
**                        FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

extern _mqx_uint _mcf5xxx_dspi_polled_install(char_ptr,MCF5XXX_DSPI_INIT_STRUCT_CPTR);
extern uint_32 _mcf5xxx_dspi_int_install(char_ptr, MCF5XXX_DSPI_INIT_STRUCT_CPTR);
extern pointer _bsp_get_dspi_base_address(uint_8);
extern uint_32 _bsp_get_dspi_vector(uint_8,uint_8);

#ifdef __cplusplus
}
#endif


#endif 

/* EOF */

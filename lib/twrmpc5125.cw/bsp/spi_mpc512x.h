#ifndef __spi_mpc512x_spi_h__
#define __spi_mpc512x_spi_h__
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
* $FileName: spi_mpc512x.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
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

#define MPC512X_SPI_INT_GLOBAL     (0) // Logical or of all following
#define MPC512X_SPI_INT_EOQF       (1) // End of queue interrupt
#define MPC512X_SPI_INT_TFFF       (2) // Transmit FIFO fill interrupt
#define MPC512X_SPI_INT_TCF        (3) // Transfer complete interrupt
#define MPC512X_SPI_INT_TFUF       (4) // Transmit FIFO underflow interrupt
#define MPC512X_SPI_INT_RFDF       (5) // Receive FIFO not empty interrupt
#define MPC512X_SPI_INT_RFOF       (6) // Receive FIFO overflow interrupt
#define MPC512X_SPI_INT_RFOF_TFUF  (7) // Receive FIFO overflow or transmit FIFO underflow interrupt

#define MPC512X_SPI_CS_COUNT (10)
#define MPC512X_SPI_CS0      (1 << 0)
#define MPC512X_SPI_CS1      (1 << 1)
#define MPC512X_SPI_CS2      (1 << 2)
#define MPC512X_SPI_CS3      (1 << 3)
#define MPC512X_SPI_CS4      (1 << 4)
#define MPC512X_SPI_CS5      (1 << 5)
#define MPC512X_SPI_CS6      (1 << 6)
#define MPC512X_SPI_CS7      (1 << 7)
#define MPC512X_SPI_CS8      (1 << 8)
#define MPC512X_SPI_CS9      (1 << 9)

/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

/*
** MPC512X_SPI_INIT_STRUCT
**
** This structure defines the initialization parameters to be used
** when a spi port is initialized.
*/
typedef struct mpc512x_spi_init_struct
{
   /* spi channel number */
   uint_32 CHANNEL;

   /* The SPI default chip select */
   uint_32 CS; 
   
   /* The SPI transfer mode */
   uint_32 TRANSFER_MODE;

   /* The Baud rate for the channel */
   uint_32 BAUD_RATE;

   /* The clock speed of MCLK */
   uint_32 CLOCK_SPEED;

   /* The SPI clock phase and polarity mode */
   uint_32 CLOCK_POL_PHASE; 

   /* The maximum size of each receive */
   uint_32 RX_BUFFER_SIZE;

   /* The maximum size of each transmit */
   uint_32 TX_BUFFER_SIZE;
   
   /* The interrupt vector to use if interrupt driven */
   uint_32 VECTOR;
   
   /* The serial I/O queue size to use to buffer Rx/Tx data. */
   uint_32 QUEUE_SIZE;

   /* Uart device driver Tx/Rx alarm settings for RxRDY/TxRDY. */
   uint_32 RX_QUEUE_ALARM;
   uint_32 TX_QUEUE_ALARM;
      
} MPC512X_SPI_INIT_STRUCT, _PTR_ MPC512X_SPI_INIT_STRUCT_PTR;

typedef const MPC512X_SPI_INIT_STRUCT _PTR_ MPC512X_SPI_INIT_STRUCT_CPTR;


/*--------------------------------------------------------------------------*/
/* 
**                        FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

extern _mqx_uint _mpc512x_spi_polled_install(char_ptr,MPC512X_SPI_INIT_STRUCT_CPTR);
extern uint_32 _mpc512x_spi_int_install(char_ptr, MPC512X_SPI_INIT_STRUCT_CPTR);
extern pointer _bsp_get_spi_base_address(uint_8);
extern uint_32 _bsp_get_spi_vector(uint_8,uint_8);

#ifdef __cplusplus
}
#endif


#endif 

/* EOF */

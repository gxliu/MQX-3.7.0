#ifndef __spi_mcf5xxx_spi16_h__
#define __spi_mcf5xxx_spi16_h__
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
* $FileName: spi_mcf5xxx_spi16.h$
* $Version : 3.5.2.0$
* $Date    : Dec-2-2009$
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for the SPI driver
*
*END************************************************************************/


/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

#define MCF5XXX_SPI16_CS_COUNT (4)
#define MCF5XXX_SPI16_CS0      (0x01)
#define MCF5XXX_SPI16_CS1      (0x02)
#define MCF5XXX_SPI16_CS2      (0x04)
#define MCF5XXX_SPI16_CS3      (0x08)


/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

/*
** MCF5XXX_SPI16_INIT_STRUCT
**
** This structure defines the initialization parameters to be used
** when a spi port is initialized.
*/
typedef struct mcf5xxx_spi16_init_struct
{
   /* The SPI channel number */
   uint_32 CHANNEL;

   /* The SPI default chip select mask */
   uint_32 CS;
   
   /* The clock speed of CPU */
   uint_32 CLOCK_SPEED;

   /* The Baud rate for the channel */
   uint_32 BAUD_RATE;

   /* The maximum size of each receive */
   uint_32 RX_BUFFER_SIZE;

   /* The maximum size of each transmit */
   uint_32 TX_BUFFER_SIZE;

   /* The interrupt vector to use if interrupt driven */
   uint_32 VECTOR;

   /* The SPI transfer mode */
   uint_32 TRANSFER_MODE;

   /* The SPI clock phase and polarity mode */
   uint_32 CLOCK_POL_PHASE;   

} MCF5XXX_SPI16_INIT_STRUCT, _PTR_ MCF5XXX_SPI16_INIT_STRUCT_PTR;

typedef const MCF5XXX_SPI16_INIT_STRUCT _PTR_ MCF5XXX_SPI16_INIT_STRUCT_CPTR; 

/*--------------------------------------------------------------------------*/
/* 
**                        FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

extern _mqx_uint _mcf5xxx_spi16_polled_install(char_ptr, MCF5XXX_SPI16_INIT_STRUCT_CPTR);
extern _mqx_uint _mcf5xxx_spi16_int_install(char_ptr, MCF5XXX_SPI16_INIT_STRUCT_CPTR);
extern pointer _bsp_get_spi_base_address(uint_8);
extern uint_32 _bsp_get_spi_vector(uint_8);

#ifdef __cplusplus
}
#endif


#endif 

/* EOF */

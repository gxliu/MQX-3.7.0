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
* $FileName: mcf5xxx_spi16.h$
* $Version : 3.6.2.0$
* $Date    : May-31-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf5xxx SPI16 module.
*
*END************************************************************************/

#ifndef __mcf5xxx_spi16_h__
#define __mcf5xxx_spi16_h__

#define __mcf5xxx_spi16_h__version "$Version:3.6.2.0$"
#define __mcf5xxx_spi16_h__date    "$Date:May-31-2010$"

#ifdef __cplusplus
extern "C" {
#endif

// bits in SPIxC1
#define MCF5XXX_SPI16_SPIC1_SPIE                  (1<<7)
#define MCF5XXX_SPI16_SPIC1_SPE                   (1<<6)
#define MCF5XXX_SPI16_SPIC1_SPTIE                 (1<<5)
#define MCF5XXX_SPI16_SPIC1_MSTR                  (1<<4)
#define MCF5XXX_SPI16_SPIC1_CPOL                  (1<<3)
#define MCF5XXX_SPI16_SPIC1_CPHA                  (1<<2)
#define MCF5XXX_SPI16_SPIC1_SSOE                  (1<<1)
#define MCF5XXX_SPI16_SPIC1_LSBFE                 (1<<0)

// bits in SPIxC2
#define MCF5XXX_SPI16_SPIC2_SPMIE                 (1<<7)
#define MCF5XXX_SPI16_SPIC2_SPIMODE               (1<<6)
#define MCF5XXX_SPI16_SPIC2_MODFEN                (1<<4)
#define MCF5XXX_SPI16_SPIC2_BIDIROE               (1<<3)
#define MCF5XXX_SPI16_SPIC2_SPISWAI               (1<<1)
#define MCF5XXX_SPI16_SPIC2_SPC0                  (1<<0)

// bits in SPIxBR
#define MCF5XXX_SPI16_SPIBR_SPPR(x)               ((x&0x7)<<4)
#define MCF5XXX_SPI16_SPIBR_SPR(x)                (x&0x0F)

// bits in SPIxS
#define MCF5XXX_SPI16_SPIS_SPRF                   (1<<7)
#define MCF5XXX_SPI16_SPIS_SPMF                   (1<<6)
#define MCF5XXX_SPI16_SPIS_SPTEF                  (1<<5)
#define MCF5XXX_SPI16_SPIS_MODF                   (1<<4)
#define MCF5XXX_SPI16_SPIS_RNFULLF                (1<<3)
#define MCF5XXX_SPI16_SPIS_TNEAREF                (1<<2)
#define MCF5XXX_SPI16_SPIS_TXFULLF                (1<<1)
#define MCF5XXX_SPI16_SPIS_RFIFOEF                (1<<0)

// bits in SPIxC3
#define MCF5XXX_SPI16_SPIC3_TNEAREF_MARK          (1<<5)
#define MCF5XXX_SPI16_SPIC3_RNFULL_MARK           (1<<4)
#define MCF5XXX_SPI16_SPIC3_INTCLR                (1<<3)
#define MCF5XXX_SPI16_SPIC3_TNEARIEN              (1<<2)
#define MCF5XXX_SPI16_SPIC3_RNFULLIEN             (1<<1)
#define MCF5XXX_SPI16_SPIC3_FIFOMODE              (1<<0)

// bits in SPIxCI
#define MCF5XXX_SPI16_SPICI_TXFERR                (1<<7)
#define MCF5XXX_SPI16_SPICI_RXFERR                (1<<6)
#define MCF5XXX_SPI16_SPICI_TXFOF                 (1<<5)
#define MCF5XXX_SPI16_SPICI_RXFOF                 (1<<4)
#define MCF5XXX_SPI16_SPICI_TNEAREFCI             (1<<3)
#define MCF5XXX_SPI16_SPICI_RNFULLFCI             (1<<2)
#define MCF5XXX_SPI16_SPICI_SPTEFCI               (1<<1)
#define MCF5XXX_SPI16_SPICI_SPRFCI                (1<<0)

typedef struct mcf5xxx_spi16_struct
{
  uchar   SPIC1;
  uchar   SPIC2;
  uchar   SPIBR;
  uchar   SPIS;
  uint_16 SPID;
  uint_16 SPIM;
  uchar   SPIC3;
  uchar   SPICI;
} MCF5XXX_SPI16_STRUCT, _PTR_ MCF5XXX_SPI16_STRUCT_PTR;
typedef volatile struct mcf5xxx_spi16_struct _PTR_ VMCF5XXX_SPI16_STRUCT_PTR;

typedef struct mcf5xxx_spi16_no_fifo_struct
{
  uchar   SPIC1;
  uchar   SPIC2;
  uchar   SPIBR;
  uchar   SPIS;
  uint_16 SPID;
  uint_16 SPIM;
} MCF5XXX_SPI16_NO_FIFO_STRUCT, _PTR_ MCF5XXX_SPI16_STRUCT_NO_FIFO_PTR;
typedef volatile struct mcf5xxx_spi16_no_fifo_struct _PTR_ VMCF5XXX_SPI16_NO_FIFO_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif

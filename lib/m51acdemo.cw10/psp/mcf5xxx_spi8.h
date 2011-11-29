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
* $FileName: mcf5xxx_spi8.h$
* $Version : 3.6.3.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf51xx SPI module.
*
*END************************************************************************/

#ifndef __mcf5xxx_spi8_h__
#define __mcf5xxx_spi8_h__

#define __mcf5xxx_spi8_h__version "$Version:3.6.3.0$"
#define __mcf5xxx_spi8_h__date    "$Date:Jun-4-2010$"

#ifdef __cplusplus
extern "C" {
#endif

// bits in SPIxC1
#define MCF5XXX_SPI8_SPIC1_SPIE                     (1<<7)
#define MCF5XXX_SPI8_SPIC1_SPE                      (1<<6)
#define MCF5XXX_SPI8_SPIC1_SPTIE                    (1<<5)
#define MCF5XXX_SPI8_SPIC1_MSTR                     (1<<4)
#define MCF5XXX_SPI8_SPIC1_CPOL                     (1<<3)
#define MCF5XXX_SPI8_SPIC1_CPHA                     (1<<2)
#define MCF5XXX_SPI8_SPIC1_SSOE                     (1<<1)
#define MCF5XXX_SPI8_SPIC1_LSBFE                    (1<<0)

// bits in SPIxC2
#define MCF5XXX_SPI8_SPIC2_MODFEN                   (1<<4)
#define MCF5XXX_SPI8_SPIC2_BIDIROE                  (1<<3)
#define MCF5XXX_SPI8_SPIC2_SPISWAI                  (1<<1)
#define MCF5XXX_SPI8_SPIC2_SPC0                     (1<<0)

// bits in SPIxBR
#define MCF5XXX_SPI8_SPIBR_SPPR(x)                  ((x&0x70)<<4)
#define MCF5XXX_SPI8_SPIBR_SPR(x)                   (x&0x0F)

// bits in SPIxS
#define MCF5XXX_SPI8_SPIS_SPRF                        (1<<7)
#define MCF5XXX_SPI8_SPIS_SPTEF                       (1<<5)
#define MCF5XXX_SPI8_SPIS_MODF                        (1<<4)

typedef struct mcf5xxx_spi8_struct
{
  uchar SPIC1;  /*** SPI1C1 - SPI1 Control Register 1; 0xFFFF81C0 ***/
  uchar SPIC2;  /*** SPI1C2 - SPI1 Control Register 2; 0xFFFF81C1 ***/
  uchar SPIBR;  /*** SPI1BR - SPI1 Baud Rate Register; 0xFFFF81C2 ***/
  uchar SPIS;   /*** SPI1S - SPI1 Status Register; 0xFFFF81C3 ***/
  uchar reserved01; 
  uchar SPID;   /*** SPI1D - SPI1 Data Register; 0xFFFF81C5 ***/ 
} MCF5XXX_SPI8_STRUCT, _PTR_ MCF5XXX_SPI8_STRUCT_PTR;
typedef volatile struct mcf5xxx_spi8_struct _PTR_ VMCF5XXX_SPI8_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif
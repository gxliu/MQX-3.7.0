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
* $FileName: mcf51ac_i2c.h$
* $Version : 3.6.1.0$
* $Date    : May-18-2010$
*
* Comments:
*
*   This file contains the type definitions for the I2C module of the
*   51AC Coldfire family.
*
*END************************************************************************/

#ifndef __mcf51ac_i2c_h__
    #define __mcf51ac_i2c_h__ 1

#define __mcf51ac_i2c_h__version "$Version:3.6.1.0$"
#define __mcf51ac_i2c_h__date    "$Date:May-18-2010$"


#define MCF51XX_IICA_AD1_MASK              (0x02)
#define MCF51XX_IICA_AD2_MASK              (0x04)
#define MCF51XX_IICA_AD3_MASK              (0x08)
#define MCF51XX_IICA_AD4_MASK              (0x10)
#define MCF51XX_IICA_AD5_MASK              (0x20)
#define MCF51XX_IICA_AD6_MASK              (0x40)
#define MCF51XX_IICA_AD7_MASK              (0x80)
#define MCF51XX_IICA_AD_1_MASK             (0xFE)
#define MCF51XX_IICA_AD_1_BITNUM           (0x01)

#define MCF51XX_IICF_ICR0_MASK             (0x01)
#define MCF51XX_IICF_ICR1_MASK             (0x02)
#define MCF51XX_IICF_ICR2_MASK             (0x04)
#define MCF51XX_IICF_ICR3_MASK             (0x08)
#define MCF51XX_IICF_ICR4_MASK             (0x10)
#define MCF51XX_IICF_ICR5_MASK             (0x20)
#define MCF51XX_IICF_MULT0_MASK            (0x40)
#define MCF51XX_IICF_MULT1_MASK            (0x80)
#define MCF51XX_IICF_ICR_MASK              (0x3F)
#define MCF51XX_IICF_ICR_BITNUM            (0x00)
#define MCF51XX_IICF_MULT_MASK             (0xC0)
#define MCF51XX_IICF_MULT_BITNUM           (0x06)
#define MCF51XX_IICF_SET(mult,icr)         ( (((mult)<<MCF51XX_IICF_MULT_BITNUM)&MCF51XX_IICF_MULT_MASK) \
                                           | (((icr)<<MCF51XX_IICF_ICR_BITNUM)&MCF51XX_IICF_ICR_MASK) )

#define MCF51XX_IIC_MUL_1                  (0x01)
#define MCF51XX_IIC_MUL_2                  (0x02)
#define MCF51XX_IIC_MUL_4                  (0x04)
                                          
#define MCF51XX_IIC_IICF_MUL_1             (0x00)
#define MCF51XX_IIC_IICF_MUL_2             (0x01)
#define MCF51XX_IIC_IICF_MUL_4             (0x03)

#define MCF51XX_IICC1_RSTA_MASK            (0x04)
#define MCF51XX_IICC1_TXAK_MASK            (0x08)
#define MCF51XX_IICC1_TX_MASK              (0x10)
#define MCF51XX_IICC1_MST_MASK             (0x20)
#define MCF51XX_IICC1_IICIE_MASK           (0x40)
#define MCF51XX_IICC1_IICEN_MASK           (0x80)

#define MCF51XX_IICS_RXAK_MASK             (0x01)
#define MCF51XX_IICS_IICIF_MASK            (0x02)
#define MCF51XX_IICS_SRW_MASK              (0x04)
#define MCF51XX_IICS_ARBL_MASK             (0x10)
#define MCF51XX_IICS_BUSY_MASK             (0x20)
#define MCF51XX_IICS_IAAS_MASK             (0x40)
#define MCF51XX_IICS_TCF_MASK              (0x80)

#define MCF51XX_IICD_DATA0_MASK            (0x01)
#define MCF51XX_IICD_DATA1_MASK            (0x02)
#define MCF51XX_IICD_DATA2_MASK            (0x04)
#define MCF51XX_IICD_DATA3_MASK            (0x08)
#define MCF51XX_IICD_DATA4_MASK            (0x10)
#define MCF51XX_IICD_DATA5_MASK            (0x20)
#define MCF51XX_IICD_DATA6_MASK            (0x40)
#define MCF51XX_IICD_DATA7_MASK            (0x80)

#define MCF51XX_IICC2_AD8_MASK             (0x01)
#define MCF51XX_IICC2_AD9_MASK             (0x02)
#define MCF51XX_IICC2_AD10_MASK            (0x04)
#define MCF51XX_IICC2_ADEXT_MASK           (0x40)
#define MCF51XX_IICC2_GCAEN_MASK           (0x80)
#define MCF51XX_IICC2_AD_8_MASK            (0x07)
#define MCF51XX_IICC2_AD_8_BITNUM          (0x00)

#define MCF51XX_IICSMB_SHTF_MASK           (0x04)
#define MCF51XX_IICSMB_SLTF_MASK           (0x08)
#define MCF51XX_IICSMB_TCKSEL_MASK         (0x10)
#define MCF51XX_IICSMB_SIICAEN_MASK        (0x20)
#define MCF51XX_IICSMB_ALERTEN_MASK        (0x40)
#define MCF51XX_IICSMB_FACK_MASK           (0x80)

#define MCF51XX_IICA2_SAD1_MASK            (0x02)
#define MCF51XX_IICA2_SAD2_MASK            (0x04)
#define MCF51XX_IICA2_SAD3_MASK            (0x08)
#define MCF51XX_IICA2_SAD4_MASK            (0x10)
#define MCF51XX_IICA2_SAD5_MASK            (0x20)
#define MCF51XX_IICA2_SAD6_MASK            (0x40)
#define MCF51XX_IICA2_SAD7_MASK            (0x80)
#define MCF51XX_IICA2_SAD_1_MASK           (0xFE)
#define MCF51XX_IICA2_SAD_1_BITNUM         (0x01)

#define MCF51XX_IICSLTL_SSLT0_MASK         (0x01)
#define MCF51XX_IICSLTL_SSLT1_MASK         (0x02)
#define MCF51XX_IICSLTL_SSLT2_MASK         (0x04)
#define MCF51XX_IICSLTL_SSLT3_MASK         (0x08)
#define MCF51XX_IICSLTL_SSLT4_MASK         (0x10)
#define MCF51XX_IICSLTL_SSLT5_MASK         (0x20)
#define MCF51XX_IICSLTL_SSLT6_MASK         (0x40)
#define MCF51XX_IICSLTL_SSLT7_MASK         (0x80)

#define MCF51XX_IICSLTH_SSLT8_MASK         (0x01)
#define MCF51XX_IICSLTH_SSLT9_MASK         (0x02)
#define MCF51XX_IICSLTH_SSLT10_MASK        (0x04)
#define MCF51XX_IICSLTH_SSLT11_MASK        (0x08)
#define MCF51XX_IICSLTH_SSLT12_MASK        (0x10)
#define MCF51XX_IICSLTH_SSLT13_MASK        (0x20)
#define MCF51XX_IICSLTH_SSLT14_MASK        (0x40)
#define MCF51XX_IICSLTH_SSLT15_MASK        (0x80)

#define MCF51XX_IICSLT_SSLT0_MASK          (0x0001)
#define MCF51XX_IICSLT_SSLT1_MASK          (0x0002)
#define MCF51XX_IICSLT_SSLT2_MASK          (0x0004)
#define MCF51XX_IICSLT_SSLT3_MASK          (0x0008)
#define MCF51XX_IICSLT_SSLT4_MASK          (0x0010)
#define MCF51XX_IICSLT_SSLT5_MASK          (0x0020)
#define MCF51XX_IICSLT_SSLT6_MASK          (0x0040)
#define MCF51XX_IICSLT_SSLT7_MASK          (0x0080)
#define MCF51XX_IICSLT_SSLT8_MASK          (0x0100)
#define MCF51XX_IICSLT_SSLT9_MASK          (0x0200)
#define MCF51XX_IICSLT_SSLT10_MASK         (0x0400)
#define MCF51XX_IICSLT_SSLT11_MASK         (0x0800)
#define MCF51XX_IICSLT_SSLT12_MASK         (0x1000)
#define MCF51XX_IICSLT_SSLT13_MASK         (0x2000)
#define MCF51XX_IICSLT_SSLT14_MASK         (0x4000)
#define MCF51XX_IICSLT_SSLT15_MASK         (0x8000)

#define MCF51XX_IICFLT_FLT0_MASK           (0x01)
#define MCF51XX_IICFLT_FLT1_MASK           (0x02)
#define MCF51XX_IICFLT_FLT2_MASK           (0x04)
#define MCF51XX_IICFLT_FLT_MASK            (0x07)
#define MCF51XX_IICFLT_FLT_BITNUM          (0x00)


/*
** MCF51AC_I2C_STRUCT
** This structure defines what one i2c register look like
*/

typedef struct mcf51ac_i2c_struct
{
   uchar  IICA1;   /*** IIC1A1 - IIC Address Register ***/
   uchar  IICF;    /*** IIC1F - IIC Frequency Divider Register ***/
   uchar  IICC1;   /*** IIC1C1 - IIC Control Register 1 ***/
   uchar  IICS;    /*** IIC1S - IIC Status Register ***/
   uchar  IICD;    /*** IIC1D - IIC Data I/O Register ***/
   uchar  IICC2;   /*** IIC1C2 - IIC Control Register 2 ***/
} MCF51AC_I2C_STRUCT, _PTR_ MCF51AC_I2C_STRUCT_PTR;

typedef volatile struct mcf51ac_i2c_struct _PTR_ VMCF51AC_I2C_STRUCT_PTR;

#endif  /* __mcf51ac_i2c_h__ */


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
* $FileName: mcf5xxx_dspi.h$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf5xxx DSPI module.
*
*END************************************************************************/


#ifndef __mcf5xxx_dspi_h__
#define __mcf5xxx_dspi_h__

#define __mcf5xxx_dspi_h__version "$Version:3.6.2.0$"
#define __mcf5xxx_dspi_h__date    "$Date:Jun-4-2010$"

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------*/
/*
** DSPI  (reg)isters bit set.
*/

/* Bit definitions and macros for MCF5XXX_DSPI_MCR */
#define MCF5XXX_DSPI_MCR_MSTR                       (0x80000000)
#define MCF5XXX_DSPI_MCR_CONT_SCKE                  (0x40000000)
#define MCF5XXX_DSPI_MCR_DCONF_MASK                 (0x30000000)
#define MCF5XXX_DSPI_MCR_FRZ                        (0x08000000)
#define MCF5XXX_DSPI_MCR_MTFE                       (0x04000000)
#define MCF5XXX_DSPI_MCR_PCSSE                      (0x02000000)
#define MCF5XXX_DSPI_MCR_ROOE                       (0x01000000)
#define MCF5XXX_DSPI_MCR_PCSIS7                     (0x00800000)
#define MCF5XXX_DSPI_MCR_PCSIS6                     (0x00400000)
#define MCF5XXX_DSPI_MCR_PCSIS5                     (0x00200000)
#define MCF5XXX_DSPI_MCR_PCSIS4                     (0x00100000)
#define MCF5XXX_DSPI_MCR_PCSIS3                     (0x00080000)
#define MCF5XXX_DSPI_MCR_PCSIS2                     (0x00040000)
#define MCF5XXX_DSPI_MCR_PCSIS1                     (0x00020000)
#define MCF5XXX_DSPI_MCR_PCSIS0                     (0x00010000)
#define MCF5XXX_DSPI_MCR_PCSIS_GET(reg)             (((reg) >> 16) & 0xFF)
#define MCF5XXX_DSPI_MCR_PCSIS_SET(val)             (((val) & 0xFF) << 16)
#define MCF5XXX_DSPI_MCR_MDIS                       (0x00004000)
#define MCF5XXX_DSPI_MCR_DIS_TXF                    (0x00002000)
#define MCF5XXX_DSPI_MCR_DIS_RXF                    (0x00001000)
#define MCF5XXX_DSPI_MCR_CLR_TXF                    (0x00000800)
#define MCF5XXX_DSPI_MCR_CLR_RXF                    (0x00000400)
#define MCF5XXX_DSPI_MCR_SMPL_PT_MASK               (0x00000300)
#define MCF5XXX_DSPI_MCR_SMPL_PT_2                  (0x00000200)
#define MCF5XXX_DSPI_MCR_SMPL_PT_1                  (0x00000100)
#define MCF5XXX_DSPI_MCR_SMPL_PT_0                  (0x00000000)
#define MCF5XXX_DSPI_MCR_HALT                       (0x00000001)

/* Bit definitions and macros for MCF5XXX_DSPI_TCR */
#define MCF5XXX_DSPI_TCR_GET(reg)                   ((reg) >> 16)
#define MCF5XXX_DSPI_TCR_SET(val)                   ((val) << 16)

/* Bit definitions and macros for MCF5XXX_DSPI_CTARn */
#define MCF5XXX_DSPI_CTAR_DBR                       (0x80000000)
#define MCF5XXX_DSPI_CTAR_FMSZ_GET(reg)             ((((reg) >> 27) & 0x0F) + 1)
#define MCF5XXX_DSPI_CTAR_FMSZ_SET(val)             (((val - 1) & 0x0F) << 27)
#define MCF5XXX_DSPI_CTAR_CPOL                      (0x04000000)
#define MCF5XXX_DSPI_CTAR_CPHA                      (0x02000000)
#define MCF5XXX_DSPI_CTAR_LSBFE                     (0x01000000)
#define MCF5XXX_DSPI_CTAR_PCSSCK_MASK               (0x00C00000)
#define MCF5XXX_DSPI_CTAR_PCSSCK_7                  (0x00C00000)
#define MCF5XXX_DSPI_CTAR_PCSSCK_5                  (0x00800000)
#define MCF5XXX_DSPI_CTAR_PCSSCK_3                  (0x00400000)
#define MCF5XXX_DSPI_CTAR_PCSSCK_1                  (0x00000000)
#define MCF5XXX_DSPI_CTAR_PASC_MASK                 (0x00300000)
#define MCF5XXX_DSPI_CTAR_PASC_7                    (0x00300000)
#define MCF5XXX_DSPI_CTAR_PASC_5                    (0x00200000)
#define MCF5XXX_DSPI_CTAR_PASC_3                    (0x00100000)
#define MCF5XXX_DSPI_CTAR_PASC_1                    (0x00000000)
#define MCF5XXX_DSPI_CTAR_PDT_MASK                  (0x000C0000)
#define MCF5XXX_DSPI_CTAR_PDT_7                     (0x000C0000)
#define MCF5XXX_DSPI_CTAR_PDT_5                     (0x00080000)
#define MCF5XXX_DSPI_CTAR_PDT_3                     (0x00040000)
#define MCF5XXX_DSPI_CTAR_PDT_1                     (0x00000000)
#define MCF5XXX_DSPI_CTAR_PBR_GET(reg)              (((reg) >> 16) & 0x03)
#define MCF5XXX_DSPI_CTAR_PBR_SET(val)              (((val) & 0x03) << 16)
#define MCF5XXX_DSPI_CTAR_CSSCK_GET(reg)            (((reg) >> 12) & 0x0F)
#define MCF5XXX_DSPI_CTAR_CSSCK_SET(val)            (((val) & 0x0F) << 12)
#define MCF5XXX_DSPI_CTAR_ASC_GET(reg)              (((reg) >> 8) & 0x0F)
#define MCF5XXX_DSPI_CTAR_ASC_SET(val)              (((val) & 0x0F) << 8)
#define MCF5XXX_DSPI_CTAR_DT_GET(reg)               (((reg) >> 4) & 0x0F)
#define MCF5XXX_DSPI_CTAR_DT_SET(val)               (((val) & 0x0F) << 4)
#define MCF5XXX_DSPI_CTAR_BR_GET(reg)               ((reg) & 0x0F)
#define MCF5XXX_DSPI_CTAR_BR_SET(val)               ((val) & 0x0F)

/* Bit definitions and macros for MCF5XXX_DSPI_SR */
#define MCF5XXX_DSPI_SR_TCF                         (0x80000000)
#define MCF5XXX_DSPI_SR_TXRXS                       (0x40000000)
#define MCF5XXX_DSPI_SR_EOQF                        (0x10000000)
#define MCF5XXX_DSPI_SR_TFUF                        (0x08000000)
#define MCF5XXX_DSPI_SR_TFFF                        (0x02000000)
#define MCF5XXX_DSPI_SR_RFOF                        (0x00080000)
#define MCF5XXX_DSPI_SR_RFDF                        (0x00020000)
#define MCF5XXX_DSPI_SR_TXCTR_GET(reg)              (((reg) >> 12) & 0x0F)
#define MCF5XXX_DSPI_SR_TXCTR_SET(val)              (((val) & 0x0F) << 12)
#define MCF5XXX_DSPI_SR_TXNXTPTR_GET(reg)           (((reg) >> 8) & 0x0F)
#define MCF5XXX_DSPI_SR_TXNXTPTR_SET(val)           (((val) & 0x0F) << 8)
#define MCF5XXX_DSPI_SR_RXCTR_GET(reg)              (((reg) >> 4) & 0x0F)
#define MCF5XXX_DSPI_SR_RXCTR_SET(val)              (((val) & 0x0F) << 4)
#define MCF5XXX_DSPI_SR_POPNXTPTR_GET(reg)          ((reg) & 0x0F)
#define MCF5XXX_DSPI_SR_POPNXTPTR_SET(val)          ((val) & 0x0F)

/* Bit definitions and macros for MCF5XXX_DSPI_RSER */
#define MCF5XXX_DSPI_RSER_TCFRE                     (0x80000000)
#define MCF5XXX_DSPI_RSER_EOQF_RE                   (0x10000000)
#define MCF5XXX_DSPI_RSER_TFUF_RE                   (0x08000000)
#define MCF5XXX_DSPI_RSER_TFFF_RE                   (0x02000000)
#define MCF5XXX_DSPI_RSER_TFFF_DIRS                 (0x01000000)
#define MCF5XXX_DSPI_RSER_RFOF_RE                   (0x00080000)
#define MCF5XXX_DSPI_RSER_RFDF_RE                   (0x00020000)
#define MCF5XXX_DSPI_RSER_RFDF_DIRS                 (0x00010000)

/* Bit definitions and macros for MCF5XXX_DSPI_PUSHR */
#define MCF5XXX_DSPI_PUSHR_CONT                     (0x80000000)
#define MCF5XXX_DSPI_PUSHR_CTAS_GET(reg)            (((reg) >> 28) & 0x07)
#define MCF5XXX_DSPI_PUSHR_CTAS_SET(val)            (((val) & 0x07) << 28)
#define MCF5XXX_DSPI_PUSHR_EOQ                      (0x08000000)
#define MCF5XXX_DSPI_PUSHR_CTCNT                    (0x04000000)
#define MCF5XXX_DSPI_PUSHR_PCS7                     (0x00800000)
#define MCF5XXX_DSPI_PUSHR_PCS6                     (0x00400000)
#define MCF5XXX_DSPI_PUSHR_PCS5                     (0x00200000)
#define MCF5XXX_DSPI_PUSHR_PCS4                     (0x00100000)
#define MCF5XXX_DSPI_PUSHR_PCS3                     (0x00080000)
#define MCF5XXX_DSPI_PUSHR_PCS2                     (0x00040000)
#define MCF5XXX_DSPI_PUSHR_PCS1                     (0x00020000)
#define MCF5XXX_DSPI_PUSHR_PCS0                     (0x00010000)
#define MCF5XXX_DSPI_PUSHR_PCS_GET(reg)             (((reg) >> 16) & 0xFF)
#define MCF5XXX_DSPI_PUSHR_PCS_SET(val)             (((val) & 0xFF) << 16)
#define MCF5XXX_DSPI_PUSHR_TXDATA_GET(reg)          ((reg) & 0xFFFF)
#define MCF5XXX_DSPI_PUSHR_TXDATA_SET(val)          ((val) & 0xFFFF)

/* Bit definitions and macros for MCF5XXX_DSPI_POPR */
#define MCF5XXX_DSPI_POPR_RXDATA_GET(reg)           (((uint_16)(reg)) & 0xFFFF)

/* Bit definitions and macros for MCF5XXX_DSPI_TXFRn */
#define MCF5XXX_DSPI_TXFR_TXCMD_GET(reg)            (((reg) >> 16) & 0xFFFF)
#define MCF5XXX_DSPI_TXFR_TXDATA_GET(reg)           ((reg) & 0xFFFF)

/* Bit definitions and macros for MCF5XXX_DSPI_RXFRn */
#define MCF5XXX_DSPI_RXFR_RXDATA_GET(reg)           ((reg) & 0xFFFF)


/*
** MCF5XXX_DSPI_STRUCT
** DSPI
*/
typedef struct mcf5xxx_dspi_struct
{
    uint_32 DSPI_MCR;
    uint_32 filler1;
    uint_32 DSPI_TCR;
    uint_32 DSPI_CTAR[8];
    uint_32 DSPI_SR;
    uint_32 DSPI_RSER;
    uint_32 DSPI_PUSHR;
    uint_32 DSPI_POPR;
    uint_32 DSPI_TXFR[16];
    uint_32 DSPI_RXFR[16];
    
} MCF5XXX_DSPI_STRUCT, _PTR_ MCF5XXX_DSPI_STRUCT_PTR;
typedef volatile struct mcf5xxx_dspi_struct _PTR_ VMCF5XXX_DSPI_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif
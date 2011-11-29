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
* $FileName: reg_nfc.h$
* $Version : 3.6.5.0$
* $Date    : Feb-10-2011$
*
* Comments:
*
*   This file contains the type definitions for the MCF5XXX NAND Flash
*   Controller (NFC).
*
*END************************************************************************/

#ifndef __reg_nfc_h__
#define __reg_nfc_h__

#define __reg_nfc_h__version "$Version:3.6.5.0$"
#define __reg_nfc_h__date    "$Date:Feb-10-2011$"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
** NFC  registers bit set.
*/
/* Bit definitions and macros for NFC_CMD1 */
#define NFC_CMD1_BYTE3(x)            (((x)&0xFF)<<0x10)
#define NFC_CMD1_BYTE2(x)            (((x)&0xFF)<<0x18)

/* Bit definitions and macros for NFC_CMD2 */
#define NFC_CMD2_BUSY_START          (0x1)
#define NFC_CMD2_BUFNO(x)            (((x)&0x3)<<0x1)
#define NFC_CMD2_CODE(x)             (((x)&0xFFFF)<<0x8)
#define NFC_CMD2_BYTE1(x)            (((x)&0xFF)<<0x18)

/* Bit definitions and macros for NFC_CAR */
#define NFC_CAR_BYTE1(x)             (((x)&0xFF)<<0)
#define NFC_CAR_BYTE2(x)             (((x)&0xFF)<<0x8)

/* Bit definitions and macros for NFC_RAR */
#define NFC_RAR_BYTE1(x)             (((x)&0xFF)<<0)
#define NFC_RAR_BYTE2(x)             (((x)&0xFF)<<0x8)
#define NFC_RAR_BYTE3(x)             (((x)&0xFF)<<0x10)
#define NFC_RAR_RB                   (0x1000000)
#define NFC_RAR_CS                   (0x10000000)

/* Bit definitions and macros for NFC_RPT */
#define NFC_RPT_COUNT(x)             (((x)&0xFFFF)<<0)

/* Bit definitions and macros for NFC_RAI */
#define NFC_RAI_INC1(x)              (((x)&0xFF)<<0)
#define NFC_RAI_INC2(x)              (((x)&0xFF)<<0x8)
#define NFC_RAI_INC3(x)              (((x)&0xFF)<<0x10)

/* Bit definitions and macros for NFC_SR1 */
#define NFC_SR1_ID4(x)               (((x)&0xFF)<<0)
#define NFC_SR1_ID3(x)               (((x)&0xFF)<<0x8)
#define NFC_SR1_ID2(x)               (((x)&0xFF)<<0x10)
#define NFC_SR1_ID1(x)               (((x)&0xFF)<<0x18)

/* Bit definitions and macros for NFC_SR2 */
#define NFC_SR2_STATUS1(x)           (((x)&0xFF)<<0)
#define NFC_SR2_ID5(x)               (((x)&0xFF)<<0x18)

/* Bit definitions and macros for NFC_DMA1 */
#define NFC_DMA1_ADDRESS(x)          (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for NFC_DMACFG */
#define NFC_DMACFG_ACT2              (0x1)
#define NFC_DMACFG_ACT1              (0x2)
#define NFC_DMACFG_OFFSET2(x)        (((x)&0x7FF)<<0x2)
#define NFC_DMACFG_COUNT2(x)         (((x)&0x7F)<<0xD)
#define NFC_DMACFG_COUNT1(x)         (((x)&0xFFF)<<0x14)

/* Bit definitions and macros for NFC_SWAP */
#define NFC_SWAP_ADDR1(x)            (((x)&0x7FF)<<0x1)
#define NFC_SWAP_ADDR2(x)            (((x)&0x7FF)<<0x11)

/* Bit definitions and macros for NFC_SECSZ */
#define NFC_SECSZ_SIZE(x)            (((x)&0x1FFF)<<0)

/* Bit definitions and macros for NFC_CFG */
#define NFC_CFG_PAGECNT(x)           (((x)&0xF)<<0)
#define NFC_CFG_AIBN                 (0x10)
#define NFC_CFG_AIAD                 (0x20)
#define NFC_CFG_BTMD                 (0x40)
#define NFC_CFG_16BIT                (0x80)
#define NFC_CFG_TIMEOUT(x)           (((x)&0x1F)<<0x8)
#define NFC_CFG_IDCNT(x)             (((x)&0x7)<<0xD)
#define NFC_CFG_FAST                 (0x10000)
#define NFC_CFG_ECCMODE(x)           (((x)&0x7)<<0x11)
#define NFC_CFG_DMAREQ               (0x100000)
#define NFC_CFG_ECCSRAM              (0x200000)
#define NFC_CFG_ECCAD(x)             (((x)&0x1FF)<<0x16)
#define NFC_CFG_STOPWERR             (0x80000000)

/* Bit definitions and macros for NFC_DMA2 */
#define NFC_DMA2_ADDRESS(x)          (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for NFC_ISR */
#define NFC_ISR_DMABN(x)             (((x)&0x3)<<0)
#define NFC_ISR_ECCBN(x)             (((x)&0x3)<<0x2)
#define NFC_ISR_RESBN(x)             (((x)&0x3)<<0x4)
#define NFC_ISR_IDLECLR              (0x20000)
#define NFC_ISR_DONECLR              (0x40000)
#define NFC_ISR_WERRCL               (0x80000)
#define NFC_ISR_IDLEEN               (0x100000)
#define NFC_ISR_DONEEN               (0x200000)
#define NFC_ISR_WERREN               (0x400000)
#define NFC_ISR_DMABUSY              (0x800000)
#define NFC_ISR_ECCBUSY              (0x1000000)
#define NFC_ISR_RESBUSY              (0x2000000)
#define NFC_ISR_CMDBUSY              (0x4000000)
#define NFC_ISR_WERRNS               (0x8000000)
#define NFC_ISR_IDLE                 (0x20000000)
#define NFC_ISR_DONE                 (0x40000000)
#define NFC_ISR_WERR                 (0x80000000)

/*
** NFC ECC status word
*/

#define NFC_ECC_STATUS_CORFAIL       (0x80)
#define NFC_ECC_STATUS_ERROR_COUNT   (0x3F)

/*
** NFC_STRUCT                                                                   
** This structure defines NFC registers
*/
typedef struct nfc_struct
{
   uint_8   SRAM_B0[2304];  /* NFC SRAM Buffer0 */
   uint_8   nfc_reserved0[1792];
   uint_8   SRAM_B1[2304];  /* NFC SRAM Buffer1 */
   uint_8   nfc_reserved1[1792];
   uint_8   SRAM_B2[2304];  /* NFC SRAM Buffer2 */
   uint_8   nfc_reserved2[1792];
   uint_8   SRAM_B3[2304];  /* NFC SRAM Buffer3 */
   uint_8   nfc_reserved3[1536];
   uint_32  CMD1;      /* NFC Flash Command 1 Register */
   uint_32  CMD2;      /* NFC Flash Command 2 Register */
   uint_32  CAR;       /* NFC Column Address Register */
   uint_32  RAR;       /* NFC Row Address Register */
   uint_32  RPT;       /* NFC Flash Command Repeat Register */
   uint_32  RAI;       /* NFC Row Address Increment */
   uint_32  SR1;       /* NFC Flash Status 1 Register */
   uint_32  SR2;       /* NFC Flash Status 2 Register */
   uint_32  DMA1;      /* NFC DMA 1 Address Register */
   uint_32  DMACFG;    /* NFC DMA Configuration Register */
   uint_32  SWAP;      /* NFC Cache Swap Register */
   uint_32  SECSZ;     /* NFC Sector Size Register */
   uint_32  CFG;       /* NFC Flash Configuration Register */
   uint_32  DMA2;      /* NFC DMA 2 Address Register */
   uint_32  ISR;       /* NFC Interrupt Status Register */
} NFC_STRUCT, _PTR_ NFC_STRUCT_PTR;
typedef volatile struct nfc_struct _PTR_ VNFC_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif  /*__reg_nfc_h__ */

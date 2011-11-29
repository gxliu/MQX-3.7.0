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
* $FileName: mcf5xxx_sdramc.h$
* $Version : 3.0.1.0$
* $Date    : Jul-20-2009$
*
* Comments:
*
*   This file contains the SDRAM controler type definitions for the 
*   mcf54xx processor. It has been split out into a separate header 
*   file to share with other Coldfire PSP's.
*
*END************************************************************************/

#ifndef __mcf5xxx_sdramc_h__
#define __mcf5xxx_sdramc_h__

#define __mcf5xxx_sdramc_h__version "$Version:3.0.1.0$"
#define __mcf5xxx_sdramc_h__date    "$Date:Jul-20-2009$"

#ifdef __cplusplus
extern "C" {
#endif

#define MCF5XXX_SDRAMC_SDMR_DDR2_AD(x)  ((x) & 0x3fff)
#define MCF5XXX_SDRAMC_SDMR_CMD         (1 << 16)
#define MCF5XXX_SDRAMC_SDMR_AD(x)       (((x) & 0xfff) << 18)
#define MCF5XXX_SDRAMC_SDMR_BK(x)       (((x) & 3) << 30)
#define MCF5XXX_SDRAMC_SDMR_LMR         0
#define MCF5XXX_SDRAMC_SDMR_LEMR        (1 << 30)

#define MCF5XXX_SDRAMC_SDCR_DPD             (1)
#define MCF5XXX_SDRAMC_SDCR_IPALL           (1 << 1)
#define MCF5XXX_SDRAMC_SDCR_IREF            (1 << 2)
#define MCF5XXX_SDRAMC_SDCR_DQS_OE(x)       (((x) & 3) << 10)
#define MCF5XXX_SDRAMC_SDCR_MEM_PS          (1 << 13)
//#define MCF5XXX_SDRAMC_SDCR_PS_16           
#define MCF5XXX_SDRAMC_SDCR_REF_CNT(x)      (((x) & 0x3f) << 16)
#define MCF5XXX_SDRAMC_SDCR_OE_RULE         (1 << 22)
#define MCF5XXX_SDRAMC_SDCR_ADDR_MUX(x)     (((x) & 3) << 24)
#define MCF5XXX_SDRAMC_SDCR_DDR2_MODE       (1 << 27)
#define MCF5XXX_SDRAMC_SDCR_REF_EN          (1 << 28)
#define MCF5XXX_SDRAMC_SDCR_DDR_MODE        (1 << 29)
#define MCF5XXX_SDRAMC_SDCR_CKE             (1 << 30)
#define MCF5XXX_SDRAMC_SDCR_MODE_EN         (1 << 31)

#define MCF5XXX_SDRAMC_SDCFG1_WT_LAT(x)     (((x) & 7) << 4)
#define MCF5XXX_SDRAMC_SDCFG1_REF2ACT(x)    (((x) & 0xf) << 8)
#define MCF5XXX_SDRAMC_SDCFG1_PRE2ACT(x)    (((x) & 7) << 12)
#define MCF5XXX_SDRAMC_SDCFG1_ACT2RW(x)     (((x) & 7) << 16)
#define MCF5XXX_SDRAMC_SDCFG1_RD_LAT(x)     (((x) & 0xf) << 20)
#define MCF5XXX_SDRAMC_SDCFG1_SWT2RWP(x)    (((x) & 7) << 24)
#define MCF5XXX_SDRAMC_SDCFG1_SRD2RWP(x)    (((x) & 0xf) << 28)

#define MCF5XXX_SDRAMC_SDCFG2_BL(x)         (((x) & 0x0f) << 16)
#define MCF5XXX_SDRAMC_SDCFG2_BRD2W(x)      (((x) & 0x0f) << 20)
#define MCF5XXX_SDRAMC_SDCFG2_BWT2RWP(x)    (((x) & 0x0f) << 24)
#define MCF5XXX_SDRAMC_SDCFG2_BRD2RP(x)     (((x) & 0x0f) << 28)

/* Bit definitions and macros for SDRAMC_SDCS */
#define MCF5XXX_SDRAMC_SDCS_CSSZ(x)         ((x) & 0x1f)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_DISABLED   (0)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_1MBYTE     (0x13)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_2MBYTE     (0x14)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_4MBYTE     (0x15)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_8MBYTE     (0x16)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_16MBYTE    (0x17)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_32MBYTE    (0x18)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_64MBYTE    (0x19)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_128MBYTE   (0x1A)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_256MBYTE   (0x1B)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_512MBYTE   (0x1C)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_1GBYTE     (0x1D)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_2GBYTE     (0x1E)
#define MCF5XXX_SDRAMC_SDCS_CSSZ_4GBYTE     (0x1F)
#define MCF5XXX_SDRAMC_SDCS_CSBA(x)         (((x) & 0xFFF) << 20)
#define MCF5XXX_SDRAMC_SDCS_BA(x)           ((x) & 0xFFF00000)


typedef struct mcf5xxx_sdramc_struct {
    uint_32 SDMR;  
    uint_32 SDCR;  
    uint_32 SDCFG1;
    uint_32 SDCFG2;
    uint_8  filler[0x100];
    uint_32 SDCS0; 
    uint_32 SDCS1; 
} MCF5XXX_SDRAM_CTRL_STRUCT, _PTR_ MCF5XXX_SDRAM_CTRL_STRUCT_PTR;
typedef volatile struct mcf5xxx_sdramc_struct _PTR_ VMCF5XXX_SDRAM_CTRL_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif // __mcf5xxx_sdramc_h__

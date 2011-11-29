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
* $FileName: mcf5xxx_esdhc.h$
* $Version : 3.6.4.0$
* $Date    : Aug-11-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf5xxx eSDHC module.
*
*END************************************************************************/


#ifndef __mcf5xxx_esdhc_h__
#define __mcf5xxx_esdhc_h__

#define __mcf5xxx_esdhc_h__version "$Version:3.6.4.0$"
#define __mcf5xxx_esdhc_h__date    "$Date:Aug-11-2010$"

#ifdef __cplusplus
extern "C" {
#endif


/*! \brief SDHC - Peripheral register structure */
typedef struct SDHC_MemMap {
  uint_32 DSADDR;                                 /*!< DMA System Address Register, offset: 0x0 */
  uint_32 BLKATTR;                                /*!< Block Attributes Register, offset: 0x4 */
  uint_32 CMDARG;                                 /*!< Command Argument Register, offset: 0x8 */
  uint_32 XFERTYP;                                /*!< Transfer Type Register, offset: 0xC */
  uint_32 CMDRSP[4];                              /*!< Command Response 0..Command Response 3, array offset: 0x10, array step: 0x4 */
  uint_32 DATPORT;                                /*!< Buffer Data Port Register, offset: 0x20 */
  uint_32 PRSSTAT;                                /*!< Present State Register, offset: 0x24 */
  uint_32 PROCTL;                                 /*!< Protocol Control Register, offset: 0x28 */
  uint_32 SYSCTL;                                 /*!< System Control Register, offset: 0x2C */
  uint_32 IRQSTAT;                                /*!< Interrupt Status Register, offset: 0x30 */
  uint_32 IRQSTATEN;                              /*!< Interrupt Status Enable Register, offset: 0x34 */
  uint_32 IRQSIGEN;                               /*!< Interrupt Signal Enable Register, offset: 0x38 */
  uint_32 AC12ERR;                                /*!< Auto CMD12 Error Status Register, offset: 0x3C */
  uint_32 HTCAPBLT;                               /*!< Host Controller Capabilities, offset: 0x40 */
  uint_32 WML;                                    /*!< Watermark Level Register, offset: 0x44 */
  uint_8  RESERVED_0[8];
  uint_32 FEVT;                                   /*!< Force Event Register, offset: 0x50 */
  uint_32 ADMAES;                                 /*!< ADMA Error Status Register, offset: 0x54 */
  uint_32 ADSADDR;                                /*!< ADMA System Address Register, offset: 0x58 */
  uint_8  RESERVED_1[100];
  uint_32 VENDOR;                                 /*!< Vendor Specific Register, offset: 0xC0 */
  uint_32 MMCBOOT;                                /*!< MMC Boot Register, offset: 0xC4 */
  uint_8  RESERVED_2[52];
  uint_32 HOSTVER;                                /*!< Host Controller Version, offset: 0xFC */
} volatile *SDHC_MemMapPtr, SDHC_MEMMAP;

/*! \brief SDHC - Register accessors */
#define SDHC_DSADDR_REG(base)                    ((base)->DSADDR)
#define SDHC_BLKATTR_REG(base)                   ((base)->BLKATTR)
#define SDHC_CMDARG_REG(base)                    ((base)->CMDARG)
#define SDHC_XFERTYP_REG(base)                   ((base)->XFERTYP)
#define SDHC_CMDRSP_REG(base,index)              ((base)->CMDRSP[index])
#define SDHC_DATPORT_REG(base)                   ((base)->DATPORT)
#define SDHC_PRSSTAT_REG(base)                   ((base)->PRSSTAT)
#define SDHC_PROCTL_REG(base)                    ((base)->PROCTL)
#define SDHC_SYSCTL_REG(base)                    ((base)->SYSCTL)
#define SDHC_IRQSTAT_REG(base)                   ((base)->IRQSTAT)
#define SDHC_IRQSTATEN_REG(base)                 ((base)->IRQSTATEN)
#define SDHC_IRQSIGEN_REG(base)                  ((base)->IRQSIGEN)
#define SDHC_AC12ERR_REG(base)                   ((base)->AC12ERR)
#define SDHC_HTCAPBLT_REG(base)                  ((base)->HTCAPBLT)
#define SDHC_WML_REG(base)                       ((base)->WML)
#define SDHC_FEVT_REG(base)                      ((base)->FEVT)
#define SDHC_ADMAES_REG(base)                    ((base)->ADMAES)
#define SDHC_ADSADDR_REG(base)                   ((base)->ADSADDR)
#define SDHC_VENDOR_REG(base)                    ((base)->VENDOR)
#define SDHC_MMCBOOT_REG(base)                   ((base)->MMCBOOT)
#define SDHC_HOSTVER_REG(base)                   ((base)->HOSTVER)

/*! \brief SDHC - Register bit group masks and offsets */
/*! \brief DSADDR Bit Fields */
#define SDHC_DSADDR_DSADDR_MASK                  0xFFFFFFFCu
#define SDHC_DSADDR_DSADDR_SHIFT                 2
#define SDHC_DSADDR_DSADDR(x)                    (((x)<<SDHC_DSADDR_DSADDR_SHIFT)&SDHC_DSADDR_DSADDR_MASK)
/*! \brief BLKATTR Bit Fields */
#define SDHC_BLKATTR_BLKSIZE_MASK                0x1FFFu
#define SDHC_BLKATTR_BLKSIZE_SHIFT               0
#define SDHC_BLKATTR_BLKSIZE(x)                  (((x)<<SDHC_BLKATTR_BLKSIZE_SHIFT)&SDHC_BLKATTR_BLKSIZE_MASK)
#define SDHC_BLKATTR_BLKCNT_MASK                 0xFFFF0000u
#define SDHC_BLKATTR_BLKCNT_SHIFT                16
#define SDHC_BLKATTR_BLKCNT(x)                   (((x)<<SDHC_BLKATTR_BLKCNT_SHIFT)&SDHC_BLKATTR_BLKCNT_MASK)
/*! \brief CMDARG Bit Fields */
#define SDHC_CMDARG_CMDARG_MASK                  0xFFFFFFFFu
#define SDHC_CMDARG_CMDARG_SHIFT                 0
#define SDHC_CMDARG_CMDARG(x)                    (((x)<<SDHC_CMDARG_CMDARG_SHIFT)&SDHC_CMDARG_CMDARG_MASK)
/*! \brief XFERTYP Bit Fields */
#define SDHC_XFERTYP_DMAEN_MASK                  0x1u
#define SDHC_XFERTYP_DMAEN_SHIFT                 0
#define SDHC_XFERTYP_BCEN_MASK                   0x2u
#define SDHC_XFERTYP_BCEN_SHIFT                  1
#define SDHC_XFERTYP_AC12EN_MASK                 0x4u
#define SDHC_XFERTYP_AC12EN_SHIFT                2
#define SDHC_XFERTYP_DTDSEL_MASK                 0x10u
#define SDHC_XFERTYP_DTDSEL_SHIFT                4
#define SDHC_XFERTYP_MSBSEL_MASK                 0x20u
#define SDHC_XFERTYP_MSBSEL_SHIFT                5
#define SDHC_XFERTYP_RSPTYP_MASK                 0x30000u
#define SDHC_XFERTYP_RSPTYP_SHIFT                16
#define SDHC_XFERTYP_RSPTYP(x)                   (((x)<<SDHC_XFERTYP_RSPTYP_SHIFT)&SDHC_XFERTYP_RSPTYP_MASK)
#define SDHC_XFERTYP_CCCEN_MASK                  0x80000u
#define SDHC_XFERTYP_CCCEN_SHIFT                 19
#define SDHC_XFERTYP_CICEN_MASK                  0x100000u
#define SDHC_XFERTYP_CICEN_SHIFT                 20
#define SDHC_XFERTYP_DPSEL_MASK                  0x200000u
#define SDHC_XFERTYP_DPSEL_SHIFT                 21
#define SDHC_XFERTYP_CMDTYP_MASK                 0xC00000u
#define SDHC_XFERTYP_CMDTYP_SHIFT                22
#define SDHC_XFERTYP_CMDTYP(x)                   (((x)<<SDHC_XFERTYP_CMDTYP_SHIFT)&SDHC_XFERTYP_CMDTYP_MASK)
#define SDHC_XFERTYP_CMDINX_MASK                 0x3F000000u
#define SDHC_XFERTYP_CMDINX_SHIFT                24
#define SDHC_XFERTYP_CMDINX(x)                   (((x)<<SDHC_XFERTYP_CMDINX_SHIFT)&SDHC_XFERTYP_CMDINX_MASK)
/*! \brief CMDRSP Bit Fields */
#define SDHC_CMDRSP_CMDRSP0_MASK                 0xFFFFFFFFu
#define SDHC_CMDRSP_CMDRSP0_SHIFT                0
#define SDHC_CMDRSP_CMDRSP0(x)                   (((x)<<SDHC_CMDRSP_CMDRSP0_SHIFT)&SDHC_CMDRSP_CMDRSP0_MASK)
#define SDHC_CMDRSP_CMDRSP1_MASK                 0xFFFFFFFFu
#define SDHC_CMDRSP_CMDRSP1_SHIFT                0
#define SDHC_CMDRSP_CMDRSP1(x)                   (((x)<<SDHC_CMDRSP_CMDRSP1_SHIFT)&SDHC_CMDRSP_CMDRSP1_MASK)
#define SDHC_CMDRSP_CMDRSP2_MASK                 0xFFFFFFFFu
#define SDHC_CMDRSP_CMDRSP2_SHIFT                0
#define SDHC_CMDRSP_CMDRSP2(x)                   (((x)<<SDHC_CMDRSP_CMDRSP2_SHIFT)&SDHC_CMDRSP_CMDRSP2_MASK)
#define SDHC_CMDRSP_CMDRSP3_MASK                 0xFFFFFFFFu
#define SDHC_CMDRSP_CMDRSP3_SHIFT                0
#define SDHC_CMDRSP_CMDRSP3(x)                   (((x)<<SDHC_CMDRSP_CMDRSP3_SHIFT)&SDHC_CMDRSP_CMDRSP3_MASK)
/*! \brief DATPORT Bit Fields */
#define SDHC_DATPORT_DATCONT_MASK                0xFFFFFFFFu
#define SDHC_DATPORT_DATCONT_SHIFT               0
#define SDHC_DATPORT_DATCONT(x)                  (((x)<<SDHC_DATPORT_DATCONT_SHIFT)&SDHC_DATPORT_DATCONT_MASK)
/*! \brief PRSSTAT Bit Fields */
#define SDHC_PRSSTAT_CIHB_MASK                   0x1u
#define SDHC_PRSSTAT_CIHB_SHIFT                  0
#define SDHC_PRSSTAT_CDIHB_MASK                  0x2u
#define SDHC_PRSSTAT_CDIHB_SHIFT                 1
#define SDHC_PRSSTAT_DLA_MASK                    0x4u
#define SDHC_PRSSTAT_DLA_SHIFT                   2
#define SDHC_PRSSTAT_SDSTB_MASK                  0x8u
#define SDHC_PRSSTAT_SDSTB_SHIFT                 3
#define SDHC_PRSSTAT_IPGOFF_MASK                 0x10u
#define SDHC_PRSSTAT_IPGOFF_SHIFT                4
#define SDHC_PRSSTAT_HCKOFF_MASK                 0x20u
#define SDHC_PRSSTAT_HCKOFF_SHIFT                5
#define SDHC_PRSSTAT_PEROFF_MASK                 0x40u
#define SDHC_PRSSTAT_PEROFF_SHIFT                6
#define SDHC_PRSSTAT_SDOFF_MASK                  0x80u
#define SDHC_PRSSTAT_SDOFF_SHIFT                 7
#define SDHC_PRSSTAT_WTA_MASK                    0x100u
#define SDHC_PRSSTAT_WTA_SHIFT                   8
#define SDHC_PRSSTAT_RTA_MASK                    0x200u
#define SDHC_PRSSTAT_RTA_SHIFT                   9
#define SDHC_PRSSTAT_BWEN_MASK                   0x400u
#define SDHC_PRSSTAT_BWEN_SHIFT                  10
#define SDHC_PRSSTAT_BREN_MASK                   0x800u
#define SDHC_PRSSTAT_BREN_SHIFT                  11
#define SDHC_PRSSTAT_CINS_MASK                   0x10000u
#define SDHC_PRSSTAT_CINS_SHIFT                  16
#define SDHC_PRSSTAT_CLSL_MASK                   0x800000u
#define SDHC_PRSSTAT_CLSL_SHIFT                  23
#define SDHC_PRSSTAT_DLSL_MASK                   0xFF000000u
#define SDHC_PRSSTAT_DLSL_SHIFT                  24
#define SDHC_PRSSTAT_DLSL(x)                     (((x)<<SDHC_PRSSTAT_DLSL_SHIFT)&SDHC_PRSSTAT_DLSL_MASK)
/*! \brief PROCTL Bit Fields */
#define SDHC_PROCTL_LCTL_MASK                    0x1u
#define SDHC_PROCTL_LCTL_SHIFT                   0
#define SDHC_PROCTL_DTW_MASK                     0x6u
#define SDHC_PROCTL_DTW_SHIFT                    1
#define SDHC_PROCTL_DTW(x)                       (((x)<<SDHC_PROCTL_DTW_SHIFT)&SDHC_PROCTL_DTW_MASK)
#define SDHC_PROCTL_D3CD_MASK                    0x8u
#define SDHC_PROCTL_D3CD_SHIFT                   3
#define SDHC_PROCTL_EMODE_MASK                   0x30u
#define SDHC_PROCTL_EMODE_SHIFT                  4
#define SDHC_PROCTL_EMODE(x)                     (((x)<<SDHC_PROCTL_EMODE_SHIFT)&SDHC_PROCTL_EMODE_MASK)
#define SDHC_PROCTL_CDTL_MASK                    0x40u
#define SDHC_PROCTL_CDTL_SHIFT                   6
#define SDHC_PROCTL_CDSS_MASK                    0x80u
#define SDHC_PROCTL_CDSS_SHIFT                   7
#define SDHC_PROCTL_DMAS_MASK                    0x300u
#define SDHC_PROCTL_DMAS_SHIFT                   8
#define SDHC_PROCTL_DMAS(x)                      (((x)<<SDHC_PROCTL_DMAS_SHIFT)&SDHC_PROCTL_DMAS_MASK)
#define SDHC_PROCTL_SABGREQ_MASK                 0x10000u
#define SDHC_PROCTL_SABGREQ_SHIFT                16
#define SDHC_PROCTL_CREQ_MASK                    0x20000u
#define SDHC_PROCTL_CREQ_SHIFT                   17
#define SDHC_PROCTL_RWCTL_MASK                   0x40000u
#define SDHC_PROCTL_RWCTL_SHIFT                  18
#define SDHC_PROCTL_IABG_MASK                    0x80000u
#define SDHC_PROCTL_IABG_SHIFT                   19
#define SDHC_PROCTL_WECINT_MASK                  0x1000000u
#define SDHC_PROCTL_WECINT_SHIFT                 24
#define SDHC_PROCTL_WECINS_MASK                  0x2000000u
#define SDHC_PROCTL_WECINS_SHIFT                 25
#define SDHC_PROCTL_WECRM_MASK                   0x4000000u
#define SDHC_PROCTL_WECRM_SHIFT                  26
/*! \brief SYSCTL Bit Fields */
#define SDHC_SYSCTL_IPGEN_MASK                   0x1u
#define SDHC_SYSCTL_IPGEN_SHIFT                  0
#define SDHC_SYSCTL_HCKEN_MASK                   0x2u
#define SDHC_SYSCTL_HCKEN_SHIFT                  1
#define SDHC_SYSCTL_PEREN_MASK                   0x4u
#define SDHC_SYSCTL_PEREN_SHIFT                  2
#define SDHC_SYSCTL_SDCLKEN_MASK                 0x8u
#define SDHC_SYSCTL_SDCLKEN_SHIFT                3
#define SDHC_SYSCTL_DVS_MASK                     0xF0u
#define SDHC_SYSCTL_DVS_SHIFT                    4
#define SDHC_SYSCTL_DVS(x)                       (((x)<<SDHC_SYSCTL_DVS_SHIFT)&SDHC_SYSCTL_DVS_MASK)
#define SDHC_SYSCTL_SDCLKFS_MASK                 0xFF00u
#define SDHC_SYSCTL_SDCLKFS_SHIFT                8
#define SDHC_SYSCTL_SDCLKFS(x)                   (((x)<<SDHC_SYSCTL_SDCLKFS_SHIFT)&SDHC_SYSCTL_SDCLKFS_MASK)
#define SDHC_SYSCTL_DTOCV_MASK                   0xF0000u
#define SDHC_SYSCTL_DTOCV_SHIFT                  16
#define SDHC_SYSCTL_DTOCV(x)                     (((x)<<SDHC_SYSCTL_DTOCV_SHIFT)&SDHC_SYSCTL_DTOCV_MASK)
#define SDHC_SYSCTL_RSTA_MASK                    0x1000000u
#define SDHC_SYSCTL_RSTA_SHIFT                   24
#define SDHC_SYSCTL_RSTC_MASK                    0x2000000u
#define SDHC_SYSCTL_RSTC_SHIFT                   25
#define SDHC_SYSCTL_RSTD_MASK                    0x4000000u
#define SDHC_SYSCTL_RSTD_SHIFT                   26
#define SDHC_SYSCTL_INITA_MASK                   0x8000000u
#define SDHC_SYSCTL_INITA_SHIFT                  27
/*! \brief IRQSTAT Bit Fields */
#define SDHC_IRQSTAT_CC_MASK                     0x1u
#define SDHC_IRQSTAT_CC_SHIFT                    0
#define SDHC_IRQSTAT_TC_MASK                     0x2u
#define SDHC_IRQSTAT_TC_SHIFT                    1
#define SDHC_IRQSTAT_BGE_MASK                    0x4u
#define SDHC_IRQSTAT_BGE_SHIFT                   2
#define SDHC_IRQSTAT_DINT_MASK                   0x8u
#define SDHC_IRQSTAT_DINT_SHIFT                  3
#define SDHC_IRQSTAT_BWR_MASK                    0x10u
#define SDHC_IRQSTAT_BWR_SHIFT                   4
#define SDHC_IRQSTAT_BRR_MASK                    0x20u
#define SDHC_IRQSTAT_BRR_SHIFT                   5
#define SDHC_IRQSTAT_CINS_MASK                   0x40u
#define SDHC_IRQSTAT_CINS_SHIFT                  6
#define SDHC_IRQSTAT_CRM_MASK                    0x80u
#define SDHC_IRQSTAT_CRM_SHIFT                   7
#define SDHC_IRQSTAT_CINT_MASK                   0x100u
#define SDHC_IRQSTAT_CINT_SHIFT                  8
#define SDHC_IRQSTAT_CTOE_MASK                   0x10000u
#define SDHC_IRQSTAT_CTOE_SHIFT                  16
#define SDHC_IRQSTAT_CCE_MASK                    0x20000u
#define SDHC_IRQSTAT_CCE_SHIFT                   17
#define SDHC_IRQSTAT_CEBE_MASK                   0x40000u
#define SDHC_IRQSTAT_CEBE_SHIFT                  18
#define SDHC_IRQSTAT_CIE_MASK                    0x80000u
#define SDHC_IRQSTAT_CIE_SHIFT                   19
#define SDHC_IRQSTAT_DTOE_MASK                   0x100000u
#define SDHC_IRQSTAT_DTOE_SHIFT                  20
#define SDHC_IRQSTAT_DCE_MASK                    0x200000u
#define SDHC_IRQSTAT_DCE_SHIFT                   21
#define SDHC_IRQSTAT_DEBE_MASK                   0x400000u
#define SDHC_IRQSTAT_DEBE_SHIFT                  22
#define SDHC_IRQSTAT_AC12E_MASK                  0x1000000u
#define SDHC_IRQSTAT_AC12E_SHIFT                 24
#define SDHC_IRQSTAT_DMAE_MASK                   0x10000000u
#define SDHC_IRQSTAT_DMAE_SHIFT                  28
/*! \brief IRQSTATEN Bit Fields */
#define SDHC_IRQSTATEN_CCSEN_MASK                0x1u
#define SDHC_IRQSTATEN_CCSEN_SHIFT               0
#define SDHC_IRQSTATEN_TCSEN_MASK                0x2u
#define SDHC_IRQSTATEN_TCSEN_SHIFT               1
#define SDHC_IRQSTATEN_BGESEN_MASK               0x4u
#define SDHC_IRQSTATEN_BGESEN_SHIFT              2
#define SDHC_IRQSTATEN_DINTSEN_MASK              0x8u
#define SDHC_IRQSTATEN_DINTSEN_SHIFT             3
#define SDHC_IRQSTATEN_BWRSEN_MASK               0x10u
#define SDHC_IRQSTATEN_BWRSEN_SHIFT              4
#define SDHC_IRQSTATEN_BRRSEN_MASK               0x20u
#define SDHC_IRQSTATEN_BRRSEN_SHIFT              5
#define SDHC_IRQSTATEN_CINSEN_MASK               0x40u
#define SDHC_IRQSTATEN_CINSEN_SHIFT              6
#define SDHC_IRQSTATEN_CRMSEN_MASK               0x80u
#define SDHC_IRQSTATEN_CRMSEN_SHIFT              7
#define SDHC_IRQSTATEN_CINTSEN_MASK              0x100u
#define SDHC_IRQSTATEN_CINTSEN_SHIFT             8
#define SDHC_IRQSTATEN_CTOESEN_MASK              0x10000u
#define SDHC_IRQSTATEN_CTOESEN_SHIFT             16
#define SDHC_IRQSTATEN_CCESEN_MASK               0x20000u
#define SDHC_IRQSTATEN_CCESEN_SHIFT              17
#define SDHC_IRQSTATEN_CEBESEN_MASK              0x40000u
#define SDHC_IRQSTATEN_CEBESEN_SHIFT             18
#define SDHC_IRQSTATEN_CIESEN_MASK               0x80000u
#define SDHC_IRQSTATEN_CIESEN_SHIFT              19
#define SDHC_IRQSTATEN_DTOESEN_MASK              0x100000u
#define SDHC_IRQSTATEN_DTOESEN_SHIFT             20
#define SDHC_IRQSTATEN_DCESEN_MASK               0x200000u
#define SDHC_IRQSTATEN_DCESEN_SHIFT              21
#define SDHC_IRQSTATEN_DEBESEN_MASK              0x400000u
#define SDHC_IRQSTATEN_DEBESEN_SHIFT             22
#define SDHC_IRQSTATEN_AC12ESEN_MASK             0x1000000u
#define SDHC_IRQSTATEN_AC12ESEN_SHIFT            24
#define SDHC_IRQSTATEN_DMAESEN_MASK              0x10000000u
#define SDHC_IRQSTATEN_DMAESEN_SHIFT             28
/*! \brief IRQSIGEN Bit Fields */
#define SDHC_IRQSIGEN_CCIEN_MASK                 0x1u
#define SDHC_IRQSIGEN_CCIEN_SHIFT                0
#define SDHC_IRQSIGEN_TCIEN_MASK                 0x2u
#define SDHC_IRQSIGEN_TCIEN_SHIFT                1
#define SDHC_IRQSIGEN_BGEIEN_MASK                0x4u
#define SDHC_IRQSIGEN_BGEIEN_SHIFT               2
#define SDHC_IRQSIGEN_DINTIEN_MASK               0x8u
#define SDHC_IRQSIGEN_DINTIEN_SHIFT              3
#define SDHC_IRQSIGEN_BWRIEN_MASK                0x10u
#define SDHC_IRQSIGEN_BWRIEN_SHIFT               4
#define SDHC_IRQSIGEN_BRRIEN_MASK                0x20u
#define SDHC_IRQSIGEN_BRRIEN_SHIFT               5
#define SDHC_IRQSIGEN_CINSIEN_MASK               0x40u
#define SDHC_IRQSIGEN_CINSIEN_SHIFT              6
#define SDHC_IRQSIGEN_CRMIEN_MASK                0x80u
#define SDHC_IRQSIGEN_CRMIEN_SHIFT               7
#define SDHC_IRQSIGEN_CINTIEN_MASK               0x100u
#define SDHC_IRQSIGEN_CINTIEN_SHIFT              8
#define SDHC_IRQSIGEN_CTOEIEN_MASK               0x10000u
#define SDHC_IRQSIGEN_CTOEIEN_SHIFT              16
#define SDHC_IRQSIGEN_CCEIEN_MASK                0x20000u
#define SDHC_IRQSIGEN_CCEIEN_SHIFT               17
#define SDHC_IRQSIGEN_CEBEIEN_MASK               0x40000u
#define SDHC_IRQSIGEN_CEBEIEN_SHIFT              18
#define SDHC_IRQSIGEN_CIEIEN_MASK                0x80000u
#define SDHC_IRQSIGEN_CIEIEN_SHIFT               19
#define SDHC_IRQSIGEN_DTOEIEN_MASK               0x100000u
#define SDHC_IRQSIGEN_DTOEIEN_SHIFT              20
#define SDHC_IRQSIGEN_DCEIEN_MASK                0x200000u
#define SDHC_IRQSIGEN_DCEIEN_SHIFT               21
#define SDHC_IRQSIGEN_DEBEIEN_MASK               0x400000u
#define SDHC_IRQSIGEN_DEBEIEN_SHIFT              22
#define SDHC_IRQSIGEN_AC12EIEN_MASK              0x1000000u
#define SDHC_IRQSIGEN_AC12EIEN_SHIFT             24
#define SDHC_IRQSIGEN_DMAEIEN_MASK               0x10000000u
#define SDHC_IRQSIGEN_DMAEIEN_SHIFT              28
/*! \brief AC12ERR Bit Fields */
#define SDHC_AC12ERR_AC12NE_MASK                 0x1u
#define SDHC_AC12ERR_AC12NE_SHIFT                0
#define SDHC_AC12ERR_AC12TOE_MASK                0x2u
#define SDHC_AC12ERR_AC12TOE_SHIFT               1
#define SDHC_AC12ERR_AC12EBE_MASK                0x4u
#define SDHC_AC12ERR_AC12EBE_SHIFT               2
#define SDHC_AC12ERR_AC12CE_MASK                 0x8u
#define SDHC_AC12ERR_AC12CE_SHIFT                3
#define SDHC_AC12ERR_AC12IE_MASK                 0x10u
#define SDHC_AC12ERR_AC12IE_SHIFT                4
#define SDHC_AC12ERR_CNIBAC12E_MASK              0x80u
#define SDHC_AC12ERR_CNIBAC12E_SHIFT             7
/*! \brief HTCAPBLT Bit Fields */
#define SDHC_HTCAPBLT_MBL_MASK                   0x70000u
#define SDHC_HTCAPBLT_MBL_SHIFT                  16
#define SDHC_HTCAPBLT_MBL(x)                     (((x)<<SDHC_HTCAPBLT_MBL_SHIFT)&SDHC_HTCAPBLT_MBL_MASK)
#define SDHC_HTCAPBLT_ADMAS_MASK                 0x100000u
#define SDHC_HTCAPBLT_ADMAS_SHIFT                20
#define SDHC_HTCAPBLT_HSS_MASK                   0x200000u
#define SDHC_HTCAPBLT_HSS_SHIFT                  21
#define SDHC_HTCAPBLT_DMAS_MASK                  0x400000u
#define SDHC_HTCAPBLT_DMAS_SHIFT                 22
#define SDHC_HTCAPBLT_SRS_MASK                   0x800000u
#define SDHC_HTCAPBLT_SRS_SHIFT                  23
#define SDHC_HTCAPBLT_VS33_MASK                  0x1000000u
#define SDHC_HTCAPBLT_VS33_SHIFT                 24
#define SDHC_HTCAPBLT_VS30_MASK                  0x2000000u
#define SDHC_HTCAPBLT_VS30_SHIFT                 25
#define SDHC_HTCAPBLT_VS18_MASK                  0x4000000u
#define SDHC_HTCAPBLT_VS18_SHIFT                 26
/*! \brief WML Bit Fields */
#define SDHC_WML_RDWML_MASK                      0xFFu
#define SDHC_WML_RDWML_SHIFT                     0
#define SDHC_WML_RDWML(x)                        (((x)<<SDHC_WML_RDWML_SHIFT)&SDHC_WML_RDWML_MASK)
#define SDHC_WML_WRWML_MASK                      0xFF0000u
#define SDHC_WML_WRWML_SHIFT                     16
#define SDHC_WML_WRWML(x)                        (((x)<<SDHC_WML_WRWML_SHIFT)&SDHC_WML_WRWML_MASK)
#define SDHC_WML_WRBRSTLEN_MASK                  0x1F000000u
#define SDHC_WML_WRBRSTLEN_SHIFT                 24
#define SDHC_WML_WRBRSTLEN(x)                    (((x)<<SDHC_WML_WRBRSTLEN_SHIFT)&SDHC_WML_WRBRSTLEN_MASK)
/*! \brief FEVT Bit Fields */
#define SDHC_FEVT_FEVTAC12NE_MASK                0x1u
#define SDHC_FEVT_FEVTAC12NE_SHIFT               0
#define SDHC_FEVT_FEVTAC12TOE_MASK               0x2u
#define SDHC_FEVT_FEVTAC12TOE_SHIFT              1
#define SDHC_FEVT_FEVTAC12CE_MASK                0x4u
#define SDHC_FEVT_FEVTAC12CE_SHIFT               2
#define SDHC_FEVT_FEVTAC12EBE_MASK               0x8u
#define SDHC_FEVT_FEVTAC12EBE_SHIFT              3
#define SDHC_FEVT_FEVTAC12IE_MASK                0x10u
#define SDHC_FEVT_FEVTAC12IE_SHIFT               4
#define SDHC_FEVT_FEVTCNIBAC12E_MASK             0x80u
#define SDHC_FEVT_FEVTCNIBAC12E_SHIFT            7
#define SDHC_FEVT_FEVTCTOE_MASK                  0x10000u
#define SDHC_FEVT_FEVTCTOE_SHIFT                 16
#define SDHC_FEVT_FEVTCCE_MASK                   0x20000u
#define SDHC_FEVT_FEVTCCE_SHIFT                  17
#define SDHC_FEVT_FEVTCEBE_MASK                  0x40000u
#define SDHC_FEVT_FEVTCEBE_SHIFT                 18
#define SDHC_FEVT_FEVTCIE_MASK                   0x80000u
#define SDHC_FEVT_FEVTCIE_SHIFT                  19
#define SDHC_FEVT_FEVTDTOE_MASK                  0x100000u
#define SDHC_FEVT_FEVTDTOE_SHIFT                 20
#define SDHC_FEVT_FEVTDCE_MASK                   0x200000u
#define SDHC_FEVT_FEVTDCE_SHIFT                  21
#define SDHC_FEVT_FEVTDEBE_MASK                  0x400000u
#define SDHC_FEVT_FEVTDEBE_SHIFT                 22
#define SDHC_FEVT_FEVTAC12E_MASK                 0x1000000u
#define SDHC_FEVT_FEVTAC12E_SHIFT                24
#define SDHC_FEVT_FEVTDMAE_MASK                  0x10000000u
#define SDHC_FEVT_FEVTDMAE_SHIFT                 28
#define SDHC_FEVT_FEVTCINT_MASK                  0x80000000u
#define SDHC_FEVT_FEVTCINT_SHIFT                 31
/*! \brief ADMAES Bit Fields */
#define SDHC_ADMAES_ADMAES_MASK                  0x3u
#define SDHC_ADMAES_ADMAES_SHIFT                 0
#define SDHC_ADMAES_ADMAES(x)                    (((x)<<SDHC_ADMAES_ADMAES_SHIFT)&SDHC_ADMAES_ADMAES_MASK)
#define SDHC_ADMAES_ADMALME_MASK                 0x4u
#define SDHC_ADMAES_ADMALME_SHIFT                2
#define SDHC_ADMAES_ADMADCE_MASK                 0x8u
#define SDHC_ADMAES_ADMADCE_SHIFT                3
/*! \brief ADSADDR Bit Fields */
#define SDHC_ADSADDR_ADSADDR_MASK                0xFFFFFFFCu
#define SDHC_ADSADDR_ADSADDR_SHIFT               2
#define SDHC_ADSADDR_ADSADDR(x)                  (((x)<<SDHC_ADSADDR_ADSADDR_SHIFT)&SDHC_ADSADDR_ADSADDR_MASK)
/*! \brief VENDOR Bit Fields */
#define SDHC_VENDOR_EXTDMAEN_MASK                0x1u
#define SDHC_VENDOR_EXTDMAEN_SHIFT               0
#define SDHC_VENDOR_VOLTSEL_MASK                 0x2u
#define SDHC_VENDOR_VOLTSEL_SHIFT                1
#define SDHC_VENDOR_INTSTVAL_MASK                0xFF0000u
#define SDHC_VENDOR_INTSTVAL_SHIFT               16
#define SDHC_VENDOR_INTSTVAL(x)                  (((x)<<SDHC_VENDOR_INTSTVAL_SHIFT)&SDHC_VENDOR_INTSTVAL_MASK)
/*! \brief MMCBOOT Bit Fields */
#define SDHC_MMCBOOT_DTOCVACK_MASK               0xFu
#define SDHC_MMCBOOT_DTOCVACK_SHIFT              0
#define SDHC_MMCBOOT_DTOCVACK(x)                 (((x)<<SDHC_MMCBOOT_DTOCVACK_SHIFT)&SDHC_MMCBOOT_DTOCVACK_MASK)
#define SDHC_MMCBOOT_BOOTACK_MASK                0x10u
#define SDHC_MMCBOOT_BOOTACK_SHIFT               4
#define SDHC_MMCBOOT_BOOTMODE_MASK               0x20u
#define SDHC_MMCBOOT_BOOTMODE_SHIFT              5
#define SDHC_MMCBOOT_BOOTEN_MASK                 0x40u
#define SDHC_MMCBOOT_BOOTEN_SHIFT                6
#define SDHC_MMCBOOT_AUTOSABGEN_MASK             0x80u
#define SDHC_MMCBOOT_AUTOSABGEN_SHIFT            7
#define SDHC_MMCBOOT_BOOTBLKCNT_MASK             0xFFFF0000u
#define SDHC_MMCBOOT_BOOTBLKCNT_SHIFT            16
#define SDHC_MMCBOOT_BOOTBLKCNT(x)               (((x)<<SDHC_MMCBOOT_BOOTBLKCNT_SHIFT)&SDHC_MMCBOOT_BOOTBLKCNT_MASK)
/*! \brief HOSTVER Bit Fields */
#define SDHC_HOSTVER_SVN_MASK                    0xFFu
#define SDHC_HOSTVER_SVN_SHIFT                   0
#define SDHC_HOSTVER_SVN(x)                      (((x)<<SDHC_HOSTVER_SVN_SHIFT)&SDHC_HOSTVER_SVN_MASK)
#define SDHC_HOSTVER_VVN_MASK                    0xFF00u
#define SDHC_HOSTVER_VVN_SHIFT                   8
#define SDHC_HOSTVER_VVN(x)                      (((x)<<SDHC_HOSTVER_VVN_SHIFT)&SDHC_HOSTVER_VVN_MASK)


#ifdef __cplusplus
}
#endif

#endif

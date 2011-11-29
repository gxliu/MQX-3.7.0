#ifndef __mpc5125_csbarb_h__
#define __mpc5125_csbarb_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
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
* $FileName: mpc512x_csbarb.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define MPC5125_CSBARB_ADDR()       (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->CSB)
/***************** Register Bit Fields and Values ***************************/
// configuration register **************
#define CSBARB_ACR_ALL_MASK (0x0737777F)      /**<all valid bit mask*/

#define CSBARB_ACR_RESERVED_1_SHIFT 27 /**< position of bit field*/
#define CSBARB_ACR_RESERVED_1_MASK (0xF8000000) /**< bit field mask */

#define CSBARB_ACR_DTO_DIS_SHIFT 26 /**< position of bit field*/
#define CSBARB_ACR_DTO_DIS_MASK (0x04000000) /**< bit field mask */
#define CSBARB_ACR_DTO_EN (0x0)   /**< DTO timer enable*/
#define CSBARB_ACR_DTO_DIS (0x1)  /**< DTO timer disable*/

#define CSBARB_ACR_ATO_DIS_SHIFT 25 /**< position of bit field*/
#define CSBARB_ACR_ATO_DIS_MASK (0x02000000) /**< bit field mask */
#define CSBARB_ACR_ATO_EN (0x0)   /**< ATO timer enable*/
#define CSBARB_ACR_ATO_DIS (0x1)  /**< ATO timer disable*/

#define CSBARB_ACR_COREDIS_SHIFT 24 /**< position of bit field*/
#define CSBARB_ACR_COREDIS_MASK (0x01000000) /**< bit field mask */
#define CSBARB_ACR_CORE_EN (0x0)  /**< CPU core can access bus*/
#define CSBARB_ACR_CORE_DIS (0x1) /**< CPU core cannot access bus*/

#define CSBARB_ACR_RESERVED_2_SHIFT 22/**< position of bit field*/
#define CSBARB_ACR_RESERVED_2_MASK (0x00C00000) /**< bit field mask */

#define CSBARB_ACR_AACKWS_SHIFT 20 /**< position of bit field*/
#define CSBARB_ACR_AACKWS_MASK (0x00300000)     /**< bit field mask */
#define CSBARB_ACR_WS_0 (0x0) /**< 0 wait cycles until ack*/
#define CSBARB_ACR_WS_1 (0x1) /**< 1 wait cycles until ack*/
#define CSBARB_ACR_WS_2 (0x2) /**< 2 wait cycles until ack*/
#define CSBARB_ACR_WS_3 (0x3) /**< 3 wait cycles until ack*/

#define CSBARB_ACR_RESERVED_3_SHIFT 19 /**< position of bit field*/
#define CSBARB_ACR_RESERVED_3_MASK (0x00080000) /**< bit field mask */

#define CSBARB_ACR_PIPE_DEP_SHIFT 16 /**< position of bit field*/
#define CSBARB_ACR_PIPE_DEP_MASK (0x00070000)   /**< bit field mask */
#define CSBARB_ACR_PIPE_DEP_1 (0x0) /**< max. 1 piped transaction*/
#define CSBARB_ACR_PIPE_DEP_2 (0x1) /**< max. 2 piped transactions*/
#define CSBARB_ACR_PIPE_DEP_3 (0x2) /**< max. 3 piped transactions*/
#define CSBARB_ACR_PIPE_DEP_4 (0x3) /**< max. 4 piped transactions*/
#define CSBARB_ACR_PIPE_DEP_5 (0x4) /**< max. 5 piped transactions*/
#define CSBARB_ACR_PIPE_DEP_6 (0x5) /**< max. 6 piped transactions*/
#define CSBARB_ACR_PIPE_DEP_7 (0x6) /**< max. 7 piped transactions*/
#define CSBARB_ACR_PIPE_DEP_8 (0x7) /**< max. 8 piped transactions*/

#define CSBARB_ACR_RESERVED_4_SHIFT 15 /**< position of bit field*/
#define CSBARB_ACR_RESERVED_4_MASK (0x00008000) /**< bit field mask */

#define CSBARB_ACR_PCI_RPTCNT_SHIFT 12 /**< position of bit field*/
#define CSBARB_ACR_PCI_RPTCNT_MASK (0x00007000) /**< bit field mask */
#define CSBARB_ACR_PCI_TRAN_1 (0x0) /**< max. 1 repeated PCI transaction*/
#define CSBARB_ACR_PCI_TRAN_2 (0x1) /**< max. 2 repeated PCI transactions*/
#define CSBARB_ACR_PCI_TRAN_3 (0x2) /**< max. 3 repeated PCI transactions*/
#define CSBARB_ACR_PCI_TRAN_4 (0x3) /**< max. 4 repeated PCI transactions*/
#define CSBARB_ACR_PCI_TRAN_5 (0x4) /**< max. 5 repeated PCI transactions*/
#define CSBARB_ACR_PCI_TRAN_6 (0x5) /**< max. 6 repeated PCI transactions*/
#define CSBARB_ACR_PCI_TRAN_7 (0x6) /**< max. 7 repeated PCI transactions*/
#define CSBARB_ACR_PCI_TRAN_8 (0x7) /**< max. 8 repeated PCI transactions*/

#define CSBARB_ACR_RESERVED_5_SHIFT 11 /**< position of bit field*/
#define CSBARB_ACR_RESERVED_5_MASK (0x00000800) /**< bit field mask */

#define CSBARB_ACR_RPTCNT_SHIFT 8 /**< position of bit field*/
#define CSBARB_ACR_RPTCNT_MASK (0x00000700)     /**< bit field mask */
#define CSBARB_ACR_TRAN_1 (0x0) /**< max. 1 repeated transaction*/ 
#define CSBARB_ACR_TRAN_2 (0x1) /**< max. 2 repeated transactions*/
#define CSBARB_ACR_TRAN_3 (0x2) /**< max. 3 repeated transactions*/
#define CSBARB_ACR_TRAN_4 (0x3) /**< max. 4 repeated transactions*/
#define CSBARB_ACR_TRAN_5 (0x4) /**< max. 5 repeated transactions*/
#define CSBARB_ACR_TRAN_6 (0x5) /**< max. 6 repeated transactions*/
#define CSBARB_ACR_TRAN_7 (0x6) /**< max. 7 repeated transactions*/
#define CSBARB_ACR_TRAN_8 (0x7) /**< max. 8 repeated transactions*/

#define CSBARB_ACR_RESERVED_6_SHIFT 7 /**< position of bit field*/
#define CSBARB_ACR_RESERVED_6_MASK (0x00000080) /**< bit field mask */

#define CSBARB_ACR_WPARK_SHIFT 6  /**< position of bit field*/
#define CSBARB_ACR_WPARK_MASK (0x00000040)   /**< bit field mask */
#define CSBARB_ACR_WPARK_CPU (0x0) /**< CPU uses address
                                    *   parking on WOP cycles*/
#define CSBARB_ACR_WPARK_NO (0x1)  /**< no address parking on
                                    *   WOP cycles*/

#define CSBARB_ACR_APARK_SHIFT 4  /**< position of bit field*/
#define CSBARB_ACR_APARK_MASK (0x00000030)       /**< bit field mask */
#define CSBARB_ACR_APARK_MSTR (0x0) /**< PARKM master is selected
                                     *   for address parking */
#define CSBARB_ACR_APARK_LAST (0x1) /**< last master is selected
                                     *   for address parking */
#define CSBARB_ACR_APARK_DISABLE (0x2) /**< disable address parking */

#define CSBARB_ACR_PARKM_SHIFT 0 /**< position of bit field*/
#define CSBARB_ACR_PARKM_MASK (0x0000000F)       /**< bit field mask */
#define CSBARB_ACR_PARKM_CPU (0x0) /**< address parking master is CPU */
#define CSBARB_ACR_PARKM_PCI (0x1) /**< address parking master is PCI */
#define CSBARB_ACR_PARKM_TPR (0x2) /**< address parking master is test port */

// time out register**************
#define CSBARB_ATR_ALL_MASK (0xFFFFFFFF)     /**< all valid bit mask */

#define CSBARB_ATR_DTO_SHIFT 16 /**< position of bit field*/
#define CSBARB_ATR_DTO_MASK (0xFFFF0000)         /**< bit field mask */
#define CSBARB_ATR_ATO_SHIFT 0 /**< position of bit field*/
#define CSBARB_ATR_ATO_MASK (0x0000FFFF)         /**< bit field mask */

// transfer error register**************
// (which events are treated as events)
#define CSBARB_ATER_ALL_MASK (0x0000003F)    /**< all valid bit mask */

#define CSBARB_ATER_RESERVED_SHIFT 6 /**< position of bit field*/
#define CSBARB_ATER_RESERVED_MASK (0xFFFFFFC0)   /**< bit field mask */

#define CSBARB_ATER_NOT_ERROR (0x0) /**< event is not treated as error*/
#define CSBARB_ATER_ERROR (0x1)     /**< event is treated as error*/

//external TEA
#define CSBARB_ATER_ETEA_SHIFT 5 /**< position of bit field*/
#define CSBARB_ATER_ETEA_MASK (0x00000020)       /**< bit field mask */

// reserved transfer type
#define CSBARB_ATER_RES_SHIFT 4 /**< position of bit field*/
#define CSBARB_ATER_RES_MASK (0x00000010)        /**< bit field mask */

//external control word
#define CSBARB_ATER_ECW_SHIFT 3 /**< position of bit field*/
#define CSBARB_ATER_ECW_MASK (0x00000008)        /**< bit field mask */

//address only
#define CSBARB_ATER_AO_SHIFT 2 /**< position of bit field*/
#define CSBARB_ATER_AO_MASK (0x00000004)        /**< bit field mask */

//data time out
#define CSBARB_ATER_DTO_SHIFT 1 /**< position of bit field*/
#define CSBARB_ATER_DTO_MASK (0x00000002)        /**< bit field mask */

//address time out
#define CSBARB_ATER_ATO_SHIFT 0 /**< position of bit field*/
#define CSBARB_ATER_ATO_MASK (0x00000001)        /**< bit field mask */

// event register **************
// (flags which event happened)
#define CSBARB_AER_ALL_MASK (0x0000003F)     /**< all valid bit mask */

#define CSBARB_AER_RESERVED_SHIFT 6 /**< position of bit field*/
#define CSBARB_AER_RESERVED_MASK (0xFFFFFFC0)    /**< bit field mask */

#define CSBARB_AER_NOT_ERROR (0x0) /**< an error event did not happened */
#define CSBARB_AER_ERROR (0x1)     /**< an error event happened */

#define CSBARB_AER_ETEA_SHIFT 5 /**< position of bit field*/
#define CSBARB_AER_ETEA_MASK (0x00000020)        /**< bit field mask */

#define CSBARB_AER_RES_SHIFT 4 /**< position of bit field*/
#define CSBARB_AER_RES_MASK (0x00000010)        /**< bit field mask */

#define CSBARB_AER_ECW_SHIFT 3 /**< position of bit field*/
#define CSBARB_AER_ECW_MASK (0x00000008)        /**< bit field mask */

#define CSBARB_AER_AO_SHIFT 2 /**< position of bit field*/
#define CSBARB_AER_AO_MASK (0x00000004)          /**< bit field mask */

#define CSBARB_AER_DTO_SHIFT 1 /**< position of bit field*/
#define CSBARB_AER_DTO_MASK (0x00000002)        /**< bit field mask */

#define CSBARB_AER_ATO_SHIFT 0 /**< position of bit field*/
#define CSBARB_AER_ATO_MASK (0x00000001)        /**< bit field mask */

// interrupt definition register **************
//(regular or mcp interrupt on event)
#define CSBARB_AIDR_ALL_MASK (0x0000003F)    /**< all valid bit mask */

#define CSBARB_AIDR_RESERVED_SHIFT 6 /**< position of bit field*/
#define CSBARB_AIDR_RESERVED (0xFFFFFFC0)        /**< bit field mask */

#define CSBARB_AIDR_REG (0x0) /**< use regular interrupt */
#define CSBARB_AIDR_MCP (0x1) /**< use MCP interrupt */

//external TEA
#define CSBARB_AIDR_ETEA_SHIFT 5 /**< position of bit field*/
#define CSBARB_AIDR_ETEA_MASK (0x00000020)        /**< bit field mask */

// reserved transfer type
#define CSBARB_AIDR_RES_SHIFT 4 /**< position of bit field*/
#define CSBARB_AIDR_RES_MASK (0x00000010)         /**< bit field mask */

//external control word
#define CSBARB_AIDR_ECW_SHIFT 3 /**< position of bit field*/
#define CSBARB_AIDR_ECW_MASK (0x00000008)        /**< bit field mask */

//address only
#define CSBARB_AIDR_AO_SHIFT 2 /**< position of bit field*/
#define CSBARB_AIDR_AO_MASK (0x00000004)        /**< bit field mask */

//data time out
#define CSBARB_AIDR_DTO_SHIFT 1 /**< position of bit field*/
#define CSBARB_AIDR_DTO_MASK (0x00000002)        /**< bit field mask */

//address time out
#define CSBARB_AIDR_ATO_SHIFT 0 /**< position of bit field*/
#define CSBARB_AIDR_ATO_MASK (0x00000001)        /**< bit field mask */

// interrupt mask register **************
//(enable or disable interrupt/reset on event)
#define CSBARB_AMR_ALL_MASK (0x0000003F)     /**< all valid bit mask */

#define CSBARB_AMR_RESERVED_SHIFT 6 /**< position of bit field*/
#define CSBARB_AMR_RESERVED_MASK (0xFFFFFFC0)    /**< bit field mask */

#define CSBARB_AMR_INT_DIS (0x0) /**< disable interrupt */
#define CSBARB_AMR_INT_EN (0x1)  /**< enable interrupt */

//external TEA
#define CSBARB_AMR_ETEA_SHIFT 5 /**< position of bit field*/
#define CSBARB_AMR_ETEA_MASK (0x00000020)        /**< bit field mask */

// reserved transfer
#define CSBARB_AMR_RES_SHIFT 4 /**< position of bit field*/
#define CSBARB_AMR_RES_MASK (0x00000010)        /**< bit field mask */

//external control word
#define CSBARB_AMR_ECW_SHIFT 3 /**< position of bit field*/
#define CSBARB_AMR_ECW_MASK (0x00000008)        /**< bit field mask */

//address only
#define CSBARB_AMR_AO_SHIFT 2 /**< position of bit field*/
#define CSBARB_AMR_AO_MASK (0x00000004)          /**< bit field mask */

//data time out
#define CSBARB_AMR_DTO_SHIFT 1 /**< position of bit field*/
#define CSBARB_AMR_DTO_MASK (0x00000002)        /**< bit field mask */

//address time out
#define CSBARB_AMR_ATO_SHIFT 0 /**< position of bit field*/
#define CSBARB_AMR_ATO_MASK (0x00000001)        /**< bit field mask */

//event attributes register **************
//(attributes of access that caused the event)
#define CSBARB_AEATR_ALL_MASK (0x071F0F1F)   /**< all valid bit mask */

#define CSBARB_AEATR_RESERVED_1_SHIFT 27 /**< position of bit field*/
#define CSBARB_AEATR_RESERVED_1_MASK (0xF8000000)/**< bit field mask */

#define CSBARB_AEATR_EVENT_SHIFT 24 /**< position of bit field*/
#define CSBARB_AEATR_EVENT_MASK (0x07000000)     /**< bit field mask */

#define CSBARB_AEATR_RESERVED_2_SHIFT 21 /**< position of bit field*/
#define CSBARB_AEATR_RESERVED_2_MASK (0x00E00000)/**< bit field mask */

#define CSBARB_AEATR_MSTR_ID_SHIFT 16 /**< position of bit field*/
#define CSBARB_AEATR_MSTR_ID_MASK (0x001F0000)  /**< bit field mask */

#define CSBARB_AEATR_RESERVED_3_SHIFT 12 /**< position of bit field*/
#define CSBARB_AEATR_RESERVED_3_MASK (0x0000F000)/**< bit field mask */

#define CSBARB_AEATR_TBST_SHIFT 11 /**< position of bit field*/
#define CSBARB_AEATR_TBST_MASK (0x00000800)    /**< bit field mask */

#define CSBARB_AEATR_TSIZE_SHIFT 8 /**< position of bit field*/
#define CSBARB_AEATR_TSIZE_MASK (0x00000700)      /**< bit field mask */

#define CSBARB_AEATR_RESERVED_4_SHIFT 5 /**< position of bit field*/
#define CSBARB_AEATR_RESERVED_4_MASK (0x000000E0)/**< bit field mask */

#define CSBARB_AEATR_TTYPE_SHIFT 0 /**< position of bit field*/
#define CSBARB_AEATR_TTYPE_MASK (0x0000001F)    /**< bit field mask */

//event address register **************
//(address that caused the event)
#define CSBARB_AEADR_ALL_MASK (0xFFFFFFFF)  /**< all valid bit mask */

#define CSBARB_AEADR_ADDR_SHIFT 0 /**< position of bit field*/
#define CSBARB_AEADR_ADDR_MASK (0xFFFFFFFF)     /**< bit field mask */

//event response register **************
//(response with interrupt or reset on event)
#define CSBARB_AERR_ALL_MASK (0x0000003F)   /**< all valid bit mask */

#define CSBARB_AERR_RESERVED_SHIFT 6 /**< position of bit field*/
#define CSBARB_AERR_RESERVED_MASK (0xFFFFFFC0)  /**< bit field mask */

// possible values
#define CSBARB_AERR_INT (0x0) /**< call interrupt on event */
#define CSBARB_AERR_RST (0x1) /**< perform reset on event */

//external TEA
#define CSBARB_AERR_ETEA_SHIFT 5 /**< position of bit field*/
#define CSBARB_AERR_ETEA_MASK (0x00000020)    /**< bit field mask */

// reserved transfer
#define CSBARB_AERR_RES_SHIFT 4 /**< position of bit field*/
#define CSBARB_AERR_RES_MASK (0x00000010)       /**< bit field mask */

//external control word
#define CSBARB_AERR_ECW_SHIFT 3 /**< position of bit field*/
#define CSBARB_AERR_ECW_MASK (0x00000008)       /**< bit field mask */

//address only
#define CSBARB_AERR_AO_SHIFT 2 /**< position of bit field*/
#define CSBARB_AERR_AO_MASK (0x00000004)       /**< bit field mask */

//data time out
#define CSBARB_AERR_DTO_SHIFT 1 /**< position of bit field*/
#define CSBARB_AERR_DTO_MASK (0x00000002)       /**< bit field mask */

//address time out
#define CSBARB_AERR_ATO_SHIFT 0 /**< position of bit field*/
#define CSBARB_AERR_ATO_MASK (0x00000001)       /**< bit field mask */


typedef volatile struct mpc5125_csb_arbiter_struct {
   vuint_32 ACR;     // 0x00 Arbiter Configuration Register R/W 0x0UU0_0000 8.2.1.1/8-2
   vuint_32 ATR;     // 0x04 Arbiter Timers Register R/W 0xFFFF_FFFF 8.2.1.2/8-4
   vuint_32 ATER;    // 0x08 Arbiter Transfer Error Register  R/W 0x0000_003F 8.2.1.3/8-5
   vuint_32 AER;     // 0x0C Arbiter Event Register R/W 0x0000_0000 8.2.1.4/8-6
   vuint_32 AIDR;    // 0x10 Arbiter Interrupt Definition Register R/W 0x0000_0000 8.2.1.5/8-7
   vuint_32 AMR;     // 0x14 Arbiter Mask Register R/W 0x0000_0000 8.2.1.6/8-8
   vuint_32 AEATR;   // 0x18 Arbiter Event Attributes Register R 0x0000_0000 8.2.1.7/8-9
   vuint_32 AEADR;   // 0x1C Arbiter Event Address Register R 0x0000_0000 8.2.1.8/8-11
   vuint_32 AERR;    // 0x20 Arbiter Event Response Register R/W 0x0000_0000 8.2.1.9/8-12
   RESERVED_REGISTER(0x24,0x100);
} MPC5125_CSB_ARBITER_STRUCT, _PTR_ MPC5125_CSB_ARBITER_STRUCT_PTR;

#endif
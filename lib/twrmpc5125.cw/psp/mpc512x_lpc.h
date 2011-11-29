#ifndef __mpc5125_lpc_h__
#define __mpc5125_lpc_h__
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
* $FileName: mpc512x_lpc.h$
* $Version :  3.7.3.0$
* $Date    :  Feb-7-2011$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/
/* Bit definitions and macros for MPC5125_LPCS_SCPLC */

#define MPC5125_LPCS_CS0BOOTC_WAITP(x)            ((x) << 24)
#define MPC5125_LPCS_CS0BOOTC_WAITX(x)            ((x) << 16)
#define MPC5125_LPCS_CS0BOOTC_MUX_MASK            (0x1 << 15)
#define MPC5125_LPCS_CS0BOOTC_ALEV_MASK           (0x1 << 14)  
#define MPC5125_LPCS_CS0BOOTC_AA_MASK             (0x1 << 13) 
#define MPC5125_LPCS_CS0BOOTC_CE_MASK             (0x1 << 12)
#define MPC5125_LPCS_CS0BOOTC_ALEN(x)             ((x) << 10)
#define MPC5125_LPCS_CS0BOOTC_DS(x)               ((x) << 8)
#define MPC5125_LPCS_CS0BOOTC_BM_MASK             (0x1 << 7)
#define MPC5125_LPCS_CS0BOOTC_ADDRM_MASK          (0x1 << 6)
#define MPC5125_LPCS_CS0BOOTC_WTYP(x)             ((x) << 4)      
#define MPC5125_LPCS_CS0BOOTC_WS_MASK             (0x1 << 3)
#define MPC5125_LPCS_CS0BOOTC_RS_MASK             (0x1 << 2)
#define MPC5125_LPCS_CS0BOOTC_WO_MASK             (0x1 << 1)
#define MPC5125_LPCS_CS0BOOTC_RO_MASK             (0x1 << 0)  

#define MPC5125_LPCS_CSC_IE_MASK                  (0x1 << 27)
#define MPC5125_LPCS_CSC_ME_MASK                  (0x1 << 24)

#define MPC5125_LPCS_CSDC_MASK                    (0x33333333)
#define MPC5125_LPCS_CSHC_MASK                    (0x33333333)

#define MPC5125_LPCS_SCLPC_E_ME_MASK              (0x1 << 0)
#define MPC5125_LPCS_SCLPC_E_NIE_MASK             (0x1 << 8)
#define MPC5125_LPCS_SCLPC_E_AIE_MASK             (0x1 << 9)
#define MPC5125_LPCS_SCLPC_E_RF_MASK              (0x1 << 16)
#define MPC5125_LPCS_SCLPC_E_RC_MASK              (0x1 << 24)

#define MPC5125_LPCS_SCLPC_C_BPT(x)               ((x) << 0)
#define MPC5125_LPCS_SCLPC_C_DAI_MASK             (0x1 << 8)
#define MPC5125_LPCS_SCLPC_C_RW_MASK              (0x1 << 16)    
#define MPC5125_LPCS_SCLPC_C_FLUSH                (0x1 << 15)
#define MPC5125_LPCS_SCLPC_PS_RESTART_MASK        (0x1 << 31)
#define MPC5125_LPCS_SCLPC_PS_PACKET_SIZE(x)      ((x) & 0x7FFFFFFF)

#define MPC5125_LPCS_SCLPC_FIFOC_GR(x)            ((x) << 24)

typedef volatile struct mpc5125_lpc_struct {
   vuint_32 CS0BOOTC;      // 0x000 Chip Select 0/Boot Configuration Register (LPC_CS0BOOTC)    R/W 0x0020_UUU1 21.2.1.1.1/21-4
   vuint_32 CS1C;          // 0x004 Chip Select 1 Configuration Register (LPC_CS1C)             R/W 0x0000_0000 21.2.1.1.2/21-7
   vuint_32 CS2C;          // 0x008 Chip Select 2 Configuration Register (LPC_CS2C)             R/W 0x0000_0000 21.2.1.1.2/21-7
   vuint_32 CS3C;          // 0x00C Chip Select 3 Configuration Register (LPC_CS3C)             R/W 0x0000_0000 21.2.1.1.2/21-7
   vuint_32 CS4C;          // 0x010 Chip Select 4 Configuration Register (LPC_CS4C)             R/W 0x0000_0000 21.2.1.1.2/21-7
   vuint_32 CS5C;          // 0x014 Chip Select 5 Configuration Register (LPC_CS5C)             R/W 0x0000_0000 21.2.1.1.2/21-7
   vuint_32 CS6C;          // 0x018 Chip Select 6 Configuration Register (LPC_CS6C)             R/W 0x0000_0000 21.2.1.1.2/21-7
   vuint_32 CS7C;          // 0x01C Chip Select 7 Configuration Register (LPC_CS7C)             R/W 0x0000_0000 21.2.1.1.2/21-7
   vuint_32 CSC;           // 0x020 Chip Select Control Register (LPC_CSC)                      R/W 0x0000_0000 21.2.1.1.3/21-9
   vuint_32 CSS;           // 0x024 Chip Select Status Register (LPC_CSS)                       R/W 0x0000_0000 21.2.1.1.4/21-9
   vuint_32 CSBC;          // 0x028 Chip Select Burst Control (LPC_CSBC)                        R/W 0x0000_0000 21.2.1.1.5/21-10
   vuint_32 CSDC;          // 0x02C Chip Select Deadcycle Control Register (LPC_CSDC)           R/W 0x3333_3333 21.2.1.1.6/21-11
   vuint_32 CSHC;          // 0x030 Chip Select Holdcycle Control Register (LPC_CSHC)           R/W 0x3333_3333 21.2.1.1.7/21-12
   vuint_32 ALTR;          // 0x034 Address Latch Timing Register (LPC_ALTR)                    R/W 0x0000_0000 21.2.1.1.8/21-12
   vuint_32 TTE;           // 0x038 TSIZ and TS Enable Register (LPC_TTE)                       R/W 0x0000_000U 21.2.1.1.9/21-13
   RESERVED_REGISTER(0x03C,0x100);     
   vuint_32 SCLPC_PS;      // 0x100 SCLPC Packet Size Register (LPC_SCLPC_PS)                   R/W 0x0000_0000 21.2.1.2.1/21-14
   vuint_32 SCLPC_SA;      // 0x104 SCLPC Start Address Register (LPC_SCLPC_SA)                 R/W 0x0000_0000 21.2.1.2.2/21-15
   vuint_32 SCLPC_C;       // 0x108 SCLPC Control Register (LPC_SCLPC_C)                        R/W 0x0001_0000 21.2.1.2.3/21-15
   vuint_32 SCLPC_E;       // 0x10C SCLPC Enable Register (LPC_SCLPC_E)                         R/W 0x0000_0000 21.2.1.2.4/21-16
   RESERVED_REGISTER(0x110,0x114);     
   vuint_32 SCLPC_S;       // 0x114 SCLPC Status Register (LPC_SCLPC_S)                         R/W 0x0000_0000 21.2.1.2.5/21-17
   vuint_32 SCLPC_BD;      // 0x118 SCLPC Bytes Done Register (LPC_SCLPC_BD)                    R/W 0x0000_0000 21.2.1.2.6/21-17
   vuint_32 EMB_SC;        // 0x11C EMB Share Counter Register (LPC_EMB_SC)                     R/W 0x0010_0000 21.2.1.2.7/21-18
   vuint_32 EMB_PC;        // 0x120 EMB Pause Control Register (LPC_EMB_PC)                     R/W 0x0000_0000 21.2.1.2.8/21-18
   RESERVED_REGISTER(0x124,0x140);     
   vuint_32 SCLPC_FIFOD;   // 0x140 LPC RX/TX FIFO Data Word Register (LPC_SCLPC_FIFOD)         R/W             21.2.1.3.1/21-19
   vuint_32 SCLPC_FIFOS;   // 0x144 LPC RX/TX FIFO Status Register (LPC_SCLPC_FIFOS)            R/W 0x0001_0000 21.2.1.3.2/21-20
   vuint_32 SCLPC_FIFOC;   // 0x148 LPC RX/TX FIFO Control Register (LPC_SCLPC_FIFOC)           R/W 0x0100_0000 21.2.1.3.3/21-21
   vuint_32 SCLPC_FIFOA;   // 0x14C LPC RX/TX FIFO Alarm Register (LPC_SCLPC_FIFOA)             R/W 0x0000_0000 21.2.1.3.4/21-21
   RESERVED_REGISTER(0x150,0x200);     
} MPC5125_LPC_STRUCT, _PTR_ MPC5125_LPC_STRUCT_PTR;


// Local Plus Bus related constants



#endif
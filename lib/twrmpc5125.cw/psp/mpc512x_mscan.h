#ifndef __mpc5125_mscan_h__
#define __mpc5125_mscan_h__
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
* $FileName: mpc512x_mscan.h$
* $Version :  3.6.2.0$
* $Date    :  Jun-4-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/



#define MPC5125_NUM_MSCAN  4

#define MPC5125_MSCAN1     0
#define MPC5125_MSCAN2     1
#define MPC5125_MSCAN3     2
#define MPC5125_MSCAN4     3

#define MPC5125_MSCAN1_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->MSCAN1)
#define MPC5125_MSCAN2_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->MSCAN2)
#define MPC5125_MSCAN3_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->MSCAN3)
#define MPC5125_MSCAN4_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->MSCAN4)



#define MSCAN_CANCTL0_RXFRM_MASK    0x80
#define MSCAN_CANCTL0_RXFRM_SHIFT   7
#define MSCAN_CANCTL0_RXACT_MASK    0x40
#define MSCAN_CANCTL0_RXACT_SHIFT   6
#define MSCAN_CANCTL0_CSWAI_MASK    0x20
#define MSCAN_CANCTL0_CSWAI_SHIFT   5
#define MSCAN_CANCTL0_SYNCH_MASK    0x10
#define MSCAN_CANCTL0_SYCNH_SHIFT   4
#define MSCAN_CANCTL0_TIME_MASK     0x08
#define MSCAN_CANCTL0_TIME_SHIFT    3
#define MSCAN_CANCTL0_WUPE_MASK     0x04
#define MSCAN_CANCTL0_WUPE_SHIFT    2
#define MSCAN_CANCTL0_SLPRQ_MASK    0x02
#define MSCAN_CANCTL0_SLPRQ_SHIFT   1
#define MSCAN_CANCTL0_INITRQ_MASK   0x01
#define MSCAN_CANCTL0_INITRQ_SHIFT  0

#define MSCAN_CANCTL1_CANE_MASK     0x80
#define MSCAN_CANCTL1_CANE_SHIFT    7
#define MSCAN_CANCTL1_CLKSRC_MASK   0x40
#define MSCAN_CANCTL1_CLKSRC_SHIFT  6
#define MSCAN_CANCTL1_LOOPB_MASK    0x20
#define MSCAN_CANCTL1_LOOPB_SHIFT   5
#define MSCAN_CANCTL1_LISTEN_MASK   0x10
#define MSCAN_CANCTL1_LISTEN_SHIFT  4
#define MSCAN_CANCTL1_BORM_MASK     0x08
#define MSCAN_CANCTL1_BORM_SHIFT    3
#define MSCAN_CANCTL1_WUPM_MASK     0x04
#define MSCAN_CANCTL1_WUPM_SHIFT    2
#define MSCAN_CANCTL1_SLPAK_MASK    0x02
#define MSCAN_CANCTL1_SLPAK_SHIFT   1
#define MSCAN_CANCTL1_INITAK_MASK   0x01
#define MSCAN_CANCTL1_INITAK_SHIFT  0

#define MSCAN_CANBTR0_SJW1_MASK     0x80
#define MSCAN_CANBTR0_SJW1_SHIFT    7
#define MSCAN_CANBTR0_SJW0_MASK     0x40
#define MSCAN_CANBTR0_SJW0_SHIFT    6
#define MSCAN_CANBTR0_BRP5_MASK     0x20
#define MSCAN_CANBTR0_BRP5_SHIFT    5
#define MSCAN_CANBTR0_BRP4_MASK     0x10
#define MSCAN_CANBTR0_BRP4_SHIFT    4
#define MSCAN_CANBTR0_BRP3_MASK     0x08
#define MSCAN_CANBTR0_BRP3_SHIFT    3
#define MSCAN_CANBTR0_BRP2_MASK     0x04
#define MSCAN_CANBTR0_BRP2_SHIFT    2
#define MSCAN_CANBTR0_BRP1_MASK     0x02
#define MSCAN_CANBTR0_BRP1_SHIFT    1
#define MSCAN_CANBTR0_BRP0_MASK     0x01
#define MSCAN_CANBTR0_BRP0_SHIFT    0

#define MSCAN_CANBTR0_SJW_MASK      0xC0
#define MSCAN_CANBTR0_SJW_SHIFT     6
#define MSCAN_CANBTR0_BRP_MASK      0x3F
#define MSCAN_CANBTR0_BRP_SHIFT     0

#define MSCAN_CANBTR1_SAMP_MASK     0x80
#define MSCAN_CANBTR1_SAMP_SHIFT    7
#define MSCAN_CANBTR1_TSEG2_MASK    0x70
#define MSCAN_CANBTR1_TSEG2_SHIFT   4
#define MSCAN_CANBTR1_TSEG1_MASK    0x0F
#define MSCAN_CANBTR1_TSEG1_SHIFT   0

#define MSCAN_CANRFLG_WUPIF_MASK    0x80
#define MSCAN_CANRFLG_WUPIF_SHIFT   7
#define MSCAN_CANRFLG_CSCIF_MASK    0x40
#define MSCAN_CANRFLG_CSCIF_SHIFT   6
#define MSCAN_CANRFLG_RSTAT_MASK    0x30
#define MSCAN_CANRFLG_RSTAT_SHIFT   4
#define MSCAN_CANRFLG_TSTAT_MASK    0x0C
#define MSCAN_CANRFLG_TSTAT_SHIFT   2
#define MSCAN_CANRFLG_OVRIF_MASK    0x02
#define MSCAN_CANRFLG_OVRIF_SHIFT   1
#define MSCAN_CANRFLG_RXF_MASK      0x01
#define MSCAN_CANRFLG_RXF_SHIFT     0

#define MSCAN_CANRIER_WUPIE_MASK    0x80
#define MSCAN_CANRIER_WUPIE_SHIFT   7
#define MSCAN_CANRIER_CSCIE_MASK    0x40
#define MSCAN_CANRIER_CSCIE_SHIFT   6
#define MSCAN_CANRIER_RSTATE_MASK   0x30
#define MSCAN_CANRIER_RSTATE_SHIFT  4
#define MSCAN_CANRIER_TSTATE_MASK   0x0C
#define MSCAN_CANRIER_TSTATE_SHIFT  2
#define MSCAN_CANRIER_OVRIE_MASK    0x02
#define MSCAN_CANRIER_OVRIE_SHIFT   1
#define MSCAN_CANRIER_RXFIE_MASK    0x01
#define MSCAN_CANRIER_RXFIE_SHIFT   0

#define MSCAN_CANTFLG_TXE_MASK      0x07
#define MSCAN_CANTFLG_TXE_SHIFT     0

#define MSCAN_CANTIER_TXEIE_MASK    0x07
#define MSCAN_CANTIER_TXEIE_SHIFT   0

#define MSCAN_CANTARQ_ABTRQ_MASK    0x07
#define MSCAN_CANTARQ_ABTRQ_SHIFT   0

#define MSCAN_CANTAAK_ABTAK_MASK    0x07
#define MSCAN_CANTAAK_ABTAK_SHIFT   0

#define MSCAN_CANTBSEL_TX_MASK      0x07
#define MSCAN_CANTBSEL_TX_SHIFT     0

#define MSCAN_CANIDAC_IDAM_MASK     0x30
#define MSCAN_CANIDAC_IDAM_SHIFT    4
#define MSCAN_CANIDAC_IDHIT_MASK    0x07
#define MSCAN_CANIDAC_IDHIT_SHIFT   0

#define MSCAN_CANTEST_RAMB0_MASK    0x80
#define MSCAN_CANTEST_RAMB0_SHIFT   7
#define MSCAN_CANTEST_RXAMP_MASK    0x40
#define MSCAN_CANTEST_RXAMP_SHIFT   6
#define MSCAN_CANTEST_MBIST_MASK    0x20
#define MSCAN_CANTEST_MBIST_SHIFT   5
#define MSCAN_CANTEST_FGBF_MASK     0x1C
#define MSCAN_CANTEST_FGBF_SHIFT    2
#define MSCAN_CANTEST_ECLOAD_MASK   0x02
#define MSCAN_CANTEST_ECLOAD_SHIFT  1
#define MSCAN_CANTEST_MSCOUNT_MASK  0x01
#define MSCAN_CANTEST_MSCOUNT_SHIFT 0

#define MSCAN_CANMISC_BOFFHOLD_MASK 0x01
#define MSCAN_CANMISC_BOFFHOLD_SHIFT    0

#define MSCAN_CANRXERR_RXERR_MASK   0xFF
#define MSCAN_CANRXERR_RXERR_SHIFT  0

#define MSCAN_CANTXERR_TXERR_MASK   0xFF
#define MSCAN_CANTXERR_TXERR_SHIFT  0

#define MSCAN_CANIDAR0_AC_MASK      0xFF
#define MSCAN_CANIDAR0_AC_SHIFT     0

#define MSCAN_CANIDAR1_AC_MASK      0xFF
#define MSCAN_CANIDAR1_AC_SHIFT     0

#define MSCAN_CANIDAR2_AC_MASK      0xFF
#define MSCAN_CANIDAR2_AC_SHIFT     0

#define MSCAN_CANIDAR3_AC_MASK      0xFF
#define MSCAN_CANIDAR3_AC_SHIFT     0

#define MSCAN_CANIDMR0_AM_MASK      0xFF
#define MSCAN_CANIDMR0_AM_SHIFT     0

#define MSCAN_CANIDMR1_AM_MASK      0xFF
#define MSCAN_CANIDMR1_AM_SHIFT     0

#define MSCAN_CANIDMR2_AM_MASK      0xFF
#define MSCAN_CANIDMR2_AM_SHIFT     0

#define MSCAN_CANIDMR3_AM_MASK      0xFF
#define MSCAN_CANIDMR3_AM_SHIFT     0

#define MSCAN_CANIDAR4_AC_MASK      0xFF
#define MSCAN_CANIDAR4_AC_SHIFT     0

#define MSCAN_CANIDAR5_AC_MASK      0xFF
#define MSCAN_CANIDAR5_AC_SHIFT     0

#define MSCAN_CANIDAR6_AC_MASK      0xFF
#define MSCAN_CANIDAR6_AC_SHIFT     0

#define MSCAN_CANIDAR7_AC_MASK      0xFF
#define MSCAN_CANIDAR7_AC_SHIFT     0

#define MSCAN_CANIDMR4_AM_MASK      0xFF
#define MSCAN_CANIDMR4_AM_SHIFT     0

#define MSCAN_CANIDMR5_AM_MASK      0xFF
#define MSCAN_CANIDMR5_AM_SHIFT     0

#define MSCAN_CANIDMR6_AM_MASK      0xFF
#define MSCAN_CANIDMR6_AM_SHIFT     0

#define MSCAN_CANIDMR7_AM_MASK      0xFF
#define MSCAN_CANIDMR7_AM_SHIFT     0

typedef volatile struct mpc5125_mscan_msg_struct
{
    vuint_8 IDR0;  // 0x00 RX/TX Identifier Register 0 (IDR0)             R/W  4 22.3.3.1/22-28
    vuint_8 IDR1;  // 0x01 RX/TX Identifier Register 1 (IDR1)             R/W  4  22.3.3.1/22-28
    RESERVED_REGISTER(0x02,0x04);              
    vuint_8 IDR2;  // 0x04 RX/TX Identifier Register 2 (IDR2)              R/W  4  22.3.3.1/22-28
    vuint_8 IDR3;  // 0x05 RX/TX Identifier Register 3 (IDR3)              R/W  4  22.3.3.1/22-28
    RESERVED_REGISTER(0x06,0x08);              
    vuint_8 DSR0;  // 0x08 RX/TX Data Segment Register 0 (DSR0)            R/W  4  22.3.3.2/22-31
    vuint_8 DSR1;  // 0x09 RX/TX Data Segment Register 1 (DSR1)            R/W  4  22.3.3.2/22-31
    RESERVED_REGISTER(0x0A,0x0C);              
    vuint_8 DSR2;  // 0x0C RX/TX Data Segment Register 2 (DSR2)            R/W  4  22.3.3.2/22-31
    vuint_8 DSR3;  // 0x0D RX/TX Data Segment Register 3 (DSR3)            R/W  4  22.3.3.2/22-31
    RESERVED_REGISTER(0x0E,0x10);              
    vuint_8 DSR4;  // 0x10 RX/TX Data Segment Register 4 (DSR4)            R/W  4  22.3.3.2/22-31
    vuint_8 DSR5;  // 0x11 RX/TX Data Segment Register 5 (DSR5)            R/W  4  22.3.3.2/22-31
    RESERVED_REGISTER(0x12,0x14);              
    vuint_8 DSR6;  // 0x14 RX/TX Data Segment Register 6 (DSR6)            R/W  4  22.3.3.2/22-31
    vuint_8 DSR7;  // 0x15 RX/TX Data Segment Register 7 (DSR7)            R/W  4  22.3.3.2/22-31
    RESERVED_REGISTER(0x16,0x18);              
    vuint_8 DLR;  // 0x18 RX/TX Data Length Register (DLR)                 R/W  4  22.3.3.3/22-32
    vuint_8 TBPR;  // 0x19 RX/TX Transmit Buffer Priority Register (TBPR)  R/W 0x00 22.3.3.4/22-32
    RESERVED_REGISTER(0x1A,0x1C);              
    vuint_8 TSRH;  // 0x1C RX/TX Time Stamp Register High (TSRH)           R  4  22.3.3.5/22-3
    vuint_8 TSRL;  // 0x1D RX/TX Time Stamp Register Low (TSRL)            R  4  22.3.3.5/22-3
    RESERVED_REGISTER(0x1E,0x20);              
} MPC5125_MSCAN_MSG_STRUCT, _PTR_ MPC5125_MSCAN_MSG_STRUCT_PTR;

   
   
typedef volatile struct mpc5125_mscan_struct
{
   vuint_8 CANCTL0;              // 0x00 MSCAN Control Register 0 (CANCTL0) R/W 0x01 22.3.2.1/22-10
   vuint_8 CANCTL1;              // 0x01 MSCAN Control Register 1 (CANCTL1) R/W 0x11 22.3.2.2/22-12
   RESERVED_REGISTER(0x02,0x04);              
   vuint_8 CANBTR0;              // 0x04 MSCAN Bus Timing Register 0 (CANBTR0) R/W 0x00 22.3.2.3/22-13
   vuint_8 CANBTR1;              // 0x05 MSCAN Bus Timing Register 1 (CANBTR1) R/W 0x00 22.3.2.4/22-14
   RESERVED_REGISTER(0x06,0x08);              
   vuint_8 CANRFLG;              // 0x08 MSCAN Receiver Flag Register (CANRFLG) R/W 0x00 22.3.2.5/22-15
   vuint_8 CANRIER;              // 0x09 MSCAN Receiver Interrupt Enable Register (CANRIER) R/W 0x00 22.3.2.6/22-16
   RESERVED_REGISTER(0x0A,0x0C);              
   vuint_8 CANTFLG;              // 0x0C MSCAN Transmitter Flag Register (CANTFLG) R/W 0x07 22.3.2.7/22-18
   vuint_8 CANTIER;              // 0x0D MSCAN Transmitter Interrupt Enable Register (CANTIER) R/W 0x00 22.3.2.8/22-18
   RESERVED_REGISTER(0x0E,0x10);              
   vuint_8 CANTARQ;              // 0x10 MSCAN Transmitter Message Abort Control (CANTARQ) R/W 0x00 22.3.2.9/22-19
   vuint_8 CANTAAK;              // 0x11 MSCAN Transmitter Message Abort Control (CANTAAK) R 0x00 22.3.2.10/22-20
   RESERVED_REGISTER(0x12,0x14);              
   vuint_8 CANTBSEL;             // 0x14 MSCAN Transmit Buffer Selection (CANTBSEL) R/W 0x00 22.3.2.11/22-21
   vuint_8 CANIDAC;              // 0x15 MSCAN Identifier Acceptance Control Register (CANIDAC) R/W 0x00 22.3.2.12/22-22
   RESERVED_REGISTER(0x16,0x19);              
   vuint_8 CANMISC;              // 0x19 MSCAN MISC Register (CANMISC) R/W 0x00 22.3.2.13/22-22
   RESERVED_REGISTER(0x1A,0x1C);              
   vuint_8 CANRXERR;             // 0x1C MSCAN Receive Error Counter Register (CANRXERR) R 0x00 22.3.2.14/22-23
   vuint_8 CANTXERR;             // 0x1D MSCAN Transmitter Error Counter Register (CANTXERR)R 0x00 22.3.2.15/22-23
   RESERVED_REGISTER(0x1E,0x20);              
   vuint_8 CANIDAR0;             // 0x20 MSCAN Identifier Acceptance Registers (CANIDAR0) R/W 0x00 22.3.2.16/22-24
   vuint_8 CANIDAR1;             // 0x21 MSCAN Identifier Acceptance Registers (CANIDAR1) R/W 0x00 22.3.2.16/22-24
   RESERVED_REGISTER(0x22,0x24);             
   vuint_8 CANIDAR2;             // 0x24 MSCAN Identifier Acceptance Registers (CANIDAR2) R/W 0x00 22.3.2.16/22-24
   vuint_8 CANIDAR3;             // 0x25 MSCAN Identifier Acceptance Registers (CANIDAR3) R/W 0x00 22.3.2.16/22-24
   RESERVED_REGISTER(0x26,0x28);              
   vuint_8 CANIDMR0;             // 0x28 MSCAN Identifier Mask Registers (CANIDMR0) R/W 0x00 22.3.2.17/22-25
   vuint_8 CANIDMR1;             // 0x29 MSCAN Identifier Mask Registers (CANIDMR1) R/W 0x00 22.3.2.17/22-25
   RESERVED_REGISTER(0x2A,0x2C);              
   vuint_8 CANIDMR2;             // 0x2C MSCAN Identifier Mask Registers (CANIDMR2) R/W 0x00 22.3.2.17/22-25
   vuint_8 CANIDMR3;             // 0x2D MSCAN Identifier Mask Registers (CANIDMR3) R/W 0x00 22.3.2.17/22-25
   RESERVED_REGISTER(0x2E,0x30);              
   vuint_8 CANIDAR4;             // 0x30 MSCAN Identifier Acceptance Registers (CANIDAR4) R/W 0x00 22.3.2.16/22-24
   vuint_8 CANIDAR5;             // 0x31 MSCAN Identifier Acceptance Registers (CANIDAR5) R/W 0x00 22.3.2.16/22-24
   RESERVED_REGISTER(0x32,0x34);              
   vuint_8 CANIDAR6;             // 0x34 MSCAN Identifier Acceptance Registers (CANIDAR6) R/W 0x00 22.3.2.16/22-24
   vuint_8 CANIDAR7;             // 0x35 MSCAN Identifier Acceptance Registers (CANIDAR7) R/W 0x00 22.3.2.16/22-24
   RESERVED_REGISTER(0x36,0x38);              
   vuint_8 CANIDMR4;             // 0x38 MSCAN Identifier Mask Registers (CANIDMR4) R/W 0x00 22.3.2.17/22-25
   vuint_8 CANIDMR5;             // 0x39 MSCAN Identifier Mask Registers (CANIDMR5) R/W 0x00 22.3.2.17/22-25
   RESERVED_REGISTER(0x3A,0x3C);              
   vuint_8 CANIDMR6;             // 0x3C MSCAN Identifier Mask Registers (CANIDMR6) R/W 0x00 22.3.2.17/22-25
   vuint_8 CANIDMR7;             // 0x3D MSCAN Identifier Mask Registers (CANIDMR7) R/W 0x00 22.3.2.17/22-25
   RESERVED_REGISTER(0x3E,0x40);     
   MPC5125_MSCAN_MSG_STRUCT   CANRXFG; // 0x40–0x5F MSCAN Receive Message Buffer (CANRXFG) 3 22.4.3/22-38
   MPC5125_MSCAN_MSG_STRUCT   CANTXFG; // 0x60–0x7F MSCAN Transmit Message Buffer (CANTXFG) 5 22.4.3/22-38
} MPC5125_MSCAN_STRUCT, _PTR_ MPC5125_MSCAN_STRUCT_PTR;

             
#endif
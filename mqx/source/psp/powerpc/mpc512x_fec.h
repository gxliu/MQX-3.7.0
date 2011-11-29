#ifndef __mpc512x_fec_h__
#define __mpc512x_fec_h__
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
* $FileName: mpc512x_fec.h$
* $Version :  3.6.2.0$
* $Date    :  Jun-4-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define __mpc512x_fec_h__version "$Version:3.6.2.0$"
#define __mpc512x_fec_h__date    "$Date:Jun-4-2010$"

#ifdef __cplusplus
extern "C" {
#endif


#define MPC5125_FEC0    0
#define MPC5125_FEC1    1

/*------------------------------------------------------------------------*/
/*
** ENET FEC  registers bit set.
*/

/* FEC Ethernet Buffer descriptor bits */
#define MPC512X_FEC_BD_ETHER_RX_EMPTY                (1<<15)
#define MPC512X_FEC_BD_ETHER_RX_WRAP                 (1<<13)

/* The following are status bits set after reception */
#define MPC512X_FEC_BD_ETHER_RX_LAST_FRAME           (1<<11)
#define MPC512X_FEC_BD_ETHER_RX_MISS                 (1<<8)
#define MPC512X_FEC_BD_ETHER_RX_BROADCAST            (1<<7)
#define MPC512X_FEC_BD_ETHER_RX_MULTICAST            (1<<6)
#define MPC512X_FEC_BD_ETHER_RX_LENGTH_VIOLATION     (1<<5)
#define MPC512X_FEC_BD_ETHER_RX_NON_OCTET            (1<<4)
#define MPC512X_FEC_BD_ETHER_RX_CRC_ERROR            (1<<2)
#define MPC512X_FEC_BD_ETHER_RX_OVERRUN              (1<<1)
#define MPC512X_FEC_BD_ETHER_RX_TRUNCATED            (1<<0)

#define MPC512X_FEC_BD_ETHER_TX_READY                (1<<15)
#define MPC512X_FEC_BD_ETHER_TX_SOFTWARE_OWNERSHIP_1 (1<<14)
#define MPC512X_FEC_BD_ETHER_TX_WRAP                 (1<<13)
#define MPC512X_FEC_BD_ETHER_TX_SOFTWARE_OWNERSHIP_2 (1<<12)
#define MPC512X_FEC_BD_ETHER_TX_LAST                 (1<<11)
#define MPC512X_FEC_BD_ETHER_TX_SEND_CRC             (1<<10)
#define MPC512X_FEC_BD_ETHER_TX_BAD_CRC              (1<<9)

/* FEC Ethernet Control Register */
#define MPC512X_FEC_ECR_ETHER_EN                 (0x00000002)
#define MPC512X_FEC_ECR_RESET                    (0x00000001)

/* FEC Interrupt Event Register */
#define MPC512X_FEC_EIR_ALL_PENDING              (0xFFF80000)
#define MPC512X_FEC_EIR_HBERR                    (0x80000000)
#define MPC512X_FEC_EIR_BABR                     (0x40000000)
#define MPC512X_FEC_EIR_BABT                     (0x20000000)
#define MPC512X_FEC_EIR_GRA                      (0x10000000)
#define MPC512X_FEC_EIR_TXF                      (0x08000000)
#define MPC512X_FEC_EIR_TXB                      (0x04000000)
#define MPC512X_FEC_EIR_RXF                      (0x02000000)
#define MPC512X_FEC_EIR_RXB                      (0x01000000)
#define MPC512X_FEC_EIR_MII                      (0x00800000)
#define MPC512X_FEC_EIR_EBERR                    (0x00400000)
#define MPC512X_FEC_EIR_LC                       (0x00200000)
#define MPC512X_FEC_EIR_RL                       (0x00100000)
#define MPC512X_FEC_EIR_UN                       (0x00080000)

/* FEC Interrupt Mask Register */
#define MPC512X_FEC_EIMR_MASK_ALL                (0xFFF80000)
#define MPC512X_FEC_EIMR_HBERR                   (0x80000000)
#define MPC512X_FEC_EIMR_BABR                    (0x40000000)
#define MPC512X_FEC_EIMR_BABT                    (0x20000000)
#define MPC512X_FEC_EIMR_GRA                     (0x10000000)
#define MPC512X_FEC_EIMR_TXF                     (0x08000000)
#define MPC512X_FEC_EIMR_TXB                     (0x04000000)
#define MPC512X_FEC_EIMR_RXF                     (0x02000000)
#define MPC512X_FEC_EIMR_RXB                     (0x01000000)
#define MPC512X_FEC_EIMR_MII                     (0x00800000)
#define MPC512X_FEC_EIMR_EBERR                   (0x00400000)
#define MPC512X_FEC_EIMR_LC                      (0x00200000)
#define MPC512X_FEC_EIMR_RL                      (0x00100000)
#define MPC512X_FEC_EIMR_UN                      (0x00080000)


/* FEC Receive Descriptor Active Register */
#define MPC512X_FEC_RDAR_ACTIVE                  (1<<24)

/* FEC Transmit Descriptor Active Register */
#define MPC512X_FEC_TDAR_ACTIVE                  (1<<24)

/* FEC Receive Control Register */
#define MPC512X_FEC_RCR_RMMI_ECHO                (0x00000800)
#define MPC512X_FEC_RCR_RMMI_LOOP                (0x00000400)
#define MPC512X_FEC_RCR_RMMI_10T                 (0x00000200)
#define MPC512X_FEC_RCR_RMMI_MODE                (0x00000100)
#define MPC512X_FEC_RCR_FCE                      (0x00000020)
#define MPC512X_FEC_RCR_BC_REJ                   (0x00000010)
#define MPC512X_FEC_RCR_PROM                     (0x00000008)
#define MPC512X_FEC_RCR_MII_MODE                 (0x00000004)
#define MPC512X_FEC_RCR_DRT                      (0x00000002)
#define MPC512X_FEC_RCR_LOOP                     (0x00000001)
#define MPC512X_FEC_RCR_FRAME_LENGTH(x)          (((x)&0x7ff)<<16)

/* FEC Transmit Control Register */
#define MPC512X_FEC_TCR_FDEN                     (0x00000004)
#define MPC512X_FEC_TCR_HBC                      (0x00000002)
#define MPC512X_FEC_TCR_GTS                      (0x00000001)

/* MII Management Frame Register */
#define MPC512X_FEC_MII_START_OF_FRAME           (0x40000000)
#define MPC512X_FEC_MII_OPCODE_READ              (0x20000000)
#define MPC512X_FEC_MII_OPCODE_WRITE             (0x10000000)
#define MPC512X_FEC_MII_PA(x)                    (((x)&0x1F)<<23)
#define MPC512X_FEC_MII_RA(x)                    (((x)&0x1F)<<18)
#define MPC512X_FEC_MII_DATA(x)                  (((x)&0xFFFF))
#define MPC512X_FEC_MII_TURNAROUND               (0x00020000)
#define MPC512X_FEC_MII_MSCR_PREAMBLE            (1<<7)
#define MPC512X_FEC_MII_MSCR_SPEED(x)            (((x) 0x3F) << 1)

#define MPC512X_FEC_SIM_ICR_ERX_IL(a)                ( 0x00000800 | (((a)&0x07)<<8) )
#define MPC512X_FEC_SIM_ICR_ETX_IL(a)                ( 0x00000080 | (((a)&0x07)<<4) )
#define MPC512X_FEC_SIM_ICR_ENTC_IL(a)               ( 0x00000008 | ((a)&0x07) )


// Just one interrupt vector
#define MPC512X_FEC_INT         0                 
#define MPC512X_FEC_NUM_INTS    1  


#define ETH_DMA_CONTROL_DATA_BO_BIG       0x80000000
#define ETH_DMA_CONTROL_DESC_BO_BIG       0x40000000
#define ETH_DMA_CONTROL_DATA_BO_LITTLE    0x00000000
#define ETH_DMA_CONTROL_DESC_BO_LITTLE    0x00000000


/*
** MPC512X_FEC_STRUCT
** Fast Ethernet Controller registers
*/
typedef struct MPC512X_FEC_struct
{


   vuint_32 ETH_FEC_ID;                //  0x000 ETH_FEC_ID       FEC Identification Register               R/W 0x0000_0000 14.3.5.1/14-11
   vuint_32 EIR;                       //  0x004 ETH_IEVENT       Interrupt Event Register                  R/W 0x0000_0000 14.3.5.2/14-12
   vuint_32 EIMR;                      //  0x008 ETH_IMASK        Interrupt Mask Register                   R/W 0x0000_0000 14.3.5.3/14-14
   RESERVED_REGISTER(0x00C,0x010);     //  Reserved
   vuint_32 RDAR;                      //  0x010 ETH_R_DES_ACTIVE CSR Receive Descriptor Active Register    R/W 0x0000_0000 14.3.5.4/14-15
   vuint_32 TDAR;                      //  0x014 ETH_X_DES_ACTIVE CSR Transmit Descriptor Active Register   R/W 0x0000_0000 14.3.5.5/14-16
   RESERVED_REGISTER(0x018,0x024);     //  Reserved
   vuint_32 ECR;                       //  0x024 ETH_ECNTRL       Ethernet Control register                 R/W 0x0000_0000 14.3.5.6/14-17
   RESERVED_REGISTER(0x028,0x040);     //  Reserved
   vuint_32 MMFR;                      //  0x040 ETH_MII_DATA     MII Management Frame Register             R/W 0x0000_0000 14.3.5.7/14-17
   vuint_32 MSCR;                      //  0x044 ETH_MII_SPEED    MII Speed Control Register                R/W 0x0000_0000 14.3.5.8/14-19
   RESERVED_REGISTER(0x048,0x064);     //  Reserved
   vuint_32 MIBC;                      //  0x064 ETH_MIB_CONTROL  MIB Control Register                      R/W 0xC000_0000 14.3.5.9/14-20
   RESERVED_REGISTER(0x068,0x084);     //  Reserved
   vuint_32 RCR;                       //  0x084 ETH_R_CNTRL      Receive Control Register                  R/W 0x05EE_0001 14.3.5.10/14-20
   vuint_32 ETH_R_HASH;                //  0x088 ETH_R_HASH       Receive Hash Register                     R               14.3.5.11/14-22
   RESERVED_REGISTER(0x08C,0x0C4);     //  Reserved
   vuint_32 TCR;                       //  0x0C4 ETH_X_CNTRL      Transmit Control Register                 R/W 0x0000_0000 14.3.5.12/14-23
   RESERVED_REGISTER(0x0C8,0x0E4);     //  Reserved
   vuint_32 PALR;                      //  0x0E4 ETH_PADDR1       Physical Address Low Register             R/W 0x0000_0000 14.3.5.13/14-24
   vuint_32 PAUR;                      //  0x0E8 ETH_PADDR2       Physical Address High Register            R/W 0x0000_8808 14.3.5.14/14-25
   vuint_32 OPD;                       //  0x0EC ETH_OP_PAUSE     Opcode/Pause Duration Register            R/W 0x0001_UUUU 14.3.5.15/14-25
   RESERVED_REGISTER(0x0F0,0x118);     //  Reserved
   vuint_32 IAUR;                      //  0x118 ETH_IADDR1       Descriptor Individual Address 1           R/W             14.3.5.16/14-26
   vuint_32 IALR;                      //  0x11C ETH_IADDR2       Descriptor Individual Address 2           R/W             14.3.5.17/14-27
   vuint_32 GAUR;                      //  0x120 ETH_GADDR1       Descriptor Group Address 1                R/W             14.3.5.18/14-27
   vuint_32 GALR;                      //  0x124 ETH_GADDR2       Descriptor Group Address 2                R/W             14.3.5.19/14-28
   RESERVED_REGISTER(0x128,0x144);     //  Reserved
   vuint_32 TFWR;                      //  0x144 ETH_X_WMRK       FIFO Transmit FIFO Watermark              R/W 0x0000_0000 14.3.5.20/14-28
   RESERVED_REGISTER(0x148,0x14C);     //  Reserved
   vuint_32 FRBR;                      //  0x14C ETH_R_BOUND      FIFO Receive Bound Register               R   0x0000_0600 14.3.5.21/14-29
   vuint_32 FRSR;                      //  0x150 ETH_R_FSTART     FIFO Receive Start Register               R/W 0x0000_0500 14.3.5.22/14-30
   RESERVED_REGISTER(0x154,0x180);     //  Reserved
   vuint_32 ERDSR;                     //  0x180 ETH_R_DES_START  Beginning of Receive Descriptor Ring      R/W             14.3.5.23/14-30
   vuint_32 ETDSR;                     //  0x184 ETH_X_DES_START  Beginning of Transmit Descriptor Ring     R/W             14.3.5.24/14-31
   vuint_32 EMRBR;                     //  0x188 ETH_R_BUFF_SIZE  Receive Buffer Size Register              R/W             14.3.5.25/14-32
   RESERVED_REGISTER(0x18C,0x1F4);     //  Reserved
   vuint_32 ETH_DMA_CONTROL;           //  0x1F4 ETH_DMA_CONTROL  DMA Function Control Register             R/W 0xU000_0000 14.3.5.26/14-32
   RESERVED_REGISTER(0x1F8,0x200);     //  Reserved
   vuchar   MIB_RAM[512];              //  Ram to store FEC counters
   RESERVED_REGISTER(0x400,0x800);     //  Reserved
} MPC512X_FEC_STRUCT, _PTR_ MPC512X_FEC_STRUCT_PTR;
typedef volatile struct MPC512X_FEC_struct _PTR_ VMPC512X_FEC_STRUCT_PTR;

/*
** MPC512X_FEC_BD_STRUCT
** This structure defines what the Ethernet buffer descriptor looks like
*/
typedef struct MPC512X_FEC_bd_struct
{
   uint_16      CONTROL;
   uint_16      LENGTH;
   uchar_ptr    BUFFER;
} MPC512X_FEC_BD_STRUCT, _PTR_ MPC512X_FEC_BD_STRUCT_PTR;
typedef volatile struct MPC512X_FEC_bd_struct _PTR_ VMPC512X_FEC_BD_STRUCT_PTR;

#ifdef __cplusplus
}
#endif


#endif

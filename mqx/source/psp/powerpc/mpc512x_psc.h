#ifndef __mpc5125_psc_h__
#define __mpc5125_psc_h__
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
* $FileName: mpc512x_psc.h$
* $Version :  3.7.4.0$
* $Date    :  Feb-7-2011$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/




#define MPC5125_PSC_UART_DEVICE_ADDRESS(dev)    ((MPC5125_PSC_STRUCT_PTR)(BSP_IMMR_BASE + _mpc5125_psc_address[dev]))
#define MPC5125_PSC_FIFO_DEVICE_ADDRESS(dev)     (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->PSC_FIFO)

/* PSC offset definitions */
#define MPC5125_PSC_UART0_OFFSET                0x11000
#define MPC5125_PSC_UART1_OFFSET                0x11100
#define MPC5125_PSC_UART2_OFFSET                0x11200
#define MPC5125_PSC_UART3_OFFSET                0x11300
#define MPC5125_PSC_UART4_OFFSET                0x11400
#define MPC5125_PSC_UART5_OFFSET                0x11500 
#define MPC5125_PSC_UART6_OFFSET                0x11600
#define MPC5125_PSC_UART7_OFFSET                0x11700
#define MPC5125_PSC_UART8_OFFSET                0x11800
#define MPC5125_PSC_UART9_OFFSET                0x11900

#define MPC5125_NUM_PSC                         10
#define MPC5125_PSC1                            0
#define MPC5125_PSC2                            1
#define MPC5125_PSC3                            2
#define MPC5125_PSC4                            3
#define MPC5125_PSC5                            4
#define MPC5125_PSC6                            5
#define MPC5125_PSC7                            6
#define MPC5125_PSC8                            7
#define MPC5125_PSC9                            8
#define MPC5125_PSC10                           9


#define PSC_MR1_RxRTS                           0x80
#define PSC_MR1_TimeOutEn                       0x20
#define PSC_MR1_PM_WITH_PARITY                  0x00
#define PSC_MR1_PM_FORCE_PARITY                 0x08
#define PSC_MR1_PM_NO_PARITY                    0x10
#define PSC_MR1_PM_MULTIDROP_MODE               0x18
#define PSC_MR1_PT_EVEN                         0x00
#define PSC_MR1_PT_ODD                          0x04
#define PSC_MR1_PT_LOW                          0x00
#define PSC_MR1_PT_HIGH                         0x04
#define PSC_MR1_BC_5                            0x00
#define PSC_MR1_BC_6                            0x01
#define PSC_MR1_BC_7                            0x02
#define PSC_MR1_BC_8                            0x03

#define PSC_MR2_CM_NORMAL                       0x00
#define PSC_MR2_CM_AUTOMATIC_ECHO               0x40
#define PSC_MR2_CM_LOCAL_LOOPBACK               0x80
#define PSC_MR2_CM_REMOTE_LOOPBACK              0xC0
#define PSC_MR2_TxRTS                           0x20
#define PSC_MR2_TxCTS                           0x10
#define PSC_MR2_SB_BC5_1                        0x00
#define PSC_MR2_SB_BC68_1                       0x07
#define PSC_MR2_SB_BC5_1_5                      0x07
#define PSC_MR2_SB_BC58_1_5                     0x08
#define PSC_MR2_SB_BC58_2                       0x0f

#define PSC_CR_RESET_RECEIVER                   0x20
#define PSC_CR_RESET_TRANSMITTER                0x30
#define PSC_CR_RESET_ERROR                      0x40
#define PSC_CR_RESET_BREAK                      0x50
#define PSC_CR_START_BREAK                      0x60
#define PSC_CR_STOP_BREAK                       0x70
#define PSC_CR_TX_ENABLE                        0x04
#define PSC_CR_TX_DISABLE                       0x08
#define PSC_CR_RX_ENABLE                        0x01
#define PSC_CR_RX_DISABLE                       0x02

#define PSC_SR_RB                               0x8000
#define PSC_SR_FE                               0x4000
#define PSC_SR_PE                               0x2000
#define PSC_SR_ORERR                            0x1000
#define PSC_SR_TxEMP                            0x0800
#define PSC_SR_CDE                              0x0080
#define PSC_SR_ERROR                            0x0040
#define PSC_SR_TIMEOUT                          0x0020


#define PSC_CSR_RCS_IPB_16X                     0xd000
#define PSC_CSR_RCS_MCLK_16X                    0xe000
#define PSC_CSR_RCS_IPB_10X                     0xf000
#define PSC_CSR_TCS_IPB_16X                     0x0d00
#define PSC_CSR_TCS_MCLK_16X                    0x0e00
#define PSC_CSR_TCS_IPB_10X                     0x0f00

#define PSC_SICR_SIM_UART                       0x00000000
#define PSC_SICR_SIM_UART_WITH_DCD              0x08000000
#define PSC_SICR_SIM_CODEC_8                    0x01000000
#define PSC_SICR_SIM_CODEC_12                   0x09000000
#define PSC_SICR_SIM_CODEC_16                   0x02000000
#define PSC_SICR_SIM_CODEC_20                   0x0A000000
#define PSC_SICR_SIM_CODEC_24                   0x07000000
#define PSC_SICR_SIM_CODEC_32                   0x0F000000
#define PSC_SICR_MSTR                           0x00004000
#define PSC_SICR_CPOL                           0x00002000
#define PSC_SICR_CPHA                           0x00001000
#define PSC_SICR_UseEOF                         0x00000800
#define PSC_SICR_GenClk                         0x00800000
#define PSC_SICR_SPI                            0x00008000
#define PSC_SICR_SHDIR_LSB                      0x10000000

#define PSC_ISR_IPC                             0x8000
#define PSC_ISR_ORERR                           0x1000
#define PSC_ISR_URERR                           0x0800
#define PSC_ISR_TxEMP                           0x0800
#define PSC_ISR_DB                              0x0400
#define PSC_ISR_ERROR                           0x0040
#define PSC_ISR_TIMEOUT                         0x0020
#define PSC_ISR_CMD_SEND                        0x0008
#define PSC_ISR_DATA_OVR                        0x0004
#define PSC_ISR_DATA_VALID                      0x0002
#define PSC_ISR_UNEX_RX_SLOT                    0x0001

#define PSC_IMR_IPC                             0x8000
#define PSC_IMR_ORERR                           0x1000
#define PSC_IMR_URERR                           0x0800
#define PSC_IMR_TxEMP                           0x0800
#define PSC_IMR_DB                              0x0400
#define PSC_IMR_ERROR                           0x0040
#define PSC_IMR_TIMEOUT                         0x0020
#define PSC_IMR_CMD_SEND                        0x0008
#define PSC_IMR_DATA_OVR                        0x0004
#define PSC_IMR_DATA_VALID                      0x0002
#define PSC_IMR_UNEX_RX_SLOT                    0x0001

#define PSC_ISR_FFULL                           0x0200
#define PSC_ISR_RxRDY                           0x0200
#define PSC_ISR_TxRDY                           0x0100
#define PSC_IMR_FFULL                           0x0200
#define PSC_IMR_RxRDY                           0x0200
#define PSC_IMR_TxRDY                           0x0100

#define PSC_FIFO_CMD_EOF                        (1<<8)
#define PSC_FIFO_CMD_RESET_SLICE                (1<<7)
#define PSC_FIFO_CMD_DMA_EN                     (1<<2)
#define PSC_FIFO_CMD_SLICE_EN                   (1)


#define PSC_FIFO_SR_DEBUG_MODE                  (1<<15)
#define PSC_FIFO_SR_SIZE_ZERO                   (1<<7)
#define PSC_FIFO_SR_MEM_ERROR                   (1<<6)
#define PSC_FIFO_SR_DATA_READY                  (1<<5)
#define PSC_FIFO_SR_ORERR                       (1<<4)
#define PSC_FIFO_SR_URERR                       (1<<3)
#define PSC_FIFO_SR_ALARM                       (1<<2)
#define PSC_FIFO_SR_FULL                        (1<<1)
#define PSC_FIFO_SR_EMPTY                       (1)

#define PSC_FIFO_ISR_MEM_ERROR                   (1<<6)
#define PSC_FIFO_ISR_DATA_READY                  (1<<5)
#define PSC_FIFO_ISR_ORERR                       (1<<4)
#define PSC_FIFO_ISR_URERR                       (1<<3)
#define PSC_FIFO_ISR_ALARM                       (1<<2)
#define PSC_FIFO_ISR_FULL                        (1<<1)
#define PSC_FIFO_ISR_EMPTY                       (1)

#define PSC_FIFO_IMR_MEM_ERROR                   (1<<6)
#define PSC_FIFO_IMR_DATA_READY                  (1<<5)
#define PSC_FIFO_IMR_ORERR                       (1<<4)
#define PSC_FIFO_IMR_URERR                       (1<<3)
#define PSC_FIFO_IMR_ALARM                       (1<<2)
#define PSC_FIFO_IMR_FULL                        (1<<1)
#define PSC_FIFO_IMR_EMPTY                       (1)

#define PSC_IPCR_DCD                             (1)
#define PSC_IPCR_CTS                             (2)

#define PSC_OP_RTS                               (1)

typedef volatile struct
{
   vuchar   MR1;         // 0x00 Mode Register 1              MR1 8 R/W
   RESERVED_REGISTER(0x01,0x04);
   vuchar   MR2;         // 0x04 Mode Register 1              MR2 8 R/W
   RESERVED_REGISTER(0x05,0x08);
   vuint_16 SR;          // 0x08 Status Register              SR 16 R
   RESERVED_REGISTER(0x0a,0x0c);
   vuchar   CSR;         // 0x0c Command Register             CR 16 R/W       <-- BYTE docs appear to be wrong
   RESERVED_REGISTER(0x0d,0x10);
   vuchar   CR;          // 0x10 Command Register             CR 16 R/W       <-- BYTE docs appear to be wrong
   RESERVED_REGISTER(0x11,0x14);
   vuint_32 buffer;      // 0x14 Rx Buffer Register           RB 32 R       <-- BYTE docs appear to be wrong
   //RESERVED_REGISTER(0x15,0x18);
   vuchar   IPCR;        // 0x18 Input Port Change Register   IPCR 8 R
   RESERVED_REGISTER(0x19,0x1c);
   vuchar   ACR;         // 0x1c Input Port Change Register   ACR 8 R
   RESERVED_REGISTER(0x1d,0x20);
   vuint_16 ISR;         // 0x20 Interrupt Status Register    ISR 16 R
   RESERVED_REGISTER(0x22,0x24);
   vuint_16 IMR;         // 0x24 Interrupt Mask Register      IMR 16 W
   RESERVED_REGISTER(0x26,0x28);
   vuchar   CTUR;        // 0x28 Counter Timer Upper Register CTUR 8 W
   RESERVED_REGISTER(0x29,0x2C);
   vuchar   CTLR;        // 0x2C Counter Timer Lower Register CTLR 8 W
   RESERVED_REGISTER(0x2d,0x30);
   vuint_32 CCR;         // 0x30 Codec Clock Register         CCR R/W
   vuint_32 AC97Slots;   // 0x34
   vuint_32 AC97CMD;     // 0x38
   vuint_32 AC97Data;    // 0x3c
   RESERVED_REGISTER(0x40,0x44);
   vuchar   IP;          // 0x44 Input Port Register          IP 8 R
   RESERVED_REGISTER(0x45,0x48);
   vuchar   OP1;         // 0x48 Output Port 1 Bit Set        OP1 8 W
   RESERVED_REGISTER(0x49,0x4C);
   vuchar   OP0;         // 0x4C Output Port 0 Bit Set        OP0 8 W
   RESERVED_REGISTER(0x4d,0x50);
   vint_32  SICR;        // 0x50 PSC Control Register         SICR 32 R/W     <-- BYTE docs appear to be wrong
   RESERVED_REGISTER(0x54,0x80);
   vuint_32 TX_CMD;      // 0x80 Command register for PSCn TX slice - PSCn_TX_CMD                 26.2.1.1 32 R/W
   vuint_32 TX_ALARM;    // 0x84 Alarm level for PSCn TX slice - PSCn_TX_ALARM                    26.2.1.2 32 R/W
   vuint_32 TX_SR;       // 0x88 Status register for PSCn TX slice - PSCn_TX_SR                   26.2.1.3 32 R
   vuint_32 TX_ISR;      // 0x8C Interrupt status register for PSCn TX slice - PSCn_TX_ISR        26.2.1.4 32 R
   vuint_32 TX_IMR;      // 0x90 Interrupt mask register for PSCn TX slice - PSCn_TX_IMR          26.2.1.5 32 R/W
   vuint_32 TX_COUNT;    // 0x94 FIFO count for PSCn TX slice - PSCn_TX_COUNT                     26.2.1.6 32 R
   vuint_32 TX_POINTER;  // 0x98 FIFO pointer for PSCn TX slice - PSCn_TX_POINTER                 26.2.1.7 32 R
   vuint_32 TX_SIZE;     // 0x9C FIFO size register for PSCn TX slice - PSCn_TX_SIZE              26.2.1.8 32 R/W
   RESERVED_REGISTER(0xa0,0xbc);
   vuint_32 TX_DATA;     // 0xBC FIFO data register for PSCn TX slice - PSCn_TX_DATA              26.2.1.9 32 R/W
   vuint_32 RX_CMD;      // 0xC0 Command register for PSCn RX slice - PSCn_RX_CMD                 26.2.1.1 32 R/W
   vuint_32 RX_ALARM;    // 0xC4 Alarm level for PSCn RX slice - PSCn_RX_ALARM                    26.2.1.2 32 R/W
   vuint_32 RX_STAT;     // 0xC8 Status register for PSCn RX slice - PSCn_RX_STAT                 26.2.1.3 32 R
   vuint_32 RX_ISR;      // 0xCC Interrupt status register for PSCn RX slice - PSCn_RX_INTSTAT    26.2.1.4 32 R
   vuint_32 RX_IMR;      // 0xD0 Interrupt mask register for PSCn RX slice - PSCn_RX_INTMASK      26.2.1.5 32 R/W
   vuint_32 RX_COUNT;    // 0xD4 FIFO count for PSCn RX slice - PSCn_RX_COUNT                     26.2.1.6 32 R
   vuint_32 RX_POINTER;  // 0xD8 FIFO pointer for PSCn RX slice - PSCn_RX_POINTER                 26.2.1.7 32 R
   vuint_32 RX_SIZE;     // 0xDC FIFO size register for PSCn RX slice - PSCn_RX_SIZE              26.2.1.8 32 R/W
   RESERVED_REGISTER(0xe0,0xfc);
   vuint_32 RX_DATA;     // 0xFC FIFO data register for PSCn RX slice - PSCn_RX_DATA              26.2.1.9 32 R/W

} MPC5125_PSC_STRUCT, _PTR_ MPC5125_PSC_STRUCT_PTR;


typedef volatile struct mpc5125_psc_fifo_controller {
   vuint_32 COMMAND;           // 0xF00 FIFO command 26.2.1.10 32 R/W
   vuint_32 INTERRUPT_STATUS;  // 0xF04 FIFO interrupt status 26.2.1.11 32 R
   vuint_32 DMA_REQUEST;       // 0xF08 FIFO DMA request  26.2.1.12 32 R
   RESERVED_REGISTER(0x0c,0x10);
   vuint_32 DEBUG;             // 0xF10 FIFO debug  26.2.1.13 32 R/W
   RESERVED_REGISTER(0x14,0x100);
} MPC5125_PSC_FIFO_CONTROLLER, _PTR_ MPC5125_PSC_FIFO_CONTROLLER_PTR;

extern const uint_32 _mpc5125_psc_address[];

#endif

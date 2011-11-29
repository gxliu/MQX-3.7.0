#ifndef __mpc5125_ioc_h__
#define __mpc5125_ioc_h__
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
* $FileName: mpc512x_ioc.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define MPC5125_IOC_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->IOC)

#define IO_CONTROL_ENABLE           (0x01)

#define IO_CONTROL_SLEW_RATE_MASK   (0x3)
#define IO_CONTROL_SLEW_RATE_0      (0)
#define IO_CONTROL_SLEW_RATE_1      (0x1)
#define IO_CONTROL_SLEW_RATE_2      (0x2)
#define IO_CONTROL_SLEW_RATE_3      (0x3)

#define IO_CONTROL_SCHMITT_MASK     (0x04)
#define IO_CONTROL_SCHMITT_ENABLE   (0x04)
#define IO_CONTROL_SCHMITT_DISABLE  (0x00)

#define IO_CONTROL_PULL_MASK        (0x18)
#define IO_CONTROL_NO_PULL          (0x0)
#define IO_CONTROL_PULL_UP          (0x18)
#define IO_CONTROL_PULL_DOWN        (0x08)

#define IO_CONTROL_FUNCTION_MASK    (0x60)
#define IO_CONTROL_FUNCTION_0       (0)
#define IO_CONTROL_FUNCTION_1       (0x20)
#define IO_CONTROL_FUNCTION_2       (0x40)
#define IO_CONTROL_FUNCTION_3       (0x60)


typedef volatile struct
{
   uchar MEM;              // 0x00 MEM pad control register R/W
   uchar GBOBE;            // 0x01 GBOBE pad control register R/W
   RESERVED_REGISTER(0x02,0x04);
   uchar LPC_CLK;          // 0x04 LPC_CLK pad control register R/W
   uchar LPC_OE_B;         // 0x05 LPC_OE_B pad control register R/W
   uchar LPC_RWB;          // 0x06 LPC_RWB pad control register R/W
   uchar LPC_CS0_B;        // 0x07 LPC_CS0_B pad control register R/W
   uchar LPC_ACK_B;        // 0x08 LPC_ACK_B pad control register R/W
   uchar LPC_AX03;         // 0x09 LPC_AX03 pad control register R/W
   uchar EMB_AX02;         // 0x0a EMB_AX02 pad control register R/W
   uchar EMB_AX01;         // 0x0b EMB_AX01 pad control register R/W
   uchar EMB_AX00;         // 0x0c EMB_AX00 pad control register R/W
   uchar EMB_AD31;         // 0x0d EMB_AD31 pad control register R/W
   uchar EMB_AD30;         // 0x0e EMB_AD30 pad control register R/W
   uchar EMB_AD29;         // 0x0f EMB_AD29 pad control register R/W
   uchar EMB_AD28;         // 0x10 EMB_AD28 pad control register R/W
   uchar EMB_AD27;         // 0x11 EMB_AD27 pad control register R/W
   uchar EMB_AD26;         // 0x12 EMB_AD26 pad control register R/W
   uchar EMB_AD25;         // 0x13 EMB_AD25 pad control register R/W
   uchar EMB_AD24;         // 0x14 EMB_AD24 pad control register R/W
   uchar EMB_AD23;         // 0x15 EMB_AD23 pad control register R/W
   uchar EMB_AD22;         // 0x16 EMB_AD22 pad control register R/W
   uchar EMB_AD21;         // 0x17 EMB_AD21 pad control register R/W
   uchar EMB_AD20;         // 0x18 EMB_AD20 pad control register R/W
   uchar EMB_AD19;         // 0x19 EMB_AD19 pad control register R/W
   uchar EMB_AD18;         // 0x1a EMB_AD18 pad control register R/W
   uchar EMB_AD17;         // 0x1b EMB_AD17 pad control register R/W
   uchar EMB_AD16;         // 0x1c EMB_AD16 pad control register R/W
   uchar EMB_AD15;         // 0x1d EMB_AD15 pad control register R/W
   uchar EMB_AD14;         // 0x1e EMB_AD14 pad control register R/W
   uchar EMB_AD13;         // 0x1f EMB_AD13 pad control register R/W
   uchar EMB_AD12;         // 0x20 EMB_AD12 pad control register R/W
   uchar EMB_AD11;         // 0x21 EMB_AD11 pad control register R/W
   uchar EMB_AD10;         // 0x22 EMB_AD10 pad control register R/W
   uchar EMB_AD09;         // 0x23 EMB_AD09 pad control register R/W
   uchar EMB_AD08;         // 0x24 EMB_AD08 pad control register R/W
   uchar EMB_AD07;         // 0x25 EMB_AD07 pad control register R/W
   uchar EMB_AD06;         // 0x26 EMB_AD06 pad control register R/W
   uchar EMB_AD05;         // 0x27 EMB_AD05 pad control register R/W
   uchar EMB_AD04;         // 0x28 EMB_AD04 pad control register R/W
   uchar EMB_AD03;         // 0x29 EMB_AD03 pad control register R/W
   uchar EMB_AD02;         // 0x2a EMB_AD02 pad control register R/W
   uchar EMB_AD01;         // 0x2b EMB_AD01 pad control register R/W
   uchar EMB_AD00;         // 0x2c EMB_AD00 pad control register R/W
   uchar NFC_CE0_B;        // 0x2d NFC_CE0_B pad control register R/W
   uchar NFC_RB;           // 0x2e NFC_RB pad control register R/W
   uchar DIU_CLK;          // 0x2f DIU_CLK pad control register R/W
   uchar DIU_DE;           // 0x30 DIU_DE pad control register R/W
   uchar DIU_HSYNC;        // 0x31 DIU_HSYNC pad control register R/W
   uchar DIU_VSYNC;        // 0x32 DIU_VSYNC pad control register R/W
   uchar DIU_LD00;         // 0x33 DIU_LD00 pad control register R/W
   uchar DIU_LD01;         // 0x34 DIU_LD01 pad control register R/W
   uchar DIU_LD02;         // 0x35 DIU_LD02 pad control register R/W
   uchar DIU_LD03;         // 0x36 DIU_LD03 pad control register R/W
   uchar DIU_LD04;         // 0x37 DIU_LD04 pad control register R/W
   uchar DIU_LD05;         // 0x38 DIU_LD05 pad control register R/W
   uchar DIU_LD06;         // 0x39 DIU_LD06 pad control register R/W
   uchar DIU_LD07;         // 0x3a DIU_LD07 pad control register R/W
   uchar DIU_LD08;         // 0x3b DIU_LD08 pad control register R/W
   uchar DIU_LD09;         // 0x3c DIU_LD09 pad control register R/W
   uchar DIU_LD10;         // 0x3d DIU_LD10 pad control register R/W
   uchar DIU_LD11;         // 0x3e DIU_LD11 pad control register R/W
   uchar DIU_LD12;         // 0x3f DIU_LD12 pad control register R/W
   uchar DIU_LD13;         // 0x40 DIU_LD13 pad control register R/W
   uchar DIU_LD14;         // 0x41 DIU_LD14 pad control register R/W
   uchar DIU_LD15;         // 0x42 DIU_LD15 pad control register R/W
   uchar DIU_LD16;         // 0x43 DIU_LD16 pad control register R/W
   uchar DIU_LD17;         // 0x44 DIU_LD17 pad control register R/W
   uchar DIU_LD18;         // 0x45 DIU_LD18 pad control register R/W
   uchar DIU_LD19;         // 0x46 DIU_LD19 pad control register R/W
   uchar DIU_LD20;         // 0x47 DIU_LD20 pad control register R/W
   uchar DIU_LD21;         // 0x48 DIU_LD21 pad control register R/W
   uchar DIU_LD22;         // 0x49 DIU_LD22 pad control register R/W
   uchar DIU_LD23;         // 0x4a DIU_LD23 pad control register R/W
   uchar I2C2_SCL;         // 0x4b I2C2_SCL pad control register R/W
   uchar I2C2_SDA;         // 0x4c I2C2_SDA pad control register R/W
   uchar CAN1_TX;          // 0x4d CAN1_TX pad control register R/W
   uchar CAN2_TX;          // 0x4e CAN2_TX pad control register R/W
   uchar I2C1_SCL;         // 0x4f I2C1_SCL pad control register R/W
   uchar I2C1_SDA;         // 0x50 I2C1_SDA pad control register R/W
   uchar FEC1_TXD_2;       // 0x51 FEC1_TXD_2 pad control register R/W
   uchar FEC1_TXD_3;       // 0x52 FEC1_TXD_3 pad control register R/W
   uchar FEC1_RXD_2;       // 0x53 FEC1_RXD_2 pad control register R/W
   uchar FEC1_RXD_3;       // 0x54 FEC1_RXD_3 pad control register R/W
   uchar FEC1_CRS;         // 0x55 FEC1_CRS pad control register R/W
   uchar FEC1_TX_ER;       // 0x56 FEC1_TX_ER pad control register R/W
   uchar FEC1_RXD_1;       // 0x57 FEC1_RXD_1 pad control register R/W
   uchar FEC1_TXD_1;       // 0x58 FEC1_TXD_1 pad control register R/W
   uchar FEC1_MDC;         // 0x59 FEC1_MDC pad control register R/W
   uchar FEC1_RX_ER;       // 0x5a FEC1_RX_ER pad control register R/W
   uchar FEC1_MDIO;        // 0x5b FEC1_MDIO pad control register R/W
   uchar FEC1_RXD_0;       // 0x5c FEC1_RXD_0 pad control register R/W
   uchar FEC1_TXD_0;       // 0x5d FEC1_TXD_0 pad control register R/W
   uchar FEC1_TX_CLK;      // 0x5e FEC1_TX_CLK pad control register R/W
   uchar FEC1_RX_CLK;      // 0x5f FEC1_RX_CLK pad control register R/W
   uchar FEC1_RX_DV;       // 0x60 FEC1_RX_DV pad control register R/W
   uchar FEC1_TX_EN;       // 0x61 FEC1_TX_EN pad control register R/W
   uchar FEC1_COL;         // 0x62 FEC1_COL pad control register R/W
   uchar USB1_DATA0;       // 0x63 USB1_DATA0 pad control register R/W
   uchar USB1_DATA1;       // 0x64 USB1_DATA1 pad control register R/W
   uchar USB1_DATA2;       // 0x65 USB1_DATA2 pad control register R/W
   uchar USB1_DATA3;       // 0x66 USB1_DATA3 pad control register R/W
   uchar USB1_DATA4;       // 0x67 USB1_DATA4 pad control register R/W
   uchar USB1_DATA5;       // 0x68 USB1_DATA5 pad control register R/W
   uchar USB1_DATA6;       // 0x69 USB1_DATA6 pad control register R/W
   uchar USB1_DATA7;       // 0x6a USB1_DATA7 pad control register R/W
   uchar USB1_STOP;        // 0x6b USB1_STOP pad control register R/W
   uchar USB1_CLK;         // 0x6c USB1_CLK pad control register R/W
   uchar USB1_NEXT;        // 0x6d USB1_NEXT pad control register R/W
   uchar USB1_DIR;         // 0x6e USB1_DIR pad control register R/W
   uchar SDHC1_CLK;        // 0x6f SDHC1_CLK pad control register R/W
   uchar SDHC1_CMD;        // 0x70 SDHC1_CMD pad control register R/W
   uchar SDHC1_D0;         // 0x71 SDHC1_D0 pad control register R/W
   uchar SDHC1_D1;         // 0x72 SDHC1_D1 pad control register R/W
   uchar SDHC1_D2;         // 0x73 SDHC1_D2 pad control register R/W
   uchar SDHC1_D3;         // 0x74 SDHC1_D3 pad control register R/W
   uchar PSC_MCLK_IN;      // 0x75 PSC_MCLK_IN pad control register R/W
   uchar PSC0_0;           // 0x76 PSC0_0 pad control register R/W
   uchar PSC0_1;           // 0x77 PSC0_1 pad control register R/W
   uchar PSC0_2;           // 0x78 PSC0_2 pad control register R/W
   uchar PSC0_3;           // 0x79 PSC0_3 pad control register R/W
   uchar PSC0_4;           // 0x7a PSC0_4 pad control register R/W
   uchar PSC1_0;           // 0x7b PSC1_0 pad control register R/W
   uchar PSC1_1;           // 0x7c PSC1_1 pad control register R/W
   uchar PSC1_2;           // 0x7d PSC1_2 pad control register R/W
   uchar PSC1_3;           // 0x7e PSC1_3 pad control register R/W
   uchar PSC1_4;           // 0x7f PSC1_4 pad control register R/W
   uchar J1850_TX;         // 0x80 J1850_TX pad control register R/W
   uchar J1850_RX;         // 0x81 J1850_RX pad control register R/W
   RESERVED_REGISTER(0x82,0x1000);
} MPC5125_IO_CONTROL_STRUCT, _PTR_ MPC5125_IO_CONTROL_STRUCT_PTR;

#endif

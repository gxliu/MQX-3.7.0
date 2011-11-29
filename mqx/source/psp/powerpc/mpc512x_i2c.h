#ifndef __mpc5125_i2c_h__
#define __mpc5125_i2c_h__
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
* $FileName: mpc512x_i2c.h$
* $Version :  3.7.3.0$
* $Date    :  Feb-7-2011$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define MPC5125_I2C_NUM_MODULES     3
#define MPC5125_I2C_ADDR()          (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->I2C)
#define MPC5125_I2C_MODULE_ADDR(n)  (&((MPC5125_I2C_MODULE_STRUCT_PTR) MPC5125_I2C_ADDR())[n])


/***************** Register Bit Fields and Values *****************************/
// I2C

// address register
#define I2C_MADR_EN_MASK                 0xFE000000
#define I2C_MADR_EN_SHIFT                25

// frequency divide register              
#define I2C_MFDR_EN_MASK                 0xFE000000
#define I2C_MFDR_EN_SHIFT                25

//control register
#define I2C_MCR_EN_MASK                  ((0x1 << 31))
#define I2C_MCR_EN_SHIFT                 31
#define I2C_MCR_IEN_MASK                 ((0x1 << 30))
#define I2C_MCR_IEN_SHIFT                30
#define I2C_MCR_STA_MASK                 ((0x1 << 29))
#define I2C_MCR_STA_SHIFT                29
#define I2C_MCR_TX_MASK                  ((0x1 << 28))
#define I2C_MCR_TX_SHIFT                 28
#define I2C_MCR_TXAK_MASK                ((0x1 << 27))
#define I2C_MCR_TXAK_SHIFT               27
#define I2C_MCR_RSTA_MASK                ((0x1 << 26))
#define I2C_MCR_RSTA_SHIFT               26
//status register
#define I2C_MSR_CF_MASK                  ((0x1 << 31))
#define I2C_MSR_CF_SHIFT                 31
#define I2C_MSR_AAS_MASK                 ((0x1 << 30))
#define I2C_MSR_AAS_SHIFT                30
#define I2C_MSR_BB_MASK                  ((0x1 << 29))
#define I2C_MSR_BB_SHIFT                 29
#define I2C_MSR_AL_MASK                  ((0x1 << 28))
#define I2C_MSR_AL_SHIFT                 28
#define I2C_MSR_AKF_MASK                 ((0x1 << 27))
#define I2C_MSR_AKF_SHIFT                27
#define I2C_MSR_SRW_MASK                 ((0x1 << 26))
#define I2C_MSR_SRW_SHIFT                26
#define I2C_MSR_IF_MASK                  ((0x1 << 25))
#define I2C_MSR_IF_SHIFT                 25
#define I2C_MSR_RXAK_MASK                ((0x1 << 24))
#define I2C_MSR_RXAK_SHIFT               24
// data register
#define I2C_MDR_EN_MASK                  0xFF000000
#define I2C_MDR_EN_SHIFT                 24

#define I2C_MDR_D7_MASK                  ((0x1 << 31))
#define I2C_MDR_D7_SHIFT                 31
#define I2C_MDR_D6_MASK                  ((0x1 << 30))
#define I2C_MDR_D6_SHIFT                 30
#define I2C_MDR_D5_MASK                  ((0x1 << 29))
#define I2C_MDR_D5_SHIFT                 29
#define I2C_MDR_D4_MASK                  ((0x1 << 28))
#define I2C_MDR_D4_SHIFT                 28
#define I2C_MDR_D3_MASK                  ((0x1 << 27))
#define I2C_MDR_D3_SHIFT                 27
#define I2C_MDR_D2_MASK                  ((0x1 << 26))
#define I2C_MDR_D2_SHIFT                 26
#define I2C_MDR_D1_MASK                  ((0x1 << 25))
#define I2C_MDR_D1_SHIFT                 25
#define I2C_MDR_D0_MASK                  ((0x1 << 24))
#define I2C_MDR_D0_SHIFT                 24

typedef volatile struct mpc5125_i2c_module_struct {
   vuint_32 MADR;    // 0x00 I2C_MADRx - I2Cx Address Register R/W 0x0000_0000 19.3.1.1/19-9
   vuint_32 MFDR;    // 0x04 I2C_MFDRx - I2Cx Frequency Divider Register R/W 0x0000_0000 19.3.1.2/19-9
   vuint_32 MCR;     // 0x08 I2C_MCRx  - I2Cx Control Register R/W 0x0000_0000 19.3.1.3/19-16
   vuint_32 MSR;     // 0x0C I2C_MSRx  - I2Cx Status Register R/W 0x8000_0000 19.3.1.4/19-17
   vuint_32 MDR;     // 0x10 I2C_MDRx  - I2Cx Date I/O Register R/W 0x0000_0000 19.3.1.5/19-20
   RESERVED_REGISTER(0x14,0x20);
 } MPC5125_I2C_MODULE_STRUCT, _PTR_ MPC5125_I2C_MODULE_STRUCT_PTR;
typedef volatile struct mpc5125_i2c_module_struct _PTR_ VMPC5125_I2C_MODULE_STRUCT_PTR;

typedef volatile struct mpc5125_i2c_struct {
   MPC5125_I2C_MODULE_STRUCT MODULE[MPC5125_I2C_NUM_MODULES];
   vuint_32 ICR;     // 0x60 I2C_ICR  - I2C Interrupt Control Register R/W 0x1500_0000 19.3.1.6/19-20
   vuint_32 MIFR;    // 0x64 I2C_MIFR - I2C Filter Register R/W 0x0000_0000 19.3.1.7/19-21
   RESERVED_REGISTER(0x68,0x100);
 } MPC5125_I2C_STRUCT, _PTR_ MPC5125_I2C_STRUCT_PTR;

#endif
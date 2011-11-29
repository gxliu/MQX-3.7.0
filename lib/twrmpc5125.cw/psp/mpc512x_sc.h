#ifndef __mpc5125_sc_h__
#define __mpc5125_sc_h__
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
* $FileName: mpc512x_sc.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define MPC5125_SC_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->SYSCON)
#define MPC5125_SC_SPCR_TBEN (1<<22)


typedef volatile struct mpc5125_system_configuration_struct {
   uint_32 IMMRBAR;        // 0 0x000 Configuration registers (IMMRBAR) Fixed 1 MB window size
   RESERVED_REGISTER(0x004,0x020);
   uint_32 LPBus_Boot_AW;  // 1 0x020 LocalPlus Bus Boot Access Window Register 
   uint_32 LPBus_CS0_AW;   // 2 0x024 LocalPlus Bus CS0 Access Window Register 
   uint_32 LPBus_CS1_AW;   // 3 0x028 LocalPlus Bus CS1 Access Window Register 
   uint_32 LPBus_CS2_AW;   // 4 0x02C LocalPlus Bus CS2 Access Window Register 
   uint_32 LPBus_CS3_AW;   // 5 0x030 LocalPlus Bus CS3 Access Window Register 
   uint_32 LPBus_CS4_AW;   // 6 0x034 LocalPlus Bus CS4 Access Window Register 
   uint_32 LPBus_CS5_AW;   // 7 0x038 LocalPlus Bus CS5 Access Window Register 
   uint_32 LPBus_CS6_AW;   // 8 0x03C LocalPlus Bus CS6 Access Window Register 
   uint_32 LPBus_CS7_AW;   // 9 0x040 LocalPlus Bus CS7 Access Window Register 
   RESERVED_REGISTER(0x044,0x0a0);
   uint_32 LPBus_DDR_SDRAM_AW_BAR;  // 10 0x0A0 DDR SDRAM Local Access Window Base Address Register 
   uint_32  LPBus_DDR_SDRAM_AW_AR;  //    0x0A4 DDR SDRAM Local Access Window Attributes Register 
   RESERVED_REGISTER(0x0A8,0x0C4);
   uint_32 LPBus_CSRAM_AW; // 11 0x0C4 SRAM Base Address Register Fixed 256 KB window siz
   uint_32 LPBus_NFC_AW; // 12 0x0C8  NFC Base Address Register Fixed 1 MB window size
   RESERVED_REGISTER(0x0CC,0x100); 
   uint_32 SPRIDR;   // 0x100 System Part and Revision ID Register (SPRIDR) R 0x8019_0010 2.3.1.1.1/2-15
   uint_32 SPCR;     // 0x104 System Priority Configuration Register (SPCR) R/W 0x0000_0010 2.3.1.1.2/2-16
   RESERVED_REGISTER(0x108,0x200); 
} MPC5125_SYSTEM_CONFIGURATION_STRUCT, _PTR_ MPC5125_SYSTEM_CONFIGURATION_STRUCT_PTR;
#endif
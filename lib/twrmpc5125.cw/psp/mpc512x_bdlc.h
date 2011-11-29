#ifndef __mpc5125_bdlc_h__
#define __mpc5125_bdlc_h__
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
* $FileName: mpc512x_bdlc.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/


typedef volatile struct mpc5125_bdlc_struct
{
   vuint_8 DLCBCR1;     // 0x00 BDLC Control Register 1 (BDLC_DLCBCR1)                 R/W 0xC0 6.3.2.1/6-5
   vuint_8 DLCBSVR;     // 0x01 BDLC State Vector Register (BDLC_DLCBSVR)              R 0x00 6.3.2.2/6-6
   RESERVED_REGISTER(0x02,0x04);               
   vuint_8 DLCBCR2;     // 0x04 BDLC Control Register 2 (BDLC_DLCBCR2)                 R/W 0x40 6.3.2.3/6-8
   vuint_8 DLCBDR;      // 0x05 BDLC Data Register (BDLC_DLCBDR)                       R/W 0x00 6.3.2.4/6-13
   RESERVED_REGISTER(0x06,0x08);               
   vuint_8 DLCBARD;     // 0x08 BDLC Analog Round Trip Delay Register (BDLC_DLCBARD)   R/W 0x50 6.3.2.5/6-14
   vuint_8 DLCBRSR;     // 0x09 BDLC Rate Select Register (BDLC_DLCBRSR)               R/W 0x00 6.3.2.6/6-16
   RESERVED_REGISTER(0x0A,0x0C);               
   vuint_8 DLCSCR;      // 0x0C BDLC Control Register (BDLC_DLCSCR)                    R/W 0x00 6.3.2.7/6-17
   vuint_8 DLCBSTAT;    // 0x0D BDLC Status Register (BDLC_DLCBSTAT)                   R/W 0x00 6.3.2.8/6-18
   RESERVED_REGISTER(0x0E,0x100);               
} MPC5125_BDLC_STRUCT, _PTR_ MPC5125_BDLC_STRUCT_PTR;


#endif
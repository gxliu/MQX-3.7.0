#ifndef __mpc5125_iim_h__
#define __mpc5125_iim_h__
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
* $FileName: mpc512x_iim.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

typedef volatile struct mpc5125_iim_struct {
   vuint_32 STAT;       // 0x000 IIM_STAT Status register                              R/W 0x0000_0000 17.3.2.1/17-2
   vuint_32 STATM;      // 0x004 IIM_STATM Status IRQ Mask register                    R/W 0x0000_0000 17.3.2.2/17-3
   vuint_32 ERR;        // 0x008 IIM_ERR Module Errors register                        R/W 0x0000_000U 17.3.2.3/17-4
   vuint_32 EMASK;      // 0x00C IIM_EMASK Error IRQ Mask register                     R/W 0x0000_0000 17.3.2.4/17-5
   vuint_32 FCTL;       // 0x010 IIM_FCTL Fuse Control register                        R/W 0x0000_0030 17.3.2.5/17-6
   vuint_32 UA;         // 0x014 IIM_UA Upper Address register                         R/W 0x0000_0000 17.3.2.6/17-7
   vuint_32 LA;         // 0x018 IIM_LA Lower Address register                         R/W 0x0000_0000 17.3.2.7/17-8
   vuint_32 SDAT;       // 0x01C IIM_SDAT Explicit Sense Data register                 R   0x0000_0000 17.3.2.8/17-9
   RESERVED_REGISTER(0x020,0x02C);              
   vuint_32 PREG_P;     // 0x02C IIM_PREG_P Program Protection register                R/W 0x0000_0000 17.3.2.9/17-9
   RESERVED_REGISTER(0x30,0x03C);              
   vuint_32 DIVIDE;     // 0x03C IIM_DIVIDE Divide Factor register                     R/W 0x0000_0042 17.3.2.10/17-10
   RESERVED_REGISTER(0x040,0xc00);              
   vuint_32 FBAC1;      // 0xC00 IIM_FBAC1 Fuse Bank 1 Protection Register             R/W 0x0000_00UU 17.3.2.11/17-11
   vuint_8 FB1W1[0x7c]; // 0xC04 0xC7F IIM_FB1W1 Fuse Bank 1 Data (available for user) R/W 0x0000_00UU 17.3.2.12/17-12
   RESERVED_REGISTER(0xC80,0x1000);              
} MPC5125_IIM_STRUCT, _PTR_ MPC5125_IIM_STRUCT_PTR;


#endif
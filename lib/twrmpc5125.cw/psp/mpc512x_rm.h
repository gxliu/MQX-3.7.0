#ifndef __mpc5125_rm_h__
#define __mpc5125_rm_h__
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
* $FileName: mpc512x_rm.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define MPC5125_RM_BASE()      ((MPC5125_RM_STRUCT_PTR)     (MPC5125_GET_IMMR() + MPC5125_RESET_MODULE_BASE))

#define RM_RCWLR_SYSPLL_MASK      (0x0f000000)
#define RM_RCWLR_SYSPLL_SHIFT     (24)
#define RM_RCWLR_COREPLL_MASK     (0x00070000)

#define RM_RCWLR_COREPLL_SHIFT    (16)
#define RM_RCWLR_SYSDIV_MASK      (0x00000700)
#define RM_RCWLR_SYSDIV_SHIFT     (8)


// 4  Reset Module 
typedef volatile struct mpc5125_reset_struct
{
   vuint_32 RCWL;    // 0x00 Reset Configuration Word Low (RCWL) Register     R   0x0U0U_0U00 4.6.1/4-9
   vuint_32 RCWH;    // 0x04 Reset Configuration Word High (RCWH) Register    R   0xUUU0_UU00 4.6.2/4-9
   RESERVED_REGISTER(0x08,0x10);               
   vuint_32 RSR;     // 0x10 Reset Status Register (RSR)                       R/W 0x6000_0000 4.6.3/4-10
   vuint_32 RMR;     // 0x14 Reset Mode Register (RMR)                         R/W 0x0000_0000 4.6.4/4-12
   vuint_32 RPR;     // 0x18 Reset Protection Register (RPR)                   R/W 0x0000_0000 4.6.5/4-13
   vuint_32 RCR;     // 0x1C Reset Control Register (RCR)                      R/W 0x0000_0000 4.6.6/4-13
   vuint_32 RCER;    // 0x20 Reset Control Enable Register (RCER)              R/W 0x0000_0000 4.6.7/4-14
   RESERVED_REGISTER(0x24,0x100);               
} MPC5125_RESET_STRUCT, _PTR_ MPC5125_RESET_STRUCT_PTR;

#endif

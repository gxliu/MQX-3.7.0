#ifndef __mpc5125_pmc_h__
#define __mpc5125_pmc_h__
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
* $FileName: mpc512x_pmc.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

typedef volatile struct mpc5125_pmc_struct
{
   vuint_32 PMCCR;   // 0x00 PMC Configuration Register (PMC_PMCCR)           R/W 0x0000_0000 24.2.2.1/24-2
   vuint_32 PMCER;   // 0x04 PMC Event Register (PMC_PMCER)                   R/W 0x0000_0000 24.2.2.2/24-3
   vuint_32 PMCMR;   // 0x08 PMC Mask Register (PMC_PMCMR)                    R/W 0x0000_0000 24.2.2.3/24-4
   vuint_32 PMCSR;   // 0x0C PMC CORE_PLL Shadow Register (PMC_PMCSR)         R/W 0x0000_0000 24.2.2.4/24-5
   vuint_32 PMCWSE;  // 0x10 PMC Wakeup Source Enable Register (PMC_PMCWSE)   R/W 0x0000_0000 24.2.2.5/24-5
   vuint_32 PMCWSP;  // 0x14 PMC Wakeup Source Polarity Register (PMC_PMCWSP) R/W 0x0000_00FF 24.2.2.6/24-6
   RESERVED_REGISTER(0x18,0x100);               
} MPC5125_PMC_STRUCT, _PTR_ MPC5125_PMC_STRUCT_PTR;


#endif
#ifndef __mpc5125_ipic_h__
#define __mpc5125_ipic_h__
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
* $FileName: mpc512x_ipic.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/


#define MPC5125_IPIC_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->IPIC)

/* Integrated Programmable Interrupt Controller */
typedef volatile struct mpc5125_ipic_struct {
   vuint_32 SICFR;      /* 00: System Global Interrupt Configuration Register */
   vuint_32 SIVCR;      /* 04: System Global Interrupt Vecotr Register */
   vuint_32 SIPNRH;     /* 08: System Internal Interrupt Pending Register High */
   vuint_32 SIPNRL;     /* 0c: System Internal Interrupt Pending Register Low */
   vuint_32 SIPRRA;     /* 10: System Internal Interrupt Group A Priority Register */
   vuint_32 SIPRRB;     /* 14: System Internal Interrupt Group B Priority Register */
   vuint_32 SIPRRC;     /* 18: System Internal Interrupt Group C Priority Register */
   vuint_32 SIPRRD;     /* 1c: System Internal Interrupt Group D Priority Register */
   vuint_32 SIMSRH;     /* 20: System Internal Interrupt Mask Register High */
   vuint_32 SIMSRL;     /* 24: System Internal Interrupt Mask Register Low */
   vuint_32 SICNR;      /* 28: System Internal Interrupt Control Register */
   vuint_32 SEPNR;      /* 2c: System External Interrupt Pending Register */
   vuint_32 SMPRRA;     /* 30: System Mixed Interrupt Group A Priority Register */
   vuint_32 SMPRRB;     /* 34: System Mixed Interrupt Group B Priority Register */
   vuint_32 SEMSR;      /* 38: System External Interrupt Mask Register */
   vuint_32 SECNR;      /* 3c: System External Interrupt Control Register */
   vuint_32 SERSR;      /* 40: System Error Status Register */
   vuint_32 SERMR;      /* 44: System Error Mask Register */
   RESERVED_REGISTER(0x48,0x4c);
   vuint_32 SEPCR;      /* 4c: System External Inrerrupt Polarity Check  Register */
   vuint_32 SIFCRH;     /* 50: System Internal Interrupt Force Register High */
   vuint_32 SIFCRL;     /* 54: System Internal Interrupt Force Register Low */
   vuint_32 SEFCR;      /* 58: System External Interrupt Force Register */
   vuint_32 SERFR;      /* 5c: System Error Force Register */
   vuint_32 SCVCR;      /* 60: System Critical Interrupt Vector Register */
   vuint_32 SMVCR;      /* 64: System Management Interrupt Vector register */
   RESERVED_REGISTER(0x68,0x100);
   
} MPC5125_IPIC_STRUCT, _PTR_ MPC5125_IPIC_STRUCT_PTR;

#endif

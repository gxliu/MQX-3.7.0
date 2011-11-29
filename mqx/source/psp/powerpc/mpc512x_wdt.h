#ifndef __mpc5125_wdt_h__
#define __mpc5125_wdt_h__
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
* $FileName: mpc512x_wdt.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

typedef volatile struct mpc5125_wdt_struct
{
   RESERVED_REGISTER(0x00,0x04);               
   vuint_32 SWCRR; // 0x04 WDT_SWCRR - Software watchdog control register  R/W 0x0000_0004 29.2.2.1/29-2
   vuint_32 SWCNR; // 0x08 WDT_SWCNR - Software watchdog count register    R   0x0000_0000 29.2.2.2/29-3
   RESERVED_REGISTER(0x0c,0x0e);               
   vuint_16 SWSRR; // 0x0E SWSRR - Software watchdog service register        W 0x0000 29.2.2.3/29-4
   RESERVED_REGISTER(0x10,0x100);               
} MPC5125_WDT_STRUCT, _PTR_ MPC5125_WDT_STRUCT_PTR;


#endif
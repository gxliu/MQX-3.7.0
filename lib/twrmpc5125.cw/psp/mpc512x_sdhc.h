#ifndef __mpc5125_sdhc_h__
#define __mpc5125_sdhc_h__
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
* $FileName: mpc512x_sdhc.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

typedef volatile struct mpc5125_sdhc_struct
{
   vuint_32 STR_STP_CLK;        // 0x00 SDHC_STR_STP_CLK SDHC Clock Control Register               R/W 0x0000_0000 28.3.2.1/28-4
   vuint_32 STATUS;             // 0x04 SDHC_STATUS SDHC Status Register                           R/W 0x0000_0000 28.3.2.2/28-5
   vuint_32 CLK_RATE;           // 0x08 SDHC_CLK_RATE SDHC Card Clock Rate Register                R/W 0x0000_0008 28.3.2.3/28-9
   vuint_32 CMD_DAT_CONT;       // 0x0C SDHC_CMD_DAT_CONT SDHC Command and Data Control Register   R/W 0x0000_0000 28.3.2.4/28-10
   vuint_32 RES_TO;             // 0x10 SDHC_RES_TO SDHC Response Time-out Register                R/W 0x0000_0040 28.3.2.5/28-12
   vuint_32 READ_TO;            // 0x14 SDHC_READ_TO SDHC Read Time-out Register                   R/W 0x0000_FFFF 28.3.2.6/28-13
   vuint_32 BLK_LEN;            // 0x18 SDHC_BLK_LEN SDHC Block Length Register                    R/W 0x0000_0000 28.3.2.7/28-14
   vuint_32 NOB;                // 0x1C SDHC_NOB SDHC Number of Block Register                     R/W 0x0000_0000 28.3.2.8/28-15
   vuint_32 REV_NO;             // 0x20 SDHC_REV_NO SDHC Revision Number Register                  R   0x0000_0400 28.3.2.9/28-16
   vuint_32 INT_CNTR;           // 0x24 SDHC_INT_CNTR SDHC Interrupt Control Register              R/W 0x0000_0000 28.3.2.10/28-17
   vuint_32 CMD;                // 0x28 SDHC_CMD SDHC Command Number Register                      R/W 0x0000_0000 28.3.2.11/28-20
   vuint_32 ARG;                // 0x2C SDHC_ARG SDHC Command Argument Register                    R/W 0x0000_0000 28.3.2.12/28-21
   RESERVED_REGISTER(0x30,0x34);              
   vuint_32 RES_FIFO;           // 0x34 SDHC_RES_FIFO SDHC Command Response FIFO Access Register   R   0x0000_0000 28.3.2.13/28-21
   vuint_32 BUFFER_ACCESS;      // 0x38 SDHC_BUFFER_ACCESS SDHC Data Buffer Access Register        R/W 0x0000_0000 28.3.2.14/28-22
   RESERVED_REGISTER(0x3C,0x100);              
} MPC5125_SDHC_STRUCT, _PTR_ MPC5125_SDHC_STRUCT_PTR;

#endif
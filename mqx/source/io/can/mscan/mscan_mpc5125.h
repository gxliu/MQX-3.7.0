#ifndef _mscan_mpc5125_h_
#define _mscan_mpc5125_h_ 1
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
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
* $FileName: mscan_mpc5125.h$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains mpc5125 specific mscan information.
*
*   Feb.8/04    2.50          Initial version
*
*END************************************************************************/


#define MSCAN_DEVICES         MPC5125_NUM_MSCAN
/*
** MSCAN addresses
*/
#define MSCAN_ADDRESS_1             (MPC5125_MSCAN1_ADDR())
#define MSCAN_ADDRESS_2             (MPC5125_MSCAN2_ADDR())
#define MSCAN_ADDRESS_3             (MPC5125_MSCAN2_ADDR())
#define MSCAN_ADDRESS_4             (MPC5125_MSCAN2_ADDR())

#define MSCAN1_INT_VECTOR       MPC5125_MSCAN1_VECTOR
#define MSCAN2_INT_VECTOR       MPC5125_MSCAN2_VECTOR
#define MSCAN3_INT_VECTOR       MPC5125_MSCAN3_VECTOR
#define MSCAN4_INT_VECTOR       MPC5125_MSCAN4_VECTOR


/*
** MSCAN clock source  
*/
//#define MSCAN_IPBUS_CLK               _mpc5125_get_ipb_clock(BSP_EXCLK_CLOCK) // input clock is IPBUS clock
//#define MSCAN_OSC_CLK             (BSP_EXCLK_CLOCK) //input clock is oscillator clock
#define MSCAN_CLK_SOURCE_IPB     1

#define MSCAN_RXMSG_STRUCT       MPC5125_MSCAN_MSG_STRUCT
#define MSCAN_RXMSG_STRUCT_PTR   MPC5125_MSCAN_MSG_STRUCT_PTR
#define VMSCAN_RXMSG_STRUCT_PTR  MPC5125_MSCAN_MSG_STRUCT_PTR
#define MSCAN_TXMSG_STRUCT       MPC5125_MSCAN_MSG_STRUCT
#define MSCAN_TXMSG_STRUCT_PTR   MPC5125_MSCAN_MSG_STRUCT_PTR
#define VMSCAN_TXMSG_STRUCT_PTR  MPC5125_MSCAN_MSG_STRUCT_PTR
#define MSCAN_REG_STRUCT         MPC5125_MSCAN_STRUCT
#define MSCAN_REG_STRUCT_PTR     MPC5125_MSCAN_STRUCT_PTR
#define VMSCAN_REG_STRUCT_PTR    MPC5125_MSCAN_STRUCT_PTR

#endif

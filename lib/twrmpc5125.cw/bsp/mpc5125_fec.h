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
* $FileName: mpc5125_fec.h$
* $Version : 3.5.1.0$
* $Date    : Feb-24-2010$
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for the ethernet drivers for the MCF5225x processor
*
*END************************************************************************/
#ifndef _mpc5125_fec_h
#define _mpc5125_fec_h 1


#define MPC512X_FEC_DEVICE_COUNT            2
   
#define MPC512X_FEC_RX_BUFFER_ALIGNMENT     64     // check
#define MPC512X_FEC_TX_BUFFER_ALIGNMENT     64     // check
#define MPC512X_FEC_BD_ALIGNMENT            64     // check
/*
** PHY MII Speed (MDC - Management Data Clock)
*/
#define MPC512X_PHY_MII_SPEED                             (2500000L)

// Needs to be here, because a SMALL packet must be a multiple of the RX_BUFFER_ALIGNMENT
#define MCF5XXX_SMALL_PACKET_SIZE           ENET_ALIGN(64, MPC512X_FEC_RX_BUFFER_ALIGNMENT)
       
// temporary - these should be generic PSP functions.
#define _psp_set_int_prio_and_level(vector, level, sublev, unmask)    _mpc5125_enable_interrupt(vector)
#define _psp_int_mask(x)                    _mpc5125_disable_interrupt(x)

#endif


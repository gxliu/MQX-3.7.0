#ifndef __mpc5125_gpt_h__
#define __mpc5125_gpt_h__
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
* $FileName: mpc512x_gpt.h$
* $Version :  3.5.1.0$
* $Date    :  Feb-24-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/


#define MPC5125_GPT1_ADDR()    (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->GPT1)
#define MPC5125_GPT2_ADDR()    (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->GPT2)

#define MCF5125_NUM_GPTS                           (2)
#define MCF5125_CHANNELS_PER_GPT                   (8)

#define MPC5125_GPT_EMSR_CE                        (0x00001000)
#define MPC5125_GPT_EMSR_CONTINUOUS                (0x00000400)
#define MPC5125_GPT_EMSR_OPEN_DRN                  (0x00000200)
#define MPC5125_GPT_EMSR_INTEN                     (0x00000100)
#define MPC5125_GPT_EMSR_GPIO_INPUT                (0x00000000)
#define MPC5125_GPT_EMSR_GPIO_OUTPUT_0             (0x00000020)
#define MPC5125_GPT_EMSR_GPIO_OUTPUT_1             (0x00000030)
#define MPC5125_GPT_EMSR_TIMER_MS_DISABLED         (0x00000000)
#define MPC5125_GPT_EMSR_TIMER_MS_INPUT_CAPTURE    (0x00000001)
#define MPC5125_GPT_EMSR_TIMER_MS_OUTPUT_COMPARE   (0x00000002)
#define MPC5125_GPT_EMSR_TIMER_MS_PMW              (0x00000003)
#define MPC5125_GPT_EMSR_TIMER_MS_GPIO             (0x00000004)

#define MPC5125_GPT_SR_CLEAR_ALL                   (0x0000001f)



typedef volatile struct mpc5125_gpt_channel_struct
{
   vuint_32 EMSR;  // 0x00 GPT0 Enable and Mode Select Register R/W 0x0000_0000 15.2.1.1/15-4
   vuint_32 CIOR;  // 0x04 GPT0 Counter Input and up/down counter Output Register R/W 0x0000_0000 15.2.1.2/15-7
   vuint_32 PWMCR; // 0x08 GPT0 PWM Configuration Register R/W 0x0000_0000 15.2.1.3/15-8
   vuint_32 SR;    // 0x0C GPT0 Status Register R 0x0000_0000 15.2.1.4/15-9
} MPC5125_GPT_CHANNEL_STRUCT, _PTR_ MPC5125_GPT_CHANNEL_STRUCT_PTR;

typedef volatile struct mpc5125_gpt_struct
{
   MPC5125_GPT_CHANNEL_STRUCT  CHANNEL[MCF5125_CHANNELS_PER_GPT];
   RESERVED_REGISTER(0x80,0x100);
} MPC5125_GPT_STRUCT, _PTR_ MPC5125_GPT_STRUCT_PTR;

#endif
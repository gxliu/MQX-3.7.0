/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $FileName: timer_mpc512x.c$
* $Version : 3.7.2.0$
* $Date    : Feb-22-2011$
*
* Comments:
*
*   This file contains timer functions for use with all supported mpc512x CPUs
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h"



MPC5125_GPT_CHANNEL_STRUCT_PTR _mpc512x_gpt_channel_address( uint_32 channel)
{
   MPC5125_GPT_STRUCT_PTR gpt_ptr;

   uint_32 gpt = channel/MCF5125_CHANNELS_PER_GPT;
   uint_32 gpt_channel = channel-gpt*MCF5125_CHANNELS_PER_GPT;

   if (gpt==0) {
      gpt_ptr = MPC5125_GPT1_ADDR();
   } else if (gpt==1) {
      gpt_ptr = MPC5125_GPT2_ADDR();
   } else {
      return NULL;
   }
   return &gpt_ptr->CHANNEL[gpt_channel];
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc512x_gpt_init
* Returned Value  : Timer Hardware Reference Value
* Comments        :
*   this function will set up MPC512x GPT(General Purpose Timer)
*   to interrupt the processor on every system tick
*   (default: 5 ms or 200 ticks per second)
*
*END*---------------------------------------------------------------------*/

uint_32 _mpc512x_gpt_init
   ( 
      uint_32     channel,
      uint_32     vector,
      
      /* [IN] the tick rate wanted in ticks per second */
      uint_32     resolution,
      
      /* [IN] the processor external clock speed */
      uint_32     external_clock
   )
{ 
   MPC5125_GPT_CHANNEL_STRUCT_PTR   chan_ptr;
   PSP_SUPPORT_STRUCT_PTR           support_ptr;
   uint_32                          reference, clk, prescaler, count;
   
   if (channel>(MCF5125_NUM_GPTS*MCF5125_CHANNELS_PER_GPT)) {
      return 0;
   }
   
   support_ptr = (PSP_SUPPORT_STRUCT_PTR)_mpc5125_get_psp_support();
   chan_ptr = _mpc512x_gpt_channel_address(channel);
   
   /* Disable GPT interrupt at IPIC level */
   _mpc5125_disable_interrupt(vector);
   
   /* Disable GPT */
   chan_ptr->EMSR = 0;
   
   clk = _mpc5125_get_ipb_clock(external_clock);
   reference = (clk / resolution);

   // Find minimum prescaler
   for (prescaler=1;((reference/prescaler)>0xffff);prescaler++) {
   }
   count = reference/prescaler;

   /* Set Prescaler and Count values */
   chan_ptr->CIOR = (prescaler<<16) | count;
   
   /* Enable clock and Interrupt */
   chan_ptr->EMSR = MPC5125_GPT_EMSR_CE | MPC5125_GPT_EMSR_CONTINUOUS | MPC5125_GPT_EMSR_INTEN | MPC5125_GPT_EMSR_TIMER_MS_GPIO;   
                      
                      
   /* Enable Timer Interrupt at IPIC level  */
   _mpc5125_enable_interrupt(vector);

   return(reference);
} 




/*ISR*********************************************************************
*
* Function Name    : _mpc512x_gpt_isr
* Returned Value   : void
* Comments         :
*    The timer ISR is the interrupt handler for the clock tick.
*
*END**********************************************************************/

void _mpc512x_gpt_isr
   (
      pointer channel
   )
{ /* Body */
   MPC5125_GPT_CHANNEL_STRUCT_PTR   chan_ptr;
   
   chan_ptr = _mpc512x_gpt_channel_address((uint_32)channel);
   
   /* Clear Satus Register */
   chan_ptr->SR = MPC5125_GPT_SR_CLEAR_ALL;

   _time_notify_kernel();
} 


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc512x_gpt_get_hwticks
* Returned Value   : none
* Comments         :
*    This function returns the number of hw ticks that have elapsed
* since the last interrupt - since this can't be read, 0 is returned
*
*END*----------------------------------------------------------------------*/

uint_32 _mpc512x_gpt_get_hwticks
   (
      pointer channel
   )
{
   return 0;
}



/* EOF */

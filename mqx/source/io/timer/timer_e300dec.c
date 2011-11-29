/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
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
* $FileName: timer_e300dec.c$
* $Version : 3.7.1.1$
* $Date    : Mar-30-2011$
*
* Comments:
* 
*    This file contains definitions for the PPC e300 core decrementer
*    timer utility functions.
*
*END***********************************************************************/


#include "mqx_inc.h"
#include "bsp.h"
#include "bsp_prv.h"

/*ISR*********************************************************************
*
* Function Name    : _bsp_decrementer_isr
* Returned Value   : void
* Comments         :
*    The decrementer ISR.  Needed because the decrementer WILL interrupt
*
*END**********************************************************************/
void _e300_decrementer_isr
   (
      pointer dummy
   )
{ 
   KERNEL_DATA_STRUCT_PTR  kernel_data;
   uint_32 preload;

   _GET_KERNEL_DATA(kernel_data);
   preload = kernel_data->TIMER_HW_REFERENCE;
 //  _PSP_SPR_SET(E300CORE_DEC,preload);

   _time_notify_kernel();
}

uint_32 _e300_decrementer_get_hwticks
   (
      pointer param
   )
{
   KERNEL_DATA_STRUCT_PTR  kernel_data;
   uint_32 result, preload, hwticks=0;

   _GET_KERNEL_DATA(kernel_data);
   preload = kernel_data->TIMER_HW_REFERENCE;

   _PSP_SPR_GET(hwticks,E300CORE_DEC);

   if (hwticks > preload) {
      result = 0xffffffff - hwticks;
   } else {
      result = preload - hwticks;
   }

   return result;
} 


#if MQX_CPU==PSP_CPU_MPC5125
uint_32 _e300_decrementer_timer_init
   (
      /* [IN] the tick rate wanted */
      uint_32 frequency,

      /* [IN] External clock speed */
      uint_32 ext_clock,

      /* [OUT] DEC value loaded */
      uint_32_ptr preload_ptr
   )
{
   MPC5125_SYSTEM_CONFIGURATION_STRUCT_PTR sc_ptr = MPC5125_SC_ADDR();
   uint_32 dec_freq,preload,hid0;

   dec_freq = _mpc5125_get_ppc_clock(ext_clock);
   preload = (dec_freq/frequency + 1 ) >> 3;

  _PSP_SPR_SET(E300CORE_DEC,preload);

   _PSP_SPR_GET(hid0,E300CORE_HID0);
   hid0 |= (1<<6);
   _PSP_SPR_SET(E300CORE_HID0,hid0);

   *preload_ptr = preload;
   sc_ptr->SPCR |= MPC5125_SC_SPCR_TBEN;
   
   return MQX_OK;
}

#elif PSP_MQX_CPU_IS_MPC830x

uint_32 _e300_decrementer_timer_init
   (
      /* [IN] the tick rate wanted */
      uint_32 frequency,

      /* [IN] External clock speed */
      uint_32 ext_clock,

      /* [OUT] DEC value loaded */
      uint_32_ptr preload_ptr
   )
{
   MPC83xx_SYSCON_STRUCT_PTR syscon_ptr;
   uint_32 dec_freq,preload,hid0;
   uint_32                      immr;
   
   immr = (uint_32)BSP_IMMR_BASE;

   syscon_ptr = (MPC83xx_SYSCON_STRUCT_PTR)(immr + MPC83xx_SYSCON_BASE);  

   dec_freq = _mpc83xx_get_core_clock(BSP_CLKIN);
   preload = (dec_freq/frequency + 1 ) >> 2;
 
   
  _PSP_SPR_SET(E300CORE_DEC,preload);

   _PSP_SPR_GET(hid0,E300CORE_HID0);
   hid0 |= (1<<6);
   _PSP_SPR_SET(E300CORE_HID0,hid0);

   *preload_ptr = preload;
   syscon_ptr->SPCR |= MPC83XX_SYSCON_TBEN;
   
   return MQX_OK;
}
#endif

/* EOF */
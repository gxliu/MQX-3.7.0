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
* $FileName: mpc5125.c$
* $Version :  3.7.5.0$
* $Date    :  Feb-18-2011$
*
* Comments:
*
*   This file contains utility functions for use with the MPC5125 CPU.
*
*END************************************************************************/

#include "mqx_inc.h"



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_initialize_support
* Returned Value   : none
* Comments         :
*  Initilize the support functions for the MPC5125
*
*END*------------------------------------------------------------------------*/

void _mpc5125_initialize_support
   (
      /* [IN] IMMR base address */
      uint_32 immr
   )
{ 
   KERNEL_DATA_STRUCT_PTR       kernel_data;
   PSP_SUPPORT_STRUCT_PTR       support_ptr;

   _GET_KERNEL_DATA(kernel_data);

   support_ptr =  _mem_alloc_system_zero((uint_32)sizeof(PSP_SUPPORT_STRUCT));

   kernel_data->PSP_SUPPORT_PTR = support_ptr;
   
   support_ptr->IMMR_BASE = (pointer)immr;
} 


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_get_psp_support
* Returned Value   : none
* Comments         :
*   returns the address of the support information 
*
*END*------------------------------------------------------------------------*/

PSP_SUPPORT_STRUCT_PTR _mpc5125_get_psp_support(void)
{ 
   KERNEL_DATA_STRUCT_PTR kernel_data;

   _GET_KERNEL_DATA(kernel_data);
   return (kernel_data->PSP_SUPPORT_PTR);
} 


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_get_immr
* Returned Value   : none
* Comments         :
*   returns the address of the dpram of the MPC5125
*
*END*------------------------------------------------------------------------*/

pointer _mpc5125_get_immr(void)
{ 
   KERNEL_DATA_STRUCT_PTR kernel_data;
   PSP_SUPPORT_STRUCT_PTR support_ptr;

   _GET_KERNEL_DATA(kernel_data);
   support_ptr = kernel_data->PSP_SUPPORT_PTR;
   return (pointer) support_ptr->IMMR_BASE;

} 

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_gpio_pin_config
* Returned Value  : none
* Comments        :
*   configures GPIO pin spcified
*
*END*---------------------------------------------------------------------*/

void _mpc5125_gpio_pin_config
   (
      /* [IN] which port to set GPIO1/GPIO2 */
      uint_32 port,
      
      /* [IN] the pin number to set 0 - 31 */
      uint_32 pin,

      /* [IN] is this an output */
      boolean outputp,
      
      /* [IN] is this pin Open drain?, dummy if pin is input pin */
      boolean opdrain,
      
      /* [IN] is this pin drives interrupt */
      boolean interrupt,
      
      /* [IN] iedge detection mode  */
      uint_32 edge
   )
{ 
   MPC5125_GPIO_STRUCT_PTR      gpio_ptr;
   uint_32                      bit;
   vuint_32_ptr                 icr_ptr;
   uint_32                      icr_shift;
   
#if MQX_CHECK_ERRORS
   if (port > MPC5125_NUM_GPIO_PORTS){
      return;
   } 
#endif

   gpio_ptr = MPC5125_GPIO_ADDR(port);

   bit = (1 << (31 - pin));
   
   if(outputp) {
      gpio_ptr->DIR |= bit;
      if(opdrain) {
         gpio_ptr->ODR |= bit;
      }
      else {
         gpio_ptr->ODR &= ~bit;
      } 
   }
   else {
     gpio_ptr->DIR &= ~bit;
     if(interrupt) {
        gpio_ptr->IER |= bit; // Clear interrupt first
        gpio_ptr->IMR |= bit;
        
        if (pin < 16) {
           icr_ptr = &gpio_ptr->ICR1;
           icr_shift = 15-pin;
        } else {
           icr_ptr = &gpio_ptr->ICR2;
           icr_shift = 31-pin;
        }
        *icr_ptr &= ~(3<<icr_shift);
           *icr_ptr |= ((edge&3)<<icr_shift);
     }
     else {
        gpio_ptr->IMR &= ~bit;  
     } 
   } 
} 


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_gpio_get_data
* Returned Value  : TRUE if pin status is HIGH, else FALSE
* Comments        :
*   Gets the status of GPIO pin data
*
*END*---------------------------------------------------------------------*/

boolean _mpc5125_gpio_get_data
   (
      /* [IN] which port to set GPIO1/GPIO2 */
      uint_32 port,
      
      /* [IN] the pin number to set 0 - 31 */
      uint_32 pin
   )
{ 
   MPC5125_GPIO_STRUCT_PTR gpio_ptr;
   
#if MQX_CHECK_ERRORS
   if (port > MPC5125_NUM_GPIO_PORTS){
      return;
   } 
#endif

   gpio_ptr = MPC5125_GPIO_ADDR(port);
   _PSP_SYNC();
   return((gpio_ptr->DAT & (1 << (31 - pin))) ? TRUE : FALSE);
} 


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _MPC5125_gpio_set_data
* Returned Value  : none
* Comments        :
*   Sets the GPIO pin output to HIGH
*
*END*---------------------------------------------------------------------*/

void _mpc5125_gpio_set_data
   (
      /* [IN] which port to set GPIO1/GPIO2 */
      uint_32 port,
      
      /* [IN] the pin number to set 0 - 31 */
      uint_32 pin,
      
      /* [IN] Data bit High/Low */
      boolean status
   )
{ 
   MPC5125_GPIO_STRUCT_PTR gpio_ptr;
   
#if MQX_CHECK_ERRORS
   if (port > MPC5125_NUM_GPIO_PORTS){
      return;
   } 
#endif

   gpio_ptr = MPC5125_GPIO_ADDR(port);
   
   if(status) {
      gpio_ptr->DAT |= (1 << (31 - pin));
   }
   else {
      gpio_ptr->DAT &= ~(1 << (31 - pin));  
   } 
} 


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_gpio_get_event
* Returned Value  : TRUE if event status is HIGH, else FALSE
* Comments        :
*   Gets the status of GPIO pin data
*
*END*---------------------------------------------------------------------*/

boolean _mpc5125_gpio_get_event
   (
      /* [IN] which port to set GPIO1/GPIO2 */
      uint_32 port,
      
      /* [IN] the pin number to set 0 - 31 */
      uint_32 pin
   )
{
   MPC5125_GPIO_STRUCT_PTR gpio_ptr;
   
#if MQX_CHECK_ERRORS
   if (port > MPC5125_NUM_GPIO_PORTS){
      return;
   } 
#endif

   gpio_ptr = MPC5125_GPIO_ADDR(port);
   
   return((gpio_ptr->IER & (1 << (31 - pin))) ? TRUE : FALSE);
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_gpio_clear_event
* Returned Value  : none
* Comments        :
*   Sets the GPIO pin output to HIGH
*
*END*---------------------------------------------------------------------*/

void _mpc5125_gpio_clear_event
   (
      /* [IN] which port to set GPIO1/GPIO2 */
      uint_32 port,
      
      /* [IN] the pin number to set 0 - 31 */
      uint_32 pin
   )
{
   MPC5125_GPIO_STRUCT_PTR gpio_ptr;
   
#if MQX_CHECK_ERRORS
   if (port > MPC5125_NUM_GPIO_PORTS){
      return;
   } 
#endif

   gpio_ptr = MPC5125_GPIO_ADDR(port);
   
   gpio_ptr->IER |= (1 << (31 - pin));
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_get_sys_clock
* Returned Value  : uint_32
* Comments        :
*   Determines SYS_CLK
*
*END*---------------------------------------------------------------------*/

// Note, because the divisor can be x.5, we double both the multiplier and divisor.
static uint_32 _mpc5125_SPMF_2x_ratio[] = { 136,2,24,32,40,48,56,64,72,80,88,96,104,112,120,128 };
static uint_32 _mpc5125_sys_div_2x_ratio[] = { 4,5,6,7,8,9,10,14,12,16,18,22,20,24,26,30,28,32,34,38,36,40,42,46,44,48,50,54,52,56,58,62,60,64,66 };

uint_32 _mpc5125_get_sys_clock
   (
      /* [IN] the speed of the external clock (EXTCLK) */
      uint_32 extclk
   )
{ 
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   uint_32  spmf,sysdiv;
   uint_64  fsys, fext;

   fext = extclk;
   
   spmf   = GET_FIELD_OF_REG(ccm_ptr,CCM,SPMR,SPMF);
   sysdiv = GET_FIELD_OF_REG(ccm_ptr,CCM,SCFR2,SYS_DIV);

   // Calculate sys clk bus frequency
   fsys = fext * _mpc5125_SPMF_2x_ratio[spmf] / _mpc5125_sys_div_2x_ratio[sysdiv];

   return (uint_32) fsys;
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_get_csb_clock
* Returned Value  : uint_32
* Comments        :
*   Determines CSB_CLK
*
*END*---------------------------------------------------------------------*/

uint_32 _mpc5125_get_csb_clock
   (
      /* [IN] the speed of the external clock (EXTCLK) */
      uint_32 external_clock
   )
{
   return  _mpc5125_get_sys_clock(external_clock)/2;
}
  
  
/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_get_ipb_clock
* Returned Value  : uint_32
* Comments        :
*   Determines IPS_CLK
*
*END*---------------------------------------------------------------------*/

uint_32 _mpc5125_get_ppc_clock
   (
      /* [IN] the speed of the external clock (EXTCLK) */
      uint_32 external_clock
   )
{ 
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   uint_32 cpmf, f_ppc, f_csb;
   
   f_csb = _mpc5125_get_csb_clock(external_clock);
   cpmf = GET_FIELD_OF_REG(ccm_ptr,CCM,SPMR,CPMF);

   if (cpmf>1){
      // Calculate ppc clock frequency
      f_ppc = f_csb * cpmf / 2;
   } else {
      f_ppc = f_csb;
   }
   return f_ppc;
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_get_diu_clock
* Returned Value  : uint_32
* Comments        :
*   Determines IPS_CLK
*
*END*---------------------------------------------------------------------*/

uint_32 _mpc5125_get_diu_clock
   (
      /* [IN] the speed of the external clock (EXTCLK) */
      uint_32 external_clock
   )
{ 
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   int_32 diu_div, f_diu, f_csb;
   
   f_csb = _mpc5125_get_csb_clock(external_clock);
   diu_div = GET_FIELD_OF_REG(ccm_ptr,CCM,SCFR1,DIU_DIV);

   f_diu = f_csb*4/diu_div;
   return f_diu;
}
   
   
/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_get_ipb_clock
* Returned Value  : uint_32
* Comments        :
*   Determines IPS_CLK
*
*END*---------------------------------------------------------------------*/

uint_32 _mpc5125_get_ipb_clock
   (
      /* [IN] the speed of the external clock (EXTCLK) */
      uint_32 external_clock
   )
{ 
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   int_32 ips_div, f_ipb, f_sys;
   
   f_ipb=0;
   f_sys = _mpc5125_get_sys_clock(external_clock);
   ips_div = GET_FIELD_OF_REG(ccm_ptr,CCM,SCFR1,IPS_DIV);

   if ((ips_div==2) || (ips_div==3)|| (ips_div==4)|| (ips_div==6)){
      // Calculate ips clock frequency
      f_ipb = (f_sys>>1) / ips_div;
   }
   return f_ipb;
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_set_diu_clock
* Returned Value  : uint_32
* Comments        :
*   
*
*END*---------------------------------------------------------------------*/

void _mpc5125_set_diu_clock(uint_32 extclk,uint_32 freq,uint_32 delay, boolean invert)
{
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   
    uint_32  fcsb, div, scfr1;

   fcsb = _mpc5125_get_csb_clock(extclk);
    div = (fcsb *4)/freq;

    scfr1 = ccm_ptr->SCFR1 & ~CCM_SCFR1_DIU_DIV_MASK;
    ccm_ptr->SCFR1 = scfr1 | (div & CCM_SCFR1_DIU_DIV_MASK);
    
   ccm_ptr->SCCR2 |= CCM_SCCR2_DIU_EN;
   
   SET_FIELD_OF_REG(ccm_ptr,CCM,DCCR,DLY_NUM,delay);
   SET_FIELD_OF_REG(ccm_ptr,CCM,DCCR,DLY_NUM,invert);
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_enable_i2c_clock
* Returned Value  : uint_32
* Comments        :
*   Determines I2C_CLK
*
*END*---------------------------------------------------------------------*/

void _mpc5125_enable_i2c_clock(void)
{
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   ccm_ptr->SCCR2 |= CCM_SCCR2_I2C_EN;
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc512x_enable_fec_clock
* Returned Value  : uint_32
* Comments        :
*   Determines FEC_CLK
*
*END*---------------------------------------------------------------------*/

void _mpc512x_enable_fec_clock(uint_32 fecnum)
{
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   
   if (fecnum==MPC5125_FEC0) {
      ccm_ptr->SCCR1 |= CCM_SCCR1_FEC1_EN;
   } else if (fecnum==MPC5125_FEC1) {
      ccm_ptr->SCCR1 |= CCM_SCCR1_FEC2_EN;
   }
}

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc512x_set_psc_clock
* Returned Value  : uint_32
* Comments        :
*   Determines PSC_CLK
*
*END*---------------------------------------------------------------------*/

boolean _mpc512x_set_psc_clock(uint_32 extclk, uint_32 pscdev, uint_32 src, uint_32 pscclk)
{
  MPC5125_CCM_STRUCT_PTR  ccm_ptr = MPC5125_CCM_ADDR();
  uint_32                 clk=0,div; 
  
  switch (src) { 
      case CCM_MxCCR_MSCANx_CLK_SRC_SYS_CLK:
         clk = _mpc5125_get_sys_clock(extclk);
         break;
         
      case CCM_MxCCR_MSCANx_CLK_SRC_REF_CLK:
         clk = extclk;
         break;
         
      case CCM_MxCCR_MSCANx_CLK_SRC_PSC_MCLK_IN:
         div = 0;
         break;
         
      case CCM_MxCCR_MSCANx_CLK_SRC_CAN_CLK_IN:
         div = 0;
         break;
         
      default:
         return FALSE;
      
   }       
 
   if (clk) {
      if (pscclk==0) {
         return FALSE;
       }
      div = clk/pscclk -1;
   }
   
   switch (pscdev) {
      case MPC5125_PSC1:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P0CCR,MCLK_0_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P0CCR,PSC0_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P0CCR,PSC0_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P0CCR,MCLK_0_EN,1);
         break;
         
      case MPC5125_PSC2:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P1CCR,MCLK_1_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P1CCR,PSC1_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P1CCR,PSC1_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P1CCR,MCLK_1_EN,1);
         break;
      
      case MPC5125_PSC3:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P2CCR,MCLK_2_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P2CCR,PSC2_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P2CCR,PSC2_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P2CCR,MCLK_2_EN,1);
         break;
                  
      case MPC5125_PSC4:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P3CCR,MCLK_3_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P3CCR,PSC3_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P3CCR,PSC3_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P3CCR,MCLK_3_EN,1);
         break;
                  
      case MPC5125_PSC5:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P4CCR,MCLK_4_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P4CCR,PSC4_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P4CCR,PSC4_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P4CCR,MCLK_4_EN,1);
         break;
      case MPC5125_PSC6:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P5CCR,MCLK_5_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P5CCR,PSC5_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P5CCR,PSC5_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P5CCR,MCLK_5_EN,1);
         break;

      case MPC5125_PSC7:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P6CCR,MCLK_6_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P6CCR,PSC6_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P6CCR,PSC6_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P6CCR,MCLK_6_EN,1);
         break;

      case MPC5125_PSC8:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P7CCR,MCLK_7_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P7CCR,PSC7_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P7CCR,PSC7_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P7CCR,MCLK_7_EN,1);
         break;

      case MPC5125_PSC9:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P8CCR,MCLK_8_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P8CCR,PSC8_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P8CCR,PSC8_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P8CCR,MCLK_8_EN,1);
         break;

      case MPC5125_PSC10:
         SET_FIELD_OF_REG(ccm_ptr,CCM,P9CCR,MCLK_9_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P9CCR,PSC9_MCLK_0_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P9CCR,PSC9_MCLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,P9CCR,MCLK_9_EN,1);
         break;

      default:
         return FALSE;
      
   }       
   return TRUE;
   
}

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc512x_enable_can_clock
* Returned Value  : uint_32
* Comments        :
*   Determines CAN_CLK
*
*END*---------------------------------------------------------------------*/

boolean _mpc512x_enable_can_clock(uint_32 extclk, uint_32 candev, uint_32 src, uint_32 canclk)
{
   MPC5125_CCM_STRUCT_PTR  ccm_ptr = MPC5125_CCM_ADDR();
   uint_32                 clk=0,div; 
  
   switch (src) { 
      case CCM_MxCCR_MSCANx_CLK_SRC_SYS_CLK:
         clk = _mpc5125_get_sys_clock(extclk);
         break;
         
      case CCM_MxCCR_MSCANx_CLK_SRC_REF_CLK:
         clk = extclk;
         break;
         
      case CCM_MxCCR_MSCANx_CLK_SRC_PSC_MCLK_IN:
         div = 0;
         break;
         
      case CCM_MxCCR_MSCANx_CLK_SRC_CAN_CLK_IN:
         div = 0;
         break;
         
      default:
         return FALSE;
      
   }       
 
   if (clk) {
      if (canclk==0) {
         return FALSE;
       }
      div = clk/canclk -1;
   }
  
   switch (candev) {
      case MPC5125_MSCAN1:
         SET_FIELD_OF_REG(ccm_ptr,CCM,M1CCR,MSCAN1_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M1CCR,MSCAN1_CLK_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M1CCR,MSCAN1_CLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M1CCR,MSCAN1_EN,1);
         break;
         
      case MPC5125_MSCAN2:
         SET_FIELD_OF_REG(ccm_ptr,CCM,M2CCR,MSCAN2_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M2CCR,MSCAN2_CLK_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M2CCR,MSCAN2_CLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M2CCR,MSCAN2_EN,1);
         break;
      
      case MPC5125_MSCAN3:
         SET_FIELD_OF_REG(ccm_ptr,CCM,M3CCR,MSCAN3_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M3CCR,MSCAN3_CLK_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M3CCR,MSCAN3_CLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M3CCR,MSCAN3_EN,1);
         break;
         
      case MPC5125_MSCAN4:
         SET_FIELD_OF_REG(ccm_ptr,CCM,M4CCR,MSCAN4_EN,0);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M4CCR,MSCAN4_CLK_SRC,src);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M4CCR,MSCAN4_CLK_DIV,div);
         SET_FIELD_OF_REG(ccm_ptr,CCM,M4CCR,MSCAN4_EN,1);
         break;
      
      default:
         return FALSE;
      
   }       
   return TRUE;
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_prioman_config
* Returned Value  : uint_32
* Comments        :
*   Sets PRIOMAN registers
*
*END*---------------------------------------------------------------------*/

void _mpc5125_prioman_config(uint_32_ptr prioman_set_ptr)
{
   MPC5125_PRIOMAN_STRUCT_PTR prioman_ptr = MPC5125_PRIOMAN_ADDR();
    uint_32_ptr prioman_reg_ptr = (uint_32_ptr) prioman_ptr;
    int i;


    for (i=0; i<23; i++)
    {
        prioman_reg_ptr[i] = prioman_set_ptr[i];
    }
}


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_csbarb_init
* Returned Value  : uint_32
* Comments        :
*   Initializes the Coherent Systems Bus (CSB) arbiter 
*
*END*---------------------------------------------------------------------*/

void _mpc5125_csbarb_init(void)
{
   MPC5125_CSB_ARBITER_STRUCT_PTR csbarb_ptr = MPC5125_CSBARB_ADDR();
  // set configuration values
#ifndef SPECIAL_CLK_CFG
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ACR,AACKWS,CSBARB_ACR_WS_0);
#else
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ACR,AACKWS,CSBARB_ACR_WS_1);
#endif
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ACR,PIPE_DEP,CSBARB_ACR_PIPE_DEP_2);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ACR,RPTCNT,CSBARB_ACR_PCI_TRAN_8);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ACR,WPARK,CSBARB_ACR_WPARK_CPU);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ACR,APARK,CSBARB_ACR_APARK_MSTR);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ACR,PARKM,CSBARB_ACR_PARKM_CPU);

   // disable event mask
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,ETEA,CSBARB_AMR_INT_DIS);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,RES,CSBARB_AMR_INT_DIS);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,ECW,CSBARB_AMR_INT_DIS);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,AO,CSBARB_AMR_INT_DIS);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,DTO,CSBARB_AMR_INT_DIS);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,ATO,CSBARB_AMR_INT_DIS);

   // set transfer error register
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ATER,ETEA,CSBARB_ATER_ERROR);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ATER,RES,CSBARB_ATER_ERROR);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ATER,ECW,CSBARB_ATER_ERROR);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ATER,AO,CSBARB_ATER_ERROR);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ATER,DTO,CSBARB_ATER_ERROR);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ATER,ATO,CSBARB_ATER_ERROR);

   // select event interrupt or reset
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AERR,ETEA,CSBARB_AERR_INT);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AERR,RES,CSBARB_AERR_INT);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AERR,ECW,CSBARB_AERR_INT);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AERR,AO,CSBARB_AERR_INT);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AERR,DTO,CSBARB_AERR_INT);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AERR,ATO,CSBARB_AERR_INT);

   // select event interrupt type (regular or MPC)
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AIDR,ETEA,CSBARB_AIDR_REG);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AIDR,RES,CSBARB_AIDR_REG);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AIDR,ECW,CSBARB_AIDR_REG);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AIDR,AO,CSBARB_AIDR_REG);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AIDR,DTO,CSBARB_AIDR_REG);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AIDR,ATO,CSBARB_AIDR_REG);

   // enable event mask
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,ETEA,CSBARB_AMR_INT_EN);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,RES,CSBARB_AMR_INT_EN);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,ECW,CSBARB_AMR_INT_EN);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,AO,CSBARB_AMR_INT_EN);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,DTO,CSBARB_AMR_INT_EN);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,AMR,ATO,CSBARB_AMR_INT_EN);

   // set time out values
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ATR,DTO,0);
   SET_FIELD_OF_REG(csbarb_ptr,CSBARB,ATR,ATO,0);
}

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_psc_fifo_slice_alloc
* Returned Value  : uint_32
* Comments        :
*   allocate fifo slice data 
*
*END*---------------------------------------------------------------------*/

#define MPC5125_PSC_MIN_FIFO_ALLOCATION_SIZE 8

// move to PSP support struct
static char _mpc5125_psc_fifo_slice_map[4096/MPC5125_PSC_MIN_FIFO_ALLOCATION_SIZE] = {0};

uint_32 _mpc5125_psc_fifo_slice_alloc(uint_32 psc, uint_32 requested)
{
   uint_32 i, found=0,start,end,offset = (uint_32) -1;
   
   for (i=0;((i<ELEMENTS_OF(_mpc5125_psc_fifo_slice_map)) &&  (found < requested)); i++) {
      if (_mpc5125_psc_fifo_slice_map[i] == 0) {
         if (found == 0) {
            // keep track of start of group of free bytes found
            start = i;
         }
         // increment number of consecutive bytes found.
         found += MPC5125_PSC_MIN_FIFO_ALLOCATION_SIZE;
         end = i;      
      } else {
         // reset number of consecutive bytes found.
         found = 0;
      }
   }         

   if (found >= requested) {
      for (i=start;i<=end;i++) {
         _mpc5125_psc_fifo_slice_map[i] = psc | 0x80;  
      }
      offset = start*MPC5125_PSC_MIN_FIFO_ALLOCATION_SIZE;
   }
   
   return offset;
}   

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mpc5125_psc_fifo_slice_free
* Returned Value  : uint_32
* Comments        :
*   free fifo slice data 
*
*END*---------------------------------------------------------------------*/

void _mpc5125_psc_fifo_slice_free(uint_32 psc)
{
   uint_32 i;
   
   for (i=0;i<ELEMENTS_OF(_mpc5125_psc_fifo_slice_map); i++) {
      if (_mpc5125_psc_fifo_slice_map[i] == (psc | 0x80)) {
        _mpc5125_psc_fifo_slice_map[i] = 0;
      }
   }         
}   

/* EOF */

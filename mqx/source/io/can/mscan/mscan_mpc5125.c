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
* $FileName: mscan_mpc5125.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>

uint_32 mscan_vectors[MSCAN_DEVICES] = {MSCAN1_INT_VECTOR,MSCAN2_INT_VECTOR,MSCAN3_INT_VECTOR,MSCAN4_INT_VECTOR};


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_validate_address  
* Returned Value   : TRUE if CAN device address is valid
* Comments         :
*    This function verifies that the MSCAN device address is valid.
*
*END*********************************************************************/


extern MSCAN_TIMING_PARAM_STRUCT bsp_mscan_timing_params[];

int_32 mscan_device_num(uint_32 mscan_ptr)
{ 
   /* MSCAN_ADDRESS_1 and MSCAN_ADDRESS_2 are defined in mscan.h */
   if (mscan_ptr == (uint_32) MSCAN_ADDRESS_1) {
      return MPC5125_MSCAN1;
   } else if (mscan_ptr == (uint_32)MSCAN_ADDRESS_2) {
      return MPC5125_MSCAN2;
   } else if (mscan_ptr == (uint_32)MSCAN_ADDRESS_3) {
      return MPC5125_MSCAN3;
   } else if (mscan_ptr == (uint_32)MSCAN_ADDRESS_4) {
      return MPC5125_MSCAN4;
   } else {
      return IO_ERROR;
   }
} 



mscan_int_mask(dev)
{
   _mpc5125_disable_interrupt(mscan_vectors[dev]);
   return MQX_OK;
}

mscan_int_unmask(dev)
{
   _mpc5125_enable_interrupt(mscan_vectors[dev]);
   return MQX_OK;
}


uint_32  mscan_init_clocks_and_bit_timing(
   VMSCAN_REG_STRUCT_PTR          mscan_reg_ptr,
   uint_32                       mscan_dev,
   uint_32                       bit_rate,
   MSCAN_TIMING_PARAM_STRUCT_PTR in_params_ptr )
{
   MSCAN_TIMING_PARAM_STRUCT_PTR params_ptr=NULL;
   uint_32                       i;
   
   if (bit_rate) {
      for (i=0;bsp_mscan_timing_params[i].BIT_RATE;i++) {
         if (bit_rate == bsp_mscan_timing_params[i].BIT_RATE) {
            params_ptr = &bsp_mscan_timing_params[i];
            break;
         }
      }
   } else if (in_params_ptr) {
      params_ptr = in_params_ptr;
   }
   
   if (params_ptr==NULL) {
      return ERR_MSCAN_INVALID_FREQUENCY;
   }
   
   
   if (params_ptr->CLOCK_SOURCE == MSCAN_CLK_SOURCE_IPB) {
      /* MSCAN clock is IPBUS clock */
       mscan_reg_ptr->CANCTL1 |= 0x40;
   } else {
       mscan_reg_ptr->CANCTL1 &= ~0x40;
   }
   _bsp_enable_can_clock(mscan_dev,bit_rate*1000);

   SET_FIELD_OF_REG(mscan_reg_ptr,MSCAN,CANBTR0,SJW,params_ptr->SJW);
   SET_FIELD_OF_REG(mscan_reg_ptr,MSCAN,CANBTR0,BRP,params_ptr->BRP);
   SET_FIELD_OF_REG(mscan_reg_ptr,MSCAN,CANBTR1,SAMP,params_ptr->SAMP);
   SET_FIELD_OF_REG(mscan_reg_ptr,MSCAN,CANBTR1,TSEG2,params_ptr->TSEG2);
   SET_FIELD_OF_REG(mscan_reg_ptr,MSCAN,CANBTR1,TSEG1,params_ptr->TSEG1);
 
   return MQX_OK;
}
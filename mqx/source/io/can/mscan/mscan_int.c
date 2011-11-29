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
* $FileName: mscan_int.c$
* $Version : 3.6.6.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>

extern uint_32 mscan_vectors[MSCAN_DEVICES] ;

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_int_disable
* Returned Value   : uint_32 
* Comments         : Disable interrupt for both MSCAN modules.
*     
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_int_disable
   (
   /* [IN] MSCAN base address */
   pointer mscan_ptr
   )
{
   int_32   dev= mscan_device_num(mscan_ptr);
   if (dev<0) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   } else {
      if (mscan_int_mask(dev) != MQX_OK) {
         return (ERR_MSCAN_INT_DISABLE_FAILED);
      }
   }
   
   return MSCAN_OK;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_int_enable
* Returned Value   : uint_32 
* Comments         : enable interrupt for both MSCAN modules.
*     
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_int_enable
   (
   /* [IN] MSCAN base address */
   pointer mscan_ptr
   )
{
   int_32   dev= mscan_device_num(mscan_ptr);
   
   if (dev<0) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   } else {
      if (mscan_int_unmask(dev) != MQX_OK) {
         return (ERR_MSCAN_INT_DISABLE_FAILED);
      }
   }
   
   return MSCAN_OK;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_int_init
* Returned Value   : uint_32 
* Comments         : Register interrupt handlers with kernel
*     
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_int_init
   (
   /* [IN] mscan base address */
   pointer mscan_ptr,
   /* [IN] interrupt handler function */
   pointer isr
   )
{
   uint_32   return_code = MSCAN_OK;
   void     (_CODE_PTR_ result)(pointer);   
   int_32   dev= mscan_device_num(mscan_ptr);

   if (dev<0) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   } else {

      /* Install interrupt */
      result = _int_install_isr(mscan_vectors[dev], (void (_CODE_PTR_))isr, mscan_ptr);
      if(result == NULL) {
         return_code = _task_get_error();
      }
   }
   
   return return_code;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_isr
* Returned Value   : uint_32 
* Comments         : MSCAN interrupt handler
*     
*
*END*------------------------------------------------------------------------*/

void mscan_isr
   (
   /* [IN] MSCAN base address */
   pointer mscan_addr
   )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   uchar                        bufBit, tmp;
   vuint_8                  tx_buff;
   uint_8                  mask;
   
 
   /* MSCAN receive interrupt */
   if ((mscan_reg_ptr->CANRFLG & MSCAN_RXF_VALUE) == MSCAN_RXF_VALUE)
   {
      mscan_reg_ptr->CANRFLG |= MSCAN_RXF_VALUE;
      mscan_reg_ptr->CANCTL0 |= MSCAN_CLEAR_RXFRM;
   } 

   // clear transmit interrupts
   for (tx_buff=MSCAN_TX_BUFF1;tx_buff<=MSCAN_TX_BUFF3;tx_buff++) {
      mask = 1<<tx_buff;
      if (mscan_reg_ptr->CANTFLG & mask) {
         if (mscan_reg_ptr->CANTIER & mask) {
            mscan_reg_ptr->CANTIER &= ~mask;
         }
      }
   }

   /* MSCAN Overrun interrupt */
   if ((mscan_reg_ptr->CANRFLG & 0x02) == 0x02)
   {
      mscan_reg_ptr->CANRFLG = 0x03;
   }
    
   /* MSCAN Bus error interrupt */
   if (mscan_reg_ptr->CANRFLG & 0x40) {
       mscan_reg_ptr->CANRFLG |= 0x40;
   }
   
   /* MSCAN Wakeup interrupt */
   if (mscan_reg_ptr->CANRFLG & 0x80)  {
      mscan_reg_ptr->CANRFLG |= 0x80;
   }
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_error_int_enable  
* Returned Value   : uint_32 (Error code) 
* Comments         :
*    This function enables the error interrupt based on direction of the
*    message buffer (Tx or Rx).
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_error_int_enable
   (
   /* [IN] MSCAN base address */
   pointer mscan_addr, 
   /* [IN] Direction of the message (Tx or Rx) */
   uint_32 direction
   )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   } 
   
   if (direction == CAN_TX) {
      /* 
      * Generate error interrup if if transmitter enters or leaves 
      * TxErr or BusOff state
      */
      mscan_reg_ptr->CANRIER |= 0x48;
   } else if(direction == CAN_RX) {
      /* 
      * Generate error interrup if if receiver enters or leaves 
      * RxErr or BusOff state (there is no BusOff state for receiver)
      */
      mscan_reg_ptr->CANRIER |= 0x63;
   } else {
      return (ERR_MSCAN_UNKNOWN_DIRECTION);
   }
   
   return MSCAN_OK;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_wakeup_int_enable
* Returned Value   : uint_32 (Error Code)
* Comments         :
*               This function checks for wakeup mode. If device is in 
*               wakeup operation mode, then enables the wakeup interrupt
*               for the device.
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_wakeup_int_enable
    (
   /* [IN] MSCAN base address */
   pointer mscan_addr
   )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;

   /* Select MSCAN module */
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)){
      return (ERR_MSCAN_INVALID_ADDRESS);
   }

   /* Check for wakeup mode */
   if( (mscan_reg_ptr->CANCTL0 & MSCAN_WAKEUP_MODE) == MSCAN_WAKEUP_MODE) {
      /* Enable wakeup interrupt */
      mscan_reg_ptr->CANRIER |= 0x80;
   } else {
      return (ERR_MSCAN_WAKEUP_MODE_DISABLE);
   }
   return (MSCAN_OK);
}


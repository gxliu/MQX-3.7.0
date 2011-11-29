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
* $FileName: mscan_util.c$
* $Version : 3.6.5.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_validate_address  
* Returned Value   : TRUE if CAN device address is valid
* Comments         :
*    This function verifies that the MSCAN device address is valid.
*
*END*------------------------------------------------------------------------*/


boolean mscan_validate_address(uint_32 mscan_ptr)
{ 
   return ( mscan_device_num(mscan_ptr)!=IO_ERROR);

} 





/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_timestamp_select  
* Returned Value   : uint_32 (Error code) 
* Comments         :
*     
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_timestamp_select
   (
   /* [IN] MSCAN base address */
   pointer mscan_addr, 
   /* [IN] time stamp flag */
   uint_32 flag
   )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   }
   
   if (flag == MSCAN_WITH_TIMESTAMP) {
      mscan_reg_ptr->CANCTL0 |= 0x08;
   } else if(flag == MSCAN_WITHOUT_TIMESTAMP) {
      mscan_reg_ptr->CANCTL0 &= 0xF7;
   } else {
      return (ERR_MSCAN_INVALID_TIMESTAMP);               
   }
   
   return MSCAN_OK;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_rxbuffdep_select  
* Returned Value   : uint_32 (Error code) 
* Comments         :
*     
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_rxbuffdep_select(pointer mscan_addr, uint_32 Depth)
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   } 
   
   switch (Depth) {
      case (MSCAN_RX_NORMAL):
         mscan_reg_ptr->CANRIER |= 0x01;  //Enable Rx interrupt request (Rx buffer full)
          break;
      case  (MSCAN_RX_BUF_DEPTH): 
          mscan_reg_ptr->CANRIER |= 0x02; // Overrun error interrupt enable
          break;
      default:
         return ERR_MSCAN_INVALID_BUFF_DEPTH;
   }
   
   return MSCAN_OK;
}



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_read  
* Returned Value   : uint_32 (Error code) 
* Comments         :
*    This function reads the contents of the specified CAN memory.
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_read(pointer mscan_addr, uint_32 offset, uint_32_ptr data_ptr)
{ 
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   vuint_32                 read_ptr;
   
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   }
   
   read_ptr = (uint_32)mscan_reg_ptr + offset;
   *data_ptr = (uint_32) *(uchar_ptr)read_ptr;
    
   return MSCAN_OK;
} 



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_write  
* Returned Value   : uint_32 (Error code)
* Comments         :
*    This function writes to the specified value to the specified CAN 
*    memory.
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_write(pointer mscan_addr, uint_32 offset, uint_32 value)
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   uint_32                     write_ptr;
   
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   }
   
   write_ptr = (uint_32)mscan_reg_ptr + offset;
   *(uchar_ptr)write_ptr = (uchar)value;
   
   return MSCAN_OK;
} 

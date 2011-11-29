/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access 
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
* $FileName: mcf532x_nfc.c$
* $Version : 3.7.3.0$
* $Date    : Feb-23-2011$
*
* Comments:
*
*   The file contains functions to interface NAND Flash Controller of the
*   MCF532x device.
*
*END************************************************************************/

#include "mqx.h" 
#include "bsp.h"
#include "nandflash.h"
#include "nandflashprv.h"
#include "mcf532x_nfc.h"

uint_32 mcf532x_nfc_swap_addr1, mcf532x_nfc_swap_addr2;

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_nfc_address
* Returned Value   : Address upon success
* Comments         :
*    This function returns the base register address of the NFC
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_nfc_address()
{
   return (pointer)((vuint_8*)NAND_FLASH_ADDRESS); 
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf532x_nfc_init
* Returned Value   : NANDFLASHERR_NO_ERROR or 
*                    NANDFLASHERR_IMPROPER_ECC_SIZE
* Comments         :
*    This function initializes the driver.
*
*END*----------------------------------------------------------------------*/
uint_32 mcf532x_nfc_init
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr
   )
{ /* Body */


   uint_32 result = NANDFLASHERR_NO_ERROR;
   VMCF532X_NFC_STRUCT_PTR  nfc_ptr;
   uint_32 num_ecc_bytes;   
   
   _bsp_nand_flash_io_init(NAND_FLASH_ADDRESS);
   /* Get the pointer to nfc registers structure */
   nfc_ptr = _bsp_get_nfc_address();

   /* Set both addresses in the SWAP register to the same value equal to
      the possition of the bad block marker within the physical page, mapped 
      to the virtual page */
   num_ecc_bytes = NANDFLASH_ECC_SIZE_TO_NUM_BYTES_CONV(nandflash_ptr->ECC_SIZE);
   mcf532x_nfc_swap_addr1 = ((nandflash_ptr->NANDFLASH_INFO_PTR->PHY_PAGE_SIZE)-
                             ((nandflash_ptr->PHY_PAGE_SIZE_TO_VIRTUAL_PAGE_SIZE_RATIO - 1) * 
                             (nandflash_ptr->VIRTUAL_PAGE_SIZE + num_ecc_bytes)))/8;
   mcf532x_nfc_swap_addr2 = (nandflash_ptr->VIRTUAL_PAGE_SIZE)/8;
   
   return(result);
  
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_deinit
* Returned Value   : 
* Comments         : 
*    This function de-initializes the driver. 
* 
*END*----------------------------------------------------------------------*/

void mcf532x_nfc_deinit
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr
   )
{ /* Body */

} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_erase_flash
* Returned Value   : NANDFLASHERR_NO_ERROR or 
*                    NANDFLASHERR_ERASE_FAILED
* Comments         : 
*    This function erases the whole NAND Flash using the NFC of the mcf532x.
* 
*END*----------------------------------------------------------------------*/

uint_32 mcf532x_nfc_erase_flash
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr
   )
{ /* Body */

   uint_32 count;

   for (count = 0; count < (nandflash_ptr->NANDFLASH_INFO_PTR->NUM_BLOCKS); count++)
   {
       if (NANDFLASHERR_NO_ERROR != mcf532x_nfc_erase_block(nandflash_ptr, count, FALSE))
           return NANDFLASHERR_ERASE_FAILED;
   }
   return NANDFLASHERR_NO_ERROR;
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_erase_block
* Returned Value   : NANDFLASHERR_NO_ERROR or 
*                    NANDFLASHERR_ERASE_FAILED or
*                    NANDFLASHERR_TIMEOUT
* Comments         : 
*    This function erases the defined block of NAND Flash 
*    using the NFC of the mcf532x.
* 
*END*----------------------------------------------------------------------*/

uint_32 mcf532x_nfc_erase_block
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr,

      /* [IN] the block to erase */
      uint_32                 block_number,
      
      /* [IN] TRUE = force block erase in case the block is marked as bad */
      boolean                 force_flag
   )
{ /* Body */

   uint_32 result = NANDFLASHERR_TIMEOUT;
   uint_32 count,i;
   uint_32 block_add;
   VMCF532X_NFC_STRUCT_PTR  nfc_ptr;

   /* Do not erase block if force_flag is zero and the block is marked as bad */
   if((!force_flag) &&
      (NANDFLASHERR_BLOCK_NOT_BAD != mcf532x_nfc_check_block(nandflash_ptr, block_number)))
   {
       return NANDFLASHERR_ERASE_FAILED;
   }

   if (nandflash_ptr->WRITE_PROTECT) {
      (*nandflash_ptr->WRITE_PROTECT)(nandflash_ptr, FALSE);
   }/* Endif */
	
   block_add = ((nandflash_ptr->NANDFLASH_INFO_PTR->BLOCK_SIZE /
	                  nandflash_ptr->NANDFLASH_INFO_PTR->PHY_PAGE_SIZE * block_number) & 0xFFFFFF);
	                  
   /* Get the pointer to nfc registers structure */
   nfc_ptr = _bsp_get_nfc_address();
   nfc_ptr->CMD   = NANDFLASH_CMD_BLOCK_ERASE_CYCLE1;
   nfc_ptr->ALE   = (block_add & 0xFF);           /* A9 to A16*/
   nfc_ptr->ALE   = ((block_add >> 0x08) & 0x7F); /* A17 to A23*/
   nfc_ptr->CMD   = NANDFLASH_CMD_BLOCK_ERASE_CYCLE2;
   /* Wait 2ms for block erase successful (Max time 10ms)*/
   _time_delay(2);
   /* Read status */
   nfc_ptr->CMD   = NANDFLASH_CMD_READ_STATUS;
   result         = nfc_ptr->ADD;
   
   if(result & NANDFLASH_STATUS_ERR) {
      result = NANDFLASHERR_ERASE_FAILED;
   }
   else{
      result = NANDFLASHERR_NO_ERROR;
   }

   if (nandflash_ptr->WRITE_PROTECT) {
      (*nandflash_ptr->WRITE_PROTECT)(nandflash_ptr, TRUE);
   }/* Endif */
   return(result);
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_read_page
* Returned Value   : NANDFLASHERR_NO_ERROR or 
*                    NANDFLASHERR_ECC_FAILED or
*                    NANDFLASHERR_ECC_CORRECTED or
*                    NANDFLASHERR_TIMEOUT
* Comments         : 
*    This function reads one or several pages of NAND Flash 
*    using the NFC of the mcf532x.
* 
*END*----------------------------------------------------------------------*/

uint_32 mcf532x_nfc_read_page
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr,

      /* [OUT} where to copy data to */
      uchar_ptr               to_ptr,

      /* [IN] the page to read */
      uint_32                 page_number,

      /* [IN] the amount of pages to read */
      uint_32                 page_count
   )
{ /* Body */
   uint_32 result = NANDFLASHERR_TIMEOUT;
   uint_32 count1, count2;
   uint_32 output_offset = 0;
   boolean ecc_corrected = FALSE, swap = FALSE;
   uint_32 row, num_ecc_bytes;

   VMCF532X_NFC_STRUCT_PTR  nfc_ptr;

   /* Get the pointer to nfc registers structure */
   nfc_ptr = _bsp_get_nfc_address();

   for (count1 = page_number; count1 < (page_number + page_count); count1++)
   {
     row = count1/nandflash_ptr->PHY_PAGE_SIZE_TO_VIRTUAL_PAGE_SIZE_RATIO;
     nfc_ptr->CMD  = NANDFLASH_CMD_PAGE_READ_CYCLE1;
     nfc_ptr->ALE  = (0x00 & 0xFF);
     nfc_ptr->ALE  = (row & 0xFF);
     nfc_ptr->ALE  = ((row << 0x08)& 0xFF);
	  /* Reading time min 20 ns */
	  _time_delay(1);
	  for(count2 = 0; count2 < (nandflash_ptr->VIRTUAL_PAGE_SIZE); count2++){
         *(to_ptr + output_offset) = nfc_ptr->ADD;
			output_offset++;
	  }	   
	  result = NANDFLASHERR_NO_ERROR;
    
   }
   return(result);
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_write_page
* Returned Value   : NANDFLASHERR_NO_ERROR or 
*                    NANDFLASHERR_WRITE_FAILED or
*                    NANDFLASHERR_TIMEOUT
* Comments         : 
*    This function writes one or several pages of NAND Flash 
*    using the NFC of the mcf532x.
* 
*END*----------------------------------------------------------------------*/

uint_32 mcf532x_nfc_write_page
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr,

      /* [IN] where to copy data from */
      uchar_ptr               from_ptr,

      /* [IN] the first page to write */
      uint_32                 page_number,

      /* [IN] the amount of pages to write */
      uint_32                 page_count
   )
{ /* Body */

   uint_32 result = NANDFLASHERR_TIMEOUT;
   uint_32 count1, count2, output_offset = 0;
   uint_32 row, num_ecc_bytes,i;
   uchar read_ptr[600];
   boolean swap = FALSE;

   VMCF532X_NFC_STRUCT_PTR  nfc_ptr;

   if (nandflash_ptr->WRITE_PROTECT) {
      (*nandflash_ptr->WRITE_PROTECT)(nandflash_ptr, FALSE);
   }/* Endif */
   
   /* Get the pointer to nfc registers structure */
   nfc_ptr = _bsp_get_nfc_address();

   for (count1 = page_number; count1 < (page_number + page_count); count1++)
   {
     row = count1/nandflash_ptr->PHY_PAGE_SIZE_TO_VIRTUAL_PAGE_SIZE_RATIO;
     
     nfc_ptr->CMD  = NANDFLASH_CMD_PAGE_PROGRAM_CYCLE1;
     nfc_ptr->ALE  = 0x00;
     nfc_ptr->ALE  = row;
     nfc_ptr->ALE  = ((row << 0x08)& 0xFF);
     
     for ( count2 = 0; count2 < (nandflash_ptr->VIRTUAL_PAGE_SIZE); count2++ )
     {
     	nfc_ptr->ADD = *(from_ptr + count2);  
        
     }
     nfc_ptr->CMD  = NANDFLASH_CMD_PAGE_PROGRAM_CYCLE2;
     /* Programming max time 1ms */
     _time_delay(1);
     from_ptr += nandflash_ptr->VIRTUAL_PAGE_SIZE;
   }
   
   /* Read status */
   nfc_ptr->CMD   = NANDFLASH_CMD_READ_STATUS;
   result         = nfc_ptr->ADD;
   
   if(nfc_ptr->ADD & NANDFLASH_STATUS_ERR) {
      result = NANDFLASHERR_WRITE_FAILED;
   }
   else{
      result = NANDFLASHERR_NO_ERROR;
   }
   
   if (nandflash_ptr->WRITE_PROTECT) {
      (*nandflash_ptr->WRITE_PROTECT)(nandflash_ptr, TRUE);
   }/* Endif */
   return(result);

} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_reset
* Returned Value   : NANDFLASHERR_NO_ERROR or 
*                    NANDFLASHERR_TIMEOUT
* Comments         : 
*    This function resets the NAND Flash using the NFC of the mcf532x.
* 
*END*----------------------------------------------------------------------*/

uint_32 mcf532x_nfc_reset
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr
   )
{ /* Body */

   uint_32 result = NANDFLASHERR_TIMEOUT;
   uint_32 count;
   VMCF532X_NFC_STRUCT_PTR  nfc_ptr;

   /* Get the pointer to nfc registers structure */
   nfc_ptr = _bsp_get_nfc_address();

   nfc_ptr->CMD  = NANDFLASH_CMD_RESET;
   _time_delay(1);
   return(NANDFLASHERR_NO_ERROR);
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_check_block
* Returned Value   : NANDFLASHERR_BLOCK_NOT_BAD or 
*                    NANDFLASHERR_BLOCK_BAD or
*                    NANDFLASHERR_TIMEOUT
* Comments         : 
*    This function checks if the defined NAND Flash block is bad or not 
*    using the NFC of the mcf532x.
* 
*END*----------------------------------------------------------------------*/

uint_32 mcf532x_nfc_check_block
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr,

      /* [IN] block to check */
      uint_32                 block_number
   )
{ /* Body */

   uint_32 result = NANDFLASHERR_TIMEOUT;
   uint_32 count, cfg_bck, col, block_add;

   VMCF532X_NFC_STRUCT_PTR  nfc_ptr;

   /* Get the pointer to nfc registers structure */
   nfc_ptr = _bsp_get_nfc_address();     
   col = nandflash_ptr->NANDFLASH_INFO_PTR->PHY_PAGE_SIZE;   
   block_add = ((nandflash_ptr->NANDFLASH_INFO_PTR->BLOCK_SIZE /
	                  nandflash_ptr->NANDFLASH_INFO_PTR->PHY_PAGE_SIZE * block_number) & 0xFFFFFF);
	                  
   nfc_ptr->CMD = NANDFLASH_CMD_PAGE_READ_CYCLE1;
   nfc_ptr->ALE   = col & 0xFF;
   nfc_ptr->ALE   = (block_add & 0xFF);           /* A9 to A16*/
   nfc_ptr->ALE   = ((block_add >> 0x08) & 0x7F); /* A17 to A23*/
   
   _time_delay(1);
	if(nfc_ptr->ADD == 0x00) {
      result = NANDFLASHERR_BLOCK_BAD;
   }
   else{
      result = NANDFLASHERR_BLOCK_NOT_BAD;
   }
  
   return(result);
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_mark_block_as_bad
* Returned Value   : NANDFLASHERR_NO_ERROR or
*                    NANDFLASHERR_WRITE_FAILED or 
*                    NANDFLASHERR_TIMEOUT
* Comments         : 
*    This function marks the defined NAND Flash block as bad 
*    using the NFC of the mcf532x (writing 0x00 to the first 
*    spare area byte).
* 
*END*----------------------------------------------------------------------*/

uint_32 mcf532x_nfc_mark_block_as_bad
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr,

      /* [IN] block to mark as bad */
      uint_32                 block_number
   )
{ /* Body */

   uint_32 result = NANDFLASHERR_TIMEOUT;
   uint_32 count, cfg_bck, col, block_add;

   VMCF532X_NFC_STRUCT_PTR  nfc_ptr;

   mcf532x_nfc_erase_block(nandflash_ptr, block_number, FALSE);
   
   if (nandflash_ptr->WRITE_PROTECT) {
      (*nandflash_ptr->WRITE_PROTECT)(nandflash_ptr, FALSE);
   }/* Endif */
   
   /* Get the pointer to nfc registers structure */
   nfc_ptr = _bsp_get_nfc_address();

   col = nandflash_ptr->NANDFLASH_INFO_PTR->PHY_PAGE_SIZE;
   block_add = ((nandflash_ptr->NANDFLASH_INFO_PTR->BLOCK_SIZE /
	                 nandflash_ptr->NANDFLASH_INFO_PTR->PHY_PAGE_SIZE * block_number) & 0xFFFFFF);
   
   nfc_ptr->CMD = NANDFLASH_CMD_PAGE_PROGRAM_CYCLE1;
   nfc_ptr->ALE = col & 0xFF;
   nfc_ptr->ALE = (block_add & 0xFF);           /* A9 to A16*/
   nfc_ptr->ALE = ((block_add >> 0x08) & 0x7F); /* A17 to A23*/
   
   nfc_ptr->ADD = 0x00;
   nfc_ptr->CMD = NANDFLASH_CMD_PAGE_PROGRAM_CYCLE2;
   _time_delay(1);
   
   /* Read status */
   nfc_ptr->CMD = NANDFLASH_CMD_READ_STATUS;
      
   if(nfc_ptr->ADD == NANDFLASH_STATUS_ERR){
      result = NANDFLASHERR_WRITE_FAILED;
   }
   else{
      result = NANDFLASHERR_NO_ERROR;
   }

   if (nandflash_ptr->WRITE_PROTECT) {
      (*nandflash_ptr->WRITE_PROTECT)(nandflash_ptr, TRUE);
   }/* Endif */

   return(result);
   
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_read_ID
* Returned Value   : NANDFLASHERR_NO_ERROR or 
*                    NANDFLASHERR_TIMEOUT
* Comments         : 
*    This function reads the ID from the NAND Flash 
*    using the NFC of the mcf532x.
* 
*END*----------------------------------------------------------------------*/

uint_32 mcf532x_nfc_read_ID
   (  
      /* [IN] the NAND flash information */
      IO_NANDFLASH_STRUCT_PTR nandflash_ptr,

      /* [IN] where to store ID */
      uchar_ptr               to_ptr,

      /* [IN] the amount of ID bytes */
      _mem_size               size
   )
{ /* Body */

   uint_32 result = NANDFLASHERR_TIMEOUT;
   uint_32 count1, count2;
   MCF532X_NFC_STRUCT_PTR  nfc_ptr;

   /* Get the pointer to nfc registers structure */
   nfc_ptr = _bsp_get_nfc_address();

   nfc_ptr->CMD   =  NANDFLASH_CMD_READ_ID;
   
   /* Start command execution */
   nfc_ptr->ALE   =  0;
   
   for (count2 = 0; count2 < size; count2++)
   {
      to_ptr[count2] = *(uchar_ptr)((uint_32)&nfc_ptr->ADD);
           
   }
   result = NANDFLASHERR_NO_ERROR;
   
   return result;
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mcf532x_nfc_ioctl
* Returned Value   : TRUE if successful
* Comments         : 
*    mcf532x_nfc ioctl function
* 
*END*----------------------------------------------------------------------*/
_mqx_int mcf532x_nfc_ioctl
   (
      /* [IN] the handle returned from _fopen */
      IO_NANDFLASH_STRUCT_PTR handle_ptr,

      /* [IN] the ioctl command */
      _mqx_uint               cmd,

      /* [IN] the ioctl parameters */
      pointer                 param_ptr
   )
{ /* Body */
	_mqx_uint result = MQX_OK;
	switch(cmd) {
		case NANDFLASH_IOCTL_GET_ID:
			/* Get the NAND Flash ID */
			result = mcf532x_nfc_read_ID(handle_ptr, param_ptr, 2);
			if (result == NANDFLASHERR_NO_ERROR) 
			{
                result = MQX_OK;
			} 
			else 
			{
                result = IO_ERROR;
			}
			break;
		default:
			break;
	}
	return result;
}

/* EOF */

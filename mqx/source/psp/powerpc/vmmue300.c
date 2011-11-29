/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: vmmue300.c$
* $Version : 3.0.2.0$
* $Date    : Aug-19-2008$
*
* Comments:
*
*   This file contains MMU functions for use with any E300 core.
*
*END************************************************************************/

#include "mqx_inc.h"

/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_vinit
* Returned Value   : mqx error code
* Comments         :             
*
*END*-------------------------------------------------------------------------*/

_mqx_uint _mmu_vinit
   (
      /* [IN] initialization flags */
      _mqx_uint flags,

      /* [IN] initialization info */
      pointer   input_init_ptr
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR   kernel_data;
   PSP_SUPPORT_STRUCT_PTR   psp_support_ptr;
   PSP_PAGE_INFO_STRUCT_PTR mem_ptr;
   PSP_MMU_VINIT_STRUCT_PTR init_ptr = input_init_ptr;
   uchar_ptr                addr;
   uint_32                  htabmask;
   uint_32                  htaborg; 
   uint_32                  vpage_num;
   boolean                  error = FALSE;
   uint_32                  temp = 0; 
   uint_32                  sdr1;
   _mqx_uint                i;

   _mmu_init(0);

   _GET_KERNEL_DATA(kernel_data);
   psp_support_ptr = kernel_data->PSP_SUPPORT_PTR;
#if MQX_CHECK_ERRORS
   if (psp_support_ptr == NULL) {
      return(MQX_COMPONENT_DOES_NOT_EXIST);
   } /* Endif */
#endif
   
   _int_disable();
   if (_lwsem_wait(&psp_support_ptr->MMU_LWSEM) == MQX_OK) {
      /* Already initialized! */
      _lwsem_post(&psp_support_ptr->MMU_LWSEM);
      _int_enable();
      return(MQX_COMPONENT_EXISTS);
   }/* Endif */
   _lwsem_create(&psp_support_ptr->VPAGE_FREELIST_LWSEM,0);
   _lwsem_create(&psp_support_ptr->MMU_LWSEM,0);
   _int_enable();

   /* Initialize the MMU page table support */ 
   if ((uint_32)init_ptr->MMU_PAGE_TABLE_BASE & E300CORE_MMU_PAGE_TABLE_SIZE) {
      /* Address is misaligned */
      error = TRUE;
   }/* Endif */
   if (init_ptr->UNMAPPED_MEMORY_SIZE) {
      if ((uint_32)init_ptr->UNMAPPED_MEMORY_BASE & (E300CORE_MMU_PAGE_SIZE-1)) {
         /* Address is misaligned */
         error = TRUE;
      }/* Endif */
      vpage_num = init_ptr->UNMAPPED_MEMORY_SIZE / E300CORE_MMU_PAGE_SIZE;
      if (!vpage_num) {
         error = TRUE;
      }/* Endif */
   } /* Endif */
   
   if (error) {
      _lwsem_destroy(&psp_support_ptr->VPAGE_FREELIST_LWSEM);
      _lwsem_destroy(&psp_support_ptr->MMU_LWSEM);
      return(MQX_INVALID_PARAMETER);
   }/* Endif */

   addr = init_ptr->MMU_PAGE_TABLE_BASE;
   psp_support_ptr->MMU_PAGE_TABLE_BASE  = (pointer)addr;
   psp_support_ptr->PAGE_SIZE = E300CORE_MMU_PAGE_SIZE;
   /* Initialize the Free pages queue */      
   _queue_init((pointer)&psp_support_ptr->VPAGE_FREELIST, 0);

   if (init_ptr->UNMAPPED_MEMORY_SIZE) {
      mem_ptr = _mem_alloc_system(vpage_num * sizeof(PSP_PAGE_INFO_STRUCT));
      if (mem_ptr == NULL) {
         _lwsem_destroy(&psp_support_ptr->VPAGE_FREELIST_LWSEM);
         _lwsem_destroy(&psp_support_ptr->MMU_LWSEM);
         return(MQX_OUT_OF_MEMORY);
      }/* Endif */
      psp_support_ptr->MMU_PAGE_INFO_BASE = mem_ptr;
      addr = init_ptr->UNMAPPED_MEMORY_BASE;
      _mem_zero(addr,init_ptr->UNMAPPED_MEMORY_SIZE);
      /* Load the free pages into the queue */
      for (i = 0; i < vpage_num; ++i) {
         mem_ptr->ADDR = addr;
         _queue_enqueue(&psp_support_ptr->VPAGE_FREELIST, &mem_ptr->ELEMENT);
         mem_ptr++;
         addr += E300CORE_MMU_PAGE_SIZE;
      } /* Endfor */
   }/* Endif */
   
   /* Set up table */
   _mem_zero(psp_support_ptr->MMU_PAGE_TABLE_BASE, 
      init_ptr->MMU_PAGE_TABLE_SIZE);
   /* Get the number of PTEG's */
   htabmask = (init_ptr->MMU_PAGE_TABLE_SIZE)/ 64;
   
   /* Get the additional bits */
   htabmask = (((htabmask >> 10) - 1) & 0x1FF);
   
   /* Get HTABORG */
   htaborg = (uint_32)init_ptr->MMU_PAGE_TABLE_BASE;
   htaborg &= E300CORE_SDR1_HTABORG_MASK;
   
   /* Set the SDR1 register */
   sdr1 = (htaborg | htabmask);
   _PSP_SPR_SET(E300CORE_SDR1, sdr1);
   
   /* Init the segment register */
   temp = E300CORE_SR_Ks_BIT | E300CORE_SR_Kp_BIT;
   for(i = 0; i < 16; i++){
      _PSP_SET_SEGREG_IN(temp+i,i*0x10000000);
   } /* Endfor */

   _lwsem_post(&psp_support_ptr->VPAGE_FREELIST_LWSEM);
   _lwsem_post(&psp_support_ptr->MMU_LWSEM);

   return(MQX_OK);
} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_venable
* Returned Value   : void
* Comments         :
*
*END*-------------------------------------------------------------------------*/

void _mmu_venable
   (
      void 
   )
{ /* Body */

   _mmu_enable();

} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_vdisable
* Returned Value   : void
* Comments         :
*
*END*-------------------------------------------------------------------------*/

void _mmu_vdisable
   (
      void 
   )
{ /* Body */

   _mmu_disable();

} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _vmmu_get_pteg_addr_internal
* Returned Value   : mqx error code 
* Comments         :
*
*END*-------------------------------------------------------------------------*/

PSP_PTE_STRUCT_PTR _vmmu_get_pteg_addr_internal
   (
      /* [IN] input hash key */
      uint_32  hashkey 
   )
{ /* Body */
   uint_32 sdr1;
   uint_32 pteg_addr;
   
   /* Get SDR1 register */
   _PSP_SPR_GET(sdr1, E300CORE_SDR1);
   
   pteg_addr = (sdr1 & E300CORE_SDR1_HTABORG_MASK) | ((hashkey & 0x3ff) << 6)
      | (((sdr1 & E300CORE_SDR1_HTABMASK_MASK) & (hashkey >> 10)) << 16);

   return((PSP_PTE_STRUCT_PTR)pteg_addr);
   
} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _vmmu_find_pte_internal
* Returned Value   : none
* Comments         :
*          Finds a PTE given a virtual address
*END*-------------------------------------------------------------------------*/

PSP_PTE_STRUCT_PTR _vmmu_find_pte_internal
   (
      /* [IN] the virtual address in question */
      pointer vaddr
   )
{/* Body */
   PSP_PTE_STRUCT_PTR pteg_ptr;
   uint_32            vsid;
   uint_32            hashkey;
   uint_32            upper_pte;
   _mqx_int           i;
 
   /* Calculate the hash value */
   vsid    = E300CORE_GET_VADDR_VSID((uint_32)vaddr);
   hashkey = vsid ^ E300CORE_GET_VADDR_PAGE_INDEX((uint_32)vaddr);
   upper_pte = E300CORE_PTE_VALID_MASK | (vsid << 7) | 
      E300CORE_GET_VADDR_API((uint_32)vaddr);
   
   /* Search PTE in primary group*/
   pteg_ptr = _vmmu_get_pteg_addr_internal(hashkey);
   i     = 9;
   while(--i) {
      if (pteg_ptr->UPPER_PTE == upper_pte) {
         return(pteg_ptr);
      } /*Endif*/
      pteg_ptr++;
   } /*Endwhile*/

   /* Search PTE in secondary group*/
   pteg_ptr = _vmmu_get_pteg_addr_internal(~hashkey);
   upper_pte |= E300CORE_PTE_H_MASK;
   i = 9;
   while(--i) {
      if (pteg_ptr->UPPER_PTE == upper_pte) {
         return(pteg_ptr);
      } /*Endif*/
      pteg_ptr++;
   } /*Endwhile*/

   return(NULL);

}/* Endbody */
   

/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _vmmu_add_pte_internal
* Returned Value   : none
* Comments         :
*
*END*-------------------------------------------------------------------------*/

boolean _vmmu_add_pte_internal
   (
      /* [IN] the pte to use */
      PSP_PTE_STRUCT_PTR pte_ptr,

      /* [IN] the hashkey to use */
      uint_32            hashkey  
   )
{ /* Body */
   PSP_PTE_STRUCT_PTR pteg_ptr;
   _mqx_uint          i = 9;
   
   pteg_ptr = _vmmu_get_pteg_addr_internal(hashkey);
   while (--i) {
      if (((pteg_ptr->UPPER_PTE) & E300CORE_PTE_VALID_MASK)== 0){
         pteg_ptr->LOWER_PTE = pte_ptr->LOWER_PTE;
         pteg_ptr->UPPER_PTE = pte_ptr->UPPER_PTE;
         _PSP_FLUSH_LINE(&pteg_ptr->UPPER_PTE);
         return(TRUE);
      }/*Endif*/
      pteg_ptr++;
   } /* Endwhile */
   
   return(FALSE);
   
} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_add_vregion
* Returned Value   : mqx error code
* Comments         :
*
*END*-------------------------------------------------------------------------*/

_mqx_uint _mmu_add_vregion
   (
      /* [IN] the starting location of the memory block */
      pointer   mem_ptr, 

      /* [IN] the starting location of the virtual memory block */
      pointer   vaddr, 

      /* [IN] the size of the memory block */
      _mem_size input_size, 

      /* [IN] flags indicating what type of memory this is */
      _mqx_uint flags
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR   kernel_data;
   PSP_SUPPORT_STRUCT_PTR   psp_support_ptr;
   PSP_PTE_STRUCT           pte;
   int_32                   size = (int_32)input_size;
   uint_32                  vsid;
   uint_32                  hashkey;
   
   _GET_KERNEL_DATA(kernel_data);
   psp_support_ptr = kernel_data->PSP_SUPPORT_PTR;
#if MQX_CHECK_ERRORS
   if (psp_support_ptr == NULL) {
      return(MQX_COMPONENT_DOES_NOT_EXIST);
   } /* Endif */
#endif

   if (_lwsem_wait(&psp_support_ptr->MMU_LWSEM) != MQX_OK) {
      return(MQX_COMPONENT_DOES_NOT_EXIST);
   }/* Endif */
   
   while (size > (E300CORE_MMU_PAGE_SIZE-1)) {
      /* Construct the page table entry */

      /* Calculate the hash value */
      vsid = E300CORE_GET_VADDR_VSID((uint_32)vaddr);
      hashkey = vsid ^ E300CORE_GET_VADDR_PAGE_INDEX((uint_32)vaddr);

      /* Set the upper 32 bits */
      pte.UPPER_PTE = E300CORE_PTE_VALID_MASK | (vsid << 7) | 
         E300CORE_GET_VADDR_API((uint_32)vaddr);
         
      /* Set the lower 32 bits */
      pte.LOWER_PTE = (uint_32)mem_ptr & E300CORE_PTE_RPN_MASK;

      /* Set the flags */
      if ( flags & PSP_MMU_CACHE_INHIBITED) {
         pte.LOWER_PTE |= E300CORE_PTE_CACHE_INHIBIT;
      } /* Endif */
   
      if ( flags & PSP_MMU_WRITE_THROUGH) {
         pte.LOWER_PTE |= E300CORE_PTE_CACHE_WRITE_THRU;
      } /* Endif */
   
      if ( flags & PSP_MMU_GUARDED) {
         pte.LOWER_PTE |= E300CORE_PTE_CACHE_GUARDED;
      } /* Endif */
   
      if ( flags & PSP_MMU_COHERENT) {
         pte.LOWER_PTE |= E300CORE_PTE_CACHE_COHERENT;
      } /* Endif */
   
      if ( flags & PSP_MMU_WRITE_PROTECTED) {
         pte.LOWER_PTE |= E300CORE_PTE_READ_ONLY;
      } else {
         pte.LOWER_PTE |= E300CORE_PTE_READ_WRITE;
      } /* Endif */
         
      if (!_vmmu_add_pte_internal(&pte, hashkey)) {
         /* Go to secondary hash key */
         pte.UPPER_PTE |= E300CORE_PTE_H_MASK;
         if (!_vmmu_add_pte_internal(&pte, ~hashkey)) {
            _lwsem_post(&psp_support_ptr->MMU_LWSEM);
            return(MQX_OUT_OF_MEMORY);
         }/*Endif*/
      }/* Endif */
      _PSP_TLBIE(vaddr);
      _PSP_SYNC();
      mem_ptr = (pointer)((uint_32)mem_ptr + E300CORE_MMU_PAGE_SIZE);
      vaddr   = (pointer)((uint_32)vaddr + E300CORE_MMU_PAGE_SIZE);
      size    -= E300CORE_MMU_PAGE_SIZE;
   } /* Endwhile */
                            
   _lwsem_post(&psp_support_ptr->MMU_LWSEM);
   return(MQX_OK);

} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_get_vpage_size
* Returned Value   : page size
* Comments         :
*
*END*-------------------------------------------------------------------------*/

_mem_size _mmu_get_vpage_size
   (
      void 
   )
{ /* Body */

   return(E300CORE_MMU_PAGE_SIZE);

} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_get_vmem_attributes
* Returned Value   : mqx error code
* Comments         :
*
*END*-------------------------------------------------------------------------*/

_mqx_uint _mmu_get_vmem_attributes
   (
      /* [IN] virtual address in question */
      pointer       vaddr,
      
      /* [OUT] virtual address of page base */
      pointer _PTR_ page_base,
      
      /* [OUT] physical address of page base */
      pointer _PTR_ physical_page_base,
      
      /* [OUT] this pages size */
      _mem_size_ptr page_size,
      
      /* [OUT] this pages flags */
      _mqx_uint_ptr page_flags
      
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR kernel_data;
   PSP_SUPPORT_STRUCT_PTR psp_support_ptr;
   PSP_PTE_STRUCT_PTR     pte_ptr;
   uint_32                flags;
   
   _GET_KERNEL_DATA(kernel_data);

   psp_support_ptr = kernel_data->PSP_SUPPORT_PTR;
#if MQX_CHECK_ERRORS
   if (psp_support_ptr == NULL) {
      return(MQX_COMPONENT_DOES_NOT_EXIST);
   } /* Endif */
#endif
   
   /* Get the page size */
   *page_size = psp_support_ptr->PAGE_SIZE;

   /* Get the virtual page base */
   *page_base = (pointer)((uint_32)vaddr & ~(psp_support_ptr->PAGE_SIZE - 1));

   /* Get page table entry group */
   pte_ptr = _vmmu_find_pte_internal(vaddr);
   if (pte_ptr == NULL) {
      return(MQX_INVALID_PARAMETER);
   } /* Endif */
   
   *physical_page_base = (pointer)(pte_ptr->LOWER_PTE & E300CORE_PTE_RPN_MASK);

   flags = 0;
   /* Get the flags */
   if (pte_ptr->LOWER_PTE & E300CORE_PTE_CACHE_INHIBIT) {
      flags |= PSP_MMU_CACHE_INHIBITED;
   } /* Endif */

   if (pte_ptr->LOWER_PTE & E300CORE_PTE_CACHE_WRITE_THRU) {
      flags |= PSP_MMU_WRITE_THROUGH;
   } /* Endif */

   if (pte_ptr->LOWER_PTE & E300CORE_PTE_CACHE_GUARDED) {
      flags |= PSP_MMU_GUARDED;
   } /* Endif */

   if (pte_ptr->LOWER_PTE  & E300CORE_PTE_CACHE_COHERENT) {
      flags |= PSP_MMU_COHERENT;
   } /* Endif */

   if ((pte_ptr->LOWER_PTE & E300CORE_PTE_READ_ONLY) == 
      (E300CORE_PTE_READ_ONLY))
   {
      flags |= PSP_MMU_WRITE_PROTECTED;
   } /* Endif */ 
     
   *page_flags = flags;

   return(MQX_OK);

} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_set_vmem_attributes
* Returned Value   : mqx error code
* Comments         :
*
*END*-------------------------------------------------------------------------*/

_mqx_uint _mmu_set_vmem_attributes
   (
      /* [IN] virtual address in question */
      pointer   vaddr,
      
      /* [IN] new pages flags */
      _mqx_uint page_flags,
      
      /* [IN] the amount of memory to be covered */
      _mem_size input_size
      
   )
{ /* Body */
   PSP_PTE_STRUCT_PTR pte_ptr;
   int_32             size = (int_32)input_size;
   uint_32            flags;
   
   while (size > (E300CORE_MMU_PAGE_SIZE-1)) {

      /* Find the PTE in question */
      pte_ptr = _vmmu_find_pte_internal(vaddr);
      if (pte_ptr == NULL) {
         return(MQX_INVALID_PARAMETER);
      } /* Endif */
      
      flags = pte_ptr->LOWER_PTE;

      /* Set the flags */
      if (page_flags & PSP_MMU_CACHE_INHIBITED) {
         flags |= E300CORE_PTE_CACHE_INHIBIT;
      } else {
         flags &= ~E300CORE_PTE_CACHE_INHIBIT;
      } /* Endif */
   
      if (page_flags & PSP_MMU_WRITE_THROUGH) {
         flags |= E300CORE_PTE_CACHE_WRITE_THRU;
      } else {
         flags &= ~E300CORE_PTE_CACHE_WRITE_THRU;
      } /* Endif */
   
      if (page_flags & PSP_MMU_GUARDED) {
         flags |= E300CORE_PTE_CACHE_GUARDED;
      } else {
         flags &= ~E300CORE_PTE_CACHE_GUARDED;
      } /* Endif */
   
      if (page_flags & PSP_MMU_COHERENT) {
         flags |= E300CORE_PTE_CACHE_COHERENT;
      } else {
         flags &= ~E300CORE_PTE_CACHE_COHERENT;
      } /* Endif */
   
      flags &= ~3; /* Remove page protection bits */
      if (page_flags & PSP_MMU_WRITE_PROTECTED) {
         flags |= E300CORE_PTE_READ_ONLY;
      } else {
         flags |= E300CORE_PTE_READ_WRITE;
      } /* Endif */

      pte_ptr->UPPER_PTE &= ~E300CORE_PTE_VALID_MASK;
      _PSP_SYNC();
      _PSP_TLBIE(vaddr);
      _PSP_SYNC();
      _PSP_TLBSYNC();
      _PSP_SYNC();
      pte_ptr->LOWER_PTE = flags;
      _PSP_SYNC();
      pte_ptr->UPPER_PTE |= E300CORE_PTE_VALID_MASK;
      _PSP_FLUSH_LINE(pte_ptr);

      vaddr  = (pointer)((uint_32)vaddr + E300CORE_MMU_PAGE_SIZE);
      size  -= E300CORE_MMU_PAGE_SIZE;
   } /* Endwhile */

   return(MQX_OK);

} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_vtop
* Returned Value   : mqx error code
* Comments         :
*
*END*-------------------------------------------------------------------------*/

_mqx_uint _mmu_vtop
   (
      /* [IN] virtual address in question */
      pointer       vaddr,
      
      /* [OUT] the physical address */
      pointer _PTR_ paddr
   )
{ /* Body */
   PSP_PTE_STRUCT_PTR pteg_ptr;

   pteg_ptr = _vmmu_find_pte_internal(vaddr);
   if (pteg_ptr == NULL) {
      return(MQX_INVALID_PARAMETER);
   } /* Endif */

   /* Get the physical address */
   *paddr = (pointer)(E300CORE_GET_PTE_RPN(pteg_ptr->LOWER_PTE)| 
      ((uint_32)vaddr & 0xFFF));

   return(MQX_OK);

} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_set_vmem_loc_internal
* Returned Value   : mqx error code
* Comments         :
*
*END*-------------------------------------------------------------------------*/

_mqx_uint _mmu_set_vmem_loc_internal
   (
      /* [IN] virtual address memory descriptor */
      PSP_PAGE_INFO_STRUCT_PTR  page_info_ptr,
      
      /* [IN] new pages flags */
      _mqx_uint                 flags
   )
{ /* Body */
   PSP_PTE_STRUCT_PTR pte_ptr;
   PSP_PTE_STRUCT_PTR pteg_ptr;
   uint_32            vsid;
   uint_32            hashkey;
   _mqx_int           i;
   
   /*Create PTE */
   pte_ptr = &page_info_ptr->PTE;
   
   /* Calculate the hash value */
   vsid = E300CORE_GET_VADDR_VSID((uint_32)page_info_ptr->VADDR);
   hashkey = vsid ^ E300CORE_GET_VADDR_PAGE_INDEX((uint_32)page_info_ptr->VADDR);

   /* Set the upper 32 bits */
   pte_ptr->UPPER_PTE = E300CORE_PTE_VALID_MASK | (vsid << 7) | 
      E300CORE_GET_VADDR_API((uint_32)page_info_ptr->VADDR);
      
   /* Set the lower 32 bits */
   pte_ptr->LOWER_PTE = (uint_32)page_info_ptr->ADDR & E300CORE_PTE_RPN_MASK;

   /* Set the flags */
   if ( flags & PSP_MMU_CACHE_INHIBITED) {
      pte_ptr->LOWER_PTE |= E300CORE_PTE_CACHE_INHIBIT;
   } /* Endif */

   if ( flags & PSP_MMU_WRITE_THROUGH) {
      pte_ptr->LOWER_PTE |= E300CORE_PTE_CACHE_WRITE_THRU;
   } /* Endif */

   if ( flags & PSP_MMU_GUARDED) {
      pte_ptr->LOWER_PTE |= E300CORE_PTE_CACHE_GUARDED;
   } /* Endif */

   if ( flags & PSP_MMU_COHERENT) {
      pte_ptr->LOWER_PTE |= E300CORE_PTE_CACHE_COHERENT;
   } /* Endif */

   if ( flags & PSP_MMU_WRITE_PROTECTED) {
      pte_ptr->LOWER_PTE |= E300CORE_PTE_READ_ONLY;
   } else {
      pte_ptr->LOWER_PTE |= E300CORE_PTE_READ_WRITE;
   } /* Endif */

   /* Find where to insert into the PTE table */
   pteg_ptr = _vmmu_get_pteg_addr_internal(hashkey);
   i = 9;
   while (--i) {
      if (((pteg_ptr->UPPER_PTE) & E300CORE_PTE_VALID_MASK)== 0){
         page_info_ptr->PTE_PTR = pteg_ptr;
         return(MQX_OK);
      } /*Endif*/
      pteg_ptr++;
   } /*Endwhile*/

   pte_ptr->UPPER_PTE |= E300CORE_PTE_H_MASK;
   pteg_ptr = _vmmu_get_pteg_addr_internal(~hashkey);
   i = 9;
   while (--i) {
      if (((pteg_ptr->UPPER_PTE) & E300CORE_PTE_VALID_MASK)== 0){
         page_info_ptr->PTE_PTR = pteg_ptr;
         return(MQX_OK);
      } /*Endif*/
      pteg_ptr++;
   } /*Endwhile*/

   /* Entry not valid */
   return(MQX_INVALID_PARAMETER);

} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_reset_vcontext_internal
* Returned Value   : void
* Comments         :
*   *** MUST BE CALLED WITH INTERRUPTS DISABLED ***
*
*END*-------------------------------------------------------------------------*/

void _mmu_reset_vcontext_internal
   (
      void
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR         kernel_data;
   TD_STRUCT_PTR                  td_ptr;
   PSP_VIRTUAL_CONTEXT_STRUCT_PTR context_ptr;
   PSP_PAGE_INFO_STRUCT_PTR       page_info_ptr;
   uint_32                        i;
     
   _GET_KERNEL_DATA(kernel_data);
   td_ptr      = kernel_data->ACTIVE_PTR;
   context_ptr = td_ptr->MMU_VIRTUAL_CONTEXT_PTR;
   i = _QUEUE_GET_SIZE(&context_ptr->PAGE_INFO) + 1;
   page_info_ptr = (pointer)context_ptr->PAGE_INFO.NEXT;
   while (--i) {
      page_info_ptr->PTE_PTR->UPPER_PTE = 0;
      _PSP_SYNC();
      _PSP_FLUSH_LINE(&page_info_ptr->PTE_PTR->UPPER_PTE);
      _PSP_TLBIE(page_info_ptr->VADDR);
      _PSP_IO_EIEIO();
      _PSP_TLBSYNC();
      _PSP_SYNC();
      page_info_ptr = (pointer)page_info_ptr->ELEMENT.NEXT;
   } /* Endwhile */
   
} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _mmu_set_vcontext_internal
* Returned Value   : void
* Comments         :
*   *** MUST BE CALLED WITH INTERRUPTS DISABLED ***
*
*END*-------------------------------------------------------------------------*/

void _mmu_set_vcontext_internal
   (
      void
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR         kernel_data;
   TD_STRUCT_PTR                  td_ptr;
   PSP_VIRTUAL_CONTEXT_STRUCT_PTR context_ptr;
   PSP_PAGE_INFO_STRUCT_PTR       page_info_ptr;
   uint_32                        i;
   
   _GET_KERNEL_DATA(kernel_data);
   td_ptr      = kernel_data->ACTIVE_PTR;
   context_ptr = td_ptr->MMU_VIRTUAL_CONTEXT_PTR;
   i = _QUEUE_GET_SIZE(&context_ptr->PAGE_INFO) + 1;
   page_info_ptr = (pointer)context_ptr->PAGE_INFO.NEXT;
   while (--i) {
      page_info_ptr->PTE_PTR->LOWER_PTE = page_info_ptr->PTE.LOWER_PTE;
      _PSP_IO_EIEIO();
      page_info_ptr->PTE_PTR->UPPER_PTE = page_info_ptr->PTE.UPPER_PTE;   
      _PSP_SYNC();
      _PSP_FLUSH_LINE(&page_info_ptr->PTE_PTR->UPPER_PTE);
      page_info_ptr = (pointer)page_info_ptr->ELEMENT.NEXT;
   } /* Endwhile */
   _PSP_SYNC();
   
} /* Endbody */

/* EOF */

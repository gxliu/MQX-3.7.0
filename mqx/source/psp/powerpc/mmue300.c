/*HEADER******************************************************************
**************************************************************************
*** 
*** Copyright (c) 1989-2005 ARC International
*** All rights reserved                                          
***                                                              
*** This software embodies materials and concepts which are      
*** confidential to ARC International and is made
*** available solely pursuant to the terms of a written license   
*** agreement with ARC International             
***
*** File: mmue300.c
***
*** Comments:      
***   This file contains MMU utiltity functions for use with the 
***   PowerPC E300 CORE
***                                                               
***
**************************************************************************
*END*********************************************************************/

#include "mqx_inc.h"

#undef  _NELEM
#define _NELEM(ary) (sizeof(ary) / sizeof(ary[0]))

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mmu_init
* Returned Value  : void
* Comments        :
*   Initialize the mmu
*
*END*---------------------------------------------------------------------*/

void _mmu_init
   (
      /* [IN] dummy value */
      pointer dummy
   )
{ /* Body */

   _mmu_disable();
   _PSP_CLEAR_TLB_ENTRIES();
   _PSP_CLEAR_ALL_SRS();

   // TLB Exception handlers should be installed by linker command
   // file using sections defined in dispatch.s

} /* Endbody */


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mmu_enable
* Returned Value  : void
* Comments        :
*   Enable the operation of the mmu
*
*END*---------------------------------------------------------------------*/

void _mmu_enable
   (
      void
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR kernel_data;
   PSP_SUPPORT_STRUCT_PTR psp_support_ptr;
   uint_32        msr_enable = 0;
   uint_32        val;

   _GET_KERNEL_DATA(kernel_data);
   psp_support_ptr = kernel_data->PSP_SUPPORT_PTR;

   if (psp_support_ptr == NULL) {
      return;
   } /* Endif */

   /*
   ** If virtual page tables are used OR any BAT registers used
   ** then we must enable the MMU.
   */
   val = psp_support_ptr->PAGE_SIZE
      |  psp_support_ptr->IBAT_COUNT | psp_support_ptr->DBAT_COUNT;
   if (val == 0) {
      /* No memory regions specified */
      return;
   } /* Endif */

   /* Initialize instruction BAT registers */
   if (psp_support_ptr->IBAT_COUNT) {
      _PSP_SPR_SET(E300CORE_IBATU0, psp_support_ptr->IBAT_TABLE[0].attr_hi);
      _PSP_SPR_SET(E300CORE_IBATL0, psp_support_ptr->IBAT_TABLE[0].attr_lo);
      _PSP_SPR_SET(E300CORE_IBATU1, psp_support_ptr->IBAT_TABLE[1].attr_hi);
      _PSP_SPR_SET(E300CORE_IBATL1, psp_support_ptr->IBAT_TABLE[1].attr_lo);
      _PSP_SPR_SET(E300CORE_IBATU2, psp_support_ptr->IBAT_TABLE[2].attr_hi);
      _PSP_SPR_SET(E300CORE_IBATL2, psp_support_ptr->IBAT_TABLE[2].attr_lo);
      _PSP_SPR_SET(E300CORE_IBATU3, psp_support_ptr->IBAT_TABLE[3].attr_hi);
      _PSP_SPR_SET(E300CORE_IBATL3, psp_support_ptr->IBAT_TABLE[3].attr_lo);
      _PSP_SPR_SET(E300CORE_IBATU4, psp_support_ptr->IBAT_TABLE[4].attr_hi);
      _PSP_SPR_SET(E300CORE_IBATL4, psp_support_ptr->IBAT_TABLE[4].attr_lo);
      _PSP_SPR_SET(E300CORE_IBATU5, psp_support_ptr->IBAT_TABLE[5].attr_hi);
      _PSP_SPR_SET(E300CORE_IBATL5, psp_support_ptr->IBAT_TABLE[5].attr_lo);
      _PSP_SPR_SET(E300CORE_IBATU6, psp_support_ptr->IBAT_TABLE[6].attr_hi);
      _PSP_SPR_SET(E300CORE_IBATL6, psp_support_ptr->IBAT_TABLE[6].attr_lo);
      _PSP_SPR_SET(E300CORE_IBATU6, psp_support_ptr->IBAT_TABLE[6].attr_hi);
      _PSP_SPR_SET(E300CORE_IBATL6, psp_support_ptr->IBAT_TABLE[6].attr_lo);
      _PSP_SPR_SET(E300CORE_IBATU7, psp_support_ptr->IBAT_TABLE[7].attr_hi);
      _PSP_SPR_SET(E300CORE_IBATL7, psp_support_ptr->IBAT_TABLE[7].attr_lo);

      msr_enable |= PSP_MSR_IR;
   } /* Endif */

   /* Initialize data BAT registers */
   if (psp_support_ptr->DBAT_COUNT) {
      _PSP_SPR_SET(E300CORE_DBATU0, psp_support_ptr->DBAT_TABLE[0].attr_hi);
      _PSP_SPR_SET(E300CORE_DBATL0, psp_support_ptr->DBAT_TABLE[0].attr_lo);
      _PSP_SPR_SET(E300CORE_DBATU1, psp_support_ptr->DBAT_TABLE[1].attr_hi);
      _PSP_SPR_SET(E300CORE_DBATL1, psp_support_ptr->DBAT_TABLE[1].attr_lo);
      _PSP_SPR_SET(E300CORE_DBATU2, psp_support_ptr->DBAT_TABLE[2].attr_hi);
      _PSP_SPR_SET(E300CORE_DBATL2, psp_support_ptr->DBAT_TABLE[2].attr_lo);
      _PSP_SPR_SET(E300CORE_DBATU3, psp_support_ptr->DBAT_TABLE[3].attr_hi);
      _PSP_SPR_SET(E300CORE_DBATL3, psp_support_ptr->DBAT_TABLE[3].attr_lo);
      _PSP_SPR_SET(E300CORE_DBATU4, psp_support_ptr->DBAT_TABLE[4].attr_hi);
      _PSP_SPR_SET(E300CORE_DBATL4, psp_support_ptr->DBAT_TABLE[4].attr_lo);
      _PSP_SPR_SET(E300CORE_DBATU5, psp_support_ptr->DBAT_TABLE[5].attr_hi);
      _PSP_SPR_SET(E300CORE_DBATL5, psp_support_ptr->DBAT_TABLE[5].attr_lo);
      _PSP_SPR_SET(E300CORE_DBATU6, psp_support_ptr->DBAT_TABLE[6].attr_hi);
      _PSP_SPR_SET(E300CORE_DBATL6, psp_support_ptr->DBAT_TABLE[6].attr_lo);
      _PSP_SPR_SET(E300CORE_DBATU7, psp_support_ptr->DBAT_TABLE[7].attr_hi);
      _PSP_SPR_SET(E300CORE_DBATL7, psp_support_ptr->DBAT_TABLE[7].attr_lo);
      msr_enable |= PSP_MSR_DR;
   } /* Endif */

   /* Finish all data writes */
   _PSP_ISYNC();
   _PSP_SYNC();

   /* Disable & unlock I/D cache */
   _PSP_SPR_GET(val, E300CORE_HID0);
   val &= ~(0xFC00);
   _PSP_SPR_SET(E300CORE_HID0, val);
   _PSP_ISYNC();
   _PSP_SYNC();

   /* Flush, unlock and invalidate the instruction cache */
   _PSP_SPR_GET(val, E300CORE_HID0);
   _PSP_SPR_SET(E300CORE_HID0, val | 0x800);
   _PSP_SPR_SET(E300CORE_HID0, val);
   _PSP_ISYNC();
   _PSP_SYNC();

   /* Flush, unlock and invalidate the data cache */
   _PSP_SPR_SET(E300CORE_HID0, val | 0x400);
   _PSP_SPR_SET(E300CORE_HID0, val);
   _PSP_ISYNC();
   _PSP_SYNC();

   /* Enable the MMU */
   val = _PSP_GET_SR();
   val &= ~(PSP_MSR_IR | PSP_MSR_DR);
   val |= msr_enable;
   _PSP_SET_SR(val);

   /* Changes to MSR take effect */
   _PSP_ISYNC();
   _PSP_SYNC();

} /* Endbody */


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mmu_disable
* Returned Value  : void
* Comments        :
*   Disable the operation of the mmu
*
*END*---------------------------------------------------------------------*/

void _mmu_disable
   (
      void
   )
{ /* Body */

   /* Finish all data writes */
   _PSP_SYNC();

   /* Disable IMMU and DMMU */
   _PSP_SET_SR(_PSP_GET_SR() & ~(PSP_MSR_IR | PSP_MSR_DR));
   _PSP_ISYNC();
   _PSP_SYNC();

   /* Clear BAT registers */
   _PSP_SPR_SET(E300CORE_IBATU0, 0);
   _PSP_SPR_SET(E300CORE_IBATL0, 0);
   _PSP_SPR_SET(E300CORE_IBATU1, 0);
   _PSP_SPR_SET(E300CORE_IBATL1, 0);
   _PSP_SPR_SET(E300CORE_IBATU2, 0);
   _PSP_SPR_SET(E300CORE_IBATL2, 0);
   _PSP_SPR_SET(E300CORE_IBATU3, 0);
   _PSP_SPR_SET(E300CORE_IBATL3, 0);
   _PSP_SPR_SET(E300CORE_IBATU4, 0);
   _PSP_SPR_SET(E300CORE_IBATL4, 0);
   _PSP_SPR_SET(E300CORE_IBATU5, 0);
   _PSP_SPR_SET(E300CORE_IBATL5, 0);
   _PSP_SPR_SET(E300CORE_IBATU6, 0);
   _PSP_SPR_SET(E300CORE_IBATL6, 0);
   _PSP_SPR_SET(E300CORE_IBATU7, 0);
   _PSP_SPR_SET(E300CORE_IBATL7, 0);

   _PSP_SPR_SET(E300CORE_DBATU0, 0);
   _PSP_SPR_SET(E300CORE_DBATL0, 0);
   _PSP_SPR_SET(E300CORE_DBATU1, 0);
   _PSP_SPR_SET(E300CORE_DBATL1, 0);
   _PSP_SPR_SET(E300CORE_DBATU2, 0);
   _PSP_SPR_SET(E300CORE_DBATL2, 0);
   _PSP_SPR_SET(E300CORE_DBATU3, 0);
   _PSP_SPR_SET(E300CORE_DBATL3, 0);
   _PSP_SPR_SET(E300CORE_DBATU4, 0);
   _PSP_SPR_SET(E300CORE_DBATL4, 0);
   _PSP_SPR_SET(E300CORE_DBATU5, 0);
   _PSP_SPR_SET(E300CORE_DBATL5, 0);
   _PSP_SPR_SET(E300CORE_DBATU6, 0);
   _PSP_SPR_SET(E300CORE_DBATL6, 0);
   _PSP_SPR_SET(E300CORE_DBATU7, 0);
   _PSP_SPR_SET(E300CORE_DBATL7, 0);

} /* Endbody */

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mmu_add_region
* Returned Value  : MQX_OK or an error code
* Comments        :
*   Initialize the mmu
*
*END*---------------------------------------------------------------------*/

_mqx_uint _mmu_add_region
   (
      /* [IN] the starting location of the memory block */
      uchar_ptr mem_ptr, 

      /* [IN] the size of the memory block */
      _mem_size size, 

      /* [IN] flags indicating what type of memory this is */
      _mqx_uint flags
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR     kernel_data;
   PSP_SUPPORT_STRUCT_PTR     psp_support_ptr;
   PSP_BAT_REGISTER_ENTRY_PTR bat;
   uint_32                    block_size = 0;

   _GET_KERNEL_DATA(kernel_data);
   psp_support_ptr = kernel_data->PSP_SUPPORT_PTR;
   if (psp_support_ptr == NULL) {
      return MQX_OUT_OF_MEMORY;
   } /* Endif */

   /*
   ** Regions that are mapped to both data and code must be
   ** done separately
   */
   if ((flags & E300CORE_MMU_SET_IBAT) && (flags & E300CORE_MMU_SET_DBAT)) {
      return(E300CORE_MMU_INVALID_FLAGS);
   } /* Endif */

   while (size > block_size) {

      size -= block_size;

      if (flags & E300CORE_MMU_SET_IBAT) {
         /* Program BAT array for the code cache */

         if (psp_support_ptr->IBAT_COUNT >= _NELEM(psp_support_ptr->IBAT_TABLE)) {
            return(E300CORE_OUT_OF_IBATS);
         } /* Endif */
     bat = &psp_support_ptr->IBAT_TABLE[psp_support_ptr->IBAT_COUNT];

         ++psp_support_ptr->IBAT_COUNT;
      } else {
         /* Program BAT array for the data cache */

         if (psp_support_ptr->DBAT_COUNT >= _NELEM(psp_support_ptr->DBAT_TABLE)) {
            return(E300CORE_OUT_OF_DBATS);
         } /* Endif */
     bat = &psp_support_ptr->DBAT_TABLE[psp_support_ptr->DBAT_COUNT];

         ++psp_support_ptr->DBAT_COUNT;
      } /* Endif */

      /* This will add region (minimum of 16 meg) to the instruction or code 
      ** cache/mmu BAT array accessable in both user and supervisor mode.
      */

      /* Set the attributes for the region */
      bat->attr_lo = (uint_32)mem_ptr & E300CORE_BATL_BRPN_MASK;

      if ( flags & E300CORE_MMU_CACHE_INHIBIT ) {
         bat->attr_lo |= E300CORE_BATL_CACHE_INHIBIT;
      } /* Endif */

      if ( flags & E300CORE_MMU_CACHE_WRITE_THRU ) {
         bat->attr_lo |= E300CORE_BATL_CACHE_WRITE_THRU;
      } /* Endif */

      if ( flags & E300CORE_MMU_CACHE_GUARDED ) {
         bat->attr_lo |= E300CORE_BATL_CACHE_GUARDED;
      } /* Endif */

      if ( flags & E300CORE_MMU_CACHE_COHERENT ) {
         bat->attr_lo |= E300CORE_BATL_CACHE_COHERENT;
      } /* Endif */

      if ( flags & E300CORE_MMU_READ_ONLY ) {
         bat->attr_lo |= E300CORE_BATL_READ_ONLY;
      } else {
         bat->attr_lo |= E300CORE_BATL_READ_WRITE;
      } /* Endif */

      bat->attr_hi = (uint_32)mem_ptr & E300CORE_BATU_BEPI_MASK;
      if ( size <= 0x1000000) {
          block_size = 0x1000000;
          bat->attr_hi |= E300CORE_BATU_16MEG_BLOCK_SIZE;
      } else if ( size <= 0x2000000) {
          block_size = 0x2000000;
          bat->attr_hi |= E300CORE_BATU_32MEG_BLOCK_SIZE;
      } else if ( size <= 0x4000000) {
          block_size = 0x4000000;
          bat->attr_hi |= E300CORE_BATU_64MEG_BLOCK_SIZE;
      } else if ( size <= 0x8000000) {
          block_size = 0x8000000;
          bat->attr_hi |= E300CORE_BATU_128MEG_BLOCK_SIZE;
      } else {
          block_size = 0x10000000;
          bat->attr_hi |= E300CORE_BATU_256MEG_BLOCK_SIZE;
      } /* Endif */

      bat->attr_hi |= E300CORE_BATU_SUPER_ACCESS;
      bat->attr_hi |= E300CORE_BATU_USER_ACCESS;

      bat->lo = (uchar_ptr)((uint_32)mem_ptr & E300CORE_BATL_BRPN_MASK);
      bat->hi = bat->lo + block_size - 1;

      mem_ptr += block_size;

   } /* Endwhile */

   return(MQX_OK);

} /* Endbody */

/* EOF */

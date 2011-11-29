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
* $FileName: mcf5301.c$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*   This file contains utiltity functions for use with a mcf5301x.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "mcf5301.h"
#include "mmu.h"

/* Copies of control registers */
volatile uint_32 _psp_saved_cacr = 0;
volatile uint_32 _psp_saved_acr0 = 0;
volatile uint_32 _psp_saved_acr1 = 0;
volatile uint_32 _psp_saved_mbar = 0xFC000000;

#define NYI()

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf5301_initialize_support
* Returned Value   : none
* Comments         :
*  Initilize the support functions for the mcf5301
*
*END*------------------------------------------------------------------------*/

void _mcf5301_initialize_support
    (
        /* [IN] dummy parameter */
        uint_32 param
    )
{
#if PSP_HAS_SUPPORT_STRUCT
    KERNEL_DATA_STRUCT_PTR kernel_data;


    _GET_KERNEL_DATA(kernel_data);

    kernel_data->PSP_SUPPORT_PTR = _mem_alloc_system_zero((uint_32)sizeof(PSP_SUPPORT_STRUCT));
#endif  /* PSP_HAS_SUPPORT_STRUCT */
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf5301_cache_enable
* Returned Value   : none
* Comments         :
*   This function enables the instruction cache or data cache or 
*	both instruction & data cache.
*
*END*----------------------------------------------------------------------*/

void _mcf5301_cache_enable
   (
      uint_32 flag
   )
{ /* Body */
   uint_32 tmp = _PSP_GET_CACR();

   tmp &= ~(0 | MCF53XX_CACR_EUSP );            /* Enable user stack pointer */


   /* Invalidate instruction and data cache */
#if (PSP_HAS_CODE_CACHE || PSP_HAS_DATA_CACHE)
   _PSP_SET_CACR(tmp  | MCF53XX_CACR_CINVA  );  /* Cache invalidate */
           
#endif


         
   tmp |= MCF53XX_CACR_EC			            	/* Enable cache */
       | MCF53XX_CACR_DCM(0) ;       	      	/* Default cache mode disabled */
      
   _PSP_SET_CACR(tmp);
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf5301_cache_disable
* Returned Value   : none
* Comments         :
*   This function disables the cache
*
*END*----------------------------------------------------------------------*/

void _mcf5301_cache_disable
   (
      void
   )
{ /* Body */
   uint_32 tmp = _PSP_GET_CACR();
   tmp &= ~(MCF53XX_CACR_EC);
   _PSP_SET_CACR(tmp);

   /* Invalidate instruction and data cache */
#if (PSP_HAS_CODE_CACHE || PSP_HAS_DATA_CACHE)
   _PSP_SET_CACR(tmp | MCF53XX_CACR_CINVA );    /* Cache invalidate */
             	
#endif

} /* Endbody */

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mmu_init
* Returned Value  : void
* Comments        :
*   Initialize the mmu and set default properties for regions not mapped by
*   the ACR registers.
*
*END*---------------------------------------------------------------------*/

void _mmu_init
   (
      /* [IN] default properties */
      pointer mmu_init
   )
{
   PSP_MMU_INIT_STRUCT_PTR mmu = mmu_init;
   KERNEL_DATA_STRUCT_PTR  kernel_data;
   PSP_SUPPORT_STRUCT_PTR  psp_support_ptr;
   uint_32  mode;
   uint_32  tmp;
   _mqx_int i;

   _GET_KERNEL_DATA(kernel_data);
   psp_support_ptr = (PSP_SUPPORT_STRUCT_PTR)kernel_data->PSP_SUPPORT_PTR;

   if (psp_support_ptr == NULL || mmu == 0) {
      _mqx_fatal_error(MQX_INVALID_POINTER);
   } /* Endif */

   /* Stop and invalidate the cache */
   _mcf5301_cache_disable();
   
   _mem_zero(psp_support_ptr->ACR_VALS, sizeof(psp_support_ptr->ACR_VALS));

   mode = mmu->INITIAL_CACR_ENABLE_BITS & ~(MCF53XX_CACR_EUSP);
   tmp = _PSP_GET_CACR();
   tmp |= mode;
   _PSP_SET_CACR(tmp);
} /* Endbody */

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mmu_enable
* Returned Value  : none
* Comments        :
*   Enables all ACRs in use
*
*END*---------------------------------------------------------------------*/

void _mmu_enable
   (
      void
   )
{ /* Body */

   KERNEL_DATA_STRUCT_PTR  kernel_data;
   PSP_SUPPORT_STRUCT_PTR  psp_support_ptr;

   _GET_KERNEL_DATA(kernel_data);
   psp_support_ptr = (PSP_SUPPORT_STRUCT_PTR)kernel_data->PSP_SUPPORT_PTR;

   if (psp_support_ptr == NULL) {
      _mqx_fatal_error(MQX_INVALID_POINTER);
   } /* Endif */

   __psp_enable_acrs(psp_support_ptr->ACR_VALS);

} /* Endbody */

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mmu_disable
* Returned Value  : none
* Comments        :
*   Disables all ACRs
*
*END*---------------------------------------------------------------------*/

void _mmu_disable
   (
      void
   )
{ /* Body */

   __psp_clear_acrs();

} /* Endbody */

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mmu_add_region
* Returned Value  : uint_32 MQX_OK or an error code
* Comments        :
*   Change the properties for a given region
*
*END*---------------------------------------------------------------------*/

_mqx_uint _mmu_add_region
   (
      /* [IN] the starting location of the memory block */
      uchar_ptr mem_ptr,

      /* [IN] the mask to apply to the memory block */
      _mem_size mem_size,

      /* [IN] flags indicating what type of memory this is */
      _mqx_uint mem_attrs
   )
{
   KERNEL_DATA_STRUCT_PTR  kernel_data;
   PSP_SUPPORT_STRUCT_PTR  psp_support_ptr;
   uint_32                 acr_val = 0;
   uint_32                 acr_num, base, base_mask;
   _mqx_int                i;

   _GET_KERNEL_DATA(kernel_data);
   psp_support_ptr = (PSP_SUPPORT_STRUCT_PTR)kernel_data->PSP_SUPPORT_PTR;

   if (psp_support_ptr == NULL) {
      return MQX_OUT_OF_MEMORY;
   }

   /* Have we used up all data ACRs? */
   if (psp_support_ptr->ACR_VALS[MCF5301_NUM_ACRS - 1] != 0) {
      return MCF5301_OUT_OF_ACRS;
   }

   /* Build value to place in ACR */
   base = (uint_32)mem_ptr;

   base_mask  = (mem_size-1)>>8;
   base_mask &= MCF53XX_ACR_BASE_ADDR_MASK; /* 0x00ff0000 */
   base      &= MCF53XX_ACR_BASE_ADDR;      /* 0xff000000 */
   acr_val = base | base_mask;

#undef  ATTRMAP
#define ATTRMAP(x,y)        { if ((mem_attrs & x) != 0) acr_val |= y; }
   
   ATTRMAP(PSP_MMU_WRITE_BUFFERED, MCF53XX_ACR_BUFFER_WRITE_ENABLE);

   if ((mem_attrs & PSP_MMU_EXEC_ALLOWED) != 0) {
      
      /* Create Code region */
      
      ATTRMAP(PSP_MMU_CODE_CACHE_INHIBITED, MCF53XX_ACR_NONCACHEABLE_MODE);
      ATTRMAP(PSP_MMU_WRITE_PROTECTED, MCF53XX_ACR_WRITE_PROTECT);
      
      /* Execute cache matching on all accesses */
      /*acr_val |=  MCF53XX_ACR_IGNORE_FC;*/

      for (i = 0, acr_num = 0; i < MCF5301_NUM_ACRS; i++, acr_num++) {
         if (psp_support_ptr->ACR_VALS[acr_num] == 0) {
            psp_support_ptr->ACR_VALS[acr_num] = acr_val | MCF53XX_ACR_ENABLE;
            break;
         }
      }
   } else {
   
      /* Create Data region */
      ATTRMAP(PSP_MMU_DATA_CACHE_INHIBITED, MCF53XX_ACR_NONCACHEABLE_MODE);
      ATTRMAP(PSP_MMU_WRITE_THROUGH, MCF53XX_ACR_CACHEABLE_MODE);
      ATTRMAP(PSP_MMU_WRITE_BUFFERED, MCF53XX_ACR_BUFFER_WRITE_ENABLE);
   
      /* Execute cache matching on all accesses */
      /*acr_val |=  MCF5301_ACR_IGNORE_FC;*/
   
      for (i = 0, acr_num = 0; i < MCF5301_NUM_ACRS; i++, acr_num++) {
         if (psp_support_ptr->ACR_VALS[acr_num] == 0) {
            psp_support_ptr->ACR_VALS[acr_num] = acr_val | MCF53XX_ACR_ENABLE;
            break;
         }
      }
   } /* Endif*/

   return MQX_OK;
} /* Endbody */

/* EOF */
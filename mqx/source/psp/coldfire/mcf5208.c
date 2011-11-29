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
* $FileName: mcf5208.c$
* $Version : 3.7.5.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains utiltity functions for use with a mcf5208x.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "mcf5208.h"    
#include "mmu.h"  

/* Copies of control registers */
volatile uint_32 _psp_saved_cacr = 0;
volatile uint_32 _psp_saved_acr0 = 0;
volatile uint_32 _psp_saved_acr1 = 0;
volatile uint_32 _psp_saved_mbar = 0xFC000000;



#define NYI()

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf5208_initialize_support
* Returned Value   : none
* Comments         :
*  Initilize the support functions for the mcf5208
*
*END*------------------------------------------------------------------------*/

void _mcf5208_initialize_support
    (
        /* [IN] dummy parameter */
        uint_32 param
    )
{
#if PSP_HAS_SUPPORT_STRUCT
    KERNEL_DATA_STRUCT_PTR kernel_data;


    _GET_KERNEL_DATA(kernel_data);

    kernel_data->PSP_SUPPORT_PTR = _mem_alloc_system_zero((uint_32)sizeof(PSP_SUPPORT_STRUCT));
#endif  /* PSP_HAS_SUPPORT_STRUCT  */  
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf5208_cache_enable
* Returned Value   : none
* Comments         :
*   This function enables the instruction cache or data cache or 
*   both instruction & data cache.
*
*END*----------------------------------------------------------------------*/

void _mcf5208_cache_enable
   (
      uint_32 flag
   )
{ /* Body */
   uint_32 tmp = _PSP_GET_CACR();

   tmp &= ~(0
      | MCF5208_CACR_EUSP               /* Enable user stack pointer */
      | MCF5208_CACR_LINE_FILL_11
      | MCF5208_CACR_CFRZ               /* Cache Freeze */
   );
   tmp |= (0
      | MCF5208_CACR_DISI               /* Disable Instruction Cache */
      | MCF5208_CACR_DISD               /* Disable Data Cache */
   );

   /* Invalidate instruction cache */
#if PSP_HAS_CODE_CACHE
   _PSP_SET_CACR(tmp
      | MCF5208_CACR_CINV               /* Cache invalidate */
      | MCF5208_CACR_INVI);             /* Invalidate instr cache only */
   tmp &= ~MCF5208_CACR_DISI;
#endif

   /* Invalidate data cache */
#if PSP_HAS_DATA_CACHE
   _PSP_SET_CACR(tmp
      | MCF5208_CACR_CINV               /* Cache invalidate */
      | MCF5208_CACR_INVD);             /* Invalidate data cache only */
   tmp &= ~MCF5208_CACR_DISD;
#endif

   switch (flag) {      
      case 0:
         /* Enable instruction cache only */
         tmp |= MCF5208_CACR_DISD;      /* Disable data cache */
         break;      
      case 1:
         /* Enable data cache only */
         tmp |= MCF5208_CACR_DISI;      /* Disable instr cache */
         break;
      case 2:
         /* Enable both instr & data cache */
         break;
    } /* EndSwtich */
         
   tmp |= MCF5208_CACR_CENB             /* Enable cache */
      | MCF5208_CACR_DCM                /* Default cache mode disabled */
      | MCF5208_CACR_CEIB               /* Enable noncacheable instruction bursting */
      | MCF5208_CACR_LINE_FILL_00;

   _PSP_SET_CACR(tmp);
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf5208_cache_disable
* Returned Value   : none
* Comments         :
*   This function disables the cache
*
*END*----------------------------------------------------------------------*/

void _mcf5208_cache_disable
   (
      void
   )
{ /* Body */
   uint_32 tmp = _PSP_GET_CACR();
   tmp &= ~(MCF5208_CACR_CENB);
   _PSP_SET_CACR(tmp);

   /* Invalidate instruction cache */
#if PSP_HAS_CODE_CACHE
   _PSP_SET_CACR(tmp
      | MCF5208_CACR_CINV               /* Cache invalidate */
      | MCF5208_CACR_INVI);             /* Invalidate instruction cache only */
#endif

   /* Invalidate data cache */
#if PSP_HAS_DATA_CACHE
   _PSP_SET_CACR(tmp
      | MCF5208_CACR_CINV               /* Cache invalidate */
      | MCF5208_CACR_INVD);             /* Invalidate data cache only */
#endif

}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf5208_icache_invalidate
* Returned Value   : none
* Comments         :
*   This function invalidates the instruction cache
*
*END*----------------------------------------------------------------------*/

void _mcf5208_icache_invalidate
   (
      void
   )
{ /* Body */
   uint_32 tmp = _PSP_GET_CACR();
   
   tmp |= MCF5208_CACR_CINV | MCF5208_CACR_INVI;
   _PSP_SET_CACR(tmp);
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf5208_dcache_invalidate
* Returned Value   : none
* Comments         :
*   This function invalidates the data cache
*
*END*----------------------------------------------------------------------*/

void _mcf5208_dcache_invalidate
   (
      void
   )
{
   uint_32 tmp = _PSP_GET_CACR();

   _PSP_SYNC(); /* Complete all instructions in the pipeline */

   tmp |= MCF5208_CACR_CINV | MCF5208_CACR_INVD;
   _PSP_SET_CACR(tmp);

}


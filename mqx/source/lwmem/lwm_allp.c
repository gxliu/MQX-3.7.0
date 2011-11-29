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
* $FileName: lwm_allp.c$
* $Version : 3.5.6.0$
* $Date    : Jan-13-2010$
*
* Comments:
*
*   This file contains the function that allocates a memory block.
*
*END************************************************************************/

#include "mqx_inc.h"
#if MQX_USE_LWMEM
#include "lwmem.h"
#include "lwmemprv.h"

/*FUNCTION*-----------------------------------------------------
* 
* Function Name    : _lwmem_alloc_from
* Returned Value   : pointer NULL is returned upon error.
* Comments         : Allocates a block of memory from a specified
*   pool
*
*END*---------------------------------------------------------*/

pointer _lwmem_alloc_from
   (
      /* [IN] the pool to allocate from */
      _lwmem_pool_id  pool_id,

      /* [IN] the size of the memory block */
      _mem_size       requested_size

   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR  kernel_data;
   pointer                 result;

   _GET_KERNEL_DATA(kernel_data);
   _KLOGE3(KLOG_lwmem_alloc_from, pool_id, requested_size);

   result = _lwmem_alloc_internal(requested_size, kernel_data->ACTIVE_PTR, 
      pool_id, FALSE);

   _KLOGX2(KLOG_lwmem_alloc_from, result);
   return(result);

} /* Endbody */
#endif /* MQX_USE_LWMEM */

/* EOF */

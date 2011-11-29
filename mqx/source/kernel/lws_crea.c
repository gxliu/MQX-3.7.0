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
* $FileName: lws_crea.c$
* $Version : 3.6.5.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the functions for manipulating the 
*   light weight semaphores.  These semaphores have low memory
*   requirements, and no extra features.  Tasks are suspended
*   in fifo order while waiting for a post.  No limits on values
*   are imposed.
*
*END************************************************************************/

#include "mqx_inc.h"

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _lwsem_create
* Returned Value   : _mqx_uint - MQX_OK or an error code
*   queue
* Comments         :
*   This function initializes a light weight semaphore.
*
*END*----------------------------------------------------------------------*/

static _mqx_uint _lwsem_create_internal
   ( 
      /* [IN] the address of the semaphore to initialize */
      LWSEM_STRUCT_PTR  sem_ptr,

      /* [IN] the inital number of semaphores available  */
      _mqx_int          initial_number,
      
      /* [IN] TRUE if semaphore will ne hidden from kernel   */
      boolean           hidden
      
   )
{ /* Body */
   KERNEL_DATA_STRUCT_PTR kernel_data;
   LWSEM_STRUCT_PTR  sem_chk_ptr;

   _GET_KERNEL_DATA(kernel_data);

   _KLOGE2(KLOG_lwsem_create, initial_number);

   sem_ptr->VALUE  = initial_number;
   _QUEUE_INIT(&sem_ptr->TD_QUEUE, 0);
   _int_disable();

  if (!hidden) {
#if MQX_CHECK_ERRORS
      /* Check if lwsem is already initialized */
      sem_chk_ptr = (LWSEM_STRUCT_PTR)((pointer)kernel_data->LWSEM.NEXT);
      while (sem_chk_ptr != (LWSEM_STRUCT_PTR)((pointer)&kernel_data->LWSEM)) {
         if (sem_chk_ptr == sem_ptr) {
            _int_enable();
            _KLOGX2(KLOG_lwsem_create, MQX_EINVAL);
            return(MQX_EINVAL);
         } /* Endif */
         sem_chk_ptr = (LWSEM_STRUCT_PTR)((pointer)sem_chk_ptr->NEXT);
      } /* Endwhile */
#endif

      _QUEUE_ENQUEUE(&kernel_data->LWSEM, sem_ptr);
  }
   sem_ptr->VALID  = LWSEM_VALID;
   _int_enable();

   _KLOGX2(KLOG_lwsem_create, MQX_OK);

   return(MQX_OK);
   
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _lwsem_create
* Returned Value   : _mqx_uint - MQX_OK or an error code
*   queue
* Comments         :
*   This function initializes a light weight semaphore.
*
*END*----------------------------------------------------------------------*/

_mqx_uint _lwsem_create
   ( 
      /* [IN] the address of the semaphore to initialize */
      LWSEM_STRUCT_PTR sem_ptr,

      /* [IN] the inital number of semaphores available  */
      _mqx_int         initial_number
   )
{ 
   return _lwsem_create_internal(sem_ptr, initial_number, FALSE);
   
}


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _lwsem_create_hidden
* Returned Value   : _mqx_uint - MQX_OK or an error code
*   queue
* Comments         :
*   This function initializes a light weight semaphore.
*
*END*----------------------------------------------------------------------*/

_mqx_uint _lwsem_create_hidden
   ( 
      /* [IN] the address of the semaphore to initialize */
      LWSEM_STRUCT_PTR sem_ptr,

      /* [IN] the inital number of semaphores available  */
      _mqx_int         initial_number
   )
{ 
   return _lwsem_create_internal(sem_ptr, initial_number, TRUE);
}


/* EOF */

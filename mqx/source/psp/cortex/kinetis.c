/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
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
* $FileName: kinetis.c$
* $Version : 3.7.3.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains utiltity functions for use with a Kinetis.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "kinetis.h"


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _kinetis_initialize_support
* Returned Value   : none
* Comments         :
*   Initilize the support functions for the Kinetis platforms
*
*END*------------------------------------------------------------------------*/

void _kinetis_initialize_support
   (
      /* [IN] dummy parameter */
      uint_32 param
   )
{ /* Body */
#if PSP_HAS_SUPPORT_STRUCT

    KERNEL_DATA_STRUCT_PTR kernel_data;
    _GET_KERNEL_DATA(kernel_data);

    kernel_data->PSP_SUPPORT_PTR = _mem_alloc_system_zero((uint_32)sizeof(PSP_SUPPORT_STRUCT));
    _mem_set_type(kernel_data->PSP_SUPPORT_PTR, MEM_TYPE_PSP_SUPPORT_STRUCT);
#endif
} /* Endbody */

/* EOF */

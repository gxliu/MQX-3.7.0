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
* $FileName: serl_mcf5441.c$
* $Version : 3.6.5.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains board-specific serial initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "serl_mcf54xx.h"

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_serial_base_address
* Returned Value   : Address upon success, NULL upon failure
* Comments         :
*    This function returns the base register address of the corresponding UART
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_serial_base_address(uint_8 dev_num) {

   VMCF5441_STRUCT_PTR reg_base = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();

/* find base addr accordign to device number */
   switch (dev_num) {
      case 0:
         return (pointer)&reg_base->UART0;
         break;
      case 1:
         return (pointer)&reg_base->UART1;
         break;
      case 2:
         return (pointer)&reg_base->UART2;
         break;
      case 3:
         return (pointer)&reg_base->UART3;
         break;
      case 4:
         return (pointer)&reg_base->UART4;
         break;
      case 5:
         return (pointer)&reg_base->UART5;
         break;
      case 6:
         return (pointer)&reg_base->UART6;
         break;
      case 7:
         return (pointer)&reg_base->UART7;
         break;
      case 8:
         return (pointer)&reg_base->UART8;
         break;
      case 9:
         return (pointer)&reg_base->UART9;
         break;
      default:
         return NULL;
   } /* Endswitch */ 
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_serial_vector
* Returned Value   : Vector number upon success, 0 upon failure
* Comments         :
*    This function returns desired interrupt vector number for specified UART
*
*END*----------------------------------------------------------------------*/
PSP_INTERRUPT_TABLE_INDEX _bsp_get_serial_vector
(
   uint_8 dev_num
)
{
    volatile PSP_INTERRUPT_TABLE_INDEX vector;
    switch (dev_num) {
      case 0:
         vector = MCF5441_INT_UART0;
         break;
      case 1:
         vector = MCF5441_INT_UART1;
         break;
      case 2:
         vector = MCF5441_INT_UART2;
         break;
      case 3:
         vector = MCF5441_INT_UART3;
         break;
      case 4:
         vector = MCF5441_INT_UART4;
         break;
      case 5:
         vector = MCF5441_INT_UART5;
         break;
      case 6:
         vector = MCF5441_INT_UART6;
         break;
      case 7:
         vector = MCF5441_INT_UART7;
         break;
      case 8:
         vector = MCF5441_INT_UART8;
         break;
      case 9:
         vector = MCF5441_INT_UART9;
         break;              
      default:
         vector = (PSP_INTERRUPT_TABLE_INDEX)0;
         break;
    } /* Endswitch */
    return vector;
}

/* EOF */

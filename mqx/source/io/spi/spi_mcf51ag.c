/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: spi_mcf51ag.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains board-specific SPI initialization functions.
*
*END************************************************************************/
#include <user_config.h>
#include <mqx.h>
#include <bsp.h>
#include "spi_mcf5xxx_spi16.h"

#if (BSPCFG_ENABLE_SPI0 || BSPCFG_ENABLE_ISPI0 || BSPCFG_ENABLE_SPI1 || BSPCFG_ENABLE_ISPI1)

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_spi_base_address
* Returned Value   : Address upon success, NULL upon failure
* Comments         :
*    This function returns the base register address of the corresponding SPI
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_spi_base_address
(
   uint_8 dev_num
)
{
   pointer addr;
    
   switch (dev_num) 
   {
      case 0:
         addr = (pointer)&(((VMCF51AG_STRUCT_PTR)BSP_IPSBAR)->SPI1);
         break;
      case 1:
         addr = (pointer)&(((VMCF51AG_STRUCT_PTR)BSP_IPSBAR)->SPI2);
         break;
      default:
         addr = NULL;
         break;
   }
   return addr;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_spi_vector
* Returned Value   : Vector number upon success, 0 upon failure
* Comments         :
*    This function returns desired interrupt vector number for specified SPI
*
*END*----------------------------------------------------------------------*/
uint_32 _bsp_get_spi_vector
(
   uint_8 dev_num
)
{
   uint_32 vector;
   switch (dev_num) {
        case 0:
         vector = MCF51AG_INT_Vspi1;
         break;
      case 1:
         vector = MCF51AG_INT_Vspi2;
         break;
      default:
         vector = 0;
         break;
   }
   return vector;
}

#endif /*(BSPCFG_ENABLE_SPI0 || BSPCFG_ENABLE_ISPI0 || BSPCFG_ENABLE_SPI1 || BSPCFG_ENABLE_ISPI1)*/
/* EOF */

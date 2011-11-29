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
* $FileName: i2c_mcf5441.c$
* $Version : 3.5.2.0$
* $Date    : Nov-27-2009$
*
* Comments:
*
*   This file contains board-specific I2C initialization functions.
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include "i2c_mcf54xx.h"


/*FUNCTION****************************************************************
*
* Function Name    : _bsp_get_i2c_base_address
* Returned Value   : address if successful, NULL otherwise
* Comments         :
*    This function returns the base register address of the corresponding I2C device.
*
*END*********************************************************************/

pointer _bsp_get_i2c_base_address
(
   uint_8 dev_num
)
{
   pointer addr;
   
   switch (dev_num) 
   {
      case 0:
         addr = (pointer)&(((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->I2C0);
         break;
      case 1:
         addr = (pointer)&(((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->I2C1);
         break;
      case 2:
         addr = (pointer)&(((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->I2C2);
         break;
      case 3:
         addr = (pointer)&(((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->I2C3);
         break;
      case 4:
         addr = (pointer)&(((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->I2C4);
         break;
      case 5:
         addr = (pointer)&(((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->I2C5);
         break;
      default:
        addr = NULL;
        break;
    }
    return addr;
}


/*FUNCTION****************************************************************
*
* Function Name    : _bsp_get_i2c_vector
* Returned Value   : vector number if successful, 0 otherwise
* Comments         :
*    This function returns desired interrupt vector number for specified I2C device.
*
*END*********************************************************************/

uint_32 _bsp_get_i2c_vector
(
   uint_8 dev_num
)
{
   uint_32 vector;
   switch (dev_num) 
   {
      case 0:
         vector = MCF5441_INT_I2C0;
         break;
      case 1:
         vector = MCF5441_INT_I2C1;
         break;
      case 2:
         vector = MCF5441_INT_I2C2;
         break;
      case 3:
         vector = MCF5441_INT_I2C3;
         break;
      case 4:
         vector = MCF5441_INT_I2C4;
         break;
      case 5:
         vector = MCF5441_INT_I2C5;
         break;
      default:
         vector = 0;
         break;
    }
    return vector;
}
/* EOF */

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
* $FileName: i2c_mcf5222.c$
* $Version : 3.6.3.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains board-specific i2c initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "i2c_mcf52xx.h"

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_i2c_base_address
* Returned Value   : Address upon success, NULL upon failure
* Comments         :
*    This function returns the base register address of the corresponding I2C
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_i2c_base_address
(
    uint_8 dev_num
)
{
    pointer addr;
    
    switch (dev_num) {
      case 0:
         addr = (pointer)&(((VMCF5222_STRUCT_PTR)_PSP_GET_IPSBAR())->I2C);
         break;
      default:
         addr = NULL;
         break;
    }
    return addr;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_i2c_vector
* Returned Value   : Vector number upon success, 0 upon failure
* Comments         :
*    This function returns desired interrupt vector number for specified I2C
*
*END*----------------------------------------------------------------------*/
uint_32 _bsp_get_i2c_vector
(
   uint_8 dev_num
)
{
    uint_32 vector;
    switch (dev_num) {
      case 0:
         vector = MCF5222_INT_I2C;
         break;
      default:
         vector = 0;
         break;
    } /* Endswitch */
    return vector;
}

/* EOF */

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
* $FileName: dac_pdd_mcf51mm.c$
* $Version : 3.6.1.0$
* $Date    : May-19-2010$
*
* Comments:
*
*   This file contains the DAC driver CPU specific functions
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include <fio_prv.h>
#include "io.h"
#include "dac_pdd_mcf51mm.h"


/*FUNCTION*********************************************************************
* 
* Function Name   : _bsp_get_dac_base_address()
*
* Input Params    : dac_module_number - the number of DAC module
*
* Returned Value  : The DAC module base address
*
* Comments        : 
*
*END**************************************************************************/


DAC_MemMapPtr _bsp_get_dac_base_address(uint_8 dac_module_number)
{
    /* Check if DAC number is correct */
    if (dac_module_number > DAC_COUNT)  {
        return NULL;
    } else 
    {
        return (&((VMCF51MM_STRUCT_PTR)_PSP_GET_MBAR())->DAC);
    }
}


/*FUNCTION*********************************************************************
* 
* Function Name   : _bsp_get_dac_vector()
*
* Input Params    : dac_module_number - the number of DAC module
*
* Returned Value  : The DAC module interrupt vector number
*
* Comments        : 
*
*END**************************************************************************/

uint_32 _bsp_get_dac_vector(uint_8 dac_module_number)
{
    return (MCF51MM_INT_Vdac);
}
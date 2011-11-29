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
* $FileName: flash_mk40.c$
* $Version : 3.6.3.0$
* $Date    : Nov-9-2010$
*
* Comments:
*
*   The file contains device specific flash functions.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "flash_kinetis.h"
#include "flash_mk40.h"

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_ftfl_address
* Returned Value   : Address upon success
* Comments         :
*    This function returns the base register address of the FTFL.
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_ftfl_address
(
    void
)
{
    return (pointer)(FTFL_BASE_PTR);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mk40_flash_install_internal
* Returned Value   : uint_32 a task error code or MQX_OK
* Comments         :
*    Install a internal flash device.
*
*END*----------------------------------------------------------------------*/
uint_32 _mk40_flash_install_internal
(
    /* [IN] A string that identifies the device for fopen */
    char_ptr           identifier,
    
    /* [IN] Flash size */
    uint_32            flashx_size
) 
{
   SIM_MemMapPtr sim = SIM_BASE_PTR;
   sim->SCGC6 |= SIM_SCGC6_FTFL_MASK;
   return kinetis_flash_install_internal (identifier, flashx_size);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : kinetis_flash_invalidate_cache
* Returned Value   : none
* Comments         :
*    Invalidate flash cache to expose flash changes.
*
*END*----------------------------------------------------------------------*/
void kinetis_flash_invalidate_cache
(
    /* [IN] What exactly to invalidate */
    uint_32 flags
) 
{
    /* Invalidate flash cache block 0 */
    if (flags & FLASHX_INVALIDATE_CACHE_BLOCK0)
    {
        FMC_PFB0CR |= FMC_PFB0CR_S_B_INV_MASK | FMC_PFB0CR_CINV_WAY_MASK;
    }
}

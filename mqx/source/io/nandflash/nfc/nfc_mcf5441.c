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
* $FileName: nfc_mcf5441.c$
* $Version : 3.6.2.0$
* $Date    : Feb-10-2011$
*
* Comments:
*
*   This file contains board-specific NAND Flash Controller module functions.
*
*END************************************************************************/

#include "mqx.h" 
#include "bsp.h"
#include "nfc.h"

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_nfc_address
* Returned Value   : Address upon success
* Comments         :
*    This function returns the base register address of the NFC module.
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_nfc_address()
{
   return (pointer)(&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->NFC);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : nfc_io_init
* Returned Value   : -
* Comments         :
*    This function initializes NFC I/O Pins.
*
*END*----------------------------------------------------------------------*/
void nfc_io_init(void)
{
   return;
}

/* EOF */

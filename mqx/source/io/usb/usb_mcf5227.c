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
* $FileName: usb_mcf5227.c$
* $Version : 3.4.6.0$
* $Date    : Sep-22-2009$
*
* Comments:
*
*   This file contains board-specific USB initialization functions.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "usb_bsp.h"

static _mqx_int _bsp_usb_init(pointer param);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_usb_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to USB
*
*END*----------------------------------------------------------------------*/
static _mqx_int _bsp_usb_init(pointer param)
{
    VMCF5227_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
    uint_32 status;

    _bsp_usb_io_init();
    
    // setup interrupt
    status = _mcf5227_int_init(MCF5227_INT1_USB, 4, TRUE);
    
    if (status != MQX_OK) {
        return -1;
    }

    return MQX_OK;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_usb_dev_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to USB device
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_usb_dev_init(pointer param)
{
    return _bsp_usb_init(param);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_usb_host_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to USB host
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_usb_host_init(pointer param)
{
    return _bsp_usb_init(param);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_usb_base
* Returned Value   : Address upon success, NULL upon failure
* Comments         :
*    This function returns the address of USB OTG module
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_usb_base(uint_8 dev_num)
{
    if (dev_num != 0) {
        return NULL;
    }
   
    return (pointer)(&((VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR())->USBOTG);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_usb_capability_register_base
* Returned Value   : Address upon success, NULL upon failure
* Comments         :
*    This function returns the address of the VUSBHS Capability Registers
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_usb_capability_register_base(uint_8 dev_num)
{
    if (dev_num != 0) {
        return NULL;
    }
   
    return (pointer)((uint_32)&(((VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR())->USBOTG) + 0x100);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_usb_timer_register_base
* Returned Value   : Address upon success, NULL upon failure
* Comments         :
*    This function returns the address of the VUSBHS Timer Registers
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_usb_timer_register_base(uint_8 dev_num)
{
    if (dev_num != 0) {
        return NULL;
    }
   
    return (pointer)((uint_32)&(((VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR())->USBOTG) + 0x080);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_usb_otg_csr
* Returned Value   : Address upon success, NULL upon failure
* Comments         :
*    This function returns the address of the U0CSR register
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_usb_otg_csr(uint_8 dev_num)
{
    if (dev_num != 0) {
        return NULL;
    }
   
    return (pointer) &(((VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR())->CCM).UOCSR;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_usb_vector
* Returned Value   : Vector Number upon success, 0 upon failure
* Comments         :
*    This function returns the vector number of the VUSBHS Host Module
*
*END*----------------------------------------------------------------------*/
uint_8 _bsp_get_usb_vector
(
    uint_8 dev_num
)
{
    if (dev_num != 0) {
        return 0;
    }
   
    return MCF5227_INT1_USB;
}

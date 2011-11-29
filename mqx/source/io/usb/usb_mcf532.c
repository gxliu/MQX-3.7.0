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
* $FileName: usb_mcf532.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains board-specific USB initialization functions.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "usb_bsp.h"

boolean  host_device;
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_usb_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to USB
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_usb_dev_init(pointer param)
{
    VMCF5329_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
    uint_32 status;
    host_device=0;
    _bsp_usb_io_init(USB_CONNECTOR_OTG);
    
    /* setup interrupt */
    status = _mcf5329_int_init(MCF5329_INT_USB_OTG, 2, TRUE);
    
    if (status != MQX_OK) {
        return -1;
    }

    return MQX_OK;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_usb_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to USB
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_usb_host_init(pointer param)
{
    VMCF5329_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
    uint_32 status;
    host_device=1;

    _bsp_usb_io_init(USB_CONNECTOR_HOST);
    
    /* setup interrupt */
    status = _mcf5329_int_init(MCF5329_INT_USB_HOST, 2, TRUE);
    
    if (status != MQX_OK) {
        return -1;
    }

    return MQX_OK;
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
   if(host_device)
    	return (pointer)(&((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->USBHOST);
   else 
   		return (pointer)(&((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->USBOTG);
    
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
  
    if(host_device)
    	return (pointer)((uint_32)&(((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->USBHOST) + 0x100);
    else
    	return (pointer)((uint_32)&(((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->USBOTG) + 0x100);
     
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
   if(host_device)
    	return (pointer)((uint_32)&(((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->USBHOST) + 0x080);
   else 
        return (pointer)((uint_32)&(((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->USBOTG) + 0x080);
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
   
    return (pointer) &(((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->CCM).UOCSR;
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
   if(host_device)
    	return MCF5329_INT_USB_HOST;
   else
     	return MCF5329_INT_USB_OTG;
}

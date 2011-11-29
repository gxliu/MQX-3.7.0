/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: mcf51mm.c$
* $Version : 3.7.5.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains utiltity functions for use with a mcf51mm.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "mcf51mm.h"


/* Copies of control registers */
volatile uint_32 _psp_saved_cacr = 0;
volatile uint_32 _psp_saved_mbar = 0xFFFF8000;

#if MCF51MM_REV2_USB_PATCH
volatile uint_8 usb_stat_shadow = 0;
volatile uint_8 usb_int_stat_shadow = 0x00;
#endif

/*
** Define padding needed to make the STOREBLOCK_STRUCT align properly
** to cache line size (see mem_prv.h)
*/
//#define PSP_MEM_STOREBLOCK_ALIGNMENT   (2) /* padding in _mqx_uints */


#define NYI()

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mcf51MM_initialize_support
* Returned Value   : none
* Comments         :
*  Initilize the support functions for the mcf51mm
*
*END*------------------------------------------------------------------------*/
void _mcf51MM_initialize_support
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

#if MCF51MM_REV2_USB_PATCH
#if   __REGABI__
    __declspec(register_abi)
#elif __STDABI__
#  error Std ABI is not supported for this processor!
#endif
asm void USB_NMI_clr_int_stat_shadow(uint_8 bit_num)
{
    /* use atomic instruction to clear bit in USB_INT_STAT */
    bclr.b d0, usb_int_stat_shadow
    rts
}

#if   __REGABI__
    __declspec(register_abi)
#elif __STDABI__
#  error Std ABI is not supported for this processor!
#endif
asm void USB_NMI_set_int_enb(uint_8 bit_num)
{
    /* use atomic instruction to set bit in USB_INT_ENB */
    bset.b d0, USB_INT_ENB
    rts
}

#if   __REGABI__
    __declspec(register_abi)
#elif __STDABI__
#  error Std ABI is not supported for this processor!
#endif
asm void USB_NMI_clr_int_enb(uint_8 bit_num)
{
    /* use atomic instruction to clear bit */
    bclr.b d0, USB_INT_ENB
    rts
}

interrupt void USB_NMI_Handler(void)
{
    volatile uint_8 int_stat_read;

    /* Here, we will defer NMI USB request to the maskable level 6 interrupt */

    /* Read INT_STAT register from USB module */
    int_stat_read = (* (uint_8 *) USB_ISTAT) & (* (uint_8 *) USB_INTEN);

    /* First exception in flags: before clearing TOK_DNE flag, STAT register must be read to shadow variable.
    ** Additionally, we must postpone next TOK_DNE handling while shadow variable was not read,
    ** by disabling TOK_DNE interrupts (they will be enabled in the USB controller driver code.
    */
    if (int_stat_read & USB_ISTAT_TOKDNE_MASK) {
        usb_stat_shadow = * (uint_8 *) USB_STAT;
        * (uint_8 *) USB_INT_STAT &= ~USB_ISTAT_TOKDNE_MASK;
    }
    
    /* Second exception in flags: ATTACH event in host occurs whenever device IS attached (not WAS attached)
    ** that means this is not positive edge interrupt, but high level interrupt. To prevent the interrupt to be called
    ** only once, we disable ATTACH interrupts from now on (USB controller driver can re-enable it)
    */
    if (int_stat_read & )
        * (uint_8 *) USB_INT_ENB &= ~USBG_ISTAT_ATTACH_MASK;

    /* Clear NMI interrupt sources, that invoked this interrupt, by writing to USB_INT_STAT register. */
    * (uint_8 *) USB_INT_STAT = int_stat_read;

    /* We will force interrupt leve 6 only in the case that new interrupt, which was not handled, occured */
    if (int_stat_read & ~usb_int_stat_shadow)
    {
        /* Force interrupt level 6 request by writing a constant to INT_SFRC register */
        * (uint_8 *) INT_SFRC = INT_SFRC_L6;
        /* and add flags about new unhandled interrupts. Note, that int_stat_read is already masked with USB_INT_ENB */
        usb_int_stat_shadow |= int_stat_read;
    }
}
#endif

/* EOF */

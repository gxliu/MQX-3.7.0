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
* $FileName: gpio_init.c$
* $Version : 3.6.16.0$
* $Date    : Dec-3-2010$
*
* Comments:
*
*   This file contains board-specific pin initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "serl_mcf54xx.h"
#include "rtc.h"
#include "mcf54xx_rtc.h"

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_serial_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to serial
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_serial_io_init(uint_8 dev_num) {
    VMCF5445_GPIO_STRUCT_PTR gpio = &((VMCF5445_STRUCT_PTR)_PSP_GET_IPSBAR())->GPIO;
    
    switch (dev_num) {
        case 0:
            gpio->PAR_UART |= MCF5445_GPIO_PAR_UART_U0RXD | MCF5445_GPIO_PAR_UART_U0TXD
#if BSPCFG_ENABLE_TTYA_HW_SIGNALS
                           |  MCF5445_GPIO_PAR_UART_U0CTS | MCF5445_GPIO_PAR_UART_U0RTS
#endif
                           ;
            break;
        case 1:
            gpio->PAR_UART |= MCF5445_GPIO_PAR_UART_U1RXD | MCF5445_GPIO_PAR_UART_U1TXD
#if BSPCFG_ENABLE_TTYB_HW_SIGNALS
                           |  MCF5445_GPIO_PAR_UART_U1CTS | MCF5445_GPIO_PAR_UART_U1RTS
#endif
                           ;
            break;
        default:
            return -1;
    }
    
    return 0;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_usb_io_init
* Returned Value   : none
* Comments         :
*    This function performs BSP-specific initialization related to USB
*
*END*----------------------------------------------------------------------*/
void _bsp_usb_io_init
(
    usb_interface_t port
)
{
    VMCF5445_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    if (port == USB_CONNECTOR_STANDARD) 
    {
        // enable power supply for usb port    
        reg_ptr->GPIO.PAR_USB = MCF5445_GPIO_PAR_USB_VBUSOC_VBUSOC | MCF5445_GPIO_PAR_USB_VBUSEN_VBUSEN;

        // switch to usb external clock - USBCLKIN
        reg_ptr->CCM.MISCCR &= ~MCF54XX_CCM_MISCCR_USBSRC;
        reg_ptr->GPIO.PAR_DMA |= MCF5445_GPIO_PAR_DMA_DREQ1_USB_CLKIN;
    }
    else if (port == USB_CONNECTOR_ULPI) 
    {
        reg_ptr->CCM.MISCCR &= ~MCF54XX_CCM_MISCCR_USBSRC;  // set clock source

        reg_ptr->GPIO.PAR_DMA &= ~(MCF5445_GPIO_PAR_DMA_DREQ1(3) | MCF5445_GPIO_PAR_DMA_DACK1(3));
        reg_ptr->GPIO.PAR_DMA |=  (MCF5445_GPIO_PAR_DMA_DREQ1_USB_CLKIN | MCF5445_GPIO_PAR_DMA_DACK1_ULPI);
    
        reg_ptr->GPIO.PAR_FEC &= MCF5445_GPIO_PAR_FEC_FEC0(7);
        reg_ptr->GPIO.PAR_FEC |= MCF5445_GPIO_PAR_FEC_FEC0_ULPI_GPIO;

        reg_ptr->GPIO.PAR_USB &= ~(MCF5445_GPIO_PAR_USB_VBUSOC(3) | MCF5445_GPIO_PAR_USB_VBUSEN(3));
        reg_ptr->GPIO.PAR_USB |=  (MCF5445_GPIO_PAR_USB_VBUSOC_ULPI_STP | MCF5445_GPIO_PAR_USB_VBUSEN_ULPI_NXT);
        
        reg_ptr->USBOTG.PORTSC1 &= ~(MCF5XXX_USBOTG_PORTSC1_PTS); // MCF5XXX_USBOTG_PORTSC1_PSPD is readonly
        reg_ptr->USBOTG.PORTSC1 |= (MCF5XXX_USBOTG_PORTSC1_PTS_ULPI); // MCF5XXX_USBOTG_PORTSC1_PSPD_HS is readonly
    }
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_rtc_io_init
* Returned Value   : none
* Comments         :
*    This function performs BSP-specific initialization related to RTC
*
*END*----------------------------------------------------------------------*/
void _bsp_rtc_io_init 
(
    void
)
{
    VMCF54XX_RTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();
    rtc->RTC_GOCU = BSP_RTC_PRESCALER_GOCU;
    rtc->RTC_GOCU = BSP_RTC_PRESCALER_GOCU;     // according to RTC register write protocol - 2x
    rtc->RTC_GOCL = BSP_RTC_PRESCALER_GOCL;
    rtc->RTC_GOCL = BSP_RTC_PRESCALER_GOCL;     // according to RTC register write protocol - 2x
    _rtc_init (RTC_INIT_FLAG_ENABLE);
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_enet_io_init
* Returned Value   : none
* Comments         :
*    This function performs BSP-specific initialization related to ENET
*
*END*----------------------------------------------------------------------*/
void _bsp_enet_io_init 
(
    uint_32 device
) 
{
    VMCF5445_STRUCT_PTR ptr;

    if (device < BSP_ENET_DEVICE_COUNT) {
        ptr = _PSP_GET_IPSBAR();
    
        ptr->GPIO.PAR_FECI2C |= MCF5445_GPIO_PAR_FECI2C_MDC0_MDC0 | MCF5445_GPIO_PAR_FECI2C_MDIO0;
    
        // TODO (FIXME) resolve pin setting conflict between FEC0 and ULPI, FEC1 and ATA

        if (device == 0)
            ptr->GPIO.PAR_FEC = (ptr->GPIO.PAR_FEC & ~MCF5445_GPIO_PAR_FEC_FEC0(7)) | MCF5445_GPIO_PAR_FEC_FEC0_RMII_GPIO;
        else
            ptr->GPIO.PAR_FEC = (ptr->GPIO.PAR_FEC & ~MCF5445_GPIO_PAR_FEC_FEC1(7)) | MCF5445_GPIO_PAR_FEC_FEC1_RMII_GPIO;
    }    
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_i2c_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to I2C
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_i2c_io_init
(
    uint_8 dev_num
)
{
    VMCF5445_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_FECI2C |= 0x000F;
            break;
        default:
            return -1;
    }
    return 0;
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_spi_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to SPI
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_dspi_io_init
(
    uint_8 dev_num
)
{
    VMCF5445_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_DSPI |= 0x17;
            break;
        default:
            return -1;
    }
    
    return 0;
} /* Endbody */

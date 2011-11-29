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
* $Version : 3.7.21.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains board-specific pin initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "serl_mcf52xx.h"
#include "rtc.h"
#include "mcf52xx_rtc.h"

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_serial_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to serial
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_serial_io_init
(
    uint_8 dev_num
)
{
    VMCF5225_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
    
    switch (dev_num) {
      case 0:
         reg_ptr->GPIO.PUAPAR |= 0
            | MCF5225_GPIO_PUAPAR_TXD0
            | MCF5225_GPIO_PUAPAR_RXD0
#if BSPCFG_ENABLE_TTYA_HW_SIGNALS
            | MCF5225_GPIO_PUAPAR_RTS0
            | MCF5225_GPIO_PUAPAR_CTS0
#endif
            ;
         break;
      case 1:
         reg_ptr->GPIO.PUBPAR |= 0
            | MCF5225_GPIO_PUBPAR_TXD1
            | MCF5225_GPIO_PUBPAR_RXD1
            ;
         break;
      case 2:
         reg_ptr->GPIO.PUCPAR |= 0
            | MCF5225_GPIO_PUCPAR_TXD2
            | MCF5225_GPIO_PUCPAR_RXD2
            ;
         break;
      default:
         return -1;
    } /* Endswitch */

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
    void
)
{
    VMCF5225_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    /* Turn Vbus off before setting pin peripheral mode */
    reg_ptr->GPIO.PORTUA |= MCF5225_GPIO_PORTxP3;

    /* USB_VBUSE as secondary function (Alt1) */
    reg_ptr->GPIO.PUAPAR &= 0x3f;
    reg_ptr->GPIO.DDRUA |= MCF5225_GPIO_DDRx3;
   
    /* USB_VBUSD as secondary function (Alt1) */
    reg_ptr->GPIO.PUAPAR &= 0xcf;
    reg_ptr->GPIO.DDRUA &= ~MCF5225_GPIO_DDRx2;
   
    /* Turn Vbus on */
    reg_ptr->GPIO.PORTUA &= ~MCF5225_GPIO_PORTxP3;
   
    /* Use external PD resistors on D+ (PQSPA6) and D- (PQSPA5) */
    //reg_ptr->GPIO.PQSPAR |= MCF5225_GPIO_PQSPAR_PQSPA5(3) | MCF5225_GPIO_PQSPAR_PQSPA6(3);

    /* Set clock source from internal PLL oscillator */
    reg_ptr->USBOTG.USBCTRL &= ~USB_USBCTRL_CLKSRC_MASK;
    reg_ptr->USBOTG.USBCTRL |= USB_USBCTRL_CLKSRC_OSCCLK;
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
    VMCF5225_CLK_STRUCT_PTR clk = &(((VMCF5225_STRUCT_PTR)_PSP_GET_IPSBAR())->CLK);
    VMCF52XX_RTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();
    clk->RTCCR = MCF5225_CLOCK_RTCCR_EXTALEN | MCF5225_CLOCK_RTCCR_REFS | MCF5225_CLOCK_RTCCR_LPEN | MCF5225_CLOCK_RTCCR_RTCSEL;
    rtc->RTCGOCU = BSP_RTC_PRESCALER_GOCU;
    rtc->RTCGOCU = BSP_RTC_PRESCALER_GOCU;    // according to RTC register write protocol - 2x
    rtc->RTCGOCL = BSP_RTC_PRESCALER_GOCL;
    rtc->RTCGOCL = BSP_RTC_PRESCALER_GOCL;    // according to RTC register write protocol - 2x
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
   VMCF5225_STRUCT_PTR mcf5225_ptr;

   if (device >= BSP_ENET_DEVICE_COUNT) 
      return;

   mcf5225_ptr = _PSP_GET_IPSBAR();
   mcf5225_ptr->GPIO.PNQPAR = 0x880;
   mcf5225_ptr->GPIO.PTIPAR = 0xFF;
   mcf5225_ptr->GPIO.PTJPAR = 0xFF;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_flexcan_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to FLEXCAN
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_flexcan_io_init
(
    uint_8 dev_num
)
{
    VMCF5225_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PUCPAR = (reg_ptr->GPIO.PUCPAR & ~0x03) | 0x02;
            reg_ptr->GPIO.PUCPAR = (reg_ptr->GPIO.PUCPAR & ~0x0C) | 0x08;
            break;
        default:
            return -1;
    }
    return 0;
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
    VMCF5225_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PASPAR = (reg_ptr->GPIO.PASPAR & ~0x0F) | 0x05;
            break;
        case 1:
            reg_ptr->GPIO.PUCPAR = (reg_ptr->GPIO.PUCPAR & ~0xF0) | 0xA0;
            break;
        default:
            return -1;
    }
    return 0;
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_qspi_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to QSPI
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_qspi_io_init
(
    uint_8 dev_num
)
{
    VMCF5225_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
    
    if (0 != dev_num) return -1;

    reg_ptr->GPIO.PQSPAR &= (~ (MCF5225_GPIO_PQSPAR_PQSPA0(3) | MCF5225_GPIO_PQSPAR_PQSPA1(3) | MCF5225_GPIO_PQSPAR_PQSPA2(3) | MCF5225_GPIO_PQSPAR_PQSPA3(3)));
    reg_ptr->GPIO.PQSPAR |= (MCF5225_GPIO_PQSPAR_PQSPA0(1) | MCF5225_GPIO_PQSPAR_PQSPA1(1) | MCF5225_GPIO_PQSPAR_PQSPA2(1) | MCF5225_GPIO_PQSPAR_PQSPA3(1));

    return 0;
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_adc_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to ADC
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_adc_io_init
(
     /* [IN] number of channel on which to perform hardware initialization */
    _mqx_uint source
)
{
    VMCF5225_GPIO_STRUCT_PTR gpio_ptr = _bsp_get_gpio_base_address();
    VMCF522XX_ADC_STRUCT_PTR adc_ptr = _bsp_get_adc_base_address();

    /* configure GPIO and MUX for ADC */
    switch (source) {
    case ADC_SOURCE_AN0:
        gpio_ptr->PANPAR |= 0x01;
        adc_ptr->CTRL1 &= 0xffef;
        break;
    case ADC_SOURCE_AN1:
        gpio_ptr->PANPAR |= 0x02;
        adc_ptr->CTRL1 &= 0xffef;
        break;
    case ADC_SOURCE_AN2:
        gpio_ptr->PANPAR |= 0x04;
        adc_ptr->CTRL1 &= 0xffdf;
        break;
    case ADC_SOURCE_AN3:
        gpio_ptr->PANPAR |= 0x08;
        adc_ptr->CTRL1 &= 0xffdf;
        break;
    case ADC_SOURCE_AN4:
        gpio_ptr->PANPAR |= 0x10;
        adc_ptr->CTRL1 &= 0xffbf;
        break;
    case ADC_SOURCE_AN5:
        gpio_ptr->PANPAR |= 0x20;
        adc_ptr->CTRL1 &= 0xffbf;
        break;
    case ADC_SOURCE_AN6:
        gpio_ptr->PANPAR |= 0x40;
        adc_ptr->CTRL1 &= 0xff7f;
        break;
    case ADC_SOURCE_AN7:
        gpio_ptr->PANPAR |= 0x80;
        adc_ptr->CTRL1 &= 0xff7f;
        break;
    case ADC_SOURCE_AN0_AN1:
        gpio_ptr->PANPAR |= 0x03;
        adc_ptr->CTRL1 |= 0x0010;
        break;
    case ADC_SOURCE_AN2_AN3:
        gpio_ptr->PANPAR |= 0x0c;
        adc_ptr->CTRL1 |= 0x0020;
        break;
    case ADC_SOURCE_AN4_AN5:
        gpio_ptr->PANPAR |= 0x30;
        adc_ptr->CTRL1 |= 0x0040;
        break;
    case ADC_SOURCE_AN6_AN7:
        gpio_ptr->PANPAR |= 0xc0;
        adc_ptr->CTRL1 |= 0x0080;
        break;
    default:
        return -1;
    }
      
    return 0;
}

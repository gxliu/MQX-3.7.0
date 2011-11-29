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
* $Version : 3.6.15.0$
* $Date    : Dec-3-2010$
*
* Comments:
*
*   This file contains board-specific pin initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "serl_mcf52xx.h"
#include "flexcan.h"
#include "i2c_mcf52xx.h"
#include "adc.h"

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
    VMCF5223_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) 
    {
        case 0:
        reg_ptr->GPIO.PUAPAR = 0
                | MCF5223_GPIO_PUAPAR_TXD0_TXD0 | MCF5223_GPIO_PUAPAR_RXD0_RXD0
#if BSPCFG_ENABLE_TTYA_HW_SIGNALS
                | MCF5223_GPIO_PUAPAR_RTS0_RTS0 | MCF5223_GPIO_PUAPAR_CTS0_CTS0
#endif
                ;
            break;
        case 1:
            reg_ptr->GPIO.PUBPAR = 0
                | MCF5223_GPIO_PUBPAR_TXD1_TXD1 | MCF5223_GPIO_PUBPAR_RXD1_RXD1
#if BSPCFG_ENABLE_TTYB_HW_SIGNALS
                | MCF5223_GPIO_PUBPAR_RTS1_RTS1 | MCF5223_GPIO_PUBPAR_CTS1_CTS1
#endif           
                ;
            break;
        case 2:
            reg_ptr->GPIO.PUCPAR = 0
                | MCF5223_GPIO_PUCPAR_TXD2_TXD2 | MCF5223_GPIO_PUCPAR_RXD2_RXD2
#if BSPCFG_ENABLE_TTYC_HW_SIGNALS
                | MCF5223_GPIO_PUCPAR_RTS2_RTS2 | MCF5223_GPIO_PUCPAR_CTS2_CTS2
#endif
                ;
            break;
        default:
            return -1;
    } /* Endswitch */

    return 0;
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
    VMCF5223_CLK_STRUCT_PTR clk = &(((VMCF5223_STRUCT_PTR)_PSP_GET_IPSBAR())->CLK);
    clk->RTCDR = MCF5223_CLOCK_RTCDR_RTCDF(25000000 - 1);
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
    uint_32 dev_num
) 
{
    VMCF5223_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) 
    {
        case 0:
            reg_ptr->GPIO.PLDPAR = 0x7F;
            break;
        default:
            break;
    }
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
    VMCF5223_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) 
    {
        case 0:
            reg_ptr->GPIO.PASPAR &= (~(MCF5223_GPIO_PASPAR_PASPA2(3) | MCF5223_GPIO_PASPAR_PASPA3(3)));
            reg_ptr->GPIO.PASPAR |= (MCF5223_GPIO_PASPAR_PASPA2(2) | MCF5223_GPIO_PASPAR_PASPA3(2));
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
    VMCF5223_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PASPAR &= (~ (MCF5223_GPIO_PASPAR_PASPA0(3) | MCF5223_GPIO_PASPAR_PASPA1(3)));
            reg_ptr->GPIO.PASPAR |= (MCF5223_GPIO_PASPAR_PASPA0(1) | MCF5223_GPIO_PASPAR_PASPA1(1));
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
    VMCF5223_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
    
    if (0 != dev_num) return -1;

    reg_ptr->GPIO.PQSPAR &= (~ (MCF5223_GPIO_PQSPAR_PQSPA0(3) | MCF5223_GPIO_PQSPAR_PQSPA1(3) | MCF5223_GPIO_PQSPAR_PQSPA2(3) | MCF5223_GPIO_PQSPAR_PQSPA3(3)));
    reg_ptr->GPIO.PQSPAR |= (MCF5223_GPIO_PQSPAR_PQSPA0(1) | MCF5223_GPIO_PQSPAR_PQSPA1(1) | MCF5223_GPIO_PQSPAR_PQSPA2(1) | MCF5223_GPIO_PQSPAR_PQSPA3(1));

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
    VMCF5223_GPIO_STRUCT_PTR gpio_ptr = _bsp_get_gpio_base_address();
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

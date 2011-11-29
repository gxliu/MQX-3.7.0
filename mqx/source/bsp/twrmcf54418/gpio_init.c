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
* $Version : 3.7.28.0$
* $Date    : Feb-11-2011$
*
* Comments:
*
*   This file contains board-specific pin initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "serl_mcf54xx.h"


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_serial_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to serial
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_serial_io_init(uint_8 dev_num) {
    VMCF5441_STRUCT_PTR reg = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();
    
    switch (dev_num) {
        case 0:
            reg->GPIO.PAR_UART0 |= MCF5441_PAD_PAR_UART_U0RXD_U0RXD | MCF5441_PAD_PAR_UART_U0TXD_U0TXD
#if BSPCFG_ENABLE_TTYA_HW_SIGNALS
                                |  MCF5441_PAD_PAR_UART_U0RTS_U0RTS | MCF5441_PAD_PAR_UART_U0CTS_U0CTS
#endif
                                ;
            reg->SCM_PMM.PMM.PPMCR0 = 24;   // clk enable UART0
            break;
        case 2:
            reg->GPIO.PAR_UART2 |= MCF5441_PAD_PAR_UART_U2RXD_U2RXD | MCF5441_PAD_PAR_UART_U2TXD_U2TXD
#if BSPCFG_ENABLE_TTYB_HW_SIGNALS
                                |  MCF5441_PAD_PAR_UART_U2RTS_U2RTS | MCF5441_PAD_PAR_UART_U2CTS_U2CTS
#endif
                                ;
            reg->SCM_PMM.PMM.PPMCR0 = 26;   // clk enable UART2
            break;
        case 4:
            reg->GPIO.PAR_UART0 |= MCF5441_PAD_PAR_UART_U0RTS_U4RXD | MCF5441_PAD_PAR_UART_U0CTS_U4TXD;
            reg->SCM_PMM.PMM.PPMCR1 = 24;   // clk enable UART4
            break;
        case 5:
            reg->GPIO.PAR_UART1 |= MCF5441_PAD_PAR_UART_U1RTS_U5RXD | MCF5441_PAD_PAR_UART_U1CTS_U5TXD;
            reg->SCM_PMM.PMM.PPMCR1 = 25;   // clk enable UART5
            break;
        case 6:
            reg->GPIO.PAR_UART2 |= MCF5441_PAD_PAR_UART_U2RTS_U6RXD | MCF5441_PAD_PAR_UART_U2CTS_U6TXD;
            reg->SCM_PMM.PMM.PPMCR1 = 26;   // clk enable UART6
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
    /* One of port possibilities */
    usb_interface_t port,
    /* use 0 for host, 1 for device and 2 for OTG */
    usb_mode_t      mode
)
{
    VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    if (port == USB_CONNECTOR_STANDARD) 
    {
        /* Configure GPIOD2 as an GPIO, output pin and set to 1 => enable 5V VBUS power */
        reg_ptr->GPIO.PAR_TIMER &= ~MCF5441_GPIO_PAR_TIMER_T3IN;
        reg_ptr->GPIO.PDDR_D |= 0x04;
        reg_ptr->GPIO.PODR_D |= 0x04;

        /* nothing needed more, USB PHY interface is not shared with any lines */
    }
    else if (port == USB_CONNECTOR_ULPI) 
    {
        /* Set PORTG.4 to GPIO function */
        reg_ptr->GPIO.PAR_SIMP0H &= ~MCF5441_GPIO_PAR_SIMP0H_DATA;

        /* Set GPIOG4 as output pin and set the pin to enable ULPI on the QS3VH16233PAG QUICKSWITCH */
        reg_ptr->GPIO.PDDR_G |= 0x10; /* set pin direction */
        reg_ptr->GPIO.PODR_G |= 0x10; /* set pin logical value */

        /* Select Alternate function 2 for T3IN, T0IN
        on T3IN, there is USBO_VBUS_EN/ULPI_DIR at Alt 2
        on T0IN, there is USBO_VBUS_OC/ULPI_NXT at Alt 2 */
        reg_ptr->GPIO.PAR_TIMER &= ~(MCF5441_GPIO_PAR_TIMER_T3IN | MCF5441_GPIO_PAR_TIMER_T0IN);
        reg_ptr->GPIO.PAR_TIMER |= (0x40 | 0x01); /* T3IN as Alternate 2 Function, T0IN as Alternate 2 Function */
        
        /* USB ULPI interface is shared with (R)MII0 and (R)MII1 as well as GPIO */
        /* Enable ULPI_DATA and ULPI_STP */
        reg_ptr->GPIO.PAR_FEC = 0x08;
    }

    if (mode == USB_MODE_HOST) {
        /* Configure external peripheral clock pin for USB_OTG and USB_HOST modules */    
        reg_ptr->GPIO.PAR_IRQ0L &= ~0xC0;
        reg_ptr->GPIO.PAR_IRQ0L |= 0x40;
    }
    else {
        /* Configure external peripheral clock pin for USB_OTG and USB_HOST modules */    
        reg_ptr->GPIO.PAR_IRQ0L &= ~0xC0;
        reg_ptr->GPIO.PAR_IRQ0L |= 0x40;

        /* Select Alternate function 2 for IRQ06, IRQ03, IRQ02.
        on IRQ06 : external peripheral clock pin for USB_OTG and USB_HOST modules 
        on IRQ03 : USB_VUSB_EN
        on IRQ02 : USB_USB_OC */
        reg_ptr->GPIO.PAR_IRQ0L = 0x54;
    }

    /* Set slew rate for GPIO pins */
    reg_ptr->GPIO.SRCR_FEC = 0x0f;
    reg_ptr->GPIO.SRCR_TIMER = 0xc3;
    reg_ptr->GPIO.SRCR_IRQ0 = 0x03;            

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
    
    VMCF5441_STRUCT_PTR ptr = _PSP_GET_IPSBAR();
    
    _rtc_unlock();
    /* Enable Oscillator */
    ptr->RTC.RTC_CFG_DATA = 0x0008;
    /* Set Alarm match to Seconds, minutes, hours, days, months, and year matched */
    ptr->RTC.RTC_CTRL |= 0x0A;

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
    VMCF5441_STRUCT_PTR ptr = _PSP_GET_IPSBAR();

    if (device < BSP_ENET_DEVICE_COUNT) {
        /* RMII on both net */
        ptr->GPIO.PAR_FEC = MCF5441_PAD_PAR_FEC_RMII0_RMII1_FULL;
        ptr->GPIO.SRCR_FEC = 0x0f;
        /* Set GPIOG4 as output pin and clear the pin 
           to enable RMMI1 on the QS3VH16233PAG QUICKSWITCH */
        ptr->GPIO.PDDR_G |= 0x10;
        ptr->GPIO.PODR_G &= ~0x10;
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
    VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            // pin G14, G15   GPIOB1, GPIOB2
            // set pins to SDA0, SCL0
            
            reg_ptr->GPIO.PAR_CANI2C &= ~( 
                PAR_CANI2C_PAR_I2C0_SDA( FC_MASK ) | 
                PAR_CANI2C_PAR_PAR_I2C0_SCL( FC_MASK ) );  
            reg_ptr->GPIO.PAR_CANI2C |= (
                PAR_CANI2C_PAR_I2C0_SDA( I2C0_SDA ) |
                PAR_CANI2C_PAR_PAR_I2C0_SCL( I2C0_SCL )
                );
            reg_ptr->SCM_PMM.PMM.PPMCR0 = 22;   // clk enable I2C0              
            
            //reg_ptr->GPIO.PAR_CANI2C = 0xF0;
            break;
        case 5:
            // pin C9, D9   GPIOF7, GPIOE0
            // set pins to SDA5, SCL5
            reg_ptr->GPIO.PAR_UART1 &= ~(
                PAR_UARTN_PAR_TXD (FC_MASK) | PAR_UARTN_PAR_TXD (FC_MASK));
            reg_ptr->GPIO.PAR_UART1 |= (
                PAR_UARTN_PAR_TXD( ALTERNATE_FC_1_10 ) |
                PAR_UARTN_PAR_RXD( ALTERNATE_FC_1_10 )  
                );
            reg_ptr->SCM_PMM.PMM.PPMCR1 = 7;   // clk enable I2C5
            break;
        default:
            return -1;
    }
    return MQX_OK;
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
    VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_DSPIOWH = 0xFF;
            reg_ptr->SCM_PMM.PMM.PPMCR0 = 23;   // clk enable DSPI0
            break;
        case 1:
            reg_ptr->GPIO.PAR_SDHCH = 0x55;
            reg_ptr->GPIO.PAR_SDHCL = 0x55;
            reg_ptr->SCM_PMM.PMM.PPMCR0 = 15;   // clk enable DSPI1
            break;
        default:
            return -1;
    }
    return 0;
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
    VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 1:
            reg_ptr->GPIO.PAR_CANI2C |= 0x0F;
            reg_ptr->SCM_PMM.PMM.PPMCR0 = 9;   // clk enable CAN1
            break;
        default:
            return -1;
    }
    return 0;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_adc_enable_clock
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function enables clock to ADC peripherial
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_adc_enable_clock()
{
   VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
   
   reg_ptr->SCM_PMM.PMM.PPMCR0 = 37;   // clk enable ADC
   return ( MQX_OK );   
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_adc_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*
*END*----------------------------------------------------------------------*/


_mqx_int _bsp_adc_io_init
(
     /* [IN] number of channel on which to perform hardware initialization */
    _mqx_uint source
)
{
    VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    /* configure GPIO and MUX for ADC */    
    switch (source) {
    case ADC_SOURCE_AN0:
        reg_ptr->ADC.ADC_CR1 &= 0xffef;
        break;
    case ADC_SOURCE_AN1:
        reg_ptr->ADC.ADC_CR1 &= 0xffef;
        break;
    case ADC_SOURCE_AN2:
        reg_ptr->ADC.ADC_CR1 &= 0xffdf;
        break;
    case ADC_SOURCE_AN3:
        reg_ptr->ADC.ADC_CR1 &= 0xffdf;
        break;
    case ADC_SOURCE_AN4:
        reg_ptr->ADC.ADC_CR1 &= 0xffbf;
        break;
    case ADC_SOURCE_AN5:
        reg_ptr->ADC.ADC_CR1 &= 0xffbf;
        break;
    case ADC_SOURCE_AN6:
        reg_ptr->ADC.ADC_CR1 &= 0xff7f;
        break;
    case ADC_SOURCE_AN7:
        reg_ptr->ADC.ADC_CR1 &= 0xff7f;
        break;
    case ADC_SOURCE_AN0_AN1:
        reg_ptr->ADC.ADC_CR1 |= 0x0010;
        break;
    case ADC_SOURCE_AN2_AN3:
        reg_ptr->ADC.ADC_CR1 |= 0x0020;
        break;
    case ADC_SOURCE_AN4_AN5:
        reg_ptr->ADC.ADC_CR1 |= 0x0040;
        break;
    case ADC_SOURCE_AN6_AN7:
        reg_ptr->ADC.ADC_CR1 |= 0x0080;
        break;
    default:
        return -1;
    }

     
    return 0;
}

 
/*FUNCTION*-------------------------------------------------------------------
* Function Name    : _bsp_esdhc_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to ESDHC
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_esdhc_io_init
(
    uint_8 dev_num,
    uint_16 value
)
{
    VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_SDHCH = (uint_8)(value >> 8);
            reg_ptr->GPIO.PAR_SDHCL = (uint_8)value;
            reg_ptr->GPIO.SRCR_SDHC = 0x01;
            reg_ptr->SCM_PMM.PMM.PPMCR0 = 51;   // clk enable ESDHC
            break;
        default:
            return -1;
    }
    return 0;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_flexbus_io_init
* Returned Value   :  none
* Comments         :
*    This function performs BSP-specific initialization FlexBUS 
*    signals for compact flash card or MRAM
*
*END*----------------------------------------------------------------------*/
void _bsp_flexbus_io_init (void)
{
   VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
   /* Enable FlexBUS CS (used by external MRAM and CPLD) */
   reg_ptr->GPIO.PAR_CS |= 0x01;   /* enable CS0 operation for MRAM or CPLD */
   reg_ptr->GPIO.PAR_FBCTL &= (~ (MCF5441_GPIO_PAR_FBCTL_FBCLK));
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_dtimer_gpio_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs DMA Timer BSP-specific initialization.
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_dtimer_gpio_init
(
    uint_8 dev_num
)
{
    VMCF5441_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    reg_ptr->CCM.MISCCR3 &= ~(1 << 12); /* MAC0 1588 timebase counter */
    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_TIMER &= ~MCF5441_GPIO_PAR_TIMER_T0IN;
            reg_ptr->GPIO.PAR_TIMER |= 0x02;
            reg_ptr->SCM_PMM.PMM.PPMCR0 = 28;
            break;
        case 1:
            reg_ptr->GPIO.PAR_TIMER &= ~MCF5441_GPIO_PAR_TIMER_T1IN;
            reg_ptr->GPIO.PAR_TIMER |= 0x08;
            reg_ptr->SCM_PMM.PMM.PPMCR0 = 29;
            break;
        case 2:
            reg_ptr->GPIO.PAR_TIMER &= ~MCF5441_GPIO_PAR_TIMER_T2IN;
            reg_ptr->GPIO.PAR_TIMER |= 0x20;
            reg_ptr->SCM_PMM.PMM.PPMCR0 = 30;
            break;
        case 3:
            reg_ptr->GPIO.PAR_TIMER &= ~MCF5441_GPIO_PAR_TIMER_T3IN;
            reg_ptr->GPIO.PAR_TIMER |= 0x80;
            reg_ptr->SCM_PMM.PMM.PPMCR0 = 31;
            break;
        default:
            return -1;
    }
    return MQX_OK;
} /* Endbody */

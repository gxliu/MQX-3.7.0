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
* $FileName: gpio_init.c$
* $Version : 3.6.12.0$
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
#include "i2c_mcf52xx.h"
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
    VMCF5227_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
    
    switch (dev_num) {
        case 0:
           reg_ptr->GPIO.PAR_UART |= MCF5227_GPIO_PAR_UART_U0TXD_U0TXD | MCF5227_GPIO_PAR_UART_U0RXD_U0RXD
#if BSPCFG_ENABLE_TTYA_HW_SIGNALS
                                  |  MCF5227_GPIO_PAR_UART_U0RTS_U0RTS | MCF5227_GPIO_PAR_UART_U0CTS_U0CTS
#endif                                     
                                  ;
           break;
        case 1:
           reg_ptr->GPIO.PAR_UART |= MCF5227_GPIO_PAR_UART_U1TXD_U1TXD | MCF5227_GPIO_PAR_UART_U1RXD_U1RXD
#if BSPCFG_ENABLE_TTYB_HW_SIGNALS
                                  |  MCF5227_GPIO_PAR_UART_U1RTS_U1RTS | MCF5227_GPIO_PAR_UART_U1CTS_U1CTS
#endif                                     
                                  ;
           break;
        case 2:
           reg_ptr->GPIO.PAR_DSPI |= MCF5227_GPIO_PAR_DSPI_SIN_U2RXD | MCF5227_GPIO_PAR_DSPI_SOUT_U2TXD
                                  ;
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
    VMCF5227_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:         
            /* mask with old values not needed, all bits are set */
            reg_ptr->GPIO.PAR_I2C = MCF5227_GPIO_PAR_SDA_I2C | MCF5227_GPIO_PAR_SCL_I2C;
            break;
        default:
            return -1;
    }
    return 0;
} /* Endbody */

/*FUNCTION****************************************************************
* 
* Function Name    : _bsp_rtc_io_init
* Returned Value   : none
* Comments         :
*    This function sets up the RTC clk source register and prescaler.
*
*END*********************************************************************/
void _bsp_rtc_io_init 
(
    void
)
{
    VMCF5227_CCM_STRUCT_PTR ccm = &(((VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR())->CCM);
    VMCF52XX_RTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();
    ccm->MISCCR &= (~ MCF5227_CCM_MISCCR_RTCSRC);
    rtc->RTCGOCU = BSP_RTC_PRESCALER_GOCU;
    rtc->RTCGOCU = BSP_RTC_PRESCALER_GOCU;       // according to RTC register write protocol - 2x
    rtc->RTCGOCL = BSP_RTC_PRESCALER_GOCL;
    rtc->RTCGOCL = BSP_RTC_PRESCALER_GOCL;       // according to RTC register write protocol - 2x
    _rtc_init (RTC_INIT_FLAG_ENABLE);
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
    VMCF5227_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    // setup gpio state, func and directions
    
    // USB_VBUS_OC
    reg_ptr->GPIO.PAR_UART = (reg_ptr->GPIO.PAR_UART & ~MCF5227_GPIO_PAR_UART_U0RTS_U0RTS) | MCF5227_GPIO_PAR_UART_U0RTS_USBVBOC;
}

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
    VMCF5227_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_DSPI |= 0xFF;   // DSPI signals + CS0 signal
            reg_ptr->GPIO.PAR_TIMER &= 0xCF;
            reg_ptr->GPIO.PAR_TIMER |= 0x10;  // DSPI CS2 signal
            break;
        default:
            return -1;
    }
    
    return 0;
} /* Endbody */


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
    VMCF5227_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_I2C = 0x0A;
            break;
        default:
            return -1;
    }
    return 0;
}

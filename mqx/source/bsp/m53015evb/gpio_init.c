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
* $Version : 3.6.3.0$
* $Date    : Dec-3-2010$
*
* Comments:
*
*   This file contains board-specific pin initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "serl_mcf53xx.h"
#include "rtc.h"
#include "mcf53xx_rtc.h"

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
{ /* Body */
    VMCF5301_GPIO_STRUCT_PTR gpio = &((VMCF5301_STRUCT_PTR)_PSP_GET_IPSBAR())->GPIO;
     
    switch (dev_num) {
        case 0:
            gpio->PAR_UART   |= MCF5301_GPIO_PAR_UART_U0RXD 
                             |  MCF5301_GPIO_PAR_UART_U0TXD
#if BSPCFG_ENABLE_TTYA_HW_SIGNALS
                             |  MCF5301_GPIO_PAR_UART_U0CTS_U0CTS
                             |  MCF5301_GPIO_PAR_UART_U0RTS_U0RTS
#endif
                             ;
            break;
        case 1:  
            gpio->PAR_SSIH   |= MCF5301_GPIO_PAR_SSIH_U1RXD
                             |  MCF5301_GPIO_PAR_SSIH_U1TXD
#if BSPCFG_ENABLE_TTYB_HW_SIGNALS
                             |  MCF5301_GPIO_PAR_SSIH_U1RTS;
                             
            gpio->PAR_SSIL   |= MCF5301_GPIO_PAR_SSIL_U1CTS
#endif
                             ;
            break;
        case 2:
            gpio->PAR_UART   |= MCF5301_GPIO_PAR_UART_U2RXD 
                             |  MCF5301_GPIO_PAR_UART_U2TXD
                             ;
            break;
        default:
            return -1;
    }
    
    return 0;
} /* Endbody */

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
{ /* Body */
    VMCF5301_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    if (port == USB_CONNECTOR_STANDARD) 
    {
        
        reg_ptr->GPIO.PAR_DSPIL |= MCF5301_GPIO_PAR_DSPIL_PCS3;
     
    }   
    else if (port == USB_CONNECTOR_OTG) 
    {
       
        reg_ptr->GPIO.PAR_UART = (reg_ptr->GPIO.PAR_UART & ~MCF5301_GPIO_PAR_UART_U0CTS_U0CTS) 
		                        | MCF5301_GPIO_PAR_UART_U0CTS_USBO_VBUS_EN;
	  
        
        /* switch to usb clock  */ 
        reg_ptr->CCM.MISCCR |= MCF53XX_CCM_MISCCR_USBSRC | MCF53XX_CCM_MISCCR_USBPUE;
    	reg_ptr->CCM.UOCSR     |= MCF53XX_CCM_UOCSR_XPDE;
    			 
    }
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_rtc_io_init
* Returned Value   : none
* Comments         :
* This function performs BSP-specific initialization related to RTC
*
*END*----------------------------------------------------------------------*/
void _bsp_rtc_io_init 
(
    void
)
{ /* Body */

   VMCF53XX_RTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();  	
   
   rtc->RTC_OCEN = ENABLE_CLOCK_32KHZ;
   rtc->RTC_GOC  = RTC_OSC_32KHZ;
   rtc->RTC_GOC  = RTC_OSC_32KHZ;
   _rtc_init (RTC_INIT_FLAG_ENABLE);
   
} /* Endbody */

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
{ /* Body */
    VMCF5301_STRUCT_PTR ptr;

    if (device < BSP_ENET_DEVICE_COUNT) {
        ptr = _PSP_GET_IPSBAR();      
	   
	  ptr-> CCM.MISCCR |= MCF53XX_CCM_MISCCR_FECM ;
        
     if (device == 0) {      
           ptr->GPIO.PAR_FECI2C |= MCF5301_GPIO_PAR_FECI2C_RMII0_MDC | MCF5301_GPIO_PAR_FECI2C_RMII0_MDIO;     
           ptr->GPIO.PAR_FEC    |= (MCF5301_GPIO_PAR_FEC_RMII0 | MCF5301_GPIO_PAR_FEC_7WIRE0 );  	    
     } else {      
           ptr->GPIO.PAR_FECI2C |= MCF5301_GPIO_PAR_FECI2C_RMII1_MDC | MCF5301_GPIO_PAR_FECI2C_RMII1_MDIO;
           ptr->GPIO.PAR_FEC    |= (MCF5301_GPIO_PAR_FEC_RMII1|MCF5301_GPIO_PAR_FEC_7WIRE1);
     }
    
    }
} /* Endbody */


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
{ /* Body */
    VMCF5301_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_FECI2C |= MCF5301_GPIO_PAR_FECI2C_SCL_SCL    /* Enable SCL,SDA pins */
                                     |  MCF5301_GPIO_PAR_FECI2C_SDA_SDA ;  
            break;
        default:
            return -1;
    }
    return 0;
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_dspi_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to SPI
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_dspi_io_init
(
    uint_8 dev_num
)
{ /* Body */
    VMCF5301_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_DSPIH |= 0xFF;   /* Enable sck,sout */
            
            break;
        default:
            return -1;
    }
    
    return 0;
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
* Function Name    : _bsp_esdhc_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
* This function performs BSP-specific initialization related to ESDHC
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_esdhc_io_init
(
	uint_8 dev_num,
	uint_16 value
)
{ /* Body */
    VMCF5301_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
    	case 0:
    		reg_ptr->GPIO.PAR_SDHC  = (uint_8)(value & 0x3F);        /* Control function of SDHC pin */
    		reg_ptr->GPIO.SRCR_SDHC = 0x01;                          /* Control slew rate of some pins on SDHC  */
			reg_ptr->SCM_B.PPMCR0   = 51;   		                     /* clk enable ESDHC */
			break;
    	default:
    		return -1;
    }
    return 0;

} /* Endbody */

/* EOF */

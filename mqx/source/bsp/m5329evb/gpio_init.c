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
* $Version : 3.7.4.0$
* $Date    : Feb-7-2011$
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
    VMCF5329_GPIO_STRUCT_PTR gpio = &((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->GPIO;
    
    switch (dev_num) {
        case 0:
            gpio->PAR_UART   |= MCF5329_GPIO_PAR_UART_UTXD0 | MCF5329_GPIO_PAR_UART_URXD0
#if BSPCFG_ENABLE_TTYA_HW_SIGNALS
                             |  MCF5329_GPIO_PAR_UART_URTS0 | MCF5329_GPIO_PAR_UART_UCTS0
#endif
                             ;
            break;
        case 1:  
            gpio->PAR_UART   |= MCF5329_GPIO_PAR_UART_UTXD1 | MCF5329_GPIO_PAR_UART_URXD1
#if BSPCFG_ENABLE_TTYB_HW_SIGNALS
                             |  MCF5329_GPIO_PAR_UART_URTS1_URTS1 | MCF5329_GPIO_PAR_UART_UCTS1_UCTS1
#endif
                             ;
            break;
        case 2:
            gpio->PAR_SSI    |=MCF5329_GPIO_PAR_SSI_RXD_U2RXD 
                             | MCF5329_GPIO_PAR_SSI_TXD_U2TXD;                           
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
 
   VMCF5329_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
   /* Setup Chip Select 1 */
   if(port==USB_CONNECTOR_OTG ||port==USB_CONNECTOR_HOST){
      
   	reg_ptr->FB[1].CSAR = MCF5XXX_FBCS_CSAR_BA(BSP_LATCH_ADDRESS);
   	reg_ptr->FB[1].CSCR = MCF5XXX_FBCS_CSCR_ASET(2)
                          | MCF5XXX_FBCS_CSCR_WS(0x0D)
                          | MCF5XXX_FBCS_CSCR_AA       /* internal ack */
                          | MCF5XXX_FBCS_CSCR_SBM
                          | MCF5XXX_FBCS_CSCR_RDAH(2)
                          | MCF5XXX_FBCS_CSCR_WRAH(2)
                          | MCF5XXX_FBCS_CSCR_PS_16;   /* data bus width 16 bits */
   	
   	reg_ptr->FB[1].CSMR = MCF5XXX_FBCS_CSMR_BAM_2M   /* 2MB data mask */
                          | MCF5XXX_FBCS_CSMR_V;       /* cs1 is valid 0x001F0001; */

      /* Initialize latch */	
      reg_ptr->GPIO.PAR_TIMER =   0x00;
      reg_ptr->GPIO.PDDR_TIMER =  0x08;
      reg_ptr->GPIO.PCLRR_TIMER = 0x00;
      /* Enable Latch - USB device and host */
      BSP_LATCH_DATA = (uint_32)0xFE;
      
     /* switch usb clock to pll clock */ 
      reg_ptr->CCM.MISCCR |= MCF5329_CLOCK_MISCCR_USBSRC| MCF5329_CLOCK_MISCCR_USBDIV;
    
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
   rtc->RTC_CR |= RTC_ENABLE|(rtc->RTC_CR & ~RTC_XTL);
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


_mqx_int _bsp_enet_io_init 
(
    uint_32 device
) 
{ /* Body */
    VMCF5329_STRUCT_PTR ptr;

    if (device > BSP_ENET_DEVICE_COUNT)
	   return -1;
    if (device == 0) {
        ptr = _PSP_GET_IPSBAR();      
        ptr->GPIO.PAR_FECI2C |= MCF5329_GPIO_PAR_FECI2C_MDC_EMDC | MCF5329_GPIO_PAR_FECI2C_MDIO_EMDIO;     
        ptr->GPIO.PAR_FEC    |= MCF5329_GPIO_PAR_FEC_7W_FEC	     | MCF5329_GPIO_PAR_FEC_MII_FEC;  	    
        return 0;    	
    } 
    else {
        return -1; 
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
    VMCF5329_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_FECI2C |= MCF5329_GPIO_PAR_FECI2C_SCL_I2C_SCL    
                                     |  MCF5329_GPIO_PAR_FECI2C_SDA_I2C_SDA ;  
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
_mqx_int _bsp_qspi_io_init
(
    uint_8 dev_num
)
{ /* Body */
  
   VMCF5329_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
            reg_ptr->GPIO.PAR_QSPI |= MCF5329_GPIO_PAR_QSPI_SCK | MCF5329_GPIO_PAR_QSPI_DOUT
                                   |  MCF5329_GPIO_PAR_QSPI_DIN | MCF5329_GPIO_PAR_QSPI_PCS0;
            
            break;
        default:
            return -1;
    }

    return 0;
   
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_setup_flexbus_for_pccard
* Returned Value   : 
* Comments         :
*    Setup flexbus for pccard operation
*
*END*----------------------------------------------------------------------*/
void _bsp_flexbus_pccard_setup (const uint_32 base_address)
{
    VMCF5329_GPIO_STRUCT_PTR gpio = &((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->GPIO;
    MCF5XXX_FB_STRUCT_PTR fbcs = (MCF5XXX_FB_STRUCT_PTR)((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->FB;
     
    gpio->PAR_CS |=  MCF5329_GPIO_PAR_CS_PAR_CS1;
    
    gpio->PAR_CS &= ~MCF5329_GPIO_PAR_CS_PAR_CS1;
    gpio->PDDR_CS = 0x3E;
    gpio->PODR_CS = 0x00;
    gpio->PPDSDR_CS = 0x00;
    
    fbcs[1].CSAR =  MCF5XXX_FBCS_CSAR_BA(base_address);

    fbcs[1].CSCR =  MCF5XXX_FBCS_CSCR_ASET(2)
                  | MCF5XXX_FBCS_CSCR_WS(0x0D) 
                  | MCF5XXX_FBCS_CSCR_AA       
                  | MCF5XXX_FBCS_CSCR_SBM
                  | MCF5XXX_FBCS_CSCR_RDAH(2)
                  | MCF5XXX_FBCS_CSCR_WRAH(2)
                  | MCF5XXX_FBCS_CSCR_PS_16;   /* data bus width 16 bits */

    fbcs[1].CSMR = MCF5XXX_FBCS_CSMR_BAM_512M  /* 512MB data mask */
                  |MCF5XXX_FBCS_CSMR_V;        /* cs1 is valid */

} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_nand_flash_io_init
* Returned Value   : 
* Comments         :
*    This function performs BSP-specific initialization related to NANDFLASH
*
*END*----------------------------------------------------------------------*/
void _bsp_nand_flash_io_init (const uint_32 base_address)
{ /* Body */

   VMCF5329_GPIO_STRUCT_PTR gpio = &((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->GPIO;
   MCF5XXX_FB_STRUCT_PTR fbcs = (MCF5XXX_FB_STRUCT_PTR)((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->FB;
     
   gpio->PAR_CS |= MCF5329_GPIO_PAR_CS_PAR_CS2;
    
   fbcs[2].CSAR = MCF5XXX_FBCS_CSAR_BA(NAND_FLASH_ADDRESS);

   fbcs[2].CSCR = MCF5XXX_FBCS_CSCR_ASET(2)
                | MCF5XXX_FBCS_CSCR_WS(0x13) /* wait states */
                | MCF5XXX_FBCS_CSCR_AA       /* internal ack */
                | MCF5XXX_FBCS_CSCR_SBM
                | MCF5XXX_FBCS_CSCR_RDAH(2)
                | MCF5XXX_FBCS_CSCR_WRAH(2)
                | MCF5XXX_FBCS_CSCR_PS_8;    /* data bus width 8 bits */

    fbcs[2].CSMR = MCF5XXX_FBCS_CSMR_BAM_16M /* 64 KB data mask */
                  |MCF5XXX_FBCS_CSMR_V;      /* cs1 is valid */
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
{ /* Body */
    VMCF5329_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
    	case 0:
	      reg_ptr->GPIO.PAR_FECI2C |=MCF5329_GPIO_PAR_FECI2C_SDA_I2C_CANTX
	                               | MCF5329_GPIO_PAR_FECI2C_SDA_I2C_CANRX  ;
			break;
    	default:
    		return -1;
    }
    return 0;
} /* Endbody */

/* EOF */

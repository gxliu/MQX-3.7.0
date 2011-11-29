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
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains board-specific pin initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "serl_mcf51xx.h"
#include "i2c_mcf51xx.h"

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
    uint_8 channel
)
{
    VMCF51JE_STRUCT_PTR reg_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;

    /* Setup GPIO for SCI0 ,SCI1 and SCI2 */
    switch (channel) {
        /* sci on TWR-SER board */  
        case MCF51XX_SCI0:
            /* SCI port to PTD6, PTD7 pins */ 
            reg_ptr->SIM.SOPT3 |= MCF51XX_SOPT3_SCI1PS_MASK;
            /* starting SGI clock */
            reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_SCI1_MASK;
        break;
        
        case MCF51XX_SCI1:
            /* SCI function */ 
            /* starting SGI clock */
            reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_SCI2_MASK;    
        break;
        
        default:
            return IO_ERROR;
        break;
    } /* Endswitch */    
    
    return IO_OK;
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
    VMCF51JE_STRUCT_PTR reg_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;
    
    /* Enable USB module clocking */
    reg_ptr->SIM.SCGC2 |= MCF51XX_SCGC2_USB_MASK;  
    
    /* Set clock source from internal PLL oscillator */
    reg_ptr->USBOTG.USBCTRL &= ~USB_USBCTRL_CLKSRC_MASK;
    reg_ptr->USBOTG.USBCTRL |= USB_USBCTRL_CLKSRC_OSCCLK;

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
    VMCF51JE_STRUCT_PTR reg_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;

    switch (dev_num) {
        case 0:
           reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_IIC1_MASK;
        break;
        default:
            return IO_ERROR;
    }
    return IO_OK;
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
    VMCF51JE_STRUCT_PTR mcf51je_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;    

    /* Enable I/O control */
    if (source <= ADC_SOURCE_AD7)    {
        mcf51je_ptr->ADCX.APCTL1 |= (1 << source);
    } else if (source <= ADC_SOURCE_AD15) {
        mcf51je_ptr->ADCX.APCTL2 |= (1 << (source - 8));
    } else if (source <= ADC_SOURCE_AD23) {
        mcf51je_ptr->ADCX.APCTL3 |= (1 << (source - 16));
    } else if (source <= ADC_SOURCE_VREFL){
        mcf51je_ptr->ADCX.APCTL4 |= (1 << (source - 24));
    } else {
        return IO_ERROR; 
    }
    
    return IO_OK;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_adc_io_deinit
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific deinitialization related to ADC
*
*END*----------------------------------------------------------------------*/

_mqx_int _bsp_adc_io_deinit
(
     /* [IN] number of channel on which to perform hardware deinitialization */
    _mqx_uint source
)
{
    VMCF51JE_STRUCT_PTR mcf51je_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;    

    /* Disable I/O control */
    if (source <= ADC_SOURCE_AD7)    {
        mcf51je_ptr->ADCX.APCTL1 &= ~(1 << source);
    } else if (source <= ADC_SOURCE_AD15) {
        mcf51je_ptr->ADCX.APCTL2 &= ~(1 << (source - 8));
    } else if (source <= ADC_SOURCE_AD23) {
        mcf51je_ptr->ADCX.APCTL3 &= ~(1 << (source - 16));
    } else if (source <= ADC_SOURCE_VREFL){
        mcf51je_ptr->ADCX.APCTL4 &= ~(1 << (source - 24));
    } else {
        return IO_ERROR; 
    }

    return IO_OK;
}



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_spi_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to SPI
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_spi_io_init
(
      uint_8 dev_num
) 
{ /* Body */
   
    VMCF51JE_STRUCT_PTR reg_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;
   
    switch (dev_num) 
    {
      case 0:
        /* select gpio pin as spi function*/
        //PTG0 --> SPSCK1
        //PTF7 --> MISO1
        //PTF6 --> MOSI1
        //PTA0 --> SSB1
        /* enable clock gate of spi1 */
        reg_ptr->SIM.SCGC2 |= MCF51XX_SCGC2_SPI1_MASK;
        break;
      case 1:
        /* select gpio pin as spi function*/
        //PTC2 --> SPSCK2
        //PTC1 --> MISO2
        //PTC0 --> MOSI2
        //PTC3 --> SSB2
        /* enable clock gate of spi2 */
        reg_ptr->SIM.SCGC2 |= MCF51XX_SCGC2_SPI2_MASK;
        break;
      default:
        return IO_ERROR;
    }
    return IO_OK;
} /* Endbody */


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
    _rtc_init (RTC_INIT_FLAG_RESET | RTC_INIT_FLAG_ENABLE);

}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_flexbus_io_init
* Returned Value   :  none
* Comments         :
*    This function performs BSP-specific initialization Mini FlexBUS 
*    signals for compact flash card or MRAM
*
*END*----------------------------------------------------------------------*/

void  _bsp_flexbus_io_init(void) 
{
   
   VMCF51JE_STRUCT_PTR reg_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;

   /* enable clock to flexBus */ 
   reg_ptr->SIM.SCGC2 |= MCF51XX_SCGC2_MFB_MASK;    
   
   /* enable flexBus pin functionality */
   reg_ptr->SIMX.MFBPC1 = 0xFF;
   reg_ptr->SIMX.MFBPC2 = 0xFF;
   reg_ptr->SIMX.MFBPC3 = 0xFF;
   reg_ptr->SIMX.MFBPC4 = 0xFF;
   
}
/* EOF */
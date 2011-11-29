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
* $Version : 3.7.7.0$
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
#include "rtc.h"

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
  VMCF51JM_STRUCT_PTR reg_ptr = (VMCF51JM_STRUCT_PTR)BSP_IPSBAR;

  /* Setup GPIO for SCI0 ,SCI1 and SCI2 */
  switch (channel) {
    case MCF51XX_SCI0:
      /* SCI function */
      /* starting SGI clock */
      reg_ptr->SIMX.SCGC1 |= MCF51XX_SCGC1_SCI1_MASK;
    break;
    case MCF51XX_SCI1:
      /* SCI function */
      /* starting SGI clock */
      reg_ptr->SIMX.SCGC1 |= MCF51XX_SCGC1_SCI2_MASK;   
    break;
    default:
      return -1;
    break;
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
    VMCF51JM_STRUCT_PTR reg_ptr = (VMCF51JM_STRUCT_PTR)BSP_IPSBAR;

    /* Enable USB module clocking */
    reg_ptr->SIMX.SCGC2 |= MCF51XX_SCGC2_USB_MASK;  
    
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
  _rtc_init (RTC_INIT_FLAG_CLEAR | RTC_INIT_FLAG_RESET | RTC_INIT_FLAG_ENABLE);
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
    VMCF51JM_STRUCT_PTR reg_ptr = (VMCF51JM_STRUCT_PTR)BSP_IPSBAR;

    switch (dev_num) {
        case 0:
           reg_ptr->SIMX.SCGC1 |= MCF51XX_SCGC1_IIC1_MASK;
        break;
        case 1:
           reg_ptr->SIMX.SCGC1 |= MCF51XX_SCGC1_IIC2_MASK;
        break;
        default:
            return -1;
    }
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
    VMCF51JM_STRUCT_PTR mcf51jm_ptr = (VMCF51JM_STRUCT_PTR)BSP_IPSBAR;    
    _mqx_int rshift;
    _mqx_int bshift;
    uint_16_ptr reg = NULL;
    
    if (source > 11)
        return -1;
    return 0;
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
   
    VMCF51JM_STRUCT_PTR reg_ptr = (VMCF51JM_STRUCT_PTR)BSP_IPSBAR;
   
    switch (dev_num) {
      case 0:
        /* select gpio pin as spi function*/
        //PTC7 --> SPSCK1
        //PTC6 --> MISO1
        //PTC5 --> MOSI1
        //PTC4 --> SSB1
        /* enable clock gate of spi1 */
        reg_ptr->SIMX.SCGC2 |= 0x01;
        break;
      case 1:
        /* select gpio pin as spi function*/
        //PTD7 --> SPSCK2
        //PTE0 --> MISO2
        //PTE1 --> MOSI2
        //PTE2 --> SSB2
        /* enable clock gate of spi2 */
        reg_ptr->SIMX.SCGC2 |= 0x02;
        break;
      default:
        return -1;
    }
    return 0;
} /* Endbody */

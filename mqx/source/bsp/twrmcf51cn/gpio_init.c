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
* $Version : 3.6.12.0$
* $Date    : Jun-4-2010$
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
  VMCF51CN_STRUCT_PTR reg_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;

  /* Setup GPIO for SCI0 ,SCI1 and SCI2 */
  switch (channel) {
    case MCF51XX_SCI0:
      /* SCI function */
      reg_ptr->GPIO.PTDPF &= ~(MCF51XX_PTXPF_X0_MASK | MCF51XX_PTXPF_X1_MASK);
      reg_ptr->GPIO.PTDPF |= (MCF51XX_PTDPF_X0_TXD1 | MCF51XX_PTDPF_X1_RXD1);
      /* starting SGI clock */
      reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_SCI1_MASK;
    break;
    case MCF51XX_SCI1:
      /* SCI function */
      reg_ptr->GPIO.PTDPF &= ~(MCF51XX_PTXPF_X2_MASK | MCF51XX_PTXPF_X3_MASK);
      reg_ptr->GPIO.PTDPF |= (MCF51XX_PTDPF_X2_TXD2 | MCF51XX_PTDPF_X3_RXD2);
      /* starting SGI clock */
      reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_SCI2_MASK;    
    break;
    case MCF51XX_SCI2:
      /* SCI function */
      //next command is not needed, no bit is needed to clear in fact
      //        reg_ptr->GPIO.PTEPF &= ~(MCF51XX_PTXPF_X6_MASK | MCF51XX_PTXPF_X7_MASK);
      reg_ptr->GPIO.PTEPF |= (MCF51XX_PTEPF_X6_TXD3 | MCF51XX_PTEPF_X7_RXD3);
      /* starting SGI clock */
      reg_ptr->SIM.SCGC2 |= MCF51XX_SCGC2_SCI3_MASK;    
    break;
    default:
      return -1;
    break;
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
  _rtc_init (RTC_INIT_FLAG_CLEAR | RTC_INIT_FLAG_RESET | RTC_INIT_FLAG_ENABLE);
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
   VMCF51CN_STRUCT_PTR mcf51cn_ptr =(VMCF51CN_STRUCT_PTR)BSP_IPSBAR;
    
   mcf51cn_ptr->GPIO.PTAPF &= ~MCF51XX_PTDPA_MII_MASK;
   mcf51cn_ptr->GPIO.PTAPF |=  MCF51XX_PTDPA_MII_SIGNALS; // PHYCLK, MDIO, MDC RXD3-0,  RX_DV 
   mcf51cn_ptr->GPIO.PTBPF &= ~MCF51XX_PTDPB_MII_MASK;
   mcf51cn_ptr->GPIO.PTBPF |=  MCF51XX_PTDPB_MII_SIGNALS; // RX_CLK, RX_ER, TX_ER, TX_CLK, TX_EN, TXD0-2
   mcf51cn_ptr->GPIO.PTCPF &= ~MCF51XX_PTDPC_MII_MASK;
   mcf51cn_ptr->GPIO.PTCPF |=  MCF51XX_PTDPC_MII_SIGNALS; // TD3, MII_COL, MII_CRS

   mcf51cn_ptr->GPIO.PTADS = 0x6;
   mcf51cn_ptr->GPIO.PTBDS = 0xf4;
   mcf51cn_ptr->GPIO.PTCDS |= 0x1;

   mcf51cn_ptr->GPIO.PTAIFE = 0x06;
   mcf51cn_ptr->GPIO.PTBIFE = 0xf4;
   mcf51cn_ptr->GPIO.PTCIFE |= 1;

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
    VMCF51CN_STRUCT_PTR reg_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;

    switch (dev_num) {
        case 0:
           reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_IIC1_MASK;
            reg_ptr->GPIO.PTGPF |= 0xF0;
        break;
        case 1:
           reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_IIC2_MASK;
           reg_ptr->GPIO.PTCPF &= (~ 0xF000);
           reg_ptr->GPIO.PTCPF |= 0x5000;
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
*    This function performs BSP-specific initialization related to ADC
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_adc_io_init
(
     /* [IN] number of channel on which to perform hardware initialization */
    _mqx_uint source
)
{
    VMCF51CN_STRUCT_PTR mcf51cn_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;
    VMCF51CN_GPIO_STRUCT_PTR gpio_ptr = _bsp_get_gpio_base_address();
    _mqx_int rshift;
    _mqx_int bshift;
    uint_16_ptr reg;
    
    if (source > 11)
        return -1;
    
    if (source > 4) {
        rshift = (11 - source + 4) / 8;
        bshift = (11 - source + 4) % 8;
        
        reg = ((uint_16_ptr)&gpio_ptr->PTCPF) + rshift;
    } 
    else {
        rshift = (3 - source + 7) / 8;
        bshift = (3 - source + 7) % 8;
        
        reg = ((uint_16_ptr)&gpio_ptr->PTDPF) + rshift;
    }
    
    *reg |= (3 << (bshift * 2));
    
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
   
    VMCF51CN_STRUCT_PTR reg_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;
   
    switch (dev_num) {
      case 0:
        /* select gpio pin as spi function*/
        //PTC7 --> SPSCK1
        //PTC6 --> MISO1
        //PTC5 --> MOSI1
        //PTC4 --> SSB1
        reg_ptr->GPIO.PTCPF &= (~ 0xFF00);
        reg_ptr->GPIO.PTCPF |= 0xAA00;
        /* enable clock gate of spi1 */
        reg_ptr->SIM.SCGC2 |= 0x01;
        break;
      case 1:
        /* select gpio pin as spi function*/
        //PTD7 --> SPSCK2
        //PTE0 --> MISO2
        //PTE1 --> MOSI2
        //PTE2 --> SSB2
        reg_ptr->GPIO.PTDPF &= (~ 0xC000);
        reg_ptr->GPIO.PTDPF |= 0x8000;
        reg_ptr->GPIO.PTEPF &= (~ 0x003F);
        reg_ptr->GPIO.PTEPF |= 0x002A;
        /* enable clock gate of spi2 */
        reg_ptr->SIM.SCGC2 |= 0x02;
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
*    This function performs BSP-specific initialization Mini FlexBUS 
*    signals for compact flash card or MRAM
*
*END*----------------------------------------------------------------------*/

void  _bsp_flexbus_io_init(void) 
{
   
    VMCF51CN_STRUCT_PTR reg_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;
    
    reg_ptr->GPIO.PTEPF &= ~MCF51XX_PTEPF_MB_MUX_MASK;
    reg_ptr->GPIO.PTEPF |= MCF51XX_PTEPF_MB_MUX_SIGNALS;
    reg_ptr->GPIO.PTFPF &= ~MCF51XX_PTFPF_MB_MUX_MASK;
    reg_ptr->GPIO.PTFPF |= MCF51XX_PTFPF_MB_MUX_SIGNALS;
    reg_ptr->GPIO.PTGPF &= ~MCF51XX_PTGPF_MB_MUX_MASK;
    reg_ptr->GPIO.PTGPF |= MCF51XX_PTGPF_MB_MUX_SIGNALS;
    reg_ptr->GPIO.PTHPF &= ~MCF51XX_PTHPF_MB_MUX_MASK;
    reg_ptr->GPIO.PTHPF |= MCF51XX_PTHPF_MB_MUX_SIGNALS;
    reg_ptr->GPIO.PTJPF &= ~MCF51XX_PTJPF_MB_MUX_MASK;
    reg_ptr->GPIO.PTJPF |= MCF51XX_PTJPF_MB_MUX_SIGNALS;

    reg_ptr->SIM.SCGC4 |= MCF51XX_SCGC4_MB_MASK; /* enable clock to flexBus */    
}
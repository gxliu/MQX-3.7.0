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
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains board-specific pin initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>

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
  VMCF51AC_STRUCT_PTR reg_ptr = (VMCF51AC_STRUCT_PTR)BSP_IPSBAR;

  /* Setup GPIO for SCI0 ,SCI1 and SCI2 */
  switch (channel) {
    case MCF51XX_SCI0:
      /* SCI function */
      /* starting SGI clock */
      reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_SCI1_MASK;
    break;
    case MCF51XX_SCI1:
      /* SCI function */
      /* starting SGI clock */
      reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_SCI2_MASK;    
    break;
    default:
      return -1;
    break;
  } /* Endswitch */    
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
    VMCF51AC_STRUCT_PTR reg_ptr = (VMCF51AC_STRUCT_PTR)BSP_IPSBAR;

    switch (dev_num) {
        case 0:
           reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_IIC_MASK;
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
    VMCF51AC_STRUCT_PTR mcf51ac_ptr = (VMCF51AC_STRUCT_PTR)BSP_IPSBAR;    
    _mqx_int rshift;
    _mqx_int bshift;
    uint_16_ptr reg = NULL;
    
    if (source > ADC_SOURCE_AN30)
    {
      return -1; 
    } 
    
    /* Enable BUS clock to ADC module */
    mcf51ac_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_ADC_MASK;   
    
    /* Enable I/O control */
    if (source <= ADC_SOURCE_AN7)    {
        mcf51ac_ptr->ADC.APCTL1 |= (1 << source);
    } else if (source <= ADC_SOURCE_AN15) {
        mcf51ac_ptr->ADC.APCTL2 |= (1 << (source >> 8));
    } else if (source <= ADC_SOURCE_AN23) {
        mcf51ac_ptr->ADC.APCTL3 |= (1 << (source >> 16));        
    } 
    
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
   
    VMCF51AC_STRUCT_PTR reg_ptr = (VMCF51AC_STRUCT_PTR)BSP_IPSBAR;
   
    switch (dev_num) {
      case 0:
        /* select gpio pin as spi function*/
        //PTC7 --> SPSCK1
        //PTC6 --> MISO1
        //PTC5 --> MOSI1
        //PTC4 --> SSB1
        /* enable clock gate of spi1 */
        reg_ptr->SIM.SCGC2 |= MCF51XX_SCGC2_SPI1_MASK;
        break;
      case 1:
        /* select gpio pin as spi function*/
        //PTD7 --> SPSCK2
        //PTE0 --> MISO2
        //PTE1 --> MOSI2
        //PTE2 --> SSB2
        /* enable clock gate of spi2 */
        reg_ptr->SIM.SCGC2 |= MCF51XX_SCGC2_SPI2_MASK;
        break;
      default:
        return -1;
    }
    return 0;
} /* Endbody */

/* EOF */
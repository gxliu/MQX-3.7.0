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
* $Version : 3.6.7.0$
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
  VMCF51EM_STRUCT_PTR reg_ptr = (VMCF51EM_STRUCT_PTR)BSP_IPSBAR;


  /* Setup GPIO for SCI0 ,SCI1 and SCI2 */
  switch (channel) {
    case MCF51XX_SCI0:
      
      /* SCI function */
      reg_ptr->GPIO.PTBPF |=  (MCF51EM_PTBPF_B2_RX1 | MCF51EM_PTBPF_B3_TX1);
      
      /* starting SGI clock */
      reg_ptr->SIM.SCGC1 |= MCF51EM_SCGC1_SCI1_MASK;
    break;
    case MCF51XX_SCI1:
      /* SCI function */

#define MCF51EM_TX2_ON_PTB0   true

    #if MCF51EM_TX2_ON_PTB0 == true      
      /* RX2 is muxed on PTB0, TX2 is muxed on PTB1 */
      reg_ptr->GPIO.PTBPF &= ~(MCF51EM_PTBPF_B0_MASK | MCF51EM_PTBPF_B1_MASK);
      reg_ptr->GPIO.PTBPF |=  (MCF51EM_PTBPF_B0_RX2  | MCF51EM_PTBPF_B1_TX2);
      
    #else
      
      /* RX2 is muxed on PTB0  */
      reg_ptr->GPIO.PTBPF &= ~(MCF51EM_PTBPF_B0_MASK);
      reg_ptr->GPIO.PTBPF |=  (MCF51EM_PTBPF_B0_RX2);   /* RX2 pin */
      
      /* TX2 is muxed on PTE6  */
      reg_ptr->GPIO.PTBPF &= ~(MCF51EM_PTBPF_B0_MASK);  /* RX2 pin */
      reg_ptr->GPIO.PTEPF |=  (MCF51EM_PTEPF_E6_TX2);   /* TX2 pin */
    #endif  
      
      /* starting SGI clock */
      reg_ptr->SIM.SCGC1 |= MCF51EM_SCGC1_SCI2_MASK;
    break;
    case MCF51XX_SCI2:
      /* SCI function */

#define MCF51EM_TX3_ON_PTC0   true

      #if MCF51EM_TX3_ON_PTC0 == true 
      /* RX3 is muxed on PTC0, TX3 is muxed on PTC1 */
      reg_ptr->GPIO.PTFPF &= ~(MCF51EM_PTFPF_F2_RX3 | MCF51EM_PTFPF_F3_TX3);
      reg_ptr->GPIO.PTCPF |=  (MCF51EM_PTCPF_C0_RX3 | MCF51EM_PTCPF_C1_TX3);
      #else
      /* RX3 is muxed on PTF2, TX3 is muxed on PTF3 */
      reg_ptr->GPIO.PTCPF &= ~(MCF51EM_PTCPF_C0_RX3 | MCF51EM_PTCPF_C1_TX3);
      reg_ptr->GPIO.PTFPF |=  (MCF51EM_PTFPF_F2_RX3 | MCF51EM_PTFPF_F3_TX3);
      #endif                               
      
      /* starting SGI clock */
      reg_ptr->SIM.SCGC1 |= MCF51EM_SCGC1_SCI3_MASK;    
    break;
    default:
      return -1;
    break;
  } /* Endswitch */    


  return MQX_OK;
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
    _rtc_int_install( _rtc_isr );
    _rtc_init (RTC_INIT_FLAG_RESET | RTC_INIT_FLAG_ENABLE);
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
   VMCF51EM_STRUCT_PTR reg_ptr = (VMCF51EM_STRUCT_PTR)BSP_IPSBAR;

   switch (dev_num) {
      case 0:
         /* Set pin multiplexer for IIC module */
         reg_ptr->GPIO.PTBPF &= ~(MCF51EM_PTBPF_B4_MASK | MCF51EM_PTBPF_B5_MASK);
         reg_ptr->GPIO.PTBPF |=  (MCF51EM_PTBPF_B4_SCL  | MCF51EM_PTBPF_B5_SDA);
         
         /* Enable Bus clock for IIC module */
         reg_ptr->SIM.SCGC1  |= MCF51EM_SCGC1_IIC_MASK;
         break;
      default:
         return -1;
   }
   return MQX_OK;
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

    VMCF51EM_STRUCT_PTR reg_ptr = (VMCF51EM_STRUCT_PTR)BSP_IPSBAR;

    uint_16     adc_channel = ADC_GET_CHANNEL(source);

    switch (adc_channel)
    {
        case 8:
            reg_ptr->GPIO.PTEPF &= ~MCF51EM_PTEPF_E0_MASK;
            reg_ptr->GPIO.PTEPF |=  MCF51EM_PTEPF_E0_AD8;
        break;
        
        case 9:
            reg_ptr->GPIO.PTEPF &= ~MCF51EM_PTEPF_E1_MASK;
            reg_ptr->GPIO.PTEPF |=  MCF51EM_PTEPF_E1_AD9;
        break;
        
        case 10:
            reg_ptr->GPIO.PTAPF &= ~MCF51EM_PTAPF_A2_MASK;
            reg_ptr->GPIO.PTAPF |=  MCF51EM_PTAPF_A2_AD10;
        break;
        
        case 11:
            reg_ptr->GPIO.PTAPF &= ~MCF51EM_PTAPF_A5_MASK;
            reg_ptr->GPIO.PTAPF |=  MCF51EM_PTAPF_A5_AD11;
        break;
        
        case 12:
            reg_ptr->GPIO.PTAPF &= ~MCF51EM_PTAPF_A6_MASK;
            reg_ptr->GPIO.PTAPF |=  MCF51EM_PTAPF_A6_AD12;
        break;
        
        case 13:
            reg_ptr->GPIO.PTAPF &= ~MCF51EM_PTAPF_A7_MASK;
            reg_ptr->GPIO.PTAPF |=  MCF51EM_PTAPF_A7_AD13;
        break;
        
        case 14:
            reg_ptr->GPIO.PTBPF &= ~MCF51EM_PTBPF_B6_MASK;
            reg_ptr->GPIO.PTBPF |=  MCF51EM_PTBPF_B6_AD14;
        break;
        
        case 15:
            reg_ptr->GPIO.PTBPF &= ~MCF51EM_PTBPF_B7_MASK;
            reg_ptr->GPIO.PTBPF |=  MCF51EM_PTBPF_B7_AD15;
        break;
        
        case 16:
            reg_ptr->GPIO.PTFPF &= ~MCF51EM_PTFPF_F4_MASK;
            reg_ptr->GPIO.PTFPF |=  MCF51EM_PTFPF_F4_AD16;
        break;
        
        case 17:
            reg_ptr->GPIO.PTFPF &= ~MCF51EM_PTFPF_F5_MASK;
            reg_ptr->GPIO.PTFPF |=  MCF51EM_PTFPF_F5_AD17;
        break;
        
        case 18:
            reg_ptr->GPIO.PTFPF &= ~MCF51EM_PTFPF_F6_MASK;
            reg_ptr->GPIO.PTFPF |=  MCF51EM_PTFPF_F6_AD18;
        break;
        
        case 19:
            reg_ptr->GPIO.PTFPF &= ~MCF51EM_PTFPF_F7_MASK;
            reg_ptr->GPIO.PTFPF |=  MCF51EM_PTFPF_F7_AD19;
        break;
    }

    return MQX_OK;
}




/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_lcd_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to LCD
*
*END*----------------------------------------------------------------------*/

_mqx_int _bsp_lcd_io_init
(
    void
)
{

    VMCF51EM_STRUCT_PTR reg_ptr = (VMCF51EM_STRUCT_PTR)BSP_IPSBAR;
    
    /* Set pin multiplexer for LCD functionality (MC51EM256 reference manual page 48) */
    /* LCD[0:4] --> shared with PTC[3:7] */
    reg_ptr->GPIO.PTCPF &= ~( MCF51EM_PTCPF_C3_MASK  | \
                              MCF51EM_PTCPF_C4_MASK  | \
                              MCF51EM_PTCPF_C5_MASK  | \
                              MCF51EM_PTCPF_C6_MASK  | \
                              MCF51EM_PTCPF_C7_MASK);

    reg_ptr->GPIO.PTCPF |=  ( MCF51EM_PTCPF_C3_LCD0  | \
                              MCF51EM_PTCPF_C4_LCD1  | \
                              MCF51EM_PTCPF_C5_LCD2  | \
                              MCF51EM_PTCPF_C6_LCD3  | \
                              MCF51EM_PTCPF_C7_LCD4);

    /* LCD5 --> shared with PTE7 */    
    reg_ptr->GPIO.PTEPF &= ~( MCF51EM_PTEPF_E7_MASK);
    reg_ptr->GPIO.PTEPF |=  ( MCF51EM_PTEPF_E7_LCD5);


    /* LCD[6:9] --> shared with SPI2 */
    reg_ptr->GPIO.LCDPF &= ~( MCF51EM_LCDPF_LCD6_MASK | \
                              MCF51EM_LCDPF_LCD7_MASK | \
                              MCF51EM_LCDPF_LCD8_MASK | \
                              MCF51EM_LCDPF_LCD9_MASK);


    reg_ptr->GPIO.LCDPF |=  ( MCF51EM_LCDPF_LCD6_LCD6 | \
                              MCF51EM_LCDPF_LCD7_LCD7 | \
                              MCF51EM_LCDPF_LCD8_LCD8 | \
                              MCF51EM_LCDPF_LCD9_LCD9);

    /* LCD[10:26] are dedicated just for LCD */
    
    /* LCD[27:34] --> shared with PTD[0:7]   */
    reg_ptr->GPIO.PTDPF &= ~( MCF51EM_PTDPF_D0_MASK  | \
                              MCF51EM_PTDPF_D1_MASK  | \
                              MCF51EM_PTDPF_D2_MASK  | \
                              MCF51EM_PTDPF_D3_MASK  | \
                              MCF51EM_PTDPF_D4_MASK  | \
                              MCF51EM_PTDPF_D5_MASK  | \
                              MCF51EM_PTDPF_D6_MASK  | \
                              MCF51EM_PTDPF_D7_MASK);

    reg_ptr->GPIO.PTDPF |=  ( MCF51EM_PTDPF_D0_LCD27 | \
                              MCF51EM_PTDPF_D1_LCD28 | \
                              MCF51EM_PTDPF_D2_LCD29 | \
                              MCF51EM_PTDPF_D3_LCD30 | \
                              MCF51EM_PTDPF_D4_LCD31 | \
                              MCF51EM_PTDPF_D5_LCD32 | \
                              MCF51EM_PTDPF_D6_LCD33 | \
                              MCF51EM_PTDPF_D7_LCD34);

    /* LCD35 */    
    reg_ptr->GPIO.LCDPF &= ~( MCF51EM_LCDPF_LCD35_MASK);
    reg_ptr->GPIO.LCDPF |=  ( MCF51EM_LCDPF_LCD35_LCD35);
    
    /* LCD[36:43] --> shared with PTF[0:7] */
    reg_ptr->GPIO.PTFPF &= ~( MCF51EM_PTFPF_F0_MASK  | \
                              MCF51EM_PTFPF_F1_MASK  | \
                              MCF51EM_PTFPF_F2_MASK  | \
                              MCF51EM_PTFPF_F3_MASK  | \
                              MCF51EM_PTFPF_F4_MASK  | \
                              MCF51EM_PTFPF_F5_MASK  | \
                              MCF51EM_PTFPF_F6_MASK  | \
                              MCF51EM_PTFPF_F7_MASK);

    reg_ptr->GPIO.PTFPF |=  ( MCF51EM_PTFPF_F0_LCD36 | \
                              MCF51EM_PTFPF_F1_LCD37 | \
                              MCF51EM_PTFPF_F2_LCD38 | \
                              MCF51EM_PTFPF_F3_LCD39 | \
                              MCF51EM_PTFPF_F4_LCD40 | \
                              MCF51EM_PTFPF_F5_LCD41 | \
                              MCF51EM_PTFPF_F6_LCD42 | \
                              MCF51EM_PTFPF_F7_LCD43);
    
    
    /* Enable Bus clock to LCD module */
    reg_ptr->SIM.SCGC2 = MCF51EM_SCGC2_LCD_MASK;
    
    return MQX_OK;
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
   
    VMCF51EM_STRUCT_PTR reg_ptr = (VMCF51EM_STRUCT_PTR)BSP_IPSBAR;
   
    switch (dev_num) {
        case 0:
            /* select gpio pin as SPI function*/
            /* PTA1 --> MOSI1
             * PTA2 --> MISO1
             * PTA3 --> SCLK1
             * PTA4 --> SSB1 
             */
            reg_ptr->GPIO.PTAPF &= ~( MCF51EM_PTAPF_A1_MASK  | \
                                      MCF51EM_PTAPF_A2_MASK  | \
                                      MCF51EM_PTAPF_A3_MASK  | \
                                      MCF51EM_PTAPF_A4_MASK);
            
            reg_ptr->GPIO.PTAPF |=  ( MCF51EM_PTAPF_A1_MOSI1 | \
                                      MCF51EM_PTAPF_A2_MISO1 | \
                                      MCF51EM_PTAPF_A3_SCLK1 | \
                                      MCF51EM_PTAPF_A4_PTA4);
           
            /* enable clock gate of SPI1 */
            reg_ptr->SIM.SCGC2  |= MCF51EM_SCGC2_SPI1_MASK;

            break;
        case 1:
            /* select lcd pin as spi function */
            /* LCD6 --> MOSI2
             * LCD7 --> MISO2
             * LCD8 --> SCLK2
             * LCD9 --> SSB2 
             */
             reg_ptr->GPIO.LCDPF &= ~( MCF51EM_LCDPF_LCD6_MASK  | \
                                       MCF51EM_LCDPF_LCD7_MASK  | \
                                       MCF51EM_LCDPF_LCD8_MASK  | \
                                       MCF51EM_LCDPF_LCD9_MASK);
            
            reg_ptr->GPIO.LCDPF  |=  ( MCF51EM_LCDPF_LCD6_MOSI2 | \
                                       MCF51EM_LCDPF_LCD7_MISO2 | \
                                       MCF51EM_LCDPF_LCD8_SCLK2 | \
                                       MCF51EM_LCDPF_LCD9_SSB2);

            /* enable clock gate of spi2 */
            reg_ptr->SIM.SCGC2  |= MCF51EM_SCGC2_SPI2_MASK;
            break;
      
      case 2:
            /* select gpio pin as SPI function */
            /* PTE3 --> MOSI3
             * PTE4 --> MISO3
             * PTE5 --> SCLK3
             * PTE6 --> SSB3 
             */
            reg_ptr->GPIO.PTEPF &= ~( MCF51EM_PTEPF_E3_MASK  | \
                                      MCF51EM_PTEPF_E4_MASK  | \
                                      MCF51EM_PTEPF_E5_MASK  | \
                                      MCF51EM_PTEPF_E6_MASK);
 
 
            reg_ptr->GPIO.PTEPF |=  ( MCF51EM_PTEPF_E3_MOSI3 | \
                                      MCF51EM_PTEPF_E4_MISO3 | \
                                      MCF51EM_PTEPF_E5_SCLK3 | \
                                      MCF51EM_PTEPF_E6_PTE6);

           
            /* enable clock gate of SPI1 */
            reg_ptr->SIM.SCGC2  |= MCF51EM_SCGC2_SPI3_MASK;            
      default:
            return -1;
    }
    return 0;
} /* Endbody */

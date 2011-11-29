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
* $Version : 3.7.4.0$
* $Date    : Feb-22-2011$
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
     VMCF5208_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();
    
    switch (dev_num) {
        case 0:
           /* UART0 in default pins */
               reg_ptr->GPIO.PAR_UART |= MCF5208_GPIO_PAR_UART_PAR_U0RXD |
                                         MCF5208_GPIO_PAR_UART_PAR_U0TXD
#if BSPCFG_ENABLE_TTYA_HW_SIGNALS
                                       | MCF5208_GPIO_PAR_UART_PAR_URTS0_URTS0
                                       | MCF5208_GPIO_PAR_UART_PAR_UCTS0_UCTS0
#endif
                                       ;
           break;
        case 1:
           /* UART1 in default pins */
               reg_ptr->GPIO.PAR_UART |= MCF5208_GPIO_PAR_UART_PAR_U1RXD |
                                         MCF5208_GPIO_PAR_UART_PAR_U1TXD
#if BSPCFG_ENABLE_TTYB_HW_SIGNALS
                                       | MCF5208_GPIO_PAR_UART_PAR_URTS1_URTS1
                                       | MCF5208_GPIO_PAR_UART_PAR_UCTS1_UCTS1
#endif
                                       ;
           break;
        case 2:
           /* UART2 in DTIM pins */
               reg_ptr->GPIO.PAR_TIMER |= MCF5208_GPIO_PAR_TIMER_PAR_TIN0_UTXD2 |
                                          MCF5208_GPIO_PAR_TIMER_PAR_TIN1_URXD2 
#if BSPCFG_ENABLE_TTYC_HW_SIGNALS
                                        | MCF5208_GPIO_PAR_TIMER_PAR_TIN2_URTS2
                                        | MCF5208_GPIO_PAR_TIMER_PAR_TIN3_UCTS2
#endif
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
    VMCF5208_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
       case 0:          
            /* mask with old values not needed, all bits are set */
            /* SDA and SCL in default SDA_U2RXD/SCL_U2TXD  */
            reg_ptr->GPIO.PAR_FECI2C = MCF5208_GPIO_PAR_FECI2C_PAR_SDA_SDA | MCF5208_GPIO_PAR_FECI2C_PAR_SCL_SCL;
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
*    This function performs BSP-specific initialization related to SPI
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_qspi_io_init
(
      uint_8 dev_num
)
{
    VMCF5208_STRUCT_PTR reg_ptr = _PSP_GET_IPSBAR();

    switch (dev_num) {
        case 0:
          /* QSPI signals + CS2 used as GPIO  */
               reg_ptr->GPIO.PAR_QSPI = MCF5208_GPIO_PAR_QSPI_PAR_SCK_SCK |
                                        MCF5208_GPIO_PAR_QSPI_PAR_DOUT_DOUT |
                                        MCF5208_GPIO_PAR_QSPI_PAR_DIN_DIN;
         /* CS0 and CS1 in U0CTS/U1CTS  */
             reg_ptr->GPIO.PAR_UART &= 0xF3CF; 
             reg_ptr->GPIO.PAR_UART |= MCF5208_GPIO_PAR_UART_PAR_UCTS1_PCS1 |
                                       MCF5208_GPIO_PAR_UART_PAR_UCTS0_PCS0; 
            break;
         default:
            return -1;
    }
    
    return 0;
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
    uint_32  device
) 
{
   VMCF5208_STRUCT_PTR mcf5208_ptr;

   if (device >= BSP_ENET_DEVICE_COUNT) 
      return;

   mcf5208_ptr = _PSP_GET_IPSBAR();
   
    /* Enable FEC pins */
        
   mcf5208_ptr->GPIO.PAR_FEC =      MCF5208_GPIO_PAR_FEC_PAR_FEC_7W_FEC |
                                    MCF5208_GPIO_PAR_FEC_PAR_FEC_MII_FEC;
   mcf5208_ptr->GPIO.PAR_FECI2C =   MCF5208_GPIO_PAR_FECI2C_PAR_MDC_EMDC |
                                    MCF5208_GPIO_PAR_FECI2C_PAR_MDIO_EMDIO;
}


/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $Version : 3.7.5.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains board-specific pin initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>


#define FEC_COL         0x00000001
#define FEC_CRS         0x00000002
#define FEC_MDC         0x00000004
#define FEC_MDIO        0x00000008
#define FEC_RX_CLK      0x00000010
#define FEC_RX_DV       0x00000020
#define FEC_RXD3        0x00000040
#define FEC_RXD2        0x00000080
#define FEC_RXD1        0x00000100
#define FEC_RXD0        0x00000200
#define FEC_RX_ER       0x00000400
#define FEC_TX_CLK      0x00000800
#define FEC_TXD3        0x00001000
#define FEC_TXD2        0x00002000
#define FEC_TXD1        0x00004000
#define FEC_TXD0        0x00008000
#define FEC_TX_EN       0x00010000
#define FEC_TX_ER       0x00020000

#define FEC_MII_PINS    0x0003ffff
#define FEC_7WIRE_PINS  (FEC_COL|FEC_RX_CLK|FEC_RX_DV|FEC_RXD0|FEC_TX_CLK|FEC_TXD0|FEC_TX_EN)
#define FEC_RMII_PINS   (FEC_MDC|FEC_MDIO|FEC_RX_DV|FEC_RXD1|FEC_RXD0|FEC_RX_ER|FEC_TX_CLK|FEC_TXD1|FEC_TXD0|FEC_TX_EN)


extern _mqx_int _bsp_sdhc_io_init (uint_8,boolean);

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_diu_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to DIU
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_diu_io_init( void )
{
   MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();

   ioc_ptr->DIU_CLK   = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x2f DIU_CLK pad control register R/W */
   ioc_ptr->DIU_DE    = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x30 DIU_DE pad control register R/W */
   ioc_ptr->DIU_HSYNC = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x31 DIU_HSYNC pad control register R/W */
   ioc_ptr->DIU_VSYNC = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x32 DIU_VSYNC pad control register R/W */
   ioc_ptr->DIU_LD00  = IO_CONTROL_FUNCTION_2|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x33 DIU_LD00 pad control register R/W */
   ioc_ptr->DIU_LD01  = IO_CONTROL_FUNCTION_2|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x34 DIU_LD01 pad control register R/W */
   ioc_ptr->DIU_LD02  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x35 DIU_LD02 pad control register R/W */
   ioc_ptr->DIU_LD03  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x36 DIU_LD03 pad control register R/W */
   ioc_ptr->DIU_LD04  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x37 DIU_LD04 pad control register R/W */
   ioc_ptr->DIU_LD05  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x38 DIU_LD05 pad control register R/W */
   ioc_ptr->DIU_LD06  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x39 DIU_LD06 pad control register R/W */
   ioc_ptr->DIU_LD07  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x3a DIU_LD07 pad control register R/W */
   ioc_ptr->DIU_LD08  = IO_CONTROL_FUNCTION_2|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x3b DIU_LD08 pad control register R/W */
   ioc_ptr->DIU_LD09  = IO_CONTROL_FUNCTION_2|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x3c DIU_LD09 pad control register R/W */
   ioc_ptr->DIU_LD10  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x3d DIU_LD10 pad control register R/W */
   ioc_ptr->DIU_LD11  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x3e DIU_LD11 pad control register R/W */
   ioc_ptr->DIU_LD12  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x3f DIU_LD12 pad control register R/W */
   ioc_ptr->DIU_LD13  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x40 DIU_LD13 pad control register R/W */
   ioc_ptr->DIU_LD14  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x41 DIU_LD14 pad control register R/W */
   ioc_ptr->DIU_LD15  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x42 DIU_LD15 pad control register R/W */
   ioc_ptr->DIU_LD16  = IO_CONTROL_FUNCTION_2|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x43 DIU_LD16 pad control register R/W */
   ioc_ptr->DIU_LD17  = IO_CONTROL_FUNCTION_2|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x44 DIU_LD17 pad control register R/W */
   ioc_ptr->DIU_LD18  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x45 DIU_LD18 pad control register R/W */
   ioc_ptr->DIU_LD19  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x46 DIU_LD19 pad control register R/W */
   ioc_ptr->DIU_LD20  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x47 DIU_LD20 pad control register R/W */
   ioc_ptr->DIU_LD21  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x48 DIU_LD21 pad control register R/W */
   ioc_ptr->DIU_LD22  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x49 DIU_LD22 pad control register R/W */
   ioc_ptr->DIU_LD23  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; /* 0x4a DIU_LD23 pad control register R/W */
   ioc_ptr->GBOBE     = IO_CONTROL_ENABLE;
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_serial_io_init
* Returned Value   : MQX_OK for success, IO_ERROR for failure
* Comments         :
*    This function performs BSP-specific initialization related to serial
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_serial_io_init(uint_8 dev_num)
{
   MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();

   switch (dev_num) {
      case 0:
         #if BSPCFG_PCS0_USES_PSC0
           #if BSPCFG_ENABLE_TTYA_HW_SIGNALS
            ioc_ptr->PSC0_0 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
            ioc_ptr->PSC0_1 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
            ioc_ptr->PSC0_4 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
           #endif
            ioc_ptr->PSC0_2 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
            ioc_ptr->PSC0_3 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
         #elif BSPCFG_PCS0_USES_FEC1
           #if BSPCFG_ENABLE_TTYA_HW_SIGNALS
            ioc_ptr->FEC1_TX_CLK = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;     
            ioc_ptr->FEC1_RX_CLK = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;     
            ioc_ptr->FEC1_COL    = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;
           #endif
            ioc_ptr->FEC1_RX_DV  = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;      
            ioc_ptr->FEC1_TX_EN  = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
         #else
            return IO_ERROR;
         #endif         
         break;
         
      case 1:
         #if BSPCFG_PCS1_USES_PSC1
           #if BSPCFG_ENABLE_TTYB_HW_SIGNALS
            ioc_ptr->PSC1_0 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
            ioc_ptr->PSC1_1 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
            ioc_ptr->PSC1_4 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
           #endif
            ioc_ptr->PSC1_2 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
            ioc_ptr->PSC1_3 = IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;           
         #elif BSPCFG_PCS1_USES_USB1
           #if BSPCFG_ENABLE_TTYB_HW_SIGNALS
            ioc_ptr->USB1_DATA0 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->USB1_DATA1 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->USB1_DATA4 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
           #endif
            ioc_ptr->USB1_DATA2 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->USB1_DATA3 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
         #else
            return IO_ERROR;
         #endif         
         break;
      case 2:
         #if BSPCFG_PCS2_USES_EMB
           #if BSPCFG_ENABLE_TTYC_HW_SIGNALS
            ioc_ptr->EMB_AD15 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->EMB_AD14 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->EMB_AD11 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;  
           #endif
            ioc_ptr->EMB_AD13 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->EMB_AD12 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
         #elif BSPCFG_PCS2_USES_FEC1
           #if BSPCFG_ENABLE_TTYC_HW_SIGNALS
            ioc_ptr->FEC1_TXD_2 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->FEC1_TXD_3 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->FEC1_CRS   = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
           #endif
            ioc_ptr->FEC1_RXD_2 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->FEC1_RXD_3 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
         #else
            return IO_ERROR;
         #endif         
         break;
      case 3:
         #if BSPCFG_PCS3_USES_LPC_EMB
           #if BSPCFG_ENABLE_TTYD_HW_SIGNALS
            ioc_ptr->EMB_AD10 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->EMB_AD09 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->LPC_RWB  = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3; 
           #endif
            ioc_ptr->EMB_AD08 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;      
            ioc_ptr->LPC_OE_B = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;
         #elif BSPCFG_PCS3_USES_FEC1
           #if BSPCFG_ENABLE_TTYD_HW_SIGNALS
            ioc_ptr->FEC1_TX_ER = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->FEC1_RXD_1 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->FEC1_RX_ER = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
           #endif
            ioc_ptr->FEC1_TXD_1 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->FEC1_MDC   = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
         #else
            return IO_ERROR;
         #endif         
         break;
      case 4:
         #if BSPCFG_PCS4_USES_DUI
           #if BSPCFG_ENABLE_TTYE_HW_SIGNALS
            ioc_ptr->DIU_CLK   = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;          
            ioc_ptr->DIU_DE    = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;           
            ioc_ptr->DIU_LD02  = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
           #endif
            ioc_ptr->DIU_HSYNC = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;        
            ioc_ptr->DIU_VSYNC = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
         #elif BSPCFG_PCS4_USES_USB1
           #if BSPCFG_ENABLE_TTYE_HW_SIGNALS
            ioc_ptr->USB1_DATA5 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->USB1_DATA6 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->USB1_CLK   = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;
           #endif
            ioc_ptr->USB1_DATA7 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;       
            ioc_ptr->USB1_STOP  = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;        
         #else
            return IO_ERROR;
         #endif         
         break;
      case 5:
         #if BSPCFG_PCS5_USES_DIU
           #if BSPCFG_ENABLE_TTYF_HW_SIGNALS
            ioc_ptr->DIU_LD03 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD04 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD07 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
           #endif
            ioc_ptr->DIU_LD05 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD06 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
         #elif BSPCFG_PCS5_USES_SDHC1
           #if BSPCFG_ENABLE_TTYF_HW_SIGNALS
            ioc_ptr->SDHC1_CMD;        
            ioc_ptr->SDHC1_D0;         
            ioc_ptr->SDHC1_D3;         
           #endif
            ioc_ptr->SDHC1_D1;         
            ioc_ptr->SDHC1_D2;         
         #else
            return IO_ERROR;
         #endif         
         break;
      case 6:
         #if BSPCFG_PCS6_USES_DIU
           #if BSPCFG_ENABLE_TTYG_HW_SIGNALS
            ioc_ptr->DIU_LD08 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD09 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD12 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
           #endif
            ioc_ptr->DIU_LD10 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD11 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
         #else
            return IO_ERROR;
         #endif         
         break;
      case 7:
         #if BSPCFG_PCS7_USES_DIU
           #if BSPCFG_ENABLE_TTYH_HW_SIGNALS
            ioc_ptr->DIU_LD13 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD14 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD19 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
           #endif
            ioc_ptr->DIU_LD15 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD18 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
         #else
            return IO_ERROR;
         #endif         
         break;
      case 8:
         #if BSPCFG_PCS8_USES_DIU_I2C
           #if BSPCFG_ENABLE_TTYI_HW_SIGNALS
            ioc_ptr->DIU_LD20 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD21 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->I2C2_SCL = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
           #endif
            ioc_ptr->DIU_LD22 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->DIU_LD23 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
         #else
            return IO_ERROR;
         #endif         
         break;
      case 9:
         #if BSPCFG_PCS9_USES_I2C1
            ioc_ptr->I2C1_SCL = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         
            ioc_ptr->I2C1_SDA = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;         

           #if BSPCFG_ENABLE_TTYJ_HW_SIGNALS
            #if BSPCFG_PCS9_USES_I2C2
               ioc_ptr->I2C2_SDA = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;    
            #endif
                             
            #if BSPCFG_PCS9_USES_CAN
               ioc_ptr->CAN1_TX  = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;          
               ioc_ptr->CAN2_TX  = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;          
            #endif
           #endif
         #else
            return IO_ERROR;
         #endif         
         break;
      default:
         return IO_ERROR;
   } 

#if BSPCFG_USB_DEV_GBOBE
      return MQX_OK;
   #else
      ioc_ptr->GBOBE = IO_CONTROL_ENABLE;
#endif
   return MQX_OK;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_usb_io_init
* Returned Value   : none
* Comments         :
*    This function performs BSP-specific initialization related to USB
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_usb_io_init
(
    uint_32 device
)
{

   MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();   
   VMPC5125_STRUCT_PTR  reg_ptr = ((VMPC5125_STRUCT_PTR)MPC5125_GET_IMMR());
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
   
   if (device == USB_CONNECT_ULPI1) {
      ccm_ptr->SCCR2 |= CCM_SCCR2_USB1_EN; // Enable usb_ulpi1 clock 
      ioc_ptr->USB1_DATA0  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN  ; 
      ioc_ptr->USB1_DATA1  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN;    
      ioc_ptr->USB1_DATA2  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN;     
      ioc_ptr->USB1_DATA3  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN;     
      ioc_ptr->USB1_DATA4  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN;       
      ioc_ptr->USB1_DATA5  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN;     
      ioc_ptr->USB1_DATA6  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN;     
      ioc_ptr->USB1_DATA7  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN;     
      ioc_ptr->USB1_STOP   =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3 ;
      ioc_ptr->USB1_CLK    =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      ioc_ptr->USB1_NEXT   =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;      
      ioc_ptr->USB1_DIR    =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;
   }
   else if (device == USB_CONNECT_ULPI2) {
      ccm_ptr->SCCR2 |= CCM_SCCR2_USB2_EN;// Enable usb_ulpi2 clock 
        ioc_ptr->DIU_LD12 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN ;     
        ioc_ptr->DIU_LD13 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN ;
        ioc_ptr->DIU_LD14 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN ;
        ioc_ptr->DIU_LD15 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN ;
        ioc_ptr->DIU_LD18 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN ;
      ioc_ptr->DIU_LD19 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN ;
      ioc_ptr->DIU_LD20 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN ;
      ioc_ptr->DIU_LD21 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3|IO_CONTROL_PULL_DOWN ;
      ioc_ptr->DIU_LD22 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3 ;                         
      ioc_ptr->DIU_LD23 = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3 ;                         
      ioc_ptr->I2C2_SCL = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3 ;
      ioc_ptr->I2C2_SDA = IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3 ;
   }
else {
      return IO_ERROR;
   }

   ioc_ptr->GBOBE = IO_CONTROL_ENABLE;
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
   MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();

   ioc_ptr->GBOBE = IO_CONTROL_ENABLE;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_enet_io_init
* Returned Value   : none
* Comments         :
*    This function performs BSP-specific initialization related to ENET
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_enet_io_init( uint_32 device, uint_32 mode) 
{
   MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();
   uint_32                       pins;
   
   if (mode & ENET_OPTION_7WIRE) {
      pins=FEC_MII_PINS;
   } else if (mode & ENET_OPTION_RMII) {
      pins=FEC_RMII_PINS;
   } else {
      pins=FEC_MII_PINS;
   }
   
   if (device== MPC5125_FEC0) {
      if (pins & FEC_COL)    ioc_ptr->FEC1_COL    =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;       
      if (pins & FEC_CRS)    ioc_ptr->FEC1_CRS    =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;       
      if (pins & FEC_MDC)    ioc_ptr->FEC1_MDC    =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3; 
      if (pins & FEC_MDIO)   ioc_ptr->FEC1_MDIO   =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;      
      if (pins & FEC_RX_CLK) ioc_ptr->FEC1_RX_CLK =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
      if (pins & FEC_RX_DV)  ioc_ptr->FEC1_RX_DV  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RXD3)   ioc_ptr->FEC1_RXD_3  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RXD2)   ioc_ptr->FEC1_RXD_2  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RXD1)   ioc_ptr->FEC1_RXD_1  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RXD0)   ioc_ptr->FEC1_RXD_0  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RX_ER)  ioc_ptr->FEC1_RX_ER  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TX_CLK) ioc_ptr->FEC1_TX_CLK =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
      if (pins & FEC_TXD3)   ioc_ptr->FEC1_TXD_3  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TXD2)   ioc_ptr->FEC1_TXD_2  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
      if (pins & FEC_TXD1)   ioc_ptr->FEC1_TXD_1  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TXD0)   ioc_ptr->FEC1_TXD_0  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TX_EN)  ioc_ptr->FEC1_TX_EN  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TX_ER)  ioc_ptr->FEC1_TX_ER  =  IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;     
   } else if (device== MPC5125_FEC1 ) {
      if (pins & FEC_COL)    ioc_ptr->USB1_DIR    =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;       
      if (pins & FEC_CRS)    ioc_ptr->SDHC1_D2    =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;       
      if (pins & FEC_MDC)    ioc_ptr->USB1_DATA2  =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3; 
      if (pins & FEC_MDIO)   ioc_ptr->USB1_DATA4  =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;      
      if (pins & FEC_RX_CLK) ioc_ptr->USB1_STOP   =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;    
      if (pins & FEC_RX_DV)  ioc_ptr->USB1_CLK    =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RXD3)   ioc_ptr->SDHC1_D1    =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RXD2)   ioc_ptr->SDHC1_D0    =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RXD1)   ioc_ptr->USB1_DATA0  =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RXD0)   ioc_ptr->USB1_DATA5  =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_RX_ER)  ioc_ptr->USB1_DATA3  =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TX_CLK) ioc_ptr->USB1_DATA7  =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;    
      if (pins & FEC_TXD3)   ioc_ptr->SDHC1_CMD   =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TXD2)   ioc_ptr->SDHC1_CLK   =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;    
      if (pins & FEC_TXD1)   ioc_ptr->USB1_DATA1  =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TXD0)   ioc_ptr->USB1_DATA6  =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TX_EN)  ioc_ptr->USB1_NEXT   =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
      if (pins & FEC_TX_ER)  ioc_ptr->SDHC1_D3    =  IO_CONTROL_FUNCTION_2|IO_CONTROL_SLEW_RATE_3;     
   } else {
      return IO_ERROR;
   }
   
   ioc_ptr->GBOBE = IO_CONTROL_ENABLE;
   return MQX_OK;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_mscan_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to FLEXCAN
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_mscan_io_init
(
    uint_8 dev_num
)
{
   MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();

   switch (dev_num) {
      case MPC5125_MSCAN1:
         // NOTE: CAN1_RX is a dedicated pin, so it does not have an IOC register
         #if BSPCFG_MSCAN1_USES_MSCAN1
            ioc_ptr->CAN1_TX  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
         #elif BSPCFG_MSCAN1_USES_PSC0
            ioc_ptr->PSC0_4  = IO_CONTROL_FUNCTION_3|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
         #else
            return IO_ERROR;
         #endif
         break;
         
      case MPC5125_MSCAN2:
         // NOTE: CAN2_RX is a dedicated pin, so it does not have an IOC register
         #if BSPCFG_MSCAN2_USES_MSCAN2
            ioc_ptr->CAN2_TX  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
         #elif BSPCFG_MSCAN2_USES_PSC1
            ioc_ptr->PSC1_0  = IO_CONTROL_FUNCTION_3|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
            return IO_ERROR;
         #endif
         break;
         
      case MPC5125_MSCAN3:
         #if BSPCFG_MSCAN3_USES_DIU
             ioc_ptr->DIU_LD00  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
            ioc_ptr->DIU_LD01  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
         #elif BSPCFG_MSCAN3_USES_I2C1
            ioc_ptr->I2C1_SCL  = IO_CONTROL_FUNCTION_2|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
            ioc_ptr->I2C1_SDA  = IO_CONTROL_FUNCTION_2|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
         #else
            return IO_ERROR;
         #endif
   
         break;
         
      case MPC5125_MSCAN4:
         ioc_ptr->DIU_LD08  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
         ioc_ptr->DIU_LD09  = IO_CONTROL_FUNCTION_0|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3; 
         break;
         
      default:
         return IO_ERROR;
      
   }       
         
   ioc_ptr->GBOBE = IO_CONTROL_ENABLE;
   return MQX_OK;
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
   MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();

   switch (dev_num) {
      case 0:
         // Set for I2C1 SCL and SDA
         ioc_ptr->J1850_TX = IO_CONTROL_FUNCTION_3|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3;
         ioc_ptr->J1850_RX = IO_CONTROL_FUNCTION_3|IO_CONTROL_SCHMITT_ENABLE|IO_CONTROL_SLEW_RATE_3;
         break;
      case 1:
         // Set for I2C2 SCL and SDA ... To be completed
         return IO_ERROR;
         break;
      case 2:
         // Set for I2C3 SCL and SDA ... To be completed
         return IO_ERROR;
         break;
      default:
         return IO_ERROR;
   } 

   ioc_ptr->GBOBE = IO_CONTROL_ENABLE;
   return MQX_OK;
} 



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_spi_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
*    This function performs BSP-specific initialization related to I2C
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_spi_io_init
(
    uint_8 dev_num
)
{
   MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();
   
   _bsp_serial_io_init(dev_num);

#if BSP_SPI_MEMORY_GPIO_CS   
   switch (dev_num) {
      case 0:
         #if BSPCFG_PCS0_USES_PSC0      
            ioc_ptr->PSC0_1 = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3;     /* SPI_SS */  
            /* Set SPI_SS as GPIO out put function */ 
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT1,MPC5125_GPIO_PIN(16),MPC5125_GPIO_OUT_EN,1,0,1);
         #elif BSPCFG_PCS0_USES_FEC1
            ioc_ptr->FEC1_RX_CLK = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3;/* SPI_SS */
            /* Set SPI_SS as GPIO out put function */
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT1,MPC5125_GPIO_PIN(5),MPC5125_GPIO_OUT_EN,1,0,1);
         #else
            return IO_ERROR;
         #endif         
         break;
         
      case 1:
         return IO_ERROR; /* PSC1 can not set SPI_SS as GPIO out put function */
      case 2:
         #if BSPCFG_PCS2_USES_EMB     
            ioc_ptr->EMB_AD14 = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3;   /* SPI_SS */
            /* Set SPI_SS as GPIO out put function */
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT1,MPC5125_GPIO_PIN(22),MPC5125_GPIO_OUT_EN,1,0,1);
         #elif BSPCFG_PCS2_USES_FEC1    
            ioc_ptr->FEC1_TXD_3 = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3; /* SPI_SS */
            /* Set SPI_SS as GPIO out put function */
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT2,MPC5125_GPIO_PIN(20),MPC5125_GPIO_OUT_EN,1,0,1); 
         #else
            return IO_ERROR;
         #endif         
         break;
      case 3:
         #if BSPCFG_PCS3_USES_LPC_EMB
            ioc_ptr->LPC_RWB  = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3;   /* SPI_SS */
            /* Set SPI_SS as GPIO out put function */
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT1,MPC5125_GPIO_PIN(6),MPC5125_GPIO_OUT_EN,1,0,1);      
         #elif BSPCFG_PCS3_USES_FEC1     
            ioc_ptr->FEC1_RXD_1 = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3; /* SPI_SS */
            /* Set SPI_SS as GPIO out put function */
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT2,MPC5125_GPIO_PIN(25),MPC5125_GPIO_OUT_EN,1,0,1);      
         #else
            return IO_ERROR;
         #endif         
         break;
      case 4:
         #if BSPCFG_PCS4_USES_DUI    
            ioc_ptr->DIU_DE    = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3;  /* SPI_SS */
            /* PSC4 can not set SPI_SS as GPIO out put function */       
         #elif BSPCFG_PCS4_USES_USB1      
            ioc_ptr->USB1_DATA6 = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3; /* SPI_SS */
            /* PSC4 can not set SPI_SS as GPIO out put function */
         #else
            return IO_ERROR;
         #endif         
         break;
      case 5:
         #if BSPCFG_PCS5_USES_DIU
            /* This mode PSC5 can not set SPI_SS as GPIO out put function */  
            return IO_ERROR;            
         #elif BSPCFG_PCS5_USES_SDHC1     
            ioc_ptr->SDHC1_D0  = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3; /* SPI_SS */ 
            /* Set SPI_SS as GPIO out put function */
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT1,MPC5125_GPIO_PIN(13),MPC5125_GPIO_OUT_EN,1,0,1);         
         #else
            return IO_ERROR;
         #endif         
         break;
      case 6:
         #if BSPCFG_PCS6_USES_DIU       
            ioc_ptr->DIU_LD09 = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3;  /* SPI_SS */ 
            /* Set SPI_SS as GPIO out put function */
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT2,MPC5125_GPIO_PIN(6),MPC5125_GPIO_OUT_EN,1,0,1);        
         #else
            return IO_ERROR;
         #endif         
         break;
      case 7:        
         /* PSC7 can not set SPI_SS as GPIO out put function */  
         return IO_ERROR;
         
      case 8:
         #if BSPCFG_PCS8_USES_DIU_I2C      
            ioc_ptr->DIU_LD21 = IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;  /* SPI_SS */
            /* Set SPI_SS as GPIO out put function */
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT1,MPC5125_GPIO_PIN(15),MPC5125_GPIO_OUT_EN,1,0,1);        
         #else
            return IO_ERROR;
         #endif         
         break;
      case 9:
         #if BSPCFG_PCS9_USES_CAN
            ioc_ptr->CAN2_TX  = IO_CONTROL_FUNCTION_3|IO_CONTROL_SLEW_RATE_3;
            /* Set SPI_SS as GPIO out put function */
            _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT2,MPC5125_GPIO_PIN(27),MPC5125_GPIO_OUT_EN,1,0,1);         
         #else
            return IO_ERROR;
         #endif         
         break;
      default:
         return IO_ERROR;
   }
#endif

   ioc_ptr->GBOBE = IO_CONTROL_ENABLE;
   return MQX_OK;
} 

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_setup_lpc_for_pccard
* Returned Value   : 
* Comments         :
*    Setup Localplus bus for pccard operation
*
*END*----------------------------------------------------------------------*/
void _bsp_lpc_pccard_setup 
(
  void
)
{
    MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();
    
    MPC5125_LPC_STRUCT_PTR lpc_ptr = &((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->LPC;
    MPC5125_SYSTEM_CONFIGURATION_STRUCT_PTR syscon_ptr = &((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->SYSCON;
       
    ioc_ptr->LPC_CS0_B  =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;
     ioc_ptr->LPC_CLK      =    IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;
     ioc_ptr->LPC_OE_B  =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;
    ioc_ptr->LPC_RWB       =    IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;
     ioc_ptr->LPC_ACK_B =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;
    ioc_ptr->LPC_AX03   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;   

     ioc_ptr->EMB_AX02  =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;        
    ioc_ptr->EMB_AX01   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AX00   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD31   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD30   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD29   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD28   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD27   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD26   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD25   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD24   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD23   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD22   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD21   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD20   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD19   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD18   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD17   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD16   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD15   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD14   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD13   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD12   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD11   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD10   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD09   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD08   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD07   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD06   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD05   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD04   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD03   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD02   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD01   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD00   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;      
 
    ioc_ptr->GBOBE = IO_CONTROL_ENABLE;
    
    syscon_ptr->LPBus_CS0_AW = 0x1000ffff;
     lpc_ptr->CS0BOOTC =0x00000000 // wait states = 3
                      | MPC5125_LPCS_CS0BOOTC_WAITX(3)
                      | MPC5125_LPCS_CS0BOOTC_MUX_MASK  //mux
                      | MPC5125_LPCS_CS0BOOTC_ALEV_MASK //al
                      | MPC5125_LPCS_CS0BOOTC_RS_MASK       //RS = 1 
                      | MPC5125_LPCS_CS0BOOTC_WS_MASK       //WS = 1(8-bit devices no effect :-?)  
                      | MPC5125_LPCS_CS0BOOTC_CE_MASK;//AA=0,CE = 1 enable external chip select
                      
     lpc_ptr->CSC   =   MPC5125_LPCS_CSC_ME_MASK;
     lpc_ptr->CSBC  =   0x00;
     lpc_ptr->CSDC  =   MPC5125_LPCS_CSDC_MASK;
     lpc_ptr->ALTR  =   0x00;
     lpc_ptr->CSHC  =   MPC5125_LPCS_CSHC_MASK;
     lpc_ptr->EMB_SC    =   0x00100000;
     lpc_ptr->EMB_PC    =   0x00;
     lpc_ptr->SCLPC_E   =   (MPC5125_LPCS_SCLPC_E_RC_MASK | MPC5125_LPCS_SCLPC_E_RF_MASK);
     lpc_ptr->SCLPC_FIFOC   =   MPC5125_LPCS_SCLPC_FIFOC_GR(1);
     lpc_ptr->SCLPC_FIFOA   =   0x00;
     lpc_ptr->SCLPC_C   =   (MPC5125_LPCS_SCLPC_C_FLUSH | MPC5125_LPCS_SCLPC_C_RW_MASK | MPC5125_LPCS_SCLPC_C_BPT(1));
     lpc_ptr->SCLPC_SA  =   0x10000000;
     lpc_ptr->SCLPC_PS  =   (MPC5125_LPCS_SCLPC_PS_RESTART_MASK|MPC5125_LPCS_SCLPC_PS_PACKET_SIZE(1));

} /* Endbody */



/*FUNCTION*-------------------------------------------------------------------
* Function Name    : _bsp_sdhc_io_init
* Returned Value   : 0 for success, -1 for failure
* Comments         :
* This function performs BSP-specific initialization related to SDHC
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_sdhc_io_init
(
    uint_8 dev_num,
    boolean card_detected
)
{ /* Body */
    MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();
    MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
    
    _mpc5125_gpio_pin_config(MPC5125_GPIO_PORT1,MPC5125_GPIO_PIN(2),0,1,1,1);
    
     
    ccm_ptr->SCCR2 |= 0x01000000; //ENABLE CLK SDHC1
    switch (dev_num) {
      case 0:           
            ioc_ptr->SDHC1_CLK   = IO_CONTROL_FUNCTION_0|IO_CONTROL_PULL_UP |IO_CONTROL_SLEW_RATE_3;
            ioc_ptr->SDHC1_CMD   = IO_CONTROL_FUNCTION_0|IO_CONTROL_PULL_UP |IO_CONTROL_SLEW_RATE_3;
            ioc_ptr->SDHC1_D0    = IO_CONTROL_FUNCTION_0|IO_CONTROL_PULL_UP |IO_CONTROL_SLEW_RATE_3;
            ioc_ptr->SDHC1_D1    = IO_CONTROL_FUNCTION_0|IO_CONTROL_PULL_UP |IO_CONTROL_SLEW_RATE_3;
            ioc_ptr->SDHC1_D2    = IO_CONTROL_FUNCTION_0|IO_CONTROL_PULL_UP |IO_CONTROL_SLEW_RATE_3;
    if (card_detected == 0)
            ioc_ptr->SDHC1_D3    = IO_CONTROL_FUNCTION_0|IO_CONTROL_PULL_UP|IO_CONTROL_SLEW_RATE_3;
    else
            ioc_ptr->SDHC1_D3    = IO_CONTROL_FUNCTION_0|IO_CONTROL_PULL_DOWN|IO_CONTROL_SLEW_RATE_3;
            break;
       default:
          return -1;
    }
   ioc_ptr->GBOBE = IO_CONTROL_ENABLE;
   return MQX_OK;
} /* Endbody */
/*FUNCTION*-------------------------------------------------------------------
* Function Name    : _bsp_nandflash_io_init
* Returned Value   : 
* Comments         :
* This function performs BSP-specific initialization related to nandflash
*
*END*----------------------------------------------------------------------*/
_mqx_int _bsp_nandflash_io_init
(
   void
)

{

    MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();
    MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
    MPC5125_SYSTEM_CONFIGURATION_STRUCT_PTR  syscnf = MPC5125_SC_ADDR();
    
    ccm_ptr->SCCR2 |= CCM_SCCR1_NFC_EN;
    _mpc5125_get_csb_clock(BSP_EXCLK_CLOCK);
    
    ioc_ptr->EMB_AD19   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD18   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD17   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD16   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3; 
    ioc_ptr->EMB_AD07   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD06   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD05   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD04   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD03   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD02   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD01   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;    
    ioc_ptr->EMB_AD00   =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3; 
    ioc_ptr->NFC_CE0_B  =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;
    ioc_ptr->LPC_ACK_B  =   IO_CONTROL_FUNCTION_1|IO_CONTROL_SLEW_RATE_3;
    ioc_ptr->NFC_CE0_B  =   IO_CONTROL_FUNCTION_0|IO_CONTROL_SLEW_RATE_3;

    /* Set NFC Base Address Register */
    syscnf->LPBus_NFC_AW = (uint_32)BSP_NANDFLASH_BASE;

    ioc_ptr->GBOBE = IO_CONTROL_ENABLE;

    return MQX_OK ;
}
/* EOF */
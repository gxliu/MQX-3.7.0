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
* $FileName: bsp_init.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains flash boot code to initialize chip selects,
*   disable the watchdog timer and initialize the PLL.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"

static void _mqx_clock_init_intosc(void); 
static void _mqx_clock_init_xosc1(void);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf51AGxx_init
* Returned Value   : void
*
* Comments : 
* Initialize CPU speed and chip selects. Called from vectors.cw boot 
* sequence before calling the runtime application startup code. 
* 
* WARNING: This function is called before the device and memory 
* interface is initialized, and before the C runtime is initialized. 
* Do not use global variables in this function, doing so may be disastrous.
*
*END*----------------------------------------------------------------------*/
void mcf51AGxx_init
   (
      void
   )
{
    VMCF51AG_STRUCT_PTR reg_ptr = (VMCF51AG_STRUCT_PTR)BSP_IPSBAR;

    reg_ptr->WDOG.WDOG_UNLOCK = 0xC520U;     
    reg_ptr->WDOG.WDOG_UNLOCK = 0xD928U;     
    reg_ptr->WDOG.WDOG_ST_CTRL_H = 0xD2;     
    reg_ptr->SIM.SOPT1 = MCF51XX_SOPT1_STOPE_MASK | MCF51XX_SOPT1_WAITE_MASK;		 
    reg_ptr->SIMX.SOPT2 =0x00;
    reg_ptr->PMC.SPMSC1 = 0x1C;              
    reg_ptr->PMC.SPMSC2 = 0x00;              
    reg_ptr->SIM.SMCLK &= (uchar)~0x17;
   
    /* Internal oscillator selected */
    #if (BSPCFG_USE_INTCLK == 1)
        #if (BSPCFG_USE_Y1CLK == 1)
            #error "Only one clock source must be selected - fix problem in user_config.h"    
        #else
            _mqx_clock_init_intosc();  
        #endif
    /* Low-frequency 17000kHz external crystal selected */
    #elif (BSPCFG_USE_Y1CLK == 1)
        #if (BSPCFG_USE_INTCLK == 1)
            #error "Only one clock source must be selected - fix problem in user_config.h"    
        #else
            _mqx_clock_init_xosc1();
        #endif
    #else
        #error  "Select clock source in user_config.h"
    #endif
    reg_ptr->SIMX.SCGC2 = 0x4C;
    reg_ptr->INTC.WCR   = 0x80;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mqx_clock_init_intosc
* Returned Value   : void
*
* Comments : 
*
*END*----------------------------------------------------------------------*/
static void _mqx_clock_init_intosc(void) 
{
   VMCF51AG_STRUCT_PTR reg_ptr = (VMCF51AG_STRUCT_PTR)BSP_IPSBAR;
   /* Test if the device trim value is stored on the specified address */ 
   if (*(uchar_ptr)0x03FF != 0xFF) {
	   /* Initialize ICSTRM register from a non volatile memory */
	   reg_ptr->ICS.ICSTRM = *(uchar_ptr)0x03FF;
	   /* Initialize ICSSC register from a non volatile memory */
	   reg_ptr->ICS.ICSSC = (uchar)((*(uchar_ptr)0x03FE) & (uchar)0x01);
    }
    /* Initialization of the ICS control register 1 */
    /* ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
    reg_ptr->ICS.ICSC1 = 0x06;
    /* Initialization of the ICS control register 2 */
    /* ICSC2: BDIV=1,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
    reg_ptr->ICS.ICSC2 = 0x40;
    /* Wait until the source of reference clock is internal clock */
    while(!(reg_ptr->ICS.ICSSC & 0x10)) {
    }
    /* Initialization of the ICS status and control */
    /* ICSSC: DRST_DRS=0,DMX32=0 */
    reg_ptr->ICS.ICSSC |= (uchar)0x50;
    reg_ptr->ICS.ICSSC = (uint_8)(((reg_ptr->ICS.ICSSC) & (uint_8)~0x60) | (uint_8)0x80);
    /* Wait until the FLL switches to Low range DCO mode */
    while((reg_ptr->ICS.ICSSC & 0xC0) != 0x00) {
    }
}
                        
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mqx_clock_init_xosc1
* Returned Value   : void
*
* Comments : 
* 
*
*END*----------------------------------------------------------------------*/
static void _mqx_clock_init_xosc1(void) 
{  
    VMCF51AG_STRUCT_PTR reg_ptr = (VMCF51AG_STRUCT_PTR)BSP_IPSBAR;
    
    /* Test if the device trim value is stored on the specified address */
    if (*(uchar_ptr)0x03FF != 0xFF) {
	   /* Initialize ICSTRM register from a non volatile memory */
	   reg_ptr->ICS.ICSTRM = *(uchar_ptr)0x03FF;
	   /* Initialize ICSSC register from a non volatile memory */
	   reg_ptr->ICS.ICSSC = (uchar)((*(uchar_ptr)0x03FE) & (uchar)0x01);
    }
    /* Initialization of the ICS control register 1 */
    /* ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
    reg_ptr->ICS.ICSC1 = 0x1A;
    /* Initialization of the ICS control register 2 */
    /* ICSC2: BDIV=1,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */    
    reg_ptr->ICS.ICSC2 = 0x26;
    /* Wait until the initialization of the external crystal oscillator is completed */
    while(!(reg_ptr->ICS.ICSSC & 0x02)) {
    }    
    reg_ptr->ICS.ICSSC = (uint_8)(((reg_ptr->ICS.ICSSC) & (uint_8)~0xA0) | (uint_8)0x40);
    /* Wait until the FLL switches to Low range DCO mode */
    while((reg_ptr->ICS.ICSSC & 0xC0) != 0x40) {
    }
    /* FEE mode entered */
}

/* EOF */
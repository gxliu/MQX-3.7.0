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
* $Version : 3.5.4.0$
* $Date    : Dec-11-2009$
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



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf51EMxx_init
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

static void _mqx_clock_init_intosc(void); 
static void _mqx_clock_init_xosc1(void);


void mcf51EMxx_init
   (
      void
   )
{
    VMCF51EM_STRUCT_PTR reg_ptr = (VMCF51EM_STRUCT_PTR)BSP_IPSBAR;


    reg_ptr->SIM.SOPT1 = MCF51XX_SOPT1_STOPE_MASK | MCF51XX_SOPT1_WAITE_MASK | MCF51XX_SOPT1_COPCLKS_MASK |MCF51XX_SOPT1_COPW_MASK;

    /* Internal oscillator selected */
    #if (BSPCFG_USE_INTCLK == 1)
        #if (BSPCFG_USE_Y1CLK == 1) || (BSPCFG_USE_Y2CLK == 1)
            #error "Only one clock source must be selected - fix problem in user_config.h"    
        #else
            _mqx_clock_init_intosc();  
        #endif
    /* Low-frequency 32768kHz external crystal selected */
    #elif (BSPCFG_USE_Y1CLK == 1)
        #if (BSPCFG_USE_INTCLK == 1) || (BSPCFG_USE_Y2CLK == 1)
            #error "Only one clock source must be selected - fix problem in user_config.h"    
        #else
            _mqx_clock_init_xosc1();
        #endif
    #else
        #error  "Select clock source in user_config.h"
    #endif

    /* disable all RTC interrupts */
    _rtc_int_enable(FALSE, MCF51EM_RTC_INT_ALL_MASK);
}

#define ICSSC_FTRIM_MASK                1


/* INTOSC 25.165824MHz BUS_CLOCK  */
static void _mqx_clock_init_intosc(void) 
{
  
    VMCF51EM_STRUCT_PTR reg_ptr = (VMCF51EM_STRUCT_PTR)BSP_IPSBAR;

    /* Test if the device trim value is stored on the specified address */
    if (*(uchar*far)0x03FF != 0xFF) { /* Test if the device trim value is stored on the specified address */
        reg_ptr->ICS.ICSTRM = *(uchar_ptr far)0x03FF; /* Initialize ICSTRM register from a non volatile memory */
        reg_ptr->ICS.ICSSC = (uchar)((*(uchar_ptr far)0x03FE) & (uchar)ICSSC_FTRIM_MASK); /* Initialize ICSSC register from a non volatile memory */
    }

    /* Select XOSC2 clock input */
    /* CCSCTRL: SEL=0 */
    reg_ptr->ICS.CCSCTRL &= (uint_8)~MCF51EM_CCSCTRL_SEL_MASK;     
    
    /* Initialization of the ICS control register 1 */
    /* ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
    reg_ptr->ICS.ICSC1 = 0x06;                        
    
    /* Initialization of the ICS control register 2 */
    /* ICSC2: BDIV=0,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
    reg_ptr->ICS.ICSC2 = 0x00;                        
    
    /* Wait until the source of reference clock is internal clock */
    while(!(reg_ptr->ICS.ICSSC & MCF51EM_ICSSC_IREFST_MASK)) {               
    }
    
    /* Initialization of the ICS status and control */
    /* ICSSC: DRST_DRS=2,DMX32=0 */
    reg_ptr->ICS.ICSSC = (uint_8)(((reg_ptr->ICS.ICSSC) & (uint_8)~0x60) | (uint_8)0x80); 
    
    /* Wait until the FLL switches to High range DCO mode */
    while((reg_ptr->ICS.ICSSC & 0xC0) != 0x80) {      
    }

    /* FEI mode entered */   
}
                        

/* XOSC1 25.165824MHz BUS_CLOCK  */
static void _mqx_clock_init_xosc1(void) 
{
  
    VMCF51EM_STRUCT_PTR reg_ptr = (VMCF51EM_STRUCT_PTR)BSP_IPSBAR;

    /* Select XOSC1 clock input */
    reg_ptr->ICS.CCSCTRL = (uint_8)MCF51EM_CCSCTRL_SEL_MASK;

    /* Initialization of the ICS control register 1 */
    /* ICSC1: CLKS=0,RDIV=0,IREFS=0,IRCLKEN=0,IREFSTEN=0 */
    reg_ptr->ICS.ICSC1 = 0x00;

    /* Initialization of the ICS control register 2 */
    /* ICSC2: BDIV=0,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=1,EREFSTEN=0 */
    reg_ptr->ICS.ICSC2 = 0x02;

    /* Initialization of the ICS status and control */
    /* ICSSC: DRST_DRS=2,DMX32=0 */
    reg_ptr->ICS.ICSSC = (uint_8)(((reg_ptr->ICS.ICSSC) & (uint_8)~0x60) | (uint_8)0x80);

    /* Wait until the FLL switches to High range DCO mode */
    while (((reg_ptr->ICS.ICSSC) & 0xC0) != 0x80) {
    }
    
    /* FEE mode entered */
}
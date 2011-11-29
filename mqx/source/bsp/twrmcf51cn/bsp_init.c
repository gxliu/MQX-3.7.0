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
* $Version : 3.6.16.0$
* $Date    : Aug-19-2010$
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

static void _bsp_flexbus_mram_setup (const uint_32 base_address);
static void _bsp_flexbus_d4d_setup (const uint_32 base_address);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf51CNxx_init
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

static void _mqx_clock_init_32KHz();
static void _mqx_clock_init_25MHz();

void mcf51CNxx_init
   (
      void
   )
{
   VMCF51CN_STRUCT_PTR reg_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;


   reg_ptr->SIM.SOPT1 = MCF51XX_SOPT1_STOPE_MASK | MCF51XX_SOPT1_WAITE_MASK | MCF51XX_SOPT1_COPCLKS_MASK |MCF51XX_SOPT1_COPW_MASK;


   // D5 extal pin ON + D4 xtal pin ON  
   reg_ptr->GPIO.PTDPF |= 0b11 << MCF51XX_PTXPF_X4_BITNUM;
   reg_ptr->GPIO.PTDPF |= 0b11 << MCF51XX_PTXPF_X5_BITNUM;

 
#if   (BSPCFG_USE_25MHZ_XTAL == 1) & (BSPCFG_USE_32KHZ_XTAL == 0)
   _mqx_clock_init_25MHz();  
#elif (BSPCFG_USE_25MHZ_XTAL == 0) & (BSPCFG_USE_32KHZ_XTAL == 1)
   _mqx_clock_init_32KHz();
#elif (BSPCFG_USE_25MHZ_XTAL == 1) & (BSPCFG_USE_32KHZ_XTAL == 1)
#error "Only one clock source must be selected - fix problem in user_config.h"
#elif (BSPCFG_USE_25MHZ_XTAL == 0) & (BSPCFG_USE_32KHZ_XTAL == 0)
#error "One external clock source must be selected - fix problem in user_config.h"
#endif   

    /* Enable Mini FlexBUS signals for compact flash card or MRAM*/
    _bsp_flexbus_io_init();

   /* setup flexbus for CS0 - MRAM*/
   _bsp_flexbus_mram_setup((uint_32)BSP_EXTERNAL_MRAM_BASE); 

}

   


static void _mqx_clock_init_32KHz() 
{
   VMCF51CN_STRUCT_PTR reg_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;

   // Start in FEI Mode - set up external crystal 
   // crystal is being used + external reference clock
   reg_ptr->MCG.MCGC2 = MCF51XX_MCGC2_EREFS_MASK | MCF51XX_MCGC2_ERCLKEN_MASK;


   // wait for OSC to start
   while (!(reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_OSCINIT_MASK))      
   ;

   /* select clock mode */
   reg_ptr->MCG.MCGC1 = (0b10  << MCF51XX_MCGC1_CLKS_BITNUM)  // CLKS = 10 -> external reference clock
                     | (0b000 << MCF51XX_MCGC1_RDIV_BITNUM)  // RDIV = 1 -> 32khz
                     | MCF51XX_MCGC1_IRCLKEN_MASK;            // IRCLK to RTC enabled

    
   // switch from FEI to FBE (FLL bypassed external)
   // wait for Reference Status bit to update
   while (!(reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_IREFST_MASK)) 
   ;


   // DCO Range select 0b10 = FLL by 1536 = 50331648 Hz        
   reg_ptr->MCG.MCGC4 = (0b10<<MCF51XX_MCGC4_DRST_DRS_BITNUM);           
        

   // wait for DCO to effect and for FLL to lock
   while ((reg_ptr->MCG.MCGC4 & MCF51XX_MCGC4_DRST_DRS_MASK) && (reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_LOCK_MASK))  
   ;                                    

   reg_ptr->MCG.MCGC1 &= ~(0b11 << MCF51XX_MCGC1_CLKS_BITNUM);  // switch to FLL

   /* Wait for clock status bits to update */
   while ((reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_CLKST_MASK )!= 0b00)       
   ;
   // FEE mode entered
}

static void _mqx_clock_init_25MHz() 
{
   VMCF51CN_STRUCT_PTR reg_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;


   //1. First, FEI must transition to FBE mode:
   //a) MCGC2 = 0x36 (%00110110)
   //– BDIV (bits 7 and 6) set to %00, or divide-by-1
   //– RANGE (bit 5) set to 1 because the frequency of 8 MHz is within the high frequency range
   //– HGO (bit 4) set to 1 to configure the crystal oscillator for high gain operation
   //– EREFS (bit 2) set to 1, because a crystal is being used
   //– ERCLKEN (bit 1) set to 1 to ensure the external reference clock is active
   reg_ptr->MCG.MCGC2 = MCF51XX_MCGC2_EREFS_MASK | MCF51XX_MCGC2_ERCLKEN_MASK | MCF51XX_MCGC2_RANGE_MASK | MCF51XX_MCGC2_HGO_MASK;        


   //b) Loop until OSCINIT (bit 1) in MCGSC is 1, indicating the crystal selected by the EREFS bit
   //has been initialized.
   while (!(reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_OSCINIT_MASK))      
   ;

   //c) Because RANGE = 1, set DIV32 (bit 4) in MCGC3 to allow access to the proper RDIV bits
   //while in an FLL external mode.
   reg_ptr->MCG.MCGC3 |= MCF51XX_MCGC3_DIV32_MASK;

   //d) MCGC1 = 0x98 (%10011000)
   //– CLKS (bits 7 and 6) set to %10 to select external reference clock as system clock source
   //– RDIV (bits 5-3) set to %011, or divide-by-256 because 8MHz / 256 = 31.25 kHz that is in
   //the 31.25 kHz to 39.0625 kHz range required by the FLL
   //– IREFS (bit 2) cleared to 0, selecting the external reference clock
   reg_ptr->MCG.MCGC1 = (0b10  << MCF51XX_MCGC1_CLKS_BITNUM)  // CLKS = 10 -> external reference clock
                     | (0b100 << MCF51XX_MCGC1_RDIV_BITNUM); // RDIV = 2^4 -> 25MHz/16 = 1.5625 MHz for PLL



   // wait for Reference Status bit to update 
   while (!(reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_IREFST_MASK)) 
   ;

   // and for clock status bits to update
   while ((reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_CLKST_MASK) != (0b10 << MCF51XX_MCGSC_CLKST_BITNUM)) 
   ;


   // switch from FBE to PBE (PLL bypassed internal) mode 
   // set PLL multi 50MHz amd select PLL      
   reg_ptr->MCG.MCGC3 = (0b1000<< MCF51XX_MCGC3_VDIV_BITNUM) | MCF51XX_MCGC3_PLLS_MASK;           
              
   // wait for PLL status bit and LOCK bit
   while (!(reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_PLLST_MASK) && !(reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_LOCK_MASK))  
   ;

   //switch from PBE to PEE (PLL enabled external mode)                                    
   reg_ptr->MCG.MCGC1 &= ~(0b11 << MCF51XX_MCGC1_CLKS_BITNUM);  

   /* Wait for clock status bits to update */
   while ((reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_CLKST_MASK )!= (0b11<<MCF51XX_MCGSC_CLKST_BITNUM))       
   ;
   // FEE mode entered
}

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
    VMCF51CN_STRUCT_PTR reg_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;
    /* CS0 base address */    
    reg_ptr->MB.CSAR0 = (vuint_32)base_address;
    /* CS0 control (8bit data, 0x13 waitstate, multiplexed mode) */     
    reg_ptr->MB.CSCR0 = MCF5XXX_FBCS_CSCR_ASET(1) | MCF5XXX_FBCS_CSCR_WS(0x13) |
        MCF5XXX_FBCS_CSCR_MUX | MCF5XXX_FBCS_CSCR_AA | MCF5XXX_FBCS_CSCR_PS_8;      
    /* CS0 address mask and enable */    
    reg_ptr->MB.CSMR0 = MCF5XXX_FBCS_CSMR_BAM_64K | MCF5XXX_FBCS_CSMR_V;
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_flexbus_mram_setup
* Returned Value   : 
* Comments         :
*     Enable external MRAM mapped on CS0 
*
*END*----------------------------------------------------------------------*/
static void _bsp_flexbus_mram_setup (const uint_32 base_address)
{
   VMCF51CN_STRUCT_PTR reg_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;

   /* CS0 base address */    
   reg_ptr->MB.CSAR0 = (vuint_32)base_address;
   /* CS0 control (8bit data, 1 waitstate, multiplexed mode) */     
   reg_ptr->MB.CSCR0 = MCF5XXX_FBCS_CSCR_ASET(1) | MCF5XXX_FBCS_CSCR_WS(1) |
     MCF5XXX_FBCS_CSCR_MUX | MCF5XXX_FBCS_CSCR_AA | MCF5XXX_FBCS_CSCR_PS_8;      
   /* CS0 address mask and enable */    
   reg_ptr->MB.CSMR0 = MCF5XXX_FBCS_CSMR_BAM_512K | MCF5XXX_FBCS_CSMR_V;
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_flexbus_lcd_setup
* Returned Value   : 
* Comments         :
*    Setup flexbus for lcd operation
*
*END*----------------------------------------------------------------------*/
void _bsp_flexbus_lcd_setup (const uint_32 base_address)
{
    VMCF51CN_STRUCT_PTR fb_ptr = (VMCF51CN_STRUCT_PTR)BSP_IPSBAR;
    
    /* Enable external MRAM mapped on CS0 */
    fb_ptr->MB.CSAR0 = MCF5XXX_FBCS_CSAR_BA(base_address); /* CS0 base address */  
    fb_ptr->MB.CSCR0 = MCF5XXX_FBCS_CSCR_MUX | MCF5XXX_FBCS_CSCR_AA | MCF5XXX_FBCS_CSCR_PS_16; 
    fb_ptr->MB.CSMR0 = MCF5XXX_FBCS_CSMR_BAM_128K | MCF5XXX_FBCS_CSMR_V; /* The address range is set to 128K because the DC signal is connected on address wire */   
    
    /* set the flex bus to shared mode */
    fb_ptr->GPIO.PTJPF &= ~MCF51XX_PTXPF_X0_MASK;
    fb_ptr->GPIO.PTJDD |= 0x01;
    fb_ptr->GPIO.PTJD |= 0x01;
   
}
/* EOF */

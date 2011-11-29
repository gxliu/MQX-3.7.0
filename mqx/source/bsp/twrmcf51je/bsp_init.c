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

/***************************************************************************
 * Local Functions Prototypes 
 ***************************************************************************/
static void _mqx_clock_init_16MHz();
static void _mqx_clock_init_32KHz();
static void _bsp_flexbus_mram_setup (const uint_32 base_address);
/***************************************************************************
 * Local Functions 
 ***************************************************************************/

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mqx_clock_init_24MHz
* Returned Value   : void
* Comments         :
*   
*
*END*----------------------------------------------------------------------*/

static void _mqx_clock_init_16MHz() 
{
    VMCF51JE_MCG_STRUCT_PTR mcg_ptr = 
        (VMCF51JE_MCG_STRUCT_PTR)&(((VMCF51JE_STRUCT_PTR)BSP_IPSBAR)->MCG);

    /*
    ** ------FBE MODE------  
    ** Assume 16MHz external clock source connected.
    ** RANGE = 1; HGO = 1; ERCLKEN=1; EREFS = 1; BDIV = 00
    */

    mcg_ptr->MCGC2 =  MCF51XX_MCGC2_RANGE_MASK
                    | MCF51XX_MCGC2_HGO_MASK
                    | MCF51XX_MCGC2_ERCLKEN_MASK
                    | MCF51XX_MCGC2_EREFS_MASK; 

    /* 
    ** Loop until OSCINIT (bit 1) in MCGSC is 1, 
    ** indicating the crystal selected 
    ** by the EREFS bit has been initialized. 
    */
    while( ! mcg_ptr->MCGSC & MCF51XX_MCGSC_OSCINIT_MASK )  
        ;

    /* 
    ** Because RANGE = 1, set DIV32 (bit 4) 
    ** in MCGC3 to allow access to the proper
    ** RDIV bits while in an FLL external mode. 
    */
    mcg_ptr->MCGC3 = MCF51XX_MCGC3_DIV32_MASK;  

    /* 
    ** CLKS = 10; RDIV = 100; IREFS = 0; 
    ** Therefore, external reference divider factor is 512 
    */
    mcg_ptr->MCGC1 =   MCF51XX_MCGC1_CLKS1_MASK 
                     | MCF51XX_MCGC1_RDIV2_MASK 
                     | MCF51XX_MCGC1_IRCLKEN_MASK;

    /* 
    ** IREFS (bit 2) cleared to 0, 
    ** selecting the external reference clock 
    */
    mcg_ptr->MCGC1 &= ~MCF51XX_MCGC1_IREFS_MASK;

    /* 
    ** Loop until IREFST (bit 4) in MCGSC is 0, 
    ** indicating the external reference 
    ** is the current source for the reference clock 
    */
    while (mcg_ptr->MCGSC & MCF51XX_MCGSC_IREFST_MASK)
        ;


    /* 
    ** Loop until CLKST (bits 3 and 2) in MCGSC is %10, 
    ** indicating that the external reference clock 
    ** is selected to feed MCGOUT 
    */
    while (((mcg_ptr->MCGSC & MCF51XX_MCGSC_CLKST_MASK) >> 2) != 0b10)
        ;

    /* 
    ** ------PBE MODE------
    ** PLLS =1; DIV32 = 1; VDIV = 1001, 
    ** Multiplication factor is 48
    */
    mcg_ptr->MCGC3 =  MCF51XX_MCGC3_PLLS_MASK 
                    | MCF51XX_MCGC3_DIV32_MASK 
                    | MCF51XX_MCGC3_VDIV3_MASK 
                    | MCF51XX_MCGC3_VDIV2_MASK;   


    /* wait for PLL status bit to update */
    while ( !(mcg_ptr->MCGSC & MCF51XX_MCGSC_PLLST_MASK) )
        ;
    /* Wait for LOCK bit to set */
    while ( !(mcg_ptr->MCGSC & MCF51XX_MCGSC_LOCK_MASK) )
        ;

    /*
    ** ------PEE MODE------
    ** CLKS = 00; RDIV = 100; IREFS = 0
    */
    mcg_ptr->MCGC1 &= ~MCF51XX_MCGC1_CLKS_MASK;

    /* 
    ** Loop until CLKST (bits 3 and 2) in MCGSC are %11, 
    ** indicating that the PLL output is selected 
    ** to feed MCGOUT in the current clock mode 
    */  
    while (((mcg_ptr->MCGSC & MCF51XX_MCGSC_CLKST_MASK) >> 2) != 0b11)
        ; 
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mqx_clock_init_32KHz
* Returned Value   : void
* Comments         : Initialize MCG for 32.768kHz XOSC1 use
*   
*
*END*----------------------------------------------------------------------*/

static void _mqx_clock_init_32KHz() 
{
    VMCF51JE_STRUCT_PTR reg_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;


    /*  System clock initialization */
    reg_ptr->MCG_CCS.CCSCTRL =  MCF51XX_CCSCTRL_HGO1_MASK
                              | MCF51XX_CCSCTRL_ERCLKEN1_MASK
                              | MCF51XX_CCSCTRL_EN_MASK
                              | MCF51XX_CCSCTRL_SEL_MASK;

    /* Start in FEI Mode - set up external crystal 
    ** crystal is being used + external reference clock
    */
    reg_ptr->MCG.MCGC2 = MCF51XX_MCGC2_EREFS_MASK | MCF51XX_MCGC2_ERCLKEN_MASK;


    /* Wait for OSC to start */
    while (!(reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_OSCINIT_MASK))      
        ;

    /* 
    ** Select clock mode 
    ** CLKS = 10 -> external reference clock
    ** RDIV = 1 -> 32khz
    ** IRCLK to RTC enabled
    */
    reg_ptr->MCG.MCGC1 =  (0b10  << MCF51XX_MCGC1_CLKS_BITNUM)  
                        | (0b000 << MCF51XX_MCGC1_RDIV_BITNUM)
                        | MCF51XX_MCGC1_IRCLKEN_MASK;


    /* 
    ** Switch from FEI to FBE (FLL bypassed external)
    ** wait for Reference Status bit to update
    */
    while (!(reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_IREFST_MASK)) 
        ;


    /* DCO Range select 0b10 = FLL by 1536 = 50331648 Hz */
    reg_ptr->MCG.MCGC4 = (0b10 << MCF51XX_MCGC4_DRST_DRS_BITNUM);           
        

    /* wait for DCO to effect and for FLL to lock */
    while (    (reg_ptr->MCG.MCGC4 & MCF51XX_MCGC4_DRST_DRS_MASK) 
            && (reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_LOCK_MASK))
        ;                                    

    /* Switch to FLL */
    reg_ptr->MCG.MCGC1 &= ~(0b11 << MCF51XX_MCGC1_CLKS_BITNUM);

    /* Wait for clock status bits to update */
    while ((reg_ptr->MCG.MCGSC & MCF51XX_MCGSC_CLKST_MASK )!= 0b00)       
        ;
    
    /* FEE mode entered */
}


/***************************************************************************
 * Global Functions 
 ***************************************************************************/
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf51JExx_init
* Returned Value   : void
* Comments         :
*   Initialize CPU speed and chip selects.  Called from vectors.cw boot
* sequence before calling the runtime application startup code.
*
*END*----------------------------------------------------------------------*/
void mcf51JExx_init
   (
      void
   )
{
   VMCF51JE_STRUCT_PTR reg_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;
   reg_ptr->SIM.SOPT1 = MCF51XX_SOPT1_STOPE_MASK | 
                       MCF51XX_SOPT1_WAITE_MASK |
                       MCF51XX_SOPT1_RSTPE_MASK |
                       MCF51XX_SOPT1_BKGDPE_MASK ;

   reg_ptr->PMC.SPMSC1 = 0x40; //Low-Voltage Detect Interrupt Enable 
   reg_ptr->PMC.SPMSC2 = 0; 

   #if   (BSPCFG_USE_16MHZ_XTAL == 1) & (BSPCFG_USE_32KHZ_XTAL == 0)
      _mqx_clock_init_16MHz();  
   #elif (BSPCFG_USE_16MHZ_XTAL == 0) & (BSPCFG_USE_32KHZ_XTAL == 1)
      _mqx_clock_init_32KHz();
   #elif (BSPCFG_USE_16MHZ_XTAL == 1) & (BSPCFG_USE_32KHZ_XTAL == 1)
   #error "Only one clock source must be selected - fix problem in user_config.h"
   #elif (BSPCFG_USE_16MHZ_XTAL == 0) & (BSPCFG_USE_32KHZ_XTAL == 0)
   #error "One external clock source must be selected - fix problem in user_config.h"
   #endif 
   
   /* Enable Mini FlexBUS signals for compact flash card or MRAM*/
   _bsp_flexbus_io_init();

   /* setup flexbus for CS0 - MRAM*/
   _bsp_flexbus_mram_setup((uint_32)BSP_EXTERNAL_MRAM_BASE); 
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
   VMCF5XXX_MINIFB_STRUCT_PTR mb_ptr = &((VMCF51JE_STRUCT_PTR)BSP_IPSBAR)->MB;
 
   /* CS0 base address */    
   mb_ptr->CSAR0 = (vuint_32)base_address; 
   /* CS0 control (8bit data, 1 waitstate, internal ack) */     
   mb_ptr->CSCR0 |=  MCF5XXX_FBCS_CSCR_WS(1) |  
      MCF5XXX_FBCS_CSCR_AA | MCF5XXX_FBCS_CSCR_PS_8;      
   /* CS0 address mask and enable */    
   mb_ptr->CSMR0 = MCF5XXX_FBCS_CSMR_BAM_512K | MCF5XXX_FBCS_CSMR_V;
  
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_setup_flexbus_for_pccard
* Returned Value   : 
* Comments         :
*    Setup flexbus for pccard operation  on CS1
*
*END*----------------------------------------------------------------------*/
void _bsp_flexbus_pccard_setup (const uint_32 base_address)
{
    VMCF51JE_STRUCT_PTR reg_ptr = (VMCF51JE_STRUCT_PTR)BSP_IPSBAR;
    /* CS0 base address */    
    reg_ptr->MB.CSAR1 = MCF5XXX_FBCS_CSAR_BA(base_address);
    /* CS0 control (8bit data, 0x13 waitstate, internal ack) */     
    reg_ptr->MB.CSCR1 = MCF5XXX_FBCS_CSCR_WS(0x13) |   /* wait states    */
                        MCF5XXX_FBCS_CSCR_AA |         /* internal ack   */  
                        MCF5XXX_FBCS_CSCR_PS_8;        /* data bus width */
    /* CS0 address mask and enable */    
    reg_ptr->MB.CSMR1 = MCF5XXX_FBCS_CSMR_BAM_64K | MCF5XXX_FBCS_CSMR_V;
}

/* EOF */

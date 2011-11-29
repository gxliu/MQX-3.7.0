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
* $FileName: init_hw.c$
* $Version : 3.7.12.1$
* $Date    : Apr-6-2011$
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


/* local function prototypes */

static void set_sys_dividers
(
    /* [IN] Clock 1 output divider value */
    uint_32 outdiv 
);

static void set_sys_dividers_end(void);

#if !PE_LDD_VERSION

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : pll_init
* Returned Value   : void
* Comments         :
*   Initialize PLL
*
*END*----------------------------------------------------------------------*/

static unsigned char pll_init(void) 
{
    void (*fcn_ram_call)(uint_32);

    uint_32 fcn_thumb_flag;
    uint_32 fcn_rom_addr;
    uint_32 fcn_ram_addr;
    
    /* 
     * Allocate stack space for set_sys_dividers() function copy 
     * The sizeof(set_sys_dividers_ram_copy) must be enough to 
     * fit whole set_sys_dividers() function.  
     */
    uint_32 fcn_ram_copy[64];
    uint_32 SIM_CLKDIV1_COPY;
    
    /* 
     * Copy set_sys_dividers() function to stack @ function_copy address 
     * Because Thumb-2 instruction mode is used its necessary to set 
     * bit[0] correctly to represent the opcode type of the branch target.
     * For details see:
     * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka12545.html
     */

    fcn_thumb_flag = (uint_32)set_sys_dividers & 0x01;
    fcn_rom_addr = (uint_32)set_sys_dividers & ~(uint_32)0x01;
    fcn_ram_addr = (uint_32)fcn_ram_copy | (fcn_rom_addr & 0x02);
    
    _mem_copy ((pointer)fcn_rom_addr, (pointer)fcn_ram_addr, sizeof(fcn_ram_copy)-3);
    
    /* Get pointer of set_sys_dividers function to run_in_ram_fcn  */
    fcn_ram_call = (void (*)(uint_32))(fcn_ram_addr | fcn_thumb_flag);
    
    /* 
     * First move to FBE mode
     * Enable external oscillator, RANGE=2, HGO=1, EREFS=1, LP=0, IRCS=0
     */
    MCG_C2 = MCG_C2_RANGE(2) | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK | MCG_C2_IRCS_MASK;

    /* Select external oscillator and Reference Divider and clear IREFS 
     * to start external oscillator
     * CLKS = 2, FRDIV = 3, IREFS = 0, IRCLKEN = 0, IREFSTEN = 0
     */
    MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);

    /* Wait for oscillator to initialize */
    while (!(MCG_S & MCG_S_OSCINIT_MASK)){};

    /* Wait for Reference Clock Status bit to clear */
    while (MCG_S & MCG_S_IREFST_MASK) {};
    
    /* Wait for clock status bits to show clock source 
     * is external reference clock */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2) {};
    
    /* Now in FBE
     * Configure PLL Reference Divider, PLLCLKEN=1, PLLSTEN=0, PRDIV=8
     * The crystal frequency is used to select the PRDIV value. 
     * Only even frequency crystals are supported
     * that will produce a 2MHz reference clock to the PLL.
     */

    MCG_C5 = MCG_C5_PRDIV(BSP_REF_CLOCK_DIV - 1) | MCG_C5_PLLCLKEN_MASK;

    /* Ensure MCG_C6 is at the reset default of 0. LOLIE disabled, 
     * PLL disabled, clock monitor disabled, PLL VCO divider is clear
     */
    MCG_C6 = 0;

    
    /* Calculate mask for System Clock Divider Register 1 SIM_CLKDIV1 */
    SIM_CLKDIV1_COPY =  SIM_CLKDIV1_OUTDIV1(BSP_CORE_DIV    - 1) |
                        SIM_CLKDIV1_OUTDIV2(BSP_BUS_DIV     - 1) |
                        SIM_CLKDIV1_OUTDIV3(BSP_FLEXBUS_DIV - 1) |
                        SIM_CLKDIV1_OUTDIV4(BSP_FLASH_DIV   - 1);

    /*
     * Set system clock dividers by function running from RAM
     * This routine must be placed in RAM. It is a workaround for errata e2448.
     */
    fcn_ram_call(SIM_CLKDIV1_COPY);
    
    /* Set the VCO divider and enable the PLL, 
     * LOLIE = 0, PLLS = 1, CME = 0, VDIV = 2MHz * BSP_CLOCK_MUL
     */
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(BSP_CLOCK_MUL - 24);

    /* wait for PLL status bit to set */
    while (!(MCG_S & MCG_S_PLLST_MASK)) {};
    
    /* Wait for LOCK bit to set */
    while (!(MCG_S & MCG_S_LOCK_MASK)) {};

    /* Now running PBE Mode */

    /* Transition into PEE by setting CLKS to 0
     * CLKS=0, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
     */
    MCG_C1 &= ~MCG_C1_CLKS_MASK;

    /* Wait for clock status bits to update */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3) {};

    /* Now running PEE Mode */
    
    return MQX_OK;
}

#endif /* !PE_LDD_VERSION */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : kinetis_clock_enable
* Returned Value   : void
* Comments         :
*   Enable clock to peripheral modules
*
*END*----------------------------------------------------------------------*/

void kinetis_clock_enable(void) 
{
  
    SIM_SCGC1 = 0xFFFFFFFF;
    SIM_SCGC2 = 0xFFFFFFFF;
    SIM_SCGC3 = 0xFFFFFFFF;

    /* USBOTG clock gating is turned on in _bsp_usb_io_init() function */
    SIM_SCGC4 = (0xFFFFFFFF - SIM_SCGC4_USBOTG_MASK);
    SIM_SCGC5 = 0xFFFFFFFF;
    SIM_SCGC6 = 0xFFFFFFFF;
    SIM_SCGC7 = 0xFFFFFFFF;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : kinetis_wdt_disable
* Returned Value   : void
* Comments         :
*   Disable watchdog timer
*
*END*----------------------------------------------------------------------*/

void kinetis_wdt_disable(void) 
{
    WDOG_MemMapPtr reg = WDOG_BASE_PTR;
    
    /* unlock watchdog */
    reg->UNLOCK = 0xc520;
    reg->UNLOCK = 0xd928;
    
    /* disable watchdog */
    reg->STCTRLH &= ~(WDOG_STCTRLH_WDOGEN_MASK);
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _bsp_flexbus_setup
* Returned Value   :  none
* Comments         :
*    Setup FlexBus pins for early MRAM operation
*
*END*----------------------------------------------------------------------*/
static void _bsp_flexbus_setup (void) 
{
    #define ALT5                    0x05
    #define OFF_CHIP_ACCESS_ALLOW   3  
    
    PORT_MemMapPtr  pctl;
    SIM_MemMapPtr   sim = SIM_BASE_PTR;
    
    /* Enable clock to FlexBus module */
    sim->SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;
    sim->SOPT2 |= SIM_SOPT2_FBSL(OFF_CHIP_ACCESS_ALLOW);
    
    pctl = (PORT_MemMapPtr)PORTE_BASE_PTR;
    pctl->PCR[6] = PORT_PCR_MUX(ALT5); /* FB_ALE */
    pctl->PCR[7] = PORT_PCR_MUX(ALT5); /* FB_CS0_b */
    pctl->PCR[8] = PORT_PCR_MUX(ALT5); /* FB_AD4 */
    pctl->PCR[9] = PORT_PCR_MUX(ALT5); /* FB_AD3 */
    pctl->PCR[10] = PORT_PCR_MUX(ALT5); /* FB_AD2 */
    pctl->PCR[11] = PORT_PCR_MUX(ALT5); /* FB_AD1 */
    pctl->PCR[12] = PORT_PCR_MUX(ALT5); /* FB_AD0 */
    
    pctl = (PORT_MemMapPtr)PORTA_BASE_PTR;
    pctl->PCR[6] = PORT_PCR_MUX(ALT5); /* FB_CLKOUT */
    pctl->PCR[7] = PORT_PCR_MUX(ALT5); /* FB_AD18 */
    pctl->PCR[8] = PORT_PCR_MUX(ALT5); /* FB_AD17 */
    pctl->PCR[9] = PORT_PCR_MUX(ALT5); /* FB_AD16 */
    pctl->PCR[10] = PORT_PCR_MUX(ALT5); /* FB_AD15 */
    pctl->PCR[11] = PORT_PCR_MUX(ALT5); /* FB_OE_b */  
    pctl->PCR[24] = PORT_PCR_MUX(ALT5); /* FB_AD14 */
    pctl->PCR[25] = PORT_PCR_MUX(ALT5); /* FB_AD13 */   
    pctl->PCR[26] = PORT_PCR_MUX(ALT5); /* FB_AD12 */
    pctl->PCR[27] = PORT_PCR_MUX(ALT5); /* FB_AD11 */
    pctl->PCR[28] = PORT_PCR_MUX(ALT5); /* FB_AD10 */
    pctl->PCR[29] = PORT_PCR_MUX(ALT5); /* FB_AD19 */
    
    pctl = (PORT_MemMapPtr)PORTD_BASE_PTR;
    pctl->PCR[10] = PORT_PCR_MUX(ALT5); /* FB_AD9 */
    pctl->PCR[11] = PORT_PCR_MUX(ALT5); /* FB_AD8 */
    pctl->PCR[12] = PORT_PCR_MUX(ALT5); /* FB_AD7 */
    pctl->PCR[13] = PORT_PCR_MUX(ALT5); /* FB_AD6 */
    pctl->PCR[14] = PORT_PCR_MUX(ALT5); /* FB_AD5 */
    pctl->PCR[15] = PORT_PCR_MUX(ALT5); /* FB_RW_b */
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_flexbus_mram_setup
* Returned Value   : 
* Comments         :
*    Setup FlexBus for MRAM operation
*
*END*----------------------------------------------------------------------*/
static void _bsp_flexbus_mram_setup (const uint_32 base_address)
{
    FB_MemMapPtr fb_ptr = FB_BASE_PTR;
    
    /* Enable external MRAM mapped on CS0 */
    /* CS0 base address */
    fb_ptr->CS[0].CSAR = base_address;
    /* CS0 control (8bit data, 1 wait state, multiplexed mode) */
    fb_ptr->CS[0].CSCR = FB_CSCR_ASET(1)  | 
                         FB_CSCR_AA_MASK  | 
                         FB_CSCR_WS(2)    | 
                         FB_CSCR_PS(1)    | 
                         FB_CSCR_BEM_MASK | 
                         FB_CSCR_BLS_MASK; 

    /* CS0 address mask and enable */
    fb_ptr->CS[0].CSMR = FB_CSMR_BAM(0x07) | FB_CSMR_V_MASK; 
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_flexbus_lcd_setup
* Returned Value   : 
* Comments         :
*    Setup FlexBus for LCD operation
*
*END*----------------------------------------------------------------------*/
void _bsp_flexbus_lcd_setup (const uint_32 base_address)
{
    FB_MemMapPtr fb_ptr = FB_BASE_PTR;
    
    /* Enable external LCD mapped on CS0 */
    fb_ptr->CS[0].CSAR = base_address; 
    fb_ptr->CS[0].CSCR = FB_CSCR_BLS_MASK | 
                         FB_CSCR_AA_MASK  | 
                         FB_CSCR_PS(2)    | 
                         FB_CSCR_BEM_MASK; 
    
    /* 
     * The address range is set to 128K because 
     * the DC signal is connected on address wire 
     */
    fb_ptr->CS[0].CSMR = FB_CSMR_BAM(1) | FB_CSMR_V_MASK;      
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_mpu_disable
* Returned Value   : void
* Comments         :
*   Disable memory protection unit.
*
*END*----------------------------------------------------------------------*/

static void _bsp_mpu_disable(void) 
{
    MPU_MemMapPtr mpu = MPU_BASE_PTR;
    /* Disable MPU */
    mpu->CESR &= ~MPU_CESR_VLD_MASK;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : kinetis_init
* Returned Value   : void
* Comments         :
*   Initialize Kinetis device.
*
*END*----------------------------------------------------------------------*/

void kinetis_init(void) 
{
#if PE_LDD_VERSION
    /*  Watchdog disabled by CPU bean (need to setup in CPU Inspector) */
    __pe_initialize_hardware();
    /* Enable clock to peripheral modules */
    kinetis_clock_enable();
    _bsp_mpu_disable();
    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
#else
    kinetis_wdt_disable();
    pll_init();
    /* Enable clock to peripheral modules */
    kinetis_clock_enable();
    _bsp_mpu_disable();
#endif
    /* Initialize FlexBus */
    _bsp_flexbus_setup();
    /* Initialize MRAM */
    _bsp_flexbus_mram_setup((uint_32)BSP_EXTERNAL_MRAM_RAM_BASE);
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : set_sys_dividers
* Returned Value   : void
* Comments         :
*   Flash prefetch must be disabled when the flash clock divider is changed.
*   This cannot be performed while executing out of flash.
*   There must be a short delay after the clock dividers are changed 
*   before prefetch can be re-enabled.
*   
*END*----------------------------------------------------------------------*/

static void set_sys_dividers
(
    /* [IN] SIM_CLKDIV1 mask */
    uint_32 outdiv 
)
{
    uint_32 FMC_PFAPR_backup;
    uint_32 i;
    volatile uint_32 dummy;    
    
    /* Store present value of FMC_PFAPR */
    FMC_PFAPR_backup = FMC_PFAPR; 
    
    /* Set M0PFD through M7PFD to 1 to disable prefetch */
    FMC_PFAPR |= FMC_PFAPR_M7PFD_MASK | FMC_PFAPR_M6PFD_MASK | 
                 FMC_PFAPR_M5PFD_MASK | FMC_PFAPR_M4PFD_MASK | 
                 FMC_PFAPR_M3PFD_MASK | FMC_PFAPR_M2PFD_MASK | 
                 FMC_PFAPR_M1PFD_MASK | FMC_PFAPR_M0PFD_MASK;
    
    /* Set SIM_CLKDIV1 mask */
    SIM_CLKDIV1 = outdiv;
    
    /* Wait for dividers to change */
    dummy = dummy;

    /* Re-store original value of FMC_PFAPR */  
    FMC_PFAPR = FMC_PFAPR_backup; 
}
/* Do not add any code between set_sys_dividers and set_sys_dividers_end functions. */
static void set_sys_dividers_end(void)
{
}


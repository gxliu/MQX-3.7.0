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
* $Version : 3.6.21.0$
* $Date    : Feb-8-2011$
*
* Comments:
*
*   This file contains flash boot code to initialize chip selects,
*   sdram controler, disable the watchdog timer and initialize the PLL.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"

#pragma define_section init ".init" far_absolute R

static void _bsp_flexbus_mram_setup (const uint_32 base_address);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : pll_init
* Returned Value   : void
* Comments         :
*   Initialize PLL - this function must be executed from SRAM (or Flash)
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void pll_set(void) {
    VMCF5441_STRUCT_PTR reg = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();
    /* pll */
    reg->CCM.MISCCR |= MCF54XX_CCM_MISCCR_LIMP;
    
    reg->PLL.DR = MCF5441_PLL_DR_OUTDIV5(14 - 1)   /* NAND clk fnfc = fvco / 14 */ 
        | MCF5441_PLL_DR_OUTDIV4(8 - 1)            /* fusb = fvco / 8 ; in fact, the 60MHz reference is taken from an external ULPI chip */
        | MCF5441_PLL_DR_OUTDIV3(2 - 1)            /* ffb_clk = fvco / 2 */
        | MCF5441_PLL_DR_OUTDIV2(4 - 1)            /* fbus = fsys / 2 = fvco / 4 */
        | MCF5441_PLL_DR_OUTDIV1(2 - 1);           /* fsys = fvco / 2 */

    reg->PLL.CR = MCF5441_PLL_CR_LOLEN | MCF5441_PLL_CR_FBKDIV(10 - 1);     /* fvco = 10 * 50MHz = 500MHz */

    reg->CCM.MISCCR &= ~MCF54XX_CCM_MISCCR_LIMP;
    
    while (!(reg->PLL.SR & MCF5441_PLL_SR_LOCK)) {
        /* _ASM_NOP(); */    
    };
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : pll_init
* Returned Value   : void
* Comments         :
*   Initialize PLL
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void pll_init(void) {

#if 1   /* set to zero for internal SRAM target */
    char *dst = (char*)&__INTERNAL_SRAM_BASE;
    char *src = (char*)&pll_set;
    unsigned long size = 200; /* pll_set code length */
    void (_CODE_PTR_ pll_set_in_sram)(void);

    /* copy pll_set function to sram */
    if (dst != src) {
        while (size--) {
            *((char *)dst)++ = *((char *)src)++;
        }

        /* process from sram */
        pll_set_in_sram = (void (_CODE_PTR_)(void))&__INTERNAL_SRAM_BASE;
        pll_set_in_sram();
    }
    
#else
    pll_set();
#endif
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : ram_init
* Returned Value   : void
* Comments         :
*   Initialize chip selects and SDRAM controller
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void ram_init(void) {
}

SDRAM_INFO sdraminf = { SDRAM_DDR2, 14, 10, 8, CASL_5, 10, 12, 8, 16, 20, 10, 0x0b, 44, 70000, 56, 152, 8, 7800, 2, 8 };


static void sdram_init (uint_32 sd_clk_per, SDRAM_INFO sdram_params) {
    uint_32 temp, temp2;    /* temp variables used to store intermediate register and field values */
    VMCF5441_STRUCT_PTR reg = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();
    VMCF5441_DDRMC_STRUCT_PTR ddrmc = (VMCF5441_DDRMC_STRUCT_PTR)&reg->DDRMC;
    
    /*  Test to make sure that the SDRAMC has not already been initialized before
     *  starting. If it has, then we do not want to re-init.
     */
    if(!(ddrmc->DDR_CR09 & MCF5441_DDRMC_DDR_CR09_START)) {
        /* Need to parameterize this later. Right now it is hard coded for full strength DDR2 */
        reg->GPIO.MSCR_SDRAMC = 0x01;

        /* DDR PHY initialization */
        ddrmc->DDR_PHY_RCR_CTRL = 0x00000000;       /* Disable RCR */
        ddrmc->DDR_PHY_RCR_CTRL |= MCF5441_DDRMC_DDR_PHY_RCR_CTRL_RCR_RST;      /* Force RCR soft reset */
      
        /* Are these the correct settings to use for DDR1, or just for DDR2? */
        ddrmc->DDR_PHY_PAD_CTRL = (MCF5441_DDRMC_DDR_PHY_PAD_CTRL_PAD_ODT_CS0(0x1)
                                | MCF5441_DDRMC_DDR_PHY_PAD_CTRL_OFFSET_VALUE(0x3)
                                | MCF5441_DDRMC_DDR_PHY_PAD_CTRL_PAD_DEBUG(0x2)
                                | MCF5441_DDRMC_DDR_PHY_PAD_CTRL_SPARE_DLY_CTRL(0x3)
                                );
        
        ddrmc->DDR_CR02 = (MCF5441_DDRMC_DDR_CR02_BIGEND); /* enable big endian mode */
                        
        /* Enable differential DQS mode if using DDR2 */
      	ddrmc->DDR_CR03 = MCF5441_DDRMC_DDR_CR03_DQSBEN;
    
        /* To initialize CTL4 we need to determine the number of banks in the memory */
        switch (sdram_params.num_banks) {
            case 4: 
                temp = 0;   /* bit is cleared for 4 banks */
                break;
            case 8: 
                temp = MCF5441_DDRMC_DDR_CR04_8BNK;     /* bit is set for 8 banks */
                break;
            default: 
                /* ERR! Unsupported number of banks. */
                break;
        }
    
        ddrmc->DDR_CR04 = 	(temp /* use the setting for banks determined by case statement above */
                           	| MCF5441_DDRMC_DDR_CR04_QKREF
                        	);

        ddrmc->DDR_CR06 = 	(MCF5441_DDRMC_DDR_CR06_ODT_ALT_EN    /* ODT and CASL3 supported, documentation says this bit must be set */
                           	| MCF5441_DDRMC_DDR_CR06_ODT_ADD_TURN_CLK_EN /* add turnaround clock between back to back reads to different banks */
                        	);
                        
        ddrmc->DDR_CR08 = (MCF5441_DDRMC_DDR_CR08_REDUC); /* 8-bit port width */

        ddrmc->DDR_CR10 = (MCF5441_DDRMC_DDR_CR10_TREF_ENABLE);    /* enable controller to refresh the memory */
                    
        /* Will need to parameterize the FIFO_TYPE_REG settings eventually */                   
        ddrmc->DDR_CR11 = MCF5441_DDRMC_DDR_CR11_AHB0_FIFO_TYPE_REG(0x3);   /* synchronous mode */
                        
        ddrmc->DDR_CR12 = 	(MCF5441_DDRMC_DDR_CR12_CSMAP(1) /* enable chip select, right now this is a two bit field, but only one CS on MCF5441x */
                          	| MCF5441_DDRMC_DDR_CR12_AHB1_FIFO_TYPE_REG(0x3) /* synchronous mode */
                        	);  

        ddrmc->DDR_CR13 = 0;
                    
        ddrmc->DDR_CR14 = MCF5441_DDRMC_DDR_CR14_ODT_WR_MAP_CS0(1); /* enable write ODT for a chip select, right now this is a two bit field */
                    
        /* Calculate difference between max addr pins (16) and actual number of 
        * address lines used in order to initialize CTL15[ADDPINS] */
        temp = 16 - sdram_params.num_row_addr;
    
        /* Error check to make sure num of row addresses field is valid */
        /* Not sure what actual max value for the ADDPINS field is
        * so I might need to revisit this. */
        ddrmc->DDR_CR15 = (MCF5441_DDRMC_DDR_CR15_ADDR_PINS(temp)   /* allows controller to determine number of row addresses */
                            | MCF5441_DDRMC_DDR_CR15_RTT_0(0x1) /* set ODT termination resistance, use 75 ohm for now */
                            | MCF5441_DDRMC_DDR_CR15_Q_FULLNESS(0x1)    /* not really sure what this is used for, might be a status bit */
                        );
                    
        /* Calculate difference between max col pins (12) and actual number of 
        * column address lines used in order to initialize CTL16[COLSIZ] */
        temp = 12 - sdram_params.num_col_addr;
    
        /* Error check to make sure num of col addresses field is valid */
        /* Not sure what actual max value for the COLSIZ field is
        * so I might need to revisit this. */
                                                                        
        /* Calculate CASLAT field value based on passed in casl value  */
        if (sdram_params.casl == CASL_2_5)      
            temp2 = 0x6;  /* This is the DDR1 mode reg value for CASL = 2.5 */
        else
            temp2 = sdram_params.casl; /* For whole num CASL values, the mode reg setting matches the CASL */

        ddrmc->DDR_CR16 = (MCF5441_DDRMC_DDR_CR16_COLUMN_SIZE(temp)
        /*                      | MCF5441_DDRMC_DDR_CR16_CKE_DELAY(0) // additional cycles to delay CKE for status reporting */
                                | MCF5441_DDRMC_DDR_CR16_CASLAT(temp2)
                        );                  
                        
        ddrmc->DDR_CR17 = (MCF5441_DDRMC_DDR_CR17_TDFI_CTRL_DELAY(0x2) /* delay for power-down or self refresh; this value comes from old ddr2_init routine, not sure if this is really right */
                                | MCF5441_DDRMC_DDR_CR17_TCKE(0x3) /* min CKE pulse width, value comes from old ddr2_init */
        /*                      | MCF5441_DDRMC_DDR_CR17_COMMAND_AGE_COUNT // command aging counter */
                        );
                        
        ddrmc->DDR_CR18 = (MCF5441_DDRMC_DDR_CR18_TRRD((int)((sdram_params.trrd/sd_clk_per) + 1)) /* active to active delay */
        /*                      | MCF_DDR_CR18_TRRD((int)((sdram_params.trrd/sd_clk_per) + 0.5)) // active to active delay */
                                | MCF5441_DDRMC_DDR_CR18_TDFI_DRAM_CLK_ENABLE(0x1)
                                | MCF5441_DDRMC_DDR_CR18_TDFI_DRAM_CLK_DISABLE(0x2) /* cycles to needed to disable PHY clock, 0x2 is recommended setting */
                        );

        /* Forcing to DDR2 selection since memtype passing isn't working correctly */                       
        /* Determine the WRLAT value to use in CTL19 */
        temp = sdram_params.casl - 1;

        ddrmc->DDR_CR19 = (MCF5441_DDRMC_DDR_CR19_APREBIT(0xA) /* location of AP bit, set to 10 for now might need to make this a variable later */
                                | MCF5441_DDRMC_DDR_CR19_WRLAT(temp)
                                | MCF5441_DDRMC_DDR_CR19_TWTR((int)((sdram_params.twtr/sd_clk_per) + 1)) /* write to read delay */
                                | MCF5441_DDRMC_DDR_CR19_TRTP((int)((sdram_params.trtp/sd_clk_per) + 1)) /* read to precharge delay */
                        );
                    
        /* Determine value for CASLAT field in CTL20 */
        temp = sdram_params.casl << 1;  /* shift CASL by one bit. this makes space for the fractional component */
        if (sdram_params.casl > 0x200)  /* determine if the CASL has a fractional component */
        {
            temp |= 0x1;    /* set bit 1 to add 0.5 */
            temp &= ~0x200; /* clear the upper bit used for indicating the fraction in the original value */
        }               
                    
        ddrmc->DDR_CR20 = (MCF5441_DDRMC_DDR_CR20_INITAREF(0x2) /* # of refreshes needed during init sequence, need 2 for DDR1 and DDR2 */
                                | MCF5441_DDRMC_DDR_CR20_CASLAT_LIN(temp) /* CASL value */
                        );
                    
        ddrmc->DDR_CR21 = (MCF5441_DDRMC_DDR_CR21_TDFI_PHY_RDLAT(0x5) /* PHY read latency, current value comes from old ddr2_init */
                                | MCF5441_DDRMC_DDR_CR21_TDAL((int)((sdram_params.twr/sd_clk_per) + (sdram_params.trp/sd_clk_per) + 1))
                        );
                    
        ddrmc->DDR_CR22 = ( 0
                                | MCF5441_DDRMC_DDR_CR22_TRP((int)((sdram_params.trp/sd_clk_per) + 1))
                                | MCF5441_DDRMC_DDR_CR22_TDFI_RDDATA_EN_BASE(0x2) /* DFI read data enable timing parameter, manual says set to 0x2 */
                                | MCF5441_DDRMC_DDR_CR22_TDFI_PHY_WRLAT_BASE(0x2) /* DFI write latency timing parameter, manual says set to 0x2 */
                        );
                    
        ddrmc->DDR_CR23 = ( 0
                                | MCF5441_DDRMC_DDR_CR23_TWR_INT((int)((sdram_params.twr/sd_clk_per) + 1)) /* write recovery time */
                         );
                    
        ddrmc->DDR_CR24 = ( 0
                                | MCF5441_DDRMC_DDR_CR24_TMRD((int)(sdram_params.tmrd)) /* mode register command time */
                                | MCF5441_DDRMC_DDR_CR24_TFAW((int)((sdram_params.tfaw/sd_clk_per) + 1)) /* bank activate period */
                        );
                    
        ddrmc->DDR_CR25 =	(MCF5441_DDRMC_DDR_CR25_TRAS_MIN((int)((sdram_params.tras_min/sd_clk_per) + 1)) /* active to precharge time */
                            | MCF5441_DDRMC_DDR_CR25_TRC((int)((sdram_params.trc/sd_clk_per) + 1)) /* active to active time */
                        	);
                    
        ddrmc->DDR_CR26 = 	(MCF5441_DDRMC_DDR_CR26_INT_MASK(0xFFF)
                           	| MCF5441_DDRMC_DDR_CR26_TRFC((int)((sdram_params.trfc/sd_clk_per) + 1)) /* refresh command period */
                            | MCF5441_DDRMC_DDR_CR26_TRCD_INT((int)((sdram_params.trcd/sd_clk_per) + 1)) /* active to read/write delay */
                        	);                                                                                                                                                                                                                                      

        ddrmc->DDR_CR31 = 	(MCF5441_DDRMC_DDR_CR31_TREF((int)((sdram_params.trefi/sd_clk_per) - 1))); /* # of cycles between refreshes */
                    
        ddrmc->DDR_CR41 = MCF5441_DDRMC_DDR_CR41_TCPD(0x0002); /* clock enable to PRE delay, couldn't find in DRAM spec current setting comes from old ddr2_init */
                    
        ddrmc->DDR_CR42 = 	(MCF5441_DDRMC_DDR_CR42_TRAS_MAX((int)((sdram_params.tras_max/sd_clk_per) + 1)) /* max row active time */
                          	| MCF5441_DDRMC_DDR_CR42_TPDEX(sdram_params.xard) /* power down exit time */
                        	);                  
    
        ddrmc->DDR_CR43 = 	(MCF5441_DDRMC_DDR_CR43_TXSR(0x1) /* self refresh exit time is spec'd in ps, so for MCF54451x we can assume 1 */
                          	| MCF5441_DDRMC_DDR_CR43_TXSNR((int)(((sdram_params.trfc + 10)/sd_clk_per) + 1)) /* exit self refresh to non-read command delay */
                       	 	);
                    
        ddrmc->DDR_CR45 = MCF5441_DDRMC_DDR_CR45_TINIT(0x61A8); /* initialization startup time (200us), might need to parameterize this later */
    
        ddrmc->DDR_CR56 = 	( 0
        					/* forcing to DDR2 right now since memtype isn't passing correctly */
                            | MCF5441_DDRMC_DDR_CR56_DRAM_CLASS(0x4) /* setup controller for DDR1 or DDR2 mode */
                        	);
    
        ddrmc->DDR_CR57 = 	(MCF5441_DDRMC_DDR_CR57_TMOD((int)((sdram_params.tmod/sd_clk_per) + 1)) /* mrs to ODT enable delay */
                            | MCF5441_DDRMC_DDR_CR57_WRLAT_ADJ(sdram_params.casl - 1) /* PHY write latency adjustment, current value comes from old ddr2_init */
                            | MCF5441_DDRMC_DDR_CR57_RDLAT_ADJ(sdram_params.casl) /* PHY read latency adjustment, current value comes from old ddr2_init */
                        	);                                  

        ddrmc->DDR_CR58 = (MCF5441_DDRMC_DDR_CR58_EMRS1_DATA_0(0x4004)  /* set ODT resistance to 75 ohms */
                                );
                    
        /* CTL59 sets up EMR3, but DDR2 spec has all bits reserved */
        ddrmc->DDR_CR59 = 0xC0004004;
                    
        /* Calculate the value for mode register */
        temp = sdram_params.casl << 20; /* start with the CASL field value starting at bit 4 */
        temp |= 0x0002C000;                 /* set burst length to 4 */
        
        /* Calculate write recovery time */
        temp2 = ((int)( (sdram_params.twr/sd_clk_per) + 1))<<24;
        
        ddrmc->DDR_CR60 = (temp|temp2);

        /* Temp value, not really sure if this is needed. If it is need to use caculated mode register value above */                       
        ddrmc->DDR_CR61 = 0x00000242;                       

        /* Now that all the registers are setup, write the CTL9[START] bit to begin initialization sequence */
        ddrmc->DDR_CR09 |= MCF5441_DDRMC_DDR_CR09_START;
    
        /* Wait for init to complete */
        while (!(ddrmc->DDR_CR27 & (1 << 3))) {
            _ASM_NOP();
        }
    }
    
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf5441_init
* Returned Value   : void
* Comments         :
*   Initialize CPU speed and chip selects.  Called from vectors.cw boot
* sequence before calling the runtime application startup code.
*
*END*----------------------------------------------------------------------*/

__declspec(init) far void mcf5441_init(void) {
    VMCF5441_STRUCT_PTR reg = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();

    reg->SCM_PMM.PMM.PPMCR0 = 18;   /* ICTRL0 */
    reg->SCM_PMM.PMM.PPMCR0 = 19;   /* ICTRL1 */
    reg->SCM_PMM.PMM.PPMCR0 = 20;   /* ICTRL2 */
    
    reg->SCM_PMM.PMM.PPMCR0 = 32;   /* PIT0 */
    reg->SCM_PMM.PMM.PPMCR0 = 33;   /* PIT1 */
    reg->SCM_PMM.PMM.PPMCR0 = 34;   /* PIT2 */
    reg->SCM_PMM.PMM.PPMCR0 = 35;   /* PIT3 */
    
    reg->SCM_PMM.PMM.PPMCR0 = 46;   /* SDRAM */


    /* pll */
    /* pll_init(); // already initialized by the debugger */
    
    /* sdram */
    sdram_init(4, sdraminf);

    /* Setup GPIO pin to Flexbus mode for usage in this BSP */
    _bsp_flexbus_io_init();
   
    /* init MRAM */
    _bsp_flexbus_mram_setup((uint_32)BSP_EXTERNAL_MRAM_BASE);
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
    VMCF5XXX_FB_STRUCT_PTR fb_ptr = &((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->FB[0];
    
    fb_ptr->CSAR = MCF5XXX_FBCS_CSAR_BA(base_address);

    fb_ptr->CSCR = MCF5XXX_FBCS_CSCR_WS(0x20)  /* wait states */
                  | MCF5XXX_FBCS_CSCR_AA        /* internal ack */
                  | MCF5XXX_FBCS_CSCR_PS_8;     /* data bus width */

    fb_ptr->CSMR = MCF5XXX_FBCS_CSMR_BAM_64K  /* 64 KB data mask */
                  | MCF5XXX_FBCS_CSMR_V;       /* cs1 is valid */
}



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_flexbus_mram_setup
* Returned Value   : 
* Comments         :
*    Setup flexbus for mram operation
*
*END*----------------------------------------------------------------------*/
static void _bsp_flexbus_mram_setup (const uint_32 base_address)
{
    VMCF5XXX_FB_STRUCT_PTR fb_ptr = &((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->FB[0];
    
    /* Enable external MRAM mapped on CS0 */
    fb_ptr->CSAR = MCF5XXX_FBCS_CSAR_BA(base_address); /* CS0 base address */
    fb_ptr->CSCR = 0x00000540; /* CS control (8bit data, 1 waitstate) */
    fb_ptr->CSMR = 0x00070001; /* CS address mask and enable */
}
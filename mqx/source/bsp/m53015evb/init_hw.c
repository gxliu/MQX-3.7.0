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
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
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

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : pll_init
* Returned Value   : void
* Comments         :
*   Initialize PLL - this function must be executed from SRAM (or Flash)
*
*END*----------------------------------------------------------------------*/

#pragma define_section init ".init" far_absolute R

 __declspec(init) far static void pll_set(void) {
    VMCF5301_STRUCT_PTR reg = (VMCF5301_STRUCT_PTR)_PSP_GET_IPSBAR();

    /* pll */
    reg->CCM.MISCCR |= MCF53XX_CCM_MISCCR_LIMP;    
    reg->PLL.PCR = MCF5301_PLL_CR_FBKDIV(0x2F) /* 47 fvco = (47 + 1)/(2^1) * 20MHz = 480MHz */
        | MCF5301_PLL_CR_REFDIV(1);
    reg->PLL.PDR = MCF5301_PLL_DR_OUTDIV4(7)   /* fusb = fvco / 8 = 60MHz */
        | MCF5301_PLL_DR_OUTDIV3(2)            /* fsdram = fvco / 3 = 160MHz */
        | MCF5301_PLL_DR_OUTDIV2(5)            /* ffb_clk = fsys / 2 = fvco / 6 = 80MHz */
        | MCF5301_PLL_DR_OUTDIV1(1);           /* fsys = fvco / 2 = 240MHz */
    
    reg->CCM.MISCCR &= ~MCF53XX_CCM_MISCCR_LIMP;
    while (!(reg->PLL.PSR & MCF5301_PLL_SR_LOCK)) {
    	/* nop */    
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
        
    char *dst = (char*)&__INTERNAL_SRAM_BASE;
    char *src = (char*)&pll_set;    
    void (_CODE_PTR_ pll_init_in_sram)(void);    
    /* pll_set code length (safe) */
    unsigned long size = 200; 

    /* copy pll_set function to sram */
    if (dst != src) 
    {
        while (size--) {
            *((char *)dst)++ = *((char *)src)++;
        }

        /* run from sram */        
        pll_init_in_sram = (void (_CODE_PTR_)(void))&__INTERNAL_SRAM_BASE;
        pll_init_in_sram();
    }
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
    _mqx_int i;
    VMCF5301_STRUCT_PTR reg = (VMCF5301_STRUCT_PTR)_PSP_GET_IPSBAR();
    VMCF53XX_SDRAM_CTRL_STRUCT_PTR sdramc = &((VMCF5301_STRUCT_PTR)_PSP_GET_IPSBAR())->SDRAMC;

    if (!(sdramc->SDCR & MCF53XX_SDRAMC_SDCR_REF_EN)) {
        sdramc->SDCR &= ~MCF53XX_SDRAMC_SDCR_REF_EN;

        reg->GPIO.MSCR_2 = MCF5301_GPIO_MSCR2(MCF5301_GPIO_MSCR_SDRAM_SDXXX_FS_LPDDR);
                
        /* SDRAM chip select initialization */
        sdramc->SDCS0 = MCF53XX_SDRAMC_SDCS_BA((uint_32)BSP_RAM_BASE)
            | MCF53XX_SDRAMC_SDCS_CSSZ(MCF53XX_SDRAMC_SDCS_CSSZ_64MBYTE);

        /* 
        ** Basic configuration and initialization 
        */         
        sdramc->SDCFG1 = MCF53XX_SDRAMC_SDCFG1_SRD2RWP(4)
		    | MCF53XX_SDRAMC_SDCFG1_SWT2RWP(3)
		    | MCF53XX_SDRAMC_SDCFG1_RD_LAT(7)
		    | MCF53XX_SDRAMC_SDCFG1_ACT2RW(1)
		    | MCF53XX_SDRAMC_SDCFG1_PRE2ACT(1)
		    | MCF53XX_SDRAMC_SDCFG1_REF2ACT(6)
		    | MCF53XX_SDRAMC_SDCFG1_WT_LAT(3);
           
	    sdramc->SDCFG2 = MCF53XX_SDRAMC_SDCFG2_BRD2RP(5)
		    | MCF53XX_SDRAMC_SDCFG2_BWT2RWP(6)
		    | MCF53XX_SDRAMC_SDCFG2_BRD2W(6)
		    | MCF53XX_SDRAMC_SDCFG2_BL(7);
		    
       /* 
        ** Precharge and enable write to SDMR 
        */
       sdramc->SDCR = MCF53XX_SDRAMC_SDCR_MODE_EN | MCF53XX_SDRAMC_SDCR_CKE
		   | MCF53XX_SDRAMC_SDCR_DDR_MODE | MCF53XX_SDRAMC_SDCR_ADDR_MUX(1)
		   | MCF53XX_SDRAMC_SDCR_REF_CNT(9)
		   | MCF53XX_SDRAMC_SDCR_MEM_PS | MCF53XX_SDRAMC_SDCR_IPALL;
		         
		 /* 
        ** Perform two refresh cycles 
        */
	    sdramc->SDCR |= MCF53XX_SDRAMC_SDCR_IREF;
	    sdramc->SDCR |= MCF53XX_SDRAMC_SDCR_IREF;
	    
	    /* 
        ** Write extended mode register 
        */
	    sdramc->SDMR = MCF53XX_SDRAMC_SDMR_BK(0) | MCF53XX_SDRAMC_SDMR_AD(0x33) | MCF53XX_SDRAMC_SDMR_CMD;

        /* 
        ** Write mode register and reset DLL 
        */
	    sdramc->SDMR = MCF53XX_SDRAMC_SDMR_BK(2) | MCF53XX_SDRAMC_SDMR_AD(0x00) | MCF53XX_SDRAMC_SDMR_CMD;
      
        /*
        ** Execute a PALL command 
        */
	    sdramc->SDCR |= MCF53XX_SDRAMC_SDCR_IPALL;

        /*
        ** Enable auto refresh and lock SDMR 
        */
	    sdramc->SDCR &= ~MCF53XX_SDRAMC_SDCR_MODE_EN;
       sdramc->SDCR |= (MCF53XX_SDRAMC_SDCR_REF_EN | MCF53XX_SDRAMC_SDCR_DQS_OE(0x3));	    

    
    }
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : flash_init
* Returned Value   : void
* Comments         :
*   Initialize chip selects for FLASH
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void flash_init(void) {
    VMCF5301_STRUCT_PTR reg = (VMCF5301_STRUCT_PTR)_PSP_GET_IPSBAR();
    MCF5XXX_FB_STRUCT_PTR fbcs = (MCF5XXX_FB_STRUCT_PTR)((VMCF5301_STRUCT_PTR)_PSP_GET_IPSBAR())->FB;

    fbcs[0].CSAR = MCF5XXX_FBCS_CSAR_BA((uint_32)BSP_FLASH_BASE);
    fbcs[0].CSCR = MCF5XXX_FBCS_CSCR_WS(7) | MCF5XXX_FBCS_CSCR_SBM | MCF5XXX_FBCS_CSCR_AA | MCF5XXX_FBCS_CSCR_PS_16 | MCF5XXX_FBCS_CSCR_BEM;
    fbcs[0].CSMR = MCF5XXX_FBCS_CSMR_BAM_16M | MCF5XXX_FBCS_CSMR_V;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mram_init
* Returned Value   : void
* Comments         :
*   Initialize chip selects for MRAM
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void mram_init(void) {
    VMCF5301_STRUCT_PTR reg = (VMCF5301_STRUCT_PTR)_PSP_GET_IPSBAR();
    MCF5XXX_FB_STRUCT_PTR fbcs = (MCF5XXX_FB_STRUCT_PTR)((VMCF5301_STRUCT_PTR)_PSP_GET_IPSBAR())->FB;

    fbcs[1].CSAR = MCF5XXX_FBCS_CSAR_BA((uint_32)BSP_EXTERNAL_MRAM_RAM_BASE);
    fbcs[1].CSCR = MCF5XXX_FBCS_CSCR_WS(7) | MCF5XXX_FBCS_CSCR_SBM | MCF5XXX_FBCS_CSCR_AA | MCF5XXX_FBCS_CSCR_PS_16 | MCF5XXX_FBCS_CSCR_BEM;
    fbcs[1].CSMR = MCF5XXX_FBCS_CSMR_BAM_512K | MCF5XXX_FBCS_CSMR_V;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf5301_init
* Returned Value   : void
* Comments         :
*   Initialize CPU speed and chip selects.  Called from vectors.cw boot
* sequence before calling the runtime application startup code.
*
*END*----------------------------------------------------------------------*/

__declspec(init) far void mcf5301_init(void) {
    VMCF5301_STRUCT_PTR reg = (VMCF5301_STRUCT_PTR)_PSP_GET_IPSBAR();
    
    /* pll */
    pll_init();
    
    /* sdram */
    ram_init();
    
    /* mram init */
    mram_init();
    
    /* flash init */
    flash_init();
}

/* EOF */
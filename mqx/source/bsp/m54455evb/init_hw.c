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
* $Version : 3.6.13.0$
* $Date    : Jun-4-2010$
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
    VMCF5445_STRUCT_PTR reg = (VMCF5445_STRUCT_PTR)_PSP_GET_IPSBAR();

    // pll
    reg->CCM.MISCCR |= MCF54XX_CCM_MISCCR_LIMP;
    reg->PLL.PCR = MCF5445_PLL_PCR_PFDR(16)     // fvco = 16 * 33MHz = 528MHz
        | MCF5445_PLL_PCR_OUTDIV5(8)            // fusb = fvco / 9 = 58.67MHz
        | MCF5445_PLL_PCR_OUTDIV4(0)            // fpci = fvco / 1 = 
        | MCF5445_PLL_PCR_OUTDIV3(7)            // ffb_clk = fvco / 8 = 66MHz
        | MCF5445_PLL_PCR_OUTDIV2(3)            // fbus = fsys / 2 = fvco / 4 = 132MHz
        | MCF5445_PLL_PCR_OUTDIV1(1);           // fsys = fvco / 2 = 264MHz;
    
    reg->CCM.MISCCR &= ~MCF54XX_CCM_MISCCR_LIMP;
    while (!(reg->PLL.PSR & MCF5445_PLL_PSR_LOCK)) {
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
    
    char *dst = (char*)&__INTERNAL_SRAM_BASE;
    char *src = (char*)&pll_set;
    unsigned long size = 200; // pll_set code length
    void (_CODE_PTR_ pll_set_in_sram)(void);

    // copy pll_set function to sram
    if (dst != src) {
        while (size--) {
            *((char *)dst)++ = *((char *)src)++;
        }

        // process from sram        
        pll_set_in_sram = (void (_CODE_PTR_)(void))&__INTERNAL_SRAM_BASE;
        pll_set_in_sram();
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
    VMCF5445_STRUCT_PTR reg = (VMCF5445_STRUCT_PTR)_PSP_GET_IPSBAR();
    VMCF54XX_SDRAM_CTRL_STRUCT_PTR sdramc = &((VMCF5445_STRUCT_PTR)_PSP_GET_IPSBAR())->SDRAMC;

    if (!(sdramc->SDCR & MCF54XX_SDRAMC_SDCR_REF_EN)) {
        sdramc->SDCR &= ~MCF54XX_SDRAMC_SDCR_REF_EN;

        reg->GPIO.MSCR_SDRAM = MCF5445_GPIO_MSCR_SDRAM_SDDATA(MCF5445_GPIO_MSCR_SDRAM_SDXXX_DDR2)
            | MCF5445_GPIO_MSCR_SDRAM_SDDQS(MCF5445_GPIO_MSCR_SDRAM_SDXXX_DDR2)
            | MCF5445_GPIO_MSCR_SDRAM_SDCLK(MCF5445_GPIO_MSCR_SDRAM_SDXXX_DDR2)
            | MCF5445_GPIO_MSCR_SDRAM_SDCTL(MCF5445_GPIO_MSCR_SDRAM_SDXXX_DDR2);
        
        sdramc->SDCS0 = MCF54XX_SDRAMC_SDCS_BA((uint_32)BSP_RAM_BASE) | MCF54XX_SDRAMC_SDCS_CSSZ(MCF54XX_SDRAMC_SDCS_CSSZ_128MBYTE);
        sdramc->SDCS1 = MCF54XX_SDRAMC_SDCS_BA((uint_32)BSP_RAM_BASE + (BSP_RAM_SIZE / 2)) | MCF54XX_SDRAMC_SDCS_CSSZ(MCF54XX_SDRAMC_SDCS_CSSZ_128MBYTE);
        
        sdramc->SDCFG1 = MCF54XX_SDRAMC_SDCFG1_SRD2RWP(6) 
            | MCF54XX_SDRAMC_SDCFG1_SWT2RWP(5) | MCF54XX_SDRAMC_SDCFG1_RD_LAT(3)
            | MCF54XX_SDRAMC_SDCFG1_ACT2RW(1) | MCF54XX_SDRAMC_SDCFG1_PRE2ACT(1) 
            | MCF54XX_SDRAMC_SDCFG1_REF2ACT(6) | MCF54XX_SDRAMC_SDCFG1_WT_LAT(1);
            
        sdramc->SDCFG2 = MCF54XX_SDRAMC_SDCFG2_BRD2RP(5) | MCF54XX_SDRAMC_SDCFG2_BWT2RWP(9) 
            | MCF54XX_SDRAMC_SDCFG2_BRD2W(6) | MCF54XX_SDRAMC_SDCFG2_BL(7);

        // 7.8us (ind 3.9us) tREFI, 133MHz -> REF_CNT = 7 (3.9us) 15 (7.8us)
        sdramc->SDCR = MCF54XX_SDRAMC_SDCR_MODE_EN | MCF54XX_SDRAMC_SDCR_CKE 
            | MCF54XX_SDRAMC_SDCR_DDR_MODE | MCF54XX_SDRAMC_SDCR_DDR2_MODE
            | MCF54XX_SDRAMC_SDCR_ADDR_MUX(2) | MCF54XX_SDRAMC_SDCR_REF_CNT(11)
            | MCF54XX_SDRAMC_SDCR_MEM_PS | MCF54XX_SDRAMC_SDCR_IPALL;
            
        sdramc->SDMR = MCF54XX_SDRAMC_SDMR_BK(1) | MCF54XX_SDRAMC_SDMR_AD(0) | MCF54XX_SDRAMC_SDMR_CMD | MCF54XX_SDRAMC_SDMR_DDR2_AD(0x408);
        sdramc->SDMR = MCF54XX_SDRAMC_SDMR_BK(0) | MCF54XX_SDRAMC_SDMR_AD(0) | MCF54XX_SDRAMC_SDMR_CMD | MCF54XX_SDRAMC_SDMR_DDR2_AD(0x333);

        // few clocks wait time (not needed because DLL lock time is 2 memory clocks)
        /* for (i = 0; i < 10; i++) { 
            _ASM_NOP(); 
        }  
        */
        
        sdramc->SDCR |= MCF54XX_SDRAMC_SDCR_MODE_EN | MCF54XX_SDRAMC_SDCR_IPALL;
        
        sdramc->SDCR |= MCF54XX_SDRAMC_SDCR_IREF;   
        sdramc->SDCR |= MCF54XX_SDRAMC_SDCR_IREF;

        sdramc->SDMR = MCF54XX_SDRAMC_SDMR_BK(0) | MCF54XX_SDRAMC_SDMR_AD(0) | MCF54XX_SDRAMC_SDMR_CMD | MCF54XX_SDRAMC_SDMR_DDR2_AD(0x233);
        
        sdramc->SDCR &= ~MCF54XX_SDRAMC_SDCR_MODE_EN;
        sdramc->SDCR |= MCF54XX_SDRAMC_SDCR_REF_EN | MCF54XX_SDRAMC_SDCR_DQS_OE(3);

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
    VMCF5445_STRUCT_PTR reg = (VMCF5445_STRUCT_PTR)_PSP_GET_IPSBAR();
    MCF5XXX_FB_STRUCT_PTR fbcs = (MCF5XXX_FB_STRUCT_PTR)((VMCF5445_STRUCT_PTR)_PSP_GET_IPSBAR())->FB;

    // Boot Flash: AT49BV040 (default UBoot)
    fbcs[0].CSAR = MCF5XXX_FBCS_CSAR_BA((uint_32)BSP_FLASH0_BASE);
    fbcs[0].CSCR = (MCF5XXX_FBCS_CSCR_PS_8 | MCF5XXX_FBCS_CSCR_AA | MCF5XXX_FBCS_CSCR_WS(5));
    fbcs[0].CSMR = MCF5XXX_FBCS_CSMR_BAM_512K | MCF5XXX_FBCS_CSMR_V;

    // User Flash: JS28F128J3D-75
    fbcs[1].CSAR = MCF5XXX_FBCS_CSAR_BA((uint_32)BSP_FLASH1_BASE);
    fbcs[1].CSCR = (MCF5XXX_FBCS_CSCR_PS_8 | MCF5XXX_FBCS_CSCR_AA | MCF5XXX_FBCS_CSCR_WS(5));
    fbcs[1].CSMR = MCF5XXX_FBCS_CSMR_BAM_16M | MCF5XXX_FBCS_CSMR_V;
}



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf5445_init
* Returned Value   : void
* Comments         :
*   Initialize CPU speed and chip selects.  Called from vectors.cw boot
* sequence before calling the runtime application startup code.
*
*END*----------------------------------------------------------------------*/

__declspec(init) far void mcf5445_init(void) {
    VMCF5445_STRUCT_PTR reg = (VMCF5445_STRUCT_PTR)_PSP_GET_IPSBAR();
    
    // pll
    pll_init();
    
    // sdram
    ram_init();
    
    // flash init
    flash_init();
}

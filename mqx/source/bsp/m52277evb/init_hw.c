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
* $FileName: init_hw.c$
* $Version : 3.6.16.0$
* $Date    : Aug-31-2010$
*
* Comments:
*
*   This file contains flash boot code to initialize chip selects,
*   disable the watchdog timer, initialize the PLL and initialize
*   the DRAM controller.
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
 __declspec(init) far static void pll_set(void) 
 {
    VMCF5227_STRUCT_PTR reg = (VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR();

    /* bypass PLL temporarily */
    reg->CCM.MISCCR |= MCF5227_CCM_MISCCR_LIMP;
    
    /* setup PLL */
    reg->PLL.PCR = MCF5227_PLL_PCR_PFDR(34) /* fvco = 34 * 16MHz = 544MHz */
        | MCF5227_PLL_PCR_OUTDIV5(8)        /* fusb = fvco / 9   = 60.44MHz */   
/*      | MCF5227_PLL_PCR_OUTDIV4(0)  */    /* fpci = not used */
        | MCF5227_PLL_PCR_OUTDIV3(3)        /* fsdram = fvco / 4 = 136MHz (must be = fsys) */
        | MCF5227_PLL_PCR_OUTDIV2(7)        /* fbus = fvco / 8 = 68MHz (must be = fsys/2) */
        | MCF5227_PLL_PCR_OUTDIV1(3);       /* fsys = fvco / 4 = 136MHz */

    /* switch to new clocks */
    reg->CCM.MISCCR &= ~MCF5227_CCM_MISCCR_LIMP;
    while (!(reg->PLL.PSR & MCF5227_PLL_PSR_LOCK)) {
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

__declspec(init) far static void pll_init(void) 
{
    
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

__declspec(init) far static void ram_init(void) 
{
    _mqx_int i;
    VMCF5227_STRUCT_PTR reg = (VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR();
    VMCF5XXX_SDRAM_CTRL_STRUCT_PTR sdramc = &((VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR())->SDRAMC;

    if (!(sdramc->SDCR & MCF5XXX_SDRAMC_SDCR_REF_EN)) {
        sdramc->SDCR &= ~MCF5XXX_SDRAMC_SDCR_REF_EN;
    
        /* SDRAM chip select initialization */
        sdramc->SDCS0 = MCF5XXX_SDRAMC_SDCS_BA((uint_32)BSP_RAM_BASE)
            | MCF5XXX_SDRAMC_SDCS_CSSZ(MCF5XXX_SDRAMC_SDCS_CSSZ_64MBYTE);

        /* 
        ** Basic configuration and initialization 
        */         
        sdramc->SDCFG1 = MCF5XXX_SDRAMC_SDCFG1_SRD2RWP(4)
            | MCF5XXX_SDRAMC_SDCFG1_SWT2RWP(3)
            | MCF5XXX_SDRAMC_SDCFG1_RD_LAT(7)
            | MCF5XXX_SDRAMC_SDCFG1_ACT2RW(1)
            | MCF5XXX_SDRAMC_SDCFG1_PRE2ACT(1)
            | MCF5XXX_SDRAMC_SDCFG1_REF2ACT(6)
            | MCF5XXX_SDRAMC_SDCFG1_WT_LAT(3);
           
        sdramc->SDCFG2 = MCF5XXX_SDRAMC_SDCFG2_BRD2RP(5)
            | MCF5XXX_SDRAMC_SDCFG2_BWT2RWP(6)
            | MCF5XXX_SDRAMC_SDCFG2_BRD2W(6)
            | MCF5XXX_SDRAMC_SDCFG2_BL(7);

        /* 
        ** Precharge and enable write to SDMR 
        */
        sdramc->SDCR = MCF5XXX_SDRAMC_SDCR_MODE_EN | MCF5XXX_SDRAMC_SDCR_CKE
           | MCF5XXX_SDRAMC_SDCR_DDR_MODE | MCF5XXX_SDRAMC_SDCR_ADDR_MUX(1)
           | MCF5XXX_SDRAMC_SDCR_REF_CNT(9)
           | MCF5XXX_SDRAMC_SDCR_MEM_PS | MCF5XXX_SDRAMC_SDCR_IPALL;

        /* 
        ** Write extended mode register 
        */
        sdramc->SDMR = MCF5XXX_SDRAMC_SDMR_BK(2) | MCF5XXX_SDRAMC_SDMR_AD(0x60) | MCF5XXX_SDRAMC_SDMR_CMD;

        /* 
        ** Write mode register and reset DLL 
        */
        sdramc->SDMR = MCF5XXX_SDRAMC_SDMR_LMR | MCF5XXX_SDRAMC_SDMR_AD(0x33) | MCF5XXX_SDRAMC_SDMR_CMD;

        /*
        ** Execute a PALL command 
        */
        sdramc->SDCR |= MCF5XXX_SDRAMC_SDCR_IPALL;

        /* 
        ** Perform two REF cycles 
        */
        sdramc->SDCR |= MCF5XXX_SDRAMC_SDCR_IREF;
        sdramc->SDCR |= MCF5XXX_SDRAMC_SDCR_IREF;

        /* 
        ** Write mode register and clear reset DLL 
        */
        /*sdramc->SDMR = MCF5XXX_SDRAMC_SDMR_LMR | MCF5XXX_SDRAMC_SDMR_AD(0x63) | MCF5XXX_SDRAMC_SDMR_CMD; */
      
        /*
        ** Enable auto refresh and lock SDMR 
        */
        sdramc->SDCR &= ~MCF5XXX_SDRAMC_SDCR_MODE_EN;
        sdramc->SDCR |= (MCF5XXX_SDRAMC_SDCR_REF_EN | MCF5XXX_SDRAMC_SDCR_DQS_OE(0x3));
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

__declspec(init) far static void flash_init(void) 
{
    VMCF5227_STRUCT_PTR reg = (VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR();
    MCF5XXX_FB_STRUCT_PTR fbcs = (MCF5XXX_FB_STRUCT_PTR)((VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR())->FB;

    fbcs[0].CSAR = MCF5XXX_FBCS_CSAR_BA((uint_32)BSP_FLASH_BASE);
    fbcs[0].CSCR = MCF5XXX_FBCS_CSCR_WS(7) | MCF5XXX_FBCS_CSCR_SBM | MCF5XXX_FBCS_CSCR_AA | MCF5XXX_FBCS_CSCR_PS_16 | MCF5XXX_FBCS_CSCR_BEM;
    fbcs[0].CSMR = MCF5XXX_FBCS_CSMR_BAM_16M | MCF5XXX_FBCS_CSMR_V;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf5227_init
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

__declspec(init) far void mcf5227_init(void) 
{
    VMCF5227_STRUCT_PTR reg = (VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR();

#if 0
   VMCF5227_STRUCT_PTR mcf5227_ptr = (pointer)0xFC000000; /* == _psp_saved_mbar */
   
   /* Disable core watchdog timer */
   mcf5227_ptr->CWCR = 0;
   
   /* All masters are trusted */
   mcf5227_ptr->MPR = 0x77777777;

   /* Allow supervisor/user, read/write, and trusted/untrusted access to all slaves */
   mcf5227_ptr->PACRA = 0;
   mcf5227_ptr->PACRB = 0;
   mcf5227_ptr->PACRC = 0;
   mcf5227_ptr->PACRD = 0;
   mcf5227_ptr->PACRE = 0;
   mcf5227_ptr->PACRF = 0;
   mcf5227_ptr->PACRG = 0;
   mcf5227_ptr->PACRI = 0;
#endif
       
    /* pll */ 
    pll_init();
    
    /* sdram */
    ram_init();
    
    /* flash init */
    flash_init();
}


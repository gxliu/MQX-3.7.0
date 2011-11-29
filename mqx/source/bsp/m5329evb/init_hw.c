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
* $Date    : Dec-15-2010$
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

 __declspec(init) far static void pll_set(void) 
{ /* Body */

   VMCF5329_STRUCT_PTR reg = (VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR();
   
   /* The MFD bits may only be written when the device is in limp mode MISCCR[LIMP] = 1 */
   reg->CCM.MISCCR |= MCF53XX_CCM_MISCCR_LIMP;
   
   /* Set PLL *********************************************************
   ** BSP_SYSTEM_CLOCK (Fsys) = (Fref * PFDR[MFD]) / (4 * PODR[CPUDIV])
   ** e.g.              Fsys  = (16 * 120) / (4 * 2)
   ** Fref = 16MHz, MFD = {88,..,135} and CPUDIV = {2,6}
   ** 
   ** Changing Fsys should also set the macros BSP_SYSTEM_CLOCK, SYSTEM_CLOCK
   ** and SYSTEM_CLK_PERIOD accordingly in bsp header file m5329evb.h
   */

   /* CPUDIV = 2, BUSDIV = 6 */
   reg->PLL.PODR = MCF5329_PLL_ODR_CPUDIV(0x20) | MCF5329_PLL_ODR_BUSDIV(0x06);
   
   /*
   ** The value of PODR register is fixed to 0x26. Writing any other 
   ** value to this register will result in unpredictable behavior.
   */
   reg->PLL.PFDR = MCF5329_PLL_FDR_MFD(0x78);
   
   /* Exit LIMP mode */
   reg->CCM.MISCCR &= ~MCF53XX_CCM_MISCCR_LIMP;
   
   /* Wait for PLL lock */
   while (!(reg->CCM.MISCCR & MCF53XX_CCM_MISCCR_PLL_LOCK))
   {
     /* nop */  
   };    
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : pll_init
* Returned Value   : void
* Comments         :
*   Initialize PLL
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void pll_init(void) 
{ /* Body */
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
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : ram_init
* Returned Value   : void
* Comments         :
*   Initialize chip selects and SDRAM controller
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void ram_init(void) 
{ /* Body */
    _mqx_int i;
    VMCF5329_STRUCT_PTR reg = (VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR();
    VMCF53XX_SDRAM_CTRL_STRUCT_PTR sdramc = &((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->SDRAMC;

    if (!(sdramc->SDCR & MCF53XX_SDRAMC_SDCR_REF_EN)) {
        sdramc->SDCR &= ~MCF53XX_SDRAMC_SDCR_REF_EN;
    
        /* SDRAM chip select initialization */
        sdramc->SDCS0 = MCF53XX_SDRAMC_SDCS_BA((uint_32)BSP_RAM_BASE)
                      | MCF53XX_SDRAMC_SDCS_CSSZ(MCF53XX_SDRAMC_SDCS_CSSZ_32MBYTE);
        /* 
        ** Basic configuration and initialization 
        */         
        sdramc->SDCFG1 = MCF53XX_SDRAMC_SDCFG1_SRD2RWP(5)
		                 | MCF53XX_SDRAMC_SDCFG1_SWT2RWP(3)
               		  | MCF53XX_SDRAMC_SDCFG1_RD_LAT(7)
               		  | MCF53XX_SDRAMC_SDCFG1_ACT2RW(2)
               		  | MCF53XX_SDRAMC_SDCFG1_PRE2ACT(2)
               		  | MCF53XX_SDRAMC_SDCFG1_REF2ACT(7)
               		  | MCF53XX_SDRAMC_SDCFG1_WT_LAT(3);

	     sdramc->SDCFG2 = MCF53XX_SDRAMC_SDCFG2_BRD2RP(5)
            		     | MCF53XX_SDRAMC_SDCFG2_BWT2RWP(6)
            		     | MCF53XX_SDRAMC_SDCFG2_BRD2W(6)
            		     | MCF53XX_SDRAMC_SDCFG2_BL(7);
        /* 
        ** Precharge and enable write to SDMR 
        */
        sdramc->SDCR = MCF53XX_SDRAMC_SDCR_MODE_EN 
                     | MCF53XX_SDRAMC_SDCR_CKE
                     | MCF53XX_SDRAMC_SDCR_DDR_MODE 
                     | MCF53XX_SDRAMC_SDCR_ADDR_MUX(1)
                     | MCF53XX_SDRAMC_SDCR_REF_CNT(9)
                     | MCF53XX_SDRAMC_SDCR_MEM_PS
                     | MCF53XX_SDRAMC_SDCR_IPALL;
		  /* 
        ** Perform two refresh cycles 
        */
	     sdramc->SDCR |= MCF53XX_SDRAMC_SDCR_IREF;
	     sdramc->SDCR |= MCF53XX_SDRAMC_SDCR_IREF;
	    
	     /* 
        ** Write extended mode register 
        */
	     sdramc->SDMR = MCF53XX_SDRAMC_SDMR_BK(1) 
                     | MCF53XX_SDRAMC_SDMR_AD(0x00) 
                     | MCF53XX_SDRAMC_SDMR_CMD;
       
        /* 
        ** Write mode register and reset DLL 
        */
	     sdramc->SDMR = MCF53XX_SDRAMC_SDMR_BK(0) 
                     | MCF53XX_SDRAMC_SDMR_AD(0x0163) 
                     | MCF53XX_SDRAMC_SDMR_CMD;
       
        /*
        ** Execute a PALL command 
        */
	     sdramc->SDCR |= MCF53XX_SDRAMC_SDCR_IPALL;
        /*
        ** Enable auto refresh and lock SDMR 
        */
	     sdramc->SDCR &= ~MCF53XX_SDRAMC_SDCR_MODE_EN;
        sdramc->SDCR |= (MCF53XX_SDRAMC_SDCR_REF_EN 
                     | MCF53XX_SDRAMC_SDCR_DQS_OE(0x3)); 
       
    }/* Endif */
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : flash_init
* Returned Value   : void
* Comments         :
*   Initialize chip selects for FLASH
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void flash_init(void)
{ /* Body */

    VMCF5329_STRUCT_PTR   reg  = (VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR();
    MCF5XXX_FB_STRUCT_PTR fbcs = (MCF5XXX_FB_STRUCT_PTR)((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->FB;
    
    /* NOR boot Flash 2M bytes */
    fbcs[0].CSAR = MCF5XXX_FBCS_CSAR_BA((uint_32)BSP_FLASH_BASE);
    fbcs[0].CSCR = MCF5XXX_FBCS_CSCR_WS(7) 
                 | MCF5XXX_FBCS_CSCR_SBM
                 | MCF5XXX_FBCS_CSCR_AA
                 | MCF5XXX_FBCS_CSCR_PS_16
                 | MCF5XXX_FBCS_CSCR_BEM;
    fbcs[0].CSMR = MCF5XXX_FBCS_CSMR_BAM_2M | MCF5XXX_FBCS_CSMR_V;
    
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf5329_init
* Returned Value   : void
* Comments         :
*   Initialize CPU speed and chip selects.  Called from vectors.cw boot
* sequence before calling the runtime application startup code.
*
*END*----------------------------------------------------------------------*/

__declspec(init) far void mcf5329_init(void)
{ /* Body */
   VMCF5329_STRUCT_PTR reg = (VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR();
   
   /* disable watchdog timer */
   reg->WATCHDOG.WCR = 0x00;

   /* pll initialization */
   pll_init();
    
   /* sdram initialization */
   ram_init();
    
   /* NOR flash initialization */
   flash_init();
   
} /* Endbody */

/* EOF */
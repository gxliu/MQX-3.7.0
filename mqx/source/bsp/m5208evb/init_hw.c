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
* $Version : 3.7.3.0$
* $Date    : Feb-7-2011$
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

#pragma define_section init ".init" far_absolute R

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : scm_init
* Returned Value   : void
* Comments         :
*   Initialize SCM
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void scm_init (void)
{

   VMCF5208_STRUCT_PTR reg = (VMCF5208_STRUCT_PTR)_PSP_GET_IPSBAR();

    /* All masters are trusted */
    reg->SCM_A.MPR = 0x77777777;
    
    /* Allow supervisor/user, read/write, and trusted/untrusted
       access to all slaves */
    reg->SCM_A.PACRA = 0;
    reg->SCM_A.PACRB = 0;
    reg->SCM_A.PACRC = 0;
    reg->SCM_A.PACRD = 0;
    reg->SCM_A.PACRE = 0;
    reg->SCM_A.PACRF = 0;
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
    VMCF5208_STRUCT_PTR reg = (VMCF5208_STRUCT_PTR)_PSP_GET_IPSBAR();
    VMCF5XXX_SDRAM_CTRL_STRUCT_PTR sdramc = &((VMCF5208_STRUCT_PTR)_PSP_GET_IPSBAR())->SDRAMC;

    if (!(sdramc->SDCR & MCF5XXX_SDRAMC_SDCR_REF_EN)) {
        /*sdramc->SDCR &= ~MCF5XXX_SDRAMC_SDCR_REF_EN; */
    
        /* SDRAM chip select initialization */
        sdramc->SDCS0 = MCF5XXX_SDRAMC_SDCS_BA((uint_32)BSP_RAM_BASE)
            | MCF5XXX_SDRAMC_SDCS_CSSZ(MCF5XXX_SDRAMC_SDCS_CSSZ_32MBYTE);

        /* 
        ** Basic configuration and initialization 
        */         
        sdramc->SDCFG1 = MCF5XXX_SDRAMC_SDCFG1_SRD2RWP(4)
            | MCF5XXX_SDRAMC_SDCFG1_SWT2RWP(3)
            | MCF5XXX_SDRAMC_SDCFG1_RD_LAT(6)
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
        sdramc->SDMR = MCF5XXX_SDRAMC_SDMR_LMR | MCF5XXX_SDRAMC_SDMR_AD(0x033) | MCF5XXX_SDRAMC_SDMR_CMD;

       
        /*
        ** Execute a PALL command 
        */
         sdramc->SDCR = MCF5XXX_SDRAMC_SDCR_MODE_EN | MCF5XXX_SDRAMC_SDCR_CKE
           | MCF5XXX_SDRAMC_SDCR_DDR_MODE | MCF5XXX_SDRAMC_SDCR_ADDR_MUX(1)
           | MCF5XXX_SDRAMC_SDCR_REF_CNT(9)
           | MCF5XXX_SDRAMC_SDCR_MEM_PS | MCF5XXX_SDRAMC_SDCR_IPALL;

        /* 
        ** Perform two REF cycles 
        */
        sdramc->SDCR =MCF5XXX_SDRAMC_SDCR_MODE_EN | MCF5XXX_SDRAMC_SDCR_CKE
           | MCF5XXX_SDRAMC_SDCR_DDR_MODE | MCF5XXX_SDRAMC_SDCR_ADDR_MUX(1)
           | MCF5XXX_SDRAMC_SDCR_REF_CNT(9)
           | MCF5XXX_SDRAMC_SDCR_MEM_PS | MCF5XXX_SDRAMC_SDCR_IREF;
           
        sdramc->SDCR =MCF5XXX_SDRAMC_SDCR_MODE_EN | MCF5XXX_SDRAMC_SDCR_CKE
           | MCF5XXX_SDRAMC_SDCR_DDR_MODE | MCF5XXX_SDRAMC_SDCR_ADDR_MUX(1)
           | MCF5XXX_SDRAMC_SDCR_REF_CNT(9)
           | MCF5XXX_SDRAMC_SDCR_MEM_PS | MCF5XXX_SDRAMC_SDCR_IREF;
              
        /*sdramc->SDCR |= MCF5XXX_SDRAMC_SDCR_IREF; */

        /* 
        ** Write mode register and clear reset DLL 
        */
       /*sdramc->SDMR = MCF5XXX_SDRAMC_SDMR_LMR | MCF5XXX_SDRAMC_SDMR_AD(0x63) | MCF5XXX_SDRAMC_SDMR_CMD; */
      
        /*
        ** Enable auto refresh and lock SDMR 
        */
         sdramc->SDCR = MCF5XXX_SDRAMC_SDCR_CKE| MCF5XXX_SDRAMC_SDCR_DDR_MODE | 
         MCF5XXX_SDRAMC_SDCR_REF_EN | MCF5XXX_SDRAMC_SDCR_ADDR_MUX(1)
           | MCF5XXX_SDRAMC_SDCR_REF_CNT(9)
           | MCF5XXX_SDRAMC_SDCR_MEM_PS 
           | MCF5XXX_SDRAMC_SDCR_DQS_OE(3);
    }
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : fbcs_init
* Returned Value   : void
* Comments         :
*   Initialize chip selects for FLASH and External RAM
*
*END*----------------------------------------------------------------------*/
__declspec(init) far static void fbcs_init(void) {
    VMCF5208_STRUCT_PTR reg = (VMCF5208_STRUCT_PTR)_PSP_GET_IPSBAR();
    MCF5XXX_FB_STRUCT_PTR fbcs = (MCF5XXX_FB_STRUCT_PTR)((VMCF5208_STRUCT_PTR)_PSP_GET_IPSBAR())->FB;

    /* External Flash */
    fbcs[0].CSAR = MCF5XXX_FBCS_CSAR_BA((uint_32)BSP_FLASH_BASE);
    fbcs[0].CSCR = (MCF5XXX_FBCS_CSCR_PS_16
                    | MCF5XXX_FBCS_CSCR_BEM
                    | MCF5XXX_FBCS_CSCR_AA
                    | MCF5XXX_FBCS_CSCR_SBM
                    | MCF5XXX_FBCS_CSCR_WS(7));
    fbcs[0].CSMR = MCF5XXX_FBCS_CSMR_BAM_32M | MCF5XXX_FBCS_CSMR_V;
    
    /* External SRAM */
    fbcs[1].CSAR = MCF5XXX_FBCS_CSAR_BA((uint_32)BSP_EXTERNAL_SRAM_BASE);
    fbcs[1].CSCR = (MCF5XXX_FBCS_CSCR_PS_16
                    | MCF5XXX_FBCS_CSCR_AA
                    | MCF5XXX_FBCS_CSCR_SBM
                    | MCF5XXX_FBCS_CSCR_WS(1));
    fbcs[1].CSMR = MCF5XXX_FBCS_CSMR_BAM_512K | MCF5XXX_FBCS_CSMR_V;
    
}



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf5208_init
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
__declspec(init) far void mcf5208_init(void) {
    VMCF5208_STRUCT_PTR reg = (VMCF5208_STRUCT_PTR)_PSP_GET_IPSBAR();

      /* Disable the Watchdog  */
     reg->WATCHDOG.WCR = 0;

      /* The PLL will start the core at a default frequency depending on 
       Mode configuration (SW1-1 in M5208EVBE)
       0: 166.66Mhz Core,   83.33Mhz Bus
       1: 88Mhz Core,       44Mhz Bus (DDR out of spec)
     */     

     /* scm */
    scm_init(); 
    
    /* sdram */
    ram_init();
    
    /* fbcs init  */
    fbcs_init();
}

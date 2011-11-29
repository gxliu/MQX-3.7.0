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
* $Version : 3.5.13.0$
* $Date    : Dec-10-2009$
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

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf5225_init
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

void mcf5225_init
   (
      void
   )
{
    VMCF5225_STRUCT_PTR reg_ptr = (VMCF5225_STRUCT_PTR)BSP_IPSBAR;
   
    /* Disable Software Watchdog Timer */
    reg_ptr->SCM.CWCR = 0;

    /* Enable Program Status Outputs, PST[3:0] signals */
    reg_ptr->GPIO.PDDPAR = MCF5225_GPIO_PDDPAR_PST;
  
    /* Initialize the PLL
    ** Divide 48Mhz reference crystal by 6 and multiply by 10 to achieve a 
    ** system clock of 80 Mhz.
    **   
    ** To set an MFD of ‘x’ and an RFD of ‘y’, you must first program RFD to ‘y+1’,
    ** then program MFD to ‘x’, then let the PLL lock, then program RFD to ‘y’. If 
    ** you program RFD simultaneous to MFD, you may over-clock and damage the part.
    */
    
    reg_ptr->CLK.OCLR  = 0xf0;
    reg_ptr->CLK.CCHR  = 5;
    reg_ptr->CLK.SYNCR = 0 |
        MCF5225_CLOCK_SYNCR_RFD(0) |
        MCF5225_CLOCK_SYNCR_MFD(3) |
        MCF5225_CLOCK_SYNCR_PLLMODE|
        MCF5225_CLOCK_SYNCR_PLLEN;

    /* wait for PLL locks before switching clock source */
    while (!(reg_ptr->CLK.SYNSR & MCF5225_CLOCK_SYNSR_LOCK)) {}

    /* now changing clock source is possible */
    reg_ptr->CLK.CCLR  = 0;
    reg_ptr->CLK.SYNCR |= MCF5225_CLOCK_SYNCR_CLKSRC;
      
    /* wait for PLL lock again */
    while (!(reg_ptr->CLK.SYNSR & MCF5225_CLOCK_SYNSR_LOCK)) {}
   
    /* Enable on-chip modules to access internal SRAM */
    reg_ptr->SCM.RAMBAR = MCF5225_SCM_RAMBAR_BA((uint_32)__INTERNAL_SRAM_BASE) | MCF5225_SCM_RAMBAR_BDE;
    
    /* Enable Mini FlexBUS signals (used by external MRAM and CPLD) */
    reg_ptr->GPIO.PASPAR = 0x20;   /* enable CS1 operation for CPLD */
    reg_ptr->GPIO.PTEPAR = 0xff;
    reg_ptr->GPIO.PTFPAR = 0xff;
    reg_ptr->GPIO.PTGPAR = 0xff;   /* enable CS0 operation for MRAM */
    reg_ptr->GPIO.PTHPAR = 0x5555;
    
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
    VMCF5XXX_MINIFB_STRUCT_PTR fb_ptr = &((VMCF5225_STRUCT_PTR)BSP_IPSBAR)->FB;
    
    fb_ptr->CSAR1 = MCF5XXX_FBCS_CSAR_BA(base_address);

    fb_ptr->CSCR1 = MCF5XXX_FBCS_CSCR_WS(0x13)  // wait states
                  | MCF5XXX_FBCS_CSCR_AA        // internal ack
                  | MCF5XXX_FBCS_CSCR_PS_8;     // data bus width 

    fb_ptr->CSMR1 = MCF5XXX_FBCS_CSMR_BAM_64K  // 64 KB data mask
                  | MCF5XXX_FBCS_CSMR_V;       // cs1 is valid
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
    VMCF5XXX_MINIFB_STRUCT_PTR fb_ptr = &((VMCF5225_STRUCT_PTR)BSP_IPSBAR)->FB;
    
    /* Enable external MRAM mapped on CS0 */
    fb_ptr->CSAR0 = MCF5XXX_FBCS_CSAR_BA(base_address); /* CS0 base address */
    fb_ptr->CSCR0 = 0x00000540; /* CS0 control (8bit data, 1 waitstate) */
    fb_ptr->CSMR0 = 0x00070001; /* CS0 address mask and enable */
}

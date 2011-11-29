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
* $Version : 3.6.2.0$
* $Date    : Sep-3-2010$
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
static void _mqx_clock_init_12MHz();
/***************************************************************************
 * Local Functions 
 ***************************************************************************/

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mqx_clock_init_12MHz
* Returned Value   : void
* Comments         :
*   
*
*END*----------------------------------------------------------------------*/
static void _mqx_clock_init_12MHz() 
{
    VMCF51JM_STRUCT_PTR reg_ptr = (VMCF51JM_STRUCT_PTR)BSP_IPSBAR;
      
     /* a)the MCG is default set to FEI mode, it should be change to FBE mode*/
     /*  MCG Control Register 2 */
     reg_ptr->MCG.MCGC2 = 0x36;
                   /*
                *  0b00110110
                *    ||||||||__ bit0: External ref clock disabled in stop
                *    |||||||___ bit1: MCGERCLK active
                *    ||||||____ bit2: Oscillator requested
                *    |||||_____ bit3: FLL/PLL not disabled in bypass modes
                *    ||||______ bit4: Configure crystal oscillator for
                *    |||              high gain operation
                *    |||_______ bit5: High frequency range selected for
                *    ||               crystal oscillator of 1 MHz to 16 MHz
                *    ||________ bit6: Divides selected clock by 1
                *    |_________ bit7: Divides selected clock by 1
                */
  /* b) MCG Status and Control Register */
    while(!(reg_ptr->MCG.MCGSC & 0x02)){};       /*Wait for the OSC stable*/
                   /*
                *  0b00000010
                *    ||||||||__ bit0:   FTRIM       MCG fine trim
                *    |||||||___ bit1:   OSCINIT OSC initialization
                *    ||||||____ bit2:   CLKST       Clock Mode status
                *    |||||_____ bit3:   CLKST
                *    ||||______ bit4:   IREFST  Internal reference status
                *    |||_______ bit5:   PLLST       PLL select status
                *    ||________ bit6:   LOCK        Lock Status
                *    |_________ bit7:   LOLS        Loss of lock status
                */
    
    //reg_ptr->MCG.MCGC1 =0x98; 
                
                
  /* MCG Control Register 1 */
    reg_ptr->MCG.MCGC1 = 0x9B;
                   /*
                *  0b10011011
                *    ||||||||__ bit0: Internal ref clock stays enabled in stop
                *    |||||||          if IRCLKEN is set or if MCG is in FEI,
                *    |||||||          FBI or BLPI mode before entering stop.
                *    |||||||___ bit1: MCGIRCLK active
                *    ||||||____ bit2: External reference clock selected
                *    |||||_____ bit3: External Reference Divider
                *    ||||______ bit4: External Reference Divider
                *    |||_______ bit5: External Reference Divider
                *    ||________ bit6: External reference clock is selected
                *    |_________ bit7: External reference clock is selected
                */

    /* check the external reference clock is selected or not*/
    while((reg_ptr->MCG.MCGSC & 0x1C ) != 0x08){};

    /* Switch to PBE mode from FBE*/
    /* MCG Control Register 3 */
    reg_ptr->MCG.MCGC3 = 0x48;
                     /*
                *  0b01001000
                *    ||||||||__ bit0: VCO Divider - Multiply by 32
                *    |||||||___ bit1: VCO Divider - Multiply by 32
                *    ||||||____ bit2: VCO Divider - Multiply by 32
                *    |||||_____ bit3: VCO Divider - Multiply by 32
                *    ||||______ bit4: Divide-by-32 is disabled
                *    |||_______ bit5: Clock monitor is disabled
                *    ||________ bit6: PLL is selected
                *    |_________ bit7: Generate an interrupt request on loss of lock
                */
    while ((reg_ptr->MCG.MCGSC & 0x48) != 0x48){};       /*wait for the PLL is locked & */

    /*Switch to PEE mode from PBE mode*/
    reg_ptr->MCG.MCGC1 &= 0x3F;
    while((reg_ptr->MCG.MCGSC & 0x6C) != 0x6C){};

    return; 
}

/***************************************************************************
 * Global Functions 
 ***************************************************************************/
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf51JMxx_init
* Returned Value   : void
* Comments         :
*   Initialize CPU speed and chip selects.  Called from vectors.cw boot
* sequence before calling the runtime application startup code.
*
*END*----------------------------------------------------------------------*/
void mcf51JMxx_init
   (
      void
   )
{
  VMCF51JM_STRUCT_PTR reg_ptr = (VMCF51JM_STRUCT_PTR)BSP_IPSBAR;


  reg_ptr->SIM.SOPT1 = MCF51XX_SOPT1_STOPE_MASK | MCF51XX_SOPT1_WAITE_MASK;
  
  reg_ptr->SIM.SOPT2 = 0;
  reg_ptr->PMC.SPMSC1 = 0x40;
  reg_ptr->PMC.SPMSC2 = 0;

  /* INTC_WCR: ENB=1,MASK=0 */
  reg_ptr->INTC.WCR = 0x80;
  _mqx_clock_init_12MHz();   
}

   



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
* $Version : 3.4.3.0$
* $Date    : Sep-2-2009$
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

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf5223_init
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

void mcf5223_init
   (
      void
   )
{
    VMCF5223_STRUCT_PTR reg_ptr = (VMCF5223_STRUCT_PTR)BSP_IPSBAR;
   
    /* Disable Software Watchdog Timer */
    reg_ptr->SCM.CWCR = 0;

    /* Enable Program Status Outputs, PST[3:0] signals */
    reg_ptr->GPIO.PDDPAR = MCF5223_GPIO_PDDPAR_PST;
  
    /* Initialize the PLL
    ** Divide 25Mhz reference crystal by 5 and multiply by 12 to achieve a 
    ** system clock of 60 Mhz.
    **   
    ** To set an MFD of ‘x’ and an RFD of ‘y’, you must first program RFD to ‘y+1’,
    ** then program MFD to ‘x’, then let the PLL lock, then program RFD to ‘y’. If 
    ** you program RFD simultaneous to MFD, you may over-clock and damage the part.
    */
    
    reg_ptr->CLK.CCHR  = 4;
    reg_ptr->CLK.SYNCR = 0 |
        MCF5223_CLOCK_SYNCR_RFD(0) |
        MCF5223_CLOCK_SYNCR_MFD(4) |
        MCF5223_CLOCK_SYNCR_PLLMODE|
        MCF5223_CLOCK_SYNCR_PLLEN;

    /* wait for PLL locks before switching clock source */
    while (!(reg_ptr->CLK.SYNSR & MCF5223_CLOCK_SYNSR_LOCK)) {}

    /* now changing clock source is possible */
    reg_ptr->CLK.SYNCR |= MCF5223_CLOCK_SYNCR_CLKSRC;
      
    /* wait for PLL lock again */
    while (!(reg_ptr->CLK.SYNSR & MCF5223_CLOCK_SYNSR_LOCK)) {}
   
    /* Enable on-chip modules to access internal SRAM */
    reg_ptr->SCM.RAMBAR = MCF5223_SCM_RAMBAR_BA((uint_32)__INTERNAL_SRAM_BASE) | MCF5223_SCM_RAMBAR_BDE;
}

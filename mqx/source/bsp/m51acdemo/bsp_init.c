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
* $Version : 3.6.1.0$
* $Date    : Apr-7-2010$
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
static void _mqx_clock_init_20MHz();
/***************************************************************************
 * Local Functions 
 ***************************************************************************/
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mqx_clock_init_20MHz
* Returned Value   : void
* Comments         :
*   
*
*END*----------------------------------------------------------------------*/
static void _mqx_clock_init_20MHz()   
{
    VMCF51AC_MCG_STRUCT_PTR mcg_ptr = 
        (VMCF51AC_MCG_STRUCT_PTR)&(((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->MCG);
  
  
  /* Configure MCG to run in PEE Mode */
  /* 20MHz bus clock from a 4MHz external crystal */
  
  /* set up external oscillator */
  mcg_ptr->MCGC2 = 0x26; /* RANGE = 1; HGO = 0; ERCLKEN=1; EREFS = 1; BDIV = 00 (/1); */
   
  /* wait for oscillator to initialize - poll on OSCINIT bit of MCGSC*/
  while (!(mcg_ptr->MCGSC & 0x02)){}
  
  /* Configure MCGC3 to access the proper RDIV values */
  mcg_ptr->MCGC3 = 0x10; /* DIV32 = 1; */
    
  /* Select Clock Mode and Reference Divider */
  mcg_ptr->MCGC1 = 0x90; /* CLKS = 10; RDIV = 2 (/4, /128 with DIV32=1); IREFS = 0; */

  /* wait for Reference Status bit to update - poll on IREFST bit*/
  while (mcg_ptr->MCGSC & 0x10){} 
  
  /* Wait for clock status bits to update */
  while (((mcg_ptr->MCGSC & 0x0C)>>2) != 0b10){}        
  
  /* Configure MCGC3 to select PLL and VDIV */
  mcg_ptr->MCGC3 = 0x5A; /* PLLS =1; DIV32 = 1; VDIV = 1010 (x40) */
  
   /* wait for PLL status bit to update - poll on PLLST bit*/
  while (!(mcg_ptr->MCGSC & 0x20)){}
  
   /* Wait for LOCK bit to set - poll on LOCK bit*/
  while (!(mcg_ptr->MCGSC & 0x40)){}

  /* Now running PBE Mode */
  
  /* Transition into PEE */
  mcg_ptr->MCGC1 = 0x10; /* CLKS = 00; RDIV = 2 (/4 with PLLS=1); IREFS = 0; */

  /* Wait for clock status bits to update */
  while (((mcg_ptr->MCGSC & 0x0C)>>2) != 0b11){};           

  /* Now running PEE Mode */

    return; 
}

/***************************************************************************
 * Global Functions 
 ***************************************************************************/
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : mcf51ACxx_init
* Returned Value   : void
* Comments         :
*   Initialize CPU speed and chip selects.  Called from vectors.s boot
* sequence before calling the runtime application startup code.
*
*END*----------------------------------------------------------------------*/
void mcf51ACxx_init
   (
      void
   )
{
  VMCF51AC_SIM_STRUCT_PTR sim_ptr = 
        (VMCF51AC_SIM_STRUCT_PTR)&(((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->SIM);
        
  sim_ptr->SOPT = MCF51XX_SOPT1_STOPE_MASK | MCF51XX_SOPT1_WAITE_MASK; //0x20; // disable COP, enable STOP
  sim_ptr->SOPT2 = 0;
  sim_ptr->SPMSC1 = 0x40;
  sim_ptr->SPMSC2 = 0;
  
   _mqx_clock_init_20MHz();   
}

   



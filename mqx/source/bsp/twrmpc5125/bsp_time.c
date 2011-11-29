/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $FileName: bsp_time.c$
* $Version : 3.7.4.0$
* $Date    : Feb-7-2011$
*
* Comments:
* 
*     This file contains time functions for the BSP.
*
*END***********************************************************************/


#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_elapsed_time
* Returned Value   : microseconds since boot
* Comments         :
*    This function returns elapsed time since last timer reset in Microseconds
*
*END*----------------------------------------------------------------------*/

uint_64 _bsp_elapsed_time(void)
{ 
   return _psp_read_timebase() / (BSP_EXCLK_CLOCK / 1000000);
} 

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_spin_time
* Returned Value   : none
* Comments         :
*
*END*----------------------------------------------------------------------*/

void _bsp_spin_time
   (
      // [IN] number of microseconds to wait
      uint_32 us
   )
{ 

   uint_64 now = _bsp_elapsed_time();
   uint_64 timeout = now + us;

   while (timeout > _bsp_elapsed_time()) {
   } 
} 


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_ipb_frequency
* Returned Value   : none
* Comments         :
*
*END*----------------------------------------------------------------------*/


uint_32 _bsp_ipb_frequency(void)
{    
   return _mpc5125_get_ipb_clock(BSP_EXCLK_CLOCK);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_set_psc_clock
* Returned Value   : none
* Comments         :
*
*END*----------------------------------------------------------------------*/


boolean _bsp_set_psc_clock(uint_32 dev,uint_32 pscclk)
{    
   return _mpc512x_set_psc_clock(BSP_EXCLK_CLOCK, dev, CCM_MxCCR_MSCANx_CLK_SRC_SYS_CLK, pscclk); /* Set src to sys_clk */
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_ipb_frequency
* Returned Value   : none
* Comments         :
*
*END*----------------------------------------------------------------------*/


boolean _bsp_enable_can_clock(uint_32 dev,uint_32 canclk)
{    
   return _mpc512x_enable_can_clock(BSP_EXCLK_CLOCK, dev, CCM_MxCCR_MSCANx_CLK_SRC_SYS_CLK, canclk); // Set src to sys_clk
 }


MSCAN_TIMING_PARAM_STRUCT bsp_mscan_timing_params[] =
//  bitrate, clksrc, sjw, presc, samp, tseg1, tseg2 
{
  { 1000,    1,      0,   5,     1,    5,     3     },
  { 500,     1,      0,   10,    1,    6,     3     },
  { 250,     1,      0,   21,    1,    6,     3     },
  { 125,     1,      0,   32,    1,    8,     5     },
  { 100,     1,      0,   32,    1,    12,    5     },
  { 50,      1,      0,   59,    1,    13,    6     },
  { 0 }
};


/* EOF */

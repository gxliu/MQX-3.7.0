/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
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
* $FileName: timer_mcf5227.c$
* $Version : 3.6.4.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains timer functions for use with a MCF5227.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5227_timer_init_freq
* Returned Value  : the clock rate for the timer (ns per hw tick)
* Comments        :
*   this function will set up a timer to interrupt
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5227_timer_init_freq
   (
      /* [IN] the timer to initialize */
      _timer_id timer,

      /* [IN] ticks per second */
      uint_32   tickfreq,

      /* [IN] the system clock speed in MHz */
      uint_32   system_clock,

      /* [IN] Unmask the timer after initializing */
      boolean   unmask_timer
   )
{ /* Body */

   volatile MCF5227_STRUCT _PTR_  reg_ptr = _PSP_GET_MBAR();
   volatile MCF5XXX_PIT_STRUCT _PTR_  pit_ptr = &reg_ptr->PIT[timer];
   uint_32 rate, prescale = 0;
   uint_32 tps = tickfreq;
   uint_32 clk = system_clock;

  _mcf5227_int_init(_bsp_timers[timer].INTERRUPT, _bsp_timers[timer].LEVEL, FALSE);

   pit_ptr->PCSR = MCF5XXX_PIT_PCSR_HALTED  /* stop timer when halted */
      | MCF5XXX_PIT_PCSR_PIF                /* Clear interrupt if present */
      | MCF5XXX_PIT_PCSR_OVW;               /* Overwrite count with PMR when written */

   rate = (clk / tps );
   while (rate > 0xFFFF) {
      prescale += 1;                        /* divides clock in half */
      clk >>= 1;
      rate = (clk / tps );
   } /* Endwhile */

   pit_ptr->PCSR = (prescale << MCF5XXX_PIT_PCSR_PRESCALE_SHIFT)
      | MCF5XXX_PIT_PCSR_OVW                /* Enables writing to PMR */
      | MCF5XXX_PIT_PCSR_PIE                /* PIT interrupt Enable */
      | MCF5XXX_PIT_PCSR_RLD;               /* Enabled Reload bit */

   /* Set counter reload value and counter value */
   pit_ptr->PMR = (uint_16)rate;

   if (unmask_timer) {
      _mcf5227_timer_unmask_int(timer);
   } /* Endif */

   /* Enable the timer */
   pit_ptr->PCSR |= MCF5XXX_PIT_PCSR_EN;

   /* Return the tick rate */
   return rate;

} /* Endbody */


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5227_timer_init_int
* Returned Value  : the clock rate for the timer (ns per hw tick)
* Comments        :
*   this function will set up a timer to interrupt
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5227_timer_init_int
   (
      /* [IN] the timer to initialize */
      _timer_id timer,

      /* [IN] the tick rate wanted in milliseconds */
      uint_32   frequency,

      /* [IN] the system clock speed in MHz */
      uint_32   system_clock,

      /* [IN] Unmask the timer after initializing */
      boolean   unmask_timer
   )
{ /* Body */

   return _mcf5227_timer_init_freq(timer, 1000 / frequency,
      system_clock, unmask_timer);

} /* Endbody */


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : get_ticks_and_pmr
* Returned Value  : Number of ticks
* Comments        :
*   This function will return the number of ticks elapsed since the last
* timer tick and the PMR value.
*
*END*---------------------------------------------------------------------*/

static uint_32 get_ticks_and_pmr
   (
      /* [IN] the timer to clear */
      _timer_id   timer,

      /* [OUT] the timer's PMR value */
      uint_16_ptr pmrp
   )
{ /* Body */

   volatile MCF5227_STRUCT _PTR_  reg_ptr = _PSP_GET_MBAR();
   volatile MCF5XXX_PIT_STRUCT _PTR_  pit_ptr = &reg_ptr->PIT[timer];

/* Start CR 1973 */   
   uint_16 pmr   = pit_ptr->PMR;
   uint_32 ticks = pmr - pit_ptr->PCNTR;

   if ((pit_ptr->PCSR & MCF5XXX_PIT_PCSR_PIF) != 0) {
      // Another full TICK period has expired since we handled
      // the last timer interrupt.  We need to read the counter (PCNTR) again, since the wrap may have
      // occurred between the previous read and the checking of the PIF bit.
      ticks = pmr + (pmr-pit_ptr->PCNTR);
   } /* Endif */
   
/* End CR 1973 */   
   *pmrp = pmr;

   return ticks;

} /* Endbody */



/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5227_timer_get_nsec
* Returned Value  : Number of ticks
* Comments        :
*   This function will return the number of ticks elapsed since the last
* timer tick.
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5227_get_hwticks
   (
      /* [IN] the timer to clear */
      _timer_id timer
   )
{ /* Body */

   uint_16 pmr;
   return get_ticks_and_pmr(timer,&pmr);

} /* Endbody */


/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _mcf5227_timer_get_nsec
* Returned Value  : nseconds
* Comments        :
*   this function will return the number of nanoseconds elapsed since
* the last timer tick.
*
*END*---------------------------------------------------------------------*/

uint_32 _mcf5227_timer_get_nsec
   (
      /* [IN] the timer to use */
      _timer_id timer,

      /* [IN] the alarm resolution in milliseconds */
      uint_32   resolution
   )
{ /* Body */

   uint_16 pmr;
   uint_32 ticks = get_ticks_and_pmr(timer,&pmr);
   /* like to make it nanoseconds here but don't want to overflow uint_32 */
   uint_32 tmsec_resolution = resolution * 10000; /* microseconds * 10 */
   uint_32 tms = ticks * tmsec_resolution;
   uint_32 n = tms / pmr;

   return n*100; /* microseconds * 10 *100 = nanoseconds */

} /* Endbody */

/* EOF */
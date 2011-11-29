#ifndef __tmpc512x_h__
#define __tmpc512x_h__
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
* $FileName: timer_mpc512x.h$
* $Version : 3.5.1.0$
* $Date    : Feb-24-2010$
*
* Comments:
* 
*    This file contains definitions for the mpc512x general purpose
*    timer utility functions.
*
*END***********************************************************************/

/*--------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/


/*-----------------------------------------------------------------------*/
/*                      FUNCTION PROTOTYPES
*/


#ifdef __cplusplus
extern "C" {
#endif

extern uint_32 _mpc512x_gpt_init( uint_32,uint_32,uint_32, uint_32);
extern void _mpc512x_gpt_isr( pointer channel );
extern uint_32 _mpc512x_gpt_get_hwticks( pointer channel );

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

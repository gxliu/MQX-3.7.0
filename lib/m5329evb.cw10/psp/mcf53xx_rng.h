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
* $FileName: mcf53xx_rng.h$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf53xx random number generator module.
*
*END************************************************************************/

#ifndef __mcf53xx_rng_h__
#define __mcf53xx_rng_h__

#define __mcf53xx_rng_h__version "$Version:3.6.1.0$"
#define __mcf53xx_rng_h__date    "$Date:Aug-2-2010$"

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------*/
/*
** RNG registers
*/


/*------------------------------------------------------------------------*/
/*

/*
** MCF53XX_RNG_STRUCT
*/

typedef struct mcf53xx_rng_struct
{
   uint_32 RNGVER;
   uint_32 RNGCMD;
   uint_32 RNGCR;
   uint_32 RNGSR;
   uint_32 RNGESR;
   uint_32 RNGOUT;
   uint_32 RNGER;

} MCF53XX_RNG_STRUCT, _PTR_ MCF53XX_RNG_STRUCT_PTR;
typedef volatile struct mcf53xx_rng_struct _PTR_ VMCF53XX_RNG_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif  /*__mcf53xx_rng_h__*/

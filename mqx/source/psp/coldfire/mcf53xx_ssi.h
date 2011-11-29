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
* $FileName: mcf53xx_ssi.h$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf53xx SSI module.
*
*END************************************************************************/

#ifndef __mcf53xx_ssi_h__
#define __mcf53xx_ssi_h__

#define __mcf53xx_ssi_h__version "$Version:3.6.1.0$"
#define __mcf53xx_ssi_h__date    "$Date:Aug-2-2010$"

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------*/
/*
** SSI registers
*/


/*------------------------------------------------------------------------*/
/*

/*
** MCF53XX_SSI_STRUCT

*/

typedef struct mcf53xx_ssi_struct
{
   uint_32 SSI_TX0;
   uint_32 SSI_TX1;
   uint_32 SSI_RX0;
   uint_32 SSI_RX1;
   uint_32 SSI_CR;
   uint_32 SSI_IER;
   uint_32 SSI_TCR;
   uint_32 SSI_RCR;
   uint_32 SSI_CCR;
   uint_32 filler0;
   uint_32 SSI_FCSR;
   uint_32 filler1[2];
   uint_32 SSI_ACR;
   uint_32 SSI_ACADD;
   uint_32 SSI_ACDAT;
   uint_32 SSI_ATAG;
   uint_32 SSI_TMASK;
   uint_32 SSI_RMASK;
   uint_32 SSI_ACCSR;
   uint_32 SSI_ACCEN;
   uint_32 SSI_ACCDIS;

} MCF53XX_SSI_STRUCT, _PTR_ MCF53XX_SSI_STRUCT_PTR;
typedef volatile struct mcf53xx_ssi_struct _PTR_ VMCF53XX_SSI_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif  /*__mcf53xx_ssi_h__*/

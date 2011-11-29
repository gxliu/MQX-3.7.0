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
* $FileName: mcf53xx_dma.h$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf53xx I2C module.
*
*END************************************************************************/

#ifndef __mcf53xx_dma_h__
#define __mcf53xx_dma_h__

#define __mcf53xx_dma_h__version "$Version:3.6.1.0$"
#define __mcf53xx_dma_h__date    "$Date:Aug-2-2010$"

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------*/
/*
** SIM registers


/* Bit definitions and macros for MCF53XX_DMA */



/*------------------------------------------------------------------------*/
/*

/*
** MCF53XX_SIM_STRUCT
** This structure defines what one SIM register look like
*/

typedef struct mcf53xx_dma_struct
{
   uchar    DTMR;    /* MA Timer n Mode Register */
	uchar    DTXMR;	/* xtended Mode Register */
   uchar    DTER;		/* Event Register */
	uchar	   DTRR;		/* Reference Register */
	uchar	   DTCR;		/* Capture Register */
	uchar    DTCN;		/* Counter Register */
	uchar    filler1[0x3FF0];

} MCF53XX_DMA_TIMER_STRUCT, _PTR_ MCF53XX_DMA_TIMER_STRUCT_PTR;
typedef volatile struct mcf53xx_dma_struct _PTR_ VMCF53XX_DMA_TIMER_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif  /*__mcf53xx_dma_h__*/

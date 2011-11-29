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
* $FileName: mcf53xx_sim.h$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf53xx I2C module.
*
*END************************************************************************/

#ifndef __mcf53xx_sim_h__
#define __mcf53xx_sim_h__

#define __mcf53xx_sim_h__version "$Version:3.6.1.0$"
#define __mcf53xx_sim_h__date    "$Date:Aug-2-2010$"

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------*/
/*
** SIM registers
/*SIM Port Control Registers (SIM_CRn)*/

/* Bit definitions and macros for MCF53XX_SIM */
#define MCF53XX_SIM_SAPD                    (0x01)
#define MCF53XX_SIM_SVEN                    (0x02)
#define MCF53XX_SIM_STEN                    (0x4)
#define MCF53XX_SIM_SRST                    (0x8)
#define MCF53XX_SIM_SCEN                    (0x10)
#define MCF53XX_SIM_SCSP                    (0x20)
#define MCF53XX_SIM_3VOLT                   (0x40)
#define MCF53XX_SIM_SFPD                    (0x80)


/*------------------------------------------------------------------------*/
/*

/*
** MCF53XX_SIM_STRUCT
** This structure defines what one SIM register look like
*/

typedef struct mcf53xx_sim_struct
{
   uchar    SIM_CR1  ;      /* SIM port 1 control registeR */
   uchar    filler1[3];        
   uchar    SIM_SETUP;      /* SIM setup register */
   uchar    filler2[3];        
   uchar    SIM_DETECT1;    /* SIM port 1 detect register */
   uchar    filler3[3];        
   uchar    SIM_TBUF1;      /* SIM port 1 transmit buffer register  */
   uchar    filler4[3];        
   uchar    SIM_RBUF1;      /* SIM port 1 receive buffer register  */
   uchar    filler5[3];        
   uchar    SIM_CR0;        /* SIM port 0 control register  */
   uchar    filler6[3];        
   uchar    SIM_CR;         /* SIM control register  */
   uchar    filler7[3];        
   uchar    SIM_PRE;        /* SIM clock prescaler register  */
   uchar    filler8[3];        
   uchar    SIM_RTHR;       /* SIM receive threshold register  */
   uchar    filler9[3];        
   uchar    SIM_EN;         /* SIM enable register */
   uchar    filler10[3];       
   uchar    SIM_TSR;        /* SIM transmit status register */
   uchar    filler11[3];       
   uchar    SIM_RSR;		    /* SIM receive status register  */
   uchar    filler12[3];       
   uchar    SIM_IMR;		    /* SIM interrupt mask register */
   uchar    filler13[3];       
   uchar    SIM_TBUF0;      /* SIM port0 transmit buffer register  */
   uchar    filler14[3];       
   uchar    SIM_RBUF0;	    /* SIM port0 receive buffer register  */
   uchar    filler15[3];       
   uchar    SIM_DETECT0;    /* SIM port0 detect register  */
   uchar    filler16[3];       
   uchar    SIM_FORMAT0;    /* SIM data format register */
   uchar    filler17[3];       
   uchar    SIM_TTHR;	    /* SIM transmit threshold register  */
   uchar    filler18[3];       
   uchar    SIM_TGCR;       /* SIM transmit guard control register  */
   uchar    filler19[3];       
   uchar    SIM_ODCR;       /* SIM open drain configuration control register */
   uchar    filler20[3];       
   uchar    SIM_RCR;        /* SIM reset control register  	 */
   uchar    filler21[3];       
   uchar    SIM_CWTR;       /* SIM character wait time register  */
   uchar    filler22[3];       
   uchar    SIM_GPCNT;      /* SIM general purpose counter register  */
   uchar    filler23[3];       
   uchar    SIM_DIV;        /* SIM divisor register  */
   uchar    filler24[3];       
   uchar    SIM_BWT;        /* SIM block wait time register  */
   uchar    filler25[3];       
   uchar    SIM_BGT;        /* SIM block guard time register  */
   uchar    filler26[3];       
   uchar    SIM_BWTH;       /* SIM block wait time register high  */
   uchar    filler27[3];       
   uchar    SIM_TFSR;       /* SIM transmit FIFO status register  */
   uchar    filler28[3];       
   uchar    SIM_RFCR;       /* SIM receive FIFO counter register  */
   uchar    filler29[3];       
   uchar    SIM_RFWP;       /* SIM receive FIFO write pointer register  */
   uchar    filler30[3];       
   uchar    SIM_RFRP;       /* SIM receive FIFO read pointer register  */

} MCF53XX_SIM_STRUCT, _PTR_ MCF53XX_SIM_STRUCT_PTR;
typedef volatile struct mcf53xx_sim_struct _PTR_ VMCF53XX_SIM_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif  /*__mcf53xx_sim_h__*/

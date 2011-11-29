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
* $FileName: mcf53xx_usbhost.h$
* $Version : 3.6.1.0$
* $Date    : Dec-15-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf53xx I2C module.
*
*END************************************************************************/

#ifndef __mcf53xx_usbhost_h__
#define __mcf53xx_usbhost_h__

#define __mcf53xx_usbhost_h__version "$Version:3.6.1.0$"
#define __mcf53xx_usbhost_h__date    "$Date:Dec-15-2010$"

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------*/
/*
** USB HOST  registers


/* Bit definitions and macros for MCF53XX_usbhost */



/*------------------------------------------------------------------------*/
/*

/*
** MCF53XX_usbhost_STRUCT
** This structure defines what one USB register look like
*/

typedef struct mcf53xx_usbhost_struct {
	
	uint_32    ID;
 	uint_32    HWGENERAL;
	uint_32    HWHOST;
	uint_32    filler4;
	uint_32    HWTXBUF;
	uint_32    HWRXBUF;
	uchar      filler5[0x4100-0x4014-1-4];
	uint_16    HCIVERSION;
	uchar      filler6;
	uint_8     CAPLENGTH;
	uint_32    HCSPARAMS;
	uint_32    HCCPARAMS;
	uint_32    filler7[13];
	uint_32    USBCMD;
	uint_32    USBSTS;
	uint_32    USBINTR;
	uint_32    FRINDEX;
	uint_32    filler11;
	uint_32    PERIODICLISTBASE;
	uint_32    ASYNCLISTADDR;
	uint_32    TTCTRL;
	uint_32    BURSTSIZE ;
	uint_32    TXFILLTUNING ;
	uint_32    filler16[6];
	uint_32    CONFIGFLAG;
	uint_32    PORTSC1;
	uint_32    filler18[8];
	uint_32    MODE;
	

} MCF53XX_USBHOST_STRUCT, _PTR_ MCF53XX_USBHOST_STRUCT_PTR;
typedef volatile struct mcf53xx_usbhost_struct _PTR_ VMCF53XX_USBHOST_STRUCT_PTR;


#ifdef __cplusplus
}
#endif

#endif  /*__mcf53xx_usbhost_h__*/

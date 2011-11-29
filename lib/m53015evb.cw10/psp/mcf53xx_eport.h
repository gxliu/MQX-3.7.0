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
* $FileName: mcf53xx_eport.h$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf53xx I2C module.
*
*END************************************************************************/

#ifndef __mcf53xx_eport_h__
#define __mcf53xx_eport_h__

#define __mcf53xx_eport_h__version "$Version:3.6.1.0$"
#define __mcf53xx_eport_h__date    "$Date:Aug-2-2010$"

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------*/
/*
** SIM registers


/* Bit definitions and macros for MCF53XX_usbhost */



/*------------------------------------------------------------------------*/
/*

/*
** MCF53XX_usbhost_STRUCT
** This structure defines what one SIM register look like
*/

typedef struct mcf5301_eport_struct {
	
	uchar	EPPAR;
	uchar EPDDR;
	uchar	EPIER;
	uchar	EPDR;
	uchar	EPPDR;
	uchar	EPFR;

	

} MCF53XX_EPORT_STRUCT, _PTR_ MCF53XX_EPORT_STRUCT_PTR;
typedef volatile struct mcf5301_eport_struct _PTR_ VMCF53XX_EPORT_STRUCT_PTR;


#ifdef __cplusplus
}
#endif

#endif  /*__mcf53xx_eport_h__*/

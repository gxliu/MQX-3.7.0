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
* $FileName: mcf53xx_iim.h$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf53xx IC identification module.
*
*END************************************************************************/

#ifndef __mcf53xx_iim_h__
#define __mcf53xx_iim_h__

#define __mcf53xx_iim_h__version "$Version:3.6.1.0$"
#define __mcf53xx_iim_h__date    "$Date:Aug-2-2010$"

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------*/
/*
** RNG registers
*/


/*------------------------------------------------------------------------*/


typedef struct mcf53xx_seckey_struct
{
   uchar SECKEY;             
   uchar filler[3];              
   
} MCF53XX_SECKEY_STRUCT, _PTR_ MCF53XX_SECKY_STRUCT_PTR;
typedef volatile struct mcf53xx_seckey_struct _PTR_ VMCF53XX_SECKEY_STRUCT_PTR;


typedef struct mcf53xx_iim_fb_struct
{
   uchar FBW;             
   uchar filler2[3];              
   
} MCF53XX_IIM_FB_STRUCT, _PTR_ MCF53XX_IIM_FB_STRUCT_PTR;
typedef volatile struct mcf53xx_iim_fb_struct _PTR_ VMCF53XX_IIM_FB__STRUCT_PTR;


/*
** MCF53XX_RNG_STRUCT
*/

typedef struct mcf53xx_iim_struct
{
   uint_8                 IIM_SR;
   uint_8                 filler0[3];
   uint_8                 IIM_SIMR;
   uint_8                 filler1[3];
   uint_8                 IIM_ESR;
   uint_8                 filler2[3];
   uint_8                 IIM_EIMR;
   uint_8                 filler3[3];
   uint_8                 IIM_FCR;
   uint_8                 filler4[3];
   uint_8                 IIM_UA;
   uint_8                 filler5[3];
   uint_8                 IIM_LA;
   uint_8                 filler6[3];
   uint_8                 IIM_SDAT;
   uint_8                 filler7[11];
   uint_8                 IIM_PRGP;
   uint_8                 filler8[3];
   uint_8                 IIM_DIVIDE;
   uint_8                 filler9[0x0800-0x03D];
   uint_8                 IIM_FBAC0;
   uint_8                 filler10[3];
   uint_8                 IIM_ANATEST;
   uint_8                 filler11[3];
   uint_8                 IIM_BGPTRIM;
   uint_8                 filler12[3];
   uint_8                 IIM_AMPBR;
   uint_8                 filler13[3];
   uint_8                 IIM_DRVACR;
   uint_8                 filler14[3];
   uint_8                 IIM_SPKACR;
   uint_8                 filler15[3];
   uint_8                 IIM_HSHPACR;
   uint_8                 filler16[3];
   MCF53XX_SECKEY_STRUCT  IIM_SECKEY[21];
   uint_8                 filler17[8];
   uint_8                 IIM_SAKRAM;
   uint_8                 filler18[3];
   uint_8                 IIM_SATAG;
   uint_8                 filler19[3];
   uint_8                 IIM_SACACHE;
   uint_8                 filler20[0xC00 - 0x87D];
   uint_8                 IIM_FBAC1;
   uint_8                 filler21[3];
   uint_8                 IIM_SASCCM;
   uint_8                 filler22[3];
   uint_8                 IIM_DEVID;
   uint_8                 filler23[3];
   MCF53XX_IIM_FB_STRUCT  IIM_FB1W[29];
   uint_8                 IIM_FBAC2;
   uint_8                 filler24[3];
   MCF53XX_IIM_FB_STRUCT  IIM_FB2W[31];
   uint_8                 IIM_FBAC3;
   uint_8                 filler25[3];
   MCF53XX_IIM_FB_STRUCT  IIM_FB3W[31];
   uint_8                 IIM_FBAC4;
   uint_8                 filler26[3];
   MCF53XX_IIM_FB_STRUCT  IIM_FB4W[31];
   uint_8                 IIM_FBAC5;
   uint_8                 filler27[3];
   MCF53XX_IIM_FB_STRUCT  IIM_FB5W[31];
   uint_8                 IIM_FBAC6;
   uint_8                 filler28[3];
   MCF53XX_IIM_FB_STRUCT  IIM_FB6W[31];
   uint_8                 IIM_FBAC7;
   uint_8                 filler29[3];
   MCF53XX_IIM_FB_STRUCT  IIM_FB7W[31];
   
   
} MCF53XX_IIM_STRUCT, _PTR_ MCF53XX_IIM_STRUCT_PTR;
typedef volatile struct mcf53xx_iim_struct _PTR_ VMCF53XX_IIM_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif  /*__mcf53xx_rng_h__*/

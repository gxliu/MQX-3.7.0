/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: mcf51xx_ftsr.h$
* $Version : 3.6.2.0$
* $Date    : May-18-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf51xx SPI module.
*
*END************************************************************************/

#ifndef __mcf51xx_ftsr_h__
#define __mcf51xx_ftsr_h__

#define __mcf51xx_ftsr_h__version "$Version:3.6.2.0$"
#define __mcf51xx_ftsr_h__date    "$Date:May-18-2010$"

#ifdef __cplusplus
extern "C" {
#endif

/* FCDIV */
#define MCF51XX_FTSR_FCDIV_FDIVLD  0x80
#define MCF51XX_FTSR_FCDIV_PRDIV8  0x40
#define MCF51XX_FTSR_FCDIV_FDIV(x) (((x)&0x3F)<<0)

/* FOPT */
#define MCF51XX_FTSR_FOPT_KEYEN(x)  ((x)&0x03 <<0x06)
#define MCF51XX_FTSR_FOPT_SEC(x)    ((x)&0x03 <<0)  

/* FCNFG */
#define MCF51XX_FTSR_FCNFG_CBIE     0x80
#define MCF51XX_FTSR_FCNFG_CCIE     0x40
#define MCF51XX_FTSR_FCNFG_KEYACC   0x20

/* FRPOT */
#define MCF51XX_FTSR_FPROT_FPS(x)   ((x)&0x7F<<1)
#define MCF51XX_FTSR_FPROT_FOPEN    0x01

/* FSTAT */
#define MCF51XX_FTSR_FSTAT_FCBEF    0x80
#define MCF51XX_FTSR_FSTAT_FCCF     0x40
#define MCF51XX_FTSR_FSTAT_FPVIOL   0x20
#define MCF51XX_FTSR_FSTAT_FACCERR  0x10
#define MCF51XX_FTSR_FSTAT_FBLANK   0x04

/* FCMD */
#define MCF51XX_FTSR_FCMD_FCMD(x)   ((x)&0x7F<<0)
#define MCF51XX_FTSR_FCMD_ERASE_VERIFY  0x05
#define MCF51XX_FTSR_FCMD_PROGRAM       0x20
#define MCF51XX_FTSR_FCMD_BURST_PROGRAM 0x25
#define MCF51XX_FTSR_FCMD_SECTOR_ERASE  0x40
#define MCF51XX_FTSR_FCMD_MASS_ERASE    0x41

typedef struct MCF51XX_ftsr_struct
{
  uchar FCDIV;  /*** FTSR - Flash Clock Divider Register; 0xFFFF82E0 ***/
  uchar FOPT;   /*** FTSR - Flash Options Register; 0xFFFF82E1 ***/
  uchar reserved0[1];  /*** FTSR - Reserved ***/
  uchar FCNFG;  /*** FTSR - Flash Configuration Register; 0xFFFF82E3 ***/
  uchar FPROT;  /*** FTSR - Flash Protection Register; 0xFFFF82E4 ***/
  uchar FSTAT;  /*** FTSR - Flash Status Register; 0xFFFF82E5 ***/ 
  uchar FCMD;   /*** FTSR - Flash Command Register; 0xFFFF82E6 ***/
  uchar reserved1[1];
  uchar FADDRHI; 
  uchar FADDRLO;
  uchar reserved2[2];
  uchar FDATAHI1;
  uchar FDATALO1;
  uchar FDATAHI0;
  uchar FDATALO0;
} MCF51XX_FTSR_STRUCT, _PTR_ MCF51XX_FTSR_STRUCT_PTR;
typedef volatile struct MCF51XX_ftsr_struct _PTR_ VMCF51XX_FTSR_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif
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
* $FileName: mcf51xx_pmc.h$
* $Version : 3.0.1.0$
* $Date    : May-21-2009$
*
* Comments:
*
*   This file contains the type definitions for the mcf51xx SPI module.
*
*END************************************************************************/

#ifndef __mcf51xx_pmc_h__
#define __mcf51xx_pmc_h__

#define __mcf51xx_pmc_h__version "$Version:3.0.1.0$"
#define __mcf51xx_pmc_h__date    "$Date:May-21-2009$"

#ifdef __cplusplus
extern "C" {
#endif

// bits in SPMSC1
#define MCF51XX_PMC_SPMSC1_LVDF     0x80
#define MCF51XX_PMC_SPMSC1_LVDACK   0x40
#define MCF51XX_PMC_SPMSC1_LVDIE    0x20
#define MCF51XX_PMC_SPMSC1_LVDRE    0x10
#define MCF51XX_PMC_SPMSC1_LVDSE    0x08
#define MCF51XX_PMC_SPMSC1_LVDE     0x04
#define MCF51XX_PMC_SPMSC1_BGBE     0x01

// bits in SPMSC2
#define MCF51XX_PMC_SPMSC2_LPR      0x80
#define MCF51XX_PMC_SPMSC2_LPRS     0x40
#define MCF51XX_PMC_SPMSC2_LPWUI    0x20
#define MCF51XX_PMC_SPMSC2_PPDF     0x08
#define MCF51XX_PMC_SPMSC2_PPDACK   0x04
#define MCF51XX_PMC_SPMSC2_PPDE     0x02
#define MCF51XX_PMC_SPMSC2_PPDC     0x01

// bits in SPMSC3
#define MCF51XX_PMC_SPMSC3_LVWF     0x80
#define MCF51XX_PMC_SPMSC3_LVWACK   0x40
#define MCF51XX_PMC_SPMSC3_LVDV     0x20
#define MCF51XX_PMC_SPMSC3_LVWV     0x10
#define MCF51XX_PMC_SPMSC3_LVWIE    0x08

/*
** MCF51CN_pmc_struct
** This structure defines System Integration Module registers
*/
typedef struct MCF51XX_pmc_struct
{
  uchar  SPMSC1;    /*** SPMSC1 - System Power Management Status and Control Register 1; 0xFFFF8120 ***/
  uchar  SPMSC2;    /*** SPMSC2 - System Power Management Status and Control Register 2; 0xFFFF8121 ***/
  uchar  reserved00[1];  
  uchar  SPMSC3;    /*** SPMSC3 - System Power Management Status and Control Register 3; 0xFFFF8123 ***/
} MCF51XX_PMC_STRUCT, _PTR_ MCF51XX_PMC_STRUCT_PTR;
typedef volatile struct MCF51XX_pmc_struct _PTR_ VMCF51XX_PMC_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif
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
* $FileName: mcf51ac_adc.h$
* $Version : 3.6.2.0$
* $Date    : Sep-7-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf51xx ADC module.
*
*END************************************************************************/

#ifndef __mcf51ac_adc_h__
#define __mcf51ac_adc_h__

#define __mcf51ac_adc_h__version "$Version:3.6.2.0$"
#define __mcf51ac_adc_h__date    "$Date:Sep-7-2010$"

#ifdef __cplusplus
extern "C" {
#endif


#define MCF51XX_ADCCFG_ADLPC(val)       (((val) & 1) << 7)
#define MCF51XX_ADCCFG_ADIV(val)        (((val) & 3) << 5)
#define MCF51XX_ADCCFG_ALSMP(val)       (((val) & 1) << 4)
#define MCF51XX_ADCCFG_MODE(val)        (((val) & 3) << 2)
#define MCF51XX_ADCCFG_ADICLK(val)      ((val) & 3)

#define MCF51XX_ADCSC1_COCO_MASK        (1 << 7)

#define MCF51XX_ADCSC1_AIEN_MASK        (1 << 6)
#define MCF51XX_ADCSC1_AIEN(val)        (((val) & 1) << 6)

#define MCF51XX_ADCSC1_ADCO_MASK        (1 << 5)
#define MCF51XX_ADCSC1_ADCO(val)        (((val) & 1) << 5)

#define MCF51XX_ADCSC1_ADCH_MASK        (0x1F)
#define MCF51XX_ADCSC1_ADCH(val)        ((val) & MCF51XX_ADCSC1_ADCH_MASK)

#define MCF51XX_ADCSC2_ADACT_MASK       (1 << 7)

/*------------------------------------------------------------------------*/
/*

/*
** MCF51AC_adc_struct
** This structure defines System Integration Module registers
*/

typedef struct MCF51AC_adc_struct
{
    uchar  ADCSC1;    /* Status and Control Register */       
    uchar  ADCSC2;    /* Status and Control Register 2 */
    uchar  ADCRH;     /* Data Result High Register */
    uchar  ADCRL;     /* Data Result Low Register */
    uchar  ADCCVH;    /* Compare Value High Register */
    uchar  ADCCVL;    /* Compare Value Low Register */
    uchar  ADCCFG;    /* Configuration Register */  
    uchar  APCTL1;    /* Pin Control 1 Register */
    uchar  APCTL2;    /* Pin Control 2 Register */
    uchar  APCTL3;    /* Pin Control 3 Register */
} MCF51AC_ADC_STRUCT, _PTR_ MCF51AC_ADC_STRUCT_PTR;
typedef volatile struct MCF51AC_adc_struct _PTR_ VMCF51AC_ADC_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif  /* __mcf51ac_adc_h__ */

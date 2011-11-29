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
* $FileName: mcf51ag_adc.h$
* $Version : 3.7.3.0$
* $Date    : Feb-22-2011$
*
* Comments:
*
*   This file contains the type definitions for the mcf51xx ADC module.
*
*END************************************************************************/

#ifndef __mcf51ag_adc_h__
#define __mcf51ag_adc_h__

#define __mcf51ag_adc_h__version "$Version:3.7.3.0$"
#define __mcf51ag_adc_h__date    "$Date:Feb-22-2011$"

#ifdef __cplusplus
extern "C" {
#endif

#define MCF51AG_ADC_CFG_ADICLK(x)               (x & 0x03)
#define MCF51AG_ADC_CFG_ADICLK_MASK             (0x0003)
#define MCF51AG_ADC_CFG_ADICLK_BUSCLK           (0x0000)
#define MCF51AG_ADC_CFG_ADICLK_BUSCLK2          (0x0001)
#define MCF51AG_ADC_CFG_ADICLK_ALTCLK           (0x0002)
#define MCF51AG_ADC_CFG_ADICLK_ADACK            (0x0003)
#define MCF51AG_ADC_CFG_MODE(x)                 ((x & 0x03) << 2) 
#define MCF51AG_ADC_CFG_MODE_MASK               (0x000C)
#define MCF51AG_ADC_CFG_MODE_8BIT               (0x0000)
#define MCF51AG_ADC_CFG_MODE_12BIT              (0x0004)
#define MCF51AG_ADC_CFG_MODE_10BIT              (0x0008)
#define MCF51AG_ADC_CFG_ADLSMP                  (0x0010)
#define MCF51AG_ADC_CFG_ADIV_MASK               (0x0060)
#define MCF51AG_ADC_CFG_ADIV(x)                 (((x) & 3) << 5)
#define MCF51AG_ADC_CFG_ADIV_1                  (0x0000)
#define MCF51AG_ADC_CFG_ADIV_2                  (0x0020)
#define MCF51AG_ADC_CFG_ADIV_4                  (0x0040)
#define MCF51AG_ADC_CFG_ADIV_8                  (0x0060)
#define MCF51AG_ADC_CFG_ADLPC                   (0x0080)

#define MCF51AG_ADC_SC1A_ADCCH_MASK             (0x001F)
#define MCF51AG_ADC_SC1A_ADCO                   (0x0020)
#define MCF51AG_ADC_SC1A_AIEN                   (0x0040)
#define MCF51AG_ADC_SC1A_COCO                   (0x0080)

#define MCF51AG_ADC_SC1B_ADCCH_MASK             (0x001F)
#define MCF51AG_ADC_SC1B_ADCO                   (0x0020)
#define MCF51AG_ADC_SC1B_AIEN                   (0x0040)
#define MCF51AG_ADC_SC1B_COCO                   (0x0080)

#define MCF51AG_ADC_SC2_ADACT                   (0x80)
#define MCF51AG_ADC_SC2_ADTRG                   (0x40)
#define MCF51AG_ADC_SC2_BB                      (0x01)
#define MCF51AG_ADC_SC2_DMAEN                   (0x08)
#define MCF51AG_ADC_SC2_REFSEL(x)               (x & 3)
#define MCF51AG_ADC_SC2_REFSL_MASK              (0x0003)
#define MCF51AG_ADC_SC2_REFSL_VREF              (0x0000)
#define MCF51AG_ADC_SC2_REFSL_VALT              (0x0001)
#define MCF51AG_ADC_SC2_REFSL_VBG               (0x0002)

/*------------------------------------------------------------------------*/
/*

/*
** MCF51AG_adc_struct
** This structure defines System Integration Module registers
*/

#ifdef __cplusplus
}
#endif

#endif  /* __mcf51ag_adc_h__ */

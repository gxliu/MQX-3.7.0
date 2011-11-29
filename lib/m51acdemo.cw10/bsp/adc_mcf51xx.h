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
* $FileName: adc_mcf51xx.h$
* $Version : 3.7.14.0$
* $Date    : Feb-22-2011$
*
* Comments:
*
*   CPU specific ADC driver header file
*
*END************************************************************************/

#ifndef __adc_mcf51xx_h__
#define __adc_mcf51xx_h__

#define __adc_mcf51xx_h__version "$Version : 3.7.14.0$"
#define __adc_mcf51xx_h__date    "$Date    : Feb-22-2011$"

/*
**  ADC constant definitions
*/

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_MAX_CLOCK           8000000     // max ADCK

#define ADC_HW_CHANNELS         1

#define ADC_RESOLUTION_8BIT     0
#define ADC_RESOLUTION_10BIT    2
#define ADC_RESOLUTION_12BIT    1

#define ADC_RESOLUTION_DEFAULT  ADC_RESOLUTION_12BIT

#define ADC_SOURCE_AN0          0x00
#define ADC_SOURCE_AN1          0x01
#define ADC_SOURCE_AN2          0x02
#define ADC_SOURCE_AN3          0x03
#define ADC_SOURCE_AN4          0x04
#define ADC_SOURCE_AN5          0x05
#define ADC_SOURCE_AN6          0x06
#define ADC_SOURCE_AN7          0x07
#define ADC_SOURCE_AN8          0x08
#define ADC_SOURCE_AN9          0x09
#define ADC_SOURCE_AN10         0x0A
#define ADC_SOURCE_AN11         0x0B
#define ADC_SOURCE_AN12         0x0C
#define ADC_SOURCE_AN13         0x0D
#define ADC_SOURCE_AN14         0x0E
#define ADC_SOURCE_AN15         0x0F
#define ADC_SOURCE_AN16         0x10
#define ADC_SOURCE_AN17         0x11
#define ADC_SOURCE_AN18         0x12
#define ADC_SOURCE_AN19         0x13
#define ADC_SOURCE_AN20         0x14
#define ADC_SOURCE_AN21         0x15
#define ADC_SOURCE_AN22         0x16
#define ADC_SOURCE_AN23         0x17
#define ADC_SOURCE_AN24         0x18
#define ADC_SOURCE_AN25         0x19
#define ADC_SOURCE_AN26         0x1A
#define ADC_SOURCE_AN27         0x1B
#define ADC_SOURCE_AN28         0x1C
#define ADC_SOURCE_AN29         0x1D
#define ADC_SOURCE_AN30         0x1E
#define ADC_SOURCE_AN31         0x1F

#define ADC_SOURCE_LAST         ADC_SOURCE_AN31
/*
**  ADC hardware specific errors
*/
#define ADC_ERROR_LWTIMER   (ADC_ERROR_BASE | (ADC_ERROR_HW_SPECIFIC + 0x00)) /* cannot initialize lwtimer */


/*FUNCTION****************************************************************
* 
* Function Name    : _bsp_get_adc_base_address
* Returned Value   : pointer to base of ADC registers
* Comments         :
*    This function returns base address of ADC related register space.
*
*END*********************************************************************/

pointer _bsp_get_adc_base_address();

#ifdef __cplusplus
}
#endif

#endif   /* __adc_mcf51xx_h__ */

/* EOF */

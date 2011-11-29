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
* $FileName: adc_mcf51em.c$
* $Version : 3.7.14.0$
* $Date    : Dec-17-2010$
*
* Comments:
*
*   This file contains the ADC driver CPU specific functions
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include <fio_prv.h>
#include "io.h"
#include "adc.h"
#include "adc_prv.h"
#include "adc_mcf51em_prv.h"

/* Declarations of IRQ handlers */
static void adc_complete_isr(pointer);

/* static variables for ADC driver */
static struct {
    uint_32  used_channel;  /* mask of used channels */
    ADC_CHANNEL_BUNDLE_PTR open_channels[8]; 
} adc_internal = { 0 };

ADC_BUNDLE adc_bundle;

static _mqx_int adc_set_calibration_data(_mqx_int adc_num, VMCF51EM_ADC16_CALIB_STRUCT_PTR calib_ptr);
static _mqx_int adc_get_calibration_data(_mqx_int adc_num, VMCF51EM_ADC16_CALIB_STRUCT_PTR calib_ptr);
static _mqx_int adc_calibrate(_mqx_int adc_num);
static void adc_process_data(_mqx_int adc_num, _mqx_int ch_num);

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_ioctl
* Returned Value   : int_32
* Comments         :
*    Returns result of ioctl operation.
*
*END*********************************************************************/
_mqx_int _adc_hw_ioctl(MQX_FILE_PTR f, _mqx_uint cmd, pointer param_ptr)
{
    VMCF51EM_ADC_STRUCT_PTR adc_ptr;
    ADC_DRIVER_BUNDLE_PTR adc_d_bundle = (ADC_DRIVER_BUNDLE_PTR) f->DEV_PTR->DRIVER_INIT_PTR;
    ADC_CHANNEL_BUNDLE_PTR adc_ch_bundle = (ADC_CHANNEL_BUNDLE_PTR) f->DEV_DATA_PTR;
    _mqx_int adc_num = adc_d_bundle->init->ADC_NUMBER;
    volatile uint_8_ptr status_reg;
    
    switch (cmd) 
    {
        case ADC_IOCTL_CALIBRATE:
            /* calibrate ADC autonomously */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* cannot run calibration on channel */
            if ((adc_internal.used_channel >> (ADC_MAX_CHANNELS * adc_num)) & ((1 << ADC_MAX_CHANNELS) - 1))
                return ADC_ERROR_NONEMPTY; /* calibration can be run only if no channel of ADC is opened */
            return adc_calibrate(adc_num);

        case ADC_IOCTL_SET_CALIBRATION:
            /* set calibration values to ADC without performing calibration */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* cannot set calibration data on channel */
            return adc_set_calibration_data(adc_num, (VMCF51EM_ADC16_CALIB_STRUCT_PTR) param_ptr);

        case ADC_IOCTL_GET_CALIBRATION:
            /* gets calibrated value */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* cannot get calibration data on channel */
            return adc_get_calibration_data(adc_num, (VMCF51EM_ADC16_CALIB_STRUCT_PTR) param_ptr);

        case ADC_IOCTL_SET_LONG_SAMPLE:
            /* sets sampling time for ADC module for long; param_ptr = (uint_32) cycles - see ADLSMP in Reference Manual */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* long sample must be set on device file, not on channel file */
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);

            adc_ptr->ADCCFG2 &= ~MCF51EM_ADC_CFG2_ADLSTS_MASK;
            if ((uint_32) param_ptr == 20)
                adc_ptr->ADCCFG2 |= MCF51EM_ADC_CFG2_ADLSTS_20;
            else if ((uint_32) param_ptr == 12)
                adc_ptr->ADCCFG2 |= MCF51EM_ADC_CFG2_ADLSTS_12;
            else if ((uint_32) param_ptr == 6)
                adc_ptr->ADCCFG2 |= MCF51EM_ADC_CFG2_ADLSTS_6;
            else if ((uint_32) param_ptr == 2)
                adc_ptr->ADCCFG2 |= MCF51EM_ADC_CFG2_ADLSTS_2;
            else
                return ADC_ERROR_BAD_PARAM; /* invalid parameter for ioctl command */

            adc_ptr->ADCCFG1 |= MCF51EM_ADC_CFG1_ADLSMP;
            break;

        case ADC_IOCTL_SET_SHORT_SAMPLE:
            /* sets sampling time for ADC module for short - see ADLSMP in Reference Manual */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* long sample must be set on device file, not on channel file */
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);

            adc_ptr->ADCCFG1 &= ~MCF51EM_ADC_CFG1_ADLSMP;
            break;

        case ADC_IOCTL_SET_HIGH_SPEED:
            /* sets high speed ADC module - see ADHSC bit in Reference Manual */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* high speed must be set on device file, not on channel file */
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);

            adc_ptr->ADCCFG2 |= MCF51EM_ADC_CFG2_ADHSC;
            break;
                                        
        case ADC_IOCTL_SET_LOW_SPEED:
            /* sets low speed ADC module - see ADHSC bit in Reference Manual */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* low speed must be set on device file, not on channel file */
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);

            adc_ptr->ADCCFG2 &= ~MCF51EM_ADC_CFG2_ADHSC;
            break;

        case ADC_IOCTL_SET_HW_AVERAGING:
            /* sets sample averaging by hardware; param_ptr = (uint_32) cycles - see AVGE bit in Reference Manual */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* averaging must be set on device file, not on channel file */
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);

            if ((uint_32) param_ptr == 0)
                adc_ptr->ADCSC3 &= ~MCF51EM_ADC_SC3_AVGE; /* if zero cycles, disable averaging */
            else {
                adc_ptr->ADCSC3 &= ~MCF51EM_ADC_SC3_AVGS_MASK;
                if ((uint_32) param_ptr == 32)
                    adc_ptr->ADCSC3 |= MCF51EM_ADC_SC3_AVGS_32 | MCF51EM_ADC_SC3_AVGE;
                else if ((uint_32) param_ptr == 16)
                    adc_ptr->ADCSC3 |= MCF51EM_ADC_SC3_AVGS_16 | MCF51EM_ADC_SC3_AVGE;
                else if ((uint_32) param_ptr == 8)
                    adc_ptr->ADCSC3 |= MCF51EM_ADC_SC3_AVGS_8 | MCF51EM_ADC_SC3_AVGE;
                else if ((uint_32) param_ptr == 4)
                    adc_ptr->ADCSC3 |= MCF51EM_ADC_SC3_AVGS_4 | MCF51EM_ADC_SC3_AVGE;
                else
                    return ADC_ERROR_BAD_PARAM; /* invalid parameter for ioctl command */
            }

            break;

        case ADC_IOCTL_SET_IDELAY_PROCESS:
            /* Postpones channel data processing */
            if (adc_ch_bundle == NULL)
                return ADC_ERROR_ONLY_CHANNEL; /* data processing can be postponed only on channel files */

            _int_disable();
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
            status_reg = (uint_8_ptr) &adc_ptr->ADCSC1[0];
            status_reg += adc_ch_bundle->ch_num;
            /* Before writing to register to disable COCO channel :) interrupt, we have to check COCO bit;
            ** this is needed as any write to register will clear COCO bit.
            ** Question: what if COCO bit is set after it was checked for? Answer: no other way, we lose one sample...
            */
            while (*status_reg & MCF51EM_ADC_SC1_COCO) {
                /* COCO bit is set, we have to read data before disabling interrupts */
                adc_process_data(adc_num, adc_ch_bundle->ch_num);
            }
            *status_reg &= ~MCF51EM_ADC_SC1_AIEN; /* disable interrupts, this also clears COCO bit */
            adc_bundle.late_process |= (1 << (ADC_MAX_CHANNELS * adc_num + adc_ch_bundle->ch_num));
            _int_enable();
            break;

        case ADC_IOCTL_SET_INT_PROCESS:
            /* Postpones channel data processing */
            if (adc_ch_bundle == NULL)
                return ADC_ERROR_ONLY_CHANNEL; /* data processing can be postponed only on channel files */

            _int_disable();
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
            status_reg = (uint_8_ptr) &adc_ptr->ADCSC1[0];
            status_reg += adc_ch_bundle->ch_num;
            /* Before writing to register to disable COCO channel :) interrupt, we have to check COCO bit;
            ** this is needed as any write to register will clear COCO bit.
            ** Question: what if COCO bit is set after it was checked for? Answer: no other way, we lose one sample...
            */
            while (*status_reg & MCF51EM_ADC_SC1_COCO) {
                /* COCO bit is set, we have to read data before disabling interrupts */
                adc_process_data(adc_num, adc_ch_bundle->ch_num);
            }
            *status_reg |= MCF51EM_ADC_SC1_AIEN; /* enable interrupts, this also clears COCO bit */
            adc_bundle.late_process &= ~(1 << (ADC_MAX_CHANNELS * adc_num + adc_ch_bundle->ch_num));
            _int_enable();            
            break;

        case ADC_IOCTL_SET_OFFSET: {
            uint_32 uparam_32 = (uint_32) param_ptr;
            uint_16 uparam_16 = (uint_16) uparam_32;

            /* Set offset for ADC module */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* Offset cannot be set on channel files */
            if (uparam_32 > MAX_UINT_16)
                return ADC_ERROR_BAD_PARAM; /* Cannot set offset that exceeds 16 bits */
            
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
            adc_ptr->ADCOFS = uparam_16;
            break;
        }           
        
        case ADC_IOCTL_SET_PLUS_GAIN: {
            uint_32 uparam_32 = (uint_32) param_ptr;
            uint_16 uparam_16 = (uint_16) uparam_32;

            /* Set offset for ADC module */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* Gain cannot be set on channel files */
            if (uparam_32 > MAX_UINT_16)
                return ADC_ERROR_BAD_PARAM; /* Cannot set gain that exceeds 16 bits */
            
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
            adc_ptr->ADCPG = uparam_16;
            break;
        }           

        case ADC_IOCTL_SET_MINUS_GAIN: {
            uint_32 uparam_32 = (uint_32) param_ptr;
            uint_16 uparam_16 = (uint_16) uparam_32;

            /* Set offset for ADC module */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* Gain cannot be set on channel files */
            if (uparam_32 > MAX_UINT_16)
                return ADC_ERROR_BAD_PARAM; /* Cannot set gain that exceeds 16 bits */
            
            adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
            adc_ptr->ADCMG = uparam_16;
            break;
        }           

        case ADC_IOCTL_SET_REFERENCE: {
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* Gain cannot be set on channel files */
            adc_ptr = (MCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
            adc_ptr->ADCSC2 &= ~MCF51EM_ADC_SC2_REFSL_MASK;
            if ((uint_32) param_ptr == ADC_REF_VREF)
                adc_ptr->ADCSC2 |= MCF51EM_ADC_SC2_REFSL_VREF;
            else if ((uint_32) param_ptr == ADC_REF_VALT)
                adc_ptr->ADCSC2 |= MCF51EM_ADC_SC2_REFSL_VALT;
            else if ((uint_32) param_ptr == ADC_REF_VBG)
                adc_ptr->ADCSC2 |= MCF51EM_ADC_SC2_REFSL_VBG;
            else
                return ADC_ERROR_BAD_PARAM; /* Cannot set any other reference */
            break;
        }

        default:
            return IO_ERROR_INVALID_IOCTL_CMD;
    }

    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_install
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific initialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adc_hw_install(char_ptr identifier, ADC_DRIVER_BUNDLE_PTR adc_d_bundle, pointer init)
{
    adc_d_bundle->init = (MCF51EM_ADC_INIT_STRUCT_PTR) init;
    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_init
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific initialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adc_hw_init(MQX_FILE_PTR f, ADC_PTR adc_d) 
{
    ADC_DRIVER_BUNDLE_PTR adc_d_bundle = (ADC_DRIVER_BUNDLE_PTR) f->DEV_PTR->DRIVER_INIT_PTR;
    _mqx_int adc_num = adc_num = adc_d_bundle->init->ADC_NUMBER;
    VMCF51EM_ADC_STRUCT_PTR adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);

    /* set AD clock to be as fast as 5 MHz */
    switch (adc_d_bundle->init->CLOCK_SOURCE) {
        case ADC_CLK_BUSCLK_ANY:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
#if BSP_BUS_CLOCK <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_1 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 2) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_2 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 4) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_4 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 8) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_8 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 16) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_8 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK2;
#else
                #error Cannot set ADC clock to be less than 5MHz.
#endif
            else {
                if ((BSP_BUS_CLOCK / (1 << adc_d_bundle->init->CLOCK_DIV)) <= ADC_MAX_FREQUENCY)
                    adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
                else if ((BSP_BUS_CLOCK / 2 / (1 << adc_d_bundle->init->CLOCK_DIV)) <= ADC_MAX_FREQUENCY)
                    adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51EM_ADC_CFG1_ADICLK_BUSCLK2;
                else
                    return ADC_ERROR_BAD_PARAM; /* such clock combination is too fast for ADC */
            }
            break;

        case ADC_CLK_BUSCLK:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
#if BSP_BUS_CLOCK <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_1 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 2) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_2 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 4) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_4 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 8) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_8 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
#else
                #error Cannot set ADC clock to be less than 5MHz.
#endif
            else if ((BSP_BUS_CLOCK / (1 << adc_d_bundle->init->CLOCK_DIV)) <= ADC_MAX_FREQUENCY)
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51EM_ADC_CFG1_ADICLK_BUSCLK;
            else
                return ADC_ERROR_BAD_PARAM; /* such clock combination is too fast for ADC */
            break;

        case ADC_CLK_BUSCLK2:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
#if (BSP_BUS_CLOCK / 16) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV_8 | MCF51EM_ADC_CFG1_ADICLK_BUSCLK2;
#else
                #error Cannot set ADC clock to be less than 5MHz.
#endif
            else if ((BSP_BUS_CLOCK / 2 / (1 << adc_d_bundle->init->CLOCK_DIV)) <= ADC_MAX_FREQUENCY)
                adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51EM_ADC_CFG1_ADICLK_BUSCLK2;
            else
                return ADC_ERROR_BAD_PARAM; /* such clock combination is too fast for ADC */
            break;

        case ADC_CLK_ALTERNATE:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
                return ADC_ERROR_BAD_PARAM; /* alternate clock + any division is not supported now */
            adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51EM_ADC_CFG1_ADICLK_ALTCLK;
            break;

        case ADC_CLK_ASYNC:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
                return ADC_ERROR_BAD_PARAM; /* async clock + any division is not supported now */
            adc_ptr->ADCCFG1 = MCF51EM_ADC_CFG1_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51EM_ADC_CFG1_ADICLK_ADACK;
            break;

        default:
            return ADC_ERROR_BAD_PARAM; /* invalid clock source */
    }

    if (adc_d->g.resolution == ADC_RESOLUTION_8BIT)
        adc_ptr->ADCCFG1 |= MCF51EM_ADC_CFG1_MODE_8BIT;
    else if (adc_d->g.resolution == ADC_RESOLUTION_10BIT)
        adc_ptr->ADCCFG1 |= MCF51EM_ADC_CFG1_MODE_10BIT;
    else if (adc_d->g.resolution == ADC_RESOLUTION_12BIT)
        adc_ptr->ADCCFG1 |= MCF51EM_ADC_CFG1_MODE_12BIT;
    else if (adc_d->g.resolution == ADC_RESOLUTION_16BIT)
        adc_ptr->ADCCFG1 |= MCF51EM_ADC_CFG1_MODE_16BIT;
    else
        return ADC_ERROR_BAD_PARAM; /* the specified resolution is not supported */

    adc_ptr->ADCSC2 |= MCF51EM_ADC_SC2_ADTRG; /* set HW trigger */
        
    adc_d->old_isr_data = (pointer) _int_get_isr_data(adc_d_bundle->init->ADC_VECTOR);
    adc_d->old_isr = (pointer) _int_install_isr(adc_d_bundle->init->ADC_VECTOR, adc_complete_isr, f);

    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_deinit
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific deinitialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adc_hw_deinit(MQX_FILE_PTR f, ADC_PTR adc_d)
{
    ADC_DRIVER_BUNDLE_PTR adc_d_bundle = (ADC_DRIVER_BUNDLE_PTR) f->DEV_PTR->DRIVER_INIT_PTR;

    _int_install_isr(adc_d_bundle->init->ADC_VECTOR, adc_d->old_isr, adc_d->old_isr_data);

    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_cpu_channel_init
* Returned Value   : int_32
* Comments         :
*    Returns result of ioctl operation.
*
*END*********************************************************************/
_mqx_int _adc_hw_channel_init(MQX_FILE_PTR f, ADC_CHANNEL_PTR adc_ch)
{
    ADC_DRIVER_BUNDLE_PTR adc_d_bundle = (ADC_DRIVER_BUNDLE_PTR) f->DEV_PTR->DRIVER_INIT_PTR;
    ADC_CHANNEL_BUNDLE_PTR adc_ch_bundle = (ADC_CHANNEL_BUNDLE_PTR) f->DEV_DATA_PTR;
    _mqx_int adc_num = adc_d_bundle->init->ADC_NUMBER;
    _mqx_int ch_num;
    VMCF51EM_ADC_STRUCT_PTR adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
    _mqx_uint used_ch = adc_internal.used_channel >> (ADC_MAX_CHANNELS * adc_num);
    volatile uint_8 *status_reg;
    uint_8 source_reg;

    adc_ch->b = adc_ch_bundle;

    source_reg = ADC_GET_CHANNEL(adc_ch->g.source);
    if (ADC_GET_DIFF(adc_ch->g.source))
        source_reg |= MCF51EM_ADC_SC1_DIFF;
    source_reg |= MCF51EM_ADC_SC1_AIEN;

    if (!(used_ch & 0x01))
        /* channel A is free, use it */
        ch_num = 0;
    else if (!(used_ch & 0x02))
        /* channel B is free, use it */
        ch_num = 1;
    else
        return ADC_ERROR_FULL; /* both channels are used, no more allowed; shouldn't happen */

    status_reg = &adc_ptr->ADCSC1[0];
    status_reg[ch_num] = source_reg;

    adc_ch_bundle->adc_num = adc_num;
    adc_ch_bundle->ch_num = ch_num;
    adc_internal.used_channel |= 0x01 << (ADC_MAX_CHANNELS * adc_num + ch_num);

    adc_internal.open_channels[ADC_MAX_CHANNELS * adc_num + ch_num] = adc_ch_bundle;

/*  NOT USED ON MCF51EMXX
    // from uknown reason the ADPC register is Little-Endian, unlike FSL ColdFire architecture customs
    
    if (pin_num < 8)
        adc_ptr->ADCAPCTL1 |= (1 << pin_num);
    else if (pin_num < 16)
        adc_ptr->ADCAPCTL1 |= (1 << (pin_num - 8));
    else if (pin_num < 24)
        adc_ptr->ADCAPCTL1 |= (1 << (pin_num - 16));
    else if (pin_num < 32)
        adc_ptr->ADCAPCTL1 |= (1 << (pin_num - 24));
    else
        return IO_ERROR; // invalid pin number
*/

    return _bsp_adc_io_init(ADC_GET_CHANNEL(adc_ch->g.source));
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_channel_deinit
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific deinitialization for ADC channel
*
*END*********************************************************************/
_mqx_int _adc_hw_channel_deinit(MQX_FILE_PTR f, ADC_CHANNEL_PTR adc_ch) 
{
    ADC_CHANNEL_BUNDLE_PTR adc_ch_bundle = (ADC_CHANNEL_BUNDLE_PTR) f->DEV_DATA_PTR;
    _mqx_int adc_num = adc_ch_bundle->adc_num;
    _mqx_int ch_num = adc_ch_bundle->ch_num;
    VMCF51EM_ADC_STRUCT_PTR adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
    volatile uint_8 *status_reg;

    /* deinit channel */
    status_reg = &adc_ptr->ADCSC1[0];
    _int_disable();
    status_reg[ch_num] &= ~MCF51EM_ADC_SC1_AIEN;
    adc_bundle.late_process &= ~(0x01 << (ADC_MAX_CHANNELS * adc_num + ch_num));
    _int_enable();

    adc_internal.used_channel &= ~(0x01 << (ADC_MAX_CHANNELS * adc_num + ch_num));
    adc_internal.open_channels[ADC_MAX_CHANNELS * adc_num + ch_num] = NULL;

/*  NOT USED ON MCF51EMXX
    if (pin_num < 8)
        adc_ptr->ADCAPCTL1 &= ~(1 << pin_num);
    else if (pin_num < 16)
        adc_ptr->ADCAPCTL1 &= ~(1 << (pin_num - 8));
    else if (pin_num < 24)
        adc_ptr->ADCAPCTL1 &= ~(1 << (pin_num - 16));
    else
        adc_ptr->ADCAPCTL1 &= ~(1 << (pin_num - 24));
*/
    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : adc_process_data
* Returned Value   : void
* Comments         : Process data result for specific channel
*
*END*********************************************************************/
static void adc_process_data(_mqx_int adc_num, _mqx_int ch_num)
{
    ADC_CHANNEL_PTR        adc_ch;
    ADT_CHANNEL_PTR        adt_ch;
    VMCF51EM_ADC_STRUCT_PTR adc_ptr;
    ADC_CHANNEL_BUNDLE_PTR adc_ch_bundle;
    volatile uint_16_ptr result_reg;
    volatile uint_8_ptr status_reg;

    adc_ptr = (VMCF51EM_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
    result_reg = (uint_16_ptr) &adc_ptr->ADCR[0];
    status_reg = (uint_8_ptr) &adc_ptr->ADCSC1[0];

    if (!(status_reg[ch_num] & MCF51EM_ADC_SC1_COCO))
        return; /* conversion was not completed on this channel */

    adc_ch_bundle = adc_internal.open_channels[ADC_MAX_CHANNELS * adc_num + ch_num];
    adc_ch = adc_ch_bundle->adc_ch;

    if (adc_ch_bundle->periods != 0) {
        volatile uint_32 dummy_read;
        /* dummy read to clear interrupt flag */
        dummy_read = (uint_32) result_reg[ch_num];
        adc_ch_bundle->periods--;
    } else {
        adc_ch_bundle->periods = adc_ch_bundle->periods_preset - 1;

        if (adc_ch->g.init_flags & ADC_CHANNEL_ACCUMULATE)
            /* if the channel has ADC_CHANNEL_ACCUMULATE, then accumulate result */
            adc_ch->g.buffer_driver->result += result_reg[ch_num];
        else
            /* else copy the result to the channel buffer */
            adc_ch->g.buffer_driver->result = result_reg[ch_num];
    
        adt_ch = adc_ch_bundle->adt_ch;
        if (!(adc_ch->g.init_flags & ADC_CHANNEL_ACCUMULATE) || !(adt_ch->g.samples)) {
            /* move driver pointer to next index, circullarily */
            if (++adc_ch->g.buffer_driver >= adc_ch->g.buffer_end)
                adc_ch->g.buffer_driver = adc_ch->g.buffer_start;
            /* if new value should overwrite old value in ring buffer, move read pointer to next value */
            if (adc_ch->g.buffer_driver == adc_ch->g.buffer_task) {
                if (++adc_ch->g.buffer_task >= adc_ch->g.buffer_end)
                    adc_ch->g.buffer_task = adc_ch->g.buffer_start;
            }
        }
        _adt_process_data(adc_ch_bundle);
    }
}

/*FUNCTION*****************************************************************
* 
* Function Name    : adc_process_all_data
* Returned Value   : void
* Comments         : Look at all channels and finds 
*
*END*********************************************************************/
void adc_process_all_data()
{
    _mqx_int adc_num, ch_num;

    /* conversion done, but which channel? */
    for (adc_num = 0; adc_num < ADC_MAX_MODULES; adc_num++) {
        for (ch_num = 0; ch_num < ADC_MAX_CHANNELS; ch_num++) {
            if (adc_internal.open_channels[ADC_MAX_CHANNELS * adc_num + ch_num] == NULL)
                continue;
            adc_process_data(adc_num, ch_num);
        }
    }
}

/*FUNCTION*****************************************************************
* 
* Function Name    : adc_complete_isr
* Returned Value   : void
* Comments         : IRQ handler for completed AD conversion(s)
*
*END*********************************************************************/
void adc_complete_isr
   (
      /* [IN] the file pointer */
      pointer param
   )
{ /* Body */
    MQX_FILE_PTR f = (MQX_FILE_PTR) param;
    ADC_DRIVER_BUNDLE_PTR adc_d_bundle = (ADC_DRIVER_BUNDLE_PTR) f->DEV_PTR->DRIVER_INIT_PTR;
    _mqx_int adc_num = adc_d_bundle->init->ADC_NUMBER;
    _mqx_int ch_num;

    for (ch_num = 0; ch_num < ADC_MAX_CHANNELS; ch_num++) {
        adc_process_data(adc_num, ch_num);
    }
}

/*FUNCTION****************************************************************
* 
* Function Name    : adc_calibrate
* Returned Value   : ADC_OK or ADC_ERROR
* Comments         : Calibrates the ADC module
*
*END*********************************************************************/
static _mqx_int adc_calibrate(_mqx_int adc_index)
{
    uint_16 cal_var;
    VMCF51EM_ADC_STRUCT_PTR adc_ptr = _bsp_get_adc_base_address(adc_index);
    struct {
        uint_8  ADCSC2;
        uint_8  ADCSC3;
    } saved_regs;

    if (adc_ptr == NULL)
        return ADC_ERROR_BAD_PARAM; /* no such ADC peripheral exists */

    saved_regs.ADCSC2 = adc_ptr->ADCSC2;
    saved_regs.ADCSC3 = adc_ptr->ADCSC3;
    
    /* Enable Software Conversion Trigger for Calibration Process */
    adc_ptr->ADCSC2 &= ~MCF51EM_ADC_SC2_ADTRG;

    /* Initiate calibration */
    adc_ptr->ADCSC3 |= MCF51EM_ADC_SC3_CAL;             

    /* Wait for conversion to be active */
    while (adc_ptr->ADCSC2 & MCF51EM_ADC_SC2_ADACT){}  
    /* Wait for conversion result to complete */
    while ((adc_ptr->ADCSC1[ADC_A] & MCF51EM_ADC_SC1_COCO) == 0){}  

    /* Check if calibration failed */
    if (adc_ptr->ADCSC3 & MCF51EM_ADC_SC3_CALF)  {
        /* Clear calibration failed flag */
        adc_ptr->ADCSC3 |= MCF51EM_ADC_SC3_CALF;
        
        /* calibration failed */
        return -1;
    }

    /* Calculate plus-side calibration values according to Calibration function described in reference manual. */
    /* 1. Initialize (clear) a 16b variable in RAM */
    cal_var  = 0x0000;
    /* 2. Add the following plus-side calibration results CLP0, CLP1, CLP2, CLP3, CLP4, and CLPS to the variable. */
    cal_var +=  adc_ptr->ADCCLP0; 
    cal_var +=  adc_ptr->ADCCLP1;
    cal_var +=  adc_ptr->ADCCLP2;
    cal_var +=  adc_ptr->ADCCLP3;
    cal_var +=  adc_ptr->ADCCLP4;
    cal_var +=  adc_ptr->ADCCLPS;

    /* 3. Divide the variable by two. */
    cal_var = cal_var / 2;

    /* 4. Set the MSB of the variable. */
    cal_var += 0x8000;

    /* 5. Store the value in the plus-side gain calibration registers ADCPGH and ADCPGL. */
    adc_ptr->ADCPG = cal_var;

    /* Repeat procedure for the minus-side gain calibration value. */ 
    /* 1. Initialize (clear) a 16b variable in RAM */
    cal_var  = 0x0000;

    /* 2. Add the following plus-side calibration results CLM0, CLM1, CLM2, CLM3, CLM4, and CLMS to the variable. */
    cal_var  = 0x0000;
    cal_var += adc_ptr->ADCCLM0; 
    cal_var += adc_ptr->ADCCLM1; 
    cal_var += adc_ptr->ADCCLM2; 
    cal_var += adc_ptr->ADCCLM3; 
    cal_var += adc_ptr->ADCCLM4; 
    cal_var += adc_ptr->ADCCLMS;
    
    /* 3. Divide the variable by two. */
    cal_var = cal_var / 2;

    /* 4. Set the MSB of the variable. */
    cal_var += 0x8000;

    /* 5. Store the value in the minus-side gain calibration registers ADCMGH and ADCMGL. */
    adc_ptr->ADCMG = cal_var;

    /* Clear CAL bit */
    // adc_ptr->ADCSC3 &= ~MCF51EM_ADC_SC3_CAL; // done in next line
    
    adc_ptr->ADCSC3 = saved_regs.ADCSC3;
    adc_ptr->ADCSC2 = saved_regs.ADCSC2;

    return ADC_OK;
}

/*FUNCTION****************************************************************
* 
* Function Name    : adc_get_calibration_data
* Returned Value   : ADC_OK or ADC_ERROR
* Comments         : Calibrates the ADC.
*    Gets (copies) calibrated data from ADC registers to memory
*
*END*********************************************************************/
static _mqx_int adc_get_calibration_data
(    /* ADC module index */
    _mqx_int                       adc_index, 
    /* pointer to structure to read the calibration data */
    VMCF51EM_ADC16_CALIB_STRUCT_PTR calib_ptr
)
{
    VMCF51EM_ADC_STRUCT_PTR adc_ptr = _bsp_get_adc_base_address(adc_index);
    
    if (calib_ptr == NULL)
        return ADC_ERROR_PARAM; /* pointer to store calibration data to is NULL */
    if (adc_ptr == NULL)
        return ADC_ERROR_BAD_PARAM; /* no such ADC peripheral exists */

    //FIXME: r51423 optimization with memcopy()
    calib_ptr->ADCOFS  = adc_ptr->ADCOFS; 
    calib_ptr->ADCCLP0 = adc_ptr->ADCCLP0;
    calib_ptr->ADCCLP1 = adc_ptr->ADCCLP1;
    calib_ptr->ADCCLP2 = adc_ptr->ADCCLP2;
    calib_ptr->ADCCLP3 = adc_ptr->ADCCLP3;
    calib_ptr->ADCCLP4 = adc_ptr->ADCCLP4;
    calib_ptr->ADCCLPS = adc_ptr->ADCCLPS;
    calib_ptr->ADCPG   = adc_ptr->ADCPG;  
    calib_ptr->ADCTST  = adc_ptr->ADCTST; 
    calib_ptr->ADCCLM0 = adc_ptr->ADCCLM0; 
    calib_ptr->ADCCLM1 = adc_ptr->ADCCLM1; 
    calib_ptr->ADCCLM2 = adc_ptr->ADCCLM2; 
    calib_ptr->ADCCLM3 = adc_ptr->ADCCLM3; 
    calib_ptr->ADCCLM4 = adc_ptr->ADCCLM4; 
    calib_ptr->ADCCLMS = adc_ptr->ADCCLMS;
    calib_ptr->ADCMG   = adc_ptr->ADCMG;  

    return ADC_OK;
}

/*FUNCTION****************************************************************
* 
* Function Name    : adc_set_calibration_data
* Returned Value   : ADC_OK or ADC_ERROR
* Comments         : Calibrates the ADC.
*    Sets directly calibration data to calibration registers
*
*END*********************************************************************/
static _mqx_int adc_set_calibration_data
(    /* ADC module index */
    _mqx_int                       adc_index, 
    /* pointer to structure to read the calibration data */
    VMCF51EM_ADC16_CALIB_STRUCT_PTR calib_ptr
)
{
    VMCF51EM_ADC_STRUCT_PTR adc_ptr = _bsp_get_adc_base_address(adc_index);
    
    if (calib_ptr == NULL)
        return ADC_ERROR_PARAM; /* pointer to store calibration data to is NULL */
    if (adc_ptr == NULL)
        return ADC_ERROR_BAD_PARAM; /* no such ADC peripheral exists */
    
    //FIXME: r51423 optimization with memcopy()
    adc_ptr->ADCOFS  = calib_ptr->ADCOFS;
    adc_ptr->ADCCLP0 = calib_ptr->ADCCLP0;
    adc_ptr->ADCCLP1 = calib_ptr->ADCCLP1;
    adc_ptr->ADCCLP2 = calib_ptr->ADCCLP2;
    adc_ptr->ADCCLP3 = calib_ptr->ADCCLP3;
    adc_ptr->ADCCLP4 = calib_ptr->ADCCLP4;
    adc_ptr->ADCCLPS = calib_ptr->ADCCLPS;
    adc_ptr->ADCPG   = calib_ptr->ADCPG;
    adc_ptr->ADCTST  = calib_ptr->ADCTST;
    adc_ptr->ADCCLM0 = calib_ptr->ADCCLM0; 
    adc_ptr->ADCCLM1 = calib_ptr->ADCCLM1; 
    adc_ptr->ADCCLM2 = calib_ptr->ADCCLM2; 
    adc_ptr->ADCCLM3 = calib_ptr->ADCCLM3; 
    adc_ptr->ADCCLM4 = calib_ptr->ADCCLM4; 
    adc_ptr->ADCCLMS = calib_ptr->ADCCLMS;
    adc_ptr->ADCMG   = calib_ptr->ADCMG;

    return ADC_OK;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _bsp_get_adc_base_address
* Returned Value   : pointer to base of ADC registers
* Comments         :
*    This function returns base address of ADC related register space.
*
*END*********************************************************************/
pointer _bsp_get_adc_base_address(_mqx_uint  adc_index)
{
    
    if (adc_index > ADC_MAX_MODULES) {
        return NULL;
    }
    else {    
        return (pointer)(&((VMCF51EM_STRUCT_PTR)BSP_IPSBAR)->ADC[adc_index]);
    }
}

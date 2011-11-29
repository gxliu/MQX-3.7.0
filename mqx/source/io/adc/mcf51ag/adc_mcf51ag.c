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
* $FileName: adc_mcf51ag.c$
* $Version : 3.7.3.0$
* $Date    : Feb-22-2011$
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
#include "adc_mcf51ag_prv.h"  

/* Declarations of IRQ handlers */
static void adc_complete_isr(pointer);

/* static variables for ADC driver */
static struct {
    uint_32  used_channel;  /* mask of used channels */
    ADC_CHANNEL_BUNDLE_PTR open_channels[8]; 
} adc_internal = { 0 };

ADC_BUNDLE adc_bundle;

static void adc_process_data(_mqx_int ch_num);

#define adc_num 0
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
    VMCF51AG_ADC_STRUCT_PTR adc_ptr;
    ADC_DRIVER_BUNDLE_PTR adc_d_bundle = (ADC_DRIVER_BUNDLE_PTR) f->DEV_PTR->DRIVER_INIT_PTR;
    ADC_CHANNEL_BUNDLE_PTR adc_ch_bundle = (ADC_CHANNEL_BUNDLE_PTR) f->DEV_DATA_PTR;
    volatile uint_8_ptr status_reg;
    
    switch (cmd) 
    {
        

        case ADC_IOCTL_SET_LONG_SAMPLE:
            /* sets sampling time for ADC module for long; param_ptr = (uint_32) cycles - see ADLSMP in Reference Manual */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* long sample must be set on device file, not on channel file */
            adc_ptr = (VMCF51AG_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
            adc_ptr->ADCCFG |= MCF51AG_ADC_CFG_ADLSMP;
            break;

        case ADC_IOCTL_SET_SHORT_SAMPLE:
            /* sets sampling time for ADC module for short - see ADLSMP in Reference Manual */
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* long sample must be set on device file, not on channel file */
            adc_ptr = (VMCF51AG_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);

            adc_ptr->ADCCFG &= ~MCF51AG_ADC_CFG_ADLSMP;
            break;

        case ADC_IOCTL_SET_INT_PROCESS:
            /* Postpones channel data processing */
            if (adc_ch_bundle == NULL)
                return ADC_ERROR_ONLY_CHANNEL; /* data processing can be postponed only on channel files */

            _int_disable();
            adc_ptr = (VMCF51AG_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
            status_reg = (uint_8_ptr) &adc_ptr->ADCSC1A;
            status_reg += adc_ch_bundle->ch_num;
            /* Before writing to register to disable COCO channel :) interrupt, we have to check COCO bit;
            ** this is needed as any write to register will clear COCO bit.
            ** Question: what if COCO bit is set after it was checked for? Answer: no other way, we lose one sample...
            */
            while (*status_reg & MCF51AG_ADC_SC1A_COCO) {
                /* COCO bit is set, we have to read data before disabling interrupts */
                adc_process_data(adc_ch_bundle->ch_num);
            }
            *status_reg |= MCF51AG_ADC_SC1A_AIEN; /* enable interrupts, this also clears COCO bit */
            adc_bundle.late_process &= ~(1 << (ADC_MAX_CHANNELS * adc_num + adc_ch_bundle->ch_num));
            _int_enable();            
            break;        

        case ADC_IOCTL_SET_REFERENCE: {
            if (adc_ch_bundle != NULL)
                return ADC_ERROR_ONLY_DEVICE; /* Gain cannot be set on channel files */
            adc_ptr = (MCF51AG_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
            adc_ptr->ADCSC2 &= ~MCF51AG_ADC_SC2_REFSL_MASK;
            if ((uint_32) param_ptr == ADC_REF_VREF)
                adc_ptr->ADCSC2 |= MCF51AG_ADC_SC2_REFSL_VREF;
            else if ((uint_32) param_ptr == ADC_REF_VALT)
                adc_ptr->ADCSC2 |= MCF51AG_ADC_SC2_REFSL_VALT;
            else if ((uint_32) param_ptr == ADC_REF_VBG)
                adc_ptr->ADCSC2 |= MCF51AG_ADC_SC2_REFSL_VBG;
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
    adc_d_bundle->init = (MCF51AG_ADC_INIT_STRUCT_PTR) init;
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
    VMCF51AG_ADC_STRUCT_PTR adc_ptr = (VMCF51AG_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
     VMCF51AG_STRUCT_PTR     mcf51xx_ptr = ((VMCF51AG_STRUCT_PTR)BSP_IPSBAR);
    
    
    /* set AD clock to be as fast as 5 MHz */
    switch (adc_d_bundle->init->CLOCK_SOURCE) {
        case ADC_CLK_BUSCLK_ANY:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
#if BSP_BUS_CLOCK <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_1 | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 2) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_2 | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 4) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_4 | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 8) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_8 | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 16) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_8 | MCF51AG_ADC_CFG_ADICLK_BUSCLK2;
#else
                #error Cannot set ADC clock to be less than 5MHz.
#endif
            else {
                if ((BSP_BUS_CLOCK / (1 << adc_d_bundle->init->CLOCK_DIV)) <= ADC_MAX_FREQUENCY)
                    adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
                else if ((BSP_BUS_CLOCK / 2 / (1 << adc_d_bundle->init->CLOCK_DIV)) <= ADC_MAX_FREQUENCY)
                    adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51AG_ADC_CFG_ADICLK_BUSCLK2;
                else
                    return ADC_ERROR_BAD_PARAM; /* such clock combination is too fast for ADC */
            }
            break;

        case ADC_CLK_BUSCLK:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
#if BSP_BUS_CLOCK <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_1 | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 2) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_2 | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 4) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_4 | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
#elif (BSP_BUS_CLOCK / 8) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_8 | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
#else
                #error Cannot set ADC clock to be less than 5MHz.
#endif
            else if ((BSP_BUS_CLOCK / (1 << adc_d_bundle->init->CLOCK_DIV)) <= ADC_MAX_FREQUENCY)
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51AG_ADC_CFG_ADICLK_BUSCLK;
            else
                return ADC_ERROR_BAD_PARAM; /* such clock combination is too fast for ADC */
            break;

        case ADC_CLK_BUSCLK2:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
#if (BSP_BUS_CLOCK / 16) <= ADC_MAX_FREQUENCY
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV_8 | MCF51AG_ADC_CFG_ADICLK_BUSCLK2;
#else
                #error Cannot set ADC clock to be less than 5MHz.
#endif
            else if ((BSP_BUS_CLOCK / 2 / (1 << adc_d_bundle->init->CLOCK_DIV)) <= ADC_MAX_FREQUENCY)
                adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51AG_ADC_CFG_ADICLK_BUSCLK2;
            else
                return ADC_ERROR_BAD_PARAM; /* such clock combination is too fast for ADC */
            break;

        case ADC_CLK_ALTERNATE:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
                return ADC_ERROR_BAD_PARAM; /* alternate clock + any division is not supported now */
            adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51AG_ADC_CFG_ADICLK_ALTCLK;
            break;

        case ADC_CLK_ASYNC:
            if (adc_d_bundle->init->CLOCK_DIV == ADC_DIV_ANY)
                return ADC_ERROR_BAD_PARAM; /* async clock + any division is not supported now */
            adc_ptr->ADCCFG = MCF51AG_ADC_CFG_ADIV(adc_d_bundle->init->CLOCK_DIV) | MCF51AG_ADC_CFG_ADICLK_ADACK;
            break;

        default:
            return ADC_ERROR_BAD_PARAM; /* invalid clock source */
    }

    if (adc_d->g.resolution == ADC_RESOLUTION_8BIT)
        adc_ptr->ADCCFG |= MCF51AG_ADC_CFG_MODE_8BIT;
    else if (adc_d->g.resolution == ADC_RESOLUTION_10BIT)
        adc_ptr->ADCCFG |= MCF51AG_ADC_CFG_MODE_10BIT;
    else if (adc_d->g.resolution == ADC_RESOLUTION_12BIT)
        adc_ptr->ADCCFG |= MCF51AG_ADC_CFG_MODE_12BIT;
    else
        return ADC_ERROR_BAD_PARAM; /* the specified resolution is not supported */
   
    
     
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
    _mqx_int ch_num;
    VMCF51AG_ADC_STRUCT_PTR adc_ptr = (VMCF51AG_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
    _mqx_uint used_ch = adc_internal.used_channel >> (ADC_MAX_CHANNELS * adc_num);
    
    uint_8 source_reg;
    
    if(IO_ERROR == _bsp_adc_io_init(ADC_GET_CHANNEL(adc_ch->g.source)))
      return IO_ERROR;
               
    adc_ptr->ADCSC2 |= MCF51AG_ADC_SC2_ADTRG; /* set HW trigger */
    
    adc_ch->b = adc_ch_bundle;

    source_reg = ADC_GET_CHANNEL(adc_ch->g.source);
    
    source_reg |= MCF51AG_ADC_SC1A_AIEN;

    for (ch_num = 0; ch_num < ADC_MAX_CHANNELS; ch_num++)
        if (((1 << ch_num) & used_ch) == 0)
            break; /* found free, not used channel */
    if (ch_num == ADC_MAX_CHANNELS)
        return ADC_ERROR_FULL; /* all channels are used, no more allowed; shouldn't happen */

    if(ch_num == 0)
        adc_ptr->ADCSC1A = source_reg;
    else
        adc_ptr->ADCSC1B = source_reg;

    
  
    adc_ch_bundle->ch_num = ch_num;
    adc_internal.used_channel |= 0x01 << (ADC_MAX_CHANNELS * adc_num + ch_num);

    adc_internal.open_channels[ADC_MAX_CHANNELS * adc_num + ch_num] = adc_ch_bundle;

    return ADC_OK;
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
    _mqx_int ch_num = adc_ch_bundle->ch_num;
    VMCF51AG_ADC_STRUCT_PTR adc_ptr = (VMCF51AG_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
    volatile uint_8 *status_reg;

    /* deinit channel */
    status_reg = &adc_ptr->ADCSC1A;
    _int_disable();
    status_reg[ch_num] &= ~MCF51AG_ADC_SC1A_AIEN;
    adc_bundle.late_process &= ~(0x01 << (ADC_MAX_CHANNELS * adc_num + ch_num));
    _int_enable();

    adc_internal.used_channel &= ~(0x01 << (ADC_MAX_CHANNELS * adc_num + ch_num));
    adc_internal.open_channels[ADC_MAX_CHANNELS * adc_num + ch_num] = NULL;

    return ADC_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : adc_process_data
* Returned Value   : void
* Comments         : Process data result for specific channel
*
*END*********************************************************************/
static void adc_process_data(_mqx_int ch_num)
{
    ADC_CHANNEL_PTR        adc_ch;
    ADT_CHANNEL_PTR        adt_ch;
    VMCF51AG_ADC_STRUCT_PTR adc_ptr;
    ADC_CHANNEL_BUNDLE_PTR adc_ch_bundle;
    volatile uint_16_ptr result_reg;
    volatile uint_8_ptr status_reg;

    adc_ptr = (VMCF51AG_ADC_STRUCT_PTR) _bsp_get_adc_base_address(adc_num);
    result_reg = (uint_16_ptr) &adc_ptr->ADCRA;
    status_reg = (uint_8_ptr) &adc_ptr->ADCSC1A;

    if (!(status_reg[ch_num * 0x14] & MCF51AG_ADC_SC1A_COCO))
        return; /* conversion was not completed on this channel */

    adc_ch_bundle = adc_internal.open_channels[ADC_MAX_CHANNELS * adc_num + ch_num];
    /* Question: can adc_ch_bundle == NULL ever? Answer: yes, ChA is running all the time,
    ** even if it was closed. This is because of operation of ADC, that cannot run without ChA
    ** running. */
    if ((adc_ch_bundle == NULL) || (adc_ch_bundle->waste_channel)) {
        volatile uint_32 dummy_read;
        /* dummy read to clear interrupt flag */
        dummy_read = (uint_32) result_reg[ch_num];
        return; /* that's all, folks! */
    }

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
    _mqx_int ch_num;

    /* conversion done, but which channel? */
    for (ch_num = 0; ch_num < ADC_MAX_CHANNELS; ch_num++) {
       if (adc_internal.open_channels[ADC_MAX_CHANNELS * adc_num + ch_num] == NULL)
          continue;
       adc_process_data(ch_num);
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
    _mqx_int ch_num;

    for (ch_num = 0; ch_num < ADC_MAX_CHANNELS; ch_num++) {
        adc_process_data(ch_num);
    }
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
        return (pointer)(&((VMCF51AG_STRUCT_PTR)BSP_IPSBAR)->ADC);
    }
}

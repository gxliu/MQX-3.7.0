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
* $FileName: adc_mcf51xx.c$
* $Version : 3.7.16.0$
* $Date    : Mar-2-2011$
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
#include <lwtimer.h>
#include "adc.h"
#include "adc_prv.h"
#include "adc_mcf51xx_prv.h"


#if     PSP_MQX_CPU_IS_MCF51CN
    #define VMCF51XX_STRUCT_PTR     VMCF51CN_STRUCT_PTR
    #define VMCF51XX_ADC_STRUCT_PTR VMCF51CN_ADC_STRUCT_PTR  
#elif   PSP_MQX_CPU_IS_MCF51AC
    #define VMCF51XX_STRUCT_PTR     VMCF51AC_STRUCT_PTR
    #define VMCF51XX_ADC_STRUCT_PTR VMCF51AC_ADC_STRUCT_PTR  
#elif   PSP_MQX_CPU_IS_MCF51JM
    #define VMCF51XX_STRUCT_PTR     VMCF51JM_STRUCT_PTR
    #define VMCF51XX_ADC_STRUCT_PTR VMCF51AC_ADC_STRUCT_PTR     
#elif   PSP_MQX_CPU_IS_MCF51AG
    #define VMCF51XX_STRUCT_PTR     VMCF51AG_STRUCT_PTR
    #define VMCF51XX_ADC_STRUCT_PTR VMCF51AG_ADC_STRUCT_PTR 
#endif

/* static variables */
static uint_32               ch_mask, last_mask;
static ADC_DRIVER_BUNDLE_PTR driver_bundle = NULL;

/* Declarations of IRQ handlers */
static void adc_complete_isr(pointer);
static void adc_conv_end(uint_16 *results_buf, ADC_HW_CHANNEL_MASK mask);

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_ioctl
* Returned Value   : _mqx_int
* Comments         :
*    Returns result of ioctl operation.
*
*END*********************************************************************/
_mqx_int _adc_hw_ioctl(MQX_FILE_PTR f, _mqx_uint cmd, pointer param_ptr)
{
    return IO_ERROR_INVALID_IOCTL_CMD;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_install
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific initialization for ADC driver (during install)
*
*END*********************************************************************/
_mqx_int _adc_hw_install(char_ptr, ADC_DRIVER_BUNDLE_PTR adc_driver_bundle, pointer)
{
   driver_bundle = adc_driver_bundle; /* store driver bundle struct pointer locally */
   return IO_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_init
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific initialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adc_hw_init(MQX_FILE_PTR f, ADC_PTR adc)
{
    
    VMCF51XX_STRUCT_PTR     mcf51xx_ptr = ((VMCF51XX_STRUCT_PTR)BSP_IPSBAR);
    VMCF51XX_ADC_STRUCT_PTR adc_ptr     = &((VMCF51XX_STRUCT_PTR)BSP_IPSBAR)->ADC;
    
    _mqx_uint req_div, div, clk_src;
    void (_CODE_PTR_ old_isr_adc1)(pointer);
    void (_CODE_PTR_ old_isr_timer)(pointer);
    pointer old_isr_adc1_param;
        
    /* Check ADC configuration */
    if (adc->g.resolution != ADC_RESOLUTION_8BIT &&
        adc->g.resolution != ADC_RESOLUTION_10BIT &&
        adc->g.resolution != ADC_RESOLUTION_12BIT)
        return ADC_ERROR_BAD_PARAM; /* cannot set ADC resolution */
        
    if (BSP_BUS_CLOCK / ADC_MAX_CLOCK > 16)
        return ADC_ERROR_BAD_PARAM; /* cannot set correct ADCK (from bus clock) */
        
    /* Enable ADC clock */
    #if PSP_MQX_CPU_IS_MCF51JM | PSP_MQX_CPU_IS_MCF51AG
      mcf51xx_ptr->SIMX.SCGC1 |= MCF51XX_SCGC1_ADC_MASK;  
    #else 
      mcf51xx_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_ADC_MASK;
    #endif
    
    /* Set ADC clock */
    clk_src = (BSP_BUS_CLOCK / ADC_MAX_CLOCK > 8) ? 1 : 0;
    
    /* Calculate ADC divider */
    req_div = (clk_src) ? (BSP_BUS_CLOCK / 2 / ADC_MAX_CLOCK) : (BSP_BUS_CLOCK / ADC_MAX_CLOCK);
    for (div = 0; (req_div > (1 << div)) && (div < 4); div++) {}
    
    /* Save exact ADC hw clock frequency */
    adc->g.adc_frq = (clk_src) ? (BSP_BUS_CLOCK / 2 / ADC_MAX_CLOCK / (1 << div)) : (BSP_BUS_CLOCK / ADC_MAX_CLOCK / (1 << div)); 
    adc_ptr->ADCCFG = 
        MCF51XX_ADCCFG_ADLPC(0)                | /* high power consuption    */
        MCF51XX_ADCCFG_ADIV(div)               | /* divider                  */
        MCF51XX_ADCCFG_ALSMP(0)                | /* short sample time        */
        MCF51XX_ADCCFG_MODE(adc->g.resolution) | /* mode                     */
        MCF51XX_ADCCFG_ADICLK(clk_src);          /* clock source - bus clock */

    /* adc isr */
    old_isr_adc1_param = _int_get_isr_data(BSP_ADC_INTERRUPT_VECTOR);
    old_isr_adc1 = _int_install_isr(BSP_ADC_INTERRUPT_VECTOR, adc_complete_isr, NULL);
    
    if (old_isr_adc1 == NULL)
        return ADC_ERROR_ISR; /* should not happen, old ISR should not be NULL */

    /* adc conf */
    adc_ptr->ADCSC2 = 0;

    return IO_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_deinit
* Returned Value   : _mqx_int
* Comments         :
*    Performs CPU specific deinitialization for ADC driver
*
*END*********************************************************************/
_mqx_int _adc_hw_deinit(MQX_FILE_PTR, ADC_PTR)
{
    return IO_OK;
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
    if (adc_ch->g.source > ADC_SOURCE_LAST)
        /* ADC_SOURCE constant does not match any source signal for this CPU */
        return ADC_ERROR_BAD_PARAM; /* ADC_SOURCE_ constant does not match any source signal for this CPU */
      
    /* configure GPIO and MUX for ADC */
    return _bsp_adc_io_init(adc_ch->g.source);
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
    return IO_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : _adc_hw_measure
* Returned Value   : _mqx_int
* Comments         :
*    Starts AD conversion on specified channels defined by mask
*
*END*********************************************************************/
void _adc_hw_measure(ADC_HW_CHANNEL_MASK mask) 
{
    _mqx_int                i;
    ADC_HW_CHANNEL_MASK     tmp = mask;
    VMCF51XX_ADC_STRUCT_PTR adc_ptr = &((VMCF51XX_STRUCT_PTR)BSP_IPSBAR)->ADC;
    
    ch_mask = last_mask = mask;
    last_mask = mask;

    
    /* find channel with lowest channel number to trigger */
    for (i = 0; i < ADC_MAX_CHANNELS && tmp; i++, tmp >>= 1) {
        if (tmp & 1) {
            adc_ptr->ADCSC1 = MCF51XX_ADCSC1_AIEN_MASK | MCF51XX_ADCSC1_ADCH(i);
            break;
        }    
    }
}

/*FUNCTION*****************************************************************
* 
* Function Name    : adc_cpu_isr
* Returned Value   : void
* Comments         : IRQ handler for completed AD conversion(s)
*    In adc_c.channels_to_next_adc we have list of channels that
*    have been sampled and whole we need to handle the results.
*    We will copy results from AD converter to channels buffers.
*    Since AD converter can hold 8 samples a time, we check if any
*    other channel needs to be sampled and if yes, prepare next AD
*    conversion.
*
*END*********************************************************************/
void adc_complete_isr
   (
      /* [IN] the address of the device specific information */
      pointer parameter
   )
{ /* Body */
    VMCF51XX_ADC_STRUCT_PTR adc_ptr = &((VMCF51XX_STRUCT_PTR)BSP_IPSBAR)->ADC;
    uint_16                 results_internal[ADC_MAX_CHANNELS];
    _mqx_uint               ch = adc_ptr->ADCSC1 & MCF51XX_ADCSC1_ADCH_MASK;
    _mqx_int                i;
    ADC_HW_CHANNEL_MASK     mask;
#if PSP_MQX_CPU_IS_MCF51AG
    results_internal[ch] = adc_ptr->ADCRA >> 3;
#else
    /* read result from ADC result registers*/
    results_internal[ch] = ((adc_ptr->ADCRH << 8) | adc_ptr->ADCRL);
#endif
    ch_mask &= ~(1 << ch);
    
    if (ch_mask) {
        /* trigger next conversion...*/
        for (i = ch + 1, mask = (ch_mask >> (ch + 1)); i < ADC_MAX_CHANNELS && mask; i++) {
            if (mask & 1) {
                adc_ptr->ADCSC1 = MCF51XX_ADCSC1_AIEN_MASK | MCF51XX_ADCSC1_ADCH(i);
                break;
            }
                
            mask >>= 1;
        }
    }
    else {
        /* measure finished */
        adc_conv_end(results_internal, last_mask);
    }
}

/*FUNCTION*****************************************************************
* 
* Function Name    : adc_conv_end
* Returned Value   : 
* Comments         : This is called by low-level driver to inform generic
*                    driver, that some conversion was performed. Function
*                    moves stored data to the channel buffers.
*END*********************************************************************/
static void adc_conv_end(uint_16 *results_buf, ADC_HW_CHANNEL_MASK mask)
{
    _mqx_int i;
    ADC_CHANNEL_PTR *adc_ch = driver_bundle->adc_ch;
    ADT_CHANNEL_PTR *adt_ch = driver_bundle->adt_ch;

    for (i = 0; i < ADC_MAX_CHANNELS; i++) {
        if (!adc_ch[i] || !(adt_ch[i]->g.runtime_flags & ADC_CHANNEL_RESUMED) || !(mask & (1 << adc_ch[i]->g.source)))
            continue;
            
        if (adc_ch[i]->g.init_flags & ADC_CHANNEL_ACCUMULATE)
            /* if the channel has ADC_CHANNEL_ACCUMULATE, then accumulate result */
            adc_ch[i]->g.buffer_driver->result += results_buf[adc_ch[i]->g.source];

        else
            /* else copy the result to the channel buffer */
            adc_ch[i]->g.buffer_driver->result = results_buf[adc_ch[i]->g.source];

        if (!(adc_ch[i]->g.init_flags & ADC_CHANNEL_ACCUMULATE) || !(adt_ch[i]->g.samples)) {
            /* move driver pointer to next index, circullarily */
            if (++adc_ch[i]->g.buffer_driver >= adc_ch[i]->g.buffer_end)
                adc_ch[i]->g.buffer_driver = adc_ch[i]->g.buffer_start;

            /* if new value should overwrite old value in ring buffer, move read pointer to next value */
            if (adc_ch[i]->g.buffer_driver == adc_ch[i]->g.buffer_task) {
                if (++adc_ch[i]->g.buffer_task >= adc_ch[i]->g.buffer_end)
                    adc_ch[i]->g.buffer_task = adc_ch[i]->g.buffer_start;
            }
        }
        
        if (adt_ch[i]->g.samples) {
            adt_ch[i]->g.samples--;
        }
        else {
#if MQX_USE_LWEVENTS
            /* if it is the last sample in the batch, then set event */
            if (adt_ch[i]->g.complete_event)
                _lwevent_set(adt_ch[i]->g.complete_event, adt_ch[i]->g.event_mask); /* set completion event */
#endif
                
            if (adc_ch[i]->g.init_flags & ADC_CHANNEL_MEASURE_ONCE)
                adt_ch[i]->g.runtime_flags &= ~ADC_CHANNEL_RUNNING;
            
            adt_ch[i]->g.samples = adt_ch[i]->g.samples_preset;
        }
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

pointer _bsp_get_adc_base_address()
{
    return (pointer)(&((VMCF51XX_STRUCT_PTR)BSP_IPSBAR)->ADC);
}

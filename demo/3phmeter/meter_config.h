/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
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
* $FileName: meter_config.h$
* $Version : 3.5.6.0$
* $Date    : Jan-20-2010$
*
* Comments:
*
*END************************************************************************/

#ifndef __METER_CONFIG_H__
    #define __METER_CONFIG_H__


/*
**  Define line frequency which can be 50 or 60 Hz
*/
#define LINE_FREQUENCY          (50)


/*
**  Define number of samples per line period
**  It affects the size of buffers used for sampling
**  The valid values are 32, 64, 128
*/
#define SAMPLES_PER_PERIOD      (64)

/* Allocate ADC sample buffers */
#define SAMPLE_BUFFER           (SAMPLES_PER_PERIOD + 16)

/* Sampling period in microseconds */
#define ADC_SAMPLING_PERIOD     (1000000 / (LINE_FREQUENCY) / (SAMPLES_PER_PERIOD))
#define ADC_IDELAY              (ADC_SAMPLING_PERIOD - 10)    
#define ADC_HARDWARE_AVERAGING  (0)
#define ADC_LONG_SAMPLE         (2)
#define ADC_RESULT_RANGE_SCALE  0xFFFF  /* not implemented in ADC driver */

/* Delay voltage and current sampling from trigger point in microseconds */
#define ADC_VOLTAGE_DELAY       (0)
#define ADC_CURRENT_DELAY       (ADC_SAMPLING_PERIOD / 2)

/* LWEVENT masks for meter_shared_event */
#define ADC_DATA_READY_MASK     (1 << 0)
#define IO_SW1_MASK             (1 << 1)
#define IO_SW2_MASK             (1 << 2)
#define IO_SW3_MASK             (1 << 3)
#define IO_SW4_MASK             (1 << 4)

extern LWEVENT_STRUCT           meter_shared_event;


/* Buffers used for calculation */
extern int_16                   iL1_buff[SAMPLES_PER_PERIOD];
extern int_16                   vL1_buff[SAMPLES_PER_PERIOD];
extern int_16                   iL2_buff[SAMPLES_PER_PERIOD];
extern int_16                   vL2_buff[SAMPLES_PER_PERIOD];
extern int_16                   iL3_buff[SAMPLES_PER_PERIOD];
extern int_16                   vL3_buff[SAMPLES_PER_PERIOD];


#endif /* __METER_CONFIG_H__ */

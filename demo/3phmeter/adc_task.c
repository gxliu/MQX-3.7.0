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
* $FileName: adc_task.c$
*
* Comments:
*
*   This file contains the source for the ADC example program.
*   Two channels are running, one is running in loop, the second one
*   only once.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <string.h>
#include "meter_config.h"
#include "task_template_list.h"


#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif



/* Function prototypes */
extern void process_calculation(void);

static void adc_init(void);
static _mqx_int adc_calibrate(void);
static _mqx_int adc_save_calibration_data(void);
static _mqx_int adc_restore_calibration_data(void);

static void adc_channel_init(void);
static void adc_start_measuring(void);
static void adc_idelay_callback(void);
static void adc_error_callback(void);


/* ADC device init struct string definitions */

const ADC_INIT_STRUCT adc_init_param = {
    ADC_RESOLUTION_16BIT,     /* resolution */
};

/* 
** L1 voltage and current - logical channel init structures 
*/
#define ADC_L1_STR      "adc3:"
#define ADC_vL1_STR     "adc3:vL1"
#define ADC_iL1_STR     "adc3:iL1"

const ADC_INIT_CHANNEL_STRUCT vL1_channel_param = 
{
/* physical ADC channel                  */ ADC_SOURCE_ADC3_AD4,     
/* runs continuously after PDB trigger   */ (ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_TRIGGERED), 
/* number of samples in one run sequence */ SAMPLES_PER_PERIOD,             
/* time offset from trigger point in us  */ ADC_VOLTAGE_DELAY,              
/* period in us                          */ ADC_SAMPLING_PERIOD,            
/* scale range of result (not used now)  */ ADC_RESULT_RANGE_SCALE,         
/* circular buffer size (sample count)   */ SAMPLE_BUFFER,             
/* adc trigger                           */ ADC_PDB_TRIGGER,
/* lwevent object                        */ NULL,
/* lwevent mask                          */ 0
};


const ADC_INIT_CHANNEL_STRUCT iL1_channel_param = 
{
/* physical ADC channel                  */ ADC_SOURCE_ADC3_AD0,     
/* runs continuously after PDB trigger   */ (ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_TRIGGERED), 
/* number of samples in one run sequence */ SAMPLES_PER_PERIOD,             
/* time offset from trigger point in us  */ ADC_CURRENT_DELAY,              
/* period in us                          */ ADC_SAMPLING_PERIOD,            
/* scale range of result (not used now)  */ ADC_RESULT_RANGE_SCALE,         
/* circular buffer size (sample count)   */ SAMPLE_BUFFER,             
/* adc trigger                           */ ADC_PDB_TRIGGER,
/* lwevent object                        */ &meter_shared_event,
/* lwevent mask                          */ ADC_DATA_READY_MASK,
};

/* 
** L2 voltage and current - logical channel init structures 
*/

#define ADC_L2_STR      "adc1:"
#define ADC_iL2_STR     "adc1:iL2"
#define ADC_vL2_STR     "adc1:vL2"

const ADC_INIT_CHANNEL_STRUCT vL2_channel_param = 
{
/* physical ADC channel                  */ ADC_SOURCE_ADC1_AD5,     
/* runs continuously after PDB trigger   */ (ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_TRIGGERED), 
/* number of samples in one run sequence */ SAMPLES_PER_PERIOD,             
/* time offset from trigger point in us  */ ADC_VOLTAGE_DELAY,              
/* period in us                          */ ADC_SAMPLING_PERIOD,            
/* scale range of result (not used now)  */ ADC_RESULT_RANGE_SCALE,         
/* circular buffer size (sample count)   */ SAMPLE_BUFFER,             
/* adc trigger                           */ ADC_PDB_TRIGGER,
/* lw event callback                     */ NULL
};



const ADC_INIT_CHANNEL_STRUCT iL2_channel_param = 
{
/* physical ADC channel                  */ ADC_SOURCE_ADC1_AD1,     
/* runs continuously after PDB trigger   */ (ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_TRIGGERED), 
/* number of samples in one run sequence */ SAMPLES_PER_PERIOD,             
/* time offset from trigger point in us  */ ADC_CURRENT_DELAY,              
/* period in us                          */ ADC_SAMPLING_PERIOD,            
/* scale range of result (not used now)  */ ADC_RESULT_RANGE_SCALE,         
/* circular buffer size (sample count)   */ SAMPLE_BUFFER,             
/* adc trigger                           */ ADC_PDB_TRIGGER,
/* lwevent object                        */ NULL,
/* lwevent mask                          */ 0
};

/* 
** L3 voltage and current - logical channel init structures 
*/
#define ADC_L3_STR      "adc2:"
#define ADC_vL3_STR     "adc2:vL3"
#define ADC_iL3_STR     "adc2:iL3"

const ADC_INIT_CHANNEL_STRUCT vL3_channel_param = 
{
/* physical ADC channel                  */ ADC_SOURCE_ADC2_AD6,     
/* runs continuously after PDB trigger   */ (ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_TRIGGERED), 
/* number of samples in one run sequence */ SAMPLES_PER_PERIOD,             
/* time offset from trigger point in us  */ ADC_VOLTAGE_DELAY,              
/* period in us                          */ ADC_SAMPLING_PERIOD,            
/* scale range of result (not used now)  */ ADC_RESULT_RANGE_SCALE,         
/* circular buffer size (sample count)   */ SAMPLE_BUFFER,             
/* adc trigger                           */ ADC_PDB_TRIGGER,
/* lwevent object                        */ NULL,
/* lwevent mask                          */ 0
};

const ADC_INIT_CHANNEL_STRUCT iL3_channel_param = 
{
/* physical ADC channel                  */ ADC_SOURCE_ADC2_AD2,     
/* runs continuously after PDB trigger   */ (ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_TRIGGERED), 
/* number of samples in one run sequence */ SAMPLES_PER_PERIOD,             
/* time offset from trigger point in us  */ ADC_CURRENT_DELAY,              
/* period in us (64 samples per period)  */ ADC_SAMPLING_PERIOD,            
/* scale range of result (not used now)  */ ADC_RESULT_RANGE_SCALE,         
/* circular buffer size (sample count)   */ SAMPLE_BUFFER,             
/* adc trigger                           */ ADC_PDB_TRIGGER,
/* lwevent object                        */ NULL,
/* lwevent mask                          */ 0
};


/* ADC file pointers */
MQX_FILE_PTR file_L1, file_vL1, file_iL1;  /* Line 1 file pointers */
MQX_FILE_PTR file_L2, file_vL2, file_iL2;  /* Line 2 file pointers */
MQX_FILE_PTR file_L3, file_vL3, file_iL3;  /* Line 3 file pointers */

/* EEPROM file pointers */
MQX_FILE_PTR file_eeprom;

/* Calculation buffers */
int_16 iL1_buff[SAMPLES_PER_PERIOD];
int_16 vL1_buff[SAMPLES_PER_PERIOD];
int_16 iL2_buff[SAMPLES_PER_PERIOD];
int_16 vL2_buff[SAMPLES_PER_PERIOD];
int_16 iL3_buff[SAMPLES_PER_PERIOD];
int_16 vL3_buff[SAMPLES_PER_PERIOD];

uint_32 num_read_vL1, num_read_vL2, num_read_vL3;
uint_32 num_read_iL1, num_read_iL2, num_read_iL3;

LWEVENT_STRUCT  meter_shared_event;

extern uint_16  Energy[3];            
extern int_16 clear_offset(int_16 *I, uint_16 nsamples);

/*TASK******************************************************
** 
** Task Name    : adc_task
** Comments     :
**
*END*******************************************************/


void adc_task
   (
      uint_32 initial_data
   )
{
    static vuint_32 timeout = 0;
    static vuint_8  swap = 0;
       
    puts("\n\n*****************************\n");
    puts("ADC task is running\n");



    /* Initialize energy counters from standby RAM */
    if (MQX_OK != _rtc_read_from_standby_ram(0, (uint_8_ptr)&Energy, sizeof(Energy)))
    {
        _task_block();
    }


    adc_init();
    
    /* Calibrate ADC devices used in 3-phase meter */
    puts("Calibrating ADC devices... ");    

    if (MQX_OK == adc_calibrate())  {
        puts("done\n");
    }
    else {
        puts("failed\n");
    }
    
    
    /* 
    ** Prepare ADC for measuring signals of 3 curents (DAD1-DAD3)
    ** and 3 voltage (AD4-AD7) into buffers. 
    */
    if (_lwevent_create(&meter_shared_event, 0) != MQX_OK) {
        puts("\nMake event failed!\n");
        _task_block();
    }
    
    _lwevent_set_auto_clear( &meter_shared_event, ADC_DATA_READY_MASK);
 
    /* Initialize ADC channels */
    adc_channel_init();
 
    /* Trigger ADC measurements */
    adc_start_measuring();
    
    
    while(1)
    {
        /* Wait for adc data ready event */
        if (_lwevent_wait_ticks (&meter_shared_event, ADC_DATA_READY_MASK, TRUE, 0) == MQX_OK) 
        {

            /* Read data from ADC driver internal buffers */
            num_read_vL1 = read(file_vL1, vL1_buff, SAMPLES_PER_PERIOD * sizeof(vL1_buff[0]));
            num_read_iL1 = read(file_iL1, iL1_buff, SAMPLES_PER_PERIOD * sizeof(iL1_buff[0]));
            num_read_vL2 = read(file_vL2, vL2_buff, SAMPLES_PER_PERIOD * sizeof(vL2_buff[0]));
            num_read_iL2 = read(file_iL2, iL2_buff, SAMPLES_PER_PERIOD * sizeof(iL2_buff[0]));
            num_read_vL3 = read(file_vL3, vL3_buff, SAMPLES_PER_PERIOD * sizeof(vL3_buff[0]));
            num_read_iL3 = read(file_iL3, iL3_buff, SAMPLES_PER_PERIOD * sizeof(iL3_buff[0]));
            
            /* Process metering algorithms */
            process_calculation();    

            /* Blink on fire symbol on LCD to show that adc_task is running */
            if (++timeout > (LINE_FREQUENCY / 4))
            {
                
                timeout = 0;
                if(swap == 0) {
                    swap = 1;
                    _lcd_symbol(LCD_FIRE, TRUE);
                }
                else {
                    swap = 0;
                    _lcd_symbol(LCD_FIRE, FALSE);
                }
            }
        }
    }
}  

/*FUNCTION****************************************************************
* 
* Function Name    : adc_init
* Returned Value   : void
* Comments         :
*
*END*********************************************************************/

static void adc_init(void)
{
    _mqx_uint      error_code = 0;

    /* Opening ADC devices */
    puts("Opening ADC devices for measurement\n");

    /* Opening ADC3 device for L1 phase */    
    puts("L1 phase voltage and current -> ADC3\n");
    file_L1   = fopen(ADC_L1_STR, (const char*)&adc_init_param);
    if(file_L1  != NULL)    
    {    
        /* Set long sample time */
        error_code += ioctl(file_L1, ADC_IOCTL_SET_LONG_SAMPLE, (pointer)ADC_LONG_SAMPLE);    

        /* Set hardware averaging to be taken from 16 samples */
        error_code += ioctl(file_L1, ADC_IOCTL_SET_HW_AVERAGING,(pointer)ADC_HARDWARE_AVERAGING);    

        /* Set low conversion speed */
        error_code += ioctl(file_L1, ADC_IOCTL_SET_LOW_SPEED,   NULL);    

        /* Set common sampling period for all ADC channels */
        error_code += ioctl(file_L1, ADC_IOCTL_SET_BASE_PERIOD, (pointer)ADC_SAMPLING_PERIOD);    

        /* Set idelay function callback */
        error_code += ioctl(file_L1, ADC_IOCTL_SET_IDELAY_FCN, &adc_idelay_callback);    
        
        
        error_code += ioctl(file_L1, ADC_IOCTL_SET_IDELAY, (pointer)(ADC_IDELAY));    

        /* Set ADC error callback function for capturing triggering errors */
        error_code += ioctl(file_L1, ADC_IOCTL_SET_ERROR_FCN, &adc_error_callback);
    }
    else  {    
        error_code++;
    }

    /* Opening ADC1 device for L2 phase 
    ** Timing is set from ADC3 initialization already
    */

    puts("L2 phase voltage and current -> ADC1\n");
    file_L2   = fopen(ADC_L2_STR, (const char*)&adc_init_param);
    if(file_L2  != NULL)    
    {    
        /* Set long sample time */
        error_code += ioctl(file_L2, ADC_IOCTL_SET_LONG_SAMPLE, (pointer)ADC_LONG_SAMPLE);    
        /* Set hardware averaging to be taken from 16 samples */
        error_code += ioctl(file_L2, ADC_IOCTL_SET_HW_AVERAGING,(pointer)ADC_HARDWARE_AVERAGING);    
        /* Set low conversion speed */
        error_code += ioctl(file_L2, ADC_IOCTL_SET_LOW_SPEED,   NULL);    
    }
    else  {    
        error_code++;
    }


    /* Opening ADC2 device for L3 phase */
    puts("L3 phase voltage and current -> ADC2\n");
    file_L3   = fopen(ADC_L3_STR, (const char*)&adc_init_param);
    // file_ADC2 = fopen("adc2:", (const char*)&adc_init_param);
    if(file_L3  != NULL)    
    {    
        /* Set long sample time */
        error_code += ioctl(file_L3, ADC_IOCTL_SET_LONG_SAMPLE, (pointer)ADC_LONG_SAMPLE);    
        /* Set hardware averaging to be taken from 16 samples */
        error_code += ioctl(file_L3, ADC_IOCTL_SET_HW_AVERAGING,(pointer)ADC_HARDWARE_AVERAGING);    
        /* Set low conversion speed */
        error_code += ioctl(file_L3, ADC_IOCTL_SET_LOW_SPEED,   NULL);    
    }
    else  {    
        error_code++;
    }

    printf("ADC_SAMPLING_PERIOD = %dus\n",ADC_SAMPLING_PERIOD);
    printf("SAMPLES_PER_PERIOD  = %d\n",  SAMPLES_PER_PERIOD);
    
    puts("ADC device initalization...");            
    if (error_code == 0)
    {
        puts("succeed\n");            
    }
    else 
    {
        puts("failed\n");
        _task_block();
    }
}

/*FUNCTION****************************************************************
* 
* Function Name    : adc_channel_init
* Returned Value   : void
* Comments         :
*
*END*********************************************************************/

static void adc_channel_init(void)
{

    _mqx_uint      error_code = 0;

    puts("Opening ADC channels for L1,L2,L3 measurement\n");

    /* Opening ADC channels for L1 voltage and current measurements */
    puts("L1 voltage channel...");
    file_vL1 = fopen(ADC_vL1_STR, (const char*)&vL1_channel_param);
    if(file_vL1 != NULL)
    {    
        /* Force L1 voltage channel data to be processed in PDB interrupt */
        error_code += ioctl(file_vL1, ADC_IOCTL_SET_IDELAY_PROCESS, NULL);    
        puts("opened\n");
    }
    else
    {    
        puts("failed\n");
        _task_block();
    }

    

    puts("L1 current channel...");
    file_iL1 = fopen(ADC_iL1_STR, (const char*)&iL1_channel_param);
    
    if(file_iL1 != NULL)
    {    
        /* Force L1 current channel data to be processed in PDB interrupt */
        error_code += ioctl(file_iL1, ADC_IOCTL_SET_IDELAY_PROCESS, NULL);    
        puts("opened\n");
    }
    else
    {    
        puts("failed\n");
        _task_block();
    }
 
 
    /* Opening ADC channels for L2 voltage and current measurements */
    puts("L2 voltage channel...");
    file_vL2 = fopen(ADC_vL2_STR, (const char*)&vL2_channel_param);
    
    if(file_vL2 != NULL)
    {    
        /* Force L2 voltage channel data to be processed in PDB interrupt */
        error_code += ioctl(file_vL2, ADC_IOCTL_SET_IDELAY_PROCESS, NULL);    
        puts("opened\n");
    }
    else
    {    
        puts("failed\n");
        _task_block();
    }

    puts("L2 current channel...");
    file_iL2 = fopen(ADC_iL2_STR, (const char*)&iL2_channel_param);
    
    if(file_iL2 != NULL)
    {    
        /* Force L2 current channel data to be processed in PDB interrupt */
        error_code += ioctl(file_iL2, ADC_IOCTL_SET_IDELAY_PROCESS, NULL);    
        puts("opened\n");
    }
    else
    {    
        puts("failed\n");
        _task_block();
    }
  
    /* Opening ADC channels for L3 voltage and current measurements */
    puts("L3 voltage channel...");
    file_vL3 = fopen(ADC_vL3_STR, (const char*)&vL3_channel_param);
    
    if(file_vL3 != NULL)
    {    
        /* Force L3 voltage channel data to be processed in PDB interrupt */
        error_code += ioctl(file_vL3, ADC_IOCTL_SET_IDELAY_PROCESS, NULL);    
        puts("opened\n");
    }
    else
    {    
        puts("failed\n");
        _task_block();
    }
    
    puts("L3 current channel...");
    file_iL3 = fopen(ADC_iL3_STR, (const char*)&iL3_channel_param);
    
    if(file_iL3 != NULL)
    {    
        /* Force L3 current channel data to be processed in PDB interrupt */
        error_code += ioctl(file_iL3, ADC_IOCTL_SET_IDELAY_PROCESS, NULL);    
        puts("opened\n");
    }
    else
    {    
        puts("failed\n");
        _task_block();
    }

    puts("\n All channels are waiting for trigger\n");
}

/*FUNCTION****************************************************************
* 
* Function Name    : adc_calibrate
* Returned Value   : _mqx_int
* Comments         :
*
*END*********************************************************************/

static _mqx_int adc_calibrate(void)
{
    _mqx_int   error_code = MQX_OK;

    /* ADC1 calibration */    
    error_code = ioctl(file_L1, ADC_IOCTL_CALIBRATE, NULL);
    
    if (error_code != MQX_OK)    {
        return error_code;
    }

    /* ADC2 calibration */    
    error_code = ioctl(file_L2, ADC_IOCTL_CALIBRATE, NULL);

    if (error_code != MQX_OK)    {
        return error_code;
    }
    
    /* ADC3 calibration */    
    error_code = ioctl(file_L3, ADC_IOCTL_CALIBRATE, NULL);

    return  error_code;   
}


/*FUNCTION****************************************************************
* 
* Function Name    : adc_save_calibration_data
* Returned Value   : _mqx_int
* Comments         :
*
*END*********************************************************************/

static _mqx_int adc_save_calibration_data(void)
{
    MCF51EM_ADC16_CALIB_STRUCT_PTR  calib_data_ptr;
    _mqx_int                        io_result = MQX_OK;
    _mqx_int                        i         = 0;
    
    /* Open file for calibration data */
    file_eeprom = fopen("flashx1:", NULL);
    
    if (file_eeprom == NULL)    {
        /* ADC calibration data file opening failed */
        puts("File with ADC calibration data opening failed");
        _task_block();
    }
   
   /* Allocate memory for calibration data */
    calib_data_ptr = _mem_alloc(3 * sizeof(MCF51EM_ADC16_CALIB_STRUCT));

    if (calib_data_ptr == NULL)  {
        /* Return error message */
        return MQX_OUT_OF_MEMORY;
    }
    else
    {

        io_result = ioctl(file_L1, ADC_IOCTL_GET_CALIBRATION, &calib_data_ptr[0]);
        if (io_result != MQX_OK)    {
            /* Return ioctl error message */
            return  io_result;
        }


        io_result = ioctl(file_L2, ADC_IOCTL_GET_CALIBRATION, &calib_data_ptr[1]);
        if (io_result != MQX_OK)    {
            /* Return ioctl error message */
            return  io_result;
        }

        io_result = ioctl(file_L3, ADC_IOCTL_GET_CALIBRATION, &calib_data_ptr[2]);
        if (io_result != MQX_OK)    {
            /* Return ioctl error message */
            return  io_result;
        }

        
        /* Seek calibration file begin */
        fseek(file_eeprom, 0, IO_SEEK_SET);
        
        /* Write calibration data into flash */
        i = write(file_eeprom, 0, (3 * sizeof(MCF51EM_ADC16_CALIB_STRUCT)));
        
        _mem_free(calib_data_ptr);
        
        printf("%i bytes of calibration data saved to flash\n", i);
        
        return MQX_OK;
    }

}

/*FUNCTION****************************************************************
* 
* Function Name    : adc_save_calibration_data
* Returned Value   : _mqx_int
* Comments         :
*
*END*********************************************************************/

static _mqx_int  adc_restore_calibration_data(void)
{
    MCF51EM_ADC16_CALIB_STRUCT_PTR  calib_data_ptr;
    _mqx_int                        io_result = MQX_OK;
    _mqx_int                        i         = 0;


   /* Allocate memory for calibration data */    
    calib_data_ptr = _mem_alloc(3 * sizeof(MCF51EM_ADC16_CALIB_STRUCT));

    if (calib_data_ptr == NULL)  {
        /* Return error message */
        return MQX_OUT_OF_MEMORY;
    }
    else    {
        printf("%i bytes of calibration data read from flash\n", i);

        /* Seek calibration file begin */
        fseek(file_eeprom, 0, IO_SEEK_SET);

        i = read(file_eeprom, calib_data_ptr, (3 * sizeof(MCF51EM_ADC16_CALIB_STRUCT)));


        io_result = ioctl(file_L1, ADC_IOCTL_SET_CALIBRATION, &calib_data_ptr[1]);
        if (io_result != MQX_OK)    {
            /* Return ioctl error message */
            return  io_result;
        }


        io_result = ioctl(file_L2, ADC_IOCTL_SET_CALIBRATION, &calib_data_ptr[1]);
        if (io_result != MQX_OK)    {
            /* Return ioctl error message */
            return  io_result;
        }

        io_result = ioctl(file_L3, ADC_IOCTL_SET_CALIBRATION, &calib_data_ptr[2]);
        if (io_result != MQX_OK)    {
            /* Return ioctl error message */
            return  io_result;
        }

        
        /* Seek calibration file begin */
        fseek(file_eeprom, 0, IO_SEEK_SET);
        
        /* Write calibration data into flash */
        i = write(file_eeprom, 0, (3 * sizeof(MCF51EM_ADC16_CALIB_STRUCT)));
        
        _mem_free(calib_data_ptr);
        
        return MQX_OK;
    }
}

/*FUNCTION****************************************************************
* 
* Function Name    : adc_start_measuring
* Returned Value   : void
* Comments         :
*
*END*********************************************************************/

static void adc_start_measuring(void)
{
    /* Triggering */
    puts("Starting measurement...\n");
    ioctl(file_L1, ADC_IOCTL_FIRE_TRIGGER, (pointer) ADC_PDB_TRIGGER);
    ioctl(file_L2, ADC_IOCTL_FIRE_TRIGGER, (pointer) ADC_PDB_TRIGGER);
    ioctl(file_L3, ADC_IOCTL_FIRE_TRIGGER, (pointer) ADC_PDB_TRIGGER);
}


/*FUNCTION****************************************************************
* 
* Function Name    : adc_idelay_callback
* Returned Value   : void
* Comments         :
*
*END*********************************************************************/

volatile uint_32 adc_idelay_count = 0;

static void adc_idelay_callback(void)
{
    adc_idelay_count++;
}



/*FUNCTION****************************************************************
* 
* Function Name    : adc_error_callback
* Returned Value   : void
* Comments         :
*
*END*********************************************************************/

volatile uint_32 adc_error_count = 0;

static void adc_error_callback(void)
{
    adc_error_count++;
}

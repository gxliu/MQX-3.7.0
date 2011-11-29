/**HEADER********************************************************************
* 
* Copyright (c) 2011 Freescale Semiconductor;
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
* $FileName: tchres.c$
* $Version : 3.7.3.1$
* $Date    : Apr-6-2011$
*
* Comments:
*
*   This file contains the source for the hello example program.
*
*END************************************************************************/
#include "mqx.h"
#include "bsp.h"
#include "tchres_prv.h"

#if !MQX_USE_LWEVENTS
#error use MQX_USE_LWEVENTS
#endif

#if 0
const ADC_INIT_STRUCT adc_init = {
    ADC_RESOLUTION_DEFAULT,     /* resolution */
};
#endif
/* static function protoypes */
static _mqx_int _tchres_uninstall( IO_DEVICE_STRUCT_PTR );
static _mqx_int _tchres_open( MQX_FILE_PTR, char_ptr, char_ptr );
static _mqx_int _tchres_close( MQX_FILE_PTR );
static _mqx_int _tchres_ioctl( MQX_FILE_PTR, _mqx_uint, pointer );
static uint_16 _tchres_read_touch_axis( TCHRES_PIN_SELECT_ENUM, TCHRES_DEVICE_STRUCT_PTR );
static int_16 _tchres_get_raw_limits( TCHRES_LIMITS_ENUM, TCHRES_DEVICE_STRUCT_PTR );
static uchar _tchres_get_filtered_axis(TCHRES_DEVICE_STRUCT_PTR, TCHRES_PIN_SELECT_ENUM, uint_16 *);
static void _tchres_set_pins_to_default( TCHRES_DEVICE_STRUCT_PTR );

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_tchres_install
* Returned Value   : none
* Comments         :
*    Return filtered value from adc 
*
*END*----------------------------------------------------------------------*/
_mqx_uint _io_tchres_install
(
   /* [IN] A string that identifies the device for fopen */
   char_ptr             identifier,
  
   /* [IN] The I/O init data pointer */
   TCHRES_INIT_STRUCT_PTR  init_ptr,
   
   /* [IN] adc device handle */
   MQX_FILE_PTR   adc_device
)
{
   TCHRES_DEVICE_STRUCT_PTR    dev_ptr;
   ADC_INIT_CHANNEL_STRUCT_PTR adc_x_ptr, adc_y_ptr;
   _mqx_int                    result = MQX_OK; 
   
   if( adc_device == NULL )
   {
      result = MQX_INVALID_IO_CHANNEL;
      goto tchres_alloc_err;
   }   
   
   /* allocate memory */
   dev_ptr = _mem_alloc_system_zero((_mem_size)sizeof( TCHRES_DEVICE_STRUCT ));
   #if MQX_CHECK_MEMORY_ALLOCATION_ERRORS
   if (dev_ptr == NULL) 
   {
      result = MQX_OUT_OF_MEMORY;
      goto tchres_alloc_err;
   } /* Endif */
   #endif
   
   adc_x_ptr = _mem_alloc_system_zero((_mem_size)sizeof( ADC_INIT_CHANNEL_STRUCT ));
   #if MQX_CHECK_MEMORY_ALLOCATION_ERRORS
   if (adc_x_ptr == NULL) 
   {
      result = MQX_OUT_OF_MEMORY;
      goto adcx_alloc_err;
   } /* Endif */
   #endif
   
   adc_y_ptr = _mem_alloc_system_zero((_mem_size)sizeof( ADC_INIT_CHANNEL_STRUCT ));
   #if MQX_CHECK_MEMORY_ALLOCATION_ERRORS
   if (adc_y_ptr == NULL) 
   {
      result = MQX_OUT_OF_MEMORY;
      goto adcy_alloc_err;
   } /* Endif */
   #endif
   
   _mem_set_type( dev_ptr, MEM_TYPE_IO_TCHRES_STRUCT );
   _mem_set_type( adc_x_ptr, MEM_TYPE_IO_TCHRES_STRUCT );
   _mem_set_type( adc_y_ptr, MEM_TYPE_IO_TCHRES_STRUCT );
 
   if (_lwevent_create(&dev_ptr->TCH_EVENT, LWEVENT_AUTO_CLEAR) != MQX_OK) 
   {
      result = MQX_IO_OPERATION_NOT_AVAILABLE;
      goto event_err;
   }
   
   /* Channel X adc settings */
   adc_x_ptr->source = init_ptr->ADC_CHANNEL_X_SOURCE;
   adc_x_ptr->flags = TCHRES_ADC_FLAGS;            
   adc_x_ptr->number_samples = TCHRES_ADC_NUM_SAMPLES;   
   adc_x_ptr->time_offset = TCHRES_ADC_TIME_OFFSET;      
   adc_x_ptr->time_period = TCHRES_ADC_TIME_PERIOD;     
   adc_x_ptr->range = TCHRES_ADC_RANGE;                     
   adc_x_ptr->buffer_size = TCHRES_ADC_BUFFER_SIZE;    
   adc_x_ptr->trigger = init_ptr->ADC_CHANNEL_X_TRIGGER;   
   adc_x_ptr->complete_event = &dev_ptr->TCH_EVENT;
   adc_x_ptr->event_mask = TCH_ADC_X_COMPLETE;      
   
   /* Channel Y adc settings */
   adc_y_ptr->source = init_ptr->ADC_CHANNEL_Y_SOURCE;
   adc_y_ptr->flags = TCHRES_ADC_FLAGS;            
   adc_y_ptr->number_samples = TCHRES_ADC_NUM_SAMPLES;   
   adc_y_ptr->time_offset = TCHRES_ADC_TIME_OFFSET;      
   adc_y_ptr->time_period = TCHRES_ADC_TIME_PERIOD;     
   adc_y_ptr->range = TCHRES_ADC_RANGE;                     
   adc_y_ptr->buffer_size = TCHRES_ADC_BUFFER_SIZE;    
   adc_y_ptr->trigger = init_ptr->ADC_CHANNEL_Y_TRIGGER;   
   adc_y_ptr->complete_event = &dev_ptr->TCH_EVENT;
   adc_y_ptr->event_mask = TCH_ADC_Y_COMPLETE; 
   
   /* copy the adc channel information */
   dev_ptr->ADC_LIMITS = init_ptr->ADC_LIMITS;
   dev_ptr->ADC_CHANNEL_X_STRUCT = adc_x_ptr;
   dev_ptr->ADC_CHANNEL_Y_STRUCT = adc_y_ptr;
   dev_ptr->ADC_DEVICE = adc_device;
   
   /* initialize lwgpio */
   if (!lwgpio_init(&dev_ptr->X_PLUS_PIN, init_ptr->PIN_CONFIG.X_PLUS, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE))
   {
      result = MQX_IO_OPERATION_NOT_AVAILABLE;
      goto lw_err;
   }
   if (!lwgpio_init(&dev_ptr->Y_PLUS_PIN, init_ptr->PIN_CONFIG.Y_PLUS, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE))
   {
      result = MQX_IO_OPERATION_NOT_AVAILABLE;
      goto lw_err;
   }
   if (!lwgpio_init(&dev_ptr->X_MINUS_PIN, init_ptr->PIN_CONFIG.X_MINUS, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE))
   {
      result = MQX_IO_OPERATION_NOT_AVAILABLE;
      goto lw_err;
   }
   if (!lwgpio_init(&dev_ptr->Y_MINUS_PIN, init_ptr->PIN_CONFIG.Y_MINUS, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE))
   {
      result = MQX_IO_OPERATION_NOT_AVAILABLE;
      goto lw_err;
   }   
 
   /* set adc and gpio functianily mux indexes */
   dev_ptr->PIN_FUNCT = init_ptr->PIN_CONFIG.PIN_FUNCT; 
   
   /* install device */
   return ( _io_dev_install_ext ( identifier,
      _tchres_open,
      _tchres_close,
      NULL, 
      NULL,
      _tchres_ioctl,
      _tchres_uninstall, 
      (pointer)dev_ptr) );
    
    /* exceptions, clear memory */  
lw_err:
    _lwevent_destroy(&dev_ptr->TCH_EVENT);  
event_err:
   _mem_free(adc_y_ptr);      
adcy_alloc_err:
   _mem_free(adc_x_ptr);
adcx_alloc_err:
   _mem_free(dev_ptr);
tchres_alloc_err:
   return result;
      
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _tchres_uninstall
* Returned Value   : _mqx_uint a task error code or MQX_OK
* Comments         :
*    Uninstall the touch screen driver .
*
*END*----------------------------------------------------------------------*/
static _mqx_int _tchres_uninstall
(
    IO_DEVICE_STRUCT_PTR    io_dev_ptr  
)
{
   TCHRES_DEVICE_STRUCT_PTR tchscr_dev_ptr = io_dev_ptr->DRIVER_INIT_PTR;
   
   /* free adc channel infos */
   if( tchscr_dev_ptr->ADC_CHANNEL_X_STRUCT )
   {      
      _mem_free(tchscr_dev_ptr->ADC_CHANNEL_X_STRUCT);
   }
   if( tchscr_dev_ptr->ADC_CHANNEL_Y_STRUCT )
   {      
      _mem_free(tchscr_dev_ptr->ADC_CHANNEL_Y_STRUCT);
   }
   if( &tchscr_dev_ptr->TCH_EVENT )
   {      
      _lwevent_destroy( &tchscr_dev_ptr->TCH_EVENT );
   }
   if( tchscr_dev_ptr )
   {      
      _mem_free (tchscr_dev_ptr);
   }
   io_dev_ptr->DRIVER_INIT_PTR = NULL;
   return IO_OK;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _tchres_open
* Returned Value   : _mqx_uint a task error code or MQX_OK
* Comments         :
*    Open the touch screen driver and initialize the gpio pins to default 
*    states. Register  used pins in gpio driver as used. .
*
*END*----------------------------------------------------------------------*/
static _mqx_int _tchres_open
(
   /* [IN] The address of the device specific information */
   MQX_FILE_PTR     fd_ptr,

   /* [IN] The rest of the name of the device opened */
   char_ptr open_name_ptr,
   
   /* [IN] the flags to be used during operation: */
   char_ptr   flags
)
{
   IO_DEVICE_STRUCT_PTR       io_dev_ptr;
   TCHRES_DEVICE_STRUCT_PTR   tchscr_dev_ptr;
   _mqx_int                   result = MQX_OK; 
   
   io_dev_ptr     = (IO_DEVICE_STRUCT_PTR)fd_ptr->DEV_PTR;
   tchscr_dev_ptr = (TCHRES_DEVICE_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
   
   /* open this driver only once */
   if( tchscr_dev_ptr->COUNT == 0 )
   {      
      tchscr_dev_ptr->COUNT = 1;

      /* open X adc channel */
      tchscr_dev_ptr->ADC_CHANNEL_X = fopen(BSP_TCHRES_ADC_DEVICE "adc_X", (const char*)tchscr_dev_ptr->ADC_CHANNEL_X_STRUCT);
      if( tchscr_dev_ptr->ADC_CHANNEL_X == NULL )
      {
         result = MQX_IO_OPERATION_NOT_AVAILABLE;
      }
      /* opne Y adc channel */
      tchscr_dev_ptr->ADC_CHANNEL_Y = fopen(BSP_TCHRES_ADC_DEVICE "adc_Y", (const char*)tchscr_dev_ptr->ADC_CHANNEL_Y_STRUCT);
      if( tchscr_dev_ptr->ADC_CHANNEL_Y == NULL )
      {
         result = MQX_IO_OPERATION_NOT_AVAILABLE;
      }      
      
      /* set pisns to default state */
      lwgpio_set_direction( &tchscr_dev_ptr->X_PLUS_PIN, LWGPIO_DIR_OUTPUT );
      lwgpio_set_direction( &tchscr_dev_ptr->Y_PLUS_PIN, LWGPIO_DIR_OUTPUT );
      lwgpio_set_direction( &tchscr_dev_ptr->X_MINUS_PIN, LWGPIO_DIR_OUTPUT );
      lwgpio_set_direction( &tchscr_dev_ptr->Y_MINUS_PIN, LWGPIO_DIR_OUTPUT );
      
      lwgpio_set_value( &tchscr_dev_ptr->X_PLUS_PIN, LWGPIO_VALUE_LOW ); 
      lwgpio_set_value( &tchscr_dev_ptr->X_MINUS_PIN, LWGPIO_VALUE_LOW ); 
      lwgpio_set_value( &tchscr_dev_ptr->Y_PLUS_PIN, LWGPIO_VALUE_LOW ); 
      lwgpio_set_value( &tchscr_dev_ptr->Y_MINUS_PIN, LWGPIO_VALUE_LOW );
      
      lwgpio_set_functionality( &tchscr_dev_ptr->X_PLUS_PIN, tchscr_dev_ptr->PIN_FUNCT.X_PLUS_GPIO_FUNCTION );
      lwgpio_set_functionality( &tchscr_dev_ptr->X_MINUS_PIN, tchscr_dev_ptr->PIN_FUNCT.X_MINUS_GPIO_FUNCTION );
      lwgpio_set_functionality( &tchscr_dev_ptr->Y_PLUS_PIN, tchscr_dev_ptr->PIN_FUNCT.Y_PLUS_GPIO_FUNCTION );
      lwgpio_set_functionality( &tchscr_dev_ptr->Y_MINUS_PIN, tchscr_dev_ptr->PIN_FUNCT.Y_MINUS_GPIO_FUNCTION );
         
   }
   else
   {
      result = MQX_IO_OPERATION_NOT_AVAILABLE;
   }

   return( result );
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _tchres_close
* Returned Value   : _mqx_uint a task error code or MQX_OK
* Comments         :
*    Close the touch screen driver.
*
*END*----------------------------------------------------------------------*/
static _mqx_int _tchres_close
(
   /* [IN] The address of the device specific information */
   MQX_FILE_PTR     fd_ptr
)
{ 
   IO_DEVICE_STRUCT_PTR       io_dev_ptr;
   TCHRES_DEVICE_STRUCT_PTR   tchscr_dev_ptr;
   
   io_dev_ptr     = (IO_DEVICE_STRUCT_PTR)fd_ptr->DEV_PTR;
   tchscr_dev_ptr = (TCHRES_DEVICE_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;

   if( tchscr_dev_ptr )
   {   
      fclose( tchscr_dev_ptr->ADC_CHANNEL_X );
      fclose( tchscr_dev_ptr->ADC_CHANNEL_Y );
      
      /* open this driver only once */
      tchscr_dev_ptr->COUNT = 0; 
   }    
      
   return( MQX_OK );
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _tchres_ioctl
* Returned Value   : _mqx_uint a task error code or MQX_OK
* Comments         :
*    This driver function performs various commands upon the opened TCHSCR 
*    device.
*
*END*----------------------------------------------------------------------*/
static _mqx_int _tchres_ioctl
(
   /* [IN] the handle returned from _fopen */
   MQX_FILE_PTR     handle_ptr,

   /* [IN] the ioctl command */
   _mqx_uint   cmd,

   /* [IN] the ioctl parameters */
   pointer     param_ptr
)
{
   IO_DEVICE_STRUCT_PTR       io_dev_ptr;
   TCHRES_DEVICE_STRUCT_PTR   tchscr_dev_ptr;
   _mqx_int                   result = MQX_OK;
   int                        x_pos, y_pos;
   TCHRES_POSITION_STRUCT_PTR position_ptr;
   
   io_dev_ptr     = (IO_DEVICE_STRUCT_PTR)handle_ptr->DEV_PTR;
   tchscr_dev_ptr = (TCHRES_DEVICE_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
     
   switch (cmd) {
      /* not supported yet  
        case IO_IOCTL_TCHSCR_GET_POSITION :
            break;               
      case IO_IOCTL_TCHSCR_SET_CALIBRATION :
         break;         
      case  IO_IOCTL_TCHSCR_GET_CALIBRATION :
         break;     
        */  
      case IO_IOCTL_TCHSCR_GET_POSITION_RAW :
         if( param_ptr == NULL )
         {
            result = TCHRES_ERROR_INVALID_PARAMETER;
            break;
         }
         /* Call the generic get_possition_raw function */
         result = _tchres_get_position_raw( &x_pos, &y_pos, tchscr_dev_ptr );
         if( result == TCHRES_OK )
         {
            position_ptr = (TCHRES_POSITION_STRUCT_PTR)param_ptr;
            position_ptr->X = x_pos;
            position_ptr->Y = y_pos;
         }
         
         break;                       
              
      case IO_IOCTL_TCHSCR_GET_RAW_LIMITS:
         if( param_ptr != NULL )
         {            
            *(TCHRES_ADC_LIMITS_STRUCT_PTR)param_ptr = tchscr_dev_ptr->ADC_LIMITS;
            result = MQX_OK;
         }
         else
         {
            result = TCHRES_ERROR_INVALID_PARAMETER;
         }
         break;
         
        default:
           /* return unsupported command */
           result = IO_ERROR_INVALID_IOCTL_CMD;
         break;

    } /* end switch */
   
   return( result );
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _tchres_read_touch_axis
* Returned Value   : adc value or 0
* Comments         :
*    Returns the value from ADC from selected channel
*
*END*----------------------------------------------------------------------*/
static uint_16 _tchres_read_touch_axis
(
   TCHRES_PIN_SELECT_ENUM pin_select,
   TCHRES_DEVICE_STRUCT_PTR tchscr_dev_ptr
)
{
   ADC_RESULT_STRUCT data;   
   
   switch( pin_select )
   {
      case X_PLUS:
         ioctl(tchscr_dev_ptr->ADC_CHANNEL_X, ADC_IOCTL_FIRE_TRIGGER, (pointer) tchscr_dev_ptr->ADC_CHANNEL_X_STRUCT->trigger);
         _lwevent_wait_ticks(&tchscr_dev_ptr->TCH_EVENT, tchscr_dev_ptr->ADC_CHANNEL_X_STRUCT->event_mask, TRUE, 0);
         read( tchscr_dev_ptr->ADC_CHANNEL_X, &data, sizeof(data) );
         break;
         
      case Y_PLUS:
         ioctl(tchscr_dev_ptr->ADC_CHANNEL_Y, ADC_IOCTL_FIRE_TRIGGER, (pointer) tchscr_dev_ptr->ADC_CHANNEL_Y_STRUCT->trigger);
         _lwevent_wait_ticks(&tchscr_dev_ptr->TCH_EVENT, tchscr_dev_ptr->ADC_CHANNEL_Y_STRUCT->event_mask, TRUE, 0);
         read( tchscr_dev_ptr->ADC_CHANNEL_Y, &data, sizeof(data) );
         break;
         
      default:
         return  0;   
   }   
   return( data.result ); 
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _tchres_get_filtered_axis
* Returned Value   : none
* Comments         :
*    Return filtered value from adc 
*
*END*----------------------------------------------------------------------*/  
static uchar _tchres_get_filtered_axis
( 
   TCHRES_DEVICE_STRUCT_PTR tchscr_dev_ptr,
   TCHRES_PIN_SELECT_ENUM pinId, 
   uint_16 *Res
)
{  
   #define COUNTER_LIMIT 0x50
   
   uint_16 wSample[AVERAGE_BUFF_LEN];
   uint_16 wRes, wSum;
   uint_16 wADCReading;
   uchar tmp, tmp_res;    
   int cnt;  
   uchar sample_margin;
   TCHRES_ADC_LIMITS_STRUCT_PTR p_limits = &tchscr_dev_ptr->ADC_LIMITS;


   sample_margin = (uchar)(p_limits->FULL_SCALE / 256);

   /* clear all local variables and buffer */
   for(tmp = 0; tmp < AVERAGE_BUFF_LEN; tmp++)
   {
      wSample[tmp] = 0;
   }
   wSum = 0;
   cnt = 0;
    
   while( cnt < COUNTER_LIMIT )
   {
      cnt++;
      /* Read ADC value */
      wADCReading = _tchres_read_touch_axis(pinId, tchscr_dev_ptr);

      /* check if input value is under minimal value */
      if((wADCReading < p_limits->X_TOUCH_MIN) || (wADCReading > (p_limits->FULL_SCALE - p_limits->FULL_SCALE / 16)))
      {         
         break;
      }

      /* Compute the current output value */
      wSum += wADCReading;
      wSum -= wSample[AVERAGE_BUFF_LEN - 1];

      /* shift all values in input buffer */
      for(tmp = (AVERAGE_BUFF_LEN - 1); tmp > 0 ;tmp--)
      {
         wSample[tmp] = wSample[tmp - 1]; 
      }

      /* put new value into buffer */
      wSample[0] = wADCReading;

      /* compute current result from all bufer values */
      wRes = (uint_16)(wSum / AVERAGE_BUFF_LEN);

      /* if buffer is full */
      if(cnt > AVERAGE_BUFF_LEN) 
      {
         /* Check all input samples if are in allowed range */
         tmp_res = 0;       
         for(tmp = 0; tmp < AVERAGE_BUFF_LEN ;tmp++)
         {
            if((wRes > (wSample[tmp] - sample_margin)) && 
               (wRes < (wSample[tmp] + sample_margin)))
            {
               tmp_res++;            
            }
         }
     
         /* If most of sample are in allowed range with output value, 
         ** assert this sample as result */
         if(tmp_res >= (AVERAGE_BUFF_LEN - 2)) 
         {            
            *Res = wRes;
            return 1;
         }
      }
   }
   
   return 0;  
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _tchres_set_pins_to_default
* Returned Value   : none
* Comments         : set X, Y pins to default state- ADC off, pins low
*    
*
*END*----------------------------------------------------------------------*/
static void _tchres_set_pins_to_default
( 
   TCHRES_DEVICE_STRUCT_PTR tchscr_dev_ptr 
)
{
   /* Disable ADC function on X+ and Y+ */
   lwgpio_set_functionality( &tchscr_dev_ptr->X_PLUS_PIN, tchscr_dev_ptr->PIN_FUNCT.X_PLUS_GPIO_FUNCTION );
   lwgpio_set_direction( &tchscr_dev_ptr->X_PLUS_PIN, LWGPIO_DIR_OUTPUT );
   lwgpio_set_direction( &tchscr_dev_ptr->X_MINUS_PIN, LWGPIO_DIR_OUTPUT );
   lwgpio_set_functionality( &tchscr_dev_ptr->Y_PLUS_PIN, tchscr_dev_ptr->PIN_FUNCT.Y_PLUS_GPIO_FUNCTION );
   lwgpio_set_direction( &tchscr_dev_ptr->Y_PLUS_PIN, LWGPIO_DIR_OUTPUT );
   lwgpio_set_direction( &tchscr_dev_ptr->Y_MINUS_PIN, LWGPIO_DIR_OUTPUT );

   /* Put on touch screen pins into default mode */   
   lwgpio_set_value( &tchscr_dev_ptr->X_PLUS_PIN, LWGPIO_VALUE_LOW ); 
   lwgpio_set_value( &tchscr_dev_ptr->X_MINUS_PIN, LWGPIO_VALUE_LOW ); 
   lwgpio_set_value( &tchscr_dev_ptr->Y_PLUS_PIN, LWGPIO_VALUE_LOW ); 
   lwgpio_set_value( &tchscr_dev_ptr->Y_MINUS_PIN, LWGPIO_VALUE_LOW );       
}
  
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _tchres_get_position_raw
* Returned Value   : unsigned int *TouchPositionX    Pointer to X coordinate
*                    unsigned int *TouchPositionY    Pointer to Y ccordinate
*                    0   no screen touch
*                    1   screen touch
                     2   internal timeout error
* Comments         : returns the filtered coordinate values from adc
*    
*
*END*----------------------------------------------------------------------*/  
_mqx_int _tchres_get_position_raw
(
   int *TouchPositionX, 
   int *TouchPositionY,
   TCHRES_DEVICE_STRUCT_PTR tchscr_dev_ptr
)
{       
   #define RAW_VALID_VALUE_TIMEOUT 254

   /* Declare and initialise local variables */
   uint_16 tmpRes = 0; 
   uchar tmpCnt; 
   uchar bSampleComplete = TCHRES_ERROR_NO_TOUCH;
   
   _tchres_set_pins_to_default( tchscr_dev_ptr );
   /* Switch on ADC channel on Y+ wire */
   lwgpio_set_functionality( &tchscr_dev_ptr->Y_PLUS_PIN, tchscr_dev_ptr->PIN_FUNCT.Y_PLUS_ADC_FUNCTION );
    
   /* to check that the touch screen surface is without any voltage and prepared */
   tmpCnt = 0;
   while( _tchres_read_touch_axis( Y_PLUS, tchscr_dev_ptr ) > _tchres_get_raw_limits( Y_TOUCH_MIN, tchscr_dev_ptr ) 
      && (++tmpCnt < RAW_VALID_VALUE_TIMEOUT) )
   {
     ;
   }

   /* test for tmpCnt overflov */
   if( tmpCnt == RAW_VALID_VALUE_TIMEOUT )
   {
      _tchres_set_pins_to_default( tchscr_dev_ptr );
      return ( TCHRES_ERROR_TIMEOUT );
   }
   
   /* when the touch screen surface is prepared 
   ** switch on on X+ wire high level */
   lwgpio_set_value( &tchscr_dev_ptr->X_PLUS_PIN, LWGPIO_VALUE_HIGH );    

   /* and Y- pin put into high Z mode to keep measurent non affected */
   lwgpio_set_direction( &tchscr_dev_ptr->Y_MINUS_PIN, LWGPIO_DIR_INPUT );    

   /* read value of Y axis and check if touch screen is touched */
   if(_tchres_get_filtered_axis( tchscr_dev_ptr, Y_PLUS, &tmpRes))
   {
      /* if it's touched save the result of Y measurement */
      *TouchPositionY = tmpRes;

      /* Disable ADC function on Y+ */
      lwgpio_set_functionality( &tchscr_dev_ptr->Y_PLUS_PIN, tchscr_dev_ptr->PIN_FUNCT.Y_PLUS_GPIO_FUNCTION );    

      /* Set pins to default values */
      lwgpio_set_value( &tchscr_dev_ptr->X_PLUS_PIN, LWGPIO_VALUE_LOW ); 
      lwgpio_set_value( &tchscr_dev_ptr->X_MINUS_PIN, LWGPIO_VALUE_LOW ); 
      lwgpio_set_value( &tchscr_dev_ptr->Y_PLUS_PIN, LWGPIO_VALUE_LOW ); 
      lwgpio_set_value( &tchscr_dev_ptr->Y_MINUS_PIN, LWGPIO_VALUE_LOW );
      
      lwgpio_set_direction( &tchscr_dev_ptr->Y_MINUS_PIN, LWGPIO_DIR_OUTPUT );     

      /* Switch on ADC channel on X+ wire */
      lwgpio_set_functionality( &tchscr_dev_ptr->X_PLUS_PIN, tchscr_dev_ptr->PIN_FUNCT.X_PLUS_ADC_FUNCTION );

      /* to check that the touch screen surface is without any voltage and prepared */
      tmpCnt = 0;
      while(( _tchres_read_touch_axis( X_PLUS, tchscr_dev_ptr ) > _tchres_get_raw_limits( X_TOUCH_MIN, tchscr_dev_ptr ))
         && ( ++tmpCnt < RAW_VALID_VALUE_TIMEOUT) )
      {
       ;
      }
      
      /* test for tmpCnt overflov */
      if( tmpCnt == RAW_VALID_VALUE_TIMEOUT )
      {
         _tchres_set_pins_to_default( tchscr_dev_ptr );
         return ( TCHRES_ERROR_TIMEOUT );
      }
                  
      /* when the touch screen surface is prepared 
      ** switch on on Y+ wire high level */
      lwgpio_set_value( &tchscr_dev_ptr->Y_PLUS_PIN, LWGPIO_VALUE_HIGH );   

      /* and X- pin put into high Z mode to keep measurent non affected */
      lwgpio_set_direction( &tchscr_dev_ptr->X_MINUS_PIN, LWGPIO_DIR_INPUT );    

      /* read value of X axis and check if touch screen is touched */
      if(_tchres_get_filtered_axis ( tchscr_dev_ptr, X_PLUS, &tmpRes ))
      {
         /* if it's touched save the result of X measurement */
         *TouchPositionX = tmpRes;
         bSampleComplete =  TCHRES_OK;
      }  
   }
   
   _tchres_set_pins_to_default( tchscr_dev_ptr );    
       
   /* return back result - if screen is touched or  not */
   return ( bSampleComplete );
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _tchres_get_raw_limits
* Returned Value   : none
* Comments         :
*    Return selected limit for adc 
*
*END*----------------------------------------------------------------------*/
static int_16 _tchres_get_raw_limits
(
   TCHRES_LIMITS_ENUM limit,
   TCHRES_DEVICE_STRUCT_PTR tchscr_dev_ptr
)
{
   int_16 result = 0;
   
   switch( limit )
   {
      case FULL_SCALE:
         result = tchscr_dev_ptr->ADC_LIMITS.FULL_SCALE;
         break;
      case X_TOUCH_MIN:
         result = tchscr_dev_ptr->ADC_LIMITS.X_TOUCH_MIN;
         break;
      case Y_TOUCH_MIN:
         result = tchscr_dev_ptr->ADC_LIMITS.Y_TOUCH_MIN;
         break;
      case X_TOUCH_MAX:
         result = tchscr_dev_ptr->ADC_LIMITS.X_TOUCH_MAX;
         break;
      case Y_TOUCH_MAX:
         result = tchscr_dev_ptr->ADC_LIMITS.Y_TOUCH_MAX;
         break;                     
      default: 
      break;
   } 
   return result;
}
/* EOF */  
  

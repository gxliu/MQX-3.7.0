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
* $FileName: dac_ldd.h$
* $Version : 3.7.2.1$
* $Date    : Mar-29-2011$
*
* Comments:
*   This component implements an internal D/A converter of the MCU.
*
*END************************************************************************/

#ifndef __dac_ldd_h__
    #define __dac_ldd_h__

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************
**
**  DAC device types and constants
**
***************************************************************************/

/* Available devices */
#define DAC_1                           0
    
/* DAC error codes and error identifier type */
typedef uint_16                         LDD_TError;
#define DAC_ERROR_OK                    0x00                                               
#define DAC_ERROR_DISABLED              (DAC_ERROR_BASE | 0x01)
#define DAC_ERROR_VALUE                 (DAC_ERROR_BASE | 0x02)
#define DAC_ERROR_RANGE                 (DAC_ERROR_BASE | 0x03)


/* DAC event mask type and codes */
typedef uint_32 LDD_TEventMask;

#define LDD_DAC_ON_BUFFER_WATERMARK     0x01u       /* OnBufferWatermark event mask */
#define LDD_DAC_ON_BUFFER_END           0x02u       /* OnBufferEnd event mask */
#define LDD_DAC_ON_BUFFER_START         0x04u       /* OnBufferStart event mask */


typedef pointer LDD_TDeviceDataPtr;        
                                           /* Pointer to the private structure  
                                            * containing component state information. 
                                            * Init method of the component creates 
                                            * the private state structure 
                                            * and returns the pointer to it. 
                                            * This pointer needs to be passed 
                                            * to every component method.
                                            */

typedef pointer  LDD_DAC_TDataPtr;          /* Type specifying the pointer to the DAC data variable */
typedef uint_32  LDD_DAC_TData;             /* The DAC data variable type */


typedef struct 
{
    /* DAC device number */
    uint_8        DAC_DEVICE_NUMBER;                  
    /* DAC reference selection */
    uint_8        DAC_REFSEL;                         
    /* DAC trigger mode */
    uint_8        DAC_TRIGER_MODE;                    
    /* DAC buffer mode */
    uint_8        DAC_MODE;                           
    /* DAC start buffer callback */
    void (_CODE_PTR_ DAC_PDD_BUFFER_START_CALLBACK)    (LDD_RTOS_TDeviceDataPtr);
    /* DAC start buffer callback */
    void (_CODE_PTR_ DAC_PDD_BUFFER_WATERMARK_CALLBACK)(LDD_RTOS_TDeviceDataPtr);   
    /* DAC end buffer callback */
    void (_CODE_PTR_ DAC_PDD_BUFFER_END_CALLBACK)      (LDD_RTOS_TDeviceDataPtr);         
} LDD_RTOS_TDeviceData, _PTR_ LDD_RTOS_TDeviceDataPtr;


/* 
** This data type is intended to be used for declaration 
** of DAC data buffer work modes which 
** will be passed to SetBufferMode method. 
*/

typedef enum {
    LDD_DAC_BUFFER_DISABLED     = 0,
    LDD_DAC_BUFFER_NORMAL_MODE  = 1,
    LDD_DAC_BUFFER_SWING_MODE   = 2,
    LDD_DAC_BUFFER_OTSCAN_MODE  = 3
} LDD_DAC_TBufferMode;


/*
** This data type is intended to be used for declaration 
** of DAC data buffer watermark levels which will be passed 
** to SetBufferWatermark methods. 
*/

typedef enum {
    LDD_DAC_BUFFER_WATERMARK_L1 = 0,    /* 1 word  */
    LDD_DAC_BUFFER_WATERMARK_L2 = 1,    /* 2 words */
    LDD_DAC_BUFFER_WATERMARK_L3 = 2,    /* 3 words */
    LDD_DAC_BUFFER_WATERMARK_L4 = 3     /* 4 words */
} LDD_DAC_TBufferWatermark;


/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_Init
*
* Input Params    : RTOSDeviceData - Pointer to the RTOS device structure. 
*                   This pointer will be passed to all callback 
*                   events as parameter.
*
* Returned Value  : Pointer to the dynamically allocated private structure 
*                   or NULL if there was an error.
*
* Comments        : Initializes the device according to design-time 
*                   configuration properties. 
*                   Allocates memory for the device data structure. 
*                   If the "Enable in init code" is set to "yes" then 
*                   the device is also enabled 
*                   (see the description of the Enable() method). 
*                   This method can be called only once. 
*                   Before the second call of Init() the Deinit() 
*                   must be called first.
*
*END**************************************************************************/

LDD_TDeviceDataPtr DAC_Init (
    /* [IN] Pointer to the RTOS device structure. */
    const LDD_RTOS_TDeviceDataPtr     RTOSDeviceData
);


/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_Deinit
*
* Input Params    : DeviceData - Device data structure pointer.
*
* Returned Value  : None
*
* Comments        : Disables the device and frees the device data structure memory.
*
*END**************************************************************************/

void DAC_Deinit (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr DeviceData
);

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_Enable
*
* Input Params    : DeviceData - Device data structure pointer.
*
* Returned Value  : DAC_ERR_OK     - OK
*
* Comments        : Enables DAC device. If possible, this method switches 
*                   on digital-to-analog converter device, voltage reference, etc. 
*                   This method is intended to be used together 
*                   with DAC_Disable method to temporary switch On/Off 
*                   the device after the device is initialized. 
*
*END**************************************************************************/

LDD_TError DAC_Enable (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr DeviceData
);


/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_Disable
*
* Input Params    : DeviceData - Device data structure pointer.
*
* Returned Value  : DAC_ERR_OK - OK
*
* Comments        : Disables the DAC device. If possible, this method switches 
*                   off digital-to-analog converter device, voltage reference, etc. 
*                   When the device is disabled, some component methods 
*                   should not be called. If so, error DAC_ERR_DISABLED is reported. 
*                   This method is intended to be used together with DAC_Enable 
*                   method to temporary switch On/Off the device after 
*                   the device is initialized. This method is not required. 
*                   The Deinit() method can be used to switch off 
*                   and uninstall the device.
*
*END**************************************************************************/

LDD_TError DAC_Disable  (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr DeviceData
);


/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetEventMask
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   EventMask    - Mask of events to enable.
*                                  e.g. LDD_DAC_ON_WATERMARK
*                                  The component event masks 
*                                  are described in the API constants
*
* Returned Value  : DAC_ERR_OK       - OK
*                   DAC_ERR_VALUE    - Event mask is not valid.
*                   DAC_ERR_DISABLED - This component is disabled by user
*
* Comments        : Enables/disables event(s). 
*                   This method is available if the interrupt service/event 
*                   property is enabled and at least one event is enabled. 
*                   Pair method to GetEventMask().
*
* Note            : This method is usable only for DAC devices 
*                   with the support of interrupts.
*
*END**************************************************************************/

LDD_TError DAC_SetEventMask (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr DeviceData,
    /* [IN] Mask of events to enable. */
    LDD_TEventMask EventMask
);

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_GetEventMask
*
* Input Params    : DeviceData   - Device data structure pointer.
*
* Returned Value  : Current EventMask. 
*                   The component event masks are described in the API constants 
*
* Comments        : Returns current events mask. 
*                   This method is available if the interrupt service/event 
*                   property is enabled and at least one event is enabled. 
*                   Pair method to SetEventMask().
*
* Note            : This method is usable only for DAC devices 
*                   with the support of interrupts.
*
*END**************************************************************************/

LDD_TEventMask DAC_GetEventMask (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr DeviceData
);

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_GetEventStatus
*
* Input Params    : DeviceData   - Device data structure pointer.
*
* Returned Value  : Current EventMask. 
*                   The component event masks are described in the API constants 
*
* Comments        : This method returns current state of status flags 
*                   and clears pending interrupt flags. 
*                   Return value has the same format as EventMask parameter 
*                   of SetEventMask() method. 
*                   Can be used for polling mode without using events.
*
* Note            : This method is usable only for DAC devices 
*                   with the support of interrupts.
*
*END**************************************************************************/

LDD_TEventMask DAC_GetEventStatus (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr DeviceData
);

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetValue
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   Data         - User data
*
* Returned Value  : DAC_ERR_OK       - OK
*
* Comments        : Sets DAC output voltage according to specified value. 
*                   Input data format is specified by Data type design 
*                   time configuration property settings. 
*                   If selected formatting is not native for DAC device which 
*                   is used then transformation (e.g. shifting) is done.
*
*END**************************************************************************/

LDD_TError DAC_SetValue (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr  DeviceData,
    /* [IN] User data */
    LDD_DAC_TData       Data
);

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetBuffer
*
* Input Params    : DeviceData      - Device data structure pointer.
*                   DataArrayPtr    - Pointer to array containing user data.
*                   DataArrayLength - Length of user data array   
*                                     which should be written to data buffer.
*                   StartBufferReg  - Index of first written data buffer register.
*
* Returned Value  : DAC_ERR_OK          - OK
*                   ERR_RANGE       - Parameter out of range
*
* Comments        : Writes an array of data words to the data buffer registers. 
*                   Array is defined by pointer to start address and by length. 
*                   First written data buffer register is defined by index, 
*                   rest of array is written to registers with increasing index.
*                   If the length of array exceeds number of registers between 
*                   the first written register and the last one at the end of 
*                   the buffer then an ERR_RANGE is returned and no data are written. 
*                   It is possible to write all register available 
*                   in hardware - no checking for current upper limit value 
*                   of buffer is done, so it is possible to write data to 
*                   the whole data buffer regardless of current configuration.
*                   DataArrayPtr has fixed data type regardless of current hardware 
*                   or design time configuration and must be always used. 
*                   Real type of user data is specified in configuration time 
*                   in Data type property and execution of SetBuffer method 
*                   is done according to this setting.
*
* Note            : This method is usable only for DAC devices 
*                   with a data buffer module.
*
*END**************************************************************************/

LDD_TError DAC_SetBuffer (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr  DeviceData,
    /* [IN] Pointer to array containing user data. */
    uint_16_ptr          DataArrayPtr,
    /* [IN] Length of user data array which should be written to data buffer. */
    uint_8              DataArrayLength,
    /* [IN] Index of first written data buffer register. */
    uint_8              StartBufferReg
);


/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_ForceSWTrigger
*
* Input Params    : DeviceData   - Device data structure pointer.
*
* Returned Value  : DAC_ERR_OK       - OK
*                   DAC_ERR_DISABLED - HW trigger is selected or buffer is disabled.
*
* Comments        : Triggers data buffer read pointer.
*
* Note            : This method is usable only for DAC devices 
*                   with a software triggering support.
*
*END**************************************************************************/

LDD_TError DAC_ForceSWTrigger (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr  DeviceData
);

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetBufferMode
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   Mode         - Buffer work mode.
*
* Returned Value  : DAC_ERR_OK       - OK
*
* Comments        : Selects buffer work mode. 
*                   Work mode constants described in the API Types section 
*                   can be used to select requested operation mode.
*
* Note            : This method is usable only for DAC devices 
*                   with a data buffer module.
*
*END**************************************************************************/

LDD_TError DAC_SetBufferMode(
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr  DeviceData,  
    /* [IN] - Buffer work mode. */    
    LDD_DAC_TBufferMode Mode
);

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetBufferSize
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   Size         - Number of data buffer registers.
*
* Returned Value  : DAC_ERR_OK       - OK
*                   ERR_RANGE    - Requested buffer size out of range.
*
* Comments        : Sets data buffer size. 
*                   If requested buffer size exceeds hardware capacity 
*                   then ERR_RANGE is returned.
*
* Note            : This method is usable only for DAC devices 
*                   with a data buffer module.
*
*END**************************************************************************/

LDD_TError DAC_SetBufferSize(
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr  DeviceData,
    /* [IN] Number of data buffer registers. */
    uint_8               Size
);

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetBufferWatermark
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   Watermark    - Words number between the read pointer 
*                                  and upper address. e.g. LDD_DAC_BUFFER_WATERMARK_L1
*                                  Possible watermark levels are described 
*                                  in the section API Types.
*
* Returned Value  : DAC_ERR_OK       - OK
*
* Comments        : Selects watermark words number.
*
* Note            : This method is usable only for DAC devices 
*                   with a data buffer module.
*
*END**************************************************************************/

LDD_TError DAC_SetBufferWatermark(
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr          DeviceData,
    /* [IN] number between the read pointer and upper address. */    
    LDD_DAC_TBufferWatermark    Watermark
);

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetBufferReadPointer
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   Pointer      - New read pointer value.
*
* Returned Value  : DAC_ERR_OK       - OK
*                   ERR_RANGE    - Pointer value out of range.
*
* Comments        : Sets the data buffer read pointer value. 
*                   If requested pointer value is greater 
*                   than buffer size defined by buffer upper limit value 
*                   then error is returned. 
*
* Note            : This method is usable only for DAC devices 
*                   with a data buffer module.
*
*END**************************************************************************/

LDD_TError DAC_SetBufferReadPointer(
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr  DeviceData,
    /* [IN] New read pointer value. */
    uint_8              Pointer
);



#ifdef __cplusplus
}
#endif


#endif /* __dac_ldd_h__ */

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
* $FileName: dac_ldd.c$
* $Version : 3.6.1.0$
* $Date    : May-19-2010$
*
* Comments:
*   This component implements an internal D/A converter of the MCU.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "dac_pdd_mcf51mm.h"
#include "dac_pdd_mcf51mm_mac.h"
#include "dac_ldd.h"


/* This constant contains maximal buffer size available on selected device. */
#define DAC_BUFFER_MAX_SIZE         16

#define DAC_AVAILABLE_EVENTS_MASK (LDD_DAC_ON_BUFFER_WATERMARK | LDD_DAC_ON_BUFFER_END | LDD_DAC_ON_BUFFER_START)

typedef struct {
    /* Copy of RTOS device data structure */
    LDD_RTOS_TDeviceData RTOS_DeviceData;
    /* DAC base addres pointer */
    DAC_MemMapPtr        DAC_MODULE_BASE_PTR;
} DAC_TDeviceData;                              /* Device data structure type */


typedef DAC_TDeviceData* DAC_TDeviceDataPtr;    /* Pointer to the device data structure. */


static DAC_TDeviceDataPtr  DAC_DeviceDataPrv[DAC_COUNT];


/* local function prototypes */
static void DAC_BufferInterrupt(DAC_TDeviceDataPtr DeviceDataPtr); 


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
    LDD_RTOS_TDeviceDataPtr     RTOSDeviceData
)
{
    DAC_MemMapPtr       DAC_BasePtr;
    DAC_TDeviceDataPtr  DAC_DeviceDataPtr;
    uint_32             DAC_DeviceNumber = RTOSDeviceData->DAC_DEVICE_NUMBER;
    uint_32             i; 
    
    /* Initilize DAC module base address */
    if (NULL == (DAC_BasePtr = _bsp_get_dac_base_address(DAC_DeviceNumber)))   {
        return NULL;      /* No such DAC device */
    }


    if (NULL == (DAC_DeviceDataPtr = _mem_alloc((_mem_size)sizeof(DAC_TDeviceData))))  {
        return NULL;      /* MQX_OUT_OF_MEMORY */
    }

    /* Store the RTOS device structure */
    DAC_DeviceDataPtr->RTOS_DeviceData = *RTOSDeviceData;

    /* Store DAC module base address */
    DAC_DeviceDataPtr->DAC_MODULE_BASE_PTR = DAC_BasePtr;
    
    
    DAC_DeviceDataPrv[DAC_DeviceNumber] = DAC_DeviceDataPtr;
    
    /* Disable device */
    DAC_PDD_DisableDevice(DAC_BasePtr); 


    /* Interrupt vector(s) installation */
    if (NULL == _int_install_isr ( _bsp_get_dac_vector(DAC_DeviceNumber), 
                                  (void (_CODE_PTR_))DAC_BufferInterrupt, 
                                  (pointer)DAC_DeviceDataPtr)) 
    {
        _mem_free(DAC_DeviceDataPtr);    
    
        return NULL;    
    }
    
    
    /* Clear DAC DATA registers */
    for (i = 0; i < 16; i++)    {
        DAC_DAT_REG(DAC_BasePtr, i) = (uint_16)0x0000;
    }

    /* Set buffer upper limit to 16 words */
    DAC_PDD_SetBufferSize(DAC_BasePtr, (DAC_BUFFER_MAX_SIZE - 1)); 
        
    DAC_PDD_EnableBuffer(DAC_BasePtr, PDD_ENABLE);    
    
    /* Select DAC Buffer Work Mode  */
    switch(DAC_DeviceDataPtr->RTOS_DeviceData.DAC_MODE)
    {

        case LDD_DAC_BUFFER_NORMAL_MODE:
            DAC_PDD_SelectBufferMode(DAC_BasePtr, DAC_PDD_BUFFER_NORMAL_MODE);
            break;
                    
        case LDD_DAC_BUFFER_SWING_MODE:
            DAC_PDD_SelectBufferMode(DAC_BasePtr, DAC_PDD_BUFFER_SWING_MODE);
            break;
            
        case LDD_DAC_BUFFER_OTSCAN_MODE:
            DAC_PDD_SelectBufferMode(DAC_BasePtr, DAC_PDD_BUFFER_OTSCAN_MODE);
            break;    

        case LDD_DAC_BUFFER_DISABLED:
        default:
            DAC_PDD_EnableBuffer(DAC_BasePtr, PDD_DISABLE);
            break;
    }
    
    /* DAC reference selection */
    DAC_PDD_SelectReference(DAC_BasePtr, DAC_DeviceDataPtr->RTOS_DeviceData.DAC_REFSEL);
                                                                
    /* DAC trigger selection */
    DAC_PDD_SelectTrigger(DAC_BasePtr, DAC_DeviceDataPtr->RTOS_DeviceData.DAC_TRIGER_MODE);


    /* Clear all interrupt flags */
    DAC_PDD_ClearInterruptFlags(DAC_BasePtr, DAC_AVAILABLE_EVENTS_MASK); 

    /* Check if valid buffer start callback is installed */    
    if (DAC_DeviceDataPtr->RTOS_DeviceData.DAC_PDD_BUFFER_START_CALLBACK != NULL)    {
        /* Enable start buffer interrupt */
        DAC_PDD_EnableInterrupts(DAC_BasePtr, DAC_PDD_BUFFER_START_INT); 
    }    

    /* Check if valid watermark callback is installed */    
    if (DAC_DeviceDataPtr->RTOS_DeviceData.DAC_PDD_BUFFER_WATERMARK_CALLBACK != NULL)   {
        
        /* Enable Watermark interrupt */
        DAC_PDD_EnableInterrupts(DAC_BasePtr, DAC_PDD_BUFFER_WATERMARK_INT); 
    }    

    /* Check if valid buffer end callback is installed */    
    if (DAC_DeviceDataPtr->RTOS_DeviceData.DAC_PDD_BUFFER_END_CALLBACK != NULL)    {
        /* Enable Watermark interrupt */
        DAC_PDD_EnableInterrupts(DAC_BasePtr, DAC_PDD_BUFFER_END_INT);
    }    

    /* Return pointer to the data data structure */
    return (DAC_DeviceDataPtr); 
}
            

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
)
{
    /* Get DAC module base address */
    DAC_MemMapPtr DAC_BasePtr      = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;

    uint_32       DAC_DeviceNumber = ((DAC_TDeviceDataPtr)DeviceData)->RTOS_DeviceData.DAC_DEVICE_NUMBER;
    
    /* Disable device */
    DAC_PDD_DisableDevice((DAC_BasePtr)); 
    
    _mem_free(DAC_DeviceDataPrv[DAC_DeviceNumber]);
    
    DAC_DeviceDataPrv[DAC_DeviceNumber] = NULL;    

}
/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_Enable
*
* Input Params    : DeviceData - Device data structure pointer.
*
* Returned Value  : DAC_ERROR_OK     - OK
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
) 
{
    /* Get DAC module base address */
    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
    
    DAC_PDD_EnableDevice(DAC_BasePtr);

    return DAC_ERROR_OK;
}

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_Disable
*
* Input Params    : DeviceData - Device data structure pointer.
*
* Returned Value  : DAC_ERROR_OK - OK
*
* Comments        : Disables the DAC device. If possible, this method switches 
*                   off digital-to-analog converter device, voltage reference, etc. 
*                   When the device is disabled, some component methods 
*                   should not be called. If so, error DAC_ERROR_DISABLED is reported. 
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
) 
{
    
    /* Get DAC module base address */
    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
    
    DAC_PDD_DisableDevice(DAC_BasePtr);

    return DAC_ERROR_OK;
}

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
* Returned Value  : DAC_ERROR_OK       - OK
*                   DAC_ERROR_VALUE    - Event mask is not valid.
*                   DAC_ERROR_DISABLED - This component is disabled by user
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
) 
{
  
    /* Get DAC module base address */
    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
  
    /* Device state test - Is device enabled? */
    if (DAC_PDD_GetDeviceState(DAC_BasePtr) == DAC_PDD_DISABLE)
    {
        return DAC_ERROR_DISABLED;  /* No, return DAC_ERROR_DISABLED */
    }

    /* Event mask test - Is the mask valid for given component setting? */
    if (EventMask & (LDD_TEventMask)(~((LDD_TEventMask)DAC_AVAILABLE_EVENTS_MASK)))
    {
        return DAC_ERROR_VALUE;     /* No, return DAC_ERROR_VALUE */
    }

    DAC_PDD_EnableInterrupts(DAC_BasePtr,(uint_8)EventMask);

    return DAC_ERROR_OK;    
}

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
) 
{

    /* Get DAC module base address */
    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
   
    /* Return current event mask for generated events */
    return((LDD_TEventMask)((LDD_TEventMask)(DAC_PDD_GetInterruptsMask(DAC_BasePtr)) & (LDD_TEventMask)DAC_AVAILABLE_EVENTS_MASK));

}
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
)
{
    uint_8 State;

    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
    
    State = DAC_PDD_GetInterruptFlags(DAC_BasePtr); /* Save pending interrupts state */

    DAC_PDD_ClearInterruptFlags(DAC_BasePtr, State); /* Clear flags */
    
    return((LDD_TEventMask)State);       /* Return interrupt flags */

}

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetValue
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   Data         - User data
*
* Returned Value  : DAC_ERROR_OK       - OK
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
)
{
    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
    
    DAC_PDD_SetData(DAC_BasePtr,(uint_16)Data, 0);

    return DAC_ERROR_OK;
}

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
* Returned Value  : DAC_ERROR_OK          - OK
*                   DAC_ERROR_RANGE       - Parameter out of range
*
* Comments        : Writes an array of data words to the data buffer registers. 
*                   Array is defined by pointer to start address and by length. 
*                   First written data buffer register is defined by index, 
*                   rest of array is written to registers with increasing index.
*                   If the length of array exceeds number of registers between 
*                   the first written register and the last one at the end of 
*                   the buffer then an DAC_ERROR_RANGE is returned and no data are written. 
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
    uint_16_ptr         DataArrayPtr,
    /* [IN] Length of user data array which should be written to data buffer. */
    uint_8              DataArrayLength,
    /* [IN] Index of first written data buffer register. */
    uint_8              StartBufferReg
)
{
    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
    uint_32       i;

    /* Range test -> Are input parameters in possible range? */
    if((StartBufferReg + DataArrayLength) > DAC_BUFFER_MAX_SIZE) 
    {
        return DAC_ERROR_RANGE;                  /* No, return ERR_RANGE. */
    }

    for(i = 0U; i < DataArrayLength; i++)
    {
        DAC_PDD_SetData(DAC_BasePtr,(uint_16)(*(DataArrayPtr + i)),(StartBufferReg + i));
    }

    return DAC_ERROR_OK;
}


/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_ForceSWTrigger
*
* Input Params    : DeviceData   - Device data structure pointer.
*
* Returned Value  : DAC_ERROR_OK       - OK
*                   DAC_ERROR_DISABLED - HW trigger is selected or buffer is disabled.
*
* Comments        : Triggers data buffer read pointer.
*
* Note            : This method is usable only for DAC devices 
*                   with a software triggering support.
*
*END**************************************************************************/

LDD_TError DAC_ForceSWTrigger(
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr  DeviceData
)
{

    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;

    /* Device state test - this test can be disabled by setting the "Ignore enable test"
       property to the "yes" value in the "Configuration inspector" */
    
    if (DAC_PDD_GetDeviceState(DAC_BasePtr) == 0x00u) /* Is device enabled? */
    {
        return DAC_ERROR_DISABLED;               /* No, return ERR_DISABLED */
    }
    if (DAC_PDD_GetBufferState(DAC_BasePtr) == 0x00u) /* Is buffer enabled? */
    {
        return DAC_ERROR_DISABLED;               /* No, return ERR_DISABLED */
    }
    if (DAC_PDD_GetTriggerSource(DAC_BasePtr) == 0x00u) /* Is SW trigger enabled? */
    {
        return DAC_ERROR_DISABLED;               /* No, return ERR_DISABLED */
    }

    DAC_PDD_SWTrigger(DAC_BasePtr);
    
    return DAC_ERROR_OK;
}

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetBufferMode
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   Mode         - Buffer work mode.
*
* Returned Value  : DAC_ERROR_OK       - OK
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
)
{
    /* Get DAC module base address */
    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
    
    if (Mode == LDD_DAC_BUFFER_DISABLED)    {
        DAC_PDD_EnableBuffer(DAC_BasePtr, DAC_PDD_BUFFER_DISABLE);
    } 
    else  {
        DAC_PDD_SelectBufferMode(DAC_BasePtr, (((Mode - 1) << DAC_C1_DACBFMD_SHIFT) & DAC_C1_DACBFMD_MASK));
        DAC_PDD_EnableBuffer(DAC_BasePtr, DAC_PDD_BUFFER_ENABLE);
    }
    
    return DAC_ERROR_OK;
}

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetBufferSize
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   Size         - Number of data buffer registers.
*
* Returned Value  : DAC_ERROR_OK       - OK
*                   DAC_ERROR_RANGE    - Requested buffer size out of range.
*
* Comments        : Sets data buffer size. 
*                   If requested buffer size exceeds hardware capacity 
*                   then DAC_ERROR_RANGE is returned.
*
* Note            : This method is usable only for DAC devices 
*                   with a data buffer module.
*
*END**************************************************************************/

LDD_TError DAC_SetBufferSize(
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr  DeviceData,
    /* [IN] Number of data buffer registers. */
    uint_8              Size
)
{
    
    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
  
    /* Buffer size vallue test */
    if(Size > DAC_BUFFER_MAX_SIZE)       /* Is required buffer size in possible range? */
    {
        return DAC_ERROR_RANGE;                  /* No, return ERR_RANGE. */
    }

    DAC_PDD_SetBufferSize(DAC_BasePtr,Size);
    
    return DAC_ERROR_OK;
}

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
* Returned Value  : DAC_ERROR_OK       - OK
*
* Comments        : Selects watermark words number.
*
* Note            : This method is usable only for DAC devices 
*                   with a data buffer module.
*
*END**************************************************************************/

LDD_TError DAC_SetBufferWatermark (
    /* [IN] Device data structure pointer. */
    LDD_TDeviceDataPtr          DeviceData,
    /* [IN] number between the read pointer and upper address. */    
    LDD_DAC_TBufferWatermark    Watermark
)
{

    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;

    uint_8        WatermarkMask = (Watermark << DAC_C1_DACBFWM_SHIFT) & DAC_C1_DACBFWM_MASK;
    
    DAC_PDD_SetBufferWatermark(DAC_BasePtr,WatermarkMask);

    return DAC_ERROR_OK;
}

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_SetBufferReadPointer
*
* Input Params    : DeviceData   - Device data structure pointer.
*                   Pointer      - New read pointer value.
*
* Returned Value  : DAC_ERROR_OK       - OK
*                   DAC_ERROR_RANGE    - Pointer value out of range.
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
)
{

    DAC_MemMapPtr DAC_BasePtr = ((DAC_TDeviceDataPtr)DeviceData)->DAC_MODULE_BASE_PTR;
    
    /* Is required read pointer value in possible range? */
    if(Pointer > DAC_PDD_GetBufferSize(DAC_BasePtr)) 
    {
        return DAC_ERROR_RANGE;                  /* No, return DAC_ERROR_RANGE. */
    }
    
    DAC_PDD_SetBufferReadPointer(DAC_BasePtr,Pointer);

    return DAC_ERROR_OK;
}

/*FUNCTION*********************************************************************
* 
* Function Name   : DAC_BufferInterrupt
*
* Input Params    : DeviceDataPtr   - Device data structure pointer.
*
* Returned Value  : None
*
* Comments        : DAC Buffer interrupt handler
*                   The DAC_BufferInterrupt() clears the DAC pending flags 
*                   and calls user callback functions registered using
*                   DAC_Init() function.
*
*END**************************************************************************/

static void DAC_BufferInterrupt(DAC_TDeviceDataPtr DeviceDataPtr)
{

    uint_8        State;
    uint_32       DAC_DeviceNumber  = DeviceDataPtr->RTOS_DeviceData.DAC_DEVICE_NUMBER;
    DAC_MemMapPtr DAC_BasePtr       = DeviceDataPtr->DAC_MODULE_BASE_PTR;
    
    State  = DAC_PDD_GetInterruptFlags(DAC_BasePtr);           /* Store pending interrupts state */
    State &= DAC_PDD_GetInterruptsMask(DAC_BasePtr);           /* Handle only enabled interrupts */
    DAC_PDD_ClearInterruptFlags(DAC_BasePtr, State);           /* Clear flags */

    if (   (State & DAC_PDD_BUFFER_WATERMARK_INT) 
        && (NULL != DeviceDataPtr->RTOS_DeviceData.DAC_PDD_BUFFER_WATERMARK_CALLBACK))
    {
        /* Call user event */            
        DeviceDataPtr->RTOS_DeviceData.DAC_PDD_BUFFER_WATERMARK_CALLBACK(DeviceDataPtr->RTOS_DeviceData);
    }

    if (   (State & DAC_PDD_BUFFER_END_INT) 
        && (NULL != DeviceDataPtr->RTOS_DeviceData.DAC_PDD_BUFFER_END_CALLBACK))

    {
        /* Call user event */            
        DeviceDataPtr->RTOS_DeviceData.DAC_PDD_BUFFER_END_CALLBACK(DeviceDataPtr->RTOS_DeviceData);
    }

    if (   (State & DAC_PDD_BUFFER_START_INT) 
        && (NULL != DeviceDataPtr->RTOS_DeviceData.DAC_PDD_BUFFER_START_CALLBACK))
    {
       /* Call user event */
       DeviceDataPtr->RTOS_DeviceData.DAC_PDD_BUFFER_START_CALLBACK(DeviceDataPtr->RTOS_DeviceData);
    }
}

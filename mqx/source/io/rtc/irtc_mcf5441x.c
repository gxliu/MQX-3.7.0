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
* $FileName: irtc_mcf5441x.c$
* $Version : 3.6.3.0$
* $Date    : Sep-22-2010$
*
* Comments:
*
*   Processor family specific file needed for IRTC module.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>


#define RTC_CTRL_WE0_MASK           (1 << 0)
#define RTC_CTRL_WE1_MASK           (1 << 1)
#define RTC_CTRL_WE_MASK            (RTC_CTRL_WE1_MASK|RTC_CTRL_WE0_MASK)


#define RTC_BASE_YEAR               2112
#define RTC_STATUS_INVAL_MASK       (1 << 0)
#define RTC_STATUS_C_DON_MASK       (1 << 1)
#define RTC_STATUS_BERR_MASK        (1 << 2)
#define RTC_STATUS_OCAL_MASK        (1 << 3)
#define RTC_STATUS_WPE_MASK         (1 << 4)
#define RTC_STATUS_CLV_MASK         (1 << 5)

#define RTC_CTRL_SWR_MASK           256

#define NUM_OF_TEST                 200


/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_init
* Returned Value   : MQX error code
* Comments         :
*    This function (re)initializes/clears/enables RTC module.
*    If cleared, alarm happens after RTC overflow, stopwatch happens next minute.
*    Reset disables and clears all interrupts and stopwatch (even if cleared).
*
*END*********************************************************************/

uint_32 _rtc_init 
(
    /* [IN] flags identifying init operations */
    uint_32 flags
)
{
    VMCF5XXX_IRTC_STRUCT_PTR rtc    = _bsp_get_rtc_base_address ();  
    uint_32                  result = MQX_OK;

    _int_disable();

    if( _rtc_tested_unlock( NUM_OF_TEST ) != MQX_OK )    {
        _int_enable();
        return MQX_RTC_UNLOCK_FAILED;
    }

    if (flags & RTC_INIT_FLAG_CLEAR)    {
        rtc->RTC_YEAR        = (int_8)((int_16)2009-RTC_BASE_YEAR);
        rtc->RTC_MONTH       = (uint_8)12;
        rtc->RTC_DAYS        = (uint_8)9;
        rtc->RTC_DAY_OF_WEEK = (uint_8)3;
        rtc->RTC_HOURS       = (uint_8)0;
        rtc->RTC_MINUTES     = (uint_8)0;
        rtc->RTC_SECONDS     = (uint_8)0;

        rtc->RTC_ALM_YEAR    = (int_8)((uint_16)2009 - RTC_BASE_YEAR);
        rtc->RTC_ALM_MONTH   = (uint_8)0;
        rtc->RTC_ALM_DAYS    = (uint_8)0;
        rtc->RTC_ALM_HOURS   = (uint_8)0;
        rtc->RTC_ALM_MINUTES = (uint_8)0;
        rtc->RTC_ALM_SEC     = (uint_8)0;
    }

    if (flags & RTC_INIT_FLAG_RESET)    {
        rtc->RTC_IER  = 0x0000;
        rtc->RTC_CTRL = RTC_CTRL_SWR_MASK;      
    }

    if (flags & RTC_INIT_FLAG_ENABLE)    {
        /* RTC module is enabled after reset and its not possible to disable it */
    }

    _rtc_lock();

    /* Install default RTC interrupt function */
//    _mcf5441_int_init(BSP_RTC_INT_VECTOR, BSP_RTC_INT_LEVEL, FALSE);
    
    _int_enable();

    return MQX_OK;
}



/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_int_install
* Returned Value   : MQX error code
* Comments         :
*    This function installs given ISR for RTC module.
*
*END*********************************************************************/
uint_32 _rtc_int_install 
(
    /* [IN] pointer to user ISR code */
    pointer isr
)
{
    void (_CODE_PTR_ result)(pointer);
    
    VMCF5XXX_IRTC_STRUCT_PTR rtc;
    
    if (NULL == isr) return MQX_INVALID_POINTER;
    
    rtc = _bsp_get_rtc_base_address ();
    
    result = _int_install_isr (_bsp_get_rtc_vector (), (void (_CODE_PTR_))isr, (pointer)rtc);
    
    if (NULL == result) return _task_get_error ();
    
    return MQX_OK;
}


/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_int_enable
* Returned Value   : bitmask of new int enable state
* Comments         :
*    This function enables/disables RTC interrupts according to specified bitmask.
*
*END*********************************************************************/
uint_32 _rtc_int_enable 
(
    /* [IN] whether to enable or disable interrupts */
    boolean enable, 
    /* [IN] bitmask of affected interrupts */
    uint_32 bitmask
)
{
    VMCF5XXX_IRTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();
    
    while( (_rtc_tested_unlock( NUM_OF_TEST )) != MQX_OK ){
    };
    
    if (enable) {
        
        bitmask =  rtc->RTC_IER | bitmask;
        rtc->RTC_IER = bitmask;
    }
    else    {
        
        bitmask =  rtc->RTC_IER & (~bitmask);
        rtc->RTC_IER = bitmask;
    }
   
    _rtc_lock();

    
    _mcf5441_int_init(BSP_RTC_INT_VECTOR, BSP_RTC_INT_LEVEL, rtc->RTC_IER == 0x0001 ? FALSE : TRUE);

    
    return bitmask;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_isr
* Returned Value   : none
* Comments         :
*    This is template ISR for RTC module.
*
*END*********************************************************************/
void _rtc_isr 
(
    /* [IN] data pointer passed to interrupt */
    pointer ptr
)
{
    VMCF5XXX_IRTC_STRUCT_PTR rtc = (VMCF5XXX_IRTC_STRUCT_PTR)ptr;
    uint_16 mask;
    
    mask = (uint_16)(rtc->RTC_ISR & rtc->RTC_IER);
    
    
    if (mask & RTC_INT_ALM_MASK)
    {
        // alarm interrupt
    }
    
    if (mask & RTC_INT_STW_MASK)
    {
        // stopwatch interrupt
    }
    
    if (mask & (RTC_INT_1HZ_MASK | RTC_INT_MIN_MASK | RTC_INT_HR_MASK | RTC_INT_DAY_MASK))
    {
        // time change interrupt (sec, min, hour, day)
    }

    /* clear interrupt flag */
    _rtc_clear_requests(mask);
}

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_clear_requests
* Returned Value   : none
* Comments         :
*   This function clears RTC interrupt requests according to given bitmask.
*   If 
*
*END*********************************************************************/
void _rtc_clear_requests 
(
    /* [IN] bitmask of affected interrupts */
    uint_32 bitmask
)
{
    VMCF5XXX_IRTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();

    while( _rtc_tested_unlock( NUM_OF_TEST )!= MQX_OK )
    {
    };    

    rtc->RTC_ISR = bitmask;
    _rtc_lock();
}


/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_get_status
* Returned Value   : bitmask of actual RTC interrupt requests.
* Comments         :
*
*END*********************************************************************/

uint_32 _rtc_get_status 
(
    void
)
{

    VMCF5XXX_IRTC_STRUCT_PTR rtc = _bsp_get_rtc_base_address ();

    return (uint_32)rtc->RTC_ISR & ~0x0001;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _bsp_get_rtc_base_address
* Returned Value   : pointer to base of RTC registers
* Comments         :
*    This function returns base address of RTC related register space.
*
*END*********************************************************************/
pointer _bsp_get_rtc_base_address 
(
    void
)
{
    VMCF5441_STRUCT_PTR reg_base = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();

    return (pointer)&reg_base->RTC;
}


/*FUNCTION****************************************************************
* 
* Function Name    : _bsp_get_rtc_vector
* Returned Value   : MQX vector number for specified interrupt
* Comments         :
*    This function returns index into MQX interrupt vector table for
*    RTC interrupt.
*
*END*********************************************************************/
PSP_INTERRUPT_TABLE_INDEX _bsp_get_rtc_vector 
(
    void
)
{
    return MCF5441_INT_Robust_RTC;
}


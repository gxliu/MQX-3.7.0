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
* $FileName: irtc_mcf5441x.h$
* $Version : 3.6.3.0$
* $Date    : Sep-22-2010$
*
* Comments:
*
*   Processor family specific file needed for IRTC module.
*
*END************************************************************************/

#ifndef __irtc_mcf5441x__
    #define __irtc_mcf5441x__ 1


/* RTC init flag masks */
#define RTC_INIT_FLAG_CLEAR     (1 << 0)
#define RTC_INIT_FLAG_RESET     (1 << 1)
#define RTC_INIT_FLAG_ENABLE    (1 << 2)

/* RTC masks for clearing interrupt requests */
#define RTC_INT_SAM7_MASK       MCF5XXX_RTC_INT_SAM7_MASK
#define RTC_INT_SAM6_MASK       MCF5XXX_RTC_INT_SAM6_MASK
#define RTC_INT_SAM5_MASK       MCF5XXX_RTC_INT_SAM5_MASK
#define RTC_INT_SAM4_MASK       MCF5XXX_RTC_INT_SAM4_MASK
#define RTC_INT_SAM3_MASK       MCF5XXX_RTC_INT_SAM3_MASK
#define RTC_INT_SAM2_MASK       MCF5XXX_RTC_INT_SAM2_MASK
#define RTC_INT_SAM1_MASK       MCF5XXX_RTC_INT_SAM1_MASK
#define RTC_INT_SAM0_MASK       MCF5XXX_RTC_INT_SAM0_MASK

#define RTC_INT_2HZ_MASK        MCF5XXX_RTC_INT_2HZ_MASK 
#define RTC_INT_1HZ_MASK        MCF5XXX_RTC_INT_1HZ_MASK 
#define RTC_INT_MIN_MASK        MCF5XXX_RTC_INT_MIN_MASK 
#define RTC_INT_HR_MASK         MCF5XXX_RTC_INT_HR_MASK  
#define RTC_INT_DAY_MASK        MCF5XXX_RTC_INT_DAY_MASK 
#define RTC_INT_ALM_MASK        MCF5XXX_RTC_INT_ALM_MASK 
#define RTC_INT_STW_MASK        MCF5XXX_RTC_INT_STW_MASK 
#define RTC_INT_ALL_MASK        MCF5XXX_RTC_INT_ALL_MASK 

/* RTC masks for RTC example application */
#define RTC_RTCISR_SW           RTC_INT_STW_MASK
#define RTC_RTCISR_ALM          RTC_INT_ALM_MASK
#define RTC_RTCIENR_SW          RTC_INT_STW_MASK
#define RTC_RTCIENR_ALM         RTC_INT_ALM_MASK


/* RTC CFG register masks for 51EM */
#define RTC_CFG_DATA_CFG0       (1 << 0)
#define RTC_CFG_DATA_CFG1       (1 << 1)
#define RTC_CFG_DATA_CFG2       (1 << 2)
#define RTC_CFG_DATA_CFG3       (1 << 3)
#define RTC_CFG_DATA_CFG4       (1 << 4)
#define RTC_CFG_DATA_CFG5       (1 << 5)
#define RTC_CFG_DATA_CFG6       (1 << 6)
#define RTC_CFG_DATA_CFG7       (1 << 7)


/* IRTC platform specific functions */

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

extern uint_32 _rtc_init 
(
    /* [IN] flags identifying init operations */
    uint_32 flags
);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_int_install
* Returned Value   : MQX error code
* Comments         :
*    This function installs given ISR for RTC module.
*
*END*********************************************************************/

extern uint_32 _rtc_int_install 
(
    /* [IN] pointer to user ISR code */
    pointer isr
);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_int_enable
* Returned Value   : bitmask of new int enable state
* Comments         :
*    This function enables/disables RTC interrupts according to specified bitmask.
*
*END*********************************************************************/

extern uint_32 _rtc_int_enable 
(
    /* [IN] whether to enable or disable interrupts */
    boolean enable, 
    /* [IN] bitmask of affected interrupts */
    uint_32 bitmask
);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_isr
* Returned Value   : none
* Comments         :
*    This is template ISR for RTC module.
*
*END*********************************************************************/

extern void _rtc_isr 
(
    /* [IN] data pointer passed to interrupt */
    pointer ptr
);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_clear_requests
* Returned Value   : none
* Comments         :
*    This function clears RTC interrupt requests according to given bitmask.
*
*END*********************************************************************/

extern void _rtc_clear_requests 
(
    /* [IN] bitmask of affected interrupts */
    uint_32 bitmask
);

/*FUNCTION****************************************************************
* 
* Function Name    : _rtc_get_status
* Returned Value   : bitmask of actual RTC interrupt requests.
* Comments         :
*
*END*********************************************************************/

extern uint_32 _rtc_get_status 
(
    void
);
 
/*FUNCTION****************************************************************
* 
* Function Name    : _bsp_get_rtc_base_address
* Returned Value   : pointer to base of RTC registers
* Comments         :
*    This function returns base address of RTC related register space.
*
*END*********************************************************************/

extern pointer _bsp_get_rtc_base_address 
(
    void
);

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
);

#endif   /* __irtc_mcf5441x__ */

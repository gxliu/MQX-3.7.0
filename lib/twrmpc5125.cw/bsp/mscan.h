#ifndef _MSCAN_h_
#define _MSCAN_h_ 1
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
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
* $FileName: mscan.h$
* $Version : 3.6.6.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This include file is used to provide constant and structure definitions
*   specific to the MSCAN Serial Communications Controller
*   Revision History:
*   Feb.8/04    2.50          Initial version
*
*END************************************************************************/


/*********************************************************************
*
* MSCAN Module
*
*********************************************************************/
/*
** CAN commands
*/
#define CAN_TX                      (0xFF)
#define CAN_RX                      (0x00)
#define CAN_EXTENDED                (0xFF)
#define CAN_STANDARD                (0x00)
#define CAN_ENABLE                  (0xFF)
#define CAN_DISABLE                 (0x00)

/*
** MSCAN PIN selection
*/
#define MSCAN_TIMER_PIN             (0x10000000UL)
#define MSCAN_PSC2_PIN              (0x00000010UL)


/*
** MSCAN Mode selection
*/
#define MSCAN_INIT_MODE             (0x01)
#define MSCAN_SLEEP_MODE            (0x02)
#define MSCAN_WAKEUP_MODE           (0x04)
#define MSCAN_LISTEN_MODE           (0x10)
#define MSCAN_LOOPBACK_MODE         (0x20)
#define MSCAN_NORMAL_MODE           (0x80)

/*
** MSCAN Filtering mode
*/
#define MSCAN_FILTER_CLOSE          (0)
#define MSCAN_FILTER_8_BIT_MODE     (8)
#define MSCAN_FILTER_16_BIT_MODE    (16)
#define MSCAN_FILTER_32_BIT_MODE    (32)    

/*
** MSCAN RX Buffer Depth selection
*/
#define MSCAN_RX_NORMAL             (0)
#define MSCAN_RX_BUF_DEPTH          (1)

/*
** MSCAN time stamp
*/
#define MSCAN_WITHOUT_TIMESTAMP     (0)
#define MSCAN_WITH_TIMESTAMP        (1)

/*
** MSCAN TX buffers
*/
#define MSCAN_TX_BUFF1              (0)
#define MSCAN_TX_BUFF2              (1)
#define MSCAN_TX_BUFF3              (2)

/*
** MSCAN error codes
*/

#define MSCAN_OK                        (0)
#define ERR_MSCAN_INIT_FAILD                (MSCAN_ERROR_BASE | 0x001)
#define ERR_MSCAN_IN_INIT_ENABLE            (MSCAN_ERROR_BASE | 0x002)
#define ERR_MSCAN_INT_ENABLE_FAILED         (MSCAN_ERROR_BASE | 0x003)
#define ERR_MSCAN_INT_DISABLE_FAILED        (MSCAN_ERROR_BASE | 0x004)
#define ERR_MSCAN_INVALID_PIN               (MSCAN_ERROR_BASE | 0x005)
#define ERR_MSCAN_INVALID_ADDRESS           (MSCAN_ERROR_BASE | 0x006)
#define ERR_MSCAN_INVALID_DEVICE            (MSCAN_ERROR_BASE | 0x007)
#define ERR_MSCAN_INVALID_FREQUENCY         (MSCAN_ERROR_BASE | 0x008)
#define ERR_MSCAN_INVALID_FILTER            (MSCAN_ERROR_BASE | 0x009)
#define ERR_MSCAN_INVALID_MODE              (MSCAN_ERROR_BASE | 0x00A)
#define ERR_MSCAN_INVALID_BUFF_DEPTH        (MSCAN_ERROR_BASE | 0x00B)
#define ERR_MSCAN_INVAILD_DATA_LENGTH       (MSCAN_ERROR_BASE | 0x00C)
#define ERR_MSCAN_INVALID_TX_BUFF           (MSCAN_ERROR_BASE | 0x00D)
#define ERR_MSCAN_INVALID_TIMESTAMP         (MSCAN_ERROR_BASE | 0x00E)
#define ERR_MSCAN_TRANSMIT_BUS_OFF          (MSCAN_ERROR_BASE | 0x00F)
#define ERR_MSCAN_TRANSMIT_ERROR            (MSCAN_ERROR_BASE | 0x010)
#define ERR_MSCAN_TIMED_OUT                 (MSCAN_ERROR_BASE | 0x011)
#define ERR_MSCAN_BUSOFF                    (MSCAN_ERROR_BASE | 0x012)
#define ERR_MSACN_UNKNOWN_FORMAT            (MSCAN_ERROR_BASE | 0x013)
#define ERR_MSCAN_UNKNOWN_DIRECTION         (MSCAN_ERROR_BASE | 0x014)
#define ERR_MSCAN_UNKNOWN_ACCEPTANCE_MODE   (MSCAN_ERROR_BASE | 0x015)
#define ERR_MSCAN_NO_MESSAGE                (MSCAN_ERROR_BASE | 0x016)
#define ERR_MSCAN_WRONG_MSGFORMAT           (MSCAN_ERROR_BASE | 0x017)
#define ERR_MSACN_ID_MISMATCH               (MSCAN_ERROR_BASE | 0x018)
#define ERR_MSCAN_OUT_INIT_MODE             (MSCAN_ERROR_BASE | 0x019)
#define ERR_MSCAN_NO_TX_BUFF_AVAILABLE      (MSCAN_ERROR_BASE | 0x01A)
#define ERR_MSCAN_WAKEUP_MODE_DISABLE       (MSCAN_ERROR_BASE | 0x01B)
#define ERR_MSCAN_RX_OVERRUN                (MSCAN_ERROR_BASE | 0x01C)
#define ERR_MSCAN_CLK_INVALID               (MSCAN_ERROR_BASE | 0x01D)
#define ERR_MSCAN_FREQUENCY_TOO_HIGH        (MSCAN_ERROR_BASE | 0x01E)
#define ERR_MSCAN_FREQUENCY_TOO_LOW         (MSCAN_ERROR_BASE | 0x01F)

/*
** commands
*/
#define MSCAN_WITH_ERROR_COUNT      (1)
#define MSCAN_BUS_STATUS_DISABLE    (0)
#define MSCAN_BUS_STATUS_ENABLE     (1)
#define MSCAN_WITHOUT_WAKEUP        (0)
#define MSCAN_WITH_WAKEUP           (1)


#define MSCAN_WAIT_TIME             (0x90000000)
#define BUS_STATUS                  4


/*
** MSCAN commands
*/
#define MSCAN_CLEAR_RXFRM           (0x80)
#define MSCAN_RXF_VALUE             (0x01)

#define MSCAN_RJW_VALUE             (3)
#define MSCAN_SJW_VALUE             (MSCAN_RJW_VALUE - 1)
#define MSCAN_PRESCALER_VALUE       (0x0A) // for 500Kbps

#define MSCAN_CLOSE_FILTERING       (0x30)


typedef struct mscan_timing_param_struct {
   uint_32  BIT_RATE;
   uint_32  CLOCK_SOURCE; // Not used
   uint_32  SJW;
   uint_32  BRP;
   uint_32  SAMP;
   uint_32  TSEG1;
   uint_32  TSEG2;
} MSCAN_TIMING_PARAM_STRUCT, * MSCAN_TIMING_PARAM_STRUCT_PTR;


/*----------------------------------------------------------------------*/
/*
**                    FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

extern uint_32 mscan_init(pointer,uint_32,MSCAN_TIMING_PARAM_STRUCT_PTR);
extern uint_32 mscan_softreset(pointer);
extern uint_32 mscan_select_mode(pointer,uint_32,uint_32);
extern uint_32 mscan_start(pointer);
extern uint_32 mscan_filter_init(pointer,uint_32,uint_32,uint_32,uint_32,uint_32,uint_32);
extern uint_32 mscan_timestamp_select(pointer,uint_32);
extern uint_32 mscan_int_enable(pointer);
extern uint_32 mscan_int_disable(pointer);
extern uint_32 mscan_int_init(pointer, pointer);
extern void    mscan_isr(pointer);
extern uint_32 mscan_wakeup_int_enable(pointer);
extern uint_32 mscan_rx_message(pointer,pointer,uint_32_ptr,uint_32_ptr,uint_32,uint_32_ptr,uint_32);
extern uint_32 mscan_tx_message(pointer,pointer,uint_32,uint_32,uint_32,uint_32,uint_32);
extern uint_32 mscan_abort_message(pointer);
extern uint_32 mscan_request_message(pointer,uint_32);
extern uint_32 mscan_error_int_enable(pointer,uint_32);
extern uint_32 mscan_write(pointer,uint_32,uint_32);
extern uint_32 mscan_read(pointer,uint_32,uint_32_ptr);
#ifdef __cplusplus
}
#endif

#endif

/* EOF */

#ifndef _smpc5125_h_
#define _smpc5125_h_ 1
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $FileName: serl_mpc5125.h$
* $Version :  3.6.2.0$
* $Date    :  Dec-3-2010$
*
* Comments:
*   This include file is used to provide information needed by
*   an application program using a Motorola Programmable Serial
*   controller (as defined for the MPC5125).
*
*
*END************************************************************************/


/*--------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* Standard parity definitions */
#define IO_SERIAL_NO_PARITY    1
#define IO_SERIAL_EVEN_PARITY  2
#define IO_SERIAL_ODD_PARITY   3

/* Standard stop bit definitions */
#define IO_SERIAL_1_STOP_BIT    1
#define IO_SERIAL_1_5_STOP_BITS 2
#define IO_SERIAL_2_STOP_BITS   3


/*
** MPC5125 SERIAL INIT STRUCT
**
** This structure defines what the UART initialization record contains
*/
typedef struct mpc5125_serial_init_struct
{
   // The com port offset from MBAR
   uint_32   DEVICE;

   // The serial I/O queue size to use to buffer Rx/Tx data.
   _mqx_uint QUEUE_SIZE;

   // Uart device driver Tx/Rx alarm settings for RxRDY/TxRDY.
   _mqx_uint RX_QUEUE_ALARM;
   _mqx_uint TX_QUEUE_ALARM;

   // The baud rate for the channel
   uint_32   BAUD_RATE;

   // The number of bits in a character
   _mqx_uint BITS_PER_CHARACTER;

   // The parity to initialize the channel to
   _mqx_uint PARITY;

   // The number of stop bits
   _mqx_uint STOP_BITS;

   // The Clock speed to the uart
   uint_32   (_CODE_PTR_ CLOCK_SPEED)(void);
} MPC5125_SERIAL_INIT_STRUCT, _PTR_ MPC5125_SERIAL_INIT_STRUCT_PTR;


/*
** MPC5125_SERIAL_INFO_STRUCT
** Run time state information for the serial channel
*/
typedef struct mpc5125_serial_info_struct
{
   // Current initialized values
   MPC5125_SERIAL_INIT_STRUCT  INIT;

   // Pointer to uart registers
   MPC5125_PSC_STRUCT_PTR UART_PTR;

   // Internal driver interrupt state
   uint_32                   VECTOR;

   /* The previous interrupt handler and data */
   void          (_CODE_PTR_ OLD_ISR)(pointer);
   void          (_CODE_PTR_ OLD_ISR_EXCEPTION_HANDLER)(_mqx_uint, _mqx_uint,
      pointer, pointer);
   pointer                   OLD_ISR_DATA;

   uint_32                   CONTROL_BITS;

   /* Statistical information */
   uint_32                   INTERRUPTS;
   uint_32                   RX_DROPPED_INPUT;
   uint_32                   RX_GOOD_CHARS;
   uint_32                   RX_CHARS;
   uint_32                   TX_CHARS;
   uint_32                   RX_PARITY_ERRORS;
   uint_32                   RX_FRAMING_ERRORS;
   uint_32                   RX_OVERRUNS;
   uint_32                   RX_BREAKS;

} MPC5125_SERIAL_INFO_STRUCT, _PTR_ MPC5125_SERIAL_INFO_STRUCT_PTR;


/*--------------------------------------------------------------------------*/
/*
**                        FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

/* Polled driver functions */
extern uint_32 _mpc5125_serial_polled_install(char_ptr,
   const MPC5125_SERIAL_INIT_STRUCT _PTR_);

/* Polled driver functions */
extern uint_32 _mpc5125_serial_int_install(char_ptr,
   const MPC5125_SERIAL_INIT_STRUCT _PTR_);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

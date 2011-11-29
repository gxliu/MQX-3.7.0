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
* $FileName: serl_mcf51xx.h$
* $Version : 3.6.9.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for the sci drivers for the MCF51XX
*
*END************************************************************************/
#ifndef _serial_mcf51xx_h_h
#define _serial_mcf51xx_h_h

#ifdef __cplusplus
extern "C" {
#endif

#include "mcf51xx_sci.h"

/*--------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/*
** I/O Initialization error codes
*/
#define MCF51XX_IO_INVALID_CHANNEL        (0x10000)

/* Initialization values for the DEVICE field of the IO_INIT_STRUCT */
/* Channel number for Serial port 1 */
#define MCF51XX_SCI0                  (0)
/* Channel number for Serial port 2 */
#define MCF51XX_SCI1                  (1)
/* Channel number for Serial port 3 */
#define MCF51XX_SCI2                  (2)



/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

/*
** MCF51XX_SCI_INIT_STRUCT
**
** This structure defines the initialization parameters to be used
** when a serial port is initialized.
*/
typedef struct mcf51xx_sci_init_struct
{

   /* The size of the queues to buffer incoming/outgoing data */
   uint_32 QUEUE_SIZE;

   /* The device to initialize */
   uint_32 DEVICE;

   /* The clock speed of cpu */
   uint_32 CLOCK_SPEED;

   /* The value for the SCIxC1 1 register */
   uint_8 SCIC1_VALUE;

   /* The value for the SCIxC2 2 register */
   uint_8 SCIC2_VALUE;

   /* The value for the SCIxC3 3 register */
   uint_8 SCIC3_VALUE;

   /* The baud rate for the channel */
   uint_32 BAUD_RATE;
   
   /* RX interrupt vector */
   uint_32 RX_VECTOR;
   
   /* TX interrupt vector */
   uint_32 TX_VECTOR;
   
   /* ERROR interrupt vector */
   uint_32 ER_VECTOR;

} MCF51XX_SCI_INIT_STRUCT, _PTR_ MCF51XX_SCI_INIT_STRUCT_PTR;
typedef const MCF51XX_SCI_INIT_STRUCT _PTR_ MCF51XX_SCI_INIT_STRUCT_CPTR;

/*
** MCF51XX_SCI_INFO_STRUCT
** Run time state information for each serial channel
*/
typedef struct mcf51xx_sci_info_struct
{
   /* The current init values for this port */
   MCF51XX_SCI_INIT_STRUCT          INIT;

   /* The sci device register */
   MCF51XX_SCI_STRUCT_PTR           SCI_PTR;

   /* The previous interrupt handler and data */
   void       (_CODE_PTR_ OLD_ISR)(pointer);
   void       (_CODE_PTR_ OLD_ISR_EXCEPTION_HANDLER)(uint_32, uint_32, pointer,
               pointer);
   pointer                           OLD_ISR_DATA;

   /* Statistical information */
   uint_32                           INTERRUPTS;
   uint_32                           RX_CHARS;
   uint_32                           TX_CHARS;
   uint_32                           RX_BREAKS;
   uint_32                           RX_PARITY_ERRORS;
   uint_32                           RX_FRAMING_ERRORS;
   uint_32                           RX_OVERRUNS;
   uint_32                           RX_DROPPED_INPUT;
   uint_32                           RX_NOISE_ERRORS;
} MCF51XX_SCI_INFO_STRUCT, _PTR_ MCF51XX_SCI_INFO_STRUCT_PTR;

/*--------------------------------------------------------------------------*/
/*
**                        FUNCTION PROTOTYPES
*/

extern uint_32 _mcf51xx_sci_polled_init(MCF51XX_SCI_INIT_STRUCT_PTR, pointer _PTR_,char _PTR_);
extern uint_32 _mcf51xx_sci_polled_install(char_ptr, MCF51XX_SCI_INIT_STRUCT_CPTR, uint_32);
extern uint_32 _mcf51xx_sci_int_install(char_ptr, MCF51XX_SCI_INIT_STRUCT_CPTR, uint_32);
extern pointer _bsp_get_serial_base_address(uint_8);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

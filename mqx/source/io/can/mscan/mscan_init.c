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
* $FileName: mscan_init.c$
* $Version : 3.6.6.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>


/* Global variables */
static boolean request_flag[MSCAN_DEVICES] = {0}; //Remote frame request


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_wait  
* Returned Value   : uint_32 (Error code) 
* Comments         :
*    This function resets the MSCAN device by bring it into the sleep mode
*    and then initialization mode.     
*
*END*------------------------------------------------------------------------*/

static boolean mscan_wait( VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr, uint_32 mode, uint_32 wait_time)
{

   while( (wait_time > 0) && ((mscan_reg_ptr->CANCTL1 & mode) != mode) ) {
      wait_time--;
   }
   return (wait_time>=0);
   if(wait_time < 0) {
   }
   return TRUE;
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_softreset  
* Returned Value   : uint_32 (Error code) 
* Comments         :
*    This function resets the MSCAN device by bring it into the sleep mode
*    and then initialization mode.     
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_softreset
   (
      /* [IN] MSCAN base address */
      pointer mscan_addr
   )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   }
      
   /* Bring the MSCAN into Sleep Mode */
   mscan_reg_ptr->CANCTL0 = MSCAN_SLEEP_MODE;
   if (!mscan_wait(mscan_reg_ptr,MSCAN_SLEEP_MODE,MSCAN_WAIT_TIME)) {
      return (ERR_MSCAN_TIMED_OUT);
   }

   /* Bring the MSCAN into initialization mode */
   mscan_reg_ptr->CANCTL0 = MSCAN_INIT_MODE;
   if (!mscan_wait(mscan_reg_ptr,MSCAN_INIT_MODE,MSCAN_WAIT_TIME)) {
      return (ERR_MSCAN_TIMED_OUT);
   }
   
   return MSCAN_OK;
}



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_init  
* Returned Value   : uint_32 (Error code) 
* Comments         :
*    This function initializes the MSCAN device by bring it into the 
*    initialization mode and program the bit timing registers, enabling 
*    device in normal mode operation and selecting clock source.
*
*END*------------------------------------------------------------------------*/
uint_32 mscan_init
   (
   /* [IN] MSCAN base address */
   pointer  mscan_addr,
   uint_32                       bit_rate,
   MSCAN_TIMING_PARAM_STRUCT_PTR in_params_ptr )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   uint_32                 mscan_dev = mscan_device_num(mscan_reg_ptr);
   
   /* Validate MSCAN module */
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)){
      return (ERR_MSCAN_INVALID_ADDRESS);
   }
   

   // Enable MSCAN pins
   _bsp_mscan_io_init(mscan_dev);
   
   request_flag[mscan_dev] = FALSE;
   
   /* 
   ** Enter initialization Mode 
   ** Check for initialization mode request bit and 
   ** initialization mode ack bit
   */
   mscan_reg_ptr->CANCTL0 = MSCAN_INIT_MODE;
   if (!mscan_wait(mscan_reg_ptr,MSCAN_INIT_MODE,MSCAN_WAIT_TIME)) {
      return (ERR_MSCAN_TIMED_OUT);
   }

   /* Clear RXFRM bit */
   mscan_reg_ptr->CANCTL0 |= MSCAN_CLEAR_RXFRM;
   
   /* Enable MSCAN in normal mode */
   mscan_reg_ptr->CANCTL1 = MSCAN_NORMAL_MODE;
   
   
   /* Select and Enable MSCAN clock */
   return mscan_init_clocks_and_bit_timing(mscan_reg_ptr,mscan_dev,bit_rate, in_params_ptr);
}



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_select_mode
* Returned Value   : uint_32 (Error code)
* Comments         :
*               This function selects the MSCAN operation mode and 
*               enable/disable the MSCAN interrupt. It will overwrite 
*               the operation mode, which is been set in device initialization 
*               function. If normal operation mode will be used, this function
*               can be replaced with mscan_int_enable().
*
*END*------------------------------------------------------------------------*/

uint_32 mscan_select_mode
   (
  /* [IN] MSCAN_base address */
  pointer mscan_addr,
  /* [IN] mode */
  uint_32 mode,
  /* [IN] enable/disable interrupt */
  uint_32 int_enable
   )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   
   /* Validate MSCAN module */
   if (!mscan_validate_address((uint_32)mscan_reg_ptr))
      return (ERR_MSCAN_INVALID_ADDRESS);

   /* Check for initilization mode */
   if( (mscan_reg_ptr->CANCTL1 & MSCAN_INIT_MODE) != MSCAN_INIT_MODE )  
      return (ERR_MSCAN_OUT_INIT_MODE);
 
   /* Enable MSCAN interrupt */
   if(int_enable == CAN_ENABLE){
      if(mscan_int_enable(mscan_addr) != MSCAN_OK) {
         return (ERR_MSCAN_INT_ENABLE_FAILED);
      }
   } else if (int_enable == CAN_DISABLE){
      if (mscan_int_disable(mscan_addr) != MSCAN_OK) {
         return (ERR_MSCAN_INT_DISABLE_FAILED);
      }
   }
      
   /* Select MSCAN mode */
   switch (mode)
   {
      case MSCAN_WAKEUP_MODE:
         /* MSCAN wakeup enable */
         mscan_reg_ptr->CANCTL0 |= MSCAN_WAKEUP_MODE;
         /* Set WUPE bit (wakeup CPU after any recessive to dominant edge on the CAN bus) */
         mscan_reg_ptr->CANCTL1 &= ~(MSCAN_WAKEUP_MODE); 
         break;

      case MSCAN_LISTEN_MODE:
         /* MSCAN is listen only mode (bus monitoring) */
         mscan_reg_ptr->CANCTL1 |= MSCAN_LISTEN_MODE;
         break;

      case MSCAN_NORMAL_MODE:
         /* MSCAN normal mode */
         mscan_reg_ptr->CANCTL1 |= MSCAN_NORMAL_MODE;
         break;

      case MSCAN_LOOPBACK_MODE:
         /* MSCAN loop back mode (self test) */
         mscan_reg_ptr->CANCTL1 |= MSCAN_LOOPBACK_MODE;
         break;

      case MSCAN_SLEEP_MODE:
         /* MSCAN sleep mode request */
         mscan_reg_ptr->CANCTL0 |= MSCAN_SLEEP_MODE;
         if (!mscan_wait(mscan_reg_ptr,MSCAN_SLEEP_MODE,MSCAN_WAIT_TIME)) {
            return (ERR_MSCAN_TIMED_OUT);
         }
         break;

      default:
         return (ERR_MSCAN_INVALID_MODE);
   }

   return MSCAN_OK;  
}



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_filter_init
* Returned Value   : uint_32 (Error code)
* Comments         : 
*    filter bank 1: IDAR 0-3, IDMR 0-3
*    filter bank 2  IDAR 4-7, IDMR 4-7
*    --------------------------------------------------------------------
*    First bank:
*    32 bits mode : 2 hits: (hit0 ID (IDR 0-3))
*    16 bits mode : 4 hits: (hit0 ID (IDR 0 & IDR 1), hit1 (IDR2 & IDR3))
*     8 bits mode : 8 hits: (hit0 ID (IDR 0), hit1 (IDR1), hit2 (IDR2), 
*                           hit3 (IDR3))
*    Same for second bank, therefore 32bits mode results in 2 hits and 
*    16 bits mode results in 4 hits and 8 bits mode results in 8 hits.
*
*END*------------------------------------------------------------------------*/
uint_32 mscan_filter_init
   (
   /* [IN] MSCAN base address */
   pointer mscan_addr, 
   /* [IN] acceptance mode (8, 16, 32 bit or filter close) */
   uint_32 mode,
   /* [IN] acceptance Code (filter bank 1) applied to IDAR 0-3 */
   uint_32 filter1,
   /* [IN] acceptance Code (filter bank 2) applied to IDAR 4-7 */
   uint_32 filter2,
   /* [IN] ID Mask (mask bank 1) applied to IDMR 0-3 */
   uint_32 mask1,
   /* [IN] ID Mask (mask bank 2) applied to IDMR 4-7 */
   uint_32 mask2,
   /* [IN] message format (CAN_STANDARD OR CAN_EXTENDED) */
   uint_32 format
   )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;

    /* Validate MSCAN module */
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   }
   
   
   /* Check for initilization mode */
   if( (mscan_reg_ptr->CANCTL1 & MSCAN_INIT_MODE) != MSCAN_INIT_MODE ) {
      return ERR_MSCAN_OUT_INIT_MODE;
   }
   
   switch (mode)
   {
      case (MSCAN_FILTER_CLOSE):
       mscan_reg_ptr->CANIDAC = 0x30;
       return (MSCAN_OK);   
      case (MSCAN_FILTER_8_BIT_MODE):
         mscan_reg_ptr->CANIDAC = 0x20;
       break;
      case (MSCAN_FILTER_16_BIT_MODE):
         mscan_reg_ptr->CANIDAC = 0x10;
       break;
      case (MSCAN_FILTER_32_BIT_MODE):
       mscan_reg_ptr->CANIDAC = 0x00;
       break;
      default:
       return (ERR_MSCAN_UNKNOWN_ACCEPTANCE_MODE);
   }

   /* First bank */
   mscan_reg_ptr->CANIDAR3 = (uint_8)(filter1 & 0x000000FF);
   mscan_reg_ptr->CANIDAR2 = (uint_8)((filter1 & 0x0000FF00) >> 8);
   mscan_reg_ptr->CANIDAR1 = (uint_8)((filter1 & 0x00FF0000) >> 16);
   mscan_reg_ptr->CANIDAR0 = (uint_8)((filter1 & 0xFF000000) >> 24);
   mscan_reg_ptr->CANIDMR3 = (uint_8)(mask1 & 0x000000FF);
   mscan_reg_ptr->CANIDMR2 = (uint_8)((mask1 & 0x0000FF00) >> 8);
   mscan_reg_ptr->CANIDMR1 = (uint_8)((mask1 & 0x00FF0000) >> 16);
   mscan_reg_ptr->CANIDMR0 = (uint_8)((mask1 & 0xFF000000) >> 24);
   /* Second bank */
   mscan_reg_ptr->CANIDAR7 = (uint_8)(filter2 & 0x000000FF);
   mscan_reg_ptr->CANIDAR6 = (uint_8)((filter2 & 0x0000FF00) >> 8);
   mscan_reg_ptr->CANIDAR5 = (uint_8)((filter2 & 0x00FF0000) >> 16);
   mscan_reg_ptr->CANIDAR4 = (uint_8)((filter2 & 0xFF000000) >> 24);
   mscan_reg_ptr->CANIDMR7 = (uint_8)(mask2 & 0x000000FF);
   mscan_reg_ptr->CANIDMR6 = (uint_8)((mask2 & 0x0000FF00) >> 8);
   mscan_reg_ptr->CANIDMR5 = (uint_8)((mask2 & 0x00FF0000) >> 16);
   mscan_reg_ptr->CANIDMR4 = (uint_8)((mask2 & 0xFF000000) >> 24);

   /* 
   ** To receive standard messages in 32-bit filter mode, the last three bits (AM[0:2])
   ** of CANIDMR1, CANIDMR5 registers must be programmed as "don’t care.
   ** To receive standard messages in 16-bit filter mode, the last three bits (AM[0:2])
   ** of CANIDMR1, CANIDMR3, CANIDMR5, CANIDMR7 registers must be programmed as "don’t care.
   */
   if(format == CAN_STANDARD) {
      if( (mode == MSCAN_FILTER_32_BIT_MODE) || (mode == MSCAN_FILTER_16_BIT_MODE) ){
          mscan_reg_ptr->CANIDMR1 |= 0x07;
           mscan_reg_ptr->CANIDMR5 |= 0x07;
       }
       if(mode == MSCAN_FILTER_16_BIT_MODE){
          mscan_reg_ptr->CANIDMR3 |= 0x07;
           mscan_reg_ptr->CANIDMR7 |= 0x07;
       }
   } 
   
   /* MPC5200 ERRATA for MSCAN extended messages */
   if(format == CAN_EXTENDED){
      if( (mode == MSCAN_FILTER_32_BIT_MODE) || (mode == MSCAN_FILTER_16_BIT_MODE) ){
          mscan_reg_ptr->CANIDMR1 |= 0xF1;
           mscan_reg_ptr->CANIDMR5 |= 0xF1;
       }
       if(mode == MSCAN_FILTER_16_BIT_MODE){
          mscan_reg_ptr->CANIDMR3 |= 0xF1;
           mscan_reg_ptr->CANIDMR7 |= 0xF1;
       }
   } 

   return MSCAN_OK;
}



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_request_message
* Returned Value   : uint_32 (Error Code)
* Comments         :
*                  This function will set the RTR bit for sending a remote
*                  frame. Message buffer becomes receive mailbox after 
*                  sending remote frame. This function should be called
*                  befor mscan_tx_message(). Global variable request_flag
*                  will be set to TRUE ewhich will be checked by 
*                  mscan_tx_message() function.
*
*END*------------------------------------------------------------------------*/
uint_32 mscan_request_message
    (
    /* [IN] MSCAN base address */
    pointer mscan_addr,
    /* [IN] message format */
    uint_32 format
    )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   uint_32                 mscan_dev = mscan_device_num(mscan_reg_ptr);

   /* Validate MSCAN module */
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   }
   
   /* Set RTR bit for remote frame based on message format */
   if(format == CAN_EXTENDED) {
      mscan_reg_ptr->CANTXFG.IDR3 = 0x01; 
   } else if(format == CAN_STANDARD) {
      mscan_reg_ptr->CANTXFG.IDR1 = 0x10;
   } else {
      return (ERR_MSACN_UNKNOWN_FORMAT);
   }
   
   /* Set the request flag (global variable) */
   request_flag[mscan_dev] = TRUE;

   return (MSCAN_OK);
}



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_start  
* Returned Value   : uint_32 (Error Code)
* Comments         :
*               This function takes the MSCAN device out of initialization
*               mode and synchronizes it with the bus.     
*
*END*------------------------------------------------------------------------*/
uint_32 mscan_start
    (
    /* [IN] MSCAN base address */
    pointer mscan_addr
    )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   uint_32                  wait_time = MSCAN_WAIT_TIME;
   
   /* Validate MSCAN module */
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   }
   
   /* Check for initilization mode */
   if( (mscan_reg_ptr->CANCTL1 & MSCAN_INIT_MODE) != MSCAN_INIT_MODE ) {
      return ERR_MSCAN_OUT_INIT_MODE;
   }
   
   /* MSCAN synchronized to the CAN bus. */
   mscan_reg_ptr->CANCTL0 &= ~(MSCAN_INIT_MODE);
   
   /* Exit MSCAN from initilization mode */
   while ((wait_time > 0) && ((mscan_reg_ptr->CANCTL1 & MSCAN_INIT_MODE) != 0x00)) {
      wait_time--;
   }
   
   if(wait_time < 0) {
      return ERR_MSCAN_TIMED_OUT;
   }
   
   return MSCAN_OK;    
}





/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_rx_message
* Returned Value   : uint_32 (Error Code)
* Comments         :  
*       Receive buffer: SRR does not have to be set to 1
*       This function checks receive buffer full flag, if set, then 
*       assembles the ID and stores data, ID, hit filter and data lenght 
*       to the parameters provided by the application. 
*       If interrupt is disabled, then clears receive buffer full flag 
*       and received frame flag to release message buffer (unlock it).
*     
*
*END*------------------------------------------------------------------------*/
uint_32 mscan_rx_message
    (
   /* [IN] MSCAN base address */
   pointer     mscan_addr,
   /* [IN/OUT] Location to store the data */
   pointer     data_ptr,
   /* [IN/OUT] message ID */
   uint_32_ptr identifier,     
   /* [IN/OUT] number of bytes read from message buffer (0 to 8) */ 
   uint_32_ptr data_len_code,
   /* [IN] message format (CAN_STANDARD OR CAN_EXTENDED) */ 
   uint_32     format,
   /* [IN/OUT] Identifier Acceptance Hit Indicator */
   uint_32_ptr filter_hit,
   /* [IN] interrupt enable/disable */
   uint_32     int_enable
    )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   vuint_32                    ID, temp;
   
   /* Validate MSCAN module */
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)){
      return (ERR_MSCAN_INVALID_ADDRESS);
   }

   if ( ((mscan_reg_ptr->CANRFLG & MSCAN_RXF_VALUE) == MSCAN_RXF_VALUE) ||
        ((mscan_reg_ptr->CANCTL0 & MSCAN_CLEAR_RXFRM) == MSCAN_CLEAR_RXFRM) ||
        ((mscan_reg_ptr->CANCTL1 & MSCAN_LOOPBACK_MODE) == MSCAN_LOOPBACK_MODE) )
   {
      /* Assemble the ID according to format structure */
      if ( format == CAN_EXTENDED ) {
         /* ID[6-0] */
         temp = mscan_reg_ptr->CANRXFG.IDR3;
         /* ID[14-7] */
         temp |= (mscan_reg_ptr->CANRXFG.IDR2 << 8 );
         /* ID[17-15] and ID[20-18] */
         temp |= (mscan_reg_ptr->CANRXFG.IDR1 << 16);
         /* ID[28-21] */
         temp |= (mscan_reg_ptr->CANRXFG.IDR0 << 24);
         temp = temp >> 1;
         /* IDR3 & IDR2 */
         ID = temp & 0xFFFF;
         /* IDR0 */
         ID |= (temp >> 2) & 0xFF000000;
         /* IDR1 */
         temp &= 0xFFF30000;
         ID |= temp & 0xF0000;
         ID |= (temp >> 2) & 0xFC0000;
      } else if(format == CAN_STANDARD) {
         /* ID[0-2] */
         ID = mscan_reg_ptr->CANRXFG.IDR1;
         /* ID[3-10] */
         ID |= (mscan_reg_ptr->CANRXFG.IDR0 << 8);
          ID = ID >> 5;
      } else {
         return ERR_MSCAN_WRONG_MSGFORMAT;
      }

      /* Set the identifier for returning to the application */
      *identifier = ID;

      /* Copy stored data to buffer */
      ((uchar_ptr)data_ptr)[0] = mscan_reg_ptr->CANRXFG.DSR0;
      ((uchar_ptr)data_ptr)[1] = mscan_reg_ptr->CANRXFG.DSR1;
      ((uchar_ptr)data_ptr)[2] = mscan_reg_ptr->CANRXFG.DSR2;
      ((uchar_ptr)data_ptr)[3] = mscan_reg_ptr->CANRXFG.DSR3;
      ((uchar_ptr)data_ptr)[4] = mscan_reg_ptr->CANRXFG.DSR4;
      ((uchar_ptr)data_ptr)[5] = mscan_reg_ptr->CANRXFG.DSR5;
      ((uchar_ptr)data_ptr)[6] = mscan_reg_ptr->CANRXFG.DSR6;
      ((uchar_ptr)data_ptr)[7] = mscan_reg_ptr->CANRXFG.DSR7;

      /* Clear data stored into the MB */
      mscan_reg_ptr->CANRXFG.DSR0 = 0x00;
      mscan_reg_ptr->CANRXFG.DSR1 = 0x00;
      mscan_reg_ptr->CANRXFG.DSR2 = 0x00;
      mscan_reg_ptr->CANRXFG.DSR3 = 0x00;
      mscan_reg_ptr->CANRXFG.DSR4 = 0x00;
      mscan_reg_ptr->CANRXFG.DSR5 = 0x00;
      mscan_reg_ptr->CANRXFG.DSR6 = 0x00;
      mscan_reg_ptr->CANRXFG.DSR7 = 0x00;

      /* Identifier Acceptance Hit Indicator */
      *filter_hit = (mscan_reg_ptr->CANIDAC & 0x07);
   
      /* Set the data length code */
      *data_len_code = (mscan_reg_ptr->CANRXFG.DLR & 0x0F);
   
   } else {
      return ERR_MSCAN_NO_MESSAGE;
   }

   /*
   ** Clear the RXF and RXFRM to indicate this buffer is empty (released) 
   ** Polling mode.
   */
   if (int_enable == CAN_DISABLE) {
      mscan_reg_ptr->CANRFLG |= MSCAN_RXF_VALUE;
      mscan_reg_ptr->CANCTL0 |= MSCAN_CLEAR_RXFRM;
   }

   return MSCAN_OK;
}



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_tx_message  
* Returned Value   : uint_32
* Comments         :
*           This function find the first available Tx buffer and set it up
*           as foreground Tx buffer. 
*           Then sets the ID, DLC, message format and priority of the 
*           message. Copy the data into the message buffer and clears the 
*           transmitter buffer empty flag to transmit the message.
*        -----------------------------------------------------------------
*           If remote frame is needed to be transmitted, then 
*           mscan_request_message() function need to be called before 
*           mscan_tx_message(). mscan_tx_message() function checks for  
*           the global variable request_flag, if its set then OR the ID  
*           to the appropriate Identifier Register and unset the global
*           variable. That means, each remote frame needs a function 
*           call to set the RTR bit before sending it.
*
*END*------------------------------------------------------------------------*/
uint_32 mscan_tx_message
    (
   /* [IN] MSCAN base address */
   pointer mscan_addr,
   /* [IN] Pointer to stored data */
   pointer data_ptr,
   /* [IN] priority of the message */
   uint_32 priority,
   /* [IN] message ID */
   uint_32 identifier,     
   /* [IN] number of bytes to write to the mailbox (0 to 8) */ 
   uint_32 data_len_code,
   /* [IN] message format (CAN_STANDARD OR CAN_EXTENDED) */ 
   uint_32 format,
   /* [IN] interrupt enable/disable */
   uint_32 int_enable
    )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   uint_32                 mscan_dev = mscan_device_num(mscan_reg_ptr);
   uint_32                     result;
   vuint_8                  tx_buff;
   uint_8                  mask;
      
   /* Validate MSCAN module */
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)){
      return (ERR_MSCAN_INVALID_ADDRESS);
   }
   
   /* check to see which transmit buffer is empty and set it up as TXFG buffer */
   for (tx_buff=MSCAN_TX_BUFF1;tx_buff<=MSCAN_TX_BUFF3;tx_buff++) {
      mask = 1<<tx_buff;
      if (mscan_reg_ptr->CANTFLG & mask) {
         // buffer is empty
         if (!(mscan_reg_ptr->CANTIER & mask)) {
            // interrupt is not enabled, so buffer not in use - use it
            mscan_reg_ptr->CANTBSEL = mask;
            break;
         }
      }
   }
   
   if (tx_buff>MSCAN_TX_BUFF3) {
      return (ERR_MSCAN_NO_TX_BUFF_AVAILABLE);
   }

   
   /* Set the ID according the format structure */
   if ( format == CAN_EXTENDED ) {
      /* 29 bit ID Data frame */
      identifier = (identifier & 0x1FFFFFFF) << 1;
      /* ID[6-0] and RTR */
       if(!request_flag[mscan_dev]) {
         mscan_reg_ptr->CANTXFG.IDR3 = (uint_8)(identifier & 0x000000FF);
       } else {
          mscan_reg_ptr->CANTXFG.IDR3 |= (uint_8)(identifier & 0x000000FF);
       }
      /* ID[14-7] */
      mscan_reg_ptr->CANTXFG.IDR2 = (uint_8)( (identifier & 0x0000FF00) >> 8 );
      /* ID[17-15] */
      mscan_reg_ptr->CANTXFG.IDR1 = (uint_8)( ((identifier & 0x00FF0000) >> 16) & 0x07 );
       /* ID[20-18] */
       mscan_reg_ptr->CANTXFG.IDR1 |= (uint_8)( (((identifier & 0x00FF0000) >> 16) << 2) & 0xE0 );
      /* IDE and SRR */
      mscan_reg_ptr->CANTXFG.IDR1 |= 0x18;
      /* ID[28-21] */
       mscan_reg_ptr->CANTXFG.IDR0 = (uint_8)( ((identifier << 2 ) & 0xFF000000) >> 24 );
   } else if(format == CAN_STANDARD) {
       /* 11 bit ID Data frame */
      identifier = (identifier & 0x7FF) << 5;
      /* ID[0-2] set the IDE for standard format and RTR */
       if(!request_flag[mscan_dev]) {
         mscan_reg_ptr->CANTXFG.IDR1 = (uint_8)(identifier & 0xFF);
       } else {
         mscan_reg_ptr->CANTXFG.IDR1 |= (uint_8)(identifier & 0xFF);
       }
      /* ID[3-10] */
      mscan_reg_ptr->CANTXFG.IDR0 = (uint_8)( (identifier & 0xFF00) >> 8 );
   } else {
      return (ERR_MSACN_UNKNOWN_FORMAT);
   }

   /* Set the data length code */
   if(0 >= data_len_code >= 8) {
      return (ERR_MSCAN_INVAILD_DATA_LENGTH);
   } else {
      mscan_reg_ptr->CANTXFG.DLR = (vuint_8)data_len_code;
   }
   
   if(!request_flag[mscan_dev]) {
      /* Copy data to transmit */
      mscan_reg_ptr->CANTXFG.DSR0 = ((uchar_ptr)data_ptr)[0];
      mscan_reg_ptr->CANTXFG.DSR1 = ((uchar_ptr)data_ptr)[1];
      mscan_reg_ptr->CANTXFG.DSR2 = ((uchar_ptr)data_ptr)[2];
      mscan_reg_ptr->CANTXFG.DSR3 = ((uchar_ptr)data_ptr)[3];
      mscan_reg_ptr->CANTXFG.DSR4 = ((uchar_ptr)data_ptr)[4];
      mscan_reg_ptr->CANTXFG.DSR5 = ((uchar_ptr)data_ptr)[5];
      mscan_reg_ptr->CANTXFG.DSR6 = ((uchar_ptr)data_ptr)[6];
      mscan_reg_ptr->CANTXFG.DSR7 = ((uchar_ptr)data_ptr)[7];
   } 

   /* Set priority of the message*/
   mscan_reg_ptr->CANTXFG.TBPR = (vuint_8)priority;

   request_flag[mscan_dev] = FALSE;
          
   // Clear the flag (by writing 1) to indicate this buffer is full 
   mscan_reg_ptr->CANTFLG = mask;
    // enable the interrupt 
   if (int_enable == CAN_ENABLE) {
      mscan_reg_ptr->CANTIER |= mask;
   }

   return MSCAN_OK;
}



/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : mscan_abort_message  
* Returned Value   : uint_32
* Comments         :
*           This function aborts all pending messages in Tx buffers.
*
*
*END*------------------------------------------------------------------------*/
uint_32 mscan_abort_message
    (
   /* [IN] MSCAN base address */
   pointer mscan_addr
    )
{
   VMSCAN_REG_STRUCT_PTR    mscan_reg_ptr = (VMSCAN_REG_STRUCT_PTR) mscan_addr;
   uint_32                  wait_time = MSCAN_WAIT_TIME;
      
   /* Validate MSCAN module */
   if (!mscan_validate_address((uint_32)mscan_reg_ptr)) {
      return (ERR_MSCAN_INVALID_ADDRESS);
   }

   /* Abort all messages in transmit buffer */
   mscan_reg_ptr->CANTARQ = 0x07;

   /* Wait for abort acknowledge */
   while ((wait_time > 0) && ((mscan_reg_ptr->CANTAAK & 0x07) != 0x07))  {
      wait_time--;
   }
   
      
   if(wait_time < 0) {
      return ERR_MSCAN_TIMED_OUT;
   }
   
   return (MSCAN_OK);

}

/* EOF */
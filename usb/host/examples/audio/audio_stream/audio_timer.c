/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
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
 **************************************************************************//*!
 *
 * @file audio_timer.c
 *
 * @author
 *
 * @version
 *
 * @date    
 *
 * @brief   
 *          
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <string.h>
#include "types.h"          /* Contains User Defined Data Types */
#include "audio.h"
#include "audio_timer.h"

/******************************************************************************
 * Local functions
 *****************************************************************************/
#if (defined BSP_TWRMCF51JE)
static void ClearCmtInterrupt(void);
void cmt_init_freq(uint_32 period);
void EnableCmtInterrupt(void);
void DisableCmtInterrupt(void);
#endif

/******************************************************************************
 * Global functions
 *****************************************************************************/
void audio_timer_init(void);
void AUDIO_TIMER_ISR(void);
extern void usb_host_audio_tr_callback(_usb_pipe_handle ,pointer ,uchar_ptr ,uint_32 ,uint_32 );

/******************************************************************************
 * Global variable
 *****************************************************************************/
extern volatile AUDIO_CONTROL_DEVICE_STRUCT audio_control;
extern volatile AUDIO_STREAM_DEVICE_STRUCT audio_stream;

extern uint_8 wav_buff[MAX_ISO_PACKET_SIZE];
extern uint_8 wav_recv_buff[MAX_ISO_PACKET_SIZE];
extern uint_8 wav_recv_buff_tmp[MAX_ISO_PACKET_SIZE];
extern uint_8 device_direction;
extern uint_32 packet_size;
extern LWEVENT_STRUCT USB_Event;
#if (defined BSP_TWRMCF51JE) 
extern volatile uint_16 *duty;
#else
extern volatile uint_8 *duty;
#endif
extern uint_8 resolution_size;
extern volatile boolean trCallBack;
extern uint_8 sample_out;

uint_8 audio_sample = 0;

/******************************************************************************
*   @name        pit1_init
*
*   @brief       This function init PIT0
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void audio_timer_init(void) 
{ 
#if (defined BSP_M52259DEMO) || (defined BSP_M52259EVB) || (defined BSP_TWRMCF52259)
   if (_int_install_isr(BSP_PIT1_INT_VECTOR,
      (void (_CODE_PTR_)(pointer))AUDIO_TIMER_ISR, NULL) == NULL)
   {
      return ;
   } /* Endif */
#endif
#if (defined BSP_TWRMCF51JE)
    _int_install_isr(MCF51JE_INT_Vcmt,
        (void (_CODE_PTR_)(pointer))AUDIO_TIMER_ISR,NULL);
#endif

#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
	if(_int_install_isr(INT_PIT1,
				(void (_CODE_PTR_)(pointer))AUDIO_TIMER_ISR, NULL) == NULL)
	{
		return ;
	} /* Endif */
	_bsp_int_init(INT_PIT1, 2, 0, TRUE);
#endif
}

#if (defined BSP_TWRMCF51JE)
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : cmt_init_freq
* Returned Value   :
* Comments         : Initialize timer module
*    
*
*END*----------------------------------------------------------------------*/
void cmt_init_freq(uint_32 period)
{
    VMCF51JE_CMT_STRUCT_PTR cmt = &(((MCF51JE_STRUCT_PTR)_PSP_GET_MBAR())->CMT);
    /* CMTMSC: EOCF=0,CMTDIV1=0,CMTDIV0=0,EXSPC=0,BASE=0,FSK=0,EOCIE=0,MCGEN=0 */
    cmt->CMTMSC = 0x00;                
    /* CMTOC: IROL=0,CMTPOL=0,IROPEN=0,??=0,??=0,??=0,??=0,??=0 */
    cmt->CMTOC = 0x00;                 
    /* CMTCG1: PH7=0,PH6=0,PH5=0,PH4=0,PH3=0,PH2=0,PH1=0,PH0=0,PL7=0,PL6=0,PL5=0,PL4=0,PL3=0,PL2=0,PL1=0,PL0=0 */
    cmt->CMTCGH1 = 0x00;
    cmt->CMTCGL1 = 0x00;
    /* CMTCG2: SH7=0,SH6=0,SH5=0,SH4=0,SH3=0,SH2=0,SH1=0,SH0=0,SL7=0,SL6=0,SL5=0,SL4=0,SL3=0,SL2=0,SL1=0,SL0=0 */
    cmt->CMTCGH2 = 0x00;
    cmt->CMTCGL2 = 0x00;               
    /* CMTCMD12: MB15=0,MB14=0,MB13=0,MB12=0,MB11=0,MB10=0,MB9=0,MB8=1,MB7=0,MB6=1,MB5=1,MB4=1,MB3=0,MB2=1,MB1=1,MB0=0 */
    cmt->CMTCMD1 = (uint_8)((period & 0xFF00)>>8);
    cmt->CMTCMD2 = (uint_8)(period & 0x00FF);           

    /* CMTCMD34: SB15=0,SB14=0,SB13=0,SB12=0,SB11=0,SB10=0,SB9=0,SB8=0,SB7=0,SB6=0,SB5=0,SB4=0,SB3=0,SB2=0,SB1=0,SB0=0 */
    cmt->CMTCMD3 = 0x00;
    cmt->CMTCMD4 = 0x00;
    /* CMTMSC: EOCF=0,CMTDIV1=0,CMTDIV0=0,EXSPC=0,BASE=0,FSK=0,EOCIE=1,MCGEN=1 */
    cmt->CMTMSC = 0x01;  
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : EnableCmtInterrupt 
* Returned Value   :
* Comments         : Enable CMT interrupt
*    
*
*END*----------------------------------------------------------------------*/
void EnableCmtInterrupt(void)
{
    VMCF51JE_CMT_STRUCT_PTR cmt = &(((MCF51JE_STRUCT_PTR)_PSP_GET_MBAR())->CMT);
  	/* Enable Timer Interrupt */
  	cmt->CMTMSC |= 0x02;
  	return;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : DisableCmtInterrupt 
* Returned Value   :
* Comments         : Disable CMT interrupt.
*    
*
*END*----------------------------------------------------------------------*/
void DisableCmtInterrupt(void)
{
    VMCF51JE_CMT_STRUCT_PTR cmt = &(((MCF51JE_STRUCT_PTR)_PSP_GET_MBAR())->CMT);
  	/* Disable Timer Interrupt */
  	cmt->CMTMSC &= ~(0x02);
  	return;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : ClearCmtInterrupt 
* Returned Value   :
* Comments         : Clear CMT Interrupt.
*    
*
*END*----------------------------------------------------------------------*/
static void ClearCmtInterrupt(void)
{
    VMCF51JE_CMT_STRUCT_PTR cmt = &(((MCF51JE_STRUCT_PTR)_PSP_GET_MBAR())->CMT);
  	/* Clear Timer Interrupt */
    (void)cmt->CMTMSC; 
    (void)cmt->CMTCMD2;
  	return;
}
#endif


#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
/*FUNCTION*-----------------------------------------------------------------
*
* Function Name   : _kinetis_timer_init_freq
* Returned Value  : the clock rate for the timer (ns per hw tick)
* Comments        :
*   this function will set up a timer to interrupt
*
*END*---------------------------------------------------------------------*/
void _kinetis_timer_init_freq
   (
      /* [IN] the timer to initialize */
      _mqx_uint timer,

      /* [IN] ticks per second */
      uint_32   tickfreq,
      
      /* [IN] the system clock speed in MHz */
      uint_32   system_clock,

      /* [IN] Unmask the timer after initializing */
      boolean   unmask_timer
   )
{ /* Body */
	
	if(tickfreq != 0)
	{
		/* Enable PIT Module Clock */
		SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
		
		/* Configure PIT */
		PIT_MCR = ~(PIT_MCR_FRZ_MASK |PIT_MCR_MDIS_MASK);

		/* Timer counter value */
		PIT_LDVAL_REG(PIT_BASE_PTR,timer) = system_clock/tickfreq;
	
		/* Enable PIT interrupt */
		PIT_TCTRL_REG(PIT_BASE_PTR,timer) = PIT_TCTRL_TEN_MASK;
		
		/* Mask PIT interrupt flag */
		PIT_TFLG_REG(PIT_BASE_PTR,timer)= PIT_TFLG_TIF_MASK; 
		
	}
	if (unmask_timer) 
	{
	    _kinetis_timer_unmask_int(timer);
	} 
}

/******************************************************************************
*   @name        _kinetis_timer_mask_int
*
*   @brief       This function enables PIT timer interrupt
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void _kinetis_timer_mask_int(uint_32 timer)
{ 					  
	PIT_TCTRL_REG(PIT_BASE_PTR,timer)&=~PIT_TCTRL_TEN_MASK;  
    PIT_TCTRL_REG(PIT_BASE_PTR,timer)&=~PIT_TCTRL_TIE_MASK;
} 

/******************************************************************************
*   @name        _kinetis_timer_unmask_int
*
*   @brief       This function disables PIT timer interrupt
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void _kinetis_timer_unmask_int(uint_32 timer)
{ 					 
	PIT_TCTRL_REG(PIT_BASE_PTR,timer)|= PIT_TCTRL_TEN_MASK;  
    PIT_TCTRL_REG(PIT_BASE_PTR,timer)|= PIT_TCTRL_TIE_MASK;
} 

/******************************************************************************
*   @name        _kinetis_timer_clear_int
*
*   @brief       This function clears PIT interrupt flag
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void _kinetis_timer_clear_int(uint_32 timer)
{
	PIT_TFLG_REG(PIT_BASE_PTR,timer) |= PIT_TFLG_TIF_MASK;
}
#endif
/******************************************************************************
 *   @name        PIT0_ISR
 *
 *   @brief       This routine services RTC Interrupt
 *
 *	 @param       None
 *
 *   @return      None
 *
 ******************************************************************************
 * Services Programmable Interrupt Timer 0. If a Timer Object expires, then  
 * removes the object from Timer Queue and Calls the callback function 
 * (if registered)
 *****************************************************************************/
void AUDIO_TIMER_ISR(void)
{
#if (defined BSP_M52259DEMO) || (defined BSP_M52259EVB) || (defined BSP_TWRMCF52259)
	_mcf5225_timer_clear_int(BSP_LAST_TIMER);
#endif
#if (defined BSP_TWRMCF51JE)
	ClearCmtInterrupt();
#endif
#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
	_kinetis_timer_clear_int(BSP_LAST_TIMER);
#endif

	if (USB_DEVICE_INTERFACED == audio_stream.DEV_STATE)
	{
		/* Check device type */
		if(IN_DEVICE == device_direction)
		{
			/* For speaker */
			/* Send data */
			usb_audio_send_data((CLASS_CALL_STRUCT_PTR)&audio_control.CLASS_INTF,
			(CLASS_CALL_STRUCT_PTR)&audio_stream.CLASS_INTF, usb_host_audio_tr_callback,
			NULL, packet_size, (uchar_ptr)wav_buff);			
		}
		else
		{
			/* For microphone */
			if((packet_size-1) < audio_sample)
			{	
				audio_sample = 0;
				
				/* Recv data */
				usb_audio_recv_data((CLASS_CALL_STRUCT_PTR)&audio_control.CLASS_INTF,
				(CLASS_CALL_STRUCT_PTR)&audio_stream.CLASS_INTF, usb_host_audio_tr_callback,
				NULL, packet_size*resolution_size, (uchar_ptr)wav_recv_buff);
			}
			else
			{
				/* Check packet is sent completely */
		    	if(trCallBack)
		    	{
		    		trCallBack=FALSE;
				    /* update duty */
				    *duty = wav_recv_buff_tmp[audio_sample];
		    	}
			}
			audio_sample+=sample_out;		
		}
	}
#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
	PIT_TCTRL_REG(PIT_BASE_PTR,1)|= PIT_TCTRL_TIE_MASK;
#endif
}

/* EOF */

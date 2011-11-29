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
 * @file kbi.c
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
#include "kbi.h"

/******************************************************************************
 * Local functions
 *****************************************************************************/
static void process_play_button(void);
#if (defined BSP_M52259DEMO) || (defined BSP_M52259EVB) || (defined BSP_TWRMCF52259)
void SwitchIntervalPollingTimerCallback(void);
void DTIM0_init(void);
void DTIM0_ISR(void);
#endif

#if (defined BSP_TWRMCF51JE)
void IRQ_ISR(void);
void KBI_ISR(void);
#endif

#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
void IRQ_ISR1(void);
void IRQ_ISR2(void);
#endif
/******************************************************************************
 * Global variables
 *****************************************************************************/
extern boolean play;
extern uint_8 mute_flag;
extern LWEVENT_STRUCT USB_Event;
extern volatile AUDIO_CONTROL_DEVICE_STRUCT 	audio_stream;
/* Buttons for MCF52259 */
#if (defined BSP_M52259DEMO) || (defined BSP_M52259EVB) || (defined BSP_TWRMCF52259)
static MQX_FILE_PTR port_file1;
volatile uint_8 kbi_gpio_state1 = GPIO_PIN_STATUS,kbi_gpio_state2 = GPIO_PIN_STATUS;
static GPIO_PIN_STRUCT pins[] = {
    BSP_BUTTON2,
    BSP_BUTTON1,
    GPIO_LIST_END
};
#endif

/* Buttons for BSP_TWRMCF51JE */
#if (defined BSP_TWRMCF51JE)
static MQX_FILE_PTR port_file1;
GPIO_PIN_STRUCT pin1[] = 
{
	  BSP_BUTTON1 | GPIO_PIN_IRQ_FALLING,
    GPIO_LIST_END
};
#endif

/* Buttons for TWR_K40X256 */
#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
MQX_FILE_PTR port_file1,port_file2;
GPIO_PIN_STRUCT pin1[] = 
{
	BSP_BUTTON1 | GPIO_PIN_IRQ_FALLING,
    GPIO_LIST_END
};
GPIO_PIN_STRUCT pin2[] = {
	BSP_BUTTON2 | GPIO_PIN_IRQ_FALLING,
	GPIO_LIST_END
};
#endif

/******************************************************************************
*   @name        process_play_button
*
*   @brief       process play button
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
static void process_play_button(void)
{
	if(USB_DEVICE_INTERFACED == audio_stream.DEV_STATE)
	{
		play = 1 - play;
		/* play */
		if (TRUE == play)
		{
			printf("Playing ...\n");
			_lwevent_set(&USB_Event, USB_EVENT_RECEIVED_DATA);
#if (defined BSP_TWRMCF51JE)
		  EnableCmtInterrupt();
#else
			_audio_timer_unmask_int(BSP_LAST_TIMER);
#endif
		}
		/* stop */
		else
		{
			printf("\nPaused.\n");
#if (defined BSP_TWRMCF51JE)
		  DisableCmtInterrupt();
#else
			_audio_timer_mask_int(BSP_LAST_TIMER);
#endif
		}
	}	
}
/******************************************************************************
*   @name        GPIO_Init
*
*   @brief       This function init GPIO
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void GPIO_Init(void)
{
#if (defined BSP_M52259DEMO) || (defined BSP_M52259EVB) || (defined BSP_TWRMCF52259)
   /* opening pins/signals for input */
   if (NULL == (port_file1 = fopen("gpio:read", (char_ptr) &pins )))
   {
       printf("Opening file1 GPIO with associated pins failed.\n");
      _mqx_exit(-1);
   }

   /* Initialize DTIM0 timer */
   DTIM0_init();
#endif

#if (defined BSP_TWRMCF51JE)
    VMCF51JE_GPIO_STRUCT_PTR gpio_pe =  &(((MCF51JE_STRUCT_PTR)_PSP_GET_MBAR())->GPIO_A_G[GPIO_PORT_D]);
    VMCF51JE_IRQ_STRUCT_PTR irq =  &(((MCF51JE_STRUCT_PTR)_PSP_GET_MBAR())->IRQ);
   
    /* Port pull up enable */
    gpio_pe->PTxPE |= 32;
    
    irq->IRQSC = 2 | 16;
   
    /* Install kbi interrupt service */
    _int_install_isr(MCF51JE_INT_Virq,
        (void (_CODE_PTR_)(pointer))IRQ_ISR, NULL);

               
    /* opening pins/signals for input */
  	if (NULL == (port_file1 = fopen("gpio:read", (char_ptr) &pin1 )))
  	{
		printf("Opening file3 GPIO with associated pins failed.\n");
		_mqx_exit(-1);
  	}
     
  	/* install gpio interrupt callback */
  	ioctl(port_file1, GPIO_IOCTL_SET_IRQ_FUNCTION, (pointer)KBI_ISR); 
#endif

#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
	/* opening pins/signals for input */
	if (NULL == (port_file1 = fopen("gpio:read", (char_ptr) &pin1 )))
	{
		printf("Opening file3 GPIO with associated pins failed.\n");
		_mqx_exit(-1);
	}
   
/* opening pins/signals for input */
	if (NULL == (port_file2 = fopen("gpio:read", (char_ptr) &pin2 )))
	{
		printf("Opening file3 GPIO with associated pins failed.\n");
		_mqx_exit(-1);
	}
	/* install gpio interrupt callback */
	ioctl(port_file1, GPIO_IOCTL_SET_IRQ_FUNCTION, (pointer)IRQ_ISR1);
	  
	ioctl(port_file2, GPIO_IOCTL_SET_IRQ_FUNCTION, (pointer)IRQ_ISR2);
#endif
}


#if (defined BSP_M52259DEMO) || (defined BSP_M52259EVB) || (defined BSP_TWRMCF52259)
/******************************************************************************
*   @name        DTIM_init
*
*   @brief       This function inits DTIM0
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void DTIM0_init(void) 
{ 
 
 	VMCF5225_DMA_TIMER_STRUCT_PTR dtim0 = &(((VMCF5225_STRUCT_PTR)_PSP_GET_IPSBAR())->DMA_TIMER[0]);
    /* Internal Bus Clock is System Clock/2 meaning 40 MHz */
    /* Prescaler 4 (PRE field equals to 2) thus giving an tick of 0.1 usec. */
    dtim0->DTMR = 		MCF5225_DTIM_DTMR_PS(7) | 
    					MCF5225_DTIM_DTMR_CE_NONE |
    					MCF5225_DTIM_DTMR_FRR |
    					MCF5225_DTIM_DTMR_CLK_DIV1 |
    					MCF5225_DTIM_DTMR_ORRI;

	dtim0->DTRR = 10000;
	
	dtim0->DTER = 0x03;
	
	_int_install_isr(MCF5225_INT_DTIM0,
      (void (_CODE_PTR_)(pointer))DTIM0_ISR, NULL);

    _mcf52xx_int_init(MCF5225_INT_DTIM0, 3,2, TRUE);
    
	/* Enable timer */
	dtim0->DTMR |= MCF5225_DTIM_DTMR_RST;

}

/******************************************************************************
 *   @name        DTIM0_ISR
 *
 *   @brief       This routine services DTIM Interrupt
 *
 *	 @param       None
 *
 *   @return      None
 *
 ******************************************************************************
 * Services Programmable Interrupt Timer 0. 
 *****************************************************************************/
void DTIM0_ISR(void)
{
	VMCF5225_DMA_TIMER_STRUCT_PTR dtim0 = &(((VMCF5225_STRUCT_PTR)_PSP_GET_IPSBAR())->DMA_TIMER[0]);	
	
	SwitchIntervalPollingTimerCallback();
	dtim0->DTER |= 0x03;
}

/******************************************************************************
*   @name        SwitchIntervalPollingTimerCallback
*
*   @brief       This function services keyboard polling
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void SwitchIntervalPollingTimerCallback(void)
{
	uint_8 kbi_gpio_new_state1 = 0,kbi_gpio_new_state2 = 0;
	
	/* read pin/signal status to pin list */
    if (IO_OK != ioctl(port_file1, GPIO_IOCTL_READ, (char_ptr) &pins))
    {
      	printf("Reading pin status from file1 to pin1 list failed.\n");
      	_mqx_exit(-1);
    }
   
	kbi_gpio_new_state1 = !(pins[0] & GPIO_PIN_STATUS);
	
 	/* Process button 1 */
 	if ((kbi_gpio_new_state1 != kbi_gpio_state1 ) && (kbi_gpio_new_state1 ))	
 	{ 		
		process_play_button();
 	}	
 	
 	kbi_gpio_new_state2 = !(pins[1] & GPIO_PIN_STATUS);
 	/* Process button 2 */
 	if ((kbi_gpio_new_state2 != kbi_gpio_state2 ) && (kbi_gpio_new_state2 ))	
 	{ 		
	 	mute_flag=1;
 	}
 	kbi_gpio_state1 = kbi_gpio_new_state1;
 	kbi_gpio_state2 = kbi_gpio_new_state2;
}
#endif

#if (defined BSP_TWRMCF51JE)
/******************************************************************************
*   @name        IRQ_ISR
*
*   @brief       Service interrupt routine of KBI
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void IRQ_ISR(void)
{
    MCF51JE_IRQ_STRUCT_PTR irq = &(((MCF51JE_STRUCT_PTR)_PSP_GET_MBAR())->IRQ);
    mute_flag = 1;
    /* Clear kbi interrupt */
    irq->IRQSC |= 0x04;  
   
}

/******************************************************************************
*   @name        KBI_ISR
*
*   @brief       Service interrupt routine of IRQ
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void KBI_ISR(void)
{
	process_play_button();	
}
#endif

#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
/******************************************************************************
*   @name        IRQ_ISR1
*
*   @brief       Service interrupt routine of IRQ
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void  IRQ_ISR1(void)
{
	if(USB_DEVICE_INTERFACED == audio_stream.DEV_STATE)
	{
		play = 1 - play;
		/* play */
		if (TRUE == play)
		{
			printf("Playing ...\n");
			_lwevent_set(&USB_Event, USB_EVENT_RECEIVED_DATA);
			_kinetis_timer_unmask_int(BSP_LAST_TIMER);
		}
		/* stop */
		else
		{
			printf("\nPaused.\n");
			_kinetis_timer_mask_int(BSP_LAST_TIMER);
		}
	}
}

/******************************************************************************
*   @name        IRQ_ISR2
*
*   @brief       Service interrupt routine of IRQ
*
*   @return      None
*
*   @comment	 
*    
*******************************************************************************/
void  IRQ_ISR2(void)
{
	mute_flag=1;
}
#endif
/* EOF */

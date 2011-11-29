/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
* All Rights Reserved
*
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
* $FileName: audio_pwm.c$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief 
*
*****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "audio_pwm.h"

/*****************************************************************************
 * Constant and Macro's 
 *****************************************************************************/

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
void _pwm_init(void);

/****************************************************************************
 * Global Variables
 ****************************************************************************/
#if (defined BSP_TWRMCF51JE) 
volatile uint_16 *duty;
#else
volatile uint_8 *duty;
#endif

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Local Variables 
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/******************************************************************************
 *
 *   @name        _pwm_init
 *
 *   @brief       This function initialyzes PWM.
 *
 *   @param       None
 *
 *   @return      None
 *****************************************************************************/
void _pwm_init()
{
#if (defined BSP_M52259DEMO) || (defined BSP_M52259EVB) || (defined BSP_TWRMCF52259)
	VMCF5225_PWM_STRUCT_PTR pwm = &(((VMCF5225_STRUCT_PTR)_PSP_GET_IPSBAR())->PWM);
	VMCF5225_GPIO_STRUCT_PTR gpio = &(((VMCF5225_STRUCT_PTR)_PSP_GET_IPSBAR())->GPIO);	
#ifdef BSP_TWRMCF52259
	duty = &(pwm->PWMDTY[0]);
	
	/* Init IO for PWM */;
	gpio->PTCPAR |= 0x03;	
	
	pwm->PWME = 0;
	/* PCKA = 1: clock A rate = bus clk / 1 = 40MHz*/
	pwm->PWMPRCLK = 0x00;
		
	pwm->PWMPER[0] = 0xFF;
	pwm->PWMDTY[0] = 0x00;
	
	/* High at begin of period */
	pwm->PWMPOL = 0x2;
	/* chose clock source is A */
	pwm->PWMCLK = 0x00;
	/* No Concatenates */
	pwm->PWMCTL = 0x00;
	
	/* Enable PWM */
	pwm->PWME = 0x01;
#else
	duty = &(pwm->PWMDTY[1]);
	
	/* Init IO for PWM */
	gpio->PTAPAR |= 0x03;

	pwm->PWME = 0;
	/* PCKA = 1: clock A rate = bus clk / 1 = 40MHz*/
	pwm->PWMPRCLK = 0x00;
	
	pwm->PWMPER[1] = 0xFF;
	pwm->PWMDTY[1] = 0x00;
	

	/* High at begin of period */
	pwm->PWMPOL = 0x2;
	/* chose clock source is A */
	pwm->PWMCLK = 0x00;
	/* No Concatenates */
	pwm->PWMCTL = 0x00;
	
	/* Enable PWM */
	pwm->PWME = 0x02;
#endif
#endif
#if (defined BSP_TWRMCF51JE)
  	VMCF51JE_TPM_STRUCT_PTR tpm = &(((MCF51JE_STRUCT_PTR)_PSP_GET_MBAR())->TPM2);
  	VMCF51JE_STRUCT_PTR reg_ptr = _PSP_GET_MBAR();
  	
  	reg_ptr->SIM.SCGC1 |= MCF51XX_SCGC1_TPM2_MASK;  
  		
  	duty = (uint_16*)(&(tpm->TPMxC[0].TPMxCyV));
    
    
  	tpm->TPMxSC = 0;
  	tpm->TPMxMOD = 0xFF;
  	tpm->TPMxC[0].TPMxCySC = 0x24;
  	*duty = 0x55;
  	tpm->TPMxSC = 0x08;
#endif
#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
	duty = (uint_8 *)&(FTM0_C0V);
	/* FTM0_CH0 enable on PTA3 ****/
	PORTC_PCR1 = PORT_PCR_MUX(0x4); 
	
	/* Enable clock for FTM */
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
	
	/* Set FTM mode */
	FTM0_MODE = (FTM_MODE_WPDIS_MASK | FTM_MODE_FTMEN_MASK);
	FTM0_MODE &= ~FTM_MODE_FTMEN_MASK;
	FTM0_SC = 0;
	FTM0_CNTIN = 0x00;
	
	/* Set FTM modular */
	FTM0_MOD = 0xFF;
	FTM0_QDCTRL &= ~(FTM_QDCTRL_QUADEN_MASK);
	FTM0_COMBINE &= ~(FTM_COMBINE_DECAPEN0_MASK \
			|FTM_COMBINE_DECAPEN1_MASK \
			|FTM_COMBINE_DECAPEN2_MASK \
			|FTM_COMBINE_DECAPEN3_MASK \
			|FTM_COMBINE_COMBINE0_MASK \
			|FTM_COMBINE_COMBINE1_MASK \
			|FTM_COMBINE_COMBINE2_MASK \
			|FTM_COMBINE_COMBINE3_MASK);
	FTM0_C0SC = 0x28;   
	
	/* Enable FTM */
	FTM0_SC = 0x08;  
#endif
}
/* EOF */

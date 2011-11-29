/** ###################################################################
**     Filename  : Events.h
**     Project   : ProcessorExpert
**     Processor : MK40X256VMD100
**     Component : Events
**     Version   : Driver 01.00
**     Compiler  : CodeWarrior ARM C Compiler
**     Date/Time : 2011-02-04, 14:38, # CodeGen: 0
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "MQX1.h"
#include "GPIO1.h"
#include "DA1.h"
#include "TRG.h"
#include "WDog1.h"
#include "PWM.h"
#include "PE_LDD.h"

void DA1_OnBufferWatermark(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Event       :  DA1_OnBufferWatermark (module Events)
**
**     Component   :  DA1 [DAC_LDD]
**     Description :
**         Buffer read pointer reached the watermark level. This event
**         can be enabled only if Interrupt service is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * UserDataPtr     - Pointer to the user or
**                           RTOS specific data.
**     Returns     : Nothing
** ===================================================================
*/

void DA1_OnBufferEnd(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Event       :  DA1_OnBufferEnd (module Events)
**
**     Component   :  DA1 [DAC_LDD]
**     Description :
**         Buffer read pointer reached buffer top position. This event
**         can be enabled only if Interrupt service is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * UserDataPtr     - Pointer to the user or
**                           RTOS specific data.
**     Returns     : Nothing
** ===================================================================
*/

void DA1_OnBufferStart(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Event       :  DA1_OnBufferStart (module Events)
**
**     Component   :  DA1 [DAC_LDD]
**     Description :
**         Buffer read pointer reached buffer bottom position. This
**         event can be enabled only if Interrupt service is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * UserDataPtr     - Pointer to the user or
**                           RTOS specific data.
**     Returns     : Nothing
** ===================================================================
*/

void PWM_OnCounterRestart(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Event       :  PWM_OnCounterRestart (module Events)
**
**     Component   :  PWM [TimerUnit_LDD]
**     Description :
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         <SetEventMask> and <GetEventMask> methods. This event is
**         available only if a <Interrupt> is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
**     Returns     : Nothing
** ===================================================================
*/

void TRG_OnCounterRestart(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Event       :  TRG_OnCounterRestart (module Events)
**
**     Component   :  TRG [TimerUnit_LDD]
**     Description :
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         <SetEventMask> and <GetEventMask> methods. This event is
**         available only if a <Interrupt> is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 [04.48]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

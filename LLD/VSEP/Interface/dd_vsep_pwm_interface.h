#ifndef DD_VSEP_PWM_INTERFACE_H
#define DD_VSEP_PWM_INTERFACE_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_pwm_interface.h~4:incl:mt20u2#2 %
//
// created_by:       lz7r3l
//
// date_created:     Tue Feb  8 10:35:20 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 11:15:41 2007 %
//
// %version:         4 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================


#include "dd_vsep.h"
#include "dd_vsep_pwm.h"
#include "dd_vsep_fault.h"


#define VSEP_SPIPWM(action,in_configuration,value)  VSEP_PWM_PWM ## action ## (in_configuration, value)

/* action type
Initialeze Clear Enable Disable GetStatus GetTimeState GetFreq	GetTimeSize	SetPeriod		
SetDuty	SetPeriodImmediate	SetDutyImmediate		GetDuty Getperiod
*/
// discuss the what is the kind of input paremeter
#define VSEP_PWM_PWMInitialize(in_configuration, value)\
	VSEP_PWM_Channel_Initialize(in_configuration)
#define VSEP_PWM_PWMClear(in_configuration, value)\
	VSEP_PWM_Channel_Clear(in_configuration)
#define VSEP_PWM_PWMEnable(in_configuration, value)\
	VSEP_PWM_Enable_Channel(in_configuration)

#define VSEP_PWM_PWMDisable(in_configuration, value)\
	VSEP_PWM_Disable_Channel(in_configuration)
	
#define VSEP_PWM_PWMGetStatus(in_configuration, value)\
	VSEP_PWM_Get_Channel_Status(in_configuration)

//---------------------------------------------
#define VSEP_PWM_PWMGetTimeState(in_configuration, value)	IO_TIMER_STATE_RUNNING
	
//	VSEP_PWM_Timer_Get_State(in_configuration)
// VSEP does not support changing frequency of SPI based PWM output
#define VSEP_PWM_PWMSetFreq(in_configuration, value) \
	VSEP_PWM_Set_Period_And_Duty_Cycle(in_configuration,value,VSEP_PWM_Period_InType_HZ,20,VSEP_PWM_DutyCycle_InType_Percent,true,false)

#define VSEP_PWM_PWMSetFreqImmediate(in_configuration,value)\
       VSEP_PWM_Set_Period_And_Duty_Cycle_Immediate(in_configuration,value,VSEP_PWM_Period_InType_HZ,20,VSEP_PWM_DutyCycle_InType_Percent,true,false)

#define VSEP_PWM_PWMGetFreq(in_configuration, value)\
	VSEP_PWM_Get_Period(in_configuration,VSEP_PWM_Period_ReturnType_HZ)

#define VSEP_PWM_PWMGetTimerSize(in_configuration, value)	IO_TIMER_12_BIT
	
//	VSEP_PWM_Timer_Get_Size(in_configuration)
//--------------------------------------------------------------------
#define VSEP_PWM_PWMSetPeriod(in_configuration, value)\
	VSEP_PWM_Set_Period_And_Duty_Cycle(in_configuration,value,VSEP_PWM_Period_InType_MS,20,VSEP_PWM_DutyCycle_InType_Percent,true,false)
	
#define VSEP_PWM_PWMSetDuty(in_configuration, value)\
	VSEP_PWM_Set_Period_And_Duty_Cycle(in_configuration,value+1,VSEP_PWM_Period_InType_MS,value,VSEP_PWM_DutyCycle_InType_Percent,false,true)

#define VSEP_PWM_PWMSetPeriodImmediate(in_configuration,value)\
       VSEP_PWM_Set_Period_And_Duty_Cycle_Immediate(in_configuration,value,VSEP_PWM_Period_InType_MS,20,VSEP_PWM_DutyCycle_InType_Percent,true,false)

#define VSEP_PWM_PWMSetDutyImmediate(in_configuration,value)\
       VSEP_PWM_Set_Period_And_Duty_Cycle_Immediate(in_configuration,value+1,VSEP_PWM_Period_InType_MS,value,VSEP_PWM_DutyCycle_InType_Percent,false,true)

#define VSEP_PWM_PWMGetPeriod(in_configuration, value)\
	VSEP_PWM_Get_Period(in_configuration,VSEP_PWM_Period_ReturnType_MS)
#define VSEP_PWM_PWMGetPeriod_US(in_configuration, value)\
	VSEP_PWM_Get_Period(in_configuration,VSEP_PWM_Period_ReturnType_US)

#define VSEP_PWM_PWMGetDuty(in_configuration, value)\
	VSEP_PWM_Get_Duty_Cycle(in_configuration,VSEP_PWM_DutyCycle_ReturnType_Percent)

#define VSEP_PWM_PWMGetDuty_MS(in_configuration, value)\
	VSEP_PWM_Get_Duty_Cycle(in_configuration,VSEP_PWM_DutyCycle_ReturnType_MS)
#define VSEP_PWM_PWMGetDuty_US(in_configuration, value)\
	VSEP_PWM_Get_Duty_Cycle(in_configuration,VSEP_PWM_DutyCycle_ReturnType_US)

#define VSEP_PWM_PWMGet_Fault(in_configuration, value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	VSEP_FAULT_Get_OUTPUT_SHORT_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	VSEP_FAULT_Get_OUTPUT_SHORT_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	VSEP_FAULT_Get_OUTPUT_OPEN_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	VSEP_FAULT_Get_OUTPUT_OPEN_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):0))))
	

#define VSEP_PWM_PWMClear_Fault(in_configuration, value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_SHORT_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_SHORT_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_OPEN_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_OPEN_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):0))))

//VSEP_PWM_DISCRETE_INTERFACE

#define VSEP_PWMSPIDISCRETE(action,in_configuration,value)  VSEP_PWM_Discrete ## action ## (in_configuration, value)
/*action type
Initialize	Clear	Set	SetImmediate	Get GetImmediate 	Toggle	ToggleImmediate
*/
#define VSEP_PWM_DiscreteInitialize(in_configuration, value)\
	VSEP_PWM_DISCRETE_Channel_Initialize(in_configuration)
#define VSEP_PWM_DiscreteClear(in_configuration, value)\
	VSEP_PWM_DISCRETE_Channel_Clear(in_configuration)
#define VSEP_PWM_DiscreteSet(in_configuration, value)\
	VSEP_PWM_DISCRETE_Set_State(in_configuration, value)
#define VSEP_PWM_DiscreteSetImmediate(in_configuration, value)\
	VSEP_PWM_DISCRETE_Set_Immediate_State(in_configuration, value)
#define VSEP_PWM_DiscreteGet(in_configuration, value)\
	VSEP_PWM_DISCRETE_Get_State(in_configuration)
#define VSEP_PWM_DiscreteGetImmediate(in_configuration, value)\
	VSEP_PWM_DISCRETE_Get_State(in_configuration)
#define VSEP_PWM_DiscreteToggle(in_configuration, value)\
	VSEP_PWM_DISCRETE_Toggle_State(in_configuration)
#define VSEP_PWM_DiscreteToggleImmediate(in_configuration, value)\
	VSEP_PWM_DISCRETE_Toggle_Immediate_State(in_configuration)

#define VSEP_PWM_DiscreteGet_Fault(in_configuration, value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	VSEP_FAULT_Get_OUTPUT_SHORT_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	VSEP_FAULT_Get_OUTPUT_SHORT_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	VSEP_FAULT_Get_OUTPUT_OPEN_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	VSEP_FAULT_Get_OUTPUT_OPEN_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):0))))

#define VSEP_PWM_DiscreteClear_Fault(in_configuration, value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_SHORT_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_SHORT_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_OPEN_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_OPEN_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Channel(in_configuration)]):0))))

#endif // DD_VSEP_PWM_INTERFACE_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

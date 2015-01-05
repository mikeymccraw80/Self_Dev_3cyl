#ifndef HAL_OS_H
#define HAL_OS_H

//=============================================================================
// include files
//=============================================================================
#include "reuse.h"

typedef enum {
	HLS_TASK_NORMAL = 0x0000,
	HLS_TASK_1MS    = 0x0001,
	HLS_TASK_2MS    = 0x0002,
	HLS_TASK_5MS    = 0x0004,
	HLS_TASK_10MS   = 0x0008,
	HLS_TASK_20MS   = 0x0010,
	HLS_TASK_50MS   = 0x0020,
	HLS_TASK_100MS  = 0x0040,
	HLS_TASK_200MS  = 0x0080,
	HLS_TASK_1000MS = 0x0100
}HLS_TASK_STATE_T;

//=============================================================================
// HAL_Set_HLS_Task_State
//=============================================================================
 void HAL_Set_HLS_Task_State(int state);

//=============================================================================
// HAL_OS_Get_Shutdown
//=============================================================================
  bool HAL_OS_Get_Shutdown(void);

//=============================================================================
// HAL_OS_1ms_TimeBasedTask
//=============================================================================
void  HAL_OS_1ms_TimeBasedTask(void);

//=============================================================================
// HAL_OS_2ms_TimeBasedTask
//=============================================================================
void  HAL_OS_2ms_TimeBasedTask(void);

//=============================================================================
// HAL_OS_1ms_Task
//=============================================================================
  void  HAL_OS_1ms_Task(void);
//=============================================================================
// HAL_OS_2ms_Task
//=============================================================================
  void  HAL_OS_2ms_Task(void);
//=============================================================================
//  HAL_OS_10ms_Task
//=============================================================================
  void  HAL_OS_10ms_Task(void);
//=============================================================================
//  HAL_OS_100ms_Task
//=============================================================================
  void  HAL_OS_100ms_Task(void);

//=============================================================================
//  App_Init_Task
//=============================================================================
  void HAL_OS_Init_Task(void);

//=============================================================================
//  HAL_OS_SYN_Task
//=============================================================================
 void HAL_OS_SYN_Task(void);

//=============================================================================
// HAL_OS_ToothInt_Hook
//=============================================================================
void HAL_OS_ToothInt_Hook(void);
//=============================================================================
// HAL_OS_CAM_W_Hook
//=============================================================================
void HAL_OS_CAM_W_Hook(void);

//=============================================================================
// HAL_OS_CAM_X_Hook
//=============================================================================
void HAL_OS_CAM_X_Hook(void);
//=============================================================================
// HAL_OS_Engine_Stall_Reset
//=============================================================================
void HAL_OS_Engine_Stall_Reset(void);

//=============================================================================
// HAL_OS_Engine_Start_Crank
//=============================================================================
 void HAL_OS_Engine_Start_Crank(void);

//=============================================================================
// HAL_OS_Engine_First_Gap
//=============================================================================
 void HAL_OS_Engine_First_Gap(void) ;
//=============================================================================
// HAL_OS_Get_Battery_Remove
//=============================================================================
 bool HAL_OS_Get_Battery_Remove(void) ;
 
//=============================================================================
// HAL_OS_Powerdown_Callback
//=============================================================================
void HAL_OS_Powerdown_Callback(void);

//=============================================================================
// HAL_OS_Get_PowerFail_Flag
//=============================================================================
bool HAL_OS_Get_PowerFail_Flag(void);

//=============================================================================
// HAL_OS_Set_PowerFail_Flag
//=============================================================================
void HAL_OS_Set_PowerFail_Flag(bool flag);

//=============================================================================
// HAL_OS_Get_RunningReset_Flag
//=============================================================================
bool HAL_OS_Get_RunningReset_Flag(void);

//=============================================================================
// HAL_OS_Set_RunningReset_Flag
//=============================================================================
void HAL_OS_Set_RunningReset_Flag(bool flag);

// interrupt control routines
void Disable_1ms_interrupt(void) ;
void Enable_1ms_interrupt(void) ;
void LLD_disable_interrupt(void);
void LLD_enable_interrupt(void);

interrupt_state_t Enter_Critical_Section( void );
interrupt_state_t Enter_Critical_Enable_Section( void );
void Leave_Critical_Section( interrupt_state_t in_interrupt_state );

/* The following functions are called in Hal Engine module */
void Sinit_CrankToRun(void);
void Sinit_CrankToStall(void);
void Sinit_KeyOnToCrank(void);
void Sinit_KeyOnToPowerOff(void);
void Sinit_PowerOffDelayToKeyOn(void);
void Sinit_PowerOffDelayToShutDwn(void);
void Sinit_RunToCrank(void);
void Sinit_RunToPowerOffDelay(void);
void Sinit_ShutdownInProcessToKeyOff(void);
void Sinit_ShutdownInProcessToKeyOn(void);
void Sinit_StallToCrank(void);
void Sinit_StallToPowerOffDelay(void);

//=============================================================================
// ToggleHWIO_WatchDog related APIs
//=============================================================================
void ToggleHWIO_WatchDog(void);
void ToggleHWIO_WatchDog_ExceedTimer(void);
void SetHWIO_ServiceExtCOP_1Time(void);
void ToggleHWIO_WatchDogDuringInit(void);
void ToggleHWIO_WatchDog_In_Critical_Section(void);

#endif


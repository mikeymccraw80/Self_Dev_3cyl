#ifndef HAL_OS_H
#define HAL_OS_H

//=============================================================================
// include files
//=============================================================================
#include "reuse.h"

//=============================================================================
// HAL_OS_Get_Shutdown
//=============================================================================
  bool HAL_OS_Get_Shutdown(void);
//=============================================================================
// HAL_OS_1ms_Task
//=============================================================================
  void  HAL_OS_1ms_Task(void);

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

#endif


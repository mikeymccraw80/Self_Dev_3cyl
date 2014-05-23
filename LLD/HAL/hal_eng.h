#ifndef HAL_ENG_H
#define HAL_ENG_H

//=============================================================================
// include files
//=============================================================================
#include "reuse.h"
#include "t_gentypes.h"

typedef enum {
	CeENG_OFF,                    /* 00 */
	CeENG_KEYON,                  /* 01 */
	CeENG_CRANK,                  /* 02 */
	CeENG_RUN,                    /* 03 */
	CeENG_STALL,                  /* 04 */
	CeENG_POWEROFFDELAY,          /* 05 */
	CeENG_SHUTDOWNINPROCESS       /* 06 */
} TeENG_STATE;

typedef enum {
	CeENG_RunModeTranResetDis,
	CeENG_RunModeTranDis,
	CeENG_RunModeTranEnb
} TeENG_RunModeTran;

/******************************************************************************
 *  Global Variable Declarations
 *****************************************************************************/
extern TeENG_STATE     VeVIOS_EngSt;
extern T_COUNT_WORD    NfVIOS_t_EngRunTime;

/**********************************************************************/
/***  Return cumulative total tooth error counts during 58x synchronization. ***/
/**********************************************************************/
extern volatile TbBOOLEAN  Engine_Truning_Flag;
#define GetEngineTurning()				( Engine_Truning_Flag )
#define SetEngineTurning(s)				( Engine_Truning_Flag = (s>0)? true:false)

/*****************************************************************************
 *  Function Declarations
 *****************************************************************************/
void InitVIOS_EngSt(void);
void DtrmnVIOS_RunModeCount(void);
void UpdateVIOS_EngSpdThrsh(void);
void UpdateVIOS_CntrlShutdownLogic(void);
void UpdateVIOS_EngSt(void);
void UpdateVIOS_EngRunTime(void);

//=============================================================================
// HAL_Eng_Get_Cyl_Number
//=============================================================================
  uint16_t HAL_Eng_Get_Cyl_Number(void);


//=============================================================================
// HAL_Eng_Get_Sys_Timer
//=============================================================================
  uint32_t HAL_Eng_Get_Sys_Timer(void) ;

//=============================================================================
// HAL_Eng_Get_Tooth_Period
//=============================================================================
  uint32_t HAL_Eng_Get_Tooth_Period(void) ;

//=============================================================================
// HAL_Eng_Get_Engine_Speed
//=============================================================================
  uint16_t HAL_Eng_Get_Engine_Speed(void) ;
#define GetVIOS_n_EngSpd() HAL_Eng_Get_Engine_Speed()


//=============================================================================
// HAL_Eng_Get_Engine_Reference_Time
//=============================================================================
  uint32_t HAL_Eng_Get_Engine_Reference_Time(void) ;
//=============================================================================
// HAL_Eng_Get_Loss_Of_Sync
//=============================================================================
  bool HAL_Eng_Get_Loss_Of_Sync(void) ;
//=============================================================================
// HAL_Eng_Get_Engine_Tooth
//=============================================================================
  uint16_t HAL_Eng_Get_Engine_Tooth(void) ;

#endif
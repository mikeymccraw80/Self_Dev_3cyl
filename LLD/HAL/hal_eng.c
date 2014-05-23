/*===========================================================================*\
 * Header Files
\*===========================================================================*/
#include "dd_crank_interface.h"
#include "hal_eng.h"
#include "hal_os.h"
#include "hwiocald.h"
#include "intr_ems.h"

#define GetVIOS_n_EngTurnThrsh()\
    ( V_RPMa(60.0) )

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
TbBOOLEAN             VbVIOS_CrankToRunMet;
TbBOOLEAN             VbVIOS_CrankToStallMet;
TbBOOLEAN             VbVIOS_RunToCrankMet;
TbBOOLEAN             VbVIOS_OnToCrankMet;
TbBOOLEAN             VbVIOS_PowerdownDelayTimeExpired;
TbBOOLEAN             VbVIOS_StallToCrankMet;
TbBOOLEAN             VbVIOS_ShutdownComplete;
T_COUNT_BYTE          VcVIOS_RunCylCount;
T_COUNT_BYTE          VcVIOS_RunModeCount;
TeENG_RunModeTran     VeVIOS_RunModeTran;
TeENG_STATE           VeVIOS_EngSt;
Every_Loop_Sec_W      VaVIOS_t_PowerdownDelayTimer;
T_COUNT_WORD          NfVIOS_t_EngRunTime;
volatile TbBOOLEAN  Engine_Truning_Flag;

/******************************************************************************
*  Local Function declarations
******************************************************************************/
static void DtrmnVIOS_RUN_Mode(void);
static void DtrmnVIOS_CrankExit(void);
static void DtrmnVIOS_RunToCrankMet(void);
static void DtrmnVIOS_StallToCrankMet(void);
static void DtrmnVIOS_OnToCrankMet(void);

/*****************************************************************************
 *                                                                           *
 * Function:            DtrmnVIOS_RUN_Mode                                   *
 * Description:         This procedure Determine and Update the Engine State *
 *                      value at power up.                                   *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *                                                                           *
 *****************************************************************************/

static void DtrmnVIOS_RUN_Mode(void)
{
	if (VeVIOS_EngSt != CeENG_RUN) {
		if (GetVIOS_T_CoolTemp() < KfVIOS_T_RunCoolLo) {
			VcVIOS_RunCylCount = KcVIOS_RunRefCold;
		} else if (GetVIOS_T_CoolTemp() < KfVIOS_T_RunCoolHi) {
			VcVIOS_RunCylCount = KcVIOS_RunRefWarm;
		} else {
			VcVIOS_RunCylCount = KcVIOS_RunRefHot;
		}
	}
}

/*****************************************************************************
 *                                                                           *
 * Function:            DtrmnVIOS_CrankExit                                  *
 * Description:         This procedure Update the Engine State Crank EXIT    *
 *                      Mode   .                                             *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *                                                                           *
 *****************************************************************************/
static void DtrmnVIOS_CrankExit(void)
{
	if ( (VeVIOS_EngSt == CeENG_CRANK)
		&& (GetVIOS_n_EngSpd() >= KfVIOS_n_CrankToRunThrsh) )
	{
		VeVIOS_RunModeTran      = CeENG_RunModeTranEnb;
		if (VcVIOS_RunModeCount >= VcVIOS_RunCylCount)
		{
			VbVIOS_CrankToRunMet = CbTRUE;
			VeVIOS_RunModeTran = CeENG_RunModeTranDis;
		}
	}
	else
	{
		VbVIOS_CrankToRunMet = CbFALSE;
		VeVIOS_RunModeTran = CeENG_RunModeTranResetDis;
	}

	if ((VeVIOS_EngSt == CeENG_CRANK)
	&& (GetVIOS_n_EngSpd() <= GetVIOS_n_EngTurnThrsh()))
	{
		VbVIOS_CrankToStallMet = CbTRUE;
	}
	else
	{
		VbVIOS_CrankToStallMet = CbFALSE;
	}
}

/*****************************************************************************
 *                                                                           *
 * Function:            DtrmnVIOS_RunToCrankMet                              *
 * Description:         This procedure Detrmine if Engine State Run to Crank *
 *                      IS Enable.                                           *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *****************************************************************************/

static void DtrmnVIOS_RunToCrankMet (void)
{
	if ( (VeVIOS_EngSt == CeENG_RUN)
	&& (GetVIOS_n_EngSpd() <= KfVIOS_n_RunToCrankThrsh))
	{
		VbVIOS_RunToCrankMet = CbTRUE;
	}
	else
	{
		VbVIOS_RunToCrankMet = CbFALSE;
	}
}

/*****************************************************************************
 *                                                                           *
 * Function:            DtrmnVIOS_StallToCrankMet                            *
 * Description:         This procedure Detrmine if Engine Stall to           *
 *                      Crank IS Enable.                                     *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *****************************************************************************/

static void DtrmnVIOS_StallToCrankMet (void)
{
	if ( ( VeVIOS_EngSt == CeENG_STALL )
	&& ( GetVIOS_n_EngSpd() > GetVIOS_n_EngTurnThrsh()))
	{
		VbVIOS_StallToCrankMet = CbTRUE;
	}
	else
	{
		VbVIOS_StallToCrankMet = CbFALSE;
	}
}


/*****************************************************************************
 *                                                                           *
 * Function:            DtrmnVIOS_OnToCrankMet                               *
 * Description:         This procedure Detrmine if Engine ON to Crank IS     *
 *                      Enable.                                              *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *****************************************************************************/

static void DtrmnVIOS_OnToCrankMet (void)
{
	if (  (  (VeVIOS_EngSt == CeENG_KEYON)
	&& (GetVIOS_IgnSt() == CeIGN_ON) )
	&& (GetVIOS_n_EngSpd() > GetVIOS_n_EngTurnThrsh()) )
	{
		VbVIOS_OnToCrankMet = CbTRUE;
	}
	else
	{
		VbVIOS_OnToCrankMet = CbFALSE;
	}
}

/*****************************************************************************
 *                                                                           *
 * Function:           UpdateVIOS_EngSpdThrsh                                *
 * Description:        This procedure Update engine speed threshold every    *
 *                     7.81 ms                                               *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *****************************************************************************/

void UpdateVIOS_EngSpdThrsh (void)
{
	DtrmnVIOS_RUN_Mode();
	DtrmnVIOS_CrankExit();
	DtrmnVIOS_RunToCrankMet();
	DtrmnVIOS_StallToCrankMet();
	DtrmnVIOS_OnToCrankMet();
}

/*****************************************************************************
*                                                                            *
* Function:             SinitVIOS_EngSt                                      *
* Description:          This procedure Initialize the Engine State value at  *
*                       power up.                                            *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void InitVIOS_EngSt(void)
{
	VeVIOS_RunModeTran = CeENG_RunModeTranResetDis;
	VeVIOS_EngSt       = CeENG_KEYON;
}

/*****************************************************************************
 *                                                                           *
 * Function:            UpdateVIOS_CntrlShutdownLogic                        *
 * Description:         This procedure Control the Engine Shut down Logic    *
 *                      which get Updated Every 7.8 ms                       *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *****************************************************************************/
void UpdateVIOS_CntrlShutdownLogic (void)
{
	if ((GetVIOS_IgnSt() == CeIGN_OFF)
	 &&( VaVIOS_t_PowerdownDelayTimer < KfVIOS_t_PowerdownDelayTime ) )
	{
		VaVIOS_t_PowerdownDelayTimer++;
	}
	else if ((GetVIOS_IgnSt() == CeIGN_OFF) &&
			(VaVIOS_t_PowerdownDelayTimer >= KfVIOS_t_PowerdownDelayTime) )
	{
		VbVIOS_PowerdownDelayTimeExpired = CbTRUE;
		VaVIOS_t_PowerdownDelayTimer = 0;
	}
	else
	{
		VbVIOS_PowerdownDelayTimeExpired = CbFALSE;
		VaVIOS_t_PowerdownDelayTimer = 0;
	}

	if (VbVIOS_PowerdownDelayTimeExpired && HAL_OS_Get_Shutdown())
	{
		VbVIOS_ShutdownComplete = CbTRUE;
	}
}

/*****************************************************************************
 *                                                                           *
 * Function:            UpdateVIOS_EngSt                                     *
 * Description:         This procedure Update the Engine State Every 7.81ms. *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *****************************************************************************/

void UpdateVIOS_EngSt(void)
{
	switch (VeVIOS_EngSt) {
	case CeENG_KEYON:
		if (GetVIOS_IgnSt() == CeIGN_OFF) {
			VeVIOS_EngSt = CeENG_POWEROFFDELAY;
			Sinit_KeyOnToPowerOff();
		} else if (VbVIOS_OnToCrankMet) {
			VeVIOS_EngSt = CeENG_CRANK;
			Sinit_KeyOnToCrank();
		} else {
			/* nothing */
		}
		break;

	case CeENG_CRANK:
		if (VbVIOS_CrankToRunMet)
		{
			VeVIOS_EngSt = CeENG_RUN;
			Sinit_CrankToRun();
		}
		else if ((VbVIOS_CrankToStallMet)
				|| (GetVIOS_IgnSt() == CeIGN_OFF))
		{
			VeVIOS_EngSt = CeENG_STALL;
			Sinit_CrankToStall();
		}
		else
		{
			/* nothing */
		}
		break;

	case CeENG_RUN:
		if (GetVIOS_IgnSt() == CeIGN_OFF) {
			VeVIOS_EngSt = CeENG_POWEROFFDELAY;
			Sinit_RunToPowerOffDelay ();
		} else if (VbVIOS_RunToCrankMet) {
			VeVIOS_EngSt = CeENG_CRANK;
			Sinit_RunToCrank();
		} else {
			/* nothing */
		}
		break;

	case CeENG_STALL:
		if (GetVIOS_IgnSt()== CeIGN_OFF) {
			VeVIOS_EngSt = CeENG_POWEROFFDELAY;
			Sinit_StallToPowerOffDelay();
		} else if (VbVIOS_StallToCrankMet) {
			VeVIOS_EngSt = CeENG_CRANK;
			Sinit_StallToCrank();
		} else {
			/* nothing */
		}
		break;

	case CeENG_POWEROFFDELAY:
		if (GetVIOS_IgnSt() == CeIGN_ON) {
			VeVIOS_EngSt = CeENG_KEYON;
			Sinit_PowerOffDelayToKeyOn();
		} else if ( VbVIOS_PowerdownDelayTimeExpired) {
			VeVIOS_EngSt = CeENG_SHUTDOWNINPROCESS;
			Sinit_PowerOffDelayToShutDwn();
		}
		break;

	case CeENG_SHUTDOWNINPROCESS:
		if (VbVIOS_ShutdownComplete) {
			Sinit_ShutdownInProcessToKeyOff();
			VeVIOS_EngSt = CeENG_OFF;
			/* do shutdown logic here */
		} else if (GetVIOS_IgnSt() == CeIGN_ON) {
			VeVIOS_EngSt = CeENG_KEYON;
			Sinit_ShutdownInProcessToKeyOn();
		}
		break;

	default:
		if (GetVIOS_n_EngSpd() > KfVIOS_n_CrankToRunThrsh) {
			VeVIOS_EngSt = CeENG_RUN;
		} else {
			VeVIOS_EngSt = CeENG_KEYON;
		}
		break;
	}
}

/*****************************************************************************
 *                                                                           *
 * Function:            UpdateVIOS_EngRunTime                                *
 * Description:         This procedure Update the Engine State Every Run     *
 *                      time every 1 SECOND.                                 *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *****************************************************************************/
void UpdateVIOS_EngRunTime(void)
{
	if (VeVIOS_EngSt == CeENG_RUN) {
		if ( NfVIOS_t_EngRunTime < V_COUNT_WORD(65535) ) {
			NfVIOS_t_EngRunTime++;
		}
	} else {
		NfVIOS_t_EngRunTime = V_COUNT_WORD(0);
	}
}

/*****************************************************************************
 *                                                                           *
 * Function:            DtrmnVIOS_RunModeCount                               *
 * Description:         This procedure Update the Engine State Run Mode      *
 *                      Counter.                                             *
 *                      Pulse counter of LoRes                               *
 *                      0 disable and reset                                  *
 *                      1 disable                                            *
 *                      2 enable.                                            *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *                                                                           *
 ****************************************************************************/
void DtrmnVIOS_RunModeCount(void)
{
	if (VeVIOS_RunModeTran == CeENG_RunModeTranResetDis)
	{
		VcVIOS_RunModeCount = 0;
	}
	else if (VeVIOS_RunModeTran == CeENG_RunModeTranEnb)
	{
		VcVIOS_RunModeCount ++;
	}
}

//=============================================================================
// HAL_Eng_Get_Cyl_Number
//=============================================================================
  uint16_t HAL_Eng_Get_Cyl_Number(void) 
 {
     return  (uint16_t)CRANK_Get_Cylinder_ID();
 }


//=============================================================================
// HAL_Eng_Get_Sys_Timer
//=============================================================================
  uint32_t HAL_Eng_Get_Sys_Timer(void) 
 {
     return  (uint32_t)STM_Timer_Get_Value();
 }

//=============================================================================
// HAL_Eng_Get_Tooth_Period
//=============================================================================
  uint32_t HAL_Eng_Get_Tooth_Period(void) 
 {
      /* 4M -> 1M HZ*/
      return  (uint32_t)CRANK_Get_Tooth_Period()>>2;
 }

//=============================================================================
// HAL_Eng_Get_Engine_Speed
//=============================================================================
  uint16_t HAL_Eng_Get_Engine_Speed(void) 
 {
     return  (uint16_t)CRANK_Get_Engine_Speed();
 }


//=============================================================================
// HAL_Eng_Get_Engine_Reference_Time
//=============================================================================
  uint32_t HAL_Eng_Get_Engine_Reference_Time(void) 
 {
     return  (uint32_t)CRANK_Get_Engine_Reference_Time();
 }

//=============================================================================
// HAL_Eng_Get_Loss_Of_Sync
//=============================================================================
  bool HAL_Eng_Get_Loss_Of_Sync(void) 
 {
     return  (bool)CRANK_Get_Loss_Of_Sync();
 }

//=============================================================================
// HAL_Eng_Get_Engine_Tooth
//=============================================================================
  uint16_t HAL_Eng_Get_Engine_Tooth(void) 
 {
   return   CRANK_Get_Engine_Tooth();
} 


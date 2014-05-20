//=============================================================================
// include files
//=============================================================================
#include "hal_os.h"
#include "dd_pit_interface.h"
#include "HLS.h"
#include "io_interface_eng.h"
#include "io_interface_vcpc.h"
#include "io_interface_pulse.h"
#include "io_interface_analog.h"
#include "io_interface_fuel.h"
#include "io_interface_spark.h"
#include "io_interface_os.h"
#include "io_interface_gpio.h"
#include "io_interface_can.h"
#include "io_interface_cam.h"
#include "io_interface_etc.h"
#include "hal_cam.h"
#include "hal_eng.h"
#include "emsdpapi.h"
#include "eosdpapi.h"
#include "prgdpapi.h"
#include "estdpapi.h"
#include "epsdpapi.h"
#include "es_knock.h"
#include "hal_soh.h"
#include "hal_analog.h"
#include "io_config_siu.h"
#include "vvtdpapi.h"
#include "condpapi.h"

static int hls_task_state;

//extern void Update_DiagStatus_10ms(void);
//=============================================================================
// Disable/Enable HWIO_MasterIRQ
//=============================================================================
 interrupt_state_t Enter_Critical_Section( void )
{
   uint32_t temp_msr;
   temp_msr = ESYS_READ_MSR_VALUE();

   Disable_Interrupts();
   return temp_msr;
}

//=============================================================================
// Disable/Enable HWIO_MasterIRQ
//=============================================================================
 interrupt_state_t Enter_Critical_Enable_Section( void )
{
   uint32_t temp_msr;
   temp_msr = ESYS_READ_MSR_VALUE();

   Enable_Interrupts();
   return temp_msr;
}

 void Leave_Critical_Section( interrupt_state_t in_interrupt_state )
{
 Leave_Critical_Section_asm(in_interrupt_state);
 }
//=============================================================================
// HAL_OS_Get_Shutdown
//=============================================================================
bool HAL_OS_Get_Shutdown(void)
{ 
	bool shutdown_status;

	shutdown_status = IO_OS_Get_Shutdown();
	return shutdown_status;
}

//=============================================================================
// HAL_Set_HLS_Task_State
//=============================================================================
void HAL_Set_HLS_Task_State(int state)
{
	hls_task_state = state;
}

//=============================================================================
// HAL_OS_1ms_TimeBasedTask
// called in RTI 1ms interrupt
//=============================================================================
void  HAL_OS_1ms_TimeBasedTask(void) 
{
	IO_Analog_1ms_Update();
	HLS_Task_1ms();
	IO_ETC_Update_1msTimeBase();
	// IO_OS_BackGround_1ms_Status_Check();
}

//=============================================================================
// HAL_OS_1ms_Task
// 
//=============================================================================
void  HAL_OS_1ms_Task(void) 
{
	// IO_Analog_1ms_Update();
	// HLS_Task_1ms();
	// IO_ETC_Update_1msTimeBase();
	IO_OS_BackGround_1ms_Status_Check();
}

//=============================================================================
// HAL_OS_2ms_Task
//=============================================================================
void  HAL_OS_2ms_Task(void) 
{
    HLS_Task_2ms();
}

//=============================================================================
// HAL_OS_5ms_Task
//=============================================================================
void  HAL_OS_5ms_Task(void) 
{
	static uint32_t OS_5ms_CNT = 0;

	HLS_Task_5ms();

	/* hw diagnosis update functions */
	OS_5ms_CNT++;
	if (OS_5ms_CNT == 25) {
		MngINJD_125msTasks();
		MngEOSD_O2_11_Htr125msTasks();
		MngEOSD_O2_12_Htr125msTasks();
		MngPRGD_Purge_125msTasks();
		MngVVTD_125msTasks();
		OS_5ms_CNT = 0;
		MngCOND_ADC0();
	}
}
//=============================================================================
//  HAL_OS_10ms_Task
//=============================================================================
uint16_t OS_10ms_Cnt0;
uint16_t OS_10ms_Cnt1;
void  HAL_OS_10ms_Task(void)
{
	OS_10ms_Cnt0++;
	IO_GPIO_DI_Task();
	IO_Analog_10ms_Update();
	IO_Eng_Update_System_Time_Background();
	Calculate_HiRes_Engine_Speed();
	Calculate_Esc_Input_10ms();
	if ((hls_task_state == HLS_TASK_NORMAL) || (hls_task_state == HLS_TASK_100MS)) {
		HLS_Task_10ms();
	} else if (hls_task_state == HLS_TASK_10MS) {
		HLS_Task_10ms();
		HAL_Set_HLS_Task_State(HLS_TASK_100MS);
	}
	HAL_SOH_Update_Loop_Sequence_10MS();
	IO_GPIO_DO_Task();
	IO_Pulse_Update_Function();
	if(OS_10ms_Cnt1&1) {
		ScheduleKnockFastBckgLogic();
		HLS_Task_20ms();
	}
	OS_10ms_Cnt1++;
	if(OS_10ms_Cnt0 ==5) {
		HLS_Task_50ms();
		OS_10ms_Cnt0 = 0;
	}
	MngChery_Can_10ms();
	Update_DiagStatus_10ms();
	
	/* update vss counter per 10ms */
	IO_Pulse_VSS_Update_10ms();
	/* check the hls reset request status */
	IO_OS_Perform_Reset_Task();
	/* update analog diagnose */
	HAL_Analog_ADC_Diag_10ms();

	/* update engine state machine */
	UpdateVIOS_EngSpdThrsh();
	UpdateVIOS_CntrlShutdownLogic();
	UpdateVIOS_EngSt();

	/* hardware diagnosis update functions */
	MngEOSD_O2_11_Htr10msTasks();
	MngEOSD_O2_12_Htr10msTasks();
	MngESTD_7p81msTasks();
	MngEPSD_Crank7p81msTasks();
    MngCOND_AD_InputResp15p6msTasksA();
}

//=============================================================================
//  HAL_OS_100ms_Task
//=============================================================================
uint16_t OS_100ms_Cnt;
void HAL_OS_100ms_Task(void)
{
	OS_100ms_Cnt++;
	Calculate_Esc_Input_1000ms();
	ScheduleKnockSlowBckgLogic();
	if (hls_task_state == HLS_TASK_NORMAL) {
		HLS_Task_100ms();
	} else if (hls_task_state == HLS_TASK_100MS) {
		HLS_Task_100ms();
		HAL_Set_HLS_Task_State(HLS_TASK_NORMAL);
	}
	if(OS_100ms_Cnt ==5) {
		IO_Pulse_VSS_Update_500ms();
	}
	if(OS_100ms_Cnt == 10) {
		IO_Pulse_VSS_Update_500ms();
		IO_OS_OneSecond_Task();
		HLS_Task_1000ms();
		OS_100ms_Cnt = 0;
		MngChery_Can_1000ms();
		MngChery_Can_2000ms();

		/* update engine running time in 1s loop*/
		UpdateVIOS_EngRunTime();
	}
	if(!(OS_100ms_Cnt&0x01)) {
		HLS_Task_200ms();

		/* hw diagnosis update functions */
		MngEMSD_AcClutch200msTasks();
		MngEMSD_MainRelay200msTasks();
		MngEMSD_FuelPump200msTasks();
		MngEMSD_MIL200msTasks();
		MngEMSD_SVS200msTasks();
		MngEMSD_GIS200msTasks();
		MngEMSD_FanA200msTasks();
		MngEMSD_FanB200msTasks();
		MngEMSD_FileROM200msTasks();
		MngCOND_CheckCPU_31p2Tasks();
	}
	MngChery_Can_100ms();
}

//=============================================================================
//  App_Init_Task
//=============================================================================
void HAL_OS_Init_Task(void)
{
	IO_OS_Power_Status_Init();
	Initialize_HiRes_Engine_Speed();
	//chery init
	HLS_ini();
	HLS_inisyn();
	//init etc direction output
	IO_ETC_Init();
	//app fuel setup
	IO_Fuel_Syn_Init();
	//app spark setup
	IO_Spark_Syn_Init();
	//app eng status setup
	IO_Eng_Engine_Init();
	IO_Analog_1ms_Update();
	IO_Analog_10ms_Update();
	HLS_ini2();
       //knock init
	Calculate_Esc_Input_10ms();
	InitialiseESC() ;

	/*Initialize the Engine State value at power up. */
	InitVIOS_EngSt();
	InitEPSD_CrankRstToKeyOn();
	InitCOND_AD_InputRespRstKeyOn();
}


//=============================================================================
//  HAL_OS_SYN_Task
//=============================================================================
void HAL_OS_SYN_Task(void)
{

   interrupt_state_t       interrupt_status;
   
    IO_Eng_Cyl_Update();
     KnockControl58XReferenceLogic();
    //Enter critical section
    interrupt_status = Enter_Critical_Enable_Section();
     HLS_syn();
    Leave_Critical_Section(interrupt_status);
    //app fuel update
    IO_Fuel_Syn_Update();
    //  app spark update
    IO_Spark_Syn_Update();

	/* update engine state machine */
	DtrmnVIOS_RunModeCount();

	/* hardware diagnosis */
	MngESTD_RefEventTasks();
}

//=============================================================================
// HAL_OS_ToothInt_Hook
//=============================================================================
void HAL_OS_ToothInt_Hook(void)
{
 //Chery requirement
 IO_CAM_Level_Update();
 IO_Eng_ToothInt(); 
}
//=============================================================================
// HAL_OS_CAM_W_Hook
//=============================================================================
void HAL_OS_CAM_W_Hook(void)
{
	//syn of chery
	IO_VCPC_Convert_CAMW();
	IO_CAMW_Update();
	HLS_ph1();
	IO_Crank_Status_Update();
}


//=============================================================================
// HAL_OS_CAM_X_Hook
//=============================================================================
void HAL_OS_CAM_X_Hook(void)
{
	//syn of chery
	IO_VCPC_Convert_CAMX();
	IO_CAMX_Update();
	HLS_ph2();
}

//=============================================================================
// HAL_OS_CAM_READ_Hook
//=============================================================================
void HAL_OS_CAM_READ_Hook(void)
{
	//syn of chery
	IO_CAM_Status_Update();
}
//=============================================================================
// HAL_OS_KNOCK_CYL_EVENT
//=============================================================================
 void HAL_OS_KNOCK_CYL_EVENT(void) 
{

}
//=============================================================================
// HAL_OS_KNOCK_WINGATE_OFF
//=============================================================================
 void HAL_OS_KNOCK_WINGATE_OFF(void) 
{
   ESCEvent();
}

//=============================================================================
// HAL_OS_Engine_Stall_Reset
//=============================================================================
 void HAL_OS_Engine_Stall_Reset(void) 
{

   IO_Eng_Engine_Stall_Reset();
   IO_Fuel_Engine_Stall_Reset();

}

//=============================================================================
// HAL_OS_Engine_Start_Crank
//=============================================================================
 void HAL_OS_Engine_Start_Crank(void) 
{
  IO_Eng_Engine_Start_Crank();
}

//=============================================================================
// HAL_OS_Engine_First_Gap
//=============================================================================
 void HAL_OS_Engine_First_Gap(void) 
{
   IO_Eng_Engine_First_Gap();
}

//=============================================================================
// HAL_OS_Get_Battery_Remove
//=============================================================================
 bool HAL_OS_Get_Battery_Remove(void) 
{
  return Get_BatteryRemove_Status();
}

//=============================================================================
// HAL_OS_Powerdown_Callback
//=============================================================================
void HAL_OS_Powerdown_Callback(void)
{
    IO_OS_Powerdown_Callback();
}


//=============================================================================
// HAL_OS_Get_PowerFail_Flag
//=============================================================================
bool HAL_OS_Get_PowerFail_Flag(void)
{
    return IO_OS_Get_PowerFail_Flag();
}

//=============================================================================
// HAL_OS_Set_PowerFail_Flag
//=============================================================================
void HAL_OS_Set_PowerFail_Flag(bool flag)
{
    IO_OS_Set_PowerFail_Flag(flag);
}

//=============================================================================
// interrupt control routines
//=============================================================================
void Disable_1ms_interrupt(void)
{
	PIT_INTERRUPT_Set_Enable(PIT_CHANNEL_RTI, false);
}

void Enable_1ms_interrupt(void)
{
	PIT_INTERRUPT_Set_Enable(PIT_CHANNEL_RTI, true);
}

void LLD_disable_interrupt(void)
{
	Disable_Interrupts();
}

void LLD_enable_interrupt(void)
{
	Enable_Interrupts();
}




void Sinit_KeyOffDelay(void)
{
	//InitEMSD_AcClutchRstToKeyOff();
	//InitEMSD_FanxRstToKeyOff();
	//InitEMSD_FileROMRstToKeyOn();
	//InitEMSD_FuelPumpRstToKeyOff();
	//InitEMSD_MILRstToKeyOff();
	//InitEMSD_MainRelayRstToKeyOff();
	//InitEOSD_O2_11_HtrRstToKeyOff();
	//InitEOSD_O2_12_HtrRstToKeyOff();
	//InitEPSD_CamRstTo_Keyoff();
	// InitEPSD_CrankRstTo_Keyoff();
	//InitESTD_RstToKeyOff();
	//InitKNKD_RstToKeyOff();
	//InitPRGD_Purge_RstToKeyOff();
	// InitINJD_RstToKeyOff();
}



/*****************************************************************************
*                                                                            *
* Function:             Sinit_KeyOnToPowerOff                                *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Key On to Power off.              *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_KeyOnToPowerOff(void)
{
	//Sinit_KeyOffDelay();
}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_KeyOnToCrank                                   *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Key On to Crank.                  *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_KeyOnToCrank(void)
{
}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_CrankToRun                                     *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Crank To Run.                     *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_CrankToRun(void)
{
    
}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_CrankToStall                                   *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from crank to Stall.                   *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_CrankToStall (void)
{
    // InitEPSD_CamCrankToStall();
    InitEPSD_CrankCrankToStall();
}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_RunToPowerOffDelay                             *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Run to Power off Delay.           *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_RunToPowerOffDelay(void)
{
	// InitEPSD_CamRunToPowerOffDelay();
	InitEPSD_CrankRunToPowerOffDelay();
	// Sinit_KeyOffDelay();
}


/*****************************************************************************
*                                                                            *
* Function:             Sinit_RunToCrank                                     *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Run To Crank.                     *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_RunToCrank(void)
{
  
}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_StallToPowerOffDelay                           *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Stall to Power off Delay.         *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_StallToPowerOffDelay(void)
{
	// Sinit_KeyOffDelay();
}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_StallToCrank                                   *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Stall to Crank.                   *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_StallToCrank(void)
{

}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_PowerOffDelayToKeyOn                           *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Power off delay to Key on.        *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_PowerOffDelayToKeyOn(void)
{
    InitEPSD_CrankRstToKeyOn();
    InitCOND_AD_InputRespRstKeyOn();
}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_PowerOffDelayToShutDwn                         *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Power off Delay to Shut down.     *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_PowerOffDelayToShutDwn(void)
{
   
}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_ShutdownInProcessToKeyOff                      *
* Description:          This procedure will spawn all routines that need to  *
*                       be executed on a Shut down In Process To Key Off.    *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_ShutdownInProcessToKeyOff(void)
{
	// InitESTD_ShutdownInProgToKeyOn();
}

/*****************************************************************************
*                                                                            *
* Function:             Sinit_ShutdownInProcessToKeyOn                       *
* Description:          This procedure will Initialize all routines need to  *
*                       re-initialize from Shut down In Process To Key On.   *
*                                                                            *
* Parameters:           None                                                 *
* Return:               None                                                 *
******************************************************************************/
void Sinit_ShutdownInProcessToKeyOn(void)
{
    InitEPSD_CrankRstToKeyOn();
}

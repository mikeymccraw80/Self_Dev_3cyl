
//=============================================================================
// include files
//=============================================================================
#include "dd_intc.h"
#include "dd_pit_interface.h"
#include "os_type.h"
#include "dd_pfi_interface.h"
#include "io_conversion.h"
#include "dd_ecsm.h"
#include "hal_emulated_eeprom.h"
#include "os_type.h"

void OS_LoResTasks_Hook(void);
void OS_KnockEvntTasks_Hook(void);
void OS_WinGateTasks_Hook(void); 

//=============================================================================
//static variables
//=============================================================================
bool APPLICATION_VCP0_TASK;
bool APPLICATION_VCP1_TASK;
bool APPLICATION_VCP_TASK;
bool APPLICATION_6X_EVENT_TASK;
bool CAM_CYLINDER_EVENT_TASK;
bool APPLICATION_CYLINDER_EVENT_TASK;
bool APPLICATION_TDC_EVENT_TASK;
bool APPLICATION_KNOCK_WINDOW_CLOSED_TASK;
bool APPLICATION_KNOCK_CYL_EVENT_TASK;


//=============================================================================
// OS_SCHEDULER_Cylinder_Event
//=============================================================================
void OS_SCHEDULER_Cylinder_Event(void)
{ 
  APPLICATION_CYLINDER_EVENT_TASK = true;

CRANK_High_Priority_Cylinder_Event();  
  INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH0_CH, true);  
}

//=============================================================================
// OS_SCHEDULER_CAM_Cylinder_Event
//=============================================================================

void OS_SCHEDULER_CAM_Cylinder_Event(void)
{
  CAM_CYLINDER_EVENT_TASK = true;
  INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH0_CH, true);  
}

//=============================================================================
// OS_SCHEDULER_VCP0_Event
//=============================================================================
void OS_SCHEDULER_VCP0_Event(void)
{
  APPLICATION_VCP0_TASK = true;
  INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH0_CH, true);  
}

//=============================================================================
// OS_SCHEDULER_VCP1_Event
//=============================================================================
void OS_SCHEDULER_VCP1_Event(void)
{
  APPLICATION_VCP1_TASK = true;
  INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH0_CH, true);  
}

//=============================================================================
// OS_SCHEDULER_VCP_Event
//=============================================================================
void OS_SCHEDULER_VCP_Event(void)
{
  APPLICATION_VCP_TASK = true;
  INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH0_CH, true);  
}

//=============================================================================
// OS_SCHEDULER_6X_Event
//=============================================================================

void OS_SCHEDULER_6X_Event(void)
{
  APPLICATION_6X_EVENT_TASK = true;
  INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH0_CH, true);  
}

//=============================================================================
// OS_SCHEDULER_TDC_Event
//=============================================================================
void OS_SCHEDULER_TDC_Event(void)
{
  APPLICATION_TDC_EVENT_TASK = true;
  INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH0_CH, true);  
}

//=============================================================================
// OS_SCHEDULER_KNOCK_WINDOW_CLOSED_Event
//=============================================================================
void OS_SCHEDULER_KNOCK_WINDOW_CLOSED_Event(void)
{
  APPLICATION_KNOCK_WINDOW_CLOSED_TASK = true;
  INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH0_CH, true);  
}
//=============================================================================
// OS_SCHEDULER_KNOCK_CYL_Event
//=============================================================================
void OS_SCHEDULER_KNOCK_CYL_Event(void)
{
  APPLICATION_KNOCK_CYL_EVENT_TASK = true;
  INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH0_CH, true);  
}

//=============================================================================
// OS_SW_INTC_Control, software interrupt trigered by Event
//=============================================================================
void OS_SW_INTC_Control( void)
{
	INTC_INTERRUPT_Clear_Pending(INTC_CHANNEL_SOFTWARE_CH0_CH );

	if (APPLICATION_KNOCK_WINDOW_CLOSED_TASK) {
		OS_WinGateTasks_Hook();
		APPLICATION_KNOCK_WINDOW_CLOSED_TASK = false;
	}

	if (APPLICATION_TDC_EVENT_TASK) {
		OS_KnockEvntTasks_Hook();
		APPLICATION_TDC_EVENT_TASK = false;
	}

	if (APPLICATION_CYLINDER_EVENT_TASK) {
		Enter_OSThroughputMeasure(CeOSTK_SEG_CYLINDER_EVENT); //measuring cylinder event time
		OS_LoResTasks_Hook();
		SPARK_Process_Cylinder_Event();
		PFI_Process_Cylinder_Event();
		CAM_Application_Event_Tasks();
		APPLICATION_CYLINDER_EVENT_TASK = false;
		Leave_OSThroughputMeasure(CeOSTK_SEG_CYLINDER_EVENT); //measuring cylinder event time
	}

	if (CAM_CYLINDER_EVENT_TASK) {
		//CAM_Lo_Res_Event_Tasks();
		CAM_CYLINDER_EVENT_TASK = false;
	}

	if (APPLICATION_6X_EVENT_TASK) {
		//OS_6X_Tasks_Hook();
		APPLICATION_6X_EVENT_TASK = false;
	}

	if (APPLICATION_VCP_TASK) {
		//OS_VCPC_58X_Event_Hook();
		APPLICATION_VCP_TASK = false;
	}

	if (APPLICATION_VCP1_TASK) {
		//OS_VCPC_camX_Task02_Hook();
		APPLICATION_VCP1_TASK = false;
	}

	if (APPLICATION_VCP0_TASK) {
		//  OS_VCPC_camX_Task00_Hook();
		APPLICATION_VCP0_TASK = false;
	}
}

//=============================================================================
// Service_ECSM_Error, Flash ECC service routine, called by core excepiton
//=============================================================================
#pragma section DATA " " ".nc_nvram"
uint32_t HAL_Last_ECC_Address;
#pragma section DATA " " ".bss"

void Service_ECSM_Error(void)
{
   uint32_t *address;

   if ( (bitfield8_t)1 == ECSM.ESR.F.RNCE )
   {
      HAL_Last_ECC_Address = ECSM.REAR;
      // Fix RAM ECC error
      address = (uint32_t *)HAL_Last_ECC_Address;
	  address -= address%4;
      *address = 0;
      ECSM.ESR.F.RNCE = 1;
   }
   else if ((bitfield8_t)1 == ECSM.ESR.F.FNCE )
   {
      HAL_Last_ECC_Address = ECSM.FEAR;
      EEPROM_Fix_ECC_Error(HAL_Last_ECC_Address);
      INST_Fix_Backup_Page_ECC_Error(HAL_Last_ECC_Address);
      ECSM.ESR.F.FNCE = 1;
   }
   else
   {
      // Not Implemented
   }
}




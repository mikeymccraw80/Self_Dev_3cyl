
//=============================================================================
// include files
//=============================================================================
#include "dd_intc.h"
#include "dd_pit_interface.h"
#include "os_type.h"
///
#include "dd_pfi_interface.h"
#include "io_conversion.h"
#include "HLS.h"

void OS_LoResTasks_Hook(void);

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
bool CAM_CYLINDER_EVENT_TASK;


//=============================================================================
// OS_SCHEDULER_Cylinder_Event
//=============================================================================
void OS_SCHEDULER_Cylinder_Event(void)
{ 
  APPLICATION_CYLINDER_EVENT_TASK = true;
   
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
// OS_SW_INTC_Control
//=============================================================================
 void OS_SW_INTC_Control( void)
{

 INTC_INTERRUPT_Clear_Pending(INTC_CHANNEL_SOFTWARE_CH0_CH );
 
 if(APPLICATION_KNOCK_WINDOW_CLOSED_TASK)
 {
  //OS_WinGateTasks_Hook();
 
  APPLICATION_KNOCK_WINDOW_CLOSED_TASK = false;
 }
 else if(APPLICATION_TDC_EVENT_TASK)
 {
  //OS_KnockEvntTasks_Hook();
  APPLICATION_TDC_EVENT_TASK = false;
 }
else if(APPLICATION_CYLINDER_EVENT_TASK)
{
  OS_LoResTasks_Hook();

  APPLICATION_CYLINDER_EVENT_TASK = false;
}
else if(CAM_CYLINDER_EVENT_TASK)
{
 //CAM_Lo_Res_Event_Tasks();
  CAM_CYLINDER_EVENT_TASK = false;
}

else if(APPLICATION_6X_EVENT_TASK)
{
 //OS_6X_Tasks_Hook();
  APPLICATION_6X_EVENT_TASK = false;
}


else if(APPLICATION_VCP_TASK)
{
//OS_VCPC_58X_Event_Hook();
  APPLICATION_VCP_TASK = false;
}

else if(APPLICATION_VCP1_TASK)
{
 //OS_VCPC_camX_Task02_Hook();
  APPLICATION_VCP1_TASK = false;
}

else if(APPLICATION_VCP0_TASK)
{
 //  OS_VCPC_camX_Task00_Hook();
  APPLICATION_VCP0_TASK = false;
}


}




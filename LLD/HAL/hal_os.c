//=============================================================================
// include files
//=============================================================================
#include "hal_os.h"
#include "HLS.h"
#include "io_interface_eng.h"
#include "io_interface_vcpc.h"
#include "io_interface_pulse.h"
#include "io_interface_analog.h"
#include "io_interface_fuel.h"
#include "io_interface_spark.h"
#include "io_interface_os.h"
#include "io_interface_gpio.h"
//#include "hal_diag.h"


//extern void Update_DiagStatus_10ms(void);

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
// HAL_OS_1ms_Task
//=============================================================================
void  HAL_OS_1ms_Task(void) 
 {
     IO_Analog_1ms_Update();
     HLS_Task_1ms();
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
     HLS_Task_5ms();
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
    HLS_Task_10ms();
    IO_GPIO_DO_Task();
    IO_Pulse_Update_Function();
    if(OS_10ms_Cnt1&1)
    {
       HLS_Task_20ms();
    }
   OS_10ms_Cnt1++;
   if(OS_10ms_Cnt0 ==5)
   {
        HLS_Task_50ms();
        OS_10ms_Cnt0 = 0;
    }
   

   Update_DiagStatus_10ms();
 }

//=============================================================================
//  HAL_OS_100ms_Task
//=============================================================================
uint16_t OS_100ms_Cnt;
  void  HAL_OS_100ms_Task(void)
{

   OS_100ms_Cnt++;
   HLS_Task_100ms();
   if(OS_100ms_Cnt ==5)
   {
     IO_Pulse_VSS_Update_500ms();
   }
   if(OS_100ms_Cnt ==10)
   {
      IO_Pulse_VSS_Update_500ms();
      IO_OS_OneSecond_Task();
      HLS_Task_1000ms();
      OS_100ms_Cnt = 0;
   }
   
   if(!(OS_100ms_Cnt&&0x01))
   {
    HLS_Task_200ms();
   }

}

//=============================================================================
//  App_Init_Task
//=============================================================================
  void HAL_OS_Init_Task(void)
  {

    IO_OS_Power_Status_Init();
    //chery init	
    HLS_ini();
    HLS_inisyn();
    //app fuel setup
    IO_Fuel_Syn_Init();
    //app spark setup
    IO_Spark_Syn_Init();
    //app eng status setup
    IO_Eng_Engine_Init();
	
    HLS_ini2();	
  }


//=============================================================================
//  HAL_OS_SYN_Task
//=============================================================================
 void HAL_OS_SYN_Task(void)
 {
     IO_Eng_Cyl_Update();
     HLS_syn();
     //app fuel update
     IO_Fuel_Syn_Update();    
     //  app spark update
     IO_Spark_Syn_Update();	
    
 }

//=============================================================================
// HAL_OS_ToothInt_Hook
//=============================================================================
void HAL_OS_ToothInt_Hook(void)
{
 //Chery requirement
 IO_Eng_ToothInt(); 
}
//=============================================================================
// HAL_OS_CAM_W_Hook
//=============================================================================
void HAL_OS_CAM_W_Hook(void)
{
   //syn of chery
   IO_VCPC_Convert_CAMW();
   HLS_ph1();	 
}


//=============================================================================
// HAL_OS_CAM_X_Hook
//=============================================================================
void HAL_OS_CAM_X_Hook(void)
{
   //syn of chery
   IO_VCPC_Convert_CAMX();
   HLS_ph2();	 
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


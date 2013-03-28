
//=============================================================================
// include files
//=============================================================================
#include "io_config_pit.h"
#include "dd_pit_interface.h"
#include "dd_dma_interface.h"
#include "dd_mios_interface.h"
#include "io_config_mios.h"
#include "dd_dspi_interface.h"
#include "dd_fi_interface.h"

//tempoary
#include "soh.h"
#include "dd_vsep_est_select.h"


//=============================================================================
// OS_Startup_Hook
//=============================================================================

 void OS_Startup_Hook(void)
{
  //set up os loop time 10ms
  PIT_TIMER_Set_Value( PIT_CHANNEL_RTI, RTI_LOAD_VALUE_1MS);
  PIT_INTERRUPT_Set_Enable(PIT_CHANNEL_RTI, true);

    //enable QADC DMA time base scan
  DMA_Enable_Request(DMA_CHANNEL_QADC_FISR4_RFDF_4);
  DMA_Enable_Request(DMA_CHANNEL_QADC_FISR4_CFFF_4);

  HAL_OS_Init_Task();   

  CAN_RX_B15_Config();
  //app fuel setup
  IO_Fuel_Syn_Init();
 //app spark setup
  IO_Spark_Syn_Init();

   FI_Initialize();


}
//=============================================================================
//MngOSTK_1msTasks
//=============================================================================

 void MngOSTK_1msTasks(void)
{
  HAL_OS_1ms_Task();
}
//=============================================================================
//MngOSTK_5msTasks
//=============================================================================
void MngOSTK_5msTasks(void)
{
  HLS_Task_5ms();
}
//=============================================================================
//MngOSTK_10msTasks
//=============================================================================
uint16_t test_cnt;
void MngOSTK_10msTasks(void)
{

  SWT_Service_WatchDog();
  VSEP_SPI_Scheduler_Manage_Periodic();
  IO_GPIO_DI_Task();
  HAL_OS_10ms_Task(); 
  IO_GPIO_DO_Task();
  IO_Pulse_Update_Function();
  HAL_CAN_10ms_Task();
  test_cnt++;
  if (test_cnt == 3)
  {
     test_cnt=0;
     SOH_VSEP_CR_Service();
  } 
  
}

//=============================================================================
// MngOSTK_100msTasks
//=============================================================================	
void MngOSTK_100msTasks(void)
{
  HAL_OS_100ms_Task();
  FI_Get_current_Count();
}
//=============================================================================
// OS_Free_Time_Tasks_Hook
//=============================================================================
void OS_Free_Time_Tasks_Hook(void)
{

}

//=============================================================================
// OS_TimeBasedTask1ms
//=============================================================================
 void OS_TimeBasedTask1ms(void) 
{
    
}


//=============================================================================
// OS_TimeBasedTask5ms
//=============================================================================
 void OS_TimeBasedTask5ms(void) 
{
    CRANK_EngineStall_PerioCheck();   
}


//=============================================================================
//OS_TimeBasedTask10ms
//=============================================================================
void OS_TimeBasedTask10ms(void) 
{
    //wait for update   
     VSEP_Fault_Task_7_8ms();
}

//=============================================================================
// OS_LoResTasks_Hook
//=============================================================================
void OS_LoResTasks_Hook(void)
{
   //syn of chery
   HAL_OS_SYN_Task();
   //app fuel update
   IO_Fuel_Syn_Update();    
   //  app spark update
   IO_Spark_Syn_Update();	 
}

//=============================================================================
// OS_CAM_W_Hook
//=============================================================================
void OS_CAM_W_Hook(void)
{
   //syn of chery
	 
}


//=============================================================================
// OS_CAM_X_Hook
//=============================================================================
void OS_CAM_X_Hook(void)
{
   //syn of chery
	 
}

//=============================================================================
// OS_TimeBasedTask5ms
//=============================================================================
 void OS_Engine_Stall_Reset(void) 
{
IO_Fuel_Engine_Stall_Reset();

}


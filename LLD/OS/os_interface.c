
//=============================================================================
// include files
//=============================================================================
#include "io_config_pit.h"
#include "io_config_mios.h"
#include "dd_pit_interface.h"
#include "dd_dma_interface.h"
#include "dd_mios_interface.h"
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

   // turn on Time Off Delay signal 
   //Activate_TimeOffDelay
   HAL_GPIO_SET_TODO_Enable(true);

  HAL_OS_Init_Task();   

  CAN_RX_B15_Config();
  
   FI_Initialize();
   
   CCP_Initialize();


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
uint16_t test_cnt_30ms;
void MngOSTK_10msTasks(void)
{

  SWT_Service_WatchDog();
  VSEP_SPI_Scheduler_Manage_Periodic();

  HAL_OS_10ms_Task(); 

  HAL_CAN_10ms_Task();
  test_cnt_30ms++;
  if (test_cnt_30ms == 3)
  {
     test_cnt_30ms=0;
     SOH_VSEP_CR_Service();
  } 

   /* CCP 10ms Trigger */
   CCP_Trigger_Event_Channel( 10 );
  
}

//=============================================================================
// MngOSTK_100msTasks
//=============================================================================	
uint16_t test_cnt_500ms;
void MngOSTK_100msTasks(void)
{

 FI_Update_Count_Time();
 HAL_OS_100ms_Task();
  /* CCP 125ms Task 0 Trigger */
  CCP_Trigger_Event_Channel( 11 );
   test_cnt_500ms++;
  if (test_cnt_500ms == 5)
  {
     test_cnt_500ms=0;
         /* CCP 500ms Task 0 Trigger */
    CCP_Trigger_Event_Channel( 25 );
  }


}
//=============================================================================
// OS_Free_Time_Tasks_Hook
//=============================================================================
void OS_Free_Time_Tasks_Hook(void)
{
 CCP_Periodic_Task();

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
   /* CCP LoRes Trigger */
   CCP_Trigger_Event_Channel( 0 );
}

//=============================================================================
// OS_LoResTasks_Hook
//=============================================================================
void OS_ToothInt_Hook(void)
{
   HAL_OS_ToothInt_Hook(); 
}
//=============================================================================
// OS_CAM_W_Hook
//=============================================================================
void OS_CAM_W_Hook(void)
{
   HAL_OS_CAM_W_Hook();
}


//=============================================================================
// OS_CAM_X_Hook
//=============================================================================
void OS_CAM_X_Hook(void)
{  
   HAL_OS_CAM_X_Hook();
}

//=============================================================================
// OS_TimeBasedTask5ms
//=============================================================================
 void OS_Engine_Stall_Reset(void) 
{
  HAL_OS_Engine_Stall_Reset();
}

//=============================================================================
// OS_Engine_Start_Crank
//=============================================================================
 void OS_Engine_Start_Crank(void) 
{
   HAL_OS_Engine_Start_Crank();
}

//=============================================================================
// OS_Engine_First_Gap
//=============================================================================
 void OS_Engine_First_Gap(void) 
{
    HAL_OS_Engine_First_Gap();
}



 



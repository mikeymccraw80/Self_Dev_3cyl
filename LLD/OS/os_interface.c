
//=============================================================================
// include files
//=============================================================================
#include "io_config_pit.h"
#include "io_config_mios.h"
#include "dd_pit_interface.h"
#include "dd_dma_interface.h"
#include "dd_mios_interface.h"
#include "dd_dspi_interface.h"
#include "dd_sci_interface.h"
#include "kw2exec.h"
#include "dd_fi_interface.h"
#include "dd_l9958_interface.h"
#include "dd_vsep_fault_interface.h"
#include "dd_crank_interface.h"
#include "v_ignit.h"
#include "soh.h"
#include "dd_vsep_est_select.h"
#include "intr_ems.h"


//=============================================================================
// OS_Startup_Hook
//=============================================================================
void OS_Startup_Hook(void)
{
    HAL_GPIO_SET_TODO_Enable(true);

    HAL_OS_Init_Task();

    KeywordExecutive(CwKW2000_Initializes);

    /* update ems initial parameters */
    Init_IntrParameter();

    /* init power source status */
    InitializePowerSource();

    /* init soh part, this part must placed behind nvram erase */
    SOH_ETC_Initialize(true);

    //enable QADC DMA time base scan
    DMA_Enable_Request(DMA_CHANNEL_QADC_FISR1_RFDF_1);
    DMA_Enable_Request(DMA_CHANNEL_QADC_FISR1_CFFF_1);

    // set up os loop time 10ms
    PIT_TIMER_Set_Value( PIT_CHANNEL_RTI, RTI_LOAD_VALUE_1MS);
    PIT_INTERRUPT_Set_Enable(PIT_CHANNEL_RTI, true);
}
//=============================================================================
//MngOSTK_1msTasks
//=============================================================================

void MngOSTK_1msTasks(void)
{
	HAL_OS_1ms_Task();
}

//=============================================================================
//MngOSTK_2msTasks
//=============================================================================
void MngOSTK_2msTasks(void)
{
    HAL_OS_2ms_Task();
}

//=============================================================================
//MngOSTK_5msTasks
//=============================================================================
void MngOSTK_5msTasks(void)
{
    HAL_OS_5ms_Task();
}

//=============================================================================
//MngOSTK_10msTasks
//=============================================================================
static int soh_service_cnt_30ms;
void MngOSTK_10msTasks(void)
{
    /* call device driver layer functions */
    VSEP_SPI_SCHEDULER_10MS();
    VSEP_Fault_Task_10MS();
    L9958_FAULT_Diagnose_Update();

#ifndef ENABLE_ETC_SOH_MODULE
    SWT_Service_WatchDog();
    /* call soh service */
    soh_service_cnt_30ms++;
    if (soh_service_cnt_30ms == 3) {
        soh_service_cnt_30ms=0;
        SOH_VSEP_CR_Service();
    }
#endif
    
    /* call hal layer callback functions */
    HAL_OS_10ms_Task(); 

    /* CCP 10ms Trigger */
    CCP_Trigger_Event_Channel( 10 );
    /* update kw2000 state machine */
    KeywordExecutive(CwKW2000_RunMode);

    /* update ignition status */
    UpdateIgnitionState_10MS();

    /* update power source status */
    PowerSourceStatus_EveryLoop();
}

//=============================================================================
// MngOSTK_100msTasks
//=============================================================================	
static uint16_t test_cnt_500ms;
void MngOSTK_100msTasks(void)
{
    FI_Update_Count_Time();
    HAL_OS_100ms_Task();
    /* CCP 125ms Task 0 Trigger */
    CCP_Trigger_Event_Channel( 11 );
    test_cnt_500ms++;
    if (test_cnt_500ms == 5) {
        test_cnt_500ms=0;
        /* CCP 500ms Task 0 Trigger */
        CCP_Trigger_Event_Channel( 25 );
    }
    
    /* update ems parameters */
    Intr_16msTasks();
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
#ifdef ENABLE_ETC_SOH_MODULE
    SOH_ETC_Update_RTI_Array();
#endif
    HAL_OS_1ms_TimeBasedTask();
}

//=============================================================================
// OS_TimeBasedTask2ms
//=============================================================================
void OS_TimeBasedTask2ms(void)
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

}

//=============================================================================
// OS_LoResTasks_Hook
//=============================================================================
void OS_LoResTasks_Hook(void)
{
    /* call the interface callback, spark fuel... */
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
// OS_CAM_READ_Hook
//=============================================================================
void OS_CAM_READ_Hook(void)
{
    HAL_OS_CAM_READ_Hook();
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
//=============================================================================
// OS_KnockEvntTasks_Hook
//=============================================================================
 void OS_KnockEvntTasks_Hook(void) 
{
   HAL_OS_KNOCK_CYL_EVENT();
}

//=============================================================================
// OS_WinGateTasks_Hook
//=============================================================================
 void OS_WinGateTasks_Hook(void) 
{
   HAL_OS_KNOCK_WINGATE_OFF();
}

//=============================================================================
// OS_Powerdown_Callback
//=============================================================================
OS_Powerdown_Callback(void)
{
    HAL_OS_Powerdown_Callback();
}

 



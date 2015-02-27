//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_output_cycling_EMC.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:             %
//
// %version:         6 %
//
//=============================================================================
#if 0
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_config.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_analog.h"
#include "mg_hal_discrete.h"
#include "mg_hal_PWM.h"
#include "mg_hal_est.h"
#include "mg_hal_etc.h"
#include "mg_hal_inj.h"
#include "mg_hal_fault.h"
#include "mg_hal_timer.h"
#ifdef __MG_C2MIO_USED
#include "mg_C2MIO_fault_diagnostic_history_test.h"
#include "mg_C2MIO_fault_diagnostic_clear_test.h"
#endif
#ifdef __MG_VSEP_USED
#include "mg_VSEP_fault_diagnostic_history_test.h"
#include "mg_VSEP_fault_diagnostic_clear_test.h"
#endif

#define THERMAL_120_CYCLING

#define DIAG_HISTORY      0x06
#define DIAG_CLEAR          0x0E


void mg_output_cycling_EMC(void)
{
    uint8_t idx;

    mg_HAL_Output_Cycling_EMC_Init();

#ifdef THERMAL_CYCLING
    mg_HAL_Output_Cycling_Thermal_Config();
#endif
#ifdef EMC_CYCLING
    mg_HAL_Output_Cycling_EMC_Config();
#endif
#ifdef THERMAL_120_CYCLING
    mg_HAL_Output_Cycling_Thermal_Config_120();
#endif
    mg_HAL_Service_WatchDog();

    if (mg_HAL_Get_EST_Sequential_Mode())
    {
        mg_HAL_EST_Set_Sequential_Mode(true);
    }
    else
    {
        mg_HAL_EST_Set_Sequential_Mode(false);
    }
    mg_HAL_EST_Init(MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME,  MG_HAL_EST_GROUP.on_time_us,
        MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.delay_time_us, 0);
    mg_HAL_ETC_Discrete_Enable(true);
    mg_HAL_ETC_Discrete_Direction(false);
    mg_HAL_ETC_Set_Freq_And_Duty();
    for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++)
    {
        if (PWM == MG_HAL_DISCRETE_OUT_GROUP[idx].type)
        {
            mg_HAL_PWM_Set_Discrete_Out_Group_Frequency_And_Duty_Immediate(idx);
        }
        else if (PWM_REVERSE == MG_HAL_DISCRETE_OUT_GROUP[idx].type)
        {
            mg_HAL_PWM_Set_Discrete_Out_Group_Frequency_And_Duty(idx);
        }
        else
        {
            /* do in while */
        }
        mg_HAL_Service_WatchDog();
    }

    mg_HAL_Discrete_Set_FSE(true);
    mg_HAL_Discrete_Set_GEN_ENABLE(true);

    mg_HAL_EST_Start();

   // stay in cycling until a reset occurs or IGN OFF
    while(1)
    {
        mg_HAL_EST_cycling();
        mg_HAL_Injector_Discrete_Cycling();
        mg_HAL_PWM_Discrete_Out_Cycling();
#if ((defined THERMAL_CYCLING) || (defined EMC_CYCLING))
        mg_HAL_ETC_Discrete_Cycling_Validation();
#endif
#ifdef THERMAL_120_CYCLING
        mg_HAL_ETC_Discrete_Cycling_120();
#endif

        if (DIAG_HISTORY == MG_MAILBOX_IN(testid))
        {
#ifdef __MG_C2MIO_USED
            mg_C2MIO_fault_diagnostic_history_test();
#endif
#ifdef __MG_VSEP_USED
            mg_VSEP_fault_diagnostic_history_test();
#endif
            MG_MAILBOX_IN(testid) = 0xFF;
        }
        if (DIAG_CLEAR == MG_MAILBOX_IN(testid))
        {
#ifdef __MG_C2MIO_USED
            mg_C2MIO_fault_diagnostic_clear_test();
#endif
#ifdef __MG_VSEP_USED
            mg_VSEP_fault_diagnostic_clear_test();
#endif
            MG_MAILBOX_IN(testid) = 0xFF;
        }
        mg_HAL_Service_WatchDog();
    }
    mg_HAL_Output_Cycling_EMC_Uninit();
}
#endif
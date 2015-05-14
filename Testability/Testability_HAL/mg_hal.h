#ifndef MG_HAL_H
#define MG_HAL_H
#include "io_config_tpu.h"
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_hal.h %
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
typedef enum
{
    MG_PWMIE_INDEX_58XPOS,
    MG_PWMIE_INDEX_VSSFI,
    MG_PWMIE_INDEX_CAM1,
    MG_PWMIE_INDEX_CAM2,
    MG_PWMIE_INDEX_WSSFI,
    MG_PWMIE_INDEX_ENSFI,
    MG_PWMIE_INDEX_MAX
} MG_PWMIE_INDEX_T;

extern const TPU_CHANNEL_Configuration_T MG_TPU_CONFIG_IC_PWMIE[MG_PWMIE_INDEX_MAX];

void mg_HAL_Entey_Critical(void);
void mg_HAL_Exit_Critical(void);
void mg_HAL_Service_WatchDog(void);
void mg_HAL_SWT_Enable_WatchDog(bool state);
void mg_HAL_Internal_Device_Init(void);
void mg_HAL_External_Device_Init(void);
void mg_HAL_SPI_Timer_Enable(bool state);
void mg_HAL_Output_Cycling_Init(void);
void mg_HAL_Output_Cycling_Uninit(void);
void mg_HAL_Output_Cycling_Config(void);
void mg_HAL_Output_Cycling_Diagnostic(uint8_t *pch);
void mg_HAL_Output_Cycling_EMC_Init(void);
void mg_HAL_Output_Cycling_EMC_Uninit(void);
void mg_HAL_Output_Cycling_EMC_Config(void);
void mg_HAL_Output_Cycling_Thermal_Config(void);
void mg_HAL_Output_Cycling_Thermal_Config_120(void);
void mg_HAL_Output_Cycling_Validation_Init(void);
void mg_HAL_Output_Cycling_Validation_Uninit(void);
void mg_HAL_Output_Cycling_Validation_Config(void);
void mg_HAL_Disable_CAN_10ms_Task_Timer(void);

#endif /* end of include guard: MG_HAL_H */

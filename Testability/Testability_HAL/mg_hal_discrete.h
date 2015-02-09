#ifndef MG_HAL_DISCRETE_H
#define MG_HAL_DISCRETE_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_hal_discrete.h %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:         %
//
// %version:         1 %
//
//=============================================================================
#include "mg_config.h"


void mg_HAL_Discrete_Set_Discrete_Out_Group_Value(uint8_t index, bool state);
void mg_HAL_Discrete_Set_ELOAD1(bool state);
void mg_HAL_Discrete_Set_ELOAD2(bool state);
void mg_HAL_Discrete_Set_BRKLDI(bool state);
void mg_HAL_Discrete_Set_FPO1(bool state);
void mg_HAL_Discrete_Set_FPO2(bool state);
void mg_HAL_Discrete_Set_FPO3(bool state);
void mg_HAL_Discrete_Set_FPO4(bool state);
void mg_HAL_Discrete_Set_FPO5(bool state);
void mg_HAL_Discrete_Set_FPO6(bool state);
void mg_HAL_Discrete_Set_FPO7(bool state);
void mg_HAL_Discrete_Set_FSE(bool state);
void mg_HAL_Discrete_Set_TACH(bool state);
void mg_HAL_Discrete_Set_ACREQDI(bool state);
void mg_HAL_Discrete_Set_PSPSDI(bool state);
void mg_HAL_Discrete_Set_MIDACDI(bool state);
void mg_HAL_Discrete_Set_Fuel_Pump_Low(bool state);
void mg_HAL_Discrete_Set_FAN1(bool state);
void mg_HAL_Discrete_Set_FAN2(bool state);
void mg_HAL_Discrete_Set_O2_1_Pump_Current(bool state);
void mg_HAL_Discrete_Set_O2_2_Pump_Current(bool state);
void mg_HAL_Discrete_Set_GEN_No_Affect(bool state);
void mg_HAL_Discrete_Set_GEN_ENABLE(bool state);
void mg_HAL_Discrete_Set_TODO(bool state);
#ifdef __MG_C2PS_USED
void mg_HAL_Discrete_Set_C2PS_WTO(bool state);
void mg_HAL_Discrete_Set_C2PS_WP_Config(bool state);
void mg_HAL_Discrete_Set_C2PS_DRVENS(bool state);
void mg_HAL_Discrete_Set_C2PS_VIGNF(bool state);
#endif
bool mg_HAL_Discrete_Get_Discrete_In_Group(uint8_t index);
bool mg_HAL_Discrete_Get_BRkSW(void);
bool mg_HAL_Discrete_Get_ELOAD1(void);
bool mg_HAL_Discrete_Get_ELOAD2(void);

void mg_HAL_Discrete_Reconfigure_CAL(void);


#endif /* end of include guard: MG_HAL_DISCRETE_OUT_H */

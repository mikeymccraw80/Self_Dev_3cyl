#ifndef MG_HAL_SOH_H
#define MG_HAL_SOH_H

void mg_HAL_SOH_Init(bool Is_Disarmed);
uint32_t mg_HAL_SOH_Get_Challenge(void);
uint32_t mg_HAL_SOH_Calculate_Response(uint32_t challenge);
void mg_HAL_SOH_Set_Response(uint32_t response);
void mg_HAL_Set_SOH_Test_Flag(uint8_t flag);
uint8_t mg_HAL_Get_SOH_Test_Flag(void);

#endif

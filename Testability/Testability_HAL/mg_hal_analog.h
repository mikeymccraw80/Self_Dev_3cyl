#ifndef MG_HAL_ANALOG_H
#define MG_HAL_ANALOG_H

uint16_t mg_HAL_Analog_Get_Analog_Value(uint8_t index);
uint16_t mg_HAL_Analog_Get_Baro_Pressure(void);
uint16_t mg_HAL_Analog_Get_Baro_Temperature(void);
uint16_t mg_HAL_Analog_Get_HWCFG(void);
uint16_t mg_HAL_Analog_Get_TPS1(void);
uint16_t mg_HAL_Analog_Get_TPS2(void);
uint16_t mg_HAL_Analog_Get_Knock(uint8_t index);

#endif

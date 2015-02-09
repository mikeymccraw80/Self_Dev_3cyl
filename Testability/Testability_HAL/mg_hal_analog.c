#include "mg_hal_config.h"
#include "io_analog.h"

uint16_t mg_HAL_Analog_Get_Analog_Value(uint8_t index)
{
    uint16_t value;
    if (NULL != MG_HAL_ANALOG_GROUP[index].io)
    {
        value = IO_ANALOG_Get_Immediate_Value(MG_HAL_ANALOG_GROUP[index].io);
    }
    else
    {
        value = 0;
    }
    return value;
}

uint16_t mg_HAL_Analog_Get_Baro_Pressure(void)
{
    return IO_ANALOG_Get_Immediate_Value(MG_HIODEVICE_BARO_PRESSURE);
}

uint16_t mg_HAL_Analog_Get_Baro_Temperature(void)
{
    return IO_ANALOG_Get_Immediate_Value(MG_HIODEVICE_BARO_TEMPERATURE);
}

uint16_t mg_HAL_Analog_Get_HWCFG(void)
{
    return IO_ANALOG_Get_Immediate_Value(&HWCFGVI);
}

uint16_t mg_HAL_Analog_Get_TPS1(void)
{
    return IO_ANALOG_Get_Immediate_Value(&TPS1VI);
}

uint16_t mg_HAL_Analog_Get_TPS2(void)
{
    return IO_ANALOG_Get_Immediate_Value(&TPS2VI);
}

uint16_t mg_HAL_Analog_Get_Knock(uint8_t index)
{
    uint16_t value;
    if (NULL != MG_HAL_KNOCK_GROUP[index].io)
    {
        value = IO_ANALOG_Get_Immediate_Value(MG_HAL_KNOCK_GROUP[index].io);
    }
    else
    {
        value = 0;
    }
    return value;
}

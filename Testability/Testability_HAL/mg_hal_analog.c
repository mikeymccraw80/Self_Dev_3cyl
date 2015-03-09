#include "mg_hal_config.h"
// #include "io_analog.h"
#include "dd_qadc_interface.h"

uint16_t mg_HAL_Analog_Get_Analog_Value(uint8_t index)
{
    uint16_t value;
    if (MG_HIODEVICE_NULL != MG_HAL_ANALOG_GROUP[index])
    {
        value = QADC_Analog_Get_Value(MG_HAL_ANALOG_GROUP[index]) << 2;
    }
    else
    {
        value = 0;
    }
    return value;
}

#if 0
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
#endif

uint16_t mg_HAL_Analog_Get_TPS1(void)
{
    return (QADC_Analog_FIFO1_Get_Value(AD_TPS1VI_Channel) << 2);
}

uint16_t mg_HAL_Analog_Get_TPS2(void)
{
    return (QADC_Analog_FIFO1_Get_Value(AD_TPS2VI_Channel) << 2);
}

#if 0
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
#endif

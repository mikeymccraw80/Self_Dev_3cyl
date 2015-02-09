#include "mg_hal_config.h"
#include "dd_sci.h"
/*=============================================================================
 * mg_HAL_Kline_Get_Read_Status
 * @func  get Kline status
 * @parm  none
 * @rdesc  Kline ready state
 *===========================================================================*/
bool mg_HAL_Kline_Get_Read_Status(void)
{
    return SCI_Get_Status(SCI_PORT_1.Configuration, SCI_INTERRUPT_CHANNEL_RX);
}

/*=============================================================================
 * mg_HAL_Kline_Reset_Read_Status
 * @func  reset Kline status
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_Kline_Reset_Read_Status(void)
{
    SCI_Reset_Status(SCI_PORT_1.Configuration, SCI_INTERRUPT_CHANNEL_RX);
}

/*=============================================================================
 * mg_HAL_Kline_Get_Write_Status
 * @func  get Kline status
 * @parm  none
 * @rdesc  Kline ready state
 *===========================================================================*/
bool mg_HAL_Kline_Get_Write_Status(void)
{
    return SCI_Get_Status(SCI_PORT_1.Configuration, SCI_INTERRUPT_CHANNEL_TX_COMPLETE);
}

/*=============================================================================
 * mg_HAL_Kline_Reset_Write_Status
 * @func  reset Kline status
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_Kline_Reset_Write_Status(void)
{
    SCI_Reset_Status(SCI_PORT_1.Configuration, SCI_INTERRUPT_CHANNEL_TX_COMPLETE);
}

/*=============================================================================
 * mg_HAL_Kline_Read
 * @func  read Kline data
 * @parm  none
 * @rdesc  Kline received data
 *===========================================================================*/
uint8_t mg_HAL_Kline_Read(void)
{
    return (uint8_t)SCI_Read(SCI_PORT_1.Configuration);
}

/*=============================================================================
 * mg_HAL_Kline_Write
 * @func  write Kline data
 * @parm  Kline data to transmit
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_Kline_Write(uint8_t data)
{
    SCI_Write(SCI_PORT_1.Configuration, (uint16_t)data);
}



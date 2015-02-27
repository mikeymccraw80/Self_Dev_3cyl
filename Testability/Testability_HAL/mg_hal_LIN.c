#if 0
#include "mg_hal_config.h"
#include "dd_sci.h"
#include "dd_lin.h"
#include "lin_port_init.h"

/*=============================================================================
 * mg_HAL_LIN_Get_Read_Status
 * @func  get LIN status
 * @parm  none
 * @rdesc  LIN ready state
 *===========================================================================*/
bool mg_HAL_LIN_Get_Read_Status(void)
{
    return SCI_Get_Status(SCI_PORT_0.Configuration, SCI_INTERRUPT_CHANNEL_RX);
}

/*=============================================================================
 * mg_HAL_LIN_Reset_Read_Status
 * @func  reset LIN status
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_LIN_Reset_Read_Status(void)
{
    SCI_Reset_Status(SCI_PORT_0.Configuration, SCI_INTERRUPT_CHANNEL_RX);
}

/*=============================================================================
 * mg_HAL_LIN_Get_Write_Status
 * @func  get LIN status
 * @parm  none
 * @rdesc  LIN ready state
 *===========================================================================*/
bool mg_HAL_LIN_Get_Write_Status(void)
{
    return SCI_Get_Status(SCI_PORT_0.Configuration, SCI_INTERRUPT_CHANNEL_TX_COMPLETE);
}

/*=============================================================================
 * mg_HAL_LIN_Reset_Write_Status
 * @func  reset LIN status
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_LIN_Reset_Write_Status(void)
{
    SCI_Reset_Status(SCI_PORT_0.Configuration, SCI_INTERRUPT_CHANNEL_TX_COMPLETE);
}

/*=============================================================================
 * mg_HAL_LIN_Read
 * @func  read LIN data
 * @parm  none
 * @rdesc  LIN received data
 *===========================================================================*/
uint8_t mg_HAL_LIN_Read(void)
{
    return (uint8_t)SCI_Read(SCI_PORT_0.Configuration);
}

/*=============================================================================
 * mg_HAL_LIN_Write
 * @func  write LIN data
 * @parm  LIN data to transmit
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_LIN_Write(uint8_t data)
{
    SCI_Write(SCI_PORT_0.Configuration, (uint16_t)data);
}

/*=============================================================================
 * mg_HAL_LIN_Set_DMA_Enable
 * @func  set LIN DMA enable
 * @parm  DMA enable state
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_LIN_Set_DMA_Enable(bool state)
{
    LIN_Device_Set_DMA_Enable(LIN_PORT_A.configuration, LIN_DMA_CHANNEL_RX, state);
    LIN_Device_Set_DMA_Enable(LIN_PORT_A.configuration, LIN_DMA_CHANNEL_TX, state);
}

#endif
//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
#include "dd_sci_interface.h"
#include "dd_sci.h"
#include "dd_siu.h"
#include "io_config_sci.h"
#include "dd_sci_interrupt.h"

static int scib_init(int bd)
{
	/* init the config of sci module */
	SCI_Configure_Device(SCI_DEVICE_1, SCI_NO_LOOPBACK);
	/* set speed of sci module */
	SCI_Set_Speed(SCI_DEVICE_1, bd);
	// SCI_Interrupt_Set_Channel(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_RX);
	// SCI_INTERRUPT_Set_Enable(SCI_DEVICE_1, true);
	// SCI_Set_Interrupt_Enable(SCI_DEVICE_1, true);
	return 0;
}

static int scib_set_speed(int bd)
{
	SCI_Set_Speed(SCI_DEVICE_1, bd);
	return 0;
}

static int scib_read(void)
{
	return SCI_Read(SCI_DEVICE_1);
}

static int scib_write(int ch)
{
	while(!SCI_Get_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY));
	SCI_Write(SCI_DEVICE_1, ch);

	return 0;
}

static int scib_poll(void)
{
	return SCI_Get_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_RX);
}

static int scib_reset(void)
{
	uint16_t rx_temp;

	// SCI_Shutdown_Device(SCI_DEVICE_1);

	if (SCI_Get_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_RX)) {
		SCI_Reset_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_RX);
		rx_temp = SCI_Read(SCI_DEVICE_1);
	}
	if (SCI_Get_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_OVERRUN_ERROR)) {
		SCI_Reset_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_OVERRUN_ERROR);
		rx_temp = SCI_Read(SCI_DEVICE_1);
	}
	if (SCI_Get_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_NOISE_FLAG_ERROR)) {
		SCI_Reset_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_NOISE_FLAG_ERROR);
		rx_temp = SCI_Read(SCI_DEVICE_1);
	}
	if (SCI_Get_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_FRAME_ERROR)) {
		SCI_Reset_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_FRAME_ERROR);
		rx_temp = SCI_Read(SCI_DEVICE_1);
	}
	if (SCI_Get_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_PARITY_ERROR)) {
		SCI_Reset_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_PARITY_ERROR);
		rx_temp = SCI_Read(SCI_DEVICE_1);
	}

	rx_temp = rx_temp;

	// scib_init(10400);

	return 0;
}

static int scib_get_all_err_flag(void)
{
	return SCI_Get_Rx_Error_Flag(SCI_DEVICE_1);
}

static int scib_get_frm_err_flag(void)
{
	return SCI_Get_Status(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_FRAME_ERROR);
}

static int scib_get_active_flag(void)
{
	// return SCI_Get_Status(SCI_DEVICE_1, SCI_STATUS_FLAG_RAF);
	if(SIU_GPIO_DISCRETE_Get_State(SIU_GPIO_CHANNEL_92)) {
		return 0;
	} else {
		return 1;
	}
}

static void scib_rx_disable_int(void)
{
	SCI_Interrupt_Set_Channel(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_RX);
	SCI_INTERRUPT_Set_Enable(SCI_DEVICE_1, false);
}

static void scib_rx_enable_int(void)
{
	SCI_Interrupt_Set_Channel(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_RX);
	SCI_INTERRUPT_Set_Enable(SCI_DEVICE_1, true);
}

extern void SerialcomReceiveInt(void);
static void scib_rx_callback(void)
{
	SerialcomReceiveInt();
}

void DD_SCIB_INT(void)
{
	scib.RxInt();
	SCI_Interrupt_Set_Channel(SCI_DEVICE_1, SCI_INTERRUPT_CHANNEL_RX);
	SCI_INTERRUPT_Clear_Pending(SCI_DEVICE_1);
}

const sci_bus_t scib = {
	scib_init,
	scib_set_speed,
	scib_read,
	scib_write,
	scib_poll,
	scib_reset,
	scib_get_all_err_flag,
	scib_get_frm_err_flag,
	scib_get_active_flag,
	scib_rx_callback,
	scib_rx_disable_int,
	scib_rx_enable_int,
};






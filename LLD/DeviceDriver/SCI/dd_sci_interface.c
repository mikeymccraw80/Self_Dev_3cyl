//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
#include "dd_sci_interface.h"
#include "dd_sci.h"
#include "io_config_sci.h"
#include "dd_sci_interrupt.h"

static int scib_init(void)
{
	/* init the config of sci module */
	SCI_Configure_Device(SCI_DEVICE_1, SCI_NO_LOOPBACK);
	/* set speed of sci module */
	SCI_Set_Speed(SCI_DEVICE_1, 10400);
	SCI_INTERRUPT_Set_Enable(SCI_DEVICE_1, true);
	// SCI_Set_Interrupt_Enable(SCI_DEVICE_1, true);
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

static void scib_rx_callback(void)
{


}

static void scib_tx_callback(void)
{


}
static uint8_t chch;
void DD_SCIB_INT(void)
{
	scib.RxInt();
	scib.TxCPInt();
	chch = scib.read();
	SCI_INTERRUPT_Clear_Pending(SCI_DEVICE_1);
}

const sci_bus_t scib = {
	scib_init,
	scib_read,
	scib_write,
	scib_poll,
	scib_rx_callback,
	scib_tx_callback,
};






/*===========================================================================*\
 * Header Files
\*===========================================================================*/
//#include "HLS.h"
#include "dd_flexcan_interface.h"
#include "io_config_flexcan.h"
#include "ccp2conf.h"
#include "hal_can.h"
#include "vehicle_can_cald.h"

/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
/* define receive temp buffer, this buffer is only as
 * FlexCAN_Receive_Interrupt() buffer only feel curious
 */
uint8_t	 CAN_Message_RX_DATA[FLEXCAN_DATA_MAX_BYTES];
uint32_t CAN_Message_RX_ID;

/* Used to diagnostic can meter */
CAN_RECEIVE_ERR_TYPE VsCAN_Receive_Err;

CAN_Port_Error_T HAL_CAN_Err_Status[4];


//=============================================================================
// HAL_CAN_RX_B00_Config
//=============================================================================
void HAL_CAN_RX_B00_Config(void)
{
//CCP_CANID_CRO
	FlexCAN_Receive_Configure(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_CRO,
			CCP_CANID_CRO
	);
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_CRO,
			true );
}
//=============================================================================
// HAL_CAN_RX_B00_INT
//=============================================================================
void HAL_CAN_RX_B00_INT(void)
{
//CCP_CANID_CRO
	FlexCAN_Receive_Interrupt(FLEXCAN_DEVICE_A, CAN_Message_RX_DATA);
}
//=============================================================================
// HAL_CAN_TX_B01_Config
//=============================================================================

void HAL_CAN_TX_B01_Config(void)
{
//CCP_CANID_DTO
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DTO,
			true );
}
//=============================================================================
// HAL_CAN_TX_B01_INT
//=============================================================================

void HAL_CAN_TX_B01_INT(void)
{
//CCP_CANID_DTO
	FlexCAN_Transmit_Interrupt(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DTO	 );

}
//=============================================================================
// HAL_CAN_TX_B02_Config
//=============================================================================

void HAL_CAN_TX_B02_Config(void)
{
//CCP_CANID_DAQ0
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ0,
			true );
}
//=============================================================================
// HAL_CAN_TX_B02_INT
//=============================================================================

void HAL_CAN_TX_B02_INT(void)
{
//CCP_CANID_DAQ0
	FlexCAN_Transmit_Interrupt(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ0  );

}

//=============================================================================
// HAL_CAN_TX_B03_Config
//=============================================================================

void HAL_CAN_TX_B03_Config(void)
{
//CCP_CANID_DAQ1
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ1,
			true );
}
//=============================================================================
// HAL_CAN_TX_B03_INT
//=============================================================================

void HAL_CAN_TX_B03_INT(void)
{
//CCP_CANID_DAQ1
	FlexCAN_Transmit_Interrupt(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ1  );

}

//=============================================================================
// HAL_CAN_TX_B04_Config
//=============================================================================

void HAL_CAN_TX_B04_Config(void)
{
//CCP_CANID_DAQ2
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ2,
			true );
}
//=============================================================================
// HAL_CAN_TX_B04_INT
//=============================================================================

void HAL_CAN_TX_B04_INT(void)
{
//CCP_CANID_DAQ2
	FlexCAN_Transmit_Interrupt(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ2  );

}

//=============================================================================
// HAL_CAN_TX_B05_Config
//=============================================================================

void HAL_CAN_TX_B05_Config(void)
{
//CCP_CANID_DAQ3
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ3,
			true );
}
//=============================================================================
// HAL_CAN_TX_B05_INT
//=============================================================================

void HAL_CAN_TX_B05_INT(void)
{
//CCP_CANID_DAQ3
	FlexCAN_Transmit_Interrupt(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ3 );

}

//=============================================================================
// HAL_CAN_RX_B06_Config
//=============================================================================
void HAL_CAN_RX_B06_Config(void)
{
//CCP_CANID_CRO
	FlexCAN_Receive_Configure(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_INCA_RECEIVE,
			CCP_INCA_RECEIVE
	);
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_INCA_RECEIVE,
			true );
}
//=============================================================================
// HAL_CAN_RX_B06_INT
//=============================================================================
void HAL_CAN_RX_B06_INT(void)
{
//CCP_CANID_CRO
	FlexCAN_Receive_Interrupt(FLEXCAN_DEVICE_A,	CAN_Message_RX_DATA);
}

//=============================================================================
// HAL_CAN_TX_B07_Config
//=============================================================================

void HAL_CAN_TX_B07_Config(void)
{
//CCP_CANID_DAQ3
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_INCA_TRANSIT,
			true );
}
//=============================================================================
// HAL_CAN_TX_B07_INT
//=============================================================================

void HAL_CAN_TX_B07_INT(void)
{
//CCP_CANID_DAQ3
	FlexCAN_Transmit_Interrupt(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_Index_CCP_INCA_TRANSIT );

}


void HAL_CAN_Transmit_Message(uint32_t id, uint8_t len, uint8_t *pdata)
{
	bool result;
	static int can_obj_num = FLEXCAN_MSG_OBJ_16;
	can_obj_num = can_obj_num >= FLEXCAN_MSG_OBJ_31?FLEXCAN_MSG_OBJ_16:can_obj_num++;
	result = FlexCAN_Transmit_Message(
					 &FlexCAN_A,
					 can_obj_num,
					 id,
					 pdata,
					 len);
}


extern uint8_t	VsCAN_CHERY_ID2E9[8];
extern uint8_t	VsCAN_CHERY_ID310[8];
extern uint8_t	VsCAN_CHERY_ID51A[8];
extern uint8_t	VsCAN_CHERY_ID3C0[8];
extern uint8_t	VsCAN_CHERY_ID430[8];
extern uint8_t	VsCAN_CHERY_ID1AE[8];
extern uint8_t	VsCAN_CHERY_ID300[8];


void HAL_CAN_RX_B08_Config(void)
{
	FlexCAN_Receive_Configure(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_8,
			0x2E9
	);
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_8,
			true );
}

void HAL_CAN_RX_B08_INT(void)
{
	FlexCAN_Receive_Interrupt(FLEXCAN_DEVICE_A, VsCAN_CHERY_ID2E9);
}

void HAL_CAN_RX_B09_Config(void)
{
	FlexCAN_Receive_Configure(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_9,
			0x310
	);
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_9,
			true );
}

void HAL_CAN_RX_B09_INT(void)
{
	FlexCAN_Receive_Interrupt(FLEXCAN_DEVICE_A,VsCAN_CHERY_ID310);
}

void HAL_CAN_RX_B10_Config(void)
{
	FlexCAN_Receive_Configure(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_10,
			0x51A
	);
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_10,
			true );
}

void HAL_CAN_RX_B10_INT(void)
{
	FlexCAN_Receive_Interrupt(FLEXCAN_DEVICE_A, VsCAN_CHERY_ID51A);
}

void HAL_CAN_RX_B11_Config(void)
{
	FlexCAN_Receive_Configure(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_11,
			0x3C0
	);
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_11,
			true );
}

void HAL_CAN_RX_B11_INT(void)
{
	FlexCAN_Receive_Interrupt(FLEXCAN_DEVICE_A, VsCAN_CHERY_ID3C0);
}

void HAL_CAN_RX_B12_Config(void)
{
	FlexCAN_Receive_Configure(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_12,
			0x430
	);
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_12,
			true );
}

void HAL_CAN_RX_B12_INT(void)
{
	FlexCAN_Receive_Interrupt(FLEXCAN_DEVICE_A, VsCAN_CHERY_ID430);
}

void HAL_CAN_RX_B13_Config(void)
{
	FlexCAN_Receive_Configure(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_13,
			0x1ae
	);
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_13,
			true );
}

void HAL_CAN_RX_B13_INT(void)
{
	FlexCAN_Receive_Interrupt(FLEXCAN_DEVICE_A, VsCAN_CHERY_ID1AE);
	VsCAN_Receive_Err.CAN_ID1AE_RXF = true;
}

void HAL_CAN_RX_B14_Config(void)
{
	FlexCAN_Receive_Configure(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_14,
			0x300
	);
	FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
			&FlexCAN_A,
			FLEXCAN_MSG_OBJ_14,
			true );
}

void HAL_CAN_RX_B14_INT(void)
{
	FlexCAN_Receive_Interrupt(FLEXCAN_DEVICE_A, VsCAN_CHERY_ID300);
}

void HAL_CAN_RX_B31_16_INT(void)
{
	hwi_can_device_a_isr();
}

void HAL_CAN_RX_B63_32_INT(void)
{
	hwi_can_device_a_isr();
}

void HAL_CAN_Diag_Network_10ms(void)
{
	if (VsCAN_Receive_Err.CAN_ID1AE_RXF == true) {
		VsCAN_Receive_Err.CAN_ID1AE_ERR = false;
	} else {
		VsCAN_Receive_Err.CAN_ID1AE_ERR = true;
	}
	VsCAN_Receive_Err.CAN_ID1AE_RXF = false;
}

void HAL_CAN_Initialize(void)
{
	HAL_CAN_RX_B00_Config();
	HAL_CAN_TX_B01_Config();
	HAL_CAN_TX_B02_Config();
	HAL_CAN_TX_B03_Config();
	HAL_CAN_TX_B04_Config();
	HAL_CAN_TX_B05_Config();
	HAL_CAN_RX_B06_Config();
	HAL_CAN_TX_B07_Config();

	/* for chery receive interrupt */
	if(KbHwio_CheryCanID2E9_Enable)

	    HAL_CAN_RX_B08_Config();
	
	if(KbHwio_CheryCanID310_Enable)

	    HAL_CAN_RX_B09_Config();
	
	if(KbHwio_CheryCanID51A_Enable)
		
	    HAL_CAN_RX_B10_Config();
	
	if(KbHwio_CheryCanID3C0_Enable)
		
	    HAL_CAN_RX_B11_Config();
	
	if(KbHwio_CheryCanID430_Enable)
		
	    HAL_CAN_RX_B12_Config();

	if(KbHwio_CheryCanID1AE_Enable)

	    HAL_CAN_RX_B13_Config();

	if(KbHwio_CheryCanID300_Enable)

	    HAL_CAN_RX_B14_Config();
}


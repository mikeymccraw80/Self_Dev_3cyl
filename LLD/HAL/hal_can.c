

/*===========================================================================*\
 * Header Files
\*===========================================================================*/
//#include "HLS.h"
#include "dd_flexcan_interface.h"
#include "io_config_flexcan.h"
#include "ccp2conf.h"


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
uint8_t CAN_Message_Transmit_0x480[FLEXCAN_DATA_MAX_BYTES];
uint8_t test_can =0;

/* define receive temp buffer, this buffer is only as 
 * FlexCAN_Receive_Interrupt() buffer only feel curious
 */
uint8_t  CAN_Message_RX_DATA[FLEXCAN_DATA_MAX_BYTES];
uint32_t CAN_Message_RX_ID;

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
FlexCAN_Receive_Interrupt(
           FLEXCAN_DEVICE_A,
           FLEXCAN_MSG_OBJ_Index_CCP_CANID_CRO,
           CCP_CANID_CRO,
           CAN_Message_RX_DATA
          );

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
           FLEXCAN_MSG_OBJ_Index_CCP_CANID_DTO  );

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
FlexCAN_Receive_Interrupt(
           FLEXCAN_DEVICE_A,
           FLEXCAN_MSG_OBJ_Index_CCP_INCA_RECEIVE,
           CCP_INCA_RECEIVE,
           CAN_Message_RX_DATA
          );

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
	can_obj_num = can_obj_num >= FLEXCAN_MSG_OBJ_31?can_obj_num++ : FLEXCAN_MSG_OBJ_16;
	result = FlexCAN_Transmit_Message(
			&FlexCAN_A,
			can_obj_num,
			id,
			pdata,
			len);
}

/* ============================================================================ *\
 * HAL_DI_10ms_Task
\*============================================================================ */
 void HAL_CAN_10ms_Task(void) 
{ 
   bool transmit_complete;
   uint8_t index;

      for(index = FLEXCAN_DATA_0_BYTES; index < FLEXCAN_DATA_MAX_BYTES; index++)
      {
         CAN_Message_Transmit_0x480[index] = test_can++;
      	}
	  
   transmit_complete = FlexCAN_Transmit_Message(
   &FlexCAN_A,
   FLEXCAN_MSG_OBJ_14,
   0x480,
   CAN_Message_Transmit_0x480,
   FLEXCAN_DATA_MAX_BYTES   );
    
}

void CAN_RX_B15_Config(void)
{
 FlexCAN_Receive_Configure(
            &FlexCAN_A,
           FLEXCAN_MSG_OBJ_15,
           0x555
          );
  FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
   &FlexCAN_A,
   FLEXCAN_MSG_OBJ_15,
   true );
}

void CAN_RX_10ms_B15_INT(void)
{

FlexCAN_Receive_Interrupt(
           FLEXCAN_DEVICE_A,
           FLEXCAN_MSG_OBJ_15,
           CAN_Message_RX_ID,
           CAN_Message_RX_DATA
          );

}

extern uint8_t  VsCAN_CHERY_ID2E9[8];
extern uint8_t  VsCAN_CHERY_ID310[8];
extern uint8_t  VsCAN_CHERY_ID391[8];
extern uint8_t  VsCAN_CHERY_ID3C0[8];
extern uint8_t  VsCAN_CHERY_ID430[8];

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

FlexCAN_Receive_Interrupt(
           FLEXCAN_DEVICE_A,
           FLEXCAN_MSG_OBJ_8,
           CAN_Message_RX_ID,
           VsCAN_CHERY_ID2E9
          );

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

FlexCAN_Receive_Interrupt(
           FLEXCAN_DEVICE_A,
           FLEXCAN_MSG_OBJ_9,
           CAN_Message_RX_ID,
           VsCAN_CHERY_ID310
          );

}

void HAL_CAN_RX_B10_Config(void)
{
 FlexCAN_Receive_Configure(
            &FlexCAN_A,
           FLEXCAN_MSG_OBJ_10,
           0x391
          );
  FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
   &FlexCAN_A,
   FLEXCAN_MSG_OBJ_10,
   true );
}

void HAL_CAN_RX_B10_INT(void)
{

FlexCAN_Receive_Interrupt(
           FLEXCAN_DEVICE_A,
           FLEXCAN_MSG_OBJ_10,
           CAN_Message_RX_ID,
           VsCAN_CHERY_ID391
          );

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

FlexCAN_Receive_Interrupt(
           FLEXCAN_DEVICE_A,
           FLEXCAN_MSG_OBJ_11,
           CAN_Message_RX_ID,
           VsCAN_CHERY_ID3C0
          );

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

FlexCAN_Receive_Interrupt(
           FLEXCAN_DEVICE_A,
           FLEXCAN_MSG_OBJ_12,
           CAN_Message_RX_ID,
           VsCAN_CHERY_ID430
          );

}


void CCP_Initialize(void)
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
	HAL_CAN_RX_B08_Config();
	HAL_CAN_RX_B09_Config();
	HAL_CAN_RX_B10_Config();
	HAL_CAN_RX_B11_Config();
	HAL_CAN_RX_B12_Config();
}


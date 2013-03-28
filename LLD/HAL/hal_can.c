

/*===========================================================================*\
 * Header Files
\*===========================================================================*/
#include "HLS.h"
#include "dd_flexcan_interface.h"
#include "io_config_flexcan.h"


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
uint8_t   CAN_Message_Transmit_0x480[FLEXCAN_DATA_MAX_BYTES];
uint8_t    test_can =0;

uint8_t   CAN_Message_RX_DATA[FLEXCAN_DATA_MAX_BYTES];
uint32_t   CAN_Message_RX_ID;

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
   FLEXCAN_MSG_OBJ_0,
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


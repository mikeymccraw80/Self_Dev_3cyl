#ifndef DD_FLEXCAN_INTERFACE_H
#define DD_FLEXCAN_INTERFACE_H

#include "dd_flexcan.h"



//=============================================================================
// FlexCAN_Initialize_Device
//=============================================================================
extern void FlexCAN_A_Initialize_Device(void );

//=============================================================================
// FlexCAN_Initialize_Device
//=============================================================================
extern void FlexCAN_C_Initialize_Device(void );

//============================================================================
// FlexCAN_Transmit_Message
//============================================================================
extern bool FlexCAN_Transmit_Message(
  FLEXCAN_T *                  in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T        msg_obj,
   uint32_t in_message_id,
   uint8_t *in_data_buffer,
   uint8_t  in_data_length    );




//=============================================================================
//    FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable
//============================================================================
extern void FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
   FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T        in_msg_obj,
   bool in_enable ); 

//============================================================================
// FlexCAN_Receive_Configure
//============================================================================
extern void FlexCAN_Receive_Configure(
            FLEXCAN_T *      in_pFlexCAN,
           FlexCAN_MSGOBJ_INDEX_T        msg_obj,
           uint32_t in_message_id
          );

extern void FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
   FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T        in_msg_obj,
   bool in_enable );

//============================================================================
// FlexCAN_Receive_Interrupt
//============================================================================
extern void FlexCAN_Receive_Interrupt(FlexCAN_Index_T in_FlexCAN, uint8_t *in_data_buffer);

//============================================================================
// FlexCAN A Buffer 32-63 interrupt
//============================================================================
extern void hwi_can_device_a_isr();

//=============================================================================
// FlexCAN_Get_Device
//=============================================================================
FLEXCAN_T* FlexCAN_Get_Device(
   IO_Configuration_T in_configuration );


#endif // DD_FLEXCAN_INTERFACE_H


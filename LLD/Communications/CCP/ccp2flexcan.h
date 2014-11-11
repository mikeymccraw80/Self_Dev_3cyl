#ifndef CCP2FLEXCAN_H
#define CCP2FLEXCAN_H

//=============================================================================
//       Include Files
//=============================================================================
#include "io_type.h"
#include "dd_flexcan_interface.h"


//=============================================================================
//       Macro Definitions
//=============================================================================
#define  CAN_MSG_LENGTH   (8)

#define HWTEST_CANID_TX   (0x701)
#define HWTEST_CANID_RX   (0x701)

typedef struct
{   
    uint32_t CAN_id;
    uint8_t  data_size;
    uint8_t data[8];
} Rx_Callback_Msg_Type;

typedef  void (* const FlexCAN_Transmit_CALLBACK_T )(uint32_t);
typedef  void (* const FlexCAN_Recieve_CALLBACK_T)(uint32_t,  uint8_t*, uint8_t);
typedef  void (* const FlexCAN_Error_CALLBACK_T)(void);

#define FLEXCAN_RECEIVE_CALLBACK_INIT_A  (FlexCAN_Receive_Callback_T)(FlexCAN_RX_CallBack)
#define FLEXCAN_TRANSMIT_CALLBACK_INIT_A (FlexCAN_Transmit_Callback_T)(FlexCAN_TX_CallBack)
#define FLEXCAN_RECEIVE_CALLBACK_INIT_C  (FlexCAN_Receive_Callback_T)(FlexCAN_RX_CallBack)
#define FLEXCAN_TRANSMIT_CALLBACK_INIT_C (FlexCAN_Transmit_Callback_T)(FlexCAN_TX_CallBack)

typedef struct FlexCAN_message_parameter_Tag
{
   uint32_t    Message_ID;
   uint8_t     *FlexCAN_buffer_ptr;
   void        (*notifier_function_ptr)(void);
   uint32_t    Message_Config;
}  FlexCAN_message_parameter_T;


#define HWTEST_CANID_TX   (0x701)
#define HWTEST_CANID_RX   (0x701)

//=============================================================================
//       extern const
//=============================================================================

extern const FlexCAN_Transmit_CALLBACK_T  FlexCAN_Transmit_CALLBACK_Table[FLEXCAN_DEVICE_MAX];
extern const FlexCAN_Recieve_CALLBACK_T   FlexCAN_Recieve_CALLBACK_Table[FLEXCAN_DEVICE_MAX];
extern const FlexCAN_Error_CALLBACK_T     FlexCAN_Error_CALLBACK_Table[FLEXCAN_DEVICE_MAX];


extern uint8_t FlexCAN_RX_Message_Count[];

extern const FlexCAN_message_parameter_T FlexCAN_TX_Message_Parameter_Table[];
extern const FlexCAN_message_parameter_T FlexCAN_RX_Message_Parameter_Table[];

extern uint8_t FlexCAN_RX_MSG_DLC;

//=============================================================================
// FlexCAN_RX_CallBack
//
// @func FlexCAN device Recieve Message Call back function 
//
// @parm message_id | 32-bit RX message id
//       data_length| length of RX message  
//       data_buffer| Recieved data pointer 
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_RX_CallBack (
   uint32_t in_message_id,
   uint8_t *in_data_buffer,
   uint8_t  in_data_length    );

//=============================================================================
// FlexCAN_TX_CallBack
//
// @func FlexCAN device Recieve Message Call back function 
//
// @parm message_id | 32-bit TX message id
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_TX_CallBack ( 
   uint32_t message_id          );

//=============================================================================
// FLEXCAN_Get_RX_Message_Index
//
// @func This function returns message index in message table for a message id 
//
// @parm message_id | 32-bit message id
//
// @rdesc None
//
// @end
//=============================================================================
uint8_t FLEXCAN_Get_RX_Message_Index(
   uint32_t  message_id );

//=============================================================================
// FlexCAN_Message_Initialization
//
// @func This function returns message index in message table for a message id 
//
// @parm None
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Message_Initialization (void);

#endif //IO_FLEXCAN_CONFIG_H

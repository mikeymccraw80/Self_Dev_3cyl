#ifndef HAL_CAN_H
#define HAL_CAN_H

#include "reuse.h"

//=============================================================================
// @enum HAL_CAN_Device_T
//=============================================================================
typedef enum
{
   HAL_CAN_DEVICE_A,
   HAL_CAN_DEVICE_B,
   HAL_CAN_DEVICE_C,
   HAL_CAN_DEVICE_D
} HAL_CAN_Device_T;

//=============================================================================
// @enum HAL_CAN_Baud_T
//=============================================================================
typedef enum
{
   HAL_CAN_BAUD_100KBPS,
   HAL_CAN_BAUD_250KBPS,
   HAL_CAN_BAUD_500KBPS,
   HAL_CAN_BAUD_1MBPS,
   HAL_CAN_BAUD_MAX
} HAL_CAN_Baud_T;

//=============================================================================
// @enum HAL_CAN_Message_Direction_T
//=============================================================================
typedef enum
{
   HAL_CAN_MESSAGE_DIRECTION_RECEIVE,
   HAL_CAN_MESSAGE_DIRECTION_TRANSMIT
} HAL_CAN_Message_Direction_T;

//=============================================================================
// @enum HAL_CAN_Error_T
//=============================================================================
typedef enum
{
   HAL_CAN_ERROR_NONE,
   HAL_CAN_ERROR_INVALID_RX_MESSAGE,
   HAL_CAN_ERROR_INVALID_TX_MESSAGE,
   HAL_CAN_ERROR_PERMANENT_BUSOFF,
   HAL_CAN_ERROR_TEMPORARY_BUSOFF
} HAL_CAN_Error_T;

//=============================================================================
// @enum HAL_CAN_Message_Status_T
//=============================================================================
typedef enum
{
   HAL_CAN_MESSAGE_STATUS_IN_PROGRESS,
   HAL_CAN_MESSAGE_STATUS_COMPLETED
} HAL_CAN_Message_Status_T;

//=============================================================================
// @enum HAL_CAN_Callback_Type_T
//=============================================================================
typedef enum HAL_CAN_Callback_Type_Tag
{
   HAL_CAN_CALLBACK_TYPE_TRANSMIT,              
   HAL_CAN_CALLBACK_TYPE_RECEIVE,
   HAL_CAN_CALLBACK_TYPE_ERROR,
   HAL_CAN_CALLBACK_TYPE_MAX
} HAL_CAN_Callback_Type_T;

//=============================================================================
// @enum HAL_CCP_Event_Channel_T
//=============================================================================
typedef enum HAL_CCP_Event_Channel_Tag
{
   HAL_CCP_EVENT_CHANNEL_LORES,
   HAL_CCP_EVENT_CHANNEL_AMAF,
   HAL_CCP_EVENT_CHANNEL_3P9MS,
   HAL_CCP_EVENT_CHANNEL_7P8MS,
   HAL_CCP_EVENT_CHANNEL_15P6MS_TASK0,
   HAL_CCP_EVENT_CHANNEL_15P6MS_TASK1,
   HAL_CCP_EVENT_CHANNEL_31P25MS_TASK0,
   HAL_CCP_EVENT_CHANNEL_31P25MS_TASK1,
   HAL_CCP_EVENT_CHANNEL_31P25MS_TASK2,
   HAL_CCP_EVENT_CHANNEL_31P25MS_TASK3,
   HAL_CCP_EVENT_CHANNEL_62P5MS_TASK0,
   HAL_CCP_EVENT_CHANNEL_62P5MS_TASK1,
   HAL_CCP_EVENT_CHANNEL_62P5MS_TASK2,
   HAL_CCP_EVENT_CHANNEL_62P5MS_TASK3,
   HAL_CCP_EVENT_CHANNEL_62P5MS_TASK4,
   HAL_CCP_EVENT_CHANNEL_62P5MS_TASK5,
   HAL_CCP_EVENT_CHANNEL_62P5MS_TASK6,
   HAL_CCP_EVENT_CHANNEL_62P5MS_TASK7,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK0,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK1,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK2,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK3,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK4,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK5,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK6,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK7,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK8,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK9,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK10,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK11,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK12,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK13,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK14,
   HAL_CCP_EVENT_CHANNEL_125MS_TASK15,
   HAL_CCP_EVENT_CHANNEL_500MS_TASK0,
   HAL_CCP_EVENT_CHANNEL_500MS_TASK1,
   HAL_CCP_EVENT_CHANNEL_500MS_TASK2,
   HAL_CCP_EVENT_CHANNEL_500MS_TASK3,
   HAL_CCP_EVENT_CHANNEL_001S_TASK0,
   HAL_CCP_EVENT_CHANNEL_001S_TASK1,
   HAL_CCP_EVENT_CHANNEL_001S_TASK2,
   HAL_CCP_EVENT_CHANNEL_001S_TASK3
} HAL_CCP_Event_Channel_T;

//=============================================================================
// HAL_CAN_Transmit_Callback_T
//=============================================================================
typedef void ( *HAL_CAN_Transmit_Callback_T )(
   uint32_t   in_msg_obj );

//=============================================================================
// HAL_CAN_Receive_Callback_T
//=============================================================================
typedef void ( *HAL_CAN_Receive_Callback_T )(
   uint32_t   in_msg_obj,
   uint8_t*   in_data_buff,
   uint8_t    in_length );

//=============================================================================
// HAL_CAN_Error_Callback_T
//=============================================================================
typedef void ( *HAL_CAN_Error_Callback_T )(
   HAL_CAN_Error_T   in_error_status );
/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/
typedef struct
{
  bitfield16_t CAN_ID1AE_ERR :1;
  bitfield16_t CAN_ID2E9_ERR :1;
  bitfield16_t CAN_ID310_ERR :1;
  bitfield16_t CAN_ID3C0_ERR :1;
  bitfield16_t CAN_ID430_ERR :1;
  bitfield16_t CAN_ID51A_ERR :1;
  bitfield16_t UNUSED_ERR :2;
  bitfield16_t CAN_ID1AE_RXF :1;
  bitfield16_t CAN_ID2E9_RXF :1;
  bitfield16_t CAN_ID310_RXF :1;
  bitfield16_t CAN_ID3C0_RXF :1;
  bitfield16_t CAN_ID430_RXF :1;
  bitfield16_t CAN_ID51A_RXF :1;
  bitfield16_t UNUSED_RXF :2;
}CAN_RECEIVE_ERR_TYPE;
/* Used to diagnostic can meter */
extern CAN_RECEIVE_ERR_TYPE VsCAN_Receive_Err;
CAN_Port_Error_T HAL_CAN_Err_Status[4];

void HAL_CAN_Initialize(void);
void HAL_CAN_Transmit_Message(uint32_t id, uint8_t len, uint8_t *pdata);
void HAL_CAN_Diag_Network_10ms(void);

#endif


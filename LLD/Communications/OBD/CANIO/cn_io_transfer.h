#ifndef CN_IO_TRANSFER_H
#define CN_IO_TRANSFER_H
/******************************************************************************
 *
 * Filename:          cn_io_transfer.h
 *
 * Description:       can transfer header file.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2009, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/
//=============================================================================
// Include Files
//=============================================================================
#include "t_gentypes.h"
#include "io_type.h"
//=============================================================================
// Global Function Prototypes
//=============================================================================
typedef void (*Notifier_T)( uint32_t );

typedef enum
{
   CANH_DEVICE_A,
   CANH_DEVICE_B,
   CANH_DEVICE_C,
   CANH_DEVICE_D
} CANH_DEVICE_T;

typedef enum
{
   CANH_MESSAGE_DIRECTION_RECEIVE,
   CANH_MESSAGE_DIRECTION_TRANSMIT
} CANH_Message_Direction_T;

typedef struct CAN_Message_Parameter_Tag
{
    uint16_t                      CAN_message_ID;
    uint8_t                       CAN_message_length;
    uint8_t                       CAN_buffer_depth;
    uint8_t                       *CAN_buffer_ptr;
    Notifier_T                    callback;
    CANH_DEVICE_T                 node_type;
    CANH_Message_Direction_T      message_dir;
    IO_Configuration_T            in_configuration;
} CAN_Message_Parameter_T;

extern void    CAN_Reset_Init( void );
extern uint8_t Get_Receive_Message_Number_From_Message_ID( uint16_t Message_ID );
extern bool    Get_OBD_Message( uint8_t CAN_receive_message_number, uint8_t *message_address );
extern bool    Transmit_Message( uint16_t can_id, uint8_t *message_address );
extern uint8_t Get_Transmit_Message_Number_From_Message_ID(uint16_t Message_ID );

extern CAN_Message_Parameter_T *CAN_Message_Parameter_Table_Ptr;

extern uint8_t          CANMsg_Buffer_DLC;
#define GetCANMsg_Buffer_DLC()       CANMsg_Buffer_DLC


// xuhui added
#define MESSAGE_ID_NOT_IN_TABLE  255

uint8_t CN_IO_Find_Message_idx(uint32_t message_id);

#endif/*CN_IO_TRANSFER_H*/
/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
******************************************************************************/

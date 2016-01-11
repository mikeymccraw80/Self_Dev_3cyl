/*****************************************************************************
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Siddarth, Sandeep                                       *
 * Project: CCA - DATA TYPES                                                 *
 * File Name:  j1939_data_types.h                                            *
 * Description: This file contans the data types those are commonly used in  *
 *              Delphi CAN Handler (DCH)                                     *
 *****************************************************************************/

#ifndef J1939_DATA_TYPES_H
#define J1939_DATA_TYPES_H

/*=======================           INCLUDES           =======================*/
#include "io_type.h"

/*=======================        TYPE DEFINITIONS      =======================*/

typedef signed char         sint8_t;
typedef signed short        sint16_t;
typedef signed int          sint32_t;

#if 0
 typedef enum
{
   CAN_cbFALSE,
   CAN_cbTRUE
} can_boolean_t;    //  boolean_t
#endif

#define can_boolean_t bool
#define CAN_cbFALSE false
#define CAN_cbTRUE true

typedef enum {
  PosAck,
  NegAck,
  DenyAck,
  BusyAck
  } AckModeType;


/************************************************************************/
/* STRUCTURE: J1939_Transmit_Messages_Index_Tag                                              */
/* Description: Used to indicate the start & end index of the Message Table. */
/************************************************************************/
typedef struct J1939_Transmit_Messages_Index_Tag
{
  uint8_t Start_Index;
  uint8_t End_Index;
}J1939_Transmit_Messages_Index_T;


/************************************************************************/
/* STRUCTURE: CanRxMsgType                                              */
/* Description: Used as the means of data communication between can     */
/*                modules for Rx messages                               */
/*              Passed to parse routine                                 */
/************************************************************************/
typedef struct J1939_Receive_Message_Info_Tag
{
  uint32_t ID;
  uint8_t  Length;
  uint8_t  Data[8];
} J1939_Receive_Message_Info_T;


/************************************************************************/
/* STRUCTURE: CanTxMsgType                                              */
/* Description: Used as the means of data communication between can     */
/*                modules for Tx messages                               */
/*              Passed to service routine                               */
/************************************************************************/
typedef struct J1939_Transmit_Message_Info_Tag
{
  uint8_t   Extended_ID;
  uint32_t  ID;
  uint8_t   Length;
  uint8_t   Data[8];
  /* Additional data shared between layers */
  uint8_t   Requested;
  uint8_t   Requester;
  uint16_t  Callback_Time_W;
  uint16_t  Callback_Timeout_W;
} J1939_Transmit_Message_Info_T;


/************************************************************************/
/* STRUCTURE:  Cofigures/Controls all the CAN Rx messages               */
/************************************************************************/
typedef struct
{
  void (*Parse_Routine) (J1939_Receive_Message_Info_T *Rx_Message);
  void (*Message_Lost_Routine) (void);
  uint16_t Message_Lost_Timeout_W;
  uint8_t  Message_Lost;
  uint8_t  Message_Lost_Action_Taken;
  uint16_t Message_Lost_Timer_W;
} J1939_Receive_Message_Control_T;


/************************************************************************/
/* STRUCTURE:  Cofigures/Controls all the CAN Tx messages               */
/************************************************************************/
typedef struct J1939_Transmit_Message_Control_Tag
{
  bool (*Service_Routine)(J1939_Transmit_Message_Info_T *Tx_Message);
  uint8_t   Time_To_Service;
  uint8_t   Tx_Timeout;
  uint16_t  Time_To_Next_Service_W;
  uint16_t  Tx_Timeout_Timer_W;
  uint8_t   Requested;
  uint8_t   Requester;
  
  uint16_t  Event_Trigger_Service_Buffer;
  bool      Event_Trigger_Flag;

  
} J1939_Transmit_Message_Control_T;


//=============================================================================
// CAN_Port_TransmitCallback_T
//=============================================================================
typedef void (*CAN_Port_TransmitCallback_T)(
   uint8_t in_msg_obj );
//=============================================================================
// CAN_Port_ReceiveCallback_T
//=============================================================================
typedef void (*CAN_Port_ReceiveCallback_T)(
   uint8_t   in_msg_obj,
   uint8_t*  in_data_buff,
   uint8_t   in_data_length );

//=============================================================================
// CAN_Port_ErrorCallback_T
//=============================================================================
typedef void (*CAN_Port_ErrorCallback_T)(
   uint8_t            in_can_node,
   CAN_Port_Error_T   in_error_status );

// @struct CANPortInterfaceCallback_T | This structure contanis
// the interrupt call backs of CAN port object.
typedef struct CANPortInterfaceCallback_Tag
{
   CAN_Port_TransmitCallback_T       TransmitCallback;
   CAN_Port_ReceiveCallback_T        ReceiveCallback;
   CAN_Port_ErrorCallback_T          ErrorCallback; 

} CANPortInterfaceCallback_T;

typedef enum CAN_Port_Message_Direction_Tag
{
   CAN_PORT_MSG_DIR_RECEIVE,
   CAN_PORT_MSG_DIR_TRANSMIT
} CAN_Port_Message_Direction_T;

typedef struct J1939_Message_Table_Tag
{
   uint32_t 			             message_ID;
   uint8_t				             message_length;
} J1939_Message_Table_T;

typedef enum
{
   J1939_NEW_MESSAGE_UNAVAILABLE = 0x00,
   J1939_NEW_MESSAGE_AVAILABLE
} J1939_New_Message_Status_T;

typedef struct J1939_Receive_Message_Buffer_Tag
{
   uint8_t                        msg_data[8];
   J1939_New_Message_Status_T     new_msg;
} J1939_Receive_Message_Buffer_T;

#endif



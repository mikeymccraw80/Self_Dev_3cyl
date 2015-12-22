#ifndef IO_DCAN_CONFIG_H
#define IO_DCAN_CONFIG_H
//=============================================================================
//       COPYRIGHT 2005, Delphi Technologies, Inc. All Rights reserved
//                             Delphi Confidential
//
// --------------------------------------------------------------------------
// %name:            io_dcan_config.h %
//
// created_by:       qznx5b
//
// date_created:     Wed. Mar. 2 2005
//
// %derived_by:      zzrfyj %
//
// %date_modified:         %
//
// %version:         6 %
//
//=============================================================================

//=============================================================================
//       Include Files
//=============================================================================
#include "io_type.h"
#include "dcantran.h"
#include "cn_io_transfer.h"/*CAN_Message_Parameter_T*/
#include "hal_can.h"

//=============================================================================
//       Macro Definitions
//=============================================================================

/* Polled / Interrupt Mode selection values for Transmit, Receive 
 *  and Error-Handler routines
 */
typedef struct
{
   uint16_t       CAN_message_ID; //mzyqz4-added newly.
   uint8_t        MessageBufferNumber;
   void             (*Task) (Can8DataBytesArrayType *);  /*--- address of the can task to
                                                    execute on the reception of a message
                                                    identified by its CAN ID  ---*/
}CanRxMessageControlType;

#define Buffer0        (0x0)
#define Buffer1        (0x1)
#define Buffer2        (0x2)
/*--------------------------------------------------------------------*/
/*--- AFFECTATION OF CAN MESSAGES TO THE DIFFERENT RECEIVE BUFFERS ---*/
/*--------------------------------------------------------------------*/
/*---      .                                                       ---*/
/*---     / \     the following definition must follow the naming  ---*/
/*---    / | \    convention:                                      ---*/
/*---   /  |  \   "Buffer"+"Can_message_ID"                        ---*/
/*---  /   |   \                                                   ---*/
/*---  ---------                                                   ---*/
/*--------------------------------------------------------------------*/

#define BufferCanId7df                (Buffer0)
#define BufferCanId7e0                (Buffer1)
#define BufferCanIdCAL                (Buffer2)

/*** WARNING : Buffer can not be allocated beyond 24 as 8 buffers are used for Transmit msgs ***/
/*-----------------------------------------------------------------*/
/*--- VIO RECEIVE MESSAGES TYPES DEFINITION                        */
/*--- (for Received messages which have a buffer in Virtual IO) ---*/
/*-----------------------------------------------------------------*/
#define VioRxBufferNotActive (0)
#define VioRxBufferEmpty     (1)
#define VioRxBufferBusy      (2)
#define VioRxBufferFull      (3)
#define VioRxBufferOverrun   (4)

/*****************************************/
/*            CAN OBD config             */
/*****************************************/
/*****************************************/
#define TX_MESSAGE_NUM_OF_CANOBD (2)
#define RX_MESSAGE_NUM_OF_CANOBD (3)
#define TX_MESSAGE_NUM_OF_CANTSW (0)	//note, tsw can config and callback share canobd can config structure.
#define RX_MESSAGE_NUM_OF_CANTSW (2)	//note, tsw can config and callback share canobd can config structure.
#define MESSAGE_NUM_OF_CANOBD    (TX_MESSAGE_NUM_OF_CANOBD + RX_MESSAGE_NUM_OF_CANOBD + TX_MESSAGE_NUM_OF_CANTSW + RX_MESSAGE_NUM_OF_CANTSW)

#define TX_MESSAGE_NUM_OF_J1939 (2)	//note, tsw can config and callback share canobd can config structure.
#define RX_MESSAGE_NUM_OF_J1939 (2)	//note, tsw can config and callback share canobd can config structure.
#define MESSAGE_NUM_OF_J1939    (TX_MESSAGE_NUM_OF_J1939 + RX_MESSAGE_NUM_OF_J1939)

extern CAN_Message_Parameter_T CANOBD_Message_Parameter_Table[MESSAGE_NUM_OF_CANOBD];
extern CAN_Message_Parameter_T Get_CANOBD_Message_Parameter_Table(uint8_t index);
extern J1939_Message_Parameter_T Get_J1939_Message_Parameter_Table(uint8_t index);

extern void Initial_CANOBD_CAL_ID(uint16_t CANID);

#endif


//=============================================================================
//       COPYRIGHT 2005, Delphi Technologies, Inc. All Rights reserved
//                             Delphi Confidential
//
// --------------------------------------------------------------------------
// %name:            io_dcan_config.c %
//
// created_by:       qznx5b
//
// date_created:     Wed. Mar. 2 2005
//
// %derived_by:      tzwfxv %
//
// %date_modified:       %
//
// %version:         4 %
//
//=============================================================================
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/     
#include "io_dcan_config.h" 
#include "cn_io_diagnostic.h" /* For Message_Length_Mismatch                 */
#include "mcamos.h"           /* Add tsw can config here */
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/

/******************************************************************************
 *  Global Variables
 *****************************************************************************/
uint8_t           canobd_tx_rx_buffer[MESSAGE_NUM_OF_CANOBD][8];
uint8_t           J1939_tx_rx_buffer[MESSAGE_NUM_OF_CANOBD][8];
VioCanRxBufferStructType VioCanRxBuffer[RX_MSG_BUFFER_NUMBER];
/******************************************************************************
 *  Global Variable Declarations
 *****************************************************************************/

extern const uint8_t BufferSizeRxMesgControlTable;

/**********************************************************************/
/*** Function prototype                                             ***/
/**********************************************************************/
void Callback_Application_CANOBD( uint32_t message_id);
void Notify_Application_CANOBD( uint32_t message_id);

/* added for tsw can interrupt entry routine */
void Callback_Application_CANTSW( uint32_t message_id);
void Notify_Application_CANTSW( uint32_t  message_id );

/*********************************************************************/
/*** Define CANOBD message parameter  table         ***/
/*********************************************************************/
CAN_Message_Parameter_T   CANOBD_Message_Parameter_Table[MESSAGE_NUM_OF_CANOBD] =
{
   {CanId5e8,   8, 1, &canobd_tx_rx_buffer[0][0], Callback_Application_CANOBD,HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_TRANSMIT }
  ,{CanId7e8,   8, 1, &canobd_tx_rx_buffer[1][0], Callback_Application_CANOBD,HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_TRANSMIT }
  ,{CanId7df,   8, 1, &canobd_tx_rx_buffer[2][0], Notify_Application_CANOBD, HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_RECEIVE}
  ,{CanId7e0,   8, 1, &canobd_tx_rx_buffer[3][0], Notify_Application_CANOBD, HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_RECEIVE}
  ,{CanIdCAL,   8, 1, &canobd_tx_rx_buffer[4][0], Notify_Application_CANOBD, HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_RECEIVE}
  ,{MCAMOS_CANID_7EF,   8, 1, &canobd_tx_rx_buffer[5][0], Notify_Application_CANTSW, HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_RECEIVE}
  ,{MCAMOS_CANID_7EE,   8, 1, &canobd_tx_rx_buffer[6][0], Notify_Application_CANTSW, HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_RECEIVE}
};

/*********************************************************************/
/*** Define J1939 message parameter  table         ***/
/*********************************************************************/
J1939_Message_Parameter_T   J1939_Message_Parameter_Table[MESSAGE_NUM_OF_CANOBD] =
{
   {0x18EA0000,   8, 1, &J1939_tx_rx_buffer[0][0], Callback_Application_CANOBD,HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_TRANSMIT }
  ,{0x18EAAA00,   8, 1, &J1939_tx_rx_buffer[1][0], Callback_Application_CANOBD,HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_TRANSMIT }
  ,{0x18EABB00,   8, 1, &J1939_tx_rx_buffer[2][0], Notify_Application_CANOBD, HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_RECEIVE}
  ,{0x18EACC00,   8, 1, &J1939_tx_rx_buffer[3][0], Notify_Application_CANOBD, HAL_CAN_DEVICE_A,HAL_CAN_MESSAGE_DIRECTION_RECEIVE}
   {J1939_PGN_59904_BASE_ID,      J1939_PGN_59904_LENGTH,  Notify_Application_J1939, FIFO_CAN_MESSAGE,  1, Rx_Index_Method_PDU1_Match},
 };
/****************************************************************/
/***                     RECEPTION TASKS                      ***/
/****************************************************************/
CanRxMessageControlType CanRxMesgControlTable [] = {
/* Functional Request EOBD */
  CanId7df,
  BufferCanId7df,
  CanId7dfRcvdEvent
  ,
/* Diagnostic Information Usdt */
  CanId7e0,
  BufferCanId7e0,
  CanId7e0RcvdEvent
  ,
/* Diagnostic Information Usdt */
  CanIdCAL,
  BufferCanIdCAL,
  CanIdCALRcvdEvent
};

#define RxMsgNbWithRxTimingsControlled (sizeof (CanRxMesgControlTable) / sizeof (CanRxMessageControlType))
const uint8_t BufferSizeRxMesgControlTable = RxMsgNbWithRxTimingsControlled;

void Notify_Application_CANOBD( uint32_t  message_id )
{
   VioCanRxBufferStructType * PtrOnVioCanRxBuffer;
   Can8DataBytesArrayType *Can8DataBytesArrayPtr;
   uint16_t PreviousRxBufferstate;
   uint8_t CanBuffer=0;
   uint8_t found = false;
   uint8_t CAN_message_number = 0;
   uint8_t  Transferlayerbuffernumber = 0;

   /* Bypass message length check because CAN-OBD supports multi-frame mode */
   Clear_Message_Length_Mismatch();

   Transferlayerbuffernumber = Get_Receive_Message_Number_From_Message_ID(message_id); //mzyqz4-sep10
 
   for( CAN_message_number = 0;
        CAN_message_number <  BufferSizeRxMesgControlTable ;
        CAN_message_number++ )
   {
      if( CanRxMesgControlTable[CAN_message_number].CAN_message_ID == message_id )
      {
         found  = 1;
         CanBuffer = CAN_message_number;
         break;
      }
   }

   if (found != false)
   {
      // we have found a matching buffer entry,lets try to process the received msg.
      
     //CanBuffer = CanRxMesgControlTable [CAN_message_number].MessageBufferNumber;

      PtrOnVioCanRxBuffer = &(VioCanRxBuffer [CanBuffer]);

      PreviousRxBufferstate = VioCanRxBuffer[CanBuffer].State; 
      VioCanRxBuffer[CanBuffer].State = VioRxBufferBusy;

      if ( Get_OBD_Message( Transferlayerbuffernumber, PtrOnVioCanRxBuffer->DataBytes ) )
      {
         if (PreviousRxBufferstate == VioRxBufferEmpty) 
         {
            VioCanRxBuffer[CanBuffer].State = VioRxBufferFull;
         }
         else
         {
            VioCanRxBuffer[CanBuffer].State = VioRxBufferOverrun;
         }
         Can8DataBytesArrayPtr =
                   (Can8DataBytesArrayType *) &(VioCanRxBuffer [CanBuffer].DataBytes);
        (*CanRxMesgControlTable [CanBuffer].Task) (Can8DataBytesArrayPtr);

      }
   } 
}

void Callback_Application_CANOBD( uint32_t   CanId)
{
   uint16_t in_msg_obj;
   Can8DataBytesArrayType *Can8DataBytesArrayPtr;

   in_msg_obj = Get_Transmit_Message_Number_From_Message_ID(CanId);
   Can8DataBytesArrayPtr = (Can8DataBytesArrayType *) CANOBD_Message_Parameter_Table[ in_msg_obj].CAN_buffer_ptr; 
   switch (CanId)
   {
      case CanId5e8:
        CanId5e8RcvdEvent(Can8DataBytesArrayPtr);
        break;
      case CanId7e8:
        CanId7e8RcvdEvent(Can8DataBytesArrayPtr);
        break;
   }
}

void Notify_Application_CANTSW( uint32_t  message_id )
{
  if (message_id == MCAMOS_CANID_7EF) {
    MCAMOS_Process_7EF_Message(&canobd_tx_rx_buffer[5][0]);
  } else if (message_id == MCAMOS_CANID_7EE) {
    MCAMOS_Process_7EE_Message(&canobd_tx_rx_buffer[6][0]);
  } else {
    //todo nothing
  }
}

CAN_Message_Parameter_T Get_CANOBD_Message_Parameter_Table(uint8_t index)
{
    return CANOBD_Message_Parameter_Table[index];
}

J1939_Message_Parameter_T Get_J1939_Message_Parameter_Table(uint8_t index)
{
    return J1939_Message_Parameter_Table[index];
}
void Initial_CANOBD_CAL_ID(uint16_t CANID)
{
    CANOBD_Message_Parameter_Table[IndxCanIdCAL].CAN_message_ID = CANID;
    CanRxMesgControlTable[TXIndxCanIdCAL].CAN_message_ID = CANID;
}

/**********************************************************************
*
* Revision History:                                                 
*                                                                    
* Rev.   YYMMDD Who RSM# Change                                  
* ------ ------ --- ---- ---------------------------------------
*3     121017 xll  add CAN ID 0x600 for extended service functional addressing
*4     121224 xjj  add function Get_CANOBD_Message_Parameter_Table & Initial_CANOBD_CAL_ID
**********************************************************************/

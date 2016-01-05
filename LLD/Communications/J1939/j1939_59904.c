/************************************************************************/
/* Copyright Delphi-Delco Electronics 2009                              */
/* Filename - j1939_59904.c                                             */
/* Purpose - Request PGN                                                */
/************************************************************************/
#include "j1939_pgn_config.h"

/***************************************************************************/
/* FUNCTION: Parse_PGN_59904 Request a PGN                                 */
/***************************************************************************/
static void Parse_PGN_59904 (J1939_Receive_Message_Info_T *RxMsg)
{
#if 0
   bool           PgnFound;
   TxMsgIndexType Index;
   uint32_t       RequestedPgn;
   uint32_t       checkPgn;
   /* Byte 1 - Parameter Group Number Bits 23-16 */
   /* Byte 2 - Parameter Group Number Bits 15-8 */
   /* Byte 3 - Parameter Group Number Bits 7-0 */
   RequestedPgn  = (RxMsg->Data[2] << 16);
   RequestedPgn |= (RxMsg->Data[1] << 8);
   RequestedPgn |= RxMsg->Data[0];
   checkPgn      = (RequestedPgn << 8);
   /* Search for matching Tx message that is availble upon request */
   PgnFound = false;

   for (Index = J1939_TX_PGN_65226_INDEX; (! PgnFound) && (Index < J1939_TX_PGN_65280_INDEX); Index++)
   {
      /* Check if message PGN matches the requested PGN and also check if */
      /* the message has a valid service function (CCP2 entries may not)    */
    if ( checkPgn == 
      (J1939_Message_Table[J1939_NO_OF_RECEIVE_MESSAGES + Index].message_ID & (0x03ffff00)) )
       // && (CAN_CkValidTxMsgServiceRoutine (Bus, Index))) 
      {
         PgnFound = true;
         J1939_RequestTxMsgService (Index, J1939_GET_SRC_ADDR(RxMsg->ID));
         J1939_Trigger_Transmit_Message_Service ( (uint8_t) Index);
         break;
      }
   }

   /* If requested PGN not supported then return NEG ACK */
   if ( (! PgnFound) &&
        (J1939_GET_DEST_ADDR (RxMsg->ID) != J1939_GLOBAL_DEST_ADDR))
   {
      J1939_SendUnmanagedAcknowledgement (NegAck, RequestedPgn);
   }
#endif
}


/***************************************************************************/
/* FUNCTION: J1939_RxInit_PGN_59904                                        */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J1939_RxInit_PGN_59904 (J1939_Receive_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Parse_Routine = Parse_PGN_59904;
   MsgCtrl->Message_Lost = 0x00;
   MsgCtrl->Message_Lost_Action_Taken = 0x00;
   MsgCtrl->Message_Lost_Timeout_W = CAN_NO_LOST_TIMER;
   MsgCtrl->Message_Lost_Timer_W = MsgCtrl->Message_Lost_Timeout_W;
}

/***************************************************************************
 * %full_filespec: j1939_59904.c~3:csrc:kok_pt2#1 %
 * %version:           3 %
 * %derived_by:        tzjds6 %
 * %date_modified:     Mon Nov  9 11:37:57 2009 %
 * CHANGE LOG
 *
 * DATE    PRV VER  CHANGE
 * _______ ________ ___________________________________________________
 * 24aug09 M6-01.00 Added support for 2 CAN buses
 * 01may09 M5-35.00 Ported from MEFI-5D (M5-35.00)
****************************************************************************/

/************************************************************************/
/* Copyright Delphi-Delco Electronics 2009                              */
/* Filename - j1939_73_dm11.c                                           */
/* Purpose - J1939/73 diagnostic DM11 (clear Active DTCs)               */
/************************************************************************/
#include "j1939_pgn_config.h"
#include "j1939_tp.h"
#include "j1939_tp_out.h"
#include "j1939_73.h"

/***************************************************************************/
/* FUNCTION: Service_PGN_65235_Ack                                         */
/* DM3, PGN_65228                                                          */
/* Description: Returns response to request to clear logged malf codes     */
/* Note:  MEFI-4B did not impliment the DM3 protocol correctly             */
/*                                                                         */
/* Byte: 0      0 = Positive, 1 = Negative                                 */
/*       1-4    Reserved = 0xFF                                            */
/*       5,7    Pgn of requestor = PGN_65235                               */
/***************************************************************************/
static bool Service_PGN_65235_Ack (J1939_Transmit_Message_Info_T *TxMsg)
{
   TxMsg->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
#if 0
   if (TRUE == ClrJ1939_DM11_Active_Dtcs())
   {
      J1939_SendUnmanagedAcknowledgement (PosAck, J193973_PGN_65235);
   }
   else
   {
      J1939_SendUnmanagedAcknowledgement (NegAck, J193973_PGN_65235);
   }
#endif
   return (false);
}


/***************************************************************************/
/* FUNCTION: J1939_TxInit_PGN_65235_Ack                                    */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J193973_TxInit_PGN_65235_Ack (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = Service_PGN_65235_Ack;
   MsgCtrl->Time_To_Service       = 0x00;
   MsgCtrl->Tx_Timeout           = 0x00;
   MsgCtrl->Time_To_Next_Service_W = CAN_NO_PERIODIC_SERVICE;
   MsgCtrl->Tx_Timeout_Timer_W    = 0x00;
}

/***************************************************************************
 * %full_filespec: j1939_73_dm3.c~2:csrc:kok_pt2#1 %
 * %version:           2 %
 * %derived_by:        tzjds6 %
 * %date_modified:     Thu Sep 17 15:25:05 2009 %
 * CHANGE LOG
 *
 * DATE    PRV VER  CHANGE
 * _______ ________ ___________________________________________________
 * 121016            Added DM11
****************************************************************************/

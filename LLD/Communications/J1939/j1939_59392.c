/************************************************************************/
/* Copyright Delphi-Delco Electronics 2004                              */
/*                                                                      */
/* Filename - j1939_59392.c                                             */
/*                                                                      */
/* Purpose - J1939 Acknowledgement                                      */
/************************************************************************/
#include "j1939_pgn_config.h"
/***************************************************************************/
/* FUNCTION: J1939_SendUnmanagedAcknowledgement                            */
/* Description: Sends an unmanaged acknowledgement.                        */
/* Parameters:                                                             */
/*  Mode :, Positive, Negative, Access Denied, Busy                        */
/* Byte: 0      0 = Positive, 1 = Negative                                 */
/*       1      Group Function Value (if applicable)                       */
/*       2-3    Reserved = 0xFF                                            */
/*       4      Address of sendor that resulted in this acknowledgement    */
/*              (remeber all acknowledgements are sent globally)           */
/*       5,7    Pgn of requestor                                           */
/***************************************************************************/
void J1939_SendUnmanagedAcknowledgement (AckModeType Mode, uint32_t RequestedPgn)
{
  J1939_Transmit_Message_Info_T TxMsg;
  uint32_t Id;

 /* Dest Address is always global for ACK */
  Id = J1939_ADD_THIS_SRC_ADDR (J1939_PGN_59392_BASE_ID);
  TxMsg.ID = J1939_PUT_DEST_ADDR (Id, J1939_GLOBAL_DEST_ADDR);

  TxMsg.Length = J1939_PGN_59392_LENGTH;

  /* Byte 0 = mode */
  TxMsg.Data[0] = (uint8_t)Mode;

  /* Assign Byte 1 - Group Function */
  TxMsg.Data[1] = J1939_DATA_NOT_AVAILABLE; /* Not supported */

  /* Assign Byte 2 - 4 Reserved for assignment by SAE, should be filled with FF*/
  TxMsg.Data[2] = J1939_DATA_NOT_AVAILABLE;
  TxMsg.Data[3] = J1939_DATA_NOT_AVAILABLE;
  TxMsg.Data[4] = J1939_DATA_NOT_AVAILABLE;

  /* Assign Byte 5 - Requested PGN */
  /* Parameter Group Number of requested information */
  /* 8 LSB of parameter group number, bit 8 most significant*/
  TxMsg.Data[5] = (uint8_t)(RequestedPgn & 0x000000FF);
  
  /* Parameter Group Number of requested information */
  /* 2 byte of parameter group number, bit 8 most significant*/
  TxMsg.Data[6] = (uint8_t)((RequestedPgn & 0x0000FF00) >> 8);

  /* Parameter Group Number of requested information */
  /* 8 MSBs of parameter group number, bit 8 most significant*/
  TxMsg.Data[7] = (uint8_t)((RequestedPgn & 0x00FF0000) >> 16);

  //TxMsg.CallBackTime_W = J1939_PGN_59392_FREQ;
  J1939_Transmit_Unmanaged_Message (&TxMsg);
  TxMsg.Callback_Timeout_W = J1939_PGN_59392_TIMEOUT;

}

/***************************************************************************/
/* FUNCTION: J1939_TxInit_SendUnmanagedAcknowledgement                     */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J1939_TxInit_SendUnmanagedAcknowledgement(J1939_Transmit_Message_Control_T *MsgCtrl) 
{
  //MsgCtrl->Service_Routine = J1939_SendUnmanagedAcknowledgement;
  MsgCtrl->Time_To_Service = 0x00;
  MsgCtrl->Time_To_Next_Service_W = CAN_NO_PERIODIC_SERVICE; //Non periodic message
  MsgCtrl->Tx_Timeout = 0x00;
  MsgCtrl->Tx_Timeout_Timer_W = 0x00;
}

/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_73_dm3.c
*  Creation date :
*  Description   :Alarm Message Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/
#include "j1939_pgn_config.h"
#include "j1939_tp.h"
#include "j1939_tp_out.h"
#include "j1939_73.h"
#include "j1939_app.h"

/******************************************************************************
* Function : Service_PGN_65232
* Description : Service PGN
******************************************************************************/
static bool Service_PGN_65232(J1939_Transmit_Message_Info_T *tx_msg_ptr)
{
    J1939_DATA_T *jd = (J1939_DATA_T *)&J1939_73_dm8;

    tx_msg_ptr->ID                 = J1939_ADD_THIS_SRC_ADDR(J193973_PGN_65232_BASE_ID);
    tx_msg_ptr->Length             = J193973_PGN_65232_LENGTH;
    tx_msg_ptr->Data[0]            = jd->data[0];
    tx_msg_ptr->Data[1]            = jd->data[1];
    tx_msg_ptr->Data[2]            = jd->data[2];
    tx_msg_ptr->Data[3]            = jd->data[3];
    tx_msg_ptr->Data[4]            = jd->data[4];
    tx_msg_ptr->Data[5]            = jd->data[5];
    tx_msg_ptr->Data[6]            = jd->data[6];
    tx_msg_ptr->Data[7]            = jd->data[7];
    tx_msg_ptr->Callback_Time_W    = J193973_PGN_65232_FREQ;
    tx_msg_ptr->Callback_Timeout_W = J1939_PGN_65232_TIMEOUT;
    return(true);
}
/******************************************************************************
* Function : J1939_Transmit_Initialize_PGN_65232
* Description : Initialize hooks to can manager
******************************************************************************/
void J193973_TxInit_PGN_65232(J1939_Transmit_Message_Control_T * MsgCtrl) 
{
    MsgCtrl->Service_Routine        = Service_PGN_65232 ;
    MsgCtrl->Time_To_Service        = 0x00;
    MsgCtrl->Time_To_Next_Service_W = J193973_PGN_65232_FREQ;
    MsgCtrl->Tx_Timeout             = 0x00;
    MsgCtrl->Tx_Timeout_Timer_W     = J1939_PGN_65232_TIMEOUT;
    J1939_73_dm8.spn_1226=0x01;
	J1939_73_dm8.spn_1227=0xFFFF;
	J1939_73_dm8.spn_1228=0xFFFF;
	J1939_73_dm8.spn_1225=0x01;
}

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


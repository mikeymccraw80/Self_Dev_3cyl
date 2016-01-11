/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65282.c
*  Creation date :
*  Description   :Status Message1 Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

#include "j1939_pgn_65282.h"


/******************************************************************************
* Function : J1939_PGN_65282
* Description : Status Message1
* Start Posn      Length       Parameter Name
* 1               8              Mode
* 2               8              Time_To_Delivery
* 3               8              Time_To_Cooldown
* 4               8              Output_Voltage
* 5               16              Present_Output_Power
* 7               16              MAX_Output_Power
******************************************************************************/
uint8_t SM1_Message[8];

const Byte_Bit_Fld_T Mode =
        {(uint8_t *)(SM1_Message + 0),7,0};

const Byte_Bit_Fld_T Time_To_Delivery =
        {(uint8_t *)(SM1_Message + 1),7,0};

const Byte_Bit_Fld_T Time_To_Cooldown =
        {(uint8_t *)(SM1_Message + 2),7,0};

const Byte_Bit_Fld_T Output_Voltage =
        {(uint8_t *)(SM1_Message + 3),7,0};

const Word_Bit_Fld_T Present_Output_Power =
        {(uint16_t *)(SM1_Message + 4),15,0};

const Word_Bit_Fld_T MAX_Output_Power =
        {(uint16_t *)(SM1_Message + 6),15,0};

/******************************************************************************
* Function : J1939_Service_PGN_65282
* Description : Service PGN
******************************************************************************/
static bool Service_PGN_65282(J1939_Transmit_Message_Info_T *tx_msg_ptr)
{
    tx_msg_ptr->ID                 = J1939_ADD_THIS_SRC_ADDR(J1939_PGN_65282_BASE_ID);
    tx_msg_ptr->Length             = J1939_PGN_65282_LENGTH;
        tx_msg_ptr->Data[0]        = SM1_Message[0];
        tx_msg_ptr->Data[1]        = SM1_Message[1];
        tx_msg_ptr->Data[2]        = SM1_Message[2];
        tx_msg_ptr->Data[3]        = SM1_Message[3];
        tx_msg_ptr->Data[4]        = SM1_Message[4];
        tx_msg_ptr->Data[5]        = SM1_Message[5];
        tx_msg_ptr->Data[6]        = SM1_Message[6];
        tx_msg_ptr->Data[7]        = SM1_Message[7];
    tx_msg_ptr->Callback_Time_W    = J1939_PGN_65282_FREQ;
    tx_msg_ptr->Callback_Timeout_W = J1939_PGN_65282_TIMEOUT;
    return(true);
}

/******************************************************************************
* Function : J1939_Transmit_Initialize_PGN_65282
* Description : Initialize hooks to can manager
******************************************************************************/
void J1939_Transmit_Initialize_PGN_65282(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr) 
{
    tx_msg_ctrl_ptr->Service_Routine        = Service_PGN_65282 ;
    tx_msg_ctrl_ptr->Time_To_Service        = 0x00;
    tx_msg_ctrl_ptr->Time_To_Next_Service_W = J1939_PGN_65282_FREQ;
    tx_msg_ctrl_ptr->Tx_Timeout             = 0x00;
    tx_msg_ctrl_ptr->Tx_Timeout_Timer_W     = J1939_PGN_65282_TIMEOUT;
}

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


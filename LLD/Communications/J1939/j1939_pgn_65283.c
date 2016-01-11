/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65283.c
*  Creation date :
*  Description   :Status Message2 Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

#include "j1939_pgn_65283.h"


/******************************************************************************
* Function : J1939_PGN_65283
* Description : Status Message2
* Start Posn      Length       Parameter Name
* 1               16              Instantaneous_Fuel_Consumption
* 3               16              Accumulated_Fuel_Consumption
* 6               24              Hour_Meter
******************************************************************************/
uint8_t SM2_Message[8];

const Word_Bit_Fld_T Instantaneous_Fuel_Consumption =
        {(uint16_t *)(SM2_Message + 0),15,0};

const Word_Bit_Fld_T Accumulated_Fuel_Consumption =
        {(uint16_t *)(SM2_Message + 2),15,0};

const Long_Word_Bit_Fld_T Hour_Meter =
        {(uint32_t *)(SM2_Message + 5),23,0};

/******************************************************************************
* Function : J1939_Service_PGN_65283
* Description : Service PGN
******************************************************************************/
static bool Service_PGN_65283(J1939_Transmit_Message_Info_T *tx_msg_ptr)
{
    tx_msg_ptr->ID                 = J1939_ADD_THIS_SRC_ADDR(J1939_PGN_65283_BASE_ID);
    tx_msg_ptr->Length             = J1939_PGN_65283_LENGTH;
        tx_msg_ptr->Data[0]        = SM2_Message[0];
        tx_msg_ptr->Data[1]        = SM2_Message[1];
        tx_msg_ptr->Data[2]        = SM2_Message[2];
        tx_msg_ptr->Data[3]        = SM2_Message[3];
        tx_msg_ptr->Data[4]        = SM2_Message[4];
        tx_msg_ptr->Data[5]        = SM2_Message[5];
        tx_msg_ptr->Data[6]        = SM2_Message[6];
        tx_msg_ptr->Data[7]        = SM2_Message[7];
    tx_msg_ptr->Callback_Time_W    = J1939_PGN_65283_FREQ;
    tx_msg_ptr->Callback_Timeout_W = J1939_PGN_65283_TIMEOUT;
    return(true);
}

/******************************************************************************
* Function : J1939_Transmit_Initialize_PGN_65283
* Description : Initialize hooks to can manager
******************************************************************************/
void J1939_Transmit_Initialize_PGN_65283(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr) 
{
    tx_msg_ctrl_ptr->Service_Routine        = Service_PGN_65283 ;
    tx_msg_ctrl_ptr->Time_To_Service        = 0x00;
    tx_msg_ctrl_ptr->Time_To_Next_Service_W = J1939_PGN_65283_FREQ;
    tx_msg_ctrl_ptr->Tx_Timeout             = 0x00;
    tx_msg_ctrl_ptr->Tx_Timeout_Timer_W     = J1939_PGN_65283_TIMEOUT;
}

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


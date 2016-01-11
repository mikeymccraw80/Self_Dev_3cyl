/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65284.c
*  Creation date :
*  Description   :Alarm Message Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

#include "j1939_pgn_65284.h"


/******************************************************************************
* Function : J1939_PGN_65284
* Description : Alarm Message
* Start Posn      Length       Parameter Name
* 1               3              Unit_Alarm_Fault
* 1               5              Unused1
* 2               5              Fault_Code

* 2               3              Unused2
* 3               4              Alarm_Code
* 3               4              Unused3
* 4               4              Service_Request
* 4               4              Unused4
******************************************************************************/
uint8_t AM_Message[8];

const Byte_Bit_Fld_T Unit_Alarm_Fault =
        {(uint8_t *)(AM_Message + 0),2,0};

const Byte_Bit_Fld_T Unused1 =
        {(uint8_t *)(AM_Message + 0),7,3};

const Byte_Bit_Fld_T Fault_Code
 =
        {(uint8_t *)(AM_Message + 1),4,0};

const Byte_Bit_Fld_T Unused2 =
        {(uint8_t *)(AM_Message + 1),7,5};

const Byte_Bit_Fld_T Alarm_Code =
        {(uint8_t *)(AM_Message + 2),3,0};

const Byte_Bit_Fld_T Unused3 =
        {(uint8_t *)(AM_Message + 2),7,4};

const Byte_Bit_Fld_T Service_Request =
        {(uint8_t *)(AM_Message + 3),3,0};

const Byte_Bit_Fld_T Unused4 =
        {(uint8_t *)(AM_Message + 3),7,4};

/******************************************************************************
* Function : J1939_Service_PGN_65284
* Description : Service PGN
******************************************************************************/
static bool Service_PGN_65284(J1939_Transmit_Message_Info_T *tx_msg_ptr)
{
    tx_msg_ptr->ID                 = J1939_ADD_THIS_SRC_ADDR(J1939_PGN_65284_BASE_ID);
    tx_msg_ptr->Length             = J1939_PGN_65284_LENGTH;
        tx_msg_ptr->Data[0]        = AM_Message[0];
        tx_msg_ptr->Data[1]        = AM_Message[1];
        tx_msg_ptr->Data[2]        = AM_Message[2];
        tx_msg_ptr->Data[3]        = AM_Message[3];
        tx_msg_ptr->Data[4]        = AM_Message[4];
        tx_msg_ptr->Data[5]        = AM_Message[5];
        tx_msg_ptr->Data[6]        = AM_Message[6];
        tx_msg_ptr->Data[7]        = AM_Message[7];
    tx_msg_ptr->Callback_Time_W    = J1939_PGN_65284_FREQ;
    tx_msg_ptr->Callback_Timeout_W = J1939_PGN_65284_TIMEOUT;
    return(true);
}

/******************************************************************************
* Function : J1939_Transmit_Initialize_PGN_65284
* Description : Initialize hooks to can manager
******************************************************************************/
void J1939_Transmit_Initialize_PGN_65284(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr) 
{
    tx_msg_ctrl_ptr->Service_Routine        = Service_PGN_65284 ;
    tx_msg_ctrl_ptr->Time_To_Service        = 0x00;
    tx_msg_ctrl_ptr->Time_To_Next_Service_W = J1939_PGN_65284_FREQ;
    tx_msg_ctrl_ptr->Tx_Timeout             = 0x00;
    tx_msg_ctrl_ptr->Tx_Timeout_Timer_W     = J1939_PGN_65284_TIMEOUT;
#if 0
    AIFPutUnused1(0xff);
    AIFPutUnused2(0xff);
    AIFPutUnused3(0xff);
    AIFPutUnused4(0xff);
#endif
}

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


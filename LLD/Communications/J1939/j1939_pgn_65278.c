/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65278.c
*  Creation date :
*-----------------------------------------------------------------------------
*  Description   :Vehicle Electrical Power 1 Implementation
*-----------------------------------------------------------------------------
*  History       :
*-----------------------------------------------------------------------------
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

#include  "j1939_pgn_65278.h"

/******************************************************************************
* Function : J1939_PGN_65278
* Description : Vehicle Electrical Power 1
* Start Posn      Length in bits      Parameter Name
* 1                 8          Net_Battery_Current
* 2                 8          Alternator_Current
* 3-4                 16          Charging_System_Potential
* 5-6                 16          Batt_Potential_Power_Input_1
* 7-8                 16          Keyswitch_Battery_Potential
******************************************************************************/
static bool J1939_PGN_65278_Message_Ind_Flag;
static bool J1939_PGN_65278_Message_Lost_Ind_Flag;
static uint8_t J1939_PGN_65278_Message[8];
static void J1939_Message_Lost_Routine_PGN_65278(void);
static void J1939_Parse_PGN_65278(J1939_Receive_Message_Info_T *rx_msg_ptr);
 

/******************************************************************************
* Function : J1939_Message_Lost_Routine_PGN_65278
* Description : Reset
******************************************************************************/
static void J1939_Message_Lost_Routine_PGN_65278(void)
{
   J1939_PGN_65278_Message_Lost_Ind_Flag = true;
}

/******************************************************************************
* Function : J1939_Parse_PGN_65278
* Description : Parse Data From Engine. If Raw data equals Enginnering data,
*               copy the data to application signal buffer without any change
******************************************************************************/
static void J1939_Parse_PGN_65278(J1939_Receive_Message_Info_T *rx_msg_ptr)
{
   uint8_t index;
   for( index =0; index<8; index++ )
   {
        J1939_PGN_65278_Message[index] = rx_msg_ptr->Data[index];  //Copy to Application Signal Buffer
   }
   J1939_PGN_65278_Message_Ind_Flag = true;
   J1939_PGN_65278_Message_Lost_Ind_Flag = false;
}

bool J1939_Get_PGN_65278_Message_Indicator(void)
{
   return J1939_PGN_65278_Message_Ind_Flag;
}

bool J1939_Get_PGN_65278_Message_Lost_Indicator(void)
{
   return J1939_PGN_65278_Message_Lost_Ind_Flag;
}

void J1939_Clear_PGN_65278_Message_Indicator(void)
{
   J1939_PGN_65278_Message_Ind_Flag = false;
}

/******************************************************************************
* Function : J1939_Receive_Initialize_PGN_65278
* Description : Initialize hooks to can manager
******************************************************************************/
void J1939_Receive_Initialize_PGN_65278(J1939_Receive_Message_Control_T * rx_msg_ctrl_ptr)
{
   rx_msg_ctrl_ptr->Parse_Routine             = J1939_Parse_PGN_65278;
   rx_msg_ctrl_ptr->Message_Lost_Timeout_W    = J1939_PGN_65278_TIMEOUT; //Message loss timeout setting
   rx_msg_ctrl_ptr->Message_Lost_Timer_W      = rx_msg_ctrl_ptr->Message_Lost_Timeout_W; // software timer for monitoring Message loss
   rx_msg_ctrl_ptr->Message_Lost_Routine      = J1939_Message_Lost_Routine_PGN_65278;
   rx_msg_ctrl_ptr->Message_Lost              = 0x00;
   rx_msg_ctrl_ptr->Message_Lost_Action_Taken = 0x00;
   J1939_PGN_65278_Message_Ind_Flag = false;
   J1939_PGN_65278_Message_Lost_Ind_Flag = false;
}

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


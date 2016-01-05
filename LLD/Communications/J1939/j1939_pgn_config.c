/******************************************************************************
*  Project       : J1939 - PGN Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_config.c
*  Creation date : 10/19/2011
*-----------------------------------------------------------------------------
*  Description   : This module contains J1939 PGN transmit and receive init
*                  tables. The index must match the VBM Table index.
*-----------------------------------------------------------------------------
* Copyright 2011 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

#include "j1939_pgn_config.h"
//#include "j1939_tp.h"

//=============================================================================
// Pointers to Init Routines
// Must Match the Index in VBM Transmit Parameter Table
//=============================================================================
#if 0
const void (*const J1939_Transmit_Initialize[]) (J1939_Transmit_Message_Control_T *) =
{

   J1939_TxInit_TransportOut_0, /* Tx Transport out management connection 0 */
   J1939_TxInit_TransportOut_1, /* Tx Transport out management connection 1 */
   J1939_TxInit_TransportOut_2, /* Tx Transport out management connection 2 */
   J1939_TxInit_TransportIn_0,  /* Tx Transport in management connection 0 */
   J1939_TxInit_TransportIn_1,  /* Tx Transport in management connection 1 */
   J1939_TxInit_TransportIn_2,  /* Tx Transport in management connection 2 */
   J193973_TxInit_PGN_65226,    /*DM1*/
   J193973_TxInit_PGN_65227,    /*DM2*/
   J193973_TxInit_PGN_65228_Ack,/*DM3*/
   J193973_TxInit_PGN_65229,    /*DM4*/
   J193973_TxInit_PGN_65235_Ack,/*DM11*/
   J193973_TxInit_PGN_65236,    /*DM12*/
   J193973_TxInit_PGN_65249,    /*PGN_65249*/
   J193973_TxInit_PGN_65251,    /*PGN_65251*/  
   J1939_Transmit_Initialize_PGN_65280,
   J1939_Transmit_Initialize_PGN_65281,
   J1939_Transmit_Initialize_PGN_65282,
   J1939_Transmit_Initialize_PGN_65283,
   J1939_Transmit_Initialize_PGN_65284,
   J1939_Transmit_Initialize_PGN_65285,
   J1939_Transmit_Initialize_PGN_65286,
   J1939_Transmit_Initialize_PGN_65287,
   J1939_Transmit_Initialize_PGN_65288,
   J1939_Transmit_Initialize_PGN_65289,
   J1939_TxInit_SendUnmanagedAcknowledgement

};
#endif

#ifdef J1939_CH0_SELECTED

//=============================================================================
// Pointers to Init Routines
// Must Match the Index in Channel specific VBM Receive parameter Table
//=============================================================================

const void (*const J1939_Receive_Initialize_Channel_0[]) (J1939_Receive_Message_Control_T *) =
{
   J1939_RxInit_PGN_59904
   	#if 0
   J1939_RxInit_PGN_60160,
   J1939_RxInit_PGN_60416,
   J1939_Receive_Initialize_PGN_65271,
   J1939_Receive_Initialize_PGN_65272,
   J1939_Receive_Initialize_PGN_65273,
   J1939_Receive_Initialize_PGN_65274,
   J1939_Receive_Initialize_PGN_65275,
   J1939_Receive_Initialize_PGN_65276,
   J1939_Receive_Initialize_PGN_65277,
   J1939_Receive_Initialize_PGN_65278,
   J1939_Receive_Initialize_PGN_65279,
   J1939_Receive_Initialize_PGN_65296
   #endif
};

const J1939_Message_Table_T  J1939_Message_Table[J1939_MESSAGES_NUMBER] =
{
// RECEIVE_MESSAGE
   { J1939_PGN_59904_BASE_ID,    J1939_PGN_59904_LENGTH }

//below two were defined in J1939_tp.h
  // , { J1939_PGN_60160_BASE_ID,    J1939_PGN_60160_LENGTH }

   //, { J1939_PGN_60416_BASE_ID,    J1939_PGN_60416_LENGTH }
#if 0
, { 0x18EC0000,    8 }
, { 0x18EC0000,    8 }
   , { J1939_PGN_65271_BASE_ID,    J1939_PGN_65271_LENGTH }

   , { J1939_PGN_65272_BASE_ID,    J1939_PGN_65272_LENGTH }

   , { J1939_PGN_65273_BASE_ID,    J1939_PGN_65273_LENGTH }

   , { J1939_PGN_65274_BASE_ID,    J1939_PGN_65274_LENGTH }

   , { J1939_PGN_65275_BASE_ID,    J1939_PGN_65275_LENGTH }

   , { J1939_PGN_65276_BASE_ID,    J1939_PGN_65276_LENGTH }

   , { J1939_PGN_65277_BASE_ID,    J1939_PGN_65277_LENGTH }

   , { J1939_PGN_65278_BASE_ID,    J1939_PGN_65278_LENGTH }

   , { J1939_PGN_65279_BASE_ID,    J1939_PGN_65279_LENGTH }

   , { J1939_PGN_65296_BASE_ID,    J1939_PGN_65296_LENGTH }

// TRANSMIT_MESSAGE
   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport out management connection 0 */

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport out management connection 1 */

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport out management connection 2 */

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport in management connection 0 */

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport in management connection 1*/

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport in management connection 2 */

   , { J193973_PGN_65226_BASE_ID, J193973_PGN_65226_LENGTH }

   , { J193973_PGN_65227_BASE_ID, J193973_PGN_65227_LENGTH }

   , { J193973_PGN_65228_BASE_ID, J193973_PGN_65228_LENGTH }

   , { J193973_PGN_65229_BASE_ID, J193973_PGN_65229_LENGTH }

   , { J193973_PGN_65235_BASE_ID, J193973_PGN_65235_LENGTH }

   , { J193973_PGN_65236_BASE_ID, J193973_PGN_65236_LENGTH }

   , { J193973_PGN_65249_BASE_ID, J193973_PGN_65249_LENGTH }

   , { J193973_PGN_65251_BASE_ID, J193973_PGN_65251_LENGTH }
   
   , { J1939_PGN_65280_BASE_ID,    J1939_PGN_65280_LENGTH }

   , { J1939_PGN_65281_BASE_ID,    J1939_PGN_65281_LENGTH }

   , { J1939_PGN_65282_BASE_ID,    J1939_PGN_65282_LENGTH }

   , { J1939_PGN_65283_BASE_ID,    J1939_PGN_65283_LENGTH }

   , { J1939_PGN_65284_BASE_ID,    J1939_PGN_65284_LENGTH }

   , { J1939_PGN_65285_BASE_ID,    J1939_PGN_65285_LENGTH }

   , { J1939_PGN_65286_BASE_ID,    J1939_PGN_65286_LENGTH }

   , { J1939_PGN_65287_BASE_ID,    J1939_PGN_65287_LENGTH }

   , { J1939_PGN_65288_BASE_ID,    J1939_PGN_65288_LENGTH }

   , { J1939_PGN_65289_BASE_ID,    J1939_PGN_65289_LENGTH }

   , { J1939_DENY_REQUEST_PGN, 8} /* Unmanaged Acknowledgement */
#endif
};

#endif
const uint8_t J1939_NO_OF_RECEIVE_MESSAGES_CHANNEL_0 = J1939_RECEIVE_MESSAGES_NUMBER_CHANNEL_0;
const uint8_t J1939_NO_OF_RECEIVE_MESSAGES_CHANNEL_1 = J1939_RECEIVE_MESSAGES_NUMBER_CHANNEL_1;
const uint8_t J1939_NO_OF_TRANSMIT_MESSAGES_CHANNEL_0 = J1939_TRANSMIT_MESSAGES_NUMBER_CHANNEL_0;
const uint8_t J1939_NO_OF_TRANSMIT_MESSAGES_CHANNEL_1 = J1939_TRANSMIT_MESSAGES_NUMBER_CHANNEL_1;

const uint8_t J1939_NO_OF_RECEIVE_MESSAGES            = J1939_RECEIVE_MESSAGES_NUMBER;
const uint8_t J1939_NO_OF_TRANSMIT_MESSAGES           = J1939_TRANSMIT_MESSAGES_NUMBER;
const uint8_t J1939_NO_OF_MESSAGES                    = J1939_MESSAGES_NUMBER;

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  =================     ==========================      *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release       *
* 2        03/06/2012    nz8l7x                code clean up                  *
* 3        11/15/2012    cjqq                  Add DM information             *
******************************************************************************/
/*-------------------------------------------------------------------*/
/* j1939_pgn_config.c  rev.     - 22 Aug 2014 - Xi Yanpeng           */
/*                                                                   */
/* -Add PGN65251 PGN65259 Configurations                             */
/*-------------------------------------------------------------------*/


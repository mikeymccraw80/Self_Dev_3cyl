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
#include "j1939_tp.h"

//=============================================================================
// Pointers to Init Routines
// Must Match the Index in VBM Transmit Parameter Table
//=============================================================================

const void (*const J1939_Transmit_Initialize[]) (J1939_Transmit_Message_Control_T *) =
{
#if J1939_DENY_REQUEST_SUPPORTED
   J1939_TxInit_TransportOut_0, /* Tx Transport out management connection 0 */
   J1939_TxInit_TransportOut_1, /* Tx Transport out management connection 1 */
   J1939_TxInit_TransportOut_2, /* Tx Transport out management connection 2 */
   J1939_TxInit_TransportIn_0,  /* Tx Transport in management connection 0 */
   J1939_TxInit_TransportIn_1,  /* Tx Transport in management connection 1 */
   J1939_TxInit_TransportIn_2,  /* Tx Transport in management connection 2 */
#endif
#if J193973_PGN_65226_SUPPORTED
   J193973_TxInit_PGN_65226,    /*DM1*/
#endif
#if J193973_PGN_65227_SUPPORTED
   J193973_TxInit_PGN_65227,    /*DM2*/
#endif
#if J193973_PGN_65228_SUPPORTED
   J193973_TxInit_PGN_65228_Ack,/*DM3*/
#endif
#if J193973_PGN_65229_SUPPORTED
   J193973_TxInit_PGN_65229,    /*DM4*/
#endif
#if J193973_PGN_65230_SUPPORTED
   J193973_TxInit_PGN_65230,    /*DM5*/
#endif
#if J193973_PGN_65235_SUPPORTED
   J193973_TxInit_PGN_65235_Ack,/*DM11*/
#endif
#if J193973_PGN_65236_SUPPORTED
   J193973_TxInit_PGN_65236,    /*DM12*/
#endif
#if J193973_PGN_65249_SUPPORTED
   J193973_TxInit_PGN_65249,    /*PGN_65249*/
#endif
#if J193973_PGN_65251_SUPPORTED
   J193973_TxInit_PGN_65251,    /*PGN_65251*/  
#endif
#if J1939_PGN_64965_SUPPORTED
   J1939_TxInit_PGN_64965,            /* john deere ecuid */
#endif
#if J1939_PGN_65242_SUPPORTED
   J1939_TxInit_PGN_65242,            /* john deere soft */
#endif
#if J1939_PGN_61444_SUPPORTED
   J1939_Transmit_Initialize_PGN_61444, /* john deere EEC1 */
#endif
#if J1939_PGN_61443_SUPPORTED
   J1939_Transmit_Initialize_PGN_61443, /* john deere EEC2 */
#endif
#if J1939_PGN_65247_SUPPORTED
   J1939_Transmit_Initialize_PGN_65247, /* john deere EEC3 */
#endif
#if J1939_PGN_64997_SUPPORTED
   J1939_Transmit_Initialize_PGN_64997, /* john deere MVS */
#endif
#if J1939_PGN_65266_SUPPORTED
   J1939_Transmit_Initialize_PGN_65266, /* john deere LFE */
#endif
#if J1939_PGN_65262_SUPPORTED
   J1939_Transmit_Initialize_PGN_65262, /* john deere ET1 */
#endif
#if J1939_PGN_65263_SUPPORTED
   J1939_Transmit_Initialize_PGN_65263, /* john deere EFL/P1 */
#endif
#if J1939_PGN_65270_SUPPORTED
   J1939_Transmit_Initialize_PGN_65270, /* john deere IC1 */
#endif
#if J1939_PGN_65271_SUPPORTED
   J1939_Transmit_Initialize_PGN_65271, /* john deere VEP1 */
#endif
#if J1939_PGN_65213_SUPPORTED
   J1939_Transmit_Initialize_PGN_65213, /* john deere FD */
#endif
#if J1939_PGN_65253_SUPPORTED
   J1939_Transmit_Initialize_PGN_65253, /* john deere Hours */
#endif
#if J1939_PGN_65232_SUPPORTED
   J193973_TxInit_PGN_65232, /* j1939 73 dm8 */
#endif
#if J1939_PGN_65289_SUPPORTED
   J1939_TxInit_PGN_65289, /* john deere TLA */
#endif
#if J1939_PGN_60928_SUPPORTED
   J1939_TxInit_PGN_60928, /* john deere Address Claim */
#endif
#if J1939_PGN_65299_SUPPORTED
   J1939_TxInit_PGN_65299, /* john deere defined PGN */
#endif
#if J1939_PGN_65154_SUPPORTED
   J1939_TxInit_PGN_65154, /* john deere IT1 */
#endif
#if J1939_PGN_55808_SUPPORTED
   J1939_TxInit_PGN_55808,
#endif
#if J1939_DENY_REQUEST_SUPPORTED
   J1939_TxInit_SendUnmanagedAcknowledgement
#endif
};


#ifdef J1939_CH0_SELECTED

//=============================================================================
// Pointers to Init Routines
// Must Match the Index in Channel specific VBM Receive parameter Table
//=============================================================================

const void (*const J1939_Receive_Initialize_Channel_0[]) (J1939_Receive_Message_Control_T *) =
{
#if J1939_PGN_59904_SUPPORTED
   J1939_RxInit_PGN_59904,
#endif
#if J1939_PGN_60160_SUPPORTED
   J1939_RxInit_PGN_60160,
#endif
#if J1939_PGN_60416_SUPPORTED
   J1939_RxInit_PGN_60416,
#endif
#if J1939_PGN_57344_SUPPORTED
   J1939_Receive_Initialize_PGN_57344,
#endif
#if J1939_PGN_00000_SUPPORTED_ICC
   J1939_Receive_Initialize_PGN_00000_ICC,
#endif
#if J1939_73_dm7_SUPPORTED
   J1939_Receive_Initialize_73_dm7,
#endif
#if J1939_73_dm13_SUPPORTED
   J1939_Receive_Initialize_73_dm13,
#endif
#if J1939_PGN_65265_SUPPORTED
   J1939_Receive_Initialize_PGN_65265,
#endif
#if J1939_PGN_64971_SUPPORTED
   J1939_Receive_Initialize_PGN_64971,
#endif
#if J1939_PGN_61442_SUPPORTED
   J1939_Receive_Initialize_PGN_61442,
#endif
#if J1939_PGN_61445_SUPPORTED
   J1939_Receive_Initialize_PGN_61445,
#endif
#if J1939_PGN_65298_SUPPORTED
   J1939_Receive_Initialize_PGN_65298,
#endif
#if J1939_PGN_65276_SUPPORTED
   J1939_Receive_Initialize_PGN_65276,
#endif
#if J1939_PGN_65277_SUPPORTED
   J1939_Receive_Initialize_PGN_65277,
#endif
#if J1939_PGN_65278_SUPPORTED
   J1939_Receive_Initialize_PGN_65278,
#endif
#if J1939_PGN_65279_SUPPORTED
   J1939_Receive_Initialize_PGN_65279,
#endif
#if J1939_PGN_65296_SUPPORTED
   J1939_Receive_Initialize_PGN_65296,
#endif
#if J1939_PGN_55808_SUPPORTED
   J1939_RxInit_PGN_55808,
#endif
#if J1939_PGN_00000_SUPPORTED_TCU
   J1939_Receive_Initialize_PGN_00000_TCU
#endif
};

const J1939_Message_Table_T  J1939_Message_Table[J1939_MESSAGES_NUMBER] =
{
// RECEIVE_MESSAGE
#if J1939_PGN_59904_SUPPORTED
   { J1939_PGN_59904_BASE_ID,    J1939_PGN_59904_LENGTH }
#endif
#if J1939_PGN_60160_SUPPORTED
   , { J1939_PGN_60160_BASE_ID,    J1939_PGN_60160_LENGTH }
#endif
#if J1939_PGN_60416_SUPPORTED
   , { J1939_PGN_60416_BASE_ID,    J1939_PGN_60416_LENGTH }
#endif
#if J1939_PGN_57344_SUPPORTED
   , { J1939_PGN_57344_BASE_ID,    J1939_PGN_57344_LENGTH }
#endif
#if J1939_PGN_00000_SUPPORTED_ICC
  , { J1939_PGN_00000_BASE_ID_ICC,    J1939_PGN_00000_LENGTH_ICC }
#endif
#if J1939_73_dm7_SUPPORTED
    , { J1939_73_dm7_BASE_ID,    J1939_73_dm7_LENGTH }
 #endif
#if J1939_73_dm13_SUPPORTED
   , { J193973_PGN_57088_BASE_ID,    J1939_PGN_65296_LENGTH }
#endif
#if J1939_PGN_65265_SUPPORTED
  , { J1939_PGN_65265_BASE_ID,    J1939_PGN_65265_LENGTH }
#endif
#if J1939_PGN_64971_SUPPORTED
   , { J1939_PGN_64971_BASE_ID,    J1939_PGN_64971_LENGTH }
#endif
#if J1939_PGN_61442_SUPPORTED
   , { J1939_PGN_61442_BASE_ID,    J1939_PGN_61442_LENGTH }
#endif
#if J1939_PGN_61445_SUPPORTED
   , { J1939_PGN_61445_BASE_ID,    J1939_PGN_61445_LENGTH }
#endif
#if J1939_PGN_65298_SUPPORTED
   , { J1939_PGN_65298_BASE_ID,    J1939_PGN_65298_LENGTH }
#endif
#if J1939_PGN_65276_SUPPORTED
   , { J1939_PGN_65276_BASE_ID,    J1939_PGN_65276_LENGTH }
#endif
#if J1939_PGN_65277_SUPPORTED
   , { J1939_PGN_65277_BASE_ID,    J1939_PGN_65277_LENGTH }
#endif
#if J1939_PGN_65278_SUPPORTED
   , { J1939_PGN_65278_BASE_ID,    J1939_PGN_65278_LENGTH }
#endif
#if J1939_PGN_65279_SUPPORTED
   , { J1939_PGN_65279_BASE_ID,    J1939_PGN_65279_LENGTH }
#endif
#if J1939_PGN_55808_SUPPORTED
   , {J1939_PGN_55808_BASE_ID,    J1939_PGN_55808_LENGTH}
#endif
#if J1939_PGN_65296_SUPPORTED
   , { J1939_PGN_65296_BASE_ID,    J1939_PGN_65296_LENGTH }
#endif
#if J1939_PGN_00000_SUPPORTED_TCU
   , { J1939_PGN_00000_BASE_ID_TCU,    J1939_PGN_00000_LENGTH_TCU }
#endif

// TRANSMIT_MESSAGE
#if J1939_DENY_REQUEST_SUPPORTED
   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport out management connection 0 */

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport out management connection 1 */

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport out management connection 2 */

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport in management connection 0 */

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport in management connection 1*/

   , { J1939_DENY_REQUEST_PGN, 8} /* Tx Transport in management connection 2 */
#endif                       
#if J193973_PGN_65226_SUPPORTED
   , { J193973_PGN_65226_BASE_ID, J193973_PGN_65226_LENGTH }
#endif
#if J193973_PGN_65227_SUPPORTED
   , { J193973_PGN_65227_BASE_ID, J193973_PGN_65227_LENGTH }
#endif
#if J193973_PGN_65228_SUPPORTED
   , { J193973_PGN_65228_BASE_ID, J193973_PGN_65228_LENGTH }
#endif
#if J193973_PGN_65229_SUPPORTED
   , { J193973_PGN_65229_BASE_ID, J193973_PGN_65229_LENGTH }
#endif
#if J193973_PGN_65230_SUPPORTED
   , { J193973_PGN_65230_BASE_ID, J193973_PGN_65230_LENGTH }  
#endif
#if J193973_PGN_65235_SUPPORTED
   , { J193973_PGN_65235_BASE_ID, J193973_PGN_65235_LENGTH }
#endif
#if J193973_PGN_65236_SUPPORTED
   , { J193973_PGN_65236_BASE_ID, J193973_PGN_65236_LENGTH }
#endif
#if J193973_PGN_65249_SUPPORTED
   , { J193973_PGN_65249_BASE_ID, J193973_PGN_65249_LENGTH }
#endif
#if J193973_PGN_65251_SUPPORTED
   , { J193973_PGN_65251_BASE_ID, J193973_PGN_65251_LENGTH }
 #endif
#if J1939_PGN_64965_SUPPORTED  
   , {J1939_PGN_64965_BASE_ID,         J1939_PGN_64965_LENGTH }
#endif
#if J1939_PGN_65242_SUPPORTED
   , {J1939_PGN_65242_BASE_ID,         J1939_PGN_65242_LENGTH}
#endif
#if J1939_PGN_61444_SUPPORTED
  ,  {J1939_PGN_61444_BASE_ID,         J1939_PGN_61444_LENGTH}
#endif
#if J1939_PGN_61443_SUPPORTED
   , {J1939_PGN_61443_BASE_ID,         J1939_PGN_61443_LENGTH}
#endif
#if J1939_PGN_65247_SUPPORTED
   , {J1939_PGN_65247_BASE_ID,         J1939_PGN_65247_LENGTH}
#endif
#if J1939_PGN_64997_SUPPORTED
   , {J1939_PGN_64997_BASE_ID,         J1939_PGN_64997_LENGTH}
#endif
#if J1939_PGN_65266_SUPPORTED
   , {J1939_PGN_65266_BASE_ID,         J1939_PGN_65266_LENGTH}
#endif
#if J1939_PGN_65262_SUPPORTED
   , {J1939_PGN_65262_BASE_ID,         J1939_PGN_65262_LENGTH}
#endif
#if J1939_PGN_65263_SUPPORTED
   , {J1939_PGN_65263_BASE_ID,         J1939_PGN_65263_LENGTH}
#endif
#if J1939_PGN_65270_SUPPORTED
   , {J1939_PGN_65270_BASE_ID,         J1939_PGN_65270_LENGTH}
#endif
#if J1939_PGN_65271_SUPPORTED
   , {J1939_PGN_65271_BASE_ID,         J1939_PGN_65271_LENGTH}
#endif
#if J1939_PGN_65213_SUPPORTED
   , {J1939_PGN_65213_BASE_ID,         J1939_PGN_65213_LENGTH}
#endif
#if J1939_PGN_65253_SUPPORTED
   , {J1939_PGN_65253_BASE_ID,         J1939_PGN_65253_LENGTH}
#endif
#if J1939_PGN_65232_SUPPORTED
   , {J193973_PGN_65232_BASE_ID,       J193973_PGN_65232_LENGTH}
#endif
#if J1939_PGN_65289_SUPPORTED
   , {J1939_PGN_65289_BASE_ID,       J1939_PGN_65289_LENGTH}
#endif
#if 	J1939_PGN_60928_SUPPORTED
   , {J1939_PGN_60928_BASE_ID,       J1939_PGN_60928_LENGTH}
#endif
#if 	J1939_PGN_65299_SUPPORTED
   , {J1939_PGN_65299_BASE_ID,       J1939_PGN_65299_LENGTH}
#endif
#if J1939_PGN_65154_SUPPORTED
   , {J1939_PGN_65154_BASE_ID,       J1939_PGN_65154_LENGTH}
#endif
#if J1939_PGN_55808_SUPPORTED
   , {J1939_PGN_55808_BASE_ID,       J1939_PGN_55808_LENGTH}
#endif
#if J1939_DENY_REQUEST_SUPPORTED
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


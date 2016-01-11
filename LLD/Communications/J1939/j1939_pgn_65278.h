/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65278.h
*  Creation date :
*  Description   :Vehicle Electrical Power 1 Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

/*-------------------------------------------------------------------
* to avoid multiple definition if the file is included several times
*-------------------------------------------------------------------*/
#ifndef J1939_PGN_65278_DEF
#define J1939_PGN_65278_DEF

#include "j1939_pgn_config.h"
#include "j1939_bit_fields.h"



extern bool J1939_Get_PGN_65278_Message_Indicator(void);
extern bool J1939_Get_PGN_65278_Message_Lost_Indicator(void);
extern void J1939_Clear_PGN_65278_Message_Indicator(void);


#endif

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


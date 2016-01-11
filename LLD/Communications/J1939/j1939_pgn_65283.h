/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65283.h
*  Creation date :
*  Description   :Status Message2 Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

/*-------------------------------------------------------------------
* to avoid multiple definition if the file is included several times
*-------------------------------------------------------------------*/
#ifndef J1939_PGN_65283_DEF
#define J1939_PGN_65283_DEF

#include "j1939_pgn_config.h"
#include "j1939_bit_fields.h"


extern const Word_Bit_Fld_T Instantaneous_Fuel_Consumption;
extern const Word_Bit_Fld_T Accumulated_Fuel_Consumption;
extern const Long_Word_Bit_Fld_T Hour_Meter;


#define AIFPutInstantaneous_Fuel_Consumption(x)      Write_Word_Bit_Fld(&Instantaneous_Fuel_Consumption,x)
#define AIFPutAccumulated_Fuel_Consumption(x)      Write_Word_Bit_Fld(&Accumulated_Fuel_Consumption,x)
#define AIFPutHour_Meter(x)      Write_Long_Word_Into_Odd_Add_Bit_Fld(&Hour_Meter,x)
 
#endif

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


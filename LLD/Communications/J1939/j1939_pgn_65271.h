/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65271.h
*  Creation date :
*  Description   :Vehicle Electrical Power 1 Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

/*-------------------------------------------------------------------
* to avoid multiple definition if the file is included several times
*-------------------------------------------------------------------*/
#ifndef J1939_PGN_65271_DEF
#define J1939_PGN_65271_DEF

#include "j1939_pgn_config.h"
#include "j1939_bit_fields.h"


extern const Byte_Bit_Fld_T Net_Battery_Current;
extern const Byte_Bit_Fld_T Alternator_Current;
extern const Word_Bit_Fld_T Charging_System_Potential;
extern const Word_Bit_Fld_T Batt_Potential_Power_Input_1;
extern const Word_Bit_Fld_T Keyswitch_Battery_Potential;


#define AIFGetNet_Battery_Current()    Read_Byte_Bit_Fld(&Net_Battery_Current)
#define AIFGetAlternator_Current()    Read_Byte_Bit_Fld(&Alternator_Current)
#define AIFGetCharging_System_Potential()    Read_Unsigned_Word_Bit_Fld(&Charging_System_Potential)
#define AIFGetBatt_Potential_Power_Input_1()    Read_Unsigned_Word_Bit_Fld(&Batt_Potential_Power_Input_1)
#define AIFGetKeyswitch_Battery_Potential()    Read_Unsigned_Word_Bit_Fld(&Keyswitch_Battery_Potential)


extern bool J1939_Get_PGN_65271_Message_Indicator(void);
extern bool J1939_Get_PGN_65271_Message_Lost_Indicator(void);
extern void J1939_Clear_PGN_65271_Message_Indicator(void);


#endif

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


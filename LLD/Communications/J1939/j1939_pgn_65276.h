/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65276.h
*  Creation date :
*  Description   :Dash Display Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

/*-------------------------------------------------------------------
* to avoid multiple definition if the file is included several times
*-------------------------------------------------------------------*/
#ifndef J1939_PGN_65276_DEF
#define J1939_PGN_65276_DEF

#include "j1939_pgn_config.h"
#include "j1939_bit_fields.h"


extern const Byte_Bit_Fld_T Washer_Fluid_Level;
extern const Byte_Bit_Fld_T Fuel_Level_1;
extern const Byte_Bit_Fld_T Engine_Fuel_Filt_Diff_Pressure;
extern const Byte_Bit_Fld_T Engine_Oil_Filt_Diff_Pressure;
extern const Byte_Bit_Fld_T Fuel_Level_2;
extern const Word_Bit_Fld_T Cargo_Ambient_Temperature;


#define AIFGetWasher_Fluid_Level()    Read_Byte_Bit_Fld(&Washer_Fluid_Level)
#define AIFGetFuel_Level_1()    Read_Byte_Bit_Fld(&Fuel_Level_1)
#define AIFGetEngine_Fuel_Filt_Diff_Pressure()    Read_Byte_Bit_Fld(&Engine_Fuel_Filt_Diff_Pressure)
#define AIFGetEngine_Oil_Filt_Diff_Pressure()    Read_Byte_Bit_Fld(&Engine_Oil_Filt_Diff_Pressure)
#define AIFGetFuel_Level_2()    Read_Byte_Bit_Fld(&Fuel_Level_2)
#define AIFGetCargo_Ambient_Temperature()    Read_Unsigned_Word_Bit_Fld(&Cargo_Ambient_Temperature)


extern bool J1939_Get_PGN_65276_Message_Indicator(void);
extern bool J1939_Get_PGN_65276_Message_Lost_Indicator(void);
extern void J1939_Clear_PGN_65276_Message_Indicator(void);


#endif

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


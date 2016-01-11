/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65282.h
*  Creation date :
*  Description   :Status Message1 Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

/*-------------------------------------------------------------------
* to avoid multiple definition if the file is included several times
*-------------------------------------------------------------------*/
#ifndef J1939_PGN_65282_DEF
#define J1939_PGN_65282_DEF

#include "j1939_pgn_config.h"
#include "j1939_bit_fields.h"


extern const Byte_Bit_Fld_T Mode;
extern const Byte_Bit_Fld_T Time_To_Delivery;
extern const Byte_Bit_Fld_T Time_To_Cooldown;
extern const Byte_Bit_Fld_T Output_Voltage;
extern const Word_Bit_Fld_T Present_Output_Power;
extern const Word_Bit_Fld_T MAX_Output_Power;

 

#define AIFPutMode(x)      Write_Byte_Bit_Fld(&Mode,x)
#define AIFPutTime_To_Delivery(x)      Write_Byte_Bit_Fld(&Time_To_Delivery,x)
#define AIFPutTime_To_Cooldown(x)      Write_Byte_Bit_Fld(&Time_To_Cooldown,x)
#define AIFPutOutput_Voltage(x)      Write_Byte_Bit_Fld(&Output_Voltage,x)
#define AIFPutPresent_Output_Power(x)      Write_Word_Bit_Fld(&Present_Output_Power,x)
#define AIFPutMAX_Output_Power(x)      Write_Word_Bit_Fld(&MAX_Output_Power,x)
 
#endif

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


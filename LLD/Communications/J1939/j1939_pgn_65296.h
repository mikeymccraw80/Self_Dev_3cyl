/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65296.h
*  Creation date :
*  Description   :Remote Activation Message Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

/*-------------------------------------------------------------------
* to avoid multiple definition if the file is included several times
*-------------------------------------------------------------------*/
#ifndef J1939_PGN_65296_DEF
#define J1939_PGN_65296_DEF

#include "j1939_pgn_config.h"
#include "j1939_bit_fields.h"


extern const Byte_Bit_Fld_T Operating_Cond_Update;
extern const Byte_Bit_Fld_T Service_Requested;
extern const Byte_Bit_Fld_T Desired_Output_Voltage;


#define AIFGetOperating_Cond_Update()    Read_Byte_Bit_Fld(&Operating_Cond_Update)
#define AIFGetService_Requested()    Read_Byte_Bit_Fld(&Service_Requested)
#define AIFGetDesired_Output_Voltage()    Read_Byte_Bit_Fld(&Desired_Output_Voltage)


extern bool J1939_Get_PGN_65296_Message_Indicator(void);
extern bool J1939_Get_PGN_65296_Message_Lost_Indicator(void);
extern void J1939_Clear_PGN_65296_Message_Indicator(void);


#endif

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65284.h
*  Creation date :
*  Description   :Alarm Message Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

/*-------------------------------------------------------------------
* to avoid multiple definition if the file is included several times
*-------------------------------------------------------------------*/
#ifndef J1939_PGN_65284_DEF
#define J1939_PGN_65284_DEF

#include "j1939_pgn_config.h"
#include "j1939_bit_fields.h"


extern const Byte_Bit_Fld_T Unit_Alarm_Fault;
extern const Byte_Bit_Fld_T Unused1;
extern const Byte_Bit_Fld_T Fault_Code;
extern const Byte_Bit_Fld_T Unused2;
extern const Byte_Bit_Fld_T Alarm_Code;
extern const Byte_Bit_Fld_T Unused3;
extern const Byte_Bit_Fld_T Service_Request;
extern const Byte_Bit_Fld_T Unused4;


#define AIFPutUnit_Alarm_Fault(x)   Write_Byte_Bit_Fld(&Unit_Alarm_Fault,x)
#define AIFPutUnused1(x)            Write_Byte_Bit_Fld(&Unused1,x)
#define AIFPutFault_Code(x)         Write_Byte_Bit_Fld(&Fault_Code,x)
#define AIFPutUnused2(x)            Write_Byte_Bit_Fld(&Unused2,x)
#define AIFPutAlarm_Code(x)         Write_Byte_Bit_Fld(&Alarm_Code,x)
#define AIFPutUnused3(x)            Write_Byte_Bit_Fld(&Unused3,x)
#define AIFPutService_Request(x)    Write_Byte_Bit_Fld(&Service_Request,x)
#define AIFPutUnused4(x)            Write_Byte_Bit_Fld(&Unused4,x)

#endif

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


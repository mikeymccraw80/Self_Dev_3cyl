/******************************************************************************
 *
 * Filename:          j1939_app.c
 *
 * Description:       This module contains all of the stub funtion
 *                    needed for Weichai
 *
 * Global Functions Defined:
 *                    Sinit_ResetToKeyOn
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 1999-2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %derived_by:    jzjv3m %
 * %full_name:     ctc_pt3#5/csrc/weichaiapp.c/9 %
 * %date_created:  Tue Jun 10 14:09:02 2014 %
 * %version:       9 %
 *
 *****************************************************************************/

/******************************************************************************
 *  System Include Files
 *****************************************************************************/


/******************************************************************************
 *  Global I/O Include Files
 *****************************************************************************/
#include "j1939_app.h"
#include "j1939_pgn_config.h"


uint8_t J1939_DM1_Message[J1939_DM1_BUFFER_SIZE] =
{
   0x00, 0xFF, 0x00, 0xFE, 0xCA, 0x00, 0x00, 0x97, 0x03, 0x8a, 0x00,
   0x51, 0x63, 0x8a
};

uint16_t J1939_DM1_DTCs;

uint8_t J1939_PGN_65251_Message[J1939_PGN_65251_BUFFER_SIZE];

uint8_t J1939_PGN_65249_Message[J1939_PGN_65249_BUFFER_SIZE];

uint8_t J1939_DM2_Message[J1939_DM2_BUFFER_SIZE] =
{
   0x00, 0xFF, 0x00, 0xFE, 0xCA, 0x00, 0x00, 0x97, 0x03, 0x8a, 0x00,
   0x51, 0x63, 0x8a
};

uint16_t J1939_DM2_PreActiveDTCs;

bool J1939_DM3_Clr_PreActive_Dtcs;

uint8_t J1939_DM4_Message[J1939_DM4_BUFFER_SIZE] =
{
   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
   0x0B, 0x0C, 0x0D
};

bool J1939_DM11_Clr_Active_Dtcs;

uint8_t J1939_DM12_Message[J1939_DM12_BUFFER_SIZE] =
{
   0x00, 0xFF, 0x00, 0xFE, 0xCA, 0x00, 0x00, 0x97, 0x03, 0x8a, 0x00,
   0x51, 0x63, 0x8a
};

uint16_t J1939_DM12_EmissionsRelated_ActiveDTCs;



uint8_t *GetJ1939_DM1_MsgPtr (void)
{
   return J1939_DM1_Message;
}

uint16_t GetJ1939_DM1_ActiveDTC_NUMBER (void)
{
   return J1939_DM1_DTCs;
}

uint8_t *GetJ1939_PGN_65251_MsgPtr (void)
{
   return J1939_PGN_65251_Message;
}
uint8_t *GetJ1939_PGN_65249_MsgPtr (void)
{
   return J1939_PGN_65249_Message;
}

uint16_t GetJ1939_PGN_65251_BYTE_NUMBER (void)
{
   return J1939_PGN_65251_BUFFER_SIZE;
}
uint16_t GetJ1939_PGN_65249_BYTE_NUMBER (void)
{
   return J1939_PGN_65249_BUFFER_SIZE;
}

uint8_t *GetJ1939_DM2_MsgPtr (void)
{
   return J1939_DM2_Message;
}

uint16_t GetJ1939_DM2_PreActiveDTC_NUMBER (void)
{
   return J1939_DM2_PreActiveDTCs;
}

uint8_t *GetJ1939_DM4_MsgPtr (void)
{
   return J1939_DM4_Message;
}

uint8_t *GetJ1939_DM12_MsgPtr (void)
{
   return J1939_DM12_Message;
}

uint16_t GetJ1939_DM12_EmissionsRelated_ActiveDTCs_Number (void)
{
   return J1939_DM12_EmissionsRelated_ActiveDTCs;
}

bool ClrJ1939_DM3_PreActive_Dtcs (void)
{
   //Add the hook function to clear previous active DTCs here
   //return true if all the previous active DTCs have been cleared or no fault
   //return false if the clear action can't be performed.
   return J1939_DM3_Clr_PreActive_Dtcs;
}

bool ClrJ1939_DM11_Active_Dtcs (void)
{
   //Add the hook function to clear active DTCs here
   //return true if all the active DTCs have been cleared or no fault
   //return false if the clear action can't be performed.
   return J1939_DM11_Clr_Active_Dtcs;
}
/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     120310 lzh      Create module from Weichai program.
*
******************************************************************************/


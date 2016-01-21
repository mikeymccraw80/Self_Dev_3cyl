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
/* j1939 receive pgn variables define */
J1939_PGN_TSC1_00000_T  pgn_tsc1_00000;    //peer-to-peer mode
J1939_PGN_CM1_57344_T   pgn_cm1_57344;
J1939_PGN_CCVS_65265_T  pgn_ccvs_65265;
J1939_PGN_OHECS_64971_T pgn_ohecs_64971;

/* j1939 transmit pgn variables define */
J1939_PGN_ET1_65262_T    pgn_et1_65262;     //broadcast
J1939_PGN_EFL_P1_65263_T pgn_efl_p1_65263;  //broadcast
J1939_PGN_LFE_65266_T    pgn_lfe_65266;     //broadcast
J1939_PGN_ECC1_61444_T   pgn_ecc1_61444;    //broadcast
J1939_PGN_ECC2_61443_T   pgn_ecc2_61443;    //broadcast
J1939_PGN_MVS_64997_T    pgn_mvs_64997;     //boradcast
J1939_PGN_IT1_65154_T    pgn_IT1_65154;     //request
J1939_PGN_FD_65213_T     pgn_fd_65213;      //broadcast
J1939_PGN_VEP1_65271_T   pgn_vep1_65271;    //broadcast
J1939_PGN_IC1_65270_T    pgn_ic1_65270;     //broadcast
J1939_PGN_HOURS_65253_T  pgn_hours_65253;   //broadcast
J1939_pgn_65289_T        J1939_pgn_65289;   //TLA
J1939_73_dm13_57088_T    J1939_73_dm13;

J1939_PGN_DM1_T          pgn_dm1, pgn_dm2;
J1939_73_dm7_58112_T     J1939_73_dm7;
J1939_73_dm8_65232_T     J1939_73_dm8;
uint8_t                  DTC_Number_DM1;
uint8_t                  DTC_Number_DM2;
uint8_t                  DTC_Number_DM4;
J1939_73_DM4_T           J1939_73_dm4;
J1939_73_dm5_65230_T     J1939_73_dm5;

bool B_Ign0Req;
bool B_Ign1Req;
bool B_Ign2Req;

/* MAX_SOFTID_BUFFER_LENGTH should be specified by chery application */
uint8_t SOFTID_Buffer[]={
	'S','W','0','0','0','1',',','T','C','A','1','2','3','4','5',',','0','1','.','0','1','#',
	'A','P','0','1','0','1',',','T','C','U','3','3','4','7','0',',','0','0','.','0','7','#','*',
	'B','B','0','0','0','1',',','P','H','2','5','1','1','1',',','1','0','.','1','4','#',
	'O','S','0','0','0','1',',','P','H','2','5','0','0','6','2',',','0','5','.','0','2','#','*'
	
};

uint8_t ECUID_Buffer[]={
   'P','H','9','0','2','1','5','4','9','4','0','1','.','0','0','*',
   'S','N','0','4','0','0','2','1','9','*',
   'C','h','i','n','a','*',
   'E','n','g','i','n','e',' ','C','o','n','t','r','o','l','l','e','r','*',
   'd','e','l','p','h','i','*'};

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

uint16_t GetJ939_ECUID_Size(void)
{
    return sizeof(ECUID_Buffer);
}

uint8_t * GetJ1939_ECUID_MsgPtr(void)
{
    return ECUID_Buffer;
}

uint16_t GetJ1939_SoftID_Size(void)
{
   return sizeof(SOFTID_Buffer);
}

uint8_t * GetJ1939_SoftID_MsgPtr(void)
{
    return SOFTID_Buffer;
}


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

uint8_t GetJ1939_DM4_ActiveDTC_NUMBER (void)
{
    return DTC_Number_DM4;
}

J1939_73_DM4_T * GetJ1939_DM4_MsgPtr (void)
{
   J1939_73_dm4.Freeze_Frame[0].spn_1217 = sizeof(J1939_DM4_FreezeFrame_T)-1;  
   J1939_73_dm4.Freeze_Frame[1].spn_1217 = sizeof(J1939_DM4_FreezeFrame_T)-1;   
   J1939_73_dm4.Freeze_Frame[2].spn_1217 = sizeof(J1939_DM4_FreezeFrame_T)-1;  
   return &J1939_73_dm4;
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


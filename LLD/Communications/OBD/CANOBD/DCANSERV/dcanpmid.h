#ifndef DCANPMID_H
#define DCANPMID_H
/***********************************************************************
*  DELCO ELECTRONICS CORPORATION, INC.                                 *
*  COPYRIGHT 1999 DELCO ELECTRONICS CORPORATION, INC.                  *
*  (c) 2000 Delphi Automotive Systems, all rights reserved             *
*  ALL RIGHTS RESERVED                                                 *
*  This program may not be reproduced, in whole or in part in any form *
*  or by any means whatsoever without the written permission of:       *
*                                                                      *
*         DELCO ELECTRONICS CORPORATION                                *
*         One Corporate Center                                         *
*         Kokomo, Indiana  46904-9005                                  *
*         USA                                                          *
*                                                                      *
************************************************************************
* Filename     : dcanpmid.h                                            *
* Project Name : Reusable Common Communications 1998 PID routine       *
*                                                                      *
*                                                                      *
* Applicable   : Protocal  Class2/Keyword 2000                         *
* Documents      Common Software Reuse routine                         *
*                Services Recommended Practice  Vers. 1.1   11-14-98   *
*                                                                      *
* Description  : This module contains the support functions required   *
*                by the SAE 1979/keyword 14230 communications protocals*
*                                                                      *
*                                                                      *
************************************************************************
/*            INCLUDE FILES                                           */
/**********************************************************************/

/******************************************************************************
* APP Include Files
******************************************************************************/
//#include "obdsfexi.h"
//#include "obdlfapi.h"
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanpcfg.h"/*XeDCAN_SID_06_Supported*/
//#include "dcanlegi.h"/*CeDCAN_SCID_0E,TeDCAN_TID_List*/
//#include "intr_eobd.h"
#include "obdltype.h"
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
/*******************************
* SID $06                      *
*******************************/
#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)

typedef enum
{
   CeDCAN_MID_00 = 0x00,
   CeDCAN_MID_01 = 0x01,
   CeDCAN_MID_02 = 0x02,
   CeDCAN_MID_05 = 0x05,
   CeDCAN_MID_06 = 0x06,
   CeDCAN_MID_20 = 0x20,
   CeDCAN_MID_21 = 0x21,
   CeDCAN_MID_22 = 0x22,
   CeDCAN_MID_31 = 0x31,
   CeDCAN_MID_35 = 0x35,
   CeDCAN_MID_36 = 0x36,
   CeDCAN_MID_39 = 0x39,
   CeDCAN_MID_3B = 0x3B,
   CeDCAN_MID_3C = 0x3C,
   CeDCAN_MID_3D = 0x3D,
   CeDCAN_MID_40 = 0x40,
   CeDCAN_MID_41 = 0x41,
   CeDCAN_MID_42 = 0x42,
   CeDCAN_MID_45 = 0x45,
   CeDCAN_MID_46 = 0x46,
   CeDCAN_MID_60 = 0x60,
   CeDCAN_MID_80 = 0x80,
   CeDCAN_MID_A0 = 0xA0,
   CeDCAN_MID_A1 = 0xA1,
   CeDCAN_MID_A2 = 0xA2,
   CeDCAN_MID_A3 = 0xA3,
   CeDCAN_MID_A4 = 0xA4,
   CeDCAN_MID_A5 = 0xA5,
   CeDCAN_MID_A6 = 0xA6,
   CeDCAN_MID_A7 = 0xA7,
   CeDCAN_MID_A8 = 0xA8,
   CeDCAN_MID_A9 = 0xA9,
   CeDCAN_MID_C0 = 0xC0,
   CeDCAN_MID_E0 = 0xE0,
   CeDCAN_MID_FF = 0xFF
}TeDCAN_MID_List;

typedef enum
{
   CeDCAN_No_TID = 0x00,
/* This is the list of Stantardized Test IDs */
   CeDCAN_TID_01 = 0x01,
   CeDCAN_TID_02 = 0x02,
   CeDCAN_TID_03 = 0x03,
   CeDCAN_TID_04 = 0x04,
   CeDCAN_TID_05 = 0x05,
   CeDCAN_TID_06 = 0x06,
   CeDCAN_TID_07 = 0x07,
   CeDCAN_TID_08 = 0x08,
   CeDCAN_TID_09 = 0x09,
   CeDCAN_TID_0A = 0x0A,
   CeDCAN_TID_0B = 0x0B,
   CeDCAN_TID_0C = 0x0C,
/* This is the list of Manufacturer defined Test IDs */
   CeDCAN_TID_80 = 0x80,
   CeDCAN_TID_81 = 0x81,
   CeDCAN_TID_82 = 0x82,
   CeDCAN_TID_83 = 0x83,
   CeDCAN_TID_84 = 0x84,
   CeDCAN_TID_8F = 0x8F,
   CeDCAN_TID_91 = 0x91,
   CeDCAN_TID_A1 = 0xA1,
   CeDCAN_TID_A2 = 0xA2,
   CeDCAN_TID_B1 = 0xB1,
   CeDCAN_TID_BA = 0xBA,
   CeDCAN_TID_BB = 0xBB,
   CeDCAN_TID_BC = 0xBC,
   CeDCAN_TID_BD = 0xBD,
   CeDCAN_TID_C1 = 0xC1,
   CeDCAN_TID_C2 = 0xC2,
   CeDCAN_TID_C3 = 0xC3,
   CeDCAN_TID_C4 = 0xC4,
   CeDCAN_TID_C5 = 0xC5,
   CeDCAN_TID_C6 = 0xC6
}TeDCAN_TID_List;

typedef enum
{
   CeDCAN_NO_SCID = 0x00,
   CeDCAN_SCID_0A = 0x0A,     /* Voltage - 0.122mV per bit */
   CeDCAN_SCID_0B = 0x0B,     /* Voltage - 0.001 V per bit */
   CeDCAN_SCID_0C = 0x0C,     /* Voltage - 0.01 V per bit*/
   CeDCAN_SCID_0E = 0x0E,     /* Current - 1 ma per bit */
   CeDCAN_SCID_10 = 0x10,     /* Time - 1 ms per bit */
   CeDCAN_SCID_20 = 0x20,     /* Ratio - 0.0039062 per bit */
   CeDCAN_SCID_24 = 0x24,     /* Counts - 1 count per bit */
   CeDCAN_SCID_29 = 0x29,     /* Pressure per time - 0.25 Pa/s per bit */
   CeDCAN_SCID_2B = 0x2B,     /* Switches - hex to decimal */
   CeDCAN_SCID_9C = 0x9C,     /* Angle - 0.01 degree/bit               */
   CeDCAN_SCID_FD = 0xFD,     /* Pressure(Absolute) - 0.001 kPa per bit */
   CeDCAN_SCID_FE = 0xFE      /* Pressure(Vaccuum) - 0.25 Pa per bit */
}TeDCAN_ScalingID_List;

#endif

#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
/******************************************************************************
 *  Local Data Types
 *****************************************************************************/
typedef struct
{
  TeDCAN_TID_List            f_TID_Number;
  TeDGDM_DIAGNOSTIC_TESTS    f_DTC_ID;
  TpDCAN_MID_Param_Callback  p_Param_Function;
  TpDCAN_MID_Param_Callback  p_Param_Min_Function;
  TpDCAN_MID_Param_Callback  p_Param_Max_Function;
  TeDCAN_ScalingID_List      f_TID_ScalingID;
}TsDCAN_MID_TID_AttrType;

typedef struct
{
  TeDCAN_MID_List                f_MID_Number;
  T_COUNT_BYTE                   f_Number_Of_TIDs;
  const TsDCAN_MID_TID_AttrType  *p_MIDxx_TID_Attributes;
} TsDCAN_MID_DEFINITION_ARRAY_TYPE;

/******************************************************************************
 *  Local Defines
 *****************************************************************************/
#define CcDCAN_1979_SuppMID_BitMask  (LONGWORD)(0x80000000)

/*********************************************************************/
/*           CONSTANT DECLARATIONS                                   */
/*********************************************************************/
extern const TsDCAN_MID_DEFINITION_ARRAY_TYPE CaDCAN_Supported_MIDs[];
extern const BYTE                    CyDCAN_NumOf_MIDs;
extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_NO_TID_Attributes[];
extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_01_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_02_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_05_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_21_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_22_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_41_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_42_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_A2_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_A3_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_A4_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_A5_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_A6_TID_Attributes[];
//extern const TsDCAN_MID_TID_AttrType CaDCAN_MID_A7_TID_Attributes[];

/******************************************************************************
 *  Global Variable Declarations
 *****************************************************************************/
/*********************************************************************
* FUNCTION:     GetDCAN_MIDNumber                                    *
* DESCRIPTION:  returns MID number from table                        *
*********************************************************************/
#define GetDCAN_MIDNumber( LyDCAN_MID_Idx ) \
                   (CaDCAN_Supported_MIDs[ LyDCAN_MID_Idx ].f_MID_Number)

/*********************************************************************
* FUNCTION:     GetDCAN_Num_Of_TIDs                                  *
* DESCRIPTION:  returns TID table                                    *
*********************************************************************/
#define GetDCAN_Num_Of_TIDs( LyDCAN_MID_Idx ) \
                 (CaDCAN_Supported_MIDs[ LyDCAN_MID_Idx ].f_Number_Of_TIDs)

/*********************************************************************
* FUNCTION:     GetDCAN_TID_Num                                      *
* DESCRIPTION:  returns TID table                                    *
*********************************************************************/
#define GetDCAN_TID_Num( LyDCAN_MID_Idx, LyDCAN_TID_Idx ) \
          (CaDCAN_Supported_MIDs[ LyDCAN_MID_Idx ].p_MIDxx_TID_Attributes[LyDCAN_TID_Idx].f_TID_Number)

/*********************************************************************
* FUNCTION:     GetDCAN_DTC_ID                                       *
* DESCRIPTION:  returns DTC ID                                       *
*********************************************************************/
#define GetDCAN_DTC_ID( LyDCAN_MID_Idx, LyDCAN_TID_Idx ) \
          (CaDCAN_Supported_MIDs[ LyDCAN_MID_Idx ].p_MIDxx_TID_Attributes[LyDCAN_TID_Idx].f_DTC_ID)

/*********************************************************************
* FUNCTION:     GetDCAN_TID_ScalingID                                *
* DESCRIPTION:  returns scaling ID of the TID                        *
*********************************************************************/
#define GetDCAN_TID_ScalingID( LyDCAN_MID_Idx,LyDCAN_TID_Idx ) \
          (CaDCAN_Supported_MIDs[ LyDCAN_MID_Idx ].p_MIDxx_TID_Attributes[LyDCAN_TID_Idx].f_TID_ScalingID)

/*********************************************************************
* FUNCTION:     GetDCAN_Param_Value                                  *
* DESCRIPTION:  returns the Test Value parameter name                *
*********************************************************************/
#define GetDCAN_Param_Value( LyDCAN_MID_Idx,LyDCAN_TID_Idx,LgDCAN_Parm_Addr ) \
          (CaDCAN_Supported_MIDs[ LyDCAN_MID_Idx ].p_MIDxx_TID_Attributes[LyDCAN_TID_Idx]. \
                       p_Param_Function(LgDCAN_Parm_Addr))

/*********************************************************************
* FUNCTION:     GetDCAN_Param_Min_Value                              *
* DESCRIPTION:  returns Minimum Threshold                            *
*********************************************************************/
#define GetDCAN_Param_Min_Value( LyDCAN_MID_Idx,LyDCAN_TID_Idx,LgDCAN_Parm_Addr ) \
          (CaDCAN_Supported_MIDs[ LyDCAN_MID_Idx ].p_MIDxx_TID_Attributes[LyDCAN_TID_Idx]. \
                       p_Param_Min_Function(LgDCAN_Parm_Addr))

/*********************************************************************
* FUNCTION:     GetDCAN_Param_Max_Value                              *
* DESCRIPTION:  returns Maximum Threshold                            *
*********************************************************************/
#define GetDCAN_Param_Max_Value( LyDCAN_MID_Idx,LyDCAN_TID_Idx,LgDCAN_Parm_Addr ) \
          (CaDCAN_Supported_MIDs[ LyDCAN_MID_Idx ].p_MIDxx_TID_Attributes[LyDCAN_TID_Idx]. \
                       p_Param_Max_Function(LgDCAN_Parm_Addr))

/*********************************************************************
* FUNCTION:     GetMIDNumber                                         *
* DESCRIPTION:  returns number of supported MIDs                     *
*********************************************************************/
#define GetDCAN_NumberOfMIDs()                  (CyDCAN_NumOf_MIDs)

#else
extern void DefineOSTK_EmptyFunction(void);

#define GetDCAN_MIDNumber( LyDCAN_MID_Idx )       (V_COUNT_BYTE(0))
#define PfrmDCAN_ExecuteMIDFunction            DefineOSTK_EmptyFunction
#define GetDCAN_NumberOfMIDs()                    (V_COUNT_BYTE(0))
#endif /* (XeDCAN_SID_06_Supported == CeDCAN_Supported) */

#endif
/***********************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.   Date  User RSM#  Description of Changes                       *
* ----  ------ ---- ----  ---------------------------------------------*
* 1     050526 ban  5311  Created Module                               *
* 2     051209 ban  5311  Removed MID A1                               *
* tci_pt3#2 
*      070503  AB  xxxx Removed MID 3C TID 82                          *
*                       Added TID 80 in MID 3D .                       *
* tci_pt3#2
*      080404  VP  6833 Added TID 90 in MID 31.
*
* 3.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 paltform.
***********************************************************************/

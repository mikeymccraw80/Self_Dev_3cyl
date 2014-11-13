#ifndef OBDLTYPE_H
#define OBDLTYPE_H
/***********************************************************************
*  DELCO ELECTRONICS CORPORATION, INC.                                 *
*  COPYRIGHT 1999 DELCO ELECTRONICS CORPORATION, INC.                  *
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
* Filename     : obdltype.h                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents                                                            *
* Version      : 1.1                                                   *
* Date         : June 1998.                                            *
*                                                                      *
* Purpose      : Keyword 2000 file to export type defs used by KW2K    *
*                                                                      *
* Description  : This modules contains all the functions and the       *
*               Variables which need to be exported out to other       *
*               functions.                                             *
*                                                                      *
* $Source: ems_project@brighton.tcb:daewoo_2002:obd_type.h $
* $Revision: 1.1 $
* $Author: brighton.tcb:/users/safayyad...daewoo_2002_MathLib:safayyad $
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   09-11-98  cwe     Initial file creation                        *
* 1.2   10-15-98  cdw     New version created from Daewoo delivery     *
* 1.3   12-03-98 JZha     Made it to be standard.                      *
************************************************************************/
 
/*********************************************************************/
/*            INCLUDE FILES                                          */
/*********************************************************************/
#include "obdsbase.h"

/*********************************************************************/
/*            EQUATES                                                */
/*********************************************************************/
#define UDWORD unsigned long

/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/


typedef enum
{
   CeDCAN_MsgLength_Three = 3,
   CeDCAN_MsgLength_Four  = 4,
   CeDCAN_MsgLength_Five  = 5
}TeDCAN_Srv30_MsgLength;



typedef union
{
  BYTE ubyte;
  WORD uword;
} BYTEANDWORD1;



typedef struct
{
  BYTE                     f_LID_Index;
  TbBOOLEAN                b_LID_Valid;
} TsDCAN_LID_Status;


/* Scaling Indentification Type */
typedef enum
{
   CeDCAN_SC_NONE,  /* No Scaling */
   CeDCAN_USB_USB,  /* Unsigned Byte - Unsigned Byte */
   CeDCAN_USB_USW,  /* Unsigned Byte - Unsigned Word */
   CeDCAN_USW_USB,  /* Unsigned Word - Unsigned Byte */
   CeDCAN_USW_USW,  /* Unsigned Word - Unsigned Word */
   CeDCAN_SSB_SSB,  /* Signed Byte   - Signed Byte   */
   CeDCAN_SSB_SSW,  /* Signed Byte   - Signed Word   */
   CeDCAN_SSW_SSB,  /* Signed Word   - Signed Byte   */
   CeDCAN_SSW_SSW,  /* Signed Word   - Signed Word   */
   CeDCAN_SSB_USB,  /* Signed Byte   - Unsigned Byte */
   CeDCAN_SSB_USW,  /* Signed Byte   - Unsigned Word */
   CeDCAN_SSW_USB,  /* Signed Word   - Unsigned Byte */
   CeDCAN_SSW_USW   /* Signed Word   - Unsigned Word */
} TeDCAN_ScalingType;

/*********************************************************************/
/* GLOBAL DATA TYPE DECLARATIONS                                     */
/*********************************************************************/

/*********************************************************************/
/* GLOBAL DATA TYPE DECLARATIONS                                     */
/*********************************************************************/

typedef struct
{
  BYTE  Byte_Two;
  BYTE  Byte_One;
} WORD_TO_BYTE_ACCESS_TYPE;

typedef struct
{
  BYTE  Byte_Four;
  BYTE  Byte_Three;
  BYTE  Byte_Two;
  BYTE  Byte_One;
} LWORD_TO_BYTE_ACCESS_TYPE;

typedef struct
{
  WORD  Word_Two;
  WORD  Word_One;
} LWORD_TO_WORD_ACCESS_TYPE;


typedef union
{
  LWORD_TO_BYTE_ACCESS_TYPE    Byte_Access;
  LWORD_TO_WORD_ACCESS_TYPE    Word_Access;
  UDWORD                       DWord_Access;
} FOUR_BYTE_DATA_TYPE;


typedef union
{
  WORD_TO_BYTE_ACCESS_TYPE   Byte_Access;
  WORD                      Word_Access;
} TWO_BYTE_DATA_TYPE;

typedef
  struct
    {
    bitfield16_t PreviousCommState:                 1;
    bitfield16_t SecurityAccessUnlocked:            1;
    bitfield16_t ECUResetPending:                   1;
    bitfield16_t WaitingForWriteDataByIdToComplete: 1;
    bitfield16_t WriteLongPIDData:                  1;
    bitfield16_t UnusedBit2:                        1;
    bitfield16_t TransferDataRequested:             1; 
    bitfield16_t DownLoadRequested:                 1;
    
    bitfield16_t DownLoadGranted:                   1;
    bitfield16_t ReprogramWdgCalPending:            1;
    bitfield16_t SendingOneShotDpidResponse:        1;
    bitfield16_t ReadMemoryByAddressActive:         1;
    bitfield16_t ReadSupportedDTCActive:            1;
    bitfield16_t DeviceControlActive:               1;
    bitfield16_t SmallGmLan:                        1;
    }
  LnDiagSvFlagsType;

/* DTC information returned to the service functions.  */
typedef struct
{
  TWO_BYTE_DATA_TYPE       DTC_Number;
  BYTE                     DTC_FailureType;
  BYTE                     DTC_Status;
  TbBOOLEAN                DTC_Valid;
  TbBOOLEAN                Addl_DTC_Found;
} DTC_STATUS_INFO_TYPE;

typedef enum {
  MODE_3,
  MODE_7
} MODES_TYPE;
/*****************************************************************************
 *  Local Types
 *****************************************************************************/
typedef enum
{
   CeDCAN_RealTimeData,
   CeDCAN_FreezeFrameData
}TeDCAN_PID_DataType;

typedef enum
{
  CeDCANOBD_default
#ifdef OBD_CONTROLLER_IS_MT92
  ,CeDCANOBD_CHK011_MT92
  ,CeDCANOBD_JAC_MT92
  ,CeDCANOBD_CHB031_MT92
#endif
#ifdef OBD_CONTROLLER_IS_MT62P1
  ,CeDCANOBD_DX5_MT62p1
  ,CeDCANOBD_DM7A_MT62p1
#endif
#ifdef OBD_CONTROLLER_IS_MT22P3
  ,CeDCANOBD_CMCAS_MT22p3
#endif
} TeDCANOBD_Applictaion_Type;

/* PID's table function pointer definition */
typedef void (*TpDCAN_MID_Param_Callback)(void*);
typedef void (*TpDCAN_PID_Param_Callback)(void*, TeDCAN_PID_DataType);
typedef void (*TpDCAN_Addl_Call_RetVoid)(void);
#endif



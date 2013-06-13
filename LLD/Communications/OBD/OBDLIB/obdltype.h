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

/*****************************************************************************
 *  Local Types
 *****************************************************************************/
typedef enum
{
   CeDCAN_RealTimeData,
   CeDCAN_FreezeFrameData
}TeDCAN_PID_DataType;

/* PID's table function pointer definition */
typedef void (*TpDCAN_MID_Param_Callback)(void*);
typedef void (*TpDCAN_PID_Param_Callback)(void*, TeDCAN_PID_DataType);
typedef void (*TpDCAN_Addl_Call_RetVoid)(void);
#endif



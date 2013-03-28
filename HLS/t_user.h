#ifndef t_user_h
#define t_user_h
/******************************************************************************
 *
 * Filename:          t_user.h
 *
 * Description:       This file contains global definitions associated
 *                    with this project.  All information is considered
 *                    public.
 *
 * Global Functions Defined:
 *                    None
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
 * %full_name:     tcb_pt1#4/incl/t_user.h/3 %
 * %date_created:  Tue Jun 10 14:57:08 2008 %
 * %version:       3 %
 * %derived_by:    pzb6v4 %
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * The following binary discrete data types that are usable in expressions
 * without a compare operation {if (a)}.  Any data that is not defined in this
 * section shall only be used with a comparision {if (a==b) }.
 *
 * NOTE: It is important that the NEGATIVE or FAILED or FALSE equivalent value
 *       is defined first.  The C enum data type defines the first element to
 *       be equal to 0 (zero).  This allows the "FALSE" condition of the
 *       conditional statement {if (a)} to be eqivalent to {if (a=="FALSE")}
 *
 * ALSO, Even though the binary discrete data types are defined with the enum
 *       mechanism, they are still binary values.  Thus, the type and constant
 *       are "Tb" and "Cb".  In other words, the second character represents
 *       the data type and NOT the mechanism for defining that type.
 *
 *****************************************************************************/

typedef enum
  {
  CbFALSE,
  CbTRUE
  }TbBOOLEAN;

/****************************************************************************
The following enumeration definition is a mirror image of enumeration type
TbBOOLEAN. It may be used by redundant software paths to promote diversity.
****************************************************************************/
typedef enum
  {
  CbREDN_TRUE,
  CbREDN_FALSE
  } TbREDN_BOOLEAN;

typedef enum
  {
  CbNO,
  CbYES
  }TbYES;

typedef enum
  {
  CbFAIL,
  CbPASS
  }TbPASS;

typedef enum
  {
  CbINVALID,
  CbVALID
  }TbVALID;

/************************************************************/
/* Warning, the following types must be mirror images       */
/* TbREDN_ON is used for redundant software diversification */
/************************************************************/

typedef enum
  {
  CbOFF,
  CbON
  } TbON;

typedef enum
  {
  CbREDN_ON,
  CbREDN_OFF
  } TbREDN_ON;

/***********************************************************/

typedef enum
  {
  CbDISABLED,
  CbENABLED
  }TbENBL;

typedef enum
  {
  CbDISENGAGED,
  CbENGAGED
  }TbENGAGE;

typedef enum
  {
  CbINACTIVE,
  CbACTIVE
  }TbACTIVE;

typedef enum
  {
  CbLOW,
  CbHIGH
  }TbHIGH;

typedef enum
  {
  CbUNLOCK,
  CbLOCK
  }TbLOCK;

typedef enum
  {
  CbRELEASE,
  CbAPPLY
  }TbAPPLY;

typedef enum
    {
    CbCLOSED,
    CbOPENED
    }TbOPENED;

typedef enum
{
  CbNOT_LEARNED,
    CbLEARNED
} TbLEARNED;

typedef enum
{
  CbOUT_OF_RANGE,
  CbIN_RANGE
}  TbIN_RANGE;

#define CbSUBS_OFF  0
#define CbSUBS_ON   1

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
* -- Core Revision History: --
*
* 1.4   990204 arr 0149 Merged in LECC node 375 containing the following
*                       change(s):
*       971104 blt 0249 API cleanup
*       981009 blt 0679 Added TbREDN_BOOLEAN for Dual-Path
* 1.5   990805 ajk 0302 Merged in Proto2 node 050 (cp2050f0) containing the
*                        following change(s):
*       990512 blt 0941 Added TbREDN_ON for dual-path
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
*
* -- Core Revision History: --
*
* 2     070628 gps 6290 CDAS 4.0 using HD08 15.1 activity.
* 2.1   080404 mcb 6924 Added CbSUBS_OFF, CbSUBS_ON
* 3     080512 gps 6290 Merged 't_user.h~2' with 't_user.h~2.1'.
*
******************************************************************************/

/*****************************************************************************
 *
 * (c) 1997 General Motors Corporation, all rights reserved
 *
 *   $Archive: /midrange/MR140/Proto1/src/t_user.h $
 *  $Workfile:   t_user.h  $
 *  $Revision: 1.1 $
 *   $Modtime: 12/09/98 11:41a $
 *    $Author: brighton.tcb:/users/mrwoznic/dsds/core_dc2:mrwoznic $
 *
 *
 * Description:         This file contains global definitions associated
 *                      with this project.  All information is considered
 *                      public.
 *
 *                      The following non-instrumented data types are
 *                      declared within this file:
 *
 *
 * Revision History:
 *
 * $Log: /midrange/MR140/Proto1/src/t_user.h $
 *
 * 5     12/09/98 2:06p Gzdmlz
 * New Files from level 24 integration
 *
 * 7     12/09/98 11:00a Gzdmlz
 * New Files from level 26 integration
 * Revision 1.2  1995/02/10  13:03:44  rcalla01
 * Author id: rcalla01     lines deleted/added/moved: 9/7/0
 * removed TbMode since TbOn covered any need for this type
 *
 *
 *    Rev 1.2   Fri Feb 10 13:03:44 1995   rcalla01
 * removed TbMode since TbOn covered any need for this type
 *
 *    Rev 1.1   Wed Feb 01 13:25:04 1995   tslawi01
 * Added TbOPENED
 *
 *****************************************************************************/
#ifndef t_user_h
#define t_user_h

/*****************************************************************************
 *  Global Data Type Include Files (Genesys-2000 Output)
 *****************************************************************************/


/*****************************************************************************
 *
 * Module:              t_user
 * Version:             Alpha
 * Last Modify Date:    10-Oct-94
 * Last Author:         William E. Debs
 *
 * Description:         Global Data Types defined using Genesys-2000
 *
 *
 * Change History:
 *  10-Oct-94 W.Debs      Created by hand
 *  17-Nov-94 T.Giardini  Added Engaged | Disengaged
 *  15-Dec-94 T.Giardini  Added Valid | Invalid
 *  15-Dec-94 T.Giardini  Added NOTE to explain definition syntax
 *  03-Jan-95 T.Giardini  Added Active | Inactive
 *  16-Jan-95 P.Raja      Added High | Low
 *  21-Jan-95 T.Giardini  Global Naming Change
 *  23-Jan-95 P.Raja      Added TbAPPLY, TbLOCK, TbMODE
 *  01-Feb-95 T.Slawinski Added TbOPENED
 *  10-Feb-95 R.Callaghan Deleted TbMODE (nonstandard)
 *
 * (c) 1997 General Motors Corporation, all rights reserved
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
  FALSE,
  TRUE
  }BOOLEAN;

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
* 1.2   070105 Shoujun xxx defined BOOLEAN
*
******************************************************************************/
/*
* $Source: common@brighton.tcb:core_dc2:t_user.h $
* $Revision: 1.1 $
* $Author: brighton.tcb:/users/mrwoznic/dsds/core_dc2:mrwoznic $
*/



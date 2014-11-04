/******************************************************************************
 *
 * Filename:          dcanmmng.c
 *
 * Description:       This module contains all of the initialization
 *                    routines needed for OS
 *
 * Global Functions Defined:
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2000-2009, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     ctc_pt3#2/csrc/dcanmmng.c/2 %
 * %date_created:  Fri Apr  1 14:52:00 2011 %
 * %version:       2 %
 * %derived_by:    hzpcqq %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
#include "systpcfg.h"
#include "obdsfapp.h"/*ImmoGoToNormalKeyword()*/
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanserv.h" /*UpdateLnDiagServices ()*/
                                /*UpdateDCAN_Services()*/
                                /*InitializeLnDiagServices()*/
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#include "dcancomm.h"/*UpdateLnDiagSvCommunication()*/

/******************************************************************************
 *  Global Variables
 *****************************************************************************/

/******************************************************************************
 * Static Variables
 *****************************************************************************/
 /*****************************************************************************
 *  Local Function declarations
 *****************************************************************************/

/***********************************************************************
* FUNCTION:      MngCANOBD_TasksExecutive                               *
*                                                                      *
* TYPE:          Global                                                *
*                                                                      *
* Description: This function will executive CANOBD service         *
***********************************************************************/
void MngCANOBD_TasksExecutive( void )
{
   UpdateLnTransportLayer ();
   UpdateLnDiagSvCommunication ();
   UpdateLnDiagServices ();
}
/***********************************************************************
* FUNCTION:      MngDCAN_TasksExecutive                                *
*                                                                      *
* TYPE:          Global                                                *
*                                                                      *
* Description: This function will be called at each 7.8125 ms  by the  *
*              operation system to check the recieved Msg.             *
***********************************************************************/
FARFUNC void MngDCAN_TasksExecutive( void )
{
      /*- Normal Keyword Mode. Server Mode-*/
      MngCANOBD_TasksExecutive();
}

/***********************************************************************
* FUNCTION:      MngDCAN_RstToKeyOnTasks                               *
*                                                                      *
* TYPE:          Global                                                *
*                                                                      *
* Description: This function will be called at reset to key on         *
***********************************************************************/
FARFUNC void InitDCAN_RstToKeyOnTasks( void )
{
   InitializeDCAN_Services() ;
   InitializeLnDiagServices ();
}


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* base of T300
*1.0  20090808 cjqq Added Legisted CANOBD
*
******************************************************************************/

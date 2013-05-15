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
 * %full_name:     mt20u2#2/csrc/dcanmmng.c/1 %
 * %date_created:  Tue Sep  7 14:55:37 2010 %
 * %version:       1 %
 * %derived_by:    pz0vmh %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
//#include "systpcfg.h"
#if(XeSYST_CANOBD_SrvsEnable == CeSYST_AVAILABLE)
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
//#include "dcantran.h"/*UpdateLnTransportLayer()*/
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
FAR_COS void MngDCAN_TasksExecutive( void )
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
FAR_COS void InitDCAN_RstToKeyOnTasks( void )
{
   InitializeDCAN_Services() ;
   InitializeLnDiagServices ();
}

#else
/***********************************************************************
* FUNCTION:      MngDCAN_TasksExecutive                                *
*                                                                      *
* TYPE:          Global                                                *
*                                                                      *
* Description: This function will be called at each 7.8125 ms  by the  *
*              operation system to check the recieved Msg.             *
***********************************************************************/
//FAR_COS void MngDCAN_TasksExecutive( void )
//{

//}

/***********************************************************************
* FUNCTION:      MngDCAN_RstToKeyOnTasks                               *
*                                                                      *
* TYPE:          Global                                                *
*                                                                      *
* Description: This function will be called at reset to key on         *
***********************************************************************/
//FAR_COS void InitDCAN_RstToKeyOnTasks( void )
//{

//}
#endif
/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* base of T300
*1.  20090808 cjqq Added Legisted CANOBD
*
* 2.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 paltform.
******************************************************************************/

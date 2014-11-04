#ifndef DCANSV2F_H
#define DCANSV2F_H
/*-------------------------------------------------------------------*/
/* filename -  dcansv2f.h                                            */
/*                                                                   */
/*    This module is application layer of the Delco Electronics      */
/*    engine control s/w, where the GMLAN diagnostics services       */
/*    are processed.                                                 */
/*                                                                   */
/*    LN stands for Local Network of GMLAN                           */
/*                                                                   */
/* Usage:                                                            */
/*                                                                   */
/*   InitializeGmlanServices is called in the initialisation to set  */
/*    up all variables related to this module.                       */
/*                                                                   */
/* list of function(s):                                              */
/*                                                                   */
/*  Proto:  LnInputOutputControlByIdentifier                                         */
/*                                                                   */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* DELPHI Delco Luxembourg C Engine Management Software              */
/* (c) Copyright DELPHI Delco Europe 2000                            */
/* Origin: 19-Sep-2000 from scratch                                  */
/* Written by: Frederique d'Ennetieres                               */
/*-------------------------------------------------------------------*/

 /****************************************************************************
 *
 * Current Module Info:
 * %full_name:      lux_pt1#1/incl/dcansv2f.h/1 %
 * %date_created:   Wed Feb 15 18:20:47 2006 %
 * %version:        1 %
 * %derived_by:     c23cr %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/

/*********************************************************************/
/*          GLOBAL FUNCTION PROTOTYPES                               */
/*********************************************************************/
extern void DefineOSTK_EmptyFunction(void);
/**********************************************************************/
/*** LnDiag service: Device Control                                 ***/
/**********************************************************************/
#if (XeDCAN_SID_2F_Supported == CeDCAN_Supported)
void LnInputOutputControlByIdentifier(void);
void PostOFVC_LnResponseToRequest (void);
#else /* SID_2F not Supported */

#define LnInputOutputControlByIdentifier    ServiceNotSupported_DCAN
#define PostOFVC_LnResponseToRequest        DefineOSTK_EmptyFunction

#endif /* (XeDCAN_SID_2F_Supported == CeDCAN_Supported) */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     060215 cr       Created from TCL version (archive cvs partition op36cm)
*                  
*
******************************************************************************/

#endif

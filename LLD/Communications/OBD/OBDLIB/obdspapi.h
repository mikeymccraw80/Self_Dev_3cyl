#ifndef OBDSPAPI_H
#define OBDSPAPI_H
/******************************************************************************
 * 
 * Filename:          obdspapi.h
 * 
 * Description:       This modules contains the all user interface constants and inline functions.
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 * 
 * Forward Engine Management Systems
 * 
 * Copyright 2007-2008, Delphi Technologies, Inc.
 * All rights reserved.
 * 
 *****************************************************************************
 * 
 * Current Module Info:
 * %full_name:      mt20u2#1/incl/obdspapi.h/1 %
 * %date_created:   Fri Sep 10 14:34:23 2010 %
 * %version:        1 %
 * %derived_by:     pz0vmh %
 * 
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* System Include Files
******************************************************************************/
/*********************************************************************/
/* DESCRIPTION   Get the DTC related data structures.             */
/*********************************************************************/

/*********************************************************************/
/* DESCRIPTION   Clears the DTC related data structures.             */
/*********************************************************************/

/*****************************************************************************
 *  Global Function Prototypes
 *****************************************************************************/
extern void   SendStandardNegativeAnswer( BYTE in_code );
extern void   SendStandardPositiveAnswer( BYTE in_msg_size );
extern void OBD_ByKW2000( void );
extern void MngDCAN_TasksExecutive( void );
extern void InitDCAN_RstToKeyOnTasks( void );

#endif /* OBDSPAPI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 

******************************************************************************/

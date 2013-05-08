#ifndef ESTDPAPI_H
#define ESTDPAPI_H
/*****************************************************************************
* Filename:             estdpapi.h
*                                                                           
* Description:		This is the public header file for EST Fault 
*                       Diagnostics
*
* List of Function 
*         Prototypes:   InitINJD_RstToKeyOn()
*                       InitINJD_OFVC_Clear()
*                       MngINJD_RefEventTasks()
*
* List of Inlines:      None
*
* C Software Project Forward EMS
* (c) Copyright Delco Electronics  1997
******************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files 
 *****************************************************************************/
#include "t_gentypes.h" /* For Gloabl Data Type */

/******************************************************************************
 *  Diagnostic Execution Routine Definitions
 *****************************************************************************/

FAR_COS void MngESTD_RefEventTasks(void);
FAR_COS void InitESTD_ShutdownInProgToKeyOn (void);
FAR_COS void MngESTD_7p81msTasks (void);
//FAR_COS void InitESTD_RstToKeyOff (void);

#endif /* End of ESTDPAPI_H */

/*****************************************************************************
*
******************************************************************************/

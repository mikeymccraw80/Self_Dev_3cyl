#ifndef KW2SRV10M_H
#define KW2SRV10M_H
/* ============================================================================ *\
 * kw2srv10m.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv10m.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, March 20, 2003 11:22:02 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $10 -  start diagnostic session (Minimized)
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "reuse.h"

/* Enumeration of the Keyword 2000 State Type                      */

typedef enum
{
   StandardDiagnosticModeState,
   ECUProgrammingSessionState
}  Kw2000DiagStateType;

typedef enum
{
 CeBaudRate9p6KB         = 1,
 CeBaudRate19p2KB        = 2,
 CeBaudRate38p4KB        = 3,
 CeBaudRate57p6KB        = 4,
 CeBaudRate115p2KB       = 5
} BaudRate_type;

/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/

/* Modes */
#define CyStandardDiagnosticMode           (0x81)
#define CyECUProgrammingMode               (0x85)

/* The number of Received data bytes */
#define CyStartDiagMsgLength_WithoutBaud   (2)
#define CyStartDiagMsgLength_WithBaud      (3)

/* Received data positions */
#define CyDiagnosticMode                   (1)
#define CyBaudRateSelect                   (2)

/* The number of Answer data bytes */
#define CyPositiveAnswer_WithoutBaud       (2)
#define CyPositiveAnswer_WithBaud          (3)

/* Kwyword 2000 baud rate */
#define CyKw2000BaudRate10p4     (10400)
#define CyKw2000BaudRate9p6      (9600)
#define CyKw2000BaudRate19p2     (19200)
#define CyKw2000BaudRate38p4     (38400)
#define CyKw2000BaudRate57p6     (57600)
#define CyKw2000BaudRate115p2    (115200)

/*********************************************************************/
/*                  GLOBAL VARIABLES DECLARATIONS                    */
/*********************************************************************/
extern Kw2000DiagStateType  Kw2000DiagSt;
extern uint8_t              Kw2DiagMode ;
extern uint8_t              Kw2BaudRate ;
extern bool                 BaudRateChangeRequest ;

/*********************************************************************/
/*                  EXTERN FUNCTION DECLARATIONS                     */
/*********************************************************************/
extern void KwJ14230MiniStartDiagSession( void );
extern void ProcessRequest ( void );

/*********************************************************************/
/*  This function returns baud rate value. The input arguement is an */
/*  enumeration depicting the baud rate. This funtion is defined in  */
/*  api file, as the buad rate ranges are application specific.      */
/*  The Keyword 2000 software supports the six baud rates implemented*/
/*  in the function.  This function needs to be modefied if the      */
/*  application does not support all the baud rates.  Remove the     */
/*  'case' statement processing for the unsupported baud rates.      */
/*********************************************************************/
uint32_t GetSrv10BaudRate ( BaudRate_type BaudRate );

/*********************************************************************/
/*                  INLINE FUNCTION DECLARATIONS                     */
/*********************************************************************/
/*********************************************************************/
/*** Check the current mode of Programming state                     ***/
/*********************************************************************/
#define CheckProgrammingState()             (Kw2000DiagSt == ECUProgrammingSessionState)

/*********************************************************************/
/*** Check the current mode of StandardDiagnosticModeState           ***/
/*********************************************************************/
#define CheckStandardDiagnosticState()      (Kw2000DiagSt == StandardDiagnosticModeState)

/*********************************************************************/
/*** Set the current mode to be ECUProgrammingSessionState         ***/
/*********************************************************************/
#define SetECUProgrammingSessionState()     (Kw2000DiagSt = ECUProgrammingSessionState)

/*********************************************************************/
/*** Set the current mode to be StandardDiagnosticModeState        ***/
/*********************************************************************/
#define SetStandardDiagnosticState()        (Kw2000DiagSt = StandardDiagnosticModeState)


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 03/03/03     sgchia      106
 * + Boot Loader.
 *
\* ============================================================================ */
#endif

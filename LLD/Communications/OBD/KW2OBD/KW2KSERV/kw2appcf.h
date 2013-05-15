#ifndef KW2APPCF
#define KW2APPCF
/* ============================================================================ *\
 * kw2appcf.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2appcf.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:09:44 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 application layer configuration.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#include "kw2dll.h"

/***********************Global DEFINITIONS:****************************/

/*--- "APPLICATION LAYER" Service Id Requests                Implemented? ---*/
#define sirSAEJ1979DiagTestMode00                      (0x00) /* NO */
#define sirSAEJ1979DiagTestMode01                      (0x01) /* NO  */
#define sirSAEJ1979DiagTestMode02                      (0x02) /* NO  */
#define sirSAEJ1979DiagTestMode03                      (0x03) /* NO  */
#define sirSAEJ1979DiagTestMode04                      (0x04) /* NO  */
#define sirSAEJ1979DiagTestMode05                      (0x05) /* NO  */
#define sirSAEJ1979DiagTestMode06                      (0x06) /* NO  */
#define sirSAEJ1979DiagTestMode07                      (0x07) /* NO  */
#define sirSAEJ1979DiagTestMode08                      (0x08) /* NO  */
#define sirSAEJ1979DiagTestMode09                      (0x09) /* NO  */
#define sirSAEJ1979DiagTestMode10                      (0x0A) /* NO  */
#define sirSAEJ1979DiagTestMode11                      (0x0B) /* NO  */
#define sirSAEJ1979DiagTestMode12                      (0x0C) /* NO  */
#define sirSAEJ1979DiagTestMode13                      (0x0D) /* NO  */
#define sirSAEJ1979DiagTestMode14                      (0x0E) /* NO  */
#define sirSAEJ1979DiagTestMode15                      (0x0F) /* NO  */
#define sirStartDiagnosticSession                      (0x10) /* YES */
#define sirEcuReset                                    (0x11) /* YES */
#define sirReadFreezeFrameData                         (0x12) /* NO  */
#define sirReadDiagnosticTroubleCodes                  (0x13) /* NO */
#define sirClearDiagnosticInformation                  (0x14) /* YES */
#define sirSetRamOverlay                               (0x15) /* NO  */
#define sirGetRamOverlay                               (0x16) /* NO  */
#define sirReadStatusOfDiagnosticTroubleCodes          (0x17) /* NO  */
#define sirReadDiagnosticTroubleCodesByStatus          (0x18) /* YES */
#define sirReadStatusOfDiagTroubleCodesByStatus        (0x19) /* NO  */
#define sirReadEcuIdentification                       (0x1A) /* YES */
#define sirStopDiagnosticSession                       (0x20) /* YES */
#define sirReadDataByLocalIdentifier                   (0x21) /* YES  */
#define sirReadDataByCommonIdentifier                  (0x22) /* NO  */
#define sirReadMemoryByAddress                         (0x23) /* YES */
#define sirSetDataRates                                (0x26) /* NO  */
#define sirSecurityAccess                              (0x27) /* YES */
#define sirDynamicallyDefineLocalIdentifier            (0x2C) /* YES */
#define sirWriteDataByCommonIdentifier                 (0x2E) /* NO  */
#define sirInputOutputControlByCommonIdentifier        (0x2F) /* NO  */
#define sirInputOutputControlByLocalIdentifier         (0x30) /* YES */
#define sirStartRoutineByLocalIdentifier               (0x31) /* YES */
#define sirStopRoutineByLocalIdentifier                (0x32) /* NO  */
#define sirRequestRoutineResultsByLocalIdentifier      (0x33) /* NO  */
#define sirRequestDownload                             (0x34) /* YES */
#define sirRequestUpload                               (0x35) /* NO  */
#define sirTransferData                                (0x36) /* YES */
#define sirRequestTransferExit                         (0x37) /* YES */
#define sirStartRoutineByAddress                       (0x38) /* YES */
#define sirStopRoutineByAddress                        (0x39) /* N0  */
#define sirRequestRoutineResultsByAddress              (0x3A) /* N0  */
#define sirWriteDataByLocalIdentifier                  (0x3B) /* YES */
#define sirResetFactoryTest                            (0x3B) /* YES */
#define sirWriteMemoryByAddress                        (0x3D) /* YES */
#define sirTesterPresent                               (0x3E) /* YES */


extern void InitAppLvlCommVariables_KW ( void );
extern void InitAppLvlCommVariablesGlobal( void );
extern void UpdateKeyword2000ServiceTasks(void);

/* ============================================================================ *\
 * FUNCTION: ServiceNotSupported
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * If the receive message ID does not match send this negative response.
 *
\* ============================================================================ */
void ServiceNotSupported(void);

/* ============================================================================ *\
 * FUNCTION: KwNoMultiModeAval
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This will only execute if the wrong enum is set.
 *
\* ============================================================================ */
void KwNoMultiModeAval(void);
/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 06/08/08     FX      -
 * + Baseline - Created from MT22U.
 *
\* ============================================================================ */
#endif

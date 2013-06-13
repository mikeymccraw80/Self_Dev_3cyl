#ifndef KW2API_H
#define KW2API_H
/* ============================================================================ *\
 * kw2api.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2api.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:09:23 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 API layer.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */


/*********************************************************************/
/*            INCLUDE FILES                                          */
/*********************************************************************/
#include "kw2type.h"
#include "kw2dll.h"
//#include "kw2cfg.h"
#include "intr_ems.h"

/*  application specific functions */

/* Define boundrys for start and end of ram */
#define CyRAM_SectionStart    0x7000
#define CyRAM_SectionEnd      0x7f00

#define      CyRAM_DCAN_SectionStart    (0x0f9000)
#define      CyRAM_DCAN_SectionEnd      (0x0FFFFF)

#define DOWNLOADRAM_START     (uint8_t *) CyRAM_SectionStart
#define DOWNLOADRAM_END       (uint8_t *) CyRAM_SectionEnd

#define CpHWIO_ROM_CalibrationStart (uint8_t *) 0x4000
#define CpHWIO_ROM_CalibrationEnd   (uint8_t *) 0x63ff


/********************************************************************
 * J1979 Mode 9 info 6, CRC16 checksum calculation configure step.  *
 * This parameter depicts the memory size to calculate the checksum *
 * in each execution of the checksum process.  The checksum process *
 * is time-slice implented.  It allows the checksum process to      *
 * execute partially in one invocation and complete the job in      *
 * multiple invocations.  Time-Slicing enables longer running       *
 * processes not to overflow the throughput.                        *
 *******************************************************************/

#define KW_CRC_Step_Lenth        (100)

extern const uint8_t       ECUResetStatusTable [];
extern const uint8_t       ECUResetStatusSize;

/*********************************************************************/
/*  These functions are not application-dependent. Do not modify     */
/*  these functions.                                                 */
/*********************************************************************/

/*********************************************************************/
/*   Returns Read ECU Reset Status  table                            */
/*********************************************************************/
#define GetECUResetStatusTable(LyIndex)         ((uint8_t) ECUResetStatusTable[ LyIndex ])

/*********************************************************************/
/*    Returns ECU Reset Status Table Size                            */
/*********************************************************************/
#define GetECUResetStatusTableSize()            ((uint8_t) ECUResetStatusSize)

/*********************************************************************/
/*          Returns the RAM start address for keyword 2000           */
/*                 upload and download services.                     */
/*********************************************************************/
#define GetRAMStartAddrForUpDownload()          ((uint8_t*) DOWNLOADRAM_START)

/*********************************************************************/
/*          Returns the RAM end address for keyword 2000             */
/*                 upload and download services.                     */
/*********************************************************************/
#define GetRAMEndAddrForUpDownload()            ((uint8_t*) DOWNLOADRAM_END)

/*********************************************************************/
/*         Returns the requested data byte from the recv.            */
/*                 buffer                                            */
/*********************************************************************/
#define GetServiceData(location)                ((uint8_t) GetKw2000ServiceData(location))

/*********************************************************************/
/*         Returns The data length of the recv. buffer               */
/*********************************************************************/
#define GetServiceDataLength()                  ((uint8_t) GetKeyword2000ServiceDataLength())

/*********************************************************************/
/*          Write the service DLL data buffer                        */
/*********************************************************************/
#define WrtServiceData(data,location)           (WrtKw2000ServiceData( data , location ))

/*********************************************************************/
/*          test for DLL finsh send Transmit buffer                  */
/*********************************************************************/
#define AnswerStillBeingSent()                  (Keyword2000AnswerStillBeingSent())

/*********************************************************************/
/*      Returns the start address of the Calibration Rom section.    */
/*********************************************************************/
#define GetROMCalibrationStart()                ((uint8_t *) CpHWIO_ROM_CalibrationStart)

/*********************************************************************/
/*     Returns the end address of the Calibration Rom section.       */
/*********************************************************************/
#define GetROMCalibrationEnd()                  ((uint8_t *) CpHWIO_ROM_CalibrationEnd)



/*********************************************************************/
/*  These functions are application-dependent. Application interface,*/
/*  functions/variables/definitions must be hooked.                  */
/*********************************************************************/

/*********************************************************************/
/*  This procedure returns a boolean to indicate if the              */
/*             engine is turning   True = is turning.                */
/*             This procedure MUST call some application function    */
/*             which returns the state of Engine Turning as a        */
/*             boolean.                                              */
/*********************************************************************/
#define Get_EngineTurning()                     ( GetEngineTurning() )

/*********************************************************************/
/*  This procedure returns a boolean to indicate if the              */
/*             vehicle is moving   True = is moving.                */
/*             This procedure MUST call some application function    */
/*             which returns the state of vehicle moving as a        */
/*             boolean.                                              */
/*********************************************************************/
#define Get_VehicleMoving()                     ( GetVIOS_v_VehSpd() > V_KPH(3))

/*********************************************************************/
/*    This procedure returns a boolean to indicate if the            */
/*               Appication code has shut down..........             */
/*               This procedure MUST call some application function  */
/*               which returns the state of Api layer                */
/*               boolean.                                            */
/*********************************************************************/
#define GetAppRdyForPrograming()                (CanBeProgrammed() )

/*********************************************************************/
/*   This function returns TRUE if manufacturing or development      */
/*   mode is active.  The security access service unlocks the box    */
/*   if this function returns TRUE.  Application should define the   */
/*   logic here.                                                     */
/*********************************************************************/
#define IsDevelopmentOrManfModeActive()         (    IsDevelopment() \
                                                  || ( Get_Security_Seed_Data() == 0x0000 ) \
                                                  || ( Get_Security_Seed_Data() == 0xffff ) \
                                                  || ( Kw2000VulnerabilityFlag == 0xFF ) )

#define IsL2SecurityKeyNotValid()               (    IsDevelopment()  )

/*********************************************************************/
/*     The function resets the actautors, which are                  */
/*     activated by the client during the diagnostic                 */
/*     session.                                                      */
/*********************************************************************/
#define ResetActuatorsIfActivated()

/*********************************************************************/
/*     Returns the start address of the Calibration                  */
/*     Rom section.                                                  */
/*********************************************************************/
#define GetAPI_Isgasoline()                         (true )

/*********************************************************************/
/*     This functions returns TRUE, if the conditions exists to      */
/*     run the service 38 in diagnostic mode. Application has to     */
/*     include the logic to test the conditions.                     */
/*********************************************************************/
#define CheckIfConditionsCorrectToRunInDiagMode()       (true )

/*********************************************************************/
/*  This function resets the system.  Invoke the application         */
/*  processor reset function.                                        */
/*********************************************************************/
static INLINE void PerformReset(void)
{
   while (true) {};
}

/*********************************************************************/
/*  This function returns TRUE when main keyword logic is executing. */
/*  This function is useful in cases where the keyword line is used  */
/*  by other devices/protocals such as Immobilizer. Invoke the       */
/*  application function.                                            */
/*********************************************************************/
#define IfKeywordLogicIsActive()            (true)

/*********************************************************************/
/*  This function do   required actions before doing a reset.        */
/*  such as : clear the non-volatile (NVRAM), other initializations  */
/*  etc.                                                             */
/*********************************************************************/
#define DoNecessaryActionsBeforeReset()                    /* no action required -yet- */

/*********************************************************************/
/*         Returns The Value of "CAL ID software version ID"         */
/*********************************************************************/
#define GetCALIBRATION_FILE_PART_NRVal(Index)       ((uint8_t) Index)


/*********************************************************************/
/*   Returns TRUE if the engine state is FUEL_RUN.                   */
/*********************************************************************/
#define IfEngineStateIsFuelRun()            (true)

/*********************************************************************/
/*   Returns TRUE if the engine state is KEY_ON.                     */
/*********************************************************************/
#define IfEngineStateIsKeyOn()              (true)



/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 03/03/03     sgchia      106
 * + Boot Loader.
 *   - moved GetSrv10BaudRate() out of this file.
 *
 * March/09/2006 Q.W     mt20u2#47
 * + Support SAE J1979 kw2000 modes
 *   -delete redundant function define, remove constant define
 *
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - defined: IsL2SecurityKeyNotValid()
\* ============================================================================ */
#endif

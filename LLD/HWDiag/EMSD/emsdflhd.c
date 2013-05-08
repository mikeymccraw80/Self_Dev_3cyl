/*****************************************************************************
* Filename:             emsdflhd.c
*
* Description:          OBDII program to process Flash ROM Checksum 
*                       Diagnostic
*
* List of functions:    InitEMSD_FileROMOFVC_Clear ()
*                       InitEMSD_FileROMRstToKeyOn ()
*                       MngEMSD_FileROM125msTasks ()
*
* List of inlines:
*
* C Software Project Forward EMS
* (c) Copyright Delco Electronics 2005
*****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/
#include "emsdfexi.h" /* For external interfaces                 */
#include "emsdpapi.h" /* For forced declaration definition check */
#include "emsdcald.h" /* For local calibrations                  */

/*****************************************************************************
 *  Local Include Files
 *****************************************************************************/


/*****************************************************************************
*   Local Function Declarations
******************************************************************************/

/*****************************************************************************
 *  Static Data Define
 *****************************************************************************/
  TbBOOLEAN        SbEMSD_FileROMTestComplete ;
#pragma section [nvram] 
  TbBOOLEAN        SbEMSD_FileROMTestFailed ;
#pragma section [] 
/*****************************************************************************
 *  Function definition
 ******************************************************************************/

/*****************************************************************************
 *
 * Function:     InitEMSD_FileROM_RstToKeyOn
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
//FAR_COS void InitEMSD_FileROMRstToKeyOn(void)
//{
  
  //SbEMSD_FileROMTestComplete= CbFALSE;
  //SbEMSD_FileROMTestFailed  = CbFALSE;

//}

 /*****************************************************************************
 *
 * Function:     MngEMSD_FileROM125msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 0.125 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void MngEMSD_FileROM125msTasks (void)
{
 if(!SbEMSD_FileROMTestComplete)
 {
  /*     
 *      ==================================================
 *      This process activates the Data Manager and reports
 *      the FileROM_Checksum fail/pass results
 *      when the test has been completed. The Data Manager is
 *      activated immediately (CALL, JSR, etc.) when
 *      Report_Test_Failed or Report_Test_Passed is set to
 *      "CbTRUE", and reports the test result identified by
 *      DTC_Identifier. Multiple results will be reported
 *      successively. */

    if( (GetVIOS_IgnSt() == CeIGN_ON)
	&&GetEMSD_FileROM_ChecksumState())
      {
       SbEMSD_FileROMTestFailed   = CbTRUE;
       SbEMSD_FileROMTestComplete = CbTRUE;
      }
      else
      {
       SbEMSD_FileROMTestFailed   = CbFALSE;
       SbEMSD_FileROMTestComplete = CbTRUE;
      }

 }
 else
 {
  /* do nothing*/
 }
}
/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 
\* ============================================================================ */

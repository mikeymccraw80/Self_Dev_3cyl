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
#include "emsdpapi.h" /* For forced declaration definition check */
#include "emsdcald.h" /* For local calibrations                  */
#include "mall_lib.h"
#include "intr_ems.h"
#include "v_power.h"
#include "hal_memory.h"
#include "io_config_eeprom.h"
 
/*****************************************************************************
 *  Static Data Define
 *****************************************************************************/
#pragma section DATA " " ".nc_nvram"
TbBOOLEAN        SbEMSD_FileROMTestFailed ;
#pragma section DATA " " ".bss"

TbBOOLEAN   SbEMSD_FileROMTestComplete;

static TbBOOLEAN   Sb_AppCksum_Test_Failed;
static TbBOOLEAN   Sb_CalCksum_Test_Failed;
static TbBOOLEAN   Sb_AppCksum_Calc_Complete;
static TbBOOLEAN   Sb_CalCksum_Calc_Complete;
static uint16_t    Vc_AppCksum;
static uint16_t    Vc_CalCksum;
static uint16_t *  SpFILE_AppROM_ChecksumLocation;
static uint16_t *  SpFILE_CalROM_ChecksumLocation;

#define        CcFILE_ROM_NumOfWordsToSumAtOnce        (64)

#define GetEMSD_FileROM_ChecksumState() (Sb_AppCksum_Test_Failed || Sb_CalCksum_Test_Failed)
/*****************************************************************************
 *  Function definition
 ******************************************************************************/


uint16_t PerfmFILE_ROM_Checksum(uint16_t * start_addr, uint16_t * end_addr)
{
	uint16_t cksum = 0;

	while( start_addr < end_addr ) {
		cksum += *start_addr;
		start_addr ++;
	}

	return cksum;
}

/*****************************************************************************
 *
 * Function:     InitEMSD_FileROM_RstToKeyOn
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void InitEMSD_FileROMRstToKeyOn(void)
{
	SbEMSD_FileROMTestComplete = CbFALSE;
	Sb_AppCksum_Test_Failed    = CbFALSE;
	Sb_CalCksum_Test_Failed    = CbFALSE;
	Sb_AppCksum_Calc_Complete  = CbFALSE;
	Sb_CalCksum_Calc_Complete  = CbFALSE;

	Vc_AppCksum                    = 0;
	Vc_CalCksum                    = 0;
	SpFILE_AppROM_ChecksumLocation = 0;
	SpFILE_CalROM_ChecksumLocation = 0;
}

 /*****************************************************************************
 *
 * Function:     MngEMSD_FileROM10msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 0.125 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *               code execution time is about 12us
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void MngEMSD_FileROM10msTasks (void)
{
	uint16_t cksum_portion;
	uint16_t cksum_cal_calculation;

	if (!Sb_AppCksum_Calc_Complete) {
		if (SpFILE_AppROM_ChecksumLocation == 0) {
			SpFILE_AppROM_ChecksumLocation = IO_MEM_ROM_Block_Checksum[2].VpHWIO_MemSegmentStartAddress;
		} else if (SpFILE_AppROM_ChecksumLocation < IO_MEM_ROM_Block_Checksum[2].VpHWIO_MemSegmentEndAddress) {
			cksum_portion = PerfmFILE_ROM_Checksum(SpFILE_AppROM_ChecksumLocation, SpFILE_AppROM_ChecksumLocation + CcFILE_ROM_NumOfWordsToSumAtOnce);
			Vc_AppCksum += cksum_portion;
			SpFILE_AppROM_ChecksumLocation += CcFILE_ROM_NumOfWordsToSumAtOnce;
		} else {
			Sb_AppCksum_Calc_Complete = CbTRUE;
			/*calculate the app cksum */
			Vc_AppCksum = Vc_AppCksum - *(uint16_t*)(PF_KKSUM_ADDRESS);
			/* validate the cksum, this should be palce behind siu init */
			if (Vc_AppCksum != *((uint16_t*)PF_KKSUM_ADDRESS)) {
				Sb_AppCksum_Test_Failed = CbTRUE;
			} else {
				Sb_AppCksum_Test_Failed = CbFALSE;
			}
		}
	} else if (!Sb_CalCksum_Calc_Complete) {
		if (SpFILE_CalROM_ChecksumLocation == 0) {
			SpFILE_CalROM_ChecksumLocation = IO_MEM_ROM_Block_Checksum[1].VpHWIO_MemSegmentStartAddress;
		} else if (SpFILE_CalROM_ChecksumLocation < IO_MEM_ROM_Block_Checksum[1].VpHWIO_MemSegmentEndAddress) {
			cksum_portion = PerfmFILE_ROM_Checksum(SpFILE_CalROM_ChecksumLocation, SpFILE_CalROM_ChecksumLocation + CcFILE_ROM_NumOfWordsToSumAtOnce);
			Vc_CalCksum += cksum_portion;
			SpFILE_CalROM_ChecksumLocation += CcFILE_ROM_NumOfWordsToSumAtOnce;
		} else {
			Sb_CalCksum_Calc_Complete = CbTRUE;
			/*calculate the app cksum */
			Vc_CalCksum = Vc_CalCksum - *(uint16_t*)(CAL_CKSUM_ADDRESS);
			cksum_cal_calculation = Vc_CalCksum;
			Vc_CalCksum = (uint16_t)(~Vc_CalCksum + 0X01);
			/* validate the cksum, this should be palce behind siu init */
			if ((uint16_t)(cksum_cal_calculation + *((uint16_t*)CAL_CKSUM_ADDRESS)) == 0) {
				Sb_CalCksum_Test_Failed = CbFALSE;
			} else {
				Sb_CalCksum_Test_Failed = CbTRUE;
			}
		}
	} else {
		// todo nothing
	}

	if((!SbEMSD_FileROMTestComplete) && (GetVIOS_IgnSt() == CeIGN_ON)) {
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
		if (Sb_AppCksum_Calc_Complete && Sb_AppCksum_Test_Failed) {
			SbEMSD_FileROMTestFailed   = CbTRUE;
			SbEMSD_FileROMTestComplete = CbTRUE;
		} else if (Sb_CalCksum_Calc_Complete && Sb_CalCksum_Test_Failed) {
			SbEMSD_FileROMTestFailed   = CbTRUE;
			SbEMSD_FileROMTestComplete = CbTRUE;
		} else {
			SbEMSD_FileROMTestComplete = (Sb_AppCksum_Calc_Complete && Sb_CalCksum_Calc_Complete);
			if (SbEMSD_FileROMTestComplete) {
				SbEMSD_FileROMTestFailed = CbFALSE;
			}
		}
	} else {
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

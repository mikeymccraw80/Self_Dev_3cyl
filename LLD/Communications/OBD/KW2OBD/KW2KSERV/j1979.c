/***********************************************************************
*  DELCO ELECTRONICS CORPORATION, INC.                                 *
*  COPYRIGHT 1999 DELCO ELECTRONICS CORPORATION, INC.                  *
*  ALL RIGHTS RESERVED                                                 *
*  This program may not be reproduced, in whole or in part in any form *
*  or by any means whatsoever without the written permission of:       *
*                                                                      *
*         DELCO ELECTRONICS CORPORATION                                *
*         One Corporate Center                                         *
*         Kokomo, Indiana  46904-9005                                  *
*         USA                                                          *
*                                                                      *
************************************************************************
* Filename     : j1979.c                                               *
* Project Name : Isuzu-2000                                            *
*                                                                      *
* Applicable   : J1979 Modes 1- 9                                      *
* Documents                                                            *
* Version      : 1.0                                                   *
* Date         : June 1998.                                            *
*                                                                      *
* Purpose      : Keyword 2000 application level service handler.       *
*                                                                      *
* Description  : This module is the application layer of Keyword 2000, *
*                where the application level services are processed.   *
*                                                                      *
* $Source: ems_project@brighton.tcb:gmdat05:j1979.c $                *
* $Revision: 1.3 $                                                     *
* $Author: bright...:/ems/users/nz35qp/dsds/diagegrf:nz35qp $          *
* Creation Date: APR 7th 1997                                          *
*                                                                      *
*
************************************************************************
*                                                                      *
* External variables and constants referenced, and why:                *
*          NAME                DECLARED IN     REASON/PURPOSE          *
*                                                                      *
************************************************************************
* Functions in this file:                                              *
************************************************************************
*                                                                      *
***********************************************************************/
 
/***********************LOCAL DEFINITIONS:*****************************/

/*********************************************************************/
/*** Initialize Kw2000 application level service handler.          ***/
/*********************************************************************/
#include "lux_type.h"
#include "j1979.h"
#include "kw2api.h"    /*  GetServiceDataLength() */
#include "kw2dll.h"    /* nrcSubFunctionNotSupported_InvalidFormat */
// #include "t_custom.h"  
// #include "dd_nvram.h" 
#include "HLS.h"
// #include "id_cald.h"
#include "obdlfsrv.h"
/*********************************************************************/
/*            TYPE DEFS                                              */
/*********************************************************************/

/*********************************************************************/
/*            Extern Object                                                */
/*********************************************************************/
VehicleInformation scnVehInfo;
ECU_Identification scnEcuId;


/*********************************************************************/
/*            STATIC DATA DECLARATIONS                               */
/* Removed Mode 8 static variables. bdt 4/10/00                      */
/*********************************************************************/
static BYTE                            Vi1979_Mode09_MsgIdx ;
static BYTE                            Vi1979_Mode09_CalCharIdx ;
static BYTE                            Vi1979_Mode09_CalIdx ;
static BYTE                            Vi1979_CompID ;
static BYTE                            Vi1979_Mode09_CurrMsgIdx ;
/*********************************************************************/
/*            STATIC FUNCTION PROTOTYPES                             */
/*********************************************************************/

/*********************************************************************/
/*            Mode 6 Test ID Tables                                  */
/* Constant definitions in this table are part of j1979 generic      */
/* specification. Application should add/delete the array elements   */
/* according to the specific project.                                */
/*********************************************************************/

/*
 * Request Catalyst Efficiency "Non-Idle" test Results
 */

/*********************************************************************/
/* FUNCTION:     J1979Mode1Handler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   Request current Powertrain Diagnostic Data          */
/*                                                                   */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*                                                                   */
/*********************************************************************/
#define J1979_MODE_01_MSG_LENGTH (2) 
#define Cy1979_Mode_01_MaxInfoType      (0x60)
#define CyInfoType               (1)
//BYTE    Vy1979_InfoType ;

void J1979Mode1Handler (void)
{
	BYTE LyFound;
	BYTE Ly1979_MsgIdx ;
	BYTE Li1979_DataIdx ;
	Li1979_DataIdx = CyInfoType;
	LyFound  = 0;


	if ( GetServiceDataLength() == J1979_MODE_01_MSG_LENGTH ) {
		Vy1979_InfoType =  GetServiceData(CyInfoType);
		WrtServiceData( Vy1979_InfoType , Li1979_DataIdx++ );

		if ( Vy1979_InfoType < Cy1979_Mode_01_MaxInfoType ) {
			LyFound = CbTRUE ;
			switch(Vy1979_InfoType) {
			case Cy1979_PID00:  /*PID 00*/
				// WrtServiceData( Cy1979_PID00 , Li1979_DataIdx++ ) ;
				/*support PID(01~08) 01, 02,03, 04,05, 06, 07*/
				WrtServiceData( 0xFE , Li1979_DataIdx++ ) ;
				/*support PID(09~10) 0B, 0C,0D, 0E,0F*/
				WrtServiceData( 0x3E , Li1979_DataIdx++ ) ;
				/*support PID(11~18) 11, 13,14, 15*/
				WrtServiceData( 0xB8, Li1979_DataIdx++ ) ;
				/*support PID(19~20) 1C, 1F,20*/
				WrtServiceData( 0x13 , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID01: /*PID 01*/
				WrtServiceData( telem_data.tele_Monitor_status[0] ,Li1979_DataIdx++);
				WrtServiceData( telem_data.tele_Monitor_status[1] ,Li1979_DataIdx++);
				WrtServiceData( telem_data.tele_Monitor_status[2] ,Li1979_DataIdx++);
				WrtServiceData( telem_data.tele_Monitor_status[3] ,Li1979_DataIdx++);
				break;

			case Cy1979_PID02: /*PID 02*/
				WrtKw2000ServiceData( Hi8Of16( telem_data.tele_Cause_Frame_Pcode ), Li1979_DataIdx++);
				WrtKw2000ServiceData( Lo8Of16( telem_data.tele_Cause_Frame_Pcode ), Li1979_DataIdx++);
				break;

			case Cy1979_PID03: /*PID 03*/
				WrtServiceData( telem_data.tele_B_FuelStatus,Li1979_DataIdx++);
				WrtServiceData( 0x00,Li1979_DataIdx++);
				break;

			case Cy1979_PID04: /*PID 04*/
				WrtServiceData( telem_data.tele_CsMaf,Li1979_DataIdx++);
				break;

			case Cy1979_PID05: /*PID 05*/
				WrtServiceData( telem_data.tele_TmLin,Li1979_DataIdx++);
				break;

			case Cy1979_PID06: /*PID 06*/
				WrtServiceData( telem_data.tele_fLc,Li1979_DataIdx++);
				break;

			case Cy1979_PID07: /*PID 07*/
				WrtServiceData( telem_data.tele_fLcAd,Li1979_DataIdx++);
				break;

			case Cy1979_PID0B:
				WrtServiceData( telem_data.tele_Pmap,Li1979_DataIdx++);
				break;

			case Cy1979_PID0C:     
				WrtServiceData( Hi8Of16(telem_data.tele_N),Li1979_DataIdx++);
				WrtServiceData( Lo8Of16(telem_data.tele_N),Li1979_DataIdx++);
				break;

			case Cy1979_PID0D:
				WrtServiceData( telem_data.tele_Vsp,Li1979_DataIdx++);
				break;

			case Cy1979_PID0E:
				WrtServiceData( telem_data.tele_IgaOut,Li1979_DataIdx++);
				break;

			case Cy1979_PID0F:
				WrtServiceData( telem_data.tele_TaLin,Li1979_DataIdx++);
				break;

			case Cy1979_PID14:
				WrtServiceData( telem_data.tele_uLsb,Li1979_DataIdx++);
				WrtServiceData( telem_data.tele_uLsbfLc,Li1979_DataIdx++);
				break;

			case Cy1979_PID15:
				WrtServiceData( telem_data.tele_uLsa,Li1979_DataIdx++);
				WrtServiceData( telem_data.tele_uLsafLc,Li1979_DataIdx++);
				break;

			case Cy1979_PID1C:
				WrtServiceData( telem_data.tele_obd_Type,Li1979_DataIdx++);
				break;

			case Cy1979_PID1D:
				WrtServiceData( telem_data.tele_O2SPos,Li1979_DataIdx++);
				break;

			case Cy1979_PID1F:
				WrtServiceData( Hi8Of16(telem_data.tele_tStaEnd),Li1979_DataIdx++);
				WrtServiceData( Lo8Of16(telem_data.tele_tStaEnd),Li1979_DataIdx++);
				break;

			case Cy1979_PID20:
				//    WrtServiceData( Cy1979_PID20 , Li1979_DataIdx++ ) ;
				/*support PID(21~28) 21*/
				WrtServiceData( 0x80,Li1979_DataIdx++);
				/*support PID(29~30) 2E, 2F*/
				WrtServiceData( 0x07,Li1979_DataIdx++);
				/*support PID(31~38) 30,33*/
				WrtServiceData( 0x20,Li1979_DataIdx++);
				/*support PID(31~40) */
				WrtServiceData( 0x11,Li1979_DataIdx++);
				break;

			case Cy1979_PID21:
				WrtServiceData( Hi8Of16(telem_data.tele_KmQ6Mil),Li1979_DataIdx++);
				WrtServiceData( Lo8Of16(telem_data.tele_KmQ6Mil),Li1979_DataIdx++);
				break;

			case Cy1979_PID2E:
				WrtServiceData( telem_data.tele_DuCyPgOut,Li1979_DataIdx++);
				break;

			case Cy1979_PID30:
				WrtServiceData( telem_data.tele_WmuCntVal,Li1979_DataIdx++);
				break;

			case Cy1979_PID33:
				WrtServiceData( telem_data.tele_Pam,Li1979_DataIdx++);
				break;

			case Cy1979_PID3C:
				WrtServiceData( Hi8Of16(telem_data.tele_TcatPre_b),Li1979_DataIdx++);
				WrtServiceData( Lo8Of16(telem_data.tele_TcatPre_b),Li1979_DataIdx++);
				break;

			case Cy1979_PID40:
				//      WrtServiceData( Cy1979_PID40 , Li1979_DataIdx++ ) ;
				/*support PID(41~48) 42, 46*/
				WrtServiceData( 0x44,Li1979_DataIdx++);
				/*support PID(49~50) */
				WrtServiceData( 0x00,Li1979_DataIdx++);
				/*support PID(51~58) 30,33*/
				WrtServiceData( 0x00,Li1979_DataIdx++);
				/*support PID(59~60) */
				WrtServiceData( 0x00,Li1979_DataIdx++);
				break;

			case Cy1979_PID42:
				WrtServiceData(  Hi8Of16(telem_data.tele_Ub_b),Li1979_DataIdx++);
				WrtServiceData(  Lo8Of16(telem_data.tele_Ub_b),Li1979_DataIdx++);
				break;

			case Cy1979_PID45:
				WrtServiceData( telem_data.tele_TpPos,Li1979_DataIdx++);
				break;

			case Cy1979_PID46:
				WrtServiceData( telem_data.tele_Tam,Li1979_DataIdx++);
				break;

			case Cy1979_PID51:
				WrtServiceData( telem_data.tele_FuelType,Li1979_DataIdx++);
				break;

			case Cy1979_PID5A:
				WrtServiceData( telem_data.tele_PedPos,Li1979_DataIdx++);
				break;

			default: 
				/* Send negative responce if PID not supported */
				LyFound = CbFALSE ;                 
				break;
			}

			if ( LyFound != CbFALSE ) {
				SendStandardPositiveAnswer( Li1979_DataIdx );
			} else {
				SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
			}
		} else {
			/* Send negative responce if PID not supported */
			SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
		}
	} else {
		/* Send negative responce if PID not supported */
		SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	}
}



/*********************************************************************/
/* FUNCTION:     KwJ1979Mode2Handler                                 */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   This allows access to the data which is captured    */
/*               in the powertrain controller freezeframe            */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#define Cy1979_Mode_02_MaxInfoType      (0x60)
#define J1979_MODE_02_MSG_LENGTH (3)
#define CyReqPIDNumberMode2      (1)
#define Cy1979_FramePosition     (2)
#define Cy1979FrameReqZero       (0)
#define Cy1979FrameReqMax        (3)

void J1979Mode2Handler (void)
{
	BYTE LyFound = 0, Li1979_DataIdx = CyInfoType;
	BYTE frame_index, info_index;

	if ( GetServiceDataLength() == J1979_MODE_02_MSG_LENGTH ) {
		info_index =  GetServiceData(CyInfoType);
		frame_index = GetKw2000ServiceData ( Cy1979_FramePosition );

		if( ( info_index < Cy1979_Mode_02_MaxInfoType )&& (frame_index < Cy1979FrameReqMax )) {
			Li1979_DataIdx = 1;
			WrtServiceData( info_index , Li1979_DataIdx++ );

			LyFound = CbTRUE ;

			switch (info_index) {

			case Cy1979_PID00:  /*PID 00*/
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				/*support PID(01~08) 01, 02,03, 04,05, 06, 07*/
				WrtServiceData( 0x7E , Li1979_DataIdx++ ) ;
				/*support PID(09~10) 0B, 0C,0D, 0E,0F*/
				WrtServiceData( 0x3E , Li1979_DataIdx++ ) ;
				/*support PID(11~18) 11, 13,14, 15*/
				WrtServiceData( 0x80, Li1979_DataIdx++ ) ;
				/*support PID(19~20) 1C, 1F,20*/
				WrtServiceData( 0x01 , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID02:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Frame_Pcode), Li1979_DataIdx++ ) ;
				WrtServiceData( Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Frame_Pcode) , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID03:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_B_FuelStatus, Li1979_DataIdx++ ) ;
				//  WrtServiceData( 0x00 , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID04:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_CsMaf, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID05:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_TmLin, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID06:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_fLc, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID07:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_fLcAd, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0B:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Pmap, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0C:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData(  Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_N), Li1979_DataIdx++ ) ;
				WrtServiceData(  Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_N) , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0D:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Vsp, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0E:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_IgaOut, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0F:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_TaLin, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID11:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_TpPos, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID20:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				/*support PID(21~28) 21*/
				WrtServiceData( 0x80 , Li1979_DataIdx++ ) ;
				/*support PID(29~30) */
				WrtServiceData( 0x00 , Li1979_DataIdx++ ) ;
				/*support PID(31~38) */
				WrtServiceData( 0x00, Li1979_DataIdx++ ) ;
				/*support PID(39~40) 40*/
				WrtServiceData( 0x01 , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID21:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData(  Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_KmQ6Mil), Li1979_DataIdx++ ) ;
				WrtServiceData(  Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_KmQ6Mil) , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID40:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				/*support PID(41~48) 42*/
				WrtServiceData( 0x40 , Li1979_DataIdx++ ) ;
				/*support PID(49~50) */
				WrtServiceData( 0x00 , Li1979_DataIdx++ ) ;
				/*support PID(51~58) */
				WrtServiceData( 0x00, Li1979_DataIdx++ ) ;
				/*support PID(59~50) 00*/
				WrtServiceData( 0x00 , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID42:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData(  Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Ub_b), Li1979_DataIdx++ ) ;
				WrtServiceData(  Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Ub_b) , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID45:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData(  DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_TpPos, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID5A:
				/*Freezeframe number*/
				WrtServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtServiceData( Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_PedPos_b), Li1979_DataIdx++ ) ;
				WrtServiceData( Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_PedPos_b) , Li1979_DataIdx++ ) ;
				break;

			default: 
				/* Send negative responce if PID not supported */
				LyFound = CbFALSE ;                 
				break;
			}
			if ( LyFound != CbFALSE ) {
				SendStandardPositiveAnswer( Li1979_DataIdx );
			} else {
				SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
			}
		} else {
			/* Send negative responce if PID not supported */
			SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
		}
	} else {
		/* Send negative responce if PID not supported */
		SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	}
}

/*********************************************************************/
/* FUNCTION:     J1979Mode3Handler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Handles the initial request to transmit emission    */
/*               related fault codes.  The message length must be 4  */
/*               and there must NOT be a mode 3 already in process.  */
/*               fThe flag Vb1979_M3_InProgress is used to determine */
/*               if a previous mode 3 is in process.  If valid faults*/
/*               exist ,then a message is queued and a callback is   */
/*               generated to stuff the codes in the message.        */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: Vb1979_M3_FirstMsg,Vb1979_M3_InProgress,*/
/*                           ViC2GL_CurrentMsg                       */
/*********************************************************************/
#define J1979_MODE_03_MSG_LENGTH   (1)
#define J1979_Mode_43_DTC_Length   (7)
#define RETURN_ID_OFFSET           (1)
#define  SyZERO_VALUE   (0)

void J1979Mode3Handler (void)
{
	/* Test for valid  message length */
	if (( J1979_MODE_03_MSG_LENGTH ) == GetServiceDataLength() ) {
		FormJ1979_Mode_43_Data ();
	} else {
		/* Send negative responce if PID not supported */  
		SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	}
}

/*********************************************************************/
/* FUNCTION:     FormJ1979_Mode_43_Data                              */
/*                                                                   */
/* Type:         local                                               */
/*                                                                   */
/* DESCRIPTION:  Invoked by Mode_03 handler as well as Queue1979_Next*/
/*               Mode43 procedure, this function finds out and forms */
/*               the data block for the mode 43 response.            */
/*               As long as valid fault codes exist, this procedure  */
/*               will continue to queue new messages.  When no more  */
/*               faults exist, the remaining bytes of the Keyword    */
/*               message are padded with 0s.                         */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       2 if there are more faults                          */
/*               1 if there is 1 or 2 fault                          */
/*               0 if there is no fault                              */
/*                                                                   */
/* Global Variables Updated: Va1979_M43_Data,Vb1979_M3_FirstMsg,     */
/*********************************************************************/
void FormJ1979_Mode_43_Data( void )
{
	static WORD          DTCCount ;
	/* This signifies if at least one DTC was found, for the present
	packet.  */
	static TbBOOLEAN     DTCFoundInPacket ;
	/* This signifies if at least one DTC was found. */
	static TbBOOLEAN     DTCFound ;

	BYTE                 TrByteCount ;
	TrByteCount = RETURN_ID_OFFSET ;

	while ( DTCCount < count_DTCs_SID03 ) {
		DTCFound = CbTRUE;
		DTCFoundInPacket = CbTRUE;
		WrtServiceData(Hi8Of16(DTCs_SID03[DTCCount]),TrByteCount++);
		WrtServiceData(Lo8Of16(DTCs_SID03[DTCCount]),TrByteCount++);
		DTCCount++;

		if ( TrByteCount >= J1979_Mode_43_DTC_Length ) {
			break;
		}
	}
 
	/* if no DTC was found or if the message lenght is less 
		than maximum append zero's to the message, and send a 
		positive response. */

	if (( !DTCFound ) || (( DTCFoundInPacket ) && ( DTCFound ))) {
		while ( TrByteCount < J1979_Mode_43_DTC_Length ) {
			WrtKw2000ServiceData( 0, TrByteCount++);
		}
	} else {
		TrByteCount = 0;
	}

	SendStandardPositiveAnswer (TrByteCount);

	/* set the flag to FALSE, the message is complete */
	DTCFoundInPacket = CbFALSE;
 
	/* If all the list is searched, disable multiple response message logic.  */
	if ( DTCCount >= count_DTCs_SID03) {
		DTCFound = CbFALSE;
		DTCCount = 0;
		WrtMultiRespInProgress( CbFALSE  ) ;
	} else {
		WrtMultiRespInProgress( CbTRUE  ) ;
	}
}

/*********************************************************************/
/* FUNCTION:     J1979Mode4Handler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Mode 4 message is a request to clear/reset all      */
/*               diagnostic information.  This request initializes   */
/*               both emission and non-emission related powertrain   */
/*               diagnostics which must include all transmission,    */
/*               engine, etc. diagnostics.  The list of variables and*/
/*               corresponding initialization values is extensive.   */
/*               Along with clearing DTC's, freeze frame and failure */
/*               records Fault ID's must be cleared, diagnostic      */
/*               timers and counters initialized, etc.  Some variable*/
/*               initialization is conditional on whether a DTC is   */
/*               stored.  A typical application will likely be       */
/*               required to initialize humdreds of variables.       */
/*               "initialization" in general does not mean "clear".  */
/*               The PCM response to this request contains only an   */
/*               acknowledgement that the request has been granted   */
/*               or is in the process of being granted.  The PCM will*/
/*               always respond to this request affirmatively after  */
/*               it has received it.  The PCM does not need to wait  */
/*               until the actual initialization process is complete */
/*               to respond.  The PCM requirement the initialization */
/*               shall be complete no later than 1 second after the  */
/*               44 response.  At a minimum, the ignition must be ON */
/*               to guarantee a complete execution of this request.  */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
/* no callback need to be set for mode 44 transmit*/
#define J1979_MODE_04_MSG_LENGTH  (1)

void J1979Mode4Handler (void)
{
	if (GetServiceDataLength() == ( J1979_MODE_04_MSG_LENGTH )) {
		/* It is not required to reply after clearing the DTC's.
		* The DTC's should be cleared within 1 second of sending
		* the response.
		*/
		B_DiagInfoClrReq = true;
		SendStandardPositiveAnswer ( RETURN_ID_OFFSET );
		/* imported from CMNDTC module */
	} else {
		SendStandardNegativeAnswer(
		nrcSubFunctionNotSupported_InvalidFormat);
	}
}

/*********************************************************************/
/* FUNCTION:     J1979Mode7Handler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Handles the initial request to transmit emission    */
/*               related fault codes.  The message length must be 4  */
/*               and there must NOT be a mode 7 already in process.  */
/*               fThe flag Vb1979_M7_InProgress is used to determine */
/*               if a previous mode 7 is in process.  If valid faults*/
/*               exist ,then a message is queued and a callback is   */
/*               generated to stuff the codes in the message.        */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: Vb1979_M7_FirstMsg,Vb1979_M7_InProgress,*/
/*                           ViC2GL_CurrentMsg                       */
/*********************************************************************/
/* mode 47 transmit callback is set, data from array Va1979_M47_Data */
/* should be transmitted and the data length should be entered as six*/
/* in the table.                                                     */
#define J1979_MODE_07_MSG_LENGTH   (1)
#define J1979_Mode_47_DTC_Length   (7)
#define RETURN_ID_OFFSET           (1)
 
void J1979Mode7Handler (void)
{
	if ( J1979_MODE_07_MSG_LENGTH == GetServiceDataLength() ) {
		/*  WrtMultiRespInProgress( CbTRUE  ) ; */
		FormJ1979_Mode_47_Data ();
	} else {
		/* Send negative responce if message length not valid. */
		SendStandardNegativeAnswer(
		nrcSubFunctionNotSupported_InvalidFormat);
	}
}


/*********************************************************************/
/* FUNCTION:     Form1979_Mode_47_Data                               */
/*                                                                   */
/* Type:         local                                               */
/*                                                                   */
/* DESCRIPTION:  Invoked by Mode_07 handler as well as Queue1979_Next*/
/*               Mode47 procedure, this function finds out and forms */
/*               the data block for the mode 47 response.            */
/*               As long as valid fault codes exist, this procedure  */
/*               will continue to queue new messages.  When no more  */
/*               faults exist, the remaining bytes of the Class 2    */
/*               message are padded with 0s.                         */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       2 if there are more faults                          */
/*               1 if there is 1 or 2 fault                          */
/*               0 if there is no fault                              */
/*                                                                   */
/* Global Variables Updated: Va1979_M47_Data,Vb1979_M7_FirstMsg,     */
/*********************************************************************/
void FormJ1979_Mode_47_Data( void )
{
	static WORD          DTCCount1 ;
	/* This signifies if at least one DTC was found, for the present packet.  */
	static TbBOOLEAN     DTCFoundInPacket1 ;
	/* This signifies if at least one DTC was found. */
	static TbBOOLEAN     DTCFound1 ;

	BYTE                 TrByteCount ;
	TrByteCount = RETURN_ID_OFFSET ;

	while ( DTCCount1 < count_DTCs_SID07 ) {
		DTCFound1 = CbTRUE;
		DTCFoundInPacket1 = CbTRUE;
		WrtServiceData(Hi8Of16(DTCs_SID07[DTCCount1]),TrByteCount++);
		WrtServiceData(Lo8Of16(DTCs_SID07[DTCCount1]),TrByteCount++);
		DTCCount1++;

		if ( TrByteCount >= J1979_Mode_43_DTC_Length ) {
			break;
		}
	}

    /* if no DTC was found or if the message lenght is less 
       than maximum append zero's to the message, and send a 
       positive response. */

	if (( !DTCFound1 ) || (( DTCFoundInPacket1 ) && ( DTCFound1 ))) {
		while ( TrByteCount < J1979_Mode_43_DTC_Length ) {
			WrtKw2000ServiceData( 0, TrByteCount++);
		}
	} else {
		TrByteCount = 0;
	}

	SendStandardPositiveAnswer (TrByteCount);
	/* set the flag to FALSE, the message is complete */
	DTCFoundInPacket1 = CbFALSE;
 
    /* If all the list is searched, disable multiple response 
       message logic.  */
	if ( DTCCount1 >= count_DTCs_SID07) {
		DTCFound1 = CbFALSE;
		DTCCount1 = 0;
		WrtMultiRespInProgress( CbFALSE  ) ;
	} else {
		WrtMultiRespInProgress( CbTRUE  ) ;
	}
}


/*********************************************************************/
/* FUNCTION:     1979_Mode_09_Request                                */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  This function analyzes the incoming info type and   */
/*               sends the vehicle specific information such as      */
/*               vehicle identification number,calibration ids and   */
/*               calibration verification numbers.This request may   */
/*               have one or more 49 responses.                      */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: ViC2GL_CurrentMsg, Va1979_M49_Data      */
/*********************************************************************/
#define J1979_MODE_09_MSG_LENGTH (2)
void J1979Mode9Handler( void )
{
	BYTE Li1979_DataIdx,Ly1979_MsgIdx,LyMultiMode,LyFound;

	Vi1979_Mode09_MsgIdx = 0;
	Vi1979_Mode09_CalIdx = 0;
	Vi1979_Mode09_CalCharIdx = 0;
	Vi1979_Mode09_CurrMsgIdx = 0;
	Li1979_DataIdx = CyInfoType ;
	LyMultiMode  = 0 ;
	LyFound  = 0;

	if ( GetServiceDataLength() == J1979_MODE_09_MSG_LENGTH ) {
		Vy1979_InfoType =  GetServiceData(CyInfoType);
		WrtServiceData( Vy1979_InfoType , Li1979_DataIdx++ );
		LyFound = CbTRUE ;

		switch(Vy1979_InfoType) {
		case Cy1979_InfoType0:
			WrtServiceData( Cy1979_InfoType0_MsgCnt , Li1979_DataIdx++ ) ;
			/*support infotype 02, 04, 06*/
			WrtServiceData( 0xF3 , Li1979_DataIdx++ ) ;
			WrtServiceData( 0x00 , Li1979_DataIdx++ ) ;
			WrtServiceData( 0x00, Li1979_DataIdx++ ) ;
			WrtServiceData( 0x00 , Li1979_DataIdx++ ) ;
			break;

		case Cy1979_InfoType1:
			WrtServiceData( Cy1979_NumOfMsgsToRptVIN , Li1979_DataIdx++ );
			break;

		case Cy1979_InfoType2:
			Vi1979_Mode09_MsgIdx = Cy1979_NumOfMsgsToRptVIN;
			WrtServiceData(++Vi1979_Mode09_CurrMsgIdx   ,Li1979_DataIdx++) ;
			WrtServiceData( 0 , Li1979_DataIdx++);
			WrtServiceData( 0 , Li1979_DataIdx++);
			WrtServiceData( 0 , Li1979_DataIdx++);
			WrtServiceData( scnVehInfo.VIN[ Vi1979_Mode09_CalCharIdx++ ], Li1979_DataIdx++ );
			LyMultiMode = CbTRUE ;
			break;

		case Cy1979_InfoType3:
			WrtServiceData(Cy1979_NumOfMsgsToRptCalID,Li1979_DataIdx++);
			break;

		case Cy1979_InfoType4:
			Vi1979_Mode09_MsgIdx = (Cy1979_NumOfMsgsToRptCalID );
			WrtServiceData( ++Vi1979_Mode09_CurrMsgIdx,  Li1979_DataIdx++);
			WrtServiceData( scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++],Li1979_DataIdx++ );
			WrtServiceData( scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++],Li1979_DataIdx++ );
			WrtServiceData( scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++],Li1979_DataIdx++ );
			WrtServiceData( scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++],Li1979_DataIdx++ );
			LyMultiMode = CbTRUE ;
			break;

		case Cy1979_InfoType7:
			WrtServiceData(Cy1979_NumOfMsgsToRptIUPR,Li1979_DataIdx++);
			break;

		case Cy1979_InfoType8:
			Vi1979_Mode09_MsgIdx = (Cy1979_NumOfMsgsToRptIUPR);
			WrtServiceData(++Vi1979_Mode09_CurrMsgIdx,  Li1979_DataIdx++);
			WrtServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++);
			WrtServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++);
			WrtServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++);
			WrtServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++);
			LyMultiMode = CbTRUE ;
			break;

		default: 
			/* Send negative responce if PID not supported */
			LyFound = CbFALSE ;                 
			break;
		}

		if(( LyMultiMode ) && ( Vi1979_Mode09_CurrMsgIdx < Vi1979_Mode09_MsgIdx ) && ( LyFound != CbFALSE )) {
			WrtMultiRespInProgress( CbTRUE  ) ;
			if(Li1979_DataIdx > 0)
				SendStandardPositiveAnswer( Li1979_DataIdx );
		} else if ( LyFound != CbFALSE ) {
			SendStandardPositiveAnswer( Li1979_DataIdx );
		} else {
			SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
		}
	} else {
		/* Send negative responce if PID not supported */
		SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	}
}

/*********************************************************************/
/* FUNCTION:     FormJ1979_NextMode49                                */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Invoked periodically to send many more mode 49      */
/*               responses depending on the available calibration ids*/
/*               as response to the previous mode 9 request received.*/
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: Va1979_M49_Data                         */
/*********************************************************************/
#define        HexZero     0
#define Cy1979_InitVal               0
void FormJ1979_NextMode49( void )
{
	BYTE Ly1979_InfoType ;
	BYTE Li1979_DataIdx ;
	BYTE Ly1979_MsgIdx ;
	/* TbBOOLEAN Lb1979_Mode9_ID_6_Done = CbFALSE; */

	if( ( Vi1979_Mode09_MsgIdx > Cy1979_InitVal ) && (Vi1979_Mode09_CurrMsgIdx < Vi1979_Mode09_MsgIdx))
	{
		Li1979_DataIdx = Cy1979_Mode09_MsgNumLoc;
		WrtServiceData( Vy1979_InfoType , Li1979_DataIdx++ );
		WrtServiceData( ++Vi1979_Mode09_CurrMsgIdx, Li1979_DataIdx++ );

		switch (Vy1979_InfoType) {
		case Cy1979_InfoType2:
			for( Ly1979_MsgIdx = 0; Ly1979_MsgIdx < Cy1979_PerRespMaxChar; Ly1979_MsgIdx++ ) {
				WrtServiceData( scnVehInfo.VIN[ Vi1979_Mode09_CalCharIdx++ ], Li1979_DataIdx++ );
			}
			break;

		case Cy1979_InfoType4:
			for( Ly1979_MsgIdx = 0; Ly1979_MsgIdx < Cy1979_PerRespMaxChar; Ly1979_MsgIdx++ ) {
				WrtServiceData(scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++ );
			}
			break;

		case Cy1979_InfoType8:
			for( Ly1979_MsgIdx = 0; Ly1979_MsgIdx < Cy1979_PerRespMaxChar; Ly1979_MsgIdx++ ) {
				WrtServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++ );
			}
			break;

      /* >>>>> This functionality was removed because the
         calculation of the CVN happens so quickly after
         keyon that testing was unable to take the code
         through this path.  This will have to be placed
         back into the code if the S/W as well as the Cal
         are included in the CRC. <<<<<<<<<<<<<<<<<<<<<<<< */

		default:
			--Vi1979_Mode09_CurrMsgIdx;
			break;
		}
	} else {
		Li1979_DataIdx = Cy1979_InitVal;
		Vi1979_Mode09_MsgIdx = Cy1979_InitVal;
		Vi1979_Mode09_CurrMsgIdx = Cy1979_InitVal;
		WrtMultiRespInProgress( CbFALSE );
	}

	if( Vi1979_Mode09_CurrMsgIdx >= Vi1979_Mode09_MsgIdx ) {
		WrtMultiRespInProgress( CbFALSE ) ;
		SendStandardPositiveAnswer( Li1979_DataIdx );
	} else {
		SendStandardPositiveAnswer( Li1979_DataIdx );
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


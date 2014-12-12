/******************************************************************************
 *
 * Filename:          dcanlegi.c
 *
 * Description:       J1979/ISO 15031-5 Modes 0x01- 0x0F diagnostic handler
 *
 * Global Functions Defined:
 *                    J1979Mode1Handler_DCAN
 *                    J1979Mode2Handler_DCAN
 *                    J1979Mode3Handler_DCAN
 *                    FormJ1979_Mode_43_Data_DCAN
 *                    J1979Mode4Handler_DCAN
 *                    J1979Mode5Handler_DCAN
 *                    J1979Mode6Handler_DCAN
 *                    J1979Mode7Handler_DCAN
 *                    FormJ1979_Mode_47_Data_DCAN
 *                    J1979Mode8Handler_DCAN
 *                    J1979Mode9Handler_DCAN
 *                    FormJ1979_NextMode49_DCAN
 *                    J1979ModeAHandler
 *                    FormJ1979_Mode_4A_Data
 * Static Functions Defined:
 *                    Read_O2Sensor_DCAN
 *                    DtrmnDCAN_M6_Data
 *                    PrfmDCAN_MID_SuppRange
 *                    Is1979Mode8TestIDSupp_DCAN
 *                    Refresh1979_Mode8_SystemLeakTest_DCAN
 *                    DtrmnJ1979_SuppM9Infotypes
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2003-2009, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     ctc_pt3#1/csrc/dcanlegi.c/10 %
 * %date_created:  Thu Jun 26 10:56:47 2014 %
 * %version:       10 %
 * %derived_by:    dzrpmq %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
// #include "obdsfexi.h" /*GetVIOS_EngSt_Run()*/
#include "hal_eng.h"
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanlegi.h"
#include "dcanpmid.h"  /*GetDCAN_Param_Value(),GetDCAN_TID_Num(),GetDCAN_MIDNumber()*/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlcdat.h"/*KyDCAN_Mode_09_Info_01_To_08*/
#include "obdlfsrv.h" /* Cy1979_SuppPIDRange_00_20 */
// #include "obdlfpid.h"/*MaskMode_01*/
// #include "obdlfdtc.h"/*Get_Next_Valid_Emission_P_Code*/
// #include "obdlcald.h" /*KbDCANCORE_MODE4_With_EngRUN*/
// #include "ofvcpall.h"/*VbOFVC_DeviceControlActive*/
#include "obdlcdat.h"
#include "kw2srv10m.h"

/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#include "dcancomm.h"  /*for PfrmDCAN_AckReqWithoutResponse()*/
#include "hls.h"
#include "lux_type.h"
#include "j1979.h"

/*********************************************************************/
/*            TYPE DEFS                                              */
/*********************************************************************/

/*********************************************************************/
/*            EQUATES                                                */
/*********************************************************************/
#define  MaskMode_01 0x10
#define  MaskMode_02 0x20
#define  MaskMode_12 0x40
#define  MaskMode_22 0x80

#define  Mode_01 MaskMode_01
#define  Mode_02 MaskMode_02
#define  Mode_12 MaskMode_12 
#define  Mode_22 MaskMode_22 

/*********************************************************************/
/*            GLOBAL CONSTANT VARIABLES                              */
/*********************************************************************/
TbBOOLEAN VbDCAN_NRC78hexInProgress;
TbBOOLEAN VbDCAN_SendNRC78hexResponse;

#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
BYTE   VyDCAN_1979_RequestedMID;
#endif

/*********************************************************************/
/*            STATIC DATA DECLARATIONS                               */
/*********************************************************************/
#if (XeDCAN_SID_08_Supported == CeDCAN_Supported)
static TeMode8TestIDStatus             Se1979Mode8TestID_01_Status;
#endif

#if (XeDCAN_SID_09_Supported == CeDCAN_Supported)
static BYTE                            Sy1979_Mode09_CalIdx ;
static TbBOOLEAN                       Sb1979_M9_InfoTypeFound;


/*********************************************************************/
/*            STATIC DATA DECLARATIONS                               */
/* Removed Mode 8 static variables. bdt 4/10/00                      */
/*********************************************************************/
static BYTE                            Vi1979_Mode09_MsgIdx ;
static BYTE                            Vi1979_Mode09_CalCharIdx ;
static BYTE                            Vi1979_Mode09_CalIdx ;
static BYTE                            Vi1979_CompID ;
static BYTE                            Vi1979_Mode09_CurrMsgIdx ;

#endif

/*********************************************************************/
/*            Static FUNCTIONS                                       */
/*********************************************************************/
#if (XeDCAN_SID_05_Supported == CeDCAN_Supported)
INLINE WORD DCAN_LimitFunction(WORD ,WORD ,WORD );
#endif

#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
static FOUR_BYTE_DATA_TYPE PrfmDCAN_MID_SuppRange(void);
static void DtrmnDCAN_M6_Data(TWO_BYTE_DATA_TYPE *,
                              TWO_BYTE_DATA_TYPE *,
                              TWO_BYTE_DATA_TYPE *,
                              BYTE,
                              BYTE);
#endif

#if (XeDCAN_SID_08_Supported == CeDCAN_Supported)
static TbBOOLEAN    Is1979Mode8TestIDSupp_DCAN( BYTE ) ;
static void         Refresh1979_Mode8_SystemLeakTest_DCAN( void ) ;
#endif

#if (XeDCAN_SID_09_Supported == CeDCAN_Supported)

#endif

/*****************************************************************************
 *  Variable Exports
 *****************************************************************************/
TbBOOLEAN                       Sb1979_EngCVNSent;
BYTE                            Vy1979_InfoType ;
/*********************************************************************/
/*            GLOBAL FUNCTIONS                                       */
/*********************************************************************/

/*********************************************************************/
/* FUNCTION:     J1979Mode1Handler_DCAN                                   */
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
#if (XeDCAN_SID_01_Supported == CeDCAN_Supported)

#define J1979_MODE_01_MIN_MSG_LENGTH (2)
#define J1979_MODE_01_MAX_MSG_LENGTH (7)
#define CyMode1_DataOffset           (1)
#define Cy1979_Mode_01_MaxInfoType      (0x60)

void J1979Mode1Handler_DCAN (void)
{
	BYTE       LyDCAN_PID_DataIdx ;
	BYTE       Li1979_DataIdx ;
	BYTE       LyFound;

	LyFound = 0;

	/*Check if it is in standard diagnostic mode to support service*/
	if(CheckStandardDiagnosticState()) {
		/* check for message validity */
		/* length should contain at least one PID */
		if (( GetLnServiceDataLength () == J1979_MODE_01_MIN_MSG_LENGTH ) ) {
			Li1979_DataIdx = CyMode1_DataOffset;
			Vy1979_InfoType = (GetLnServiceData ())[CyMode1_DataOffset];
			WrtDCAN_ServiceData( Vy1979_InfoType , Li1979_DataIdx++ );

			if ( Vy1979_InfoType < Cy1979_Mode_01_MaxInfoType ) {
				LyFound = CbTRUE ;
				switch(Vy1979_InfoType) {
				case Cy1979_PID00:  /*PID 00*/
					// WrtServiceData( Cy1979_PID00 , Li1979_DataIdx++ ) ;
					/*support PID(01~08) 01, 02,03, 04,05, 06, 07*/
					WrtDCAN_ServiceData( 0xFE , Li1979_DataIdx++ ) ;
					/*support PID(09~10) 0B, 0C,0D, 0E,0F*/
					WrtDCAN_ServiceData( 0x3E , Li1979_DataIdx++ ) ;
					/*support PID(11~18) 11, 13,14, 15*/
					WrtDCAN_ServiceData( 0xB8, Li1979_DataIdx++ ) ;
					/*support PID(19~20) 1C, 1F,20*/
					WrtDCAN_ServiceData( 0x13 , Li1979_DataIdx++ ) ;
					break;

				case Cy1979_PID01: /*PID 01*/
					WrtDCAN_ServiceData( telem_data.tele_Monitor_status[0] ,Li1979_DataIdx++);
					WrtDCAN_ServiceData( telem_data.tele_Monitor_status[1] ,Li1979_DataIdx++);
					WrtDCAN_ServiceData( telem_data.tele_Monitor_status[2] ,Li1979_DataIdx++);
					WrtDCAN_ServiceData( telem_data.tele_Monitor_status[3] ,Li1979_DataIdx++);
					break;

				case Cy1979_PID02: /*PID 02*/
					WrtDCAN_ServiceData( Hi8Of16( telem_data.tele_Cause_Frame_Pcode ), Li1979_DataIdx++);
					WrtDCAN_ServiceData( Lo8Of16( telem_data.tele_Cause_Frame_Pcode ), Li1979_DataIdx++);
					break;

				case Cy1979_PID03: /*PID 03*/
					WrtDCAN_ServiceData( telem_data.tele_B_FuelStatus,Li1979_DataIdx++);
					WrtDCAN_ServiceData( 0x00,Li1979_DataIdx++);
					break;

				case Cy1979_PID04: /*PID 04*/
					WrtDCAN_ServiceData( telem_data.tele_CsMaf,Li1979_DataIdx++);
					break;

				case Cy1979_PID05: /*PID 05*/
					WrtDCAN_ServiceData( telem_data.tele_TmLin,Li1979_DataIdx++);
					break;

				case Cy1979_PID06: /*PID 06*/
					WrtDCAN_ServiceData( telem_data.tele_fLc,Li1979_DataIdx++);
					break;

				case Cy1979_PID07: /*PID 07*/
					WrtDCAN_ServiceData( telem_data.tele_fLcAd,Li1979_DataIdx++);
					break;

				case Cy1979_PID0B:
					WrtDCAN_ServiceData( telem_data.tele_Pmap,Li1979_DataIdx++);
					break;

				case Cy1979_PID0C:     
					WrtDCAN_ServiceData( Hi8Of16(telem_data.tele_N),Li1979_DataIdx++);
					WrtDCAN_ServiceData( Lo8Of16(telem_data.tele_N),Li1979_DataIdx++);
					break;

				case Cy1979_PID0D:
					WrtDCAN_ServiceData( telem_data.tele_Vsp,Li1979_DataIdx++);
					break;

				case Cy1979_PID0E:
					WrtDCAN_ServiceData( telem_data.tele_IgaOut,Li1979_DataIdx++);
					break;

				case Cy1979_PID0F:
					WrtDCAN_ServiceData( telem_data.tele_TaLin,Li1979_DataIdx++);
					break;

				case Cy1979_PID14:
					WrtDCAN_ServiceData( telem_data.tele_uLsb,Li1979_DataIdx++);
					WrtDCAN_ServiceData( telem_data.tele_uLsbfLc,Li1979_DataIdx++);
					break;

				case Cy1979_PID15:
					WrtDCAN_ServiceData( telem_data.tele_uLsa,Li1979_DataIdx++);
					WrtDCAN_ServiceData( telem_data.tele_uLsafLc,Li1979_DataIdx++);
					break;

				case Cy1979_PID1C:
					WrtDCAN_ServiceData( telem_data.tele_obd_Type,Li1979_DataIdx++);
					break;

				case Cy1979_PID1D:
					WrtDCAN_ServiceData( telem_data.tele_O2SPos,Li1979_DataIdx++);
					break;

				case Cy1979_PID1F:
					WrtDCAN_ServiceData( Hi8Of16(telem_data.tele_tStaEnd),Li1979_DataIdx++);
					WrtDCAN_ServiceData( Lo8Of16(telem_data.tele_tStaEnd),Li1979_DataIdx++);
					break;

				case Cy1979_PID20:
					//    WrtServiceData( Cy1979_PID20 , Li1979_DataIdx++ ) ;
					/*support PID(21~28) 21*/
					WrtDCAN_ServiceData( 0x80,Li1979_DataIdx++);
					/*support PID(29~30) 2E, 2F*/
					WrtDCAN_ServiceData( 0x07,Li1979_DataIdx++);
					/*support PID(31~38) 30,33*/
					WrtDCAN_ServiceData( 0x20,Li1979_DataIdx++);
					/*support PID(31~40) */
					WrtDCAN_ServiceData( 0x11,Li1979_DataIdx++);
					break;

				case Cy1979_PID21:
					WrtDCAN_ServiceData( Hi8Of16(telem_data.tele_KmQ6Mil),Li1979_DataIdx++);
					WrtDCAN_ServiceData( Lo8Of16(telem_data.tele_KmQ6Mil),Li1979_DataIdx++);
					break;

				case Cy1979_PID2E:
					WrtDCAN_ServiceData( telem_data.tele_DuCyPgOut,Li1979_DataIdx++);
					break;

				case Cy1979_PID30:
					WrtDCAN_ServiceData( telem_data.tele_WmuCntVal,Li1979_DataIdx++);
					break;

				case Cy1979_PID33:
					WrtDCAN_ServiceData( telem_data.tele_Pam,Li1979_DataIdx++);
					break;

				case Cy1979_PID3C:
					WrtDCAN_ServiceData( Hi8Of16(telem_data.tele_TcatPre_b),Li1979_DataIdx++);
					WrtDCAN_ServiceData( Lo8Of16(telem_data.tele_TcatPre_b),Li1979_DataIdx++);
					break;

				case Cy1979_PID40:
					//      WrtServiceData( Cy1979_PID40 , Li1979_DataIdx++ ) ;
					/*support PID(41~48) 42, 46*/
					WrtDCAN_ServiceData( 0x44,Li1979_DataIdx++);
					/*support PID(49~50) */
					WrtDCAN_ServiceData( 0x00,Li1979_DataIdx++);
					/*support PID(51~58) 30,33*/
					WrtDCAN_ServiceData( 0x00,Li1979_DataIdx++);
					/*support PID(59~60) */
					WrtDCAN_ServiceData( 0x00,Li1979_DataIdx++);
					break;

				case Cy1979_PID42:
					WrtDCAN_ServiceData(  Hi8Of16(telem_data.tele_Ub_b),Li1979_DataIdx++);
					WrtDCAN_ServiceData(  Lo8Of16(telem_data.tele_Ub_b),Li1979_DataIdx++);
					break;

				case Cy1979_PID45:
					WrtDCAN_ServiceData( telem_data.tele_TpPos,Li1979_DataIdx++);
					break;

				case Cy1979_PID46:
					WrtDCAN_ServiceData( telem_data.tele_Tam,Li1979_DataIdx++);
					break;

				case Cy1979_PID51:
					WrtDCAN_ServiceData( telem_data.tele_FuelType,Li1979_DataIdx++);
					break;

				case Cy1979_PID5A:
					WrtDCAN_ServiceData( telem_data.tele_PedPos,Li1979_DataIdx++);
					break;

				default: 
					/* Send negative responce if PID not supported */
					LyFound = CbFALSE ;                 
					break;
				}

				if ( LyFound != CbFALSE ) {
					SendLnStandardPositiveAnswer( Li1979_DataIdx );
				} else {
					SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
				}
			} else {
				/* Send negative responce if PID not supported */
				SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
			}
		} else {
			/* Send negative responce if PID not supported */
			SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
		}
	}
}
#endif

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
#if (XeDCAN_SID_02_Supported == CeDCAN_Supported)
#define Cy1979_Mode_02_MaxInfoType      (0x60)
#define J1979_MODE_02_MSG_LENGTH (3)
#define CyReqPIDNumberMode2      (1)
#define Cy1979_FramePosition     (2)
#define Cy1979FrameReqZero       (0)
#define Cy1979FrameReqMax        (3)

void J1979Mode2Handler_DCAN (void)
{
	BYTE LyFound = 0, Li1979_DataIdx = 1;
	BYTE frame_index, info_index;

	if ( GetLnServiceDataLength() == J1979_MODE_02_MSG_LENGTH ) {
		info_index =  (GetLnServiceData ())[1];
		frame_index = (GetLnServiceData ())[2];

		if( ( info_index < Cy1979_Mode_02_MaxInfoType )&& (frame_index < Cy1979FrameReqMax )) {
			Li1979_DataIdx = 1;
			WrtDCAN_ServiceData( info_index , Li1979_DataIdx++ );

			LyFound = CbTRUE ;

			switch (info_index) {

			case Cy1979_PID00:  /*PID 00*/
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				/*support PID(01~08) 01, 02,03, 04,05, 06, 07*/
				WrtDCAN_ServiceData( 0x7E , Li1979_DataIdx++ ) ;
				/*support PID(09~10) 0B, 0C,0D, 0E,0F*/
				WrtDCAN_ServiceData( 0x3E , Li1979_DataIdx++ ) ;
				/*support PID(11~18) 11, 13,14, 15*/
				WrtDCAN_ServiceData( 0x80, Li1979_DataIdx++ ) ;
				/*support PID(19~20) 1C, 1F,20*/
				WrtDCAN_ServiceData( 0x01 , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID02:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Frame_Pcode), Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Frame_Pcode) , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID03:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_B_FuelStatus, Li1979_DataIdx++ ) ;
				//  WrtServiceData( 0x00 , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID04:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_CsMaf, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID05:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_TmLin, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID06:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_fLc, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID07:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_fLcAd, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0B:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Pmap, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0C:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData(  Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_N), Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData(  Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_N) , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0D:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Vsp, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0E:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_IgaOut, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID0F:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_TaLin, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID11:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_TpPos, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID20:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				/*support PID(21~28) 21*/
				WrtDCAN_ServiceData( 0x80 , Li1979_DataIdx++ ) ;
				/*support PID(29~30) */
				WrtDCAN_ServiceData( 0x00 , Li1979_DataIdx++ ) ;
				/*support PID(31~38) */
				WrtDCAN_ServiceData( 0x00, Li1979_DataIdx++ ) ;
				/*support PID(39~40) 40*/
				WrtDCAN_ServiceData( 0x01 , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID21:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData(  Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_KmQ6Mil), Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData(  Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_KmQ6Mil) , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID40:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				/*support PID(41~48) 42*/
				WrtDCAN_ServiceData( 0x40 , Li1979_DataIdx++ ) ;
				/*support PID(49~50) */
				WrtDCAN_ServiceData( 0x00 , Li1979_DataIdx++ ) ;
				/*support PID(51~58) */
				WrtDCAN_ServiceData( 0x00, Li1979_DataIdx++ ) ;
				/*support PID(59~50) 00*/
				WrtDCAN_ServiceData( 0x00 , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID42:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData(  Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Ub_b), Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData(  Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_Ub_b) , Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID45:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData(  DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_TpPos, Li1979_DataIdx++ ) ;
				break;

			case Cy1979_PID5A:
				/*Freezeframe number*/
				WrtDCAN_ServiceData( frame_index , Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( Hi8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_PedPos_b), Li1979_DataIdx++ ) ;
				WrtDCAN_ServiceData( Lo8Of16(DIAG_STATUS_FREEZE_FRAME[frame_index].Ffm_PedPos_b) , Li1979_DataIdx++ ) ;
				break;

			default: 
				/* Send negative responce if PID not supported */
				LyFound = CbFALSE ;                 
				break;
			}
			if ( LyFound != CbFALSE ) {
				SendLnStandardPositiveAnswer( Li1979_DataIdx );
			} else {
				SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
			}
		} else {
			/* Send negative responce if PID not supported */
			SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
		}
	} else {
		/* Send negative responce if PID not supported */
		SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	}
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode3Handler_DCAN                                   */
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
#if (XeDCAN_SID_03_Supported == CeDCAN_Supported)
#define CcM3_RETURN_ID_OFFSET      (2)


void J1979Mode3Handler_DCAN (void)
{
	/* Test for valid  message length */
	if (( J1979_MODE_03_MSG_LENGTH ) == GetLnServiceDataLength() ) {
		FormJ1979_Mode_43_Data_DCAN ();
	} else {
		/* Send negative responce if PID not supported */  
		SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	}
}
#endif

/*********************************************************************/
/* FUNCTION:     FormJ1979_Mode_43_Data_DCAN                              */
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
#if (XeDCAN_SID_03_Supported == CeDCAN_Supported)
void FormJ1979_Mode_43_Data_DCAN( void )
{
	WORD          DTCCount    = 0;
	BYTE          TrByteCount = CcM3_RETURN_ID_OFFSET ;

	while ( DTCCount < count_DTCs_SID03 ) {
		WrtDCAN_ServiceData(Hi8Of16(DTCs_SID03[DTCCount]),TrByteCount++);
		WrtDCAN_ServiceData(Lo8Of16(DTCs_SID03[DTCCount]),TrByteCount++);
		DTCCount++;
	}
	WrtDCAN_ServiceData( DTCCount, CyM3_M7_NumDTC_Offset);
	SendLnStandardPositiveAnswer (TrByteCount);
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode4Handler_DCAN                                   */
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
#if (XeDCAN_SID_04_Supported == CeDCAN_Supported)
/* no callback need to be set for mode 44 transmit*/
#define J1979_MODE_04_MSG_LENGTH  (1)

void J1979Mode4Handler_DCAN (void)
{
	if (GetLnServiceDataLength() == ( J1979_MODE_04_MSG_LENGTH ) && ( GetVIOS_EngSt_Run())) {
		SendLnStandardNegativeAnswer(CcDCAN_CondNotCorrect_RequestSequenceError);
	} else if (GetLnServiceDataLength() == ( J1979_MODE_04_MSG_LENGTH )) {
		/* It is not required to reply after clearing the DTC's.
		* The DTC's should be cleared within 1 second of sending
		* the response.
		*/
		B_DiagInfoClrReq = true;
		SendLnStandardPositiveAnswer ( RETURN_ID_OFFSET );
		/* imported from CMNDTC module */
	} else {
		SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	}
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode5Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   This mode is to obtain the results of O2 Sensor     */
/*               Monitoring Tests with in the PCM .                  */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_05_Supported == CeDCAN_Supported)

void J1979Mode5Handler_DCAN (void)
{
   TsC2AP_O2Sensor Ls1979_T_Code;

   BYTE    Ly1979_TestID;
   BYTE    Ly1979_O2ID;

   BYTE    Ly1979_MsgIdx;

   Ly1979_MsgIdx  = J1979_ActualDataLoc ;

   Ly1979_TestID  = (GetLnServiceData ())[CyTestIDMode5];
   Ly1979_O2ID    = (GetLnServiceData ())[Cy02IDMode5];

   /*Check if it is in standard diagnostic mode to support service*/
   if(!CheckStandardDiagnosticState())
   {
      SendLnStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
   }
   else
   {
      if ( J1979_MODE_05_MSG_LENGTH == GetLnServiceDataLength())
      {

         WrtDCAN_ServiceData( Ly1979_TestID , Ly1979_MsgIdx++) ;
         WrtDCAN_ServiceData( Ly1979_O2ID   , Ly1979_MsgIdx++) ;

         Ls1979_T_Code = Read_O2Sensor(Ly1979_TestID , Ly1979_O2ID );

         if ( Ls1979_T_Code.LyTestIdFlag )
         {
            if ( OneByteO2Snsr == Ls1979_T_Code.LyRsltSize)
            {
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_One ,
                               Ly1979_MsgIdx++ ) ;

               SendLnStandardPositiveAnswer ( Ly1979_MsgIdx );

            }
            else if ( ThreeByteO2Snsr == Ls1979_T_Code.LyRsltSize)
            {
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_One ,
                               Ly1979_MsgIdx++ ) ;

               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Two ,
                               Ly1979_MsgIdx++ ) ;

               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Three ,
                               Ly1979_MsgIdx++ ) ;

               SendLnStandardPositiveAnswer ( Ly1979_MsgIdx );
            }
            /* Reading and queueing the Cal constant value           */
            else if(FourByteCalConst == Ls1979_T_Code.LyRsltSize)
            {
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_One ,
                               Ly1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Two ,
                               Ly1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Three ,
                               Ly1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Four ,
                               Ly1979_MsgIdx++ ) ;

               SendLnStandardPositiveAnswer ( Ly1979_MsgIdx );
            }
         }
         else
         {
            /* Send negative responce if PID not supported */
            SendLnStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
         }
      }
      else
      {
         /* Send negative responce if PID not supported */
         SendLnStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
      }
   }
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode6Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   This mode is to obtain the results of On board      */
/*               Diagnostic tests by Test ID.                        */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
void J1979Mode6Handler_DCAN (void)
{
   BYTE                LyDCAN_DataIdx ;
   BYTE                LyDCAN_DataIdx_Old ;
   TbBOOLEAN           LbDCAN_MID_Found;
   TbBOOLEAN           LbDCAN_SendResponse;
   TbBOOLEAN           LbDCAN_SuppMID_Requested;
   TbBOOLEAN           LbDCAN_MIDData_Requested;
   BYTE                LyDCAN_MID_Index;
   BYTE                LyDCAN_TID_Index;
   TWO_BYTE_DATA_TYPE  LuDCAN_TestValue;
   FOUR_BYTE_DATA_TYPE LuDCAN_Supp_Range ;
   TWO_BYTE_DATA_TYPE  LuDCAN_Min_Thrsh;
   TWO_BYTE_DATA_TYPE  LuDCAN_Max_Thrsh;
   BYTE                LyDCAN_MsgIdx ;
   BYTE                LaDCAN_ServiceData[CcDCAN_MODE6_MAX_MSG_LENGTH] ;

   LbDCAN_MID_Found         = CbFALSE;
   LbDCAN_SendResponse      = CbFALSE;
   LyDCAN_MID_Index         = 0;
   LyDCAN_MsgIdx            = CcDCAN_MODE6_DataOffset;
   LbDCAN_SuppMID_Requested = CbFALSE;
   LbDCAN_MIDData_Requested = CbFALSE;

   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      /* check for message validity */
      /* length should contain at least one MID */
      if (( GetLnServiceDataLength () >= CcDCAN_MODE6_MIN_MSG_LENGTH )
         && ( GetLnServiceDataLength () <= CcDCAN_MODE6_MAX_MSG_LENGTH ))
      {
         for(LyDCAN_DataIdx = CcDCAN_MODE6_DataOffset;
             LyDCAN_DataIdx < GetLnServiceDataLength (); LyDCAN_DataIdx++)
         {
            LaDCAN_ServiceData[LyDCAN_DataIdx] = (GetLnServiceData ())[LyDCAN_DataIdx];
         }

         for(LyDCAN_DataIdx = CcDCAN_MODE6_DataOffset;
             LyDCAN_DataIdx < GetLnServiceDataLength (); LyDCAN_DataIdx++)
         {
            VyDCAN_1979_RequestedMID = LaDCAN_ServiceData[LyDCAN_DataIdx];
            /* The do-while loop below is repeatedly executed until either find */
            /* matching MID Index or get to last index.                         */

            /* Write request MID Number to Transmit Buffer */
            WrtDCAN_ServiceData( VyDCAN_1979_RequestedMID ,
                                  LyDCAN_MsgIdx++ ) ;

            LyDCAN_DataIdx_Old = LyDCAN_MsgIdx;

            if( (!LbDCAN_MIDData_Requested)
              && ( (CeDCAN_MID_00 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_20 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_40 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_60 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_80 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_A0 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_C0 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_E0 == VyDCAN_1979_RequestedMID) ) )
            {
               LbDCAN_SuppMID_Requested = CbTRUE;
               LuDCAN_Supp_Range = PrfmDCAN_MID_SuppRange();
               if(LuDCAN_Supp_Range.DWord_Access != V_COUNT_LONG(0))
               {
                  WrtDCAN_ServiceData( LuDCAN_Supp_Range.Byte_Access.Byte_One ,
                                        LyDCAN_MsgIdx++ ) ;

                  WrtDCAN_ServiceData( LuDCAN_Supp_Range.Byte_Access.Byte_Two ,
                                        LyDCAN_MsgIdx++ ) ;

                  WrtDCAN_ServiceData( LuDCAN_Supp_Range.Byte_Access.Byte_Three ,
                                        LyDCAN_MsgIdx++ ) ;

                  WrtDCAN_ServiceData( LuDCAN_Supp_Range.Byte_Access.Byte_Four ,
                                        LyDCAN_MsgIdx++ ) ;
               }
            }
            else if( (!LbDCAN_SuppMID_Requested)
                    && (GetLnServiceDataLength () == CcDCAN_MODE6_MIN_MSG_LENGTH) )
            {
               do
               {
                  if (  GetDCAN_MIDNumber( LyDCAN_MID_Index ) ==
                        VyDCAN_1979_RequestedMID )
                  {
                     LbDCAN_MID_Found = CbTRUE;
                     break ;
                  }
                  LyDCAN_MID_Index++ ;
               }  while ( LyDCAN_MID_Index <= GetDCAN_NumberOfMIDs() );

               if(LbDCAN_MID_Found)
               {
                  LyDCAN_TID_Index    = 0;

                  while(LyDCAN_TID_Index < GetDCAN_Num_Of_TIDs(LyDCAN_MID_Index))
                  {
                     WrtDCAN_ServiceData( GetDCAN_TID_Num(LyDCAN_MID_Index, LyDCAN_TID_Index),
                               LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( GetDCAN_TID_ScalingID(LyDCAN_MID_Index, LyDCAN_TID_Index),
                               LyDCAN_MsgIdx++ ) ;

                     DtrmnDCAN_M6_Data(&LuDCAN_TestValue,
                                       &LuDCAN_Min_Thrsh,
                                       &LuDCAN_Max_Thrsh,
                                       LyDCAN_MID_Index,
                                       LyDCAN_TID_Index);

                     WrtDCAN_ServiceData( LuDCAN_TestValue.Byte_Access.Byte_One ,
                                    LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_TestValue.Byte_Access.Byte_Two ,
                                    LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_Min_Thrsh.Byte_Access.Byte_One ,
                                    LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_Min_Thrsh.Byte_Access.Byte_Two ,
                                    LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_Max_Thrsh.Byte_Access.Byte_One ,
                                  LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_Max_Thrsh.Byte_Access.Byte_Two ,
                                LyDCAN_MsgIdx++ ) ;

                     LyDCAN_TID_Index++;

                     if(LyDCAN_TID_Index < GetDCAN_Num_Of_TIDs(LyDCAN_MID_Index))
                     {
                        /* Write request MID Number to Transmit Buffer */
                        WrtDCAN_ServiceData( VyDCAN_1979_RequestedMID ,
                                              LyDCAN_MsgIdx++ ) ;
                     }
                  } /*End of while */
               } /* if(LbDCAN_MID_Found) */
               else
               {
                  /* Do nothing */
               }
            }
            else
            {
               /* Do not suppport MID supported and MID data in the same message */
               LbDCAN_SendResponse = CbFALSE;
               break;
            }

            if(LyDCAN_DataIdx_Old != LyDCAN_MsgIdx)
            {
               LbDCAN_SendResponse = CbTRUE;
            }
            else
            {
               /* Buffer not filled with MID data for some reason */
               LyDCAN_MsgIdx--;
            }
         } /* End of For loop */

         if(LbDCAN_SendResponse)
         {
            SendLnStandardPositiveAnswer ( LyDCAN_MsgIdx  );
         }
         else
         {
            /* Do not send any response if invalid message received */
            PfrmDCAN_AckReqWithoutResponse ();
         }
      }
      else
      {
         /* Do not send any response if invalid message received */
         PfrmDCAN_AckReqWithoutResponse ();
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse ();
   }
}

/*********************************************************************/
/* FUNCTION:    DtrmnDCAN_M6_Data()                                  */
/*                                                                   */
/* Type:        static                                               */
/*                                                                   */
/* DESCRIPTION: Builds the bit encoded value of supported MIDs       */
/*                                                                   */
/* PARAMETERS:  TWO_BYTE_DATA_TYPE                                   */
/*              TWO_BYTE_DATA_TYPE                                   */
/*              TWO_BYTE_DATA_TYPE                                   */
/*              BYTE                                                 */
/*              BYTE                                                 */
/*                                                                   */
/* RETURN:      NONE                                                 */
/*                                                                   */
/* Global Variables Updated: None                                    */
/*********************************************************************/
static void DtrmnDCAN_M6_Data(TWO_BYTE_DATA_TYPE *LpDCAN_Test_Value,
                              TWO_BYTE_DATA_TYPE *LpDCAN_Min_Thrsh,
                              TWO_BYTE_DATA_TYPE *LpDCAN_Max_Thrsh,
                              BYTE               LyDCAN_MID_Index,
                              BYTE               LyDCAN_TID_Index)
{
   TbBOOLEAN LbDCAN_TestReportingEnabled = CbFALSE;
   TeDGDM_DIAGNOSTIC_TESTS    LeDCAN_DTC_ID;

   LeDCAN_DTC_ID = GetDCAN_DTC_ID(LyDCAN_MID_Index,LyDCAN_TID_Index);

   if ( CeDGDM_Misfire == LeDCAN_DTC_ID )
   {
      if ( DtrmnMISF_CAN_TestReportingEnabled() )
      {
         LbDCAN_TestReportingEnabled = CbTRUE;
      }
   }
   else if ( ( CeDGDM_NoFault == LeDCAN_DTC_ID )
          || ( ( CeDGDM_FAULT_TYPE_Z != GetDGDM_DTC_FaultType(LeDCAN_DTC_ID) )
            && ( GetDGDM_TestCompletedSnceCdClr(LeDCAN_DTC_ID) ) ) )
   {
     LbDCAN_TestReportingEnabled = CbTRUE;
   }

   if ( LbDCAN_TestReportingEnabled )
   {
      GetDCAN_Param_Value(LyDCAN_MID_Index, LyDCAN_TID_Index,
                          &LpDCAN_Test_Value->Word_Access);
      GetDCAN_Param_Min_Value(LyDCAN_MID_Index, LyDCAN_TID_Index,
                          &LpDCAN_Min_Thrsh->Word_Access);
      GetDCAN_Param_Max_Value(LyDCAN_MID_Index, LyDCAN_TID_Index,
                          &LpDCAN_Max_Thrsh->Word_Access);
   }
   else
   {
      LpDCAN_Test_Value->Word_Access = V_COUNT_WORD(0);
      LpDCAN_Min_Thrsh->Word_Access = V_COUNT_WORD(0);
      LpDCAN_Max_Thrsh->Word_Access = V_COUNT_WORD(0);
   }
}

/*********************************************************************/
/* FUNCTION:    PrfmDCAN_MID_SuppRange()                             */
/*                                                                   */
/* Type:        static                                               */
/*                                                                   */
/* DESCRIPTION: Builds the bit encoded value of supported MIDs       */
/*                                                                   */
/* PARAMETERS:  TeDCAN_TID_List                                      */
/*                                                                   */
/* RETURN:      TsDCAN_SID06_MID                                     */
/*                                                                   */
/* Global Variables Updated: None                                    */
/*********************************************************************/
static FOUR_BYTE_DATA_TYPE PrfmDCAN_MID_SuppRange(void)
{
   FOUR_BYTE_DATA_TYPE LuDCAN_TestValue ;
   T_COUNT_BYTE        LyDCAN_MID_NumBitsToShift ;
   T_COUNT_BYTE        LyDCAN_MID_RangeToCheck ;
   T_COUNT_BYTE        LyDCAN_MID_TableIdx;

   LuDCAN_TestValue.DWord_Access = V_COUNT_LONG(0);
   LyDCAN_MID_NumBitsToShift = V_COUNT_BYTE(0);
   LyDCAN_MID_RangeToCheck = V_COUNT_BYTE(0);

   if(CeDCAN_MID_00 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_20;
   }
   else if(CeDCAN_MID_20 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_40;
   }
   else if(CeDCAN_MID_40 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_60;
   }
   else if(CeDCAN_MID_60 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_80;
   }
   else if(CeDCAN_MID_80 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_A0;
   }
   else if(CeDCAN_MID_A0 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_C0;
   }
   else if(CeDCAN_MID_C0 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_E0;
   }
   else if(CeDCAN_MID_E0 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_FF;
   }
   else
   {
      /* Do nothing */
   }
   for(LyDCAN_MID_TableIdx = 0;LyDCAN_MID_TableIdx < CyDCAN_NumOf_MIDs;
       LyDCAN_MID_TableIdx++)
   {
      if((CaDCAN_Supported_MIDs[LyDCAN_MID_TableIdx].f_MID_Number > GetDCAN_1979_RequestedMID())
        && (CaDCAN_Supported_MIDs[LyDCAN_MID_TableIdx].f_MID_Number <= LyDCAN_MID_RangeToCheck))
      {
         LyDCAN_MID_NumBitsToShift =
            usSUB_us_usp((usSUB_us_usp(CaDCAN_Supported_MIDs[LyDCAN_MID_TableIdx].f_MID_Number,
                                       GetDCAN_1979_RequestedMID(),
                                       S_COUNT_BYTE,
                                       S_COUNT_BYTE,
                                       S_COUNT_BYTE)),
                          V_COUNT_BYTE(1),
                          S_COUNT_BYTE,
                          S_COUNT_BYTE,
                          S_COUNT_BYTE);

         LuDCAN_TestValue.DWord_Access |=
                 (CcDCAN_1979_SuppMID_BitMask >> LyDCAN_MID_NumBitsToShift);
      }
   }
   return(LuDCAN_TestValue);
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode7Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Handles the initial request to transmit emission    */
/*               related fault codes.  The message length must be 4  */
/*               and there must NOT be a mode 7 already in process.  */
/*               If valid faults exist ,then a message is queued and */
/*               a callback is generated to stuff the codes in the   */
/*               message.                                            */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: None                                    */
/*********************************************************************/
/* mode 47 transmit callback is set                                  */
#if (XeDCAN_SID_07_Supported == CeDCAN_Supported)
#define J1979_MODE_07_MSG_LENGTH   (1)
#define J1979_Mode_47_DTC_Length   (7)

void J1979Mode7Handler_DCAN (void)
{
	if ( J1979_MODE_07_MSG_LENGTH == GetLnServiceDataLength() ) {
		/*  WrtMultiRespInProgress( CbTRUE  ) ; */
		FormJ1979_Mode_47_Data_DCAN ();
	} else {
		/* Send negative responce if message length not valid. */
		SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
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
/* Global Variables Updated: None                                    */
/*********************************************************************/
#define CcM7_RETURN_ID_OFFSET      (2)
void FormJ1979_Mode_47_Data_DCAN( void )
{
	WORD    DTCCount1 = 0;
	BYTE    TrByteCount = CcM7_RETURN_ID_OFFSET;

	while ( DTCCount1 < count_DTCs_SID07 ) {
		WrtDCAN_ServiceData(Hi8Of16(DTCs_SID07[DTCCount1]),TrByteCount++);
		WrtDCAN_ServiceData(Lo8Of16(DTCs_SID07[DTCCount1]),TrByteCount++);
		DTCCount1++;
	}

	WrtDCAN_ServiceData( DTCCount1, CyM3_M7_NumDTC_Offset);
	SendLnStandardPositiveAnswer (TrByteCount);
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode8Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   This mode is to request the mode 08 Test ID's       */
/*               which are supported                                 */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_08_Supported == CeDCAN_Supported)

void J1979Mode8Handler_DCAN( void )
{
   BYTE    Li1979_MsgIdx;
   BYTE    Li1979_CalIdx;
   BYTE    LyFlag;
   BYTE    Ly1979_TestRange_TestID ;

   /*Check if it is in standard diagnostic mode to support service*/
   if(!CheckStandardDiagnosticState())
   {
      SendLnStandardNegativeAnswer(
                            CcDCAN_SubFuncNotSupp_InvalidFormat );
   }
   else
   {
      Refresh1979_Mode8_SystemLeakTest_DCAN( );

      /* Do message verification and validation */
      if ( Ky1979_MODE_08_MSG_LENGTH  ==
                              GetLnServiceDataLength())
      {
         Ly1979_TestRange_TestID = (GetLnServiceData ())[CyTestID_OR_Range];
         Li1979_MsgIdx = 1 ;
         LyFlag = CbFALSE;

         WrtDCAN_ServiceData( Ly1979_TestRange_TestID , Li1979_MsgIdx++ ) ;

         if(( CyMode8Test_01 == Ly1979_TestRange_TestID )  &&
              Is1979Mode8TestIDSupp_DCAN( Ly1979_TestRange_TestID ))
         {
            /* Engine is not running                                   */
            if ( ( !Get_EngineTurning())
                 &&  !GetEVPD_TankProtectionMode() )
 /*              &&  ( GetEVPD_TankProtectionMode() == CbFALSE ) ) */
            {
               VbOFVC_DeviceControlActive = 1;
               Se1979Mode8TestID_01_Status = CeMode8TestIDEnabled;
               SetOFVC_DiagEvapVentVlvOvrd (CeFORCE_CLOSED);
               SetOFVC_CCP_SD_OvrdValue (V_PERCENTa(0));

               /* No reject reason */
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               /* Pad the message with Zeros                         */
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;

               LyFlag = CbTRUE; /* Message can be queued            */
            }
            else
            {
               Se1979Mode8TestID_01_Status = CeMode8TestIDEnabled;
               if(Get_EngineTurning())
               {
                  WrtDCAN_ServiceData( 0x2 , Li1979_MsgIdx++ ) ;
               }
               else if (GetEVPD_TankProtectionMode())
               {
                  WrtDCAN_ServiceData( 0x1 , Li1979_MsgIdx++ ) ;
               }
               else
               {
                  /* Send postive respond */
                  WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               }
               /* Pad the message with Zeros            */
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               SendLnStandardPositiveAnswer( Li1979_MsgIdx );
            }
         }
         /* If TestRange is Zero  */
         else if ( Cy1979_Mode_08_TestRange_0 == Ly1979_TestRange_TestID)
         {
            WrtDCAN_ServiceData( 0 , Li1979_MsgIdx++ ) ;
            for (Li1979_CalIdx = Cy1979_InitVal;
               Li1979_CalIdx < Cy1979_Mode_08_IndexLim;
               Li1979_CalIdx++)
            {
             /* Calibration Constant containing the TestID supported */
              WrtDCAN_ServiceData(  Ka1979_M8_TID_Supported[Li1979_CalIdx] ,
                                                     Li1979_MsgIdx++ ) ;

             /* Check for data has been calculated for a valid supported */
             /* Test Range.If no test range is supported,send a negative */
             /* response. */
              if (Cy1979_InitVal !=
                                Ka1979_M8_TID_Supported[Li1979_CalIdx])
              {
                 LyFlag = CbTRUE;
              }
            }
            if(!LyFlag)
            {
              SendLnStandardNegativeAnswer(
                              CcDCAN_SubFuncNotSupp_InvalidFormat);
            }
         }
         else
         {
            SendLnStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
         }

         if(CbTRUE == LyFlag)
         {
            SendLnStandardPositiveAnswer( Li1979_MsgIdx );
         }
      }
      else
      {
         /* Send negative responce if Test ID not supported */
         SendLnStandardNegativeAnswer(
                              CcDCAN_SubFuncNotSupp_InvalidFormat);
      }
   }
   SendLnStandardNegativeAnswer( CcDCAN_ServiceNotSupported ) ;
}

/*********************************************************************/
/* FUNCTION:     Is1979Mode8TestIDSupp_DCAN                               */
/*                                                                   */
/* Type:         Static                                              */
/*                                                                   */
/* DESCRIPTION:  This function returns True of False depending on the*/
/*               support or non-support of the test Id's for Mode 8  */
/*                                                                   */
/* PARAMETERS:   Test ID                                             */
/*                                                                   */
/* RETURN:       TbBOOLEAN                                           */
/*                                                                   */
/* Global Variables Updated:None                                     */
/*********************************************************************/
static TbBOOLEAN Is1979Mode8TestIDSupp_DCAN(BYTE LyTestID)
{
   TbBOOLEAN LyFlag;
   BYTE      LyTempBuff;

   LyFlag = CbFALSE;
   if(CyMode8Test_01 == LyTestID)
   {
      LyTempBuff =  Ka1979_M8_TID_Supported[0];

      /* Evaporative system leak test supported ( TestID 0x01 )     */
      if(LyTempBuff & CySetBit7)
      {
         LyFlag = CbTRUE;
      }
   }
   return LyFlag;
}

/*********************************************************************/
/* FUNCTION:     fresh1979_Mode8_SystemLeakTest                      */
/*                                                                   */
/* Type:         Global                                              */
/*                                                                   */
/* DESCRIPTION:  Refresh function for the Evaporative system leak    */
/*               test. Called in the kw2 executive                   */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: ViC2GL_CurrentMsg, Va1979_M49_Data      */
/*********************************************************************/
static void Refresh1979_Mode8_SystemLeakTest_DCAN( void )
{
   /* Engine is  running                                             */
   if((Get_EngineTurning())
       && (CeMode8TestIDEnabled == Se1979Mode8TestID_01_Status))
   {
      Se1979Mode8TestID_01_Status = CeMode8TestIDDisabled;
   }
}
#endif

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
#if (XeDCAN_SID_09_Supported == CeDCAN_Supported)
#define J1979_MODE_09_INFO_LENGTH      (2)

void J1979Mode9Handler_DCAN( void )
{
	BYTE Li1979_DataIdx,Ly1979_MsgIdx,LyMultiMode,LyFound;

	Vi1979_Mode09_MsgIdx = 0;
	Vi1979_Mode09_CalIdx = 0;
	Vi1979_Mode09_CalCharIdx = 0;
	Vi1979_Mode09_CurrMsgIdx = 0;
	Li1979_DataIdx = CyInfoType ;
	LyMultiMode  = 0 ;
	LyFound  = 0;

	if ( GetLnServiceDataLength() == J1979_MODE_09_MSG_LENGTH ) {
		Vy1979_InfoType =  (GetLnServiceData())[1];
		WrtDCAN_ServiceData( Vy1979_InfoType , Li1979_DataIdx++ );
		LyFound = CbTRUE ;

		switch(Vy1979_InfoType) {
		case Cy1979_InfoType0:
			WrtDCAN_ServiceData( Cy1979_InfoType0_MsgCnt , Li1979_DataIdx++ ) ;
			/*support infotype 02, 04, 06*/
			WrtDCAN_ServiceData( 0xF3 , Li1979_DataIdx++ ) ;
			WrtDCAN_ServiceData( 0x00 , Li1979_DataIdx++ ) ;
			WrtDCAN_ServiceData( 0x00, Li1979_DataIdx++ ) ;
			WrtDCAN_ServiceData( 0x00 , Li1979_DataIdx++ ) ;
			break;

		case Cy1979_InfoType1:
			WrtDCAN_ServiceData( Cy1979_NumOfMsgsToRptVIN , Li1979_DataIdx++ );
			break;

		case Cy1979_InfoType2:
			Vi1979_Mode09_MsgIdx = Cy1979_NumOfMsgsToRptVIN;
			WrtDCAN_ServiceData(++Vi1979_Mode09_CurrMsgIdx   ,Li1979_DataIdx++) ;
			WrtDCAN_ServiceData( 0 , Li1979_DataIdx++);
			WrtDCAN_ServiceData( 0 , Li1979_DataIdx++);
			WrtDCAN_ServiceData( 0 , Li1979_DataIdx++);
			WrtDCAN_ServiceData( scnVehInfo.VIN[ Vi1979_Mode09_CalCharIdx++ ], Li1979_DataIdx++ );
			LyMultiMode = CbTRUE ;
			break;

		case Cy1979_InfoType3:
			WrtDCAN_ServiceData(Cy1979_NumOfMsgsToRptCalID,Li1979_DataIdx++);
			break;

		case Cy1979_InfoType4:
			Vi1979_Mode09_MsgIdx = (Cy1979_NumOfMsgsToRptCalID );
			WrtDCAN_ServiceData( ++Vi1979_Mode09_CurrMsgIdx,  Li1979_DataIdx++);
			WrtDCAN_ServiceData( scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++],Li1979_DataIdx++ );
			WrtDCAN_ServiceData( scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++],Li1979_DataIdx++ );
			WrtDCAN_ServiceData( scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++],Li1979_DataIdx++ );
			WrtDCAN_ServiceData( scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++],Li1979_DataIdx++ );
			LyMultiMode = CbTRUE ;
			break;

		case Cy1979_InfoType7:
			WrtDCAN_ServiceData(Cy1979_NumOfMsgsToRptIUPR,Li1979_DataIdx++);
			break;

		case Cy1979_InfoType8:
			Vi1979_Mode09_MsgIdx = (Cy1979_NumOfMsgsToRptIUPR);
			WrtDCAN_ServiceData(++Vi1979_Mode09_CurrMsgIdx,  Li1979_DataIdx++);
			WrtDCAN_ServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++);
			WrtDCAN_ServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++);
			WrtDCAN_ServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++);
			WrtDCAN_ServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++);
			LyMultiMode = CbTRUE ;
			break;

		default: 
			/* Send negative responce if PID not supported */
			LyFound = CbFALSE ;                 
			break;
		}

		if(( LyMultiMode ) && ( Vi1979_Mode09_CurrMsgIdx < Vi1979_Mode09_MsgIdx ) && ( LyFound != CbFALSE )) {
			WrtDCANMultiRespInProgress( CbTRUE  ) ;
			if(Li1979_DataIdx > 0)
				SendLnStandardPositiveAnswer( Li1979_DataIdx );
		} else if ( LyFound != CbFALSE ) {
			SendLnStandardPositiveAnswer( Li1979_DataIdx );
		} else {
			SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
		}
	} else {
		/* Send negative responce if PID not supported */
		SendLnStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	}
}


/*********************************************************************/
/* FUNCTION:     FormJ1979_NextMode49_DCAN                                */
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
#define HexZero            0
#define Cy1979_InitVal     0

void FormJ1979_NextMode49_DCAN( void )
{
	BYTE Ly1979_InfoType ;
	BYTE Li1979_DataIdx ;
	BYTE Ly1979_MsgIdx ;
	/* TbBOOLEAN Lb1979_Mode9_ID_6_Done = CbFALSE; */

	if( ( Vi1979_Mode09_MsgIdx > Cy1979_InitVal ) && (Vi1979_Mode09_CurrMsgIdx < Vi1979_Mode09_MsgIdx))
	{
		Li1979_DataIdx = Cy1979_Mode09_MsgNumLoc;
		WrtDCAN_ServiceData( Vy1979_InfoType , Li1979_DataIdx++ );
		WrtDCAN_ServiceData( ++Vi1979_Mode09_CurrMsgIdx, Li1979_DataIdx++ );

		switch (Vy1979_InfoType) {
		case Cy1979_InfoType2:
			for( Ly1979_MsgIdx = 0; Ly1979_MsgIdx < Cy1979_PerRespMaxChar; Ly1979_MsgIdx++ ) {
				WrtDCAN_ServiceData( scnVehInfo.VIN[ Vi1979_Mode09_CalCharIdx++ ], Li1979_DataIdx++ );
			}
			break;

		case Cy1979_InfoType4:
			for( Ly1979_MsgIdx = 0; Ly1979_MsgIdx < Cy1979_PerRespMaxChar; Ly1979_MsgIdx++ ) {
				WrtDCAN_ServiceData(scnVehInfo.CALID[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++ );
			}
			break;

		case Cy1979_InfoType8:
			for( Ly1979_MsgIdx = 0; Ly1979_MsgIdx < Cy1979_PerRespMaxChar; Ly1979_MsgIdx++ ) {
				WrtDCAN_ServiceData(scnVehInfo.IUPR[Vi1979_Mode09_CalCharIdx++], Li1979_DataIdx++ );
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
		WrtDCANMultiRespInProgress( CbFALSE );
	}

	if( Vi1979_Mode09_CurrMsgIdx >= Vi1979_Mode09_MsgIdx ) {
		WrtDCANMultiRespInProgress( CbFALSE ) ;
		SendLnStandardPositiveAnswer( Li1979_DataIdx );
	} else {
		SendLnStandardPositiveAnswer( Li1979_DataIdx );
	}
}

#endif
/*********************************************************************/
/* FUNCTION:     J1979ModeAHandler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Handles the initial request to transmit permanent   */
/*               fault codes.  The pupose of this service is to      */
/*               enable the external tester to obtain all DTCs with  */
/*               Permanent DTC status. These DTCs thatare confirmed  */
/*               and are retained in the non-volatile memory of the  */
/*               server until the appropriate monitor for each DTC   */
/*               has determined that the malfunction is no longer    */
/*               present and is not commanding the MIL on.           */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_0A_Supported == CeDCAN_Supported)
#define J1979_MODE_0A_MSG_LENGTH   (1)
#define J1979_Mode_4A_DTC_Length   (7)
#define CcMA_RETURN_ID_OFFSET      (2)

void J1979ModeAHandler (void)
{
   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      /* Test for valid  message length */
      if (( J1979_MODE_0A_MSG_LENGTH ) ==
                           GetLnServiceDataLength() )
      {
         FormJ1979_Mode_4A_Data ();
      }
      else
      {
         /* Do not send a response if request invalid */
         PfrmDCAN_AckReqWithoutResponse();
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse();
   }
}

/*********************************************************************/
/* FUNCTION:     FormJ1979_Mode_4A_Data                              */
/*                                                                   */
/* Type:         local                                               */
/*                                                                   */
/* DESCRIPTION:  Invoked by Mode_0A handler as well as Queue1979_Next*/
/*               Mode4A procedure, this function finds out and forms */
/*               the data block for the mode 4A response.            */
/*               As long as valid fault codes exist, this procedure  */
/*               will continue to queue new messages.  When no more  */
/*               faults exist, the remaining bytes of the CAN        */
/*               message are padded with 0s.                         */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/*********************************************************************/
void FormJ1979_Mode_4A_Data( void )
{
    BYTE                 LcPermnNDTCCount ;
    BYTE                 TrByteCount ;
    DTC_STATUS_INFO_TYPE DTCRecord;
    WORD                 ReadDTCFaultCode;

    TrByteCount = CcMA_RETURN_ID_OFFSET ;
    LcPermnNDTCCount = V_COUNT_BYTE(0);

    while ( ( GetCMN_PD_PermNDTCArray( LcPermnNDTCCount ) != 0 )
             && (LcPermnNDTCCount < GetCMN_PD_NumOfEEpromDTCs() ) )
    {
       ReadDTCFaultCode = GetCMNDTCP_Code (GetCMN_PD_PermNDTCArray( LcPermnNDTCCount ));
       DTCRecord.DTC_Number.Word_Access = ReadDTCFaultCode;
          WrtDCAN_ServiceData(DTCRecord.DTC_Number.Byte_Access.Byte_One,
                         TrByteCount++);
          WrtDCAN_ServiceData(DTCRecord.DTC_Number.Byte_Access.Byte_Two,
                         TrByteCount++);
       LcPermnNDTCCount++;
    }
    WrtDCAN_ServiceData( LcPermnNDTCCount, CyModeA_NumDTC_Offset);
    SendLnStandardPositiveAnswer (TrByteCount);
}
#endif


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
******************************************************************************/

#ifndef DCANLEGI_H
#define DCANLEGI_H
/******************************************************************************
 *
 * Filename:          dcanlegi.h
 *
 * Description:       Create interface variables for Keyword J1979 message
 *                    handling
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2005-2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 * Current Module Info:
 * %full_name:     mt20u2#1/incl/dcanlegi.h/1 %
 * %date_created:  Tue Sep  7 14:57:08 2010 %
 * %version:       1 %
 * %derived_by:    pz0vmh %
 *
 *****************************************************************************/
/******************************************************************************
 *  System Include Files
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
//#include "obdsfexi.h"
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/

#include "dcanpcfg.h"
#include "kw2app.h"
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/

/*********************************************************************/
/*            GLOBAL CONSTANT DECLARATIONS                           */
/*********************************************************************/

//extern const BYTE Ka1979_M8_TID_Supported[];
//extern const BYTE Ka1979_M5_TestRange_00Thru80[];

#define Cy1979_Mode09  0x09
#define DCAN_GetHighByte(x) ((x) >> 8)

/*******************************************************************
* Response Code For Legisted CANOBD                                                   *
*******************************************************************/
#define CcDCAN_SubFuncNotSupp_InvalidFormat         (0x12)
#define CcDCAN_ReqCorrectlyRecvd_ResponsePending    (0x78)
#define CcDCAN_CondNotCorrect_RequestSequenceError  (0x22)
#define CcDCAN_ServiceNotSupported                  (0x11)
#define CcDCAN_None                                 (0x00)

/*Not used*/
#define CcDCAN_GeneralReject                        (0x10)
#define CcDCAN_RequestOutOfRange                    (0x31)
#define CcDCAN_AccessDenied_SecurityAccessRequested (0x33)
#define CcDCAN_InvalidKey                           (0x35)
#define CcDCAN_ExceedNumberOfAttempts               (0x36)
#define CcDCAN_RequiredTimeDelayNotExpired          (0x37)
#define CcDCAN_DownloadNotAccepted                  (0x40)
#define CcDCAN_CanNotDownloadToSpecifiedAddress     (0x42)
#define CcDCAN_CanNotDownloadNumOfBytesRequested    (0x43)
#define CcDCAN_UploadNotAccepted                    (0x50)
#define CcDCAN_CanNotUploadfromSpecifiedAddress     (0x52)
#define CcDCAN_CanNotUploadNumberOfBytesRequested   (0x53)
#define CcDCAN_IllegalByteCountInBlockTransfer      (0x75)
#define CcDCAN_IncorrectByteCntDuringBlckTransfer   (0x79)
#define CcDCAN_ServiceNotSuppInActiveDiagMode       (0x80)
/*end*/



/*********************************************************************/
/*          GLOBAL Variable Declarations                             */
/*********************************************************************/
#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
extern BYTE   VyDCAN_1979_RequestedMID;
#endif

//extern TbBOOLEAN VbDCAN_NRC78hexInProgress;
/*********************************************************************/
/***  Get NRC 0x78 in Progress flag                                ***/
/*********************************************************************/
//#define GetDCANMultiRespInProgress()  (VbDCAN_NRC78hexInProgress)

/*********************************************************************/
/***  Set NRC 0x78 in Progress flag                                ***/
/*********************************************************************/
//#define WrtDCANMultiRespInProgress(x)\
  //            (VbDCAN_NRC78hexInProgress = (x))

//extern TbBOOLEAN VbDCAN_SendNRC78hexResponse;
/*********************************************************************/
/***  Get NRC 0x78 Send flag                                       ***/
/*********************************************************************/
//#define GetDCAN_Send_Next_78Response()  (VbDCAN_SendNRC78hexResponse)

/*********************************************************************/
/***  Set NRC 0x78 Send flag                                       ***/
/*********************************************************************/
//#define SetDCAN_Send_Next_78Response(x)\
  //            (VbDCAN_SendNRC78hexResponse = (x))

/*********************************************************************/
/*          GLOBAL FUNCTION PROTOTYPES                               */
/*********************************************************************/
extern void DefineOSTK_EmptyFunction(void);
//void WrtDCAN_ServiceData( BYTE in_data, BYTE in_location );

#if (XeDCAN_SID_01_Supported == CeDCAN_Supported)
void J1979Mode1Handler_DCAN (void);
#else
#define J1979Mode1Handler_DCAN               ServiceNotSupported
#endif

#if (XeDCAN_SID_02_Supported == CeDCAN_Supported)
void J1979Mode2Handler_DCAN (void);
#else
#define J1979Mode2Handler_DCAN               ServiceNotSupported
#endif

#if (XeDCAN_SID_03_Supported == CeDCAN_Supported)
void J1979Mode3Handler_DCAN (void);
void FormJ1979_Mode_43_Data_DCAN (void);
#else
#define J1979Mode3Handler_DCAN               ServiceNotSupported
#define FormJ1979_Mode_43_Data_DCAN          DefineOSTK_EmptyFunction
#endif

#if (XeDCAN_SID_04_Supported == CeDCAN_Supported)
void J1979Mode4Handler_DCAN (void);
#else
#define J1979Mode4Handler_DCAN               ServiceNotSupported
#endif

#if (XeDCAN_SID_05_Supported == CeDCAN_Supported)
void J1979Mode5Handler_DCAN (void);
#else
#define J1979Mode5Handler_DCAN               ServiceNotSupported
#endif

#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
void J1979Mode6Handler_DCAN (void);

#define GetDCAN_1979_RequestedMID()  VyDCAN_1979_RequestedMID
#else
#define J1979Mode6Handler_DCAN            ServiceNotSupported
#define GetDCAN_1979_RequestedMID()  (V_COUNT_BYTE(0))
#endif

#if (XeDCAN_SID_07_Supported == CeDCAN_Supported)
void J1979Mode7Handler_DCAN (void);
void FormJ1979_Mode_47_Data_DCAN (void);
#else
#define J1979Mode7Handler_DCAN               ServiceNotSupported
#define FormJ1979_Mode_47_Data_DCAN          DefineOSTK_EmptyFunction
#endif

#if (XeDCAN_SID_08_Supported == CeDCAN_Supported)
void J1979Mode8Handler_DCAN (void);
#else
#define J1979Mode8Handler_DCAN               ServiceNotSupported
#endif

#if (XeDCAN_SID_09_Supported == CeDCAN_Supported)
void J1979Mode9Handler_DCAN (void);
void FormJ1979_NextMode49_DCAN(void);
#else
#define J1979Mode9Handler_DCAN               ServiceNotSupported
#define FormJ1979_NextMode49_DCAN            DefineOSTK_EmptyFunction
#endif

#if (XeDCAN_SID_0A_Supported == CeDCAN_Supported)
void J1979ModeAHandler (void);
void FormJ1979_Mode_4A_Data (void);
#else
#define J1979ModeAHandler               ServiceNotSupported
#define FormJ1979_Mode_4A_Data          DefineOSTK_EmptyFunction
#endif

#if (XeDCAN_SID_0B_Supported == CeDCAN_Supported)
void J1979ModeBHandler (void);
#else
#define J1979ModeBHandler               ServiceNotSupported
#endif

#if (XeDCAN_SID_0C_Supported == CeDCAN_Supported)
void J1979ModeCHandler (void);
#else
#define J1979ModeCHandler               ServiceNotSupported
#endif

#if (XeDCAN_SID_0D_Supported == CeDCAN_Supported)
void J1979ModeDHandler (void);
#else
#define J1979ModeDHandler               ServiceNotSupported
#endif

#if (XeDCAN_SID_0E_Supported == CeDCAN_Supported)
void J1979ModeEHandler (void);
#else
#define J1979ModeEHandler               ServiceNotSupported
#endif

#if (XeDCAN_SID_0F_Supported == CeDCAN_Supported)
void J1979ModeFHandler (void);
#else
#define J1979ModeFHandler               ServiceNotSupported
#endif

#endif /* DCANLEGI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.01  11 Aug 97 TLP       Added ifndef,source/rev,changelog,compile
*                           check
* 1.1   03-23-98  CDW       Created from Lansing 2000 code SCR05083645
* 1.1   10-15-98  cdw       New version created from Daewoo delivery
* 1.5   11-15-98  cdw       Fixed and reduce function code
* 1.6   02-10-98  cdw       Fixed and reduce function code
* 1.7   10-04-99  HFU       Removed TestID 06 in SID06 in Daewoo
*                           Project.
* 1.8   03-31-00  bdt       Removed SID08 from T-150 project.
* 1.9   05-24-00  hfu       Removed SID 06, TestID_07, CompID_4C
*                           in Ga
*                           Application from T150.. 
* 1.10  04-16-03  ban  2648 Modified TeC2AP_Mode5_SupportedTstIDs to
*                           match CARB requirements
* tci_pt3#1.1.6
*       031021    ban  3074 Deleted unused extern declaration
*                           for VbModeDiagClearEvent
*                               Vb1979_ALDL_ModeDiagClearEvent
* tci_pt3#1.1.7
*       031114    ban  3312 Modified #define Cy1979_NumOfMsgsToRptCVNs
* tci_pt3#1.1.8
*       040422    ban  3932 Renamed CeTestID_04CompID_60 and
*                           CeTestID_04CompID_70 to
*                           CeTestID_04CompID_E0 and
*                           CeTestID_04CompID_F0 respectively.
* tci_pt3#1.1.9
*       041011 ban 4534 Renamed CeTestID_0ACompID_03 to
*                       CeTestID_0ACompID_83
* tcb_p1#2.0   ksr -BM- Merged 'j1979.h-tcb_pt1#1.1.9' with
*                        'j1979.h-tci_pt3#1.1.9'.
* tci_pt3#2.1
*       041124 ban 4674 Added Test IDs 70,71 and 81 in
*                       TeC2AP_Mode5_SupportedTstIDs
* 2.0   051130 tln 5311 Added info types Cy1979_InfoTypeA0,
*                      Cy1979_InfoTypeC0, Cy1979_InfoTypeE0 for SID 09
* tcb_pt1#3
*       060313 hdb 5378 Add USID conversions for service bay $06
*                        messages.  Add CeDCAN_SCID_20
* tci_pt3#3.1.1
*       070521 mtc 6316 Removed KW2K Purge & Vent Valve Override Status
*                       References.
* tci_pt3#4
*       070305 AB  6191 Added support for Service 0x09 Infotype 0x0A
*                       Ecu Name ( ECM or PCM ).
* tcb_pt1#4.1.1
*       070612 hdb 6262 Added CeDCAN_SCID_0E, CeDCAN_TID_BA, ..BB,
*                              ..BC, ..BD.
* tcb_pt1#6
*       070616 hdb 6262 merge tcb_pt1#5 and tcb_pt1#4.1.1
* tcb_pt1#4.1.2
*       070618 me  6394 Removed CeDCAN_TID_BD = 0xBD
* tcb_pt1#7
*       070618 me  xxxx Merged tcb_pt1#4.1.2 with tcb_pt1#6
* tcb_pt1#8
*       071108 hdb 6618 New Phaser Response / Error monitors for SID $06
* tcb_pt1#8.1.1
*       071216 me  6755 Added CeDCAN_TID_BD = 0xBD
* tcb_pt1#8.3.1
*       080115 me  6754 Added CyModeA_NumDTC_Offset
*                       Added function prototype for the services 0xA to 0x0F.
* 8.1.2
*       080404 VP  6833 Added CeDCAN_MID_31,CeDCAN_SCID_FD,CeDCAN_TID_91.
* tcb_pt1#8.1.3
*       080611 mt  -BM- Merged 'dcancarb.h~8.1.2' with 'dcancarb.h~tcb_pt1#8.3.1'.
* tcb_pt1#8.1.4
*       080909 me  7212 Added Mode9 IT08 RM Add Secondary O2 Results
*
* 3.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 paltform.
******************************************************************************/

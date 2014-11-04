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
 * %full_name:     ctc_pt3#1/incl/dcanlegi.h/2 %
 * %date_created:  Fri Apr  1 14:51:32 2011 %
 * %version:       2 %
 * %derived_by:    hzpcqq %
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

extern TbBOOLEAN VbDCAN_NRC78hexInProgress;
/*********************************************************************/
/***  Get NRC 0x78 in Progress flag                                ***/
/*********************************************************************/
#define GetDCANMultiRespInProgress()  (VbDCAN_NRC78hexInProgress)

/*********************************************************************/
/***  Set NRC 0x78 in Progress flag                                ***/
/*********************************************************************/
#define WrtDCANMultiRespInProgress(x)\
              (VbDCAN_NRC78hexInProgress = (x))

extern TbBOOLEAN VbDCAN_SendNRC78hexResponse;
/*********************************************************************/
/***  Get NRC 0x78 Send flag                                       ***/
/*********************************************************************/
#define GetDCAN_Send_Next_78Response()  (VbDCAN_SendNRC78hexResponse)

/*********************************************************************/
/***  Set NRC 0x78 Send flag                                       ***/
/*********************************************************************/
#define SetDCAN_Send_Next_78Response(x)\
              (VbDCAN_SendNRC78hexResponse = (x))

/*********************************************************************/
/*          GLOBAL FUNCTION PROTOTYPES                               */
/*********************************************************************/
extern void DefineOSTK_EmptyFunction(void);
//void WrtDCAN_ServiceData( BYTE in_data, BYTE in_location );

#if (XeDCAN_SID_01_Supported == CeDCAN_Supported)
void J1979Mode1Handler_DCAN (void);
#else
#define J1979Mode1Handler_DCAN               ServiceNotSupported_DCAN
#endif

#if (XeDCAN_SID_02_Supported == CeDCAN_Supported)
void J1979Mode2Handler_DCAN (void);
#else
#define J1979Mode2Handler_DCAN               ServiceNotSupported_DCAN
#endif

#if (XeDCAN_SID_03_Supported == CeDCAN_Supported)
void J1979Mode3Handler_DCAN (void);
void FormJ1979_Mode_43_Data_DCAN (void);
#else
#define J1979Mode3Handler_DCAN               ServiceNotSupported_DCAN
#define FormJ1979_Mode_43_Data_DCAN          DefineOSTK_EmptyFunction

#endif

#if (XeDCAN_SID_04_Supported == CeDCAN_Supported)
void J1979Mode4Handler_DCAN (void);
#else
#define J1979Mode4Handler_DCAN               ServiceNotSupported_DCAN
#endif

#if (XeDCAN_SID_05_Supported == CeDCAN_Supported)
void J1979Mode5Handler_DCAN (void);
#else
#define J1979Mode5Handler_DCAN               ServiceNotSupported_DCAN
#endif

#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
void J1979Mode6Handler_DCAN (void);

#define GetDCAN_1979_RequestedMID()  VyDCAN_1979_RequestedMID
#else
#define J1979Mode6Handler_DCAN            ServiceNotSupported_DCAN
#define GetDCAN_1979_RequestedMID()  (V_COUNT_BYTE(0))
#endif

#if (XeDCAN_SID_07_Supported == CeDCAN_Supported)
void J1979Mode7Handler_DCAN (void);
void FormJ1979_Mode_47_Data_DCAN (void);
#else
#define J1979Mode7Handler_DCAN               ServiceNotSupported_DCAN
#define FormJ1979_Mode_47_Data_DCAN          DefineOSTK_EmptyFunction
#endif

#if (XeDCAN_SID_08_Supported == CeDCAN_Supported)
void J1979Mode8Handler_DCAN (void);
#else
#define J1979Mode8Handler_DCAN               ServiceNotSupported_DCAN
#endif

#if (XeDCAN_SID_09_Supported == CeDCAN_Supported)
void J1979Mode9Handler_DCAN (void);
void FormJ1979_NextMode49_DCAN(void);
#else
#define J1979Mode9Handler_DCAN               ServiceNotSupported_DCAN
#define FormJ1979_NextMode49_DCAN            DefineOSTK_EmptyFunction
#endif

#if (XeDCAN_SID_0A_Supported == CeDCAN_Supported)
void J1979ModeAHandler (void);
#else

#define J1979ModeAHandler               ServiceNotSupported_DCAN

#endif

#endif /* DCANLEGI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0  110402 cjqq       Base on GMLAN project
*
******************************************************************************/

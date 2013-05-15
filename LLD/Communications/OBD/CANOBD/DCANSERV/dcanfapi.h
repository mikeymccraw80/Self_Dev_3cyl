#ifndef DCANFAPI_H
#define DCANFAPI_H
/******************************************************************************
 *
 * Filename:          dcanfapi.h
 *
 * Description: This modules contains the all user interface constants and inline functions.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    SendStandardNegativeAnswer
 *                    SendStandardPositiveAnswer
 *                    DCAN_AnswerStillBeingSent
 *                    WrtDCAN_ServiceData
 *                    GetWrtbufferAddr
 *                    GetDCAN_ApplicationLevelServicePending
 *                    GetCommunicationEstablishedState
 *                    GetDCAN_RespPending_Sent
 *                    SetDCAN_RespPending_Sent
 *                    GetDCAN_ServiceId
 *
 * Forward Engine Management Systems
 *
 * Copyright 2001-2009, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#1/incl/dcanfapi.h/1 %
 * %date_created:  Tue Sep  7 14:58:04 2010 %
 * %version:       1 %
 * %derived_by:    pz0vmh %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Subsystem Include Files
 *****************************************************************************/

/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/

/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#if(XeSYST_CANOBD_SrvsEnable == CeSYST_AVAILABLE)
#include "dcantran.h"
/*********************************************************************/
/*** Load a data to a location of  the transmit data buffer        ***/
/*********************************************************************/
#define DCAN_GetServiceData()               ((uint8_t*)  &LnServiceDataFrame.Data[0])
FAR_COS void PostOFVC_LnResponseToRequest (void);
bool DCAN_GetCommunicationActiveState( void );
//FAR_COS uint8_t *DCAN_GetServiceData( void );
void DCAN_SendStandardPositiveAnswer (register uint16_t MsgSize);
void DCAN_SendStandardNegativeAnswer( uint8_t NegativeResponseCode );
TbBOOLEAN DCAN_AnswerStillBeingSent( void );
FAR_COS void KW2KCAN_Received_Message(Can8DataBytesArrayType Can8DataBytesArrayPtr);

#else

#define PostOFVC_LnResponseToRequest         DefineOSTK_EmptyFunction

#define DCAN_AnswerStillBeingSent  CbFALSE

INLINE void DCAN_SendStandardPositiveAnswer (register uint16_t MsgSize)
{
   Parameter_Not_Used( MsgSize);
}

INLINE void DCAN_SendStandardNegativeAnswer( uint8_t NegativeResponseCode )
{
   Parameter_Not_Used(NegativeResponseCode);	
}

INLINE bool DCAN_GetCommunicationActiveState( void )
{
   return ( false );
}

INLINE  uint8_t *DCAN_GetServiceData( void )
{
   return ( 0x00 );
}
#endif

#endif /* DCANFAPI_H */
/***********************************************************************
* Change Log:
*
* Rev.    Date   User RSM# Description of Changes
* ----  -------  ---- ---- -------------------------------------------*
* tci_pt3#4
*        041027  ban  4600 Added SetNext78ResponseToBeSent() and
*                          GetNext78ResponseToBeSent()
* tci_pt3#3
*        070503  AB   xxxx Changed MultiRespInProgress and
*                          Send_Next_78Response flags to service
*                          SID 0x09 from DCANCORE with the modified
*                          DCAN transport layer in MT80 T255 .
* 2     090122 me  7637 Modified CANOBD APIs' names.
* 3.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 paltform.
*
***********************************************************************/

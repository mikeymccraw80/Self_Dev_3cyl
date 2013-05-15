#ifndef DCANPCFG_H
#define DCANPCFG_H
/******************************************************************************
 *
 * Filename:          dcanpcfg.h
 *
 * Description:       This is the config file which contains all the default
 *                    parameters and conversions required by the OBD CAN
 *                    transport protocol
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
 * Copyright 1997-2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#43/incl/dcanpcfg.h/1 %
 * %date_created:  Tue Sep  7 14:55:18 2010 %
 * %version:       1 %
 * %derived_by:    pz0vmh %
 *
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
#include "timepcvc.h" /*for TwTIME_t_R7p8125ms*/
/***************************************************************
* Start of configuration settings for application layer        *
***************************************************************/

/******************************************************************
* "APPLICATION LAYER" Service Id Supported/Not Supported status   *
* NOTE : SIDs $01 - $09 should always be supported for CARB       *
* applications                                                    *
******************************************************************/
#define CeDCAN_NotSupported                (0)
#define CeDCAN_Supported                   (1)

#define XeDCAN_SID_00_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_01_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_02_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_03_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_04_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_05_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_06_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_07_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_08_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_09_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_0A_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_0B_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_0C_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_0D_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_0E_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_0F_Supported             (CeDCAN_NotSupported)


/***************************************************************
* End of configuration settings for application layer          *
***************************************************************/

#endif
/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* tci_pt3#1
*       050916 ban xxxx Created Module
*       051003 tln xxxx Added constants for S3 timer
* 2     051208 ban 5311 Added compiler switches for SIDs 28 and 29
* 2     070629 abh 6023 modified as per GMW3110
* 2.1.1 080131 me  6754 Added support for service 0x0A
* 3.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 paltform.
******************************************************************************/


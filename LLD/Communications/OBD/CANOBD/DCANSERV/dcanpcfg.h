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
 * %full_name:     ctc_pt3#6/incl/dcanpcfg.h/2 %
 * %date_created:  Fri Apr  1 14:51:45 2011 %
 * %version:       2 %
 * %derived_by:    hzpcqq %
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

/***************************************************************
* Start of configuration settings for application layer        *
***************************************************************/

/******************************************************************
* "APPLICATION LAYER" Service Id Supported/Not Supported status   *
* NOTE : SIDs $01 - $09 should always be supported for applications *
******************************************************************/
#define CeDCAN_NotSupported                (0)
#define CeDCAN_Supported                   (1)

#define XeDCAN_SID_01_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_02_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_03_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_04_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_05_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_06_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_07_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_08_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_09_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_0A_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_10_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_11_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_14_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_19_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_22_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_23_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_27_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_2A_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_2E_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_2F_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_31_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_3E_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_85_Supported             (CeDCAN_Supported)
#define XeDCAN_SID_28_Supported             (CeDCAN_NotSupported)
#define XeDCAN_SID_B0_Supported             (CeDCAN_NotSupported)
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
*1.0      110401 cjqq base on T300 GMLAN Module
******************************************************************************/


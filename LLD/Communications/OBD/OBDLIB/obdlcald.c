/******************************************************************************
 *
 * Filename:          obdlcald.c
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
 * Copyright 9999-The system cannot accept the date entered.Enter the new date: (mm-dd-yy) , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     ctc_pt3#1/csrc/obdlcald.c/3 %
 * %date_created:  Tue Jul  1 13:15:28 2014 %
 * %version:       3 %
 * %derived_by:    mzh1qz %
 *
 *****************************************************************************/
/*                                                                   */
/* FILE NAME: obdlcald.c                                             */
/*                                                                   */
/* DESCRIPTION: This file contains the ofvc calibration constants    */
/*                                                                   */
/* LIST OF FUNCTIONS: NIL                                            */
/*********************************************************************/

/*********************************************************************/
/*            INCLUDE FILES                                          */
/*********************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/

/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlcald.h"


/* ==========================================================================
 * Calibration declarations for CAN
 * ==========================================================================*/

/*
*| obdlcald {
*|
*|  .t_service_security_access_type
*|  {
*|   :kind = enumeration;
*|   :enumerators = (
*|      CeService_SecurityAccessUnused,
*|      CeService_SecurityAccessUsed
*|      );
*|   :type = uint8;
*| }
*|  .ann_Security_Access_Used_SID
*|  {
*|      :kind = define_annotation;
*|      :units = "Service_ID";
*|      :table = ("ServiceID_2E", "ServiceID_2F") ;
*|  }
*|
*|}
*/

/*
*| obdlcald.{
*| KbDCANCORE_MODE4_With_EngRUN {
*|     : is_calconst;
*|     : description = "If KbDCANCORE_MODE4_With_EngRUN = True, then "
*|                     "Mode-0x04 Code Clear in Engine State = Run. "
*|                     "If KbDCANCORE_MODE4_With_EngRUN = False, Mode-0x04 "
*|                     "Code Clear is not allowed in Engine State = Run. "
*|                     "Mode-0x04 Code Clear is always allowed when Engine "
*|                     "State <> Run.";
*|     : type = types.size2_0to1;
*|     : units = "boolean";
*|   }
*| }
*/
const TbBOOLEAN   KbDCANCORE_MODE4_With_EngRUN = CbFALSE;

/*
*| obdlcald.{
*| KeDCANOBD_Security_Algorithm {
*|     : is_calconst;
*|     : description =" This calibration indicate Mode-0x27 support which cunstomer's"
*|                    " Security Algorithm.";
*|     : units = "enum";
*|   }
*| }
*/
const TeSID27_SeedKeyType   KeDCANOBD_Security_Algorithm = CeDelphi_Generic_Static;

/*
*| obdlcald.{
*|    KwDCANOBD_CANID {
*|     : is_calconst;
*|     : description ="Additional CAN OBD Function address ID for specific customer. "
*|                          "0x0 is disabling the additional ID; 0x600 is for GW CHK application";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|    }
*| }
*/
const  T_COUNT_WORD   KwDCANOBD_CANID = V_COUNT_WORD(0);

/*
*| obdlcald.{
*|   KgSYST_DELPHI_END_MODEL_NR {
*|     : is_calconst;
*|     : description =" It'll be updated when end model release "
*| "and the MFG will store the first end model number. ";
*|     : type = types.t_count_long;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_LONG KgSYST_DELPHI_END_MODEL_NR = 0x00UL;

/*
*| obdlcald.{
*| KeDCANOBD_Applictaion {
*|     : is_calconst;
*|     : description = "This calibration indicate which custom use the CANOBD, "
*|     " 0 = CeDCANOBD_default; 1= CeDCANOBD_CHK011_MT92; 2=CeDCANOBD_JAC_MT92.";
*|     : units = "enum";
*|   }
*| }
*/
const TeDCANOBD_Applictaion_Type   KeDCANOBD_Applictaion = CeDCANOBD_default;

/*
*| obdlcald.{
*|  KaDCANOBD_SecurityAccessUsedService {
*|     : is_calconst;
*|     : description = "specify Service ID $2E & 2F if these SID need unlock  the security access "
*| "CeService_SecurityAccessUnused: don't need security access."
*| "CeService_SecurityAccessUsed:  need security access.";
*|     : elements:type = obdlcald.t_service_security_access_type;
*|     : annotation = obdlcald.ann_Security_Access_Used_SID;
*|     : elements:units = "Service_ID";
*|  }
*| }
*/
const TeService_SecurityAccess_Type  KaDCANOBD_SecurityAccessUsedService[CcSecurityAccessUsedServiceID] =
{
   CeService_SecurityAccessUnused,
   CeService_SecurityAccessUnused
};

/*
*| obdlcald.{
*|  KfDCAN_t_SecurityAccessDelayTime {
*|     : is_calconst;
*|     : description ="Set the lockout timer for security access in initial function.";
*|     : type = types.t_w_R7p8125ms;
*|     : units = "seconds";
*|   }
*| }
*/
const TwTIME_t_R7p8125ms  KfDCAN_t_SecurityAccessDelayTime = C_R7p8125ms16(2.0) ;

/*
*| obdlcald.{
*|   KySYST_BTC_NR {
*|     : is_calconst;
*|     : description =" This is the BTC code, it'll be updated when end model release "
*| "Engineering Range: any hex value; enter the ASCII code for any values "
*| "which must appear as  ASCII in the keyword mode 09 ID 04 message "
*| "Resolution: na ";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_BYTE  KySYST_BTC_NR[] =
        { 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30 };

/*
*| obdlcald.{
*|   KyCOMM_VehMfgSparePartNumber {
*|     : is_calconst;
*|     : description =" This value shall be used to reference the "
*| " vehicle manufacturer spare part number. "
*| "Value To Calibrate Out: not applicable "
*| "Engineering Range: any hex value; enter the ASCII code for any values. "
*| "Resolution: na ";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_BYTE  KyCOMM_VehMfgSparePartNumber[CcCOMM_VehMfgSparePartNumber] =
        { 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
          0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30 };

/*
*| obdlcald.{
*|   KyCOMM_SysSupplierDataIdentifier {
*|     : is_calconst;
*|     : description =" This value shall be used to reference the "
*| " system supplier name and address information. "
*| "Value To Calibrate Out: not applicable "
*| "Engineering Range: any hex value; enter the ASCII code for any values. "
*| "Resolution: na ";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_BYTE  KyCOMM_SysSupplierDataIdentifier[CcCOMM_SysSupplierDataIdentifier] =
        { 0x30, 0x30, 0x30, 0x30, 0x30,
          0x30, 0x30, 0x30,
          0x30, 0x30
        };

#if defined(OBD_CONTROLLER_IS_MT92) || defined(OBD_CONTROLLER_IS_MT22P3)
/*
*| obdlcald.{
*|   KaDCAN_Matrix_VersionLevel {
*|     : is_calconst;
*|     : description ="ECU Communication Matrix Version Level";
*|     : type  = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_BYTE  KaDCAN_Matrix_VersionLevel[CcDCAN_Matrix_VersionLevel] = 
        { 0x30, 0x30, 0x30, 0x30, 0x30,
          0x30, 0x30, 0x30,
          0x30, 0x30
        };
#endif

#if defined(OBD_CONTROLLER_IS_MT22P3)
/*
*| obdlcald.{
*|   KaDCAN_NM_VersionLevel {
*|     : is_calconst;
*|     : description ="ECU Network Management Version Level";
*|     : type  = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_BYTE  KaDCAN_NM_VersionLevel[CcDCAN_NM_VersionLevel] = { 0x30, 0x30 };

/*
*| obdlcald.{
*|   KaDCAN_DiagProtocol_VersionLevel {
*|     : is_calconst;
*|     : description ="ECU Diagnostic Protocol Version Level";
*|     : type  = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_BYTE  KaDCAN_DiagProtocol_VersionLevel[CcDCAN_DiagProtocol_VersionLevel] = { 0x30, 0x30 };

/*
*| obdlcald.{
*|   KaDCAN_CommSpec_VersionLevel {
*|     : is_calconst;
*|     : description ="Communication SpecVersionLevel";
*|     : type  = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_BYTE  KaDCAN_CommSpec_VersionLevel[CcDCAN_CommSpec_VersionLevel] = { 0x30, 0x30 };

#endif /* #if defined(OBD_CONTROLLER_IS_MT22P3) */

/*
*| obdlcald.{
*|   KbDCAN_VIN_UpdateOnce {
*|     : is_calconst;
*|     : description ="VIN Update Only Once, Once this calibration is set to" 
*|"true Security access and Flag in EEprom will be checked for vin update feasibility.";
*|     : type = types.size2_0to1;
*|     : units = "boolean";
*|   }
*| }
*/
const TbBOOLEAN  KbDCAN_VIN_UpdateOnce = CbFALSE;


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
******************************************************************************/

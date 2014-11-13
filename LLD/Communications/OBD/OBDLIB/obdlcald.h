#ifndef obdlcald_H
#define obdlcald_H
/*********************************************************************/
/*                                                                   */
/* FILE NAME: obdlcald.h                                             */
/*                                                                   */
/* DESCRIPTION: This file contains the extern ofvc cal declarations  */
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
#include "io_type.h"
#include "obdltype.h"
#include "t_gentypes.h"
#include "timepcvc.h"

/*********************************************************************/
/*            EQUATES                                                */
/*********************************************************************/

/*********************************************************************/
/*            TYPEDEFS AND STRUCTURE DECLARATIONS                    */
/*********************************************************************/
/**********************************************************************
* Following Definition of enumerations and Cals moved from ofvccald.h
***********************************************************************/
typedef enum
{
  CeDelphi_Generic_Static = 0x00
#ifdef COMPILE_SID27_GWM_CHK011
  ,CeGWM_CHK011 = 0x01
#endif
#ifdef COMPILE_SID27_JAC_SII
  ,CeJAC_SII = 0x02
#endif
  //,CeBAIC_CANOBD = 0x03//reversed for BAIC
  //,CeGWM_H5 = 0x04//reversed for GWM
  /* For Algorithm which is coded in external device read SA Index from PML*/
  ,CePML_2Sd4Key = 0x80
  ,CePML_4Sd4Key = 0x81
  /*Delphi Generic Algorithm */
  //,CeCustomer_Generic_Four_Bytes = 0x82//reversed for Customer_Generic
} TeSID27_SeedKeyType;

typedef enum
{
  CeService_SecurityAccessUnused,
  CeService_SecurityAccessUsed
} TeService_SecurityAccess_Type;

typedef enum
{
   /* Note: forward gear positions to be listed 1st */
   CeServiceID_2E,
   CeServiceID_2F,
   CcSecurityAccessUsedServiceID
} TeSecurityAccessUsedServiceID;

typedef enum TeDCAN_CalEEPROMDATAS
{
  CeDCAN_EEPROM_DATA1,             /* 00 */
  CeDCAN_EEPROM_DATA2,             /* 01 */
  CeDCAN_EEPROM_DATA3,             /* 03 */
  CeDCAN_EEPROM_DATA4,             /* 04 */
  CeDCAN_EEPROM_DATA5,             /* 05 */
  CeDCAN_EEPROM_DATA6,             /* 06 */
  CeDCAN_EEPROM_DATA7,             /* 07 */
  CeDCAN_EEPROM_DATA8,             /* 08 */
  CeDCAN_EEPROM_DATA9,             /* 09 */
  CeDCAN_EEPROM_DATA10,             /* 10 */
  CcDCAN_NumberOfCalEEPROM_DATA
} TeDCAN_CalEEPROM_DATA;

typedef enum
{
  CeSupport_None,
  CeSupport_22_2E,            
  CeSupport_22             
} TeDCANMethod;

typedef struct TsDCAN_CalEEPROM_Tag
{
	WORD KwDCAN_DID_Number;
	BYTE KfDCAN_Data_Length;
	BYTE KfDCAN_Data_Address_Offset;
	TeDCANMethod KeDCAN_Data_SupportMethod;
}TsDCAN_CalEEPROM_T;

#define CcCOMM_VehMfgSparePartNumber          (16)
#define CcCOMM_SysSupplierDataIdentifier      (10)
#ifdef OBD_CONTROLLER_IS_MT22P3
#define CcDCAN_NM_VersionLevel                (2)
#define CcDCAN_DiagProtocol_VersionLevel      (2)
#define CcDCAN_CommSpec_VersionLevel          (2)
extern const T_COUNT_BYTE                  KaDCAN_NM_VersionLevel[];
extern const T_COUNT_BYTE                  KaDCAN_DiagProtocol_VersionLevel[];
extern const T_COUNT_BYTE                  KaDCAN_CommSpec_VersionLevel[];
#endif
extern const TbBOOLEAN                     KbDCAN_VIN_UpdateOnce;
extern const T_COUNT_BYTE                  KyCOMM_VehMfgSparePartNumber[];
extern const T_COUNT_BYTE                  KyCOMM_SysSupplierDataIdentifier[];
extern const TbBOOLEAN                     KbDCANCORE_MODE4_With_EngRUN;
extern const TeSID27_SeedKeyType           KeDCANOBD_Security_Algorithm;
extern const T_COUNT_WORD                  KwDCANOBD_CANID;
extern const TeDCANOBD_Applictaion_Type    KeDCANOBD_Applictaion;
extern const TeService_SecurityAccess_Type KaDCANOBD_SecurityAccessUsedService[];
extern const TwTIME_t_R7p8125ms            KfDCAN_t_SecurityAccessDelayTime;
extern const TsDCAN_CalEEPROM_T            KaDCAN_CalEEPROM_Data[CcDCAN_NumberOfCalEEPROM_DATA];
extern const T_COUNT_BYTE                  KySYST_BTC_NR[];
extern const T_COUNT_LONG                  KgSYST_DELPHI_END_MODEL_NR;

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0   120330 cjqq xxxx create a new version for canobd
* 2.0   121017 xll  xxxx added cal KwDCANOBD_CANID
* 3.0   121022 xll  xxxx added cal KgSYST_DELPHI_END_MODEL_NR.
* 4.0   121213 xll  VIR#1022 added cal KeDCANOBD_Applictaion and type TeDCANOBD_Applictaion_Type.
* 5.0   130118 xll  RCR#1036 added cal KaDCANOBD_SecurityAccessUsedService,
*                            type TeSecurityAccessUsedServiceID and TeService_SecurityAccess_Type.
* 6.0   130614 xll  SCR#1153 Added cal KbDCAN1979_InfoType8_20Items_Supported
* 7.0   130628 xll  SCR#1168 Added cal KySYST_BTC_NR
* 8.0   130725 xll  SCR#1169 Modified TeSID27_SeedKeyType and TeDCANOBD_Applictaion_Type.
* 9.0   130830 xll  RCR#1239 Moved TeDCANOBD_Applictaion_Type to obdltype.h
*                            Added TeDCAN_CalEEPROM_DATA,TeDCANMethod, TsDCAN_CalEEPROM_T.
*                            Added KaDCAN_CalEEPROM_Data.
* 11.0  140317 Aaron RSM#8292 Add the KaDCAN_Matrix_VersionLevel,KaDCAN_NM_VersionLevel,
*                           KaDCAN_DiagProtocol_VersionLevel,KaDCAN_CommSpec_VersionLevel
* 12.0  140423 Aaron RSM#8314 Add the KbDCAN_VIN_UpdateOnce and KbDCAN_KW_3BSecurityAccessEnable
*                          to support update vin once.
* 13    140522 xll -BM- Compile out KbDCAN_KW_3BSecurityAccessEnable for MT92.
* 13.1.1 140529 cxg SCR_1634 Added CAL0ADDR for KgSYST_DELPHI_END_MODEL_NR, KySYST_BTC_NR and KaDCAN_CalEEPROM_Data
* 13.1.2.1.1 140618 lj rsm8342 Modify CcCOMM_VehMfgSparePartNumber to 16
* 14    140617 Aaron Move KbDCAN_KW_3BSecurityAccessEnable and KbDCAN_J1979_xInfoType8_20Items_Supported to kw2kcald.c                  
* 3     140701 xll   SCR1581 Modified TeSID27_SeedKeyType
* 4     140701 xll   RSM#8300 Added CcDCAN_Matrix_VersionLevel and modified KaDCAN_Matrix_VersionLevel
******************************************************************************/


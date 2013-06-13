#ifndef OBDLFSRV_H 
#define OBDLFSRV_H
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
* Filename     : obdlfsrv.h                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents      Implementation of Diagnostic Services                 *
*                Recommended Practice  Vers. 1.1   1-31-97             *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 38.  This service is used by the client to    *
*                start a routine in server's memory.                   *
*                                                                      *
* $Source: ems_project@brigh...:daewoo_2002:obdlserv.h $              *
* $Revision$                                                     *
* $Author: brighton.tcb:/users/s..._2002_MathLib:safayyad $           *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   12-10-98  IAJ     Initial file creation                        *
* 1.2   12-23-98  IAJ     Changed the .c file.                         *
* 1.3   01-11-99  IAJ     Chnaged the header.                          *
* 1.4   06-15-99  IAJ     Added inline procedures and extern           *
*                         declarations.                                *
************************************************************************
* Functions in this file:                                              *
*         KwJ14230StartRoutineByAddress                                *
***********************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/

/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdltype.h"/*ECUProgrammingSessionState*/
//#include "cmndtc.h"/*ECUProgrammingSessionState*/
#include "kw2api.h"


#define Cy1979FrameReqZero       (0)
#define J1979_MODE_02_MIN_MSG_LENGTH (3)
#define J1979_MODE_02_MAX_MSG_LENGTH (7)
#define CyMode2_DataOffset           (1)

#define J1979_MODE_03_MSG_LENGTH   (1)
#define J1979_Mode_43_DTC_Length   (7)
#define RETURN_ID_OFFSET           (1)

#define J1979_MODE_04_MSG_LENGTH  (1)

#define J1979_ActualDataLoc       (1)
#define J1979_MODE_05_MSG_LENGTH  (3)
#define Cy02IDMode5               (2)
#define CyTestIDMode5             (1)

#define J1979_MODE_06_MSG_LENGTH  (2)
#define CyTestIDMode6             (1)
#define Cy1979_Mode6_CalSixthByte (0xff)
#define CcDCAN_MODE6_DataOffset     (1)
#define CcDCAN_MODE6_MIN_MSG_LENGTH (2)
#define CcDCAN_MODE6_MAX_MSG_LENGTH (7)

#define J1979_MODE_07_MSG_LENGTH   (1)
#define J1979_Mode_47_DTC_Length   (7)

#define Ky1979_MODE_08_MSG_LENGTH  (7)
#define CyTestID_OR_Range         (1)
#define  Cy1979_Mode_08_TestRange_0  0x00
#define  Cy1979_Mode_08_IndexLim     0x04
#define  CyMode8Test_01              0x01

#define J1979_MODE_09_MSG_LENGTH (2)
#define CyInfoType               (1)
#define HexZero     0
#define Cy1979_Mode_09_MaxInfoType   9
#define Cy1979_InfoType0             0
#define Cy1979_InfoType1             1
#define Cy1979_InfoType2             2
#define Cy1979_InfoType3             3
#define Cy1979_InfoType4             4
#define Cy1979_InfoType5             5
#define Cy1979_InfoType6             6
#define Cy1979_InfoType7             7
#define Cy1979_InfoType8             8
#define Cy1979_InfoType0A           0x0A

#define Cy1979_InfoType0_MsgCnt      1
#define Cy1979_InfoType_01_BitPosVal 0x80
#define Cy1979_InfoType_07_BitPosVal 0x02  /* ADDED -- Check value*/
#define Cy1979_NumOfMsgsToRptVIN     5
#define Cy1979_MessageCountIPT       8     /* ADDED */

#define Cy1979_InfoType_02_BitPosVal 0x40
#define Cy1979_InfoType_03_BitPosVal 0x20
#define Cy1979_InfoType_04_BitPosVal 0x10
#define Cy1979_InfoType_05_BitPosVal 0x08
#define Cy1979_InfoType_06_BitPosVal 0x04
#define Cy1979_InfoType_08_BitPosVal 0x01
#define Cy1979_InfoType_0A_BitPosVal 0x40

#define Cy1979_NumOfMsgsToRptCalID   4
//#define Cy1979_NumOfMsgsToRptCVNs    1
#define Cy1979_Mode09_MsgNumLoc      1
#define Cy1979_InfoTypeDataIdx       1
#define Cy1979_PerRespMaxChar        4
#define Chk1979_Md9_InfoTypeSupported(LyVal,LyBit) \
      ( ((LyVal & LyBit) == LyBit) ? CbTRUE:CbFALSE )

#define Cy1979_InitVal               0
#define  CySetBit7                   0x80
#define  CySetBit6                   0x40
#define  CySetBit5                   0x20
#define  CySetBit4                   0x10
#define  CySetBit3                   0x08
#define  CySetBit2                   0x04
#define  CySetBit1                   0x02
#define  CySetBit0                   0x01

#define Cy1979_SuppPIDRange_00_20    0x00
#define Cy1979_SuppPIDRange_20_40    0x20
#define Cy1979_SuppPIDRange_40_60    0x40
#define Cy1979_SuppPIDRange_60_80    0x60
#define Cy1979_SuppPIDRange_80_A0    0x80
#define Cy1979_SuppPIDRange_A0_C0    0xA0
#define Cy1979_SuppPIDRange_C0_E0    0xC0
#define Cy1979_SuppPIDRange_E0_FF    0xE0

#define  CyM3_M7_NumDTC_Offset       (1)
#define  CyModeA_NumDTC_Offset       (1)

/* SID 09 Supported Infotypes */
//#define Cy1979_InfoType20            0x20
#define Cy1979_InfoType40            0x40
#define Cy1979_InfoType60            0x60
#define Cy1979_InfoType80            0x80
#define Cy1979_InfoTypeA0            0xA0
#define Cy1979_InfoTypeC0            0xC0
#define Cy1979_InfoTypeE0            0xE0

#define Cy1979_InfoType_07_BitPosVal 0x02  /* ADDED -- Check value*/
#define Cy1979_NumOfMsgsToRptVIN_DCAN     1     /* 1 Msg only for CAN */
#define Cy1979_MessageCountIPT_DCAN       1     /* 1 Msg only for CAN */

#define Cy1979_Info_02_NumDataItems  1
#define Cy1979_Info_04_NumDataItems  1
#define Cy1979_Info_06_NumDataItems  1
#define Cy1979_Info_08_NumDataItems  16
#define Cy1979_Info_0A_NumDataItems  1

#define Cy1979_NumOfMsgsToRptCalID_DCAN   1    /* 1 Msg only for CAN */

//#define Cy1979_MaxCalIDs             1
//#define Cy1979_MaxCVNIDs             1
//#define Cy1979_Mode09_MaxCalChar     16

//#if XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM
//#define Cy1979_Mode09_MaxCalCharPCM  32
//#define Cy1979_MaxCalIDsPCM          2
//#endif

//#if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) &&\
   // (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
//#define Cy1979_MaxCVNIDsPCM          2
//#endif

/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/
/*****  Supported Record Local Identifier  *****/
#if 0
#define CcRdliSnapShot        (0x01)
#define CcSideRail                       (0x02)
#define CcEndModelPN                     (0x03)
#define CcBaseModelPN                    (0x04)
#define CcBroadcastCode                  (0x05)
/*not used*/
#define CcHyundaiEndModelPN              (0x06)
#define CcHyundaiCalID_PN                (0x07)
/*Not supported in Hyundai*/
#define CcHyundaiEngCalID_PN             (0x08)
/*end*/
#define CcBank1BLMCells                  (0x09)
#define CcCrankShaftAdaptiveCylinder     (0x0A)
#define CcTECDSampleCounter              (0x0B)
#define CcLOCKODO                        (0x0C)
#define CcBank2BLMCells                  (0x0D)
/*not used*/
#define CcVehicleSpdSignalType           (0x11)
#define CcChassisControllerType          (0x12)
#define CcCruiseControlType              (0x13)
#define CcPowerSteeringSensorType        (0x14)
#define CcHyundaiTRNCalID_PN             (0x15)
#define CcImmobilizerType                (0x16)
#define CcImm_VIN_Key                    (0x17)
#define CcImm_Mode                       (0x18)
#define CcImmVehSpecificData             (0x19)
#define CcImmUserPassword                (0x20)
/*end*/
#define CcABSAutoDetectFlag 		    (0x21)
#define CcImmVINHighByte                   (0x22)
#define CcImmVINLowByte                   (0x23)
#define CcImmConfigByte                   (0x24)
#define CcImmLastRandomNumber           (0x25)
#define CcImmPolynomial 				(0x26)
/*not used*/
#define CcImmKeyLearnt                   (0x27)
#define CcImmTransponderFault            (0x28)
#define CcImmEMS_Status                  (0x29)
#define CcImmPasswordStatus              (0x2A)
#define CcImmLockByTimer                 (0x2B)
#define CcImmNumWrongInputs_PW_Teach     (0x2C)
#define CcImmNumWrong_VSD_KeyTeach       (0x2D)
#define CcImmNumWrong_PW_ForLH           (0x2E)
#define CcImmNumWrong_VSD_ForNeutral     (0x2F)
/*end*/

//#define CcSystemNameOrEngineType         (0x97)
#define CcInstrumentationDatasetID       (0x9B)
#define CcManuEnableCounter              (0xA0)
#define CcSW10BytesNameAndFixName        (0xB0)
#define CcMainSoftwareCalID              (0xB1)

#if XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM
#define CcIniFillTmLrn                   (0x40)
#define CcDC_ND12_AppIniLrn              (0x41)
#define CcDC_NR_AppIniLrn                (0x42)
#define CcDC_N1R_LR_HoldLrn              (0x43)
#define CcDC_N2R_LR_HoldLrn              (0x44)
#define CcNS43_IniFillTmLrn              (0x45)
#define CcNS32_IniFillTmLrn              (0x46)
#define CcDC_NS43_AppIniLrn              (0x47)
#define CcDC_NS32_AppIniLrn              (0x48)
#define CcDC_AppLrn12                    (0x49)
#define CcDC_AppLrn23                    (0x4A)
#define CcDC_AppLrn34                    (0x4B)
#define CcOnFillTmLrn12                  (0x4C)
#define CcOnFillTmLrn23                  (0x4D)
#define CcOnFillTmLrn34                  (0x4E)
#define CcRelTmLrn23                     (0x4F)
#define CcRelTmLrn34                     (0x50)
#define CcNVM_LrnTgtRCAftInit            (0x51)
#define CcNVM_LrnTgtRCUseStdVal          (0x52)
#define CcNVM_RC_OccurAftLrnInit         (0x53)
#define CcPwOnHs21FillTmLrn              (0x54)
#define CcPwOnHs32FillTmLrn              (0x55)
#define CcPwOnHs43FillTmLrn              (0x56)
#define CcPwOnHs31FillTmLrn              (0x57)
#define CcPwOnHs42FillTmLrn              (0x58)
#define CcPwOnHsRelDC_Lrned              (0x59)
#define CcPwOnHsRelDC_Lrned1             (0x5A)
#define CcPwOnHsRelDC_Lrned2             (0x5B)
#define CcPwOnHsRelDC_Lrned3             (0x5C)
#if ((XeTRNS_SYST_NUMBER_GEARS == CcTRNS_SYST_5_SPD) || (XeTRNS_SYST_4_5_SPD_CAL == CeSYST_AVAILABLE))
#if XeSYST_KW_NOT_SUPPORTED == CeSYST_FALSE
/*Not supported in Hyundai*/
#define CcPwOnHs54FillTmLrn              (0x5D)
#endif
#define CcNS54_IniFillTmLrn              (0x5E)
#define CcDC_NS54_AppIniLrn              (0x5F)
#define CcDC_AppLrn45                    (0x60)
#define CcOnFillTmLrn45                  (0x61)
#endif
#define CcDC_OfDA_Lrn12                  (0x62)
#define CcDC_OfDA_Lrn23                  (0x63)
#define CcDC_OfDA_Lrn34                  (0x64)
#if ((XeTRNS_SYST_NUMBER_GEARS == CcTRNS_SYST_5_SPD) || (XeTRNS_SYST_4_5_SPD_CAL == CeSYST_AVAILABLE))
#define CcDC_OfDA_Lrn45                  (0x65)
#define CcDC_2ND_SkipPrepRelLrnD5D3      (0x66)
#define CcDC_OD_SkipPrepRelLrnD5D2       (0x67)
#define CcDC_2ND_SemiSkipPrepRelLrnD5D3  (0x68)
#define CcDC_OD_SemiSkipPrepRelLrnD5D2   (0x69)
#endif
#define CcShiftPtRoadTraffCond           (0x6A)
#define CcShiftPtDriverSportIndx         (0x6B)
#define CcAvgSpdIndicator                (0x6C)
#define CcLowSpdDCLrn32                  (0x6D)
#define CcLowSpdDCLrn43                  (0x6E)
#endif

#if XeSYST_CO_ADJUST_OPTION == CeSYST_AVAILABLE
#define CcCO_AjustFactor                 (0xB4)
#define CO_AdjustFactorSize                (2)
#endif

/*********************************************************************
* These constants are ECU Identifier Object list for service 1A and  *
* 3B. Service 1A reads the Identifier data and service 3B writes it. *
* Application can add/delete the Identifier for the specific project.*
*********************************************************************/
#define CcECUIdentificationDataTable                  (0x80)
#define CcECUIdentificationScalingTable               (0x81)
#define CcVehicleIdentificationNumber                 (0x90)
#define CcvehicleManufactureECUHardwareNumber         (0x91)
#define CcsystemSupplierECUHardwareNumber             (0x92)
#define CcsystemSupplierECUHardwareVersionNumber      (0x93)
#define CcsystemSupplierECUSoftwareNumber             (0x94)
#define CcsystemSupplierECUSoftwareVersionNumber      (0x95)/*not used*/
#define CcexhaustRegulationOrTypeApprovalNumber       (0x96)/*not used*/
#define CcSystemNameOrEngineType                      (0x97)
#define CcRepairShopCodeOrTesterSerialNumber          (0x98)
#define CcProgrammingDate                             (0x99)
/*--- ECU Identifier Object list: manufacturer specific (9Ah..9Fh)---*/
#define CcDiagnosticDataIdentifier                    (0x9A)/*not used*/

#define CcSoftwareName                                (0x9B)/*not used*/
#define CcMANUENBNumber                               (0xA0)
#define CcDiagnosticDataID               (0x9A)
#define CcCustomerBaseModelPN            (0x9B)
#define CcCustomerEndModelPN             (0x9C)
#define CcCustomerSoftwarePN              (0x9D)
#define CcCustomerCalPN                       (0x9E)
#define CcCustomerUtilityPN                   (0x9F)
/*--- Special ---*/
#define CcEndOfScalingTable           (0xFF)
#define CcScalingSize                 (42)

/*********************************************************************
* FUNCTION:     GetSrvc12MinPID                                      *
* DESCRIPTION:  get min PID table counter                            *
*                                                                    *
*********************************************************************/
//#define GetMinPIDtableIndex()               (CeDIAG_MIN_PID_INDEX)
/* Service 18, sub-mode definitions */
#define ReqSuppDTCAndStatus         (0x01)
#define ReqIdentDTCAndStatus        (0x00)

          /*** Service 21  and Service 2C*********/
#define DynamicallyDefinedLocalIDMaxVal  0xF3
#define DynamicallyDefinedLocalIDMinVal  0xF0

#define NumberOfDDLIDefined (DynamicallyDefinedLocalIDMaxVal-\
                                   DynamicallyDefinedLocalIDMinVal+1)

#define NumberOfDataElementsInDDLI       42
#endif
#define KW2K_SEED_ADDRESS                 (0x80008114)
#define KW2K_KEY_ADDRESS                  (0x80008116)
#define CgKW2KSideRailAddress             (0x80008100)
#define CgDelphiBaseModelPNAddr           (0x80008118)

#define CpKW2KSideRailAddress_Ptr         (BYTE *) CgKW2KSideRailAddress
#define CpDelphiBaseModelPNAddr_Ptr       (BYTE *) CgDelphiBaseModelPNAddr

/**********End of  Service 21 and Service 2C Definition****************/

/***************** Service 31 *****************************************/
//#define CgKW2K_APP_COM_PATTERN        0x78563412
//#define CgKW2K_AppComPatternAddr      0xD0007FFC
//#define CpKW2K_AppComPatternAddr_Ptr  (LONGWORD *) CgKW2K_AppComPatternAddr

/***********************************************************************
* Local Identifiers for SID 31                                         *
***********************************************************************/
//#define CyKW2K_CopyKernelToRAM          0xFD
//#define CyKW2K_NVM_Reset                     0xAA

//#define GetWrtbufferAddr() (KW2K_GetServiceData())

/***********************End of  Service 31*****************************/
#if 0
/***************** Service 1A and Service 3B **************************/
#define VIN_Size                     (17)/* Defines size of Vin Number Array */
#define VehicleManu_HW_Number_Size    (11)
#define SS_ECU_HW_Number_Size         (20)
//#define SS_ECU_SW_Number_Size         (8)
#define SS_ECU_SW_Version_Number_Size (10)
#define DiagnosticDataID_Size         (2)
#define SystemName_EngineType_Size    (6)
#define RepairShopCode_Size           (10)
#define ProgrammingDate_Size          (4)
#define InstrumentationDatasetID_Size (4)
#define SW10BytesNameAndFixName_Size  (20)
#define SS_ECU_SW_Version_Number_Fixed_Size (10)

/* Special for Service 3B */
#define End_Model_P_N_Size            (4)
#define MANUENB_Size                  (1)
#define CcHyundaiEndModelPartNumSize      (10)
#define CcHyundaiCalIDPartNumSize         (16)
#define CcDCAN_Immob_VIN_Key_Size         (2)

/*not used*/
#define CcImmVehSpecificDataSize      (9)
#define CcImmUserPasswordSize         (2)
#define CcImmKey_1_IDESize            (4)
#define CcImmKey_2_IDESize            (4)
#define CcImmKey_3_IDESize            (4)
#define CcImmKey_4_IDESize            (4)
#define CcImmNoOfLHStartsByTesterSize (1)
#define CcImmNoOfTwiceIgnOnSeqSize    (1)
#define CcImmKeyLearntSize            (1)
#define CcImmTransponderFaultSize     (1)
#define CcImmEMS_StatusSize           (1)
#define CcImmPasswordStatusSize       (1)
#define CcImmLockByTimerSize          (1)
#define CcImmNumWrongInputs_PW_TeachSize  (1)
#define CcImmNumWrong_VSD_KeyTeachSize    (1)
#define CcImmNumWrong_PW_ForLHSize        (1)
#define CcImmNumWrong_VSD_ForNeutralSize  (1)
#define CcVehicleSpdSignalSize            (1)
#define CcChassisControllerSize           (1)
#define CcCruiseControlSize               (1)
#define CcPowerSteeringSensorSize         (1)
#define CcImmobilizerSize                 (1)
#define CcImmobVINKeySize                 (2)
#define CcImmobModeSize                   (1)
/*end*/
#define CcCustomerEndModelPN_Size     (4)
#define CcCustomerBaseModelPN_Size    (4)
#define CcCustomerSoftwarePN_Size      (4)
#define CcCustomerCalibrationPN_Size      (4)
#define CcCustomerUtilityPN_Size           (4)
#define CcODOInformation_Size              (4)
#define CcFILE_CAL_ID_SIZE           16

/* Special for Service 3B */
#define CcEndModelPNumber                             (0x03)
#define CcMANUENBNumber                               (0xA0)
#define CcODOInformation                              (0xDC)
#define CcDelphiImmoSecretKEY                         (0x10)
#define CcSecurityAccessLevel2Key                     (0x20)

#define Cy1979_EngCalIDSize               (8)
#define Cy1979_TrnCalIDSize               (8)

/*****  Supported Record Local Identifier Size *****/
#define CyAfterSalesServiceRecordSize      (7)/*not used*/
#define SideRailSize                       (20)
#define EndModelPNSize                     (4)
#define BaseModelPNSize                    (4)
#define BroadcastCodeSize                  (4)
#define EngineLearnedZeroThrottleSize      (4)/*not used*/
#define IACKeepAlivesSize                  (2)/*not used*/
#define CrankShaftAdaptiveCylinderSize     (16)
#define LOCKODOSize                        (1)
#define TECDSampleCounterSize              (1)
#define ABSAutoDetectFlagSize              (1)
#define ImmVINHighByteSize                 (1)
#define ImmVINLowByteSize                  (1)
#define ImmConfigByteSize                  (1)
#define ImmLastRandomNumberSize            (4)/*not used*/
#define ImmPolynomialSize                  (4)
#define SystemNameOrEngineTypeSize         (6)/*not used*/
#define InstrumentationDatasetIDSize       (4)
#define StaticInstrumentDataSize           (1)

/* Define boundaries for start and end of ram */
#define      CyRAM_SectionStart    (0xD0000000)
#define      CyRAM_SectionEnd      (0xD000DFFC)

#define      CgScratch_RAM_SectionStart    (0xC0000000)
#define      CgScratch_RAM_SectionEnd      (0xC0003FFF)

#define      RAM_START (BYTE *)    CyRAM_SectionStart
#define      RAM_END   (BYTE *)    CyRAM_SectionEnd
#define      CpRAM_Scratch_START (BYTE *)    CgScratch_RAM_SectionStart
#define      CpRAM_Scratch_END   (BYTE *)    CgScratch_RAM_SectionEnd

#define      CyCal_SectionStart    (0xA0020000)
#define      CyCal_SectionEnd      (0xA003FFFF)

#define      CpHWIO_ROM_CalibrationStart   CyCal_SectionStart
#define      CpHWIO_ROM_CalibrationEnd     CyCal_SectionEnd

#define      CyEEPROM_SectionStart    (0xd000d000)
#define      CyEEPROM_SectionEnd      (0xD000DFFC)
#endif
/*********************************************************************/
/*                  GLOBAL VARIABLES DECLARATIONS                    */
/*********************************************************************/
//extern TbBOOLEAN  VbOFVC_Runing_CAN ;
//extern Kw2000DiagStateType  Kw2000DiagSt;
//extern T_COUNT_BYTE *const KW2000_SideRail_Ptr;
//extern T_COUNT_BYTE *const KW2000_DelphiBaseModelPN_Ptr;
//extern TbBOOLEAN  VbECUResetPending ;
//extern uint32_T local_Timer;
//extern BYTE CyServiceRequestTable_Idx ;
//extern BYTE CommunicationStatus ;
//extern TbBOOLEAN Sb1979_EngCVNSent;
//extern BYTE Vy1979_InfoType ;
//extern BYTE VyRequestedFrameNumber;
extern TbBOOLEAN VbCAN_OBD_Enabled;
extern TbBOOLEAN VbKW2K_OBD_Enabled;
//extern BYTE KW2CrankShaftAdaptiveCylinder[];/*CrankShaftAdaptiveCylinderSize*/


/*********************************************************************/
/*                  EXTERN FUNCTION DECLARATIONS                     */
/*********************************************************************/
//FARFUNC TbBOOLEAN CheckProgrammingState(void);
//extern BYTE* GetWrtbufferAddr( void );
//extern FAR_COS void RunKernelOnRam (void );
//void   ServiceNotSupported(void);
extern FAR_COS void   SendStandardNegativeAnswer( BYTE in_code );
extern FAR_COS void   SendStandardPositiveAnswer( BYTE in_msg_size );
//WORD   Get_Security_Seed_Data( void );
//WORD   Get_Key( void );
//void   PerformReset ( void );
//TbBOOLEAN  Address_Is_Validkw( LONGWORD , BYTE );
//TbBOOLEAN  Srv23Address_Is_Validkw( LONGWORD , BYTE );
extern FAR_COS  TbBOOLEAN GetCommunicationEstablishedState( void );
extern FAR_COS  void OBD_ByKW2000( void );
void OBD_ByCAN( void );
//BYTE GetECUIDScalingTable ( BYTE LyIndex  );
//void ResetActuatorsIfActivated (void);
//TbBOOLEAN CheckIfConditionsCorrectToRunInDiagMode ( void );
//TbBOOLEAN IfKeywordLogicIsActive ( void );
//void DoNecessaryActionsBeforeReset ( void );
//TbBOOLEAN IsDevelopmentOrManfModeActive ( void );
FAR_COS void UpdateOBD_Services(void);
FAR_COS void InitAppLvlCommVariables(void);

#endif

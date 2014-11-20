#ifndef DCANSV2E_H
#define DCANSV2E_H
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
* Filename     : dcansv2e.h                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : CANOBD                                *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 10 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This module contains the extern and inline functions  *
*                related to the Keyword 2000 Diagnostic Service 10     *
*                as defined by the above applicable doc.               *
*                                                                      *
* $Source: ems_project@bright...:daewoo_2002:kw2srv10.h $              *
* $Revision: 1.1 $                                                     *
* $Author: brighton.tcb:/users/sa...o_2002_MathLib:safayyad $          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   11-16-98  JZha    Initial file creation                        *
* 1.4   01-25-99  JZha    Standardized this file.                      *
* 1.5   10-07-99  IAJ     Chnaged the callback function name in the    *
*                         extern declaration.                          *
* 3     09-14-12  cjqq    Add PID f1a0 f1a1 f1a2 for GW                *
* 4     10-17-12  xll     change complie option MT92_GDI_4CYL_T3_TURBO_LO2 *
*                         to MT92_GDI_PID_Config                       *
* 5     12-13-12  xll     VIR#1022 Deleted complie option MT92_GDI_PID_Config *
* 7     13-08-30  xll     RCR#1239 Deleted DIdNetworkTopologyInformation *
*                                          DIdSystemConfiguration        *
*                                          DIdVehicleMaufacturingDate    *
* 9     14-04-03  tz9dw1  RSM8282 Added DIdTTECANIMMOWriteSC and         *
*                         DIdTTECANIMMOWriteSK for TTE CAN IMMO in MT62p1 *
* 11    14-06-30  lgj     SCR 1167 define DIdValeoIMMOWriteSC          *
************************************************************************
* 2     07-31-12  azh     Added DIdKostallImmoSKCheckResult            *
************************************************************************
* Functions in this file:                                              *
************************************************************************
* extern:                                                              *
*        void LnDiagnosticSessionControl (void);                  *
* Inline:                                                              *

***********************************************************************/
#include "dcanpcfg.h"
#include "filepcfg.h"

#if (XeDCAN_SID_2E_Supported == CeDCAN_Supported)

#define wdliMalfDisableArray    (0xFA)
#define ExpectedTimeToFlushAllEepInMs (2000.0)
/*--- Data Identifier list definition (SID2E)---*/
/*---------------------------------------*/
#define DIdCrankshaftAdaptiveCylinder            (0x010a)
#define DIdTECDSampleCounter                     (0x010b)
#define DIdVehicleIdentificationNumber           (0xf190)
#define DIdRepairShopCodeOrTesterSerialNumber    (0xf198)
#define DIdProgrammingDate                       (0xf199)
#define DIdManufacturersEnableCounter            (0x01a0)

#if defined(OBD_CONTROLLER_IS_MT22P3)
   #if defined(CeFILE_USE_CMC_2nd_Set_VIN)
#define DldCMC1stVehicleIdentificationNumber     (0xf014)
#define DldCMC2ndVehicleIdentificationNumber     (0xf013)
   #endif /* #if defined (CeFILE_USE_CMC_2nd_Set_VIN)*/
#endif /* #if defined(OBD_CONTROLLER_IS_MT22P3)*/

#define DIdKostallImmoSKCheckResult              (0xfd00)
#ifdef OBD_CONTROLLER_IS_MT22P3
#define DIdCMCEngineDataIdentifier               (0xf015)
#endif
/*--f1a0,f1a1,f1a2 supported for CHK, not supported for JAC--*/
#define DIdContiIMMOWriteSC                      (0x0206)
#define DIdContiIMMOWriteSK                      (0x0201)
#define DIdHIRAINIMMOWriteSK                     (0x0203)
#define DIdTTECANIMMOWriteSC                     (0xFE1A)
#define DIdTTECANIMMOWriteSK                     (0xFE1B)
#define DIdValeoIMMOWriteSC                      (0x20B2)

void LnWriteDataByIdentifier (void);

#else /* SID_2E not Supported */

#define LnWriteDataByIdentifier        ServiceNotSupported_DCAN

#endif /* (XeDCAN_SID_2E_Supported == CeDCAN_Supported) */

#endif

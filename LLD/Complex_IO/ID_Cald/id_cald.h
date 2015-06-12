#ifndef ID_CALD_H
#define ID_CALD_H
/* ============================================================================ *\
 * id_cald.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       id_cald.h-5:incl:mt20a#2
 * Revision:        5
 * Creation date:   Tuesday, October 08, 2002 3:19:10 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the ECU identification calibrations.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "reuse.h"


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
/*  none  */

/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */
/*  none  */

/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*--- Production program identifier to be compared to KKPgmId ---*/

//#define ProductionProgramId	     (0x08)


#define CalibrationPartNumberSize     (8)
#define BaseModelNumberSize              (8)
#define VIN_Size                     (17)/* Defines size of Vin Number Array */
#define VehicleManu_HW_Number_Size   (11)
#define SS_ECU_HW_Number_Size        (20)
#define SS_ECU_SW_Number_Size        (10)
//#define SS_ECU_SW_Version_Number_Size (8)
#define SystemName_EngineType_Size    (6)
#define RepairShopCode_Size          (10)
#define ProgrammingDate_Size          (4)
#define BroadcastCode_Size            (4)

#define CustPartNumberSize		(11)
#define EndModelNumberSize              (11)
#define ExhaustRegulationSize            (6)
#define CustEngineNameSizeT0             (10)


/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
extern const uint16_t  PromId;
extern const uint8_t DEBroadcastCode[BroadcastCode_Size];
extern const uint16_t KKSum;
extern const uint8_t  KKPgmId;
extern const uint8_t CalibrationPartNumber[CalibrationPartNumberSize];
extern const uint8_t KCustPartNumber[CustPartNumberSize] ;
extern const uint8_t KSystemSupplierECUHardwareNumber[SS_ECU_HW_Number_Size];
extern const uint8_t BaseModelNumber[BaseModelNumberSize];
extern const uint8_t EndModelNumber[EndModelNumberSize] ;
extern const uint16_t  ECUSoftwareVersionNumber;
extern const uint8_t ExhaustRegulation[ExhaustRegulationSize] ;
extern const uint8_t CustomerEngineName[CustEngineNameSizeT0];

/* ============================================================================ *\
 * Local INLINE functions and #define function-like macros.
\* ============================================================================ */
/*  none  */

/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported INLINE functions and #define function-like macros.
\* ============================================================================ */
#define IsDevelopment()                ( KKPgmId == 0xAA )


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * (dd/mm/yy)
 * ----------   -------     ---
 * 06/09/04     sgchia      -
 * + Created initial version of the file.
 * 07/08/06     Shoujun  mt20u2#581  Add small keyword App into MT20U3 for 
 *                                   reprogramming
 * 27/12/06     Shoujun  n/a  Changed to support MT22CORE application
 *
\* ============================================================================ */
#endif /* ID_CALD_H */

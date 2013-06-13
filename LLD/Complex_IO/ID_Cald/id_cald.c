/* ============================================================================ *\
 * id_cald.c
 * ============================================================================
 * Copyright 1999,2004 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       id_cald.c-1:csrc:mt20a#2
 * Revision:        5
 * Creation date:   Tuesday, July 16, 2002 11:34:16 AM
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
 * Other header files.
\* ============================================================================ */
#include "id_cald.h"


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local preprocessor #define macros.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local type declarations.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */

/*
*| id_cald.{
*/

//#pragma section const {CAL_ID}

/*--- WARNING: This must be strictly located at address 0x7F4000 ---*/
/*
*|        PromId {
*|            :is_calconst;
*|            :description = " Prom ID: last 4 digits of the end model number, "
*|"stored as unsigned integer value.";
*|            :units = " ";
*|        }
*/

const uint16_t  PromId = 0xFFFF ;

/*--- WARNING: This must be strictly located at address 0x7F4002 ---*/
/*
*|        DEBroadcastCode {
*|            :is_calconst;
*|            :description = " DE Broadcast Code / ECU Software Number stored as an ASCII string.";
*|            :units = " ";
*|        }
*/
const uint8_t DEBroadcastCode[BroadcastCode_Size] =
/*--- ASCII ---*/
{
   0xFF,    /*--- 00 ---*/
   0xFF,    /*--- 01 ---*/
   0xFF,    /*--- 02 ---*/
   0xFF     /*--- 03 ---*/
} ;


/*--- WARNING: This must be strictly located at address 0x4006, compatible with U2 ---*/
/*
*|        KKSum {
*|            :is_calconst;
*|            :description = "Checksum of flash memory.";
*|            :units = " ";
*|        }
*/

const uint16_t  KKSum = 0xFFFF;

/*--- AAAAh (for development unit - no checksum check) ---*/
/*--- 0076h (for MT20UED production unit)              ---*/
/*--- WARNING: This must be strictly located at address 0x4002 ---*/
/*
*|        KKPgmId {
*|            :is_calconst;
*|            :description = "Program Identifier (0xAAAA = non-production unit).";
*|            :units = " ";
*|        }
*/
const uint8_t KKPgmId = 0xAA;

/*
*|        CalibrationPartNumber {
*|            :is_calconst;
*|            :description = " Calibration Part Number / Alpha Code stored as an ASCII string.";
*|            :units = " ";
*|        }
*/

const uint8_t CalibrationPartNumber[CalibrationPartNumberSize] =
{
	0xFF,	/*--- 00 ---*/
	0xFF,	/*--- 01 ---*/
	0xFF,	/*--- 02 ---*/
	0xFF,	/*--- 03 ---*/
	0xFF,	/*--- 04 ---*/
	0xFF,	/*--- 05 ---*/
	0xFF,	/*--- 06 ---*/
	0xFF,	/*--- 07 ---*/
};


const uint8_t KCustPartNumber[CustPartNumberSize] =
{
   /*--- ASCII ---*/
   0xFF,   /*--- 00 ---*/
   0xFF,   /*--- 01 ---*/
   0xFF,   /*--- 02 ---*/
   0xFF,   /*--- 03 ---*/
   0xFF,   /*--- 04 ---*/
   0xFF,   /*--- 05 ---*/
   0xFF,   /*--- 06 ---*/
   0xFF,   /*--- 07 ---*/
   0xFF,   /*--- 08 ---*/
   0xFF,   /*--- 09 ---*/
   0xFF    /*--- 10 ---*/
} ;
/*
*|        KCustPartNumber {
*|            :is_calconst;
*|            :description = " Customer Part Number stored as an ASCII string.";
*|            :units = " ";
*|        }
*/

const uint8_t KSystemSupplierECUHardwareNumber[SS_ECU_HW_Number_Size]=
{
	/*--- ASCII ---*/
	0xFF,	/*--- 00 ---*/
	0xFF,	/*--- 01 ---*/
	0xFF,	/*--- 02 ---*/
	0xFF,	/*--- 03 ---*/
	0xFF,	/*--- 04 ---*/
	0xFF,	/*--- 05 ---*/
	0xFF,	/*--- 06 ---*/
	0xFF,	/*--- 07 ---*/
	0xFF,	/*--- 08 ---*/
	0xFF,	/*--- 09 ---*/
	0xFF,	/*--- 10 ---*/
	0xFF,	/*--- 11 ---*/
	0xFF,	/*--- 12 ---*/
	0xFF,	/*--- 13 ---*/
	0xFF,	/*--- 14 ---*/
	0xFF,	/*--- 15 ---*/
	0xFF,	/*--- 16 ---*/
	0xFF,	/*--- 17 ---*/
	0xFF,	/*--- 18 ---*/
	0xFF	/*--- 19 ---*/ 
};
/*
*|        KSystemSupplierECUHardwareNumber {
*|            :is_calconst;
*|            :description = " SystemNameOrEngineType ";
*|            :units = " ";
*|        }
*/

const uint8_t BaseModelNumber[BaseModelNumberSize] =
/*--- ASCII ---*/
{
   0xFF,    /*--- 00 ---*/
   0xFF,    /*--- 01 ---*/
   0xFF,    /*--- 02 ---*/
   0xFF,    /*--- 03 ---*/
   0xFF,    /*--- 04 ---*/
   0xFF,    /*--- 05 ---*/
   0xFF,    /*--- 06 ---*/
   0xFF     /*--- 07 ---*/
} ;
/*
*|        BaseModelNumber {
*|            :is_calconst;
*|            :description = " Base Model Number.";
*|            :units = " ";
*|        }
*/


const uint8_t EndModelNumber[EndModelNumberSize] =
/*--- ASCII ---*/
{
   0xFF,   /*--- 00 ---*/
   0xFF,   /*--- 01 ---*/
   0xFF,   /*--- 02 ---*/
   0xFF,   /*--- 03 ---*/
   0xFF,   /*--- 04 ---*/
   0xFF,   /*--- 05 ---*/
   0xFF,   /*--- 06 ---*/
   0xFF,   /*--- 07 ---*/
   0xFF,   /*--- 08 ---*/
   0xFF,   /*--- 09 ---*/
   0xFF    /*--- 10 ---*/
} ;
/*
*|        EndModelNumber {
*|            :is_calconst;
*|            :description = " End Model Number / Alpha Code stored as an ASCII string.";
*|            :units = " ";
*|        }
*/


const uint16_t  ECUSoftwareVersionNumber = 0x0000 ;
/*
*|        ECUSoftwareVersionNumber {
*|            :is_calconst;
*|            :description = " ECU Software Version Number ";
*|            :units = " ";
*|        }
*/

const uint8_t ExhaustRegulation[ExhaustRegulationSize] =
/*--- ASCII ---*/
{
   0xFF,    /*--- 00 ---*/
   0xFF,    /*--- 01 ---*/
   0xFF,    /*--- 02 ---*/
   0xFF,    /*--- 03 ---*/
   0xFF,    /*--- 04 ---*/
   0xFF     /*--- 05 ---*/
} ;
/*
*|        ExhaustRegulation {
*|            :is_calconst;
*|            :description = " Exhaust Regulation stored as an ASCII string.";
*|            :units = " ";
*|        }
*/

const uint8_t CustomerEngineName[CustEngineNameSizeT0] =
/*--- ASCII ---*/
{
   'X',    /*--- 00 ---*/
   '1',    /*--- 01 ---*/
   '6',    /*--- 02 ---*/
   'X',    /*--- 03 ---*/
   'E',    /*--- 04 ---*/
   'L',    /*--- 05 ---*/
   ' ',    /*--- 06 ---*/
   ' ',    /*--- 07 ---*/
   ' ',    /*--- 08 ---*/
   ' '     /*--- 09 ---*/
} ;
/*
*|        CustomerEngineName {
*|            :is_calconst;
*|            :description = " Customer Engine Name stored as an ASCII string.";
*|            :units = " ";
*|        }
*/



//#pragma section const {}

/*
*|   }
*/


/* ============================================================================ *\
 * Local variables.
\* ============================================================================ */
/*  none */


/* ============================================================================ *\
 * Local function prototypes.
\* ============================================================================ */
/* none */


/* ============================================================================ *\
 * Local INLINE functions and #define function-like macros.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Function definitions
 * ============================================================================ */
/* none */


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 06/09/04     sgchia      -
 * + Created initial version of the file.
 * 11/09/05     lzh         -
 * + Add VehicleManufactureHardwareNumber, SystemSupplierECUHardwareNumber and 
 *   SystemNameOrEngineType
 * 07/08/2006   Shoujun  mt20u2#581  Add small keyword App into MT20U3 for 
 *                                   reprogramming
 * ============================================================================ */

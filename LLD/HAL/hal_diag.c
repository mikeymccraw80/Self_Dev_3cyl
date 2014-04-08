/* ============================================================================ *\
 * hal_diag.c
 * ============================================================================
 * Copyright 1999,2004 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       hal_diag.c
 * Revision:        1
 * Creation date:
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   Hardware test software - PSVI diagnostic test.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "hal_diag.h"
#include "dd_l9958_interface.h"

HAL_Diag_T HAL_Diag;

uint16_t HAL_Diag_Get_L9958_HWDiag_Status(void)
{
    return L9958_FAULT_Get_HWDiag_Status();
}

//=============================================================================
// Get_IO_Discrete_Diag_ADC_0
//=============================================================================
bool Get_IO_Discrete_Diag_ADC_0(EMS_Diagnostic_T diagnostic)
{
   bool value = false;

   switch (diagnostic)
   {
   case OUTPUT_GEN_FLT_TESTED:
      value = true;
      break;

   case OUTPUT_GEN_FLT_PRESENT:
      // value = GetHWIO_ADConversionStatus();
      value = HAL_Diag.Bits.ADC_AUTOSCAN_ERR;
      break;

   default:
      break;
   }

   return (value);
}

//=============================================================================
// Clear_IO_Discrete_Diag_ADC_0
//=============================================================================
void Clear_IO_Discrete_Diag_ADC_0(EMS_Diagnostic_T diagnostic)
{
   Parameter_Not_Used( diagnostic );
   // ClearHWIO_ADConversionStatus();
   HAL_Diag.Bits.ADC_AUTOSCAN_ERR = false;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *   110420   hzm   updated for StartStop Application
 *
\*===========================================================================*/

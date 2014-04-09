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
 * Name:         HAL_ResetDiag_Log_Parameters
\*===========================================================================*/
void HAL_ResetDiag_Log_Parameters(HWIO_Reset_Status_T reset_cause, uint32_t reset_address )
{
   if (reset_cause.Loss_Lock_Reset || reset_cause.Loss_Clock_Reset)
   {
       HAL_Diag.Bits.CPU_PLL_CLKERR = true;
   }
#if 0
   uint32_t lapse_time;
   uint8_t  index;

   if (reset_cause.Power_On_Reset)
   {
        HAL_uncleard_ram.reset_exception_pattern = 0; // reset the pattern which serves kinds of Exception
        HAL_uncleard_ram.reset_reason = CAUSE_OF_POWER_ON_RST;
   }
   else if (reset_cause.External_Reset)
   {
        HAL_uncleard_ram.reset_reason = CAUSE_OF_EXTERNAL_RST;
   }
   else if (reset_cause.Loss_Lock_Reset)
   {
       HAL_Diag.Bits.CPU_PLL_CLKERR = true;
       HAL_uncleard_ram.reset_reason = CAUSE_OF_LOSS_OF_LOCK_RST;
   }
   else if (reset_cause.Loss_Clock_Reset)
   {
       HAL_Diag.Bits.CPU_PLL_CLKERR = true;
       HAL_uncleard_ram.reset_reason = CAUSE_OF_LOSS_OF_CLOCK_RST;
   }
   else if (reset_cause.Watchdog_Reset)
   {
       HAL_uncleard_ram.reset_reason = CAUSE_OF_WATCHDOG_TIMER_DEBUG_RST;
   }
   else if (reset_cause.CheckStop_Reset)
   {
       HAL_uncleard_ram.reset_reason = CAUSE_OF_SOFTWARE_WATCHDOG_TIMER_RST;
   }
   else if (reset_cause.SoftwareWDTimer_Reset)
   {
       HAL_uncleard_ram.reset_reason = CAUSE_OF_CHECKSTOP_RST;
   }
   else if (reset_cause.SoftwareSystem_Reset)
   {
      if ( 0x5a == HAL_uncleard_ram.reset_exception_pattern )
      {
          /* reset was triggered by exception
           * updated in Exception routine
           */
      }
      else
      {
          HAL_uncleard_ram.reset_reason = CAUSE_OF_SOFTWARE_SYSTEM_RST;
      }
   }
   else if (reset_cause.SoftwareExternal_Reset)
   {
       HAL_uncleard_ram.reset_reason = CAUSE_OF_SOFTWARE_EXTERNAL_RST;
   }
   else
   {
       HAL_uncleard_ram.reset_reason = CAUSE_OF_SOFTWARE_UNKNOWN_RST;
   }

   for ( index=(RESETSOURCE_HISTORY_SIZE-1); index>0; index-- )
   {
       ResetSource_History[index] = ResetSource_History[index-1];
   }
   ResetSource_History[0] = HAL_uncleard_ram.reset_reason;
#endif
}

//=============================================================================
// Get_IO_Discrete_Diag_CPU_Clock
//=============================================================================
bool Get_IO_Discrete_Diag_CPU_Clock(EMS_Diagnostic_T diagnostic)
{
   // Not supported
   Parameter_Not_Used( diagnostic );
   return (bool)HAL_Diag.Bits.CPU_PLL_CLKERR;
}

//=============================================================================
// Clear_IO_Discrete_Diag_CPU_Clock
//=============================================================================
void Clear_IO_Discrete_Diag_CPU_Clock(EMS_Diagnostic_T diagnostic)
{
   // Not supported
   Parameter_Not_Used( diagnostic );
   HAL_Diag.Bits.CPU_PLL_CLKERR = false;
}



/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *   110420   hzm   updated for StartStop Application
 *
\*===========================================================================*/

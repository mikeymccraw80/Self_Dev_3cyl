/* ============================================================================ *\
 * hal_mileage.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       hal_mileage.c-5:csrc:2
 * Revision:        5
 * Creation date:   Monday, June 03, 2002 1:34:46 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains vehicle speed sensor virtual I/O
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
#include "io_type.h"


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "filenvmd.h"
#include "hal_mileage.h"
#include "HLS.h"

/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
#define Convert_Km_To_100m(x)          (x*10)
#define Convert_100m_To_Km(x)          (x/10)


void InitialiseMileage(void)
{
   uint32_t *p;
   p = (uint32_t *)NsFILE_NVM_EE_ManufactData.VaFILE_EE_Odometer;
   odometer = Convert_100m_To_Km(*p);
}


void UpdateMileage( void )
{
   uint32_t *p;
   p = (uint32_t *)NsFILE_NVM_EE_ManufactData.VaFILE_EE_Odometer;

   *p = Convert_Km_To_100m(odometer);
}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */

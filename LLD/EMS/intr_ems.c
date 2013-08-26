/* ============================================================================ *\
 * intr_ems.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       intr_ems.c-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, 16 September, 2003 02:41:00 AM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the parameter update function for interface with EMS.
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
#include "intr_ems.h"

/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
int16_t                              EOBD_CoolTemp;
EOBD_PERCENTa                        EOBD_CcpDutyCycle;
EOBD_VOLTb                           EOBD_Ignition_Voltage;
EOBD_VOLTb                           EOBD_IgnVoltageAtKeyOn;


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
\* ============================================================================ */

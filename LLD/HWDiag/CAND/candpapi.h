#ifndef CANDPAPI_H
#define CANDPAPI_H
/******************************************************************************
 *
 * Filename:          candpapi.h
 *
 * Description:       CAN communication with TCM diagnostic interface subsystem
 *                    API interface  file
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
 * Copyright 2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      mt20u2#8/incl/candpapi.h/1 %
 * %date_created:   Wed Mar 19 09:46:28 2008 %
 * %version:        1 %
 * %derived_by:     vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
 Include Files
******************************************************************************/

#include "candcald.h"    /* For CAND Local Configuration       */


/******************************************************************************
 *  Include Files
******************************************************************************/

/*********************************************************************
* exported functions
**********************************************************************/
void InitCAND_RstToKeyOn(void);
void InitCAND_OFVC_Clear(void);
void MngCAND_31p2msTCU_Tasks(void);

#define CcDGDM_CAN_TCM_Communication         KsDGDM_CAN_Communication//CcDDMS_UNDEFINED

#define CcDGTH_CAN_TCM_Communication         CcDDMS_DEFINED//CcDDMS_UNDEFINED


/****************************************************************************
 *  Inline Functions
 ****************************************************************************/


#endif /*CANDPAPI_H*/


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 16/12/05     LShoujun    mt20u2#36
 * + Baseline - Add CAN Commu Failure Diag
 *
\* ============================================================================ */

#ifndef KW2SRV30EXEC_H
#define KW2SRV30EXEC_H
/* ============================================================================ *\
 * kw2srv30exec.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv30exec.h-1:incl:mt20u2#51
 * Revision:        1
 * Creation date:   June 08, 2006 
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $30 execution function - Input/output control by local identifier
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#if 0
#include "reuse.h"

extern FAR_COS void IOLIdCheckLight( uint8_t IOCtrl, uint8_t CtrlState );
extern FAR_COS void IOLIdCharcoalCanisterPurgeOnOff( uint8_t IOCtrl, uint8_t CtrlState );
extern FAR_COS void IOLIdFuelPumpRelay( uint8_t IOCtrl, uint8_t CtrlState );
extern FAR_COS void IOLIdACCutoffRelay( uint8_t IOCtrl, uint8_t CtrlState );
extern FAR_COS void IOLIdFan1( uint8_t IOCtrl, uint8_t CtrlState );
extern FAR_COS void IOLIdFan2( uint8_t IOCtrl, uint8_t CtrlState );
#endif
#endif

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 09/06/06     Jerry.Wu    mt20u2#51
 * + Update kword spec
 *   - Add function IOLIdCheckLight, IOLIdCharcoalCanisterPurgeOnOff, IOLIdACCutoffRelay
 *   - IOLIdFan1, IOLIdFan2 and IOLIdFuelPumpRelay.
 *
 *
\* ============================================================================ */

#ifndef MOD_CALS_H
#define MOD_CALS_H
/* ============================================================================ *\
 * mod_cals.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       mod_cals.h-5:incl:mt20a#2
 * Revision:        5
 * Creation date:   Wednesday, June 19, 2002 11:09:13 AM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the Mode 4 snapshot calibrations.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "reuse.h"    /* for uint8_t, bool, uint16_t */

typedef uint16_t                          Modes4BaudRateType ;
#define Prec_Modes4BaudRateType (4.0)
#define Min_Modes4BaudRateType	(4.0)
#define Max_Modes4BaudRateType	(262144.0)

#define RFactor_Modes4BaudRateType_BaudRateType (16.0)

#define NbADTSSTables (9)                                  /* number of snapshot tables */

typedef
enum{hdMode0ALDL = 0, hdKw81 = 1}         Modes4HeaderType ;
typedef
enum{tnNoTable = 0, tn1 = 1, tn2 = 2, tn3 = 3, tn4 = 4, tn5 = 5, tn6 = 6, tn7 = 7, tn8 = 8, tn9 = 9}Modes4TableNumber ;
typedef uint8_t                         Modes4SlowTableBlockSizeType ;
typedef
struct
{
    bitfield16_t M4CalSessionSelect                : 1 ;
    bitfield16_t UnassignedBits                    : 15 ;
}                                         M4CalSessionState_Type ;

/*--- Address Table 1 for snapshot in ReadDataByLocalId and Modes4. ---*/

#define MaximumATSnapshot1Size (4)

extern const uint16_t                     AddressTableSnapshot1[MaximumATSnapshot1Size] ;
/*--- Address Table 2 for snapshot in ReadDataByLocalId and Modes4. ---*/

#define MaximumATSnapshot2Size (12)

extern const uint16_t                     AddressTableSnapshot2[MaximumATSnapshot2Size] ;
/*--- Address Table 3 for snapshot in ReadDataByLocalId and Modes4. ---*/

#define MaximumATSnapshot3Size (28)

extern const uint16_t                     AddressTableSnapshot3[MaximumATSnapshot3Size] ;
/*--- Address Table 4 for snapshot in ReadDataByLocalId and Modes4. ---*/

#define MaximumATSnapshot4Size (61)

extern const uint16_t                     AddressTableSnapshot4[MaximumATSnapshot4Size] ;
/*--- Address Table 5 for snapshot in ReadDataByLocalId and Modes4. ---*/

#define MaximumATSnapshot5Size (12)

extern const uint16_t                     AddressTableSnapshot5[MaximumATSnapshot5Size] ;
/*--- Address Table 6 for snapshot in ReadDataByLocalId and Modes4. ---*/

#define MaximumATSnapshot6Size (60)

extern const uint16_t                     AddressTableSnapshot6[MaximumATSnapshot6Size] ;
/*--- Address Table 7 for snapshot in ReadDataByLocalId and Modes4. ---*/

#define MaximumATSnapshot7Size (12)

extern const uint16_t                     AddressTableSnapshot7[MaximumATSnapshot7Size] ;
/*--- Address Table 8 for snapshot in ReadDataByLocalId and Modes4. ---*/

#define MaximumATSnapshot8Size (42)

extern const uint16_t                     AddressTableSnapshot8[MaximumATSnapshot8Size] ;
/*--- Address Table 9 for snapshot in ReadDataByLocalId and Modes4. ---*/

#define MaximumATSnapshot9Size (50)

extern const uint16_t                     AddressTableSnapshot9[MaximumATSnapshot9Size] ;






/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 16/03/05     Q.W         280
 * + Reallocate Calibration Space and delete Redundant Cals
 *   - Deleted M4CalBaudRate, M4CalFastTableNumber, M4CalHeader, M4CalSessionState, M4CalSlowTableBlockSize, M4CalSlowTableNumber.
 *
\* ============================================================================ */
#endif /* MOD_CALS_H */
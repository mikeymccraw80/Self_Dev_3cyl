/* ============================================================================ *\
 * j1939_cald.c
 * ============================================================================
 * Copyright 1999,2004 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       j1939_cald.c-5:csrc:mt20a#2
 * Revision:        5
 * Creation date:   Tuesday, July 16, 2002 11:34:16 AM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the j1939 tx and rx enable calibrations.
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
#include "t_custom.h"
#include "j1939_cald.h"
/*
*| j1939_cald.{
*/

/*
*|   KeHWIO_J1939_Trigger_TYPE {
*|     : is_calconst;
*|     : description = "Event trigger sent PGN type.";
*|     : units = "enum";
*|   }
*/
const HWI_J1939_Trigger_TYPE KeHWIO_J1939_Trigger_TYPE=TX_PGN_65251_INDEX;

/*
*|   KbHWIO_J1939_Event_Trigger {
*|     : is_calconst;
*|     : description = "J1939 message transmit inner trigger event switch.";
*|     : type = types.size2_0to1;
*|     : units = "bool";
*|   }
*/
const  uint8_t KbHWIO_J1939_Event_Trigger = FALSE;


/*
*|   KfHWIO_J193973_PGN_65226_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J193973_PGN_65226 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J193973_PGN_65226_FREQ = V_COUNT_WORD(1000);


/*
*|   KfHWIO_J1939_PGN_61444_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J1939_PGN_61444 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_61444_FREQ = V_COUNT_WORD(20);

/*
*|   KfHWIO_J1939_PGN_61443_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J1939_PGN_61443 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_61443_FREQ = V_COUNT_WORD(50);

/*
*|   KfHWIO_J1939_PGN_64997_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J1939_PGN_64997 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_64997_FREQ = V_COUNT_WORD(1000);

/*
*|   KfHWIO_J1939_PGN_65266_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J1939_PGN_65266 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_65266_FREQ = V_COUNT_WORD(100);

/*
*|   KfHWIO_J1939_PGN_65262_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J1939_PGN_65262 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_65262_FREQ = V_COUNT_WORD(1000);

/*
*|   KfHWIO_J1939_PGN_65263_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J1939_PGN_65263 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_65263_FREQ = V_COUNT_WORD(500);

/*
*|   KfHWIO_J1939_PGN_65270_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J1939_PGN_65270 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_65270_FREQ = V_COUNT_WORD(500);

/*
*|   KfHWIO_J1939_PGN_65271_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J1939_PGN_65271 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_65271_FREQ = V_COUNT_WORD(1000);

/*
*|   KfHWIO_J1939_PGN_65213_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the tx period of J1939_PGN_65213 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_65213_FREQ = V_COUNT_WORD(1000);


/*
*|   KfHWIO_J1939_PGN_57344_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the rx period of J1939_PGN_57344 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_57344_FREQ = V_COUNT_WORD(1000);

/*
*|   KfHWIO_J1939_PGN_00000_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the rx period of J1939_PGN_00000 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_00000_FREQ = V_COUNT_WORD(20);

/*
*|   KfHWIO_J1939_PGN_65265_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the rx period of J1939_PGN_65265 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_65265_FREQ = V_COUNT_WORD(100);

/*
*|   KfHWIO_J1939_PGN_64971_FREQ{
*|     : is_calconst;
*|     : description ="This calibration determines the rx period of J1939_PGN_64971 ";
*|     : type = types.uint16_t;
*|     : units = "ms";
*|   }
*/
const uint16_t  KfHWIO_J1939_PGN_64971_FREQ = V_COUNT_WORD(500);

/*
*|   }
*/

#ifndef J1939_CALD_H
#define J1939_CALD_H
/******************************************************************************
 *
 * Filename:          candcald.h
 *
 * Description:       CAN Diagnostic - Calibration header file
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
 * Copyright 2001-2002, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/******************************************************************************
 *  Subsystem Include Files
 *****************************************************************************/
#include "t_gentypes.h"
typedef enum
  {
  TX_PGN_65249_INDEX=12,
  TX_PGN_65251_INDEX=13
  } HWI_J1939_Trigger_TYPE;

extern const HWI_J1939_Trigger_TYPE KeHWIO_J1939_Trigger_TYPE;
extern const  uint8_t  KbHWIO_J1939_Event_Trigger;
extern const uint16_t  KfHWIO_J193973_PGN_65226_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_61444_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_61443_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65247_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_64997_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65266_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65262_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65263_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65270_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65271_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65213_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65249_FREQ;

extern const uint16_t  KfHWIO_J1939_PGN_57344_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_00000_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65265_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_64971_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_61442_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_61445_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65298_FREQ;
extern const uint16_t  KfHWIO_J193973_PGN_65251_FREQ; 
extern const uint16_t  KfHWIO_J1939_PGN_65299_FREQ;
extern const uint16_t  KfHWIO_J1939_PGN_65226_FREQ;

#endif


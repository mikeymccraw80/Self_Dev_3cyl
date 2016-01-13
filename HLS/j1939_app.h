#ifndef J1939_APP_H
#define J1939_APP_H

/******************************************************************************
 *
 * Filename:          j1939_app.h
 *
 * Description:       j1939 app header file for APPLICATION
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
 * Copyright 2015 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/
#include "reuse.h"

uint8_t*GetJ1939_DM1_MsgPtr (void);
uint16_t GetJ1939_DM1_ActiveDTC_NUMBER (void);

uint8_t *GetJ1939_PGN_65251_MsgPtr (void);
uint8_t *GetJ1939_PGN_65249_MsgPtr (void);

uint16_t GetJ1939_PGN_65251_BYTE_NUMBER (void);
uint16_t GetJ1939_PGN_65249_BYTE_NUMBER (void);


uint8_t *GetJ1939_DM2_MsgPtr (void);
uint16_t GetJ1939_DM2_PreActiveDTC_NUMBER (void);

bool ClrJ1939_DM3_PreActive_Dtcs(void);

uint8_t *GetJ1939_DM4_MsgPtr (void);

bool ClrJ1939_DM11_Active_Dtcs (void);

uint8_t *GetJ1939_DM12_MsgPtr (void);
uint16_t GetJ1939_DM12_EmissionsRelated_ActiveDTCs_Number (void);



#endif /* End of J1939_APP_H */

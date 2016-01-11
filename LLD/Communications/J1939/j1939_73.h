/*****************************************************************************
 * Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
 * AUTHORS: Sandeep, Prakash, Mehak                                          *
 * Project: CNG E483                                                         *
 * File Name:  j1939_73.h                                                    *
 * File Description:                                                         *
 * This file is used to build DTCs for DM messaegs                           *
 *****************************************************************************/

#ifndef J1939_73_H
#define J1939_73_H

#include "j1939_data_types.h"

extern bool                 J1939_DMRequired;

extern void J1939_Message_SnapShot (uint8_t *MsgBuf, uint8_t *SnapShotBuf, uint16_t size);
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   08-Apr-10   Mehak           CNG E483 first release                      *
 ******************************************************************************/
#endif

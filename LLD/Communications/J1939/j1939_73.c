/*****************************************************************************
 * Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
 * AUTHORS: Sandeep, Prakash, Mehak                                          *
 * Project: CNG E483                                                         *
 * File Name:  j1939_73.c                                                    *
 * File Description:                                                         *
 * This file is used to build DTCs for DM messaegs                           *
*****************************************************************************/
#include "j1939_73.h"

/************************************************************************/
/* Static vars shared amoung j1939_73_dmX                               */
/************************************************************************/
void J1939_Message_SnapShot (uint8_t *MsgBuf, uint8_t *SnapShotBuf, uint16_t size)
{
   uint16_t buf_index;

   for (buf_index = 0; buf_index < size;  buf_index++)
   {
      SnapShotBuf[buf_index] = MsgBuf[buf_index];
   }
}
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   08-Apr-10   Mehak           CNG E483 first release                      *
 ******************************************************************************/


#ifndef SIEMENS_IMMOSAUT_H
#define SIEMENS_IMMOSAUT_H
/******************************************************************************
 *
 * Filename:          siemens_immosaut.h
 *
 * Description:       This module contains the authentication services of 
 *                    Siemens Immobilizer 
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
 * Copyright 2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/******************************************************************************
 *  Include Files
 *****************************************************************************/

/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "kw2dll.h"
#include "kw2app.h"
#include "Immo_cal.h"



extern TbBOOLEAN VbSiemens_IllegalMsgReceived;
extern TbBOOLEAN VbSiemens_MsgSeqError;

//for test

/******************************************************************************
 * Global Function Prototypes
 ******************************************************************************/

extern void SiemensImmo_UpdateStateMachine (void);



#endif /* Siemens_IMMOSAUT_H */
/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/

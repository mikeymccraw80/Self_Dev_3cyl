#ifndef SIEMENS_IMMOSENC_H
#define SIEMENS_IMMOSENC_H
/******************************************************************************
 *
 * Filename:          siemens_immosenc.h
 *
 * Description:       This module contains the encrypt arithmetic of 
 *                    Siemens Immobilizer 
 *
 * Global Functions Defined:
 *                    void CalcSiemens_Encrypt()
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
#include "io_type.h"

/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "kw2dll.h"
#include "kw2app.h"
#include "Immo_cal.h"
  

extern BYTE VaSiemens_RandomNum[6];
extern BYTE VaSiemens_RefResponse[6];

//extern FAR_COS void CalcBRIL_Encrypt(BYTE * Challenge, BYTE * CustomerID, BYTE * SecretKey, BYTE * Response);
extern void CalcSiem_Encrypt(BYTE * Challenge, BYTE * CustomerID, BYTE * SecretKey, BYTE * Response);
#endif /* SiemensLIANCE_IMMOSENC_H */
/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/

#ifndef SIEMENS_IMMOSSRV_H
#define SIEMENS_IMMOSSRV_H
/******************************************************************************
 *
 * Filename:          siemens_immossrv.h
 *
 * Description:       This module contains the DLL functions used by Siemens
 *                    immobilizer
 *
 * Global Functions Defined:
 *                    STECImmo_UpdateStateMachine
 *                    STECImmo_ReadVariable_From_EEPROM
 *                    STECImmo_P3MaxOvertime
 *                    STECImmo_Reset
 *                    STECImmo_BldChallengeRspMsgFrame
 *                    STECImmo_BldCodeRspMsgFrame
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
#include "reuse.h"
#include "types.h"
/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "kw2dll.h"
#include "kw2app.h"
#include "Immo_cal.h"


/******************************************************************************
 *  Include Files
 *****************************************************************************/

#define CySiemens_nrcDownloadNotAccepted        (0x40)
#define CySiemens_nrcTranspResponseIncorrect    (0xB0)
#define CySiemens_nrcPreReleaseTimeExpired      (0xB2)
#define CySiemens_nrcImmoFunctionNotProgrammed  (0xA0)
#define CySiemens_nrcSystemNotInDeliveryMode    (0xA1)
#define CySiemens_nrcIncorrectSecurityCode      (0xA2)

extern TbBOOLEAN             VbSiemens_ImmoFuncNotProgrammed;
extern TbBOOLEAN             VbSiemens_ECUPreEnable;
extern T_COUNT_BYTE          VySiemens_P3MaxOvertimeCntr;
extern T_COUNT_BYTE          PowerUpDelayTiniCntr;
extern T_COUNT_WORD          ECMLearnedDelayTime; 
extern T_COUNT_WORD          ECMResetToDeliveryDlayTime; 

extern bool ECMLearnedDelayTime_En;
extern bool ECMResetToDeliveryDlayTime_En;
/******************************************************************************
 * Global Function Prototypes
 ******************************************************************************/
void SiemensImmo_PrepareAuthenData(void);
void SiemensImmo_Initializing(void);
FAR_COS void SiemensImmo_P3MaxOvertime(void);
FAR_COS void SiemensImmo_BldChallengeRspMsgFrame (void);
FAR_COS void SiemensImmo_BldCodeRspMsgFrame (void);
extern FAR_COS void SiemensImmo_AuthResultLostService(void);

#endif /* SiemensLIANCE_IMMOSSRV_H */
/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/

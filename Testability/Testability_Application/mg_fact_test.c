//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_fact_test.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:              %
//
// %version:         7 %
//
//=============================================================================
#if 0
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal_discrete.h"
#include "mg_hal_etc.h"


/*  ASCII table For testability version
 -----------------------------------------
 | char | Hex  | Comments                |
 -----------------------------------------
 |  p   | 0x70 | Prod release for SuZhou |
 -----------------------------------------
 |  e   | 0x65 | For EE test             |
 -----------------------------------------
 |  v   | 0x76 | For validation test     |
 -----------------------------------------
 |  d   | 0x64 | for development         |
 -----------------------------------------
*/
#define MG_TESTABILITY_MAJOR_VERSION         0x64
#define MG_TESTABILITY_MINOR_VERSION         0x08

#define NUMBER_EST                                              4
#define NUMBER_INJ                                              4

/*=============================================================================
 * factTest
 * @func  this function will initilize all I/O for test and pop the testability
 *        verstion to OUTBOX
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_fact_test(void)
{
    uint8_t idx;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    MG_MAILBOX_OUT(parameter[1]) = MG_TESTABILITY_MAJOR_VERSION;
    MG_MAILBOX_OUT(parameter[2]) = MG_TESTABILITY_MINOR_VERSION;

    mg_HAL_Discrete_Set_GEN_ENABLE(false);
    mg_HAL_Discrete_Set_FSE(false);
    mg_HAL_ETC_Discrete_Enable(false);
    mg_HAL_Discrete_Set_GEN_No_Affect(false);
}

#endif
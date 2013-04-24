/*===========================================================================*\
 *
 *       COPYRIGHT, 2000, DELPHI DELCO ELECTRONICS SYSTEMS CORPORATION
 *
 *===========================================================================
 * $Archive:: /DC2/src/CorePrimitives/inst_overlay.c                        $
 *
 * $Date:: 8/13/01 12:18p                                                   $
 *
 * $Author:: Rskearney                                                      $
 *
 * $Revision:: 3                                                            $
 *
 *===========================================================================
 * DESCRIPTION:
 * This module includes all of the register definitions needed to define the
 * following subsection of the TriCore architecture.
 *
 * MODULE NAME:
 * Insert module name here (hardware or application.)
 *
 * SPECIFICATION REVISION:
 * MPC5634M Microcontroller Reference Manual Rev.4 27 May. 2010
 * MPC5644A Microcontroller Reference Manual Rev.5 20 May. 2010
 *
 *===========================================================================
 *
\*===========================================================================*/

#include "inst_config.h"
#include "inst_overlay_nvm.h"


/*===========================================================================*\
 * Global Variable declarations
\*===========================================================================*/
#pragma section DATA " " ".nc_nvram"
uint32_t INST_Internal_Cal_Page_Pattern_NVM;
#pragma section DATA " " ".bss"

//=============================================================================
//
// Revisiion History:
//
// Rev. YYMMDD Who  SCR# Changes
// ---- ------ ---- ---- -----------------------------------------------------
// 1.0  110715 xh   xxxx Create initial release.
//=============================================================================


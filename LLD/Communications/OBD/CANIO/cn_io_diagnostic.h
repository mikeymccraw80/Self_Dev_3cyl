#ifndef CN_IO_DIAGNOSTIC_H
#define CN_IO_DIAGNOSTIC_H
/******************************************************************************
 *
 * Filename:          cn_io_diagnostic.h
 *
 * Description:       CAN Diagnostics Handler header file
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
 * Copyright 2009, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/
//=============================================================================
// Include Files
//=============================================================================
#include "t_gentypes.h" // for Generic data types and Timer functions

extern bool CAN_message_length_mismatch_flag;

// XuHui - Need to be deleted after remove it's caller from io_dcan_config.c
#define Message_Length_Mismatch() \
  ( CAN_message_length_mismatch_flag )

#define Set_Message_Length_Mismatch() \
  ( CAN_message_length_mismatch_flag = true )

#define Clear_Message_Length_Mismatch() \
  ( CAN_message_length_mismatch_flag = false )

//===========================================================================
// Global Function Prototypes
//===========================================================================
extern TbBOOLEAN GetCANH_ACKMissing(void);
extern TbBOOLEAN GetCANH_PassiveState(void);
extern void DisableCANH_NetWork_Send(void);
extern void EnableCANH_NetWork_Send(void);
extern TbBOOLEAN GetCANH_BusOff_Status(void);
extern void SetCANH_BusOff_Reset(void);

#endif/*CN_IO_DIAGNOSTIC_H*/

/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     090416 yrw xxxx Initial version
* 1.1.1     
*       100322 sh  xxxx Delete #include "t_gentypes.h"
* 2     111014 sh  9541 Added interfaces.
******************************************************************************/

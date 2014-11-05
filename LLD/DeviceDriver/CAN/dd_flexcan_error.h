#ifndef DD_FLEXCAN_ERROR_H
#define DD_FLEXCAN_ERROR_H
//=============================================================================
//       COPYRIGHT 2005, Delphi Technologies, Inc. All Rights reserved
//                             Delphi Confidential
//
// --------------------------------------------------------------------------
// %name:            dd_flexcan_error.h %
//
// created_by:
//
// date_created:     Wed. Mar. 2 2005
//
// %derived_by:      zzrfyj %
//
// %date_modified:    %
//
// %version:         ctc_pt3#4 %
//
//=============================================================================
// Configurable Development Software Module:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
//
//=============================================================================

//=============================================================================
// Includes
//=============================================================================
#include "dd_flexcan.h"


typedef enum 
{
   FLEXCAN_ERROR_CHANNEL_BIT1ERR,
   FLEXCAN_ERROR_CHANNEL_BIT0ERR,
   FLEXCAN_ERROR_CHANNEL_ACKERR,
   FLEXCAN_ERROR_CHANNEL_CRCERR,
   FLEXCAN_ERROR_CHANNEL_FRMERR,
   FLEXCAN_ERROR_CHANNEL_STFERR
} FLEXCAN_ERROR_CHANNEL_T;

typedef enum 
{
   FLEXCAN_FLT_CONF_ERR_ACTIVE,
   FLEXCAN_FLT_CONF_ERR_PASSTIVE,
   FLEXCAN_FLT_CONF_ERR_BUSOFF
} FLEXCAN_FLT_CONF_ERR_T;


//=============================================================================
// FlexCAN_Error_Handler
//
// @func FlexCAN device Error Interrupt Handler. This handler is called whenever
//       a Bus-off or error happens for the FlexCAN device
//
// @parm FlexCAN_Index_T* | in_FlexCAN |pointer to FlexCAN device which caused  
//          the interrupt 
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Error_Handler (
   FlexCAN_Index_T in_FlexCAN);

uint8_t FlexCAN_Get_Rx_Error_Counter (
   FlexCAN_Index_T in_FlexCAN);

uint8_t FlexCAN_Get_Tx_Error_Counter (
   FlexCAN_Index_T in_FlexCAN);

bool FlexCAN_Get_Error_Status (
   FlexCAN_Index_T in_FlexCAN, FLEXCAN_ERROR_CHANNEL_T in_channel);

void FlexCAN_Set_Busoff_Recovery_Auto_Enable(
   FlexCAN_Index_T in_FlexCAN, bool in_enable);

FLEXCAN_FLT_CONF_ERR_T FlexCAN_Get_Fault_Confinement_State(
      FlexCAN_Index_T in_FlexCAN);

#endif

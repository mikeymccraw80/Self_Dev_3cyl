#ifndef DD_FLEXCAN_RECIEVE_H
#define DD_FLEXCAN_RECIEVE_H
//=============================================================================
//       COPYRIGHT 2005, Delphi Technologies, Inc. All Rights reserved
//                             Delphi Confidential
//
// --------------------------------------------------------------------------
// %name:            dd_flexcan_recieve.h %
//
// created_by:
//
// date_created:     Wed. Mar. 2 2005
//
// %derived_by:      pzkdkj %
//
// %date_modified:   Tue Jun 14 06:03:21 2011 %
//
// %version:         kok_pt2#5 %
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
//=============================================================================
// FlexCAN_Receive_Interrupt
//
// @func FlexCAN device Recieve Interrupt Handler.
//
// @parm FlexCAN_Index_T | in_FlexCAN |index to FlexCAN device which caused  
//          the interrupt 
//
// @rdesc None
//
// @end
//=============================================================================
//void FlexCAN_Receive_Interrupt(
//   FlexCAN_Index_T  in_FlexCAN);

//=============================================================================
// FlexCAN_Process_Received_Message
//
// @func This function processes the recieved message and calls the Rx callback 
//       function with recieved data and message id details. 
//
// @parm FlexCAN_Index_T* | in_FlexCAN |pointer to FlexCAN device  
//       IO_Configuration_T in_config configuration word with message object 
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Process_Received_Message(
   FLEXCAN_T* in_pFlexCAN,
   IO_Configuration_T in_config);

#endif //DD_FLEXCAN_RECIEVE_H

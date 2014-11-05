#ifndef DD_FLEXCAN_TRANSMIT_H
#define DD_FLEXCAN_TRANSMIT_H
//=============================================================================
//       COPYRIGHT 2005, Delphi Technologies, Inc. All Rights reserved
//                             Delphi Confidential
//
// --------------------------------------------------------------------------
// %name:            dd_flexcan_transmit.h %
//
// created_by:
//
// date_created:     Wed. Mar. 2 2005
//
// %derived_by:      hz1swt %
//
// %date_modified:   Thu Mar 29 08:33:41 2012 %
//
// %version:         kok_pt2#4 %
//
//=============================================================================

//=============================================================================
// Includes
//=============================================================================
#include "dd_flexcan.h"


//=============================================================================
// FlexCAN_Initiate_Message_Transmit
//
// @func FlexCAN device Initiate Transmit. This function makes the message buffer
//       ready to be transmitted on FlexCAN bus
//
// @parm FlexCAN_Index_T* | in_pFlexCAN |pointer to FlexCAN register address  
//       FlexCAN_MSGOBJ_INDEX_T | in_msg_obj   |message buffer no
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Initiate_Message_Transmit(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj    );

//=============================================================================
// FlexCAN_Transmit_Interrupt
//
// @func FlexCAN device Transmit Interrupt Handler.It clears the pending  
//       interrupt and calls transmit callback function 
//
// @parm FlexCAN_Index_T* | in_FlexCAN |pointer to FlexCAN device which caused  
//          the interrupt 
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Transmit_Interrupt(
   uint32_t in_FlexCAN );


//=============================================================================
// FlexCAN_Transmit_Message
//
// @func FlexCAN Transmit Function. This function is called whenever
//       a message needs to be transmitted
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//       uint8_t * | data_buffer | It contains the data bytes to be transmitted   
//
// @rdesc None
//
// @end
//=============================================================================
bool FlexCAN_Transmit_Message(
   IO_Configuration_T in_configuration,
   uint32_t in_message_id,        
   const uint8_t *in_data_buffer,
   uint8_t  in_data_length    );
//=============================================================================
// FlexCAN_Process_Transmitted_Message
//
// @func FlexCAN process transmitted message. This function gives the notification
//       call-back for the message transmitted
//
// @parm FlexCAN_T* | in_pFlexCAN |pointer to FlexCAN register address 
//       IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Process_Transmitted_Message(
   FLEXCAN_T          *in_pFlexCAN,
   IO_Configuration_T  in_config);

#endif

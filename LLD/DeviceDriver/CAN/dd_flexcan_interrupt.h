#ifndef DD_FLEXCAN_INTERRUPT_H
#define DD_FLEXCAN_INTERRUPT_H
//=============================================================================
//
//       COPYRIGHT, 2005, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_flexcan_interrupt.h~sdc_mt80#4:incl:kok_toy#1 %
//
// created_by:       gzdmlz
//
// date_created:     Fri Jan 13 22:58:37 2006
//
// %derived_by:      dz48hg %
//
// %date_modified:   Thu Sep  8 06:52:52 2011 %
//
// %version:         sdc_mt80#4 %
//
// ============================================================================
// Configurable Development Software Module:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
//
//=============================================================================
#include "dd_flexcan.h"
#include "io_type.h"

//=============================================================================
// FLEXCAN_INTERRUPT_Initialize
//
// @func FlexCAN Interrupt Initialization Function. This function initializes
//       FlexCAN device interrupt
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_INTERRUPT_Initialize(
   IO_Configuration_T in_configuration,
   uint8_t              in_vector,
   const IO_Callback_T  in_callback,
   IO_TOS_T             in_tos );

//=============================================================================
// FLEXCAN_INTERRUPT_Clear
//
// @func FlexCAN Interrupt Clear Function. This function clears 
//       FlexCAN device interrupt
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_INTERRUPT_Clear(
   IO_Configuration_T in_configuration  );

//=============================================================================
// FLEXCAN_INTERRUPT_Set_Enable
//
// @func FlexCAN Interrupt enable function. This function enables FlexCAN device 
//       interrupt based on status(enable/disable) 
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//       bool status desired interrupt status
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_INTERRUPT_Set_Enable(
   IO_Configuration_T in_configuration,
   bool status);

//=============================================================================
// FLEXCAN_INTERRUPT_Get_Enable
//
// @func FlexCAN Interrupt  for returing enable status of FlexCAN device 
//       interrupt 
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc bool interrupt enable status
//
// @end
//=============================================================================
bool FLEXCAN_INTERRUPT_Get_Enable(
   IO_Configuration_T in_configuration  );

//=============================================================================
// FLEXCAN_INTERRUPT_Get_Status
//
// @func FlexCAN Interrupt function for returing FlexCAN device interrupt flag
//       status 
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc bool current interrupt flag status
//
// @end
//=============================================================================
bool FLEXCAN_INTERRUPT_Get_Status(
   IO_Configuration_T in_configuration  );

//=============================================================================
// FLEXCAN_INTERRUPT_Clear_Pending
//
// @func FlexCAN Interrupt function for clearing pending FlexCAN device 
//       interrupt 
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_INTERRUPT_Clear_Pending(
   IO_Configuration_T in_configuration  );

//=============================================================================
// FLEXCAN_MSGOBJ_INTERRUPT_Initialize
//
// @func FlexCAN MSGOBJ Interrupt Initialization Function. This function 
//       initializes FlexCAN message object interrupt
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_MSGOBJ_INTERRUPT_Initialize(
   IO_Configuration_T in_configuration,
   uint8_t              in_vector,
   const IO_Callback_T  in_callback,
   IO_TOS_T             in_tos );

//=============================================================================
// FLEXCAN_MSGOBJ_INTERRUPT_Clear
//
// @func FlexCAN MSGOBJ Interrupt Clear Function. This function clears 
//       FlexCAN message object interrupt
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_MSGOBJ_INTERRUPT_Clear(
   IO_Configuration_T in_configuration  );

//=============================================================================
// FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable
//
// @func FlexCAN MSGOBJ Interrupt Enable Function. This function enables/disables 
//       FlexCAN message object interrupt
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//       bool in_enable desired interrupt status
//
// @rdesc None
//
// @end
//=============================================================================
#if 0
void FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
   IO_Configuration_T in_configuration,
   bool in_enable );
#endif

//=============================================================================
// FLEXCAN_MSGOBJ_INTERRUPT_Get_Enable
//
// @func FlexCAN MSGOBJ Interrupt function for returning enables/disables 
//       status of FlexCAN message object interrupt
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
bool FLEXCAN_MSGOBJ_INTERRUPT_Get_Enable(
   IO_Configuration_T in_configuration );

//=============================================================================
// FLEXCAN_MSGOBJ_INTERRUPT_Get_Status
//
// @func FlexCAN MSGOBJ Interrupt function for returning interrupt flag status 
//       of FlexCAN message object
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
bool FLEXCAN_MSGOBJ_INTERRUPT_Get_Status(
   IO_Configuration_T in_configuration );

//=============================================================================
// FLEXCAN_MSGOBJ_INTERRUPT_Clear_Pending
//
// @func FlexCAN MSGOBJ Interrupt function for clearing FlexCAN message object 
//       pending interrupt
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_MSGOBJ_INTERRUPT_Clear_Pending(
   IO_Configuration_T in_configuration  );


#endif // DD_FLEXCAN_INTERRUPT_H

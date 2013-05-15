#ifndef DD_SCI_INTERRUPT_H
#define DD_SCI_INTERRUPT_H
//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_sci_interrupt.h~sdc_mt80#3:incl:kok_toy#1 %
//
// created_by:       fz3pdz
//
// date_created:     Mon Apr 24 10:13:37 2006
//
// %derived_by:      dz48hg %
//
// %date_modified:   Wed Dec 14 04:53:39 2011 %
//
// %version:         sdc_mt80#3 %
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

//=============================================================================
// SCI_INTERRUPT_Initialize
//
// @func Initializes a interrupt to occur for a specific device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm uint8_t | in_vector | A configurable value set in io_vector.h
//          that specifies the vector for this service request handler.
//
// @parm IO_Callback_T | in_callback | Interrupt Service Request control callback of type <t IO_Callback_T>
//
// @parm IO_TOS_T | in_tos | Interrupt selection modes from <t IO_TOS_T>
//
// @rdesc None
//
// @end
//=============================================================================
void SCI_INTERRUPT_Initialize(
   IO_Configuration_T   in_configuration,
   uint8_t              in_vector,
   const IO_Callback_T  in_callback,
   IO_TOS_T             in_tos );

//=============================================================================
// SCI_INTERRUPT_Clear
//
// @func Clears a configured interrupt for a specific device to its reset state.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void SCI_INTERRUPT_Clear(
   IO_Configuration_T   in_configuration );

//=============================================================================
// SCI_INTERRUPT_Set_Enable
//
// @func Enables or disables the interrupt.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm bool | in_enable | Set true for enabled, false for isabled.
//
// @rdesc None
//
// @end
//=============================================================================
void SCI_INTERRUPT_Set_Enable(
   IO_Configuration_T   in_configuration,
   bool                 in_enable );

//=============================================================================
// SCI_INTERRUPT_Get_Enable
//
// @func Provides enable information for the interrupt.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc Return true for enabled, false for disabled.
//
// @end
//=============================================================================
bool SCI_INTERRUPT_Get_Enable(
   IO_Configuration_T   in_configuration );

//=============================================================================
// SCI_INTERRUPT_Get_Status
//
// @func Get the status of the interrupt pending flag.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc Return the status of the interrupt pending flag
// @flag true | interrupt pending flag is set
// @flag false | interrupt pending flag is not set
//
// @end
//=============================================================================
bool SCI_INTERRUPT_Get_Status(
   IO_Configuration_T   in_configuration );

//=============================================================================
// SCI_INTERRUPT_Clear_Pending
//
// @func  Clear the pending flag of the requested interrupt.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void SCI_INTERRUPT_Clear_Pending(
   IO_Configuration_T   in_configuration );

//=============================================================================
// SCI_INTERRUPT_Set_Priority
//
// @func Set the desired interrupt priority level for the requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm uint32_t | in_priority | Desired priority level.
//
// @rdesc The previous interrupt priority level
//
// @end
//=============================================================================
uint32_t SCI_INTERRUPT_Set_Priority(
   IO_Configuration_T   in_configuration,
   uint32_t             in_priority );

//=============================================================================
// SCI_INTERRUPT_Get_Priority
//
// @func Get the current interrupt priority level of the requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The current interrupt priority level.
//
// @end
//=============================================================================
uint32_t SCI_INTERRUPT_Get_Priority(
   IO_Configuration_T   in_configuration );

//=============================================================================
// SCI_INTERRUPT_Get_Initial_Priority
//
// @func Get the initial (configured) interrupt priority level of the requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The current interrupt priority level.
//
// @end
//=============================================================================
uint32_t SCI_INTERRUPT_Get_Initial_Priority(
   IO_Configuration_T   in_configuration );


#endif // DD_SCI_INTERRUPT_H

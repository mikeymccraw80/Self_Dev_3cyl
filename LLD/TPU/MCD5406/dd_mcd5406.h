#ifndef DD_MCD5406_H
#define DD_MCD5406_H

#include "dd_tpu.h"
#include "rqom.h"
#include "mcd5406.h"

//===========================================================================
// Function Prototypes                                                       
//===========================================================================

//=============================================================================
// MCD5406_Initialize_Channel
//
// @func Initilaizes the MCD5406 primitiv
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm void | *in_init | Primitive specific initialization structure
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Initialize_Channel(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   void        *in_init );

//=============================================================================
// MCD5406_Shutdown
//
// @func This function shuts down the MCD5406 RQOM Primitive
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @rdesc none
//
// @end
//=============================================================================
void MCD5406_Shutdown(  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5406_Request
//
// @func Issues request on the RQOM given channel.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Request(  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5406_Update
//
// @func This Update Request is invoked if there are any changes in the
//       values of the global parameters after a pulse request has
//       been made.
//
// @parm   IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Update(  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5406_Set_Parameter
//
// @func This sets the size of the active array for the selected channel.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm Rqom_Parameter_T | in_parameter | selected parameter to modify
//
// @parm uint32_t | in_value | selected channel parameter value
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Set_Parameter(  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   Rqom_Parameter_T  in_parameter,
   uint32_t          in_value );

//=============================================================================
// MCD5406_Get_Parameter
//
// @func Returns the parameter for the selected channel.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm Rqom_Parameter_T | in_parameter | selected parameter to modify
//
// @rdesc Parameter value
//
// @end
//=============================================================================
uint32_t MCD5406_Get_Parameter(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   Rqom_Parameter_T  in_parameter );

//=============================================================================
// MCD5406_Set_Flag
//
// @func This procedure will update the Start, end and status flags for the
//       selected channel.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm Rqom_Flag_T | in_flag | selected flag to set
//
// @parm bool | in_value | value to be set
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Set_Flag(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   Rqom_Flag_T    in_flag,
   bool           in_value );

//=============================================================================
// MCD5406_Get_Flag
//
// @func Returns the Start_Flags parameter for the selected RQOM channel.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm Rqom_Flag_T | in_flag | selecteg flag to be returned
//
// @rdesc Returned flag value
//
// @end
//=============================================================================
bool MCD5406_Get_Flag(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   Rqom_Flag_T    in_flag );

//=============================================================================
// MCD5406_Set_Array_Flag
//
// @func This procedure will update array flag for the
//       selected channel, array, and index.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm uint32_t | *in_array | array pointer, NULL = local array
//
// @parm uint32_t | in_index | index to array location
//
// @parm Rqom_Flag_T | in_flag | selected flag
//
// @parm bool | in_value | value to be set
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Set_Array_Flag(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t         *in_array,
   uint32_t          in_index,
   Rqom_Array_Flag_T in_flag,
   bool              in_value );

//=============================================================================
// MCD5406_Get_Array_Flag
//
// @func This procedure will read array flag for the
//       selected channel, array, and index.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm uint32_t | *in_array | array pointer, NULL = local array
//
// @parm uint32_t | in_index | index to array location
//
// @parm Rqom_Flag_T | in_flag | selected flag to be returned
//
// @rdesc Returned flag value
//
// @end
//=============================================================================
bool MCD5406_Get_Array_Flag(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index,
   Rqom_Array_Flag_T    in_flag );

//=============================================================================
// MCD5406_Set_All_Array_Flags
//
// @func This procedure shall update all of the array flags for a given index.
//       It shall move the applicable flags to a temp variable and write all flags 
//       per index see the specific primitive as to which array flags are available.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm uint32_t | *in_array | array pointer, NULL = local array
//
// @parm uint32_t | in_index | index to array location
//
// @parm uint32_t | in_all_flags | a uint32 containing all array flag values 
//      to be set
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Set_All_Array_Flags(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index,
   uint32_t       in_all_flags );

//=============================================================================
// MCD5406_Get_All_Array_Flags
//
// @func Returns the Start_Flags parameter for the selected RQOM channel.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm uint32_t | *in_array | array pointer, NULL = local array
//
// @parm uint32_t | in_index | index to array location
//
// @rdesc Returned all flags in a uint32 value
//
// @end
//=============================================================================
uint32_t MCD5406_Get_All_Array_Flags(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index );

//=============================================================================
// MCD5406_Set_Array_Data
//
// @func This procedure will update the Array_Event parameter for the
//       selected RQOM channel.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm uint32_t | *in_array | array pointer, NULL = local array
//
// @parm uint32_t | in_index | index to array location
//
// @parm uint32_t | in_value | value to be written to array location
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Set_Array_Data(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index,
   uint32_t       in_value );

//=============================================================================
// MCD5406_Get_Array_Data
//
// @func Returns the Array_Event parameter for the selected RQOM channel.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm uint32_t | *in_array | array pointer, NULL = local array
//
// @parm uint32_t | in_index | index to array location
//
// @rdesc Array Event
//
// @end
//=============================================================================
uint32_t MCD5406_Get_Array_Data(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index );

//=============================================================================
// MCD5406_Copy_Array
//
// @func This procedure will copy arrays.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm uint32_t | *in_source_array | source array pointer, NULL = local array
//
// @parm uint32_t | *in_destination_array | destination array pointer, NULL = local array
//
// @parm uint32_t | in_size | array size to be copied
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Copy_Array(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_source_array,
   uint32_t      *in_destination_array,
   uint32_t       in_size );

//=============================================================================
// MCD5406_Use_Array
//
// @func This procedure will use the array object passed in and copy it to the 
//       tpu's local array.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm uint32_t | *in_source_array | source array pointer, NULL = local array
//
// @parm uint32_t | in_size | size of the array to be used.
//
// @rdesc None
//
// @end
//=============================================================================
void MCD5406_Use_Array(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_source_array,
   uint32_t       in_size );

//=============================================================================
// MCD5406_DISCRETE_Get_Immediate_State
//
// @func Gets the current state of the given discrete input directly
//           from the I/O port immediately ( unbuffered ).
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc  State of the pin as defined by its configuration value
//         true | Pin is active.
//         false | Pin is inactive.
//
// @end
//=============================================================================
bool MCD5406_DISCRETE_Get_Immediate_State(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5406_Set_Host_Interrupt_Enable
//
// @func This procedure is used to set the interrupt enable state for the RQOM
//       to Host interrupt.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm bool | in_state | Requested state for the pin.
// @flag true | interrupt is enabled.
// @flag false | interrupt is disabled.
//
// @rdesc none
//
// @end
//=============================================================================
void MCD5406_Set_Host_Interrupt_Enable(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   bool           in_state );

//=============================================================================
// MCD5406_Get_Host_Interrupt_Enable
//
// @func This procedure is used to get the interrupt enable state for the RQOM.
//       MCD5406_Get_Host_Interrupt_Enable
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @rdesc enable state
//        true  | interrupt is enabled
//        false | interrupt is disabled
//
//
// @end
//=============================================================================
bool MCD5406_Get_Host_Interrupt_Enable(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5406_Set_Host_Interrupt_Status
//
// @func This procedure sets the interrupt status. use to clear the interrupt
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @parm bool | in_status | Clear pending or request an interrupt.
// @flag true | Request Interrupt.
// @flag false | Clear Pending.
//
// @rdesc none
//
// @end
//=============================================================================
void MCD5406_Set_Host_Interrupt_Status(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   bool           in_status );

//=============================================================================
// MCD5406_Get_Host_Interrupt_Status
//
// @func This procedure returns current value of interrupt status.
//
// @parm IO_Rqom_C_T | *in_rqom | RQOM object "this" pointer
//
// @rdesc status
//        true  | interrupt is pending
//        false | interrupt is not pending
//
// @end
//=============================================================================
bool MCD5406_Get_Host_Interrupt_Status(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

#endif // DD_MCD5406_H

#ifndef DD_KP254_H
#define DD_KP254_H

//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254.h %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:        %
//
// %version:         1.1.1 %
//
//=============================================================================
#include "io_type.h"
#include "dd_kp254_rxd.h"
#include "dd_kp254_txd.h"

//=============================================================================
// @enum KP254 index 
//=============================================================================
typedef enum KP254_Index_Tag
{
   KP254_INDEX_0,    // @emem KP254 Device 1
   KP254_INDEX_1,    // @emem KP254 Device 2
   KP254_INDEX_MAX   // @emem KP254 Max number of devices
}  KP254_Index_T;

//=============================================================================
// @enum KP254 messages
//=============================================================================
typedef enum KP254_Message_Tag
{
   KP254_MESSAGE_ACQ_PRESSURE ,     //@emem Acquire Pressure Register
   KP254_MESSAGE_ACQ_TEMPERATURE ,  //@emem Acquire Temperature Register
   KP254_MESSAGE_Trigger_DIAG ,     //@emem Trigger Diagnosis Register
   KP254_MESSAGE_ACQ_ID ,           //@emem Acquire Ientifier Register  
   KP254_MESSAGE_MAX                //@emem KP254 Maximum No of Messages
}  KP254_Message_T;

//=============================================================================
// @enum KP254 reset strategy
//=============================================================================
typedef enum KP254_Reset_Strategy_Tag
{
    KP254_RESET_FAILURES,          //@emem reset all detected failures
    KP254_DONT_RESET_FAILURES      //@emem don't reset all detected failures
} KP254_Reset_Strategy_T;

//=============================================================================
// @Extern declarations for KP254 Tx and Rx buffers
//=============================================================================
extern uint16_t  KP254_ACQ_Pressure_Txd[];        // Acquire pressure command
extern uint16_t  KP254_ACQ_Temperature_Txd[];     // Acquire temperature command
extern uint16_t  KP254_Trigger_DIAG_Txd[];        // Trigger diagnosis command
extern uint16_t  KP254_ACQ_ID_Txd[];              // Acquire identifier command 

extern uint16_t  KP254_Pressure_Rxd[];            // Pressure rxd buffer (With out of range diag)
extern uint16_t  KP254_Temperature_Rxd[];         // Temperature rxd buffer(With out of range diag)
extern uint16_t  KP254_DIAG_Rxd[];                // full diagnosis codes
extern uint16_t  KP254_ID_Rxd[];                  // identifier rxd buffer

extern uint8_t  KP254_Fault_Log[];                  // Fault lof buffer

//=============================================================================
// Device Set and Get macros
//=============================================================================
// @enum KP254_Device_Configuration_Position_T | Defines position for extract 
// and insertion of the device configuration
typedef enum KP254_Device_Configuration_Position_Tag
{
   KP254_DEVICE_INDEX_POSITION                  = 0,   //@emem [0-1]Index position
   KP254_DEVICE_RESET_STRATEGY_POSITION         = 2,   //@emem [2]Reset strategy position
   KP254_DEVICE_MESSAGE_POSITION                = 3    //@emem [3-5]Reset strategy position
}  KP254_Device_Configuration_Position_T;

// @enum KP254_Device_Configuration_Width_T | Defines width for extract and 
//insertion of the device configuration 
typedef enum KP254_Device_Configuration_Width_Tag
{
   KP254_DEVICE_INDEX_WIDTH          = 2,   //@emem [0-1]Index width
   KP254_DEVICE_RESET_STRATEGY_WIDTH = 1,   //@emem [2]Reset strategy width
   KP254_DEVICE_MESSAGE_WIDTH        = 3    //@emem [3-5]Reset strategy position
}  KP254_Device_Configuration_Width_T;

//============================================================================================================
// KP254_Set_Device_Index
//
// @func selects the device index
//
// @parm KP254_Index_T 
//
// @rdesc
//
// @end
//===========================================================================================================
#define KP254_Set_Device_Index(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, KP254_DEVICE_INDEX_POSITION, KP254_DEVICE_INDEX_WIDTH) )
//============================================================================================================
// KP254_Get_Device_Index
//
// @func returns the device index
//
// @parm KP254_Index_T 
//
// @rdesc
//
// @end
//===========================================================================================================
#define KP254_Get_Device_Index(x) \
   (KP254_Index_T)( Extract_Bits( x, KP254_DEVICE_INDEX_POSITION, KP254_DEVICE_INDEX_WIDTH) )

//============================================================================================================
// KP254_Set_Reset_Strategy
//
// @func 
//
// @parm KP254_Reset_Strategy_T
//
// @rdesc
//
// @end
//===========================================================================================================
#define KP254_Set_Reset_Strategy(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, KP254_DEVICE_RESET_STRATEGY_POSITION, KP254_DEVICE_RESET_STRATEGY_WIDTH ) )
//============================================================================================================
// KP254_Get_Reset_Strategy
//
// @func 
//
// @parm 
//
// @rdesc KP254_Reset_Strategy_T
//
// @end
//===========================================================================================================
#define KP254_Get_Reset_Strategy(x) \
   (KP254_Reset_Strategy_T)( Extract_Bits( x, KP254_DEVICE_RESET_STRATEGY_POSITION, KP254_DEVICE_RESET_STRATEGY_WIDTH ) )

//============================================================================================================
// KP254_Set_Message
//
// @func 
//
// @parm KP254_Message_T
//
// @rdesc
//
// @end
//===========================================================================================================
#define KP254_Set_Message(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, KP254_DEVICE_MESSAGE_POSITION, KP254_DEVICE_MESSAGE_WIDTH) )
//============================================================================================================
// KP254_Get_Message
//
// @func 
//
// @parm 
//
// @rdesc KP254_Message_T
//
// @end
//===========================================================================================================
#define KP254_Get_Message(x) \
   (KP254_Message_T)( Extract_Bits( x, KP254_DEVICE_MESSAGE_POSITION, KP254_DEVICE_MESSAGE_WIDTH) )

//============================================================================================================
// KP254_Initialize_Device
//
// @func initialize kp254 before use
//
// @parm 
//
// @rdesc 
//
// @end
//===========================================================================================================
void KP254_Initialize_Device(
   IO_Configuration_T in_configuration );

//============================================================================================================
// KP254_Get_Identifier
//
// @func get kp254 ID
//
// @parm 
//
// @rdesc 
//
// @end
//===========================================================================================================
uint16_t KP254_Get_Identifier(
   IO_Configuration_T in_configuration );


#endif /* end of include guard: DD_KP254_H */

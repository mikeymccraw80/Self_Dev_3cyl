#ifndef FAULT_H
#define FAULT_H
//=============================================================================
//
//       COPYRIGHT, 2003, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            fault.h %
//
// created_by:       rskearne
//
// date_created:     Thu May 29 13:04:57 2003
//
// %derived_by:      wzf9ks %
//
// %date_modified:   Fri Apr 14 10:38:54 2006 %
//
// %version:         5 %
//
// ============================================================================
// @doc
//
// @module fault.h | Diagnostics interface definition file
//
// The purpose of this module is to provide application to access the
// functions related to diagnostics.
//
// @end
//
//=============================================================================
#include "io_type.h"

typedef uint16_t Fault_Log_T;

// @enum FAULT_T | Defines different types of diagnostic faults 
typedef enum FAULT_Tag
{
   FAULT_OCCURED_POSITION                 =  0, // @emem Occured Postition
   FAULT_SHORT_TO_GROUND                  =  0, // @emem short to ground enum for get_fault_status
   FAULT_OCCURED_SHORT_TO_GROUND          =  0, // @emem Occured short to ground fault 
   FAULT_OPEN_CIRCUIT                     =  1, // @emem open circuit enum for get_fault_status
   FAULT_OCCURED_OPEN_CIRCUIT             =  1, // @emem Occured open circuit fault 
   FAULT_SHORT_TO_BATTERY                 =  2, // @emem short to battery enum for get_fault_status
   FAULT_OCCURED_SHORT_TO_BATTERY         =  2, // @emem Occured short to battery fault 
   FAULT_THERMAL                          =  3, // @emem over temp enum for get_fault_status
   FAULT_OCCURED_THERMAL                  =  3, // @emem Occured over temp fault 
   FAULT_VOLTAGE_REGULATION               =  4, // @emem Voltage Out of Regulation enum for get_fault_status
   FAULT_OCCURED_VOLTAGE_REGULATION       =  4, // @emem Occured Voltage Out of Regulation fault 
   FAULT_TESTED_POSITION                  =  5, // @emem Test Postition
   FAULT_TESTED_SHORT_TO_GROUND           =  5, // @emem Test short to ground fault 
   FAULT_TESTED_OPEN_CIRCUIT              =  6, // @emem Test open circuit fault 
   FAULT_TESTED_SHORT_TO_BATTERY          =  7, // @emem Test short to battery fault 
   FAULT_TESTED_THERMAL                   =  8, // @emem Test over temp fault 
   FAULT_TESTED_VOLTAGE_REGULATION        =  9, // @emem Test Voltage Out of Regulation fault 
   FAULT_SUPPORTED_POSITION               = 10, // @emem Supported Postition
   FAULT_SUPPORTED_SHORT_TO_GROUND        = 10, // @emem Support short to ground fault 
   FAULT_SUPPORTED_OPEN_CIRCUIT           = 11, // @emem Support open circuit fault 
   FAULT_SUPPORTED_SHORT_TO_BATTERY       = 12, // @emem Support short to battery fault 
   FAULT_SUPPORTED_THERMAL                = 13, // @emem Support over temp fault 
   FAULT_SUPPORTED_VOLTAGE_REGULATION     = 14, // @emem Support Voltage Out of Regulation fault 
   FAULT_ENABLED                          = 15  // @emem faults enabled for this channel

}  FAULT_T;

#define FAULT_OCCURED_SHORT_TO_GROUND_SET  0x0001
#define FAULT_OCCURED_OPEN_CIRCUIT_SET  0x0002
#define FAULT_OCCURED_SHORT_TO_BATTERY_SET  0x0004
#define FAULT_TESTED_SHORT_TO_GROUND_SET  0x0020
#define FAULT_TESTED_OPEN_CIRCUIT_SET  0x0040
#define FAULT_TESTED_SHORT_TO_BATTERY_SET  0x0080

#define FAULT_Set_Enable( x, y ) \
   ( Insert_Bits( x, y, FAULT_ENABLED, BIT_1 ))

#define FAULT_Get_Enable( x ) \
   ( Extract_Bits( x, FAULT_ENABLED, BIT_1 ))

//=============================================================================
// FAULT_Set_Result
//
// @func Sets a specific fault based on the values passed in.
//
// @parm uint32_t | x | old value
//
// @parm bool | y | A <t bool> fault diagnostic for the channel
//
// @parm uint32_t | z | the position
//
// @rdesc new value
//
// @end
//=============================================================================
#if ( ( config_Compiler_Vendor == option_DIABDATA_5_3 ) || \
      ( config_Compiler_Vendor == option_DIABDATA ) )
#define FAULT_Set_Result(x,y,z) \
   ( Insert_Bits_Macro( x, y, z, 1 ) )
#else
#define FAULT_Set_Result(x,y,z) \
   ( Insert_Bits( x, y, z, 1 ) )
#endif

//=============================================================================
// FAULT_Get_Result
//
// @func Get fault status based on the values passed in.
//
// @parm Fault_Log_T | x | A <t Fault_Log_T> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Result(x,y) \
   (bool)(Fault_Log_T)( Extract_Bits( x, y, 1 ) )

//=============================================================================
// FAULT_Set_Channel_Occured
//
// @func Sets "Occured Position" fault for a channel.
//
// @parm Fault_Log_T | x | A <t Fault_Log_T> fault diagnostics for the channel
//
// @parm Fault_Log_T | y | <t Fault_Log_T> elements
//
// @rdesc <t Fault_Log_T> containing the elements
//
// @end
//=============================================================================
#define FAULT_Set_Channel_Occured(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_OCCURED_POSITION, BIT_5 ) )

//=============================================================================
// FAULT_Get_Channel_Occured
//
// @func Gets the status of "Occured Position" fault for a channel.
//
// @parm Fault_Log_T | x | A <t Fault_Log_T> fault diagnostics for the channel
//
// @rdesc <t Fault_Log_T>
//
// @end
//=============================================================================
#define FAULT_Get_Channel_Occured(x) \
   (Fault_Log_T)( Extract_Bits( x, FAULT_OCCURED_POSITION, BIT_5 ) )

//=============================================================================
// FAULT_Set_Channel_Tested
//
// @func Sets "Tested Position" fault for a channel.
//
// @parm Fault_Log_T | x | A <t Fault_Log_T> fault diagnostics for the channel
//
// @parm Fault_Log_T | y | <t Fault_Log_T> elements
//
// @rdesc <t Fault_Log_T> containing the elements
//
// @end
//=============================================================================
#define FAULT_Set_Channel_Tested(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_TESTED_POSITION, BIT_5 ) )

//=============================================================================
// FAULT_Get_Channel_Tested
//
// @func Gets the status of "Tested Position" fault for a channel.
//
// @parm Fault_Log_T | x | A <t Fault_Log_T> fault diagnostics for the channel
//
// @rdesc <t Fault_Log_T>
//
// @end
//=============================================================================
#define FAULT_Get_Channel_Tested(x) \
   (Fault_Log_T)( Extract_Bits( x, FAULT_TESTED_POSITION, BIT_5 ) )

//=============================================================================
// FAULT_Set_Channel_Supported
//
// @func Sets "Supported Position" fault for a channel.
//
// @parm Fault_Log_T | x | A <t Fault_Log_T> fault diagnostics for the channel
//
// @parm Fault_Log_T | y | <t Fault_Log_T> elements
//
// @rdesc <t Fault_Log_T> containing the elements
//
// @end
//=============================================================================
#define FAULT_Set_Channel_Supported(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_SUPPORTED_POSITION, BIT_5 ) )

//=============================================================================
// FAULT_Get_Channel_Supported
//
// @func Gets the status of "Supported Position" fault for a channel.
//
// @parm Fault_Log_T | x | A <t Fault_Log_T> fault diagnostics for the channel
//
// @rdesc <t Fault_Log_T>
//
// @end
//=============================================================================
#define FAULT_Get_Channel_Supported(x) \
   (Fault_Log_T)( Extract_Bits( x, FAULT_SUPPORTED_POSITION, BIT_5 ) )

//=============================================================================
// FAULT_Set_Occured_Short_To_Ground
//
// @func Sets "Occured Short To Ground" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Occured_Short_To_Ground(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_OCCURED_SHORT_TO_GROUND, 1 ) )

#define FAULT_Clear_Occured_Short_To_Ground(x) \
	 FAULT_Set_Occured_Short_To_Ground(x,false) 
//=============================================================================
// FAULT_Get_Occured_Short_To_Ground
//
// @func Gets the status of "Occured Short To Ground" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Occured_Short_To_Ground(x) \
   (bool)( Extract_Bits( x, FAULT_OCCURED_SHORT_TO_GROUND, 1 ) )

//=============================================================================
// FAULT_Set_Occured_Open_Circuit
//
// @func Sets "Occured Open Circuit" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Occured_Open_Circuit(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_OCCURED_OPEN_CIRCUIT, 1 ) )

#define FAULT_Clear_Occured_Open_Circuit(x) \
	FAULT_Set_Occured_Open_Circuit(x,false)
//=============================================================================
// FAULT_Get_Occured_Open_Circuit
//
// @func Gets the status of "Occured Open Circuit" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Occured_Open_Circuit(x) \
   (bool)( Extract_Bits( x, FAULT_OCCURED_OPEN_CIRCUIT, 1 ) )

//=============================================================================
// FAULT_Set_Occured_Short_To_Battery
//
// @func Sets "Occured Short To Battery" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Occured_Short_To_Battery(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_OCCURED_SHORT_TO_BATTERY, 1 ) )

//=============================================================================
// FAULT_Get_Occured_Short_To_Battery
//
// @func Gets the status of "Occured Short To Battery" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Occured_Short_To_Battery(x) \
   (bool)( Extract_Bits( x, FAULT_OCCURED_SHORT_TO_BATTERY, 1 ) )
   
//=============================================================================
// FAULT_Set_Occured_Thermal
//
// @func Sets "Occured Thermal" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Occured_Thermal(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_OCCURED_THERMAL, 1 ) )

//=============================================================================
// FAULT_Get_Occured_Thermal
//
// @func Gets the status of "Occured Thermal" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Occured_Thermal(x) \
   (bool)( Extract_Bits( x, FAULT_OCCURED_THERMAL, 1 ) )

//=============================================================================
// FAULT_Set_Occured_Voltage_Regulation
//
// @func Sets "Occured Voltage Regulation" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Occured_Voltage_Regulation(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_OCCURED_VOLTAGE_REGULATION, 1 ) )

//=============================================================================
// FAULT_Get_Occured_Voltage_Regulation
//
// @func Gets the status of "Occured Voltage Regulation" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Occured_Voltage_Regulation(x) \
   (bool)( Extract_Bits( x, FAULT_OCCURED_VOLTAGE_REGULATION, 1 ) )

//=============================================================================
// FAULT_Set_Tested_Short_To_Ground
//
// @func Sets "Tested Short To Ground" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Tested_Short_To_Ground(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_TESTED_SHORT_TO_GROUND, 1 ) )

#define FAULT_Clear_Tested_Short_To_Ground(x) \
  	FAULT_Set_Tested_Short_To_Ground(x,false)
//=============================================================================
// FAULT_Get_Tested_Short_To_Ground
//
// @func Gets the status of "Tested Short To Ground" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Tested_Short_To_Ground(x) \
   (bool)( Extract_Bits( x, FAULT_TESTED_SHORT_TO_GROUND, 1 ) )
   
//=============================================================================
// FAULT_Set_Tested_Open_Circuit
//
// @func Sets "Tested Open Circuit" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Tested_Open_Circuit(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_TESTED_OPEN_CIRCUIT, 1 ) )

#define FAULT_Clear_Tested_Open_Circuit(x) \
	FAULT_Set_Tested_Open_Circuit(x,false)
//=============================================================================
// FAULT_Get_Tested_Open_Circuit
//
// @func Gets the status of "Tested Open Circuit" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Tested_Open_Circuit(x) \
   (bool)( Extract_Bits( x, FAULT_TESTED_OPEN_CIRCUIT, 1 ) )
   
//=============================================================================
// FAULT_Set_Tested_Short_To_Battery
//
// @func Sets "Tested Short To Battery" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Tested_Short_To_Battery(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_TESTED_SHORT_TO_BATTERY, 1 ) )

//=============================================================================
// FAULT_Get_Tested_Short_To_Battery
//
// @func Gets the status of "Tested Short To Battery" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Tested_Short_To_Battery(x) \
   (bool)( Extract_Bits( x, FAULT_TESTED_SHORT_TO_BATTERY, 1 ) )

//=============================================================================
// FAULT_Set_Tested_Thermal
//
// @func Sets "Tested Thermal" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Tested_Thermal(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_TESTED_THERMAL, 1 ) )

//=============================================================================
// FAULT_Get_Tested_Thermal
//
// @func Gets the status of "Tested Thermal" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Tested_Thermal(x) \
   (bool)( Extract_Bits( x, FAULT_TESTED_THERMAL, 1 ) )

//=============================================================================
// FAULT_Set_Tested_Voltage_Regulation
//
// @func Sets "Tested Voltage Regulation" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Tested_Voltage_Regulation(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_TESTED_VOLTAGE_REGULATION, 1 ) )

//=============================================================================
// FAULT_Get_Tested_Voltage_Regulation
//
// @func Gets the status of "Tested Voltage Regulation" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Tested_Voltage_Regulation(x) \
   (bool)( Extract_Bits( x, FAULT_TESTED_VOLTAGE_REGULATION, 1 ) )

//=============================================================================
// FAULT_Set_Supported_Short_To_Ground
//
// @func Sets "Supported Short To Ground" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Supported_Short_To_Ground(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_SUPPORTED_SHORT_TO_GROUND, 1 ) )

//=============================================================================
// FAULT_Get_Supported_Short_To_Ground
//
// @func Gets the status of "Supported Short To Ground" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Supported_Short_To_Ground(x) \
   (bool)( Extract_Bits( x, FAULT_SUPPORTED_SHORT_TO_GROUND, 1 ) )

//=============================================================================
// FAULT_Set_Supported_Open_Circuit
//
// @func Sets "Supported Open Circuit" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Supported_Open_Circuit(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_SUPPORTED_OPEN_CIRCUIT, 1 ) )

//=============================================================================
// FAULT_Get_Supported_Open_Circuit
//
// @func Gets the status of "Supported Open Circuit" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Supported_Open_Circuit(x) \
   (bool)( Extract_Bits( x, FAULT_SUPPORTED_OPEN_CIRCUIT, 1 ) )

//=============================================================================
// FAULT_Set_Supported_Short_To_Battery
//
// @func Sets "Supported Short To Battery" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Supported_Short_To_Battery(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_SUPPORTED_SHORT_TO_BATTERY, 1 ) )

//=============================================================================
// FAULT_Get_Supported_Short_To_Battery
//
// @func Gets the status of "Supported Short To Battery" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Supported_Short_To_Battery(x) \
   (bool)( Extract_Bits( x, FAULT_SUPPORTED_SHORT_TO_BATTERY, 1 ) )

//=============================================================================
// FAULT_Set_Supported_Thermal
//
// @func Sets "Supported Thermal" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Supported_Thermal(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_SUPPORTED_THERMAL, 1 ) )

//=============================================================================
// FAULT_Get_Supported_Thermal
//
// @func Gets the status of "Supported Thermal" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Supported_Thermal(x) \
   (bool)( Extract_Bits( x, FAULT_SUPPORTED_THERMAL, 1 ) )

//=============================================================================
// FAULT_Set_Supported_Voltage_Regulation
//
// @func Sets "Supported Voltage Regulation" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint16_t> containing the element <t bool>
//
// @end
//=============================================================================
#define FAULT_Set_Supported_Voltage_Regulation(x,y) \
   (Fault_Log_T)( Insert_Bits( x, y, FAULT_SUPPORTED_VOLTAGE_REGULATION, 1 ) )

//=============================================================================
// FAULT_Get_Supported_Voltage_Regulation
//
// @func Gets the status of "Supported Thermal" fault for a channel.
//
// @parm uint16_t | x | A <t uint16_t> fault diagnostics for the channel
//
// @rdesc <t bool> element decoded from the <t uint16_t>
//
// @end
//=============================================================================
#define FAULT_Get_Supported_Voltage_Regulation(x) \
   (bool)( Extract_Bits( x, FAULT_SUPPORTED_VOLTAGE_REGULATION, 1 ) )
//=============================================================================
//                               FUNCTIONS
//=============================================================================
//=============================================================================
// FAULT_Get_Device_Fault_T
//
// @func Get the status of any fault on the requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc Return true if there is any fault on the device.
//
// @end
//=============================================================================
typedef bool (*FAULT_Get_Device_Fault_T)(
   IO_Configuration_T in_configuration );

//=============================================================================
// FAULT_Clear_Device_Fault_T
//
// @func Clears all faults on a requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
typedef void (*FAULT_Clear_Device_Fault_T)(
   IO_Configuration_T in_configuration );

//=============================================================================
// FAULT_Diagnose_Device_Fault_T
//
// @func Diagnose all faults on a requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
typedef void (*FAULT_Diagnose_Device_Fault_T)(
   IO_Configuration_T in_configuration );

//=============================================================================
// Object Structure Definition
//=============================================================================

typedef struct Fault_Interface_Tag
{
   FAULT_Get_Device_Fault_T            Get_Device_Fault;
   FAULT_Clear_Device_Fault_T          Clear_Device_Fault;
   FAULT_Diagnose_Device_Fault_T       Diagnose_Device_Fault;
} Fault_Interface_T;

// This gets overloaded by the device to store local functions and data.
// The only requirement is to keep the Fault_Interface_T as the first
// member of the structure.
typedef struct Fault_Tag
{
   Fault_Interface_T Fault;

} Fault_T;

typedef struct IO_Fault_Tag
{
   IO_Configuration_T   Configuration;
   const uint32_t      *reserved_0;
   const uint32_t      *reserved_1;
   const uint32_t      *reserved_2;
   Fault_Log_T         *Fault_Log;     //Ram value pointer to fault log information
   const Fault_T       *F;

}  IO_Fault_T;

#endif // FAULT_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date        By         Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14  WSQ     Created the initial version for MT22p1 based on MT80
 * mt20u2#442  09/10/19  MaKun  FAULT_Set_Enable() QAC warning Msg(2:3411)correction
\*===========================================================================*/


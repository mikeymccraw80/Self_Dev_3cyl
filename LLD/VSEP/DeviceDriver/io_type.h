#ifndef IO_TYPE_H
#define IO_TYPE_H
//=============================================================================
//
//       COPYRIGHT, 2003, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            io_type.h %
//
// created_by:       jwyrick
//
// date_created:     Thu Jul 24 08:09:11 2003
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Thursday, March 08, 2007 5:03:47 PM %
//
// %version:         5 %
//
// ============================================================================
// @doc
//   ???????? ask Jay
// @module io_type.h |
//
// The purpose of this module is to provide type information to the IO layer.
//
// @normal Copyright <cp> 2003, Delphi Technologies, Inc. All Rights reserved
//
// @end
//
//=============================================================================
#include "reuse.h"

#define HW_SOH_DISABLE
#define VSEP_CALIBRATION_ENABLE  1
#define FAR_COS

//
// @enum IO_TOS_T | Defines the different SRC selection modes
//
typedef enum
{
   IO_TOS_CPU,  // @emem Use --- CPU
   IO_TOS_PCP,  // @emem Use --- PCP
   IO_TOS_RES0, // @emem Use --- reserved
   IO_TOS_RES1  // @emem Use --- reserved
} IO_TOS_T;


//
// @enum Edge_T | Defines the edge to trigger the pulse on
//
typedef enum
{
   IO_EDGE_NONE,     // @emem No edge to trigger on - disabled
   IO_EDGE_RISING,   // @emem Trigger on Rising edge only
   IO_EDGE_FALLING,  // @emem Trigger on Falling edge only
   IO_EDGE_BOTH      // @emem Trigger on the rising and falling edges

}  IO_Edge_T;


//
// @enum IO_Time_T | Defines relative or absolute time settings to a timer.
//
typedef enum
{
   IO_TIME_ABSOLUTE,          // @emem Actual time value
   IO_TIME_RELATIVE,          // @emem Relative to current value of the timer
   IO_TIME_RELATIVE_LAST_EDGE // @emem Relative to last edge value of the timer

}  IO_Time_T;

//
// @enum IO_Data_Direction_T | Defines the data direction of a signal
//
typedef enum
{
   IO_DATA_IN,     // @emem Data is entering the part
   IO_DATA_OUT     // @emem Data is leaving the part.

}  IO_Data_Direction_T;

//
// @enum IO_Polarity_T | Defines the voltage output of an active state.
//
typedef enum
{
   IO_ACTIVE_LOW, // @emem Output is 0 (0v) when active, 1 (5v,3.3v) when inactive.
   IO_ACTIVE_HIGH // @emem Output is 1 (5v,3.3v) when active, 0 (0v) when inactive.

}  IO_Polarity_T;


//
// @enum IO_Active_State_T | Defines the .
//
typedef enum
{
   IO_INACTIVE,   // @emem State of the channel or pin is inactive.
   IO_ACTIVE      // @emem State of the channel or pin is active.

}  IO_Active_State_T;


//
// @enum TimerSize_T | Defines the size of a timer in bits
//
typedef enum
{
   IO_TIMER_2_BIT    =  2, // @emem  2 bit timer stored in a 8 bit value
   IO_TIMER_3_BIT    =  3, // @emem  3 bit timer stored in a 8 bit value
   IO_TIMER_6_BIT    =  6, // @emem  6 bit timer stored in a 8 bit value
   IO_TIMER_8_BIT    =  8, // @emem  8 bit timer
   IO_TIMER_11_BIT   = 11, // @emem 11 bit timer
   IO_TIMER_12_BIT   = 12, // @emem 12 bit timer stored in a 16 bit value
   IO_TIMER_16_BIT   = 16, // @emem 16 bit timer
   IO_TIMER_18_BIT   = 18, // @emem 18 bit timer
   IO_TIMER_22_BIT   = 22, // @emem 22 bit timer
   IO_TIMER_24_BIT   = 24, // @emem 24 bit timer stored in a 32 bit value
   IO_TIMER_32_BIT   = 32, // @emem 32 bit timer
   IO_TIMER_40_BIT   = 40, // @emem 40 bit timer
   IO_TIMER_48_BIT   = 48, // @emem 48 bit timer
   IO_TIMER_56_BIT   = 56, // @emem 56 bit timer
   IO_TIMER_64_BIT   = 64  // @emem 64 bit timer

}  IO_Timer_Size_T;

//
// @struct PWM_Data_T | Used for PWM information
//
typedef struct
{
   uint32_t        Period;           // @field Period
   uint32_t        Duty_Cycle;       // @field Duty cycle, 0=0%, 0xFFFF=100%

}  PWM_Data_T;

//
// @struct IO_Array_T | Used for controlled array size
//
typedef struct 
{
   uint8_t  Size;    // @field size of the array using sizeof(array)/sizeof(type),
   void    *Array;   // @field put the array name here.

} IO_Array_T;



//=============================================================================
// Interrupt Service Request Control Callback
//=============================================================================
//typedef void (*IO_Callback_T)(void);

//typedef void* HANDLE;

typedef void const * HIODEVICE;

/*typedef void (*Vector_Callback_T)(void*);

typedef struct Vector_Callback_Table_Tag
{
   Vector_Callback_T vector_callback;
   void             *vector_argument;

}  Vector_Callback_Table_T;
   

*/
//=============================================================================
// @enum IO_Fault_Status_T | Fault Status type
//=============================================================================
typedef enum IO_Fault_Status_Tag
{
   IO_FAULT_STATUS_INACTIVE,              // @emem Requested fault type is currently not active
   IO_FAULT_STATUS_ACTIVE,                // @emem Requested fault type is currently active
   IO_FAULT_STATUS_UNSUPPORTED,           // @emem Requested fault type is unsupported
   IO_FAULT_STATUS_UNTESTED               // @emem Requested fault type is untested

}  IO_Fault_Status_T;

//=============================================================================
// @enum IO_Timer_State_T | Timer State indication type
//=============================================================================
typedef enum IO_Timer_State_Tag
{
   IO_TIMER_STATE_RESET,                  // @emem Timer is currently not active ( in reset )
   IO_TIMER_STATE_RUNNING,                // @emem Timer is currently active ( running )
   IO_TIMER_STATE_OVERFLOW,               // @emem Timer overflow occured
   IO_TIMER_STATE_UNDERFLOW               // @emem Timer underflow occured

}  IO_Timer_State_T;

//=============================================================================
//  IO_Configuration_T A configurable value set in
//          io_type.h that specifies the device type, device number,
//          pin output, and device specific information..
//
//=============================================================================
typedef uint32_t IO_Configuration_T;

typedef uint32_t 	IO_mask_T;
#define Cast_IO_Configuration(x) ((IO_Configuration_T)(x))

//
// place the device type into the configuration field. 0x00 to 0x1F
// Allows up to 32 different device types.
//
#define IO_Set_Device(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, 27, 5 ) )
#define IO_Get_Device(x) \
   ( Extract_Bits( x, 27, 5 ) )


//=============================================================================
//  This section provides the information needed for a specific compiler and
// hardware architecture
//
//=============================================================================

//=============================================================================
// _DEBUG_
// This defines is used to turn the debugging features on or off.
//
//=============================================================================
//#define _DEBUG_ 1

//=============================================================================
// Generate_Compiler_Error
//    This name is used in some files to cause a complier error. When we are
// debugging we dont want this to occur. ( + I dont think this works anyway.
//=============================================================================
#ifdef _DEBUG_
#define Generate_Compiler_Error( x )
#endif

//=============================================================================
// Get_This_Pointer
//
//    This macro is used to downcast an object structure.
//
//=============================================================================
#define Get_This_Pointer( pointer, object_type ) ((object_type*)pointer)

//=============================================================================
// ASSERT
//
//    This macro/function is used to provide debugging support. When the
// inIsValid value is flase, the function will stay here forever.
//
//=============================================================================
#ifdef _DEBUG_
INLINE
void ASSERT( bool      inIsValid )
{
   if( !inIsValid )
   {
      while(1);// should stick the debug instruction here.
   }
}
#else
#define ASSERT( inIsValid ) // Non Debug
#endif

//=============================================================================
// IMPLEMENT_DEBUG_OBJECT_ID
//
//    This macro is used to define an object type id based on the type name
//
//=============================================================================
#ifdef _DEBUG_
#define IMPLEMENT_DEBUG_OBJECT_ID( object_type ) object_type##_ID
#else
#define IMPLEMENT_DEBUG_OBJECT_ID( object_type ) // Non Debug
#endif

//=============================================================================
// SET_DEBUG_OBJECT_ID
// This sets the appropriate debug object type to the correct object variable
//
//=============================================================================
#ifdef _DEBUG_
#define SET_DEBUG_OBJECT_ID( object, object_type ) \
   ((object_type*)object)->ObjectId = IMPLEMENT_DEBUG_OBJECT_ID( object_type ) 
#else
#define SET_DEBUG_OBJECT_ID( object, object_type ) // Non Debug
#endif

//=============================================================================
// DEBUG_OBJECT_Type
//
//    This enumeration lists all the objects in defined.
//
// This is manual process the user must add a new object to this list before
// the object can be valid.
//
//=============================================================================
#ifdef _DEBUG_
typedef enum _tagObjectTypes
{
   IMPLEMENT_DEBUG_OBJECT_ID( DEVICE_DATA_T ),
   IMPLEMENT_DEBUG_OBJECT_ID( FLASH_DATA_T ),
   IMPLEMENT_DEBUG_OBJECT_ID( AMD_AM29BL802C_DATA_T ),
   IMPLEMENT_DEBUG_OBJECT_ID( SDLMData_T )
} DebugObject_T;
#endif

//=============================================================================
// DECLARE_DEBUG_OBJECT_ID
//
//    This macro is used to declare the object type id variable in the
// objects structure.
//=============================================================================
#ifdef _DEBUG_
#define DECLARE_DEBUG_OBJECT_ID DebugObject_T ObjectId // identifer of the structure
#else
#define DECLARE_DEBUG_OBJECT_ID // Non Debug
#endif


//=============================================================================
// ASSERT_VALID_OBJECT
//
//    This macro is used for debugging objects declared with
// DECLARE_DEBUG_OBJECT_ID macro. If a pointer is passed to the
// ASSERT_VALID_OBJECT is not of the same type as the object type argument
// an assertion will occur.
//
//=============================================================================
#ifdef _DEBUG_
#define ASSERT_VALID_OBJECT( pointer, object_type )\
{\
   if( ((object_type*)pointer)->ObjectId != object_type##_ID )\
   {\
      ASSERT( false );\
   }\
}
#else
#define ASSERT_VALID_OBJECT( pointer, object_type ) // Non Debug
#endif

//=============================================================================
// ASSERT_VALID_POINTER
//
//    This macro is used for debugging objects declared with
// DECLARE_DEBUG_OBJECT_ID macro. If a pointer is passed to the
// ASSERT_VALID_OBJECT is not of the same type as the object type argument
// an assertion will occur.
//
//=============================================================================
#ifdef _DEBUG_
#define ASSERT_VALID_POINTER( pointer )\
{\
   if( NULL == pointer )\
   {\
      ASSERT( false );\
   }\
}
#else
#define ASSERT_VALID_POINTER( pointer ) // Non Debug
#endif

// @enum Cause_Of_Reset_T | enumeration containing causes of resets and traps.
typedef enum Cause_Of_Reset_Tag
{
   
   // Resets
   CAUSE_OF_RESET_POWERON_RST = 1,          // Power ON reset
   CAUSE_OF_RESET_HARDWARE_RST,             // Hardware Reset
   CAUSE_OF_RESET_SOFTWARE_RST,             // Software Reset
   CAUSE_OF_RESET_WATCHDOG_RST,             // Watchdog Reset
   
   // Following enums are used to indicate the exact cause of Traps generataed
   // by hw or sw. The cause of the trap is interpreted based on the Trap
   // Identification Number (TIN) stored by the controller.

   // Class 0 MMU traps
   CAUSE_OF_RESET_VIRTUAL_ADDR_FILL,        // TIN = 0: Virtual address fill 
   CAUSE_OF_RESET_VIRTUAL_ADDR_PROT,        // TIN = 1: Virtual address protection

   // Class 1 Internal Protection traps
   CAUSE_OF_RESET_PRIVIL_INSTR,             // TIN = 1: Previlage Violation 
   CAUSE_OF_RESET_MEM_PROT_READ,            // TIN = 2: Data read from protected area.
   CAUSE_OF_RESET_MEM_PROT_WRITE,           // TIN = 3: Data write to protected area.
   CAUSE_OF_RESET_MEM_PROT_EXEC,            // TIN = 4: Code read from proteced area
   CAUSE_OF_RESET_MEM_PROT_PERIPH_ACCESS,   // TIN = 5: Access to peripheral address.
   CAUSE_OF_RESET_MEM_PROT_NULL_ADDR,       // TIN = 6: Load/Store to effective address 0
   CAUSE_OF_RESET_WRITE_PROT_GLBL_REG,      // TIN = 7: Access to protected GPR (A0,A1,A8,A9)

   // Class 2 Instruction Error traps
   CAUSE_OF_RESET_ILLEGAL_OPCODE,           // TIN = 1: Illegal opcode executed.
   CAUSE_OF_RESET_UNIMPL_OPCODE,            // TIN = 2: Unimplemented opcode executed.
   CAUSE_OF_RESET_INVALID_OPERAND,          // TIN = 3: Invalid operand specification.
   CAUSE_OF_RESET_DATA_ADDR_ALIGN_ERR,      // TIN = 4: Violation of alignment rule.
   CAUSE_OF_RESET_INVALID_LOCAL_MEM_ADDR,   // TIN = 5: Invalid memory access.

   // Class 3 Context Management traps
   CAUSE_OF_RESET_FREE_CXT_LIST_DEPLETED,   // TIN = 1: Free Context List depleted 
   CAUSE_OF_RESET_CALL_DEPTH_OVERFLOW,      // TIN = 2: Call depth Counter Overflow.
   CAUSE_OF_RESET_CALL_DEPTH_UNDRFLOW,      // TIN = 3: Call depth Counter Underflow.
   CAUSE_OF_RESET_FREE_CXT_LIST_UNDRFLOW,   // TIN = 4: Free Context List empty
   CAUSE_OF_RESET_CALL_STACK_UNDRFLOW,      // TIN = 5: Call Stack Underflow.
   CAUSE_OF_RESET_CXT_TYPE_ERR,             // TIN = 6: Context Type Error.
   CAUSE_OF_RESET_NESTING_ERR,              // TIN = 7: Nesting Error.

   // Class 4 System Bus & Peri Errors
   CAUSE_OF_RESET_PROG_FETCH_BUS_ERR,       // TIN = 1: Program Fetch Bus Error 
   CAUSE_OF_RESET_DFLASH_SGLBIT_ERR,        // Dflash Single bit error
   CAUSE_OF_RESET_DFLASH_DBLBIT_ERR,		// Dflash Double bit error
   CAUSE_OF_RESET_PFLASH_SGLBIT_ERR,		// Pflash Single bit error
   CAUSE_OF_RESET_PFLASH_DBLBIT_ERR,		// Pflash Double bit error
   CAUSE_OF_RESET_DATA_LOAD_BUS_ERR,        // TIN = 2: Data Load Bus Error.
   CAUSE_OF_RESET_DATA_STORE_BUS_ERR,       // TIN = 3: Data Store Bus Error.

   // Class 5 Assertion
   CAUSE_OF_RESET_ARITH_OVERFLOW,           // TIN = 1: Arithmatic Overflow. 
   CAUSE_OF_RESET_STICKY_ARITH_OVERFLOW,    // TIN = 2: Sticky Arithmatic Overflow.

   // Class 6 System Call traps
   CAUSE_OF_RESET_SYS_CALL,                 // TIN = 1: System Call	                

   // Class 7 Non Maskable Interrupt        // TIN = 0
   CAUSE_OF_RESET_NMI_WDT,                  // WDT time out / access error
   CAUSE_OF_RESET_NMI_PLL,                  // PLL loss of lock
   CAUSE_OF_RESET_NMI_EXTERNAL,             // Transition on NMI pin
   CAUSE_OF_RESET_NMI_SRAM_DRAM_PERR,       // SRAM parity error in Data RAM
   CAUSE_OF_RESET_NMI_SRAM_SCRATCHPAD_PERR, // SRAM parity error in ScratchPad
   CAUSE_OF_RESET_NMI_SRAM_PROGTAG_PERR,    // SRAM parity error Program Tag
   CAUSE_OF_RESET_NMI_SRAM_PCPRAM_PERR,     // SRAM parity error in PCP RAM
   CAUSE_OF_RESET_NMI_SRAM_PCPCODE_PERR,    // SRAM parity error in PCP Code Memory
   CAUSE_OF_RESET_NMI_SRAM_CANMEM_PERR      // SRAM parity error in CAN memory

}  Cause_Of_Reset_T ;

typedef enum RESET_Tag
{
   INT_WDT, /* MCU watchdog */
   HFPS_COP /* TLE4471 COP */
}  COP_RESET_T;


typedef void (*Cause_Of_Reset_Callback_T)(Cause_Of_Reset_T in_cause_of_reset, uint32_t reset_address );

/*===========================================================================*\
 * @enum IO_Fault_Request_T | Type of fault to request
\*===========================================================================*/
typedef enum IO_Fault_Request_Tag
{
   IO_FAULT_TESTED_GENERAL_FAULTS,       /* @emem Request general faults test conditions met */
   IO_FAULT_REQUEST_GENERAL_FAULT        /* @emem Request general fault status */
} IO_Fault_Request_T;

typedef void (*Flash_Error_Callback_T)(Cause_Of_Reset_T in_cause_of_reset);

#endif // IO_TYPE_H


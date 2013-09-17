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


#endif // IO_TYPE_H

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

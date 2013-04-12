
#ifndef REUSE_H
#define REUSE_H

//=============================================================================
// Include Files
//=============================================================================
#include "e200z3.h"
#include "powerpc_diabdata.h"
#include "powerpc_diabdata_types.h"
#include "powerpc_diabdata_copy.h"


//=============================================================================
// /------------------------------------------------------------------------
// |                 Standard Preprocessor Definitions
// \------------------------------------------------------------------------
// ============================================================================
// StandardPreprocessor Definitions are placed here to allow specific
// compiler/processor choices to override the defaults.
//=============================================================================

//per 7.18 of the ANSI/ISO Standard
#ifndef UINT8_MIN
#define UINT8_MIN      (0)             // Minimum value for uint8_t
#endif
#ifndef UINT8_MAX
#define UINT8_MAX      (0xffU)         // Maximum value for uint8_t
#endif

#ifndef UINT16_MIN
#define UINT16_MIN     (0)             // Minimum value for uint16_t
#endif
#ifndef UINT16_MAX
#define UINT16_MAX     (0xffffU)       // Maximum value for uint16_t
#endif

#ifndef UINT24_MIN
#define UINT24_MIN     (0)             // Minimum value for uint32_t containing 24 bits
#endif
#ifndef UINT24_MAX
#define UINT24_MAX     (0x00ffffffU)   // Maximum value for uint32_t containing 24 bits
#endif

#ifndef UINT32_MIN
#define UINT32_MIN     (0)             // Minimum value for uint32_t
#endif
#ifndef UINT32_MAX
#define UINT32_MAX     (0xffffffffU)   // Maximum value for uint32_t
#endif


#ifndef INT8_MIN
#define INT8_MIN      (-INT8_MAX-1)    // Minimum value for int8_t
#endif
#ifndef INT8_MAX
#define INT8_MAX      (127)            // Maximum value for int8_t
#endif

#ifndef INT16_MIN
#define INT16_MIN     (-INT16_MAX-1)   // Minimum value for int16_t
#endif
#ifndef INT16_MAX
#define INT16_MAX     (32767)          // Maximum value for int16_t
#endif

#ifndef INT24_MIN
#define INT24_MIN     (-INT24_MAX-1)   // Minimum value for int32_t containing 24 bits
#endif
#ifndef INT24_MAX
#define INT24_MAX     (8388607)        // Maximum value for int32_t containing 24 bits
#endif

#ifndef INT32_MIN
#define INT32_MIN     (-INT32_MAX-1)   // Minimum value for int32_t
#endif
#ifndef INT32_MAX
#define INT32_MAX     (2147483647)     // Maximum value for int32_t
#endif

#ifndef SIG_ATOMIC_SIZE
#define SIG_ATOMIC_SIZE    (8*sizeof(sig_atomic_t))
#endif
#ifndef SIG_ATOMIC_MIN
#define SIG_ATOMIC_MIN     UINT8_MIN
#endif
#ifndef SIG_ATOMIC_MAX
#define SIG_ATOMIC_MAX     UINT8_MAX
#endif


//
// Max function.
//
#ifndef Max
#define Max(a,b) ( ( (a)>(b) )?(a):(b) ) 
#endif

//
// Min function.
//
#ifndef Min
#define Min(a,b) ( ( (a)<(b) )?(a):(b) ) 
#endif

#ifndef BIT_T
#define BIT_T
//
// @enum Bit_T | Defines the position of the bits
//
typedef enum
{
   BIT_0,   // @emem Bit Position  0
   BIT_1,   // @emem Bit Position  1
   BIT_2,   // @emem Bit Position  2
   BIT_3,   // @emem Bit Position  3
   BIT_4,   // @emem Bit Position  4
   BIT_5,   // @emem Bit Position  5
   BIT_6,   // @emem Bit Position  6
   BIT_7,   // @emem Bit Position  7
   BIT_8,   // @emem Bit Position  8
   BIT_9,   // @emem Bit Position  9
   BIT_10,  // @emem Bit Position 10
   BIT_11,  // @emem Bit Position 11
   BIT_12,  // @emem Bit Position 12
   BIT_13,  // @emem Bit Position 13
   BIT_14,  // @emem Bit Position 14
   BIT_15,  // @emem Bit Position 15
   BIT_16,  // @emem Bit Position 16
   BIT_17,  // @emem Bit Position 17
   BIT_18,  // @emem Bit Position 18
   BIT_19,  // @emem Bit Position 19
   BIT_20,  // @emem Bit Position 20
   BIT_21,  // @emem Bit Position 21
   BIT_22,  // @emem Bit Position 22
   BIT_23,  // @emem Bit Position 23
   BIT_24,  // @emem Bit Position 24
   BIT_25,  // @emem Bit Position 25
   BIT_26,  // @emem Bit Position 26
   BIT_27,  // @emem Bit Position 27
   BIT_28,  // @emem Bit Position 28
   BIT_29,  // @emem Bit Position 29
   BIT_30,  // @emem Bit Position 30
   BIT_31,  // @emem Bit Position 31
   BIT_MAX  // @emem 32 Bits

} bit_t;

#endif

/*===========================================================================*/
/* DD_FAULT_RESULT_T    Type of fault to request                             */
/*===========================================================================*/
typedef enum EMS_DIAGNOSTIC_Tag
{
   OUTPUT_OPEN_CKT_FAULT,      /* Request open circuit fault    */
   OUTPUT_OPEN_CKT_TESTED,
   OUTPUT_SHORT_CKT_FAULT,     /* Request short circuit fault   */
   OUTPUT_SHORT_CKT_TESTED,
   OUTPUT_GEN_FLT_PRESENT,
   OUTPUT_GEN_FLT_TESTED,
   OUTPUT_OVERTEMP_FAULT,      /* Request over voltage fault    */
   OUTPUT_VOLTAGE_FAULT,       /* Request Voltage fault         */
   OUTPUT_UNDERVOLT_FAULT,     /* Request under voltage fault   */
   OUTPUT_CLOCK_FAULT,         /* Request Clock fault status    */
   OUTPUT_CONTROL_ALLOWED      /* Request to allow control      */
}  EMS_DIAGNOSTIC_T;

#define EMS_Diagnostic_T   EMS_DIAGNOSTIC_T


//=============================================================================
//                         Edge Information
//=============================================================================

//
// @enum Edge_T | Defines the edge to trigger the pulse on
//
typedef enum
{
   EDGE_NONE,     // @emem No edge to trigger on - disabled
   EDGE_RISING,   // @emem Trigger on Rising edge only
   EDGE_FALLING,  // @emem Trigger on Falling edge only
   EDGE_BOTH      // @emem Trigger on the rising and falling edges

}  Edge_T;


typedef struct
{
   uint32_t          Count;          // Edge count
   uint32_t          Time;           // Edge time
   bool                Valid_Edge;     // Set first time a valid edge isseen
   uint16_t          Zero_Edge_Count;// Background counter incremented
                                     // in a periodic loop and cleared
                                     // on each edge.

}  Edge_Data_T;

//
// @struct PulseData_T | Used for PWM single pulse edge information
//
typedef struct
{
   Edge_Data_T  Rising;    // @field Rising  edge data
   Edge_Data_T  Falling;   // @field Falling edge data

}  Pulse_Data_T;


//
// @struct PulseHistory_T | Used for PWM history information
//
typedef struct
{
   Pulse_Data_T   Current;       // @field Current  pulse data
   Pulse_Data_T   Previous;      // @field Previous pulse data
   Edge_T         Current_Edge;  // @field the edge that just occured.


}  Pulse_History_T;



//
// @enum TimerSize_T | Defines the size of a timer in bits
//
typedef enum
{
   TIMER_0_BIT    =  0, // @emem  0 bit timer
   TIMER_2_BIT    =  2, // @emem  2 bit timer stored in a 8 bit value
   TIMER_3_BIT    =  3, // @emem  3 bit timer stored in a 8 bit value
   TIMER_6_BIT    =  6, // @emem  6 bit timer stored in a 8 bit value
   TIMER_8_BIT    =  8, // @emem  8 bit timer
   IMER_11_BIT   = 11, // @emem 11 bit timer
   TIMER_12_BIT   = 12, // @emem 12 bit timer stored in a 16 bit value
   TIMER_16_BIT   = 16, // @emem 16 bit timer
   TIMER_18_BIT   = 18, // @emem 18 bit timer
   IMER_22_BIT   = 22, // @emem 22 bit timer
   TIMER_24_BIT   = 24, // @emem 24 bit timer stored in a 32 bit value
   TIMER_32_BIT   = 32, // @emem 32 bit timer
   TIMER_40_BIT   = 40, // @emem 40 bit timer
   TIMER_48_BIT   = 48, // @emem 48 bit timer
   TIMER_56_BIT   = 56, // @emem 56 bit timer
   TIMER_64_BIT   = 64  // @emem 64 bit timer

}  Timer_Size_T;

//=============================================================================
// @enum IO_Timer_State_T | Timer State indication type
//=============================================================================
typedef enum Timer_State_Tag
{
   TIMER_STATE_RESET,                  // @emem Timer is currently not active ( in reset )
   TIMER_STATE_RUNNING,                // @emem Timer is currently active ( running )
   TIMER_STATE_OVERFLOW,               // @emem Timer overflow occured
   TIMER_STATE_UNDERFLOW               // @emem Timer underflow occured

}  Timer_State_T;

//
// @enum IO_Polarity_T | Defines the voltage output of an active state.
//
typedef enum
{
   ACTIVE_LOW, // @emem Output is 0 (0v) when active, 1 (5v,3.3v) when inactive.
   ACTIVE_HIGH // @emem Output is 1 (5v,3.3v) when active, 0 (0v) when inactive.

}  Polarity_T;

typedef void (*IO_Callback_T)(void);

#define Cast_bitfield32(x) ((bitfield32_t)(x))
#define Cast_bitfield16(x) ((bitfield16_t)(x))
#define Cast_bitfield8(x)  ( (bitfield8_t)(x))

#define Cast_uint8(x)          ( (uint8_t)(x))
#define Cast_uint16(x)         ((uint16_t)(x))
#define Cast_uint32(x)         ((uint32_t)(x))

#define Cast_int8(x)            ( (int8_t)(x))
#define Cast_int16(x)           ((int16_t)(x))
#define Cast_int32(x)           ((int32_t)(x))

#define NULL            0
#if 0
#define Extract_Bits(value,position,width) (((value) & Mask32((position), (width))) >> (position))
#define Insert_Bits(old_value,value,position,width)  (Zero_Bits_Macro((old_value),(position),(width)) | (((value) << (position)) & Mask32((position),(width))) )

#define Zero_Bits_Macro(value,position,width)   (uint32_t)(~(Mask32((position),(width))) & (value))

#define Mask32(in_position,in_width)\
   (uint32_t)(((1 << (in_width)) - 1) << (in_position))
#define Mask16(in_position,in_width)\
   (uint16_t)(((1 << (in_width )) - 1) << (in_position))
#define Mask8(in_position,in_width)\
   (uint8_t)((( 1 << (in_width)) - 1) << (in_position))
#endif

//=============================================================================
// Mask32
//=============================================================================
#define Mask32( in_position, in_width ) \
   (uint32_t)( ( ( ( ( ( 1UL << ( (uint32_t)(in_width) ) ) ) - 1U ) & UINT32_MAX ) << ( (uint32_t)(in_position) ) ) & UINT32_MAX )

//=============================================================================
// Mask16
//=============================================================================
#define Mask16( in_position, in_width ) \
   (uint16_t)( ( (uint16_t)( ( ( ( 1U << (  in_width ) ) ) - 1U ) & UINT16_MAX ) << ( in_position ) ) & UINT16_MAX )

//=============================================================================
// Mask8
//=============================================================================
#define Mask8( in_position, in_width ) \
   (uint8_t)( ( (uint8_t)( ( ( 1U << ( in_width ) ) - 1U ) & UINT8_MAX ) << ( in_position ) ) & UINT8_MAX )


#define Zero_Bits_Macro(value,position,width)    (uint32_t)( ~( Mask32( position, width ) ) & (value) )


#define  Insert_Bits(old_value,value,position,width) ( Zero_Bits_Macro(old_value,position,width) | ( ( value << position ) & Mask32( position, width ) ) )

#define Extract_Bits(value,position,width) ( ( value & Mask32( position, width ) ) >> position )


#endif // REUSE_H


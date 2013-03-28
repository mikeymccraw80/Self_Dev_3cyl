#ifndef DD_MCD5412_H
#define DD_MCD5412_H

#include "dd_tpu.h"
#include "mcd5412.h"

//=============================================================================
// Macro Definitions                                                           
//=============================================================================
#define MCD5412_TIMER_MAX                             ( 0x00FFFFFF )

// Maximum value of pulse On time / Off time
#define MCD5412_TIMER_MAX_DIV_BY_2                    ( 0x007FFFFF )

// Limit the value to TIMER_MAX 
#define MCD5412_LIMIT_TO_TIMER_SIZE(x)                ( (x) & ( MCD5412_TIMER_MAX ) )

// Limit the value to Range maximum value
#define MCD5412_LIMIT_TO_TIMER_MAX_DIV_BY_2(value)    ((value) & (MCD5412_TIMER_MAX_DIV_BY_2))

// @enum MPTAC_Time_Mode_T | Defines mode for time and angle calculation options
typedef enum
{
   MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME,         // @emem The cpu calling function will calculate the start time.
   MPTAC_TIME_MODE_CPU_CALCULATES_END_TIME,        // @emem The cpu calling function will calculate the end time.
   MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_START_TIME,   // @emem The primitive will calculate the time.
   MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_END_TIME,  // @emem The primitive will calculate the angle.
   MPTAC_TIME_MODE_MAX

}  MPTAC_Time_Mode_T;

// @enum MPTAC_Flags_T | Defines MPTAC flags
typedef enum
{
   MPTAC_REQ_OUT_OF_RANGE_FLAG,         // @emem 
   MPTAC_MULTI_PULSE_MODE_FLAG,        // @emem 
   MPTAC_DIG_SHUTOFF_ENABLED_FLAG      // @emem 
}  MPTAC_Flags_T;


#endif // DD_MCD5412_H

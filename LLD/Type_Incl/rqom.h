#ifndef RQOM_H
#define RQOM_H

#include "reuse.h"


//============================================================== 
//   Type declarations                                            MCD MCD MCD MCD MCD MCD MCD MCD
//==============================================================   5   5   5   5   5   5   4   4
// @enum Rqom_Flag_T | Defines flag position in the 32 bit uint    4   4   4   4   4   4   4   4
typedef enum                                           //          0   1   1   1   1   5   0   0
{                                                      //          6   3   4   5   9   1   6   7
                                                       // 
   RQOM_FLAG_DELAY_UPDATE,                             // @emem    -   -   -   y   -   -   -   -
   RQOM_FLAG_ENABLE_STOP_STATE,                        // @emem    -   -   -   y   y   -   -   -
   RQOM_FLAG_STOPPED_PIN_STATE,                        // @emem    -   -   -   y   y   -   -   -
   RQOM_FLAG_STOP_IMMEDIATE,                           // @emem    -   -   -   y   y   -   -   -
   RQOM_FLAG_DESIRED_PIN_STATE,                        // @emem    -   -   -   y   y   y   -   -
   RQOM_FLAG_ENABLE_INIT_STATE,                        // @emem    -   -   -   y   y   -   -   -
   RQOM_FLAG_INIT_PIN_STATE,                           // @emem    -   -   -   y   y   y   y   -
   RQOM_FLAG_USE_START_EVENT,                          // @emem    y   Y   Y   -   -   y   y   -
   RQOM_FLAG_ENABLE_DROPPED_EVENTS,                    // @emem    -       Y   -   -   -       -
   RQOM_FLAG_START_EVENT_USES_POINTER,                 // @emem    y   Y   Y   -   -   y   y   -
   RQOM_FLAG_START_EVENT_ACTIVE_STATE,                 // @emem    y   Y   Y   -   -   -   y   -
   RQOM_FLAG_USE_END_EVENT,                            // @emem    y   -   y   -   -   Y   y   -
   RQOM_FLAG_END_EVENT_USE_ALTERNATE_TIMER,            // @emem    y   -   y   -   -   Y   y   -
   RQOM_FLAG_END_EVENT_CAPTURE_ALTERNATE_TIMER,        // @emem    -   -   -   -   -   Y   y   -
   RQOM_FLAG_END_EVENT_STORE_ACTUAL,                   // @emem    y   -   y   -   -   y       -
   RQOM_FLAG_END_EVENT_ACTIVE_STATE,                   // @emem    y   -   y   -   -   y   y   -
   RQOM_FLAG_END_EVENT_REQUEST_DMA,                    // @emem    y   -   -   -   -   y   y   -
   RQOM_FLAG_END_EVENT_REQUEST_INTERRUPT,              // @emem    y   -   y   -   -   y   y   -
   RQOM_FLAG_STATUS_LOOP_RUNNING,                      // @emem    y   -   -   -   -   y   y   -
   RQOM_FLAG_STATUS_DMA_SCHEDULED,                     // @emem    y   -   -   -   -   y   y   -
   RQOM_FLAG_STATUS_INTERRUPT_SCHEDULED,               // @emem    -   -   -   -   -   y   y   -
   RQOM_FLAG_STATUS_END_EVENT_SETUP,                   // @emem    -   -   -   -   -   -   y   -
   RQOM_FLAG_STATUS_MATCH_FOLLOWING_NEXT_EVENT_INVALID,// @emem    -   -   Y   -   -   -   y   -
   RQOM_FLAG_STATUS_DUAL_ACTION_LAST_MATCH_A,          // @emem    -   -   -   -   -   -   -   -
   RQOM_FLAG_STATUS_PKHLD,                             // @emem    -   -   -   -   -   -   -   -
   RQOM_FLAG_PKHLD_INIT_PIN_STATE,                     // @emem    -   -   -   -   -   -   -   -
   RQOM_FLAG_LEADING_EVENT_STATE,                      // @emem    -   -   -   -   -   -   -   -
   RQOM_FLAG_INTERRUPT_HOST_ON_FAULT,                  // @emem    -   -   -   -   -   -   -   -
   RQOM_FLAG_SHUT_OFF_PULSE_ON_FAULT,                  // @emem    -   -   -   -   -   -   -   -
   RQOM_FLAG_END_EVENT_ENABLE_LINK,                    // @emem    -   -   -   -   -   y   -   -
   RQOM_FLAG_STATUS_LINK_PENDING,                      // @emem    -   -   -   -   -   y   -   -
   RQOM_FLAG_STATUS_TIME_B4_ANGLE_WAKEUP_PENDING,      // @emem    -   -   -   -   -   y   -   -
   RQOM_FLAG_ENABLE_SYNC_PULSE_AT_START,               // @emem    -   -   -   -   -   y   -   -
   RQOM_FLAG_SYNC_PULSE_ACTIVE_STATE,                  // @emem    -   -   -   -   -   y   -   -
   RQOM_FLAG_SYNC_PULSE_IN_ALTERNATE_TIMER_COUNTS,     // @emem    -   -   -   -   -   y   -   -
   RQOM_FLAG_EXTENDED_EVENT,                           // @enum                                   y
   RQOM_FLAG_MAX                                       // @emem 
 
}  Rqom_Flag_T;

//==============================================================  MCD MCD MCD MCD MCD MCD MCD MCD
//   Type declarations                                             5   5   5   5   5   5   4   4
//==============================================================   4   4   4   4   4   4   4   4
// @enum Rqom_Array_Flag_T | Defines flag position in the 32 bit   0   1   1   1   1   5   0   0
typedef enum                                 //                    6   3   4   5   9   1   6   7
{                                            //                    
   RQOM_ARRAY_FLAG_END_SEQUENCE,             // @emem              y   y   y   -   -   y   y   y
   RQOM_ARRAY_FLAG_REQUEST_DMA,              // @emem              y   y   -   -   -   y   y   y
   RQOM_ARRAY_FLAG_REQUEST_INTERRUPT,        // @emem              y   y   y   -   -   y   y   y
   RQOM_ARRAY_FLAG_MATCH_ALTERNATE_TIMER,    // @emem              y   y   y   -   -   y   y   y
   RQOM_ARRAY_FLAG_CAPTURE_ALTERNATE_TIMER,  // @emem                  y   -   -   -   y   y   y
   RQOM_ARRAY_FLAG_STORE_TIMER,              // @emem              y   -   y   -   -   y   y   y
   RQOM_ARRAY_FLAG_ABSOLUTE_MATCH_EVENT,     // @emem              y   y   y   -   -   y*  y   y
   RQOM_ARRAY_FLAG_END_OF_LOOP,              // @emem              y   y   y   -   -   y*  y   y
   RQOM_ARRAY_FLAG_ACTIVE_STATE,             // @emem              y   y   y   -   -   y   y   y
   RQOM_ARRAY_FLAG_STATUS_DROPPED_EVENT,     // @emem                  -   y   -   -   -   y   y
   RQOM_ARRAY_FLAG_REQUEST_SYNC_PULSE,       // @emem                  -   -   -   -   -   y   y
   RQOM_ARRAY_FLAG_ENABLE_LINK,              // @emem                  -   -   -   -   Y   y   y
   RQOM_ARRAY_FLAG_SKIP_EVENT,               // @emem                  -   -   -   -   Y*  -   -
   RQOM_ARRAY_FLAG_TIME_BEFORE_ANGLE_EVENT,  // @emem 
   RQOM_ARRAY_FLAG_MAX                       // @emem 
 
}  Rqom_Array_Flag_T;

//====================================================            MCD MCD MCD MCD MCD MCD MCD MCD
// @enum Rqom_Parameter_T |                                        5   5   5   5   5   5   4   4
//                                                                 4   4   4   4   4   4   4   4
//====================================================             0   1   1   1   1   5   0   0
typedef enum Rqom_Parameter_Tag              //                    6   3   4   5   9   1   6   7
{                                            //
   RQOM_PARAMETER_ARRAY_SIZE,                // @emem              y   -   y   -   -   y   -   -
   RQOM_PARAMETER_ARRAY_ADDRESS,             // @emem              -   y   -   -   -   y   -   -
   RQOM_PARAMETER_ARRAY_INDEX,               // @emem              y   -   -   -   -   y   -   -
   RQOM_PARAMETER_ARRAY_FLAGS_BUFFERED,      // @emem              -   -   -   -   -   -   -   -
   RQOM_PARAMETER_START_EVENT,               // @emem              y   y   Y   -   -   y   -   -
   RQOM_PARAMETER_START_EVENT_INDEX,         // @emem              -   -   -   -   -   -   -   -
   RQOM_PARAMETER_START_EVENT_ADDRESS,       // @emem              -   -   -   -   -   y   y   -
   RQOM_PARAMETER_LOOP_COUNTER,              // @emem              y   Y   Y   -   -   y   y   -
   RQOM_PARAMETER_INTERRUPT_INDEX,           // @emem              -   -   Y   -   -   -   -   -
   RQOM_PARAMETER_INTERRUPT_ADDRESS,         // @emem              y   Y   -   -   -   -   y   -
   RQOM_PARAMETER_MATCH_TIME,                // @emem              y   Y   -   -   -   -   y   -
   RQOM_PARAMETER_END_EVENT,                 // @emem              y   -   Y   -   -   Y   y   -
   RQOM_PARAMETER_LAST_EVENT_ADDRESS,        // @emem              -   -   -   -   -   -   y   -
   RQOM_PARAMETER_DESIRED_HALF_PERIOD,       // @emem              -   -   -   Y   Y   -   y   -
   RQOM_PARAMETER_PERIOD_ACCUMULATED_PTR,    // @emem              -   -   -   Y   Y   -   -    -
   RQOM_PARAMETER_RATIO,                     // @emem              -   -   -   Y   Y   -   y   -
   RQOM_PARAMETER_LEADING_EDGE_THRESHOLD,    // @emem              -   -   -   -   -   -   y   -
   RQOM_PARAMETER_PKHLD_OFF_DELAY,           // @emem              -   -   -   -   -   -   y   -
   RQOM_PARAMETER_EVENT_COUNT,               // @emem              -   -   -   -   -   -   y   -
   RQOM_PARAMETER_FAULT_COUNT,               // @emem              -   -   -   -   -   -   y   -
   RQOM_PARAMETER_LEADING_EDGE_LAG_TIME,     // @emem              -   -   -   -   -   -   y   -
   RQOM_PARAMETER_ACTUAL_EDGE_COUNT,         // @emem              -   -   -   Y   -   -   y   -
   RQOM_PARAMETER_SYNC_PULSE_WIDTH,          // @emem              -   -   Y   -   -   y   y   -
   RQOM_PARAMETER_DMA_CHANNEL_INDEX,         // @emem              -   -   -   -   -   y   -   -
   RQOM_PARAMETER_REMOTE_DATA_ADDRESS,       // @emem              -   -   -   -   -   y   -   -
   RQOM_PARAMETER_LINK_CHANNEL_INDEX,        // @emem              -   -   -   -   -   y   -   -
   RQOM_PARAMETER_LATEST_TCR2_EVENT,         // @emem              -   -   y   -   -   -   -   -
   RQOM_PARAMETER_LATEST_TCR1_EVENT,         // @emem              -   -   y   -   -   -   -   -
   RQOM_PARAMETER_XEVENT_REMAIN,             // @emem              -   -   y   -   -   -   -   -
   RQOM_PARAMETER_MAX                        // @emem 

}  Rqom_Parameter_T;

#endif

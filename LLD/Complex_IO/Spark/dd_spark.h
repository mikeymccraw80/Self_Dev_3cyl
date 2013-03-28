#ifndef DD_SPARK_H
#define DD_SPARK_H

//=============================================================================
// Data Type Include Files
//=============================================================================
#include "reuse.h"

//=============================================================================
// Include Files
//=============================================================================
#include "io_config_spark.h"


//=============================================================================
// Function Declarations
//=============================================================================

//
// @enum Spark_Mode_T | Defines the EST firing Mode
//
typedef enum
{
   SPARK_SIMULTANEOUS_MODE,      // @emem Use to set the EST outputs to simultaneous mode
   SPARK_SINGLE_CHANNEL_MODE,    // @emem Use to set the EST outputs to single channel mode
   SPARK_DUAL_ALTERNATING_MODE,  // @emem Use to set the EST outputs to dual alternating mode
   SPARK_SEQUENTIAL_MODE         // @emem Use to set the EST outputs to sequential mode

}  Spark_Mode_T;

//
// @enum Spark_Control_Select_T | Defines the Spark control channel numbers.
//
typedef enum
{
   SPARK_CONTROL_0,
   SPARK_CONTROL_1,
   SPARK_CONTROL_2,
   SPARK_CONTROL_3,
   SPARK_CONTROL_4,
   SPARK_CONTROL_5,
   SPARK_CONTROL_6,
   SPARK_CONTROL_7,
   SPARK_CONTROL_8,
   SPARK_CONTROL_9,
   SPARK_CONTROL_10,
   SPARK_CONTROL_11

} Spark_Control_Select_T;


//
// @struct Spark_Durations_T | Used for spark on and off time information for multiple pulses
//
typedef struct Spark_Durations_Tag
{
   uint32_t on_time;  // @field On time for the spark pulse
   uint32_t off_time; // @field Off time for the spark pulse (first off time is minimum off time)

}  Spark_Durations_T;

//
// @enum Spark_Duration_Index_Tag | Defines the spark pulse index
//
typedef enum Spark_Duration_Index_Tag
{
   SPARK_DWELL_INDEX_MAIN_PULSE,    // @emem Spark main  pulse 
   SPARK_DWELL_INDEX_EXTRA_PULSE_1, // @emem Spark extra pulse 1
   SPARK_DWELL_INDEX_EXTRA_PULSE_2, // @emem Spark extra pulse 2
   SPARK_DWELL_INDEX_MAX

}  Spark_Duration_Index_T;


typedef struct IO_Spark_Initialization_Parameters_Tag
{
   Spark_Control_Select_T *Control_Select_Map;
   Spark_Mode_T           Initial_Est_Mode;
   uint8_t         SPARK_Select_Max;              

}  IO_Spark_Initialization_Parameters_T;


#endif // DD_SPARK_H

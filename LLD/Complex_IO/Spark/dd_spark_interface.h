#ifndef DD_SPARK_INTERFACE_H
#define DD_SPARK_INTERFACE_H

#include "dd_spark.h"
#include "io_config_crank.h"




//=============================================================================
// variable Declarations
//=============================================================================

extern const IO_Spark_Initialization_Parameters_T MTSA_SPARK_INITIALIZATION_PARAMETERS;

extern Crank_Cylinder_T              SPARK_Cylinder_Event_ID;
//=============================================================================
// Function Declarations
//=============================================================================


//=============================================================================
// SPARK_Initialize
//=============================================================================
void SPARK_Initialize(
   IO_Spark_Initialization_Parameters_T  *const in_initialization_parameters );

//=============================================================================
// SPARK_Set_Enable
//=============================================================================
void SPARK_Set_Enable(
   bool        in_state );

//=============================================================================
// SPARK_Get_Enable
//=============================================================================
bool SPARK_Get_Enable( void );

//=============================================================================
// SPARK_Set_Channel_Enable
//=============================================================================
void SPARK_Set_Channel_Enable(
   Crank_Cylinder_T  in_cylinder,
   bool              in_state );

//=============================================================================
// SPARK_Get_Channel_Enable
//=============================================================================
bool SPARK_Get_Channel_Enable(
   Crank_Cylinder_T  in_cylinder );

//=============================================================================
// SPARK_Set_Angle
//=============================================================================
void SPARK_Set_Angle_In_Counts(Crank_Cylinder_T in_cylinder, Crank_Angle_T advance_spark_count);

//=============================================================================
// SPARK_Set_Min_Duration
//=============================================================================
void SPARK_Set_Min_Duration(
   uint32_t    in_min_duration,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution );

//=============================================================================
// SPARK_Set_Max_Duration
//=============================================================================
 void SPARK_Set_Max_Duration(
   uint32_t    in_max_duration,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution );

//=============================================================================
// SPARK_Set_Duration
//=============================================================================
void SPARK_Set_Duration(uint8_t cylinder, uint32_t duration, uint8_t time_precision, uint8_t time_resolution);

//=============================================================================
// SPARK_Set_Duration_Extra_P1
//=============================================================================
void SPARK_Set_Duration_Extra_P1(uint8_t cylinder, uint32_t breaktime, uint32_t duration, uint8_t time_precision, uint8_t time_resolution);

//=============================================================================
// SPARK_Set_Duration_Extra_P2
//=============================================================================
void SPARK_Set_Duration_Extra_P2(uint8_t cylinder, uint32_t breaktime, uint32_t duration, uint8_t time_precision, uint8_t time_resolution);

//=============================================================================
// SPARK_Set_State
//=============================================================================
void SPARK_Set_State(uint8_t cylinder, bool state);

//=============================================================================
// SPARK_Set_ExtraPulse_Count
//=============================================================================
void SPARK_Set_ExtraPulse_Count(uint8_t cylinder, uint8_t extra_pulse);

//=============================================================================
// SPARK_Set_Mode
//=============================================================================
void SPARK_Set_Mode(Spark_Mode_T   in_spark_mode );

//=============================================================================
// SPARK_Get_Mode
//=============================================================================
Spark_Mode_T SPARK_Get_Mode( void );

//=============================================================================
// SPARK_Get_Delivered_Duration
//=============================================================================
uint32_t SPARK_Get_Delivered_Duration(
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution );

//=============================================================================
// SPARK_Get_Commanded_Spark_Advance
//=============================================================================
Crank_Angle_T SPARK_Get_Commanded_Spark_Advance(
   Crank_Cylinder_T  in_cylinder );


//=============================================================================
// SPARK_Set_Override_Mode
//=============================================================================
void SPARK_Set_Override_Mode(
   bool        in_enable );

//=============================================================================
// SPARK_Force_Pulse
//=============================================================================
void SPARK_Force_Pulse(
   Crank_Cylinder_T  in_cylinder,
   uint32_t          in_duration,
   uint8_t           in_time_precision,
   uint8_t           in_time_resolution );

//=============================================================================
// SPARK_Reset_Parameters
//=============================================================================
void SPARK_Reset_Parameters( void );

//=============================================================================
// SPARK_Process_Cylinder_Event
//=============================================================================
void SPARK_Process_Cylinder_Event( void );
//=============================================================================
// void SPARK_ReSet_Host_Interrupt
//=============================================================================
void SPARK_ReSet_Host_Interrupt( void );

#endif // DD_SPARK_INTERFACE_H

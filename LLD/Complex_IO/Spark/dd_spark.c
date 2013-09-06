
//=============================================================================
//  Algorithm Include Files
//=============================================================================
#include "dd_spark.h"
#include "io_conversion.h"
#include "dd_mcd5412_interface.h"
#include "io_config_tpu.h"
#include "io_config_crank.h"

#include "dd_vsep_est_select.h"



typedef enum
{
   SPARK_CALC_POSITION_Ref         =  0,
   SPARK_CALC_POSITION_Isr         =  1
}SPARK_CALC_POSITION_T;

//=============================================================================
//  Global Variable Definitions
//=============================================================================
uint32_t                 SPARK_Actual_Duration;
// flags
bool                     SPARK_Enable;
bool                     SPARK_Override_Enabled;
//
uint8_t                  SPARK_Control_Select_Max;
Spark_Mode_T             SPARK_Mode;
Crank_Angle_T           SPARK_Advance_Count[SPARK_MAX_CYLINDERS];
uCrank_Angle_T          SPARK_Calculated_End_Angle_In_Counts[SPARK_MAX_CYLINDERS];
Spark_Control_Select_T  SPARK_Control_Select_Map[SPARK_MAX_CYLINDERS];
Spark_Durations_T       SPARK_Duration[SPARK_MAX_CYLINDERS][SPARK_DWELL_INDEX_MAX];

//=============================================================================
//  Local Variable Definitions
//=============================================================================
uint32_t                      SPARK_Max_Duration;
uint32_t                      SPARK_Min_Duration;
uint32_t                      SPARK_Channel_Enabled;
bool                          SPARK_Cylinder_Event_Occured;
bool                          SPARK_Spark_Scheduled;
uCrank_Angle_T                SPARK_Angle_From_Cylinder_Event_To_TDC;
uCrank_Angle_T                SPARK_Angle_At_Cylinder_Event;
Crank_Cylinder_T              SPARK_Cylinder_Event_ID;
uint32_t                      SPARK_Previous_Cylinder_Event_ID;
uint8_t                       SPARK_Number_Of_Cylinders;
extern Spark_Control_Select_T SPARK_Control_Select_Map[];
Spark_Mode_T                  SPARK_Initial_Est_Mode;
uint32_t                      SPARK_Number_Of_Extra_Pulses;
static bool                   SPARK_ISR_PulseRequested;
static uint8_t                SPARK_Set_Max_Fall_Angle_InToothCount;
static uint8_t                SPARK_Set_Min_Angle_For_Rise_InToothCount;

IO_Spark_Initialization_Parameters_T  *SPARK_Init_Parameters_Ptr;

Crank_Cylinder_T  SPARK_Cylinder_Event_ID_test;
//=============================================================================
//  Function Definitions
//=============================================================================
#define SPARK_Get_Channel(x) SPARK_Cylinder_Event_ID

//=============================================================================
// SPARK_Enable_Channel
//=============================================================================
INLINE uint32_t SPARK_Enable_Channel( uint32_t y )
{
   uint32_t local = SPARK_Channel_Enabled;

   local = Insert_Bits( local, 1, y, BIT_1 );
   local = Insert_Bits( local, 0, y + BIT_16, BIT_1 );

   return local;
}


//=============================================================================
// SPARK_Set_Channel_Pending
//=============================================================================
#define SPARK_Set_Channel_Pending(y) \
   (uint32_t)( Insert_Bits( SPARK_Channel_Enabled, 1, y + BIT_16, BIT_1 ) )

//=============================================================================
// SPARK_Get_Channel_Pending
//=============================================================================
#define SPARK_Get_Channel_Pending(y) \
   (bool)( Extract_Bits( SPARK_Channel_Enabled, y + BIT_16, BIT_1 ) )

//=============================================================================
// SPARK_Disable_Channel
//=============================================================================
#define SPARK_Disable_Channel(y) \
   (uint32_t)( Insert_Bits( SPARK_Channel_Enabled, 0, y, BIT_1 ) )


//=============================================================================
// SPARK_Schedule_Next_Event
//=============================================================================
static void SPARK_Schedule_Next_Event(
   Crank_Cylinder_T  in_cylinder_id,
   uint32_t          injection_angle );


//=============================================================================
// SPARK_Update_Current_Pulse
//=============================================================================
static void SPARK_Update_Current_Pulse(
   Crank_Cylinder_T  in_cylinder_id,
   uint8_t           in_number_of_cylinder_events );


//=============================================================================
// SPARK_Calculate_End_Angle_In_Counts
//=============================================================================
static uint32_t SPARK_Calculate_End_Angle_In_Counts(
   Crank_Cylinder_T  in_cylinder_id,
   uint8_t           in_number_of_cylinder_events,
   SPARK_CALC_POSITION_T calc_position );


//=============================================================================
// SPARK_Update_Duration_Values
//=============================================================================
static void SPARK_Update_Duration_Values(
   Spark_Control_Select_T in_spark_select );

void SPARK_Set_Mode(Spark_Mode_T   in_spark_mode );

//=============================================================================
// SPARK_Initialize
//=============================================================================
void SPARK_Initialize(
   IO_Spark_Initialization_Parameters_T  * const in_initialization_parameters )
{
   uint8_t     counter;

   SPARK_Init_Parameters_Ptr  = (IO_Spark_Initialization_Parameters_T*)in_initialization_parameters;

 
   SPARK_Override_Enabled = false;

   SPARK_Number_Of_Cylinders = CRANK_Get_Number_Of_Cylinders();


   SPARK_Control_Select_Max = in_initialization_parameters->SPARK_Select_Max;

   for (counter = 0; counter < SPARK_Number_Of_Cylinders; counter++ )
   {
      SPARK_Actual_Duration               = 0;
      SPARK_Advance_Count[counter]        = 0;
      SPARK_Control_Select_Map[counter]   = in_initialization_parameters->Control_Select_Map[counter];
   }
   SPARK_Initial_Est_Mode = in_initialization_parameters->Initial_Est_Mode;

   for( counter = 0; counter < SPARK_Control_Select_Max; counter++ )
   {

      MCD5412_Initialize_Channel( MPTAC_TPU_INDEX, SPARK_Mptac[ counter ]);

      MCD5412_Set_Time_Mode( MPTAC_TPU_INDEX,&TPU,  SPARK_Mptac[ counter ], MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_END_TIME );

      // Disable interrupts until ready
      MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX,&TPU,  SPARK_Mptac[ counter ], false );
	  
      // Write the duration values to MPTAC:
      SPARK_Update_Duration_Values( counter );
   }

   //C2MIO_EST_Select_Initialize_Device
  // EST_Select_Initialize_Device( &MTSA_EST_SELECT_DEVICE );
  VSEP_EST_Select_Initialize_Device();

   SPARK_Set_Mode( SPARK_Initial_Est_Mode );

   //C2MIO_EST_Select_Set_Number_Of_Cylinders
   //EST_Select_Set_Number_Of_Cylinders( &MTSA_EST_SELECT_DEVICE, SPARK_Number_Of_Cylinders );
   VSEP_EST_Select_Set_Number_Of_Cylinders(SPARK_Number_Of_Cylinders);

   //JPE Enable all spark channels at init.  This functionality should be handled by the algorithm
   // in a later release.  This is part of the temporary HWIO disabling of shorted EST channels.
   for (counter = 0; counter < SPARK_Number_Of_Cylinders; counter++ )
   {
      SPARK_Channel_Enabled = SPARK_Enable_Channel( counter );
   }

   // Calculate the number of 58X teeth corresponding the calibration angle for TDC:
   SPARK_Angle_From_Cylinder_Event_To_TDC = CRANK_Get_Parameter( CRANK_PARAMETER_ANGLE_FROM_CYLINDER_EVENT_TO_TDC, 0, 0);

}

//=============================================================================
// SPARK_Reset_Parameters
//=============================================================================
void SPARK_Reset_Parameters( void )
{
   SPARK_Initialize( SPARK_Init_Parameters_Ptr );
   SPARK_ISR_PulseRequested = false;
   SPARK_Cylinder_Event_ID_test =false; 
}

//=============================================================================
// SPARK_Set_Enable
//=============================================================================
void SPARK_Set_Enable(
   bool        in_state )
{
   uint8_t     counter;

   if ( in_state )
   {

      // Set a flag to indicate that the function is enabled:
      SPARK_Enable = true;

      // Update the dwell values:
      for( counter = 0; counter < SPARK_Control_Select_Max; counter++ )
      {
	     SPARK_Update_Duration_Values( counter );
      }

      //EST_Select_Enable( &MTSA_EST_SELECT_DEVICE );
      VSEP_EST_Select_Enable();
      //C2MIO_EST_Select_Enable
   }
   else
   {
      uint32_t cs;

      // Set a flag to indicate that the function is disabled:
      SPARK_Enable = false;

      // Disable Spark
      cs = Enter_Critical_Section();

      for( counter = 0; counter < SPARK_Control_Select_Max; counter++ )
      {
         MCD5412_Set_Time_Mode( MPTAC_TPU_INDEX,&TPU,  SPARK_Mptac[ counter ], MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_END_TIME);

         // Disable interrupts until ready
         MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX,&TPU,  SPARK_Mptac[ counter ], false );
      }

      Leave_Critical_Section(cs);

      SPARK_Set_Mode( SPARK_Initial_Est_Mode );

      //C2MIO_EST_Select_Disable
      //EST_Select_Disable( &MTSA_EST_SELECT_DEVICE );
      VSEP_EST_Select_Disable();
	  

   }

}


//=============================================================================
// SPARK_Get_Enable
//=============================================================================
bool SPARK_Get_Enable( void )
{
   return SPARK_Enable;
}


//=============================================================================
// SPARK_Set_Channel_Enable
//=============================================================================
void SPARK_Set_Channel_Enable(
   Crank_Cylinder_T  in_cylinder,
   bool              in_state )
{
   if ( in_state == true )
   {
      SPARK_Channel_Enabled = SPARK_Set_Channel_Pending( (uint32_t)in_cylinder );
   }
   else
   {
      SPARK_Channel_Enabled = SPARK_Disable_Channel( (uint32_t)in_cylinder );
   }
}


//=============================================================================
// SPARK_Get_Channel_Enable
//=============================================================================
bool SPARK_Get_Channel_Enable(
   Crank_Cylinder_T  in_cylinder )
{
   return( (bool)( Extract_Bits( SPARK_Channel_Enabled, in_cylinder, BIT_1 ) ) );
}


//=============================================================================
// SPARK_Set_Angle
//=============================================================================
void SPARK_Set_Angle_In_Counts(
   Crank_Angle_T *in_spark_count_array)
{
   uint8_t  counter;

   for (counter = 0; counter < SPARK_Number_Of_Cylinders; counter++ )
   {
      SPARK_Advance_Count[counter] = in_spark_count_array[counter];
   }
}


//=============================================================================
// SPARK_Set_Min_Duration
//=============================================================================
void SPARK_Set_Min_Duration(
   uint32_t    in_min_duration,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution )
{
   uint32_t    base_frequency = TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ] );

   SPARK_Min_Duration = IO_Convert_Time_To_Count(
      in_min_duration,
      base_frequency ,
      in_time_precision,
      in_time_resolution ) & UINT24_MAX;

   if(  SPARK_Min_Duration > INT24_MAX )
   {
      SPARK_Min_Duration = INT24_MAX ;
   }
}


//=============================================================================
// SPARK_Set_Max_Duration
//=============================================================================
 void SPARK_Set_Max_Duration(
   uint32_t    in_max_duration,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution )
{
   uint32_t    base_frequency = TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ] );

   SPARK_Max_Duration = IO_Convert_Time_To_Count(
      in_max_duration,
      base_frequency ,
      in_time_precision,
      in_time_resolution ) & UINT24_MAX;

   if(  SPARK_Max_Duration > INT24_MAX )
   {
      SPARK_Max_Duration = INT24_MAX;
   }
 }


//=============================================================================
// SPARK_Set_Duration
//=============================================================================
void SPARK_Set_Duration(
   uint32_t    in_duration,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution )
{
   uint32_t    base_frequency = TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX,SPARK_Mptac[ SPARK_CONTROL_0 ] );

   //When there is a transition from Multipulse to Single pulse mode, make sure that 
   //the number of extra pulses is reset to zero.
   SPARK_Number_Of_Extra_Pulses = 0;

   SPARK_Duration[0][SPARK_DWELL_INDEX_MAIN_PULSE].on_time = IO_Convert_Time_To_Count(
      in_duration,
      base_frequency ,
      in_time_precision,
      in_time_resolution );

   if(  SPARK_Duration[0][SPARK_DWELL_INDEX_MAIN_PULSE].on_time > INT24_MAX )
   {
      SPARK_Duration[0][SPARK_DWELL_INDEX_MAIN_PULSE].on_time = INT24_MAX;
   }

}

//=============================================================================
// SPARK_Set_Duration
//=============================================================================
void SPARK_Set_Durations(
   uint8_t              in_cylinder,
   Spark_Durations_T   *in_durations,
   uint8_t              in_array_size,
   uint8_t              in_time_precision,
   uint8_t              in_time_resolution,
   uint8_t              in_number_of_pulses )
{
   uint32_t    base_frequency = TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ] );
   uint8_t     number_of_pulses;
   uint8_t     pulse_count;
   
   //Set up the number of extrat pulses
   if(in_number_of_pulses >= 1)
   {
      SPARK_Number_Of_Extra_Pulses = in_number_of_pulses-1;
   }
  
   if(in_number_of_pulses <= SPARK_DWELL_INDEX_MAX)
   {
      number_of_pulses = in_number_of_pulses;
   }
   else
   {
      number_of_pulses = SPARK_DWELL_INDEX_MAX;
   }
      
   for(pulse_count = 0; (pulse_count < number_of_pulses)&&(pulse_count<in_array_size); pulse_count++)
   {
      //Set ON Time
      SPARK_Duration[in_cylinder][pulse_count].on_time = IO_Convert_Time_To_Count(
         in_durations[pulse_count].on_time,
         base_frequency ,
         in_time_precision,
         in_time_resolution );
      //Check for dwell limit
      if(  SPARK_Duration[in_cylinder][pulse_count].on_time > INT24_MAX )
      {
         SPARK_Duration[in_cylinder][pulse_count].on_time = INT24_MAX;
      }

      //Set Off time
      SPARK_Duration[in_cylinder][pulse_count].off_time = IO_Convert_Time_To_Count(
         in_durations[pulse_count].off_time,
         base_frequency ,
         in_time_precision,
         in_time_resolution );
      //Check for dwell limit
      if(  SPARK_Duration[in_cylinder][pulse_count].off_time > INT24_MAX )
      {
         SPARK_Duration[in_cylinder][pulse_count].off_time = INT24_MAX;
      }
   }
}

//=============================================================================
// SPARK_Set_Mode
//=============================================================================
void SPARK_Set_Mode(Spark_Mode_T   in_spark_mode )
{
   if ( SPARK_Control_Select_Max > 1 )
   {
      switch( in_spark_mode )
      {
      case SPARK_SIMULTANEOUS_MODE:
         VSEP_EST_Select_Set_Mode( MTSA_CONFIG_VSEP_DEVICE_0, EST_MODE_SIMULTANEOUS_MULTIPLE_ENABLE );
            //C2MIO_EST_Select_Set_Mode
         break;

      case SPARK_SINGLE_CHANNEL_MODE:
//#if 0
//         EST_Select_Set_Mode( &MTSA_EST_SELECT_DEVICE, EST_MODE_MULTIPLE_CHANNEL );
//#endif
         break;

      case SPARK_DUAL_ALTERNATING_MODE:
     //    EST_Select_Set_Mode( &MTSA_EST_SELECT_DEVICE, EST_MODE_PAIRED_MULTIPLE_ENABLE );
          VSEP_EST_Select_Set_Mode(MTSA_CONFIG_VSEP_DEVICE_0,EST_MODE_PAIRED_MULTIPLE_ENABLE);
         break;

      case SPARK_SEQUENTIAL_MODE:
      //   EST_Select_Set_Mode( &MTSA_EST_SELECT_DEVICE, EST_MODE_SEQUENTIAL_MULTIPLE_ENABLE );
      VSEP_EST_Select_Set_Mode(MTSA_CONFIG_VSEP_DEVICE_0,EST_MODE_SEQUENTIAL_MULTIPLE_ENABLE);
         break;

      default:

         SPARK_Set_Enable( false );
         break;
      }
   }
   else
   {
      switch( in_spark_mode )
      {
      case SPARK_SIMULTANEOUS_MODE:
         VSEP_EST_Select_Set_Mode( MTSA_CONFIG_VSEP_DEVICE_0, EST_MODE_SIMULTANEOUS_SINGLE_ENABLE );
         break;

      case SPARK_SINGLE_CHANNEL_MODE:
         VSEP_EST_Select_Set_Mode( MTSA_CONFIG_VSEP_DEVICE_0, EST_MODE_SINGLE_CHANNEL );
         break;

      case SPARK_DUAL_ALTERNATING_MODE:
        VSEP_EST_Select_Set_Mode(MTSA_CONFIG_VSEP_DEVICE_0,EST_MODE_PAIRED_MULTIPLE_ENABLE);
         break;

      case SPARK_SEQUENTIAL_MODE:
         VSEP_EST_Select_Set_Mode(MTSA_CONFIG_VSEP_DEVICE_0,EST_MODE_SEQUENTIAL_MULTIPLE_ENABLE);
         break;

      default:

         SPARK_Set_Enable( false );
         break;
      }
   }

   SPARK_Mode = in_spark_mode;
}

//=============================================================================
// SPARK_Get_Mode
//=============================================================================
Spark_Mode_T SPARK_Get_Mode( void )
{
   // This function is used in HWTest
   return SPARK_Mode;
}

//=============================================================================
// SPARK_Get_Delivered_Duration
//=============================================================================
uint32_t SPARK_Get_Delivered_Duration(
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution )
{
   uint32_t    delivered_duration;
   uint32_t    base_frequency =TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ] );

   if ( !in_time_precision && !in_time_resolution )
   {
      delivered_duration = SPARK_Actual_Duration;
   }
   else
   {
      delivered_duration =  IO_Convert_Count_To_Time(
         SPARK_Actual_Duration,
         base_frequency,
         in_time_precision,
         in_time_resolution );
   }
   return delivered_duration;

}


//=============================================================================
// SPARK_Get_Commanded_Spark_Advance
//=============================================================================
Crank_Angle_T SPARK_Get_Commanded_Spark_Advance(
   Crank_Cylinder_T  in_cylinder )
{
   return SPARK_Advance_Count[in_cylinder];
}

//=============================================================================
// SPARK_Set_Override_Mode
//=============================================================================
void SPARK_Set_Override_Mode(
   bool        in_enable )
{
   uint8_t   counter;

   if( in_enable )
   {
      SPARK_Enable = false;
      SPARK_Override_Enabled = true;

      for( counter = 0; counter < SPARK_Control_Select_Max; counter++ )
      {
        MCD5412_Set_Time_Mode(MPTAC_TPU_INDEX,&TPU,  SPARK_Mptac[ counter ], MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME );
      }
   }
   else
   {
      SPARK_Override_Enabled = false;
      SPARK_Set_Enable( false );
   }
}


//=============================================================================
// SPARK_Force_Pulse
//=============================================================================
void SPARK_Force_Pulse(
   Crank_Cylinder_T  in_cylinder,
   uint32_t          in_duration,
   uint8_t           in_time_precision,
   uint8_t           in_time_resolution )
{
   uint32_t start_time;

   Spark_Control_Select_T spark_select = SPARK_Control_Select_Map[in_cylinder];

   // Setup EST channel Select lines
   //C2MIO_EST_Select_Set_Channel
   //EST_Select_Set_Channel(&MTSA_EST_SELECT_DEVICE, (EST_Select_Cylinder_T)in_cylinder);
   VSEP_EST_Select_Set_Channel( MTSA_CONFIG_VSEP_DEVICE_0, (EST_Select_Cylinder_T)in_cylinder );

   // Setup pulse width and 0 duration for start now
   SPARK_Set_Duration( in_duration, in_time_precision, in_time_resolution);
   MCD5412_Set_Duration(MPTAC_TPU_INDEX,SPARK_Mptac[ spark_select ], SPARK_Duration[0][SPARK_DWELL_INDEX_MAIN_PULSE].on_time );

   // start time cannot equal 0, special case
   start_time = CRANK_Get_Parameter( CRANK_PARAMETER_TIMER_VALUE_RAW, 0, 0 ) - 1;
   start_time = ( start_time ? start_time : 0x7FFFFF );
   MCD5412_Set_CPU_Start_Time(MPTAC_TPU_INDEX, SPARK_Mptac[ spark_select ], start_time );

   // Request that a new pulse be set up:
   MCD5412_Request_Pulse(MPTAC_TPU_INDEX,  SPARK_Mptac[ spark_select ] );

}

//=============================================================================
// SPARK_Schedule_Next_Event
//=============================================================================
static void SPARK_Schedule_Next_Event(
   Crank_Cylinder_T  in_cylinder_id,
   uint32_t          injection_angle )
{
   Spark_Control_Select_T spark_select   = SPARK_Control_Select_Map[in_cylinder_id];
   uint32_t       end_angle;

   // Update the end angle information:
   MCD5412_Set_Angle(MPTAC_TPU_INDEX, SPARK_Mptac[spark_select], injection_angle );

   // Request that a new pulse be set up:
   MCD5412_Request_Pulse( MPTAC_TPU_INDEX,  SPARK_Mptac[spark_select] );

   SPARK_Spark_Scheduled = true;

}

//=============================================================================
// SPARK_Update_Current_Pulse
//=============================================================================
static void SPARK_Update_Current_Pulse(
   Crank_Cylinder_T  in_cylinder_id,
   uint8_t           in_number_of_cylinder_events )
{
   Spark_Control_Select_T spark_select   = SPARK_Control_Select_Map[in_cylinder_id];
   uint32_t       end_angle;

   end_angle = SPARK_Calculate_End_Angle_In_Counts( in_cylinder_id, in_number_of_cylinder_events, SPARK_CALC_POSITION_Ref );

   // Update the end angle information:
   MCD5412_Set_Angle( MPTAC_TPU_INDEX, SPARK_Mptac[spark_select], end_angle );

   // Request that the new angle information is used.
   MCD5412_Request_Update( MPTAC_TPU_INDEX, SPARK_Mptac[spark_select] );
}

//=============================================================================
// SPARK_Calculate_End_Angle_In_Counts
//=============================================================================
static uint32_t SPARK_Calculate_End_Angle_In_Counts(
   Crank_Cylinder_T  in_cylinder_id,
   uint8_t           in_number_of_cylinder_events,
   SPARK_CALC_POSITION_T calc_position )
{
   uint32_t       end_angle;
   Crank_Angle_T  spark_advance;
   uCrank_Angle_T tdc_angle;
   uCrank_Angle_T angle_in_pa_counts;
   uCrank_Angle_T future_cylinder_event_counts;
   uCrank_Angle_T base_angle;
   Spark_Control_Select_T in_spark_select;

   spark_advance = SPARK_Advance_Count[in_cylinder_id];

   if ( SPARK_CALC_POSITION_Ref == calc_position )
   {
      // Calculate the spark angle in reference to the Crank:
      tdc_angle =
         ( SPARK_Angle_From_Cylinder_Event_To_TDC + SPARK_Angle_At_Cylinder_Event );

      // convert the signed angle in counts to the pulse accumulated counts needed by the primitive
      angle_in_pa_counts = tdc_angle - spark_advance;

      future_cylinder_event_counts = (uCrank_Angle_T)( ( ( in_number_of_cylinder_events * CRANK_Get_Parameter( CRANK_PARAMETER_INITIAL_VIRTUAL_TEETH_PER_CYLINDER_EVENT, 0, 0 ) ) << CRANK_ANGLE_PRECISION ) & uCRANK_ANGLE_MAX);

      // Calculate the true end angle in pulse counts for this cylinder given the current counts:
      end_angle =    (uint32_t)( ( angle_in_pa_counts + future_cylinder_event_counts ) & uCRANK_ANGLE_MAX );

      SPARK_Calculated_End_Angle_In_Counts[in_cylinder_id] = end_angle;
   }
   else //SPARK_CALC_POSITION_Isr
   {
      in_spark_select = SPARK_Control_Select_Map[in_cylinder_id];
      base_angle = MCD5412_Get_Actual_End_Angle(MPTAC_TPU_INDEX, SPARK_Mptac[ in_spark_select ]);

      end_angle =  base_angle + ( CRANK_Get_Parameter( CRANK_PARAMETER_INITIAL_VIRTUAL_TEETH_PER_CYLINDER_EVENT, 0, 0 )<< CRANK_ANGLE_PRECISION );

   }

   return end_angle;
}


//=============================================================================
// SPARK_Convert_PaCounts_To_End_Angle
//=============================================================================
static Crank_Angle_T SPARK_Convert_PaCounts_To_End_Angle(
   int8_t            cylinder_events_complensated,
   uCrank_Angle_T    in_angle_in_pa_counts )
{


   Crank_Angle_T  end_angle;
   Crank_Angle_T  spark_delivered;
   uCrank_Angle_T tdc_angle;
   Crank_Angle_T  future_cylinder_event_counts;

   // Calculate the spark angle in reference to the Crank:
   tdc_angle = SPARK_Angle_From_Cylinder_Event_To_TDC + SPARK_Angle_At_Cylinder_Event;

   // convert the pulse accumulated counts to the signed angle in counts
   spark_delivered = (Crank_Angle_T)(tdc_angle - in_angle_in_pa_counts);

   future_cylinder_event_counts = (Crank_Angle_T)( ( cylinder_events_complensated * (Crank_Angle_T)( CRANK_Get_Parameter( CRANK_PARAMETER_INITIAL_VIRTUAL_TEETH_PER_CYLINDER_EVENT, 0, 0 ) << CRANK_ANGLE_PRECISION ) ) );

   // Calculate :
   end_angle = spark_delivered + future_cylinder_event_counts;

   return end_angle;
}

//=============================================================================
// SPARK_Update_Duration_Values
//=============================================================================
static void SPARK_Update_Duration_Values( Spark_Control_Select_T in_spark_select )
{
uint32_t    base_frequency = TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX,  SPARK_Mptac[ SPARK_CONTROL_0 ] );

   MCD5412_Set_Min_Duration(MPTAC_TPU_INDEX, SPARK_Mptac[ in_spark_select ], SPARK_Min_Duration );
   MCD5412_Set_Duration(MPTAC_TPU_INDEX, SPARK_Mptac[ in_spark_select ], SPARK_Duration[0][SPARK_DWELL_INDEX_MAIN_PULSE].on_time );
   MCD5412_Set_Max_Duration(MPTAC_TPU_INDEX,  SPARK_Mptac[ in_spark_select ], SPARK_Max_Duration );

   SPARK_Set_Max_Fall_Angle_InToothCount = (uint8_t)SPARK_DWELL_MPTAC_MAX_FALL_ANGLE_IN_TOOTHCOUNT;
   SPARK_Set_Min_Angle_For_Rise_InToothCount = (uint8_t)( ( SPARK_DWELL_ABSOLUTE_MAXVALUE_IN_SEC * (CRANK_VIRTUAL_TEETH_PER_CRANK/2))\
                                                          * base_frequency\
                                                          / CRANK_Get_Parameter( CRANK_PARAMETER_HI_RES_REFERENCE_PERIOD, 0, 0 ) );
   if ( SPARK_Set_Min_Angle_For_Rise_InToothCount > (uint8_t)(SPARK_DWELL_LIMIT_IN_REFPERIOD_PERCENT*CRANK_VIRTUAL_TEETH_PER_CRANK/2) )
   {
      SPARK_Set_Min_Angle_For_Rise_InToothCount = (uint8_t)(SPARK_DWELL_LIMIT_IN_REFPERIOD_PERCENT*CRANK_VIRTUAL_TEETH_PER_CRANK/2);
   }
   else
   {
      // nothing
   }
   MCD5412_Set_Min_Angle_For_Rise(MPTAC_TPU_INDEX, SPARK_Mptac[ in_spark_select ], SPARK_Set_Min_Angle_For_Rise_InToothCount );
   MCD5412_Set_Max_Fall_Angle(MPTAC_TPU_INDEX, SPARK_Mptac[ in_spark_select ], SPARK_Set_Max_Fall_Angle_InToothCount );
   
	//Set extra pulses
   MCD5412_Set_Extra_Pulses(MPTAC_TPU_INDEX,SPARK_Number_Of_Extra_Pulses);

   //If extra pulses are required, update On/Off times for extra pulses
   if(SPARK_Number_Of_Extra_Pulses)
   {	  	
      MCD5412_Set_Min_Off_Time( MPTAC_TPU_INDEX, SPARK_Mptac[ in_spark_select ], SPARK_Duration[0][SPARK_DWELL_INDEX_MAIN_PULSE].off_time);
      MCD5412_Set_On_Time_2( MPTAC_TPU_INDEX, SPARK_Duration[0][SPARK_DWELL_INDEX_EXTRA_PULSE_1].on_time);
      MCD5412_Set_Off_Time_2( MPTAC_TPU_INDEX, SPARK_Duration[0][SPARK_DWELL_INDEX_EXTRA_PULSE_1].off_time );
      MCD5412_Set_On_Time_3( MPTAC_TPU_INDEX, SPARK_Duration[0][SPARK_DWELL_INDEX_EXTRA_PULSE_2].on_time );
   }		 
}

//=============================================================================
// SPARK_Process_Interrupt
//    SPARK_Control_Select_Max = 2
//                          Cyl:  A         B          C          D
//                          TDC:        a|         b|         c|         d|
//                                       :          :          :          :
//                          C E   |      :  |       :  |       :  |       :
//                                       :          :          :          :
//        SPARK_Spark_Scheduled:T        :T         :T         :T         :T
//                                       :          :          :          :
// SPARK_Cylinder_Event_Occured:  T      F  T       F  T       F  T       F
//                                       :          :          :          :
//  cylinder_events_compensated:         2          2          2          2
//
// Scheduling cylinder                   C          D          A          B
//
// ============================================================================
//
//                          Cyl:  A         B          C          D
//                          TDC:        a|              b|    c|         d|
//                                       :               :     :          :
//                          C E   |      :  |          | :     :  |       :
//                                       :               :     :          :
//        SPARK_Spark_Scheduled:T        :T            F :     :          :
//                                       :               :     :          :
// SPARK_Cylinder_Event_Occured:  T      F  T          T F     F          F
//                                       :               :     :          :
//  cylinder_events_compensated:         2               1     2          2
//
// Scheduling cylinder                   C               D     A          B
//
//=============================================================================

void SPARK_Process_Interrupt(
   Spark_Control_Select_T in_spark_select )
{
   uint8_t                 faults                                 = 0;
   uint8_t                 scheduled_cylinder_events_compensated;
   Crank_Cylinder_T        cylinder = 0;
   Spark_Control_Select_T  control_select; 
  uCrank_Angle_T          actual_angle_in_pa_counts;
   uCrank_Angle_T          end_angle;

   // Get the amount of EST dwell which was delivered:
   SPARK_Actual_Duration = MCD5412_Get_Actual_Duration(MPTAC_TPU_INDEX, SPARK_Mptac[ in_spark_select ]);
   actual_angle_in_pa_counts = MCD5412_Get_Actual_End_Angle( MPTAC_TPU_INDEX, SPARK_Mptac[ in_spark_select ] );

   // Calculate the next EST channel, and output the
   // EST control signals and the SEL1/0 signals:
   //
   if( SPARK_Enable )
   {
#if 0

      // Normally, the next spark will be this number of cylinder events away:
      scheduled_cylinder_events_compensated = SPARK_Control_Select_Max;

      if( SPARK_Spark_Scheduled )
      {
         // Cylinder event has NOT occured since last interrupt
         cylinder_event_complensation     = 0;
      }
      else
      {
         // Cylinder event HAS occured since last interrupt: decriment the cylinder event
         cylinder_event_complensation     = -1;
      }

      // If the spark dwell occurs across a lo res event, the cylinder ID is indexed before
      // this end of dwell interrupt is serviced.  If this end of dwell interrupt is
      // serviced before the Lo Res event (i.e. a coil fault that prematurely ends spark)
      // then the next spark must be setup for the proper cylinder, thus the +1.
      if ( SPARK_Cylinder_Event_Occured )
      {
         if( SPARK_Spark_Scheduled )
         {
            SPARK_Cylinder_Event_Occured = false;
         }
      }
      else
      {
         cylinder_event_complensation     += 1;
      }
      // For the diagnostic routine
      cylinder = CRANK_Increment_Cylinder_ID(
         SPARK_Cylinder_Event_ID,
         cylinder_event_complensation );

      // Diagnostic conversion from pulse accumulated angle to Cylinder TDC referenced angle.
      SPARK_Delivered_End_Angle[cylinder] = SPARK_Convert_PaCounts_To_End_Angle( cylinder_event_complensation, actual_angle_in_pa_counts );

      // For the next scheduled Spark Event
      scheduled_cylinder_events_compensated += cylinder_event_complensation;
      cylinder = CRANK_Increment_Cylinder_ID(
         SPARK_Cylinder_Event_ID,
         scheduled_cylinder_events_compensated );


      control_select = SPARK_Control_Select_Map[cylinder];

      // If there is a channel without a fault, update its values and set it up:
      if( SPARK_Get_Channel_Enable( cylinder ) )
      {

         // Set the channel number in the selected EST Select Device
         //EST_Select_Set_Channel( &MTSA_EST_SELECT_DEVICE, (EST_Select_Cylinder_T)cylinder );
         VSEP_EST_Select_Set_Channel(MTSA_CONFIG_VSEP_DEVICE_0,(EST_Select_Cylinder_T)cylinder  );

         // Setup the pulse to be delivered:
         end_angle = SPARK_Calculate_End_Angle_In_Counts( cylinder, (uint8_t)control_select, SPARK_CALC_POSITION_Isr );
         SPARK_Schedule_Next_Event( cylinder, end_angle );
         SPARK_ISR_PulseRequested = true;

      }
      else
      {
         SPARK_Set_Enable( false );
      }

      // Update the dwell values:
      SPARK_Update_Duration_Values( control_select );

#endif

      // For the diagnostic routine
      SPARK_Cylinder_Event_ID_test = CRANK_Increment_Cylinder_ID(
         SPARK_Cylinder_Event_ID_test, 1    );
      cylinder = SPARK_Cylinder_Event_ID_test;
      
      control_select = SPARK_Control_Select_Map[cylinder];
      // If there is a channel without a fault, update its values and set it up:
      if( SPARK_Get_Channel_Enable( cylinder ) )
      {

         // Set the channel number in the selected EST Select Device
         //EST_Select_Set_Channel( &MTSA_EST_SELECT_DEVICE, (EST_Select_Cylinder_T)cylinder );
         VSEP_EST_Select_Set_Channel(MTSA_CONFIG_VSEP_DEVICE_0,(EST_Select_Cylinder_T)cylinder  );

         // Setup the pulse to be delivered:
         end_angle = SPARK_Calculate_End_Angle_In_Counts( cylinder, (uint8_t)control_select, SPARK_CALC_POSITION_Isr );
         SPARK_Schedule_Next_Event( cylinder, end_angle );

      }
      else
      {
         SPARK_Set_Enable( false );
      }

      // Update the dwell values:
      SPARK_Update_Duration_Values( control_select );
		
	 
   }

   // Disable interrupts until ready
   MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX,&TPU, SPARK_Mptac[0], false );



}


//=============================================================================
// SPARK_Process_Cylinder_Event
//=============================================================================
void SPARK_Process_Cylinder_Event( void )
{
   uint32_t          cs;
   Crank_Cylinder_T  cylinder = 0;
   uint32_t          counter;
   Crank_Cylinder_T  channel;
    uint32_t          cylinder_event_id;
   uCrank_Angle_T    end_angle;
    Spark_Control_Select_T spark_select  ;
   
   cs = Enter_Critical_Section();


   SPARK_Cylinder_Event_ID       = CRANK_Get_Cylinder_ID();

   SPARK_Angle_At_Cylinder_Event = CRANK_Get_Parameter( CRANK_PARAMETER_ANGLE_AT_CYLINDER_EVENT, 0, 0 );

   if( SPARK_Cylinder_Event_Occured )
   {
      // No Interrupt event occurred between cylinder events
      SPARK_Spark_Scheduled = false;
   }

   SPARK_Cylinder_Event_Occured = true;

   Leave_Critical_Section( cs );

   if( SPARK_Enable )
   {

 
      if( SPARK_Get_Channel_Enable( SPARK_Cylinder_Event_ID ) )
      {

        if(!SPARK_ISR_PulseRequested)
        {
	     for( counter = 0; counter < SPARK_Control_Select_Max; counter++ )
            {
               channel = CRANK_Get_Future_Cylinder_ID( (uint8_t)counter );
    	       MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX,&TPU, SPARK_Mptac[counter], true );
               spark_select =  SPARK_Control_Select_Map[channel];
	       SPARK_Update_Duration_Values(spark_select);
               // Setup the initial cylinders for normal operation:
               // Put the cylinder ID for this est control to the correct value
               //C2MIO_EST_Select_Set_Channel
               //EST_Select_Set_Channel( &MTSA_EST_SELECT_DEVICE, (EST_Select_Cylinder_T)channel );
               VSEP_EST_Select_Set_Channel(MTSA_CONFIG_VSEP_DEVICE_0,(EST_Select_Cylinder_T)channel  );
               end_angle = SPARK_Calculate_End_Angle_In_Counts( channel, (uint8_t)counter, SPARK_CALC_POSITION_Ref );
		  // Update the end angle information:(
               SPARK_Schedule_Next_Event( channel, end_angle );
		  SPARK_Cylinder_Event_ID_test  = channel;
             }
		 


             SPARK_ISR_PulseRequested = true;
          }				 
	   else
	   {
	     	  spark_select =  SPARK_Control_Select_Map[SPARK_Cylinder_Event_ID];
               // SPARK_Update_Duration_Values( spark_select );
               MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX,&TPU,  SPARK_Mptac[0], true );
               // Update current spark:
                SPARK_Update_Current_Pulse( SPARK_Cylinder_Event_ID, 0 );

	   }	
        #if 0
         //
         // If the spark channel's interrupt has not been previously enabled, do it now.
         //
         if ( SPARK_ISR_PulseRequested )
         {
            SPARK_ISR_PulseRequested = false;
	      // Update the dwell values:
	      spark_select =  SPARK_Control_Select_Map[SPARK_Cylinder_Event_ID];
           // SPARK_Update_Duration_Values( spark_select );
           /MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX,&TPU,  SPARK_Mptac[0], true );
            // Update current spark:
            SPARK_Update_Current_Pulse( SPARK_Cylinder_Event_ID, 0 );

	  
         }
         else if ( MCD5412_Get_Host_Interrupt_Enable( MPTAC_TPU_INDEX,&TPU, SPARK_Mptac[ SPARK_Control_Select_Map[SPARK_Cylinder_Event_ID] ] ) == false )
         {
            SPARK_Previous_Cylinder_Event_ID = (uint32_t)SPARK_Cylinder_Event_ID;
            for( counter = 0; counter < SPARK_Control_Select_Max; counter++ )
            {
               // Enable interrupts:
               channel = CRANK_Get_Future_Cylinder_ID( (uint8_t)counter );
    	       MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX,&TPU, SPARK_Mptac[counter], true );
               spark_select =  SPARK_Control_Select_Map[channel];
	       SPARK_Update_Duration_Values(spark_select);
               // Setup the initial cylinders for normal operation:
               // Put the cylinder ID for this est control to the correct value
               //C2MIO_EST_Select_Set_Channel
               //EST_Select_Set_Channel( &MTSA_EST_SELECT_DEVICE, (EST_Select_Cylinder_T)channel );
               VSEP_EST_Select_Set_Channel(MTSA_CONFIG_VSEP_DEVICE_0,(EST_Select_Cylinder_T)channel  );
               end_angle = SPARK_Calculate_End_Angle_In_Counts( channel, (uint8_t)counter, SPARK_CALC_POSITION_Ref );
		  // Update the end angle information:(
               SPARK_Schedule_Next_Event( channel, end_angle );

            }

         }
         else
         {
            // nothing
         }

	#endif	 
      }
      else
      {
         // Since this cylinder has faulted, clear the cylinder event occured flag:
         SPARK_Cylinder_Event_Occured = false;
      }
   }
        #if 0
   if ( SPARK_Cylinder_Event_ID == CRANK_CYLINDER_A )
   {
      cylinder_event_id = SPARK_Number_Of_Cylinders;
   }
   else
   {
      cylinder_event_id = SPARK_Cylinder_Event_ID;
   }

   if ( ( cylinder_event_id - SPARK_Previous_Cylinder_Event_ID ) > 1 )
   {
      for( counter = 0; counter < SPARK_Control_Select_Max; counter++ )
      {
         channel = CRANK_Get_Future_Cylinder_ID( (uint8_t)counter );
		 //C2MIO_EST_Select_Set_Channel
         VSEP_EST_Select_Set_Channel( MTSA_CONFIG_VSEP_DEVICE_0, (EST_Select_Cylinder_T)channel );
      }
   }
#endif
   SPARK_Previous_Cylinder_Event_ID = (uint32_t)SPARK_Cylinder_Event_ID;

}




//=============================================================================
// /------------------------------------------------------------------------
// | Interrupt Handlers
// \------------------------------------------------------------------------
//=============================================================================

//=============================================================================
// SPARK_Set_Next_Interrupt_EST1
//=============================================================================
void SPARK_Set_Next_Interrupt_EST1( void ) 
{
//   Parameter_Not_Used( in_context );
   MCD5412_Set_Host_Interrupt_Status(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[ 0 ], false);
   
   if( !SPARK_Override_Enabled )
   {
      SPARK_Process_Interrupt( SPARK_CONTROL_0 );
   }

}




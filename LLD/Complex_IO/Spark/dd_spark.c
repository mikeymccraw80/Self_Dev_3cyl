
//=============================================================================
//  Algorithm Include Files
//=============================================================================
#include "dd_spark.h"
#include "io_conversion.h"
#include "dd_mcd5412_interface.h"
#include "io_config_tpu.h"
#include "io_config_crank.h"
#include "dd_vsep_est_select.h"
#include "dd_mcd5408_interface.h"
#include "dd_siu_interface.h"


typedef enum {
    SPARK_CALC_POSITION_Ref         =  0,
    SPARK_CALC_POSITION_Isr         =  1
} SPARK_CALC_POSITION_T;

//
// @struct Spark_Channel_T | Used for each spark channel information for multiple pulses
//
typedef struct Spark_Channel_Tag {
    bool                state;
    uint8_t             extra_pulse;
    Crank_Angle_T       advance_count;
    Spark_Durations_T   duration[SPARK_DWELL_INDEX_MAX];
}  Spark_Channel_T;


//=============================================================================
//  Global Variable Definitions
//=============================================================================
uint32_t                 SPARK_Actual_Duration;
bool                     SPARK_Enable;
bool                     SPARK_Override_Enabled;
uint8_t                  SPARK_Control_Select_Max;
Spark_Mode_T             SPARK_Mode;
uCrank_Angle_T           SPARK_Calculated_End_Angle_In_Counts[SPARK_MAX_CYLINDERS];
Spark_Control_Select_T   SPARK_Control_Select_Map[SPARK_MAX_CYLINDERS];
Spark_Channel_T          SPARK_Channel[SPARK_MAX_CYLINDERS];

//=============================================================================
//  Local Variable Definitions
//=============================================================================
uint32_t                      SPARK_Max_Duration;
uint32_t                      SPARK_Min_Duration;
uint32_t                      SPARK_Channel_Enabled;
bool                          SPARK_Spark_Scheduled;
uCrank_Angle_T                SPARK_Angle_From_Cylinder_Event_To_TDC;
uCrank_Angle_T                SPARK_Angle_At_Cylinder_Event;
Crank_Cylinder_T              SPARK_Cylinder_Event_ID;
uint8_t                       SPARK_Number_Of_Cylinders;
Spark_Mode_T                  SPARK_Initial_Est_Mode;
uint32_t                      SPARK_Number_Of_Extra_Pulses;
static bool                   SPARK_ISR_PulseRequested;
static uint8_t                SPARK_Set_Max_Fall_Angle_InToothCount;
static uint8_t                SPARK_Set_Min_Angle_For_Rise_InToothCount;
static volatile uint8_t       SPARK_Scheduled_SynControl;

IO_Spark_Initialization_Parameters_T  *SPARK_Init_Parameters_Ptr;

/* ============================================================================ *\
 *  Local Constant Definitions
\* ============================================================================ */
/* local est channel remap, simulate PF mode by software */
static const uint8_t CeVSEP_EST_CylinderID_Mapping[] = {
    CRANK_CYLINDER_A,
    CRANK_CYLINDER_B,
    CRANK_CYLINDER_A,
    CRANK_CYLINDER_B
};

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
// SPARK_Enable_Channel
//=============================================================================
#define SPARK_Enable_Channel(y) \
   (uint32_t)( Insert_Bits( SPARK_Channel_Enabled, 1, y, BIT_1 ) )

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
static void SPARK_Update_Duration_Values(Spark_Control_Select_T in_spark_select, Crank_Cylinder_T in_cylinder );

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

    for (counter = 0; counter < SPARK_Number_Of_Cylinders; counter++ ) {
        SPARK_Actual_Duration               = 0;
        // SPARK_Advance_Count[counter]        = 0;
        SPARK_Channel[counter].advance_count = 0;
        SPARK_Control_Select_Map[counter]   = in_initialization_parameters->Control_Select_Map[counter];
    }
    SPARK_Initial_Est_Mode = in_initialization_parameters->Initial_Est_Mode;

    for( counter = 0; counter < SPARK_Control_Select_Max; counter++ ) {
        MCD5412_Initialize_Channel( MPTAC_TPU_INDEX, SPARK_Mptac[ counter ]);
        // Enable multi pulse
        MCD5412_Set_Flag(MPTAC_TPU_INDEX, SPARK_Mptac[SPARK_CONTROL_0], MPTAC_MULTI_PULSE_MODE_FLAG, true);
        MCD5412_Set_Time_Mode( MPTAC_TPU_INDEX,&TPU,  SPARK_Mptac[ counter ], MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_END_TIME );
        // Disable interrupts until ready
        MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[ counter ], false );
        // Write the duration values to MPTAC:
        // SPARK_Update_Duration_Values( counter );
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
    for (counter = 0; counter < SPARK_Number_Of_Cylinders; counter++ ) {
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
}

//=============================================================================
// SPARK_Set_Enable
//=============================================================================
void SPARK_Set_Enable(bool in_state )
{
    uint8_t     counter;

    if ( in_state ) {
        // Set a flag to indicate that the function is enabled:
        SPARK_Enable = true;
        // Update the dwell values:
        // for( counter = 0; counter < SPARK_Control_Select_Max; counter++ ) {
        // SPARK_Update_Duration_Values( counter );
        // }
        VSEP_EST_Select_Enable();
    } else {
        uint32_t cs;

        // Set a flag to indicate that the function is disabled:
        SPARK_Enable = false;

        // Disable Spark
        cs = Enter_Critical_Section();

        for( counter = 0; counter < SPARK_Control_Select_Max; counter++ ) {
            MCD5412_Set_Time_Mode( MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[counter], MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_END_TIME);
            // Disable interrupts until ready
            MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[counter], false);
        }

        Leave_Critical_Section(cs);

        SPARK_Set_Mode( SPARK_Initial_Est_Mode );
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
void SPARK_Set_Channel_Enable(Crank_Cylinder_T  in_cylinder, bool in_state )
{
    if ( in_state == true ) {
        SPARK_Channel_Enabled = SPARK_Enable_Channel( (uint32_t)in_cylinder );
    } else {
        SPARK_Channel_Enabled = SPARK_Disable_Channel( (uint32_t)in_cylinder );
    }
}

//=============================================================================
// SPARK_Get_Channel_Enable
//=============================================================================
bool SPARK_Get_Channel_Enable(Crank_Cylinder_T  in_cylinder )
{
    return( (bool)( Extract_Bits( SPARK_Channel_Enabled, in_cylinder, BIT_1 ) ) );
}


//=============================================================================
// SPARK_Set_Angle
//=============================================================================
void SPARK_Set_Angle_In_Counts(Crank_Cylinder_T in_cylinder, Crank_Angle_T advance_spark_count)
{
    SPARK_Channel[in_cylinder].advance_count = advance_spark_count;
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

    if(  SPARK_Min_Duration > INT24_MAX ) {
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

    if(  SPARK_Max_Duration > INT24_MAX ) {
        SPARK_Max_Duration = INT24_MAX;
    }
}


//=============================================================================
// SPARK_Set_Duration
//=============================================================================
void SPARK_Set_Duration(uint8_t cylinder, uint32_t duration, uint8_t time_precision, uint8_t time_resolution)
{
    uint32_t    base_frequency = TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX,SPARK_Mptac[ SPARK_CONTROL_0 ] );

    //When there is a transition from Multipulse to Single pulse mode, make sure that
    //the number of extra pulses is reset to zero.
    SPARK_Number_Of_Extra_Pulses = 0;

    SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_MAIN_PULSE].on_time = IO_Convert_Time_To_Count(
                duration,
                base_frequency ,
                time_precision,
                time_resolution );

    if(SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_MAIN_PULSE].on_time > INT24_MAX) {
        SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_MAIN_PULSE].on_time = INT24_MAX;
    }
    
}

//=============================================================================
// SPARK_Set_Duration_Extra_P1
//=============================================================================
void SPARK_Set_Duration_Extra_P1(uint8_t cylinder, uint32_t breaktime, uint32_t duration, uint8_t time_precision, uint8_t time_resolution)
{
    uint32_t    base_frequency = TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX,SPARK_Mptac[ SPARK_CONTROL_0 ] );

    //When there is a transition from Multipulse to Single pulse mode, make sure that
    //the number of extra pulses is reset to zero.
    // SPARK_Number_Of_Extra_Pulses = 0;

    SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_1].on_time = IO_Convert_Time_To_Count(
                duration,
                base_frequency ,
                time_precision,
                time_resolution );

    if(SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_1].on_time > INT24_MAX) {
        SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_1].on_time = INT24_MAX;
    }

    SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_MAIN_PULSE].off_time = IO_Convert_Time_To_Count(
                breaktime,
                base_frequency ,
                time_precision,
                time_resolution );
}

//=============================================================================
// SPARK_Set_Duration_Extra_P2
//=============================================================================
void SPARK_Set_Duration_Extra_P2(uint8_t cylinder, uint32_t breaktime, uint32_t duration, uint8_t time_precision, uint8_t time_resolution)
{
    uint32_t base_frequency = TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX,SPARK_Mptac[ SPARK_CONTROL_0 ] );

    //When there is a transition from Multipulse to Single pulse mode, make sure that
    //the number of extra pulses is reset to zero.
    // SPARK_Number_Of_Extra_Pulses = 0;

    SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_2].on_time = IO_Convert_Time_To_Count(
                duration,
                base_frequency ,
                time_precision,
                time_resolution );

    if(SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_2].on_time > INT24_MAX ) {
        SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_2].on_time = INT24_MAX;
    }

    SPARK_Channel[cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_1].off_time = IO_Convert_Time_To_Count(
                breaktime,
                base_frequency ,
                time_precision,
                time_resolution );
}

//=============================================================================
// SPARK_Set_ExtraPulse_Count
//=============================================================================
void SPARK_Set_ExtraPulse_Count(uint8_t cylinder, uint8_t extra_pulse)
{
    SPARK_Channel[cylinder].extra_pulse = extra_pulse;
}

//=============================================================================
// SPARK_Set_Enable
//=============================================================================
void SPARK_Set_State(uint8_t cylinder, bool state)
{
    SPARK_Channel[cylinder].state = state;
}

//=============================================================================
// SPARK_Set_Mode
//=============================================================================
void SPARK_Set_Mode(Spark_Mode_T   in_spark_mode )
{
    if ( SPARK_Control_Select_Max > 1 ) {
        switch( in_spark_mode ) {
        case SPARK_SIMULTANEOUS_MODE:
            VSEP_EST_Select_Set_Mode( MTSA_CONFIG_VSEP_DEVICE_0, EST_MODE_SIMULTANEOUS_MULTIPLE_ENABLE );
            //C2MIO_EST_Select_Set_Mode
            break;

        case SPARK_SINGLE_CHANNEL_MODE:
//         EST_Select_Set_Mode( &MTSA_EST_SELECT_DEVICE, EST_MODE_MULTIPLE_CHANNEL );
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
    } else {
        switch( in_spark_mode ) {
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
            VSEP_EST_Select_Set_Mode(MTSA_CONFIG_VSEP_DEVICE_0,EST_MODE_SEQUENTIAL_SINGLE_ENABLE);
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

    if ( !in_time_precision && !in_time_resolution ) {
        delivered_duration = SPARK_Actual_Duration;
    } else {
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
Crank_Angle_T SPARK_Get_Commanded_Spark_Advance(Crank_Cylinder_T  in_cylinder )
{
    // return SPARK_Advance_Count[in_cylinder];
    return SPARK_Channel[in_cylinder].advance_count;
}

//=============================================================================
// SPARK_Set_Override_Mode
//=============================================================================
void SPARK_Set_Override_Mode(bool        in_enable )
{
    uint8_t   counter;

    if( in_enable ) {
        SPARK_Enable = false;
        SPARK_Override_Enabled = true;

        for( counter = 0; counter < SPARK_Control_Select_Max; counter++ ) {
            MCD5412_Set_Time_Mode(MPTAC_TPU_INDEX,&TPU,  SPARK_Mptac[ counter ], MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME );
        }
    } else {
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

    //vsep select channel, note there's a map relation between logic cylinder and vsep output
    VSEP_EST_Select_Set_Channel( MTSA_CONFIG_VSEP_DEVICE_0, CeVSEP_EST_CylinderID_Mapping[in_cylinder]);

    // Setup pulse width and 0 duration for start now
    SPARK_Set_Duration(in_cylinder, in_duration, in_time_precision, in_time_resolution);
    MCD5412_Set_Duration(MPTAC_TPU_INDEX,SPARK_Mptac[ spark_select ], \
                        SPARK_Channel[in_cylinder].duration[SPARK_DWELL_INDEX_MAIN_PULSE].on_time );

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
    uint32_t       end_angle;
    Spark_Control_Select_T spark_select   = SPARK_Control_Select_Map[in_cylinder_id];

    // Update the end angle information:
    MCD5412_Set_Angle(MPTAC_TPU_INDEX, SPARK_Mptac[spark_select], injection_angle );

    // Request that a new pulse be set up:
    MCD5412_Request_Pulse( MPTAC_TPU_INDEX,  SPARK_Mptac[spark_select] );

    // Request that the new angle information is used.
    MCD5412_Request_Update( MPTAC_TPU_INDEX, SPARK_Mptac[spark_select] );

    SPARK_Spark_Scheduled = true;
}

//=============================================================================
// SPARK_Update_Current_Pulse
//=============================================================================
static void SPARK_Update_Current_Pulse(
    Crank_Cylinder_T  in_cylinder_id,
    uint8_t           in_number_of_cylinder_events )
{
    uint32_t       end_angle;
    Spark_Control_Select_T spark_select   = SPARK_Control_Select_Map[in_cylinder_id];

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

    spark_advance = SPARK_Channel[in_cylinder_id].advance_count;

    if ( SPARK_CALC_POSITION_Ref == calc_position ) {
        // Calculate the spark angle in reference to the current tdc:
        tdc_angle = ( SPARK_Angle_From_Cylinder_Event_To_TDC + SPARK_Angle_At_Cylinder_Event );
        // convert the signed angle in counts to the pulse accumulated counts needed by the primitive
        angle_in_pa_counts = tdc_angle - spark_advance;
        future_cylinder_event_counts = (uCrank_Angle_T)( ( ( in_number_of_cylinder_events * CRANK_Get_Parameter( CRANK_PARAMETER_INITIAL_VIRTUAL_TEETH_PER_CYLINDER_EVENT, 0, 0 ) ) << CRANK_ANGLE_PRECISION ) & uCRANK_ANGLE_MAX);
        // Calculate the true end angle in pulse counts for this cylinder given the current counts:
        end_angle =    (uint32_t)( ( angle_in_pa_counts + future_cylinder_event_counts ) & uCRANK_ANGLE_MAX );
        SPARK_Calculated_End_Angle_In_Counts[in_cylinder_id] = end_angle;
    } else {
        // Calculate the spark angle in reference to the next tdc:
        tdc_angle = ( SPARK_Angle_From_Cylinder_Event_To_TDC + SPARK_Angle_At_Cylinder_Event );
        // convert the signed angle in counts to the pulse accumulated counts needed by the primitive
        angle_in_pa_counts = tdc_angle - spark_advance;
        future_cylinder_event_counts = (uCrank_Angle_T)( ( ( in_number_of_cylinder_events * CRANK_Get_Parameter( CRANK_PARAMETER_INITIAL_VIRTUAL_TEETH_PER_CYLINDER_EVENT, 0, 0 ) ) << CRANK_ANGLE_PRECISION ) & uCRANK_ANGLE_MAX);
        // Calculate the true end angle in pulse counts for this cylinder given the current counts:
        end_angle =    (uint32_t)( ( angle_in_pa_counts + future_cylinder_event_counts ) & uCRANK_ANGLE_MAX );
        SPARK_Calculated_End_Angle_In_Counts[in_cylinder_id] = end_angle;
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
static void SPARK_Update_Duration_Values(Spark_Control_Select_T in_spark_select, Crank_Cylinder_T in_cylinder )
{
    uint32_t base_frequency = TPU_TIMER_Get_Base_Frequency(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ] );

    /* check whether the spark channel is disabled */
    if (SPARK_Channel[in_cylinder].state == false) {
        MCD5412_Set_Min_Duration(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ], 0);
        MCD5412_Set_Duration(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ], 0);
        MCD5412_Set_Max_Duration(MPTAC_TPU_INDEX, SPARK_Mptac[SPARK_CONTROL_0], 0);
        MCD5412_Set_Extra_Pulses(MPTAC_TPU_INDEX, 0);
        return;
    }

    /* set main pulse duration */
    MCD5412_Set_Min_Duration(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ], SPARK_Min_Duration );
    MCD5412_Set_Duration(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ], \
                        SPARK_Channel[in_cylinder].duration[SPARK_DWELL_INDEX_MAIN_PULSE].on_time );
    MCD5412_Set_Max_Duration(MPTAC_TPU_INDEX,  SPARK_Mptac[ SPARK_CONTROL_0 ], SPARK_Max_Duration );


    SPARK_Set_Max_Fall_Angle_InToothCount = (uint8_t)SPARK_DWELL_MPTAC_MAX_FALL_ANGLE_IN_TOOTHCOUNT;
    SPARK_Set_Min_Angle_For_Rise_InToothCount = (uint8_t)( ( SPARK_DWELL_ABSOLUTE_MAXVALUE_IN_SEC * (CRANK_VIRTUAL_TEETH_PER_CRANK/2))\
            * base_frequency / CRANK_Get_Parameter( CRANK_PARAMETER_HI_RES_REFERENCE_PERIOD, 0, 0 ) );
    if ( SPARK_Set_Min_Angle_For_Rise_InToothCount > (uint8_t)(SPARK_DWELL_LIMIT_IN_REFPERIOD_PERCENT*CRANK_VIRTUAL_TEETH_PER_CRANK/2) ) {
        SPARK_Set_Min_Angle_For_Rise_InToothCount = (uint8_t)(SPARK_DWELL_LIMIT_IN_REFPERIOD_PERCENT*CRANK_VIRTUAL_TEETH_PER_CRANK/2);
    } else {
        // nothing
    }
    MCD5412_Set_Min_Angle_For_Rise(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ], SPARK_Set_Min_Angle_For_Rise_InToothCount );
    MCD5412_Set_Max_Fall_Angle(MPTAC_TPU_INDEX, SPARK_Mptac[ SPARK_CONTROL_0 ], SPARK_Set_Max_Fall_Angle_InToothCount );

    /* set extra pulses, if extra pulses are required, update On/Off times for extra pulses */
    MCD5412_Set_Extra_Pulses(MPTAC_TPU_INDEX, SPARK_Channel[in_cylinder].extra_pulse);
    if (SPARK_Channel[in_cylinder].extra_pulse == 1) {              /* for extra pulse 1 */
        MCD5412_Set_Min_Off_Time(MPTAC_TPU_INDEX, SPARK_Mptac[in_spark_select], \
                                SPARK_Channel[in_cylinder].duration[SPARK_DWELL_INDEX_MAIN_PULSE].off_time);
        MCD5412_Set_On_Time_2( MPTAC_TPU_INDEX, \
                                SPARK_Channel[in_cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_1].on_time);
    }
    if (SPARK_Channel[in_cylinder].extra_pulse == 2) {              /* for extra pulse 2 */
        MCD5412_Set_Min_Off_Time(MPTAC_TPU_INDEX, SPARK_Mptac[in_spark_select], \
                                SPARK_Channel[in_cylinder].duration[SPARK_DWELL_INDEX_MAIN_PULSE].off_time);
        MCD5412_Set_On_Time_2( MPTAC_TPU_INDEX, \
                                SPARK_Channel[in_cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_1].on_time);
        MCD5412_Set_Off_Time_2( MPTAC_TPU_INDEX, \
                                SPARK_Channel[in_cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_1].off_time );
        MCD5412_Set_On_Time_3( MPTAC_TPU_INDEX, \
                                SPARK_Channel[in_cylinder].duration[SPARK_DWELL_INDEX_EXTRA_PULSE_2].on_time );
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

void SPARK_Process_Interrupt(Spark_Control_Select_T in_spark_select )
{
    Crank_Cylinder_T        cylinder = 0;
    Spark_Control_Select_T  control_select;
    uCrank_Angle_T          end_angle;

    // Get the amount of EST dwell which was delivered:
    SPARK_Actual_Duration = MCD5412_Get_Actual_Duration(MPTAC_TPU_INDEX, SPARK_Mptac[ in_spark_select ]);

    // Calculate the next EST channel, and output the
    // EST control signals and the SEL1/0 signals:
    if( SPARK_Enable ) {
        // For the diagnostic routine
        cylinder = CRANK_Increment_Cylinder_ID(SPARK_Cylinder_Event_ID, 1);

        control_select = SPARK_Control_Select_Map[cylinder];
        // If there is a channel without a fault, update its values and set it up:
        if( SPARK_Get_Channel_Enable(cylinder) && (SPARK_Scheduled_SynControl < 2)) {
            /* Set the channel number, if disabled, swith it to channel D */
            if (SPARK_Channel[cylinder].state == true) {
                VSEP_EST_Select_Set_Channel(MTSA_CONFIG_VSEP_DEVICE_0, CeVSEP_EST_CylinderID_Mapping[cylinder]);
            } else {
                VSEP_EST_Select_Set_Channel(MTSA_CONFIG_VSEP_DEVICE_0, CRANK_CYLINDER_D);
            }

            /* set end angle, the reference tdc is next tdc */
            end_angle = SPARK_Calculate_End_Angle_In_Counts(cylinder, (uint8_t)1, SPARK_CALC_POSITION_Isr );
            SPARK_Update_Duration_Values(control_select, cylinder);
            /* start next pulse request */
            SPARK_Schedule_Next_Event(cylinder, end_angle );
        }
        SPARK_Scheduled_SynControl = 0;
    }
}


//=============================================================================
// SPARK_Process_Cylinder_Event
//=============================================================================
void SPARK_Process_Cylinder_Event( void )
{
    uint32_t          cs;
    uint32_t          counter;
    Crank_Cylinder_T  channel;
    uCrank_Angle_T    end_angle;

    cs = Enter_Critical_Section();
    SPARK_Cylinder_Event_ID       = CRANK_Get_Cylinder_ID();
    SPARK_Angle_At_Cylinder_Event = CRANK_Get_Parameter( CRANK_PARAMETER_ANGLE_AT_CYLINDER_EVENT, 0, 0 );
    Leave_Critical_Section( cs );

    if( SPARK_Enable ) {
        if(!SPARK_ISR_PulseRequested) {
            for( counter = 0; counter < SPARK_Control_Select_Max; counter++ ) {
                channel = CRANK_Increment_Cylinder_ID(SPARK_Cylinder_Event_ID, 1);
                MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[counter], true );
                // Put the cylinder ID for this est control to the correct value
                VSEP_EST_Select_Set_Channel(MTSA_CONFIG_VSEP_DEVICE_0, CeVSEP_EST_CylinderID_Mapping[channel]);
                // Setup the initial cylinders for normal operation,  Update the end angle information
                SPARK_Update_Duration_Values(SPARK_CONTROL_0, channel);
                end_angle = SPARK_Calculate_End_Angle_In_Counts( channel, (uint8_t)counter, SPARK_CALC_POSITION_Ref );
                SPARK_Schedule_Next_Event(channel, end_angle);
            }
            SPARK_ISR_PulseRequested = true;
            SPARK_Scheduled_SynControl ++;
        } else {
                /* Set the channel number, if disabled, swith it to channel D */
                if (SPARK_Channel[SPARK_Cylinder_Event_ID].state == true) {
                    VSEP_EST_Select_Set_Channel(MTSA_CONFIG_VSEP_DEVICE_0, CeVSEP_EST_CylinderID_Mapping[SPARK_Cylinder_Event_ID]);
                } else {
                    VSEP_EST_Select_Set_Channel(MTSA_CONFIG_VSEP_DEVICE_0, CRANK_CYLINDER_D);
                }
                SPARK_Update_Duration_Values(SPARK_CONTROL_0, SPARK_Cylinder_Event_ID);
                end_angle = SPARK_Calculate_End_Angle_In_Counts( SPARK_Cylinder_Event_ID, (uint8_t)0, SPARK_CALC_POSITION_Ref );
                SPARK_Schedule_Next_Event(SPARK_Cylinder_Event_ID, end_angle);
                
                /* increase the syncontrol var, if syncontrol==2, multipulse pass next event tooth */
                SPARK_Scheduled_SynControl ++;
        }
    }
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
    MCD5412_Set_Host_Interrupt_Status(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[ 0 ], false);

    if( !SPARK_Override_Enabled ) {
        SPARK_Process_Interrupt( SPARK_CONTROL_0 );
    }
}




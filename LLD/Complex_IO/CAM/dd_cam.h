#ifndef DD_CAM_H
#define DD_CAM_H

//=============================================================================
//   Includes
//=============================================================================
#include "reuse.h"
#include "dd_mcd5411.h"
#include "dd_crank.h"

//=============================================================================
//   Type declaration
//=============================================================================

//=============================================================================
// @enum Cam_Parameter_T
//=============================================================================
typedef enum Cam_Parameter_Tag {
	CAM_PARAMETER_1,
	CAM_PARAMETER_MAX
}  Cam_Parameter_T;

typedef enum {
	CAM1,
	CAM2,
	CAM3,
	CAM4,
	NUMBER_OF_CAM_SENSORS
} CAM_Sensors_T;

typedef struct CAM_Profile_Data_Tag {
	uint8_t  Duty_Cycle_Min;
	uint8_t  Duty_Cycle_Max;
	uint16_t Edge_Angle;
	uint8_t  Crank_Teeth_Per_Pulse;
} CAM_Profile_Data_T;

typedef struct IO_Cam_Initialization_Parameters_Tag {
	uCrank_Angle_T       cam_read_angle;
	bool                *CAM_Active_State;
	uint32_t             number_of_gaps_before_sync;
	bool                 use_cam_toggle;
	uint32_t             number_of_toggles_before_sync;
	CAM_Profile_Data_T  *cam_profile_data;
	uint8_t              cam_profile_data_pulse_count;
	uint8_t              cam_min_pulses_for_sync;
	CAM_Sensors_T        cam_sensor_for_sync;
	uint8_t              cam_edge_before_gap;
	uint8_t              delta_teeth_from_edge_to_tooth_1;
	uint8_t              cam_cyl_id_before_gap;
}  IO_Cam_Initialization_Parameters_T;


// Number of ticks per crank tooth to be used in generating an angle clock:
#define NUMBER_TICKS_PER_CRANK_TOOTH ( 16 )
#define NUMBER_TICKS_PER_CRANK_EDGE (NUMBER_TICKS_PER_CRANK_TOOTH / 2)

typedef enum {
	CAM_FLAG_POWER_UP,
	CAM_FLAG_SYNC_STARTED,
	CAM_FLAG_FIRST_SYNC_OCCURRED,
	CAM_FLAG_BACKUP_SYNC_OCCURED,
	CAM_FLAG_RESYNC_IN_PROGRESS
} CAM_Sync_Mode_T;


//=============================================================================
//   Type declarations
//=============================================================================
// @enum Cam_Sensor_Flag_T | Defines flag position in the 32 bit uint
typedef enum Cam_Sensor_Flag_Tag {
	CAM_SENSOR_FLAG_ENABLE_INTERRUPT_ON_CRITICAL_EDGE,       // @emem enable or disable interrupts on critical transitions - irq_crit_edge   ( 0=disable, 1=enable )
	CAM_SENSOR_FLAG_ENABLE_INTERRUPT_ON_NON_CRITICAL_EDGE,   // @emem enable or disable interrupts on non-critical transitions - irq_ncrit_edge  ( 0=disable, 1=enable ) 
	CAM_SENSOR_FLAG_ENABLE_REPLICATED_CAM_OUTPUT,            // @emem (24 bits) The amount of time by which the replicated cam output signal will lag the cam input signal. Units correspond with the Use_TCR2 bit. Only valid when Rep_Out_En = 1.
	CAM_SENSOR_FLAG_STATUS_LAST_EDGE_WAS_CRITICAL,           // @emem will return true if the last transition was a critical edge.
	CAM_SENSOR_FLAG_STATUS_TIMEOUT                           // @emem will return true if there is a timeout between edges.
}  Cam_Sensor_Flag_T;

// @enum CAM_Index_Type | Defines CAM sensor index
typedef enum {
	CAM_W                   = 0,
	CAM_X                   = 1,
	CAM_Y                   = 2,
	CAM_Z                   = 3,
	CAM_VOID                = 255
} CAM_Index_Type;


//=============================================================================
//   Type declarations
//=============================================================================
// @enum Cam_Sensor_Parameter_T | Defines parameter requested for non-coherent gets and sets
typedef enum Cam_Sensor_Parameter_Tag {
	CAM_SENSOR_PARAMETER_OFF_PERIOD,                      // @emem from the non-critical edge time to the critical edge time.  This values update on the critical edge
	CAM_SENSOR_PARAMETER_ON_PERIOD,                       // @emem starting with the previous critical edge ending with the  non critical edge
	CAM_SENSOR_PARAMETER_MIN_PERIOD,                      // @emem limit the rate at which the primitive can interrupt the CPU if some fault condition creates a high frequency signal at the CAM input
	CAM_SENSOR_PARAMETER_REPLICATED_CAM_OUTPUT_LAG_TIME,  // @emem The amount of time by which the replicated cam output signal will lag the cam input signal. Units correspond with the Use_TCR2 bit. Only valid when Rep_Out_En = 1.
	CAM_SENSOR_PARAMETER_CRITICAL_EDGE_TIME,              // @emem The cam critical edge time
	CAM_SENSOR_PARAMETER_CRITICAL_EDGE_COUNT,             // @emem The cam critical edge time
	CAM_SENSOR_PARAMETER_NON_CRITICAL_EDGE_COUNT,         // @emem The cam non critical edge count
	CAM_SENSOR_PARAMETER_NON_CRITICAL_EDGE_TIME,          // @emem The cam non critical edge time
	CAM_SENSOR_PARAMETER_NOISE_COUNT,                     // @emem The noise count
	CAM_SENSOR_PARAMETER_PERIOD,                          // @emem The period between the last two critical cam
	CAM_SENSOR_PARAMETER_NON_CRITICAL_ANGLE_BUFFERED,     // @emem Buffered value of NCrit_TCR2 so as to be coherent with other critical edge data
	CAM_SENSOR_PARAMETER_NON_CRITICAL_ANGLE               // @emem A snapshot of the TCR2 taken at the non-critical cam edge
}  Cam_Sensor_Parameter_T;

typedef struct Cam_Sensor_Coherent_Tag {
	uint16_t current_crank_count_at_critical_edge;
	uint16_t previous_crank_count_at_critical_edge;
	uint16_t current_crank_count_at_non_critical_edge_buffered;
	uint16_t previous_crank_count_at_non_critical_edge_buffered;
	uint16_t current_crank_count_at_last_non_critical_edge;
	uint16_t previous_crank_count_at_last_non_critical_edge;
	uint32_t current_critical_time;
	uint32_t previous_critical_time;
}  Cam_Sensor_Coherent_T;

typedef struct {
	uint32_t          Count;          // Edge count, this member seems to be angle, not count
	uint32_t          Time;           // Edge time
	uint32_t          Edge_Period;    // two valid edge period
	bool              Valid_Edge;     // Set first time a valid edge is seen
	uint16_t          Zero_Edge_Count;// Background counter incremented, in a periodic loop and cleared on each edge.
}  CAM_Edge_Data_T;

#endif // DD_CAM_H

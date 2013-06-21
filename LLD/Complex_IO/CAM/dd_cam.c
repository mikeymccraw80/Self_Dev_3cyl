
//=============================================================================
//   Includes files
//=============================================================================
#include "reuse.h"
#include "dd_cam.h"
#include "dd_crank_interface.h"
#include "io_config_cam.h"
#include "io_config_tpu.h"
#include "io_conversion.h"

//=============================================================================
//   Type declaration
//=============================================================================

//=============================================================================
// Variable declarations
//=============================================================================
uint16_t       CAM_Reset_Reference_Counter;
uint8_t        CAM_State_Change_Occurred;          // bit packed array
uint8_t        CAM_State_Change_Occurred_This_Rev; // bit packed array
uint8_t        CAM_Stuck;                          // bit packed array
uint8_t        CAM_EdgeDetected;                   // bit packed array
bool           CAM_Sensor_State;
bool           CAM_Previous_State;
bool           CAM_Not_Synched;
bool           CAM_Stuck_At_Gap2;
bool           CAM_Estimated_State;
uint8_t        CAM_Correct_Toggles;
uint32_t       CAM_Crank_Number_Gaps_Detected;

CAM_Sensors_T  CAM_Sensor_In_Use;

uint8_t        CAM_Number_Of_Cylinders;
uint8_t        CAM_Number_Of_Sensors;
uint8_t        CAM_Number_Of_Pulses;

static IO_Cam_Initialization_Parameters_T  *CAM_Initialization_Parameters;

//=============================================================================
// Variable Definitions
//=============================================================================
Cam_Sensor_Coherent_T    CAM_Sensor_Coherent_data[CAM_NUMBER_OF_SENSORS];
CAM_Edge_Data_T          CAM_Edge_Data[CAM_NUMBER_OF_SENSORS * CAM_NUMBER_OF_PULSES];
uint32_t                 CAM_Current_Edge_Period[CAM_NUMBER_OF_SENSORS];
uint8_t                  CAM_Current_Edge[CAM_NUMBER_OF_SENSORS];
uint8_t                  CAM_Total_Edge[CAM_NUMBER_OF_SENSORS];

//=============================================================================
// Extern Function Prototypes
//=============================================================================
void OS_CAM_W_Hook(void);
void OS_CAM_X_Hook(void);
//=============================================================================
// Local Function Prototypes
//=============================================================================

//=============================================================================
// CAM_Reset_Parameters
//=============================================================================
void CAM_Reset_Parameters( void )
{
	CAM_Not_Synched                     = true;
	CAM_Correct_Toggles                 = 0;
	CAM_Stuck                           = 0;
	CAM_State_Change_Occurred           = 0;
	CAM_State_Change_Occurred_This_Rev  = 0;
	CAM_EdgeDetected                    = 0;
	CAM_Reset_Reference_Counter         = 0;
}
//=============================================================================
// CAM_Initialize
//=============================================================================
void CAM_Initialize(IO_Cam_Initialization_Parameters_T  * const in_initialization_parameters )
{
	CAM_Number_Of_Sensors = (uint8_t)CAM_INITIALIZATION_PARAMETERS.cam_sensor_for_sync;
	CAM_Number_Of_Pulses = in_initialization_parameters->cam_profile_data_pulse_count;
	CAM_Number_Of_Cylinders = CRANK_Get_Number_Of_Cylinders();
	CAM_Sensor_In_Use = CAM1;
	CAM_Initialization_Parameters = in_initialization_parameters;

	CAM_Reset_Parameters();
}

//=============================================================================
// CAM_Initialize_4X_Config
//=============================================================================
void CAM_Initialize_4X_Config( uint8_t cam_index )
{
	uint32_t min_period = (uint32_t)(CAMe_MIN_PERIOD_IN_SEC * TPU_A_TCR1_CLOCK_FREQ);

	MCD5411_Set_Parameter(CAME_TPU_INDEX ,CAM_CAME[cam_index], CAM_SENSOR_PARAMETER_MIN_PERIOD, min_period);
	MCD5411_Initialize_Channel(CAME_TPU_INDEX ,&TPU, CAM_CAME[cam_index], &CAM_INIT);
	MCD5411_Set_Host_Interrupt_Status(CAME_TPU_INDEX ,&TPU, CAM_CAME[cam_index], false);
	MCD5411_Set_Host_Interrupt_Enable(CAME_TPU_INDEX, &TPU,  CAM_CAME[cam_index], true );
}


//=============================================================================
// CAM_Lo_Res_Event_Tasks
//=============================================================================
void CAM_Lo_Res_Event_Tasks(void)
{
	CAM_State_Change_Occurred = Insert_Bits( CAM_State_Change_Occurred, false, CAM_Sensor_In_Use, 1 );
}

//=============================================================================
// CAM_SetStuck
//=============================================================================
void CAM_Set_Stuck(CAM_Sensors_T  in_sensor, bool in_stuck )
{
	CAM_Stuck = Insert_Bits( CAM_Stuck, in_stuck, CAM_Sensor_In_Use, 1 );
}


//=============================================================================
// CAM_Get_Stuck
//=============================================================================
bool CAM_Get_Stuck(CAM_Sensors_T  in_sensor )
{
	bool return_state = Extract_Bits( CAM_Stuck, in_sensor, 1 );

	return return_state;
}


//=============================================================================
// CAM_Reset_Stuck
//=============================================================================
void CAM_Reset_Stuck(CAM_Sensors_T  in_sensor )
{
	if( Extract_Bits( CAM_Stuck, CAM_Sensor_In_Use, 1 )) {
		if(CAM_Reset_Reference_Counter == (CRANK_Get_Number_Of_Cylinders() / 2 - 1)) {
			CAM_Stuck = Insert_Bits( CAM_Stuck, false, CAM_Sensor_In_Use, 1 );
			CAM_Reset_Reference_Counter  = 0;
		} else {
		CAM_Reset_Reference_Counter++;
		}
	} else {
		CAM_Reset_Reference_Counter = 0;
	}
}

static bool       cam_active_state;
//=============================================================================
// CAM_Update_State
//  Description:         Determine cam state and cylinder synch event
//
//  Parameters:          None
//  Return:              None
//=============================================================================
void CAM_Update_State( void )
{
	uint32_t          counter;
	Crank_Cylinder_T  cylinderID;
	bool              use_cam_toggle = CAM_Initialization_Parameters->use_cam_toggle;
	uint32_t          cam_history;

	cam_history  = CRANK_Get_Parameter( CRANK_PARAMETER_CAM_HISTORY, 0, 0);

	//Get CAM state at current tooth
	CAM_Sensor_State = (bool)( cam_history & 0x01);
	cam_active_state  = CAM_Initialization_Parameters->CAM_Active_State[CAM_Sensor_In_Use];

	CAM_Crank_Number_Gaps_Detected = CRANK_Get_Parameter( CRANK_PARAMETER_NUMBER_OF_GAPS_DETECTED, 0, 0);

	if ( ( CAM_Crank_Number_Gaps_Detected == 2 ) && ( CAM_Sensor_State == CAM_Previous_State ) ) {
		CAM_Stuck_At_Gap2 = true;
	} else {
		//  CAM_Crank_Number_Gaps_Detected >= 3 || CAM_Crank_Number_Gaps_Detected <= 1
		CAM_Stuck_At_Gap2 = false;  
	}

	if ( use_cam_toggle ) {
		//==========================================================================
		// estimated CAM phase logic. The CAM phase is estimated based on the first
		// reliable read, then toggled. The actual CAM is used for diagnostic only 
		//==========================================================================
		if ( CAM_Not_Synched ) {
			// as long as CAM signal is not reliable, the estimated CAM equals the actual measured phase.
			CAM_Estimated_State = CAM_Sensor_State;
		} else {
			// after the second gap it is toggled each CAM event
			CAM_Estimated_State = !CAM_Estimated_State;
		}

		// Determine if cam state has changed since last crank rotation
		if( (CAM_Sensor_State != CAM_Previous_State) || CAM_Not_Synched ) {
			// Wait until the second 58x gap for a reliable cam sensor signal:
			if ( CAM_Crank_Number_Gaps_Detected >= CAM_Initialization_Parameters->number_of_gaps_before_sync ) {
				// Number of reliable Cam Reads (The cam is togling correctly before sync. )
				if ( CAM_Correct_Toggles < CAM_Initialization_Parameters->number_of_toggles_before_sync ) {
					CAM_Correct_Toggles++;
				} else {  
					// CAM is considered reliable after a cal. nb. of correct toggles
					CAM_Not_Synched = false;
				}
			} else {
				CAM_Correct_Toggles++;
			}

			// Indicate cam signal is not stuck in last state
			CAM_Stuck = Insert_Bits( CAM_Stuck, false, CAM_Sensor_In_Use, 1 );

			// Update previous cam state with current state
			CAM_Previous_State = CAM_Sensor_State;
		} else {
			// Indicate cam signal is stuck:
			CAM_Stuck = Insert_Bits( CAM_Stuck, true, CAM_Sensor_In_Use, 1 );
		}

		// Determine if cam occurred
		if( CAM_Estimated_State == cam_active_state ) {
			// Indicate correct cylinder event
			cylinderID = CAM_Number_Of_Cylinders - 1;
			CAM_State_Change_Occurred          = Insert_Bits( CAM_State_Change_Occurred,          true, CAM_Sensor_In_Use, 1 );
			CAM_State_Change_Occurred_This_Rev = Insert_Bits( CAM_State_Change_Occurred_This_Rev, true, CAM_Sensor_In_Use, 1 );

			for (counter = 0; counter < CAM_NUMBER_OF_SENSORS; counter++ ) {
				CAM_Current_Edge[counter] = CAM_Initialization_Parameters->cam_edge_before_gap;
			}
		} else {
			cylinderID = ( CAM_Number_Of_Cylinders / 2 ) - 1;
			CAM_State_Change_Occurred          = Insert_Bits( CAM_State_Change_Occurred,          false, CAM_Sensor_In_Use, 1 );
			CAM_State_Change_Occurred_This_Rev = Insert_Bits( CAM_State_Change_Occurred_This_Rev, false, CAM_Sensor_In_Use, 1 );
		}

		// Indicate correct cylinder event:
		CRANK_Set_Cylinder_ID( cylinderID );
	} else {
		/* Determine if cam state has changed since last crank rotation */
		if(( CAM_Sensor_State != CAM_Previous_State ) || CAM_Not_Synched ) {
			/* Wait until the second 58x gap for a reliable cam sensor signal: */
			if( CAM_Crank_Number_Gaps_Detected >= CAM_Initialization_Parameters->number_of_gaps_before_sync ) {
				/* Indicate cam has now been read reliably at least once: */
				CAM_Not_Synched = false;
			}

			/* Indicate cam signal is not stuck in last state: */
			CAM_Stuck = Insert_Bits( CAM_Stuck, false, CAM_Sensor_In_Use, 1 );

			/* Determine if cam occurred: */
			if( CAM_Sensor_State == cam_active_state ) {
				/* Indicate correct cylinder event: */
				cylinderID = CAM_Number_Of_Cylinders - 1;
				CAM_State_Change_Occurred          = Insert_Bits( CAM_State_Change_Occurred,          true, CAM_Sensor_In_Use, 1 );
				CAM_State_Change_Occurred_This_Rev = Insert_Bits( CAM_State_Change_Occurred_This_Rev, true, CAM_Sensor_In_Use, 1 );

				for (counter = 0; counter < CAM_NUMBER_OF_SENSORS; counter++ ) {
					CAM_Current_Edge[counter] = CAM_Initialization_Parameters->cam_edge_before_gap;
				}
			} else {
				cylinderID = ( CAM_Number_Of_Cylinders / 2 ) - 1;
				CAM_State_Change_Occurred          = Insert_Bits( CAM_State_Change_Occurred,          false, CAM_Sensor_In_Use, 1 );
				CAM_State_Change_Occurred_This_Rev = Insert_Bits( CAM_State_Change_Occurred_This_Rev, false, CAM_Sensor_In_Use, 1 );
			}

			// Ignore CAM sensor for sync after calibrated number of gaps are detected.
			// 255 = override, always use CAM for sync (do not ignore).
			if( ( CAM_Crank_Number_Gaps_Detected <= CAM_Initialization_Parameters->number_of_toggles_before_sync ) || 
			( 255 == CAM_Initialization_Parameters->number_of_toggles_before_sync ) )
			{
				/* Indicate correct cylinder event: */
				CRANK_Set_Cylinder_ID( cylinderID );
			}
			/* Update previous cam state with current state: */
			CAM_Previous_State = CAM_Sensor_State;
		} else {
			/* Indicate cam signal is stuck: */
			CAM_Stuck = Insert_Bits( CAM_Stuck, true, CAM_Sensor_In_Use, 1 );
		}
	}
} 

//=============================================================================
// CAM_Get_Sensor_State
//=============================================================================
bool CAM_Get_Sensor_State(CAM_Sensors_T  in_sensor )
{
	return CAM_Sensor_State;
}

//=============================================================================
// CAM_Use_Sensor
//=============================================================================
void CAM_Select_Sensor(CAM_Sensors_T  in_sensor )
{
	CAM_Sensor_In_Use = in_sensor;

	// set CAM channel
	MCD5408_Set_Cam_Channel(EPPWMT_TPU_INDEX, CAM_CAME[in_sensor].F.TPU_CHANNEL_CONFIGURATION_CHANNEL);
}


//=============================================================================
// CAM_Get_Sensor_In_Use
//=============================================================================
CAM_Sensors_T CAM_Get_Selected_Sensor( void )
{
	return CAM_Sensor_In_Use;
}


//=============================================================================
// CAM_Set_State_Change_Occurred
//=============================================================================
void CAM_Set_State_Change_Occurred(CAM_Sensors_T  in_sensor, bool in_state_change_occurred )
{
	CAM_State_Change_Occurred = Insert_Bits( CAM_State_Change_Occurred, in_state_change_occurred, in_sensor, 1 );
}


//=============================================================================
// CAM_Get_State_Change_Occurred
//=============================================================================
bool CAM_Get_State_Change_Occurred(CAM_Sensors_T  in_sensor )
{
	bool return_state = Extract_Bits( CAM_State_Change_Occurred, in_sensor, 1);

	return return_state;
}


//=============================================================================
// CAM_Get_State_Change_Occurred_Current_Revolution
//=============================================================================
bool CAM_Get_State_Change_Occurred_Current_Revolution(CAM_Sensors_T  in_sensor )
{
	bool return_state = Extract_Bits( CAM_State_Change_Occurred_This_Rev, in_sensor, 1 );

	return return_state;
}

void CAM_Change_Active_State(void)
{
	cam_active_state = ( cam_active_state ) ? false : true;
}

//=============================================================================
// CAM_Get_Edge_Data
//=============================================================================
void CAM_Get_Edge_Data(CAM_Sensors_T     in_sensor, 
                               uint8_t           in_cam_edge,
                               Edge_Data_T*   in_cam_edge_data )
{
	in_cam_edge_data->Count = CAM_Edge_Data[(in_sensor * CAM_Number_Of_Pulses ) + in_cam_edge].Count;
	in_cam_edge_data->Time  = CAM_Edge_Data[(in_sensor * CAM_Number_Of_Pulses ) + in_cam_edge].Time;
}

//=============================================================================
// uint8_t CAM_Get_Current_Edge
//=============================================================================
uint8_t CAM_Get_Current_Edge(CAM_Sensors_T     in_sensor )
{
	return (CAM_Current_Edge[in_sensor]);
}

//=============================================================================
// uint8_t CAM_Get_Current_Edge
//=============================================================================
uint8_t CAM_Get_Total_Edge(CAM_Sensors_T     in_sensor)
{
	return CAM_Total_Edge[in_sensor];
}

//=============================================================================
// uint8_t CAM_Get_Current_Edge_Period
//=============================================================================
uint8_t CAM_Get_Current_Edge_Period(CAM_Sensors_T     in_sensor)
{
	return CAM_Current_Edge_Period[in_sensor];
}

//=============================================================================
// uint8_t CAM_Get_Current_Edge
//=============================================================================
void CAM_Set_Current_Edge(CAM_Sensors_T     in_sensor )
{
	CAM_Current_Edge[in_sensor]  = 0;
	CAM_Total_Edge[in_sensor] = 255;
}
//=============================================================================
//  FUNCTION: CAM_Increment_Cam_Edge_Counter
//=============================================================================
static uint8_t CAM_Increment_Cam_Edge_Counter(uint8_t in_cam_edge)
{
	if(in_cam_edge >= (uint8_t)( CAM_Initialization_Parameters->cam_profile_data_pulse_count - 1)) {
		in_cam_edge = 0;
	} else {
		in_cam_edge++;
	}

	return in_cam_edge;
}

//=============================================================================
// CAM_Edge_Interrupt_Handler
//=============================================================================
void CAM_Edge_Process( uint32_t in_cam_sensor )
{
	CAM_Sensors_T   cam_sensor = (CAM_Sensors_T)in_cam_sensor;
	uint32_t        cam_event_time;

	uint8_t         current_edge_index;
	uCrank_Count_T  pa_tooth_count;
	uCrank_Count_T  whole_angle_in_teeth;
	uCrank_Angle_T  cam_event_angle_fraction;
	uint32_t        delta_time;
	uint32_t        tooth_period;
	uint32_t        previous_time;
	uint32_t        current_time;

	CAM_EdgeDetected = Insert_Bits( CAM_EdgeDetected, true, cam_sensor, 1 );
	current_edge_index = CAM_Current_Edge[cam_sensor];
	CAM_Total_Edge[cam_sensor] ++;

	cam_event_time = MCD5411_Get_Parameter(CAME_TPU_INDEX ,CAM_CAME[cam_sensor], CAM_SENSOR_PARAMETER_CRITICAL_EDGE_TIME );
	cam_event_time &= UINT24_MAX;

	MCD5411_Get_Coherent_Angle_With_History(CAME_TPU_INDEX ,CAM_CAME[cam_sensor], &(CAM_Sensor_Coherent_data[cam_sensor]));

	// get the tooth before for the correct tooth period.
	pa_tooth_count = CAM_Sensor_Coherent_data[cam_sensor].current_crank_count_at_critical_edge;

	// add the distance for the current cylinder event
	// we are subtracting 1 from the value to go from [1:120] to [0.00:119.FF]
	whole_angle_in_teeth  = CRANK_Get_Parameter(CRANK_PARAMETER_CURRENT_TOOTH,0,0) -
                          ( (CRANK_Get_Parameter(CRANK_PARAMETER_CURRENT_EDGE_COUNT,0,0) -
                                     pa_tooth_count));

	current_time = CRANK_Get_Edge_Time_From_Count( pa_tooth_count);

	// Get the time from the previous edge out of the array
	previous_time =CRANK_Get_Edge_Time_From_Count( pa_tooth_count-1);

	delta_time = ( cam_event_time - current_time) & UINT24_MAX;

	// Convert the cam delta time to a crank angle
	tooth_period = ( current_time - previous_time ) & UINT24_MAX;

	// convert to delta angle from time
	cam_event_angle_fraction = IO_Convert_uTime_To_uAngle(delta_time, uCRANK_ANGLE_PRECISION, tooth_period, 1);
	CAM_Edge_Data[( cam_sensor * CAM_Number_Of_Pulses ) + current_edge_index].Count = CRANK_Convert_Teeth_To_uCrank_Angle( whole_angle_in_teeth ) + cam_event_angle_fraction;
	CAM_Edge_Data[( cam_sensor * CAM_Number_Of_Pulses ) + current_edge_index].Time = cam_event_time;
	CAM_Edge_Data[( cam_sensor * CAM_Number_Of_Pulses ) + current_edge_index].Edge_Period = tooth_period;
	CAM_Current_Edge_Period[cam_sensor] = tooth_period;
	// Increment CAM edge if edges are valid (we know where we are) else we have an issue.
	CAM_Current_Edge[cam_sensor] = CAM_Increment_Cam_Edge_Counter( CAM_Current_Edge[cam_sensor] );
}


//=============================================================================
// CAM_W_Edge_Interrupt_Handler
//=============================================================================
void CAM_W_Edge_Interrupt_Handler( void )
{
	CAM_Edge_Process(CAM_W);
	OS_CAM_W_Hook();
	MCD5411_Set_Host_Interrupt_Status(CAME_TPU_INDEX ,&TPU, CAM_CAME[CAM_W], false );
}

//=============================================================================
// CAM_X_Edge_Interrupt_Handler
//=============================================================================
void CAM_X_Edge_Interrupt_Handler( void )
{
	CAM_Edge_Process(CAM_X);
	OS_CAM_X_Hook();
	MCD5411_Set_Host_Interrupt_Status(CAME_TPU_INDEX ,&TPU, CAM_CAME[CAM_X], false );
}

//=============================================================================
// CAM_Edge_Interrupt_Handler
//=============================================================================
uint8_t CAM_Get_CAM_Current_Index( uint32_t in_cam_sensor )
{
	return CAM_Current_Edge[in_cam_sensor] ;
}

//=============================================================================
// CAM_Edge_Interrupt_Handler
//=============================================================================
uint32_t CAM_Get_CAM_Angle( uint32_t in_cam_sensor ,uint8_t index )
{
	return  CAM_Edge_Data[(in_cam_sensor*CAM_Number_Of_Pulses)+ index].Count ;
}


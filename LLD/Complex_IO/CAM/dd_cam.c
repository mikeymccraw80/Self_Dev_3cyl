
//=============================================================================
//   Includes files
//=============================================================================
#include "reuse.h"
#include "dd_cam.h"
#include "dd_crank_interface.h"
#include "io_config_cam.h"
#include "io_config_tpu.h"
#include "io_conversion.h"
#include "hal_cam.h"
#include "hwiocald.h"
#include "io_config_siu.h"
#include "dd_siu_interface.h"
#include "dd_cam_interface.h"

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
bool           CAM2_Sensor_State;
bool           CAM2_Previous_State;
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
static bool              cam_active_state;

//=============================================================================
// Crank Limp Home Mode Realize, Local Definitions
//=============================================================================
typedef enum {
	CAM_DutyCycle_X,
	CAM_DutyCycle_Y,
	CAM_DutyCycle_Z
} CAM_DutyCycle_T;

/* import global crank variables declairation */
extern uCrank_Count_T   CRANK_Current_Event_Tooth;
extern uCrank_Count_T   CRANK_Current_Event_PA_Content;
extern uCrank_Count_T   CRANK_Next_Event_PA_Content;
extern uCrank_Count_T   CRANK_Previous_Real_Edge_Count;
extern uCrank_Count_T   CRANK_Current_Real_Edge_Count;

/* import crank diagnose result */
extern bool SbEPSD_CrankNoSigTestFailed;

#define CAM_DUTY_CYCLE_LENGTH   4
#define CAM_FALLING_EDGE_NUMBER 4
static uint8_t      CAM1_DutyCycle_Circle_FIFO[CAM_DUTY_CYCLE_LENGTH];
static uint8_t      CAM1_DutyCycle_Linear_BUF[CAM_DUTY_CYCLE_LENGTH];
static uint8_t      CAM1_Falling_Edge_Tooth_Number[CAM_DUTY_CYCLE_LENGTH];
static uint32_t     CAM1_Period_Circle_FIFO[CAM_DUTY_CYCLE_LENGTH];
static uint32_t     CAM1_Period_Average_Value;
static uint32_t     CAM1_Period_Off_Circle_FIFO[CAM_DUTY_CYCLE_LENGTH];
static uint8_t      CAM1_Circle_FIFO_Index;
static Crank_Cylinder_T CAM_Backup_Edge_Cylinder_ID;

uint32_t     CAM1_Backup_Falling_Edge_Time;

#define CAM_CRANK_DIAGNOSE_MAX_Fail_COUNT 2
static uint8_t      CAM1_CRANK_Diagnose_Fail_Count;

/* vcpc monitor variable */
static uint8_t      CAM1_VCPC_Whole_Tooth_Count[4];
static uint8_t      CAM2_VCPC_Whole_Tooth_Count[4];
static uint32_t     CAM1_VCPC_Fraction_Angle[4];
static uint32_t     CAM2_VCPC_Fraction_Angle[4];

/* cam stuck backup */
static bool         CAM1_BACKUP_FLAG;

static const Crank_Cylinder_T CAM_DutyCycle_Cylinder_Map[] =
{
	CRANK_CYLINDER_D,
	CRANK_CYLINDER_C,
	CRANK_CYLINDER_B,
	CRANK_CYLINDER_A
};

static Crank_Cylinder_T CAM_Get_DutyCycle_Pattern_CylinderID(uint8_t *buf);

#define IS_IN_RANGE(val, min, max) (((val) >= (min)) && ((val) <= (max)))

//=============================================================================
// name:      CAM_Get_DutyCycle_Pattern_CylinderID
// parameter:
// mark     : this function is called in cam edge interrupt, calculate the next syn
//            cylinder id
//=============================================================================
static Crank_Cylinder_T CAM_Get_DutyCycle_Pattern_CylinderID(uint8_t *buf)
{
	int buf_index = 0;
	CAM_DutyCycle_T pattern_array[CAM_FALLING_EDGE_NUMBER];

	for (buf_index = 0; buf_index < CAM_FALLING_EDGE_NUMBER; buf_index++) {
		if (IS_IN_RANGE(buf[buf_index], 5, 50)) {
			pattern_array[buf_index] = CAM_DutyCycle_X;
		} else if (IS_IN_RANGE(buf[buf_index], 55, 95)) {
			pattern_array[buf_index] = CAM_DutyCycle_Y;
		} else {
			pattern_array[buf_index] = CAM_DutyCycle_Z;
		}
	}
	if (pattern_array[0] == CAM_DutyCycle_X) {
		if (pattern_array[1] == CAM_DutyCycle_X) {
			if ((pattern_array[2] == CAM_DutyCycle_Y) && (pattern_array[3] == CAM_DutyCycle_Y))
				return CRANK_CYLINDER_C;
			else
				return CRANK_CYLINDER_NULL;
		} else if (pattern_array[1] == CAM_DutyCycle_Y) {
			if ((pattern_array[2] == CAM_DutyCycle_Y) && (pattern_array[3] == CAM_DutyCycle_X))
				return CRANK_CYLINDER_D;
			else
				return CRANK_CYLINDER_NULL;
		} else {
			return CRANK_CYLINDER_NULL;
		}
	} else if (pattern_array[0] == CAM_DutyCycle_Y) {
		if (pattern_array[1] == CAM_DutyCycle_X) {
			if ((pattern_array[2] == CAM_DutyCycle_X) && (pattern_array[3] == CAM_DutyCycle_Y))
				return CRANK_CYLINDER_B;
			else
				return CRANK_CYLINDER_NULL;
		} else if (pattern_array[1] == CAM_DutyCycle_Y) {
			if ((pattern_array[2] == CAM_DutyCycle_X) && (pattern_array[3] == CAM_DutyCycle_X))
				return CRANK_CYLINDER_A;
			else
				return CRANK_CYLINDER_NULL;
		} else {
			return CRANK_CYLINDER_NULL;
		}
	} else {
		return CRANK_CYLINDER_NULL;
	}

	return CRANK_CYLINDER_NULL;
}

//=============================================================================
// Extern Function Prototypes
//=============================================================================
void OS_CAM_W_Hook(void);
void OS_CAM_X_Hook(void);
void OS_CAM_READ_Hook(void);
//=============================================================================
// Local Function Prototypes
//=============================================================================

//=============================================================================
// CAM_Reset_Parameters
//=============================================================================
void CAM_Reset_Parameters( void )
{
	uint8_t count;

	CAM_Not_Synched                     = true;
	CAM_Correct_Toggles                 = 0;
	CAM_Stuck                           = 0;
	CAM_State_Change_Occurred           = 0;
	CAM_State_Change_Occurred_This_Rev  = 0;
	CAM_EdgeDetected                    = 0;
	CAM_Reset_Reference_Counter         = 0;
	CAM1_Period_Average_Value           = UINT24_MAX;
	CAM_Backup_Edge_Cylinder_ID         = CRANK_CYLINDER_NULL;

	for (count = 0; count < CAM_DUTY_CYCLE_LENGTH; count++) {
		CAM1_DutyCycle_Circle_FIFO[count] = 0;
		CAM1_Period_Circle_FIFO[count] = 0;
		CAM1_Period_Off_Circle_FIFO[count] = 0;
		CAM1_Circle_FIFO_Index = 0;
	}
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
// CAM_Application_Event_Tasks
//=============================================================================
void CAM_Application_Event_Tasks(void)
{
	/* clear cam occurred flag for cam rational diagnose */
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


//=============================================================================r
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
	Crank_Cylinder_T  pattern_cylinder_id;

	cam_history  = CRANK_Get_Parameter( CRANK_PARAMETER_CAM_HISTORY, 0, 0);

	//Get CAM state at current tooth
	CAM_Sensor_State = (bool)( cam_history & 0x01);
	CAM2_Sensor_State = (bool)HAL_Get_CAM_Level(CAM2);;
	cam_active_state  = CAM_Initialization_Parameters->CAM_Active_State[CAM_Sensor_In_Use];

	CAM_Crank_Number_Gaps_Detected = CRANK_Get_Parameter( CRANK_PARAMETER_NUMBER_OF_GAPS_DETECTED, 0, 0);

	if ( ( CAM_Crank_Number_Gaps_Detected == 2 ) && ( CAM_Sensor_State == CAM_Previous_State ) ) {
		CAM_Stuck_At_Gap2 = true;
	} else {
		//  CAM_Crank_Number_Gaps_Detected >= 3 || CAM_Crank_Number_Gaps_Detected <= 1
		CAM_Stuck_At_Gap2 = false;  
	}

	/* cam2 stuck diagnose */
	if (CAM2_Sensor_State != CAM2_Previous_State) {
		CAM_Stuck = Insert_Bits( CAM_Stuck, false, CAM2, 1 );
		// Update previous cam state with current state
		CAM2_Previous_State = CAM2_Sensor_State;
	} else {
		CAM_Stuck = Insert_Bits( CAM_Stuck, true, CAM2, 1 );
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
		if(( CAM_Sensor_State != CAM_Previous_State ) || CAM_Not_Synched || (CRANK_Get_Flag(CRANK_FLAG_CAM_BACKUP) == true)) {
			/* Wait until the second 58x gap for a reliable cam sensor signal: */
			if( CAM_Crank_Number_Gaps_Detected >= CAM_Initialization_Parameters->number_of_gaps_before_sync ) {
				/* Indicate cam has now been read reliably at least once: */
				CAM_Not_Synched = false;
			}

			/* Indicate cam signal is not stuck in last state: */
			CAM_Stuck = Insert_Bits( CAM_Stuck, false, CAM_Sensor_In_Use, 1 );

			/* Determine if in backup mode and cam occurred: */
			if (CRANK_Get_Flag(CRANK_FLAG_CAM_BACKUP) == false) {
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
			} else {
				pattern_cylinder_id = CAM_Backup_Edge_Cylinder_ID;
				if (pattern_cylinder_id == CRANK_CYLINDER_D) {
					/* Indicate correct cylinder event: */
					cylinderID = CAM_Number_Of_Cylinders - 1;
					CAM_State_Change_Occurred          = Insert_Bits( CAM_State_Change_Occurred,          true, CAM_Sensor_In_Use, 1 );
					CAM_State_Change_Occurred_This_Rev = Insert_Bits( CAM_State_Change_Occurred_This_Rev, true, CAM_Sensor_In_Use, 1 );

					for (counter = 0; counter < CAM_NUMBER_OF_SENSORS; counter++ ) {
						CAM_Current_Edge[counter] = CAM_Initialization_Parameters->cam_edge_before_gap;
					}
				} else if (pattern_cylinder_id == CRANK_CYLINDER_B) {
					cylinderID = ( CAM_Number_Of_Cylinders / 2 ) - 1;
					CAM_State_Change_Occurred          = Insert_Bits( CAM_State_Change_Occurred,          false, CAM_Sensor_In_Use, 1 );
					CAM_State_Change_Occurred_This_Rev = Insert_Bits( CAM_State_Change_Occurred_This_Rev, false, CAM_Sensor_In_Use, 1 );
				} else {
					//do nothing
				}
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
			if (B_ErCylSynGap == true) {
				if (CRANK_Get_Cylinder_ID() == CRANK_CYLINDER_B) {
					CRANK_Set_Cylinder_ID(CRANK_CYLINDER_D);
				} else if (CRANK_Get_Cylinder_ID() == CRANK_CYLINDER_D) {
					CRANK_Set_Cylinder_ID(CRANK_CYLINDER_B);
				}
				B_ErCylSynGap = false;
			} else {
				 // invalid cylinder id, set to default value 
				if ((CRANK_Get_Cylinder_ID() == CRANK_CYLINDER_A) || (CRANK_Get_Cylinder_ID() == CRANK_CYLINDER_C)) {
					CRANK_Set_Cylinder_ID(CRANK_CYLINDER_D);
				} else {
					//to do nothing
				}
			}
		}
	}
	OS_CAM_READ_Hook();
}

//=============================================================================
// CAM_Get_Stuck_State
//=============================================================================
bool CAM_Get_Stuck_State(void)
{
	return CAM_Stuck;
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
uint32_t CAM_Get_Current_Edge_Period(CAM_Sensors_T     in_sensor)
{
	return CAM_Current_Edge_Period[in_sensor];
}

//=============================================================================
// uint8_t CAM_Get_Current_Edge
//=============================================================================
void CAM_Set_Current_Edge(CAM_Sensors_T     in_sensor )
{
	CAM_Current_Edge[in_sensor]  = 0;
}

//=============================================================================
// uint8_t CAM_Get_Current_Edge
//=============================================================================
void CAM_Set_Total_Edge(CAM_Sensors_T     in_sensor )
{
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
extern uCrank_Count_T    CRANK_GAP_COUNT;

static uint32_t haha_cam_event_angle_fraction;
static uint32_t haha_tooth_period;
static uint32_t haha_delta_time;
void CAM_Edge_Process( uint32_t in_cam_sensor )
{
	CAM_Sensors_T   cam_sensor = (CAM_Sensors_T)in_cam_sensor;

	uCrank_Angle_T  backup_delta_ucrank_angle;
	uCrank_Count_T  backup_delta_tooth;
	uint8_t         current_edge_index;
	uCrank_Count_T  pa_tooth_count;
	uCrank_Count_T  whole_angle_in_teeth;
	uCrank_Angle_T  cam_event_angle_fraction;
	uCrank_Angle_T  cam_event_angle_teeth;
	uint32_t        delta_time;
	uint32_t        cam_event_time;
	uint32_t        cam_previou_event_time;
	uint32_t        tooth_period;
	uint32_t        previous_time;
	uint32_t        current_time;
	uint32_t        counter;
	uint32_t        CAM1_Linear_BUF_Index;
	uint32_t        average_period;

	/* define backup variables */
	uint32_t backup_period;
	uint32_t backup_cam_edge_time;
	uint16_t backup_first_edge_count;
	uint16_t backup_last_edge_count;
	uint8_t  backups_between_cams;
	uint32_t backup_counts_per_time;
	uint32_t backup_current_time;

	current_edge_index = CAM_Current_Edge[cam_sensor];
	CAM_EdgeDetected = Insert_Bits( CAM_EdgeDetected, true, cam_sensor, 1 );
	CAM_Total_Edge[cam_sensor] ++;

	cam_event_time = MCD5411_Get_Parameter(CAME_TPU_INDEX ,CAM_CAME[cam_sensor], CAM_SENSOR_PARAMETER_CRITICAL_EDGE_TIME );
	cam_event_time &= UINT24_MAX;

	MCD5411_Get_Coherent_Angle_With_History(CAME_TPU_INDEX ,CAM_CAME[cam_sensor], &(CAM_Sensor_Coherent_data[cam_sensor]));

	/* record cam egde duty cycle and period in crank limp mode */
	if (cam_sensor == CAM1) {
		CAM1_Period_Circle_FIFO[CAM1_Circle_FIFO_Index]     = MCD5411_Get_Parameter(CAME_TPU_INDEX ,CAM_CAME[cam_sensor], CAM_SENSOR_PARAMETER_PERIOD );
		CAM1_Period_Off_Circle_FIFO[CAM1_Circle_FIFO_Index] = MCD5411_Get_Parameter(CAME_TPU_INDEX ,CAM_CAME[cam_sensor], CAM_SENSOR_PARAMETER_OFF_PERIOD);
		CAM1_DutyCycle_Circle_FIFO[CAM1_Circle_FIFO_Index]  = IO_Convert_Counts_To_Percent(CAM1_Period_Off_Circle_FIFO[CAM1_Circle_FIFO_Index], 100, CAM1_Period_Circle_FIFO[CAM1_Circle_FIFO_Index]);
		CAM1_Falling_Edge_Tooth_Number[CAM1_Circle_FIFO_Index] = (uint8_t)CRANK_Get_Engine_Tooth();
		CAM1_Circle_FIFO_Index ++;
		if (CAM1_Circle_FIFO_Index >= CAM_DUTY_CYCLE_LENGTH)
			CAM1_Circle_FIFO_Index = 0;

		CAM1_Linear_BUF_Index = CAM1_Circle_FIFO_Index;
		counter = 0;
		average_period = 0;
		while (counter < CAM_DUTY_CYCLE_LENGTH) {
			CAM1_DutyCycle_Linear_BUF[counter] = CAM1_DutyCycle_Circle_FIFO[CAM1_Linear_BUF_Index];
			average_period += CAM1_Period_Circle_FIFO[CAM1_Linear_BUF_Index];
			CAM1_Linear_BUF_Index ++;
			if (CAM1_Linear_BUF_Index >= CAM_DUTY_CYCLE_LENGTH)
				CAM1_Linear_BUF_Index = 0;
			counter++;
		}
		CAM_Backup_Edge_Cylinder_ID = CAM_Get_DutyCycle_Pattern_CylinderID(CAM1_DutyCycle_Linear_BUF);
		/* calculate the valid Period average value */
		if (CAM_Backup_Edge_Cylinder_ID != CRANK_CYLINDER_NULL)
			CAM1_Period_Average_Value = (average_period >> 2);
		/* get current falling edge ETPU time */
		backup_counts_per_time = TPU_TIMER_Get_Base_Frequency( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT);
		backup_current_time = TPU_TIMER_Get_Value_Channel( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT);
		backup_current_time = IO_PULSE_Convert_Counts_To_Time(backup_counts_per_time, backup_current_time,0,0);
		CAM1_Backup_Falling_Edge_Time = backup_current_time;

		if (CRANK_Get_Flag(CRANK_FLAG_CAM_BACKUP) == false) {
			if (CRANK_Get_Diag_Tooth_Cnt() == 0) {
				CAM1_CRANK_Diagnose_Fail_Count ++;
			} else {
				CAM1_CRANK_Diagnose_Fail_Count = 0;
			}
			if (CAM1_CRANK_Diagnose_Fail_Count >= CAM_CRANK_DIAGNOSE_MAX_Fail_COUNT) {
				/* if diagnose fail count get the maximum, enable pre-syn value */
				OS_Engine_Start_Crank();
				CRANK_Set_Flag(CRANK_FLAG_STALL_DETECTED, false);
				CRANK_Set_Flag(CRANK_FLAG_TRANSITION_TO_CAM_BACKUP, true);

				/* confirm current CAM Edge */
				if (((CAM_Backup_Edge_Cylinder_ID == CRANK_CYLINDER_B) || (CAM_Backup_Edge_Cylinder_ID == CRANK_CYLINDER_D)) \
					&& (CAM_Get_CAM1_EngineSpeed() > KfVIOS_n_BackupModeEventScheduleThrsh))
				{
					backup_delta_ucrank_angle = CRANK_Convert_Angle_To_uCrank_Angle(KyHWIO_Delta_Angle_From_Edge_To_Tooth_1, S_CRANK_ANGLE);
					backup_delta_tooth = CRANK_Convert_uCrank_Angle_To_Teeth(backup_delta_ucrank_angle);
					/* reset crank_current_event_tooth, just like when gap confirmed setting tooth */
					// CRANK_Current_Event_Tooth = backup_delta_tooth + (CAM_Backup_Edge_Cylinder_ID * 30);
					CRANK_Current_Event_Tooth = (CAM_Backup_Edge_Cylinder_ID * 30) + 30 - backup_delta_tooth;
					/* Set cylinder id in current cam edge, same as the CAM_Backup_Edge_Cylinder_ID*/
					CRANK_Set_Cylinder_ID( CAM_Backup_Edge_Cylinder_ID );

					/* set the first edge time, pulse number, tooth period */
					backup_last_edge_count = CAM_Sensor_Coherent_data[cam_sensor].current_crank_count_at_critical_edge;
					//Edge time in GTC counts
					backup_cam_edge_time = cam_event_time;
					// Using crank private to access private data.
					CRANK_Next_Event_PA_Content = backup_last_edge_count + 1;
					//Calculate number of crank pulses for next CAM Pulse
					backups_between_cams = KyHWIO_Crank_Angle_Per_CAM_Pulse[CAM_Backup_Edge_Cylinder_ID];
					//Calculate crank period based on the last CAM Pulse
					backup_period = CAM1_Period_Average_Value/backups_between_cams;
					//We have either no Crank signal or lost crank synchronization, so start edge count at 1
					backup_first_edge_count = backup_last_edge_count + 1;
					//Schedule Initial crank matches
					MCD5408_BACKUP_MODE_Initialize_Channel(EPPWMT_TPU_INDEX, &TPU, TPU_CONFIG_IC_EPPWMT, 0);

					CRANK_Previous_Real_Edge_Count = MCD5408_Get_Real_Edge_Count(EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT);
					CRANK_Current_Real_Edge_Count = CRANK_Previous_Real_Edge_Count;

					MCD5408_BACKUP_MODE_Enter_Backup_Service_Request(
						EPPWMT_TPU_INDEX,
						&TPU,
						TPU_CONFIG_IC_EPPWMT,
						backup_cam_edge_time + backup_period,
						backup_period,
						backup_first_edge_count,
						backups_between_cams);

					// Schedule the first crank event
					MCD5408_Set_New_IRQ_Count(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, CRANK_EPPE_IRQ_Select, CRANK_Next_Event_PA_Content );
					// Clear the interrupt flag: false == clear
					MCD5408_Set_Host_Interrupt_Status(EPPWMT_TPU_INDEX,&TPU,TPU_CONFIG_IC_EPPWMT,false);

					// Enable interrupts
					MCD5408_Enable_Host_Interrupt(EPPWMT_TPU_INDEX, &TPU, TPU_CONFIG_IC_EPPWMT);
					
					/* set cam backup mode flag */
					CRANK_Set_Flag(CRANK_FLAG_CAM_BACKUP, true);
					/* disable the 58x signal input port */
					SIU_GPIO_InputBuffer_Config(HAL_GPIO_CRANK_CHANNEL, false);
					SIU_Pad_Config(HAL_GPIO_CRANK_CHANNEL, SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1);
					
					CAM1_BACKUP_FLAG = true;
					
					/* update crank status, including hls and crank */
					CRANK_Backup_Set_Syn_Status();
				}
				else
				{
					// todo: nothing
				}
			} else {
				// todo: nothing
			}
		} else {
			CRANK_Set_Flag( CRANK_FLAG_STALL_DETECTED, false );

			/* confirm current CAM Edge */
			CAM_Backup_Edge_Cylinder_ID = CAM_Get_DutyCycle_Pattern_CylinderID(CAM1_DutyCycle_Linear_BUF);

			if ((CAM_Backup_Edge_Cylinder_ID == CRANK_CYLINDER_B) || (CAM_Backup_Edge_Cylinder_ID == CRANK_CYLINDER_D)) {
				//todo nothing
			} else {
				CAM_Backup_Edge_Cylinder_ID = CRANK_Get_Cylinder_ID();
			}

			/* confirm the duty cycle pattern */
			if (CAM_Backup_Edge_Cylinder_ID != CRANK_CYLINDER_NULL) {
				backup_delta_ucrank_angle = CRANK_Convert_Angle_To_uCrank_Angle(KyHWIO_Delta_Angle_From_Edge_To_Tooth_1, S_CRANK_ANGLE);
				backup_delta_tooth = CRANK_Convert_uCrank_Angle_To_Teeth(backup_delta_ucrank_angle);
				/* reset crank_current_event_tooth, just like when gap confirmed setting tooth */
				CRANK_Current_Event_Tooth = (CAM_Backup_Edge_Cylinder_ID * 30) + 30 - backup_delta_tooth;

				/* set the first edge time, pulse number, tooth period */
				backup_last_edge_count = CAM_Sensor_Coherent_data[cam_sensor].current_crank_count_at_critical_edge;
				//Edge time in GTC counts
				backup_cam_edge_time = cam_event_time;
				// Using crank private to access private data.
				CRANK_Next_Event_PA_Content = backup_last_edge_count + 1;
				//Calculate number of crank pulses for next CAM Pulse
				backups_between_cams = KyHWIO_Crank_Angle_Per_CAM_Pulse[CAM_Backup_Edge_Cylinder_ID];
				//Calculate crank period based on the last CAM Pulse
				backup_period = CAM1_Period_Average_Value/backups_between_cams;
				//We have either no Crank signal or lost crank synchronization, so start edge count at 1
				backup_first_edge_count = backup_last_edge_count + 1;

				MCD5408_BACKUP_MODE_Request_Backup_Edges(
					EPPWMT_TPU_INDEX,
					&TPU,
					TPU_CONFIG_IC_EPPWMT,
					backup_cam_edge_time + backup_period,
					backup_period,
					backup_first_edge_count,
					backups_between_cams);
			} else {
				//todo: nothing
			}
		}
	}

	// Crank_Count can be in error by + or – one count, so we need to avoid + one case
	current_time = CRANK_Get_Edge_Time_From_Count(pa_tooth_count);
	delta_time = (cam_event_time - current_time) & UINT24_MAX;
	if (delta_time > (uint32_t)INT24_MAX) {
		pa_tooth_count --;
		current_time = CRANK_Get_Edge_Time_From_Count(pa_tooth_count);
		delta_time = (cam_event_time - current_time) & UINT24_MAX;
	}
	previous_time = CRANK_Get_Edge_Time_From_Count(pa_tooth_count-1);
	tooth_period = (current_time - previous_time) & UINT24_MAX;

	// get the tooth before for the correct tooth period.
	pa_tooth_count = CAM_Sensor_Coherent_data[cam_sensor].current_crank_count_at_critical_edge;
	whole_angle_in_teeth = pa_tooth_count - CRANK_GAP_COUNT + 2;
	switch(CRANK_Get_Cylinder_ID()) {
	case CRANK_CYLINDER_A:
		CAM_Set_Current_Edge(in_cam_sensor);
	case CRANK_CYLINDER_B:
		whole_angle_in_teeth = (whole_angle_in_teeth > 60) ? (whole_angle_in_teeth - 60) : (whole_angle_in_teeth);
		break;
	case CRANK_CYLINDER_C:
	case CRANK_CYLINDER_D:
		whole_angle_in_teeth = (whole_angle_in_teeth < 60) ? (whole_angle_in_teeth + 60) : (whole_angle_in_teeth);
		break;
	default:
		break;
	}

	// convert to delta angle from time
	haha_cam_event_angle_fraction = IO_Convert_uTime_To_uAngle(haha_delta_time, uCRANK_ANGLE_PRECISION, haha_tooth_period, 1);
	cam_event_angle_fraction = IO_Convert_uTime_To_uAngle(delta_time, uCRANK_ANGLE_PRECISION, tooth_period, 1);
	cam_event_angle_teeth    = CRANK_Convert_Teeth_To_uCrank_Angle(whole_angle_in_teeth);
	CAM_Edge_Data[( cam_sensor * CAM_Number_Of_Pulses ) + current_edge_index].Count = cam_event_angle_teeth + cam_event_angle_fraction;
	CAM_Edge_Data[( cam_sensor * CAM_Number_Of_Pulses ) + current_edge_index].Time = cam_event_time;
	CAM_Edge_Data[( cam_sensor * CAM_Number_Of_Pulses ) + current_edge_index].Edge_Period = tooth_period;
	// start monitor the whole tooth counter and fraction
	if (cam_sensor == CAM1) {
		CAM1_VCPC_Fraction_Angle[current_edge_index]    = current_time;
		CAM1_VCPC_Whole_Tooth_Count[current_edge_index] = cam_event_time;
	} else {
		CAM2_VCPC_Fraction_Angle[current_edge_index]    = current_time;
		CAM2_VCPC_Whole_Tooth_Count[current_edge_index] = cam_event_time;
	}
	// end monitor the whole tooth counter and fraction
	if (current_edge_index == 0) {
		current_edge_index = 3;
	} else {
		current_edge_index --;
	}
	cam_previou_event_time = CAM_Edge_Data[( cam_sensor * CAM_Number_Of_Pulses ) + current_edge_index].Time;
	CAM_Current_Edge_Period[cam_sensor] = (cam_event_time - cam_previou_event_time) & UINT24_MAX;

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

//=============================================================================
// CAM_Get_CAM1_Period
//=============================================================================
uint32_t CAM_Get_CAM1_Period(void)
{
	return CAM1_Period_Average_Value;
}

//=============================================================================
// CAM_Get_CAM1_EngineSpeed
//=============================================================================
#define CRANK_SECONDS_PER_MINUTE      (60)
#define CRANK_DEFAULT_RPM_PRECSION    (8)
uint32_t CAM_Get_CAM1_EngineSpeed(void)
{
	uint32_t engine_speed=0;
	uint8_t tooth_per_lores;
	uint8_t rpm_conv_factor;

	tooth_per_lores = CRANK_SCHEDULE_CONFIG_VIRTUAL_TEETH_PER_REVOLUTION / 4;

	//The conversion factor is applied to support other crank profiles like 24x,30x etc
	rpm_conv_factor = (CRANK_VIRTUAL_TEETH_PER_CRANK)/tooth_per_lores;

	engine_speed = (CRANK_SECONDS_PER_MINUTE*(TPU_TIMER_Get_Base_Frequency( EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT ))
	*CRANK_DEFAULT_RPM_PRECSION)/(CAM1_Period_Average_Value *rpm_conv_factor);

	return ( engine_speed );
}


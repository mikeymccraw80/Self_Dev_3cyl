#include "io_config_cam.h"
#include "io_config_tpu.h"


//=============================================================================
// cam const config
//=============================================================================
const MCD5411_Channel_Init_T  CAM_INIT = {
	1, // critical edge IRQ disabled
	0, // non critical edge IRQ disabled
	MCD5411_CAME_REPLICATE_DISABLE,
	0, // Rep. cam output mirrors input
	0, //MCD5411_HSR_CRIT_EDGE_RISING
	CAME_TCR1_TIMEBASE,
	TPU_CHANNEL_0, // Rep. cam output has been disabled
	(uint32_t)( TPU_A_TCR1_CLOCK_FREQ * 0.000020 ) //replicated cam output signal will lag the cam input signal by which time
};

const bool CAM_CONFIG_ACTIVE_STATE[NUMBER_OF_CAM_SENSORS] = {
	false,
	false
};

const IO_Cam_Initialization_Parameters_T CAM_INITIALIZATION_PARAMETERS = {
	CRANK_Convert_Teeth_To_uCrank_Angle(3), // cam_read_angle
	(bool*const)CAM_CONFIG_ACTIVE_STATE,    //CAM_Active_State
	2,     //number_of_gaps_before_sync
	false, //use_cam_toggle
	255, /*number_of_toggles_before_sync, 255 = override, always use CAM for sync*/
	NULL, //cam_profile_data
	4, //cam_profile_data_pulse_count
	0,       // cam_min_pulses_for_sync;
	NUMBER_OF_CAM_SENSORS,       // cam_sensor_for_sync, not supported;
	0,       // cam_edge_before_gap;
	15,       // delta_teeth_from_edge_to_tooth_1;
	0       // cam_cyl_id_before_gap;
};

//=============================================================================
// 
//=============================================================================




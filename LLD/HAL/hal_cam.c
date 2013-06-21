//=============================================================================
// include files
//=============================================================================
 #include "dd_cam_interface.h"
 #include "dd_crank_interface.h"

//=============================================================================
// HAL_Get_CAM_Period
//=============================================================================
uint32_t HAL_Get_CAM_Period(uint32_t cam_sensor)
{
	return CAM_Get_Current_Edge_Period(cam_sensor);
}

//=============================================================================
// HAL_Get_CAM_Edge_Count
// resolution is 0.25us.
//=============================================================================
uint8_t HAL_Get_CAM_Edge_Count(uint32_t cam_sensor)
{
	return CAM_Get_Total_Edge(cam_sensor);
}

//=============================================================================
// HAL_Get_CAM_Level, called by hal_os
//=============================================================================
uint8_t HAL_Get_CAM_Level(uint32_t cam_sensor)
{
	uint32_t          cam_history;
	if (cam_sensor == CAM1) {
		cam_history  = CRANK_Get_Parameter( CRANK_PARAMETER_CAM_HISTORY, 0, 0);
		return (uint8_t)(cam_history & 0x01);
	} else {
		cam_history  = CRANK_Get_Parameter( CRANK_PARAMETER_CAM_HISTORY, 0, 0);
		return (uint8_t)(cam_history & 0x01);
	}
}



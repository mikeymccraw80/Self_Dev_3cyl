//=============================================================================
// include files
//=============================================================================
#include "dd_cam_interface.h"
#include "dd_crank_interface.h"
#include "io_config_siu.h"
#include "dd_siu_interface.h"


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
		return (uint8_t)(SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_CAM1_CHANNEL));
	} else {
		return (uint8_t)(SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_CAM2_CHANNEL));
	}
}

//=============================================================================
// HAL_GET_CAM_Stuck_State
//=============================================================================
bool HAL_GET_CAM_Stuck_State(uint32_t cam_sensor)
{
	return (bool)(CAM_Get_Stuck(cam_sensor));
}

//=============================================================================
// HAL_Diag_Crank_Signal, called on the falling edge of cam inlet
//=============================================================================
bool HAL_Diag_Crank_Signal(void)
{
	bool result;

	result = (CRANK_Get_Diag_Tooth_Cnt() == 0) ? 1 : 0;
	CRANK_Set_Diag_Tooth_Cnt(0);
	return result;
}




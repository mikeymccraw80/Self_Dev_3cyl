//=============================================================================
// include files
//=============================================================================
#include "HLS.h"
#include "hal_cam.h"

#define CAM1 0
#define CAM2 1

//=============================================================================
//  IO_CAMW_Update, should be called on camw falling edge.
//=============================================================================
void IO_CAMW_Update(void)
{
	cam1_sig.period = HAL_Get_CAM_Period(CAM1);
	cam1_sig.edge_count = HAL_Get_CAM_Edge_Count(CAM1);
}

//=============================================================================
//  IO_CAMX_Update, should be called on camx falling edge
//=============================================================================
void IO_CAMX_Update(void)
{
	cam2_sig.period = HAL_Get_CAM_Period(CAM2);
	cam2_sig.edge_count = HAL_Get_CAM_Edge_Count(CAM2);
}

//=============================================================================
//  IO_CAM_Level_Update, should be called on 58x falling edge
//=============================================================================
void IO_CAM_Level_Update(void)
{
	cam1_sig.level = HAL_Get_CAM_Level(CAM1);
	cam2_sig.level = HAL_Get_CAM_Level(CAM2);
}

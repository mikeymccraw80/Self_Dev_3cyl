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
	cam1_sig.period = ((HAL_Get_CAM_Period(CAM1) * 25) / 80 );
	cam1_sig.edge_count = HAL_Get_CAM_Edge_Count(CAM1);
}

//=============================================================================
//  IO_CAMX_Update, should be called on camx falling edge
//=============================================================================
void IO_CAMX_Update(void)
{
	/* convert 0.25us -> 0.8us */
	cam2_sig.period = ((HAL_Get_CAM_Period(CAM2) * 25) / 80 );
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

//=============================================================================
//  IO_CAM_Status_Update, should be called on CAM read reference
//  remark, there's no meaning to update cam2 status
//=============================================================================
void IO_CAM_Status_Update (void)
{
	if (HAL_GET_CAM_Stuck_State()) {
		cam1_sig.status.B_cam_failed = 1;
		cam1_sig.status.B_cam_loss_of_sync = 1;
		cam1_sig.status.B_cam_limp_home = 1;
	} else {
		cam1_sig.status.B_cam_failed = 0;
		cam1_sig.status.B_cam_loss_of_sync = 0;
		cam1_sig.status.B_cam_limp_home = 0;
	}
}

//=============================================================================
//  IO_Crank_Status_Update, should be called on cam falling edge
//=============================================================================
void IO_Crank_Status_Update(void)
{
	/* Check if crank failed */
	if ( HAL_Diag_Crank_Signal()) {
		crank_sig.crank_status.B_crank_failed = ( bitfield8_t )true;
		crank_sig.crank_status.B_crank_limp_home = ( bitfield8_t )true;
		crank_sig.crank_status.B_crank_sync = ( bitfield16_t )false ;
	} else {
		crank_sig.crank_status.B_crank_failed = ( bitfield8_t )false;
		crank_sig.crank_status.B_crank_limp_home = ( bitfield8_t )false;
	}
}


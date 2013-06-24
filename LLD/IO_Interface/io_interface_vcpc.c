//=============================================================================
// include files
//=============================================================================
#include "HLS.h"
#include "hal_vcpc.h"
#include "hwiocald.h"


//=============================================================================
// global variable
//=============================================================================

//=============================================================================
// static variable
//=============================================================================

//=============================================================================
//  IO_VCPC_Convert_CAMW
//=============================================================================
void IO_VCPC_Convert_CAMW(void)
{
	uint8_t edge_index;
	edge_index = HAL_VCPC_Get_CAM_Current_Index(0);
	edge_index = (edge_index == 0) ? 3 : edge_index --;
	/* 6/256 => 1/1024 */
	angle_crank_cam_inlet = ((HAL_VCPC_Get_CAM_Angle(0,edge_index) - (KyHWIO_ToothOfFirstLoResEvent << 8)) * 6) >> 8;
}

//=============================================================================
//  IO_VCPC_Convert_CAMW
//=============================================================================
void IO_VCPC_Convert_CAMX(void)
{
	uint8_t edge_index;
	edge_index = HAL_VCPC_Get_CAM_Current_Index(1);
	edge_index = (edge_index == 0) ? 3 : edge_index --;
	angle_crank_cam_outlet =  ((HAL_VCPC_Get_CAM_Angle(1,edge_index) - (KyHWIO_ToothOfFirstLoResEvent << 8)) * 6) >> 8;
}


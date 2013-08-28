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
uint16_t cam_inlet[4];
uint16_t cam_outlet[4];
//=============================================================================
//  IO_VCPC_Convert_CAMW
//=============================================================================
void IO_VCPC_Convert_CAMW(void)
{
	uint8_t edge_index;
	uint32_t angle_temp;

	edge_index = HAL_VCPC_Get_CAM_Current_Index(0);
	edge_index = (edge_index == 0) ? 3 : edge_index --;
	/* unit: 6/256 => 1024/65536(1/64) */
	angle_temp =  ((HAL_VCPC_Get_CAM_Angle(0,edge_index) - (KyHWIO_ToothOfCAMRefEvent << 8)) * 3) / 2;
	angle_crank_cam_inlet = (uint16_t)angle_temp;
	cam_inlet[edge_index] = angle_crank_cam_inlet;
}

//=============================================================================
//  IO_VCPC_Convert_CAMW
//=============================================================================
void IO_VCPC_Convert_CAMX(void)
{
	uint8_t edge_index;
	uint32_t angle_temp;

	edge_index = HAL_VCPC_Get_CAM_Current_Index(1);
	edge_index = (edge_index == 0) ? 3 : edge_index --;
	/* unit: 6/256 => 1024/65536(1/64) */
	angle_temp =  ((HAL_VCPC_Get_CAM_Angle(1,edge_index) - (KyHWIO_ToothOfCAMRefEvent << 8)) * 3) / 2;
	angle_crank_cam_outlet = (uint16_t)angle_temp;
	cam_outlet[edge_index] = angle_crank_cam_outlet;
}


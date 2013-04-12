//=============================================================================
// include files
//=============================================================================
#include "HLS.h"
#include "hal_vcpc.h"


//=============================================================================
// global variable
//=============================================================================
const unsigned char VCPC_Ref_Tooth[4] ={3,33,63,93};

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
  angle_crank_cam_inlet =  HAL_VCPC_Get_CAM_Angle(0,edge_index)*3/2-VCPC_Ref_Tooth[edge_index]*384;
	 
}

//=============================================================================
//  IO_VCPC_Convert_CAMW
//=============================================================================
  void IO_VCPC_Convert_CAMX(void)
{
  uint8_t edge_index;
   edge_index = HAL_VCPC_Get_CAM_Current_Index(1);
  angle_crank_cam_outlet =  HAL_VCPC_Get_CAM_Angle(1,edge_index)*3/2-VCPC_Ref_Tooth[edge_index]*384;
	 
}


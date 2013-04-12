//=============================================================================
// include files
//=============================================================================
 #include "dd_cam_interface.h"



//=============================================================================
// HAL_VCPC_Get_CAM_Current_Index
//=============================================================================
  uint8_t HAL_VCPC_Get_CAM_Current_Index(uint32_t cam_sensor) 
 {

    return CAM_Get_CAM_Current_Index(cam_sensor);

 }
//=============================================================================
// HAL_VCPC_Get_CAM_Angle
//=============================================================================
  uint32_t HAL_VCPC_Get_CAM_Angle(uint32_t cam_sensor, uint8_t edge_index) 
 {
     return  CAM_Get_CAM_Angle(cam_sensor, edge_index);
 }


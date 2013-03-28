
#ifndef IO_CONFIG_CAM_H
#define IO_CONFIG_CAM_H

//=============================================================================
//   include files
//=============================================================================

#include "dd_cam.h"

//=============================================================================
// confige define
//=============================================================================
#define CAM_NUMBER_OF_SENSORS          (2)
#define CAM_NUMBER_OF_PULSES            (4)
#define CAMe_MIN_PERIOD_IN_SEC ( 0.0005 ) /* 0.5ms */

//=============================================================================
//  extern const
//=============================================================================
extern const MCD5411_Channel_Init_T  CAM_INIT;

extern  const bool CAM_CONFIG_ACTIVE_STATE[];

extern const IO_Cam_Initialization_Parameters_T CAM_INITIALIZATION_PARAMETERS;



#endif


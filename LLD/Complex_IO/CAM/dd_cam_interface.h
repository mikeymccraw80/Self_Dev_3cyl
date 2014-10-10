#ifndef DD_CAM_INTERFACE_H
#define DD_CAM_INTERFACE_H

//=============================================================================
//  include files
//=============================================================================
#include "dd_cam.h"


//=============================================================================
//   Function Prototypes
//=============================================================================

//=============================================================================
// CAM_Initialize
//=============================================================================
void CAM_Initialize(
   IO_Cam_Initialization_Parameters_T  * const in_initialization_parameters );


//=============================================================================
// CAM_Reset_Parameters
//=============================================================================
void CAM_Reset_Parameters( void );


//=============================================================================
// CAM_Lo_Res_Event_Tasks
//=============================================================================
void CAM_Lo_Res_Event_Tasks( void );

//=============================================================================
// CAM_Application_Event_Tasks
//=============================================================================
void CAM_Application_Event_Tasks(void);

//=============================================================================
// CAM_Reset_Stuck
//=============================================================================
void CAM_Reset_Stuck(
   CAM_Sensors_T  in_sensor );


//=============================================================================
// CAM_Update_State
//=============================================================================
void CAM_Update_State( void );


//=============================================================================
// CAM_Get_Sensor_State
//=============================================================================
bool CAM_Get_Sensor_State(
   CAM_Sensors_T  in_sensor );


//=============================================================================
// CAM_Use_Sensor
//
// @func indicates which cam sensor to use.
//
// @end
//=============================================================================
void CAM_Select_Sensor(
   CAM_Sensors_T  in_sensor );


//=============================================================================
// CAM_Get_Sensor_In_Use
//
// @func returns which cam sensor is in use.
//
// @end
//=============================================================================
CAM_Sensors_T CAM_Get_Selected_Sensor( void );


//=============================================================================
// CAM_SetStuck
//
// @func Sets a the cam stuck state.
//
// Parameters:    inStuck - the state of the cam
// Returns:       none
// @rdesc none
//
// @end
//=============================================================================
void CAM_Set_Stuck(
   CAM_Sensors_T  in_sensor,
   bool           in_stuck );


//=============================================================================
// CAM_Get_Stuck
//
// @func Returns a boolean indicating true if the cam is in the stuck state.
//
// @rdesc wether or not cam is s
// @flag true | cam high
// @flag false | cam low
//
// @end
//=============================================================================
bool CAM_Get_Stuck(
   CAM_Sensors_T  in_sensor );


//=============================================================================
// CAM_ResetStuck
//
// @func Resets the CAM to not being stuck.
//
// @rdesc none
//
// @end
//=============================================================================
void CAM_Reset_Stuck(
   CAM_Sensors_T  in_sensor );


//=============================================================================
// CAM_Set_State_Change_Occurred
//
// @func Write a value to the CAM_State_Change_Occurred variable.
//
// Parameters:    CAM_Sensors_T, which cam sensor
//                in_state_change_occurred - true if occurred, false if it hasn't
// Returns:       none
// @rdesc none
//
// @end
//=============================================================================
void CAM_Set_State_Change_Occurred(
   CAM_Sensors_T  in_sensor,
   bool           in_state_change_occurred );


//=============================================================================
// CAM_Get_State_Change_Occurred
//
// @func Returns a boolean indicating the cam changed state.
//
// Parameters:    CAM_Sensors_T, which cam sensor
// Returns:       boolean, true = cam occurred
// @rdesc none
//
// @end
//=============================================================================
bool CAM_Get_State_Change_Occurred(
   CAM_Sensors_T  in_sensor );



//=============================================================================
// CAM_Get_State_Change_Occurred_Current_Revolution
//
// @func Returns a boolean indicating the cam changed state.
//
// Parameters:    none
// Returns:       boolean, true = cam occured.
// @rdesc none
//
// @end
//=============================================================================
bool CAM_Get_State_Change_Occurred_Current_Revolution(
   CAM_Sensors_T  in_sensor );

//=============================================================================
// CAM_Edge_Interrupt_Handler
//=============================================================================
uint8_t CAM_Get_CAM_Current_Index( uint32_t in_cam_sensor );

//=============================================================================
// CAM_Edge_Interrupt_Handler
//=============================================================================
uint32_t CAM_Get_CAM_Angle( uint32_t in_cam_sensor ,uint8_t index );

//=============================================================================
// CAM_Get_CAM1_Period
//=============================================================================
uint32_t CAM_Get_CAM1_Period(void);

//=============================================================================
// CAM_Get_CAM1_EngineSpeed
//=============================================================================
uint32_t CAM_Get_CAM1_EngineSpeed(void);

//=============================================================================
// uint8_t CAM_Get_Current_Edge
//=============================================================================
uint8_t CAM_Get_Total_Edge(CAM_Sensors_T     in_sensor);

//=============================================================================
// CAM_Get_Edge_Data
//=============================================================================
void CAM_Get_Edge_Data(CAM_Sensors_T in_sensor, uint8_t in_cam_edge, Edge_Data_T* in_cam_edge_data);

//=============================================================================
// uint8_t CAM_Get_Current_Edge
//=============================================================================
void CAM_Set_Current_Edge(CAM_Sensors_T     in_sensor );

//=============================================================================
// uint8_t CAM_Set_Total_Edge
//=============================================================================
void CAM_Set_Total_Edge(CAM_Sensors_T     in_sensor );

//=============================================================================
// CAM_Get_Stuck_State
//=============================================================================
bool CAM_Get_Stuck_State(void);

#endif // DD_CAM_INTERFACE_H

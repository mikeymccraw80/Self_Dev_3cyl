#ifndef DD_MCD5411_INTERFACE_H
#define DD_MCD5411_INTERFACE_H

#include "dd_mcd5411.h"

//===========================================================================
// Function Prototypes
//===========================================================================

//===========================================================================
// MCD5411_Initialize_Channel
//===========================================================================
void MCD5411_Initialize_Channel(
    TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   const void          *in_init );


//===========================================================================
// MCD5411_Clear_Channel
//===========================================================================
void MCD5411_Clear_Channel(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );


//=============================================================================
// MCD5411_Set_Parameter
//=============================================================================
void MCD5411_Set_Parameter(
          TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Parameter_T  in_parameter,
   uint32_t                in_value );


//=============================================================================
// MCD5411_Get_Parameter
//=============================================================================
uint32_t MCD5411_Get_Parameter(
          TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Parameter_T  in_parameter );


//=============================================================================
// MCD5411_Set_Flag
//=============================================================================
void MCD5411_Set_Flag(
             TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Flag_T    in_flag,
   bool                 in_value );


//=============================================================================
// MCD5411_Get_Flag
//=============================================================================
bool MCD5411_Get_Flag(
                TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Flag_T    in_flag );


//=============================================================================
// MCD5411_Get_Angle_Clock_Data
//=============================================================================
void MCD5411_Get_Angle_Clock_Data(
                TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   uint32_t            *out_current_angle,
   uint32_t            *out_previous_angle );


//=============================================================================
// MCD5411_Get_Coherent_Angle_With_History
//=============================================================================
void MCD5411_Get_Coherent_Angle_With_History(
                  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Coherent_T   *out_angle_data );


//=============================================================================
// MCD5411_Set_Host_Interrupt_Enable
//=============================================================================
void  MCD5411_Set_Host_Interrupt_Enable(
                   TPU_Index_T index,
                     TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure ,
   bool                 in_state );


//=============================================================================
// MCD5411_Get_Host_Interrupt_Enable
//=============================================================================
bool MCD5411_Get_Host_Interrupt_Enable(
                      TPU_Index_T index,
                     TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure  );


//=============================================================================
// MCD5411_Set_Host_Interrupt_Status
//=============================================================================
void MCD5411_Set_Host_Interrupt_Status(
                      TPU_Index_T index,
                     TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure ,
   bool                 in_status );


//=============================================================================
// MCD5411_Get_Host_Interrupt_Status
//=============================================================================
bool MCD5411_Get_Host_Interrupt_Status(
                        TPU_Index_T index,
                     TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure  );



#endif // DD_MCD5411_INTERFACE_H 

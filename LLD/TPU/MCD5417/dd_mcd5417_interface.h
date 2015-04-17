#ifndef DD_MCD5417_INTERFACE_H
#define DD_MCD5417_INTERFACE_H

#include "dd_mcd5417.h"

//===========================================================================
// Function Prototypes                                                       
//===========================================================================

//=============================================================================
// MCD5417_Initialize_Channel
//=============================================================================
void MCD5417_Initialize_Channel(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5417_Update_Boundary
//=============================================================================
void MCD5417_Update_Boundary(
      TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure,
   uint32_t           in_dfpw,
   uint32_t           in_boundary_angle,
   uint32_t           in_normal_offset,
   uint32_t           in_trim_offset );


//=============================================================================
// MCD5417_Update_Channel
//=============================================================================
void MCD5417_Update_Channel(
      TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure,
   uint32_t      in_dfpw,
   uint32_t      in_boundary,
   uint32_t      in_normal_offset,
   uint32_t      in_trim_offset );



//=============================================================================
// MCD5417_Update_Engine_Data
//=============================================================================
void MCD5417_Update_Engine_Data(
       TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure,
   uint32_t            edge_time,
   uint16_t            edge_count,
   uint32_t            period );

//=============================================================================
// MCD5417_Set_Engine_Data
//=============================================================================
void MCD5417_Set_Engine_Data(
         TPU_Index_T index,
   uint32_t            edge_time,
   uint16_t            edge_count,
   uint32_t            period );

//=============================================================================
// MCD5417_Shutdown
//=============================================================================
void MCD5417_Shutdown(
         TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure );


//=============================================================================
// MCD5417_Set_Normal_Offset
//=============================================================================
void MCD5417_Set_Normal_Offset(
    TPU_Index_T index,
   uint32_t            normal_offset );

//=============================================================================
// MCD5417_Get_Normal_Offset
//=============================================================================
uint32_t MCD5417_Get_Normal_Offset(void );

//=============================================================================
// MCD5417_Set_Trim_Offset
//=============================================================================
void MCD5417_Set_Trim_Offset(
      TPU_Index_T index,
   uint32_t            trim_offset );

//=============================================================================
// MCD5417_Get_Trim_Offset
//=============================================================================
uint32_t MCD5417_Get_Trim_Offset(void);

//=============================================================================
// MCD5417_Set_Kinj
//=============================================================================
void MCD5417_Set_Kinj(
         TPU_Index_T index,
   uint32_t            kinj );

//=============================================================================
// MCD5417_Get_Kinj
//=============================================================================
uint32_t MCD5417_Get_Kinj(void );

//=============================================================================
// MCD5417_Set_Min_Inj_Off
//=============================================================================
void MCD5417_Set_Min_Inj_Off(
    TPU_Index_T index,
   uint32_t            min_inj_off );

//=============================================================================
// MCD5417_Get_Min_Inj_Off
//=============================================================================
uint32_t MCD5417_Get_Min_Inj_Off(void);


//=============================================================================
// MCD5417_Set_Min_Trim
//=============================================================================
void MCD5417_Set_Min_Trim(
       TPU_Index_T index,
   uint32_t            min_trim );

//=============================================================================
// MCD5417_Get_Min_Trim
//=============================================================================
uint32_t MCD5417_Get_Min_Trim(void);

//=============================================================================
// MCD5417_Set_Multiple_Trim
//=============================================================================
void MCD5417_Set_Multiple_Trim(
      TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure,
   uint32_t        multiple_trim );

//=============================================================================
// MCD5417_Get_Multiple_Trim
//=============================================================================
uint32_t MCD5417_Get_Multiple_Trim(void);

//=============================================================================
// MCD5417_Set_DFPW
//=============================================================================
void MCD5417_Set_DFPW(
         TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure,
   uint32_t            dfpw );

//=============================================================================
// MCD5417_Get_DFPW
//=============================================================================
uint32_t MCD5417_Get_DFPW(void);

//=============================================================================
// MCD5417_Set_AFPW
//=============================================================================
 void MCD5417_Set_AFPW(
         TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure,
   uint32_t            in_afpw );

//=============================================================================
// MCD5417_Get_AFPW
//=============================================================================
uint32_t MCD5417_Get_AFPW(
          TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5417_Set_Boundary
//=============================================================================
void MCD5417_Set_Boundary(
           TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure,
   uint32_t            in_boundary_angle );

//=============================================================================
// MCD5417_Get_Boundary
//=============================================================================
uint32_t MCD5417_Get_Boundary(void);

//=============================================================================
// MCD5417_Get_Normal_Pulse_Occurred
//=============================================================================
uint32_t MCD5417_Get_Normal_Pulse_Occurred(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5417_Get_Trim_Pulse_Occurred
//=============================================================================
uint32_t MCD5417_Get_Trim_Pulse_Occurred(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5417_Get_Kinj_Active
//=============================================================================
uint32_t MCD5417_Get_Kinj_Active(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5417_Get_Fuel_Active
//=============================================================================
bool MCD5417_Get_Fuel_Active(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5417_Get_Min_Inj_Off_Active
//=============================================================================
uint32_t MCD5417_Get_Min_Inj_Off_Active(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5417_Get_Start_End_Time
//=============================================================================
uint32_t MCD5417_Get_Start_End_Time(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5417_Set_Enable_Interrupt
//=============================================================================
void  MCD5417_Set_Host_Interrupt_Enable(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   bool                in_interrupt_enable);

//=============================================================================
// MCD5417_Get_Interrupt_Enable
//=============================================================================
bool MCD5417_Get_Host_Interrupt_Enable(
    TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5417_Set_Host_Interrupt_Status
//=============================================================================
void MCD5417_Set_Host_Interrupt_Status(
      TPU_Index_T index,
      TPU_T         *p_tpu,
      TPU_CHANNEL_Configuration_T   configure,
       bool                in_state);

//=============================================================================
// MCD5417_Get_Host_Interrupt_Status
//=============================================================================
bool MCD5417_Get_Host_Interrupt_Status(
         TPU_Index_T index,
         TPU_T         *p_tpu,
         TPU_CHANNEL_Configuration_T   configure);

#endif // DD_MCD5417_INTERFACE_H 

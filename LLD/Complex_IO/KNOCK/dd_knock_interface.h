
#ifndef DD_KNOCK_INTERFACE_H
#define DD_KNOCK_INTERFACE_H

#include "reuse.h"

//=============================================================================
// KNOCK_Initialize
//=============================================================================
void KNOCK_Initialize(void);
//=============================================================================
// KNOCK_Cylinder_Event_MultiKnock
//=============================================================================
void KNOCK_Cylinder_Event_MultiKnock(void);
//=============================================================================
// KNOCK_Get_Window_Status
//=============================================================================
bool KNOCK_Get_Window_Status( void );

//=============================================================================
// KNOCK_Get_Last_Analog_Conversion
//=============================================================================

uint16_t KNOCK_Get_MultiLast_Analog_Conversion1( void );

uint16_t KNOCK_Get_MultiLast_Analog_Conversion2( void );

//=============================================================================
// KNOCK_Set_High_Gain
//=============================================================================
void KNOCK_Set_High_Gain( bool in_gain_high );

bool KNOCK_Get_High_Gain( void );

//=============================================================================
// KNOCK_Set_Center_Frequency
//=============================================================================

void KNOCK_Set_MultiCenter_Frequency1( uint8_t in_center_frequency);
void KNOCK_Set_MultiCenter_Frequency2( uint8_t in_center_frequency);
void KNOCK_Set_MultiCenter_Frequency3( uint8_t in_center_frequency);

//=============================================================================
// KNOCK_Set_Window_Start
//=============================================================================
void KNOCK_Set_MultiWindow_Start1( int32_t angle, uint8_t precision );

void KNOCK_Set_MultiWindow_Start2( int32_t angle, uint8_t precision );

void KNOCK_Set_MultiWindow_End1( int32_t angle, uint8_t precision );

void KNOCK_Set_MultiWindow_End2( int32_t angle, uint8_t precision );



void KNOCK_Get_MultiIntensity_Value1( uint32_t* values );

void KNOCK_Get_MultiIntensity_Value2( uint32_t* values );


//=============================================================================
// KNOCK_Get_Window_Closed_Status
//=============================================================================
bool KNOCK_Get_Window_Closed_Status(void);
bool KNOCK_Get_Window1_Closed_Status(void);
bool KNOCK_Get_Window2_Closed_Status(void);
//=============================================================================
// KNOCK_Set_Window_Closed_Status
//=============================================================================

void KNOCK_Set_Window1_Closed_Status(
      bool   in_status );
void KNOCK_Set_Window2_Closed_Status(
      bool   in_status );

//=============================================================================
// KNOCK_Set_Window_Length
//=============================================================================
void KNOCK_Set_Window_Length(
   uint16_t in_window_length,
   uint8_t  in_time_precision );

#endif


//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_est_select.c~4.1.3:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:45 2005
//
// %derived_by:      nz45s2 %
//
// %date_modified:   Tue Mar  1 20:18:03 2011 %
//
// %version:         4.1.3 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

#include "dd_vsep_est_select.h"


#ifdef VSEP_TCB_COMPLEX_IO

#include "dd_spark.h"
#include "dd_spark_interface.h"


uint16_t VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_MAX];
uint16_t VSEP_EST_Select_Rxd[VSEP_EST_SELECT_RXD_MESSAGE_MAX];

//=============================================================================
// This variable defines our current mode of operation.
//=============================================================================
static EST_Mode_T VSEP_EST_Select_Mode;

//=============================================================================
// Provides the number of cylinders to the select routines.
//=============================================================================
uint8_t     VSEP_EST_Number_Of_Cylinders;

EST_Mode_T  VSEP_EST_Select_Requested_Mode;

static VSEP_EST_Select_State_T VSEP_EST_Select_State;
#endif


#ifndef VSEP_TCB_COMPLEX_IO

//=============================================================================
// VSEP_PWM_Device_Initialize
//=============================================================================
FAR_COS void VSEP_EST_Select_Initialize_Device(void)
{

#ifdef VSEP_EST_SELECT_STATIC_INITIALIZATION

   VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ]      = VSEP_EST_SELECT_INITIAL[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ];
   VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL ]  = VSEP_EST_SELECT_INITIAL[ VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL];

#else
   VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_EST_STAT );
   VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_EST_CTRL );
#endif
}

#else

//=============================================================================
// VSEP_EST_Select_Manage_Transition
//
// when a set mode is called the variable is set in place, but the transition to
// te mode will occure when the next cylinder is set by the spark code.
// This routine will handle the change.
//=============================================================================
static void VSEP_EST_Select_Manage_Transition( void );

//=============================================================================
// VSEP_PWM_Device_Initialize
//=============================================================================
FAR_COS void VSEP_EST_Select_Initialize_Device(void)
{
#ifdef VSEP_EST_SELECT_STATIC_INITIALIZATION

   VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ]      = VSEP_EST_SELECT_INITIAL[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ];
   VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL ]  = VSEP_EST_SELECT_INITIAL[ VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL];

#else
   VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_EST_STAT );
   VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_EST_Select_Txd[ VSEP_EST_SELECT_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_EST_CTRL );
#endif
}

#endif

#ifdef LA_VSEP_EST_SELECT_ENABLE
typedef struct
{
   uint8_t  channel;
   uint8_t  mode;
   uint8_t  type; 

}  LA_EST_Select_T;

LA_EST_Select_T LA_EST_Select[120];
uint8_t LA_EST_Select_Counter = 0;
#endif

#ifdef VSEP_TCB_COMPLEX_IO

#if CcSYST_NUM_OF_CYLINDERS == 3
//=============================================================================
// VSEP_EST_Select_Set_Index  change for MT22.1
//=============================================================================
FAR_COS void VSEP_EST_Select_Set_Index(
   IO_Configuration_T        in_configuration,//MTSA_CONFIG_VSEP_DEVICE_0
   bool						 in_index )//Crank_Cylinder_T
{
   bool             index_est  = (bool)in_index;
 
  //VSEP_EST_Select_Txd[index][VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = VSEP_Msg_EST_Set_EST1CEN( VSEP_EST_Select_Txd[index][VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL], true );
  // VSEP_EST_Select_Txd[index][VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = VSEP_Msg_EST_Set_EST1C( VSEP_EST_Select_Txd[index][VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL], channel );
   VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = VSEP_Msg_EST_Set_INDEX( VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL], index_est ); 

   // send the message
   //VSEP_SPI_Immediate_Transfer( in_est_select->Configuration, VSEP_MESSAGE_EST_SELECT );
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_EST_SELECT );

   // disable the counter value
  // VSEP_EST_Select_Txd[index][VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = VSEP_Msg_EST_Set_EST1CEN( VSEP_EST_Select_Txd[index][VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL], false );
  // VSEP_EST_Select_Txd[index][VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = VSEP_Msg_EST_Set_EST2CEN( VSEP_EST_Select_Txd[index][VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL], false );

}
#endif
//=============================================================================
// VSEP_EST_Select_Set_Channel  change for MT22.1
//=============================================================================
FAR_COS void VSEP_EST_Select_Set_Channel(
   IO_Configuration_T        in_configuration,//MTSA_CONFIG_VSEP_DEVICE_0
   EST_Select_Cylinder_T   in_channel )//Crank_Cylinder_T
{
   uint32_t             channel  = (uint32_t)in_channel;
 
   VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = VSEP_Msg_EST_Set_EST1CEN( VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL], true );
   VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = VSEP_Msg_EST_Set_EST1C( VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL], channel );
     

   // send the message
   //VSEP_SPI_Immediate_Transfer( in_est_select->Configuration, VSEP_MESSAGE_EST_SELECT );
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_EST_SELECT );

   // disable the counter value
   VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = VSEP_Msg_EST_Set_EST1CEN( VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL], false );
   VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = VSEP_Msg_EST_Set_EST2CEN( VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL], false );

}


//=============================================================================
// VSEP_EST_Select_Set_Channel
//=============================================================================
FAR_COS void VSEP_EST_Select_Increment_Channel(
   EST_Select_Cylinder_T   in_channel )//Crank_Cylinder_T
{
   uint32_t channel = (uint32_t)in_channel;
   uint16_t index=0;
//   VSEP_EST_Select_Manage_Transition();

#ifdef LA_VSEP_EST_SELECT_ENABLE
   if ( LA_EST_Select_Counter < 120 )
   {
      LA_EST_Select[LA_EST_Select_Counter].channel = in_channel;
      LA_EST_Select[LA_EST_Select_Counter].mode = VSEP_EST_Select_Mode;
      LA_EST_Select[LA_EST_Select_Counter].type = 1; 
      LA_EST_Select_Counter++;
   }
#endif
   //
   // Test if we are using a single est (true) or double.
   //
   switch( VSEP_EST_Select_Mode )
   {
   case EST_MODE_SINGLE_CHANNEL:
//   case EST_MODE_MULTIPLE_CHANNEL: Need to add this to the list !!!
      // send a spy resync request (counter)
      break;

   case EST_MODE_PAIRED_SINGLE_ENABLE:
   case EST_MODE_SEQUENTIAL_SINGLE_ENABLE:
   case EST_MODE_SIMULTANEOUS_SINGLE_ENABLE:
   //   if( DISCRETE_OUT_EST_SYNC )//should be consider again
   //   {
         // Force VSEP SYNC low ( switch to next EST )
    //    PORT_DISCRETE_Set_State();//set the discrete directly for MTSA_CONFIG_D_OUT_EST_SYNC
   // DD_SetDiscrete(DISCRETE_OUT_EST_SYNC,true);
   HAL_GPIO_SET_ESTSYNC_Enable(true);
   
   while(index<20)
   	{
            index++;
   	}
	//DD_SetDiscrete(DISCRETE_OUT_EST_SYNC,false);
  HAL_GPIO_SET_ESTSYNC_Enable(false);
     // }
      break;
   case EST_MODE_PAIRED_MULTIPLE_ENABLE:
   case EST_MODE_SEQUENTIAL_MULTIPLE_ENABLE:
   case EST_MODE_SIMULTANEOUS_MULTIPLE_ENABLE:
   default:
      // If setting up spark: A, C, E or G
      if ( ( channel & 0x01 ) == 0x00 )
      {
     //    if( DISCRETE_OUT_EST_SYNC )
     //    {
            // Transition from inactive (lo) to active (hi) for EST1C ( switch to next EST )
            //DD_SetDiscrete(DISCRETE_OUT_EST_SYNC,true);
             HAL_GPIO_SET_ESTSYNC_Enable(true);
      //   }
      }
      else // setting up spark: B, D, F or H
      {
     //    if( DISCRETE_OUT_EST_SYNC)
       //  {
            // Transition from active (hi) to inactive (lo) for EST1C ( switch to next EST )
         	//DD_SetDiscrete(DISCRETE_OUT_EST_SYNC,false);
         	 HAL_GPIO_SET_ESTSYNC_Enable(false);
       //  }
      }
      break;
   }

}

//=============================================================================
// VSEP_EST_Select_Enable
//=============================================================================
FAR_COS void VSEP_EST_Select_Enable(void)
{
 //DD_SetDiscrete(DISCRETE_OUT_EST_SYNC,false);
 HAL_GPIO_SET_ESTSYNC_Enable(false);

   // Activate the EST signal
   // Put code here...

}


//=============================================================================
// VSEP_EST_Select_Disable
//=============================================================================
FAR_COS void VSEP_EST_Select_Disable(void)
{
  // Parameter_Not_Used( DISCRETE_OUT_EST_SYNC );
   // Deactivate the EST signal
   // put code here...
}

//=============================================================================
// VSEP_EST_Select_Set_Number_Of_Cylinders
//=============================================================================
FAR_COS void VSEP_EST_Select_Set_Number_Of_Cylinders(
   uint8_t           in_number_of_cylinders )
{
   VSEP_EST_Number_Of_Cylinders = in_number_of_cylinders;
   //Parameter_Not_Used( DISCRETE_OUT_EST_SYNC );

   // send spi message?

}


//=============================================================================
// VSEP_EST_Select_Set_Mode
//=============================================================================
FAR_COS void VSEP_EST_Select_Set_Mode(
   IO_Configuration_T        in_configuration,//MTSA_EST_SELECT_DEVICE/	VSEP_INDEX_0
   EST_Mode_T        in_mode )
{
   switch( in_mode )
   {
   case EST_MODE_SINGLE_CHANNEL:
      VSEP_EST_Select_Mode = in_mode;
      //
      // Set PF Mode 0
      //
      VSEP_EST_Select_State.paired_fire_mode = VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED; // VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED

      //
      // Set Index 0
      //
      VSEP_EST_Select_State.index_mode = VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER; // VSEP_EST_SELECT_INCREMENT_INDEX_MODE_TWICE_PER

      //
      // Set Edge 0
      //
      VSEP_EST_Select_State.index_pin_select = VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN; // VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN
      break;
// must implement this
#if 0
   case EST_MODE_MULTIPLE_CHANNEL:
      VSEP_EST_Select_Mode = in_mode;
      //
      // Set PF Mode 0
      //
      VSEP_EST_Select_State.paired_fire_mode = VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED; // VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED

      //
      // Set Index 0
      //
      VSEP_EST_Select_State.index_mode = VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER; // VSEP_EST_SELECT_INCREMENT_INDEX_MODE_TWICE_PER

      //
      // Set Edge 0
      //
      VSEP_EST_Select_State.index_pin_select = VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN; // VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN
      break;
#endif
   case EST_MODE_PAIRED_SINGLE_ENABLE:
      VSEP_EST_Select_Mode = in_mode;
      //
      // Set PF Mode 1
      //
      VSEP_EST_Select_State.paired_fire_mode = VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED; // VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED

      //
      // Set Index 0
      //
      VSEP_EST_Select_State.index_mode = VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER; // VSEP_EST_SELECT_INCREMENT_INDEX_MODE_TWICE_PER

      //
      // Set Edge 0
      //
      VSEP_EST_Select_State.index_pin_select = VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN; // VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN
      break;

   case EST_MODE_PAIRED_MULTIPLE_ENABLE:
      VSEP_EST_Select_Mode = in_mode;
      //
      // Set PF Mode 1
      //
      VSEP_EST_Select_State.paired_fire_mode = VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED; // VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED

      //
      // Set Index 1
      //
      VSEP_EST_Select_State.index_mode = VSEP_EST_SELECT_INCREMENT_INDEX_MODE_TWICE_PER; // VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER

      //
      // Set Edge 0
      //
      VSEP_EST_Select_State.index_pin_select = VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN; // VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN
      break;

   case EST_MODE_SEQUENTIAL_SINGLE_ENABLE:
      VSEP_EST_Select_Mode = in_mode;
      //
      // Set PF Mode 0
      //
      VSEP_EST_Select_State.paired_fire_mode = VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED; // VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED
      //
      // Set Index 0
      //
      VSEP_EST_Select_State.index_mode = VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER; // VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER

      //
      // Set Edge 1
      //
      VSEP_EST_Select_State.index_pin_select = VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN; // VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN

      break;

   case EST_MODE_SEQUENTIAL_MULTIPLE_ENABLE:
      VSEP_EST_Select_Mode = EST_MODE_SEQUENTIAL_MULTIPLE_ENABLE;
      //
      // Set PF Mode 0
      //
      VSEP_EST_Select_State.paired_fire_mode = VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED; // VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED
      //
      // Set Index 1
      //
      VSEP_EST_Select_State.index_mode = VSEP_EST_SELECT_INCREMENT_INDEX_MODE_TWICE_PER; // VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER

      //
      // Set Edge 1
      //
      VSEP_EST_Select_State.index_pin_select = VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN; // VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN

      break;

   case EST_MODE_SIMULTANEOUS_SINGLE_ENABLE:
      VSEP_EST_Select_Mode = in_mode;
      //
      // Set PF Mode 1
      //
      VSEP_EST_Select_State.paired_fire_mode = VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED; // VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED
      //
      // Set Index 0
      //
      VSEP_EST_Select_State.index_mode = VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER; // VSEP_EST_SELECT_INCREMENT_INDEX_MODE_TWICE_PER

      //
      // Set Edge 1
      //
      VSEP_EST_Select_State.index_pin_select = VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN; // VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN

      break;

   case EST_MODE_SIMULTANEOUS_MULTIPLE_ENABLE:
      VSEP_EST_Select_Mode = EST_MODE_SIMULTANEOUS_SINGLE_ENABLE;
      //
      // Set PF Mode 1
      //
      VSEP_EST_Select_State.paired_fire_mode = VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED; // VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED
      //
      // Set Index 1
      //
      VSEP_EST_Select_State.index_mode = VSEP_EST_SELECT_INCREMENT_INDEX_MODE_TWICE_PER; // VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER

      //
      // Set Edge 1
      //
      VSEP_EST_Select_State.index_pin_select = VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN; // VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN

      break;
   }
   {
      uint16_t est_ctrl = 0;

      // set up the message
      est_ctrl = VSEP_Msg_EST_Set_PFMODE( est_ctrl, ( VSEP_EST_Select_State.paired_fire_mode ? 1 : 0 ) );
      est_ctrl = VSEP_Msg_EST_Set_EDGE( est_ctrl, ( VSEP_EST_Select_State.index_pin_select ? 1 : 0 ) );
      est_ctrl = VSEP_Msg_EST_Set_INDEX( est_ctrl, ( VSEP_EST_Select_State.index_mode ? 1 : 0 ) );

      VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] = est_ctrl;
   }
   // send the message
   
   //VSEP_SPI_Immediate_Transfer( in_est_select->Configuration, VSEP_MESSAGE_EST_SELECT );
   VSEP_SPI_Immediate_Transfer(in_configuration, VSEP_MESSAGE_EST_SELECT );

}
//=============================================================================
// VSEP_EST_Set_PF_Mode
//=============================================================================
FAR_COS void VSEP_EST_Set_PF_Mode(
   IO_Configuration_T        in_configuration,//MTSA_EST_SELECT_DEVICE/	VSEP_INDEX_0
   VSEP_EST_Select_Paired_Fire_Mode_T        in_mode )
{
	VSEP_EST_Select_State.paired_fire_mode = in_mode;
	VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL] =            
      VSEP_Msg_EST_Set_PFMODE( VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL],    in_mode) ;
      VSEP_SPI_Immediate_Transfer(in_configuration, VSEP_MESSAGE_EST_SELECT );
	
}
//=============================================================================
// VSEP_EST_Select_Get_Mode
//=============================================================================
FAR_COS EST_Mode_T VSEP_EST_Select_Get_Mode(void)
{
   //Parameter_Not_Used( DISCRETE_OUT_EST_SYNC );
   return VSEP_EST_Select_Mode;
}

//=============================================================================
// VSEP_EST_Select_Get_Mode
//=============================================================================
FAR_COS bool VSEP_EST_Select_Get_Mode_PF(void)
{
  // Parameter_Not_Used( DISCRETE_OUT_EST_SYNC );
   return   VSEP_EST_Select_State.paired_fire_mode;
}
//=============================================================================
// VSEP_EST_Select_Manage_Transition
//=============================================================================
static void VSEP_EST_Select_Manage_Transition( void )
{
   EST_Mode_T mode = VSEP_EST_Select_Requested_Mode;

   if(  ( EST_MODE_SIMULTANEOUS_SINGLE_ENABLE == VSEP_EST_Select_Mode
      ||  EST_MODE_SIMULTANEOUS_MULTIPLE_ENABLE   == VSEP_EST_Select_Mode )
      &&( EST_MODE_SEQUENTIAL_SINGLE_ENABLE == VSEP_EST_Select_Requested_Mode
      ||  EST_MODE_SEQUENTIAL_MULTIPLE_ENABLE   == VSEP_EST_Select_Requested_Mode )
      &&( SPARK_Cylinder_Event_ID == EST_SELECT_CYLINDER_A ) )
      //or (( GetCurrentCylinder() + 1 ) % NUMBER_OF_CYLINDERS) == EST_SELECT_CYLINDER_A;
   {//IO_CRANK_Get_Future_Cylinder_ID( Active_Crank, 1 )
      // Cannot transition again until mode is reset
      VSEP_EST_Select_Requested_Mode = VSEP_EST_Select_Mode;

//      VSEP_EST_Select_Set_Sequential_Mode();

      if( EST_MODE_SEQUENTIAL_MULTIPLE_ENABLE   == mode )
      {
//         VSEP_Set_EST_Input_Mode( 2 );
      }
      else
      {
//         VSEP_Set_EST_Input_Mode( 2 );
      }

      VSEP_EST_Select_Mode = mode;
   }

}


#endif
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 * 4.1.3 mt20u2#800 11/01/02 nz45s2 RSM_CTC_8093_Add Mt22p1 ETC 3cylinder package_Rev0_20110120 *
\*===========================================================================*/

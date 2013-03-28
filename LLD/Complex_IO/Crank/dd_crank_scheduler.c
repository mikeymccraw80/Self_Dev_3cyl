
#include "dd_crank_scheduler.h"
#include "io_config_crank.h"



IO_Callback_T CRANK_Event_List[CRANK_EVENT_ID_MAX] ;

uint32_t CRANK_Schedule_Table[CRANK_VIRTUAL_TEETH_PER_REVOLUTION];


//=============================================================================
// /-----------------------------------------------------------------------\
// | SCHEDULE AND EXECUTE THE Crank EVENT
// \-----------------------------------------------------------------------/
//=============================================================================


//=============================================================================
// CRANK_Insert_Event_In_Table
//=============================================================================
bool CRANK_Insert_Event_In_Table(
   Crank_Event_Id_T  in_event_id,
   uCrank_Angle_T    in_event_angle )
{
   uint32_t  tooth;

   // subtract one to get array index.
   tooth = CRANK_Convert_uCrank_Angle_To_Teeth( in_event_angle ) - 1;

   //
   // limit check
   //
   if( tooth >= CRANK_SCHEDULE_CONFIG_VIRTUAL_TEETH_PER_REVOLUTION )
   {
      tooth %= CRANK_SCHEDULE_CONFIG_VIRTUAL_TEETH_PER_REVOLUTION;
   }

  CRANK_Schedule_Table[ tooth ] |= CRANK_Set_Priority_Enable( 1, in_event_id );

   return true;
}

//=============================================================================
// CRANK_Remove_Event_From_Table
//=============================================================================
bool CRANK_Remove_Event_From_Table(
   Crank_Event_Id_T  in_event_id,
   uCrank_Angle_T    in_event_angle )
{
   uint32_t  tooth;

   // subtract one to get array index.
   tooth = CRANK_Convert_uCrank_Angle_To_Teeth( in_event_angle ) - 1;

   //
   // limit check
   //
   if( tooth > CRANK_SCHEDULE_CONFIG_VIRTUAL_TEETH_PER_REVOLUTION )
   {
      tooth %= CRANK_SCHEDULE_CONFIG_VIRTUAL_TEETH_PER_REVOLUTION;
   }

   CRANK_Schedule_Table[ tooth ] &= ~( CRANK_Set_Priority_Enable( 1, in_event_id ) );

   return true;
}




//=============================================================================
// CRANK_SCHEDULER_Assign_Event
//=============================================================================
bool CRANK_SCHEDULER_Assign_Event( 
   Crank_Event_Id_T  in_event_id, 
   uCrank_Angle_T    in_first_event_angle, 
   uCrank_Angle_T    in_event_angle_offset, 
   uint32_t          in_number_of_events )
{
   bool           dynamic_is_on = false;
   uint32_t       event_count;
   uCrank_Angle_T angle;

   for( event_count = 0; event_count < in_number_of_events; event_count++ )
   {
      angle = in_first_event_angle + ( in_event_angle_offset * event_count );
      
      // schedule tooth for event in_event_id
      dynamic_is_on = CRANK_Insert_Event_In_Table( in_event_id, angle );
   }

   return dynamic_is_on;
}

//=============================================================================
// CRANK_SCHEDULER_Remove_Event
//=============================================================================
void CRANK_SCHEDULER_Remove_Event( 
   Crank_Event_Id_T  in_event_id, 
   uCrank_Angle_T    in_first_event_angle, 
   uCrank_Angle_T    in_event_angle_offset, 
   uint32_t          in_number_of_events )
{
   bool           dynamic_is_on = false;
   uint32_t       event_count;
   uCrank_Angle_T angle;

   for( event_count = 0; event_count < in_number_of_events; event_count++ )
   {
      angle = in_first_event_angle + ( in_event_angle_offset * event_count );
      
      // schedule tooth for event in_event_id
      dynamic_is_on = CRANK_Remove_Event_From_Table( in_event_id, angle );
   }


}




//=============================================================================
// CRANK_SCHEDULER_Assign_Handler_To_Event_ID
//=============================================================================
void CRANK_SCHEDULER_Assign_Handler_To_Event_ID(
   Crank_Event_Id_T  in_event_id,
   IO_Callback_T     in_callback )
{
   //
   //   SynEv0 .. SynEv15 are the associated event identifiers.
   //   The priority order of Event ID is SynEv15 down to SynEv0.
   //
   CRANK_Event_List[ (uint8_t)in_event_id ] = in_callback;


}







//=============================================================================
// include files
//=============================================================================
#include "dd_mcd5406.h"
#include "dd_tpu_interface.h"

//=============================================================================
// type define
//=============================================================================
#define MCD5406_FLAG_UNUSED (32UL)
#define MCD5406_LOCAL_ARRAY_FIRST_INDEX_POSITION  (sizeof(MCD5406_SDM_T))


typedef enum MCD5406_HSR_Tag
{
   MCD5406_HSR_UPDATE      = 4,
   MCD5406_HSR_INTIALIZE   = 5,
   MCD5406_HSR_REQUEST     = 6,
   MCD5406_HSR_SHUTDOWN    = 7

}  MCD5406_HSR_T;

typedef enum MCD5406_Array_Flags_Tag
{
   MCD5406_ARRAY_FLAGS_STORE_ACTUAL = 24,
   MCD5406_ARRAY_FLAGS_DMA          = 25,
   MCD5406_ARRAY_FLAGS_USE_TCR2     = 26,
   MCD5406_ARRAY_FLAGS_END_SEQ      = 27,
   MCD5406_ARRAY_FLAGS_ABS_EVENT    = 28,
   MCD5406_ARRAY_FLAGS_END_LOOP     = 29,
   MCD5406_ARRAY_FLAGS_PIN_STATE    = 30,
   MCD5406_ARRAY_FLAGS_INTERRUPT    = 31

}  MCD5406_Array_Flags_T;

typedef enum MCD5406_Start_Event_Flags_Tag
{
   MCD5406_START_EVENT_FLAGS_SE_POINTER      = 29,
   MCD5406_START_EVENT_FLAGS_INIT_PIN_STATE  = 30,
   MCD5406_START_EVENT_FLAGS_USE_START_EVENT = 31

}  MCD5406_Start_Event_Flags_T;

typedef enum MCD5406_End_Event_Flags_Tag
{
   MCD5406_END_EVENT_FLAGS_EE_STORE_ACTUAL   = 24,
   MCD5406_END_EVENT_FLAGS_EE_DMA            = 25,
   MCD5406_END_EVENT_FLAGS_EE_USE_TCR2       = 26,
   MCD5406_END_EVENT_FLAGS_USE_END_EVENT     = 29,
   MCD5406_END_EVENT_FLAGS_EE_PIN_STATE      = 30,
   MCD5406_END_EVENT_FLAGS_EE_INTERRUPT      = 31

}  MCD5406_Start_Event_Flags_T;

typedef enum MCD5406_Status_Flags_Tag
{
   MCD5406_STATUS_FLAGS_DMA_SCHED    = 30,
   MCD5406_STATUS_FLAGS_LOOP_RUNNING = 31

}  MCD5406_Status_Flags_T;

const uint8_t  MCD5406_Global_Flags_Map[] =
{
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_DELAY_UPDATE
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_ENABLE_STOP_STATE
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_STOPPED_PIN_STATE
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_STOP_IMMEDIATE
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_DESIRED_PIN_STATE
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_ENABLE_INIT_STATE
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_INIT_PIN_STATE
   MCD5406_START_EVENT_FLAGS_USE_START_EVENT,   // RQOM_FLAG_USE_START_EVENT
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_ENABLE_DROPED_EVENTS
   MCD5406_START_EVENT_FLAGS_SE_POINTER,        // RQOM_FLAG_START_EVENT_USES_POINTER
   MCD5406_START_EVENT_FLAGS_INIT_PIN_STATE,    // RQOM_FLAG_START_EVENT_ACTIVE_STATE
   MCD5406_END_EVENT_FLAGS_USE_END_EVENT,       // RQOM_FLAG_USE_END_EVENT
   MCD5406_END_EVENT_FLAGS_EE_USE_TCR2,         // RQOM_FLAG_END_EVENT_USE_ALTERNATE_TIMER
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_END_EVENT_CAPTURE_ALTERNATE_TIMER
   MCD5406_END_EVENT_FLAGS_EE_STORE_ACTUAL,     // RQOM_FLAG_END_EVENT_STORE_ACTUAL
   MCD5406_END_EVENT_FLAGS_EE_PIN_STATE,        // RQOM_FLAG_END_EVENT_ACTIVE_STATE
   MCD5406_END_EVENT_FLAGS_EE_DMA,              // RQOM_FLAG_END_EVENT_REQUEST_DMA
   MCD5406_END_EVENT_FLAGS_EE_INTERRUPT,        // RQOM_FLAG_END_EVENT_REQUEST_INTERRUPT
   MCD5406_STATUS_FLAGS_LOOP_RUNNING,           // RQOM_FLAG_STATUS_LOOP_RUNNING
   MCD5406_STATUS_FLAGS_DMA_SCHED,              // RQOM_FLAG_STATUS_DMA_SCHEDULED
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_STATUS_INTERRUPT_SCHEDULED
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_STATUS_END_EVENT_SETUP
   MCD5406_FLAG_UNUSED,                         // RQOM_FLAG_STATUS_MATCH_FOLLOWING_NEXT_EVENT_INVALID
   MCD5406_FLAG_UNUSED                          // RQOM_FLAG_STATUS_DUAL_ACTION_LAST_MATCH_A
};

const uint8_t  MCD5406_Array_Flags_Map[] =
{
   MCD5406_ARRAY_FLAGS_END_SEQ,        // RQOM_ARRAY_FLAG_END_SEQUENCE
   MCD5406_ARRAY_FLAGS_DMA,            // RQOM_ARRAY_FLAG_REQUEST_DMA
   MCD5406_ARRAY_FLAGS_INTERRUPT,      // RQOM_ARRAY_FLAG_REQUEST_INTERRUPT
   MCD5406_ARRAY_FLAGS_USE_TCR2,       // RQOM_ARRAY_FLAG_MATCH_ALTERNATE_TIMER,
   MCD5406_FLAG_UNUSED,                // RQOM_ARRAY_FLAG_CAPTURE_ALTERNATE_TIMER
   MCD5406_ARRAY_FLAGS_STORE_ACTUAL,   // RQOM_ARRAY_FLAG_STORE_TIMER
   MCD5406_ARRAY_FLAGS_ABS_EVENT,      // RQOM_ARRAY_FLAG_ABSOLUTE_MATCH_EVENT
   MCD5406_ARRAY_FLAGS_END_LOOP,       // RQOM_ARRAY_FLAG_END_OF_LOOP
   MCD5406_ARRAY_FLAGS_PIN_STATE,      // RQOM_ARRAY_FLAG_ACTIVE_STATE
   MCD5406_FLAG_UNUSED                 // RQOM_ARRAY_FLAG_STATUS_DROPPED_EVENT
}; 

//=============================================================================
// MCD5406_Initialize_Channel
//=============================================================================
void MCD5406_Initialize_Channel(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   void        *in_init )
{
   uint32_t critical_status;
   uint8_t  fun_mode0;
   uint8_t  fun_mode1;

  TPU_Channel_T channel= configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
  TPU_Index_T    index_group = TPU_Get_Index_Group(index);

   critical_status = Enter_Critical_Section();

   TPU_Initialize_Channel(index, configure);

   TPU_Set_Static_Base_Address(index, configure);

   fun_mode0 =( configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE0== TPU_TCR1_TIME_BASE) ? 0 : 1;

   p_tpu->Channel_Map[index_group].Channel_Control[channel].CSCR.F.FM0 = fun_mode0;

   fun_mode1 = configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE0;//RQOM_IMMEDIATE_UPDATE, RQOM_SYNCHRONOUS_UPDATE

   p_tpu->Channel_Map[index_group].Channel_Control[channel].CSCR.F.FM1 = fun_mode1;
   
   //Disable 

   //No links required

   // Issue HSR
   TPU_Set_HSR(index, configure, MCD5406_HSR_INTIALIZE );

   //Set channel priority CPR
   TPU_Channel_Enable(index, configure); 

   // Wait until the channel not active
   TPU_Wait_HSR_Request_Complete(index, configure);

   Leave_Critical_Section( critical_status );
}

//=============================================================================
// MCD5406_Shutdown
//=============================================================================
void MCD5406_Shutdown (  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   //The RQOM can also be shut down by sending a link from any other TPU channel
   interrupt_state_t  critical_status;

   //Enter critical section
   critical_status = Enter_Critical_Section();
   
   // Issue HSR
   TPU_Set_HSR(index, configure, MCD5406_HSR_SHUTDOWN);

   // Wait until the channel not active
   TPU_Wait_HSR_Request_Complete(index, configure);

   // Disable channel
   TPU_Channel_Disable(index, configure);

   Leave_Critical_Section( critical_status );

}

//=============================================================================
// MCD5406_Request
//=============================================================================
void MCD5406_Request(  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   // Issue update HSR
   TPU_Set_HSR(index, configure, MCD5406_HSR_REQUEST);
}

//=============================================================================
// MCD5406_Update
//=============================================================================
void MCD5406_Update(  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   // Issue update HSR
   TPU_Set_HSR(index, configure, MCD5406_HSR_UPDATE);
}

 MCD5406_SDM_T *mcd5406_sdm_Vis; 
//=============================================================================
// MCD5406_Set_Parameter
//=============================================================================
void MCD5406_Set_Parameter(  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   Rqom_Parameter_T  in_parameter,
   uint32_t          in_value )

{
   MCD5406_SDM_T *mcd5406_sdm 
   	= (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   mcd5406_sdm_Vis = mcd5406_sdm;
   
   switch ( in_parameter )
   {
   case RQOM_PARAMETER_ARRAY_SIZE:
      {
         mcd5406_sdm->Array_Parameters.F.Array_Size = in_value;
      }
      break;

   case RQOM_PARAMETER_START_EVENT:
      {
         mcd5406_sdm->Start_Event.F.Start_Event = in_value;
      }
      break;

   case RQOM_PARAMETER_END_EVENT:
      {
         mcd5406_sdm->End_Event.F.End_Event = in_value;
      }
      break;

   default:
      {
         // do nothing
      }
      break;
   }
}

//=============================================================================
// MCD5406_Get_Parameter
//=============================================================================
uint32_t MCD5406_Get_Parameter  (TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   Rqom_Parameter_T  in_parameter )
{
   uint32_t value;

   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   switch ( in_parameter )
   {
   case RQOM_PARAMETER_ARRAY_SIZE:
      {
         value = mcd5406_sdm->Array_Parameters.F.Array_Size;
      }
      break;

   case RQOM_PARAMETER_START_EVENT:
      {
         value = mcd5406_sdm->Start_Event.F.Start_Event;
      }
      break;

   case RQOM_PARAMETER_LOOP_COUNTER:
      {
         value = mcd5406_sdm->General_Flags.F.Loop_Counter;
      }
      break;

   case RQOM_PARAMETER_ARRAY_FLAGS_BUFFERED:
      {
         value = mcd5406_sdm->Array_Parameters.F.Array_Flags_Buf;
      }
      break;

   case RQOM_PARAMETER_ARRAY_INDEX:
      {
         value = mcd5406_sdm->Array_Parameters.F.Index;
      }
      break;

   case RQOM_PARAMETER_INTERRUPT_INDEX:
      {
         value = mcd5406_sdm->General_Flags.F.Intr_Index;
      }
      break;

   case RQOM_PARAMETER_END_EVENT:
      {
         value = mcd5406_sdm->End_Event.F.End_Event;
      }
      break;

   default:
      {
         // do nothing
         value = 0;
      }
      break;
   }

   return value;
}

//=============================================================================
// MCD5406_Set_Flag
//=============================================================================
void MCD5406_Set_Flag (TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   Rqom_Flag_T    in_flag,
   bool           in_value )
{
   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint8_t        flag        = MCD5406_Global_Flags_Map[in_flag];

   if ( flag < MCD5406_FLAG_UNUSED )
   {
      if ( in_flag < RQOM_FLAG_USE_END_EVENT )
      {
         // Start Event Flag
         mcd5406_sdm->Start_Event.U32 = Insert_Bits( mcd5406_sdm->Start_Event.U32, in_value, flag, 1 );
      }
      else if ( in_flag < RQOM_FLAG_STATUS_LOOP_RUNNING )
      {
         // End Event Flag
         mcd5406_sdm->End_Event.U32 = Insert_Bits( mcd5406_sdm->End_Event.U32, in_value, flag, 1 );
      }
      else
      {
         // Status Flag
         mcd5406_sdm->General_Flags.U32 = Insert_Bits( mcd5406_sdm->General_Flags.U32, in_value, flag, 1 );
      }
   }
}

//=============================================================================
// MCD5406_Get_Flag
//=============================================================================
bool MCD5406_Get_Flag(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   Rqom_Flag_T    in_flag )
{
   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   bool           state       = false;
   uint8_t        flag        = MCD5406_Global_Flags_Map[in_flag];

   if ( flag < MCD5406_FLAG_UNUSED )
   {
      if ( in_flag < RQOM_FLAG_USE_END_EVENT )
      {
         // Start Event Flag
         state = (bool)Extract_Bits( mcd5406_sdm->Start_Event.U32, flag, 1 );
      }
      else if ( in_flag < RQOM_FLAG_STATUS_LOOP_RUNNING )
      {
         // End Event Flag
         state = (bool)Extract_Bits( mcd5406_sdm->End_Event.U32, flag, 1 );
      }
      else
      {
         // Status Flag
         state = (bool)Extract_Bits( mcd5406_sdm->General_Flags.U32, flag, 1 );
      }
   }

   return state;
}

//=============================================================================
// MCD5406_Set_Array_Flag
//=============================================================================
void MCD5406_Set_Array_Flag(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t         *in_array,
   uint32_t          in_index,
   Rqom_Array_Flag_T in_flag,
   bool              in_value )
{
   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint8_t        flag        = MCD5406_Array_Flags_Map[in_flag];

   if ( flag < MCD5406_FLAG_UNUSED )
   {
      if ( in_array == NULL )
      {
         // Local Array
         uint32_t   mcd5406_temp;
         uint32_t   *local_array;

         mcd5406_temp = MCD5406_LOCAL_ARRAY_FIRST_INDEX_POSITION +  (in_index* sizeof(uint32_t));
         local_array  = (uint32_t*)mcd5406_sdm + (mcd5406_temp>>2);

         *local_array = Insert_Bits( *local_array, in_value, flag, 1 );
      }
      else
      {
         // Use Array Pointer
         uint32_t   *external_array = in_array + ( in_index * sizeof(uint32_t) );

         *external_array = Insert_Bits( *external_array, in_value, flag, 1 );
      }
   }
}

//=============================================================================
// MCD5406_Get_Array_Flag
//=============================================================================
bool MCD5406_Get_Array_Flag(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index,
   Rqom_Array_Flag_T    in_flag )
{
   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   bool           state       = false;
   uint8_t        flag        = MCD5406_Array_Flags_Map[in_flag];

   if ( flag < MCD5406_FLAG_UNUSED )
   {
      if ( in_array == NULL )
      {
         uint32_t mcd5406_temp;
         uint32_t   *local_array;

         mcd5406_temp = MCD5406_LOCAL_ARRAY_FIRST_INDEX_POSITION +  (in_index* sizeof(uint32_t));
         local_array  = (uint32_t*)mcd5406_sdm + (mcd5406_temp>>2);
         state = (bool)Extract_Bits( *local_array, flag, 1 );
      }
      else
      {
         // Use Array Pointer
         uint32_t   *external_array = in_array + ( in_index * sizeof(uint32_t) );
         state = (bool)Extract_Bits( *external_array, flag, 1 );
      }
   }

   return state;
}

//=============================================================================
// MCD5406_Set_All_Array_Flags
//=============================================================================
void MCD5406_Set_All_Array_Flags(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index,
   uint32_t       in_all_flags )
{
   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t       flags       = in_all_flags >> BIT_24;

   if ( in_array == NULL )
   {
      // Local Array
      uint32_t mcd5406_temp;
      uint32_t   *local_array;
      mcd5406_temp = MCD5406_LOCAL_ARRAY_FIRST_INDEX_POSITION +  (in_index * sizeof(uint32_t));
      local_array  = (uint32_t*)mcd5406_sdm + (mcd5406_temp>>2);
      *local_array = Insert_Bits( *local_array, flags, BIT_24, BIT_8 );
   }
   else
   {
      // Use Array Pointer
      uint32_t   *external_array = in_array + ( in_index * sizeof(uint32_t) );
      *external_array = Insert_Bits( *external_array, flags, BIT_24, BIT_8 );
   }
}

//=============================================================================
// MCD5406_Get_All_Array_Flags
//=============================================================================
uint32_t MCD5406_Get_All_Array_Flags(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index )
{

   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t       flags;

   if ( in_array == NULL )
   {
         uint32_t mcd5406_temp;
         uint32_t   *local_array;

         mcd5406_temp = MCD5406_LOCAL_ARRAY_FIRST_INDEX_POSITION +  (in_index* sizeof(uint32_t));
         local_array  = (uint32_t*)mcd5406_sdm + (mcd5406_temp>>2);
         flags = *local_array & 0xFF000000;
   }
   else
   {
         // Use Array Pointer
         uint32_t   *external_array = in_array + ( in_index * sizeof(uint32_t) );
         flags = *external_array & 0xFF000000;
   }

   return flags;
}

//=============================================================================
// MCD5406_Set_Array_Data
//=============================================================================
void MCD5406_Set_Array_Data(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index,
   uint32_t       in_value )
{
   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   if ( in_array == NULL )
   {
      // Local Array
      uint32_t   *local_array;
      uint32_t mcd5406_temp;

      mcd5406_temp = MCD5406_LOCAL_ARRAY_FIRST_INDEX_POSITION +  (in_index* sizeof(uint32_t));
      local_array  = (uint32_t*)mcd5406_sdm + (mcd5406_temp>>2);
      *local_array = Insert_Bits( *local_array, (in_value & UINT24_MAX), BIT_0, BIT_24 );
   }
   else
   {
      // Use Array Pointer
      uint32_t   *external_array = in_array + ( in_index * sizeof(uint32_t) );
      *external_array = Insert_Bits( *external_array, (in_value & UINT24_MAX), BIT_0, BIT_24 );
   }
}

//=============================================================================
// MCD5406_Get_Array_Data
//=============================================================================
uint32_t MCD5406_Get_Array_Data(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_array,
   uint32_t       in_index )
{
   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t       value;
   
   if ( in_array == NULL )
   {
      // Local Array

      uint32_t   *local_array;
      uint32_t    mcd5406_temp;

      mcd5406_temp = MCD5406_LOCAL_ARRAY_FIRST_INDEX_POSITION +  (in_index* sizeof(uint32_t));
      local_array  = (uint32_t*)mcd5406_sdm + (mcd5406_temp>>2);
      value = *local_array & UINT24_MAX;
   }
   else
   {
      // Use Array Pointer
      uint32_t   *external_array = in_array + ( in_index * sizeof(uint32_t) );

      value = *external_array & UINT24_MAX;
   }

   return value;
}

//=============================================================================
// MCD5406_Copy_Array
//=============================================================================
void MCD5406_Copy_Array(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_source_array,
   uint32_t      *in_destination_array,
   uint32_t       in_size )
{
   MCD5406_SDM_T *mcd5406_sdm = (MCD5406_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t      *source;
   uint32_t      *destination;
   uint32_t      *local_array = (uint32_t*) ( (uint32_t)mcd5406_sdm + MCD5406_LOCAL_ARRAY_FIRST_INDEX_POSITION );

   if ( in_source_array == NULL )
   {
      source      = local_array;
      destination = in_destination_array;
   }
   else if ( in_destination_array == NULL )
   {
      source      = in_source_array;
      destination = local_array;
   }
   else
   {
      source      = in_source_array;
      destination = in_destination_array;
   }

   // make sure that both arrays were not passed in as null.
   if ( ( source != NULL ) && ( destination != NULL ) )
   {
      uint32_t counter;

      for ( counter = 0; counter < in_size; counter++ )
      {
         *(destination++) = *(source++);
      }
   }
}

//=============================================================================
// MCD5406_Use_Array
//=============================================================================
void MCD5406_Use_Array(TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t      *in_source_array,
   uint32_t       in_size )
{
   // This primitive cannot use arrays outside of the TPU so we will do a copy
   MCD5406_Copy_Array(index, configure, in_source_array, NULL, in_size );
}

//=============================================================================
// MCD5406_DISCRETE_Get_Immediate_State
//=============================================================================
bool MCD5406_DISCRETE_Get_Immediate_State(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)
{
   interrupt_state_t  critical_status;
   bool                 state, active_state;
   Polarity_T           polarity = configure.F.TPU_CHANNEL_CONFIGURATION_POLARITY;
   TPU_Channel_T channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   state = (bool)p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.OPS;

    // State  Polarity  active_state 
   //----------------
   //   0      0        1 
   //   0      1        0 
   //   1      0        0 
   //   1      1        1

   active_state   = ( ( state == polarity ) ? true: false);

  return active_state;
 
}

//=============================================================================
// MCD5406_Set_Host_Interrupt_Enable
//=============================================================================
void MCD5406_Set_Host_Interrupt_Enable(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   bool           in_state )
{
   // The tpu does not have a seperate host and io interrupt as the 
   // tpu engine is the same, however, higher level complex io
   // shall use these functions to enable differing processor families to
   // use the functionality as presented here.
   TPU_INTERRUPT_Set_Enable(index, configure, in_state );
}

//=============================================================================
// MCD5406_Get_Host_Interrupt_Enabel
//=============================================================================
bool MCD5406_Get_Host_Interrupt_Enable(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   // The tpu does not have a seperate host and io interrupt as the 
   // tpu engine is the same, however, higher level complex io
   // shall use these functions to enable differing processor families to
   // use the functionality as presented here.
   return TPU_INTERRUPT_Get_Enable(index, configure);
}

//=============================================================================
// MCD5406_Set_Host_Interrupt_Status
//=============================================================================
void MCD5406_Set_Host_Interrupt_Status(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   bool           in_status )
{
   if ( in_status == true )
   {
      // Manually trigger the interrupt
   }
   else
   {
      // The tpu does not have a seperate host and io interrupt as the 
      // tpu engine is the same, however, higher level complex io
      // shall use these functions to enable differing processor families to
      // use the functionality as presented here.
      // Clear the interrupt
      TPU_INTERRUPT_Clear_Pending(index, configure);
   }
}

//=============================================================================
// MCD5406_Get_Host_Interrupt_Status
//=============================================================================
bool MCD5406_Get_Host_Interrupt_Status(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   bool state;
   TPU_Channel_T channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   // The tpu does not have a seperate host and io interrupt as the 
   // tpu engine is the same, however, higher level complex io
   // shall use these functions to enable differing processor families to
   // use the functionality as presented here.
   state = ( Extract_Bits( TPU.CISR[index].U32, channel, 1 ) ) ? true : false;

   return state;
}

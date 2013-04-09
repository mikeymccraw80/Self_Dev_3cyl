//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            io_spi_scheduler.c~3:csrc:mt20u2#1 %
//
// created_by:       gzdmlz
//
// date_created:     Mon Aug  7 10:20:59 2006
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Sep 29 14:02:05 2006 %
//
// %version:         3 %
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================
#include "io_type.h"
#include "io_spi_scheduler.h"
#include "dd_vsep.h"
#include "reuse.h"
#include "io_spi_config.h"

typedef struct
{
   bitfield8_t Number_Of_Periodical_Messages : 7;
   bitfield8_t Running                       : 1;
}SPI_SCHEDULER_DATA_T;

//=============================================================================
// SPI_SCHEDULER_Data
//=============================================================================
static SPI_SCHEDULER_DATA_T SPI_SCHEDULER_Data = { 0, 0 };

//=============================================================================
// SPI_SCHEDULER_Initialize
//=============================================================================
 SPI_Scheduler_Status_T VSEP_SPI_SCHEDULER_Buffer_Initialize( 
   const SPI_SCHEDULER_Message_T   *in_messages, 
   uint32_t                         in_number_of_messages )
{
	SPI_SCHEDULER_Data.Number_Of_Periodical_Messages     = 0;
	SPI_SCHEDULER_Data.Running                           = false;

	return VSEP_SPI_SCHEDULER_Schedule_Messages( in_messages, in_number_of_messages );
}
//=============================================================================
// SPI_SCHEDULER_Initialize
//=============================================================================
FAR_COS void VSEP_SPI_SCHEDULER_Initialize( void )
{
	VSEP_SPI_SCHEDULER_Buffer_Initialize( SPI_SCHEDULER_Message, SPI_SCHEDULER_Message_Numberof );
	VSEP_SPI_SCHEDULER_Set_Enable( true );
}
//=============================================================================
// SPI_SCHEDULER_Clear
//=============================================================================
void VSEP_SPI_SCHEDULER_Clear( void )
{
	interrupt_state_t context;
	uint32_t i;

	context = Enter_Critical_Section();
	for( i = 0; i < SPI_SCHEDULER_Data.Number_Of_Periodical_Messages; i++ )
	{
		SPI_SCHEDULER_Priority_Queue[ SPI_SCHEDULER_Data.Number_Of_Periodical_Messages - 1 ] = 0;
	}

	SPI_SCHEDULER_Data.Number_Of_Periodical_Messages     = 0;
	SPI_SCHEDULER_Data.Running                           = false;

	Leave_Critical_Section( context );
}

//=============================================================================
// SPI_SCHEDULER_Set_Enable
//=============================================================================
 bool VSEP_SPI_SCHEDULER_Set_Enable( bool in_enable)
{
	bool previous_status = (bool)(SPI_SCHEDULER_Data.Running);

	SPI_SCHEDULER_Data.Running = in_enable;

	return previous_status;
}

//=============================================================================
// SPI_SCHEDULER_Get_Status
//=============================================================================
bool VSEP_SPI_SCHEDULER_Get_Status( void )
{
	return (bool)(SPI_SCHEDULER_Data.Running);
}

//=============================================================================
// SPI_SCHEDULER_Schedule_Messages
//=============================================================================
SPI_Scheduler_Status_T  VSEP_SPI_SCHEDULER_Schedule_Messages( 
   const SPI_SCHEDULER_Message_T   *in_messages, 
   uint32_t                         in_number_of_messages )
{
	uint32_t i;
	SPI_Scheduler_Status_T status = SPI_SCHEDULER_STATUS_OK;
	interrupt_state_t context;

	context = Enter_Critical_Section();

	for( i = 0; ( i < in_number_of_messages ) && ( status == SPI_SCHEDULER_STATUS_OK ); i++ )
	{
		status = VSEP_SPI_SCHEDULER_Schedule_Message( in_messages[i].message, in_messages[i].interval, in_messages[i].offset + SPI_SCHEDULER_START_DELAY );
	}

	Leave_Critical_Section( context );

	return status;
}

//=============================================================================
// SPI_SCHEDULER_Clear_Message
//=============================================================================
uint32_t  VSEP_SPI_SCHEDULER_Clear_Messages( 
   const SPI_SCHEDULER_Message_T   *in_messages, 
   uint32_t                         in_number_of_messages )
{
	uint32_t i;
	uint32_t message_removed = 0xffffffffU;

	interrupt_state_t context;

	context = Enter_Critical_Section();

	for( i = 0; ( i < in_number_of_messages ) && ( message_removed == 0xffffffffU ); i++ )
	{
		if( in_messages[i].interval > 0 )
		{
			if( VSEP_SPI_SCHEDULER_Clear_Message( in_messages[i].message ) == false )
			{
				message_removed = i;
			}
		}
	}

	Leave_Critical_Section( context );

   return message_removed;
}

//=============================================================================
// SPI_SCHEDULER_Schedule_Message
//=============================================================================
SPI_Scheduler_Status_T  VSEP_SPI_SCHEDULER_Schedule_Message(
   const SPI_Message_T *in_message,
   SPI_Scheduler_Time_T in_interval,
   SPI_Scheduler_Time_T in_start_time )
{
	SPI_Scheduler_Status_T status = SPI_SCHEDULER_STATUS_QUEUE_FULL;

	interrupt_state_t context;

	context = Enter_Critical_Section();

	if( SPI_SCHEDULER_Data.Number_Of_Periodical_Messages <  SPI_SCHEDULER_QUEUE_SIZE_MAX )
	{
		if( in_interval > 0 )
		{
			SPI_SCHEDULER_Priority_Queue[ SPI_SCHEDULER_Data.Number_Of_Periodical_Messages ]               = in_message;
			SPI_SCHEDULER_Priority_Queue[ SPI_SCHEDULER_Data.Number_Of_Periodical_Messages ]->cb->interval = in_interval;
			SPI_SCHEDULER_Priority_Queue[ SPI_SCHEDULER_Data.Number_Of_Periodical_Messages ]->cb->time     = in_start_time;
			SPI_SCHEDULER_Priority_Queue[ SPI_SCHEDULER_Data.Number_Of_Periodical_Messages ]->cb->status   = SPI_MESSAGE_STATUS_IDLE;
			SPI_SCHEDULER_Data.Number_Of_Periodical_Messages++;
		}

		status = SPI_SCHEDULER_STATUS_OK;
	}

	Leave_Critical_Section( context );

	return status;
}

//=============================================================================
// SPI_SCHEDULER_Clear_Message
//=============================================================================
bool VSEP_SPI_SCHEDULER_Clear_Message(const SPI_Message_T *in_message )
{
	bool message_removed = false;
	interrupt_state_t context ;   
	uint32_t i;

	context = Enter_Critical_Section();
	for( i = 0; i < SPI_SCHEDULER_Data.Number_Of_Periodical_Messages; i++ )
	{
		if( SPI_SCHEDULER_Priority_Queue[ i ] == in_message )
		{
			SPI_SCHEDULER_Priority_Queue[ i ] = SPI_SCHEDULER_Priority_Queue[ SPI_SCHEDULER_Data.Number_Of_Periodical_Messages - 1 ];
			SPI_SCHEDULER_Priority_Queue[ SPI_SCHEDULER_Data.Number_Of_Periodical_Messages - 1 ] = 0;
			SPI_SCHEDULER_Data.Number_Of_Periodical_Messages--;
			message_removed = true;
		}
	}

	Leave_Critical_Section( context );

	return message_removed;
}

//=============================================================================
// SPI_SCHEDULER_Service_Scheduler
//=============================================================================
void VSEP_SPI_SCHEDULER_Service_Scheduler(SPI_Scheduler_Time_T in_time)
{
	uint8_t i;

	for (i = 0; i < SPI_SCHEDULER_Data.Number_Of_Periodical_Messages; i++ )
	{
		if ( in_time >= SPI_SCHEDULER_Priority_Queue[i]->cb->time ) 
		{
			SPI_SCHEDULER_Priority_Queue[i]->cb->time += SPI_SCHEDULER_Priority_Queue[i]->cb->interval;
			if ( SPI_SCHEDULER_Data.Running ) 
			{
				VSEP_SPI_Port_Transfer( SPI_SCHEDULER_Priority_Queue[i]->def);
			}
		}
	}
}
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/


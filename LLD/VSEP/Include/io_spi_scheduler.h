#ifndef IO_SPI_SCHEDULER_H
#define IO_SPI_SCHEDULER_H
//=============================================================================
//
//       COPYRIGHT, 2002, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
//===========================================================================*
// %name:            io_spi_scheduler.h %
//
// created_by:       jwyrick
//
// date_created:     Tue Oct  1 11:02:11 2002
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Mon Aug  7 10:21:52 2006 %
//
// %version:         2 %
//
//===========================================================================*
// @doc
//
// @module io_spi_scheduler.h | Name of Module
//
// The purpose of this module is to Schedule Spi Messages
//
// <nl> Put a brief description here 
// brief description continued
// brief description continued
//
// @normal Copyright <cp> 2001 Delco Electronics , All Rights Reserved
//
// @topic SPI API Overview |  add some kind of overview here
//
// @head3 SPI Schedule  Configuration Definition |
// @index | SPI Schedule & CONFIG
//
// @head3 SPI Schedule API Definition
// @index | SPI Schedule & API
//
// @end
//
// SPECIFICATION REVISION:
//
//===========================================================================*
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
//
//=============================================================================

#include "spi_message.h"
#include "dd_vsep.h"


typedef enum 
{
   SPI_SCHEDULER_STATUS_OK,
   SPI_SCHEDULER_STATUS_IDLE,
   SPI_SCHEDULER_STATUS_QUEUE_FULL
}SPI_Scheduler_Status_T;

typedef uint32_t SPI_Scheduler_Time_T;

typedef struct SPI_SCHEDULER_Message_Tag
{
   const SPI_Message_T     *message; 
   SPI_Scheduler_Time_T     offset; 
   SPI_Scheduler_Time_T     interval;
   
} SPI_SCHEDULER_Message_T;

//=============================================================================
// SPI_SCHEDULER_QUEUE_SIZE_MAX
//=============================================================================
extern const uint8_t SPI_SCHEDULER_QUEUE_SIZE_MAX;

//=============================================================================
// SPI_SCHEDULER_START_DELAY
//=============================================================================
extern const uint8_t SPI_SCHEDULER_START_DELAY;

//=============================================================================
// SPI_SCHEDULER_Priority_Queue
//=============================================================================
extern const SPI_Message_T *SPI_SCHEDULER_Priority_Queue[];

//=============================================================================
// SPI_SCHEDULER_Initialize
//
// @func Initialize the SPI scheduler allocating all messages passed in in_messages
//
// @parm  SPI_SCHEDULER_Message_T | *in_messages | An array of SPI_SCHEDULER_Message_T
//    message objects. Refer to the SPI_SCHEDULER_Message_Tag structure above.
//
// @parm  uint32_t | in_number_of_messages | The number of SPI_SCHEDULER_Message_T objects
//    stored in in_messages.
//
// @rdesc none 
//
// @end
//=============================================================================
 SPI_Scheduler_Status_T VSEP_SPI_SCHEDULER_Buffer_Initialize( 
   const SPI_SCHEDULER_Message_T   *in_messages, 
   uint32_t                         in_number_of_messages );

FAR_COS void VSEP_SPI_SCHEDULER_Initialize( void );
//=============================================================================
// SPI_SCHEDULER_Clear
//
// @func Clear scheduler priority queue and disable the scheduler. 
// 
// @rdesc none
//
// @end
//=============================================================================
void VSEP_SPI_SCHEDULER_Clear( void );

//=============================================================================
// SPI_SCHEDULER_Set_Enable
//
// @func Enable or disable sending periodic messages 
// 
// @rdesc bool | The previous state of the scheduler.
// @flag  true | If the scheduler was previously running
// @flag false | If the scheduler was previously disabled
//
// @end
//=============================================================================
FAR_COS bool VSEP_SPI_SCHEDULER_Set_Enable( bool in_enable);

//=============================================================================
// SPI_SCHEDULER_Get_Status
//
// @func Get the state of the SPI scheduler. Is it enabled or disabled? 
// 
// @rdesc bool | The state of the SPI scheduler
// @flag  true | If the scheduler is running 
// @flag false | If the scheduler is disabled
//
// @end
//=============================================================================
bool VSEP_SPI_SCHEDULER_Get_Status( void );

//=============================================================================
// SPI_SCHEDULER_Schedule_Message
//
// @func Adds message objects to the SPI scheduler queue. Only the messages with
//  an interval greater than zero will be added.
//
// @parm SPI_SCHEDULER_Message_T | *in_messages | An array of SPI_SCHEDULER_Message_T
//    message objects. Refer to the SPI_SCHEDULER_Message_Tag structure above.
//
// @parm uint32_t | in_number_of_messages | The number of SPI_SCHEDULER_Message_T objects
//    stored in in_messages.
//
// @rdesc SPI_Scheduler_Status_T | The status of the SPI scheduler queue.
// @flag SPI_SCHEDULER_STATUS_OK | If scheduling was successful
// @flag SPI_SCHEDULER_STATUS_QUEUE_FULL |  If the allocated SPI queue is full
//
// @end
// 
//=============================================================================
SPI_Scheduler_Status_T VSEP_SPI_SCHEDULER_Schedule_Messages( 
   const SPI_SCHEDULER_Message_T   *in_messages, 
   uint32_t                         in_number_of_messages );


//=============================================================================
// SPI_SCHEDULER_Schedule_Message
//
// @func Removes message objects from the SPI scheduler queue. Only the messages with
//  an interval greater than zero will be removed.
//
// @parm SPI_SCHEDULER_Message_T | *in_messages | An array of SPI_SCHEDULER_Message_T
//    message objects. Refer to the SPI_SCHEDULER_Message_Tag structure above.
//
// @parm uint32_t | in_number_of_messages | The number of SPI_SCHEDULER_Message_T objects
//    stored in in_messages.
//
// @rdesc uint32_t | UINT32_MAX if all the messages defined in in_messages where removed,
// otherwise the index of the message not found in the queue.
//
// @end
//=============================================================================
uint32_t VSEP_SPI_SCHEDULER_Clear_Messages(
   const SPI_SCHEDULER_Message_T   *in_messages, 
   uint32_t                         in_number_of_messages );

//=============================================================================
// SPI_SCHEDULER_Schedule_Message
//
// @func Adds a message pointer to the scheduler queue.
//
// @parm SPI_Message_T* | in_message | Pointer to the message definition  
//
// @parm SPI_Scheduler_Time_T | interval | Time interval at which the message 
//    is to repeat
//
// @parm SPI_Scheduler_Time_T | offset | Time after start for first send 
//
// @rdesc SPI_Scheduler_Status_T | The status of the SPI scheduler queue.
// @flag SPI_SCHEDULER_STATUS_OK             |  If scheduling was successful
// @flag SPI_SCHEDULER_STATUS_QUEUE_FULL     |  If the allocated SPI queue is full
//
// @end
// 
//=============================================================================
SPI_Scheduler_Status_T VSEP_SPI_SCHEDULER_Schedule_Message( 
   const SPI_Message_T *in_message,
   SPI_Scheduler_Time_T in_interval,
   SPI_Scheduler_Time_T in_start_time );

//=============================================================================
// SPI_SCHEDULER_Clear_Message
//
// @func Remove a message pointer from the scheduler queue.
//
// @parm SPI_Message_T* | in_message | Pointer to the message definition to remove
// from the priority queue.
//
// @rdesc bool | The status indicating the message was removed successfully.
// @flag true | If scheduling was successful in removing the message from the queue
// @flag false | The message was not found in the scheduler queue.
//
// @end
// 
//=============================================================================
bool VSEP_SPI_SCHEDULER_Clear_Message(
   const SPI_Message_T *in_message );

//=============================================================================
// SPI_SCHEDULER_Service_Scheduler
//
// @func This function must be called at an interval defined by the tick count
// set in interval and offset in the SPI_SCHEDULER_Message_T array and/or the
// interval and start time passed to the SPI_SCHEDULER_Schedule_Message funtion.
//
// @parm  SPI_Scheduler_Time_T | in_time | A tick count defined by 
// interval/offset (SPI_SCHEDULER_Schedule_Messages) and/or by 
// in_interval/in_start_time (SPI_SCHEDULER_Schedule_Message).
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_SPI_SCHEDULER_Service_Scheduler( 
   SPI_Scheduler_Time_T time );



#endif // IO_SPI_SCHEDULER_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

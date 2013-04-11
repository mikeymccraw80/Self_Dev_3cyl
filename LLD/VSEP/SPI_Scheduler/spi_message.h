#ifndef SPI_MESSAGE_H
#define SPI_MESSAGE_H
//=============================================================================
//
//       COPYRIGHT, 2002, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
//===========================================================================*
// %name:            spi_message.h %
//
// created_by:       rskearne
//
// date_created:     Tue Jul 30 13:51:50 2002
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Wed Aug 27 12:44:29 2003 %
//
// %version:         1 %
//
//===========================================================================*
// @doc
//
// @module spi_message.h | Name of Module
//
// The purpose of this module is to 
//
// <nl> Put a brief description here 
// brief description continued
// brief description continued
//
// @normal Copyright <cp> 2001 Delco Electronics , All Rights Reserved
//
// @topic (MODULE) API Overview |  add some kind of overview here
//
// @head3 (MODULE) (What) Configuration Definition |
// @index | (MODULE) & (WHAT) & CONFIG
//
// @head3 (MODULE) (What) API Definition
// @index | (MODULE) & (WHAT) & API
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

#include "io_type.h"

//=============================================================================
// /-----------------------------------------------------------------------\
// | Types for SPI Driver
// \-----------------------------------------------------------------------/
//=============================================================================

typedef enum 
{
   SPI_MESSAGE_STATUS_IDLE,
   SPI_MESSAGE_STATUS_TRANSFERRING,
   SPI_MESSAGE_STATUS_QUEUED_FOR_TRANSFER,
   SPI_MESSAGE_STATUS_ERROR_MESSAGE_REJECTED
} SPI_Message_Status_T;

typedef enum 
{
   SPI_MESSAGE_CLOCK_POLARITY_ACTIVE_LOW,
   SPI_MESSAGE_CLOCK_POLARITY_ACTIVE_HIGH

} SPI_Message_Clock_Polarity_T;

typedef enum 
{
   SPI_MESSAGE_CLOCK_PHASE_LEADING_EDGE,
   SPI_MESSAGE_CLOCK_PHASE_TRAILING_EDGE

} SPI_Message_Clock_Phase_T;

typedef enum 
{
   SPI_MESSAGE_TYPE_SLAVE,
   SPI_MESSAGE_TYPE_MASTER

} SPI_Message_Type_T;

typedef struct SPI_Peripheral_Device_Parameters_Tag
{
   uint16_t                      rate;
   uint16_t                      width;
   uint32_t                      delay_before;
   uint32_t                      delay_after;
   SPI_Message_Clock_Phase_T     phase;
   SPI_Message_Clock_Polarity_T  polarity;
} SPI_Peripheral_Device_Parameters_T;

typedef struct SPI_Peripheral_Device_Mux_Chipselect_Tag
{                        
   HIODEVICE             io_device;
   uint32_t              bit_shifter;
   uint8_t               mux_size;
   uint8_t               chip_select;
   uint8_t               default_chip_select;
} SPI_Peripheral_Device_Mux_Chipselect_T;

typedef struct SPI_Peripheral_Device_Tag
{
   const SPI_Peripheral_Device_Parameters_T       *param;
   const HIODEVICE                                 channel;
   const SPI_Peripheral_Device_Mux_Chipselect_T   *mux_chip_select;
} SPI_Peripheral_Device_T;

typedef struct SPI_Message_Data_Descriptor_Tag
{
   const SPI_Peripheral_Device_T *dev;
   bool                           cont;
} SPI_Message_Data_Descriptor_T;

typedef void* SPI_HClient_T;
/*
typedef struct SPI_Message_Definition_Tag
{
   const SPI_Message_Data_Descriptor_T *descrip;
   void                                *receive_data;
   void                                *transmit_data;
   SPI_Message_Type_T                  ms;
   void                                (*execute_before)( SPI_HClient_T );
   SPI_HClient_T                       execute_before_handle;
   void                                (*execute_after )( SPI_HClient_T );
   SPI_HClient_T                       execute_after_handle;
   uint16_t                            length;
} SPI_Message_Definition_T;
*/
typedef struct SPI_Message_Definition_Tag
{
  // const SPI_Message_Data_Descriptor_T *descrip;
   void                                *receive_data;
   void                                *transmit_data;
   uint8_t					SPI_chip_slect;
   uint16_t                            length_of_receive_message;
    uint16_t                            length_of_transmit_message;
} SPI_Message_Definition_T;

typedef struct SPI_Message_Control_Block_Tag
{
   uint32_t             interval;
   SPI_Message_Status_T status;
   uint32_t             time;
} SPI_Message_Control_Block_T;

typedef struct SPI_Message_Tag
{
   const SPI_Message_Definition_T  *def;
   SPI_Message_Control_Block_T     *cb;
} SPI_Message_T;

#endif // SPI_MESSAGE_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

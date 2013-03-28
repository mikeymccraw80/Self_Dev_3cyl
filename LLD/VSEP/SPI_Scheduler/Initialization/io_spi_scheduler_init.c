//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            io_spi_scheduler_init.c~2:csrc:mt20u2#1 %
//
// created_by:       gzdmlz
//
// date_created:     Mon Aug  7 10:21:24 2006
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Thu Sep  7 16:57:26 2006 %
//
// %version:         2 %
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

//#include "io_config.h"
#include "io_spi_scheduler.h"
#include "io_spi_scheduler_init.h"

//=============================================================================
// SPI_SCHEDULER_QUEUE_SIZE_MAX
//=============================================================================
const uint8_t SPI_SCHEDULER_QUEUE_SIZE_MAX = SPI_SCHEDULER_SCHEDULER_QUEUE_SIZE_MAX_INIT;

//=============================================================================
// SPI_SCHEDULER_START_DELAY
//=============================================================================
const uint8_t SPI_SCHEDULER_START_DELAY    = SPI_SCHEDULER_START_DELAY_INIT;

//=============================================================================
// SPI_SCHEDULER_Priority_Queue
//=============================================================================
const SPI_Message_T *SPI_SCHEDULER_Priority_Queue[ SPI_SCHEDULER_SCHEDULER_QUEUE_SIZE_MAX_INIT ];
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

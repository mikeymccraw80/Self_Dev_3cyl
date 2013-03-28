#ifndef IO_SPI_CONFIG_H
#define IO_SPI_CONFIG_H
//=============================================================================
//
//       COPYRIGHT, 2000, DELPHI DELCO ELECTRONICS SYSTEMS CORPORATION
//
//===========================================================================*
// %name:            io_spi_config.h %
//
// created_by:       rskearne
//
// date_created:     Tue Aug 13 11:05:25 2002
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Thursday, March 15, 2007 4:55:30 PM %
//
// %version:         1 %
//
//===========================================================================*
// SPECIFICATION REVISION:
//
//===========================================================================*
// REUSE:
// none
//
//=============================================================================
#include "io_spi_scheduler.h"

extern const SPI_SCHEDULER_Message_T SPI_SCHEDULER_Message[];
extern const uint32_t SPI_SCHEDULER_Message_Numberof;
extern uint32_t ADConversion_Time;
extern bool ADConversion_Error;
extern FAR_COS void VSEP_SPI_Scheduler_Manage_Periodic( void );
#endif /* IO_SPI_CONFIG_H */
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

//=============================================================================
//
//       COPYRIGHT, 2000, DELPHI DELCO ELECTRONICS SYSTEMS CORPORATION
//
//===========================================================================*
// %name:            io_spi_config.c %
//
// created_by:       rskearne
//
// date_created:     Tue Aug 13 11:05:21 2002
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Tuesday, April 17, 2007 8:52:25 AM %
//
// %version:         5 %
//
//===========================================================================*
//
// SPECIFICATION REVISION:
//
//===========================================================================*
// REUSE:
// none
//
//=============================================================================

#include "io_spi_config.h"
#include "io_spi_timing.h"
#include "io_spi_scheduler.h"
#include "dd_vsep.h"
#include "dd_vsep_pwm.h"

extern const SPI_Message_T VSEP_MESSAGE[ NUMBER_OF_VSEP ][VSEP_MESSAGE_MAX];
extern const SPI_Message_T VSEP_HWTEST_INIT_MESSAGE;
extern const SPI_Message_T VSEP_CFG_MESSAGE;
 #ifdef VSEP_MORE
extern const SPI_Message_T HFPS_CTRL_MESSAGE;
extern const SPI_Message_T HFPS_LPC_MESSAGE;
extern const SPI_Message_T HFPS_COP_MESSAGE;
#endif
//************************************************************************
//*                         Schedule SPI Messages                          
//************************************************************************
const SPI_SCHEDULER_Message_T SPI_SCHEDULER_Message[] =
{
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_SOH_STATUS],  VSEP_SOH_STATUS_OFFSET,   VSEP_SOH_STATUS_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_PWM+0],       VSEP_PWM_OFFSET(1),       VSEP_PWM_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_PWM+1],       VSEP_PWM_OFFSET(2),       VSEP_PWM_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_PWM+2],       VSEP_PWM_OFFSET(3),       VSEP_PWM_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_PWM+3],       VSEP_PWM_OFFSET(4),       VSEP_PWM_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_PWM+4],       VSEP_PWM_OFFSET(5),       VSEP_PWM_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_PWM+5],       VSEP_PWM_OFFSET(6),       VSEP_PWM_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_PWM+6],       VSEP_PWM_OFFSET(7),       VSEP_PWM_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_PWM+7],       VSEP_PWM_OFFSET(8),       VSEP_PWM_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_PCH_MPIO],    VSEP_PCH_OFFSET,          VSEP_PCH_INTERVAL    },
   {     &VSEP_MESSAGE[0][VSEP_MESSAGE_FAULT],       VSEP_FAULT_OFFSET,        VSEP_FAULT_INTERVAL  }
}; 

const uint32_t SPI_SCHEDULER_Message_Numberof = sizeof( SPI_SCHEDULER_Message )/sizeof( SPI_SCHEDULER_Message_T);

static SPI_Scheduler_Time_T SPI_SCHEDULER_Timer = 0;
uint32_t ADConversion_Time;
bool ADConversion_Error;

//=============================================================================
// SPI_Scheduler_Manage_Periodic
//
// @func Put pointer in last slot of queue, bubble it up
//
// @rdesc status of the message
//
// @end
//=============================================================================
void VSEP_SPI_Scheduler_Manage_Periodic( void )//excute per 7.8ms/10ms
{
	VSEP_SPI_SCHEDULER_Service_Scheduler( SPI_SCHEDULER_Timer++ );
}

/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

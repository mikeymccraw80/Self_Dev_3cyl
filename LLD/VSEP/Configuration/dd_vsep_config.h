#ifndef DD_VSEP_CONFIG_H
#define DD_VSEP_CONFIG_H
//=============================================================================
//
//       COPYRIGHT, 2003, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_vsep_config.h %
//
// created_by:       fz3pdz
//
// date_created:     Thu Aug 25 08:09:59 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Oct 21 06:27:33 2005 %
//
// %version:         6 %
//
//=============================================================================
#include "reuse.h"
#include "io_type.h"
#include "spi_message.h"

#define VSEP_DEPS_STATIC_INITIALIZATION
#define VSEP_DISCRETE_STATIC_INITIALIZATION
#define VSEP_EST_DIAGNOSTIC_DEBUG
#define VSEP_EST_SELECT_STATIC_INITIALIZATION
#define VSEP_PWM_STATIC_INITIALIZATION
#define VSEP_VR_STATIC_INITIALIZATION
//#define VSEP_CALIBRATION_ENABLE



#define NUMBER_OF_VSEP (1)

extern  FAR_COS void VSEP_Fault_Task_7_8ms( void );
extern const SPI_Message_Definition_T VSEP_HWTEST_INIT_MESSAGE_DEFINITION[ NUMBER_OF_VSEP ];






#endif // DD_VSEP_CONFIG_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        mm/dd/yy By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       *
 *
 * 5.0  272        08/11/24 sjl Add configurable calibrations for discrete inputs 
 *
\*===========================================================================*/

#ifndef DD_L9958_CONFIG_H
#define DD_L9958_CONFIG_H
//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958_config.h %
//
// created_by:       fz3pdz
//
// date_created:     Thu Apr 27 08:50:43 2005
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Wed Feb 28 10:09:36 2007 %
//
// %version:         mt20u2#2 %
//
//=============================================================================
//
// Configuration macros

#include "io_type.h"
#include "dd_l9958_txd.h"

#define MTSA_USE_BITS_MACRO

#define NUMBER_OF_L9958 (1)

void L9958_SPI_Immediate_Transfer(L9958_Txd_Message_T in_msg_index);

#endif // DD_L9958_CONFIG_H

#ifndef DD_VSEP_LED_H
#define DD_VSEP_LED_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_discrete.h~4:incl:mt20u2#2 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:42 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 11:58:39 2007 %
//
// %version:         4 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================
#include "reuse.h"
#include "dd_vsep.h"

#define NUMBER_OF_VSEP (1)


typedef enum
{
                                                         // [ 6: 0] Reserved
   VSEP_LEDMODE_CONFIGURATION_POSITION_ENABLE      = 7   //      7  LEDMODE Enable

}VSEP_LEDMODE_Configuration_Position_T;

typedef enum
{
                                                         // [ 6: 0] Reserved
   VSEP_LEDMODE_CONFIGURATION_WIDTH_ENABLE         = 1   //      7  LEDMODE Enable

}VSEP_LEDMODE_Configuration_Width_T;


typedef enum
{
   VSEP_LEDMODE_25,
   VSEP_LEDMODE_26,
   VSEP_LEDMODE_30,
   VSEP_LEDMODE_CHANNEL_MAX,
   VSEP_LEDMODE_ALL_CHANNEL
}VSEP_LEDMODE_Channel_T;

typedef enum
{
   VSEP_LEDMODE_DISABLE = 0,
   VSEP_LEDMODE_ENABLE = 1,
   VSEP_LEDMODE_ALL_CHANNEL_ENABLE = 0x07,
   VSEP_LEDMODE_ALL_CHANNEL_DISABLE = 0x00
}VSEP_LEDMODE_T;

#define VSEP_LEDMODE_Set_Enable( configuration, enable ) \
   (IO_Configuration_T)(Insert_Bits( configuration, enable, VSEP_LEDMODE_CONFIGURATION_POSITION_ENABLE, VSEP_LEDMODE_CONFIGURATION_WIDTH_ENABLE ) )

#define VSEP_LEDMODE_Get_Enable( configuration ) \
   (VSEP_LEDMODE_T)(Extract_Bits( configuration, VSEP_LEDMODE_CONFIGURATION_POSITION_ENABLE, VSEP_LEDMODE_CONFIGURATION_WIDTH_ENABLE ) )

typedef enum
{
   VSEP_LEDMODE_TXD_MESSAGE_CTRL,
   VSEP_LEDMODE_TXD_MESSAGE_ENABLE,
   VSEP_LEDMODE_TXD_MESSAGE_MAX
}VSEP_LEDMODE_Txd_Message_T;

extern uint16_t VSEP_LEDMODE_Txd[VSEP_LEDMODE_TXD_MESSAGE_MAX];

//=============================================================================
// VSEP_LEDMODE_Initialize_Device
//=============================================================================
void VSEP_LEDMODE_Initialize_Device(void);

//=============================================================================
// VSEP_LEDMODE_Set_Channel
//=============================================================================
void VSEP_LEDMODE_Set_Channel( 
   IO_Configuration_T in_configuration,
   VSEP_LEDMODE_Channel_T in_group, 
   uint32_t in_ledmode );

//=============================================================================
// VSEP_LEDMODE_Get_Channel
//=============================================================================
uint32_t VSEP_LEDMODE_Get_Channel(IO_Configuration_T in_configuration,
   VSEP_LEDMODE_Channel_T in_group );



#endif // DD_VSEP_LED_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       *
\*===========================================================================*/

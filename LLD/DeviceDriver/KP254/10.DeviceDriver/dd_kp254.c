//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:        %
//
// %version:         1.1.1 %
//
//=============================================================================
#include "dd_kp254.h"

//=============================================================================
// KP254_Get_Identifier
//=============================================================================
uint16_t KP254_Get_Identifier(
   IO_Configuration_T in_configuration )
{
    KP254_Index_T   index     = KP254_Get_Device_Index( in_configuration );
    KP254_SPI_Immediate_Transfer( in_configuration, KP254_MESSAGE_ACQ_ID);
    return KP254_ID_Rxd[index];
}

//=============================================================================
// KP254_Initialize_Device
//=============================================================================
void KP254_Initialize_Device(
   IO_Configuration_T in_configuration )
{
   KP254_Index_T          index     =   KP254_Get_Device_Index( in_configuration );

   if( index < KP254_INDEX_MAX )
   {
       KP254_ACQ_Pressure_Txd[index]    =   KP254_Msg_Set_Request(0,KP254_ACQUIRE_PRESSURE)      |\
                                            KP254_Msg_Set_Reset_Strategy(0,KP254_DONT_RESET_FAILURES) |\
                                            KP254_Msg_Set_Additional_Req(0,0);
       KP254_ACQ_Temperature_Txd[index] =   KP254_Msg_Set_Request(0,KP254_ACQUIRE_TEMPERATURE)   |\
                                            KP254_Msg_Set_Reset_Strategy(0,KP254_DONT_RESET_FAILURES) |\
                                            KP254_Msg_Set_Additional_Req(0,0);
       KP254_Trigger_DIAG_Txd[index]    =   KP254_Msg_Set_Request(0,KP254_TRIGGER_DIAGNOSIS)     |\
                                            KP254_Msg_Set_Reset_Strategy(0,KP254_DONT_RESET_FAILURES) |\
                                            KP254_Msg_Set_Additional_Req(0,0);
       KP254_ACQ_ID_Txd[index]          =   KP254_Msg_Set_Request(0,KP254_ACQUIRE_IDENTIFIER)    |\
                                            KP254_Msg_Set_Reset_Strategy(0,KP254_DONT_RESET_FAILURES) |\
                                            KP254_Msg_Set_Additional_Req(0,0);
   }
}


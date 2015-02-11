//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254_analog.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      zzrfyj %
//
// %date_modified:        %
//
// %version:         2 %
//
//=============================================================================

#include "dd_kp254.h"



//=============================================================================
// KP254_ANALOG_Get_Buffered_Value
//=============================================================================
uint16_t KP254_ANALOG_Get_Buffered_Value(
   IO_Configuration_T in_configuration )
{
    KP254_Index_T   index     = KP254_Get_Device_Index( in_configuration );
    KP254_Message_T message   = KP254_Get_Message( in_configuration );
    uint16_t        result = 0;

    switch(message)
    {
        case KP254_MESSAGE_ACQ_PRESSURE:
            result = KP254_Get_Rxd_Data(KP254_Pressure_Rxd[index]);
            break;
        case KP254_MESSAGE_ACQ_TEMPERATURE:
            result = KP254_Get_Rxd_Data(KP254_Temperature_Rxd[index]);
            break;
        default:
            break;
    }
    // justify result from 10 bits to 16 bits
    return (result<<6);
}



//=============================================================================
// KP254_ANALOG_Get_Immediate_Value
//=============================================================================
uint16_t KP254_ANALOG_Get_Immediate_Value( 
   IO_Configuration_T in_configuration )
{
    KP254_Message_T message   = KP254_Get_Message( in_configuration );
    // flush the command stack, or it will get the last command's response
    KP254_SPI_Immediate_Transfer( in_configuration, message);
    KP254_SPI_Immediate_Transfer( in_configuration, message);
    return KP254_ANALOG_Get_Buffered_Value(in_configuration);
}

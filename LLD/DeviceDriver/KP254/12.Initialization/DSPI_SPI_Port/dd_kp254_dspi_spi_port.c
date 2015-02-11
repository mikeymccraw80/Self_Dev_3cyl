//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254_dspi_spi_port.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      zzrfyj %
//
// %date_modified:       %
//
// %version:         1 %
//
//=============================================================================
#include "dd_dspi_spi_port.h"
#include "dd_kp254.h"


DSPI_SPI_PORT_DECLARE_DEVICE_MESSAGES( KP254, KP254_MESSAGE_MAX )
//=============================================================================
// KP254_SPI_Immediate_Transfer
//=============================================================================
bool KP254_SPI_Immediate_Transfer (
     IO_Configuration_T  in_configuration,
     KP254_Message_T       in_kp254_message )
{
   KP254_Index_T        index            = KP254_Get_Device_Index( in_configuration );

   SPI_Port_Status_T   transfer_status = SPIPort_Transfer_Immediate( DSPI_SPI_PORT_USE_DEVICE_MESSAGES(KP254,index,in_kp254_message)->port,
                                                    DSPI_SPI_PORT_USE_DEVICE_MESSAGES(KP254,index,in_kp254_message) );
   return ((bool)( SPI_PORT_STATUS_SUCCESSFUL == transfer_status )? true:false);
}

//=============================================================================
// KP254_SPI_Transfer
//=============================================================================
bool KP254_SPI_Transfer (
     IO_Configuration_T  in_configuration,
     KP254_Message_T       in_kp254_message )
{
   KP254_Index_T        index            = KP254_Get_Device_Index( in_configuration );

   SPI_Port_Status_T   transfer_status  = SPIPort_Transfer( DSPI_SPI_PORT_USE_DEVICE_MESSAGES(KP254,index,in_kp254_message)->port,
                                                    DSPI_SPI_PORT_USE_DEVICE_MESSAGES(KP254,index,in_kp254_message) );
   return ((bool)( SPI_PORT_STATUS_SUCCESSFUL == transfer_status )? true:false);
}

#ifndef DD_KP254_DSPI_SPI_PORT_INIT_H
#define DD_KP254_DSPI_SPI_PORT_INIT_H

//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254_dspi_spi_port_init.h %
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

#ifndef NUMBER_OF_KP254
#error Must define "NUMBER_OF_KP254" macro in dd_kp254_config.h to number of KP254 in the system
#endif

//=============================================================================
// @KP254 Chipselects Error message
//=============================================================================
#ifndef KP254_SPI_CTAR_INIT_0
#error Must define "KP254_SPI_CTAR_INIT_0" macro to assign to an item DSPI_PUSHR_DSICR_CTAS_T
#endif

#if (NUMBER_OF_KP254 > 1 )
#ifndef KP254_SPI_CTAR_INIT_1
#error Must define KP254_SPI_CTAR_INIT_1 macro to assign to an item DSPI_PUSHR_DSICR_CTAS_T
#endif
#endif

//=============================================================================
// @KP254 SPI Port Error message
//=============================================================================
#ifndef KP254_SPI_CHANNEL_INIT_0
#error Must define "KP254_SPI_CHANNEL_INIT_0" macro assign to IO_SPI_Port_T to KP254 spi channel
#endif

#if (NUMBER_OF_KP254 > 1 )
#ifndef KP254_SPI_CHANNEL_INIT_1
#error Must define KP254_SPI_CHANNEL_INIT_1 macro assign to IO_SPI_Port_T to KP254 spi channel
#endif
#endif

//=============================================================================
// @KP254 ACQ_Pressure Callbacks 
//=============================================================================
#ifndef KP254_ACQ_Pressure_BEFORE_FUNCTION_INIT_0
#define KP254_ACQ_Pressure_BEFORE_FUNCTION_INIT_0 (0)
#endif
#ifndef KP254_ACQ_Pressure_BEFORE_CONTEXT_INIT_0
#define KP254_ACQ_Pressure_BEFORE_CONTEXT_INIT_0 (0)
#endif
#ifndef KP254_ACQ_Pressure_AFTER_FUNCTION_INIT_0
#define KP254_ACQ_Pressure_AFTER_FUNCTION_INIT_0 (0)
#endif
#ifndef KP254_ACQ_Pressure_AFTER_CONTEXT_INIT_0
#define KP254_ACQ_Pressure_AFTER_CONTEXT_INIT_0 (0)
#endif

#if (NUMBER_OF_KP254 > 1 )
#ifndef KP254_ACQ_Pressure_BEFORE_FUNCTION_INIT_1
#define KP254_ACQ_Pressure_BEFORE_FUNCTION_INIT_1 (0)
#endif
#ifndef KP254_ACQ_Pressure_BEFORE_CONTEXT_INIT_1
#define KP254_ACQ_Pressure_BEFORE_CONTEXT_INIT_1 (0)
#endif
#ifndef KP254_ACQ_Pressure_AFTER_FUNCTION_INIT_1
#define KP254_ACQ_Pressure_AFTER_FUNCTION_INIT_1 (0)
#endif
#ifndef KP254_ACQ_Pressure_AFTER_CONTEXT_INIT_1
#define KP254_ACQ_Pressure_AFTER_CONTEXT_INIT_1 (0)
#endif
#endif

//=============================================================================
// @KP254 ACQ_Temperature Callbacks 
//=============================================================================
#ifndef KP254_ACQ_Temperature_BEFORE_FUNCTION_INIT_0
#define KP254_ACQ_Temperature_BEFORE_FUNCTION_INIT_0 (0)
#endif
#ifndef KP254_ACQ_Temperature_BEFORE_CONTEXT_INIT_0
#define KP254_ACQ_Temperature_BEFORE_CONTEXT_INIT_0 (0)
#endif
#ifndef KP254_ACQ_Temperature_AFTER_FUNCTION_INIT_0
#define KP254_ACQ_Temperature_AFTER_FUNCTION_INIT_0 (0)
#endif
#ifndef KP254_ACQ_Temperature_AFTER_CONTEXT_INIT_0
#define KP254_ACQ_Temperature_AFTER_CONTEXT_INIT_0 (0)
#endif

#if (NUMBER_OF_KP254 > 1 )
#ifndef KP254_ACQ_Temperature_BEFORE_FUNCTION_INIT_1
#define KP254_ACQ_Temperature_BEFORE_FUNCTION_INIT_1 (0)
#endif
#ifndef KP254_ACQ_Temperature_BEFORE_CONTEXT_INIT_1
#define KP254_ACQ_Temperature_BEFORE_CONTEXT_INIT_1 (0)
#endif
#ifndef KP254_ACQ_Temperature_AFTER_FUNCTION_INIT_1
#define KP254_ACQ_Temperature_AFTER_FUNCTION_INIT_1 (0)
#endif
#ifndef KP254_ACQ_Temperature_AFTER_CONTEXT_INIT_1
#define KP254_ACQ_Temperature_AFTER_CONTEXT_INIT_1 (0)
#endif
#endif

//=============================================================================
// @KP254 Trigger_DIAG Callbacks 
//=============================================================================
#ifndef KP254_Trigger_DIAG_BEFORE_FUNCTION_INIT_0
#define KP254_Trigger_DIAG_BEFORE_FUNCTION_INIT_0 (0)
#endif
#ifndef KP254_Trigger_DIAG_BEFORE_CONTEXT_INIT_0
#define KP254_Trigger_DIAG_BEFORE_CONTEXT_INIT_0 (0)
#endif
#ifndef KP254_Trigger_DIAG_AFTER_FUNCTION_INIT_0
#define KP254_Trigger_DIAG_AFTER_FUNCTION_INIT_0 (0)
#endif
#ifndef KP254_Trigger_DIAG_AFTER_CONTEXT_INIT_0
#define KP254_Trigger_DIAG_AFTER_CONTEXT_INIT_0 (0)
#endif

#if (NUMBER_OF_KP254 > 1 )
#ifndef KP254_Trigger_DIAG_BEFORE_FUNCTION_INIT_1
#define KP254_Trigger_DIAG_BEFORE_FUNCTION_INIT_1 (0)
#endif
#ifndef KP254_Trigger_DIAG_BEFORE_CONTEXT_INIT_1
#define KP254_Trigger_DIAG_BEFORE_CONTEXT_INIT_1 (0)
#endif
#ifndef KP254_Trigger_DIAG_AFTER_FUNCTION_INIT_1
#define KP254_Trigger_DIAG_AFTER_FUNCTION_INIT_1 (0)
#endif
#ifndef KP254_Trigger_DIAG_AFTER_CONTEXT_INIT_1
#define KP254_Trigger_DIAG_AFTER_CONTEXT_INIT_1 (0)
#endif
#endif

//=============================================================================
// @KP254 ACQ_ID Callbacks 
//=============================================================================
#ifndef KP254_ACQ_ID_BEFORE_FUNCTION_INIT_0
#define KP254_ACQ_ID_BEFORE_FUNCTION_INIT_0 (0)
#endif
#ifndef KP254_ACQ_ID_BEFORE_CONTEXT_INIT_0
#define KP254_ACQ_ID_BEFORE_CONTEXT_INIT_0 (0)
#endif
#ifndef KP254_ACQ_ID_AFTER_FUNCTION_INIT_0
#define KP254_ACQ_ID_AFTER_FUNCTION_INIT_0 (0)
#endif
#ifndef KP254_ACQ_ID_AFTER_CONTEXT_INIT_0
#define KP254_ACQ_ID_AFTER_CONTEXT_INIT_0 (0)
#endif

#if (NUMBER_OF_KP254 > 1 )
#ifndef KP254_ACQ_ID_BEFORE_FUNCTION_INIT_1
#define KP254_ACQ_ID_BEFORE_FUNCTION_INIT_1 (0)
#endif
#ifndef KP254_ACQ_ID_BEFORE_CONTEXT_INIT_1
#define KP254_ACQ_ID_BEFORE_CONTEXT_INIT_1 (0)
#endif
#ifndef KP254_ACQ_ID_AFTER_FUNCTION_INIT_1
#define KP254_ACQ_ID_AFTER_FUNCTION_INIT_1 (0)
#endif
#ifndef KP254_ACQ_ID_AFTER_CONTEXT_INIT_1
#define KP254_ACQ_ID_AFTER_CONTEXT_INIT_1 (0)
#endif
#endif











#endif /* end of include guard: DD_KP254_DSPI_SPI_PORT_INIT_H */

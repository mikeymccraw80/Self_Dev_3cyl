//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254_dspi_spi_port_init.c %
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
#include "io_config.h"
#include "io.h"
#include "dd_kp254.h"
#include "dd_dspi_spi_port.h"
#include "dd_kp254_dspi_spi_port_init.h"

#define KP254_IS8BIT (0)

//=============================================================================
// KP254 Acquire pressure PUSHR
//=============================================================================
DSPI_PUSHR_DEFINITION_BEGIN(KP254,ACQ_Pressure,sizeof(KP254_ACQ_Pressure_Txd[KP254_INDEX_0])/sizeof(uint16_t) )
   DSPI_PUSHR_TRANSFER_START_END(KP254_SPI_CTAR_INIT_0, KP254_SPI_PCx_INIT_0 )
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_PUSHR_TRANSFER_START_END(KP254_SPI_CTAR_INIT_1, KP254_SPI_PCx_INIT_1 )
#endif
DSPI_PUSHR_END_DEFINITION

//=============================================================================
// KP254 Acquire temperature PUSHR
//=============================================================================
DSPI_PUSHR_DEFINITION_BEGIN(KP254,ACQ_Temperature,sizeof(KP254_ACQ_Temperature_Txd[KP254_INDEX_0])/sizeof(uint16_t) )
   DSPI_PUSHR_TRANSFER_START_END(KP254_SPI_CTAR_INIT_0, KP254_SPI_PCx_INIT_0 )
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_PUSHR_TRANSFER_START_END(KP254_SPI_CTAR_INIT_1, KP254_SPI_PCx_INIT_1 )
#endif
DSPI_PUSHR_END_DEFINITION

//=============================================================================
// KP254 trigger diagnosis PUSHR
//=============================================================================
DSPI_PUSHR_DEFINITION_BEGIN(KP254,Trigger_DIAG,sizeof(KP254_Trigger_DIAG_Txd[KP254_INDEX_0])/sizeof(uint16_t) )
   DSPI_PUSHR_TRANSFER_START_END(KP254_SPI_CTAR_INIT_0, KP254_SPI_PCx_INIT_0 )
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_PUSHR_TRANSFER_START_END(KP254_SPI_CTAR_INIT_1, KP254_SPI_PCx_INIT_1 )
#endif
DSPI_PUSHR_END_DEFINITION

//=============================================================================
// KP254 Acquire identifier PUSHR
//=============================================================================
DSPI_PUSHR_DEFINITION_BEGIN(KP254,ACQ_ID,sizeof(KP254_ACQ_ID_Txd[KP254_INDEX_0])/sizeof(uint16_t) )
   DSPI_PUSHR_TRANSFER_START_END(KP254_SPI_CTAR_INIT_0, KP254_SPI_PCx_INIT_0 )
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_PUSHR_TRANSFER_START_END(KP254_SPI_CTAR_INIT_1, KP254_SPI_PCx_INIT_1 )
#endif
DSPI_PUSHR_END_DEFINITION

//=============================================================================
// KP254 acquire pressure Message Descriptor
//=============================================================================
DSPI_SPI_PORT_BEGIN_MESSAGE_DEFINITION(KP254, ACQ_Pressure )
   DSPI_SPI_PORT_MESSAGE_DEFINITION( KP254,
                                     ACQ_Pressure,
                                     KP254_INDEX_0,
                                     &KP254_ACQ_Pressure_Txd[KP254_INDEX_0],
                                     &KP254_Pressure_Rxd[KP254_INDEX_0],
                                     SPI_MESSAGE_TYPE_MASTER,
                                     DSPI_SPI_PORT_PUSHR_NAME(KP254,ACQ_Pressure),
                                     KP254_IS8BIT,
                                     DSPI_SPI_PORT_BEFORE_FUNCTION_NAME(KP254,ACQ_Pressure, 0),
                                     DSPI_SPI_PORT_BEFORE_CONTEXT_NAME(KP254,ACQ_Pressure, 0),
                                     DSPI_SPI_PORT_AFTER_FUNCTION_NAME(KP254,ACQ_Pressure, 0),
                                     DSPI_SPI_PORT_AFTER_CONTEXT_NAME(KP254,ACQ_Pressure, 0))
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_SPI_PORT_MESSAGE_DEFINITION( KP254,
                                     ACQ_Pressure,
                                     KP254_INDEX_1,
                                     &KP254_ACQ_Pressure_Txd[KP254_INDEX_1],
                                     &KP254_Pressure_Rxd[KP254_INDEX_1],
                                     SPI_MESSAGE_TYPE_MASTER,
                                     DSPI_SPI_PORT_PUSHR_NAME(KP254,ACQ_Pressure),
                                     KP254_IS8BIT,
                                     DSPI_SPI_PORT_BEFORE_FUNCTION_NAME(KP254,ACQ_Pressure, 1),
                                     DSPI_SPI_PORT_BEFORE_CONTEXT_NAME(KP254,ACQ_Pressure, 1),
                                     DSPI_SPI_PORT_AFTER_FUNCTION_NAME(KP254,ACQ_Pressure, 1),
                                     DSPI_SPI_PORT_AFTER_CONTEXT_NAME(KP254,ACQ_Pressure, 1))
#endif
DSPI_SPI_PORT_END_MESSAGE_DEFINITION

//=============================================================================
// KP254 acquire temperature Message Descriptor
//=============================================================================
DSPI_SPI_PORT_BEGIN_MESSAGE_DEFINITION(KP254, ACQ_Temperature )
   DSPI_SPI_PORT_MESSAGE_DEFINITION( KP254,
                                     ACQ_Temperature,
                                     KP254_INDEX_0,
                                     &KP254_ACQ_Temperature_Txd[KP254_INDEX_0],
                                     &KP254_Temperature_Rxd[KP254_INDEX_0],
                                     SPI_MESSAGE_TYPE_MASTER,
                                     DSPI_SPI_PORT_PUSHR_NAME(KP254,ACQ_Temperature),
                                     KP254_IS8BIT,
                                     DSPI_SPI_PORT_BEFORE_FUNCTION_NAME(KP254,ACQ_Temperature, 0),
                                     DSPI_SPI_PORT_BEFORE_CONTEXT_NAME(KP254,ACQ_Temperature, 0),
                                     DSPI_SPI_PORT_AFTER_FUNCTION_NAME(KP254,ACQ_Temperature, 0),
                                     DSPI_SPI_PORT_AFTER_CONTEXT_NAME(KP254,ACQ_Temperature, 0))
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_SPI_PORT_MESSAGE_DEFINITION( KP254,
                                     ACQ_Temperature,
                                     KP254_INDEX_1,
                                     &KP254_ACQ_Temperature_Txd[KP254_INDEX_1],
                                     &KP254_Temperature_Rxd[KP254_INDEX_1],
                                     SPI_MESSAGE_TYPE_MASTER,
                                     DSPI_SPI_PORT_PUSHR_NAME(KP254,ACQ_Temperature),
                                     KP254_IS8BIT,
                                     DSPI_SPI_PORT_BEFORE_FUNCTION_NAME(KP254,ACQ_Temperature, 1),
                                     DSPI_SPI_PORT_BEFORE_CONTEXT_NAME(KP254,ACQ_Temperature, 1),
                                     DSPI_SPI_PORT_AFTER_FUNCTION_NAME(KP254,ACQ_Temperature, 1),
                                     DSPI_SPI_PORT_AFTER_CONTEXT_NAME(KP254,ACQ_Temperature, 1))
#endif
DSPI_SPI_PORT_END_MESSAGE_DEFINITION

//=============================================================================
// KP254 trigger diagnosis Message Descriptor
//=============================================================================
DSPI_SPI_PORT_BEGIN_MESSAGE_DEFINITION(KP254, Trigger_DIAG )
   DSPI_SPI_PORT_MESSAGE_DEFINITION( KP254,
                                     Trigger_DIAG,
                                     KP254_INDEX_0,
                                     &KP254_Trigger_DIAG_Txd[KP254_INDEX_0],
                                     &KP254_DIAG_Rxd[KP254_INDEX_0],
                                     SPI_MESSAGE_TYPE_MASTER,
                                     DSPI_SPI_PORT_PUSHR_NAME(KP254,Trigger_DIAG),
                                     KP254_IS8BIT,
                                     DSPI_SPI_PORT_BEFORE_FUNCTION_NAME(KP254,Trigger_DIAG, 0),
                                     DSPI_SPI_PORT_BEFORE_CONTEXT_NAME(KP254,Trigger_DIAG, 0),
                                     DSPI_SPI_PORT_AFTER_FUNCTION_NAME(KP254,Trigger_DIAG, 0),
                                     DSPI_SPI_PORT_AFTER_CONTEXT_NAME(KP254,Trigger_DIAG, 0))
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_MESSAGE_DEFINITION( KP254,
                                     Trigger_DIAG,
                                     KP254_INDEX_1,
                                     &KP254_Trigger_DIAG_Txd[KP254_INDEX_1],
                                     &KP254_DIAG_Rxd[KP254_INDEX_1],
                                     SPI_MESSAGE_TYPE_MASTER,
                                     DSPI_SPI_PORT_PUSHR_NAME(KP254,Trigger_DIAG),
                                     KP254_IS8BIT,
                                     DSPI_SPI_PORT_BEFORE_FUNCTION_NAME(KP254,Trigger_DIAG, 1),
                                     DSPI_SPI_PORT_BEFORE_CONTEXT_NAME(KP254,Trigger_DIAG, 1),
                                     DSPI_SPI_PORT_AFTER_FUNCTION_NAME(KP254,Trigger_DIAG, 1),
                                     DSPI_SPI_PORT_AFTER_CONTEXT_NAME(KP254,Trigger_DIAG, 1))
   DSPI_SPI_PORT_SEPERATOR
#endif
DSPI_SPI_PORT_END_MESSAGE_DEFINITION

//=============================================================================
// KP254 acquire identifier Message Descriptor
//=============================================================================
DSPI_SPI_PORT_BEGIN_MESSAGE_DEFINITION(KP254, ACQ_ID )
   DSPI_SPI_PORT_MESSAGE_DEFINITION( KP254,
                                     ACQ_ID,
                                     KP254_INDEX_0,
                                     &KP254_ACQ_ID_Txd[KP254_INDEX_0],
                                     &KP254_ID_Rxd[KP254_INDEX_0],
                                     SPI_MESSAGE_TYPE_MASTER,
                                     DSPI_SPI_PORT_PUSHR_NAME(KP254,ACQ_ID),
                                     KP254_IS8BIT,
                                     DSPI_SPI_PORT_BEFORE_FUNCTION_NAME(KP254,ACQ_ID, 0),
                                     DSPI_SPI_PORT_BEFORE_CONTEXT_NAME(KP254,ACQ_ID, 0),
                                     DSPI_SPI_PORT_AFTER_FUNCTION_NAME(KP254,ACQ_ID, 0),
                                     DSPI_SPI_PORT_AFTER_CONTEXT_NAME(KP254,ACQ_ID, 0))
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_SPI_PORT_MESSAGE_DEFINITION( KP254,
                                     ACQ_ID,
                                     KP254_INDEX_1,
                                     &KP254_ACQ_ID_Txd[KP254_INDEX_1],
                                     &KP254_ID_Rxd[KP254_INDEX_1],
                                     SPI_MESSAGE_TYPE_MASTER,
                                     DSPI_SPI_PORT_PUSHR_NAME(KP254,ACQ_ID),
                                     KP254_IS8BIT,
                                     DSPI_SPI_PORT_BEFORE_FUNCTION_NAME(KP254,ACQ_ID, 1),
                                     DSPI_SPI_PORT_BEFORE_CONTEXT_NAME(KP254,ACQ_ID, 1),
                                     DSPI_SPI_PORT_AFTER_FUNCTION_NAME(KP254,ACQ_ID, 1),
                                     DSPI_SPI_PORT_AFTER_CONTEXT_NAME(KP254,ACQ_ID, 1))
#endif
DSPI_SPI_PORT_END_MESSAGE_DEFINITION

//=============================================================================
// KP254 acquire pressure Message
//=============================================================================
DSPI_SPI_PORT_BEGIN_KINDS_OF_MESSAGE( KP254, ACQ_Pressure )
   DSPI_SPI_PORT_KINDS_OF_MESSAGE(KP254, ACQ_Pressure, KP254_INDEX_0,KP254_SPI_CHANNEL_INIT_0)
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_SPI_PORT_KINDS_OF_MESSAGE(KP254, ACQ_Pressure, KP254_INDEX_1,KP254_SPI_CHANNEL_INIT_1)
#endif
DSPI_SPI_PORT_END_KINDS_OF_MESSAGE

//=============================================================================
// KP254 acquire temperature Message
//=============================================================================
DSPI_SPI_PORT_BEGIN_KINDS_OF_MESSAGE( KP254, ACQ_Temperature )
   DSPI_SPI_PORT_KINDS_OF_MESSAGE(KP254, ACQ_Temperature, KP254_INDEX_0,KP254_SPI_CHANNEL_INIT_0)
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_SPI_PORT_KINDS_OF_MESSAGE(KP254, ACQ_Temperature, KP254_INDEX_1,KP254_SPI_CHANNEL_INIT_1)
#endif
DSPI_SPI_PORT_END_KINDS_OF_MESSAGE

//=============================================================================
// KP254 trigger diagnosis Message
//=============================================================================
DSPI_SPI_PORT_BEGIN_KINDS_OF_MESSAGE( KP254, Trigger_DIAG )
   DSPI_SPI_PORT_KINDS_OF_MESSAGE(KP254, Trigger_DIAG, KP254_INDEX_0,KP254_SPI_CHANNEL_INIT_0)
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_SPI_PORT_KINDS_OF_MESSAGE(KP254, Trigger_DIAG, KP254_INDEX_1,KP254_SPI_CHANNEL_INIT_1)
#endif
DSPI_SPI_PORT_END_KINDS_OF_MESSAGE

//=============================================================================
// KP254 acquire identifier Message
//=============================================================================
DSPI_SPI_PORT_BEGIN_KINDS_OF_MESSAGE( KP254, ACQ_ID )
   DSPI_SPI_PORT_KINDS_OF_MESSAGE(KP254, ACQ_ID, KP254_INDEX_0,KP254_SPI_CHANNEL_INIT_0)
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_SPI_PORT_KINDS_OF_MESSAGE(KP254, ACQ_ID, KP254_INDEX_1,KP254_SPI_CHANNEL_INIT_1)
#endif
DSPI_SPI_PORT_END_KINDS_OF_MESSAGE

//=============================================================================
// KP254 All message array for all devices
//=============================================================================
DSPI_SPI_PORT_BEGIN_DEVICE_MESSAGES(KP254, KP254_MESSAGE_MAX )
   DSPI_SPI_PORT_USE_KINDS_OF_MESSAGE(KP254,ACQ_Pressure,KP254_INDEX_0),
   DSPI_SPI_PORT_USE_KINDS_OF_MESSAGE(KP254,ACQ_Temperature,KP254_INDEX_0),
   DSPI_SPI_PORT_USE_KINDS_OF_MESSAGE(KP254,Trigger_DIAG,KP254_INDEX_0),
   DSPI_SPI_PORT_USE_KINDS_OF_MESSAGE(KP254,ACQ_ID,KP254_INDEX_0)
#if (NUMBER_OF_KP254 > 1)
   DSPI_SPI_PORT_SEPERATOR
   DSPI_SPI_PORT_USE_KINDS_OF_MESSAGE(KP254,ACQ_Pressure,KP254_INDEX_1),
   DSPI_SPI_PORT_USE_KINDS_OF_MESSAGE(KP254,ACQ_Temperature,KP254_INDEX_1),
   DSPI_SPI_PORT_USE_KINDS_OF_MESSAGE(KP254,Trigger_DIAG,KP254_INDEX_1),
   DSPI_SPI_PORT_USE_KINDS_OF_MESSAGE(KP254,ACQ_ID,KP254_INDEX_1)
#endif
DSPI_SPI_PORT_END_DEVICE_MESSAGES


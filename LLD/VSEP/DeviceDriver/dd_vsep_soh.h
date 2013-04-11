#ifndef DD_VSEP_SOH_H
#define DD_VSEP_SOH_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_soh.h~4:incl:mt20u2#2 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:09:02 2005
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Fri Feb 16 11:37:15 2007 %
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


#include "dd_vsep.h"
#include "spi_message.h"

typedef enum
{
   VSEP_SOH_TXD_MESSAGE_CTRL,
   VSEP_SOH_TXD_MESSAGE_RESPONSE,
   VSEP_SOH_TXD_MESSAGE_MAX
}VSEP_SOH_Txd_Message_T;

typedef enum
{
   VSEP_SOH_RXD_MESSAGE_FLT,
   VSEP_SOH_RXD_MESSAGE_CHALLENGE,
   VSEP_SOH_RXD_MESSAGE_MAX
}VSEP_SOH_Rxd_Message_T;

typedef enum
{
   VSEP_SOH_STATUS_TXD_MESSAGE_CTRL,
   VSEP_SOH_STATUS_TXD_MESSAGE_RESERVED,
   VSEP_SOH_STATUS_TXD_MESSAGE_MAX
}VSEP_SOH_Status_Txd_Message_T;

typedef enum
{
   VSEP_SOH_STATUS_RXD_MESSAGE_FLT,
   VSEP_SOH_STATUS_RXD_MESSAGE_STATUS,
   VSEP_SOH_STATUS_RXD_MESSAGE_MAX
}VSEP_SOH_Status_Rxd_Message_T;

typedef enum 
{
                                                    //[ 6: 0] Reserved by VSEP.h
   VSEP_SOHRSTEN_CONFIGURATION_POSITION    = 7      //     7  SOHRSTEN   
}VSEP_SOHRSTEN_CONFIGURATION_POSITION_T;

typedef enum 
{
                                                    //[ 6: 0] Reserved by VSEP.h
   VSEP_SOHRSTEN_CONFIGURATION_WIDTH       = 1      //     1  
}VSEP_SOHRSTEN_CONFIGURATION_WIDTH_T;

typedef enum 
{                                                    //[ 6: 0] Reserved by VSEP.h
   VSEP_SOH_ENABLE_CONFIGURATION_POSITION =5 //      5  CRDISARM   
}VSEP_SOH_ENABLE_CONFIGURATION_POSITION_T;

typedef enum 
{                                                    //[ 6: 0] Reserved by VSEP.h
   VSEP_SOH_ENABLE_CONFIGURATION_WIDTH       = 1      // CRDISARM
}VSEP_SOH_ENABLE_CONFIGURATION_WIDTH_T;

extern uint16_t VSEP_SOH_Txd[NUMBER_OF_VSEP][VSEP_SOH_TXD_MESSAGE_MAX];
extern uint16_t VSEP_SOH_Rxd[NUMBER_OF_VSEP][VSEP_SOH_RXD_MESSAGE_MAX];
extern uint16_t VSEP_SOH_Status_Rxd[ NUMBER_OF_VSEP ][VSEP_SOH_STATUS_RXD_MESSAGE_MAX];


typedef enum
{
   VSEP_SOH_NORMAL_MODE,
   VSEP_SOH_HARDWARE_RESET_MODE
}VSEP_SOH_SOHRSTEN_Setting_T;
//=============================================================================
// VSEP_SOH_Set_SOHRSTEN
//
// @func Set desired setting for the SOHRSTEN bit.
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_SOH_SOHRSTEN_Setting_T | y | A <t uint16_t> desired value for SOHRSTEN.
//
// @rdesc <t IO_Configuration_T> containing the desired value for SOHRSTEN
//
// @end
//=============================================================================
#define VSEP_SOH_Set_SOHRSTEN(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_SOHRSTEN_CONFIGURATION_POSITION, VSEP_SOHRSTEN_CONFIGURATION_WIDTH ))
//=============================================================================
// VSEP_SOH_Get_SOHRSTEN
//
// @func Get the value of the SOHRSTEN bit.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_SOH_SOHRSTEN_Setting_T> value for SOHRSTEN decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_SOH_Get_SOHRSTEN(x) \
   (VSEP_SOH_SOHRSTEN_Setting_T)( Extract_Bits( x, VSEP_SOHRSTEN_CONFIGURATION_POSITION, VSEP_SOHRSTEN_CONFIGURATION_WIDTH ))

typedef enum
{
   VSEP_SOH_ENABLE,
   VSEP_SOH_DISABLE
}VSEP_SOH_ENABLE_Setting_T;
//=============================================================================
// VSEP_Msg_Set_CRDISARM
//
// @func Set EST IGBTCFG setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST CRDISARM
//    setting
//
// @parm uint8_t | crdisarm | The new EST CRDISARM setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST CRDISARM setting
//
// @end
//=============================================================================
#define VSEP_Msg_SOH_Set_CRDISARM( msg, crdisarm )\
   (uint16_t)( Insert_Bits( msg, crdisarm, VSEP_TXD_SETUP_CONFIGURATION_POSITION_CRDISARM, VSEP_TXD_SETUP_CONFIGURATION_WIDTH_CRDISARM ) )

//=============================================================================
// VSEP_SOH_Get_SOH_STATE
//
// @func Get the value of the CRDISARM bit.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_SOH_SOHRSTEN_Setting_T> value for SOHRSTEN decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_SOH_Get_ENABLE_STATE(x) \
   (VSEP_SOH_ENABLE_Setting_T)( Extract_Bits( x, VSEP_SOH_ENABLE_CONFIGURATION_POSITION, VSEP_SOH_ENABLE_CONFIGURATION_WIDTH ))
//=============================================================================
// VSEP_SOH_Set_SOHSTATE
//
// @func Set desired setting for the SOHRSTEN bit.
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_SOH_SOHRSTEN_Setting_T | y | A <t uint16_t> desired value for SOHRSTEN.
//
// @rdesc <t IO_Configuration_T> containing the desired value for SOHRSTEN
//
// @end
//=============================================================================
#define VSEP_SOH_Set_ENABLE(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_SOH_ENABLE_CONFIGURATION_POSITION, VSEP_SOH_ENABLE_CONFIGURATION_WIDTH ))
//=============================================================================
// VSEP_SOH_Initialize_Device
//
// @func Initialize the SOH portion of the VSEP device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_SOH_Initialize_Device( IO_Configuration_T in_config );

//=============================================================================
// VSEP_SOH_Set_Response
//
// @func Send the response value to the VSEP.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm uint32_t | response | The response value calculated from a previous
//    read of the challenge value.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_SOH_Set_Response( IO_Configuration_T in_configuration, uint32_t response  );

//=============================================================================
// VSEP_SOH_Set_Disable_Request
//
// @func Set fuel, spark disable request bit to the VSEP.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm bool | fse_disreq | Disable fuel, spark request through SPI.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_SOH_Set_DisableFSE_Request( IO_Configuration_T in_configuration, bool fse_disreq );

//=============================================================================
// VSEP_SOH_Set_Disable_Request_Immediate
//
// @func Send the disable request to the VSEP immediately.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm bool | fse_disreq | Disable fuel, spark request through SPI.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_SOH_Set_DisableFSE_Request_Immediate( IO_Configuration_T in_configuration, bool fse_disreq );

//=============================================================================
// VSEP_SOH_Set_Timeout_Fault
//
// @func Set challenge & response timeout fault bit clear.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm bool | cr_timeout | clear timeout fault bit.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_SOH_Set_Timeout_Fault( IO_Configuration_T in_configuration, bool cr_timeout );

//=============================================================================
// VSEP_SOH_Get_Challenge
//
// @func Retrieve the challenge value from the VSEP.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS uint32_t VSEP_SOH_Get_Challenge( IO_Configuration_T in_configuration  );


//=============================================================================
// Update_VSEP_SOH_Status_Immediate
//
// @func Retrieve the challenge value from the VSEP.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void Update_VSEP_SOH_Status_Immediate( IO_Configuration_T in_configuration  );


//=============================================================================
// VSEP_SOH_Set_SOHRSTEN_Request
//
// @func Retrieve the challenge value from the VSEP.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_SOH_Set_SOHRSTEN_Request( IO_Configuration_T in_configuration, bool sohrsten  );


// VSEP_SOH_Calculate_Response
//
// @func Calculate the response value to send back to the vsep.
//
// @parm uint32_t | challenge | The challenge value read from the VSEP
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_Calculate_Response( SPI_HClient_T in_hclient );
uint32_t VSEP_SOH_Calculate_Response( uint32_t challenge );
void VSEP_SOH_DisableSOH_Request( IO_Configuration_T in_configuration  );
void VSEP_SeviceSOH( void ); 
void VSEP_Disable_SOH( void );
#endif // DD_VSEP_SOH_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

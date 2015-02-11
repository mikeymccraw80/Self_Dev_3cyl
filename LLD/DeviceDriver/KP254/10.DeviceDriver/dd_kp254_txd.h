#ifndef DD_KP254_TXD_H
#define DD_KP254_TXD_H

//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254_txd.h %
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

typedef enum KP254_Request_Tag
{
    KP254_ACQUIRE_PRESSURE        = 0x01,
    KP254_ACQUIRE_TEMPERATURE     = 0x02,
    KP254_TRIGGER_DIAGNOSIS       = 0x04,
    KP254_ACQUIRE_IDENTIFIER      = 0x07
} KP254_Request_T;

typedef enum 
{
    KP254_MSB_POSITION_ADDITIONAL_REQ     = 10,
    KP254_MSB_POSITION_RESET_STRATEGY     = 12,
    KP254_MSB_POSITION_REQUEST            = 13
} KP254_Msg_Reset_Strategy_Configuration_Position_T;

typedef enum 
{
    KP254_MSB_WIDTH_ADDITIONAL_REQ     = 2,
    KP254_MSB_WIDTH_RESET_STRATEGY     = 1,
    KP254_MSB_WIDTH_REQUEST            = 3
} KP254_Msg_Reset_Strategy_Configuration_Width_T;

//=============================================================================
// KP254_Msg_Set_Additional_Req
//
// @func 
//
// @parm 
//
// @rdesc uint16_t
//
// @end
//=============================================================================
#define KP254_Msg_Set_Additional_Req( x, y ) \
   (uint16_t)( Insert_Bits( x, y, KP254_MSB_POSITION_ADDITIONAL_REQ, KP254_MSB_WIDTH_ADDITIONAL_REQ) )
//=============================================================================
// KP254_Msg_Get_Additional_Req
//
// @func 
//
// @parm 
//
// @rdesc uint16_t
//
// @end
//=============================================================================
#define KP254_Msg_Get_Additional_Req( x ) \
   (uint16_t)( Extract_Bits( x, KP254_MSB_POSITION_ADDITIONAL_REQ, KP254_MSB_WIDTH_ADDITIONAL_REQ) )


//=============================================================================
// KP254_Msg_Set_Reset_Strategy
//
// @func 
//
// @parm bool
//
// @rdesc uint16_t
//
// @end
//=============================================================================
#define KP254_Msg_Set_Reset_Strategy( x, y ) \
   (uint16_t)( Insert_Bits( x, y, KP254_MSB_POSITION_RESET_STRATEGY, KP254_MSB_WIDTH_RESET_STRATEGY) )
//=============================================================================
// KP254_Msg_Get_Reset_Strategy
//
// @func 
//
// @parm uint16_t
//
// @rdesc KP254_Reset_Strategy_T
//
// @end
//=============================================================================
#define KP254_Msg_Get_Reset_Strategy( x, y ) \
   (KP254_Reset_Strategy_T)( Extract_Bits( x, y, KP254_MSB_POSITION_RESET_STRATEGY, KP254_MSB_WIDTH_RESET_STRATEGY) )

//=============================================================================
// KP254_Msg_Set_Request
//
// @func 
//
// @parm KP254_Request_T
//
// @rdesc uint16_t
//
// @end
//=============================================================================
#define KP254_Msg_Set_Request( x, y ) \
   (uint16_t)( Insert_Bits( x, y, KP254_MSB_POSITION_REQUEST, KP254_MSB_WIDTH_REQUEST) )
//=============================================================================
// KP254_Msg_Get_Request
//
// @func 
//
// @parm uint16_t
//
// @rdesc KP254_Request_T
//
// @end
//=============================================================================
#define KP254_Msg_Get_Request( x, y ) \
   (KP254_Request_T)( Extract_Bits( x, y, KP254_MSB_POSITION_REQUEST, KP254_MSB_WIDTH_REQUEST) )

#endif /* end of include guard: DD_KP254_TXD_H */

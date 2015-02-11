#ifndef DD_KP254_RXD_H
#define DD_KP254_RXD_H

//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254_rxd.h %
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

typedef enum 
{
    KP254_RXD_PARITY_POSITION    = 0,    //@emem [0] parity
    KP254_RXD_DATA_POSITION      = 1,    //@emem [1-10] data
    KP254_RXD_DIAGNOSIS_POSITION = 11    //@emem [11-15] diagnosis information
} KP254_Rxd_Configuration_Postion_T;

typedef enum 
{
    KP254_RXD_PARITY_WIDTH       = 1,    //@emem [0] parity
    KP254_RXD_DATA_WIDTH         = 10,   //@emem [1-10] data
    KP254_RXD_DIAGNOSIS_WIDTH    = 5     //@emem [11-15] diagnosis information
} KP254_Rxd_Configuration_Width_T;

//=============================================================================
// KP254_Get_Rxd_Parity
//
// @func Get the rxd parity
//
// @parm IO_Configuration_T
//
// @rdesc uint16_t
//
// @end
//=============================================================================
#define KP254_Get_Rxd_Parity(x) \
   (uint16_t)( Extract_Bits( x, KP254_RXD_PARITY_POSITION, KP254_RXD_PARITY_WIDTH ) )

//=============================================================================
// KP254_Get_Rxd_Data
//
// @func Get the data information of rxd
//
// @parm IO_Configuration_T
//
// @rdesc uint16_t
//
// @end
//=============================================================================
#define KP254_Get_Rxd_Data(x) \
   (uint16_t)( Extract_Bits( x, KP254_RXD_DATA_POSITION, KP254_RXD_DATA_WIDTH) )

//=============================================================================
// KP254_Get_Rxd_Diagnosis
//
// @func Get the rxd diagnosis information
//
// @parm IO_Configuration_T
//
// @rdesc uint16_t
//
// @end
//=============================================================================
#define KP254_Get_Rxd_Diagnosis(x) \
   (uint16_t)( Extract_Bits( x, KP254_RXD_DIAGNOSIS_POSITION, KP254_RXD_DIAGNOSIS_WIDTH) )

#endif /* end of include guard: DD_KP254_RXD_H */

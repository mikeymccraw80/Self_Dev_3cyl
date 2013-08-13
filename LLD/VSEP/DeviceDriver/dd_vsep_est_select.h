#ifndef DD_VSEP_EST_SELECT_H
#define DD_VSEP_EST_SELECT_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_vsep_est_select.h %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:47 2005
//
// %derived_by:      nz45s2 %
//
// %date_modified:   Tue Mar  1 20:19:13 2011 %
//
// %version:         4.1.3 %
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
#define VSEP_TCB_COMPLEX_IO

#ifdef VSEP_TCB_COMPLEX_IO
#include "hal.h"
#endif

//=============================================================================
// Used for storing local data, not to be mapped onto the configuration word!
//=============================================================================
typedef struct
{
   bitfield32_t                     :  7; // [ 6: 0] Reserved by VSEP.h
   bitfield32_t number_of_cylinders :  3; // [ 9: 7] CYCCNT
   bitfield32_t index_mode          :  1; //     10  INDEX Mode (1x/2x)
   bitfield32_t paired_fire_mode    :  1; //     11  PFMODE
   bitfield32_t index_pin_select    :  1; //     12  EDGE
   bitfield32_t drive_mode          :  1; //     13  IGBTCFG
   bitfield32_t select_mode         :  1; //     14  DEC_DISCB
   bitfield32_t                     : 17; //[ 31:15] unused

}  VSEP_EST_Select_State_T;

//=============================================================================
// defines the cylinder to select for est.
//=============================================================================
typedef enum
{
   EST_SELECT_CYLINDER_A,
   EST_SELECT_CYLINDER_B,
   EST_SELECT_CYLINDER_C,
   EST_SELECT_CYLINDER_D,
   EST_SELECT_CYLINDER_E,
   EST_SELECT_CYLINDER_F,
   EST_SELECT_CYLINDER_G,
   EST_SELECT_CYLINDER_H,
   EST_SELECT_CYLINDER_I,
   EST_SELECT_CYLINDER_J,
   EST_SELECT_CYLINDER_K,
   EST_SELECT_CYLINDER_L


} EST_Select_Cylinder_T;//reuse from MT80

typedef enum 
{
                                                                     // [ 6: 0] Reserved by VSEP.h
   VSEP_EST_SELECT_CONFIGURATION_POSITION_NUMBER_OF_CYLINDERS  =  0, // [ 9: 7] CYCCNT
   VSEP_EST_SELECT_CONFIGURATION_POSITION_INDEX_MODE           =  3, //     10  INDEX Mode (1x/2x)
   VSEP_EST_SELECT_CONFIGURATION_POSITION_PAIRED_FIRE_MODE     =  4, //     11  PFMODE
   VSEP_EST_SELECT_CONFIGURATION_POSITION_INDEX_PIN_SELECT     =  5, //     12  EDGE
   VSEP_EST_SELECT_CONFIGURATION_POSITION_DRIVE_MODE           =  6, //     13  IGBTCFG
   VSEP_EST_SELECT_CONFIGURATION_POSITION_SELECT_MODE          =  7  //     14  DEC_DISCB

}VSEP_EST_Select_Configuration_Position_T;

typedef enum 
{
                                                                     // [ 6: 0] Reserved by VSEP.h
   VSEP_EST_SELECT_CONFIGURATION_WIDTH_NUMBER_OF_CYLINDERS     =  3, // [ 9: 7] CYCCNT
   VSEP_EST_SELECT_CONFIGURATION_WIDTH_INDEX_MODE              =  1, //     10  INDEX Mode (1x/2x)
   VSEP_EST_SELECT_CONFIGURATION_WIDTH_PAIRED_FIRE_MODE        =  1, //     11  PFMODE
   VSEP_EST_SELECT_CONFIGURATION_WIDTH_INDEX_PIN_SELECT        =  1, //     12  EDGE
   VSEP_EST_SELECT_CONFIGURATION_WIDTH_DRIVE_MODE              =  1, //     13  IGBTCFG
   VSEP_EST_SELECT_CONFIGURATION_WIDTH_SELECT_MODE             =  1  //     14  DEC_DISCB

}VSEP_EST_Select_Configuration_Width_T;

typedef enum
{
   VSEP_EST_SELECT_NUMBER_OF_CYLINDERS_3 = 2,
   VSEP_EST_SELECT_NUMBER_OF_CYLINDERS_4 = 3,
   VSEP_EST_SELECT_NUMBER_OF_CYLINDERS_5 = 4,
   VSEP_EST_SELECT_NUMBER_OF_CYLINDERS_6 = 5,
   VSEP_EST_SELECT_NUMBER_OF_CYLINDERS_8 = 7

}VSEP_EST_Select_Number_Of_Cylinders_T;

//=============================================================================
// dfines our current mode of operation.
//=============================================================================
typedef enum
{
   EST_MODE_SINGLE_CHANNEL,
   EST_MODE_PAIRED_SINGLE_ENABLE,
   EST_MODE_PAIRED_MULTIPLE_ENABLE,
   EST_MODE_SEQUENTIAL_SINGLE_ENABLE,
   EST_MODE_SEQUENTIAL_MULTIPLE_ENABLE,
   EST_MODE_SIMULTANEOUS_SINGLE_ENABLE,
   EST_MODE_SIMULTANEOUS_MULTIPLE_ENABLE

} EST_Mode_T; //reuse from MT80

//=============================================================================
// VSEP_EST_Select_Set_Cylinder_Count
//
// @func Set the desired number of cylinders in the configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_EST_Select_Number_Of_Cylinders_T | y | A <t VSEP_EST_Select_Number_Of_Cylinders_T> value.
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_EST_Select_Number_Of_Cylinders_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Set_Cylinder_Count(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_EST_SELECT_CONFIGURATION_POSITION_NUMBER_OF_CYLINDERS, VSEP_EST_SELECT_CONFIGURATION_WIDTH_NUMBER_OF_CYLINDERS ) )

//=============================================================================
// VSEP_EST_Select_Get_Cylinder_Count
//
// @func Get the configured number of cylinders.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_EST_Select_Number_Of_Cylinders_T> number of cylinders decoded from 
//    the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Get_Cylinder_Count(x) \
   (VSEP_EST_Select_Number_Of_Cylinders_T)( Extract_Bits( x, VSEP_EST_SELECT_CONFIGURATION_POSITION_NUMBER_OF_CYLINDERS, VSEP_EST_SELECT_CONFIGURATION_WIDTH_NUMBER_OF_CYLINDERS ) )

typedef enum
{
   VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN,
   VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN

}  VSEP_EST_Select_Index_Pin_Select_T;

//=============================================================================
// VSEP_EST_Select_Set_Index_Pin_Select
//
// @func Set the desired index pin select in the configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_EST_Select_Index_Pin_Select_T | y | A <t VSEP_EST_Select_Index_Pin_Select_T> value.
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_EST_Select_Index_Pin_Select_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Set_Index_Pin_Select(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_EST_SELECT_CONFIGURATION_POSITION_INDEX_PIN_SELECT, VSEP_EST_SELECT_CONFIGURATION_WIDTH_INDEX_PIN_SELECT ) )

//=============================================================================
// VSEP_EST_Select_Get_Index_Pin_Select
//
// @func Get the configured index pin select
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_EST_Select_Index_Pin_Select_T> index pin select decoded from 
//    the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Get_Index_Pin_Select(x) \
   (VSEP_EST_Select_Index_Pin_Select_T)( Extract_Bits( x, VSEP_EST_SELECT_CONFIGURATION_POSITION_INDEX_PIN_SELECT, VSEP_EST_SELECT_CONFIGURATION_WIDTH_INDEX_PIN_SELECT ) )

typedef enum
{
   VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER,
   VSEP_EST_SELECT_INCREMENT_INDEX_MODE_TWICE_PER

}  VSEP_EST_Select_Increment_Index_Mode_T;

//=============================================================================
// VSEP_EST_Select_Set_Increment_Index_Mode
//
// @func Set the desired EST increment index mode in the configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_EST_Select_Increment_Index_Mode_T | y | A <t VSEP_EST_Select_Increment_Index_Mode_T> value.
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_EST_Select_Increment_Index_Mode_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Set_Increment_Index_Mode(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_EST_SELECT_CONFIGURATION_POSITION_INDEX_MODE, VSEP_EST_SELECT_CONFIGURATION_WIDTH_INDEX_MODE ) )

//=============================================================================
// VSEP_EST_Select_Get_Increment_Index_Mode
//
// @func Get the configured EST increment index mode.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_EST_Select_Increment_Index_Mode_T> EST increment index mode decoded from 
//    the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Get_Increment_Index_Mode(x) \
   (VSEP_EST_Select_Increment_Index_Mode_T)( Extract_Bits( x, VSEP_EST_SELECT_CONFIGURATION_POSITION_INDEX_MODE, VSEP_EST_SELECT_CONFIGURATION_WIDTH_INDEX_MODE ) )

typedef enum
{
   VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED,
   VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED

}  VSEP_EST_Select_Paired_Fire_Mode_T;

//=============================================================================
// VSEP_EST_Select_Set_Paired_Fire_Mode
//
// @func Set the desired EST paired firing mode in the configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_EST_Select_Paired_Fire_Mode_T | y | A <t VSEP_EST_Select_Paired_Fire_Mode_T> value.
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_EST_Select_Paired_Fire_Mode_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Set_Paired_Fire_Mode(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_EST_SELECT_CONFIGURATION_POSITION_PAIRED_FIRE_MODE, VSEP_EST_SELECT_CONFIGURATION_WIDTH_PAIRED_FIRE_MODE ) )

//=============================================================================
// VSEP_EST_Select_Get_Paired_Fire_Mode
//
// @func Get the configured EST paired firing mode.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_EST_Select_Paired_Fire_Mode_T> EST paired firing mode decoded from 
//    the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Get_Paired_Fire_Mode(x) \
   (VSEP_EST_Select_Paired_Fire_Mode_T)( Extract_Bits( x, VSEP_EST_SELECT_CONFIGURATION_POSITION_PAIRED_FIRE_MODE, VSEP_EST_SELECT_CONFIGURATION_WIDTH_PAIRED_FIRE_MODE ) )

typedef enum
{
   VSEP_EST_SELECT_DRIVE_MODE_EST,
   VSEP_EST_SELECT_DRIVE_MODE_IGBT

}  VSEP_EST_Select_Drive_Mode_T;

//=============================================================================
// VSEP_EST_Select_Set_Drive_Mode
//
// @func Set the desired EST output drive mode in the configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_EST_Select_Drive_Mode_T | y | A <t VSEP_EST_Select_Drive_Mode_T> value.
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_EST_Select_Drive_Mode_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Set_Drive_Mode(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_EST_SELECT_CONFIGURATION_POSITION_DRIVE_MODE, VSEP_EST_SELECT_CONFIGURATION_WIDTH_DRIVE_MODE ) )

//=============================================================================
// VSEP_EST_Select_Get_Drive_Mode
//
// @func Get the configured EST output drive mode.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_EST_Select_Drive_Mode_T> EST output drive mode decoded from 
//    the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Get_Drive_Mode(x) \
   (VSEP_EST_Select_Drive_Mode_T)( Extract_Bits( x, VSEP_EST_SELECT_CONFIGURATION_POSITION_DRIVE_MODE, VSEP_EST_SELECT_CONFIGURATION_WIDTH_DRIVE_MODE ) )

typedef enum
{
   VSEP_EST_SELECT_SELECT_MODE_EXTERNAL_IO,
   VSEP_EST_SELECT_SELECT_MODE_INTERNAL_DECODER

}  VSEP_EST_Select_Select_Mode_T;

//=============================================================================
// VSEP_EST_Select_Set_Select_Mode
//
// @func Set the desired EST select mode in the configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_EST_Select_Drive_Mode_T | y | A <t VSEP_EST_Select_Select_Mode_T> value.
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_EST_Select_Select_Mode_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Set_Select_Mode(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_EST_SELECT_CONFIGURATION_POSITION_SELECT_MODE, VSEP_EST_SELECT_CONFIGURATION_WIDTH_SELECT_MODE ) )

//=============================================================================
// VSEP_EST_Select_Get_Select_Mode
//
// @func Get the configured EST select mode.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_EST_Select_Select_Mode_T> EST select mode decoded from 
//    the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_EST_Select_Get_Select_Mode(x) \
   (VSEP_EST_Select_Select_Mode_T)( Extract_Bits( x, VSEP_EST_SELECT_CONFIGURATION_POSITION_SELECT_MODE, VSEP_EST_SELECT_CONFIGURATION_WIDTH_SELECT_MODE ) )

typedef enum
{
   VSEP_EST_SELECT_TXD_MESSAGE_CTRL,
   VSEP_EST_SELECT_TXD_MESSAGE_EST_CTRL,
   VSEP_EST_SELECT_TXD_MESSAGE_MAX

}  VSEP_EST_Select_Txd_Message_T;

typedef enum
{
   VSEP_EST_SELECT_RXD_MESSAGE_FLT,
   VSEP_EST_SELECT_RXD_MESSAGE_ESTCNT,
   VSEP_EST_SELECT_RXD_MESSAGE_MAX

}  VSEP_EST_Select_Rxd_Message_T;

extern uint16_t VSEP_EST_Select_Txd[VSEP_EST_SELECT_TXD_MESSAGE_MAX];
extern uint16_t VSEP_EST_Select_Rxd[VSEP_EST_SELECT_RXD_MESSAGE_MAX];
#ifdef  VSEP_CALIBRATION_ENABLE
 extern uint16_t VSEP_EST_SELECT_INITIAL[VSEP_EST_SELECT_TXD_MESSAGE_MAX];
#else
extern const uint16_t VSEP_EST_SELECT_INITIAL[VSEP_EST_SELECT_TXD_MESSAGE_MAX];
#endif

#ifndef VSEP_TCB_COMPLEX_IO

//=============================================================================
// EST_Select_Initialize_Device_T
//
// @func 
//
// @parm IO_Configuration_T | in_configuration | .
//
// @rdesc none
//
// @end
//=============================================================================
FAR_COS void VSEP_EST_Select_Initialize_Device(
   IO_Configuration_T  in_configuration );

#else
//=============================================================================
// EST_Select_Initialize_Device_T
//
// @func 
//
// @parm IO_Est_Select_Tag | in_est_select | A handle to the est select device.
//
// @rdesc none
//
// @end
//=============================================================================
FAR_COS void VSEP_EST_Select_Initialize_Device(
  IO_Configuration_T  in_configuration );


//=============================================================================
// EST_Select_Set_Channel_T
//
// @func 
//
// @parm IO_Est_Select_Tag | in_est_select | A handle to the est select device.
//
// @rdesc none
//
// @end
//=============================================================================
FAR_COS void VSEP_EST_Select_Set_Channel(
   IO_Configuration_T        in_configuration,
   EST_Select_Cylinder_T   in_channel );

#if CcSYST_NUM_OF_CYLINDERS == 3
//=============================================================================
// VSEP_EST_Select_Set_Index
//
// @func 
//
// @parm
//
// @rdesc
//
// @end
//=============================================================================
FAR_COS void VSEP_EST_Select_Set_Index(
   IO_Configuration_T        in_configuration,
   bool					     in_index );
#endif
//=============================================================================
// VSEP_EST_Select_Increment_Channel
//
// @func 
//
// @parm IO_Est_Select_Tag | in_est_select | A handle to the est select device.
//
// @rdesc none
//
// @end
//=============================================================================
FAR_COS void VSEP_EST_Select_Increment_Channel(
   EST_Select_Cylinder_T   in_channel );


//=============================================================================
// EST_Select_Enable_T
//
// @func 
//
// @parm IO_Est_Select_Tag | in_est_select | A handle to the est select device.
//
// @rdesc none
//
// @end
//=============================================================================
FAR_COS void VSEP_EST_Select_Enable(void);


//=============================================================================
// EST_Select_Disable_T
//
// @func 
//
// @parm IO_Est_Select_Tag | in_est_select | A handle to the est select device.
//
// @rdesc none
//
// @end
//=============================================================================
FAR_COS void VSEP_EST_Select_Disable(void);



//=============================================================================
// EST_Select_Set_Number_Of_Cylinders_T
//
// @func 
//
// @parm IO_Est_Select_Tag | in_est_select | A handle to the est select device.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_EST_Select_Set_Number_Of_Cylinders(
   uint8_t           in_number_of_cylinders );


//=============================================================================
// EST_Select_Get_Mode_T
//
// @func 
//
// @parm IO_Est_Select_Tag | in_est_select | A handle to the est select device.
//
// @rdesc none
//
// @end
//=============================================================================
FAR_COS EST_Mode_T VSEP_EST_Select_Get_Mode(void );

FAR_COS bool VSEP_EST_Select_Get_Mode_PF(void);
//=============================================================================
// EST_Select_Set_Mode_T
//
// @func 
//
// @parm IO_Est_Select_Tag | in_est_select | A handle to the est select device.
//
// @rdesc none
//
// @end
//=============================================================================
FAR_COS void VSEP_EST_Select_Set_Mode(
   IO_Configuration_T        in_configuration,
   EST_Mode_T        in_mode );

//=============================================================================
// VSEP_EST_Set_PF_Mode
//
// @func 
//
// @parm IO_Est_Select_Tag | in_est_select | A handle to the est select device.
//
// @rdesc none
//
// @end
//=============================================================================

FAR_COS void VSEP_EST_Set_PF_Mode(
   IO_Configuration_T        in_configuration,//MTSA_EST_SELECT_DEVICE/	VSEP_INDEX_0
   VSEP_EST_Select_Paired_Fire_Mode_T        in_mode );

#endif
#endif // DD_VSEP_EST_SELECT_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       *
 * 4.1.3 mt20u2#800 11/01/02 nz45s2 RSM_CTC_8093_Add Mt22p1 ETC 3cylinder package_Rev0_20110120 *
 \*===========================================================================*/

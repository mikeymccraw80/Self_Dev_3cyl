#ifndef DD_VSEP_FAULT_H
#define DD_VSEP_FAULT_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_vsep_fault.h %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:52 2005
//
// %derived_by:      nz45s2 %
//
// %date_modified:   Thu Mar  3 18:32:29 2011 %
//
// %version:         13.1.1 %
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


#include "fault.h"
#include "dd_vsep_pwm_interface.h"
#include "dd_vsep_est_select.h"
#include "hal.h"
#include "hwiocald.h"

//#ifdef HW_TEST_SW
#define GetSPRK_SparkDeliveryMode() CeWasteEST // 2IGBT
//#define GetSPRK_SparkDeliveryMode() CeSequentialEST // 4IGBT
//#endif

#define MICROSECOND_RESOLUTION (6)//need consider again

typedef unsigned long                                                    TIME_DWELL_DW;
#define Prec_TIME_DWELL_DW                                 (1.0/1000000)
#define Min_TIME_DWELL_DW                                                    (0)
#define Max_TIME_DWELL_DW               (4294967295uL * Prec_TIME_DWELL_DW + Min_TIME_DWELL_DW)


typedef unsigned long                                                    PULSE_PERIOD_DW;
#define Prec_PULSE_PERIOD_DW                                (1.0/1000000)
#define Min_PULSE_PERIOD_DW                                                    (0)
#define Max_PULSE_PERIOD_DW               (4294967295uL * Prec_PULSE_PERIOD_DW + Min_PULSE_PERIOD_DW)


typedef unsigned long                                                    COUNT_DW;
#define Prec_COUNT_DW                                  			 (1.0)
#define Min_COUNT_DW                                                    (0.0)
#define Max_COUNT_DW               (4294967295uL * Prec_COUNT_DW + Min_COUNT_DW)

#define VSEP_FAULT_COUNTER_DECREMENT_TIME_COUNT \
                                 ( (uint16_t)(VSEP_FAULT_COUNTER_DECREMENT_TIME / VSEP_FAULT_UPDATE_TIME) )
/* threshold to shutdown channel due to contiually STB */
#define VSEP_CHANNEL_FAULT_COUNT_THRESHOLD ((VSEP_SHUTOFF_TIME_WHEN_STB) / (VSEP_FAULT_UPDATE_TIME))
#define VSEP_CHANNEL_FAULT_COUNTER_INCREMENT_STEP 1 /* step to increase */
#define VSEP_CHANNEL_FAULT_COUNTER_DECREMENT_STEP 1 /* step to decrease */
#define VSEP_EST_PAIRED_FIRE_MODE (VSEP_EST_Select_Get_Paired_Fire_Mode( VSEP_0_EST_SELECT_SETUP_INIT ))


#define VSEP_SHUTOFF_TIME_WHEN_STB (128.0) /* 128ms given by EE */
#define VSEP_FAULT_UPDATE_TIME (7.8125) /* the periodic time to update VSEP fault -- VSEP_Fault_Diagnose_Channels() */
#define VSEP_FAULT_COUNTER_DECREMENT_TIME (20000) /* 20 sec */





typedef enum
{
   VSEP_EST_FAULT_TXD_MESSAGE_CTRL,
   VSEP_EST_FAULT_TXD_MESSAGE_GRADCHECK,
   VSEP_EST_FAULT_TXD_MESSAGE_MAX
}VSEP_EST_Fault_Txd_Message_T;

typedef enum
{
   VSEP_EST_FAULT_RXD_MESSAGE_FLT,
   VSEP_EST_FAULT_RXD_MESSAGE_GRADCOUNT,
   VSEP_EST_FAULT_RXD_MESSAGE_MAX
}VSEP_EST_Fault_Rxd_Message_T;

typedef enum
{
   VSEP_EST_FAULT_CHECK_TXD_MESSAGE_CTRL,
   VSEP_EST_FAULT_CHECK_TXD_MESSAGE_NA_0,
   VSEP_EST_FAULT_CHECK_TXD_MESSAGE_MAX
}VSEP_EST_Fault_CHECK_Txd_Message_T;

typedef enum
{
   VSEP_EST_FAULT_SYNC_TXD_MESSAGE_CTRL_BYTE0,
   VSEP_EST_FAULT_SYNC_TXD_MESSAGE_CTRL_BYTE1,
   VSEP_EST_FAULT_SYNC_TXD_MESSAGE_SYNC_BYTE2,
   VSEP_EST_FAULT_SYNC_TXD_MESSAGE_MAX_BYTE
}VSEP_EST_Fault_SYNC_BYTE_Txd_Message_T;

typedef enum
{
   VSEP_EST_FAULT_SYNC_RXD_MESSAGE_FLT_BYTE0,
   VSEP_EST_FAULT_SYNC_RXD_MESSAGE_FLT_BYTE1,
   VSEP_EST_FAULT_SYNC_RXD_MESSAGE_FLT_BYTE2,
   VSEP_EST_FAULT_SYNC_RXD_MESSAGE_MAX_BYTE
}VSEP_EST_Fault_SYNC_BYTE_Rxd_Message_T;

typedef enum
{
   VSEP_FAULT_TXD_MESSAGE_CTRL,
   VSEP_FAULT_TXD_MESSAGE_NA_0,
   VSEP_FAULT_TXD_MESSAGE_NA_2,
   VSEP_FAULT_TXD_MESSAGE_NA_4,
   VSEP_FAULT_TXD_MESSAGE_NA_6,
   VSEP_FAULT_TXD_MESSAGE_MAX
}VSEP_Fault_Txd_Message_T;

typedef enum
{
   VSEP_EST_FAULT_CHECK_RXD_MESSAGE_FLT,
   VSEP_EST_FAULT_CHECK_RXD_MESSAGE_FLT_GRP_5,
   VSEP_EST_FAULT_CHECK_RXD_MESSAGE_MAX
}VSEP_EST_Fault_CHECK_Rxd_Message_T;

typedef enum
{
   VSEP_FAULT_RXD_MESSAGE_FLT,
   VSEP_FAULT_RXD_MESSAGE_FLT_GRP_6,
   VSEP_FAULT_RXD_MESSAGE_FLT_GRP_8,
   VSEP_FAULT_RXD_MESSAGE_FLT_GRP_A,
   VSEP_FAULT_RXD_MESSAGE_FLT_GRP_C,
   VSEP_FAULT_RXD_MESSAGE_MAX
}VSEP_Fault_Rxd_Message_T;

typedef enum
{
   VSEP_FAULT_PCH_NO_FAULTS_DETECTED,
   VSEP_FAULT_PCH_OPEN_FAULT,
   VSEP_FAULT_PCH_SHORT_TO_GROUND_FAULT,
   VSEP_FAULT_PCH_SHORT_TO_BATTERY_FAULT
}VSEP_Fault_PCH_T;

typedef enum
{
   VSEP_GRADIENT_CHECK_CONFIGURATION_POSITION_THRESHOLD    = 1, // [ 3: 1] Gradient Threshold
   VSEP_GRADIENT_CHECK_CONFIGURATION_POSITION_FILTER_TIME  = 4  // [ 3: 4] Filter Time
}  VSEP_Gradient_Check_Configuration_Position_T;

typedef enum
{
   VSEP_GRADIENT_CHECK_CONFIGURATION_WIDTH_THRESHOLD       = 3, // [ 3: 1] Gradient Threshold 
   VSEP_GRADIENT_CHECK_CONFIGURATION_WIDTH_FILTER_TIME     = 3  // [ 3: 4] Filter Time
}  VSEP_Gradient_Check_Configuration_Width_T;

/////////////////////////////////////////////
typedef enum
{
   VSEP_FAULT_MAP_CONFIGURATION_POSITION_CHANNEL   = 0,
   VSEP_FAULT_MAP_CONFIGURATION_POSITION_INDEX     = 6,
   VSEP_FAULT_MAP_CONFIGURATION_POSITION_POSITION  = 9,
   VSEP_FAULT_MAP_CONFIGURATION_POSITION_WIDTH     = 13

} VSEP_FAULT_Map_Configuration_Position_T;

typedef enum
{
   VSEP_FAULT_MAP_CONFIGURATION_WIDTH_CHANNEL   = 6,
   VSEP_FAULT_MAP_CONFIGURATION_WIDTH_INDEX     = 3,
   VSEP_FAULT_MAP_CONFIGURATION_WIDTH_POSITION  = 4,
   VSEP_FAULT_MAP_CONFIGURATION_WIDTH_WIDTH     = 1

} VSEP_FAULT_Map_Configuration_Width_T;

#define DD_DiscreteOutputEnable(function) \
             function ## _Fault ## (Set_Output_Enable, function ## _DiagMask, 1 )

#define DD_GetDiscreteDiagStatus(function,fault) \
             function ## _Fault## (Get_Fault, function ## _Channel, fault)

#define DD_ClearDiscreteDiagStatus(function,fault) \
             function ## _Fault## (Clear_Fault, function ## _Channel, fault)

#define VSEP_FAULT_Get_OUTPUT_OPEN_CKT_FAULT(x) \
	(FAULT_Get_Occured_Open_Circuit(x)||FAULT_Get_Occured_Short_To_Ground(x))

#define VSEP_FAULT_Clear_OUTPUT_OPEN_CKT_FAULT(x) \
	(FAULT_Clear_Occured_Open_Circuit(x)&FAULT_Clear_Occured_Short_To_Ground(x))

#define VSEP_FAULT_Clear_OUTPUT_SHORT_CKT_FAULT(x) \
	FAULT_Set_Occured_Short_To_Battery(x,false) 

#define VSEP_FAULT_Get_OUTPUT_SHORT_CKT_FAULT(x) \
	(FAULT_Get_Occured_Short_To_Battery(x)) 

#define VSEP_FAULT_Get_OUTPUT_OPEN_CKT_TESTED(x) \
	(FAULT_Get_Tested_Open_Circuit(x)||FAULT_Get_Tested_Short_To_Ground(x))

#define VSEP_FAULT_Clear_OUTPUT_OPEN_CKT_TESTED(x) \
	(FAULT_Clear_Tested_Open_Circuit(x)&FAULT_Clear_Tested_Short_To_Ground(x))

#define VSEP_FAULT_Clear_OUTPUT_SHORT_CKT_TESTED(x) \
	 FAULT_Set_Tested_Short_To_Battery(x,false)

#define VSEP_FAULT_Get_OUTPUT_SHORT_CKT_TESTED(x) \
	FAULT_Get_Tested_Short_To_Battery(x)

#define VSEP_FAULT_Map_Set_Channel( configuration, channel ) \
   ( Insert_Bits( configuration, channel, VSEP_FAULT_MAP_CONFIGURATION_POSITION_CHANNEL, VSEP_FAULT_MAP_CONFIGURATION_WIDTH_CHANNEL ) )
#define VSEPS_FAULT_Map_Get_Channel( configuration ) \
   ( Extract_Bits( configuration, VSEP_FAULT_MAP_CONFIGURATION_POSITION_CHANNEL, VSEP_FAULT_MAP_CONFIGURATION_WIDTH_CHANNEL ) )

#define VSEP_FAULT_Map_Set_Index( configuration, index ) \
   ( Insert_Bits( configuration, index, VSEP_FAULT_MAP_CONFIGURATION_POSITION_INDEX, VSEP_FAULT_MAP_CONFIGURATION_WIDTH_INDEX ) )
#define VSEPS_FAULT_Map_Get_Index( configuration ) \
   ( Extract_Bits( configuration, VSEP_FAULT_MAP_CONFIGURATION_POSITION_INDEX, VSEP_FAULT_MAP_CONFIGURATION_WIDTH_INDEX ) )

#define VSEP_FAULT_Map_Set_Position( configuration, position ) \
   ( Insert_Bits( configuration, position, VSEP_FAULT_MAP_CONFIGURATION_POSITION_POSITION, VSEP_FAULT_MAP_CONFIGURATION_WIDTH_POSITION ) )
#define VSEPS_FAULT_Map_Get_Position( configuration ) \
   ( Extract_Bits( configuration, VSEP_FAULT_MAP_CONFIGURATION_POSITION_POSITION, VSEP_FAULT_MAP_CONFIGURATION_WIDTH_POSITION ) )

typedef enum
{
   VSEP_FAULT_MAP_WIDTH_1_BIT,
   VSEP_FAULT_MAP_WIDTH_2_BIT
}VSEP_FAULT_Map_Width_T;

#define VSEP_FAULT_Map_Set_Width( configuration, width ) \
   ( Insert_Bits( configuration, width, VSEP_FAULT_MAP_CONFIGURATION_POSITION_WIDTH, VSEP_FAULT_MAP_CONFIGURATION_WIDTH_WIDTH ) )

#define VSEPS_FAULT_Map_Get_Width( configuration ) \
   ( Extract_Bits( configuration, VSEP_FAULT_MAP_CONFIGURATION_POSITION_WIDTH, VSEP_FAULT_MAP_CONFIGURATION_WIDTH_WIDTH ) )

typedef enum
{
   VSEP_GRADIENT_CHECK_FILTER_TIME_304US,
   VSEP_GRADIENT_CHECK_FILTER_TIME_464US,
   VSEP_GRADIENT_CHECK_FILTER_TIME_592US,
   VSEP_GRADIENT_CHECK_FILTER_TIME_912US,
   VSEP_GRADIENT_CHECK_FILTER_TIME_1200US,
   VSEP_GRADIENT_CHECK_FILTER_TIME_1808US,
   VSEP_GRADIENT_CHECK_FILTER_TIME_2416US,
   VSEP_GRADIENT_CHECK_FILTER_TIME_2992US
}  VSEP_Gradient_Check_Filter_Time_T;

//=============================================================================
// VSEP_EST_Gradient_Check_Set_Filter_Time
//
// @func Set the desired gradient check filter time in the configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_EST_Select_Gradient_Check_Time_T | y | A <t VSEP_EST_Select_Gradient_Check_Time_T> value.
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_EST_Select_Gradient_Check_Time_T>
//
// @end
//=============================================================================
#define VSEP_Gradient_Check_Set_Filter_Time(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_GRADIENT_CHECK_CONFIGURATION_POSITION_FILTER_TIME, VSEP_GRADIENT_CHECK_CONFIGURATION_WIDTH_FILTER_TIME))

//=============================================================================
// VSEP_Gradient_Check_Filter_Time
//
// @func Get the configured gradient check filter time.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_EST_Select_Gradient_Check_Time_T> EST gradient check time decoded from 
//    the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Gradient_Check_Get_Filter_Time(x) \
   (VSEP_Gradient_Check_Filter_Time_T)( Extract_Bits( x, VSEP_GRADIENT_CHECK_CONFIGURATION_POSITION_FILTER_TIME, VSEP_GRADIENT_CHECK_CONFIGURATION_WIDTH_FILTER_TIME))

typedef enum
{
   VSEP_GRADIENT_CHECK_THRESHOLD_160MV,
   VSEP_GRADIENT_CHECK_THRESHOLD_180MV,
   VSEP_GRADIENT_CHECK_THRESHOLD_200MV,
   VSEP_GRADIENT_CHECK_THRESHOLD_220MV,
   VSEP_GRADIENT_CHECK_THRESHOLD_240MV,
   VSEP_GRADIENT_CHECK_THRESHOLD_260MV,
   VSEP_GRADIENT_CHECK_THRESHOLD_280MV,
   VSEP_GRADIENT_CHECK_THRESHOLD_300MV

}  VSEP_Gradient_Check_Threshold_T;

//=============================================================================
// VSEP_Gradient_Check_Set_Threshold
//
// @func Set the desired gradient check threshold in the configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_EST_Select_Gradient_Threshold_T | y | A <t VSEP_EST_Select_Gradient_Threshold_T> value.
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_EST_Select_Gradient_Threshold_T>
//
// @end
//=============================================================================
#define VSEP_Gradient_Check_Set_Threshold(x,y) \
   (IO_Configuration_T)(Insert_Bits( x, y, VSEP_GRADIENT_CHECK_CONFIGURATION_POSITION_THRESHOLD, VSEP_GRADIENT_CHECK_CONFIGURATION_WIDTH_THRESHOLD)) 

//=============================================================================
// VSEP_Gradient_Check_Get_Threshold
//
// @func Get the configured EST gradient threshold.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_EST_Select_Gradient_Threshold_T> EST gradient threshold decoded from 
//    the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Gradient_Check_Get_Threshold(x) \
   (VSEP_Gradient_Check_Threshold_T)( Extract_Bits( x, VSEP_GRADIENT_CHECK_CONFIGURATION_POSITION_THRESHOLD, VSEP_GRADIENT_CHECK_CONFIGURATION_WIDTH_THRESHOLD))

/////////////////////////////////////////////

typedef enum
{
   VSEP_FAULT_IO_KIND_DISCRETE,
   VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION,
   VSEP_FAULT_IO_KIND_OUTPUT_COMPARE,
   VSEP_FAULT_IO_DUMMY_PIN,
   VSEP_FAULT_IO_KIND_IGNORE_PIN_STATE
}VSEP_Fault_IO_Kind_T;

typedef enum
{
   IO_MICROP_DISCRETE,
   IO_VSEP_DISCRETE,
   IO_VSEP_PWM,
   IO_MICROP_PWM,
   IO_NOT_CARE
}VSEP_CHANNEL_TYPE_T;

typedef struct 
{
   IO_Configuration_T            fault_configuration;
   IO_Configuration_T            io_configuration;
   VSEP_Fault_IO_Kind_T kind;
   IO_mask_T				io_mask;
   
}VSEP_Fault_Channel_Data_T;



 //typedef union 
 //{
//	KsVSEP_HW_Protect_Enable  Protect_Enable_Struct;
//	uint32_t  Protect_Enable_u32; 
// } Uprotect_Enable;


#define Number_of_EST_Channel  VSEP_EST_Select_Get_Cylinder_Count( VSEP_INIT_TXD_INITIAL[ 0 ][ VSEP_INIT_TXD_MESSAGE_EST_SELECT_INIT ])

extern uint16_t VSEP_EST_Fault_Txd[NUMBER_OF_VSEP][VSEP_EST_FAULT_RXD_MESSAGE_MAX];
extern uint16_t VSEP_EST_Fault_Rxd[NUMBER_OF_VSEP][VSEP_EST_FAULT_RXD_MESSAGE_MAX];
extern uint8_t VSEP_EST_Fault_SYNC_Txd[NUMBER_OF_VSEP][VSEP_EST_FAULT_SYNC_TXD_MESSAGE_MAX_BYTE];
extern uint8_t VSEP_EST_Fault_SYNC_Rxd[NUMBER_OF_VSEP][VSEP_EST_FAULT_SYNC_RXD_MESSAGE_MAX_BYTE];
extern uint16_t VSEP_Fault_Rxd[NUMBER_OF_VSEP][VSEP_FAULT_RXD_MESSAGE_MAX];
extern Fault_Log_T VSEP_Fault_Log[NUMBER_OF_VSEP][VSEP_CHANNEL_MAX];

extern uint16_t 	VSEP_Fault_Counter[NUMBER_OF_VSEP][VSEP_CHANNEL_PCH_30_FLT_LVL_7+1];
extern uint16_t 	VSEP_Fault_Counter_Decrement_Counter;
extern uint32_t            VSEP_DIS_ON_OFF_state ;

extern uint32_t 		VSEP_PWM_period_us[30];
extern uint32_t 		VSEP_PWM_ontime_us[30];
//extern Uprotect_Enable  Channel_Protect_Enable;
extern uint32_t Channel_Protect_Enable;
extern uint8_t			Filter_Time_Array[30];

//=============================================================================
// VSEP_FAULT_Get_Device_Fault
//
// @func Get the status of any fault on the requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc Return true if there is any fault on the device.
//
// @end
//=============================================================================
bool VSEP_FAULT_Get_Device_Fault(
   IO_Configuration_T in_configuration );

//=============================================================================
// FAULT_Clear_Device_Fault_T
//
// @func Clears all faults on a requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_FAULT_Clear_Device_Fault(
   IO_Configuration_T in_configuration );

//=============================================================================
// VSEP_FAULT_Is_Message_Valid
//
// @func The VSEP_FAULT_Is_Message_Valid function checks the SPI receive message
//    for validity.
//
// @parm IO_Configuration_T | in_configuration | Specifies which output on which
//       VSEP in the system to diagnose
//
// @parm VSEP_Message_T | in_message | Specifies the message to test.
//
// @rdesc true if the message is valid, otherwise false if the message is invalid.
//
// @end
//=============================================================================
bool VSEP_FAULT_Is_Message_Valid( 
   IO_Configuration_T in_configuration, 
   VSEP_Message_T     in_message );

void VSEP_Fault_Diagnose_Channels(void* in_pointer );
void VSEP_Fault_GRADCOUNT_Diagnose_EST_Channel(
   IO_Configuration_T in_configuration,
   uint8_t            in_channel,
   uint32_t           in_time	);

void VSEP_EST_Fault_SYNC_Interface(VSEP_Index_T vsep_index, EST_Select_Cylinder_T curent_spark_cylinder);
void VSEP_Fault_Initialize(void);
//=============================================================================
// VSEP_FAULT_EST_Initialize_Device
//
// @func Initialize a timer-based device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_FAULT_EST_Initialize_Device(
   IO_Configuration_T in_configuration );

//=============================================================================
// VSEP_FAULT_EST_Set_Filter_Time
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm VSEP_Gradient_Check_Filter_Time_T | in_time | The defined filter time value.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_FAULT_EST_Set_Filter_Time(
   IO_Configuration_T in_configuration,
   VSEP_Gradient_Check_Filter_Time_T in_time);

//=============================================================================
// VSEP_FAULT_EST_Set_Filter_Time_Immediate
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm VSEP_Gradient_Check_Filter_Time_T | in_time | The defined filter time value.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_FAULT_EST_Set_Filter_Time_Immediate(
   IO_Configuration_T in_configuration,
   VSEP_Gradient_Check_Filter_Time_T in_time);

//=============================================================================
// VSEP_FAULT_EST_Get_Filter_Time
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
// 
// @rdesc Gradient Check Filter Time
//
// @end
//=============================================================================
VSEP_Gradient_Check_Filter_Time_T VSEP_FAULT_EST_Get_Filter_Time(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_FAULT_EST_Set_Threshold
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm VSEP_Gradient_Check_Threshold_T | in_threshold | The gradient check threshold value.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_FAULT_EST_Set_Threshold(
   IO_Configuration_T in_configuration,
   VSEP_Gradient_Check_Threshold_T in_threshold);

//=============================================================================
// VSEP_FAULT_EST_Set_Threshold_Immediate
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm VSEP_Gradient_Check_Threshold_T | in_threshold | The gradient check threshold value.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_FAULT_EST_Set_Threshold_Immediate(
   IO_Configuration_T in_configuration,
   VSEP_Gradient_Check_Threshold_T in_threshold);

//=============================================================================
// VSEP_FAULT_EST_Get_Threshold
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The threshold value.
//
// @end
//=============================================================================
 VSEP_Gradient_Check_Threshold_T VSEP_FAULT_EST_Get_Threshold(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_Get_Channel_Fault
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The threshold value.
//
// @end
//=============================================================================
bool VSEP_Diagnostic_Get_Channel_Fault(IO_Configuration_T in_configuration,FAULT_T fault_type);

/*
//=============================================================================
// VSEP_Get_Channel_Fault
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The threshold value.
//
// @end
//=============================================================================
void  VSEP_Diagnostic_Set_Discrete_Channel_State(EMS_Discrete_Signals_T in_channel, bool in_state);
//=============================================================================
// VSEP_Get_Channel_Fault
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The threshold value.
//
// @end
//=============================================================================
void VSEP_Diagnostic_Toggle_Discrete_Channel_Immidiate(EMS_Discrete_Signals_T in_channel);
//=============================================================================
// VSEP_Get_Channel_Fault
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The threshold value.
//
// @end
//=============================================================================
bool VSEP_Diagnostic_Get_Discrete_Channel_State(EMS_Discrete_Signals_T in_channel);
//=============================================================================
// VSEP_Get_Channel_Fault
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The threshold value.
//
// @end
//=============================================================================
void VSEP_Diagnostic_Toggle_PWM_Channel_Immediate(EMS_PWM_Output_T in_channel);
//=============================================================================
// VSEP_Get_Channel_Fault
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The threshold value.
//
// @end
//=============================================================================
void VSEP_Diagnostic_PWM_Set_Duty_Cycle_Immediate(IO_Configuration_T in_configuration ,   uint32_t  in_duty_cycle);
*/
#endif // DD_VSEP_FAULT_H

/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 * 13.1.1 110128 nz45s2 mt20u2#809 RSM_CTC_0375_add auto start-stop function in MT22.1_Rev0_20101229
\*===========================================================================*/

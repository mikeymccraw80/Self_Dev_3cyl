#ifndef CRANK_H
#define CRANK_H

#include "reuse.h"

//=============================================================================
// @enum CRANK_Event_Id_T |
// Provides an enumerated list of Event IDs that are checked on crank tooth 
// events.  The priority is based on the enumeration value - the higher the
// value the higher the priority
//=============================================================================
typedef enum Crank_Event_Id_Tag
{
   CRANK_EVENT_ID_USER0,
   CRANK_EVENT_ID_USER1,
   CRANK_EVENT_ID_USER2,
   CRANK_EVENT_ID_USER3,
   CRANK_EVENT_ID_USER4,
   CRANK_EVENT_ID_USER5,
   CRANK_EVENT_ID_USER6,
   CRANK_EVENT_ID_USER7,
   CRANK_EVENT_ID_USER8,
   CRANK_EVENT_ID_USER9,
   CRANK_EVENT_ID_USER10,
   CRANK_EVENT_ID_USER11,
   CRANK_EVENT_ID_USER12,
   CRANK_EVENT_ID_USER13,
   CRANK_EVENT_ID_USER14,
   CRANK_EVENT_ID_USER15,
   CRANK_EVENT_ID_USER16,
   CRANK_EVENT_ID_USER17,
   CRANK_EVENT_ID_USER18,
   CRANK_EVENT_ID_USER19,
   CRANK_EVENT_ID_USER20,
   CRANK_EVENT_ID_USER21,
   CRANK_EVENT_ID_USER22,
   CRANK_EVENT_ID_USER23,
   CRANK_EVENT_ID_USER24,
   CRANK_EVENT_ID_USER25,
   CRANK_EVENT_ID_USER26,
   CRANK_EVENT_ID_USER27,
   CRANK_EVENT_ID_USER28,
   CRANK_EVENT_ID_USER29,
   CRANK_EVENT_ID_USER30,
   CRANK_EVENT_ID_USER31,
   CRANK_EVENT_ID_MAX

}Crank_Event_Id_T;

//=============================================================================
// @enum Crank_Tooth_T |
//
//=============================================================================
typedef enum Crank_Tooth_Tag
{
   CRANK_TOOTH__1 = 1,
   CRANK_TOOTH__2,
   CRANK_TOOTH__3,
   CRANK_TOOTH__4,
   CRANK_TOOTH__5,
   CRANK_TOOTH__6,
   CRANK_TOOTH__7,
   CRANK_TOOTH__8,
   CRANK_TOOTH__9,
   CRANK_TOOTH_10,
   CRANK_TOOTH_11,
   CRANK_TOOTH_12,
   CRANK_TOOTH_13,
   CRANK_TOOTH_14,
   CRANK_TOOTH_15,
   CRANK_TOOTH_16,
   CRANK_TOOTH_17,
   CRANK_TOOTH_18,
   CRANK_TOOTH_19,
   CRANK_TOOTH_20,
   CRANK_TOOTH_21,
   CRANK_TOOTH_22,
   CRANK_TOOTH_23,
   CRANK_TOOTH_24,
   CRANK_TOOTH_25,
   CRANK_TOOTH_26,
   CRANK_TOOTH_27,
   CRANK_TOOTH_28,
   CRANK_TOOTH_29,
   CRANK_TOOTH_30,
   CRANK_TOOTH_31,
   CRANK_TOOTH_32,
   CRANK_TOOTH_33,
   CRANK_TOOTH_34,
   CRANK_TOOTH_35,
   CRANK_TOOTH_36,
   CRANK_TOOTH_37,
   CRANK_TOOTH_38,
   CRANK_TOOTH_39,
   CRANK_TOOTH_40,
   CRANK_TOOTH_41,
   CRANK_TOOTH_42,
   CRANK_TOOTH_43,
   CRANK_TOOTH_44,
   CRANK_TOOTH_45,
   CRANK_TOOTH_46,
   CRANK_TOOTH_47,
   CRANK_TOOTH_48,
   CRANK_TOOTH_49,
   CRANK_TOOTH_50,
   CRANK_TOOTH_51,
   CRANK_TOOTH_52,
   CRANK_TOOTH_53,
   CRANK_TOOTH_54,
   CRANK_TOOTH_55,
   CRANK_TOOTH_56,
   CRANK_TOOTH_57,
   CRANK_TOOTH_58,
   CRANK_TOOTH_59,
   CRANK_TOOTH_60,
   CRANK_TOOTH_61,
   CRANK_TOOTH_62,
   CRANK_TOOTH_63,
   CRANK_TOOTH_64,
   CRANK_TOOTH_65,
   CRANK_TOOTH_66,
   CRANK_TOOTH_67,
   CRANK_TOOTH_68,
   CRANK_TOOTH_69,
   CRANK_TOOTH_70,
   CRANK_TOOTH_71,
   CRANK_TOOTH_72,
   CRANK_TOOTH_73,
   CRANK_TOOTH_74,
   CRANK_TOOTH_75,
   CRANK_TOOTH_76,
   CRANK_TOOTH_77,
   CRANK_TOOTH_78,
   CRANK_TOOTH_79,
   CRANK_TOOTH_80,
   CRANK_TOOTH_81,
   CRANK_TOOTH_82,
   CRANK_TOOTH_83,
   CRANK_TOOTH_84,
   CRANK_TOOTH_85,
   CRANK_TOOTH_86,
   CRANK_TOOTH_87,
   CRANK_TOOTH_88,
   CRANK_TOOTH_89,
   CRANK_TOOTH_90,
   CRANK_TOOTH_91,
   CRANK_TOOTH_92,
   CRANK_TOOTH_93,
   CRANK_TOOTH_94,
   CRANK_TOOTH_95,
   CRANK_TOOTH_96,
   CRANK_TOOTH_97,
   CRANK_TOOTH_98,
   CRANK_TOOTH_99,
   CRANK_TOOTH100,
   CRANK_TOOTH101,
   CRANK_TOOTH102,
   CRANK_TOOTH103,
   CRANK_TOOTH104,
   CRANK_TOOTH105,
   CRANK_TOOTH106,
   CRANK_TOOTH107,
   CRANK_TOOTH108,
   CRANK_TOOTH109,
   CRANK_TOOTH110,
   CRANK_TOOTH111,
   CRANK_TOOTH112,
   CRANK_TOOTH113,
   CRANK_TOOTH114,
   CRANK_TOOTH115,
   CRANK_TOOTH116,
   CRANK_TOOTH117,
   CRANK_TOOTH118,
   CRANK_TOOTH119,
   CRANK_TOOTH120,
   CRANK_TOOTH_MAX = CRANK_TOOTH120

}  Crank_Tooth_T;

//=============================================================================
//   Type declarations
//=============================================================================
// @enum Crank_Flag_T | Defines flag position in the 32 bit uint
typedef enum
{
   CRANK_FLAG_SYNC_OCCURRED                 =  0, // @emem 
   CRANK_FLAG_FIRST_SYNC_OCCURRED           =  1, // @emem 
   CRANK_FLAG_SYNC_ERROR_IN_PROGRESS        =  2, // @emem 
   CRANK_FLAG_FIRST_CYLINDER_EVENT_OCCURED  =  3, // @emem 
   CRANK_FLAG_POWER_UP                      =  4, // @emem 
   CRANK_FLAG_FILTER_ENABLED                =  5, // @emem 
   CRANK_FLAG_RUN_RESET_BYPASS_FILTER       =  6, // @emem 
   CRANK_FLAG_SYNC_STARTED                  =  7, // @emem 
   CRANK_FLAG_VALID_TOOTH                   =  8, // @emem 
   CRANK_FLAG_RESYNC_ATTEMPT_IN_PROG        =  9, // @emem 
   CRANK_FLAG_ENGINE_TURNING                = 10, // @emem 
   CRANK_FLAG_USING_DYNAMIC_SCHEDULER       = 12, // @emem 
   CRANK_FLAG_STALL_DETECTED                = 13, // @emem 
   CRANK_FLAG_CAM_BACKUP                    = 14, // @emem 
   CRANK_FLAG_TRANSITION_TO_CAM_BACKUP      = 15, // @emem 
   CRANK_FLAG_SYNC_FIRST_REVOLUTION         = 30, // @emem 
   CRANK_FLAG_SYNC_SECOND_REVOLUTION        = 31  // @emem 
 
}  Crank_Flag_T;

//=============================================================================
// @enum Crank_Parameter_T |
//
//=============================================================================

typedef enum Crank_Parameter_Tag
{
   CRANK_PARAMETER_HI_RES_REFERENCE_PERIOD,
   CRANK_PARAMETER_LO_RES_REFERENCE_PERIOD,
   CRANK_PARAMETER_TIME_BASE,
   CRANK_PARAMETER_CURRENT_EDGE_TIME,
   CRANK_PARAMETER_EDGE_TIME,
   CRANK_PARAMETER_EDGE_ANGLE,
   CRANK_PARAMETER_TIMER_VALUE_RAW,
   CRANK_PARAMETER_MAX_TIMER_VALUE,
   CRANK_PARAMETER_FILTER_VALUE,
   CRANK_PARAMETER_CYLINDER_EVENT_TIME,
   CRANK_PARAMETER_CYLINDER_EVENT_ANGLE,
   CRANK_PARAMETER_INITIAL_VIRTUAL_TEETH_PER_CYLINDER_EVENT,
   CRANK_PARAMETER_VIRTUAL_TEETH_PER_CYLINDER_EVENT,
   CRANK_PARAMETER_ANGLE_AT_CYLINDER_EVENT,
   CRANK_PARAMETER_REFERENCE_TOOTH_ERROR_COUNT,
   CRANK_PARAMETER_CURRENT_TOOTH,
   CRANK_PARAMETER_ANGLE_FROM_CYLINDER_EVENT_TO_TDC,
   CRANK_PARAMETER_NUMBER_OF_GAPS_DETECTED,
   CRANK_PARAMETER_REAL_REFERENCE_PERIOD,
   CRANK_PARAMETER_STALL_TIME_OUT,
   CRANK_PARAMETER_CAM_HISTORY,
   CRANK_PARAMETER_ENGINE_SPEED,
   CRANK_PARAMETER_CURRENT_EDGE_COUNT,
   CRANK_PARAMETER_MAX

}  Crank_Parameter_T;

//=============================================================================
// @enum Crank_Cylinder_T | Enumeration to indicate which cylinder's interval is occurring.
//=============================================================================
typedef enum
{
   CRANK_CYLINDER_A, // @emem
   CRANK_CYLINDER_B, // @emem
   CRANK_CYLINDER_C, // @emem
   CRANK_CYLINDER_D, // @emem
   CRANK_CYLINDER_E, // @emem
   CRANK_CYLINDER_F, // @emem
   CRANK_CYLINDER_G, // @emem
   CRANK_CYLINDER_H, // @emem
   CRANK_CYLINDER_I, // @emem
   CRANK_CYLINDER_J, // @emem
   CRANK_CYLINDER_K, // @emem
   CRANK_CYLINDER_L  // @emem

} Crank_Cylinder_T;

//=============================================================================
// @enum GPTA_Index_T | Index into arrays based on device selected.
// INCLUDE BEFORE COMMON!
//=============================================================================
typedef enum
{
   CRANK_State_Initialize,
   CRANK_State_Synchronize,
   CRANK_State_Normal,
   CRANK_State_Stall

}  Crank_State_T;

typedef uint16_t uCrank_Count_T;

typedef int16_t   Crank_Count_T;

typedef uint32_t uCrank_Angle_T;

typedef int32_t   Crank_Angle_T;

#define uCRANK_COUNT_MAX  UINT16_MAX

#define uCRANK_COUNT_MIN  UINT16_MIN

#define CRANK_COUNT_MAX   INT16_MAX

#define CRANK_COUNT_MIN   INT16_MIN

typedef struct IO_Crank_Initialization_Parameters_Tag
{
   uint8_t        number_of_cylinders;
   uCrank_Angle_T synchronization_start_angle;
   uCrank_Angle_T first_cylinder_event_angle;
   uCrank_Angle_T degrees_top_dead_center;
   uint32_t       rpm_synchronization_criteria; // Run time synchronization checking
   uint32_t       filter_min_rpm_for_synchronization;  // for initial and resync events
   uint32_t       filter_max_rpm_for_synchronization;  // for initial and resync events
   uint32_t       valid_synchronization_tooth_periods; // The number of valid teeth before we can search for the gap.

}  IO_Crank_Initialization_Parameters_T;

typedef struct Crank_Coherent_Edge_Time_And_Count_Tag
{
   uint16_t count;
   uint32_t time;

}  Crank_Coherent_Edge_Time_And_Count_T;



#endif // CRANK_H

#ifndef MCD5412_H
#define MCD5412_H

#include "reuse.h"
//=============================================================================
// Enumeration Definitions                                                     
//=============================================================================

//=============================================================================
// @enum MCD5412_SD_Mode_T | Start-Duration Mode or End-Duration Mode
//=============================================================================
typedef enum
{
   MCD5412_END_DURATION_MODE,
   MCD5412_START_DURATION_MODE
} MCD5412_SD_Mode_T;

//=============================================================================
// @enum MCD5412_Angle_Mode_T | Time Mode or Angle Mode
//=============================================================================
typedef enum
{
   MCD5412_TIME_MODE,
   MCD5412_ANGLE_MODE
}  MCD5412_Angle_Mode_T;

//=============================================================================
// MCD5412_Fall_Time_T
//=============================================================================
typedef struct MCD5412_Fall_Time_F_Tag
{
   bitfield32_t Current_State  : BIT_8;
   bitfield32_t Time           : BIT_24;

}  MCD5412_Fall_Time_F_T;

typedef union MCD5412_Fall_Time_Tag
{
   MCD5412_Fall_Time_F_T   F;
   uint32_t                U32;

}  MCD5412_Fall_Time_T;

//=============================================================================
// MCD5412_Rise_Time_T
//=============================================================================
typedef struct MCD5412_Rise_Time_F_Tag
{
   bitfield32_t Pulse_Counter  :  BIT_8;
   bitfield32_t Time           : BIT_24;

}  MCD5412_Rise_Time_F_T;

typedef union MCD5412_Rise_Time_Tag
{
   MCD5412_Rise_Time_F_T   F;
   uint32_t                U32;

}  MCD5412_Rise_Time_T;

//=============================================================================
// MCD5412_Max_Duration_T
//=============================================================================
typedef struct MCD5412_Max_Duration_F_Tag
{
   bitfield32_t                :  BIT_8;
   bitfield32_t Duration       : BIT_24;

}  MCD5412_Max_Duration_F_T;

typedef union MCD5412_Max_Duration_Tag
{
   MCD5412_Max_Duration_F_T   F;
   uint32_t                U32;

}  MCD5412_Max_Duration_T;

//=============================================================================
// MCD5412_Min_Duration_T
//=============================================================================
typedef struct MCD5412_Min_Duration_F_Tag
{
   bitfield32_t Max_Fall_Angle :  BIT_8;
   bitfield32_t Duration       : BIT_24;

}  MCD5412_Min_Duration_F_T;

typedef union MCD5412_Min_Duration_Tag
{
   MCD5412_Min_Duration_F_T   F;
   uint32_t                   U32;

}  MCD5412_Min_Duration_T;

//=============================================================================
// MCD5412_Duration_T
//=============================================================================
typedef struct MCD5412_Duration_F_Tag
{
   bitfield32_t Min_Rise_Angle :  BIT_8;
   bitfield32_t Duration       : BIT_24;

}  MCD5412_Duration_F_T;

typedef union MCD5412_Duration_Tag
{
   MCD5412_Duration_F_T       F;
   uint32_t                   U32;

}  MCD5412_Duration_T;

//=============================================================================
// MCD5412_Critical_Event_T
//=============================================================================
typedef struct MCD5412_Critical_Event_F_Tag
{
   bitfield32_t                      :  BIT_4;
   bitfield32_t In_SD_Mode           :  BIT_1;
   bitfield32_t Req_Out_Of_Range     :  BIT_1;
   bitfield32_t Multi_Pulse_Mode     :  BIT_1;
   bitfield32_t Dig_ShutOff_Enabled  :  BIT_1;
   bitfield32_t Event                : BIT_24;

}  MCD5412_Critical_Event_F_T;

typedef union MCD5412_Critical_Event_Tag
{
   MCD5412_Critical_Event_F_T     F;
   uint32_t                       U32;

} MCD5412_Critical_Event_T;

//=============================================================================
// MCD5412_Min_Off_Time_T
//=============================================================================
typedef struct MCD5412_Min_Off_Time_F_Tag
{
   bitfield32_t            :  BIT_8;
   bitfield32_t Time       : BIT_24;

}  MCD5412_Min_Off_Time_F_T;

typedef union MCD5412_Min_Off_Time_Tag
{
   MCD5412_Min_Off_Time_F_T       F;
   uint32_t                       U32;

} MCD5412_Min_Off_Time_T;

//=============================================================================
// MCD5412_Comp_Time_T
//=============================================================================
typedef struct MCD5412_Comp_Time_F_Tag
{
   bitfield32_t            :  BIT_8;
   bitfield32_t Time       : BIT_24;

}  MCD5412_Comp_Time_F_T;

typedef union MCD5412_Comp_Time_Tag
{
   MCD5412_Comp_Time_F_T       F;
   uint32_t                    U32;

}  MCD5412_Comp_Time_T;

//=============================================================================
// MCD5412_Fall_1_Time_T
//=============================================================================
typedef struct MCD5412_Fall_1_Time_F_Tag
{
   bitfield32_t            :  BIT_8;
   bitfield32_t Time       : BIT_24;

}  MCD5412_Fall_1_Time_F_T;

typedef union MCD5412_Fall_1_Time_Tag
{
   MCD5412_Fall_1_Time_F_T       F;
   uint32_t                      U32;

}  MCD5412_Fall_1_Time_T;

//=============================================================================
// MCD5412_Fall_1_Angle_T
//=============================================================================
typedef struct MCD5412_Fall_1_Angle_F_Tag
{
   bitfield32_t            :  BIT_8;
   bitfield32_t Angle      : BIT_24;

}  MCD5412_Fall_1_Angle_F_T;

typedef union MCD5412_Fall_1_Angle_Tag
{
   MCD5412_Fall_1_Angle_F_T       F;
   uint32_t                      U32;

}  MCD5412_Fall_1_Angle_T;

//=============================================================================
// MPTACe Structure
//=============================================================================
typedef volatile struct MCD5412_SDM_Tag
{
   MCD5412_Fall_Time_T        Fall_Time;
   MCD5412_Rise_Time_T        Rise_Time;
   MCD5412_Max_Duration_T     Max_Duration;
   MCD5412_Min_Duration_T     Min_Duration;
   MCD5412_Duration_T         Duration;
   MCD5412_Critical_Event_T   Critical_Event;
   MCD5412_Min_Off_Time_T     Min_Off_Time;
   MCD5412_Comp_Time_T        Comp_Time;
   MCD5412_Fall_1_Time_T      Fall_1_Time;
   MCD5412_Fall_1_Angle_T     Fall_1_Angle;

}  MCD5412_SDM_T;

#endif // MCD5412_H

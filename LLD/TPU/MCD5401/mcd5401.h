#ifndef MCD5401_H
#define MCD5401_H

#include "reuse.h"
#include "dd_tpu.h"

//===========================================================================
// Exported type declarations (enum, struct, union, typedef)
//===========================================================================

//===========================================================================
// MCD5401_Edge_Data_T
//===========================================================================
typedef struct MCD5401_Edge_Data_Tag
{
  uint32_t    Edge_Cnt;
  uint32_t    Edge_Time;
} MCD5401_Edge_Data_T;

//===========================================================================
// MCD5401_Edge_Count_T
//===========================================================================
typedef struct MCD5401_Edge_Count_F_Tag
{
   bitfield32_t                            : BIT_8;
   bitfield32_t Edge_Cnt                   : BIT_24;
}MCD5401_Edge_Count_F_T;

typedef union MCD5401_Edge_Count_Tag
{
   MCD5401_Edge_Count_F_T                  F;
   uint32_t                                U32;
}MCD5401_Edge_Count_T;

//===========================================================================
// MCD5401_Edge_Time_T
//===========================================================================
typedef struct MCD5401_Edge_Time_F_Tag
{
   bitfield32_t                            : BIT_8;
   bitfield32_t Edge_Time                  : BIT_24;
}MCD5401_Edge_Time_F_T;


typedef union MCD5401_Edge_Time_Tag
{
   MCD5401_Edge_Time_F_T                   F;
   uint32_t                                U32;
}MCD5401_Edge_Time_T;

//===========================================================================
// MCD5401_Requested_Time_T
//===========================================================================
typedef struct MCD5401_Requested_Time_F_Tag
{
   bitfield32_t                            :  BIT_8;
   bitfield32_t Requested_Time             : BIT_24;
}MCD5401_Requested_Time_F_T;

typedef union MCD5401_Requested_Time_Tag
{
   MCD5401_Requested_Time_F_T              F;
   uint32_t                                U32;
}MCD5401_Requested_Time_T;

//===========================================================================
// MCD5401_Actual_Event_Time_T
//===========================================================================
typedef struct MCD5401_Actual_Event_Time_F_Tag
{
   bitfield32_t                           : BIT_8;
   bitfield32_t Actual_Event_Time         : BIT_24;
}MCD5401_Actual_Event_Time_F_T;

typedef union MCD5401_Actual_Event_Time_Tag
{
   MCD5401_Actual_Event_Time_F_T          F;
   uint32_t                               U32;

} MCD5401_Actual_Event_Time_T;

//===========================================================================
// ICPCE Structure
//===========================================================================
typedef struct MCD5401_SDM_F_Tag
{
   volatile MCD5401_Edge_Count_T                     Edge_Count;
   volatile MCD5401_Edge_Time_T                      Edge_Time;
   volatile MCD5401_Requested_Time_T                 Requested_Time;
   volatile MCD5401_Actual_Event_Time_T              Actual_Event_Time;
}  MCD5401_SDM_F_T;

typedef struct MCD5401_SDM_Tag
{
   MCD5401_SDM_F_T                    F;
}  MCD5401_SDM_T;

//===========================================================================
// MCD5401_Channel_Init_T - Channel Init paramters
//===========================================================================
typedef struct MCD5401_Channel_Init_Tag
{
   const bitfield32_t    Link_Start           : BIT_8;
   const bitfield32_t    Link_Count           : BIT_8;
   const bitfield32_t    Xth_Intr             : BIT_8;
         bitfield32_t                         : BIT_8;
}MCD5401_Channel_Init_T;

#endif // MCD5401_H 

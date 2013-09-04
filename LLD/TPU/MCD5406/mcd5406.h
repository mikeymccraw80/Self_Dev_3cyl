#ifndef MCD5406_H
#define MCD5406_H

//=============================================================================
// include files
//=============================================================================
#include "reuse.h"
//=============================================================================
// MCD5406_General_Flags_Tag
//=============================================================================
typedef struct MCD5406_General_Flags_F_Tag
{
   bitfield32_t  General_Flags   :  BIT_8;
   bitfield32_t  Intr_Index      :  BIT_8;
   bitfield32_t  Loop_Counter    : BIT_16;

}  MCD5406_General_Flags_F_T;

typedef union MCD5406_General_Flags_Tag
{
   MCD5406_General_Flags_F_T  F;
   uint32_t                   U32;

}  MCD5406_General_Flags_T;

//=============================================================================
// MCD5406_Array_Parameters_T
//=============================================================================
typedef struct MCD5406_Array_Parameters_F_Tag
{
   bitfield32_t Array_Size       :  BIT_8;
   bitfield32_t                  :  BIT_8;
   bitfield32_t Array_Flags_Buf  :  BIT_8;
   bitfield32_t Index            :  BIT_8;

}  MCD5406_Array_Parameters_F_T;

typedef union MCD5406_Array_Parameters_Tag
{
   MCD5406_Array_Parameters_F_T  F;
   uint32_t                      U32;

}  MCD5406_Array_Parameters_T;

//=============================================================================
// MCD5406_Start_Event_T
//=============================================================================
typedef struct MCD5406_Start_Event_F_Tag
{
   bitfield32_t Start_Flags   :  BIT_8;
   bitfield32_t Start_Event   : BIT_24;

}  MCD5406_Start_Event_F_T;

typedef union MCD5406_Start_Event_Tag
{
   MCD5406_Start_Event_F_T    F;
   uint32_t                   U32;

}  MCD5406_Start_Event_T;

//=============================================================================
// MCD5406_End_Event_T
//=============================================================================
typedef struct MCD5406_End_Event_F_Tag
{
   bitfield32_t End_Flags  :  BIT_8;
   bitfield32_t End_Event  : BIT_24;

}  MCD5406_End_Event_F_T;

typedef union MCD5406_End_Event_Tag
{
   MCD5406_End_Event_F_T   F;
   uint32_t                U32;

}  MCD5406_End_Event_T;

//=============================================================================
// RQOM Structure
//=============================================================================
typedef volatile struct MCD5406_SDM_Tag
{
   MCD5406_General_Flags_T    General_Flags;
   MCD5406_Array_Parameters_T Array_Parameters;
   MCD5406_Start_Event_T      Start_Event;
   MCD5406_End_Event_T        End_Event;
   
} MCD5406_SDM_T;

#endif // MCD5406_H

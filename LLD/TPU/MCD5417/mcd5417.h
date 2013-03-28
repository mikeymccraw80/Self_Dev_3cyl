#ifndef MCD5417_H
#define MCD5417_H

#include "reuse.h"
#include "dd_tpu.h"

//===========================================================================
// MCD5417_Flags_Start_End_Time_T
//===========================================================================
typedef struct MCD5417_Flags_Start_End_Time_F_Tag
{
   bitfield32_t Normal_Done     : BIT_1;
   bitfield32_t Trim_Done       : BIT_1;
   bitfield32_t Kinj_Active     : BIT_1;
   bitfield32_t Fuel_Active     : BIT_1;
   bitfield32_t MIO_Active      : BIT_1;
   bitfield32_t unused          : BIT_3;
   bitfield32_t Start_End_Time  : BIT_24;
}MCD5417_Flags_Start_End_Time_F_T;

typedef union MCD5417_Flags_Start_End_Time_Tag
{
   MCD5417_Flags_Start_End_Time_F_T    F;
   uint32_t                            U32;
} MCD5417_Flags_Start_End_Time_T;

//=============================================================================
// MCD5417_Fuel_Flag_DFPW_T
//=============================================================================
typedef struct MCD5417_Fuel_Flag_DFPW_F_Tag
{
   bitfield32_t Multiple_Trim  : BIT_1;
   bitfield32_t unused         : BIT_7;
   bitfield32_t DFPW           : BIT_24;
} MCD5417_Fuel_Flag_DFPW_F_T;

typedef union MCD5417_Fuel_Flag_DFPW_Tag
{
   MCD5417_Fuel_Flag_DFPW_F_T          F;
   uint32_t                            U32;
} MCD5417_Fuel_Flag_DFPW_T;

//=============================================================================
// MCD5417_AFPW_T
//=============================================================================
typedef struct MCD5417_AFPW_F_Tag
{
   bitfield32_t unused         : BIT_8;
   bitfield32_t AFPW           : BIT_24;
} MCD5417_AFPW_F_T;

typedef union MCD5417_AFPW_Tag
{
   MCD5417_AFPW_F_T                    F;
   uint32_t U32;
} MCD5417_AFPW_T;

//=============================================================================
// MCD5417_Boundary_Angle_T
//=============================================================================
typedef struct MCD5417_Boundary_Angle_F_Tag
{
   bitfield32_t unused         : BIT_8;
   bitfield32_t Boundary_Angle : BIT_24;
} MCD5417_Boundary_Angle_F_T;

typedef union MCD5417_Boundary_Angle_Tag
{
   MCD5417_Boundary_Angle_F_T          F;
   uint32_t                            U32;
} MCD5417_Boundary_Angle_T;

//=============================================================================
// DESFIE STRUCTURE
//=============================================================================
typedef struct MCD5417_SDM_F_Tag
{
   volatile MCD5417_Flags_Start_End_Time_T    Flags_StartEnd_Time;
   volatile MCD5417_Fuel_Flag_DFPW_T          Fuel_Flag_DFPW;
   volatile MCD5417_AFPW_T                    AFPW;
   volatile MCD5417_Boundary_Angle_T          Boundary_Angle;

}volatile MCD5417_SDM_F_T;

typedef struct MCD5417_SDM_Tag
{
   MCD5417_SDM_F_T            F;
}MCD5417_SDM_T;


//===========================================================================
// Global Variable Externs                                                   
//===========================================================================
extern uint32_t                 DESFIE_Normal_Offset;
extern uint32_t                 DESFIE_Trim_Offset;
extern uint32_t                 DESFIE_Kinj;
extern uint32_t                 DESFIE_Min_Inj_Off;
extern uint32_t                 DESFIE_Min_Trim;
extern uint32_t                 DESFIE_Boundary_Angle;
extern bool                      DESFIE_Multiple_Trim;
extern uint32_t                 DESFIE_DFPW;

#endif // MCD5417_H

#ifndef MCD5402_H
#define MCD5402_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec    :   mcd5402.h %
//
// created_by       :   dz48hg
//
// date_created     :   Mon, Sep 10, 2007 7:57:30 PM
//
// %derived_by       :   mz01yw %
//
// %date_modified    :   Mon, Mar 24, 2008 09:26:30 AM %
//
// %version          :   tci_pt2#3 %
//
//=============================================================================
//
//===========================================================================
// REUSE:                                                                    
// DO NOT MODIFY THIS FILE.  Coordinate any desired changes with the         
// Complex I/O group.                                                        
//                                                                           
//===========================================================================

//===========================================================================
// Exported type declarations (enum, struct, union, typedef)
//===========================================================================

//===========================================================================
// MCD5402_Coherent_Period_Hi_Time_T
//===========================================================================
typedef struct MCD5402_Coherent_Period_Hi_Time_F_Tag
{
   bitfield32_t One_Crit_Edge    :  BIT_1;
   bitfield32_t                  :  BIT_7;
   bitfield32_t Period           : BIT_24;
   bitfield32_t                  :  BIT_8;
   bitfield32_t HighTime         : BIT_24;

}  MCD5402_Coherent_Period_Hi_Time_F_T;

typedef union MCD5402_Coherent_Period_Hi_Time_Tag
{
   MCD5402_Coherent_Period_Hi_Time_F_T   F;
   uint32_t                              U32[2];
   uint64_t                              U64;

}  MCD5402_Coherent_Period_Hi_Time_T;

//===========================================================================
// MCD5402_Coherent_Edge_T
//===========================================================================
typedef struct MCD5402_Coherent_Edge_F_Tag
{
   bitfield32_t Crit_Edge_Cnt_B  :  BIT_8;
   bitfield32_t Crit_Edge_Time   : BIT_24;

}  MCD5402_Coherent_Edge_F_T;

typedef union MCD5402_Coherent_Edge_Tag
{
   MCD5402_Coherent_Edge_F_T   F;
   uint32_t                    U32;

}  MCD5402_Coherent_Edge_T;

//===========================================================================
// MCD5402_NCrit_Edge_T
//===========================================================================
typedef struct MCD5402_NCrit_Edge_Time_F_Tag
{
   bitfield32_t             :  BIT_8;
   bitfield32_t Time        : BIT_24;

}  MCD5402_NCrit_Edge_F_T;

typedef union MCD5402_NCrit_Edge_Time_Tag
{
   MCD5402_NCrit_Edge_F_T    F;
   uint32_t                  U32;

}  MCD5402_NCrit_Edge_T;

//===========================================================================
// MCD5402_Coherent_Accum_T
//===========================================================================
typedef struct MCD5402_Coherent_Accum_F_Tag
{
   bitfield32_t                   :  BIT_8;
   bitfield32_t Accum_Period      : BIT_24;
   bitfield32_t Crit_Edge_Cnt_A   :  BIT_8;
   bitfield32_t Accum_Hi_Time     : BIT_24;

}  MCD5402_Coherent_Accum_F_T;

typedef union MCD5402_Coherent_Accum_Tag
{
   MCD5402_Coherent_Accum_F_T   F;
   uint32_t                     U32[2];
   uint64_t                     U64;

}  MCD5402_Coherent_Accum_T;

//=============================================================================
// PWMIE Structure
//=============================================================================
typedef volatile struct MCD5402_SDM_Tag
{
   MCD5402_Coherent_Period_Hi_Time_T    Period_Hi_Time;
   MCD5402_Coherent_Edge_T              Crit_Edge_Time_Count;
   MCD5402_NCrit_Edge_T                 NCrit_Edge_Time;
   MCD5402_Coherent_Accum_T             Accum_Time_Count;
} MCD5402_SDM_T;

#endif // MCD5402_H

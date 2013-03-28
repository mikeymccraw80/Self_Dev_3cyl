#ifndef MCD5408_H
#define MCD5408_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec    :   mcd5408.h %
//
// created_by       :   gzdmlz
//
// date_created     :   Wed May 23 15:16:22 2007
//
// %derived_by       :   mz01yw %
//
// %date_modified    :   Mon, Mar 24, 2008 16:10:21 %
//
// %version          :   tci_pt2#6 %
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
// Macro Definitions                                                         
//===========================================================================

#define MCD5408_EDGE_TIME_ARRAY_SIZE       0x40


//=============================================================================
// @enum MCD5408_CAM_Mode_T | CAM Backup or normal mode.
//=============================================================================
typedef enum
{
   MCD5408_CAM_NORMAL_MODE,
   MCD5408_CAM_BACKUP_MODE
} MCD5408_CAM_Mode_T;

//=============================================================================
// @enum MCD5408_HSR_T | HSR types.
//=============================================================================
typedef enum
{
   MCD5408_HSR_UNUSED_0,
   MCD5408_HSR_UNUSED_1,
   MCD5408_HSR_UPDATE,
   MCD5408_HSR_EXIT_BACKUP,
   MCD5408_HSR_REQUEST_BACKUP,
   MCD5408_HSR_INIT,
   MCD5408_HSR_UNUSED_6,
   MCD5408_HSR_SHUTDOWN   
} MCD5408_HSR_T;

//=============================================================================
// @enum MCD_5408_Filter_T | Filter type.
//=============================================================================
typedef enum
{
   MCD5408_SW_MIN_PERIOD,
   MCD5408_HW_MIN_PERIOD   
} MCD_5408_Filter_T;

//=============================================================================
// @enum MCD5408_EDGE_T | Critical Edge type.
//=============================================================================
typedef enum
{
   MCD5408_EDGE_FALLING,
   MCD5408_EDGE_RISING
} MCD5408_EDGE_T;

//=============================================================================
// @enum MCD5408_TCR2_Option_T | TCR2 angle mode options.
//=============================================================================
typedef enum
{
   MCD5408_TCR2_TIME_MODE,
   MCD5408_TCR2_ANGLE_MODE,
   MCD5408_TCR2_EDGE_COUNT_MODE
} MCD5408_TCR2_Option_T;

//=============================================================================
// @enum MCD5408_TCR_Select_T | TCR select.
//=============================================================================
typedef enum
{
   MCD5408_TIMEBASE_TCR1,
   MCD5408_TIMEBASE_TCR2
} MCD5408_TCR_Select_T;

//=============================================================================
// @enum MCD5408_Gap_Detect_Enable_T | Gap detection enable / disable.
//=============================================================================
typedef enum
{
   MCD5408_GAP_DETECT_DISABLE,
   MCD5408_GAP_DETECT_ENABLE
} MCD5408_Gap_Detect_Enable_T;

//=============================================================================
// @enum MCD5408_Gap_Detect_T | Gap detection method.
//=============================================================================
typedef enum
{
   MCD5408_PERCENT_PERIOD,
   MCD5408_1_X__Y_1
} MCD5408_Gap_Detect_T;

//=============== ==============================================================
// MCD5408_Coherent_Edge_T
//=============================================================================
typedef struct MCD5408_Coherent_Edge_F_Tag
{
   bitfield32_t       :  BIT_8;
   bitfield32_t Time  : BIT_24;
   bitfield32_t       : BIT_16;
   bitfield32_t Count : BIT_16;

}  MCD5408_Coherent_Edge_F_T;

typedef union MCD5408_Coherent_Edge_Tag
{
   MCD5408_Coherent_Edge_F_T  F;
   uint32_t                   U32[2];
   uint64_t                   U64;

}  MCD5408_Coherent_Edge_T;

//=============================================================================
// MCD5408_24bit_Time_T
//=============================================================================
typedef struct MCD5408_24bit_Time_F_Tag
{
   bitfield32_t             :  BIT_8;
   bitfield32_t Time        : BIT_24;

}  MCD5408_24bit_Time_F_T;

typedef union MCD5408_24bit_Time_Tag
{
   MCD5408_24bit_Time_F_T   F;
   uint32_t                U32;

}  MCD5408_24bit_Time_T;

//=============================================================================
// MCD5408_Options_T
//=============================================================================
typedef struct MCD5408_Options_F_Tag
{
   bitfield32_t  Min_Period_Method      :  BIT_1;
   bitfield32_t  Gap_Detect_Method    :  BIT_1;
   bitfield32_t  Gap_Detect_Enabled    :  BIT_1;
   bitfield32_t  Period_Calc_Enabled     :  BIT_1;
   bitfield32_t  Critical_Edge                :  BIT_1;
   bitfield32_t  Period_Calc_2_Enabled  :  BIT_1;
   bitfield32_t  Period_Avg_Enabled     :  BIT_1;
   bitfield32_t                                   :  BIT_1;  // unused - 1 more flags available
   bitfield32_t  TCR2_Option               :  BIT_8;
   bitfield32_t  Min_Period                   :  BIT_16;

}  MCD5408_Options_F_T;

typedef union MCD5408_Options_Tag
{
   MCD5408_Options_F_T  F;
   uint32_t             U32;

}  MCD5408_Options_T;

//=============================================================================
// MCD5408_Flags_T
//=============================================================================
typedef struct MCD5408_Flags_F_Tag
{
   bitfield32_t  Synthetic_Edge_Occurred    :  BIT_1;
   bitfield32_t  Over_Two_Pulses               :  BIT_1;
   bitfield32_t  Two_Pulses                        :  BIT_1;
   bitfield32_t  Tooth_2_After_Gap            :  BIT_1;
   bitfield32_t  Gap_Detect_Delay              :  BIT_1;
   bitfield32_t  Match_Flag                        :  BIT_1;
   bitfield32_t                                         :  BIT_2; // unused 
   bitfield32_t  Remaining_Synthetic_Teeth : BIT_24;

}  MCD5408_Flags_F_T;

typedef union MCD5408_Flags_Tag
{
   MCD5408_Flags_F_T F;
   uint32_t          U32;

}  MCD5408_Flags_T;

//=============================================================================
// MCD5408_Critical_Array_T
//=============================================================================
typedef struct MCD5408_Critical_Array_F_Tag
{
   bitfield32_t In_The_Gap  : BIT_1;
   bitfield32_t                    : BIT_7;
   bitfield32_t Time            : BIT_24;

}  MCD5408_Critical_Array_F_T;

typedef union MCD5408_Critical_Array_Tag
{
   MCD5408_Critical_Array_F_T F;
   uint32_t                   U32;

}  MCD5408_Critical_Array_T;

//=============================================================================
// MCD5408_Link_Count_T
//=============================================================================
typedef struct MCD5408_Link_Count_F_Tag
{
   bitfield32_t  Count_1 :  BIT_8;
   bitfield32_t  Start_1 :  BIT_8;
   bitfield32_t  Count_2 :  BIT_8;
   bitfield32_t  Start_2 :  BIT_8;

}  MCD5408_Link_Count_F_T;

typedef union MCD5408_Link_Count_Tag
{
   MCD5408_Link_Count_F_T  F;
   uint32_t                U32;

} MCD5408_Link_Count_T;

//=============================================================================
// MCD5408_Links_T
//=============================================================================
typedef struct MCD5408_Links_F_Tag
{
   bitfield32_t  Array_Mask   :  BIT_8;
   bitfield32_t  Link_Pointer : BIT_24;

}  MCD5408_Links_F_T;

typedef union MCD5408_Links_Tag
{
   MCD5408_Links_F_T   F;
   uint32_t          U32;

}  MCD5408_Links_T;

///=============================================================================
// MCD5408_IRQ_Enable_T
//=============================================================================
typedef struct MCD5408_IRQ_Enable_F_Tag
{
   bitfield32_t  IRQ_Enable_Edge_Rejected    :  BIT_1;
   bitfield32_t  IRQ_Enable_Gap_Detected     :  BIT_1;
   bitfield32_t  IRQ_Enable_1                :  BIT_1;
   bitfield32_t  IRQ_Enable_2                :  BIT_1;
   bitfield32_t  IRQ_Enable_3                :  BIT_1;
   bitfield32_t  IRQ_Enable_4                :  BIT_1;
   bitfield32_t  IRQ_Enable_Change_Dir       :  BIT_1;
   bitfield32_t                              :  BIT_1;    //unused
   bitfield32_t  Time                        :  BIT_24;

}  MCD5408_IRQ_Enable_F_T;

typedef union MCD5408_IRQ_Enable_Tag
{
   MCD5408_IRQ_Enable_F_T   F;
   uint8_t                  U8[4];
   uint32_t                 U32;

}  MCD5408_IRQ_Enable_T;

//=============================================================================
// MCD5408_IRQ_Request_T
//=============================================================================
typedef struct MCD5408_IRQ_Request_F_Tag
{
   bitfield32_t  IRQ_Request_Edge_Rejected   :  BIT_1;
   bitfield32_t  IRQ_Request_Gap_Detected    :  BIT_1;
   bitfield32_t  IRQ_Request_1               :  BIT_1;
   bitfield32_t  IRQ_Request_2               :  BIT_1;
   bitfield32_t  IRQ_Request_3               :  BIT_1;
   bitfield32_t  IRQ_Request_4               :  BIT_1;
   bitfield32_t  IRQ_Request_Change_Dir      :  BIT_1;
   bitfield32_t                              :  BIT_1;    //unused
   bitfield32_t  Time                        :  BIT_24;

}  MCD5408_IRQ_Request_F_T;

typedef union MCD5408_IRQ_Request_Tag
{
   MCD5408_IRQ_Request_F_T F;
   uint8_t                 U8[4];
   uint32_t                U32;

}  MCD5408_IRQ_Request_T;

//=============================================================================
// MCD5408_IRQ_T
//=============================================================================
typedef struct MCD5408_IRQ_F_Tag
{
   bitfield32_t                :  BIT_8;
   bitfield32_t  Time          : BIT_24;

}  MCD5408_IRQ_F_T;

typedef union MCD5408_IRQ_Tag
{
   MCD5408_IRQ_F_T   F;
   uint32_t          U32;

}  MCD5408_IRQ_T;


//=============================================================================
// MCD5408_DirCrank_Param_T
//=============================================================================
typedef struct MCD5408_DirCrank_Param_F_Tag
{
   bitfield32_t  Reverse_Detect_Enable  :  BIT_1;
   bitfield32_t  Reverse_Process_Enable  :  BIT_1;
   bitfield32_t  LS_Gap_Detect_Disable  :  BIT_1;
   bitfield32_t                                    :  BIT_5;
   bitfield32_t  PW_Threshold              : BIT_24;

}  MCD5408_DirCrank_Param_F_T;

typedef union MCD5408_DirCrank_Param_Tag
{
   MCD5408_DirCrank_Param_F_T   F;
   uint32_t          U32;

}  MCD5408_DirCrank_Param_T;


//=============================================================================
// MCD5408_DirCrank_FlagsPW_T
//=============================================================================
typedef struct MCD5408_DirCrank_FlagsPW_F_Tag
{
   bitfield32_t  Crank_Backwards  :  BIT_1;
   bitfield32_t                           :  BIT_7;
   bitfield32_t  Dir_Crank_PW      : BIT_24;

}  MCD5408_DirCrank_FlagsPW_F_T;

typedef union MCD5408_DirCrank_FlagsPW_Tag
{
   MCD5408_DirCrank_FlagsPW_F_T   F;
   uint32_t          U32;

}  MCD5408_DirCrank_FlagsPW_T;

//=============================================================================
// MCD5408_DirCountEdge_T
//=============================================================================
typedef struct MCD5408_DirCountEdge_F_Tag
{
   bitfield32_t  Chg_Dir_Count  :  BIT_8;
   bitfield32_t                         :  BIT_8;
   bitfield32_t  Accum_Edges    : BIT_16;

}  MCD5408_DirCountEdge_F_T;

typedef union MCD5408_DirCountEdge_Tag
{
   MCD5408_DirCountEdge_F_T   F;
   uint32_t          U32;

}  MCD5408_DirCountEdge_T;


//=============================================================================
// MCD5408_RevCountEdge_T
//=============================================================================
typedef struct MCD5408_RevCountEdge_F_Tag
{
   bitfield32_t  Abs_Edge_Count         :  BIT_8;
   bitfield32_t                         :  BIT_8;
   bitfield32_t  Accum_Reverse_Edges    : BIT_16;

}  MCD5408_RevCountEdge_F_T;

typedef union MCD5408_RevCountEdge_Tag
{
   MCD5408_RevCountEdge_F_T   F;
   uint32_t          U32;

}  MCD5408_RevCountEdge_T;


//=============================================================================
// MCD5408_IRQ_Backups_T
//=============================================================================
typedef struct MCD5408_IRQ_Backups_F_Tag
{
   bitfield32_t  Backups_Left     :  BIT_8;
   bitfield32_t  Time             : BIT_24;

}  MCD5408_IRQ_Backups_F_T;

typedef union
{
   MCD5408_IRQ_Backups_F_T F;
   uint32_t                U32;

}  MCD5408_IRQ_Backups_T;

//=============================================================================
// MCD5408_Backup_T
//=============================================================================
typedef struct MCD5408_Backups_F_Tag
{
   bitfield32_t  Between_Cams     :  BIT_8;
   bitfield32_t  First_Edge_Time  : BIT_24;

}  MCD5408_Backups_F_T;

typedef union
{
   MCD5408_Backups_F_T  F;
   uint32_t             U32;

}  MCD5408_Backup_T;


//=============================================================================
// EPPE Structure
//=============================================================================
typedef volatile struct MCD5408_SDM_Tag
{
   MCD5408_Coherent_Edge_T    Real_Coherent_Edge;
   MCD5408_24bit_Time_T          Real_Period;
   MCD5408_24bit_Time_T          Real_Edg_Time_NF;
   MCD5408_Coherent_Edge_T    Critical_Coherent_Edge;
   MCD5408_24bit_Time_T          Period;
   MCD5408_Options_T               Options;
   MCD5408_Flags_T                   Flags;
   MCD5408_24bit_Time_T          Real_Prev_Period;
   uint16_t                                 Previous_Y_1_Count;
   uint16_t                                 Previous_1_X_Count;
   uint8_t                                   Mult_1_X;
   uint8_t                                   Mult_Y_1;
   uint8_t                                   Percent_Multiplier;
   uint8_t                                   Filter_Delay;
   uint8_t                                   Unused0;
   uint8_t                                   Gap_Size;
   uint16_t                                 Gap_Count;
   uint16_t                                 Gap_2_Fmult;
   uint16_t                                 Gap_Fmult;
   uint16_t                                 Gap_Detect_Count;
   uint16_t                                 TCR2_Error_Count;
   uint32_t                                 Cam_History;
   MCD5408_Link_Count_T           Link_Count;
   MCD5408_Links_T                    Links;
   uint16_t                                 Tach_High;
   uint16_t                                 Tach_Low;
   uint16_t                                 Unused1;
   uint16_t                                 Tach_Count;
   MCD5408_IRQ_Enable_T           IRQ_Edge_Time_1;
   MCD5408_IRQ_Request_T         IRQ_Edge_Time_2;
   MCD5408_IRQ_T                      IRQ_Edge_Time_3;
   MCD5408_IRQ_Backups_T         IRQ_Edge_Time_4;
   uint16_t                                  IRQ_Edge_Count_1;
   uint16_t                                  IRQ_Edge_Count_2;
   uint16_t                                  IRQ_Edge_Count_3;
   uint16_t                                 IRQ_Edge_Count_4;
   MCD5408_DirCrank_Param_T     Dir_Crank_Params;
   MCD5408_DirCrank_FlagsPW_T   Dir_Crank_Flags_PW;
   MCD5408_DirCrank_Param_T     Buf_Dir_Crank_Params;
   MCD5408_DirCountEdge_T        DirCount_AccumEdge;
   MCD5408_RevCountEdge_T      AbsEdgeCount_AccumRevEdge;
   MCD5408_Backup_T                Backup;
   MCD5408_Critical_Array_T        Critical_Array[MCD5408_EDGE_TIME_ARRAY_SIZE]; // Array can be any size

}  MCD5408_SDM_T;

#endif // MCD5408_H

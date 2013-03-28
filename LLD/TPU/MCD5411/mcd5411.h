#ifndef MCD5411_H
#define MCD5411_H

#include "reuse.h"
#include "dd_tpu.h"

//===========================================================================
// MCD5411_Prev_Crit_ET_And_Flags_T
//===========================================================================
typedef struct  MCD5411_Prev_Crit_ET_And_Flags_F_Tag
{
   bitfield32_t Coherent_2     :  BIT_1;
   bitfield32_t                :  BIT_5;
   bitfield32_t Last_Edge_Crit :  BIT_1;
   bitfield32_t Timeout        :  BIT_1;
   bitfield32_t Prev_Crit_ET   :  BIT_24;

}  MCD5411_Prev_Crit_ET_And_Flags_F_T;
   
typedef union
{
   MCD5411_Prev_Crit_ET_And_Flags_F_T   F;
   uint32_t                             U32;

}  MCD5411_Prev_Crit_ET_And_Flags_T;

//===========================================================================
// MCD5411_Crit_Ecnt_T
//===========================================================================
typedef struct MCD5411_Crit_Ecnt_F_Tag
{
   bitfield32_t             :  BIT_8;
   bitfield32_t Crit_Ecnt   :  BIT_24;

}  MCD5411_Crit_Ecnt_F_T;

typedef union MCD5411_Crit_Ecnt_Tag
{
   MCD5411_Crit_Ecnt_F_T   F;
   uint32_t                U32;

}  MCD5411_Crit_Ecnt_T;

//===========================================================================
// MCD5411_Crit_ET_T
//===========================================================================
typedef struct MCD5411_Crit_ET_F_Tag
{
   bitfield32_t            :  BIT_8;
   bitfield32_t Crit_ET    :  BIT_24;

}  MCD5411_Crit_ET_F_T;

typedef union MCD5411_Crit_ET_Tag
{
   MCD5411_Crit_ET_F_T  F;
   uint32_t             U32;

}  MCD5411_Crit_ET_T;

//===========================================================================
// MCD5411_Period_And_Noise_Cnt_T
//===========================================================================
typedef struct MCD5411_Period_And_Noise_Cnt_F_Tag
{
   bitfield32_t Noise_Cnt  :  BIT_8;
   bitfield32_t Period     :  BIT_24;

}  MCD5411_Period_And_Noise_Cnt_F_T;

typedef union MCD5411_Period_And_Noise_Cnt_Tag
{
   MCD5411_Period_And_Noise_Cnt_F_T   F;
   uint32_t                           U32;

}  MCD5411_Period_And_Noise_Cnt_T;

//===========================================================================
// MCD5411_Crit_TCR2_T
//===========================================================================
typedef struct MCD5411_Crit_TCR2_F_Tag
{
   bitfield32_t            :  BIT_8;
   bitfield32_t Crit_TCR2  :  BIT_24;

}  MCD5411_Crit_TCR2_F_T;

typedef union MCD5411_Crit_TCR2_Tag
{
   MCD5411_Crit_TCR2_F_T   F;
   uint32_t                U32;

}  MCD5411_Crit_TCR2_T;

//===========================================================================
// MCD5411_Crank_Cnt_T
//===========================================================================
typedef struct MCD5411_Crank_Cnt_F_Tag
{
   bitfield32_t Prev_Crank_Count    : BIT_16;
   bitfield32_t Crank_Count         : BIT_16;

}  MCD5411_Crank_Cnt_F_T;

typedef union MCD5411_Crank_Cnt_Tag
{
   MCD5411_Crank_Cnt_F_T   F;
   uint32_t                U32;

}  MCD5411_Crank_Cnt_T;

//===========================================================================
// MCD5411_Buff_NCrit_TCR2_T
//===========================================================================
typedef struct MCD5411_Buff_NCrit_TCR2_F_Tag
{
   bitfield32_t                    :  BIT_8;
   bitfield32_t Buff_NCrit_TCR2    :  BIT_24;

}  MCD5411_Buff_NCrit_TCR2_F_T;

typedef union MCD5411_Buff_NCrit_TCR2_Tag
{
   MCD5411_Buff_NCrit_TCR2_F_T    F;
   uint32_t                      U32;

}  MCD5411_Buff_NCrit_TCR2_T;

//===========================================================================
// MCD5411_Buff_NCrit_ET_And_Flag_T
//===========================================================================
typedef struct MCD5411_Buff_NCrit_ET_And_Flag_F_Tag
{
   bitfield32_t Coherent_1      :  BIT_1;
   bitfield32_t                 :  BIT_7;
   bitfield32_t Buff_NCrit_ET   :  BIT_24;

}  MCD5411_Buff_NCrit_ET_And_Flag_F_T;

typedef union MCD5411_Buff_NCrit_ET_And_Flag_Tag
{
   MCD5411_Buff_NCrit_ET_And_Flag_F_T  F;
   uint32_t                            U32;

}  MCD5411_Buff_NCrit_ET_And_Flag_T;

//===========================================================================
// MCD5411_Ncrit_Ecnt_And_Flag_T
//===========================================================================
typedef struct MCD5411_Ncrit_Ecnt_And_Flag_F_Tag
{
   bitfield32_t  Coherent_2   :  BIT_1;
   bitfield32_t               :  BIT_7;
   bitfield32_t  Ncrit_Ecnt   :  BIT_24;

}  MCD5411_Ncrit_Ecnt_And_Flag_F_T;

typedef union MCD5411_Ncrit_Ecnt_Tag
{
   MCD5411_Ncrit_Ecnt_And_Flag_F_T  F;
   uint32_t                         U32;

}  MCD5411_Ncrit_Ecnt_And_Flag_T;

//===========================================================================
// MCD5411_Ncrit_ET_And_Flag_T
//===========================================================================
typedef struct MCD5411_Ncrit_ET_And_Flag_F_Tag
{
   bitfield32_t Rep_Out_En     :  BIT_1; 
   bitfield32_t                :  BIT_5;
   bitfield32_t NCrit_IRQ_En   :  BIT_1;
   bitfield32_t Crit_IRQ_En    :  BIT_1;
   bitfield32_t NCrit_ET       :  BIT_24;

}  MCD5411_Ncrit_ET_And_Flag_F_T;

typedef union MCD5411_Ncrit_ET_And_Flag_Tag
{
   MCD5411_Ncrit_ET_And_Flag_F_T        F;
   uint32_t                             U32;

}  MCD5411_Ncrit_ET_And_Flag_T;

//===========================================================================
// MCD5411_NCrit_TCR2_T
//===========================================================================
typedef struct MCD5411_NCrit_TCR2_And_Flag_F_Tag
{
   bitfield32_t Coherent_1    :  BIT_1;
   bitfield32_t               :  BIT_7;
   bitfield32_t NCrit_TCR2    :  BIT_24;

}  MCD5411_NCrit_TCR2_And_Flag_F_T;

typedef union MCD5411_NCrit_TCR2_And_Flag_Tag
{
   MCD5411_NCrit_TCR2_And_Flag_F_T   F;
   uint32_t                 U32;

}  MCD5411_NCrit_TCR2_And_Flag_T;


//===========================================================================
// CAME STRUCTURE
//===========================================================================
typedef struct MCD5411_SDM_F_Tag
{
   volatile MCD5411_Prev_Crit_ET_And_Flags_T     Prev_Crit_ET_And_Flags;
   volatile MCD5411_Crit_Ecnt_T                  Crit_Ecnt;
   volatile MCD5411_Crit_ET_T                    Crit_ET;
   volatile MCD5411_Period_And_Noise_Cnt_T       Period_And_Noise_Cnt;
   volatile MCD5411_Crit_TCR2_T                  Prev_Crit_TCR2;
   volatile MCD5411_Crit_TCR2_T                  Crit_TCR2;
   volatile MCD5411_Crank_Cnt_T                  Crank_Cnt;
   volatile MCD5411_Buff_NCrit_TCR2_T            Buff_NCrit_TCR2;
   volatile MCD5411_Crank_Cnt_T                  Buff_NCrit_Crank_Cnt;
   volatile MCD5411_Buff_NCrit_ET_And_Flag_T     Buff_NCrit_ET_And_Flag;
   volatile MCD5411_Ncrit_Ecnt_And_Flag_T        Ncrit_Ecnt_And_Flag;
   volatile MCD5411_Ncrit_ET_And_Flag_T          Ncrit_ET_And_Flag;
   volatile MCD5411_Crank_Cnt_T                  NCrit_Crank_Cnt;
   volatile MCD5411_NCrit_TCR2_And_Flag_T        NCrit_TCR2_And_Flag;

}  MCD5411_SDM_F_T;

typedef union MCD5411_SDM_Tag
{
   MCD5411_SDM_F_T   F;
   uint32_t          U32[sizeof(MCD5411_SDM_F_T)/sizeof(uint32_t)];

}  MCD5411_SDM_T;

//===========================================================================
// Channel Init paramters
//===========================================================================
typedef struct MCD5411_Channel_Init_Tag
{
   const bitfield32_t    Crit_IRQ_Enable      :  BIT_1;
   const bitfield32_t    Non_Crit_IRQ_Enable  :  BIT_1;
   const bitfield32_t    Rep_Enable           :  BIT_1;
   const bitfield32_t    Rep_Out_Inv          :  BIT_1;
   const bitfield32_t    HSR_Initialize       :  BIT_1;
   const bitfield32_t    Use_TCR2             :  BIT_1;
   const bitfield32_t                         :  BIT_26;
   const bitfield32_t    Rep_Channel          :  BIT_8;
   const bitfield32_t    Rep_Lag_Time         :  BIT_24;

}  MCD5411_Channel_Init_T;

//===========================================================================
// Global Variable Externs                                                   
//===========================================================================
extern uint8_t                 MCD5411_Rep_Channel_Num;

#endif // MCD5411_H 

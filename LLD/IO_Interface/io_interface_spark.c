//=============================================================================
// include files
//=============================================================================
#include "hal_spark.h"
#include"io_config_spark.h"
#include "io_config_vsep.h"
#include "dd_vsep_est_select.h"
#include "hwiocald.h"
#include "HLS.h"

//=============================================================================
// Chery spark Marco define
//=============================================================================
#define Convert_Chery_Ign_Width(value,prec) (uint16_t)(((uint32_t)value *(2<<(prec-1)))/1000)

//=============================================================================
// IO_Spark_Syn_Init
//=============================================================================
void  IO_Spark_Syn_Init(void)
{
    T_MILLISECONDSb dwell_time;
    int i;
    SetHWIO_MinDwell(KfSPRK_t_CrankMinDwellInit);
    SetHWIO_MaxDwell(KfSPRK_t_CrankMaxDwellInit);
    for (i=0; i < 4; i ++)
        SetHWIO_MainPulse_DwellTime(i, V_MILLISECONDSb(4));
    // VSEP_EST_Set_PF_Mode(VSEP_INDEX_0,VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED);
    VSEP_EST_Set_PF_Mode(VSEP_INDEX_0,VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED);
    SPARK_Set_Enable( true);

}
//=============================================================================
// IO_Spark_Syn_Update
//=============================================================================
void IO_Spark_Syn_Update(void)
{
    uint8_t counter;
    T_MILLISECONDSb dwell_time, break_time;
    T_ANGLEa spark_angle;

    // set spark channel A
    SetHWIO_Spark_State(LLD_IGN_CHANNEL_A, ign_enable.B_ign_A);
    SetHWIO_Spark_ExtraPulse_Count(LLD_IGN_CHANNEL_A, ign_sig[LLD_IGN_CHANNEL_A].follow_up_sparks);
    spark_angle =(( ign_sig[LLD_IGN_CHANNEL_A].ign_angle<<S_ANGLEa)*3)/4;
    SetHWIO_SpkAngle(LLD_IGN_CHANNEL_A, spark_angle);
    if (ign_sig[LLD_IGN_CHANNEL_A].follow_up_sparks > 0) {
		dwell_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_A].dwell_time_of_follow_up_sparks,S_MILLISECONDSb);
		break_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_A].break_time_of_follow_up_sparks,S_MILLISECONDSb);
		SetHWIO_ExtraPulse1_DwellTime(LLD_IGN_CHANNEL_A, break_time, dwell_time);
        if (ign_sig[LLD_IGN_CHANNEL_A].follow_up_sparks == 2)
            SetHWIO_ExtraPulse2_DwellTime(LLD_IGN_CHANNEL_A, break_time, dwell_time);
    }
	dwell_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_A].dwell_time,S_MILLISECONDSb);
	SetHWIO_MainPulse_DwellTime(LLD_IGN_CHANNEL_A, dwell_time);

    // set spark channel B
    SetHWIO_Spark_State(LLD_IGN_CHANNEL_B, ign_enable.B_ign_B);
    SetHWIO_Spark_ExtraPulse_Count(LLD_IGN_CHANNEL_B, ign_sig[LLD_IGN_CHANNEL_B].follow_up_sparks);
    spark_angle =(( ign_sig[LLD_IGN_CHANNEL_B].ign_angle<<S_ANGLEa)*3)/4;
    SetHWIO_SpkAngle(LLD_IGN_CHANNEL_B, spark_angle);
    if (ign_sig[LLD_IGN_CHANNEL_B].follow_up_sparks > 0) {
		dwell_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_B].dwell_time_of_follow_up_sparks,S_MILLISECONDSb);
		break_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_B].break_time_of_follow_up_sparks,S_MILLISECONDSb);
		SetHWIO_ExtraPulse1_DwellTime(LLD_IGN_CHANNEL_B, break_time, dwell_time);
        if (ign_sig[LLD_IGN_CHANNEL_B].follow_up_sparks == 2)
            SetHWIO_ExtraPulse2_DwellTime(LLD_IGN_CHANNEL_B, break_time, dwell_time);
    }
	dwell_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_B].dwell_time,S_MILLISECONDSb);
	SetHWIO_MainPulse_DwellTime(LLD_IGN_CHANNEL_B, dwell_time);

    // set spark channel C
    SetHWIO_Spark_State(LLD_IGN_CHANNEL_C, ign_enable.B_ign_C);
    SetHWIO_Spark_ExtraPulse_Count(LLD_IGN_CHANNEL_C, ign_sig[LLD_IGN_CHANNEL_C].follow_up_sparks);
    spark_angle =(( ign_sig[LLD_IGN_CHANNEL_C].ign_angle<<S_ANGLEa)*3)/4;
    SetHWIO_SpkAngle(LLD_IGN_CHANNEL_C, spark_angle);
    if (ign_sig[LLD_IGN_CHANNEL_C].follow_up_sparks > 0) {
		dwell_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_C].dwell_time_of_follow_up_sparks,S_MILLISECONDSb);
		break_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_C].break_time_of_follow_up_sparks,S_MILLISECONDSb);
		SetHWIO_ExtraPulse1_DwellTime(LLD_IGN_CHANNEL_C, break_time, dwell_time);
        if (ign_sig[LLD_IGN_CHANNEL_C].follow_up_sparks == 2)
            SetHWIO_ExtraPulse2_DwellTime(LLD_IGN_CHANNEL_C, break_time, dwell_time);
    }
	dwell_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_C].dwell_time,S_MILLISECONDSb);
	SetHWIO_MainPulse_DwellTime(LLD_IGN_CHANNEL_C, dwell_time);

    // set spark channel D
    SetHWIO_Spark_State(LLD_IGN_CHANNEL_D, ign_enable.B_ign_D);
    SetHWIO_Spark_ExtraPulse_Count(LLD_IGN_CHANNEL_D, ign_sig[LLD_IGN_CHANNEL_D].follow_up_sparks);
    spark_angle =(( ign_sig[LLD_IGN_CHANNEL_D].ign_angle<<S_ANGLEa)*3)/4;
    SetHWIO_SpkAngle(LLD_IGN_CHANNEL_D, spark_angle);
    if (ign_sig[LLD_IGN_CHANNEL_D].follow_up_sparks > 0) {
		dwell_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_D].dwell_time_of_follow_up_sparks,S_MILLISECONDSb);
		break_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_D].break_time_of_follow_up_sparks,S_MILLISECONDSb);
		SetHWIO_ExtraPulse1_DwellTime(LLD_IGN_CHANNEL_D, break_time, dwell_time);
        if (ign_sig[LLD_IGN_CHANNEL_D].follow_up_sparks == 2)
            SetHWIO_ExtraPulse2_DwellTime(LLD_IGN_CHANNEL_D, break_time, dwell_time);
    }
	dwell_time = Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_D].dwell_time,S_MILLISECONDSb);
	SetHWIO_MainPulse_DwellTime(LLD_IGN_CHANNEL_D, dwell_time);
}

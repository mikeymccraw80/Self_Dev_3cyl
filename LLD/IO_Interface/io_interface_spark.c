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
    SetHWIO_MinDwell(KfSPRK_t_CrankMinDwellInit);
    SetHWIO_MaxDwell(KfSPRK_t_CrankMaxDwellInit);
    SetHWIO_DwellTime(V_MILLISECONDSb(4));
    VSEP_EST_Set_PF_Mode(VSEP_INDEX_0,VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED);
    SPARK_Set_Enable( true);

}
//=============================================================================
// IO_Spark_Syn_Update
//=============================================================================
void  IO_Spark_Syn_Update(void)
{
    uint8_t counter;
    T_MILLISECONDSb dwell_time;
    T_ANGLEa spark_angle[4];

    //  SPARK_Set_Enable( true);
    for(counter =0; counter<4; counter++) {
        spark_angle[counter] =(( ign_sig[counter].ign_angle<<S_ANGLEa)*3)/4;
    }
    SetHWIO_SpkAngle(spark_angle);

    // Chery requirement: If the dwell time is set to zero, disable the spark
    if (ign_sig[LLD_IGN_CHANNEL_A].dwell_time != 0) {

        dwell_time =  Convert_Chery_Ign_Width(ign_sig[LLD_IGN_CHANNEL_A].dwell_time,S_MILLISECONDSb);
        SetHWIO_DwellTime(dwell_time);
    } else {
        SetHWIO_DwellTime(0);
    }

    // realize the enable interface
    switch (LLD_cyl_num) {
    case CYLINDER_0:
        if (ign_enable.B_ign_A == 0)
            SetHWIO_DwellTime(0);
        break;
    case CYLINDER_1:
        if (ign_enable.B_ign_B == 0)
            SetHWIO_DwellTime(0);
        break;
    case CYLINDER_2:
        if (ign_enable.B_ign_C == 0)
            SetHWIO_DwellTime(0);
        break;
        break;
    case CYLINDER_3:
        if (ign_enable.B_ign_D == 0)
            SetHWIO_DwellTime(0);
        break;
    default:
        break;
    }
}



/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
/*None*/


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "v_esc.h"
#include "es_types.h"
#include "esc_cal.h"




/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local type declarations.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */

/*  -------------------------------------------------  *\
 *  system initialisation
\*  -------------------------------------------------  */
const  bool                       K_ESC_Enable = true;
/*
*| esc_cal.{
*|    K_ESC_Enable{
*|       :is_calconst;
*|       :units = "BOOLEAN";
*|       :description = "enable ESC Detection";
*|    }
*| }
*/



const Volt0to5Volts_W                     K_ADESC_Min_Threshold= FixDefConst( 0.1, Volt0to5Volts_W );
/*
*| esc_cal.{
*|    K_ADESC_Min_Threshold
*|    {
*|       :is_calconst;
*|       :description = "ADESC_Min_Threshold";
*|       :units = "Volt";
*|       :type = types.Volt0to5Volts_W;
*|    }
*| }
*/

const Multiplier_0_to_2                     K_ADESC_Scl_Multi= FixDefConst( 1.0, Multiplier_0_to_2 ) ;
/*
*| esc_cal.{
*|    K_ADESC_Scl_Multi
*|    {
*|       :is_calconst;
*|       :description = "ADESC multipiler scl";
*|       :units = "scl";
*|       :type = types.Multiplier_0_to_2;
*|    }
*| }
*/

/*--------------------------------*\
 *---  Knock Window Placement  ---*
\*--------------------------------*/

const T_MILLISECONDSb FSTPWD[RPM_400to6400by400_Steps] =
{
    FixDefConst( 3.700, T_MILLISECONDSb ),      /* RPM_400  */
    FixDefConst( 3.700, T_MILLISECONDSb ),      /* RPM_800  */
    FixDefConst( 3.700, T_MILLISECONDSb ),      /* RPM_1200 */
    FixDefConst( 3.700, T_MILLISECONDSb ),      /* RPM_1600 */
    FixDefConst( 2.502, T_MILLISECONDSb ),      /* RPM_2000 */
    FixDefConst( 2.006, T_MILLISECONDSb ),      /* RPM_2400 */
    FixDefConst( 1.900, T_MILLISECONDSb ),      /* RPM_2800 */
    FixDefConst( 1.900, T_MILLISECONDSb ),      /* RPM_3200 */
    FixDefConst( 1.450, T_MILLISECONDSb ),      /* RPM_3600 */
    FixDefConst( 1.350, T_MILLISECONDSb ),      /* RPM_4000 */
    FixDefConst( 1.998, T_MILLISECONDSb ),      /* RPM_4400 */
    FixDefConst( 1.998, T_MILLISECONDSb ),      /* RPM_4800 */
    FixDefConst( 0.900, T_MILLISECONDSb ),      /* RPM_5200 */
    FixDefConst( 0.847, T_MILLISECONDSb ),      /* RPM_5600 */
    FixDefConst( 0.847, T_MILLISECONDSb ),      /* RPM_6000 */
    FixDefConst( 0.847, T_MILLISECONDSb )       /* RPM_6400 */
} ;
/*
*| esc_cal.{
*|    FSTPWD {
*|       :is_calconst;
*|       :elements:type = types.t_millisecondsb;
*|       :units = "Micro Seconds";
*|       :description = "Knock window length from the start point for a given RPM";
*|       :annotation = types.RPM_400to6400by400_Steps;
*|    }
*| }
*/


const CrankAngleInDeg_W FSTRTWD[kPa_60to100by10_Steps][RPM_400to6400by400_Steps] =
{
    {/* 60_kPa */
        FixDefConst( 5.273, CrankAngleInDeg_W ),      /* RPM_400  */
        FixDefConst( 5.273, CrankAngleInDeg_W ),      /* RPM_800  */
        FixDefConst( 5.273, CrankAngleInDeg_W ),      /* RPM_1200 */
        FixDefConst( 4.570, CrankAngleInDeg_W ),      /* RPM_1600 */
        FixDefConst( 5.273, CrankAngleInDeg_W ),      /* RPM_2000 */
        FixDefConst( 3.867, CrankAngleInDeg_W ),      /* RPM_2400 */
        FixDefConst( 5.273, CrankAngleInDeg_W ),     /* RPM_2800 */
        FixDefConst( 5.273, CrankAngleInDeg_W ),     /* RPM_3200 */
        FixDefConst( 5.273, CrankAngleInDeg_W ),     /* RPM_3600 */
        FixDefConst( 5.273, CrankAngleInDeg_W ),     /* RPM_4000 */
        FixDefConst( 5.273, CrankAngleInDeg_W ),     /* RPM_4400 */
        FixDefConst( 5.273, CrankAngleInDeg_W ),      /* RPM_4800 */
        FixDefConst( 5.273, CrankAngleInDeg_W ),      /* RPM_5200 */
        FixDefConst( 4.570, CrankAngleInDeg_W ),      /* RPM_5600 */
        FixDefConst( 4.570, CrankAngleInDeg_W ),      /* RPM_6000 */
        FixDefConst( 4.570, CrankAngleInDeg_W )      /* RPM_6400 */
    },
    {/* 70_kPa */
        FixDefConst( 8.437, CrankAngleInDeg_W ),      /* RPM_400  */
        FixDefConst( 9.141, CrankAngleInDeg_W ),      /* RPM_800  */
        FixDefConst( 9.141, CrankAngleInDeg_W ),      /* RPM_1200 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),      /* RPM_1600 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),      /* RPM_2000 */
        FixDefConst( 8.086, CrankAngleInDeg_W ),      /* RPM_2400 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),     /* RPM_2800 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),     /* RPM_3200 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),     /* RPM_3600 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),     /* RPM_4000 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),     /* RPM_4400 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),     /* RPM_4800 */
        FixDefConst( 7.031, CrankAngleInDeg_W ),      /* RPM_5200 */
        FixDefConst( 7.031, CrankAngleInDeg_W ),      /* RPM_5600 */
        FixDefConst( 7.031, CrankAngleInDeg_W ),      /* RPM_6000 */
        FixDefConst( 7.031, CrankAngleInDeg_W )       /* RPM_6400 */
    },
    {/* 80_kPa */
        FixDefConst( 13.008, CrankAngleInDeg_W ),      /* RPM_400  */
        FixDefConst( 13.008, CrankAngleInDeg_W ),     /* RPM_800  */
        FixDefConst( 13.008, CrankAngleInDeg_W ),     /* RPM_1200 */
        FixDefConst( 12.656, CrankAngleInDeg_W ),      /* RPM_1600 */
        FixDefConst( 13.008, CrankAngleInDeg_W ),     /* RPM_2000 */
        FixDefConst( 13.008, CrankAngleInDeg_W ),     /* RPM_2400 */
        FixDefConst( 13.008, CrankAngleInDeg_W ),     /* RPM_2800 */
        FixDefConst( 13.008, CrankAngleInDeg_W ),     /* RPM_3200 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_3600 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_4000 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_4400 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_4800 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_5200 */
        FixDefConst( 9.141,   CrankAngleInDeg_W ),     /* RPM_5600 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),     /* RPM_6000 */
        FixDefConst( 9.141, CrankAngleInDeg_W )       /* RPM_6400 */
    },
    {/* 90_kPa */
        FixDefConst( 20.039, CrankAngleInDeg_W ),      /* RPM_400  */
        FixDefConst( 20.039, CrankAngleInDeg_W ),     /* RPM_800  */
        FixDefConst( 20.039, CrankAngleInDeg_W ),     /* RPM_1200 */
        FixDefConst( 17.930, CrankAngleInDeg_W ),     /* RPM_1600 */
        FixDefConst( 17.930, CrankAngleInDeg_W ),     /* RPM_2000 */
        FixDefConst( 17.930, CrankAngleInDeg_W ),     /* RPM_2400 */
        FixDefConst( 16.172, CrankAngleInDeg_W ),     /* RPM_2800 */
        FixDefConst( 14.062, CrankAngleInDeg_W ),     /* RPM_3200 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_3600 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_4000 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_4400 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_4800 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_5200 */
        FixDefConst( 8.086, CrankAngleInDeg_W ),     /* RPM_5600 */
        FixDefConst( 8.086, CrankAngleInDeg_W ),     /* RPM_6000 */
        FixDefConst( 8.086, CrankAngleInDeg_W )       /* RPM_6400 */
    },
    {/* 100_kPa */
        FixDefConst( 21.094, CrankAngleInDeg_W ),      /* RPM_400  */
        FixDefConst( 21.094, CrankAngleInDeg_W ),     /* RPM_800  */
        FixDefConst( 21.094, CrankAngleInDeg_W ),     /* RPM_1200 */
        FixDefConst( 20.039, CrankAngleInDeg_W ),     /* RPM_1600 */
        FixDefConst( 18.984, CrankAngleInDeg_W ),     /* RPM_2000 */
        FixDefConst( 18.984, CrankAngleInDeg_W ),     /* RPM_2400 */
        FixDefConst( 16.875, CrankAngleInDeg_W ),     /* RPM_2800 */
        FixDefConst( 16.875, CrankAngleInDeg_W ),     /* RPM_3200 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_3600 */
        FixDefConst( 10.898, CrankAngleInDeg_W ),     /* RPM_4000 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),     /* RPM_4400 */
        FixDefConst( 9.141, CrankAngleInDeg_W ),     /* RPM_4800 */
        FixDefConst( 8.086, CrankAngleInDeg_W ),     /* RPM_5200 */
        FixDefConst( 7.031, CrankAngleInDeg_W ),     /* RPM_5600 */
        FixDefConst( 7.031, CrankAngleInDeg_W ),     /* RPM_6000 */
        FixDefConst( 7.031, CrankAngleInDeg_W )       /* RPM_6400 */
    }
} ;
/*
*| esc_cal.{
*|    FSTRTWD {
*|       :is_calconst;
*|       :elements:elements:type = types.t_crank_anglea;
*|       :units = "Degrees";
*|       :description = "Knock window START angle : "
*| "the values are defined from -45Deg (BTDC) to 24Deg (ATDC). "
*| "A small value corresponds to early start, "
*| "a large value corresponds to a late start. "
*| "\n WARNING !!! Do not exceed 24 Deg ATDC";
*|       :elements:annotation = types.RPM_400to6400by400_Steps;
*|       :annotation = types.kPa_60to100by10_Steps;
*|    }
*| }
*/


/*  -------------------------------------------------  *\
 *  Enable/disable conditions                          *
\*  -------------------------------------------------  */


const Seconds_Low                   K_ESCEnableRunTime = FixDefConst( 3, Seconds_Low ) ;
/*
*| esc_cal.{
*|    K_ESCEnableRunTime {
*|       :is_calconst;
*|       :type = types.Seconds_Low;
*|       :units = "Seconds";
*|       :description = "Minimum engine run time to enable knock control";
*|    }
*| }
*/


const RPM_W                         K_ESCEnableRPM = FixDefConst( 700.0, RPM_W ) ;
/*  RPM enable threshold for knock logic */
/*  N = E/25 RPM  */
/*
*| esc_cal.{
*|    K_ESCEnableRPM
*|    {
*|       :is_calconst;
*|       :description = "RPM enable threshold for knock logic";
*|       :units = "RPM";
*|       :type = types.RPM_W;
*|    }
*| }
*/

const kPa_B                         K_ESCEnableMAP = FixDefConst( 39.837, kPa_B ) ;
/*  MAP enable threshold for knock logic */
/*  N = (E*2.71104) - 28.05502  */
/*
*| esc_cal.{
*|    K_ESCEnableMAP
*|    {
*|       :is_calconst;
*|       :description = "MAP enable threshold for knock logic";
*|       :units = "kPa";
*|       :type = types.kPa_B;
*|    }
*| }
*/

/*  -------------------------------------------------  *\
 *  PE                            *
\*  -------------------------------------------------  */
const Percent_B K_PE_TPS_Load_Thres_2D[RPM_0to6400by800_Steps] =
{
    FixDefConst( 90.0, Percent_B ), /*--- RPM_0    ---*/
    FixDefConst( 90.0, Percent_B ), /*--- RPM_800  ---*/
    FixDefConst( 90.0, Percent_B ), /*--- RPM_1600 ---*/
    FixDefConst( 90.0, Percent_B ), /*--- RPM_2400 ---*/
    FixDefConst( 90.0, Percent_B ), /*--- RPM_3200 ---*/
    FixDefConst( 90.0, Percent_B ), /*--- RPM_4000 ---*/
    FixDefConst( 90.0, Percent_B ), /*--- RPM_4800 ---*/
    FixDefConst( 90.0, Percent_B ), /*--- RPM_5600 ---*/
    FixDefConst( 90.0, Percent_B )  /*--- RPM_6400 ---*/
} ;
/*
*| esc_cal.{
*|    K_PE_TPS_Load_Thres_2D {
*|       :is_calconst;
*|       :elements:type = types.Percent_B;
*|       :units = "Percent";
*|       :description = "F58: Power Enrichment TPS Load threshold. \n"
*|          "Input RPM-Speed.";
*|       :annotation= types.RPM_0to6400by800_Steps;
*|    }
*| }
*/

const Percent_B                       K_Fuel_TPS_Hysteresis_For_PE = FixDefConst( 3.125, Percent_B ) ;
/*
*| esc_cal.{
*|    K_Fuel_TPS_Hysteresis_For_PE {
*|       :is_calconst;
*|       :type = types.Percent_B;
*|       :units = "Percent";
*|       :description = "KTPSHYS: Throttle hysteresis for power enrichment.";
*|    }
*| }
*/

const Every_4th_Loop_Sec_W   F_PE_Delay_Time_2D[RPM_0to6400by800_Steps] =
{
    FixDefConst( 3.0, Every_4th_Loop_Sec_W ),       /*--- RPM_0    ---*/
    FixDefConst( 3.0, Every_4th_Loop_Sec_W ),       /*--- RPM_800  ---*/
    FixDefConst( 3.0, Every_4th_Loop_Sec_W ),       /*--- RPM_1600 ---*/
    FixDefConst( 15.0, Every_4th_Loop_Sec_W ),       /*--- RPM_2400 ---*/
    FixDefConst( 20.0, Every_4th_Loop_Sec_W ),       /*--- RPM_3200 ---*/
    FixDefConst( 15.0, Every_4th_Loop_Sec_W ),      /*--- RPM_4000 ---*/
    FixDefConst( 3.0, Every_4th_Loop_Sec_W ),      /*--- RPM_4800 ---*/
    FixDefConst( 3.0, Every_4th_Loop_Sec_W ),      /*--- RPM_5600 ---*/
    FixDefConst( 3.0, Every_4th_Loop_Sec_W )       /*--- RPM_6400 ---*/
} ;
/*
*| esc_cal.{
*|    F_PE_Delay_Time_2D {
*|       :is_calconst;
*|       :elements:type = types.Every_4th_Loop_Sec_W;
*|       :units = "Seconds";
*|       :description = "Fxx: Power Enrichment Delay Timer. Input RPM-Speed.";
*|       :annotation= types.RPM_0to6400by800_Steps;
*|    }
*| }
*/

const Every_4th_Loop_Sec_W   F_EveryPE_DelayTime_2D[RPM_0to6400by800_Steps] =
{
    FixDefConst( 0.0, Every_4th_Loop_Sec_W ),       /*--- RPM_0    ---*/
    FixDefConst( 0.0, Every_4th_Loop_Sec_W ),       /*--- RPM_800  ---*/ 
    FixDefConst( 0.0, Every_4th_Loop_Sec_W ),       /*--- RPM_1600 ---*/ 
    FixDefConst( 0.0, Every_4th_Loop_Sec_W ),       /*--- RPM_2400 ---*/ 
    FixDefConst( 0.0, Every_4th_Loop_Sec_W ),       /*--- RPM_3200 ---*/ 
    FixDefConst( 0.0, Every_4th_Loop_Sec_W ),       /*--- RPM_4000 ---*/ 
    FixDefConst( 0.0, Every_4th_Loop_Sec_W ),       /*--- RPM_4800 ---*/ 
    FixDefConst( 0.0, Every_4th_Loop_Sec_W ),       /*--- RPM_5600 ---*/ 
    FixDefConst( 0.0, Every_4th_Loop_Sec_W )        /*--- RPM_6400 ---*/ 
} ;
/*
*| esc_cal.{
*|    F_EveryPE_DelayTime_2D {
*|       :is_calconst;
*|       :elements:type = types.Every_4th_Loop_Sec_W;
*|       :units = "Seconds";
*|       :description = "Fxx: Power Enrichment Delay Timer from TPS above threshold to PE enabled. Input RPM-Speed.";
*|       :annotation= types.RPM_0to6400by800_Steps;
*|    }
*| }
*/
/*  -------------------------------------------------  *\
 *  ESC average calculation                            *
\*  -------------------------------------------------  */

const Filter_Q_W                    K_IntegratorFilterUp = FixDefConst( 0.60, Filter_Q_W ) ;
/*  Integrator filter coefficient for increasing throttle/RPM */
/*  N = E*65536  */
/*
*| esc_cal.{
*|    K_IntegratorFilterUp
*|    {
*|       :is_calconst;
*|       :description = "Integrator filter coefficient for increasing throttle/RPM";
*|       :units = "";
*|       :type = types.Filter_Q_W;
*|    }
*| }
*/

const Filter_Q_W                    K_IntegratorFilterDown = FixDefConst( 0.32, Filter_Q_W ) ;
/*  Integrator filter coefficient for decreasing throttle/RPM */
/*  N = E*65536  */
/*
*| esc_cal.{
*|    K_IntegratorFilterDown
*|    {
*|       :is_calconst;
*|       :description = "Integrator filter coefficient for decreasing throttle/RPM";
*|       :units = "";
*|       :type = types.Filter_Q_W;
*|    }
*| }
*/

const Filter_Q_W                    K_IntegratorFilterSteadyState = FixDefConst( 0.10, Filter_Q_W ) ;
/*  Integrator filter coefficient for steady state throttle/RPM */
/*  N = E*65536  */
/*
*| esc_cal.{
*|    K_IntegratorFilterSteadyState
*|    {
*|       :is_calconst;
*|       :description = "Integrator filter coefficient for steady state throttle/RPM";
*|       :units = "";
*|       :type = types.Filter_Q_W;
*|    }
*| }
*/

const Filter_Q_W                    K_IntegratorFilterKnockMult = FixDefConst( 0.10, Filter_Q_W ) ;
/*  Integrator filter multiplier if knock is present */
/*  N = E*65536  */
/*
*| esc_cal.{
*|    K_IntegratorFilterKnockMult
*|    {
*|       :is_calconst;
*|       :description = "Integrator filter coefficient multiplier if knock is present";
*|       :units = "";
*|       :type = types.Filter_Q_W;
*|    }
*| }
*/

const RPM_W                         K_DeltaRPMIncThreshold = FixDefConst( 100.0, RPM_W ) ;
/*  Engine speed increasing delta threshold for IntAveQ determination */
/*  N = E/12.5 RPM  */
/*
*| esc_cal.{
*|    K_DeltaRPMIncThreshold
*|    {
*|       :is_calconst;
*|       :description = "Engine speed increasing delta threshold for IntAveQ determination";
*|       :units = "RPM";
*|       :type = types.RPM_W;
*|    }
*| }
*/

const RPM_W                         K_DeltaRPMDecThreshold = FixDefConst( 100.0, RPM_W ) ;
/*  Engine speed decreasing delta threshold for IntAveQ determination */
/*  N = E/12.5 RPM  */
/*
*| esc_cal.{
*|    K_DeltaRPMDecThreshold
*|    {
*|       :is_calconst;
*|       :description = "Engine speed decreasing delta threshold for IntAveQ determination";
*|       :units = "RPM";
*|       :type = types.RPM_W;
*|    }
*| }
*/

const TPS_B                         K_DeltaTPSIncThreshold = FixDefConst( 10.0, TPS_B ) ;
/*  Throttle increasing delta threshold for IntAveQ determination */
/*  N = E*256/100 %  */
/*
*| esc_cal.{
*|    K_DeltaTPSIncThreshold
*|    {
*|       :is_calconst;
*|       :description = "Throttle increasing delta threshold for IntAveQ determination";
*|       :units = "%";
*|       :type = types.TPS_B;
*|    }
*| }
*/

const TPS_B                         K_DeltaTPSDecThreshold = FixDefConst( 10.0, TPS_B ) ;
/*  Throttle decreasing delta threshold for IntAveQ determination */
/*  N = E*256/100 % */
/*
*| esc_cal.{
*|    K_DeltaTPSDecThreshold
*|    {
*|       :is_calconst;
*|       :description = "Throttle decreasing delta threshold for IntAveQ determination";
*|       :units = "%";
*|       :type = types.TPS_B;
*|    }
*| }
*/

const Volt0to5Volts_B               K_ESCAverageInit = FixDefConst( 1.914, Volt0to5Volts_B ) ;
/*  ESC Average initialisation value */
/*  N = E*256/5.0 V */
/*
*| esc_cal.{
*|    K_ESCAverageInit
*|    {
*|       :is_calconst;
*|       :description = "ESC Average initialisation value";
*|       :units = "V";
*|       :type = types.Volt0to5Volts_B;
*|    }
*| }
*/

const Volt0to5Volts_B               K_ESCAverageMin = FixDefConst( 0.17578125, Volt0to5Volts_B ) ;
/*  ESC Average minimum value */
/*  N = E*256/5.0 V */
/*
*| esc_cal.{
*|    K_ESCAverageMin
*|    {
*|       :is_calconst;
*|       :description = "ESC Average minimum value";
*|       :units = "V";
*|       :type = types.Volt0to5Volts_B;
*|    }
*| }
*/

/*  -------------------------------------------------  *\
 *  Amplifier gain determination                       *
\*  -------------------------------------------------  */

const Volt0to5Volts_W               K_ESCAverageUppThreshold = FixDefConst( 5.0, Volt0to5Volts_W ) ;
/*  ESC Average upper threshold to decrease the amplifier gain */
/*  N = E*65536/5 V */
/*
*| esc_cal.{
*|    K_ESCAverageUppThreshold
*|    {
*|       :is_calconst;
*|       :description = "ESC Average upper threshold to decrease the amplifier gain";
*|       :units = "V";
*|       :type = types.Volt0to5Volts_W;
*|    }
*| }
*/

const Volt0to5Volts_W               K_ESCAverageLowThreshold = FixDefConst( 5.0, Volt0to5Volts_W ) ;
/*  ESC Average lower threshold to increase the amplifier gain */
/*  N = E*65536/5 V */
/*
*| esc_cal.{
*|    K_ESCAverageLowThreshold
*|    {
*|       :is_calconst;
*|       :description = "ESC Average lower threshold to increase the amplifier gain";
*|       :units = "V";
*|       :type = types.Volt0to5Volts_W;
*|    }
*| }
*/

/*  -------------------------------------------------  *\
 *  MAD determination                                  *
\*  -------------------------------------------------  */

const Filter_Q_W                    K_MADFilterCoefficient = FixDefConst( 0.01, Filter_Q_W ) ;
/*  MAD filter coefficient */
/*  N = E*65536  */
/*
*| esc_cal.{
*|    K_MADFilterCoefficient
*|    {
*|       :is_calconst;
*|       :description = "MAD filter coefficient";
*|       :units = "";
*|       :type = types.Filter_Q_W;
*|    }
*| }
*/

const Volt0to5Volts_W               K_MADMax = FixDefConst( 0.15, Volt0to5Volts_W ) ;
/*  Maximum MAD */
/*  N = E*65536/5.0 V  */
/*
*| esc_cal.{
*|    K_MADMax
*|    {
*|       :is_calconst;
*|       :description = "Maximum MAD";
*|       :units = "V";
*|       :type = types.Volt0to5Volts_W;
*|    }
*| }
*/

const Volt0to5Volts_W               K_MADMin = FixDefConst( 0.1, Volt0to5Volts_W ) ;
/*  Minimum MAD */
/*  N = E*65536/5.0 V  */
/*
*| esc_cal.{
*|    K_MADMin
*|    {
*|       :is_calconst;
*|       :description = "Minimum MAD";
*|       :units = "V";
*|       :type = types.Volt0to5Volts_W;
*|    }
*| }
*/

const RPM_W                         K_MADRPM = FixDefConst( 700.0, RPM_W ) ;
/*  RPM threshold to update MAD */
/*  N = E/25 RPM  */
/*
*| esc_cal.{
*|    K_MADRPM
*|    {
*|       :is_calconst;
*|       :description = "RPM threshold to update MAD";
*|       :units = "RPM";
*|       :type = types.RPM_W;
*|    }
*| }
*/

const kPa_B                         K_MADMAP = FixDefConst( 19.919, kPa_B ) ;
/*  MAP threshold to update MAD */
/*  N = (E*2.71104) - 28.05502  */
/*
*| esc_cal.{
*|    K_MADMAP
*|    {
*|       :is_calconst;
*|       :description = "MAP threshold to update MAD";
*|       :units = "kPa";
*|       :type = types.kPa_B;
*|    }
*| }
*/

const RPM_W                         K_MADDeltaRPM = FixDefConst( 100, RPM_W ) ;
/*  RPM change limit for MAD update */
/*  N = E/12.5 RPM  */
/*
*| esc_cal.{
*|    K_MADDeltaRPM
*|    {
*|       :is_calconst;
*|       :description = "RPM change over threshold for MAD transient mode";
*|       :units = "RPM";
*|       :type = types.RPM_W;
*|    }
*| }
*/

const TPS_B                         K_MADDeltaTPS = FixDefConst( 10.0, TPS_B ) ;
/*  TPS change limit for MAD update */
/*  N = E*256/100 %  */
/*
*| esc_cal.{
*|    K_MADDeltaTPS
*|    {
*|       :is_calconst;
*|       :description = "TPS change limit for MAD update";
*|       :units = "%";
*|       :type = types.TPS_B;
*|    }
*| }
*/

const kPa_Delta                     K_MADDeltaMAP = FixDefConst( 10.0, kPa_Delta ) ;
/*  MAP change limit for MAD update */
/*  N = (E*2.71104)  */
/*
*| esc_cal.{
*|    K_MADDeltaMAP
*|    {
*|       :is_calconst;
*|       :description = "MAP change over 125 ms threshold for MAD transient mode";
*|       :units = "kPa";
*|       :type = types.kPa_Delta;
*|    }
*| }
*/

const Every_10th_Loop_Sec_B         K_MADTransientTime = FixDefConst( 2.0, Every_10th_Loop_Sec_B ) ;
/*  Duration of transient period for MAD update */
/*  N = E/8 ms */
/*
*| esc_cal.{
*|    K_MADTransientTime
*|    {
*|       :is_calconst;
*|       :description = "Duration of transient period for MAD update";
*|       :units = "Seconds";
*|       :type = types.Every_10th_Loop_Sec_B;
*|    }
*| }
*/

/*  -------------------------------------------------  *\
 *  Knock threshold determination                      *
\*  -------------------------------------------------  */

const TPS_B                         K_MADMultiplierDeltaTPS = FixDefConst( 5.078, TPS_B ) ;
/*  TPS change over 13.3 ms limit for MAD offset */
/*  N = E*256/100 %  */
/*
*| esc_cal.{
*|    K_MADMultiplierDeltaTPS
*|    {
*|       :is_calconst;
*|       :description = "TPS change over 15.625 ms limit for MAD offset";
*|       :units = "%";
*|       :type = types.TPS_B;
*|    }
*| }
*/

const Every_2nd_Loop_Sec_B          K_MADMultTPSTimer = FixDefConst( 0.5, Every_2nd_Loop_Sec_B ) ;
/*  duration of TPS delta condition to offset MAD multiplier */
/*  N = E/16  */
/*
*| esc_cal.{
*|    K_MADMultTPSTimer
*|    {
*|       :is_calconst;
*|       :description = "duration of TPS delta condition to offset MAD multiplier";
*|       :units = "Seconds";
*|       :type = types.Every_2nd_Loop_Sec_B;
*|    }
*| }
*/

const RPM_Hi_Res_W                  K_MADMultiplierDeltaRPM = FixDefConst( 200.0, RPM_Hi_Res_W ) ;
/*  RPM change limit for MAD offset */
/*  N = E/1 RPM  */
/*
*| esc_cal.{
*|    K_MADMultiplierDeltaRPM
*|    {
*|       :is_calconst;
*|       :description = "RPM change over 15.625 ms threshold for MAD offset";
*|       :units = "RPM";
*|       :type = types.RPM_Hi_Res_W;
*|    }
*| }
*/

const Every_4th_Loop_Sec_B          K_MADMultRPMTimer = FixDefConst( 0.5, Every_4th_Loop_Sec_B ) ;
/*  duration of RPM delta condition to offset MAD multiplier */
/*  N = E/16 */
/*
*| esc_cal.{
*|    K_MADMultRPMTimer
*|    {
*|       :is_calconst;
*|       :description = "duration of RPM delta condition to offset MAD multiplier";
*|       :units = "Seconds";
*|       :type = types.Every_4th_Loop_Sec_B;
*|    }
*| }
*/

const Multiplier_0_to_64 F_MADMultiplier[NUMBER_OF_CYLINDERS][RPM_0to6400by400_Steps] =
/*  MAD multiplier for high load */
/*  N = E*4  */
{
    {/* cylinder 1 */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  400 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  800 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 1200 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 1600 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 2000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 2400 RPM */
        FixDefConst( 3.25, Multiplier_0_to_64 ),  /* 2800 RPM */
        FixDefConst( 3.50, Multiplier_0_to_64 ),  /* 3200 RPM */
        FixDefConst( 4.50, Multiplier_0_to_64 ),  /* 3600 RPM */
        FixDefConst( 4.50, Multiplier_0_to_64 ),   /* 4000 RPM */
        FixDefConst( 4.50, Multiplier_0_to_64 ),  /* 4400 RPM */
        FixDefConst( 4.00, Multiplier_0_to_64 ),  /* 4800 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 5200 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 5600 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),   /* 6000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 )    /* 6400 RPM */
    },
    {/* cylinder 2 */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  400 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  800 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 1200 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 1600 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 2000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 2400 RPM */
        FixDefConst( 3.25, Multiplier_0_to_64 ),  /* 2800 RPM */
        FixDefConst( 3.50, Multiplier_0_to_64 ),  /* 3200 RPM */
        FixDefConst( 4.75, Multiplier_0_to_64 ),  /* 3600 RPM */
        FixDefConst( 4.75, Multiplier_0_to_64 ),   /* 4000 RPM */
        FixDefConst( 4.50, Multiplier_0_to_64 ),  /* 4400 RPM */
        FixDefConst( 4.00, Multiplier_0_to_64 ),  /* 4800 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 5200 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 5600 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),   /* 6000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 )    /* 6400 RPM */
    },
    {/* cylinder 3 */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  400 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  800 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 1200 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 1600 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 2000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 2400 RPM */
        FixDefConst( 3.25, Multiplier_0_to_64 ),  /* 2800 RPM */
        FixDefConst( 3.50, Multiplier_0_to_64 ),  /* 3200 RPM */
        FixDefConst( 4.75, Multiplier_0_to_64 ),  /* 3600 RPM */
        FixDefConst( 4.75, Multiplier_0_to_64 ),   /* 4000 RPM */
        FixDefConst( 4.50, Multiplier_0_to_64 ),  /* 4400 RPM */
        FixDefConst( 4.00, Multiplier_0_to_64 ),  /* 4800 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 5200 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 5600 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),   /* 6000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 )    /* 6400 RPM */
    }
#if CcSYST_NUM_OF_CYLINDERS > 3
,
    {/* cylinder 4 */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  400 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /*  800 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 1200 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 1600 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 2000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 2400 RPM */
        FixDefConst( 3.25, Multiplier_0_to_64 ),  /* 2800 RPM */
        FixDefConst( 3.50, Multiplier_0_to_64 ),  /* 3200 RPM */
        FixDefConst( 4.50, Multiplier_0_to_64 ),  /* 3600 RPM */
        FixDefConst( 4.50, Multiplier_0_to_64 ),   /* 4000 RPM */
        FixDefConst( 4.50, Multiplier_0_to_64 ),  /* 4400 RPM */
        FixDefConst( 4.00, Multiplier_0_to_64 ),  /* 4800 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 5200 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),  /* 5600 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 ),   /* 6000 RPM */
        FixDefConst( 3.00, Multiplier_0_to_64 )    /* 6400 RPM */
    }
#endif
};
/*
*| esc_cal.{
*|    F_MADMultiplier
*|    {
*|       # --- 3D table --- #
*|       :is_calconst;
*|       :description = "MAD multiplier";
*|       :elements:elements:units = " ";
*|       :elements:elements:type = types.Multiplier_0_to_64;
*/
#if CcSYST_NUM_OF_CYLINDERS == 3
/*
*|       :annotation = types.NUMBER_OF_CYLINDERS_3Cyl;
*/
#else
/*
*|       :annotation = types.NUMBER_OF_CYLINDERS;
*/
#endif
/*
*|       :elements:annotation = types.RPM_0to6400by400_Steps;
*|    }
*| }
*/

const Multiplier_0_to_4 F_MADMultLoadComp[kPa_20to100by20_Steps][RPM_0to6400by400_Steps] =
/*  MAD multiplier compensation when for engine load */
/*  N = E*64  */
{
    {/*--- kPa_20  ---*/
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /*  000 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /*  400 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /*  800 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 1200 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 1600 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 2000 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 2400 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 2800 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 3200 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 3600 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 4000 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 4400 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 4800 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 5200 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 5600 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 6000 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 )   /* 6400 RPM */
    },
    {/*--- kPa_40  ---*/
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /*  000 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /*  400 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /*  800 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 1200 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 1600 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 2000 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 2400 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 2800 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 3200 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 3600 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 4000 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 4400 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 4800 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 5200 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 5600 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 6000 RPM */
        FixDefConst( 1.0, Multiplier_0_to_4 )   /* 6400 RPM */
    },
    {/*--- kPa_60  ---*/
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /*  000 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /*  400 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /*  800 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 1200 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 1600 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 2000 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 2400 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 2800 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 3200 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 3600 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 4000 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 4400 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 4800 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 5200 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 5600 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 ),  /* 6000 RPM */
        FixDefConst( 1.094, Multiplier_0_to_4 )   /* 6400 RPM */
    },
    {/*--- kPa_80  ---*/
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /*  000 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /*  400 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /*  800 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 1200 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 1600 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 2000 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 2400 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 2800 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 3200 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 3600 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 4000 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 4400 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 4800 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 5200 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 5600 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 ),  /* 6000 RPM */
        FixDefConst( 1.203, Multiplier_0_to_4 )   /* 6400 RPM */
    },
    {/*--- kPa_100  ---*/
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /*  000 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /*  400 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /*  800 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 1200 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 1600 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 2000 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 2400 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 2800 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 3200 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 3600 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 4000 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 4400 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 4800 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 5200 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 5600 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 ),  /* 6000 RPM */
        FixDefConst( 1.297, Multiplier_0_to_4 )   /* 6400 RPM */
    }
};
/*
*| esc_cal.{
*|    F_MADMultLoadComp
*|    {
*|         # --- 3D table --- #
*|       :is_calconst;
*|       :description = "MAD multiplier compensation when for engine load";
*|       :elements:elements:units = "";
*|       :elements:elements:type = types.Multiplier_0_to_4;
*|       :annotation = types.kPa_20to100by20_Steps;
*|       :elements:annotation = types.RPM_0to6400by400_Steps;
*|    }
*| }
*/

const Multiplier_0_to_4 F_MADMultPEComp[RPM_0to6400by400_Steps] =
/*  MAD multiplier compensation when in Power Enrichment */
/*  N = E*64  */
{
    FixDefConst( 1.0, Multiplier_0_to_4 ),   /*  000 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /*  400 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /*  800 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 1200 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 1600 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 2000 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 2400 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 2800 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 3200 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 3600 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 4000 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 4400 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 4800 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 5200 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 5600 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 ),  /* 6000 RPM */
    FixDefConst( 1.0, Multiplier_0_to_4 )   /* 6400 RPM */
 } ;
/*
*| esc_cal.{
*|    F_MADMultPEComp
*|    {
*|       # --- 2D table ---
*|       :is_calconst;
*|       :description = "MAD multiplier compensation when in Power Enrichment";
*|       :elements:units = "";
*|       :elements:type = types.Multiplier_0_to_4;
*|       :annotation = types.RPM_0to6400by400_Steps;
*|    }
*| }
*/

const Multiplier_0_to_64 F_MADMultTPSOffset[RPM_0to6400by400_Steps] =
/*  MAD multiplier offset for TPS change conditions */
/*  N = E*4  */
{
    FixDefConst( 1.5, Multiplier_0_to_64 ), /*  000 RPM */
    FixDefConst( 1.5, Multiplier_0_to_64 ), /*  400 RPM */
    FixDefConst( 1.5, Multiplier_0_to_64 ), /*  800 RPM */
    FixDefConst( 1.5, Multiplier_0_to_64 ), /* 1200 RPM */
    FixDefConst( 1.5, Multiplier_0_to_64 ), /* 1600 RPM */
    FixDefConst( 1.5, Multiplier_0_to_64 ), /* 2000 RPM */
    FixDefConst( 1.5, Multiplier_0_to_64 ), /* 2400 RPM */
    FixDefConst( 1.5, Multiplier_0_to_64 ), /* 2800 RPM */
    FixDefConst( 1.5, Multiplier_0_to_64 ), /* 3200 RPM */
    FixDefConst( 2.0, Multiplier_0_to_64 ), /* 3600 RPM */
    FixDefConst( 2.0, Multiplier_0_to_64 ), /* 4000 RPM */
    FixDefConst( 2.5, Multiplier_0_to_64 ), /* 4400 RPM */
    FixDefConst( 2.5, Multiplier_0_to_64 ), /* 4800 RPM */
    FixDefConst( 3.0, Multiplier_0_to_64 ), /* 5200 RPM */
    FixDefConst( 3.0, Multiplier_0_to_64 ), /* 5600 RPM */
    FixDefConst( 3.0, Multiplier_0_to_64 ), /* 6000 RPM */
    FixDefConst( 3.0, Multiplier_0_to_64 )  /* 6400 RPM */
 } ;
/*
*| esc_cal.{
*|    F_MADMultTPSOffset
*|    {
*|        # --- 2D table ---
*|       :is_calconst;
*|       :description = "MAD multiplier offset for TPS change conditions";
*|       :elements:units = "";
*|       :elements:type = types.Multiplier_0_to_64;
*|       :annotation = types.RPM_0to6400by400_Steps;
*|    }
*| }
*/

const Multiplier_0_to_64 F_MADMultRPMOffset[RPM_0to6400by400_Steps] =
/*  MAD multiplier offset for RPM change conditions */
/*  N = E*4  */
{
    FixDefConst( 6.0, Multiplier_0_to_64 ), /*  000 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /*  400 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /*  800 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 1200 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 1600 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 2000 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 2400 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 2800 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 3200 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 3600 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 4000 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 4400 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 4800 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 5200 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 5600 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 ), /* 6000 RPM */
    FixDefConst( 6.0, Multiplier_0_to_64 )  /* 6400 RPM */
} ;
/*
*| esc_cal.{
*|    F_MADMultRPMOffset
*|   {
*|         # --- 2D table ---
*|       :is_calconst;
*|       :description = "MAD multiplier offset for RPM change conditions";
*|       :elements:units = "";
*|       :elements:type = types.Multiplier_0_to_64;
*|       :annotation = types.RPM_0to6400by400_Steps;
*|    }
*| }
*/

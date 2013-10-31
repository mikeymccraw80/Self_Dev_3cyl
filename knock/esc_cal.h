#ifndef ES_CAL_H
#define ES_CAL_H

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "lux_type.h"
#include "lux_math.h"

/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "es_types.h"

/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */


/*  -------------------------------------------------  *\
 *  system initialisation
\*  -------------------------------------------------  */
extern const  bool                       K_ESC_Enable ;
extern const Volt0to5Volts_W                     K_ADESC_Min_Threshold;
extern const Multiplier_0_to_2                     K_ADESC_Scl_Multi;
/*--------------------------------*\
 *---  Knock Window Placement  ---*
\*--------------------------------*/

extern const CrankAngleInDeg_W     FSTPWD[RPM_400to6400by400_Steps];
extern const CrankAngleInDeg_W   FSTRTWD[kPa_60to100by10_Steps][RPM_400to6400by400_Steps];

/*  -------------------------------------------------  *\
 *  Enable/disable conditions                          *
\*  -------------------------------------------------  */

extern const Seconds_Low                   K_ESCEnableRunTime;
extern const RPM_W                         K_ESCEnableRPM;
extern const kPa_B                         K_ESCEnableMAP;


/*  -------------------------------------------------  *\
 *  ESC average calculation                            *
\*  -------------------------------------------------  */

extern const Filter_Q_W                    K_IntegratorFilterUp;
extern const Filter_Q_W                    K_IntegratorFilterDown;
extern const Filter_Q_W                    K_IntegratorFilterSteadyState;
extern const Filter_Q_W                    K_IntegratorFilterKnockMult;
extern const RPM_W                         K_DeltaRPMIncThreshold;
extern const RPM_W                         K_DeltaRPMDecThreshold;
extern const TPS_B                         K_DeltaTPSIncThreshold;
extern const TPS_B                         K_DeltaTPSDecThreshold;
extern const Volt0to5Volts_B               K_ESCAverageInit;
extern const Volt0to5Volts_B               K_ESCAverageMin;

/*  -------------------------------------------------  *\
 *  Amplifier gain determination                       *
\*  -------------------------------------------------  */

//extern const Volt0to5Volts_W               K_ESCAverageUppThreshold;
//extern const Volt0to5Volts_W               K_ESCAverageLowThreshold;


/*  -------------------------------------------------  *\
 *  MAD determination                                  *
\*  -------------------------------------------------  */

extern const Filter_Q_W                    K_MADFilterCoefficient;
extern const Volt0to5Volts_W               K_MADMax;
extern const Volt0to5Volts_W               K_MADMin;
extern const RPM_W                         K_MADRPM;
extern const kPa_B                         K_MADMAP;
extern const RPM_W                         K_MADDeltaRPM;
extern const TPS_B                         K_MADDeltaTPS;
extern const kPa_Delta                     K_MADDeltaMAP;
extern const Every_16th_Loop_Sec_B         K_MADTransientTime;

/*  -------------------------------------------------  *\
 *  Knock threshold determination                      *
\*  -------------------------------------------------  */

extern const TPS_B                         K_MADMultiplierDeltaTPS;
extern const Every_2nd_Loop_Sec_B          K_MADMultTPSTimer;
extern const RPM_Hi_Res_W                  K_MADMultiplierDeltaRPM;
extern const Every_4th_Loop_Sec_B          K_MADMultRPMTimer;
extern const Multiplier_0_to_64            F_MADMultiplier[NUMBER_OF_CYLINDERS][RPM_0to6400by400_Steps];
extern const Multiplier_0_to_4             F_MADMultLoadComp[kPa_20to100by20_Steps][RPM_0to6400by400_Steps];
extern const Multiplier_0_to_4             F_MADMultPEComp[RPM_0to6400by400_Steps];
extern const Multiplier_0_to_64            F_MADMultTPSOffset[RPM_0to6400by400_Steps];
extern const Multiplier_0_to_64            F_MADMultRPMOffset[RPM_0to6400by400_Steps];
extern const Every_2nd_Loop_Sec_B          K_ESCKnockDisplay;


/*---------------------------------*\
 *---  PE judgement     ---*
\*---------------------------------*/
extern const Percent_B K_PE_TPS_Load_Thres_2D[RPM_0to6400by800_Steps];
extern const Percent_B                       K_Fuel_TPS_Hysteresis_For_PE ;
extern const Every_4th_Loop_Sec_W   F_PE_Delay_Time_2D[RPM_0to6400by800_Steps]; 
extern const Every_4th_Loop_Sec_W   F_EveryPE_DelayTime_2D[RPM_0to6400by800_Steps]; 

/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported INLINE functions and #define function-like macros.
\* ============================================================================ */
/*  none  */


#endif /* ES_CAL_H */

#ifndef INTR_EMS_H
#define INTR_EMS_H
/* ============================================================================ *\
 * intr_ems.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       intr_ems.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, 16 September, 2003 02:41:00 AM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the type definition for interface with EMS.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */


/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "reuse.h"
#include "v_ignit.h"
#include "HLS.h"
#include "dd_vsep_fault.h"
#include "hwiocald.h"
#include "hal_gpio.h"
#include "hal_eng.h"
#include "hal_diag.h"
#include "hal_analog.h"
#include "dd_cam_interface.h"
#include "hal_emulated_eeprom.h"

/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */


/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */

#define STOICH_AFR (14.6)

typedef uint16_t                            CHERY_TEMP_Ta ;
#define Prec_CHERY_TEMP_Ta                   ( 0.0195 )
#define Min_CHERY_TEMP_Ta                    ( -50.0 )
#define Max_CHERY_TEMP_Ta                    ( 65535.0 * Prec_CHERY_TEMP_Ta + Min_CHERY_TEMP_Ta )

typedef uint16_t                            CHERY_BPW ;            /* [0,1024) ms */
#define Prec_CHERY_BPW                       (0.00256)
#define Min_CHERY_BPW                        (0.0)
#define Max_CHERY_BPW                        (65535*Prec_CHERY_BPW+Min_CHERY_BPW)

typedef uint8_t                            CHERY_RPMa ;
#define Prec_CHERY_RPMa                       ( 10.0 )
#define Min_CHERY_RPMa                        ( 0.0 )
#define Max_CHERY_RPMa                        ( 255.0 * Prec_CHERY_RPMa + Min_CHERY_RPMa )

typedef uint16_t                            CHERY_KPAa ;
#define Prec_CHERY_KPAa                       ( 1.0 / 256 )
#define Min_CHERY_KPAa                        ( 0.0 )
#define Max_CHERY_KPAa                        ( 65535.0 * Prec_CHERY_KPAa )

typedef uint8_t                            CHERY_DEG_T ;
#define Prec_CHERY_DEG_T                     ( 0.75 )
#define Min_CHERY_DEG_T                      ( -48.0 )
#define Max_CHERY_DEG_T                      ( 255.0 * Prec_CHERY_DEG_T + Min_CHERY_DEG_T )

typedef uint16_t                            CHERY_Lam ;
#define Prec_CHERY_Lam                  ( 1.0 / 4096 )
#define Min_CHERY_Lam                   ( 0.0 )
#define Max_CHERY_Lam                   ( 65535 * Prec_CHERY_Lam + Min_CHERY_Lam)

typedef uint16_t                            CHERY_AFR ;
#define Prec_CHERY_AFR                  ( Prec_CHERY_Lam * STOICH_AFR )
#define Min_CHERY_AFR                   ( 0.0 )
#define Max_CHERY_AFR                   ( 65535 * Prec_CHERY_AFR + Min_CHERY_AFR)

typedef uint16_t                            CHERY_AIRFLOW_KGH ;
#define Prec_CHERY_AIRFLOW_KGH               ( 0.1 ) //or 0.1kg/h
#define Min_CHERY_AIRFLOW_KGH                ( 0.0 )
#define Max_CHERY_AIRFLOW_KGH                ( 65535.0 * Prec_CHERY_AIRFLOW_KGH + Min_CHERY_AIRFLOW_KGH )

typedef uint16_t                            CHERY_AIRFLOW ;
#define Prec_CHERY_AIRFLOW                   ( Prec_CHERY_AIRFLOW_KGH/3.6 )
#define Min_CHERY_AIRFLOW                    ( 0.0 )
#define Max_CHERY_AIRFLOW                    ( 65535.0 * Prec_CHERY_AIRFLOW + Min_CHERY_AIRFLOW )

typedef uint16_t                            CHERY_VOLTb ;
#define Prec_CHERY_VOLTb                     ( 5.0 / 1024.0 )
#define Min_CHERY_VOLTb                      ( -1.0 )
#define Max_CHERY_VOLTb                      ( 65535 * Prec_CHERY_VOLTb + Min_CHERY_VOLTb )

typedef uint8_t                            CHERY_ANGLEa ;
#define Prec_CHERY_ANGLEa                 (0.75 )
#define Min_CHERY_ANGLEa                  (-96.0)
#define Max_CHERY_ANGLEa                  (255 * Prec_CHERY_ANGLEa + Min_CHERY_ANGLEa )

typedef uint16_t                            EOBD_BPW ;            /* [0,1024) ms */
#define Const_EOBD_BPW                      (64.0)
#define Prec_EOBD_BPW                       (1.0/64.0)
#define Min_EOBD_BPW                        (0.0)
#define Max_EOBD_BPW                        (65535*Prec_EOBD_BPW)

typedef int16_t                             EOBD_A_DEG_Cb;
#define Const_EOBD_A_DEG_Cb                 (16)
#define Prec_EOBD_A_DEG_Cb                  (1.0/16.0)
#define Min_EOBD_A_DEG_Cb                   (-2048.0)
#define Max_EOBD_A_DEG_Cb                   (65535*Prec_EOBD_A_DEG_Cb)
#define V_EOBD_A_DEG_Cb(val)                (int16_t)((val)/Prec_EOBD_A_DEG_Cb)

typedef uint16_t                            EOBD_PERCENT_W ;
#define Prec_EOBD_PERCENTb                   ( 100.0 / 65536 )
#define Min_EOBD_PERCENTb                    ( 0.0 )
#define Max_EOBD_PERCENTb                    ( 65535 * 100.0 / 65536 )

typedef uint16_t                            EOBD_MILEAGE_PER_KM ;
#define Prec_EOBD_MILEAGE_PER_KM             ( 1.0 )
#define Min_EOBD_MILEAGE_PER_KM              ( 0.0 )
#define Max_EOBD_MILEAGE_PER_KM              ( 65535.0 )

typedef uint16_t                            EOBD_RPMa ;
#define Prec_EOBD_RPMa                       ( 1.0 / 8 )
#define Min_EOBD_RPMa                        ( 0.0 )
#define Max_EOBD_RPMa                        ( 65535.0 * Prec_EOBD_RPMa + Min_EOBD_RPMa )

typedef uint16_t                            EOBD_KPAa ;
#define Prec_EOBD_KPAa                       ( 1.0 / 256 )
#define Min_EOBD_KPAa                        ( 0.0 )
#define Max_EOBD_KPAa                        ( 65535.0 * Prec_EOBD_KPAa + Min_EOBD_KPAa )

typedef uint16_t                            EOBD_KPH ;
#define Prec_EOBD_KPH                       ( 0.0078125 )
#define Min_EOBD_KPH                        ( 0.0 )
#define Max_EOBD_KPH                        ( 65535.0 * 0.0078125 )

typedef uint16_t                            EOBD_DEG_Ca ;
#define Prec_EOBD_DEG_Ca                     ( 1.0 / 128 )
#define Min_EOBD_DEG_Ca                      ( -256.0 )
#define Max_EOBD_DEG_Ca                      ( 65535.0 * Prec_EOBD_DEG_Ca + Min_EOBD_DEG_Ca )

typedef uint16_t                            EOBD_DEG_Cb ;
#define Prec_EOBD_DEG_Cb                     ( 0.0625 )
#define Min_EOBD_DEG_Cb                      ( -2048.0 )
#define Max_EOBD_DEG_Cb                      ( 65535.0 * Prec_EOBD_DEG_Cb + Min_EOBD_DEG_Cb )

typedef uint16_t                            EOBD_COUNT_WORD;
#define Prec_EOBD_COUNT_WORD                 ( 1 )
#define Min_EOBD_COUNT_WORD                  ( 0 )
#define Max_EOBD_COUNT_WORD                  ( 65535 )

typedef uint16_t                            EOBD_T_PERCENT;
#define Prec_EOBD_T_PERCENT                  (0.001525878906)
#define Min_EOBD_T_PERCENT                   (0)
#define Max_EOBD_T_PERCENT                   (65535.0*0.001525878906)

typedef uint16_t                            EOBD_T_PERCENT_MULTb;
#define Prec_EOBD_T_PERCENT_MULTb           ( 1.0/65536 )
#define Min_EOBD_T_PERCENT_MULTb            ( 0.0 )
#define Max_EOBD_T_PERCENT_MULTb            ( 65535.0 * Prec_EOBD_T_PERCENT_MULTb )

typedef uint32_t               EOBD_Mileage_In_KM_L ;
#define Prec_EOBD_Mileage_In_KM_L  ( 1.0 )
#define Min_EOBD_Mileage_In_KM_L   ( 0.0 )
#define Max_EOBD_Mileage_In_KM_L   ( MAX_uint32_t * Prec_EOBD_Mileage_In_KM_L )

typedef uint16_t                            EOBD_PERCENTa ;
#define Prec_EOBD_PERCENTa                  ( 100.0 / 32768 )
#define Min_EOBD_PERCENTa                   ( 0.0 )
#define Max_EOBD_PERCENTa                   ( 65535 * Prec_EOBD_PERCENTa )

typedef uint16_t                            EOBD_AIRFLOW ;
#define Prec_EOBD_AIRFLOW                   ( 1 / 128.0 )
#define Min_EOBD_AIRFLOW                    ( 0.0 )
#define Max_EOBD_AIRFLOW                    ( 65535.0 * Prec_EOBD_AIRFLOW + Min_EOBD_AIRFLOW )

typedef uint16_t                            EOBD_VOLTb ;
#define Prec_EOBD_VOLTb                     ( 1.0 / 2048.0 )
#define Min_EOBD_VOLTb                      ( 0.0 )
#define Max_EOBD_VOLTb                      ( 65535 * Prec_EOBD_VOLTb )

typedef uint16_t                            EOBD_AFR_T ;
#define Prec_EOBD_AFR_T                     ( 1.0 / 2048.0 )
#define Min_EOBD_AFR_T                      ( 0.0 )
#define Max_EOBD_AFR_T                      ( 65535 * Prec_EOBD_AFR_T )

typedef uint16_t                            EOBD_MULTP_0_TO_1_T ;
#define Prec_EOBD_MULTP_0_TO_1_T            ( 1.0 / 65536.0 )
#define Min_EOBD_MULTP_0_TO_1_T             ( 0.0 )
#define Max_EOBD_MULTP_0_TO_1_T             ( 65535 * Prec_EOBD_MULTP_0_TO_1_T )

typedef uint16_t                            EOBD_MULTP_0_TO_2_T ;
#define Prec_EOBD_MULTP_0_TO_2_T            ( 1.0 / 32768.0 )
#define Min_EOBD_MULTP_0_TO_2_T             ( 0.0 )
#define Max_EOBD_MULTP_0_TO_2_T             ( 65535 * Prec_EOBD_MULTP_0_TO_2_T )

typedef uint16_t                            EOBD_RATIO_0_2 ;
#define Prec_EOBD_RATIO_0_2                 (1.0 / 32768.0 )
#define Min_EOBD_RATIO_0_2                  (0.0)
#define Max_EOBD_RATIO_0_2                  (65535 * Prec_EOBD_RATIO_0_2 )

typedef int16_t                             EOBD_ANGLEa;
#define Const_EOBD_ANGLEa                   (128)
#define Prec_EOBD_ANGLEa                    (256.0/65536.0)
#define Min_EOBD_ANGLEa                     (-128.0)
#define Max_EOBD_ANGLEa                     (Min_EOBD_ANGLEa+65535*Prec_EOBD_ANGLEa)


typedef enum {
	CeIGN_OFF,              /* 00 */
	CeIGN_ON                /* 01 */
} TeIGN_STATE;


#define Prec_T_DECIBELS                     (0.25)
#define Min_T_DECIBELS                      (0)


#define KyVIOS_NumberOfCylinders       ( NUMBER_OF_CYLINDERS )
#define NumOfPrevTPEntries             ((uint8_t) (0.132/0.0078125))
#define Number_of_Cells                (22)
#define EOBD_BLM_CELLS                 (Number_of_Cells)

typedef uint16_t               kPa_W_EOBD ;
#define Prec_kPa_W_EOBD                       ( 1.0 / 256 )
#define Min_kPa_W_EOBD                              ( 0.0 )
#define Max_kPa_W_EOBD        ( 65535.0 * Prec_kPa_W_EOBD )
/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */


/* ============================================================================ *\
 * Local INLINE functions and #define function-like macros.
\* ============================================================================ */
#define RFactor_kPa_Double_EOBD_KPAa                    (512.0)
#define RFactor_kPa_Plus_Fraction_EOBD_KPAa             (694.0*256.0)
#define RFactor_Degrees_C_B_EOBD_DEG_Ca                 (256.0)
#define RFactor_RPM_Hi_Res_W_EOBD_RPMa                  (8.0)
#define RFactor_RPM_Med_Plus_Fraction_EOBD_RPMa         (512.0)
#define RFactor_Degrees_C_W_EOBD_DEG_Ca                 (256.0)
#define RFactor_Seconds_Low_EOBD_COUNT_WORD             (1.0)
#define RFactor_Airflow_W_EOBD_PERCENTb                 (65536.0)
#define RFactor_Shortcard_Plus_Fraction_EOBD_T_PERCENT  (65536.0)
#define RFactor_Degress_C_W_EOBD_DEG_Ca                 (256.0)
#define RFactor_kPa_W_EOBD_KPAa                         (256.0)
#define RFactor_KPH_EOBD_KPH                            (128.0)
#define RFactor_Mileage_In_100M_L_EOBD_Mileage_In_KM_L  (10.0)
#define RFactor_Fraction_W_EOBD_T_PERCENT               (65536.0)
#define RFactor_Grams_Per_Second_W_EOBD_AIRFLOW         (256.0)
#define RFactor_Percent_Plus_Fraction_EOBD_T_PERCENT    (65536.0)
#define RFactor_Percent_B_EOBD_PERCENTa                 (32768.0)
#define RFactor_kPa_B_EOBD_KPAa                         (694.0*256.0)
#define RFactor_Volts_W_EOBD_VOLTb                      (2048.0)
#define RFactor_Percent_Plus_Fraction_EOBD_PERCENTa     (65536.0)
#define RFactor_kPa_Plus_Fraction_EOBD_T_PERCENT        (65536.0)
#define RFactor_Multiplier_0_to_2_EOBD_MULTP_0_TO_2_T   (32768.0)
#define RFactor_Multiplier_0_to_2_EOBD_RATIO_0_2        (32768.0)
#define RFactor_DegreeConvTempBType_EOBD_DEG_Cb         (16.0)
#define RFactor_AirFuel_Ratio_Type_EOBD_AFR_T           (20480.0)
#define RFactor_RPM_Med_Res_B_EOBD_RPMa                 (8.0)
#define RFactor_EOBD_AFR_T_AirFuel_Ratio_Type           (20480.0)
#define RFactor_Percent_B_EOBD_T_PERCENT                (65536.0)
#define RFactor_Percent_Plus_Fraction_EOBD_T_PERCENT_MULTb  (65536.0)
#define RFactor_AnalogADCommonPct_W_EOBD_T_PERCENT_MULTb    (65536.0)
#define RFactor_SparkAdvance_Deg_B_EOBD_ANGLEa              (256.0)
#define RFactor_DegreeConvTempFiltType_EOBD_A_DEG_Cb        (256.0)
#define RFactor_BPFGain_Type_T_DECIBELS                     (4.0)

// for conversion between CHERY and EOBD module
#define RFactor_CHERY_AFR_EOBD_AFR_T                   (40960.0)
#define RFactor_EOBD_AFR_T_CHERY_AFR                   (40960.0)
#define RFactor_CHERY_AIRFLOW_EOBD_AIRFLOW             (1152.0)
#define RFactor_CHERY_ANGLEa_EOBD_ANGLEa               (256.0)
#define RFactor_CHERY_BPW_EOBD_BPW                     (3906.0)
#define RFactor_CHERY_DEG_T_EOBD_DEG_Ca                (256.0)
#define RFactor_CHERY_KPAa_EOBD_KPAa                   (52480.0)
#define RFactor_CHERY_RPMa_EOBD_RPMa                   (8.0)
#define RFactor_CHERY_VOLTb_EOBD_VOLTb                 (2048.0)
#define RFactor_Volts_Plus_Fraction_EOBD_VOLTb         (10240.0)
#define RFactor_CHERY_TEMP_Ta_EOBD_A_DEG_Cb            (2000.0)

/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */


/**********************************************************************/
/*** Converts 16 bit unsigned  value  to signed value               ***/
/**********************************************************************/
#define UnsignedToSigned_16t( Value ) \
   ( ( ( Value ) >= 0x8000 ) ? \
   ( ( Value ) - 0x8000 ) : \
   ( ( Value ) + 0x8000 ) )

#define UnsignedToSigned_8t( Value ) \
   ( ( ( Value ) >= 0x80 ) ? \
   ( ( Value ) - 0x80 ) : \
   ( ( Value ) + 0x80 ) )

#define SignedToUnsigned_8b( Value ) \
   ( ( ( Value ) >= 0x80 ) ? \
   ( ( Value ) - 0x80 ) : \
   ( ( Value ) + 0x80 ) )


/***********************************************************************
 ********************   RPM                       **********************
 ***********************************************************************/
// extern RPM_W             VfVIOS_n_EngSpd ;
// #define GetVIOS_n_EngSpd()\
                      // (VfVIOS_n_EngSpd)

/***********************************************************************
 ************** Ignition Voltage  **************************************
 ***********************************************************************/
extern EOBD_VOLTb        EOBD_Ignition_Voltage;
extern EOBD_VOLTb        EOBD_IgnVoltageAtKeyOn;
#define	GetVIOS_U_IgnVolt()\
                        (EOBD_Ignition_Voltage)
#define GetVIOS_U_IgnVoltageAtKeyOn()\
                        (EOBD_IgnVoltageAtKeyOn)
static INLINE void ConvertIntrParam_IgnitionVoltage(void)
{
    EOBD_Ignition_Voltage = FixConvert((HAL_Analog_Get_IGNVI_Value() << 2), Volts_Plus_Fraction, EOBD_VOLTb );
}
static INLINE void ConvertIntrParam_IgnKeyOn(void)
{
    EOBD_IgnVoltageAtKeyOn = FixConvert((HAL_Analog_Get_IGNVI_Value() << 2), Volts_Plus_Fraction, EOBD_VOLTb);
}

/***********************************************************************
 **************    Manifold Pressure    ********************************
 ***********************************************************************/
// extern EOBD_T_PERCENT          EOBD_Pct_RawMAP;
// extern EOBD_KPAa               EOBD_UndefMnfdPresFiltd;
// extern EOBD_KPAa               EOBD_DefFiltdMnfdPres;
// extern EOBD_KPAa               EOBD_MAP_Altitude;
// extern Percent_Plus_Fraction   EOBD_EngineLoad_MAP_Percent;
// extern EOBD_T_PERCENT                   EOBD_Pct_RawBRPre;
// #define GetVIOS_Pct_RawMnfdPres()\
                    // (EOBD_Pct_RawMAP)
#define GetVIOS_p_MnfdPresFiltd()\
                    (FixConvert(Pim, CHERY_KPAa, EOBD_KPAa))
// #define GetVIOS_p_UndefMnfdPresFiltd()\
                    // (EOBD_UndefMnfdPresFiltd)
// #define GetVIOS_p_AltdCompMnfdPres()\
                    // (EOBD_MAP_Altitude)
// #define GetVIOS_p_MnfdPresDouble()\
                    // (EOBD_UndefMnfdPresFiltd)
// #define	GetAIRF_p_AltdCompMnfdPres()\
                    // (EOBD_MAP_Altitude)
// #define GetVIOS_p_UndefAltdCompMnfdPres()\
                    // (EOBD_MAP_Altitude)
// #define GetFTRM_Pct_EngineLoad_MAP()\
                    // (EOBD_EngineLoad_MAP_Percent)

// #define GetVIOS_Pct_RawBRPres()\
                    // (EOBD_Pct_RawBRPre)
// INLINE void ConvertIntrParam_MAP(void)
// {
    // EOBD_DefFiltdMnfdPres = FixConvert(Pim, CHERY_KPAa, EOBD_KPAa);
    // EOBD_UndefMnfdPresFiltd = FixConvert(Pmap, CHERY_KPAa, EOBD_KPAa);
    // EOBD_MAP_Altitude = FixNonBiasedShortDivide( Pim, CHERY_KPAa,
                                                 // fAlt, Multiplier_0_to_4_W,
                                                 // CHERY_KPAa);
    // EOBD_Pct_RawMAP = ATD_buffer[AD_MANIFOLD_ABS_PRESSURE_TIME_BASE_TYPE];
    // EOBD_EngineLoad_MAP_Percent = FixNonBiasedShortDivide ( Min(EOBD_DefFiltdMnfdPres, FixDefConst(Max_kPa_W, EOBD_KPAa)), EOBD_KPAa,
                                                            // FixDefConst( Max_kPa_W, kPa_W), kPa_W,
                                                            // Multiplier_0_to_1_W );
// }

//INLINE void ConvertIntrParam_BRP(void)
//{
//EOBD_Pct_RawBRPre = ATD_buffer[AD_SS_BRAKE_VACUUM_TYPE ];

//}

/***********************************************************************
 *************************    Vacuum    ********************************
 ***********************************************************************/
extern kPa_W_EOBD                           EOBD_Vacuum_W_;
#define GetVIOS_p_MnfdVac()\
                      ( EOBD_Vacuum_W_ )
INLINE void ConvertIntrParam_Vacuum(void)
{
    if (Pam >= Pim)
    {
       EOBD_Vacuum_W_ = Pam - Pim;
    }
    else
    {
       EOBD_Vacuum_W_ = FixDefConst(0, kPa_W_EOBD);
    }
}


/***********************************************************************
 **************    Coolant Temperature  ********************************
 ***********************************************************************/
// extern EOBD_T_PERCENT    EOBD_RawCoolant;
extern int16_t           EOBD_CoolTemp;
// extern int16_t           EOBD_CoolTempStartup;
// extern int16_t           EOBD_UndefCoolTemp;
// #define GetVIOS_Pct_RawCoolant()\
                       // (EOBD_RawCoolant)
#define GetVIOS_T_CoolTemp()\
                       (EOBD_CoolTemp)
// #define GetVIOS_T_CoolTempStartup()\
                       // (EOBD_CoolTempStartup)
// #define GetVIOS_T_UndefCoolTemp()\
                       // (EOBD_UndefCoolTemp)
// INLINE void ConvertIntrParam_ECT(void)
// {
    // EOBD_RawCoolant = ATD_buffer[AD_ENGINE_COOLANT_TEMPERATURE_TYPE];
    // EOBD_CoolTemp = (int16_t)UnsignedToSigned_16t(FixConvert(Tm,CHERY_DEG_T,EOBD_DEG_Ca));
    // EOBD_CoolTempStartup = (int16_t)UnsignedToSigned_16t(FixConvert(Tmini,CHERY_DEG_T,EOBD_DEG_Ca));
    // EOBD_UndefCoolTemp = (int16_t)UnsignedToSigned_16t(FixConvert(TmLin,CHERY_DEG_T,EOBD_DEG_Ca));
// }

/***********************************************************************
 **************    Intake Air Temperature  *****************************
 ***********************************************************************/
// extern int16_t            EOBD_IntakeTemp;
// extern int16_t            EOBD_IntakeTempStartup;
// extern EOBD_T_PERCENT     EOBD_Pct_RawIntakeAirTemp;
// #define GetVIOS_T_UndefIntakeTemp()\
                       // (EOBD_IntakeTemp)
// #define GetVIOS_T_IntakeTemp()\
                       // (EOBD_IntakeTemp)
// #define GetVIOS_T_IntakeTempStartup()\
                       // (EOBD_IntakeTempStartup)
// #define GetVIOS_Pct_RawIntakeAirTemp()\
                       // (EOBD_Pct_RawIntakeAirTemp)
// INLINE void ConvertIntrParam_IAT(void)
// {
    // EOBD_IntakeTemp = (int16_t)UnsignedToSigned_16t(FixConvert(Ta,CHERY_DEG_T,EOBD_DEG_Ca));
    // EOBD_IntakeTempStartup = (int16_t)UnsignedToSigned_16t(FixConvert(Taini,CHERY_DEG_T,EOBD_DEG_Ca));
    // EOBD_Pct_RawIntakeAirTemp = ATD_buffer[AD_INTAKE_AIR_TEMPERATURE_TYPE];
// }

/***********************************************************************
 **************    Vehicle Speed   *************************************
 ***********************************************************************/
extern EOBD_KPH          EOBD_VehSpd;
#define GetVIOS_v_VehSpd()\
                      (EOBD_VehSpd)
#define GetVIOS_v_ATVehSpd()\
                      (FixDefConst(0.0, EOBD_KPH))
INLINE void ConvertIntrParam_VSS(void)
{
    EOBD_VehSpd = Vsp;
}

/***********************************************************************
 ********************    Air Flow  *************************************
 ***********************************************************************/
// extern EOBD_AIRFLOW      EOBD_dm_Airflow;
// #define GetAIRF_dm_Airflow()\
                      // (EOBD_dm_Airflow)
// INLINE void ConvertIntrParam_Airflow(void)
// {
    // EOBD_dm_Airflow =  FixConvert(Maf, CHERY_AIRFLOW, EOBD_AIRFLOW);
// }

/***********************************************************************
 ********************   Fuel Learn                **********************
 ***********************************************************************/
// extern EOBD_MULTP_0_TO_2_T EOBD_CL_IntMultTermB1;
// extern EOBD_RATIO_0_2  EOBD_BLM[];
// extern uint8_t EOBD_BLM_Number;
// #define GetFUEL_CL_IntMultTermB1()\
                      // (EOBD_CL_IntMultTermB1)
// #define GetFUEL_BLM_CellContentsB1(cell_num)\
                      // (EOBD_BLM[cell_num])
// #define GetVIOS_Bank1BLM()\
                      // (GetFUEL_BLM_CellContentsB1(EOBD_BLM_Number))
// #define GetFUEL_BLM_CellNum()\
                      // (EOBD_BLM_Number)

// INLINE void ConvertIntrParam_FuelLearnData(void)
// {
// uint8_t index;

    // EOBD_CL_IntMultTermB1 = fLc;
    
    // for (index=0; index<Number_of_Cells; index++)
    // EOBD_BLM[index] = fLcAd;
// }

/***********************************************************************
 ********************   Spark Advance             **********************
 ***********************************************************************/
// extern EOBD_ANGLEa     EOBD_SparkAdvanceTopDeadCenter;
// #define GetSPRK_phi_ComnSparkAdvAtTopDeadCenter()\
                                // (EOBD_SparkAdvanceTopDeadCenter)

// INLINE void ConvertIntrParam_SparkAdv(void)
// {
    // EOBD_SparkAdvanceTopDeadCenter =UnsignedToSigned_16t(FixConvert( SignedToUnsigned_8b(IgaOut),
                                                 // CHERY_ANGLEa,
                                                 // EOBD_ANGLEa ));
// }

/***********************************************************************
 ********************   Fuel Pulse Width          **********************
 ***********************************************************************/
// extern EOBD_BPW        EOBD_SyncFuel_Var;
// #define GetFUEL_t_FinalBPW_B1()\
                        // (EOBD_SyncFuel_Var)

// INLINE void ConvertIntrParam_BPW(void)
// {
    // EOBD_SyncFuel_Var = FixConvert( Ti_b1, CHERY_BPW, EOBD_BPW);
// }

/***********************************************************************
 ********************   Converter Temperature          **********************
 ***********************************************************************/
// extern EOBD_A_DEG_Cb   EOBD_ConverterTempFilt; 
// #define GetEXAC_T_CatalystTempFilt()\
                    // (EOBD_ConverterTempFilt)
// #define GetEXAC_T_CatalystTempEstimate()\
                    // (EOBD_ConverterTempFilt)
// INLINE void ConvertIntrParam_ConverterTemp(void)
// {
    // EOBD_ConverterTempFilt = (int16_t)UnsignedToSigned_16t(FixConvert(TcatInPre,CHERY_TEMP_Ta,EOBD_A_DEG_Cb));
// }

/***********************************************************************
 ********************   Knock Parameter           **********************
 ***********************************************************************/
#define CcSYST_NUM_OF_CYLINDERS 4
extern Volt0to5Volts_W   ADESC[CcSYST_NUM_OF_CYLINDERS] ; 
extern Volt0to5Volts_W   ADESC_Average_Wingateoff[CcSYST_NUM_OF_CYLINDERS] ; 

extern uint16_t          EOBD_IntegratorAverage[CcSYST_NUM_OF_CYLINDERS] ;      /* filtered value */
extern uint16_t          EOBD_ADESC[CcSYST_NUM_OF_CYLINDERS] ;                  /* raw data */

#define GetVIOS_Pct_CCESC_IntensAverage_EMS(x)\
                           EOBD_IntegratorAverage[x]
#define GetVIOS_Pct_CCESC_IntUnfilt_EMS(x)\
                           EOBD_ADESC[x]
static INLINE void ConvertIntrParam_KnockParam(void)
{
	uint8_t loop_counter;

	for( loop_counter = 0; loop_counter < CcSYST_NUM_OF_CYLINDERS; loop_counter++ ) {
		/* it would be more effiecncy to divide 2 instead of useing mutily macro*/
		EOBD_ADESC[loop_counter] = (uint16_t)( ADESC[loop_counter] / 2 );
		EOBD_IntegratorAverage[loop_counter] = (uint16_t)( ADESC_Average_Wingateoff[loop_counter] / 2 );
	}
}


/***********************************************************************
 ********************   CCP                       **********************
 ***********************************************************************/
extern EOBD_PERCENTa   EOBD_CcpDutyCycle;
#define GetEVAP_CCP_DutyCycle()\
                     (EOBD_CcpDutyCycle)
// INLINE void ConvertIntrParam_CcpDC(void)
// {
    // EOBD_CcpDutyCycle = FixConvert(DuCyPgOut, Percent_B, EOBD_PERCENTa);
// }

/***********************************************************************
 ********************   ETC                       **********************
 ***********************************************************************/
extern EOBD_PERCENTa   EOBD_ETCDutyCycle;
#define GetEVAP_ETC_DutyCycle()\
                     (EOBD_ETCDutyCycle)
INLINE void ConvertIntrParam_ETCDC(void)
{
    EOBD_ETCDutyCycle = FixConvert(etc_sig.etc_duty, Percent_Plus_Fraction, EOBD_PERCENTa);
}


/***********************************************************************
 ********************   TPS                       **********************
 ***********************************************************************/
// extern EOBD_T_PERCENT    EOBD_RawThrotPstn;
// extern EOBD_PERCENTa     EOBD_UndefTPS;
// extern EOBD_PERCENTa     EOBD_TPS_Buffer[NumOfPrevTPEntries];
// extern EOBD_PERCENTa     EOBD_TPS;
// #define GetVIOS_Pct_ThrotPstn()\
                           // (EOBD_TPS)
// #define GetETCI_Pct_VrtlAccelPedalPstn_CAN()\
                           // (EOBD_TPS)
// #define GetVIOS_Pct_VirtualThrotPstn()\
                           // (EOBD_TPS)
// #define GetVIOS_Pct_UndefThrotPstn()\
                           // (EOBD_UndefTPS)
// #define GetVIOS_Pct_RawThrotPstn()\
                        // (EOBD_RawThrotPstn)

// INLINE void ConvertIntrParam_TPS(void)
// {
// uint8_t index;

   // EOBD_RawThrotPstn = ATD_buffer[AD_THROTTLE_POSITION_2_TYPE];
   // EOBD_TPS = FixConvert(TpPosl, Percent_Plus_Fraction, EOBD_PERCENTa);
   // EOBD_UndefTPS = FixConvert(Tpp, Percent_Plus_Fraction, EOBD_PERCENTa);

   // /* shifts the TPS history buffer contents */
   // for (index = NumOfPrevTPEntries - 1; index >= 1; index--)
   // {
         // EOBD_TPS_Buffer[index] = EOBD_TPS_Buffer [index - 1];
   // }

   // /* store the current throttle position */
   // EOBD_TPS_Buffer[0] = EOBD_TPS;
// }

// INLINE void Initialize_TPSBuffer (void)
// {
// uint8_t index;

   // /* Initialize TPS history buffer */
   // for (index = NumOfPrevTPEntries - 1; index > 0; index--)
   // {
       // EOBD_TPS_Buffer[index] = FixConvert(TpPosl, Percent_Plus_Fraction, EOBD_PERCENTa);
   // }
// }

#define Ignition_On()                                     ((bool)(IgnitionOnStatus.IgnitionIsOn))
#define GetFILE_NVM_Failure()                             (EEP_NVM_Fault)
// #define GetVIOS_VehInMfgPlant()                           (PbVIDS_VehInMfgPlant)
#define GetVIOS_VehInMfgPlant()                           (false) //bypass the immo authentication
// #define GetVIOS_VehInMfgPlant()                           (false) //enable the immo authentication
#define GetVIOS_IgnSt()                                   (Ignition_On())
#define GetVIOS_t_EngRunTime()                            (NfVIOS_t_EngRunTime)
#define GetVIOS_EngSt()                                   (VeVIOS_EngSt)
// #define GetVIOS_CoolTempRange()                           (CLT_Range_High)

// #define GetHVMIVEC_StateTrnstngForMisfire()               (CbFALSE)
// #define ClearHVMIVEC_StateTrnstngForMisfire()
// #define GetVIOS_CrankRefToothErrCnt()                     (ToothErrCnt)

// #define GetVIOS_CylNum()                                  (PhysicalEstCylinder)
#define GetVIOS_CylNum()                                  (HAL_Eng_Get_Cyl_Number())
// #define GetVCPC_HW_Avail()                                (CbFALSE)
// #define GetVIOS_IAT_Range()                               (false)


// #define GetIDLE_CondsMet()                              (GetIDLE_Normal_PID_Enabled())
// #define GetINST_InstPresent()                           (LCIInstrumented())
// #define GetFUEL_CL_StoichAF()                           (B_Lc)
// #define GetFUEL_CL_Enable()                             (B_Lc)
// #define GetVIOS_HiResReferencePeriod()                  (ReferencePeriod_HighRes)

#define EMS_ZERO_RPM                              	(60.0)
// #define NbAcClutchStates                                ( 2 )
// #define GetEMS_ShutdownComplete()\
                     // ( (sys_cmd.B_after_run_end) || (B_after_run_end_abnormal) )

// /* not supported */
// #define GetVIOS_PwrSteeringCramped()                    (CbFALSE)
// #define GetTORQ_FuelRatioCorrectionEnabled()            (CbFALSE)
// #define	GetSAID_IntrusiveSystemCondsMet()            	(CbFALSE)
// #define GetIDLE_Pct_IntegCL_Airflow()			(EOBD_dm_Airflow)
// #define GetIDLE_Pct_Airflow()   			(EOBD_dm_Airflow)

// /* for KNOCK */
// #define GetVIOS_CCESC_Enabled_EMS()                     ( EscFlag.EscEnabled )
// #define GetVIOS_CamOccurred()                           ( CamSensorFlags.CamOccurred )
#define GetVIOS_Cam1Occurred()                           (1)
#define GetVIOS_Cam2Occurred()                           (1)
#define GetVIOS_Cam1Stuck()                              CAM_Get_Stuck(CAM1)
#define GetVIOS_Cam2Stuck()                              CAM_Get_Stuck(CAM2)

/* for PIDS */
#define GetFUEL_DFCO_Enabled()                          (B_Fof)

// #if CcSYST_NUM_OF_CYLINDERS ==3
// #define  GetFUEL_AllCylsOn()                   (inj_enable.B_inj_A &&\
                                                // inj_enable.B_inj_B &&\
                                                // inj_enable.B_inj_C)
// #else
// #define  GetFUEL_AllCylsOn()                   (inj_enable.B_inj_A &&\
                                                // inj_enable.B_inj_B &&\
                                                // inj_enable.B_inj_C &&\
                                                // inj_enable.B_inj_D)
// #endif                                                

// #if CcSYST_NUM_OF_CYLINDERS ==3
// #define  GetFUEL_FuelCutOff()                (!(inj_enable.B_inj_A ||\
                                                // inj_enable.B_inj_B ||\
                                                // inj_enable.B_inj_C))
// #else
// #define  GetFUEL_FuelCutOff()                (!(inj_enable.B_inj_A ||\
                                                // inj_enable.B_inj_B ||\
                                                // inj_enable.B_inj_C ||\
                                                // inj_enable.B_inj_D))
// #endif

// #define  GetFUEL_FuelCutOffAny()               ( !GetFUEL_AllCylsOn() )

// #define  GetHWIO_58xCylinderEvent()            (PhysicalEstCylinder)
// #define  GetSPRK_SparkMode()                   (GetVIOS_EngSt())

// #define GetVIOS_O2_12_Htr_PSVIFaultShortHi()\
//    ( DD_GetDiscreteDiagStatus(PULSE_OUT_O2_HEATER_12,OUTPUT_SHORT_CKT_FAULT) )
// #define GetVIOS_O2_12_Htr_PSVIFaultShortLow()\
//    ( DD_GetDiscreteDiagStatus(PULSE_OUT_O2_HEATER_12,OUTPUT_OPEN_CKT_FAULT) )

#define GetOSSP_O2_DiagCntrDsbl()        (CbFALSE)


// #define GetOpenFault(function)       (DD_GetDiscreteDiagStatus(function,OUTPUT_OPEN_CKT_FAULT))
// #define GetShortFault(function)      (DD_GetDiscreteDiagStatus(function,OUTPUT_SHORT_CKT_FAULT))
// #define GetAnyFault(function)        (GetOpenFault(function) || GetShortFault(function))


/******************************************************************************
 * TPIC Fault reading for AcClutch diagnostic 
 ******************************************************************************/
// #define GetVIOS_ACCD_FaultShortHi()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_AC_CLUTCH,OUTPUT_SHORT_CKT_FAULT))
// #define GetVIOS_ACCD_FaultShortLo()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_AC_CLUTCH,OUTPUT_OPEN_CKT_FAULT))
// #define GetVIOS_ACCD_FaultAny()        (GetVIOS_ACCD_FaultShortHi() ||\
                                        // GetVIOS_ACCD_FaultShortLo() )
// #define GetVIOS_ACCD_Presnt()          (true)//(AcFlags.AcPresent)

/******************************************************************************
 * TPIC Fault reading for Main Power Relay diagnostic 
 ******************************************************************************/
// #define GetVIOS_MPRD_FaultShortHi()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_MAINRLY,OUTPUT_SHORT_CKT_FAULT))
// #define GetVIOS_MPRD_FaultShortLo()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_MAINRLY,OUTPUT_OPEN_CKT_FAULT))
// #define GetVIOS_MPRD_FaultAny()        (GetVIOS_MPRD_FaultShortHi());//||GetVIOS_MPRD_FaultShortLo() )
// #define GetVIOS_MPRD_Presnt()          (true)//(IsMPRPresent())
#define GetVIOS_t_IgnOnTime()          (IgnitionOn_Time)
#define GetVIOS_MainPwrRly_Status()    (IsMPRPresent() ? CbTRUE : CbTRUE)
#define IsMPRPresent()\
               (K_MainPowerRelayPresent == true)
#define IsMPRNotPresent()\
               (K_MainPowerRelayPresent == false)
#define GetMPRState()\
               (HAL_GPIO_GET_MPR_Status())

// /******************************************************************************
 // * Power OK Check 
 // ******************************************************************************/
#define GetPowerOK(APP)                         (GetVIOS_PowerOK_##APP())
#define GetVIOS_FPR_PowerOK()                   ( GetPowerOK(FPR) )
#define GetVIOS_FANA_PowerOK()                  ( GetPowerOK(FANA) )
#define GetVIOS_FANB_PowerOK()                  ( GetPowerOK(FANB) )
// #define GetVIOS_FANC_PowerOK()                  ( GetPowerOK(FANC) )
#define GetVIOS_ACCLUTCH_PowerOK()              ( GetPowerOK(ACClutch) )
// #define GetVIOS_SVS_PowerOK()                   ( GetPowerOK(SVS) )
#define GetVIOS_CCP_PowerOK()                   ( GetPowerOK(CCP) )
#define GetVIOS_ETC_PowerOK()                   ( GetPowerOK(ETC) )
#define GetVIOS_O2HEATER_PowerOK()              ( GetPowerOK(O2Heater) )

// /******************************************************************************
 // * To test injectors A,B,C,D 
 // ******************************************************************************/
#define InjectorAFault()            (GetAnyFault(PULSE_OUT_INJ_CYL_A))
#define InjectorAShortHi()          (GetShortFault(PULSE_OUT_INJ_CYL_A))
#define InjectorAShortLo()          (GetOpenFault(PULSE_OUT_INJ_CYL_A))

#define InjectorBFault()            (GetAnyFault(PULSE_OUT_INJ_CYL_B))
#define InjectorBShortHi()          (GetShortFault(PULSE_OUT_INJ_CYL_B))
#define InjectorBShortLo()          (GetOpenFault(PULSE_OUT_INJ_CYL_B))

#define InjectorCFault()            (GetAnyFault(PULSE_OUT_INJ_CYL_C))
#define InjectorCShortHi()          (GetShortFault(PULSE_OUT_INJ_CYL_C))
#define InjectorCShortLo()          (GetOpenFault(PULSE_OUT_INJ_CYL_C))

#define InjectorDFault()            (GetAnyFault(PULSE_OUT_INJ_CYL_D))
#define InjectorDShortHi()          (GetShortFault(PULSE_OUT_INJ_CYL_D))
#define InjectorDShortLo()          (GetOpenFault(PULSE_OUT_INJ_CYL_D))



#define GetAPI_InjCktState(x)       ((((x == INJ_CHANNEL_A)&&(InjectorAFault()))||\
                                     ((x == INJ_CHANNEL_B)&&(InjectorBFault()))||\
                                     ((x == INJ_CHANNEL_C)&&(InjectorCFault()))||\
                                     ((x == INJ_CHANNEL_D)&&(InjectorDFault())))?CeINJ_FAILED:CeINJ_NORMAL)

// /******************************************************************************
 // * To test EST A,B 
 // ******************************************************************************/
// #define GetESTAShortFaultStatus()   (GetShortFault(PULSE_OUT_EST_A)||GetEstLine1HighCurrentFlag())
// #define GetESTAOpenFaultStatus()    (GetOpenFault(PULSE_OUT_EST_A))

#define GetESTAShortFaultStatus()   (GetShortFault(PULSE_OUT_EST_A))
#define GetESTAOpenFaultStatus()    (GetOpenFault(PULSE_OUT_EST_A))
#define ClearESTAShortFaultStatus()   (ClearShortFault(PULSE_OUT_EST_A))
#define ClearESTAOpenFaultStatus()    (ClearOpenFault(PULSE_OUT_EST_A))

// #define GetESTBShortFaultStatus()   (GetShortFault(PULSE_OUT_EST_B)||GetEstLine2HighCurrentFlag())
// #define GetESTBOpenFaultStatus()    (GetOpenFault(PULSE_OUT_EST_B))

#define GetESTBShortFaultStatus()   (GetShortFault(PULSE_OUT_EST_B))
#define GetESTBOpenFaultStatus()    (GetOpenFault(PULSE_OUT_EST_B))
#define ClearESTBShortFaultStatus()   (ClearShortFault(PULSE_OUT_EST_B))
#define ClearESTBOpenFaultStatus()    (ClearOpenFault(PULSE_OUT_EST_B))

INLINE TeEST_CIRCUIT_STATE GetAPI_EST_CircuitState(uint8_t active_estline)
{
	TeEST_CIRCUIT_STATE est_line_fault;

	if ( (active_estline == 0) &&
		(GetESTAShortFaultStatus()||GetESTAOpenFaultStatus()) )
	{
		est_line_fault = CeEST_FAULTED;
		ClearESTAShortFaultStatus();
		ClearESTAOpenFaultStatus();
		// ClearEstLine1HighCurrentFlag();

	}
	else if ( (active_estline == 1) &&
		(GetESTBShortFaultStatus()||GetESTBOpenFaultStatus()) )
	{
		est_line_fault = CeEST_FAULTED;
		ClearESTBShortFaultStatus();
		ClearESTBOpenFaultStatus();
		// ClearEstLine2HighCurrentFlag();
	}
	else
	{
		est_line_fault = CeEST_NOMINAL;
	}

	return(est_line_fault);
}

// INLINE void SetVIOS_MainRlyOff(void)
// {
  // LLD_do_table[LLD_DO_MAIN_RELAY].value  = CbTRUE;
// }

// #define GetVIOS_EstActiveLine()         (EstLineActive)
#define GetVIOS_EstActiveLine()         (TRUE)
#define GetVIOS_SPARKCOIL_PowerOK()     (GetPowerOK(SparkCoil))

// /******************************************************************************
 // * for Chery Can Meters 
 // ******************************************************************************/
extern bool EOBD_CANH_Msg_NotReceived;
#define ReadCANH_Msg_NotReceived()              (EOBD_CANH_Msg_NotReceived)

// /******************************************************************************
 // * for Chery Can Meters 
 // ******************************************************************************/
// extern bool EOBD_LIN_Msg_NotReceived;
// #define ReadLIN_Msg_NotReceived()              (EOBD_LIN_Msg_NotReceived)


// /******************************************************************************
 // * File ROM Checksum Diagnostic 
 // ******************************************************************************/
// #define GetEMSD_FileROM_ChecksumState()          ((OS_CpuInfo.F.FlashChksumFail== (bool)true)?CbTRUE : CbFALSE)

#define GetHWIO_PurgeSolOutputFault()        (GetAnyFault(PULSE_OUT_CANISTER_PURGE))
#define GetHWIO_PurgeSolOutputFaultShortLo() (GetOpenFault(PULSE_OUT_CANISTER_PURGE))
#define GetHWIO_PurgeSolOutputFaultShortHi() (GetShortFault(PULSE_OUT_CANISTER_PURGE))


/* ============================================================================ *\
 * Inline function definition
\* ============================================================================ */
INLINE void ClrVIOS_CrankRefToothErrCnt( void )
{
	// TooFewTeeth = FixDefConst( 0.0, Fixed_Shortcard );
	// TooManyTeeth = FixDefConst( 0.0, Fixed_Shortcard );
	// ToothErrCnt = FixDefConst( 0.0, Fixed_Shortcard );
}

#define GetKNKD_Disable_Fault()   \
	(LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_status.B_max||\
	LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_status.B_min)

void Intr_16msTasks(void);
void Init_IntrParameter(void);
// EOBD_PERCENTa GetDINT_Pct_ThrotPstnOld(uint8_t index);

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
\* ============================================================================ */
#endif /* INTR_DDMS_H */

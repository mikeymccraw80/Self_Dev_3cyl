/* ============================================================================ *\
 * intr_ems.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       intr_ems.c-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, 16 September, 2003 02:41:00 AM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the parameter update function for interface with EMS.
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
#include "types.h"

/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "intr_ems.h"

// temp header file inclusion
#include "hal_esc.h" /* Coolant_Temperature */

/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */
/**********************************************************************/


/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
bool                                 EOBD_ACClutchTrnstng;
bool                                 EOBD_ACClutchTrnstngForMisfire;
bool                                 EOBD_CANH_Msg_NotReceived;
bool                                 EOBD_LIN_Msg_NotReceived;

uint16_t                             EOBD_HiResOdometerAccumB;
uint16_t                             EOBD_17h_RPM_Rescale;
uint8_t                              EOBD_HiResOdometerAccumC;
EOBD_KPAa                            EOBD_Baro;
EOBD_KPAa                            EOBD_UndefMnfdPresFiltd;
EOBD_KPAa                            EOBD_DefFiltdMnfdPres;
EOBD_RATIO_0_2                       EOBD_BLM[Number_of_Cells];
uint8_t                              EOBD_BLM_Number;
EOBD_ANGLEa                          EOBD_SparkAdvanceTopDeadCenter;
EOBD_BPW                             EOBD_SyncFuel_Var;
EOBD_A_DEG_Cb                        EOBD_ConverterTempFilt; 

int16_t                              EOBD_CoolTemp;
int16_t                              EOBD_CoolTempStartup;
int16_t                              EOBD_IntakeTemp;
int16_t                              EOBD_IntakeTempStartup;
int16_t                              EOBD_UndefCoolTemp;

EOBD_KPH                             EOBD_VehSpd;
EOBD_T_PERCENT                       EOBD_RawThrotPstn;
EOBD_T_PERCENT                       EOBD_RawCoolant;
EOBD_AIRFLOW                         EOBD_dm_Airflow;
EOBD_PERCENTa                        EOBD_TPS;
EOBD_PERCENTa                        EOBD_TPS_Buffer[NumOfPrevTPEntries];
EOBD_PERCENTa                        EOBD_UndefTPS;

EOBD_PERCENTa                        EOBD_CcpDutyCycle;
EOBD_KPAa                            EOBD_MAP_Altitude;
EOBD_VOLTb                           EOBD_Ignition_Voltage;
EOBD_VOLTb                           EOBD_IgnVoltageAtKeyOn;
EOBD_T_PERCENT                       EOBD_Pct_RawIntakeAirTemp;
EOBD_T_PERCENT                       EOBD_Pct_RawMAP;
EOBD_T_PERCENT                   EOBD_Pct_RawBRPre;
EOBD_AFR_T                           EOBD_AirFuelRatio;
EOBD_RPMa                            EOBD_Dsr_Eng_Spd;
int16_t                              EOBD_Eng_Spd_Eror;
EOBD_VOLTb                           EOBD_O2_Bank1_Snsr1;
EOBD_VOLTb                           EOBD_O2_Bank1_Snsr2;
EOBD_MULTP_0_TO_2_T                  EOBD_CL_IntMultTermB1;
Percent_Plus_Fraction                EOBD_EngineLoad_MAP_Percent;

kPa_W_EOBD                           EOBD_Vacuum_W_;
Percent0To200_Plus_Fraction          EOBD_ADESC[num_cyl] ;                  /* raw data */
Percent0To200_Plus_Fraction          EOBD_IntegratorAverage[num_cyl] ;      /* filtered value */
T_DECIBELS			     EOBD_ESCGain[num_cyl];

static  CHERY_Lam    LLD_ICMD_Lam;
/* ============================================================================ *\
 * Function definitions
 * ============================================================================ */

/* ============================================================================ *\
 * FUNCTION: GetDINT_Pct_ThrotPstnOld
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   Nil.
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Get the 125ms old TPS.
\* ============================================================================ */
FCALL EOBD_PERCENTa GetDINT_Pct_ThrotPstnOld(uint8_t index)
{
       return  ( index ? (EOBD_TPS_Buffer[(uint8_t)((index -1)/2)]) : EOBD_TPS_Buffer[0]);
}


/* ============================================================================ *\
 * FUNCTION: Init_IntrParameter
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   EOBD_UndefFiltdMnfdPres
 *   EOBD_IgnVoltageAtKeyOn
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Initialize EMS parameters to variables of EOBD_** to be used in EOBD software.
\* ============================================================================ */

FCALL void Init_IntrParameter(void)
{
    /* update Ignition Voltage at Power On */
    ConvertIntrParam_IgnKeyOn();
    /* Update Mileage at Power On */
    ConvertIntrParam_Mileage();
    /* Initialize TPS buffer data */
    Initialize_TPSBuffer();

}
/* ============================================================================ *\
 * Function definitions
 * ============================================================================ */


/* ============================================================================ *\
 * FUNCTION: Intr_16msTasks
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   EOBD_Engine_State
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Update EMS parameters to variables of EOBD_** to be used in EOBD software.
\* ============================================================================ */
FCALL void Intr_16msTasks(void)
{
uint8_t loop_counter;

    /* Convert Ignition Voltage */
    ConvertIntrParam_IgnitionVoltage();
    /* Convert Mileage */
    ConvertIntrParam_Mileage();
    /* Convert Baro */
    ConvertIntrParam_Baro();
    /* Convert MAP */
    ConvertIntrParam_MAP();
    /* Convert Break Pressure */
	//ConvertIntrParam_BRP();
    /* Convert Vacuum */
    ConvertIntrParam_Vacuum();
    /* Convert Engine Coolant Temperature */
    ConvertIntrParam_ECT();
    /* Convert Intake Air Temperature */
    ConvertIntrParam_IAT();
    /* Convert Vehicle Speed */
    ConvertIntrParam_VSS();
    /* Convert Air Flow */
    ConvertIntrParam_Airflow();
    /* Calculate Table Lookup Index */
  //  ConvertIntrParam_TableIndex();
    /* Convert Air Fuel Ratio */
    ConvertIntrParam_AFR();
    /* Convert Idle Speed */
    ConvertIntrParam_IdleSpd();
    /* Convert O2 sensor voltage */
    ConvertIntrParam_O2SensorV();
    /* Convert Spark Advance */
    ConvertIntrParam_SparkAdv();
    /* Convert BPW */
    ConvertIntrParam_BPW();
    /* Convert Catalyst Temperature */
    ConvertIntrParam_ConverterTemp();
    /* Convert Knock Parameters */
    ConvertIntrParam_KnockParam();
    /* Convert CCP solenoid PWM duty cycle */
    ConvertIntrParam_CcpDC();
    /* Convert TPS */
    ConvertIntrParam_TPS();
    
    EOBD_CANH_Msg_NotReceived = ((KbHwio_CheryCanID2E9_Enable&&(bool)VsCAN_CHERY_Receive_Err.CAN_CHERY_ID2E9_ERR) &&
                                                          (KbHwio_CheryCanID310_Enable&&(bool)VsCAN_CHERY_Receive_Err.CAN_CHERY_ID310_ERR) &&
                                                          (KbHwio_CheryCanID391_Enable&&(bool)VsCAN_CHERY_Receive_Err.CAN_CHERY_ID391_ERR) &&
                                                          (KbHwio_CheryCanID3C0_Enable&&(bool)VsCAN_CHERY_Receive_Err.CAN_CHERY_ID3C0_ERR) &&
                                                          (KbHwio_CheryCanID430_Enable&&(bool)VsCAN_CHERY_Receive_Err.CAN_CHERY_ID430_ERR) );

}



/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
\* ============================================================================ */

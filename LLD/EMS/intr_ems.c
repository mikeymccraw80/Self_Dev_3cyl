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
#include "intr_ems.h"
#include "hal_can.h"
#include "vehicle_can_cald.h"

/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
int16_t                              EOBD_CoolTemp;
EOBD_PERCENTa                        EOBD_CcpDutyCycle;
EOBD_PERCENTa                        EOBD_ETCDutyCycle;
EOBD_VOLTb                           EOBD_Ignition_Voltage;
EOBD_VOLTb                           EOBD_IgnVoltageAtKeyOn;

kPa_W_EOBD                           EOBD_Vacuum_W_;
uint16_t                             EOBD_ADESC[CcSYST_NUM_OF_CYLINDERS] ;                  /* raw data */
uint16_t                             EOBD_IntegratorAverage[CcSYST_NUM_OF_CYLINDERS] ;      /* filtered value */
bool                                 EOBD_CANH_Msg_NotReceived;
EOBD_KPH                             EOBD_VehSpd;

void Init_IntrParameter(void)
{
    /* update Ignition Voltage at Power On */
    ConvertIntrParam_IgnKeyOn();
    /* Update Mileage at Power On */
    // ConvertIntrParam_Mileage();
    /* Initialize TPS buffer data */
    // Initialize_TPSBuffer();

}

void Intr_16msTasks(void)
{
    // /* Convert Ignition Voltage */
    ConvertIntrParam_IgnitionVoltage();
    // /* Convert Mileage */
    // ConvertIntrParam_Mileage();
    // /* Convert Baro */
    // ConvertIntrParam_Baro();
    // /* Convert MAP */
    // ConvertIntrParam_MAP();
    /* Convert Vacuum */
    ConvertIntrParam_Vacuum();
    // /* Convert Engine Coolant Temperature */
    // ConvertIntrParam_ECT();
    // /* Convert Intake Air Temperature */
    // ConvertIntrParam_IAT();
    // /* Convert Vehicle Speed */
    // ConvertIntrParam_VSS();
    // /* Convert Air Flow */
    // ConvertIntrParam_Airflow();
    // /* Calculate Table Lookup Index */
    // ConvertIntrParam_TableIndex();
    // /* Convert Air Fuel Ratio */
    // ConvertIntrParam_AFR();
    // /* Convert Idle Speed */
    // ConvertIntrParam_IdleSpd();
    // /* Convert O2 sensor voltage */
    // ConvertIntrParam_O2SensorV();
    // /* Convert Spark Advance */
    // ConvertIntrParam_SparkAdv();
    // /* Convert BPW */
    // ConvertIntrParam_BPW();
    // /* Convert Catalyst Temperature */
    // ConvertIntrParam_ConverterTemp();
    /* Convert Knock Parameters */
    ConvertIntrParam_KnockParam();
    // /* Convert CCP solenoid PWM duty cycle */
    // ConvertIntrParam_CcpDC();
    /* Convert ETC PWM duty cycle */
    ConvertIntrParam_ETCDC();
    // /* Convert TPS */
    // ConvertIntrParam_TPS();
    EOBD_CANH_Msg_NotReceived = ((KbHwio_CheryCanID1AE_Enable&&(bool)VsCAN_Receive_Err.CAN_ID1AE_ERR) ||
                                 (KbHwio_CheryCanID2E9_Enable&&(bool)VsCAN_Receive_Err.CAN_ID2E9_ERR) ||
                                 (KbHwio_CheryCanID310_Enable&&(bool)VsCAN_Receive_Err.CAN_ID310_ERR) ||
                                 (KbHwio_CheryCanID51A_Enable&&(bool)VsCAN_Receive_Err.CAN_ID51A_ERR) ||
                                 (KbHwio_CheryCanID3C0_Enable&&(bool)VsCAN_Receive_Err.CAN_ID3C0_ERR) ||
                                 (KbHwio_CheryCanID430_Enable&&(bool)VsCAN_Receive_Err.CAN_ID430_ERR) );
}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
\* ============================================================================ */

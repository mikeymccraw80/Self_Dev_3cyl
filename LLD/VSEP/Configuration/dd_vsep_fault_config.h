#ifndef DD_VSEP_FAULT_CONFIG_H
#define DD_VSEP_FAULT_CONFIG_H

/*===========================================================================*/
/* FILE: dd_vsep_config.h                                                         */
/*===========================================================================*/
/* COPYRIGHT 2004, Delphi Electronics and Safety Systems.                    */
/* All Rights reserved, Delphi Confidential.                                 */
/*===========================================================================*/
/*===========================================================================*/
/* DESCRIPTION:                                                              */
/*   This file contains HWIO signals configuration.                          */
/*                                                                           */
/*===========================================================================*/
/* REUSE: DO NOT MODIFY THIS FILE.                                           */
/* Co-ordinate any desired changes with the Software Forward Engineering and */
/* Building Blocks group                                                     */
/*===========================================================================*/
#include "reuse.h"
#include "dd_vsep_pwm_interface.h"
#include "dd_vsep_discrete_interface.h"


/*===========================================================================*\
 * Imported Objects
\*===========================================================================*/
extern uint32_t     VSEP_Channel_Enabled;


/********** VSEP related signals STARTS**************/
// PULSE_OUT_INJ_CYL_A
#define PULSE_OUT_INJ_CYL_A_Type                      PORTDISCRETE
#define PULSE_OUT_INJ_CYL_A_Fault                     VSEP_SPIDISCRETE
#define PULSE_OUT_INJ_CYL_A_Pin                       PTT_PTT4
#define PULSE_OUT_INJ_CYL_A_Channel                   MTSA_CONFIG_VSEP_PCH_09
#define PULSE_OUT_INJ_CYL_A_Inverted                  false
#define PULSE_OUT_INJ_CYL_A_Flag                      VSEP_Channel_Enabled
#define PULSE_OUT_INJ_CYL_A_DiagMask                  ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_09),1)))

// PULSE_OUT_INJ_CYL_B
#define PULSE_OUT_INJ_CYL_B_Type                      PORTDISCRETE
#define PULSE_OUT_INJ_CYL_B_Fault                     VSEP_SPIDISCRETE
#define PULSE_OUT_INJ_CYL_B_Pin                       PTT_PTT5
#define PULSE_OUT_INJ_CYL_B_Channel                   MTSA_CONFIG_VSEP_PCH_10
#define PULSE_OUT_INJ_CYL_B_Inverted                  false
#define PULSE_OUT_INJ_CYL_B_Flag                      VSEP_Channel_Enabled
#define PULSE_OUT_INJ_CYL_B_DiagMask                  ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_10),1)))

// PULSE_OUT_INJ_CYL_C
#define PULSE_OUT_INJ_CYL_C_Type                      PORTDISCRETE
#define PULSE_OUT_INJ_CYL_C_Fault                     VSEP_SPIDISCRETE
#define PULSE_OUT_INJ_CYL_C_Pin                       PTT_PTT6
#define PULSE_OUT_INJ_CYL_C_Channel                   MTSA_CONFIG_VSEP_PCH_11
#define PULSE_OUT_INJ_CYL_C_Inverted                  false
#define PULSE_OUT_INJ_CYL_C_Flag                      VSEP_Channel_Enabled
#define PULSE_OUT_INJ_CYL_C_DiagMask                  ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_11),1)))

// PULSE_OUT_INJ_CYL_D
#define PULSE_OUT_INJ_CYL_D_Type                      PORTDISCRETE
#define PULSE_OUT_INJ_CYL_D_Fault                     VSEP_SPIDISCRETE
#define PULSE_OUT_INJ_CYL_D_Pin                       PTT_PTT7
#define PULSE_OUT_INJ_CYL_D_Channel                   MTSA_CONFIG_VSEP_PCH_12
#define PULSE_OUT_INJ_CYL_D_Inverted                  false
#define PULSE_OUT_INJ_CYL_D_Flag                      VSEP_Channel_Enabled
#define PULSE_OUT_INJ_CYL_D_DiagMask                  ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_12),1)))

//PULSE_OUT_EST_A
#define PULSE_OUT_EST_A_Fault                         VSEP_SPIDISCRETE//for diagnostic imformation
#define PULSE_OUT_EST_A_Channel                       MTSA_CONFIG_VSEP_PCH_01//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define PULSE_OUT_EST_A_Flag                          VSEP_Channel_Enabled//this will be revised again
#define PULSE_OUT_EST_A_DiagMask                      ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_01),1)))//this will be revised again
                                                
//PULSE_OUT_EST_B                               
#define PULSE_OUT_EST_B_Fault                         VSEP_SPIDISCRETE//for diagnostic imformation
#define PULSE_OUT_EST_B_Channel                       MTSA_CONFIG_VSEP_PCH_02//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define PULSE_OUT_EST_B_Flag                          VSEP_Channel_Enabled//this will be revised again
#define PULSE_OUT_EST_B_DiagMask                      ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_02),1)))//this will be revised again
                                                
//PULSE_OUT_EST_C                               
#define PULSE_OUT_EST_C_Fault                         VSEP_SPIDISCRETE//for diagnostic imformation
#define PULSE_OUT_EST_C_Channel                       MTSA_CONFIG_VSEP_PCH_03//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define PULSE_OUT_EST_C_Flag                          VSEP_Channel_Enabled//this will be revised again
#define PULSE_OUT_EST_C_DiagMask                      ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_03),1)))//this will be revised again
                                                
//PULSE_OUT_EST_D                               
#define PULSE_OUT_EST_D_Fault                         VSEP_SPIDISCRETE//for diagnostic imformation
#define PULSE_OUT_EST_D_Channel                       MTSA_CONFIG_VSEP_PCH_04//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define PULSE_OUT_EST_D_Flag                          VSEP_Channel_Enabled//this will be revised again
#define PULSE_OUT_EST_D_DiagMask                      ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_04),1)))//this will be revised again

//DISCRETE_OUT_FAN_INTERCOOLER  vsep control
#define MTSA_CONFIG_D_OUT_FAN_INTERCOOLER	0
#define DISCRETE_OUT_FAN_INTERCOOLER_Type                VSEP_SPIDISCRETE// for output control
#define DISCRETE_OUT_FAN_INTERCOOLER_Fault                VSEP_SPIDISCRETE//for diagnostic imformation
#define DISCRETE_OUT_FAN_INTERCOOLER_Pin                    MTSA_CONFIG_VSEP_PCH_19
#define DISCRETE_OUT_FAN_INTERCOOLER_Channel            MTSA_CONFIG_VSEP_PCH_19
#define DISCRETE_OUT_FAN_INTERCOOLER_Inverted          VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_19)
#define DISCRETE_OUT_FAN_INTERCOOLER_Flag                 VSEP_Channel_Enabled
#define DISCRETE_OUT_FAN_INTERCOOLER_DiagMask         ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_19),1)))

//DISCRETE_OUT_IMMOREQ  vsep control share channel with SAIC-relay
#define DISCRETE_OUT_IMMOREQ_Type                                     VSEP_SPIDISCRETE// for output control
#define DISCRETE_OUT_IMMOREQ_Fault                                     VSEP_SPIDISCRETE //for diagnostic imformation
#define DISCRETE_OUT_IMMOREQ_Pin                                        MTSA_CONFIG_VSEP_PCH_14
#define DISCRETE_OUT_IMMOREQ_Channel                                MTSA_CONFIG_VSEP_PCH_14
#define DISCRETE_OUT_IMMOREQ_Inverted                              VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_14)
#define DISCRETE_OUT_IMMOREQ_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_IMMOREQ_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_14),1)))

//DISCRETE_OUT_FAN_1  vsep control share channel withPWM FAN
#define DISCRETE_OUT_FAN_1_Type                                     VSEP_PWMSPIDISCRETE// for output control
#define DISCRETE_OUT_FAN_1_Fault                                     VSEP_PWMSPIDISCRETE//for diagnostic imformation
#define DISCRETE_OUT_FAN_1_Pin                                        MTSA_CONFIG_VSEP_PCH_15
#define DISCRETE_OUT_FAN_1_Channel                                MTSA_CONFIG_VSEP_PCH_15
#define DISCRETE_OUT_FAN_1_Inverted                              VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_15)
#define DISCRETE_OUT_FAN_1_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_FAN_1_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_15),1)))

//DISCRETE_OUT_MAINRLY
#define DISCRETE_OUT_MAINRLY_Type                                  VSEP_SPIDISCRETE// for output control
#define DISCRETE_OUT_MAINRLY_Fault                                  VSEP_SPIDISCRETE//for diagnostic imformation
#define DISCRETE_OUT_MAINRLY_Pin                                     MTSA_CONFIG_VSEP_PCH_05// for output control 
#define DISCRETE_OUT_MAINRLY_Channel                              MTSA_CONFIG_VSEP_PCH_05//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define DISCRETE_OUT_MAINRLY_Inverted                            VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_05)//for vsep control channel, that information is not needed, but you still can remain it for the common format
#define DISCRETE_OUT_MAINRLY_Flag                                   VSEP_Channel_Enabled//this will be revised again
#define DISCRETE_OUT_MAINRLY_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_05),1)))//this will be revised again

//DISCRETE_OUT_FUEL_PUMP
#define DISCRETE_OUT_FUEL_PUMP_Type                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_FUEL_PUMP_Fault                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_FUEL_PUMP_Pin                                     MTSA_CONFIG_VSEP_PCH_06
#define DISCRETE_OUT_FUEL_PUMP_Channel                             MTSA_CONFIG_VSEP_PCH_06
#define DISCRETE_OUT_FUEL_PUMP_Inverted                              VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_06)
#define DISCRETE_OUT_FUEL_PUMP_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_FUEL_PUMP_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_06),1)))//????

//DISCRETE_OUT_AC_CLUTCH
#define DISCRETE_OUT_AC_CLUTCH_Type                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_AC_CLUTCH_Fault                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_AC_CLUTCH_Pin                                     MTSA_CONFIG_VSEP_PCH_07
#define DISCRETE_OUT_AC_CLUTCH_Channel                             MTSA_CONFIG_VSEP_PCH_07
#define DISCRETE_OUT_AC_CLUTCH_Inverted                             VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_07)
#define DISCRETE_OUT_AC_CLUTCH_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_AC_CLUTCH_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_07),1)))//????

//DISCRETE_OUT_FAN_2
#define DISCRETE_OUT_FAN_2_Type                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_FAN_2_Fault                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_FAN_2_Pin                                     MTSA_CONFIG_VSEP_PCH_08
#define DISCRETE_OUT_FAN_2_Channel                             MTSA_CONFIG_VSEP_PCH_08
#define DISCRETE_OUT_FAN_2_Inverted                             VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_08)
#define DISCRETE_OUT_FAN_2_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_FAN_2_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_08),1)))//????

// DISCRETE_OUT_TRIP_COMPUTER
#define DISCRETE_OUT_TRIP_COMPUTER_Type                                  PORTDISCRETE// for output control
#define DISCRETE_OUT_TRIP_COMPUTER_Fault                                  VSEP_SPIDISCRETE//for diagnostic imformation
#define DISCRETE_OUT_TRIP_COMPUTER_Pin                                     PORTK_PK6// for output control 
#define DISCRETE_OUT_TRIP_COMPUTER_Channel                              MTSA_CONFIG_VSEP_PCH_13//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define DISCRETE_OUT_TRIP_COMPUTER_Inverted                              false//for vsep control channel, that information is not needed, but you still can remain it for the common format
#define DISCRETE_OUT_TRIP_COMPUTER_Flag                                   VSEP_Channel_Enabled//this will be revised again
#define DISCRETE_OUT_TRIP_COMPUTER_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_13),1)))//this will be revised again

//DISCRETE_OUT_AIR_VALVE  VSEP SAIC control
#define DISCRETE_OUT_AIR_VALVE_Type                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_AIR_VALVE_Fault                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_AIR_VALVE_Pin                                     MTSA_CONFIG_VSEP_PCH_14
#define DISCRETE_OUT_AIR_VALVE_Channel                             MTSA_CONFIG_VSEP_PCH_14
#define DISCRETE_OUT_AIR_VALVE_Inverted                             VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_14)
#define DISCRETE_OUT_AIR_VALVE_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_AIR_VALVE_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_14),1)))//????

//DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE
#define DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE_Type                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE_Fault                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE_Pin                                     MTSA_CONFIG_VSEP_PCH_23
#define DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE_Channel                             MTSA_CONFIG_VSEP_PCH_23
#define DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE_Inverted                              VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_23)
#define DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_23),1)))//????

//DISCRETE_OUT_SS_STATUS_LAMP
#define DISCRETE_OUT_SS_STATUS_LAMP_Type                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_SS_STATUS_LAMP_Fault                                  VSEP_SPIDISCRETE
#define DISCRETE_OUT_SS_STATUS_LAMP_Pin                                     MTSA_CONFIG_VSEP_PCH_23
#define DISCRETE_OUT_SS_STATUS_LAMP_Channel                             MTSA_CONFIG_VSEP_PCH_23
#define DISCRETE_OUT_SS_STATUS_LAMP_Inverted                              VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_23)
#define DISCRETE_OUT_SS_STATUS_LAMP_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_SS_STATUS_LAMP_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_23),1)))// SS Status lamp

//DISCRETE_OUT_OBD2_LAMP  vsep control
#define DISCRETE_OUT_OBD2_LAMP_Type                                  VSEP_SPIDISCRETE// for output control
#define DISCRETE_OUT_OBD2_LAMP_Fault                                  VSEP_SPIDISCRETE//for diagnostic imformation
#define DISCRETE_OUT_OBD2_LAMP_Pin                                     MTSA_CONFIG_VSEP_PCH_25// for output control 
#define DISCRETE_OUT_OBD2_LAMP_Channel                             MTSA_CONFIG_VSEP_PCH_25//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define DISCRETE_OUT_OBD2_LAMP_Inverted                              VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_25)//for vsep control channel, that information is not needed, but you still can remain it for the common format
#define DISCRETE_OUT_OBD2_LAMP_Flag                                   	VSEP_Channel_Enabled//this will be revised again
#define DISCRETE_OUT_OBD2_LAMP_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_25),1)))//this will be revised again

//DISCRETE_OUT_SES_LAMP
#define DISCRETE_OUT_SES_LAMP_Type                                   VSEP_SPIDISCRETE
#define DISCRETE_OUT_SES_LAMP_Fault                                   VSEP_SPIDISCRETE
#define DISCRETE_OUT_SES_LAMP_Pin                                      MTSA_CONFIG_VSEP_PCH_26
#define DISCRETE_OUT_SES_LAMP_Channel                              MTSA_CONFIG_VSEP_PCH_26
#define DISCRETE_OUT_SES_LAMP_Inverted                              VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_26)
#define DISCRETE_OUT_SES_LAMP_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_SES_LAMP_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_26),1)))//????

//DISCRETE_OUT_SS_CLUSTER_TT_DISABLE
#define DISCRETE_OUT_SS_CLUSTER_TT_DISABLE_Type                       VSEP_SPIDISCRETE
#define DISCRETE_OUT_SS_CLUSTER_TT_DISABLE_Fault                       VSEP_SPIDISCRETE
#define DISCRETE_OUT_SS_CLUSTER_TT_DISABLE_Pin                          MTSA_CONFIG_VSEP_PCH_26
#define DISCRETE_OUT_SS_CLUSTER_TT_DISABLE_Channel                  MTSA_CONFIG_VSEP_PCH_26
#define DISCRETE_OUT_SS_CLUSTER_TT_DISABLE_Inverted                 VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_26)
#define DISCRETE_OUT_SS_CLUSTER_TT_DISABLE_Flag                      	VSEP_Channel_Enabled
#define DISCRETE_OUT_SS_CLUSTER_TT_DISABLE_DiagMask               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_26),1)))// SS Cluster TT Disable

// DISCRETE_OUT_VIS_OUTPUT1
#define MTSA_CONFIG_D_OUT_VIS1		0
#define DISCRETE_OUT_VIS_OUTPUT1_Type			VSEP_SPIDISCRETE
#define DISCRETE_OUT_VIS_OUTPUT1_Fault			VSEP_SPIDISCRETE
#define DISCRETE_OUT_VIS_OUTPUT1_Pin				MTSA_CONFIG_VSEP_PCH_19
#define DISCRETE_OUT_VIS_OUTPUT1_Channel		MTSA_CONFIG_VSEP_PCH_19
#define DISCRETE_OUT_VIS_OUTPUT1_Inverted	VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_19)
#define DISCRETE_OUT_VIS_OUTPUT1_Flag			VSEP_Channel_Enabled
#define DISCRETE_OUT_VIS_OUTPUT1_DiagMask	((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_19),1)))//????

// DISCRETE_OUT_VIS_OUTPUT1
//#define MTSA_CONFIG_D_OUT_SS_VIS1		0
//#define DISCRETE_OUT_VIS_OUTPUT1_SS_Type			MT20_UNUSED
//#define DISCRETE_OUT_VIS_OUTPUT1_SS_DiagMask		NO_DIAGNOSTIC_MASK

// DISCRETE_OUT_VIS_OUTPUT2
#define MTSA_CONFIG_D_OUT_VIS2		0
#define DISCRETE_OUT_VIS_OUTPUT2_Type			VSEP_SPIDISCRETE
#define DISCRETE_OUT_VIS_OUTPUT2_Fault			VSEP_SPIDISCRETE
#define DISCRETE_OUT_VIS_OUTPUT2_Pin			MTSA_CONFIG_VSEP_PCH_20
#define DISCRETE_OUT_VIS_OUTPUT2_Channel		MTSA_CONFIG_VSEP_PCH_20
#define DISCRETE_OUT_VIS_OUTPUT2_Inverted		VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_20)
#define DISCRETE_OUT_VIS_OUTPUT2_Flag			VSEP_Channel_Enabled
#define DISCRETE_OUT_VIS_OUTPUT2_DiagMask		((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_20),1)))//????

// DISCRETE_OUT_VIS_OUTPUT2
#define MTSA_CONFIG_D_OUT_SS_VIS2		0
#define DISCRETE_OUT_VIS_OUTPUT2_SS_Type			MT20_UNUSED
#define DISCRETE_OUT_VIS_OUTPUT2_SS_DiagMask		NO_DIAGNOSTIC_MASK

// DISCRETE_OUT_BRAKE_BOOST_PUMP
#define DISCRETE_OUT_BRAKE_BOOST_PUMP_Type			VSEP_SPIDISCRETE
#define DISCRETE_OUT_BRAKE_BOOST_PUMP_Fault			VSEP_SPIDISCRETE
#define DISCRETE_OUT_BRAKE_BOOST_PUMP_Pin			MTSA_CONFIG_VSEP_PCH_20
#define DISCRETE_OUT_BRAKE_BOOST_PUMP_Channel		MTSA_CONFIG_VSEP_PCH_20
#define DISCRETE_OUT_BRAKE_BOOST_PUMP_Inverted		VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_20)
#define DISCRETE_OUT_BRAKE_BOOST_PUMP_Flag			VSEP_Channel_Enabled
#define DISCRETE_OUT_BRAKE_BOOST_PUMP_DiagMask		((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_20),1)))//????


//PWM CHANNEL

//PULSE_OUT_VCPS_B1_INTK Micro-p PWM
#define PULSE_OUT_VCPS_B1_INTK_Type                PORTPWM// for output control
#define PULSE_OUT_VCPS_B1_INTK_Fault               VSEP_SPIPWM//for diagnostic imformation
#define PULSE_OUT_VCPS_B1_INTK_Pin                   PWM01// for output control
#define PULSE_OUT_VCPS_B1_INTK_Channel             MTSA_CONFIG_VSEP_PCH_17//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define PULSE_OUT_VCPS_B1_INTK_Ch                   (PWME_PWME1_MASK)
#define PULSE_OUT_VCPS_B1_INTK_Flag                VSEP_Channel_Enabled//this will be revised again
#define PULSE_OUT_VCPS_B1_INTK_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_17),1)))//this will be revised again

// PULSE_OUT_ETC
#define PULSE_OUT_ETC_Type                           PORTPWM
#define PULSE_OUT_ETC_Pin                            PWM23
#define PULSE_OUT_ETC_Ch                            PWME_PWME3_MASK
#define PULSE_OUT_ETC_Flag                           VSEP_Channel_Enabled
#define PULSE_OUT_ETC_DiagMask                      (0x0010) //?????

//PULSE_OUT_VCPS_B1_EXH
#define PULSE_OUT_VCPS_B1_EXH_Type                PORTPWM
#define PULSE_OUT_VCPS_B1_EXH_Fault               VSEP_SPIPWM
#define PULSE_OUT_VCPS_B1_EXH_Pin                   PWM45
#define PULSE_OUT_VCPS_B1_EXH_Channel          MTSA_CONFIG_VSEP_PCH_18
#define PULSE_OUT_VCPS_B1_EXH_Ch                    (PWME_PWME5_MASK)
#define PULSE_OUT_VCPS_B1_EXH_Flag                VSEP_Channel_Enabled
#define PULSE_OUT_VCPS_B1_EXH_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_18),1)))//?????

// PULSE_OUT_LINEAR_EGR
//#define PULSE_OUT_LINEAR_EGR_Type                    PORTPWM
//#define PULSE_OUT_LINEAR_EGR_Fault                   VSEP_SPIPWM
//#define PULSE_OUT_LINEAR_EGR_Pin                     PWM45
//#define PULSE_OUT_LINEAR_EGR_Channel                 MTSA_CONFIG_VSEP_PCH_18
//#define PULSE_OUT_LINEAR_EGR_Flag                    VSEP_Channel_Enabled
//#define PULSE_OUT_LINEAR_EGR_DiagMask                ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_18),1))) //?????

//PULSE_OUT_AIR_PUMP_SPEED
#define PULSE_OUT_AIR_PUMP_SPEED_Type		VSEP_SPIPWM
#define PULSE_OUT_AIR_PUMP_SPEED_Fault		VSEP_SPIPWM
#define PULSE_OUT_AIR_PUMP_SPEED_Pin			MTSA_CONFIG_VSEP_PCH_28
#define PULSE_OUT_AIR_PUMP_SPEED_Channel		MTSA_CONFIG_VSEP_PCH_28
#define PULSE_OUT_AIR_PUMP_SPEED_Ch			MTSA_CONFIG_VSEP_PCH_28
#define PULSE_OUT_AIR_PUMP_SPEED_Flag		VSEP_Channel_Enabled
#define PULSE_OUT_AIR_PUMP_SPEED_DiagMask	((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_28),1)))//?????

// PULSE_OUT_TACHOMETER
#define PULSE_OUT_TACHOMETER_Type		VSEP_SPIPWM
#define PULSE_OUT_TACHOMETER_Fault		VSEP_SPIPWM
#define PULSE_OUT_TACHOMETER_Pin		MTSA_CONFIG_VSEP_PCH_29
#define PULSE_OUT_TACHOMETER_Channel		MTSA_CONFIG_VSEP_PCH_29
#define PULSE_OUT_TACHOMETER_Ch		MTSA_CONFIG_VSEP_PCH_29
#define PULSE_OUT_TACHOMETER_Flag		VSEP_Channel_Enabled
#define PULSE_OUT_TACHOMETER_DiagMask	((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_29),1)))//?????

//VSEP PWM OUTPUT
//PULSE_OUT_FAN_PWM VSEP PWM
#define PULSE_OUT_FAN_PWM_Type			VSEP_SPIPWM
#define PULSE_OUT_FAN_PWM_Fault			VSEP_SPIPWM
#define PULSE_OUT_FAN_PWM_Pin			MTSA_CONFIG_VSEP_PCH_15
#define PULSE_OUT_FAN_PWM_Channel		MTSA_CONFIG_VSEP_PCH_15
#define PULSE_OUT_FAN_PWM_Ch			MTSA_CONFIG_VSEP_PCH_15
#define PULSE_OUT_FAN_PWM_Flag			VSEP_Channel_Enabled
#define PULSE_OUT_FAN_PWM_DiagMask		((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_15),1)))//?????

//PULSE_OUT_CANISTER_PURGE VSEP PWM
#define PULSE_OUT_CANISTER_PURGE_Type		VSEP_SPIPWM
#define PULSE_OUT_CANISTER_PURGE_Fault		VSEP_SPIPWM
#define PULSE_OUT_CANISTER_PURGE_Pin		MTSA_CONFIG_VSEP_PCH_16
#define PULSE_OUT_CANISTER_PURGE_Channel	MTSA_CONFIG_VSEP_PCH_16
#define PULSE_OUT_CANISTER_PURGE_Ch		MTSA_CONFIG_VSEP_PCH_16
#define PULSE_OUT_CANISTER_PURGE_Flag		VSEP_Channel_Enabled
#define PULSE_OUT_CANISTER_PURGE_DiagMask	((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_16),1)))//?????

// PULSE_OUT_O2_HEATER_11 VSEP PWM
#define PULSE_OUT_O2_HEATER_11_Type		VSEP_SPIPWM// for output control
#define PULSE_OUT_O2_HEATER_11_Fault		VSEP_SPIPWM//for diagnostic imformation
#define PULSE_OUT_O2_HEATER_11_Pin		MTSA_CONFIG_VSEP_PCH_21// for output control
#define PULSE_OUT_O2_HEATER_11_Channel		MTSA_CONFIG_VSEP_PCH_21//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define PULSE_OUT_O2_HEATER_11_Ch		MTSA_CONFIG_VSEP_PCH_21//for DD_PWMEnable & DD_PWMDisable, the vsep channel can not support now
#define PULSE_OUT_O2_HEATER_11_Flag		VSEP_Channel_Enabled//this will be revised again
#define PULSE_OUT_O2_HEATER_11_DiagMask		((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_21),1)))//this will be revised again

// PULSE_OUT_O2_HEATER_12 VSEP PWM
#define PULSE_OUT_O2_HEATER_12_Type                VSEP_SPIPWM// for output control
#define PULSE_OUT_O2_HEATER_12_Fault               VSEP_SPIPWM//for diagnostic imformation
#define PULSE_OUT_O2_HEATER_12_Pin                   MTSA_CONFIG_VSEP_PCH_22// for output control
#define PULSE_OUT_O2_HEATER_12_Channel           MTSA_CONFIG_VSEP_PCH_22//will be used in DD_GetDiscreteDiagStatus & DD_ClearDiscreteDiagStatus
#define PULSE_OUT_O2_HEATER_12_Ch		MTSA_CONFIG_VSEP_PCH_22//for DD_PWMEnable & DD_PWMDisable, the vsep channel can not support now
#define PULSE_OUT_O2_HEATER_12_Flag                VSEP_Channel_Enabled//this will be revised again
#define PULSE_OUT_O2_HEATER_12_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_22),1)))//this will be revised again

//PULSE_OUT_TURBO_WG_PWM
#define PULSE_OUT_TURBO_WG_PWM_Type                VSEP_SPIPWM
#define PULSE_OUT_TURBO_WG_PWM_Fault               VSEP_SPIPWM
#define PULSE_OUT_TURBO_WG_PWM_Pin                   MTSA_CONFIG_VSEP_PCH_24
#define PULSE_OUT_TURBO_WG_PWM_Channel          MTSA_CONFIG_VSEP_PCH_24
#define PULSE_OUT_TURBO_WG_PWM_Ch                   MTSA_CONFIG_VSEP_PCH_24
#define PULSE_OUT_TURBO_WG_PWM_Flag                VSEP_Channel_Enabled
#define PULSE_OUT_TURBO_WG_PWM_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_24),1)))//?????

//PULSE_OUT_SS_STARTER_RELAY_PWM
#define PULSE_OUT_SS_STARTER_RELAY_PWM_Type                VSEP_SPIPWM
#define PULSE_OUT_SS_STARTER_RELAY_PWM_Fault               VSEP_SPIPWM
#define PULSE_OUT_SS_STARTER_RELAY_PWM_Pin                   MTSA_CONFIG_VSEP_PCH_24
#define PULSE_OUT_SS_STARTER_RELAY_PWM_Channel          MTSA_CONFIG_VSEP_PCH_24
#define PULSE_OUT_SS_STARTER_RELAY_PWM_Flag                VSEP_Channel_Enabled
#define PULSE_OUT_SS_STARTER_RELAY_PWM_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_24),1)))// SS Starter Relay

//PULSE_OUT_COOL_TEMP_PWM
#define PULSE_OUT_COOL_TEMP_PWM_Type                VSEP_SPIPWM
#define PULSE_OUT_COOL_TEMP_PWM_Fault               VSEP_SPIPWM
#define PULSE_OUT_COOL_TEMP_PWM_Pin                   MTSA_CONFIG_VSEP_PCH_27
#define PULSE_OUT_COOL_TEMP_PWM_Channel          MTSA_CONFIG_VSEP_PCH_27
#define PULSE_OUT_COOL_TEMP_PWM_Ch                   MTSA_CONFIG_VSEP_PCH_27
#define PULSE_OUT_COOL_TEMP_PWM_Flag                VSEP_Channel_Enabled
#define PULSE_OUT_COOL_TEMP_PWM_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_27),1)))//?????

//PULSE_OUT_ELECTRIC_THERMOSTAT
#define PULSE_OUT_ELECTRIC_THERMOSTAT_Type                VSEP_SPIPWM
#define PULSE_OUT_ELECTRIC_THERMOSTAT_Fault               VSEP_SPIPWM
#define PULSE_OUT_ELECTRIC_THERMOSTAT_Pin                   MTSA_CONFIG_VSEP_PCH_27
#define PULSE_OUT_ELECTRIC_THERMOSTAT_Channel          MTSA_CONFIG_VSEP_PCH_27
#define PULSE_OUT_ELECTRIC_THERMOSTAT_Ch                   MTSA_CONFIG_VSEP_PCH_27
#define PULSE_OUT_ELECTRIC_THERMOSTAT_Flag                VSEP_Channel_Enabled
#define PULSE_OUT_ELECTRIC_THERMOSTAT_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_27),1)))//?????

//PULSE_OUT_TURBVGT
#define PULSE_OUT_TURBVGT_Type                VSEP_SPIPWM
#define PULSE_OUT_TURBVGT_Fault               VSEP_SPIPWM
#define PULSE_OUT_TURBVGT_Pin                   MTSA_CONFIG_VSEP_PCH_24
#define PULSE_OUT_TURBVGT_Channel          MTSA_CONFIG_VSEP_PCH_24
#define PULSE_OUT_TURBVGT_Flag                VSEP_Channel_Enabled
#define PULSE_OUT_TURBVGT_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_24),1)))//?????

//PULSE_OUT_SS_ALTERNATOR_OUTPUT_PWM
#define PULSE_OUT_SS_ALTERNATOR_OUTPUT_PWM_Type                VSEP_SPIPWM
#define PULSE_OUT_SS_ALTERNATOR_OUTPUT_PWM_Fault               VSEP_SPIPWM
#define PULSE_OUT_SS_ALTERNATOR_OUTPUT_PWM_Pin                   MTSA_CONFIG_VSEP_PCH_28
#define PULSE_OUT_SS_ALTERNATOR_OUTPUT_PWM_Channel          MTSA_CONFIG_VSEP_PCH_28
#define PULSE_OUT_SS_ALTERNATOR_OUTPUT_PWM_Flag                VSEP_Channel_Enabled
#define PULSE_OUT_SS_ALTERNATOR_OUTPUT_PWM_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_28),1)))// SS Alternator PWM Output

#define MTSA_CONFIG_PWM_VCPS_B2_INTK 0
//PULSE_OUT_VCPS_B2_INTK VSEP PWM
#define PULSE_OUT_VCPS_B2_INTK_Type                VSEP_SPIPWM
#define PULSE_OUT_VCPS_B2_INTK_Fault               VSEP_SPIPWM
#define PULSE_OUT_VCPS_B2_INTK_Pin                   MTSA_CONFIG_PWM_VCPS_B2_INTK
#define PULSE_OUT_VCPS_B2_INTK_Channel             MTSA_CONFIG_PWM_VCPS_B2_INTK
#define PULSE_OUT_VCPS_B2_INTK_Flag                VSEP_Channel_Enabled
#define PULSE_OUT_VCPS_B2_INTK_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_PWM_VCPS_B2_INTK),1)))//?????

#define MTSA_CONFIG_PWM_VCPS_B2_EXH 0
//PULSE_OUT_VCPS_B2_EXH VSEP PWM
#define PULSE_OUT_VCPS_B2_EXH_Type                VSEP_SPIPWM
#define PULSE_OUT_VCPS_B2_EXH_Fault               VSEP_SPIPWM
#define PULSE_OUT_VCPS_B2_EXH_Pin                   MTSA_CONFIG_PWM_VCPS_B2_EXH
#define PULSE_OUT_VCPS_B2_EXH_Channel             MTSA_CONFIG_PWM_VCPS_B2_EXH
#define PULSE_OUT_VCPS_B2_EXH_Flag                VSEP_Channel_Enabled
#define PULSE_OUT_VCPS_B2_EXH_DiagMask            ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_PWM_VCPS_B2_EXH),1)))//?????

//DISCRETE_OUT_VVT1  vsep control share channel with SAIC-relay and VCM_Valve // Added by czh2h9 at May22 2009  
#define DISCRETE_OUT_VCM_Vlv_Type                                     VSEP_SPIDISCRETE// for output control
#define DISCRETE_OUT_VCM_Vlv_Fault                                     VSEP_SPIDISCRETE //for diagnostic imformation
#define DISCRETE_OUT_VCM_Vlv_Pin                                        MTSA_CONFIG_VSEP_PCH_17
#define DISCRETE_OUT_VCM_Vlv_Channel                                MTSA_CONFIG_VSEP_PCH_17
#define DISCRETE_OUT_VCM_Vlv_Inverted                              VSEP_PCH_Get_Inverte_State(MTSA_CONFIG_VSEP_PCH_17)
#define DISCRETE_OUT_VCM_Vlv_Flag                                   	VSEP_Channel_Enabled
#define DISCRETE_OUT_VCM_Vlv_DiagMask                               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_17),1)))

/********** VSEP related signals ENDS**************/

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Rev  Date         user id     SCR       (description on following lines)
 * ---  ------       -------     ---
 *  
\*==========================================================================*/
#endif /* DD_VSEP_CONFIG_H */

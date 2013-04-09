#ifndef IO_INTERFACE_DIAG_H
#define IO_INTERFACE_DIAG_H
/* ============================================================================ *\
 * hal_diag.h
 * ============================================================================
 * Copyright 1999,2004 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       io_interface_diag.h
 * Revision:        1
 * Creation date:
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
\* ============================================================================ */

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
#include "HLS.h"

/*===========================================================================*\
 * Interface Variable Status Macros
\*===========================================================================*/
#define Bit_failed          0x80 /*signal failed * comprehending min, max and sig*/
#define Bit_fail_pending    0x40 /*signal failure pending */
#define Bit_max             0x20 /* signal value high or short to battery */
#define Bit_min             0x10 /* signal value low or short to ground */
#define Bit_sig             0x08 /* signal open load */
#define Bit_npl             0x04 /* reserved position for HLS signal value non-plausible ( for EOBD) */
#define Bit_substitute      0x02 /* substitute value is being passed by LLD */
#define Bit_clrerr          0x01 /* reserved position for HLS */

#define OUT_SHORT_HIGH     ( Bit_max )
#define OUT_SHORT_LOW      ( Bit_min | Bit_sig )
#define OUT_FAIL           ( Bit_failed )
#define OUT_SUBSTITUTE     ( Bit_substitute )
#define OUT_FAIL_MASK      (0x7D)
                          
#define OUT_FAULT_CLEAR    ( 0 )


/* EST */
#define Diag_EST_A_Status   *((uint8_t *)&(ign_sig[LLD_IGN_CHANNEL_A].status))
#define Diag_EST_B_Status   *((uint8_t *)&(ign_sig[LLD_IGN_CHANNEL_B].status))
#define Diag_EST_C_Status   *((uint8_t *)&(ign_sig[LLD_IGN_CHANNEL_C].status))
#define Diag_EST_D_Status   *((uint8_t *)&(ign_sig[LLD_IGN_CHANNEL_D].status))

/* Injection */
#define Diag_INJ_A_Status   *((uint8_t *)&(inj_sig[INJ_CHANNEL_A].status))
#define Diag_INJ_B_Status   *((uint8_t *)&(inj_sig[INJ_CHANNEL_B].status))
#define Diag_INJ_C_Status   *((uint8_t *)&(inj_sig[INJ_CHANNEL_C].status))
#define Diag_INJ_D_Status   *((uint8_t *)&(inj_sig[INJ_CHANNEL_D].status))

/* Digital Output */
#define Diag_MIL_Status      *((uint8_t *)&(LLD_do_table[LLD_DO_MIL_LAMP].status))
#define Diag_SVS_Status      *((uint8_t *)&(LLD_do_table[LLD_DO_SVS_LAMP].status))
#define Diag_Fan1_Status     *((uint8_t *)&(LLD_do_table[LLD_DO_FAN1].status))
#define Diag_Fan2_Status     *((uint8_t *)&(LLD_do_table[LLD_DO_FAN2].status))
#define Diag_MainRly_Status  *((uint8_t *)&(LLD_do_table[LLD_DO_MAIN_RELAY].status))
#define Diag_FulPump_Status  *((uint8_t *)&(LLD_do_table[LLD_DO_FUEL_PUMP].status))
#define Diag_ACCluch_Status  *((uint8_t *)&(LLD_do_table[LLD_DO_AC_CLUTCH].status))
#define Diag_Purge_Status    *((uint8_t *)&(LLD_pwm_out_table[LLD_PWM_PURGE].status))
#define Diag_O2AHeat_Status  *((uint8_t *)&(LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].status))
#define Diag_O2BHeat_Status  *((uint8_t *)&(LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].status))
#define Diag_ECT_PWM_Status  *((uint8_t *)&(LLD_pwm_out_table[LLD_PWM_ECT].status))
#define Diag_TACHO_Status    *((uint8_t *)&(LLD_pwm_out_table[LLD_PWM_TACHO].status))
#define Diag_FulCsum_Status  *((uint8_t *)&(LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].status))

/* Analog Input */
#define Diag_Map_Status      *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_status))
#define Diag_O2ASesor_Status *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_1].LLD_atd_status))
#define Diag_O2BSesor_Status *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_2].LLD_atd_status))
#define Diag_TA_Status       *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_TA].LLD_atd_status))
#define Diag_ECT_Status      *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_ECT].LLD_atd_status))
#define Diag_BattVtg_Status  *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_VBATT_SW].LLD_atd_status))
 #define Diag_TPS1_Status    *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_THROTTLE_1].LLD_atd_status))
#define Diag_TPS2_Status     *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_THROTTLE_2].LLD_atd_status))
#define Diag_PPS1_Status     *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_PEDAL_1].LLD_atd_status))
#define Diag_PPS2_Status     *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_PEDAL_2].LLD_atd_status))
#define Diag_ACP_Status      *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_AC_PRESSURE].LLD_atd_status))
#define Diag_FETEP_Status    *((uint8_t *)&(LLD_atd_input_table[LLD_ATD_FRONT_EVAP_TEMP].LLD_atd_status))


/*===========================================================================*\
 * Analog variable Diag Macros
\*===========================================================================*/
#define K_Map_Default      		(word)(831)//4.06v
#define K_O2sensor_Default 	(word)(92)//450mv
#define K_TA_Default      	 		(word)(733)//3.58v
#define K_ECT_Default      		(word)(733)//3.58v
#define K_TPS1_Default      		(word)(164)
#define K_TPS2_Default      		(word)(831)
#define K_PPS1_Default      		(word)(160)
#define K_PPS2_Default      		(word)(850)
#define K_FETEP_Default   		(word)(850)
#define K_ACP_Default				(word)(850)



#define K_Vbatt_TooHigh    (word)(0.9 * 65535)
#define K_Vbatt_TooLow     (word)(0.1 * 65535)

#define Rescale_1s_To_10ms(x) ((uint16_t)(x*100))

/*===========================================================================*\
 * Extern function declarition
\*===========================================================================*/
void Update_DiagStatus_10ms(void);

#endif

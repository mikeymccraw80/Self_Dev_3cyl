
/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/


/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
#include "HLS.h"

/* ============================================================================ *\
 * global variabes used by both lld and hls.
\* ============================================================================ */

LLD_atd_input_item LLD_atd_input_table[LLD_ATD_MAX_CHANNEL];
LLD_di_item LLD_di_table[LLD_DI_MAX_CHANNEL];
LLD_do_item LLD_do_table[LLD_DO_MAX_CHANNEL];
LLD_pwm_out_item LLD_pwm_out_table[LLD_PWM_MAX_CHANNEL]; /* The index means the channel no of the PWM output module */

/* The instant fuel consumption from HLS */
uint16_t instant_fuel_consumption; 

 current_channel_num LLD_cyl_num;
 cam_signals cam_sig; 
crank_signals crank_sig;
inj_signals inj_sig[MAX_INJ_CHANNEL];
inj_enable_bits inj_enable;
ign_enable_bits ign_enable;
ign_signals ign_sig[LLD_MAX_IGN_CHANNEL];

veh_spd_signals veh_spd_sig;


bool knock_flag_a;
bool knock_flag_b;
bool knock_flag_c;
bool knock_flag_d;



bool B_syn_update;
bool B_KeyOn;

bool S_AC;


sys_status_bits sys_status;
sys_cmmd_bits sys_cmd;

/* HLS mileage variable */
uint32_t odometer;
/* LLD variable to inform HLS turn on the mil light */
/* Attention: Do not defined as hls_bss variable */
uint32_t Sys_time;
bool CAN_MIL_Status;
/*===========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/*===========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---     ----------------------------------       */
/*===========================================================================*/



/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "reuse.h"


/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
#include "HLS.h"
//#include "hal_di.h"


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */

uint16_t HLS_MAP_Value;
bool   HLS_MAP_Status;
uint16_t HLS_OXYGEN_Value;
bool  HLS_OXYGEN_Status;
uint16_t HLS_BATT_Value;
bool  HLS_BATT_Status;
uint16_t HLS_TA_Value;
bool  HLS_TA_Status;
uint16_t HLS_ECT_Value;
bool HLS_ECT_Status;
uint16_t HLS_TPS_Value;
bool HLS_TPS_Status;
uint8_t HLS_Filtered_AC_REQUEST_INPUT;
uint8_t HLS_Filtered_AC_PRESSURE_SWITCH;
uint8_t HLS_Filtered_DI_CAM_1;
uint8_t HLS_Filtered_DI_IGN_ON_OFF_SW;
uint8_t HLS_Filtered_DI_HEAD_LAMP;
unsigned char  TpPos_b;//tps=100*0.3922=39.22
unsigned char  Pmap_b;
unsigned char  Tm;//Tm= 200*0.75-48 =102
unsigned char  TmLin; 
unsigned char  Ta;
 uint8_t FCMEnd;
 uint8_t MafTst;
 uint16_t fLc;
 uint16_t fLcAd;
 uint8_t Pmap_b;
 unsigned short       Pmap;
 uint16_t N;
 uint8_t Vsp_b;
 int8_t IgaOut;
 uint8_t TaLin;
 uint16_t Tpp;
 uint16_t uLsb;
 uint16_t uLsa;
 uint16_t KmQ1Mil;
 uint8_t Ub_b;
 uint8_t TpPos_b;
 uint16_t uTm;
 uint8_t uTa;
 uint16_t uPmap;
 uint16_t uTps;
 uint16_t Ti;
 uint8_t NDsrIdc;
 uint8_t Ld_b;
 uint16_t fAlt;
 int16_t  dTqIdcP;
 int16_t dTqIdcI;
 int8_t dIgaKnc[4];
 uint16_t FtCntEmisCyl[4];
// uint8_t StepPos;
 uint8_t StepPosDsr;
bool                 B_Fan1;
bool                 B_Fan2;
bool                 B_AcOn;
 uint16_t tLsbAfFlt;
 int8_t IntLcDwnI;
 uint8_t SsCatDwnM;
 uint8_t MxGrdLsaFit_b;
tele_type telem_data;
uint8_t 	count_DTCs_SID03;
bool	B_DiagInfoClrReq;
uint8_t 	count_DTCs_SID07;
uint8_t Gr;
uint8_t Maf_b;
uint16_t             KmQ1;
uint16_t             KmQ65;
signed char              dNDsr;
bool                 B_Fof;


/*VCPC*/
unsigned int angle_crank_cam_inlet;
unsigned int angle_crank_cam_outlet;

//ETC
etc_signals etc_sig;

/* ============================================================================ *\
 * Local FUNCTION.
\* ============================================================================ */

/*AD test code*/
  void TestATD_ATD_Function(void)
{

HLS_MAP_Value = LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_val;
//HLS_MAP_Status = LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_status;
HLS_OXYGEN_Value = LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_1].LLD_atd_val;
//HLS_OXYGEN_Status = LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_1].LLD_atd_status;
HLS_BATT_Value = LLD_atd_input_table[LLD_ATD_VBATT_SW].LLD_atd_val;
//HLS_BATT_Status = LLD_atd_input_table[LLD_ATD_VBATT_SW].LLD_atd_status;
HLS_TA_Value = LLD_atd_input_table[LLD_ATD_TA].LLD_atd_val;
//HLS_TA_Status = LLD_atd_input_table[LLD_ATD_TA].LLD_atd_status;
HLS_ECT_Value = LLD_atd_input_table[LLD_ATD_ECT].LLD_atd_val;
//HLS_ECT_Status = LLD_atd_input_table[LLD_ATD_ECT].LLD_atd_status;
HLS_TPS_Value = LLD_atd_input_table[LLD_ATD_THROTTLE_1].LLD_atd_val;
//HLS_TPS_Status = LLD_atd_input_table[LLD_ATD_THROTTLE_1].LLD_atd_status;

}

/*HWIO DI test code*/
  void Test_DI_Function(void)
{
HLS_Filtered_AC_REQUEST_INPUT = LLD_di_table[LLD_DI_AC_REQUEST_INPUT].value;
HLS_Filtered_AC_PRESSURE_SWITCH= LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].value;
HLS_Filtered_DI_CAM_1=LLD_di_table[LLD_DI_CAM_1].value;
HLS_Filtered_DI_IGN_ON_OFF_SW=LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value;
HLS_Filtered_DI_HEAD_LAMP=LLD_di_table[LLD_DI_HEAD_LAMP].value;

}

/*HWIO DO test code*/
  void Test_DO_Toggle_Function(void)
{
  if( LLD_do_table[LLD_DO_FAN1].value)
  {
      LLD_do_table[LLD_DO_FAN1].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_FAN1].value = true;
   }	

    if( LLD_do_table[LLD_DO_FAN2].value)
  {
      LLD_do_table[LLD_DO_FAN2].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_FAN2].value = true;
   }	 

    if( LLD_do_table[LLD_DO_FUEL_PUMP].value)
  {
      LLD_do_table[LLD_DO_FUEL_PUMP].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_FUEL_PUMP].value = true;
   }	 

    if( LLD_do_table[LLD_DO_MAIN_RELAY].value)
  {
      LLD_do_table[LLD_DO_MAIN_RELAY].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_MAIN_RELAY].value = true;
   }	 

    if( LLD_do_table[LLD_DO_MIL_LAMP].value)
  {
      LLD_do_table[LLD_DO_MIL_LAMP].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_MIL_LAMP].value = true;
   }	 

    if( LLD_do_table[LLD_DO_SVS_LAMP].value)
  {
      LLD_do_table[LLD_DO_SVS_LAMP].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_SVS_LAMP].value = true;
   }	 

    if( LLD_do_table[LLD_DO_AC_CLUTCH].value)
  {
      LLD_do_table[LLD_DO_AC_CLUTCH].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_AC_CLUTCH].value = true;
   }	 

   if( LLD_do_table[LLD_DO_R_LINE].value)
  {
      LLD_do_table[LLD_DO_R_LINE].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_R_LINE].value = true;
   }

    if( LLD_do_table[LLD_DO_VIS_SWITCH].value)
  {
      LLD_do_table[LLD_DO_VIS_SWITCH].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_VIS_SWITCH].value = true;
   }	

   if( LLD_do_table[LLD_DO_ETB_DIR].value)
  {
      LLD_do_table[LLD_DO_ETB_DIR].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_ETB_DIR].value = true;
   }	


   if( LLD_do_table[LLD_DO_START_MOTR_RLY].value)
  {
      LLD_do_table[LLD_DO_START_MOTR_RLY].value = false;
  }	
  else
  {
      LLD_do_table[LLD_DO_START_MOTR_RLY].value = true;
   }

 }


/* ============================================================================ *\
 * Exported FAR_COS FUNCTION.
\* ============================================================================ */
/* Call back function for 1ms task */
 void HLS_Task_1ms(void)
{
  TestATD_ATD_Function();
}

 void HLS_Task_5ms(void)
{
 
}

/* Call back function for 10ms task */
 void HLS_Task_10ms(void)
{
 Test_DI_Function();
}
/* Call back function for 20ms task */
 void HLS_Task_20ms(void)
{
}
/* Call back function for 50ms task */
 void HLS_Task_50ms(void)
{
}
/* Call back function for 100ms task */
 void HLS_Task_100ms(void)
{
}
/* Call back function for 200ms task */
 void HLS_Task_200ms(void)
{
}
/* Call back function for 1000ms task */
  void HLS_Task_1000ms(void)
{
Test_DO_Toggle_Function();
//Test_IAC_Running();
}

 void HLS_afterrun(void)
{
 //sys_cmd.B_after_run_end = true;
}

/*HLS initialization function.*/
  void HLS_ini(void)
{


 
 LLD_di_table[LLD_DI_AC_REQUEST_INPUT].DebounceTimes = LLD_DI_AC_REQUEST_INPUT_DebTime ;
 LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].DebounceTimes=LLD_DI_AC_PRESSURE_SWITCH_DebTime ;
 LLD_di_table[LLD_DI_CAM_1].DebounceTimes = LLD_DI_CAM_1_DebTime;
 LLD_di_table[LLD_DI_IGN_ON_OFF_SW].DebounceTimes = LLD_DI_IGN_ON_OFF_SW_DebTime ;
 LLD_di_table[LLD_DI_HEAD_LAMP].DebounceTimes = LLD_DI_HEAD_LAMP_DebTime ;
 LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].B_enable = true;
  LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].B_enable = true;
 LLD_pwm_out_table[LLD_PWM_PURGE].B_enable = true;
 LLD_pwm_out_table[LLD_PWM_ECT].B_enable = true;
 LLD_pwm_out_table[LLD_PWM_EGR].B_enable = true;
 LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].B_enable = true;
 LLD_pwm_out_table[LLD_PWM_VVT1].B_enable = true;
 LLD_pwm_out_table[LLD_PWM_VVT2].B_enable = true;
  LLD_pwm_out_table[LLD_PWM_ETB].B_enable = true;
 
 LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].duty = 128;
  LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].duty = 128;
 LLD_pwm_out_table[LLD_PWM_PURGE].duty=128;
 LLD_pwm_out_table[LLD_PWM_ECT].duty=128;
  LLD_pwm_out_table[LLD_PWM_EGR].duty=128;
 LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].duty=128;
 LLD_pwm_out_table[LLD_PWM_VVT1].duty=128;
 LLD_pwm_out_table[LLD_PWM_VVT2].duty=128;
LLD_pwm_out_table[LLD_PWM_ETB].duty=128;

 LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].period = 100;
  LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].period = 100;
 LLD_pwm_out_table[LLD_PWM_PURGE].period = 100;
 LLD_pwm_out_table[LLD_PWM_ECT].period = 10;
 LLD_pwm_out_table[LLD_PWM_EGR].period = 100;
 LLD_pwm_out_table[LLD_PWM_VVT1].period = 10;
 LLD_pwm_out_table[LLD_PWM_VVT2].period = 10;
 LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].period = 10;
  LLD_pwm_out_table[LLD_PWM_ETB].period = 1;

 
 inj_enable.B_inj_A = (uint8_t)true;
 inj_enable.B_inj_B = (uint8_t)true;
 inj_enable.B_inj_C = (uint8_t)true;
 inj_enable.B_inj_D = (uint8_t)true;

 inj_sig[INJ_CHANNEL_A].inj_time = 20000;
 inj_sig[INJ_CHANNEL_B].inj_time = 20000;
 inj_sig[INJ_CHANNEL_C].inj_time = 20000;
 inj_sig[INJ_CHANNEL_D].inj_time = 20000;

 inj_sig[INJ_CHANNEL_A].inj_end_angle = 200;
 inj_sig[INJ_CHANNEL_B].inj_end_angle = 200;
 inj_sig[INJ_CHANNEL_C].inj_end_angle = 200;
 inj_sig[INJ_CHANNEL_D].inj_end_angle = 200;


 ign_enable.B_ign_A = (uint8_t)true;     
 ign_enable.B_ign_B = (uint8_t)true;
 ign_enable.B_ign_C = (uint8_t)true;
 ign_enable.B_ign_D = (uint8_t)true;

 ign_sig[LLD_IGN_CHANNEL_A].dwell_time = 8000;
 ign_sig[LLD_IGN_CHANNEL_B].dwell_time = 8000;
 ign_sig[LLD_IGN_CHANNEL_C].dwell_time = 8000;
 ign_sig[LLD_IGN_CHANNEL_D].dwell_time = 8000;

 ign_sig[LLD_IGN_CHANNEL_A].ign_angle = -16;
 ign_sig[LLD_IGN_CHANNEL_B].ign_angle = -16;
 ign_sig[LLD_IGN_CHANNEL_C].ign_angle = -16;
 ign_sig[LLD_IGN_CHANNEL_D].ign_angle = -16;


 /*sys_cmd.B_after_run_end= false;
 sys_cmd.B_SW_Pwf = false;
 sys_cmd.B_rsv = 0x0;
 sys_status.B_after_run_end_abnormal = false;
 sys_status.B_Pwf = false;
 sys_status.B_rsv = 0x0;*/

//TpPos_b=100;//tps=100*0.3922=39.22
Pmap_b=100;//Pmap_b=100kpa
Pmap=25650;//pmap=0.0039*25650=100.35kpa
 Tm=200;//Tm= 200*0.75-48 =102 
 TmLin=200;//TmLin= 200*0.75-48 =102
 Ta=200;

// B_after_run_end_abnormal =0x00;



      LLD_do_table[LLD_DO_FAN1].value = true;

      LLD_do_table[LLD_DO_FAN2].value = false;

      LLD_do_table[LLD_DO_FUEL_PUMP].value = true;

      LLD_do_table[LLD_DO_MAIN_RELAY].value = true;

      LLD_do_table[LLD_DO_MIL_LAMP].value = false;

      LLD_do_table[LLD_DO_SVS_LAMP].value = true;

      LLD_do_table[LLD_DO_AC_CLUTCH].value = false;

      LLD_do_table[LLD_DO_R_LINE].value = true;

      LLD_do_table[LLD_DO_VIS_SWITCH].value = false;

      LLD_do_table[LLD_DO_ETB_DIR].value = false;

	     LLD_do_table[LLD_DO_START_MOTR_RLY].value = true;


}
/*HLS initialization function*/
 void HLS_ini2(void)
{

unsigned char i;
telem_data.tele_N =0x1234;
telem_data.tele_B_FuelStatus = 0xaa;
telem_data.tele_CsMaf = 0xbb;
telem_data.tele_fLc = 0xcc;
telem_data.tele_fLcAd = 0xdd;
telem_data.tele_IgaOut = 0xee;
telem_data.tele_Pmap = 0xff;
telem_data.tele_TaLin = 0x11;
telem_data.tele_TmLin = 0x22;
telem_data.tele_TpPos = 0x33;
telem_data.tele_uLsb = 0x44;
telem_data.tele_Vsp = 0x55;


//scnVehInfo.CVN[0] = 0xaa;
//scnVehInfo.CVN[1] = 0xbb;
//scnVehInfo.CVN[2] =0xcc;
//scnVehInfo.CVN[3] =0xdd;



LLD_do_table[LLD_DO_ETB_DIS].value = 0;

}

/*will be called after _ini() at ECU power on, and at engine stall*/
 void HLS_inisyn(void)
{

}

/*will be called when the synch is lost/reset, this is an event trigged function call*/
 void HLS_rstsyn(void)
{

}
/*will be called when the first Synchronization (first gap) is confirmed, this is an event trigged function call*/
  void HLS_firstsyn(void)
{

}
/*will be called for every segment (at Software reference mark)*/
 void HLS_syn(void)
{ 
  /* if( knock_flag_a == true)
   {
      ign_sig[LLD_IGN_CHANNEL_A].ign_angle = knock_retard_a;
   }	
   else
   {
      ign_sig[LLD_IGN_CHANNEL_A].ign_angle = 0;
   }

     if( knock_flag_b == true)
   {
      ign_sig[LLD_IGN_CHANNEL_B].ign_angle = knock_retard_b;
   }	
   else
   {
      ign_sig[LLD_IGN_CHANNEL_B].ign_angle = 0;
   }

      if( knock_flag_c == true)
   {
      ign_sig[LLD_IGN_CHANNEL_C].ign_angle = knock_retard_c;
   }	
   else
   {
      ign_sig[LLD_IGN_CHANNEL_C].ign_angle = 0;
   }

    if( knock_flag_d == true)
   {
      ign_sig[LLD_IGN_CHANNEL_D].ign_angle = knock_retard_d; 
   }	
   else
   {
      ign_sig[LLD_IGN_CHANNEL_D].ign_angle = 0;
   }*/
   
   inj_sig[INJ_CHANNEL_A].inj_time = 10000;
   inj_sig[INJ_CHANNEL_B].inj_time = 10000;
   inj_sig[INJ_CHANNEL_C].inj_time = 10000;
   inj_sig[INJ_CHANNEL_D].inj_time = 10000;
  
   inj_sig[INJ_CHANNEL_A].B_post_inj = true;
   inj_sig[INJ_CHANNEL_A].post_inj_time =1000;
   inj_sig[INJ_CHANNEL_B].B_post_inj = true;
   inj_sig[INJ_CHANNEL_B].post_inj_time =1000;
   inj_sig[INJ_CHANNEL_C].B_post_inj = true;
   inj_sig[INJ_CHANNEL_C].post_inj_time =1000;
   inj_sig[INJ_CHANNEL_D].B_post_inj = true;
   inj_sig[INJ_CHANNEL_D].post_inj_time =1000;

}
/*will be called on each falling edge of the CAM signal*/
 void HLS_ph1(void)
{

}

/*will be called on each falling edge of the CAM signal*/
 void HLS_ph2(void)
{

}
/* will be called at the falling edge of every crank tooth */
 void HLS_tooth_interrupt(void)
{
   
} 

/*===========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/*===========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---     ----------------------------------       */
/*===========================================================================*/


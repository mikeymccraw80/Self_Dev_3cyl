//=============================================================================
// include files
//=============================================================================
#include "hal_pulse.h"
#include "HLS.h"


//=============================================================================
// HAL_Pulse_Init_Task
//=============================================================================
 void  IO_Pulse_Update_Function(void) 
{
  //MIOS channel: ETC
  //500us equal 2KHZ
  //duty resoultion is 1/1000
  HAL_Pulse_ETC_Enable((bool)etc_sig.etc_enable);
  HAL_Pulse_ETC_Set_Period_Duty(500, (uint16_t)etc_sig.etc_duty*500/255);

  //MIOS channel: VVT1
  //period in us
  //duty resoultion is 1/1000
  HAL_Pulse_VVT1CTL_Enable((bool)LLD_pwm_out_table[LLD_PWM_VVT1].B_enable);
  HAL_Pulse_VVT1CTL_Set_Period_Duty((uint32_t)LLD_pwm_out_table[LLD_PWM_VVT1].period*1000,
  	                                                (uint16_t)LLD_pwm_out_table[LLD_PWM_VVT1].duty*1000/255);

  
  //MIOS channel: VVT2
  //period in us
  //duty resoultion is 1/1000
  HAL_Pulse_VVT2CTL_Enable((bool)LLD_pwm_out_table[LLD_PWM_VVT2].B_enable);
  HAL_Pulse_VVT2CTL_Set_Period_Duty((uint32_t)LLD_pwm_out_table[LLD_PWM_VVT2].period*1000,
  	                                                (uint16_t)LLD_pwm_out_table[LLD_PWM_VVT2].duty*1000/255);

  //VSEP channel: period resoultion is 1/64ms; duty resoultion is 1/32768
  //VSEP channel :CCP
  if(LLD_pwm_out_table[LLD_PWM_PURGE].B_enable)
   {
    HAL_Pulse_CCP_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_PURGE].period*64, 
 	                                                      (uint16_t)LLD_pwm_out_table[LLD_PWM_PURGE].duty*128);
   }
  else
  {

    HAL_Pulse_CCP_Set_Period_Duty( (uint32_t)0, 
 	                                                      (uint16_t)LLD_pwm_out_table[LLD_PWM_PURGE].duty*128);
  }

 //VSEP channel: period resoultion is 1/64ms; duty resoultion is 1/32768
 //VSEP channel :O2 HTRA
 if(LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].B_enable)
  {
    HAL_Pulse_O2AHTR_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].period*64, 
 	                                                      (uint16_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].duty*128);
  }
 else
 {

    HAL_Pulse_O2AHTR_Set_Period_Duty( (uint32_t)0, 
 	                                                      (uint16_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].duty*128);
 }
 
 //VSEP channel: period resoultion is 1/64ms; duty resoultion is 1/32768
 //VSEP channel :O2 HTRB
 if(LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].B_enable)
  {
    HAL_Pulse_O2BHTR_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].period*64, 
 	                                                      (uint16_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].duty*128);
  }
 else
 {

    HAL_Pulse_O2BHTR_Set_Period_Duty( (uint32_t)0, 
 	                                                      (uint16_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].duty*128);
 }
 
   //VSEP channel: period resoultion is 1/64ms; duty resoultion is 1/32768
 //VSEP channel :CLT Gauge
  if(LLD_pwm_out_table[LLD_PWM_ECT].B_enable)
  {
    HAL_Pulse_CLTGAUGE_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_ECT].period*64, 
 	                                                      (uint16_t)LLD_pwm_out_table[LLD_PWM_ECT].duty*128);
 //test code
  //  HAL_Pulse_ALTCTL_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_ECT].period*64, 
 	//                                                      (uint16_t)LLD_pwm_out_table[LLD_PWM_ECT].duty*128);
  }
 else
 {

    HAL_Pulse_CLTGAUGE_Set_Period_Duty( (uint32_t)0, 
 	                                                      (uint16_t)LLD_pwm_out_table[LLD_PWM_ECT].duty*128);

   //test code
    //HAL_Pulse_ALTCTL_Set_Period_Duty( (uint32_t)0, 
 	   //                                                   (uint16_t)LLD_pwm_out_table[LLD_PWM_ECT].duty*128);
 }

    
}
//=============================================================================
// IO_Pulse_VSEP_CLK_Enable
//=============================================================================
void  IO_Pulse_VSEP_CLK_Enable(void)
{
 HAL_Pulse_VSEP_CLK_Enable(true);
}

uint32_t  Pulse_VSS_Count_Previous;
uint32_t  Pulse_VSS_Time_Previous;
uint32_t  Pulse_VSS_Count;
uint32_t  Pulse_VSS_Time;

//=============================================================================
// IO_Pulse_VSS_Update_500ms
//=============================================================================
void  IO_Pulse_VSS_Update_500ms(void)
{

  Pulse_VSS_Count_Previous  =  Pulse_VSS_Count;
  Pulse_VSS_Count =  HAL_Pulse_Get_VSS_Count();

    if ( Pulse_VSS_Count == Pulse_VSS_Count_Previous )
    {
     veh_spd_sig.period = 0xFFFF;
    } 
    else
    {  
    //TPU time is 4M and VSS period resoultion is 0.01ms
      veh_spd_sig.period = HAL_Pulse_Get_VSS_Period()/40;
    }	 
	
}

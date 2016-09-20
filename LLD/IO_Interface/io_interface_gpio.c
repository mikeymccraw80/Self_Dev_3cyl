//=============================================================================
// include files
//=============================================================================
#include "hal_gpio.h"
#include "hal_analog.h"
#include "HLS.h"
#include "vehicle_can_cald.h"
#include "immo_cal.h"
#include "immo.h"
#include "hwiocald.h"

//=============================================================================
// LLD_di_samplecnt
//=============================================================================
uint8_t LLD_di_samplecnt[LLD_DI_MAX_CHANNEL];
bool Ign_off;
extern bool    KW31_EndofLine_FuelAdjustMode;
/*
//=============================================================================
//  IO_GPIO_DI_Task
//=============================================================================
void IO_GPIO_DI_Task(void)
{
	// DI
	
	
	uint16_t v_ign;
	
	v_ign = FixConvert(HAL_Analog_Get_IGNVI_Value() << 2, Volts_Plus_Fraction, Volts_B ) ;

	if(v_ign < FixDefConst( 4.5, Volts_B )){

	   LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value = false;
	   
	}
	else if(v_ign > FixDefConst( 7.5, Volts_B )){

	   LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value = true;
	   
	}
	//LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value =FixConvert((HAL_Analog_Get_IGNVI_Value() << 2), Volts_Plus_Fraction, uint16_t );

	LLD_di_table[LLD_DI_AC_REQUEST_INPUT].value = (uint8_t)HAL_GPIO_GET_ACRequest_Status();

	LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].value = (uint8_t)HAL_GPIO_GET_MIDAC_Status();

	LLD_di_table[LLD_DI_HEAD_LAMP].value = (uint8_t)HAL_GPIO_GET_ELOAD2_Status();
*/
	/* brake switch input, notice, this is high active but it is alway connected, so we reverse it */
//	LLD_di_table[LLD_DI_BRAKE_SWITCH].value = (HAL_GPIO_GET_BRKSWDI_Status()?false:true);

	/* this channel is changed to AD channel */
	// LLD_di_table[LLD_DI_BRAKE_LAMP].value = (uint8_t)HAL_GPIO_GET_BRKLMPDI_Status();

	/* crank request input channel */
//	LLD_di_table[LLD_DI_CRANK_REQUEST].value = (uint8_t)HAL_GPIO_GET_ELOAD1_Status();

	/* power steering and clutch share some input channel */
//	LLD_di_table[LLD_DI_CLUTCH_TOP].value = (uint8_t)HAL_GPIO_GET_PSPS_Status();
//	LLD_di_table[LLD_DI_POWER_STEERING].value = (uint8_t)HAL_GPIO_GET_PSPS_Status();
//}


void LLD_DI_1ms_sample(void)
 {
    /* AC request input channel */
    if((bool)HAL_GPIO_GET_ACRequest_Status()){
		
       if(LLD_di_samplecnt[LLD_DI_AC_REQUEST_INPUT] < 
	   	 LLD_di_table[LLD_DI_AC_REQUEST_INPUT].DebounceTimes){
	   	 
          LLD_di_samplecnt[LLD_DI_AC_REQUEST_INPUT]++;
       }
    }
    else{
		
       if(LLD_di_samplecnt[LLD_DI_AC_REQUEST_INPUT] > 0){
	   	
          LLD_di_samplecnt[LLD_DI_AC_REQUEST_INPUT] --;
	   }	   
    }	   

    /* AC Pressure input channel */
    if( (bool)HAL_GPIO_GET_MIDAC_Status()){
		
       if(LLD_di_samplecnt[LLD_DI_AC_PRESSURE_SWITCH] < 
	   	 LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].DebounceTimes){
	   	 
          LLD_di_samplecnt[LLD_DI_AC_PRESSURE_SWITCH] ++;
       }
    }
    else{
		
       if(LLD_di_samplecnt[LLD_DI_AC_PRESSURE_SWITCH] > 0){
	   	
          LLD_di_samplecnt[LLD_DI_AC_PRESSURE_SWITCH] --;
       }		  
    }

    /* Head lamp input channel */
    if( (bool)HAL_GPIO_GET_ELOAD2_Status()){
		
       if(LLD_di_samplecnt[LLD_DI_HEAD_LAMP] < 
	   	 LLD_di_table[LLD_DI_HEAD_LAMP].DebounceTimes){
	   	 
          LLD_di_samplecnt[LLD_DI_HEAD_LAMP] ++;
       }	  
    }
    else{
		
       if(LLD_di_samplecnt[LLD_DI_HEAD_LAMP] > 0){
	   	
          LLD_di_samplecnt[LLD_DI_HEAD_LAMP] --;
	   }   
    }

    /* Break Switch input channel */
	if( (bool)(HAL_GPIO_GET_BRKSWDI_Status()) == false ){
		
       if(LLD_di_samplecnt[LLD_DI_BRAKE_SWITCH] < 
	   	 LLD_di_table[LLD_DI_BRAKE_SWITCH].DebounceTimes){
	   	 
           LLD_di_samplecnt[LLD_DI_BRAKE_SWITCH] ++;
        }	  
    }
    else{
       if(LLD_di_samplecnt[LLD_DI_BRAKE_SWITCH] > 0){
	   	
           LLD_di_samplecnt[LLD_DI_BRAKE_SWITCH] --;
	   }   
    }

	/* crank request input channel */
    if((bool)HAL_GPIO_GET_ELOAD1_Status()){
		
       if(LLD_di_samplecnt[LLD_DI_CRANK_REQUEST] < 
	   	 LLD_di_table[LLD_DI_CRANK_REQUEST].DebounceTimes){
	   	 
           LLD_di_samplecnt[LLD_DI_CRANK_REQUEST] ++;
       }
    }
    else{
        if(LLD_di_samplecnt[LLD_DI_CRANK_REQUEST] > 0){
			
           LLD_di_samplecnt[LLD_DI_CRANK_REQUEST] --;
       }		 
    }
    

	/* Clutch Top input channel */
    if((bool)HAL_GPIO_GET_PSPS_Status()){
		
      if(LLD_di_samplecnt[LLD_DI_CLUTCH_TOP] < 
	   	 LLD_di_table[LLD_DI_CLUTCH_TOP].DebounceTimes){
	   	 
         LLD_di_samplecnt[LLD_DI_CLUTCH_TOP] ++;
       }
    }
    else{
   	
      if(LLD_di_samplecnt[LLD_DI_CLUTCH_TOP] > 0){
	  	
         LLD_di_samplecnt[LLD_DI_CLUTCH_TOP] --;
       }		 
    }
    
    /* Power Steering input channel */
    if((bool)HAL_GPIO_GET_PSPS_Status()){
   	
      if(LLD_di_samplecnt[LLD_DI_POWER_STEERING] < 
	   	 LLD_di_table[LLD_DI_POWER_STEERING].DebounceTimes){
	   	 
           LLD_di_samplecnt[LLD_DI_POWER_STEERING] ++;
        }
    }
    else{
   	
      if(LLD_di_samplecnt[LLD_DI_POWER_STEERING] > 0){
	  	
          LLD_di_samplecnt[LLD_DI_POWER_STEERING] --;
	  }	  
    }

    /* Ignition On input channel */
	if((HAL_Analog_Get_IGNVI_Value() << 2) > K_VOLT_KeyOnThreshold){
		
	   if(LLD_di_samplecnt[LLD_DI_IGN_ON_OFF_SW] < LLD_di_table[LLD_DI_IGN_ON_OFF_SW].DebounceTimes){
	   	
           LLD_di_samplecnt[LLD_DI_IGN_ON_OFF_SW] ++;
        }
	}
	else if((HAL_Analog_Get_IGNVI_Value() << 2) < K_VOLT_KeyoffThreshold){
		
       if(LLD_di_samplecnt[LLD_DI_IGN_ON_OFF_SW] > 0)
	    {  	
          LLD_di_samplecnt[LLD_DI_IGN_ON_OFF_SW] --;
	    }	 
	
	}
 }


void LLD_DI_INTR(void)
{
  /* AC Request input channel */
  if (LLD_di_table[LLD_DI_AC_REQUEST_INPUT].DebounceTimes != 0){

	if( LLD_di_samplecnt[LLD_DI_AC_REQUEST_INPUT] >= 
	   	 LLD_di_table[LLD_DI_AC_REQUEST_INPUT].DebounceTimes){
	   	 
      LLD_di_table[LLD_DI_AC_REQUEST_INPUT].value = true;
    }
    else if (LLD_di_samplecnt[LLD_DI_AC_REQUEST_INPUT] == 0){
		
      LLD_di_table[LLD_DI_AC_REQUEST_INPUT].value = false;
    }
  }  
  else{
  	
     LLD_di_table[LLD_DI_AC_REQUEST_INPUT].value = (bool)HAL_GPIO_GET_ACRequest_Status();
    
  }

  /* AC Pressure Switch input channel */
  if (LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].DebounceTimes != 0){
  	
    if( LLD_di_samplecnt[LLD_DI_AC_PRESSURE_SWITCH] >= 
	   	 LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].DebounceTimes){
	   	 
      LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].value = true;
    }
    else if (LLD_di_samplecnt[LLD_DI_AC_PRESSURE_SWITCH] == 0){
		
      LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].value = false;
    }
  }  
  else{
  	
      LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].value = (bool)HAL_GPIO_GET_MIDAC_Status();
    
  }

  /* HEAD LAMP input channel */
  if (LLD_di_table[LLD_DI_HEAD_LAMP].DebounceTimes != 0){
  	
    if( LLD_di_samplecnt[LLD_DI_HEAD_LAMP] >= 
	   	 LLD_di_table[LLD_DI_HEAD_LAMP].DebounceTimes){
	   	 
      LLD_di_table[LLD_DI_HEAD_LAMP].value = true;
    }
    else if (LLD_di_samplecnt[LLD_DI_HEAD_LAMP] == 0){
		
      LLD_di_table[LLD_DI_HEAD_LAMP].value = false;
    }
  }  
  else{
  	
      LLD_di_table[LLD_DI_HEAD_LAMP].value = (bool)HAL_GPIO_GET_ELOAD2_Status();
    
  }

  /* Break Switch input channel */
  if (LLD_di_table[LLD_DI_BRAKE_SWITCH].DebounceTimes != 0){
  	
    if( LLD_di_samplecnt[LLD_DI_BRAKE_SWITCH] >= 
	   	 LLD_di_table[LLD_DI_BRAKE_SWITCH].DebounceTimes){
	   	 
      LLD_di_table[LLD_DI_BRAKE_SWITCH].value = true;
    }
    else if (LLD_di_samplecnt[LLD_DI_BRAKE_SWITCH] == 0){
		
      LLD_di_table[LLD_DI_BRAKE_SWITCH].value = false;
    }
  }  
  else{
  	
      LLD_di_table[LLD_DI_BRAKE_SWITCH].value = (bool)HAL_GPIO_GET_BRKSWDI_Status();
    
  }

  /* Crank Request input channel */
   if (LLD_di_table[LLD_DI_CRANK_REQUEST].DebounceTimes != 0){
		
    if( LLD_di_samplecnt[LLD_DI_CRANK_REQUEST] >= 
	   	 LLD_di_table[LLD_DI_CRANK_REQUEST].DebounceTimes){
	   	 
      LLD_di_table[LLD_DI_CRANK_REQUEST].value = true;
    }
    else if (LLD_di_samplecnt[LLD_DI_CRANK_REQUEST] == 0){
		
      LLD_di_table[LLD_DI_CRANK_REQUEST].value = false;
    }
   }  
   else{
  	
      LLD_di_table[LLD_DI_CRANK_REQUEST].value = (bool)HAL_GPIO_GET_ELOAD1_Status();
    
   }

  /* Clutch Top input channel */
   if (LLD_di_table[LLD_DI_CLUTCH_TOP].DebounceTimes != 0){
   	
    if( LLD_di_samplecnt[LLD_DI_CLUTCH_TOP] >= 
	   	 LLD_di_table[LLD_DI_CLUTCH_TOP].DebounceTimes)
    {
      LLD_di_table[LLD_DI_CLUTCH_TOP].value = true;
    }
    else if (LLD_di_samplecnt[LLD_DI_CLUTCH_TOP] == 0)
    {	
      LLD_di_table[LLD_DI_CLUTCH_TOP].value = false;
    }
   }  
   else{
   	
      LLD_di_table[LLD_DI_CLUTCH_TOP].value = (bool)HAL_GPIO_GET_PSPS_Status();
    
   }

  /* Power Steering input channel */
   if (LLD_di_table[LLD_DI_POWER_STEERING].DebounceTimes != 0){
   	
    if( LLD_di_samplecnt[LLD_DI_POWER_STEERING] >= 
	   	 LLD_di_table[LLD_DI_POWER_STEERING].DebounceTimes){
	   	 
      LLD_di_table[LLD_DI_POWER_STEERING].value = true;
    }
    else if (LLD_di_samplecnt[LLD_DI_POWER_STEERING] == 0){
		
      LLD_di_table[LLD_DI_POWER_STEERING].value = false;
    }
   }  
   else{
  	
      LLD_di_table[LLD_DI_POWER_STEERING].value = (bool)HAL_GPIO_GET_PSPS_Status();
    
   }

  /* Ignition On input channel */
   if (LLD_di_table[LLD_DI_IGN_ON_OFF_SW].DebounceTimes != 0){
   	
    if( LLD_di_samplecnt[LLD_DI_IGN_ON_OFF_SW] >= 
	   	 LLD_di_table[LLD_DI_IGN_ON_OFF_SW].DebounceTimes){
	   	 
      LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value = true;
	  Ign_off = false;
	  
    }
    else if (LLD_di_samplecnt[LLD_DI_IGN_ON_OFF_SW] == 0){
		
      LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value = false;
//ign_off keeps false, in order to keep the ECM running, so that the ECM wont shut down on IGNOFF
//	  Ign_off = true;
	  
    }
   }  
   else{
   	
    if((HAL_Analog_Get_IGNVI_Value() << 2) > K_VOLT_KeyOnThreshold){

	   LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value = true;
	   Ign_off = false;
	   
    }
	else if((HAL_Analog_Get_IGNVI_Value() << 2) < K_VOLT_KeyoffThreshold){

	   LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value = false;
//ign_off keeps false, in order to keep the ECM running, so that the ECM wont shut down on IGNOFF
//	  Ign_off = true;
	   
	}
  }
   
}
//=============================================================================
//IO_GPIO_DO_Task
//=============================================================================
void IO_GPIO_DO_Task(void) 
{
	HAL_GPIO_SET_MPR_Enable((bool) LLD_do_table[LLD_DO_MAIN_RELAY].value);

	if(K_Immo_FuelPump_channel==CeFuelPumpPin) {
		if (ImmoStopEngine()) {
			if (KW31_EndofLine_FuelAdjustMode == false)
				HAL_GPIO_SET_FPR_Enable((bool) false);
		} else {
			if (KW31_EndofLine_FuelAdjustMode == false)
				HAL_GPIO_SET_FPR_Enable((bool) LLD_do_table[LLD_DO_FUEL_PUMP].value);
		}
		HAL_GPIO_SET_ACClutch_Enable((bool) LLD_do_table[LLD_DO_AC_CLUTCH].value);
	} else {
		if (ImmoStopEngine()) {
			if (KW31_EndofLine_FuelAdjustMode == false)
				HAL_GPIO_SET_ACClutch_Enable(false);
		} else {
			if (KW31_EndofLine_FuelAdjustMode == false)
				HAL_GPIO_SET_ACClutch_Enable((bool) LLD_do_table[LLD_DO_FUEL_PUMP].value);
		}
		HAL_GPIO_SET_FPR_Enable((bool) LLD_do_table[LLD_DO_AC_CLUTCH].value);
	}
	HAL_GPIO_SET_FAN1_Enable((bool) LLD_do_table[LLD_DO_FAN1].value);
	//HAL_GPIO_SET_FAN2_Enable((bool) LLD_do_table[LLD_DO_FAN2].value);
	// HAL_GPIO_SET_IMMOREQ_Enable((bool) LLD_do_table[LLD_DO_R_LINE].value);
	 HAL_GPIO_SET_SMR_Enable((bool) LLD_do_table[LLD_DO_START_MOTR_RLY].value);
	//HAL_GPIO_SET_CRUISI_Enable((bool) LLD_do_table[LLD_DO_START_MOTR_RLY].value);
	HAL_GPIO_SET_VGIS1_Enable((bool) LLD_do_table[LLD_DO_VIS_SWITCH].value);
	
	/* for meter signal output */
	if (!K_Can_Meter_MIL_Disable) {
		HAL_GPIO_SET_MIL_Enable((bool) LLD_do_table[LLD_DO_MIL_LAMP].value);
	}
	if (!K_Can_Meter_SVS_Disable) {
		HAL_GPIO_SET_SVS_Enable((bool) LLD_do_table[LLD_DO_SVS_LAMP].value);
	}
}


//=============================================================================
//IO_GPIO_DO_Task
//=============================================================================
void IO_GPIO_DO_Task_1ms(void) 
{

}

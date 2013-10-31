//=============================================================================
// include files
//=============================================================================
#include "hal_analog.h"
#include "HLS.h"


//=============================================================================
//  analogy default value
//=============================================================================


#define K_Map_Default      (unsigned int)(831)//4.06v
#define K_O2sensor_Default (unsigned int)(92)//450mv
#define K_TA_Default       (unsigned int)(733)//3.58v
#define K_ECT_Default      (unsigned int)(733)//3.58v
#define K_TPS1_Default      (unsigned int)(164)
#define K_TPS2_Default      (unsigned int)(831)

//=============================================================================
//  IO_Analog_1ms_Update
//=============================================================================
  void IO_Analog_1ms_Update(void)
{
 // Map 
  if ( LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_status.B_failed )
  {
   LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_val = K_Map_Default;
   //Diag_Map_Status = Diag_Map_Status | OUT_SUBSTITUTE;
  } 
  else
  {
   LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_val =HAL_Analog_Get_MAPVI_Value()>>2;

  }//chery requirement

   //TPS1 
   // if ( LLD_atd_input_table[LLD_ATD_THROTTLE_1].LLD_atd_status.B_failed )
  //{
  // LLD_atd_input_table[LLD_ATD_THROTTLE_1].LLD_atd_val = K_TPS1_Default;
  // Diag_Map_Status = Diag_Map_Status | OUT_SUBSTITUTE;
 // } 
 // else
  {
   LLD_atd_input_table[LLD_ATD_THROTTLE_1].LLD_atd_val =HAL_Analog_Get_TPS1VI_Value()>>2;

  }//chery requirement

    // TPS2 
  //if ( LLD_atd_input_table[LLD_ATD_THROTTLE_2].LLD_atd_status.B_failed )
  //{
 //  LLD_atd_input_table[LLD_ATD_THROTTLE_2].LLD_atd_val = K_TPS2_Default;
 //  Diag_Map_Status = Diag_Map_Status | OUT_SUBSTITUTE;
 // } 
 // else
  {
   LLD_atd_input_table[LLD_ATD_THROTTLE_2].LLD_atd_val =HAL_Analog_Get_TPS2VI_Value()>>2;;
  }//chery requirement
}

//=============================================================================
//IO_Analog_10ms_Update
//=============================================================================
  void IO_Analog_10ms_Update(void)
{ 
  // O2 sensor A 
  if ( LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_1].LLD_atd_status.B_failed )
  {
   LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_1].LLD_atd_val = K_O2sensor_Default;
   //Diag_O2ASesor_Status = Diag_O2ASesor_Status | OUT_SUBSTITUTE;
  } 
  else
  {
   LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_1].LLD_atd_val = HAL_Analog_Get_O2AVI_Value()>>2;
  }//chery requirement
  
  // O2 sensor B 
  if ( LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_2].LLD_atd_status.B_failed )
  {
   LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_2].LLD_atd_val = K_O2sensor_Default;
   //Diag_O2BSesor_Status = Diag_O2BSesor_Status | OUT_SUBSTITUTE;
  } 
  else
  {
   LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_2].LLD_atd_val =HAL_Analog_Get_O2BVI_Value()>>2;
  }//chery requirement
  
 // TA 
  if ( LLD_atd_input_table[LLD_ATD_TA].LLD_atd_status.B_failed )
  {
   LLD_atd_input_table[LLD_ATD_TA].LLD_atd_val = K_TA_Default;
  // Diag_TA_Status = Diag_TA_Status | OUT_SUBSTITUTE;
  } 
  else
  {
   LLD_atd_input_table[LLD_ATD_TA].LLD_atd_val = HAL_Analog_Get_MATVI_Value()>>2;
  }//chery requirement
  
  // Tm 
  if ( LLD_atd_input_table[LLD_ATD_ECT].LLD_atd_status.B_failed )
  {
   LLD_atd_input_table[LLD_ATD_ECT].LLD_atd_val = K_ECT_Default;
   //Diag_ECT_Status = Diag_ECT_Status | OUT_SUBSTITUTE;
  } 
  else
  {
   LLD_atd_input_table[LLD_ATD_ECT].LLD_atd_val = HAL_Analog_Get_CLTVI_Value()>>2;
  }//chery requirement
    
  //Ingition voltage 
  LLD_atd_input_table[LLD_ATD_VBATT_SW].LLD_atd_val = HAL_Analog_Get_IGNVI_Value()>>2;
  
  //Front Evap Temperature 
  LLD_atd_input_table[LLD_ATD_FRONT_EVAP_TEMP].LLD_atd_val = HAL_Analog_Get_FREPVI_Value()>>2;

 //AC PRESSURE 
  LLD_atd_input_table[LLD_ATD_AC_PRESSURE].LLD_atd_val = HAL_Analog_Get_ACPREVI_Value()>>2;

   //PPS1
  LLD_atd_input_table[LLD_ATD_PEDAL_1].LLD_atd_val = HAL_Analog_Get_PPS1VI_Value()>>2;

 //PPS2 
  LLD_atd_input_table[LLD_ATD_PEDAL_2].LLD_atd_val = HAL_Analog_Get_PPS2VI_Value()>>2;

   //Protect Battery 
  LLD_atd_input_table[LLD_ATD_BATTERY_1].LLD_atd_val = HAL_Analog_Get_PBATTVI_Value()>>2;
  

  
}

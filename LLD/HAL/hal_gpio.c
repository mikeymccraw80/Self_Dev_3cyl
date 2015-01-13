
//=============================================================================
// include files
//=============================================================================
#include "dd_siu_interface.h"
#include "io_config_siu.h"
#include "dd_vsep_discrete_interface.h"
#include "io_config_vsep.h"
#include "hwiocald.h"
#include "io_config_tpu.h"

void HAL_GPIO_SET_INJECTION_Enable(bool in_enable)
{
	SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_INJECTION1_CHANNEL,in_enable);
	SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_INJECTION2_CHANNEL,in_enable);
	SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_INJECTION3_CHANNEL,in_enable);
	SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_INJECTION4_CHANNEL,in_enable);
}

void HAL_GPIO_SET_INJECTION_GPIO_Mode_Enable(bool in_enable)
{
	if (in_enable) {
		SIU_Pad_Config(HAL_GPIO_INJECTION1_CHANNEL, SIU_GPIO_PIN_ASSIGNMENT_GPIO);
		SIU_Pad_Config(HAL_GPIO_INJECTION2_CHANNEL, SIU_GPIO_PIN_ASSIGNMENT_GPIO);
		SIU_Pad_Config(HAL_GPIO_INJECTION3_CHANNEL, SIU_GPIO_PIN_ASSIGNMENT_GPIO);
		SIU_Pad_Config(HAL_GPIO_INJECTION4_CHANNEL, SIU_GPIO_PIN_ASSIGNMENT_GPIO);
	} else {
		SIU_Pad_Config(HAL_GPIO_INJECTION1_CHANNEL, SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0);
		SIU_Pad_Config(HAL_GPIO_INJECTION2_CHANNEL, SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0);
		SIU_Pad_Config(HAL_GPIO_INJECTION3_CHANNEL, SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0);
		SIU_Pad_Config(HAL_GPIO_INJECTION4_CHANNEL, SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0);
	}
}


//=============================================================================
// HAL_GPIO_SET_FSE_Enable
//=============================================================================
 void HAL_GPIO_SET_FSE_Enable(bool in_enable) 
 {
   SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_FSE_ENABLE_CHANNEL,in_enable);
 }

//=============================================================================
//HAL_GPIO_GET_FSE_Status
//=============================================================================

  bool HAL_GPIO_GET_FSE_Status(void) 
 {
  return  SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_FSE_ENABLE_CHANNEL);
 }

//=============================================================================
//HAL_GPIO_SET_GEN_Enable
//=============================================================================
  void HAL_GPIO_SET_GEN_Enable(bool in_enable)  
 {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_GEN_ENABLE_CHANNEL,in_enable);
 }

//=============================================================================
// HAL_GPIO_GET_GEN_Status
//=============================================================================
    bool HAL_GPIO_GET_GEN_Status(void) 
 {
   return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_GEN_ENABLE_CHANNEL);
 }

//=============================================================================
// HAL_GPIO_SET_ESTSYNC_Enable
//=============================================================================
  void HAL_GPIO_SET_ESTSYNC_Enable(bool in_enable) 
 {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_ESTSYNC_CHANNEL,in_enable);
  }

//=============================================================================
//HAL_GPIO_SET_ESTSYNC_Enable
//=============================================================================
   bool HAL_GPIO_GET_ESTSYNC_Status(void) 
 {
  return  SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_ESTSYNC_CHANNEL);
 }

//=============================================================================
//HAL_GPIO_SET_ETCDIS_Enable 
//=============================================================================
  void HAL_GPIO_SET_ETCDIS_Enable(bool in_enable) 
 {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_ETCDIS_CHANNEL,in_enable);
 }

//=============================================================================
//HAL_GPIO_GET_ECTDIS_SHAL_GPIO_GET_ETCDIS_Statustatus
//=============================================================================
   bool HAL_GPIO_GET_ETCDIS_Status(void) 
 {
   return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_ETCDIS_CHANNEL);
 }

//=============================================================================
// HAL_GPIO_SET_ETCDIR_Enable
//=============================================================================
    void HAL_GPIO_SET_ETCDIR_Enable(bool in_enable) 
 {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_ETCDIR_CHANNEL,in_enable);
 }

//=============================================================================
// HAL_GPIO_GET_ETCDIR_Status
//=============================================================================
   bool HAL_GPIO_GET_ETCDIR_Status(void) 
 {
   return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_ETCDIR_CHANNEL);
 }

//=============================================================================
// HAL_GPIO_SET_VGIS1_Enable
//=============================================================================
    void HAL_GPIO_SET_VGIS1_Enable(bool in_enable) 
 {
      SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_VGIS1CTL_CHANNEL,in_enable);
 }

//=============================================================================
// HAL_GPIO_GET_VGIS1_Status
//=============================================================================	
   bool HAL_GPIO_GET_VGIS1_Status(void) 
 {
  return  SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_VGIS1CTL_CHANNEL);
 }
   
//=============================================================================
// HAL_GPIO_SET_VGIS2_Enable
//=============================================================================
    void HAL_GPIO_SET_VGIS2_Enable(bool in_enable) 
 {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_VGIS2CTL_CHANNEL,in_enable);
 }

//=============================================================================
//HAL_GPIO_GET_VGIS2_Status
//=============================================================================	
   bool HAL_GPIO_GET_VGIS2_Status(void) 
 {
   return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_VGIS2CTL_CHANNEL);
 }
   
//=============================================================================
//HAL_GPIO_SET_MPR_Enable
//=============================================================================
    void HAL_GPIO_SET_MPR_Enable(bool in_enable) 
 {
     VSEP_DiscreteSet(VSEP_DO_MPR_CH,in_enable);
 }

//=============================================================================
// HAL_GPIO_GET_MPR_Status
//=============================================================================		
   bool HAL_GPIO_GET_MPR_Status(void) 
 {
  return  VSEP_DiscreteGet(VSEP_DO_MPR_CH);
 }
   
//=============================================================================
//HAL_GPIO_SET_FPR_Enable
//=============================================================================
    void HAL_GPIO_SET_FPR_Enable(bool in_enable) 
 {
     VSEP_DiscreteSet(VSEP_DO_FPR_CH,in_enable);
 }

//=============================================================================
// HAL_GPIO_GET_FPR_Status
//=============================================================================			
   bool HAL_GPIO_GET_FPR_Status(void) 
 {
  return  VSEP_DiscreteGet(VSEP_DO_FPR_CH);
 }
   
//=============================================================================
// HAL_GPIO_SET_ACClutch_Enable
//=============================================================================
    void HAL_GPIO_SET_ACClutch_Enable(bool in_enable) 
 {
     VSEP_DiscreteSet(VSEP_DO_ACCLUTCH_CH,in_enable);
 }

//=============================================================================
// HAL_GPIO_GET_ACClutch_Status
//=============================================================================			
   bool HAL_GPIO_GET_ACClutch_Status(void) 
 {
  return  VSEP_DiscreteGet(VSEP_DO_ACCLUTCH_CH);
 }
   
//=============================================================================
//HAL_GPIO_SET_FAN2_Enable
//=============================================================================
 void HAL_GPIO_SET_FAN2_Enable(bool in_enable) 
 {
     VSEP_DiscreteSet(VSEP_DO_FAN2_CH,in_enable);
 }

//=============================================================================
//HAL_GPIO_GET_FAN2_Status
//=============================================================================			
   bool HAL_GPIO_GET_FAN2_Status(void) 
 {
   return VSEP_DiscreteGet(VSEP_DO_FAN2_CH);
 }
   
//=============================================================================
// HAL_GPIO_SET_IMMOREQ_Enable
//=============================================================================
  void HAL_GPIO_SET_IMMOREQ_Enable(bool in_enable) 
 {
     VSEP_DiscreteSetImmediate(VSEP_DO_IMMOREQ_CH  ,in_enable);
 }

//=============================================================================
//HAL_GPIO_GET_IMMOREQ_Status
//=============================================================================			
   bool HAL_GPIO_GET_IMMOREQ_Status(void) 
 {
 return   VSEP_DiscreteGet(VSEP_DO_IMMOREQ_CH);
 }   

//=============================================================================
// HAL_GPIO_SET_MIL_Enable
//=============================================================================
   void HAL_GPIO_SET_MIL_Enable(bool in_enable) 
 {
     VSEP_DiscreteSet(VSEP_DO_MIL_CH,in_enable);
 }

//=============================================================================
// HAL_GPIO_GET_MIL_Status
//=============================================================================			
   bool HAL_GPIO_GET_MIL_Status(void) 
 {
  return VSEP_DiscreteGet(VSEP_DO_MIL_CH);
 }   

//=============================================================================
//HAL_GPIO_SET_SVS_Enable
//=============================================================================
    void HAL_GPIO_SET_SVS_Enable(bool in_enable) 
 {
     VSEP_DiscreteSet(VSEP_DO_SVS_CH,in_enable);
 }

//=============================================================================
// HAL_GPIO_GET_SVS_Status
//=============================================================================			
   bool HAL_GPIO_GET_SVS_Status(void) 
 {
  return VSEP_DiscreteGet(VSEP_DO_SVS_CH);
 }   

//=============================================================================
//HAL_GPIO_SET_FAN1_Enable
//=============================================================================
 void HAL_GPIO_SET_FAN1_Enable(bool in_enable) 
 {
     VSEP_PWM_DISCRETE_Set_State(VSEP_PO_FAN1_CH,in_enable);
 }

 //=============================================================================
//HAL_GPIO_GET_FAN1_Status
//=============================================================================			
   bool HAL_GPIO_GET_FAN1_Status(void) 
 {
  return VSEP_PWM_DISCRETE_Get_State(VSEP_PO_FAN1_CH);
 }   
//=============================================================================
// HAL_GPIO_SET_SMR_Enable
//=============================================================================
 void HAL_GPIO_SET_SMR_Enable(bool in_enable) 
 {
     VSEP_PWM_DISCRETE_Set_State(VSEP_PO_SMR_CH,in_enable);
 }

//=============================================================================
//HAL_GPIO_GET_SMR_Status 
//=============================================================================		
   bool HAL_GPIO_GET_SMR_Status(void) 
 {
   return VSEP_PWM_DISCRETE_Get_State(VSEP_PO_SMR_CH);
 }

//=============================================================================
// HAL_GPIO_SET_SMR_Enable
//=============================================================================
void HAL_GPIO_SET_CRUISI_Enable(bool in_enable) 
{
   VSEP_DiscreteSet(VSEP_PO_CRUISI_CH,in_enable);
}

//=============================================================================
//HAL_GPIO_GET_SMR_Status 
//=============================================================================   
bool HAL_GPIO_GET_CRUISI_Status(void) 
{
   return VSEP_DiscreteGet(VSEP_PO_CRUISI_CH);
}

//=============================================================================
//HAL_GPIO_GET_ACRequest_Status 
//=============================================================================		
   bool HAL_GPIO_GET_ACRequest_Status(void) 
 {

     return VSEP_DiscreteGet(VSEP_MPIO_ACRequest_CH);

 }

//=============================================================================
//HAL_GPIO_GET_PSPS_Status 
//=============================================================================		
   bool HAL_GPIO_GET_PSPS_Status(void) 
 {

     return VSEP_DiscreteGet(VSEP_MPIO_PSPS_CH);

 }

//=============================================================================
//HAL_GPIO_GET_MIDAC_Status 
//=============================================================================		
   bool HAL_GPIO_GET_MIDAC_Status(void) 
 {

     return VSEP_DiscreteGet(VSEP_MPIO_MIDAC_CH);

 }

//=============================================================================
//HAL_GPIO_GET_ELOAD1_Status 
//=============================================================================		
   bool HAL_GPIO_GET_ELOAD1_Status(void) 
 {

     return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_ELOAD1DI_CHANNEL);

 }

//=============================================================================
//HAL_GPIO_GET_ELOAD2_Status 
//=============================================================================		
   bool HAL_GPIO_GET_ELOAD2_Status(void) 
 {
 
     return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_ELOAD2DI_CHANNEL);
   
 }
//=============================================================================
//HAL_GPIO_GET_BRKLMPDI_Status 
//=============================================================================		
   bool HAL_GPIO_GET_BRKLMPDI_Status(void) 
 {
      if(CPU_Info == CPU_LCI)
   {
     return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_BRKLMPDI_CHANNEL_LCI);
   }
   else
   {
     return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_BRKLMPDI_CHANNEL);
   }	 
 }   

//=============================================================================
//HAL_GPIO_GET_BRKSWDI_Status 
//=============================================================================		
   bool HAL_GPIO_GET_BRKSWDI_Status(void) 
 {
  return  SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_BRKSWDI_CHANNEL);
 } 

//=============================================================================
//HAL_GPIO_SET_TODO_Enable
//=============================================================================
 void HAL_GPIO_SET_TODO_Enable(bool in_enable) 
 {
   SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_TODO_CHANNEL,in_enable);
 }

 //=============================================================================
//HAL_GPIO_SET_ELOAD1DICTL_Enable
//=============================================================================
 void HAL_GPIO_SET_ELOAD1DICTL_Enable(bool in_enable) 
 {
    if(CPU_Info == CPU_LCI)
   {
    SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_ELOAD1DICTL_CHANNEL_LCI,in_enable);
   }
   else
   {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_ELOAD1DICTL_CHANNEL,in_enable);
   }	 
 }


 //=============================================================================
//HAL_GPIO_SET_ELOAD2DICTL_Enable
//=============================================================================
 void HAL_GPIO_SET_ELOAD2DICTL_Enable(bool in_enable) 
 {
    if(CPU_Info == CPU_LCI)
   {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_ELOAD2DICTL_CHANNEL_LCI,in_enable);
   }
   else
   {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_ELOAD2DICTL_CHANNEL,in_enable);
   }	 
 }

 //=============================================================================
//HAL_GPIO_SET_BRKLMPDICTL_Enable
//=============================================================================
 void HAL_GPIO_SET_BRKLMPDICTL_Enable(bool in_enable) 
 {
    if(CPU_Info == CPU_LCI)
   {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_BRKLMPDICTL_CHANNEL_LCI,in_enable);
   }
   else
   {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_BRKLMPDICTL_CHANNEL,in_enable);
   }	 
 }


  //=============================================================================
//HAL_GPIO_SET_Reset_DIO_Enable
//=============================================================================
 void HAL_GPIO_SET_Reset_DIO_Enable(bool in_enable) 
 {
    if(CPU_Info == CPU_LCI)
   {
    SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_Reset_DIO_CHANNEL_LCI,in_enable);
   }
   else
   {
     SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_Reset_DIO_CHANNEL,in_enable);
   }	 
 }

//=============================================================================
//HAL_GPIO_GET_Reset_DIO_Status 
//=============================================================================		
   bool HAL_GPIO_GET_Reset_DIO_Status(void) 
 {
      if(CPU_Info == CPU_LCI)
   {
     return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_Reset_DIO_CHANNEL_LCI);
   }
   else
   {
     return SIU_GPIO_DISCRETE_Get_State(HAL_GPIO_Reset_DIO_CHANNEL);
   }	 
 }   

//=============================================================================
//HAL_GPIO_Reset_DIO_Output_Confige 
//=============================================================================		
   void HAL_GPIO_Reset_DIO_Output_Confige(bool enable) 
 {
      if(CPU_Info == CPU_LCI)
   {
     SIU_GPIO_Output_Confige(HAL_GPIO_Reset_DIO_CHANNEL_LCI, enable);
   }
   else
   {
      SIU_GPIO_Output_Confige(HAL_GPIO_Reset_DIO_CHANNEL, enable);
   }	 
 } 

//=============================================================================
//HAL_GPIO_DI_Active_Status_Init 
//=============================================================================		
   void HAL_GPIO_DI_Active_Status_Init(void) 
 {

   HAL_GPIO_SET_ELOAD1DICTL_Enable(!KbHWIO_ELOAD1_Active_High);
   HAL_GPIO_SET_ELOAD2DICTL_Enable(!KbHWIO_ELOAD2_Active_High);
   HAL_GPIO_SET_BRKLMPDICTL_Enable(!KbHWIO_BRKLMP_Active_High);

}


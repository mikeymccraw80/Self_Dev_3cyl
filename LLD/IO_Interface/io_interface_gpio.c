//=============================================================================
// include files
//=============================================================================
#include "hal_gpio.h"
#include "HLS.h"


//=============================================================================
// LLD_di_samplecnt
//=============================================================================
uint8_t   LLD_di_samplecnt[LLD_DI_MAX_CHANNEL];


//=============================================================================
//  IO_GPIO_DI_Task
//=============================================================================
  void IO_GPIO_DI_Task(void)
{

  // DI
 LLD_di_table[LLD_DI_HEAD_LAMP].value = (uint8_t)HAL_GPIO_GET_ELOAD1_Status();
  
 LLD_di_table[LLD_DI_BRAKE_LAMP].value = (uint8_t)HAL_GPIO_GET_BRKLMPDI_Status();

 LLD_di_table[LLD_DI_BRAKE_SWITCH].value = (uint8_t)HAL_GPIO_GET_BRKSWDI_Status();

 LLD_di_table[LLD_DI_CLUTCH_TOP].value = (uint8_t)HAL_GPIO_GET_ELOAD2_Status();


}

//=============================================================================
//IO_GPIO_DO_Task
//=============================================================================
 void IO_GPIO_DO_Task(void) 
{
 //DO
 HAL_GPIO_SET_FAN1_Enable((bool) LLD_do_table[LLD_DO_FAN1].value);
 HAL_GPIO_SET_FAN2_Enable((bool) LLD_do_table[LLD_DO_FAN2].value);
 HAL_GPIO_SET_FPR_Enable((bool) LLD_do_table[LLD_DO_FUEL_PUMP].value);
 HAL_GPIO_SET_MPR_Enable((bool) LLD_do_table[LLD_DO_MAIN_RELAY].value);
 //HAL_GPIO_SET_MIL_Enable((bool) LLD_do_table[LLD_DO_MIL_LAMP].value);
 HAL_GPIO_SET_SVS_Enable((bool) LLD_do_table[LLD_DO_SVS_LAMP].value);
 HAL_GPIO_SET_ACClutch_Enable((bool) LLD_do_table[LLD_DO_AC_CLUTCH].value);
 HAL_GPIO_SET_IMMOREQ_Enable((bool) LLD_do_table[LLD_DO_R_LINE].value);
 HAL_GPIO_SET_SMR_Enable((bool) LLD_do_table[LLD_DO_START_MOTR_RLY].value);
 HAL_GPIO_SET_VGIS1_Enable((bool) LLD_do_table[LLD_DO_VIS_SWITCH].value);
 HAL_GPIO_SET_ETCDIS_Enable((bool) LLD_do_table[LLD_DO_ETB_DIS].value);
 HAL_GPIO_SET_ETCDIR_Enable((bool) LLD_do_table[LLD_DO_ETB_DIR].value); 

//test
 HAL_GPIO_SET_VGIS2_Enable((bool) LLD_do_table[LLD_DO_VIS_SWITCH].value);

}



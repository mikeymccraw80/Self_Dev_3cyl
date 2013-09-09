
//=============================================================================
// include files
//=============================================================================
#include "io_config_stm.h"
#include "dd_stm_interface.h"
#include "dd_stm.h"
#include "dd_siu.h"
#include "dd_dma.h"

//=============================================================================
// STM_CR_INITIAL
//=============================================================================

const STM_CR_T STM_CR_INITIAL = 
{
   STM_CLOCK_PRESCALER, // Counter Prescaler.
   STM_FREEZE_DISABLE,  //freeze
   false                            //Timer Counter Enabled.
};

void IO_STM0_20ms_INT(void)
{
uint8_t idx;
uint32_t s_time_stamp,e_time_stamp;
uint32_t soh_ref_freq;
	
uint8_t current_dma_idx;
uint8_t start_dma_idx;

	STM_INTERRUPT_Clear_Pending(STM_CHANNEL_0);

	//DMA_Clear_Request(DMA_CHANNEL_MIOS_EMIOSFLAG_4);		
	//time_delta = SOH_DMA_External_Ref_Time[3]-SOH_DMA_External_Ref_Time[2];
	//DMA_Enable_Request(DMA_CHANNEL_MIOS_EMIOSFLAG_4);
	HAL_SOH_ETC_ISR();

	//STM_Timer_Set_Value(STM_CHANNEL_0,1000*20);
}

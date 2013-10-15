
#include "dd_mios.h"
#include "io_config_mios.h"

//=============================================================================
// MIOS
//=============================================================================
#define SECTION_MIOS_REGISTER
#include "section.h"
 MIOS_T MIOS;
#define SECTION_END
#include "section.h"
//=============================================================================
// MIOS_Initialize_Device
//=============================================================================
void MIOS_Initialize_Device(void )
{


   MIOS.MCR.U32 = MIOS_MCR_INITIAL.U32;


//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_0 - 
//=======================================================================================
     MIOS.CH[MIOS_CHANNEL_0].CADR    = MIOS_CH0_CBDR_INITIAL/2;
     MIOS.CH[MIOS_CHANNEL_0].CBDR    = MIOS_CH0_CBDR_INITIAL;
     MIOS.CH[MIOS_CHANNEL_0].CCR.U32 = MIOS_CH0_INITIAL.U32;

    // MIOS.CH[MIOS_CHANNEL_0].CSR.U32 = MIOS_RESET_CSR.U32;



//=======================================================================================
// MIOS_CHANNEL_INIT_1 
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_2
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_3 - 
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_4 - 
//=======================================================================================
		MIOS.CH[MIOS_CHANNEL_4].CADR		= 0;
		MIOS.CH[MIOS_CHANNEL_4].CBDR		= 0;
		MIOS.CH[MIOS_CHANNEL_4].CCR.U32 = MIOS_CH4_INITIAL.U32;

//=======================================================================================
// MIOS_CHANNEL_INIT_5 -
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_6 -
//=======================================================================================


//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_8 - 
//=======================================================================================
     MIOS.CH[MIOS_CHANNEL_8].CADR    = 0;
     MIOS.CH[MIOS_CHANNEL_8].CBDR    = MIOS_CH8_CBDR_INITIAL;
     MIOS.CH[MIOS_CHANNEL_8].CCR.U32 = MIOS_CH8_INITIAL.U32;
     //MIOS.CH[MIOS_CHANNEL_8].CSR.U32 = MIOS_RESET_CSR.U32;



//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_9 - 
//=======================================================================================
     MIOS.CH[MIOS_CHANNEL_9].CADR    = 0;
     MIOS.CH[MIOS_CHANNEL_9].CBDR    = MIOS_CH9_CBDR_INITIAL;
     MIOS.CH[MIOS_CHANNEL_9].CCR.U32 = MIOS_CH9_INITIAL.U32;
    // MIOS.CH[MIOS_CHANNEL_9].CSR.U32 = MIOS_RESET_CSR.U32;


//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_10 - 
//=======================================================================================
     MIOS.CH[MIOS_CHANNEL_10].CADR    = 0;
     MIOS.CH[MIOS_CHANNEL_10].CBDR    = MIOS_CH10_CBDR_INITIAL;
     MIOS.CH[MIOS_CHANNEL_10].CCR.U32 = MIOS_CH10_INITIAL.U32;

    // MIOS.CH[MIOS_CHANNEL_10].CSR.U32 = MIOS_RESET_CSR.U32;

//=======================================================================================
// MIOS_CHANNEL_INIT_11 - 
//=======================================================================================



//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_12 - 
//=======================================================================================
     MIOS.CH[MIOS_CHANNEL_12].CADR    = 0;
     MIOS.CH[MIOS_CHANNEL_12].CBDR    = MIOS_CH12_CBDR_INITIAL;
     MIOS.CH[MIOS_CHANNEL_12].CCR.U32 = MIOS_CH12_INITIAL.U32;
    // MIOS.CH[MIOS_CHANNEL_12].CSR.U32 = MIOS_RESET_CSR.U32;

//=======================================================================================
// MIOS_CHANNEL_INIT_13 - 
//=======================================================================================

//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_14 - 
//=======================================================================================
     MIOS.CH[MIOS_CHANNEL_14].CADR    = 0;
     MIOS.CH[MIOS_CHANNEL_14].CBDR    = MIOS_CH14_CBDR_INITIAL;
     MIOS.CH[MIOS_CHANNEL_14].CCR.U32 = MIOS_CH14_INITIAL.U32;
     //MIOS.CH[MIOS_CHANNEL_14].CSR.U32 = MIOS_RESET_CSR.U32;
   

//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_15 - 
//=======================================================================================
   //  MIOS.CH[MIOS_CHANNEL_15].CADR    = 0;
   //  MIOS.CH[MIOS_CHANNEL_15].CBDR    = MIOS_CH15_CBDR_INITIAL;
  //   MIOS.CH[MIOS_CHANNEL_15].CCR.U32 = MIOS_CH15_INITIAL.U32;
     //MIOS.CH[MIOS_CHANNEL_15].CSR.U32 = MIOS_RESET_CSR.U32;
   

//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_23
//=======================================================================================
     MIOS.CH[MIOS_CHANNEL_23].CADR    = 0;
     MIOS.CH[MIOS_CHANNEL_23].CBDR    = MIOS_CH23_CBDR_INITIAL;
     MIOS.CH[MIOS_CHANNEL_23].CCR.U32 = MIOS_CH23_INITIAL.U32;
     //MIOS.CH[MIOS_CHANNEL_23].CSR.U32 = MIOS_RESET_CSR.U32;
   
}

//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
void MIOS_PWM_Set_Period_And_DutyCycle_US(
   MIOS_Channel_T   channel,
   uint32_t             in_period,
   uint32_t             in_duty_cycle )
{

   uint32_t period_count, duty_count;


   //preiod and duty in us to count
   period_count = in_period*(EMIOS_FREQUENCY_HZ /((MIOS_PRESCALER_RATIO_1+1)*1000000));
   duty_count =   period_count*in_duty_cycle/1000;//in_duty_cycle*(EMIOS_FREQUENCY_HZ /((MIOS_PRESCALER_RATIO_1+1)*1000000));

  MIOS.CH[channel].CADR =  duty_count;
  MIOS.CH[channel].CBDR = period_count;

}


//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
void MIOS_PWM_Set_Frequency_And_DutyCycle(
   MIOS_Channel_T   channel,
   uint16_t             in_hz,
   uint16_t             in_duty_cycle )
{

   uint32_t period_count, duty_count;
  //duty cycle one count means 1/1000
   period_count =  EMIOS_FREQUENCY_HZ/(in_hz* (MIOS_PRESCALER_RATIO_1+1));
   duty_count = period_count*in_duty_cycle/1000;

  MIOS.CH[channel].CADR =  duty_count;
  MIOS.CH[channel].CBDR = period_count;

}

//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
void MIOS_PWM_Set_Duty_Cycle(
   MIOS_Channel_T   channel,
   uint32_t             in_duty_cycle )
{
  uint32_t  duty_count;
  duty_count = ( EMIOS_FREQUENCY_HZ*in_duty_cycle)/((MIOS_PRESCALER_RATIO_1+1)*1000000);

  MIOS.CH[channel].CADR =  in_duty_cycle;

}

//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
uint32_t  MIOS_PWM_Get_Duty_Cycle(
   MIOS_Channel_T   channel )
{

   return MIOS.CH[channel].CADR;

}

//=============================================================================
// MIOS_PULSE_Enable_Channel
//=============================================================================
void MIOS_PWM_Enable_Channel(
    MIOS_Channel_T   channel, 
    bool enable )
{

   if(enable)
       {
           MIOS.OUDR.U32 &=  (uint32_t) (~(1<<channel));  
        }
   else
   	{
   	    MIOS.CH[channel].CADR = 0;
           MIOS.OUDR.U32 |=(1<<channel);  
   	}
}

void MIOS_Interrupt_Enable(
    MIOS_Channel_T   channel)
{
	MIOS.CH[channel].CCR.F.FEN = 1;
}

void MIOS_Interrupt_Disable(
    MIOS_Channel_T   channel)
{
	MIOS.CH[channel].CCR.F.FEN = 0;
}

void MIOS_Interrupt_Clear_Flag(
    MIOS_Channel_T   channel)
{
	MIOS.CH[channel].CSR.F.FLAG = 1;
}

void MIOS_PWM_Set_Polarity(
    MIOS_Channel_T   channel, bool egde_pol)
{
	MIOS.CH[channel].CCR.F.EDPOL = egde_pol;
}

void MIOS_PWM_Set_Frozen(
    MIOS_Channel_T   channel, bool fren)
{
	MIOS.UCDIS.F.CHDIS8 = fren;
	MIOS.MCR.F.FRZ = fren;
	MIOS.CH[channel].CCR.F.FREN = fren;
}

void MIOS_PWM_Clear_FreeRunningRegister(
    MIOS_Channel_T   channel)
{
	MIOS.CH[channel].CCNTR = 0;
}

bool MIOS_Interrupt_Get_Flag(
    MIOS_Channel_T   channel)
{
	return MIOS.CH[channel].CSR.F.FLAG;
}

void MIOS_Interrupt_Clear_Pending(
   MIOS_Channel_T channel )
{
   uint32_t                 reg_value;
   reg_value = MIOS.CH[channel].CSR.U32;
   reg_value = (reg_value & MIOS_CSR_FLAG_CLEAR_MASK);
   MIOS.CH[channel].CSR.U32 = reg_value;
}


//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_pwm.c~6.1.3:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:54 2005
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Thu Jul 12 17:19:09 2007 %
//
// %version:         6.1.3 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

#include "dd_vsep.h"

#include "dd_vsep_pwm.h"
#include "dd_vsep_txd.h"
//#include "dd_pwm.h"
//#include "lux_math.h"
//#include "dd_port.h"
#include "dd_vsep_fault.h"
/********************************************
CDIV_PWM[x] Bit	 Valid Frequency Range (Hz) Step Size
0				  32 ¨C 475				  8Us/bit
1				  4.0 ¨C 60				  64Us/bit
********************************************/
#define VSEP_PWM_FREQ_DIVDER_THRSH_HZ (36 * 4)
#define VSEP_PWM_PERIOD_DIVDER_THRSH_MS (0.027 * 64000)
#define VSEP_PWM_PERIOD_DIVDER_THRSH_US (0.027* 1000000)

/*it is a 12bit buffer for period setting*/
#define VSEP_PWM_PERIOD_Limit	0xFFF

static const uint8_t VSEP_PWM_CHANNEL_MAP[VSEP_CHANNEL_MAX] =
{
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_1,
   VSEP_PWM_CHANNEL_2,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_3,
   VSEP_PWM_CHANNEL_4,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_5,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_6,
   VSEP_PWM_CHANNEL_7,
   VSEP_PWM_CHANNEL_8,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX,
   VSEP_PWM_CHANNEL_MAX
};

//=============================================================================
// VSEP_PWM_Get_PWM_Buffer
//=============================================================================
static uint16_t* VSEP_PWM_Get_PWM_Buffer(
   IO_Configuration_T   in_configuration)
{
   VSEP_Index_T               device = VSEP_Get_Device_Index(in_configuration);
   uint16_t                  *pwm_buf = NULL;
   VSEP_PWM_Channel_T        channel = VSEP_PWM_Get_Channel( in_configuration);
   
   if( channel < VSEP_PWM_CHANNEL_MAX )
   {
      pwm_buf = VSEP_PWM_Txd[device][channel];
   }

   return pwm_buf;
}

//=============================================================================
// VSEP_PWM_Device_Initialize
//=============================================================================
FAR_COS void VSEP_PWM_Device_Initialize(
   IO_Configuration_T in_configuration)
{
   VSEP_Index_T device = VSEP_Get_Device_Index( in_configuration );
   VSEP_PWM_Channel_T channel;

   for( channel = VSEP_PWM_CHANNEL_1; channel < VSEP_PWM_CHANNEL_MAX; channel++ )
   {
#ifdef VSEP_PWM_STATIC_INITIALIZATION
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL   ] = VSEP_PWM_TXD_INITIAL[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL   ];
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_ONTIME ] = VSEP_PWM_TXD_INITIAL[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_ONTIME ]; 
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_PERIOD ] = VSEP_PWM_TXD_INITIAL[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_PERIOD ]; 
#else
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_NOT_USED );
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_PWM_ONT_1 + ( channel * 4) );
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_ONTIME ] = 0;
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_PERIOD ] = 0;

#endif
   }
}

//=============================================================================
// VSEP_PWM_Device_Clear
//=============================================================================
void VSEP_PWM_Device_Clear(
   IO_Configuration_T in_configuration)
{
   VSEP_Index_T device = VSEP_Get_Device_Index( in_configuration );
   VSEP_PWM_Channel_T channel;

   for( channel = VSEP_PWM_CHANNEL_1; channel < VSEP_PWM_CHANNEL_MAX; channel++ )
   {
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_NOT_USED );
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_PWM_ONT_1 + ( channel * 4) );
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_ONTIME ] = 0;
      VSEP_PWM_Txd[ device ][ channel ][ VSEP_PWM_TXD_MESSAGE_PERIOD ] = 0;

   }
}

//=============================================================================
// VSEP_PWM_Channel_Initialize
//=============================================================================
FAR_COS void VSEP_PWM_Channel_Initialize( 
   IO_Configuration_T in_configuration)
{
   uint16_t *pwm_buf = VSEP_PWM_Get_PWM_Buffer( in_configuration );

   if( pwm_buf )// have such pwm channel
   {
      pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD] = VSEP_Msg_PWM_Set_Divider( pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD], VSEP_PWM_Get_Base_Frequency_Divider( in_configuration ) );
   // why only set period?
      	VSEP_PWM_Set_Period_And_Duty_Cycle(in_configuration,
                VSEP_PWM_Get_Initial_Period( in_configuration ),
                VSEP_PWM_Period_InType_Count,
            	  VSEP_PWM_Get_Initial_Duty_Cycle( in_configuration ),
            	  VSEP_PWM_DutyCycle_InType_Count,
            true,true );
   }
}

//=============================================================================
// VSEP_PWM_Channel_Clear
//=============================================================================
FAR_COS void VSEP_PWM_Channel_Clear(
   IO_Configuration_T in_configuration )
{
   uint16_t *pwm_buf = VSEP_PWM_Get_PWM_Buffer( in_configuration );

   if( pwm_buf )
   {
      pwm_buf[ VSEP_PWM_TXD_MESSAGE_ONTIME ] = 0;
      pwm_buf[ VSEP_PWM_TXD_MESSAGE_PERIOD ] = 0;
   }
}

//=============================================================================
// VSEP_PWM_Enable_Channel
//=============================================================================
FAR_COS void VSEP_PWM_Enable_Channel(
   IO_Configuration_T in_configuration )
{
   Parameter_Not_Used( in_configuration );
}

//=============================================================================
// VSEP_PWM_Disable_Channel
//=============================================================================
FAR_COS void VSEP_PWM_Disable_Channel( 
   IO_Configuration_T in_configuration )
{
   Parameter_Not_Used( in_configuration );
}

//=============================================================================
// VSEP_PWM_Get_Channel_Status
//
//=============================================================================
FAR_COS bool VSEP_PWM_Get_Channel_Status( IO_Configuration_T in_configuration )
{
   Parameter_Not_Used( in_configuration );

   return false;
}

//=============================================================================
// VSEP_PWM_Get_Channel
//=============================================================================
VSEP_PWM_Channel_T VSEP_PWM_Get_Channel( 
   IO_Configuration_T   in_configuration)
{
   VSEP_Channel_T     vsep_channel = VSEP_Get_Channel( in_configuration );
   VSEP_PWM_Channel_T      channel = VSEP_PWM_CHANNEL_MAP[ vsep_channel ];

   return channel;
}

//=============================================================================
// VSEP_PWM_Set_Period
//=============================================================================
void VSEP_PWM_Set_Period( 
   IO_Configuration_T   in_configuration,
   uint32_t             in_period ,
   VSEP_PWM_Period_InType_T 	in_type)
{
	uint32_t base_frequency_hz;
	uint32_t in_period_count = 0;
	VSEP_PWM_Channel_T    channel = VSEP_PWM_Get_Channel( in_configuration);
   	bool pwm_divider = false;
	VSEP_Channel_T     vsep_channel = VSEP_Get_Channel( in_configuration );
	
   uint16_t *pwm_buf = VSEP_PWM_Get_PWM_Buffer( in_configuration );

      
   if( pwm_buf )
   {
   	switch(in_type){
		case VSEP_PWM_Period_InType_MS://  in_period  T_Period_Millisecond_UW
			if( channel < VSEP_PWM_CHANNEL_MAX )
      			{
				pwm_divider = (in_period < (uint32_t)VSEP_PWM_PERIOD_DIVDER_THRSH_MS)?0:1;
         			pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD] = VSEP_Msg_PWM_Set_Divider( pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD], pwm_divider );      
      			}
			base_frequency_hz = VSEP_PWM_Timer_Get_Base_Frequency_HZ(in_configuration);
			in_period_count = VSEP_ConvertPeriodMillisecondToCountScaled(in_period,base_frequency_hz);
			break;
		case VSEP_PWM_Period_InType_US://  in_period  T_Period_Microsecond_UL
			if( channel < VSEP_PWM_CHANNEL_MAX )
      			{
				pwm_divider = (in_period < (uint32_t)VSEP_PWM_PERIOD_DIVDER_THRSH_US)?0:1;
         			pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD] = VSEP_Msg_PWM_Set_Divider( pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD], pwm_divider );      
      			}
			base_frequency_hz = VSEP_PWM_Timer_Get_Base_Frequency_HZ(in_configuration);
			in_period_count = VSEP_ConvertPeriodMicrosecondToCount(in_period,base_frequency_hz);
			break;
		case VSEP_PWM_Period_InType_HZ:
			
      			if( channel < VSEP_PWM_CHANNEL_MAX )
      			{
				pwm_divider = (in_period < (uint32_t)VSEP_PWM_FREQ_DIVDER_THRSH_HZ)?1:0;
         			pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD] = VSEP_Msg_PWM_Set_Divider( pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD], pwm_divider );      
      			}
			base_frequency_hz = VSEP_PWM_Timer_Get_Base_Frequency_HZ(in_configuration);
			in_period_count = VSEP_ConvertPeriodHERTZToCountScaled(in_period,base_frequency_hz);			
			break;
		case VSEP_PWM_Period_InType_Count:
		default:
			break;
		}
	if(in_period_count>=VSEP_PWM_PERIOD_Limit){
		in_period_count = VSEP_PWM_PERIOD_Limit;
	}
	VSEP_PWM_period_us[vsep_channel]=VSEP_ConvertPeriodCountToMicrosecond( in_period_count,base_frequency_hz);
	  pwm_buf[ VSEP_PWM_TXD_MESSAGE_PERIOD ] = VSEP_Msg_PWM_Set_Period( pwm_buf[ VSEP_PWM_TXD_MESSAGE_PERIOD ], in_period_count );
   }
}

//=============================================================================
// VSEP_PWM_Get_Period
//=============================================================================
FAR_COS uint32_t VSEP_PWM_Get_Period(
   IO_Configuration_T   in_configuration ,
   VSEP_PWM_Period_ReturnType_T  return_type)
{
   uint16_t   *pwm_buf = VSEP_PWM_Get_PWM_Buffer( in_configuration );
   uint32_t	base_frequency;

  uint32_t		return_period = 0;

   base_frequency = VSEP_PWM_Timer_Get_Base_Frequency_HZ(in_configuration);

   if( pwm_buf )
   {
      return_period = VSEP_Msg_PWM_Get_Period( pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD] );

      if( return_period == 0 )
      {
         return_period = 1;
      }
   }
  
	
    switch(return_type){
		case VSEP_PWM_Period_ReturnType_HZ://  return_period  T_Freq_HERTZ_UW
			return_period =VSEP_ConvertPeriodCountToHERTZScaled(return_period,base_frequency);
			break;
		case VSEP_PWM_Period_ReturnType_MS://  return_period  T_Period_Millisecond_UW
			return_period= VSEP_ConvertPeriodCountToMillisecondScaled(return_period,base_frequency);
			break;
		case VSEP_PWM_Period_ReturnType_US://  return_period  T_Period_Microsecond_UL
			return_period =VSEP_ConvertPeriodCountToMicrosecond(return_period,base_frequency);
			break;
		case VSEP_PWM_Period_ReturnType_Count:
		default:
			break;
	}
return 	return_period;
   
}

//=============================================================================
// VSEP_PWM_Set_Duty_Cycle
//=============================================================================
void VSEP_PWM_Set_Duty_Cycle(
   IO_Configuration_T   in_configuration,
   uint32_t             in_on_time ,
   VSEP_PWM_DutyCycle_InType_T	in_type)
{
   uint32_t    period_count = 0;
   uint32_t    in_on_time_count = 0;
   uint32_t base_frequency_hz;
   VSEP_Channel_T   vsep_channel = VSEP_Get_Channel(in_configuration);
   uint16_t *pwm_buf = VSEP_PWM_Get_PWM_Buffer( in_configuration );

     base_frequency_hz = VSEP_PWM_Timer_Get_Base_Frequency_HZ(in_configuration);

   if( pwm_buf )
   {
   	
	  switch(in_type){
	  	case VSEP_PWM_DutyCycle_InType_Percent://T_Duty_PERCENT_UW
	  		
			period_count = VSEP_Msg_PWM_Get_Period( pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD] );
			
      			if(0==in_on_time){
				in_on_time_count = 0;
				VSEP_PWM_ontime_us[vsep_channel] = 0;
			}else if(0x8000>in_on_time){					
				in_on_time_count=VSEP_ConvertDutyPercentToCountScaled(in_on_time,period_count);
				VSEP_PWM_ontime_us[vsep_channel] = VSEP_ConvertDutyCountToMicrosecond(in_on_time_count, base_frequency_hz);
			}else{
				in_on_time_count = period_count+1;
				VSEP_PWM_ontime_us[vsep_channel] = VSEP_PWM_period_us[vsep_channel];
			}
			
			break;
		case VSEP_PWM_DutyCycle_InType_Count://COUNT_DW
		default:
			in_on_time_count = in_on_time;
			break;		
	  }      

      pwm_buf[VSEP_PWM_TXD_MESSAGE_ONTIME] = VSEP_Msg_PWM_Set_OnTime( pwm_buf[VSEP_PWM_TXD_MESSAGE_ONTIME], in_on_time_count );
   }
}

//=============================================================================
// VSEP_PWM_Get_Duty_Cycle
//=============================================================================
FAR_COS uint32_t VSEP_PWM_Get_Duty_Cycle(
   IO_Configuration_T   in_configuration,
   VSEP_PWM_DutyCycle_ReturnType_T	return_type)
{
   uint16_t *pwm_buf = VSEP_PWM_Get_PWM_Buffer( in_configuration );
   uint32_t on_time_count = 0;
   uint32_t on_time_percent = 0;
    uint32_t on_time_ms = 0;
    uint32_t on_time_us = 0;
   uint32_t    period = 0;
   uint32_t	on_time_return =0;
   uint32_t	base_frequency;
   
   if( pwm_buf )
   {
      base_frequency = VSEP_PWM_Timer_Get_Base_Frequency_HZ(in_configuration);
      on_time_count = VSEP_Msg_PWM_Get_OnTime( pwm_buf[VSEP_PWM_TXD_MESSAGE_ONTIME] );
	period = VSEP_Msg_PWM_Get_Period( pwm_buf[VSEP_PWM_TXD_MESSAGE_PERIOD] );

      if( period == 0 )
      {
         period = 1;
      }
   
   
   	switch(return_type){
   		case VSEP_PWM_DutyCycle_ReturnType_Percent://  on_time_return  T_Duty_PERCENT_UW
			on_time_percent = VSEP_ConvertDutyCountToPercentScaled( on_time_count,period);
			on_time_return= on_time_percent;
			break;
		case VSEP_PWM_DutyCycle_ReturnType_MS://  on_time_return  T_Period_Millisecond_UW
			on_time_ms= VSEP_ConvertDutyCountToMillisecondScaled( on_time_count,base_frequency);
			on_time_return= on_time_ms;
			break;
		case VSEP_PWM_DutyCycle_ReturnType_US://  on_time_return  T_Period_Microsecond_UL
			on_time_us= VSEP_ConvertDutyCountToMicrosecond( on_time_count,base_frequency);
			on_time_return= on_time_us;
			break;
		case VSEP_PWM_DutyCycle_ReturnType_Count:// on_time_return COUNT_DW
		default:
			  on_time_return =on_time_count;
			break;
 	  }
   }
   return on_time_return;
}

//=============================================================================
// VSEP_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
FAR_COS void VSEP_PWM_Set_Period_And_Duty_Cycle(
   IO_Configuration_T   in_configuration,
   uint32_t             in_period,
   VSEP_PWM_Period_InType_T in_period_type,
   uint32_t             in_on_time,
   VSEP_PWM_DutyCycle_InType_T  in_duty_type,
   bool                 in_update_period,
    bool                 in_update_duty)
{
   uint16_t *pwm_buf = VSEP_PWM_Get_PWM_Buffer( in_configuration );
   VSEP_Index_T            index = VSEP_Get_Device_Index( in_configuration );



 if(in_update_duty)
 {
   VSEP_PWM_Set_Duty_Cycle(in_configuration, in_on_time,in_duty_type );
 }
   
   if( in_update_period )
   {
      VSEP_PWM_Set_Period( in_configuration, in_period,in_period_type );
   }
}

//=============================================================================
// VSEP_PWM_Set_Period_And_Duty_Cycle_Immediate
//=============================================================================
FAR_COS void VSEP_PWM_Set_Period_And_Duty_Cycle_Immediate(
   IO_Configuration_T   in_configuration,
   uint32_t             in_period,
   VSEP_PWM_Period_InType_T in_period_type,
   uint32_t             in_on_time,
    VSEP_PWM_DutyCycle_InType_T  in_duty_type,
   bool                 in_update_period ,
    bool                 in_update_duty)
{
   VSEP_PWM_Set_Period_And_Duty_Cycle( in_configuration, in_period, in_period_type,in_on_time,in_duty_type, in_update_period,in_update_duty);
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_PWM );

}


//=============================================================================
// VSEP_PWM_Get_Base_Frequency 
//=============================================================================
FAR_COS uint32_t VSEP_PWM_Timer_Get_Base_Frequency_HZ(
   IO_Configuration_T in_configuration)
{
   uint32_t base_frequency_hz = 0;

//   uint16_t    *pwm_buf = VSEP_PWM_Get_PWM_Buffer( in_configuration );
   VSEP_Index_T            index = VSEP_Get_Device_Index( in_configuration );
   VSEP_PWM_Channel_T    channel = VSEP_PWM_Get_Channel( in_configuration);

   if( channel < VSEP_PWM_CHANNEL_MAX )
   {
      VSEP_PWM_CDIV_T cdiv = VSEP_Msg_PWM_Get_Divider(  VSEP_PWM_Txd[ index][channel][VSEP_PWM_TXD_MESSAGE_PERIOD] );

      if( cdiv == VSEP_PWM_CDIV_32 )
      {
         base_frequency_hz = VSEP_BASE_FREQUENCY / VSEP_PWM_CDIV_DIVIDER_0; 
      }
      else
      {
         base_frequency_hz = VSEP_BASE_FREQUENCY / VSEP_PWM_CDIV_DIVIDER_1;
      }
   }

   return base_frequency_hz;//COUNT_DW
}

//=============================================================================
// VSEP_PWM_Get_State
//=============================================================================
/*IO_Timer_State_T VSEP_PWM_Timer_Get_State(
   IO_Configuration_T in_configuration)
{
   Parameter_Not_Used( in_configuration );           //This line gets rid of the compiler warning

   return IO_TIMER_STATE_RUNNING;
}*/

//=============================================================================
// VSEP_PWM_Timer_Get_Size
//=============================================================================
/*IO_Timer_Size_T VSEP_PWM_Timer_Get_Size(
   IO_Configuration_T in_configuration )
{
   Parameter_Not_Used( in_configuration );          //This line gets rid of the compiler warning

   return IO_TIMER_12_BIT;
}
*/
//=============================================================================
// VSEP_DISCRETE_Initialize_Channel
//=============================================================================
FAR_COS void VSEP_PWM_DISCRETE_Channel_Initialize(
   IO_Configuration_T in_configuration)
{
   VSEP_PWM_DISCRETE_Set_State( in_configuration, 
   VSEP_PWM_Get_Initial_State( in_configuration ) == IO_ACTIVE ? true : false );
}

//=============================================================================
// VSEP_DISCRETE_Clear_Channel
//=============================================================================
FAR_COS void VSEP_PWM_DISCRETE_Channel_Clear(
   IO_Configuration_T in_configuration)
{
   VSEP_PWM_Set_Period( in_configuration, 0,VSEP_PWM_Period_InType_MS );
   VSEP_PWM_Set_Duty_Cycle( in_configuration, 0,VSEP_PWM_DutyCycle_InType_Percent );
}

//=============================================================================
// VSEP_DISCRETE_Get_State
//=============================================================================
FAR_COS bool VSEP_PWM_DISCRETE_Get_State( 
   IO_Configuration_T in_configuration)
{

   bool state = false;
   uint16_t duty_cycle;
   uint16_t period;
   IO_Polarity_T polarity = VSEP_PWM_Get_Polarity( in_configuration );
	//T_Duty_PERCENT_UW
   duty_cycle = (uint16_t)VSEP_PWM_Get_Duty_Cycle( in_configuration,VSEP_PWM_DutyCycle_ReturnType_Percent );
	//T_Period_Millisecond_UW
   period     = (uint16_t)VSEP_PWM_Get_Period( in_configuration,VSEP_PWM_Period_ReturnType_MS);

   if( duty_cycle == 0 )
   {
      state = false;
   }
   else if( duty_cycle >= 0x7FFF )//T_Duty_PERCENT_UW
   {
      state =  true;
   }
   else
   {
      //output is not used as discrete
   }

   if(polarity != IO_ACTIVE_HIGH)
   {
      state = (state == true) ? false : true;
   }
   
   return state;
}

//=============================================================================
// VSEP_DISCRETE_Set_State
// what is the logic? period = 0, ontime = 1=>    DISCRETE ON?
//=============================================================================
FAR_COS void VSEP_PWM_DISCRETE_Set_State(
   IO_Configuration_T in_configuration,
   bool               in_state)
{
   IO_Polarity_T polarity = VSEP_PWM_Get_Polarity( in_configuration );
   VSEP_Channel_T   vsep_channel = VSEP_Get_Channel(in_configuration);
											//T_Period_Millisecond_UW
   VSEP_PWM_Set_Period( in_configuration,0 ,VSEP_PWM_Period_InType_MS);

   if(polarity != IO_ACTIVE_HIGH)
   {
      in_state = (in_state == true) ? false : true;
   }
   
   if(in_state){
   	VSEP_DIS_ON_OFF_state |=(Mask32(vsep_channel,1));
   }else{
   	VSEP_DIS_ON_OFF_state &=~(Mask32(vsep_channel,1));
   }
   
   if( in_state == true )
   {			//T_Duty_PERCENT_UW
      VSEP_PWM_Set_Duty_Cycle( in_configuration, 0x8000,VSEP_PWM_DutyCycle_InType_Percent);
   }
   else
   {			//T_Duty_PERCENT_UW
      VSEP_PWM_Set_Duty_Cycle( in_configuration, 0 ,VSEP_PWM_DutyCycle_InType_Percent);
   }

}

//=============================================================================
// VSEP_DISCRETE_Set_Immediate_State
//=============================================================================
FAR_COS void VSEP_PWM_DISCRETE_Set_Immediate_State(
   IO_Configuration_T in_configuration,
   bool               in_state)
{
   VSEP_PWM_DISCRETE_Set_State( in_configuration, in_state );
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_PWM );

}

//=============================================================================
// VSEP_DISCRETE_Toggle_State
//=============================================================================
FAR_COS void VSEP_PWM_DISCRETE_Toggle_State(
   IO_Configuration_T in_configuration)
{
         VSEP_PWM_DISCRETE_Set_State(in_configuration, 
         VSEP_PWM_DISCRETE_Get_State( in_configuration ) == true ? false : true );
}

//=============================================================================
// VSEP_DISCRETE_Toggle_Immediate_State
//=============================================================================
FAR_COS void VSEP_PWM_DISCRETE_Toggle_Immediate_State(
   IO_Configuration_T in_configuration)
{
   VSEP_PWM_DISCRETE_Toggle_State( in_configuration );
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_PWM );

}
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR                 Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a                  08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 * 1.1  n/a                  09/08/24 WSQ Enable the code for the automatic choose pwm_divider
 * 1.2  mt20u2#442     09/10/19 Mk    VSEP_PWM_Set_Period QAC warning Msg(7:3347)correction
\*===========================================================================*/

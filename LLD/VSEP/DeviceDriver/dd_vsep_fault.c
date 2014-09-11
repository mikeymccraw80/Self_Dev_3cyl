//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_fault.c~16.1.1.1.3.1.1.2.1:csrc:mt20u2#1 %
//
// created_by:       fz3pdz
//
// date_created:     Fri May 13 11:33:39 2005
//
// %derived_by:      nz45s2 %
//
// %date_modified:   Thu Mar  3 18:31:05 2011 %
//
// %version:         16.1.1.1.3.1.1.2.1 %
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
#include "io_type.h"
#include "dd_vsep.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_soh.h"
#include "dd_vsep_est_select.h"
#include "io_config_vsep.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_discrete_interface.h"
#include "dd_vsep_pwm_interface.h"
#include "io_config_crank.h"
#include "io_config_dspi.h"
#include "io_config_dma.h"
#include "dd_vsep_init_config.h"

/* import global external variables */
extern const VSEP_Fault_Channel_Data_T VSEP_Fault_Logging[VSEP_CHANNEL_PCH_30_FLT_LVL_7+1];

/* Fault messge buffer difinition for EST */
uint16_t    VSEP_EST_Fault_Txd[VSEP_EST_FAULT_TXD_MESSAGE_MAX];
uint16_t    VSEP_EST_Fault_Rxd[VSEP_EST_FAULT_RXD_MESSAGE_MAX];
uint8_t     VSEP_EST_Fault_SYNC_Txd[VSEP_EST_FAULT_SYNC_TXD_MESSAGE_MAX_BYTE];
uint8_t     VSEP_EST_Fault_SYNC_Rxd[VSEP_EST_FAULT_SYNC_RXD_MESSAGE_MAX_BYTE];

/* Fault messge buffer difinition for others */
//extern const uint16_t VSEP_FAULT_TXD[VSEP_FAULT_TXD_MESSAGE_MAX]
uint16_t    VSEP_Fault_Rxd[VSEP_FAULT_RXD_MESSAGE_MAX];

/* Fault interface for upper layer */
Fault_Log_T VSEP_Fault_Log[VSEP_CHANNEL_MAX];

uint16_t VSEP_Fault_Counter[VSEP_CHANNEL_PCH_30_FLT_LVL_7+1];
uint16_t VSEP_Fault_Counter_Decrement_Counter;
uint32_t VSEP_PWM_ontime_us[30];
uint32_t VSEP_PWM_period_us[30];

uint32_t VSEP_DIS_ON_OFF_state = 0x00000000;
bool     EST_Diagnostic_7p8ms[4];

/* local private variables define */
uint32_t Channel_Protect_Enable;

//****************************************************************//
//this const is created to derive the diagnostic infromation from VSEP_Fault_Rxd,
// if the diagnostic structure is not changed, this const should be not changed
const	uint8_t	diagnostic_index[30]={	1,1,1,1, 		 //the fisrt 4 will be ignored, the diagnostic  will be done in VSEP_EST_Fault_SYNC_Interface
										1,1,1,1,1,1,1,1,// fist byte for channel 5~12										
										2,2,2,2,2,2,2,2,//seconde byte for channel 13 ~ 20
										3,3,3,3,3,3,3,3,// third byte for channel 21 ~ 28
										4,4			  // forth byte for channel 29.30
										};
//this const is created to derive the diagnostic infromation from VSEP_Fault_Rxd,
// if the diagnostic structure is not changed, this const should be not changed
const	uint8_t	diagnostic_bit_position[30]={  0,2,4,6, 			//ignored,   the diagnostic  will be done in VSEP_EST_Fault_SYNC_Interface
											8,10,12,14,0,2,4,6,// fist byte for channel 5~12	 
											8,10,12,14,0,2,4,6,//seconde byte for channel 13 ~ 20
											8,10,12,14,0,2,4,6,// third byte for channel 21 ~ 28
											8,10				// forth byte for channel 29.30
											};				// first the higher adress data out
//*************************************************************************//											
#ifdef  VSEP_CALIBRATION_ENABLE
uint8_t	Filter_Time_Array[30];
#else
const	uint8_t Filter_Time_Array[30]={		VSEP_FAULT_FILTER_TIME_15US,VSEP_FAULT_FILTER_TIME_15US,
											VSEP_FAULT_FILTER_TIME_15US,VSEP_FAULT_FILTER_TIME_15US,
											VSEP_FAULT_FILTER_TIME_15US,VSEP_FAULT_FILTER_TIME_15US,
											VSEP_FAULT_FILTER_TIME_15US,VSEP_FAULT_FILTER_TIME_15US,
											VSEP_FAULT_FILTER_TIME_15US,VSEP_FAULT_FILTER_TIME_15US,
											VSEP_FAULT_FILTER_TIME_15US,VSEP_FAULT_FILTER_TIME_15US,
											VSEP_FAULT_FILTER_TIME_46US,VSEP_FAULT_FILTER_TIME_46US,
											VSEP_FAULT_FILTER_TIME_46US,VSEP_FAULT_FILTER_TIME_46US,
											VSEP_FAULT_FILTER_TIME_7_5US,VSEP_FAULT_FILTER_TIME_7_5US,
											VSEP_FAULT_FILTER_TIME_15US,VSEP_FAULT_FILTER_TIME_15US,
											VSEP_FAULT_FILTER_TIME_15US,VSEP_FAULT_FILTER_TIME_15US,
											VSEP_FAULT_FILTER_TIME_15US,VSEP_FAULT_FILTER_TIME_15US,
											VSEP_FAULT_FILTER_TIME_46US,VSEP_FAULT_FILTER_TIME_46US,
											VSEP_FAULT_FILTER_TIME_46US,VSEP_FAULT_FILTER_TIME_46US,
											VSEP_FAULT_FILTER_TIME_46US,VSEP_FAULT_FILTER_TIME_46US
											};
#endif
//this const discrip the VSEP PWM(8channel) which channel was set to be VSEP SPI control PWM.
//Please change it according to you project PMD
const uint8_t VSEP_PWM_PCH_CHANNEL_MAP[VSEP_CHANNEL_MPIO_1] =
{
    VSEP_PWM_CHANNEL_MAX,// 1
    VSEP_PWM_CHANNEL_MAX,// 2
    VSEP_PWM_CHANNEL_MAX,// 3
    VSEP_PWM_CHANNEL_MAX,// 4
    VSEP_PWM_CHANNEL_MAX,// 5
    VSEP_PWM_CHANNEL_MAX,// 6
    VSEP_PWM_CHANNEL_MAX,// 7
    VSEP_PWM_CHANNEL_MAX,// 8
    VSEP_PWM_CHANNEL_MAX,// 9
    VSEP_PWM_CHANNEL_MAX,// 10
    VSEP_PWM_CHANNEL_MAX,// 11
    VSEP_PWM_CHANNEL_MAX,// 12
    VSEP_PWM_CHANNEL_MAX,// 13
    VSEP_PWM_CHANNEL_MAX,// 14
    VSEP_PWM_CHANNEL_1,// 15
    VSEP_PWM_CHANNEL_2,// 16
    VSEP_PWM_CHANNEL_MAX,// 17
    VSEP_PWM_CHANNEL_MAX,// 18
    VSEP_PWM_CHANNEL_MAX,// 19
    VSEP_PWM_CHANNEL_MAX,// 20
    VSEP_PWM_CHANNEL_3,// 21
    VSEP_PWM_CHANNEL_4,// 22
    VSEP_PWM_CHANNEL_MAX,// 23
    VSEP_PWM_CHANNEL_5,// 24
    VSEP_PWM_CHANNEL_MAX,// 25
    VSEP_PWM_CHANNEL_MAX,// 26
    VSEP_PWM_CHANNEL_6,// 27
    VSEP_PWM_CHANNEL_7,// 28
    VSEP_PWM_CHANNEL_8,// 29
    VSEP_PWM_CHANNEL_MAX// 30
};

//=============================================================================
// VSEP_FAULT_Is_Message_Valid
//=============================================================================
bool VSEP_FAULT_Is_Message_Valid(IO_Configuration_T in_configuration, VSEP_Message_T     in_message )
{
	bool spi_msg_fault;
	uint16_t fault_data;

	switch ( in_message ) {
	case VSEP_MESSAGE_SOH_STATUS:
		 fault_data = (uint16_t) ( VSEP_SOH_Status_Rxd[VSEP_SOH_STATUS_RXD_MESSAGE_FLT] );
		 break;
	case VSEP_MESSAGE_SOH:
	default:
		fault_data = (uint16_t) ( VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_FLT] );
		break;
	}

	if((VSEP_Msg_CMD_Get_Test_Bit_Low( fault_data ) == 0) &&
	  (VSEP_Msg_CMD_Get_Test_Bit_High( fault_data ) == 1))
	{
		spi_msg_fault = true;
	}
	else
	{
		spi_msg_fault = false;
	}

	return spi_msg_fault;
}

//=============================================================================
// VSEP_Fault_Diagnose_Channels, only for PCH
//=============================================================================
void VSEP_Fault_Diagnose_Channels(void* in_pointer)
{
	uint8_t            x,fault_index,fault_position;
	VSEP_Channel_T     fault_channel;
	IO_Configuration_T configuration;
	uint32_t           period;
	uint32_t           on_time;
	uint32_t           off_time;
	uint32_t           period_in_counts;
	uint32_t           counts_per_time;
	uint32_t           percent_in_counts;
	VSEP_Fault_PCH_T   vsep_pch_fault;
	static int fault_clear_count;

	VSEP_Fault_Channel_Data_T *vsep_fault_channel_data = (VSEP_Fault_Channel_Data_T*)in_pointer;
	fault_clear_count ++;
	/* clear fault log buffer every 500ms */
	if (fault_clear_count >= 50) {
		VSEP_Fault_Log_Clear();
		fault_clear_count = 0;
	}
	if (vsep_fault_channel_data != NULL) {
		// diagnose fault, and also provide delay between IO_DISCRETE_Set_Immediate_State commands
		//VSEP_Fault_Diagnose_Get_channel_state();
		for( x = 0; x <= VSEP_CHANNEL_PCH_30_FLT_LVL_7; x++ )
		{
			configuration =vsep_fault_channel_data[x].fault_configuration;
			fault_channel = VSEP_Get_Channel( configuration );

			if(x > Number_of_EST_Channel)//the EST channel diagnostic was done in function--VSEP_EST_Fault_SYNC_Interface
			{
				vsep_pch_fault = (VSEP_Fault_PCH_T)Extract_Bits( VSEP_Fault_Rxd[diagnostic_index[x]],
                                    diagnostic_bit_position[x], BIT_2 );
    
				// check for discrete signals
				switch (vsep_fault_channel_data[x].kind) {
				case VSEP_FAULT_IO_KIND_DISCRETE:
				{
					if (VSEP_DIS_ON_OFF_state & vsep_fault_channel_data[x].io_mask) {
						VSEP_Fault_Log[fault_channel] |= FAULT_TESTED_SHORT_TO_BATTERY_SET;
						// if discrete signal report short to battery fault
						if (vsep_pch_fault == VSEP_FAULT_PCH_SHORT_TO_BATTERY_FAULT ) {
							VSEP_Fault_Log[fault_channel] |= FAULT_OCCURED_SHORT_TO_BATTERY_SET;
							if (VSEP_Fault_Counter[x] < (KsVSEP_Diagnostic_Counter_Thd)) {
								VSEP_Fault_Counter[x] = VSEP_Fault_Counter[x] + VSEP_CHANNEL_FAULT_COUNTER_INCREMENT_STEP;
							}
							// toggle discrete signal to re-enable signal again
							VSEP_DiscreteToggleImmediate(vsep_fault_channel_data[x].io_configuration);
							VSEP_DiscreteToggleImmediate(vsep_fault_channel_data[x].io_configuration);
						}
					} else {
						VSEP_Fault_Log[fault_channel] |=FAULT_TESTED_OPEN_CIRCUIT_SET;
						VSEP_Fault_Log[fault_channel] |= FAULT_TESTED_SHORT_TO_GROUND_SET;
						if(vsep_pch_fault == VSEP_FAULT_PCH_OPEN_FAULT ){
							VSEP_Fault_Log[fault_channel] |= FAULT_OCCURED_OPEN_CIRCUIT_SET;
						} else if (vsep_pch_fault == VSEP_FAULT_PCH_SHORT_TO_GROUND_FAULT ){ 
							VSEP_Fault_Log[fault_channel] |= FAULT_OCCURED_SHORT_TO_GROUND_SET;
						}
					}
					break;
				}
				case VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION: // signal is not discrete
				{
					on_time = VSEP_PWM_ontime_us[fault_channel];//HZ
					period = VSEP_PWM_period_us[fault_channel];
					off_time = period - on_time;
					if ((off_time == 0) || (on_time > ( Filter_Time_Array[fault_channel]+ 1))) {
						VSEP_Fault_Log[fault_channel] |= FAULT_TESTED_SHORT_TO_BATTERY_SET;
						// check if shorted to battery and if pwm is on 100%, toggle to reset output
						if (vsep_pch_fault == VSEP_FAULT_PCH_SHORT_TO_BATTERY_FAULT ) {
							VSEP_Fault_Log[fault_channel] |= FAULT_OCCURED_SHORT_TO_BATTERY_SET;
							if (VSEP_Fault_Counter[x] < (KsVSEP_Diagnostic_Counter_Thd)) {
								// increment channel fault counter
								VSEP_Fault_Counter[x] = VSEP_Fault_Counter[x] + VSEP_CHANNEL_FAULT_COUNTER_INCREMENT_STEP;
							}
							if(on_time == period) {
								//when PWM is at 100% duty cycle, pin must be toggled to reset pin fault
								//need put something here, need a function to toggle the pin
								VSEP_PWM_DISCRETE_Toggle_Immediate_State(vsep_fault_channel_data[x].io_configuration);
								VSEP_PWM_DISCRETE_Toggle_Immediate_State(vsep_fault_channel_data[x].io_configuration);
							}
						}
					}
					if((on_time == 0) || (off_time > VSEP_MIN_OFF_TIME_FOR_TEST)) {
						VSEP_Fault_Log[fault_channel] |= FAULT_TESTED_OPEN_CIRCUIT_SET;
						VSEP_Fault_Log[fault_channel] |= FAULT_TESTED_SHORT_TO_GROUND_SET;
						if(vsep_pch_fault == VSEP_FAULT_PCH_OPEN_FAULT ){   
							VSEP_Fault_Log[fault_channel] |= FAULT_OCCURED_OPEN_CIRCUIT_SET;
						}else if(vsep_pch_fault == VSEP_FAULT_PCH_SHORT_TO_GROUND_FAULT ){ 
							VSEP_Fault_Log[fault_channel] |= FAULT_OCCURED_SHORT_TO_GROUND_SET;
						}
					}
					break;
				}
				case VSEP_FAULT_IO_DUMMY_PIN:
					/*dummy pin*/
					break;
				case VSEP_FAULT_IO_KIND_OUTPUT_COMPARE:
				case VSEP_FAULT_IO_KIND_IGNORE_PIN_STATE:
				default:
				{
					VSEP_Fault_Log[fault_channel] |= FAULT_TESTED_SHORT_TO_BATTERY_SET;             
					// if IGBT - only diagnose short to battery, we should change the logic
					VSEP_Fault_Log[fault_channel] |= FAULT_TESTED_OPEN_CIRCUIT_SET;
					VSEP_Fault_Log[fault_channel] |= FAULT_TESTED_SHORT_TO_GROUND_SET;
					if (vsep_pch_fault == VSEP_FAULT_PCH_SHORT_TO_BATTERY_FAULT ) {
						VSEP_Fault_Log[fault_channel] |= FAULT_OCCURED_SHORT_TO_BATTERY_SET;
						if (VSEP_Fault_Counter[x] < (KsVSEP_Diagnostic_Counter_Thd)) {
							// increment channel fault counter
							VSEP_Fault_Counter[x] = VSEP_Fault_Counter[x] + VSEP_CHANNEL_FAULT_COUNTER_INCREMENT_STEP;
						}
					} else if (vsep_pch_fault == VSEP_FAULT_PCH_OPEN_FAULT ) {
							VSEP_Fault_Log[ fault_channel ] |= FAULT_OCCURED_OPEN_CIRCUIT_SET;
					} else if (vsep_pch_fault == VSEP_FAULT_PCH_SHORT_TO_GROUND_FAULT ){
							VSEP_Fault_Log[ fault_channel ] |= FAULT_OCCURED_SHORT_TO_GROUND_SET;
					}
				}
				}
			} else {
				EST_Diagnostic_7p8ms[x] = true;
			}

			//application can not set the channel to high again
			if( (VSEP_Fault_Counter[x] >= (KsVSEP_Diagnostic_Counter_Thd)) 
				&& (VSEP_Channel_Enabled & (vsep_fault_channel_data[x].io_mask))
				&& (Channel_Protect_Enable & (vsep_fault_channel_data[x].io_mask)))
			{
				// channel is discrete, disable channel by setting to FALSE
				if (VSEP_FAULT_IO_KIND_DISCRETE == vsep_fault_channel_data[x].kind) {
					//VSEP_Diagnostic_Set_Discrete_Channel_State( vsep_fault_channel_data[x].io_configuration,false);
					VSEP_DiscreteSet( vsep_fault_channel_data[x].fault_configuration,false);
					VSEP_Channel_Enabled	&=(~((vsep_fault_channel_data[x].io_mask)));
				} else if (VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION == vsep_fault_channel_data[x].kind) {
				// channel is PWM, disable channel by setting duty cycle to 0%
					//VSEP_Diagnostic_PWM_Set_Duty_Cycle_Immediate(vsep_fault_channel_data[x].io_configuration, 0 );
					VSEP_PWM_DISCRETE_Toggle_Immediate_State(vsep_fault_channel_data[x].io_configuration);
					VSEP_PWM_DISCRETE_Toggle_Immediate_State(vsep_fault_channel_data[x].io_configuration);
					VSEP_Channel_Enabled	&=(~((vsep_fault_channel_data[x].io_mask)));
				} else if (VSEP_FAULT_IO_DUMMY_PIN == vsep_fault_channel_data[x].kind) {
					/*dummy pin*/
				} else if ((x >= 0) && (x <= 3)) {
				// channel is EST, disable channel
					// do not perform turnoff ESTC and ESTD in waste spark mode
					if (VSEP_EST_Select_Get_Mode_PF() == VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED) {
						VSEP_Channel_Enabled &=(~((vsep_fault_channel_data[x].io_mask)));
					} else if (VSEP_EST_Select_Get_Mode_PF() == VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED) {
						if  ((x >= 0) && (x <= 1)) {   
							VSEP_Channel_Enabled	&=(~((vsep_fault_channel_data[x].io_mask)));
							VSEP_Channel_Enabled	&=(~((vsep_fault_channel_data[x+2].io_mask)));
						}
					}
				} else {//here is for the INJ set the VSEP_Channel_Enabled
					VSEP_Channel_Enabled	&=(~((vsep_fault_channel_data[x].io_mask)));
				}
			}
		}

		//decreace the counter
		if (VSEP_Fault_Counter_Decrement_Counter < VSEP_FAULT_COUNTER_DECREMENT_TIME_COUNT) {
			VSEP_Fault_Counter_Decrement_Counter++;
		} else {
			for( x = 0; x <= VSEP_CHANNEL_PCH_30_FLT_LVL_7; x++ ) {
				if ((VSEP_Fault_Counter[x] < (KsVSEP_Diagnostic_Counter_Thd)) && (VSEP_Fault_Counter[x] > 0)) {
					VSEP_Fault_Counter[x] = VSEP_Fault_Counter[x] - VSEP_CHANNEL_FAULT_COUNTER_DECREMENT_STEP;
				}
			}
			VSEP_Fault_Counter_Decrement_Counter = 0;
		}
	}
}

//=============================================================================
// VSEP_Fault_GRADCOUNT_Diagnose_EST_Channel
//=============================================================================
void VSEP_Fault_GRADCOUNT_Diagnose_EST_Channel(//need consider calfuly
   IO_Configuration_T in_configuration,
   uint8_t            in_channel,
   uint32_t           in_time )
{
   VSEP_Channel_T channel = (VSEP_Channel_T)in_channel;
   uint32_t       period_in_counts;
   uint8_t        gradcount;
   uint8_t        dwell;

   period_in_counts = VSEP_ConvertPeriodMillisecondToCountScaled(in_time,VSEP_GRADCOUNT_BASE_FREQUENCY);

   dwell = (uint8_t)period_in_counts + 1;

   // send the message
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_EST_FAULT );

   // Read GRADCOUNT from SPI data
   gradcount = VSEP_Msg_Get_GRADCOUNT( VSEP_EST_Fault_Rxd[ VSEP_EST_FAULT_RXD_MESSAGE_GRADCOUNT ] );

#ifdef VSEP_EST_DIAGNOSTIC_DEBUG
   VSEP_EST_Select_Dwell_Current_Time[ channel ]     = dwell;
#endif

   // fault has occured if gradcount is within 128us of dwell (128us / 32us gradcount resolution = 4 counts @ 4MHz VSEP clock)
   if ( ( 0 != dwell ) && ( ( dwell - gradcount ) < VSEP_GRADCOUNT_FAULT_WINDOW ) )
   {
      VSEP_Fault_Log[ channel ] = FAULT_Set_Occured_Open_Circuit( VSEP_Fault_Log[ channel ], true );
      VSEP_Fault_Log[ channel ] = FAULT_Set_Occured_Short_To_Ground( VSEP_Fault_Log[ channel ], true );
   }

   VSEP_Fault_Log[ channel ] = FAULT_Set_Tested_Open_Circuit( VSEP_Fault_Log[channel], true );
   VSEP_Fault_Log[ channel ] = FAULT_Set_Tested_Short_To_Ground( VSEP_Fault_Log[channel], true );
}

//===================================================================
// VSEP_FAULT_EST_Initialize_Device
//===================================================================
void VSEP_FAULT_EST_Initialize_Device(IO_Configuration_T in_configuration)
{
#ifdef VSEP_FAULT_EST_STATIC_INITIALIZATION
	VSEP_EST_Fault_Txd[ VSEP_EST_FAULT_TXD_MESSAGE_CTRL ]     = VSEP_EST_FAULT_GRAD_INITIAL[ VSEP_EST_FAULT_TXD_MESSAGE_CTRL ];
	VSEP_EST_Fault_Txd[ VSEP_EST_FAULT_TXD_MESSAGE_GRADCHECK ] = VSEP_EST_FAULT_GRAD_INITIAL[ VSEP_EST_FAULT_TXD_MESSAGE_GRADCHECK ];
#else
	VSEP_EST_Fault_SYNC_Txd[ VSEP_EST_FAULT_SYNC_TXD_MESSAGE_CTRL_BYTE0 ] = VSEP_EST_FAULT_SYNC_MESSAGE_BYTE_INITIAL[VSEP_EST_FAULT_SYNC_TXD_MESSAGE_CTRL_BYTE0];
	VSEP_EST_Fault_SYNC_Txd[ VSEP_EST_FAULT_SYNC_TXD_MESSAGE_CTRL_BYTE1 ] = VSEP_EST_FAULT_SYNC_MESSAGE_BYTE_INITIAL[VSEP_EST_FAULT_SYNC_TXD_MESSAGE_CTRL_BYTE1];
	VSEP_EST_Fault_SYNC_Txd[ VSEP_EST_FAULT_SYNC_TXD_MESSAGE_SYNC_BYTE2 ] = VSEP_EST_FAULT_SYNC_MESSAGE_BYTE_INITIAL[VSEP_EST_FAULT_SYNC_TXD_MESSAGE_SYNC_BYTE2];
#endif
}


//=============================================================
// VSEP_FAULT_EST_Set_Filter_Time
//=============================================================
void VSEP_FAULT_EST_Set_Filter_Time(IO_Configuration_T in_configuration, VSEP_Gradient_Check_Filter_Time_T in_time)
{
	uint16_t* txd_time = &VSEP_EST_Fault_Txd[ VSEP_EST_FAULT_TXD_MESSAGE_GRADCHECK ];

	*txd_time = VSEP_Msg_IGBT_Set_GRADFILT( *txd_time, in_time );
}

//=============================================================
// VSEP_FAULT_EST_Set_Filter_Time_Immediate
//=============================================================
void VSEP_FAULT_EST_Set_Filter_Time_Immediate(IO_Configuration_T in_configuration, VSEP_Gradient_Check_Filter_Time_T in_time)
{
	VSEP_FAULT_EST_Set_Filter_Time( in_configuration, in_time );
	VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_EST_FAULT );
}

//=============================================================
// VSEP_FAULT_EST_Get_Filter_Time
//=============================================================
VSEP_Gradient_Check_Filter_Time_T VSEP_FAULT_EST_Get_Filter_Time(IO_Configuration_T in_configuration)
{
	uint16_t* txd_time = &VSEP_EST_Fault_Txd[ VSEP_EST_FAULT_TXD_MESSAGE_GRADCHECK ];
	VSEP_Gradient_Check_Filter_Time_T time;

	time = (VSEP_Gradient_Check_Filter_Time_T)VSEP_Msg_IGBT_Get_GRADFILT( *txd_time );

	return ( time );
}

//=============================================================================
// VSEP_FAULT_EST_Set_Threshold
//=============================================================================
void VSEP_FAULT_EST_Set_Threshold(
   IO_Configuration_T in_configuration,
   VSEP_Gradient_Check_Threshold_T in_threshold)
{
   uint16_t *txd_threshold = &VSEP_EST_Fault_Txd[ VSEP_EST_FAULT_TXD_MESSAGE_GRADCHECK ];

   *txd_threshold = VSEP_Msg_IGBT_Set_GRADTHR( *txd_threshold, in_threshold );
}

//=============================================================================
// VSEP_FAULT_EST_Set_Threshold_Immediate
//=============================================================================
void VSEP_FAULT_EST_Set_Threshold_Immediate(IO_Configuration_T in_configuration,
   VSEP_Gradient_Check_Threshold_T in_threshold)
{
	VSEP_FAULT_EST_Set_Threshold( in_configuration, in_threshold );
	VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_EST_FAULT);
}

//=============================================================
// VSEP_FAULT_EST_Get_Threshold
//=============================================================
VSEP_Gradient_Check_Threshold_T VSEP_FAULT_EST_Get_Threshold(IO_Configuration_T in_configuration)
{
	uint16_t* txd_threshold = &VSEP_EST_Fault_Txd[ VSEP_EST_FAULT_TXD_MESSAGE_GRADCHECK ];
	VSEP_Gradient_Check_Threshold_T threshold;

	threshold = (VSEP_Gradient_Check_Threshold_T)VSEP_Msg_IGBT_Get_GRADTHR( *txd_threshold );

	return ( threshold );
}

//=============================================================
// VSEP_EST_SYNC_Interface
//=============================================================
void VSEP_EST_Fault_SYNC_Interface(EST_Select_Cylinder_T curent_spark_cylinder)
{
	//****************************************
	interrupt_state_t     irq_state;
	uint8_t               index, transmint_length;
	uint8_t               index_transmint,index_receive,x;
	VSEP_Fault_PCH_T      vsep_pch_fault;
	static uint8_t        CurrentEstLine;
	static uint8_t        PreviousEstLine;
	static uint8_t        Cylinder_numbers;

	//here determine which channel should be tested for which type fault
	//for the first time, how to determine the PreviousEstCylinder?
	PreviousEstLine = CurrentEstLine;

	if( CeWasteEST == GetSPRK_SparkDeliveryMode() ){
		Cylinder_numbers = CRANK_CONFIG_NUMBER_OF_CYLINDERS/2;
		if (curent_spark_cylinder == EST_SELECT_CYLINDER_A || curent_spark_cylinder == EST_SELECT_CYLINDER_C) {
			CurrentEstLine = 0;
		} else {
			CurrentEstLine = 1;
		}
	} else {
		CurrentEstLine = curent_spark_cylinder;
		Cylinder_numbers = CRANK_CONFIG_NUMBER_OF_CYLINDERS;
	}

	VSEP_EST_Fault_SYNC_Txd[VSEP_EST_FAULT_SYNC_TXD_MESSAGE_SYNC_BYTE2] = \
			VSEP_Msg_EST_Set_EST1CEN_BYTE_FORMAT(VSEP_EST_Fault_SYNC_Txd[VSEP_EST_FAULT_SYNC_TXD_MESSAGE_SYNC_BYTE2],true);
	VSEP_EST_Fault_SYNC_Txd[VSEP_EST_FAULT_SYNC_TXD_MESSAGE_SYNC_BYTE2] = \
			VSEP_Msg_EST_Set_EST1C_BYTE_FORMAT(VSEP_EST_Fault_SYNC_Txd[VSEP_EST_FAULT_SYNC_TXD_MESSAGE_SYNC_BYTE2],curent_spark_cylinder);


	//**************************************************
	irq_state = Get_Interrupt_State();
	Disable_Interrupts();

	/*SPI Clock Phase Bit ¡ª This bit is used to select the SPI clock format. In master mode, a change of this bit will
	abort a transmission in progress and force the SPI system into idle state.
	0 Sampling of data occurs at odd edges (1,3,5,...) of the SCK clock.
	1 Sampling of data occurs at even edges (2,4,6,...) of the SCK clock.*/

	for ( index_transmint = 0,index_receive =0; index_transmint <VSEP_EST_FAULT_SYNC_TXD_MESSAGE_MAX_BYTE; index_transmint++,index_receive++)
	{
		// for byte transfer algorithem       
		VSEP_EST_Fault_SYNC_Rxd[index_receive] =  \
						(uint8_t)DSPI_B_Exchange_Data1(VSEP_CHIP_SELECT,
												VSEP_CTAR_SELECT,
												DSPI_CTAR_FMSZ_8,
												&VSEP_EST_Fault_SYNC_Txd[index_transmint],
												(index_transmint == (VSEP_EST_FAULT_SYNC_TXD_MESSAGE_MAX_BYTE-1)? true:false));
	}

	Set_Interrupt_State(irq_state) ;
	//****************************************

	for (x=0;x<Cylinder_numbers;x++) {
		vsep_pch_fault = (VSEP_Fault_PCH_T)Extract_Bits( VSEP_EST_Fault_SYNC_Rxd[VSEP_EST_FAULT_SYNC_RXD_MESSAGE_FLT_BYTE2],
									x*2, BIT_2 );

	#ifdef  VSEP_CALIBRATION_ENABLE
		 if((x != PreviousEstLine  )||(!KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_IGBTCFG))
	#else
		 if((x != PreviousEstLine  )||(!VSEP_EST_Select_Get_Drive_Mode( VSEP_0_EST_SELECT_SETUP_INIT )))
	#endif
		{
			/* test open fault */
			VSEP_Fault_Log[ x ] |= FAULT_TESTED_OPEN_CIRCUIT_SET; 
			if (VSEP_FAULT_PCH_OPEN_FAULT == vsep_pch_fault) {
				VSEP_Fault_Log[ x ] |= FAULT_OCCURED_OPEN_CIRCUIT_SET;
			}
			/* test short to gound fault */
			VSEP_Fault_Log[ x ] |= FAULT_TESTED_SHORT_TO_GROUND_SET; 
			if(VSEP_FAULT_PCH_SHORT_TO_GROUND_FAULT == vsep_pch_fault){
				VSEP_Fault_Log[ x ] |= FAULT_OCCURED_SHORT_TO_GROUND_SET; 
			}
		}
		/* test short to battery fault */
		VSEP_Fault_Log[ x ]  |= FAULT_TESTED_SHORT_TO_BATTERY_SET; 
		if(VSEP_FAULT_PCH_SHORT_TO_BATTERY_FAULT == vsep_pch_fault){
			VSEP_Fault_Log[ x ] |= FAULT_OCCURED_SHORT_TO_BATTERY_SET; 
			if ((VSEP_Fault_Counter[x] < (KsVSEP_Diagnostic_Counter_Thd))&&(EST_Diagnostic_7p8ms[x])) {
				// increment channel fault counter per 7.8ms
				EST_Diagnostic_7p8ms[x] = false;
				VSEP_Fault_Counter[x] = VSEP_Fault_Counter[x] + VSEP_CHANNEL_FAULT_COUNTER_INCREMENT_STEP;
			}
		}
	}
}

void VSEP_Fault_Log_Clear(void)
{
	uint8_t channel;

	for(channel = VSEP_CHANNEL_PCH_01_FLT_LVL_1; channel <= VSEP_CHANNEL_PCH_30_FLT_LVL_7; channel++){
		//initialize the FaultLog, clear all fault flags
		VSEP_Fault_Log[ channel ] = 0x0;
		VSEP_Fault_Log[ channel ] = FAULT_Set_Supported_Open_Circuit( VSEP_Fault_Log[ channel ], true );
		VSEP_Fault_Log[ channel ] = FAULT_Set_Supported_Short_To_Battery( VSEP_Fault_Log[ channel ], true );
		VSEP_Fault_Log[ channel ] = FAULT_Set_Supported_Short_To_Ground( VSEP_Fault_Log[ channel ], true );
	}
}

//=============================================================
// VSEP_Fault_Initialize
// initializing the channel controled by spi
//=============================================================
void VSEP_Fault_Initialize(void)
{
	uint8_t channel; 
	VSEP_PWM_Channel_T pwm_channel;
	uint32_t base_frequency_hz,in_on_time_count,in_period_count;

	VSEP_DIS_ON_OFF_state = 0x00000000;
	//Channel_Protect_Enable.Protect_Enable_Struct =  KsVSEP_HW_Protect_Setting;protect all
	Channel_Protect_Enable = 0x7FFFFFFF;

 	for(channel = VSEP_CHANNEL_PCH_01_FLT_LVL_1 ; channel <= VSEP_CHANNEL_PCH_30_FLT_LVL_7;channel++){
		//initialize the FaultLog,
		VSEP_Fault_Log[ channel ] = FAULT_Set_Supported_Open_Circuit( VSEP_Fault_Log[ channel ], true );
		VSEP_Fault_Log[ channel ] = FAULT_Set_Supported_Short_To_Battery( VSEP_Fault_Log[ channel ], true );
		VSEP_Fault_Log[ channel ] = FAULT_Set_Supported_Short_To_Ground( VSEP_Fault_Log[ channel ], true );
		//initialize the vsep Spi Discrete(include the VSEP PWM SPI discrete channel), 
		//we did not care about the non-vsep-spi discrete channel
		if(VSEP_PCH_Get_Initial_State(VSEP_Fault_Logging[channel].fault_configuration)){
			VSEP_DIS_ON_OFF_state |=  ((Mask32(VSEP_Get_Channel(VSEP_Fault_Logging[channel].fault_configuration),1)));
		}
		//initialize the vsep spi PWM
		//we did not care about the non-vsep-spi discrete channel and VSEP PWM SPI discrete channel 
		pwm_channel = ( channel < VSEP_CHANNEL_MPIO_1 ) ? VSEP_PWM_PCH_CHANNEL_MAP[ channel ] : VSEP_PWM_CHANNEL_MAX;
		if(pwm_channel != VSEP_PWM_CHANNEL_MAX){
			base_frequency_hz = VSEP_PWM_Timer_Get_Base_Frequency_HZ(VSEP_Fault_Logging[channel].fault_configuration);
			in_on_time_count 	= VSEP_Msg_PWM_Get_OnTime(VSEP_PWM_TXD_INITIAL[ pwm_channel ][ VSEP_PWM_TXD_MESSAGE_ONTIME ]); 
			in_period_count 	= VSEP_Msg_PWM_Get_Period(VSEP_PWM_TXD_INITIAL[ pwm_channel ][ VSEP_PWM_TXD_MESSAGE_PERIOD ]); 
 			VSEP_PWM_period_us[channel] = VSEP_ConvertPeriodCountToMicrosecond( in_period_count,base_frequency_hz);

			if (in_on_time_count == in_period_count){
				VSEP_PWM_ontime_us[channel] = VSEP_PWM_period_us [channel];
			} else {
				VSEP_PWM_ontime_us[channel] =  VSEP_ConvertDutyCountToMicrosecond(in_on_time_count, base_frequency_hz);
			}
		}
	}
}


/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 *
 * ----------   -------     ---
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 03/30/09     sjl         mt20u2#304
 * + MT22.1: RSM_CTC_0129_Add ESC integral signal DA output_Rev1_20090227
 *   - Modified VSEP_EST_Fault_SYNC_Interface as a result of revised SPI driver
 * 2.0  mt20u2#203        09/04/17 hdg Added  DISCRETE_OUT_IMMOREQ    *
 * 16.1.1.1.3.1.1.2.1 110128 nz45s2 mt20u2#809 RSM_CTC_0375_add auto start-stop function in MT22.1_Rev0_20101229
\*===========================================================================*/


//=============================================================================
//include files
//=============================================================================
#include "reuse.h"
#include "rqom.h"
#include "hwiocald.h"
#include "dd_siu_hwinfo.h"
#include "dd_crank_interface.h"
#include "io_config_knock.h"
#include "dd_dma_interface.h"
#include "io_config_dma.h"
#include "io_config_siu.h"
#include "io_config_tpu.h"
#include "io_conversion.h"
#include "hal_analog.h"

// for function test
#include "Io_config_vsep.h"
#include "Dd_vsep_discrete.h"
#include "Dd_vsep_pwm.h"



typedef enum KNOCK_Status_Tag {
	KNOCK_Status_Default,
	KNOCK_Status_Stable,
	KNOCK_Status_Win1_On,
	KNOCK_Status_Win1_OFF,
	KNOCK_Status_Win2_ON,
	KNOCK_Status_Win2_OFF
} KNOCK_Status_T;

typedef enum KNOCK_PostStatus_Tag {
	KNOCK_PostStatus_Default,
	KNOCK_PostStatus_LowPass,
	KNOCK_PostStatus_BandPass1,
	KNOCK_PostStatus_BandPass2,
	KNOCK_PostStatus_BandPass3,
	KNOCK_PostStatus_INT1,
	KNOCK_PostStatus_INT2,
	KNOCK_PostStatus_INT3
} KNOCK_PostStatus_T;

//=============================================================================
// Global Variable Definitions
//=============================================================================
uCrank_Angle_T KNOCK_Angle_From_Cylinder_Event_To_TDC;
Crank_Angle_T  KNOCK_Angle_Stable ;
Crank_Angle_T  KNOCK_Window_Begin1;
Crank_Angle_T  KNOCK_Window_End1;
Crank_Angle_T  KNOCK_Window_Begin2;
Crank_Angle_T  KNOCK_Window_End2;
uCrank_Angle_T KNOCK_REF_To_WindowBegin1;
uCrank_Angle_T KNOCK_REF_To_WindowEnd1;
uCrank_Angle_T KNOCK_REF_To_WindowBegin2;
uCrank_Angle_T KNOCK_REF_To_WindowEnd2;
uint32_t       KNOCK_Last_Intensity_Value1[MULTIKNOCK_NUM_FILTERS];
uint32_t       KNOCK_Last_Analog_Conversion1;
uint32_t       KNOCK_Last_Intensity_Value2[MULTIKNOCK_NUM_FILTERS];
uint32_t       KNOCK_Last_Analog_Conversion2;
IO_Callback_T  KNOCK_OS_End_Of_Window_CallBack1;
IO_Callback_T  KNOCK_OS_End_Of_Window_CallBack2;
uint16_t       KNOCK_DSP_Process_Count_Wingate_Stauts;
uint16_t       KNOCK_DSP_Process_Count_Winagte_PostStatus;
bool           KNOCK_VGA_Gain_High;
uint32_t       KNOCK_Window_Length;

//=============================================================================
// Static Variable Definitions
//=============================================================================
volatile KNOCK_Status_T  KNOCK_Status;
volatile KNOCK_PostStatus_T  KNOCK_PostStatus;
volatile uint32_t       KNOCK_Stable_Time;
volatile uint32_t       KNOCK_Stable_Time_Winagte_PostStatus;
volatile uint32_t       KNOCK_Ref_to_WindowBegin1_time;
volatile uint32_t       KNOCK_Ref_to_WindowBegin2_time;
volatile uint32_t       KNOCK_WindowBegin1_to_WindowEnd1_time;
volatile uint32_t       KNOCK_WindowEnd1_to_WindowBegin2_time;
volatile uint32_t       KNOCK_WindowBegin2_to_WindowEnd2_time;
volatile uint32_t       KNOCK_WindowBegin1_to_WindowEnd2_time;
//volatile uint32_t       KNOCK_DSP_Process_time;

volatile uint8_t        KNOCK_Number_Of_Cylinders;
volatile uint8_t        KNOCK_center_frequency1;
volatile uint8_t        KNOCK_center_frequency2;
volatile uint8_t        KNOCK_center_frequency3;
volatile uCrank_Count_T KNOCK_Tooth_Count_From_Cylinder_Event_To_TDC;
volatile uCrank_Count_T KNOCK_Teeth_Per_Cylinder_Event;
volatile uCrank_Count_T KNOCK_Tooth_Count_TDC_to_CylEvt;

//=============================================================================
// /------------------------------------------------------------------------
// | Local Function Prototypes
// \------------------------------------------------------------------------
//=============================================================================
uint32_t asm_knock_ABS_INT( int16_t  *LpData, uint32_t num) ;
void asm_Enable_SPE_APU(void);
void OS_KNOCK_CYL_EVENT(void);
void OS_KNOCK_WINGATE_OFF(void) ;
//=============================================================================
//
//=============================================================================
void KNOCK_Perform_Event_Task( void *in_event_condition );

//=============================================================================
// KNOCK_Set_High_Gain
//=============================================================================
void KNOCK_Set_High_Gain( bool  in_high_gain )
{
	KNOCK_VGA_Gain_High = in_high_gain;
}

//=============================================================================
// KNOCK_Get_High_Gain
//=============================================================================
bool KNOCK_Get_High_Gain( void )
{
	return KNOCK_VGA_Gain_High ;
}

//=============================================================================
// KNOCK_Initialize
//=============================================================================
void KNOCK_Reset_Parameters( void )
{
	uint8_t i;

	KNOCK_Window_Begin1 = 0;
	KNOCK_Window_Begin2 = 0;
	KNOCK_Window_End1 = 0;
	KNOCK_Window_End2 = 0;
	KNOCK_Last_Analog_Conversion1 = 0;
	KNOCK_Last_Analog_Conversion2 = 0;

	for (i=0; i<MULTIKNOCK_NUM_FILTERS; i++) {
		KNOCK_Last_Intensity_Value1[i] = 0;
		KNOCK_Last_Intensity_Value2[i] = 0;
	}

	KNOCK_Status = KNOCK_Status_Default;
}

//=============================================================================
// KNOCK_Initialize
//=============================================================================
void KNOCK_Initialize(void)
{
	KNOCK_Number_Of_Cylinders = CRANK_Get_Number_Of_Cylinders();

	KNOCK_Reset_Parameters();
	KNOCK_Angle_From_Cylinder_Event_To_TDC = CRANK_Get_Parameter(CRANK_PARAMETER_ANGLE_FROM_CYLINDER_EVENT_TO_TDC, 0, 0);
	KNOCK_Tooth_Count_From_Cylinder_Event_To_TDC = CRANK_Convert_uCrank_Angle_To_Teeth(KNOCK_Angle_From_Cylinder_Event_To_TDC);
	KNOCK_Teeth_Per_Cylinder_Event  = CRANK_Get_Parameter( CRANK_PARAMETER_VIRTUAL_TEETH_PER_CYLINDER_EVENT, 0, 0 );
	KNOCK_Tooth_Count_TDC_to_CylEvt = KNOCK_Teeth_Per_Cylinder_Event - KNOCK_Tooth_Count_From_Cylinder_Event_To_TDC;

	QADC_Knock_SIU_Init();

	DMA_Initialize_Channel(
		DMA_CHANNEL_QADC_FISR0_RFDF_0,
		DMA_QADC_RFDF_0_Source_Address,
		DMA_QADC_RFDF_0_Second_32Bit,
		DMA_QADC_RFDF_0_Third_32Bit,
		DMA_QADC_RFDF_0_Slast,
		DMA_QADC_RFDF_0_Dest_Address,
		DMA_QADC_RFDF_0_Sixth_32Bit,
		DMA_QADC_RFDF_0_Dlast,
		DMA_QADC_RFDF_0_Eighth_32Bit);

	DMA_Clear_Request(DMA_CHANNEL_QADC_FISR0_RFDF_0);

	asm_Enable_SPE_APU();

	SIU_Knock_Connect_Pin_To_ETPU(true,HAL_RQOME_Wingate_CHANNEL);

	MCD5406_Set_Host_Interrupt_Enable(RQOME_TPU_INDEX, WINGATE_RQOME, true);
}


/* =====================================================================================================================
 * Knoc signal sampling:
 *
 *                                      ----------------------------------------------------------
 * eQADC        ________________________|                                                        |________________
 *
 *
 * DMA               -----------------------------------------------------------------------------
 *              _____|                                                                           |________________
 *
 *                                                              ----------------------------------
 * Wingate      ________________________________________________|                                |________________
 *
 *              ------                 --------------------------                                -----------------
 * eTPU              |_________________|                        |________________________________|
 *
 * time         ---------------------------------------------------------------------------------------------------------------> t
 *                   |                 |                        |                                |
 *             Tce[Cylinder Event]    Tst               Twb[Wingate Begain]            Twe[Wingate End(eTPU ISR)]
 *                                [Start Point(eTPU ISR)]
 *
 *
 * Tce - Cylinder Event (ISR)
 *       tasks: 1. Disconnect eTPU to PIN out (must before task. 2)
 *              2. Configure eTPU to RQOM mode to generate signals at Tst(Array 0), Tsiu(Array 1), Twb and Twe
 *                 - Use TCR2 abs angle for Twb/Twe accdoring to calibration
 *                 - USR TCR1 time base for Tst = Twb - t(knoc stable time)
 *                 - Issue tpu ISR at Tst
 * Tst - Knoc signal smapling start point, Trigger eQADC to sample KONC signal(Rising edge)
 *       eTPU ISR tasks: 1. connect eTPU to PIN out
 * Twb - Enbale wingate, no ISR required, handled by micro code
 * Twe - Disable wingate, handled by micro code, Trigger eQADC to stop sampling of KNOC signal(Rising edge)
 *       eTPU ISR task: 1. perpare to KNOC process
 *                      2. Disconnect wingate from etpu
 *
 * ===================================================================================================================== */
uint32_t stable_start,stable_end;
uint32_t time_per_tooth_cnt;
uint32_t tcr1_current, tcr2_current;

void KNOCK_Cylinder_Event_MultiKnock(void)
{
	Crank_Coherent_Edge_Time_And_Count_T   coherent_count_time;
	uint32_t                               previous_tooth_time;
//function test code
VSEP_DISCRETE_Toggle_Immediate_State(VSEP_PO_VVT2_CH);

	if(KNOCK_Window_Begin2>=0) {
		KNOCK_REF_To_WindowBegin2 =  KNOCK_Angle_From_Cylinder_Event_To_TDC + KNOCK_Window_Begin2;
	} else {
		KNOCK_REF_To_WindowBegin2 =  KNOCK_Angle_From_Cylinder_Event_To_TDC - abs(KNOCK_Window_Begin2);
	}

	KNOCK_REF_To_WindowEnd2 = KNOCK_REF_To_WindowBegin2 + KNOCK_Window_End2;

	time_per_tooth_cnt =  CRANK_Get_Tooth_Period();

	KNOCK_Ref_to_WindowBegin2_time = (KNOCK_REF_To_WindowBegin2*time_per_tooth_cnt) >> (uCRANK_ANGLE_PRECISION);

	KNOCK_WindowBegin2_to_WindowEnd2_time = abs(KNOCK_Window_End2) * time_per_tooth_cnt >> (uCRANK_ANGLE_PRECISION);

	if( (KNOCK_WindowBegin2_to_WindowEnd2_time>(Knock_IIR_ADC_Sample_Time*Knock_Time_Scale)*Knock_Min_Wingate_Cnt)
	    &&(KNOCK_WindowBegin2_to_WindowEnd2_time<=(Knock_Max_Winggate_Time*Knock_Time_Scale))
	  )
	{

		if((KNOCK_Status == KNOCK_Status_Default) || (KNOCK_Status_Win2_ON == KNOCK_Status)) {
			// calculate the sitable stable time
			if(KNOCK_Ref_to_WindowBegin2_time>Knock_Stable_Time*Knock_Time_Scale) {
				KNOCK_Stable_Time = Knock_Stable_Time*Knock_Time_Scale;
			} else if(KNOCK_Ref_to_WindowBegin2_time<Knock_Stable_Min_Time*Knock_Time_Scale) {
				KNOCK_Stable_Time = Knock_Stable_Min_Time*Knock_Time_Scale;
				KNOCK_Ref_to_WindowBegin2_time = KNOCK_Stable_Time;
			} else {
				// -  KNOCK_Ref_to_WindowBegin2_time%(16); //(KNOCK_Ref_to_WindowBegin2_time/400)*400;
				KNOCK_Stable_Time = KNOCK_Ref_to_WindowBegin2_time&0xfff0;
			}

			KNOCK_Status = KNOCK_Status_Stable;

			SIU_Knock_Connect_Pin_To_ETPU(false,HAL_RQOME_Wingate_CHANNEL);

			DMA_Initialize_Channel(
			        DMA_CHANNEL_QADC_FISR0_RFDF_0,
			        DMA_QADC_RFDF_0_Source_Address,
			        DMA_QADC_RFDF_0_Second_32Bit,
			        DMA_QADC_RFDF_0_Third_32Bit,
			        DMA_QADC_RFDF_0_Slast,
			        DMA_QADC_RFDF_0_Dest_Address,
			        DMA_QADC_RFDF_0_Sixth_32Bit,
			        DMA_QADC_RFDF_0_Dlast,
			        DMA_QADC_RFDF_0_Eighth_32Bit);

			DMA_Enable_Request(DMA_CHANNEL_QADC_FISR0_RFDF_0);

			QADC_Push_Knock_Command(KNOCK_Get_High_Gain());

			//============================================================RQOM=====================================
			tcr2_current = TPU_TIMER_Get_Value(RQOME_TPU_INDEX, TPU_TCR2_TIME_BASE);
			tcr1_current = TPU_TIMER_Get_Value(RQOME_TPU_INDEX, TPU_TCR1_TIME_BASE);

			// set array size = 1
			MCD5406_Set_Parameter(RQOME_TPU_INDEX, WINGATE_RQOME, RQOM_PARAMETER_ARRAY_SIZE, 2 );
			//==================Set Start Event====================
			// set start event time
			MCD5406_Set_Parameter(RQOME_TPU_INDEX, WINGATE_RQOME, RQOM_PARAMETER_START_EVENT, tcr1_current );

			// set init pin state = 1
			MCD5406_Set_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,RQOM_FLAG_START_EVENT_ACTIVE_STATE,true);
			// set use start event = true
			MCD5406_Set_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,RQOM_FLAG_USE_START_EVENT,true);
			// set use end event
			MCD5406_Set_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,RQOM_FLAG_USE_END_EVENT,false);

			MCD5406_Initialize_Channel(RQOME_TPU_INDEX, &TPU, WINGATE_RQOME,NULL);

			//==================Set array 0====================
			// set array 0 time
			MCD5406_Set_Array_Data(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,0,((KNOCK_Ref_to_WindowBegin2_time-KNOCK_Stable_Time)&UINT24_MAX));
			// array 0 use TCR2
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,0,RQOM_ARRAY_FLAG_MATCH_ALTERNATE_TIMER,false);
			// array 0 use abs time
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,0,RQOM_ARRAY_FLAG_ABSOLUTE_MATCH_EVENT,false);
			// array 0 pin state 0
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,0,RQOM_ARRAY_FLAG_ACTIVE_STATE,false);
			// array 0 store time
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,0,RQOM_ARRAY_FLAG_STORE_TIMER,false);
			// array 0 request interrupt
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,0,RQOM_ARRAY_FLAG_REQUEST_INTERRUPT,true);

			//==================Set array 1====================
			// set array 0 time
			MCD5406_Set_Array_Data(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,1,(((tcr2_current&0xFFFF00) + KNOCK_REF_To_WindowBegin2)&UINT24_MAX));
			// array 1 use TCR2
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,1,RQOM_ARRAY_FLAG_MATCH_ALTERNATE_TIMER,true);
			// array 1 use abs time
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,1,RQOM_ARRAY_FLAG_ABSOLUTE_MATCH_EVENT,true);
			// array 1 pin state 0
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,1,RQOM_ARRAY_FLAG_ACTIVE_STATE,true);

			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,1,RQOM_ARRAY_FLAG_REQUEST_INTERRUPT,false);
			// array 1 store time
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,1,RQOM_ARRAY_FLAG_STORE_TIMER,true);

			//==================Set array 2====================
			// set array 0 time
			MCD5406_Set_Array_Data(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,2,(((tcr2_current&0xFFFF00) + KNOCK_REF_To_WindowEnd2)&UINT24_MAX));
			// array 1 use TCR2
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,2,RQOM_ARRAY_FLAG_MATCH_ALTERNATE_TIMER,true);
			// array 1 use abs time
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,2,RQOM_ARRAY_FLAG_ABSOLUTE_MATCH_EVENT,true);
			// array 1 pin state 0
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,2,RQOM_ARRAY_FLAG_ACTIVE_STATE,false);

			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,2,RQOM_ARRAY_FLAG_END_SEQUENCE,true);
			// array 2 request interrupt
			MCD5406_Set_Array_Flag(RQOME_TPU_INDEX, WINGATE_RQOME,NULL,2,RQOM_ARRAY_FLAG_REQUEST_INTERRUPT,true);

			MCD5406_Request(RQOME_TPU_INDEX, WINGATE_RQOME);

			//============================================================RQOM=====================================
			stable_start = tcr1_current + (KNOCK_Ref_to_WindowBegin2_time-KNOCK_Stable_Time);
		}
	}
}

//=============================================================================
// KNOCK_Initialize
//=============================================================================
uint32_t knk_test_cnt1;
void KNOCK_ETPU_Interrupt_Service(void)
{
	TPU_INTERRUPT_Clear(RQOME_TPU_INDEX, WINGATE_RQOME);

// HAL_GPIO_SET_VGIS2_Enable(true);
	if (KNOCK_Status_Stable == KNOCK_Status) {
		SIU_Knock_Connect_Pin_To_ETPU(true,HAL_RQOME_Wingate_CHANNEL);
		KNOCK_Status = KNOCK_Status_Win2_ON;

	} else if (KNOCK_Status_Win2_ON == KNOCK_Status) { // Winagte is on, turn off wingate, prepare to process data
		KNOCK_Status = KNOCK_Status_Default;
		knk_test_cnt1++;
		if (!DMA_Get_Channel_Running_Status(DMA_CHANNEL_QADC_FISR0_RFDF_0)) {
			KNOCK_DSP_Process_Count_Wingate_Stauts = DEC_FILT_A_DMA_RESULT_BUFF_SIZE;
		} else {
			// dsp process count                              BITER                              CITER
			KNOCK_DSP_Process_Count_Wingate_Stauts =
			        DMA_Get_Channel_Biter(DMA_CHANNEL_QADC_FISR0_RFDF_0) - DMA_Get_Channel_Citer(DMA_CHANNEL_QADC_FISR0_RFDF_0) ;

			if (KNOCK_DSP_Process_Count_Wingate_Stauts > DEC_FILT_A_DMA_RESULT_BUFF_SIZE) {
				KNOCK_DSP_Process_Count_Wingate_Stauts = DEC_FILT_A_DMA_RESULT_BUFF_SIZE;
			}
		}

		KNOCK_DSP_Process_Count_Wingate_Stauts =   (KNOCK_Stable_Time +  KNOCK_WindowBegin2_to_WindowEnd2_time)/(Knock_IIR_ADC_Sample_Time*Knock_Time_Scale);
		DMA_Clear_Request(DMA_CHANNEL_QADC_FISR0_RFDF_0);


		KNOCK_Last_Analog_Conversion2 = abs(DEC_FILT_A_Result_Buffer_A[KNOCK_DSP_Process_Count_Wingate_Stauts-1]);


		/*stable_start = RQOM_Get_Array_Data(&MTSA_PWM_WINGATE,NULL,0);*/
		stable_end = MCD5406_Get_Array_Data(RQOME_TPU_INDEX, WINGATE_RQOME, NULL,1);

		if (stable_start < stable_end ) {
			KNOCK_Stable_Time_Winagte_PostStatus = stable_end - stable_start;
		} else {
			KNOCK_Stable_Time_Winagte_PostStatus = 0xFFFFFF - stable_start + stable_end ;
		}

		if (KNOCK_Stable_Time_Winagte_PostStatus > KNOCK_Stable_Time) {
			KNOCK_Stable_Time_Winagte_PostStatus = KNOCK_Stable_Time;
		}


		// if((KNOCK_PostStatus == KNOCK_PostStatus_Default)&&KNOCK_DSP_Process_Count_Wingate_Stauts >= DEC_FILT_A_DMA_PREFILL_SIZE)
		if(KNOCK_DSP_Process_Count_Wingate_Stauts >= DEC_FILT_A_DMA_PREFILL_SIZE) {
			KNOCK_DSP_Process_Count_Winagte_PostStatus = KNOCK_DSP_Process_Count_Wingate_Stauts ;
			KNOCK_PostStatus = KNOCK_PostStatus_LowPass;

			DEC_FILTER_MCR_SETUP(DSP_LOW_PASS_FILTER_IIR_COEFF,
			                     DECFILT_MCR_LOWPASS, DEC_FILT_A_Result_Buffer_A);
			DEC_FILTER_DMA_SETUP_LOWPASS();
			DEC_FILTER_INOUTPUT_DMA_ENABLE();
		}
	}
}

//=============================================================================
// DMA_DECFIL_DRAIN_BUF_A_Transfer_Complete
//=============================================================================
void  DMA_DECFIL_DRAIN_BUF_A_Transfer_Complete(void )
{
// HAL_GPIO_SET_VGIS1_Enable(true);

	if(CPU_Info==CPU_LCI) {
		DMA_Clear_MAJ_Pending_INT(DMA_CHANNEL_DECFIL_DRAIN_BUF_A);
	} else {
		DMA_Clear_MAJ_Pending_INT(DMA_CHANNEL_DECFIL_DRAIN_BUF);
	}

	switch ( KNOCK_PostStatus ) {
	case KNOCK_PostStatus_LowPass:

		KNOCK_PostStatus =  KNOCK_PostStatus_BandPass1;

		DEC_FILTER_MCR_SETUP( DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF1,
		                      DECFILT_MCR_BANDPASS, DEC_FILT_A_Result_Buffer_B);
		DEC_FILTER_DMA_SETUP_BANDPASS( );
		DEC_FILTER_INOUTPUT_DMA_ENABLE( );

		break ;

	case KNOCK_PostStatus_BandPass1:

		KNOCK_PostStatus =  KNOCK_PostStatus_BandPass2;

		DEC_FILTER_MCR_SETUP( DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF2,
		                      DECFILT_MCR_BANDPASS, DEC_FILT_A_Result_Buffer_B);

		DEC_FILTER_INOUTPUT_DMA_ENABLE( );

		break ;

	case KNOCK_PostStatus_BandPass2:

		KNOCK_PostStatus =  KNOCK_PostStatus_BandPass3;

		DEC_FILTER_MCR_SETUP( DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF3,
		                      DECFILT_MCR_BANDPASS, DEC_FILT_A_Result_Buffer_B);

		DEC_FILTER_INOUTPUT_DMA_ENABLE();


		break ;

	case KNOCK_PostStatus_BandPass3:

		KNOCK_PostStatus = KNOCK_PostStatus_INT1;

		// IO_INTERRUPT_Set_Enable( &MTSA_INTC_SWI_1, true);
		//INTC_INTERRUPT_Set_SW1_Interrupt(true);
		INTC_INTERRUPT_Set_Enable(INTC_CHANNEL_SOFTWARE_CH1_CH, true);
		DEC_FILTER_STOP_DSP( );
		break ;

	default :
		//do nothing
		break ;
	}
//HAL_GPIO_SET_VGIS1_Enable(false);
}

//=============================================================================
// OS_Callback_Manager
//=============================================================================
void SWI_Knock_INT( void )
{
	uint32_t interrupt_state;
	uint32_t   test_count;
	INTC_INTERRUPT_Clear_Pending(INTC_CHANNEL_SOFTWARE_CH1_CH);

	if ( (KNOCK_DSP_Process_Count_Winagte_PostStatus/DEC_FILT_A_DMA_LOWPASS_DECRATE- DEC_FILT_A_DMA_PREFILL_SIZE-1) >
	     (KNOCK_Stable_Time_Winagte_PostStatus/(DEC_FILT_A_DMA_LOWPASS_DECRATE*20))
	   ) {
		test_count = ((KNOCK_DSP_Process_Count_Winagte_PostStatus/DEC_FILT_A_DMA_LOWPASS_DECRATE- DEC_FILT_A_DMA_PREFILL_SIZE-1)
		              -KNOCK_Stable_Time_Winagte_PostStatus/(DEC_FILT_A_DMA_LOWPASS_DECRATE*20))*2;//  75 = KNOCK_Stable_Time/4
	} else {
		// exception handle, prevent reset from asm_knock_ABS_INT, this function can't take big test_count as para or it will reset uP
		test_count = 0;
	}

	asm_Enable_SPE_APU();

	KNOCK_Last_Intensity_Value2[0]  =  asm_knock_ABS_INT( &DEC_FILT_A_Result_Buffer_B[
	                DEC_FILT_A_DMA_RESULT_BUFF_SIZE/DEC_FILT_A_DMA_LOWPASS_DECRATE
	                +KNOCK_Stable_Time_Winagte_PostStatus/(DEC_FILT_A_DMA_LOWPASS_DECRATE
	                                *Knock_Time_Scale*Knock_IIR_ADC_Sample_Time) +1],test_count);
	//76 = KNOCK_Stable_Time/4 +1

	KNOCK_PostStatus = KNOCK_PostStatus_INT2;
	KNOCK_Last_Intensity_Value2[1]  =  asm_knock_ABS_INT( &DEC_FILT_A_Result_Buffer_B[
	                DEC_FILT_A_DMA_RESULT_BUFF_SIZE/DEC_FILT_A_DMA_LOWPASS_DECRATE*2
	                +KNOCK_Stable_Time_Winagte_PostStatus/(DEC_FILT_A_DMA_LOWPASS_DECRATE
	                                *Knock_Time_Scale*Knock_IIR_ADC_Sample_Time) +1],test_count);
	//76 = KNOCK_Stable_Time/4 +1

	KNOCK_PostStatus = KNOCK_PostStatus_INT3;
	KNOCK_Last_Intensity_Value2[2]  =  asm_knock_ABS_INT( &DEC_FILT_A_Result_Buffer_B[
	                DEC_FILT_A_DMA_RESULT_BUFF_SIZE/DEC_FILT_A_DMA_LOWPASS_DECRATE*3
	                +KNOCK_Stable_Time_Winagte_PostStatus/(DEC_FILT_A_DMA_LOWPASS_DECRATE
	                                *Knock_Time_Scale*Knock_IIR_ADC_Sample_Time) +1],test_count);
	//76 = KNOCK_Stable_Time/4 +1

	//OS_SCHEDULER_Dispatch_Event( IO_SCHEDULE_APPLICATION_KNOCK_WINDOW_CLOSED_TASK );
	OS_SCHEDULER_KNOCK_WINDOW_CLOSED_Event();

	KNOCK_PostStatus =  KNOCK_PostStatus_Default;
	// IO_DISCRETE_Set_State( &MTSA_D_OUT_PDA, false );
}

//=============================================================================
// KNOCK_Get_Window_Status
//=============================================================================
bool KNOCK_Get_Window_Status( void )
{
	return (((KNOCK_Status == KNOCK_Status_Win2_ON) |(KNOCK_Status == KNOCK_Status_Win2_ON)) ? true : false) ;
}

//=============================================================================
// KNOCK_Get_Last_Analog_Conversion
//=============================================================================
uint16_t KNOCK_Get_MultiLast_Analog_Conversion1( void )
{
	return KNOCK_Last_Analog_Conversion1;
}

uint16_t KNOCK_Get_MultiLast_Analog_Conversion2( void )
{
	return KNOCK_Last_Analog_Conversion2;
}

//=============================================================================
// KNOCK_Set_Center_Frequency
//=============================================================================

void KNOCK_Set_MultiCenter_Frequency1( uint8_t in_center_frequency)
{
	KNOCK_center_frequency1 = in_center_frequency;
}
void KNOCK_Set_MultiCenter_Frequency2( uint8_t in_center_frequency)
{
	KNOCK_center_frequency2 = in_center_frequency;
}
void KNOCK_Set_MultiCenter_Frequency3( uint8_t in_center_frequency)
{
	KNOCK_center_frequency3 = in_center_frequency;
}

//=============================================================================
// KNOCK_Set_Window_Start
//=============================================================================
void KNOCK_Set_MultiWindow_Start1( int32_t angle, uint8_t precision )
{
	KNOCK_Window_Begin1 = CRANK_Convert_To_Crank_Angle(angle, precision);
}

void KNOCK_Set_MultiWindow_Start2( int32_t angle, uint8_t precision )
{
	KNOCK_Window_Begin2 = CRANK_Convert_To_Crank_Angle(angle, precision);
}

void KNOCK_Set_MultiWindow_End1( int32_t angle, uint8_t precision )
{
	KNOCK_Window_End1 = CRANK_Convert_To_Crank_Angle(angle, precision);
}

void KNOCK_Set_MultiWindow_End2( int32_t angle, uint8_t precision )
{
	KNOCK_Window_End2 = CRANK_Convert_To_Crank_Angle(angle, precision);
}

void KNOCK_Get_MultiIntensity_Value1( uint32_t* values )
{
	int i;
	for (i=0; i<MULTIKNOCK_NUM_FILTERS; i++) {
		values[i] = KNOCK_Last_Intensity_Value1[i];
	}
}

void KNOCK_Get_MultiIntensity_Value2( uint32_t* values )
{
	int i;
	for (i=0; i<MULTIKNOCK_NUM_FILTERS; i++) {
		values[i] = KNOCK_Last_Intensity_Value2[i];
	}
}

//=============================================================================
// KNOCK_Get_Window_Closed_Status
//
// @func This function returns the state of the window closed flag
//
// @rdesc none.
//
// @end
//=============================================================================
bool KNOCK_Get_Window_Closed_Status(void)
{
	//KNOCK 1 interface
	return (((KNOCK_Status == KNOCK_Status_Win2_ON) |(KNOCK_Status == KNOCK_Status_Win2_ON)) ? false : true) ;
}

bool KNOCK_Get_Window1_Closed_Status(void)
{
	return ((KNOCK_Status == KNOCK_Status_Win1_On) ? false : true) ;
}

bool KNOCK_Get_Window2_Closed_Status(void)
{
	return ((KNOCK_Status == KNOCK_Status_Win2_ON) ?  false : true) ;
}
//=============================================================================
// KNOCK_Set_Window_Closed_Status
//=============================================================================

void KNOCK_Set_Window1_Closed_Status(
        bool   in_status )
{

}
void KNOCK_Set_Window2_Closed_Status(
        bool   in_status )
{

}

//=============================================================================
// KNOCK_Set_Window_Length
//=============================================================================
void KNOCK_Set_Window_Length(
        uint16_t in_window_length,
        uint8_t  in_time_precision )
{
	KNOCK_Window_Length = IO_Convert_Time_To_Count(
								  in_window_length,
								  CRANK_Get_Parameter(CRANK_PARAMETER_TIME_BASE, 0, 0),
								  in_time_precision,
								  MILLISECOND_RESOLUTION ) & UINT24_MAX;
}

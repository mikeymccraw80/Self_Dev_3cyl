//=============================================================================
// include files
//=============================================================================
#include "HLS.h"
#include "hal_eng.h"
#include "hal_pulse.h"
#include "vehicle_can_cald.h"
#include "io_interface_os.h"


//=============================================================================
// global variable
//=============================================================================
uint8_t Startup_Counter;
bool     First_Syn_Flag;

//=============================================================================
// static variable
//=============================================================================
unsigned char Tooth_Interrupt_Flag;

//=============================================================================
//  IO_Eng_Cyl_Update
//=============================================================================
void IO_Eng_Cyl_Update(void)
{
	LLD_cyl_num  = HAL_Eng_Get_Cyl_Number();
	if (HAL_Eng_Get_CAM_Backup_Flag() == false) {
		crank_sig.engine_rpm = HAL_Eng_Get_Engine_Speed()/2;//rpm scale 0.125 to 0.25(chery)
		crank_sig.segment_time = (HAL_Eng_Get_Engine_Reference_Time()*5)/16;// time base is 4M, convert to 0.8us
	} else {
		crank_sig.engine_rpm = HAL_Eng_Get_CAM1_Engine_Speed()/2;//rpm scale 0.125 to 0.25(chery)
		crank_sig.segment_time = (HAL_Eng_Get_CAM1_Reference_Time()*5)/16;// time base is 4M, convert to 0.8us
	}
	crank_sig.crank_status.B_crank_loss_of_sync =  HAL_Eng_Get_Loss_Of_Sync();
	if (crank_sig.crank_status.B_crank_loss_of_sync || crank_sig.crank_status.B_crank_no_sync) {
		crank_sig.crank_status.B_RefMrk = 0;
	} else {
		crank_sig.crank_status.B_RefMrk = 1;
	}

	if(!First_Syn_Flag) {
		HLS_firstsyn();
	}
}

//=============================================================================
// IO_Eng_Engine_Stall_Reset
//=============================================================================
void  IO_Eng_Engine_Stall_Reset(void)
{
	First_Syn_Flag= 0;
	Startup_Counter = 0;
	Tooth_Interrupt_Flag = 0;

	crank_sig.crank_status.B_crank_stall = ( bitfield16_t )1;
	crank_sig.crank_status.B_crank_sync = ( bitfield16_t )0 ;
	crank_sig.crank_status.B_crank_pre_sync = ( bitfield16_t )0 ;
	crank_sig.engine_rpm =0;
	crank_sig.segment_time = 0xFFFFFFFF;
	if (!Is_IGN_Off()) {
		/* called when the synch is lost/reset */
		HLS_rstsyn();
	}
}


//=============================================================================
// IO_Eng_Engine_Start_Crank
//=============================================================================
void  IO_Eng_Engine_Start_Crank(void)
{
	crank_sig.crank_status.B_crank_no_sync = ( bitfield16_t )0;
	crank_sig.crank_status.B_crank_stall = ( bitfield16_t )0;
	crank_sig.crank_status.B_crank_pre_sync  =( bitfield16_t )1;
}


//=============================================================================
// IO_Eng_Engine_First_Gap
//=============================================================================
void  IO_Eng_Engine_First_Gap(void)
{
	crank_sig.crank_status.B_crank_pre_sync  =( bitfield16_t )0;
	crank_sig.crank_status.B_crank_sync = ( bitfield16_t )1 ;
}

//=============================================================================
// IO_Eng_Engine_Init
//=============================================================================
void  IO_Eng_Engine_Init(void)
{
	crank_sig.crank_status.B_crank_no_sync = ( bitfield16_t )1;
}


//=============================================================================
// IO_Eng_ToothInt
//=============================================================================
void  IO_Eng_ToothInt(void)
{
	//Chery requirement: Update the 32bit system time
	// Set the tooth interrupt flag to avoid the background update the system time
	Tooth_Interrupt_Flag = 1;
	crank_sig.engine_position_tc = HAL_Eng_Get_Engine_Tooth()%60;
	Sys_time = HAL_Eng_Get_Sys_Timer();
	Tooth_time += HAL_Eng_Get_Tooth_Period();
	//Chery requirement: Call the HLS tooth task at every falling edge of crank tooth
	HLS_tooth_interrupt();
}

//=============================================================================
// IO_Eng_Update_System_Time_Background
//=============================================================================
void IO_Eng_Update_System_Time_Background(void)
{
	if ( crank_sig.engine_rpm == 0) {
		Sys_time = HAL_Eng_Get_Sys_Timer();
	}

	if (crank_sig.crank_status.B_crank_pre_sync ) {
		crank_sig.engine_rpm = 400; //100rpm
		crank_sig.segment_time = 300000;//100rpm,300ms
	}

	/* update engine turning flag */
	SetEngineTurning(crank_sig.engine_rpm);

	//TACH output
	if(!K_Can_Meter_TACH_Disable) {
		if(crank_sig.engine_rpm >0) {
			//vsep pwm period scale is 1/64ms, duty scale is 1/32768
			// crank_sig.segment_time is 0.8us, formula is: (segment_time * 0.8 us)/((1/64)ms)
			HAL_Pulse_TACH_Set_Period_Duty((uint32_t)(crank_sig.segment_time*64)/1250, 32768/2 );
		} else {
			//vsep pwm period scale is 1/64ms, duty scale is 1/32768
			// crank_sig.segment_time is 0.8us, formula is: (segment_time * 0.8 us)/((1/64)ms)
			HAL_Pulse_TACH_Set_Period_Duty((uint32_t)(crank_sig.segment_time*64)/1250, 0 );
		}
	}
}


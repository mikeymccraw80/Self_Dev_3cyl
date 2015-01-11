//=============================================================================
// include files
//=============================================================================
#include "hal_fuel.h"
#include "hal_eng.h"
#include "io_config_fuel.h"
#include "io_conversion.h"
#include "io_interface_eng.h"
#include "io_interface_os.h"
#include "HLS.h"
#include "hwiocald.h"
#include "immo.h"

//=============================================================================
// Chery fuel Variable
//=============================================================================
uint16_t Chery_Post_Injection[MAX_INJ_CHANNEL];

//=============================================================================
// Chery fuel Marco define
//=============================================================================
#define Prec_Inj_end_angle_chery                (720/256)

//The macro is used to convert the computer value of chery Injection end engle to engineering value
//Attention! Because prec*256(=720),so to simplify the macro, the prec*256 is replaced by 720
#define Convert_Chery_Inj_angle(value,prec) (uint16_t)(((uint32_t)value * 720)>>8)
#define Convert_Chery_Inj_Width(value,prec) (uint16_t)(((uint32_t)value *(2<<(prec-1)))/1000)


/* local type define */
typedef enum {
	IO_FUEL_CYLINDER_A = 0,
	IO_FUEL_CYLINDER_B,
	IO_FUEL_CYLINDER_C,
	IO_FUEL_CYLINDER_D
} io_fuel_cylinder_t;

//=============================================================================
// IO_Fuel_Syn_Init
//=============================================================================
void  IO_Fuel_Syn_Init(void)
{
	SetHWIO_MinInjectorOffTime(V_MILLISECONDSb(0.25));
}

//=============================================================================
// IO_Fuel_Syn_Update
//=============================================================================
void IO_Fuel_Syn_Update(void)
{
	Crank_Cylinder_T current_cylinder_id;
	T_MILLISECONDSb  PFI_PulseWidth;
	uint32_t         chery_inj_width;
	uint16_t         chery_inj_end_angle;
	uint16_t         chery_inj_end_angle_prev;
	uint16_t         counter;

	current_cylinder_id = HAL_Eng_Get_Cyl_Number();

	if (First_Syn_Flag == false) {
		/*Convert the engineer value of Chery Injection end angle to Delphi engineer value */
		//chery_inj_end_angle = (900 - 720)<<S_CRANK_ANGLE;
		SetHWIO_SequentialFuelMode(false);

		// Chery requirement: Determine which cylinder should be arranged simultaneous injection
		// cylinder A,simultaneous inject cylB,cylC,cylD
		if (current_cylinder_id == IO_FUEL_CYLINDER_A) {
			//enable post injection
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_B);
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_C);
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_D);

			if (ImmoInhibitEngine == false) {
				chery_inj_width = inj_sig[INJ_CHANNEL_A].inj_time;
			} else {
				chery_inj_width = 0;
			}
			PFI_PulseWidth = Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
			PFI_Set_Pulse_Width(INJ_CHANNEL_A, 0,              S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_B, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_C, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_D, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
		} else if (current_cylinder_id == IO_FUEL_CYLINDER_B) {
			//enable post injection
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_A);
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_C);
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_D);

			if (ImmoInhibitEngine == false) {
				chery_inj_width = inj_sig[INJ_CHANNEL_B].inj_time;
			} else {
				chery_inj_width = 0;
			}
			PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
			PFI_Set_Pulse_Width(INJ_CHANNEL_B, 0,              S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_A, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_C, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_D, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
		} else if (current_cylinder_id == IO_FUEL_CYLINDER_C){
			//cylinder C,simultaneous inject cylA,cylB,cylD
			//enable post injection
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_A);
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_B);
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_D);

			if (ImmoInhibitEngine == false) {
				chery_inj_width = inj_sig[INJ_CHANNEL_C].inj_time;
			} else {
				chery_inj_width = 0;
			}
			PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
			PFI_Set_Pulse_Width(INJ_CHANNEL_A, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_B, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_C, 0,              S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_D, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
		} else if (current_cylinder_id == IO_FUEL_CYLINDER_D) {
			//enable post injection
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_A);
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_B);
			PFI_Enable_Trim_Pulses(INJ_CHANNEL_C);

			if (ImmoInhibitEngine == false) {
				chery_inj_width = inj_sig[INJ_CHANNEL_D].inj_time;
			} else {
				chery_inj_width = 0;
			}
			PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
			PFI_Set_Pulse_Width(INJ_CHANNEL_D, 0,              S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_A, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_B, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
			PFI_Set_Pulse_Width(INJ_CHANNEL_C, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
		}

		/*Convert the engineer value of Chery Injection end angle to Delphi engineer value */
		chery_inj_end_angle = (900 - Convert_Chery_Inj_angle(inj_sig[INJ_CHANNEL_A].inj_end_angle,Prec_Inj_end_angle_chery))<<S_CRANK_ANGLE;
		chery_inj_end_angle = chery_inj_end_angle - KfHWIO_phi_BoundaryFraction;
		SetHWIO_FuelInjectorEOIT(chery_inj_end_angle);
		SetHWIO_FuelInjectorTrimEOIT(chery_inj_end_angle);

		if (current_cylinder_id == IO_FUEL_CYLINDER_A) {
			if (ImmoInhibitEngine == false) {
				chery_inj_width =  inj_sig[INJ_CHANNEL_A].inj_time;
			} else {
				chery_inj_width = 0;
			}
			PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
			PFI_Set_Pulse_Width(INJ_CHANNEL_A, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
		} else if (current_cylinder_id == IO_FUEL_CYLINDER_B)  {
			if (ImmoInhibitEngine == false) {
				chery_inj_width =  inj_sig[INJ_CHANNEL_B].inj_time;
			} else {
				chery_inj_width = 0;
			}
			PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
			PFI_Set_Pulse_Width(INJ_CHANNEL_B, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
		} else if (current_cylinder_id == IO_FUEL_CYLINDER_C)  {
			if (ImmoInhibitEngine == false) {
				chery_inj_width =  inj_sig[INJ_CHANNEL_C].inj_time;
			} else {
				chery_inj_width = 0;
			}
			PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
			PFI_Set_Pulse_Width(INJ_CHANNEL_C, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
		} else if (current_cylinder_id == IO_FUEL_CYLINDER_D)  {
			if (ImmoInhibitEngine == false) {
				chery_inj_width =  inj_sig[INJ_CHANNEL_D].inj_time;
			} else {
				chery_inj_width = 0;
			}
			PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
			PFI_Set_Pulse_Width(INJ_CHANNEL_D, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
		}

		PFI_Set_Channel_Update_Enable(current_cylinder_id, true);

		First_Syn_Flag = true;
	} else {
		/*Convert the engineer value of Chery Injection end angle to Delphi engineer value */
		chery_inj_end_angle = (900 - Convert_Chery_Inj_angle(inj_sig[INJ_CHANNEL_A].inj_end_angle,Prec_Inj_end_angle_chery))<<S_CRANK_ANGLE;
		chery_inj_end_angle = chery_inj_end_angle - KfHWIO_phi_BoundaryFraction;
		SetHWIO_FuelInjectorEOIT(chery_inj_end_angle);
		SetHWIO_FuelInjectorTrimEOIT(chery_inj_end_angle);
		//  PFI_Set_Angle( PFI_TRIM_ANGLE, chery_inj_end_angle, 1<<S_CRANK_ANGLE );

		if(current_cylinder_id != INJ_CHANNEL_A) {
			if(inj_sig[INJ_CHANNEL_A].B_post_inj) {
				Chery_Post_Injection[INJ_CHANNEL_A]+=inj_sig[INJ_CHANNEL_A].post_inj_time; 
			 PFI_Enable_Trim_Pulses(INJ_CHANNEL_A);
			}
		} else {
			Chery_Post_Injection[INJ_CHANNEL_A] = 0;
		}

		if((inj_enable.B_inj_A ) && (!Is_IGN_Off()) && (ImmoInhibitEngine == false)) {
			chery_inj_width =  inj_sig[INJ_CHANNEL_A].inj_time+Chery_Post_Injection[INJ_CHANNEL_A];
		} else {
			chery_inj_width = 0;
		}

		inj_sig[INJ_CHANNEL_A].B_post_inj = 0;
		PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
		PFI_Set_Pulse_Width(INJ_CHANNEL_A, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );

		if(current_cylinder_id != INJ_CHANNEL_B) {
			if(inj_sig[INJ_CHANNEL_B].B_post_inj) {
				Chery_Post_Injection[INJ_CHANNEL_B]+=inj_sig[INJ_CHANNEL_B].post_inj_time;
				PFI_Enable_Trim_Pulses(INJ_CHANNEL_B);
			}
		} else {
			Chery_Post_Injection[INJ_CHANNEL_B] = 0;
		}

		if((inj_enable.B_inj_B ) && (!Is_IGN_Off()) && (ImmoInhibitEngine == false)) {
			chery_inj_width =  inj_sig[INJ_CHANNEL_B].inj_time+Chery_Post_Injection[INJ_CHANNEL_B];
		} else {
			chery_inj_width =0;
		}

		inj_sig[INJ_CHANNEL_B].B_post_inj = 0;
		PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
		PFI_Set_Pulse_Width(INJ_CHANNEL_B, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );

		if(current_cylinder_id != INJ_CHANNEL_C) {
			if(inj_sig[INJ_CHANNEL_C].B_post_inj) {
				Chery_Post_Injection[INJ_CHANNEL_C]+=inj_sig[INJ_CHANNEL_C].post_inj_time;
				PFI_Enable_Trim_Pulses(INJ_CHANNEL_C);
			}
		} else {
			Chery_Post_Injection[INJ_CHANNEL_C] = 0;
		}

		if((inj_enable.B_inj_C) && (!Is_IGN_Off()) && (ImmoInhibitEngine == false)) {
			chery_inj_width =  inj_sig[INJ_CHANNEL_C].inj_time+Chery_Post_Injection[INJ_CHANNEL_C];
		} else {
			chery_inj_width =0;
		}

		inj_sig[INJ_CHANNEL_C].B_post_inj = 0;
		PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
		PFI_Set_Pulse_Width(INJ_CHANNEL_C, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );

		if(current_cylinder_id != INJ_CHANNEL_D) {
			if(inj_sig[INJ_CHANNEL_D].B_post_inj) {
				Chery_Post_Injection[INJ_CHANNEL_D]+=inj_sig[INJ_CHANNEL_D].post_inj_time;
				PFI_Enable_Trim_Pulses(INJ_CHANNEL_D);
			}
		} else {
			Chery_Post_Injection[INJ_CHANNEL_D] = 0;
		}

		if((inj_enable.B_inj_D) && (!Is_IGN_Off()) && (ImmoInhibitEngine == false)) {
			chery_inj_width =  inj_sig[INJ_CHANNEL_D].inj_time+Chery_Post_Injection[INJ_CHANNEL_D];
		} else {
			chery_inj_width =0;
		}

		inj_sig[INJ_CHANNEL_D].B_post_inj = 0;
		PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
		PFI_Set_Pulse_Width(INJ_CHANNEL_D, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
	}
	//Clear the flag to tell the HLS that LLD get the parameters
	B_syn_update = false;
}

//=============================================================================
// IO_Fuel_Engine_Stall_Reset
//=============================================================================
void IO_Fuel_Engine_Stall_Reset(void)
{
	SetHWIO_SequentialFuelMode(false);
	Chery_Post_Injection[INJ_CHANNEL_A]=0;
	Chery_Post_Injection[INJ_CHANNEL_B]=0;
	Chery_Post_Injection[INJ_CHANNEL_C]=0;
	Chery_Post_Injection[INJ_CHANNEL_D]=0;

	 //enable post injection
	PFI_Disable_Trim_Pulses(INJ_CHANNEL_A);
	PFI_Disable_Trim_Pulses(INJ_CHANNEL_B);
	PFI_Disable_Trim_Pulses(INJ_CHANNEL_C);
	PFI_Disable_Trim_Pulses(INJ_CHANNEL_D);

	Startup_Counter =0;
}


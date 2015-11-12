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
	uint8_t inj_enable_status[CcSYST_NUM_OF_CYLINDERS-1];
	uint8_t INJ_CHANNEL;
       uint8_t INJ_CHANNEL_number;
	current_cylinder_id = HAL_Eng_Get_Cyl_Number();

		/*Convert the engineer value of Chery Injection end angle to Delphi engineer value */
		/*900(960)=720+cylinder offset */
#if CcSYST_NUM_OF_CYLINDERS == 4		
		chery_inj_end_angle = (900 - Convert_Chery_Inj_angle(inj_sig[INJ_CHANNEL_A].inj_end_angle,Prec_Inj_end_angle_chery))<<S_CRANK_ANGLE;
#elif CcSYST_NUM_OF_CYLINDERS == 3
		chery_inj_end_angle = (960 - Convert_Chery_Inj_angle(inj_sig[INJ_CHANNEL_A].inj_end_angle,Prec_Inj_end_angle_chery))<<S_CRANK_ANGLE;
#endif		
		chery_inj_end_angle = chery_inj_end_angle - KfHWIO_phi_BoundaryFraction;
		SetHWIO_FuelInjectorEOIT(chery_inj_end_angle);
		SetHWIO_FuelInjectorTrimEOIT(chery_inj_end_angle);

	if (First_Syn_Flag == false) {
		SetHWIO_SequentialFuelMode(false);

		for(INJ_CHANNEL=INJ_CHANNEL_A;INJ_CHANNEL<CcSYST_NUM_OF_CYLINDERS;INJ_CHANNEL++){
                if (current_cylinder_id == INJ_CHANNEL) {
                     if (ImmoInhibitEngine == false) {
                        chery_inj_width = inj_sig[INJ_CHANNEL].inj_time;
	              } else {
	                chery_inj_width = 0;
	              }
		PFI_PulseWidth = Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
              for(INJ_CHANNEL_number=INJ_CHANNEL_A;INJ_CHANNEL_number<CcSYST_NUM_OF_CYLINDERS;INJ_CHANNEL_number++){
		PFI_Set_Pulse_Width(INJ_CHANNEL_number, PFI_PulseWidth,              S_MILLISECONDSb, MILLISECOND_RESOLUTION );
              }
             }
          }		
		PFI_Set_Channel_Update_Enable(current_cylinder_id, true);
		First_Syn_Flag = true;
	} else {
		/* set fuel delivery mode to sequential*/
		SetHWIO_SequentialFuelMode(true);


	   inj_enable_status[0]=inj_enable.B_inj_A;
	   inj_enable_status[1]=inj_enable.B_inj_B;
	   inj_enable_status[2]=inj_enable.B_inj_C;
#if CcSYST_NUM_OF_CYLINDERS == 4
	   inj_enable_status[3]=inj_enable.B_inj_D;
#endif
   for(INJ_CHANNEL=INJ_CHANNEL_A;INJ_CHANNEL<CcSYST_NUM_OF_CYLINDERS;INJ_CHANNEL++)
   {
	if(current_cylinder_id != INJ_CHANNEL) {
			if(inj_sig[INJ_CHANNEL].B_post_inj) {
				Chery_Post_Injection[INJ_CHANNEL]+=inj_sig[INJ_CHANNEL].post_inj_time; 
			 PFI_Enable_Trim_Pulses(INJ_CHANNEL);
			}
	} else {
		Chery_Post_Injection[INJ_CHANNEL] = 0;
	}

	if((inj_enable_status[INJ_CHANNEL] ) && (!Is_IGN_Off()) && (ImmoInhibitEngine == false)) {
		chery_inj_width =  inj_sig[INJ_CHANNEL].inj_time+Chery_Post_Injection[INJ_CHANNEL];
	} else {
		chery_inj_width = 0;
	}

	inj_sig[INJ_CHANNEL].B_post_inj = 0;
	PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
	PFI_Set_Pulse_Width(INJ_CHANNEL, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
	PFI_Set_Channel_Update_Enable(INJ_CHANNEL, true);
   }
		
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
#if CcSYST_NUM_OF_CYLINDERS == 4
	Chery_Post_Injection[INJ_CHANNEL_D]=0;
#endif
	 //enable post injection
	PFI_Disable_Trim_Pulses(INJ_CHANNEL_A);
	PFI_Disable_Trim_Pulses(INJ_CHANNEL_B);
	PFI_Disable_Trim_Pulses(INJ_CHANNEL_C);
#if CcSYST_NUM_OF_CYLINDERS == 4
	PFI_Disable_Trim_Pulses(INJ_CHANNEL_D);
#endif
}


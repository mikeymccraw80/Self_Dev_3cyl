
//=============================================================================
// include files
//=============================================================================
#include "hal_fuel.h"
#include "hal_eng.h"
#include"io_config_fuel.h"
#include "io_conversion.h"
#include "io_interface_eng.h"
#include "io_interface_os.h"
#include "HLS.h"


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

//=============================================================================
// IO_Fuel_Syn_Init
//=============================================================================
 void  IO_Fuel_Syn_Init(void) 
{

   SetHWIO_MinInjectorOffTime( V_MILLISECONDSb(0.25) );


   SetHWIO_SimultaneousFuelMode();
     //make sure in sequential mode

    
}
   uint16_t chery_inj_end_angle;


//=============================================================================
// IO_Fuel_Syn_Update
//=============================================================================
void  IO_Fuel_Syn_Update(void)
{
   T_MILLISECONDSb PFI_PulseWidth;
   uint32_t chery_inj_width;
   uint8_t disable_cyl2_cyl4_flag;


    if (First_Syn_Flag == false)
  {

    // Chery requirement: Determine which cylinder should be arranged simultaneous injection 
  //Cam low means physical cylinder 1,simultaneous inject cyl2,cyl3,cyl4 
    if (CAM_Get_Sensor_State(0) == false)
    {
     // Chery requirement: Disable squence injection of cyl2,cyl4 if corresponding simultaneous injection happened 
      disable_cyl2_cyl4_flag = true;
    }
    //Cam high means physical cylinder 4,simultaneous inject cyl1,cyl2,cyl3 
    else
    {
     // Chery requirement: Disable squence injection of cyl1,cyl3 if corresponding simultaneous injection happened 
      disable_cyl2_cyl4_flag = false;
    }

    /* Cam low means physical cylinder 1,simultaneous inject cyl2,cyl3,cyl4 */
    if (disable_cyl2_cyl4_flag == true)
    {
     chery_inj_width =  inj_sig[INJ_CHANNEL_A].inj_time;
     PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
     PFI_Set_Pulse_Width(INJ_CHANNEL_B, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
     PFI_Set_Pulse_Width(INJ_CHANNEL_C, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
     PFI_Set_Pulse_Width(INJ_CHANNEL_D, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
     PFI_Set_Pulse_Width(INJ_CHANNEL_A, 0, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
    }
    /* Cam high means physical cylinder 4,simultaneous inject cyl1,cyl2,cyl3 */
    else
    {
     chery_inj_width =  inj_sig[INJ_CHANNEL_C].inj_time;
     PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
     PFI_Set_Pulse_Width(INJ_CHANNEL_A, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
     PFI_Set_Pulse_Width(INJ_CHANNEL_C, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
     PFI_Set_Pulse_Width(INJ_CHANNEL_B, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
     PFI_Set_Pulse_Width(INJ_CHANNEL_D, 0, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
    }
    PerfmHWIO_SimultaneousFuelDelivery();
	First_Syn_Flag = true;
  }


  //Chery requirement: Do not enable the squence injection until the first two HLS_Syn finished, 
 // if corresponding simultaneous injection happened 
  if ( Startup_Counter < (PFI_MAX_CYLINDERS/2) )
  { 

    if(Startup_Counter ==1)
     {
     SetHWIO_SequentialFuelMode(0);
     SetHWIO_PrimePulseComplete();   
     SetHWIO_FuelSqSwitch(false);
   //enable post injection
    PFI_Enable_Trim_Pulses(INJ_CHANNEL_A);
    PFI_Enable_Trim_Pulses(INJ_CHANNEL_B);
    PFI_Enable_Trim_Pulses(INJ_CHANNEL_C);
    PFI_Enable_Trim_Pulses(INJ_CHANNEL_D);
    }
	
     Startup_Counter++;
	 
    if ( disable_cyl2_cyl4_flag )
    {
      inj_sig[INJ_CHANNEL_C].inj_time = 0;
      inj_sig[INJ_CHANNEL_D].inj_time = 0;
    }
    else
    {
      inj_sig[INJ_CHANNEL_A].inj_time = 0;
      inj_sig[INJ_CHANNEL_B].inj_time = 0;
    }
	
	inj_sig[INJ_CHANNEL_A].B_post_inj = 0;
	inj_sig[INJ_CHANNEL_B].B_post_inj = 0;
      inj_sig[INJ_CHANNEL_C].B_post_inj = 0;
      inj_sig[INJ_CHANNEL_D].B_post_inj = 0;
  }
   
 //SetHWIO_FuelSqSwitch(true);
  /*Convert the engineer value of Chery Injection end angle to Delphi engineer value */
  chery_inj_end_angle = (720- Convert_Chery_Inj_angle(inj_sig[INJ_CHANNEL_A].inj_end_angle,Prec_Inj_end_angle_chery))<<S_CRANK_ANGLE ;
  SetHWIO_FuelInjectorEOIT(  chery_inj_end_angle );
  SetHWIO_FuelInjectorTrimEOIT(  chery_inj_end_angle );
//  PFI_Set_Angle( PFI_TRIM_ANGLE, chery_inj_end_angle, 1<<S_CRANK_ANGLE );


   if(CRANK_Get_Cylinder_ID() != INJ_CHANNEL_A)
   {
     if(inj_sig[INJ_CHANNEL_A].B_post_inj)
     {
      Chery_Post_Injection[INJ_CHANNEL_A]+=inj_sig[INJ_CHANNEL_A].post_inj_time;
	  
     	}
    }
   else
   {
    Chery_Post_Injection[INJ_CHANNEL_A] = 0;
   }

   if((inj_enable.B_inj_A )&&(!Is_IGN_Off()))
   {
    chery_inj_width =  inj_sig[INJ_CHANNEL_A].inj_time+Chery_Post_Injection[INJ_CHANNEL_A]; 
   }
   else
   {
     chery_inj_width =0;
   }	 

     inj_sig[INJ_CHANNEL_A].B_post_inj = 0;
     PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
     PFI_Set_Pulse_Width(INJ_CHANNEL_A, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );

 // EnableHWIO_FuelInjector(0);

   if(CRANK_Get_Cylinder_ID() != INJ_CHANNEL_B)
   {
     if(inj_sig[INJ_CHANNEL_B].B_post_inj)
     {
      Chery_Post_Injection[INJ_CHANNEL_B]+=inj_sig[INJ_CHANNEL_B].post_inj_time;
	  
     	}
    }
   else
   {
    Chery_Post_Injection[INJ_CHANNEL_B] = 0;
   }

   if((inj_enable.B_inj_B)&&(!Is_IGN_Off()))
   {
    chery_inj_width =  inj_sig[INJ_CHANNEL_B].inj_time+Chery_Post_Injection[INJ_CHANNEL_B]; 
   }
   else
   {
     chery_inj_width =0;
   }	 

     inj_sig[INJ_CHANNEL_B].B_post_inj = 0;
	
     PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
     PFI_Set_Pulse_Width(INJ_CHANNEL_B, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );

//EnableHWIO_FuelInjector(1);

   if(CRANK_Get_Cylinder_ID() != INJ_CHANNEL_C)
   {
     if(inj_sig[INJ_CHANNEL_C].B_post_inj)
     {
      Chery_Post_Injection[INJ_CHANNEL_C]+=inj_sig[INJ_CHANNEL_C].post_inj_time;
	  
     	}
    }
   else
   {
    Chery_Post_Injection[INJ_CHANNEL_C] = 0;
   }

   if((inj_enable.B_inj_C)&&(!Is_IGN_Off()))
   {
    chery_inj_width =  inj_sig[INJ_CHANNEL_C].inj_time+Chery_Post_Injection[INJ_CHANNEL_C]; 
   }
   else
   {
     chery_inj_width =0;
   }	 

     inj_sig[INJ_CHANNEL_C].B_post_inj = 0;
     PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
     PFI_Set_Pulse_Width(INJ_CHANNEL_C, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
 
 
//EnableHWIO_FuelInjector(2);
	
   if(CRANK_Get_Cylinder_ID() != INJ_CHANNEL_D)
   {
     if(inj_sig[INJ_CHANNEL_D].B_post_inj)
     {
      Chery_Post_Injection[INJ_CHANNEL_D]+=inj_sig[INJ_CHANNEL_D].post_inj_time;
	  
     	}
    }
   else
   {
    Chery_Post_Injection[INJ_CHANNEL_D] = 0;
   }

   if((inj_enable.B_inj_D)&&(!Is_IGN_Off()))
   {
    chery_inj_width =  inj_sig[INJ_CHANNEL_D].inj_time+Chery_Post_Injection[INJ_CHANNEL_D]; 
   }
   else
   {
     chery_inj_width =0;
   }	 

     inj_sig[INJ_CHANNEL_D].B_post_inj = 0;
	 
     PFI_PulseWidth =Convert_Chery_Inj_Width(chery_inj_width,S_MILLISECONDSb);
     PFI_Set_Pulse_Width(3, PFI_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );	

  //Clear the flag to tell the HLS that LLD get the parameters 
  B_syn_update = false; 
 

   //SetHWIO_FuelSqSwitch(false);
}

//=============================================================================
// IO_Fuel_Engine_Stall_Reset
//=============================================================================
 void  IO_Fuel_Engine_Stall_Reset(void) 
{

   SetHWIO_SimultaneousFuelMode();
   ClrHWIO_PrimePulseComplete();
   Chery_Post_Injection[INJ_CHANNEL_A]=0;
   Chery_Post_Injection[INJ_CHANNEL_B]=0;
   Chery_Post_Injection[INJ_CHANNEL_C]=0;
   Chery_Post_Injection[INJ_CHANNEL_D]=0;	 

    
}


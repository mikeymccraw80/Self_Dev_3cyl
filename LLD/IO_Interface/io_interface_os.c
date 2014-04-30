//=============================================================================
// include files
//=============================================================================
#include "HLS.h"
#include "io_interface_os.h"
#include "hal_os.h"
#include "hal_ucram.h"

//=============================================================================
// define value
//=============================================================================
#define MIN_RPM_CHERY       (80)//80 is the computer variable 
                                                    //the precision is 1/4
#define Onehour_CNT    (3600)//count with 1s step



 
//NV_ram
#pragma section DATA " " ".nc_nvram"
bool B_SW_Pwf;
bool B_after_run_end_abnormal;
#pragma section DATA " " ".bss"

bool VsCAN_CHERY_EMS_ID_Disable_keyoff500ms;
//=============================================================================
// global variable
//=============================================================================
unsigned int IgnitionOffTimeVar;
bool    B_HLS_afterrun;
unsigned int   Pwr_Afruncnt;
//=============================================================================
// extern variable
//=============================================================================
//The address of these variables are the size numbers because these variables 
// are calculated by the linker
extern char HWIO_HLSBSS_START[];
extern uint16_t HWIO_HLSBSS_SIZE;
/**********************************************************************/
/*** Initialize the HLS Crank and Cam Status as the requirement required    ***/
/**********************************************************************/
INLINE void Init_HLS_Crank_Cam_Status(void)
{
    /* Initilize the Chery flag bit */
    crank_sig.crank_status.B_crank_failed = ( bitfield8_t )false;
    crank_sig.crank_status.B_crank_loss_of_sync = ( bitfield8_t )false;
    crank_sig.crank_status.B_crank_limp_home = ( bitfield8_t )false;
    crank_sig.crank_status.B_crank_no_sync = ( bitfield16_t )true ;
    crank_sig.crank_status.B_crank_pre_sync = ( bitfield16_t )false ;
    crank_sig.crank_status.B_crank_stall= ( bitfield16_t )false ;
    crank_sig.crank_status.B_crank_sync = ( bitfield16_t )false;
    crank_sig.crank_status.B_RefMrk = ( bitfield8_t )false;
    /* Initilize the Cam parameters */
    cam1_sig.edge_count = 0;
    cam1_sig.period = 0xFFFFFFFF;
    cam2_sig.edge_count = 0;
    cam2_sig.period = 0xFFFFFFFF;
}
//=============================================================================
// IO_OS_Get_Shutdown
//=============================================================================
  bool IO_OS_Get_Shutdown(void)
{ 
  //If HLS_afterrun run too long(e.x. 1hour), power down 
  return ((sys_cmd.B_after_run_end) || (B_after_run_end_abnormal));       
}


//=============================================================================
// IO_OS_Power_Status_Init
//=============================================================================
 void  IO_OS_Power_Status_Init(void) 
{
  if(HAL_OS_Get_Battery_Remove())
  {
       sys_status.B_Pwf = true;

  } 
  else
  {
       /* Restore Nvm saved during last keycyle (last keycyle has already been a fully powerdown) from EEPROM */
           /* Chery requirement: tell HLS last HLS_afterrun() is running too long */
       if (true == B_after_run_end_abnormal)
       {
         sys_status.B_after_run_end_abnormal = true;
         B_after_run_end_abnormal = false;
	
       }
       
       /* Chery requirement: emulate bad power down by HLS command */
       if (true == B_SW_Pwf)
       {
         sys_status.B_Pwf = true;
       }
       if (true == HAL_uncleard_ram.data[NCRAM_REPROGRAM_FLAG])
       {
         sys_status.B_Pwf = true;
         HAL_uncleard_ram.data[NCRAM_REPROGRAM_FLAG] = false;
       }
  } 

}

//=============================================================================
// IO_OS_Powerdown_Callback
//=============================================================================
void IO_OS_Powerdown_Callback(void)
{
    B_SW_Pwf = sys_cmd.B_SW_Pwf;
}

//=============================================================================
// IO_OS_PowerFail_Flag
//=============================================================================
bool IO_OS_PowerFail_Flag(void)
{
    return B_SW_Pwf;
}

//=============================================================================
// IO_OS_BackGround_1ms_Status_Check
//=============================================================================
void  IO_OS_BackGround_1ms_Status_Check(void) 
{
	/* HLS power down logic */
	if (Is_IGN_Off()) {
		IgnitionOffTimeVar=(IgnitionOffTimeVar<UINT16_MAX)? (IgnitionOffTimeVar+1) : UINT16_MAX;
		HLS_afterrun();
		B_HLS_afterrun = true;
		/* Key off and rpm = 0,reset the no sync flag */
		if((crank_sig.engine_rpm < MIN_RPM_CHERY) && (crank_sig.crank_status.B_crank_stall == (bitfield16_t)true)) {
			/* Initilize the Chery flag bit */
			crank_sig.crank_status.B_crank_no_sync = ( bitfield16_t )true ;
		}
	} else {
		IgnitionOffTimeVar = 0;
	}

	/* Doing the software reset as the chery requirement */
	if ((B_HLS_afterrun == true) && 
		(!Is_IGN_Off()) &&
		(crank_sig.engine_rpm < MIN_RPM_CHERY) &&
		(B_KeyOn == true))
	{           
		/* Stop the all task containers */
		Disable_Interrupts( );
		/* called when the synch is lost/reset */
		HLS_rstsyn(); 
		/* Chery requirement: Reset the correspoding flags */
		Init_HLS_Crank_Cam_Status();
		/* Chery requirement: Clear the power fail flag if fast key off/key on */
		sys_status.B_Pwf = false;
		/* Chery requirement: Clear all the Chery HLS non-initialized variables */
		// HLS_Clear_Variables();
		/* clear uninitialized data				*/
		if (&HWIO_HLSBSS_SIZE) {
			Clear_Longs(&HWIO_HLSBSS_START[0],(((uint16_t)(&HWIO_HLSBSS_SIZE)+3)/4));
		}
		/* Call the chery initialize functions */
		HLS_ini();
		HLS_inisyn();
		HLS_ini2();                      
		/* Clear the flag */
		B_HLS_afterrun = false;
		/* turn on interrupts */
		Enable_Interrupts();
	}

	/*chery can requirement:stop communciation after key off 500ms*/
	if(IgnitionOffTimeVar > 49) {
		VsCAN_CHERY_EMS_ID_Disable_keyoff500ms = true;
	} else {
		VsCAN_CHERY_EMS_ID_Disable_keyoff500ms = false;
	}
}

//=============================================================================
// IO_OS_OneSecond_Task
//=============================================================================
 void IO_OS_OneSecond_Task(void)
{
  if (Is_IGN_Off())
   {
      /*B_ after_run_end_abnormal is TRUE, meaning that HLS_afterrun() is running too long (more than an hour), and LLD is
      to force ECU to shut down after necessary work.*/
     if((Pwr_Afruncnt == Onehour_CNT)&&( !sys_cmd.B_after_run_end))
     {	
        B_after_run_end_abnormal = true;
      }
  	
     /* wait for one hour if ignition off and no shuntdown command*/
      if(Pwr_Afruncnt<Onehour_CNT)
      {
        Pwr_Afruncnt++;
      }	
  }
  else
  {
    Pwr_Afruncnt = 0;
  }

}

//=============================================================================
// IO_OS_Perform_Reset_Task
//=============================================================================
void IO_OS_Perform_Reset_Task(void)
{
	if (sys_cmd.B_ResetEtsm) {
		Disable_Interrupts();
		sys_cmd.B_ResetEtsm = 0;
		while (true) {};
	}
}

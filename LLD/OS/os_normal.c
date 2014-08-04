
//=============================================================================
// include files
//=============================================================================
#include "dd_swt_interface.h"
#include "io_config_swt.h"
#include "inst_config.h"
#include "os_type.h"
#include "dd_stm_interface.h"
#include "dd_sswt.h"

//=============================================================================
//  define
//=============================================================================


#pragma section SECTION_PF_KKSUM address=0x00160000
#pragma use_section SECTION_PF_KKSUM PF_KKSUM
const uint16_t PF_KKSUM = 0x6D27;
#pragma section

#pragma section SECTION_APP_PRESENCE_PATTERN address=0x0017FFFE
#pragma use_section SECTION_APP_PRESENCE_PATTERN APP_PRESENCE_PATTERN
const uint16_t APP_PRESENCE_PATTERN = APP_CAL_PRESENCE_PATTERN;
#pragma section

#pragma section SECTION_CAL_PRESENCE_PATTERN address=0x0003FFFE;
#pragma use_section SECTION_CAL_PRESENCE_PATTERN CAL_PRESENCE_PATTERN
const uint16_t CAL_PRESENCE_PATTERN = APP_CAL_PRESENCE_PATTERN;
#pragma section

#pragma section SECTION_CALID_INAPP address=0x0017FFFC
#pragma use_section SECTION_CALID_INAPP CAL_FORMID_INAPP
const uint16_t CAL_FORMID_INAPP  = Cw_CalFORM_ID;
#pragma section

#pragma section SECTION_CALID_INCAL address=0x0003FFFC
#pragma use_section SECTION_CALID_INCAL CAL_FORMID_INCAL
const uint16_t CAL_FORMID_INCAL = Cw_CalFORM_ID;
#pragma section

//=============================================================================
// function define
//=============================================================================
void OS_Startup_Hook(void);
void MngOSTK_1msTasks(void);
void MngOSTK_5msTasks(void);
void MngOSTK_10msTasks(void);
void MngOSTK_100msTasks(void);
void OS_Free_Time_Tasks_Hook(void);
void OS_Powerdown_Callback(void);
//=============================================================================
// Local variable
//=============================================================================
static uint8_t  Normal_10ms_CNT;

/* record loop flag overflow counter */
static uint16_t LOOP_OF_CNT_ARRAY[4];

//=============================================================================
// StartOS_Task_Normal
//=============================================================================
void StartOS_Task_Normal(void)
{
	union SPR_TSRVAL tsr_temp;

	OS_Startup_Hook();
	/* init throughput related data */
	Init_InitThroughputData();

	/* Set watchdog timeout to 62ms during normal operation */
	SWT_Set_Timeout_Value(SWT_TIMEOUT_VALUE_NORMAL) ;
	SWT_Service_WatchDog();

	/* this is core watchdog */
	hwi_init_watchdog(HWI_WATCHDOG_ENABLE);
	hwi_kick_watchdog_position(SSWT_EXPIRATION_TIME_26MS);
	hwi_kick_wdg_local();

	/* turn on interrupts and start real os */
	Enable_Interrupts();

	/* do until application indicates shutdown */
	while (!HAL_OS_Get_Shutdown()) {
		/* os background 1ms schedule */
		if (RTI_Flags.bf.TimeFor1ms == 1) {
			Enter_OSThroughputMeasure(CeOSTK_SEG_1msLOOP);
			RTI_Flags.bf.TimeFor1ms = 0x00;
			MngOSTK_1msTasks();
			/* detect overflow event, and record it */
			if (RTI_Flags.bf.TimeFor1ms == 1) {
				RTI_Flags.bf.OverFlowFor1ms = 1;
				LOOP_OF_CNT_ARRAY[CeOSTK_SEG_1msLOOP] ++;
				/* need not to make compension schedule for 1ms */
				RTI_Flags.bf.TimeFor1ms = 0x00;
			}
			Leave_OSThroughputMeasure(CeOSTK_SEG_1msLOOP);
		}

		/* os background 2ms schedule */
		if (RTI_Flags.bf.TimeFor2ms == 1) {
			Enter_OSThroughputMeasure(CeOSTK_SEG_2msLOOP);
			RTI_Flags.bf.TimeFor2ms = 0x00;
			MngOSTK_2msTasks();
			/* detect overflow event, and record it */
			if (RTI_Flags.bf.TimeFor2ms == 1) {
				RTI_Flags.bf.OverFlowFor2ms = 1;
				LOOP_OF_CNT_ARRAY[CeOSTK_SEG_2msLOOP] ++;
				/* need not to make compension schedule for 2ms */
				RTI_Flags.bf.TimeFor2ms = 0x00;
			}
			Leave_OSThroughputMeasure(CeOSTK_SEG_2msLOOP);
		}

		/* os background 5ms schedule */
		if (RTI_Flags.bf.TimeFor5ms == 1) {
			Enter_OSThroughputMeasure(CeOSTK_SEG_5msLOOP);
			RTI_Flags.bf.TimeFor5ms = 0x00;
			MngOSTK_5msTasks();
			/* detect overflow event, and record it */
			if (RTI_Flags.bf.TimeFor5ms == 1) {
				RTI_Flags.bf.OverFlowFor5ms = 1;
				LOOP_OF_CNT_ARRAY[CeOSTK_SEG_5msLOOP] ++;
			}
			Leave_OSThroughputMeasure(CeOSTK_SEG_5msLOOP);
		}

		/* os background 10ms schedule */
		if (RTI_Flags.bf.TimeFor10ms == 1) {
			Enter_OSThroughputMeasure(CeOSTK_SEG_10msLOOP);
			RTI_Flags.bf.TimeFor10ms = 0x00;
			MngOSTK_10msTasks();
			Normal_10ms_CNT++;
			/* detect overflow event, and record it */
			if (RTI_Flags.bf.TimeFor10ms == 1) {
				RTI_Flags.bf.OverFlowFor10ms = 1;
				LOOP_OF_CNT_ARRAY[CeOSTK_SEG_10msLOOP] ++;
			}
			Leave_OSThroughputMeasure(CeOSTK_SEG_10msLOOP);
		}

		/* os background 100ms schedule */
		if (Normal_10ms_CNT == 10) {
			Enter_OSThroughputMeasure(CeOSTK_SEG_100msLOOP);
			MngOSTK_100msTasks();
			Normal_10ms_CNT = 0;
			Leave_OSThroughputMeasure(CeOSTK_SEG_100msLOOP);
		}

		OS_Free_Time_Tasks_Hook();
	}

	//Turn off power supply and return to OSEK
	/* disable interrupts */
	Disable_Interrupts();

	// Set watchdog timeout to 62ms during normal operation
	SWT_Set_Timeout_Value(SWT_TIMEOUT_VALUE_INIT) ;
	SWT_Service_WatchDog();

	OS_Powerdown_Callback();
}



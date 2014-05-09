//=============================================================================
// include files
//=============================================================================
#include "dd_pit_interface.h"
#include "os_type.h"
#include "dd_stm.h"

//=============================================================================
// local variables
//=============================================================================
static uint32_t OS_RTI_1ms_Count;
RtiFlagsType RTI_Flags;

//=============================================================================
// private variables for os throughput measurement
//=============================================================================
static LOOP_THROUGHPUT_T VaOSTK_ThruPutData[NUMBER_OF_CeOSTK_SEG];
static bool VbOSTK_ThruPutData_FirstTime[NUMBER_OF_CeOSTK_SEG];


//=============================================================================
// local functions
//=============================================================================
 void OS_TimeBasedTask1ms(void) ;
 void OS_TimeBasedTask2ms(void) ;
 void OS_TimeBasedTask5ms(void) ;
 void OS_TimeBasedTask10ms(void);


//=============================================================================
// OS_RTI_1ms_INT, this the time schedule reference
//=============================================================================
void OS_RTI_1ms_INT(void)
{
	uint32_t  cs;

	cs = Enter_Critical_Section();
	PIT_INTERRUPT_Clear_Pending(PIT_CHANNEL_RTI);

	OS_RTI_1ms_Count = (OS_RTI_1ms_Count >= 10)? 1 : OS_RTI_1ms_Count++;

	/* 1ms task reference */
	RTI_Flags.bf.TimeFor1ms = 1;
	Enter_OSThroughputMeasure(CeOSTK_SEG_1msTIMEBASE);
	OS_TimeBasedTask1ms();
	Leave_OSThroughputMeasure(CeOSTK_SEG_1msTIMEBASE);

	/* 2ms task reference */
	if (OS_RTI_1ms_Count & 0x01) {
		Enter_OSThroughputMeasure(CeOSTK_SEG_2msTIMEBASE);
		RTI_Flags.bf.TimeFor2ms = 1;
		OS_TimeBasedTask2ms();
		Leave_OSThroughputMeasure(CeOSTK_SEG_2msTIMEBASE);
	}

	/* 5ms task reference */
	if ((OS_RTI_1ms_Count % 5) == 0) {
		Enter_OSThroughputMeasure(CeOSTK_SEG_5msTIMEBASE);
		RTI_Flags.bf.TimeFor5ms = 1;
		OS_TimeBasedTask5ms();
		Leave_OSThroughputMeasure(CeOSTK_SEG_5msTIMEBASE);
	}

	/* 10ms task reference */
	if ((OS_RTI_1ms_Count % 10) == 0) {
		Enter_OSThroughputMeasure(CeOSTK_SEG_10msTIMEBASE);
		RTI_Flags.bf.TimeFor10ms = 1;
		OS_TimeBasedTask10ms();
		Leave_OSThroughputMeasure(CeOSTK_SEG_10msTIMEBASE);
	}
	Leave_Critical_Section(cs);
}

/*===========================================================================*\
 * Inline Functions
\*===========================================================================*/
void Init_InitThroughputData(void)
{
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_1msLOOP] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_2msLOOP] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_5msLOOP] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_10msLOOP] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_100msLOOP] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_1msTIMEBASE] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_2msTIMEBASE] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_5msTIMEBASE] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_10msTIMEBASE] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_CYLINDER_EVENT] = true;
}


void Enter_OSThroughputMeasure(OSTK_SEG_T index)
{
	VaOSTK_ThruPutData[index].t_EnterTime = (uint32_t)(STM.CNT);
}

void Leave_OSThroughputMeasure(OSTK_SEG_T index)
{
	VaOSTK_ThruPutData[index].t_LeaveTime = (uint32_t)(STM.CNT);
	VaOSTK_ThruPutData[index].t_CurrExecTime = \
		VaOSTK_ThruPutData[index].t_LeaveTime - VaOSTK_ThruPutData[index].t_EnterTime;
	if ( VbOSTK_ThruPutData_FirstTime[index] ) {
		VbOSTK_ThruPutData_FirstTime[index] = false;
		VaOSTK_ThruPutData[index].t_AvgExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
		VaOSTK_ThruPutData[index].t_MaxExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
		VaOSTK_ThruPutData[index].t_MinExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
	} else {
		if ( VaOSTK_ThruPutData[index].t_CurrExecTime < VaOSTK_ThruPutData[index].t_MinExecTime ) {
			/* find minimum value */
			VaOSTK_ThruPutData[index].t_MinExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
		} else if ( VaOSTK_ThruPutData[index].t_CurrExecTime > VaOSTK_ThruPutData[index].t_MaxExecTime ) {
			/* find maximum value */
			VaOSTK_ThruPutData[index].t_MaxExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
		} else {
			// nothing to do
		}
	}

	if ( VaOSTK_ThruPutData[index].t_AvgExecTime < VaOSTK_ThruPutData[index].t_CurrExecTime ) {
		VaOSTK_ThruPutData[index].t_AvgExecTime += 
			(VaOSTK_ThruPutData[index].t_CurrExecTime-VaOSTK_ThruPutData[index].t_AvgExecTime) >> TIMEMEASURE_PARAMETER ;
	} else {
		VaOSTK_ThruPutData[index].t_AvgExecTime -= 
			(VaOSTK_ThruPutData[index].t_AvgExecTime-VaOSTK_ThruPutData[index].t_CurrExecTime) >> TIMEMEASURE_PARAMETER ;
	}
}




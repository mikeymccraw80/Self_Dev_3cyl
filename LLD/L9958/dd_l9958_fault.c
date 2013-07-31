//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//=============================================================================

#include "dd_l9958_fault.h"
#include "dd_l9958_txd.h"
#include "dd_l9958_rxd.h"
#include "dd_l9958.h"
#include "io_config_l9958.h"

#define L9958_HWDIAG_STATUS (L9958_Rxd.Value)

Fault_Log_T L9958_Fault_Log;

//=============================================================================
// L9958_FAULT_Initialize_Device
//=============================================================================
void L9958_FAULT_Initialize_Device(void)
{
	L9958_Fault_Log = L9958_FAULT_LOG_INITIAL;
}

//=============================================================================
// L9958_FAULT_Get_Device_Fault
//=============================================================================
bool L9958_FAULT_Get_Device_Fault(void)
{
	bool fault_state;

	fault_state = FAULT_Get_Occured_Open_Circuit(L9958_Fault_Log)     ||
				  FAULT_Get_Occured_Short_To_Battery(L9958_Fault_Log) ||
				  FAULT_Get_Occured_Short_To_Ground(L9958_Fault_Log)  ||
				  FAULT_Get_Occured_Thermal(L9958_Fault_Log)          ||
				  FAULT_Get_Occured_Voltage_Regulation(L9958_Fault_Log);

	return fault_state;
}

//=============================================================================
// L9958_Get_Fault_Status
//=============================================================================
L9958_Fault_Status_T L9958_Get_Fault_Status(void)
{
	return L9958_Msg_Get_Fault_Status(L9958_HWDIAG_STATUS);  
}

//=============================================================================
// L9958_FAULT_Clear_Device_Fault
//=============================================================================
void L9958_FAULT_Clear_Device_Fault(void)
{
	L9958_FAULT_Initialize_Device();
}


//=============================================================================
// L9958_FAULT_Diagnose_Fault, called os 10ms loop
// move L9958_Rxd => L9958_Fault_Log
//=============================================================================
#define L9958_MAX_DIAGTIMER (50) // 10ms * 50 = 500ms
void L9958_FAULT_Diagnose_Update(void)
{
    static int diag_cnt = 0;
    diag_cnt ++;
    if (diag_cnt >= L9958_MAX_DIAGTIMER) {
        L9958_FAULT_Initialize_Device();
        diag_cnt = 0;
    }

    /* get the fault reg value from l9958, and then pick up information to Fault_log*/
    L9958_Diag_Rst_Disable_Set(L9958_DIAG_RST_DISABLE_FALSE);
    L9958_SPI_Immediate_Transfer();

    if(L9958_Msg_Get_Temp_Warning(L9958_HWDIAG_STATUS) || L9958_Msg_Get_OverTemp_Shutdown (L9958_HWDIAG_STATUS))
    {
        L9958_Fault_Log |= FAULT_Set_Occured_Thermal(L9958_Fault_Log, true);
    }

    if(L9958_Msg_Get_OL_OFF(L9958_HWDIAG_STATUS) || L9958_Msg_Get_OL_ON (L9958_HWDIAG_STATUS) )
    {
        L9958_Fault_Log |= FAULT_Set_Occured_Open_Circuit(L9958_Fault_Log, true);
    }

    if(L9958_Msg_Get_Vdd_OverVolt(L9958_HWDIAG_STATUS) || L9958_Msg_Get_VS_UnderVolt(L9958_HWDIAG_STATUS))
    {
        L9958_Fault_Log |= FAULT_Set_Occured_Voltage_Regulation(L9958_Fault_Log, true);
    }

    L9958_Fault_Log |= FAULT_Set_Occured_Short_To_Battery(L9958_Fault_Log, L9958_Msg_Get_Short_to_BAT_in_OFF(L9958_HWDIAG_STATUS));
    L9958_Fault_Log |= FAULT_Set_Occured_Short_To_Ground(L9958_Fault_Log, L9958_Msg_Get_Short_to_GND_in_OFF(L9958_HWDIAG_STATUS));
}

//=============================================================================
// L9958_FAULT_Get_HWDiag_Status, called by other module.
// Return, the real diagnose information of l9958 device
//=============================================================================
uint16_t L9958_FAULT_Get_HWDiag_Status(void)
{
    return L9958_HWDIAG_STATUS;
}

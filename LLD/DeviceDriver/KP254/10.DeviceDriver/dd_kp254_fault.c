#include "dd_kp254_fault.h"
//=============================================================================
//KP254_FAULT_Clear_Device_Fault
//=============================================================================
void KP254_FAULT_Clear_Device_Fault(
   IO_Configuration_T in_configuration )
{
    KP254_Index_T  index  = KP254_Get_Device_Index( in_configuration );
    KP254_Message_T in_kp254_message = KP254_Get_Message(in_configuration);
    
    //clear fault buffer
    KP254_DIAG_Rxd[index] = 0;
    KP254_Msg_Set_Reset_Strategy(KP254_Trigger_DIAG_Txd[index], KP254_RESET_FAILURES);
    KP254_SPI_Immediate_Transfer(in_configuration, in_kp254_message);
}

//=============================================================================
//KP254_FAULT_Get_Device_Fault
//=============================================================================
bool KP254_FAULT_Get_Device_Fault(
   IO_Configuration_T in_configuration )
{
    KP254_Index_T   index     = KP254_Get_Device_Index( in_configuration );

    //check if any of the fault occured bit is set in the fault log buffer 
    return (NO_ERROR == KP254_Fault_Log[index]) ? false : true;
}

//=============================================================================
//KP254_FAULT_Diagnose_Device_Fault
//=============================================================================
void KP254_FAULT_Diagnose_Device_Fault(
   IO_Configuration_T in_configuration)
{
    KP254_Message_T in_kp254_message = KP254_Get_Message(in_configuration);
    KP254_Index_T   index     = KP254_Get_Device_Index( in_configuration );

    KP254_Msg_Set_Reset_Strategy(KP254_Trigger_DIAG_Txd[index], KP254_DONT_RESET_FAILURES);
    KP254_SPI_Immediate_Transfer(in_configuration, in_kp254_message);
    KP254_SPI_Immediate_Transfer(in_configuration, in_kp254_message);
    KP254_Fault_Log[index] = KP254_Get_Rxd_Diagnosis(KP254_DIAG_Rxd[index]);
}

//=============================================================================
//KP254_FAULT_Get_Device_Fault_Type
//=============================================================================
KP254_FAULT_T KP254_FAULT_Get_Device_Fault_Type(
   IO_Configuration_T in_configuration)
{
    KP254_Index_T   index     = KP254_Get_Device_Index( in_configuration );
    return (KP254_FAULT_T)KP254_Fault_Log[index];
}

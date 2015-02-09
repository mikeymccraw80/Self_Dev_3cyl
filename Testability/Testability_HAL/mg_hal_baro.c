#include "mg_hal_config.h"
#include "mg_hal_fault.h"
#include "dd_kp254.h"
/*=============================================================================
 * mg_Baro_Get_ID
 * @func  get BARO identifier
 * @parm  none
 * @rdesc identifier 
 *===========================================================================*/
uint16_t mg_HAL_Baro_Get_ID(void)
{
    return KP254_Get_Identifier(MG_MTSA_CONFIG_KP254_ACQ_ID);
}

/*=============================================================================
 * mg_Baro_Get_Diagnostic
 * @func  get BARO fault
 * @parm  none
 * @rdesc identifier 
 *===========================================================================*/
uint8_t mg_HAL_Baro_Get_Diagnostic(void)
{
    mg_HAL_BARO_Fault_Clear();
    mg_HAL_BARO_Fault_Read();
    return mg_HAL_BARO_Fault_Get(0);
}

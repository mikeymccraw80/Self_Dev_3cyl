#if 0
#include "mg_config.h"
#include "mg_hal_config.h"
#include "mg_hal_discrete.h"
#ifdef __MG_C2MIO_USED
#include "dd_c2mio.h"
#endif
#ifdef __MG_VSEP_USED
#include "dd_vsep.h"
#include "dd_vsep_soh.h"
#endif
#include "hal_ucram.h "

/*=============================================================================
 * mg_HAL_SOH_Get_Challenge
 * @func  get SOH challenge value
 * @parm  none
 * @rdesc challenge value 
 *===========================================================================*/
uint32_t mg_HAL_SOH_Get_Challenge(void)
{
#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
    return C2MIO_SOH_Get_Challenge(C2MIO_Set_Device_Index( 0, C2MIO_INDEX_0 ));
#endif
#ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
    return VSEP_SOH_Get_Challenge(VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ));
#endif
}

/*=============================================================================
 * mg_HAL_SOH_Calculate_Response
 * @func  calculate SOH response value
 * @parm  challenge value
 * @rdesc response value 
 *===========================================================================*/
uint32_t mg_HAL_SOH_Calculate_Response(uint32_t challenge)
{
#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
    return C2MIO_SOH_Calculate_Response(challenge);
#endif
#ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
    return VSEP_SOH_Calculate_Response(challenge);
#endif
}

/*=============================================================================
 * mg_HAL_SOH_Set_Response
 * @func  set SOH response value
 * @parm  response value
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_SOH_Set_Response(uint32_t response)
{
#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
    C2MIO_SOH_Set_Response(C2MIO_Set_Device_Index( 0, C2MIO_INDEX_0 ), response);
#endif
#ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
    VSEP_SOH_Set_Response(VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ), response);
#endif
}

/*=============================================================================
 * mg_HAL_Set_SOH_Test_Flag
 * @func  set SOH test flag
 * @parm  SOH test flag
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_Set_SOH_Test_Flag(uint8_t flag)
{
    HAL_uncleard_ram.data[0] = flag;
}

/*=============================================================================
 * mg_HAL_Get_SOH_Test_Flag
 * @func  get SOH test flag
 * @parm  none
 * @rdesc SOH test flag 
 *===========================================================================*/
uint8_t mg_HAL_Get_SOH_Test_Flag(void)
{
    return HAL_uncleard_ram.data[0];
}

/*=============================================================================
 * mg_HAL_SOH_Init
 * @func  get SOH test flag
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_SOH_Init(bool Is_Disarmed)
{
    uint32_t CHALLENGE_TEMP;
    uint32_t RESPONSE_TEMP;
    /* Select initialization for armed or disarmed according to SOH_test_flag */
    // Disable the IOEN line to enable the IO pins
    mg_HAL_Discrete_Set_GEN_ENABLE(false);
    // Disable FSE pin
    mg_HAL_Discrete_Set_FSE(false);
    // --BEGIN MIO SOH INITIAL SEQUENCE--
    // Send Init message with SOH Disarm requested
    if (Is_Disarmed)
    {
#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
        C2MIO_Set_SOH_Disable_Request_Value(C2MIO_Set_Device_Index( 0, C2MIO_INDEX_0 ), C2MIO_SELECT_SOH_DISABLE_REQUDISARM);
#endif
#ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
        VSEP_Set_SOH_Disable_Request_Value(VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ), VSEP_SELECT_SOH_DISABLE_REQUDISARM);
#endif
    }
    else
    {
#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
        C2MIO_Set_SOH_Disable_Request_Value(C2MIO_Set_Device_Index( 0, C2MIO_INDEX_0 ), C2MIO_SELECT_SOH_DISABLE_NO_REQUEST);
#endif
#ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
        VSEP_Set_SOH_Disable_Request_Value(VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ), VSEP_SELECT_SOH_DISABLE_NO_REQUEST);
#endif
    }

#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
    C2MIO_SPI_Immediate_Transfer( C2MIO_Set_Device_Index( 0, C2MIO_INDEX_0 ), C2MIO_MESSAGE_INIT );
#endif
#ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
    VSEP_SPI_Immediate_Transfer( VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ), VSEP_MESSAGE_INIT );
#endif

    // Enable the IOEN line to enable the IO pins
    mg_HAL_Discrete_Set_GEN_ENABLE(true);
    // Enable FSE pin
    mg_HAL_Discrete_Set_FSE(true);

    // Send SOH C&R Messages first time
    CHALLENGE_TEMP = mg_HAL_SOH_Get_Challenge();
    RESPONSE_TEMP = mg_HAL_SOH_Calculate_Response( CHALLENGE_TEMP );
    mg_HAL_SOH_Set_Response(RESPONSE_TEMP);

#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
    C2MIO_SPI_Immediate_Transfer( C2MIO_Set_Device_Index( 0, C2MIO_INDEX_0 ), C2MIO_MESSAGE_INIT );
#endif
#ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
    VSEP_SPI_Immediate_Transfer( VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ), VSEP_MESSAGE_INIT );
#endif

    // Send SOH C&R Messages a second time
    CHALLENGE_TEMP = mg_HAL_SOH_Get_Challenge();
    RESPONSE_TEMP = mg_HAL_SOH_Calculate_Response( CHALLENGE_TEMP );
    mg_HAL_SOH_Set_Response(RESPONSE_TEMP);
    // --END MIO SOH INITIAL SEQUENCE--
}

#endif

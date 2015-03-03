
#include "mg_config.h"
#ifdef __MG_C2MIO_USED
#include "dd_c2mio.h"
#include "dd_c2mio_fault.h"
#endif
#ifdef __MG_VSEP_USED
#include "dd_vsep.h"
#include "dd_vsep_fault.h"
#endif
#ifdef __MG_C2PS_USED
#include "dd_c2ps.h"
#endif
#ifdef __MG_TLE4471_USED
#endif
#ifdef __MG_PHDL_USED
#include "dd_phd2.h"
#endif
#ifdef __MG_L9958_USED
#include "dd_l9958.h"
#include "dd_l9958_init.h"
#endif
#ifdef __MG_KP254_USED
#include "dd_kp254_fault.h"
#endif
#include "mg_hal_config.h"
#if 0
#ifdef __MG_C2MIO_USED
/*----------------------------------------------------------------------------*/
/*   Definition of C2MIO Channel Maximom                                              */
/*----------------------------------------------------------------------------*/
const uint8_t MG_COMPLEXIO_CHANNEL_MAX = 37;//C2MIO_CHANNEL_MAX;

/*----------------------------------------------------------------------------*/
/*   Definition of C2MIO Fault Value                                              */
/*----------------------------------------------------------------------------*/
const uint8_t MG_COMPLEXIO_FAULT_OPEN = C2MIO_FAULT_PCH_OPEN_FAULT;
const uint8_t MG_COMPLEXIO_FAULT_SHORT_TO_GROUND = C2MIO_FAULT_PCH_SHORT_TO_GROUND_FAULT;
const uint8_t MG_COMPLEXIO_FAULT_SHORT_TO_BATTERY = C2MIO_FAULT_PCH_SHORT_TO_BATTERY_FAULT;
#endif
#ifdef __MG_VSEP_USED
/*----------------------------------------------------------------------------*/
/*   Definition of VSEP Channel Maximom                                              */
/*----------------------------------------------------------------------------*/
const uint8_t MG_COMPLEXIO_CHANNEL_MAX = 30;//VSEP_CHANNEL_MAX;

/*----------------------------------------------------------------------------*/
/*   Definition of VSEP Fault Value                                              */
/*----------------------------------------------------------------------------*/
const uint8_t MG_COMPLEXIO_FAULT_OPEN = VSEP_FAULT_PCH_OPEN_FAULT;
const uint8_t MG_COMPLEXIO_FAULT_SHORT_TO_GROUND = VSEP_FAULT_PCH_SHORT_TO_GROUND_FAULT;
const uint8_t MG_COMPLEXIO_FAULT_SHORT_TO_BATTERY = VSEP_FAULT_PCH_SHORT_TO_BATTERY_FAULT;
#endif



#ifdef __MG_PHDL_USED
/*=============================================================================
 * mg_PHD_Set_Clear_Fault
 * @func  set PHD clear fault flag
 * @parm  PHD clear fault flag
 * @rdesc  none
 *===========================================================================*/
void mg_PHD_Set_Clear_Fault(uint8_t flag)
{
    PHD_Txd[ 0 ] = PHD_Msg_Set_Clear_Fault(PHD_Txd[ 0 ], flag);
}

/*=============================================================================
 * mg_PHD_Set_Auto_LS_Current_Limit_Slew_Time
 * @func  set PHD auto LS current limit slew time flag
 * @parm  PHD auto LS current limit slew time flag
 * @rdesc  none
 *===========================================================================*/
void mg_PHD_Set_Auto_LS_Current_Limit_Slew_Time(uint8_t flag)
{
    PHD_Txd[ 0 ] = PHD_Msg_Set_Auto_LS_Current_Limit_Slew_Time(PHD_Txd[ 0 ], flag);
}

/*=============================================================================
 * mg_PHD_Set_Auto_Thermal_Warning_Current_Limit
 * @func  set PHD auto thermal warning current limit flag
 * @parm  PHD auto thermal warning current limit flag
 * @rdesc  none
 *===========================================================================*/
void mg_PHD_Set_Auto_Thermal_Warning_Current_Limit(uint8_t flag)
{
    PHD_Txd[ 0 ] = PHD_Msg_Set_Auto_Thermal_Warning_Current_Limit(PHD_Txd[ 0 ], flag);
}

/*=============================================================================
 * mg_PHD_Set_Auto_Thermal_Warning_Slew_Time
 * @func  set PHD auto thermal warning slew time flag
 * @parm  PHD auto thermal warning slew time flag
 * @rdesc  none
 *===========================================================================*/
void mg_PHD_Set_Auto_Thermal_Warning_Slew_Time(uint8_t flag)
{
    PHD_Txd[ 0 ] = PHD_Msg_Set_Auto_Thermal_Warning_Slew_Time(PHD_Txd[ 0 ], flag);
}

/*=============================================================================
 * mg_PHD_Set_Low_Side_Current_Limit
 * @func  set PHD low side current limit flag
 * @parm  PHD low side current limit flag
 * @rdesc  none
 *===========================================================================*/
void mg_PHD_Set_Low_Side_Current_Limit(uint8_t data)
{
    PHD_Txd[ 0 ] = PHD_Msg_Set_Low_Side_Current_Limit(PHD_Txd[ 0 ], data);
}

/*=============================================================================
 * mg_PHD_Set_Slew_Time
 * @func  set PHD slew time flag
 * @parm  PHD slew time flag
 * @rdesc  none
 *===========================================================================*/
void mg_PHD_Set_Slew_Time(uint8_t data)
{
    PHD_Txd[ 0 ] = PHD_Msg_Set_Slew_Time(PHD_Txd[ 0 ], data);
}
#endif

#ifdef __MG_L9958_USED
#endif

/*=============================================================================
 * mg_HAL_Fault_ETC_Open_Test_Configure
 * @func  set ETC open fault configure
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_Fault_ETC_Open_Test_Configure(void)
{
#ifdef __MG_PHDL_USED
    mg_PHD_Set_Low_Side_Current_Limit(0x03);
    mg_PHD_Set_Slew_Time(0x00);
    mg_PHD_Set_Auto_LS_Current_Limit_Slew_Time(1);
    mg_PHD_Set_Auto_Thermal_Warning_Current_Limit(1);
    mg_PHD_Set_Auto_Thermal_Warning_Slew_Time(1);
#endif
#ifdef __MG_L9958_USED
    L9958_Diag_Rst_Disable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_DIAG_RST_DISABLE_FLASE);
    L9958_Regulation_Curr_Level_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_CURRENT_LEVEL_8P6);
    L9958_OL_ON_Enable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_OPEN_LOAD_ON_ENABLE);
    L9958_VSR_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_VSR_LO);
    L9958_ISR_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_ISR_LO);
    L9958_ISR_Disable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_ISR_DISABLE_FALSE);
#endif
}

/*=============================================================================
 * mg_HAL_Fault_ETC_STB_STG_Test_Configure
 * @func  set ETC STB or STG fault configure
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_Fault_ETC_STB_STG_Test_Configure(void)
{
#ifdef __MG_PHDL_USED
    mg_PHD_Set_Low_Side_Current_Limit(0x03);
    mg_PHD_Set_Slew_Time(0x00);
    mg_PHD_Set_Auto_LS_Current_Limit_Slew_Time(1);
    mg_PHD_Set_Auto_Thermal_Warning_Current_Limit(1);
    mg_PHD_Set_Auto_Thermal_Warning_Slew_Time(1);
#endif
#ifdef __MG_L9958_USED
    L9958_Diag_Rst_Disable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_DIAG_RST_DISABLE_FLASE);
    L9958_Regulation_Curr_Level_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_CURRENT_LEVEL_8P6);
    L9958_OL_ON_Enable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_OPEN_LOAD_ON_DISABLE);
    L9958_VSR_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_VSR_LO);
    L9958_ISR_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_ISR_LO);
    L9958_ISR_Disable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_ISR_DISABLE_TRUE);
#endif
}

/*=============================================================================
 * mg_HAL_Fault_ETC_Over_Current_Test_Configure
 * @func  set ETC over current fault configure
 * @parm  slew rate
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_Fault_ETC_Over_Current_Test_Configure(uint8_t slew_rate)
{
#ifdef __MG_PHDL_USED
    mg_PHD_Set_Low_Side_Current_Limit(0x00);
    mg_PHD_Set_Slew_Time(slew_rate);
    mg_PHD_Set_Auto_LS_Current_Limit_Slew_Time(1);
    mg_PHD_Set_Auto_Thermal_Warning_Current_Limit(1);
    mg_PHD_Set_Auto_Thermal_Warning_Slew_Time(1);
#endif
#ifdef __MG_L9958_USED
    L9958_Diag_Rst_Disable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_DIAG_RST_DISABLE_FLASE);
    L9958_Regulation_Curr_Level_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_CURRENT_LEVEL_2P5);
    L9958_OL_ON_Enable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_OPEN_LOAD_ON_ENABLE);
    L9958_VSR_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_VSR_LO);
    L9958_ISR_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_ISR_LO);
    L9958_ISR_Disable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_ISR_DISABLE_FALSE);
#endif
}

/*=============================================================================
 * mg_HAL_ComplexIO_Fault_Read
 * @func  read external device fault buff
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ComplexIO_Fault_Read(void)
{
#ifdef __MG_C2MIO_USED
    C2MIO_SPI_Immediate_Transfer( C2MIO_Set_Device_Index( 0, C2MIO_INDEX_0 ), C2MIO_MESSAGE_PCH_FAULTS_STATUS_READ);
#endif
#ifdef __MG_VSEP_USED
    SPIPort_Transfer_Immediate( VSEP_EST_FAULT_SYNC_MESSAGE[VSEP_INDEX_0].port, &VSEP_EST_FAULT_SYNC_MESSAGE[VSEP_INDEX_0] );
    SPIPort_Transfer_Immediate( VSEP_SDOA06_MESSAGE[VSEP_INDEX_0].port, &VSEP_SDOA06_MESSAGE[VSEP_INDEX_0] );
    VSEP_SPI_Immediate_Transfer( VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ), VSEP_MESSAGE_FAULT_READ);
#endif
}
#endif
/*=============================================================================
 * mg_HAL_PowerDevice_Fault_Read
 * @func  read external device fault buff
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_PowerDevice_Fault_Read(void)
{
#ifdef __MG_C2PS_USED
    C2PS_SPI_Immediate_Transfer(C2PS_Set_Device_Index( 0, C2PS_INDEX_0 ), C2PS_MESSAGE_READ_DIAG);
#endif
#ifdef __MG_TLE4471_USED
#endif
}

#if 0
/*=============================================================================
 * mg_HAL_ETC_Fault_Read
 * @func  read external device fault buff
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Fault_Read(void)
{
#ifdef __MG_PHDL_USED
    PHD_SPI_Immediate_Transfer(PHD_Set_Index( 0, PHD_INDEX_0 ));
    mg_PHD_Set_Clear_Fault(0);
#endif
#ifdef __MG_L9958_USED
    L9958_Diag_Rst_Disable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_DIAG_RST_DISABLE_FLASE);
    L9958_SPI_Immediate_Transfer( L9958_Set_Device_Index( 0, L9958_INDEX_0 ) );
#endif
}

/*=============================================================================
 * mg_HAL_BARO_Fault_Read
 * @func  read external device fault buff
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_BARO_Fault_Read(void)
{
#ifdef __MG_KP254_USED
    KP254_FAULT_Diagnose_Device_Fault(MG_MTSA_CONFIG_KP254_TRIG_DIAG);
#endif
}

/*=============================================================================
 * mg_HAL_ComplexIO_Fault_Clear
 * @func  clear external device fault buff
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ComplexIO_Fault_Clear(void)
{
#ifdef __MG_C2MIO_USED
    C2MIO_SPI_Immediate_Transfer( C2MIO_Set_Device_Index( 0, C2MIO_INDEX_0 ), C2MIO_MESSAGE_PCH_FAULTS_STATUS_READ);
#endif
#ifdef __MG_VSEP_USED
    SPIPort_Transfer_Immediate( VSEP_EST_FAULT_SYNC_MESSAGE[VSEP_INDEX_0].port, &VSEP_EST_FAULT_SYNC_MESSAGE[VSEP_INDEX_0] );
    SPIPort_Transfer_Immediate( VSEP_SDOA06_MESSAGE[VSEP_INDEX_0].port, &VSEP_SDOA06_MESSAGE[VSEP_INDEX_0] );
    VSEP_SPI_Immediate_Transfer( VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ), VSEP_MESSAGE_FAULT);
#endif
}

/*=============================================================================
 * mg_HAL_PowerDevice_Fault_Clear
 * @func  clear external device fault buff
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_PowerDevice_Fault_Clear(void)
{
#ifdef __MG_C2PS_USED
    C2PS_SPI_Immediate_Transfer(C2PS_Set_Device_Index( 0, C2PS_INDEX_0 ), C2PS_MESSAGE_READ_DIAG);
#endif
#ifdef __MG_TLE4471_USED
#endif
}

/*=============================================================================
 * mg_HAL_ETC_Fault_Clear
 * @func  clear external device fault buff
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Fault_Clear(void)
{
#ifdef __MG_PHDL_USED
    mg_PHD_Set_Clear_Fault(1);
#endif
#ifdef __MG_L9958_USED
    L9958_Diag_Rst_Disable_Set((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0, L9958_DIAG_RST_DISABLE_FLASE);
    L9958_SPI_Immediate_Transfer( L9958_Set_Device_Index( 0, L9958_INDEX_0 ) );
#endif
}

/*=============================================================================
 * mg_HAL_BARO_Fault_Clear
 * @func  clear external device fault buff
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_BARO_Fault_Clear(void)
{
#ifdef __MG_KP254_USED
    KP254_FAULT_Clear_Device_Fault(MG_MTSA_CONFIG_KP254_TRIG_DIAG);
#endif
}

/*=============================================================================
 * mg_HAL_ComplexIO_Fault_Get
 * @func  get external fault information
 * @parm  map index
 * @rdesc fault result
 *===========================================================================*/
uint8_t mg_HAL_ComplexIO_Fault_Get(uint8_t index)
{
    uint8_t fault_result;
    uint8_t fault_map_index;
    uint8_t fault_map_position;
#ifdef __MG_C2MIO_USED

    fault_map_index = (uint8_t)C2MIO_FAULT_Map_Get_Index( C2MIO_FAULT_CHANNEL_MAP[index]);
    fault_map_position = (uint8_t)C2MIO_FAULT_Map_Get_Position( C2MIO_FAULT_CHANNEL_MAP[index]);
    fault_result = (uint8_t)Extract_Bits( C2MIO_PCH_Fault_Rxd[ C2MIO_INDEX_0 ][fault_map_index], fault_map_position, BIT_2 );
#endif
#ifdef __MG_VSEP_USED
    fault_map_index = (uint8_t)VSEP_FAULT_Map_Get_Index( VSEP_FAULT_CHANNEL_MAP[index]);
    fault_map_position = (uint8_t)VSEP_FAULT_Map_Get_Position( VSEP_FAULT_CHANNEL_MAP[index]);
    if ( index >= VSEP_CHANNEL_PCH_01_FLT_LVL_1 && index <= VSEP_CHANNEL_PCH_04_FLT_LVL_1_2)
    {
      fault_result = (uint8_t)Extract_Bits( VSEP_EST_Fault_SYNC_Rxd[VSEP_INDEX_0][fault_map_index],fault_map_position, BIT_2 );
    }
    else if ( index >= VSEP_CHANNEL_PCH_05_FLT_LVL_1_2 && index <= VSEP_CHANNEL_PCH_08_FLT_LVL_1_2)
    {
      fault_result = (uint8_t)Extract_Bits( VSEP_SDOA06_Rxd[VSEP_INDEX_0][fault_map_index],fault_map_position, BIT_2 );
    }
    else//for PCH09~PCH30
    {
      fault_result = (uint8_t)Extract_Bits( VSEP_Fault_Rxd[VSEP_INDEX_0][fault_map_index],fault_map_position, BIT_2 );
    }
#endif
    return fault_result;
}
#endif
/*=============================================================================
 * mg_HAL_PowerDevice_Fault_Get
 * @func  get external fault information
 * @parm  map index
 * @rdesc fault result
 *===========================================================================*/
uint8_t mg_HAL_PowerDevice_Fault_Get(uint8_t index)
{
    uint8_t fault_result;
#ifdef __MG_C2PS_USED
    fault_result = (uint8_t)((C2PS_DIAG_Rxd[0][2] >> 12) & 0x03);
#endif
#ifdef __MG_TLE4471_USED
    fault_result = 0;
#endif
    return fault_result;
}
#if 0
/*=============================================================================
 * mg_HAL_ETC_Fault_Get
 * @func  get external fault information
 * @parm  map index
 * @rdesc fault result
 *===========================================================================*/
uint8_t mg_HAL_ETC_Fault_Get(uint8_t index)
{
    uint8_t fault_result;
#ifdef __MG_PHDL_USED
    fault_result = PHD_Rxd[0];
#endif
#ifdef __MG_L9958_USED
    MG_HAL_WORD_ACCESS_T fault_log;
    fault_log.word = (uint16_t)L9958_Get_Fault_Status((IO_Configuration_T)L9958_CONFIGURATION_REG_INIT_0);
    switch (index)
    {
        case 0:
            fault_result = fault_log.byte_access.hibyte;
            break;
        case 1:
            fault_result = fault_log.byte_access.lobyte;
            break;
        default:
            fault_result = 0;
            break;
    }
#endif
    return fault_result;
}

/*=============================================================================
 * mg_HAL_BARO_Fault_Get
 * @func  get external fault information
 * @parm  map index
 * @rdesc fault result
 *===========================================================================*/
uint8_t mg_HAL_BARO_Fault_Get(uint8_t index)
{
    uint8_t fault_result;
#ifdef __MG_KP254_USED
    fault_result = (uint8_t)KP254_FAULT_Get_Device_Fault_Type(MG_MTSA_CONFIG_KP254_TRIG_DIAG);
#endif
    return fault_result;
}

#endif
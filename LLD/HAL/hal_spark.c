#include "HLS.h"
#include "hwiocald.h"
#include "io_conversion.h"
#include "dd_spark_interface.h"
#include "dd_crank_interface.h"
#include "io_config_spark.h"

//=============================================================================
// Spark
//=============================================================================
//=============================================================================
// SetHWIO_SPARK_DiagEnabled
//=============================================================================
void SetHWIO_SPARK_DiagEnabled( void )
{
}

//=============================================================================
// SetHWIO_SPARK_DiagDisabled
//=============================================================================
void SetHWIO_SPARK_DiagDisabled( void )
{
}

//=============================================================================
// DisableHWIO_EST
//=============================================================================
void DisableHWIO_EST( void )
{
   SPARK_Set_Enable(false);
}

//=============================================================================
// EnableHWIO_EST
//=============================================================================
void EnableHWIO_EST( void )
{
   SPARK_Set_Enable( true);
}

//=============================================================================
// DisableHWIO_EST_Channel
//=============================================================================
void SetHWIO_EST_Channel_State(uint8_t  in_cylinder, bool in_state)
{
    SPARK_Set_Channel_Enable(in_cylinder, in_state );
}

//=============================================================================
// GetHWIO_t_DeliveredDwell
//=============================================================================
T_MILLISECONDSb GetHWIO_t_DeliveredDwell( void )
{
   return (T_MILLISECONDSb)SPARK_Get_Delivered_Duration(S_MILLISECONDSb, MILLISECOND_RESOLUTION);
}

//=============================================================================
// GetHWIO_Num58xGapsBeforeSeqn
//=============================================================================
uint8_t GetHWIO_Num58xGapsBeforeSeqn (void)
{
   return KyHWIO_Num58xGapsBeforeSeqn;
}

//=============================================================================
// CRANK_Convert_To_Signed_Angle
//   TOBE moved out of hal_spark.c
//=============================================================================
T_ANGLEa CRANK_Convert_To_Signed_Angle( Crank_Angle_T in_crank_angle )
{
    uint32_t  unsigned_crank_angle;
    T_ANGLEa  angle;
    uint32_t  temp_angle;

    unsigned_crank_angle = (uint32_t) in_crank_angle;

    if ( in_crank_angle < 0 )
    {
        unsigned_crank_angle = ( 0 - unsigned_crank_angle );
     
        temp_angle = (unsigned_crank_angle * CRANK_DEGREES_PER_TOOTH) >> (CRANK_ANGLE_PRECISION - S_ANGLEa);
     
        angle = (T_ANGLEa)( ( temp_angle > V_ANGLEa(256) ) ? V_ANGLEa(-256) : -((int32_t)temp_angle) );
    }
    else
    {
        temp_angle = (unsigned_crank_angle * CRANK_DEGREES_PER_TOOTH) >> (CRANK_ANGLE_PRECISION - S_ANGLEa);
     
        angle = (T_ANGLEa)( ( temp_angle > V_ANGLEa(256) ) ? V_ANGLEa(256) : temp_angle );
    }
   
    return( angle );
}


//=============================================================================
// SetHWIO_DualEST_AlternatingMode
//=============================================================================
void SetHWIO_DualEST_AlternatingMode( void )
{
   SPARK_Set_Mode( SPARK_SIMULTANEOUS_MODE );
}

//=============================================================================
// SetHWIO_MainPulse_DwellTime
//=============================================================================
void SetHWIO_MainPulse_DwellTime(uint8_t cylinder, T_MILLISECONDSb in_dwell_time)
{
    SPARK_Set_Duration(cylinder, in_dwell_time, S_MILLISECONDSb, MILLISECOND_RESOLUTION);
}

//=============================================================================
// SetHWIO_ExtraPulse1_DwellTime
//=============================================================================
void SetHWIO_ExtraPulse1_DwellTime(uint8_t cylinder,  T_MILLISECONDSb in_break_time, T_MILLISECONDSb in_dwell_time)
{
    SPARK_Set_Duration_Extra_P1(cylinder, in_break_time, in_dwell_time, S_MILLISECONDSb, MILLISECOND_RESOLUTION);
}

//=============================================================================
// SetHWIO_ExtraPulse2_DwellTime
//=============================================================================
void SetHWIO_ExtraPulse2_DwellTime(uint8_t cylinder, T_MILLISECONDSb in_break_time, T_MILLISECONDSb in_dwell_time)
{
    SPARK_Set_Duration_Extra_P2(cylinder, in_break_time, in_dwell_time, S_MILLISECONDSb, MILLISECOND_RESOLUTION);
}

//=============================================================================
// SetHWIO_Spark_State
//=============================================================================
void SetHWIO_Spark_State(uint8_t cylinder, bool state)
{
    SPARK_Set_State(cylinder, state);
}

//=============================================================================
// SetHWIO_Spark_ExtraPulse_Count
//=============================================================================
void SetHWIO_Spark_ExtraPulse_Count(uint8_t cylinder, uint8_t extra_pulse)
{
    SPARK_Set_ExtraPulse_Count(cylinder, extra_pulse);
}

//=============================================================================
// SetHWIO_MaxDwell
//=============================================================================
void SetHWIO_MaxDwell(T_MILLISECONDSb in_max_dwell )
{
   SPARK_Set_Max_Duration(in_max_dwell, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
}

//=============================================================================
// SetHWIO_MinDwell
//=============================================================================
void SetHWIO_MinDwell(T_MILLISECONDSb in_min_dwell )
{
   SPARK_Set_Min_Duration(in_min_dwell, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
}

//=============================================================================
// SetHWIO_SequentialEST_Mode
//=============================================================================
void SetHWIO_SequentialEST_Mode( void )
{

   SPARK_Set_Mode( SPARK_SEQUENTIAL_MODE );
}

//=============================================================================
// SetHWIO_SimultaneousEST_Mode
//=============================================================================
void SetHWIO_SimultaneousEST_Mode( void )
{
   SPARK_Set_Mode( SPARK_SIMULTANEOUS_MODE );
}

//=============================================================================
// SetHWIO_SingleChannelEST_Mode
//=============================================================================
void SetHWIO_SingleChannelEST_Mode( void )
{
   SPARK_Set_Mode(  SPARK_SINGLE_CHANNEL_MODE );
}

//=============================================================================
// SetHWIO_SpkAngle
//=============================================================================
void SetHWIO_SpkAngle(uint8_t in_cylinder, T_ANGLEa advance_spark_count)
{
    uint32_t temp_count, unsigned_angle;
    Crank_Angle_T spark_angle;
    T_ANGLEa signed_angle;

    signed_angle = advance_spark_count;
    unsigned_angle = (uint32_t) signed_angle;

    if (signed_angle < 0 )
    {
        unsigned_angle = ( 0 - unsigned_angle );

        temp_count = CRANK_Convert_Angle_To_uCrank_Angle(unsigned_angle,S_ANGLEa);

        spark_angle = (Crank_Angle_T)( ( temp_count > CRANK_ANGLE_MAX ) ? CRANK_ANGLE_MIN : -((int32_t)temp_count) );
    }
    else
    {

        temp_count = CRANK_Convert_Angle_To_uCrank_Angle(unsigned_angle,S_ANGLEa);

        spark_angle = (Crank_Angle_T)( ( temp_count > CRANK_ANGLE_MAX ) ? CRANK_ANGLE_MAX : temp_count );
    }

    SPARK_Set_Angle_In_Counts(in_cylinder, spark_angle);
}

//=============================================================================
// SetHWIO_SprkMinBurn
//=============================================================================
void SetHWIO_SprkMinBurn(T_MILLISECONDSb SfVIOS_MinBurn)
{

}

//=============================================================================
// EnableHWIO_Spark_Overide
//=============================================================================
void EnableHWIO_Spark_Overide(void)
{
   SPARK_Set_Override_Mode(  true);
}

//=============================================================================
// DisableHWIO_Spark_Overide
//=============================================================================
void DisableHWIO_Spark_Overide(void)
{
   SPARK_Set_Override_Mode( false);
}

//=============================================================================
// SetHWIO_SparkForcedPulse
//=============================================================================
void SetHWIO_SparkForcedPulse(uint8_t in_channel, T_MILLISECONDSb in_dwell_time)
{
   SPARK_Force_Pulse(
           in_channel,
      in_dwell_time,
      S_MILLISECONDSb,
      MILLISECOND_RESOLUTION );
}

//=============================================================================
// GetHWIO_t_Spark_BurnTime
//=============================================================================
T_MILLISECONDSb GetHWIO_t_Spark_BurnTime( uint8_t in_cylinder, uint8_t in_pulse_index )
{
   return (T_MILLISECONDSb)0; // stubbed
}

//=============================================================================
// GetIO_SPRK_BurnTime
//=============================================================================
T_MILLISECONDSb GetIO_SPRK_BurnTime( uint8_t in_cylinder, uint8_t in_pulse_index )
{
   return (T_MILLISECONDSb)0; // stubbed
}

//=============================================================================
// SetIO_SPRK_BT_OneShotOption
//=============================================================================
void SetIO_SPRK_BT_OneShotOption(TbBOOLEAN one_shot)
{
} // stubbed

//=============================================================================
// SetHWIO_Min_OffTime
//=============================================================================
void SetHWIO_Min_OffTime(T_MILLISECONDSb in_min_dwell )
{
} // stubbed

//=============================================================================
// SetIO_SPRK_BT_WakeUpDelay
//=============================================================================
void SetIO_SPRK_BT_WakeUpDelay(T_MILLISECONDSb in_wakeup_delay )
{
   SetHWIO_Min_OffTime(in_wakeup_delay);
}

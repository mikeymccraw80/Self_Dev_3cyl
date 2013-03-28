#ifndef IO_CONVERSION_H
#define IO_CONVERSION_H

#include "reuse.h"

//=============================================================================
// Individual Microprocessor Device Drivers must provide these functions.
//=============================================================================

//=============================================================================
// mult_div64
//
// ( a * b ) / c
//
//=============================================================================
uint32_t mult_div64(
   uint32_t a,
   uint32_t b,
   uint32_t c );

//=============================================================================
// mult_div64_shift
//
// ( a * b ) / c >> d
//
//=============================================================================
uint32_t mult_div64_shift(
   uint32_t a,
   uint32_t b,
   uint32_t c,
   uint32_t d );

//=============================================================================
// mult_shift_div64
//
// ( ( a * b ) << d ) / c
//
//=============================================================================
uint32_t mult_shift_div64(
   uint32_t a,
   uint32_t b,
   uint32_t c,
   uint32_t d );

//=============================================================================
// mult64_shift
//
// ( a * b ) >> c
//
//=============================================================================
int32_t mult64_shift(
   int32_t  a,
   uint32_t b,
   uint32_t c );

//=============================================================================
// umult64_shift
//
// ( a * b ) >> c
//
//=============================================================================
uint32_t umult64_shift(
   uint32_t a,
   uint32_t b,
   uint32_t c );


//=============================================================================
//
// Second resolutions
//
// Purpose: These values provide decimal positions for time resolution
//
//=============================================================================
#define SECOND_RESOLUTION      (0)
#define MILLISECOND_RESOLUTION (3)
#define MICROSECOND_RESOLUTION (6)
#define NANOSECOND_RESOLUTION  (9)


extern const uint32_t POWER_OF_10[];

//=============================================================================
// @doc IO_CONVERSION & API
//=============================================================================
//=============================================================================
// IO_Convert_Time_To_Count
//
// @func This procedure will convert the application time to the
//          device counts.
//          The combination of in_time and in_counts_per_time
//          may exceed 32 bits, however the in_time_resolution value must be sufficently
//          large to bring the final result back to a 32 bit value.
//          count = ( ( time * counts_per_time ) / 10^time_resolution ) >> time_scaler
//
// @parm uint32_t | in_time | non hardware representation of time, range [0:0xFFFFFFFF]
//
// @parm uint32_t | in_counts_per_time | frequency in Hz, range [0:0xFFFFFF00]
//
// @parm uint8_t | in_time_bit_precision | fixed point decimal location range [0:31]
//
// @parm uint8_t | in_time_resolution | power of 10 representation of the number passed in
//                                      0 SECOND_RESOLUTION     
//                                      3 MILLISECOND_RESOLUTION
//                                      6 MICROSECOND_RESOLUTION
//                                      9 NANOSECOND_RESOLUTION 
//
// @rdesc counts
//
// @end
//=============================================================================
INLINE uint32_t IO_Convert_Time_To_Count(
   uint32_t in_time,
   uint32_t in_counts_per_time,
   uint8_t  in_time_bit_precision,
   uint8_t  in_time_resolution )
{
   uint32_t count;
   uint32_t power = POWER_OF_10[ in_time_resolution ];
   
   in_time_bit_precision &= 0x1f;
   count = mult_div64_shift(in_time,in_counts_per_time,power,in_time_bit_precision);

   return count;


}


//=============================================================================
// IO_Convert_Count_To_Time
//
// @func This procedure will convert the device counts to the specific
//          application time.
//          The combination of in_counts and in_time_resolution
//          may exceed 32 bits, however the counts_per_time value must be sufficently
//          large to bring the final result back to a 32 bit value.
//          time = ( ( count * 10^time_resolution ) << time_scaler ) / counts_per_time
//
// @parm uint32_t | in_counts | time represented in hardware device counts, range [0:0xFFFFFFFF]
//
// @parm uint32_t | in_counts_per_time | frequency in Hz, range [0:0xFFFFFF00]
//
// @parm uint8_t | in_time_bit_precision | fixed point decimal location, range [0:31]
//
// @parm uint8_t | in_time_resolution | power of 10 representation of the number passed in
//                                      0 SECOND_RESOLUTION     
//                                      3 MILLISECOND_RESOLUTION
//                                      6 MICROSECOND_RESOLUTION
//                                      9 NANOSECOND_RESOLUTION 
//
// @rdesc time.
//
// @end
//=============================================================================
INLINE uint32_t IO_Convert_Count_To_Time(
   uint32_t in_counts,
   uint32_t in_counts_per_time,
   uint8_t  in_time_bit_precision,
   uint8_t  in_time_resolution )
{

   uint32_t time;
   uint32_t power = POWER_OF_10[ in_time_resolution ];
   
   in_time_bit_precision &= 0x1f;
   time =  mult_shift_div64( in_counts, power, in_counts_per_time, in_time_bit_precision);

   return time;

}


//=============================================================================
// IO_Convert_Frequency_To_Counts
//
// @func This function converts the specific application frequency to
//          device counts.
//          counts = ( counts_per_time << frequency_scaler ) / frequency
//
// @parm uint32_t | in_frequency | frequency value in Hz range [0:0xFFFFFFFF]
//
// @parm uint8_t  | in_frequency_scaler | fixed point decimal location range [0:31]
//
// @parm uint32_t | in_counts_per_time | frequency in Hz range [0:0xFFFFFFFF]
//
// @rdesc counts.
//
// @end
//=============================================================================
INLINE uint32_t IO_Convert_Frequency_To_Counts(
   uint32_t  in_frequency,
   uint8_t   in_frequency_scaler,
   uint32_t  in_counts_per_time)
{
   uint32_t count = 0;

   /* check for zero denominator */
   if(in_frequency != 0)
   {
      in_frequency_scaler &= 0x1f;
      count = mult_shift_div64( in_counts_per_time, 1, in_frequency, in_frequency_scaler );
   }

   return count;
}


//=============================================================================
// IO_Convert_Counts_To_Frequency
//
// @func This function converts device counts to the specific application
//          frequency.
//          The combination of in_percent and in_counts_per_period
//          may exceed 32 bits, however the in_max_percent value must be sufficently
//          large to bring the final result back to a 32 bit value.
//          frequency = ( ( pulses * counts_per_time ) << frequency_scaler ) / elapsed time
//
// @parm uint32_t | in_counts | device hardware counts range [0:0xFFFFFFFF]
//
// @parm uint8_t  | in_frequency_scaler | fixed point decimal location range [0:31]
//
// @parm uint32_t | in_counts_per_time | frequency in Hz range [0:0xFFFFFFFF]
//
// @parm uint32_t | in_elapsed_time | time im hardware counts that has elapsed range [0:0xFFFFFF00]
//
// @rdesc frequency range [0:0xFFFFFFFF]
//
// @end
//=============================================================================
INLINE uint32_t IO_Convert_Counts_To_Frequency(
   uint32_t in_number_of_pulses,
   uint8_t  in_frequency_scaler,
   uint32_t in_counts_per_time,
   uint32_t in_elapsed_time )
{
   uint32_t frequency = 0xFFFFFFFF;

   /* check for zero denominator */
   if( in_elapsed_time != 0 )
   {
      in_frequency_scaler &= 0x1F;
      frequency = mult_shift_div64( in_number_of_pulses, in_counts_per_time, in_elapsed_time, in_frequency_scaler );
   }

   return frequency;
}


//=============================================================================
// IO_Convert_Percent_To_Counts
//
// @func This function converts the specific application frequency to
//          device counts.
//          The combination of in_percent and in_counts_per_period
//          may exceed 32 bits, however the in_max_percent value must be sufficently
//          large to bring the final result back to a 32 bit value.
//          count = ( percent * counts_per_period ) / max_percent
//
// @parm uint32_t | in_percent | any value range [0:0xFFFFFFFF]
//
// @parm uint32_t | in_max_percent | value equivalent to 100% range [0:0xFFFFFF00]
//
// @parm uint32_t | in_counts_per_period | device hardware counts equivelant
//                                         to 100% range [0:0xFFFFFFFF]
//
// @rdesc counts.
//
// @end
//=============================================================================
INLINE uint32_t IO_Convert_Percent_To_Counts(
   uint32_t  in_percent,
   uint32_t  in_max_percent,
   uint32_t  in_counts_per_period)
{
   uint32_t count;

   count = mult_div64( in_percent, in_counts_per_period, in_max_percent );
   
   return count;
}


//=============================================================================
// IO_Convert_Counts_To_Percent
//
// @func This function converts device counts to the specific application
//          Percentage.
//          The combination of in_count and in_max_percent
//          may exceed 32 bits, however the in_counts_per_period value must be sufficently
//          large to bring the final result back to a 32 bit value.
//          percent = ( count * max_percent ) / counts_per_period
//
// @parm uint32_t | in_count | device hardware counts range [0:0xFFFFFFFF]
//
// @parm uint32_t | in_max_percent | value equivalent to 100% range [0:0xFFFFFF00]
//
// @parm uint32_t | in_counts_per_period | device hardware counts equivelant
//                                         to 100% range [0:0xFFFFFFFF]
//
// @rdesc percent.
//
// @end
//=============================================================================
INLINE uint32_t IO_Convert_Counts_To_Percent(
   uint32_t in_count,
   uint32_t in_max_percent,
   uint32_t in_counts_per_period )
{
   uint32_t percent;

   percent = mult_div64( in_count, in_max_percent, in_counts_per_period );
   
   return percent;
}

#define IO_CONVERSION_DEFAULT_SHIFT ( 8 )

//=============================================================================
// IO_Convert_Time_To_Angle
//
// @func This procedure will convert the application time to the
//          device angle.
//
// @parm int32_t | in_time | non hardware representation of time, range [0x80000000:0x7FFFFFFF]
//
// @parm uint8_t | in_angle_bit_precision | fixed point decimal location, range [0:31]
//
// @parm uint32_t | in_period | period, range [0:0x00FFFFFF]
//
// @parm uint16_t | in_degrees | range [0 : 720] must be a non fractional value.
//
// @rdesc signed angle [0x80000000:0x7FFFFFFF]
//
// @end
//=============================================================================
INLINE int32_t IO_Convert_Time_To_Angle(
   int32_t  in_time,
   uint8_t  in_angle_bit_precision,
   uint32_t in_period,
   uint16_t  in_degrees )
{
   int32_t  angle;
   uint32_t  calc_angle;
   uint32_t time;
   bool     sign_of_time = ( in_time > 0 ) ? true : false;
   uint32_t intermediate;

   time = ( sign_of_time ) ? in_time : -in_time;

   intermediate = ( in_period ) / in_degrees;
   
   in_angle_bit_precision &= 0x0f;
   calc_angle = mult_shift_div64( time, 1, intermediate, in_angle_bit_precision );
   
   angle = ( sign_of_time ) ? calc_angle : -(int32_t)calc_angle;

   return angle;
}

//=============================================================================
// IO_Convert_uTime_To_uAngle
//
// @func This procedure will convert the application time to the
//          device angle.
//
// @parm uint32_t | in_time | non hardware representation of time, range [0:0x00FFFFFF]
//
// @parm uint8_t | in_angle_bit_precision | fixed point decimal location, range [0:31]
//
// @parm uint32_t | in_period | period, range [0:0x00FFFFFF]
//
// @parm uint16_t | in_degrees | range [0 : 720] must be a non fractional value.
//
// @rdesc unsigned angle [0:0xFFFFFFFF]
//
// @ex |
// angle = IO_Convert_uTime_To_uAngle(
//     Delta_Time,              // Time to be converted into angle
//     8,                       // Precision of Angle being returned
//     Cylinder_Event_Time,     // Time per Cylinder Event
//     120 / 4 );               // Teeth per Cylinder Event = Number of Teeth / Number of channels
//
// @end
//=============================================================================
INLINE uint32_t IO_Convert_uTime_To_uAngle(
   uint32_t in_time,
   uint8_t  in_angle_bit_precision,
   uint32_t in_period,
   uint16_t in_degrees )
{
   uint32_t angle;
   uint32_t intermediate;

   intermediate = in_period  / in_degrees;

   in_angle_bit_precision &= 0x0f;
   angle =  mult_shift_div64( ( in_time << IO_CONVERSION_DEFAULT_SHIFT ), 1, intermediate, in_angle_bit_precision) >> IO_CONVERSION_DEFAULT_SHIFT;

   return angle;
}

//=============================================================================
// IO_Convert_Angle_To_Time
//
// @func This procedure will convert the device angle to the specific
//          application time.
//
// @parm int32_t | in_angle | time represented in hardware device angle, range [0x80000000:0x7FFFFFFF]
//
// @parm uint8_t | in_angle_bit_precision | fixed point decimal location, range [0:31]
//
// @parm uint32_t | in_period | period, range [0:0x00FFFFFF]
//
// @parm uint32_t | in_degrees | range [0 : 720] must be a non fractional value.
//
// @rdesc signed time [0x80000000:0x7FFFFFFF]
//
// @end
//=============================================================================
INLINE int32_t IO_Convert_Angle_To_Time(
   int32_t  in_angle,
   uint8_t  in_angle_bit_precision,
   uint32_t in_period,
   uint16_t in_degrees )
{

   int32_t time;
   uint32_t intermediate;

   intermediate = ( in_period << IO_CONVERSION_DEFAULT_SHIFT ) / in_degrees;

   in_angle_bit_precision &= 0x0f;
   time =  mult64_shift( in_angle, intermediate, ( in_angle_bit_precision + IO_CONVERSION_DEFAULT_SHIFT ) );

   return time;

}

//=============================================================================
// IO_Convert_uAngle_To_uTime
//
// @func This procedure will convert the device angle to the specific
//          application time.
//
// @parm uint32_t | in_angle | time represented in hardware device angle, range [0:0x00FFFFFF]
//
// @parm uint8_t | in_angle_bit_precision | fixed point decimal location, range [0:31]
//
// @parm uint32_t | in_period | period, range [0:0x00FFFFFF]
//
// @parm uint32_t | in_degrees | range [0 : 720] must be a non fractional value.
//
// @rdesc time [0:0xFFFFFFFF]
//
// @end
//=============================================================================
INLINE uint32_t IO_Convert_uAngle_To_uTime(
   uint32_t in_angle,
   uint8_t  in_angle_bit_precision,
   uint32_t in_period,
   uint16_t in_degrees )
{

   uint32_t time;
   uint32_t intermediate;

   intermediate = ( in_period << IO_CONVERSION_DEFAULT_SHIFT ) / in_degrees;

   in_angle_bit_precision &= 0x0f;
   time =  umult64_shift( in_angle, intermediate, ( in_angle_bit_precision + IO_CONVERSION_DEFAULT_SHIFT ) );

   return time;

}


#endif // IO_CONVERSION_H


#ifndef DD_CRANK_H
#define DD_CRANK_H

#include "crank.h"
#include "dd_mcd5408.h"

//=============================================================================
//   Enum Data Defines
//=============================================================================
typedef enum MCD5408_IRQ_Enable_F_MASK
{
   EPI_CRANK_EDGE_REJECTED_IRQ_ENABLE = 0x80000000,
   EPI_CRANK_GAP_DETECTED_IRQ_ENABLE  = 0x40000000,
   EPI_CRANK_TOOTHPULSE_IRQ_ENABLE_1  = 0x20000000,
   EPI_CRANK_TOOTHPULSE_IRQ_ENABLE_2  = 0x10000000,
   EPI_CRANK_TOOTHPULSE_IRQ_ENABLE_3  = 0x08000000,
   EPI_CRANK_TOOTHPULSE_IRQ_ENABLE_4  = 0x04000000

}  MCD5408_IRQ_Enable_MASK_T;


//=============================================================================
// Crank Angle is based on the primitive being used.
// EPPwMT uses A resolution of 6 degrees per tooth and 1/256 fraction of a tooth
// in precision. It's range is [0 to 256).
//=============================================================================
#define CRANK_ANGLE_PRECISION (8UL)
#define CRANK_ANGLE_MIN       (INT16_MIN)
#define CRANK_ANGLE_MAX       (INT16_MAX)

#define uCRANK_ANGLE_PRECISION (8UL)
#define uCRANK_ANGLE_MIN       (UINT24_MIN)
#define uCRANK_ANGLE_MAX       (UINT24_MAX)

#define CRANK_Convert_uCrank_Angle_To_Teeth(a) \
   ( (a) >> uCRANK_ANGLE_PRECISION )

#define CRANK_Convert_Teeth_To_uCrank_Angle(a) \
   ( (a) << uCRANK_ANGLE_PRECISION )

#define CRANK_Convert_uCrank_Angle_To_Angle(a) \
   ( ( (a) * CRANK_DEGREES_PER_TOOTH ) >> uCRANK_ANGLE_PRECISION )

#define CRANK_Convert_Angle_To_uCrank_Angle(a,b) \
   (( ( (a) << uCRANK_ANGLE_PRECISION) / CRANK_DEGREES_PER_TOOTH ) >> (b) )


//=============================================================================
// /------------------------------------------------------------------------
// | 
// \------------------------------------------------------------------------
//=============================================================================

extern IO_Callback_T CRANK_Event_List[];

//=============================================================================
// CRANK_Get_Priority_Enable
//=============================================================================
#define CRANK_Get_Priority_Enable(a,b) \
   (uint32_t)( Insert_Bits( 0, a, b, 1 ) )

//=============================================================================
// CRANK_Set_Priority_Enable
//=============================================================================
#define CRANK_Set_Priority_Enable(a,b) \
   (uint32_t)( Insert_Bits( 0, a, b, 1 ) )


//=============================================================================
// CRANK_Set_Sync_Occurred
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Sync_Occurred(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_SYNC_OCCURRED, 1 ) )

//=============================================================================
// CRANK_Get_Sync_Occurred
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Sync_Occurred(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_SYNC_OCCURRED, 1 ) )

//=============================================================================
// CRANK_Set_First_Sync_Occurred
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_First_Sync_Occurred(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_FIRST_SYNC_OCCURRED, 1 ) )

//=============================================================================
// CRANK_Get_First_Sync_Occurred
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_First_Sync_Occurred(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_FIRST_SYNC_OCCURRED, 1 ) )

//=============================================================================
// CRANK_Set_Sync_Error_In_Progress
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Sync_Error_In_Progress(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_SYNC_ERROR_IN_PROGRESS, 1 ) )

//=============================================================================
// CRANK_Get_Sync_Error_In_Progress
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Sync_Error_In_Progress(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_SYNC_ERROR_IN_PROGRESS, 1 ) )

//=============================================================================
// CRANK_Set_First_Cylinder_Event_Occured
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_First_Cylinder_Event_Occured(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_FIRST_CYLINDER_EVENT_OCCURED, 1 ) )

//=============================================================================
// CRANK_Get_First_Cylinder_Event_Occured
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_First_Cylinder_Event_Occured(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_FIRST_CYLINDER_EVENT_OCCURED, 1 ) )

//=============================================================================
// CRANK_Set_Power_Up
//
// @func Set the flag Power_Up
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Power_Up(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_POWER_UP, 1 ) )

//=============================================================================
// CRANK_Get_Power_Up
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Power_Up(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_POWER_UP, 1 ) )

//=============================================================================
// CRANK_Set_Filter_Enabled
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Filter_Enabled(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_FILTER_ENABLED, 1 ) )

//=============================================================================
// CRANK_Get_Filter_Enabled
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Filter_Enabled(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_FILTER_ENABLED, 1 ) )

//=============================================================================
// CRANK_Set_Run_Reset_Bypass_Filter
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Run_Reset_Bypass_Filter(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_RUN_RESET_BYPASS_FILTER, 1 ) )

//=============================================================================
// CRANK_Get_Run_Reset_Bypass_Filter
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Run_Reset_Bypass_Filter(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_RUN_RESET_BYPASS_FILTER, 1 ) )

//=============================================================================
// CRANK_Set_Sync_Started
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Sync_Started(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_SYNC_STARTED, 1 ) )

//=============================================================================
// CRANK_Get_Sync_Started
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Sync_Started(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_SYNC_STARTED, 1 ) )

//=============================================================================
// CRANK_Set_Valid_Tooth
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Valid_Tooth(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_VALID_TOOTH, 1 ) )

//=============================================================================
// CRANK_Get_Valid_Tooth
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Valid_Tooth(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_VALID_TOOTH, 1 ) )

//=============================================================================
// CRANK_Set_Resync_Attempt_In_Prog
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Resync_Attempt_In_Prog(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_RESYNC_ATTEMPT_IN_PROG, 1 ) )

//=============================================================================
// CRANK_Get_Resync_Attempt_In_Prog
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Resync_Attempt_In_Prog(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_RESYNC_ATTEMPT_IN_PROG, 1 ) )

//=============================================================================
// CRANK_Set_Engine_Turning
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Engine_Turning(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_ENGINE_TURNING, 1 ) )

//=============================================================================
// CRANK_Get_Engine_Turning
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Engine_Turning(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_ENGINE_TURNING, 1 ) )

//=============================================================================
// CRANK_Set_Sync_First_Revolution
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Sync_First_Revolution(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_SYNC_FIRST_REVOLUTION, 1 ) )

//=============================================================================
// CRANK_Get_Sync_First_Revolution
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Sync_First_Revolution(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_SYNC_FIRST_REVOLUTION, 1 ) )

//=============================================================================
// CRANK_Set_Sync_Second_Revolution
//
// @func Set the flag
//
// @parm uint32_t | x | A <t uint32_t> to store the flag
//
// @parm bool | y | A <t bool> element
//
// @rdesc <t uint32_t> containing the element <t bool>
//
// @end
//=============================================================================
#define CRANK_Set_Sync_Second_Revolution(x,y) \
   (uint32_t)( Insert_Bits( x, y, CRANK_FLAG_SYNC_SECOND_REVOLUTION, 1 ) )

//=============================================================================
// CRANK_Get_Sync_Second_Revolution
//
// @func Get the flag
//
// @parm uint32_t | x | A <t uint32_t> that contains the flag
//
// @rdesc <t bool> element decoded from the <t uint32_t>
//
// @end
//=============================================================================
#define CRANK_Get_Sync_Second_Revolution(x) \
   (bool)( Extract_Bits( x, CRANK_FLAG_SYNC_SECOND_REVOLUTION, 1 ) )

//=============================================================================
// CRANK_Initialize
//=============================================================================
void CRANK_Initialize(
   IO_Crank_Initialization_Parameters_T  * const in_initialization_parameters );



//=============================================================================
// CRANK_Reset_Parameters
//=============================================================================
void CRANK_Reset_Parameters( void );

//=============================================================================
// CRANK_Get_First_Cylinder_Event_Angle
//
// @func Returns the first lo-res angle.
//
// @rdesc first lo resolution event angle.
//
// @end
//=============================================================================
uCrank_Angle_T CRANK_Get_First_Cylinder_Event_Angle( void );


//=============================================================================
// CRANK_Convert_To_Crank_Angle
//
// @func This procedure will convert an angle with fixed point precision to a Crank_Angle_T angle.
// <nl>       in_angle  is signed
// <nl>       returned Crank_Angle_T is signed
//
// @parm int32_t | in_signed_angle | description.
//
// @parm uint8_t | in_precision | description.
//
// @rdesc return value is signed so take precaution
//
// @end
//=============================================================================
Crank_Angle_T CRANK_Convert_To_Crank_Angle(
   int32_t  in_signed_angle,
   uint8_t  in_precision );

//=============================================================================
// CRANK_Convert_To_uCrank_Angle
//
// @func This procedure will convert an angle with fixed point precision to a Crank_Angle_T angle.
// <nl>       in_angle  is unsigned
// <nl>       returned uCrank_Angle_T is unsigned
//
// @parm uint32_t | in_unsigned_angle | description.
//
// @parm uint8_t | in_precision | description.
//
// @rdesc return value is signed so take precaution
//
// @end
//=============================================================================
uCrank_Angle_T CRANK_Convert_To_uCrank_Angle(
   uint32_t in_unsigned_angle,
   uint8_t  in_precision );

//=============================================================================
// Crank Angle to Time conversion
//=============================================================================

//=============================================================================
// CRANK_Convert_uCrank_Angle_To_uTime
//
// @func
//
// @parm uCrank_Angle_T | in_angle | description.
//
// @rdesc none
//
// @end
//=============================================================================
uint32_t CRANK_Convert_uCrank_Angle_To_uTime(
   uCrank_Angle_T  in_angle);

//=============================================================================
// CRANK_Convert_Crank_Angle_To_Time
//
// @func
//
// @parm Crank_Angle_T | in_angle | description.
//
// @rdesc none
//
// @end
//=============================================================================
int32_t CRANK_Convert_Crank_Angle_To_Time(
   Crank_Angle_T  in_angle);

//=============================================================================
// Time to Crank Angle conversion
//=============================================================================

//=============================================================================
// CRANK_Convert_uTime_To_uCrank_Angle
//
// @func
//
// @parm uint32_t | in_time | description.
//
// @rdesc the crank angle
//
// @end
//=============================================================================
uCrank_Angle_T CRANK_Convert_uTime_To_uCrank_Angle(
    uint32_t in_time);

//=============================================================================
// CRANK_Convert_Time_To_Crank_Angle
//
// @func
//
// @parm int32_t | in_time | description.
//
// @rdesc none
//
// @end
//=============================================================================
Crank_Angle_T CRANK_Convert_Time_To_Crank_Angle(
    int32_t in_time);

//=============================================================================
// Angle to Time conversion
//=============================================================================


//=============================================================================
// CRANK_Convert_uAngle_To_uTime
//=============================================================================
uint32_t CRANK_Convert_uAngle_To_uTime(
   uint32_t in_angle,
   uint8_t  in_precision );

//=============================================================================
// CRANK_Convert_Angle_To_Time
//=============================================================================
int32_t CRANK_Convert_Angle_To_Time(
   int32_t  in_angle,
   uint8_t  in_precision );

//=============================================================================
// Time to Angle conversion
//=============================================================================

//=============================================================================
// CRANK_Convert_uTime_To_uAngle
//=============================================================================
uint32_t CRANK_Convert_uTime_To_uAngle(
   uint32_t in_time,
   uint8_t  in_precision );

//=============================================================================
// CRANK_Convert_Time_To_Angle
//=============================================================================
int32_t CRANK_Convert_Time_To_Angle(
   int32_t  in_time,
   uint8_t  in_precision );

//=============================================================================
// CRANK_Get_Number_Of_Cylinders

//=============================================================================
uint8_t CRANK_Get_Number_Of_Cylinders( void );

//=============================================================================
// CRANK_Set_Cylinder_ID
//=============================================================================
void CRANK_Set_Cylinder_ID(
   Crank_Cylinder_T  in_id );


//=============================================================================
// CRANK_Get_Cylinder_ID
//=============================================================================
Crank_Cylinder_T CRANK_Get_Cylinder_ID( void );


//=============================================================================
// CRANK_Get_Next_Cylinder_ID
//=============================================================================
Crank_Cylinder_T CRANK_Get_Next_Cylinder_ID( void );


//=============================================================================
// CRANK_Get_Future_Cylinder_ID
//=============================================================================
Crank_Cylinder_T CRANK_Get_Future_Cylinder_ID(
   uint8_t  in_offset );


//=============================================================================
// CRANK_Increment_Cylinder_ID
//=============================================================================
Crank_Cylinder_T CRANK_Increment_Cylinder_ID(
   Crank_Cylinder_T  in_current_id,
   int8_t            in_offset );


//=============================================================================
// CRANK_Get_Edge_Time_From_Count
//=============================================================================
uint32_t CRANK_Get_Edge_Time_From_Count(
   uint16_t in_edge_count );


//=============================================================================
// CRANK_Get_Parameter
//=============================================================================
uint32_t CRANK_Get_Parameter(
   Crank_Parameter_T in_parameter,
   uint8_t           in_time_precision,
   uint8_t           in_time_resolution );


//=============================================================================
// CRANK_Set_Flag
//=============================================================================
void CRANK_Set_Flag(
   Crank_Flag_T   in_flag,
   bool           in_value );


//=============================================================================
// CRANK_Get_Flag
//=============================================================================
bool CRANK_Get_Flag(
   Crank_Flag_T   in_flag );



//=============================================================================
// CRANK_Enable_Synchronization
//=============================================================================
 void CRANK_Enable_Synchronization( void );


#endif // DD_CRANK_H


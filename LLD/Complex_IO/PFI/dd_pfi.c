//=============================================================================
//  Include Files
//=============================================================================
#include "dd_pfi.h"
#include "dd_stm_interface.h"
#include "io_conversion.h"
#include "io_config_fuel.h"
#include "io_config_tpu.h"
#include "io_interface_eng.h"
#include "t_custom.h"

//=============================================================================
//  local micra definitions
//=============================================================================
#define PFI_ADJUST_TIME (uint32_t)( 400UL ) //100us
// scale up 8 bits to provide much better resolution in storing a 24 bit value in 32 bits.
#define PFI_PRESERVE_RESOLUTION (8)

//=============================================================================
//  private  Variable Definitions
//=============================================================================
static IO_PFI_Initialization_Parameters_T *PFI_Initialization_Parameters;
static Crank_Cylinder_T  PFI_Cylinder_Event_ID;

static uint8_t           PFI_Injector_Diagnostic;
static uint8_t           PFI_Number_Of_Cylinders;
static uint8_t           PFI_Simultaneous_Delay_Count;
static PFI_Flags_T       PFI_Flags;

/* mcd5417 global ram parameter */
static uint32_t          PFI_Normal_Offset;
static uint32_t          PFI_Trim_Offset;
static uint32_t          PFI_Kinj;
static uint32_t          PFI_Min_Inj_Off;
static uint32_t          PFI_Min_Trim;
static uint32_t          PFI_Edge_Time;
static uint16_t          PFI_Edge_Count;
static uint32_t          PFI_Period;

/* mcd5417 channel ram parameter */
static uint32_t          PFI_Desired_Pulse_Width[PFI_MAX_CYLINDERS];
static uint32_t          PFI_Actual_Pulse_Width[PFI_MAX_CYLINDERS];
static uint32_t          PFI_Boundary_Time[PFI_MAX_CYLINDERS];

//=============================================================================
//  Local Variable Definitions
//=============================================================================
static uint8_t                    PFI_IX_Boundary;
static uint32_t                   PFI_Boundary_Crossed;
static uint32_t                   PFI_Prime_Pulse_Fuel;
static Pfi_Fuel_Delivery_Mode_T   PFI_Fueling_Mode;
static uCrank_Angle_T             PFI_Normal_EOIT[PFI_MAX_CYLINDERS];
static uCrank_Angle_T             PFI_Trim_EOIT[PFI_MAX_CYLINDERS];

static volatile uint32_t          PFI_Time_Per_Boundary_Fraction;


//=============================================================================
// local private function declaration
//=============================================================================
#define PFI_Set_Channel_Update_Flag(in_channel)    (PFI_Flags.U32 |= (0x80000000>>in_channel))
#define PFI_Clear_Channel_Update_Flag(in_channel)  (PFI_Flags.U32 &= ~(0x80000000>>in_channel))

#define PFI_Set_Boundary_Update_Flag(in_channel)    (PFI_Flags.U32 |= (0x08000000>>in_channel))
#define PFI_Clear_Boundary_Update_Flag(in_channel)  (PFI_Flags.U32 &= ~(0x08000000>>in_channel))

static void     PFI_INJ_Boundary(void);
static uint32_t PFI_Calculate_Boundary(uint8_t  in_channel);
static void     PFI_Perform_Boundary_Logic(uint8_t in_channel);

//=============================================================================
// PFI_Calculate_Boundary
//
// @func Description
//
// @parm uint8_t | inCurrentChannel | description.
//
// @rdesc time per boundary fraction
//
// @end
//=============================================================================
static uint32_t PFI_Calculate_Boundary(uint8_t in_channel )
{
	uint8_t        counter;
	uint32_t       angle_per_cylinder_event;
	uint32_t       angle_per_boundary_frac;
	uint32_t       angle;
	uint32_t       normal_eoit_to_nextboundary;
	uint32_t       trim_eoit_to_nextboundary;

	// Get the time at the last lo res
	angle = CRANK_Get_Parameter( CRANK_PARAMETER_CYLINDER_EVENT_ANGLE, 0, 0 );
	angle_per_cylinder_event = CRANK_Convert_Angle_To_uCrank_Angle( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / PFI_Number_Of_Cylinders, 0 );

	// total number of degrees including the boundry fraction
	angle_per_boundary_frac = PFI_Initialization_Parameters->boundary_fraction;

	for( counter = 0; counter < PFI_Number_Of_Cylinders; counter++ ) {
		if( counter == in_channel ) {
			PFI_Boundary_Time[ counter ] = ( PFI_Number_Of_Cylinders
											* angle_per_cylinder_event )
											+ angle_per_boundary_frac
											+ angle;
		} else if( counter < in_channel ) {
			PFI_Boundary_Time[ counter ] = ( ( PFI_Number_Of_Cylinders 
											- in_channel
											+ counter )
											* angle_per_cylinder_event )
											+ angle_per_boundary_frac
											+ angle;
		} else { // counter > in_channel
			PFI_Boundary_Time[ counter ] = ( ( counter 
											- in_channel )
											* angle_per_cylinder_event )
											+ angle_per_boundary_frac
											+ angle;
		}
		PFI_Boundary_Time[ counter ] = PFI_Boundary_Time[counter] & UINT24_MAX;
	}

	PFI_Time_Per_Boundary_Fraction = angle_per_boundary_frac;
	return PFI_Time_Per_Boundary_Fraction;
}

//=============================================================================
// PFI_Set_Channel_Update_Enable
//=============================================================================
void PFI_Set_Channel_Update_Enable(Crank_Cylinder_T in_channel, bool flag)
{
	if (flag == true)
		PFI_Set_Channel_Update_Flag(in_channel);
	else
		PFI_Clear_Channel_Update_Flag(in_channel);
}

//=============================================================================
// PFI_Set_Boundary_Update_Enable
//=============================================================================
void PFI_Set_Boundary_Update_Enable(Crank_Cylinder_T in_channel, bool flag)
{
	if (flag == true)
		PFI_Set_Boundary_Update_Flag(in_channel);
	else
		PFI_Clear_Boundary_Update_Flag(in_channel);
}

//=============================================================================
// PFI_Set_Pulse_Width
//=============================================================================
void PFI_Set_Pulse_Width(
   Crank_Cylinder_T  in_channel,
   uint32_t          in_pulse_width,
   uint8_t           in_time_precision,
   uint8_t           in_time_resolution )
{
	uint32_t    base_frequency;

	base_frequency = TPU_TIMER_Get_Base_Frequency(PFI_FUEL_TPU_INDEX,  PFI_Desfi[ in_channel ] );

	PFI_Desired_Pulse_Width[in_channel] = \
		IO_Convert_Time_To_Count(in_pulse_width, base_frequency, in_time_precision, in_time_resolution);
}

//=============================================================================
// PFI_Set_Angle
//=============================================================================
void PFI_Set_Angle(Pfi_Angle_T in_angle_type, uint32_t in_angle, uint8_t in_precision)
{
	uCrank_Angle_T  in_angle_limit;
	uCrank_Angle_T  eoit_angle_in_ucrank;
	Crank_Cylinder_T cylinder_id;

	cylinder_id    = CRANK_Get_Cylinder_ID();
	in_angle_limit =  CRANK_Convert_Angle_To_uCrank_Angle( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION, 0 );
	eoit_angle_in_ucrank = CRANK_Convert_Angle_To_uCrank_Angle(in_angle, 0);

	if ( in_precision ) {
		eoit_angle_in_ucrank = eoit_angle_in_ucrank / in_precision;
	}

	if ( eoit_angle_in_ucrank >= in_angle_limit ) {
		eoit_angle_in_ucrank = in_angle_limit;
	}

	/* convert application EOIT angle (the last boundary event to EOIT) to 
	* MCD EOIT angle (EOIT to next boundary event, MCD-5417 Rev 2.0)
	*/
	eoit_angle_in_ucrank = in_angle_limit - eoit_angle_in_ucrank;

	switch( in_angle_type ) {
	case PFI_ANGLE_NORMAL:
		PFI_Normal_EOIT[cylinder_id] = in_angle;
		PFI_Normal_Offset            = eoit_angle_in_ucrank;
		break;
	case PFI_ANGLE_TRIM:
		PFI_Trim_EOIT[cylinder_id] = in_angle;
		PFI_Trim_Offset            = eoit_angle_in_ucrank;
		break;
	default:
		break;
	}
}

//=============================================================================
// PFI_Set_Fueling_Mode
//=============================================================================
void PFI_Set_Fueling_Mode(Pfi_Fuel_Delivery_Mode_T   in_mode)
{
	PFI_Flags.F.PFI_DELIVERY_MODE = in_mode;
}

//=============================================================================
// PFI_Perform_Simultaneous_Delivery
//=============================================================================
static void PFI_Perform_Simultaneous_Delivery( void )
{
	uint8_t        counter;
	uint32_t       time;
	uint32_t       desired_pulse_width;
	uint32_t       offset;

	/* Get the time at the last lo res */
	time = CRANK_Get_Parameter( CRANK_PARAMETER_CYLINDER_EVENT_ANGLE, 0, 0 );

	for(counter = 0; counter < PFI_Number_Of_Cylinders; counter++ ) {
	   /* Write values to Boundary_Angle (all fuel channels) and
	    * DESFIE_Normal_Offset such that the end-of-injection target (EOIT1) for
	    * each fuel channel is equal to (or less than) the current timer value,
	    * to start at once on all fuel channels simultaneously
	    */
		if (counter == CRANK_Get_Cylinder_ID())  {
			desired_pulse_width = 0;
		} else {
			desired_pulse_width = PFI_Desired_Pulse_Width[counter];
		}
		/* convert boundary angle to counter, and sub current time */
		offset = PFI_Boundary_Time[counter] - time;

		MCD5417_Update_Boundary( 
			PFI_FUEL_TPU_INDEX,
			PFI_Desfi[counter],
			desired_pulse_width,
			PFI_Boundary_Time[counter],
			offset,//PFI_Normal_Offset,
			offset);

		MCD5417_Set_AFPW(PFI_FUEL_TPU_INDEX, PFI_Desfi[counter], 0);
	}
}

//=============================================================================
// PFI_Update_Engine_Data
//=============================================================================
static void PFI_Update_Engine_Data(uint8_t in_channel)
{
	uint32_t period;
	EPPwMT_Coherent_Edge_Time_And_Count_T edge_time_and_count;

	MCD5408_Get_Coherent_Edge_Time_And_Count(EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT, &edge_time_and_count );
	period = MCD5408_Get_Period(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT);

	// Update engine data for DESFI MCD
	MCD5417_Update_Engine_Data(
		PFI_FUEL_TPU_INDEX,
		PFI_Desfi[in_channel], // global data update, channel independent
		edge_time_and_count.Time,
		edge_time_and_count.Count,
		period);
}

//=============================================================================
// PFI_Perform_Boundary_Logic
//=============================================================================
static void PFI_Perform_Boundary_Logic( uint8_t in_channel )
{
	uint32_t       desired_pulse_width;

	desired_pulse_width =0;

	MCD5417_Update_Boundary(
		PFI_FUEL_TPU_INDEX,
		PFI_Desfi[in_channel],
		desired_pulse_width,
		PFI_Boundary_Time[in_channel],
		PFI_Normal_Offset,
		PFI_Trim_Offset );

	PFI_Actual_Pulse_Width[in_channel] = MCD5417_Get_AFPW(PFI_FUEL_TPU_INDEX, PFI_Desfi[in_channel]);
	MCD5417_Set_AFPW(PFI_FUEL_TPU_INDEX, PFI_Desfi[in_channel], 0 );

	// If the hardware has slow fault detection then this code should be activated so that
	// false faults are not reported.
	// Set a flag indicating that we have crossed the boundary:
	PFI_Boundary_Crossed = Insert_Bits( PFI_Boundary_Crossed, true, in_channel, 1 );
}

//=============================================================================
// PFI_Update_Channel
//=============================================================================
void PFI_Update_Channel(void)
{
	uint8_t counter;

	/* update related channel */
	for(counter = 0; counter < PFI_MAX_CYLINDERS; counter ++) {
		if( PFI_Flags.U32 & (0x80000000 >> counter)) {
			MCD5417_Update_Channel( PFI_FUEL_TPU_INDEX, 
									PFI_Desfi[ counter ],
									PFI_Desired_Pulse_Width[ counter ],
									PFI_Boundary_Time[ counter ],
									PFI_Normal_Offset,
									PFI_Trim_Offset );
		}
	}

	/* reset all update flag */
	PFI_Flags.U32 &= 0x0FFFFFFF;
}

//=============================================================================
// PFI_Update_Channel
//=============================================================================
void PFI_Update_Boundary(void)
{
	uint8_t counter;

	/* update related channel */
	for(counter = 0; counter < PFI_MAX_CYLINDERS; counter ++) {
		if( PFI_Flags.U32 & (0x08000000 >> counter)) {
			MCD5417_Update_Boundary( PFI_FUEL_TPU_INDEX, 
									PFI_Desfi[ counter ],
									PFI_Desired_Pulse_Width[ counter ],
									PFI_Boundary_Time[ counter ],
									PFI_Normal_Offset,
									PFI_Trim_Offset );
			PFI_Actual_Pulse_Width[counter] = MCD5417_Get_AFPW( PFI_FUEL_TPU_INDEX, PFI_Desfi[counter] );
			MCD5417_Set_AFPW(PFI_FUEL_TPU_INDEX, PFI_Desfi[counter], 0 );
		}
	}

	/* reset all update flag */
	PFI_Flags.U32 &= 0xF0FFFFFF;
}

//=============================================================================
// PFI_INJ_Boundary, called in PFI boundary tooth event
//=============================================================================
void PFI_Perform_Injection_Tasks( void )
{
	uint8_t counter;

	/* abort the simultaneous injection pulse */
	PFI_Calculate_Boundary( PFI_IX_Boundary );
	PFI_Perform_Boundary_Logic(PFI_IX_Boundary);
}

//=============================================================================
// PFI_Process_Cylinder_Event
//=============================================================================
void PFI_Process_Cylinder_Event(void)
{
	Crank_Cylinder_T  next_cylinder_id;
	Crank_Cylinder_T  current_cylinder_id;

	if (PFI_Flags.F.PFI_DELIVERY_MODE == PFI_FUEL_DELIVERY_SIMULTANEOUS) {
		/* update current cylinder channel boundary */
		current_cylinder_id = CRANK_Get_Cylinder_ID();
		next_cylinder_id = CRANK_Get_Next_Cylinder_ID();

		PFI_Calculate_Boundary(next_cylinder_id);
		PFI_Update_Engine_Data(current_cylinder_id);

		/* perform three channel simultaneous injection */
		PFI_Perform_Simultaneous_Delivery();

		/* init PFI_IX_Boundary for sequential mode use */
		PFI_IX_Boundary = next_cylinder_id;

		PFI_Update_Channel();
	} else {
		/* Check to see if a boundary occurred in the previous lo-res interval */
		if ( !Extract_Bits(PFI_Boundary_Crossed, PFI_IX_Boundary, 1) ) {
			// Since no boundary occurred, perform the boundary logic now:
			// PFI_Calculate_Boundary( PFI_IX_Boundary );
			// PFI_Update_Engine_Data(PFI_IX_Boundary);
			PFI_Perform_Boundary_Logic( PFI_IX_Boundary );
		}
		PFI_Update_Engine_Data(PFI_IX_Boundary);

		// Get the cylinder ID for the upcoming lo-res interval:
		PFI_Cylinder_Event_ID = CRANK_Get_Next_Cylinder_ID();
		// Clear a flag to indicate that we are expecting a boundary in this lo-res:
		PFI_Boundary_Crossed = Insert_Bits( PFI_Boundary_Crossed, false, PFI_Cylinder_Event_ID, 1 );
		PFI_IX_Boundary = PFI_Cylinder_Event_ID;

		/* perform all channels prime pulse and trim pulse(untarget pulse) */
		PFI_Update_Channel();
	}
}

//=============================================================================
// PFI_Reset_Parameters
//=============================================================================
void PFI_Reset_Parameters( void )
{
	uint8_t counter;

	PFI_Normal_Offset = 0;
	PFI_Trim_Offset = 0;
	PFI_Boundary_Crossed = 0x0;

	PFI_Flags.U32 = 0x0;
}

//=============================================================================
// PFI_Initialize
//=============================================================================
void PFI_Initialize(IO_PFI_Initialization_Parameters_T  * const  in_initialization_parameters )
{
	uint8_t     counter;

	PFI_Number_Of_Cylinders = CRANK_Get_Number_Of_Cylinders();
	PFI_Initialization_Parameters = in_initialization_parameters;

	for( counter = 0; counter < PFI_Number_Of_Cylinders; counter++ ) {
		MCD5417_Initialize_Channel(PFI_FUEL_TPU_INDEX, &TPU, PFI_Desfi[counter]);
	}

	PFI_Reset_Parameters();
}

//=============================================================================
// PFI_Enable_Channel
//=============================================================================
void PFI_Enable_Channel(Crank_Cylinder_T  in_cylinder )
{
	MCD5417_Update_Channel( PFI_FUEL_TPU_INDEX, 
							PFI_Desfi[in_cylinder],
							PFI_Desired_Pulse_Width[in_cylinder],
							PFI_Boundary_Time[in_cylinder],
							PFI_Normal_Offset,
							PFI_Trim_Offset );
}

//=============================================================================
// PFI_Disable_Channel
//=============================================================================
void PFI_Disable_Channel(Crank_Cylinder_T  in_cylinder )
{
	PFI_Desired_Pulse_Width[ in_cylinder ] = 0;
	MCD5417_Update_Channel( PFI_FUEL_TPU_INDEX,
							PFI_Desfi[ in_cylinder ],
							0,
							PFI_Boundary_Time[ in_cylinder ],
							PFI_Normal_Offset,
							PFI_Trim_Offset );
}

//=============================================================================
// PFI_Enable_Trim_Pulses
//=============================================================================
void PFI_Enable_Trim_Pulses( uint8_t index)
{
	MCD5417_Set_Multiple_Trim(PFI_FUEL_TPU_INDEX, PFI_Desfi[index], 1 );
}

//=============================================================================
// PFI_Disable_Trim_Pulses
//=============================================================================
void PFI_Disable_Trim_Pulses( uint8_t index)
{
	MCD5417_Set_Multiple_Trim( PFI_FUEL_TPU_INDEX,PFI_Desfi[index], 0 );
}

//=============================================================================
// PFI_Set_Minimum_Off_Time
//=============================================================================
void PFI_Set_Minimum_Off_Time(
   uint32_t    in_min_off_time,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution )
{
   uint32_t    conversion_time;
   uint32_t    base_frequency;

   base_frequency = TPU_TIMER_Get_Base_Frequency(PFI_FUEL_TPU_INDEX, PFI_Desfi[ 0 ] );

   conversion_time = IO_Convert_Time_To_Count(
      in_min_off_time,
      base_frequency,
      in_time_precision,
      in_time_resolution ); 

   MCD5417_Set_Min_Inj_Off( PFI_FUEL_TPU_INDEX, conversion_time );
}

//=============================================================================
// PFI_Set_Min_Trim_Pulse_Width
//=============================================================================
void PFI_Set_Min_Trim_Pulse_Width(
   uint32_t    in_min_pulse_width,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution )
{
   uint32_t    conversion_time;
   uint32_t    base_frequency;

   base_frequency = TPU_TIMER_Get_Base_Frequency(PFI_FUEL_TPU_INDEX, PFI_Desfi[ 0 ] );

   if ( !in_time_precision && !in_time_resolution )
   {
      conversion_time = in_min_pulse_width;
   }
   else
   {
      conversion_time = IO_Convert_Time_To_Count(
         in_min_pulse_width,
         base_frequency,
         in_time_precision,
         in_time_resolution );
   }

   MCD5417_Set_Min_Trim( PFI_FUEL_TPU_INDEX, conversion_time );
}

//=============================================================================
// PFI_Set_Injector_Offset
//=============================================================================
void PFI_Set_Injector_Offset(
   uint32_t    in_offset,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution )
{
	uint32_t    conversion_time;
	uint32_t    base_frequency;

	base_frequency = TPU_TIMER_Get_Base_Frequency(PFI_FUEL_TPU_INDEX, PFI_Desfi[ 0 ] );

	conversion_time = IO_Convert_Time_To_Count(
		in_offset,
		base_frequency,
		in_time_precision,
		in_time_resolution );

	MCD5417_Set_Kinj( PFI_FUEL_TPU_INDEX, conversion_time );
}

//=============================================================================
//  Include Files
//=============================================================================
#include "dd_pfi.h"
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
static uCrank_Angle_T             PFI_Normal_EOIT;
static uCrank_Angle_T             PFI_Trim_EOIT;

static volatile uint32_t          PFI_Time_Per_Boundary_Fraction;


//=============================================================================
// local private function declaration
//=============================================================================
#define PFI_Set_Channel_Update_Flag(in_channel)    (PFI_Flags.u32 |= (0x80000000>>in_channel))
#define PFI_Clear_Channel_Update_Flag(in_channel)  (PFI_Flags.u32 &= ~(0x80000000>>in_channel))


static void     PFI_INJ_Boundary(void);
static uint32_t PFI_Calculate_Boundary(uint8_t  in_channel);
static void     PFI_Perform_Boundary_Logic(uint8_t in_channel);
static void     PFI_Enable_Sequential(uint8_t in_delay_count);

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

static void PFI_Set_Channel_Update_Enable(Crank_Cylinder_T in_channel, bool flag)
{
	if (flag = true)
		PFI_Set_Channel_Update_Flag(in_channel);
	else
		PFI_Clear_Channel_Update_Flag(in_channel);
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
// PFI_Update_Channel
//=============================================================================
void PFI_Update_Channel(void)
{
	uint8_t counter;

	/* update related channel */
	for(counter = 0; counter < PFI_MAX_CYLINDERS; counter ++)
		if( PFI_Flags.u32 & (0x8000000 >> counter)) {
			MCD5417_Update_Channel( PFI_FUEL_TPU_INDEX, 
									PFI_Desfi[ counter ],
									PFI_Desired_Pulse_Width[ counter ],
									PFI_Boundary_Time[ counter ],
									PFI_Normal_Offset,
									PFI_Trim_Offset );
		}
	}
}

//=============================================================================
// PFI_Update_Channel
//=============================================================================
void PFI_Update_Boundary(Crank_Cylinder_T in_channel)
{
	if( PFI_Flags.Update_Enabled ) {
		MCD5417_Update_Boundary( PFI_FUEL_TPU_INDEX, 
								PFI_Desfi[ in_channel ],
								PFI_Desired_Pulse_Width[ in_channel ],
								PFI_Boundary_Time[ in_channel ],
								PFI_Normal_Offset,
								PFI_Trim_Offset );
	}
}

//=============================================================================
// PFI_Set_Angle
//=============================================================================
void PFI_Set_Angle(Pfi_Angle_T in_angle_type, uint32_t in_angle, uint8_t in_precision)
{
	uCrank_Angle_T  in_angle_limit;
	uCrank_Angle_T  eoit_angle_in_ucrank;

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
		PFI_Normal_EOIT      = in_angle;
		PFI_Normal_Offset    = eoit_angle_in_ucrank;
		break;
	case PFI_ANGLE_TRIM:
		PFI_Trim_EOIT        = in_angle;
		PFI_Trim_Offset      = eoit_angle_in_ucrank;
		break;
	default:
		break;
	}
}

//=============================================================================
// PFI_Set_Angle
//=============================================================================
void PFI_Set_Illegal_Angle(Pfi_Angle_T in_angle_type)
{
	uint32_t current_time;
	
	current_time = TPU_TIMER_Get_Value(TPU_INDEX_0, TPU_TCR1_TIME_BASE);

	switch( in_angle_type ) {
	case PFI_ANGLE_NORMAL:
		PFI_Normal_Offset    = current_time;
		break;
	case PFI_ANGLE_TRIM:
		PFI_Trim_Offset      = current_time;
		break;
	default:
		break;
	}
}



//=============================================================================
// PFI_Set_Fueling_Mode
//=============================================================================
void PFI_Set_Fueling_Mode(
   Pfi_Fuel_Delivery_Mode_T   in_mode,
   uint8_t                    in_delay_count)
{
   PFI_Fueling_Mode = in_mode;
   
   PFI_Simultaneous_Delay_Count = in_delay_count;

   if( in_mode == PFI_FUEL_DELIVERY_SEQUENTIAL )
   {
      PFI_Enable_Sequential( PFI_Simultaneous_Delay_Count );
   }
}



//=============================================================================
// PFI_Set_Delay_Counter
//=============================================================================
void PFI_Set_Delay_Counter(
   uint8_t     in_sequential_delay_counter )
{
   PFI_Simultaneous_Delay_Count = in_sequential_delay_counter;
}


//=============================================================================
// PFI_Perform_Simultaneous_Delivery
//=============================================================================
void PFI_Perform_Simultaneous_Delivery( void )
{
	uint8_t        counter;
	uint32_t       time;

	// Get the time at the last lo res
	time = CRANK_Get_Parameter( CRANK_PARAMETER_CYLINDER_EVENT_TIME, 0, 0 );

	// time = (time + PFI_ADJUST_TIME ) & UINT24_MAX;//(2 * time_per_cylinder_event) ) & UINT24_MAX;

	for(counter = 0; counter < PFI_Number_Of_Cylinders; counter++ ) {
	   /* Write values to Boundary_Angle (all fuel channels) and
	    * DESFIE_Normal_Offset such that the end-of-injection target (EOIT1) for
	    * each fuel channel is equal to (or less than) the current timer value,
	    * to start at once on all fuel channels simultaneously
	    */
		if (counter != CRANK_Get_Cylinder_ID()) {
			MCD5417_Update_Boundary( 
				PFI_FUEL_TPU_INDEX,
				PFI_Desfi[ counter ],
				PFI_Desired_Pulse_Width[ counter ],
				time,
				time,//PFI_Normal_Offset,
				time );
		}

		MCD5417_Set_AFPW( PFI_FUEL_TPU_INDEX, PFI_Desfi[ counter ], 0 );
		// MCD5417_Set_Min_Inj_Off( PFI_FUEL_TPU_INDEX, PFI_Desfi[ counter ], 0);
	}

	PFI_Flags.Prime_Pulse_Complete = false;
}

//=============================================================================
// PFI_Enable_Sequential
//=============================================================================
static void PFI_Enable_Sequential(uint8_t in_delay_count )
{
	uint8_t           counter;
	Crank_Cylinder_T  cylinder_id;

	// We want one cylinder in the future.
	cylinder_id = CRANK_Get_Next_Cylinder_ID();

	PFI_IX_Boundary = cylinder_id;

	// calculate boundry
	PFI_Calculate_Boundary( cylinder_id );

	// Setup next cylinder and previous cylinders based on application value
	for( counter = 0; counter <= in_delay_count; counter++ ) {
		PFI_Perform_Boundary_Logic( cylinder_id );

		if( cylinder_id == 0 ) {
			cylinder_id = PFI_Number_Of_Cylinders - 1;
		} else {
			cylinder_id--;
		}
	}
}

//=============================================================================
// PFI_Perform_Boundary_Logic
//=============================================================================
static void PFI_Perform_Boundary_Logic( uint8_t in_channel )
{
	uint32_t period;
	EPPwMT_Coherent_Edge_Time_And_Count_T edge_time_and_count;
	uint32_t       desired_pulse_width;

	MCD5408_Get_Coherent_Edge_Time_And_Count(EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT, &edge_time_and_count );
	period = MCD5408_Get_Period(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT);

	// Update engine data for DESFI MCD
	MCD5417_Update_Engine_Data(
		PFI_FUEL_TPU_INDEX,
		PFI_Desfi[ in_channel ], // global data update, channel independent
		edge_time_and_count.Time,
		edge_time_and_count.Count,
		period );

	if(Startup_Counter<PFI_MAX_CYLINDERS+1) {
		desired_pulse_width =0;
	} else {
		desired_pulse_width = PFI_Desired_Pulse_Width[ in_channel ];
	}

	// Update boundary:
	// MCD5417_Update_Boundary(
	// 	PFI_FUEL_TPU_INDEX,
	// 	PFI_Desfi[ in_channel ],
	// 	//PFI_Desired_Pulse_Width[ in_channel ],
	// 	desired_pulse_width,
	// 	PFI_Boundary_Time[ in_channel ],
	// 	PFI_Normal_Offset,
	// 	PFI_Trim_Offset );

	// PFI_Actual_Pulse_Width[ in_channel ] = MCD5417_Get_AFPW( PFI_FUEL_TPU_INDEX, PFI_Desfi[ in_channel ] );
	// MCD5417_Set_AFPW(PFI_FUEL_TPU_INDEX, PFI_Desfi[ in_channel ], 0 );

	// If the hardware has slow fault detection then this code should be activated so that
	// false faults are not reported.
	// Set a flag indicating that we have crossed the boundary:
	PFI_Boundary_Crossed = Insert_Bits( PFI_Boundary_Crossed, true, in_channel, 1 );
}

//=============================================================================
// PFI_Process_Cylinder_Event
//=============================================================================
void PFI_Process_Cylinder_Event(void)
{
#if 0
	uint32_t          cylinder_event_period;
	uint32_t          boundary;
	uint8_t           channel;

	if (PFI_Fueling_Mode == PFI_FUEL_DELIVERY_SEQUENTIAL) {
		// Check to see if a boundary occurred in the previous lo-res interval:
		if ( !Extract_Bits(PFI_Boundary_Crossed, PFI_IX_Boundary, 1) ) {
			// Since no boundary occurred, perform the boundary logic now:
			PFI_INJ_Boundary();
		}

		// Get the cylinder ID for the upcoming lo-res interval:
		PFI_Cylinder_Event_ID = CRANK_Get_Next_Cylinder_ID();

		// Clear a flag to indicate that we are expecting a boundary in this lo-res:
		PFI_Boundary_Crossed = Insert_Bits( PFI_Boundary_Crossed, false, PFI_Cylinder_Event_ID, 1 );

		PFI_IX_Boundary = PFI_Cylinder_Event_ID;

		cylinder_event_period = CRANK_Get_Parameter( CRANK_PARAMETER_LO_RES_REFERENCE_PERIOD, 0, 0 );
		channel = CRANK_Get_Cylinder_ID();

		MCD5417_Update_Channel(PFI_FUEL_TPU_INDEX,
			PFI_Desfi[ channel ],
			PFI_Desired_Pulse_Width[ channel ],
			PFI_Boundary_Time[ channel ],
			PFI_Normal_Offset,
			PFI_Trim_Offset );
	}
#endif
}

//=============================================================================
// PFI_Update_Prime_Pulse_Complete
//=============================================================================
void PFI_Update_Prime_Pulse_Complete( void )
{
   PFI_Prime_Pulse_Fuel = MCD5417_Get_AFPW( PFI_FUEL_TPU_INDEX, PFI_Desfi[ 0 ] );//PFI_Actual_Pulse_Width[ 0 ];

   if( ( PFI_Fueling_Mode             == PFI_FUEL_DELIVERY_SIMULTANEOUS       )
    && ( PFI_Desired_Pulse_Width[ 0 ] <= PFI_Prime_Pulse_Fuel )
    && ( PFI_Prime_Pulse_Fuel         != 0                    ) )
   {
      PFI_Flags.Prime_Pulse_Complete = true;
   }
   else
   {
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

	PFI_Number_Of_Cylinders = CRANK_Get_Number_Of_Cylinders();

	for( counter = 0; counter < PFI_Number_Of_Cylinders; counter++ ) {
		MCD5417_Shutdown(PFI_FUEL_TPU_INDEX, PFI_Desfi[counter]);
		MCD5417_Initialize_Channel(PFI_FUEL_TPU_INDEX, &TPU, PFI_Desfi[counter]);
	}

	for (counter = 0; counter < PFI_Number_Of_Cylinders; counter++)
		MCD5417_Set_AFPW(PFI_FUEL_TPU_INDEX, PFI_Desfi[counter], 0);
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

	//  if( PFI_Fueling_Mode == PFI_FUEL_DELIVERY_SIMULTANEOUS )
	//  {
	//    PFI_Perform_Simultaneous_Delivery();
	//   }

	//   PFI_Flags.Update_Enabled = true;

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


//=============================================================================
// PFI_Set_Pulse_Width
//=============================================================================
void PFI_Set_Update_Enable(
   bool        in_enable )
{
   PFI_Flags.Update_Enabled = in_enable;
}

//=============================================================================
// PFI_Set_All_Pulse_Widths
//=============================================================================
void PFI_Set_All_Pulse_Widths(
   uint32_t    in_pulse_width,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution )
{
  // save Fuel Pluse width for other usage
   uint32_t base_frequency;
   uint8_t  counter;

   base_frequency =  TPU_TIMER_Get_Base_Frequency(PFI_FUEL_TPU_INDEX,  PFI_Desfi[ 0 ] );

   for( counter = 0; counter < PFI_Number_Of_Cylinders; counter++ )
   {
      PFI_Desired_Pulse_Width[ counter ] = IO_Convert_Time_To_Count(
         in_pulse_width,
         base_frequency,
         in_time_precision,
         in_time_resolution ); 

     MCD5417_Update_Channel(   
	 	PFI_FUEL_TPU_INDEX, PFI_Desfi[ counter ],
                              PFI_Desired_Pulse_Width[ counter ],
                              PFI_Boundary_Time[ counter ],
                              PFI_Normal_Offset,
                              PFI_Trim_Offset );
   }

}

//=============================================================================
// PFI_INJ_Boundary
//=============================================================================
void PFI_INJ_Boundary( void )
{
   if (PFI_Fueling_Mode == PFI_FUEL_DELIVERY_SEQUENTIAL)
   {
      PFI_Calculate_Boundary( PFI_IX_Boundary );
      PFI_Perform_Boundary_Logic( PFI_IX_Boundary );
   }
}

//=============================================================================
// PFI_INJ_Boundary
//=============================================================================
void PFI_Perform_Injection_Tasks( void )
{
   PFI_INJ_Boundary();
}





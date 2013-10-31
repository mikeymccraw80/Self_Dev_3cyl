

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "lux_type.h"
#include "lux_lkup.h"
#include "lux_math.h"
/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "es_knock.h"
#include "hal.h"
#include "HLS.h"
#include "hal_knock.h"
#include "hal_emulated_eeprom.h"
#include "v_esc.h"
#include "esc_cal.h"


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  None */

/* ============================================================================ *\
 * Local type declarations.
\* ============================================================================ */
typedef uint32_t               Multiplier_0_to_1_L ;
#define Prec_Multiplier_0_to_1_L ( Prec_Multiplier_0_to_1 / 256.0 )
#define Min_Multiplier_0_to_1_L  ( Min_Multiplier_0_to_1 )
#define Max_Multiplier_0_to_1_L  ( 65535 * Prec_Multiplier_0_to_1_W )


/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */

#pragma section DATA " " ".nc_nvram"
      Volt0to5Volts_W               FilteredMAD[num_cyl] ;            /* filtered MAD */
#pragma section DATA " " ".bss"

T_CRANK_ANGLEa              KnockWindowLength ; /*wingate length for s12*/
T_CRANK_ANGLEa            KnockWindowStartAngleVsTDC ;
ESCCylinderType               EscCylinder ;           /* cylinder on which knock calculations are performed */
bool                                ESCGain_High[num_cyl];                 /* gain for this cylinder */
Volt0to5Volts_W               ADESC[num_cyl] ;                  /* knock data of  fir */
Volt0to5Volts_W               IntegratorAverage[num_cyl] ;      /* filtered value */
Volt0to5Volts_W               RawMAD[num_cyl] ;                 /* raw (instant) MAD */
Multiplier_0_to_64            MADMultiplier[num_cyl] ;          /* MAD Multiplier */
Volt0to5Volts_W               KnockThreshold[num_cyl] ;         /* knock threshold */

/* ============================================================================ *\
 * Local variables.
\* ============================================================================ */

Filter_Q_W                    IntAveQ ;                     /* IntegratorAverage filter coefficient */
Every_10th_Loop_Sec_B         MAD_Transient_Timer ;         /* timer for MAD transient mode */
TPS_B                         EscOldTPS ;                   /* 125 ms old TPS */
RPM_W                         EscOldRPM ;                   /* 125 ms old RPM */
kPa_B                         EscOldMAP ;                   /* 125 ms old NMAPLD */
TPS_B                         EscOldMultiplierTPS ;         /* 15.6 ms old TPS */
RPM_Hi_Res_W                  EscOldMultiplierRPM ;         /* 32.25 ms old RPM */
Every_2nd_Loop_Sec_B          MAD_Mult_TPS_Timer ;          /* Timer for TPS delta */
Every_4th_Loop_Sec_B          MAD_Mult_RPM_Timer ;          /* Timer for RPM delta */

Volt0to5Volts_W       ADESC_DSPKnock[MULTIKNOCK_NUM_FILTERS];
Volt0to5Volts_W       ADESC_Average_Wingateoff[num_cyl] ;              /* raw knock sensor average value when wingate off */
EscFlag_Type            EscFlag ;
bool Multiplier_Delta_RPM;
bool Multiplier_Delta_TPS;
bool MAD_Transient_Detected;
bool MAD_Filtering_Enabled;


/* ============================================================================ *\
 * Local INLINE functions and #define function-like macros.
\* ============================================================================ */



#define MADTransient()          (EscFlag.MADTransientDetected == (bitfield8_t) true)
#define SetMADTransient()       (EscFlag.MADTransientDetected = (bitfield8_t) true)
#define ClearMADTransient()     (EscFlag.MADTransientDetected = (bitfield8_t) false)

#define EnableESC()             (EscFlag.EscEnabled = (bitfield8_t) true)
#define DisableESC()            (EscFlag.EscEnabled = (bitfield8_t) false)

/* ============================================================================ *\
 * Local function prototypes.
\* ============================================================================ */


/* ============================================================================ *\
 * FUNCTION: ConfigESC
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   None
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Configures and initialises all ESC detection, fast and slow variables.
 * Called at initialisation only.
\* ============================================================================ */
static void ConfigESC( void );


/* ============================================================================ *\
 * FUNCTION: DetermineESCEnabled
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Determines the ESC enabled status. Sets the fast retard to 0 if the ESC is
 * not enabled.
 * Called every 15.625 msec
\* ============================================================================ */
static void DetermineESCEnabled( void );


/* ============================================================================ *\
 * FUNCTION: CalculateKnockMultiplier
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Calculates the knock multiplier for all cylinders based on cylinder load and
 * transient conditions.
 * Called every 15.625 msec.
\* ============================================================================ */
static void CalculateKnockMultiplier( void );


/* ============================================================================ *\
 * FUNCTION: CalculateIntAveQ
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   Filter_Q_W   IntAveQ        - filter coefficient
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Calculates the integrator averge filter coefficient before compensation
 * for knock present conditions.
 * Called every 15.625 msec.
\* ============================================================================ */
static void CalculateIntAveQ( void );


/* ============================================================================ *\
 * FUNCTION: DetermineMADEnabled
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Determines the standard MAD enabling conditions.
 * Called every 125 msec.
\* ============================================================================ */
static void DetermineMADEnabled( void );


/* ============================================================================ *\
 * FUNCTION: UpdateDSPKnockGain
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Calculates the DSP Knock gain for each cylinder and adjusts the integrator
 * averages if there is a jump in gain.
 * Called every 125 msec in RunSpark.
\* ============================================================================ */
//static void UpdateDSPKNOCKGain( void );


/* ============================================================================ *\
 * FUNCTION: FilterIntegratorAverage
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Updates the integrator average for the cylinder which has just fired.
 * Called every ESC event (end of Wingate)
\* ============================================================================ */
static void FilterIntegratorAverage( void );


/* ============================================================================ *\
 * FUNCTION: CalculateMAD
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   Volt0to5Volts_W    ADESCRAW          - IRIC sample and hold output raw voltage
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Updates the MAD for the cylinder which has just fired.
 * Called every ESC event (end of Wingate)
\* ============================================================================ */
static void CalculateMAD( void );


/* ============================================================================ *\
 * FUNCTION: CalculateKnockThreshold
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Updates the knock threshold for the cylinder which has just fired.
 * Called every ESC event (end of Wingate)
\* ============================================================================ */
static void CalculateKnockThreshold( void );


/*===========================================================*\
 * InitialiseESC
\*===========================================================*/
 void InitialiseESC( void )
{
uint8_t  cylinder;

    /*  Initialise the ESC system */
    ConfigESC() ;


    /*  Disable the MAD filtering */
    EscFlag.MADFilteringEnabled = (bitfield8_t) false;

    MAPStartup = Manifold_Air_Pressure() ;
    /*  -------------------------------------------------------- */
    /*  Initialisation of parameters for transient determination */
    /*  -------------------------------------------------------- */
    
    EscOldTPS = Throttle_Position_Value() ;
    EscOldRPM = HAL_Eng_Get_Engine_Speed();
    EscOldMAP = Manifold_Air_Pressure() ;

    EscOldMultiplierTPS = Throttle_Position_Value() ;
    EscOldMultiplierRPM = Hi_Res_Engine_Speed_W() ;

  
} /* End of InitialiseESC */


/*===========================================================*\
 * ScheduleKnockSlowBckgLogic
\*===========================================================*/
 void ScheduleKnockSlowBckgLogic( void )
{

    /*---------------------------------------*/
    /*  Filtering Coefficient                */
    /*---------------------------------------*/

    CalculateIntAveQ() ;

    /*-----------------------------------*/
    /*  MAD update enable check          */
    /*-----------------------------------*/

    DetermineMADEnabled() ;

    /*  only if the engine is properly running, execute the following sections */
   // if ( Run_Spark() )
    //{
       /*----------------------------------*/
        /*  Input amplifier gain adjustment */
        /*----------------------------------*/

        //UpdateDSPKNOCKGain() ;
   // }

    /*----------------------------------*/
    /*  update the 125ms old variables  */
    /*----------------------------------*/

    EscOldTPS = Throttle_Position_Value() ;    
    EscOldRPM = HAL_Eng_Get_Engine_Speed();
    EscOldMAP = Manifold_Air_Pressure() ;



} /* End ScheduleKnockSlowBckgLogic */


/*===========================================================*\
 * ESCEvent
\*===========================================================*/
 void ESCEvent( void )
{
 
    /*---------------------------------------*/
    /*  get the raw knock data               */
    /*---------------------------------------*/

    ADESC_Average_Wingateoff[EscCylinder]  = GetIO_MultiKnock_Raw_Sample(MULTIKNOCK_WINDOW_2);
	
    /* Knock AD buffer sum is the summary of 20 knock AD value*/
    /*keep the same of number as xgate part*/
   GetIO_MultiKnock_Intensity_Value(MULTIKNOCK_WINDOW_2, ADESC_DSPKnock );

   /*limit the AD Raw value to a min threshold*/	
    if (ADESC_DSPKnock[0] < K_ADESC_Min_Threshold)
    {
       ADESC_DSPKnock[0] = K_ADESC_Min_Threshold;
    }	   

  /*multi a scl to the AD Raw value*/
    ADESC_DSPKnock[0] = FixMultiplyHighLimit(ADESC_DSPKnock[0], Volt0to5Volts_W, K_ADESC_Scl_Multi, Multiplier_0_to_2, Volt0to5Volts_W);

  /* give the AD value to different cylinder*/
    ADESC[EscCylinder] = ADESC_DSPKnock[0] ;

 

    /*---------------------------------------*/
    /*  Integrator Averaging Filtering       */
    /*---------------------------------------*/

    FilterIntegratorAverage() ;

    /*---------------------------------------*/
    /*  Mean Absolute Deviation              */
    /*---------------------------------------*/

    CalculateMAD() ;

    /*---------------------------------------*/
    /*  Knock threshold                      */
    /*---------------------------------------*/

    CalculateKnockThreshold() ;

    /*---------------------------------------*/
    /*  Knock decision                       */
    /*---------------------------------------*/
    if (    ( ADESC[EscCylinder] > KnockThreshold[EscCylinder] )
        &&  ESCEnabled() )
    {
#if CcSYST_NUM_OF_CYLINDERS == 3
        if(EscCylinder == cyl_1)
         {
           knock_flag_a = true;
         }
         else if(EscCylinder == cyl_2)
         {
           knock_flag_b = true;
         }
         else if(EscCylinder == cyl_3)   
         {
           knock_flag_c = true;
         }
#else
        if(EscCylinder == cyl_1)
         {
           knock_flag_a = true;
         }
         else if(EscCylinder == cyl_2)
         {
           knock_flag_b = true;
         }
         else if(EscCylinder == cyl_3)   
         {
           knock_flag_c = true;
         }
         else
         {
            knock_flag_d =true;
         } 
#endif   
          EscFlag.KnockActive=true ;   
  
           

    }
    else
    {

#if CcSYST_NUM_OF_CYLINDERS == 3
         if(EscCylinder == cyl_1)
         {
           knock_flag_a = false;
         }
         else if(EscCylinder == cyl_2)
         {
           knock_flag_b = false;
         }
         else if(EscCylinder == cyl_3)   
         {
           knock_flag_c = false;
         }
#else
         if(EscCylinder == cyl_1)
         {
           knock_flag_a = false;
         }
         else if(EscCylinder == cyl_2)
         {
           knock_flag_b = false;
         }
         else if(EscCylinder == cyl_3)   
         {
           knock_flag_c = false;
         }
         else
         {
            knock_flag_d = false;
         } 
#endif
	EscFlag.KnockActive=false ;	 
    }
	

} /* End of ESCEvent */



/*===========================================================*\
 * ScheduleKnockFastBckgLogic
\*===========================================================*/
 void ScheduleKnockFastBckgLogic( void )
{

    /* Determine if ESC retard is enabled */
    DetermineESCEnabled() ;

    /*---------------------------------------*/
    /*  Knock multiplier                     */
    /*---------------------------------------*/

    CalculateKnockMultiplier() ;
 
} /* End ScheduleKnockFastBckgLogic */




/*===========================================================*\
 * KnockControl58XReferenceLogic
\*===========================================================*/
 void KnockControl58XReferenceLogic( void )
{
   Table_Index_Type         index_X, index_Y;
   CrankAngleInDeg_W crank_angle_temp;
   crank_angle_temp = Table_2D_W( FSTPWD, Index_Var(HAL_Eng_Get_Engine_Speed(), Prec_RPM_W, 0.0, 400.0, 6400.0, 400.0 ) ) ;
   if(crank_angle_temp >= FixDefConst(0.0, CrankAngleInDeg_W))
    {
      KnockWindowLength = crank_angle_temp - ShortMax;
    }
   else
   {
     KnockWindowLength = V_CRANK_ANGLEa(0.0);
   }  
   /*--- lookup window start angle relative to TDC (-45 to 45 deg) ---*/

   index_X = Index_Var(MAP_W(), Prec_kPa_W, 0.0, 60.0, 100.0, 10.0);
   index_Y = Index_Var(HAL_Eng_Get_Engine_Speed(), 0.125, 0.0, 400.0, 6400.0, 400.0);
   crank_angle_temp = Table_3D_W(FSTRTWD[0], index_X, index_Y, RPM_400to6400by400_Steps) ;
   if(crank_angle_temp >= FixDefConst(0.0, CrankAngleInDeg_W))
    {
      KnockWindowStartAngleVsTDC = crank_angle_temp - ShortMax;
    }
   else
   {
     KnockWindowStartAngleVsTDC = ShortMax +crank_angle_temp;
   }
      

  EscCylinder = (ESCCylinderType) CRANK_Get_Cylinder_ID() ;
  
  SetIO_MultiKnock_Window_Start(MULTIKNOCK_WINDOW_2, KnockWindowStartAngleVsTDC );
  
  SetIO_MultiKnock_Window_End (MULTIKNOCK_WINDOW_2,KnockWindowLength);
  	
  SetIO_MultiKnock_High_Gain(ESCGain_High[EscCylinder]);

} /* End of KnockControl58XReferenceLogic */





/*===========================================================*\
 * ConfigESC
\*===========================================================*/
static void ConfigESC( void )
{
   uint8_t  cylinder;

 if ( Get_EEP_NVM_Fault() )
   /*  non-volatile ram was lost, re-initialise all ESC parameters */
   {
#if CcSYST_NUM_OF_CYLINDERS == 3
      FilteredMAD[cyl_1] = K_MADMax;
      FilteredMAD[cyl_2] = K_MADMax;
      FilteredMAD[cyl_3] = K_MADMax;
#else      
      FilteredMAD[cyl_1] = K_MADMax;
      FilteredMAD[cyl_2] = K_MADMax;
      FilteredMAD[cyl_3] = K_MADMax;
      FilteredMAD[cyl_4] = K_MADMax;
#endif
  
 }

   /*  ---------------------------- */
   /*  initialise ESC volatile data */
   /*  ---------------------------- */
#if CcSYST_NUM_OF_CYLINDERS == 3
   for ( cylinder = cyl_1 ; cylinder <= cyl_3 ; cylinder++ )
#else
   for ( cylinder = cyl_1 ; cylinder <= cyl_4 ; cylinder++ )
#endif
   {
      IntegratorAverage[cylinder] = FixConvert( K_ESCAverageInit, Volt0to5Volts_B, Volt0to5Volts_W ) ;
      /* clear those fields in ESCData which are volatile and un-initialised to 0 */
      ADESC[cylinder] = FixConvert( K_ESCAverageInit, Volt0to5Volts_B, Volt0to5Volts_W ) ;
      RawMAD[cylinder] = K_MADMax ;
      MADMultiplier[cylinder] = 0 ;
      KnockThreshold[cylinder] = 0 ;
      ESCGain_High[cylinder] = false;
   }

   IntAveQ = K_IntegratorFilterSteadyState ;

}


/*===========================================================*\
 * DetermineESCEnabled
\*===========================================================*/
static void DetermineESCEnabled( void )
{
   if (    ( HAL_Eng_Get_Engine_Speed() >= K_ESCEnableRPM )               /* RPM high enough */
        && ( Manifold_Air_Pressure() >= K_ESCEnableMAP )      /* -and- MAP high enough */
        && ( K_ESC_Enable== (bitfield8_t) true)   /* -and- knock logic enabled through calibration  */
        && ( Engine_Running_Time() >= K_ESCEnableRunTime ))
   {
      /*  knock control enabled */
      EnableESC() ;
   }
   else
   {
       /*  knock control is disabled */
       DisableESC() ;
   }
} /* End DetermineESCEnabled */




/*===========================================================*\
 * FilterIntegratorAverage
\*===========================================================*/
static void FilterIntegratorAverage( void )
{
    IntegratorAverage[EscCylinder] = LagFilter( ADESC[EscCylinder],             /* raw value */
                                                      IntegratorAverage[EscCylinder], /* filtered value */
                                                      AverageCoefficient() ) ;                /* filter coefficient */

    /* Check for minimum Average */
    IntegratorAverage[EscCylinder] = Max( IntegratorAverage[EscCylinder],
                                          FixConvert( K_ESCAverageMin, Volt0to5Volts_B, Volt0to5Volts_W ) ) ;

} /* End FilterIntegratorAverage */




/*===========================================================*\
 * CalculateIntAveQ
\*===========================================================*/
static void CalculateIntAveQ( void )
{
    if ( ( SubLimit( ( Throttle_Position_Value() ), EscOldTPS ) > K_DeltaTPSIncThreshold ) ||
         ( SubLimit( ( HAL_Eng_Get_Engine_Speed() ), EscOldRPM ) > K_DeltaRPMIncThreshold ) )
    {
        /* increasing TPS or increasing RPM */
        IntAveQ = K_IntegratorFilterUp ;
    }
    else if ( ( SubLimit( EscOldTPS, ( Throttle_Position_Value() ) ) > K_DeltaTPSDecThreshold ) ||
              ( SubLimit( EscOldRPM, ( HAL_Eng_Get_Engine_Speed()  ) ) > K_DeltaRPMDecThreshold ) )
    {
        /* decreasing TPS or decreasing RPM */
        IntAveQ = K_IntegratorFilterDown ;
    }
    else
    {
        /* steady state condition */
        IntAveQ = K_IntegratorFilterSteadyState ;
    }
} /* End CalculateIntAveQ */




/*===========================================================*\
 * DetermineMADEnabled
\*===========================================================*/
static void DetermineMADEnabled( void )
{
    if (   ( HAL_Eng_Get_Engine_Speed()>= K_MADRPM )
        && ( Manifold_Air_Pressure() >= K_MADMAP ) )
    {
        /* enable MAD update */
        EscFlag.MADFilteringEnabled = (bitfield8_t) true ;
        MAD_Filtering_Enabled = true;
    }
    else
    {
        EscFlag.MADFilteringEnabled = (bitfield8_t) false ;
        MAD_Filtering_Enabled = false;
    }

    /*  check the transient conditions */
    if ( ( SubAbs( Throttle_Position_Value(), EscOldTPS ) > K_MADDeltaTPS ) ||
         ( SubAbs( HAL_Eng_Get_Engine_Speed(), EscOldRPM ) > K_MADDeltaRPM ) ||
         ( SubAbs( Manifold_Air_Pressure(), EscOldMAP ) > K_MADDeltaMAP ) )
    {
        /* transient condition has been met - start new transient period */
        SetMADTransient() ;
        MAD_Transient_Detected = true;
        MAD_Transient_Timer = K_MADTransientTime ;
    }
    else
    {
        /*  no new transient time - check if we have to time out an existing time
         */
        MAD_Transient_Timer = DecB( MAD_Transient_Timer ) ;
        if ( MAD_Transient_Timer == FixDefConst( 0.0, Every_10th_Loop_Sec_B ) )
        {
            ClearMADTransient() ;
            MAD_Transient_Detected = false;
        }
        else
        {
            SetMADTransient() ;
            MAD_Transient_Detected = true;
        }
    }
}                                                          /* End DetermineMADDisabler */


/*===========================================================*\
 * CalculateMAD
\*===========================================================*/
static void CalculateMAD( void )
{
    Volt0to5Volts_W        mad;
    /* first, calculate the RAW MAD */
    RawMAD[EscCylinder] = FixSubLowLimit( IntegratorAverage[EscCylinder],
                                          ADESC[EscCylinder], Volt0to5Volts_W,
                                          FixDefConst( Min_Volt0to5Volts_W, Volt0to5Volts_W ) ) ;

    /* now check if the MAD filtering conditions have been met */
    if ( (EscFlag.MADFilteringEnabled == (bitfield8_t)true) &&             /* MAD update conditions met */
         !MADTransient() &&                                                /* -and- no MAD transient */
         ( IntegratorAverage[EscCylinder] >= ADESC[EscCylinder] ) )        /* -and- RAW MAD is greater than or equal to 0 */
    {
        /* update the MAD */
        mad = LagFilter( RawMAD[EscCylinder],
                               FilteredMAD[EscCylinder],
                               K_MADFilterCoefficient ) ;
        /* limit the MAD */
        mad = Min( mad, K_MADMax ) ;
        FilteredMAD[EscCylinder] = Max( mad, K_MADMin ) ;
    }
} /* End CalculateMAD */



#if 0
/*===========================================================*\
 * UpdateIRICGain
\*===========================================================*/
static void UpdateDSPKNOCKGain( void )
{
   uint8_t cylinder ;
#if CcSYST_NUM_OF_CYLINDERS == 3
   for ( cylinder = cyl_1 ; cylinder <= cyl_3 ; cylinder++ )
#else
   for ( cylinder = cyl_1 ; cylinder <= cyl_4 ; cylinder++ )
#endif
   {
       if (( IntegratorAverage[cylinder] > K_ESCAverageUppThreshold )
	   	 &&(ESCGain_High[cylinder] ==true))
       {
         ESCGain_High[cylinder] =false; 
           
       }
       else if ( IntegratorAverage[cylinder] < K_ESCAverageLowThreshold )
       {
	   ESCGain_High[cylinder] =true;        
       }

   }
} /* End UpdateIRICGain */

#endif
/*===========================================================*\
 * CalculateKnockThreshold
\*===========================================================*/
static void CalculateKnockThreshold( void )
{
   Volt0to5Volts_L noise_band_L ;                             /* MAD*MADMultiplier */
   Volt0to5Volts_W noise_band ;                               /* MAD*MADMultiplier */

   /* calculate the band around the average which is no knock - save as long in
    case of overflow*/
   noise_band_L = FixMultiply( FilteredMAD[EscCylinder], Volt0to5Volts_W,
                               MADMultiplier[EscCylinder], Multiplier_0_to_64,
                               Volt0to5Volts_L ) ;

   /* convert the long to a word and limit for overflow */
   noise_band = ( Volt0to5Volts_W )Min( noise_band_L, FixDefConst( Max_Volt0to5Volts_W, Volt0to5Volts_W ) ) ;

   /*  and add this to the average */
   KnockThreshold[EscCylinder] = AddHighLimit( IntegratorAverage[EscCylinder],
                                               noise_band,
                                               FixDefConst( Max_Volt0to5Volts_W, Volt0to5Volts_W ) ) ;
} /* End CalculateKnockThreshold */




/*===========================================================*\
 * CalculateKnockMultiplier
\*===========================================================*/
uint8_t Vc10msCounter;
static void CalculateKnockMultiplier( void )
{
   Multiplier_0_to_64     mad_mul_offset ;                  /* MAD multiplier offset in transient mode */
   Multiplier_0_to_64     base_mult ;                       /* MAD multiplier */
   Multiplier_0_to_4      PE_mult ;
   Multiplier_0_to_4      load_mult ;

   uint8_t                cylinder ;
   
    Vc10msCounter++;
   /*  first determine delta TPS conditions */
   if ( FixSubAbs( ( Throttle_Position_Value() ), EscOldMultiplierTPS, TPS_B ) > K_MADMultiplierDeltaTPS )
   {
      MAD_Mult_TPS_Timer = K_MADMultTPSTimer ;
      EscFlag.MultiplierDeltaTPS = (bitfield8_t) true ;
      Multiplier_Delta_TPS = true;
   }
   else
   {
      MAD_Mult_TPS_Timer = DecB( MAD_Mult_TPS_Timer ) ;
      if ( MAD_Mult_TPS_Timer == 0 )
      {
         EscFlag.MultiplierDeltaTPS = (bitfield8_t) false ;
         Multiplier_Delta_TPS = false;
      }
   }
   EscOldMultiplierTPS = ( Throttle_Position_Value() ) ;

   /*  determine delta RPM conditions */
   if ( Vc10msCounter&0x01 )
   {
      /* 40 ms passed ..... */
      if ( ( FixSubAbs( Hi_Res_Engine_Speed_W(), EscOldMultiplierRPM, RPM_Hi_Res_W ) > K_MADMultiplierDeltaRPM ) )
      {
          MAD_Mult_RPM_Timer = K_MADMultRPMTimer ;
          EscFlag.MultiplierDeltaRPM = (bitfield8_t) true ;
          Multiplier_Delta_RPM = true;
      }
      else
      {
          MAD_Mult_RPM_Timer = DecB( MAD_Mult_RPM_Timer ) ;
          if ( MAD_Mult_RPM_Timer == 0 )
          {
             EscFlag.MultiplierDeltaRPM = (bitfield8_t) false ;
             Multiplier_Delta_TPS = false;
          }
      }
      EscOldMultiplierRPM = ( Hi_Res_Engine_Speed_W() ) ;
   }

   /*  calculate the offset ( if applicable) */
   mad_mul_offset = FixDefConst(0.0, Multiplier_0_to_64) ;
   PE_mult = FixDefConst(1.0, Multiplier_0_to_4) ;
   load_mult = FixDefConst(1.0, Multiplier_0_to_4) ;

   if ( MAD_Mult_TPS_Timer > 0 )
   {
       /*  calculate for delta TPS conditions */
       /* default: method = MAD_MULT_USE_OFFSET */
       mad_mul_offset = Lookup_2D_B( HAL_Eng_Get_Engine_Speed(), Prec_RPM_W, 0.0, 0.0, 6400.0, 400.0, F_MADMultTPSOffset ) ;
   }
   else if ( MAD_Mult_RPM_Timer > 0 )
   {
       /*  calculate for delta RPM conditions */
       /* default: method = MAD_MULT_USE_OFFSET */
       mad_mul_offset = Lookup_2D_B( HAL_Eng_Get_Engine_Speed(), Prec_RPM_W, 0.0, 0.0, 6400.0, 400.0, F_MADMultRPMOffset ) ;
   }
   else
   {
       /*  no delta TPS/RPM conditions */
       load_mult = ( Multiplier_0_to_4 )Lookup_3D_B( Manifold_Air_Pressure(), Prec_kPa_B, Min_kPa_B, 20.0, 100.0, 20.0,
                                                     HAL_Eng_Get_Engine_Speed(), Prec_RPM_W, 0.0, 0.0, 6400.0, 400.0,
                                                     RPM_0to6400by400_Steps,
                                                     &F_MADMultLoadComp[0][0] ) ;
       if ( Power_Enrichment_Met() )
       {
           /* power enrichment is enabled */
           PE_mult = Lookup_2D_B( HAL_Eng_Get_Engine_Speed(), Prec_RPM_W, 0.0, 0.0, 6400.0, 400.0, F_MADMultPEComp ) ;
       }
   }

#if CcSYST_NUM_OF_CYLINDERS == 3
   for ( cylinder = cyl_1 ; cylinder <= cyl_3 ; cylinder++ )
   {
       base_mult = Lookup_3D_B( cylinder, Fixed_Shortcard, 0.0, cyl_1, cyl_3, 1.0,
                                HAL_Eng_Get_Engine_Speed(), RPM_W, 0.0, 0.0, 6400.0, 400.0,
                                RPM_0to6400by400_Steps,
                                F_MADMultiplier[0] ) ;
#else
   for ( cylinder = cyl_1 ; cylinder <= cyl_4 ; cylinder++ )
   {
       base_mult = Lookup_3D_B( cylinder, Prec_Fixed_Shortcard, 0.0, cyl_1, cyl_4, 1.0,
                                HAL_Eng_Get_Engine_Speed(), Prec_RPM_W, 0.0, 0.0, 6400.0, 400.0,
                                RPM_0to6400by400_Steps,
                                F_MADMultiplier[0] ) ;
#endif
       if ( mad_mul_offset != 0 )
       {
           /* MAD multiplier offset has to be calculated and added */
           MADMultiplier[cylinder] = FixAddHighLimit( base_mult, mad_mul_offset, Multiplier_0_to_64,
                                                              FixDefConst( Max_Multiplier_0_to_64, Multiplier_0_to_64 ) ) ;
       }
       else
       {
           /*  load and PE compensation factors have to be added */
           base_mult = FixMultiply( base_mult, Multiplier_0_to_64, load_mult, Multiplier_0_to_4,
                                                          Multiplier_0_to_64 ) ;

           if ( Power_Enrichment_Met() )
           {
               /*  power enrichment is enabled */
               MADMultiplier[cylinder] = FixMultiply( base_mult, Multiplier_0_to_64,
                                                      PE_mult, Multiplier_0_to_4, Multiplier_0_to_64 ) ;
           }
           else
           {
               MADMultiplier[cylinder] = base_mult;
           }
       }
   }
} /* End CalculateKnockMultiplier */



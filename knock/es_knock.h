#ifndef ES_KNOCK_H
#define ES_KNOCK_H
/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "es_types.h"

/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */
#if CcSYST_NUM_OF_CYLINDERS == 3
#define cyl_1        0
#define cyl_2        1
#define cyl_3        2
#define cyl_global   0
#define num_cyl      3
#else 
#define cyl_1        0
#define cyl_2        1
#define cyl_3        2
#define cyl_4        3
#define cyl_global   0
//#define num_cyl      4
#define num_cyl      3
#endif


/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */


typedef struct
{
    Volt0to5Volts_W               ADESC ;                  /* raw data */
    Volt0to5Volts_W               IntegratorAverage ;      /* filtered value */
    Volt0to5Volts_W               RawMAD ;                 /* raw (instant) MAD */
    Volt0to5Volts_W               FilteredMAD ;            /* filtered MAD */
    Multiplier_0_to_64            MADMultiplier ;          /* MAD Multiplier */
    Volt0to5Volts_W               KnockThreshold ;         /* knock threshold */
    bool                                Gain_high;                    /* gain for this cylinder */
} ESCDataType ;
#if CcSYST_NUM_OF_CYLINDERS == 3
typedef enum
{
   cylinder_0,
   cylinder_1,
   cylinder_2
} ESCCylinderType;
#else
typedef enum
{
   cylinder_0,
   cylinder_1,
   cylinder_2,
   cylinder_3
} ESCCylinderType;
#endif

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
extern ESCCylinderType        EscCylinder ;
extern bool                    ESCGain_High[num_cyl];                 /* gain for this cylinder */
extern Volt0to5Volts_W        ADESC[num_cyl] ; 
extern Volt0to5Volts_W        IntegratorAverage[num_cyl] ;      /* filtered value */
extern Volt0to5Volts_W       ADESC_Average_Wingateoff[num_cyl] ; 
extern EscFlag_Type           EscFlag ;

/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */

/* ============================================================================ *\
 * FUNCTION: InitialiseESC
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   All
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * Initialised the complete ESC system.
\* ============================================================================ */
 void InitialiseESC( void );


/* ============================================================================ *\
 * FUNCTION: ScheduleKnockSlowBckgLogic
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
 * ESC logic slow updated scheduler (every 125 ms).
\* ============================================================================ */
 void ScheduleKnockSlowBckgLogic( void );


/* ============================================================================ *\
 * FUNCTION: ESCEvent
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
 * ESC Event scheduler (end of Wingate).
\* ============================================================================ */
 void ESCEvent( void );


/* ============================================================================ *\
 * FUNCTION: ScheduleKnockFastBckgLogic
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
 * ESC event fast scheduler (every 15.625 msec).
\* ============================================================================ */
 void ScheduleKnockFastBckgLogic( void );


/* ============================================================================ *\
 * FUNCTION: AverageCoefficient
 * ============================================================================
 * RETURN VALUE:
 *   Filter_Q_W         - integrator average filter coefficient
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
 * Calculates and returns the integrator average filter cofficient.
\* ============================================================================ */
#define AverageCoefficient()    ( EscFlag.KnockPresent ? \
                                  FixMultiply(IntAveQ, Filter_Q_W, \
                                              K_IntegratorFilterKnockMult, Filter_Q_W, \
                                              Filter_Q_W) : \
                                              IntAveQ)



/* ============================================================================ *\
 * FUNCTION: ESCEnabled
 * ============================================================================
 * RETURN VALUE:
 *   bool            - true if ESC enable conditions are met
 *                   - false if ESC enable conditions are not met
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
 * Returns the ESC enable conditions met status.
\* ============================================================================ */
#define ESCEnabled()             (EscFlag.EscEnabled == (bitfield8_t) true)

#define GetKnockActive()         (EscFlag.KnockActive)

#define Hi_Res_Engine_Speed_W() Hi_Res_Engine_Speed_Var


#endif /* ES_KNOCK_H */

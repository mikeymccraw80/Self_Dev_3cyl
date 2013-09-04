#ifndef V_ESC_H
#define V_ESC_H

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "lux_type.h"


/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
/*  none */

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/
extern Degrees_C_B             Coolant_Temperature_ ;
extern kPa_W                       Manifold_Air_Pressure_W_;
extern kPa_B                        MAPADFiltered_B ;
extern kPa_B                        MAPStartup ;
extern Percent_B                   Throttle_Position_;
extern Degrees_C_B             Manifold_Air_Temperature_ ;
extern bool                           Engine_Run_Spark_;
extern Seconds_Low              Engine_Run_Time_ ;
extern RPM_Hi_Res_W  Hi_Res_Engine_Speed_Var ;
extern kPa_W_NonLinear                MapWithSlopeChangeAt80kPa ;
/* ==========================================================================*\
 * Exported INLINE functions and #define function-like macros.
\* ==========================================================================*/
#define Throttle_Position_Value()       ( (Percent_B)Throttle_Position_ )
#define Manifold_Air_Pressure()   ( ( kPa_B )MAPADFiltered_B )
#define MAP_W()                   ( Manifold_Air_Pressure_W_ )
#define MAP_Startup()             ( ( kPa_B )MAPStartup )
#define Run_Spark()               (bool)Engine_Run_Spark_
#define  Coolant_Temperature()     Coolant_Temperature_
#define Manifold_Air_Temperature() \
                                ((Degrees_C_B)Manifold_Air_Temperature_)
#define Power_Enrichment_Met()  PEConditionsMetDetermination()  /*TBD, chery have no sense of PE*/
#define  Engine_Running_Time() \
          (Seconds_Low) Engine_Run_Time_

/***************************************************************/
/***  the absolute pressure with a non linear type.          ***/
/***************************************************************/
#define GetMapVarWithSlopeChangeAt80kPa() \
     ( kPa_W_NonLinear )MapWithSlopeChangeAt80kPa

          


/*===========================================================================*/
/* Discrete enumeration for input and outputs                                */
/*===========================================================================*/
/*  none */


/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/

extern  void Initialize_HiRes_Engine_Speed( void );
extern  void Calculate_HiRes_Engine_Speed( void );
extern  void Calculate_Esc_Input_1000ms(void);
extern  void Calculate_Esc_Input_10ms(void);
extern  bool PEConditionsMetDetermination( void );
/*===========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/*===========================================================================*/
/*                                                                           */
/*  Date        user id     SCR       (description on following lines)       */
/* ----------   -------     ---     ----------------------------------       */
/*===========================================================================*/
#endif /* HAL_ESC_H */

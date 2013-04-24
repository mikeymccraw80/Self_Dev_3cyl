#ifndef DD_VSEP_PWM_H
#define DD_VSEP_PWM_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_pwm.h~5:incl:mt20u2#2 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:57 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 11:42:26 2007 %
//
// %version:         5 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

#include "dd_vsep.h"

#include "dd_vsep_fault.h"


#define VSEP_PWM_VALID_PERIOD_MIN      (uint32_t)0x7A
#define VSEP_PWM_VALID_PERIOD_MAX      (uint32_t)0xffffff

typedef uint16_t               T_Duty_PERCENT_Scaled_UW;//refer to T_PERCENT_MULTa
#define Prec_T_Duty_PERCENT_Scaled_UW                                   (1.0/32768)
#define Min_T_Duty_PERCENT_Scaled_UW                                         (0.0)
#define Max_T_Duty_PERCENT_Scaled_UW              (32768 * Prec_T_Duty_PERCENT_Scaled_UW + Min_T_Duty_PERCENT_Scaled_UW)


typedef uint16_t            T_Period_Millisecond_Scaled_UW;// refer to T_MILLISECONDSb
#define Prec_T_Period_Millisecond_Scaled_UW                        (1.0/64000)
#define Min_T_Period_Millisecond_Scaled_UW                             (0.0)
#define Max_T_Period_Millisecond_Scaled_UW             (32768 * Prec_T_Period_Millisecond_Scaled_UW + Min_T_Period_Millisecond_Scaled_UW)

typedef uint16_t            T_Period_Millisecond_UW;
#define Prec_T_Period_Millisecond_UW                        (1.0/1000)
#define Min_T_Period_Millisecond_UW                             (0.0)
#define Max_T_Period_Millisecond_UW             (32768 * Prec_T_Period_Millisecond_UW + Min_T_Period_Millisecond_UW)

typedef uint16_t            T_Period_Microsecond_UL;
#define Prec_T_Period_Microsecond_UL                        (1.0/1000000)
#define Min_T_Period_Microsecond_UL                             (0.0)
#define Max_T_Period_Microsecond_UL            (2147483648 * Prec_T_Period_Microsecond_UL   + Min_T_Period_Microsecond_UL)

typedef uint16_t            T_Freq_HERTZ_Scaled_UW;//refer to T_HERTZ
#define Prec_T_Freq_HERTZ_Scaled_UW                        (1.0/4)
#define Min_T_Freq_HERTZ_Scaled_UW                             (0.0)
#define Max_T_Freq_HERTZ_Scaled_UW            (32768 * Prec_T_Freq_HERTZ_Scaled_UW   + Min_T_Freq_HERTZ_Scaled_UW)




typedef unsigned long     LONGCARD;
#define MIN_LONGCARD          (0uL)     /*--- 000000000h ---*/
#define MAX_LONGCARD (4294967295uL)     /*--- 0FFFFFFFFh ---*/

typedef long signed int    LONGINT;



/*--- internal macros ---*/

#define RoundUp (0.5)

#define FactorRound(Factor) ( \
 ((Factor) >= 0.0) ? ((Factor) + RoundUp) : ((Factor) - RoundUp) \
 )
#define FactorCasted(Factor) ( \
 ((Factor) >= 0.0) ? \
 ((LONGCARD) FactorRound (Factor)) : ((LONGINT) FactorRound (Factor)) \
 )



#define FactorAbs(Factor) (((Factor) >= 0.0) ? (Factor) : - (Factor))



#define FixMultiply(VarOrgA,TypeOrgA,VarOrgB,TypeOrgB,TypeDest) \
((TypeDest) \
(((FactorAbs ((Prec_##TypeOrgA * Prec_##TypeOrgB) / Prec_##TypeDest) < 1.0) ? \
   (((LONGCARD) (VarOrgA) * (VarOrgB)) / \
   FactorCasted (Prec_##TypeDest / (Prec_##TypeOrgA * Prec_##TypeOrgB))) : \
   (((LONGCARD) (VarOrgA) * (VarOrgB)) * \
   FactorCasted ((Prec_##TypeOrgA * Prec_##TypeOrgB) / Prec_##TypeDest))) \
 + \
 ((Min_##TypeOrgB > 0.0) ? \
   ((FactorAbs ((Prec_##TypeOrgA * Min_##TypeOrgB) / Prec_##TypeDest) < 1.0) ? \
     ((LONGCARD) (VarOrgA) / \
    FactorCasted (Prec_##TypeDest / (Prec_##TypeOrgA * Min_##TypeOrgB))) : \
    ((LONGCARD) (VarOrgA) * \
    FactorCasted ((Prec_##TypeOrgA * Min_##TypeOrgB) / Prec_##TypeDest)) \
   ) : \
  ((Min_##TypeOrgB < 0.0) ? \
   ((FactorAbs ((Prec_##TypeOrgA * (Min_##TypeOrgB)) / Prec_##TypeDest) < 1.0) ? \
     - ((LONGCARD) (VarOrgA) / \
    FactorCasted (Prec_##TypeDest / (Prec_##TypeOrgA * (-Min_##TypeOrgB)))) : \
    - ((LONGCARD) (VarOrgA) * \
    FactorCasted ((Prec_##TypeOrgA * (-Min_##TypeOrgB)) / Prec_##TypeDest)) \
   ) : \
   ((LONGCARD) (0)))) \
 + \
 ((Min_##TypeOrgA > 0.0) ? \
   ((FactorAbs ((Min_##TypeOrgA * Prec_##TypeOrgB) / Prec_##TypeDest) < 1.0) ? \
     ((LONGCARD) (VarOrgB) / \
    FactorCasted (Prec_##TypeDest / (Min_##TypeOrgA * Prec_##TypeOrgB))) : \
    ((LONGCARD) (VarOrgB) * \
    FactorCasted ((Min_##TypeOrgA * Prec_##TypeOrgB) / Prec_##TypeDest)) \
   ) : \
  ((Min_##TypeOrgA < 0.0) ? \
   ((FactorAbs ((Min_##TypeOrgA * Prec_##TypeOrgB) / Prec_##TypeDest) < 1.0) ? \
     - ((LONGCARD) (VarOrgB) / \
    FactorCasted (Prec_##TypeDest / ((-Min_##TypeOrgA) * Prec_##TypeOrgB))) : \
    - ((LONGCARD) (VarOrgB) * \
    FactorCasted (((-Min_##TypeOrgA) * Prec_##TypeOrgB) / Prec_##TypeDest)) \
   ) : \
   ((LONGCARD) (0)))) \
 + \
 FactorCasted ((Min_##TypeOrgA * Min_##TypeOrgB - Min_##TypeDest) / Prec_##TypeDest) \
))

typedef unsigned char    SHORTCARD;
#define Prec_SHORTCARD         (1u)
#define Min_SHORTCARD          (0u)     /*--- 000000000h ---*/
#define Max_SHORTCARD        (255u)     /*--- 0000000FFh ---*/

/*--- NOT TO BE DEFINED SOMEWHERE! ---*/
SHORTCARD CrashFunction (void);

/*--- FixNonBiasedDivide gives the quotient of two fixed point variable, ---*/
/*--- the result is of a different fixed point type                      ---*/


#define FixMaxDefConst(Type) \
 ((Type) FactorRound ((Max_##Type - Min_##Type) / Prec_##Type))

#define FixLimitDiv(Var,Limit) (((Var) > (Limit)) ? (Limit) : (Var))

#define FixNonBiasedDiv(VarN,TypeN,VarD,TypeD,TypeQ) ((TypeQ) ( \
 (((Prec_##TypeN / Prec_##TypeD) / Prec_##TypeQ) >= 1.0) ? \
  ((FactorCasted ((Prec_##TypeN / Prec_##TypeD) / Prec_##TypeQ) * (VarN)) / \
     (VarD)) : \
  ((VarN) / (FactorCasted (Prec_##TypeQ / (Prec_##TypeN / Prec_##TypeD)) * \
     (VarD))) \
  ))

#define FixNonBiasedDivide(VarN,TypeN,VarD,TypeD,TypeQ) ( (TypeQ) ( \
	(Min_##TypeN != 0.0 || Min_##TypeD != 0.0 || Min_##TypeQ != 0.0) ? \
     CrashFunction () : \
   FixLimitDiv (FixNonBiasedDiv(VarN,TypeN,VarD,TypeD,TypeQ), \
     FixMaxDefConst (TypeQ)) \
  ))



#if 0	

// duty_count = (duty_percent/100) * Period_count
#define VSEP_ConvertDutyPercentToCountScaled( duty_percent,Period_count) \
      FixMultiply(duty_percent,T_Duty_PERCENT_Scaled_UW,Period_count,COUNT_DW,COUNT_DW)
      	    //  ((((uint32_t)duty_percent)*Period_count)*Prec_T_Duty_PERCENT_Scaled_UW)

				
// duty_percent/100 = duty_count * Period_count/100
#define VSEP_ConvertDutyCountToPercentScaled( duty_count,Period_count) \	  
         FixNonBiasedDivide(duty_count,COUNT_DW,Period_count,COUNT_DW,T_Duty_PERCENT_Scaled_UW)
     //  ((((uint32_t)duty_count)/Prec_T_Duty_PERCENT_Scaled_UW)/Period_count)

//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertDutyCountToMillisecondScaled( Duty_count,base_frequecy)\
	FixNonBiasedDivide(Duty_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Millisecond_Scaled_UW)
 // (( ( (uint32_t)Duty_count)/(Prec_T_Period_Millisecond_Scaled_UW))/base_frequecy )

//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertDutyCountToMillisecond( Duty_count,base_frequecy)\
	    	FixNonBiasedDivide(Duty_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Millisecond_UW)
	  //  (( ( (uint32_t)Duty_count)/(Prec_T_Period_Millisecond_UW))/base_frequecy )
	  
#define VSEP_ConvertDutyCountToMicrosecond( Duty_count,base_frequecy)\
		FixNonBiasedDivide(Duty_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Microsecond_UL)
    //    (( ( (uint32_t)Duty_count)/(Prec_T_Period_Microsecond_UL))/base_frequecy )
    
//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertPeriodMillisecondToCountScaled( Period_MS,base_frequecy)\
	        	FixMultiply(Period_MS,T_Period_Millisecond_Scaled_UW,base_frequecy,COUNT_DW,COUNT_DW)
	        	 //    (  ( ( (uint32_t)Period_MS)*(Prec_T_Period_Millisecond_Scaled_UW))/base_frequecy)
	        	 
#define  VSEP_ConvertPeriodMicrosecondToCount( Period_US,base_frequecy)\
	FixMultiply(Period_US,T_Period_Microsecond_UL,base_frequecy,COUNT_DW,COUNT_DW)
		   // (  ( ( (uint32_t)Period_US)*(Prec_T_Period_Microsecond_UL))/base_frequecy)

#define  VSEP_ConvertPeriodHERTZToCountScaled( Period_HZ,base_frequecy)\
	 	FixNonBiasedDivide(base_frequecy,COUNT_DW,Period_HZ,T_Freq_HERTZ_Scaled_UW,COUNT_DW)
	    //    (((uint32_t)base_frequecy)/(Period_HZ*Prec_T_Freq_HERTZ_Scaled_UW))
	    
//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertPeriodCountToMillisecondScaled( Period_count,base_frequecy)\
               	FixNonBiasedDivide(Period_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Millisecond_Scaled_UW)
//   (  (  ( (uint32_t)Period_count)/(Prec_T_Period_Millisecond_Scaled_UW))/base_frequecy)

//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertPeriodCountToMillisecond( Period_count,base_frequecy)\
	 	FixNonBiasedDivide(Period_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Millisecond_UW)
	 	     //    (  (  ( (uint32_t)Period_count)/(Prec_T_Period_Millisecond_UW))/base_frequecy)
	 	     
#define VSEP_ConvertPeriodCountToMicrosecond( Period_count,base_frequecy)\	      
	FixNonBiasedDivide(Period_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Microsecond_UL)
	// (  (  ( (uint32_t)Period_count)/(Prec_T_Period_Microsecond_UL))/base_frequecy)

#define VSEP_ConvertPeriodCountToHERTZScaled( Period_count,base_frequecy)\	
	FixNonBiasedDivide(base_frequecy,COUNT_DW,Period_count,COUNT_DW,T_Freq_HERTZ_Scaled_UW)
      //  ( (   ( (uint32_t)base_frequecy)/Prec_T_Freq_HERTZ_Scaled_UW )/Period_count)
#endif
// duty_count = (duty_percent/100) * Period_count
#define VSEP_ConvertDutyPercentToCountScaled( duty_percent,Period_count) \
 FixMultiply(duty_percent,T_Duty_PERCENT_Scaled_UW,Period_count,COUNT_DW,COUNT_DW)
 					
// duty_percent/100 = duty_count * Period_count/100
#define VSEP_ConvertDutyCountToPercentScaled( duty_count,Period_count) \
 FixNonBiasedDivide(duty_count,COUNT_DW,Period_count,COUNT_DW,T_Duty_PERCENT_Scaled_UW)

//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertDutyCountToMillisecondScaled( Duty_count,base_frequecy)\
	FixNonBiasedDivide(Duty_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Millisecond_Scaled_UW)

//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertDutyCountToMillisecond( Duty_count,base_frequecy)\
	FixNonBiasedDivide(Duty_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Millisecond_UW)
	
#define VSEP_ConvertDutyCountToMicrosecond( Duty_count,base_frequecy)\
	FixNonBiasedDivide(Duty_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Microsecond_UL)

//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertPeriodMillisecondToCountScaled( Period_MS,base_frequecy)\
	FixMultiply(Period_MS,T_Period_Millisecond_Scaled_UW,base_frequecy,COUNT_DW,COUNT_DW)
#define  VSEP_ConvertPeriodMicrosecondToCount( Period_US,base_frequecy)\
	FixMultiply(Period_US,T_Period_Microsecond_UL,base_frequecy,COUNT_DW,COUNT_DW)

#define  VSEP_ConvertPeriodHERTZToCountScaled( Period_HZ,base_frequecy)\
	FixNonBiasedDivide(base_frequecy,COUNT_DW,Period_HZ,T_Freq_HERTZ_Scaled_UW,COUNT_DW)

//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertPeriodCountToMillisecondScaled( Period_count,base_frequecy)\
	FixNonBiasedDivide(Period_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Millisecond_Scaled_UW)
//period_count =  period_ms * base_frequecy_hz/1000
#define  VSEP_ConvertPeriodCountToMillisecond( Period_count,base_frequecy)\
	FixNonBiasedDivide(Period_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Millisecond_UW)
#define VSEP_ConvertPeriodCountToMicrosecond( Period_count,base_frequecy)\
	FixNonBiasedDivide(Period_count,COUNT_DW,base_frequecy,COUNT_DW,T_Period_Microsecond_UL)

#define VSEP_ConvertPeriodCountToHERTZScaled( Period_count,base_frequecy)\
	FixNonBiasedDivide(base_frequecy,COUNT_DW,Period_count,COUNT_DW,T_Freq_HERTZ_Scaled_UW)


typedef enum
{
	VSEP_PWM_DutyCycle_ReturnType_Count,
	VSEP_PWM_DutyCycle_ReturnType_MS,
	VSEP_PWM_DutyCycle_ReturnType_US,
	VSEP_PWM_DutyCycle_ReturnType_Percent
}VSEP_PWM_DutyCycle_ReturnType_T;     

typedef enum
{
	VSEP_PWM_DutyCycle_InType_Count,
	VSEP_PWM_DutyCycle_InType_Percent
}VSEP_PWM_DutyCycle_InType_T;  

typedef enum
{
	VSEP_PWM_Period_ReturnType_Count,
	VSEP_PWM_Period_ReturnType_MS,
	VSEP_PWM_Period_ReturnType_US,
	VSEP_PWM_Period_ReturnType_HZ
}VSEP_PWM_Period_ReturnType_T;     

typedef enum
{
	VSEP_PWM_Period_InType_Count,
	VSEP_PWM_Period_InType_MS,
	VSEP_PWM_Period_InType_US,
	VSEP_PWM_Period_InType_HZ
}VSEP_PWM_Period_InType_T;  

typedef enum
{
                                                                       //[ 6: 0] Reserved
   VSEP_PWM_CONFIGURATION_POSITION_POLARITY                       = 7, //     7  Polarity
   VSEP_PWM_CONFIGURATION_POSITION_INITIAL_STATE                  = 8  //     8  Initial State
}VSEP_PWM_Configuration_Position_T;                               
                                                                  
typedef enum                                                      
{                                                                 
                                                                       //[ 6: 0] Reserved
   VSEP_PWM_CONFIGURATION_WIDTH_POLARITY                          = 1, //     7  Polarity
   VSEP_PWM_CONFIGURATION_WIDTH_INITIAL_STATE                     = 1  //     8  Initial State
}VSEP_PWM_Configuration_Width_T;

typedef enum
{
   VSEP_PWM_FREQUENCY_CONFIGURATION_POSITION_INITIAL_DUTY_CYCLE   = 0, //[11:0] Initial Duty Cycle
   VSEP_PWM_FREQUENCY_CONFIGURATION_POSITION_INITIAL_PERIOD       =16, //[27:16] Initial Period
   VSEP_PWM_FREQUENCY_CONFIGURATION_POSITION_INITIAL_CDIV         =28  //    28  Initial CDIV
}VSEP_PWM_Frequency_Configuration_Position_T;

typedef enum
{
   VSEP_PWM_FREQUENCY_CONFIGURATION_WIDTH_INITIAL_DUTY_CYCLE    =12, //[11:0]  Initial Duty Cycle
   VSEP_PWM_FREQUENCY_CONFIGURATION_WIDTH_INITIAL_PERIOD        =12, //[27:16] Initial Period
   VSEP_PWM_FREQUENCY_CONFIGURATION_WIDTH_INITIAL_CDIV          = 1  //    28  Initial CDIV
}VSEP_PWM_Frequency_Configuration_Width_T;

typedef enum 
{
   VSEP_PWM_CHANNEL_1,
   VSEP_PWM_CHANNEL_2,
   VSEP_PWM_CHANNEL_3,
   VSEP_PWM_CHANNEL_4,
   VSEP_PWM_CHANNEL_5,
   VSEP_PWM_CHANNEL_6,
   VSEP_PWM_CHANNEL_7,
   VSEP_PWM_CHANNEL_8,
   VSEP_PWM_CHANNEL_MAX    
}VSEP_PWM_Channel_T;

//=============================================================================
// VSEP_PWM_Get_Polarity
//
// @func Get the configured polarity
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t IO_Polarity_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_PWM_Get_Polarity( x ) \
   (IO_Polarity_T)( Extract_Bits( x, VSEP_PWM_CONFIGURATION_POSITION_POLARITY, VSEP_PWM_CONFIGURATION_WIDTH_POLARITY ) )

//=============================================================================
// VSEP_PWM_Set_Polarity
//
// @func Set the desired polarity
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @parm IO_Polarity_T | y | The desired polarity 
//
// @rdesc <t IO_Configuration_T> element encoded with the desired IO_Polarity_T
//
// @end
//=============================================================================
#define VSEP_PWM_Set_Polarity( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_PWM_CONFIGURATION_POSITION_POLARITY, VSEP_PWM_CONFIGURATION_WIDTH_POLARITY ) )

//=============================================================================
// VSEP_PWM_Get_Initial_State
//
// @func Get the configured initial state
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t IO_Active_State_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_PWM_Get_Initial_State( x ) \
   (IO_Active_State_T)( Extract_Bits( x, VSEP_PWM_CONFIGURATION_POSITION_INITIAL_STATE, VSEP_PWM_CONFIGURATION_WIDTH_INITIAL_STATE ) )

//=============================================================================
// VSEP_PWM_Set_Initial_State
//
// @func Set the desired initial state
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @parm IO_Active_State_T | y | The desired polarity 
//
// @rdesc <t IO_Configuration_T> element encoded with the desired IO_Active_State_T
//
// @end
//=============================================================================
#define VSEP_PWM_Set_Initial_State( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_PWM_CONFIGURATION_POSITION_INITIAL_STATE, VSEP_PWM_CONFIGURATION_WIDTH_INITIAL_STATE ) )

//=============================================================================
// VSEP_PWM_Get_Initial_Period
//
// @func Get the Initial PWM period.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t uint32_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_PWM_Get_Initial_Period(x) \
   (uint32_t)(Extract_Bits( x, VSEP_PWM_FREQUENCY_CONFIGURATION_POSITION_INITIAL_PERIOD, VSEP_PWM_FREQUENCY_CONFIGURATION_WIDTH_INITIAL_PERIOD ))

//=============================================================================
// VSEP_PWM_Set_Initial_Period
//
// @func Set the Initial PWM period.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @parm uint32_t | y | The desired initial PWM period
//
// @rdesc <t IO_Configuration_T> element encoded with the desired initial PWM period
//
// @end
//=============================================================================
#define VSEP_PWM_Set_Initial_Period(x,y) \
   (IO_Configuration_T)(Insert_Bits( x, y, VSEP_PWM_FREQUENCY_CONFIGURATION_POSITION_INITIAL_PERIOD, VSEP_PWM_FREQUENCY_CONFIGURATION_WIDTH_INITIAL_PERIOD ) )

//=============================================================================
// VSEP_PWM_Get_Initial_Duty_Cycle
//
// @func Get the Initial PWM duty cycle.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t uint32_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_PWM_Get_Initial_Duty_Cycle(x) \
   (uint32_t)(Extract_Bits( x, VSEP_PWM_FREQUENCY_CONFIGURATION_POSITION_INITIAL_DUTY_CYCLE, VSEP_PWM_FREQUENCY_CONFIGURATION_WIDTH_INITIAL_DUTY_CYCLE ))

//=============================================================================
// VSEP_PWM_Set_Initial_Duty_Cycle
//
// @func Set the Initial PWM duty cycle.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @parm uint32_t | y | The desired initial PWM period
//
// @rdesc <t IO_Configuration_T> element encoded with the desired initial PWM 
//    duty cycle
//
// @end
//=============================================================================
#define VSEP_PWM_Set_Initial_Duty_Cycle(x,y) \
   (IO_Configuration_T)(Insert_Bits( x, y, VSEP_PWM_FREQUENCY_CONFIGURATION_POSITION_INITIAL_DUTY_CYCLE, VSEP_PWM_FREQUENCY_CONFIGURATION_WIDTH_INITIAL_DUTY_CYCLE ) )

typedef enum
{
   VSEP_PWM_CDIV_32,
   VSEP_PWM_CDIV_256
}VSEP_PWM_CDIV_T;

#define VSEP_PWM_CDIV_DIVIDER_0    (32)
#define VSEP_PWM_CDIV_DIVIDER_1    (256)

//=============================================================================
// VSEP_PWM_Get_Base_Frequency_Divider
//
// @func Get the PWM base frequency divider
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t uint32_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_PWM_Get_Base_Frequency_Divider(x) \
   (uint32_t)(Extract_Bits( x, VSEP_PWM_FREQUENCY_CONFIGURATION_POSITION_INITIAL_CDIV, VSEP_PWM_FREQUENCY_CONFIGURATION_WIDTH_INITIAL_CDIV ))

//=============================================================================
// VSEP_PWM_Set_Base_Frequency_Divider
//
// @func Set the PWM base frequency divider.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @parm uint32_t | y | The desired base frequency divider
//
// @rdesc <t IO_Configuration_T> element encoded with the desired base frequency
//    divider.
//
// @end
//=============================================================================
#define VSEP_PWM_Set_Base_Frequency_Divider(x,y) \
   (IO_Configuration_T)(Insert_Bits( x, y, VSEP_PWM_FREQUENCY_CONFIGURATION_POSITION_INITIAL_CDIV, VSEP_PWM_FREQUENCY_CONFIGURATION_WIDTH_INITIAL_CDIV ) )

//=============================================================================
// VSEP_PWM_Convert_Frequency
//
// @func Convert enginnering units to computer units for VSEP PWM frequency
//
// @parm VSEP_PWM_CDIV_T | pwm_div | A <t VSEP_PWM_CDIV_T> type
//
// @parm float | frequency | Desired frequency in hertz for the configured VSEP PWM
//
// @rdesc <t uint16_t> value represent the converted desired frequency convert to computer units.
//
// @end
//=============================================================================
#define VSEP_PWM_Convert_Frequency( pwm_div, frequency ) \
   (uint16_t)( ( ( VSEP_EXTERNAL_CLOCK_BASE_FREQUENCY / ( pwm_div==VSEP_PWM_CDIV_32 ? VSEP_PWM_CDIV_DIVIDER_0 :  VSEP_PWM_CDIV_DIVIDER_1 ) ) / (frequency) ) - 1 )

//=============================================================================
// VSEP_PWM_Convert_Duty_Cycle
//
// @func Convert enginnering units to computer units for VSEP PWM duty cycle
//
// @parm VSEP_PWM_CDIV_T | pwm_div | A <t VSEP_PWM_CDIV_T> type
//
// @parm float | frequency | Desired frequency in hertz for the configured VSEP PWM
//
// @parm float | duty_cycle | Desired duty cycle in percent for the configured VSEP PWM
//
// @rdesc <t uint16_t> value represent the converted desired duty cycle convert to computer units.
//
// @end
//=============================================================================
#define VSEP_PWM_Convert_Duty_Cycle( pwm_div, frequency, duty_cycle ) \
   (uint16_t) (( (duty_cycle) * VSEP_PWM_Convert_Frequency( pwm_div, frequency ) ) / 100 )

//=============================================================================
// VSEP_PWM_Set_Initial_Frequency_Duty_Cycle
//
// @func Set initial PWM frequency and duty cycle computer units based on 
//    engineering units.
//
// @parm VSEP_PWM_CDIV_T | pwm_div | A <t VSEP_PWM_CDIV_T> type
//
// @parm float | frequency | Desired frequency in hertz for the configured VSEP PWM
//
// @parm float | duty_cycle | Desired duty cycle in percent for the configured VSEP PWM
//
// @rdesc <t uint32_t> value represent the computer units for frequency and duty cycle.
//
// @end
//=============================================================================
#define VSEP_PWM_Set_Initial_Frequency_Duty_Cycle( pwm_div, frequency, duty_cycle ) \
   (uint32_t)( VSEP_PWM_Set_Initial_Period( 0,  VSEP_PWM_Convert_Frequency( pwm_div, frequency             ) ) | \
           VSEP_PWM_Set_Initial_Duty_Cycle( 0, VSEP_PWM_Convert_Duty_Cycle( pwm_div, frequency, duty_cycle ) ) | \
       VSEP_PWM_Set_Base_Frequency_Divider( 0, pwm_div ) )





typedef enum
{
   VSEP_PWM_TXD_MESSAGE_CTRL,
   VSEP_PWM_TXD_MESSAGE_ONTIME,
   VSEP_PWM_TXD_MESSAGE_PERIOD,
   VSEP_PWM_TXD_MESSAGE_MAX
}VSEP_PWM_Txd_Message_T;

typedef enum
{
   VSEP_PWM_RXD_MESSAGE_FLT,
   VSEP_PWM_RXD_MESSAGE_NU_1,
   VSEP_PWM_RXD_MESSAGE_NU_2,
   VSEP_PWM_RXD_MESSAGE_MAX
}VSEP_PWM_Rxd_Message_T;

/* global vsep pwm messagge buffer declare */
extern uint16_t VSEP_PWM_Txd[NUMBER_OF_VSEP][VSEP_PWM_CHANNEL_MAX][VSEP_PWM_TXD_MESSAGE_MAX];
extern uint16_t VSEP_PWM_Rxd[NUMBER_OF_VSEP][VSEP_PWM_RXD_MESSAGE_MAX];


//=============================================================================
// VSEP_PWM_Get_Channel
//
// @func Get the PWM Channel
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_PWM_Channel_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
VSEP_PWM_Channel_T VSEP_PWM_Get_Channel( 
   IO_Configuration_T   in_configuration);


//=============================================================================
// VSEP_PWM_Device_Initialize
//
// @func Initialize the PWM IO portion of the VSEP device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_Device_Initialize(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_PWM_Device_Clear
//
// @func Clear the PWM IO portion of the VSEP device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_Device_Clear(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_PWM_Channel_Initialize
//
// @func Initialize a channel to operate as a pulse width modulator.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_Channel_Initialize( 
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_PWM_Channel_Clear
//
// @func Clear a pwm channel.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_Channel_Clear(
   IO_Configuration_T in_configuration );

//=============================================================================
// VSEP_PWM_Enable_Channel
//
// @func Enables the channel for the specific device requested.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//
//=============================================================================
void VSEP_PWM_Enable_Channel(
   IO_Configuration_T in_configuration );

//=============================================================================
// VSEP_PWM_Disable_Channel
//
// @func Disables the channel for the specific device requested.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//
//=============================================================================
void VSEP_PWM_Disable_Channel( 
   IO_Configuration_T in_configuration );

//=============================================================================
// VSEP_PWM_Get_Channel_Status
//
// @func Returns the enable status of the requested channel.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc the enable state of the channel
// @flag  true | channel enabled
// @flag  false | channel disabled
//
// @end
//=============================================================================
bool VSEP_PWM_Get_Channel_Status( IO_Configuration_T in_configuration );
//=============================================================================
// VSEP_PWM_Set_Period
//
// @func This function will set the pulse width of the requested output by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc the period in counts
//
// @end
//=============================================================================
void VSEP_PWM_Set_Period( 
   IO_Configuration_T   in_configuration,
   uint32_t             in_period ,
   VSEP_PWM_Period_InType_T 	in_type);
//=============================================================================
// VSEP_PWM_Get_Period
//
// @func This function will set the pulse width of the requested output by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc the period in counts
//
// @end
//=============================================================================
uint32_t VSEP_PWM_Get_Period( 
   IO_Configuration_T   in_configurationd ,VSEP_PWM_Period_ReturnType_T  return_type);

//=============================================================================
// VSEP_PWM_Set_Duty_Cycle
//
// @func This function will set the dutycycle of the requested output by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc the duty cycle in counts
//
// @end
//=============================================================================
void VSEP_PWM_Set_Duty_Cycle(
   IO_Configuration_T   in_configuration,
   uint32_t             in_on_time ,
   VSEP_PWM_DutyCycle_InType_T	in_type);
//=============================================================================
// VSEP_PWM_Get_Duty_Cycle
//
// @func This function will set the dutycycle of the requested output by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc the duty cycle in counts
//
// @end
//=============================================================================
uint32_t VSEP_PWM_Get_Duty_Cycle(
   IO_Configuration_T   in_configuration,VSEP_PWM_DutyCycle_ReturnType_T	return_type );

//=============================================================================
// VSEP_PWM_Set_Period_And_Duty_Cycle
//
// @func This function will set both the period and the dutycycle of the
// requested output by calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm uint32_t | in_period | The period in time from rising edge to rising
//          edge of the pulse.
//
// @parm uint32_t | in_duty_cycle | A percent of the pulse width that is high.
//
// @parm bool | in_update_period | update period with new value.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_PWM_Set_Period_And_Duty_Cycle(
   IO_Configuration_T   in_configuration,
   uint32_t             in_period,
   VSEP_PWM_Period_InType_T in_period_type,
   uint32_t             in_on_time,
   VSEP_PWM_DutyCycle_InType_T  in_duty_type,
   bool                 in_update_period,
    bool                 in_update_duty);
//=============================================================================
// VSEP_PWM_Set_Period_And_Duty_Cycle_Immediate
//
// @func This function will set both the period and the dutycycle of the
// requested output by calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm uint32_t | in_period | The period in time from rising edge to rising
//          edge of the pulse.
//
// @parm uint32_t | in_duty_cycle | A percent of the pulse width that is high.
//
// @parm bool | in_update_period | update period with new value.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_PWM_Set_Period_And_Duty_Cycle_Immediate(
   IO_Configuration_T   in_configuration,
   uint32_t             in_period,
   VSEP_PWM_Period_InType_T in_period_type,
   uint32_t             in_on_time,
    VSEP_PWM_DutyCycle_InType_T  in_duty_type,
   bool                 in_update_period,
   bool                 in_update_duty);

//=============================================================================
// TIMER functions (see prototypes in timer.h)
//=============================================================================

//=============================================================================
// VSEP_PWM_Timer_Get_State
//
// @func This is an empty function for this application.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The state of the Timer.  This will always be returned as running.
//
// @end
//=============================================================================
/*IO_Timer_State_T VSEP_PWM_Timer_Get_State(
   IO_Configuration_T in_configuration);
*/
//=============================================================================
// VSEP_PWM_Timer_Get_Base_Frequency
//
// @func This procedure will return the base frequency for a given pwm.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc the frequency being used by this pwm.
//
// @end
//=============================================================================
uint32_t VSEP_PWM_Timer_Get_Base_Frequency_HZ(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_PWM_Timer_Get_Size
//
// @func This procedure will return the timer size via an enumerated value.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc the size in bits of the timer being used.
//
// @end
//=============================================================================
/*IO_Timer_Size_T VSEP_PWM_Timer_Get_Size(
   IO_Configuration_T in_configuration );
*/

//=============================================================================
// DISCRETE functions (see prototypes in discrete.h)
//=============================================================================

//=============================================================================
// VSEP_PWM_DISCRETE_Channel_Initialize
//
// @func Initializes a specific discrete channel on the VSEP device based on 
// its configuration value passed in.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_DISCRETE_Channel_Initialize(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_PWM_DISCRETE_Channel_Clear
//
// @func Sets the VSEP discrete channel's registers back to their reset state. 
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_DISCRETE_Channel_Clear(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_PWM_DISCRETE_Get_State
//
// @func Gets the current state of the given discrete input as indicated by
// the last set state.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc state of the pin as defined by its configuration value
// @flag true | Pin is active
// @flag false | Pin is inactive
//
// @end
//=============================================================================
bool VSEP_PWM_DISCRETE_Get_State( 
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_PWM_DISCRETE_Get_Immediate_State
//
// @func Gets the current state of the given discrete input directly
// from the I/O port immediately ( unbuffered ).
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc state of the pin as defined by its configuration value
// @flag true | Pin is active
// @flag false | Pin is inactive
//
// @end
//=============================================================================
bool VSEP_PWM_DISCRETE_Get_Immediate_State( 
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_PWM_DISCRETE_Set_State
//
// @func Performs a discrete output function directly to the I/O port, 
//       may be buffered
// @comm The output will be buffered for serial device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm bool | in_state | requested state for the pin
// @flag true | pin is active
// @flag false | pin is inactive
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_DISCRETE_Set_State(
   IO_Configuration_T in_configuration,
   bool               in_state);

//=============================================================================
// VSEP_PWM_DISCRETE_Set_Immediate_State
//
// @func Performs a discrete output function directly to the I/O port 
//       immediately (unbuffered).
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm bool | in_state | requested state for the pin
// @flag true | pin is active
// @flag false | pin is inactive
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_DISCRETE_Set_Immediate_State(
   IO_Configuration_T in_configuration,
   bool               in_state);

//=============================================================================
// VSEP_PWM_DISCRETE_Toggle_State
//
// @func Toggles the state of the desired output, may be buffered.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_DISCRETE_Toggle_State(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_PWM_DISCRETE_Toggle_Immediate_State
//
// @func Toggles the state of the desired output immediately.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PWM_DISCRETE_Toggle_Immediate_State(
   IO_Configuration_T in_configuration);

//********************************************************//


#endif // DD_VSEP_PWM_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 * 09/10/15    task# 1978   wsq
 * bug fix for VSEP PWM channel STG diagnostic can not work when low frequence(buffer overflow)
\*===========================================================================*/

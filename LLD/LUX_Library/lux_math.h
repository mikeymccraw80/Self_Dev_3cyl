#ifndef LUX_MATH
#define LUX_MATH
/*-------------------------------------------------------------------*/
/* filename -  FIX_MATH.H                                            */
/*                                                                   */
/* purpose:                                                          */
/*    This file contains the fix point support functions.            */
/*                                                                   */
/* Usage:                                                            */
/*   FixDefConst defines a fixed point constant.                     */
/*                                                                   */
/*   FixMaxDefConst defines the maximum value for the fixed type.    */
/*                                                                   */
/*   FixMinDefConst defines the minimum value for the fixed type.    */
/*                                                                   */
/*   FixLimitedDefConst converts a fixed point constant to a binary  */
/* value fixed point constant Limited to Min and Max.                */
/*                                                                   */
/*   FixConvert converts a fixed point variable to another fixed     */
/* point type.                                                       */
/*                                                                   */
/*   FixConvertLimitCheck converts a fixed point variable to another */
/* fixed point and checks that the result is mindest >= =< maxdest.  */
/*                                                                   */
/*   FixAdd adds two fixed point variables (of the same type).       */
/*                                                                   */
/*   FixSub subs two fixed point variables (of the same type).       */
/*                                                                   */
/*   FixAbs Returns the absolute value of the fix type limited to    */
/* the maximum for that type.                                        */
/*                                                                   */
/*   FixMultiply multiplies two fixed point variables of different   */
/* types to a different fixed point type.                            */
/* Warning: For asymptotic decaying, use FixDecayMult0To1.           */
/*                                                                   */
/*   FixDecayMult0To1 decays a variable down to 0 by multiplying a   */
/* variable of a any type by a multiplier "from 0 to 1" every time   */
/* intervals. Remark: The 0 value is reached, even if the theoritical*/
/* curve is asymptotic, when the value is small enough.              */
/*                                                                   */
/*   FixNonBiasedShortDivide divides two fixed point variables of    */
/* different types to a different fixed point type. WARNING: for this*/
/* macro, the fixed point types of all variables must be non biased  */
/* and their size <= 2 bytes.                                        */
/*                                                                   */
/*   FixAddHighLimit makes a fixed point addition up to a limit,     */
/* even if the calculation overflows or the limit is the top         */
/* boundary of the fixed point base type. See important WARNING, for */
/* BIASed types especially!                                          */
/*                                                                   */
/*   FixSubLowLimit makes a fixed point substraction down to a limit,*/
/* even if the calculation underflows or the limit is the bottom     */
/* boundary of the fixed point base type (=0). See important WARNING,*/
/* BIASed types especially!                                          */
/*                                                                   */
/*   FixSubAbs returns |VarA-VarB| of two fixed point variables of   */
/* the same type.                                                    */
/*                                                                   */
/*   FixConvertPercentToMultiplier converts a Percent factor to a    */
/* multiplier factor.                                                */
/*                                                                   */
/*   FixConvertMultiplierToPercent Converts a multiplier factor to a */
/* Percent factor.                                                   */
/*                                                                   */
/*   FixConvertPercentWToPercentB converts specifically a PercentW   */
/* type to PercentB and make sure that the value of 100 % (in        */
/* PercentW) is converted to 99.6 % (in PercentB) and not 0 %.       */
/*                                                                   */
/*   FixGetDelta returns the difference between the A and B (A>B     */
/* else 0) in a delta type format (same precision and bias nul).     */
/*                                                                   */
/*   FixGetAbsDelta returns the absolute difference between the A    */
/* and B in a delta type format (same precision and bias nul).       */
/*                                                                   */
/*   FixAddDelta returns the result of an addition between           */
/* a element of a type and a delta of that type. A check on the      */
/* delta type format is also performed.                              */
/*                                                                   */
/*   FixAddDeltaHighLimit returns the result of an addition between  */
/* a element of a type and a delta of that type. That result is      */
/* clipped to a maximum. A check on the delta type format is also    */
/* performed.                                                        */
/*                                                                   */
/*   FixSubDelta returns the result of a substraction between a      */
/* element of a type and a delta of that type. A check on the delta  */
/* type format is also performed.                                    */
/*                                                                   */
/*   FixSubDeltaLowLimiteturns the result of a substraction between  */
/* a element of a type and a delta of that type. That result is      */
/* clipped to a minimum. A check on the delta type format is also    */
/* performed.                                                        */
/*                                                                   */
/*   FixIncrementWithLimit Increments var by prec and checks for     */
/* overflow.                                                         */
/*                                                                   */
/*   FixDecrementWithLimit decrements var by prec and checks for     */
/* underflow.                                                        */
/*                                                                   */
/* list of function(s):                                              */
/*  Internal Macro:                                                  */
/*          Const                                                    */
/*          FactorRound                                              */
/*          FactorRound                                              */
/*          FactorCasted                                             */
/*          FactorAbs                                                */
/*          FixLimitVarMin                                           */
/*          FixLimitVarMax                                           */
/*          FixLimitVar                                              */
/*          FixNoCkAdd                                               */
/*          FixNoCkSub                                               */
/*          FixNonBiasedDiv                                          */
/*          FixLimitDiv                                              */
/*          FixNonBiasedDivide                                       */
/*  Macro:  FixDefConst                                              */
/*          FixMaxDefConst                                           */
/*          FixMinDefConst                                           */
/*          FixLimitedDefConst                                       */
/*          FixConvert                                               */
/*          FixConvertLimitCheck                                     */
/*          FixAdd                                                   */
/*          FixSub                                                   */
/*          FixAbs                                                   */
/*          FixMultiply                                              */
/*          FixDecayMult0To1                                         */
/*          FixNonBiasedShortDivide                                  */
/*          FixAddHighLimit                                          */
/*          FixSubLowLimit                                           */
/*          FixSubAbs                                                */
/*          FixConvertPercentToMultiplier                            */
/*          FixConvertMultiplierToPercent                            */
/*          FixConvertPercentWToPercentB                             */
/*          FixGetDelta                                              */
/*          FixGetAbsDelta                                           */
/*          FixAddDelta                                              */
/*          FixAddDeltaHighLimit                                     */
/*          FixSubDelta                                              */
/*          FixSubDeltaLowLimit                                      */
/*          FixIncrementWithLimit                                    */
/*          FixDecrementWithLimit                                    */
/* inline : FixAddLimitSHORTCARD                                     */
/*          FixAddLimitCARDINAL                                      */
/*          FixAddLimitLONGCARD                                      */
/*          FixSubLimitSHORTCARD                                     */
/*          FixSubLimitCARDINAL                                      */
/*          FixSubLimitLONGCARD                                      */
/* proto  : CrashFunction   (NOT TO BE DEFINED SOMEWHERE!)           */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* SASD C Engine Management Software                                 */
/* (c) Copyright Delco Electronics Europe 1994/95/96/97              */
/* Origin: from ibu_project:t3000_98 types.h                         */
/* Written by: Yves Clement / Craig Rolfe / Gregory Hogdal           */
/* Last update: 21-Jul-1998 by Frederique d'Ennetieres               */
/*-------------------------------------------------------------------*/


/* #include "options.h" */ /* for Ensemble6 */
/* #define Ensemble6 */

#include "lux_type.h" /* for SHORTCARD, CARDINAL, LONGCARD, BOOLEAN,
                                  Min (), Max () */

/**********************************************************************/
/*** This function is for debugging purpose to crash the software   ***/
/*** when the Fix point functions (for type and delta type) are     ***/
/*** wrongly used, with types of different precision, for instance. ***/
/*** This function must not be defined somewhere like that if it is ***/
/*** called, the linker will not find it and an error message will  ***/
/*** be generated (that's better than a rest on the bench!!!).      ***/
/**********************************************************************/

/*--- NOT TO BE DEFINED SOMEWHERE! ---*/
SHORTCARD CrashFunction (void);

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


/*--- FixDefConst converts a physical value fixed point constant ---*/
/*--- to a binary value fixed point constant                     ---*/
/*--- WARNING: Make sure that the floating value is not outside  ---*/
/*---  the boundaries of the Fixed Point type.                   ---*/
/*---  The internal value result is not rounded to the Min or Max---*/
/*---  of the type in that case!                                 ---*/
/*--- If Ensemble6 Id is defined, the behaviour of the macro is  ---*/
/*--- changed to avoid problem using the documentation (CFD      ---*/
/*--- builder) of "Cadre Ensemble v6".                           ---*/
/*--- Do not define the Ensemble6 Id for real code compilation!  ---*/

#ifdef Ensemble6
#define FixDefConst(ConstFloat,TypeName) \
((TypeName) (ConstFloat))
#else
#define FixDefConst(ConstFloat,TypeName) \
((TypeName) FactorRound (((ConstFloat) - Min_##TypeName) / Prec_##TypeName))
#endif

/*--- You must cast it. It is equivalent to the macro ---*/
/*--- FixDefConst but is intended to be used in the   ---*/
/*--- INLINE fixed point functions.            ---*/

#define Const(ConstFloat,Min,Prec) ( \
 (FactorRound (((ConstFloat) - (Min)) / (Prec))) \
 )

/*--- FixMaxDefConst defines the maximum value for the fixed type ---*/

#ifdef Ensemble6
#define FixMaxDefConst(Type) \
 ((Type) Max_##Type)
#else
#define FixMaxDefConst(Type) \
 ((Type) FactorRound ((Max_##Type - Min_##Type) / Prec_##Type))
#endif

/*--- FixMinDefConst defines the minimum value for the fixed type ---*/

#ifdef Ensemble6
#define FixMinDefConst(Type) \
 ((Type) Min_##Type)
#else
#define FixMinDefConst(Type) \
 ((Type) FactorRound ((Min_##Type - Min_##Type) / Prec_##Type))
#endif

/*--- FixLimitedDefConst converts a physical value fixed point constant ---*/
/*--- to a binary value fixed point constant Limited to Min and Max.    ---*/

#ifdef Ensemble6
#define FixLimitedDefConst(ConstFloat,Type) \
((Type) (((ConstFloat) <= Min_##Type) ? \
         (Min_##Type) : \
         (((ConstFloat) >= Max_##Type) ? \
          (Max_##Type) : \
          (ConstFloat))))
#else
#define FixLimitedDefConst(ConstFloat,Type) \
((Type) (((ConstFloat) <= Min_##Type) ? \
         (FixMinDefConst (Type)) : \
         (((ConstFloat) >= Max_##Type) ? \
          (FixMaxDefConst (Type)) : \
          (((ConstFloat) - Min_##Type) / Prec_##Type))))
#endif

/*--- FixLimitVarMin forces to fixed point variable to be bigger   ---*/
/*--- than the min of the destination type if it is bigger than    ---*/
/*--- the min of the origin type. Otherwise it passes the variable.---*/

#define FixLimitVarMin(VarOrg,TypeOrg,TypeDest) \
((Min_##TypeDest > Min_##TypeOrg) ? \
 Max ((VarOrg), FixLimitedDefConst(Min_##TypeDest,TypeOrg)) : \
 (VarOrg) \
)

/*--- FixLimitVarMax forces to fixed point variable to be smaller  ---*/
/*--- than the max of the destination type if it is smaller than   ---*/
/*--- the max of the origin type. Otherwise it passes the variable.---*/

#define FixLimitVarMax(VarOrg,TypeOrg,TypeDest) \
((Max_##TypeDest < Max_##TypeOrg) ? \
 Min ((VarOrg), FixLimitedDefConst(Max_##TypeDest,TypeOrg)) : \
 (VarOrg) \
)

/*--- FixLimitVar checks if the fixed point variable of TypeOrg ---*/
/*--- is in the range of TypeDest. The variable is forced to    ---*/
/*--- TypeDest limits if out of range.                          ---*/

#define FixLimitVar(VarOrg,TypeOrg,TypeDest) \
(FixLimitVarMin(FixLimitVarMax(VarOrg,TypeOrg,TypeDest), \
             TypeOrg,TypeDest) \
)

/*--- FixConvertLimitCheck converts a fixed point variable to another  ---*/
/*--- fixed point and checks that the result is mindest >= =< maxdest. ---*/

#ifdef Ensemble6
#define FixConvertLimitCheck(VarOrg,TypeOrg,TypeDest) \
((TypeDest) VarOrg)
#else
#define FixConvertLimitCheck(VarOrg,TypeOrg,TypeDest) \
(FixConvert (FixLimitVar(VarOrg,TypeOrg,TypeDest), \
             TypeOrg,TypeDest) \
)
#endif

/*--- FixConvert converts a fixed point variable to ---*/
/*--- another fixed point type.                     ---*/
/*--- If Ensemble6 Id is defined, the behaviour of the macro is  ---*/
/*--- changed to avoid having problems of id size exceeded for   ---*/
/*--- RFactors with "Cadre Ensemble v6".                         ---*/
/*--- Do not define the Ensemble6 Id for real code compilation!  ---*/

#ifdef Ensemble6
#define FixConvert(VarOrg,TypeOrg,TypeDest) \
((TypeDest) VarOrg)
#else
#define FixConvert(VarOrg,TypeOrg,TypeDest) \
((TypeDest) \
(((VarOrg) * FactorCasted (Prec_##TypeOrg * RFactor_##TypeOrg##_##TypeDest) + \
  FactorCasted ((Min_##TypeOrg - Min_##TypeDest) * RFactor_##TypeOrg##_##TypeDest)) / \
  FactorCasted (Prec_##TypeDest * RFactor_##TypeOrg##_##TypeDest)))
#endif


/*--- FixNoCkAdd adds two fixed point variables of the same type. ---*/

#define FixNoCkAdd(VarA,VarB,Type) ( \
 (Type)((VarA) + (VarB) + FactorCasted (Min_##Type / Prec_##Type)) \
 )

/*--- FixNoCkSub substracts VarB from VarA, of the same type. ---*/

#define FixNoCkSub(VarA,VarB,Type) ( \
 (Type)((VarA) - (VarB) - FactorCasted (Min_##Type / Prec_##Type)) \
 )

/*--- FixAbs Returns the absolute value of the fix type limited to ---*/
/*--- the maximum for that type.                                   ---*/

#define FixAbs(Var, Type) ( \
 (Min_##Type >= 0.0 || (Var) >= FixDefConst (0.0, Type)) ? \
  (Var) : \
 ((-Min_##Type <= Max_##Type || (Var) >= (FixDefConst (-Max_##Type, Type))) ? \
  (FixNoCkSub (FixDefConst (0.0,Type), (Var), Type)) : \
  (FixMaxDefConst (Type)) \
  ) \
 )


/*--- Returns |VarA-VarB|, two fixed point variables of the same type.---*/

#define FixSubAbs(VarA,VarB,TypeName) \
(((VarA) >= (VarB)) ? \
 FixSub (VarA, VarB, TypeName) : FixSub (VarB, VarA, TypeName))


/*--- Returns Min (FixAdd (OperandA, OperandB, TypeName), HighLim) ---*/
/*--- even if the calculation overflows or HighLim is the top      ---*/
/*--- boundary of the fixed point base type. OperandA, OperandB    ---*/
/*--- and HighLim are constants or variables of the type TypeName  ---*/
/*--- (so in counts).                                              ---*/
/*--- WARNING: Make sure first that:                               ---*/
/*---  (HighLim - OperandB) >= Min (TypeName)                      ---*/
/*---  (HighLim - OperandB) is in the range of the type            ---*/
/*---  HIGH RISK WITH BIAS TYPES!                                  ---*/

INLINE SHORTCARD FixAddLimitSHORTCARD (SHORTCARD VarA, SHORTCARD VarB,
    float Min, float Prec, SHORTCARD HighLim)
  {
  SHORTCARD Temp;

  Temp = VarA + VarB + (SHORTCARD)FactorCasted (Min / Prec);
  if (0.0 <= Min || VarB >= (SHORTCARD) Const (0.0, Min, Prec))
    {
    if ((Temp < VarA) || (Temp > HighLim))
      { /*--- overflow ---*/
      Temp = HighLim;
      }
    }
  else
    {
    if (Temp > VarA)
      { /*--- underflow ---*/
      Temp = (SHORTCARD) Const (Min, Min, Prec);
      }
    }
  return (Temp);
  } /*** End of FixAddLimitSHORTCARD ***/


INLINE CARDINAL FixAddLimitCARDINAL (CARDINAL VarA, CARDINAL VarB,
    float Min, float Prec, CARDINAL HighLim)
  {
  CARDINAL Temp;

  Temp = VarA + VarB + (CARDINAL)FactorCasted (Min / Prec);
  if (0.0 <= Min || VarB >= (CARDINAL) Const (0.0, Min, Prec))
    {
    if ((Temp < VarA) || (Temp > HighLim))
      { /*--- overflow ---*/
      Temp = HighLim;
      }
    }
  else
    {
    if (Temp > VarA)
      { /*--- underflow ---*/
      Temp = (CARDINAL) Const (Min, Min, Prec);
      }
    }
  return (Temp);
  } /*** End of FixAddLimitCARDINAL ***/


INLINE LONGCARD FixAddLimitLONGCARD (LONGCARD VarA, LONGCARD VarB,
    float Min, float Prec, LONGCARD HighLim)
  {
  LONGCARD Temp;

  Temp = VarA + VarB + FactorCasted (Min / Prec);
  if (0.0 <= Min || VarB >= (LONGCARD) Const (0.0, Min, Prec))
    {
    if ((Temp < VarA) || (Temp > HighLim))
      { /*--- overflow ---*/
      Temp = HighLim;
      }
    }
  else
    {
    if (Temp > VarA)
      { /*--- underflow ---*/
      Temp = (LONGCARD) Const (Min, Min, Prec);
      }
    }
  return (Temp);
  } /*** End of FixAddLimitLONGCARD ***/

#ifdef Ensemble6
#define FixAddHighLimit(VarA,VarB,Type,HighLim) \
((Type) (((VarA) < ((HighLim) - (VarB))) ? ((VarA) + (VarB)) : (HighLim)))
#else
#define FixAddHighLimit(VarA,VarB,Type,HighLim) ((Type) \
(sizeof (Type) == sizeof (SHORTCARD)) ? \
  FixAddLimitSHORTCARD ((SHORTCARD)(VarA), (SHORTCARD)(VarB), Min_##Type, Prec_##Type, (SHORTCARD)(HighLim)) : \
 (sizeof (Type) == sizeof (CARDINAL)) ? \
  FixAddLimitCARDINAL ((CARDINAL)(VarA), (CARDINAL)(VarB), Min_##Type, Prec_##Type, (CARDINAL)(HighLim)) : \
 (sizeof (Type) == sizeof (LONGCARD)) ? \
  FixAddLimitLONGCARD ((LONGCARD)(VarA), (LONGCARD)(VarB), Min_##Type, Prec_##Type, (LONGCARD)(HighLim)) : \
 CrashFunction ())
#endif


/*--- FixAdd adds two fixed point variables of the same type together ---*/

#ifdef Ensemble6
#define FixAdd(OperandA,OperandB,TypeName) \
((TypeName) (OperandA + OperandB))
#else
#define FixAdd(OperandA,OperandB,TypeName) \
(FixNoCkAdd (OperandA, OperandB, TypeName))
#endif

#ifdef Ensemble6
#define FixAddnBit(OperandA,OperandB,TypeName) \
((TypeName) (OperandA + OperandB))
#else
#define FixAddnBit(OperandA,OperandB,TypeName) \
(FixNoCkAdd (OperandA, OperandB, TypeName) & Mask_##TypeName)
#endif

/*--- FixIncrementWithLimit Increments var by prec and ---*/
/*--- checks for overflow.                             ---*/

#define FixIncrementWithLimit(VarA,Type) ( \
 (((VarA) < FixMaxDefConst (Type)) ? (++VarA) : (VarA)) \
 )

INLINE SHORTCARD FixSubLimitSHORTCARD (SHORTCARD VarA, SHORTCARD VarB,
    float Min, float Max, float Prec, SHORTCARD LowLim)
  {
  SHORTCARD Temp;

  Temp = VarA - VarB - (SHORTCARD)FactorCasted (Min / Prec);
  if (0.0 <= Min || VarB >= (SHORTCARD) Const (0.0, Min, Prec))
    {
    if ((Temp > VarA) || (Temp < LowLim))
      { /*--- underfow ---*/
      Temp = LowLim;
      }
    }
  else
    {
    if (Temp < VarA)
      { /*--- overflow ---*/
      Temp = (SHORTCARD) Const (Max, Min, Prec);
      }
    }
  return (Temp);
  } /*** End of FixSubLimitSHORTCARD ***/

INLINE CARDINAL FixSubLimitCARDINAL (CARDINAL VarA, CARDINAL VarB,
    float Min, float Max, float Prec, CARDINAL LowLim)
  {
  CARDINAL Temp; /* this uproc works better with words than bytes */

  Temp = VarA - VarB - (CARDINAL)FactorCasted (Min / Prec);
  if (0.0 <= Min || VarB >= (CARDINAL) Const (0.0, Min, Prec))
    {
    if ((Temp > VarA) || (Temp < LowLim))
      { /*--- underfow ---*/
      Temp = LowLim;
      }
    }
  else
    {
    if (Temp < VarA)
      { /*--- overflow ---*/
      Temp = (CARDINAL) Const (Max, Min, Prec);
      }
    }
  return (Temp);
  } /*** End of FixSubLimitCARDINAL ***/


INLINE LONGCARD FixSubLimitLONGCARD (LONGCARD VarA, LONGCARD VarB,
    float Min, float Max, float Prec, LONGCARD LowLim)
  {
  LONGCARD Temp; /* this uproc works better with words than bytes */

  Temp = VarA - VarB - FactorCasted (Min / Prec);
  if (0.0 <= Min || VarB >= (LONGCARD) Const (0.0, Min, Prec))
    {
    if ((Temp > VarA) || (Temp < LowLim))
      { /*--- underfow ---*/
      Temp = LowLim;
      }
    }
  else
    {
    if (Temp < VarA)
      { /*--- overflow ---*/
      Temp = (LONGCARD) Const (Max, Min, Prec);
      }
    }
  return (Temp);
  } /*** End of FixSubLimitLONGCARD ***/

#ifdef Ensemble6
#define FixSubLowLimit(VarA,VarB,Type,LowLim) \
((Type) (((VarA) > ((LowLim) + (VarB))) ? ((VarA) - (VarB)) : (LowLim)))
#else
#define FixSubLowLimit(VarA,VarB,Type,LowLim) \
((Type) \
 (sizeof (Type) == sizeof (SHORTCARD)) ? \
  FixSubLimitSHORTCARD ((SHORTCARD)(VarA), (SHORTCARD)(VarB), Min_##Type, Max_##Type, Prec_##Type, (SHORTCARD)(LowLim)) : \
 (sizeof (Type) == sizeof (CARDINAL)) ? \
  FixSubLimitCARDINAL ((CARDINAL)(VarA), (CARDINAL)(VarB), Min_##Type, Max_##Type, Prec_##Type, (CARDINAL)(LowLim)) : \
 (sizeof (Type) == sizeof (LONGCARD)) ? \
  FixSubLimitLONGCARD ((LONGCARD)(VarA), (LONGCARD)(VarB), Min_##Type, Max_##Type, Prec_##Type, (LONGCARD)(LowLim)) : \
 CrashFunction () \
)
#endif

/*--- FixSub substracts VarB of VarA, two fixed point ---*/
/*--- variables of the same type.                     ---*/

#ifdef Ensemble6
#define FixSub(OperandA,OperandB,TypeName) \
((TypeName) (OperandA - OperandB))
#else
#define FixSub(OperandA,OperandB,TypeName) \
(FixNoCkSub (OperandA, OperandB, TypeName))
#endif

#ifdef Ensemble6
#define FixSubnBit(OperandA,OperandB,TypeName) \
((TypeName) (OperandA - OperandB))
#else
#define FixSubnBit(OperandA,OperandB,TypeName) \
(FixNoCkSub (OperandA, OperandB, TypeName) & Mask_##TypeName)
#endif



/*--- FixDecrementWithLimit decrements var by prec and ---*/
/*--- checks for underflow.                            ---*/

#define FixDecrementWithLimit(VarA,Type) ( \
 (((VarA) > FixMinDefConst (Type)) ? (--VarA) : (VarA)) \
 )

/*--- Returns the difference between the A and B (A>B else 0) ---*/
/*--- in a delta type format (same precision and bias nul).   ---*/

#ifdef Ensemble6
#define FixGetDelta(VarA,VarB,RawType,DeltaType) \
((DeltaType) ((VarA) - (VarB)))
#else
#define FixGetDelta(VarA,VarB,RawType,DeltaType) \
((DeltaType) (((Prec_##RawType == Prec_##DeltaType) && \
               (Min_##DeltaType == 0.0)) ? \
              (((VarA) < (FixDefConst (Min_##RawType,      \
                                     RawType) + VarB)) ? \
               (FixDefConst (Min_##RawType, RawType)) :  \
               (VarA) - (VarB)) : \
              CrashFunction ()))
#endif


/*--- Returns the absolute difference between the A and B in ---*/
/*--- a delta type format (same precision and bias nul).     ---*/

#ifdef Ensemble6
#define FixGetAbsDelta(VarA,VarB,RawType,DeltaType) \
((DeltaType) (((VarA) > (VarB)) ? ((VarA) - (VarB)) \
                            : ((VarB) - (VarA))))
#else
#define FixGetAbsDelta(VarA,VarB,RawType,DeltaType) \
((DeltaType) (((Prec_##RawType == Prec_##DeltaType) && \
               (Min_##DeltaType == 0.0)) ? \
              (((VarA) > (VarB)) ? ((VarA) - (VarB)) \
                             : ((VarB) - (VarA))) : \
              (RawType) CrashFunction ()))
#endif


/*--- Returns the result of an addition between a element of a type ---*/
/*--- and a delta of that type. A check on the delta type format is ---*/
/*--- also performed.                                               ---*/

#ifdef Ensemble6
#define FixAddDelta(VarRaw,RawType,VarDelta,DeltaType) \
((RawType) ((VarRaw) + (VarDelta)))
#else
#define FixAddDelta(VarRaw,RawType,VarDelta,DeltaType) \
((RawType) (((Prec_##RawType == Prec_##DeltaType) && \
             (Min_##DeltaType == 0.0)) ? \
            (VarRaw) + (VarDelta) : CrashFunction ()))
#endif


/*--- Returns the result of an addition between a element of a type  ---*/
/*--- and a delta of that type. That result is clipped to a maximum. ---*/
/*--- A check on the delta type format is also performed.            ---*/

#ifdef Ensemble6
#define FixAddDeltaHighLimit(VarRaw,HighLimit,RawType,VarDelta,DeltaType) \
((RawType) (((VarRaw) > ((HighLimit) - (VarDelta))) ? \
            (HighLimit) : ((VarRaw) + (VarDelta))))
#else
#define FixAddDeltaHighLimit(VarRaw,HighLimit,RawType,VarDelta,DeltaType) \
((RawType) (((Prec_##RawType == Prec_##DeltaType) && \
             (Min_##DeltaType == 0.0) && \
             (sizeof (RawType) == sizeof (DeltaType))) ? \
            (((VarDelta) > FixGetDelta(HighLimit,VarRaw,RawType,DeltaType)) ? \
             (HighLimit) : ((VarRaw) + (VarDelta))) : \
            CrashFunction ()))
#endif


/*--- Returns the result of a substraction between an element of ---*/
/*--- a type and a delta of that type. A check on the delta type ---*/
/*--- format is also performed.                                  ---*/

#ifdef Ensemble6
#define FixSubDelta(VarRaw,RawType,VarDelta,DeltaType) \
((RawType) ((VarRaw) - (VarDelta)))
#else
#define FixSubDelta(VarRaw,RawType,VarDelta,DeltaType) \
((RawType) (((Prec_##RawType == Prec_##DeltaType) && \
             (Min_##DeltaType == 0.0) && \
             (sizeof (RawType) == sizeof (DeltaType))) ? \
            (VarRaw) - (VarDelta) : CrashFunction ()))
#endif


/*--- Returns the result of a substraction between an element of    ---*/
/*--- a type and a delta of that type. That result is clipped to    ---*/
/*--- a minimum. A check on the delta type format is also performed.---*/

#ifdef Ensemble6
#define FixSubDeltaLowLimit(VarRaw,LowLimit,RawType,VarDelta,DeltaType) \
((RawType) (((VarRaw) < ((LowLimit) + (VarDelta))) ? \
             (LowLimit) : (VarRaw) - (VarDelta)))
#else
#define FixSubDeltaLowLimit(VarRaw,LowLimit,RawType,VarDelta,DeltaType) \
((RawType) (((Prec_##RawType == Prec_##DeltaType) && \
             (Min_##DeltaType == 0.0) && \
             (sizeof (RawType) == sizeof (DeltaType))) ? \
            (((VarDelta) > FixGetDelta(VarRaw,LowLimit,RawType,DeltaType)) ? \
             (LowLimit) : ((VarRaw) - (VarDelta))) : \
            CrashFunction ()))
#endif


/*--- FixMultiply does the product of two fixed point variable,     ---*/
/*--- the result is of a different fixed point type.                ---*/
/*--- Remark: When used for asymptotic decaying, the 0 value is not ---*/
/*---         always reached, use FixDecayMult0To1 in that case.    ---*/
#ifdef Ensemble6
#define FixMultiply(VarOrgA,TypeOrgA,VarOrgB,TypeOrgB,TypeDest) \
((TypeDest) (VarOrgA) * (VarOrgB))
#else
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
#endif

/*--- FixDecayMult0To1 does the product of a variable by a multiplier ---*/
/*--- of type Multiplier_0_to_1 to decay the variable down to 0.      ---*/
/*--- FixMultiply should not be used for that purpose as it does      ---*/
/*--- not take into account the round up/down of the partial result   ---*/
/*--- when the variable is of a biased type.                          ---*/
/*--- The decay is only possible for values of types whose bias are   ---*/
/*--- lower or equal to zero.                                         ---*/

#ifdef Ensemble6
#define FixDecayMult0To1(Var,TypeVar,Mult) \
((TypeVar) ((Var) * (Mult)))
#else
#define FixDecayMult0To1(Var,TypeVar,Mult) \
((TypeVar) \
 ((Min_##TypeVar <= 0.0) ? \
  (((LONGCARD) (((LONGCARD) (Var + (LONGCARD) (Min_##TypeVar / Prec_##TypeVar)) * Mult) / \
                (LONGCARD) (1 / Prec_Multiplier_0_to_1)) - \
    (LONGCARD) (Min_##TypeVar / Prec_##TypeVar))) : \
   (LONGCARD) CrashFunction ()))
#endif


#define FixNonBiasedDiv(VarN,TypeN,VarD,TypeD,TypeQ) ((TypeQ) ( \
 (((Prec_##TypeN / Prec_##TypeD) / Prec_##TypeQ) >= 1.0) ? \
  ((FactorCasted ((Prec_##TypeN / Prec_##TypeD) / Prec_##TypeQ) * (VarN)) / \
     (VarD)) : \
  ((VarN) / (FactorCasted (Prec_##TypeQ / (Prec_##TypeN / Prec_##TypeD)) * \
     (VarD))) \
  ))

#define FixLimitDiv(Var,Limit) (((Var) > (Limit)) ? (Limit) : (Var))

/*--- FixNonBiasedDivide gives the quotient of two fixed point variable, ---*/
/*--- the result is of a different fixed point type                      ---*/

#define FixNonBiasedDivide(VarN,TypeN,VarD,TypeD,TypeQ) ( (TypeQ) ( \
 (Min_##TypeN != 0.0 || Min_##TypeD != 0.0 || Min_##TypeQ != 0.0) ? \
   CrashFunction () : \
   FixLimitDiv (FixNonBiasedDiv(VarN,TypeN,VarD,TypeD,TypeQ), \
     FixMaxDefConst (TypeQ)) \
  ))

/*--- FixNonBiasedShortDivide gives the quotient of two fixed point ---*/
/*--- variable, the result is of a different fixed point type       ---*/

#ifdef Ensemble6
#define FixNonBiasedShortDivide(VarNum,TypeNum,VarDiv,TypeDiv,TypeQuot) \
((VarNum) / (VarDiv))
#else
#define FixNonBiasedShortDivide(VarNum,TypeNum,VarDiv,TypeDiv,TypeQuot) \
(FixNonBiasedDivide (VarNum, TypeNum, VarDiv, TypeDiv, TypeQuot))
#endif

/*--- Converts percent fixed point types to multiplier fixed point types ---*/

#define FixConvertPercentToMultiplier(VarPercent,TypePercent,TypeMultiplier) \
 FixNonBiasedShortDivide (VarPercent, TypePercent, \
 FixDefConst (100.0, Fixed_Shortcard), Fixed_Shortcard, TypeMultiplier)


/*--- Converts multiplier fixed point types to percent fixed point types ---*/

#define FixConvertMultiplierToPercent(VarMultiplier,TypeMultiplier,TypePercent) \
 FixMultiply (VarMultiplier, TypeMultiplier, \
 FixDefConst (100.0, Fixed_Shortcard), Fixed_Shortcard, TypePercent)


/*--- Converts specifically Percent_W type to Percent_B and make sure ---*/
/*--- that the value of 100 % (in Percent_W) is converted to 99.6 %   ---*/
/*--- (in Percent_B) and not 0 %.                                     ---*/

#define FixConvertPercentWToPercentB(VarPercentW) \
(((VarPercentW) >= FixDefConst (Max_Percent_B, Percent_W)) ? \
 FixDefConst (Max_Percent_B, Percent_B) : \
 FixConvert (VarPercentW, Percent_W, Percent_B))


#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     040506 woz 3990 Implemented changes required for TCL TORQ integration.
* 2     050120 cpp 2279 (TCL) removed rounding causing overflow in
*                       FixConvertLimitCheck.
*
******************************************************************************/

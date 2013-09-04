#ifndef LUX_MATH
#define LUX_MATH


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


#define FixDefConst(ConstFloat,TypeName) \
((TypeName) FactorRound (((ConstFloat) - Min_##TypeName) / Prec_##TypeName))


/*--- You must cast it. It is equivalent to the macro ---*/
/*--- FixDefConst but is intended to be used in the   ---*/
/*--- INLINE fixed point functions.            ---*/

#define Const(ConstFloat,Min,Prec) ( \
 (FactorRound (((ConstFloat) - (Min)) / (Prec))) \
 )

/*--- FixMaxDefConst defines the maximum value for the fixed type ---*/


#define FixMaxDefConst(Type) \
 ((Type) FactorRound ((Max_##Type - Min_##Type) / Prec_##Type))


/*--- FixMinDefConst defines the minimum value for the fixed type ---*/

#define FixMinDefConst(Type) \
 ((Type) FactorRound ((Min_##Type - Min_##Type) / Prec_##Type))


/*--- FixLimitedDefConst converts a physical value fixed point constant ---*/
/*--- to a binary value fixed point constant Limited to Min and Max.    ---*/


#define FixLimitedDefConst(ConstFloat,Type) \
((Type) (((ConstFloat) <= Min_##Type) ? \
         (FixMinDefConst (Type)) : \
         (((ConstFloat) >= Max_##Type) ? \
          (FixMaxDefConst (Type)) : \
          (((ConstFloat) - Min_##Type) / Prec_##Type))))


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


#define FixConvertLimitCheck(VarOrg,TypeOrg,TypeDest) \
(FixConvert (FixLimitVar(VarOrg,TypeOrg,TypeDest), \
             TypeOrg,TypeDest) \
)


/*--- FixConvert converts a fixed point variable to ---*/
/*--- another fixed point type.                     ---*/
/*--- If Ensemble6 Id is defined, the behaviour of the macro is  ---*/
/*--- changed to avoid having problems of id size exceeded for   ---*/
/*--- RFactors with "Cadre Ensemble v6".                         ---*/
/*--- Do not define the Ensemble6 Id for real code compilation!  ---*/

#define FixConvert(VarOrg,TypeOrg,TypeDest) \
((TypeDest) \
(((VarOrg) * FactorCasted (Prec_##TypeOrg * RFactor_##TypeOrg##_##TypeDest) + \
  FactorCasted ((Min_##TypeOrg - Min_##TypeDest) * RFactor_##TypeOrg##_##TypeDest)) / \
  FactorCasted (Prec_##TypeDest * RFactor_##TypeOrg##_##TypeDest)))


#define ConvertSigned8bToSigned16b(x)   ((x>0x80)?(x |0xFF00):(x))

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

SHORTCARD FixAddLimitSHORTCARD (SHORTCARD VarA, SHORTCARD VarB,
    float Min, float Prec, SHORTCARD HighLim);


CARDINAL FixAddLimitCARDINAL (CARDINAL VarA, CARDINAL VarB,
    float Min, float Prec, CARDINAL HighLim);


LONGCARD FixAddLimitLONGCARD (LONGCARD VarA, LONGCARD VarB,
    float Min, float Prec, LONGCARD HighLim);



/*--- FixAdd adds two fixed point variables of the same type together ---*/

#define FixAdd(OperandA,OperandB,TypeName) \
(FixNoCkAdd (OperandA, OperandB, TypeName))

#define FixAddnBit(OperandA,OperandB,TypeName) \
(FixNoCkAdd (OperandA, OperandB, TypeName) & Mask_##TypeName)


/*--- FixIncrementWithLimit Increments var by prec and ---*/
/*--- checks for overflow.                             ---*/

#define FixIncrementWithLimit(VarA,Type) ( \
 (((VarA) < FixMaxDefConst (Type)) ? (++VarA) : (VarA)) \
 )

SHORTCARD FixSubLimitSHORTCARD (SHORTCARD VarA, SHORTCARD VarB,
    float Min, float Max, float Prec, SHORTCARD LowLim);


CARDINAL FixSubLimitCARDINAL (CARDINAL VarA, CARDINAL VarB,
    float Min, float Max, float Prec, CARDINAL LowLim);



LONGCARD FixSubLimitLONGCARD (LONGCARD VarA, LONGCARD VarB,
    float Min, float Max, float Prec, LONGCARD LowLim);


/*--- FixSub substracts VarB of VarA, two fixed point ---*/
/*--- variables of the same type.                     ---*/

#define FixSub(OperandA,OperandB,TypeName) \
(FixNoCkSub (OperandA, OperandB, TypeName))

#define FixSubnBit(OperandA,OperandB,TypeName) \
(FixNoCkSub (OperandA, OperandB, TypeName) & Mask_##TypeName)



/*************************************/
#ifndef         DLUX_ADD_HIGH_SUB_LOW
#define         DLUX_ADD_HIGH_SUB_LOW 1
#endif /*ifndef DLUX_ADD_HIGH_SUB_LOW*/

#if             DLUX_ADD_HIGH_SUB_LOW

/*DLUX defines*/
/*
 * There are four cases of AddHigh and SubLow, determined by Type and B parameters.
 *   1) Min##Type == 0.0   [unsigned, no bias, clip to High and Low]
 *   2) Min##Type >  0.0   [unsigned with linear transform bias, clip to High and Low]
 *   3) Min##Type <  0.0 with B >= zero for type  [signed with bias into unsigned]
 *   4) Min##Type <  0.0 with B < zero for type   [signed with bias into unsigned]
 * Usually the distinction between cases 3 and 4 can occur only at runtime.
 * The Luxembourg library supported all four cases through inline functions.
 * Since the Cosmic/Star12 C compiler only supports inline functions with void
 * return, the Singapore variant of the Luxembourg library converted the inline
 * functions into inline macros.  For AddHigh and SubLow, however, support was
 * dropped for the runtime distinction between cases 3 and 4, and all cases were
 * treated as if the B parameter were non-negative (equal to or greater than the
 * zero point after biasing).  As a consequence, all AddHigh and SubLow calls failed
 * whenever the B parameter was less than zero for Type.
 * Subsequently, AddSub_protected was written to handle CARDINAL (it can also handle
 * SHORTCARD), and placed in types.h.  It is both large (200 bytes larger than the
 * code here) and slow (155 cycles more than the code here), so was restricted to
 * specific locations where problems were known to occur.
 * The DLUX macros for these cases are four in number for each of AddHigh and SubLow.
 * AddHigh
 *   1) AddHighMin0
 *   2) AddHighMinP
 *   3) AddHighMinN
 *   4) AddMinMinN
 * SubLow
 *   1) SubLowMin0
 *   2) SubLowMinP
 *   3) SubLowMinN
 *   4) SubMaxMinN
 * (A) The Singapore AddHigh_protected and SubLow_protected symbols are routed into
 * code that handles all four cases listed above.  All three Type widths (SHORTCARD,
 * CARDINAL, and LONGCARD) are supported for the _protected symbols, not just some.
 * (B) Dlux macros FixAddHighLimit_Bge0 and FixSubLowLimit_Bge0 merge case 4 into 3,
 * similarly to the Singapore UNprotected macros, and can be used wherever the
 * application engineer is certain that the B parameter will always be greater than
 * or equal to zero for Type.  These _Bge0 macros have runtime footprints 11 bytes
 * smaller and complete their execution about 10 cycles quicker than the Singapore
 * UNprotected macros.
 * (C) DLUX macros FixAddHighLimit_bias and FixSubLowLimit_bias handle all four cases,
 * using compile time isolation of cases 1 and 2 from cases 3 and 4, and runtime
 * selection between cases 3 and 4 (whenever B is known at compile time, all four
 * cases will be isolated at compile time).  Consequently for cases 3 and 4, the _bias
 * macros have larger runtime footprints (+50 bytes) than the corresponding Singapore
 * UNprotected macros, but only consume four more cycles apiece, while having the
 * advantage of correct handling of case 4 (as well as cases 1 and 2).  For cases 1
 * and 2, the _bias macros convert into runtime code that is as small and fast as the
 * UNprotected singapore AddHigh and SubLow macros.
 * (D) To convert FixAddHighLimit into FixAddHighLimit_Bge0, set
 *    -dDLUX_ADD_ASSUME_BgtZ=1
 * into the compile time options for Cosmic/STAR12.  By default, this symbol will be
 * set to 0 if not defined by the application engineer.
 * (E) To convert FixSubLowLimit into FixSubLowLimit_Bge0, set
 *    -dDLUX_SUB_ASSUME_BgtZ=1
 * into the compile time options for Cosmic/STAR12.  By default, this symbol will be
 * set to 0 if not defined by the application engineer.
 * (F) Use of the _protected suffix takes precedence over the compile time options
 * identified in subsections (D) and (E) above.
 */

#ifndef         DLUX_SUB_ASSUME_BgtZ
#define         DLUX_SUB_ASSUME_BgtZ 0
#endif /*ifndef DLUX_SUB_ASSUME_BgtZ*/
#ifndef         DLUX_ADD_ASSUME_BgtZ
#define         DLUX_ADD_ASSUME_BgtZ 0
#endif /*ifndef DLUX_ADD_ASSUME_BgtZ*/


/*DLUX macros*/

#define FixBias(Type) (Type)FactorRound((Min_##Type)/(Prec_##Type))
#define FixZero(Type) FixDefConst(0.0,Type) /*round((0.0-min)/prec) 0>min=>pos,0<min=>neg*/

/*ADD and SUB macros*/

/*prerequisites (perq)*/
/*Add -- HighLim>B, which parallels existing lux/sing prerequisites*/
/*       exception: min<0.0 with B<zero  --  -*no prerequisite*- */
/*Sub -- 1) min==0  --  -*no prerequisite*- */
/*       2) min>0.0  --  bias+LowLim < ch_max  [ch_max==(T)(-1)]*/
/*       3) min<0.0 with B>=zero  --  LowLim <= zero*/
/*       4) min<0.0 with B<zero  --  -*no prerequisite*- */

#define AddZeq0(A,B,T)       ((T)((A)+(B)))
/*A=(iA+z) B=(iB+z), whence A+B=iA+iB+2z, thus sub z (FixZero==-FixBias) to restore offset*/
#define AddZne0(A,B,T)       ((T)((A)+(B)-FixZero(T)))
#define SubZeq0(A,B,T)       ((T)((A)-(B)))
/*A=(iA+z) B=(iB+z), whence A-B=iA-iB, thus add z (FixZero==-FixBias) to restore offset*/
#define SubZne0(A,B,T)       ((T)((A)-(B)+FixZero(T)))

/*MinN := minimum for type is negative*/

/*sub B>=z makes A smaller [min<0], makes L+B bigger [preq L<=z]*/
/*preq L<=z [no ovl for L+B]*/
#define SubLowMinN(A,B,T,L)  ((AddZne0(L,B,T)<(A)) ? SubZne0(A,B,T) : (L))
/*add B<z makes A smaller [min<0]*/
/*preq none*/
#define AddMinMinN(A,B,T)    ((AddZne0(A,B,T)<(A)) ? AddZne0(A,B,T) : ((T)(0)))

/*sub B<z makes A bigger [min<0]*/
/*preq none*/
#define SubMaxMinN(A,B,T)    ((SubZne0(A,B,T)>(A)) ? SubZne0(A,B,T) : ((T)(-1)))
/*add B>=z makes A bigger [min<0], makes H-B smaller*/
/*preq H>=B*/
#define AddHighMinN(A,B,T,H) ((SubZne0(H,B,T)>(A)) ? AddZne0(A,B,T) : (H))

/*MinP := minimum for type is positive: 0>FixZero(T)=(0.0-min)/prec; 0<FixBias(T)*/

/*sub B>=min>0 makes A smaller  L<=A-B+z [z<0] => L-z<=A-B [ovl unless A>=B]*/
/*preq bias+L<=max*/
#define SubLowMinP(A,B,T,L) (((A)>(B)) && ((T)((A)-(B))>(FixBias(T)+(L))) ? \
                            SubZne0(A,B,T) : (L))
/*add B>=min>0 makes A bigger  H>=A+B-z [-z>0] => H-B+z>=A [neg ovl unless H-B>=-z]*/
/*preq H>=B*/
#define AddHighMinP(A,B,T,H) (((FixBias(T)<=((H)-(B)))&&((A)<SubZne0(H,B,T))) ? \
                             AddZne0(A,B,T) : (H))

/*Min0 := minimum for type is 0: 0==FixZero(T)=(0.0-min)/prec; 0==FixBias(T)*/
/*preq none*/
#define SubLowMin0(A,B,T,L) ((((A)>(B))&&(L<=SubZeq0(A,B,T))) ? SubZeq0(A,B,T) : (L))
/*preq H>=B*/
#define AddHighMin0(A,B,T,H) ((SubZeq0(H,B,T)>(A)) ? AddZeq0(A,B,T) : (H))


#define FixSubLowLimit_Bge0( OperandA, OperandB, TypeName, LowLim ) \
 ( (0.0==Min_##TypeName) ? \
       SubLowMin0(OperandA,OperandB,TypeName,LowLim) : \
 ( (0.0< Min_##TypeName)  ? /*min positive => FixZero(T) negative, FixBias(T) pos*/ \
       SubLowMinP(OperandA,OperandB,TypeName,LowLim) : \
       SubLowMinN(OperandA,OperandB,TypeName,LowLim) ) )

#define FixSubLowLimit_bias( OperandA, OperandB, TypeName, LowLim ) \
 ( (0.0==Min_##TypeName) ? \
       SubLowMin0(OperandA,OperandB,TypeName,LowLim) : \
 ( (0.0< Min_##TypeName)  ? /*min positive => FixZero(T) negative, FixBias(T) pos*/ \
       SubLowMinP(OperandA,OperandB,TypeName,LowLim) : \
 (    (FixZero(TypeName)<=(OperandB)) ? /*FixMin(T) negative => FixZero(T) positive*/ \
     /*FixSubLowLimit_NoOvlChk(OperandA,OperandB,TypeName,LowLim) :*/ \
       SubLowMinN(OperandA,OperandB,TypeName,LowLim) : \
       SubMaxMinN(OperandA,OperandB,TypeName) ) ) )


#define FixAddHighLimit_Bge0( OperandA, OperandB, TypeName, HighLim ) \
 ( (0.0==Min_##TypeName) ? \
       AddHighMin0(OperandA,OperandB,TypeName,HighLim) : \
 ( (0.0< Min_##TypeName)  ? /*min positive => FixZero(T) negative, FixBias(T) pos*/ \
       AddHighMinP(OperandA,OperandB,TypeName,HighLim) : \
       AddHighMinN(OperandA,OperandB,TypeName,HighLim) ) )

#define FixAddHighLimit_bias( OperandA, OperandB, TypeName, HighLim ) \
 ( (0.0==Min_##TypeName) ? \
       AddHighMin0(OperandA,OperandB,TypeName,HighLim) : \
 ( (0.0< Min_##TypeName)  ? /*min positive => FixZero(T) negative, FixBias(T) pos*/ \
       AddHighMinP(OperandA,OperandB,TypeName,HighLim) : \
 (    (FixZero(TypeName)<=(OperandB)) ? /*FixMin(T) negative => FixZero(T) positive*/ \
     /*FixAddHighLimit_NoOvlChk(OperandA,OperandB,TypeName,HighLim) :*/ \
       AddHighMinN(OperandA,OperandB,TypeName,HighLim) : \
       AddMinMinN(OperandA,OperandB,TypeName) ) ) )

/*DLUX routing for AddHigh and SubLow*/

#define FixSubLowLimit_protected( A,B,T,L) FixSubLowLimit_bias( A,B,T,L)
#define FixAddHighLimit_protected(A,B,T,H) FixAddHighLimit_bias(A,B,T,H)

#if DLUX_SUB_ASSUME_BgtZ
#define FixSubLowLimit( A,B,T,L) FixSubLowLimit_Bge0( A,B,T,L)
#else /*if DLUX_SUB_ASSUME_BgtZ*/
#define FixSubLowLimit( A,B,T,L) FixSubLowLimit_bias( A,B,T,L)
#endif /*else*/ /*if DLUX_SUB_ASSUME_BgtZ*/

#if DLUX_ADD_ASSUME_BgtZ
#define FixAddHighLimit(A,B,T,H) FixAddHighLimit_Bge0(A,B,T,H)
#else /*if DLUX_ADD_ASSUME_BgtZ*/
#define FixAddHighLimit(A,B,T,H) FixAddHighLimit_bias(A,B,T,H)
#endif /*else*/ /*if DLUX_ADD_ASSUME_BgtZ*/

#endif     /*if DLUX_ADD_HIGH_SUB_LOW*/
/*************************************/

/*--- FixDecrementWithLimit decrements var by prec and ---*/
/*--- checks for underflow.                            ---*/

#define FixDecrementWithLimit(VarA,Type) ( \
 (((VarA) > FixMinDefConst (Type)) ? (--VarA) : (VarA)) \
 )

/*--- Returns the difference between the A and B (A>B else 0) ---*/
/*--- in a delta type format (same precision and bias nul).   ---*/


#define FixGetDelta(VarA,VarB,RawType,DeltaType) \
((DeltaType) (((Prec_##RawType == Prec_##DeltaType) && \
               (Min_##DeltaType == 0.0)) ? \
              (((VarA) < (FixDefConst (Min_##RawType,      \
                                     RawType) + VarB)) ? \
               (FixDefConst (Min_##RawType, RawType)) :  \
               (VarA) - (VarB)) : \
              CrashFunction ()))


/*--- Returns the absolute difference between the A and B in ---*/
/*--- a delta type format (same precision and bias nul).     ---*/


#define FixGetAbsDelta(VarA,VarB,RawType,DeltaType) \
((DeltaType) (((Prec_##RawType == Prec_##DeltaType) && \
               (Min_##DeltaType == 0.0)) ? \
              (((VarA) > (VarB)) ? ((VarA) - (VarB)) \
                             : ((VarB) - (VarA))) : \
              (RawType) CrashFunction ()))


/*--- Returns the result of an addition between a element of a type ---*/
/*--- and a delta of that type. A check on the delta type format is ---*/
/*--- also performed.                                               ---*/

#define FixAddDelta(VarRaw,RawType,VarDelta,DeltaType) \
((RawType) (((Prec_##RawType == Prec_##DeltaType) && \
             (Min_##DeltaType == 0.0)) ? \
            (VarRaw) + (VarDelta) : CrashFunction ()))


/*--- Returns the result of an addition between a element of a type  ---*/
/*--- and a delta of that type. That result is clipped to a maximum. ---*/
/*--- A check on the delta type format is also performed.            ---*/


#define FixAddDeltaHighLimit(VarRaw,HighLimit,RawType,VarDelta,DeltaType) \
((RawType) (((Prec_##RawType == Prec_##DeltaType) && \
             (Min_##DeltaType == 0.0) && \
             (sizeof (RawType) == sizeof (DeltaType))) ? \
            (((VarDelta) > FixGetDelta(HighLimit,VarRaw,RawType,DeltaType)) ? \
             (HighLimit) : ((VarRaw) + (VarDelta))) : \
            CrashFunction ()))


/*--- Returns the result of a substraction between an element of ---*/
/*--- a type and a delta of that type. A check on the delta type ---*/
/*--- format is also performed.                                  ---*/

#define FixSubDelta(VarRaw,RawType,VarDelta,DeltaType) \
((RawType) (((Prec_##RawType == Prec_##DeltaType) && \
             (Min_##DeltaType == 0.0) && \
             (sizeof (RawType) == sizeof (DeltaType))) ? \
            (VarRaw) - (VarDelta) : CrashFunction ()))


/*--- Returns the result of a substraction between an element of    ---*/
/*--- a type and a delta of that type. That result is clipped to    ---*/
/*--- a minimum. A check on the delta type format is also performed.---*/

#define FixSubDeltaLowLimit(VarRaw,LowLimit,RawType,VarDelta,DeltaType) \
((RawType) (((Prec_##RawType == Prec_##DeltaType) && \
             (Min_##DeltaType == 0.0) && \
             (sizeof (RawType) == sizeof (DeltaType))) ? \
            (((VarDelta) > FixGetDelta(VarRaw,LowLimit,RawType,DeltaType)) ? \
             (LowLimit) : ((VarRaw) - (VarDelta))) : \
            CrashFunction ()))

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

#define FixDecayMult0To1(Var,TypeVar,Mult) \
((TypeVar) \
 ((Min_##TypeVar <= 0.0) ? \
  (((LONGCARD) (((LONGCARD) (Var + (LONGCARD) (Min_##TypeVar / Prec_##TypeVar)) * Mult) / \
                (LONGCARD) (1 / Prec_Multiplier_0_to_1)) - \
    (LONGCARD) (Min_##TypeVar / Prec_##TypeVar))) : \
   (LONGCARD) CrashFunction ()))



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

#define FixNonBiasedShortDivide(VarNum,TypeNum,VarDiv,TypeDiv,TypeQuot) \
(FixNonBiasedDivide (VarNum, TypeNum, VarDiv, TypeDiv, TypeQuot))


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

/*--- FixMultiplyHighLimit, created by Q.W  ---*/
/*--- The high limitation is the max engineering value of destionation type      ---*/
/*--- Remark:be aware of the '>=' mark and FactorCast, they are really important ---*/
/*--- for the correction of final calculation result.                            ---*/

#define FixMultiplyHighLimit( VarOrgA, TypeOrgA, VarOrgB, TypeOrgB, TypeDest ) \
   ( ( ( int32_t ) ( ( ( ( ( ( FactorAbs ( Prec_##TypeOrgA * Prec_##TypeOrgB )  < 1.0 ) ? \
   ( ( ( uint32_t )( VarOrgA ) * ( VarOrgB ) ) / \
   FactorCasted( 1 / ( Prec_##TypeOrgA * Prec_##TypeOrgB ) ) ) : \
   ( ( ( uint32_t )(VarOrgA ) * ( VarOrgB ) ) * \
   FactorCasted( ( Prec_##TypeOrgA * Prec_##TypeOrgB ) ) ) ) \
   + \
   ( ( Min_##TypeOrgB > 0.0 ) ? \
   ( ( FactorAbs( Prec_##TypeOrgA * Min_##TypeOrgB  ) < \
   1.0 ) ? \
   ( ( uint32_t )( VarOrgA ) / \
   FactorCasted( 1 / ( Prec_##TypeOrgA * Min_##TypeOrgB ) ) ) : \
   ( ( uint32_t )( VarOrgA ) * \
   FactorCasted( ( Prec_##TypeOrgA * Min_##TypeOrgB ) ) ) ) :\
   ( ( Min_##TypeOrgB < 0.0 ) ? \
   ( ( FactorAbs( Prec_##TypeOrgA * ( Min_##TypeOrgB ) ) \
   < 1.0 ) ? \
   -( ( uint32_t )( VarOrgA ) / \
   FactorCasted( 1 / \
   ( Prec_##TypeOrgA * ( -Min_##TypeOrgB ) ) ) ) : \
   -( ( uint32_t )(VarOrgA ) * \
   FactorCasted( ( Prec_##TypeOrgA * \
   ( -Min_##TypeOrgB ) ) ) ) ) : \
   ( ( uint32_t )( 0 ) ) ) ) \
   + \
   ( ( Min_##TypeOrgA > 0.0 ) ? \
   ( ( FactorAbs( Min_##TypeOrgA * Prec_##TypeOrgB  ) < \
   1.0 ) ? \
   ( ( uint32_t )( VarOrgB ) / \
   FactorCasted( 1 / ( Min_##TypeOrgA * Prec_##TypeOrgB ) ) ) : \
   ( ( uint32_t )( VarOrgB ) * \
   FactorCasted( ( Min_##TypeOrgA * Prec_##TypeOrgB ) ) ) ) :\
   ( ( Min_##TypeOrgA < 0.0 ) ? \
   ( ( FactorAbs( ( Min_##TypeOrgA * Prec_##TypeOrgB ) ) < \
   1.0 ) ? \
   -( ( uint32_t )( VarOrgB ) / \
   FactorCasted( 1 / \
   ( ( -Min_##TypeOrgA ) * Prec_##TypeOrgB ) ) ) : \
   -( ( uint32_t )( VarOrgB ) * \
   FactorCasted( ( ( -Min_##TypeOrgA ) * \
   Prec_##TypeOrgB ) ) ) ) : \
   ( ( uint32_t )( 0 ) ) ) ) \
   + \
   FactorCasted( Min_##TypeOrgA * Min_##TypeOrgB ) ) ) )-FactorCasted( Max_##TypeDest ) ) >=( ( int32_t )( 0.0 ) ) ) ? \
   ( ( TypeDest)FactorCasted( (Max_##TypeDest-Min_##TypeDest)/Prec_##TypeDest) ) : \
   ( FixMultiply( VarOrgA, TypeOrgA, VarOrgB, TypeOrgB, TypeDest )  )  )


/*--- Returns OperandA - OperandB, checked for underflow           ---*/
#define SubLimit( OperandA, OperandB ) \
   ( ( ( OperandA ) > ( OperandB ) ) ? \
   ( ( OperandA ) - ( OperandB ) ) : \
   0 )

/* macros included from Daihatsu code for the knock logic - dj 04Aug  */

#define DecB( OperandA ) \
   ( ( ( OperandA ) > 0 ) ? ( OperandA ) - 1 : ( OperandA ) )


#define FixAddHighLimitNew( OperandA, OperandB, TypeName, HighLim ) \
   ( ( ( OperandA ) < FixSub( HighLim, Min(OperandB,HighLim), TypeName ) ) ? \
   FixAdd( OperandA, Min(OperandB,HighLim), TypeName ) : \
   ( HighLim ) )


typedef CARDINAL               FilterCoeff0to1;  /*--- Range 0.0 .. <=1.0 ---*/

#define Prec_FilterCoeff0to1   (Prec_Filter_Coefficient)
#define Min_FilterCoeff0to1    (0.0)
#define Max_FilterCoeff0to1    (1.0)

#define RFactor_Filter_Coefficient_Shortcard_Plus_Fraction   (1)
#define RFactor_Shortcard_Plus_Fraction_Filter_Coefficient   (1)
#define RFactor_Filter_Coefficient_FilterCoeff0to1           (256)
#define RFactor_FilterCoeff0to1_Filter_Coefficient           (256)

typedef LONGCARD               FilterCoeff0to1_L;  /*--- Range 0.0 .. <=1.0 ---*/

#define Prec_FilterCoeff0to1_L (Prec_Filter_Coefficient_W)
#define Min_FilterCoeff0to1_L  (0.0)
#define Max_FilterCoeff0to1_L  (1.0)

#define RFactor_Filter_Coefficient_L_Shortcard_Plus_Fraction (1)
#define RFactor_Shortcard_Plus_Fraction_Filter_Coefficient_L (1)
#define RFactor_Filter_Coefficient_W_FilterCoeff0to1_L       (65536)
#define RFactor_FilterCoeff0to1_L_Filter_Coefficient_W       (65536)
/************************************************************/
/***                                                      ***/
/***               LagFilter Calculations                 ***/
/***                                                      ***/
/***  NewValueFilt = OldValue (1 - Coefficient) +         ***/
/***                    (Coefficient * NewValue)          ***/
/***                                                      ***/
/***  with NewMultGain  = NewValue * Coefficient          ***/
/***       OneMinusGain = 1 - Coefficient                 ***/
/***       OldMultGain  = OldValue * OneMinusGain         ***/
/***       NewValueFilt = NewMultGain + OldMultGain       ***/
/***                                                      ***/
/************************************************************/

INLINE CARDINAL LagFilter ( CARDINAL NewValue,
                     CARDINAL OldValue,
                     Filter_Coefficient Coefficient)

  {
  Shortcard_Plus_Fraction NewMultGain, OldMultGain, NewValueFilt;
  FilterCoeff0to1        OneMinusGain;

  NewMultGain = FixMultiply (NewValue, Shortcard_Plus_Fraction,
                             Coefficient, Filter_Coefficient,
                             Shortcard_Plus_Fraction);

  OneMinusGain = FixSub (FixDefConst (1.0, FilterCoeff0to1),
                         FixConvert (Coefficient,
                                     Filter_Coefficient,
                                     FilterCoeff0to1),
                         FilterCoeff0to1);

  OldMultGain = FixMultiply (OldValue, Shortcard_Plus_Fraction,
                             OneMinusGain, FilterCoeff0to1,
                             Shortcard_Plus_Fraction);

  NewValueFilt = FixAdd (NewMultGain, OldMultGain, Shortcard_Plus_Fraction);

  return NewValueFilt;
  } /*** End of LagFilter ***/

#endif



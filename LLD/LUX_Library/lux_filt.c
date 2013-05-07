/*-------------------------------------------------------------------*/
/* Filename -  FILTER.C                                              */
/*                                                                   */
/* Purpose:                                                          */
/*                                                                   */
/* This module provides general purpose filter utilities.            */
/*                                                                   */
/* Filters are normally used to filter out unwanted transients from  */
/* input values.  An interpolation is done between the new value and */
/* the old value.  The equation for this is:                         */
/*                                                                   */
/*    Result = OldValue + Coefficient * ( NewValue - OldValue )      */
/*                                                                   */
/* The filter coefficient is a fraction (0.XXXX) from 0.0 to < 1.0   */
/* with either 16 or 8 bit resolution that can be calculated from    */
/* the time constant equation:                                       */
/*                                                                   */
/*                              -Loop / Tau                          */
/*    Coefficient = N * ( 1 - E             )                        */
/*                                                                   */
/* Where:                                                            */
/*                                                                   */
/*       N  = 256 for 8 bit coefficient                              */
/*       E  = 2.71828182845                                          */
/*    Loop  = Time between calls to this function                    */
/*     Tau  = Desired time constant                                  */
/*                                                                   */
/*                                                                   */
/* List of Function(s):                                              */
/*  Implem: LagFilter                                                */
/*          SlowLagFilter                                            */
/*          Lag_Filter_B                 -h-                         */
/*          Slow_Lag_Filter_B            -h-                         */
/*          Lag_Filter_W                 -h-                         */
/*          Lag_Filter_Approx_W          -h-                         */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* SASD C Engine Management Software                                 */
/* (c) Copyright Delco Electronics Europe 1999                       */
/* Origin: 06-Dec-1997 from rev 1.3 partition : math                 */
/* Written by: Christophe Laurent                                    */
/*-------------------------------------------------------------------*/


#include "lux_type.h" /* for CARDINAL, SHORTCARD, MAX_SHORTCARD,
                             Shortcard_Plus_Fraction,
                             Filter_Coefficient */
#include "lux_math.h" /* for FixMultiply (), FixSub (),
                             FixDefConst (), FixConvert (),
                             FixAdd () */

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

CARDINAL LagFilter (register CARDINAL NewValue,
                    register CARDINAL OldValue,
                    register Filter_Coefficient Coefficient)

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


/************************************************************/
/*** Same as LagFilter but with a Coefficient on 2 bytes  ***/
/************************************************************/

CARDINAL SlowLagFilter (register CARDINAL NewValue,
                        register CARDINAL OldValue,
                        register Filter_Coefficient_W Coefficient)

  {
  Shortcard_Plus_Fraction NewMultGain, OldMultGain, NewValueFilt;
  FilterCoeff0to1_L       OneMinusGain;

  NewMultGain = FixMultiply (NewValue, Shortcard_Plus_Fraction,
                             Coefficient, Filter_Coefficient_W,
                             Shortcard_Plus_Fraction);

  OneMinusGain = FixSub (FixDefConst (1.0, FilterCoeff0to1_L),
                         FixConvert (Coefficient,
                                     Filter_Coefficient_W,
                                     FilterCoeff0to1_L),
                         FilterCoeff0to1_L);

  OldMultGain = FixMultiply (OldValue, Shortcard_Plus_Fraction,
                             OneMinusGain, FilterCoeff0to1_L,
                             Shortcard_Plus_Fraction);

  NewValueFilt = FixAdd (NewMultGain, OldMultGain, Shortcard_Plus_Fraction);

  return NewValueFilt;
  } /*** End of SlowLagFilter ***/


/************************************************************/
/***                                                      ***/
/************************************************************/


CARDINAL Lag_Filter_B (register SHORTCARD NewValue,
                       register CARDINAL  OldValue,
                       register Filter_Coefficient Coefficient)

  {
  Shortcard_Plus_Fraction NewValueWithFraction;

  if (Coefficient != FixDefConst (0.0, Filter_Coefficient))
    {
    NewValueWithFraction = FixConvert (NewValue, Fixed_Shortcard,
                                       Shortcard_Plus_Fraction);
    return LagFilter (NewValueWithFraction,
                      OldValue, Coefficient);
    }
  else
    {
    return OldValue;
    }
  } /*** End of Lag_Filter_B ***/


/************************************************************/
/***                                                      ***/
/************************************************************/

CARDINAL Slow_Lag_Filter_B (register SHORTCARD NewValue,
                            register CARDINAL  OldValue,
                            register Filter_Coefficient_W Coefficient)

  {
  Shortcard_Plus_Fraction NewValueWithFraction;

  if (Coefficient != FixDefConst (0.0, Filter_Coefficient_W))
    {
    NewValueWithFraction = FixConvert (NewValue, Fixed_Shortcard,
                                       Shortcard_Plus_Fraction);
    return SlowLagFilter (NewValueWithFraction,
                          OldValue, Coefficient);
    }
  else
    {
    return OldValue;
    }
  } /*** End of Slow_Lag_Filter_B ***/


/************************************************************/
/***                                                      ***/
/************************************************************/

CARDINAL Lag_Filter_W (register CARDINAL NewValue,
                       register CARDINAL OldValue,
                       register Filter_Coefficient Coefficient)

  {
  if (Coefficient != FixDefConst (0.0, Filter_Coefficient))
    {
    return LagFilter (NewValue, OldValue, Coefficient);
    }
  else
    {
    return OldValue;
    }
  } /*** End of Lag_Filter_W ***/

/************************************************************************/
/***  First Order Lag Filter Approximation                            ***/
/************************************************************************/
/************************************************************************/
/* Calculates the first order lag filter based on the formula:          */
/* (new_filtered) = (old_filtered) + gain * (input - old_filter)        */
/*                                                                      */
/* As the fractional part of the result is not memorized between        */
/* consecutive executions of the routine, the gain times the delta      */
/* between the input and the old filtered value is forced to be equal   */
/* to at least one count in case the input and the filtered value are   */
/* different. This is done to ensure that the filtered value reaches    */
/* eventually the 2-byte input value. From a mathematical standpoint    */
/* this is wrong and does not allow to model accurately a first order   */
/* lag filter. The routine yields therefore only an approximation of    */
/* the result that would be expected from a real lag filter.            */
/************************************************************************/

CARDINAL Lag_Filter_Approx_W (register CARDINAL NewValue,
                              register CARDINAL OldValue,
                              register Filter_Coefficient Coefficient)

  {
  Fixed_Cardinal     Delta;
  Fixed_Cardinal     NewFiltdValue;
  BOOLEAN            PositiveDelta;

  /* Compute delta between input value (NewValue) and filtered value  */
  /* (OldValue).                                                      */
  if (NewValue > OldValue)
    {
    PositiveDelta = TRUE;
    Delta = FixSub (NewValue,
                    OldValue,
                    Fixed_Cardinal);
    }
  else
    {
    PositiveDelta = FALSE;
    Delta = FixSub (OldValue,
                    NewValue,
                    Fixed_Cardinal);
    }

  /* Compute gain * (input - old_filter) and ensure that delta is at  */
  /* least equal to one count if input <> old_filter                  */
  Delta =  FixMultiply (Delta, Fixed_Cardinal,
                        Coefficient, Filter_Coefficient,
                        Fixed_Cardinal);

  if ( (NewValue != OldValue)
     && (Coefficient != FixDefConst (0.0, Filter_Coefficient))
     && (Delta == FixDefConst (0.0, Fixed_Cardinal)) )
    {
    Delta = FixDefConst (1.0, Fixed_Cardinal);
    }

  /* Compute new filtered value                                       */
  if (PositiveDelta)
    {
    NewFiltdValue = FixAdd (OldValue, Delta, Fixed_Cardinal);
    }
  else
    {
    NewFiltdValue = FixSub (OldValue, Delta, Fixed_Cardinal);
    }

  return NewFiltdValue;

  } /*** End of Lag_Filter_Approx_W ***/

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     040506 woz 3990 Implemented changes required for TCL TORQ integration.
*
******************************************************************************/

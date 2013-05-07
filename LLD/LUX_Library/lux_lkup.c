/*-------------------------------------------------------------------*/
/* filename -  LOOKUP.C                                              */
/*                                                                   */
/* purpose:                                                          */
/*    provide a set of functions to handle the lookups.              */
/*                                                                   */
/* list of function(s):                                              */
/*  Inline: InterpolateB                                             */
/*          InterpolateW                                             */
/*          Table2DB                                                 */
/*          Table2DW                                                 */
/*  Implem: Table_2D_B          -h-                                  */
/*          Table_2D_W          -h-                                  */
/*          Table_3D_B          -h-                                  */
/*          Table_3D_W          -h-                                  */
/*          Index_Var_N_B       -h-                                  */
/*          Index_Var_N_W       -h-                                  */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* SASD C Engine Management Software                                 */
/* (c) Delco Electronics Europe 1997                                 */
/* Origin: written from scratch                                      */
/* Written by: Christophe Laurent                                    */
/*-------------------------------------------------------------------*/

#include "lux_type.h"  /* for SHORTCARD, CARDINAL, Fixed_Shortcard,
                              Shortcard_Plus_Fraction, Fixed_Cardinal */
#include "lux_math.h"  /* for FixConvert (), FixMultiply (), FixSub () */
#include "lux_lkup.h"  /* for Table_Index_Type */

SHORTCARD InterpolateB (SHORTCARD y1,
                       SHORTCARD y2,
                       SHORTCARD frac)
  {
  SHORTCARD delta;

  if (y1>y2)
    {
    frac = ~frac;
    delta = y1-y2;
    y1 = ((CARDINAL) (delta*frac)) >> 8;
    return (SHORTCARD) (y2 + y1);
    }
  else
    {
    delta = y2-y1;
    y2 = ((CARDINAL) (delta*frac)) >> 8;
    return (SHORTCARD) (y1 + y2 );
    }
  }

CARDINAL InterpolateB2W (SHORTCARD y1,
                         SHORTCARD y2,
                         SHORTCARD frac)
  {
  SHORTCARD delta;
  CARDINAL  temp;

  if (y1>y2)
    {
    frac = ~frac;
    delta = y1-y2;
    temp = (CARDINAL)delta * frac;
    return (((CARDINAL)y2 << 8) + temp);
    }
  else
    {
    delta = y2-y1;
    temp = (CARDINAL)delta * frac;
    return (((CARDINAL)y1 << 8) + temp);
    }
  }

/*************************************************************/
/*** Lookup and interpolate a 2 dimensional table of bytes ***/
/*************************************************************/

SHORTCARD Table_2D_B (const SHORTCARD *table, Table_Index_Type index)
  {
  SHORTCARD y1,y2,frac;
  const SHORTCARD *y;

  frac = Lo8Of16(index);
  y = table;
  y = y + Hi8Of16(index);

  if (frac==0) return *y;

  y1 = *y++;
  y2 =  *y;

  return InterpolateB (y1,y2,frac);
  }

CARDINAL Table_2D_B2_W (const SHORTCARD *table, Table_Index_Type index)
  {
  SHORTCARD y1,y2,frac;
  const SHORTCARD *y;

  frac = Lo8Of16(index);
  y = table;
  y = y + Hi8Of16(index);

  if (frac==0) return ((CARDINAL)(*y) << 8);

  y1 = *y++;
  y2 =  *y;

  return InterpolateB2W (y1,y2,frac);
  }

CARDINAL InterpolateW (CARDINAL y1,
                       CARDINAL y2,
                       SHORTCARD frac)
  {
  CARDINAL delta;

  if (y1>y2)
    {
    frac = ~frac;
    delta = y1-y2;
    y1 = (CARDINAL) (((LONGCARD) delta * frac) >> 8);
    return (CARDINAL) (y2 + y1);
    }
    else
    {
    delta = y2-y1;
    y2 = (CARDINAL) (((LONGCARD) delta * frac) >> 8);
    return (CARDINAL) (y1 + y2 );
    }
  }

CARDINAL InterpolateWW (CARDINAL y1,
                        CARDINAL y2,
                        CARDINAL frac)
  {
  CARDINAL delta;

  if (y1>y2)
    {
    frac = ~frac;
    delta = y1-y2;
    y1 = (CARDINAL) (((LONGCARD) delta * frac) >> 16);
    return (CARDINAL) (y2 + y1);
    }
    else
    {
    delta = y2-y1;
    y2 = (CARDINAL) (((LONGCARD) delta * frac) >> 16);
    return (CARDINAL) (y1 + y2 );
    }
  }

/*************************************************************/
/*** Lookup and interpolate a 2 dimensional table of words ***/
/*************************************************************/

CARDINAL  Table_2D_W (const  CARDINAL *table, Table_Index_Type index)
  {
  SHORTCARD frac;
  CARDINAL y1,y2;
  const CARDINAL *y;

  frac = Lo8Of16(index);
  y = table;
  y = y + Hi8Of16(index);

  if (frac==0) return *y;

  y1 = *y++;
  y2 =  *y;

  return InterpolateW (y1,y2,frac);
  }


/**********************************************************************/
/*   Three (3) dimentional table (of bytes) lookup and interpolate.   */
/*   Note: index is in the format that TBLS is expecting.             */
/*   X_Axle is Row, Y_Axle is Column                                  */
/**********************************************************************/

SHORTCARD Table_3D_B (const SHORTCARD *Table,
                      Table_Index_Type Index_X,
                      Table_Index_Type Index_Y,
                      CARDINAL Dimension_Y)
  {
  Fixed_Shortcard         IntegralPartIndexX;
  Fixed_Shortcard         X1Val, X2Val, TableOut;
  Fixed_Cardinal          OffsetTable;
  Shortcard_Plus_Fraction FractionPartIndexX;

  IntegralPartIndexX = FixConvert (Index_X, Shortcard_Plus_Fraction,
                                   Fixed_Shortcard);
  OffsetTable = FixMultiply (Dimension_Y, Fixed_Cardinal,
                             IntegralPartIndexX, Fixed_Shortcard,
                             Fixed_Cardinal);
  X1Val = Table_2D_B (Table+OffsetTable, Index_Y);
  FractionPartIndexX = FixSub (Index_X,
                               FixConvert (IntegralPartIndexX,
                                           Fixed_Shortcard,
                                           Shortcard_Plus_Fraction),
                               Shortcard_Plus_Fraction);
  if (FractionPartIndexX == 0) return X1Val;
  X2Val = Table_2D_B (Table+OffsetTable+Dimension_Y, Index_Y);
  TableOut = InterpolateB (X1Val, X2Val, FractionPartIndexX);
  return TableOut;
  } /*** End of Table_3D_B ***/

CARDINAL Table_3D_B2_W (const SHORTCARD *Table,
                        Table_Index_Type Index_X,
                        Table_Index_Type Index_Y,
                        CARDINAL Dimension_Y)
  {
  Fixed_Shortcard         IntegralPartIndexX;
  Fixed_Cardinal          X1Val, X2Val, TableOut;
  Fixed_Cardinal          OffsetTable;
  Shortcard_Plus_Fraction FractionPartIndexX;

  IntegralPartIndexX = FixConvert (Index_X, Shortcard_Plus_Fraction,
                                   Fixed_Shortcard);
  OffsetTable = FixMultiply (Dimension_Y, Fixed_Cardinal,
                             IntegralPartIndexX, Fixed_Shortcard,
                             Fixed_Cardinal);
  X1Val = Table_2D_B2_W (Table+OffsetTable, Index_Y);
  FractionPartIndexX = FixSub (Index_X,
                               FixConvert (IntegralPartIndexX,
                                           Fixed_Shortcard,
                                           Shortcard_Plus_Fraction),
                               Shortcard_Plus_Fraction);
  if (FractionPartIndexX == 0) return X1Val;
  X2Val = Table_2D_B2_W (Table+OffsetTable+Dimension_Y, Index_Y);
  TableOut = InterpolateW (X1Val, X2Val, FractionPartIndexX);
  return TableOut;
  } /*** End of Table_3D_B2W ***/


/**********************************************************************/
/*   Three (3) dimentional table (of words) lookup and interpolate.   */
/*   Note: index is in the format that TBLS is expecting.             */
/*   X_Axle is Row, Y_Axle is Column                                  */
/**********************************************************************/

CARDINAL  Table_3D_W (const CARDINAL *Table,
                      Table_Index_Type Index_X,
                      Table_Index_Type Index_Y,
                      CARDINAL Dimension_Y)
  {
  Fixed_Shortcard         IntegralPartIndexX;
  Fixed_Cardinal          OffsetTable, X1Val, X2Val, TableOut;
  Shortcard_Plus_Fraction FractionPartIndexX;

  IntegralPartIndexX = FixConvert (Index_X, Shortcard_Plus_Fraction,
                                   Fixed_Shortcard);
  OffsetTable = FixMultiply (Dimension_Y, Fixed_Cardinal,
                             IntegralPartIndexX, Fixed_Shortcard,
                             Fixed_Cardinal);
  X1Val = Table_2D_W (Table+OffsetTable, Index_Y);
  FractionPartIndexX = FixSub (Index_X,
                               FixConvert (IntegralPartIndexX,
                                           Fixed_Shortcard,
                                           Shortcard_Plus_Fraction),
                               Shortcard_Plus_Fraction);
  if (FractionPartIndexX == 0) return X1Val;
  X2Val = Table_2D_W (Table+OffsetTable+Dimension_Y, Index_Y);
  TableOut = InterpolateW (X1Val, X2Val, FractionPartIndexX);
  return TableOut;
  } /*** End of Table_3D_W ***/


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*** Index_Var_N_B                                                   ***/
/*** Index function for non-linear tables with byte size axis var.   ***/
/***                                                                 ***/
/*** The index function provides a way to rescale the lookup table   ***/
/*** input variable to the type 'index' needed to perform the lookup.***/
/*** The type 'index' is of the format XX.XX .                       ***/
/***                                                                 ***/
/*** The index function performs as well the limitation of the input ***/
/*** variable to the scope of the table. It a pointer to a breakpoint***/
/*** definition table and the number of breakpoints as parameters.   ***/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#if ( ( config_CPU_Type == option_M68HC12 ) \
 && ( config_Compiler_Vendor == option_COSMIC )  )
#pragma section (UNPAGE_CODE)
#endif
Table_Index_Type Index_Var_N_B (SHORTCARD X,
                                const SHORTCARD *BreakTable,
                                CARDINAL  NbOfBreakPoints)
  {
  CARDINAL          LowBoundary;
  CARDINAL          HighBoundary;
  CARDINAL          StepSize = NbOfBreakPoints/4;
  SHORTCARD         BreakPointDelta;
  Multiplier_0_to_1 FractionalPart;


  if (X <= BreakTable [0])
    {/*--- X smaller than first breakpoint ---*/
    return (Table_Index_Type) (0);
    }
  else if (X >= BreakTable [NbOfBreakPoints-1])
    {/*--- X larger than last breakpoint ---*/
    return (Table_Index_Type) ((NbOfBreakPoints-1)*256);
    }
  else
    {/*--- find 2 adjoining breakpoints of X ---*/
    if (X < BreakTable[NbOfBreakPoints/2])
      {/*--- X in first or second half of table ? ---*/
      LowBoundary = 0;
      HighBoundary = NbOfBreakPoints/2;
      }
    else
      {
      LowBoundary = NbOfBreakPoints/2;
      HighBoundary = NbOfBreakPoints-1;
      }
    while ((HighBoundary - LowBoundary) > 1)
      {/*--- loop until boundary points found ---*/
      if (X < BreakTable[HighBoundary - StepSize])
        {
        HighBoundary -= StepSize;
        }
      else
        {
        LowBoundary = HighBoundary - StepSize;
        }
      if (StepSize > 1) StepSize /= 2;
      }
    /*--- found boundaries, now interpolate to find fractional part ---*/
    X -= BreakTable[LowBoundary]; /*--- fractional part of X ---*/
    BreakPointDelta = BreakTable[HighBoundary] - BreakTable[LowBoundary];
    FractionalPart = FixNonBiasedShortDivide (X,
                                              Fixed_Shortcard,
                                              BreakPointDelta,
                                              Fixed_Shortcard,
                                              Multiplier_0_to_1);
    return (Table_Index_Type) (LowBoundary*256 + FractionalPart);
    }
  }
#if ( ( config_CPU_Type == option_M68HC12 ) \
 && ( config_Compiler_Vendor == option_COSMIC )  )
#pragma section ()
#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*** Index_Var_N_W                                                   ***/
/*** Index function for non-linear tables with word size axis var.   ***/
/***                                                                 ***/
/*** The index function provides a way to rescale the lookup table   ***/
/*** input variable to the type 'index' needed to perform the lookup.***/
/*** The type 'index' is of the format XX.XX .                       ***/
/***                                                                 ***/
/*** The index function performs as well the limitation of the input ***/
/*** variable to the scope of the table. It a pointer to a breakpoint***/
/*** definition table and the number of breakpoints as parameters.   ***/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Table_Index_Type Index_Var_N_W (CARDINAL  X,
                                const CARDINAL  *BreakTable,
                                CARDINAL  NbOfBreakPoints)

  {
  CARDINAL          LowBoundary;
  CARDINAL          HighBoundary;
  CARDINAL          StepSize = NbOfBreakPoints/4;
  CARDINAL          BreakPointDelta;
  Multiplier_0_to_1 FractionalPart;


  if (X <= BreakTable [0])
    {/*--- X smaller than first breakpoint ---*/
    return (Table_Index_Type) (0);
    }
  else if (X >= BreakTable [NbOfBreakPoints-1])
    {/*--- X larger than last breakpoint ---*/
    return (Table_Index_Type) ((NbOfBreakPoints-1)*256);
    }
  else
    {/*--- find 2 adjoining breakpoints of X ---*/
    if (X < BreakTable[NbOfBreakPoints/2])
      {/*--- X in first or second half of table ? ---*/
      LowBoundary = 0;
      HighBoundary = NbOfBreakPoints/2;
      }
    else
      {
      LowBoundary = NbOfBreakPoints/2;
      HighBoundary = NbOfBreakPoints-1;
      }
    while ((HighBoundary - LowBoundary) > 1)
      {/*--- loop until boundary points found ---*/
      if (X < BreakTable[HighBoundary - StepSize])
        {
        HighBoundary -= StepSize;
        }
      else
        {
        LowBoundary = HighBoundary - StepSize;
        }
      if (StepSize > 1) StepSize /= 2;
      }
    /*--- found boundaries, now interpolate to find fractional part ---*/
    X -= BreakTable[LowBoundary]; /*--- fractional part of X ---*/
    BreakPointDelta = BreakTable[HighBoundary] - BreakTable[LowBoundary];
    FractionalPart = FixNonBiasedShortDivide (X,
                                              Fixed_Cardinal,
                                              BreakPointDelta,
                                              Fixed_Cardinal,
                                              Multiplier_0_to_1);
    return (Table_Index_Type) (LowBoundary*256 + FractionalPart);
    }
  }

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     040506 woz 3990 Implemented changes required for TCL TORQ integration.
* kok_pt2#4
*       110620 as  9635 Made changes to build using COSMIC tool set
*
******************************************************************************/

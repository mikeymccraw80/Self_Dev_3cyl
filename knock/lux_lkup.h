#ifndef LUX_LKUP
#define LUX_LKUP

#include "lux_type.h" /* for SHORTCARD, CARDINAL, MAX_CARDINAL, RoundUp */


typedef CARDINAL Table_Index_Type;

#define Prec_Table_Index_Type (1.0/256)
#define Min_Table_Index_Type  (0.0)
#define Max_Table_Index_Type  (65535 * Prec_Table_Index_Type + Min_Table_Index_Type)

  /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
  /* This is the type used by the interpolation routines.            */
  /* The integer part is the table entry and the fraction is used    */
  /* in the interpolation.                                           */
  /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*************************************************************/
/*** Lookup and interpolate a 2 dimensional table of bytes ***/
/*************************************************************/

SHORTCARD Table_2D_B    (const SHORTCARD *, Table_Index_Type);
CARDINAL  Table_2D_B2_W (const SHORTCARD *, Table_Index_Type);
#define Table_2D_B2W(table,index,TypeOrg,TypeDest) \
((TypeDest) \
(((Table_2D_B2_W(table,index)) * FactorCasted (Prec_##TypeOrg/256 * RFactor_##TypeOrg##_##TypeDest*256) + \
  FactorCasted ((Min_##TypeOrg - Min_##TypeDest) * RFactor_##TypeOrg##_##TypeDest*256)) / \
  FactorCasted (Prec_##TypeDest * RFactor_##TypeOrg##_##TypeDest*256)))


/*************************************************************/
/*** Lookup and interpolate a 2 dimensional table of words ***/
/*************************************************************/

CARDINAL  Table_2D_W (const CARDINAL *, Table_Index_Type);


/*************************************************************/
/*** Lookup and interpolate a 3 dimensional table of bytes ***/
/*************************************************************/

SHORTCARD Table_3D_B    (const SHORTCARD *table,
                         Table_Index_Type index_X,
                         Table_Index_Type index_Y,
                         CARDINAL Dimension_Y);
CARDINAL  Table_3D_B2_W (const SHORTCARD *table,
                         Table_Index_Type index_X,
                         Table_Index_Type index_Y,
                         CARDINAL Dimension_Y);
#define Table_3D_B2W(table,index_X,index_Y,Dimension_Y,TypeOrg,TypeDest) \
((TypeDest) \
(((Table_3D_B2_W(table,index_X,index_Y,Dimension_Y) * FactorCasted (Prec_##TypeOrg/256 * RFactor_##TypeOrg##_##TypeDest*256) + \
  FactorCasted ((Min_##TypeOrg - Min_##TypeDest) * RFactor_##TypeOrg##_##TypeDest*256)) / \
  FactorCasted (Prec_##TypeDest * RFactor_##TypeOrg##_##TypeDest*256))))


/*************************************************************/
/*** Lookup and interpolate a 3 dimensional table of words ***/
/*************************************************************/

CARDINAL  Table_3D_W (const CARDINAL *table,
                      Table_Index_Type index_X,
                      Table_Index_Type index_Y,
                      CARDINAL Dimension_Y);

/****************************************/
/*** Input variable indexing function ***/
/****************************************/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*** Index function :                                                ***/
/***                                                                 ***/
/*** The index function provides a way to rescale the lookup table   ***/
/*** input variable to the type 'index' needed to perform the lookup.***/
/*** The type 'index' is of the format XX.XX .                       ***/
/***                                                                 ***/
/*** The index function performs as well the limitation of the input ***/
/*** variable to the scope of the table, it handles as well the      ***/
/*** problem that occurs when the last breakpoint of the table is    ***/
/*** outside of the range of the input variable.                     ***/
/***                                                                 ***/
/*** WATCH OUT!!! this function does not check if the rescale of     ***/
/***              the input variable to form 'index' overflows the   ***/
/***              limit of the CARDINAL type. This would add checks  ***/
/***              in every table lookup indexing which would be      ***/
/***              unneeded in the large majority of the cases. Take  ***/
/***              care when creating very large tables.              ***/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

INLINE Table_Index_Type Index_Var (CARDINAL X,
                                          float Prec_In_Var,
                                          float Bias_X,
                                          float From_X,
                                          float To_X,
                                          float By_X)
  {
  Table_Index_Type MaxValueForIndexVariable;
  Table_Index_Type index=Min_Table_Index_Type;
  float            ConversConst;
  float            Offset;

  /*--- Determine the maximum value of the lookup index variable ---*/
  if ((To_X - Bias_X)  / Prec_In_Var  >= (float)MAX_CARDINAL)
    {
    /*--- if true, last breakpoint of table is outside of the range of X ---*/
    MaxValueForIndexVariable = (CARDINAL)(((To_X - From_X) / Prec_Table_Index_Type) / By_X - Prec_In_Var );
    }
  else
    {
    MaxValueForIndexVariable = (CARDINAL)(((To_X - From_X) / Prec_Table_Index_Type) / By_X);
    }

  if (X <= (CARDINAL)((From_X - Bias_X)/ Prec_In_Var) )
    {
    /*--- Limit the lookup index variable to the minimum value to access ---*/
    /*--- the first breakpoint of the table.                             ---*/
    index = Min_Table_Index_Type;
    }
  else
    {
    ConversConst = (By_X * Prec_Table_Index_Type / Prec_In_Var);
    Offset = ((From_X - Bias_X)/ By_X / Prec_Table_Index_Type);

    if (ConversConst >= 256.0)
      {
      /*--- Conversion constant large enough, no need to rescale ---*/
      index = X / (CARDINAL) ConversConst - (CARDINAL) Offset;
      }
    else
      {
      if (ConversConst >= 1.0)
        {
        /*--- Conversion constant too small, rescale to get better precision ---*/
        /*--- in the calculation.                                            ---*/
        index = (CARDINAL)((LONGCARD)X*256/(CARDINAL)(ConversConst*256)) -
              (CARDINAL) Offset;
        }
      else
        {
        if (ConversConst > 1.0/256)
          {
          /*--- Conversion constant too small, rescale to get better precision ---*/
          /*--- in the calculation.                                            ---*/
          index = (CARDINAL)((LONGCARD)X*(CARDINAL)((1/(ConversConst/256)))/256) -
                 (CARDINAL) Offset;
          }
        else
          {
          /*--- Conversion constant small enough, no need to rescale ---*/
          index = (CARDINAL)((LONGCARD)X / ConversConst) - (CARDINAL) Offset;
          }
        }
      }
    /*--- Limit to maximum value to reach the last breakpoint of the table ---*/
    if (index >= MaxValueForIndexVariable)
      index = MaxValueForIndexVariable;
    }
  return index;
  } /*** End of Index_Var ***/

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
Table_Index_Type Index_Var_N_B (SHORTCARD X,
                                const SHORTCARD *BreakTable,
                                CARDINAL  NbOfBreakPoints);

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
                                CARDINAL  NbOfBreakPoints);

/****************************************/
/*** Input variable indexing function ***/
/****************************************/

#define IndexVar(InputVar, InputType, TableName) \
          Index_Var ((CARDINAL) InputVar, Prec_##InputType, \
                     Min_##InputType, TableName##_BkPt1, \
                     TableName##_BkPtEnd, \
                     SubAbs(TableName##_BkPtEnd, TableName##_BkPt1)/ \
                     (TableName##_Size-1))

#define IndexVarX(InputVar, InputType, TableName) \
          Index_Var ((CARDINAL) InputVar, Prec_##InputType, \
                     Min_##InputType, TableName##_XBkPt1, \
                     TableName##_XBkPtEnd, \
                     SubAbs(TableName##_XBkPtEnd, TableName##_XBkPt1)/ \
                     (TableName##_XSize-1))

#define IndexVarY(InputVar, InputType, TableName) \
          Index_Var ((CARDINAL) InputVar, Prec_##InputType, \
                     Min_##InputType, TableName##_YBkPt1, \
                     TableName##_YBkPtEnd, \
                     SubAbs(TableName##_YBkPtEnd, TableName##_YBkPt1)/ \
                     (TableName##_YSize-1))

#define Table3DB(TableName, Index_X, Index_Y) \
          Table_3D_B (TableName, Index_X, Index_Y, TableName##_YSize);

#define Table3DW(TableName, Index_X, Index_Y) \
          Table_3D_W (TableName [0], Index_X, Index_Y, TableName##_YSize);


/*************************************************************/
/*** Index the input variable,                             ***/
/*** Lookup and interpolate a 2 dimensional table of bytes ***/
/*************************************************************/

INLINE SHORTCARD Lookup_2D_B (CARDINAL Var,
                                     float Prec,
                                     float Bias_X,
                                     float From_X,
                                     float To_X,
                                     float By_X,
                                     const SHORTCARD *table_start)

  {
  Table_Index_Type index;

  index = Index_Var (Var,
                     Prec,
                     Bias_X,
                     From_X,
                     To_X,
                     By_X);
  return Table_2D_B (table_start,
                     index);
  } /*** End of Lookup_2D_B ***/


/*************************************************************/
/*** Index the input variable,                             ***/
/*** Lookup and interpolate a 2 dimensional table of words ***/
/*************************************************************/

INLINE CARDINAL Lookup_2D_W (CARDINAL Var,
                                    float Prec,
                                    float Bias_X,
                                    float From_X,
                                    float To_X,
                                    float By_X,
                                    const CARDINAL *table_start)

  {
  Table_Index_Type index;

  index = Index_Var (Var,
                     Prec,
                     Bias_X,
                     From_X,
                     To_X,
                     By_X);
  return Table_2D_W (table_start,
                     index);
  } /*** End of Lookup_2D_W ***/

/*************************************************************/
/*** Index the input variable,                             ***/
/*** Lookup and interpolate a 3 dimensional table of bytes ***/
/*************************************************************/

INLINE SHORTCARD Lookup_3D_B (CARDINAL Var_X,
                                     float Prec_X,
                                     float Bias_X,
                                     float From_X,
                                     float To_X,
                                     float By_X,
                                     CARDINAL Var_Y,
                                     float Prec_Y,
                                     float Bias_Y,
                                     float From_Y,
                                     float To_Y,
                                     float By_Y,
                                     CARDINAL Dimension_Y,
                                     const SHORTCARD *table_start)

  {
  Table_Index_Type index_X,index_Y;

  index_X = Index_Var (Var_X,
                       Prec_X,
                       Bias_X,
                       From_X,
                       To_X,
                       By_X);
  index_Y = Index_Var (Var_Y,
                       Prec_Y,
                       Bias_Y,
                       From_Y,
                       To_Y,
                       By_Y);
  return Table_3D_B (table_start,
                     index_X,
                     index_Y,
                     Dimension_Y);
  } /*** End of Lookup_3D_B ***/


/*************************************************************/
/*** Index the input variable,                             ***/
/*** Lookup and interpolate a 3 dimensional table of words ***/
/*************************************************************/

INLINE CARDINAL Lookup_3D_W (CARDINAL Var_X,
                                    float Prec_X,
                                    float Bias_X,
                                    float From_X,
                                    float To_X,
                                    float By_X,
                                    CARDINAL Var_Y,
                                    float Prec_Y,
                                    float Bias_Y,
                                    float From_Y,
                                    float To_Y,
                                    float By_Y,
                                    CARDINAL Dimension_Y,
                                    const CARDINAL *table_start)

  {
  Table_Index_Type index_X,index_Y;

  index_X = Index_Var (Var_X,
                       Prec_X,
                       Bias_X,
                       From_X,
                       To_X,
                       By_X);
  index_Y = Index_Var (Var_Y,
                       Prec_Y,
                       Bias_Y,
                       From_Y,
                       To_Y,
                       By_Y);
  return Table_3D_W (table_start,
                     index_X,
                     index_Y,
                     Dimension_Y);
  } /*** End of Lookup_3D_W ***/

SHORTCARD InterpolateB (SHORTCARD y1, SHORTCARD y2, SHORTCARD frac);
CARDINAL InterpolateB2W (SHORTCARD y1, SHORTCARD y2, SHORTCARD frac);
CARDINAL InterpolateW (CARDINAL y1, CARDINAL y2, SHORTCARD frac);
CARDINAL InterpolateWW (CARDINAL y1, CARDINAL y2, CARDINAL frac);

#endif


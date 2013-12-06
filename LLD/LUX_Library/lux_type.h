#ifndef LUX_TYPE
#define LUX_TYPE
/*-------------------------------------------------------------------*/
/* filename -  lux_type.h                                            */
/*                                                                   */
/* purpose:                                                          */
/*    This file contains all new global types created.               */
/*    remark: here are defined normally the generic types only, but  */
/*            specific types are also defined here as soon as they   */
/*            are used in calibration files.                         */
/*                                                                   */
/* Usage:                                                            */
/*   AddHighLimit makes a scalar addition up to a limit,             */
/* even if the calculation overflows or the limit is the top         */
/* boundary of the operands type.                                    */
/*                                                                   */
/*   SubLowLimit makes a scalar substraction down to a limit,        */
/* even if the calculation underflows or the limit is the bottom     */
/* boundary of the operand type (=0).                                */
/*                                                                   */
/*   Max returns maximum of two values (scalar of fixed point).      */
/* This is mainly used for limitation of FixMultiply                 */
/*                                                                   */
/*   Min returns minimum of two values (scalar of fixed point).      */
/* This is mainly used for limitation of FixMultiply                 */
/*                                                                   */
/*   SubAbs returns |x-y| of two scalar variables                    */
/*                                                                   */
/*   Hi8Of16 returns the Most Significant Byte (8 bits) of a word    */
/* (16 bits).                                                        */
/*                                                                   */
/*   Lo8Of16 returns the Least Significant Byte (8 bits) of a word   */
/* (16 bits).                                                        */
/*                                                                   */
/*   Hi16Of32 returns the Most Significant Word (16 bits) of a long  */
/* (32 bits).                                                        */
/*                                                                   */
/*   Lo16Of32 returns the Least Significant Word (16 bits) of a long */
/* (32 bits).                                                        */
/*                                                                   */
/*   HexNibbleToAscii converts a 4 bit value (low nibble of param)   */
/* into its Ascii reprensation in Hexadecimal.                       */
/*                                                                   */
/* list of function(s):                                              */
/*  Macro:  AddHighLimit                                             */
/*          SubLowLimit                                              */
/*          Max                                                      */
/*          Min                                                      */
/*          SubAbs                                                   */
/*          Hi8Of16                                                  */
/*          Lo8Of16                                                  */
/*          Hi16Of32                                                 */
/*          Lo16Of32                                                 */
/* inline : HexNibbleToAscii                                         */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* DELPHI Delco Luxembourg C Engine Management Software              */
/*  Copyright 2001-2008, Delphi Technologies, Inc.  */
/*-------------------------------------------------------------------*/

//#include "t_gentypes.h"
#include "reuse.h"
#include "hal.h"

// #define MULTITARGET_FRAMEWORK

/*-------------------------------------*/
/*---                               ---*/
/*--- Fundamental C type boundaries ---*/
/*---                               ---*/
/*-------------------------------------*/

#define CharBit                 (8)     /*--- Number of bits in type char  ---*/
#define SCharMax              (127)     /*--- Max value for signed char    ---*/
#define SCharMin    (-SCharMax - 1)     /*--- Min value for signed char    ---*/
#define UCharMax             (255u)     /*--- Max value for unsigned char  ---*/
#define UCharMin               (0u)     /*--- Min value for unsigned char  ---*/

#define CharMax          (UCharMax)     /*--- Max value for char           ---*/
#define CharMin          (UCharMin)     /*--- Min value for char           ---*/

#define ShortMax            (32767)     /*--- Max value for short          ---*/
#define ShortMin    (-ShortMax - 1)     /*--- Min value for short          ---*/
#define UShortMax          (65535u)     /*--- Max value for unsigned short ---*/
#define UShortMin              (0u)     /*--- Min value for unsigned short ---*/

#define IntMax              (32767)     /*--- Max value for int            ---*/
#define IntMin        (-IntMax - 1)     /*--- Min value for int            ---*/
#define UIntMax            (65535u)     /*--- Max value for unsigned int   ---*/
#define UIntMin                (0u)     /*--- Min value for unsigned int   ---*/

#define LongMax       (2147483647L)     /*--- Max value for long           ---*/
#define LongMin      (-LongMax - 1)     /*--- Min value for long           ---*/
#define ULongMax     (4294967295uL)     /*--- Max value for unsigned long  ---*/
#define ULongMin              (0uL)     /*--- Min value for unsigned long  ---*/

#define Bit15Mask          (0x8000)
#define Bit14Mask          (0x4000)
#define Bit13Mask          (0x2000)
#define Bit12Mask          (0x1000)
#define Bit11Mask          (0x0800)
#define Bit10Mask          (0x0400)
#define Bit9Mask           (0x0200)
#define Bit8Mask           (0x0100)
#define Bit7Mask             (0x80)
#define Bit6Mask             (0x40)
#define Bit5Mask             (0x20)
#define Bit4Mask             (0x10)
#define Bit3Mask             (0x08)
#define Bit2Mask             (0x04)
#define Bit1Mask             (0x02)
#define Bit0Mask             (0x01)
#define Bit15Position          (15)
#define Bit14Position          (14)
#define Bit13Position          (13)
#define Bit12Position          (12)
#define Bit11Position          (11)
#define Bit10Position          (10)
#define Bit9Position            (9)
#define Bit8Position            (8)
#define Bit7Position            (7)
#define Bit6Position            (6)
#define Bit5Position            (5)
#define Bit4Position            (4)
#define Bit3Position            (3)
#define Bit2Position            (2)
#define Bit1Position            (1)
#define Bit0Position            (0)

//#if OS_SCHEDULER_10ms == CeSYST_AVAILABLE
//#define RegularRtiPrescaler  (0.010000)
//#else
#define RegularRtiPrescaler  (0.015625)
//#endif

/*---------------------------------*/
/*---                           ---*/
/*--- Scalar types redefinition ---*/
/*---     (Modula-GM style)     ---*/
/*---                           ---*/
/*---------------------------------*/

typedef unsigned char    SHORTCARD;
#define MIN_SHORTCARD          (0u)     /*--- 000000000h ---*/
#define MAX_SHORTCARD        (255u)     /*--- 0000000FFh ---*/
/*      CALDEF
*|      types.SHORTCARD
*|      {
*|         : kind = fixed;
*|         : precision = (1.0);
*|         : range = (0.0) TO (255.0);
*|      }
*/

/* typedef signed char SHORTINT; */
#ifndef MIN_SHORTINT
#define MIN_SHORTINT         (-128)     /*--- 000000080h ---*/
#endif
#ifndef MAX_SHORTINT
#define MAX_SHORTINT          (127)     /*--- 00000007Fh ---*/
#endif

typedef unsigned short    CARDINAL;
#define MIN_CARDINAL           (0u)     /*--- 000000000h ---*/
#define MAX_CARDINAL       (65535u)     /*--- 00000FFFFh ---*/

/*typedef signed short        INTEGER;  */
#ifndef MIN_INTEGER
#define MIN_INTEGER        (-32768)     /*--- 000008000h ---*/
#endif
#ifndef MAX_INTEGER
#define MAX_INTEGER         (32767)     /*--- 000007FFFh ---*/
#endif

typedef unsigned long     LONGCARD;
#define MIN_LONGCARD          (0uL)     /*--- 000000000h ---*/
#define MAX_LONGCARD (4294967295uL)     /*--- 0FFFFFFFFh ---*/

/*typedef signed long         LONGINT;*/
#ifndef MIN_LONGINT
#define MIN_LONGINT  (-2147483648L)     /*--- 080000000h ---*/
#endif
#ifndef MAX_LONGINT
#define MAX_LONGINT   (2147483647L)     /*--- 07FFFFFFFh ---*/
#endif

/*--------------------------------*/
/*---                          ---*/
/*---    Mathematical types    ---*/
/*---                          ---*/
/*--------------------------------*/

/*--- NULL Pointer ---*/
#ifndef NULL
#define NULL ((void*)(0))
#endif

// /*--- Boolean Type ---*/
// #ifdef MULTITARGET_FRAMEWORK
// /* TRICORE The multitarget architecture defines a incompatible bool type     */
// /* For more information about boolean definition see : tc1775_tasking.h file */
// typedef boolean_T BOOLEAN;
// #else
// typedef
  // enum
    // {FALSE, TRUE}
  // BOOLEAN;
// #endif

/*--- BitField Type ---*/
typedef unsigned int BITFIELD;

/*--- Hysteresis Type ---*/
typedef
  enum
    {High_Threshold, Low_Threshold}
  Hysteresis_Pair_Type;

#define Hysteresis_Pair (2)
/*      CALDEF
*|      types.Hysteresis_Pair
*|      {
*|         : kind = define_annotation;
*|         : units = "(0=HighThrs_/_1=LowThrs)";
*|         : table = (0,1);
*|      }
*/

/*---------------------------------*/
/*---                           ---*/
/*---        Fixed Types        ---*/
/*---                           ---*/
/*---    TypeIds = 256..65535   ---*/
/*---     (for fixed types)     ---*/
/*---                           ---*/
/*---  MAJOR RULE: Fixed types  ---*/
/*--- must always be represented---*/
/*--- be unsigned types. Signed ---*/
/*--- fixed point types must be ---*/
/*--- biased.                   ---*/
/*---                           ---*/
/*---------------------------------*/

/*-----------------------------*/
/*---                       ---*/
/*---  Ordinal Fixed Types  ---*/
/*---                       ---*/
/*-----------------------------*/

typedef SHORTCARD                                              Fixed_Shortcard;
#define Prec_Fixed_Shortcard                                              (1.0)
#define Min_Fixed_Shortcard                                               (0.0)
#define Max_Fixed_Shortcard                                             (255.0)

typedef CARDINAL                                                Fixed_Cardinal;
#define Prec_Fixed_Cardinal                                               (1.0)
#define Min_Fixed_Cardinal                                                (0.0)
#define Max_Fixed_Cardinal                                            (65535.0)

typedef LONGCARD                                                Fixed_Longcard;
#define Prec_Fixed_Longcard                                               (1.0)
#define Min_Fixed_Longcard                                                (0.0)
#define Max_Fixed_Longcard                                       (4294967295.0)

typedef INTEGER                                                  Fixed_Integer;
#define Prec_Fixed_Integer                                                (1.0)
#define Min_Fixed_Integer                                              (-32768)
#define Max_Fixed_Integer      (65535 * Prec_Fixed_Integer + Min_Fixed_Integer)

typedef CARDINAL                                       Shortcard_Plus_Fraction;
#define Prec_Shortcard_Plus_Fraction                                (1.0 / 256)
#define Min_Shortcard_Plus_Fraction                                       (0.0)
#define Max_Shortcard_Plus_Fraction                                     (255.0)

typedef LONGCARD                                        Cardinal_Plus_Fraction;
#define Prec_Cardinal_Plus_Fraction                               (1.0 / 65536)
#define Min_Cardinal_Plus_Fraction                                        (0.0)
#define Max_Cardinal_Plus_Fraction                                    (65535.0)

typedef SHORTCARD                                                     Fraction;
#define Prec_Fraction                                               (1.0 / 256)
#define Min_Fraction                                                      (0.0)
#define Max_Fraction                                          (255 * 1.0 / 256)

typedef CARDINAL                                                    Fraction_W;
#define Prec_Fraction_W                                           (1.0 / 65536)
#define Min_Fraction_W                                                    (0.0)
#define Max_Fraction_W                                    (65535 * 1.0 / 65536)

typedef LONGCARD                                                    Fraction_L;
#define Prec_Fraction_L                                    (1.0 / 4294967296.0)
#define Min_Fraction_L                                                    (0.0)
#define Max_Fraction_L                      (4294967295.0 * 1.0 / 4294967296.0)

typedef SHORTCARD                                                AdCountsFracB;
#define Prec_AdCountsFracB                                                (4.0)
#define Min_AdCountsFracB                                                 (0.0)
#define Max_AdCountsFracB                                               (255.0)

typedef SHORTCARD                                                   AdCounts_B;
#define Prec_AdCounts_B                                                   (1.0)
#define Min_AdCounts_B                                                    (0.0)
#define Max_AdCounts_B                                                  (255.0)

typedef CARDINAL                                                    AdCounts_W;
#define Prec_AdCounts_W                                                   (1.0)
#define Min_AdCounts_W                                                    (0.0)
#define Max_AdCounts_W                                                 (1023.0)

typedef CARDINAL                                                 AdCounts_Base;
#define Prec_AdCounts_Base                                                (1.0)
#define Min_AdCounts_Base                                                 (0.0)
#define Max_AdCounts_Base                                             (65535.0)

typedef CARDINAL                                          AdCountsPlusFraction;
#define Prec_AdCountsPlusFraction                                    (1.0 / 64)
#define Min_AdCountsPlusFraction                                          (0.0)
#define Max_AdCountsPlusFraction                                 (65535.0 / 64)

/*---  RFactors for Ordinal Types  ---*/

#define RFactor_Fixed_Shortcard_Shortcard_Plus_Fraction \
                                           (1.0 / Prec_Shortcard_Plus_Fraction)
#define RFactor_Shortcard_Plus_Fraction_Fixed_Shortcard \
                                           (1.0 / Prec_Shortcard_Plus_Fraction)
#define RFactor_Fixed_Shortcard_Fixed_Cardinal      (1.0 / Prec_Fixed_Cardinal)
#define RFactor_Shortcard_Plus_Fraction_Cardinal_Plus_Fraction \
                                            (1.0 / Prec_Cardinal_Plus_Fraction)
#define RFactor_Cardinal_Plus_Fraction_Shortcard_Plus_Fraction \
                                            (1.0 / Prec_Cardinal_Plus_Fraction)
#define RFactor_Fixed_Longcard_Fixed_Cardinal       (1.0 / Prec_Fixed_Cardinal)
#define RFactor_Fixed_Cardinal_Fixed_Longcard       (1.0 / Prec_Fixed_Cardinal)
#define RFactor_Fixed_Shortcard_Fixed_Longcard     (1.0 / Prec_Fixed_Shortcard)
#define RFactor_Fixed_Longcard_Fixed_Shortcard     (1.0 / Prec_Fixed_Shortcard)
#define RFactor_Table_Index_Type_Fixed_Shortcard                        (256.0)
#define RFactor_AdCounts_W_AdCountsPlusFraction                          (64.0)
#define RFactor_AdCountsPlusFraction_AdCounts_W                          (64.0)
#define RFactor_AdCountsPlusFraction_AdCountsFracB                      (256.0)
#define RFactor_AdCounts_W_AdCounts_Base                                  (1.0)
#define RFactor_AdCounts_Base_AdCounts_W                                  (1.0)
#define RFactor_AdCounts_Base_AdCountsPlusFraction                       (64.0)
#define RFactor_AdCountsPlusFraction_AdCounts_Base                       (64.0)
#define RFactor_AdCounts_W_AdCountsFracB                                (256.0)
#define RFactor_AdCountsFracB_AdCounts_W                                (256.0)

/*---------------------------------*/
/*---                           ---*/
/*---    Percent Fixed Types    ---*/
/*---                           ---*/
/*---------------------------------*/

/*--------------------------------------------------------------*/
/*--- Type                     Range (%)        Precision    ---*/
/*--- ------------             --------------  ------------  ---*/
/*--- Percent_B                0.0  ..  99.6     0.390625 %  ---*/
/*--- Percent_Biased           25.0 ..  124.6    0.390625 %  ---*/
/*--- Percent_Neq_Biased      -50.0 ..  49.6     0.390625 %  ---*/
/*--- Percent_Plus_Fraction    0.0  ..  99.998   0.001526 %  ---*/
/*--- Percent_W                0.0  ..  1599.9   0.024414 %  ---*/
/*--------------------------------------------------------------*/

typedef SHORTCARD                                                    Percent_B;
#define Prec_Percent_B                                            (100.0 / 256)
#define Min_Percent_B                                                     (0.0)
#define Max_Percent_B                                       (255 * 100.0 / 256)
/*      CALDEF
*|      types.Percent_B
*|      {
*|         : kind = fixed;
*|         : precision = (0.390625);
*|         : range = (0.000000) TO (99.609375);
*|      }
*/

typedef CARDINAL                                                Percent_B_Base;
#define Prec_Percent_B_Base                                    (Prec_Percent_B)
#define Min_Percent_B_Base                                                (0.0)
#define Max_Percent_B_Base   (65535 * Prec_Percent_B_Base + Min_Percent_B_Base)

typedef SHORTCARD                                               Percent_Biased;
#define Prec_Percent_Biased                                       (100.0 / 256)
#define Min_Percent_Biased                                               (25.0)
#define Max_Percent_Biased                           (255 * 100.0 / 256 + 25.0)

typedef SHORTCARD                                           Percent_Neg_Biased;
#define Prec_Percent_Neg_Biased                                   (100.0 / 256)
#define Min_Percent_Neg_Biased                                          (-50.0)
#define Max_Percent_Neg_Biased                       (255 * 100.0 / 256 - 50.0)

typedef CARDINAL                                       Percent_Neg_Biased_Base;
#define Prec_Percent_Neg_Biased_Base                           (Prec_Percent_B)
#define Min_Percent_Neg_Biased_Base                   (-32768 * Prec_Percent_B)
#define Max_Percent_Neg_Biased_Base \
                         (65535 * Prec_Percent_B + Min_Percent_Neg_Biased_Base)

typedef CARDINAL                              Percent_Neg_Biased_Plus_Fraction;
#define Prec_Percent_Neg_Biased_Plus_Fraction           (Prec_Percent_B / 64.0)
#define Min_Percent_Neg_Biased_Plus_Fraction \
                               (-32768 * Prec_Percent_Neg_Biased_Plus_Fraction)
#define Max_Percent_Neg_Biased_Plus_Fraction (65535 * \
  Prec_Percent_Neg_Biased_Plus_Fraction + Min_Percent_Neg_Biased_Plus_Fraction)

typedef CARDINAL                                         Percent_Plus_Fraction;
#define Prec_Percent_Plus_Fraction                              (100.0 / 65536)
#define Min_Percent_Plus_Fraction                                         (0.0)
#define Max_Percent_Plus_Fraction                       (65535 * 100.0 / 65536)

typedef LONGCARD                                    Percent_Plus_Fraction_Base;
#define Prec_Percent_Plus_Fraction_Base            (Prec_Percent_Plus_Fraction)
#define Min_Percent_Plus_Fraction_Base                                    (0.0)
#define Max_Percent_Plus_Fraction_Base \
                               (MAX_LONGCARD * Prec_Percent_Plus_Fraction_Base)

typedef CARDINAL                                                     Percent_W;
#define Prec_Percent_W                                           (100.0 / 4096)
#define Min_Percent_W                                                     (0.0)
#define Max_Percent_W                                    (65535 * 100.0 / 4096)

typedef SHORTCARD                                               PercentPerStep;
#define Prec_PercentPerStep                                     (100.0 / 65536)
#define Min_PercentPerStep                                                (0.0)
#define Max_PercentPerStep                                (255 * 100.0 / 65536)

typedef SHORTCARD                                               Percent_BPrec1;
#define Prec_Percent_BPrec1                                               (1.0)
#define Min_Percent_BPrec1                                                (0.0)
#define Max_Percent_BPrec1                        (100.0 * Prec_Percent_BPrec1)

typedef SHORTCARD                                        Percent_m12p8to12p7_B;
#define Prec_Percent_m12p8to12p7_B                                 (1.0 / 10.0)
#define Min_Percent_m12p8to12p7_B                                       (-12.8)
#define Max_Percent_m12p8to12p7_B            (255 * Prec_Percent_m12p8to12p7_B)

typedef SHORTCARD                                            Percent_0to25p5_B;
#define Prec_Percent_0to25p5_B                                     (1.0 / 10.0)
#define Min_Percent_0to25p5_B                                             (0.0)
#define Max_Percent_0to25p5_B                    (255 * Prec_Percent_0to25p5_B)

/*---------------------------------------------------------------------------*/
/*--- type needed for the representation in percent of the qadc input     ---*/
/*--- voltage which input as a divider by 3 versus the ECM input pin.     ---*/
/*--- 5 volts in input of the QADC gives the maximum value $FFC0 = 65472, ---*/
/*--- wich are in fact 15 volts at the input of the ECM because of the    ---*/
/*--- divider by 3. 15 volts at the input of the ECM is 300 %             ---*/
/*--- 15 volts at the input of the ECM is 300 %                           ---*/
/*--- 5 volts at the input of the ECM is 100 %                            ---*/
/*---------------------------------------------------------------------------*/
/*--- Type                                    Range (%)      Precision    ---*/
/*--- ------------                          --------------  ------------  ---*/
/*--- PercentOfAD5VoltsDividedBy3_W         0.0  ..  300.0   0.004582 %   ---*/
/*---------------------------------------------------------------------------*/

typedef CARDINAL                                 PercentOfAD5VoltsDividedBy3_W;
#define Prec_PercentOfAD5VoltsDividedBy3_W     /* 300 / 65472 = */  (25.0/5456)
#define Min_PercentOfAD5VoltsDividedBy3_W                                 (0.0)
#define Max_PercentOfAD5VoltsDividedBy3_W                               (300.0)

typedef CARDINAL                                              ETC_Percent_Type;
#define Prec_ETC_Percent_Type                                    (100.0 / 1024)
#define Min_ETC_Percent_Type                                              (0.0)
#define Max_ETC_Percent_Type                           (65535.0 * 100.0 / 1024)
/*      CALDEF INFORMATION
*|      etc_type.ETC_Percent_Type
*|      {
*|         : kind = fixed;
*|         : precision = (100 / 1024);
*|         : range = (0.000000) TO (65535 * (100 / 1024));
*|      }
*/

/*---  Axis Enumerations for Percent Types  ---*/

#define Counts_0to24by4_Steps                                              (13)
/*      CALDEF      */
#define Counts_0to256by16_Steps                                            (17)
/*      CALDEF      */
#define Counts_0to96by16_Steps                                              (7)
/*      CALDEF      */
#define Counts_0to64by16_Steps                                              (5)
/*      CALDEF      */
#define Counts_0to80by16_Steps                                              (6)
/*      CALDEF      */
#define Counts_12to236by16_Steps                                           (15)
/*      CALDEF      */
#define Percent_0to25by3p125_Steps                                          (9)
/*      CALDEF      */
#define Percent_0to31p25by3p125_Steps                                      (11)
/*      CALDEF      */
#define Percent_0to30by3p75_Steps                                           (9)
/*      CALDEF      */
#define Percent_0to100by6p25_Steps                                         (17)
/*      CALDEF
*|      types.Percent_0to100by6p25_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Percent";
*|         : table = (0 TO 100 BY 6.25);
*|      }
*/
#define Percent_0to50by6p25_Steps                                           (9)
/*      CALDEF      */
#define Percent_0to25by6p25_Steps                                           (5)
/*      CALDEF      */
#define Percent_50to100by6p25_Steps                                         (9)
/*      CALDEF      */
#define Percent_0to128by8_Steps                                            (17)
/*      CALDEF      */
#define Percent_0to100by10_Steps                                           (11)
/*      CALDEF
*|      types.Percent_0to100by10_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Percent";
*|         : table = (0 TO 100 BY 10);
*|      }
*/
#define Percent_0to100by5_Steps                                            (21)
/*      CALDEF
*|      types.Percent_0to100by5_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Percent";
*|         : table = (0 TO 100 BY 5);
*|      }
*/
#define Percent_0to100by12p5_Steps                                          (9)
/*      CALDEF      */
#define Percent_37p5to100by12p5_Steps                                       (6)
/*      CALDEF      */
#define Percent_37p5to100by6p25_Steps                                      (11)
/*      CALDEF      */
#define Percent_0to100by25_Steps                                            (5)
/*      CALDEF      */
#define Percent_0to100by3p125_Steps                                        (33)
/*      CALDEF      */
#define Percent_0to400by20_Steps                                           (21)
/*      CALDEF      */
#define Percent_0to200by10_Steps                                           (21)
/*      CALDEF      */
#define Counts_0_to_15        (15)
/*      CALDEF      */

/*---  RFactors for Percent Types  ---*/

#define RFactor_Percent_Neg_Biased_Plus_Fraction_Percent_Neg_Biased_Base \
                                                              (16384.0 / 100.0)
#define RFactor_Percent_Neg_Biased_Base_Percent_Neg_Biased_Plus_Fraction \
                                                              (16384.0 / 100.0)
#define RFactor_Percent_B_Base_Percent_W                                (40.96)
#define RFactor_Percent_m12p8to12p7_B_Percent_0to25p5_B                  (10.0)
#define RFactor_Percent_0to25p5_B_Percent_Plus_Fraction               (65536.0)
#define RFactor_PercentOfAD5VoltsDividedBy3_W_Percent_B     (4369.0 * 256 / 20)
#define RFactor_Percent_B_PercentOfAD5VoltsDividedBy3_W \
                              (RFactor_PercentOfAD5VoltsDividedBy3_W_Percent_B)
#define RFactor_Percent_B_Percent_BPrec1                                (256.0)
#define RFactor_Percent_Biased_Percent_B_Base                     (256.0 / 100)
#define RFactor_Percent_B_Base_Percent_Biased                     (256.0 / 100)
#define RFactor_Percent_Neg_Biased_Base_Percent_B_Base            (256.0 / 100)
#define RFactor_Percent_B_Base_Percent_Neg_Biased_Base            (256.0 / 100)
#define RFactor_Percent_Neg_Biased_Percent_B_Base                 (256.0 / 100)
#define RFactor_Percent_B_Base_Percent_Neg_Biased                 (256.0 / 100)
#define RFactor_Percent_B_Percent_Neg_Biased_Base                 (256.0 / 100)
#define RFactor_Percent_Neg_Biased_Base_Percent_B                 (256.0 / 100)
#define RFactor_Percent_BPrec1_Percent_Neg_Biased_Base            (256.0 / 100)
#define RFactor_Percent_Neg_Biased_Base_Percent_BPrec1            (256.0 / 100)
#define RFactor_Percent_Neg_Biased_Percent_Neg_Biased_Base        (256.0 / 100)
#define RFactor_Percent_Neg_Biased_Base_Percent_Neg_Biased        (256.0 / 100)
#define RFactor_Percent_B_Percent_Plus_Fraction                        (655.36)
#define RFactor_Percent_B_Percent_W                                     (40.96)
#define RFactor_Percent_Plus_Fraction_Percent_B                        (655.36)
#define RFactor_Percent_W_Percent_B                                     (40.96)
#define RFactor_Percent_Plus_Fraction_Percent_W                        (655.36)
#define RFactor_Percent_Plus_Fraction_Base_Percent_Plus_Fraction       (655.36)
#define RFactor_Percent_B_Fixed_Shortcard                               (256.0)
#define RFactor_Percent_B_Base_Percent_B                            (256.0/100)
#define RFactor_Percent_B_Base_Percent_Plus_Fraction \
                                      (RFactor_Percent_B_Percent_Plus_Fraction)
#define RFactor_Percent_BPrec1_Percent_B                                (256.0)
#define RFactor_ETC_Percent_Type_Percent_B                              (10.24)
#define RFactor_Percent_B_ETC_Percent_Type                              (10.24)
#define RFactor_ETC_Percent_Type_Percent_W                              (40.96)

/*---------------------------------*/
/*---                           ---*/
/*---   Multiplier Fixed Types  ---*/
/*---                           ---*/
/*---------------------------------*/

typedef SHORTCARD                                         Multiplier_0_to_0p25;
#define Prec_Multiplier_0_to_0p25                                  (0.25 / 256)
#define Min_Multiplier_0_to_0p25                                          (0.0)
#define Max_Multiplier_0_to_0p25                             (255 * 0.25 / 256)

typedef CARDINAL                                        Multiplier_0_to_0p25_W;
#define Prec_Multiplier_0_to_0p25_W           (Prec_Multiplier_0_to_0p25 / 256)
#define Min_Multiplier_0_to_0p25_W                   (Min_Multiplier_0_to_0p25)
#define Max_Multiplier_0_to_0p25_W        (65535 * Prec_Multiplier_0_to_0p25_W)
/*      CALDEF
*|      types.Multiplier_0_to_0p25_W
*|      {
*|         : kind = fixed;
*|         : precision = (0.0009765625/256);
*|         : range = (0.000000) TO (65535 * 0.0009765625/256);
*|      }
*/

typedef SHORTCARD                                          Multiplier_0_to_0p5;
#define Prec_Multiplier_0_to_0p5                                    (0.5 / 256)
#define Min_Multiplier_0_to_0p5                                           (0.0)
#define Max_Multiplier_0_to_0p5                               (255 * 0.5 / 256)
/*      CALDEF
*|      types.Multiplier_0_to_0p5
*|      {
*|         : kind = fixed;
*|         : precision = (0.001953);
*|         : range = (0.000000) TO (255 * 0.001953);
*|      }
*/

typedef CARDINAL                                         Multiplier_0_to_0p5_W;
#define Prec_Multiplier_0_to_0p5_W             (Prec_Multiplier_0_to_0p5 / 256)
#define Min_Multiplier_0_to_0p5_W                     (Min_Multiplier_0_to_0p5)
#define Max_Multiplier_0_to_0p5_W          (65535 * Prec_Multiplier_0_to_0p5_W)

typedef SHORTCARD                                            Multiplier_0_to_1;
#define Prec_Multiplier_0_to_1                                      (1.0 / 256)
#define Min_Multiplier_0_to_1                                             (0.0)
#define Max_Multiplier_0_to_1                                 (255 * 1.0 / 256)
/*      CALDEF
*|      types.Multiplier_0_to_1
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 256);
*|         : range = (0.000000) TO (255 * 1.0 / 256);
*|      }
*/

typedef CARDINAL                                           Multiplier_0_to_1_W;
#define Prec_Multiplier_0_to_1_W                   (Prec_Multiplier_0_to_1/256)
#define Min_Multiplier_0_to_1_W                         (Min_Multiplier_0_to_1)
#define Max_Multiplier_0_to_1_W            (65535.0 * Prec_Multiplier_0_to_1_W)
/*      CALDEF
*|      types.Multiplier_0_to_1_W
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 65536);
*|         : range = (0.000000) TO (65535 * 1.0 / 65536);
*|      }
*/

typedef CARDINAL                                          Multiplier_0_to_32_W;
#define Prec_Multiplier_0_to_32_W                                (1.0 / 2048.0)
#define Min_Multiplier_0_to_32_W                                          (0.0)
#define Max_Multiplier_0_to_32_W          (65535.0 * Prec_Multiplier_0_to_32_W)
/*      CALDEF
*|      types.Multiplier_0_to_32_W
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 2048);
*|         : range = (0.000000) TO (65535 * 1.0 / 2048);
*|      }
*/

typedef LONGCARD                                      Multiplier_0_to_1_W_Base;
#define Prec_Multiplier_0_to_1_W_Base                (Prec_Multiplier_0_to_1_W)
#define Min_Multiplier_0_to_1_W_Base                  (Min_Multiplier_0_to_1_W)
#define Max_Multiplier_0_to_1_W_Base                  (Max_Multiplier_0_to_1_W)

typedef CARDINAL                                        Multiplier_0_to_1_Base;
#define Prec_Multiplier_0_to_1_Base                    (Prec_Multiplier_0_to_1)
#define Min_Multiplier_0_to_1_Base                      (Min_Multiplier_0_to_1)
#define Max_Multiplier_0_to_1_Base        (65535 * Prec_Multiplier_0_to_1_Base)

typedef CARDINAL                                         Multiplier_0_to_128_W;
#define Prec_Multiplier_0_to_128_W                              (128.0 / 65536)
#define Min_Multiplier_0_to_128_W                                         (0.0)
#define Max_Multiplier_0_to_128_W        (65535.0 * Prec_Multiplier_0_to_128_W)

typedef SHORTCARD                                            Multiplier_0_to_2;
#define Prec_Multiplier_0_to_2                                      (2.0 / 256)
#define Min_Multiplier_0_to_2                                             (0.0)
#define Max_Multiplier_0_to_2                                 (255 * 2.0 / 256)
/*      CALDEF
*|      types.Multiplier_0_to_2
*|      {
*|         : kind = fixed;
*|         : precision = (2.0 / 256);
*|         : range = (0.000000) TO (255 * 2.0 / 256);
*|      }
*/

typedef CARDINAL                                           Multiplier_0_to_2_W;
#define Prec_Multiplier_0_to_2_W                                  (1.0 / 32768)
#define Min_Multiplier_0_to_2_W                                           (0.0)
#define Max_Multiplier_0_to_2_W                               (65535.0 / 32768)
/*      CALDEF
*|      types.Multiplier_0_to_2_W
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 32768);
*|         : range = (0.000000) TO (65535 * 1.0 / 32768);
*|      }
*/

typedef SHORTCARD                                            Multiplier_0_to_4;
#define Prec_Multiplier_0_to_4                                      (4.0 / 256)
#define Min_Multiplier_0_to_4                                             (0.0)
#define Max_Multiplier_0_to_4                                 (255 * 4.0 / 256)

typedef CARDINAL                                        Multiplier_0_to_4_Base;
#define Prec_Multiplier_0_to_4_Base                    (Prec_Multiplier_0_to_4)
#define Min_Multiplier_0_to_4_Base                      (Min_Multiplier_0_to_4)
#define Max_Multiplier_0_to_4_Base        (65535 * Prec_Multiplier_0_to_4_Base)

typedef SHORTCARD                                            Multiplier_0_to_8;
#define Prec_Multiplier_0_to_8                                      (8.0 / 256)
#define Min_Multiplier_0_to_8                                             (0.0)
#define Max_Multiplier_0_to_8                                 (255 * 8.0 / 256)
/*      CALDEF
*|      types.Multiplier_0_to_8
*|      {
*|         : kind = fixed;
*|         : precision = (0.031250);
*|         : range = (0.000000) TO (255 * 0.031250);
*|      }
*/

typedef CARDINAL                                           Multiplier_0_to_8_W;
#define Prec_Multiplier_0_to_8_W                                  (8.0 / 65536)
#define Min_Multiplier_0_to_8_W                                           (0.0)
#define Max_Multiplier_0_to_8_W              (65535 * Prec_Multiplier_0_to_8_W)
/*      CALDEF
*|      types.Multiplier_0_to_8_W
*|      {
*|         : kind = fixed;
*|         : precision = (8.0 / 65536.0);
*|         : range = (0.0) TO (65535 *(8.0 / 65536.0));
*|      }
*/

typedef SHORTCARD                                           Multiplier_0_to_16;
#define Prec_Multiplier_0_to_16                                    (16.0 / 256)
#define Min_Multiplier_0_to_16                                            (0.0)
#define Max_Multiplier_0_to_16                               (255 * 16.0 / 256)

typedef CARDINAL                                          Multiplier_0_to_16_W;
#define Prec_Multiplier_0_to_16_W                                  (1.0 / 4096)
#define Min_Multiplier_0_to_16_W                                          (0.0)
#define Max_Multiplier_0_to_16_W                                 (65535 / 4096)

typedef SHORTCARD                                           Multiplier_0_to_32;
#define Prec_Multiplier_0_to_32                                    (32.0 / 256)
#define Min_Multiplier_0_to_32                                            (0.0)
#define Max_Multiplier_0_to_32                               (255 * 32.0 / 256)
/*      CALDEF
*|      types.Multiplier_0_to_32
*|      {
*|         : kind = fixed;
*|         : precision = (32.0 / 256);
*|         : range = (0.000000) TO (255 * 32.0 / 256);
*|      }
*/

typedef SHORTCARD                                           Multiplier_0_to_64;
#define Prec_Multiplier_0_to_64                                    (64.0 / 256)
#define Min_Multiplier_0_to_64                                            (0.0)
#define Max_Multiplier_0_to_64                               (255 * 64.0 / 256)


typedef SHORTCARD                                        Multiplier_0p5_to_1p5;
#define Prec_Multiplier_0p5_to_1p5                            ((1.5-0.5) / 256)
#define Min_Multiplier_0p5_to_1p5                                         (0.5)
#define Max_Multiplier_0p5_to_1p5 \
                 (Min_Multiplier_0p5_to_1p5 + 255 * Prec_Multiplier_0p5_to_1p5)
/*      CALDEF
*|      types.Multiplier_0p5_to_1p5
*|      {
*|         : kind = fixed;
*|         : precision = (0.00390625);
*|         : range = (128 * 0.00390625) TO (383  * 0.00390625);
*|         : biased;
*|      }
*/

typedef SHORTCARD                                            Multiplier_1_to_2;
#define Prec_Multiplier_1_to_2                                      (1.0 / 256)
#define Min_Multiplier_1_to_2                                             (1.0)
#define Max_Multiplier_1_to_2                           (255 * 1.0 / 256 + 1.0)

typedef CARDINAL                                            Multiplier_m2_to_2;
#define Prec_Multiplier_m2_to_2                                   (1.0 / 16384)
#define Min_Multiplier_m2_to_2                                           (-2.0)
#define Max_Multiplier_m2_to_2                        ((65535.0 / 16384) - 2.0)

typedef CARDINAL                                           Multiplier_0_to_4_W;
#define Prec_Multiplier_0_to_4_W                                  (1.0 / 16384)
#define Min_Multiplier_0_to_4_W                                           (0.0)
#define Max_Multiplier_0_to_4_W                               (65535.0 / 16384)
/*      CALDEF
*|      types.Multiplier_0_to_4_W
*|      {
*|         : kind = fixed;
*|         : precision = (1/16384);
*|         : range = (0.000000) TO (65535/16384);
*|      }
*/

typedef SHORTCARD                                         Multiplier_0_to_25p5;
#define Prec_Multiplier_0_to_25p5                                  (1.0 / 10.0)
#define Min_Multiplier_0_to_25p5                                          (0.0)
#define Max_Multiplier_0_to_25p5                           (255 * (1.0 / 10.0))

/*---  Axis Enumerations for Multiplier Types  ---*/

#define Multiplier_0_to_2_W_0to1By0p05_Steps                               (21)
/*      CALDEF      */

/*---  RFactors for Multiplier Types  ---*/

#define RFactor_Multiplier_0_to_32_W_Fixed_Cardinal                    (2048.0)
#define RFactor_Fixed_Cardinal_Multiplier_0_to_32_W                    (2048.0)
#define RFactor_Multiplier_0_to_32_W_Multiplier_0_to_25p5             (10240.0)
#define RFactor_Multiplier_0_to_25p5_Multiplier_0_to_32_W             (10240.0)
#define RFactor_Multiplier_0_to_1_Multiplier_0_to_1_W                 (65536.0)
#define RFactor_Multiplier_0_to_1_W_Multiplier_0_to_1                 (65536.0)
#define RFactor_Multiplier_0_to_0p5_Multiplier_0_to_1_W               (65536.0)
#define RFactor_Multiplier_0_to_1_W_Multiplier_0_to_0p5               (65536.0)
#define RFactor_Multiplier_0_to_1_W_Base_Multiplier_0_to_1_W          (65536.0)
#define RFactor_Multiplier_0_to_1_W_Multiplier_0_to_1_W_Base          (65536.0)
#define RFactor_Multiplier_0_to_1_Multiplier_0_to_1_Base                (256.0)
#define RFactor_Multiplier_0_to_1_Base_Multiplier_0_to_1                (256.0)
#define RFactor_Multiplier_0_to_2_Multiplier_0_to_2_W                 (32768.0)
#define RFactor_Multiplier_0_to_2_W_Multiplier_0_to_2                 (32768.0)
#define RFactor_Multiplier_0_to_4_Multiplier_0_to_4_Base                (256.0)
#define RFactor_Multiplier_0_to_4_Base_Multiplier_0_to_4                (256.0)
#define RFactor_Multiplier_0_to_1_Multiplier_0_to_2                     (256.0)
#define RFactor_Multiplier_0_to_2_Multiplier_0_to_1                     (256.0)
#define RFactor_Multiplier_0_to_2_Multiplier_0_to_2_W                 (32768.0)
#define RFactor_Multiplier_0_to_2_W_Multiplier_0_to_2                 (32768.0)
#define RFactor_Multiplier_0_to_2_Multiplier_0_to_4                     (128.0)
#define RFactor_Multiplier_1_to_2_Multiplier_0_to_4_W                   (16384)
#define RFactor_Multiplier_0_to_8_W_Multiplier_0_to_8                  (8192.0)
#define RFactor_Multiplier_0_to_8_Multiplier_0_to_8_W                  (8192.0)
#define RFactor_Multiplier_0_to_1_W_Multiplier_0_to_2_W               (65536.0)
#define RFactor_Multiplier_0_to_2_W_Multiplier_0_to_1_W               (65536.0)
#define RFactor_Multiplier_0_to_4_W_Multiplier_0_to_1_W               (65536.0)
#define RFactor_Multiplier_0_to_32_W_Multiplier_0_to_2_W              (32768.0)
#define RFactor_Multiplier_0_to_32_Multiplier_0_to_32_W \
                                                (1 / Prec_Multiplier_0_to_32_W)

/*-----------------------------*/
/*---                       ---*/
/*---   Filter Fixed Types  ---*/
/*---                       ---*/
/*-----------------------------*/

typedef SHORTCARD                                           Filter_Coefficient;
#define Prec_Filter_Coefficient                                     (1.0 / 256)
#define Min_Filter_Coefficient                                            (0.0)
#define Max_Filter_Coefficient                                (255 * 1.0 / 256)
/*      CALDEF
*|      types.Filter_Coefficient
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 256);
*|         : range = (0.000000) TO (255 * 1.0 / 256);
*|      }
*/

typedef CARDINAL                                          Filter_Coefficient_W;
#define Prec_Filter_Coefficient_W                                 (1.0 / 65536)
#define Min_Filter_Coefficient_W                                          (0.0)
#define Max_Filter_Coefficient_W                          (65535 * 1.0 / 65536)
/*      CALDEF
*|      types.Filter_Coefficient_W
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 65536);
*|         : range = (0.000000) TO (65535 * 1.0 / 65536);
*|      }
*/

/*---  RFactors for Filter Types  ---*/

#define RFactor_Multiplier_0_to_1_Filter_Coefficient                      (256)

/*-----------------------------*/
/*---                       ---*/
/*---    Volt Fixed Types   ---*/
/*---                       ---*/
/*-----------------------------*/

/*---------------------------------------------------------------------------*/
/*---    Volts was choosen to cover all normal voltages found in the      ---*/
/*---  system.                                                            ---*/
/*---                                                                     ---*/
/*---  Millivolts was choosen to accommodate an oxygen sensor.            ---*/
/*---                                                                     ---*/
/*---  The table shown below is only for informational purposes.  Do not  ---*/
/*---  make any assumptions based on it.                                  ---*/
/*---                                                                     ---*/
/*- Type                        Range (Volts)  Precision   Based on         -*/
/*- ------------                -------------- ----------- ---------------- -*/
/*- Volts_B                     0 ..  25.6     0.1      V  Battery          -*/
/*- Volts_W                     0.0..255.9961  0.0039   V  Table lookups    -*/
/*- Volts_Plus_Fraction_Raw     0.0 .. 25.11   0.000383 V  Raw Ign & Sys.   -*/
/*- Volts_Plus_Fraction         0.0 .. 25.6    0.00039  V  Filtered Ign     -*/
/*- Millivolts_B                0.0 ..1245     4.48     mV O2 sensor        -*/
/*- Millivolts_W                0.0 ..19.9882  0.305176 mV Table lookups    -*/
/*- Millivolts_Plus_Fraction    0.0 .. 1244.99 0.01907  mV O2 sensor filter -*/
/*- Millivolts_Plus_Fraction_Base 0.0 ..82e+6  0.01907  mV O2 sensor filter -*/
/*- Millivolts_0to5000_W        0.0 ..4999.924 0.076294 mV A/D read         -*/
/*- Volt0to5Volts_W             0.0 ..4.999924 76.294e-6V  A/D read         -*/
/*- Volt0to5Volts_B             0.0 ..4.9805   0.019531 V  A/D read         -*/
/*---------------------------------------------------------------------------*/

typedef SHORTCARD                                                      Volts_B;
#define Prec_Volts_B                                                      (0.1)
#define Min_Volts_B                                                       (0.0)
#define Max_Volts_B                                                 (255 * 0.1)

typedef CARDINAL                                                       Volts_W;
#define Prec_Volts_W                                                (1.0 / 256)
#define Min_Volts_W                                                       (0.0)
#define Max_Volts_W                                         (65535 * 1.0 / 256)

typedef CARDINAL                                       Volts_Plus_Fraction_Raw;
#define Prec_Volts_Plus_Fraction_Raw                                (0.1 / 261)
#define Min_Volts_Plus_Fraction_Raw                                       (0.0)
#define Max_Volts_Plus_Fraction_Raw      (64535 * Prec_Volts_Plus_Fraction_Raw)

typedef CARDINAL                                           Volts_Plus_Fraction;
#define Prec_Volts_Plus_Fraction                                    (0.1 / 256)
#define Min_Volts_Plus_Fraction                                           (0.0)
#define Max_Volts_Plus_Fraction                             (65535 * 0.1 / 256)
/*      CALDEF
*|      types.Volts_Plus_Fraction
*|      {
*|         : kind = fixed;
*|         : precision = (0.0003906);
*|         : range = (0.000000) TO (65535 * 0.0003906);
*|      }
*/

typedef SHORTCARD                                                 Millivolts_B;
#define Prec_Millivolts_B                                       (5000.0 / 1024)
#define Min_Millivolts_B                                                  (0.0)
#define Max_Millivolts_B                              (255 * Prec_Millivolts_B)

typedef CARDINAL                                                  Millivolts_W;
#define Prec_Millivolts_W                            (Prec_Millivolts_B / 16.0)
#define Min_Millivolts_W                                                  (0.0)
#define Max_Millivolts_W                            (65535 * Prec_Millivolts_W)

typedef CARDINAL                                             Millivolts_Signed;
#define Prec_Millivolts_Signed                              (Prec_Millivolts_B)
#define Min_Millivolts_Signed                   (-256 * Prec_Millivolts_Signed)
#define Max_Millivolts_Signed                    (255 * Prec_Millivolts_Signed)

typedef CARDINAL                                      Millivolts_Plus_Fraction;
#define Prec_Millivolts_Plus_Fraction                 (Prec_Millivolts_B / 256)
#define Min_Millivolts_Plus_Fraction                                      (0.0)
#define Max_Millivolts_Plus_Fraction    (65535 * Prec_Millivolts_Plus_Fraction)

typedef CARDINAL                                          Millivolts_0to5000_W;
#define Prec_Millivolts_0to5000_W                              (5000.0 / 65536)
#define Min_Millivolts_0to5000_W                                          (0.0)
#define Max_Millivolts_0to5000_W            (65535 * Prec_Millivolts_0to5000_W)

typedef SHORTCARD                                         Millivolts_0to5000_B;
#define Prec_Millivolts_0to5000_B                                (5000.0 / 256)
#define Min_Millivolts_0to5000_B                                          (0.0)
#define Max_Millivolts_0to5000_B              (255 * Prec_Millivolts_0to5000_B)

typedef SHORTCARD                                              Volt0to5Volts_B;
#define Prec_Volt0to5Volts_B                                          (5.0/256)
#define Min_Volt0to5Volts_B                                               (0.0)
#define Max_Volt0to5Volts_B                        (255 * Prec_Volt0to5Volts_B)

typedef CARDINAL                                               Volt0to5Volts_W;
#define Prec_Volt0to5Volts_W                                        (5.0/65536)
#define Min_Volt0to5Volts_W                                               (0.0)
#define Max_Volt0to5Volts_W                      (65535 * Prec_Volt0to5Volts_W)

typedef CARDINAL                                    Volts_0_to_5_Plus_Fraction;
#define Prec_Volts_0_to_5_Plus_Fraction                           (5.0 / 65536)
#define Min_Volts_0_to_5_Plus_Fraction                                    (0.0)
#define Max_Volts_0_to_5_Plus_Fraction                    (65535 * 5.0 / 65536)

typedef CARDINAL                                                Volts_0_to_5_W;
#define Prec_Volts_0_to_5_W                                       (5.0 / 32768)
#define Min_Volts_0_to_5_W                                                (0.0)
#define Max_Volts_0_to_5_W                                                (5.0)

/*---  Axis Enumerations for Volt Types  ---*/

#define Volts_8to16by2_Steps                                                (5)
/*      CALDEF      */
#define Volts_8to16by0p5_Steps                                             (17)
/*      CALDEF
*|      types.Volts_8to16by0p5_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Volts";
*|         : table = (8 TO 16 BY 0.5);
*|      }
*/
#define Volts_8to16by1p0_Steps                                              (9)
/*      CALDEF      */
#define Volts_6to16by1p0_Steps                                             (11)
/*      CALDEF      */
#define Volts_6to18by1p0_Steps                                             (13)
/*      CALDEF      */
#define Volts_6p4to16p0by1p6_Steps                                          (7)
/*      CALDEF      */
#define Volts_0to25p6by1p6_Steps                                           (17)
/*      CALDEF      */
#define Volts_0to5by0p5_Steps                                              (11)
/*      CALDEF
*|      types.Volts_0to5by0p5_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "volts";
*|         : table = (0 TO 5.0 BY 0.5);
*|      }
*/
#define Volts_0to12p8by1p6_Steps                                            (9)
/*      CALDEF      */
#define Mvolts_0to1350by270_Steps                                           (6)
/*      CALDEF      */
#define Mvolts_0to5000by39p0625_Steps                                     (129)
/*      CALDEF      */
#define Mvolts_0to347p5by69p5_Steps                                         (6)
/*      CALDEF
*|      types.Mvolts_0to347p5by69p5_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "milli_volts";
*|         : table = (0, 69.5, 139, 208.5, 278, 347.5);
*|      }
*/

/*---  RFactors for Volt Types  ---*/

#define RFactor_Volt0to5Volts_B_Volt0to5Volts_W                     (65536.0/5)
#define RFactor_Volt0to5Volts_W_Volt0to5Volts_B                     (65536.0/5)
#define RFactor_Volt0to5Volts_W_Volts_B                              (327680.0)
#define RFactor_Volts_Plus_Fraction_Percent_B      (1/Prec_Volts_Plus_Fraction)
#define RFactor_Volts_W_Percent_B                              (1/Prec_Volts_W)
#define RFactor_Percent_B_Volts_W                   (RFactor_Volts_W_Percent_B)
#define RFactor_Volts_0_to_5_Plus_Fraction_Volt0to5Volts_B \
                                            (1/Prec_Volts_0_to_5_Plus_Fraction)
#define RFactor_Millivolts_0to5000_W_Millivolts_0to5000_B \
                                                  (1/Prec_Millivolts_0to5000_W)
#define RFactor_Volts_B_Volts_W                                     (256.0 * 5)
#define RFactor_Volts_W_Volts_B                                     (256.0 * 5)
#define RFactor_Volts_B_Volts_Plus_Fraction                        (256.0 * 10)
#define RFactor_Volts_Plus_Fraction_Volts_B                        (256.0 * 10)
#define RFactor_Volts_Plus_Fraction_Volts_W                        (256.0 * 10)
#define RFactor_Volts_Plus_Fraction_Raw_Volts_Plus_Fraction        (256.0 * 10)
#define RFactor_Volts_0_to_5_Plus_Fraction_Volts_0_to_5_W       (65536.0 / 5.0)
#define RFactor_Volts_0_to_5_W_Volts_0_to_5_Plus_Fraction       (65536.0 / 5.0)
#define RFactor_Millivolts_B_Millivolts_W             (1.0 / Prec_Millivolts_W)
#define RFactor_Millivolts_W_Millivolts_B             (1.0 / Prec_Millivolts_W)
#define RFactor_Millivolts_Signed_Millivolts_B   (1.0 / Prec_Millivolts_Signed)
#define RFactor_Millivolts_B_Millivolts_Signed   (1.0 / Prec_Millivolts_Signed)
#define RFactor_Millivolts_Signed_Millivolts_Plus_Fraction \
                                          (1.0 / Prec_Millivolts_Plus_Fraction)
#define RFactor_Millivolts_Plus_Fraction_Millivolts_Signed \
                                          (1.0 / Prec_Millivolts_Plus_Fraction)
#define RFactor_Millivolts_Plus_Fraction_Millivolts_B \
                                          (1.0 / Prec_Millivolts_Plus_Fraction)
#define RFactor_Millivolts_B_Millivolts_Plus_Fraction \
                                          (1.0 / Prec_Millivolts_Plus_Fraction)
#define RFactor_Millivolts_0to5000_W_Millivolts_B \
                                              (1.0 / Prec_Millivolts_0to5000_W)

/*-----------------------------*/
/*---                       ---*/
/*---  Amperes Fixed Types  ---*/
/*---                       ---*/
/*-----------------------------*/

/*---------------------------------------------------------------------------*/
/*---  MilliAmperes was choosen to accommodate the oxygen sensor heaters. ---*/
/*---                                                                     ---*/
/*--- Type                     Range (Amps)    Precision     Based on     ---*/
/*--- ------------             -------------- ------------  ------------- ---*/
/*--- Amperes_W                0 .. 16.38375   0.25 mAmp                  ---*/
/*---------------------------------------------------------------------------*/

typedef CARDINAL                                                     Amperes_W;
#define Prec_Amperes_W                                             (1.0 / 4000)
#define Min_Amperes_W                                                     (0.0)
#define Max_Amperes_W                                  (65535 * Prec_Amperes_W)

/*-----------------------------*/
/*---                       ---*/
/*---  Watts Fixed Types    ---*/
/*---                       ---*/
/*-----------------------------*/

typedef CARDINAL                                                   KiloWatts_W;
#define Prec_KiloWatts_W                                          (1.0 / 128.0)
#define Min_KiloWatts_W                                                   (0.0)
#define Max_KiloWatts_W                              (65535 * Prec_KiloWatts_W)
/*      CALDEF
*|      types.KiloWatts_W
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 128.0);
*|         : range = (0.000000) TO (65535.0 / 128.0);
*|      }
*/

typedef LONGCARD                                                   KiloWatts_L;
#define Prec_KiloWatts_L                                        (1.0 / 32768.0)
#define Min_KiloWatts_L                                                   (0.0)
#define Max_KiloWatts_L                       (MAX_LONGCARD * Prec_KiloWatts_L)

typedef LONGCARD                                        KiloWattsPerLoopTime_L;
#define Prec_KiloWattsPerLoopTime_L                          (Prec_KiloWatts_L)
#define Min_KiloWattsPerLoopTime_L                                        (0.0)
#define Max_KiloWattsPerLoopTime_L (MAX_LONGCARD * Prec_KiloWattsPerLoopTime_L)
/*      CALDEF
*|      types.KiloWattsPerLoopTime_L
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 32768.0);
*|         : range = (0.000000) TO (4294967295.0 / 32768.0);
*|      }
*/

typedef CARDINAL                                     NewtonMeterPerKiloWatts_W;
#define Prec_NewtonMeterPerKiloWatts_W                           (1.0 / 1024.0)
#define Min_NewtonMeterPerKiloWatts_W                                     (0.0)
#define Max_NewtonMeterPerKiloWatts_W  (65535 * Prec_NewtonMeterPerKiloWatts_W)
/*      CALDEF
*|      types.NewtonMeterPerKiloWatts_W
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 1024.0);
*|         : range = (0.000000) TO (65535.0 / 1024.0);
*|      }
*/

/*---  RFactors for Watts Types  ---*/

#define RFactor_KiloWatts_L_KiloWatts_W                               (32768.0)
#define RFactor_KiloWatts_W_KiloWatts_L                               (32768.0)

typedef CARDINAL                                                    Velocity_S;
#define Prec_Velocity_S                                         (512.0 / 65536)
#define Min_Velocity_S                                                 (-256.0)
#define Max_Velocity_S                             (65535 * Prec_Velocity_S + \
                                                                Min_Velocity_S)

typedef CARDINAL                                          Velocity_W_NonBiased;
#define Prec_Velocity_W_NonBiased                               (512.0 / 65536)
#define Min_Velocity_W_NonBiased                                          (0.0)
#define Max_Velocity_W_NonBiased         (65535 * Prec_Velocity_W_NonBiased + \
                                                      Min_Velocity_W_NonBiased)

#define RFactor_Velocity_S_Velocity_W_NonBiased           (1 / Prec_Velocity_S)
#define RFactor_Velocity_W_NonBiased_Velocity_S           (1 / Prec_Velocity_S)

/*-----------------------------*/
/*---                       ---*/
/*---   Ohms Fixed Types    ---*/
/*---                       ---*/
/*-----------------------------*/

/*---------------------------------------------------------------------------*/
/*---  Ohms was choosen to accommodate the oxygen sensor heaters.         ---*/
/*---                                                                     ---*/
/*--- Type                     Range (Ohms)    Precision     Based on     ---*/
/*--- ------------             -------------- ------------  ------------- ---*/
/*--- Ohms_W                   0 .. 65.535     1.0 mOhm                   ---*/
/*---------------------------------------------------------------------------*/

typedef CARDINAL                                                        Ohms_W;
#define Prec_Ohms_W                                                (1.0 / 1000)
#define Min_Ohms_W                                                        (0.0)
#define Max_Ohms_W                                        (65535 * Prec_Ohms_W)

/*-----------------------------------*/
/*---                             ---*/
/*---   Wheel Speed Sensor Types  ---*/
/*---                             ---*/
/*-----------------------------------*/

typedef CARDINAL                                          KPHTimesUsecPerTooth;
#define Prec_KPHTimesUsecPerTooth                                        (10.0)
#define Min_KPHTimesUsecPerTooth                                          (0.0)
#define Max_KPHTimesUsecPerTooth                                 (65535.0 * 10)

/*-------------------------------*/
/*---                         ---*/
/*---   Wheel Rotation Types  ---*/
/*---                         ---*/
/*-------------------------------*/

typedef Fixed_Cardinal                                  WheelRotationsCntrType;
#define Prec_WheelRotationsCntrType                                    (1.0/29)
#define Min_WheelRotationsCntrType                                        (0.0)
#define Max_WheelRotationsCntrType        (29695 * Prec_WheelRotationsCntrType)

/*-------------------------------*/
/*---                         ---*/
/*---   Wheel Speed CAN Types ---*/
/*---  14bits                 ---*/
/*-------------------------------*/

typedef Fixed_Cardinal                                   WheelSpeedFromCanType;
#define Prec_WheelSpeedFromCanType                                        (1.0)
#define Min_WheelSpeedFromCanType                                         (0.0)
#define Max_WheelSpeedFromCanType          (65535 * Prec_WheelSpeedFromCanType)

/*--------------------------------*/
/*---                          ---*/
/*---   Linear Distance Types  ---*/
/*---                          ---*/
/*--------------------------------*/

typedef Fixed_Shortcard                                       DistanceInCmType;
#define Prec_DistanceInCmType                                             (1.0)
#define Min_DistanceInCmType                                              (0.0)
#define Max_DistanceInCmType                      (255 * Prec_DistanceInCmType)

typedef Fixed_Cardinal                                     DistanceInCm_W_Type;
#define Prec_DistanceInCm_W_Type                                          (1.0)
#define Min_DistanceInCm_W_Type                                           (0.0)
#define Max_DistanceInCm_W_Type                 (65535 * Prec_DistanceInCmType)

typedef Fixed_Cardinal                                     DistanceInMeterType;
#define Prec_DistanceInMeterType                                       (1.0/64)
#define Min_DistanceInMeterType                                           (0.0)
#define Max_DistanceInMeterType (Max_Fixed_Cardinal * Prec_DistanceInMeterType)

typedef Fixed_Longcard                                    DistanceInMeterLType;
#define Prec_DistanceInMeterLType                                      (1.0/64)
#define Min_DistanceInMeterLType                                          (0.0)
#define Max_DistanceInMeterLType \
                               (Max_Fixed_Longcard * Prec_DistanceInMeterLType)

typedef LONGCARD                                                     Kilometer;
#define Prec_Kilometer                                                    (1.0)
#define Min_Kilometer                                                     (0.0)
#define Max_Kilometer                           (MAX_LONGCARD * Prec_Kilometer)

typedef LONGCARD                                       Kilometer3BytesPlusFrac;
#define Prec_Kilometer3BytesPlusFrac                                  (1.0/256)
#define Min_Kilometer3BytesPlusFrac                                       (0.0)
#define Max_Kilometer3BytesPlusFrac \
                                  (MAX_LONGCARD * Prec_Kilometer3BytesPlusFrac)

typedef LONGCARD                                                         Meter;
#define Prec_Meter                                                        (1.0)
#define Min_Meter                                                         (0.0)
#define Max_Meter                                     (4294967295 * Prec_Meter)

/*---  RFactors for Linear Distance Types  ---*/

#define RFactor_DistanceInCmType_DistanceInMeterType \
                                               (1.0 / Prec_DistanceInMeterType)
#define RFactor_DistanceInCm_W_Type_DistanceInMeterType \
                                               (1.0 / Prec_DistanceInMeterType)
#define RFactor_Fixed_Longcard_Kilometer                 (1.0 / Prec_Kilometer)
#define RFactor_DistanceInMeterLType_Kilometer \
                                              (1.0 / Prec_DistanceInMeterLType)
#define RFactor_Kilometer_DistanceInMeterLType \
                                       (RFactor_DistanceInMeterLType_Kilometer)
#define RFactor_Meter_Kilometer                                           (1.0)
#define RFactor_Kilometer_Meter                                           (1.0)
#define RFactor_DistanceInMeterType_Meter      (1.0 / Prec_DistanceInMeterType)
#define RFactor_Meter_DistanceInMeterType      (1.0 / Prec_DistanceInMeterType)
#define RFactor_DistanceInMeterLType_Meter      (1 / Prec_DistanceInMeterLType)
#define RFactor_Meter_DistanceInMeterLType (RFactor_DistanceInMeterLType_Meter)

/*---------------------------------------------------------*/
/*---                                                   ---*/
/*---   Wheel Rotation Linear to Distance Factor Types  ---*/
/*---                                                   ---*/
/*---------------------------------------------------------*/

typedef Fixed_Shortcard                                DistInCmPerWheelRotType;
#define Prec_DistInCmPerWheelRotType                                      (1.0)
#define Min_DistInCmPerWheelRotType                                         (0)
#define Max_DistInCmPerWheelRotType \
                           (Max_Fixed_Shortcard * Prec_DistInCmPerWheelRotType)

/*-----------------------------------*/
/*---                             ---*/
/*---   Linear Speed Fixed Types  ---*/
/*---                             ---*/
/*-----------------------------------*/

typedef CARDINAL                                               MetersPerSecond;
#define Prec_MetersPerSecond                                        (1.0 / 256)
#define Min_MetersPerSecond                                            (-128.0)
#define Max_MetersPerSecond                               (65535.0 / 256 - 128)

typedef LONGCARD                                           MetersPerSecondBase;
#define Prec_MetersPerSecondBase                                   (1.0 / 4096)
#define Min_MetersPerSecondBase                                     (-524288.0)
#define Max_MetersPerSecondBase                (4294967295.0 / 4096 - 524288.0)

typedef CARDINAL                                        MetersPerSecondSquared;
#define Prec_MetersPerSecondSquared                                (1.0 / 4096)
#define Min_MetersPerSecondSquared                                       (-8.0)
#define Max_MetersPerSecondSquared                         (65535.0 / 4096 - 8)

typedef SHORTCARD                                     MetersPerSecondSquared_B;
#define Prec_MetersPerSecondSquared_B                              (1.0 / 16.0)
#define Min_MetersPerSecondSquared_B                                     (-8.0)
#define Max_MetersPerSecondSquared_B \
                                  (255.0 * Prec_MetersPerSecondSquared_B - 8.0)

typedef SHORTCARD                             MetersPerSecondSquaredUnsigned_B;
#define Prec_MetersPerSecondSquaredUnsigned_B                      (1.0 / 32.0)
#define Min_MetersPerSecondSquaredUnsigned_B                              (0.0)
#define Max_MetersPerSecondSquaredUnsigned_B                      (255.0 /32.0)

typedef LONGCARD                                    MetersPerSecondSquaredBase;
#define Prec_MetersPerSecondSquaredBase                            (1.0 / 4096)
#define Min_MetersPerSecondSquaredBase                              (-524288.0)
#define Max_MetersPerSecondSquaredBase         (4294967295.0 / 4096 - 524288.0)

typedef CARDINAL                                MetersPerSecondSquaredUnsigned;
#define Prec_MetersPerSecondSquaredUnsigned                        (1.0 / 4096)
#define Min_MetersPerSecondSquaredUnsigned                                (0.0)
#define Max_MetersPerSecondSquaredUnsigned                     (65535.0 / 4096)

typedef CARDINAL                                          MetersPerSecondCubed;
#define Prec_MetersPerSecondCubed                                  (1.0 / 4096)
#define Min_MetersPerSecondCubed                                         (-8.0)
#define Max_MetersPerSecondCubed                           (65535.0 / 4096 - 8)

typedef LONGCARD                                      MetersPerSecondCubedBase;
#define Prec_MetersPerSecondCubedBase                              (1.0 / 4096)
#define Min_MetersPerSecondCubedBase                                (-524288.0)
#define Max_MetersPerSecondCubedBase           (4294967295.0 / 4096 - 524288.0)

typedef CARDINAL                                                             G;
#define Prec_G                                                       (1.0 / 16)
#define Min_G                                                             (0.0)
#define Max_G                                                    (65535.0 / 16)

typedef CARDINAL                                                       GSigned;
#define Prec_GSigned                                                   (Prec_G)
#define Min_GSigned                                                   (-2048.0)
#define Max_GSigned                                     (65535.0 / 16 - 2048.0)

typedef CARDINAL                                                        GHiRes;
#define Prec_GHiRes                                                 (1.0 / 256)
#define Min_GHiRes                                                        (0.0)
#define Max_GHiRes                                              (65535.0 / 256)

typedef SHORTCARD                                                          KPH;
#define Prec_KPH                                                          (1.0)
#define Min_KPH                                                           (0.0)
#define Max_KPH                                                     (255 * 1.0)
/*      CALDEF
*|      types.KPH
*|      {
*|         : kind = fixed;
*|         : precision = (1.000000);
*|         : range = (0.000000) TO (255.000000);
*|      }
*/

typedef CARDINAL                                                         KPH_W;
#define Prec_KPH_W                                                  (8.0 / 256)
#define Min_KPH_W                                                         (0.0)
#define Max_KPH_W                                           (65535 * 8.0 / 256)

typedef CARDINAL                                                KPH_B_Filtered;
#define Prec_KPH_B_Filtered                                         (1.0 / 256)
#define Min_KPH_B_Filtered                                                (0.0)
#define Max_KPH_B_Filtered                                  (65535 * 1.0 / 256)

typedef LONGCARD                                                KPH_W_Filtered;
#define Prec_KPH_W_Filtered                                       (1.0 / 65536)
#define Min_KPH_W_Filtered                                                (0.0)
#define Max_KPH_W_Filtered                 (4294967295.0 * Prec_KPH_W_Filtered)

typedef CARDINAL                                                    KPH_Signed;
#define Prec_KPH_Signed                                              (1.0 / 32)
#define Min_KPH_Signed                                      (-32768 * 1.0 / 32)
#define Max_KPH_Signed                                       (32767 * 1.0 / 32)

typedef CARDINAL                                                  KPH_Unsigned;
#define Prec_KPH_Unsigned                                            (1.0 / 32)
#define Min_KPH_Unsigned                                                  (0.0)
#define Max_KPH_Unsigned                                     (32767 * 1.0 / 32)

typedef CARDINAL                                                      KPH_Base;
#define Prec_KPH_Base                                                     (1.0)
#define Min_KPH_Base                                                      (0.0)
#define Max_KPH_Base                                              (32767 * 1.0)

typedef Filter_Coefficient                          Vehicle_Speed_Filter_Coeff;
#define Prec_Vehicle_Speed_Filter_Coeff                             (1.0 / 256)
#define Min_Vehicle_Speed_Filter_Coeff                                    (0.0)
#define Max_Vehicle_Speed_Filter_Coeff                        (255 * 1.0 / 256)

/*---  Axis Enumerations for Linear Speed Types  ---*/

#define KPH_0to128by8_Steps                                                (17)
/*      CALDEF      */
#define KPH_0to160by10_Steps                                               (17)
/*      CALDEF      */
#define KPH_16to224by16_Steps                                              (14)
/*      CALDEF      */
#define KPH_0to224by16_Steps                                               (15)
/*      CALDEF      */
#define KPH_0to256by16_Steps                                               (17)
/*      CALDEF
*|      types.KPH_0to256by16_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "km/h";
*|         : table = (0 TO 256 BY 16);
*|      }
*/
#define KPH_0to256by64_Steps                                                (5)
/*      CALDEF      */
#define KPH_Error_m32to0by16_Steps                                          (3)
/*      CALDEF      */
#define KPH_Error_m32to8by2_Steps                                          (21)
/*      CALDEF      */
#define KPH_Error_m32to8by4_Steps                                          (11)
/*      CALDEF      */

/*---  RFactors for Linear Speed Types  ---*/

#define RFactor_KPH_W_Filtered_KPH_B_Filtered         (1 / Prec_KPH_W_Filtered)
#define RFactor_MetersPerSecond_MetersPerSecondBase                    (4096.0)
#define RFactor_MetersPerSecondBase_MetersPerSecond                    (4096.0)
#define RFactor_MetersPerSecondSquared_MetersPerSecondSquaredUnsigned  (4096.0)
#define RFactor_MetersPerSecondSquaredUnsigned_MetersPerSecondSquared  (4096.0)
#define RFactor_MetersPerSecondSquared_MetersPerSecondSquaredBase      (4096.0)
#define RFactor_MetersPerSecondSquaredBase_MetersPerSecondSquared      (4096.0)
#define RFactor_MetersPerSecondSquaredBase_MetersPerSecondSquaredUnsigned \
                                                                       (4096.0)
#define RFactor_MetersPerSecondSquaredUnsigned_MetersPerSecondSquaredBase \
                                                                       (4096.0)
#define RFactor_MetersPerSecondCubed_MetersPerSecondCubedBase          (4096.0)
#define RFactor_MetersPerSecondCubedBase_MetersPerSecondCubed          (4096.0)
#define RFactor_MetersPerSecondSquared_MetersPerSecondSquared_B        (4096.0)
#define RFactor_MetersPerSecondSquared_B_MetersPerSecondSquared        (4096.0)
#define RFactor_G_GSigned                                          (1 / Prec_G)
#define RFactor_GSigned_G                                          (1 / Prec_G)
#define RFactor_KPH_KPH_Base                                              (1.0)
#define RFactor_KPH_Base_KPH                                              (1.0)
#define RFactor_KPH_B_Filtered_KPH_Unsigned                             (256.0)
#define RFactor_KPH_Unsigned_KPH_B_Filtered                             (256.0)
#define RFactor_KPH_KPH_Unsigned                                         (32.0)
#define RFactor_KPH_Unsigned_KPH                                         (32.0)
#define RFactor_KPH_B_Filtered_KPH_Signed             (1 / Prec_KPH_B_Filtered)
#define RFactor_KPH_KPH_Signed                                           (32.0)
#define RFactor_KPH_Per_Sec_Type_KPH_Per_Sec_Unsigned_Type              (256.0)
#define RFactor_KPH_Per_Sec_Type_MetersPerSecondSquared                (4096.0)
#define RFactor_MetersPerSecondSquared_KPH_Per_Sec_Type                (4096.0)
#define RFactor_KPH_KPH_W                                                (32.0)
#define RFactor_KPH_W_KPH                                                (32.0)
#define RFactor_KPH_B_Filtered_KPH                                      (256.0)

/*-------------------------------------------*/
/*---                                     ---*/
/*---   Vehicle Acceleration Fixed Types  ---*/
/*---                                     ---*/
/*-------------------------------------------*/

typedef CARDINAL                                              KPH_Per_Sec_Type;
#define Prec_KPH_Per_Sec_Type                                       (1.0 / 256)
#define Min_KPH_Per_Sec_Type                                   (-32768.0 / 256)
#define Max_KPH_Per_Sec_Type                                    (32767.0 / 256)

typedef CARDINAL                                     KPH_Per_Sec_Unsigned_Type;
#define Prec_KPH_Per_Sec_Unsigned_Type                              (1.0 / 256)
#define Min_KPH_Per_Sec_Unsigned_Type                                     (0.0)
#define Max_KPH_Per_Sec_Unsigned_Type                           (32767.0 / 256)

/*---------------------------------------*/
/*---                                 ---*/
/*---   Rotational Speed Fixed Types  ---*/
/*---                                 ---*/
/*---------------------------------------*/

/*---------------------------------------------------------------------------*/
/*--- Rotational speed types are sparated INTEGER to several different    ---*/
/*--- ranges and scalings due to the limitiations of an 8-bit processor   ---*/
/*---                                                                     ---*/
/*--- Type            Range (RPM)      Precision      Based on            ---*/
/*--- --------------  --------------   ------------   ------------------  ---*/
/*--- RPM_W           0 .. 12799.8     0.195313 RPM   Table lookups       ---*/
/*--- RPM_B           0 .. 12750.0     50.00 RPM                          ---*/
/*--- RPM_Med_Res_W   0 .. 3199.95     0.048828 RPM                       ---*/
/*--- RPM_Med_Res_B   0 .. 3187.5      12.5  RPM                          ---*/
/*--- RPM_Hi_Res_W    0 .. 65535.0     1 RPM                              ---*/
/*---------------------------------------------------------------------------*/

typedef CARDINAL                                                         RPM_W;
#define Prec_RPM_W                                                 (50.0 / 256)
#define Min_RPM_W                                                         (0.0)
#define Max_RPM_W                                          (65535 * 50.0 / 256)
/*      CALDEF
*|      types.RPM_W
*|      {
*|         : kind = fixed;
*|         : precision = (50.0 / 256);
*|         : range = (0.0) TO (65535 * 50.0 / 256);
*|      }
*/

typedef SHORTCARD                                                        RPM_B;
#define Prec_RPM_B                                                       (50.0)
#define Min_RPM_B                                                         (0.0)
#define Max_RPM_B                                            (255 * Prec_RPM_B)
/*      CALDEF
*|      types.RPM_B
*|      {
*|         : kind = fixed;
*|         : precision = (50.0);
*|         : range = (0.000000) TO (255 * 50.0);
*|      }
*/

typedef CARDINAL                                                 RPM_Med_Res_W;
#define Prec_RPM_Med_Res_W                                         (12.5 / 256)
#define Min_RPM_Med_Res_W                                                 (0.0)
#define Max_RPM_Med_Res_W                                  (65535 * 12.5 / 256)

typedef CARDINAL                                RPM_Med_Res_Per_2ndLoop_Time_W;
#define Prec_RPM_Med_Res_Per_2ndLoop_Time_W                (Prec_RPM_Med_Res_W)
#define Min_RPM_Med_Res_Per_2ndLoop_Time_W                                (0.0)
#define Max_RPM_Med_Res_Per_2ndLoop_Time_W         (65535 * Prec_RPM_Med_Res_W)

typedef CARDINAL                                                       RPM_W_S;
#define Prec_RPM_W_S                                               (Prec_RPM_W)
#define Min_RPM_W_S                                   (-32768.0 * Prec_RPM_W_S)
#define Max_RPM_W_S                        (32767 * Prec_RPM_W_S - Min_RPM_W_S)
/*      CALDEF
*|      types.RPM_W_S
*|      {
*|         : kind = fixed;
*|         : precision = (50.0 / 256);
*|         : range = -6400 TO <6400;
*|         : biased;
*|      }
*/

typedef SHORTCARD                                                RPM_Med_Res_B;
#define Prec_RPM_Med_Res_B                                               (12.5)
#define Min_RPM_Med_Res_B                                                 (0.0)
#define Max_RPM_Med_Res_B                                          (255 * 12.5)
/*      CALDEF
*|      types.RPM_Med_Res_B
*|      {
*|         : kind = fixed;
*|         : precision = (12.500000);
*|         : range = (0.000000) TO (3187.500000);
*|      }
*/

typedef CARDINAL                                                  RPM_Hi_Res_W;
#define Prec_RPM_Hi_Res_W                                                 (1.0)
#define Min_RPM_Hi_Res_W                                                  (0.0)
#define Max_RPM_Hi_Res_W                                          (65535 * 1.0)

typedef CARDINAL                                            RPM_Hi_Res_W_Error;
#define Prec_RPM_Hi_Res_W_Error                             (Prec_RPM_Hi_Res_W)
#define Min_RPM_Hi_Res_W_Error                                       (-32768.0)
#define Max_RPM_Hi_Res_W_Error \
                     (Prec_RPM_Hi_Res_W_Error * 65535 + Min_RPM_Hi_Res_W_Error)

typedef CARDINAL                                 RPM_Gradient_1rpmper100msec_W;
#define Prec_RPM_Gradient_1rpmper100msec_W                                (1.0)
#define Min_RPM_Gradient_1rpmper100msec_W                            (-32768.0)
#define Max_RPM_Gradient_1rpmper100msec_W                             (32767.0)

typedef CARDINAL                                     RPM_Gradient_1rpmpersec_W;
#define Prec_RPM_Gradient_1rpmpersec_W                                    (1.0)
#define Min_RPM_Gradient_1rpmpersec_W                                (-32768.0)
#define Max_RPM_Gradient_1rpmpersec_W                                 (32767.0)

typedef SHORTCARD                                     RPM_Gradient_100rpmsec_B;
#define Prec_RPM_Gradient_100rpmsec_B                                   (100.0)
#define Min_RPM_Gradient_100rpmsec_B                                 (-12800.0)
#define Max_RPM_Gradient_100rpmsec_B                                  (12700.0)

/*---  Axis Enumerations for Rotational Speed Speed Types  ---*/

#define RPM_400to1200by200_Steps  (5)
/*      CALDEF
*|      types.RPM_400to1200by200_Steps
*|      {
*|       :kind = define_annotation;
*|       :units = "RPM";
*|       :table = (400 TO 1200 BY 200);
*|      }
*/
#define RPM_0to500by50_Steps                                               (11)
/*      CALDEF      */
#define RPM_0to600by50_Steps                                               (13)
/*      CALDEF      */
#define RPM_0to1600by100_Steps                                             (17)
/*      CALDEF      */
#define RPM_0to3200by200_Steps                                             (17)
/*      CALDEF      */
#define RPM_0to6400by400_Steps                                             (17)
/*      CALDEF
*|      types.RPM_0to6400by400_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "RPM";
*|         : table = (0 TO 6400 BY 400);
*|      }
*/
#define RPM_400to6400by400_Steps                                           (16)
/*      CALDEF      */
#define RPM_800to6400by400_Steps                                           (15)
/*      CALDEF
*|      types.RPM_800to6400by400_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "RPM";
*|         : table = (800 TO 6400 BY 400);
*|      }
*/
#define RPM_0to3200by400_Steps                                              (9)
/*      CALDEF      */
#define RPM_0to4000by400_Steps                                             (11)
/*      CALDEF      */
#define RPM_400to2400by400_Steps                                            (6)
/*      CALDEF      */
#define RPM_0to7200by800_Steps                                             (10)
/*      CALDEF      */
#define RPM_0to6400by800_Steps                                              (9)
/*      CALDEF
*|      types.RPM_0to6400by800_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "RPM";
*|         : table = (0 TO 6400 BY 800);
*|      }
*/
#define RPM_0to4800by800_Steps                                              (7)
/*      CALDEF      */
#define RPM_800to3200by800_Steps                                            (4)
/*      CALDEF      */
#define RPM_800to4000by400_Steps                                            (9)
/*      CALDEF      */
#define RPM_800to4000by800_Steps                                            (5)
/*      CALDEF      */
#define RPM_800to4800by800_Steps                                            (4)
/*      CALDEF      */
#define RPM_800to5600by800_Steps                                            (7)
/*      CALDEF      */
#define RPM_800to6400by800_Steps                                            (8)
/*      CALDEF
*|      types.RPM_800to6400by800_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "RPM";
*|         : table = (800 TO 6400 BY 800);
*|      }
*/
#define RPM_0to7200by1200_Steps                                             (7)
/*      CALDEF      */
#define RPM_1200to4800by1200_Steps                                          (4)
/*      CALDEF
*|      types.RPM_1200to4800by1200_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "RPM";
*|         : table = (1200 TO 4800 BY 1200);
*|      }
*/
#define RPM_1200to6000by1200_Steps                                          (5)
/*      CALDEF      */
#define RPM_2000to3000by100_Steps                                          (11)
/*      CALDEF      */
#define RPM_0to6400by1600_Steps                                             (5)
/*      CALDEF
*|      types.RPM_0to6400by1600_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "RPM";
*|         : table = (0 TO 6400 BY 1600);
*|      }
*/

#define RPM_0to400by100_400to6400by400_Steps                               (20)
/*      CALDEF      */
#define RefCounts_0to16by1_Steps                                           (17)
/*      CALDEF      */

/*---  RFactors for Rotational Speed Speed Types  ---*/

#define RFactor_RPM_Med_Res_W_RPM_Med_Res_Per_2ndLoop_Time_W       (512.0 / 25)
#define RFactor_RPM_Med_Res_Per_2ndLoop_Time_W_RPM_Med_Res_W       (512.0 / 25)
#define RFactor_RPM_Med_Res_B_RPM_Hi_Res_W      (2)
#define RFactor_RPM_Hi_Res_W_RPM_Hi_Res_W_Error                           (1.0)
#define RFactor_RPM_Hi_Res_W_Error_RPM_Hi_Res_W                           (1.0)
#define RFactor_HiResRPM_Period_Sec_RPM_Gradient_1rpmper100msec_W         (1.0)
#define RFactor_RPM_Gradient_1rpm100msec_W_RPM_Gradient_1rpmpersec_W      (1.0)
#define RFactor_RPM_Gradient_1rpmpersec_W_RPM_Gradient_100rpmsec_B        (1.0)
#define RFactor_RPM_B_RPM_Hi_Res_W                                        (1.0)
#define RFactor_RPM_W_RPM_B                                (256.0 / Prec_RPM_B)
#define RFactor_RPM_B_RPM_W                                (256.0 / Prec_RPM_B)
#define RFactor_RPM_Med_Res_W_RPM_W                                (512.0 / 25)
#define RFactor_RPM_W_RPM_Med_Res_W                                (512.0 / 25)
#define RFactor_RPM_W_RPM_W_S                                    (1/Prec_RPM_W)
#define RFactor_RPM_W_S_RPM_W                                    (1/Prec_RPM_W)

#define RFactor_RPM_Med_Res_B_RPM_W_S                          (1/Prec_RPM_W_S)
#define RFactor_RPM_Med_Res_W_RPM_Med_Res_B                        (512.0 / 25)
#define RFactor_RPM_Med_Res_B_RPM_Med_Res_W                        (512.0 / 25)
#define RFactor_RPM_W_RPM_Hi_Res_W                                      (256.0)
#define RFactor_RPM_Hi_Res_W_RPM_W                                      (256.0)
#define RFactor_RPM_To_Speed_Ratio_Base_RPM_To_Speed_Ratio \
                                                 (Prec_KPH / Prec_RPM_Hi_Res_W)
#define RFactor_RPM_To_Speed_Ratio_RPM_To_Speed_Ratio_Base \
                                                 (Prec_KPH / Prec_RPM_Hi_Res_W)

/*----------------------------*/
/*---                      ---*/
/*---   Time Fixed Types   ---*/
/*---                      ---*/
/*----------------------------*/
//#if OS_SCHEDULER_10ms == CeSYST_AVAILABLE
//#define RegularRtiPrescaler                                          (0.010000)
//#else
//#define RegularRtiPrescaler                                          (0.015625)
//#endif

/*---------------------------------------------------------------------------*/
/*--- The times that require a lot of precision are based on the timing   ---*/
/*--- of the free running counters. As the different counters can have    ---*/
/*--- various timing, a MicroSec type will be defined for each one of the ---*/
/*--- counters.                                                           ---*/
/*--- The types which are function specific depending on the hardware     ---*/
/*--- used to generate the timing are defined in the hardware confi-      ---*/
/*--- guration file sk_xxxx.h based on the hardware timer clock sources   ---*/
/*--- and prescalers.                                                     ---*/
/*--- The assignement of the timing input/output is done in the I/O con-  ---*/
/*--- figuration file of the application which is included by h_interf.h  ---*/
/*---                                                                     ---*/
/*---------------------------------------------------------------------------*/

/*--- WARNING: Geneneric type only ! ---*/
typedef CARDINAL                                                 MicroSec_Type;
#define Prec_MicroSec_Type                 (MicroSec_Generic_Type_In_Use_Error)
#define Min_MicroSec_Type                  (MicroSec_Generic_Type_In_Use_Error)
#define Max_MicroSec_Type                  (MicroSec_Generic_Type_In_Use_Error)

typedef CARDINAL                                                  MicroSeconds;
#define Prec_MicroSeconds                                   (1000000.0 / 65536)
#define Min_MicroSeconds                                                  (0.0)
#define Max_MicroSeconds                            (65535 * 1000000.0 / 65536)

typedef CARDINAL                                                      MicroSec;
#define Prec_MicroSec                                                     (1.0)
#define Min_MicroSec                                                      (0.0)
#define Max_MicroSec                                                    (65535)

typedef LONGCARD                                                    Microsec_L;
#define Prec_Microsec_L                                             (1.0/32768)
#define Min_Microsec_L                                                    (0.0)
#define Max_Microsec_L                         (MAX_LONGCARD * Prec_Microsec_L)

typedef SHORTCARD                                  MicrosecToMillisecRatioType;
#define Prec_MicrosecToMillisecRatioType                           (1.0 / 1000)
#define Min_MicrosecToMillisecRatioType                                   (0.0)
#define Max_MicrosecToMillisecRatioType                      (255 * 1.0 / 1000)

typedef CARDINAL                                                    Millisec_W;
#define Prec_Millisec_W                                           (1.0 / 32768)
#define Min_Millisec_W                                                    (0.0)
#define Max_Millisec_W                                    (65535 * 1.0 / 32768)

typedef LONGCARD                                                    Millisec_L;
#define Prec_Millisec_L                                           (1.0 / 32768)
#define Min_Millisec_L                                                    (0.0)
#define Max_Millisec_L                                   (4294967295.0 / 32768)

typedef CARDINAL                                                       Seconds;
#define Prec_Seconds                                      (RegularRtiPrescaler)
#define Min_Seconds                                                       (0.0)
#define Max_Seconds                               (65535 * RegularRtiPrescaler)

typedef SHORTCARD                                                    Seconds_B;
#define Prec_Seconds_B                                    (RegularRtiPrescaler)
#define Min_Seconds_B                                                     (0.0)
#define Max_Seconds_B                               (255 * RegularRtiPrescaler)

typedef CARDINAL                                                   Seconds_Low;
#define Prec_Seconds_Low                                                  (1.0)
#define Min_Seconds_Low                                                   (0.0)
#define Max_Seconds_Low                                           (65535 * 1.0)
/*      CALDEF
*|      types.Seconds_Low
*|      {
*|         : kind = fixed;
*|         : precision = (1.000000);
*|         : range = (0.000000) TO (65535.000000);
*|      }
*/

typedef SHORTCARD                                                Seconds_Low_B;
#define Prec_Seconds_Low_B                                                (1.0)
#define Min_Seconds_Low_B                                                 (0.0)
#define Max_Seconds_Low_B                                           (255 * 1.0)

typedef SHORTCARD                                               Seconds_Medium;
#define Prec_Seconds_Medium                                         (1.0 / 128)
#define Min_Seconds_Medium                                                (0.0)
#define Max_Seconds_Medium                                    (255 * 1.0 / 128)

typedef CARDINAL                                                Seconds_Fine_W;
#define Prec_Seconds_Fine_W                                       (1.0 / 65536)
#define Min_Seconds_Fine_W                                                (0.0)
#define Max_Seconds_Fine_W                                (65535 * 1.0 / 65536)

typedef LONGCARD                                                Seconds_Fine_L;
#define Prec_Seconds_Fine_L                                       (1.0 / 65536)
#define Min_Seconds_Fine_L                                                (0.0)
#define Max_Seconds_Fine_L                           (4294967295 * 1.0 / 65536)

typedef CARDINAL                                                Milliseconds_W;
#define Prec_Milliseconds_W                                               (1.0)
#define Min_Milliseconds_W                                                (0.0)
#define Max_Milliseconds_W                        (65535 * Prec_Milliseconds_W)

typedef CARDINAL                         MicroSecondsToSeconds_Fine_WRatioType;
#define Prec_MicroSecondsToSeconds_Fine_WRatioType              (1.0 / 1000000)
#define Min_MicroSecondsToSeconds_Fine_WRatioType                         (0.0)
#define Max_MicroSecondsToSeconds_Fine_WRatioType       (65535 * 1.0 / 1000000)

typedef CARDINAL                                       MicroSecondsPrec20000_W;
#define Prec_MicroSecondsPrec20000_W                                  (20000.0)
#define Min_MicroSecondsPrec20000_W                                       (0.0)
#define Max_MicroSecondsPrec20000_W      (65535 * Prec_MicroSecondsPrec20000_W)

typedef CARDINAL                                                InverseSeconds;
#define Prec_InverseSeconds                                       (1.0 / 16384)
#define Min_InverseSeconds                                                (0.0)
#define Max_InverseSeconds                                    (65535.0 / 16384)

typedef CARDINAL                                         InverseSecondsSquared;
#define Prec_InverseSecondsSquared                                (1.0 / 16384)
#define Min_InverseSecondsSquared                                         (0.0)
#define Max_InverseSecondsSquared                             (65535.0 / 16384)

typedef SHORTCARD                                                MinutePrec2_B;
#define Prec_MinutePrec2_B                                                (2.0)
#define Min_MinutePrec2_B                                                 (0.0)
#define Max_MinutePrec2_B                            (255 * Prec_MinutePrec2_B)

/*---  Axis Enumerations for Time Types  ---*/

#define Min_0to12by1p5_Steps                                                (9)
/*      CALDEF      */

/*---  RFactors for Time Types  ---*/

#define RFactor_Seconds_Fine_W_Seconds_Fine_L                         (65536.0)
#define RFactor_Seconds_Fine_L_Seconds_Fine_W                         (65536.0)

/*-----------------------------------------------------*/
/*---                                               ---*/
/*---   Periodic Loop Rate Time Fixed Types         ---*/
/*---   Use following comments for reference only!  ---*/
/*---   Brighton code uses different loop timing!   ---*/
/*---                                               ---*/
/*-----------------------------------------------------*/

/*--------------------------------------------------------------*/
/*--- These types are measuring the time based on the cyclic ---*/
/*--- scheduler loop base period and multiples.              ---*/
/*---                                                        ---*/
/*--- Type                   Range (seconds)  Precision      ---*/
/*--- ------------           --------------   ------------   ---*/
/*--- EveryFastLoopSecB      0.. < 0.85        0.003328 sec  ---*/
/*--- EveryFastLoopSecW      0.. < 218         0.003328 sec  ---*/
/*--- EverySemiFastLoopSecB  0.. < 1.7         0.006656 sec  ---*/
/*--- EverySemiFastLoopSecW  0.. < 436         0.006656 sec  ---*/
/*--- Every_Loop_Sec_B       0.. < 2.5         0.01000 sec   ---*/
/*--- Every_Loop_Sec_W       0.. < 642         0.01000 sec   ---*/
/*--- Every_2nd_Loop_Sec_B   0.. < 5           0.02000 sec   ---*/
/*--- Every_2nd_Loop_Sec_W   0.. < 1284        0.02000 sec   ---*/
/*--- Every_4th_Loop_Sec_B   0.. < 10          0.04000 sec   ---*/
/*--- Every_4th_Loop_Sec_W   0.. < 2569        0.04000 sec   ---*/
/*--- Every_8th_Loop_Sec_B   0.. < 20          0.08000 sec   ---*/
/*--- Every_8th_Loop_Sec_W   0.. < 5138        0.08000 sec   ---*/
/*--- Every_16th_Loop_Sec_B  0.. < 40          0.16000 sec   ---*/
/*--- Every_16th_Loop_Sec_W  0.. < 10276       0.16000 sec   ---*/
/*--- Every_32nd_Loop_Sec_B  0.. < 80          0.32000 sec   ---*/
/*--- Every_32nd_Loop_Sec_W  0.. < 20552       0.32000 sec   ---*/
/*--- Every_64th_Loop_Sec_B  0.. < 160         0.64000 sec   ---*/
/*--- Every_64th_Loop_Sec_W  0.. < 41104       0.64000 sec   ---*/
/*--- Every_1Sec_Loop_Sec_B  0.. < 256         1.00000 sec   ---*/
/*--- Every_1Sec_Loop_Sec_W  0.. < 65536       1.00000 sec   ---*/
/*--- Every_1mn_Loop_Sec_L   0.. < 4294967296  1.00000 mn    ---*/
/*--------------------------------------------------------------*/

typedef SHORTCARD                                            EveryFastLoopSecB;
#define Prec_EveryFastLoopSecB                               (FastRtiPrescaler)
#define Min_EveryFastLoopSecB                                             (0.0)
#define Max_EveryFastLoopSecB                    (255 * Prec_EveryFastLoopSecB)
typedef CARDINAL                                             EveryFastLoopSecW;
#define Prec_EveryFastLoopSecW                               (FastRtiPrescaler)
#define Min_EveryFastLoopSecW                                             (0.0)
#define Max_EveryFastLoopSecW                  (65535 * Prec_EveryFastLoopSecW)

typedef SHORTCARD                                        EverySemiFastLoopSecB;
#define Prec_EverySemiFastLoopSecB                       (SemiFastRtiPrescaler)
#define Min_EverySemiFastLoopSecB                                         (0.0)
#define Max_EverySemiFastLoopSecB            (255 * Prec_EverySemiFastLoopSecB)
typedef CARDINAL                                         EverySemiFastLoopSecW;
#define Prec_EverySemiFastLoopSecW                       (SemiFastRtiPrescaler)
#define Min_EverySemiFastLoopSecW                                         (0.0)
#define Max_EverySemiFastLoopSecW          (65535 * Prec_EverySemiFastLoopSecW)

typedef CARDINAL                                              Every_Loop_Sec_W;
#define Prec_Every_Loop_Sec_W                                    (Prec_Seconds)
#define Min_Every_Loop_Sec_W                                              (0.0)
#define Max_Every_Loop_Sec_W                             (65535 * Prec_Seconds)
typedef SHORTCARD                                             Every_Loop_Sec_B;
#define Prec_Every_Loop_Sec_B                                    (Prec_Seconds)
#define Min_Every_Loop_Sec_B                                              (0.0)
#define Max_Every_Loop_Sec_B                               (255 * Prec_Seconds)
/*      CALDEF
*|      types.Every_Loop_Sec_Prec
*|      {
*|         : kind = constant;
*/
#if OS_SCHEDULER_10ms == CeSYST_AVAILABLE
/*
*|         : value = (0.010000);
*/
#else
/*
*|         : value = (0.015625);
*/
#endif
/*
*|      }
*|      types.Every_Loop_Sec_W
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_Loop_Sec_Prec);
*|         : range = (0.000000) TO (65535 * types.Every_Loop_Sec_Prec);
*|      }
*|      types.Every_Loop_Sec_B
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_Loop_Sec_Prec);
*|         : range = (0.000000) TO (255 * types.Every_Loop_Sec_Prec);
*|      }
*/

typedef CARDINAL                                          Every_2nd_Loop_Sec_W;
#define Prec_Every_2nd_Loop_Sec_W                            (2 * Prec_Seconds)
#define Min_Every_2nd_Loop_Sec_W                                          (0.0)
#define Max_Every_2nd_Loop_Sec_W                     (65535 * 2 * Prec_Seconds)
typedef SHORTCARD                                         Every_2nd_Loop_Sec_B;
#define Prec_Every_2nd_Loop_Sec_B                            (2 * Prec_Seconds)
#define Min_Every_2nd_Loop_Sec_B                                          (0.0)
#define Max_Every_2nd_Loop_Sec_B                       (255 * 2 * Prec_Seconds)
/*      CALDEF
*|      types.Every_2nd_Loop_Sec_Prec
*|      {
*|         : kind = constant;
*|         : value = (2 * types.Every_Loop_Sec_Prec);
*|      }
*|      types.Every_2nd_Loop_Sec_W
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_2nd_Loop_Sec_Prec);
*|         : range = (0.000000) TO (65535 * types.Every_2nd_Loop_Sec_Prec);
*|      }
*|      types.Every_2nd_Loop_Sec_B
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_2nd_Loop_Sec_Prec);
*|         : range = (0.000000) TO (255 * types.Every_2nd_Loop_Sec_Prec);
*|      }
*/

typedef CARDINAL                                          Every_4th_Loop_Sec_W;
#define Prec_Every_4th_Loop_Sec_W                            (4 * Prec_Seconds)
#define Min_Every_4th_Loop_Sec_W                                          (0.0)
#define Max_Every_4th_Loop_Sec_W                     (65535 * 4 * Prec_Seconds)
typedef SHORTCARD                                         Every_4th_Loop_Sec_B;
#define Prec_Every_4th_Loop_Sec_B                            (4 * Prec_Seconds)
#define Min_Every_4th_Loop_Sec_B                                          (0.0)
#define Max_Every_4th_Loop_Sec_B                       (255 * 4 * Prec_Seconds)
/*      CALDEF
*|      types.Every_4th_Loop_Sec_Prec
*|      {
*|         : kind = constant;
*|         : value = (4 * types.Every_Loop_Sec_Prec);
*|      }
*|      types.Every_4th_Loop_Sec_W
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_4th_Loop_Sec_Prec);
*|         : range = (0.000000) TO (65535 * types.Every_4th_Loop_Sec_Prec);
*|      }
*|      types.Every_4th_Loop_Sec_B
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_4th_Loop_Sec_Prec);
*|         : range = (0.000000) TO (255 * types.Every_4th_Loop_Sec_Prec);
*|      }
*/

typedef CARDINAL                                          Every_8th_Loop_Sec_W;
#define Prec_Every_8th_Loop_Sec_W                            (8 * Prec_Seconds)
#define Min_Every_8th_Loop_Sec_W                                          (0.0)
#define Max_Every_8th_Loop_Sec_W                     (65535 * 8 * Prec_Seconds)
typedef SHORTCARD                                         Every_8th_Loop_Sec_B;
#define Prec_Every_8th_Loop_Sec_B                            (8 * Prec_Seconds)
#define Min_Every_8th_Loop_Sec_B                                          (0.0)
#define Max_Every_8th_Loop_Sec_B                       (255 * 8 * Prec_Seconds)
/*      CALDEF
*|      types.Every_8th_Loop_Sec_Prec
*|      {
*|         : kind = constant;
*|         : value = (8 * types.Every_Loop_Sec_Prec);
*|      }
*|      types.Every_8th_Loop_Sec_W
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_8th_Loop_Sec_Prec);
*|         : range = (0.000000) TO (65535 * types.Every_8th_Loop_Sec_Prec);
*|      }
*|      types.Every_8th_Loop_Sec_B
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_8th_Loop_Sec_Prec);
*|         : range = (0.000000) TO (255 * types.Every_8th_Loop_Sec_Prec);
*|      }
*/

typedef CARDINAL                                         Every_16th_Loop_Sec_W;
#define Prec_Every_16th_Loop_Sec_W                          (16 * Prec_Seconds)
#define Min_Every_16th_Loop_Sec_W                                         (0.0)
#define Max_Every_16th_Loop_Sec_W                   (65535 * 16 * Prec_Seconds)
typedef SHORTCARD                                        Every_16th_Loop_Sec_B;
#define Prec_Every_16th_Loop_Sec_B                          (16 * Prec_Seconds)
#define Min_Every_16th_Loop_Sec_B                                         (0.0)
#define Max_Every_16th_Loop_Sec_B                     (255 * 16 * Prec_Seconds)
/*      CALDEF
*|      types.Every_16th_Loop_Sec_Prec
*|      {
*|         : kind = constant;
*|         : value = (16 * types.Every_Loop_Sec_Prec);
*|      }
*|      types.Every_16th_Loop_Sec_W
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_16th_Loop_Sec_Prec);
*|         : range = (0.000000) TO (65535 * types.Every_16th_Loop_Sec_Prec);
*|      }
*|      types.Every_16th_Loop_Sec_B
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_16th_Loop_Sec_Prec);
*|         : range = (0.000000) TO (255 * types.Every_16th_Loop_Sec_Prec);
*|      }
*/

typedef CARDINAL                                         Every_32nd_Loop_Sec_W;
#define Prec_Every_32nd_Loop_Sec_W                          (32 * Prec_Seconds)
#define Min_Every_32nd_Loop_Sec_W                                         (0.0)
#define Max_Every_32nd_Loop_Sec_W                   (65535 * 32 * Prec_Seconds)
typedef SHORTCARD                                        Every_32nd_Loop_Sec_B;
#define Prec_Every_32nd_Loop_Sec_B                          (32 * Prec_Seconds)
#define Min_Every_32nd_Loop_Sec_B                                         (0.0)
#define Max_Every_32nd_Loop_Sec_B                     (255 * 32 * Prec_Seconds)
/*      CALDEF
*|      types.Every_32nd_Loop_Sec_Prec
*|      {
*|         : kind = constant;
*|         : value = (32 * types.Every_Loop_Sec_Prec);
*|      }
*|      types.Every_32nd_Loop_Sec_W
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_32nd_Loop_Sec_Prec);
*|         : range = (0.000000) TO (65535 * types.Every_32nd_Loop_Sec_Prec);
*|      }
*|      types.Every_32nd_Loop_Sec_B
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_32nd_Loop_Sec_Prec);
*|         : range = (0.000000) TO (255 * types.Every_32nd_Loop_Sec_Prec);
*|      }
*/

typedef CARDINAL                                         Every_64th_Loop_Sec_W;
#define Prec_Every_64th_Loop_Sec_W                          (64 * Prec_Seconds)
#define Min_Every_64th_Loop_Sec_W                                         (0.0)
#define Max_Every_64th_Loop_Sec_W                   (65535 * 64 * Prec_Seconds)
typedef SHORTCARD                                        Every_64th_Loop_Sec_B;
#define Prec_Every_64th_Loop_Sec_B                          (64 * Prec_Seconds)
#define Min_Every_64th_Loop_Sec_B                                         (0.0)
#define Max_Every_64th_Loop_Sec_B                     (255 * 64 * Prec_Seconds)
/*      CALDEF
*|      types.Every_64th_Loop_Sec_Prec
*|      {
*|         : kind = constant;
*|         : value = (64 * types.Every_Loop_Sec_Prec);
*|      }
*|      types.Every_64th_Loop_Sec_W
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_64th_Loop_Sec_Prec);
*|         : range = (0.000000) TO (65535 * types.Every_64th_Loop_Sec_Prec);
*|      }
*|      types.Every_64th_Loop_Sec_B
*|      {
*|         : kind = fixed;
*|         : precision = (types.Every_64th_Loop_Sec_Prec);
*|         : range = (0.000000) TO (255 * types.Every_64th_Loop_Sec_Prec);
*|      }
*/

typedef CARDINAL                                         Every_1Sec_Loop_Sec_W;
#define Prec_Every_1Sec_Loop_Sec_W                                        (1.0)
#define Min_Every_1Sec_Loop_Sec_W                                         (0.0)
#define Max_Every_1Sec_Loop_Sec_W                                 (65535 * 1.0)
typedef SHORTCARD                                        Every_1Sec_Loop_Sec_B;
#define Prec_Every_1Sec_Loop_Sec_B                                        (1.0)
#define Min_Every_1Sec_Loop_Sec_B                                         (0.0)
#define Max_Every_1Sec_Loop_Sec_B                                 (255.0 * 1.0)

typedef LONGCARD                                          Every_1mn_Loop_Sec_L;
#define Prec_Every_1mn_Loop_Sec_L                                         (1.0)
#define Min_Every_1mn_Loop_Sec_L                                          (0.0)
#define Max_Every_1mn_Loop_Sec_L                           (4294967295.0 * 1.0)

/*---  RFactors for Periodic Loop Rate Time Types  ---*/

#define RFactor_Every_2nd_Loop_Sec_B_Every_2nd_Loop_Sec_W \
                                                (256/Prec_Every_2nd_Loop_Sec_W)
#define RFactor_Every_2nd_Loop_Sec_W_Every_2nd_Loop_Sec_B \
                                                (256/Prec_Every_2nd_Loop_Sec_W)
#define RFactor_Milliseconds_W_Every_Loop_Sec_W       (1/Prec_Every_Loop_Sec_W)
#define RFactor_Milliseconds_W_EverySemiFastLoopSecW \
                                                 (1/Prec_EverySemiFastLoopSecW)
#define RFactor_Every_8th_Loop_Sec_B_Every_2nd_Loop_Sec_W \
                                              (1.0 / Prec_Every_2nd_Loop_Sec_W)
#define RFactor_Every_8th_Loop_Sec_B_Every_Loop_Sec_W \
                                                  (1.0 / Prec_Every_Loop_Sec_W)
#define RFactor_Every_2nd_Loop_Sec_B_EverySemiFastLoopSecB \
                                             (1.0 / Prec_EverySemiFastLoopSecB)
#define RFactor_Every_2nd_Loop_Sec_B_EveryFastLoopSecB \
                                                 (1.0 / Prec_EveryFastLoopSecB)
#define RFactor_Every_2nd_Loop_Sec_W_EverySemiFastLoopSecB \
                                             (1.0 / Prec_EverySemiFastLoopSecB)
#define RFactor_Every_2nd_Loop_Sec_W_EveryFastLoopSecB \
                                                 (1.0 / Prec_EveryFastLoopSecB)

/*--------------------------------------*/
/*---                                ---*/
/*---   Injection Time Fixed Types   ---*/
/*---                                ---*/
/*--------------------------------------*/

typedef CARDINAL                                                 MicroSec_Slow;
#define Prec_MicroSec_Slow                                                (8.0)
#define Min_MicroSec_Slow                                                 (0.0)
#define Max_MicroSec_Slow   (MAX_CARDINAL*Prec_MicroSec_Slow+Min_MicroSec_Slow)

typedef MicroSec_Slow                                             MicroSec_INJ;
#define Prec_MicroSec_INJ                                  (Prec_MicroSec_Slow)
#define Min_MicroSec_INJ                                    (Min_MicroSec_Slow)
#define Max_MicroSec_INJ                                    (Max_MicroSec_Slow)

typedef SHORTCARD                                               MicroSec_INJ_B;
#define Prec_MicroSec_INJ_B                                 (Prec_MicroSec_INJ)
#define Min_MicroSec_INJ_B                                   (Min_MicroSec_INJ)
#define Max_MicroSec_INJ_B \
                     (MAX_SHORTCARD * Prec_MicroSec_INJ_B + Min_MicroSec_INJ_B)

typedef MicroSec_INJ                                       MicroSec_INJ_Signed;
#define Prec_MicroSec_INJ_Signed                            (Prec_MicroSec_INJ)
#define Min_MicroSec_INJ_Signed           (-32768.0 * Prec_MicroSec_INJ_Signed)
#define Max_MicroSec_INJ_Signed            (32767.0 * Prec_MicroSec_INJ_Signed)

typedef LONGCARD                                             MicroSec_INJ_Base;
#define Prec_MicroSec_INJ_Base                              (Prec_MicroSec_INJ)
#define Min_MicroSec_INJ_Base                                             (0.0)
#define Max_MicroSec_INJ_Base           (MAX_LONGCARD * Prec_MicroSec_INJ_Base)

typedef LONGCARD                                      MicroSec_INJ_Signed_Base;
#define Prec_MicroSec_INJ_Signed_Base                       (Prec_MicroSec_INJ)
#define Min_MicroSec_INJ_Signed_Base \
                                (-2147483648.0 * Prec_MicroSec_INJ_Signed_Base)
#define Max_MicroSec_INJ_Signed_Base \
                                 (2147483647.0 * Prec_MicroSec_INJ_Signed_Base)

typedef MicroSec_INJ                                                   Sec_INJ;
#define Prec_Sec_INJ                              (Prec_MicroSec_INJ / 1000000)
#define Min_Sec_INJ                                          (Min_MicroSec_INJ)
#define Max_Sec_INJ                                      (65535 * Prec_Sec_INJ)

typedef LONGCARD                                                  Sec_INJ_Base;
#define Prec_Sec_INJ_Base                                        (Prec_Sec_INJ)
#define Min_Sec_INJ_Base                                     (Min_MicroSec_INJ)
#define Max_Sec_INJ_Base                            (4294967295 * Prec_Sec_INJ)

/*---  RFactors for Injection Time Types  ---*/

#define RFactor_MicroSec_INJ_MicroSec_INJ_Hw       (1.0 / Prec_MicroSec_INJ_Hw)
#define RFactor_MicroSec_INJ_Hw_MicroSec_INJ       (1.0 / Prec_MicroSec_INJ_Hw)
#define RFactor_MicroSec_58X_MicroSec_INJ             (1.0 / Prec_MicroSec_INJ)
#define RFactor_MicroSec_INJ_MicroSec_58X             (1.0 / Prec_MicroSec_INJ)
#define RFactor_MicroSec_INJ_Base_MicroSec_INJ        (1.0 / Prec_MicroSec_INJ)
#define RFactor_MicroSec_INJ_Hw_MicroSec_INJ_Base     (1.0 / Prec_MicroSec_INJ)
#define RFactor_MicroSec_INJ_Base_MicroSec_INJ_Hw  (1.0 / Prec_MicroSec_INJ_Hw)
#define RFactor_MicroSec_INJ_MicroSec_INJ_Base     (1.0 / Prec_MicroSec_INJ_Hw)
#define RFactor_Sec_INJ_Base_Sec_INJ                       (1.0 / Prec_Sec_INJ)
#define RFactor_Sec_INJ_Sec_INJ_Base                       (1.0 / Prec_Sec_INJ)
#define RFactor_MicroSec_INJ_MicroSec_INJ_Signed      (1.0 / Prec_MicroSec_INJ)
#define RFactor_MicroSec_INJ_Signed_MicroSec_INJ      (1.0 / Prec_MicroSec_INJ)
#define RFactor_MicroSec_INJ_Signed_MicroSec_INJ_Signed_Base \
                                                      (1.0 / Prec_MicroSec_INJ)
#define RFactor_MicroSec_INJ_Signed_Base_MicroSec_INJ_Signed \
                                                      (1.0 / Prec_MicroSec_INJ)
#define RFactor_MicroSec_INJ_Signed_Base_MicroSec_INJ (1.0 / Prec_MicroSec_INJ)
#define RFactor_MicroSec_INJ_MicroSec_INJ_Signed_Base (1.0 / Prec_MicroSec_INJ)

/*--------------------------------*/
/*---                          ---*/
/*---   Frequency Fixed Types  ---*/
/*---                          ---*/
/*--------------------------------*/

/*--------------------------------------------------------------------*/
/*--- Hertz_2B is scaled with table lookup breakpoints in mind.    ---*/
/*--- Hertz     is scaled with timer configuration in mind         ---*/
/*---                                                              ---*/
/*--- Type            Range (RPM)      Precision      Based on     ---*/
/*--- --------------  --------------   ------------   ------------ ---*/
/*--- Hertz_2B        0 .. < 32768.0   0.5 Hertz      Table lookup ---*/
/*--- Hertz           0 .. < 2.15e9    0.5 Hertz      Table lookup ---*/
/*--------------------------------------------------------------------*/

typedef CARDINAL                                                      Hertz_2B;
#define Prec_Hertz_2B                                                     (0.5)
#define Min_Hertz_2B                                                      (0.0)
#define Max_Hertz_2B                                              (65535 * 0.5)

typedef LONGCARD                                                         Hertz;
#define Prec_Hertz                                                        (0.5)
#define Min_Hertz                                                         (0.0)
#define Max_Hertz                                   (Max_LONGCARD * Prec_Hertz)

/*-------------------------------*/
/*---                         ---*/
/*---   Pressure Fixed Types  ---*/
/*---                         ---*/
/*-------------------------------*/

/*---------------------------------------------------------------------*/
/*--- This pressure type is scaled for Air conditioning system type ---*/
/*--- of pressure.                                                  ---*/
/*---                                                               ---*/
/*--- Type                Range (kPa)  Precision(kPa/bit)  Based on ---*/
/*--- -----------------  ------------  -------------  ------------- ---*/
/*--- AcPressureTypeInKPa 0.0 .. 5100.0 20.0          physical range---*/
/*---------------------------------------------------------------------*/

typedef SHORTCARD                                          AcPressureTypeInKPa;
#define Prec_AcPressureTypeInKPa                                         (20.0)
#define Min_AcPressureTypeInKPa                                           (0.0)
#define Max_AcPressureTypeInKPa                                        (5100.0)

typedef CARDINAL                                     AcPresInKPa_Plus_Fraction;
#define Prec_AcPresInKPa_Plus_Fraction           (Prec_AcPressureTypeInKPa/256)
#define Min_AcPresInKPa_Plus_Fraction                 (Min_AcPressureTypeInKPa)
#define Max_AcPresInKPa_Plus_Fraction \
                                     (65535.0 * Prec_AcPresInKPa_Plus_Fraction)
/*      CALDEF
*|      types.AcPresInKPa_Plus_Fraction
*|      {
*|         : kind = fixed;
*|         : precision = (20.0 / 256);
*|         : range = (0.000000) TO (65535 * 20.0 / 256);
*|      }
*/

/*---------------------------------------------------------------------*/
/*--- MANIFOLD / ATMOSPHERIC PRESSURES                              ---*/
/*--- The pressure types defined here after are derived from the    ---*/
/*--- characteristics of the Manifold Absolute Pressure Sensor :    ---*/
/*---  Va/d / Vref = 0.01059 * kPa - 0.10941                        ---*/
/*---   .the lowest measurable pressure : (Va/d / Vref)= 0          ---*/
/*---                0.10941 / 0.01059 = 10.33 kpa                  ---*/
/*---   .the largest measurable pressure : (Va/d / Vref)= 1         ---*/
/*---               (0.10941 + 1)/ 0.01059 = 104.76 kPa             ---*/
/*---                                                               ---*/
/*--- Pressure is measured in kiloPascals.                          ---*/
/*---                                                               ---*/
/*--- Type                Range (kPa)  Precision(kPa/bit)  Based on ---*/
/*--- -----------------  ------------  -------------  ------------- ---*/
/*--- kPa_W              0.0 .. 105.0   0.01953       Table_Lookups ---*/
/*--- kPa_Base           0.0 .. 24173   0.36886       Biased base   ---*/
/*--- kPa_B              10.34..104.4   0.36886       Filtered kPa  ---*/
/*--- kPa_HiRes          0.0 .. 105.0   0.00390625    air_spd       ---*/
/*--- kPa_Double         0.0 .. 105.0   0.001953      intern.fl_bpw ---*/
/*--- kPa_Delta          0.0 .. 94.06   0.36886       Delta KPAs    ---*/
/*--- kPa_DeltaHalfRange 0.0 .. 47.03   0.18443       Delta KPAs    ---*/
/*--- kPa_Delta_Plus_Fra 0.0 .. 94.06   0.001441      Delta KPAs    ---*/
/*--- kPa_Plus_Fraction  10.34..104.8   0.001441                    ---*/
/*--- kPaPerPercentMulti.0.0 .. 1.881   0.007377      intern.v_press---*/
/*--- kPaSignedB        -47.03..47.03   0.36886       OBD Egr Flow  ---*/
/*--- kPaSignedPlusFra  -47.03..47.03   0.001441      OBD Egr Flow  ---*/
/*--- kPa_IMEP_B         0.0..4080.0    16.0          IMEP          ---*/
/*--- kPa_IMEP_W         0.0..4095.93   0.0625        IMEP          ---*/
/*---                                                               ---*/
/*---  NOTE: KPA_B is based on the "unscaled MAP" of:               ---*/
/*---                    N = E * 2.71104 - 28.05502                 ---*/
/*---------------------------------------------------------------------*/

#define kPaBias            /*--- 10.33 kPa ---*/            (0.10941 / 0.01059)
#define kPaBasePrec     /*--- 0.36886 kPa/bit---*/    (1.0 / (256.0 * 0.01059))

typedef CARDINAL                                                         kPa_W;
#define Prec_kPa_W                                                  (5.0 / 256)
#define Min_kPa_W                                                         (0.0)
#define Max_kPa_W                                                       (105.0)

typedef CARDINAL                                                      kPa_Base;
#define Prec_kPa_Base                                             (kPaBasePrec)
#define Min_kPa_Base                                                      (0.0)
#define Max_kPa_Base                                      (65535 * kPaBasePrec)

typedef SHORTCARD                                                        kPa_B;
#define Prec_kPa_B                                                (kPaBasePrec)
#define Min_kPa_B                                                     (kPaBias)
#define Max_kPa_B                                 (255 * kPaBasePrec + kPaBias)

typedef CARDINAL                                                     kPa_HiRes;
#define Prec_kPa_HiRes                                              (1.0 / 256)
#define Min_kPa_HiRes                                                     (0.0)
#define Max_kPa_HiRes                                       (65535 * 1.0 / 256)

typedef CARDINAL                                                    kPa_Double;
#define Prec_kPa_Double                                             (0.5 / 256)
#define Min_kPa_Double                                                    (0.0)
#define Max_kPa_Double                                                  (105.0)

/*---------------------------------------------------------------------*/
/*--- WARNING!!! The Precision of kPa_Delta MUST be the same as for ---*/
/*--- kPa_B and the kPa Delta min MUST be null for correct use in   ---*/
/*--- the fixed point functions for type and delta of that type.    ---*/
/*---------------------------------------------------------------------*/
typedef SHORTCARD                                                    kPa_Delta;
#define Prec_kPa_Delta                                            (kPaBasePrec)
#define Min_kPa_Delta                                                     (0.0)
#define Max_kPa_Delta                                       (255 * kPaBasePrec)

typedef CARDINAL                                                   kPa_Delta_W;
#define Prec_kPa_Delta_W                                           (Prec_kPa_W)
#define Min_kPa_Delta_W                                                   (0.0)
#define Max_kPa_Delta_W                              (65535 * Prec_kPa_Delta_W)

typedef SHORTCARD                                           kPa_DeltaHalfRange;
#define Prec_kPa_DeltaHalfRange                          (Prec_kPa_Delta / 2.0)
#define Min_kPa_DeltaHalfRange                                            (0.0)
#define Max_kPa_DeltaHalfRange                  (255 * Prec_kPa_DeltaHalfRange)

typedef CARDINAL                                       kPa_Delta_Plus_Fraction;
#define Prec_kPa_Delta_Plus_Fraction                        (kPaBasePrec / 256)
#define Min_kPa_Delta_Plus_Fraction                                       (0.0)
#define Max_kPa_Delta_Plus_Fraction                 (65535 * kPaBasePrec / 256)

typedef CARDINAL                                             kPa_Plus_Fraction;
#define Prec_kPa_Plus_Fraction                              (kPaBasePrec / 256)
#define Min_kPa_Plus_Fraction                                         (kPaBias)
#define Max_kPa_Plus_Fraction             (65535 * kPaBasePrec / 256 + kPaBias)

typedef CARDINAL                                      kPa_Boost;

#define Prec_kPa_Boost                               (1.0 / 128)
#define Min_kPa_Boost                                      (0.0)
#define Max_kPa_Boost                        (65535 * 1.0 / 128)
/*      CALDEF
*|      types.kPa_Boost
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 128.0);
*|         : range = (0.000000) TO (65535.0 / 128.0);
*|      }
*/

typedef CARDINAL                                kPa_Boost_LoRes;

#define Prec_kPa_Boost_LoRes                          (1.0 / 16)
#define Min_kPa_Boost_LoRes                                (0.0)
#define Max_kPa_Boost_LoRes                   (65535 * 1.0 / 16)
/*      CALDEF
*|      types.kPa_Boost_LoRes
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 16.0);
*|         : range = (0.000000) TO (65535.0 / 16.0);
*|      }
*/
typedef unsigned short                   kPa_Boost_LoRes_Signed;

#define Prec_kPa_Boost_LoRes_Signed       (1.0 / 16)
#define Min_kPa_Boost_LoRes_Signed        (-2048.0 )
#define Max_kPa_Boost_LoRes_Signed        ( 2047.0)
/*      CALDEF
*|      types.kPa_Boost_LoRes_Signed
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 16.0);
*|         : range = (-2048.0) TO (2047.0);
*|         : biased;
*|      }
*/

typedef LONGCARD                                kPa_Boost_HiRes;

#define Prec_kPa_Boost_HiRes                     (1.0 / 1048576)
#define Min_kPa_Boost_HiRes                                (0.0)
#define Max_kPa_Boost_HiRes         (4294967296 * 1.0 / 1048576)


typedef LONGCARD                          kPa_Boost_HiRes_Signed;

#define Prec_kPa_Boost_HiRes_Signed              (1.0 / 1048576)
#define Min_kPa_Boost_HiRes_Signed                     (-2048.0)
#define Max_kPa_Boost_HiRes_Signed                     (2047.0 )

typedef LONGCARD                                              kPa_Plus_Fract_L;
#define Prec_kPa_Plus_Fract_L                               (kPaBasePrec / 256)
#define Min_kPa_Plus_Fract_L                                          (kPaBias)
#define Max_kPa_Plus_Fract_L \
                  (4294967295.0 * Prec_kPa_Plus_Fract_L + Min_kPa_Plus_Fract_L)

typedef SHORTCARD                                      kPaPerPercentMultiplier;
#define Prec_kPaPerPercentMultiplier \
                         (Prec_kPa_B * Prec_Multiplier_0_to_2 / Prec_Percent_B)
#define Min_kPaPerPercentMultiplier                                       (0.0)
#define Max_kPaPerPercentMultiplier        (255 * Prec_kPaPerPercentMultiplier)

typedef SHORTCARD                                                   kPaSignedB;
#define Prec_kPaSignedB                                           (kPaBasePrec)
#define Min_kPaSignedB                                                 (-47.03)
#define Max_kPaSignedB                     (255 * kPaBasePrec + Min_kPaSignedB)

typedef CARDINAL                                         kPaSignedPlusFraction;
#define Prec_kPaSignedPlusFraction                          (kPaBasePrec / 256)
#define Min_kPaSignedPlusFraction                                      (-47.03)
#define Max_kPaSignedPlusFraction \
                        (65535 * kPaBasePrec / 256 + Min_kPaSignedPlusFraction)

typedef SHORTCARD                                                   kPa_IMEP_B;
#define Prec_kPa_IMEP_B                                                  (16.0)
#define Min_kPa_IMEP_B                                                    (0.0)
#define Max_kPa_IMEP_B                 (255 * Prec_kPa_IMEP_B + Min_kPa_IMEP_B)
/*      CALDEF
*|      types.kPa_IMEP_B
*|      {
*|         : kind = fixed;
*|         : precision = (16.0);
*|         : range = (0.0) TO (255  * 16.0);
*|      }
*/

typedef CARDINAL                                                    kPa_IMEP_W;
#define Prec_kPa_IMEP_W                                   (Prec_kPa_IMEP_B/256)
#define Min_kPa_IMEP_W                                                    (0.0)
#define Max_kPa_IMEP_W               (65535 * Prec_kPa_IMEP_W + Min_kPa_IMEP_W)
#define V_kPa_IMEP_W (val)           (WORD)((val)/Prec_kPa_IMEP_W)
/*      CALDEF
*|      types.kPa_IMEP_W
*|      {
*|         : kind = fixed;
*|         : precision = (16.0 / 256);
*|         : range = (0.0) TO (65535  * 16.0 / 256);
*|      }
*/

typedef LONGCARD                                                 kPa_IMEP_Base;
#define Prec_kPa_IMEP_Base                                    (Prec_kPa_IMEP_W)
#define Min_kPa_IMEP_Base                                                 (0.0)
#define Max_kPa_IMEP_Base (4294967295 * Prec_kPa_IMEP_Base + Min_kPa_IMEP_Base)

typedef CARDINAL                                       kPa_IMEP_B_PlusFraction;
#define Prec_kPa_IMEP_B_PlusFraction                      (Prec_kPa_IMEP_B/256)
#define Min_kPa_IMEP_B_PlusFraction                                       (0.0)
#define Max_kPa_IMEP_B_PlusFraction \
           (65535 * Prec_kPa_IMEP_B_PlusFraction + Min_kPa_IMEP_B_PlusFraction)

/*---  Axis Enumerations for Pressure Types  ---*/

#define AcPreskPa_1800to2800by200_Steps                                     (6)
/*      CALDEF      */
#define kPa_0to3000by500_Steps                                              (7)
/*      CALDEF
*|      types.kPa_0to3000by500_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "A/C_kPa";
*|         : table = (0 TO 3000 BY 500);
*|      }
*/
#define kPa_20to100by20_Steps                                               (5)
/*      CALDEF      */
#define kPa_0to100by10_Steps                                               (11)
/*      CALDEF      */
#define kPa_0to120by10_Steps                                               (13)
/*      CALDEF
*|      types.kPa_0to120by10_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "KPa";
*|         : table = (0 TO 120 BY 10);
*|      }
*/
#define kPa_0to80by5_Steps                                                 (17)
/*      CALDEF      */
#define kPa_0to80by10_Steps                                                 (9)
/*      CALDEF      */
#define kPa_75to105by10_Steps                                               (4)
/*      CALDEF      */
#define kPa_65to105by20_Steps                                               (3)
/*      CALDEF      */
#define kPa_65to105by10_Steps                                               (5)
/*      CALDEF      */
#define kPa_65to105by5_Steps                                                (9)
/*      CALDEF      */
#define kPa_70to100by5_Steps                                                (7)
/*      CALDEF      */
#define kPa_20to100by10_Steps                                               (9)
/*      CALDEF      */
#define kPa_100to300by10_Steps                                              (21)
/*      CALDEF
*|      types.kPa_100to300by10_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "KPa";
*|         : table = (100 TO 300 BY 10);
*|      }
*/
#define kPa_0to105by5_Steps                                                (22)
/*      CALDEF      */
#define kPa_0to70by5_Steps                                                 (15)
/*      CALDEF      */
#define kPa_10to105by5_Steps                                               (20)
/*      CALDEF      */
#define kPa_20to70by5_Steps                                                (11)
/*      CALDEF      */
#define kPa_20to100by5_Steps                                               (17)
/*      CALDEF      */
#define kPa_60to100by10_Steps                                               (5)
/*      CALDEF      */
#define kPa_75to105by5_Steps                                                (7)
/*      CALDEF      */
#define kPa_0to40by5_Steps                                                  (9)
/*      CALDEF      */
#define kPa_15to70by5_Steps                                                (12)
/*      CALDEF      */
#define kPa_15to100by5_Steps                                               (18)
/*      CALDEF      */
#define kPa_0to95by5_Steps                                                 (20)
/*      CALDEF
*|      types.kPa_0to95by5_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "kPa";
*|         : table = (0 TO 95 BY 5);
*|      }
*/
#define kPaIMEP_0to800by50_Steps                                           (17)
/*      CALDEF
*|      types.kPaIMEP_0to800by50_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "kPa_IMEP_W";
*|         : table = (0 TO 800 BY 50);
*|      }
*/
#define kPaIMEP_0to1600by100_Steps                                         (17)
/*      CALDEF
*|      types.kPaIMEP_0to1600by100_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "kPa_IMEP_W";
*|         : table = (0 TO 1600 BY 100);
*|      }
*/
#define kPaIMEP_0to3200by100_Steps                                         (33)
/*      CALDEF
*|      types.kPaIMEP_0to3200by100_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "kPa_IMEP_W";
*|         : table = (0 TO 3200 BY 100);
*|      }
*/

#define kPaIMEP_20to200by20_Steps                                          (10)
/*      CALDEF
*|      types.kPaIMEP_20to200by20_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "kPa_IMEP_W";
*|         : table = (20 TO 200 BY 20);
*|      }
*/
#define kPaIMEP_0to1600by200_Steps                                          (9)
/*      CALDEF
*|      types.kPaIMEP_0to1600by200_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "kPa_IMEP_W";
*|         : table = (0 TO 1600 BY 200);
*|      }
*/
#define kPaIMEP_0to3200by200_Steps                                          (17)
/*      CALDEF
*|      types.kPaIMEP_0to3200by200_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "kPa_IMEP_W";
*|         : table = (0 TO 3200 BY 200);
*|      }
*/
/*---  RFactors for Pressure Types  ---*/

#define RFactor_AcPresInKPa_Plus_Fraction_AcPressureTypeInKPa      (65536.0/20)
#define RFactor_AcPressureTypeInKPa_AcPresInKPa_Plus_Fraction      (65536.0/20)
#define RFactor_kPa_Base_kPa_W                                        (54220.8)
#define RFactor_kPa_Delta_W_kPa_Delta                      (256*0.01059*100000)
#define RFactor_kPa_Delta_kPa_Delta_W           (RFactor_kPa_Delta_W_kPa_Delta)
#define RFactor_kPa_IMEP_B_PlusFraction_kPa_IMEP_B \
                                               (1/Prec_kPa_IMEP_B_PlusFraction)
#define RFactor_kPa_IMEP_B_kPa_IMEP_B_PlusFraction \
                                               (1/Prec_kPa_IMEP_B_PlusFraction)
#define RFactor_kPa_IMEP_W_kPa_IMEP_Base                                  (128)
#define RFactor_kPa_IMEP_Base_kPa_IMEP_W                                  (128)
#define RFactor_kPa_Base_kPa_B                                (256.0 * 0.01059)
#define RFactor_kPa_Base_kPa_Delta                            (256.0 * 0.01059)
#define RFactor_kPa_W_kPa_B                                             (512.0)
#define RFactor_kPa_W_kPa_Plus_Fraction                 (128 * 65536 * 0.01059)
#define RFactor_kPa_W_kPa_Delta                      (65536.0 / Prec_kPa_Delta)
#define RFactor_kPa_Delta_kPa_W                      (65536.0 / Prec_kPa_Delta)
#define RFactor_kPa_Delta_kPa_Base                 (RFactor_kPa_Base_kPa_Delta)
#define RFactor_kPa_Delta_kPa_DeltaHalfRange             (2.0 / Prec_kPa_Delta)
#define RFactor_kPa_DeltaHalfRange_kPa_Delta             (2.0 / Prec_kPa_Delta)
#define RFactor_kPa_Delta_kPa_Delta_Plus_Fraction           (65536.0 * 0.01059)
#define RFactor_kPa_Delta_kPa_Plus_Fraction                 (65536.0 * 0.01059)
#define RFactor_kPa_B_kPa_Base                                (256.0 * 0.01059)
#define RFactor_kPa_Boost_kPa_Boost_LoRes                               (128.0)
#define RFactor_kPa_B_kPa_W                                             (512.0)
#define RFactor_kPa_B_kPa_Plus_Fraction                     (65536.0 * 0.01059)
#define RFactor_kPa_Plus_Fraction_kPa_Base                    (65536 * 0.01059)
#define RFactor_kPa_Base_kPa_Plus_Fraction                    (65536 * 0.01059)
#define RFactor_kPa_Plus_Fraction_kPa_W                 (128 * 65536 * 0.01059)
#define RFactor_kPa_Plus_Fraction_kPa_B                     (65536.0 * 0.01059)
#define RFactor_kPa_Plus_Fraction_kPa_Double            (256 * 65536 * 0.01059)
#define RFactor_kPa_Plus_Fraction_kPa_Plus_Fract_L \
                                                 (1.0 / Prec_kPa_Plus_Fraction)
#define RFactor_kPa_Plus_Fract_L_kPa_Plus_Fraction \
                                                 (1.0 / Prec_kPa_Plus_Fraction)
#define RFactor_kPa_Plus_Fraction_Base_kPa_Plus_Fraction    (65536.0 * 0.01059)
#define RFactor_kPa_Delta_kPa_B                               (256.0 * 0.01059)
#define RFactor_kPa_B_kPa_Delta                               (256.0 * 0.01059)
#define RFactor_kPa_Plus_Fraction_kPa_HiRes             (256 * 65536 * 0.01059)
#define RFactor_kPa_W_kPa_HiRes                                          (1280)
#define RFactor_kPa_IMEP_W_kPa_IMEP_B                                    (16.0)
#define RFactor_kPa_IMEP_B_kPa_IMEP_W                                    (16.0)
#define RFactor_kPa_W_kPa_IMEP_B                                         (256)
#define RFactor_kPa_IMEP_B_kPa_W                                         (256)
#define RFactor_kPa_Boost_LoRes_Signed_kPa_Boost_LoRes                   (16.0)
#define RFactor_kPa_Boost_LoRes_kPa_Boost_LoRes_Signed                   (16.0)

#define RFactor_kPa_Boost_HiRes_Signed_kPa_Boost_LoRes_Signed            (1048576.0)
#define RFactor_kPa_Boost_LoRes_Signed_kPa_Boost_HiRes_Signed            (1048576.0)
#define RFactor_kPaSignedB_kPaSignedPlusFraction            (256 / kPaBasePrec)
#define RFactor_kPaSignedPlusFraction_kPaSignedB            (256 / kPaBasePrec)
#define RFactor_kPa_Delta_kPaSignedB                          (1 / kPaBasePrec)
#define RFactor_kPaSignedB_kPa_Delta                          (1 / kPaBasePrec)


/*----------------------------------*/
/*---                            ---*/
/*---   Temperature Fixed Types  ---*/
/*---                            ---*/
/*----------------------------------*/

/*---------------------------------------------------------------------------*/
/*--- Type                Range (Deg C)   Precision   Based on            ---*/
/*--- ------------        --------------  ----------  ------------------  ---*/
/*--- OutsideDegrees_C_B  -40.0 .. 87.5    0.5        CAN message         ---*/
/*--- Degrees_C_W         -40.0 .. 150.75  0.046875   Table Lookups       ---*/
/*--- Degrees_C_Base      -24K  .. 24K     0.75       Calculations        ---*/
/*--- Degrees_C_BUpTo215  -40.0 .. 215     1          Coolant Temperature ---*/
/*--- Degrees_C_B         -40.0 .. 150.75  0.75       Coolant Temperature ---*/
/*--- Degrees_Filtered    -40.0 .. 150.75  0.75/256   Coolant Temperature ---*/
/*--- HotDegreeC            0.0 .. 255.0   1          Hybrid Temperature  ---*/
/*---------------------------------------------------------------------------*/

typedef CARDINAL                                              DegreesC_HiRes_W;
#define Prec_DegreesC_HiRes_W                                        (1.0 / 16)
#define Min_DegreesC_HiRes_W                                          (-2048.0)
#define Max_DegreesC_HiRes_W \
                         (65535 * Prec_DegreesC_HiRes_W + Min_DegreesC_HiRes_W)

typedef LONGCARD                                              DegreesC_HiRes_L;
#define Prec_DegreesC_HiRes_L                              (1.0 / (16 * 65536))
#define Min_DegreesC_HiRes_L                                          (-2048.0)
#define Max_DegreesC_HiRes_L \
                         (65535 * Prec_DegreesC_HiRes_L + Min_DegreesC_HiRes_L)

typedef CARDINAL                                    DegreesC_HiRes_W_NonBiased;
#define Prec_DegreesC_HiRes_W_NonBiased                              (1.0 / 16)
#define Min_DegreesC_HiRes_W_NonBiased                                    (0.0)
#define Max_DegreesC_HiRes_W_NonBiased \
                                      (65535 * Prec_DegreesC_HiRes_W_NonBiased)

typedef CARDINAL                                            OutsideDegrees_C_W;
#define Prec_OutsideDegrees_C_W                                       (1.0 / 8)
#define Min_OutsideDegrees_C_W                                          (-40.0)
#define Max_OutsideDegrees_C_W \
                     (65535 * Prec_OutsideDegrees_C_W + Min_OutsideDegrees_C_W)

typedef SHORTCARD                                           OutsideDegrees_C_B;
#define Prec_OutsideDegrees_C_B                                       (1.0 / 2)
#define Min_OutsideDegrees_C_B                                          (-40.0)
#define Max_OutsideDegrees_C_B \
                       (255 * Prec_OutsideDegrees_C_B + Min_OutsideDegrees_C_B)

typedef SHORTCARD                                                  Degrees_C_B;
#define Prec_Degrees_C_B                                          (192.0 / 256)
#define Min_Degrees_C_B                                                 (-40.0)
#define Max_Degrees_C_B              (255 * Prec_Degrees_C_B + Min_Degrees_C_B)
/*      CALDEF
*|      types.Degrees_C_B
*|      {
*|         : kind = fixed;
*|         : precision = (0.750000);
*|         : range = (-40.500000) TO (150.750000);
*|         : biased;
*|      }
*/

typedef SHORTCARD                                           Degrees_C_BUpTo215;
#define Prec_Degrees_C_BUpTo215                                           (1.0)
#define Min_Degrees_C_BUpTo215                                          (-40.0)
#define Max_Degrees_C_BUpTo215       (255 * Prec_Degrees_C_B + Min_Degrees_C_B)

typedef CARDINAL                                                   Degrees_K_W;
#define Prec_Degrees_K_W                                            (1.0 / 128)
#define Min_Degrees_K_W                                                   (0.0)
#define Max_Degrees_K_W                                   (65535.0 * 1.0 / 128)

/*---------------------------------------------------------------------------*/
/*--- WARNING!!! The Precision of DegreesCBDelta MUST be the same as for  ---*/
/*--- Degrees_C_B and the DegreesCBDelta min MUST be null for correct     ---*/
/*--- use in the fixed point functions for type and delta of that type.   ---*/
/*---------------------------------------------------------------------------*/
typedef SHORTCARD                                               DegreesCBDelta;
#define Prec_DegreesCBDelta                                       (192.0 / 256)
#define Min_DegreesCBDelta                                                (0.0)
#define Max_DegreesCBDelta                             (255 * Prec_Degrees_C_B)

typedef CARDINAL                                                Degrees_C_Base;
#define Prec_Degrees_C_Base                                       (192.0 / 256)
#define Min_Degrees_C_Base                                           (-24576.0)
#define Max_Degrees_C_Base                                           (24575.25)

typedef CARDINAL                                                   Degrees_C_W;
#define Prec_Degrees_C_W                                           (12.0 / 256)
#define Min_Degrees_C_W                                                 (-40.0)
#define Max_Degrees_C_W            (65535 * Prec_Degrees_C_W + Min_Degrees_C_W)

typedef CARDINAL                                            Degrees_C_Filtered;
#define Prec_Degrees_C_Filtered                                 (192.0 / 65536)
#define Min_Degrees_C_Filtered                                          (-40.0)
#define Max_Degrees_C_Filtered \
                     (65535 * Prec_Degrees_C_Filtered + Min_Degrees_C_Filtered)

typedef CARDINAL                                       Degrees_C_FilteredDelta;
#define Prec_Degrees_C_FilteredDelta                  (Prec_Degrees_C_Filtered)
#define Min_Degrees_C_FilteredDelta                                       (0.0)
#define Max_Degrees_C_FilteredDelta      (65535 * Prec_Degrees_C_FilteredDelta)

typedef SHORTCARD                                                   HotDegreeC;
#define Prec_HotDegreeC                                                   (1.0)
#define Min_HotDegreeC                                                    (0.0)
#define Max_HotDegreeC                 (255 * Prec_HotDegreeC + Min_HotDegreeC)

/*---  Axis Enumerations for Temperature Types  ---*/

#define Degrees_C_m40to128By12_Steps                                       (15)
/*      CALDEF INFORMATION
*|      t_types.Degrees_C_m40to128By12_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Degrees_C";
*|         : table = (-40 TO 128 BY 12);
*|      }
*/

#define Degrees_C_m40to120By20_Steps                                       (9)
/*      CALDEF INFORMATION
*|      t_types.Degrees_C_m40to120By20_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Degrees_C";
*|         : table = (-40 TO 120 BY 20);
*|      }
*/

#define Deg_C_m40to152by12_Steps                                           (17)
/*      CALDEF
*|      types.Deg_C_m40to152by12_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Deg C";
*|         : table = (-40 TO 152 BY 12);
*|      }
*/
#define Deg_C_m40to104by12_Steps                                           (13)
/*      CALDEF
*|      types.Deg_C_m40to104by12_Steps
*|      {
*|       :kind = define_annotation;
*|       :units = "Deg C";
*|       :table = (-40 TO 104 BY 12);
*|      }
*/
#define Deg_C_m40to116by12_Steps                                           (14)
/*      CALDEF
*|      types.Deg_C_m40to116by12_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Deg_C";
*|         : table = (-40 TO 116 BY 12);
*|      }
*/
#define Deg_C_m40to128by24_Steps                                            (8)
/*      CALDEF
*|      types.Deg_C_m40to128by24_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Deg_C";
*|         : table = (-40 TO 128 BY 24);
*|      }
*/
#define Deg_C_m28to116by12_Steps                                           (13)
/*      CALDEF      */
#define Deg_C_m28to116by48_Steps                                            (4)
/*      CALDEF      */
#define Deg_C_m28to68by24_Steps                                             (5)
/*      CALDEF      */
#define Deg_C_m28to56by12_Steps                                             (8)
/*      CALDEF      */
#define Deg_C_m28to80by12_Steps                                            (10)
/*      CALDEF      */
#define Deg_C_m28to44by12_Steps                                             (7)
/*      CALDEF      */
#define Deg_C_m16to92by36_Steps                                             (4)
/*      CALDEF      */
#define Deg_C_m16to68by12_Steps                                             (8)
/*      CALDEF      */
#define Deg_C_m4to44by12_Steps                                              (5)
/*      CALDEF      */
#define Deg_C_m40to44by12_Steps                                             (8)
/*      CALDEF      */
#define Deg_C_0to256by16_Steps                                             (17)
/*      CALDEF
*|      types.Deg_C_0to256by16_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Deg_C";
*|         : table = (0 TO 256 BY 16);
*|      }
*/
#define Deg_C_0to96by16_Steps                                               (7)
/*      CALDEF      */
#define Deg_C_8to56by8_Steps                                                (7)
/*      CALDEF      */
#define Deg_C_20to116by8_Steps                                             (13)
/*      CALDEF      */
#define Deg_C_0to80by8_Steps                                               (11)

#define Deg_C_0to100by20_Steps                                              (6)
/*      CALDEF
*|      types.Deg_C_0to100by20_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Deg_C";
*|         : table = (0 TO 100 BY 20);
*|      }
*/

/*---  RFactors for Temperature Types  ---*/

#define RFactor_DegreesC_HiRes_L_DegreesC_HiRes_W                (16.0 * 65536)
#define RFactor_DegreesC_HiRes_W_DegreesC_HiRes_L                (16.0 * 65536)
#define RFactor_DegreesC_HiRes_W_DegreesC_HiRes_W_NonBiased              (16.0)
#define RFactor_DegreesC_HiRes_W_NonBiased_DegreesC_HiRes_W              (16.0)
#define RFactor_OutsideDegrees_C_B_Degrees_C_B                              (4)
#define RFactor_Degrees_C_B_Degrees_C_BUpTo215                              (4)
#define RFactor_Degrees_C_W_Degrees_C_BUpTo215                             (64)
#define RFactor_Degrees_C_B_Degrees_C_W                                  (64.0)
#define RFactor_Degrees_C_B_Degrees_C_Filtered                     (1024.0 / 3)
#define RFactor_Degrees_C_Filtered_Degrees_C_B                     (1024.0 / 3)
#define RFactor_Degrees_C_B_Degrees_C_FilteredDelta                (1024.0 / 3)
#define RFactor_Degrees_C_FilteredDelta_Degrees_C_Filtered       (1024.0 / 3.0)
#define RFactor_Degrees_C_Filtered_Degrees_C_FilteredDelta       (1024.0 / 3.0)
#define RFactor_Degrees_C_W_Degrees_C_B                                  (64.0)
#define RFactor_Degrees_C_B_Degrees_C_Base                            (4.0 / 3)
#define RFactor_Degrees_C_Base_Degrees_C_B                            (4.0 / 3)
#define RFactor_Degrees_C_Filtered_Degrees_C_B                     (1024.0 / 3)
#define RFactor_Degrees_C_Filtered_Degrees_C_W                     (1024.0 / 3)
#define RFactor_DegreesCBDelta_Degrees_C_B                    (1.0/(192/256.0))
#define RFactor_DegreesCBDelta_Degrees_C_W                       (256.0 / 12.0)
#define RFactor_Degrees_C_B_DegreesCBDelta                    (1.0/(192/256.0))
#define RFactor_DegreesCBDelta_Degrees_C_W                       (256.0 / 12.0)
#define RFactor_DegreesCBDelta_Degrees_C_FilteredDelta             (1024.0 / 3)
#define RFactor_Degrees_C_FilteredDelta_DegreesCBDelta             (1024.0 / 3)
#define RFactor_Degrees_C_W_Degrees_C_FilteredDelta                (1024.0 / 3)
#define RFactor_Degrees_C_FilteredDelta_Degrees_C_W                (1024.0 / 3)

/*--------------------------------------------*/
/*---                                      ---*/
/*---   Temperature Variation Fixed Types  ---*/
/*---                                      ---*/
/*--------------------------------------------*/

/*---------------------------------------------------------*/
/*--- Type                 Range (DegC/sec)  Precision  ---*/
/*--- ------------         --------------   ----------  ---*/
/*--- Degrees_C_Per_Sec     0 .. 0.373535   0.0014648   ---*/
/*---------------------------------------------------------*/

typedef SHORTCARD                                            Degrees_C_Per_Sec;
#define Prec_Degrees_C_Per_Sec                              (192.0 / 256 / 512)
#define Min_Degrees_C_Per_Sec                                             (0.0)
#define Max_Degrees_C_Per_Sec                         (255 * 192.0 / 256 / 512)

/*----------------------------*/
/*---                      ---*/
/*---   Angle Fixed Types  ---*/
/*---                      ---*/
/*----------------------------*/
#if 0
typedef CARDINAL                                             CrankAngleInDeg_W;
#define Prec_CrankAngleInDeg_W                                     (90.0 / 256)
#define Min_CrankAngleInDeg_W                                             (0.0)
#define Max_CrankAngleInDeg_W                              (65535 * 90.0 / 256)
#endif

typedef SHORTCARD                                            CrankAngleInDeg_B;
#define Prec_CrankAngleInDeg_B                                     (90.0 / 256)
#define Min_CrankAngleInDeg_B                                             (0.0)
#define Max_CrankAngleInDeg_B                                (255 * 90.0 / 256)

typedef CARDINAL                                 CrankAngleInDeg_Plus_Fraction;
#define Prec_CrankAngleInDeg_Plus_Fraction                       (90.0 / 65536)
#define Min_CrankAngleInDeg_Plus_Fraction                                 (0.0)
#define Max_CrankAngleInDeg_Plus_Fraction                (65535 * 90.0 / 65536)

typedef SHORTCARD                                           SparkAdvance_Deg_B;
#define Prec_SparkAdvance_Deg_B                                    (90.0 / 256)
#define Min_SparkAdvance_Deg_B                                          (-22.5)
#define Max_SparkAdvance_Deg_B                      (255.0 * 90.0 / 256 - 22.5)
/*      CALDEF
*|      types.SparkAdvance_Deg_B
*|      {
*|         : kind = fixed;
*|         : precision = (0.351562);
*|         : range = (-64 * 0.351562) TO (191 * 0.351562);
*|         : biased;
*|      }
*/

typedef CARDINAL                                            SparkAdvance_Deg_W;
#define Prec_SparkAdvance_Deg_W                       (Prec_SparkAdvance_Deg_B)
#define Min_SparkAdvance_Deg_W               (-32768 * Prec_SparkAdvance_Deg_W)
#define Max_SparkAdvance_Deg_W \
                     (65535 * Prec_SparkAdvance_Deg_W + Min_SparkAdvance_Deg_W)

typedef SHORTCARD                                     SparkAdvance_Delta_Deg_B;
#define Prec_SparkAdvance_Delta_Deg_B                 (Prec_SparkAdvance_Deg_B)
#define Min_SparkAdvance_Delta_Deg_B                                      (0.0)
#define Max_SparkAdvance_Delta_Deg_B    (255.0 * Prec_SparkAdvance_Delta_Deg_B)

typedef CARDINAL                                SparkAdvance_Deg_Plus_Fraction;
#define Prec_SparkAdvance_Deg_Plus_Fraction                      (90.0 / 65536)
#define Min_SparkAdvance_Deg_Plus_Fraction                              (-22.5)
#define Max_SparkAdvance_Deg_Plus_Fraction      (65535.0 * 90.0 / 65536 - 22.5)

typedef CARDINAL                          SparkAdvance_Delta_Deg_Plus_Fraction;
#define Prec_SparkAdvance_Delta_Deg_Plus_Fraction \
                                          (Prec_SparkAdvance_Deg_Plus_Fraction)
#define Min_SparkAdvance_Delta_Deg_Plus_Fraction                          (0.0)
#define Max_SparkAdvance_Delta_Deg_Plus_Fraction \
                          (65535.0 * Prec_SparkAdvance_Delta_Deg_Plus_Fraction)

typedef CARDINAL                                        CrankAngleInDegSignedW;
#define Prec_CrankAngleInDegSignedW                                (90.0 / 256)
#define Min_CrankAngleInDegSignedW                        (-32768 * 90.0 / 256)
#define Max_CrankAngleInDegSignedW                         (32767 * 90.0 / 256)

typedef SHORTCARD                                       CrankAngleInDegSignedB;
#define Prec_CrankAngleInDegSignedB                                (90.0 / 256)
#define Min_CrankAngleInDegSignedB                          (-128 * 90.0 / 256)
#define Max_CrankAngleInDegSignedB                           (127 * 90.0 / 256)

typedef SHORTCARD                                        KnockSparkRetard_Type;
#define Prec_KnockSparkRetard_Type                    (Prec_SparkAdvance_Deg_B)
#define Min_KnockSparkRetard_Type                                         (0.0)
#define Max_KnockSparkRetard_Type            (255 * Prec_KnockSparkRetard_Type)

/*---  Axis Enumerations for Angle Types  ---*/

#define SpkRtd_0to40by4_Steps                                              (11)
/*      CALDEF      */

/*---  RFactors for Angle Types  ---*/

#define RFactor_CrankAngleInDegSignedB_CrankAngleInDeg_B \
                                                (1/Prec_CrankAngleInDegSignedB)
#define RFactor_SparkAdvance_Deg_B_SparkAdvance_Deg_Plus_Fraction \
                                                                 (65536.0 / 90)
#define RFactor_SparkAdvance_Deg_Plus_Fraction_SparkAdvance_Deg_B \
                                                                 (65536.0 / 90)
#define RFactor_SparkAdvance_Deg_B_SparkAdvance_Deg_W \
                                                    (1/Prec_SparkAdvance_Deg_B)
#define RFactor_SparkAdvance_Deg_W_SparkAdvance_Deg_B \
                                                    (1/Prec_SparkAdvance_Deg_B)
#define RFactor_SparkAdvance_Deg_W_SparkAdvance_Deg_Plus_Fraction \
                                                                 (65536.0 / 90)
#define RFactor_SparkAdvance_Deg_Plus_Fraction_SparkAdvance_Deg_W \
                                                                 (65536.0 / 90)
#define RFactor_CrankAngleInDeg_B_CrankAngleInDeg_W              (65536.0 / 90)
#define RFactor_CrankAngleInDeg_W_CrankAngleInDeg_B              (65536.0 / 90)
#define RFactor_CrankAngleInDeg_B_CrankAngleInDeg_Plus_Fraction  (65536.0 / 90)
#define RFactor_CrankAngleInDeg_W_CrankAngleInDeg_Plus_Fraction  (65536.0 / 90)
#define RFactor_SparkAdvance_Deg_B_CrankAngleInDeg_W             (65536.0 / 90)
#define RFactor_CrankAngleInDegSignedW_SparkAdvance_Deg_B        (256.0 / 90.0)
#define RFactor_SparkAdvance_Deg_B_CrankAngleInDegSignedW        (256.0 / 90.0)
#define RFactor_CrankAngleInDeg_W_CrankAngleInDegSignedW         (256.0 / 90.0)
#define RFactor_CrankAngleInDegSignedW_CrankAngleInDeg_W \
                             (RFactor_CrankAngleInDeg_W_CrankAngleInDegSignedW)

/*------------------------------*/
/*---                        ---*/
/*---   Volume Fixed Types   ---*/
/*---                        ---*/
/*------------------------------*/

/*--------------------------------------------------------------------*/
/*---  Type                        Range              Precision    ---*/
/*---  --------------------  -------------------     -----------   ---*/
/*---  Liter                      0.0  ..  99.6      0.390625      ---*/
/*---  Liters_W                   0.0   .. 15.9998   0.00024414    ---*/
/*---  MicroLiter                 0.0  ..  1024.0    0.015625      ---*/
/*---    The precision of the type MicroLiter has been choosen to  ---*/
/*---    correspond to the resolution of time resolution of the    ---*/
/*---    timer that controls the injector output                   ---*/
/*--------------------------------------------------------------------*/

typedef SHORTCARD                                                        Liter;
#define Prec_Liter                                                (100.0 / 256)
#define Min_Liter                                                         (0.0)
#define Max_Liter                                            (255 * Prec_Liter)

typedef CARDINAL                                                   LitersCAN_W;
#define Prec_LitersCAN_W                                          (1.0 / 32768)
#define Min_LitersCAN_W                                                   (0.0)
#define Max_LitersCAN_W                              (65535 * Prec_LitersCAN_W)

typedef CARDINAL                                                      Liters_W;
#define Prec_Liters_W                                              (1.0 / 4096)
#define Min_Liters_W                                                      (0.0)
#define Max_Liters_W                                       (65535 * 1.0 / 4096)

typedef CARDINAL                                                    MicroLiter;
#define Prec_MicroLiter                                              (1.0 / 64)
#define Min_MicroLiter                                                    (0.0)
#define Max_MicroLiter                                (65535 * Prec_MicroLiter)

typedef LONGCARD                                               MicroLiter_Base;
#define Prec_MicroLiter_Base                                         (1.0 / 64)
#define Min_MicroLiter_Base                                               (0.0)
#define Max_MicroLiter_Base                    (4294967295.0 * Prec_MicroLiter)

typedef SHORTCARD                                              Liter_Per_Min_B;
#define Prec_Liter_Per_Min_B                                              (0.1)
#define Min_Liter_Per_Min_B                                               (0.0)
#define Max_Liter_Per_Min_B                        (255 * Prec_Liter_Per_Min_B)

typedef CARDINAL                                               Liter_Per_Min_W;
#define Prec_Liter_Per_Min_W                                              (0.1)
#define Min_Liter_Per_Min_W                                               (0.0)
#define Max_Liter_Per_Min_W                      (65535 * Prec_Liter_Per_Min_W)

/*---  RFactors for Volume Types  ---*/

#define RFactor_Liter_Per_Min_B_Liter_Per_Min_W                          (10.0)
#define RFactor_Liter_Per_Min_W_Liter_Per_Min_B                          (10.0)
#define RFactor_MicroLiter_MicroLiter_Base                               (64.0)
#define RFactor_MicroLiter_Base_MicroLiter                               (64.0)
#define RFactor_MicroLiter_Base_LitersCAN_W                           (32768.0)

/*------------------------------*/
/*---                        ---*/
/*---   Mass Fixed Types     ---*/
/*---                        ---*/
/*------------------------------*/

/*--------------------------------------------------------------------*/
/*---  Type                        Range              Precision    ---*/
/*---  --------------------  -------------------     -----------   ---*/
/*---  Grams_Signed_L    -32768.0  .. 32767.99998    0.0000122588  ---*/
/*---  Grams_W_Base           0.0  .. 65535.99998    0.0000152588  ---*/
/*---  Grams_W                0.0  .. 0.999984741    0.0000152588  ---*/
/*---  Grams_Signed_W        -0.5  .. 0.499984741    0.0000152588  ---*/
/*---  Grams_B                0.0  .. 0.99609375     0.00390625    ---*/
/*--------------------------------------------------------------------*/

typedef LONGCARD                                                Grams_Signed_L;
#define Prec_Grams_Signed_L                                       (1.0 / 65536)
#define Min_Grams_Signed_L                                           (-32768.0)
#define Max_Grams_Signed_L \
                      (4294967295.0 * Prec_Grams_Signed_L + Min_Grams_Signed_L)

typedef LONGCARD                                                  Grams_W_Base;
#define Prec_Grams_W_Base                                         (1.0 / 65536)
#define Min_Grams_W_Base                                                  (0.0)
#define Max_Grams_W_Base                             (4294967295 * 1.0 / 65536)

typedef CARDINAL                                                       Grams_W;
#define Prec_Grams_W                                              (1.0 / 65536)
#define Min_Grams_W                                                       (0.0)
#define Max_Grams_W                                       (65535 * 1.0 / 65536)

typedef CARDINAL                                                    Grams_O2_W;
#define Prec_Grams_O2_W                                          (1.0 / 4096.0)
#define Min_Grams_O2_W                                                    (0.0)
#define Max_Grams_O2_W                                (65535 * Prec_Grams_O2_W)

typedef CARDINAL                                                Grams_Signed_W;
#define Prec_Grams_Signed_W                                      (Prec_Grams_W)
#define Min_Grams_Signed_W                       (-32768 * Prec_Grams_Signed_W)
#define Max_Grams_Signed_W   (65535 * Prec_Grams_Signed_W + Min_Grams_Signed_W)

typedef SHORTCARD                                                      Grams_B;
#define Prec_Grams_B                                                (1.0 / 256)
#define Min_Grams_B                                                       (0.0)
#define Max_Grams_B                                           (255 * 1.0 / 256)

typedef CARDINAL                                               Grams_0to255g_W;
#define Prec_Grams_0to255g_W                                        (1.0 / 256)
#define Min_Grams_0to255g_W                                               (0.0)
#define Max_Grams_0to255g_W                    (65535.0 * Prec_Grams_0to255g_W)
/*      CALDEF
*|      types.Grams_0to255g_W
*|      {
*|         : kind = fixed;
*|         : precision = (1.0 / 256);
*|         : range = (0.000000) TO (65535 / 256);
*|      }
*/

typedef LONGCARD                                               Grams_0to65Kg_L;
#define Prec_Grams_0to65Kg_L                                      (1.0 / 65536)
#define Min_Grams_0to65Kg_L                                               (0.0)
#define Max_Grams_0to65Kg_L               (4294967295.0 * Prec_Grams_0to65Kg_L)

typedef SHORTCARD                                   MilligramsToGramsRatioType;
#define Prec_MilligramsToGramsRatioType                            (1.0 / 1000)
#define Min_MilligramsToGramsRatioType                                    (0.0)
#define Max_MilligramsToGramsRatioType                       (255 * 1.0 / 1000)

typedef LONGCARD                                           Milligrams_Signed_L;
#define Prec_Milligrams_Signed_L                                  (1.0 / 32768)
#define Min_Milligrams_Signed_L                                      (-32000.0)
#define Max_Milligrams_Signed_L                (4294967295.0 / 32768 - 32000.0)

typedef LONGCARD                                                  Milligrams_L;
#define Prec_Milligrams_L                                         (1.0 / 32768)
#define Min_Milligrams_L                                                  (0.0)
#define Max_Milligrams_L                                 (4294967295.0 / 32768)

/*---  Axis Enumerations for Mass Types  ---*/

#define MilliGrams_0to250by31p25_Steps                                      (9)
/*      CALDEF      */

/*---  RFactors for Mass Types  ---*/

#define RFactor_Grams_W_Base_Grams_W                                  (65536.0)
#define RFactor_Grams_W_Grams_W_Base                                  (65536.0)
#define RFactor_Grams_W_Grams_B                                       (65536.0)
#define RFactor_Grams_B_Grams_W                                       (65536.0)
#define RFactor_Grams_W_Grams_Signed_L                                (65536.0)
#define RFactor_Grams_Signed_L_Grams_W                                (65536.0)
#define RFactor_Grams_W_Grams_Signed_W                                (65536.0)
#define RFactor_Grams_Signed_W_Grams_W                                (65536.0)
#define RFactor_Grams_W_Base_Grams_Signed_W                           (65536.0)
#define RFactor_Grams_Signed_W_Grams_W_Base                           (65536.0)
#define RFactor_Grams_0to255g_W_Grams_0to65Kg_L                       (65536.0)
#define RFactor_Grams_0to65Kg_L_Grams_0to255g_W                       (65536.0)

/*--------------------------------*/
/*---                          ---*/
/*---   Mass Flow Fixed Types  ---*/
/*---                          ---*/
/*--------------------------------*/

/*-------------------------------------------------------------------------*/
/*---  Type                                Range            Precision    ---*/
/*---  ------------------------   -----------------------  ------------  ---*/
/*---  GramsPerSecond_Signed           -64.0 .. 191.996    0.003906250   ---*/
/*---  GramsPerSecond_Signed_L        -128.0 .. 16777087.9 0.003906250   ---*/
/*---  Grams_Per_Second_Signed_L  -8388608.0 .. 8388607.9  0.003906250   ---*/
/*---  Grams_Per_Second_Base             0.0 .. 16777216   0.003906250   ---*/
/*---  Grams_Per_Second_W                0.0 .. 256.0      0.003906250   ---*/
/*---  Grams_Per_Second_B                0.0 .. 256.0      1.0           ---*/
/*---  Seconds_Per_Gram                  0.0 .. 2.0        0.000030517   ---*/
/*--------------------------------------------------------------------------*/

typedef LONGCARD                                     Grams_Per_Second_Signed_L;
#define Prec_Grams_Per_Second_Signed_L                              (1.0 / 256)
#define Min_Grams_Per_Second_Signed_L                                (-8388608)
#define Max_Grams_Per_Second_Signed_L (4294967295.0 * \
                Prec_Grams_Per_Second_Signed_L + Min_Grams_Per_Second_Signed_L)

typedef LONGCARD                                         Grams_Per_Second_Base;
#define Prec_Grams_Per_Second_Base                                  (1.0 / 256)
#define Min_Grams_Per_Second_Base                                         (0.0)
#define Max_Grams_Per_Second_Base                      (4294967295 * 1.0 / 256)

typedef CARDINAL                                            Grams_Per_Second_W;
#define Prec_Grams_Per_Second_W                                     (1.0 / 128)
#define Min_Grams_Per_Second_W                                            (0.0)
#define Max_Grams_Per_Second_W                              (65535 * 1.0 / 128)
/*      CALDEF
*|      types.Grams_Per_Second_W
*|      {
*|         : kind = fixed;
*|         : precision = (0.0078125);
*|         : range = (0.000000) TO (65535 * 0.0078125);
*|      }
*/

typedef SHORTCARD                                           Grams_Per_Second_B;
#define Prec_Grams_Per_Second_B                                           (1.0)
#define Min_Grams_Per_Second_B                                            (0.0)
#define Max_Grams_Per_Second_B                                      (255 * 1.0)

typedef CARDINAL                                              Seconds_Per_Gram;
#define Prec_Seconds_Per_Gram                                     (1.0 / 32768)
#define Min_Seconds_Per_Gram                                              (0.0)
#define Max_Seconds_Per_Gram                              (65535 * 1.0 / 32768)

typedef CARDINAL                                         GramsPerSecond_Signed;
#define Prec_GramsPerSecond_Signed                                  (1.0 / 256)
#define Min_GramsPerSecond_Signed                                       (-64.0)
#define Max_GramsPerSecond_Signed                        (65535.0 / 256 - 64.0)

typedef LONGCARD                                       GramsPerSecond_Signed_L;
#define Prec_GramsPerSecond_Signed_L                                (1.0 / 256)
#define Min_GramsPerSecond_Signed_L                                    (-128.0)
#define Max_GramsPerSecond_Signed_L                (4294967295.0 / 256 - 128.0)

/*---  Axis Enumerations for Mass Flow Types  ---*/

#define gmsec_0to6p25by0p78125_Steps                                        (9)
#define gmsec_0to16by8_Steps                                                (3)
#define gmsec_0to64by4_Steps                                               (17)
#define gmsec_0to64by16_Steps                                               (5)
#define gmsec_0to76by4_Steps                                               (20)
#define gmsec_0to80by8_Steps                                               (11)
#define gmsec_0to96by16_Steps                                               (7)
#define gmsec_0to96by4_Steps                                               (25)
#define gmsec_0to128by8_Steps                                              (17)
/*      CALDEF
*|      types.gmsec_0to128by8_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "gm/sec";
*|         : table = (0 TO 128 BY 8);
*|      }
*/
#define gmsec_0to128by4_Steps                                              (33)
#define gmsec_0to256by25p6_Steps                                           (11)
#define gmsec_0to256by16_Steps                                             (17)
#define gmsec_0to1p5by0p125_Steps                                          (13)

/*---  RFactors for Mass Flow Types  ---*/

#define RFactor_GramsPerSecond_Signed_GramsPerSecond_Signed_L           (256.0)
#define RFactor_GramsPerSecond_Signed_L_GramsPerSecond_Signed           (256.0)
#define RFactor_Grams_Per_Second_Signed_L_Grams_Per_Second_W            (256.0)
#define RFactor_GramsPerSecond_Signed_Grams_Per_Second_W                (256.0)
#define RFactor_Grams_Per_Second_W_GramsPerSecond_Signed                (256.0)
#define RFactor_Grams_Per_Second_W_Grams_Per_Second_Signed_L            (256.0)
#define RFactor_Grams_Per_Second_W_Grams_Per_Second_B                   (256.0)
#define RFactor_Grams_Per_Second_B_Grams_Per_Second_W                   (256.0)
#define RFactor_Grams_Per_Second_W_Grams_Per_Second_Base                (256.0)
#define RFactor_Grams_Per_Second_Base_Grams_Per_Second_W                (256.0)
#define RFactor_GramsPerSecond_Signed_Milliseconds_W                  (32768.0)
#define RFactor_Milligrams_Signed_L_Milligrams_L                      (32768.0)
#define RFactor_Milligrams_L_Milligrams_Signed_L                      (32768.0)

/*-----------------------------*/
/*---                       ---*/
/*--- Converter Temperature ---*/
/*---                       ---*/
/*-----------------------------*/

typedef SHORTCARD                                          DegreeConvTempBType;
#define Prec_DegreeConvTempBType                                          (4.0)
#define Min_DegreeConvTempBType                                         (200.0)
#define Max_DegreeConvTempBType \
                     (255 * Prec_DegreeConvTempBType + Min_DegreeConvTempBType)

typedef CARDINAL                                        DegreeConvTempFiltType;
#define Prec_DegreeConvTempFiltType            (Prec_DegreeConvTempBType / 256)
#define Min_DegreeConvTempFiltType                                      (200.0)
#define Max_DegreeConvTempFiltType \
             (65535 * Prec_DegreeConvTempFiltType + Min_DegreeConvTempFiltType)

typedef SHORTCARD                                     DegreeConvTempFiltType_B;
#define Prec_DegreeConvTempFiltType_B                (Prec_DegreeConvTempBType)
#define Min_DegreeConvTempFiltType_B                                    (200.0)
#define Max_DegreeConvTempFiltType_B \
           (255 * Prec_DegreeConvTempFiltType_B + Min_DegreeConvTempFiltType_B)

/*---  Axis Enumerations for Converter Temp  ---*/

#define ConvDeg_400to1000by100Steps                                         (7)

/*---  RFactors for Converter Temp  ---*/

#define RFactor_DegreeConvTempFiltType_DegreeConvTempFiltType_B \
                                                (1/Prec_DegreeConvTempFiltType)

/*-----------------------------*/
/*---                       ---*/
/*---  Lamdba definition    ---*/
/*---                       ---*/
/*-----------------------------*/

typedef CARDINAL                                                 Lambda_0to8_W;
#define Prec_Lambda_0to8_W                                         (1 / 8192.0)
#define Min_Lambda_0to8_W                                                 (0.0)
#define Max_Lambda_0to8_W                        (65535.0 * Prec_Lambda_0to8_W)

/*--------------------------------*/
/*---                          ---*/
/*---   O2 Sensor Fixed Types  ---*/
/*---                          ---*/
/*--------------------------------*/

typedef Every_8th_Loop_Sec_B                                O2_Diag_Period_Sec;
#define Prec_O2_Diag_Period_Sec                     (Prec_Every_8th_Loop_Sec_B)
#define Min_O2_Diag_Period_Sec                       (Min_Every_8th_Loop_Sec_B)
#define Max_O2_Diag_Period_Sec                       (Max_Every_8th_Loop_Sec_B)

/*--------------------------*/
/*---                    ---*/
/*---   TPS Fixed Types  ---*/
/*---                    ---*/
/*--------------------------*/

typedef Every_2nd_Loop_Sec_B                                    TPS_Period_Sec;
#define Prec_TPS_Period_Sec                         (Prec_Every_2nd_Loop_Sec_B)
#define Min_TPS_Period_Sec                           (Min_Every_2nd_Loop_Sec_B)
#define Max_TPS_Period_Sec                           (Max_Every_2nd_Loop_Sec_B)

typedef Every_8th_Loop_Sec_B                                 TPS_Diag_High_Sec;
#define Prec_TPS_Diag_High_Sec                      (Prec_Every_8th_Loop_Sec_B)
#define Min_TPS_Diag_High_Sec                        (Min_Every_8th_Loop_Sec_B)
#define Max_TPS_Diag_High_Sec                        (Max_Every_8th_Loop_Sec_B)

/*--------------------------*/
/*---                    ---*/
/*---   MAP Fixed Types  ---*/
/*---                    ---*/
/*--------------------------*/

typedef Every_8th_Loop_Sec_B                                 MAP_Diag_High_Sec;
#define Prec_MAP_Diag_High_Sec                      (Prec_Every_8th_Loop_Sec_B)
#define Min_MAP_Diag_High_Sec                        (Min_Every_8th_Loop_Sec_B)
#define Max_MAP_Diag_High_Sec                        (Max_Every_8th_Loop_Sec_B)

typedef Every_Loop_Sec_B                                        MAP_Period_Sec;
#define Prec_MAP_Period_Sec                             (Prec_Every_Loop_Sec_B)
#define Min_MAP_Period_Sec                               (Min_Every_Loop_Sec_B)
#define Max_MAP_Period_Sec                               (Max_Every_Loop_Sec_B)

/*------------------------------------*/
/*---                              ---*/
/*---   Vehicle Speed Fixed Types  ---*/
/*---                              ---*/
/*------------------------------------*/

typedef Every_2nd_Loop_Sec_B                         Vehicle_Speed_Update_Rate;
#define Prec_Vehicle_Speed_Update_Rate              (Prec_Every_2nd_Loop_Sec_B)
#define Min_Vehicle_Speed_Update_Rate                (Min_Every_2nd_Loop_Sec_B)
#define Max_Vehicle_Speed_Update_Rate                (Max_Every_2nd_Loop_Sec_B)

typedef Every_8th_Loop_Sec_B                                        VSSDiagSec;
#define Prec_VSSDiagSec                             (Prec_Every_8th_Loop_Sec_B)
#define Min_VSSDiagSec                               (Min_Every_8th_Loop_Sec_B)
#define Max_VSSDiagSec                               (Max_Every_8th_Loop_Sec_B)

/*------------------------------------*/
/*---                              ---*/
/*---   Transmission Fixed Types   ---*/
/*---                              ---*/
/*------------------------------------*/

typedef Every_2nd_Loop_Sec_B                                  Auto_Update_Rate;
#define Prec_Auto_Update_Rate                       (Prec_Every_2nd_Loop_Sec_B)
#define Min_Auto_Update_Rate                         (Min_Every_2nd_Loop_Sec_B)
#define Max_Auto_Update_Rate                         (Max_Every_2nd_Loop_Sec_B)

typedef CARDINAL                                       RPM_To_Speed_Ratio_Base;
#define Prec_RPM_To_Speed_Ratio_Base             (Prec_RPM_Hi_Res_W / Prec_KPH)
#define Min_RPM_To_Speed_Ratio_Base                                       (0.0)
#define Max_RPM_To_Speed_Ratio_Base      (65535 * Prec_RPM_To_Speed_Ratio_Base)

typedef SHORTCARD                                           RPM_To_Speed_Ratio;
#define Prec_RPM_To_Speed_Ratio                  (Prec_RPM_To_Speed_Ratio_Base)
#define Min_RPM_To_Speed_Ratio                                            (0.0)
#define Max_RPM_To_Speed_Ratio                  (255 * Prec_RPM_To_Speed_Ratio)

/*------------------------------------*/
/*---                              ---*/
/*---   Engine Speed Fixed Types   ---*/
/*---                              ---*/
/*------------------------------------*/

typedef Every_2nd_Loop_Sec_B                               HiResRPM_Period_Sec;
#define Prec_HiResRPM_Period_Sec                    (Prec_Every_2nd_Loop_Sec_B)
#define Min_HiResRPM_Period_Sec                      (Min_Every_2nd_Loop_Sec_B)
#define Max_HiResRPM_Period_Sec                      (Max_Every_2nd_Loop_Sec_B)

/*---------------------------------------------------*/
/*---                                             ---*/
/*---   Ignition and system voltage Fixed Types   ---*/
/*---                                             ---*/
/*---------------------------------------------------*/

typedef Every_8th_Loop_Sec_B                                   IgnitionDiagSec;
#define Prec_IgnitionDiagSec                        (Prec_Every_8th_Loop_Sec_B)
#define Min_IgnitionDiagSec                          (Min_Every_8th_Loop_Sec_B)
#define Max_IgnitionDiagSec                          (Max_Every_8th_Loop_Sec_B)

typedef Every_1Sec_Loop_Sec_W                             SystemVoltageDiagSec;
#define Prec_SystemVoltageDiagSec                  (Prec_Every_1Sec_Loop_Sec_W)
#define Min_SystemVoltageDiagSec                    (Min_Every_1Sec_Loop_Sec_W)
#define Max_SystemVoltageDiagSec                    (Max_Every_1Sec_Loop_Sec_W)

/*--------------------------------------*/
/*---                                ---*/
/*---   58X Diagnostic Fixed Types   ---*/
/*---                                ---*/
/*--------------------------------------*/

typedef Every_8th_Loop_Sec_B                                        Diag58XSec;
#define Prec_Diag58XSec                             (Prec_Every_8th_Loop_Sec_B)
#define Min_Diag58XSec                               (Min_Every_8th_Loop_Sec_B)
#define Max_Diag58XSec                               (Max_Every_8th_Loop_Sec_B)

/*--------------------------------------*/
/*---                                ---*/
/*---   LEGR Flow Test Fixed Types   ---*/
/*---                                ---*/
/*--------------------------------------*/

typedef Every_8th_Loop_Sec_B                                       LegrTestSec;
#define Prec_LegrTestSec                            (Prec_Every_8th_Loop_Sec_B)
#define Min_LegrTestSec                              (Min_Every_8th_Loop_Sec_B)
#define Max_LegrTestSec                              (Max_Every_8th_Loop_Sec_B)

/*---------------------------------------------*/
/*---                                       ---*/
/*---   EGR Min Position Learn Fixed Type   ---*/
/*---                                       ---*/
/*---------------------------------------------*/

typedef Every_2nd_Loop_Sec_B                                DesEgrPosTimerType;
#define Prec_DesEgrPosTimerType                     (Prec_Every_2nd_Loop_Sec_B)
#define Min_DesEgrPosTimerType                       (Min_Every_2nd_Loop_Sec_B)
#define Max_DesEgrPosTimerType                       (Max_Every_2nd_Loop_Sec_B)

/*---------------------------------*/
/*---                           ---*/
/*---        Other types        ---*/
/*---                           ---*/
/*---------------------------------*/

#define AddressType                                                    LONGCARD

/*---------------------------------*/
/*---                           ---*/
/*---    Transmission types     ---*/
/*---                           ---*/
/*---------------------------------*/

typedef
  enum
    {Manual, Mta, Auto}
  Trans_Types;

typedef
  enum
    {MtCar,AtCar}
  AtMtType;
/*      CALDEF INFORMATION
*|      types.AtMtAnnotation
*|      {
*|         : kind = define_annotation;
*|         : units = "Transmission";
*|         : table = ("Manual");
*|      }
*/

#define SelectAtMtCal(cal)                                         (cal ## _MT)
#define GetAtMtCar()                                                    (MtCar)

/*--------------------------------------------*/
/*---                                      ---*/
/*--- 58x functions / Spark delivery types ---*/
/*---                                      ---*/
/*--------------------------------------------*/

typedef
  enum                   /*--- HEI = High Ignition Voltage Switch ---*/
    {HEI, DIS}           /*--- DIS = Direct Ignition System       ---*/
  Ignition_System_Type;

/*----------------------------------*/
/*---                            ---*/
/*---   Air Conditioning types   ---*/
/*---                            ---*/
/*----------------------------------*/

#define AcNoTorqueLimitation                                                (0)
#define AcTorqueGradientLimitation                                          (1)
#define AcSlowShutdownRequest                                               (2)
#define AcFastShutdownRequest                                               (3)
typedef SHORTCARD                                ClutchlessAcStrokeRequestType;

/*---------------------------------*/
/*---                           ---*/
/*---   CAN Application types   ---*/
/*---                           ---*/
/*---------------------------------*/

typedef SHORTCARD                                               CanIdleRpmResB;
#define Prec_CanIdleRpmResB                                              (10.0)
#define Min_CanIdleRpmResB                                                (0.0)
#define Max_CanIdleRpmResB   (255.0 * Prec_CanIdleRpmResB + Min_CanIdleRpmResB)

typedef CARDINAL                                                  CanRpmHiResW;
#define Prec_CanRpmHiResW                                                 (1.0)
#define Min_CanRpmHiResW                                                  (0.0)
#define Max_CanRpmHiResW       (65535.0 * Prec_CanRpmHiResW + Min_CanRpmHiResW)

typedef CARDINAL                                                       CanRpmW;
#define Prec_CanRpmW                                                      (1.0)
#define Min_CanRpmW                                                       (0.0)
#define Max_CanRpmW                      (65535.0 * Prec_CanRpmW + Min_CanRpmW)

typedef SHORTCARD                                CanRpmHiRes_to_KPH_B_Filtered;
/*--- 60 mn = 1H, 100000 cm = 1 Km (distance per wheel rotation is in cm) ---*/
/*--- Prec_CanRpmHiRes_to_KPH_B_Filtered type is defined such as the conversion
      from DistInCmPerWheelRotType to get the conversion factor for RPM to KPH
      is not needed. the conversion factor is the same SHORTCARD value than
      the DistInCmPerWheelRot value ---*/
#define Prec_CanRpmHiRes_to_KPH_B_Filtered                      (60.0 / 100000)
#define Min_CanRpmHiRes_to_KPH_B_Filtered                                 (0.0)
#define Max_CanRpmHiRes_to_KPH_B_Filtered \
                                   (255.0 * Prec_CanRpmHiRes_to_KPH_B_Filtered)

typedef CARDINAL                                                       CanKPHW;
#define Prec_CanKPHW                                                (1.0 / 128)
#define Min_CanKPHW                                                       (0.0)
#define Max_CanKPHW                                    (65535.0 * Prec_CanKPHW)

typedef SHORTCARD                                    NewtonMeterAcCompressor_B;
#define Prec_NewtonMeterAcCompressor_B                            (100.0 / 255)
#define Min_NewtonMeterAcCompressor_B                                     (0.0)
#define Max_NewtonMeterAcCompressor_B \
         (255 * Prec_NewtonMeterAcCompressor_B + Min_NewtonMeterAcCompressor_B)

typedef SHORTCARD                                   NmAcCompressorPerAirflow_B;
#define Prec_NmAcCompressorPerAirflow_B                           (100.0 / 255)
#define Min_NmAcCompressorPerAirflow_B                                    (0.0)
#define Max_NmAcCompressorPerAirflow_B \
      (255 * Prec_NmAcCompressorPerAirflow_B  + Min_NmAcCompressorPerAirflow_B)

typedef SHORTCARD                                        NewtonMeterCANPrec1_B;
#define Prec_NewtonMeterCANPrec1_B                                        (1.0)
#define Min_NewtonMeterCANPrec1_B                                       (-50.0)
#define Max_NewtonMeterCANPrec1_B                                       (205.0)

typedef SHORTCARD                                        NewtonMeterCANPrec2_B;
#define Prec_NewtonMeterCANPrec2_B                                        (2.0)
#define Min_NewtonMeterCANPrec2_B                                      (-100.0)
#define Max_NewtonMeterCANPrec2_B                                       (400.0)

typedef SHORTCARD                                                CanMicroLiter;
#define Prec_CanMicroLiter                                   (1000000.0/8196.0)
#define Min_CanMicroLiter                                                 (0.0)
#define Max_CanMicroLiter                                           (7995930.0)

/*--- the following definition is for the calculation of the Acceleration
      Gradient variable which is of a signed type. that's why no type is
      defined because it cannot be used with the current FixPoint
      arithmetic. Only the precision is defined for the calculation ---*/
#define Prec_AcceleratorGradient_Type                                 (1.0/128)

typedef SHORTCARD                                                 CanPercent_B;
#define Prec_CanPercent_B                                         (100.0 / 255)
#define Min_CanPercent_B                                                  (0.0)
#define Max_CanPercent_B                            (255.0 * Prec_CanPercent_B)

typedef SHORTCARD                                                  GearRatio_B;
#define Prec_GearRatio_B                                               (1 / 32)
#define Min_GearRatio_B                                                   (0.0)
#define Max_GearRatio_B                             (255.0 * Prec_CanPercent_B)

/*---  RFactors for CAN Application Types  ---*/

#define RFactor_CanIdleRpmResB_RPM_Med_Res_B                                (2)
#define RFactor_RPM_Med_Res_B_CanIdleRpmResB \
                                         (RFactor_CanIdleRpmResB_RPM_Med_Res_B)
#define RFactor_RPM_Hi_Res_W_CanRpmHiResW                                 (1.0)
#define RFactor_CanRpmHiResW_RPM_Hi_Res_W                                 (1.0)
#define RFactor_RPM_Med_Res_B_CanRpmHiResW                                (2.0)
#define RFactor_CanRpmHiResW_RPM_Med_Res_B                                (2.0)
#define RFactor_RPM_Hi_Res_W_CanRpmW                                      (1.0)
#define RFactor_CanRpmW_RPM_Hi_Res_W                                      (1.0)
#define RFactor_RPM_Med_Res_B_CanRpmW                                     (1.0)
#define RFactor_CanRpmW_RPM_Med_Res_B                                     (1.0)
#define RFactor_KPH_CanKPHW                                             (128.0)
#define RFactor_CanKPHW_KPH                               (RFactor_KPH_CanKPHW)
#define RFactor_KPH_B_Filtered_CanKPHW                                  (256.0)
#define RFactor_CanKPHW_KPH_B_Filtered         (RFactor_KPH_B_Filtered_CanKPHW)
#define RFactor_NewtonMeterAcCompressor_B_TNewtonMeterHires_W \
                                             (255.0 / Prec_TNewtonMeterHires_W)
#define RFactor_TNewtonMeterHires_W_NewtonMeterAcCompressor_B \
                        (RFactor_NewtonMeterAcCompressor_B_TNewtonMeterHires_W)
#define RFactor_Newton_Meter_B_NewtonMeterCANPrec1_B                      (1.0)
#define RFactor_NewtonMeterCANPrec1_B_Newton_Meter_B                      (1.0)
#define RFactor_Newton_Meter_W_NewtonMeterCANPrec1_B                    (128.0)
#define RFactor_NewtonMeterCANPrec1_B_Newton_Meter_W                    (128.0)
#define RFactor_Newton_Meter_B_NewtonMeterCANPrec2_B                      (1.0)
#define RFactor_NewtonMeterCANPrec2_B_Newton_Meter_B                      (1.0)
#define RFactor_Newton_Meter_W_NewtonMeterCANPrec2_B                    (128.0)
#define RFactor_NewtonMeterCANPrec2_B_Newton_Meter_W                    (128.0)
#define RFactor_NewtonMeterCANPrec1_B_NewtonMeterCANPrec2_B               (1.0)
#define RFactor_NewtonMeterCANPrec2_B_NewtonMeterCANPrec1_B               (1.0)
#define RFactor_MicroLiter_CanMicroLiter                                 (64.0)
#define RFactor_CanMicroLiter_MicroLiter                                 (64.0)
#define RFactor_CanPercent_B_Percent_BPrec1                             (255.0)
#define RFactor_Percent_BPrec1_CanPercent_B                             (255.0)

/*-----------------------------*/
/*---                       ---*/
/*---  Fuel delivery types  ---*/
/*---                       ---*/
/*-----------------------------*/

typedef SHORTCARD FuelTooth;

#define MinFuelTooth                                                        (3)
#define MaxFuelTooth                                                       (23)

#ifdef EFI_ASDF
typedef
  enum
    {DFCRANK, QFCRANK}
  CrankFuelMode;
#endif

/*------------------------------*/
/*---                        ---*/
/*---  Air/Fuel Ratio types  ---*/
/*---                        ---*/
/*------------------------------*/

typedef SHORTCARD                                           AirFuel_Ratio_Type;
#define Prec_AirFuel_Ratio_Type                                           (0.1)
#define Min_AirFuel_Ratio_Type                                            (0.0)
#define Max_AirFuel_Ratio_Type                  (255 * Prec_AirFuel_Ratio_Type)
/*      CALDEF INFORMATION
*|      types.AirFuel_Ratio_Type
*|      {
*|         : kind = fixed;
*|         : precision = (0.100000);
*|         : range = (0.000000) TO (25.500000);
*|      }
*/

typedef CARDINAL                                 AirFuel_Ratio_Plus_Fract_Type;
#define Prec_AirFuel_Ratio_Plus_Fract_Type    (Prec_AirFuel_Ratio_Type / 256.0)
#define Min_AirFuel_Ratio_Plus_Fract_Type                                 (0.0)
#define Max_AirFuel_Ratio_Plus_Fract_Type \
                                   (65535 * Prec_AirFuel_Ratio_Plus_Fract_Type)

/*---  Axis Enumerations for Air/Fuel Ratio Types  ---*/

#define AFRatio_9p8to15p4by0p4_steps                                       (15)
/*      CALDEF
*|      types.AFRatio_9p8to15p4by0p4_steps
*|      {
*|         : kind = define_annotation;
*|         : units = "A/F";
*|         : table = (9.8 TO 15.4 BY 0.4);
*|      }
*/

/*-----------------------------------*/
/*---                             ---*/
/*---  Output slewing state type  ---*/
/*---                             ---*/
/*-----------------------------------*/

typedef
  enum
    {
    ssNoSlew               = 0,
    ssAbsoluteSlew         = 1,
    ssPositiveRelativeSlew = 2,
    ssNegativeRelativeSlew = 3
    }
  SlewStateType;

/*-----------------------------*/
/*---                       ---*/
/*---  Car related types    ---*/
/*---                       ---*/
/*-----------------------------*/

typedef SHORTCARD                                                   Kilogram_B;
#define Prec_Kilogram_B                                                   (8.0)
#define Min_Kilogram_B                                                    (0.0)
#define Max_Kilogram_B                                (Prec_Kilogram_B * 255.0)
/*      CALDEF
*|      types.Kilogram_B
*|      {
*|         : kind = fixed;
*|         : precision = (8.00000);
*|         : range = (0.000000) TO (255 * 8.00000);
*|      }
*/

typedef SHORTCARD                                              Meter_Med_Res_B;
#define Prec_Meter_Med_Res_B                                      (1.0 / 512.0)
#define Min_Meter_Med_Res_B                                               (0.0)
#define Max_Meter_Med_Res_B                      (Prec_Meter_Med_Res_B * 255.0)

/* end of t_types.h */

typedef
  enum
    {
    DC_NORMAL,
    DC_LIMIT_PERFORMANCE,
    DC_FORCED_IDLE
    } Driver_Command_Mode_Type;

typedef
  enum
    {
    TA_NORMAL,
    TA_POWER_MANAGE,
    TA_STALL,
    TA_STALL_BY_WDG
    } Throttle_Actuation_Mode_Type;

/* #include "iac_type.h" */ /* for Airflow_W                         */
typedef Percent_Plus_Fraction                                        Airflow_W;
#define Prec_Airflow_W                                          (100.0 / 65536)
#define Min_Airflow_W                                                     (0.0)
#define Max_Airflow_W                                   (65535 * 100.0 / 65536)

/* #include "t_types.h"  */ /* for table axis types                  */
#define AF_Ratio_1to20p5By0p75_Steps                                       (27)
/*      CALDEF INFORMATION
*|      t_types.AF_Ratio_1to20p5By0p75_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "A/F ratio";
*|         : table = (1 TO 20.5 BY 0.75);
*|      }
*/

#define SparkAdvance_Deg_W_0to50by5_Steps                                  (11)
/*      CALDEF INFORMATION
*|      t_types.SparkAdvance_Deg_W_0to50by5_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Deg Crank";
*|         : table = (0 TO 50 BY 5);
*|      }
*/

#define Seconds_0to1By0p125_Steps                                           (9)
/*      CALDEF INFORMATION
*|      t_types.Seconds_0to1By0p125_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "Seconds";
*|         : table = (0.0 TO 1 BY 0.125);
*|      }
*/

#if XeSYST_AIR_INDUCTION  ==  CeSYST_NATURAL_ASPIRATED
#define GramsPerCyl_GPCLoad_Steps                                          (13)
#else
#define GramsPerCyl_GPCLoad_Steps                                          (25)
#endif
/*      CALDEF INFORMATION
*|      t_types.GramsPerCyl_GPCLoad_Steps
*|      {
*|         : kind = define_annotation;
*|         : units = "gm/cyl";
*/
#if XeSYST_AIR_INDUCTION  ==  CeSYST_NATURAL_ASPIRATED
/*
*|         : table = ( 0 TO 120 BY 10);
*/
#else
/*
*|         : table = ( 0 TO 240 BY 10);
*/
#endif
/*
*|      }
*/

#define CBT_RPM_W_17            (17)
/*  CALDS information
*|t_types.CBT_RPM_W_17{
*|    :kind = define_annotation;
*|    :units = "Rpm";
*|    :table =
*|    ("Rpm_0","Rpm_1","Rpm_2","Rpm_3","Rpm_4","Rpm_5","Rpm_6","Rpm_7","Rpm_8","Rpm_9","Rpm_10","Rpm_11","Rpm_12","Rpm_13","Rpm_14","Rpm_15","Rpm_16");
*|    }
*/

#define CBT_RPM_W_19            (19)
/*  CALDS information
*|t_types.CBT_RPM_W_19{
*|    :kind = define_annotation;
*|    :units = "Rpm";
*|    :table =
*|    ("Rpm_0","Rpm_1","Rpm_2","Rpm_3","Rpm_4","Rpm_5","Rpm_6","Rpm_7","Rpm_8","Rpm_9","Rpm_10","Rpm_11","Rpm_12","Rpm_13","Rpm_14","Rpm_15","Rpm_16","Rpm_17","Rpm_18");
*|    }
*/

#define CBT_RPM_W_20            (20)
/*  CALDS information
*|t_types.CBT_RPM_W_20{
*|    :kind = define_annotation;
*|    :units = "Rpm";
*|    :table =
*|    ("Rpm_0","Rpm_1","Rpm_2","Rpm_3","Rpm_4","Rpm_5","Rpm_6","Rpm_7","Rpm_8","Rpm_9","Rpm_10","Rpm_11","Rpm_12","Rpm_13","Rpm_14","Rpm_15","Rpm_16","Rpm_17","Rpm_18","Rpm_19");
*|    }
*/

#define CBT_RPM_W_21              (21)
/*  CALDS information
*|t_types.CBT_RPM_W_21{
*|    :kind = define_annotation;
*|    :units = "Rpm";
*|    :table =
*|    ("Rpm0","Rpm1","Rpm2","Rpm3","Rpm4","Rpm5","Rpm6","Rpm7","Rpm8","Rpm9","Rpm10","Rpm11","Rpm12","Rpm13","Rpm14","Rpm15","Rpm16","Rpm17","Rpm18","Rpm19","Rpm20");
*|    }
*/

#define CBT_RPM_W_S_19            (19)
/*  CALDS information
*|t_types.CBT_RPM_W_S_19{
*|    :kind = define_annotation;
*|    :units = "Rpm";
*|    :table =
*|    ("Rpm_0","Rpm_1","Rpm_2","Rpm_3","Rpm_4","Rpm_5","Rpm_6","Rpm_7","Rpm_8","Rpm_9","Rpm_10","Rpm_11","Rpm_12","Rpm_13","Rpm_14","Rpm_15","Rpm_16","Rpm_17","Rpm_18");
*|    }
*/

#define CBT_Grams_W_11            (11)
/*  CALDS information
*|t_types.CBT_Grams_W_11{
*|    :kind = define_annotation;
*|    :units = "gr";
*|    :table =
*|    ("gr_0","gr_1","gr_2","gr_3","gr_4","gr_5","gr_6","gr_7","gr_8","gr_9","gr_10");
*|    }
*/

#define CBT_Newton_Meter_B_8     (8)
/*  CALDS information
*|t_types.CBT_Newton_Meter_B_8{
*|    :kind = define_annotation;
*|    :units = "Nm";
*|    :table =
*|    ("Nm_0", "Nm_1", "Nm_2", "Nm_3", "Nm_4", "Nm_5", "Nm_6", "Nm_7");
*|    }
*/

#define CBT_Percent_W_21            (21)
/*  CALDS information
*|t_types.CBT_Percent_W_21{
*|    :kind = define_annotation;
*|    :units = "%";
*|    :table =
*|    ("Pct_0","Pct_1","Pct_2","Pct_3","Pct_4","Pct_5","Pct_6","Pct_7","Pct_8","Pct_9","Pct_10","Pct_11","Pct_12","Pct_13","Pct_14","Pct_15","Pct_16","Pct_17","Pct_18","Pct_19","Pct_20");
*|    }
*/

/* end of t_types.h */

/* #include "fl_types.h"  */ /* for AirFuel_Ratio_Type               */

/* #include "v_transm.h"  */ /* for GearStates                       */
typedef
  enum
    {
    Unknown,
    First,
    Second,
    Third,
    Fourth,
    Fifth,
    Sixth,
    Reverse,
    Neutral
    } GearStates;

#define GearStates_                                                         (9)
/*      CALDEF INFORMATION
*|      types.GearStates_
*|      {
*|         : kind = define_annotation;
*|         : units = "Gear";
*|         : table = ("Unknown", "1st", "2nd", "3rd", "4th", "5th",
*|                    "6th", "Reverse (MTA/AT)", "Neutral (MTA/AT)");
*|      }
*/

#define VIO_TransRatioTypeNumber                                            (8)
/*      CALDEF INFORMATION
*|      types.TransRatioTypeAnnotation
*|      {
*|         : kind = define_annotation;
*|         : units = "TransRatioType";
*|         : table = ("MT Type 00","MT Type 01","MT Type 10",
*|                    "MT Type 11","MTA Type 00","MTA Type 01",
*|                    "MTA Type 10","MTA Type 11");
*|      }
*/

/* #include "h_int.h"  */ /* for StatusRegisterType                  */
typedef LONGCARD StatusRegisterType;

/* #include "cfg_app.h"  */ /* for PhysicalCylinder                  */
typedef
  enum
    {
    CylD = 0,
    CylA = 1,
    CylB = 2,
    CylC = 3,
    NUMBER_OF_CYLINDERS,
    AllCyl
    } CylinderType;

typedef
  enum
    {
    Cyl1 = 0,
    Cyl2 = 1,
    Cyl3 = 2,
    Cyl4 = 3,
    NUMBEROFCYLINDERS = 4,
    CylAll = 5
    } PhysicalCylinder;

/* #include "veh_cfg.h"  */ /* for CcAC_NbOfAcTypes                  */

#if CLUTCHLESS_AC_ON == CbSUBS_ON

#if CcAC_NbOfAcTypes == 2
typedef
  enum
    {
    CcAC_Conventionnal,
    CcAC_Clutchless,
    CcAC_NoAcProgrammed
    } TeAC_AcTypesType;

/* CALDEF INFORMATION
*| veh_cal.TeAC_AcTypesType
*|   {
*|   : kind = define_annotation;
*|   : units = "Type AC";
*|   : table = ("Conventional", "Clutchless");
*|   }
*/
#else
typedef
  enum
    {
    CcAC_Conventionnal,
    CcAC_Clutchless
    } TeAC_AcTypesType;
/*      CALDEF INFORMATION
*|      veh_cal.TeAC_AcTypesType
*|      {
*|         : kind = define_annotation;
*|         : units = "Type AC";
*|         : table = ("Conventional");
*|      }
*/
#endif

typedef
  enum
    {
    CcAC_ClutchlessAC,
    CcAC_NoClutchlessAcProg
    } TeAC_ClutchlessAcTypesType;

/* CALDEF INFORMATION
*| veh_cal.TeAC_ClutchLessAcTypesType
*|   {
*|   : kind = define_annotation;
*|   : units = "Type Clutchless AC";
*|   : table = ("Clutchless");
*|   }
*/

#else /* ! CLUTCHLESS_AC_ON */

typedef
  enum
    {
    CcAC_Conventionnal,
    CcAC_NoAcProgrammed
    } TeAC_AcTypesType;

/*      CALDEF INFORMATION
*|      veh_cal.TeAC_AcTypesType
*|      {
*|         : kind = define_annotation;
*|         : units = "Type AC";
*|         : table = ("Conventional");
*|      }
*/
typedef
  enum
    {
    CcAC_NoClutchlessAcProg
    } TeAC_ClutchlessAcTypesType;

#endif /* CLUTCHLESS_AC_ON */

#define NbOfFanSpeed                                                        (4)
/*      CALDEF INFORMATION
*|      fan_cal.FanSpeed
*|      {
*|         : kind = define_annotation;
*|         : units = "Fan Speed";
*|         : table = (1, 2, 3, 4);
*|      }
*/

#define AtMtSelect                                                          (1)

typedef enum {dtcTorqueSupervisionRationality} DtcNamesType;

/*********************************************************************/
/*  TCB Global (Generic/Application) Data Type Include File          */
/*********************************************************************/
/* #include "t_gentypes.h"                                           */
// #include "idleptyp.h"

/*********************************************************************/
/*  TCB Data Type parameters for use with TCL Fixed Point Math       */
/*  (in alphabetical order!)                                         */
/*********************************************************************/

/*      typedef FIXED_UW_11                                           T_AFR; */
#define Prec_T_AFR                                         (1.0 / (1UL << S_AFR))
#define Min_T_AFR                                                         (0.0)
#define Max_T_AFR                                          (65535 * Prec_T_AFR)
#define RFactor_T_AFR_AirFuel_Ratio_Type                              (10240.0)
#define RFactor_AirFuel_Ratio_Type_T_AFR                              (10240.0)
#define RFactor_AirFuel_Ratio_Plus_Fract_Type_T_AFR                   (10240.0)
#define RFactor_T_AFR_AirFuel_Ratio_Plus_Fract_Type                   (10240.0)

/*      typedef FIXED_SW_07                                        T_ANGLEa; */
#define Prec_T_ANGLEa                                   (1.0 / (1UL << S_ANGLEa))
#define Min_T_ANGLEa                                                      (0.0)
#define Max_T_ANGLEa                                    (32767 * Prec_T_ANGLEa)
#define RFactor_SparkAdvance_Deg_B_T_ANGLEa                             (128.0)
#define RFactor_T_ANGLEa_SparkAdvance_Deg_B                             (128.0)

/*      typedef FIXED_SW_07                                        T_DEG_Ca; */
#define Prec_T_DEG_Ca                                   (1.0 / (1UL << S_DEG_Ca))
#define Min_T_DEG_Ca                                                      (0.0)
#define Max_T_DEG_Ca                                    (32767 * Prec_T_DEG_Ca)
#define RFactor_T_DEG_Ca_Degrees_C_W                                    (128.0)
#define RFactor_T_DEG_Ca_Degrees_C_B                                    (128.0)
#define RFactor_Degrees_C_B_T_DEG_Ca                                    (128.0)

/*      typedef FIXED_SW_04                                        T_DEG_Cb; */
#define Prec_T_DEG_Cb                                   (1.0 / (1UL << S_DEG_Cb))
#define Min_T_DEG_Cb                                                      (0.0)
#define RFactor_T_DEG_Cb_DegreeConvTempFiltType                          (64.0)
#define RFactor_DegreeConvTempFiltType_T_DEG_Cb                          (64.0)

/*      typedef FIXED_UW_05                                        T_DEG_Kb; */
#define Prec_T_DEG_Kb                                   (1.0 / (1UL << S_DEG_Kb))
#define Min_T_DEG_Kb                                                      (0.0)
#define Max_T_DEG_Kb                                    (65535 * Prec_T_DEG_Kb)
#define RFactor_T_DEG_Kb_Degrees_C_W                                    (128.0)

/*      typedef FIXED_UW_15                                 T_GRAMS_CYL_0_2; */
#define Prec_T_GRAMS_CYL_0_2                     (1.0 / (1UL << S_GRAMS_CYL_0_2))
#define Min_T_GRAMS_CYL_0_2                                               (0.0)
#define Max_T_GRAMS_CYL_0_2                      (65535 * Prec_T_GRAMS_CYL_0_2)
#define RFactor_T_GRAMS_CYL_0_2_Grams_W                               (65536.0)

/*      typedef FIXED_UW_07                                 T_GRAMS_PER_SEC; */
#define Prec_T_GRAMS_PER_SEC                     (1.0 / (1UL << S_GRAMS_PER_SEC))
#define Min_T_GRAMS_PER_SEC                                               (0.0)
#define RFactor_T_GRAMS_PER_SEC_Grams_Per_Second_W                    (32768.0)
#define RFactor_Grams_Per_Second_W_T_GRAMS_PER_SEC                    (32768.0)

/*      typedef FIXED_UW_07                                         T_KPAf; */
#define Prec_T_KPAf                                       (1.0 / (1UL << S_KPAf))
#define Min_T_KPAf                                                       (0.0)
#define Max_T_KPAf                                        (65535 * Prec_T_KPAf)
#define RFactor_T_KPAf_kPa_Base                                      (271104.0)


/*      typedef FIXED_UW_08                                T_GRAMS_PER_SECb; */
#define Prec_T_GRAMS_PER_SECb                   (1.0 / (1UL << S_GRAMS_PER_SECb))
#define Min_T_GRAMS_PER_SECb                                              (0.0)
#define Max_T_GRAMS_PER_SECb                    (65535 * Prec_T_GRAMS_PER_SECb)
#define RFactor_T_GRAMS_PER_SECb_Grams_Per_Second_W                     (256.0)
#define RFactor_Grams_Per_Second_W_T_GRAMS_PER_SECb                     (256.0)

/*      typedef FIXED_UW_08                                          T_KPAa; */
#define Prec_T_KPAa                                       (1.0 / (1UL << S_KPAa))
#define Min_T_KPAa                                                        (0.0)
#define Max_T_KPAa                                        (65535 * Prec_T_KPAa)
#define RFactor_T_KPAa_kPa_Base                                      (271104.0)
#define RFactor_T_KPAa_kPa_Plus_Fraction                            (2168832.0)
#define RFactor_T_KPAa_kPa_W                                            (256.0)
#define RFactor_T_KPAa_kPa_Boost_LoRes                                  (256.0)
#define RFactor_kPa_Boost_LoRes_T_KPAa                                  (256.0)
#define RFactor_kPa_W_T_KPAa                                            (256.0)

/*      typedef FIXED_SW_08                                  T_KPA_N128_128; */
#define Prec_T_KPA_0_128                             (1.0 / (1UL << S_KPA_0_128))
#define Min_T_KPA_0_128                                                   (0.0)
#define Max_T_KPA_0_128                              (65535 * Prec_T_KPA_0_128)
#define RFactor_T_KPA_0_128_kPa_Boost_LoRes                             (512.0)
#define RFactor_kPa_Boost_LoRes_T_KPA_0_128                             (512.0)

/*      typedef FIXED_UW_04                                          T_KPAb; */
#define Prec_T_KPAb                                       (1.0 / (1UL << S_KPAb))
#define Min_T_KPAb                                                        (0.0)
#define Max_T_KPAb                                        (65535 * Prec_T_KPAb)
#define RFactor_T_KPAb_kPa_IMEP_W                                       (16.0)
#define RFactor_kPa_IMEP_W_T_KPAb                                       (16.0)
#define RFactor_T_KPAb_Newton_Meter_W                                   (128.0)

/*      typedef FIXED_SW_03                                          T_KPAd; */
#define Prec_T_KPAd                                       (1.0 / (1UL << S_KPAd))
#define Min_T_KPAd                                                        (0.0)
#define Max_T_KPAd                                        (32767 * Prec_T_KPAd)
#define RFactor_T_KPAd_AcPresInKPa_Plus_Fraction                        (128.0)

/*      typedef FIXED_UW_07                                           T_KPH; */
#define Prec_T_KPH                                         (1.0 / (1UL << S_KPH))
#define Min_T_KPH                                                         (0.0)
#define Max_T_KPH                                          (65535 * Prec_T_KPH)
#define RFactor_T_KPH_KPH                                               (128.0)
#define RFactor_KPH_T_KPH                                               (128.0)

/*      typedef FIXED_UW_06                                   T_MILLIGRAMSb; */
#define Prec_T_MILLIGRAMSb                         (1.0 / (1UL << S_MILLIGRAMSb))
#define Min_T_MILLIGRAMSb                                                 (0.0)
#define Max_T_MILLIGRAMSb                          (65535 * Prec_T_MILLIGRAMSb)
#define RFactor_T_MILLIGRAMSb_Milligrams_1_64                            (64.0)
#define RFactor_Milligrams_1_64_T_MILLIGRAMSb                            (64.0)

/*      typedef FIXED_SW_04                                  T_NEWTON_METER; */
#define Prec_T_NEWTON_METER                       (1.0 / (1UL << S_NEWTON_METER))
#define Min_T_NEWTON_METER                                                (0.0)
#define Max_T_NEWTON_METER                        (32767 * Prec_T_NEWTON_METER)
#define RFactor_Newton_Meter_W_T_NEWTON_METER                           (128.0)
#define RFactor_T_NEWTON_METER_Newton_Meter_W                           (128.0)

/*      typedef FIXED_SW_05                       T_NEWTON_METER_N1024_1024; */
#define Prec_T_NEWTON_METER_N1024_1024                 (1.0/ (1 << S_NEWTON_METER_N1024_1024))
#define Min_T_NEWTON_METER_N1024_1024                                     (0.0)
#define Max_T_NEWTON_METER_N1024_1024                 (32767 * Prec_T_NEWTON_METER_N1024_1024)
#define RFactor_T_NEWTON_METER_N1024_1024_Newton_Meter_W                 (32.0)
#define RFactor_Newton_Meter_W_T_NEWTON_METER_N1024_1024                 (32.0)

/*      typedef FIXED_SW_07                                  T_NEWTON_METER_N256_256; */
#define Prec_T_NEWTON_METER_N256_256                       (1.0 / (1UL << S_NEWTON_METER_N256_256))
#define Min_T_NEWTON_METER_N256_256                                                (0.0)
#define Max_T_NEWTON_METER_N256_256                        (32767 * Prec_T_NEWTON_METER_N256_256)
#define RFactor_Newton_Meter_W_T_NEWTON_METER_N256_256                           (128.0)
#define RFactor_T_NEWTON_METER_N256_256_Newton_Meter_W                           (128.0)

/*      typedef FIXED_SL_18                                  T_NEWTON_METER_N8192_8192; */
#define Prec_T_NEWTON_METER_N8192_8192                     (1.0 / (1UL << S_NEWTON_METER_N8192_8192))
#define Min_T_NEWTON_METER_N8192_8192                                             (0.0)
#define Max_T_NEWTON_METER_N8192_8192                      (LongMax * Prec_T_NEWTON_METER_N8192_8192)
#define RFactor_Newton_Meter_W_T_NEWTON_METER_N8192_8192                        (262144L)
#define RFactor_T_NEWTON_METER_N8192_8192_Newton_Meter_W                        (262144L)

/*      typedef FIXED_UW_15                                      T_PERCENTa; */
#define Prec_T_PERCENTa                               (1.0 / (1UL << S_PERCENTa))
#define Min_T_PERCENTa                                                    (0.0)
#define Max_T_PERCENTa                                (65535 * Prec_T_PERCENTa)
#define RFactor_T_PERCENTa_ETC_Percent_Type                           (32768.0)
#define RFactor_ETC_Percent_Type_T_PERCENTa                           (32768.0)
#define RFactor_Percent_B_T_PERCENTa                                  (32768.0)
#define RFactor_T_PERCENTa_Percent_W                                  (32768.0)
#define RFactor_T_PERCENTa_Percent_Plus_Fraction                      (65536.0)
#define RFactor_Percent_Plus_Fraction_T_PERCENTa                      (65536.0)
#define RFactor_T_PERCENTa_Multiplier_0_to_1_W                        (65536.0)
#define RFactor_Multiplier_0_to_1_W_T_PERCENTa                        (65536.0)
#define RFactor_Multiplier_0_to_2_W_T_PERCENTa                        (32768.0)
#define RFactor_T_PERCENTa_Multiplier_0_to_2_W                        (32768.0)

/*      typedef FIXED_UW_15                                 T_PERCENT_MULTa; */
#define Prec_T_PERCENT_MULTa                     (1.0 / (1UL << S_PERCENT_MULTa))
#define Min_T_PERCENT_MULTa                                               (0.0)
#define Max_T_PERCENT_MULTa                      (65535 * Prec_T_PERCENT_MULTa)
#define RFactor_T_PERCENT_MULTa_ETC_Percent_Type                      (32768.0)
#define RFactor_ETC_Percent_Type_T_PERCENT_MULTa                      (32768.0)
#define RFactor_Percent_B_T_PERCENT_MULTa                             (32768.0)
#define RFactor_T_PERCENT_MULTa_Percent_W                             (32768.0)
#define RFactor_T_PERCENT_MULTa_Percent_Plus_Fraction                 (65536.0)
#define RFactor_Percent_Plus_Fraction_T_PERCENT_MULTa                 (65536.0)
#define RFactor_T_PERCENT_MULTa_Multiplier_0_to_1_W                   (65536.0)
#define RFactor_Multiplier_0_to_1_W_T_PERCENT_MULTa                   (65536.0)

/*      typedef FIXED_UW_16                                      T_PERCENTb; */
#define Prec_T_PERCENTb                               (1.0 / (1UL << S_PERCENTb))
#define Min_T_PERCENTb                                                    (0.0)
#define Max_T_PERCENTb                                (65535 * Prec_T_PERCENTb)

/*      typedef FIXED_UW_09                                      T_PERCENTh; */
#define Prec_T_PERCENTh                               (1.0 / (1UL << S_PERCENTh))
#define Min_T_PERCENTh                                                    (0.0)
#define Max_T_PERCENTh                                (65535 * Prec_T_PERCENTh)
#define RFactor_T_PERCENTh_ETC_Percent_Type                             (512.0)
#define RFactor_ETC_Percent_Type_T_PERCENTh                             (512.0)
#define RFactor_T_PERCENTh_Percent_B                                    (512.0)
#define RFactor_Percent_B_T_PERCENTh                                    (512.0)

/*      typedef FIXED_UW_10                            T_JOULE_PER_MILLIGRAM; */
#define Prec_T_JOULE_PER_MILLIGRAM          (1.0 / (1UL << S_JOULE_PER_MILLIGRAM))
#define Min_T_JOULE_PER_MILLIGRAM                                          (0.0)
#define Max_T_JOULE_PER_MILLIGRAM           (65535 * Prec_T_JOULE_PER_MILLIGRAM)
#define RFactor_T_JOULE_PER_MILLIGRAM_JoulePerMg_B                      (1024.0)
#define RFactor_JoulePerMg_B_T_JOULE_PER_MILLIGRAM                      (1024.0)

/*      typedef FIXED_UW_16                                     T_RATIO_0_1; */
#define Prec_T_RATIO_0_1                             (1.0 / (1UL << S_RATIO_0_1))
#define Min_T_RATIO_0_1                                                   (0.0)
#define Max_T_RATIO_0_1                              (65535 * Prec_T_RATIO_0_1)
#define RFactor_T_RATIO_0_1_Multiplier_0_to_1_W                       (65536.0)
#define RFactor_Multiplier_0_to_1_W_T_RATIO_0_1                       (65536.0)

/*      typedef FIXED_UW_16                                        T_FILTER; */
#define Prec_T_FILTER                                  (1.0 / (1UL << S_FILTER))
#define Min_T_FILTER                                                     (0.0)
#define Max_T_FILTER                                (65535 * Prec_T_RATIO_0_1)
#define RFactor_T_FILTER_Filter_Coefficient                          (65536.0)
#define RFactor_Filter_Coefficient_T_FILTER                          (65536.0)

/*      typedef FIXED_UW_15                                     T_RATIO_0_2; */
#define Prec_T_RATIO_0_2                             (1.0 / (1UL << S_RATIO_0_2))
#define Min_T_RATIO_0_2                                                   (0.0)
#define Max_T_RATIO_0_2                              (65535 * Prec_T_RATIO_0_2)
#define RFactor_T_RATIO_0_2_Multiplier_0_to_2_W                       (32768.0)
#define RFactor_Multiplier_0_to_2_W_T_RATIO_0_2                       (32768.0)
#define RFactor_T_RATIO_0_2_Lambda_0to8_W                             (32768.0)
#define RFactor_Lambda_0to8_W_T_RATIO_0_2                             (32768.0)
#define RFactor_T_RATIO_0_2_Multiplier_0_to_1p275_B                  (819200.0)
#define RFactor_Multiplier_0_to_1p275_B_T_RATIO_0_2                  (819200.0)

/*      typedef FIXED_UW_13                                     T_RATIO_0_8; */
#define Prec_T_RATIO_0_8                             (1.0 / (1UL << S_RATIO_0_8))
#define Min_T_RATIO_0_8                                                   (0.0)
#define Max_T_RATIO_0_8                              (65535 * Prec_T_RATIO_0_8)
#define RFactor_T_RATIO_0_8_Multiplier_0_to_4_W                       (16384.0)
#define RFactor_Multiplier_0_to_4_W_T_RATIO_0_8                       (16384.0)
#define RFactor_T_RATIO_0_8_Multiplier_0_to_8_W                       (8192.0)
#define RFactor_Multiplier_0_to_8_W_T_RATIO_0_8                       (8192.0)

/*      typedef FIXED_UW_12                                    T_RATIO_0_16; */
#define Prec_T_RATIO_0_16                           (1.0 / (1UL << S_RATIO_0_16))
#define Min_T_RATIO_0_16                                                  (0.0)
#define Max_T_RATIO_0_16                            (65535 * Prec_T_RATIO_0_16)
#define RFactor_T_RATIO_0_16_Multiplier_0_to_16_W                      (4096.0)
#define RFactor_Multiplier_0_to_16_W_T_RATIO_0_16                      (4096.0)

/*      typedef FIXED_UW_03                                          T_RPMa; */
#define Prec_T_RPMa                                       (1.0 / (1UL << S_RPMa))
#define Min_T_RPMa                                                        (0.0)
#define Max_T_RPMa                                        (65535 * Prec_T_RPMa)
#define RFactor_T_RPMa_RPM_W                                            (128.0)
#define RFactor_RPM_W_T_RPMa                                            (128.0)
#define RFactor_T_RPMa_RPM_Med_Res_B                                      (8.0)
#define RFactor_T_RPMa_RPM_Hi_Res_W                                       (8.0)

/*      typedef FIXED_SW_03                                     T_RPM_DIFFa; */
#define Prec_T_RPM_DIFFa                                 (1.0 / (1UL << S_RPM_DIFFa))
#define Min_T_RPM_DIFFa                                                   (0.0)
#define Max_T_RPM_DIFFa                                  (32767 * Prec_T_RPM_DIFFa)
#define RFactor_T_RPM_DIFFa_RPM_W_S                                     (128.0)

/*      typedef FIXED_UW_11                                         T_VOLTb; */
#define Prec_T_VOLTb                                     (1.0 / (1UL << S_VOLTb))
#define Min_T_VOLTb                                                       (0.0)
#define Max_T_VOLTb                                      (65535 * Prec_T_VOLTb)
#define RFactor_T_VOLTb_Volts_B                                        (2048.0)

/*      typedef FIXED_SW_06                                  T_KPA_N512_512; */
#define Prec_T_KPA_N512_512                       (1.0 / (1UL << S_KPA_N512_512))
#define Min_T_KPA_N512_512                                                (0.0)
#define Max_T_KPA_N512_512                        (32767 * Prec_T_KPA_N512_512)
#define RFactor_Newton_Meter_W_T_KPA_N512_512                           (128.0)
#define RFactor_T_KPA_N512_512_Newton_Meter_W                           (128.0)

/*      typedef FIXED_UW_02                                  T_RATIO_0_16384; */
#define Prec_T_RATIO_0_16384                                 (16384.0 / 65536.0)
#define Min_T_RATIO_0_16384                                                (0.0)
#define Max_T_RATIO_0_16384                                           (16383.75)

/*----------------------------------*/
/*---                            ---*/
/*---      General macros        ---*/
/*---                            ---*/
/*----------------------------------*/

/*--- Returns Min (OperandA + OperandB, HighLim)                   ---*/
/*--- even if the calculation overflows or HighLim is the top      ---*/
/*--- boundary of the type of operands.                            ---*/

#define AddHighLimit(OperandA,OperandB,HighLim) \
(((OperandA) < (HighLim - OperandB)) ? \
  (OperandA + OperandB) : \
  (HighLim))

/*--- Returns Max (OperandA - OperandB, LowLim)                    ---*/
/*--- even if the calculation underflows or LowLim is the bottom   ---*/
/*--- boundary of the type (0) of operands.                        ---*/

#define SubLowLimit(OperandA,OperandB,LowLim) \
(((OperandA) > (LowLim + OperandB)) ? \
  (OperandA - OperandB) : \
  (LowLim))

/*--- Returns Max (OperandA, OperandB)                 ---*/
/*--- OperandA, OperandB and the returned value are of ---*/
/*--- the same type (scalar of fixed point).           ---*/
/*--- This is mainly used for limitation of FixProduct ---*/
/*--- WARNING: to get best compiler results, try to    ---*/
/*--- pass variables to OperandA and Operand B, and    ---*/
/*--- not complexe expressions.                        ---*/
/*
 * Max function.
 */
#ifndef Max
#define Max(a,b) ( ( (a)>(b) )?(a):(b) )
#endif

/*--- Returns Min (OperandA, OperandB)                 ---*/
/*--- OperandA, OperandB and the returned value are of ---*/
/*--- the same type (scalar of fixed point).           ---*/
/*--- This is mainly used for limitation of FixProduct ---*/
/*--- WARNING: to get best compiler results, try to    ---*/
/*--- pass variables to OperandA and Operand B, and    ---*/
/*--- not complexe expressions.                        ---*/
/*
 * Min function.
 */
#ifndef Min
#define Min(a,b) ( ( (a)<(b) )?(a):(b) )
#endif

/*--- Returns |x-y| ---*/

#define SubAbs(x,y) (((x) >= (y)) ? ((x) - (y)) : ((y) - (x)))

/*--- Returns MSB of a word ---*/

#define Hi8Of16(x) ((SHORTCARD) ((x) >> 8))

/*--- Returns LSB of a word ---*/

#define Lo8Of16(x) ((SHORTCARD) (x))

/*--- Returns MSW of a long ---*/

#define Hi16Of32(x) ((CARDINAL) ((x) >> 16))

/*--- Returns LSW of a long ---*/

#define Lo16Of32(x) ((CARDINAL) (x))

/**********************************************************************/
/*** Converts low Nibble value (hex value) to Ascii (Upper case).   ***/
/**********************************************************************/
#define HexNibbleToAscii(Nibble) \
               (((Nibble) < 0x0A) ? ((Nibble) + '0') : ((Nibble) - 0x0A + 'A'))
#define ASCIINibbleToHex(Nibble) \
                (((Nibble) < 'A') ? ((Nibble) - '0') : ((Nibble) - 'A' + 0x0A))

/* !!! This MUST be at the end of types.h as long as the include  */
/* !!! of fix_math.h has not yet been added after types.h  in     */
/* !!! the include list of all the application files.             */
#include "lux_math.h"   /* for compatibility with t3000 files */

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     040506 woz 3990 Implemented changes required for TCL TORQ integration.
* 1.1   040903 kan 3990 Addition of corrections from Delphi-LUX
* 2.0   040922 kan 4456 Corrections fro 2004 hot trip:
*                        datatype definitions/CalDef for Grams_Per_Second_W
*                        #define Prec_Grams_Per_Second_W   (1.0 / 128)
*                        #define Max_Grams_Per_Second_W    (65535 * 1.0 / 128)
*                        CalDef for gmsec_0to128by8_Steps
*                        : table = (0 TO 128 BY 8);
* 2.1.1 050201 woz 4882 Added: RFactor_RPM_W_RPM_Hi_Res_W
*                              RFactor_RPM_Hi_Res_W_RPM_W
*                              RFactor_kPa_W_T_KPAa
* 2.1.2 050215 woz 4773 Added caldefs for Percent_0to100by10_Steps.
* 2.1.3 050315 aob 4989 Added T_NEWTON_METER_N256_256.
* 2.1.4 050727 kan 5271 Changed definition for VIO_TransRatioTypeNumber:
*                        WAS: (1)
*                        IS:  (8)
* tci_pt3#1.1.2
*       050119 PVD 4827 Turbo functionality changes
*       050404 PVD 4827 Added RFactor_kPa_Boost_LoRes_T_KPAa
*                       Deg_C_0to100by20_Steps
*                       Added RFactor_T_KPAa_kPa_Boost_LoRes
*                       Updated LONGINT , INTEGER definition.
* 5.0   051028 PVD -BM- Integration of Turbo into CORE
*           Merged 4 and 2.1.4
* 6.0   060228 PVD 5541 Added  T_KPAf and RFactor_T_KPAf_kPa_Base.
* 5.1.1 060330 at  -BM- Added #include "reuse.h" to fix build error
*
* ktc_pt1#6
*       060306 rmn 5546 C-TORQ: Increase range of IMEP variables to 0-4096 kPa
* ktc_pt1#7
*       060313 rmn 5547 Expand IMEP axis from 0-2400 to 0-3200kPa for all
*                       relevant calibrations.
* 5.1.2 060403 PVD -BM- Merged ktc_pt1#7 and 5.1.1
* 7.0   060404 caw -BM- Merge
* 8.0   060522 PVD 5639 Added RFactor_Newton_Meter_W_T_KPA_N512_512
*                             RFactor_T_KPA_N512_512_Newton_Meter_W
*                             GramsPerCyl_GPCLoad_Steps
* 7.1.1 060602 gps CIII Added CTORQ3 updates.
* 9     060828 cjk -BM- Merged 'lux_type.h-8' with 'lux_type.h-7.1.1'
* 8.1.1 060908 PVD 5834 Added RFactor_T_KPAb_Newton_Meter_W
* 8.1.2 061027 PVD 5747 Added RFactors for T_KPA_0_128 to kPa_Boost_LoRes
*           conversion and vice versa.
* 10    060901 cjk 5692 Design and Implement TORQ3 Spark Related Changes
*                       - Added RFactor_T_PERCENTa_Multiplier_0_to_1_W and
*                               RFactor_Multiplier_0_to_1_W_T_PERCENTa
*                               (LCD for 1/32768 and 1/65536 is 65536)
* 11    060921 cjk 5834 Incorporate TORQ3 Functionality
*                       - Added RFactor_T_NEWTON_METER_N1024_1024_Newton_Meter_W
*                               (LCD for 8/256 and 1/32 is 32)
*                       - Added RFactor_T_RPM_DIFFa_RPM_W_S
*                               (LCD for 1/8 and 50.0 / 256 is 128)
*                       - Add CALDEF for the following:
*                         > Multiplier_0_to_0p25_W
*                         > Multiplier_0_to_32
*                         > AcPresInKPa_Plus_Fraction
*                       - Add RFactor_T_RATIO_0_2_Lambda_0to8_W and
*                             RFactor_Lambda_0to8_W_T_RATIO_0_2
*                               (LCD for 1/32768 and 1/8192 is 32768)
* 12    061121 cjk CIII Correct precision for T_PERCENTa and T_PERCENTb
* 13    061201 cjk CIII Update types.RPM_W_S per Mexico
* 14    061204 cjk -BM- Merged 'lux_type.h-tci_pt3#8.1.2' with 'lux_type.h-13'
* 15    061213 cjk CIII Update RFactor_T_DEG_Ca_Degrees_C_B and
*                              RFactor_Degrees_C_B_T_DEG_Ca to be 128
*                             (LCD of 1/128 and 192/256 is 128)
*                       Correct caldef for Multiplier_0_to_0p25_W
* 16    070122 cjk CIII Move following configurations to torqfcfg.h
*                       - CcAC_NbOfAcTypes
*                       - CcAC_NbOfClutchLessAcTypes
* 16.1.1
*       070130 cjk 6135 Add T_PERCENT_MULTa and associated RFactors
* tci_pt3#8.2
*       070206 rmn 5878 Added RFactors for T_NEWTON_METER_N8192_8192
* tci_pt3#16.2
*       070213 rmn xxxx Merged 'lux_type.h-tci_pt3#8.2' with 'lux_type.h-16.1.1'.
* 16.2.1.1
*       071004 gps 5196 EXAC: Modifications for Cylinder De-Activation.
* tcp_pwt2#
*       070524 epm 5912 Added T_JOULE_PER_MILLIGRAM
*                             T_FILTER
*                             RFactor_T_JOULE_PER_MILLIGRAM_JoulePerMg_B
*                             RFactor_JoulePerMg_B_T_JOULE_PER_MILLIGRAM
*                             RFactor_T_FILTER_Filter_Coefficient
*                             RFactor_Filter_Coefficient_T_FILTER
*                             RFactor_T_RATIO_0_2_Multiplier_0_to_1p275_B
*                             RFactor_Multiplier_0_to_1p275_B_T_RATIO_0_2
*
* 16.3  070524 cjk 6247 Add RFactor_T_RATIO_0_16_Multiplier_0_to_16_W and
*                           RFactor_Multiplier_0_to_16_W_T_RATIO_0_16
*                           (LCD for 1/4096 and 1/4096 is 4096)
* tci_pt3#16.3
*       070510 raj  5903 Renamed Prec_T_GRAMS_CYL_0_1 to Prec_T_GRAMS_CYL_0_2,
*                                Min_T_GRAMS_CYL_0_1 to Min_T_GRAMS_CYL_0_2,
*                                Max_T_GRAMS_CYL_0_1 to Max_T_GRAMS_CYL_0_2,
*                            and RFactor_T_GRAMS_CYL_0_1_Grams_W  to
*                                RFactor_T_GRAMS_CYL_0_2_Grams_W
* 16.4  070607 cjk -BM- Merged 'lux_type.h-tci_pt3#16.3' with 'lux_type.h-16.3'
* 16.4.1.1
*       071023 cjk 6363 Torque 3 improvements
*                       - Add RFactor_T_RATIO_0_8_Multiplier_0_to_8_W and
*                           RFactor_Multiplier_0_to_8_W_T_RATIO_0_8
*                           (LCD for 1/8192 and 1/8192 is 8192)
* 16.3.1.2
*       071206 cjk -BM- Merged 'lux_type.h~16.4.1.1' with 'lux_type.h~16.3.1.1'
* 16.3.1.3
*       071212 cjk -BM- Correct range for types.Multiplier_0_to_32
* 16.3.1.4
*       080121 grb 5970 Flare Mode	Added
*                        RFactor_Multiplier_0_to_2_W_T_PERCENTa
*                        RFactor_T_PERCENTa_Multiplier_0_to_2_W
* tci_pt3#16.3.1.5
*       080320 MBA 6889 Added Degrees_C_m40to120By20_Steps
* 16.3.2
*       080128 ejb 6760 Added new Axis Enumerations for Temperature Types
*                       Deg_C_m40to152by12_Steps
* 16.7  08xxxx xxx -BM- Merged 'lux_type.h~16.3.1.4' with 'lux_type.h~16.3.2'
* 16.7.1.1
*       080812 cjk -BM- Merged 'lux_type.h~tci_pt3#16.3.1.5' with
*                              'lux_type.h~16.7'
* 16.8  080512 gps 5196 Merged 'lux_type.h~16.7' with 'lux_type.h~16.2.1.1'.
* 16.9  081020 gps -BM- Merged 'lux_type.h~16.8' with 'lux_type.h~16.7.1.1'.
* 16.9.1.1
*       080903  JP 6597 Added RPM_0to6400by1600_Steps caldef
* kok_pt2#16.9.1.1.1.1
*       090728 grb 7825 Added RFactor_Newton_Meter_W_T_NEWTON_METER_N1024_1024
* kok_pt2#16.9.1.2
*       090814 gps 6730 Changes associated with 3.9 to 2.5 ms base loop transition.
*                       Modified Every_Loop_Sec_Prec.
* kok_pt2#16.9.1.3
*       090930 gps 6730 Changes associated with 3.9 to 2.5 ms base loop transition.
*                       Modified RegularRtiPrescaler.
* kok_pt2#16.9.1.4
*       091118 gps -BM- Merged 'lux_type.h~kok_pt2#16.9.1.3'
*                        with 'lux_type.h~kok_pt2#16.9.1.1.1.1'.
* kok_pt2#16.9.1.4.1.1
*       110720 as  9635 Made changes to build using 16-bit COSMIC tool set
*
******************************************************************************/

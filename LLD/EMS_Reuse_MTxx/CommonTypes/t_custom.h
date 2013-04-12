#ifndef T_CUSTOM_H
#define T_CUSTOM_H
/******************************************************************************
 *
 * Filename:          t_custom.h
 *
 * Description:       This module contains the customized type definitions
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 1995-2003, Delphi Technologies, Inc.
 * Copyright 1995-2003 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#10/incl/t_custom.h/1 %
 * %date_created:  Wed Mar 19 09:46:38 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_base.h"
#include "t_fixed.h"
#include "t_scaled.h"
#include "t_tables.h"
#include "t_user.h"
#include "t_range.h"

/* Note: File t_fixed.h is originally written by GM powertrain. The following
   base data type definitions may be put in t_fixed.h when it is owned by FEMS
*/
/*****************************************************************************/
/* Signed Byte Fixed Point Types                                             */
/*****************************************************************************/
typedef SHORTINT FIXED_SB_01;
#define V_SB_01(val) (SHORTINT)((val)*2)
#define S_SB_01 1

/*****************************************************************************/
/* Unsigned Byte Fixed Point Types                                           */
/*****************************************************************************/
typedef BYTE FIXED_UB_00;
#define V_UB_00(val) (BYTE)(val)
#define S_UB_00 0

typedef BYTE FIXED_UB_01;
#define V_UB_01(val) (BYTE)((val)*2)
#define S_UB_01 1

typedef BYTE FIXED_UB_03;
#define V_UB_03(val) (BYTE)((val)*8)
#define S_UB_03 3

typedef BYTE FIXED_UB_04;
#define V_UB_04(val) (BYTE)((val)*16)
#define S_UB_04 4

typedef BYTE FIXED_UB_07;
#define V_UB_07(val) (BYTE)((val)*128)
#define S_UB_07 7

typedef BYTE FIXED_UB_08;
#define V_UB_08(val) (BYTE)((val)*256)
#define S_UB_08 8

/* WARNING: FIXED_SW_16 is not specified in the Fixed-Point Math requirement */
/* document (TL.07.0006.D11) as a valid type.  Use with caution!             */
/* Start PSE_TSE  */
/*  cubic cm */
/* power-of-two range: [0, 8191.875) */
typedef FIXED_UW_03     T_CM3;
#define V_CM3(val)      (WORD)((val)*8)
#define S_CM3           3

typedef FIXED_UW_00     T_CM3a;
#define V_CM3a(val)     (WORD)(val)
#define S_CM3a          0

/* power-of-two range: [-4096, 4096) */
typedef FIXED_SW_03 T_KPA_SECc;
#define V_KPA_SECc(val)  (INTEGER)((val)*8)
#define S_KPA_SECc 3

/* power-of-two range: [-128, 128) */
typedef FIXED_SW_08 T_KPA_SECd;
#define V_KPA_SECd(val)  (INTEGER)((val)*256)
#define S_KPA_SECd 8

/* power-of-two range: [-32, 32) */
typedef FIXED_SW_10 T_GRAMS_PER_SECd;
#define V_GRAMS_PER_SECd(val)  (INTEGER)((val)*1024)
#define S_GRAMS_PER_SECd 10

/* power-of-two range: [0, 64) */
typedef FIXED_UW_10 T_GRAMS_PER_SECc;
#define V_GRAMS_PER_SECc(val)  (WORD)((val)*1024)
#define S_GRAMS_PER_SECc 10

/* power-of-two range: [0, 16)  Res: 0.0625 */
typedef FIXED_UB_04 T_GRAMS_PER_SECc_BYTE;
#define V_GRAMS_PER_SECc_BYTE(val)  (BYTE)((val)*16)
#define S_GRAMS_PER_SECc_BYTE 4

/* power-of-two range: [0, 4096) */
typedef FIXED_UL_20 T_GRAMS_PER_SEC_LONG;
#define V_GRAMS_PER_SEC_LONG(val) (LONGWORD)((val)*1048576L)
#define S_GRAMS_PER_SEC_LONG 20

/* power-of-two range: [0, 16) */
typedef FIXED_UW_12             T_MILLISECONDSf;
#define V_MILLISECONDSf(val)    (WORD)((val)*4096)
#define S_MILLISECONDSf         12

/* power-of-two range: [-256, 256] */
typedef FIXED_SW_07 T_GRAMS_PER_SECf;
#define V_GRAMS_PER_SECf(val)  (INTEGER)((val)*128)
#define S_GRAMS_PER_SECf 7

/* power-of-two range: [0, 2048] */
typedef FIXED_UW_05        T_MILLIGRAMSe;
#define V_MILLIGRAMSe(val) (WORD)((val)*32)
#define S_MILLIGRAMSe      5

/* power-of-two range: [-8192, 8192] */
typedef FIXED_SL_18        T_MILLIGRAMSf;
#define V_MILLIGRAMSf(val) (LONGINT)((val)*262144L)
#define S_MILLIGRAMSf      18

/* time in seconds (16-bits, LSB=0.0039 sec), range: [0, 255.996] */
typedef FIXED_UW_16           T_SECOND_0_1 ;
#define V_SECOND_0_1(val)     (WORD)((val)*(65536))
#define S_SECOND_0_1          16

/* power-of-two range: [-2048, 2048) */
typedef FIXED_SW_04           T_DEG_Kc;
#define V_DEG_Kc(val)         (INTEGER)((val)*16)
#define S_DEG_Kc              4

/*  time in minutes - used by low power counter */
/* power-of-two range: (0, 65535) */
typedef FIXED_UW_00           T_MIN;
#define V_MIN(val)            (WORD)((val)*1)
#define S_MIN                 0

/*#if XeSYST_LOW_POWER_COUNTER == CeSYST_AVAILABLE*/

/* power-of-two range: (0, 65535) */
typedef FIXED_UW_00           T_MIN_LPC;
#define V_MIN_LPC(val)        (WORD)((val)*1)
#define S_MIN_LPC             0
/*#endif*/

typedef enum {
             CeETSE_IAT,
             CeETSE_CLT
             } TeETSE_EGR_PSTN;

/*    end PSE_TSE */
typedef FIXED_UW_08            T_LITER;
#define V_LITER(val)           (WORD)(val*256)
#define S_LITER                8

typedef FIXED_UW_08            T_GRAM_SEC;
#define V_GRAM_SEC(val)        (WORD)(val*256)
#define S_GRAM_SEC             8

typedef FIXED_UL_08            T_GRAM_SEC_LONG;
#define V_GRAM_SEC_LONG(val)   (LONGWORD)(val*256)
#define S_GRAM_SEC_LONG        8

typedef FIXED_UW_02            T_HERTZ_MAF;
#define V_HERTZ_MAF(val)       (WORD)(val*4)
#define S_HERTZ_MAF            2

typedef FIXED_UW_06            T_BPW;
#define V_BPW(val)             (WORD)((val)*64)
#define S_BPW                  6

typedef FIXED_UW_06            T_CRANK_ANGLE;
#define V_CRANK_ANGLE(val)     (WORD)((val)*64)
#define S_CRANK_ANGLE          6

typedef FIXED_SW_06            T_CRANK_ANGLEa;
#define V_CRANK_ANGLEa(val)    (INTEGER)((val)*64)
#define S_CRANK_ANGLEa         6

typedef FIXED_SW_00            T_FUEL_INT;
#define V_FUEL_INT(val)        (INTEGER)((val))
#define S_FUEL_INT             0

typedef FIXED_UW_08            T_CL_FLOW;
#define V_CL_FLOW(val)         (WORD)((val)*256)
#define S_CL_FLOW              8

typedef FIXED_SW_11            T_AFR_DIFF;
#define V_AFR_DIFF(val)        (INTEGER)((val)*2048)
#define S_AFR_DIFF             11

typedef FIXED_UW_11            T_AFR;
#define V_AFR(val)             (WORD)((val)*2048)
#define S_AFR                  11

typedef FIXED_UW_10            T_AFRa;
#define V_AFRa(val)            (WORD)((val)*1024)
#define S_AFRa                 10

typedef FIXED_SW_10            T_AFRd;
#define V_AFRd(val)            (INTEGER)((val)*1024)
#define S_AFRd                 10

typedef FIXED_SW_13            T_DELIVD_CL_CORR;
#define V_DELIVD_CL_CORR(val)  (INTEGER)((val)*8192)
#define S_DELIVD_CL_CORR       13

typedef FIXED_UW_13            T_INJECT_FLOW;
#define V_INJECT_FLOW(val)     (WORD)((val)*8192)
#define S_INJECT_FLOW          13

typedef FIXED_UW_16             T_FUEL_RES;
#define V_FUEL_RES(val)         (WORD)((val)*65536)
#define S_FUEL_RES              16

typedef FIXED_SW_08             T_DEG_PER_RPM;
#define V_DEG_PER_RPM(val)      (INTEGER)((val)*256)
#define S_DEG_PER_RPM           8

/* RPM change over a 46.86 msec window (rpm/46.86 msec) */
/* range: [-256, 255.992187]                            */
typedef FIXED_SW_07                 T_RPM_PER_46P86_MSECa;
#define V_RPM_PER_46P86_MSECa(val)  (INTEGER)((val)*128)
#define S_RPM_PER_46P86_MSECa       7

/* electronic potential (volts), range: [0, 31.999] */
typedef FIXED_UW_11             T_VOLTb;
#define V_VOLTb(val)            (WORD)((val)*2048)
#define S_VOLTb                 11

/* conversion factor (rpm/volt), range: [0, 127.998] */
typedef FIXED_UW_09           T_RPM_PER_VOLTa;
#define V_RPM_PER_VOLTa(val)  (WORD)((val)*512)
#define S_RPM_PER_VOLTa       9

/* pressure in mega pascals (MPa), range: [0, 15.999] */
typedef FIXED_UW_12             T_MPA;
#define V_MPA(val)              (WORD)((val)*4096)
#define S_MPA                   12

typedef FIXED_UW_15             T_PERCENT_PER_MPA;
#define V_PERCENT_PER_MPA(val)  (WORD)((val)*32768)
#define S_PERCENT_PER_MPA       15

typedef FIXED_SW_12             T_MPA_DIFF;
#define V_MPA_DIFF(val)         (INTEGER)((val)*4096)
#define S_MPA_DIFF              12

/* pressure in kilo pascals (kPa), range: [-4096, 4095.875] */
typedef FIXED_SW_03  T_KPAd;
#define V_KPAd(val)  (INTEGER)((val)*8)
#define S_KPAd 3

/* Pressure in kilo pascals (kpa), range: [0, 32768] */
typedef FIXED_UW_01         T_KPA_0_32768;
#define V_KPA_0_32768(val)  (WORD)((val)*2)
#define S_KPA_0_32768       1

/* time in seconds (16-bits, LSB=0.0039 sec), range: [0, 255.996] */
typedef FIXED_UW_08             T_SECOND_P0039 ;
#define V_SECOND_P0039(val)     (WORD)((val)*(256))
#define S_SECOND_P0039          8

/* time in seconds (16-bits, LSB=1/65536 sec), range: [0, 1] */
typedef FIXED_UW_16             T_TIME_SEC_0_1 ;
#define V_TIME_SEC_0_1(val)     (WORD)((val)*(65536))
#define S_TIME_SEC_0_1          16

/* time in seconds (16-bits, LSB=0.0078125 sec), range: [0, 511.992] */
typedef FIXED_UW_07             T_TIME_SEC_P00781;
#define V_TIME_SEC_P00781(val)  (WORD)((val)*128)
#define S_TIME_SEC_P00781       7

/* time in seconds (16-bits, LSB=0.015625 sec), range: [0, 1022.346] */
typedef FIXED_UW_06             T_TIME_SEC_P0156;
#define V_TIME_SEC_P0156(val)   (WORD)((val)*64)
#define S_TIME_SEC_P0156        6

/* time in seconds (16-bits, LSB=0.015625 sec), range: [-512.0, 511.992] */
typedef FIXED_SW_06             T_TIME_SEC15p6Diff;
#define V_TIME_SEC15p6Diff(val) (WORD)((val)*64)
#define S_TIME_SEC15p6Diff      6

/* time in seconds (16-bits, LSB=0.0625 msec), range: [0, 4095.9375] */
typedef FIXED_UW_04             T_TIME_SEC_P0625;
#define V_TIME_SEC_P0625(val)   (WORD)((val)*16)
#define S_TIME_SEC_P0625        4

/* time in seconds (16-bits, LSB=0.000015258), range: [0, 0.999] */
typedef FIXED_UW_16             T_TIME_SEC_P000015;
#define V_TIME_SEC_P000015(val) (WORD)((val)*65536)
#define S_TIME_SEC_P000015      16

/* distance in inches, range [0,256)   */
typedef FIXED_UW_16             T_INCHES;
#define V_INCHES(val)           (WORD)((val)*256)
#define S_INCHES                8

/* distance in meters, range [0,256)   */
typedef FIXED_UW_16             T_METERS;
#define V_METERS(val)           (WORD)((val)*256)
#define S_METERS                8

/* distance in meters, range [0,256)   */
typedef FIXED_UW_08             T_METER_0_256;
#define V_METERS(val)           (WORD)((val)*256)
#define S_METERS                8

/* percent/100, range: [0, 4) */
typedef FIXED_UW_14            T_PERCENT_MULTe;
#define V_PERCENT_MULTe(val)   (WORD)((val)*16384)
#define S_PERCENT_MULTe        14


/* power-of-two range: [0, 16) Res: 0.000244 */
/*  may be used for miscellaneous unsigned factors in the range 0:16  */
typedef FIXED_UW_12               T_FACTOR_0_16;
#define V_FACTOR_0_16(val)        (WORD)(val*4096)
#define S_FACTOR_0_16             12

/* distance in kilometers, range [0,.99]   */
typedef FIXED_UW_16             T_KILOMETERSc;
#define V_KILOMETERSc(val)      (WORD)((val)*65536)
#define S_KILOMETERSc           16

/* Res:   0.007812500000000         */
/* Range: [0, 512)                  */
typedef T_W_RANGE_0_512         T_KILOMETERS_0_512;
#define V_KILOMETERS_0_512(val) V_W_RANGE_0_512(val)
#define S_KILOMETERS_0_512      S_W_RANGE_0_512

/* speed in kilometers per hour, range [0,255.996] */
typedef FIXED_UW_08 T_KPHb;
#define V_KPHb(val)  (WORD)((val)*256)
#define S_KPHb 8

/* acceleration, kilometers per hour per second, range [-32, 32) */
typedef FIXED_SW_10             T_KPH_PER_SECa;
#define V_KPH_PER_SECa(val)     (INTEGER)((val)*1024)
#define S_KPH_PER_SECa          10

/* acceleration, kilometers per hour per second, range [-64, 64) */
typedef FIXED_SW_09             T_KPH_PER_SEC_N64_64;
#define V_KPH_PER_SEC_N64_64(val) (INTEGER)((val)*512)
#define S_KPH_PER_SEC_N64_64    9

/* jerk, kilometers per hour per second per second, range [-32, 32) */
typedef FIXED_SW_10             T_KPH_SEC_SEC_N32_32;
#define V_KPH_SEC_SEC_N32_32(val) (INTEGER)((val)*1024)
#define S_KPH_SEC_SEC_N32_32    10

/* percent/100, range: [-0.5, 0.5), precision: 0.00152 */
typedef FIXED_SW_16             T_PERCENT_DIFFc;
#define V_PERCENT_DIFFc(val)    (INTEGER)((val)*655.36)
#define S_PERCENT_DIFFc 16

/* percent/100, range: [0, 2) */
typedef FIXED_UW_15             T_PERCENTd;
#define V_PERCENTd(val)         (WORD)((val)*327.68)
#define S_PERCENTd 15

/* percent/100, range: [0, <1)  resolution: 0.0039 */
typedef FIXED_UB_08             T_PERCENTd_BYTE;
#define V_PERCENTd_BYTE(val)    (BYTE)((val)*2.56)
#define S_PERCENTd_BYTE 8

/* percent/100, range: [-1,1) */
typedef FIXED_SW_15             T_PERCENT_DIFFd;
#define V_PERCENT_DIFFd(val)    (INTEGER)((val)*327.68)
#define S_PERCENT_DIFFd 15

/* percent/100, range: [0, 2) */
typedef FIXED_UW_15            T_PERCENT_MULTa;
#define V_PERCENT_MULTa(val)   (WORD)((val)*32768)
#define S_PERCENT_MULTa        15

/* percent/100, range: [0, 2)  Res: 0.0078125*/
typedef FIXED_UB_07               T_PERCENT_MULTa_BYTE;
#define V_PERCENT_MULTa_BYTE(val) (BYTE)((val)*128)
#define S_PERCENT_MULTa_BYTE      7

/* percent/100, range: [0, 1) */
typedef FIXED_UW_16            T_PERCENT_MULTb;
#define V_PERCENT_MULTb(val)   (WORD)((val)*65536)
#define S_PERCENT_MULTb        16

/* percent/100, range: [-2, 2) */
typedef FIXED_SW_14            T_PERCENT_MULTc;
#define V_PERCENT_MULTc(val)   (INTEGER)((val)*16384)
#define S_PERCENT_MULTc        14

/* percent/100, range: [-1, 1) */
typedef FIXED_SW_15            T_PERCENT_MULTd;
#define V_PERCENT_MULTd(val)   (INTEGER)((val)*32768)
#define S_PERCENT_MULTd        15

/* Data types defined by Airflow Subsystem */

typedef FIXED_UW_15             T_GRAMS_0_2;
#define V_GRAMS_0_2(val)        (WORD)(val*32768)
#define S_GRAMS_0_2             15

typedef FIXED_UW_15             T_GRAMS_CYL_0_1;
#define V_GRAMS_CYL_0_1(val)    (WORD)(val*32768)
#define S_GRAMS_CYL_0_1         15

typedef FIXED_UW_12             T_GRAMS_CYL_0_16;
#define V_GRAMS_CYL_0_16(val)   (WORD)(val*4096)
#define S_GRAMS_CYL_0_16        12

typedef T_W_RANGE_0_4096        T_GRAMS_0_4096;
#define V_GRAMS_0_4096(val)     V_W_RANGE_0_4096(val)
#define S_GRAMS_0_4096          S_W_RANGE_0_4096

typedef FIXED_UW_07             T_DEG_K_0_512;
#define V_DEG_K_0_512(val)      (WORD)(val*128)
#define S_DEG_K_0_512           7

/* End Data types defined by Airflow Subsystem */

/* power-of-two range: (-256, 256), precision = 1/128 = 0.0078125 */
typedef FIXED_SW_07            T_GRAM_SEC_DIFF;
#define V_GRAM_SEC_DIFF(val)  (INTEGER)((val)*128)
#define S_GRAM_SEC_DIFF       7

/* power-of-two range: [0, 256) */
typedef FIXED_UW_08 T_GRAMS_PER_SECb;
#define V_GRAMS_PER_SECb(val)  (WORD)((val)*256)
#define S_GRAMS_PER_SECb 8

/* power-of-two range: [0, 8) */
typedef FIXED_UW_13             T_GRAMS_PER_SECe;
#define V_GRAMS_PER_SECe(val)   (WORD)((val)*8192)
#define S_GRAMS_PER_SECe        13

/* Res:   0.015625000000000         */
/* Range: [0, 1024)                 */
typedef T_W_RANGE_0_1024             T_GRAMS_PER_SEC_0_1024;
#define V_GRAMS_PER_SEC_0_1024(val)  V_W_RANGE_0_1024(val)
#define S_GRAMS_PER_SEC_0_1024       S_W_RANGE_0_1024


/* Tank Vacuum */
/* power-of-two range: [-32, 32) */
typedef FIXED_SW_10             T_VAC;
#define V_VAC(val)              (INTEGER)((val)*1024)
#define S_VAC                   10

/* Tank Vacuum Slope */
/* power-of-two range: [-32, 32) */
typedef FIXED_SW_10             T_VAC_PER_SEC;
#define V_VAC_PER_SEC(val)      (INTEGER)((val)*1024)
#define S_VAC_PER_SEC           10

/* Tank Vacuum per %Vref Slope */
/* power-of-two range: [-32, 32) */
typedef FIXED_SW_10                 T_VAC_PER_VREF_N32_32;
#define V_VAC_PER_VREF_N32_32(val)  (INTEGER)((val)*1024)
#define S_VAC_PER_VREF_N32_32       10

/* power-of-two range: [0, 256) */
typedef FIXED_UW_08 T_SECONDSa;
#define V_SECONDSa(val)  (WORD)((val)*256)
#define S_SECONDSa 8

/* time in seconds (16-bits, LSB=0.0000610 sec), range: [0, 3.99] */
typedef FIXED_UW_16           T_SECONDS_0_4;
#define V_SECONDS_0_4(val)     (WORD)((val)*(16384))
#define S_SECONDS_0_4          14

/* time in seconds (16-bits, LSB=0.0001220 sec), range: [0, 7.99] */
typedef FIXED_UW_16           T_SECONDS_0_8;
#define V_SECONDS_0_8(val)     (WORD)((val)*(8192))
#define S_SECONDS_0_8          13

/* power-of-two range [-512, 512) */
typedef FIXED_SW_06              T_MILLISECONDSb_DIFF;
#define V_MILLISECONDSb_DIFF(val) (INTEGER)((val)*64)
#define S_MILLISECONDSb_DIFF        6

/* power-of-two range: [0, 1024) */
typedef FIXED_UW_06             T_MILLISECONDSb;
#define V_MILLISECONDSb(val)    (WORD)((val)*64)
#define S_MILLISECONDSb         6

/* power-of-two range: [0, 2048) */
typedef FIXED_UW_05             T_MILLISECONDSc;
#define V_MILLISECONDSc(val)    (WORD)((val)*32)
#define S_MILLISECONDSc         5

/* power-of-two range: [0, 16384) */
typedef FIXED_UW_02            T_MILLISECONDSd;
#define V_MILLISECONDSd(val)   (WORD)((val)*4)
#define S_MILLISECONDSd        2

/* power-of-two range: [0, 256) */
typedef FIXED_UW_08            T_MILLISECONDSe;
#define V_MILLISECONDSe(val)   (WORD)((val)*256)
#define S_MILLISECONDSe        8

typedef FIXED_SW_15             T_GRAMS_CYL_DIFF;
#define V_GRAMS_CYL_DIFF(val)   (INTEGER)(val*327.68)
#define S_GRAMS_CYL_DIFF        15

typedef FIXED_SW_02            T_DECIBELS;
#define V_DECIBELS(val)        (INTEGER)(val*4)
#define S_DECIBELS             02

typedef FIXED_UW_09            T_DUTY_CYCLEa;
#define V_DUTY_CYCLEa(val)     (WORD)((val)*(512))
#define S_DUTY_CYCLEa          9

typedef FIXED_SW_07            T_DUTY_CYCLEb;
#define V_DUTY_CYCLEb(val)     (INTEGER)((val)*(128))
#define S_DUTY_CYCLEb          7

typedef FIXED_UW_05            T_HERTZc;
#define V_HERTZc(val)          (WORD)((val)*(32))
#define S_HERTZc               5

typedef FIXED_UW_00            T_HERTZb;
#define V_HERTZb(val)          (WORD)((val)*(1))
#define S_HERTZb               0

typedef FIXED_UW_08            T_HERTZa;
#define V_HERTZa(val)          (WORD)((val)*(256))
#define S_HERTZa               8

typedef FIXED_UW_07            T_PERCENTe ;
#define V_PERCENTe(val)        (WORD)((val)*(128))
#define S_PERCENTe             7

typedef FIXED_SW_07            T_PERCENTf;
#define V_PERCENTf(val)        (INTEGER)((val)*(128))
#define S_PERCENTf             7

typedef FIXED_SW_08            T_PERCENTg;
#define V_PERCENTg(val)        (INTEGER)((val)*(256))
#define S_PERCENTg             8

typedef FIXED_UW_09            T_PERCENTh;
#define V_PERCENTh(val)        (WORD)((val)*(512))
#define S_PERCENTh             9

typedef FIXED_UW_13            T_PERCENTj;
#define V_PERCENTj(val)        (WORD)((val)*8192)
#define S_PERCENTj             13

/* power-of-two range: [-512, 512) resolution: 0.0625 */
typedef FIXED_SW_06             T_PERCENT_n512_512;
#define V_PERCENT_n512_512(val) (INTEGER)((val)*(64))
#define S_PERCENT_n512_512      6

typedef FIXED_UW_06            T_VOLTc;
#define V_VOLTc(val)           (WORD)((val)*(64))
#define S_VOLTc                6

typedef FIXED_SW_06            T_VOLTd;
#define V_VOLTd(val)           (INTEGER)((val)*(64))
#define S_VOLTd                6

typedef FIXED_SW_11            T_VOLTe;
#define V_VOLTe(val)           (INTEGER)((val)*(2048))
#define S_VOLTe                11

/* power-of-two range: [0, 8) Volts, precision = 0.00012207 */
typedef FIXED_UW_13            T_VOLTf;
#define V_VOLTf(val)           (WORD)((val)*(8192))
#define S_VOLTf                13

 /* power-of-two range: [-1, < 1] */
typedef FIXED_SW_15            T_RATIO_N1_1;
#define V_RATIO_N1_1(val)      (INTEGER)((val)*32768)
#define S_RATIO_N1_1           15

/* power-of-two range: [-8, 8) */
typedef FIXED_SW_12            T_RATIO_N8_8;
#define V_RATIO_N8_8(val)      (INTEGER)((val)*4096)
#define S_RATIO_N8_8           12

 /* power-of-two range: [-16, 16) */
typedef FIXED_SW_11            T_RATIO_N16_16;
#define V_RATIO_N16_16(val)    (INTEGER)((val)*2048)
#define S_RATIO_N16_16         11

 /* power-of-two range: [-32, < 32] */
typedef FIXED_SW_10            T_RATIO_N32_32;
#define V_RATIO_N32_32(val)    (INTEGER)((val)*1024)
#define S_RATIO_N32_32         10

 /* power-of-two range: [-64, < 64] */
typedef FIXED_SW_09            T_RATIO_N64_64;
#define V_RATIO_N64_64(val)    (INTEGER)((val)*512)
#define S_RATIO_N64_64         9

 /* power-of-two range: [-128, < 128] */
typedef FIXED_SW_08            T_RATIO_N128_128;
#define V_RATIO_N128_128(val)    (INTEGER)((val)*256)
#define S_RATIO_N128_128         8

/* power-of-two range: (-256, 256), precision = 1/128 = 0.0078125 */
typedef FIXED_SW_07            T_RATIO_N256_256;
#define V_RATIO_N256_256(val)  (INTEGER)((val)*128)
#define S_RATIO_N256_256       7

/* power-of-two range: [-512, 512] */
typedef FIXED_SW_06            T_RATIO_N512_512;
#define V_RATIO_N512_512(val)  (INTEGER)((val)*64)
#define S_RATIO_N512_512       6

/* power-of-two range: (0..<8) precision (0.00012207) */
typedef FIXED_UW_13            T_AMPSa;
#define V_AMPSa(val)            (WORD)((val)*(8192))
#define S_AMPSa                 13
typedef FIXED_UW_13            T_AMPS_0_8;  /* same as T_AMPSa */
#define V_AMPS_0_8(val)            (WORD)((val)*(8192))  /* same as V_AMPSa */
#define S_AMPS_0_8                 13                   /* same as S_AMPS_a */

/* power-of-two range: (-4..<4) precision (0.00012207) */
typedef FIXED_SW_13                 T_AMPS_N4_4;
#define V_AMPS_N4_4(val)            (INTEGER)((val)*(8192))
#define S_AMPS_N4_4                 13

 /* Purge fuction data type */
typedef FIXED_UW_13            T_PURG_FLOW;
#define V_PURG_FLOW(val)       (WORD)((val)*8192)
#define S_PURG_FLOW            13

 /* Percent/KPA */
 /* power-of-two range: [-32, 32) */
typedef FIXED_SW_10           T_PERCENT_KPA;
#define V_PERCENT_KPA(val)    (INTEGER)((val)*1024)
#define S_PERCENT_KPA  10

typedef FIXED_UW_12           T_GRAMS_SECb;
#define V_GRAMS_SECb(val)     (WORD)((val)*4096)
#define S_GRAMS_SECb  12

 /* power-of-two range:  [0, 32) */
typedef FIXED_UW_11           T_PERCENTc;
#define V_PERCENTc(val)       (WORD)((val)*20.48)
#define S_PERCENTc            11

 /* RATIO_DIFF */
 /* power-of-two range: [-32, 32) */
typedef FIXED_SW_10           T_RATIO_DIFF;
#define V_RATIO_DIFF(val)     (INTEGER)((val)*1024)
#define S_RATIO_DIFF          10

typedef FIXED_SW_14            T_PURG_FLOW_DIFF;
#define V_PURG_FLOW_DIFF(val)  (INTEGER)(val*16384)
#define S_PURG_FLOW_DIFF       14

/* power-of-two range: [-512, < 512] */
typedef FIXED_SW_06 T_KPH_DIFFa;
#define V_KPH_DIFFa(val)  (INTEGER)((val)*64)
#define S_KPH_DIFFa 6

/* power-of-two range: [-2, 2) */
typedef FIXED_SW_14 T_KPH_DIFFb;
#define V_KPH_DIFFb(val)  (INTEGER)((val)*16384)
#define S_KPH_DIFFb 14
typedef FIXED_UL_08        T_GRAMSb;
#define V_GRAMSb(val)      (LONGWORD)(val*256)
#define S_GRAMSb           8

/* time in seconds (16-bits, LSB=0.5 sec), range: [0, 32767.5] */
typedef FIXED_UW_01         T_TIME_SEC_P5;
#define V_TIME_SEC_P5(val)  (WORD)((val)*2)
#define S_TIME_SEC_P5       1

/* power-of-two range: [-32768, 32768) Res: 1 */
typedef FIXED_SW_00         T_NEWTON_S32768;
#define V_NEWTON_S32768(val) (INTEGER)((val))
#define S_NEWTON_S32768      0

/* Added for Torque */
/* power-of-two range: [-2048 2048) Res: 0.0625 */
typedef FIXED_SW_04         T_NEWTON_METER;
#define V_NEWTON_METER(val) (INTEGER)((val)*16)
#define S_NEWTON_METER      4

/* power-of-two range: [-128 128) Res: 0.00390625 */
typedef FIXED_SW_08                  T_NEWTON_METER_N128_128;
#define V_NEWTON_METER_N128_128(val) (INTEGER)((val)*256)
#define S_NEWTON_METER_N128_128      8

/* power-of-two range: [0, 1024 * 65536) Res: 0.015625 */
typedef FIXED_UL_06          T_NEWTON_METERa;
#define V_NEWTON_METERa(val) (INTEGER)((val)*64)
#define S_NEWTON_METERa      6

/* power-of-two range: [-8192, 8192) Res: 0.25 */
typedef FIXED_SW_02          T_NEWTON_METERb;
#define V_NEWTON_METERb(val) (INTEGER)((val)*4)
#define S_NEWTON_METERb      2

/* power-of-two range: [-128 127) Res: 0.00039 */
typedef FIXED_SW_08         T_KILONEWTON;
#define V_KILONEWTON(val)   (INTEGER)((val)*256)
#define S_KILONEWTON        8

/* power-of-two range: [0, 64) Res: 0.000977 */
typedef FIXED_UW_10         T_JOULE_PER_MILLIGRAM;
#define V_JOULE_PER_MILLIGRAM(val) (WORD)((val)*1024)
#define S_JOULE_PER_MILLIGRAM      10

/* power-of-two range: [0, 16) Res: 0.000244 */
typedef FIXED_UW_12         T_LITERa;
#define V_LITERa(val)       (INTEGER)((val)*4096)
#define S_LITERa            12

/* power-of-two range: [0, 1024) Res: 0.015625 */
typedef FIXED_UW_06        T_MILLIGRAMSb;
#define V_MILLIGRAMSb(val) (INTEGER)((val)*64)
#define S_MILLIGRAMSb      6

/* power-of-two range: [-512, 512) Res: 0.015625 */
typedef FIXED_SW_06        T_MILLIGRAMS_N512_512;
#define V_MILLIGRAMS_N512_512(val) (INTEGER)((val)*64)
#define S_MILLIGRAMS_N512_512      6

/* power-of-two range: [0, 1024) */
typedef FIXED_UW_06 T_KILO_WATT;
#define V_KILO_WATT(val)  (WORD)((val)*64)
#define S_KILO_WATT 6

/* power-of-two range: [0, 3.999) */
typedef FIXED_UW_14 T_METER_0_4;
#define V_METER_0_4(val)  (WORD)((val)*16384)
#define S_METER_0_4 14

/* power-of-two range: [0, 16384) */
typedef FIXED_UW_02 T_KILOGRAM;
#define V_KILOGRAM(val)  (WORD)((val)*4)
#define S_KILOGRAM 2

/* range: [0, 65535] */
typedef WORD                    T_NM_RPM_S_PER_GM;
#define V_NM_RPM_S_PER_GM(val)  (WORD)(val) /* no scaling is needed  */
#define S_NM_RPM_S_PER_GM       0           /* Count is integral     */
/* end Added for Torque */

 /* power-of-two range: [0, 256) */   /* RSM0574 */
typedef FIXED_UW_08            T_GRAMS_FUEL;
#define V_GRAMS_FUEL(val)      (WORD)((val)*256)
#define S_GRAMS_FUEL  8

/* power-of-two range: [-2048 2047) Res: 0.0625 */
typedef FIXED_SW_04              T_ANGLEa_N2048_2047;
#define V_ANGLEa_N2048_2047(val) (INTEGER)((val)*16)
#define S_ANGLEa_N2048_2047      4

/* ETC special data type for Calibration */
/* !!! T_RATIO_Cal_0_256 should ONLY be used for Calibration data type
   to reduce multiplication by 100 operation for thruput saving !!! */
/* power-of-two range: [0, 256) in code,
   Engineering range [0,2.56) in Cal-form, Res:0.0000390625 */
typedef FIXED_UW_08 T_RATIO_Cal_0_256;
#define V_RATIO_Cal_0_256(val)  (WORD)((val)*256*100)
#define S_RATIO_Cal_0_256        8

typedef struct {
               WORD fLow;
               WORD fHigh;
               }         T_HYST_PAIR;

typedef enum {
            CeDualBankDualCat,
            CeDualBankSingleCat,
            CeSingleBankSingleCat
            } TeExhaustConfig;

typedef enum {
              CeDUAL_BANK_DUAL_CAT,
              CeDUAL_BANK_SINGLE_CAT,
              CeSINGLE_BANK_SINGLE_CAT
              } TeEXHAUST_CONFIG;

typedef enum {
             CeUndefinedSFI,
             CePrimePulseSFI,
             CeSequentialSFI
             } TeFuelMode;

typedef enum {
             CeUndefinedEST,
             CeSingleChannelEST,
             CeWasteEST,
             CeSequentialEST,
             CeSimultaneousEST
             } TeSpkMode;

/* Watch out: Do not change the order or the value of the following */
/*            enumeration constants. The numerical values of the    */
/*            enumeration constants are used throughout the spark,  */
/*            fuel and knock logic.                                 */
typedef enum
{
  CeCYLINDER1=0,
  CeCYLINDER2=1,
  CeCYLINDER3=2,
  CeCYLINDER4=3,
  CeCYLINDER5=4,
  CeCYLINDER6=5,
  CeCYLINDER7=6,
  CeCYLINDER8=7,
  CeNBROFCYLS=8

} TeCYLINDER;

typedef enum
{
  CeFORCE_ON,
  CeFORCE_OFF,
  CeSD_INACTIVE
} TeSD_OVRD_ST;

typedef enum
{
  CeAC_OFF,
  CeAC_ON
} TeON_OFF;

typedef enum
{
  CeOVRD_INACTIVE,
  CeOVRD_ABSOLUTE,
  CeOVRD_MODIFY
} TeOVRD_ST;

typedef enum
{
  CeMAP,
  CeVAC
} TeLOAD_OPT;

typedef enum
{
  CeLEAN,
  CeRICH
} TeO2_STATUS;

/* typedef enum      */
/* {                 */
/*   CeFUEL_ON,      */
/*   CeFUEL_OFF,     */
/*   CeRAMP_OUT,     */
/*   CeRAMP_IN       */
/* } TeFUEL_CUT_OFF; */

typedef enum
{
  CeSIMULTANEOUS,
  CeSEQUENTIAL
} TeFUEL_DELIVRY_MODE;

/* typedef enum         */
/*{                     */
/*  CeFIRST_TIME,       */
/*  CeAFTER_STALL       */
/*} TePRIME_PULSE_MODE; */

/* typedef enum         */
/* {                    */
/*  CeDISABLE,          */
/*  CeSINGLE,           */
/*  CeMULTIPLE          */
/*} TeTRIM_PULSE_MODE;  */

typedef enum
{
  CePOWER_ON,
  CeFIRST_TOOTH
} TePUMP_PRIME_OPT;

typedef enum
{
  CeCLFLOW,
  CeBLMCELL
} TeCL_LOAD_SEL;

typedef enum
{
  CeCL_FLOW,
  CeENGINE_SPD
} TeINT_LOAD_SEL;

typedef enum
{
  CeBANK1,
  CeBANK2
} TeFUEL_BANK;

typedef enum
{
  CeMANUAL,
  CeAUTO
} TeTRANS_TYPE;

typedef enum
{
  CeNOT_STARTED,
  CeIN_PROGRESS,
  CeCOMPLETE
} TeEGR_CLEAN_STATE;

typedef enum
{
  CeUPDATE_INACT,
  CeSTEP_UP,
  CeSTEP_DOWN,
  CeSTABLE
} TeUPDATE_PURG_MOD;

typedef enum
{
  CeVLV_INACT,
  CeFORCE_OPEN,
  CeFORCE_CLOSED
} TeVLV_OVRD_ST;

typedef enum
{
  CeOVRD_INACT,
  CeRAMP_OFF
} TeTANK_OVRD;

typedef enum {
             CeEVPD_PRG_INACTIVE,
             CeEVPD_PRG_RAMP_OFF,
             CeEVPD_PRG_TANK_VACUUM,
             CeEVPD_PRG_MASS_FLOW
             } T_EVPD_PRG_CTL;

typedef enum {
              CeEVPD_VENT_INACTIVE,
              CeEVPD_VENT_FORCED_CLOSED,
              CeEVPD_VENT_FORCED_OPEN
             } T_EVPD_VENT_CTL;

/* Enumerations defined by the Airflow Subsystem */
typedef enum {
             CeSPEED_DENSITY,
             CeMASS_AIRFLOW
             } TeAIRFLOW_MODE;

typedef enum {
             CeFUEL_CRANK,
             CeFUEL_RUN,
             CeFUEL_INACTIVE
             } TeFUEL_MODE;

typedef enum {
             CeAIRF_MODIFY,
             CeAIRF_ABSOLUTE
             } TeVE_SLEW_STATUS;

typedef enum {
             CeAIRF_MAP,
             CeAIRF_VAC,
             CeAIRF_TPS
             } TeAIRF_VE_LOAD;

typedef enum {
             CeAIRF_DECREASE,
             CeAIRF_INCREASE,
             CeAIRF_INACTIVE
             } TeAIRF_TRANS_MODE;

/* End enumerations defined by the Airflow subsystem */
/* Enumerations defined by the hardware diagnostics */
typedef enum {
               CeINJ_FAILED,
               CeINJ_NORMAL
            } TeINJ_CIRCUIT_STATE;

typedef enum {
               CeEST_FAULTED,
               CeEST_NOMINAL
            } TeEST_CIRCUIT_STATE;
/* End enumerations defined by the hardware diagnostics */

/* Enumerations defined by the Cruise subsystem */
typedef enum
{
  CeVIOS_CRUZ_NOT_ASSERTED,
  CeVIOS_CRUZ_ASSERTED
} TeVIOS_CRUZ_SWITCH_STATE;

typedef enum
{
  CeVIOS_CRUZ_OFF,
  CeVIOS_CRUZ_ON
} TeVIOS_CRUZ_STATE;

typedef enum
{
  CeVIOS_CRUZ_NONE,
  CeVIOS_CRUZ_MOMENTARY,
  CeVIOS_CRUZ_LATCHING
} TeVIOS_CRUZ_SWITCH_TYPE;

typedef enum
{
  CeCRUZ_SET_COAST,                     /* 00 */
  CeCRUZ_SET_ACCEL                      /* 01 */
} TeCRUZ_CRUISE_SWITCH_CONFIG;

/* End Enumerations defined by the Cruise subsystem */

typedef FIXED_UW_15 T_MAP3_UW_INDEX;
typedef FIXED_UW_14 T_MAP5_UW_INDEX;
typedef FIXED_UW_13 T_MAP9_UW_INDEX;
typedef FIXED_UW_12 T_MAP17_UW_INDEX;
typedef FIXED_UW_11 T_MAP33_UW_INDEX;

typedef FIXED_SW_15 T_MAP3_SW_INDEX;
typedef FIXED_SW_14 T_MAP5_SW_INDEX;
typedef FIXED_SW_13 T_MAP9_SW_INDEX;
typedef FIXED_SW_12 T_MAP17_SW_INDEX;
typedef FIXED_SW_11 T_MAP33_SW_INDEX;

typedef enum {CeNotMovingSt,
              CeExtendSt,
              CePauseSt,
              CeRetractSt
              } TeIAC_MotorSt;

typedef enum {CeStable,
              CeRetract,
              CeExtend} TeIAC_MotorDirection;

typedef enum  {
               CeMANIFOLD_VACUUM,
               CePERCENT_EGR
              } TeTBL_SWITCH_VAC_EGR;

typedef FIXED_SW_07 T_MILLISECONDS_DIFF;
#define V_MILLISECONDS_DIFF(val) (WORD)(val*128)
#define S_MILLISECONDS_DIFF 7

/*
  The Hi-Resolution clock tick data types below are currently used only for the
  misfire and tooth error correction diagnostics.  The resolution of each type
  is 1 count = 8/(system clock).
 */
/* power-of-two range [0 to 4294967295) */
typedef FIXED_UL_00 T_HIRES_CLKTCKS_LONGa;
#define V_HIRES_CLKTCKS_LONGa(val) (LONGWORD)(val)
#define S_HIRES_CLKTCKS_LONGa 0

/* power-of-two range [0 to 65535) */
typedef FIXED_UW_00 T_LOWRES_CLKTCKS_WORD;
#define V_LOWRES_CLKTCKS_WORD(val) (WORD)(val)

/* power-of-two range [-2147483648 to 2147483647) */
typedef FIXED_SL_00 T_HIRES_CLKTCKS_LONGb;
#define V_HIRES_CLKTCKS_LONGb(val) (LONGINT)(val)
#define S_HIRES_CLKTCKS_LONGb 0

#if XeSYST_MISF_ENGINE_LOAD_SELECT_OPTION == CeSYST_MISF_ENGINE_LOAD_PERCENT
/*   We will create a new type which is identical to T_PERCENTa for
     applications which use LV8 */
  #define T_PERCENTb_OR_KPAa T_PERCENTb
  #define V_PERCENTb_OR_KPAa V_PERCENTb
  #define S_PERCENTb_OR_KPAa S_PERCENTb
#else  /* by default, XeSYST_MISF_LOAD_SELECT_OPTION == CeSYST_MISF_ENGINE_LOAD_KPA */
/*   We will create a new type which is identical to T_KPAa for
     applications which use MAP */
  #define T_PERCENTb_OR_KPAa T_KPAa
  #define V_PERCENTb_OR_KPAa V_KPAa
  #define S_PERCENTb_OR_KPAa S_KPAa
#endif

/* range is 0 to 131072.99999   */
/* same binary point as T_RATIO_0_2 */
typedef FIXED_UL_15 T_RATIO_0_2_LONG;
#define V_RATIO_0_2_LONG(val) (LONGWORD)(val*32768)
#define S_RATIO_0_2_LONG 15

 /* power-of-two range: [-65535, < 65535)  Res: 0.0000305176*/
typedef FIXED_SL_15 T_RATIO_N65535_65536_LONG;
#define V_RATIO_N65535_65536_LONG(val) (LONGINT)((val)*32768)
#define S_RATIO_N65535_65536_LONG  15

/* The following types are used for 8-bit lookup table */
/* power-of-two range: [0, 127)  Res: 0.5 */
typedef FIXED_UB_01 T_KPAa_BYTE;
#define V_KPAa_BYTE(val)  (BYTE)((val)*2)
#define S_KPAa_BYTE 1

/* power-of-two range: [0, 255) Res: 1.0 */
typedef FIXED_UB_00 T_ANGLEa_BYTE;
#define V_ANGLEa_BYTE(val)  (BYTE)(val)
#define S_ANGLEa_BYTE 0

/* power-of-two range: [-64, 63.5) Res: 0.5 */
typedef FIXED_SB_01 T_ANGLEa_BYTEa;
#define V_ANGLEa_BYTEa(val)  (SHORTINT)((val)*2)
#define S_ANGLEa_BYTEa 1

/* power-of-two range: [0, 255) Res: 1.0 */
typedef FIXED_UB_00         T_NEWTON_METER_BYTE;
#define V_NEWTON_METER_BYTE(val) (BYTE)(val)
#define S_NEWTON_METER_BYTE      0

/* power-of-two range: [0, 1.9921875) Res: 0.0078125 */
typedef FIXED_UB_07 T_RATIO_0_2_BYTE;
#define V_RATIO_0_2_BYTE(val) (BYTE)(val*128)
#define S_RATIO_0_2_BYTE 7

/* power-of-two range: [0, 31.875] Res: 0.125 */
typedef FIXED_UB_03            T_AFR_BYTE;
#define V_AFR_BYTE(val)        (BYTE)((val)*8)
#define S_AFR_BYTE             3

typedef FIXED_UW_07 T_CRANKPHI;
#define V_CRANKPHI(val) ((val) >= 0) ? \
   (((val)*((LONGWORD)1<<7)) > (MAX_UW)) ? \
   ((WORD)(MAX_UW)) : ((WORD)((val)*((LONGWORD)1<<7))) : \
         ((WORD)((val)*((LONGWORD)1<<7)) < (WORD)(MIN_UW) || ((MIN_UW)==0)) ? \
   ((WORD)(MIN_UW)) : ((WORD)((val)*((LONGWORD)1<<7)))
#define S_CRANKPHI 7

typedef FIXED_UL_04 T_MICROSECONDS_LONGb;
#define V_MICROSECONDS_LONGb(val) (WORD)((val)*16)
#define S_MICROSECONDS_LONGb 4

/* angle (degrees) */
/* range: [-256, 255.992187] Res: 0.0078125 */
typedef FIXED_SW_07 T_CAMPHI;
#define V_CAMPHI(val) V_SW_07(val)
#define S_CAMPHI S_SW_07

/* angular velocity (Degrees/second)   */
/* range: [-4096, 4095.875] Res: 0.125 */
typedef FIXED_SW_03         T_PHI_PER_SEC;
#define V_PHI_PER_SEC(val)  V_SW_03(val)
#define S_PHI_PER_SEC       S_SW_03

/* pressure [Psi] */

/* Res:   0.015625000 */
/* Range: [0, 1024)   */
typedef FIXED_UW_06         T_W_PSI_0_1024;
#define V_W_PSI_0_1024(val) V_UW_06(val)
#define S_W_PSI_0_1024      S_UW_06

/* Newton Meter */
/* power-of-two range: [0, 256 ) Res: 0.00390625 */
typedef FIXED_UW_08          T_NEWTON_METERc;
#define V_NEWTON_METERc(val) (WORD)((val)*256)
#define S_NEWTON_METERc      8

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.00  950803 rmg      Created module
* 1.01  950901 jrg      Changed scaling of T_GRAM_SEC, added T_HERTZ_MAF
* 1.02  951030 jrg      Changed T_GALLON to T_LITER
* 1.10  960115 jrg      Updated type names to better fit naming standards
* 1.27  960806 blt      Added: T_RPM_PER_46P86_MSECa, T_VOLTb,T_RPM_PER_VOLTa,
*                              T_TIME_SEC_P0156, T_TIME_SEC_P0625, T_KPHb, and
*                              T_KPAd
* 1.28  960815 mye      Deleted Te_SD_SLEW_STATUS (belong to INST)
* 1.41  960816 blt      Added: T_PERCENT_DIFFc, T_PERCENTd, T_PERCENT_DIFFd,
*                              FIXED_SW_16
* 1.46  961014 blt      Added T_TIME_SEC_P00781.
* 1.48  961029 blt      Changed scaling _PERCENTd and _PERCENT_DIFFd to UW_15
*                       and SW15
* 1.49  961118 l.q      Changed scaling _CL_FLOW to UW_08
* 1.52  970103 mrw 0030 changed transient spark dd
* 1.56  970416 sai      Added enumerations for hardware diagnostics
* 1.57  970506 blt      Added:  T_DUTY_CYCLEa,  T_DUTY_CYCLEb,  T_HERTZb
*                               T_PERCENTe,     T_PERCENTf,     T_PERCENTg
*                               T_VOLTc,        T_VOLTd
* 1.58  970515 l.q      Added   T_MILLISECONDSc
* 1.59  970521 blt      Added:  T_RATIO_N64_64, T_RATIO_N64_64
* 1.61  970603 cao      changed  typedef FIXED_UW_08 T_CL_FLOW
* 1.62  970610 blt      Added T_KPH_PER_SECa, T_PERCENT_MULTa, T_PERCENT_MULTb,
*                             T_PERCENT_MULTc and T_PERCENT_MULTd
* 1.63  970730 mye      Fixed KPAd scaling from 16 to 8
* 1.64  970808 sai      Added TeMIL_OVRD_ST
* 1.65  970923 sn       Added T_AMP for EOSD sensor heater current.
* 1.66  970925 raw 0211
* 1.67  971001 sn       Renamed T_AMP to T_AMPSa.
* 1.68  971001 l.q      Added purge data type.
* 1.69  971104 blt 0249 API cleanup
* 1.71  971218 sai xxxx Added T_PERCENT_n512_512
* 1.72  980116 sai xxxx Added T_RATIO_N32_32 , T_KPH_DIFFa ,
*                       TeVIOS_CRUZ_SWITCH_STATE, TeVIOS_CRUZ_STATE
* 1.73  980207 pdb 0345 misf
*                          Implement Crankshaft Misfire Diagnostic
*                          -Added type T_HIRES_CLKTCKS_LONGa,
*                           T_HIRES_CLKTCKS_LONGb, and T_PERCENTb_OR_KPAa for
*                           the Misfire and Tooth Error Correction diagnostics
* 1.76  980215 blt 0324 VIOS/HWIO cleanup
* 1.77  980419 rjk 0402 Added: T_RATIO_0_2_LONG, TeTECD_REASON_FOR_DELAY
* 1.77  980419 pdb 0324 Added TeRR_HARDWARE_SOURCE enumeration
* 1.77  980419 blt 0475 Merge Offline node 001 into Lecc partition
* 1.79  980514 sai xxxx Moved T_GRAMSb & T_TIME_SEC_P5 from ectdpall.h
* 1.79  980514 chl 0413 Implement Idle Catalyst Monitor
* 1.79  980514 mhb 0469 Enhanced evaporative diagnostic - Phase 1.
* 1.79  980514 l.q 0468evap Added the interface with OBD2 evap.
* 1.79  980514 blt 0486 Merge offline partition node 024 into Lecc node 278
* 1.81  980701 l.q 0574 Added T_GRAMS_FUEL
* 1.82  980720 sai 0602 Added definitions for the Torque subsystem:
*                         T_NEWTON_METER, T_KILO_WATT, T_METER_0_4,
*                         T_KILOGRAM, T_NM_RPM_S_PER_GM
* 1.83  980720 lq  0598 Added T_HERTZa
* 1.84  980820 sai 0641 Added T_ANGLEa_N2048_2047
*
* -- Core Revision History: --
*
* 1.3   980721 saf      Merge LECC Node 304 to the CORE Software
*
* (Merge in lecc node 326)
*
* 1.4   980720 lq  0598 Added T_HERTZa
* 1.4   980820 sai 0641 Added T_ANGLEa_N2048_2047
* 1.4   980917 blt 0081 Added T_GRAMS_PER_SECc, T_GRAMS_CYL_0_16
* 1.4   981205 raw 0128 Added T_RATIO_N1_1
*
* (End merge)
*
* 1.8   990125 wei      Added 8-bit base data types (FIXED_UB & FIXED_SB)
*       990125 wei 0147 Added 8-bit fixed data type T_NEWTON_METER_BYTE
*       990127 wei 0147 Added 8-bit fixed data type T_ANGLEa_BYTE
*       990129 wei 0147 Added 8-bit fixed data type T_RATIO_0_2_BYTE
*                       & T_ANGLEa_BYTEa
* 1.5   981013 raw 0034 Returnless Fuel.
* 1.8   990204 arr 0149 Merged in LECC node 375 containing the following
*                       change(s):
*       981009 sai 0655 Torque mods for ESP and A/T
*       980917 as  0695 Added T_RATIO_N256_256
*       981016 sai 0555 Added TeVIOS_CRUZ_SWITCH_TYPE for Cruise Input diag
*       981021 kan 0573 Changed TeTECD_REASON_FOR_DELAY to ...DISABLE,
*                       added CeTECD_OTR_VEHICLE_SPEED_RANGE to above enum.
*       981023 rjc 0382 Implement odometer functionality.
*       981117 woz 0478 Removed TeMIL_OVRD_ST enum.
*       981122 as  0746 Added T_KPH_PER_SEC_N64_64 & T_KPH_SEC_SEC_N32_32
*                       for Road Speed Kalman Filtering
*       981207 wei 0653 Added T_HERTZc
*       990216 lq  0815 Corrected typedef in T_PERCENTc
* 1.9   990325 gps 0161 Added FIXED_UB_03, T_AFR_BYTE,
*                             FIXED_SB_01, T_ANGLEa_BYTEa
*                             FIXED_UB_00, T_ANGLEa_BYTE, T_NEWTON_METER_BYTE
*                             FIXED_UB_07, T_RATIO_0_2_BYTE
* 1.10  990407 ajc 0162 Added FIXED_UB_08 and T_PERCENTd_BYTE.
*                  0163 Added FIXED_UB_01 and T_KPAa_BYTE.
*                  0164 Added FIXED_UB_04 and T_GRAMS_PER_SECc_BYTE
*                  0165 Added FIXED_UB_07 and T_PERCENT_MULTa_BYTE.
* 1.11  990805 ajk 0302 Merged in Proto2 node 050 (cp2050f0) containing the
*                        following change(s):
*       990612 gps 0973 Corrected T_LITER definition (FIXED_UW_10->FIXED_UW_08)
*                       Deleted wrong defined and unused type T_GRAM_FUEL
*                       Corrected T_TIME_SEC_P00781 definition
*                         (FIXED_UW_06->FIXED_UW_07)
*                       Corrected V_KPH_SEC_SEC_N32_32 definition
*                         ((INTEGER)((val)*512)->(INTEGER)((val)*1024))
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   000714 woz 0883 Merged modifications implemented between Core (EMSDC1a)
*                        nodes 32 and 53:
*       000131 gps 0580 Updated EVPD subsystem (based on MR140 node 101) into
*                        CORE node 31 containing the following change(s):
*                        Added T_MIN & T_MIN_LPC definitions.
*       000323 kan 0678 Integrate Daewoo RSM's:
*                       0425 Modified enum TeTECD_REASON_FOR_DISABLE:
*                            Added   CeTECD_EOL_TEST_FAILED_THIS_KEY_CYCLE
*                            Removed CeTECD_MAX_SAMPLES_LEARNED
*                       0424 Added FIXED_SL_15 T_RATIO_N65535_65536_LONG for
*                            use in TECD calculation to validate tooth
*                            error factors
*                       0501 Added TeTECD_TEST_PASS_FAIL_STATUS
*       000328 kan 0682 Integrate Daewoo RSM's:
*                       0281 Modified type TeTBL_SWITCH_VAC_EGR
*                            WAS: CeVACUUM
*                                 CeEGR_PER
*                            IS:  CeMANIFOLD_VACUUM
*                                 CePERCENT_EGR
*       000412 wei 0699 Added special data type T_RATIO_Cal_0_256 for
*                        calibration. Note: T_RATIO_Cal_0_256 should ONLY be
*                        used for Calibration data type to reduce multiplication
*                        by 100 operation for thruput saving.
*       000602 raw 0571 Add T_AFR_a, T_NEWTON_METERa, T_JOULE_PER_MILLIGRAM
*                        T_LITERa, T_MILLIGRAMSb, T_SECONDSa and
*                        T_GRAMS_PER_SEC_LONG for torque
*       000510 as  0500 Added data type for SAID diagnostic:
*                        T_GRAM_SEC_DIFF
* 1.3   000724 mhb 0840 Added T_MIN and T_MIN_LPC for model base clt and LPC
* 1.4   000928 jbn 1027 Modified type TeVIOS_CRUZ_SWITCH_TYPE.
*                       Removed unnessasary #include #if
*                       Modified as part of RSM 0481 integration.
* 1.5   001002 gps 1029 VCPS - Modular Version of Cam Phasing.
*                       Added T_CAMPHI, T_PHI_PER_SEC, T_RATIO_N16_16.
* 1.6   000614 jh  0817 Add DIG fuel pressure control MPA types
*                        T_MPA, T_PERCENT_PER_MPA, T_MPA_DIFF.
* 1.7   000925 caw 0397 Added T_VOLTf, T_AFRd, and T_MILLISECONDSd
*                       for WRAF O2.
* 1.8   001031 woz 0816 Changed T_INJECT_ANGLE to T_CRANK_ANGLE.
*                       Added T_CRANK_ANGLEa, T_AFRa, T_GRAMS_0_2,
*                        T_MILLISECONDSe data types and TeCYLINDER enum.
* 1.9   020901 gps 1246 Compiler Error/Warning Corrections
*                        to Simplify Transition DIAB 4.0b -> 4.4x.
* 1.10  010312 woz 1276 Added T_NEWTON_METERb.
* 1.11  010315 kan 1227 Added T_MILLISECONDSb_DIFF.
* 1.12  010330 kan 1313 Added T_AFR_DIFF.
* 1.13  010614 caw 1267 Added T_MILLIGRAMSe T_MILLISECONDSf T_MILLIGRAMSf
*                       and T_GRAMS_PER_SECf
* 1.14  010717 cj  0511 Removed custom enumerations for TECD and RRID
*                        TECD Subsystem enumerations are now in tecdstyp.h.
*                        RRID Subsystem enumerations were obsolete and have
*                        been removed.
*              cj  0511 Merged changes from Daewoo Node 96f0.  The collection
*                        of changes included the following RSMs:
*                        0511, 0512, 0626, 0693, 0773, 0782, 0884, 0888,
*                        0949, 0984, 1002, 1008, 1077, 1176, 1178, 1298,
*                        and 1314.
* 1.18 011203 mhb 1527  Commented out the following enumerations  Moved to fuel
*                        TeFUEL_CUT_OFF,
*                        TePRIME_PULSE_MODE,
*                        TeTRIM_PULSE_MODE
*                       Moved to fuelptyp.h
* 1.19  011204 caw 1558 Removed: TeVGIS_MODE
*                  1564 Added: T_CM3a
* 1.20  020207 woz 1629 Changed V_JOULE_PER_MILLIGRAM definition to use (WORD)
*                        typecast instead of (INTEGER).
* 1.20  020211 gps 1637 VCPS : Added T_W_PSI_0_1024 definition.
* 1.21  020409 wei 1367 Added: T_MILLIGRAMS_N512_512 for CL torque control.
*       020417 wei 1367 Added: T_NEWTON_METER_N128_128 for CL torq control.
* 1.22  020525 gps 1685 Fuel Tank Pressure : added T_VAC_PER_VREF_N32_32.
* 1.23  020621 caw 0579 Added new time in seconds types:
*                        T_SECONDS_0_4
*                        T_SECONDS_0_8
* 1.24  020819 gan 1617 Added typedef enum TeELCL_FAN_TYPE
* 1.25  020619 gps 1906 FUEL - Improve C/L Fuel And Stoichiometer AFR
*                        Enable Criteria by Use of Integrated Airflow.
*                       Added T_GRAMS_0_4096.
* 1.26  021016 caw 1607 Removed: TeELCL_FAN_TYPE
* 1.27  021029 kan 2027 Transmission software merge.
* 5.2   021024 hdb 2066 Add line pressure control definitions:
*                         T_AMPS_0_8 & T_AMPS_N4_4
* 5.3   021024 hdb 2066 Add line pressure control definitions:
*                         T_RATIO_N8_8 (moved from viossmbc.h)
* 5.4   030320 gps 2543 Reintroduction of Air Learn Algorithm.
*                       Added T_GRAMS_PER_SEC_0_1024 & T_KILOMETERS_0_512.
* 5.3.1.1
*      030319 elav 2556 Added T_KILONEWTON for torque_based cruise control.
*            (TCI)
* 5.6   030429 arr 2615 Correct macro V_AMPS_N4_4 to use INTEGER instead of
*                        WORD for signed type.
* 5.7  030606 ses  2806 Added T_KPA_0_32768 for use in Power Steering Pressure
*                      logic.
* tci_pt3#5.7
*      030430 ksr 2212 Added T_PERCENTj for EVAP Purge Concentration (TCI).
* tci_pt3#5.7
*      030430 ksr 2212 Added T_PERCENTj for EVAP Purge Concentration (TCI).
* 5.10 030616 hdb 2827 Correct values for T_AMPS_N4_4
*
** 02/12/04		feqi		242
* + Correct test findings for reuse module MISF.  
*   - Added systpcfg.h.
*
* 07/22/05		LShoujun    mt20u2#4
* + Downsize Misfire threshold table and limit History Counter update.  
*   - Defined T_LOWRES_CLKTCKS_WORD.
*
*****************************************************************************/

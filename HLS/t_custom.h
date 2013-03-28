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
 * Copyright 1995-2011, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     tcb_pt1#4/incl/t_custom.h/kok_pt2#28.16.6 %
 * %date_created:  Wed Oct  5 11:06:00 2011 %
 * %version:       kok_pt2#28.16.6 %
 * %derived_by:    zzmkdw %
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
typedef SHORTINT FIXED_SB_00;
#define V_SB_00(val) (SHORTINT)(val)
#define S_SB_00 0

typedef SHORTINT FIXED_SB_01;
#define V_SB_01(val) (SHORTINT)((val)*2)
#define S_SB_01 1

typedef SHORTINT FIXED_SB_04;
#define V_SB_04(val) (SHORTINT)((val)*16)
#define S_SB_04 4

typedef SHORTINT FIXED_SB_06;
#define V_SB_06(val) (SHORTINT)((val)*64)
#define S_SB_06 6

typedef SHORTINT FIXED_SB_07;
#define V_SB_07(val) (SHORTINT)((val)*128)
#define S_SB_07 7

/*****************************************************************************/
/* Unsigned Byte Fixed Point Types                                           */
/*****************************************************************************/
typedef BYTE FIXED_UB_00;
#define V_UB_00(val) (BYTE)(val)
#define S_UB_00 0

typedef BYTE FIXED_UB_01;
#define V_UB_01(val) (BYTE)((val)*2)
#define S_UB_01 1

typedef BYTE FIXED_UB_02;
#define V_UB_02(val) (BYTE)((val)*4)
#define S_UB_02 2

typedef BYTE FIXED_UB_03;
#define V_UB_03(val) (BYTE)((val)*8)
#define S_UB_03 3

typedef BYTE FIXED_UB_04;
#define V_UB_04(val) (BYTE)((val)*16)
#define S_UB_04 4

typedef BYTE FIXED_UB_05;
#define V_UB_05(val) (BYTE)((val)*32)
#define S_UB_05 5

typedef BYTE FIXED_UB_06;
#define V_UB_06(val) (BYTE)((val)*64)
#define S_UB_06 6

typedef BYTE FIXED_UB_07;
#define V_UB_07(val) (BYTE)((val)*128)
#define S_UB_07 7

typedef BYTE FIXED_UB_08;
#define V_UB_08(val) (BYTE)((val)*256)
#define S_UB_08 8

typedef BYTE FIXED_UB_09;
#define V_UB_09(val) (BYTE)((val)*512)
#define S_UB_09 9

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
typedef FIXED_SW_03     T_KPA_SECc;
#define V_KPA_SECc(val) (INTEGER)((val)*8)
#define S_KPA_SECc      3

/* power-of-two range: [-128, 128) */
typedef FIXED_SW_08     T_KPA_SECd;
#define V_KPA_SECd(val) (INTEGER)((val)*256)
#define S_KPA_SECd      8

/* power-of-two range: [-32, 32) */
typedef FIXED_SW_10                 T_GRAMS_PER_SECd;
#define V_GRAMS_PER_SECd(val)       (INTEGER)((val)*1024)
#define S_GRAMS_PER_SECd            10

/* power-of-two range, grams per second range [-64, 64) */
typedef FIXED_SW_09                 T_GRAMS_PER_SEC_N64_64;
#define V_GRAMS_PER_SEC_N64_64(val) (INTEGER)((val)*512)
#define S_GRAMS_PER_SEC_N64_64      9

/* power-of-two range: [0, 64) */
typedef FIXED_UW_10                 T_GRAMS_PER_SECc;
#define V_GRAMS_PER_SECc(val)       (WORD)((val)*1024)
#define S_GRAMS_PER_SECc            10

/* power-of-two range: [0, 16)  Res: 0.0625 */
typedef FIXED_UB_04                 T_GRAMS_PER_SECc_BYTE;
#define V_GRAMS_PER_SECc_BYTE(val)  (BYTE)((val)*16)
#define S_GRAMS_PER_SECc_BYTE       4

/* power-of-two range: [0, 4096) */
typedef FIXED_UL_20                 T_GRAMS_PER_SEC_LONG;
#define V_GRAMS_PER_SEC_LONG(val)   (LONGWORD)((val)*1048576L)
#define S_GRAMS_PER_SEC_LONG        20

/* power-of-two range: [0, 16) */
typedef FIXED_UW_12             T_MILLISECONDSf;
#define V_MILLISECONDSf(val)    (WORD)((val)*4096)
#define S_MILLISECONDSf         12

/* power-of-two range: [0, 256) */
typedef FIXED_UL_24             T_MILLISECONDSf2;
#define  V_MILLISECONDSf2(val)  (LONG)((val)*16777216)
#define  S_MILLISECONDSf2       24

/* power-of-two range: [-256, 256] */
typedef FIXED_SW_07             T_GRAMS_PER_SECf;
#define V_GRAMS_PER_SECf(val)  (INTEGER)((val)*128)
#define S_GRAMS_PER_SECf        7

/* power-of-two range: [0, 2048] */
typedef FIXED_UW_05             T_MILLIGRAMSe;
#define V_MILLIGRAMSe(val)      (WORD)((val)*32)
#define S_MILLIGRAMSe           5

/* power-of-two range: [-8192, 8192] */
typedef FIXED_SL_18             T_MILLIGRAMSf;
#define V_MILLIGRAMSf(val)      (LONGINT)((val)*262144L)
#define S_MILLIGRAMSf           18

/* time in seconds (16-bits, LSB=0.0039 sec), range: [0, 255.996] */
typedef FIXED_UW_16           T_SECOND_0_1 ;
#define V_SECOND_0_1(val)     (WORD)((val)*(65536))
#define S_SECOND_0_1          16

/* power-of-two range: [-2048, 2048) */
typedef FIXED_SW_04           T_DEG_Kc;
#define V_DEG_Kc(val)         (INTEGER)((val)*16)
#define S_DEG_Kc              4

/* power-of-two range: [-64 64) Res: 0.001953125 */
typedef FIXED_SW_09 T_DEG_Ke;
#define V_DEG_Ke(val) (LONGINT)((val)*512)
#define S_DEG_Ke 9

/*  time in minutes - used by low power counter */
/* power-of-two range: (0, 65535) */
typedef FIXED_UW_00           T_MIN;
#define V_MIN(val)            (WORD)((val)*1)
#define S_MIN                 0

/*  time in 1/4 minutes  */
/* power-of-two range: [0, 16384) */
typedef FIXED_UW_02           T_P25MIN;
#define V_P25MIN(val)         (WORD)((val)*4)
#define S_P25MIN              2

/*#include "systpcfg.h"*/
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

typedef FIXED_UW_07             T_FUEL_TANK_LITER;
#define V_FUEL_TANK_LITER(val)  (WORD)(val*128)
#define S_FUEL_TANK_LITER       7

typedef FIXED_UW_08            T_GRAM_SEC;
#define V_GRAM_SEC(val)        (WORD)(val*256)
#define S_GRAM_SEC             8

typedef FIXED_UL_08            T_GRAM_SEC_LONG;
#define V_GRAM_SEC_LONG(val)   (LONGWORD)(val*256)
#define S_GRAM_SEC_LONG        8

typedef FIXED_UW_02            T_HERTZ_MAF;
#define V_HERTZ_MAF(val)       (WORD)(val*4)
#define S_HERTZ_MAF            2

typedef FIXED_SW_08                T_MILLISECONDS_DIFFb;
#define V_MILLISECONDS_DIFFb(val)  (INTEGER)(val*256)
#define S_MILLISECONDS_DIFFb       8

typedef FIXED_UW_06            T_CRANK_ANGLE;
#define V_CRANK_ANGLE(val)     (WORD)((val)*64)
#define S_CRANK_ANGLE          6

typedef FIXED_SW_06            T_CRANK_ANGLEa;
#define V_CRANK_ANGLEa(val)    (INTEGER)((val)*64)
#define S_CRANK_ANGLEa         6

/* power-of-two range: [0, 128) Res: 0.5 */
typedef FIXED_UB_07             T_CRANK_ANGLE_BYTE;
#define V_CRANK_ANGLE_BYTE(val) (BYTE)((val)*2)
#define S_CRANK_ANGLE_BYTE      1

/* power-of-two range: [0, 64) Res: 0.25 */
typedef FIXED_UB_02             T_CRANK_ANGLE_0_64;
#define V_CRANK_ANGLE_0_64(val) (BYTE)((val)*4)
#define S_CRANK_ANGLE_0_64      2

typedef FIXED_SW_00            T_FUEL_INT;
#define V_FUEL_INT(val)        (INTEGER)((val))
#define S_FUEL_INT             0

typedef FIXED_UW_08            T_CL_FLOW;
#define V_CL_FLOW(val)         (WORD)((val)*256)
#define S_CL_FLOW              8

typedef FIXED_SW_11            T_AFR_DIFF;
#define V_AFR_DIFF(val)        (INTEGER)((val)*2048)
#define S_AFR_DIFF             11

/* power-of-two range: [0, 32) Res: 0.00048828125 */
typedef FIXED_UW_11            T_AFR;
#define V_AFR(val)             (WORD)((val)*2048)
#define S_AFR                  11

/* power-of-two range: [0, 16) Res: 2^4/2^32 = 0.0000000037252902984619140625 */
typedef FIXED_UL_28            T_AFR_0_16_LONG;
#define V_L_AFR_0_16(val)      (WORD)((val)*268435456l)
#define S_L_AFR_0_16           28

typedef FIXED_UW_10            T_AFRa;
#define V_AFRa(val)            (WORD)((val)*1024)
#define S_AFRa                 10

/* power-of-two range: [-32, 32) Res: 0.0009765625 */
typedef FIXED_SW_10            T_AFRd;
#define V_AFRd(val)            (INTEGER)((val)*1024)
#define S_AFRd                 10

/* power-of-two range: [0, 4096) */
typedef FIXED_UW_04           T_OHMS_0_4096;
#define V_OHMS_0_4096(val)    (WORD)((val)*16)
#define S_OHMS_0_4096          4

/* power-of-two range: [0, 8) Res: 2^3/2^16 = 0.0001220703125 */
typedef FIXED_UW_13            T_Lambda;
#define V_Lambda(val)          (WORD)((val)*8192.0)
#define S_Lambda               13
#define CfMIN_T_Lambda         ( V_Lambda(0) )
#define CfMAX_T_Lambda         ( V_Lambda(7.9998779296875) )

typedef FIXED_SW_13            T_DELIVD_CL_CORR;
#define V_DELIVD_CL_CORR(val)  (INTEGER)((val)*8192)
#define S_DELIVD_CL_CORR       13

 /* power-of-two range: [-4, < 4] Res:8/65536 */
typedef FIXED_SW_13                      T_METER_PER_SEC_SQ_N4_4;
#define V_METER_PER_SEC_SQ_N4_4(val)    (INTEGER)((val)*8192)
#define S_METER_PER_SEC_SQ_N4_4         13

#define CfMAX_T_METER_PER_SEC_SQ_N4_4   V_METER_PER_SEC_SQ_N4_4(3.9998779296875)

typedef FIXED_UW_13            T_INJECT_FLOW;
#define V_INJECT_FLOW(val)     (WORD)((val)*8192)
#define S_INJECT_FLOW          13

typedef FIXED_UW_16             T_FUEL_RES;
#define V_FUEL_RES(val)         (WORD)((val)*65536)
#define S_FUEL_RES              16

typedef FIXED_SW_08             T_DEG_PER_RPM;
#define V_DEG_PER_RPM(val)      (INTEGER)((val)*256)
#define S_DEG_PER_RPM           8

/* power-of-two range: [0, 2040) */
#define V_RPM_0_2040(val)       (BYTE)((val)*0.125)
#define S_RPM_0_2040            -3

/* power-of-two range: [-512, 512) */
#define V_RPM_BYTE_N512_512(val)  (SHORTINT)((val)*0.25)
#define S_RPM_BYTE_N512_512       -2

/* RPM change over a 46.86 msec window (rpm/46.86 msec) */
/* range: [-256, 255.992187]                            */
typedef FIXED_SW_07              T_RPM_PER_50_MSECa;
#define V_RPM_PER_50_MSECa(val)  (INTEGER)((val)*128)
#define S_RPM_PER_50_MSECa       7

/* electronic potential (volts), range: [0, 1] */
typedef FIXED_UB_08             T_VOLT_0_1_BYTE ;
#define V_VOLT_0_1_BYTE(val)    (BYTE)((val)*(256))
#define S_VOLT_0_1_BYTE          8

/* electronic potential (volts), range: [0, 128) */
typedef FIXED_UW_09             T_VOLTa;
#define V_VOLTa(val)            (WORD)((val)*512)
#define S_VOLTa                 9

/* electronic potential (volts), range: [0, 16] */
typedef FIXED_UW_12             T_VOLT_0_16;
#define V_VOLT_0_16(val)        (WORD)((val)*4096)    // for value in volts
#define S_VOLT_0_16             12

/* electronic potential (volts), range: [0, 31.999] */
typedef FIXED_UW_11             T_VOLTb;
#define V_VOLTb(val)            (WORD)((val)*2048)    // for value in volts
#define V_VOLTb_mv_0_32000(val) (WORD)(((val)*2048)/1000)  // for value in mv
#define S_VOLTb                 11

/* electronic potential (volts), range: [0, 63.999] */
typedef FIXED_UW_10             T_VOLTg;
#define V_VOLTg(val)            (WORD)((val)*1024)
#define S_VOLTg                 10


/* conversion factor (rpm/volt), range: [0, 127.998] */
typedef FIXED_UW_09           T_RPM_PER_VOLTa;
#define V_RPM_PER_VOLTa(val)  (WORD)((val)*512)
#define S_RPM_PER_VOLTa       9


/* (inverse)voltage slew rate (us/volt), range: [0, 256) */
typedef FIXED_UW_08 T_USEC_PER_VOLTb;
#define V_USEC_PER_VOLTb(val)  (WORD)((val)*256)
#define S_USEC_PER_VOLTb 8


/* pressure in mega pascals (MPa), range: [0, 31.999] */
typedef FIXED_UW_11             T_MPA;
#define V_MPA(val)              (WORD)((val)*2048)
#define S_MPA                   11

/* pressure in mega pascals (MPa), range: [0, 31.999] */
typedef FIXED_UB_03     T_MPA_BYTE;
#define V_MPA_BYTE(val) V_UB_03(val)
#define S_MPA_BYTE      S_UB_03

typedef FIXED_UW_15             T_PERCENT_PER_MPA;
#define V_PERCENT_PER_MPA(val)  (WORD)((val)*32768)
#define S_PERCENT_PER_MPA       15

typedef FIXED_SW_12             T_MPA_DIFF;
#define V_MPA_DIFF(val)         (INTEGER)((val)*4096)
#define S_MPA_DIFF              12
#define CfMAX_T_MPA_DIFF        (V_MPA_DIFF(7.999755859375))

typedef FIXED_SB_04             T_MPA_DIFF_BYTE;
#define V_MPA_DIFF_BYTE(val)    V_SB_04(val)
#define S_MPA_DIFF_BYTE         S_SB_04

/* pressure in kilo pascals (kPa), range: [-4096, 4095.875] */
typedef FIXED_SW_03  T_KPAd;
#define V_KPAd(val)  (INTEGER)((val)*8)
#define S_KPAd 3

/* Pressure in kilo pascals (kpa), range: [-16384, 16384] */
typedef FIXED_SW_02 T_KPA_N16384_16384;
#define V_KPA_N16384_16384(val)  (INTEGER)(val*2)
#define S_KPA_N16384_16384 1

/* Pressure in kilo pascals (kpa), range: [0, 32768] */
typedef FIXED_UW_01         T_KPA_0_32768;
#define V_KPA_0_32768(val)  (WORD)((val)*2)
#define S_KPA_0_32768       1

/* Pressure in BAR range: [0, 511.9921] */
typedef FIXED_UW_07         T_BAR_0_512;
#define V_BAR_0_512(val)    (WORD)((val)*128)
#define S_BAR_0_512          7


/* time in seconds (16-bits, LSB=0.00390625 sec), range: [0, 256) */
typedef FIXED_UW_08             T_SECOND_P0039 ;
#define V_SECOND_P0039(val)     (WORD)((val)*(256))
#define S_SECOND_P0039          8

/* time in seconds (16-bits, LSB=1/65536 sec), range: [0, 1) */
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

/* time in seconds (16-bits, LSB=0.125 msec), range: [0, 8191.875] */
typedef FIXED_UW_03             T_TIME_SEC_P125;
#define V_TIME_SEC_P125(val)   (WORD)((val)*8)
#define S_TIME_SEC_P125         3


/* time in seconds (16-bits, LSB=0.000015258), range: [0, 0.999] */
typedef FIXED_UW_16             T_TIME_SEC_P000015;
#define V_TIME_SEC_P000015(val) (WORD)((val)*65536)
#define S_TIME_SEC_P000015      16

/* time in milliseconds (16-bits, LSB=1 ms), range: [0, 65535] */
typedef FIXED_UW_00             T_TIME_MS_0_65535 ;
#define V_TIME_MS_0_65535(val)   (WORD)((val)*1)
#define S_TIME_MS_0_65535        0

/* distance in inches, range [0,256)   */
typedef FIXED_UW_08             T_INCHES;
#define V_INCHES(val)           (WORD)((val)*256)
#define S_INCHES                8

/* distance in inches, range [0,512)   */
typedef FIXED_UW_07                 T_INCHES_METERSa;
#define V_INCHES_METERSa(val)       (WORD)((val)*128)
#define S_INCHES_METERSa            7

/*  range [0,65535)   */
typedef FIXED_UW_00               T_RPM_KPH_MPHb;
#define V_RPM_KPH_MPHb(val)       (WORD)((val))
#define S_RPM_KPH_MPHb            0

/* distance in meters, range [0,256)   */
typedef FIXED_UW_08             T_METERS;
#define V_METERS(val)           (WORD)((val)*256)
#define S_METERS                8

/* distance in millimeters, range [0,8192)   */
typedef FIXED_UW_03             T_MILLIMETERS;
#define V_MILLIMETERS(val)      (WORD)((val)*8)
#define S_MILLIMETERS            3

/* distance in meters, range [0,2)   */
typedef FIXED_UW_15 T_METERS_0_2;
#define V_METERS_0_2(val) (WORD)(val*32768)
#define S_METERS_0_2 15

/* distance in meters, range [0,256)   */
typedef FIXED_UW_08             T_METER_0_256;
#define V_METERS(val)           (WORD)((val)*256)
#define S_METERS                8

/* distance in meters, range [0,32)   */
typedef FIXED_UW_11             T_METERS_0_32;
#define V_METERS_0_32(val)     (WORD)((val)*2048)
#define S_METERS_0_32           11

/* distance in meters, range [0,32)   */
typedef FIXED_UW_09             T_METERS_0_128;
#define V_METERS_0_128(val)     (WORD)((val)*512)
#define S_METERS_0_128          9

/* distance in meters, range [0,2048)   */
typedef FIXED_UW_05             T_METERS_0_2048;
#define V_METERS_0_2048(val)    (WORD)((val)*32)
#define S_METERS_0_2048         5

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

/* power-of-two range: [0,128)*/
typedef FIXED_UB_01 T_KILOMETERSg;
#define V_KILOMETERSg(val) (BYTE)((val)*2)
#define S_KILOMETERSg 1

/* power-of-two range: [0,256)*/
typedef FIXED_UB_00 T_KILOMETERSh;
#define V_KILOMETERSh(val) (BYTE)(val)
#define S_KILOMETERSh 0

/* Res:   0.007812500000000         */
/* Range: [0, 512)                  */
typedef T_W_RANGE_0_512         T_KILOMETERS_0_512;
#define V_KILOMETERS_0_512(val) V_W_RANGE_0_512(val)
#define S_KILOMETERS_0_512      S_W_RANGE_0_512

/* Res:   1.000000000000000         */
/* Range: [0, 4294967296)           */
typedef T_L_RANGE_0_4294967296  T_L_KILOMETERS;
#define V_L_KILOMETERS(val)     V_L_RANGE_0_4294967296(val)
#define S_L_KILOMETERS          S_L_RANGE_0_4294967296

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

/* acceleration, G's, range [-32, +32)  resolution 0.0009765625 g */
typedef  FIXED_SW_10            T_ACCEL_IN_G_N32_32;
#define  V_ACCEL_IN_G_N32_32(val) (INTEGER)((val)*1024)
#define  S_ACCEL_IN_G_N32_32    10

/* acceleration, G's, range [0, 64)     resolution 0.0009765625 g */
typedef  FIXED_UW_10            T_ACCEL_IN_G_0_64;
#define  V_ACCEL_IN_G_0_64(val) (WORD)((val)*1024)
#define  S_ACCEL_IN_G_0_64      10

/* acceleration, G's, range [0, +1024] resolution 0.03125 g */
typedef FIXED_UW_06             T_ACCEL_IN_G_0_1K;
#define V_ACCEL_IN_G_0_1K(val)  (WORD)((val)*64)
#define S_ACCEL_IN_G_0_1K       6

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

/* percent/100, range: [0, 2)  Res: 0.0078125 */
typedef FIXED_UB_07           T_PERCENTa_BYTE;
#define V_PERCENTa_BYTE(val)  (BYTE)((val)*1.28)
#define S_PERCENTa_BYTE       7

/* power-of-two range: [0, 127.5) Res: 0.5 */
typedef FIXED_UB_01             T_PERCENTh_B;
#define V_PERCENTh_B(val)       (BYTE)((val)*2)
#define S_PERCENTh_B             1

/* power-of-two range: [0, 32) */
typedef FIXED_UB_03          T_PERCENTh_0_32;
#define V_PERCENTh_0_32(val) (BYTE)((val)*8)
#define S_PERCENTh_0_32      3

/* percent/100, range: [-1, <1)  resolution: 0.0078 */
typedef FIXED_SB_07             T_PCT_DIFFA_BYTE;
#define V_PCT_DIFFA_BYTE(val)   (SHORTINT)((val)*1.28)
#define S_PCT_DIFFA_BYTE 7

/* percent/100, range: [-1,1) */
typedef FIXED_SW_15             T_PERCENT_DIFFd;
#define V_PERCENT_DIFFd(val)    (INTEGER)((val)*327.68)
#define S_PERCENT_DIFFd 15

/* percent/100, range: [0, 2) */
typedef FIXED_UW_15            T_PERCENT_MULTa;
#define V_PERCENT_MULTa(val)   (WORD)((val)*32768)
#define S_PERCENT_MULTa        15
#define CfMAX_T_PERCENT_MULTa  (V_PERCENT_MULTa(1.999969482421875))

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

/* Res:   0.390006250000000       */
/* Range: [-128, 128)               */
typedef T_W_RANGE_N128_128          T_W_PERCENTa_N128_128;
#define V_W_PERCENTa_N128_128(val)  V_W_RANGE_N128_128((val)*0.01)
#define S_W_PERCENTa_N128_128       S_W_RANGE_N128_128

/* Res:   0.195312500000000       */
/* Range: [-25, 25)               */
/* Size:  1B                      */
typedef T_B_RANGE_Nr4_r4            T_B_PERCENT_N25_25;
#define V_B_PERCENT_N25_25(val)     V_B_RANGE_Nr4_r4((val)*0.01)
#define S_B_PERCENT_N25_25          S_B_RANGE_Nr4_r4

/* Res:   0.390006250000000       */
/* Range: [-50, 50)               */
typedef T_B_RANGE_Nr2_r2            T_B_PERCENTa_N50_50;
#define V_B_PERCENTa_N50_50(val)    V_B_RANGE_Nr2_r2((val)*0.01)
#define S_B_PERCENTa_N50_50         S_B_RANGE_Nr2_r2

/* Data types defined by Airflow Subsystem */
/* power-of-two range [0, 1) precision = 1/65536 = 0.00001525879 */
typedef FIXED_UW_16             T_GRAMS_0_1;
#define V_GRAMS_0_1(val)        (WORD)((val)*65536)
#define S_GRAMS_0_1             16

/* power-of-two range [0, 2) precision = 1/32768 = 0.000030517578125 */
typedef FIXED_UW_15             T_GRAMS_0_2;
#define V_GRAMS_0_2(val)        (WORD)(val*32768)
#define S_GRAMS_0_2             15

/* power-of-two range [0, 4) precision = 1/16384 = 0.00006103515625 */
typedef FIXED_UW_14             T_GRAMS_0_4;
#define V_GRAMS_0_4(val)        (WORD)((val)*16384)
#define S_GRAMS_0_4             14

/* power-of-two range [-1, 1) precision = 1/32768 = 0.000030517578125 */
typedef FIXED_SW_15             T_GRAMS_N1_1;
#define V_GRAMS_N1_1(val)       (INTEGER)((val)*32768)
#define S_GRAMS_N1_1            15

/* power-of-two range [-2, 2) precision = 4/65536 = 0.00006103515625 */
typedef FIXED_SW_14             T_GRAMS_N2_2;
#define V_GRAMS_N2_2(val)       (INTEGER)((val)*16384)
#define S_GRAMS_N2_2            14

/* power-of-two range [-2, 2) precision = 2^2/2^32 = 0.000000000931322574615478515625 */
typedef FIXED_SL_30             T_GRAMS_N2_2_LONG;
#define V_L_GRAMS_N2_2(val)     (LONGINT)((val)*1073741824L)
#define S_L_GRAMS_N2_2          30

/* power-of-two range [0, 4) precision = 2^2/2^32 = 0.000000000931322574615478515625 */
typedef FIXED_UL_30             T_GRAMS_0_4_LONG;
#define V_L_GRAMS_0_4(val)      (LONGWORD)((val)*1073741824L)
#define S_L_GRAMS_0_4           30

typedef FIXED_UW_15             T_GRAMS_CYL_0_2;
#define V_GRAMS_CYL_0_2(val)    (WORD)(val*32768)
#define S_GRAMS_CYL_0_2         15

typedef FIXED_UW_13             T_GRAMS_CYL_0_8;
#define V_GRAMS_CYL_0_8(val)    (WORD)(val*8192)
#define S_GRAMS_CYL_0_8         13

typedef FIXED_UW_12             T_GRAMS_CYL_0_16;
#define V_GRAMS_CYL_0_16(val)   (WORD)(val*4096)
#define S_GRAMS_CYL_0_16        12

typedef T_W_RANGE_0_256         T_GRAMS_0_256;
#define V_GRAMS_0_256(val)      V_W_RANGE_0_256(val)
#define S_GRAMS_0_256           S_W_RANGE_0_256

typedef T_W_RANGE_0_4096        T_GRAMS_0_4096;
#define V_GRAMS_0_4096(val)     V_W_RANGE_0_4096(val)
#define S_GRAMS_0_4096          S_W_RANGE_0_4096

/* power-of-two range: [0, 65536) */
typedef FIXED_UW_00 T_GRAMS_SHRT_0_65536;
#define V_GRAMS_SHRT_0_65536(val) (WORD)(val)
#define S_GRAMS_SHRT_0_65536 0

/* power-of-two range: [0, 65536) */
typedef FIXED_UL_16               T_GRAMS_0_65536;
#define V_GRAMS_0_65536(val)      (LONGWORD)((LONGWORD)val*65536)
#define S_GRAMS_0_65536           16

typedef T_L_RANGE_0_33554432     T_GRAMS_0_33554432;
#define V_GRAMS_0_33554432(val)  V_L_RANGE_0_33554432(val)
#define S_GRAMS_0_33554432       S_L_RANGE_0_33554432

typedef T_L_RANGE_0_2097152      T_AFR_LONG;
#define V_AFR_LONG(val)          V_L_RANGE_0_2097152(val)
#define S_AFR_LONG               S_L_RANGE_0_2097152

typedef FIXED_UW_07             T_DEG_K_0_512;
#define V_DEG_K_0_512(val)      (WORD)(val*128)
#define S_DEG_K_0_512           7

/* power-of-two range [-2, 2) precision = 4/65536 = 0.00006103515625 */
typedef FIXED_SW_14               T_GRAMS_PER_SEC_N2_2;
#define V_GRAMS_PER_SEC_N2_2(val) (INTEGER)((val)*16384)
#define S_GRAMS_PER_SEC_N2_2      14

/* power-of-two range [-2, 2) precision = 4/(65536 * 65536)  */
typedef FIXED_SL_30                T_GRAMS_PER_SEC_N2_2L;
#define V_GRAMS_PER_SEC_N2_2L(val) (LONGINT)((val)*(16384)*(65536))
#define S_GRAMS_PER_SEC_N2_2L      30

/* power-of-two range [0, 1) precision = 1/65536 = 0.00001525879 */
typedef FIXED_UW_16               T_GRAMS_PER_SEC_0_1;
#define V_GRAMS_PER_SEC_0_1(val)  (WORD)((val)*65536)
#define S_GRAMS_PER_SEC_0_1       16

/* power-of-two range [0, 16) precision = 1/4096 = 0.000244140625 */
typedef FIXED_UW_12               T_GRAMS_PER_SEC_0_16;
#define V_GRAMS_PER_SEC_0_16(val) (WORD)((val)*4096)
#define S_GRAMS_PER_SEC_0_16       12

/* power-of-two range [0, 32) precision = 1/2048 = 0.00048828125 */
typedef FIXED_UW_11               T_GRAMS_PER_SEC_0_32;
#define V_GRAMS_PER_SEC_0_32(val) (WORD)((val)*2048)
#define S_GRAMS_PER_SEC_0_32      11

/* power-of-two range: (-256, 256), precision = 1/128 = 0.0078125 */
typedef FIXED_SW_07            T_GRAM_SEC_DIFF;
#define V_GRAM_SEC_DIFF(val)  (INTEGER)((val)*128)
#define S_GRAM_SEC_DIFF       7

/* power-of-two range: [0, 1024) */
typedef FIXED_UW_06 T_GRAMS_PER_SECa;
#define V_GRAMS_PER_SECa(val)  (WORD)((val)*64)
#define S_GRAMS_PER_SECa 6

/* power-of-two range: [0, 8192) */
typedef FIXED_UW_03 T_GRAMS_PER_SEC_0_8192;
#define V_GRAMS_PER_SEC_0_8192(val)  (WORD)((val)*8)
#define S_GRAMS_PER_SEC_0_8192 3

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

/* Tank Vacuum in inches of H2O */
/* power-of-two range: [-32, 32) */
typedef FIXED_SW_10             T_VAC;
#define V_VAC(val)              (INTEGER)((val)*1024)
#define S_VAC                   10
#define CeVAC_MAX               ( 32767/1024 ) /* value to generate 7FFF */

/* Tank Vacuum Slope in inches of H2O */
/* power-of-two range: [-32, 32) */
typedef FIXED_SW_10             T_VAC_PER_SEC;
#define V_VAC_PER_SEC(val)      (INTEGER)((val)*1024)
#define S_VAC_PER_SEC           10

/* Tank Vacuum per %Vref Slope in inches of H2O */
/* power-of-two range: [-32, 32) */
typedef FIXED_SW_10                 T_VAC_PER_VREF_N32_32;
#define V_VAC_PER_VREF_N32_32(val)  (INTEGER)((val)*1024)
#define S_VAC_PER_VREF_N32_32       10

/* Tank Vacuum per %Vref Slope in inches of H2O */
/* power-of-two range: [-64, 64) */
typedef FIXED_SW_09                 T_VAC_PER_VREF_N64_64;
#define V_VAC_PER_VREF_N64_64(val)  (INTEGER)((val)*512)
#define S_VAC_PER_VREF_N64_64       9

/* power-of-two range: [0, 256) */
typedef FIXED_UW_08 T_SECONDSa;
#define V_SECONDSa(val)  (WORD)((val)*256)
#define S_SECONDSa 8

/* time in seconds (16-bits) range: [0, 1) */
typedef FIXED_UW_16            T_SECONDS_0_1;
#define V_SECONDS_0_1(val)     (WORD)((val)*(65536))
#define S_SECONDS_0_1          16

/* time in seconds (16-bits, LSB=0.0000610 sec), range: [0, 3.99] */
typedef FIXED_UW_14           T_SECONDS_0_4;
#define V_SECONDS_0_4(val)     (WORD)((val)*(16384))
#define S_SECONDS_0_4          14

/* time in seconds (16-bits, LSB=0.0000610 sec), range: [-2, 1.99] */
typedef FIXED_SW_14           T_SECONDS_N2_2;
#define V_SECONDS_N2_2(val)   (INTEGER)((val)*(16384))
#define S_SECONDS_N2_2        14

/* time in seconds (16-bits, LSB=0.00024414 sec), range: [-8, 7.99] */
typedef FIXED_SW_12           T_SECONDS_N8_8;
#define V_SECONDS_N8_8(val)   (INTEGER)((val)*(4096))
#define S_SECONDS_N8_8        12

/* time in seconds (16-bits, LSB=0.0001220 sec), range: [0, 7.99] */
typedef FIXED_UW_13           T_SECONDS_0_8;
#define V_SECONDS_0_8(val)     (WORD)((val)*(8192))
#define S_SECONDS_0_8          13

/* time in seconds (16-bits, LSB=0.0009765625 sec), range: [0, 64) */
typedef FIXED_UW_10           T_SECONDS_0_64;
#define V_SECONDS_0_64(val)   (WORD)((val)*(1024))
#define S_SECONDS_0_64        10

/* time in seconds (16-bits) range: [0, 512) Resolution = 0.0078125*/
typedef FIXED_UW_07 T_SECONDS_0_512;
#define V_SECONDS_0_512(val) (WORD)((val)*128)
#define S_SECONDS_0_512 7

/* time in seconds (16-bits) range: [-512, 512) Resolution = 0.015625*/
typedef FIXED_SW_06 T_SECONDS_N512_512;
#define V_SECONDS_N512_512(val) (INTEGER)((val)*64)
#define S_SECONDS_N512_512 6

/* time in seconds (16-bits) range: [0, 1024) Resolution = 0.0156 */
typedef FIXED_UW_06 T_SECONDS_0_1024;
#define V_SECONDS_0_1024(val)  (WORD)((val)*64)
#define S_SECONDS_0_1024 6

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

typedef FIXED_UL_15 T_MILLISECONDSa_LONG;
#define V_MILLISECONDSa_LONG(val) (LONGWORD)(val*32768)
#define S_MILLISECONDSa_LONG 15

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

typedef FIXED_UL_08            T_HERTZa_LONG;
#define V_HERTZa_LONG(val)     (LONGWORD)((val)*(256))
#define S_HERTZa_LONG          8

typedef FIXED_UW_07            T_PERCENTe ;
#define V_PERCENTe(val)        (WORD)((val)*(128))
#define S_PERCENTe             7

typedef FIXED_SW_07            T_PERCENTf;
#define V_PERCENTf(val)        (INTEGER)((val)*(128))
#define S_PERCENTf             7

typedef FIXED_SW_08            T_PERCENTg;
#define V_PERCENTg(val)        (INTEGER)((val)*(256))
#define S_PERCENTg             8

/* power-of-two range: [-2048, 2048) */
typedef FIXED_SW_04                T_PERCENTg_PER_SEC;
#define V_PERCENTg_PER_SEC(val)    (INTEGER)((val)*(16))
#define S_PERCENTg_PER_SEC         4

typedef FIXED_UW_09            T_PERCENTh;
#define V_PERCENTh(val)        (WORD)((val)*(512))
#define S_PERCENTh             9

typedef FIXED_UW_13            T_PERCENTj;
#define V_PERCENTj(val)        (WORD)((val)*8192)
#define S_PERCENTj             13

/* power-of-two range: [0, 32768) resolution: 0.5 */
typedef FIXED_UW_01             T_PERCENT_0_32768;
#define V_PERCENT_0_32768(val)  (WORD)((val)*(2))
#define S_PERCENT_0_32768       1

/* power-of-two range: [0, 64) resolution: 0.0009765625 */
typedef FIXED_UW_10             T_PERCENT_0_64;
#define V_PERCENT_0_64(val)     (WORD)((val)*(1024))
#define S_PERCENT_0_64          10

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

/* electronic potential (volts), range: [-16, 15.999] */
typedef FIXED_SW_11            T_VOLTe;
#define V_VOLTe(val)           (INTEGER)((val)*(2048))
#define V_VOLTe_mv_n16000_16000(val) (INTEGER)(((val)*2048)/1000)  // for value in mv
#define S_VOLTe                11

/* power-of-two range: [0, 8) Volts, precision = 0.00012207 */
typedef FIXED_UW_13            T_VOLTf;
#define V_VOLTf(val)           (WORD)((val)*(8192))
#define S_VOLTf                13

/* power-of-two range: [-8, 8) */
typedef FIXED_SW_12            T_VOLT_N8_8;
#define V_VOLT_N8_8(val)      (INTEGER)((val)*4096)
#define S_VOLT_N8_8           12

 /* power-of-two range: [-1, < 1] */
typedef FIXED_SW_15            T_RATIO_N1_1;
#define V_RATIO_N1_1(val)      (INTEGER)((val)*32768)
#define S_RATIO_N1_1           15

/* power-of-two range: [-8, 8) */
typedef FIXED_SW_12            T_RATIO_N8_8;
#define V_RATIO_N8_8(val)      (INTEGER)((val)*4096)
#define S_RATIO_N8_8           12

 /* power-of-two range: [-8, < 8] Res:16/65536 */
typedef FIXED_SW_12                      T_METER_PER_SEC_SQ_N8_8;
#define V_METER_PER_SEC_SQ_N8_8(val)    (INTEGER)((val)*4096)
#define S_METER_PER_SEC_SQ_N8_8         12

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

/* power-of-two range: (0..<128) precision (0.001953125) */
typedef FIXED_UW_09            T_AMPS_0_128;
#define V_AMPS_0_128(val)        (WORD)((val)*(512))
#define S_AMPS_0_128           9

/* power-of-two range: (-4..<4) precision (0.00012207) */
typedef FIXED_SW_13                 T_AMPS_N4_4;
#define V_AMPS_N4_4(val)            (INTEGER)((val)*(8192))
#define S_AMPS_N4_4                 13

 /* Purge fuction data type */
typedef FIXED_UW_12            T_PURG_FLOW;
#define V_PURG_FLOW(val)       (WORD)((val)*4096)
#define S_PURG_FLOW            12

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

/* power-of-two range: [0, 1024) */
typedef FIXED_UW_06                    T_ALT_Load;
#define V_ALT_Load(val)                (WORD)((val)*64)
#define S_ALT_Load                     6

/* power-of-two range: [-32768, 32768) Res: 1 */
typedef FIXED_SW_00         T_NEWTON_S32768;
#define V_NEWTON_S32768(val) (INTEGER)((val))
#define S_NEWTON_S32768      0

/* Added for Torque */
/* power-of-two range: [-2048 2048) Res: 0.0625 */
typedef FIXED_SW_04         T_NEWTON_METER;
#define V_NEWTON_METER(val) (INTEGER)((val)*16)
#define S_NEWTON_METER      4
#define CfMAX_T_NEWTON_METER (V_NEWTON_METER(2047.9375))
#define CfMIN_T_NEWTON_METER (V_NEWTON_METER(-2048))

/* power-of-two range: [-8192, 8192) Res: 0.000003814697265625 */
typedef FIXED_SL_18                    T_NEWTON_METER_N8192_8192;
#define V_NEWTON_METER_N8192_8192(val) (LONGINT)((val)*262144L)
#define S_NEWTON_METER_N8192_8192      18

/* power-of-two range: [-1024, 1024), Res: 0.03125 */
typedef FIXED_SW_05                     T_NEWTON_METER_N1024_1024;
#define V_NEWTON_METER_N1024_1024(val)  ( (INTEGER)((val) * 32 ) )
#define S_NEWTON_METER_N1024_1024       ( 5 )

/* power-of-two range: [-256 256) Res: 0.0078125 */
typedef FIXED_SW_07                  T_NEWTON_METER_N256_256;
#define V_NEWTON_METER_N256_256(val) (INTEGER)((val)*128)
#define S_NEWTON_METER_N256_256      7

/* power-of-two range: [-128 128) Res: 0.00390625 */
typedef FIXED_SW_08                  T_NEWTON_METER_N128_128;
#define V_NEWTON_METER_N128_128(val) (INTEGER)((val)*256)
#define S_NEWTON_METER_N128_128      8

/* power-of-two range: [0, 1024 * 65536) Res: 0.015625 */
typedef FIXED_UL_06          T_NEWTON_METERa;
#define V_NEWTON_METERa(val) (LONGWORD)((val)*64)
#define S_NEWTON_METERa      6

/* power-of-two range: [-8192, 8192) Res: 0.25 */
typedef FIXED_SW_02          T_NEWTON_METERb;
#define V_NEWTON_METERb(val) (INTEGER)((val)*4)
#define S_NEWTON_METERb      2

/* power-of-two range: [-128 127) Res: 0.00039 */
typedef FIXED_SW_08         T_KILONEWTON;
#define V_KILONEWTON(val)   (INTEGER)((val)*256)
#define S_KILONEWTON        8

/* power-of-two range: [-2048 2048) Res: 0.0625 */
typedef FIXED_SW_04             T_NEWTON_METER_SEC;
#define V_NEWTON_METER_SEC(val) (INTEGER)((val)*16)
#define S_NEWTON_METER_SEC      4

/* power-of-two range: [0 to 65536) Res: 1 */
typedef WORD              T_NEWTON_METER_SECa;
#define V_NEWTON_METER_SECa(val) (INTEGER)((val))
#define S_NEWTON_METER_SECa     0

/* power-of-two range: [0, 64) Res: 0.000977 */
typedef FIXED_UW_10         T_JOULE_PER_MILLIGRAM;
#define V_JOULE_PER_MILLIGRAM(val) (WORD)((val)*1024)
#define S_JOULE_PER_MILLIGRAM      10

/* power-of-two range: [0, 64) Res: 0.25 */
typedef FIXED_UB_02         T_JOULE_PER_MILLIGRAM_B;
#define V_JOULE_PER_MILLIGRAM_B(val) (BYTE)((val)*4)
#define S_JOULE_PER_MILLIGRAM_B      2

/* power-of-two range: [0, 4096) Res: 0.0625 */
typedef FIXED_UW_04         T_KPA_JOULE_PER_MILLIGRAM_SQ;
#define V_KPA_JOULE_PER_MILLIGRAM_SQ(val) (WORD)((val)*16)
#define S_KPA_JOULE_PER_MILLIGRAM_SQ      4

/* power-of-two range: [0, 128) */
typedef FIXED_UW_06             T_KPA_PER_MILLIGRAM;
#define V_KPA_PER_MILLIGRAM(val)    (WORD)((val)*512)
#define S_KPA_PER_MILLIGRAM         9


/* power-of-two range: [0, 16) Res: 0.000244 */
typedef FIXED_UW_12         T_LITERa;
#define V_LITERa(val)       (WORD)((val)*4096)
#define S_LITERa            12

/* power-of-two range: [0, 16) Res: 0.000488 */
typedef FIXED_SW_11         T_MILLILITERa;
#define V_MILLILITERa(val)  (INTEGER)((val)*2048)
#define S_MILLILITERa       11

/* power-of-two range: [0, 131071.99999) Res: 0.000030517578125 */
typedef FIXED_UL_15          T_GRAMSb_LONG;
#define V_GRAMSb_LONG(val) (LONGWORD)((val)*32768)
#define S_GRAMSb_LONG      15


/* power-of-two range: [0, 1024) Res: 0.015625 */
typedef FIXED_UW_06        T_MILLIGRAMSb;
#define V_MILLIGRAMSb(val) (WORD)((val)*64)
#define S_MILLIGRAMSb      6

/* power-of-two range: [0, 64) Res: 0.000977 */
typedef FIXED_UW_10         T_MILLIGRAMS_0_64;
#define V_MILLIGRAMS_0_64(val) (WORD)((val)*1024)
#define S_MILLIGRAMS_0_64      10

/* power-of-two range: [0, 256) Res: 0.00390625 */
typedef FIXED_UW_08         T_MILLIGRAMS_0_256;
#define V_MILLIGRAMS_0_256(val) (WORD)((val)*256)
#define S_MILLIGRAMS_0_256      8

/* power-of-two range: [-512, 512) Res: 0.015625 */
typedef FIXED_SW_06        T_MILLIGRAMS_N512_512;
#define V_MILLIGRAMS_N512_512(val) (INTEGER)((val)*64)
#define S_MILLIGRAMS_N512_512      6

/* power-of-two range: [0, 4096) Res: 0.0625 */
typedef FIXED_UW_04        T_MILLIGRAMS_0_4096;
#define V_MILLIGRAMS_0_4096(val) (WORD)((val)*16)
#define S_MILLIGRAMS_0_4096      4

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

/* power-of-two range: [0, 128) */
typedef FIXED_UW_09       T_KILOGRAMa;
#define V_KILOGRAMa(val)  (WORD)((val)*512)
#define S_KILOGRAMa 9

/* power-of-two range: [-8192, 8192) */
typedef FIXED_SW_02 T_KILOGRAMb;
#define V_KILOGRAMb(val)  (INTEGER)((val)*4)
#define S_KILOGRAMb 2

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

/* gravity */
/* range [0, 2) */
typedef FIXED_UB_07 T_GRAV_RRI;
#define V_GRAV_RRI(val)  (BYTE)((val)*128)
#define S_GRAV_RRI 7

/* MolWt - power-of-two range: [0, 32) */
typedef FIXED_UW_11 T_MOLWT_0_32;
#define V_MOLWT_0_32(val)  (WORD)((val)*2048)
#define S_MOLWT_0_32 11

/* power-of-two range: [0, 16384) */
typedef FIXED_UW_00 T_MOLES_0_16384;
#define V_MOLES_0_16384(val) (WORD)((val)*4)
#define S_MOLES_0_16384 2

/* power-of-two range: [0, 32) */
typedef FIXED_UW_11 T_KPA_MOL;
#define V_KPA_MOL(val)  (WORD)((val)*2048)
#define S_KPA_MOL 11

/* distance in meters, range [0 to 8388608)   */
typedef FIXED_UL_09             T_MOLES_LONG;
#define V_MOLES_LONG(val)      (LONGWORD)((val)*512)
#define S_MOLES_LONG           9


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
} T_HYST_PAIR;

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
  CeFUEL_DIG_CrkSOIIntake,
  CeFUEL_DIG_CrkEOICmprss,
  CeFUEL_DIG_CrkSplitInject,
  CeFUEL_DIG_HomogIntk,
  CeFUEL_DIG_HomogAntiKnock,
  CeFUEL_DIG_HomogCatLghtOff,
  CeFUEL_DIG_StratifiedInj,
  CeFUEL_DIG_HomogSpltIntk,
  CeFUEL_DIG_CrankLPM,
  CeFUEL_DIG_RunLPM
} TeFUEL_InjectionMode;

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

typedef enum {
  CeNotMovingSt,
  CeExtendSt,
  CePauseSt,
  CeRetractSt
} TeIAC_MotorSt;

typedef enum {
  CeStable,
  CeRetract,
  CeExtend
}TeIAC_MotorDirection;

typedef FIXED_SW_07 T_MILLISECONDS_DIFF;
#define V_MILLISECONDS_DIFF(val) (WORD)(val*128)
#define S_MILLISECONDS_DIFF 7

/* power-of-two range [0 to 4294967295) */
typedef FIXED_UL_00               T_NANOSECONDS_LONGa;
#define V_NANOSECONDS_LONGa(val)  (LONGWORD)(val)
#define S_NANOSECONDS_LONGa       0

/* power-of-two range [-2147483648 to 2147483647) */
typedef FIXED_SL_00                 T_NANOSECONDS_LONGb;
#define V_NANOSECONDS_LONGb(val)    (LONGINT)(val)
#define S_NANOSECONDS_LONGb         0

/*
  The Hi-Resolution clock tick data types below are currently used only for the
  misfire and tooth error correction diagnostics.  The resolution of each type
  is 1 count = 8/(system clock).
 */
/* power-of-two range [0 to 4294967295) */
typedef FIXED_UL_00 T_HIRES_CLKTCKS_LONGa;
#define V_HIRES_CLKTCKS_LONGa(val) (LONGWORD)(val)
#define S_HIRES_CLKTCKS_LONGa 0

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

/* power-of-two range: [0, 255) */
typedef FIXED_UB_00         T_KPA_0_255;
#define V_KPA_0_255(val)   (BYTE)(val)
#define S_KPA_0_255         0

/* power-of-two range: [0, 255) */
typedef FIXED_UB_00         T_KPH_0_255;
#define V_KPH_0_255(val)   (BYTE)(val)
#define S_KPH_0_255         0

/* power-of-two range: [0, 64) */
typedef FIXED_UB_03         T_KPH_0_64;
#define V_KPH_0_64(val)     (BYTE)((val)*4)
#define S_KPH_0_64          2

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

/* power-of-two range: [-2, 2) */
typedef FIXED_SB_06 T_SECONDS_N2_2_BYTE;
#define V_SECONDS_N2_2_BYTE(val)  (SHORTINT)((val)*64)
#define S_SECONDS_N2_2_BYTE 6

/* power-of-two range: [0, 4) */
typedef FIXED_UB_06 T_SECONDS_0_4_BYTE;
#define V_SECONDS_0_4_BYTE(val)  (BYTE)((val)*64)
#define S_SECONDS_0_4_BYTE 6

 /* power-of-two range: [-64, < 64] */
typedef FIXED_SW_09                      T_METER_PER_SEC_SQUARED;
#define V_METER_PER_SEC_SQUARED(val)    (INTEGER)((val)*512)
#define S_METER_PER_SEC_SQUARED         9

/* power-of-two range: [0, 255) Res: 1.0 */
typedef FIXED_UB_00         T_NEWTON_METER_BYTE;
#define V_NEWTON_METER_BYTE(val) (BYTE)(val)
#define S_NEWTON_METER_BYTE      0

/* power-of-two range: [0, 0.99609375) Res: 0.001953125 */
typedef FIXED_UB_09 T_RATIO_0_0p5_BYTE;
#define V_RATIO_0_0p5_BYTE(val) (BYTE)(val*512)
#define S_RATIO_0_0p5_BYTE 9
/* power-of-two range: [0, 128) Res: 0.5 */
typedef FIXED_UB_01         T_NEWTON_METER_0_128B;
#define V_NEWTON_METER_0_128B(val) (BYTE)((val)*2)
#define S_NEWTON_METER_0_128B      1

/* power-of-two range: [0, 32) Res: 0.125 */
typedef FIXED_UB_03         T_NEWTON_METER_0_32B;
#define V_NEWTON_METER_0_32B(val) (BYTE)((val)*8)
#define S_NEWTON_METER_0_32B      3

/* power-of-two range: [0, 0.99609375] Res: 0.00390625 */
typedef FIXED_UB_08 T_RATIO_0_1_BYTE;
#define V_RATIO_0_1_BYTE(val) (BYTE)(val*256)
#define S_RATIO_0_1_BYTE 8

/* power-of-two range: [0, 1.9921875] Res: 0.0078125 */
typedef FIXED_UB_07 T_RATIO_0_2_BYTE;
#define V_RATIO_0_2_BYTE(val) (BYTE)(val*128)
#define S_RATIO_0_2_BYTE 7

/* power-of-two range: [0, 3.984375] Res: 0.015625 */
typedef FIXED_UB_06 T_RATIO_0_4_BYTE;
#define V_RATIO_0_4_BYTE(val) (BYTE)(val*64)
#define S_RATIO_0_4_BYTE 6

/* power-of-two range: [0, 7.96875] Res: 0.03125 */
typedef FIXED_UB_05 T_RATIO_0_8_BYTE;
#define V_RATIO_0_8_BYTE(val) (BYTE)(val*32)
#define S_RATIO_0_8_BYTE 5

/* power-of-two range: [0, 15.9375] Res: 0.0625 */
typedef FIXED_UB_04 T_RATIO_0_16_BYTE;
#define V_RATIO_0_16_BYTE(val) (BYTE)(val*16)
#define S_RATIO_0_16_BYTE 4

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

typedef FIXED_UL_04 T_PULSE_PER_KM_LONG_0_268435456;
#define V_PULSE_PER_KM_LONG_0_268435456(val) (LONGWORD)((val)*16)
#define S_PULSE_PER_KM_LONG_0_268435456 4

/* angle (degrees) */
/* range: [-256, 255.992187] Res: 0.0078125 */
typedef FIXED_SW_07 T_CAMPHI;
#define V_CAMPHI(val) V_SW_07(val)
#define S_CAMPHI S_SW_07

/* angle (degrees) */
/* range : [0, 64) Res: 0.0009765625 */
typedef FIXED_UW_10 T_CAMPHIa;
#define V_CAMPHIa(val) (WORD)((val)*1024)
#define S_CAMPHIa 10

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

/* pressure (in kilopascals) */

/* power-of-two range: [0, 1048576)   Res:  1/4096  */
typedef FIXED_UL_12       T_KPa_LONG;
#define V_KPa_LONG(val)   (LONGWORD)((val)*4096)
#define S_KPa_LONG        12

/* Res:   0.015625000 */
/* Range: [0, 1024)   */
typedef FIXED_UW_06         T_W_KPA_0_1024;
#define V_W_KPA_0_1024(val) V_UW_06(val)
#define S_W_KPA_0_1024      S_UW_06

/* pressure in kilo pascals (kPa), range: [0, 1020] */
typedef BYTE  T_KPAg_BYTE;
#define V_KPAg_BYTE(val)    (BYTE)((val)*0.25)
#define S_KPAg_BYTE         -2

/* power-of-two range: [0, 512 ) Res: 0.0078125 */
typedef FIXED_UW_07          T_KPA_0_512;
#define V_KPA_0_512(val)     (WORD)((val)*128)
#define S_KPA_0_512          7

/* power-of-two range: [0, 8192) */
typedef FIXED_UW_03                    T_LitersPerMinute;
#define V_LitersPerMinute(val)         ((WORD)((val)*8))
#define S_LitersPerMinute              3

/* power-of-two range: [0, 2) */
typedef FIXED_UW_15                    T_LitersPerRevolution;
#define V_LitersPerRevolution(val)     ((WORD)((val)*32768))
#define S_LitersPerRevolution          15

/* temperature, range: [-128, < 127)  resolution: 1 */
typedef SHORTINT             T_DEG_Ca_BYTE;
#define V_DEG_Ca_BYTE(val)   ((SHORTINT)(val))
#define S_DEG_Ca_BYTE 0

/* Angular speed in Degree/sec */
typedef BYTE          T_DEG_PER_SEC_BYTE;
#define V_DEG_PER_SEC_BYTE(val)    (BYTE)((val)*0.25)
#define S_DEG_PER_SEC_BYTE    -2


#endif  /* T_CUSTOM_H */

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
*       030319 ela 2556 Added T_KILONEWTON for torque_based cruise control.
*            (TCI)
* 5.6   030429 arr 2615 Correct macro V_AMPS_N4_4 to use INTEGER instead of
*                        WORD for signed type.
* 5.7   030606 ses 2806 Added T_KPA_0_32768 for use in Power Steering Pressure
*                      logic.
* tci_pt3#5.7
*       030430 ksr 2212 Added T_PERCENTj for EVAP Purge Concentration (TCI).
* tci_pt3#5.7
*       030430 ksr 2212 Added T_PERCENTj for EVAP Purge Concentration (TCI).
* 5.10  030616 hdb 2827 Correct values for T_AMPS_N4_4
* 5.11  030912 gps 2603 EPSE: Create BARO Valid Flag.
*                       Added T_L_KILOMETERS.
* 5.12  030912 kan 3119 Added:
*                       T_VAC_PER_VREF_N64_64
* 5.13  030923 rmn 3112 Added T_INCHES_METERSa, T_RPM_KPH_MPHa, T_RPM_KPH_MPHb,
*                      T_KILOGRAMa
*                      Corrected type for T_METERS and T_INCHES
* 5.14  030926 rmn 3112 Removed T_RPM_KPH_MPHa
* 5.15  031125 hdb 3374 Correct scaling for type definitions T_SECONDS_0_4
*                        and T_SECONDS_0_8
*

* tci_pt3#5.15
*       031120 kvm 3394 removed the enum TeTRANS_TYPE
* tci_pt3#5.14.1.1
*       031125  pd 3388 Added T_CAMPHIa
* 5.16  031209 as  xxxx Merged 't_custom.h-5.15' with 't_custom.h-tci_pt3#5.16'
* 8, 9  040109 woz 3174 Moved T_ACCEL_IN_G_N32_32 and T_ACCEL_IN_G_0_64 from
*                        rridstyp.h.
*                       Added T_ACCEL_IN_G_0_1K.
* 10.0  040114 rmn 3581 Added T_KILOGRAMb
* 11    040305 woz 3600 Corrected type casting of the following macros:
*                        V_NEWTON_METERa, T_LITERa, T_MILLIGRAMSb
* 13.0  040713 caw 4152 Added: T_KPA_N16384_16384
* 13.1.2
*       050315 aob 4989 Added T_NEWTON_METER_N256_256.
* 13.1.2.1.1 051202 at 5467 - Added T_KPA_N128_128
* 13.1.2.1.2 051207 at 5467 - Corrected non functional error in T_KPA_N128_128
* 13.1.3
*       050518 aob 5127 Added T_KPA_0_512 and T_KPA_N128_128.
* tci_pt3#13.1.4
*       051117 ban 5311 Added T_VOLTa, T_GRAMS_PER_SECa, T_GRAMS_PER_SEC_0_8192
*                       T_PERCENT_0_32768, T_PERCENT_0_64
* tci_pt3#14
*       060105 tln 5491 Added data type T_AMPS_0_128 for CANOBD
* 13.1.3.1.1.1.1
*       051209 gps -BM- Turbo Integration Fixes for Ver 11 of Martin's Issue.
* 13.1.3.1.1.1.1.1.1
*       060106 PVD -BM- Merged 13.1.3.1.1.1.1 and tci_pt3#13.1.4
* 13.1.4
*       050824 hdb 5277 ARFA585 Engine Speed Control for coast lock up.
*                        Moved T_NEWTON_METER_SEC from torqstyp.h
* 13.1.3.1.1.1.2
*       060106 PVD -BM- Merged 13.1.3.1.1.1.1 and tci_pt3#13.1.4
* 15.3  060216 caw -BM- Remove duplicate define of T_KPA_N128_128
* 13.2  051208 hdb 5371 Add values for CAN $06 service bay - added: CeVAC_MAX
* 15.4  060331 hdb ---- Merged 't_custom.h-15.3' with 't_custom.h-13.2'.
* 15.5  060607 at  5556 was: CeAlternatingEST is: CeWasteEST
* 15.4.1.1
*       060720 gps 5691 Implemented changes required for CTORQIII integration.
*                       Added NANOSECONDS fixed point types.
* 15.6  060828 cjk -BM- Merged 't_custom.h-15.5' with 't_custom.h-15.4.1.1'
* tci_pt3#15.5.1.1
*       061110 vs  5921 Added T_VOLTg
* tci_pt3#15.5.1.1.1.1
*       070116 ela 6095 Added T_METERS_0_2048
*                             T_METERS_0_2...
*                             T_MILLISECONDSa_LONG
* tci_pt3#15.6
*       060925 vs  5773 Added: T_GRAMS_0_33554432, T_AFR_LONG and
*                              T_GRAMS_0_65536
* tci_pt3#15.7 at  -BM- Merged 't_custom.h-tci_pt3#15.6' with
*                              't_custom.h-tci_pt3#15.5.1.1'
* 15.7  061205 cjk -BM- Merged 't_custom.h-15.6' with 't_custom.h-tci_pt3#15.7'
* tci_pt3#15.8
*       061207 AB  5904 Added: T_FUEL_TANK_LITER
* tci_pt3#15.5.1.2
*       061205 AKR 5919 Added T_MILLIMETERS,T_METERS_0_512
* tci_pt3#16
*       070110 rmn 5919 Added T_METERS_0_32
* tci_pt3#17
*       070118 rmn -BM- Merged 't_custom.h-tci_pt3#16' with 't_custom.h-15.9'.
* tci_pt3#16.1
*       070206 rmn 5878 Added T_NEWTON_METER_N8192_8192.
* tci_pt3#18.1
*       070213 rmn xxxx Merged 't_custom.h-tci_pt3#16.1' with 't_custom.h-18'.
* tci_pt3#18.2
*       070227 rmn 6020 Added T_METERS_0_128, T_PULSE_PER_KM_LONG_0_268435456
******************************************************************************/
/*-------------------------------------------------------------------*/
/* T_CUSTOM.H rev. 1.1  - 18 Jul 2006  - Claude Poull                */
/*                                                                   */
/* - Added: T_MILLILITERa, T_GRAMS_CYL_N8_8                          */
/*                                              RSC: BF_3443         */
/* - Changed resolution of T_BPW to 1/256                            */
/*                                              RSC: BF_3566         */
/*-------------------------------------------------------------------*/
/* T_CUSTOM.H rev. 1.2  - 23 Aug 2006  - Didier Gautier              */
/*                                                                   */
/* - Added: T_LAMBDA                                                 */
/*                                              RSC:                 */
/*-------------------------------------------------------------------*/
/******************************************************************************
* 18.1.1 070214 kmf DIG Changed T_BPW type.
*                       Added T_MILLILITERa, T_GRAMS_CYL_N8_8, T_LAMBDA
* 18.1.2 070523 gwm DIG Modified T_MPA, V_MPA and S_MPA to have 1 to 32
*                       bit resolution.
* 19    070130 cjk 5834 Update per peer review.
*                       - Add T_NEWTON_METER_N1024_1024
* 20    070314 cjk -BM- Merge 't_custom.h-tci_pt3#18.2' with
*                             't_custom.h-19'
* tci_pt3#xxxx
*       070312 abh 6107 Added T_GRAMS_0_256
* tci_pt3#22
*       070510 raj 5903 Renamed T_GRAMS_CYL_0_1 to T_GRAMS_CYL_0_2,
*                                V_GRAMS_CYL_0_1 to V_GRAMS_CYL_0_2,
*                            and S_GRAMS_CYL_0_1 to S_GRAMS_CYL_0_2
* 22    070530 tmw 4652 Added some new typedefs for OSC: T_GRAMS_0_1, T_GRAMS_0_4,
*                       T_GRAMS_N1_1, T_GRAMS_N2_2, T_GRAMS_N2_2_LONG,
*                       T_GRAMS_0_4_LONG, T_AFR_0_16_LONG
*                       T_GRAMS_PER_SEC_0_1, T_GRAMS_PER_SEC_0_16,
*                       T_GRAMS_PER_SEC_0_32
* tci_pt3#24
*       071029 VVM 6313 Added FIXED_UB_06, T_GRAV_RRI.
* 23    07xxxx xxx -BM- Merged 't_custom.h-tci_pt3#22' with 't_custom.h-22'
* 24    071005 cjk 6246 Update accessory torque function in Torque 3
*                       - add T_LitersPerMinute
*                       - add T_LitersPerRevolution
* 25    071112 hdb 6618 New Phaser Response / Error monitors for SID $06
*                         Add T_SECONDS_0_64
* 26    071213 caw -BM- Merged
* tci_pt3#23.1.1
*       080110 MBA 6223 Added T_NEWTON_METER_SECa.
* tci_pt3#23.1.2
*       080312 MBA -BM- Merged 't_custom.h~tci_pt3#23.1.1' with 't_custom.h~26'.
* 23.1.3
*       080530 cjk 6897 Torque 3 cleanup
*                       - add CfMAX_T_NEWTON_METER
*                       - add CfMIN_T_NEWTON_METER
* 27    080327 hdb 6464 Added V_VOLTb_mv_0_32000()
* 26.1.2
*       080417 hdb      Merge t_custom.h~26.1.1 with t_custom.h~tci_pt3#23.1.2
* tci_pt3#26.1.2.1.1
*       080610  VP 7111 Added T_RATIO_0_1_BYTE.
* 23.1.4
*       080812 cjk -BM- Merged 't_custom.h~tci_pt3#26.1.2.1.1' with
*                              't_custom.h~23.1.3'
* tci_pt3#26.1.3
*       080522 VP  6959 Added T_KILOMETERSg.
* tci_pt3#26.1.4
*       080620 VP  6959 Added T_KILOMETERSh.
* 23.1.5
*       080814 cjk -BM- Merged 't_custom.h~tci_pt3#26.1.4' with
*                              't_custom.h~23.1.4'
*23.1.5.1.1
*       080915 MU  7222  Inserted data type  V_W_KPA_0_1024
* 26.1.4.1.1
*       080805 cjk 7221 Update WRAF CL Fuel Control
*                       - add T_Lambda
*                       - add T_OHMS_0_4096
* 23.1.6
*       080909 cjk -BM- Merged 't_custom.h~23.1.5' with 't_custom.h~26.1.4.1.1'
* 28
*       080620 kmf      Merge t_custom.h~26.1.2 with t_custom.h~27
* 26.3  080930 MU Merged Ver. 23.1.6 & 23.1.5.1.1
* 26.4  081011 KN  7406 Moved T_BPW to the respective fuelptyp.h files (for GDi & PFI)
* 26.6  081208 vs  7306 Added T_W_PERCENTa_N128_128
* 26.5.2.1
*       081210 cjk 7576 WRAF Change data type
*                       - Commonize T_Lambda and T_LAMBDA
* 26.5.2.2
*       081230 cjk 7610 WRAF Rear Trim
*                       - add T_GRAMS_PER_SEC_N2_2 and T_GRAMS_PER_SEC_N2_2L
* 26.5.2.3
*       090204 cjk 7684 FUEL pulse width calculation for seq prime pulse
*                       - add T_GRAMS_CYL_0_8
*                       - remove T_GRAMS_CYL_0_1
* 26.7  090106 cjk -BM- Merged 't_custom.h~26.6' with 't_custom.h~26.5.2.1'
* 26.8  090209 cjk -BM- Merged 't_custom.h~26.7' with 't_custom.h~26.5.2.3'
* 26.11.2.1
*       091027 grb 7918 Added  T_METER_PER_SEC_SQUARED
* kok_pt2#6.11.1.1
*       090603 MU  7930 Removed   T_kPa_IMEP_W and  T_kPa_IMEP_W_DIFF
* kok_pt2#26.11.1.2
*       090909 grb 7825 Added T_NEWTON_METER_0_128B
*                             T_NEWTON_METER_0_32B
* kok_pt2#26.12
*       090528 rbg 7820 Added FIXED_SB_07, T_PCT_DIFFA_BYTE
* kok_pt2#27
*       090619  MU XXXX Merged Versions 26.11.1.1 & 26.12
* tci_pt3#26.14
*       090729  MH 8113 Added new type T_MILLISECONDSf2.
* kok_pt2#26.15
*       090916 mcb 8267 Added T_P25MIN
* kok_pt2#26.14.4.1
*       091027 grb 8332 Added T_PERCENTh_B
* kok_pt2#26.14.1.1
*       091012 gps 6730 Changes associated with 3.9 to 2.5 ms base loop transition.
*                       Renamed RPM_PER_46P86_MSECa to RPM_PER_50_MSECa.
* kok_pt2#26.14.3.2
*       091022 grb -BM- Merged t_custom.h~kok_pt2#26.11.1.2
*                       & t_custom.h~tci_pt3#26.14
* kok_pt2#26.14.2.1
*       091020 vs  8343 Added T_RATIO_0_4_BYTE
* kok_pt2#26.14.3.2
*       091023 vs  -BM- Merged 't_custom.h~kok_pt2#26.14.3.1' with
*                        't_custom.h~kok_pt2#26.14.2.1'.
* kok_pt2#26.14.3.3
*       091027 grb -BM- Merged 't_custom.h~kok_pt2#26.14.3.2' with
*                       't_custom.h~kok_pt2#26.11.2.1'.
* kok_pt2#26.14.3.4
*       091027 grb -BM- Merged 't_custom.h~kok_pt2#26.14.3.3' with
*                        't_custom.h~kok_pt2#26.14.4.1'.
* kok_pt2#26.15.1
*       091030 mcb -BM- Merge 't_custom.h~kok_pt2#26.14.3.4' 't_custom.h~kok_pt2#26.15'
* kok_pt2#26.15.2
*       091106  mt 8397 Added type T_KPA_0_255 and definitions for S_RPM_0_2040 and V_RPM_0_2040
*
* kok_pt2#26.14.3.5
*       091104 grb 8332 Corrected V_PERCENTh_B sync error.
* kok_pt2#26.14.3.6
*       091106 grb -BM- Merged 't_custom.h~kok_pt2#26.14.3.5' with
*                       't_custom.h~kok_pt2#26.15.1'.
* kok_pt2#26.14.3.7
*       091118 gps -BM- Merged 't_custom.h~kok_pt2#26.14.3.6'
*                          with 't_custom.h~kok_pt2#26.14.1.1'.
* kok_pt2#26.14.4.1
*       091112 grb 8057 Added T_RATIO_0_0p5_BYTE,
*                           T_JOULE_PER_MILLIGRAM_B
*                           FIXED_UB_09
*                           FIXED_UB_02
* kok_pt2#26.14.3.7.1.1
*       091207 grb -BM- Merged 't_custom.h~kok_pt2#26.14.3.7' with 't_custom.h~kok_pt2#26.14.5.1'.
* kok_pt2#26.14.3.7.1.2
        091209 grb -BM- Corrected V_UB_02
* kok_pt2#26.14.8.1
*       091102 pjb 8444 Added T_PERCENTh_B
* kok_pt2#26.15.1.1.1
*       091117 pjb 8444 Corrected scaling of T_PERCENTh_B
* kok_pt2#28.3.1
*       100223 gps 8644 VCPS: Calibration Memory Reduction.
*                       Moved in T_B_PERCENTa_N50_50 definition from t_range.h.
*       091209 grb -BM- Merged 't_custom.h~kok_pt2#27' with 't_custom.h~kok_pt2#26.14.3.7.1.2'.
* 29    100126 caw -BM- Merged
* kok_ptt#28.2.1
*       100204 cjk 8582 Add T_RATIO_0_8_BYTE
* kok_pt2#28.2.2
*       100216 me  -BM- Merged 't_custom.h~kok_pt2#28.2.1'
*                         with 't_custom.h~kok_pt2#28.1.1'.
* 27.0  091021 tzxz3j
                   8243 Added T_KILOGRAMc
* 26.16 100115 hp  8243 Deleted T_KILOGRAMc
* 26.17 100304 hp  -BM- Merged 't_custom.h~kok_pt2#26.16' with
*                        't_custom.h~kok_pt2#28.2.2'.
* 26.17.5.1
*     100318 hp  8305 Added T_GRAMS_SHRT_0_65536 and T_GRAMSb_LONG.
* kok_pt2#26.17.1.1
*     100401 kn     8647 Added FIXED_SB_04, T_MPA_BYTE, T_MPA_DIFF_BYTE
*
* kok_pt2#26.17.2.1
*     100406 grb 8676 Added T_KPA_JOULE_PER_MILLIGRAM_SQ,
*                           T_KPA_PER_MILLIGRAM
*
* 26.18
*     100310 hp  8709 Added T_VOLT_N8_8.
* kok_pt2#26.20
*     100412 grb -BM- Merged t_custom.h~kok_pt2#26.17.2.1 & t_custom.h~kok_pt2#26.19
* kok_pt2#26.17.4.1
*       100414 rbg 8679 Added typedef FIXED_UB_03 T_MPA_BYTE;
*                       Added CeFUEL_DIG_HomogSpltIntk to TeFUEL_InjectionMode
*                       Added T_PERCENTa_BYTE
* tci_pt3#26.18
*     100427 vk 8630 Added T_VOLT_0_16.
* kok_pt2#26.21.1
*     100502 mcb -BM- Merge 't_custom.h~kok_pt2#26.21' 't_custom.h~kok_pt2#26.17.4.1'
* tci_pt3#26.21.2
*     100512 vk -BM-  Merged 't_custom.h~kok_pt2#26.21.1' with
*                            't_custom.h~tci_pt3#26.18'.
* tci_pt3#26.18
*       100427 vk  8630 Added T_VOLT_0_16.
* kok_pt2#26.18.1.1
*       100511 JP  -BM- Merged kok_pt2#26.21.1 with tci_pt2#26.18
* 26.21.3
*           100511 caw -BM- Merges
* tci_pt3#26.21.4
*           100622 MTC 8925 Added T_KPH_0_255,T_CRANK_ANGLE_BYTE,
*                           T_CRANK_ANGLE_0_64,T_PERCENTh_0_32,
*                           T_KPH_0_64.
*       100511 caw -BM- Merges
* kok_pt2#28.3.2
*       100513 gps -BM- Merged 't_custom.h~kok_pt2#28.3.1' with 't_custom.h~kok_pt2#26.21.3'.
* kok_pt2#28.3.3
*       100513 gps -BM- Merged 't_custom.h~kok_pt2#28.3.2' with 't_custom.h~kok_pt2#26.17.5.1'.
* tci_pt3#28.3.4
*       100528 arm 8754 Added t_kpag_byte
* kok_pt2#28.3.3.1.1
*       100616 cjk 7437 Added T_SECONDS_0_1
*                       Added T_PERCENTg_PER_SEC
* tci_pt3#28.3.3.2.1
*       100712 vk  8822 Added T_KPa_LONG
* kok_pt2#26.22
*     100506 cjk 8620 Add T_RATIO_0_16_BYTE
* kok_pt2#26.17.3.1
*       100211 hp  8393 Added T_MOLWT_0_32, T_MOLES_0_16384
*                       T_GRAMS_SHRT_0_65536, T_KPA_MOL and T_MOLES_LONG.
* kok_pt2#28.3.4
*       100525 hp  -BM- Merged 't_custom.h~kok_pt2#26.17.3.1' with
*                       't_custom.h~kok_pt2#28.3.3'.
* kok_pt2#26.23
*       100609 cjk -BM- Merged 't_custom.h~kok_pt2#28.3.4'
*                         with 't_custom.h~kok_pt2#26.22'
* kok_pt2#26.21.2
*     100604 grb 8833 Added T_MILLIGRAMS_0_64
* kok_pt2#26.24
*     100617 grb -BM- Merged kok_pt2#26.21.2 & kok_pt2#26.21.2
* kok_pt2#26.26
*     100709 mcb 8794 Changed TeFUEL_InjectionMode
* tci_pt3#26.20
*     100428 nag 8641 Added T_DEG_Ca_BYTE
* kok_pt2#26.25
*     100701 nag -BM- Merged from 't_custom.h~kok_pt2#26.24:incl:tcb_pt1#4'
*                     and 't_custom.h~tci_pt3#26.20:incl:tcb_pt1#4' by fz7ytk.
* tci_pt3#26.26
*     100817 MTC 8584 Added T_METER_PER_SEC_SQ_N4_4.
* tci_pt3#26.21.5
*     100715 MTC XXXX Merged 't_custom.h~tci_pt3#26.21.4' with
*                    't_custom.h~kok_pt2#26.25'.
* 26.21.6
*     100723 caw -BM- Merges
* tci_pt3#26.24.1.1
*     100713 nag 8909 Added CfMAX_T_MPA_DIFF
* tci_26.24.1.2
*     100802 sat -BM- Merged 't_custom.h~tci_pt3#26.24.1.1' with
*                             't_custom.h~kok_pt2#26.21.6'.
* kok_pt2#28.4
*     100824 cjk -BM- Merged 't_custom.h~tci_26.24.1.2'
*                       with 't_custom.h~kok_pt2#28.3.3.1.1'
* kok_pt2#28.5
*     100802 mcb -BM- Merged 't_custom.h~tci_pt3#tci_26.24.1.2' with
*                             't_custom.h~kok_pt2#26.26'.
* kok_pt2#28.6
*     100824 caw -BM- Merges
* tci_pt3#28.6.2.1
*     101020 MTC 9058 Changed resolution of datatype T_PURG_FLOW
*                     to (1/4096).
* kok_pt2#28.7
*     100914 rbg 8944 Added T_GRAMS_PER_SEC_N64_64
* tci_pt3#28.7
*     100916 MH  9053  added T_METER_PER_SEC_SQ_N8_8.
* tci_pt3#28.7
*     100909 SMM 9059 Added T_VOLT_0_1_BYTE
* 26.8
*     100916 caw -BM- Merges
* 26.9
*     100928 caw -BM- Merges
* tci_pt3#28.10
*     101118 vk  9154 Added T_SECONDS_0_512
* tci_pt3#28.3.3.1.1
*     100819 sat 8823 Added V_RPM_BYTE_N512_512.
* tci_pt3#28.9.1.1
*     101115 arm -BM- Merged 't_custom.h~tci_pt3#28.3.3.1.1'with
*                            't_custom.h~kok_pt2#28.9'
* 26.10
*     101109 caw -BM- Merges
* 26.11
*     101109 caw -BM- Merges
* 26.12
*     101122 caw -BM- Merges
* 26.14
*     101214 caw -BM- Merges
* kok_pt2#28.16
*     110217 mcb 9197 Added T_USEC_PER_VOLTb
* tci_pt3#28.15
*     110131 nag 9008 Added T_MILLIGRAMS_0_4096, T_MILLIGRAMS_0_256
* kok_pt2#28.15
*     110119 pr 9121 Created T_TIME_SEC_P125
* kok_pt2#28.15.1.1
*     110219 me  -BM- Merges
* kok_pt2#28.16.1
      110311 mcb -BM- Merge 't_custom.h~tci_pt3#28.16'
*                            't_custom.h~kok_pt2#28.15.1.1'
* kok_pt2#28.16.3
*       110527 aq  9239 Added T_DEG_Ke.
* tci_pt3#28.3.4.1.1
*     110523 arm -BM- Merged 't_custom.h~tci_pt3#28.3.4' with
*                     't_custom.h~kok_pt2#28.16.1'.
* kok_pt2#28.13.3
*     110524 mcb 9443 Added T_SECONDS_N2_2_BYTE, T_SECONDS_0_4_BYTE
*                      FIXED_SB_06, T_SECONDS_N2_2
*                      V_VOLTe_mv_n16000_16000
*
* kok_pt2#29
*       110622 me  -BM- Merges
* kok_pt2#28.6.1.1
*     101214 cjk 8907 Add CfMAX_T_PERCENT_MULTa
* kok_pt2#28.6.1.2
*     110308 gps 7640 LO2D: Create Response Diagnostic For WRAF Sensor(s).
*                     Added T_B_PERCENT_N25_25.
*            cjk      Added T_HERTZa_LONG
* kok_pt2#28.16.2
*     110503 cjk -BM- Merged 't_custom.h~kok_pt2#28.16.1'
*                            't_custom.h~kok_pt2#28.6.1.2'
* kok_pt2#28.16.4.1.1
*     110503 cjk -BM- Merged 't_custom.h~kok_pt2#28.16.2'
*                            't_custom.h~kok_pt2#28.16.4'
* kok_pt2#28.16.4.1.2
*     110708 me  -BM- Merges
* tci_pt3#28.3.4.1.2
*     110711 vk  9407 Added T_SECONDS_0_1024
* kok_pt2#28.16.4.1.3
*     110721 me  -BM- Merges
* tci_pt3#28.12.1.4
*     110831 SMK 9612 Added T_DEG_PER_SEC_BYTE , T_BAR_0_512
*
******************************************************************************/

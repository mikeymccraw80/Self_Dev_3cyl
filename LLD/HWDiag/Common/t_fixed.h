#ifndef T_FIXED
#define T_FIXED
 /*****************************************************************************
 *
 * (c) 1997 General Motors Corporation, all rights reserved
 *
 * Description:         Define fixed point scaling types interms of hardware
 *                      data types as defined in t_base.h
 *
 *  This file was created by Bill Debs in June 1994.
 *
 *****************************************************************************
 *
 * Initial Module Info:
 * %created_by:    vzp48z %
 * %date_created:  Wed Mar 19 09:46:40 2008 %
 *
 * Current Module Info:
 * %full_name:   mt20u2#10/incl/t_fixed.h/1 %
 * %version:     1 %
 * %derived_by:  vzp48z %
 *
 *****************************************************************************/

/******************************************************************************/
/* Signed Word Fixed Point Types                                              */
/******************************************************************************/
typedef INTEGER FIXED_SW_00;
#define V_SW_00(val) (INTEGER)(val)
#define S_SW_00 0

typedef INTEGER FIXED_SW_01;
#define V_SW_01(val) (INTEGER)(val*2)
#define S_SW_01 1

typedef INTEGER FIXED_SW_02;
#define V_SW_02(val) (INTEGER)(val*4)
#define S_SW_02 2

typedef INTEGER FIXED_SW_03;
#define V_SW_03(val) (INTEGER)(val*8)
#define S_SW_03 3

typedef INTEGER FIXED_SW_04;
#define V_SW_04(val) (INTEGER)(val*16)
#define S_SW_04 4

typedef INTEGER FIXED_SW_05;
#define V_SW_05(val) (INTEGER)(val*32)
#define S_SW_05 5

typedef INTEGER FIXED_SW_06;
#define V_SW_06(val) (INTEGER)(val*64)
#define S_SW_06 6

typedef INTEGER FIXED_SW_07;
#define V_SW_07(val) (INTEGER)(val*128)
#define S_SW_07 7

typedef INTEGER FIXED_SW_08;
#define V_SW_08(val) (INTEGER)(val*256)
#define S_SW_08 8

typedef INTEGER FIXED_SW_09;
#define V_SW_09(val) (INTEGER)(val*512)
#define S_SW_09 9

typedef INTEGER FIXED_SW_10;
#define V_SW_10(val) (INTEGER)(val*1024)
#define S_SW_10 10

typedef INTEGER FIXED_SW_11;
#define V_SW_11(val) (INTEGER)(val*2048)
#define S_SW_11 11

typedef INTEGER FIXED_SW_12;
#define V_SW_12(val) (INTEGER)(val*4096)
#define S_SW_12 12

typedef INTEGER FIXED_SW_13;
#define V_SW_13(val) (INTEGER)(val*8192)
#define S_SW_13 13

typedef INTEGER FIXED_SW_14;
#define V_SW_14(val) (INTEGER)(val*16384)
#define S_SW_14 14

typedef INTEGER FIXED_SW_15;
#define V_SW_15(val) (INTEGER)(val*32768)
#define S_SW_15 15

typedef INTEGER    FIXED_SW_16;
#define V_SW_16(val) (INTEGER)(val*65536)
#define S_SW_16 16

typedef INTEGER    FIXED_SW_17;
#define V_SW_17(val) (INTEGER)(val*131072)
#define S_SW_17 17

typedef INTEGER    FIXED_SW_18;
#define V_SW_18(val) (INTEGER)(val*262144)
#define S_SW_18 18

typedef INTEGER    FIXED_SW_19;
#define V_SW_19(val) (INTEGER)(val*524288)
#define S_SW_19 19

typedef INTEGER    FIXED_SW_20;
#define V_SW_20(val) (INTEGER)(val*1048576)
#define S_SW_20 20

/******************************************************************************/
/* Unsigned Word Fixed Point Types                                            */
/******************************************************************************/
typedef WORD    FIXED_UW_00;
#define V_UW_00(val) (WORD)(val)
#define S_UW_00 0

typedef WORD    FIXED_UW_01;
#define V_UW_01(val) (WORD)(val*2)
#define S_UW_01 1

typedef WORD    FIXED_UW_02;
#define V_UW_02(val) (WORD)(val*4)
#define S_UW_02 2

typedef WORD    FIXED_UW_03;
#define V_UW_03(val) (WORD)(val*8)
#define S_UW_03 3

typedef WORD    FIXED_UW_04;
#define V_UW_04(val) (WORD)(val*16)
#define S_UW_04 4

typedef WORD    FIXED_UW_05;
#define V_UW_05(val) (WORD)(val*32)
#define S_UW_05 5

typedef WORD    FIXED_UW_06;
#define V_UW_06(val) (WORD)(val*64)
#define S_UW_06 6

typedef WORD    FIXED_UW_07;
#define V_UW_07(val) (WORD)(val*128)
#define S_UW_07 7

typedef WORD    FIXED_UW_08;
#define V_UW_08(val) (WORD)(val*256)
#define S_UW_08 8

typedef WORD    FIXED_UW_09;
#define V_UW_09(val) (WORD)(val*512)
#define S_UW_09 9

typedef WORD    FIXED_UW_10;
#define V_UW_10(val) (WORD)(val*1024)
#define S_UW_10 10

typedef WORD    FIXED_UW_11;
#define V_UW_11(val) (WORD)(val*2048)
#define S_UW_11 11

typedef WORD    FIXED_UW_12;
#define V_UW_12(val) (WORD)(val*4096)
#define S_UW_12 12

typedef WORD    FIXED_UW_13;
#define V_UW_13(val) (WORD)(val*8192)
#define S_UW_13 13

typedef WORD    FIXED_UW_14;
#define V_UW_14(val) (WORD)(val*16384)
#define S_UW_14 14

typedef WORD    FIXED_UW_15;
#define V_UW_15(val) (WORD)(val*32768)
#define S_UW_15 15

typedef WORD    FIXED_UW_16;
#define V_UW_16(val) (WORD)(val*65536)
#define S_UW_16 16

typedef WORD    FIXED_UW_17;
#define V_UW_17(val) (WORD)(val*131072)
#define S_UW_17 17

typedef WORD    FIXED_UW_18;
#define V_UW_18(val) (WORD)(val*262144)
#define S_UW_18 18

typedef WORD    FIXED_UW_19;
#define V_UW_19(val) (WORD)(val*524288)
#define S_UW_19 19

typedef WORD    FIXED_UW_20;
#define V_UW_20(val) (WORD)(val*1048576)
#define S_UW_20 20

/******************************************************************************/
/* Signed Medium Fixed Point Types                                             */
/******************************************************************************/
typedef MEDINT FIXED_SM_00;
#define V_SM_00(val) (MEDINT)(val)
#define S_SM_00 0

typedef MEDINT FIXED_SM_01;
#define V_SM_01(val) (MEDINT)(val*2)
#define S_SM_01 1

typedef MEDINT FIXED_SM_02;
#define V_SM_02(val) (MEDINT)(val*4)
#define S_SM_02 2

typedef MEDINT FIXED_SM_03;
#define V_SM_03(val) (MEDINT)(val*8)
#define S_SM_03 3

typedef MEDINT FIXED_SM_04;
#define V_SM_04(val) (MEDINT)(val*16)
#define S_SM_04 4

typedef MEDINT FIXED_SM_05;
#define V_SM_05(val) (MEDINT)(val*32)
#define S_SM_05 5

typedef MEDINT FIXED_SM_06;
#define V_SM_06(val) (MEDINT)(val*64)
#define S_SM_06 6

typedef MEDINT FIXED_SM_07;
#define V_SM_07(val) (MEDINT)(val*128)
#define S_SM_07 7

/******************************************************************************/
/* Unsigned Medium Fixed Point Types                                            */
/******************************************************************************/
typedef MEDWORD    FIXED_UM_00;
#define V_UM_00(val) (MEDWORD)(val)
#define S_UM_00 0

typedef MEDWORD    FIXED_UM_01;
#define V_UM_01(val) (MEDWORD)(val*2)
#define S_UM_01 1

typedef MEDWORD    FIXED_UM_02;
#define V_UM_02(val) (MEDWORD)(val*4)
#define S_UM_02 2

typedef MEDWORD    FIXED_UM_03;
#define V_UM_03(val) (MEDWORD)(val*8)
#define S_UM_03 3

typedef MEDWORD    FIXED_UM_04;
#define V_UM_04(val) (MEDWORD)(val*16)
#define S_UM_04 4

typedef MEDWORD    FIXED_UM_05;
#define V_UM_05(val) (MEDWORD)(val*32)
#define S_UM_05 5

typedef MEDWORD    FIXED_UM_06;
#define V_UM_06(val) (MEDWORD)(val*64)
#define S_UM_06 6

typedef MEDWORD    FIXED_UM_07;
#define V_UM_07(val) (MEDWORD)(val*128)
#define S_UM_07 7

/******************************************************************************/
/* Signed Long Fixed Point Types                                              */
/******************************************************************************/
typedef LONGINT FIXED_SL_00;
#define S_SL_00 0

typedef LONGINT FIXED_SL_01;
#define S_SL_01 1

typedef LONGINT FIXED_SL_02;
#define S_SL_02 2

typedef LONGINT FIXED_SL_03;
#define S_SL_03 3

typedef LONGINT FIXED_SL_04;
#define S_SL_04 4

typedef LONGINT FIXED_SL_05;
#define S_SL_05 5

typedef LONGINT FIXED_SL_06;
#define S_SL_06 6

typedef LONGINT FIXED_SL_07;
#define S_SL_07 7

typedef LONGINT FIXED_SL_08;
#define S_SL_08 8

typedef LONGINT FIXED_SL_09;
#define S_SL_09 9

typedef LONGINT FIXED_SL_10;
#define S_SL_10 10

typedef LONGINT FIXED_SL_11;
#define S_SL_11 11

typedef LONGINT FIXED_SL_12;
#define S_SL_12 12

typedef LONGINT FIXED_SL_13;
#define S_SL_13 13

typedef LONGINT FIXED_SL_14;
#define S_SL_14 14

typedef LONGINT FIXED_SL_15;
#define S_SL_15 15

typedef LONGINT FIXED_SL_16;
#define S_SL_16 16

typedef LONGINT FIXED_SL_17;
#define S_SL_17 17

typedef LONGINT FIXED_SL_18;
#define S_SL_18 18

typedef LONGINT FIXED_SL_19;
#define S_SL_19 19

typedef LONGINT FIXED_SL_20;
#define S_SL_20 20

typedef LONGINT FIXED_SL_21;
#define S_SL_21 21

typedef LONGINT FIXED_SL_22;
#define S_SL_22 22

typedef LONGINT FIXED_SL_23;
#define S_SL_23 23

typedef LONGINT FIXED_SL_24;
#define S_SL_24 24

typedef LONGINT FIXED_SL_25;
#define S_SL_25 25

typedef LONGINT FIXED_SL_26;
#define S_SL_26 26

typedef LONGINT FIXED_SL_27;
#define S_SL_27 27

typedef LONGINT FIXED_SL_28;
#define S_SL_28 28

typedef LONGINT FIXED_SL_29;
#define S_SL_29 29

typedef LONGINT FIXED_SL_30;
#define S_SL_30 30

typedef LONGINT FIXED_SL_31;
#define S_SL_31 31


/******************************************************************************/
/* Unsigned Long Fixed Point Types                                            */
/******************************************************************************/
typedef LONGWORD FIXED_UL_00;
#define S_UL_00 0

typedef LONGWORD FIXED_UL_01;
#define S_UL_01 1

typedef LONGWORD FIXED_UL_02;
#define S_UL_02 2

typedef LONGWORD FIXED_UL_03;
#define S_UL_03 3

typedef LONGWORD FIXED_UL_04;
#define S_UL_04 4

typedef LONGWORD FIXED_UL_05;
#define S_UL_05 5

typedef LONGWORD FIXED_UL_06;
#define S_UL_06 6

typedef LONGWORD FIXED_UL_07;
#define S_UL_07 7

typedef LONGWORD FIXED_UL_08;
#define S_UL_08 8

typedef LONGWORD FIXED_UL_09;
#define S_UL_09 9

typedef LONGWORD FIXED_UL_10;
#define S_UL_10 10

typedef LONGWORD FIXED_UL_11;
#define S_UL_11 11

typedef LONGWORD FIXED_UL_12;
#define S_UL_12 12

typedef LONGWORD FIXED_UL_13;
#define S_UL_13 13

typedef LONGWORD FIXED_UL_14;
#define S_UL_14 14

typedef LONGWORD FIXED_UL_15;
#define S_UL_15 15

typedef LONGWORD FIXED_UL_16;
#define S_UL_16 16

typedef LONGWORD FIXED_UL_17;
#define S_UL_17 17

typedef LONGWORD FIXED_UL_18;
#define S_UL_18 18

typedef LONGWORD FIXED_UL_19;
#define S_UL_19 19

typedef LONGWORD FIXED_UL_20;
#define S_UL_20 20

typedef LONGWORD FIXED_UL_21;
#define S_UL_21 21

typedef LONGWORD FIXED_UL_22;
#define S_UL_22 22

typedef LONGWORD FIXED_UL_23;
#define S_UL_23 23

typedef LONGWORD FIXED_UL_24;
#define S_UL_24 24

typedef LONGWORD FIXED_UL_25;
#define S_UL_25 25

typedef LONGWORD FIXED_UL_26;
#define S_UL_26 26

typedef LONGWORD FIXED_UL_27;
#define S_UL_27 27

typedef LONGWORD FIXED_UL_28;
#define S_UL_28 28

typedef LONGWORD FIXED_UL_29;
#define S_UL_29 29

typedef LONGWORD FIXED_UL_30;
#define S_UL_30 30

typedef LONGWORD FIXED_UL_31;
#define S_UL_31 31

typedef LONGWORD FIXED_UL_32;
#define S_UL_32 32

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0   950125 rca      Checked in original file into database.
* 1.1   950228 tgi      expanded FIXED_UL and FIXED_SL typedefs
*                       added scale definitions for all types defined
* 1.2,3 950831 rca      Added 24-bit data types.
* 1.4   951014 rca      Added "V_" functions for all data types.
* 1.5   951116 rca      Corrected the casting of the "V_" medium sized
*                        functions.
* 1.6   960415 rca      Added comments in header section. No new functionality
*                        was added.
* 1.8   960417 rca      Corrected FIXED_UL typedefs to be LONGWORD types
* 5     981209 gzd      New Files from level 24 integration
* 7     981209 gzd      New Files from level 26 integration
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   021030 kan 2027 Transmission software merge:
*              hdb 1952 Increase resolution of Duty Cycle increment values,
*                         Add definitions to support new T_PERCENT_0_nnn
*                         datatypes:
*                             FIXED_UW_17, FIXED_UW_18, FIXED_UW_19,
*                             FIXED_UW_20
*
******************************************************************************/
/*
* $Source: common@brighton.tcb:core_dc2:t_fixed.h $
* $Revision: 1.1 $
* $Author: brighton.tcb:/users/mrwoznic/dsds/core_dc2:mrwoznic $
*/

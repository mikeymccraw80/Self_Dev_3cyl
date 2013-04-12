#ifndef T_TABLES
#define T_TABLES
/******************************************************************************
 *
 * Filename:          t_tables.h
 *
 * Description:       This file contains global definitions associated
 *                    with this project.  All information is considered
 *                    public.
 *
 *                    The following non-instrumented data types are
 *                    declared within this file:
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
 * Copyright 1994-2003, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#10/incl/t_tables.h/1 %
 * %date_created:  Wed Mar 19 09:46:43 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_base.h"

/******************************************************************************
 *  Math Library Include Files
 *****************************************************************************/

/* use this type as an intermediate value when using an independent lookup */
typedef WORD    T_AXIS;

/* Calibration Table Declarations */

/* 2D Unsigned 16-bit tables */
typedef struct {
   WORD length;
   WORD data[2];
   } MAP2_UW;
typedef struct {
   WORD length;
   WORD data[3];
   } MAP3_UW;
typedef struct {
   WORD length;
   WORD data[5];
   } MAP5_UW;
typedef struct {
   WORD length;
   WORD data[7];
   } MAP7_UW;
typedef struct {
   WORD length;
   WORD data[9];
   } MAP9_UW;
typedef struct {
   WORD length;
   WORD data[17];
   } MAP17_UW;
typedef struct {
   WORD length;
   WORD data[18];
   } MAP18_UW;
typedef struct {
   WORD length;
   WORD data[24];
   } MAP24_UW;
typedef struct {
   WORD length;
   WORD data[89];
   } MAP89_UW;

/* 2D Unsigned 32-bit tables */
typedef struct {
   WORD length;
   LONGWORD data[3];
   } MAP3_UL;
typedef struct {
   WORD length;
   LONGWORD data[2];
   } MAP2_UL;
typedef struct {
   WORD length;
   LONGWORD data[5];
   } MAP5_UL;
typedef struct {
   WORD length;
   LONGWORD data[9];
   } MAP9_UL;
typedef struct {
   WORD length;
   LONGWORD data[17];
   } MAP17_UL;

/* 3D  32 bit tables */
typedef struct {
   WORD x_length;
   WORD y_length;
   LONGINT data[24][17];
   } MAP24x17_SL;

typedef struct {
   WORD x_length;
   WORD y_length;
   LONGWORD data[20][17];
   } MAP20x17_UL;

typedef struct {
   WORD x_length;
   WORD y_length;
   LONGWORD data[21][17];
   } MAP21x17_UL;

typedef struct {
   WORD x_length;
   WORD y_length;
   LONGWORD data[21][19];
   } MAP21x19_UL;

typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[20][19];
   } MAP20x19_UL;

typedef struct {
   WORD x_length;
   WORD y_length;
   LONGWORD data[24][17];
   } MAP24x17_UL;

/* 2D Signed 16-bit tables */
typedef struct {
   WORD length;
   INTEGER data[2];
   } MAP2_SW;
typedef struct {
   WORD length;
   INTEGER data[3];
   } MAP3_SW;
typedef struct {
   WORD length;
   INTEGER data[5];
   } MAP5_SW;
typedef struct {
   WORD length;
   INTEGER data[6];
   } MAP6_SW;
typedef struct {
   WORD length;
   INTEGER data[9];
   } MAP9_SW;
typedef struct {
   WORD length;
   INTEGER data[17];
   } MAP17_SW;
typedef struct {
   WORD length;
   INTEGER data[129];
   } MAP129_SW;

/* 3D Unsigned tables */
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[2][2];
   } MAP2x2_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[2][3];
   } MAP2x3_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[2][5];
   } MAP2x5_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[2][8];
   } MAP2x8_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[2][9];
   } MAP2x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[2][17];
   } MAP2x17_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[2][33];
   } MAP2x33_UW;

typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[3][2];
   } MAP3x2_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[3][3];
   } MAP3x3_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[3][5];
   } MAP3x5_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[3][9];
   } MAP3x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[3][17];
   } MAP3x17_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[3][33];
   } MAP3x33_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[4][7];
   } MAP4x7_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][2];
   } MAP5x2_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][3];
   } MAP5x3_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][5];
   } MAP5x5_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][9];
   } MAP5x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][17];
   } MAP5x17_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][33];
   } MAP5x33_UW;

typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[7][6];
   } MAP7x6_UW;

typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[8][5];
   } MAP8x5_UW;

	typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[8][6];
   } MAP8x6_UW;
	typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[9][2];
   } MAP9x2_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[9][3];
   } MAP9x3_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[9][5];
   } MAP9x5_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[9][9];
   } MAP9x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[9][17];
   } MAP9x17_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[9][33];
   } MAP9x33_UW;

typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[11][11];
   } MAP11x11_UW;
   
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[12][7];
   } MAP12x7_UW;

typedef struct {
   BYTE x_length;
   BYTE y_length;
   BYTE mapFact;
   BYTE data[13][9];
   } MAP13x9_UB;

typedef struct {
   BYTE x_length;
   BYTE y_length;
   BYTE mapFact;
   BYTE data[13][10];
   } MAP13x10_UB;

  
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][2];
   } MAP17x2_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][3];
   } MAP17x3_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][5];
   } MAP17x5_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][9];
   } MAP17x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][17];
   } MAP17x17_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][19];
   } MAP17x19_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][33];
   } MAP17x33_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[21][8];
   } MAP21x8_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[24][17];
   } MAP24x17_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[33][2];
   } MAP33x2_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[33][3];
   } MAP33x3_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[33][5];
   } MAP33x5_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[33][9];
   } MAP33x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[33][17];
   } MAP33x17_UW;

/* 3D Signed tables */

typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[2][2];
   } MAP2x2_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[2][3];
   } MAP2x3_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[2][5];
   } MAP2x5_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[2][9];
   } MAP2x9_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[2][17];
   } MAP2x17_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[2][33];
   } MAP2x33_SW;

typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[3][2];
   } MAP3x2_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[3][3];
   } MAP3x3_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[3][5];
   } MAP3x5_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[3][9];
   } MAP3x9_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[3][17];
   } MAP3x17_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[3][33];
   } MAP3x33_SW;

typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[5][2];
   } MAP5x2_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[5][3];
   } MAP5x3_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[5][5];
   } MAP5x5_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[5][6];
   } MAP5x6_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[5][9];
   } MAP5x9_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[5][17];
   } MAP5x17_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[5][33];
   } MAP5x33_SW;

typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[9][2];
   } MAP9x2_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[9][3];
   } MAP9x3_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[9][5];
   } MAP9x5_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[9][9];
   } MAP9x9_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[9][17];
   } MAP9x17_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[9][33];
   } MAP9x33_SW;

typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[17][2];
   } MAP17x2_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[17][3];
   } MAP17x3_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[17][5];
   } MAP17x5_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[17][9];
   } MAP17x9_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[17][17];
   } MAP17x17_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[17][33];
   } MAP17x33_SW;

typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[25][17];
   } MAP25x17_SW;

typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[25][33];
   } MAP25x33_SW;

typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[32][5];
   } MAP32x5_SW;

typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[33][2];
   } MAP33x2_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[33][3];
   } MAP33x3_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[33][5];
   } MAP33x5_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[33][9];
   } MAP33x9_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[33][17];
   } MAP33x17_SW;

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0   941213 rca      removed functional prototypes and put in lookup.h so
*                        that this file can be created by Genesis 00 tool
*                        (which doesn't do functional prototypes)
* 1.1   950308 nda      Header information added to match standard
* 1.2   950313 rca      Mitch added 2-d unsigned 32-bit tables
* 1.3   950323 rca      added T_AXIS type for use as an intermediate value when
*                        using Independent Lookup functions
* 1.4   950523 rca      added axis of size 2 to all table types
* 5     981209 gzd      New Files from level 24 integration
* 7     981209 gzd      New Files from level 26 integration
* 1.8   970315 as       Added MAP21x8_UW and MAP5x6_SW
* 1.9   971107 pdb 0345 Implement Crankshaft Misfire Diagnostic
*                        -Added MAP24x17_SL, MAP24x17_UL, MAP24x17_UW, and
*                         MAP24_UW
*                        -Added MAP33x33_SL and MAP33x33_UL for 32 bit table
*                         Lookup function definitions.
* 1.10  980525 blt 0526 Incorporate math library version 2.6a into C Core
* 1.11  990528 wei 0243 Changed MAP24x17_UL to MAP20x17_UL and
*                       replaced MAP24x17_UW with MAP20x17_UB_LKP(in file
*                       t_tbltyp.h)  for MISF table size reduce.
* 1.12  990504 as  0203 Added MAP18_UW
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   001002 gps 1029 VCPS - Modular Version of Cam Phasing.
*                       Added MAP11x11_UW.
* 1.3   001013 woz 1048 Added MAP17x19_UW.
* 1.4   001206 gps 0901 Upgrade Math Library to 3.8f.
*                       Added math_typ.h.
*                       Removed redundant table type definitions.
* 1.5   010614 caw 1267 Added MAP129_SW.
* 1.6   010717 cj  0511 Merged changes from Daewoo Node 96f0.  The collection
*                        of changes included the following RSMs:
*                        0511, 0512, 0626, 0693, 0773, 0782, 0884, 0888,
*                        0949, 0984, 1002, 1008, 1077, 1176, 1178, 1298, 
*                        and 1314.
* 1.7   010807 caw 1425 Added MAP6_SW
* 1.8   010913 caw 1468 Added MAP73_UW
* 1.9   010915 jbn 1467 Added MAP2x8_UW
* 1.10  021019 gps 2110 AIRF: Increase frequency range of airmeter table.
*                       Changed MAP73_UW -> MAP89_UW.
* 1.11  021029 kan 2027 Transmission software merge.
* 6     030603 gps 2602 PSE/TSE: Change TSE Table Breakpoints to Handle
*                        High Air Flow Applications.
*                       Added MAP12x7_UW.
* 7     030605 gps 1934 AECS, EPSE/ETSE : VE Multiplier to Fuel Shift
*                        Due High IAT.
*                       Added MAP4x7_UW type definition.
*
* 07/22/05		LShoujun    mt20u2#4
* + Downsize Misfire threshold table and limit History Counter update.  
*   - Defined MAP20x19_UL, MAP7x6_UW.
*
******************************************************************************/

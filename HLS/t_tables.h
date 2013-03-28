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
 * Copyright 1994-2010, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 *
 * %full_name:      tcb_pt1#4/incl/t_tables.h/tci_pt3#11.9.17 %
 * %date_created:   Tue Jul 05 19:07:24 2011 %
 * %version:        tci_pt3#11.9.17 %
 * %derived_by:     sz561c %
 *
 *****************************************************************************/

/******************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_base.h"

/******************************************************************************
 *  Math Library Include Files
 *****************************************************************************/
//#include "mathlib.h"

/* use this type as an intermediate value when using an independent lookup */
typedef WORD         T_AXIS;
#define V_AXIS(val)  (WORD)((val)*256)
#define S_AXIS        8

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

/* 2D signed  32 bit tables */
typedef struct
{
  WORD     length;
  LONGINT  data[9];
} MAP9_SL;

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
   LONGWORD data[22][17];
   } MAP22x17_UL;

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
   INTEGER data[7];
   } MAP7_SW;
typedef struct {
   WORD length;
   INTEGER data[9];
   } MAP9_SW;
typedef struct {
   WORD length;
   INTEGER data[13];
   } MAP13_SW;
typedef struct {
   WORD length;
   INTEGER data[17];
   } MAP17_SW;
typedef struct {
   WORD length;
   INTEGER data[23];
   } MAP23_SW;
typedef struct {
   WORD length;
   INTEGER data[25];
   } MAP25_SW;
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
   WORD data[2][11];
   } MAP2x11_UW;
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
   WORD data[3][16];
   } MAP3x16_UW;
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

typedef struct
{ BYTE x_length;
  BYTE y_length;
  BYTE mapFact;
  SHORTINT data[5][6];
} MAP5x6_SB;

typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][6];
   } MAP5x6_UW;

typedef struct
{ BYTE x_length;
  BYTE y_length;
  BYTE mapFact;
  SHORTINT data[5][9];
} MAP5x9_SB;

typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][9];
   } MAP5x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][10];
   } MAP5x10_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][11];
   } MAP5x11_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[5][16];
   } MAP5x16_UW;
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
   WORD data[6][5];
   } MAP6x5_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[7][9];
   } MAP7x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[8][5];
   } MAP8x5_UW;
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
   WORD data[9][7];
   } MAP9x7_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[9][9];
   } MAP9x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[9][10];
   } MAP9x10_UW;
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
   WORD data[10][26];
   } MAP10x26_UW;
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
   WORD x_length;
   WORD y_length;
   WORD data[22][21];
   } MAP22x21_UW;

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
   BYTE data[17][6];
   } MAP17x6_UB;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[13][9];
   } MAP13x9_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[6][17];
   } MAP6x17_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[13][17];
   } MAP13x17_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[13][17];
   } MAP13x17_UW;
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
   WORD data[17][6];
   } MAP17x6_UW;
 typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][7];
   } MAP17x7_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][9];
   } MAP17x9_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[17][10];
   } MAP17x10_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[17][10];
   } MAP17x10_SW;
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
   WORD data[20][5];
   } MAP20x5_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[20][7];
   } MAP20x7_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[21][7];
   } MAP21x7_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[21][8];
   } MAP21x8_UW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[21][13];
   } MAP21x13_UW;

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
   INTEGER data[4][10];
   } MAP4x10_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[4][11];
   } MAP4x11_SW;

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
   INTEGER data[5][4];
   } MAP5x4_SW;
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
   INTEGER data[5][10];
   } MAP5x10_SW;
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
   INTEGER data[7][8];
   } MAP7x8_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[7][9];
   } MAP7x9_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   WORD data[7][10];
   } MAP7x10_SW;

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
   INTEGER data[9][7];
   } MAP9x7_SW;
typedef struct {
   WORD x_length;
   WORD y_length;
   INTEGER data[9][13];
   } MAP9x13_SW;
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
   INTEGER data[10][26];
   } MAP10x26_SW;

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
   INTEGER data[17][15];
   } MAP17x15_SW;
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
   INTEGER data[19][5];
   } MAP19x5_SW;
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
   INTEGER data[29][20];
   } MAP29x20_SW;
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

typedef struct {
  WORD Slope;
  WORD Intercept;
} MAP_SignalConv_UW;

typedef struct {
  INTEGER Slope;
  INTEGER Intercept;
} MAP_SignalConv_SW;

typedef struct {
   BYTE x_length;
   BYTE y_length;
   BYTE mapFact;
   BYTE data[4][4];
} MAP4x4_UB_LKP;

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
* 8     030715 adh 2825 Added MAP13_SW for TIS Default
* 7.1.1 030815 jyz 3073 Added MAP7x9_UW
* 7.2.1 030818 rmn 3052 Added MAP7_SW
* 7.3   030908 hdb ---- Merged 't_tables.h-7.1.1' with 't_tables.h-7.2.2'.
* 10.0  030922 arr ---- Merged 't_tables.h-9' with 't_tables.h-kok_pt1#8'.
* 11.0  083004 at  4088 Added MAP22x17_UL
* 11.1.1
*       050506 PVD 5051 Added MAP20x5_UW
* tci_pt3#12
*       041006 PVD 4827 TURBO Added MAP25_SW
* 11.1.2
*       051026 gps -BM- Turbo Integration Activity.
*                       Merged 't_tables.h-11.1.1' with 't_tables.h-tci_pt3#12'.
* 11.1.3
*       060303 caw 5486 Added: MAP_SignalConv_SW
*                              MAP_SignalConv_UW
* 11.1.3.1.1
*       060512 gps 5593 EPSE : Modify VE Load Dependency for Turbo.
*                       Enhancement to exh/intake pressure ratio calculation.
* tci_pt3#11.1.4
*       060517 vs  5622 Added: MAP4x11_SW
*
* 11.1.4
*       060424 PVD 5637 Added MAP5x6_UW
* 11.1.3.1.2
*       060601 PVD -BM- Merged 11.1.4 and 11.1.3.1.1
* 11.1.3.2.1
*       060522 PVD 5639 Added MAP23_SW,MAP13x17_SW, MAP17x25_SW ,MAP9x13_SW
*                             MAP7x9_SW ,MAP9x7_SW and MAP13x9_SW
* 11.1.5
*       060601 PVD -BM- Merged tci_pt3#11.1.4 and 11.1.3.2.1
* 11.1.3.1.3
*       060601 PVD -BM- Merged  11.1.5 and 11.1.3.1.2
* 11.1.3.1.4
*       060824 PVD 5642 Added : MAP17x6_UW ,MAP21x13_UW, MAP29x20_SW
* ktc_pt1#11.2
*        060516 rmn 5698 Added: MAP6x5_UW
* ktc_pt1#11.2.1
*        070313 dvo 6198 Added: MAP5x16_UW
* ktc_pt1#11.3
*        060703 rmn ---- Merged 't_tables.h-ktc_pt1#11.2' with 't_tables.h-11.1.4'.
* ktc_pt1#11.7
*        070307 dvo 6198 Added: MAP5x16_UW
* ktc_pt1#11.7.1
*        071226 vch 6747 Added: MAP5x4_SW

* ktc_pt1#11.8
*        070424 ksl -BM- Merged 't_tables.h-ktc_pt1#11.7' with 't_tables.h-ktc_pt1#11.2.1'.
* 11.4   060918 tjd -BM- Merged 't_tables.h-ktc_pt1#11.3' with 't_tables.h-11.1.3.1.4'.
* tci_pt3#11.1.3.1.5
*       060926 sdj 5367 Added : MAP20x7_UW
* tci_pt3#11.1.3.1.6
*       061018 sdj 5367 Merged 't_tables.h-tci_pt3#11.1.3.1.5' with
*                        't_tables.h-11.4'.
* tci_pt3#11.5
*        060824 PVD 5747 Added MAP6x17_SW , MAP3x16_UW
* tcp_pwt2#11.6
*        070119 epm 5908 Added MAP5x10_UW , MAP9x10_UW, MAP10x26_UW and MAP10x17_UW
* 11.8
*        070321 teg 5908 Added MAP17x10_SW
* 11.9
*        070411 teg 5913 Rev 3: Added MAP10x26_SW and MAP5x10_SW
* 11.9.1
*        070427 teg -BM- Merged 't_tables.h-ktc_pt1#11.8' with 't_tables.h-11.9'.
* tcp_pwt2#11.9.1
*        070517 epm 5912 Added MAP13x17_UW
* 11.9.2 070726 vs  6216 Added MAP9_SL
* 11.9.4
*       070919 gps -BM- Merged 't_tables.h-11.9.3' with 't_tables.h-tcp_pwt2#11.9.3'.
* 11.9.3.1.1
*        070928 sjl 5944 Added MAP21x7_UW
* 11.9.5 071004 me  xxxx Merged from 't_tables.h~11.9.4'
*                        and 't_tables.h~11.9.3.1.1'
* 11.9.3.2.1
*        071009 cjk 6247 Update accessory torque function in Torque 3
*                        - add MAP17x15_SW
* 11.9.5.1.1
*        071206 cjk -BM- Merged 't_tables.h~11.9.5' with 't_tables.h~11.9.3.2.1'
* 11.9.6
*        071126 grb 6288 Added MAP5x11_UW
* 11.9.7 071206 cjk -BM- Merged 't_tables.h~11.9.5.1.1' with 't_tables.h~11.9.6'
* 11.9.7.1.1
*        080320 rbg 6746 Added MAP2x12_UW
* 11.9.7.1.2
*        080407 rbg 6747 Removed MAP2x12_UW, added MAP2x11_UW
* 11.9.8 080207 caw -BM- Merges
* 11.9.9 080402 rbg -BM- Merged t_tables.h~11.9.7.1.1 with t_tables.h~11.9.8
* 11.9.9.1.1
*        080403 grb 6943 Add MAP19x5_SW table.
* 11.9.10
*        080414 caw -BM- Merges
* 11.9.11
*        080417 grb -BM- Merged 't_tables.h~11.9.10' with 't_tables.h~11.9.9.1.1'.
* kok_pt2#11.9.11.1.1
*        090910 rbg 8125 Updated T_AXIS adding V_AXIS, S_AXIS
* 11.9.12
*        000828  MU 8194 Added  MAP17x7_UW table.
*
* 11.9.13.1.1
*        100205 grb 8214 Added MAP4x10_SW
* kok_pt2#11.9.12.1.1
*        090922 kn  8024 Added MAP22x19_UW table.
* kok_pt2#11.9.14
*        100115 kn  -BM- Merged 't_tables.h~kok_pt2#11.9.13' with
*                        't_tables.h~kok_pt2#11.9.12.1.1'.
* tci_pt3#11.9.14.1.1
*        100215 SMM 8542 Modified the table type from 'MAP22X19_UW' to
*                        'MAP22X21_UW'.
* kok_pt2#11.9.14.1.1.1.1
*        100310 kn  8660 Added MAP17x6_UB table
* kok_pt2#11.9.14.1.1.2.1
*        100310 pjb 8600 Added table type MAP7x8_SW
* kok_pt2#11.9.14.1.1.1.2
*        100324 kn  -BM- Merged 't_tables.h~kok_pt2#11.9.14.1.1.1.1' with
*                               't_tables.h~kok_pt2#11.9.14.1.1.2.1'.
* kok_pt2#11.9.14.1.1.1.3
*        100331 grb -BM- Merged 't_tables.h~kok_pt2#11.9.14.1.1.1.2' with
*                               't_tables.h~kok_pt2#11.9.13.1.1'.
* tci_pt3#11.9.14.1.1.1.4
*        100428 nag 8641 Added MAP5x6_SB and MAP5x9_SB
* kok_pt2#11.9.15
*        100719 mcb 8794 Added MAP7x10_SW
* kok_pt2#11.9.16
*        100824 mcb -BM- Merge 't_tables.h~kok_pt2#11.9.15'
*                         't_tables.h~tci_pt3#11.9.14.1.1.1.4'
* tci_pt3#11.9.17
*        110711 vk  9407 Added MAP4x4_UB_LKP
*
******************************************************************************/

/* ============================================================================ *\
 * mod_cals.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       mod_cals.c-5:csrc:mt20a#2
 * Revision:        5
 * Creation date:   Friday, June 14, 2002 4:10:39 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the Mode 4 snapshot calibrations.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#if 0
#include "mod_cals.h" /* for Modes4BaudRateType,
                             Modes4HeaderType,
                             Modes4TableNumber,
                             Modes4SlowTableBlockSizeType,
                             M4CalSessionState_Type,
                             M4CalSessionState,
                             M4CalBaudRate,
                             M4CalHeader,
                             M4CalFastTableNumber,
                             M4CalSlowTableNumber,
                             M4CalSlowTableBlockSize,
                             AddressTableSnapshot1,
                             AddressTableSnapshot2,
                             AddressTableSnapshot3,
                             AddressTableSnapshot4,
                             AddressTableSnapshot5,
                             AddressTableSnapshot6,
                             AddressTableSnapshot7,
                             AddressTableSnapshot8,
                             AddressTableSnapshot9,
                             MaximumATSnapshot1Size,
                             MaximumATSnapshot2Size,
                             MaximumATSnapshot3Size,
                             MaximumATSnapshot4Size,
                             MaximumATSnapshot5Size,
                             MaximumATSnapshot6Size,
                             MaximumATSnapshot7Size,
                             MaximumATSnapshot8Size,
                             MaximumATSnapshot9Size */
#include "reuse.h"    /* for uint8_t, bool, uint16_t */

extern uint8_t RxFormatByte;

/*- AddressTableSnapshot_ should be  table of constant pointer to uint8_t, -*/
/*- but CALDEF can not accept pointers as calconst. That's why the tables    -*/
/*- are declared as table of const uint16_t's with elements that are         -*/
/*- pointers casted to uint16_t.                                             -*/

/*--- Address Table 1 for snapshot in ReadDataByLocalId and Modes4. ---*/
/*--- The maximum size is based on old Modes tables.		    ---*/
/*--- To have table smaller than the maximum size, just end it by   ---*/
/*--- a null pointer (RxFormatByte).               ---*/

const uint16_t AddressTableSnapshot1[MaximumATSnapshot1Size] =
{
    ( uint16_t )&RxFormatByte,        /*--- 01 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 02 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 03 ---*/
    ( uint16_t )&RxFormatByte         /*--- 04 ---*/
};
/*
*| mod_cals. {
*|         AddressTableSnapshot1
*|             {
*|             :is_calconst;
*|             :elements:type = types.uint16_t;
*|             :units = "Address to SHORTCARD";
*|             :description = "Address Table 1 for snapshot in ReadDataByLocalId and Modes4.";
*|             }
*/

/*--- Address Table 2 for snapshot in ReadDataByLocalId and Modes4. ---*/
/*--- The maximum size is based on old Modes tables.		    ---*/
/*--- To have table smaller than the maximum size, just end it by   ---*/
/*--- a null pointer (RxFormatByte).               ---*/

const uint16_t AddressTableSnapshot2[MaximumATSnapshot2Size] =
{
    ( uint16_t )&RxFormatByte,        /*--- 01 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 02 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 03 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 04 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 05 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 06 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 07 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 08 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 09 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 10 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 11 ---*/
    ( uint16_t )&RxFormatByte         /*--- 12 ---*/
} ;
/*
*|         AddressTableSnapshot2
*|             {
*|             :is_calconst;
*|             :elements:type = types.uint16_t;
*|             :units = "Address to SHORTCARD";
*|             :description = "Address Table 2 for snapshot in ReadDataByLocalId and Modes4.";
*|             }
*/

/*--- Address Table 3 for snapshot in ReadDataByLocalId and Modes4. ---*/
/*--- The maximum size is based on old Modes tables.		    ---*/
/*--- To have table smaller than the maximum size, just end it by   ---*/
/*--- a null pointer (RxFormatByte).               ---*/

const uint16_t AddressTableSnapshot3[MaximumATSnapshot3Size] =
{
    ( uint16_t )& RxFormatByte,       /*--- 01 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 02 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 03 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 04 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 05 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 06 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 07 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 08 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 09 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 10 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 11 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 12 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 13 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 14 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 15 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 16 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 17 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 18 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 19 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 20 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 21 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 22 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 23 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 24 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 25 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 26 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 27 ---*/
    ( uint16_t )&RxFormatByte         /*--- 28 ---*/
} ;
/*
*|         AddressTableSnapshot3
*|             {
*|             :is_calconst;
*|             :elements:type = types.uint16_t;
*|             :units = "Address to SHORTCARD";
*|             :description = "Address Table 3 for snapshot in ReadDataByLocalId and Modes4.";
*|             }
*/

/*--- Address Table 4 for snapshot in ReadDataByLocalId and Modes4. ---*/
/*--- The maximum size is based on old Modes tables.		    ---*/
/*--- To have table smaller than the maximum size, just end it by   ---*/
/*--- a null pointer (RxFormatByte).               ---*/

const uint16_t AddressTableSnapshot4[MaximumATSnapshot4Size] =
{
    ( uint16_t )&RxFormatByte,     /*--- 01 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 02 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 03 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 04 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 05 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 06 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 07 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 08 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 09 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 10 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 11 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 12 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 13 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 14 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 15 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 16 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 17 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 18 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 19 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 20 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 21 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 22 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 23 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 24 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 25 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 26 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 27 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 28 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 29 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 30 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 31 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 32 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 33 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 34 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 35 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 36 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 37 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 38 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 39 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 40 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 41 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 42 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 43 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 44 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 45 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 46 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 47 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 48 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 49 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 50 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 51 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 52 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 53 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 54 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 55 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 56 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 57 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 58 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 59 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 60 ---*/
    ( uint16_t )&RxFormatByte         /*--- 61 ---*/
} ;
/*
*|         AddressTableSnapshot4
*|             {
*|             :is_calconst;
*|             :elements:type = types.uint16_t;
*|             :units = "Address to SHORTCARD";
*|             :description = "Address Table 4 for snapshot in ReadDataByLocalId and Modes4.";
*|             }
*/

/*--- Address Table 5 for snapshot in ReadDataByLocalId and Modes4. ---*/
/*--- The maximum size is based on old Modes tables.		    ---*/
/*--- To have table smaller than the maximum size, just end it by   ---*/
/*--- a null pointer (RxFormatByte).               ---*/

const uint16_t AddressTableSnapshot5[MaximumATSnapshot5Size] =
{
    ( uint16_t )&RxFormatByte,        /*--- 01 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 02 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 03 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 04 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 05 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 06 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 07 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 08 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 09 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 10 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 11 ---*/
    ( uint16_t )&RxFormatByte         /*--- 12 ---*/
} ;
/*
*|         AddressTableSnapshot5
*|             {
*|             :is_calconst;
*|             :elements:type = types.uint16_t;
*|             :units = "Address to SHORTCARD";
*|             :description = "Address Table 5 for snapshot in ReadDataByLocalId and Modes4.";
*|             }
*/

/*--- Address Table 6 for snapshot in ReadDataByLocalId and Modes4. ---*/
/*--- The maximum size is based on old Modes tables.		    ---*/
/*--- To have table smaller than the maximum size, just end it by   ---*/
/*--- a null pointer (RxFormatByte).               ---*/

const uint16_t AddressTableSnapshot6[MaximumATSnapshot6Size] =
{
    ( uint16_t )&RxFormatByte,        /*--- 01 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 02 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 03 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 04 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 05 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 06 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 07 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 08 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 09 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 10 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 11 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 12 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 13 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 14 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 15 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 16 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 17 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 18 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 19 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 20 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 21 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 22 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 23 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 24 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 25 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 26 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 27 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 28 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 29 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 30 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 31 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 32 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 33 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 34 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 35 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 36 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 37 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 38 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 39 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 40 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 41 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 42 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 43 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 44 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 45 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 46 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 47 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 48 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 49 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 50 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 51 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 52 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 53 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 54 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 55 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 56 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 57 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 58 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 59 ---*/
    ( uint16_t )&RxFormatByte         /*--- 60 ---*/
} ;
/*
*|         AddressTableSnapshot6
*|             {
*|             :is_calconst;
*|             :elements:type = types.uint16_t;
*|             :units = "Address to SHORTCARD";
*|             :description = "Address Table 6 for snapshot in ReadDataByLocalId and Modes4.";
*|             }
*/

/*--- Address Table 7 for snapshot in ReadDataByLocalId and Modes4. ---*/
/*--- The maximum size is based on old Modes tables.		    ---*/
/*--- To have table smaller than the maximum size, just end it by   ---*/
/*--- a null pointer (RxFormatByte).               ---*/

const uint16_t AddressTableSnapshot7[MaximumATSnapshot7Size] =
{
    ( uint16_t )&RxFormatByte,        /*--- 01 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 02 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 03 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 04 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 05 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 06 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 07 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 08 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 09 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 10 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 11 ---*/
    ( uint16_t )&RxFormatByte         /*--- 12 ---*/
} ;
/*
*|         AddressTableSnapshot7
*|             {
*|             :is_calconst;
*|             :elements:type = types.uint16_t;
*|             :units = "Address to SHORTCARD";
*|             :description = "Address Table 7 for snapshot in ReadDataByLocalId and Modes4.";
*|             }
*/

/*--- Address Table 8 for snapshot in ReadDataByLocalId and Modes4. ---*/
/*--- The maximum size is based on old Modes tables.		    ---*/
/*--- To have table smaller than the maximum size, just end it by   ---*/
/*--- a null pointer (RxFormatByte).               ---*/

const uint16_t AddressTableSnapshot8[MaximumATSnapshot8Size] =
{
    ( uint16_t )&RxFormatByte,        /*--- 01 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 02 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 03 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 04 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 05 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 06 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 07 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 08 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 09 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 10 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 11 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 12 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 13 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 14 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 15 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 16 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 17 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 18 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 19 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 20 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 21 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 22 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 23 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 24 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 25 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 26 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 27 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 28 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 29 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 30 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 31 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 32 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 33 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 34 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 35 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 36 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 37 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 38 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 39 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 40 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 41 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 42 ---*/
} ;
/*
*|         AddressTableSnapshot8
*|             {
*|             :is_calconst;
*|             :elements:type = types.uint16_t;
*|             :units = "Address to SHORTCARD";
*|             :description = "Address Table 8 for snapshot in ReadDataByLocalId and Modes4.";
*|             }
*/


/*--- Address Table 9 for snapshot in ReadDataByLocalId and Modes4. ---*/
/*--- The maximum size is based on old Modes tables.		    ---*/
/*--- To have table smaller than the maximum size, just end it by   ---*/
/*--- a null pointer (RxFormatByte).               ---*/

const uint16_t AddressTableSnapshot9[MaximumATSnapshot9Size] =
{
    ( uint16_t )&RxFormatByte,        /*--- 01 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 02 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 03 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 04 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 05 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 06 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 07 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 08 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 09 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 10 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 11 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 12 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 13 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 14 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 15 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 16 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 17 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 18 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 19 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 20 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 21 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 22 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 23 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 24 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 25 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 26 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 27 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 28 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 29 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 30 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 31 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 32 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 33 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 34 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 35 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 36 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 37 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 38 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 39 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 40 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 41 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 42 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 43 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 44 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 45 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 46 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 47 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 48 ---*/
    ( uint16_t )&RxFormatByte,        /*--- 49 ---*/
    ( uint16_t )&RxFormatByte         /*--- 50 ---*/
} ;

/*
*|         AddressTableSnapshot9
*|             {
*|             :is_calconst;
*|             :elements:type = types.uint16_t;
*|             :units = "Address to SHORTCARD";
*|             :description = "Address Table 9 for snapshot in ReadDataByLocalId and Modes4.";
*|             }
*| }
*/


#endif


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 16/03/05     Q.W         280
 * + Reallocate Calibration Space and delete Redundant Cals
 *   - Deleted M4CalBaudRate, M4CalFastTableNumber, M4CalHeader, M4CalSessionState, M4CalSlowTableBlockSize, M4CalSlowTableNumber.
 *
\* ============================================================================ */

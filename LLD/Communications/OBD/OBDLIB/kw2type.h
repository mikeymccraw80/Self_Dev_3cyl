#ifndef KW2TYPE_H
#define KW2TYPE_H
/* ============================================================================ *\
 * kw2type.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2type.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:10:16 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 data types.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/*********************************************************************/
/*            INCLUDE FILES                                          */
/*********************************************************************/

#include "reuse.h"

/*********************************************************************/
/*            EQUATES                                                */
/*********************************************************************/
#define UDWORD unsigned long


/*********************************************************************/
/* GLOBAL DATA TYPE DECLARATIONS                                     */
/*********************************************************************/


typedef struct
{
   uint8_t     Byte_One;
   uint8_t     Byte_Two;
   uint8_t     Byte_Three;
   uint8_t     Byte_Four;
} LWORD_TO_BYTE_ACCESS_TYPE;


typedef struct
{
   uint16_t    Word_One;
   uint16_t    Word_Two;
} LWORD_TO_WORD_ACCESS_TYPE;


typedef struct
{
   uint8_t     Byte_One;
   uint8_t     Byte_Two;
} WORD_TO_BYTE_ACCESS_TYPE;


typedef union
{
   LWORD_TO_BYTE_ACCESS_TYPE        Byte_Access;
   LWORD_TO_WORD_ACCESS_TYPE        Word_Access;
   UDWORD                           DWord_Access;
} FOUR_BYTE_DATA_TYPE;


typedef union
{
   WORD_TO_BYTE_ACCESS_TYPE         Byte_Access;
   uint16_t                         Word_Access;
} TWO_BYTE_DATA_TYPE;


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 12/04/05      Q.W        294
 * + Add four KW2000 SIDs: 04,14,12,19
 *  - Add new type: UWORD.          
\* ============================================================================ */
#endif
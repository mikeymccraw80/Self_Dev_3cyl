#ifndef KW2SRV21_H
#define KW2SRV21_H
/* ============================================================================ *\
 * kw2dynsh.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2dynsh.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:11:53 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 dynamic snapshot support
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "reuse.h"
#include "kw2type.h"

/* dynamic snapshot IDs */
#define rdliAddressDynSnapshot0 (0xF0)
#define rdliAddressDynSnapshot1 (0xF1)
#define rdliAddressDynSnapshot2 (0xF2)
#define rdliAddressDynSnapshot3 (0xF3)
#define rdliAddressDynSnapshot4 (0xF4)
#define rdliAddressDynSnapshot5 (0xF5)
#define rdliAddressDynSnapshot6 (0xF6)
#define rdliAddressDynSnapshot7 (0xF7)
#define rdliAddressDynSnapshot8 (0xF8)
#define rdliAddressDynSnapshot9 (0xF9)

#define DynSnapshotInvalid      (0xFF)


/* subcommands of opcode 0x23        (dynamic snapshot) */
#define DynSnapShotCmdClear     (0x04)
#define DynSnapShotCmdArmMode1  (0x01)
#define DynSnapShotCmdArmMode2  (0x02)
#define DynSnapShotCmdArmMode3  (0x03)

#define POSITION_OFFSET (0x01) /* 1st entry in data record goes here */

#define MAX_DYNAMIC_LENGTH (43) /* maximum entries allowed in list */


typedef struct
{
    uint8_t                            size ;
    uint8_t                            position ;
    uint8_t                            address[3] ;
} Dynamic_Snapshot_Data_Type ;

typedef struct
{
    uint8_t                            id ;
    uint8_t                            length ;
    Dynamic_Snapshot_Data_Type         data[MAX_DYNAMIC_LENGTH] ;
} Dynamic_Snapshot_Type ;


extern Dynamic_Snapshot_Type               dynamic_snapshot ;


/**************************************************************************/
/*                                                                        */
/* FUNCTION:  ClearDynamicSnapshot(void)                                  */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*      clears the parameters for a dynamic snapshot and marks the        */
/*      dynamic snapshot as undefined                                     */
/*                                                                        */
/* GLOBAL: dynamic_snapshot                                               */
/**************************************************************************/
uint8_t ClearDynamicSnapshot( uint8_t local_id );


/**************************************************************************/
/*                                                                        */
/* FUNCTION:  ArmDynamicSnapshot(void)                                    */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*      sets the parameters for a dynamic snapshot                        */
/*                                                                        */
/* GLOBAL: dynamic_snapshot                                               */
/**************************************************************************/
uint8_t ArmDynamicSnapshot( void );


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
\* ============================================================================ */
#endif

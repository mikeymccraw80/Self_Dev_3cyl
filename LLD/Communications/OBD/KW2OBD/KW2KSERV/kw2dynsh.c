/* ============================================================================ *\
 * kw2dynsh.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2dynsh.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:11:40 PM
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
#include "kw2api.h"
#include "kw2app.h"
#include "kw2dll.h"
#include "kw2dynsh.h"


/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */

Dynamic_Snapshot_Type               dynamic_snapshot ;


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
uint8_t ClearDynamicSnapshot( uint8_t local_id )
{
   uint8_t  err;

   if (   ( dynamic_snapshot.id == local_id )
       || ( dynamic_snapshot.id == DynSnapshotInvalid ) )
   {
       dynamic_snapshot.id = DynSnapshotInvalid ;         /* this id indicates that there is */
       /* no list defined                 */
       dynamic_snapshot.length = 0 ;                      /* additional, length ZERO */
       err = nrcNone;
   }
   else
   {
      err = nrcSubFunctionNotSupported_InvalidFormat;
   }

   return (err);
} /* End of ClearDynamicSnapshot */



/**************************************************************************/
/*                                                                        */
/* FUNCTION:  ArmDynamicSnapshot(void)                                    */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*      sets the parameters for a dynamic snapshot                        */
/*                                                                        */
/* GLOBAL: dynamic_snapshot                                               */
/**************************************************************************/
uint8_t ArmDynamicSnapshot( void )
{
   uint8_t  err;
   uint8_t  snapshot_length ;
   uint8_t  sd_idx ;
   uint8_t  adr_size ;
   uint8_t  record_idx ;

   /* k2kdata[1] = local ID */
   /* snapshot id already defined ? (clearing this is required before arming a new snapshot) */
   if ( dynamic_snapshot.id != DynSnapshotInvalid )
   {
      err = nrcSubFunctionNotSupported_InvalidFormat;
   }
   else
   {
      snapshot_length = GetKeyword2000ServiceDataLength() ;
      dynamic_snapshot.id = DynSnapshotInvalid ;         /* invalid while updating this list */
      dynamic_snapshot.length = 0 ;                      /* just to avoid accidents */
      for ( record_idx = 0, sd_idx = 2 ; sd_idx < snapshot_length ; record_idx++ )
      {
         adr_size = GetKw2000ServiceData (sd_idx++) ;
         dynamic_snapshot.data[record_idx].position = POSITION_OFFSET + GetKw2000ServiceData (sd_idx++) ;
         dynamic_snapshot.data[record_idx].size = GetKw2000ServiceData (sd_idx++) ;
         if ( adr_size != GetKw2000ServiceData(2) )
         {
             return (nrcSubFunctionNotSupported_InvalidFormat);
         }

         /* according to spec. : all parameters must use the same length of address definition */
         switch ( adr_size )
         {
         case 3:
            /* 3 byte addressing is specified */
            dynamic_snapshot.data[record_idx].address[0] = GetKw2000ServiceData (sd_idx++) ;
            if ( ( dynamic_snapshot.data[record_idx].address[0] != 0x0f)
               &&( dynamic_snapshot.data[record_idx].address[0] != 0x13))
            {
               /* illegal address page will be rejected              */
               /* and the snapshot definition is not marked as valid */
               return(nrcRequestOutOfRange) ;
            }
            dynamic_snapshot.data[record_idx].address[1] = GetKw2000ServiceData (sd_idx++) ;
            dynamic_snapshot.data[record_idx].address[2] = GetKw2000ServiceData (sd_idx++) ;
            break ;
         case 2:                                     /* other access-method to be implemented here */
             /* your code goes here ... */
         case 1:                                     /* other access-method to be implemented here */
             /* your code goes here ... */
         default :                                   /* error: wrong format */
            return (nrcSubFunctionNotSupported_InvalidFormat) ;
            break ;
         }
      }
      /* mark the snapshot definition as valid */
      dynamic_snapshot.length = record_idx ;
      dynamic_snapshot.id = GetKw2000ServiceData (1) ;
      err = nrcNone;
   }

   return (err);
}                                                          /* End of ArmDynamicSnapshot */


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 03/03/03     sgchia      106
 * + Boot Loader.
 *   - moved all variables to section .nvram_boot.
 *
 * 16/05/07     LShoujun    mt20u2#734(task)
 * + replace MCU of KG256 with xep100 - Step I
 *  - Changed compiler to Cosmic s12x
 *
 * 02/06/08     Shenghui.Zhou  mt20u2#248
 * + Add to read buffer RAM function through KW 2C command
\* ============================================================================ */

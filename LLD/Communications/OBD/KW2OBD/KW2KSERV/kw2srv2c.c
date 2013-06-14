/* ============================================================================ *\
 * kw2srv2c.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv2c.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, June 20, 2002 1:37:24 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $2C - Dynamically define local identifier
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#if 0
#include "kw2dll.h"
#include "kw2srv2c.h"
#include "kw2dynsh.h"


#define MODE_2C_MSG_LENGTH                  5
#define MODE_2C_RPLY_LENGTH                 2
#define CyLocalId                           1
#define CyMode                              2
#define CyReply                             1
#define CyLength                            4


void KwJ14230DynamicallyDefineLocalIdentifier( void )
{
   uint8_t     err;

   switch ( GetKw2000ServiceData (CyLocalId) )
   {
   case rdliAddressDynSnapshot0:
   case rdliAddressDynSnapshot1:
   case rdliAddressDynSnapshot2:
   case rdliAddressDynSnapshot3:
   case rdliAddressDynSnapshot4:
   case rdliAddressDynSnapshot5:
   case rdliAddressDynSnapshot6:
   case rdliAddressDynSnapshot7:
   case rdliAddressDynSnapshot8:
   case rdliAddressDynSnapshot9:
      switch ( GetKw2000ServiceData (CyMode) )
      {
      case DynSnapShotCmdClear:
         err = ClearDynamicSnapshot( GetKw2000ServiceData (CyLocalId) );
         if ( err == nrcNone )
         {
            /*  snapshot clear is Ok */
            WrtKw2000ServiceData( 0xf2, CyReply );
            SendStandardPositiveAnswer( MODE_2C_RPLY_LENGTH ) ;
         }
         else
         {
            SendStandardNegativeAnswer( err ) ;
         }
         break ;
      case DynSnapShotCmdArmMode1:
      case DynSnapShotCmdArmMode2:
      case DynSnapShotCmdArmMode3:
         err = ArmDynamicSnapshot();
         if ( err == nrcNone )
         {
            WrtKw2000ServiceData( GetKw2000ServiceData (CyLocalId), CyReply );
            SendStandardPositiveAnswer( MODE_2C_RPLY_LENGTH ) ;
         }
         else
         {
            SendStandardNegativeAnswer( err ) ;
         }
         break ;
      default :
         SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
         break ;
      }
      break ;
   default :
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
      break ;
   }
}


void InitKwJ14230DynamicallyDefineLocalIdentifier(void )
{
    dynamic_snapshot.length = 0 ;
    dynamic_snapshot.id = DynSnapshotInvalid ;
}

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
\* ============================================================================ */

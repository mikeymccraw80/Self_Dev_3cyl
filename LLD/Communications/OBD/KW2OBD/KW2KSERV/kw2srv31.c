/* ============================================================================ *\
 * kw2srv31.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv31.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, June 20, 2002 1:37:45 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $31 - Start routine by local ID
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
#include "kw2cfg.h"
#include "kw2srv1a.h"
#include "id.h"


#define CyKW2K_NVM_Reset_MsgSize            2
#define MODE_1A_MSG_LENGTH                  2
#define CyLocalId                           1
#define CyKW2K_Mode31Msg_Offset   (2)
#define CyKW2K_JumpToBootMsgSize      (2)

#define srliActivateSecurityAccess   (0x08)
#define srliCheckFlashEnvironment    (0x09)
#define srliDeactivateSecurityAccess (0xFE)
#define CyKW2K_NVM_Reset             (0xAA)
#define CyKW2K_CopyKernelToRAM          0xFD




/******************************************************************************
 *  Global NVM Definitions
 *****************************************************************************/
// #pragma section [nvram]
bool   NbFILE_NVM_Reset_RequestFromSerial;
// #pragma section []

void KwJ14230StartRoutineByLocalIdentifier( void )
{
   uint8_t  local_id ;
   uint8_t  new_flag;

   // if (Get_EngineTurning() || Get_VehicleMoving())
   if (0)
   {
      SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError ) ;
   }
   else
   {
      switch ( GetKw2000ServiceData (CyLocalId) )
      {
   

      case CyKW2K_NVM_Reset :
         {
            if( GetKeyword2000ServiceDataLength() != CyKW2K_NVM_Reset_MsgSize )
            {
               /* Invalid Message format */
               SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
            }
	     else if ( !GetVulnerabilityState() )
           {
               SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested ) ;
           }
            else
            {
               NbFILE_NVM_Reset_RequestFromSerial = true;
               SendStandardPositiveAnswer( CyKW2K_Mode31Msg_Offset );
            }
         }
         break;
		 
     case CyKW2K_CopyKernelToRAM :
        {
           if( GetKeyword2000ServiceDataLength() != CyKW2K_JumpToBootMsgSize )
           {
              /* Invalid Message format */
              SendStandardNegativeAnswer(
                         nrcSubFunctionNotSupported_InvalidFormat  ) ;
           }
	    else if ( !GetVulnerabilityState() )
           {
               SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested ) ;
           }
           else
           {   
                SendStandardPositiveAnswer(CyKW2K_Mode31Msg_Offset);				  
                SetCopyAndExecuteKernelPending(CbTRUE);
           }
        }
        break;
         
      default :
         SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
         break ;
      }
   }
}





/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - Changed to support generic immo
 *
 * 29/01/07     LShoujun    mt20u2#76
 * + Clear nvram area after re-programming with KWP2000
 *   - Added logic for ID of CyKW2K_NVM_Reset
\* ============================================================================ */

/* ============================================================================ *\
 * kw2srv3e.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv3e.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, June 18, 2002 9:02:05 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $3E - Tester present
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "kw2dll.h"
#include "kw2srv3e.h"



#define SyTesterPresentDataLength           1
#define SyTesterPresentDataLengthWithResp   2

#define CyRespond                           1
#define RespondYes                          0x01
#define RespondNo                           0x02



void KwJ14230TesterPresent( void )
{
    /* Check the Msg length if it is 1 */
    if ((GetKeyword2000ServiceDataLength () == SyTesterPresentDataLength))
    /* If the Msg length is 1, then send the positive response 7E. */
    {
        SendStandardPositiveAnswer (SyTesterPresentDataLength);
    }
    else if ((GetKeyword2000ServiceDataLength () == SyTesterPresentDataLengthWithResp))
    /* If the Msg length is 1, then send the positive response 7E. */
    {
        if ( GetKw2000ServiceData (CyRespond) == RespondYes )
        {
            SendStandardPositiveAnswer (SyTesterPresentDataLength);
        }
        else if ( GetKw2000ServiceData (CyRespond) == RespondNo )
        {
            /* do not respond but restart P3 timing .... */
            TimerBeforeNewMsgRx = 0;
        }
        else
        {
            SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
        }
    }
    else
    {
        /*If the Msg length was not 1 or 2, then send out the negtive
         *response.
         */
        SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
    }
} /*** End of KwJ14230TesterPresent ***/




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

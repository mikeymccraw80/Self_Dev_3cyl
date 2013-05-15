/* ============================================================================ *\
 * kw2srv30exec.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv30exec.c-1:csrc:mt20u2#51
 * Revision:        1
 * Creation date:   June 8, 2006 1:37:34 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $30 execution funcion- Input/output control by local identifier
 *   
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#if 0
#include "kw2srv30exec.h"
#include "kw2srv30.h"
#include "kw2dll.h"
/**************************************************************************/
/*                                                                        */
/* FUNCTION: IOLIdCheckLight                                              */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    Kw2000 service IO Ctrl By Local ID: CheckLight                      */
/*                                                                        */
/* GLOBAL: GetKeyword2000ServiceData                                      */
/**************************************************************************/
FAR_COS void IOLIdCheckLight( uint8_t IOCtrl, uint8_t CtrlState )
{
    switch ( IOCtrl )
    {
       case iocpReturnControlToECU:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // ReleaseCheckEngineLightControlToECU() ;
               SendStandardPositiveAnswer( 3 ) ;
           }
           break ;
       case iocpReportCurrentState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // WrtKw2000ServiceData( ( GetCheckEngineLightState() ? 0xFF : 0x00 ), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
       case iocpShortTermAdjustment:
           if ( GetKeyword2000ServiceDataLength() != 4 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               if ( ( CtrlState == 0x00 ) || ( CtrlState == 0xFF ) )
               {
                  // ForceCheckEngineLight( CtrlState ) ;
                   SendStandardPositiveAnswer( 4 ) ;
               }
               else
               {
                   SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
               }
           }
           break ;

       case iocpReportSlewState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
             //  WrtKw2000ServiceData( (uint8_t) GetCheckEngineLightSlewState(), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
/* PC_HUD */


       default :
           SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           break ;
    }

}

/**************************************************************************/
/*                                                                        */
/* FUNCTION: IOLIdCharcoalCanisterPurgeOnOff                              */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    Kw2000 service IO Ctrl By Local ID: CharcoalCanisterPurgeOnOff      */
/*                                                                        */
/* GLOBAL: GetKeyword2000ServiceData                                      */
/**************************************************************************/
FAR_COS void IOLIdCharcoalCanisterPurgeOnOff( uint8_t IOCtrl, uint8_t CtrlState )
{
    switch ( IOCtrl )
    {
       case iocpReturnControlToECU:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // ReleaseCharcoalCanisterPurgeControlToECU() ;
               SendStandardPositiveAnswer( 3 ) ;
           }
           break ;
       case iocpReportCurrentState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
             //  WrtKw2000ServiceData( ( FixConvertPercentWToPercentB( GetCharcoalCanisterPurgeDutyCycle() ) ?
               //                                       0xFF : 0x00 ), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
       case iocpShortTermAdjustment:
           if ( GetKeyword2000ServiceDataLength() != 4 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               if ( ( CtrlState == 0x00 ) || ( CtrlState == 0xFF ) )
               {
                  // ForceCharcoalCanisterPurge( ( CtrlState ?
                   //                              FixDefConst( Max_Percent_W, Percent_W ) : FixDefConst( Min_Percent_W,
                    //                                                                                    Percent_W ) )
                  //                              ) ;
                   SendStandardPositiveAnswer( 4 ) ;
               }
               else
               {
                   SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
               }
           }
           break ;

       case iocpReportSlewState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // WrtKw2000ServiceData( (uint8_t) GetCharcoalCanisterPurgeSlewState(), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
 /* PC_HUD */


       default :
           SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           break ;
    }
}                                                          /* End Of IOLIdCharcoalCanisterPurgeOnOff */

/**************************************************************************/
/*                                                                        */
/* FUNCTION: IOLIdFuelPumpRelay                                           */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    Kw2000 service IO Ctrl By Local ID: FuelPumpRelay                   */
/*                                                                        */
/* GLOBAL: GetKeyword2000ServiceData                                      */
/**************************************************************************/
FAR_COS void IOLIdFuelPumpRelay( uint8_t IOCtrl, uint8_t CtrlState )
{
    switch ( IOCtrl )
    {
       case iocpReturnControlToECU:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // ReleaseFuelPumpControlToECU() ;
               SendStandardPositiveAnswer( 3 ) ;
           }
           break ;
       case iocpReportCurrentState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               //WrtKw2000ServiceData( ( GetFuelPumpState() ? 0xFF : 0x00 ), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
       case iocpShortTermAdjustment:
           if ( GetKeyword2000ServiceDataLength() != 4 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               if ( ( CtrlState == 0x00 ) || ( CtrlState == 0xFF ) )
               {
                  // ForceFuelPump( (bool) CtrlState ) ;
                   SendStandardPositiveAnswer( 4 ) ;
               }
               else
               {
                   SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
               }
           }
           break ;
       case iocpReportSlewState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               //WrtKw2000ServiceData( (uint8_t) GetFuelPumpSlewState(), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
 /* PC_HUD */


       default :
           SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           break ;
    }
}                                                          /* End Of IOLIdFuelPumpRelay */

/**************************************************************************/
/*                                                                        */
/* FUNCTION: IOLIdACCutoffRelay                                           */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    Kw2000 service IO Ctrl By Local ID: ACCutoffRelay                   */
/*                                                                        */
/* GLOBAL: GetKeyword2000ServiceData                                      */
/**************************************************************************/
FAR_COS void IOLIdACCutoffRelay( uint8_t IOCtrl, uint8_t CtrlState )
{
    switch ( IOCtrl )
    {
       case iocpReturnControlToECU:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // ReleaseACClutchRelayControlToECU() ;
               SendStandardPositiveAnswer( 3 ) ;
           }
           break ;
       case iocpReportCurrentState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // WrtKw2000ServiceData( ( GetACClutchRelayState() ? 0xFF : 0x00 ), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
       case iocpShortTermAdjustment:
           if ( GetKeyword2000ServiceDataLength() != 4 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               if ( ( CtrlState == 0x00 ) || ( CtrlState == 0xFF ) )
               {
                   if ( GetEngineTurning() )
                   /*--- if engine turning only: ---*/
                   {
                       //ForceACClutchRelay( (bool) CtrlState ) ;
                       SendStandardPositiveAnswer( 4 ) ;
                   }
                   else
                   {
                       SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError ) ;
                   }
               }
               else
               {
                   SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
               }
           }
           break ;
       case iocpReportSlewState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // WrtKw2000ServiceData( (uint8_t)GetACClutchRelaySlewState(), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
/* PC_HUD */


       default :
           SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           break ;
    }
}                                                          /* End Of IOLIdACCutoffRelay */

/**************************************************************************/
/*                                                                        */
/* FUNCTION: IOLIdFan1                                                    */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    Kw2000 service IO Ctrl By Local ID: Fan1                            */
/*                                                                        */
/* GLOBAL: GetKeyword2000ServiceData                                      */
/**************************************************************************/
FAR_COS void IOLIdFan1( uint8_t IOCtrl, uint8_t CtrlState )
{
    switch ( IOCtrl )
    {
       case iocpReturnControlToECU:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // ReleaseFan1ControlToECU() ;
               SendStandardPositiveAnswer( 3 ) ;
           }
           break ;
       case iocpReportCurrentState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
              // WrtKw2000ServiceData( ( GetFan1State() ? 0xFF : 0x00 ), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
       case iocpShortTermAdjustment:
           if ( GetKeyword2000ServiceDataLength() != 4 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               if ( ( CtrlState == 0x00 ) || ( CtrlState == 0xFF ) )
               {
                  // ForceFan1( (bool) CtrlState ) ;
                   SendStandardPositiveAnswer( 4 ) ;
               }
               else
               {
                   SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
               }
           }
           break ;
       case iocpReportSlewState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               //WrtKw2000ServiceData( (uint8_t) GetFan1SlewState() , 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
 /* PC_HUD */


       default :
           SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           break ;
    }
}                                                          /* End Of IOLIdFan1 */

/**************************************************************************/
/*                                                                        */
/* FUNCTION: IOLIdFan2                                                    */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    Kw2000 service IO Ctrl By Local ID: Fan2                            */
/*                                                                        */
/* GLOBAL: GetKeyword2000ServiceData                                      */
/**************************************************************************/
FAR_COS void IOLIdFan2( uint8_t IOCtrl, uint8_t CtrlState )
{
    switch ( IOCtrl )
    {
       case iocpReturnControlToECU:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               //ReleaseFan2ControlToECU() ;
               SendStandardPositiveAnswer( 3 ) ;
           }
           break ;
       case iocpReportCurrentState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               //WrtKw2000ServiceData( ( GetFan2State() ? 0xFF : 0x00 ), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
       case iocpShortTermAdjustment:
           if ( GetKeyword2000ServiceDataLength() != 4 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               if ( ( CtrlState == 0x00 ) || ( CtrlState == 0xFF ) )
               {
                  // ForceFan2( (bool) CtrlState ) ;
                   SendStandardPositiveAnswer( 4 ) ;
               }
               else
               {
                   SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
               }
           }
           break ;
       case iocpReportSlewState:
           if ( GetKeyword2000ServiceDataLength() != 3 )
           {
               SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           }
           else
           {
               //WrtKw2000ServiceData( (uint8_t) GetFan2SlewState(), 3 );
               SendStandardPositiveAnswer( 4 ) ;
           }
           break ;
/* PC_HUD */


       default :
           SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
           break ;
    }
}                                                          /* End Of IOLIdFan2 */
#endif
/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 09/06/06     Jerry.Wu    mt20u2#51
 * + Update kword spec
 *   - Add function IOLIdCheckLight, IOLIdCharcoalCanisterPurgeOnOff, IOLIdACCutoffRelay
 *   - IOLIdFan1, IOLIdFan2 and IOLIdFuelPumpRelay.
 *
\* ============================================================================ */

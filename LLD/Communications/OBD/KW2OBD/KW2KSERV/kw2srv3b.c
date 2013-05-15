/* ============================================================================ *\
 * kw2srv3b.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv3b.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:13:20 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $3b - Write data by local identifier
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */



#include "kw2type.h"
#include "kw2dll.h"
#include "kw2app.h"
#include "kw2api.h"
#include "kw2srv18.h"


#define MODE_3B_MSG_LENGTH       (2)
#define MODE_3B_RESP_LENGTH      (2)

#define IdxIdentifier            (1)
#define IdxData                  (2)


/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230WriteDataByLocalIdentifier                *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 3b functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/

void KwJ14230WriteDataByLocalIdentifier( void )
{
   uint8_t  idx, Idx_WritePointer ;
   uint16_t eeprom_value;
   uint8_t *dataprt;
   LONGWORD Temp_Long;
   
   if ( Get_EngineTurning() )
   {
      SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError ) ;
   }
   else
   {
      switch ( GetKw2000ServiceData(IdxIdentifier) )
      {
      case eioVehicleIdentificationNumber:
         if ( !GetVulnerabilityState() )
         {
            SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested ) ;
         }
         else if ( GetKeyword2000ServiceDataLength() != ( 2 + VIN_Size ) )
         {
            SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
         }
         else
         {
            /*--- Program VehicleIdentificationNumber ---*/
            for ( idx = 0 ; idx < VIN_Size ; idx++ )
            {
             //  WriteNvmEeprom( &NV_VINNumber[idx], GetKw2000ServiceData(IdxData + idx)) ;
            }
            WrtKw2000ServiceData( GetKw2000ServiceData(IdxIdentifier), IdxIdentifier);
            SendStandardPositiveAnswer( MODE_3B_RESP_LENGTH ) ;
         }
         break ;
      case eioRepairShopCodeOrTesterSerialNumber:
         if ( !GetVulnerabilityState() )
         {
            SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested ) ;
         }
         else if ( GetKeyword2000ServiceDataLength() != ( 2 + RepairShopCode_Size ) )
         {
            SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
         }
         else
         {
            /*--- Program RepairShopCode ---*/
            for ( idx = 0 ; idx < RepairShopCode_Size ; idx++ )
            {
              // WriteNvmEeprom( &NV_RepairShopCode[idx], GetKw2000ServiceData(IdxData + idx)) ;
            }
            WrtKw2000ServiceData( GetKw2000ServiceData(IdxIdentifier), IdxIdentifier);
            SendStandardPositiveAnswer( MODE_3B_RESP_LENGTH ) ;
         }
         break ;
      case eioProgrammingDate:
         if ( !GetVulnerabilityState() )
         {
            SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested ) ;
         }
         else if ( GetKeyword2000ServiceDataLength() != ( 2 + ProgrammingDate_Size ) )
         {
            SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
         }
         else
         {
            /*--- Program ProgrammingDate ---*/
            for ( idx = 0 ; idx < ProgrammingDate_Size ; idx++ )
            {
             //  WriteNvmEeprom( &NV_ProgrammingDate[idx], GetKw2000ServiceData(IdxData + idx)) ;
            }
            WrtKw2000ServiceData( GetKw2000ServiceData(IdxIdentifier), IdxIdentifier);
            SendStandardPositiveAnswer( MODE_3B_RESP_LENGTH ) ;
         }
         break ;
    
      default :
         SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
         break;
	 
      }

	//SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );	 
   }

}


/***********************************************************************
*                                                                      *
* FUNCTION:          ModifyEepromData                                  *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 3b EE data modification    *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/
#if 0
void ModifyEepromData( void )
{
uint8_t *dataprt;

    dataprt=RxServiceData+IdxData;

    switch ( GetKw2000ServiceData(IdxIdentifier) )
    {
      case ioSecretKEY:
         /*--- Program Secret Key ---*/
         EEPROMWrite(dataprt, EE_SK, SecretKEYSize);
         /* Set the active flag to False */
         WrtMultiRespInProgress( false ) ;
         if (EEPROMWriteSuccess(EE_SK, dataprt, SecretKEYSize))
         {
            	WrtKw2000ServiceData( GetKw2000ServiceData(IdxIdentifier), IdxIdentifier);
            	SendStandardPositiveAnswer( MODE_3B_RESP_LENGTH ) ;
         }
         else
         {
            	SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError ) ;
         }
         break;

      case ioSecretCode:
         /*--- Program Level 2 Key ---*/
         EEPROMWrite(dataprt, EE_Kw2000Level2KeyArray, SecretCodeSize);
         /* Set the active flag to False */
         WrtMultiRespInProgress( false ) ;
         if (EEPROMWriteSuccess(EE_Kw2000Level2KeyArray, dataprt, SecretCodeSize))
         {
            	WrtKw2000ServiceData( GetKw2000ServiceData(IdxIdentifier), IdxIdentifier);
            	SendStandardPositiveAnswer( MODE_3B_RESP_LENGTH ) ;
         }
         else
         {
            	SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError ) ;
         }
         break;

      case ioEe_immo_option:
         /*--- Program generic immo EE control flag  ---*/
         EEPROMWrite(dataprt, &EE_Immo_option, 1);
         /* Set the active flag to False */
         WrtMultiRespInProgress( false ) ;
         if (EEPROMWriteSuccess(&EE_Immo_option, dataprt, 1))
         {
            	DtrmImmoStatus(); // to update generic immobilizer enable flag
            	WrtKw2000ServiceData( GetKw2000ServiceData(IdxIdentifier), IdxIdentifier);
            	SendStandardPositiveAnswer( MODE_3B_RESP_LENGTH ) ;
         }
         else
         {
            	SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError ) ;
         }
         break;

      default :
         SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
         break;

    }
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
 * 09/06/06     Jerry.Wu    mt20u2#51
 * + Update kword spec
 *  - Change function KwJ14230WriteDataByLocalIdentifier
 *
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - Changed to support generic immo
 *
 * 12/03/07     LShoujun    mt20u2#78
 * + Integrate P2 old immo into dev10
 *   - Recovered logic of eioDeactivateImmobilizerFunction to support old immobilizer
 *
 * 12/03/07     LShoujun    mt20u2#79    
 * + new generic immo requirement change after P3 
 *   - Changed EE writing operation of mode 3B to a multi-response message.
 *
 * 22/11/07	   Yu Runwu    mt20u2#194
 * + Implement CJAE Immobilizer and Remove Old Immobilizer
 *   - Eliminate the old immobilzer logic.
\* ============================================================================ */

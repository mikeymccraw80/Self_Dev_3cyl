/* ============================================================================ *\
 * kw2srv1a.c
 * ============================================================================
 * Copyright 1999,2002 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv1a.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, June 20, 2002 1:37:09 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $1A - Read ECU identification
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "kw2dll.h"
#include "kw2app.h"
#include "kw2cfg.h"
#include "kw2srv1a.h"
#include "id.h"
#include "HLS.h"


#define MODE_1A_MSG_LENGTH                  2
#define CyId                                1


void KwJ14230ReadEcuIdentification( void )
{
   uint16_t    idx ;
   uint8_t     TrBytes;

   if ( GetKeyword2000ServiceDataLength() != MODE_1A_MSG_LENGTH )
   {
       SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
   }
   else
   {
      switch ( GetKw2000ServiceData (CyId) )
      {
      #if 0
      case ioReportECUIdentificationTable:
         TrBytes = 1 ;
         WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /* VehicleIdentificationNumber */
         for ( idx = 0 ; idx < VehicleIdentificationNumberSize ; idx++ )
         {
            WrtKw2000ServiceData( ReadNvmEeprom( &NV_VINNumber[idx] ), TrBytes++);
         }
         /* fill in VehicleManufacturerECUHardwareNumber - KCustPartNumber */
         for ( idx = 0 ; idx < sizeof( KCustPartNumber ) ; idx++ )
         {
            WrtKw2000ServiceData( KCustPartNumber[idx], TrBytes++);
         }
         /* fill in SystemSupplierECUHardwareNumber - KSystemSupplierECUHardwareNumber */
         for ( idx = 0 ; idx < sizeof( KSystemSupplierECUHardwareNumber ) ; idx++ )
         {
            WrtKw2000ServiceData( KSystemSupplierECUHardwareNumber[idx], TrBytes++);
         }
         /* fill in SystemSupplierECUSoftwareNumber - DEBroadcastCode */ 
         for ( idx = 0 ; idx < sizeof( SoftwareName ) ; idx++ )
         {
            WrtKw2000ServiceData( SoftwareName[idx], TrBytes++);
         }
         /* fill in EngineType - CustomerEngineName - only low 6 bit according to spec*/
         for ( idx = 0 ; idx < ( sizeof( CustomerEngineName ) - 4 ) ; idx++ )
         {
            WrtKw2000ServiceData( CustomerEngineName[idx], TrBytes++);
         }
         /* RepairShopCode */
         for ( idx = 0 ; idx < RepairShopCodeSize ; idx++ )
         {
            WrtKw2000ServiceData( ReadNvmEeprom( &NV_RepairShopCode[idx] ), TrBytes++);
         }

         /* fill in ProgrammingDate */
         for ( idx = 0 ; idx < ProgrammingDateSize ; idx++ )
         {
            WrtKw2000ServiceData( ReadNvmEeprom( &NV_ProgrammingDate[idx] ), TrBytes++);
         }

         /* Build answer */
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

		 #endif
      case ioReportCheryECUIdentificationSWname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_SWVERNUM_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.SwVerNum[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationHWname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_HWVERNUM_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.HwVerNum[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationSerialNumbername:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_MDLSERNUM_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.MdlSerNum[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationOrPrgname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_PRGINF_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.PrgInf_Original[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	 case ioReportCheryECUIdentificationNO1Prgname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_PRGINF_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.PrgInf_No1[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationNO2Prgname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_PRGINF_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.PrgInf_No2[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationNO3Prgname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_PRGINF_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.PrgInf_No3[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;
#if 0
	   case ioReportECUIdentificationScalingTable:
         TrBytes = 1 ;
         //WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < sizeof( ECUIdScalingTable ) ; idx++ )
         {
            WrtKw2000ServiceData( ECUIdScalingTable[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;
        
      case ioReportVIN:
         TrBytes = 1 ;
         WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /* VehicleIdentificationNumber */
         for ( idx = 0 ; idx < VehicleIdentificationNumberSize ; idx++ )
         {
            WrtKw2000ServiceData( ReadNvmEeprom( &NV_VINNumber[idx] ), TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;
      case ioSystemSupplierECUSoftwareName:
         TrBytes = 1 ;
         WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /* fill in table with SystemSupplierECUSoftwareNumber
           - DEBroadcastCode */
         /* fill in SystemSupplierECUSoftwareNumber - DEBroadcastCode */
	 for ( idx = 0 ; idx < sizeof( SoftwareName ) ; idx++ )
         {
            WrtKw2000ServiceData( SoftwareName[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;
      case ioRepairShopCodeOrTesterSerialNumber:       /* (0x98) */
         TrBytes = 1 ;
         WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );
         /* fill with shop code or tester number */
         for ( idx = 0 ; idx < RepairShopCodeSize ; idx++ )
         {
            WrtKw2000ServiceData( ReadNvmEeprom( &NV_RepairShopCode[idx] ), TrBytes++);
         }     
     	 SendStandardPositiveAnswer( TrBytes ) ;
         break ;
      case ioProgrammingDate:                          /* (0x99) */
         TrBytes = 1 ;
         WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );
         /* fill with program date */
         for ( idx = 0 ; idx < ProgrammingDateSize ; idx++ )
         {
            WrtKw2000ServiceData( ReadNvmEeprom( &NV_ProgrammingDate[idx] ), TrBytes++);
         }      
      	 SendStandardPositiveAnswer( TrBytes ) ;
         break ;
	#endif
		
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
 * 14/06/02     ndboer      28
 * + Baseline - Kokomo re-useable KW2000 module.
 *
 * 23/05/03     sgchia      118
 * + Kw2000 DE broadcast code reading.
 *
 * 09/06/06     Jerry.Wu    mt20u2#51
 * + Update kword spec
 *   - Change table ECUIdScalingTable and function KwJ14230ReadEcuIdentification
 *
\* ============================================================================ */

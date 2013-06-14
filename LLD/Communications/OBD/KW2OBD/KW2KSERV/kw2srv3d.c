/* ============================================================================ *\
 * kw2srv3d.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv3d.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 5:22:55 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $3D - Write memory by address
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
#include "kw2srv3d.h"
// #include "dd_port.h"
// #include "instmem.h"

#define SyTesterPresentDataLength           1
#define SyTesterPresentDataLengthWithResp   2

#define CyAddrBank                          1
#define CyAddrMSB                           2
#define CyAddrLSB                           3
#define CyLength                            4
#define CyData                              5

#define RespondYes                          0x01
#define RespondNo                           0x02



void KwJ14230WriteMemoryByAddress( void )
{
#if 0
   uint8_t     *pucMemStart ;
   uint8_t*    pucServiceData ;
   uint8_t     ucLength ;
   dyn_addrType dyn_addr;
   uint8_t     count;
   uint8_t     page;
   uint8_t        gpage_buffer;
   ucLength = GetKw2000ServiceData (CyLength) ;
   page = GetKw2000ServiceData (CyAddrBank);
   /* check message length */
   if (   (GetKeyword2000ServiceDataLength() != ( ucLength + 5 ) )
       || ( !IsDevelopment() ) )
   {
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
   }
  // else if ( !Memory_Page_Is_Valid(GetKw2000ServiceData (CyAddrBank))) 
   	         
   //{
   //   SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
   //}
   else
   {
      pucMemStart = (uint8_t*) ( ((GetKw2000ServiceData (CyAddrMSB)*256) | GetKw2000ServiceData (CyAddrLSB)) & 0x00ffff  );
	
      pucServiceData = (uint8_t*) &(GetKw2000ServiceData (CyData)) ;

      if ( ( GetKw2000ServiceData (CyAddrBank) == RAM_MemoryPage)
	    && ( pucMemStart >=  RAM_START_ADDRESS )
           && ( (pucMemStart + ucLength - 1) <=  RAM_STOP_ADDRESS ) ) 
       {
	   dyn_addr.g_l.globle_page = GetKw2000ServiceData (CyAddrBank);
	   dyn_addr.g_l.local_addr =(uint16_t)( pucMemStart);
	   Disable_Interrupts() ;		 
          /* backup the current value of gpage */
          gpage_buffer = (uint8_t)_GPAGE.Byte; 
	      for ( count = 0; ucLength > count; count++ )
          {
             *dyn_addr.g_pointer = *pucServiceData;  /* write data to address */
             dyn_addr.g_pointer++; /* increment target address */
             pucServiceData++; /* increment source address */
          }
	  /* restore the value of gpage */
        _GPAGE.Byte = gpage_buffer;
        Enable_Interrupts();	  
        SendStandardPositiveAnswer( 1 ) ;
       }
      else if( LCIInstrumented() ||
	  	( ( (PARTID&0xFFC0)!=0xC080)&&
	      Is_Within_CAL_Range(pucMemStart,ucLength,GetKw2000ServiceData (CyAddrBank))  ))
      {
         if( ( (PARTID&0xFFC0)!=0xC080)&&
	       Is_Within_CAL_Range(pucMemStart,ucLength,GetKw2000ServiceData (CyAddrBank))  )
         {
            dyn_addr.g_l.globle_page = 0x0F;             
         }
         else
         {
            dyn_addr.g_l.globle_page = GetKw2000ServiceData (CyAddrBank);
         }
          //dyn_addr.g_l.globle_page = GetKw2000ServiceData (CyAddrBank);
	   dyn_addr.g_l.local_addr =(uint16_t)( pucMemStart);
	   Disable_Interrupts() ;		 
          /* backup the current value of gpage */
          gpage_buffer = (uint8_t)_GPAGE.Byte; 
          for ( count = 0; ucLength > count; count++ )
          {
             *dyn_addr.g_pointer = *pucServiceData;  /* write data to address */
             dyn_addr.g_pointer++; /* increment target address */
             pucServiceData++; /* increment source address */
          }
		  /* restore the value of gpage */
         _GPAGE.Byte = gpage_buffer;
	  Enable_Interrupts();	 	  
          SendStandardPositiveAnswer( 1 ) ;
      }
#if 0
	 else if (GetKw2000ServiceData (CyAddrBank) == EEPROM_MemeoyPage &&
	 	   (  pucMemStart >= EEPROM_START
               && ( pucMemStart + ucLength - 1) <= EEPROM_END  ) )	 	
      {	 	
          pucMemStart =(uint8_t*)( ((GetKw2000ServiceData (CyAddrMSB)*256) | GetKw2000ServiceData (CyAddrLSB)) & 0x000fff );
          /* write to EEPROM area */
	  // dyn_addr.g_l.globle_page = GetKw2000ServiceData (CyAddrBank);
	  // dyn_addr.g_l.local_addr =(uint16_t)( pucMemStart);
        if ( EEWriteBackground( pucServiceData, pucMemStart, ucLength) == EEPrgStart )
         {
           SendStandardPositiveAnswer( 1 ) ;
         }
        else
        {
           SendStandardNegativeAnswer( nrcBusy_RepeatRequest );
        }
      }
#endif
     else
     {
         SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
      }
   }
#endif
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
 * May/10/06    Jerry.Wu    mt20u2#51
 * + Update kwJ14230writebyadress logic
 *  - Change function KwJ14230WriteMemoryByAddress
 *
 * 18/01/08     Petra        ---
 * + Change local address to global for new LCI.
\* ============================================================================ */

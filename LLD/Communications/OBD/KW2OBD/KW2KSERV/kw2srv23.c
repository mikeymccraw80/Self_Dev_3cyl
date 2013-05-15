/* ============================================================================ *\
 * kw2srv23.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv23.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 5:22:25 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $23 - Read memory by address
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
#include "kw2srv23.h"
#include "instmem.h"


#define SyTesterPresentDataLength           1
#define SyTesterPresentDataLengthWithResp   2

#define MODE_23_MSG_LENGTH                  5
#define CyAddrBank                          1
#define CyAddrMSB                           2
#define CyAddrLSB                           3
#define CyLength                            4


void KwJ14230ReadDataByAddress( void )
{
   uint8_t     *pucMemStart ;
   uint8_t     ucLength ;
   uint8_t     idx, TrBytes ;
   dyn_addrType dyn_addr;
   uint8_t        gpage_buffer;

   if (   (GetKeyword2000ServiceDataLength() != MODE_23_MSG_LENGTH )
       || ( !IsDevelopment() ) )
   {
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
   }
   else if ( !Memory_Page_Is_Valid(GetKw2000ServiceData (CyAddrBank))) 
   {
      SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
   }
   else
   { 

      //dyn_addr.g_l.globle_page = GetKw2000ServiceData (CyAddrBank);
      ucLength = GetKw2000ServiceData (CyLength) ;
      pucMemStart = (uint8_t*) ( (GetKw2000ServiceData (CyAddrMSB)*256) | GetKw2000ServiceData (CyAddrLSB) );
       if( ( (PARTID&0xFFC0)!=0xC080)&&
	       Is_Within_CAL_Range(pucMemStart,ucLength,GetKw2000ServiceData (CyAddrBank))  )
         {
            dyn_addr.g_l.globle_page = 0x0F;             
         }
         else
         {
            dyn_addr.g_l.globle_page = GetKw2000ServiceData (CyAddrBank);
         }
      dyn_addr.g_l.local_addr = (uint16_t)pucMemStart;
      TrBytes = 1;
      Disable_Interrupts() ;		 
      /* backup the current value of gpage */
      gpage_buffer = (uint8_t)_GPAGE.Byte;  
      /* read memory data to KW2000 service data buffer */
      for ( idx = 0 ; idx < ucLength ; idx++ )
      {
       
         WrtKw2000ServiceData( ((uint8_t) *dyn_addr.g_pointer++), TrBytes++);
      }
      /* restore the value of gpage */
      _GPAGE.Byte = gpage_buffer;
      Enable_Interrupts();	  
      SendStandardPositiveAnswer( TrBytes ) ;
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
 * 18/01/08     Petra        ---
 * + Change local address to global for new LCI.
\* ============================================================================ */
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
#include "kw2type.h"
#include "kw2dll.h"
#include "kw2app.h"
#include "kw2api.h"
#include "kw2srv23.h"


/* Define the number of data bytes in the service 23 message */

#define Sy14230_MODE_23_MSG_LENGTH  5

/***********************************************************************
* FUNCTION:     Expand_Keyword_Memory_Address                          *
*                                                                      *
* TYPE:         Global                                                 *
*                                                                      *
* DESCRIPTION:  Get 24-bit address from KW message and translate to    *
*               32 bits.  High-order nibble of KW byte 2 is expanded   *
*               to 32-bit address bits 31-24; low-order nibble of KW   *
*               byte 2 becomes bits 17-23.  Thus A2 01 56 becomes      *
*               A0020156.                                              *
*                                                                      *
***********************************************************************/
uint32_t Expand_Keyword_Memory_Address(uint16_t Start_Index)
{
    FOUR_BYTE_DATA_TYPE LgTempDataPtr;
    uint8_t             Switch_Index;

    Switch_Index = GetKw2000ServiceData(Start_Index) & 0xf0;

/* for freescale PPC 32 bit MCU */
    if ((Switch_Index & 0xe0) == 0x00)
    {
        /* Start of FLASH  */
        LgTempDataPtr.Byte_Access.Byte_Four = 0x00;
        LgTempDataPtr.Byte_Access.Byte_Three = GetKw2000ServiceData(Start_Index);
    }
    else if ((Switch_Index == 0x40) || (Switch_Index == 0x41))
    {
        /* Start of RAM  */
        LgTempDataPtr.Byte_Access.Byte_Four = 0x40;
        LgTempDataPtr.Byte_Access.Byte_Three = (GetKw2000ServiceData(Start_Index) & 0x01);
    }
    else
    {
        /* Invalid Value */
        LgTempDataPtr.Byte_Access.Byte_Four = 0x00;
        LgTempDataPtr.Byte_Access.Byte_Three = GetKw2000ServiceData(Start_Index);
    }
    LgTempDataPtr.Byte_Access.Byte_Two = GetKw2000ServiceData( Start_Index + 1 ); 
    LgTempDataPtr.Byte_Access.Byte_One = GetKw2000ServiceData( Start_Index + 2 );

	return LgTempDataPtr.DWord_Access;
}

/***********************************************************************
* FUNCTION:     KwJ14230ReadMemoryByAddress    (SERVICE 23)            *
*                                                                      *
* TYPE:         Global                                                 *
*                                                                      *
* DESCRIPTION:  Same as the above file description.                    *
*                                                                      *
************************************************************************
* Last modified on: 01/08/99              by: John Zha                 *
***********************************************************************/

void KwJ14230ReadDataByAddress( void )
{

  /* Define the local variables to store the memory size,
   * Index and to be the pointer.
   */
   uint32_t  Physical_Address;

   BYTE                  *LgDataPtr ;
   BYTE                  LyIdx ;
   BYTE                  MemSize ;

   /* Check the message data length if it is 5 */
   if ( Sy14230_MODE_23_MSG_LENGTH ==
        GetKeyword2000ServiceDataLength() )
   {
	Physical_Address = Expand_Keyword_Memory_Address(CyMemAddrHighByte);

    /* Get the memory size from the message. */
    MemSize = GetKw2000ServiceData( CyMemSize ); 
 
    /* verify addess plus memory size fit in the user defined
     * memory block range. 
     */
    if(( Srv23Address_Is_Validkw ( Physical_Address , MemSize )) &&
        (MemSize <= CyMaxMemSize))
    {
      /*The address pointer LgdataPtr pointer to the start address */
      LgDataPtr = (BYTE *)Physical_Address;

     /*Initialize the index to be 1, because the index 0 of the
       * answer message data should be the service number 23 in 
       * the answer message.
       */
      LyIdx = 1 ;
 
      /* Load to the Transmit buffer with the memory data */     
      while( LyIdx <= (MemSize) )
      {  
       WrtKw2000ServiceData(( *(LgDataPtr++) ), LyIdx++ ) ;
      }

      /*Send out the data by the SCI transmitter*/
      SendStandardPositiveAnswer (LyIdx);
    }
    else
    {
      /* Invalid message length */
      SendStandardNegativeAnswer( nrcRequestOutOfRange );
    }
   }
   else
   {
     /* Invalid Message format */
     SendStandardNegativeAnswer( 
     nrcSubFunctionNotSupported_InvalidFormat  ) ;
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
 * 18/01/08     Petra        ---
 * + Change local address to global for new LCI.
\* ============================================================================ */
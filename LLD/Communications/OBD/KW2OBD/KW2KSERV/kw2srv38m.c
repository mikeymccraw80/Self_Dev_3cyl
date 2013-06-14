/* ============================================================================ *\
 * kw2srv38m.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv38m.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, March 20, 2003 11:24:55 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $38 - Start routine by address (Minimized)
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
#include "kw2srv38m.h"
#include "kw2srv10m.h"
#include "kw2srv36.h"


#define Cy14230_SERVICE_38_MSG_LENGTH        (4)


typedef enum
{
    ReqServiceId,
    ReqMemAddHighByte,
    ReqMemAddMiddleByte,
    ReqMemAddLowByte
} RequestMessage;

static bool DecryptRoutineDataAndVerifyChecksum(void)
{
   uint8_t                 *routine_data_pointer;
   uint8_t                 encrypted_data;
   uint16_t                i;
   uint16_t                routine_data_size;
   uint16_t                routine_data_checksum,calculated_checksum;
   
   routine_data_pointer = GetTransferAddressTypePtr();
   routine_data_size = GetTransferDataSize();
   routine_data_pointer = routine_data_pointer - routine_data_size;
   calculated_checksum = 0;
   routine_data_checksum = 0;
   
   for( i = 0; i < routine_data_size; i++ )
   {
      encrypted_data = *(routine_data_pointer + i);
      encrypted_data = ((((encrypted_data&0xF0)>>1)|((encrypted_data&0x10)<<3))&0xf0)|((((encrypted_data&0x0F)<<1)|((encrypted_data&0x08)>>3))&0x0f);
      *(routine_data_pointer + i) = ~encrypted_data;
      if( i < routine_data_size - 2 )
      {
         calculated_checksum = calculated_checksum + (*(routine_data_pointer + i));	
      }
      else
      {
         routine_data_checksum = (routine_data_checksum<<8) + (*(routine_data_pointer + i));
      }
   	
   }
   if( (calculated_checksum == routine_data_checksum) && (routine_data_size > 2) )
      return true;
   else
      return false;	
}
/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230StartRoutineByAddress                     *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 38 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/
void ExecuteStartRoutineByAddressFunction( void )
{
    union UnionType
    {
        struct Type
        {
            uint8_t byte1;
            uint8_t byte2;
            uint8_t byte3;
        } BytesVar;
        struct
        {
            uint8_t     bank;
            uint16_t    address;
        } PhysicalAddress;
    } UnionVar38;

  void (*Function_Address) (void);

  /* Get routine address. */
  UnionVar38.BytesVar.byte1 =
  GetKw2000ServiceData (ReqMemAddHighByte);

  UnionVar38.BytesVar.byte2 =
  GetKw2000ServiceData(ReqMemAddMiddleByte);

  UnionVar38.BytesVar.byte3 =
  GetKw2000ServiceData(ReqMemAddLowByte);

  Function_Address = (void *) UnionVar38.PhysicalAddress.address;

  /* Set the active flag to False */
  WrtMultiRespInProgress( false ) ;

  /* Call routine. */
  Function_Address ();

  /* Send positive response. */
  WrtKw2000ServiceData ( GetKw2000ServiceData ( ReqMemAddHighByte ),
                                                ReqMemAddHighByte );

  WrtKw2000ServiceData ( GetKw2000ServiceData ( ReqMemAddMiddleByte),
                                                ReqMemAddMiddleByte);


  WrtKw2000ServiceData ( GetKw2000ServiceData ( ReqMemAddLowByte),
                                                ReqMemAddLowByte);


  SendStandardPositiveAnswer( Cy14230_SERVICE_38_MSG_LENGTH );

} /* ExecuteStartRoutineByAddressFunction  */


/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230MiniStartRoutineByAddr                    *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 38 functionality.          *
*                    No engine condition check.                        *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/
void KwJ14230MiniStartRoutineByAddr( void )
{
    uint8_t errorno;

    errorno = 0;

    if (GetKeyword2000ServiceDataLength() != Cy14230_SERVICE_38_MSG_LENGTH)
    {
        errorno = nrcSubFunctionNotSupported_InvalidFormat ;
    }
    else if ( CheckProgrammingState ())
    {
        /* In the progrmming mode, if data transfer is in progress 
         * send negative message.
         */
        if ( CheckIfDownLoadInProgress() )
        {
            errorno = nrcConditionsNotCorrect_RequestSequenceError ;
        }
        else if (GetKw2000ServiceData (ReqMemAddHighByte) != 0)
        {
            /*  not a common bank address */
            errorno = nrcRequestOutOfRange ;
        }
        else if(DecryptRoutineDataAndVerifyChecksum() == false)
        {
          errorno = nrcBlockTransferDataChecksumError;
        }
    }
    else
    {
        errorno = nrcServiceNotSupportedInActiveDiagnosticMode ;
    }

    if ( errorno != 0 )
    {
        SendStandardNegativeAnswer( errorno );
        if(errorno == nrcBlockTransferDataChecksumError)
        {
            SetECUResetPending( true ) ;
        }    
    }
    else
    {
        /* Set the active flag to TRUE */
        WrtMultiRespInProgress( true ) ;

        /* Send back a negative response indicating
           that the function is not complete. */
        SendStandardNegativeAnswer(nrcRequestCorrectlyReceived_ResponsePending);
    }
} /*** End of KwJ14230MiniStartRoutineByAddr ***/




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
 *   - Added minimized KWP2000 Start routine by address (0x38) service. With no
 *     engine condition checks.
 *
 * 03/09/07    Longway.Huang  mt20u2#166
 * + Flash protection Strategy
 *   - Add the protection strategy for re-flash.
 * 
 * 15/11/07     Zhou Shenghui  mt20u2#198
 * + Checksum encrypt condition strategy update
 *   - Modify function DecryptRoutineDataAndVerifyChecksum(), add condition routine_data_size > 2.
 *
 * 08/05/08     Zhou Shenghui  mt20u2#238
 * + Add flash security strategy for protecting software
\* ============================================================================ */

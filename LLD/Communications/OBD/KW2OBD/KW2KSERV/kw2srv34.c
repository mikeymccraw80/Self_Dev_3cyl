/* ============================================================================ *\
 * kw2srv34.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv34.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 9:56:08 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $34 - Request download
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
#include "kw2srv10m.h"
#include "kw2srv34.h"
#include "kw2srv36.h"
// #include "hal_can.h"
// #include "dd_can.h"

#define      Cy14230_SERVICE_34_MSG_LENGTH        (8)
#define      CyTRANSMIT_MSG_BUFF_OFFSET_BYTE1     (1)
#define      CyTRANSMIT_DATA_SIZE                 (2)
#define      CyFormatIdent                        (4)
#define      CyUnCompressed                       (0)


typedef enum
{
  ReqServiceId,
  ReqMemAddHighByte,
  ReqMemAddMiddleByte,
  ReqMemAddLowByte,
  ReqDataFormatId,
  ReqUnused,
  ReqUnCompMemSizeHighByte,
  ReqUnCompMemSizeLowByte
} RequestMessage;


/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230RequestDownload                           *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 34 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/

void KwJ14230RequestDownload( void )
{
    union UnionTypeAddress
    {
        struct TypeAddress
        {
            uint8_t byte1;
            uint8_t byte2;
            uint8_t byte3;
        } BytesVar;
        struct
        {
            uint8_t    bank;
            uint16_t    address;
        } PhysicalAddress;
    } UnionVar34;

    union UnionTypeSize
    {
        struct TypeSize
        {
            uint8_t byte1;
            uint8_t byte2;
        } BytesVar;
        uint16_t    size;
    } UnionVar34a;

    uint8_t transfer_error_code;

    if ((GetKeyword2000ServiceDataLength() !=  Cy14230_SERVICE_34_MSG_LENGTH) ||
        (GetKw2000ServiceData (CyFormatIdent) != CyUnCompressed ))
    {
        transfer_error_code = nrcSubFunctionNotSupported_InvalidFormat;
    }
    else if (!CheckIfDataTransferNotInProgress ())
    {
        /*  Can't request if a transfer is in progress  */
        transfer_error_code = nrcConditionsNotCorrect_RequestSequenceError;
    }
    else if (!CheckProgrammingState ())
    {
        /*  Must be in ECU Programming Mode  */
        transfer_error_code = nrcServiceNotSupportedInActiveDiagnosticMode;
    }
    else
    {
        /* Get the download address */

        UnionVar34.BytesVar.byte1 = GetKw2000ServiceData (ReqMemAddHighByte);
        UnionVar34.BytesVar.byte2 = GetKw2000ServiceData (ReqMemAddMiddleByte);
        UnionVar34.BytesVar.byte3 = GetKw2000ServiceData (ReqMemAddLowByte);

        /* Set the download address, for service 36 to use */
        SetTransferAddressTypePtr (UnionVar34.PhysicalAddress.address);

        /* get the data size */
        UnionVar34a.BytesVar.byte1 = GetKw2000ServiceData (ReqUnCompMemSizeHighByte);
        UnionVar34a.BytesVar.byte2 = GetKw2000ServiceData (ReqUnCompMemSizeLowByte  );

        /* Set the data size, for service 36 to use */
        SetTransferDataSize (UnionVar34a.size);

        /*  Check that the download address is withing the limits of RAM  */
        if ((GetTransferAddressTypePtr () < GetRAMStartAddrForUpDownload ()) ||
            (GetTransferAddressTypePtr () > GetRAMEndAddrForUpDownload () ) ||
            (UnionVar34.PhysicalAddress.bank != 0) )
        {
            transfer_error_code = nrcCanNotDownloadToSpecifiedAddress;
        }
        else if ((uint16_t) (GetTransferAddressTypePtr() + GetTransferDataSize ()) >
                    ((uint16_t) GetRAMEndAddrForUpDownload () + 1) )
        {
            transfer_error_code = nrcCanNotDownloadNumberOfBytesRequested;
        }
        else
        {
            transfer_error_code = nrcNone;
        }
    }

    if(transfer_error_code == nrcNone)
    {
        /* Disable the Chery EMS Can data transmit */
        // VsCAN_CHERY_EMS_ID_Disable = true;
	/*disable all can 0 interrupt when refalsh*/
       // Hw_Turn_Off_CAN0_All_Interrupt();	
        /*  We have now passed all the tests  */
        SetTransferStateToDownLoad ();
        Settransfer_bytes_recdSend_so_far ( 0L);
        WrtKw2000ServiceData( CyMAX_TRANSFER_SIZE, CyTRANSMIT_MSG_BUFF_OFFSET_BYTE1 );
        SendStandardPositiveAnswer( CyTRANSMIT_DATA_SIZE );
    }
    else
    {
        SendStandardNegativeAnswer(transfer_error_code);
    }
} /*** End of RequestDownload ***/




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
 *   - added header kw2srv10m.h.
 *
\* ============================================================================ */

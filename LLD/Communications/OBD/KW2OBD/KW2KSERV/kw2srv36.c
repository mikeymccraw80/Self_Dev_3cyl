/* ============================================================================ *\
 * kw2srv36.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv36.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 9:56:28 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $36 - Transfer data
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */



#include  "kw2dll.h"
#include  "kw2api.h"
#include  "kw2srv10m.h"
#include  "kw2srv36.h"

#define   CyTRANSMIT_DATA_SIZE       (2)
#define   CyREQUEST_ID_OFFSET        (4)
#define   CyPositiveAnswerLength     (1)

/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */

uint8_t                 *transfer_address_as_pointer;
uint16_t                transfer_requested_data_size;
uint16_t                transfer_bytes_recdSend_so_far;
transfer_state_type transfer_state;



/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230TransferData                              *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 36 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/
void KwJ14230TransferData( void )
{
  uint8_t           transfer_error_code;
  uint16_t          bytes_index;
  uint8_t           bytes_trans_Count ;
  uint16_t          number_of_data_bytes;
  uint16_t          index;

  transfer_error_code = nrcNone ;
  bytes_trans_Count   = 0 ;

  /*  Must be in ECU Programming Mode  */

  if (! CheckProgrammingState ())
  {
    transfer_error_code = nrcServiceNotSupportedInActiveDiagnosticMode ;
  }
  /*  Don't allow a transfer without a request  */
  else   if ( !CheckIfDownLoadInProgress () &&
              !CheckIfUpLoadInProgress ())
  {
     transfer_error_code = nrcConditionsNotCorrect_RequestSequenceError ;
  }
  else
  {
     switch ( transfer_state )
     {
        case trstDownloadInProgress:
          /* download the data */

           number_of_data_bytes = GetKeyword2000ServiceDataLength() - CyREQUEST_ID_OFFSET;

           if ( number_of_data_bytes > CyMAX_TRANSFER_SIZE )
           {
              transfer_error_code = nrcIncorrectByteCountDuringBlockTransfer;
           }
           transfer_bytes_recdSend_so_far += number_of_data_bytes;

           /* Check if the size of data being transfered is greater
              than the size indicated in the earlier service 34 or
              35. */

           if ( Gettransfer_bytes_recdSend_so_far() > GetTransferDataSize() )
           {
              transfer_error_code = nrcIllegalByteCountInBlockTransfer;
              transfer_bytes_recdSend_so_far -= number_of_data_bytes;
           }
           else if ( Gettransfer_bytes_recdSend_so_far() == GetTransferDataSize() )
           {
                 SetTransferStateToCompltd ();
           }

           /*  If all is well. do the transfer  */
           if( transfer_error_code == nrcNone )
           {
              for(index = 0; index < number_of_data_bytes; ++index)
              {
                *transfer_address_as_pointer++ =
                GetKw2000ServiceData (index + CyRESPONSE_ID_OFFSET);
              }
           }
           WrtKw2000ServiceData (number_of_data_bytes, 1);
           bytes_trans_Count = CyTRANSMIT_DATA_SIZE;

           break;

        case trstUploadInProgress:
           /* Upload the data */

           /* The bytes_count is set to number of bytes transferred
                 till now
               */
           bytes_index = Gettransfer_bytes_recdSend_so_far();
           /* Set the number of bytes transferred in this message is
                 zero
               */
           bytes_trans_Count = 0;

           for ( index = bytes_index; index < GetTransferDataSize() ; ++index )
           {
              transfer_bytes_recdSend_so_far++;
              bytes_trans_Count++;
              WrtKw2000ServiceData (*transfer_address_as_pointer++, bytes_trans_Count);

              if ( bytes_trans_Count == CyMAX_TRANSFER_SIZE )
                 break;
           }
           /* Add 1 to bytes_trans_Count, this is to consider the
                 response code header uint8_t */
           bytes_trans_Count++;

           if ( Gettransfer_bytes_recdSend_so_far() == GetTransferDataSize() )
                SetTransferStateToCompltd ();

           break;

        case trstNotTransferring:                          /* fall through to default */
        case trstTransferCompleted:                        /* fall through to default */
        default:
           break;
          /* do nothing */
     }
  }
  if(transfer_error_code == nrcNone)
  {
     SendStandardPositiveAnswer( bytes_trans_Count );
  }
  else
  {
     SendStandardNegativeAnswer( transfer_error_code );
  }

} /*** End of KwJ14230TransferData ***/


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
 * 16/05/07     LShoujun    mt20u2#734(task)
 * + replace MCU of KG256 with xep100 - Step I
 *  - Changed compiler to Cosmic s12x
 *
\* ============================================================================ */

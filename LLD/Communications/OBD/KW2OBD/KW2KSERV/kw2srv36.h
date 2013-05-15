#ifndef KW2SRV36_H
#define KW2SRV36_H
/* ============================================================================ *\
 * kw2srv36.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv36.h-2:incl:mt20a#1
 * Revision:        2
 * Creation date:   Thursday, June 20, 2002 1:36:43 PM
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

#include "kw2type.h"

#define      CyRESPONSE_ID_OFFSET       (4)
/* The first uint8_t of transmit buffer is the Response Id */
#define      CyMAX_TRANSFER_SIZE        (MaxiServiceDataSize - CyRESPONSE_ID_OFFSET)


extern  void  KwJ14230TransferData ( void );

extern uint8_t  *transfer_address_as_pointer;
extern uint16_t  transfer_requested_data_size;
extern uint16_t  transfer_bytes_recdSend_so_far;

typedef enum
{
  trstNotTransferring,
  trstDownloadInProgress,
  trstUploadInProgress,
  trstTransferCompleted
}transfer_state_type ;

extern transfer_state_type transfer_state;

/***********************************************************************
* Set  the transfer_state to trstNotTransferring.                      *
***********************************************************************/
#define SetTransferStateToNotTransfering()                ( transfer_state = trstNotTransferring )

/***********************************************************************
* Set  the transfer_state to trstDownloadInProgress.                   *
***********************************************************************/
#define SetTransferStateToDownLoad()                       ( transfer_state = trstDownloadInProgress )

/***********************************************************************
* Set the transfer_state to trstUploadInProgress.                      *
***********************************************************************/
#define SetTransferStateToUpLoad()                         ( transfer_state = trstUploadInProgress )

/***********************************************************************
* Set the transfer_state to trstTransferCompleted.                     *
***********************************************************************/
#define SetTransferStateToCompltd()                        ( transfer_state = trstTransferCompleted )

/***********************************************************************
* Check if the transfer_state is set to trstNotTransferring.           *
***********************************************************************/
#define CheckIfDataTransferNotInProgress()                 ( transfer_state == trstNotTransferring )

/***********************************************************************
* Check if the transfer_state is set to trstDownloadInProgress.        *
***********************************************************************/
#define CheckIfDownLoadInProgress()                        ( transfer_state == trstDownloadInProgress )

/***********************************************************************
* Check if the transfer_state is set to trstUploadInProgress.          *
***********************************************************************/
#define CheckIfUpLoadInProgress()                          ( transfer_state == trstUploadInProgress )

/***********************************************************************
* Set the value of transfer_address_as_pointer variable.               *
***********************************************************************/
#define SetTransferAddressTypePtr(Address)                 ( transfer_address_as_pointer = ( uint8_t *)Address )

/***********************************************************************
* Get the value of transfer_address_as_pointer variable.               *
***********************************************************************/
#define GetTransferAddressTypePtr()                        ( (uint8_t *) transfer_address_as_pointer)

/***********************************************************************
* Set the value of transfer_requested_data_size variable.              *
***********************************************************************/
#define SetTransferDataSize(TransferBytes)                 ( transfer_requested_data_size = TransferBytes )

/***********************************************************************
* Get the value of transfer_requested_data_size variable.              *
***********************************************************************/
#define GetTransferDataSize()                              ( (uint16_t) transfer_requested_data_size )

/***********************************************************************
* Set the value of  transfer_bytes_recdSend_so_far variable.           *
***********************************************************************/
#define Settransfer_bytes_recdSend_so_far(NumberOfBytes)   ( transfer_bytes_recdSend_so_far = NumberOfBytes )

/***********************************************************************
* Get the value of  transfer_bytes_recdSend_so_far variable.           *
***********************************************************************/
#define Gettransfer_bytes_recdSend_so_far()                ( (uint16_t) transfer_bytes_recdSend_so_far)



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
#endif

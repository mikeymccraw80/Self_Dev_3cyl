/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_55808.h
*  Creation date :
*  Description   :Vehicle Electrical Power 1 Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

/*-------------------------------------------------------------------
* to avoid multiple definition if the file is included several times
*-------------------------------------------------------------------*/
#ifndef J1939_PGN_55808_DEF
#define J1939_PGN_55808_DEF

#include "j1939_pgn_config.h"
#include "j1939_bit_fields.h"

#define SidInitiateDiagnostic_length             (2)
#define SidSecurityAccess_length                 (2)
#define SidRoutineControl_length                 (4)
#define SidInitiateDiagnosticOperation           (0x10)   /*--- YES ---*/
#define SidEcuReset                                         (0x11)   /*--- YES ---*/
#define SidReadFailureRecordData                 (0x12)   /*--- NO ---*/
#define SidClearDiagInformation                  (0x14)   /*--- YES ---*/
#define SidReadDataByIdentifier                  (0x1A)   /*--- NO ---*/
#define SidReturnToNormalMode                    (0x20)   /*--- NO ---*/
#define SidReadDataByCommonIdentifier            (0x22)   /*--- YES ---*/
#define SidReadMemoryByAddress                   (0x23)   /*--- YES ---*/
#define SidSecurityAccess                        (0x27)   /*--- YES ---*/
#define SidDisableNormalCommunication            (0x28)   /*--- YES ---*/
#define SidDynamicallyDefineMessage              (0x2C)   /*---NO ---*/
#define SidRoutineControl                        (0x31)   /*--- YES ---*/
#define SidRequestDownload                       (0x34)   /*--- NO ---*/
#define SidTransferData                          (0x36)   /*--- NO ---*/
#define SidWriteDataByIdentifier                 (0x2E)   /*--- YES ---*/
#define SidWriteMemoryByAddress                  (0x3D)   /*--- NO ---*/
#define SidTesterPresent                         (0x3E)   /*--- YES ---*/
#define SidReportProgrammedState                 (0xA2)   /*--- YES ---*/
#define SidProgrammingMode                       (0xA5)   /*--- NO ---*/
#define SidReadDiagnosticInformation             (0x19)   /*--- YES ---*/
#define SidReadDataByPacketIdentifier            (0x2A)   /*--- YES ---*/
#define SidInputOutputControlByIdentifier        (0x2F)   /*--- YES ---*/

#define NegativeResponseServiceIdentifier           (0x7F)
#define ServiceIdNotSupported                       (0x11)
#define SubFunctionNotSupported_InvalidFormat       (0x12)
#define IncorrectMessageLength                      (0x13)
#define ConditionsNotCorrectOrRequestSequenceError  (0x22)


extern TbBOOLEAN  VbCopyAndExecuteKernelPending;

extern void J1939_RxInit_PGN_55808(J1939_Receive_Message_Control_T * rx_msg_ctrl_ptr);
extern void J1939_TxInit_PGN_55808(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

#endif

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/


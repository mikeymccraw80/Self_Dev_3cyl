#ifndef MG_MAILBOX_H
#define MG_MAILBOX_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_mailbox.h %
//
// created_by:       lz37cb %
//
// date_created:     Wed Jun 11 09:54:59 2008 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:          %
//
// %version:         3 %
//
//=============================================================================



#define SIZE_OF_INBOX      (0x20)
#define SIZE_OF_OUTBOX     (0xFF)
#define INBOX_ST           (0x40017400)                          /* Start of INBOX */
#define OUTBOX_ST          (INBOX_ST + SIZE_OF_INBOX)          /* Start of OUTBOX */
#define END_OF_MAILBOX     (OUTBOX_ST + SIZE_OF_OUTBOX)

#define INBOX_PTR          ((void *)(INBOX_ST))
#define OUTBOX_PTR         ((void *)(OUTBOX_ST))


typedef struct MG_INBOX_Tag
{
   uint8_t  testid;
   uint8_t  parameter[31];    
} MG_INBOX_T;

typedef struct MG_OUTBOX_Tag {
   uint8_t  parameter[32];
} MG_OUTBOX_T;


#define MG_MAILBOX_IN(member)           (((MG_INBOX_T *)INBOX_ST)->member)
#define MG_MAILBOX_OUT(member)          (((MG_OUTBOX_T *)OUTBOX_ST)->member)

#endif

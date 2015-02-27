#ifndef MG_MAIN_H
#define MG_MAIN_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_main.h %
//
// created_by:       lz37cb %
//
// date_created:     Wed Jun 11 09:54:59 2008 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:           %
//
// %version:         4 %
//
//=============================================================================

typedef enum
{
   MG_FUNCTION_TEST,
   MG_OUTPUT_CYCLING_EMC,
   MG_OUTPUT_CYCLING_VALIDATION,
   UNDEFINED_MODE,
   MODE_MAX
} MG_MODE_T;

void mg_main(void);

#endif


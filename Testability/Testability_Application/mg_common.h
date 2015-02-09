#ifndef MG_COMMON_H
#define MG_COMMON_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_common.h %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      zzrfyj %
//
// %date_modified:       %
//
// %version:         1 %
//
//=============================================================================

#include "reuse.h"


#define MG_BITMAP_SIZE   4
#define MG_BITMAP_SHIFT  3  
#define MG_BITMAP_MASK   0x07  

extern uint8_t mg_bitmap[MG_BITMAP_SIZE];





void MG_Bitmap_Init(uint8_t *ptr);
void MG_Bitmap_Set(uint8_t value);
void MG_Bitmap_Clr(uint8_t value);
bool MG_Bitmap_Test_Value_In_Map(uint8_t value);

#endif /* end of include guard: MG_COMMON_H */

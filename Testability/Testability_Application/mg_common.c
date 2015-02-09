//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_common.c %
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

#include "mg_common.h"


uint8_t mg_bitmap[MG_BITMAP_SIZE];


void MG_Bitmap_Init(uint8_t *ptr)
{
    uint8_t i;

    for (i = 0; i < MG_BITMAP_SIZE; i++) 
    {
        mg_bitmap[i] = 0;
    }

    if (ptr!=(void*)0) 
    {
        for (i = 0; i < MG_BITMAP_SIZE; i++) 
        {
            mg_bitmap[i] = *ptr;
            ptr++;
        }
    }
}

void MG_Bitmap_Set(uint8_t value)
{
    if (value>>MG_BITMAP_SHIFT < MG_BITMAP_SIZE) 
    {
        mg_bitmap[value>>MG_BITMAP_SHIFT] |= (1<<(value & MG_BITMAP_MASK));
    }
}

void MG_Bitmap_Clr(uint8_t value)
{
    if (value>>MG_BITMAP_SHIFT < MG_BITMAP_SIZE) 
    {
        mg_bitmap[value>>MG_BITMAP_SHIFT] &= ~(1<<(value & MG_BITMAP_MASK));
    }
}

bool MG_Bitmap_Test_Value_In_Map(uint8_t value)
{
    bool return_code = false;
    if ((value>>MG_BITMAP_SHIFT) < MG_BITMAP_SIZE) 
    {
        if ((mg_bitmap[value>>MG_BITMAP_SHIFT] & (1<<(value & MG_BITMAP_MASK)))!=0) 
        {
            return_code = true;
        }
    }
    return return_code;
}




/* ============================================================================ *\
 * hal_memory.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       hal_memory.c-5:csrc:2
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains vehicle speed sensor virtual I/O
\* ============================================================================ */

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "io_type.h"


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "filenvmd.h"
#include "hal_memory.h"
#include "HLS.h"
#include "hal.h"


extern uint32_t start_of_approm[];
extern uint32_t end_of_approm[];
extern uint32_t start_of_ecalrom[];
extern uint32_t end_of_ecalrom[];
extern uint32_t start_of_calrom[];
extern uint32_t end_of_calrom[];
extern uint32_t start_of_stack[];
extern uint32_t end_of_stack[];
extern uint32_t start_of_appram[];
extern uint32_t end_of_appram[];
extern uint32_t start_of_crit_nvram[];
extern uint32_t end_of_crit_nvram[];
extern uint32_t start_of_noncrit_nvram[];
extern uint32_t end_of_noncrit_nvram[];
extern uint32_t start_of_noncrit_core_nvram[];
extern uint32_t end_of_noncrit_core_nvram[];
//=============================================================================
// IO_MEM_ROM_Block_Checksum_Program
//=============================================================================
const TsMEMORY_SEGMENT_POINTERS const IO_MEM_ROM_Block_Checksum[] =
{
	{
		(WORD *)start_of_ecalrom,
		(WORD *)end_of_ecalrom
	}, 
	{
		(WORD *)start_of_calrom,
		(WORD *)end_of_calrom
	},  
	{
		(WORD *)start_of_approm,
		(WORD *)end_of_approm
	},
	{
		0,
		0
	}
};

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */

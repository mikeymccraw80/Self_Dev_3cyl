/*
 *	Copyright 2008 WindRiver Systems, Inc. All Rights Reserved
 *	Implementation module : diab/asm.h
 *
 *	Description :
 *	This module provides access to the target assembly instructions
 *	through intrinsic function prototypes.
 */

#ifdef	__ppc		/* PowerPC */
#include "ppcasm.h"
#endif
#ifdef __arm		/* ARM */
#include "armasm.h"
#endif

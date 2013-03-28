/*	Copyright 2009 WindRiver Systems, Inc. All Rights Reserved		*/
/*	Implementation module : armasm.h					*/
/*										*/
/*	Description :								*/
/*	This module provides access to the target assembly instructions		*/
/*	through intrinsic function prototypes.					*/


#ifndef	SUPPRESS_INTRINSIC_FUNCTIONS

extern void __bkpt( const unsigned int) __attribute__((intrinsic_function(9, 0, "bkpt") ));
extern int __clz( int) __attribute__((intrinsic_pseudo(1, "clz") ));
extern void __nop( void) __attribute__((intrinsic_function(8, 0, "nop") ));
extern int __pkhbt( int,  int) __attribute__((intrinsic_pseudo(1, "pkhbt") ));
extern int __pkhtb( int,  int) __attribute__((intrinsic_pseudo(1, "pkhtb") ));
extern int __rev( int) __attribute__((intrinsic_pseudo(1, "rev") ));
extern int __rev16( int) __attribute__((intrinsic_pseudo(1, "rev16") ));
extern short __revsh( short) __attribute__((intrinsic_pseudo(1, "revsh") ));
extern void __swi( const unsigned int) __attribute__((intrinsic_function(9, 0, "swi") ));
extern void __teq( int,  int) __attribute__((intrinsic_function(10, 0, "teq") ));

#endif	/* SUPPRESS_INTRINSIC_FUNCTIONS */

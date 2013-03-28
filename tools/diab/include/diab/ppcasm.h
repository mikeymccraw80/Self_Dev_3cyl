/*	Copyright 2008 WindRiver Systems, Inc. All Rights Reserved		*/
/*	Implementation module : ppcasm.h					*/
/*										*/
/*	Description :								*/
/*	This module provides access to the target assembly instructions		*/
/*	through intrinsic function prototypes.					*/

#ifdef	PPCASM_DEFINE_SPRS	/* Don't want to interfere with the user's definitions */

#define XER		1
#define LR		8
#define CTR		9

#define SPRG0		272
#define SPRG1		273
#define SPRG2		274
#define SPRG3		275
#define SPRG4		276
#define SPRG5		277
#define SPRG6		278
#define SPRG7		279

#define	SRR0		26	/* R/W	Save/Restore Register 0. Defined by Book E. */
#define	SRR1		27	/* R/W	Save/Restore Register 1. Defined by Book E. */
#define	CSRR0		58	/* R/W	Critical Save/Restore Register 0. Defined by Book E. */
#define	CSRR1		59	/* R/W	Critical Save/Restore Register 1. Defined by Book E. */
#define	DSRR0		574	/* R/W	Debug Save/Restore Register 0. Defined by Enhanced Debug APU. */
#define	DSRR1		575	/* R/W	Debug Save/Restore Register 1. Defined by Enhanced Debug APU. */
#define	GSRR0		378	/* R/W	Guest Save/Restore Register 0. Defined by Embedded Hypervisor APU. */
#define	GSRR1		379	/* R/W	Guest Save/Restore Register 1. Defined by Embedded Hypervisor APU. */
#define MCSRR0		570	/* R/W	Machine Check Save/Restore Register 0. */
#define MCSRR1		571	/* R/W	Machine Check Save/Restore Register 1. */

#define	DEC		22	/* R/W	Decrementer. Defined by Book E. */
#define	ESR		62	/* R/W	Exception Syndrome Register. Defined by Book E.	*/
#define	HID0		1008	/* R/W	Hardware Implementation Dependent Register 0.	*/
#define	HID1		1009	/* R/W	Hardware Implementation Dependent Register 1.	*/
#define	PVR		287	/* RO	Processor Version Register. Defined by Book E.	*/
#define	PIR		286	/* R/W 	Processor ID Register. Defined by Book E. */

#endif	/* PPCASM_DEFINE_SPRS */

#ifndef	SUPPRESS_INTRINSIC_FUNCTIONS

extern int __cntlzw( int) __attribute__((intrinsic_pseudo(1, "cntlzw") ));
extern void __dcba( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcba") ));
extern void __dcbf( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcbf") ));
extern void __dcbfep( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcbfep") ));
extern void __dcbi( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcbi") ));
extern void __dcblc( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "dcblc") ));
extern void __dcbst( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcbst") ));
extern void __dcbstep( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcbstep") ));
extern void __dcbt( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "dcbt") ));
extern void __dcbtep( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "dcbtep") ));
extern void __dcbtls( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "dcbtls") ));
extern void __dcbtst( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "dcbtst") ));
extern void __dcbtstep( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "dcbtstep") ));
extern void __dcbtstls( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "dcbtstls") ));
extern void __dcbz( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcbz") ));
extern void __dcbzep( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcbzep") ));
extern void __dcbzl( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcbzl") ));
extern void __dcbzlep( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dcbzlep") ));
extern void __dsn( const void*,  int) __attribute__((intrinsic_function(2094, 0, "dsn") ));
extern void __ehpriv( void) __attribute__((intrinsic_function(8, 0, "ehpriv") ));
extern void __eieio( void) __attribute__((intrinsic_function(8, 0, "eieio") ));
extern int __eqv( int,  int) __attribute__((intrinsic_pseudo(3, "eqv") ));
extern void __icbi( const void*,  int) __attribute__((intrinsic_function(2094, 0, "icbi") ));
extern void __icbiep( const void*,  int) __attribute__((intrinsic_function(2094, 0, "icbiep") ));
extern void __icblc( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "icblc") ));
extern void __icbt( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "icbt") ));
extern void __icbtls( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "icbtls") ));
extern void __isync( void) __attribute__((intrinsic_function(8, 0, "isync") ));
extern char __lbdx( const void*,  int) __attribute__((intrinsic_function(2030, 0, "lbdx") ));
extern char __lbepx( const void*,  int) __attribute__((intrinsic_function(2030, 0, "lbepx") ));
extern unsigned short __lhdx( const void*,  int) __attribute__((intrinsic_function(2030, 0, "lhdx") ));
extern unsigned short __lhepx( const void*,  int) __attribute__((intrinsic_function(2030, 0, "lhepx") ));
extern int __lwdx( const void*,  int) __attribute__((intrinsic_function(2030, 0, "lwdx") ));
extern int __lwepx( const void*,  int) __attribute__((intrinsic_function(2030, 0, "lwepx") ));
extern void __mbar( const unsigned int) __attribute__((intrinsic_function(7, 0, "mbar") ));
extern int __mfcr( void) __attribute__((intrinsic_function(2083, 0, "mfcr") ));
extern int __mfdcr( const unsigned int) __attribute__((intrinsic_function(2016, 0, "mfdcr") ));
extern int __mfmsr( void) __attribute__((intrinsic_function(2083, 0, "mfmsr") ));
extern int __mfspr( const unsigned int) __attribute__((intrinsic_function(2016, 0, "mfspr") ));
extern void __msgclr( int) __attribute__((intrinsic_function(2091, 0, "msgclr") ));
extern void __msgsnd( int) __attribute__((intrinsic_function(2091, 0, "msgsnd") ));
extern void __msync( void) __attribute__((intrinsic_function(8, 0, "msync") ));
extern void __mtdcr( const unsigned int,  int) __attribute__((intrinsic_function(2090, 0, "mtdcr") ));
extern void __mtmsr( int) __attribute__((intrinsic_function(2091, 0, "mtmsr") ));
extern void __mtspr( const unsigned int,  int) __attribute__((intrinsic_function(2090, 0, "mtspr") ));
extern void __nop( void) __attribute__((intrinsic_function(8, 0, "nop") ));
extern void __sync( void) __attribute__((intrinsic_function(8, 0, "sync") ));
extern void __tlbilx( const unsigned int,  const void*,  int) __attribute__((intrinsic_function(2095, 0, "tlbilx") ));
extern void __tlbivax( const void*,  int) __attribute__((intrinsic_function(2094, 0, "tlbivax") ));
extern void __tlbre( void) __attribute__((intrinsic_function(8, 0, "tlbre") ));
extern void __tlbsx( const void*,  int) __attribute__((intrinsic_function(2094, 0, "tlbsx") ));
extern void __tlbsync( void) __attribute__((intrinsic_function(8, 0, "tlbsync") ));
extern void __tlbwe( void) __attribute__((intrinsic_function(8, 0, "tlbwe") ));
extern void __wait( void) __attribute__((intrinsic_function(8, 0, "wait") ));
extern void __wrtee( int) __attribute__((intrinsic_function(2091, 0, "wrtee") ));
extern void __wrteei( const unsigned int) __attribute__((intrinsic_function(7, 0, "wrteei") ));

#endif	/* SUPPRESS_INTRINSIC_FUNCTIONS */

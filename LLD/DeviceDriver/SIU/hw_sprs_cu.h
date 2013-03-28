#ifndef HW_SPRS_CU_H
#define HW_SPRS_CU_H

#include "reuse.h"


/* Processor ID and Version SPRs */
#define PIR_ro_SPR ( 286 )
#define PVR_ro_SPR ( 287 )

/* MMU regs */
#define MMU_MAS0_SPR    (624)
#define MMU_MAS1_SPR    (625)
#define MMU_MAS2_SPR    (626)
#define MMU_MAS3_SPR    (627)
#define MMU_MAS4_SPR    (628)
#define MMU_MAS6_SPR    (630)

#define MMU_CSR_SPR     (1012)

#define MCSR_SPR ( 572 )
#define MMUCFG_ro_SPR ( 1015 )

/* Timer regs */
#define TBU_WRITE_SPR   (285)
#define TBL_WRITE_SPR   (284)

#define TBU_READ_SPR    (269)
#define TBL_READ_SPR    (268)

#define TLB0CFG_ro_SPR ( 688 )
#define TLB1CFG_ro_SPR ( 689 )
#define TSR_SPR        ( 336 )

#define TCR_SPR         (340)

#define DEC_SPR         (22)
#define DECAR_SPR       (54)

/* Hardware Implementation Dependant regs */
#define HID0_SPR        (1008)
#define HID1_SPR        (1009)

/* System Exception Vector Offsets */
#define IVOR0_SPR       (400)
#define IVOR1_SPR       (401)
#define IVOR2_SPR       (402)
#define IVOR3_SPR       (403)
#define IVOR4_SPR       (404)
#define IVOR5_SPR       (405)
#define IVOR6_SPR       (406)
#define IVOR7_SPR       (407)
#define IVOR8_SPR       (408)
#define IVOR9_SPR       (409)
#define IVOR10_SPR      (410)
#define IVOR11_SPR      (411)
#define IVOR12_SPR      (412)
#define IVOR13_SPR      (413)
#define IVOR14_SPR      (414)
#define IVOR15_SPR      (415)
#define IVOR32_SPR      (528)
#define IVOR33_SPR      (529)
#define IVOR34_SPR      (530)

/* Interrupt Vector Prefix reg */
#define IVPR_SPR        (63)

/* Other SPR definitions */
#define BUCSR_SPR ( 1013 )
#define CSRR0_SPR ( 58 )
#define CSRR1_SPR ( 59 )
#define CTR_SPR ( 9 )
#define CTXCR_SPR ( 560 )
#define DAC1_SPR ( 316 )
#define DAC2_SPR ( 317 )
#define DVC1_SPR ( 318 )
#define DVC2_SPR (319 )
#define DBCNT_SPR ( 562 )
#define DBCR0_SPR ( 308 )
#define DBCR1_SPR ( 309 )
#define DBCR2_SPR ( 310 )
#define DBCR3_SPR ( 561 )
#define DBSR_ro_co_SPR ( 304 )
#define DEAR_SPR ( 61 )
#define DSRR0_SPR ( 574 )
#define DSRR1_SPR ( 575 )
#define ESR_SPR ( 62 )
#define IAC1_SPR ( 312 )
#define IAC2_SPR ( 313 )
#define IAC3_SPR ( 314 )
#define IAC4_SPR ( 315 )
#define LR_SPR ( 8 )
#define PID0_SPR ( 48 )
#define SPEFSCR_SPR ( 512 )
#define SPRG0_SPR ( 272 )
#define SPRG1_SPR ( 273 )
#define SPRG2_SPR ( 274 )
#define SPRG3_SPR ( 275 )
#define SPRG4_SPR ( 276 )
#define SPRG4_ro_SPR ( 260 )
#define SPRG5_SPR ( 277 )
#define SPRG5_ro_SPR ( 261 )
#define SPRG6_SPR ( 278 )
#define SPRG6_ro_SPR ( 262 )
#define SPRG7_SPR ( 279 )
#define SPRG7_ro_SPR ( 263 )
#define SRR0_SPR ( 26 )
#define SRR1_SPR ( 27 )
#define SVR_ro_SPR ( 1023 )
#define USPRG0_SPR ( 256 )
#define XER_SPR ( 1 )
#define L1CFG0_SPR ( 515 )

#endif // HW_SPRS_CU_H


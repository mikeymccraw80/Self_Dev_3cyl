#ifndef KW2DLLCF
#define KW2DLLCF
/* ============================================================================ *\
 * kw2dll.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2dllcf.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:10:01 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 driver module configuration.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "reuse.h"

/* Keyword Physical and Functional Message ID */
#define MyImmoPhysicalAddr    (0x17)
#define MyImmoSourceAddr      (0xC1)
#define MyPhysicalAddr        (0x11)
#define MyFunctionalAddr      (0x33)
#define MyFunctionalAddrNew   (0x10)
#define MySourceAddr0         (0xF0)
#define MySourceAddr1         (0xF1)

#define DefaultP2Min (50)                                  /* 0.5 ms per count */
#define DefaultP2Max (2)                                   /* 25 ms per count */
#define DefaultP3Min (110)                                 /* 0.5 ms per count */
#define DefaultP3Max (20)                                  /* 250 ms per count */
#define DefaultP4Min (0)                                  /* 0 msec */

#define TesterP1Min (0)
#define TesterP2Min (70)
#define TesterP2Max (2)
#define TesterP3Min (65)
#define TesterP3Max (20)
#define TesterP4Min (0)
#define Kw2000VIOUpdatePeriod (0.00781) /*PeriodicLoopPeriodSec*/

#define UpdateShiftFactor (2)        /*Size Data buffer Based on Baud */

#define Kw2000HighSpeedBaudRate   (10400) /* The buffer size is based
                                       on the highest baud rate used. */

#define NbBytesPerSec (Kw2000HighSpeedBaudRate / 10)

#define KW2000InputBufferSize ((uint8_t) (UpdateShiftFactor * \
                            Kw2000VIOUpdatePeriod * NbBytesPerSec + 2))
/**********************************************************************
*  The timing parameters in Keyword 2000 are converted to loop-counts *
*  in almost all cases.  The loop-count is function of the schedule   *
*  rate of the keyword process.  The values are rounded and           *
*  approximated.  For the current implementation the schedult rate of *
*  the keyword process is 7.81ms ( 0.00781 seconds.)  These values    *
*  must be updated with extreme care.                                 *
**********************************************************************/
#define P4Max          (3)    /* 20 ms / 7.81 ms. */
                              /* The value is rounded to next intger.*/

#define TIdleInit      (7)      /* (0.050 / .00781) */
#define TIdleRestart   (2)      /* (0.010 / .00781) */
#define TIdleTimout    (0)
#define TIdleStopCom   (6)      /* (0.040 / .00781) */

#define LoopRateInMsRounded    ((uint8_t) 8)  /*--- 7.81 ms ----*/

/*********************************************************************
* The P2Min LoopCount value is rounded to the next integer.  P2Min   *
* precision is 0.5.  For Loop rate of 8ms,the P2Min LoopCount is     *
*(P2Min + 15 )/16.                                                   *
**********************************************************************/
#define  P2MinLoopCountVal(TimerVal)  ((uint8_t)\
	                         ((TimerVal+((2*LoopRateInMsRounded)-1))/ \
                                             (2*LoopRateInMsRounded)))

/**********************************************************************
*  The loop-count multiplier is 25 / 7.81.  The closest computed value*
*  is equivalent ot 32 / 10.                                          *
**********************************************************************/
#define  P2MaxLoopCountVal  ((uint8_t) 32 / 10 )

/**********************************************************************
*  The loop-count multiplier is 250 / 7.81.  The closest computed value*
*  is equivalent ot 370/ 10.                                          *
**********************************************************************/
#define  P3MaxLoopCountVal  ((uint8_t) 320 )

/**********************************************************************
*  FastInitLowTime = FastInitHighTime = 25 ms.  FastInitLowTime has   *
*  variation of +/- 1ms.                                              *
*  These parameters are used as counters to detect keyword 2000       *
*  Fastinit pattern. ( Fastinit pattern is 25ms low and 25 ms high.   *
*  The procedures Waiting25msLowSynchKw2000State and                  *
*  AwaitingMessageKw2000State use these values to measure the         *
*  duration of Logic low and Logic high at Fastinit.                  *
*  The loop rate values in the range 2ms-9ms were simulated.  The     *
*  software integrator is strongly advised to understand the fastinit *
*  reception logic and verify the operation.  For values beyond the   *
*  range mentioned need adjustments.                                  *
**********************************************************************/

/**********************************************************************
*  The value of FastInitLogicMin and FastInitLogicMax for various loop*
*  rates are given below. The loop rates are assumed rounded to the   *
*  integer vaue.                                                      *
*  Loop rate = 8ms:   FastInitLogicMin = 2;  FastInitLogicMax = 4     *
*            = 7ms:   FastInitLogicMin = 2;  FastInitLogicMax = 4     *
*            = 6ms:   FastInitLogicMin = 2;  FastInitLogicMax = 5     *
*            = 5ms:   FastInitLogicMin = 3;  FastInitLogicMax = 6     *
*            = 4ms:   FastInitLogicMin = 4;  FastInitLogicMax = 7     *
*            = 3ms:   FastInitLogicMin = 6;  FastInitLogicMax = 9     *
*            = 2ms:   FastInitLogicMin = 10;  FastInitLogicMax = 13   *
* The software integrator is strongly advised to verify after         *
* initialising these parameters.  These parameters may be required to *
* adjusted for some loop rates.                                       *
**********************************************************************/

#define  FastInitLogicMin    (2)
#define  FastInitLogicMax    (4)
#define  FastInitLogicHigh   (FastInitLogicMax - 2)

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 14/08/06	Jerry.Wu      mt20u2#53
 * + Update keyword to support message with functional address 33
 *  - Change MyFunctionalAddr to 33.
 *
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - defined: TesterPxMin/ TesterPxMax
\* ============================================================================ */
#endif

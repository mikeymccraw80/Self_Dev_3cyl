/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : FlashSusupend.c
*
* DESCRIPTION :  This function will check if there is any high voltage
*                                operation, erase or program, in progress on the C90LC
*                                module and if the operation can be suspended.
*                                This function will suspend the ongoing operation
*                                if it can be suspended.
*
* COPYRIGHT :(c) 2009, Freescale & STMicroelectronics
*
* VERSION   : Beta 1.0
* DATE      : 11.05.2009
* AUTHOR    : ...
*
* HISTORY :
* 2009.11.05		 	   Leonardo Colombo		"Unified" version supporting all targets with LC flash
******************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90lc.h"

/*******************************************************************
| external declarations
|------------------------------------------------------------------*/

/*******************************************************************
| defines and macros (scope: module-local)
|------------------------------------------------------------------*/
#define CFLASH_BASE_ADDR   (UINT32)(0xC3F88000)
#define DFLASH_BASE_ADDR   (UINT32)(0xC3F8C000)
#define C1_BASE_ADDR       (UINT32)(0xC3FB0000)
#define C2_BASE_ADDR       (UINT32)(0xC3FB4000)

/*******************************************************************
| typedefs and structures (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| global variable definitions (scope: module-exported)
|------------------------------------------------------------------*/

/*******************************************************************
| global variable definitions (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| function prototypes (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| function implementations (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| function implementations (scope: module-exported)
|------------------------------------------------------------------*/

/*************************************************************************
 * FUNCTION      :  FlashSuspend
 * DESCRIPTION   :  This function will check if there is any high voltage
 *                                  operation, erase or program, in progress on the C90FL
 *                                  module and if the operation can be suspended.
 *                                  This function will suspend the ongoing operation
 *                                  if it can be suspended.
 * PARAMETERS    :
 *                  pSSDConfig - Flash driver configuration structure
 *                  suspendState - variable to store state of the ongoing
 *                                            flash operation
 *                  suspendFlag - Flag to keep track of suspension
 * RETURN        : C90FL_OK - passes
 *                          C90FL_ERROR_SUSP - Ongoing operation cannot be suspended
 *************************************************************************/
UINT32 ssd_c90lc_FlashSuspend (PSSD_CONFIG pSSDConfig, UINT8 *suspendState, UINT8 *suspendFlag)
{
    register UINT32 returnCode;     /* return code */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */

    returnCode = C90FL_OK;
    *suspendState = NO_OPERATION;
    *suspendFlag = FALSE;

    MCRAddress = pSSDConfig->c90flRegBase + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);

    /* no P/E sequence: PGM=0 and ERS=0

       possible stages for program sequece:
          a. interlock write;               (PGM=1;EHV=0;  PSUS=0;DONE=1; ignore PEG)  OR (ERS=1;ESUS=1)
          b. high voltage active;           (PGM=1;EHV=1;  PSUS=0;DONE=0; ignore PEG)  OR (ERS=1;ESUS=1)
          c. entering suspend state;        (PGM=1;EHV=1;  PSUS=1;DONE=0; ignore PEG)  OR (ERS=1;ESUS=1)  Not possible for flash LC
          d. in suspend state;              (PGM=1;EHV=1/0;PSUS=1;DONE=1; ignore PEG)  OR (ERS=1;ESUS=1)    Not possible for flash LC
          e. resuming from suspend state;   (PGM=1;EHV=1;  PSUS=0;DONE=1; ignore PEG)  OR (ERS=1;ESUS=1) Not possible for flash LC
          f. high voltage stopped;          (PGM=1;EHV=1;  PSUS=0;DONE=1; valid  PEG)  OR (ERS=1;ESUS=1)
          g. abort period.                  (PGM=1;EHV=0;  PSUS=0;DONE=0; ignore PEG)  OR (ERS=1;ESUS=1)
       Note: 1. Only stage e and f has the same condition;
             2. PGM  set: STOP=0 and ERS=0 or ERS=1 and ESUS=1 and EHV=0
             3. PGM  clear: EHV=0 and PSUS=0 and DONE=1
             4. PSUS set: PGM=1 and EHV=1;
             5. PSUS clear: DONE=1 and EHV=1

       possible stages for erase sequece:
          a. interlock write;               (ERS=1;EHV=0;  ESUS=0;DONE=1; ignore PEG)  AND (PGM=0;PSUS=0)
          b. high voltage active;           (ERS=1;EHV=1;  ESUS=0;DONE=0; ignore PEG)  AND (PGM=0;PSUS=0)
          c. entering suspend state;        (ERS=1;EHV=1;  ESUS=1;DONE=0; ignore PEG)  AND (PGM=0;PSUS=0)
          d. in suspend state;              (ERS=1;EHV=1/0;ESUS=1;DONE=1; ignore PEG)  AND (PGM=0;PSUS=0)
          e. resuming from suspend state;   (ERS=1;EHV=1;  ESUS=0;DONE=1; ignore PEG)  AND (PGM=0;PSUS=0)
          f. high voltage stopped;          (ERS=1;EHV=1;  ESUS=0;DONE=1; valid  PEG)  AND (PGM=0;PSUS=0)
          g. abort period.                  (ERS=1;EHV=0;  ESUS=0;DONE=0; ignore PEG)  AND (PGM=0;PSUS=0)
       Note: 1. Only stage e and f has the same condition
             2. ERS  set: STOP=0 and ERS=0 and PGM=0
             3. ERS  clear: EHV=0 and ESUS=0 and DONE=1
             4. ESUS set: ERS=1 and EHV=1 and PGM=0
             5. ESUS clear: DONE=1 and EHV=1 and PGM=0

       FlashSuspend procedures:
       no sequence: NO_OPERATION
       stage     a: PGM_WRITE, ERS_WRITE
       stage b,e,f: suspend and return the current state for erase  return error for program
       stage   c,d: return the current state for erase  return error for program
       stage     g: switch to stage "a" and return the current state */

    /* No program/erase sequence */
    if ( !(MCRValue & (C90FL_MCR_PGM | C90FL_MCR_ERS)) )
    {
        goto EXIT;
    }

    if ( (MCRValue & C90FL_MCR_PGM) ||
         ((MCRValue & C90FL_MCR_ERS) && !(MCRValue & C90FL_MCR_ESUS)) )
    {
        if ( !(MCRValue & C90FL_MCR_EHV) )
        {
            /* a. interlock write */
            /* g. abort period */

            if (MCRValue & C90FL_MCR_PGM)
            {
                *suspendState = PGM_WRITE;
            }

            if (MCRValue & C90FL_MCR_ERS)
            {
                *suspendState = ERS_WRITE;
            }
            /* for interlock write stage, MCR-DONE bit already high */
            /* for abort transition stage, wait MCR-DONE bit set */
            goto EXIT_WAIT;
        }
        else
        {
            /* b. high voltage active */
            /* e. resuming from suspend state */
            /* f. high voltage stopped */

            if (MCRValue & C90FL_MCR_PGM)
            {
                /* Programming operation cannot be suspended */
                returnCode = C90FL_ERROR_SUSP;
                *suspendState = NO_SUS;
                goto EXIT;
			         }
            else  /*  ERS =1 */
            {
                C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_ESUS);   /* set MCR-ESUS bit */
                *suspendFlag = TRUE;
			         }
        }
    }

    /* Stages b, e, f, c and d will become a suspend state */

    /* read C90FLMCR again */
    MCRValue = C90FL_REG_READ (MCRAddress);

    if (MCRValue & C90FL_MCR_ESUS)
    {
        *suspendState = ERS_SUS;

        /* check MCR-PEAS bit */
        if (MCRValue & C90FL_MCR_PEAS)
        {
            *suspendState = SHADOW_ERS_SUS;
        }
    }

EXIT_WAIT:
    /* Wait until MCR-DONE = 1 */
    while ( !C90FL_REG_BIT_TEST (MCRAddress, C90FL_MCR_DONE) )
    {
    }

    /* Set MCR-EHV to 0 */
    C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_EHV);

EXIT:
    if (pSSDConfig->BDMEnable)
    {
        //asm ( "mr   r3,returnCode" );   /* save the return code to R3 */
        #ifdef VLE_ASM
        	asm ( "se_sc " );                  /* generate system call interrupt */
        #else
        	asm ( "sc " );
        #endif
    }

    return returnCode;
}

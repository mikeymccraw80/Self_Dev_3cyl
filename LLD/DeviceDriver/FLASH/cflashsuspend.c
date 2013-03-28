 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************
 *************************************************************************
 *                                                                       *
 *                Common Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  cflashsuspend.c                                      *
 * FUNCTION      :  CflashSuspend                                        *
 * DESCRIPTION   :  This function will check if there is any high voltage*
 *                  operation, erase or program, in progress on the C90FL*
 *                  module and if the operation can be suspended.        *
 *                  This function will suspend the ongoing operation     *
 *                  if it can be suspended. This function is the common  *
 *                  driver  											 *
 * PARAMETERS    :                                                       *
 *                  MCRAddress, MCRValue of the flash block			     *
 *                  suspendState and Suspend flag - variables to store   *
 *                      state of the ongoing flash operation             *
 * RETURN VALUES :  None									             *
 *                 													     *
 * DATE          :  September 18, 2008                                   *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.0   09.18.2008         Vikas Kothari	    Initial Version
 0.0.1   07.24.2009         Arvind Awasthi      Added delay to fix H/W
                                                bug while waiting for MCR
                                                DONE bit to set after
                                                setting PSUS & ESUS.
 0.4.4	 07.27.2010	        FPT Team 		    Finalize to this version												
************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"

/*
Notes:*/
/* no P/E sequence: PGM=0 and ERS=0

possible stages for program sequece:
  a. interlock write;               (PGM=1;EHV=0;  PSUS=0;DONE=1; ignore PEG)  OR (ERS=1;ESUS=1)
  b. high voltage active;           (PGM=1;EHV=1;  PSUS=0;DONE=0; ignore PEG)  OR (ERS=1;ESUS=1)
  c. entering suspend state;        (PGM=1;EHV=1;  PSUS=1;DONE=0; ignore PEG)  OR (ERS=1;ESUS=1)
  d. in suspend state;              (PGM=1;EHV=1/0;PSUS=1;DONE=1; ignore PEG)  OR (ERS=1;ESUS=1)
  e. resuming from suspend state;   (PGM=1;EHV=1;  PSUS=0;DONE=1; ignore PEG)  OR (ERS=1;ESUS=1)
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
stage     a: PGM_WRITE, ERS_WRITE, ERS_SUS_PGM_WRITE
stage b,e,f: suspend and return the current state
stage   c,d: return the current state
stage     g: switch to stage "a" and return the current state */

void CflashSuspend (UINT32 MCRAddress,
                    UINT8 *suspendState,
                    UINT8 *suspendFlag)
{

    UINT8 exitFlag;
    UINT32 MCRValue;
    UINT16 delay = 0;              /* variable added for delay*/

    MCRValue = C90FL_REG_READ (MCRAddress);

    if ( ((MCRValue & C90FL_MCR_PGM) && !(MCRValue & C90FL_MCR_PSUS)) ||
         ((MCRValue & C90FL_MCR_ERS) && !(MCRValue & C90FL_MCR_ESUS)) )
    {
        if ( !(MCRValue & C90FL_MCR_EHV) )
        {
            /* a. interlock write */
            /* g. abort period */

            if (MCRValue & C90FL_MCR_PGM)
            {
                *suspendState = PGM_WRITE;

                if (MCRValue & C90FL_MCR_ERS)
                    *suspendState = ERS_SUS_PGM_WRITE;
            }
            else
                *suspendState = ERS_WRITE;

            /* for interlock write stage, MCR-DONE bit already high */
            /* for abort transition stage, wait MCR-DONE bit set */
            exitFlag = TRUE;
        }
        else
        {
            /* b. high voltage active */
            /* e. resuming from suspend state */
            /* f. high voltage stopped */

            if (MCRValue & C90FL_MCR_PGM)
            {
                C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_PSUS);   /* set MCR-PSUS bit */
                /* Add delay to counter hardware bug*/
                /* A delay of approximately 20us for the below clock settings*/
                /* SYSTEM CLOCK FREQUENCY = 128MHZ*/
                /* A delay of about 20us*/
                for (delay=0;delay<0xA0;delay++);
			}
            else
            {
                C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_ESUS);   /* set MCR-ESUS bit */
                /* Add delay to counter hardware bug*/
                /* A delay of approximately 40us for the below clock settings*/
                /* SYSTEM CLOCK FREQUENCY = 128MHZ*/
                /* A delay of about 40us*/
                for (delay=0;delay<0x140;delay++);
			}

            *suspendFlag = TRUE;
        }
    }


    /* Stages b, e, f, c and d will become a suspend state */
    if(exitFlag != TRUE)
    {
	    /* read C90FLMCR again */
	    MCRValue = C90FL_REG_READ (MCRAddress);

	    if (MCRValue & C90FL_MCR_PSUS)
	    {
	        *suspendState = PGM_SUS;

	        if (MCRValue & C90FL_MCR_ESUS)
	        {
	            *suspendState = ERS_SUS_PGM_SUS;
			}
	    }
	    else if (MCRValue & C90FL_MCR_ESUS)
	    {
	        *suspendState = ERS_SUS;

	        /* check MCR-PEAS bit */
	        if (MCRValue & C90FL_MCR_PEAS)
	        {
	            *suspendState = SHADOW_ERS_SUS;
			}
	    }
    }
}
/* End of File */

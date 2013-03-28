 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *                Common Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  cgetlock.c                                           *
 * FUNCTION      :  CgetLock                                             *
 * DESCRIPTION   :  This function will check the block locking status of *
 *                  Shadow/Low/Middle/High address spaces in the C90FL   *
 *                  module.                                              *
 * PARAMETERS    :                                                       *
 *                  regsisterBase: Base address of MCR register for the  *
 *                  respective bank                                      *
 *                  blkLockIndicator - variable for storing block lock   *
 *                                    indicator value                    *
 *                  blkLockEnabled - flag to keep track of lock          *
 *                  blkLockState - variable for storing block lock state *
 *                                 value                                 *
 * RETURN        : C90FL_OK - passes                                     *
 *                 C90FL_ERROR_LOCK_INDICATOR - wrong indicator value    *
 *                 C90FL_ERROR_PASSWORD - incorrect password             *
 * DATE          : September 11, 2008                                    *
 * AUTHOR        : Infosys Team                                          *
 * E-mail        : r56611@freescale.com                                  *
 *                                                                       *
 *************************************************************************/

 /******************************* CHANGES *********************************
  0.0.0    09.11.2008        Arvind Awasthi      Initial Version
  0.4.4	   07.27.2010	     FPT Team 		     Finalize to this version
 *************************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90fl.h"


UINT32 CgetLock (UINT32 registerBase,
                 UINT8 blkLockIndicator,
                 BOOL  shadowLockPrimary,
                 BOOL *blkLockEnabled,
                 UINT32 *blkLockState)
{
    register UINT32 returnCode;     /* return code */
    UINT32 temp;                    /* temporary variable */
    UINT32 address;                 /* address of block locking register */
    UINT32 mask;                    /* block locking bit mask for the address space */
    UINT32 shift;                   /* bit shift value for the block locking field of an address space */

    returnCode = C90FL_OK;
    *blkLockEnabled = FALSE;

    /* assume blkLockIndicator == LOCK_SHADOW_PRIMARY by default */
    address = C90FL_LML;
    mask = C90FL_LML_SLOCK;
    shift = 20;

    if (LOCK_LOW_PRIMARY == blkLockIndicator)
    {
        mask = C90FL_LML_LLOCK;
        shift = 0;
    }
    else if (LOCK_MID_PRIMARY == blkLockIndicator)
    {
        mask = C90FL_LML_MLOCK;
        shift = 16;
    }
    else if (FALSE == shadowLockPrimary)
    {
        /* assume blkLockIndicator == LOCK_SHADOW_SECONDARY */
        address = C90FL_SLL;

        if (LOCK_LOW_SECONDARY == blkLockIndicator)
        {
            mask = C90FL_SLL_SLLOCK;
            shift = 0;
        }
        else if (LOCK_MID_SECONDARY == blkLockIndicator)
        {
            mask = C90FL_SLL_SMLOCK;
            shift = 16;
        }
        else if (LOCK_HIGH == blkLockIndicator)
        {
            address = C90FL_HBL;
            mask = C90FL_HBL_HBLOCK;
            shift = 0;
        }
    }
    else
    {
		/*do nothing*/
	}

    temp = C90FL_REG_READ (registerBase + address);
    if (temp & 0x80000000)
        *blkLockEnabled = TRUE;

    /* mask off the other bits and make proper shift */
    *blkLockState = (temp & mask) >> shift;


    return returnCode;
}


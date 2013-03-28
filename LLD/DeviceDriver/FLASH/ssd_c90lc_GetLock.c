/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : getlock.c
*
* DESCRIPTION : This file contains GetLock function implementation
*
* COPYRIGHT :(c) 2008, Freescale & STMicroelectronics
*
* VERSION   : EAR 0.2
* DATE      : 04.18.2008
* AUTHOR    : ...
*
* HISTORY :
* 2007.12.11    Arvind Awasthi   Initial Version
* 2008.04.18    Leonardo Colombo Changed header in agreement with JDP SW
*                                template
* 2009.01.28    Leonardo Colombo Porting for xPC563M64 devices (C0, C1, C2, D)
******************************************************************/
#include    "ssd_types.h"
#include    "ssd_c90lc.h"

/*******************************************************************
| external declarations
|------------------------------------------------------------------*/

/*******************************************************************
| defines and macros (scope: module-local)
|------------------------------------------------------------------*/

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
 *                                                                       *
 * FUNCTION      : GetLock                                               *
 * DESCRIPTION   : This function will verify a specified flash range     *
 *                 to be erased.                                         *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 blkLockIndicator - variable for storing block lock    *
 *                                    indicator value                    *
 *                 blkLockEnabled - flag to keep track of lock           *
 *                 blkLockState - variable for storing block lock state  *
 *                                 value                                 *
 * RETURN        : C90FL_OK - passes                                     *
 *                 C90FL_ERROR_LOCK_INDICATOR - wrong indicator value    *
 *                 C90FL_ERROR_PASSWORD - incorrect password             *
 *                                                                       *
 *************************************************************************/
UINT32 ssd_c90lc_GetLock ( PSSD_CONFIG pSSDConfig,
                 UINT8 blkLockIndicator,
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

    if (blkLockIndicator > LOCK_HIGH)
    {
        returnCode = C90FL_ERROR_LOCK_INDICATOR;
        goto EXIT;
    }

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
    else if (LOCK_SHADOW_PRIMARY != blkLockIndicator)
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

    temp = C90FL_REG_READ (pSSDConfig->c90flRegBase + address);
    if (temp & 0x80000000)
        *blkLockEnabled = TRUE;

    /* mask off the other bits and make proper shift */
    *blkLockState = (temp & mask) >> shift;

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


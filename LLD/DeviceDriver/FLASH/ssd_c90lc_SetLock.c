/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : setlock.c
*
* DESCRIPTION : This file contains SetLock function implementation
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
 * FUNCTION      : SetLock                                               *
 * DESCRIPTION   : This function will verify a specified flash range     *
 *                 to be erased.                                         *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 blkLockIndicator - variable for storing block lock    *
 *                                    indicator value                    *
 *                 blkLockState - variable for storing block lock state  *
 *                                 value                                 *
 *                 password - Variable for storing password              *
 * RETURN        : C90FL_OK - passes                                     *
 *                 C90FL_ERROR_LOCK_INDICATOR - wrong indicator value    *
 *                 C90FL_ERROR_PASSWORD - incorrect password             *
 *                                                                       *
 *************************************************************************/
UINT32 ssd_c90lc_SetLock ( PSSD_CONFIG pSSDConfig,
                 UINT8 blkLockIndicator,
                 UINT32 blkLockState,
                 UINT32 password)
{
    register UINT32 returnCode;    /* return code */
    UINT32 address;                /* address of the block locking register */
    UINT32 mask;                   /* block locking field mask of an address space */
    UINT32 shift;                  /* bit shift value for the block locking field of an address space */

    if (blkLockIndicator > LOCK_HIGH)
    {
        returnCode = C90FL_ERROR_LOCK_INDICATOR;
        goto EXIT;
    }

    returnCode = C90FL_OK;

    /* assume blkLockIndicator == LOCK_SHADOW_PRIMARY */
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
    else if (blkLockIndicator != LOCK_SHADOW_PRIMARY)
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

    address += pSSDConfig->c90flRegBase;

    /* write password to block lock register if it's locked for register writes */
    if (!C90FL_REG_BIT_TEST (address, 0x80000000))
    {
        /* write user provided password to block lock register */
        C90FL_REG_WRITE (address, password);

        /* check if the block lock register is enabled for register writes after writing password */
        if (!C90FL_REG_BIT_TEST (address, 0x80000000))
        {
            returnCode = C90FL_ERROR_PASSWORD;
            goto EXIT;
        }
    }

    /* clear the block lock field */
    C90FL_REG_BIT_CLEAR (address, mask);

    /* set the new value to the block lock field */
    C90FL_REG_BIT_SET (address, (blkLockState << shift) & mask);

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

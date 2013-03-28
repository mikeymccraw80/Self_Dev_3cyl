/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : FlashArrayIntegrityCheck.c
*
* DESCRIPTION :  This function will will check the array integrity
*                                of the Flash
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

#include "ssd_types.h"
#include "ssd_c90lc.h"


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
 * FUNCTION      :  FlashArrayIntegrityCheck
 * DESCRIPTION   :  This function will will check the array integrity  of the Flash
 *
 * PARAMETERS    :
 *                 pSSDConfig - Flash driver configuration structure
 *                 lowEnabledBlocks - selected Low Address Space block(s)
 *                 midEnabledBlocks - selected Mid Address Space block(s)
 *                 highEnabledBlocks    - selected High Address Space  block(s)
 *                 addrSeq - to determine the address sequence to be
 *                  used during array integrity checks.
 *                 misrValue - contains the MISR values calculated  by the user.
 *                 CallBack  - Callback function pointer for timeout
 *                 checking.
 *
 * RETURN VALUES : C90FL_OK                                        - Array Integrity Check passes
 *                                   C90FL_ERROR_AIC_NO_BLOCK - No block enable for Array
 *                                    Integrity Check
 *                                   C90FL_ERROR_AIC_MISMATCH - Array Integrity Check fails
 *************************************************************************/

UINT32 ssd_c90lc_FlashArrayIntegrityCheck ( PSSD_CONFIG pSSDConfig,
                                  UINT32 lowEnabledBlocks,
                                  UINT32 midEnabledBlocks,
                                  UINT32 highEnabledBlocks,
                                  BOOL addrSeq,
                                  MISR misrValue,
                                  void (*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 c90flRegBase;            /* base address of C90FL registers */
    UINT32 LMSAddress;              /* address of C90FLLMS register */
    MISR misrCalcValue;             /* store contents of the hardware calculated MISR */
    UINT32 UT0Address;              /* Address of the UT0 register */
    UINT32 u32UT0tmp;               /* Temp var for UT0 register value  */

    c90flRegBase = pSSDConfig->c90flRegBase;
    LMSAddress = c90flRegBase + C90FL_LMS;
    UT0Address = c90flRegBase + C90FL_UT0;

    /* initialize returnCode */
    returnCode = C90FL_OK;

    /* mask off reserved bits for low address space */
    lowEnabledBlocks &= 0xFFFFFFFF >> (32 - pSSDConfig->lowBlockNum);

    /* mask off reserved bits for mid address space */
    lowEnabledBlocks |= (midEnabledBlocks & (0xFFFFFFFF >> (32 - pSSDConfig->midBlockNum))) << 16;

    /* mask off reserved bits for high address space */
    highEnabledBlocks &= 0xFFFFFFFF >> (32 - pSSDConfig->highBlockNum);

    if ( !(lowEnabledBlocks | highEnabledBlocks) )
    {
        /* no blocks to be selected for evaluation */
        returnCode = C90FL_ERROR_AIC_NO_BLOCK;
        goto EXIT;
    }

    /* write password to UT0 register to enable test mode */
    C90FL_REG_WRITE(c90flRegBase + C90FL_UT0,C90FL_TEST_ENABLE_PASSWORD);

    /* set UTO-UTE bit to enable User Test Mode */
    C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_UTE);

    /* set the block selection registers */
    C90FL_REG_WRITE (LMSAddress, lowEnabledBlocks);
    C90FL_REG_WRITE (c90flRegBase + C90FL_HBS, highEnabledBlocks);

    /* set the seed values of the MISR in UMx registers */
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM0, 0);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM1, 0);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM2, 0);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM3, 0);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM4, 0);

    /* set the Address sequence to be used */
    if( C90FL_LOG_SEQ == addrSeq)
    {
        /* the logical sequence is used */
        /* initiate the Array Integrity Check by wirting 1 to Ut0_AIE bit*/
        C90FL_REG_WRITE(UT0Address, (C90FL_UT0_UTE|C90FL_UT0_AIS|C90FL_UT0_AIE));
    }
    else
    {
        /* the default sequence is used */
        /* initiate the Array Integrity Check by writing 1 to Ut0_AIE bit*/
        C90FL_REG_WRITE(UT0Address, (C90FL_UT0_UTE|C90FL_UT0_AIE));
    }


    /* wait until UT0-AID is set */
    do
    {
        u32UT0tmp = C90FL_REG_READ (UT0Address);
        if (CallBack != NULL_CALLBACK)
        {
            CallBack();
        }
    }
    while ( !(u32UT0tmp & C90FL_UT0_AID) );

    misrCalcValue.W0 = C90FL_REG_READ(c90flRegBase + C90FL_UM0);
    misrCalcValue.W1 = C90FL_REG_READ(c90flRegBase + C90FL_UM1);
    misrCalcValue.W2 = C90FL_REG_READ(c90flRegBase + C90FL_UM2);
    misrCalcValue.W3 = C90FL_REG_READ(c90flRegBase + C90FL_UM3);
    misrCalcValue.W4 = C90FL_REG_READ(c90flRegBase + C90FL_UM4);

    if( (misrCalcValue.W0 != misrValue.W0) || (misrCalcValue.W1 != misrValue.W1)
          || (misrCalcValue.W2 != misrValue.W2) || (misrCalcValue.W3 != misrValue.W3)
          || (misrCalcValue.W4 != misrValue.W4) )
    {
        /* set the returned value to an error code */
        returnCode = C90FL_ERROR_AIC_MISMATCH;
    }

    /* clear UTO-AIE bit */
    C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_AIE);
    /* Clear the Address sequence bit used */
    if( C90FL_LOG_SEQ == addrSeq)
    {
        /* the logical sequence bit is cleared */
        C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_AIS);
    }
    else
    {
        /* the default sequence doen't need to be cleared */
    }

    /* clear UTO-UTE bit to disable User Test Mode */
    C90FL_REG_WRITE (UT0Address , 0x0);

EXIT:
    if (pSSDConfig->BDMEnable)
    {
        /* save the return code to R3 */
        /* For CodeWarrior */
        #if (CODE_WARRIOR == COMPILER_SELECT)
        //asm ( "mr   r3,returnCode" );
        #else
        /* For Diab */
        //write_r3(returnCode);
        #endif

        #ifdef VLE_ASM
        	asm ( "se_sc " );                /* generate system call interrupt */
        #else
        	asm ( "sc" );
        #endif
    }

    return returnCode;
}

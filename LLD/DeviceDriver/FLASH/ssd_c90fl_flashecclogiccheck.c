 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Standard Software Driver for C90fl                      *
 *                                                                       *
 * FILE NAME     :  FlashECCLogicCheck.c                                 *
 * FUNCTION      :  FlashECCLogicCheck                                   *
 * DESCRIPTION   :  This API will check the ECC logic of the Flash. The  *
 *                  API will simulate a single or double bit fault       *
 *                  depending on the user input. If the simulated ECC    *
 *                  error is not detected, then the error code           *
 *                  C90FL_ERROR_ECC_LOGIC is returned.                   *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 dataValue - The 64 bits of data for which the ECC     *
 *                  is calculated. The bits of dataValue are flipped     *
 *                  to generate single or double bit faults.             *
 *                 errBits - To select error bit positions               *
 *                  that should be generated.                            *
 * RETURN VALUES : C90FL_OK          - ECC Logic Check passes            *
 *                 C90FL_ERROR_ECC_LOGIC - ECC Logic Check fails         *
 *                 C90FL_ERROR_ECC_NO_BIT_SET - No error bits set        *
 * DATE          :  December 22, 2008                                    *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.0   2008.12.22         Arvind Awasthi      Initial Version
 0.0.1   2009.01.12         Arvind Awasthi      Check ECC logic even if no
                                                error bit is set.
0.4.4	  07.27.2010	  FPT Team 		      Finalize to this version												
 *************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"

#if (DIAB_COMPILER == COMPILER_SELECT)
asm void write_r3(register UINT32 value)
{
% reg value
  mr r3,value
}
#endif

UINT32 ssd_c90fl_FlashECCLogicCheck ( PSSD_CONFIG pSSDConfig,
                            UINT64 dataVal,
                            UINT64 errBits,
                            UINT32 eccValue)
{
    register UINT32 returnCode;     /* return code */
    UINT32 c90flRegBase;            /* base address of C90FL registers */
    UINT64 flipDataWord;  /* Contains the flipped the data word */
    UINT32 mainArraybase ; /* Main array base to be passed to the common function*/
    UINT32 dataWord1,dataWord2;     /* hold the data words used for ECC calculation */

    returnCode = C90FL_OK;
    /* split the 64 bit value into two 32 bit words */
    dataWord1 = dataVal;
    dataWord2 = (dataVal >> 32);

    /* Flip the bits of the data words to simulate single or double bit faults */
    flipDataWord = dataVal ^ errBits;

    /* check the ECC logic for Bank0*/
    c90flRegBase = pSSDConfig->c90flRegBase;
    mainArraybase = pSSDConfig->mainArrayBase;
    returnCode = CFlashECCLogicCheck(c90flRegBase,mainArraybase,eccValue,flipDataWord,errBits,dataWord1,dataWord2);

    /*check the ECC Logic for Bank1*/
    c90flRegBase = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET;
    mainArraybase = pSSDConfig->mainArrayBase + C90FL_MAS_STARTADDR;
    returnCode |= CFlashECCLogicCheck(c90flRegBase,mainArraybase,eccValue,flipDataWord,errBits,dataWord1,dataWord2);

EXIT:
    if (pSSDConfig->BDMEnable)
    {
        /* save the return code to R3 */
        /* For CodeWarrior */
        #if (CODE_WARRIOR == COMPILER_SELECT)
        asm ( "mr   r3,returnCode" );
        #else
        /* For Diab */
        write_r3(returnCode);
        #endif

        #ifdef VLE_ASM
            asm ( "nop" );
            asm ( "se_sc " );                  /* generate system call interrupt */
            asm ( "nop" );
        #else
            asm ( "nop" );
            asm ( "sc " );
            asm ( "nop" );
        #endif
    }

    return returnCode;
}

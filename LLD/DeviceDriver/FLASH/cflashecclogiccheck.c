 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Standard Software Driver for C90fl                      *
 *                                                                       *
 * FILE NAME     :  cFlashecclogiccheck.c                                *
 * FUNCTION      :  cFlashECCLogicCheck                                  *
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
 0.0.1   2009.01.08         Arvind Awasthi      Clear DSI in UT0Value.
 0.0.2   2009.01.12         Arvind Awasthi      Check ECC logic even if no
                                                error bit is set.
 0.4.4	 2010.07.27         FPT Team 		    Finalize to this version												
 *************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"


 UINT32 CFlashECCLogicCheck(UINT32 c90flRegBase,
                            UINT32 mainArraybase,
                            UINT32 eccValue,
                            UINT64 flipDataWord,
                            UINT64 errBits,
                            UINT32 dataWord1,
                            UINT32 dataWord2)
 {
    register UINT32 returnCode;     /* return code */
    UINT32 UT0Address;              /* address of C90FL UT0 register */
    UINT32 flipDataWord1,flipDataWord2; /* hold the incorrect data words used to simulate ECC errors */
    UINT32 UT0Value;
    UINT8  errorBitsSet;
    UINT8  i;
    UINT64 temp;

    /* initialize returnCode */
    returnCode = C90FL_OK;

    UT0Address = c90flRegBase + C90FL_UT0;

    /* write password to UT0 register to enable test mode */
    C90FL_REG_WRITE(UT0Address,C90FL_TEST_ENABLE_PASSWORD);
    /* set the SBCE bit to observe Single Bit Correction results in MCR[SBC] */
    C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_SBCE);

    /* split the 64 bit flipped data word value into two 32 bit words */
    flipDataWord1 = flipDataWord;
    flipDataWord2 = (flipDataWord >> 32);

    /* initiate the ECC Logic Check by wirting 1 to UT0_EIE bit*/
    C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_EIE);

    /* write the flipped data words and the calculated ecc bits */
    C90FL_REG_WRITE(c90flRegBase + C90FL_UT1,flipDataWord1);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UT2,flipDataWord2);

    /* to write the ECC bits to UT0-DSI bits without affecting the other bits */
    UT0Value = C90FL_REG_READ(c90flRegBase + C90FL_UT0);
    /* clear DSI if already set*/
    UT0Value = UT0Value & ~(0xFF<<16);
    UT0Value = UT0Value | (eccValue << 16);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UT0,UT0Value);

    /* Write double word address to receive the data inputted in above step into the ADR register */
    C90FL_REG_WRITE(c90flRegBase + C90FL_ADR,0x00+ 0x4020);

    /* read a flash location to simulate the ECC error */
    /* UT0Value is reused to hold the value read from the flash */
    flipDataWord1 = (UINT32)(*(VUINT32 *)(mainArraybase + 0x4020));
    flipDataWord2 = (UINT32)(*(VUINT32 *)(mainArraybase + 0x4024));

    /* set errBits to zero */
    errorBitsSet = C90FL_ECC_ERR_BIT_SET_ZERO;
    temp = errBits;
    /* to find if single or double bit fault should be simulated */
    for(i = 0; i < 64; i++)
    {
        if(temp & 0x01)
        {
            errorBitsSet++;
        }
        temp = temp >> 1;
    }

    /* Check if a double bit fault has occured */
    if(C90FL_REG_BIT_TEST(c90flRegBase + C90FL_MCR, C90FL_MCR_EER))
    {
       /* double bit fault detected */
       /* Write 1 to clear the MCR_EER bit of MCR */
       C90FLMCR_EER_CLEAR(c90flRegBase + C90FL_MCR, C90FL_MCR_EER);

       /* Reset the Address register */
       C90FL_REG_WRITE(c90flRegBase + C90FL_ADR,0x00000000);
       /* if no error bits were set, or a single bit was set, then a double bit fault should not occur
       ECC logic check failed */
       if(errorBitsSet < C90FL_ECC_ERR_BIT_SET_TWO)
       {
           returnCode = C90FL_ERROR_ECC_LOGIC;
       }
    }
    /* Check if a single bit fault has occcured and has been corrected */
    /* the data written in UT1-DAI is the flipped word flipDataWord1 and MCR-SBC bit is set */
    else if((flipDataWord1 == dataWord1) && (flipDataWord2 == dataWord2) && (C90FL_REG_BIT_TEST(c90flRegBase + C90FL_MCR, C90FL_MCR_SBC)))
    {
        /* the single bit fault has been corrected */

        /* Write 1 to clear the MCR_SBC bit of MCR */
        C90FLMCR_BIT_SET(c90flRegBase + C90FL_MCR, C90FL_MCR_SBC);

        /* if error bits set was not one, then a single bit fault should not occur
           ECC logic check fails */
        if(C90FL_ECC_ERR_BIT_SET_ONE != errorBitsSet)
        {
            returnCode = C90FL_ERROR_ECC_LOGIC;
        }
    }
    /* Single or Double bit faults have not occurred */
    else
    {
        /* if no error bits were set, then a single or double bit fault should not occur */
        if(C90FL_ECC_ERR_BIT_SET_ZERO != errorBitsSet)
        {
            returnCode = C90FL_ERROR_ECC_LOGIC;
        }
    }

    /* clear UTO-EIE bit */
    C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_EIE);
    /* clear UTO-SBCE bit */
    C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_SBCE);
     /* clear UTO-UTE bit to disable User Test Mode */
    C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_UTE);

    return returnCode;
}
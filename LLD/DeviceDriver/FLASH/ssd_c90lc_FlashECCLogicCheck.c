/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : flashecclogiccheck.c
*
* DESCRIPTION : This file contains flashecclogiccheck function implementation
*
* COPYRIGHT :(c) 2008, Freescale & STMicroelectronics
*
* VERSION   : EAR 0.2
* DATE      : 04.18.2008
* AUTHOR    : ...
*
* HISTORY :
* 2008.01.02    Sindhu_R01       Initial Version
* 2008.02.08    Sindhu_R01       Changed the function to accept as argument
*                                error mask value.
* 2008.02.13    Sindhu R01       Added code to generate system call interrupt
*                                for VLE mode
* 2008.04.18    Leonardo Colombo Changed header in agreement with JDP SW
*                                template
******************************************************************/
#include "ssd_types.h"
#include "ssd_c90lc.h"

/*************************************************************************
 *                                                                       *
 * FUNCTION      :  FlashECCLogicCheck                                   *
 * DESCRIPTION   :  This function will erase selected blks.              *
 *                  NOTE: The blks need to be unlocked first.            *
 *                  We don't unlock blks in erase function to be         *
 *                  consistent with customer usage, since otherwise it   *
 *                  violates the original intention of block protection. *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 dataValue - The 64 bits of data for which the ECC     *
 *                  is calculated. The bits of dataValue are flipped     *
 *                  to generate single or double bit faults.             *
 *                 errBits - To select error bit positions               *
 *                  that should be generated.                            *
 *                 eccValue - Correct ECC value of the input 64bit data
 * RETURN VALUES : C90FL_OK          - ECC Logic Check passes            *
 *                 C90FL_ERROR_ECC_LOGIC - ECC Logic Check fails         *
 *                                                                       *
 *************************************************************************/
UINT32 ssd_c90lc_FlashECCLogicCheck ( PSSD_CONFIG pSSDConfig,
                            UINT64 dataVal,
                            UINT64 errBits,
                            UINT32 eccValue)
{
    register UINT32 returnCode;     /* return code */
    UINT32 c90flRegBase;            /* base address of C90FL registers */
    UINT32 UT0Address;              /* address of C90FL UT0 register */
    UINT32 dataWord1,dataWord2;     /* hold the data words used for ECC calculation */
    UINT32 flipDataWord1,flipDataWord2;     /* hold the incorrect data words used to simulate ECC errors */
    UINT32 UT0Value;                /* content of C90FL UT0 register */
    UINT32 temp;
    UINT64 flipDataWord;            /* Contains the flipped the data word */
    UINT8  errorBitsSet;
    UINT8  i;
    UINT32 u32EccError;


    c90flRegBase = pSSDConfig->c90flRegBase;
    UT0Address = c90flRegBase + C90FL_UT0;

    /* initialize returnCode */
    returnCode = C90FL_OK;

    /* split the 64 bit value into two 32 bit words */
    dataWord1 = dataVal;
    dataWord2 = (dataVal >> 32);

    /* write password to UT0 register to enable test mode */
    C90FL_REG_WRITE(UT0Address,C90FL_TEST_ENABLE_PASSWORD);

    C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_SBCE);

    /* Flip the bits of the data words to simulate single or double bit faults */
    flipDataWord = dataVal ^ errBits;

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
    /* clear DSI bits if already set*/
    UT0Value = UT0Value & ~(0xFF<<16);
    UT0Value = UT0Value | (eccValue << 16);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UT0,UT0Value);

#if 0
    /* Write double word address to receive the data inputted in above step into the ADR register */
    C90FL_REG_WRITE(c90flRegBase + C90FL_ADR,pSSDConfig->mainArrayBase + 0x00020);

    /* read a flash location to simulate the ECC error */
    /* UT0Value is reused to hold the value read from the flash */
    flipDataWord1 = (UINT32)(*(VUINT32 *)(pSSDConfig->mainArrayBase + 0x00020));
    flipDataWord2 = (UINT32)(*(VUINT32 *)(pSSDConfig->mainArrayBase + 0x00024));
#endif

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

    /* initiate the ECC Logic check  by writing 1 to Ut0_AIE bit*/
    C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_AIE);

    /* wait until UT0-AID is set */
    while ( !(C90FL_REG_READ (UT0Address) & C90FL_UT0_AID) );

    /* Read ECC logic check results */
    flipDataWord1 = C90FL_REG_READ(c90flRegBase + C90FL_UM0);
    flipDataWord2 = C90FL_REG_READ(c90flRegBase + C90FL_UM1);
    u32EccError = C90FL_REG_READ(c90flRegBase + C90FL_UM4)&(0xFF00FF00);

    /* Check if a double bit fault has occured */
    if(((flipDataWord1 != dataWord1) || (flipDataWord2 != dataWord2)) && (u32EccError!=0x0))
    {
        /* double bit fault detected */
        /* if no error bits were set, or a single bit was set, then a double bit fault should not occur
                          ECC logic check failed */
        if(errorBitsSet < C90FL_ECC_ERR_BIT_SET_TWO)
        {
            returnCode = C90FL_ERROR_ECC_LOGIC;
        }
    }
    /* Check if a single bit fault has occcured and has been corrected */
    /* the data written in UT1-DAI is the flipped word flipDataWord1 and MCR-SBC bit is set */
    else if((flipDataWord1 == dataWord1) && (flipDataWord2 == dataWord2) && (u32EccError!=0x0))
    {
        /* the single bit fault has been corrected */
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

    /* clear UTO-AIE bit */
    C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_AIE);

    /* clear UTO-EIE bit */
    C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_EIE);

    /* clear UTO-SBCE bit */
    C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_SBCE);

    /* clear UTO-UTE bit to disable User Test Mode */
    C90FL_REG_WRITE (UT0Address , 0x0);

EXIT:
    if (pSSDConfig->BDMEnable)
    {
        #ifdef VLE_ASM
        	asm ( "se_sc " );                /* generate system call interrupt */
        #else
        	asm ( "sc" );
        #endif
    }

    return returnCode;
}

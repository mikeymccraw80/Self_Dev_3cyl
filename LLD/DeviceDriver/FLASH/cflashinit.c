 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
  *                                                                      *
  *               Common Standard Software Driver for C90fl              *
  *                                                                      *
  * FILE NAME     : cflashinit.c                                         *
  * FUNCTION      : CflashInit                                           *
  * DESCRIPTION   : This function will initialize the flash config       *
  *                 structure.                                           *                                             *
  * PARAMETERS    :                                                      *
  *                 pSSDConfig - Flash driver configuration structure    *
  *                                                                      *
  * RETURN        : C90FL_OK      - passes                               *
  * DATE          : September 11, 2008                                   *
  * AUTHOR        : Infosys Team                                         *
  * E-mail        : r56611@freescale.com                                 *
  *                                                                      *
  *************************************************************************/

/******************************* CHANGES *********************************
  0.0.0    09.11.2008         Arvind Awasthi      Initial Version
  0.4.4	   07.27.2010	      FPT Team 		      Finalize to this version
 *************************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90fl.h"


UINT32 CflashInit ( PSSD_CONFIG pSSDConfig )
{
    register UINT32 returnCode;     /* return code */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */
    UINT32 temp;                    /* temporary variable */
	
	UINT32 size = 0x300000;
	
    returnCode = C90FL_OK;
    MCRAddress = pSSDConfig->c90flRegBase + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);

    /* Check MCR-EER and MCR-RWE bits */
    returnCode = (MCRValue & (C90FL_MCR_EER|C90FL_MCR_RWE)) >> 14;
    if (returnCode)
    {
        /* Clear EER and RWE bits are set in MCR register */
        C90FL_REG_BIT_SET(MCRAddress,(C90FL_MCR_EER|C90FL_MCR_RWE));
    }

    returnCode = 0;
    pSSDConfig->midBlockNum = 0;
    pSSDConfig->highBlockNum = 0;

    /* Number of blocks in low address space and fill into SSD_CONFIG structure */
    temp = (MCRValue & C90FL_MCR_LAS) >> 20;

    /********************************************************************************
     *  Number of blocks in low address space and fill into SSD_CONFIG structure
     *  LAS = 0: lowBlockNum = 1;
     *  LAS = 1: lowBlockNum = 2;
     *  LAS = 2: lowBlockNum = 8;
     *  LAS = 3: lowBlockNum = Reserved;
     *  LAS = 4: lowBlockNum = 10;
     *  LAS = 5: lowBlockNum = Reserved;
     *  LAS = 6: lowBlockNum = 6;
     *  LAS = 7: lowBlockNum = Reserved;
     *******************************************************************************/

     if (temp < 2)
     {
         pSSDConfig->lowBlockNum = temp + 1;
     }
     else if (2 == temp)
     {
         pSSDConfig->lowBlockNum = 8;
     }
     else if (4 == temp)
     {
         pSSDConfig->lowBlockNum = 10;
     }
     else if (6 == temp)
     {
         pSSDConfig->lowBlockNum = 6;
     }
     else
     {
     	/*do nothing*/
     }

     /* Find main array size and fill into SSD_CONFIG structure */
     temp = (MCRValue & C90FL_MCR_SIZE) >> 24;

     /********************************************************************************
      *  Get Main array size and fill into SSD_CONFIG structure
      *  Size = 0: Main Array Size = 128KB;
      *  Size = 1: Main Array Size = 256KB;
      *  Size = 2: Main Array Size = 512KB;
      *  Size = 3: Main Array Size = 1MB;
      *  Size = 4: Main Array Size = 1.5MB;
      *  Size = 5: Main Array Size = 2MB;
      *  Size = 6: Main Array Size = Reserved;
      *  Size = 7: Main Array Size = 0x300000;
     *******************************************************************************/
    switch(temp)
    {
         case 0:
            size = 0x20000;
            break;
         case 1:
            size = 0x40000;
            break;
         case 2:
            size = 0x80000;
            break;
         case 3:
            size = 0x100000;
            break;
         case 4:
            size = 0x180000;
            break;
         case 5:
            size = 0x200000;
            break;
    }

    /*update Main Array size in SSD config*/
    pSSDConfig->mainArraySize = size;

    /********************************************************************************
     *  Number of blocks in middle address space and fill into SSD_CONFIG structure
     *  MAS = 0: midBlockNum = 2;
     *  MAS = 1: midBlockNum = 1;
     *******************************************************************************/

    /* Determine the number of blocks in middle address space and fill into SSD_CONFIG structure */
    if ( MCRValue & C90FL_MCR_MAS)
    {
       pSSDConfig->midBlockNum = 1;
    }
    else
    {
       pSSDConfig->midBlockNum = 2;
    }


    /* Determine the number of blocks in high address space and fill into SSD_CONFIG structure */
    if ( size > 0x00080000 )
    {
        /* (mainArraySize - 512K) / 256K */
        pSSDConfig->highBlockNum = (size - 0x00080000) >> 18;
    }

    return returnCode;
}


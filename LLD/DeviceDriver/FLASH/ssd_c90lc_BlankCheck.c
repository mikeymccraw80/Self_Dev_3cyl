/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : blankcheck.c
*
* DESCRIPTION : This file contains BlankCheck function implementation
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
******************************************************************/


#include    "ssd_types.h"
#include    "ssd_c90lc.h"
#include    "ssd_c90lc_internal.h"

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

/************************************************************************
*                                                                       *
* FUNCTION      : BlankCheck                                            *
* DESCRIPTION   : This function will verify a specified flash range     *
*                 to be erased.                                         *
* PARAMETERS    :                                                       *
*                 pSSDConfig - Flash driver configuration structure     *
*                 dest       - start flash addr to be programmed        *
*                 size       - number of bytes to be programmed         *
*                              (need to be dword-aligned)               *
*                 pFailAddress - pointer to first failing address       *
*                 pFailData    - pointer to first failing actual data   *
*                 CallBack     - Callback function pointer for timeout  *
*                                checking.                              *
* RETURN        : C90FL_OK           - passes                           *
*                 C90FL_ERROR_VERIFY - failed verify                    *
*                 C90FL_ERROR_RANGE  - Invalid addr range               *
*                 C90FL_ERROR_ALIGNMENT - Invalid alignment             *
*                                                                       *
*************************************************************************/
UINT32 ssd_c90lc_BlankCheck ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailAddress,
                    UINT64 *pFailData,
                    void (*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 destIndex;               /* destination address index */
    UINT32 shadowRowEnd;            /* shadow row base + shadow size */
    UINT32 mainArrayEnd;            /* main array base + main array size */
    UINT32 temp;                    /* dest + size, or CallBack step */

    returnCode = C90FL_OK;

    /* Check alignments */
    if ( ((dest | size) % C90FL_DWORD_SIZE) != 0 )
    {
        returnCode = C90FL_ERROR_ALIGNMENT;
        goto EXIT;
    }

    /* The flash range should fall within either shadow row or main array */
    shadowRowEnd = pSSDConfig->shadowRowBase + pSSDConfig->shadowRowSize;
    mainArrayEnd = pSSDConfig->mainArrayBase + pSSDConfig->mainArraySize;
    temp = dest + size;

    if ( !((dest >= pSSDConfig->shadowRowBase) && (dest < shadowRowEnd) &&
           (size <= pSSDConfig->shadowRowSize) && (temp <= shadowRowEnd))
         &&
         !((dest >= pSSDConfig->mainArrayBase) && (dest < mainArrayEnd) &&
           (size <= pSSDConfig->mainArraySize) && (temp <= mainArrayEnd)) )
    {
        returnCode = C90FL_ERROR_RANGE;
        goto EXIT;
    }

    temp = 0;

    /* Blank check by double word */
    for (destIndex = 0; destIndex < (size / C90FL_DWORD_SIZE); destIndex++)
    {
        if ( (*(UINT64 *)dest) != 0xFFFFFFFFFFFFFFFF )
        {
            returnCode = C90FL_ERROR_NOT_BLANK;
            *pFailAddress = dest;
            *pFailData = *(UINT64 *)dest;
            break;
        }

        dest += C90FL_DWORD_SIZE;

        /* CallBack */
        if ( (CallBack != NULL_CALLBACK) && (destIndex == temp) )
        {
            CallBack();
            temp += CALLBACK_BC;
        }
    }

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

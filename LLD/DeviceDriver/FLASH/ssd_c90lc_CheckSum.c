/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : checksum.c
*
* DESCRIPTION : This file contains CheckSum function implementation
*
* COPYRIGHT :(c) 2008, Freescale & STMicroelectronics
*
* VERSION   : EAR 0.2
* DATE      : 04.18.2008
* AUTHOR    : ...
*
* HISTORY :
* 2007.12.17    Arvind Awasthi   Initial Version
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

/*************************************************************************
 *                                                                       *
 * FUNCTION      :  CheckSum                                             *
 * DESCRIPTION   :  This function will perform a 32-bit sum over the     *
 *                   specified flash memory range without carry, which   *
 *                   provides a rapid method for checking data integrity *
 * PARAMETERS    :                                                       *
 *                  pSSDConfig - Flash driver configuration structure    *
 *                  dest - Variable to store address from where checksum *
 *                         has to be calculated                          *
 *                  size - Variable to store size for which checksum has *
 *                         to be calculated                              *
 *                  psum - pointer to store checksum                     *
 *                  *CallBack - function pointer to Callback function    *
 * RETURN        : C90FL_OK - passes                                     *
 *                 C90FL_ERROR_ALIGNMENT - Alignment Error               *
 *                 C90FL_ERROR_RANGE - Range Error                       *
 *                                                                       *
 *************************************************************************/
UINT32 ssd_c90lc_CheckSum ( PSSD_CONFIG pSSDConfig,
                  UINT32 dest,
                  UINT32 size,
                  UINT32 *pSum,
                  void(*CallBack)(void))
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

    /* The flash range falls within either main array or shadow row */
    shadowRowEnd = pSSDConfig->shadowRowBase + pSSDConfig->shadowRowSize;
    mainArrayEnd = pSSDConfig->mainArrayBase + pSSDConfig->mainArraySize;
    temp = dest + size;

    /* The program range should fall within shadow row or main array */
    if ( !((dest >= pSSDConfig->shadowRowBase) && (dest < shadowRowEnd) &&
           (size <= pSSDConfig->shadowRowSize) && (temp <= shadowRowEnd))
         &&
         !((dest >= pSSDConfig->mainArrayBase) && (dest <  mainArrayEnd) &&
           (size <= pSSDConfig->mainArraySize) && (temp <= mainArrayEnd)) )

    {
        returnCode = C90FL_ERROR_RANGE;
        goto EXIT;
    }

    *pSum = 0;
    temp = 0;

    /* word by word checksum */
    for (destIndex = 0; destIndex < (size / C90FL_WORD_SIZE); destIndex++)
    {
        *pSum += *(UINT32 *)dest;

        dest += C90FL_WORD_SIZE;

        /* CallBack */
        if( (CallBack != NULL_CALLBACK) && (destIndex == temp) )
        {
            CallBack();
            temp += CALLBACK_CS;
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

//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_TLE4471_reset_volt_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Tue Oct 23 19:48:48 2012 %
//
// %derived_by:       tzwfxv %
//
// %date_modified:         %
//
// %version:         2 %
//
//=============================================================================
#if 0
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_discrete.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/


/*****************************************************************************
 * Function Prototype: void mg_TLE4471_reset_volt_Test(void)
 *
 * Description: This test perform Frequency Input measurement of the EXTCLK
 *              input from LMC555 circuit
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_TLE4471_reset_volt_test(void)
{
    mg_HAL_Discrete_Set_TACH(true);
}

#endif

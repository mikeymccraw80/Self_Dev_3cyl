//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_main.c %
//
// created_by:       lz37cb %
//
// date_created:     Wed Jun 11 09:54:59 2008 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:                  %
//
// %version:         11 %
//
//=============================================================================


#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_main.h"
#include "mcamos.h"
#include "mg_config.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_discrete.h"
#include "mg_output_cycling_EMC.h"
#include "mg_output_cycling_validation.h"
#include "hal_pulse.h"

/* macro define */
#define MAX_NUMBER_OF_TESTS mg_Get_Test_Max_Number()

/* variable define */
MG_MODE_T Mg_Mode = UNDEFINED_MODE;

/* function declare */
uint8_t mg_Get_Test_Max_Number(void);
void mg_Execute_Test(uint8_t test_id);


/*=============================================================================
 * clear_mailbox
 * @func  Prepare mailbox for use
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
static void clear_mailbox(void)
{
   uint8_t *mbptr;
   MG_MAILBOX_IN(testid) = MG_FINISHED;
   mbptr = (uint8_t *)INBOX_PTR;
   mbptr++;
   for (; (uint32_t)mbptr < END_OF_MAILBOX; mbptr++) 
   {
      *mbptr = 0;
   }
}

/*=============================================================================
 * Initialize_Testability
 * @func  Do all initialization here for testability
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
static void Initialize_Testability(void)
{
    uint8_t  idx;

    mg_HAL_SWT_Enable_WatchDog( false );
    clear_mailbox();

    MG_SIU_GPIO_DISCRETE_Initialize_Device_Override();

    // mg_HAL_Discrete_Reconfigure_CAL();

    mg_HAL_Internal_Device_Init();

    mg_HAL_External_Device_Init();
    
    // mg_HAL_SPI_Timer_Enable( false );


    for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++)
    {
        mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, false);
    }
    if (!mg_HAL_Discrete_Get_ELOAD1())
    {
        Mg_Mode = MG_FUNCTION_TEST;
    }
    else
    {
        if (!mg_HAL_Discrete_Get_ELOAD2())
        {
            Mg_Mode = MG_OUTPUT_CYCLING_VALIDATION;
        }
        else
        {
            Mg_Mode = MG_OUTPUT_CYCLING_EMC;
        }
    }
    Mg_Mode = MG_FUNCTION_TEST;
    if ( (Mg_Mode == MG_FUNCTION_TEST) || 
        (Mg_Mode == MG_OUTPUT_CYCLING_EMC)||
        (Mg_Mode == MG_OUTPUT_CYCLING_VALIDATION)      ) 
    {
        MCAMOS_enable = true;
    }
    Enable_Interrupts();
}

/*=============================================================================
 * mg_main
 * @func  main function of testability, it's the entry of testability
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_main(void)
{
    uint8_t volatile  testIdx;
    Mg_Mode = MG_FUNCTION_TEST;


    Initialize_Testability();
    mg_HAL_Service_WatchDog();
    // mg_HAL_Disable_CAN_10ms_Task_Timer();
    
    /* Detect IGN OFF by TOD function */
#ifdef __MG_TLE4471_USED
    mg_HAL_Discrete_Set_TODO(false);
#endif

   // stay in cycling until a reset occurs or IGN OFF
    while(1)
    {
        mg_HAL_Service_WatchDog();
        switch(Mg_Mode)
        {
            case MG_FUNCTION_TEST:
            {
                testIdx = MG_MAILBOX_IN(testid);
                /* if there is a pending test in mailbox */
                if((testIdx != MG_FINISHED) && (MCAMOS_Get_Message_Size() == 0))
                {
                    /* check if the test is valid */
                    if(testIdx < MAX_NUMBER_OF_TESTS)
                    {
                        mg_Execute_Test(testIdx);
                    }
                    /* Test is finished. Overwrite te mailbox with MG_FINISHED */
                    MG_MAILBOX_IN(testid) = MG_FINISHED;
                }
                break;
            }
            case MG_OUTPUT_CYCLING_EMC:
            {
                mg_output_cycling_EMC();
                break;
            }
            case MG_OUTPUT_CYCLING_VALIDATION:
            {
                mg_output_cycling_validation();
                break;
            }
            default:
                break;
        }
        mg_HAL_Service_WatchDog();
    }
}

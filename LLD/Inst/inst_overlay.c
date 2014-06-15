
/*===========================================================================*\
 *   Includes
\*===========================================================================*/
#include "inst_config.h"
#include "inst_overlay.h"
#include "inst_overlay_nvm.h"
#include "hw_sprs_cu.h"
#include "dd_siu_interface.h"



typedef struct
{
   bitfield8_t Active_CAL_Page : 1;
   bitfield8_t RAM_Present     : 1;
   bitfield8_t NVM_Failure     : 1;

}INST_Overlay_Data_T;

typedef enum {
	CCP_ACTIVE_CAL_PAGE_REFERENCE,
	CCP_ACTIVE_CAL_PAGE_WORKING
} CCP_Cal_Page_T;

//===========================================================================
// Local Variable declarations
//===========================================================================
static INST_Overlay_Data_T INST_Overlay_Data;
static CCP_Cal_Page_T      CCP_Active_CAL_Page; //indicate current cal page

//===========================================================================
// INST_Get_NVM_Failure
//===========================================================================
bool INST_Get_NVM_Failure( void )
{
   return INST_Overlay_Data.NVM_Failure;
}

//===========================================================================
// INST_Is_RAM_Present
//===========================================================================
bool INST_Is_RAM_Present( void )
{
   return INST_Overlay_Data.RAM_Present;
}

//===========================================================================
// INST_Set_Active_Calibration_Page
//===========================================================================
void INST_Set_Active_Calibration_Page( INST_Calibration_Page_T in_page )
{
   //=======================================================================
   // Make sure external instrumentation RAM is present
   //=======================================================================
   if( INST_Overlay_Data.RAM_Present )
   {
      if( in_page == INST_CALIBRATION_PAGE_REFERENCE )
      {
         INST_Overlay_Data.Active_CAL_Page = INST_CALIBRATION_PAGE_REFERENCE;
         CCP_Active_CAL_Page = CCP_ACTIVE_CAL_PAGE_REFERENCE;

         //=======================================================================
         // Set internal and external CAL presence patterns to CAL_INST_CALIBRATION_PAGE_REFERENCE_PATTERN
         //=======================================================================
         INST_Internal_Cal_Page_Pattern_NVM = INST_CAL_REFERENCE_PAGE_PATTERN;
      }
      else
      {
         INST_Overlay_Data.Active_CAL_Page = INST_CALIBRATION_PAGE_WORKING;
         CCP_Active_CAL_Page = CCP_ACTIVE_CAL_PAGE_WORKING;

         //=======================================================================
         // Set internal and external CAL presence patterns to CAL_INST_CALIBRATION_PAGE_WORKING_PATTERN
         //=======================================================================
         INST_Internal_Cal_Page_Pattern_NVM = INST_CAL_WORKING_PAGE_PATTERN;
      }
   }
   else // external RAM not present */
   {
      INST_Overlay_Data.Active_CAL_Page = INST_CALIBRATION_PAGE_REFERENCE;
      CCP_Active_CAL_Page = CCP_ACTIVE_CAL_PAGE_REFERENCE;
      INST_Internal_Cal_Page_Pattern_NVM = INST_CAL_REFERENCE_PAGE_PATTERN;
   }

   INST_Overlay_Set_Page(INST_Overlay_Data.Active_CAL_Page);

}

//===========================================================================
// INST_Get_Active_Cal_Page
//===========================================================================
bool INST_Is_WorkingPage( void )
{
   return ( INST_Overlay_Data.Active_CAL_Page == INST_CALIBRATION_PAGE_WORKING);
}


//===========================================================================
// INST_Get_Address_Active_Cal_Page
//===========================================================================
uint32_t INST_Get_Address_Active_Cal_Page( void )
{
   uint32_t return_value;

   if( INST_CALIBRATION_PAGE_REFERENCE == INST_Overlay_Data.Active_CAL_Page )
   {
      return_value = INST_REFERENCE_PAGE_START_ADDRESS;
   }
   else
   {
      if(CPU_LCI == CPU_Info)
      {
         return_value = INST_WORKING_PAGE_RAM_START_ADDRESS;
      }
      else if (CPU_VERTICAL == CPU_Info) 
      {
         return_value = VERTICAL_WORKING_PAGE_RAM_START_ADDRESS;
      }
      else
      {
         return_value = INST_REFERENCE_PAGE_START_ADDRESS;
      }
   }

   return return_value;
}

//===========================================================================
// INST_Initialize_Calibration_Pages
//===========================================================================
void INST_Initialize_Calibration_Pages( void )
{
   INST_Overlay_Data.NVM_Failure = false;

    //=======================================================================
    // Determine if external instrumentation RAM exists
    //=======================================================================
   INST_Overlay_Data.RAM_Present = (((CPU_LCI == CPU_Info)||(CPU_VERTICAL == CPU_Info))?true:false);

   //====================================================================
   // Determine if the working page was active at powerdown and if the
   // conditions are valid to make it active at powerup
   //====================================================================
   if(  INST_CAL_WORKING_PAGE_PATTERN == INST_Internal_Cal_Page_Pattern_NVM )
   {
      INST_Overlay_Data.Active_CAL_Page = INST_CALIBRATION_PAGE_WORKING;
      CCP_Active_CAL_Page = CCP_ACTIVE_CAL_PAGE_WORKING;
   }
   else if( INST_CAL_REFERENCE_PAGE_PATTERN == INST_Internal_Cal_Page_Pattern_NVM )
   {
      INST_Overlay_Data.Active_CAL_Page = INST_CALIBRATION_PAGE_REFERENCE;
      CCP_Active_CAL_Page = CCP_ACTIVE_CAL_PAGE_REFERENCE;
   }
   else
   {
      //====================================================================
      // Calibration NVM Failure.  Default to reference page.
      //====================================================================
      INST_Overlay_Data.Active_CAL_Page = INST_CALIBRATION_PAGE_REFERENCE;
      CCP_Active_CAL_Page = CCP_ACTIVE_CAL_PAGE_REFERENCE;
      INST_Overlay_Data.NVM_Failure     = true;
   }

   INST_Set_Active_Calibration_Page( INST_Overlay_Data.Active_CAL_Page );
}


//===========================================================================
// INST_Overlay_Set_Page
//===========================================================================
void INST_Overlay_Set_Page( INST_Calibration_Page_T in_page )
{
   interrupt_state_t context;
   uint8_t           idx;
   if(CPU_LCI == CPU_Info)
   {
      if( in_page == INST_CALIBRATION_PAGE_WORKING )
      {
         if(!Get_Working_Page_RAM_Validation())
         {
            INST_Restore_Working_Page_Again();
         }
      }
      context = Enter_Critical_Section();
      for(idx=0; idx<2; idx++)
      {
         if(INST_MMU_MAS_1_INITIAL[in_page][idx].F.VALID == 1)
         {
            STORE_SPR_VALUE_VAR(MMU_MAS0_SPR, INST_MMU_MAS_0_INITIAL[in_page][idx].U32);
            STORE_SPR_VALUE_VAR(MMU_MAS1_SPR, INST_MMU_MAS_1_INITIAL[in_page][idx].U32);
            STORE_SPR_VALUE_VAR(MMU_MAS2_SPR, INST_MMU_MAS_2_INITIAL[in_page][idx].U32);
            STORE_SPR_VALUE_VAR(MMU_MAS3_SPR, INST_MMU_MAS_3_INITIAL[in_page][idx].U32);
            TLBWE();
         }
      }
      Leave_Critical_Section(context);
   }
   else if (CPU_VERTICAL == CPU_Info) 
   {
      if( in_page == INST_CALIBRATION_PAGE_WORKING )
      {
         if(!Get_Working_Page_RAM_Validation())
         {
            INST_Restore_Working_Page_Again();
         }
      }
      context = Enter_Critical_Section();
      for(idx=0; idx<2; idx++)
      {
         if(INST_MMU_MAS_1_INITIAL[in_page][idx].F.VALID == 1)
         {
            STORE_SPR_VALUE_VAR(MMU_MAS0_SPR, VERTICAL_MMU_MAS_0_INITIAL[in_page][idx].U32);
            STORE_SPR_VALUE_VAR(MMU_MAS1_SPR, VERTICAL_MMU_MAS_1_INITIAL[in_page][idx].U32);
            STORE_SPR_VALUE_VAR(MMU_MAS2_SPR, VERTICAL_MMU_MAS_2_INITIAL[in_page][idx].U32);
            STORE_SPR_VALUE_VAR(MMU_MAS3_SPR, VERTICAL_MMU_MAS_3_INITIAL[in_page][idx].U32);
            TLBWE();
         }
      }
      Leave_Critical_Section(context);
   }
   else
   {
      context = Enter_Critical_Section();
      // Map MMU to FLASH(reference page)
      for(idx=0; idx<2; idx++)
      {
         if(INST_MMU_MAS_1_INITIAL[INST_CALIBRATION_PAGE_REFERENCE][idx].F.VALID == 1)
         {
            STORE_SPR_VALUE_VAR(MMU_MAS0_SPR, INST_MMU_MAS_0_INITIAL[INST_CALIBRATION_PAGE_REFERENCE][idx].U32);
            STORE_SPR_VALUE_VAR(MMU_MAS1_SPR, INST_MMU_MAS_1_INITIAL[INST_CALIBRATION_PAGE_REFERENCE][idx].U32);
            STORE_SPR_VALUE_VAR(MMU_MAS2_SPR, INST_MMU_MAS_2_INITIAL[INST_CALIBRATION_PAGE_REFERENCE][idx].U32);
            STORE_SPR_VALUE_VAR(MMU_MAS3_SPR, INST_MMU_MAS_3_INITIAL[INST_CALIBRATION_PAGE_REFERENCE][idx].U32);
            TLBWE();
         }
      }
      Leave_Critical_Section(context);
   }
}

/*=============================================================================
 * VERTICAL_Config_MMU
 * @func  
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
void VERTICAL_Config_MMU(void)
{
   interrupt_state_t context;
   context = Enter_Critical_Section();
   if(VERTICAL_EXTERNAL_RAM_MMU_MAS_1_INITIAL.F.VALID == 1)
   {
      STORE_SPR_VALUE_VAR(MMU_MAS0_SPR, VERTICAL_EXTERNAL_RAM_MMU_MAS_0_INITIAL.U32);
      STORE_SPR_VALUE_VAR(MMU_MAS1_SPR, VERTICAL_EXTERNAL_RAM_MMU_MAS_1_INITIAL.U32);
      STORE_SPR_VALUE_VAR(MMU_MAS2_SPR, VERTICAL_EXTERNAL_RAM_MMU_MAS_2_INITIAL.U32);
      STORE_SPR_VALUE_VAR(MMU_MAS3_SPR, VERTICAL_EXTERNAL_RAM_MMU_MAS_3_INITIAL.U32);
      TLBWE();
   }
   Leave_Critical_Section(context);
}


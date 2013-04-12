#ifndef INST_OVERLAY_H
#define INST_OVERLAY_H

#include "reuse.h"

//===========================================================================
// Working Page/Reference Page code
//===========================================================================
typedef enum
{
   INST_CALIBRATION_PAGE_REFERENCE,
   INST_CALIBRATION_PAGE_WORKING
}  INST_Calibration_Page_T;


//===========================================================================
// Global Variable declarations
//===========================================================================


//===========================================================================
// INST_Is_RAM_Present
//
// @func    Returns instrumentation RAM presence
//
// @parm    none
//
// @rdesc   true if external instrumentation RAM is present
//
// @end
//===========================================================================
bool INST_Is_RAM_Present(void);

//===========================================================================
// INST_Get_NVM_Failure
//
// @func    Retrieve indication of a calibration data NVM failure
//
// @parm    none
//
// @rdesc   true if an NVM failure has occurred
//
// @end
//===========================================================================
bool INST_Get_NVM_Failure( void );

//===========================================================================
// INST_Set_Active_Calibration_Page
//
// @func Sets the calibration memory to the selected page
//
// @parm INST_Calibration_Page_T | in_page | Desired page to make active
//
// @rdesc   none
//
// @end
//===========================================================================
void INST_Set_Active_Calibration_Page( INST_Calibration_Page_T in_page );

//===========================================================================
// INST_Get_Active_Cal_Page
//
// @func Returns the starting address of the active calibration page
//
// @parm none
//
// @rdesc Starting address of the requested page
//
// @end
//===========================================================================
uint32_t INST_Get_Address_Active_Cal_Page( void );

//===========================================================================
// INST_Is_WorkingPage
//
// @func Returns if the active page is working page
//
// @parm none
//
// @rdesc Starting address of the requested page
//
// @end
//===========================================================================
bool INST_Is_WorkingPage( void );

//===========================================================================
// INST_Initialize_Calibration_Pages
//
// @func Initializes instrumenation memory and sets the active page dependent
//       upon powerdown status and application routine.  Must be called
//       before other instrumentation functions which uses the calibration
//       pages.
//
// @parm    none
//
// @rdesc   none
//
// @end
//===========================================================================
void INST_Initialize_Calibration_Pages( void );

//===========================================================================
// VERTICAL_Config_MMU
//
// @func 
//
// @parm    none
//
// @rdesc   none
//
// @end
//===========================================================================
void VERTICAL_Config_MMU(void);

//===========================================================================
// Required Configured Functions
//===========================================================================

//===========================================================================
// INST_Overlay_Set_Page
//
// @func Sets the appropriate overlay memory aread
//
// @parm    none
//
// @rdesc   none
//
// @end
//===========================================================================
void INST_Overlay_Set_Page( INST_Calibration_Page_T in_page );


#endif // INST_OVERLAY_H

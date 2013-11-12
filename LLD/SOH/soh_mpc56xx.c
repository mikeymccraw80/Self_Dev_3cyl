/*===========================================================================*\
 * FILE: soh_mpc56xx.c
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh_mpc56xx.c~1:csrc:ctc_pt3#1 %
 * %version: 1 %
 * %derived_by:  rz65p6 %
 * %date_modified:  %
 * $SOURCE: $
 * $REVISION: $
 * $AUTHOR: $
 *---------------------------------------------------------------------------
 *
 * DESCRIPTION:
 *   ETC SOH building block software.
 *   (for Infineon TC1762, TC1765, TC1766, TC1775, TC1792, TC1796.)
 *   Used in conjunction with ASIC (VSEP, MIO) with state-of-health (SOH) logic.
 *
 *   This file contains all the microprocessor specific tests.
 *   Comment out #define SOH_STMTEST in file hal_soh.h if STM test is not 
 *   applicable.
 *
 * ABBREVIATIONS:
 *   Documented in the design and requirement documents.
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *     SDD_10012894_002_xxx.doc
 *
 *   Requirements Document(s):
 *     REQ_10012894_002_xxx.doc
 *
 *   Applicable Standards (in order of precedence: highest first):
 *     SW REF 264.15D "Delphi C Coding Standards" [23-Dec-2001]
 *
 * DEVIATIONS FROM STANDARDS:
 *   None.
 *
 \*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
 \*===========================================================================*/

/*===========================================================================*\
 * Other Header Files
 \*===========================================================================*/
#include "dd_dma.h"
//#include "dd_dma_common.h"
#include "dd_mios.h"
#include "dd_swt.h"
#include "soh_mpc56xx.h"


#define SWT_SERVICE_KEY_A        (0xA602UL)
#define SWT_SERVICE_KEY_B        (0xB480UL)
 //SKn+1 = (17*SKn+3) mod 2^16	is the formula used
#define SWT_Get_PseudoRandom_Key(key)  (((17UL*(key))+3UL) % 0x00010000UL)


 // #define SOH_DMA_External_REF_CONFIGURATION \
       // ( DMA_Set_Bandwidth_Control( 0, DMA_BANDWIDTH_CONTROL_NO_ENGINE_STALL ) | \
         // DMA_Set_Minor_Link_Enable( 0, false                                 ) | \
         // DMA_Set_Major_Link_Enable( 0, false                                 ) | \
                      // DMA_Set_Mode( 0, DMA_MODE_HARDWARE                     ) | \
     // DMA_Set_Scatter_Gather_Enable( 0, false                                 ) | \
                   // DMA_Set_Channel( 0, DMA_CHANNEL_MIOS_EMIOSFLAG_4          ) |\
            // DMA_Set_Group_Priority( 0, DMA_GROUP_PRIORITY_0                  ) | \
          // DMA_Set_Channel_Priority( 0, DMA_CHANNEL_PRIORITY_0                ) )


 uint32_t SOH_DMA_External_Ref_Time[SOH_EXTERNAL_REF_TIME_DMA_BUFFER_SIZE];

// const MPC55xx_DMA_Initialization_Parameters_T SOH_DMA_Para_ETERNAL_REF =
// {
    // (uint32_t) &MIOS.CH[4].CADR,                  // uint32_t      source_address;                              @field address of the source (read)
    // (uint32_t) SOH_DMA_External_Ref_Time,         // uint32_t      destination_address;                         @field address of the destination (write)
    // 0,                              // bitfield16_t  source_circular_buffer_length      :  BIT_5; @field
    // DMA_SIZE_32_BIT,                // bitfield16_t  source_size                        :  BIT_3; @field
    // 0,                              // bitfield16_t  destination_circular_buffer_length :  BIT_5; @field
    // DMA_SIZE_32_BIT,                // bitfield16_t  destination_size                   :  BIT_3; @field
    // 0,                              // uint16_t      source_offset;                               @field
    // 4                               // uint16_t      destination_offset;                          @field
// } ; 

/*===========================================================================*\
 * Local Preprocessor #define Constants
 \*===========================================================================*/



/*===========================================================================*\
 * FUNCTION: Initialize_SOH_HardwareRegister
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function is a child routine of the ETC SOH initialization & error
 * recovery.
 *
 * The function initializes and pre-fill microprocessor specific ETC SOH
 * register
 *
 * The function is called by SOH_ETC_Initialize() and EtcSohRecovery().
 *
 \*===========================================================================*/
void Initialize_SOH_HardwareRegister(void)
{
}

/*=============================================================================
 * SOH_Start_DMA_For_External_Ref
 * @func This function trigger DMA smaple of emios input capture value 
 * @parm  
 * @rdesc  
 *===========================================================================*/
void SOH_Start_DMA_For_External_Ref(void)
{
	DMA_Enable_Request(DMA_CHANNEL_MIOS_EMIOSFLAG_4);
}

/*=============================================================================
 * SOH_Enter_Critical_Section
 * @func  This function create a critical section by disabling DMA
 * @parm  
 * @rdesc  
 *===========================================================================*/
void SOH_Enter_Critical_Section(void)
{
	DMA_Clear_Request(DMA_CHANNEL_MIOS_EMIOSFLAG_4);
}

/*=============================================================================
 * SOH_Leave_Critical_Section
 * @func  This function create a critical section by disabling DMA
 * @parm  
 * @rdesc  
 *===========================================================================*/
void SOH_Leave_Critical_Section(void)
{
	DMA_Enable_Request(DMA_CHANNEL_MIOS_EMIOSFLAG_4);
}

/*=============================================================================
 * SOH_Service_Watchdog
 * @func feed key A to watchdog when even loop, and feed key B 
 *       to watchdog in odd loop 
 * @parm  iseven - odd/even loop identifer
 * @rdesc  none
 *===========================================================================*/
void SOH_Service_Watchdog(bool iseven)
{
	uint32_t SWT_KEY_Val;
	uint32_t SWT_SR_Val1;
	uint32_t SWT_SR_Val2;

	//check for fixed or random service mode
	if (SWT.SWT_MCR.F.KEY == SWT_KEYED_SERVICE_MODE) {
		// Read Key Value
		SWT_KEY_Val = SWT.SWT_SK.U32;

		// Generate Keys
		SWT_SR_Val1 = SWT_Get_PseudoRandom_Key(SWT_KEY_Val);
		SWT_SR_Val2 = SWT_Get_PseudoRandom_Key(SWT_SR_Val1);

		// Service Watchdog
		SWT.SWT_SR.U32 = SWT_SR_Val1;
		SWT.SWT_SR.U32 = SWT_SR_Val2;
	} else {
		if (iseven) {
			SWT.SWT_SR.U32 = SWT_SERVICE_KEY_B;
		} else {
			SWT.SWT_SR.U32 = SWT_SERVICE_KEY_A;
		}
	}
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date        userid    (Description on following lines: SCR #, etc.)
 * ----------- --------
 *
 \*===========================================================================*/

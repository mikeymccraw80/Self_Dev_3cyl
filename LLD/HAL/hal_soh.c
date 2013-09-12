/*===========================================================================*\
 * FILE: soh_hal.c
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec: hal_soh.c~4:csrc:ctc_pt3#1 %
 * %version: 4 %
 * %derived_by: zzrfyj %
 * %date_modified:      %
 * $SOURCE: $
 * $REVISION: $
 * $AUTHOR: $
 *---------------------------------------------------------------------------
 *
 * DESCRIPTION:
 *   ETC SOH building block software - HAL.
 *   (for Infineon TC1762, TC1765, TC1766, TC1775, TC1792, TC1796.)
 *   Used in conjunction with ASIC (VSEP, MIO) with state-of-health (SOH) logic.
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
 *   [C163] DEVIATION: MULTIPLE RETURN VALUES!
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

#include "soh.h"
#include "dd_vsep_soh.h"
#include "io_conversion.h"

#include "io_config_stm.h"
#include "dd_vsep.h"
#include "dd_mios.h"


/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Definitions
\*===========================================================================*/


/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/

/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * Function Definitions
\*===========================================================================*/
/*===========================================================================*\
 * FUNCTION: HAL_SOH_VsepSPI_High_Low_Error
 *===========================================================================
 * RETURN VALUE:
 * bool spi_high_low_error: whether there is error in the first two bit
 *							(1st bit is low, 2nd bit is high)
 *
 * PARAMETERS:
 * bool unbuffered: TRUE = unbuffered vsep status
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
 * This function checks whether the first two bits of SPI message from vsep
 * are correct or not
\*===========================================================================*/
 bool HAL_SOH_VsepSPI_High_Low_Error(bool unbuffered)
{
	bool spi_high_low_error;
	uint16_t inbuffer;

	
	if (unbuffered)
	{
		inbuffer = (uint16_t) (VSEP_SOH_Status_Rxd[VSEP_SOH_STATUS_RXD_MESSAGE_FLT]);
	}
	else
	{
		inbuffer = (uint16_t) (VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_FLT]);
	}

	
	if((VSEP_Msg_CMD_Get_Test_Bit_Low(inbuffer) == 0)&&
		(VSEP_Msg_CMD_Get_Test_Bit_High(inbuffer) == 1))
	{
		spi_high_low_error=false;
	}
	else
	{
		spi_high_low_error = true;
	}


	return spi_high_low_error;
}


/*===========================================================================*\
 * FUNCTION: HAL_SOH_CnR_Get_Challenge
 *===========================================================================
 * RETURN VALUE:
 * uint8_t challenge : SOH Challenge value.
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
 * This function reads the SOH challenge value.
\*===========================================================================*/
uint8_t HAL_SOH_CnR_Get_Challenge(void)
{
	return VSEP_SOH_Get_Challenge(MTSA_CONFIG_VSEP_DEVICE_0);
}


/*===========================================================================*\
 * FUNCTION: HAL_SOH_CnR_Set_Response
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * bool fse_disreq    : 1 - request disable fuel, spark and ETC.
 *                      0 - request enable fuel, spark and ETC.
 *
 * uint8_t response   : SOH Response value (6-bit).
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
 * This function writes the SOH fuel_spark_etc_disable_request bit and the
 * 6-bit response value.
\*===========================================================================*/
void HAL_SOH_CnR_Set_Response(bool fse_disreq, uint8_t response)
{
	VSEP_SOH_Set_DisableFSE_Request(MTSA_CONFIG_VSEP_DEVICE_0, fse_disreq);
	VSEP_SOH_Set_Response(MTSA_CONFIG_VSEP_DEVICE_0, response);
}

/*===========================================================================*\
 * FUNCTION: HAL_SOH_CnR_Clear_Timeout_Fault
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * bool cnr_timeout_fault	:	1 - clear C&R timeout fault bit.
 *                     			0 - do not clear C&R timeout fault bit.
 *
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
 * This function set/clear the SOH C&R timeout fault bit.
\*===========================================================================*/
void HAL_SOH_CnR_Clear_Timeout_Fault(bool cnr_timeout_fault)
{
	VSEP_SOH_Set_Timeout_Fault(MTSA_CONFIG_VSEP_DEVICE_0, cnr_timeout_fault);
}



/*===========================================================================*\
 * FUNCTION: HAL_SOH_Setup_Interrupt
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * SOH_TMR_MSEC_T irq_period : interrupt occurrence time scaled to SOH_TMR_MSEC_T.
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
 * This function setup an ETC SOH interrupt to occur in the specified time
 * in one-shot mode.
\*===========================================================================*/
void HAL_SOH_Setup_Interrupt(SOH_TMR_MSEC_T irq_period)
{
	STM_Timer_Set_Value(STM_CHANNEL_0,IO_Convert_Time_To_Count(
																			 irq_period,
																			 STM_CLOCK_FREQUENCY_HZ,
																			 S_SOH_TMR_MSEC_T,
																			 MILLISECOND_RESOLUTION ));
}

/*===========================================================================*\
 * FUNCTION: HAL_SOH_ETC_ISR
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
 * This ETC SOH interrupt service routine handler executes the ETC SOH tests.
\*===========================================================================*/
void HAL_SOH_ETC_ISR(void)
{
    SOH_ETC_ISR();
}
/*===========================================================================*\
 * FUNCTION: HAL_SOH_CnR_Get_Status
 *===========================================================================
 * RETURN VALUE:
 * Soh_CnR_Status_T status   : SOH challenge and response status.
 *
 * +---------------+----------+-------+-----------------------------------------------+
 * | Bit Name      | Bit      | State | Description                                   |
 * |               | Position |       |                                               |
 * +---------------+----------+-------+-----------------------------------------------+
 * | CRTIMEOUT     |      0   |   0	  | No timeout of the SOH C&R has occurred        |
 * |               |          |   1	  | SOH C&R timeout occurred                      |
 * |               |          |       | or communication error                        |
 * +---------------+----------+-------+-----------------------------------------------+
 * | RESPCOUNT     | 12 - 8   |   0	  | 5-bit C&R RESPCOUNT counter value             |
 * |               |          |       | (valid 0 to 19)                               |
 * +---------------+----------+-------+-----------------------------------------------+
 * | CRDISARM_STAT |     13   |   0   | SOH C&R logic is not disabled                 |
 * |               |          |   1   | SOH C&R logic is disabled                     |
 * +---------------+----------+-------+-----------------------------------------------+
 * | FSE_EN_STAT   |     14   |   0   | FSE_Enable pin is pulled to a valid low level |
 * |               |          |   1   | FSE_Enable pin is at a valid high level or    |
 * |               |          |       | or communication error                        |
 * +---------------+----------+-------+-----------------------------------------------+
 * | GEN_STAT      |     15   |   0   | GEN_FSE_RSTB input is at logic low level      |
 * |               |          |   1   | GEN_FSE_RSTB input is at logic high level     |
 * +---------------+----------+-------+-----------------------------------------------+
 *
 * PARAMETERS:
 * bool unbuffered    : 1 - unbuffered read.
 *                      0 - buffered read.
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
 * This function read the SOH challenge and response status.
\*===========================================================================*/
uint16_t HAL_SOH_CnR_Get_Status(bool unbuffered)
{
   Soh_CnR_Status_T vsep_status;

   if (unbuffered == true)
   {
		Update_VSEP_SOH_Status_Immediate(MTSA_CONFIG_VSEP_DEVICE_0);

   		if (HAL_SOH_VsepSPI_High_Low_Error(unbuffered))
		{
			vsep_status.Bits.FSE_En_Stat   = 1;
   		vsep_status.Bits.CRTimeout     =1;
   	
		}
		else 
		{
			vsep_status.Bits.FSE_En_Stat   = VSEP_Msg_CMD_Get_FSE_Enable_Status(VSEP_SOH_Status_Rxd[VSEP_SOH_STATUS_RXD_MESSAGE_FLT]);
			vsep_status.Bits.CRTimeout     = VSEP_Msg_CMD_Get_Challenge_Response_Timeout(VSEP_SOH_Status_Rxd[VSEP_SOH_STATUS_RXD_MESSAGE_FLT]);
			vsep_status.Bits.Respcount     = VSEP_Msg_CMD_Get_Challenge_Response_Count(VSEP_SOH_Status_Rxd[VSEP_SOH_STATUS_RXD_MESSAGE_FLT]);
			vsep_status.Bits.CRDisarm_Stat = VSEP_Msg_CMD_Get_Challenge_Response_Disarm(VSEP_SOH_Status_Rxd[VSEP_SOH_STATUS_RXD_MESSAGE_FLT]);
			vsep_status.Bits.GEN_Stat      = VSEP_Msg_CMD_Get_Global_Enable_Status(VSEP_SOH_Status_Rxd[VSEP_SOH_STATUS_RXD_MESSAGE_FLT]);
		}
   }
   else
   {
   		if (HAL_SOH_VsepSPI_High_Low_Error(unbuffered))
		{
			vsep_status.Bits.FSE_En_Stat   = 1;
   		vsep_status.Bits.CRTimeout     =1;
   	
		}
		else 
		{
			vsep_status.Bits.FSE_En_Stat   = VSEP_Msg_CMD_Get_FSE_Enable_Status(VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_FLT]);
		   	vsep_status.Bits.CRTimeout     = VSEP_Msg_CMD_Get_Challenge_Response_Timeout(VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_FLT]);
				vsep_status.Bits.Respcount     = VSEP_Msg_CMD_Get_Challenge_Response_Count(VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_FLT]);
		   	vsep_status.Bits.CRDisarm_Stat = VSEP_Msg_CMD_Get_Challenge_Response_Disarm(VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_FLT]);
	   		vsep_status.Bits.GEN_Stat      = VSEP_Msg_CMD_Get_Global_Enable_Status(VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_FLT]);
		}
   }

   return (uint16_t)vsep_status.Word;
}

 void UpdateHWIO_ETC_SOH_Loop_Sequence_Array( const uint8_t arr_index )
{
//#ifndef HW_SOH_DISABLE
     SOH_ETC_Update_Loop_Sequence_Array( (const uint8_t )arr_index );//mz38cg
//#endif
}

 //loop sequence validation for chery applicaiton//
 void ETSMRSV_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(0);
 }
 
 void ETSMIST_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(1);
 }
 
 void ETSMAPV_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(2);
 }
 
 void ETSMRES1_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(3);
 }
 
 void ETSMN_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(4);
 }
 
 void ETSMLD_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(5);
 }
 
 void ETSMAFST_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(6);
 }
 
 void ETSMRES2_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(7);
 }
 
 void ETSMTQP_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(8);
 }
 
 void ETSMTQF_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(9);
 }
 
 void ETSMIGA_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(10);
 }
 
 void ETSMRES3_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(11);
 }
 
 void ETSMTQC_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(12);
 }
 
 void ETSMTQ_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(13);
 }
 
 void ETSMMFR_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(14);
 }
 
 void ETSMRES4_r40ms()
 {UpdateHWIO_ETC_SOH_Loop_Sequence_Array(15);
 }

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date        userid    (Description on following lines: SCR #, etc.)
 * ----------- --------
 * 01 Nov 05  jay wyrick, sgchia
 * + Created initial file.
 *
\*===========================================================================*/

/*===========================================================================*/
/* FILE: immo_eeprom.c                                                         */
/*===========================================================================*/
/* COPYRIGHT, 2004, DELPHI ELECTRONICS & SAFETY SYSTEMS, All Rights reserved */
/* Delphi Confidential                                                       */
/*===========================================================================*/
/* %name:             immo_eeprom.c %                                          */
/*                                                                           */
/* created_by:       Liu Zheng                                                */
/*                                                                           */
/* date_created:     26 Feb 2005                                              */
/*                                                                           */
/* %derived_by:       vzp48z %                                               */
/*                                                                           */
/* %date_modified:   %                                                       */
/*                                                                           */
/* %version:         2 %                                                     */
/*                                                                           */
/*===========================================================================*/
/* DESCRIPTION:                                                              */
/*   This file contains executive for Immobilizer service on EEPROM.    */
/*                                                                           */
/* ABBREVIATIONS:                                                            */
/* None.                                                                     */
/*                                                                           */
/* TRACEABILITY INFO:                                                        */
/*   Design Document:                                                        */
/*                                                                           */
/*   Requirements Document(s):                                               */
/*                                                                           */
/*   Applicable Standards:                                                   */
/*   C Coding Standards:        SW_REF 264.15D.                              */
/*                                                                           */
/* DEVIATIONS FROM STANDARDS:                                                */
/* None.                                                                     */
/*                                                                           */
/*===========================================================================*/
/* REUSE: DO NOT MODIFY THIS FILE.                                           */
/* Co-ordinate any desired changes with the Software Forward Engineering and */
/* Building Blocks group                                                     */
/*===========================================================================*/
//#include "reuse.h"
//#include "types.h"


/* ========================================================================== *\
 * Other header files.
\* ========================================================================== */
//#include "immo_exec.h" 
//#include "dd_nvram.h"

/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */
//uint8_t    ImmoEEPROMStatus[6];

/*****************************************************************************
 *
 * Function:           SecretKeyAndSecurityAccessCodeEEPROMValid
 * Description:        Check SK and PIN validation at initialization. 
 * Parameters:         None
 * Return:             TbBOOLEAN
 *
 *****************************************************************************/
#if 0
FAR_COS TbBOOLEAN SecretKeyAndSecurityAccessCodeEEPROMValid(void)
{
   TbBOOLEAN CheckResult;

   if ( (EE_SK_L == SK_All0xFF) ||
        (EE_SK_L == SK_All0x00) )
   {
       CheckResult=CbFALSE;
   }
   else
   {
       CheckResult=CbTRUE;
   }
   
return (CheckResult);
}/*** End of SecretKeyAndSecurityAccessCodeEEPROMValid ***/
#endif
/*****************************************************************************
 *
 * Function:           EEPROMWriteSuccess
 * Description:        Check EEPROM write successfully or not. 
 * Parameters:         EEP_data_address, RAM_data_address, size
 * Return:             TbBOOLEAN
 *
 *****************************************************************************/
#if 0
FAR_COS TbBOOLEAN EEPROMWriteSuccess( uint8_t *EEP_data_address, uint8_t *RAM_data_address, uint8_t size)
{
   TbBOOLEAN result;
   uint8_t counter;

   result=CbTRUE;

   for (counter=0; counter<size; counter++)
   {
   	if (*(EEP_data_address+counter)!=*(RAM_data_address+counter)) 
   	{ 
   	   result=CbFALSE;
   	}
   }
   return (result);
}
#endif
/*****************************************************************************
 *
 * Function:           ReadImmoEEPROMData
 * Description:       Read Immo EEPROM Data(jicheng version).
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
#if 0
FAR_COS void ReadImmoEEPROMData(void)
{
   BYTE counter, *data;
   data=&EE_Learnt_Flag;
   for (counter=0;counter<6;counter++)
   {
      ImmoEEPROMStatus[counter]=*(data+counter);
   }
}/*** End of ReadImmoEEPROMData ***/
#endif
/*****************************************************************************
 *
 * Function:           UpdateImmoEEPROMData
 * Description:       Update Immo EEPROM Data.
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
#if 0
FAR_COS void UpdateImmoEEPROMData(void)
{
   BYTE counter, *data;
   TbBOOLEAN status=CbFALSE;
   data=&EE_Learnt_Flag;
   for (counter=0; counter<6;counter++)
   {
      if (ImmoEEPROMStatus[counter]!=*(data+counter))
      {
         status=CbTRUE;
         break;
      }
   }
   if (status)  EEPROMWrite(ImmoEEPROMStatus, &EE_Learnt_Flag , 6);
}/*** End of UpdateImmoEEPROMData ***/
#endif
/*****************************************************************************
 *
 * Function:           SKPINEEPROMValid
 * Description:       verify the validation of SK and PIN in EEPROM(jicheng version).
 * Parameters:       None
 * Return:              TbBOOLEAN
 *
 *****************************************************************************/
#if 0
FAR_COS TbBOOLEAN SKPINEEPROMValid(void)
{
   TbBOOLEAN CheckResult;
   
   CheckResult=CbTRUE;
   if ((EE_SK[0]==0)&&(EE_SK[1]==0)&&(EE_SK[2]==0)&&(EE_SK[3]==0)&&(EE_SK[4]==0))
   {	
      CheckResult=CbFALSE;
   }
   if ((EE_SK[0]==0xFF)&&(EE_SK[1]==0xFF)&&(EE_SK[2]==0xFF)&&(EE_SK[3]==0xFF)&&(EE_SK[4]==0xFF))
   {	 
      CheckResult=CbFALSE;
   }
   if ((EE_PIN[0]==0)&&(EE_PIN[1]==0)) 
   { 
      CheckResult=CbFALSE;
   }
   if ((EE_PIN[0]==0xFF)&&(EE_PIN[1]==0xFF))  
   {
      CheckResult=CbFALSE;
   }
   
   return (CheckResult);
}/*** End of SKPINEEPROMValid ***/
#endif

/*****************************************************************************
 *
 * Function:           PINProtectService
 * Description:       Protect PIN while learning process if wrong PIN attemt more than 3 times.
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
#if 0
FAR_COS void PINProtectService (void)
{
   ImmoEEPROMStatus[PINWrongAttemptCounterIdx]=EE_PINWrongAttemptCounter+1;
   if (ImmoEEPROMStatus[PINWrongAttemptCounterIdx]>=PINAccessMaxTimer)
   {
      /* If PIN is unprotected and Access time over, Protect PIN. */
      ImmoEEPROMStatus[PINProtectFlagIdx]=PINProtected;
      ImmoEEPROMStatus[PINWrongAttemptCounterIdx]=0;
      PIN_Protect_Timer=PINAccessDelayTime;
   }

   UpdateImmoEEPROMData();
}/*** End of PINProtectService ***/
#endif
/*****************************************************************************
 *
 * Function:           PINUnProtectService
 * Description:       Unprotect PIN till delay time out. 
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
/*FAR_COS void PINUnProtectService(void)
{
   if (ImmoEEPROMStatus[PINProtectFlagIdx]==PINProtected)
   {
      // If PIN is protected, decrease timer every 0.5s and un-protect PIN. 
      PIN_Protect_Timer--;
      if (0==PIN_Protect_Timer)
      {
         ImmoEEPROMStatus[PINProtectFlagIdx]=PINUnProtected;
			
         UpdateImmoEEPROMData();
      }
   }
}*//*** End of PINUnProtectService ***/


/*****************************************************************************
 *
 * Function:           SKWriteSuccess
 * Description:       Check whether SK is wroten into EEPROM successfully.
 * Parameters:       None
 * Return:              TbBOOLEAN
 *
 *****************************************************************************/
/*
FAR_COS TbBOOLEAN SKWriteSuccess(void)
{
   BYTE counter;
   TbBOOLEAN SK_result=CbTRUE;
   for (counter=0;counter<SK_Length_JiCheng;counter++)
   {
      if (Immo_SK[counter]!=EE_SK[counter]) SK_result=CbFALSE;
   }

   return (SK_result);
}*/
/*** End of SKWriteSuccess ***/

/*****************************************************************************
 *
 * Function:           PINWriteSuccess
 * Description:       Check whether PIN is wroten into EEPROM successfully.
 * Parameters:       None
 * Return:              TbBOOLEAN
 *
 *****************************************************************************/
#if 0
FAR_COS TbBOOLEAN PINWriteSuccess(void)
{
   BYTE counter;
   TbBOOLEAN PIN_result=CbTRUE;
   if ((Immo_PIN[0]!=EE_PIN[0])||(Immo_PIN[1]!=EE_PIN[1])) 
   { 
      PIN_result=CbFALSE;
   }
   return (PIN_result);
}/*** End of PINWriteSuccess ***/
#endif
/*****************************************************************************
 *
 * Function:           PINValid
 * Description:       Check PIN validation during learning process. 
 * Parameters:       None
 * Return:              TbBOOLEAN
 *
 *****************************************************************************/
#if 0
FAR_COS TbBOOLEAN PINValid (void)
{
   TbBOOLEAN PINResult;

   Immo_PIN[0]=GetKw2000ServiceData(3);
   Immo_PIN[1]=GetKw2000ServiceData(4);    
   			
   if ((Immo_PIN[0]==EE_PIN[0])&&(Immo_PIN[1]==EE_PIN[1]))  
   {
      PINResult=CbTRUE;
      /* Clear PINWrongAttemptCounter. */
      ImmoEEPROMStatus[PINProtectFlagIdx]=PINUnProtected;
      /* Unprotect PIN. */
      ImmoEEPROMStatus[PINWrongAttemptCounterIdx]=0;

      UpdateImmoEEPROMData();
   }
   else
   {
      PINResult=CbFALSE;
   }
   return (PINResult);
}/*** End of PINValid ***/
#endif
/*****************************************************************************
 *
 * Function:           ClearSKPIN
 * Description:       clear the sk and pin when learn sk and pin from jicheng immo.
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
/*FAR_COS void ClearSKPIN(void)
{
   BYTE temp[SK_Length_JiCheng+PIN_Length_JiCheng];
   BYTE counter;
   for (counter=0;counter<SK_Length_JiCheng+PIN_Length_JiCheng;counter++)
   {
      temp[counter]=0xFF;
   }
   EEPROMWrite(temp, EE_SK, (SK_Length_JiCheng));
   EEPROMWrite(&temp[SK_Length_JiCheng-1], EE_PIN, (PIN_Length_JiCheng));

}
*/
/* ==========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/* ==========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---                                              */
/* 
/* ===========================================================================*/



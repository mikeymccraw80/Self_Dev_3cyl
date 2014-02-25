
//=============================================================================
//                                Includes
//=============================================================================
#include "dd_ecsm.h"

//=============================================================================
// Register overlay of the submodule
//=============================================================================
#define SECTION_ECSM_REGISTER
#include "section.h"
ECSM_T ECSM;
#define SECTION_END
#include "section.h"

//=============================================================================
// ECSM_Initialize_Device
//=============================================================================
void ECSM_Initialize_Device(void)
{
   volatile uint8_t status;

   //=============================================================================
   // 1) Clear the status register
   //=============================================================================
   status = ECSM.ESR.U8;
   ECSM.ESR.U8 = (status & ECSM_ESR_CLEAR);
   //=============================================================================
   // 2) Write the ECSM control field for the desired ECR value.
   //=============================================================================
   // ER1BR      5       rw    Enable RAM 1-bit reporting
   //                          0 Reporting of single-bit platform RAM corrections 
   //                            is disabled
   //                          1 Reporting of single-bit platform RAM corrections
   //                            is enabled

   
   ECSM.ECR.F.ER1BR = 1;

   //-----------------------------------------------------------------------------
   // EF1BR      4       rw    Enable Flash 1-bit reporting.
   //                          0 Reporting of single-bit platform flash  
   //                            corrections is disabled.
   //                          1 Reporting of single-bit platform flash  
   //                            corrections is enabled.

  ECSM.ECR.F.EF1BR   = 1;

  //-----------------------------------------------------------------------------
  // ERNCR      1       rw    Enable platform RAM non-correctable reporting. The
  //                          occurrence of a non-correctable multi-bit
  //                          RAM error generates a ECSM ECC interrupt
  //                          request as signalled by the assertion of
  //                          ECSM_ESR[RNCE]. The faulting address,
  //                          attributes and data are also captured in the
  //                          REAR, PRESR, REMR, REAT and REDR registers.
  //                          0 Reporting of non-correctable RAM errors
  //                            is disabled.
  //                          1 Reporting of non-correctable RAM errors
  //                            is enabled.

 ECSM.ECR.F.ERNCR   =1;
  //-----------------------------------------------------------------------------
  // EFNCR      0       rw    Enable platform Flash non-correctable reporting. 
  //                          The occurrence of a non-correctable multi-bit
  //                          Flash error generates a ECSM ECC interrupt
  //                          request as signalled by the assertion of
  //                          ECSM_ESR[FNCE]. The faulting address,
  //                          attributes and data are also captured in the
  //                          FEAR, FEMR, FEAT and FEDR registers.
  //                          0 Reporting of non-correctable Flash errors
  //                            is disabled.
  //                          1 Reporting of non-correctable Flash errors
  //                            is enabled.

  ECSM.ECR.F.EFNCR   =1;
   //=============================================================================
   // 3) Write the EEGR control field for the desired  EEGR value.
   //=============================================================================

   //-----------------------------------------------------------------------------
   // FRCNCI    9      rw   Force RAM continuous noncorrectable 
   //                       data Inversions.
   //                       0 No RAM continuous 2-bit data inversions 
   //                         are generated.
   //                       1 2-bit data inversions in the RAM are 
   //                         continuously generated.

    ECSM.EEGR.F.FRCNCI = 0;
   //-----------------------------------------------------------------------------
   // FR1NCI    8      rw   Force RAM one noncorrectable data Inversions
   //                       0 No RAM single 2-bit data inversions are 
   //                         generated.
   //                       1 One 2-bit data error in the RAM is 
   //                        generated.
  ECSM.EEGR.F.FR1NCI = 0;
   //-----------------------------------------------------------------------------
  // ERRBIT  [7:0]    rw   Error bit position. Defines the bit position which 
  //                       is complemented to create the data inversions on 
  //                       the write operation. The bit specified by this field 
  //                       plus the odd parity bit of the ECC code are inverted.
  ECSM.EEGR.F.ERRBIT = 0;
   //-----------------------------------------------------------------------------
   //=============================================================================

}
//=============================================================================
// ECSM_Get_Flash_Attributes
//=============================================================================
uint32_t ECSM_Get_RAM_FLASH_Attributes(ECSM_RAM_Flash_Attributes_Status_T attribute_type)
{
   uint32_t status = 0;

   switch(attribute_type)
   {
   case ECSM_FEAR_FLASH_FAULT_ADDRESS :
      status = ECSM.FEAR;
      break;

   case ECSM_FEMR_FLASH_MASTER_NO :
      status = (uint32_t)ECSM.FEMR.F.FEMR;
      break;

   case ECSM_FEAT_PROTECTION :
      status = (uint32_t)ECSM.FEAT.F.PROTECTION;
      break;

   case ECSM_FEAT_BUS_SIZE :
      status = (uint32_t)ECSM.FEAT.F.SIZE;
      break;

   case ECSM_FEAT_WRITE_ACCESS :
      status = (uint32_t)ECSM.FEAT.F.WRITE;
      break;

   case ECSM_FEDR_DATA_H :
      status = ECSM.FEDRH;
      break;

   case ECSM_FEDR_DATA_L :
      status = ECSM.FEDRL;
      break;

   case ECSM_REAR_RAM_FAULT_ADDRESS :
      status = (uint32_t)ECSM.REAR;
      break;

   case ECSM_PRESR_RAM_SYNDROME :
      status = (uint32_t)ECSM.PRESR;
      break;

   case ECSM_REMR_RAM_MASTER_NO :
      status = (uint32_t)ECSM.REMR.F.REMR;
      break;

   case ECSM_REAT_PROTECTION :
      status = (uint32_t)ECSM.REAT.F.PROTECTION;
      break;

   case ECSM_REAT_BUS_SIZE :
      status = (uint32_t)ECSM.REAT.F.SIZE;
      break;

   case ECSM_REAT_WRITE_ACCESS :
      status = (uint32_t)ECSM.REAT.F.WRITE;
      break;

   case ECSM_REDR_DATA_H :
      status = (uint32_t)ECSM.REDRH;
      break;

   case ECSM_REDR_DATA_L :
      status = (uint32_t)ECSM.REDRL;
      break;

   default:
     break;
   }
   return status;
}

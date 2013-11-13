/*===========================================================================*\
 * Header Files
\*===========================================================================*/
#include "dd_qadc_interface.h"

//=============================================================================
// HAL_Analog_Get_ESC1HI_Value
//=============================================================================
  //uint16_t HAL_Analog_Get_ESC1HI_Value(void) 
 //{
   //  return  QADC_Analog_Get_Value(AD_ESC1HI_Channel);
 //}

//=============================================================================
// HAL_Analog_Get_ESC1LO_Value
//=============================================================================
 // uint16_t HAL_Analog_Get_ESC1LO_Value(void) 
 //{
  //   return  QADC_Analog_Get_Value(AD_ESC1LO_Channel);
 //}

//=============================================================================
// HAL_Analog_Get_MAPVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_MAPVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_MAPVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_ACPREVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_ACPREVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_ACPREVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_LEGRFBVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_LEGRFBVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_LEGRFBVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_TPS1VI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_TPS1VI_Value(void) 
 {
     return  QADC_Analog_FIFO1_Get_Value(AD_TPS1VI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_TPS2VI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_TPS2VI_Value(void) 
 {
     return  QADC_Analog_FIFO1_Get_Value(AD_TPS2VI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_PPS1VI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_PPS1VI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_PPS1VI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_PPS2VI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_PPS2VI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_PPS2VI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_FLVVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_FLVVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_FLVVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_EOPVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_SPA1VI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_SPA1VI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_O2AVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_O2AVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_O2AVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_O2BVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_O2BVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_O2BVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_CRSVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_CRSVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_CRSVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_CLTVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_CLTVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_CLTVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_MATVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_MATVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_MATVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_BSTATVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_BSTATVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_BSTATVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_EOTVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_FREPVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_FREPVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_BKVAVII_Value
//=============================================================================
  uint16_t HAL_Analog_Get_BKVAVII_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_BKVAVII_Channel);
 }

//=============================================================================
// HAL_Analog_Get_RREPVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_RREPVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_RREPVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_BSTPREVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_BSTPREVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_BSTPREVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_RRVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_RRVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_RRVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_PSREF1_Value
//=============================================================================
  uint16_t HAL_Analog_Get_PSREF1_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_PSREF1_Channel);
 }

//=============================================================================
// HAL_Analog_Get_PSREF2_Value
//=============================================================================
  uint16_t HAL_Analog_Get_PSREF2_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_PSREF2_Channel);
 }

//=============================================================================
// HAL_Analog_Get_IGNVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_IGNVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_IGNVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_58XRAWIN_Value
//=============================================================================
  uint16_t HAL_Analog_Get_58XRAWIN_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_58XRAWIN_Channel);
 }

//=============================================================================
// HAL_Analog_Get_PBATTVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_PBATTVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_PBATTVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_HWCFGVI_Value
//=============================================================================
  uint16_t HAL_Analog_Get_HWCFGVI_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_HWCFGVI_Channel);
 }

//=============================================================================
// HAL_Analog_Get_CPUTemp_Value
//=============================================================================
  uint16_t HAL_Analog_Get_CPUTemp_Value(void) 
 {
     return  QADC_Analog_Get_Value(AD_CPUTemp_Channel);
 }



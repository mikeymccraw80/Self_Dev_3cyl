/******************************************************************************
 *
 * Filename:          knodmall.c
 *
 * Description:         OBD-II Knock System and Sensor Diagnostic
 *
 * Global Functions Defined:
 *                    InitKNKD_RstToKeyOn
 *                    InitKNKD_OFVC_Clear
 *                    MngKNKD_CylEventTasks
 *                    MngKNKD_125msTasks
 * Static Functions Defined:
 *                    InitKNKD_CommonParameters
 *                    EvalKNKD_EnableCriteria
 *                    EvalKNKD_SystemShort
 *                    EvalKNKD_SystemHigh
 *                    EvalKNKD_SensorProcessing
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#8/csrc/knodmall.c/1 %
 * %date_created:  Wed Mar 19 10:11:41 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
*  Include Files 
*****************************************************************************/ 
// #include "knodfexi.h"   /* For global resources definitions   */
#include "knodcald.h"   /* For Definition-Declaration check   */
#include "knodpapi.h"   /* For Definition-Declaration check   */

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN            SbKNKD_SystemTestFailed;
TbBOOLEAN            SbKNKD_SystemTestLoFailed;
TbBOOLEAN            SbKNKD_SystemTestHiFailed;
TbBOOLEAN            SbKNKD_SensorTestFailed;
#pragma section DATA " " ".bss"
TbBOOLEAN            SbKNKD_SensorTestComplete;
  
#if 0
/*********************************************************************
* Module Variables
**********************************************************************/

T_COUNT_WORD                ScKNKD_SensorFailCounter;
T_COUNT_WORD                VcKNKD_SensorSampleCounter;
T_COUNT_WORD                VcKNKD_SystemFailLoCounter;
T_COUNT_WORD                VcKNKD_SystemFailHiCounter;
T_COUNT_WORD                VcKNKD_SystemSampleCounter;
T_DECIBELS             	    LfKNKD_ESCGainMin;

 TbBOOLEAN            SbKNKD_DsblgKeyOnFaultPresent;
 TbBOOLEAN            SbKNKD_SystemEnableCriteriaMet;
 TbBOOLEAN            SbKNKD_CommonEnableCriteriaMet;
 TbBOOLEAN            SbKNKD_SystemFailCriteriaMet;
 TbBOOLEAN            SbKNKD_SystemTestComplete;
  #pragma section [nvram] 
 TbBOOLEAN            SbKNKD_SystemTestFailed;
 TbBOOLEAN            SbKNKD_SystemTestLoFailed;
 TbBOOLEAN            SbKNKD_SystemTestHiFailed;
  TbBOOLEAN            SbKNKD_SensorTestFailed;
  #pragma section [] 
 TbBOOLEAN            SbKNKD_SensorEnableCriteriaMet;
 TbBOOLEAN            SbKNKD_SensorTestComplete;
 T_PERCENTa           SfKNKD_Pct_ADESC_Delta;/* Max(ADESC) - Min(ADESC)*/

  TbBOOLEAN            SbKNKD_SystemTestComplete_Internal;
 TbBOOLEAN            SbKNKD_SensorTestComplete_Internal;

/*****************************************************************************
 * KNKD Constansts for diagnostic checking
 *****************************************************************************/

/*********************************************************************
* Local module functions
*********************************************************************/
static void      EvalKNKD_EnableCriteria(void);
static TbBOOLEAN EvalKNKD_SystemHigh(void);
static TbBOOLEAN EvalKNKD_SystemShort(void);
static TbBOOLEAN EvalKNKD_SensorProcessing(void);

/*****************************************************************************
 *                                                                           *
 * Function:           InitFTRM_CommomParameters                             *
 * Type:                                                                     *
 * Description:        This function contain parameters common to multiple   *
 *                     fueltrim initialization routines                      *
 *                                                                           *
 * Parameters:         None                                                  *
 * Return:             None                                                  *
 *****************************************************************************/
 static void InitKNKD_CommonParameters(void)
 {
   VcKNKD_SystemSampleCounter = V_COUNT_WORD(0);
   VcKNKD_SystemFailLoCounter = V_COUNT_WORD(0);
   VcKNKD_SystemFailHiCounter = V_COUNT_WORD(0);
   SbKNKD_SystemTestFailed = CbFALSE;
   SbKNKD_SystemTestComplete_Internal = CbFALSE;
   ScKNKD_SensorFailCounter = V_COUNT_WORD(0);
   VcKNKD_SensorSampleCounter = V_COUNT_WORD(0);
   SbKNKD_SensorTestComplete_Internal = CbFALSE;
   SbKNKD_SensorTestFailed = CbFALSE;
   SbKNKD_SystemTestLoFailed  = CbFALSE;
   SbKNKD_SystemTestHiFailed  = CbFALSE;
}
#if 0
/********************************************************************
*
* Function:      InitKNKD_RstToKeyOn
*
* Description:   This process is called by the operating system during 
*                reset to key-on initialization.
*
* Parameters:    None
* Returns:       None
*********************************************************************/
FAR_COS void InitKNKD_RstToKeyOff(void)
{

   InitKNKD_CommonParameters ();
   SbKNKD_CommonEnableCriteriaMet = CbFALSE;
   SbKNKD_SystemEnableCriteriaMet = CbFALSE;
   SbKNKD_SensorEnableCriteriaMet = CbFALSE;
}
#endif

/********************************************************************
*
* Function:      MngKNKD_CylEventTasks
*
* Description:   This process manages knock sensor diagnostic tasks 
*                and is called by the operating system every cylinder
*                event.
*
*                Because this process is in the cylinder event loop,
*                code must be written to be as efficient as possible,
*                and liberties have been taken with the p-spec model.
*
* Parameters:    None
* Returns:       None
*********************************************************************/
void MngKNKD_CylEventTasks(void)
{
   
        /*  system pass/fail logic */

   if ( (SbKNKD_SystemEnableCriteriaMet != CbFALSE)
       && (VcKNKD_SystemSampleCounter < KcKNKD_SystemSampleThrsh)
       && (VcKNKD_SystemFailLoCounter < KcKNKD_SystemFailLoThrsh) 
       && (VcKNKD_SystemFailHiCounter < KcKNKD_SystemFailHiThrsh) )
   {
      if ( EvalKNKD_SystemShort() != CbFALSE )
      {
        VcKNKD_SystemFailLoCounter ++;
      }
     
      if ( EvalKNKD_SystemHigh() != CbFALSE )
      {
        VcKNKD_SystemFailHiCounter ++;
      }

      VcKNKD_SystemSampleCounter++;
   }
      
        /*  Sensorpass/fail logic */

   if ( (SbKNKD_SensorEnableCriteriaMet != CbFALSE)
       && (VcKNKD_SensorSampleCounter < KcKNKD_SensorSampleThrsh)
       && (ScKNKD_SensorFailCounter < KcKNKD_SensorFailThrsh) )
   {
      if (EvalKNKD_SensorProcessing() != CbFALSE)
      {
        ScKNKD_SensorFailCounter ++;
      }
      VcKNKD_SensorSampleCounter++;
   }

}

/********************************************************************
*
* Function:      MngKNKD_125msTasks
*
* Description:   This process manages knock sensor diagnostic tasks 
*                and is called by the operating system every 125 ms.
*
* Parameters:    None
* Returns:       None
*********************************************************************/
void MngKNKD_125msTasks(void)
{
   
   EvalKNKD_EnableCriteria();

        /*  system pass/fail logic */

   if (SbKNKD_SystemEnableCriteriaMet != CbFALSE)
   {
       EvalOBDU_DoubleXofY (VcKNKD_SystemFailLoCounter,
                            VcKNKD_SystemFailHiCounter,
                            VcKNKD_SystemSampleCounter,
                            KcKNKD_SystemFailLoThrsh,
                            KcKNKD_SystemFailHiThrsh,
                            KcKNKD_SystemSampleThrsh,
                            &SbKNKD_SystemTestComplete_Internal,
                            &SbKNKD_SystemTestLoFailed,
                            &SbKNKD_SystemTestHiFailed);

       /*  Consolidate failed status since we are recording only a single
           failure code for all failures while the above routine
           discriminates between failing high and failing low.  */

       if ( (SbKNKD_SystemTestLoFailed != CbFALSE )
           || (SbKNKD_SystemTestHiFailed != CbFALSE) )
       {
           SbKNKD_SystemTestFailed = CbTRUE;
       }
       else
       {
           SbKNKD_SystemTestFailed = CbFALSE;
       }


   }
   if (SbKNKD_SystemTestComplete_Internal != CbFALSE)
   {
       VcKNKD_SystemFailLoCounter = V_COUNT_WORD (0);
       VcKNKD_SystemFailHiCounter = V_COUNT_WORD (0);
       VcKNKD_SystemSampleCounter = V_COUNT_WORD (0);
   }

  SbKNKD_SensorTestComplete |=SbKNKD_SensorTestComplete_Internal;
        /*  Sensorpass/fail logic */

   if (SbKNKD_SensorEnableCriteriaMet != CbFALSE)
   {
      EvalOBDU_SingleXofY (ScKNKD_SensorFailCounter,
                           VcKNKD_SensorSampleCounter,
                           KcKNKD_SensorFailThrsh,
                           KcKNKD_SensorSampleThrsh,
                           &SbKNKD_SensorTestComplete_Internal,
                           &SbKNKD_SensorTestFailed);

   }
   if (SbKNKD_SensorTestComplete_Internal != CbFALSE)
   {
       ScKNKD_SensorFailCounter = V_COUNT_WORD (0);
       VcKNKD_SensorSampleCounter = V_COUNT_WORD (0);
   }
   SbKNKD_SensorTestComplete |= SbKNKD_SensorTestComplete_Internal;
}

/********************************************************************
*
* Function:      EvalKNKD_EnableCriteria
*
* Description:   This process evaluates the knock circuit and Sensor
*                 diagnostic common enable criteria. 
*
* Parameters:    None
* Returns:       None
*********************************************************************/
static void EvalKNKD_EnableCriteria(void)
{  

    /*
    * This process handles the table lookup for both Knock Sensor
    * diagnostics. If the engine vacuum is too high, then both diagnostics
    * are disabled.  As engine RPM increases, the vibration level of the 
    * engine increases, and the output from the knock sensor also increases.
    * The sensor output must be expected to have increased before the 
    * diagnostic can be executed.  This  particular criteria affects both 
    * the Knock Sensor test and the Knock System test.  If the Knock System
    * or Knock Sensor test has failed this key on, disable the diagnostic,
    * so that both a Knock Sensor and Knock System failure is not reported.
    * If the Knock System test fails, the Knock Sensor test is likely to
    * fail and vice versa. 
    */

	SbKNKD_DsblgKeyOnFaultPresent = GetVIOS_KNKD_Disable_Fault();

 // if (GetVIOS_p_MnfdVac() <= usLookup_xy_us (&KtKNKD_p_EngVacThrsh,
      //                                      GetVIOS_9a_RPM_Rescale() ) 
     if( (GetVIOS_p_MnfdVac() <= Lookup_2D_W(GetVIOS_n_EngSpd(), 
	 	                                 RPM_W, 0, 0, 6400, 800, KtKNKD_p_EngVacThrsh))
     && (GetVIOS_CCESC_Enabled() != CbFALSE)
     && (SbKNKD_DsblgKeyOnFaultPresent == CbFALSE) 
     && (GetVIOS_IgnSt() == CeIGN_ON))
  {
     SbKNKD_CommonEnableCriteriaMet = CbTRUE; 

     /*
     * Description:   This process compares the engine speed to the
     * calibration for the Knock System Fault minimum RPM.  If the
     * engine speed is "good" and the common criteria are met, then the
     * Knock System Fault diagnostic will be met.
     */

     if ( GetVIOS_n_EngSpd() >= KfKNKD_n_EngSpdSystemEnblThrsh )

     {
       SbKNKD_SystemEnableCriteriaMet = CbTRUE;
     }
     else
     {
       SbKNKD_SystemEnableCriteriaMet = CbFALSE;
     }
     
     /*
     * Description:   This process compares the engine speed to the
     * calibration for the Knock Sensor Fault minimum RPM.  If the
     * engine speed is "good" and the common criteria are met, then the
     * Knock Sensor Fault diagnostic will be met.
     */

     if ( GetVIOS_n_EngSpd() >= KfKNKD_n_EngSpdSensorEnblThrsh )

     {
       SbKNKD_SensorEnableCriteriaMet = CbTRUE;
     }
     else
     {
       SbKNKD_SensorEnableCriteriaMet = CbFALSE;
     }
  }  
  else  /* Commmon Enable Contions not present */
  {
     SbKNKD_CommonEnableCriteriaMet = CbFALSE;
     SbKNKD_SystemEnableCriteriaMet = CbFALSE;
     SbKNKD_SensorEnableCriteriaMet = CbFALSE;
  }
}  

/********************************************************************
*
* Function:      EvalKNKD_SystemShort
*
* Description:  The knock system should be calibrated such that each
* cylinder A/D reading should be above a low calibration limit under
* normal conditions.  If the system output is shorted to ground, ALL
* of the A/D readings will be below the calibrated low limit.
*
* Parameters:    None
* Returns:       True if system short test is failing.
*********************************************************************/
static TbBOOLEAN EvalKNKD_SystemShort(void)
{
   T_COUNT_BYTE LcKNKD_CylIndex;
   T_PERCENTa LfKNKD_Pct_MaxESC;
   
   /*  first, since max must equal at least one of the intensities,
       assume that the first is the one and set it to the first  */

   LfKNKD_Pct_MaxESC = GetVIOS_Pct_CCESC_IntensAverage(V_COUNT_BYTE(0));

   /*  second, compare to the rest of the intensities, and reset the
       value depending on which exceed the previous ones.  */

   for (LcKNKD_CylIndex = V_COUNT_BYTE(1);
        LcKNKD_CylIndex < CcSYST_NUM_OF_CYLINDERS;
        LcKNKD_CylIndex++)
   {
     if (GetVIOS_Pct_CCESC_IntensAverage(LcKNKD_CylIndex)
                                      > LfKNKD_Pct_MaxESC)
     {
       LfKNKD_Pct_MaxESC =
                   GetVIOS_Pct_CCESC_IntensAverage(LcKNKD_CylIndex);
     }
   }
   return (LfKNKD_Pct_MaxESC < KfKNKD_Pct_SystemIntensThrshLo);
}      

/********************************************************************
*
* Function:      EvalKNKD_SystemHigh
*
* Description:  The knock system should be calibrated such that the
* average noise output, for each cylinder, should be below a high A/D
* value.  If the cylinder average noise outputs are above the calibrated
* high A/D value for more than a calibrated number of events, then the
* system will be considered either out of control or shorted to vcc.
*
* Parameters:    None
* Returns:       True if system high test is failing.
*********************************************************************/
static TbBOOLEAN EvalKNKD_SystemHigh(void)
{
     return ( GetVIOS_Pct_CCESC_IntensAverage( GetVIOS_CylNumZeroBased() ) >
              KfKNKD_Pct_SystemIntnsAvThrshHi );
//return (CbTRUE);
}

/********************************************************************
*
* Function:      EvalKNKD_SensorProcessing
*
* Description:   This process depends on individual cylinder Knock
* Sensor activity.  If all values for all cylinders are within too
* small a range, then the Sensor is not properly processing individual
* cylinder information.  This process will find the maximum and
* minimum values and compare the difference between these numbers to
* a calibration.  If the difference is less than the calibration,
* then the failure flag will be set to TRUE.
*
* Parameters:    None
* Returns:       True if sensor test is failing.
*********************************************************************/
static TbBOOLEAN EvalKNKD_SensorProcessing(void)
{
   T_COUNT_BYTE LcKNKD_CylIndex;
   T_PERCENTa   LcKNKD_IntensUnfltThrshMax,
                LcKNKD_IntensUnfltThrshMin;
   /*  first, since max and min must equal at least one of the
       intensities, assume that the first is the one and set them
       both to the first  */

   LcKNKD_IntensUnfltThrshMax =
                   GetVIOS_Pct_CCESC_IntUnfilt( V_COUNT_BYTE(0) );
   LcKNKD_IntensUnfltThrshMin = LcKNKD_IntensUnfltThrshMax;
   LfKNKD_ESCGainMin = V_DECIBELS(26);
   /*  second, compare the max and the min to the each of the rest of
       the intensities, and reset their values depending on which cylinder
       intensities exceed the previous max and min.  */

   for (LcKNKD_CylIndex = V_COUNT_BYTE(1);
        LcKNKD_CylIndex < CcSYST_NUM_OF_CYLINDERS;
        LcKNKD_CylIndex++)
        {
          if (GetVIOS_Pct_CCESC_IntUnfilt(LcKNKD_CylIndex) >
                                        LcKNKD_IntensUnfltThrshMax)
          {
            LcKNKD_IntensUnfltThrshMax =
                      GetVIOS_Pct_CCESC_IntUnfilt(LcKNKD_CylIndex);
          }
          else
          {
             if (GetVIOS_Pct_CCESC_IntUnfilt(LcKNKD_CylIndex) <
                                          LcKNKD_IntensUnfltThrshMin)
             {
              LcKNKD_IntensUnfltThrshMin =
                        GetVIOS_Pct_CCESC_IntUnfilt(LcKNKD_CylIndex);
             }
             else
             {
                /* do nothing */
             }
          }
          LfKNKD_ESCGainMin = Min( LfKNKD_ESCGainMin, GetKNOC_ESCGain(LcKNKD_CylIndex) );
        }
   SfKNKD_Pct_ADESC_Delta = LcKNKD_IntensUnfltThrshMax - LcKNKD_IntensUnfltThrshMin;
   return ( TbBOOLEAN )((SfKNKD_Pct_ADESC_Delta < KfKNKD_Pct_SensorIntnsDeltThrsh) &&
                           (LfKNKD_ESCGainMin > KfKNKD_FaultDetectGain));

}
#endif

/******************************************************************************
*
* Revision history: 
*
* Rev.  YYMMDD Who RSM# Changes                                       
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/

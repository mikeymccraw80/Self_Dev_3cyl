/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "es_types.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
#include "hal.h"
#include "hal_os.h"
#include "HLS.h"
#include "esc_cal.h"
#include "intr_ems.h"
#include "v_esc.h"

/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/***************************defines**********************/

/*--- The number of previous high res. RPM entries is limited ---*/
/*--- to that which will hold  msec worth.                    ---*/
#define NUM_OF_PREV_H_RPM_ENTRIES ( (uint8_t)((0.250 / Prec_HiResRPM_Period_Sec) ))
/**********************************************************************/
/* Determines the high resolution engine speed (resolution            */
/* is 1 RPM/bit) and maintains a buffer of the last 16 high           */
/* resolution engine speed values.                                    */
/**********************************************************************/
#define High_Res_RPM_Factor \
   ( ( uint32_t )( 60000000 / Prec_RPM_Hi_Res_W / 4 / 2 ) )

/*--- 60 sec/min * 1000000 usec/sec * 1/2 Rev/HalfRev  ---*/

#define ECT_HLS_LLD_Factor    (((Min_Degrees_C_B)-(-48))/Prec_Degrees_C_B)


#define PE_TPSEnableThreshold(threshold, hysteresis)    ( (Percent_B)( Power_Enrichment_Met_BIT ? \
                                              (threshold) : \
                                              FixAddHighLimit( threshold, hysteresis, Percent_B, \
                                              FixDefConst( Max_Percent_B, Percent_B ) )))



/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
Degrees_C_B             Coolant_Temperature_ ;
kPa_W                       Manifold_Air_Pressure_W_;
Percent_B                  Throttle_Position_;
kPa_B                        MAPADFiltered_B ;
kPa_B                        MAPStartup ;
Degrees_C_B             Manifold_Air_Temperature_ ;
Seconds_Low             Engine_Run_Time_ ;
bool                          Engine_Run_Spark_;
bool                          Power_Enrichment_Met_BIT;
kPa_W_NonLinear                MapWithSlopeChangeAt80kPa ;
/* ============================================================================ *\
 * Local function prototypes.
\* ============================================================================ */

/* array size is NUM_OF_PREV_H_RPM_ENTRIES  */
RPM_Hi_Res_W  HiRes_RPM_Buffer[NUM_OF_PREV_H_RPM_ENTRIES] ;
uint8_t     HiRes_RPM_BufferPtr ;
RPM_Hi_Res_W  Hi_Res_Engine_Speed_Var ;
Every_4th_Loop_Sec_W           PE_Delay_Timer ;
Every_4th_Loop_Sec_W           PEDelayTimerForEveryTime;
/* ============================================================================ *\
 * Function definitions
 * ============================================================================ */

/********************** Converted inline static end **************************/


/*****************************************************************************/
/*                                                                           */
/* FUNCTION: CalculateDualSlopeMapVar                                        */
/*                                                                           */
/* DESCRIPTION:                                                              */
/*    Calculate the dual slope map varaible.                                 */
/*    The function converts a variable that have a constant precision over   */
/*    the whole range to a variable that has  the same precision as the      */
/*    input variable below the breakpoint and a precision half of the        */
/*    input variable above the breakpoint.                                   */
/*                                                                           */
/* GLOBAL: Nil                                                               */
/*****************************************************************************/

kPa_W_NonLinear CalculateDualSlopeMapVar( kPa_W MapLinear, kPa_W Breakpoint )
{
    kPa_W_NonLinear map_nonlinear ;

    /*--- No fixed point macro can be used to perform this calculation ---*/
    /*--- as the type kPa_W_NonLinear as a precision which is not      ---*/
    /*--- constant over the whole range of the type.                   ---*/
    if ( MapLinear <= Breakpoint )
    {
        map_nonlinear = ( kPa_W_NonLinear )MapLinear ;
    }
    else
    {
        map_nonlinear = ( kPa_W_NonLinear )( Breakpoint + ( MapLinear - Breakpoint )*2 ) ;
    }
    return map_nonlinear ;
}                                                          /* End of CalculateDualSlopeMapVar */



/******************************************************************************/
/*                                                                            */
/* FUNCTION: Calculate_HiRes_Engine_Speed                                     */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*      This function is called every 15.6 ms, and it updates the HiRes_      */
/*      RPM_Buffer with RPM, and it forms this buffer as circular one.        */
/*      So the latest RPM will be always previous entry.                      */
/*      It determines the high resolution engine speed (  resolution is       */
/*      1 RPM/bit ) and maintains a buffer of the last 16 high resolution     */
/*      engine speed values.                                                  */
/*                                                                            */
/* GLOBAL: HiRes_RPM_BufferPtr,                                               */
/*         HiRes_RPM_Buffer,                                                  */
/*         Hi_Res_Engine_Speed_Var                                            */
/******************************************************************************/

 void Calculate_HiRes_Engine_Speed( void )
{
    /* update input pointer of history buffer */
    if ( HiRes_RPM_BufferPtr != 0 )
    {
        HiRes_RPM_BufferPtr-- ;
    }
    else
    {
        /* If index is zero, point into maximum buffer position to make
         buffer as circular */
        HiRes_RPM_BufferPtr = NUM_OF_PREV_H_RPM_ENTRIES - 1 ;
    }

    /* Save old value in buffer */
    HiRes_RPM_Buffer[HiRes_RPM_BufferPtr] = Hi_Res_Engine_Speed_Var ;
    Hi_Res_Engine_Speed_Var = HAL_Eng_Get_Engine_Speed()/8; 
    /* non standard fixed point operation ( division )! G.H 22-2-95 */

}

 void Initialize_HiRes_Engine_Speed( void )
{

    Hi_Res_Engine_Speed_Var = FixDefConst( Min_RPM_Hi_Res_W, RPM_Hi_Res_W ) ;
    /* Initialize High resolution RPM Buffer index to zero. */
    HiRes_RPM_BufferPtr = 0 ;
}

 void Calculate_Esc_Input_1000ms(void)
{
/*calculate engine speed*/
  if(HAL_Eng_Get_Engine_Speed()> FixDefConst(450.0, RPM_W))
  {
    Engine_Run_Time_++;
  }
  else
  {
     Engine_Run_Time_=0;
  }
 /*Engine Run Spark*/
  if(Engine_Run_Time_> 3)
  {
    Engine_Run_Spark_ = true;
  }	
  else
  {
   Engine_Run_Spark_= false;
  } 	
}

 void Calculate_Esc_Input_10ms(void)
{
   //Throttle_Position_ =(unsigned char)( ((unsigned long)TpPos_b)*256/255);
  Throttle_Position_ = (unsigned char)TpPos_b;
   MAPADFiltered_B = (unsigned char)(((unsigned long)Pmap_b*10000)/(unsigned long)(Prec_kPa_B*10000)) - (unsigned char)(Min_kPa_B/Prec_kPa_B);
   Manifold_Air_Pressure_W_ =(unsigned short)(Pmap /5);
   
   /* Convert chery coolant to delphi coolant */
   if( ((CHERY_DEG_T)TmLin) >= ( FixDefConst(Min_Degrees_C_B,CHERY_DEG_T) ))
   {
     Coolant_Temperature_ = (unsigned char)TmLin-(unsigned char)ECT_HLS_LLD_Factor-1;//(-1) fixpoint
   }
   else
   {
     Coolant_Temperature_ = FixDefConst(Min_Degrees_C_B,Degrees_C_B);
   }
   /* Convert chery MAT to delphi MAT */
   if( ((CHERY_DEG_T)Ta) >= ( FixDefConst(Min_Degrees_C_B,CHERY_DEG_T) ))
   {
     Manifold_Air_Temperature_ = (unsigned char)Ta-(unsigned char)ECT_HLS_LLD_Factor-1;//(-1) fixpoint
   }
   else
   {
     Manifold_Air_Temperature_ = FixDefConst(Min_Degrees_C_B,Degrees_C_B);
   }
   MapWithSlopeChangeAt80kPa = CalculateDualSlopeMapVar( Manifold_Air_Pressure_W_, FixDefConst( 80.0, kPa_W ) ) ;

}

/**************************************************************************/
/*                                                                        */
/* FUNCTION: PEConditionsMetDetermination                                 */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*         Determine if PE Conditions are present                         */
/*                                                                        */
/* GLOBAL: Crank_AF_Timeout_NVVar                                         */
/**************************************************************************/


 bool PEConditionsMetDetermination( void )
{
   Percent_B       	  PE_TPS_thres ;
   Percent_B	     	  PE_TPS_hyst;
   Every_4th_Loop_Sec_W   PE_Delay_thres ;                      /* every 4th loop */
   Every_4th_Loop_Sec_W   PEDelayTimerForEveryTime_Thres;           /* every 4th loop */
 

      PE_TPS_thres = ( Percent_B )Lookup_2D_B( HAL_Eng_Get_Engine_Speed(), Prec_RPM_W, 0.0, 0.0, 6400.0, 800.0,
                                             K_PE_TPS_Load_Thres_2D) ;
      PE_TPS_hyst = K_Fuel_TPS_Hysteresis_For_PE;            
      PE_Delay_thres = ( Every_4th_Loop_Sec_W )Lookup_2D_W( HAL_Eng_Get_Engine_Speed(), Prec_RPM_W, 0.0, 0.0, 6400.0, 800.0,
                                                              F_PE_Delay_Time_2D ) ;                                                          
 
                              
   PEDelayTimerForEveryTime_Thres = ( Every_4th_Loop_Sec_W )Lookup_2D_W( HAL_Eng_Get_Engine_Speed(), Prec_RPM_W, 0.0, 0.0, 6400.0, 800.0,
                                                                       F_EveryPE_DelayTime_2D ) ; 
                                                                       
   if ( Throttle_Position_Value() > PE_TPSEnableThreshold(PE_TPS_thres, PE_TPS_hyst) )
   {  
       if (Power_Enrichment_Met_BIT == false)
       {
           if ( ( PE_Delay_Timer > PE_Delay_thres )
               &&( PEDelayTimerForEveryTime >= PEDelayTimerForEveryTime_Thres )) 
           {
               Power_Enrichment_Met_BIT = true ;
           }
           else
           {
               if ( PE_Delay_Timer <= PE_Delay_thres )
               {
                   PE_Delay_Timer++ ;
               }    
               if( PEDelayTimerForEveryTime < PEDelayTimerForEveryTime_Thres )
               {
                   PEDelayTimerForEveryTime++;
               }
           }
       }
       else
       {
           PEDelayTimerForEveryTime = 0;
       }
   } 
   else
   {
       Power_Enrichment_Met_BIT = false ;
       PEDelayTimerForEveryTime = 0;
   }
   return (bool) Power_Enrichment_Met_BIT ;
}  

/*===========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/*===========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---     ----------------------------------       */
/*===========================================================================*/



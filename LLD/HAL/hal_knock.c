
#include "hwiocald.h"
#include "hal_knock.h"
#include "dd_knock_interface.h"


/*===========================================================================*\
 * /-----------------------------------------------------------------------\
 * | DSP KNOCK Functionality
 * \-----------------------------------------------------------------------/
\*===========================================================================*/


void GetIO_MultiKnock_Intensity_Value(EMS_MultiKnock_Window_T window, T_PERCENT_MULTb* values)
{
   uint8_t i;
   uint32_t results[MULTIKNOCK_NUM_FILTERS];

   if (MULTIKNOCK_WINDOW_1 == window) {
      KNOCK_Get_MultiIntensity_Value1(  &results[0] );
   } else if (MULTIKNOCK_WINDOW_2 == window) {
      KNOCK_Get_MultiIntensity_Value2( &results[0] );
   } else {
      for (i=0; i<MULTIKNOCK_NUM_FILTERS; i++) {
          results[i]=0;
      }
   }
   
  for (i=0; i<MULTIKNOCK_NUM_FILTERS; i++) 
  {
       results[i]  = results[i] >> KyHWIO_Knock_Preshift;
	   
       if(KNOCK_Get_High_Gain())
       {
          results[i] = results[i] >> 2;
        }	
	 if (results[i] > 0xffff) 
	 {   //not sure if MIN macro is available here
            results[i] = 0xffff;
        }
	 values[i] = (T_PERCENT_MULTb)(results[i]);
   }
	   

}


void SetIO_MultiKnock_High_Gain(uint8_t in_gain)
{
    KNOCK_Set_High_Gain( in_gain  );
}



void SetIO_MultiKnock_Window_Start(EMS_MultiKnock_Window_T window, T_CRANK_ANGLEa  angle)
{
   if (MULTIKNOCK_WINDOW_1==window) {
      KNOCK_Set_MultiWindow_Start1(  angle, S_CRANK_ANGLEa );
   } else if (MULTIKNOCK_WINDOW_2==window) {
      KNOCK_Set_MultiWindow_Start2( angle, S_CRANK_ANGLEa );
   }
}

void SetIO_MultiKnock_Window_End(EMS_MultiKnock_Window_T window, T_CRANK_ANGLEa angle)
{
   if (MULTIKNOCK_WINDOW_1==window) {
      KNOCK_Set_MultiWindow_End1(  angle, S_CRANK_ANGLEa );
   } else if (MULTIKNOCK_WINDOW_2==window) {
      KNOCK_Set_MultiWindow_End2( angle, S_CRANK_ANGLEa );
   }
}

void SetIO_MultiKnock_Window_Length(EMS_MultiKnock_Window_T window, T_MILLISECONDSb in_window_length)
{
     KNOCK_Set_Window_Length(in_window_length, S_MILLISECONDSb );
}




T_PERCENT_MULTb GetIO_MultiKnock_Raw_Sample(EMS_MultiKnock_Window_T window)
{
   T_PERCENT_MULTb ret;
   if (MULTIKNOCK_WINDOW_1 == window) {
      ret = KNOCK_Get_MultiLast_Analog_Conversion1(  );
   } else if (MULTIKNOCK_WINDOW_2 == window) {
      ret = KNOCK_Get_MultiLast_Analog_Conversion2( );
   } else {
      ret = 0;
   }
   return ret;
}




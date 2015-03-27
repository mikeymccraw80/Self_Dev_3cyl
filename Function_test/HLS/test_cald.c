
/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
 
#include "test_cald.h"
/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/


#if 1

/* ============================================================================ *\
 * global variabes used by both lld and hls.
\* ============================================================================ */



/*
*| test_cald.{
*|   KT_DO {
*|     : is_calconst;
*|     : description = "Discrete output for test ";
*|     .VIS_SWITCH
*|     {
*|        :type = uint8;
*|        :description = "vis switch output for test";
*|        :units = "0 TO 1";
*|     }
*|     .START_MOTR_RLY
*|     {
*|        :type = uint8;
*|        :description = "start motor relay output for test";
*|        :units = "0 TO 1";
*|     }
*|     .R_LINE
*|     {
*|        :type = uint8;
*|        :description = "r_line output for test";
*|        :units = "0 TO 1";
*|     }
*|     .AC_CLUTCH
*|     {
*|        :type = uint8;
*|        :description = "ac clutch output for test";
*|        :units = "0 TO 1";
*|     }
*|     .SVS_LAMP
*|     {
*|        :type = uint8;
*|        :description = "svs lamp output for test";
*|        :units = "0 TO 1";
*|     }
*|     .MIL_LAMP
*|     {
*|        :type = uint8;
*|        :description = "mil lamp output for test";
*|        :units = "0 TO 1";
*|     }
*|     .MAIN_RELAY
*|     {
*|        :type = uint8;
*|        :description = "main relay output for test";
*|        :units = "0 TO 1";
*|     }
*|     .FUEL_PUMP
*|     {
*|        :type = uint8;
*|        :description = "fuel pump output for test";
*|        :units = "0 TO 1";
*|     }
*|     .FAN2
*|     {
*|        :type = uint8;
*|        :description = "fan2 output for test";
*|        :units = "0 TO 1";
*|     }
*|     .FAN1
*|     {
*|        :type = uint8;
*|        :description = "fan1 output for test";
*|        :units = "0 TO 1";
*|     }
*|    }
*|   }
*/
const DO_test_type KT_DO={
  1,1,1,1,1,1,1,1,1,0
};

/*
*| test_cald.{
*|   KT_PO_O2_heater_1 {
*|     : is_calconst;
*|     : description = "O2 heater_1 output period, enable and PWM duty for test ";
*|   .period
*|    {
*|        :type = uint8;
*|        :description = "O2 heater_1 period for test";
*|        :units = "ms";
*|    }
*|   .B_enable
*|    {
*|        :type = uint8;
*|        :description = "O2 heater_1 enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .duty
*|    {
*|        :type = uint8;
*|        :description = "O2 heater_1 duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/
const PO_test_type KT_PO_O2_heater_1={

    10, 1,   25

};

/*
*| test_cald.{
*|   KT_PO_O2_heater_2 {
*|     : is_calconst;
*|     : description = "O2 heater_2 output period, enable and PWM duty for test ";
*|   .period
*|    {
*|        :type = uint8;
*|        :description = "O2 heater_2 period for test";
*|        :units = "ms";
*|    }
*|   .B_enable
*|    {
*|        :type = uint8;
*|        :description = "O2 heater_2 enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .duty
*|    {
*|        :type = uint8;
*|        :description = "O2 heater_2 duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/
const PO_test_type KT_PO_O2_heater_2={

    10, 1,   25

};

/*
*| test_cald.{
*|   KT_PO_PURGE {
*|     : is_calconst;
*|     : description = "PURGE output period, enable and PWM duty for test ";
*|   .period
*|    {
*|        :type = uint8;
*|        :description = "PURGE period for test";
*|        :units = "ms";
*|    }
*|   .B_enable
*|    {
*|        :type = uint8;
*|        :description = "PURGE enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .duty
*|    {
*|        :type = uint8;
*|        :description = "PURGE duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/
const PO_test_type KT_PO_PURGE={

  10,  1,   25

};

/*
*| test_cald.{
*|   KT_PO_ECT {
*|     : is_calconst;
*|     : description = "ECT output period, enable and PWM duty for test ";
*|   .period
*|    {
*|        :type = uint8;
*|        :description = "ECT period for test";
*|        :units = "ms";
*|    }
*|   .B_enable
*|    {
*|        :type = uint8;
*|        :description = "ECT enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .duty
*|    {
*|        :type = uint8;
*|        :description = "ECT duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/
const PO_test_type KT_PO_ECT={

     10, 1,   25

};

/*
*| test_cald.{
*|   KT_PO_EGR {
*|     : is_calconst;
*|     : description = "EGR output period, enable and PWM duty for test, not implemented";
*|   .period
*|    {
*|        :type = uint8;
*|        :description = "EGR period for test";
*|        :units = "ms";
*|    }
*|   .B_enable
*|    {
*|        :type = uint8;
*|        :description = "EGR enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .duty
*|    {
*|        :type = uint8;
*|        :description = "EGR duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/
const PO_test_type KT_PO_EGR={

   10, 1,   25

};

/*
*| test_cald.{
*|   KT_PO_TACHO {
*|     : is_calconst;
*|     : description = "TACHO output period, enable and PWM duty for test, not implemented";
*|   .period
*|    {
*|        :type = uint8;
*|        :description = "TACHO period for test";
*|        :units = "ms";
*|    }
*|   .B_enable
*|    {
*|        :type = uint8;
*|        :description = "TACHO enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .duty
*|    {
*|        :type = uint8;
*|        :description = "TACHO duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/
const PO_test_type KT_PO_TACHO={

     10, 1,   25

};

/*
*| test_cald.{
*|   KT_PO_FUEL_CSP {
*|     : is_calconst;
*|     : description = "FUEL_COMSUPTION output period, enable and PWM duty for test, not implemented";
*|   .period
*|    {
*|        :type = uint8;
*|        :description = "FUEL_COMSUPTION period for test";
*|        :units = "ms";
*|    }
*|   .B_enable
*|    {
*|        :type = uint8;
*|        :description = "FUEL_COMSUPTION enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .duty
*|    {
*|        :type = uint8;
*|        :description = "FUEL_COMSUPTION duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/
const PO_test_type KT_PO_FUEL_CSP={

   10, 1,   25

};

/*
*| test_cald.{
*|   KT_PO_VVT1 {
*|     : is_calconst;
*|     : description = "VVT1 output period, enable and PWM duty for test ";
*|   .period
*|    {
*|        :type = uint8;
*|        :description = "VVT1 period for test";
*|        :units = "ms";
*|    }
*|   .B_enable
*|    {
*|        :type = uint8;
*|        :description = "VVT1 enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .duty
*|    {
*|        :type = uint8;
*|        :description = "VVT1 duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/
const PO_test_type KT_PO_VVT1 ={

    10, 1,   25

};
/*
*| test_cald.{
*|   KT_PO_VVT2 {
*|     : is_calconst;
*|     : description = "VVT2 output period, enable and PWM duty for test ";
*|   .period
*|    {
*|        :type = uint8;
*|        :description = "VVT2 period for test";
*|        :units = "ms";
*|    }
*|   .B_enable
*|    {
*|        :type = uint8;
*|        :description = "VVT2 enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .duty
*|    {
*|        :type = uint8;
*|        :description = "VVT2 duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/
const PO_test_type KT_PO_VVT2 ={

   10, 1,   25

};
/*
*| test_cald.{
*|   KT_InjA {
*|     : is_calconst;
*|     : description = "fuel inject A cal for test ";
*|   .enable
*|    {
*|        :type = uint8;
*|        :description = "inject enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .inj_time
*|    {
*|        :type = uint32_t;
*|        :description = "inject time for test";
*|        :units = "us";
*|    }
*|   .inj_end_angle
*|    {
*|        :type = uint8_t;
*|        :description = "inject end angle for test";
*|        :units = "2.8125deg/count";
*|    }
*|   .B_post_inj
*|    {
*|        :type = uint8_t;
*|        :description = "post inject for test";
*|        :units = "";
*|    }
*|   .post_inj_time
*|    {
*|        :type = uint16_t;
*|        :description = "post inject time for test";
*|        :units = "us";
*|    }
*|   .abort_angle
*|    {
*|        :type = uint8_t;
*|        :description = "abort angle for test";
*|        :units = "";
*|    }
*|  }
*|}
*/  
const inj_sig_test_type KT_InjA ={


   1,4000,0,0,0,0

};

/*
*| test_cald.{
*|   KT_InjB {
*|     : is_calconst;
*|     : description = "fuel inject B cal for test ";
*|   .enable
*|    {
*|        :type = uint8;
*|        :description = "inject enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .inj_time
*|    {
*|        :type = uint32_t;
*|        :description = "inject time for test";
*|        :units = "us";
*|    }
*|   .inj_end_angle
*|    {
*|        :type = uint8_t;
*|        :description = "inject end angle for test";
*|        :units = "2.8125deg/count";
*|    }
*|   .B_post_inj
*|    {
*|        :type = uint8_t;
*|        :description = "post inject for test";
*|        :units = "";
*|    }
*|   .post_inj_time
*|    {
*|        :type = uint16_t;
*|        :description = "post inject time for test";
*|        :units = "us";
*|    }
*|   .abort_angle
*|    {
*|        :type = uint8_t;
*|        :description = "abort angle for test";
*|        :units = "";
*|    }
*|  }
*|}
*/  
const inj_sig_test_type KT_InjB ={


   1,4000,0,0,0,0

};
/*
*| test_cald.{
*|   KT_InjC {
*|     : is_calconst;
*|     : description = "fuel inject C cal for test ";
*|   .enable
*|    {
*|        :type = uint8;
*|        :description = "inject enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .inj_time
*|    {
*|        :type = uint32_t;
*|        :description = "inject time for test";
*|        :units = "us";
*|    }
*|   .inj_end_angle
*|    {
*|        :type = uint8_t;
*|        :description = "inject end angle for test";
*|        :units = "2.8125deg/count";
*|    }
*|   .B_post_inj
*|    {
*|        :type = uint8_t;
*|        :description = "post inject for test";
*|        :units = "";
*|    }
*|   .post_inj_time
*|    {
*|        :type = uint16_t;
*|        :description = "post inject time for test";
*|        :units = "us";
*|    }
*|   .abort_angle
*|    {
*|        :type = uint8_t;
*|        :description = "abort angle for test";
*|        :units = "";
*|    }
*|  }
*|}
*/  
const inj_sig_test_type KT_InjC ={


   1,4000,0,0,0,0

};

/*
*| test_cald.{
*|   KT_InjD {
*|     : is_calconst;
*|     : description = "fuel inject D cal for test ";
*|   .enable
*|    {
*|        :type = uint8;
*|        :description = "inject enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .inj_time
*|    {
*|        :type = uint32_t;
*|        :description = "inject time for test";
*|        :units = "us";
*|    }
*|   .inj_end_angle
*|    {
*|        :type = uint8_t;
*|        :description = "inject end angle for test";
*|        :units = "2.8125deg/count";
*|    }
*|   .B_post_inj
*|    {
*|        :type = uint8_t;
*|        :description = "post inject for test";
*|        :units = "";
*|    }
*|   .post_inj_time
*|    {
*|        :type = uint16_t;
*|        :description = "post inject time for test";
*|        :units = "us";
*|    }
*|   .abort_angle
*|    {
*|        :type = uint8_t;
*|        :description = "abort angle for test";
*|        :units = "";
*|    }
*|  }
*|}
*/  
const inj_sig_test_type KT_InjD ={


   1,4000,0,0,0,0

};

/*
*| test_cald.{
*|   KT_IgnA {
*|     : is_calconst;
*|     : description = "Spark A cal for test ";
*|   .enable
*|    {
*|        :type = uint8_t;
*|        :description = "spark enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .ign_angle
*|    {
*|        :type = uint8_t;
*|        :description = "ign angle for test";
*|        :units = "0.75deg/count";
*|    }
*|   .dwell_time
*|    {
*|        :type = uint16_t;
*|        :description = "dwell time for test";
*|        :units = "us";
*|    }
*|   .follow_up_sparks
*|    {
*|        :type = uint8_t;
*|        :description = "follow_up_sparks for test";
*|        :units = "";
*|    }
*|   .dwell_time_of_follow_up_sparks
*|    {
*|        :type = uint16_t;
*|        :description = "dwell_time_of_follow_up_sparks for test";
*|        :units = " ";
*|    }
*|   .break_time_of_follow_up_sparks
*|    {
*|        :type = uint16_t;
*|        :description = "break_time_of_follow_up_sparks for test";
*|        :units = "";
*|    }
*|  }
*|}
*/ 
const ign_sig_test_type KT_IgnA ={

   1,128,4000,0,0,0

};

/*
*| test_cald.{
*|   KT_IgnB {
*|     : is_calconst;
*|     : description = "Spark B cal for test ";
*|   .enable
*|    {
*|        :type = uint8_t;
*|        :description = "spark enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .ign_angle
*|    {
*|        :type = uint8_t;
*|        :description = "ign angle for test";
*|        :units = "0.75deg/count";
*|    }
*|   .dwell_time
*|    {
*|        :type = uint16_t;
*|        :description = "dwell time for test";
*|        :units = "us";
*|    }
*|   .follow_up_sparks
*|    {
*|        :type = uint8_t;
*|        :description = "follow_up_sparks for test";
*|        :units = "";
*|    }
*|   .dwell_time_of_follow_up_sparks
*|    {
*|        :type = uint16_t;
*|        :description = "dwell_time_of_follow_up_sparks for test";
*|        :units = " ";
*|    }
*|   .break_time_of_follow_up_sparks
*|    {
*|        :type = uint16_t;
*|        :description = "break_time_of_follow_up_sparks for test";
*|        :units = "";
*|    }
*|  }
*|}
*/ 
const ign_sig_test_type KT_IgnB ={

   1,128,4000,0,0,0

};

/*
*| test_cald.{
*|   KT_IgnC {
*|     : is_calconst;
*|     : description = "Spark C cal for test ";
*|   .enable
*|    {
*|        :type = uint8_t;
*|        :description = "spark enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .ign_angle
*|    {
*|        :type = uint8_t;
*|        :description = "ign angle for test";
*|        :units = "0.75deg/count";
*|    }
*|   .dwell_time
*|    {
*|        :type = uint16_t;
*|        :description = "dwell time for test";
*|        :units = "us";
*|    }
*|   .follow_up_sparks
*|    {
*|        :type = uint8_t;
*|        :description = "follow_up_sparks for test";
*|        :units = "";
*|    }
*|   .dwell_time_of_follow_up_sparks
*|    {
*|        :type = uint16_t;
*|        :description = "dwell_time_of_follow_up_sparks for test";
*|        :units = " ";
*|    }
*|   .break_time_of_follow_up_sparks
*|    {
*|        :type = uint16_t;
*|        :description = "break_time_of_follow_up_sparks for test";
*|        :units = "";
*|    }
*|  }
*|}
*/ 
const ign_sig_test_type KT_IgnC ={

   1,128,4000,0,0,0

};

/*
*| test_cald.{
*|   KT_IgnD {
*|     : is_calconst;
*|     : description = "Spark D cal for test ";
*|   .enable
*|    {
*|        :type = uint8_t;
*|        :description = "spark enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .ign_angle
*|    {
*|        :type = uint8;
*|        :description = "ign angle for test";
*|        :units = "0.75deg/count";
*|    }
*|   .dwell_time
*|    {
*|        :type = uint16_t;
*|        :description = "dwell time for test";
*|        :units = "us";
*|    }
*|   .follow_up_sparks
*|    {
*|        :type = uint8_t;
*|        :description = "follow_up_sparks for test";
*|        :units = "";
*|    }
*|   .dwell_time_of_follow_up_sparks
*|    {
*|        :type = uint16_t;
*|        :description = "dwell_time_of_follow_up_sparks for test";
*|        :units = " ";
*|    }
*|   .break_time_of_follow_up_sparks
*|    {
*|        :type = uint16_t;
*|        :description = "break_time_of_follow_up_sparks for test";
*|        :units = "";
*|    }
*|  }
*|}
*/ 
const ign_sig_test_type KT_IgnD ={

   1,128,4000,0,0,0

};


/*
*| test_cald.{
*|   KT_etc {
*|     : is_calconst;
*|     : description = "etc signal for test ";
*|   .enable
*|    {
*|        :type = uint8_t;
*|        :description = "etc enable for test";
*|        :units = "0 TO 1";
*|    }
*|   .direction
*|    {
*|        :type = uint8_t;
*|        :description = "ETC motor rotate direction control for test";
*|        :units = "0 to 1";
*|    }
*|   .duty
*|    {
*|        :type = uint16_t;
*|        :description = "etc signal duty for test";
*|        :units = "";
*|    }
*|  }
*|}
*/ 

const etc_sig_test_type KT_etc ={


 true,false,32768


};

#endif
/*===========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/*===========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---     ----------------------------------       */
/*===========================================================================*/

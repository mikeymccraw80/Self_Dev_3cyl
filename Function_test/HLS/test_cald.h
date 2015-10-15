#ifndef test_cald_H
#define test_cald_H

#include "reuse.h"



#if 1


#define CcSYST_NUM_OF_CYLINDERS 3


typedef struct {
				
	uint16_t  VIS_SWITCH: 1;
    uint16_t  START_MOTR_RLY: 1;
	uint16_t  R_LINE: 1;						
	uint16_t  AC_CLUTCH: 1;
    uint16_t  SVS_LAMP: 1;
	uint16_t  MIL_LAMP: 1;						
	uint16_t  MAIN_RELAY: 1;
    uint16_t  FUEL_PUMP: 1;
	uint16_t  FAN2: 1;						
	uint16_t  FAN1: 1;						

}DO_test_type;


typedef struct {

	uint8_t  period;
	uint8_t  B_enable;  /*enable the PWM channel   */
	uint8_t  duty;      /*PWM duty*/
    
}PO_test_type;




	
typedef struct{


   uint8_t  enable;
   uint32_t inj_time;
   uint8_t  inj_end_angle;
   uint8_t B_post_inj;
   uint16_t post_inj_time;
   uint8_t abort_angle;
   
}inj_sig_test_type;



typedef struct {
	
	uint8_t  enable;
	uint8_t  ign_angle;
	uint16_t dwell_time;
	uint8_t  follow_up_sparks;
	uint16_t dwell_time_of_follow_up_sparks;
	uint16_t break_time_of_follow_up_sparks;

} ign_sig_test_type;

typedef struct{


   uint8_t   enable;    //ETC enable contorl
   uint8_t   direction; //ETC motor rotate direction control
   uint16_t  duty;      //ETC Duty

   
}etc_sig_test_type;



extern const DO_test_type KT_DO;

extern const PO_test_type KT_PO_O2_heater_1;
extern const PO_test_type KT_PO_O2_heater_2;
extern const PO_test_type KT_PO_PURGE;
extern const PO_test_type KT_PO_ECT;
extern const PO_test_type KT_PO_EGR;
extern const PO_test_type KT_PO_TACHO;
extern const PO_test_type KT_PO_FUEL_CSP;
extern const PO_test_type KT_PO_VVT1;
extern const PO_test_type KT_PO_VVT2;

extern const inj_sig_test_type KT_InjA;
extern const inj_sig_test_type KT_InjB;
extern const inj_sig_test_type KT_InjC;
extern const inj_sig_test_type KT_InjD;

extern const ign_sig_test_type KT_IgnA;
extern const ign_sig_test_type KT_IgnB;
extern const ign_sig_test_type KT_IgnC;
extern const ign_sig_test_type KT_IgnD;
extern const etc_sig_test_type KT_etc;
#endif

#endif

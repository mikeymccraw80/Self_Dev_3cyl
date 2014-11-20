
/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "reuse.h"


/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
#include "HLS.h"
#include "hal_knock.h"
#include "intr_ems.h"
//#include "hal_di.h"


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */

uint16_t HLS_MAP_Value;
bool   HLS_MAP_Status;
uint16_t HLS_OXYGEN_Value;
bool  HLS_OXYGEN_Status;
uint16_t HLS_BATT_Value;
bool  HLS_BATT_Status;

uint16_t HLS_PBATT_Value;
bool  HLS_PBATT_Status;
uint16_t HLS_TA_Value;
bool  HLS_TA_Status;
uint16_t HLS_ECT_Value;
bool HLS_ECT_Status;
uint16_t HLS_TPS_Value;
bool HLS_TPS_Status;
uint8_t HLS_Filtered_AC_REQUEST_INPUT;
uint8_t HLS_Filtered_AC_PRESSURE_SWITCH;
uint8_t HLS_Filtered_DI_CAM_1;
uint8_t HLS_Filtered_DI_IGN_ON_OFF_SW;
uint8_t HLS_Filtered_DI_HEAD_LAMP;
unsigned char  TpPos_b;//tps=100*0.3922=39.22
unsigned char  Pmap_b;
unsigned char  Tm;//Tm= 200*0.75-48 =102
unsigned char  TmLin; 
unsigned char  Ta;
 uint8_t FCMEnd;
 uint8_t MafTst;
 uint16_t fLc;
 uint16_t fLcAd;
 uint8_t Pmap_b;
 unsigned short       Pmap;
 uint16_t N;
 uint16_t VspRaw;
 int8_t IgaOut;
 uint8_t TaLin;
 uint16_t Tpp;
 uint16_t uLsb;
 uint16_t uLsa;
 uint16_t KmQ1Mil;
 uint8_t Ub_b;
 uint8_t TpPos_b;
 uint16_t uTm;
 uint8_t uTa;
 uint16_t uPmap;
 uint16_t uTps;
 uint16_t Fl;
 uint32_t Ti;
 uint8_t Nstat;
 int16_t dN;
 int16_t dTqLosAd;
 int8_t dIgaKncDyn;
 uint8_t B_Knk;
 uint8_t Ld_b;
 uint16_t fAlt;
 int16_t  dTqIdcP;
 int16_t dTqIdcI;
 int8_t dIgaKnc[4];
 uint16_t FtCntEmis;
 uint16_t FtCntEmisCyl[4];
 int16_t RounFon;
 bool                 B_Fan1;
 bool                 B_Fan2;
 bool                 B_AcOn;
 uint16_t tLsbAfFlt;
 int8_t IntLcDwnI;
 uint8_t SsCatDwnM;
 uint8_t MxGrdLsaFit_b;
 uint8_t B_LsaRdy;
 int8_t Acl_b;
 uint16_t TcatInPre;
 uint16_t uTp1;
 uint16_t uTp2;
 uint16_t TpPosDpc;
 int16_t TpPos;
 uint16_t dpcpids;
 uint8_t B_dpcPids;
 uint16_t uPed1;
 uint16_t uPed2;
 uint8_t PedPos_b;
 uint16_t AngCamOvlapAdj;
 uint8_t fctCamOvlapIn_b;
 uint8_t fctCamOvlapOut_b;
 uint16_t DyCyPsIn;
 uint16_t DyCyPsOut;
 uint16_t DuCyPgOut;
 int16_t FlPg;
 uint16_t fPgRatDsr;
 int16_t fPgAdp;
 uint8_t Tam;
 uint8_t StcEtcAdpt;
 uint8_t ScSpr;
 uint8_t ScAntiIce;
 uint8_t ScLrn;
 uint8_t B_LrnSuc;
 uint16_t uTp1Lw;
 uint16_t uTp2Lw;
 uint16_t TpPosNlp;
 uint8_t FrBitsEtsm;
 uint8_t B_FofEtsm;
 
 uint16_t TqiMx;
 uint16_t TqiDsr;
 uint16_t TqiAct;
 uint16_t tStaEndL;
 uint16_t PedPos;
 uint16_t FlVofLS;
 uint8_t  TqActRespEtsm;
 uint8_t  TpPosDsr_b;
 uint8_t  TcatInPre_b;
 uint8_t  TqActEtsm;
 int16_t  TpPos1;
 int16_t  TpPos2;
 uint8_t  TpPosNlp_b;
 uint16_t uTpNlp1;
 uint8_t  uTp1Lw_b;
 int16_t  AngVlvInOp1;
 int16_t  AngDsrVlvOpIn;
 uint16_t ToileKel;
 uint16_t uPed2Dble;
 uint16_t TexBfPreCat;
 uint8_t  TmSta;
 uint16_t MafPcv;
 uint16_t FtCntEmisCyl_[4];
 int16_t  dTqIdcPD;
 uint16_t uLsbAdc;
 uint16_t uLsaAdc;
 uint8_t  B_Vis;
 uint8_t  B_Pmp;
 
Freeze_Frame_Elem  DIAG_STATUS_FREEZE_FRAME[3];
tele_type telem_data;
uint8_t 	count_DTCs_SID03;
uint16_t	DTCs_SID03[SY_FCMTSIZE];
bool	B_DiagInfoClrReq;
uint8_t 	count_DTCs_SID07;
uint16_t	DTCs_SID07[SY_FCMTSIZE];

/*the flowing is ISO14230 service 0x31&0x32 */
// uint8_t  SupFlagC0[4];    /* 0xC0  ID Support Flag($C1-$E0) */
// uint8_t  SupFlagE0[4];    /* 0xE0  ID Support Flag($E1-$FF) */
bool     B_Inj0Req;       /* 0xCC  KDS request #1cylinder injector test  */
bool     B_Inj0Stp;       /* 0xCC  KDS stop #1cylinder injector test  */
bool     B_Inj1Req;       /* 0xCD  KDS request #2cylinder injector test */
bool     B_Inj1Stp;       /* 0xCD  KDS stop #2cylinder injector test  */
bool     B_Inj2Req;       /* 0xCE  KDS request #3cylinder injector test  */
bool     B_Inj2Stp;       /* 0xCE  KDS stop #3cylinder injector test  */
bool     B_Inj3Req;       /* 0xCF  KDS request #4cylinder injector test  */
bool     B_Inj3Stp;       /* 0xCF  KDS stop #4cylinder injector test  */
bool     B_FulPReq;       /* 0xD4  KDS demand fuel pump test  */
bool     B_FulPStp;       /* 0xD4  KDS request fuel pump test   */
bool     B_MILReq;        /* 0xD5  Tester request MIL work 5S */
bool     B_MILStp;        /* 0xD5  Tester request stop test */
bool     B_SVSReq;        /* 0xD6  Tester request SVS work 5S */
bool     B_SVSStp;        /* 0xD6  Tester request stop test */
bool     B_Fan1Req;       /* 0xE5  KDS request low fan test  */
bool     B_Fan1Stp;       /* 0xE5  KDS stop low fan test   */
bool     B_Fan2Req;       /* 0xE6  KDS request low fan test  */
bool     B_Fan2Stp;       /* 0xE6  KDS stop low fan test   */
bool     B_CpgVReq;       /* 0xE8  KDS request canister purge valve test  */
bool     B_CpgVStp;       /* 0xE8  KDS stop canister purge valve test  */


uint8_t Gr;
uint8_t Maf_b;
uint16_t             KmQ1;
uint16_t             KmQ65;
signed char              dNDsr;
bool                 B_Fof;

EOBD_KPAa            Pam;
CHERY_KPAa             Pim;
CHERY_DEG_T            Taini;
CHERY_DEG_T          Tmini;
EOBD_KPH             Vsp;
CHERY_AIRFLOW_KGH    Maf ;
CHERY_Lam            LamDsrLim;
signed char              dNDsr;
CHERY_RPMa           Nstat;
CHERY_BPW            Ti_b1;
CHERY_TEMP_Ta        TexBfCat;
CHERY_TEMP_Ta        TcatInPre;

Percent_Plus_Fraction  TpPosl;

/* IUPR part, defined in HLS*/
// uint16_t NcDGDM_RM_OFVC_IgnCycleCntr;  //=>  uint16 NumIgnCyc;
// uint16_t NcDGDM_RM_Generic_Denom;      //=>  uint16 Dom;
// uint16_t NcDGDM_RM_ICMD_B1_Numrtr;     //=>  uint16 NmeCat;
// uint16_t NcDGDM_RM_ICMD_B1_Denom;      //=>  uint16 DomCat;
// uint16_t NcDGDM_RM_EOSD_B1_S1_Numrtr;  //=>  uint16 NmeLsb;
// uint16_t NcDGDM_RM_EOSD_B1_S1_Denom;   //=>  uint16 DomLsb;
// uint16_t NcDGDM_RM_EOSD_B1_S2_Numrtr;  //=>  uint16 NmeLsaAg;
// uint16_t NcDGDM_RM_EOSD_B1_S2_Denom;   //=>  uint16 DomLsaAg;
// uint16_t NcDGDM_RM_VVT1_Numrtr;        //=>  uint16 NmeVVTIn;
// uint16_t NcDGDM_RM_VVT1_Denom;         //=>  uint16 DomVVTIn;
// uint16_t NcDGDM_RM_VVT2_Numrtr;        //=>  uint16 NmeVVTOut;
// uint16_t NcDGDM_RM_VVT2_Denom;         //=>  uint16 DomVVTOut;

/*VCPC*/
uint16_t angle_crank_cam_inlet;
uint16_t angle_crank_cam_outlet;

//ETC
etc_signals etc_sig;

//soh fault
Soh_Fault_Log_Type soh_fault;

// electronic pump fuel function
bool                 B_EOL_FuelAdjust;
bool                 E_EOL_FuelAdjust;

#define START_SECTION_static_volatile_SlowRam_32bit
#include "PRAGMA_CHERY.h"
uint32_t hlsbss_test0;
uint32_t hlsbss_test1;
uint32_t hlsbss_test2;
#define STOP_SECTION_static_volatile_SlowRam_32bit
#include "PRAGMA_CHERY.h"

#define START_SECTION_static_nonvolatile_SlowRam_32bit
#include "PRAGMA_CHERY.h"
uint32_t nvram_test0;
uint32_t nvram_test1;
uint32_t  nvram_test2;
#define STOP_SECTION_static_nonvolatile_SlowRam_32bit
#include "PRAGMA_CHERY.h"


T_CRANK_ANGLEa PfKNOC_phi_FinalWindow2Begin;/* Start angle of  knock window 2 */
T_CRANK_ANGLEa PfKNOC_phi_FinalWindow2End;/* End angle of  knock window 2 */
T_MILLISECONDSb PfKNOC_phi_FinalWindow2_length;


extern bool     First_Syn_Flag;

void HAL_GPIO_SET_INJECTION_Enable(bool in_enable);
void HAL_GPIO_SET_INJECTION_GPIO_Mode_Enable(bool in_enable);
/* ============================================================================ *\
 * Local FUNCTION.
\* ============================================================================ */
/*AD test code*/
  void TestATD_ATD_Function(void)
{

	HLS_MAP_Value = LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_val;
	//HLS_MAP_Status = LLD_atd_input_table[LLD_ATD_MAP].LLD_atd_status;
	HLS_OXYGEN_Value = LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_1].LLD_atd_val;
	//HLS_OXYGEN_Status = LLD_atd_input_table[LLD_ATD_OXYGEN_SENSOR_1].LLD_atd_status;
	HLS_BATT_Value = LLD_atd_input_table[LLD_ATD_VBATT_SW].LLD_atd_val;
	//HLS_BATT_Status = LLD_atd_input_table[LLD_ATD_VBATT_SW].LLD_atd_status;
	HLS_TA_Value = LLD_atd_input_table[LLD_ATD_TA].LLD_atd_val;
	//HLS_TA_Status = LLD_atd_input_table[LLD_ATD_TA].LLD_atd_status;
	HLS_ECT_Value = LLD_atd_input_table[LLD_ATD_ECT].LLD_atd_val;
	//HLS_ECT_Status = LLD_atd_input_table[LLD_ATD_ECT].LLD_atd_status;
	HLS_TPS_Value = LLD_atd_input_table[LLD_ATD_THROTTLE_1].LLD_atd_val;
	//HLS_TPS_Status = LLD_atd_input_table[LLD_ATD_THROTTLE_1].LLD_atd_status;
	HLS_PBATT_Value = LLD_atd_input_table[LLD_ATD_BATTERY_1].LLD_atd_val;

}

/*HWIO DI test code*/
void Test_DI_Function(void)
{
    HLS_Filtered_AC_REQUEST_INPUT = LLD_di_table[LLD_DI_AC_REQUEST_INPUT].value;
    HLS_Filtered_AC_PRESSURE_SWITCH= LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].value;
    HLS_Filtered_DI_CAM_1=LLD_di_table[LLD_DI_CAM_1].value;
    HLS_Filtered_DI_IGN_ON_OFF_SW=LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value;
    HLS_Filtered_DI_HEAD_LAMP=LLD_di_table[LLD_DI_HEAD_LAMP].value;

}

/*HWIO DO test code*/
void Test_DO_Toggle_Function(void)
{
	LLD_do_table[LLD_DO_FAN1].value = !LLD_do_table[LLD_DO_FAN1].value;
	LLD_do_table[LLD_DO_FAN2].value = !LLD_do_table[LLD_DO_FAN2].value;
	LLD_do_table[LLD_DO_FUEL_PUMP].value = !LLD_do_table[LLD_DO_FUEL_PUMP].value;
	//LLD_do_table[LLD_DO_MAIN_RELAY].value = !LLD_do_table[LLD_DO_MAIN_RELAY].value;
	LLD_do_table[LLD_DO_MIL_LAMP].value = !LLD_do_table[LLD_DO_MIL_LAMP].value;
	LLD_do_table[LLD_DO_SVS_LAMP].value = !LLD_do_table[LLD_DO_SVS_LAMP].value;
	LLD_do_table[LLD_DO_AC_CLUTCH].value = !LLD_do_table[LLD_DO_AC_CLUTCH].value;
	//LLD_do_table[LLD_DO_R_LINE].value = !LLD_do_table[LLD_DO_R_LINE].value;
	LLD_do_table[LLD_DO_START_MOTR_RLY].value = !LLD_do_table[LLD_DO_START_MOTR_RLY].value;
	LLD_do_table[LLD_DO_VIS_SWITCH].value = !LLD_do_table[LLD_DO_VIS_SWITCH].value;
	etc_sig.etc_direction  = ~etc_sig.etc_direction ;
}


/* ============================================================================ *\
 * Exported FAR_COS FUNCTION.
\* ============================================================================ */
/* Call back function for 1ms task */
void HLS_Task_1ms(void)
{
    TestATD_ATD_Function();
}

/* Call back function for 2ms task */
void HLS_Task_2ms(void)
{
}

void HLS_Task_5ms(void)
{
 
}

/* Call back function for 10ms task */
void HLS_Task_10ms(void)
{
 Test_DI_Function();
}
/* Call back function for 20ms task */
void HLS_Task_20ms(void)
{
}
/* Call back function for 50ms task */
 void HLS_Task_50ms(void)
{
}
/* Call back function for 100ms task */
 void HLS_Task_100ms(void)
{
}
/* Call back function for 200ms task */

void HLS_Task_200ms(void)
{
	soh_fault.Word = SOH_ETC_Get_Fault_Log();
}
/* Call back function for 1000ms task */
static int b_toggle_function = 1;
void HLS_Task_1000ms(void)
{
    if (b_toggle_function)
        Test_DO_Toggle_Function();
	// HAL_GPIO_SET_INJECTION_Enable(b_toggle_function);
	// b_toggle_function = !b_toggle_function;
}

void HLS_afterrun(void)
{
    sys_cmd.B_after_run_end = true;
}

/*HLS initialization function.*/
void HLS_ini(void)
{
	// HAL_GPIO_SET_INJECTION_GPIO_Mode_Enable(false);
	/* etc signal output set */
	etc_sig.etc_enable = true;
	etc_sig.etc_freq = 500; //set to 2khz
	etc_sig.etc_duty = 32768;
	etc_sig.etc_direction = false;

	/* data input debounce time set*/
	LLD_di_table[LLD_DI_AC_REQUEST_INPUT].DebounceTimes = LLD_DI_AC_REQUEST_INPUT_DebTime ;
	LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].DebounceTimes=LLD_DI_AC_PRESSURE_SWITCH_DebTime ;
	LLD_di_table[LLD_DI_CAM_1].DebounceTimes = LLD_DI_CAM_1_DebTime;
	LLD_di_table[LLD_DI_IGN_ON_OFF_SW].DebounceTimes = LLD_DI_IGN_ON_OFF_SW_DebTime ;
	LLD_di_table[LLD_DI_HEAD_LAMP].DebounceTimes = LLD_DI_HEAD_LAMP_DebTime ;
	LLD_di_table[LLD_DI_POWER_STEERING].DebounceTimes = LLD_DI_POWER_STEERING_DebTime;
	LLD_di_table[LLD_DI_BRAKE_SWITCH].DebounceTimes = LLD_DI_BREAK_SWITCH_DebTime;
	LLD_di_table[LLD_DI_CLUTCH_TOP].DebounceTimes = LLD_DI_ClUTCH_TOP_DebTime;
	LLD_di_table[LLD_DI_CRANK_REQUEST].DebounceTimes = LLD_DI_CRANK_REQUEST_DebTime;
#if 0
	/* pulse output enable/disable set */
	LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].B_enable = true;
	LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].B_enable = true;
	LLD_pwm_out_table[LLD_PWM_PURGE].B_enable = true;
	LLD_pwm_out_table[LLD_PWM_ECT].B_enable = true;
	LLD_pwm_out_table[LLD_PWM_EGR].B_enable = true;
	LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].B_enable = true;
	LLD_pwm_out_table[LLD_PWM_VVT1].B_enable = true;
	LLD_pwm_out_table[LLD_PWM_VVT2].B_enable = true;

	/* pulse output duty circle set */
	LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].duty = 128;
	LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].duty = 128;
	LLD_pwm_out_table[LLD_PWM_PURGE].duty=128;
	LLD_pwm_out_table[LLD_PWM_ECT].duty=128;
	LLD_pwm_out_table[LLD_PWM_EGR].duty=128;
	LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].duty=128;
	LLD_pwm_out_table[LLD_PWM_VVT1].duty=128;
	LLD_pwm_out_table[LLD_PWM_VVT2].duty=128;


	/* pulse output period set */
	LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].period = 100;
	LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].period = 100;
	LLD_pwm_out_table[LLD_PWM_PURGE].period = 100;
	LLD_pwm_out_table[LLD_PWM_ECT].period = 10;
	LLD_pwm_out_table[LLD_PWM_EGR].period = 100;
	LLD_pwm_out_table[LLD_PWM_VVT1].period = 10;
	LLD_pwm_out_table[LLD_PWM_VVT2].period = 10;
	LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].period = 10;
#endif

	/* injection enable set */
	inj_enable.B_inj_A = (uint8_t)true;
	inj_enable.B_inj_B = (uint8_t)true;
	inj_enable.B_inj_C = (uint8_t)true;
	inj_enable.B_inj_D = (uint8_t)true;

	inj_sig[INJ_CHANNEL_A].inj_time = 80000;
	inj_sig[INJ_CHANNEL_B].inj_time = 80000;
	inj_sig[INJ_CHANNEL_C].inj_time = 80000;
	inj_sig[INJ_CHANNEL_D].inj_time = 80000;

	inj_sig[INJ_CHANNEL_A].inj_end_angle = 127;
	inj_sig[INJ_CHANNEL_B].inj_end_angle = 127;
	inj_sig[INJ_CHANNEL_C].inj_end_angle = 127;
	inj_sig[INJ_CHANNEL_D].inj_end_angle = 127;


	ign_enable.B_ign_A = (uint8_t)true;     
	ign_enable.B_ign_B = (uint8_t)true;
	ign_enable.B_ign_C = (uint8_t)true;
	ign_enable.B_ign_D = (uint8_t)true;

	ign_sig[LLD_IGN_CHANNEL_A].dwell_time = 4000;
	ign_sig[LLD_IGN_CHANNEL_B].dwell_time = 4000;
	ign_sig[LLD_IGN_CHANNEL_C].dwell_time = 4000;
	ign_sig[LLD_IGN_CHANNEL_D].dwell_time = 4000;

	ign_sig[LLD_IGN_CHANNEL_A].ign_angle = -16;
	ign_sig[LLD_IGN_CHANNEL_B].ign_angle = -16;
	ign_sig[LLD_IGN_CHANNEL_C].ign_angle = -16;
	ign_sig[LLD_IGN_CHANNEL_D].ign_angle = -16;

	ign_sig[LLD_IGN_CHANNEL_A].follow_up_sparks = 2;
	ign_sig[LLD_IGN_CHANNEL_A].dwell_time_of_follow_up_sparks = 1000;
	ign_sig[LLD_IGN_CHANNEL_A].break_time_of_follow_up_sparks = 500;

	 /*sys_cmd.B_after_run_end= false;
	 sys_cmd.B_SW_Pwf = false;
	 sys_cmd.B_rsv = 0x0;
	 sys_status.B_after_run_end_abnormal = false;
	 sys_status.B_Pwf = false;
	 sys_status.B_rsv = 0x0;*/

	TpPos_b=100;//tps=100*0.3922=39.22
	Pmap_b=100;//Pmap_b=100kpa
	Pmap=25650;//pmap=0.0039*25650=100.35kpa
	Tm=200;//Tm= 200*0.75-48 =102 
	TmLin=200;//TmLin= 200*0.75-48 =102
	Ta=200;

	// B_after_run_end_abnormal =0x00;

	/* data output set */
	LLD_do_table[LLD_DO_FAN1].value = true;
	LLD_do_table[LLD_DO_FAN2].value = false;
	LLD_do_table[LLD_DO_FUEL_PUMP].value = true;
	LLD_do_table[LLD_DO_MAIN_RELAY].value = true;
	LLD_do_table[LLD_DO_MIL_LAMP].value = false;
	LLD_do_table[LLD_DO_SVS_LAMP].value = true;
	LLD_do_table[LLD_DO_AC_CLUTCH].value = false;
	LLD_do_table[LLD_DO_R_LINE].value = true;
	LLD_do_table[LLD_DO_START_MOTR_RLY].value = true;
	LLD_do_table[LLD_DO_VIS_SWITCH].value = true;

	PfKNOC_phi_FinalWindow2Begin = V_CRANK_ANGLEa(0);
	PfKNOC_phi_FinalWindow2End =  V_CRANK_ANGLEa(24);
	PfKNOC_phi_FinalWindow2_length = V_MILLISECONDSb(4.0);
}

/*HLS initialization function*/
void HLS_ini2(void)
{
    unsigned char i;
    telem_data.tele_N =0x1234;
    telem_data.tele_B_FuelStatus = 0xaa;
    telem_data.tele_CsMaf = 0xbb;
    telem_data.tele_fLc = 0xcc;
    telem_data.tele_fLcAd = 0xdd;
    telem_data.tele_IgaOut = 0xee;
    telem_data.tele_Pmap = 0xff;
    telem_data.tele_TaLin = 0x11;
    telem_data.tele_TmLin = 0x22;
    telem_data.tele_TpPos = 0x33;
    telem_data.tele_uLsb = 0x44;
    telem_data.tele_Vsp = 0x55;
}

/*will be called after _ini() at ECU power on, and at engine stall*/
void HLS_inisyn(void)
{

}
uint16_t test_count;
/*will be called when the synch is lost/reset, this is an event trigged function call*/
void HLS_rstsyn(void)
{
test_count =0;
}
/*will be called when the first Synchronization (first gap) is confirmed, this is an event trigged function call*/
void HLS_firstsyn(void)
{


}
/*will be called for every segment (at Software reference mark)*/

void HLS_syn(void)
{


if(First_Syn_Flag==0)
{
    inj_sig[INJ_CHANNEL_A].inj_time = 40000;
    inj_sig[INJ_CHANNEL_B].inj_time = 40000;
    inj_sig[INJ_CHANNEL_C].inj_time =40000;
    inj_sig[INJ_CHANNEL_D].inj_time = 40000;

}
else
{

if(LLD_cyl_num==INJ_CHANNEL_A)
{
    inj_sig[INJ_CHANNEL_A].inj_time = 10000;
}
if(LLD_cyl_num==INJ_CHANNEL_B)
{
    inj_sig[INJ_CHANNEL_B].inj_time = 10000;
}
if(LLD_cyl_num==INJ_CHANNEL_C)
{
    inj_sig[INJ_CHANNEL_C].inj_time = 10000;
}	
if(LLD_cyl_num==INJ_CHANNEL_D)
{	
    inj_sig[INJ_CHANNEL_D].inj_time = 10000;
}
}
#if 0
    inj_sig[INJ_CHANNEL_A].B_post_inj = true;
    inj_sig[INJ_CHANNEL_A].post_inj_time =1000;
    inj_sig[INJ_CHANNEL_B].B_post_inj = true;
    inj_sig[INJ_CHANNEL_B].post_inj_time =1000;
    inj_sig[INJ_CHANNEL_C].B_post_inj = true;
    inj_sig[INJ_CHANNEL_C].post_inj_time =1000;
    inj_sig[INJ_CHANNEL_D].B_post_inj = true;
    inj_sig[INJ_CHANNEL_D].post_inj_time =1000;
#endif	
    /* ignition test interface */
    // if(LLD_cyl_num == 0) {
        // ign_sig[0].ign_angle = 40;
        // ign_sig[1].ign_angle = -40;
        // ign_sig[2].ign_angle = 0;
        // ign_sig[3].ign_angle = 80;//
    // }
    // if(LLD_cyl_num == 1) {
        // ign_sig[0].ign_angle = -40;
        // ign_sig[1].ign_angle = 0;
        // ign_sig[2].ign_angle = 0;//
        // ign_sig[3].ign_angle = 40;
    // }
    // if(LLD_cyl_num == 2) {
        // ign_sig[0].ign_angle = 0;
        // ign_sig[1].ign_angle = -30;//
        // ign_sig[2].ign_angle = 40;
        // ign_sig[3].ign_angle = -40;
    // }
    // if(LLD_cyl_num == 3) {
        // ign_sig[0].ign_angle = -20;//
        // ign_sig[1].ign_angle = 40;
        // ign_sig[2].ign_angle = -40;
        // ign_sig[3].ign_angle = 0;
    // }

  //SetIO_MultiKnock_Window_Start(MULTIKNOCK_WINDOW_2, PfKNOC_phi_FinalWindow2Begin);
  //SetIO_MultiKnock_Window_End(MULTIKNOCK_WINDOW_2, PfKNOC_phi_FinalWindow2End);
  //SetIO_MultiKnock_Window_Length(MULTIKNOCK_WINDOW_2, PfKNOC_phi_FinalWindow2_length);

}
/*will be called on each falling edge of the CAM signal*/
void HLS_ph1(void)
{

}

/*will be called on each falling edge of the CAM signal*/
 void HLS_ph2(void)
{

}
/* will be called at the falling edge of every crank tooth */
 void HLS_tooth_interrupt(void)
{
   
} 

void ETSMRSV_r40ms(void)
{
}

void ETSMIST_r40ms()
{
}

void ETSMAPV_r40ms()
{
}

void ETSMN_r40ms()
{
}

void ETSMLD_r40ms()
{
}

void ETSMAFST_r40ms()
{
}

void ETSMTQP_r40ms()
{
}

void ETSMTQF_r40ms()
{
}

void ETSMIGA_r40ms()
{
}

void ETSMTQC_r40ms()
{
}

void ETSMTQ_r40ms()
{
}

void ETSMMFR_r40ms()
{
}

void ETSMRES1_r40ms()
{
}

void ETSMRES2_r40ms()
{
}

void ETSMRES3_r40ms()
{
}

void ETSMRES4_r40ms()
{
}

/*===========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/*===========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---     ----------------------------------       */
/*===========================================================================*/


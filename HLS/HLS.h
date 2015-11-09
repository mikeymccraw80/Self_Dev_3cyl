#ifndef HLS_H
#define HLS_H

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "reuse.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
/*  none */


/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/


/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/
typedef struct {
	uint8_t B_failed : 1; /*signal failed * comprehending min, max and sig*/
	uint8_t B_fail_pending : 1; /*signal failure pending */
	uint8_t B_max : 1; /* signal value high or short to battery */
	uint8_t B_min : 1; /* signal value low or short to ground */
	uint8_t B_sig : 1; /* signal open load */
	uint8_t B_npl : 1; /* reserved position for HLS signal value non-plausible ( for EOBD) */
	uint8_t B_substitute: 1; /* substitute value is being passed by LLD */
	uint8_t B_clrerr : 1; /* reserved position for HLS */
} status_bits;

/*ATD input module*/
typedef struct{
	uint16_t     LLD_atd_val; /* raw value from register(10bit width) */
	status_bits  LLD_atd_status; /* Status Code */
} LLD_atd_input_item;

/* DI data structure */
typedef struct{
	uint8_t DebounceTimes; // HLS can set it in initialization, otherwise it is 0
	uint8_t value ; /* Input level to return,1 or 0 */
	status_bits status ; /* Status when electrical diagnostics are available, otherwise no use */
}LLD_di_item;

typedef struct{
	uint8_t value; /* Value to be output 0-low; 1-high */
	status_bits status; /* Status code - Reserved */
}LLD_do_item;

typedef struct{
	uint8_t B_enable; /* enable the PWM channel, only writable by HLS */
	uint8_t period; /* PWM period */
	uint8_t duty; /* PWM duty cycle */
	status_bits status; /* Status Code */
}LLD_pwm_out_item;

typedef struct {
	uint8_t B_crank_failed : 1; /*signal failed */
	uint8_t B_crank_no_sync : 1; /*crank no movement */
	uint8_t B_crank_sync : 1; /*crank synchronizedy */
	uint8_t B_crank_pre_sync : 1; /* crank moving but not synchronized, 3 or less teeth */
	uint8_t B_crank_stall : 1; /* crank was synched but now no movement */
	uint8_t B_crank_loss_of_sync : 1; /* lost synchronization */
	uint8_t B_crank_limp_home : 1; /* running limphome on CAM sensor */
	uint8_t B_RefMrk : 1; /* reference bits mark */
} crank_status_bits;

typedef struct {
	uint32_t segment_time; // Segement time
	uint16_t engine_rpm; // Engine revolution per minute
	uint8_t  engine_position_tc; // Engine position tooth count
	crank_status_bits crank_status; // Crank status
} crank_signals;

typedef struct {
	uint8_t B_cam_failed : 1; /*signal failed */
	uint8_t B_cam_loss_of_sync : 1; /* cam level is wrong at the crank GAP */
	uint8_t B_cam_limp_home : 1; /* running limphome on crank sensor */
	uint8_t B_rsv : 5; /* reserved bits */
} cam_status_bits;

typedef struct {
	uint32_t period; // between falling edges
	uint8_t edge_count; // cam edge counter, from 1 to 8
	uint8_t level; // current cam sensor level
	cam_status_bits status;
} cam_signals;

typedef struct {
	uint32_t period; // Vehicle Speed Period
	status_bits status;
} veh_spd_signals;


/*ignition channels, A,B,C,D are corresponding to the firing order: 1,3,4,2 for example*/
typedef struct {
	uint8_t B_ign_A : 1; /*enable igntion channel A */
	uint8_t B_ign_B : 1; /*enable igntion channel B */
	uint8_t B_ign_C : 1; /*enable igntion channel C */
	uint8_t B_ign_D : 1; /*enable igntion channel D */
	uint8_t B_ign_rsv : 4; /*reserved */
} ign_enable_bits;

typedef struct {
	int8_t ign_angle;
	uint16_t dwell_time;
	uint8_t   follow_up_sparks;
	uint16_t dwell_time_of_follow_up_sparks;
	uint16_t break_time_of_follow_up_sparks;
	status_bits status; /* Status Code */
} ign_signals;

/*injection channels, A,B,C,D are corresponding to the firing order: 1,3,4,2 for example*/
typedef struct {
	uint8_t B_inj_A : 1; /*enable injection channel A */
	uint8_t B_inj_B : 1; /*enable injection channel B */
	uint8_t B_inj_C : 1; /*enable injection channel C */
	uint8_t B_inj_D : 1; /*enable injection channel D */
	uint8_t B_inj_rsv : 4; /* reserved */
} inj_enable_bits;

typedef struct {
	uint8_t inj_end_angle;
	uint32_t inj_time;
	uint8_t B_post_inj; /*boundary conditions, HLS to set this bit and let LLD to handle the latency.*/
	uint16_t post_inj_time;
	uint8_t abort_angle;
	status_bits status; /* Status Code */
} inj_signals;

typedef struct {
	uint8_t B_Pwf : 1; /*ECU power fail happened */
	uint8_t B_after_run_end_abnormal: 1; /* ECU after run end abnormally */
	uint8_t B_rsv : 6; /*reserved bits */
} sys_status_bits;

typedef struct {
	uint8_t B_SW_Pwf : 1;       /* HLS commanded power fail */
	uint8_t B_after_run_end: 1; /* HLS after-run end */
	uint8_t B_ResetEtsm: 1;     /* information SW-reset from cyclic RAM-check*/
	uint8_t B_rsv : 5;          /* reserved bits */
} sys_cmmd_bits;

/* ETC interface */
typedef union {
	uint16_t ETC_Fault;
	struct {
		uint16_t SBAT_OFF : 1;      // Short to Battery in OFF condition
		uint16_t SGND_OFF : 1;      // Short to GND in OFF condition
		uint16_t RES13_12 : 2;      // Reserved
		uint16_t OC_HS2 :   1;      // Over-Current on How Side 2
		uint16_t OC_HS1 :   1;      // Over-Current on How Side 1
		uint16_t OC_LS2 :   1;      // Over-Current on Low Side 2
		uint16_t OC_LS1 :   1;      // Over-Current on Low Side 1
		uint16_t ACT :      1;      // Bridge enable,Ture after reset
		uint16_t TSD :      1;      // Over-temperature Shutdown
		uint16_t TWARN :    1;      // Temperature warning
		uint16_t ILIM :     1;      // Current Limitation reached
		uint16_t VDD_OV :   1;      // Vdd overvoltage
		uint16_t VS_UV :    1;      // Vs undervoltage
		uint16_t OL_ON :    1;      // Open Load in ON condition
		uint16_t OL_OFF :   1;      // Open Load in OFF condition
	}etc_status_bits;
} ETC_Fault_type;

typedef struct {
	uint16_t       etc_freq;        //ETC frequency
	uint16_t       etc_duty;        //ETC Duty
	uint8_t        etc_enable;      //ETC enable contorl
	uint8_t        etc_direction;   //ETC motor rotate direction control
	status_bits    status1;         // M- Status Code 
	status_bits    status2;         //M+ Status Code 
	ETC_Fault_type status3;         //ETC Driver fault status
} etc_signals;

extern etc_signals etc_sig;

/* soh fault log interface */
typedef union {
	uint16_t Word; /* ETC SOH fault code */
	struct {
		uint16_t	SysClkFail 		    : 1; /* System clock frequency error */
		uint16_t	SohIrqSrcFail       : 1; /* Interrupt source error */
		uint16_t	SysTmrFail		    : 1; /* System timer error */
		uint16_t	SohSeqFail          : 1; /* Test sequence error */
		uint16_t	RtiFreqFail         : 1; /* RTI frequency error */
		uint16_t	LoopSeqFail		    : 1; /* CPU loop sequence error */
		uint16_t	CRCounterLow        : 1; /* SOH C&R counter value low */
		uint16_t	ShutOffTimeExpire   : 1; /* Shutoff timer expired */
		uint16_t	SPIFail             : 1; /* SPI error */
		uint16_t	SPICommFail         : 1; /* SPI communication error */
		uint16_t	CRDisarmed          : 1; /* SOH C&R disarmed */
		uint16_t	CRTimeoutFail       : 1; /* SOH C&R timeout */
		uint16_t	CRCounterFail	    : 1; /* SOH C&R counter value zero */
		uint16_t						: 3;
	} Bits;
} Soh_Fault_Log_Type;

extern uint16_t SOH_ETC_Get_Fault_Log(void);
extern void SOH_ETC_Clear_Fault_Log(void);

typedef enum
{
   LLD_AN00,
   LLD_AN01,
   LLD_AN02,
   LLD_AN03,
   LLD_AN04,
   LLD_AN05,
   LLD_AN06,
   LLD_AN07,
   LLD_AN08,
   LLD_AN09,
   LLD_AN10,
   LLD_AN11,
   LLD_AN12,
   LLD_AN13,
   LLD_AN14,
   LLD_AN15,
   LLD_AN16,
   LLD_AN17,
   LLD_AN18,
   LLD_AN19,
   LLD_AN20,
   LLD_AN21,
   LLD_AN22,
   LLD_AN23,
   LLD_ATD_MAX_CHANNEL 
}  LLD_ATD_T;

typedef enum
{
   LLD_DI00,
   LLD_DI01,
   LLD_DI02,
   LLD_DI03,
   LLD_DI04,
   LLD_DI05,
   LLD_DI06,
   LLD_DI07,
   LLD_DI08,
   LLD_DI09,
   LLD_DI10,
   LLD_DI11,
   LLD_DI12,
   LLD_DI_MAX_CHANNEL 
}  LLD_DI_T;

typedef enum
{
   LLD_DO00,
   LLD_DO01,
   LLD_DO02,
   LLD_DO03,
   LLD_DO04,
   LLD_DO05,
   LLD_DO06,
   LLD_DO07,
   LLD_DO08,
   LLD_DO09,
   LLD_DO_MAX_CHANNEL 
}  LLD_DO_T;

typedef enum {
	LLD_PWM00,
	LLD_PWM01,
	LLD_PWM02,
	LLD_PWM03,
	LLD_PWM04,
	LLD_PWM05,
	LLD_PWM06,
	LLD_PWM07,
	LLD_PWM08,
	LLD_PWM_MAX_CHANNEL 
}  LLD_PWM_T;


typedef enum {
	CYLINDER_0=0,
	CYLINDER_1,
	CYLINDER_2,
	CYLINDER_3
} current_channel_num;


/*the flowing is SAEJ1979 service 0x01 */
typedef struct {
	uint8_t	 tele_Monitor_status[4];    /* PID01: Monitor status since DTCs cleared */
	uint16_t tele_Cause_Frame_Pcode;	/* PID02: DTC that caused required freeze frame data storage */
	uint16_t tele_N;                    /* PID0C: Engine RPM */
	uint16_t tele_tStaEnd;				/* PID1F: Time Since Engine Start */
	uint16_t tele_KmQ6Mil;	            /* PID21: Distance Travelled While MIL is Activated */
	uint16_t tele_TcatPre_b;	    	/* PID3C: Catalyst Temperature */
	uint16_t tele_Ub_b;			        /* PID42: System voltage */
	uint8_t	 tele_B_FuelStatus;	        /* PID03: fuel supply system status */
	uint8_t	 tele_CsMaf;                /* PID04: Calculated LOAD Value */
	uint8_t	 tele_TmLin;		     	/* PID05: Engine Coolant Temperature */
	uint8_t	 tele_fLc;		        	/* PID06: Short Term Fuel Trim Bank 1 */
	uint8_t	 tele_fLcAd;	        	/* PID07: Long Term Fuel Trim Bank 1 */
	uint8_t	 tele_Pmap;		            /* PID0B: Intake Manifold Absolute Pressure */
	uint8_t	 tele_Vsp;		        	/* PID0D: Vehicle Speed Sensor */
	uint8_t	 tele_IgaOut;	            /* PID0E: Ignition Timing Advance for #1 Cylinder */
	uint8_t	 tele_TaLin;                /* PID0F: Intake Air Temperature */
	uint8_t	 tele_uLsb;                 /* PID14: Sensor Output Voltage */
	uint8_t	 tele_uLsbfLc;	        	/* PID14: Short Term Fuel Trim (B1-S1) */
	uint8_t	 tele_uLsa;		        	/* PID15: Sensor Output Voltage */
	uint8_t	 tele_uLsafLc;              /* PID15: Short Term Fuel Trim (B1-S2) */
	uint8_t	 tele_obd_Type;             /* PID1C: OBD requirements to which vehicle is designed */
	uint8_t	 tele_O2SPos;               /* PID1D: Location of Oxygen Sensors */
	uint8_t	 tele_DuCyPgOut;            /* PID2E: Command Evaporative Purge */
	uint8_t	 tele_WmuCntVal;            /* PID30: Number of warm-ups since diagnostic trouble codes cleared */
	uint8_t	 tele_Pam;                  /* PID33: Ambient air Pressure */
	uint8_t	 tele_TpPos;                /* PID45: relative Throttle Position */
	uint8_t	 tele_Tam;                  /* PID46: Ambient air temperature */
	uint8_t	 tele_FuelType;             /* PID51: Type of fuel currently being utilized by the vehicle */
	uint8_t  tele_PedPos;               /* PID5A: Relative accelerate pedal position*/
} tele_type;
extern tele_type telem_data;

/*the flowing is SAEJ1979 service 0x02 */
typedef struct {	
    uint16_t Ffm_Frame_Pcode;       /* 0x02  indicates no freeze frame data */
    uint16_t Ffm_N;                 /* 0x0C	Engine RPM	*/
    uint16_t Ffm_KmQ6Mil;           /* 0x21	Distance Travelled While MIL is Activated	*/
	uint16_t Ffm_Ub_b;              /* 0x42	System voltage	*/
    uint8_t  Ffm_B_FuelStatus;      /* 0x03  fuel supply system status*/                        
	uint8_t	 Ffm_CsMaf;             /* 0x04  Calculated LOAD Value!	*/
	uint8_t	 Ffm_TmLin;             /* 0x05	Engine Coolant Temperature	*/
	uint8_t	 Ffm_fLc;               /* 0x06	Short Term Fuel Trim Bank	*/
	uint8_t	 Ffm_fLcAd;             /* 0x07	Long Term Fuel Trim Bank 	*/
	uint8_t	 Ffm_Pmap;              /* 0x0B	Intake Manifold Absolute pressure	*/
	uint8_t	 Ffm_Vsp;               /* 0x0D	Vehicle Speed Sensor	*/
	uint8_t	 Ffm_IgaOut;            /* 0x0E	Ignition Timing Advance for #1 Cylinder	*/
	uint8_t	 Ffm_TaLin;             /* 0x0F	Intake Air Temperature	*/
	uint8_t	 Ffm_TpPos;             /* 0x45	Relative Throttle Position	*/
    uint8_t  Ffm_PedPos_b;          /* 0x5A   Relative accelerate pedal position */
}Freeze_Frame_Elem;										
extern Freeze_Frame_Elem  DIAG_STATUS_FREEZE_FRAME[3];

typedef struct {
	uint8_t  VIN[17];						/*Vehicle Identification Number*/
	uint8_t  CALID[16];						/*Calibration Identifications*/
	uint8_t  IUPR[32];						/*0x08 In Use performance tracking*/
}VehicleInformation;
extern VehicleInformation scnVehInfo;

#define SCN_ECUID_SWVERNUM_LENGHT	16
#define SCN_ECUID_HWVERNUM_LENGHT	4
#define SCN_ECUID_MDLSERNUM_LENGHT	30
#define SCN_ECUID_PRGINF_LENGHT		20

typedef struct ECU_Identification {
	uint8_t	SwVerNum[SCN_ECUID_SWVERNUM_LENGHT];
	uint8_t	HwVerNum[SCN_ECUID_HWVERNUM_LENGHT];
	uint8_t	MdlSerNum[SCN_ECUID_MDLSERNUM_LENGHT];
	uint8_t	PrgInf_Original[SCN_ECUID_PRGINF_LENGHT];
	uint8_t	PrgInf_No1[SCN_ECUID_PRGINF_LENGHT];
	uint8_t	PrgInf_No2[SCN_ECUID_PRGINF_LENGHT];
	uint8_t	PrgInf_No3[SCN_ECUID_PRGINF_LENGHT];
}ECU_Identification;
extern ECU_Identification scnEcuId;

/* the following data is stored in eeprom, total size is 40bytes*/
#define		HLS_DataStoreEEP_SIZE				40
extern uint8_t HLS_DataStoreEEP[HLS_DataStoreEEP_SIZE];

#define			SY_FCMTSIZE			8
extern uint8_t 	count_DTCs_SID03;				/* DTC counter for service 03 */
extern uint16_t	DTCs_SID03[SY_FCMTSIZE];		/* DTCs for service 03*/

extern bool	B_DiagInfoClrReq;		/*condition: request to clear diagnostic information */

#define			SY_FCMTSIZE			8
extern uint8_t 	count_DTCs_SID07;				/* DTC counter for service 07 */
extern uint16_t	DTCs_SID07[SY_FCMTSIZE];		/* DTCs for service 07*/

/*the flowing is ISO14230 service 0x31&0x32 */
// extern uint8_t  SupFlagC0[4];    /* 0xC0  ID Support Flag($C1-$E0) */
// extern uint8_t  SupFlagE0[4];    /* 0xE0  ID Support Flag($E1-$FF) */
extern bool     B_Inj0Req;       /* 0xCC  KDS request #1cylinder injector test  */
extern bool     B_Inj0Stp;       /* 0xCC  KDS stop #1cylinder injector test  */
extern bool     B_Inj1Req;       /* 0xCD  KDS request #2cylinder injector test */
extern bool     B_Inj1Stp;       /* 0xCD  KDS stop #2cylinder injector test  */
extern bool     B_Inj2Req;       /* 0xCE  KDS request #3cylinder injector test  */
extern bool     B_Inj2Stp;       /* 0xCE  KDS stop #3cylinder injector test  */
extern bool     B_Inj3Req;       /* 0xCF  KDS request #4cylinder injector test  */
extern bool     B_Inj3Stp;       /* 0xCF  KDS stop #4cylinder injector test  */
extern bool     B_FulPReq;       /* 0xD4  KDS demand fuel pump test  */
extern bool     B_FulPStp;       /* 0xD4  KDS request fuel pump test   */
extern bool     B_MILReq;        /* 0xD5  Tester request MIL work 5S */
extern bool     B_MILStp;        /* 0xD5  Tester request stop test */
extern bool     B_SVSReq;        /* 0xD6  Tester request SVS work 5S */
extern bool     B_SVSStp;        /* 0xD6  Tester request stop test */
extern bool     B_Fan1Req;       /* 0xE5  KDS request low fan test  */
extern bool     B_Fan1Stp;       /* 0xE5  KDS stop low fan test   */
extern bool     B_Fan2Req;       /* 0xE6  KDS request low fan test  */
extern bool     B_Fan2Stp;       /* 0xE6  KDS stop low fan test   */
extern bool     B_CpgVReq;       /* 0xE8  KDS request canister purge valve test  */
extern bool     B_CpgVStp;       /* 0xE8  KDS stop canister purge valve test  */


/* ==========================================================================*\
 * Exported INLINE functions and #define function-like macros.
\* ==========================================================================*/
/*chery ATD*/
/* ATD Index */
#define LLD_ATD_MAP                 LLD_AN01
#define LLD_ATD_VBATT_SW            LLD_AN02
#define LLD_ATD_OXYGEN_SENSOR_1     LLD_AN03
#define LLD_ATD_OXYGEN_SENSOR_2     LLD_AN04
#define LLD_ATD_TA                  LLD_AN05
#define LLD_ATD_ECT                 LLD_AN06
#define LLD_ATD_THROTTLE_1          LLD_AN07
#define LLD_ATD_THROTTLE_2          LLD_AN08
#define LLD_ATD_PEDAL_1             LLD_AN09
#define LLD_ATD_PEDAL_2             LLD_AN10
#define LLD_ATD_FRONT_EVAP_TEMP     LLD_AN11
#define LLD_ATD_AC_PRESSURE         LLD_AN12
#define LLD_ATD_BATTERY_1           LLD_AN13
#define LLD_ATD_BRAKE_LAMP          LLD_AN14

/*chery DI*/
/* DI Index */
#define LLD_DI_AC_REQUEST_INPUT     LLD_DI00
#define LLD_DI_AC_PRESSURE_SWITCH   LLD_DI01
#define LLD_DI_CAM_1                LLD_DI02
#define LLD_DI_IGN_ON_OFF_SW        LLD_DI03
#define LLD_DI_HEAD_LAMP            LLD_DI04
#define LLD_DI_POWER_STEERING       LLD_DI05
#define LLD_DI_BRAKE_LAMP           LLD_DI06
#define LLD_DI_BRAKE_SWITCH         LLD_DI07
#define LLD_DI_CLUTCH_TOP           LLD_DI08
#define LLD_DI_CRANK_REQUEST        LLD_DI09

/*debounce time*/
/*Debounce time for all digital inputs are tentatively defined as 10ms. It could be changed later.*/
#define LLD_DI_AC_REQUEST_INPUT_DebTime   10 /*ms*/
#define LLD_DI_AC_PRESSURE_SWITCH_DebTime 10
#define LLD_DI_CAM_1_DebTime              10
#define LLD_DI_IGN_ON_OFF_SW_DebTime      10
#define LLD_DI_HEAD_LAMP_DebTime          10
#define LLD_DI_POWER_STEERING_DebTime     10
#define LLD_DI_CRANK_REQUEST_DebTime      10
#define LLD_DI_ClUTCH_TOP_DebTime         10
#define LLD_DI_BREAK_SWITCH_DebTime       10

/* Corresponding PIN number of connector */
#define LLD_DO_FAN1             LLD_DO00 //index of digital output channel 0
#define LLD_DO_FAN2             LLD_DO01 //index of digital output channel 1
#define LLD_DO_FUEL_PUMP        LLD_DO02 //index of digital output channel 2
#define LLD_DO_MAIN_RELAY       LLD_DO03 //index of digital output channel 3
#define LLD_DO_MIL_LAMP         LLD_DO04 //index of digital output channel 4
#define LLD_DO_SVS_LAMP         LLD_DO05 //index of digital output channel 5
#define LLD_DO_AC_CLUTCH        LLD_DO06 //index of digital output channel 6
#define LLD_DO_R_LINE           LLD_DO07 //index of digital output channel 7
#define LLD_DO_START_MOTR_RLY   LLD_DO08 //index of digital output channel 8
#define LLD_DO_VIS_SWITCH       LLD_DO09 //index of digital output channel 9

#define LLD_PWM_O2_HEATER_1      LLD_PWM00      //VSEP,  PWM OUTPUT CH00
#define LLD_PWM_O2_HEATER_2      LLD_PWM06      //VSEP,  PWM OUTPUT CH01
#define LLD_PWM_PURGE            LLD_PWM02      //VSEP,  PWM OUTPUT CH02
#define LLD_PWM_ECT              LLD_PWM03      //VSEP,  PWM OUTPUT CH03
#define LLD_PWM_EGR              LLD_PWM04      //not implemented
#define LLD_PWM_TACHO            LLD_PWM05      //not implemented
#define LLD_PWM_FUEL_CONSUMPTION LLD_PWM01      //not implemented
#define LLD_PWM_VVT1             LLD_PWM07      //eMIOS, PWM OUTPUT CH07
#define LLD_PWM_VVT2             LLD_PWM08      //eMIOS, PWM OUTPUT CH08

#define LLD_IGN_CHANNEL_A 0
#define LLD_IGN_CHANNEL_B 1
#define LLD_IGN_CHANNEL_C 2
#define LLD_IGN_CHANNEL_D 3
//#define LLD_MAX_IGN_CHANNEL 4
#define LLD_MAX_IGN_CHANNEL CcSYST_NUM_OF_CYLINDERS

#define INJ_CHANNEL_A 0
#define INJ_CHANNEL_B 1
#define INJ_CHANNEL_C 2
#define INJ_CHANNEL_D 3
#define MAX_INJ_CHANNEL CcSYST_NUM_OF_CYLINDERS

/*===========================================================================*/
/* Exported global variable                               */
/*===========================================================================*/
extern LLD_atd_input_item LLD_atd_input_table[LLD_ATD_MAX_CHANNEL];
extern LLD_di_item LLD_di_table[LLD_DI_MAX_CHANNEL];
extern LLD_do_item LLD_do_table[LLD_DO_MAX_CHANNEL]; /* Digital output value*/
extern LLD_pwm_out_item LLD_pwm_out_table[LLD_PWM_MAX_CHANNEL]; /* The index means the channel no of the PWM output module */
extern crank_signals crank_sig;
extern cam_signals cam1_sig, cam2_sig;
extern veh_spd_signals veh_spd_sig;
extern uint16_t NumVspPulse;
extern current_channel_num LLD_cyl_num;
extern ign_enable_bits ign_enable;
extern ign_signals ign_sig[LLD_MAX_IGN_CHANNEL];
extern inj_enable_bits inj_enable;
extern inj_signals inj_sig[MAX_INJ_CHANNEL];
extern sys_status_bits sys_status;
extern sys_cmmd_bits sys_cmd;
extern bool           B_syn_update;  
extern bool           B_KeyOn;  
extern bool           S_AC;
extern tele_type telem_data;
extern bool           B_ErCylSynGap;

/* The coolant pull up resister flag */
/* True for 4k, False for 348 */
extern bool        CLT_Range_High;

/* The instant fuel consumption from HLS */
extern uint16_t instant_fuel_consumption;

/* HLS mileage variable */
extern uint32_t odometer;

/* Attention: Do not defined as hls_bss variable */
extern uint32_t Sys_time;
extern uint32_t Tooth_time;

/* chery requirement*/
extern  const uint16_t VAL_uTpsMx;
extern  const uint16_t VAL_uTpsMn;
extern  const uint16_t VAL_uTmMx;
extern  const uint16_t VAL_uTmMn;
extern  const uint16_t VAL_uTaMx;
extern  const uint16_t VAL_uTaMn;
extern  const uint16_t VAL_uPmapMx;
extern  const uint16_t VAL_uPmapMn;
extern  const uint16_t VAL_uLsbMx;
extern  const uint16_t VAL_uLsbMn;
extern  const uint8_t  VAL_LmDgFofDly;

extern unsigned char  TpPos_b;
extern unsigned char  Pmap_b;
extern unsigned short Pam;
extern unsigned short Pim;
extern unsigned char  Tm;
extern unsigned char  TmLin;
extern unsigned char  Ta;
extern uint8_t FCMEnd;
extern uint8_t MafTst;
extern uint16_t fLc;
extern uint16_t fLcAd;
extern uint8_t Pmap_b;
extern uint16_t N;
extern uint16_t VspRaw;
extern int8_t IgaOut;
extern uint8_t TaLin;
extern uint16_t Tpp;
extern uint16_t uLsb;
extern uint16_t uLsa;
extern uint16_t KmQ1Mil;
extern uint8_t Ub_b;
extern uint8_t TpPos_b;
extern uint16_t uTm;
extern uint8_t uTa;
extern uint16_t uPmap;
extern uint16_t uTps;
extern uint16_t Fl;
extern uint32_t Ti;
extern uint8_t Nstat;
extern int16_t dN;
extern int16_t dTqLosAd;
extern int8_t dIgaKncDyn;
extern uint8_t B_Knk;
extern uint8_t Ld_b;
extern uint16_t fAlt;
extern int16_t  dTqIdcP;
extern int16_t dTqIdcI;
extern int8_t dIgaKnc[4];
extern uint16_t FtCntEmis;
extern uint16_t FtCntEmisCyl[4];
extern int16_t RounFon;
extern bool  B_Fan1;
extern bool  B_Fan2; 
extern bool  B_AcOn;
extern uint16_t tLsbAfFlt;
extern int8_t IntLcDwnI;
extern uint8_t SsCatDwnM;
extern uint8_t MxGrdLsaFit_b;
extern uint8_t Gr;
extern uint8_t Maf_b;
extern uint16_t Pmap;
extern uint8_t B_LsaRdy;
extern int8_t Acl_b;
extern uint16_t TcatInPre;
extern uint16_t uTp1;
extern uint16_t uTp2;
extern uint16_t TpPosDpc;
extern int16_t TpPos;
extern uint16_t dpcpids;
extern uint8_t B_dpcPids;
extern uint16_t uPed1;
extern uint16_t uPed2;
extern uint8_t PedPos_b;
extern uint16_t AngCamOvlapAdj;
extern uint8_t fctCamOvlapIn_b;
extern uint8_t fctCamOvlapOut_b;
extern uint16_t DyCyPsIn;
extern uint16_t DyCyPsOut;
extern uint16_t DuCyPgOut;
extern int16_t FlPg;
extern uint16_t fPgRatDsr;
extern int16_t fPgAdp;
extern uint8_t Tam;
extern uint8_t StcEtcAdpt;
extern uint8_t ScSpr;
extern uint8_t ScAntiIce;
extern uint8_t ScLrn;
extern uint8_t B_LrnSuc;
extern uint16_t uTp1Lw;
extern uint16_t uTp2Lw;
extern uint16_t TpPosNlp;
extern uint8_t FrBitsEtsm;
extern uint8_t B_FofEtsm;
extern uint16_t Vsp; //EOBD_KPH
extern bool B_Fof;

extern uint16_t TqiMx;
extern uint16_t TqiDsr;
extern uint16_t TqiAct;
extern uint16_t tStaEndL;
extern uint16_t PedPos;
extern uint16_t FlVofLS;
extern uint8_t  TqActRespEtsm;
extern uint8_t  TpPosDsr_b;
extern uint8_t  TcatInPre_b;
extern uint8_t  TqActEtsm;
extern int16_t  TpPos1;
extern int16_t  TpPos2;
extern uint8_t  TpPosNlp_b;
extern uint16_t uTpNlp1;
extern uint8_t  uTp1Lw_b;
extern int16_t  AngVlvInOp1;
extern int16_t  AngDsrVlvOpIn;
extern uint16_t ToileKel;
extern uint16_t uPed2Dble;
extern uint16_t TexBfPreCat;
extern uint8_t  TmSta;
extern uint16_t MafPcv;
extern int16_t  dTqIdcPD;
extern uint16_t uLsbAdc;
extern uint16_t uLsaAdc;
extern uint8_t  B_Vis;
extern uint8_t  B_Pmp;
extern int8_t   IgaBas;

extern bool                 B_EOL_FuelAdjust;
extern bool                 E_EOL_FuelAdjust;
      
/* knock part, defined in HLS */
extern bool knock_flag_a;
extern bool knock_flag_b;
extern bool knock_flag_c;
extern bool knock_flag_d;

/* knock part, define in LLD */
extern uint16_t ADESC[LLD_MAX_IGN_CHANNEL] ;                             /* knock data of  fir */
extern uint16_t KnockThreshold[LLD_MAX_IGN_CHANNEL];         /* knock threshold */

/* running reset interface, define in LLD */
extern bool     OS_RunningReset_Flag;

/*VVT part, VCPC*/
extern uint16_t angle_crank_cam_inlet;
extern uint16_t angle_crank_cam_outlet;


/* Data for transmit */
extern uint8_t  VsCAN_CHERY_ID0FA[8];
extern uint8_t  VsCAN_CHERY_ID101[8];
extern uint8_t  VsCAN_CHERY_ID270[8];
extern uint8_t  VsCAN_CHERY_ID278[8];
extern uint8_t  VsCAN_CHERY_ID2C1[8];
extern uint8_t  VsCAN_CHERY_ID370[8];
extern uint8_t  VsCAN_CHERY_ID378[8];
extern uint8_t  VsCAN_CHERY_ID501[8];
extern uint8_t  VsCAN_CHERY_ID623[8];
extern uint8_t  VsCAN_CHERY_ID7C1[6];

/* Data for receive */
extern uint8_t  VsCAN_CHERY_ID2E9[8];
extern uint8_t  VsCAN_CHERY_ID310[8];
extern uint8_t  VsCAN_CHERY_ID51A[8];
extern uint8_t  VsCAN_CHERY_ID3C0[8];
extern uint8_t  VsCAN_CHERY_ID430[8];
extern uint8_t  VsCAN_CHERY_ID1AE[8];
extern uint8_t  VsCAN_CHERY_ID300[8];

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/
/*Disable/enable interrupt interface*/
extern   void Disable_1ms_interrupt(void) ;
extern   void Enable_1ms_interrupt(void) ;
extern   void LLD_disable_interrupt(void);
extern   void LLD_enable_interrupt(void);

/* Call back function for 1ms task */
extern  void HLS_Task_1ms(void);
/* Call back function for 2ms task */
extern  void HLS_Task_2ms(void);
/* Call back function for 5ms task */
extern   void HLS_Task_5ms(void);
/* Call back function for 10ms task */
extern   void HLS_Task_10ms(void);
/* Call back function for 20ms task */
extern   void HLS_Task_20ms(void);
/* Call back function for 50ms task */
extern   void HLS_Task_50ms(void);
/* Call back function for 100ms task */
extern   void HLS_Task_100ms(void);
/* Call back function for 200ms task */
extern   void HLS_Task_200ms(void);
/* Call back function for 1000ms task */
extern  void HLS_Task_1000ms(void);
/*HLS initialization function.*/
extern   void HLS_ini(void);
/*HLS initialization function*/
extern  void HLS_ini2(void);
/*will be called after _ini() at ECU power on, and at engine stall*/
extern  void HLS_inisyn(void);
/*will be called when the synch is lost/reset, this is an event trigged function call*/
extern  void HLS_rstsyn(void);
/*will be called when the first Synchronization (first gap) is confirmed, this is an event trigged function call*/
extern  void HLS_firstsyn(void);
/*will be called for every segment (at Software reference mark)*/
extern  void HLS_syn(void);
/*will be called on each falling edge of the CAM1 signal*/
extern  void HLS_ph1(void);
/*will be called on each falling edge of the CAM2 signal*/
extern  void HLS_ph2(void);
/*will be called when Ignition off*/
extern  void HLS_afterrun(void); 
/*will be called at the falling edge of every crank tooth */
extern  void HLS_tooth_interrupt(void);

/* the following functions should be defined and realized in HLS */
extern void ETSMRSV_r40ms(void);
extern void ETSMIST_r40ms(void);
extern void ETSMAPV_r40ms(void);
extern void ETSMN_r40ms(void);
extern void ETSMLD_r40ms(void);
extern void ETSMAFST_r40ms(void);
extern void ETSMTQP_r40ms(void);
extern void ETSMTQF_r40ms(void);
extern void ETSMIGA_r40ms(void);
extern void ETSMTQC_r40ms(void);
extern void ETSMTQ_r40ms(void);
extern void ETSMMFR_r40ms(void);
extern void ETSMRES1_r40ms(void);
extern void ETSMRES2_r40ms(void);
extern void ETSMRES3_r40ms(void);
extern void ETSMRES4_r40ms(void);


/*===========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/*===========================================================================*/
/*                                                                           */
/*  Date        user id     SCR       (description on following lines)       */
/* ----------   -------     ---     ----------------------------------       */
/*===========================================================================*/
#endif 


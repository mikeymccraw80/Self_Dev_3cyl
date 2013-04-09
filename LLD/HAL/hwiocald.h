#ifndef HWIOCALD_H
#define HWIOCALD_H



#include "reuse.h"
#include "dd_vsep_discrete.h"

#include "HLS.h"

typedef struct COND_Test_Option_Tag /* 1 - test enable, 0 - test disabled */
{
	bitfield16_t	CPU_Clock		: 1; /* CPU clock test */
	bitfield16_t	GPR			: 1; /* general purpose register test */
	bitfield16_t	WDT_Timer		: 1; /* all watchdog timeout test */
	bitfield16_t	ADC			: 1; /* ADC conversion test and status */
	bitfield16_t	Flash_ECC		: 1; /* Flash ECC fault detection */
	bitfield16_t	RAM_Parity		: 1; /* RAM parity checking */
	bitfield16_t	NotUsed			: 10; /* not used */
} COND_Test_Option_T;

typedef enum WSS_Type_Tag
{
	WSS_VR = 0,
	WSS_HALL
}  WSS_Type_T ;

typedef enum VSS_Source_Tag
{
	VSS_SOURCE_NONE,
	VSS_SOURCE_SENSOR,
	VSS_SOURCE_COMMUNICATION
} VSS_Source_T ;


//=============================================================================
// Description: Calibration file for 58x section of hardware input output
//                          subsystem.
//=============================================================================
typedef enum {
   WINGATE_TYPE_NONE,
   WINGATE_TYPE_ON
} WINGATE_TYPE_T;
/*
typedef uint16_t            T_CRANK_ANGLE;
#define V_CRANK_ANGLE(val)     (uint16_t)((val)*64)
#define S_CRANK_ANGLE          6

//power-of-two range: [0, 65536) 
typedef uint16_t   T_MICROSECONDS;
#define V_MICROSECONDS(val) (uint16_t)(val)
#define S_MICROSECONDS 0
*/

//crank
extern const uint8_t     KyHWIO_ToothOfFirstLoResEvent;
extern const T_CRANK_ANGLE    KyHWIO_phi_ToothAngleForCamRead;
extern const uint8_t     KyHWIO_CrankSyncStartTooth;
extern const uint8_t     KyHWIO_Num_58X_Teeth_Before_Sync;
extern const bool        KeHWIO_Cam1OccurredTrue;
extern const bool        KeHWIO_Cam2OccurredTrue;
extern const uint8_t     KyHWIO_Num58xGapsBeforeSeqn;
extern const T_CRANK_ANGLE    KfHWIO_phi_TopDeadCenter;
extern const uint8_t       KyHWIO_NumberOfCylinders;
extern const uint8_t       KyHWIO_NumValidPeriodsBeforeSyncStart;
extern const uint8_t       KyHWIO_Num58xGapsUsingCamForSync;

//pfi
extern const T_CRANK_ANGLE      KfHWIO_phi_BoundaryFraction;

//knock
extern const uint32_t  DSP_LOW_PASS_FILTER_IIR_COEFF[] ;
extern const uint32_t DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF1[];
extern  const uint32_t DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF2[];
extern  const uint32_t DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF3[];

//spark
extern const T_MILLISECONDSb  KfSPRK_t_DwellInit;
extern const T_MILLISECONDSb  KfSPRK_t_CrankMinDwellInit ;
extern const T_MILLISECONDSb KfSPRK_t_CrankMaxDwellInit ;

//vesp


typedef struct
{

    uint16_t         KeVSEP_VR1_MT : 3;                /* byte   0, bit  5~7  */
    uint16_t         KbVSEP_VR1_PERC50 : 1;                /* byte   0, bit   4  */
    uint16_t         KbVSEP_VR1_RST : 1;                /* byte   0, bit   3  */
    uint16_t         KeVSEP_VR1_dummy_bit1 : 3;                /* byte   0, bit   0~2  */
    uint16_t         KeVSEP_VR1_DLY : 7;               /* byte   1, bit   1~7  */
    uint16_t         KbVSEP_VR1_dummy_bit2 : 1;             /* byte   1, bits 0 */

}KsVSEP_VR1_Setting_Cals;
typedef struct
{
    uint8_t         KeVSEP_VR1_DLY : 7;
    uint8_t         Unused : 1;
}KsVSEP_VR1_HeavyDelay_T;


typedef struct
{

    uint16_t         KeVSEP_VR2_MT : 3;                /* byte   0, bit   5~7  */
    uint16_t         KbVSEP_VR2_PERC50 : 1;                /* byte   0, bit   4 */
    uint16_t         KbVSEP_VR2_RST : 1;                /* byte   0, bit   3 */
    uint16_t         KeVSEP_VR2_dummy_bit1 : 3;                /* byte   0, bit   0~2  */
    uint16_t         KeVSEP_VR2_DLY : 7;               /* byte   1, bit   1~7  */
    uint16_t         KbVSEP_VR2_dummy_bit2 : 1;             /* byte   1, bits 0*/

}KsVSEP_VR2_Setting_Cals;
typedef struct
{

    uint16_t         KeVSEP_DEPSDLY_dummy_bit1 : 8;                /* byte   0, bit   0~7  */
    uint16_t         KeVSEP_DEPSDLY : 7;                			/* byte   1, bit   1~7  */
    uint16_t        KbVSEP_DEPSDLY_dummy_bit2 : 1;                /* byte   1, bit   0  */

}KsVSEP_DEPSDLY_Setting_Cals;

typedef struct
{

    uint16_t         KeVSEP_SLEW4: 2;                /* byte   0, bit   6~7  */
    uint16_t         KeVSEP_SLEW5 : 2;                /* byte   0, bit   4~5  */
    uint16_t         KeVSEP_SLEWCAN : 2;                /* byte   0, bit  2~3  */
    uint16_t         KeVSEP_SLEW_dummy_bit : 2;                /* byte   0, bit    0~1 */
    uint16_t         KeVSEP_SLEW1 : 2;               /* byte   1, bit   6~7  */
    uint16_t         KeVSEP_SLEW2 : 3;             /* byte   1, bits 3~5 */
    uint16_t         KeVSEP_SLEW3 : 3;             /* byte   1, bits 0~2 */

}KsVSEP_SLEW_Cals;

typedef struct
{

    uint16_t         KeVSEP_FLTLVL3: 3;                /* byte   0, bit   5~7 */
    uint16_t         KeVSEP_FLTLVL4 : 4;                /* byte   0, bit   1~4  */
    uint16_t         KbVSEP_FLTLVL_dummy_bit1 : 1;                /* byte   0, bit   0  */
    uint16_t         KeVSEP_FLTLVL1 : 4;                /* byte   1, bit  4~7  */
    uint16_t         KeVSEP_FLTLVL2 : 3;                /* byte   1, bit    1~3 */
    uint16_t         KbVSEP_FLTLVL_dummy_bit2 : 1;                /* byte   1, bit   0  */

}KsVSEP_Fault_Level_Cals1;


typedef struct
{

    uint16_t         KeVSEP_FLTLVL7: 3;                /* byte   0, bit   5~7 */
    uint16_t         KeVSEP_FLTLVL_dummy_bit3 : 5;                /* byte   0, bit  0~4  */
    uint16_t         KeVSEP_FLTLVL5 : 4;                /* byte   1, bit  4~7  */
    uint16_t         KeVSEP_FLTLVL6 : 3;                /* byte   1, bit    1~3 */
    uint16_t         KbVSEP_FLTLVL_dummy_bit4 : 1;                /* byte   1, bit   0  */

}KsVSEP_Fault_Level_Cals2;


typedef struct
{

    uint16_t         KeVSEP_FILT_17TO18: 2;                /* byte   0, bit   6~7 */
    uint16_t         KeVSEP_FILT_19TO20: 2;                /* byte   0, bit  4~5  */
    uint16_t         KeVSEP_FILT_21TO24: 2;                /* byte   0, bit  2~3  */
    uint16_t         KeVSEP_FILT_25TO30: 2;                /* byte   0, bit    0~1 */
    uint16_t         KeVSEP_FILT_1TO8SP: 2;                /* byte   1, bit   6~7 */
    uint16_t         KeVSEP_FILT_1TO8NS: 2;                /* byte   1, bit  4~5 */
    uint16_t         KeVSEP_FILT_9TO12: 2;                /* byte   1, bit  2~3  */
    uint16_t         KeVSEP_FILT_13TO16: 2;                /* byte   1, bit    0~1 */

}KsVSEP_Fault_Filter_Cals;


typedef struct
{

    uint16_t         KeVSEP_LEDMODE_dummy_bit1: 8;                /* byte   0, bit   0~7 */
    uint16_t         KbVSEP_LEDMODE_25: 1;                /* byte   1, bit  7  */
    uint16_t         KbVSEP_LEDMODE_26: 1;                /* byte   1, bit  6  */
    uint16_t         KbVSEP_LEDMODE_30: 1;                /* byte   1, bit    5 */
    uint16_t         KeVSEP_LEDMODE_dummy_bit2: 5;                /* byte   1, bit   0~4 */

}KsVSEP_LEDMODE_Cals;


typedef struct
{
    uint16_t         KeVSEP_GRAD_dummy_bit1: 8;                /* byte   0, bit   0~7 */
    uint16_t         KbVSEP_GRADFILT: 3;                /* byte   1, bit  5~7  */
    uint16_t         KbVSEP_GRADTHR: 3;                /* byte   1, bit  2~4  */
    uint16_t         KeVSEP_GRAD_dummy_bit2: 2;                /* byte   1, bit    0~1 */
	
}KsVSEP_GRAD_Cals;


 typedef struct
{

    uint16_t         KeVSEP_Spark_CYLCNT: 3;          /* byte   0, bit   5~7 */
    uint16_t         KbVSEP_Spark_DEC_DISCB: 1;     /* byte   0, bit  4  */
    uint16_t         KbVSEP_Spark_IGBTCFG: 1;         /* byte   0, bit  3  */
    uint16_t         KbVSEP_Spark_dummy_bit1: 3;         /* byte   0, bit  0~2  */
    uint16_t         KbVSEP_Spark_EDGE: 1;              /* byte   1, bit  7  */
    uint16_t         KbVSEP_Spark_INDEX: 1;             /* byte   1, bit  6  */
    uint16_t         KeVSEP_Spark_PFMODE: 1;          /* byte   1, bit    5 */
    uint16_t         KbVSEP_Spark_dummy_bit2: 5;          /* byte   1, bit  0~4  */

}KsVSEP_Spark_Mode_Cals;

extern const  KsVSEP_VR1_Setting_Cals  KsVSEP_VR1_Setting_Initial;
extern const  KsVSEP_VR1_HeavyDelay_T  KsVSEP_VR1_Setting_Initial_Crank;
extern const  KsVSEP_VR2_Setting_Cals  KsVSEP_VR2_Setting_Initial;
extern const  KsVSEP_DEPSDLY_Setting_Cals  KsVSEP_DEPSDLY_Setting_Initial;
extern const  KsVSEP_SLEW_Cals  KsVSEP_SLEW_Initialization;
extern const  KsVSEP_Fault_Level_Cals1  KsVSEP_Fault_Level_Initial1;
extern const  KsVSEP_Fault_Level_Cals2  KsVSEP_Fault_Level_Initial2;
extern const  KsVSEP_Fault_Filter_Cals  KsVSEP_Fault_Filter_Initial;
extern const  KsVSEP_LEDMODE_Cals  KsVSEP_LEDMODE_Initial;
extern const  KsVSEP_GRAD_Cals  KsVSEP_GRAD_Initialization;
//extern const  KsVSEP_HW_Protect_Enable   KsVSEP_HW_Protect_Setting;
extern const  KsVSEP_Spark_Mode_Cals  KsVSEP_Spark_Mode_Initialization;
extern const VSEP_MPIO_Input_Mode_T KeHWIO_ACReq_pin79_Status ;

extern const VSEP_MPIO_Input_Mode_T KeHWIO_PSPS_pin60_Status;

extern const VSEP_MPIO_Input_Mode_T KeHWIO_MIDAC_pin40_Status;

extern const  uint16_t KsVSEP_Diagnostic_Counter_Thd;

extern const uint8_t KSOHCRTH;

extern const bool K_Can_Meter_MIL_Disable;
extern const bool K_Can_Meter_TACH_Disable;
extern const bool K_Can_Meter_Fuel_Consum_Disable;

#endif

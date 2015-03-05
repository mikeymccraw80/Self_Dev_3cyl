#ifndef MG_HAL_IO_MAP_H
#define MG_HAL_IO_MAP_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_hal_io_map.h %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:                  %
//
// %version:         11 %
//
//=============================================================================

// #include "io.h"
// #include "io_interface.h"
// #include "mg_io_interface_override.h"
#include "io_config_qadc.h"
#include "io_config_siu.h"
#include "io_config_vsep.h"
#include "io_config_mios.h"
#if 0
#define MG_MTSA_CONFIG_KP254_TRIG_DIAG \
         (   KP254_Set_Device_Index( 0,KP254_INDEX_0                 ) |\
           KP254_Set_Reset_Strategy( 0,KP254_RESET_FAILURES          ) |\
                  KP254_Set_Message( 0,KP254_MESSAGE_Trigger_DIAG) )

#define MG_MTSA_CONFIG_KP254_ACQ_ID \
         (   KP254_Set_Device_Index( 0,KP254_INDEX_0                 ) |\
           KP254_Set_Reset_Strategy( 0,KP254_RESET_FAILURES          ) |\
                  KP254_Set_Message( 0,KP254_MESSAGE_ACQ_ID) )
#endif


// analog input map
//remap null to 0xff, for NULL(0x00) is conflicted with AD_Analog_T
#define   MG_HIODEVICE_NULL                      0XFF 
// #define   MG_HIODEVICE_AN00                      (void *)&ESCHiVI
// #define   MG_HIODEVICE_AN01                      (void *)&ESCLoVI
#define   MG_HIODEVICE_AN00                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN01                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN02                      AD_MAPVI_Channel
#define   MG_HIODEVICE_AN03                      AD_ACPREVI_Channel
#define   MG_HIODEVICE_AN04                      AD_LEGRFBVI_Channel
// #define   MG_HIODEVICE_AN05                      (void *)&TPS1VI
// #define   MG_HIODEVICE_AN06                      (void *)&TPS2VI
#define   MG_HIODEVICE_AN05                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN06                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN07                      AD_PPS1VI_Channel
#define   MG_HIODEVICE_AN08                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN09                      AD_PPS2VI_Channel
#define   MG_HIODEVICE_AN10                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN11                      AD_FLVVI_Channel
#define   MG_HIODEVICE_AN12                      AD_SPA1VI_Channel
#define   MG_HIODEVICE_AN13                      AD_O2AVI_Channel
#define   MG_HIODEVICE_AN14                      AD_O2BVI_Channel
#define   MG_HIODEVICE_AN15                      AD_CRSVI_Channel
#define   MG_HIODEVICE_AN16                      AD_CLTVI_Channel
#define   MG_HIODEVICE_AN17                      AD_MATVI_Channel
#define   MG_HIODEVICE_AN18                      AD_BSTATVI_Channel
#define   MG_HIODEVICE_AN19                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN20                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN21                      AD_FREPVI_Channel
#define   MG_HIODEVICE_AN22                      AD_BKVAVII_Channel
#define   MG_HIODEVICE_AN23                      AD_RREPVI_Channel
#define   MG_HIODEVICE_AN24                      AD_BSTPREVI_Channel
#define   MG_HIODEVICE_AN25                      AD_RRVI_Channel
#define   MG_HIODEVICE_AN26                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN27                      AD_PSREF1_Channel
#define   MG_HIODEVICE_AN28                      AD_PSREF2_Channel
#define   MG_HIODEVICE_AN29                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN30                      AD_IGNVI_Channel
#define   MG_HIODEVICE_AN31                      AD_58XRAWIN_Channel
#define   MG_HIODEVICE_AN32                      AD_PBATTVI_Channel
// #define   MG_HIODEVICE_AN33                      (void *)&GND123VI
// #define   MG_HIODEVICE_AN34                      (void *)&GND122VI 
// #define   MG_HIODEVICE_AN35                      (void *)&GND121VI 
#define   MG_HIODEVICE_AN33                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN34                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN35                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN36                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN37                      MG_HIODEVICE_NULL
#define   MG_HIODEVICE_AN38                      AD_HWCFGVI_Channel
#define   MG_HIODEVICE_AN39                      AD_VCC2_Channel

#if 0
// knock analog map
#define   MG_HIODEVICE_KNOCK_HIGH          (void *)&ESCHiVI
#define   MG_HIODEVICE_KNOCK_LOW           (void *)&ESCLoVI
#endif


// discrete out map
#define   MG_HIODEVICE_DO_NULL                   0xFFFFFFFF
#define   MG_HIODEVICE_DO_DFB05                  VSEP_DO_MPR_CH
#define   MG_HIODEVICE_DO_DFB06                  VSEP_DO_FPR_CH
#define   MG_HIODEVICE_DO_DFB07                  VSEP_DO_ACCLUTCH_CH
#define   MG_HIODEVICE_DO_DFB08                  VSEP_DO_FAN2_CH
//#define   MG_HIODEVICE_DO_DFB11                  (void *)&MG_MTSA_D_OUT_INJ4
//#define   MG_HIODEVICE_DO_DFB12                  (void *)&MG_MTSA_D_OUT_INJ2
#define   MG_HIODEVICE_DO_DFB13                  MIOS_FUELCONCTL_CH
#define   MG_HIODEVICE_DO_DFB14                  VSEP_DO_IMMOREQ_CH
#define   MG_HIODEVICE_DO_DFB15                  VSEP_PO_FAN1_CH
#define   MG_HIODEVICE_DO_DFB16                  VSEP_PO_CCP_CH
#define   MG_HIODEVICE_DO_DFB17                  MIOS_VVT1CTL_CH
#define   MG_HIODEVICE_DO_DFB18                  MIOS_VVT2CTL_CH
#define   MG_HIODEVICE_DO_DFB19                  VSEP_DO_VGIS1_CH
#define   MG_HIODEVICE_DO_DFB20                  VSEP_DO_VGIS2_CH
#define   MG_HIODEVICE_DO_DFB21                  VSEP_PO_O2AHTR_CH
#define   MG_HIODEVICE_DO_DFB22                  VSEP_PO_O2BHTR_CH
// #define   MG_HIODEVICE_DO_DFB23                  (void *)&MTSA_PWM_CLTPUMPCTL
#define   MG_HIODEVICE_DO_DFB23                  MG_HIODEVICE_DO_NULL
#define   MG_HIODEVICE_DO_DFB24                  VSEP_PO_ALTCTL_CH
#define   MG_HIODEVICE_DO_DFB25                  VSEP_DO_MIL_CH
#define   MG_HIODEVICE_DO_DFB26                  VSEP_DO_SVS_CH
#define   MG_HIODEVICE_DO_DFB27                  VSEP_PO_CLTGAUGE_CH
#define   MG_HIODEVICE_DO_DFB28                  VSEP_PO_SMR_CH
#define   MG_HIODEVICE_DO_DFB29                  VSEP_PO_TACH_CH
#define   MG_HIODEVICE_DO_DFB30                  VSEP_PO_CRUISI_CH

#if 0
// EST - EST1:DFB01 EST2:DFB02 EST3:DFB03 EST4:DFB04
#define   MG_HIODEVICE_SPARK                     (void *)&MTSA_SPARK
#define   MG_HIODEVICE_DO_EST1                   (void *)&MG_MTSA_D_OUT_EST1
#define   MG_HIODEVICE_DO_ESTSYNC                (void *)&MG_MTSA_D_OUT_ESTSYNC

// INJ
#define   MG_HIODEVICE_DO_DFB09                  (void *)&MG_MTSA_D_OUT_INJ1
#define   MG_HIODEVICE_DO_DFB10                  (void *)&MG_MTSA_D_OUT_INJ2
#define   MG_HIODEVICE_DO_DFB11                  (void *)&MG_MTSA_D_OUT_INJ3
#define   MG_HIODEVICE_DO_DFB12                  (void *)&MG_MTSA_D_OUT_INJ4
#endif
// ETC
// #define   MG_HIODEVICE_ETC_PWM                   (void *)&MTSA_PWM_ETCCTLPWM
// #define   MG_HIODEVICE_ETCDIR                    (void *)&MTSA_D_OUT_ETC_DIR
// #define   MG_HIODEVICE_ETCDIS                    (void *)&MTSA_D_OUT_ETC_DIS
// #define   MG_HIODEVICE_ETCCS                     (void *)&MTSA_D_OUT_ETCCS
#define   MG_HIODEVICE_ETC_NULL                  0xFFFFFFFF
#define   MG_HIODEVICE_ETC_PWM                   MIOS_ETCCTLPWM_CH
#define   MG_HIODEVICE_ETCDIR                    HAL_GPIO_ETCDIR_CHANNEL
#define   MG_HIODEVICE_ETCDIS                    HAL_GPIO_ETCDIS_CHANNEL
#define   MG_HIODEVICE_ETCCS                     MG_HIODEVICE_ETC_NULL
#if 0
// RTI
#define   MG_HIODEVICE_RTI                       (void *)&MTSA_RTI_TIMER
#endif


// discrete in map
#define   MG_HIODEVICE_DI_NULL                   0xFFFFFFFF
// #define   MG_HIODEVICE_DI_MPIO1                  (void *)&MTSA_D_IN_J1_79
// #define   MG_HIODEVICE_DI_MPIO2                  (void *)&MTSA_D_IN_J1_60
// #define   MG_HIODEVICE_DI_MPIO3                  (void *)&MTSA_D_IN_J1_40
#define   MG_HIODEVICE_DI_MPIO1                  MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_MPIO2                  MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_MPIO3                  MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_GPIO139                HAL_GPIO_ELOAD1DI_CHANNEL
#define   MG_HIODEVICE_DI_GPIO138                HAL_GPIO_ELOAD2DI_CHANNEL
#define   MG_HIODEVICE_DI_GPIO224                HAL_GPIO_BRKLMPDI_CHANNEL
#define   MG_HIODEVICE_DI_GPIO121                HAL_GPIO_BRKSWDI_CHANNEL
// #define   MG_HIODEVICE_DI_GPIO122                (void *)&MTSA_D_IN_J1_45
#define   MG_HIODEVICE_DI_GPIO122                MG_HIODEVICE_DI_NULL
// #define   MG_HIODEVICE_DI_AN4                    (void *)&MTSA_D_IN_Analog_J1_55_LoActive
// #define   MG_HIODEVICE_DI_AN12                   (void *)&MTSA_D_IN_Analog_J1_56_LoActive
// #define   MG_HIODEVICE_DI_AN24                   (void *)&MTSA_D_IN_Analog_J1_57_LoActive
// #define   MG_HIODEVICE_DI_AN3                    (void *)&MTSA_D_IN_Analog_J1_53_HighActive
// #define   MG_HIODEVICE_DI_AN25                   (void *)&MTSA_D_IN_Analog_J1_59_HighActive
// #define   MG_HIODEVICE_DI_AN23                   (void *)&MTSA_D_IN_Analog_J1_29_LoActive
// #define   MG_HIODEVICE_DI_AN18                   (void *)&MTSA_D_IN_Analog_J1_72_LoActive
// #define   MG_HIODEVICE_DI_AN15                   (void *)&MTSA_D_IN_Analog_J1_26_HighActive
#define   MG_HIODEVICE_DI_AN4                    MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_AN12                   MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_AN24                   MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_AN3                    MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_AN25                   MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_AN23                   MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_AN18                   MG_HIODEVICE_DI_NULL
#define   MG_HIODEVICE_DI_AN15                   MG_HIODEVICE_DI_NULL

#if 0
// Frequency in map
#define   MG_HIODEVICE_FI_CAM1                   (void *)&MG_MTSA_IC_CAM1
#define   MG_HIODEVICE_FI_ABSPWM                 (void *)&MTSA_IC_WSSFI
#define   MG_HIODEVICE_FI_CAM2                   (void *)&MG_MTSA_IC_CAM2
#define   MG_HIODEVICE_FI_VSS                    (void *)&MG_MTSA_IC_VSS
#define   MG_HIODEVICE_FI_ENS                    (void *)&MG_MTSA_IC_ENS
#define   MG_HIODEVICE_FI_Alternator             (void *)&MTSA_IC_Alternator//zhoushenghui20131217
#define   MG_HIODEVICE_FI_58XPOS                 (void *)&MG_MTSA_IC_58XPOS

// Baro
#define	MG_HIODEVICE_BARO_PRESSURE		(void *)&BARO_Prussure_I
#define	MG_HIODEVICE_BARO_TEMPERATURE	(void *)&BARO_Temperature_I
#endif
#endif /* end of include guard: MG_HAL_IO_MAP_H */

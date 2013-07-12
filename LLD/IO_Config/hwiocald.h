#ifndef HWIOCALD_H
#define HWIOCALD_H


//=============================================================================
// include files
//=============================================================================
#include "hal.h"

//=============================================================================
// type define
//=============================================================================


//=============================================================================
// extern variables
//=============================================================================
//crank
extern const uint8_t     KyHWIO_ToothOfFirstLoResEvent;
extern const uint8_t     KyHWIO_ToothOfCAMRefEvent;
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

//DI high active or not
extern const   bool        KbHWIO_ELOAD1_Active_High;
extern const   bool        KbHWIO_ELOAD2_Active_High;
extern const   bool        KbHWIO_BRKLMP_Active_High;

#endif

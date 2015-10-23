

#ifndef IO_CONFIG_CRANK_H
#define IO_CONFIG_CRANK_H

#include "dd_crank.h"

extern const MCD5408_Channel_Init_T  EPPWMT_INIT;


//=============================================================================
//   Constant Data Defines
//=============================================================================

// for dynamic crank scheduling
#if CcSYST_NUM_OF_CYLINDERS == 3
#define CRANK_CONFIG_NUMBER_OF_CYLINDERS     (3)
#else 
#define CRANK_CONFIG_NUMBER_OF_CYLINDERS     (4)
#endif

#define CRANK_MAX_CYLINDERS  CRANK_CONFIG_NUMBER_OF_CYLINDERS
#define CRANK_SCHEDULE_CONFIG_VIRTUAL_TEETH_PER_REVOLUTION (120U)


#define CRANK_FILTER_MIN_RPM    (  50)
#define CRANK_FILTER_MAX_RPM    (7500)

//#define Conver_rpm_To_Time( x ) \
  // ( 120000 / x )

// number of real and virtual teeth on the 58X wheel
#define CRANK_VIRTUAL_TEETH_PER_CRANK           ( 60 )
#define CRANK_TEETH_PER_GAP                     ( 2 )
#define CRANK_ACTUAL_TEETH_PER_CRANK            ( CRANK_VIRTUAL_TEETH_PER_CRANK-CRANK_TEETH_PER_GAP) 

// number of degrees per tooth of the 58x tooh wheel
#define CRANK_NUMBER_OF_GAPS                    ( 2 )
#define CRANK_VIRTUAL_TEETH_PER_REVOLUTION      ( CRANK_VIRTUAL_TEETH_PER_CRANK * CRANK_NUMBER_OF_GAPS )
#define CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION  ( 720 ) 
#define CRANK_DEGREES_PER_TOOTH \
         ( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / CRANK_VIRTUAL_TEETH_PER_REVOLUTION )
         
//=============================================================================
// CRANK_INITIAL_INTERNAL_STATE
//=============================================================================
#define CRANK_INITIAL_INTERNAL_STATE \
   (0|\
   CRANK_Set_Sync_Occurred(                  0, false ) |\
   CRANK_Set_First_Sync_Occurred(            0, false ) |\
   CRANK_Set_Sync_Error_In_Progress(         0, false ) |\
   CRANK_Set_First_Cylinder_Event_Occured(   0, true  ) |\
   CRANK_Set_Power_Up(                       0, true  ) |\
   CRANK_Set_Filter_Enabled(                 0, true  ) |\
   CRANK_Set_Run_Reset_Bypass_Filter(        0, false ) |\
   CRANK_Set_Sync_Started(                   0, false ) |\
   CRANK_Set_Valid_Tooth(                    0, false ) |\
   CRANK_Set_Resync_Attempt_In_Prog(         0, false ))

//=============================================================================
// CRANK_RESET_CALLBACKS
//
// Provides a list of routines to be executed whenever a crank reset occurs.
// The order of execution is the same order the routines are placed within
// the constant.
//=============================================================================
#define PFI_BOUNDARY_EVENT                   CRANK_EVENT_ID_USER3
#define TDC_EVENT                            CRANK_EVENT_ID_USER4
#define SIX_X_EVENT                          CRANK_EVENT_ID_USER7
#define KNOCK_CYLINDER_EVENT                 CRANK_EVENT_ID_USER14
#define PFI_CYLINDER_EVENT                   CRANK_EVENT_ID_USER10
#define SPARK_CYLINDER_EVENT                 CRANK_EVENT_ID_USER11
#define VCP_CYLINDER_EVENT                   CRANK_EVENT_ID_USER12
#define CYLINDER_EVENT                       CRANK_EVENT_ID_USER13
#define CRANK_EVENT_ID_PER_CYLINDER_EVENT    CRANK_EVENT_ID_USER29
#define CRANK_EVENT_ID_SYNC                  CRANK_EVENT_ID_USER30
#define CRANK_EVENT_ID_CAM                   CRANK_EVENT_ID_USER31

//=============================================================================
// CRANK_EPPE_IRQ_Select
//=============================================================================
#define CRANK_EPPE_IRQ_Select    EPPWMT_IRQ_1


#endif

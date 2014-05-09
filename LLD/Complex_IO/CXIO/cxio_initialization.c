
//=============================================================================
// Includes
//=============================================================================

#include "hwiocald.h"
#include "dd_crank_interface.h"
#include "dd_spark_interface.h"
#include "dd_cam_interface.h"
#include "dd_tpu_interface.h"
#include "dd_pfi_interface.h"
#include "dd_knock_interface.h"
#include "io_config_crank.h"
#include "io_config_cam.h"
#include "os_sw_intc.h"



IO_Crank_Initialization_Parameters_T   IO_Init_Crank_Initialization_Parameters;
IO_PFI_Initialization_Parameters_T     IO_Init_Pfi_Initialization_Parameters;
IO_Cam_Initialization_Parameters_T     IO_Init_Cam_Initialization_Parameters;
bool                                   IO_Init_Cam_Active_Cylinders[CAM_NUMBER_OF_SENSORS];


static void CRANK_Scheduler_Initialize( void )
{
   uint32_t cylinders                  = IO_Init_Crank_Initialization_Parameters.number_of_cylinders;
   uCrank_Angle_T cylinder_offset      = CRANK_Convert_Angle_To_uCrank_Angle( ( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / cylinders ), 0 );
   uCrank_Angle_T crank_offset         = CRANK_Convert_Angle_To_uCrank_Angle( ( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / 2 ), 0 );
   uCrank_Angle_T sync_event           = IO_Init_Crank_Initialization_Parameters.synchronization_start_angle;
   uCrank_Angle_T cam_event            = IO_Init_Cam_Initialization_Parameters.cam_read_angle;
   uCrank_Angle_T first_cylinder_event = IO_Init_Crank_Initialization_Parameters.first_cylinder_event_angle;
   uCrank_Angle_T six_x_offset         = CRANK_Convert_Angle_To_uCrank_Angle( ( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / 12 ), 0 );
   uCrank_Angle_T tdc_event            = IO_Init_Crank_Initialization_Parameters.first_cylinder_event_angle +
                                         IO_Init_Crank_Initialization_Parameters.degrees_top_dead_center;

   uCrank_Angle_T pfi_boundary_event   = IO_Init_Crank_Initialization_Parameters.first_cylinder_event_angle +
                                         CRANK_Convert_Angle_To_uCrank_Angle(KfHWIO_phi_BoundaryFraction,S_CRANK_ANGLE );




   //   EVENT_ID_PRIORITY                    in_first_event_angle    in_event_angle_offset   in_number_of_events
   CRANK_SCHEDULER_Assign_Handler_To_Event_ID( CRANK_EVENT_ID_CAM, CAM_Update_State    );
   CRANK_SCHEDULER_Assign_Event(  CRANK_EVENT_ID_CAM,                  cam_event,              crank_offset,           2 );
  // CRANK_SCHEDULER_Assign_Handler_To_Event_ID( CRANK_EVENT_ID_PER_CYLINDER_EVENT,CRANK_High_Priority_Cylinder_Event   );
  // CRANK_SCHEDULER_Assign_Event(   CRANK_EVENT_ID_PER_CYLINDER_EVENT,   first_cylinder_event,   cylinder_offset,        cylinders );
   CRANK_SCHEDULER_Assign_Handler_To_Event_ID( KNOCK_CYLINDER_EVENT, KNOCK_Cylinder_Event_MultiKnock    );
   CRANK_SCHEDULER_Assign_Event(  KNOCK_CYLINDER_EVENT,                first_cylinder_event,   cylinder_offset,        cylinders );
   //CRANK_SCHEDULER_Assign_Event(  VCP_CYLINDER_EVENT,                  first_cylinder_event,   cylinder_offset,        cylinders );
   // CRANK_SCHEDULER_Assign_Handler_To_Event_ID( SPARK_CYLINDER_EVENT, SPARK_Process_Cylinder_Event    );
   // CRANK_SCHEDULER_Assign_Event(   SPARK_CYLINDER_EVENT,                first_cylinder_event,   cylinder_offset,        cylinders );
   //CRANK_SCHEDULER_Assign_Handler_To_Event_ID( PFI_CYLINDER_EVENT,  PFI_Process_Cylinder_Event          );
  // CRANK_SCHEDULER_Assign_Event(  PFI_CYLINDER_EVENT,                  first_cylinder_event,   cylinder_offset,        cylinders );
   CRANK_SCHEDULER_Assign_Handler_To_Event_ID( CYLINDER_EVENT,  OS_SCHEDULER_Cylinder_Event         );
   CRANK_SCHEDULER_Assign_Event(  CYLINDER_EVENT,                      first_cylinder_event,   cylinder_offset,        cylinders );
   CRANK_SCHEDULER_Assign_Handler_To_Event_ID(SIX_X_EVENT,  OS_SCHEDULER_6X_Event         );
   CRANK_SCHEDULER_Assign_Event(   SIX_X_EVENT,                         first_cylinder_event,   six_x_offset,           12 );
   CRANK_SCHEDULER_Assign_Handler_To_Event_ID(TDC_EVENT, OS_SCHEDULER_TDC_Event        );
   CRANK_SCHEDULER_Assign_Event(   TDC_EVENT,                           tdc_event,              cylinder_offset,        cylinders );
   CRANK_SCHEDULER_Assign_Handler_To_Event_ID( PFI_BOUNDARY_EVENT, PFI_Perform_Injection_Tasks       );
   CRANK_SCHEDULER_Assign_Event(   PFI_BOUNDARY_EVENT,                  pfi_boundary_event,     cylinder_offset,        cylinders );

}

void InitializeComplexIO( void )
{

   //=============================================================================
   // Hardware Test copies const values to be placed into the algorithms to aid
   // in white box testing.
   //=============================================================================
   // set up local structure to pass in init values
   IO_Init_Crank_Initialization_Parameters.rpm_synchronization_criteria = CRANK_Convert_Angle_To_uCrank_Angle( 312, 2);//CRANK_INITIALIZATION_PARAMETERS.rpm_synchronization_criteria;
   // new field members in IO_Crank_Initialization_Parameters_T 
   IO_Init_Crank_Initialization_Parameters.filter_min_rpm_for_synchronization    = CRANK_FILTER_MIN_RPM;
   IO_Init_Crank_Initialization_Parameters.filter_max_rpm_for_synchronization    = CRANK_FILTER_MAX_RPM;


   IO_Init_Crank_Initialization_Parameters.number_of_cylinders          = CRANK_CONFIG_NUMBER_OF_CYLINDERS;
   IO_Init_Crank_Initialization_Parameters.valid_synchronization_tooth_periods   = KyHWIO_NumValidPeriodsBeforeSyncStart;
   IO_Init_Crank_Initialization_Parameters.synchronization_start_angle  = CRANK_Convert_Teeth_To_uCrank_Angle(KyHWIO_CrankSyncStartTooth);
   IO_Init_Crank_Initialization_Parameters.first_cylinder_event_angle   = CRANK_Convert_Teeth_To_uCrank_Angle(KyHWIO_ToothOfFirstLoResEvent);
   IO_Init_Crank_Initialization_Parameters.degrees_top_dead_center      = CRANK_Convert_Angle_To_uCrank_Angle(KfHWIO_phi_TopDeadCenter,S_CRANK_ANGLE );
   IO_Init_Pfi_Initialization_Parameters.boundary_fraction = CRANK_Convert_Angle_To_uCrank_Angle(KfHWIO_phi_BoundaryFraction, S_CRANK_ANGLE);

   IO_Init_Cam_Active_Cylinders[CAM1] = (KeHWIO_Cam1OccurredTrue) ? true : false;
   IO_Init_Cam_Active_Cylinders[CAM2] = (KeHWIO_Cam2OccurredTrue) ? true : false;
   IO_Init_Cam_Initialization_Parameters.number_of_gaps_before_sync = KyHWIO_Num58xGapsBeforeSeqn;
   IO_Init_Cam_Initialization_Parameters.number_of_toggles_before_sync = KyHWIO_Num58xGapsUsingCamForSync;
   IO_Init_Cam_Initialization_Parameters.cam_read_angle = CRANK_Convert_Angle_To_uCrank_Angle(KyHWIO_phi_ToothAngleForCamRead, S_CRANK_ANGLE);

    IO_Init_Cam_Initialization_Parameters.CAM_Active_State = (bool * const )IO_Init_Cam_Active_Cylinders;
    IO_Init_Cam_Initialization_Parameters.use_cam_toggle = CAM_INITIALIZATION_PARAMETERS.use_cam_toggle;

   CRANK_Initialize(  (IO_Crank_Initialization_Parameters_T  * const)&IO_Init_Crank_Initialization_Parameters );

   CRANK_Scheduler_Initialize();

   CAM_Initialize( (IO_Cam_Initialization_Parameters_T  * const)&CAM_INITIALIZATION_PARAMETERS );
   CAM_Initialize_4X_Config(CAM1);
   CAM_Initialize_4X_Config(CAM2);
   // set CAM channel
   CAM_Select_Sensor(CAM1);

  PFI_Initialize((IO_PFI_Initialization_Parameters_T  * const)&IO_Init_Pfi_Initialization_Parameters );

  // IO_KNOCK_Set_OS_End_Of_Window_CallBack( &MTSA_KNOCK, NULL  );
   KNOCK_Initialize();
//#ifndef HWTEST
  // IO_KNOCK_Initialize( &MTSA_KNOCK, (IO_Knock_Initialization_Parameters_T  * const)&MTSA_KNOCK_INITIALIZATION_PARAMETERS );
//#endif


   SPARK_Initialize( (IO_Spark_Initialization_Parameters_T  * const)&MTSA_SPARK_INITIALIZATION_PARAMETERS );
   CRANK_Reset_Parameters();
   CRANK_Enable_Synchronization();

}


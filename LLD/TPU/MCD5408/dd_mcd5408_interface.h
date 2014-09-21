#ifndef DD_MCD5408_INTERFACE_H
#define DD_MCD5408_INTERFACE_H

#include "dd_mcd5408.h"

//=============================================================================
// MCD5408_Initialize_Channel
//=============================================================================
extern void MCD5408_Initialize_Channel(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
    MCD5408_Channel_Init_T const *parameters   
   );


//=============================================================================
// MCD5408_Shutdown
//=============================================================================
extern void MCD5408_Shutdown(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure);
//=============================================================================
// MCD5408_Enable_Host_Interrupt
//=============================================================================
void MCD5408_Enable_Host_Interrupt(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Disable_Host_Interrupt
//=============================================================================
void MCD5408_Disable_Host_Interrupt(
         TPU_Index_T index,
         TPU_T         *p_tpu,
          TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Get_Buffered_Edge_Time
//=============================================================================
uint32_t MCD5408_Get_Buffered_Edge_Time(
      TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   // MCD5408 supports more than one IRQ, so an argument is added to select the IRQ
   EPPwMT_IRQ_T in_irq );



//=============================================================================
// MCD5408_Get_Coherent_Edge_Time_And_Count
//=============================================================================
EPPwMT_Coherent_Edge_Time_And_Count_T * MCD5408_Get_Coherent_Edge_Time_And_Count(
    TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_Coherent_Edge_Time_And_Count_T *in_edge_time_and_count );
                
//=============================================================================
// MCD5408_Get_IRQ_Count_At_Last_Interrupt
//=============================================================================
uint16_t MCD5408_Get_IRQ_Count_At_Last_Interrupt(
      TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_IRQ_T    in_irq );

//=============================================================================
// MCD5408_Get_IRQ_Count
//=============================================================================
uint16_t MCD5408_Get_IRQ_Count(
        TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_IRQ_T    in_irq );

//=============================================================================
// MCD5408_Get_Period
//=============================================================================
uint32_t MCD5408_Get_Period(
        TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Set_Previous_n_1
//=============================================================================
void MCD5408_Set_Previous_n_1(
          TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   uint16_t       in_previous_n_1 );

//=============================================================================
// MCD5408_Get_Previous_n_1
//=============================================================================
uint16_t MCD5408_Get_Previous_n_1(
          TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Set_Previous_1_n
//=============================================================================
void MCD5408_Set_Previous_1_n(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   uint16_t       in_previous_1_n );

//=============================================================================
// MCD5408_Get_Previous_1_n
//=============================================================================
uint16_t MCD5408_Get_Previous_1_n(
           TPU_Index_T index,
  TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Set_New_IRQ_Count
//=============================================================================
void MCD5408_Set_New_IRQ_Count(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_IRQ_T    in_irq,
   uint16_t        in_new_irq_count);


//=============================================================================
// MCD5408_Set_Next_IRQ_Cnt_Via_Delta
//=============================================================================
void MCD5408_Set_Next_IRQ_Cnt_Via_Delta(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_IRQ_T    in_irq,
   uint16_t        in_new_irq_count);

//=============================================================================
// MCD5408_Set_New_Gap_Count
//=============================================================================
void MCD5408_Set_New_Gap_Count(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   uint16_t       in_pulse_count );

//=============================================================================
// MCD5408_Set_Gap_Count
//=============================================================================
void MCD5408_Set_Gap_Count(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   uint8_t        in_delta_teeth );

//=============================================================================
// MCD5408_Get_Gap_Count
//=============================================================================
uint16_t MCD5408_Get_Gap_Count(
            TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Update_IRQ_Count
//=============================================================================
void MCD5408_Update_IRQ_Count(
              TPU_Index_T index,
                 TPU_T         *p_tpu,
       TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Get_Real_Period
//=============================================================================
uint32_t MCD5408_Get_Real_Period(
             TPU_Index_T index,
     TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Get_Real_Edge_Time
//=============================================================================
uint32_t MCD5408_Get_Real_Edge_Time(
             TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  );

//=============================================================================
// MCD5408_Get_Real_Edge_Count
//=============================================================================
uint16_t MCD5408_Get_Real_Edge_Count(
             TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  );

//=============================================================================
// MCD5408_Get_Synthetic_Edge_Cnt
//=============================================================================
uint32_t MCD5408_Get_Synthetic_Edge_Cnt(
             TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  );


//=============================================================================
// MCD5408_Get_Time_Base
//=============================================================================
uint32_t MCD5408_Get_Time_Base(
              TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure  );

//=============================================================================
// MCD5408_Get_Max_Time
//=============================================================================
uint32_t MCD5408_Get_Max_Time(void );

//=============================================================================
// MCD5408_Set_Host_Interrupt_Status
//=============================================================================
void MCD5408_Set_Host_Interrupt_Status(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure  ,
   bool            in_interrupt_status );

//=============================================================================
// MCD5408_Get_Host_Interrupt_Status
//=============================================================================
bool MCD5408_Get_Host_Interrupt_Status(
    TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Set_Edge_Time_In_Array
//=============================================================================
void MCD5408_Set_Edge_Time_In_Array(
              TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  ,
   uint32_t       in_edge_time,
   uint16_t       in_edge_count );

//=============================================================================
// MCD5408_Get_Edge_Time_From_Array
//=============================================================================
uint32_t MCD5408_Get_Edge_Time_From_Array(
                TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure  ,
   uint16_t       in_edge_count );

//=============================================================================
// MCD5408_Set_Angle_Clock_Mode
//=============================================================================
void MCD5408_Set_Angle_Clock_Mode(
                TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  ,
   EPPwMT_Angle_Mode_T           in_mode );

//=============================================================================
// MCD5408_Get_Angle_Clock_Mode
//=============================================================================
EPPwMT_Angle_Mode_T MCD5408_Get_Angle_Clock_Mode(
                   TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure  );

//=============================================================================
// MCD5408_Get_Only_Edge_Time_From_Array
//=============================================================================
uint32_t MCD5408_Get_Only_Edge_Time_From_Array(
                  TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure ,
   uint16_t       in_edge_count );

//=============================================================================
// MCD5408_Set_Period_Calculation_Method
//=============================================================================
void MCD5408_Set_Period_Calculation_Method(
                     TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure ,
   bool           in_calculation_method );

//=============================================================================
// MCD5408_Get_Period_Calculation_Method
//=============================================================================
bool MCD5408_Get_Period_Calculation_Method(
                     TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Set_Gap_Period_Fmult
//=============================================================================
void MCD5408_Set_Gap_Period_Fmult(
                     TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure ,
   uint32_t       in_fractional_multiplier ); 

//=============================================================================
// MCD5408_Get_Gap_Period_Fmult
//=============================================================================
uint32_t MCD5408_Get_Gap_Period_Fmult(
                     TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_BACKUP_MODE_Initialize_Channel
//=============================================================================
void MCD5408_BACKUP_MODE_Initialize_Channel(
   TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure ,
   void            *in_init );

//=============================================================================
// MCD5408_BACKUP_MODE_Enter_Backup_Service_Request
//=============================================================================
void MCD5408_BACKUP_MODE_Enter_Backup_Service_Request(
    TPU_Index_T index,
   TPU_T         *p_tpu,
       TPU_CHANNEL_Configuration_T   configure ,
   uint32_t      in_backup_first_edge_time,
   uint32_t      in_backup_period,
   uint16_t      in_backup_first_edge_count,
   uint16_t      in_backups_between_cams );

//=============================================================================
// MCD5408_BACKUP_MODE_Exit_Backup_Service_Request
//=============================================================================
void MCD5408_BACKUP_MODE_Exit_Backup_Service_Request(
      TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure ,
   void          *in_init );
      
//=============================================================================
// MCD5408_BACKUP_MODE_Get_Coherent_Real_Edge_Time_And_Count
//=============================================================================
void MCD5408_BACKUP_MODE_Get_Coherent_Real_Edge_Time_And_Count(
       TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure ,
   EPPwMT_Coherent_Edge_Time_And_Count_T    *in_edge_time_and_count );

//=============================================================================
// MCD5408_BACKUP_MODE_Get_Pending_Backups
//=============================================================================
uint8_t MCD5408_BACKUP_MODE_Get_Pending_Backups(
        TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure  );

//=============================================================================
// MCD5408_Set_Links_Start1_And_Count1
//=============================================================================
void MCD5408_Set_Links_Start1_And_Count1(
          TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure ,
   uint8_t       in_tpu,
   uint8_t       in_start_1,
   uint8_t       in_count_1);

//=============================================================================
// MCD5408_Set_Links_Start2_And_Count2
//=============================================================================
void MCD5408_Set_Links_Start2_And_Count2(
           TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure ,
   uint8_t       in_tpu,
   uint8_t       in_start_2,
   uint8_t       in_count_2);

//=============================================================================
// MCD5408_Set_IRQ_X_Enable_Mask
//=============================================================================
void MCD5408_Set_IRQ_X_Enable_Mask(
            TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure , EPPwMT_IRQ_T in_irq, bool in_enable );

//=============================================================================
// MCD5408_Get_IRQ_X_Enable_Mask
//=============================================================================
bool MCD5408_Get_IRQ_X_Enable_Mask(
              TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure ,  EPPwMT_IRQ_T in_irq );

//=============================================================================
// MCD5408_Get_IRQ_X_Request
//=============================================================================
bool MCD5408_Get_IRQ_X_Request(
                 TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure , EPPwMT_IRQ_T in_irq );

//=============================================================================
// MCD5408_Clear_IRQ_X_Request
//=============================================================================
void MCD5408_Clear_IRQ_X_Request(
      TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure ,
   EPPwMT_IRQ_T in_irq );

//=============================================================================
// MCD5408_Get_Angle_Mode_Error
//=============================================================================
uint16_t MCD5408_Get_Angle_Mode_Error(
        TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Get_Gap_Detected_Count
//=============================================================================
uint16_t MCD5408_Get_Gap_Detected_Count(
        TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Set_Gap_Percent
//=============================================================================
void MCD5408_Set_Gap_Percent(
          TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure ,
   uint8_t         in_gap_percent );

//=============================================================================
// MCD5408_Set_Cam_Channel
//=============================================================================
void MCD5408_Set_Cam_Channel(
          TPU_Index_T index,
   uint8_t         cam_channel );

//=============================================================================
// MCD5408_Set_Filter_Time
//=============================================================================
void MCD5408_Set_Filter_Time(
            TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure ,
   uint16_t         in_filter_time );

//=============================================================================
// MCD5408_Set_IRQ_Enable
//=============================================================================
void MCD5408_Set_IRQ_Enable(
            TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure ,
   uint32_t         in_enable_mask );

//=============================================================================
// MCD5408_Get_IRQ_Requests
//=============================================================================
uint32_t MCD5408_Get_IRQ_Requests(
         TPU_Index_T index,
   TPU_T         *p_tpu,
       TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Get_CAM_History
//=============================================================================
uint32_t MCD5408_Get_CAM_History(            TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Set_Critical_Edge
//=============================================================================
void MCD5408_Set_Critical_Edge(
   TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure ,
   Edge_T       in_edge );

//=============================================================================
// MCD5408_Get_Real_Prev_Period
//=============================================================================
uint32_t MCD5408_Get_Real_Prev_Period(    TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  );


//=============================================================================
// MCD5408_Clear_Gap_History
//=============================================================================
void MCD5408_Clear_Gap_History( TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Init_Edge_Time_Buffer
//=============================================================================
void MCD5408_Init_Edge_Time_Buffer(    TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5408_Synthesize_Gap_In_History
//=============================================================================
void MCD5408_Synthesize_Gap_In_History( TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Get_Backup_Enabled
//=============================================================================
bool MCD5408_Get_Backup_Enabled( TPU_Index_T index,
   TPU_T         *p_tpu,
 TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Set_Abs_Edge_Count
//=============================================================================
void MCD5408_Set_Abs_Edge_Count(TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   uint8_t         in_edge_count );

//=============================================================================
// MCD5408_Get_Remaining_Synth_Teeth
//=============================================================================
uint32_t MCD5408_Get_Remaining_Synth_Teeth(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Get_Dir_Crank_PW
//=============================================================================
uint32_t MCD5408_Get_Dir_Crank_PW(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Get_Crank_Backwards
//=============================================================================
bool MCD5408_Get_Crank_Backwards(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Get_Accum_Reverse_Edges
//=============================================================================
uint16_t MCD5408_Get_Accum_Reverse_Edges(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Get_Accum_Edges
//=============================================================================
uint16_t MCD5408_Get_Accum_Edges(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Get_Abs_Edge_Count
//=============================================================================
uint8_t MCD5408_Get_Abs_Edge_Count(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_Set_Reverse_Detect_Enable
//=============================================================================
 void MCD5408_Set_Reverse_Detect_Enable(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   bool   in_revdetect_enable);

//=============================================================================
// MCD5408_Set_Reverse_Process_Enable
//=============================================================================
void MCD5408_Set_Reverse_Process_Enable(
     TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   bool   in_revprocess_enable);

//=============================================================================
// MCD5408_Set_LS_Gap_Detect_Disable
//=============================================================================
void MCD5408_Set_LS_Gap_Detect_Disable(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   bool   in_LS_gap_detect_disable);

//=============================================================================
// MCD5408_Set_Dir_PW_Threshold
//=============================================================================
void MCD5408_Set_Dir_PW_Threshold(
      TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   uint32_t   in_threshold);

//=============================================================================
// MCD5408_Set_Accum_Reverse_Edges
//=============================================================================
void MCD5408_Set_Accum_Reverse_Edges(
      TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   uint16_t   in_edges);

//=============================================================================
// MCD5408_Get_Chg_Dir_Count
//=============================================================================
uint8_t MCD5408_Get_Chg_Dir_Count(
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5408_BACKUP_MODE_Request_Backup_Edges
//=============================================================================
void MCD5408_BACKUP_MODE_Request_Backup_Edges(
    TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure ,
   uint32_t      in_backup_first_edge_time,
   uint32_t      in_backup_period,
   uint16_t      in_backup_first_edge_count,
   uint16_t      in_backups_between_cams );

#endif // DD_MCD5408_INTERFACE_H

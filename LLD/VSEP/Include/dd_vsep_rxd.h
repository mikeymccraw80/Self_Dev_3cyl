#ifndef DD_VSEP_RXD_H
#define DD_VSEP_RXD_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_vsep_rxd.h %
//
// created_by:       fz3pdz
//
// date_created:     Wed Mar  9 10:33:04 2005
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Thu Feb 15 14:42:34 2007 %
//
// %version:         1 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

typedef enum
{
   VSEP_RXD_SDOA_FAULT              =  0,
   VSEP_RXD_SDOA_RESPONSE_CNT       =  1,

   VSEP_RXD_SDOA_EST_STAT           =  2, 
   VSEP_RXD_SDOA_Mx_INPUT           =  3,
   VSEP_RXD_SDOA_CHALLENGE          =  4,

   VSEP_RXD_SDOA_FAULT_GRP_5        =  5,
   VSEP_RXD_SDOA_FAULT_GRP_6        =  6,
   VSEP_RXD_SDOA_FAULT_GRP_56       =  5,
                                    
   VSEP_RXD_SDOA_FAULT_GRP_7        =  7,
   VSEP_RXD_SDOA_FAULT_GRP_8        =  8,
   VSEP_RXD_SDOA_FAULT_GRP_78       =  7,
                                    
   VSEP_RXD_SDOA_FAULT_GRP_9        =  9,
   VSEP_RXD_SDOA_FAULT_GRP_A        = 10,
   VSEP_RXD_SDOA_FAULT_GRP_9A       =  9,
                                    
   VSEP_RXD_SDOA_FAULT_GRP_B        = 11,
   VSEP_RXD_SDOA_FAULT_GRP_C        = 12,
   VSEP_RXD_SDOA_FAULT_GRP_BC       = 11,
                                    
   VSEP_RXD_SDOA_FAULT_GRP_D        = 13,
   VSEP_RXD_SDOA_GRADCOUNT          = 14,
   VSEP_RXD_SDOA_EST_CYL_CNT        = 15,
   VSEP_RXD_SDOA_NOT_USED           = 15
}VSEP_RXD_SDOA_T;

typedef enum
{
   VSEP_RXD_COMMAND_MSG_POSITION_CRTIMEOUT                 = 8,  //      0  CRTIMEOUT
   VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_56              = 9,  //      1  FLT_WORDS_56
   VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_78              =10,  //      2  FLT_WORDS_78
   VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_9A              =11,  //      3  FLT_WORDS_9A
   VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_BC              =12,  //      4  FLT_WORDS_BC
   VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORD_D                =13,  //      5  FLT_WORD_D 
   VSEP_RXD_COMMAND_MSG_POSITION_TESTBITH                  =14,  //      6  TESTBITH
   VSEP_RXD_COMMAND_MSG_POSITION_TESTBITL                  =15,  //      7  TESTBITL
   VSEP_RXD_COMMAND_MSG_POSITION_RESPCOUNT                 = 0,  // [12: 8] RESPCOUNT
   VSEP_RXD_COMMAND_MSG_POSITION_CRDISARM_STAT             = 5,  //     13  CRDISARM_STAT
   VSEP_RXD_COMMAND_MSG_POSITION_FSE_EN_STAT               = 6,  //     14  FSE_EN_STAT     
   VSEP_RXD_COMMAND_MSG_POSITION_GEN_STAT                  = 7   //     15  GEN_STAT
}VSEP_RXD_Command_Msg_Position_T;                           
                                                                     
typedef enum                                                         
{                                                                    
   VSEP_RXD_COMMAND_MSG_WIDTH_CRTIMEOUT                    = 1,  //      0  CRTIMEOUT
   VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_56                 = 1,  //      1  FLT_WORDS_56
   VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_78                 = 1,  //      2  FLT_WORDS_78
   VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_9A                 = 1,  //      3  FLT_WORDS_9A
   VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_BC                 = 1,  //      4  FLT_WORDS_BC
   VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORD_D                   = 1,  //      5  FLT_WORD_D 
   VSEP_RXD_COMMAND_MSG_WIDTH_TESTBITH                     = 1,  //      6  TESTBITH
   VSEP_RXD_COMMAND_MSG_WIDTH_TESTBITL                     = 1,  //      7  TESTBITL
   VSEP_RXD_COMMAND_MSG_WIDTH_RESPCOUNT                    = 5,  // [12: 8] RESPCOUNT
   VSEP_RXD_COMMAND_MSG_WIDTH_CRDISARM_STAT                = 1,  //     13  CRDISARM_STAT
   VSEP_RXD_COMMAND_MSG_WIDTH_FSE_EN_STAT                  = 1,  //     14  FSE_EN_STAT     
   VSEP_RXD_COMMAND_MSG_WIDTH_GEN_STAT		                 = 1   //     15  GEN_STAT
}VSEP_RXD_Command_Msg_Width_T;

#define VSEP_Msg_CMD_Set_Challenge_Response_Timeout( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_CRTIMEOUT,VSEP_RXD_COMMAND_MSG_WIDTH_CRTIMEOUT ) )

#define VSEP_Msg_CMD_Get_Challenge_Response_Timeout( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_CRTIMEOUT,VSEP_RXD_COMMAND_MSG_WIDTH_CRTIMEOUT ) )

#define VSEP_Msg_CMD_Set_Fault_Word_56( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_56, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_56 ) )

#define VSEP_Msg_CMD_Get_Fault_Word_56( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_56, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_56 ) )

#define VSEP_Msg_CMD_Set_Fault_Word_78( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_78, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_78 ) )

#define VSEP_Msg_CMD_Get_Fault_Word_78( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_78, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_78 ) )

#define VSEP_Msg_CMD_Set_Fault_Word_9A( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_9A, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_9A ) )

#define VSEP_Msg_CMD_Get_Fault_Word_9A( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_9A, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_9A ) )

#define VSEP_Msg_CMD_Set_Fault_Word_BC( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_BC, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_BC ) )

#define VSEP_Msg_CMD_Get_Fault_Word_BC( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORDS_BC, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORDS_BC ) )

#define VSEP_Msg_CMD_Set_Fault_Word_D( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORD_D, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORD_D ) )

#define VSEP_Msg_CMD_Get_Fault_Word_D( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_FLT_WORD_D, VSEP_RXD_COMMAND_MSG_WIDTH_FLT_WORD_D ) )

#define VSEP_Msg_CMD_Set_Test_Bit_High( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_TESTBITH, VSEP_RXD_COMMAND_MSG_WIDTH_TESTBITH ) )

#define VSEP_Msg_CMD_Get_Test_Bit_High( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_TESTBITH, VSEP_RXD_COMMAND_MSG_WIDTH_TESTBITH ) )

#define VSEP_Msg_CMD_Set_Test_Bit_Low( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_TESTBITL, VSEP_RXD_COMMAND_MSG_WIDTH_TESTBITL ) )

#define VSEP_Msg_CMD_Get_Test_Bit_Low( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_TESTBITL, VSEP_RXD_COMMAND_MSG_WIDTH_TESTBITL ) )

#define VSEP_Msg_CMD_Set_Challenge_Response_Count( msg, count ) \
   (uint16_t)(Insert_Bits( msg, count, VSEP_RXD_COMMAND_MSG_POSITION_RESPCOUNT, VSEP_RXD_COMMAND_MSG_WIDTH_RESPCOUNT ) )

#define VSEP_Msg_CMD_Get_Challenge_Response_Count( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_RESPCOUNT, VSEP_RXD_COMMAND_MSG_WIDTH_RESPCOUNT ) )

#define VSEP_Msg_CMD_Set_Challenge_Response_Disarm( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_CRDISARM_STAT, VSEP_RXD_COMMAND_MSG_WIDTH_CRDISARM_STAT ) )

#define VSEP_Msg_CMD_Get_Challenge_Response_Disarm( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_CRDISARM_STAT, VSEP_RXD_COMMAND_MSG_WIDTH_CRDISARM_STAT ) )

#define VSEP_Msg_CMD_Set_FSE_Enable_Status( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_FSE_EN_STAT, VSEP_RXD_COMMAND_MSG_WIDTH_FSE_EN_STAT ) )

#define VSEP_Msg_CMD_Get_FSE_Enable_Status( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_FSE_EN_STAT, VSEP_RXD_COMMAND_MSG_WIDTH_FSE_EN_STAT ) )

#define VSEP_Msg_CMD_Set_Global_Enable_Status( msg, state ) \
   (uint16_t)(Insert_Bits( msg, state, VSEP_RXD_COMMAND_MSG_POSITION_GEN_STAT, VSEP_RXD_COMMAND_MSG_WIDTH_GEN_STAT ) )

#define VSEP_Msg_CMD_Get_Global_Enable_Status( msg ) \
   (uint8_t)(Extract_Bits( msg, VSEP_RXD_COMMAND_MSG_POSITION_GEN_STAT, VSEP_RXD_COMMAND_MSG_WIDTH_GEN_STAT ) )

typedef enum
{
   VSEP_RXD_INPUTS_MSG_POSITION_M1_CLOSED                  = 0,  //      8  M1_CLOSED
   VSEP_RXD_INPUTS_MSG_POSITION_M2_CLOSED                  = 1,  //      9  M2_CLOSED  
   VSEP_RXD_INPUTS_MSG_POSITION_M3_CLOSED                  = 2,  //     10  M3_CLOSED
   VSEP_RXD_INPUTS_MSG_POSITION_SLEWCAN                    = 3,  // [12:11] SLEWCAN
   VSEP_RXD_INPUTS_MSG_POSITION_SOHRSTEN_STAT              = 5,  //      
   VSEP_RXD_INPUTS_MSG_POSITION_M2_OHILOB                  = 6,  //     14  M2_OHILOB
   VSEP_RXD_INPUTS_MSG_POSITION_M2_OEN                     = 7,  //     15  M2_OEN
   VSEP_RXD_INPUTS_MSG_POSITION_EST1C                      = 8,  // [ 2: 0] EST1C
   VSEP_RXD_INPUTS_MSG_POSITION_EST2C                      =11,  // [ 5: 3] EST2C
   VSEP_RXD_INPUTS_MSG_POSITION_M1_OHILOB                  =14,  //      6  M1_OHILOB
   VSEP_RXD_INPUTS_MSG_POSITION_M1_OEN                     =15,  //      7  M1_OEN

                                                                 
   VSEP_RXD_INPUTS_MSG_POSITION_CHALLENGE                  = 8,  // [ 5: 0] CHALLENGE
   VSEP_RXD_INPUTS_MSG_POSITION_M3_OHILOB                  =14,  //      6  M3_OHILOB    
   VSEP_RXD_INPUTS_MSG_POSITION_M3_OEN                     =15   //      7  M3_OEN  

}VSEP_RXD_Inputs_Msg_Position_T;

typedef enum
{
   VSEP_RXD_INPUTS_MSG_WIDTH_EST1C                         = 3,  // [ 2: 0] EST1C
   VSEP_RXD_INPUTS_MSG_WIDTH_EST2C                         = 3,  // [ 5: 3] EST2C
   VSEP_RXD_INPUTS_MSG_WIDTH_M1_OHILOB                     = 1,  //      6  M1_OHILOB
   VSEP_RXD_INPUTS_MSG_WIDTH_M1_OEN                        = 1,  //      7  M1_OEN
   VSEP_RXD_INPUTS_MSG_WIDTH_M1_CLOSED                     = 1,  //      8  M1_CLOSED
   VSEP_RXD_INPUTS_MSG_WIDTH_M2_CLOSED                     = 1,  //      9  M2_CLOSED 
   VSEP_RXD_INPUTS_MSG_WIDTH_M3_CLOSED                     = 1,  //     10  M3_CLOSED
   VSEP_RXD_INPUTS_MSG_WIDTH_SLEWCAN                       = 2,  // [12:11] SLEWCAN
   VSEP_RXD_INPUTS_MSG_WIDTH_SOHRSTEN_STAT                 = 1,
   VSEP_RXD_INPUTS_MSG_WIDTH_M2_OHILOB                     = 1,  //     14  M2_OHILOB
   VSEP_RXD_INPUTS_MSG_WIDTH_M2_OEN                        = 1,  //     15  M2_OEN
                                                                     
   VSEP_RXD_INPUTS_MSG_WIDTH_CHALLENGE                     = 6,  // [ 5: 0] CHALLENGE
   VSEP_RXD_INPUTS_MSG_WIDTH_M3_OHILOB                     = 1,  //      6  M3_OHILOB  
   VSEP_RXD_INPUTS_MSG_WIDTH_M3_OEN                        = 1   //      7  M3_OEN  
}VSEP_RXD_Inputs_Msg_Width_T;


//=============================================================================
// VSEP_Msg_Set_Challenge
//
// @func Set the SOH challange value for the retrieved message
//
// @parm uint8_t | msg | The rxd message element to set the challenge value
//
// @parm uint8_t | challenge | A value from 0x00 - 0x3F
//
// @rdesc uint8_t value representing the VSEP challenge word containing the 
//    challenge value.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_Challenge( msg, challenge ) \
   (uint16_t)( Insert_Bits( msg, challenge, VSEP_RXD_INPUTS_MSG_POSITION_CHALLENGE, VSEP_RXD_INPUTS_MSG_WIDTH_CHALLENGE ) )


//=============================================================================
// VSEP_Msg_Get_Challenge
//
// @func Get the SOH challange value for the retrieved message
//
// @parm uint8_t | msg | The rxd message element to get the challenge value
//
// @rdesc uint8_t value representing the VSEP challenge value
//
// @end
//=============================================================================
#define VSEP_Msg_Get_Challenge( msg ) \
   (uint8_t)( Extract_Bits( msg, VSEP_RXD_INPUTS_MSG_POSITION_CHALLENGE, VSEP_RXD_INPUTS_MSG_WIDTH_CHALLENGE ) )

//=============================================================================
// VSEP_Msg_Set_SOHRSTEN_STAT
//
// @func Set the SOHRSTEN_STAT bit to indicate whether the SOH is in 
//         Hardware_Reset_Mode (= 1)  or not
//
// @parm uint8_t | msg | The rxd message element to set the SOHRSTEN_STAT value
//
// @parm uint8_t | sohrsten_stat | A value of 0 or 1 indicating the desired status as 
//                                 enabled ( = 1) or not ( = 0)
//
// @rdesc uint8_t value representing the SOH_STATUS word containing the 
//    SOHRSTEN_STAT value.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_SOHRSTEN_STAT( msg, sohrsten_stat ) \
   (uint16_t)( Insert_Bits( msg, sohrsten_stat, VSEP_RXD_INPUTS_MSG_POSITION_SOHRSTEN_STAT, VSEP_RXD_INPUTS_MSG_WIDTH_SOHRSTEN_STAT ) )

//=============================================================================
// VSEP_Msg_Get_SOHRSTEN_STAT
//
// @func Get the value of the SOHRSTEN_STAT bit which indicates whether the SOH is in 
//         Hardware_Reset_Mode (= 1)  or not
//
// @parm uint8_t | msg | The rxd message element to get the challenge value
//
// @rdesc uint8_t value representing the VSEP challenge value
//
// @end
//=============================================================================
#define VSEP_Msg_Get_SOHRSTEN_STAT( msg ) \
   (uint8_t)( Extract_Bits( msg, VSEP_RXD_INPUTS_MSG_POSITION_SOHRSTEN_STAT, VSEP_RXD_INPUTS_MSG_WIDTH_SOHRSTEN_STAT ) )


// PCH[x]_FLT
//
// 00	No Faults Detected
// 01	Open Fault
// 10	Short to Ground Fault
// 11	Short to Battery Fault

//Fault Group FLT_WORDS_56
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_56_MSG_POSITION_PCH1_FLT          = 0,  //[ 1: 0] PCH1_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_POSITION_PCH2_FLT          = 2,  //[ 3: 2] PCH2_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_POSITION_PCH3_FLT          = 4,  //[ 5: 4] PCH3_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_POSITION_PCH4_FLT          = 6,  //[ 7: 6] PCH4_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_POSITION_PCH5_FLT          = 8,  //[ 9: 8] PCH5_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_POSITION_PCH6_FLT          =10,  //[11:10] PCH6_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_POSITION_PCH7_FLT          =12,  //[13:12] PCH7_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_POSITION_PCH8_FLT          =14   //[15:14] PCH8_FLT
}VSEP_RXD_Faults_Group_56_Msg_Position_T;

//Fault Group FLT_WORDS_78
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_78_MSG_POSITION_PCH9_FLT          = 0,  //[ 1: 0] PCH9_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_POSITION_PCH10_FLT         = 2,  //[ 3: 2] PCH10_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_POSITION_PCH11_FLT         = 4,  //[ 5: 4] PCH11_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_POSITION_PCH12_FLT         = 6,  //[ 7: 6] PCH12_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_POSITION_PCH13_FLT         = 8,  //[ 9: 8] PCH13_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_POSITION_PCH14_FLT         =10,  //[11:10] PCH14_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_POSITION_PCH15_FLT         =12,  //[13:12] PCH15_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_POSITION_PCH16_FLT         =14   //[15:14] PCH16_FLT
}VSEP_RXD_Faults_Group_78_Msg_Position_T;
                                                            
//Fault Group FLT_WORDS_9A
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_9A_MSG_POSITION_PCH17_FLT         = 0,  //[ 1: 0] PCH17_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_POSITION_PCH18_FLT         = 2,  //[ 3: 2] PCH18_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_POSITION_PCH19_FLT         = 4,  //[ 5: 4] PCH19_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_POSITION_PCH20_FLT         = 6,  //[ 7: 6] PCH20_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_POSITION_PCH21_FLT         = 8,  //[ 9: 8] PCH21_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_POSITION_PCH22_FLT         =10,  //[11:10] PCH22_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_POSITION_PCH23_FLT         =12,  //[13:12] PCH23_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_POSITION_PCH24_FLT         =14   //[15:14] PCH24_FLT
}VSEP_RXD_Faults_Group_9A_Msg_Position_T;
                                                            
//Fault Group FLT_WORDS_BC
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_BC_MSG_POSITION_PCH25_FLT         = 0,  //[ 1: 0] PCH25_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_POSITION_PCH26_FLT         = 2,  //[ 3: 2] PCH26_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_POSITION_PCH27_FLT         = 4,  //[ 5: 4] PCH27_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_POSITION_PCH28_FLT         = 6,  //[ 7: 6] PCH28_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_POSITION_PCH29_FLT         = 8,  //[ 9: 8] PCH29_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_POSITION_PCH30_FLT         =10,  //[11:10] PCH30_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_POSITION_OPEN_2ND_D        =12,  //[14:12] OPEN_2ND_D
   VSEP_RXD_FAULTS_GROUP_BC_MSG_POSITION_OPEN_2ND_FLT      =15   //    15  OPEN_2ND_FLT
}VSEP_RXD_Faults_Group_BC_Msg_Position_T;
                                                            

//Fault Group FLT_WORD_D
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_D_MSG_POSITION_VR1DEC_FLT         = 0,  //     0  VR1DEC_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_POSITION_VR2DEC_FLT         = 1,  //     1  VR2DEC_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_POSITION_ISO_FLT            = 2,  //     2  ISO_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_POSITION_CANTHERM_FLT       = 3,  //     3  CANTHERM_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_POSITION_CANSC_FLT          = 4,  //     4  CANSC_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_POSITION_CANTO_FLT          = 5,  //     5  CANTO_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_POSITION_CLKFAIL_FLT        = 6,  //     6  CLKFAIL_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_POSITION_IREF_FLT           = 7   //     7  IREF_FLT
}VSEP_RXD_Faults_Group_D_Msg_Position_T;

//Fault Group FLT_WORDS_56
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_56_MSG_WIDTH_PCH1_FLT             = 2,  //[ 1: 0] PCH1_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_WIDTH_PCH2_FLT             = 2,  //[ 3: 2] PCH2_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_WIDTH_PCH3_FLT             = 2,  //[ 5: 4] PCH3_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_WIDTH_PCH4_FLT             = 2,  //[ 7: 6] PCH4_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_WIDTH_PCH5_FLT             = 2,  //[ 9: 8] PCH5_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_WIDTH_PCH6_FLT             = 2,  //[11:10] PCH6_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_WIDTH_PCH7_FLT             = 2,  //[13:12] PCH7_FLT
   VSEP_RXD_FAULTS_GROUP_56_MSG_WIDTH_PCH8_FLT             = 2   //[15:14] PCH8_FLT
}VSEP_RXD_Faults_Group_56_Msg_Width_T;
                                                            
//Fault Group FLT_WORDS_78
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_78_MSG_WIDTH_PCH9_FLT             = 2,  //[ 1: 0] PCH9_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_WIDTH_PCH10_FLT            = 2,  //[ 3: 2] PCH10_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_WIDTH_PCH11_FLT            = 2,  //[ 5: 4] PCH11_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_WIDTH_PCH12_FLT            = 2,  //[ 7: 6] PCH12_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_WIDTH_PCH13_FLT            = 2,  //[ 9: 8] PCH13_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_WIDTH_PCH14_FLT            = 2,  //[11:10] PCH14_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_WIDTH_PCH15_FLT            = 2,  //[13:12] PCH15_FLT
   VSEP_RXD_FAULTS_GROUP_78_MSG_WIDTH_PCH16_FLT            = 2   //[15:14] PCH16_FLT
}VSEP_RXD_Faults_Group_78_Msg_Width_T;
                                                            
//Fault Group FLT_WORDS_9A
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_9A_MSG_WIDTH_PCH17_FLT            = 2,  //[ 1: 0] PCH17_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_WIDTH_PCH18_FLT            = 2,  //[ 3: 2] PCH18_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_WIDTH_PCH19_FLT            = 2,  //[ 5: 4] PCH19_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_WIDTH_PCH20_FLT            = 2,  //[ 7: 6] PCH20_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_WIDTH_PCH21_FLT            = 2,  //[ 9: 8] PCH21_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_WIDTH_PCH22_FLT            = 2,  //[11:10] PCH22_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_WIDTH_PCH23_FLT            = 2,  //[13:12] PCH23_FLT
   VSEP_RXD_FAULTS_GROUP_9A_MSG_WIDTH_PCH24_FLT            = 2   //[15:14] PCH24_FLT
}VSEP_RXD_Faults_Group_9A_Msg_Width_T;
                                                            
//Fault Group FLT_WORDS_BC
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_BC_MSG_WIDTH_PCH25_FLT            = 2,  //[ 1: 0] PCH25_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_WIDTH_PCH26_FLT            = 2,  //[ 3: 2] PCH26_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_WIDTH_PCH27_FLT            = 2,  //[ 5: 4] PCH27_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_WIDTH_PCH28_FLT            = 2,  //[ 7: 6] PCH28_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_WIDTH_PCH29_FLT            = 2,  //[ 9: 8] PCH29_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_WIDTH_PCH30_FLT            = 2,  //[11:10] PCH30_FLT
   VSEP_RXD_FAULTS_GROUP_BC_MSG_WIDTH_OPEN_2ND_D           = 3,  //[14:12] OPEN_2ND_D
   VSEP_RXD_FAULTS_GROUP_BC_MSG_WIDTH_OPEN_2ND_FLT         = 1   //    15  OPEN_2ND_FLT
}VSEP_RXD_Faults_Group_BC_Msg_Width_T;
                                                            
//Fault Group FLT_WORDS_D
typedef enum
{
   VSEP_RXD_FAULTS_GROUP_D_MSG_WIDTH_VR1DEC_FLT            = 1,  //     0  VR1DEC_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_WIDTH_VR2DEC_FLT            = 1,  //     1  VR2DEC_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_WIDTH_ISO_FLT               = 1,  //     2  ISO_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_WIDTH_CANTHERM_FLT          = 1,  //     3  CANTHERM_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_WIDTH_CANSC_FLT             = 1,  //     4  CANSC_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_WIDTH_CANTO_FLT             = 1,  //     5  CANTO_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_WIDTH_CLKFAIL_FLT           = 1,  //     6  CLKFAIL_FLT
   VSEP_RXD_FAULTS_GROUP_D_MSG_WIDTH_IREF_FLT              = 1   //     7  IREF_FLT
}VSEP_RXD_Faults_Group_D_Msg_Width_T;

typedef enum
{
   VSEP_RXD_STATUS_MSG_POSITION_GRADCOUNT                  = 8,  //[15: 8] GRADCOUNT

   VSEP_RXD_STATUS_MSG_POSITION_CYLCNT_DEC                 = 0,  //[ 2: 0] CYLCNT_DEC
   VSEP_RXD_STATUS_MSG_POSITION_DEC_DISCB                  = 3,  //     3  DEC_DISCB
   VSEP_RXD_STATUS_MSG_POSITION_IGBT_CFG                   = 4,  //     4  IGBT_CFG
   VSEP_RXD_STATUS_MSG_POSITION_VERSN                      = 5   //[ 7: 5] VERSN
}VSEP_RXD_Status_Msg_Position_T;                           
                                                                     
typedef enum                                                         
{                                                                    
   VSEP_RXD_STATUS_MSG_WIDTH_GRADCOUNT                     = 8,  //[15: 8] GRADCOUNT
                                                                 
   VSEP_RXD_STATUS_MSG_WIDTH_CYLCNT_DEC                    = 3,  //[ 2: 0] CYLCNT_DEC
   VSEP_RXD_STATUS_MSG_WIDTH_DEC_DISCB                     = 1,  //     3  DEC_DISCB
   VSEP_RXD_STATUS_MSG_WIDTH_IGBT_CFG                      = 1,  //     4  IGBT_CFG
   VSEP_RXD_STATUS_MSG_WIDTH_VERSN                         = 3   //[ 7: 5] VERSN
}VSEP_RXD_Status_Msg_Width_T;                              

//=============================================================================
// VSEP_Msg_Get_GRADCOUNT
//
// @func Get the value of the gradient timer
//
// @parm uint8_t | msg | The rxd message element to get the gradient timer value
//
// @rdesc uint8_t value representing the VSEP gradient timer
//
// @end
//=============================================================================
#define VSEP_Msg_Get_GRADCOUNT( msg ) \
   (uint8_t)( Extract_Bits( msg, VSEP_RXD_STATUS_MSG_POSITION_GRADCOUNT, VSEP_RXD_STATUS_MSG_WIDTH_GRADCOUNT ) )

#endif // DD_VSEP_RXD_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

#ifndef DD_VSEP_TXD_H
#define DD_VSEP_TXD_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_txd.h~3:incl:mt20u2#2 %
//
// created_by:       fz3pdz
//
// date_created:     Wed Mar  9 10:33:13 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 11:33:14 2007 %
//
// %version:         3 %
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

#include "hal.h"

typedef enum
{
   VSEP_TXD_SDIA_RESPONSE           =  0,
   VSEP_TXD_SDIA_PCH                =  2,
   VSEP_TXD_SDIA_PWM_ONT_1          =  4,
   VSEP_TXD_SDIA_PWM_PER_1          =  6,
   VSEP_TXD_SDIA_PWM_ONT_2          =  8,
   VSEP_TXD_SDIA_PWM_PER_2          = 10,
   VSEP_TXD_SDIA_PWM_ONT_3          = 12,
   VSEP_TXD_SDIA_PWM_PER_3          = 14,
   VSEP_TXD_SDIA_PWM_ONT_4          = 16,
   VSEP_TXD_SDIA_PWM_PER_4          = 18,
   VSEP_TXD_SDIA_PWM_ONT_5          = 20,
   VSEP_TXD_SDIA_PWM_PER_5          = 22,
   VSEP_TXD_SDIA_PWM_ONT_6          = 24,
   VSEP_TXD_SDIA_PWM_PER_6          = 26,
   VSEP_TXD_SDIA_PWM_ONT_7          = 28,
   VSEP_TXD_SDIA_PWM_PER_7          = 30,
   VSEP_TXD_SDIA_PWM_ONT_8          = 32,
   VSEP_TXD_SDIA_PWM_PER_8          = 34,
   VSEP_TXD_SDIA_VR1_CTRL           = 36,
   VSEP_TXD_SDIA_VR2_CTRL           = 38,
   VSEP_TXD_SDIA_DEPS_CTRL          = 40,
   VSEP_TXD_SDIA_SLEW_CTRL          = 42,
   VSEP_TXD_SDIA_FAULT_CTRL         = 44,
   VSEP_TXD_SDIA_FAULT_FILTER_CTRL  = 48,
   VSEP_TXD_SDIA_LED_MODE_CTRL      = 50,
   VSEP_TXD_SDIA_GRAD_CTRL          = 52,
   VSEP_TXD_SDIA_EST_CTRL           = 54,
   VSEP_TXD_SDIA_SETUP              = 56,
   VSEP_TXD_SDIA_NOT_USED           = 63
   
}VSEP_TXD_SDIA_T;

///////////////////////////////////////////////////////////////////////////////
// ID - CMD
// Base Offset: 00 H
// Reset Value: 0000 0000 H
//
// Field       Bits    Type  Description
// =========   ======= ====  =================================================
// FLTCLR	       15         Global IO fault
//                            0	Global Fault Clear Bit.  No faults cleared.
//	                           1	Global Fault Clear Bit.  Does not affect 
//                                 
// CRTOCLR	       14         Challenge & Response Timeout fault.
//                            0	Challenge & Response Timeout fault bit.  C&R 
//                               Timeout faults not cleared.
//	                           1	Challenge & Response Timeout fault bit.  C&R 
//                               Timout fault only cleared.
//
// SDOA[3:0]   [11: 8]       This is the four (4) bit SPI Data OUT Address Register
//
// SDIA[5:0]	[ 5: 0]       This is the six (6) bit SPI Data IN Address Register
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   VSEP_TXD_CMD_CONFIGURATION_POSITION_FLTCLR                  = 15,  //      7   FLTCLR
   VSEP_TXD_CMD_CONFIGURATION_POSITION_CRTOCLR                 = 14,  //      6   CRT0CLR
   VSEP_TXD_CMD_CONFIGURATION_POSITION_SDOA                    = 8,   // [11: 8]  SDOA
   VSEP_TXD_CMD_CONFIGURATION_POSITION_SDIA                    = 0    // [ 5: 0]  SDIA
}VSEP_TXD_CMD_Configuration_Position_T;                    
                                                               
typedef enum
{
   VSEP_TXD_CMD_CONFIGURATION_BYTE1_POSITION_FLTCLR                  = 7,  //      7   FLTCLR
   VSEP_TXD_CMD_CONFIGURATION_BYTE1_POSITION_CRTOCLR                 = 6,  //      6   CRT0CLR
   VSEP_TXD_CMD_CONFIGURATION_BYTE1_POSITION_SDOA                    = 0   // [3: 0]  SDOA
}VSEP_TXD_CMD_Configuration_BYTE1_Position_T; 

typedef enum
{
   VSEP_TXD_CMD_CONFIGURATION_BYTE0_POSITION_SDIA                    = 0   // [5:0]  SDOA
}VSEP_TXD_CMD_Configuration_BYTE0_Position_T;	

typedef enum                                                   
{                                                              
   VSEP_TXD_CMD_CONFIGURATION_WIDTH_FLTCLR                     = 1,  //      7   FLTCLR FOR BYTE BYTE1 7
   VSEP_TXD_CMD_CONFIGURATION_WIDTH_CRTOCLR                    = 1,  //      6   CRT0CLR FOR BYTE BYTE1 6
   VSEP_TXD_CMD_CONFIGURATION_WIDTH_SDOA                       = 4,  // [11: 8]  SDOA FOR BYTE BYTE1 [3:0]  
   VSEP_TXD_CMD_CONFIGURATION_WIDTH_SDIA                       = 6   // [ 5: 0]  SDIA  FOR BYTE BYTE0[ 5: 0] 
}VSEP_TXD_CMD_Configuration_Width_T;                       

//=============================================================================
// VSEP_Msg_Set_FLTCLR
//
// @func Set clear fault flag for the next message transfer
//
// @parm uint16_t | msg | The txd message element to set the fault clear flag
//
// @parm uint8_t | fltclr | 1 to set fault clear flag otherwise 0
//
// @rdesc uint16_t value representing the VSEP command word containing the new
//    clear fault flag.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_FLTCLR_BYTE_FORMAT( msg, fltclr ) \
   (uint16_t)( Insert_Bits( msg, fltclr, VSEP_TXD_CMD_CONFIGURATION_BYTE1_POSITION_FLTCLR, VSEP_TXD_CMD_CONFIGURATION_WIDTH_FLTCLR ) )

//=============================================================================
// VSEP_Msg_Set_FLTCLR
//
// @func Set clear fault flag for the next message transfer
//
// @parm uint16_t | msg | The txd message element to set the fault clear flag
//
// @parm uint8_t | fltclr | 1 to set fault clear flag otherwise 0
//
// @rdesc uint16_t value representing the VSEP command word containing the new
//    clear fault flag.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_FLTCLR( msg, fltclr ) \
   (uint16_t)( Insert_Bits( msg, fltclr, VSEP_TXD_CMD_CONFIGURATION_POSITION_FLTCLR, VSEP_TXD_CMD_CONFIGURATION_WIDTH_FLTCLR ) )

//=============================================================================
// VSEP_Msg_Get_FLTCLR
//
// @func Get clear fault flag for the next message transfer
//
// @parm uint16_t | msg | The txd message element to get the fault clear flag
//
// @rdesc uint8_t value representing the clear fault flag.
//
// @end
//=============================================================================
#define VSEP_Msg_Get_FLTCLR( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_CMD_CONFIGURATION_POSITION_FLTCLR, VSEP_TXD_CMD_CONFIGURATION_WIDTH_FLTCLR ) )

//=============================================================================
// VSEP_Msg_Set_CRTOCLR
//
// @func Set set clear Challenge & Response Timeout fault bit for the next message
//    transfer
//
// @parm uint16_t | msg | The txd message element to set the clear Challenge & 
//    Response Timeout fault flag
//
// @parm uint8_t | crtoclr | 1 to set Challenge & Response Timeout fault flag 
//    otherwise 0
//
// @rdesc uint16_t value representing the VSEP command word containing the new
//    Challenge & Response Timeout fault bit.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_CRTOCLR_BYTE_FORMAT( msg, crtoclr )\
   (uint16_t)( Insert_Bits( msg, crtoclr, VSEP_TXD_CMD_CONFIGURATION_BYTE1_POSITION_CRTOCLR, VSEP_TXD_CMD_CONFIGURATION_WIDTH_CRTOCLR ) )

//=============================================================================
// VSEP_Msg_Set_CRTOCLR
//
// @func Set set clear Challenge & Response Timeout fault bit for the next message
//    transfer
//
// @parm uint16_t | msg | The txd message element to set the clear Challenge & 
//    Response Timeout fault flag
//
// @parm uint8_t | crtoclr | 1 to set Challenge & Response Timeout fault flag 
//    otherwise 0
//
// @rdesc uint16_t value representing the VSEP command word containing the new
//    Challenge & Response Timeout fault bit.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_CRTOCLR( msg, crtoclr )\
   (uint16_t)( Insert_Bits( msg, crtoclr, VSEP_TXD_CMD_CONFIGURATION_POSITION_CRTOCLR, VSEP_TXD_CMD_CONFIGURATION_WIDTH_CRTOCLR ) )

//=============================================================================
// VSEP_Msg_Get_CRTOCLR
//
// @func Get the clear Challenge & Response Timeout fault bit for the next message
//    transfer
//
// @parm uint8_t | msg | The txd message element to get the Challenge & Response 
//    Timeout fault flag
//
// @rdesc uint8_t value representing the Challenge & Response Timeout fault flag.
//
// @end
//=============================================================================
#define VSEP_Msg_Get_CRTOCLR( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_CMD_CONFIGURATION_POSITION_CRTOCLR, VSEP_TXD_CMD_CONFIGURATION_WIDTH_CRTOCLR ) )

//=============================================================================
// VSEP_Msg_Set_SDOA
//
// @func Set message serial data output address from the VSEP.
//
// @parm uint16_t | msg | The txd message element to set the SDOA address
//
// @parm VSEP_RXD_SDOA_T | sdoa | The serial data output address
//
// @rdesc uint16_t value representing the VSEP command word containing the new
//    serial data output address.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_SDOA_BYTE_FORMAT( msg, sdoa )\
   (uint16_t)( Insert_Bits( msg, sdoa, VSEP_TXD_CMD_CONFIGURATION_BYTE1_POSITION_SDOA, VSEP_TXD_CMD_CONFIGURATION_WIDTH_SDOA ) )

//=============================================================================
// VSEP_Msg_Set_SDOA
//
// @func Set message serial data output address from the VSEP.
//
// @parm uint16_t | msg | The txd message element to set the SDOA address
//
// @parm VSEP_RXD_SDOA_T | sdoa | The serial data output address
//
// @rdesc uint16_t value representing the VSEP command word containing the new
//    serial data output address.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_SDOA( msg, sdoa )\
   (uint16_t)( Insert_Bits( msg, sdoa, VSEP_TXD_CMD_CONFIGURATION_POSITION_SDOA, VSEP_TXD_CMD_CONFIGURATION_WIDTH_SDOA ) )

//=============================================================================
// VSEP_Msg_Get_SDOA
//
// @func Get message serial data output address from the VSEP.
//
// @parm uint16_t | msg | The txd message element to get the SDOA address
//
// @rdesc <t VSEP_RXD_SDOA_T> value representing the SDOA address
//
// @end
//=============================================================================
#define VSEP_Msg_Get_SDOA( msg )\
   (VSEP_RXD_SDOA_T)( Extract_Bits( msg, VSEP_TXD_CMD_CONFIGURATION_POSITION_SDOA, VSEP_TXD_CMD_CONFIGURATION_WIDTH_SDOA ) )

//=============================================================================
// VSEP_Msg_Set_SDIA
//
// @func Set message serial data input address from the VSEP.
//
// @parm uint16_t | msg | The txd message element to set the SDIA address
//
// @parm VSEP_RXD_SDIA_T | sdia | The serial data input address
//
// @rdesc uint16_t value representing the VSEP command word containing the new
//    serial data input address.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_SDIA_BYTE_FORMAT( msg, sdia )\
   (uint16_t)( Insert_Bits( msg, sdia, VSEP_TXD_CMD_CONFIGURATION_BYTE0_POSITION_SDIA, VSEP_TXD_CMD_CONFIGURATION_WIDTH_SDIA ) )

//=============================================================================
// VSEP_Msg_Set_SDIA
//
// @func Set message serial data input address from the VSEP.
//
// @parm uint16_t | msg | The txd message element to set the SDIA address
//
// @parm VSEP_RXD_SDIA_T | sdia | The serial data input address
//
// @rdesc uint16_t value representing the VSEP command word containing the new
//    serial data input address.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_SDIA( msg, sdia )\
   (uint16_t)( Insert_Bits( msg, sdia, VSEP_TXD_CMD_CONFIGURATION_POSITION_SDIA, VSEP_TXD_CMD_CONFIGURATION_WIDTH_SDIA ) )

//=============================================================================
// VSEP_Msg_Get_SDIA
//
// @func Get message serial data input address from the VSEP.
//
// @parm uint8_t | msg | The txd message element to get the SDIA address
//
// @rdesc <t VSEP_RXD_SDIA_T> value representing the SDIA.
//
// @end
//=============================================================================
#define VSEP_Msg_Get_SDIA( msg )\
   (VSEP_RXD_SDIA_T)( Extract_Bits( msg, VSEP_TXD_CMD_CONFIGURATION_POSITION_SDIA, VSEP_TXD_CMD_CONFIGURATION_WIDTH_SDIA ) )

///////////////////////////////////////////////////////////////////////////////
// ID - RESPONSE
// Base Offset: 00 H
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
// RESPONSE  [13: 8]       This is the 6 bit register value that contains the 
//                         controllers response to the VSEP's Challenge value 
//                         for the ETC SOH C & R logic
// FSE_DISABLE   14
//                         0	The State of the FSE_Enable signal is not 
//                            controlled by this input bit.
//                         1	The FSE_Enable signal transitions to a valid low 
//                            value and fuel, spark, & ETC are disabled.
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   VSEP_TXD_RESPONSE_CONFIGURATION_POSITION_RESPONSE           = 8,  // [13: 8] RESPONSE
   VSEP_TXD_RESPONSE_CONFIGURATION_POSITION_FSE_DISABLE        =14   //     14  FSE_DISABLE
}VSEP_TXD_Response_Configuration_Position_T;                   
                                                               
typedef enum                                                   
{                                                              
   VSEP_TXD_RESPONSE_CONFIGURATION_WIDTH_RESPONSE              = 6,  // [13: 8] RESPONSE
   VSEP_TXD_RESPONSE_CONFIGURATION_WIDTH_FSE_DISABLE           = 1   //     14  FSE_DISABLE
}VSEP_TXD_RESPONSE_Configuration_Width_T;

//=============================================================================
// VSEP_Msg_Set_RESPONSE
//
// @func Set the SOH response value in the txd message element
//
// @parm uint16_t | msg | The txd message element to SOH response value
//
// @parm uint8_t | response | The SOH response value
//
// @rdesc uint16_t txd message element representing the VSEP SOH response 
//    containing the new SOH response value.
//
// @end
//=============================================================================
#define VSEP_Msg_Set_RESPONSE( msg, response )\
   (uint16_t)( Insert_Bits( msg, response, VSEP_TXD_RESPONSE_CONFIGURATION_POSITION_RESPONSE, VSEP_TXD_RESPONSE_CONFIGURATION_WIDTH_RESPONSE ) )

//=============================================================================
// VSEP_Msg_Get_RESPONSE
//
// @func Get the SOH response value from the txd message element
//
// @parm uint8_t | msg | The txd message element to get the SOH reponse value
//
// @rdesc uint8_t value contain the RESPONSE value
//
// @end
//=============================================================================
#define VSEP_Msg_Get_RESPONSE( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_RESPONSE_CONFIGURATION_POSITION_RESPONSE, VSEP_TXD_RESPONSE_CONFIGURATION_WIDTH_RESPONSE ) )

//=============================================================================
// VSEP_Msg_Set_FSE_DISABLE
//
// @func Set FSE_DISABLE flag in the SOH response txd meesage element.
//
// @parm uint16_t | msg | The txd message element to set the FSE_DISABLE flag
//
// @parm uint8_t | fse_disable | The FSE_DISABLE flag
//
// @rdesc uint16_t txd message element representing the VSEP SOH response 
//    containing the new FSE_DISABLE flag
//
// @end
//=============================================================================
#define VSEP_Msg_Set_FSE_DISABLE( msg, fse_disable )\
   (uint16_t)( Insert_Bits( msg, fse_disable, VSEP_TXD_RESPONSE_CONFIGURATION_POSITION_FSE_DISABLE, VSEP_TXD_RESPONSE_CONFIGURATION_WIDTH_FSE_DISABLE ) )

//=============================================================================
// VSEP_Msg_Get_FSE_DISABLE
//
// @func Get message serial data input address from the VSEP.
//
// @parm uint16_t | msg | The txd message element to get the SDIA address
//
// @rdesc uint8_t value representing the FSE_DIABLE flag.
//
// @end
//=============================================================================
#define VSEP_Msg_Get_FSE_DISABLE( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_RESPONSE_CONFIGURATION_POSITION_FSE_DISABLE, VSEP_TXD_RESPONSE_CONFIGURATION_WIDTH_FSE_DISABLE ) )

///////////////////////////////////////////////////////////////////////////////
// ID - PCHXX_ON
// Base Offset: 02 H
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
// PCH17ON     15
//                         0	PCH[17]  commanded off
//                         1	PCH[17] commanded on
//                         
// PCH14ON     14
//                         0	PCH[14] not commanded on by the state of the 
//                            PCH14ON SPI bit. The output may be commanded on 
//                            by some other method.
//                         1	PCH[14] commanded on
//                         
// PCH13ON     13
//                         0	PCH[13] not commanded on by the state of the 
//                            PCH13ON SPI bit. The output may be commanded on 
//                            by some other method.
//                         1	PCH[13] commanded on
//                         
// PCH8ON      12
//                         0	PCH[8] not commanded on by the state of the PCH8ON 
//                            SPI bit. The output may be commanded on by some 
//                            other method.
//                         1	PCH[8] commanded on if DEC_DISCB = 0 or if fewer 
//                            than eight (8) cylinders.
//                         
// PCH7ON      11
//                         0	PCH[7] not commanded on by the state of the PGH7ON 
//                            SPI bit. The output may be commanded on by some 
//                            other method.
//                         1	PCH[7] commanded on if DEC_DISCB = 0 or if fewer 
//                            than seven (7) cylinders.
//                         
// PCH6ON      10
//                         0	PCH[6] not commanded on by the state of the PCH6ON 
//                            SPI bit. The output may be commanded on by some 
//                            other method.
//                         1	PCH[6] commanded on if DEC_DISCB = 0 or if fewer 
//                            than six (6) cylinders.
//                         
// PCH5ON       9           
//                         0	PCH[5] not commanded on by the state of the PCH5ON 
//                            SPI bit. The output may be commanded on by some 
//                            other method.
//                         1	PCH[5] commanded on if DEC_DISCB = 0 or if fewer 
//                            than five (5) cylinders.
//
// PCH4ON       8           
//                         0	PCH[4] not commanded on by the state of the PCH4ON 
//                            SPI bit. The output may be commanded on by some 
//                            other method.
//                         1	PCH[4] commanded on if DEC_DISCB = 0 or if fewer 
//                            than four (4) cylinders.
//
// PCH30ON      6 
//                         0	PCH[23] not commanded on by the state of the PCH30ON 
//                            SPI bit. The output may be commanded on by some 
//                            other method.
//                         1	PCH[30] commanded on
//                         
// PCH26ON      5 
//                         0	PCH[26] commanded off
//                         1	PCH[26] commanded on
//                         
// PCH25ON      4 
//                         0	PCH[25] commanded off
//                         1	PCH[25] commanded on
//                          
// PCH23ON      3 
//                         0	PCH[23] commanded off
//                         1	PCH[23] commanded on
//                         
// PCH20ON      2 
//                         0	PCH[20] commanded off
//                         1	PCH[20] commanded on
//                         
// PCH19ON      1
//                         0	PCH[19] commanded off
//                         1	PCH[19]commanded on
//                         
// PCH18ON      0
//                         0	PCH[18] not commanded on by the state of the 
//                            PCH18ON SPI bit. The output may be commanded on 
//                            by some other method.
//                         1	PCH[18] commanded on
//                         
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH17ON             =15,  //     15  PCH17ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH14ON             =14,  //     14  PCH14ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH13ON             =13,  //     13  PCH13ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH8ON              =12,  //     12  PCH8ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH7ON              =11,  //     11  PCH7ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH6ON              =10,  //     10  PCH6ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH5ON              = 9,  //      9  PCH5ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH4ON              = 8,  //      8  PCH4ON 
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH30ON             = 6,  //      6  PCH30ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH26ON             = 5,  //      5  PCH26ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH25ON             = 4,  //      4  PCH25ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH23ON             = 3,  //      3  PCH23ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH20ON             = 2,  //      2  PCH20ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH19ON             = 1,  //      1  PCH19ON
   VSEP_TXD_PCHXXON_CONFIGURATION_POSITION_PCH18ON             = 0   //      0  PCH18ON
}VSEP_TXD_PCHxxON_Configuration_Position_T;                    
                                                               
typedef enum                                                   
{                                                              
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH17ON                = 1,  //     15  PCH17ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH14ON                = 1,  //     14  PCH14ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH13ON                = 1,  //     13  PCH13ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH8ON                 = 1,  //     12  PCH8ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH7ON                 = 1,  //     11  PCH7ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH6ON                 = 1,  //     10  PCH6ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH5ON                 = 1,  //      9  PCH5ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH4ON                 = 1,  //      8  PCH4ON 
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH30ON                = 1,  //      6  PCH30ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH26ON                = 1,  //      5  PCH26ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH25ON                = 1,  //      4  PCH25ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH23ON                = 1,  //      3  PCH23ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH20ON                = 1,  //      2  PCH20ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH19ON                = 1,  //      1  PCH19ON
   VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH18ON                = 1   //      0  PCH18ON
}VSEP_TXD_PCHxxON_Configuration_Width_T;

//=============================================================================
// VSEP_Msg_PCHx_Set_State
//
// @func Set PCHxON state to the PCHxON txd message for the given channel
//
// @parm uint16_t | msg | The txd message element to store the PCHxON state
//
// @parm uint8_t | channel | The channel to assign the PCHxON state to.
// 
// @parm uint8_t | state | The PCHxON state to assign to the channel
// 
// @rdesc uint16_t value representing the PCHxON message element with the new 
//    PCHxON state
//
// @end
//=============================================================================
#define VSEP_Msg_PCHx_Set_State( msg, channel, state )\
   (uint16_t)( Insert_Bits( msg, state, (channel & 0x0F), VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH17ON ) ) 

//=============================================================================
// VSEP_Msg_PCHx_Get_State
//
// @func Get PCHxON state from the PCHxON txd message for the given channel
//
// @parm uint16_t | msg | The txd message element to retrieve the PCHxON state
//
// @parm uint8_t | channel | The channel to retrieve the PCHxON state from.
//
// @rdesc uint8_t value representing the PCHxON state
//
// @end
//=============================================================================
#define VSEP_Msg_PCHx_Get_State( msg, channel )\
   (uint8_t)( Extract_Bits( msg, (channel & 0x0F), VSEP_TXD_PCHXXON_CONFIGURATION_WIDTH_PCH17ON ) ) 

///////////////////////////////////////////////////////////////////////////////
// ID - PWM_X
// Base Offset: 04 H - PWM_ONT_1
// Base Offset: 08 H - PWM_ONT_2
// Base Offset: 0C H - PWM_ONT_3
// Base Offset: 10 H - PWM_ONT_4
// Base Offset: 14 H - PWM_ONT_5
// Base Offset: 18 H - PWM_ONT_6
// Base Offset: 1C H - PWM_ONT_7
// Base Offset: 20 H - PWM_ONT_8
// Reset Value: 0000 0000 H
//
// Field       Bits    Type  Description
// =========   ======= ====  =================================================
// ONT        [ 7: 0]       On Time Low Byte
// ONTXH       [ 3: 0]       On Time High Nibble
// PERXL       [ 7: 4]       Period Low Nibble
// PERH        [ 7: 0]       Period High Byte
//
//                         PWMCLK = EXTCLK/32 if CDIV_PWM[x]=0
//                         PWMCLK = EXTCLK/256 if CDIV_PWM[x]=1
//
// FrequencyPWM = (PWMCLK) / (Value of PWM Period Register + 1)
//
// % Duty Cycle = ( Value of ONTIME Register) / ( Value of PWM Period Register + 1) * 100%
//
// Note: Any duty cycle greater than 100% results in a 100% duty cycle.



///////////////////////////////////////////////////////////////////////////////
typedef enum 
{
   VSEP_TXD_PWM_CONFIGURATION_POSITION_ONTXL                   = 8,  // [15: 8] ONTL
   VSEP_TXD_PWM_CONFIGURATION_POSITION_ONTXH                   = 0,  // [ 3: 0] ONTXH
   VSEP_TXD_PWM_CONFIGURATION_POSITION_PERXL                   = 8,  // [15: 8] PERXL
   VSEP_TXD_PWM_CONFIGURATION_POSITION_PERXH                   = 0,  // [ 3: 0] PERH
   VSEP_TXD_PWM_CONFIGURATION_POSITION_CDIV                    = 4   //      4  CDIV
}VSEP_TXD_PWM_Configuration_Position_T;                        
                                                               
typedef enum                                                   
{                                                              
   VSEP_TXD_PWM_CONFIGURATION_WIDTH_ONTXL                      = 8,  // [15: 8] ONTL
   VSEP_TXD_PWM_CONFIGURATION_WIDTH_ONTXH                      = 4,  // [ 3: 0] ONTXH
   VSEP_TXD_PWM_CONFIGURATION_WIDTH_PERXL                      = 8,  // [15: 8] PERXL
   VSEP_TXD_PWM_CONFIGURATION_WIDTH_PERXH                      = 4,  // [ 3: 0] PERH
   VSEP_TXD_PWM_CONFIGURATION_WIDTH_CDIV                       = 1   //      4  CDIV
}VSEP_TXD_PWM_Configuration_Width_T;                           

typedef enum
{
   VSEP_PWM_REAL_TO_TXD_POSITION_ONTXL                         = 0,  // [ 7: 0] ONTXL
   VSEP_PWM_REAL_TO_TXD_POSITION_ONTXH                         = 8,  // [12: 8] ONTXH
   VSEP_PWM_REAL_TO_TXD_POSITION_PERXL                         = 0,  // [ 7: 0] PERXL
   VSEP_PWM_REAL_TO_TXD_POSITION_PERXH                         = 8   // [12: 8] PERXH
}VSEP_PWM_Real_To_TXD_Position_T;

typedef enum
{
   VSEP_PWM_REAL_TO_TXD_WIDTH_ONTXL                            = 8,  // [ 7: 0] ONTXL
   VSEP_PWM_REAL_TO_TXD_WIDTH_ONTXH                            = 4,  // [12: 8] ONTXH
   VSEP_PWM_REAL_TO_TXD_WIDTH_PERXL                            = 8,  // [ 7: 0] PERXL
   VSEP_PWM_REAL_TO_TXD_WIDTH_PERXH                            = 4   // [12: 8] PERXH
}VSEP_PWM_Real_To_TXD_Width_T;

//=============================================================================
// VSEP_Msg_PWM_Set_OnTime
//
// @func Set PWM ON_TIME value. The PWM on-time value spans 2 txd message elements. 
//    The two macros are used together to insert the whole PWM on-time value into 
//    the both txd message elements
//
// @parm uint16_t | msg | The txd message element to assign PWM on time value
//
// @parm uint16_t | on_time | The new PWM on-time value
// 
// @rdesc uint16_t value representing the PWM on-time message element with the new 
//    PWM on-time setting
//
// @ex
//    extern uint16_t VSEP_PWM_Txd[NUM_VSEPS][VSEP_MAX_PWM_CHANNELS][VSEP_PWM_TXD_MESSAGE_MAX];
//    uint16_t on_time = 0x80;
//
//    VSEP_PWM_Txd[device_num][channel][PWM_TXD_3] = VSEP_Msg_Get_Period( on_time );
//
// @end
//=============================================================================
#define VSEP_Msg_PWM_Set_OnTime( msg, on_time )\
   (uint16_t)( Insert_Bits( Insert_Bits( msg,\
         Extract_Bits( on_time, VSEP_PWM_REAL_TO_TXD_POSITION_ONTXL, VSEP_PWM_REAL_TO_TXD_WIDTH_ONTXL ),\
         VSEP_TXD_PWM_CONFIGURATION_POSITION_ONTXL, VSEP_TXD_PWM_CONFIGURATION_WIDTH_ONTXL ),\
         Extract_Bits( on_time, VSEP_PWM_REAL_TO_TXD_POSITION_ONTXH, VSEP_PWM_REAL_TO_TXD_WIDTH_ONTXH ),\
         VSEP_TXD_PWM_CONFIGURATION_POSITION_ONTXH, VSEP_TXD_PWM_CONFIGURATION_WIDTH_ONTXH ) )

//=============================================================================
// VSEP_Msg_PWM_Get_OnTime
//
// @func Get PWM on-time value. The PWM on-time value spans 2 txd message elements. 
//    The two macros are used together to extract the whole PWM on-time setting 
//    from both txd message elements.
//
// @parm uint16_t | msg | The txd message element retrieve to retrieve the PWM
//    on-time value.
//
// @rdesc uint16_t value representing the PWM on-time value
//
// @ex
//    extern uint16_t VSEP_PWM_Txd[NUM_VSEPS][VSEP_MAX_PWM_CHANNELS][VSEP_PWM_TXD_MESSAGE_MAX];
//    uint16_t on_time = 0;
//
//    on_time = VSEP_Msg_Get_OnTime( VSEP_PWM_Txd[device_num][channel][PWM_TXD_3] )
//
// @end
//=============================================================================
#define VSEP_Msg_PWM_Get_OnTime( msg )\
   (uint16_t)( Insert_Bits( Insert_Bits( 0,\
         Extract_Bits( msg, VSEP_TXD_PWM_CONFIGURATION_POSITION_ONTXH, VSEP_TXD_PWM_CONFIGURATION_WIDTH_ONTXH ),\
         VSEP_PWM_REAL_TO_TXD_POSITION_ONTXH, VSEP_PWM_REAL_TO_TXD_WIDTH_ONTXH ),\
         Extract_Bits( msg, VSEP_TXD_PWM_CONFIGURATION_POSITION_ONTXL, VSEP_TXD_PWM_CONFIGURATION_WIDTH_ONTXL ),\
         VSEP_PWM_REAL_TO_TXD_POSITION_ONTXL, VSEP_PWM_REAL_TO_TXD_WIDTH_ONTXL ) )

//=============================================================================
// VSEP_Msg_PWM_Set_Period
//
// @func Set PWM period value. The PWM period value spans 2 txd message elements. 
//    The two macros are used together to insert the whole PWM period value into 
//    the both txd message elements
//
// @parm uint16_t | msg | The txd message element assignthe PWM period value.
//
// @parm uint16_t | period | The new PWM period value
// 
// @rdesc uint16_t value representing the PWM period message element with the new 
//    PWM period setting
//
// @ex
//    extern uint16_t VSEP_PWM_Txd[NUM_VSEPS][VSEP_MAX_PWM_CHANNELS][VSEP_PWM_TXD_MESSAGE_MAX];
//    uint16_t period = 0x2ff;
//
//    VSEP_PWM_Txd[device_num][channel][PWM_TXD_2] = VSEP_Msg_Set_Period( period )
//
// @end
//=============================================================================
#define VSEP_Msg_PWM_Set_Period( msg, period )\
   (uint16_t)( Insert_Bits( Insert_Bits( msg,\
         Extract_Bits( period, VSEP_PWM_REAL_TO_TXD_POSITION_PERXL, VSEP_PWM_REAL_TO_TXD_WIDTH_PERXL ),\
         VSEP_TXD_PWM_CONFIGURATION_POSITION_PERXL, VSEP_TXD_PWM_CONFIGURATION_WIDTH_PERXL ),\
         Extract_Bits( period, VSEP_PWM_REAL_TO_TXD_POSITION_PERXH, VSEP_PWM_REAL_TO_TXD_WIDTH_PERXH ),\
         VSEP_TXD_PWM_CONFIGURATION_POSITION_PERXH, VSEP_TXD_PWM_CONFIGURATION_WIDTH_PERXH ) )

//=============================================================================
// VSEP_Msg_PWM_Get_Period
//
// @func Get PWM period value. The PWM period value spans 2 txd message elements. 
//    The two macros are used together to extract the whole PWM period setting 
//    from both txd message elements.
//
// @parm uint16_t | msg | The txd message element retrieve to retrieve the PWM
//    period value.
//
// @rdesc uint16_t value representing the PWM period value
//
// @ex
//    extern uint16_t VSEP_PWM_Txd[NUM_VSEPS][VSEP_MAX_PWM_CHANNELS][VSEP_PWM_TXD_MESSAGE_MAX];
//    uint16_t period;
//
//    period = VSEP_Msg_Get_Period( VSEP_PWM_Txd[device_num][channel][PWM_TXD_2] )
//
// @end
//=============================================================================
#define VSEP_Msg_PWM_Get_Period( msg )\
   (uint16_t)( Insert_Bits( Insert_Bits( 0,\
         Extract_Bits( msg, VSEP_TXD_PWM_CONFIGURATION_POSITION_PERXL, VSEP_TXD_PWM_CONFIGURATION_WIDTH_PERXL ),\
         VSEP_PWM_REAL_TO_TXD_POSITION_PERXL, VSEP_PWM_REAL_TO_TXD_WIDTH_PERXL ),\
         Extract_Bits( msg, VSEP_TXD_PWM_CONFIGURATION_POSITION_PERXH, VSEP_TXD_PWM_CONFIGURATION_WIDTH_PERXH ),\
         VSEP_PWM_REAL_TO_TXD_POSITION_PERXH, VSEP_PWM_REAL_TO_TXD_WIDTH_PERXH ) )

//=============================================================================
// VSEP_Msg_PWM_Set_Divider
//
// @func Set PWM CDIV state to the PWM CDIV txd message for the given channel
//
// @parm uint16_t | msg | The txd message element to store the PWM CDIV state
//
// @parm uint8_t | state | The PWM CDIV state to assign to the channel
// 
// @rdesc uint16_t value representing the PWM CDIV message element with the new 
//    PWM CDIV state for the given channel
//
// @end
//=============================================================================
#define VSEP_Msg_PWM_Set_Divider( msg, divider )\
   (uint16_t)( Insert_Bits( msg, divider, VSEP_TXD_PWM_CONFIGURATION_POSITION_CDIV, VSEP_TXD_PWM_CONFIGURATION_WIDTH_CDIV ) ) 

//=============================================================================
// VSEP_Msg_PWM_Get_Divider
//
// @func Get the PWM CDIV state from the PWM CDIV txd message for the given channel
//
// @parm uint16_t | msg | The txd message element to get the PWM CDIV state
//
// @rdesc uint8_t value representing the PWM CDIV state for the given channel
//
// @end
//=============================================================================
#define VSEP_Msg_PWM_Get_Divider( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_PWM_CONFIGURATION_POSITION_CDIV, VSEP_TXD_PWM_CONFIGURATION_WIDTH_CDIV ) ) 
                                                               
///////////////////////////////////////////////////////////////////////////////
// ID - VR_CFG
// Base Offset: 24 H - VR1
// Base Offset: 26 H - VR2
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
// VRxDLY    [14: 8]       VR1 delay in us = (VR1DLY[6:0] * 8) + 4
//       
// VRxRST         4
//                         0	VR #1 control logic reset is inactive
//                         1	VR #1 control logic provides a pules output on SPI write enable.
//
// VRxAT          3
//                         0	Adaptive threshold percentage of 30% selected for VR interface #1.
//                         1	Adaptive threshold percentage of 50% selected for VR interface #1.
//
// VRxMT     [ 2: 0]       DAC Minimum Threshold when no attenuation bits are on.
//
//                         SPI      Vp-p 
//                         Value    differential
//                         ======   =======
//                         000      0.250	
//                         001      0.335
//                         010      0.600	
//                         011      0.825	
//                         100      1.250		
//                         101      1.650	
//                         110      1.900	
//                         111      2.500
//
//
///////////////////////////////////////////////////////////////////////////////
typedef enum                                                   
{                                                              
   VSEP_TXD_VR_CONFIGURATION_POSITION_VRXDLY                   = 8,  // [14: 8] VRxDLY
   VSEP_TXD_VR_CONFIGURATION_POSITION_VRXRST                   = 4,  //      4  VRxRST
   VSEP_TXD_VR_CONFIGURATION_POSITION_VRXAT                    = 3,  //      3  VRxAT
   VSEP_TXD_VR_CONFIGURATION_POSITION_VRXMT                    = 0   // [ 2: 0] VRxMT
   
}VSEP_TXD_VR_Configuration_Position_T;

typedef enum
{
   VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXDLY                      = 7,  // [14: 8] VRxDLY
   VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXRST                      = 1,  //      4  VRxRST
   VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXAT                       = 1,  //      3  VRxAT
   VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXMT                       = 3   // [ 2: 0] VRxMT

}VSEP_TXD_VR_Configuration_Width_T;                            

typedef enum
{
   VSEP_TXD_DEPS_DLY_MASK        = 0x3F,
   VSEP_TXD_DEPS_MIN_TIME        = 0x0F,
   VSEP_TXD_DEPS_FIXED_BITS      = 5,
   VSEP_TXD_VR_DLY_MASK          = 0x7F,
   VSEP_TXD_VR_DLY_MIN_TIME      = 0x0F,
   VSEP_TXD_VR_DLY_FIXED_BITS    = 5
}VSEP_TXD_VR_DEPS_T;

//=============================================================================
// VSEP_Msg_VR_Set_Delay
//
// @func Set the VR interface #x digital filter delay control logic value
//    into the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to set the VR delay
//
// @parm uint8_t | delay | The desired VR x delay
// 
// @rdesc uint16_t msg element containing the VR interface #x digital filter 
//    delay value
//
// @end
//=============================================================================
#define VSEP_Msg_VR_Set_Delay( msg, delay )\
   (uint16_t)( Insert_Bits( msg, delay, VSEP_TXD_VR_CONFIGURATION_POSITION_VRXDLY, VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXDLY ) )

//=============================================================================
// VSEP_Msg_VR_Get_Delay
//
// @func Get the VR interface #x digital filter delay control logic value
//    from the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to get the VR delay.
//
// @rdesc uint8_t value representing the VR interface #x digital filter delay value 
//    stored in the msg element
//
// @end
//=============================================================================
#define VSEP_Msg_VR_Get_Delay( msg )\
   (uint16_t)( Extract_Bits( msg, VSEP_TXD_VR_CONFIGURATION_POSITION_VRXDLY, VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXDLY ) )

//=============================================================================
// VSEP_Msg_VR_Set_AT
//
// @func Set the VR interface #x adaptive threshold percentage value
//    into the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to set the VR interface #x 
//    adaptive threshold value
//
// @parm uint8_t | vr_at | The desired VR interface #x adaptive threshold value
// 
// @rdesc uint16_t msg element containing the VR interface #x adaptive threshold 
//    value
//
// @end
//=============================================================================
#define VSEP_Msg_VR_Set_AT( msg, vr_at )\
   (uint16_t)( Insert_Bits( msg, vr_at, VSEP_TXD_VR_CONFIGURATION_POSITION_VRXAT, VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXAT ) )

//=============================================================================
// VSEP_Msg_VR_Get_AT
//
// @func Get the VR interface #x adaptive threshold percentage value
//    from the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to get the VR interface #x 
//    adaptive threshold value.
//
// @rdesc uint8_t value representing the VR interface #x adaptive threshold value
//    stored in the msg element
//
// @end
//=============================================================================
#define VSEP_Msg_VR_Get_AT( msg )\
   (uint16_t)( Extract_Bits( msg, VSEP_TXD_VR_CONFIGURATION_POSITION_VRXAT, VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXAT ) )

//=============================================================================
// VSEP_Msg_VR_Set_MT
//
// @func Set the VR interface #x minimum threshold control logic value
//    into the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to set the VR interface #x 
//    minimum threshold control logic value
//
// @parm uint8_t | vr_mt | The desired VR interface #x minimum threshold control
//    logic value.
// 
// @rdesc uint16_t msg element containing the VR interface #x minimum threshold 
//    control logic value
//
// @end
//=============================================================================
#define VSEP_Msg_VR_Set_MT( msg, vr_mt )\
   (uint16_t)( Insert_Bits( msg, vr_mt, VSEP_TXD_VR_CONFIGURATION_POSITION_VRXMT, VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXMT ) )

//=============================================================================
// VSEP_Msg_VR_Get_MT
//
// @func Get the VR interface #x minimum threshold control logic value
//    from the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to get the VR interface #x 
//    minimum threshold control logic value.
//
// @rdesc uint8_t value representing the VR interface #x minimum threshold 
//    control logic value stored in the msg element
//
// @end
//=============================================================================
#define VSEP_Msg_VR_Get_MT( msg )\
   (uint16_t)( Extract_Bits( msg, VSEP_TXD_VR_CONFIGURATION_POSITION_VRXMT, VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXMT ) )

//=============================================================================
// VSEP_Msg_VR_Set_RST
//
// @func Set the VR interface #x reset control logic value
//    into the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to set the VR interface #x 
//    reset control logic value
//
// @parm uint8_t | vr_mt | The desired VR interface #x reset control
//    logic value.
// 
// @rdesc uint16_t msg element containing the VR interface #x reset 
//    control logic value
//
// @end
//=============================================================================
#define VSEP_Msg_VR_Set_RST( msg, vr_rst )\
   (uint16_t)( Insert_Bits( msg, vr_rst, VSEP_TXD_VR_CONFIGURATION_POSITION_VRXRST, VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXRST ) )

//=============================================================================
// VSEP_Msg_VR_Get_RST
//
// @func Get the VR interface #x reset control logic value
//    from the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to get the VR interface #x 
//    reset control logic value.
//
// @rdesc uint8_t value representing the VR interface #x reset 
//    control logic value stored in the msg element
//
// @end
//=============================================================================
#define VSEP_Msg_VR_Get_RST( msg )\
   (uint16_t)( Extract_Bits( msg, VSEP_TXD_VR_CONFIGURATION_POSITION_VRXRST, VSEP_TXD_VR_CONFIGURATION_WIDTH_VRXRST ) )

///////////////////////////////////////////////////////////////////////////////
// ID - DEPS_CFG
// Base Offset: 28 H
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
// DEPSDLY     [5:0]       Digital Engine Position Signal Filter Delay
//                         DEPS delay in us = (DEPSDLY[5:0] * 8) + 4    
//
///////////////////////////////////////////////////////////////////////////////
typedef enum                                                   
{                                                              
   VSEP_TXD_DEPS_CONFIGURATION_POSITION_DELAY                = 8   // [13: 8] DEPSDLY
}VSEP_TXD_DEPS_Configuration_Position_T;

typedef enum                                                   
{                                                              
   VSEP_TXD_DEPS_CONFIGURATION_WIDTH_DELAY                   = 6   // [13: 8] DEPSDLY
}VSEP_TXD_DEPS_Configuration_Width_T;                            

//=============================================================================
// VSEP_Msg_DEPS_Set_Delay
//
// @func Set the DEPS interface digital filter delay control logic value
//    into the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to set the DEPS delay
//
// @parm uint8_t | delay | The desired DEPS x delay
// 
// @rdesc uint16_t msg element containing the DEPS interface digital filter 
//    delay value
//
// @end
//=============================================================================
#define VSEP_Msg_DEPS_Set_Delay( msg, delay )\
   (uint16_t)( Insert_Bits( msg, delay, VSEP_TXD_DEPS_CONFIGURATION_POSITION_DELAY, VSEP_TXD_DEPS_CONFIGURATION_WIDTH_DELAY ) )

//=============================================================================
// VSEP_Msg_DEPS_Get_Delay
//
// @func Get the DEPS interface digital filter delay control logic value
//    from the message location pointed to by msg.
//
// @parm uint16_t | msg | The txd message element to get the DEPS delay.
//
// @rdesc uint8_t value representing the DEPS interface digital filter delay value 
//    stored in the msg element
//
// @end
//=============================================================================
#define VSEP_Msg_DEPS_Get_Delay( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_DEPS_CONFIGURATION_POSITION_DELAY, VSEP_TXD_DEPS_CONFIGURATION_WIDTH_DELAY ) )

///////////////////////////////////////////////////////////////////////////////
// ID - SLEW_CFG
// Base Offset: 2A H
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
// SLEW3     [15:13]       [PCH25-PCH30]
//
//                               Nominal   
//                               Gate
//                         SPI   Current
//                         Value (mA)
//                         =============
//                         000    100
//                         001    300
//                         010    500
//                         011    700
//                         100    900   
//                         101   1100     
//                         110   1300     
//                         111   1500     
//
// SLEW2     [10:12]       [PCH13-PCH24]
//
//                               Nominal   
//                               Gate
//                         SPI   Current
//                         Value (mA)
//                         =============
//                         000    100 
//                         001    300 
//                         010    500 
//                         011    700 
//                         100    900    
//                         101   1100      
//                         110   1300      
//                         111   1500      
//
// SLEW1     [ 9: 8]       [PCH1-PCH3] ([PCH4-PCH8] if used as EST Decode Logic )
//
//                               Nominal   
//                               Gate
//                         SPI   Current
//                         Value (mA)
//                         =============
//                         00    0.625   
//                         01    1.250 
//                         10    2.500 
//                         11    5.000 
//
// SLEWCAN   [ 5: 4]       Maximum 
//                         SPI   CAN 
//                         Value Bit Rate
//                         ====================================
//                         00    500Kbps 
//                         01    250Kbps
//                         10    125Kbps
//                         11    1.0Mbps
//
// SLEW5     [ 3: 2]       [PCH9-PCH12]
//
//                               Nominal   
//                               Gate
//                         SPI   Current
//                         Value (mA)
//                         =============
//                         00     300
//                         01     700
//                         10    1100
//                         11    1500
//
// SLEW4     [ 1: 0]      ([PCH4-PCH8] if used as END4 Discrete Input or PCH4ON SPI bit) 
//
//                               Nominal   
//                               Gate
//                         SPI   Current
//                         Value (mA)
//                         =============
//                         00    0.625
//                         01    1.250
//                         10    2.500
//                         11    5.000
//
///////////////////////////////////////////////////////////////////////////////
typedef enum                                                   
{                                                              
   VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_3    =13,  // [15:13] SLEW3
   VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_2    =10,  // [12:10] SLEW2
   VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_1    = 8,  // [ 9: 8] SLEW1
   VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_CAN  = 4,  // [ 5: 4] SLEWCAN
   VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_5    = 2,  // [ 3: 2] SLEW5
   VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_4    = 0   // [ 1: 0] SLEW4
}VSEP_TXD_Slew_Configuration_Position_T;                       
                                                               
typedef enum                                                   
{                                                              
   VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_3       = 3,  // [15:13] SLEW3
   VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_2       = 3,  // [10:12] SLEW2
   VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_1       = 2,  // [ 9: 8] SLEW1
   VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_CAN     = 2,  // [ 5: 4] SLEWCAN
   VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_5       = 2,  // [ 3: 2] SLEW5
   VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_4       = 2   // [ 1: 0] SLEW4
}VSEP_TXD_Slew_Configuration_Width_T;

//=============================================================================
// VSEP_Msg_SLEW_Set_Group_1
//
// @func Set slew group 1 setting from the txd message
//
// @parm uint16_t | msg | The txd message element to store the slew group 1
//    setting
//
// @parm uint8_t | slew | The new slew group 1.
// 
// @rdesc uint16_t value representing the slew message element with the new slew 
//    group 1 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Set_Group_1( msg, slew )\
   (uint16_t)( Insert_Bits( msg, slew, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_1, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_1 ) )

//=============================================================================
// VSEP_Msg_SLEW_Get_Group_1
//
// @func Get slew group 1 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the slew group 1 
//    setting
//
// @rdesc uint8_t value representing the slew group 1 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Get_Group_1( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_1, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_1 ) )

//=============================================================================
// VSEP_Msg_SLEW_Set_Group_2
//
// @func Set slew group 2 setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the slew group 1 
//    setting
//
// @parm uint8_t | slew | The new slew group 2 setting .
// 
// @rdesc uint16_t value representing the slew message element with the new slew 
//    group 2 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Set_Group_2( msg, slew )\
   (uint16_t)( Insert_Bits( msg, slew, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_2, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_2 ) )

//=============================================================================
// VSEP_Msg_SLEW_Get_Group_2
//
// @func Get slew group 2 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the slew group 2 
//    setting
//
// @rdesc uint8_t value representing the slew group 2 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Get_Group_2( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_2, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_2 ) )

//=============================================================================
// VSEP_Msg_SLEW_Set_Group_3
//
// @func Set slew group 3 setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the slew group 3
//    setting
//
// @parm uint8_t | slew | The new slew group 3 setting .
// 
// @rdesc uint16_t value representing the slew message element with the new slew 
//    group 3 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Set_Group_3( msg, slew )\
   (uint16_t)( Insert_Bits( msg, slew, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_3, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_3 ) )

//=============================================================================
// VSEP_Msg_SLEW_Get_Group_3
//
// @func Get slew group 3 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the slew group 3 
//    setting
//
// @rdesc uint8_t value representing the slew group 3 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Get_Group_3( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_3, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_3 ) )

//=============================================================================
// VSEP_Msg_SLEW_Set_Group_4
//
// @func Set slew group 4 setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the slew group 4
//    setting
//
// @parm uint8_t | slew | The new slew group 4 setting .
// 
// @rdesc uint16_t value representing the slew message element with the new slew 
//    group 4 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Set_Group_4( msg, slew )\
   (uint16_t)( Insert_Bits( msg, slew, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_4, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_4 ) )

//=============================================================================
// VSEP_Msg_SLEW_Get_Group_4
//
// @func Get slew group 4 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the slew group 4
//    setting
//
// @rdesc uint8_t value representing the slew group 4 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Get_Group_4( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_4, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_4 ) )

//=============================================================================
// VSEP_Msg_SLEW_Set_Group_5
//
// @func Set slew group 5 setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the slew group 5
//    setting
//
// @parm uint8_t | slew | The new slew group 5 setting.
// 
// @rdesc uint16_t value representing the slew message element with the new slew 
//    group 5 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Set_Group_5( msg, slew )\
   (uint16_t)( Insert_Bits( msg, slew, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_5, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_5 ) )

//=============================================================================
// VSEP_Msg_SLEW_Get_Group_5
//
// @func Get slew group 5 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the slew group 5
//    setting
//
// @rdesc uint8_t value representing the slew group 5 setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Get_Group_5( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_5, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_5 ) )

//=============================================================================
// VSEP_Msg_SLEW_Set_Group_CAN
//
// @func Set slew group CAN setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the slew group CAN
//    setting
//
// @parm uint8_t | slew | The new slew group CAN setting.
// 
// @rdesc uint16_t value representing the slew message element with the new slew 
//    group CAN setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Set_Group_CAN( msg, slew )\
   (uint16_t)( Insert_Bits( msg, slew, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_CAN, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_CAN ) )

//=============================================================================
// VSEP_Msg_SLEW_Get_Group_CAN
//
// @func Get slew group CAN setting from the txd message
//
// @parm uint8_t | msg | The txd message element retrieve the slew group CAN
//    setting
//
// @rdesc uint8_t value representing the slew group CAN setting
//
// @end
//=============================================================================
#define VSEP_Msg_SLEW_Get_Group_CAN( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SLEW_CONFIGURATION_POSITION_GROUP_CAN, VSEP_TXD_SLEW_CONFIGURATION_WIDTH_GROUP_CAN ) )

///////////////////////////////////////////////////////////////////////////////
// FAULT_LEVEL_CFG
// Base Offset: 2C H
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
// FLTLVL1     [3:0]       [PCH1-PCH3] ([PCH4-PCH8] if used as EST Decode Logic )
//
//                               25°C   
//                         SPI   Nominal
//                         Value Value
//                         =============
//                         0000   125 mV
//                         0001   174 mV
//                         0010   223 mV
//                         0011   298 mV
//                         0100   372 mV
//                         0101   447 mV
//                         0110   521 mV
//                         0111   596 mV
//                         1000  1903 mV
//                         1001  2053 mV
//                         1010  2203 mV
//                         1011  2353 mV
//                         1100  2503 mV
//                         1101  2653 mV
//                         1110  2803 mV
//                         1111  2953 mV

// FLTLVL2     [6:4]       [PCH9-PCH12] ([PCH4-PCH8] if used as END4 Discrete Input or 
//                         PCH4ON SPI bit) 
//
//                               25°C   
//                         SPI   Nominal
//                         Value Value
//                         =============
//                         000    125 mV
//                         001    174 mV
//                         010    223 mV
//                         111    298 mV
//                         100    372 mV
//                         101    447 mV
//                         110    521 mV
//                         111    596 mV
//
// FLTLVL3     [9:7]       [PCH13-PCH16]
//
//                               25°C   
//                         SPI   Nominal
//                         Value Value
//                         =============
//                         000    125 mV
//                         001    174 mV
//                         010    223 mV
//                         111    298 mV
//                         100    372 mV
//                         101    447 mV
//                         110    521 mV
//                         111    596 mV
//
// FLTLVL4   [13:10]       [PCH17-PCH18]
//
//                               25°C   
//                         SPI   Nominal
//                         Value Value
//                         =============
//                         0000   125 mV
//                         0001   174 mV
//                         0010   223 mV
//                         0011   298 mV
//                         0100   372 mV
//                         0101   447 mV
//                         0110   521 mV
//                         0111   596 mV
//                         1000   720 mV
//                         1001   794 mV
//                         1010   869 mV
//                         1011   943 mV
//                         1100  1018 mV
//                         1101  1092 mV
//                         1110  1167 mV
//                         1111  1241 mV
//
// FLTLVL5   [17:15]       [PCH19-PCH20]
//
//                               25°C   
//                         SPI   Nominal
//                         Value Value
//                         =============
//                         0000   125 mV
//                         0001   174 mV
//                         0010   223 mV
//                         0011   298 mV
//                         0100   372 mV
//                         0101   447 mV
//                         0110   521 mV
//                         0111   596 mV
//                         1000   720 mV
//                         1001   794 mV
//                         1010   869 mV
//                         1011   943 mV
//                         1100  1018 mV
//                         1101  1092 mV
//                         1110  1167 mV
//                         1111  1241 mV
//
// FLTLVL6   [20:18]       [PCH21-PCH24]
//
//                               25°C   
//                         SPI   Nominal
//                         Value Value
//                         =============
//                         000    125 mV
//                         001    174 mV
//                         010    223 mV
//                         111    298 mV
//                         100    372 mV
//                         101    447 mV
//                         110    521 mV
//                         111    596 mV
//
// FLTLVL7   [23:21]       [PCH25-PCH30]
//
//                               25°C   
//                         SPI   Nominal
//                         Value Value
//                         =============
//                         000    125 mV
//                         001    174 mV
//                         010    223 mV
//                         111    298 mV
//                         100    372 mV
//                         101    447 mV
//                         110    521 mV
//                         111    596 mV
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_2               =12,  // [14:12] FLTLVL2
   VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_1               = 8,  // [11: 8] FLTLVL1
   VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_4               = 3,  // [ 6: 3] FLTLVL4
   VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_3               = 0,  // [ 2: 0] FLTLVL3
   
   VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_6               =12,  // [14:12] FLTLVL6
   VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_5               = 8,  // [11: 8] FLTLVL5 
   VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_7               = 0   // [ 2: 0] FLTLVL7
                                                               
}VSEP_TXD_Fault_Configuration_Position_T;                      
                                                               
typedef enum                                                   
{                                                              
   VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_2                  = 3,  // [14:12] FLTLVL2
   VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_1                  = 4,  // [11: 8] FLTLVL1
   VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_4                  = 4,  // [ 6: 3] FLTLVL4 
   VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_3                  = 3,  // [ 2: 0] FLTLVL3
   
   VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_6                  = 3,  // [14:12] FLTLVL6 
   VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_5                  = 4,  // [11: 8] FLTLVL5 
   VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_7                  = 3   // [ 2: 0] FLTLVL7
}VSEP_TXD_Fault_Configuration_Width_T;

//=============================================================================
// VSEP_Msg_FAULT_Set_Level_1
//
// @func Set fault level 1 setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the fault level 1
//    setting
//
// @parm uint8_t | fltlvl | The new fault level 1 setting.
// 
// @rdesc uint16_t value representing the slew message element with the new 
//    fault level 1 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Set_Level_1( msg, fltlvl )\
   (uint16_t)( Insert_Bits( msg, fltlvl, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_1, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_1 ) )

//=============================================================================
// VSEP_Msg_FAULT_Get_Level_1
//
// @func Get fault level 1 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the fault level 1
//    setting
//
// @rdesc uint8_t value representing the fault level 1 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Get_Level_1( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_1, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_1 ) )

//=============================================================================
// VSEP_Msg_FAULT_Set_Level_2
//
// @func Set fault level 2 setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the fault level 2
//    setting
//
// @parm uint8_t | fltlvl | The new fault level 2 setting.
// 
// @rdesc uint16_t value representing the slew message element with the new 
//    fault level 2 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Set_Level_2( msg, fltlvl )\
   (uint16_t)( Insert_Bits( msg, fltlvl, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_2, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_2 ) )

//=============================================================================
// VSEP_Msg_FAULT_Get_Level_2
//
// @func Get fault level 2 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the fault level 2
//    setting
//
// @rdesc uint8_t value representing the fault level 2 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Get_Level_2( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_2, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_2 ) )

//=============================================================================
// VSEP_Msg_FAULT_Set_Level_3
//
// @func Set fault level 3 setting spans 2 txd message elements. The two macros
//    are used to insert the whole fault level 5 value into the both txt
//    message elements
//
// @parm uint16_t | msg | The txd message element store the fault level 3
//    setting
//
// @parm uint8_t | fltlvl | The new fault level 3 setting.
// 
// @rdesc uint16_t value representing the slew message element with the new 
//    fault level 3 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Set_Level_3( msg, fltlvl )\
   (uint16_t)( Insert_Bits( msg, fltlvl, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_3, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_3 ) )

//=============================================================================
// VSEP_Msg_FAULT_Get_Level_3
//
// @func Get fault level 3 setting spans 2 txd message elements. The two macros
//    are used to extract the whole fault level 5 setting from the txd message
//    elements.
//
// @parm uint16_t | msg | The txd message element retrieve the fault level 3
//    setting
//
// @rdesc uint8_t value representing the fault level 3 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Get_Level_3( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_3 , VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_3  ) )

//=============================================================================
// VSEP_Msg_FAULT_Set_Level_4
//
// @func Set fault level 4 setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the fault level 4
//    setting
//
// @parm uint8_t | fltlvl | The new fault level 4 setting.
// 
// @rdesc uint16_t value representing the slew message element with the new 
//    fault level 4 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Set_Level_4( msg, fltlvl )\
   (uint16_t)( Insert_Bits( msg, fltlvl, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_4, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_4 ) )

//=============================================================================
// VSEP_Msg_FAULT_Get_Level_4
//
// @func Get fault level 4 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the fault level 4
//    setting
//
// @rdesc uint8_t value representing the fault level 4 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Get_Level_4( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_4, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_4 ) )

//=============================================================================
// VSEP_Msg_FAULT_Set_Level_5
//
// @func Set fault level 5 setting spans 2 txd message elements. The two macros
//    are used to insert the whole fault level 5 value into the both txt
//    message elements
//
// @parm uint16_t | msg | The txd message element store the fault level 5
//    setting
//
// @parm uint8_t | fltlvl | The new fault level 5 setting.
// 
// @rdesc uint16_t value representing the slew message element with the new 
//    fault level 5 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Set_Level_5( msg, fltlvl )\
   (uint16_t)( Insert_Bits( msg, fltlvl, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_5, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_5 ) )

//=============================================================================
// VSEP_Msg_FAULT_Get_Level_5
//
// @func Get fault level 5 setting spans 2 txd message elements. The two macros
//    are used to extract the whole fault level 5 setting from the txd message
//    elements.
//
// @parm uint16_t | msg | The txd message element retrieve the fault level 5
//    setting
//
// @rdesc uint8_t value representing the fault level 5 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Get_Level_5( msg  )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_5, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_5 ) )

//=============================================================================
// VSEP_Msg_FAULT_Set_Level_6
//
// @func Set fault level 6 setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the fault level 6
//    setting
//
// @parm uint8_t | fltlvl | The new fault level 6 setting.
// 
// @rdesc uint16_t value representing the slew message element with the new 
//    fault level 6 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Set_Level_6( msg, fltlvl )\
   (uint16_t)( Insert_Bits( msg, fltlvl, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_6, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_6 ) )

//=============================================================================
// VSEP_Msg_FAULT_Get_Level_6
//
// @func Get fault level 6 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the fault level 6
//    setting
//
// @rdesc uint8_t value representing the fault level 6 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Get_Level_6( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_6, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_6 ) )

//=============================================================================
// VSEP_Msg_FAULT_Set_Level_7
//
// @func Set fault level 7 setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the fault level 7
//    setting
//
// @parm uint8_t | fltlvl | The new fault level 7 setting.
// 
// @rdesc uint16_t value representing the slew message element with the new 
//    fault level 7 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Set_Level_7( msg, fltlvl )\
   (uint16_t)( Insert_Bits( msg, fltlvl, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_7, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_7 ) )

//=============================================================================
// VSEP_Msg_FAULT_Get_Level_7
//
// @func Get fault level 7 setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the fault level 7
//    setting
//
// @rdesc uint8_t value representing the fault level 7 setting
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Get_Level_7( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_CONFIGURATION_POSITION_LEVEL_7, VSEP_TXD_FAULT_CONFIGURATION_WIDTH_LEVEL_7 ) )

///////////////////////////////////////////////////////////////////////////////
// FAULT_FILTER_CFG
// Base Offset: 30 H
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
// FILT_13TO16    [15:14]  Short to Battery Fault Filter Time For PCH13-PCH16
//
// FILT_9TO12     [13:12]  Short to Battery Fault Filter Time For PCH9-PCH12
//
// FILT_1TO8_NSP  [11:10]  Short to Battery Fault Filter Time For PCH1-PCH8 
//                         not defined as ignition channels.
//
// FILT_1TO8_SP   [ 9: 8]  Short to Battery Fault Filter Time For PCH1-PCH8 
//                         defined as ignition channels.
//
// FILT_25TO30    [ 7: 6]  Short to Battery Fault Filter Time For PCH25-PCH30
//
// FILT_21TO24    [ 5: 4]  Short to Battery Fault Filter Time For PCH21-PCH24
//
// FILT_19TO20    [ 3: 2]  Short to Battery Fault Filter Time For PCH19-PCH20
//
// FILT_17TO18    [ 1: 0]  Short to Battery Fault Filter Time For PCH17-PCH18

//                          ===========================================
//                         | FILT_xTOx[1:0]  | Nominal Filter time (us)|
//                         | ==========================================|                     
//                         | 00              |  7.5                    |
//                         | 01              | 15.0                    |
//                         | 10              | 34.0                    |
//                         | 11              | 46.0                    |
//                         ===========================================
//                         FLTLVL[x] Short-to-Battery Filter Time
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_1TO8_SP         = 8,  // [ 9: 8] FILT_1TO8_SP
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_1TO8_NSP        =10,  // [11:10] FILT_1TO8_NSP
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_9TO12           =12,  // [13:12] FILT_9TO12
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_13TO16          =14,  // [15:14] FILT_13TO16
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_17TO18          = 0,  // [ 1: 0] FILT_17TO18
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_19TO20          = 2,  // [ 3: 2] FILT_19TO20 
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_21TO24          = 4,  // [ 5: 4] FILT_21TO24
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_25TO30          = 6   // [ 7: 6] FILT_25TO30
}VSEP_TXD_Fault_Filter_Configuration_Position_T;                      
                                                               
typedef enum                                                   
{                                                              
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_1TO8_SP            = 2,  // [ 9: 8] FILT_1TO8_SP
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_1TO8_NSP           = 2,  // [11:10] FILT_1TO8_NSP
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_9TO12              = 2,  // [13:12] FILT_9TO12
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_13TO16             = 2,  // [15:14] FILT_13TO16
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_17TO18             = 2,  // [ 1: 0] FILT_17TO18
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_19TO20             = 2,  // [ 3: 2] FILT_19TO20 
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_21TO24             = 2,  // [ 5: 4] FILT_21TO24
   VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_25TO30             = 2   // [ 7: 6] FILT_25TO30
}VSEP_TXD_Fault_Filter_Configuration_Width_T;

//=============================================================================
// VSEP_Msg_FAULT_Filter_Set_Spark_Channels_1_To_8
//
// @func Set fault filter time for channels 1 - 8 that are used as spark control
//
// @parm uint16_t | msg | The txd message element to store the fault filter time.
//
// @parm uint8_t | flttim | The new fault filter time for channels 1 - 8 that
//    are used as spark control.
// 
// @rdesc uint16_t value representing the fault filter message element with the new 
//    fault filter time for channels 1 - 8 that are used as spark control.
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Set_Spark_Channels_1_To_8( msg, flttim )\
   (uint16_t)( Insert_Bits( msg, flttim, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_1TO8_SP, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_1TO8_SP ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Get_Spark_Channels_1_To_8
//
// @func Get fault filter time for channesl 1 - 8 that are used as spark control.
//
// @parm uint16_t | msg | The txd message element to retrieve the fault filter
//    time.
//
// @rdesc uint8_t value representing the fault filter time for channels 1 - 8
//    that are used as spark control
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Get_Spark_Channels_1_To_8( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_1TO8_SP, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_1TO8_SP ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Set_Non_Spark_Channels_1_To_8
//
// @func Set fault filter time for channels 1 - 8 that are not used as spark control
//
// @parm uint16_t | msg | The txd message element to store the fault filter time.
//
// @parm uint8_t | flttim | The new fault filter time for channels 1 - 8 that
//    are not used as spark control.
// 
// @rdesc uint16_t value representing the fault filter message element with the new 
//    fault filter time for channels 1 - 8 that are not used as spark control.
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Set_Non_Spark_Channels_1_To_8( msg, flttim )\
   (uint16_t)( Insert_Bits( msg, flttim, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_1TO8_NSP, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_1TO8_NSP ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Get_Non_Spark_Channels_1_To_8
//
// @func Get fault filter time for channesl 1 - 8 that are not used as spark control.
//
// @parm uint16_t | msg | The txd message element to retrieve the fault filter
//    time.
//
// @rdesc uint8_t value representing the fault filter time for channels 1 - 8
//    that are not used as spark control
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Get_Non_Spark_Channels_1_To_8( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_1TO8_NSP, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_1TO8_NSP ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Set_Channels_9_To_12
//
// @func Set fault filter time for channels 9 - 12.
//
// @parm uint16_t | msg | The txd message element to store the fault filter time.
//
// @parm uint8_t | flttim | The new fault filter time for channels 9 - 12.
// 
// @rdesc uint16_t value representing the fault filter message element with the new 
//    fault filter time for channels 9 - 12 .
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Set_Channels_9_To_12( msg, flttim )\
   (uint16_t)( Insert_Bits( msg, flttim, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_9TO12, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_9TO12 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Get_Channels_9_To_12
//
// @func Get fault filter time for channesl 9 - 12.
//
// @parm uint16_t | msg | The txd message element to retrieve the fault filter
//    time.
//
// @rdesc uint8_t value representing the fault filter time for channels 9 - 12
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Get_Channels_9_To_12( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_9TO12, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_9TO12 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Set_Channels_13_To_16
//
// @func Set fault filter time for channels 13 - 16.
//
// @parm uint16_t | msg | The txd message element to store the fault filter time.
//
// @parm uint8_t | flttim | The new fault filter time for channels 13 - 16.
// 
// @rdesc uint16_t value representing the fault filter message element with the new 
//    fault filter time for channels 13 - 16 .
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Set_Channels_13_To_16( msg, flttim )\
   (uint16_t)( Insert_Bits( msg, flttim, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_13TO16, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_13TO16 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Get_Channels_13_To_16
//
// @func Get fault filter time for channesl 13 - 16.
//
// @parm uint16_t | msg | The txd message element to retrieve the fault filter
//    time.
//
// @rdesc uint8_t value representing the fault filter time for channels 13 - 16
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Get_Channels_13_To_16( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_13TO16, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_13TO16 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Set_Channels_17_To_18
//
// @func Set fault filter time for channels 17 - 18.
//
// @parm uint16_t | msg | The txd message element to store the fault filter time.
//
// @parm uint8_t | flttim | The new fault filter time for channels 17 - 18.
// 
// @rdesc uint16_t value representing the fault filter message element with the new 
//    fault filter time for channels 17 - 18 .
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Set_Channels_17_To_18( msg, flttim )\
   (uint32_t)( Insert_Bits( msg, flttim, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_17TO18, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_17TO18 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Get_Channels_17_To_18
//
// @func Get fault filter time for channesl 17 - 18.
//
// @parm uint16_t | msg | The txd message element to retrieve the fault filter
//    time.
//
// @rdesc uint8_t value representing the fault filter time for channels 17 - 18
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Get_Channels_17_To_18( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_17TO18, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_17TO18 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Set_Channels_19_To_20
//
// @func Set fault filter time for channels 19 - 20.
//
// @parm uint16_t | msg | The txd message element to store the fault filter time.
//
// @parm uint8_t | flttim | The new fault filter time for channels 19 - 20.
// 
// @rdesc uint16_t value representing the fault filter message element with the new 
//    fault filter time for channels 19 - 20 .
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Set_Channels_19_To_20( msg, flttim )\
   (uint16_t)( Insert_Bits( msg, flttim, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_19TO20, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_19TO20 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Get_Channels_19_To_20
//
// @func Get fault filter time for channesl 19 - 20.
//
// @parm uint16_t | msg | The txd message element to retrieve the fault filter
//    time.
//
// @rdesc uint8_t value representing the fault filter time for channels 19 - 20
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Get_Channels_19_To_20( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_19TO20, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_19TO20 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Set_Channels_21_To_24
//
// @func Set fault filter time for channels 21 - 24.
//
// @parm uint16_t | msg | The txd message element to store the fault filter time.
//
// @parm uint8_t | flttim | The new fault filter time for channels 21 - 24.
// 
// @rdesc uint16_t value representing the fault filter message element with the new 
//    fault filter time for channels 21 - 24 .
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Set_Channels_21_To_24( msg, flttim )\
   (uint16_t)( Insert_Bits( msg, flttim, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_21TO24, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_21TO24 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Get_Channels_21_To_24
//
// @func Get fault filter time for channesl 21 - 24.
//
// @parm uint16_t | msg | The txd message element to retrieve the fault filter
//    time.
//
// @rdesc uint8_t value representing the fault filter time for channels 21 - 24
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Get_Channels_21_To_24( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_21TO24, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_21TO24 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Set_Channels_25_To_30
//
// @func Set fault filter time for channels 25 - 30.
//
// @parm uint16_t | msg | The txd message element to store the fault filter time.
//
// @parm uint8_t | flttim | The new fault filter time for channels 25 - 30.
// 
// @rdesc uint16_t value representing the fault filter message element with the new 
//    fault filter time for channels 25 - 30 .
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Set_Channels_25_To_30( msg, flttim )\
   (uint16_t)( Insert_Bits( msg, flttim, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_25TO30, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_25TO30 ) )

//=============================================================================
// VSEP_Msg_FAULT_Filter_Get_Channels_25_To_30
//
// @func Get fault filter time for channesl 25 - 30.
//
// @parm uint16_t | msg | The txd message element to retrieve the fault filter
//    time.
//
// @rdesc uint8_t value representing the fault filter time for channels 25 - 30
//
// @end
//=============================================================================
#define VSEP_Msg_FAULT_Filter_Get_Channels_25_To_30( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_FAULT_FILTER_CONFIGURATION_POSITION_FILT_25TO30, VSEP_TXD_FAULT_FILTER_CONFIGURATION_WIDTH_FILT_25TO30 ) )

///////////////////////////////////////////////////////////////////////////////
// LEDMODE_CFG
// Base Offset: 32 H
// Reset Value: 0000 0000 H
//
// Field       Bits    Type  Description
// =========   ======= ====  =================================================
// LEDMODE_25  [15:14] 
//                            0 PCH25 Off State Diagnostic Current Sounce is Enabled.
//                            1 PCH25 Off State Diagnostic Current Sounce is Disabled.
// LEDMODE_26  [13:12] 
//                            0 PCH26 Off State Diagnostic Current Sounce is Enabled.
//                            1 PCH26 Off State Diagnostic Current Sounce is Disabled.
// LEDMODE_30  [11:10]  
//                            0 PCH30 Off State Diagnostic Current Sounce is Enabled.
//                            1 PCH30 Off State Diagnostic Current Sounce is Disabled.
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_25         = 8,  //      8  LEDMODE_25
   VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_26         = 9,  //      9  LEDMODE_26
   VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_30         =10   //     10  LEDMODE_30
}VSEP_TXD_LEDMODE_Configuration_Position_T;                      
                                                               
typedef enum                                                   
{                                                              
   VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_25            = 1,  //      8  LEDMODE_25
   VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_26            = 1,  //      9  LEDMODE_26
   VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_30            = 1,   //     10  LEDMODE_30
   VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_ALL           = 3   //     10  LEDMODE_25,26,30
}VSEP_TXD_LEDMODE_Configuration_Width_T;

//=============================================================================
// VSEP_Msg_LEDMODE_Set_Channel_25
//
// @func Set LED mode configuration for channels 25.
//
// @parm uint16_t | msg | The txd message element to store the LED mode setting.
//
// @parm uint8_t | ctrl | The desired LED mode for channels 25
// 
// @rdesc uint16_t value representing the LED mode message element with the new 
//    LED Mode setting for channels 25
//
// @end
//=============================================================================
#define VSEP_Msg_LEDMODE_Set_Channel_25( msg, ctrl )\
   (uint16_t)( Insert_Bits( msg, ctrl, VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_25, VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_25 ) )

//=============================================================================
// VSEP_Msg_LEDMODE_Get_Channel_25
//
// @func Get LED Mode configuration for channesl 25.
//
// @parm uint16_t | msg | The txd message element to retrieve the LED Mode setting
//
// @rdesc uint8_t value representing the LED Mode for channels 25
//
// @end
//=============================================================================
#define VSEP_Msg_LEDMODE_Get_Channel_25( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_25, VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_25 ) )

//=============================================================================
// VSEP_Msg_LEDMODE_Set_Channel_26
//
// @func Set LED mode configuration for channels 26.
//
// @parm uint16_t | msg | The txd message element to store the LED mode setting.
//
// @parm uint8_t | ctrl | The desired LED mode for channels 26
// 
// @rdesc uint16_t value representing the LED mode message element with the new 
//    LED Mode setting for channels 26
//
// @end
//=============================================================================
#define VSEP_Msg_LEDMODE_Set_Channel_26( msg, ctrl )\
   (uint16_t)( Insert_Bits( msg, ctrl, VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_26, VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_26 ) )

//=============================================================================
// VSEP_Msg_LEDMODE_Get_Channel_26
//
// @func Get LED Mode configuration for channesl 26.
//
// @parm uint16_t | msg | The txd message element to retrieve the LED Mode setting
//
// @rdesc uint8_t value representing the LED Mode for channels 26
//
// @end
//=============================================================================
#define VSEP_Msg_LEDMODE_Get_Channel_26( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_26, VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_26 ) )

//=============================================================================
// VSEP_Msg_LEDMODE_Set_Channel_30
//
// @func Set LED mode configuration for channels 30.
//
// @parm uint16_t | msg | The txd message element to store the LED mode setting.
//
// @parm uint8_t | ctrl | The desired LED mode for channels 30
// 
// @rdesc uint16_t value representing the LED mode message element with the new 
//    LED Mode setting for channels 30
//
// @end
//=============================================================================
#define VSEP_Msg_LEDMODE_Set_Channel_30( msg, ctrl )\
   (uint16_t)( Insert_Bits( msg, ctrl, VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_30, VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_30 ) )

//=============================================================================
// VSEP_Msg_LEDMODE_Get_Channels_30
//
// @func Get LED Mode configuration for channesl 30.
//
// @parm uint16_t | msg | The txd message element to retrieve the LED Mode setting
//
// @rdesc uint8_t value representing the LED Mode for channels 30
//
// @end
//=============================================================================

#define VSEP_Msg_LEDMODE_Get_Channel_30( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_30, VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_30 ) )

//=============================================================================
// VSEP_Msg_LEDMODE_Set_Channel_ALL
//
// @func Set LED mode configuration for channels 24,26,30.
//
// @parm uint16_t | msg | The txd message element to store the LED mode setting.
//
// @parm uint8_t | ctrl | The desired LED mode for channels 30
// 
// @rdesc uint16_t value representing the LED mode message element with the new 
//    LED Mode setting for channels 30
//
// @end
//=============================================================================
#define VSEP_Msg_LEDMODE_Set_Channel_ALL( msg, ctrl )\
   (uint16_t)( Insert_Bits( msg, ctrl, VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_25, VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_ALL ) )

//=============================================================================
// VSEP_Msg_LEDMODE_Get_Channel_ALL
//
// @func Get LED Mode configuration for channesl 25,26,30.
//
// @parm uint16_t | msg | The txd message element to retrieve the LED Mode setting
//
// @rdesc uint8_t value representing the LED Mode for channels 25,26,30.
//
// @end
//=============================================================================
#define VSEP_Msg_LEDMODE_Get_Channel_ALL( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_LEDMODE_CONFIGURATION_POSITION_25, VSEP_TXD_LEDMODE_CONFIGURATION_WIDTH_ALL ) )

///////////////////////////////////////////////////////////////////////////////
// ID - IGBT_FAULT_CFG
// Base Offset: 34 H
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
// GRADTHR   [13:11]
//                               Nominal     Nominal 
//                         SPI      	IGSNSHI -   Internal 
//                         Value       IGSNSLO     GRADTHR 
//                                     Value       Value 
//                                     (mV)	      (V)
//                         ================================
//                         000	      160	      1.6
//                         001	      180	      1.8
//                         010	      200	      2.0
//                         011	      220	      2.20
//                         100	      240	      2.40
//                         101	      260	      2.60
//                         110	      280	      2.80
//                         111	      300	      3.0
//
// GRADFILT  [10: 8] 
//           
//                                  Nominal 
//                                  Gradient
//                                  Check 
//                                  Timer 
//                         SPI     Value
//                         Value	   (ms)
//                         ================
//                         00	      0.48 
//                         01	      0.992
//                         10	      2.016
//                         11	      2.976
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_POSITION_GRADTHR          = 11,  // [13:11] GRADTHR
   VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_POSITION_GRADFILT         =  8   // [10: 8] GRADFILT
}VSEP_TXD_IGBT_FAULT_CFG_Configuration_Position_T;

typedef enum
{
   VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_WIDTH_GRADTHR             =  3,  // [13:11] GRADTHR
   VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_WIDTH_GRADFILT            =  3   // [10: 8] GRADFILT
}VSEP_TXD_IGBT_FAULT_CFG_Configuration_Width_T;

//=============================================================================
// VSEP_Msg_IGBT_Set_GRADFILT
//
// @func Set IGBT GRADFILT setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the IGBT GRADFILT
//    setting
//
// @parm uint8_t | gradfilt | The new IGBT GRADFILT setting.
// 
// @rdesc uint16_t value representing the IGBT CFG message element with the new 
//    IGBT GRADFILT setting
//
// @end
//=============================================================================
#define VSEP_Msg_IGBT_Set_GRADFILT( msg, gradfilt )\
   (uint16_t)( Insert_Bits( msg, gradfilt, VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_POSITION_GRADFILT, VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_WIDTH_GRADFILT ) )

//=============================================================================
// VSEP_Msg_IGBT_Get_GRADFILT
//
// @func Get IGBT GRADFILT setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the IGBT GRADFILT
//    setting
//
// @rdesc uint8_t value representing the IGBT GRADFILT setting
//
// @end
//=============================================================================
#define VSEP_Msg_IGBT_Get_GRADFILT( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_POSITION_GRADFILT, VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_WIDTH_GRADFILT ) )

//=============================================================================
// VSEP_Msg_IGBT_Set_GRADTHR
//
// @func Set IGBT GRADTHR setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the IGBT GRADTHR
//    setting
//
// @parm uint8_t | gradthr | The new IGBT GRADTHR setting.
// 
// @rdesc uint16_t value representing the IGBT CFG message element with the new 
//    IGBT GRADTHR setting
//
// @end
//=============================================================================
#define VSEP_Msg_IGBT_Set_GRADTHR( msg, gradthr )\
   (uint16_t)( Insert_Bits( msg, gradthr, VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_POSITION_GRADTHR, VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_WIDTH_GRADTHR ) )

//=============================================================================
// VSEP_Msg_IGBT_Get_GRADTHR
//
// @func Get IGBT GRADTHR setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the IGBT GRADTHR
//    setting
//
// @rdesc uint8_t value representing the IGBT GRADTHR setting
//
// @end
//=============================================================================
#define VSEP_Msg_IGBT_Get_GRADTHR( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_POSITION_GRADTHR, VSEP_TXD_IGBT_FAULT_CFG_CONFIGURATION_WIDTH_GRADTHR ) )

///////////////////////////////////////////////////////////////////////////////
// ID - EST_CTRL
// Base Offset: 36 H
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
//  EST2EN       15
//                         0	Ignore data in the EST2C[2:0] bits
//                         1	Write data from EST2C[2:0] into counter. 
//
//  EST2C    [14:12]       Data to be written directly into the EST2 counter.
//
//  EST1EN       11
//                         0	Ignore data in the EST1C[2:0] bits
//                         1	Write data from EST1C[2:0] into counter. 
//
//  EST1C    [10: 8]       Data to be written directly into the EST1 counter.
//
//  PFMODE        2
//                         0	Paired firing mode of EST logic is disabled.
//                         1	Paired firing mode of EST logic is enabled.
//
//  INDEX         1
//                         0	EST[x]C[2:0] counters will increment by only one (1), 
//                            each time an index operation occurs.
//                         1	EST[x]C[2:0] counters will increment by two (2), 
//                            each time an index operation occurs
//
//  EDGE          0
//                         0  ESTC1 will index on the falling edge of EST1
//                            ESTC2 will index on the falling edge of EST2
//                         
//                         1  ESTC1 will index on the rising edge of SYNC
//                            ESTC2 will index on the falling edge of SYNC
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST2CEN            =15,  //     15  EST2CEN
   VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST2C              =12,  // [14:12] EST2C
   VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1CEN            =11,  //     11  EST1CEN
   VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1CEN_BYTE_FORMAT            =3,  //     3  EST1CEN
   VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1C              = 8,  // [10: 8] EST1C
   VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1C_BYTE_FORMAT              = 0,  // [2: 0] EST1C
   VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_PFMODE             = 2,  //      2  PFMODE
   VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_INDEX              = 1,  //      1  INDEX
   VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EDGE               = 0   //      0  EDGE
}VSEP_TXD_EST_CTRL_Configuration_Position_T;                   
                                                               
typedef enum                                                   
{                                                              
   VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST2CEN               = 1,  //     15  EST2CEN
   VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST2C                 = 3,  // [14:12] EST2C
   VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST1CEN               = 1,  //     11  EST1CEN
   VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST1C                 = 3,  // [10: 8] EST1C
   VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_PFMODE                = 1,  //      2  PFMODE
   VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_INDEX                 = 1,  //      1  INDEX
   VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EDGE                  = 1   //      0  EDGE
}VSEP_TXD_EST_CTRL_Configuration_Width_T;




//=============================================================================
// VSEP_Msg_EST_Set_EST2CEN
//
// @func Set EST EST2CEN setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST EDGE
//    setting
//
// @parm uint8_t | edge | The new EST EDGE setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_EST2CEN( msg, edge )\
   (uint16_t)( Insert_Bits( msg, edge, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST2CEN, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST2CEN ) )

//=============================================================================
// VSEP_Msg_EST_Get_EST2CEN
//
// @func Get EST EST2CEN setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the EST EDGE
//    setting
//
// @rdesc uint8_t value representing the EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_EST2CEN( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST2CEN, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST2CEN ) )

//=============================================================================
// VSEP_Msg_EST_Set_EST2C
//
// @func Set EST EST2C setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST EDGE
//    setting
//
// @parm uint8_t | edge | The new EST EDGE setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_EST2C( msg, edge )\
   (uint16_t)( Insert_Bits( msg, edge, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST2C, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST2C ) )

//=============================================================================
// VSEP_Msg_EST_Get_EST2C
//
// @func Get EST EST2C setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the EST EDGE
//    setting
//
// @rdesc uint8_t value representing the EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_EST2C( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST2C, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST2C ) )

//=============================================================================
// VSEP_Msg_EST_Set_EST1CEN
//
// @func Set EST EST2CEN setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST EDGE
//    setting
//
// @parm uint8_t | edge | The new EST EDGE setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_EST1CEN_BYTE_FORMAT( msg, edge )\
   (uint16_t)( Insert_Bits( msg, edge, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1CEN_BYTE_FORMAT, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST1CEN ) )

//=============================================================================
// VSEP_Msg_EST_Set_EST1CEN
//
// @func Set EST EST2CEN setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST EDGE
//    setting
//
// @parm uint8_t | edge | The new EST EDGE setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_EST1CEN( msg, edge )\
   (uint16_t)( Insert_Bits( msg, edge, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1CEN, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST1CEN ) )

//=============================================================================
// VSEP_Msg_EST_Get_EST1CEN
//
// @func Get EST EST2CEN setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the EST EDGE
//    setting
//
// @rdesc uint8_t value representing the EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_EST1CEN( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1CEN, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST1CEN ) )

//=============================================================================
// VSEP_Msg_EST_Set_EST1C
//
// @func Set EST EST2CEN setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST EDGE
//    setting
//
// @parm uint8_t | edge | The new EST EDGE setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_EST1C_BYTE_FORMAT( msg, edge )\
   (uint16_t)( Insert_Bits( msg, edge, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1C_BYTE_FORMAT, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST1C ) )

//=============================================================================
// VSEP_Msg_EST_Set_EST1C
//
// @func Set EST EST2CEN setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST EDGE
//    setting
//
// @parm uint8_t | edge | The new EST EDGE setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_EST1C( msg, edge )\
   (uint16_t)( Insert_Bits( msg, edge, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1C, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST1C ) )

//=============================================================================
// VSEP_Msg_EST_Get_EST1C
//
// @func Get EST EST2CEN setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the EST EDGE
//    setting
//
// @rdesc uint8_t value representing the EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_EST1C( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EST1C, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EST1C ) )

//=============================================================================
// VSEP_Msg_EST_Set_EDGE
//
// @func Set EST EDGE setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST EDGE
//    setting
//
// @parm uint8_t | edge | The new EST EDGE setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_EDGE( msg, edge )\
   (uint16_t)( Insert_Bits( msg, edge, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EDGE, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EDGE ) )

//=============================================================================
// VSEP_Msg_EST_Get_EDGE
//
// @func Get EST EDGE setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the EST EDGE
//    setting
//
// @rdesc uint8_t value representing the EST EDGE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_EDGE( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_EDGE, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_EDGE ) )

//=============================================================================
// VSEP_Msg_EST_Set_INDEX
//
// @func Set EST INDEX setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST INDEX
//    setting
//
// @parm uint8_t | index | The new EST INDEX setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST INDEX setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_INDEX( msg, index )\
   (uint16_t)( Insert_Bits( msg, index, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_INDEX, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_INDEX ) )

//=============================================================================
// VSEP_Msg_EST_Get_INDEX
//
// @func Get EST INDEX setting from the txd message
//
// @parm uint8_t | msg | The txd message element retrieve the EST INDEX
//    setting
//
// @rdesc uint8_t value representing the EST INDEX setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_INDEX( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_INDEX, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_INDEX ) )

//=============================================================================
// VSEP_Msg_EST_Set_PFMODE
//
// @func Set EST PFMODE setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST PFMODE
//    setting
//
// @parm uint8_t | pfmode | The new EST PFMODE setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST PFMODE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_PFMODE( msg, pfmode )\
   (uint16_t)( Insert_Bits( msg, pfmode, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_PFMODE, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_PFMODE ) )

//=============================================================================
// VSEP_Msg_EST_Get_PFMODE
//
// @func Get EST PFMODE setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the EST PFMODE
//    setting
//
// @rdesc uint8_t value representing the EST PFMODE setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_PFMODE( msg )\
   (uint16_t)( Extract_Bits( msg, VSEP_TXD_EST_CTRL_CONFIGURATION_POSITION_PFMODE, VSEP_TXD_EST_CTRL_CONFIGURATION_WIDTH_PFMODE ) )

///////////////////////////////////////////////////////////////////////////////
// ID - SETUP
// Base Offset: 38 H
// Reset Value: 0000 0000 H
//
// Field     Bits    Type  Description
// ========= ======= ====  =================================================
//
// M1_OHILOB     13
//                         0	Multi-purpose I/O #1 is configured with a current source 
//                            pull down.
//                	      1	Multi-purpose I/O #1 is configured with a current source 
//                            pull up.
//                         
// M1_OEN        12       
//                         0	Multi-purpose I/O #1 has no current sources active. 
//                            Able to be used as only a discrete input.
//                	      1	Multi-purpose I/O #1 has either the pull-up or pull-down 
//                            current sources enabled.
//                         
// M2_OHILOB	  11       
//                         0	Multi-purpose I/O #2 is configured with a current source 
//                            pull down.
//                	      1	Multi-purpose I/O #2 is configured with a current source 
//                            pull up.
//                         
// M2_OEN        10       
//                         0	Multi-purpose I/O #2 has no current sources active. 
//                            Able to be used as only a discrete input.
//                	      1	Multi-purpose I/O #2 has either the pull-up or pull-down 
//                            current sources enabled.
//                         
// M3_OHILOB	   9       
//                         0	Multi-purpose I/O #3 is configured with a current source 
//                            pull down.
//                	      1	Multi-purpose I/O #3 is configured with a current source 
//                            pull up.
//                         
// M3_OEN         8       
//                         0	Multi-purpose I/O #3 has no current sources active. 
//                            Able to be used as only a discrete input.
//                	      1	Multi-purpose I/O #3 has either the pull-up or pull-down 
//                            current sources enabled.
//
// CRDISARM       5
//                         0	The ETC SOH Logic will remain enabled.
//                         1	The ETC SOH logic will be disabled if the proper 
//                            sequence is followed.
//
// IGBTCFG        4
//                         0  Ignitition output faults set for driving EST inputs.
//                         1  Ignitition output faults set for driving IGBT's.
//
// DEC_DISB       3
//                         0	Ignitition outputs controlled by discrete inputs.
//                         1	Ignitition outputs controlled by internal decode logic.
//
// CYLCNT    [ 2: 0]
//                         CYLCNT   CYLCNT   Configuration of Outputs 
//                         SDI      SDO      PCH[1] - PCH[8] & PCH[9] - [12]
//                         =====    ======   ==================================
//                         000	   111(8)   - Invalid Value.  
//                                           - PCH[1] - PCH[8] outputs configured 
//                                             for use as ignition outputs.
//                                           - PCH[9] - PCH[12] configured for 
//                                             use as fuel injector outputs.  
//                                           - FSE_Enable will disable all of the 
//                                             above inputs if a valid low.
//
//                         001	   111(8)	- Invalid Value.  
//                                           - PCH[1] - PCH[8] outputs configured 
//                                             for use as ignition outputs.
//                                           - PCH[9] - PCH[12] configured for use 
//                                             as fuel injector outputs.  
//                                           - FSE_Enable will disable all of the 
//                                             above inputs if a valid low.
//
//                         010	   010(3)	- PCH[1] - PCH[3] outputs configured 
//                                             for use as ignition outputs.
//                                           - PCH[9] - PCH[11] configured for use 
//                                             as fuel injector outputs.  
//                                           - PCH[4] - PCH[8] & PCH[12] configured 
//                                             for use as generic gate drive outputs.
//                                           - FSE_Enable will not affect any of the 
//                                             generic gate drive outputs.
//
//                         011	   011(4)	- PCH[1] - PCH[4] outputs configured 
//                                             for use as ignition outputs.
//                                           - PCH[9] - PCH[12] configured for use 
//                                             as fuel injector outputs.  
//                                           - PCH[5] - PCH[8] configured for use 
//                                             as generic gate drive outputs.
//                                           - FSE_Enable will not affect any of 
//                                             the generic gate drive outputs.
//
//                         100	   100(5)	- PCH[1] - PCH[5] outputs configured
//                                             for use as ignition outputs.
//                                           - PCH[9] - PCH[12] & PCH[7] configured
//                                             for use as fuel injector outputs.  
//                                           - PCH[6] - PCH[8] configured for use 
//                                             as generic gate drive outputs.
//                                           - FSE_Enable will not affect any of 
//                                             the generic gate drive outputs.
//
//                         101	   101(6)	- PCH[1] - PCH[6] outputs configured
//                                             for use as ignition outputs.
//                                           - PCH[9] - PCH[12] & PCH[7] & PCH[8] 
//                                             configured for use as fuel injector 
//                                             outputs.  
//                                           - FSE_Enable will not affect any of 
//                                             the generic gate drive outputs.
// 
//                         110	   111(8)	- Invalid Value.  
//                                           - PCH[1] - PCH[8] outputs configured 
//                                             for use as ignition outputs.
//                                           - Outputs[13] - Outputs[16] configured 
//                                             for use as fuel injector outputs.  
//                                           - FSE_Enable will disable all of the 
//                                             above inputs if a valid low.
//
//                         111	   111(8)	- PCH[1] - PCH[8] outputs configured 
//                                             for use as ignition outputs.
//                                           - Outputs[13] - Outputs[16] configured 
//                                             for use as fuel injector outputs.  
//                                           - FSE_Enable will disable all of the 
//                                             above inputs if a valid low.
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   VSEP_TXD_SETUP_CONFIGURATION_POSITION_SOHRSTEN           =14,  //     14  SOHRSTEN
   VSEP_TXD_SETUP_CONFIGURATION_POSITION_M3_OHILOB_OEN      =12,  // [13:12] M3_OHILOB_OEN
      VSEP_TXD_SETUP_CONFIGURATION_POSITION_M3_OEN      =13,  // [13] M3_OHILOB_OEN
         VSEP_TXD_SETUP_CONFIGURATION_POSITION_M3_OHILOB      =12,  // [12] M3_OHILOB_OEN
   VSEP_TXD_SETUP_CONFIGURATION_POSITION_M2_OHILOB_OEN      =10,  // [11:10] M2_OHILOB_OEN
      VSEP_TXD_SETUP_CONFIGURATION_POSITION_M2_OEN      =11,  // [11] M2_OHILOB_OEN
         VSEP_TXD_SETUP_CONFIGURATION_POSITION_M2_OHILOB      =10,  // [10] M2_OHILOB_OEN
   VSEP_TXD_SETUP_CONFIGURATION_POSITION_M1_OHILOB_OEN      = 8,  // [ 9: 8] M1_OHILOB_OEN
      VSEP_TXD_SETUP_CONFIGURATION_POSITION_M1_OEN      = 9,  // [ 9] M1_OHILOB_OEN
         VSEP_TXD_SETUP_CONFIGURATION_POSITION_M1_OHILOB      = 8,  // [ 8] M1_OHILOB_OEN
   VSEP_TXD_SETUP_CONFIGURATION_POSITION_CRDISARM           = 5,  //      5  CRDISARM
   VSEP_TXD_SETUP_CONFIGURATION_POSITION_IGBTCFG            = 4,  //      4  IGBTCFG
   VSEP_TXD_SETUP_CONFIGURATION_POSITION_DEC_DISCB          = 3,  //      3  DEC_DISCB
   VSEP_TXD_SETUP_CONFIGURATION_POSITION_CYLCNT             = 0   // [ 2: 0] CYLCNT
}VSEP_TXD_EST_Cfg_Configuration_Position_T;

typedef enum
{
   VSEP_TXD_SETUP_CONFIGURATION_WIDTH_SOHRSTEN              = 1,  //     14  SOHRSTEN
   VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M3_OHILOB_OEN         = 2,  // [13:12] M3_OHILOB_OEN
      VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M3_OEN         = 1,  // [13:12] M3_OHILOB_OEN
         VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M3_OHILOB         = 1,  // [13:12] M3_OHILOB_OEN
   VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M2_OHILOB_OEN         = 2,  // [11:10] M2_OHILOB_OEN
      VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M2_OEN         = 1,  // [11:10] M2_OHILOB_OEN
         VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M2_OHILOB         = 1,  // [11:10] M2_OHILOB_OEN
   VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OHILOB_OEN         = 2,  // [ 9: 8] M1_OHILOB_OEN
      VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OEN         = 1,  // [ 9: 8] M1_OHILOB_OEN
         VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OHILOB         = 1,  // [ 9: 8] M1_OHILOB_OEN
   VSEP_TXD_SETUP_CONFIGURATION_WIDTH_CRDISARM              = 1,  //      5  CRDISARM
   VSEP_TXD_SETUP_CONFIGURATION_WIDTH_IGBTCFG               = 1,  //      4  IGBTCFG
   VSEP_TXD_SETUP_CONFIGURATION_WIDTH_DEC_DISCB             = 1,  //      3  DEC_DISCB
   VSEP_TXD_SETUP_CONFIGURATION_WIDTH_CYLCNT                = 3   // [ 2: 0] CYLCNT

}VSEP_TXD_EST_Cfg_Configuration_Width_T;                       

//=============================================================================
// VSEP_Msg_Set_SOHRSTEN
//
// @func Set SOHRSTEN in the txd message
//
// @parm uint16_t | msg | The txd message element in which the SOHRSTEN is 
//                         to be stored
//
// @parm uint8_t | SOHRSTEN | The desired SOHRSTEN setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    SOHRSTEN setting
//
// @end
//=============================================================================
#define VSEP_Msg_Set_SOHRSTEN( msg, sohrsten )\
   (uint16_t)( Insert_Bits( msg, sohrsten, VSEP_TXD_SETUP_CONFIGURATION_POSITION_SOHRSTEN, VSEP_TXD_SETUP_CONFIGURATION_WIDTH_SOHRSTEN ) )

//=============================================================================
// VSEP_Msg_Get_SOHRSTEN
//
// @func Get SOHRSTEN setting from the txd message
//
// @parm uint16_t | msg | The txd message element from which to retrieve the 
//                        SOHRSTEN setting
//
// @rdesc uint8_t value representing the SOHRSTEN setting
//
// @end
//=============================================================================
#define VSEP_Msg_Get_SOHRSTEN( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SETUP_CONFIGURATION_POSITION_SOHRSTEN, VSEP_TXD_SETUP_CONFIGURATION_WIDTH_SOHRSTEN ) )

//=============================================================================
// VSEP_Msg_MPIO_Get_Mx_OHILOB_OEN
//
// @func Set MPIO OHILOB and EN state to the MPIO txd message for the given channel
//
// @parm uint16_t | msg | The MPIO txd message element to store the OHILOB and 
//    EN state
//
// @parm uint8_t | channel | The channel to assign the MPIO OHILOB and EN 
//    state to.
// 
// @parm uint8_t | state | The MPIO OHILOB and EN state to assign to the channel
// 
// @rdesc uint16_t value representing the MPIO message element with the new 
//    OHILOB ane OEN state
//
// @end
//=============================================================================
#define VSEP_Msg_MPIO_Get_Mx_OHILOB_OEN( msg, channel )\
   (uint8_t)( Extract_Bits( msg, (VSEP_TXD_SETUP_CONFIGURATION_POSITION_M1_OHILOB_OEN + ( channel * VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OHILOB_OEN )), VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OHILOB_OEN ) )

//=============================================================================
// VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN
//
// @func Set MPIO OHILOB and EN state from the MPIO txd message for the given channel
//
// @parm uint16_t | msg | The MPIO txd message element to retrieve the OHILOB 
//    and EN state
//
// @parm uint8_t | channel | The channel to retrieve the MPIO state from.
//
// @rdesc uint8_t value representing the MPIO OHILOB and EN state
//
// @end
//=============================================================================
#define VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( msg, channel, input_mode )\
   (uint16_t)( Insert_Bits( msg, input_mode, (VSEP_TXD_SETUP_CONFIGURATION_POSITION_M1_OHILOB_OEN + ( channel * VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OHILOB_OEN ) ), VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OHILOB_OEN ) )

//=============================================================================
// VSEP_Msg_MPIO_Set_Mx_OHILOB
//
// @func Set MPIO OHILOB  state from the MPIO txd message for the given channel
//
// @parm uint16_t | msg | The MPIO txd message element to retrieve the OHILOB 
//    and EN state
//
// @parm uint8_t | channel | The channel to retrieve the MPIO state from.
//
// @rdesc uint8_t value representing the MPIO OHILOB and EN state
//
// @end
//=============================================================================
#define VSEP_Msg_MPIO_Set_Mx_OHILOB( msg, channel, input_mode )\
   (uint16_t)( Insert_Bits( msg, input_mode, (VSEP_TXD_SETUP_CONFIGURATION_POSITION_M1_OHILOB + ( channel * VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OHILOB_OEN ) ), VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OHILOB ) )

//=============================================================================
// VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN
//
// @func Set MPIO  EN state from the MPIO txd message for the given channel
//
// @parm uint16_t | msg | The MPIO txd message element to retrieve the OHILOB 
//    and EN state
//
// @parm uint8_t | channel | The channel to retrieve the MPIO state from.
//
// @rdesc uint8_t value representing the MPIO OHILOB and EN state
//
// @end
//=============================================================================
#define VSEP_Msg_MPIO_Set_Mx_OEN( msg, channel, input_mode )\
   (uint16_t)( Insert_Bits( msg, input_mode, (VSEP_TXD_SETUP_CONFIGURATION_POSITION_M1_OEN + ( channel * VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OHILOB_OEN ) ), VSEP_TXD_SETUP_CONFIGURATION_WIDTH_M1_OEN ) )


//=============================================================================
// VSEP_Msg_EST_Set_CYLCNT
//
// @func Set EST CYLCNT setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST CYLCNT
//    setting
//
// @parm uint8_t | cylcnt | The new EST CYLCNT setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST CYLCNT setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_CYLCNT( msg, cylcnt )\
   (uint16_t)( Insert_Bits( msg, cylcnt, VSEP_TXD_SETUP_CONFIGURATION_POSITION_CYLCNT, VSEP_TXD_SETUP_CONFIGURATION_WIDTH_CYLCNT ) )

//=============================================================================
// VSEP_Msg_EST_Get_CYLCNT
//
// @func Get EST CYLCNT setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the EST CYLCNT
//    setting
//
// @rdesc uint8_t value representing the EST CYLCNT setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_CYLCNT( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SETUP_CONFIGURATION_POSITION_CYLCNT, VSEP_TXD_SETUP_CONFIGURATION_WIDTH_CYLCNT ) )

//=============================================================================
// VSEP_Msg_EST_Set_DEC_DISCB
//
// @func Set EST DEC_DISCB setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST DEC_DISCB
//    setting
//
// @parm uint8_t | dec_discb | The new EST DEC_DISCB setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST DEC_DISCB setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_DEC_DISCB( msg, dec_discb )\
   (uint16_t)( Insert_Bits( msg, dec_discb, VSEP_TXD_SETUP_CONFIGURATION_POSITION_DEC_DISCB, VSEP_TXD_SETUP_CONFIGURATION_WIDTH_DEC_DISCB ) )

//=============================================================================
// VSEP_Msg_EST_Get_DEC_DISCB
//
// @func Get EST DEC_DISCB setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the EST DEC_DISCB
//    setting
//
// @rdesc uint8_t value representing the EST DEC_DISCB setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_DEC_DISCB( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SETUP_CONFIGURATION_POSITION_DEC_DISCB, VSEP_TXD_SETUP_CONFIGURATION_WIDTH_DEC_DISCB ) )

//=============================================================================
// VSEP_Msg_EST_Set_IGBTCFG
//
// @func Set EST IGBTCFG setting from the txd message
//
// @parm uint16_t | msg | The txd message element store the EST IGBTCFG
//    setting
//
// @parm uint8_t | igbtcfg | The new EST IGBTCFG setting.
// 
// @rdesc uint16_t value representing the EST CFG message element with the new 
//    EST IGBTCFG setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Set_IGBTCFG( msg, igbtcfg )\
   (uint16_t)( Insert_Bits( msg, igbtcfg, VSEP_TXD_SETUP_CONFIGURATION_POSITION_IGBTCFG, VSEP_TXD_SETUP_CONFIGURATION_WIDTH_IGBTCFG ) )

//=============================================================================
// VSEP_Msg_EST_Get_IGBTCFG
//
// @func Get EST IGBTCFG setting from the txd message
//
// @parm uint16_t | msg | The txd message element retrieve the EST IGBTCFG
//    setting
//
// @rdesc uint8_t value representing the EST IGBTCFG setting
//
// @end
//=============================================================================
#define VSEP_Msg_EST_Get_IGBTCFG( msg )\
   (uint8_t)( Extract_Bits( msg, VSEP_TXD_SETUP_CONFIGURATION_POSITION_IGBTCFG, VSEP_TXD_SETUP_CONFIGURATION_WIDTH_IGBTCFG ) )

#endif // DD_VSEP_TXD_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

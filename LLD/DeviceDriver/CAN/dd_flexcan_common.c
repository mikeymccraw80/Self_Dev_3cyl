//=============================================================================
//
//       COPYRIGHT, 2005, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_flexcan_common.c~ctc_pt3#12:csrc:kok_toy#2 %
//
// created_by:       gzdmlz
//
// date_created:     Fri Jan 13 22:58:26 2006
//
// %derived_by:      zzrfyj %
//
// %date_modified:    %
//
// %version:         ctc_pt3#12 %
//
//=============================================================================
#include "dd_flexcan.h"
#include "dd_flexcan_interrupt.h"

typedef union {
   volatile unsigned int R;
   struct {
      volatile unsigned int:14;
      volatile unsigned int TWRNINT:1;
      volatile unsigned int RWRNINT:1;
      volatile unsigned int BIT1ERR:1;
      volatile unsigned int BIT0ERR:1;
      volatile unsigned int ACKERR:1;
      volatile unsigned int CRCERR:1;
      volatile unsigned int FRMERR:1;
      volatile unsigned int STFERR:1;
      volatile unsigned int TXWRN:1;
      volatile unsigned int RXWRN:1;
      volatile unsigned int IDLE:1;
      volatile unsigned int TXRX:1;
      volatile unsigned int FLTCONF:2;
      volatile unsigned int:1;
      volatile unsigned int BOFFINT:1;
      volatile unsigned int ERRINT:1;
      volatile unsigned int:1;
      } B;
} CAN_ESR_T;

/*  Local Definitions */

#define NUMBER_OF_MESSAGE_OBJECTS  64U
#define NUMBER_OF_DATA_BYTES        8U
/* CAN Bus Timing Definitions */

/* A CAN bit is made up of a number of time quanta ( tq ). The period of  */
/* one tq is defined by the S-clock which is derived from f-SYS.          */
/* Having decided the number of tq in a bit, the actual bit rate is       */
/* controlled by the S-clock pre-scaler PRESDIV.                          */

/* 128 MHz system clock CAN bit timing */
/* At this frequency CAN bit will be made up of 16 time quanta ( tq ) as    */
/* follows:                                                                 */
/* Sync Segment              = 1 tq                                         */
/* Propagation Time Segment  = 5 tq  ( PROPSEG + 1 )                        */
/* Phase Buffer Segment 1    = 5 tq  ( PSEG1   + 1 )                        */
/* Phase Buffer Segment 2    = 5 tq  ( PSEG2   + 1 )                        */
/* This set up correspond to a valid configuration as per table 21-17 in the*/
/* MPC5554 Ref Manual Rev1.1                                                */
#define CAN_TQUANTA_PER_BIT (16)
#define CAN_SYNC_TQ (1-1) /* always 1 time quantum for the sync phase */
#define CAN_PROPSEG_TQ (5-1)
#define CAN_PSEG1_TQ (5-1)
#define CAN_PSEG2_TQ (5-1)

#if 0
#define CAN_PRESDIV_1MHz (((HWI_SYSTEM_FREQ_IN_HZ/CAN_TQUANTA_PER_BIT)/ \
                            1000000) - 1)
#define CAN_PRESDIV_500kHz (((HWI_SYSTEM_FREQ_IN_HZ/CAN_TQUANTA_PER_BIT)/ \
                              500000) - 1)
#define CAN_PRESDIV_250kHz (((HWI_SYSTEM_FREQ_IN_HZ/CAN_TQUANTA_PER_BIT)/ \
                              250000) - 1)
#define CAN_PRESDIV_125kHz (((HWI_SYSTEM_FREQ_IN_HZ/CAN_TQUANTA_PER_BIT)/ \
                              125000) - 1)

#define CANCR_LOW   (U16)(0xA000 | CAN_PROPSEG_TQ)
                                     /* Bus off interrupt enabled           */
                                     /* Error interrupt disabled            */
                                     /* Clock source is bus clock           */
                                     /* Loop back mode disabled             */
                                     /* Single sample point                 */
                                     /* bus off automatic recovery on       */
                                     /* Timer synchronization disabled      */
                                     /* Lowest message ID transmitted first */
                                     /* PROPSEG                             */

                                     /* Receive pin - 0 = dominant bit      */
                                     /* Transmit pin - 0 = dominant bit     */

#define CANCR_1MHz   (U32)(CAN_PRESDIV_1MHz << 24 |\
                           CAN_SYNC_TQ << 22 |\
                           CAN_PSEG1_TQ << 19 |\
                           CAN_PSEG2_TQ << 16 |\
                           CANCR_LOW)
#define CANCR_500kHz (U32)(CAN_PRESDIV_500kHz << 24 |\
                           CAN_SYNC_TQ << 22 |\
                           CAN_PSEG1_TQ << 19 |\
                           CAN_PSEG2_TQ << 16 |\
                           CANCR_LOW)
#define CANCR_250kHz (U32)(CAN_PRESDIV_250kHz << 24 |\
                           CAN_SYNC_TQ << 22 |\
                           CAN_PSEG1_TQ << 19 |\
                           CAN_PSEG2_TQ << 16 |\
                           CANCR_LOW)
#define CANCR_125kHz (U32)(CAN_PRESDIV_125kHz << 24 |\
                           CAN_SYNC_TQ << 22 |\
                           CAN_PSEG1_TQ << 19 |\
                           CAN_PSEG2_TQ << 16 |\
                           CANCR_LOW)
#endif

/* CAN Control Register Masks */

#define SET_MESSAGE_BUFFER_INACTIVE (uint32_t)0x007FFFFF
#define CANMCR_DEF                  (uint32_t)0x9000003F /* FRZ     - Enter debug mode disabled  */
                                                     /* HALT    - Start module running       */
                                                     /* MDIS    - module disabled            */
                                                     /* MAXMB - 64 message buffers           */
#define CAN_MODULE_READY            (uint32_t)0x0000003F  /* MAXMB - 64 message buffers           */

/*  Data Definitions */

/* The CAN registers and message objects, for both CAN devices, need */
/* to be mapped onto physical registers                              */


#define EXTEND_ID               0x1U
#define CAN_TRANSMIT_MESSAGE    (uint16_t)0x8
#define CAN_TRANSMIT_EMPTY      (uint32_t)0x8
#define TRANSMIT_CAN_MESSAGE    (uint32_t)0xC
#define CAN_RECEIVE_NOT_ACTIVE  (uint32_t)0x00
#define CAN_RECEIVE_EMPTY       (uint16_t)0x4
#define CAN_RECEIVE_BUSY        (uint16_t)0x10
#define CAN_RX_BUFFER_BUSY      (uint32_t)1

static uint16_t first_time_init[MAX_CAN_DEVICES] = {(uint16_t)true,
                                               (uint16_t)true,
#ifdef P_L_CAN2
                                               (uint16_t)true,
#endif
#ifdef P_L_CAN3
                                               (uint16_t)true,
#endif
                                               };
static uint16_t first_time_object_init[NUMBER_OF_MESSAGE_OBJECTS][MAX_CAN_DEVICES];
static uint8_t  can_error_int_init_done[MAX_CAN_DEVICES] = {0};
static uint8_t  can_error_reenable_cntr[MAX_CAN_DEVICES] = {0};
static uint64_t can_buffer_direction[MAX_CAN_DEVICES] = {0};
static BOOL_TYPE hwi_can_a_error_seen;
static BOOL_TYPE hwi_can_b_error_seen;
#ifdef P_L_CAN2
static BOOL_TYPE hwi_can_c_error_seen;
#endif
#ifdef P_L_CAN3
static BOOL_TYPE hwi_can_d_error_seen;
#endif
static CAN_ESR_T hwi_can_stferror[4];

//=============================================================================
// FlexCAN_Initialize_Message_Buffer
//=============================================================================
void FlexCAN_Initialize_Message_Object(
   IO_Configuration_T in_configuration, 
   uint32_t                 message_id)
{
   FlexCAN_MSGOBJ_INDEX_T msg_obj = FlexCAN_MSGOBJ_Get_Index(in_configuration);
   FLEXCAN_T*             pFlexCAN= FlexCAN_Get_Device( in_configuration );
   bool interrupt_state = FlexCAN_MSGOBJ_Get_Interrupt(in_configuration);

   pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.IDE    = FlexCAN_MSGOBJ_Get_ID_Length(in_configuration);
   pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.LENGTH = FlexCAN_MSGOBJ_Get_Data_Length(in_configuration);
   pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.RTR    = FlexCAN_MSGOBJ_Get_RTR(in_configuration);
   pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.SRR    = FlexCAN_MSGOBJ_Get_SRR(in_configuration);
   //Clear Message Buffer
   pFlexCAN->MSGBUF[msg_obj].F.DATA.U32[0] = 0;
   pFlexCAN->MSGBUF[msg_obj].F.DATA.U32[1] = 0;
   FLEXCAN_Set_Msg_ID(pFlexCAN, msg_obj, message_id);
   
   if(FlexCAN_MSGOBJ_Get_Direction(in_configuration) == FLEXCAN_MSGOBJ_DIR_TX)
   {
      pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_TX_INACTIVE;
   }
   else
   {
      pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_RX_EMPTY;
   }

   // FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(in_configuration, interrupt_state);
   FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(pFlexCAN, msg_obj, interrupt_state);

}

//=============================================================================
//  FLEXCAN_Get_Free_Running_Timer
//============================================================================
uint16_t FLEXCAN_Get_Free_Running_Timer(
   const FLEXCAN_T* in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T  in_msgobj)
{
   return ((uint16_t)(in_pFlexCAN->TIMER));
}
//=============================================================================
//  FLEXCAN_MSGOBJ_Configure_For_Transmit
//============================================================================
void FLEXCAN_MSGOBJ_Configure_For_Transmit(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj)
{
   in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_TX_INACTIVE; 
}
//=============================================================================
//  FLEXCAN_MSGOBJ_ConfigureForRecieve
//============================================================================
void FLEXCAN_MSGOBJ_Configure_For_Recieve(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj)
{
   in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_RX_INACTIVE;
}
//=============================================================================
//  FLEXCAN_MSGOBJ_Write_Data
//============================================================================
void FLEXCAN_MSGOBJ_Write_Data(
   FLEXCAN_T *                  in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T       in_msgobj,
   const uint8_t *              in_buffer,
   FlexCAN_MSGOBJ_Data_Length_T in_length)
{
   uint8_t data_index;
   for (data_index = 0; data_index < in_length; data_index++)
   {
      in_pFlexCAN->MSGBUF[in_msgobj].F.DATA.U8[data_index]= in_buffer[data_index];
   }
}
//=============================================================================
//  FLEXCAN_MSGOBJ_Get_Data
//============================================================================
void FLEXCAN_MSGOBJ_Get_Data(
   const FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj,
   uint8_t *              in_buffer,
   uint8_t                in_length)
{
   uint8_t data_index;               
   for (data_index = 0; data_index < in_length; data_index++)
   {
      in_buffer[data_index] = in_pFlexCAN->MSGBUF[in_msgobj].F.DATA.U8[data_index];
   }
}
//=============================================================================
//  FlexCAN_MSGOBJ_Get_Interrupt_Direction
//============================================================================
FlexCAN_MSGOBJ_DIR_T FlexCAN_Interrupt_Get_Direction(
   IO_Configuration_T in_configuration )
{
   FlexCAN_MSGOBJ_DIR_T direction;
   FlexCAN_MSGOBJ_INDEX_T msg_obj = FlexCAN_MSGOBJ_Get_Index(in_configuration);
   FLEXCAN_T *            pFlexCAN    = FlexCAN_Get_Device( in_configuration );
   FlexCAN_Msg_Code_T     message_code;

   message_code = (FlexCAN_Msg_Code_T)pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE; 

   if( (message_code == FLEXCAN_MSGOBJ_TX_INACTIVE) ||
       (message_code == FLEXCAN_MSGOBJ_TX_REMOTE) ||
       (message_code == FLEXCAN_MSGOBJ_TX_UNCONDITIONAL) ||
       (message_code == FLEXCAN_MSGOBJ_TX_REMOTE_MATCH)
     )
   {
      direction = FLEXCAN_MSGOBJ_DIR_TX;
   }
   else
   {
      direction = FLEXCAN_MSGOBJ_DIR_RX;
   }
       
   return direction;
}
//=============================================================================
// FLEXCAN_Set_Bit_Rate
//=============================================================================
void FLEXCAN_Set_Bit_Rate(
   FLEXCAN_T *      in_pFlexCAN,
   uint8_t          in_time_quanta,
   uint32_t         in_bit_rate)
{
   uint8_t prescale_div = 
           (uint8_t)((FLEXCAN_FREQUENCY_HZ / (in_time_quanta * in_bit_rate)) - 1);
   in_pFlexCAN->CR.F.PRESDIV = prescale_div;
}
//=============================================================================
// FLEXCAN_Get_Msg_ID
//=============================================================================
uint32_t FLEXCAN_Get_Msg_ID(
   const FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj)
{
   uint32_t  msg_id;
   if (FLEXCAN_MSGOBJ_ID_STD == in_pFlexCAN->MSGBUF[in_msgobj].F.CTRSTS.F.IDE)
   {
      msg_id = in_pFlexCAN->MSGBUF[in_msgobj].F.ID.U32 >> FLEXCAN_STD_ID_SHIFT;
   }
   else
   {
      msg_id = in_pFlexCAN->MSGBUF[in_msgobj].F.ID.U32;
   }
   return(msg_id);
}
//=============================================================================
// FLEXCAN_Set_Msg_ID
//=============================================================================
void FLEXCAN_Set_Msg_ID(
   FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj,
   uint32_t in_message_id)
{
   uint32_t  msg_id;
   if (FLEXCAN_MSGOBJ_ID_STD == in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.IDE)
   {
      in_pFlexCAN->MSGBUF[in_msg_obj].F.ID.F.STD_EXT = in_message_id;
      in_pFlexCAN->MSGBUF[in_msg_obj].F.ID.F.EXTENDED = 0;
   }
   else
   {
      in_pFlexCAN->MSGBUF[in_msg_obj].F.ID.U32 = in_message_id;
   }
}
//=============================================================================
// FLEXCAN_Set_Individual_Ext_Mask
//=============================================================================
void FLEXCAN_Set_Individual_Ext_Mask(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj,
   uint32_t               in_msg_mask)
{
   
   if (in_msgobj == FLEXCAN_MSG_OBJ_14)
   {
      in_pFlexCAN->RX14MASK.U32 = in_msg_mask;
   }
   else if (in_msgobj == FLEXCAN_MSG_OBJ_15)
   {
      in_pFlexCAN->RX15MASK.U32 = in_msg_mask;
   }
   else
   {
      // Do nothing
   }
}

//=============================================================================
// FLEXCAN_Set_Global_Ext_Mask
//=============================================================================
void FLEXCAN_Set_Global_Ext_Mask(
   FLEXCAN_T *            in_pFlexCAN,
   uint32_t               in_msg_mask)
{
   in_pFlexCAN->RXGMASK.U32 = in_msg_mask;
}

//=============================================================================
//  FLEXCAN_MSGOBJ_Get_Status
//============================================================================
FlexCAN_Msg_Code_T FLEXCAN_MSGOBJ_Get_Status(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj)
{
   return (FlexCAN_Msg_Code_T) (in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.CODE);
}

//=============================================================================
//  FLEXCAN_MSGOBJ_Get_Message_Length
//============================================================================
uint8_t FLEXCAN_MSGOBJ_Get_Message_Length(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj)
{
   return (uint8_t)(in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.LENGTH);
}

//=============================================================================
//  FLEXCAN_MSGOBJ_Set_Message_Length
//============================================================================
void FLEXCAN_MSGOBJ_Set_Message_Length(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj,
   uint8_t in_data_length)
{
   in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.LENGTH = in_data_length;
}


//=============================================================================
//  FLEXCAN_Unlock_Message_Buffer
//============================================================================
FLEXCAN_TIMER_T FLEXCAN_Unlock_Message_Buffer(
   FLEXCAN_T* in_pFlexCAN)
{
   return in_pFlexCAN->TIMER;
}

//=============================================================================
//  FLEXCAN_Enable_Communication
//============================================================================
void FLEXCAN_Enable_Communication(
   FLEXCAN_T* in_pFlexCAN)
{
   in_pFlexCAN->MCR.F.HALT = 0;
}

//=============================================================================
//  FLEXCAN_Disable_Communication
//============================================================================
void FLEXCAN_Disable_Communication(
   FLEXCAN_T* in_pFlexCAN)
{
   in_pFlexCAN->MCR.F.HALT = 1;
}

//=============================================================================
//  FLEXCAN_Get_Device_Freeze_Status
//============================================================================
bool FLEXCAN_Get_Device_Freeze_Status(
   FLEXCAN_T  *in_pFlexCAN)
{
   return((bool)(in_pFlexCAN->MCR.F.FRZACK));
}

//=============================================================================
// FlexCAN_Set_Device_Soft_Reset
//=============================================================================
void FlexCAN_Set_Device_Soft_Reset(
   IO_Configuration_T in_configuration)
{
   // Get the device address
   FLEXCAN_T              *pFlexCAN  = FlexCAN_Get_Device( in_configuration );

   // Set the SOFTRST bit
   pFlexCAN->MCR.F.SOFTRST = 1;
}

//=============================================================================
//  FLEXCAN_Get_Device_Soft_Reset_Status
//============================================================================
bool FLEXCAN_Get_Device_Soft_Reset_Status(
   IO_Configuration_T in_configuration)
{
   // Get the device address
   FLEXCAN_T              *pFlexCAN  = FlexCAN_Get_Device( in_configuration );

   return((bool)(pFlexCAN->MCR.F.SOFTRST));
}

//=============================================================================
//  FlexCAN_Enable_Device
//============================================================================
void FlexCAN_Enable_Device(
   IO_Configuration_T in_configuration, 
   bool in_enable)
{
   FLEXCAN_T        *pFlexCAN    = FlexCAN_Get_Device( in_configuration );

   pFlexCAN->MCR.F.MDIS = ~(in_enable);
}

//=============================================================================
//  FlexCAN_Get_Device_Status
//============================================================================
bool FlexCAN_Get_Device_Status(
   IO_Configuration_T in_configuration)
{
   FLEXCAN_T        *pFlexCAN    = FlexCAN_Get_Device( in_configuration );

   return ((bool)(pFlexCAN->MCR.F.MDISACK));
}

/********************************************************************
Function   : hwi_can_configure_object
Description: This function is used to initialise a can object. 

*********************************************************************/
HWI_ERROR hwi_can_configure_object(const P_L_CAN_OBJECT_TYPE *p_l_can_object_ptr)
{
  int16_t can_device = p_l_can_object_ptr->P_L_CAN_DEVICE_NUMBER;
  uint16_t can_object_U16, can_object_mask;
  struct FLEXCAN2_tag *can_register_ptr=&CAN_A;
  uint32_t msgid;
  int16_t msg_length, direction;
  volatile uint32_t tempU32;
  uint32_t msg_mask;
  HWI_ERROR  error_status = HWI_NO_ERROR;
  //HWI_INTERRUPTSTATE_TYPE int_state;

  /* Select the appropriate CAN object set */
  switch (can_device)
    {
    case FLEXCAN_DEVICE_A:
      /* Point at CAN A register set and message object set */
      can_register_ptr = &CAN_A;
      break;

//    case P_L_CAN1:
      /* Point at CAN B register set and message object set */
//      can_register_ptr = &CAN_B;
//      break;

//#ifdef P_L_CAN2
//    case P_L_CAN2:
//      /* Point at CAN C register set and message object set */
//      can_register_ptr = &CAN_C;      
//      break;
//#endif

//#ifdef P_L_CAN3
//    case P_L_CAN3:
//      /* Point at CAN D register set and message object set */
//      can_register_ptr = &CAN_D;
//      break;
//#endif
    }

  can_object_U16 = (int16_t)p_l_can_object_ptr->P_L_CAN_MSG_NUMBER;
  
  /* Check for valid object length */
  msg_length = p_l_can_object_ptr->P_L_CAN_LENGTH;
  
  if((msg_length > (int16_t)8 ) || (msg_length < (int16_t)0 ))
    {
      msg_length=(int16_t)8;
    }
  
  /* Check for valid message identifier */
  msgid = p_l_can_object_ptr->P_L_CAN_MSG_ID; 
  
  /* Valid identifier - set up object   */
  /* Test to see if object is transmit or receive */
  direction = p_l_can_object_ptr->P_L_CAN_DIRECTION;
  
  
  if(P_L_CAN_TX == direction)
    {
      /* Memorize the buffer direction configuration */
      can_buffer_direction[can_device] |= (uint64_t)((uint64_t)1<<(uint64_t)(p_l_can_object_ptr->P_L_CAN_MSG_NUMBER));

      if ((first_time_object_init[can_object_U16][can_device] == false) ||
         ((uint32_t)can_register_ptr->BUF[can_object_U16].CS_.B.CODE == CAN_TRANSMIT_EMPTY))
        {
          /* Indicate that the object has been configured */
          first_time_object_init[can_object_U16][can_device] =true;
          /* Force CAN transmit inactive also load number of data bytes  */ 
         // int_state = hwi_disable_interrupts_savestate();
          can_register_ptr->BUF[can_object_U16].CS_.B.LENGTH = msg_length;
          can_register_ptr->BUF[can_object_U16].CS_.B.CODE = CAN_TRANSMIT_EMPTY;
          //hwi_restore_interrupts(int_state);
        }
      else
        {
          /* Was initialised before and the buffer is not empty */
          if (((P_L_CAN0 == can_device) && (hwi_can_a_error_seen == true)) ||
              ((P_L_CAN1 == can_device) && (hwi_can_b_error_seen == true))
#ifdef P_L_CAN2       
                                                                           ||
              ((P_L_CAN2 == can_device) && (hwi_can_c_error_seen == true))
#endif
#ifdef P_L_CAN3       
                                                                           ||
              ((P_L_CAN3 == can_device) && (hwi_can_d_error_seen == true))
#endif
              )
            {
              error_status = HWI_CAN_ERROR_SEEN;
            }
          else
            {
              error_status = HWI_CAN_BUFFER_FULL;
            }
        }
    }
  else
    {
      /* Memorize the buffer direction configuration */
      can_buffer_direction[can_device] &= (uint64_t)(~((uint64_t)1<<(uint64_t)(p_l_can_object_ptr->P_L_CAN_MSG_NUMBER)));

      /* Set first time flag to false - Not used for receive type */
      first_time_object_init[can_object_U16][can_device] = false;
      /* Receive CAN object - set receive inactive  */
      //int_state = hwi_disable_interrupts_savestate();
      can_register_ptr->BUF[can_object_U16].CS_.B.CODE = CAN_RECEIVE_NOT_ACTIVE;
      //hwi_restore_interrupts(int_state);
    }
  

  /* Make sure there's no error so far - ie buffer is not full!*/
  if(error_status == HWI_NO_ERROR)
    {
      /* No error - go ahead with object configuration */
      /* Configure message ID*/
      if(P_L_CAN_XTD == p_l_can_object_ptr->P_L_CAN_TYPE)
        {
          /*===============================*/
          /*===  P_L_CAN_XTD : 29 BITS  ===*/
          /*===============================*/
          /* Load extended identifier  */
         // int_state = hwi_disable_interrupts_savestate();
          can_register_ptr->BUF[can_object_U16].ID.R = msgid;
          can_register_ptr->BUF[can_object_U16].CS_.B.SRR = 1;
          can_register_ptr->BUF[can_object_U16].CS_.B.IDE = 1;
          can_register_ptr->BUF[can_object_U16].CS_.B.RTR = 0;
          //hwi_restore_interrupts(int_state);
        }
      else
        {
          /*===============================*/
          /*===  P_L_CAN_STD : 11 BITS  ===*/
          /*===============================*/
          /* Load standard identifier  */
         // int_state = hwi_disable_interrupts_savestate();
          can_register_ptr->BUF[can_object_U16].ID.R = msgid << 18;
          can_register_ptr->BUF[can_object_U16].CS_.B.SRR = 0;
          can_register_ptr->BUF[can_object_U16].CS_.B.IDE = 0;
          can_register_ptr->BUF[can_object_U16].CS_.B.RTR = 0;
          //hwi_restore_interrupts(int_state);
        }
      
      /* Configure Receive Message mask */
      if(direction != P_L_CAN_TX)
        {
          /* Configure message mask */
          msg_mask = p_l_can_object_ptr->P_L_CAN_MSG_MASK;
          if(P_L_CAN_XTD != p_l_can_object_ptr->P_L_CAN_TYPE)
            {
              /* Reformat standard identifier mask */
              msg_mask = msg_mask << 18;
            }

          if (p_l_can_object_ptr->P_L_CAN_MSG_NUMBER == 14)
            {
              can_register_ptr->RX14MASK.R = msg_mask;
            }
          else
            {
              if (p_l_can_object_ptr->P_L_CAN_MSG_NUMBER == 15)
                {
                  can_register_ptr->RX15MASK.R = msg_mask;
                }
              else
                {
                  can_register_ptr->RXGMASK.R = msg_mask;
                }
            }
        }         

      /* Set up callback interrupt mechanism if required */
      //int_state = hwi_disable_interrupts_savestate();

      /* the buffer control registers are organized in pairs of 32 bit registers */
      /* Reformat the buffer number to access the correct bit                    */
      can_object_mask = can_object_U16 % 32;
      if ((int16_t)true== p_l_can_object_ptr->P_L_CAN_CALLBACK_ENABLED)
        {
          if (can_object_U16 >= 32)
            {
              /* Clear any pending interrupt */
              can_register_ptr->IFRH.R = (uint32_t)(1 << can_object_mask);
              /* Enable interrupt for this CAN object  */
              can_register_ptr->IMRH.R |=  (uint32_t)(1 << can_object_mask);
            }
          else
            {
              /* Clear any pending interrupt */
              can_register_ptr->IFRL.R = (uint32_t)(1 << can_object_mask);
              /* Enable interrupt for this CAN object  */
              can_register_ptr->IMRL.R |=  (uint32_t)(1 << can_object_mask);
            }
        }
      else
        {
          if (can_object_U16 >= 32)
            {
              /* Disable interrupt for this CAN object  */
              can_register_ptr->IMRH.R &= (uint32_t)~(1 << can_object_mask);
              /* Clear any pending interrupt */
              can_register_ptr->IFRH.R = (uint32_t)(1 << can_object_mask);
            }
          else
            {
              /* Disable interrupt for this CAN object  */
              can_register_ptr->IMRL.R &= (uint32_t)~(1 << can_object_mask);
              /* Clear any pending interrupt */
              can_register_ptr->IFRL.R = (uint32_t)(1 << can_object_mask);
            }
        }
      //hwi_restore_interrupts(int_state);
      
      /* Make a receive CAN object active */
      if(direction != P_L_CAN_TX)
        {
          //int_state = hwi_disable_interrupts_savestate();
          can_register_ptr->BUF[can_object_U16].CS_.B.CODE = CAN_RECEIVE_EMPTY;
          /* Ensure that the CAN object is unlocked by reading the free running timer. */
          tempU32 = can_register_ptr->TIMER.R;
          //hwi_restore_interrupts(int_state);
        }
    }
  else
    {
      /* An error occured - Do not configure the object */
    }

  return(error_status);
}  /* End of hwi_can_configure_object */      

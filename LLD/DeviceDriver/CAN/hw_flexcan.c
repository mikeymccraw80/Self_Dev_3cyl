/*-------------------------------------------------------------------*/
/*                                                                   */
/*    Delphi Automotive Systems - Delco Electronics                  */
/*                                                                   */
/*                                                                   */
/* filename - hwi_flexcan.c                                              */
/*                                                                   */
/* purpose:                                                          */
/*   -  CAN subsystem c source code.                                 */
/*                                                                   */
/*   This file contains the hardware layer routines for              */
/*   the CAN Sub System. The MPC555 processor contains two           */
/*   independent CAN devices, these are referred to as CAN_A         */
/*   and CAN_B.                                                      */
/*                                                                   */
/* list of function(s):                                              */
/*                                                                   */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* Delphi Electronics & Safety                                       */
/* (c) Copyright Delphi Electronics & Safety 2004                    */
/* Origin:                                                           */
/*-------------------------------------------------------------------*/
/*  Include Header Files */
#include "dd_flexcan.h"
#include "dd_flexcan_common.h"
#include "io_config_flexcan.h"
#include "j1939_communication_manager.h"

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



/* CAN Control Register Masks */

#define SET_MESSAGE_BUFFER_INACTIVE (U32)0x007FFFFF
#define CANMCR_DEF                  (U32)0x9000003F /* FRZ     - Enter debug mode disabled  */
                                                     /* HALT    - Start module running       */
                                                     /* MDIS    - module disabled            */
                                                     /* MAXMB - 64 message buffers           */
#define CAN_MODULE_READY            (U32)0x0000003F  /* MAXMB - 64 message buffers           */

/*  Data Definitions */

/* The CAN registers and message objects, for both CAN devices, need */
/* to be mapped onto physical registers                              */

#endif
#define EXTEND_ID               0x1U
#define CAN_TRANSMIT_MESSAGE    (uint16_t)0x8
#define CAN_TRANSMIT_EMPTY      (uint32_t)0x8
#define TRANSMIT_CAN_MESSAGE    (uint32_t)0xC
#define CAN_RECEIVE_NOT_ACTIVE  (uint32_t)0x00
#define CAN_RECEIVE_EMPTY       (uint16_t)0x4
#define CAN_RECEIVE_BUSY        (uint16_t)0x10
#define CAN_RX_BUFFER_BUSY      (uint32_t)1


static uint16_t first_time_object_init[NUMBER_OF_MESSAGE_OBJECTS][MAX_CAN_DEVICES];
static uint8_t  can_error_int_init_done[MAX_CAN_DEVICES] = {0};
static uint8_t  can_error_reenable_cntr[MAX_CAN_DEVICES] = {0};
static uint64_t can_buffer_direction[MAX_CAN_DEVICES] = {0};
static BOOL_TYPE hwi_can_a_error_seen=false;

static CAN_ESR_T hwi_can_stferror[4];

/*  Local Function Declarations  */

static void hwi_action_can_a_rcvd_callback(int16_t can_object,
                                           uint32_t p_l_can_msg_id, uint8_t *p_l_can_data_ptr,
                                           uint32_t p_l_can_msg_timestamp,
                                           uint8_t  p_l_can_msg_dlc);

static void hwi_action_can_a_xmit_callback(int16_t can_object,
                                           uint32_t p_l_can_msg_id,
                                           uint32_t p_l_can_msg_timestamp);

/********************************************************************
Function   : hwi_can_init
Description: This function is used the initialise the CAN devices. 
In MT22.3 app, CAN init was done in the UDS CAN ini.

*********************************************************************/

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
  HWI_INTERRUPTSTATE_TYPE int_state;

  /* Select the appropriate CAN object set */
  switch (can_device)
    {
    case FLEXCAN_DEVICE_A:
      /* Point at CAN A register set and message object set */
      can_register_ptr = &CAN_A;
      break;

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
          int_state = hwi_disable_interrupts_savestate();
          can_register_ptr->BUF[can_object_U16].CS_.B.LENGTH = msg_length;
          can_register_ptr->BUF[can_object_U16].CS_.B.CODE = CAN_TRANSMIT_EMPTY;
          hwi_restore_interrupts(int_state);
        }
      else
        {
          /* Was initialised before and the buffer is not empty */
          if ((P_L_CAN0 == can_device) && (hwi_can_a_error_seen == true))
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
      int_state = hwi_disable_interrupts_savestate();
      can_register_ptr->BUF[can_object_U16].CS_.B.CODE = CAN_RECEIVE_NOT_ACTIVE;
      hwi_restore_interrupts(int_state);
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
          int_state = hwi_disable_interrupts_savestate();
          can_register_ptr->BUF[can_object_U16].ID.R = msgid;
          can_register_ptr->BUF[can_object_U16].CS_.B.SRR = 1;
          can_register_ptr->BUF[can_object_U16].CS_.B.IDE = 1;
          can_register_ptr->BUF[can_object_U16].CS_.B.RTR = 0;
          hwi_restore_interrupts(int_state);
        }
      else
        {
          /*===============================*/
          /*===  P_L_CAN_STD : 11 BITS  ===*/
          /*===============================*/
          /* Load standard identifier  */
          int_state = hwi_disable_interrupts_savestate();
          can_register_ptr->BUF[can_object_U16].ID.R = msgid << 18;
          can_register_ptr->BUF[can_object_U16].CS_.B.SRR = 0;
          can_register_ptr->BUF[can_object_U16].CS_.B.IDE = 0;
          can_register_ptr->BUF[can_object_U16].CS_.B.RTR = 0;
          hwi_restore_interrupts(int_state);
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
      int_state = hwi_disable_interrupts_savestate();

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
      hwi_restore_interrupts(int_state);
      
      /* Make a receive CAN object active */
      if(direction != P_L_CAN_TX)
        {
          int_state = hwi_disable_interrupts_savestate();
          can_register_ptr->BUF[can_object_U16].CS_.B.CODE = CAN_RECEIVE_EMPTY;
          /* Ensure that the CAN object is unlocked by reading the free running timer. */
          tempU32 = can_register_ptr->TIMER.R;
          hwi_restore_interrupts(int_state);
        }
    }
  else
    {
      /* An error occured - Do not configure the object */
    }

  return(error_status);
}  /* End of hwi_can_configure_object */  


/********************************************************************
Function   : hwi_can_enble_gateway_open_ack
Description: This function re-initialises the can KWP object after 
             the CAN gateway has been opened to allow an ACK to be
             send. 
*********************************************************************/

/********************************************************************
Function   : hwi_can_re_init_link_ctrl_can
Description: This function re-initialises the can objects used by the
             CAN gateway. 

*********************************************************************/

/********************************************************************
Function   : hwi_can_receive_message
Description: This function checks to see if a new message has arrived.
             if so, and the callback for the receive object has been
             disabled, then the associated callback function is called.
             If the callback is enabled then this function takes no 
             action as the callback would have been triggered
             automatically. 

*********************************************************************/
      

/********************************************************************
Function   : hwi_can_send_message
Description: This function transmits a message from the specified CAN 
             object. 

*********************************************************************/


/********************************************************************
Function   : hwi_can_a_bus_off_isr
Description: This function processes the CAN A bus off interrupts.

*********************************************************************/

/********************************************************************
Function   : hwi_can_a_bus_off_isr
Description: This function processes the CAN A bus off interrupts.

*********************************************************************/

/********************************************************************
Function   : hwi_can_device_a_isr
Description: This function processes the CAN device 0 interrupts.

*********************************************************************/
void hwi_can_device_a_isr(void)
{
  uint64_t can_interrupt_status;
  uint64_t callback_mask = 1;
  uint64_t temp_int_flag;
  uint64_t temp_int_mask;
  int16_t can_object = 0;
  volatile uint32_t tempu32;
  uint32_t delay_count = 0;
  uint32_t can_msg_id;
  uint32_t message_data_buffer[2];
  //uint32_t p_l_can_msg_timestamp = (uint32_t)HWI_HTIME2; /* 1 usec resolution */
  uint32_t p_l_can_msg_timestamp = (uint32_t)0; /* this parameter was usless in this app */
  struct FLEXCAN2_tag *can_register_ptr = &CAN_A;
  HWI_INTERRUPTSTATE_TYPE int_state;
#ifdef APPLICATION
  BOOL_TYPE cangw_excp_msg;
#endif
  uint8_t  can_msg_dlc;

  temp_int_flag = (((uint64_t)(can_register_ptr->IFRH.R) << 32) | (uint64_t)(can_register_ptr->IFRL.R));
  temp_int_mask = (((uint64_t)(can_register_ptr->IMRH.R) << 32) | (uint64_t)(can_register_ptr->IMRL.R));
  can_interrupt_status = temp_int_flag & temp_int_mask;

  /* Clear down interrupt flag */
  can_register_ptr->IFRH.R = (uint32_t)(temp_int_flag >> 32);
  can_register_ptr->IFRL.R = (uint32_t)(temp_int_flag);

  /* Process interrupts */
  while (can_interrupt_status != 0)
    {
    
      if((can_interrupt_status & callback_mask) != (uint64_t)0)
        {
          /* Get message id */
          can_msg_id = can_register_ptr->BUF[can_object].ID.R;
          if (can_register_ptr->BUF[can_object].CS_.B.IDE != EXTEND_ID)
            {
              can_msg_id = can_msg_id >> 18;
            }


          if ((can_buffer_direction[P_L_CAN0] & callback_mask) != (uint64_t)0)
            {
                             /* Xmit buffer interrupt */
                hwi_action_can_a_xmit_callback(can_object, can_msg_id,
                                               p_l_can_msg_timestamp);
            }
          
          else
            {
              /* Lock receive object by reading the control/status register */
              /* If CAN buffer is busy wait until available */
              while ((can_register_ptr->BUF[can_object].CS_.B.CODE & CAN_RX_BUFFER_BUSY) 
                     && (delay_count < 100))
                {
                  delay_count++;
                }
              
              /* Set CAN object inactive */
              int_state = hwi_disable_interrupts_savestate();
              can_register_ptr->BUF[can_object].CS_.B.CODE = CAN_RECEIVE_NOT_ACTIVE;
              
              /* Bufferize message data */
              message_data_buffer[0] = can_register_ptr->BUF[can_object].DATA.W[0];
              message_data_buffer[1] = can_register_ptr->BUF[can_object].DATA.W[1];
              can_msg_dlc = can_register_ptr->BUF[can_object].CS_.B.LENGTH;
              /* Make receive CAN object active */
              can_register_ptr->BUF[can_object].CS_.B.CODE = CAN_RECEIVE_EMPTY;
              
              hwi_restore_interrupts(int_state);
              /* Read free running timer to unlock receive object */
              tempu32 = can_register_ptr->TIMER.R;
              
                  /*  invoke callback */
                  hwi_action_can_a_rcvd_callback(can_object, can_msg_id,
                                                 (uint8_t *) &(message_data_buffer[0]),
                                                 p_l_can_msg_timestamp,
                                                 can_msg_dlc);
            }
          /* Clear request flag */
          can_interrupt_status = can_interrupt_status & (~callback_mask);
        }

      /* Look at the next can object */
      can_object++;
      callback_mask = callback_mask << 1;
      delay_count = 0;
    }
}


/********************************************************************
Function   : hwi_can_error_int_reenable_
Description: This function reenables the CAN error interrupt after
             a certain delay

*********************************************************************/
#if 0 
void hwi_can_error_int_reenable(void)
{
  if (can_error_reenable_cntr[P_L_CAN0] != 0)
    {
      can_error_reenable_cntr[P_L_CAN0]--;
      if (can_error_reenable_cntr[P_L_CAN0] == 0)
        {
          CAN_A.CR.B.ERRMSK = 1;
        }
    }
    
  if (can_error_reenable_cntr[P_L_CAN1] != 0)
    {
      can_error_reenable_cntr[P_L_CAN1]--;
      if (can_error_reenable_cntr[P_L_CAN1] == 0)
        {
          CAN_B.CR.B.ERRMSK = 1;
        }
    }
    
#ifdef P_L_CAN2
  if (can_error_reenable_cntr[P_L_CAN2] != 0)
    {
      can_error_reenable_cntr[P_L_CAN2]--;
      if (can_error_reenable_cntr[P_L_CAN2] == 0)
        {
          CAN_C.CR.B.ERRMSK = 1;
        }
    }
#endif

#ifdef P_L_CAN3
  if (can_error_reenable_cntr[P_L_CAN3] != 0)
    {
      can_error_reenable_cntr[P_L_CAN3]--;
      if (can_error_reenable_cntr[P_L_CAN3] == 0)
        {
          CAN_D.CR.B.ERRMSK = 1;
        }
    }
#endif
}
#endif
/********************************************************************
Function   : hwi_handle_msg_type
Description: This function calls the callback function associated with 
             received message and can port. 

*********************************************************************/
static void hwi_handle_msg_type (uint8_t can,
                                 int16_t can_msg_number,
                                 uint32_t p_l_can_msg_id,
                                 uint8_t *p_l_can_data_ptr,
                                 uint32_t p_l_can_msg_timestamp,
                                 uint8_t  p_l_can_msg_dlc)
{
    if((can_msg_number>P_L_CAN_MSG31)&&(can_msg_number<=P_L_CAN_MSG63))
    {
      J1939_Message_Receive_Callback((uint8_t)can_msg_number, p_l_can_data_ptr, 8);
    }
    /* End of case statement */              
}
/********************************************************************
Function   : hwi_action_can_a_rcvd_callback
Description: This function calls the callback function associated with 
             received message. 

*********************************************************************/
static void hwi_action_can_a_rcvd_callback(int16_t can_msg_number,
                                           uint32_t p_l_can_msg_id,
                                           uint8_t *p_l_can_data_ptr,
                                           uint32_t p_l_can_msg_timestamp,
                                           uint8_t  p_l_can_msg_dlc)
{
	hwi_handle_msg_type(P_L_CAN0,
                        can_msg_number, 
                        p_l_can_msg_id,
                        p_l_can_data_ptr,
                        p_l_can_msg_timestamp,
                        p_l_can_msg_dlc);
}

/********************************************************************
Function   : hwi_transmit_msg_type
Description: This function calls the callback function associated with 
             the message to transmit. 

*********************************************************************/
#if 0
static void hwi_transmit_msg_type (U8 can,
                                   S16 can_msg_number,
                                   U32 p_l_can_msg_id,
                                   U32 p_l_can_msg_timestamp)
{
    switch(can_msg_number)
    {
        case(P_L_CAN_MSG0):
        {
            P_L_CAN_MSG0_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG1):
        {
            P_L_CAN_MSG1_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG2):
        {
            P_L_CAN_MSG2_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG3):
        {
            P_L_CAN_MSG3_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG4):
        {
            P_L_CAN_MSG4_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG5):
        {
            P_L_CAN_MSG5_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG6):
        {
            P_L_CAN_MSG6_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG7):
        {
            P_L_CAN_MSG7_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG8):
        {
            P_L_CAN_MSG8_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG9):
        {
            P_L_CAN_MSG9_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG10):
        {
            P_L_CAN_MSG10_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG11):
        {
            P_L_CAN_MSG11_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG12):
        {
            P_L_CAN_MSG12_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG13):
        {
            P_L_CAN_MSG13_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG14):
        {
            P_L_CAN_MSG14_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG15):
        {
            P_L_CAN_MSG15_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG16):
        {
            P_L_CAN_MSG16_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG17):
        {
            P_L_CAN_MSG17_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG18):
        {
            P_L_CAN_MSG18_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG19):
        {
            P_L_CAN_MSG19_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG20):
        {
            P_L_CAN_MSG20_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG21):
        {
            P_L_CAN_MSG21_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG22):
        {
            P_L_CAN_MSG22_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG23):
        {
            P_L_CAN_MSG23_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG24):
        {
            P_L_CAN_MSG24_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG25):
        {
            P_L_CAN_MSG25_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG26):
        {
            P_L_CAN_MSG26_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG27):
        {
            P_L_CAN_MSG27_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG28):
        {
            P_L_CAN_MSG28_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG29):
        {
            P_L_CAN_MSG29_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG30):
        {
            P_L_CAN_MSG30_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG31):
        {
            P_L_CAN_MSG31_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG32):
        {
            P_L_CAN_MSG32_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG33):
        {
            P_L_CAN_MSG33_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG34):
        {
            P_L_CAN_MSG34_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG35):
        {
            P_L_CAN_MSG35_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG36):
        {
            P_L_CAN_MSG36_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG37):
        {
            P_L_CAN_MSG37_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG38):
        {
            P_L_CAN_MSG38_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG39):
        {
            P_L_CAN_MSG39_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG40):
        {
            P_L_CAN_MSG40_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG41):
        {
            P_L_CAN_MSG41_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG42):
        {
            P_L_CAN_MSG42_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG43):
        {
            P_L_CAN_MSG43_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG44):
        {
            P_L_CAN_MSG44_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG45):
        {
            P_L_CAN_MSG45_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG46):
        {
            P_L_CAN_MSG46_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG47):
        {
            P_L_CAN_MSG47_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG48):
        {
            P_L_CAN_MSG48_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG49):
        {
            P_L_CAN_MSG49_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG50):
        {
            P_L_CAN_MSG50_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG51):
        {
            P_L_CAN_MSG51_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG52):
        {
            P_L_CAN_MSG52_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG53):
        {
            P_L_CAN_MSG53_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG54):
        {
            P_L_CAN_MSG54_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG55):
        {
            P_L_CAN_MSG55_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG56):
        {
            P_L_CAN_MSG56_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG57):
        {
            P_L_CAN_MSG57_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG58):
        {
            P_L_CAN_MSG58_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG59):
        {
            P_L_CAN_MSG59_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG60):
        {
            P_L_CAN_MSG60_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG61):
        {
            P_L_CAN_MSG61_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG62):
        {
            P_L_CAN_MSG62_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
        case(P_L_CAN_MSG63):
        {
            P_L_CAN_MSG63_TRANSMIT_CALLBACK(can,p_l_can_msg_id, p_l_can_msg_timestamp);
            break;
        }
    }
}

#endif
/********************************************************************
Function   : hwi_action_can_a_xmit_callback
Description: This function calls the callback function associated with 
             transmit message. 

*********************************************************************/

static void hwi_action_can_a_xmit_callback(int16_t can_msg_number,
                                           uint32_t p_l_can_msg_id,
                                           uint32_t p_l_can_msg_timestamp)
{
 #if 0
 hwi_transmit_msg_type (P_L_CAN0,
                           can_msg_number,
                           p_l_can_msg_id,
                           p_l_can_msg_timestamp);
    hwi_can_stferror[0].R = 0;
#endif
}


/*-------------------------------------------------------------------*/
/* LEVEL BLOCK                                                       */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* HWI_CAN.C rev.1.1  - 04 Dec 2008 - Yves Clement                   */
/*                                                                   */
/* -Created module from dd06nn_b2 rev1.9                             */
/* -Introduced modification made by DDS Park Royal                   */
/*  .Add compile switch to compile out the Fast Can Gateway          */
/*  .Improve code usage by grouping callback function calls after    */
/*   CAN interrupts                                                  */
/*                                            RSC : YC_4829          */
/*-------------------------------------------------------------------*/
/* HWI_CAN.C rev.1.2  - 10 Jan 2009 - Yves Clement                   */
/*                                                                   */
/* -introduced correction to preserve the correct buffer number when */
/*  performing the CAN interrupt enable/disable in                   */
/*  hwi_can_configure_object()                                       */
/*                               RSC : YC_4829 / PRV36894            */
/*-------------------------------------------------------------------*/
/* HWI_CAN.C rev.1.3  - 15 May 2009 - Yves Clement                   */
/*                                                                   */
/* -Introduced the buffering of the CAN gateway received messages    */
/*  when the Xmit channel is busy while processing the received      */
/*  message.                                                         */
/*                                          RSC : YC_5096            */
/*-------------------------------------------------------------------*/
/* HWI_CAN.C rev.1.4  - 04 Sep 2009 - Yves Clement                   */
/*                                                                   */
/* -Introduced the BYPASS/DEVELOPMENT option on all CAN buses        */
/*                                          RSC : YC_5246: PRV39891  */
/* -Introduced DDS PR modifications 							     */
/*    .hwi_can_re_init_link_ctrl_can()                               */
/*                                               RSC: YC_5261        */
/*-------------------------------------------------------------------*/
/* HWI_CAN.C rev.1.5 - 23 Mar 2010 - Yves Clement                    */
/*                                                                   */
/* -Introduced changes performed by DDS PR:                          */
/*  .Added configuration of MSG_14 in gateway setup function         */
/*  .Removed preprocessor selection of DEV/APP bypass				 */
/*                                 RSC: YC_5553 / PRV00047565        */
/*-------------------------------------------------------------------*/
/*---End of HWI_CAN.C ---*/
/*
* $SOURCE: misc@luxembourg:dd06nn_b3:hwi_can.c $
* $REVISION: 1.4 $
* $AUTHOR: luxembourg:/users/c23yc/dsds/test_dd06nn_b3_wa:c23yc $
*/


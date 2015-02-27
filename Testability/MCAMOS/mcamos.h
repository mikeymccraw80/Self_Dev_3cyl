#ifndef MCAMOS_H
#define MCAMOS_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mcamos.h %
//
// created_by:       lz37cb %
//
// date_created:     Wed Jun 11 09:54:59 2008 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:          %
//
// %version:         3 %
//
//=============================================================================

#include "reuse.h"
#include "dd_flexcan.h"







// CAN id 0x7EE or 0x7EF can be received from tester
// ECM will only send out 0x7EF
#define MCAMOS_CANID_7EE    (0x7EE)
#define MCAMOS_CANID_7EF    (0x7EF)



#define MCAMOS_MESSAGE_RECEIVE_7EE_CONFIGURATION  \
   (               FlexCAN_Set_Index( 0, FLEXCAN_DEVICE_A       ) |\
            FlexCAN_MSGOBJ_Set_Index( 0, FLEXCAN_MSG_OBJ_6      ) |\
        FlexCAN_MSGOBJ_Set_ID_Length( 0, FLEXCAN_MSGOBJ_ID_STD  ) |\
      FlexCAN_MSGOBJ_Set_Data_Length( 0, FLEXCAN_DATA_MAX_BYTES ) |\
              FlexCAN_MSGOBJ_Set_SRR( 0, false                  ) |\
              FlexCAN_MSGOBJ_Set_RTR( 0, false                  ) |\
        FlexCAN_MSGOBJ_Set_Interrupt( 0, true                   ) )

// CAN ID 0x7ef received from tester must assgined to the msg obj before 
// the 0x7ef sent by ECM
#define MCAMOS_MESSAGE_RECEIVE_7EF_CONFIGURATION  \
   (               FlexCAN_Set_Index( 0, FLEXCAN_DEVICE_A       ) |\
            FlexCAN_MSGOBJ_Set_Index( 0, FLEXCAN_MSG_OBJ_7      ) |\
        FlexCAN_MSGOBJ_Set_ID_Length( 0, FLEXCAN_MSGOBJ_ID_STD  ) |\
      FlexCAN_MSGOBJ_Set_Data_Length( 0, FLEXCAN_DATA_MAX_BYTES ) |\
              FlexCAN_MSGOBJ_Set_SRR( 0, false                  ) |\
              FlexCAN_MSGOBJ_Set_RTR( 0, false                  ) |\
        FlexCAN_MSGOBJ_Set_Interrupt( 0, true                   ) )


#define MCAMOS_MESSAGE_TRANSMIT_CONFIGURATION  \
   (               FlexCAN_Set_Index( 0, FLEXCAN_DEVICE_A       ) |\
            FlexCAN_MSGOBJ_Set_Index( 0, FLEXCAN_MSG_OBJ_8      ) |\
        FlexCAN_MSGOBJ_Set_ID_Length( 0, FLEXCAN_MSGOBJ_ID_STD  ) |\
      FlexCAN_MSGOBJ_Set_Data_Length( 0, FLEXCAN_DATA_MAX_BYTES ) |\
              FlexCAN_MSGOBJ_Set_SRR( 0, false                  ) |\
              FlexCAN_MSGOBJ_Set_RTR( 0, false                  ) |\
        FlexCAN_MSGOBJ_Set_Interrupt( 0, false                   ) )




extern bool MCAMOS_enable;


void MCAMOS_Process_7EE_Message(uint8_t *pdata);
void MCAMOS_Process_7EF_Message(uint8_t *pdata);
void MCAMOS_Upload_Data_By_Frame(void);

extern uint16_t MCAMOS_Get_Message_Size(void);





#endif

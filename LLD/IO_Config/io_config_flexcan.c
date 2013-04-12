
//=============================================================================
//Include files
//=============================================================================

#include "io_config_flexcan.h"

//=============================================================================
// Initialization Constants for Module Control Register (MCR)
// Field definitions:
//=============================================================================

//=============================================================================
// MCR - Module Configuration Register
//
//=============================================================================
const FLEXCAN_MCR_T  FLEXCAN_A_MCR_INIT = 
{

      false,   //MDIS:  Module enable, 0=enable
      false,    //FRZ:  Freeze enable, 0=ignore, 1=freeze
      false,   // FEN: FIFO Enable, 0= Not Enabled, 1= Enabled
      true,   //HALT:  Halt S-Clock, 0=normal, 1=debug
      false,   // NOTRDY: Not Ready (read-only)
      false,   //WAK_MSK: Wake Up Interrupt Mask, 0=disabled, 1=enabled
      false,    // SOFTRST: Soft Reset, 0=complete,1=initiate
      false,    //FRZACK: FRZ mode ack. 1 = FRZ mode
      true,   //SUPV:  Supervisor mode, 1=In supervisor mode, 0=In unrestricted mode
      false,    //SLF_WAK: Self Wake Up, 0=disabled, 1=enabled
      false,    //WRNEN: Warning Interrupt Enable,1 = TWRNINT and RWRNINT bits are set, 
                                     //                          0 == TWRNINT and RWRNINT bits not set
      false,    //MDISACK: Low Power Mode acknowledgement 1=FlexCAN2 disabled
      false,    //WAK_SRC: Wakeup Source, 1=Filtered input, 0=Nonfiltered input source
      false,    //DOZE: Doze Mode, 0=Not Enabled, 1=Enabled
      false,    //SRXDIS: Self Reception Disable, 1=Self Rx disabled, 0=Self Rx Enabled
      false,   //MBFEN: Message buffer filter enable, 1=Individual Rx Mask & queue enabled, 0=Disabled
      false,   //LPRIO_EN: Local Priority Enable, 1= Enabled, 0=Disabled
      false,    //AEN: Abort Enable, 0=Abort Disabled,1=Abort Enabled
      false,   //IDAM: ID Acceptance Mode, 00=format-A, 01=format-B,10=format-C,11=format-D
      (FLEXCAN_MSG_OBJ_MAX-1)  // MAXMB Maximum Number of message buffers

}  ;

//=============================================================================
// MCR - Module Configuration Register
//
//=============================================================================
const FLEXCAN_MCR_T  FLEXCAN_C_MCR_INIT = 
{

      false,   //MDIS:  Module enable, 0=enable
      true,    //FRZ:  Freeze enable, 0=ignore, 1=freeze
      false,   // FEN: FIFO Enable, 0= Not Enabled, 1= Enabled
      true,   //HALT:  Halt S-Clock, 0=normal, 1=debug
      true,   // NOTRDY: Not Ready (read-only)
      false,   //WAK_MSK: Wake Up Interrupt Mask, 0=disabled, 1=enabled
      false,    // SOFTRST: Soft Reset, 0=complete,1=initiate
      true,    //FRZACK: FRZ mode ack. 1 = FRZ mode
      true,   //SUPV:  Supervisor mode, 1=In supervisor mode, 0=In unrestricted mode
      false,    //SLF_WAK: Self Wake Up, 0=disabled, 1=enabled
      false,    //WRNEN: Warning Interrupt Enable,1 = TWRNINT and RWRNINT bits are set, 
                                     //                          0 == TWRNINT and RWRNINT bits not set
      false,    //MDISACK: Low Power Mode acknowledgement 1=FlexCAN2 disabled
      false,    //WAK_SRC: Wakeup Source, 1=Filtered input, 0=Nonfiltered input source
      false,    //DOZE: Doze Mode, 0=Not Enabled, 1=Enabled
      false,    //SRXDIS: Self Reception Disable, 1=Self Rx disabled, 0=Self Rx Enabled
      false,   //MBFEN: Message buffer filter enable, 1=Individual Rx Mask & queue enabled, 0=Disabled
      false,   //LPRIO_EN: Local Priority Enable, 1= Enabled, 0=Disabled
      false,    //AEN: Abort Enable, 0=Abort Disabled,1=Abort Enabled
      false,   //IDAM: ID Acceptance Mode, 00=format-A, 01=format-B,10=format-C,11=format-D
      (FLEXCAN_MSG_OBJ_MAX/2 - 1 )  // MAXMB Maximum Number of message buffers

};

//=============================================================================
// Initialization Constants for Control Register (CR)
// Field definitions:
//=============================================================================

const FLEXCAN_CR_T  FLEXCAN_A_CR_INIT =
   {
      FLEXCAN_A_PRESCALER,//PRESDIV  // Prescaler Division Factor
      FlexCAN_A_RJW, //RJW // Resynchronization jump width
      FlexCAN_A_Phase_Segment1, //PSEG1 // Phase Buffer Segment 1
      FlexCAN_A_Phase_Segment2, //PSEG2  // Phase Buffer Segment 2
      true, //BOFFMSK  // Bus Off interrupt mask, 0=dis, 1=en
      false, //ERRMSK // Error interrupt mask, 0=dis, 1=en
      FLEXCAN_OSCILLATOR_CLOCK, //CLKSRC // Engine clock source
      false,  //LPB  // Loop Back, 0=disable, 1=enable
      false, //TWRNMSK // Tx Warning Int Mask, 0=Disable,1=En
      false, //RWRNMSK // Rx Warning Int Mask, 0=Disable,1=En
      FLEXCAN_SAMPLE_MODE_ONE, //SMP // Sampling Mode, 0=1, 1=3 samples
      false, //BOFFREC  // Bus off recovery mode
      false, //TSYN  // Timer Synchronize mode, 0=dis, 1=en
      FLEXCAN_LOWEST_ID_FIRST, //LBUF // Lowest Buffer Transmitted first
      false, //LOM  // Listen only mode
      FlexCAN_A_Prop_Segment //PROPSEG  // Propagation Segment Time
   };

const FLEXCAN_CR_T  FLEXCAN_C_CR_INIT =
   {
      FLEXCAN_C_PRESCALER,//PRESDIV  // Prescaler Division Factor
      FlexCAN_C_RJW, //RJW // Resynchronization jump width
      FlexCAN_C_Phase_Segment1,  //PSEG1 // Phase Buffer Segment 1
      FlexCAN_C_Phase_Segment2, //PSEG2  // Phase Buffer Segment 2
      true, //BOFFMSK  // Bus Off interrupt mask, 0=dis, 1=en
      false, //ERRMSK // Error interrupt mask, 0=dis, 1=en
      FLEXCAN_OSCILLATOR_CLOCK, //CLKSRC // Engine clock source
      false, //LPB  // Loop Back, 0=disable, 1=enable
      false, //TWRNMSK // Tx Warning Int Mask, 0=Disable,1=En
      false, //RWRNMSK// Rx Warning Int Mask, 0=Disable,1=En
      FLEXCAN_SAMPLE_MODE_ONE, //SMP // Sampling Mode, 0=1, 1=3 samples
      false,//BOFFREC  // Bus off recovery mode
      false,//TSYN  // Timer Synchronize mode, 0=dis, 1=en
      FLEXCAN_LOWEST_ID_FIRST,//LBUF // Lowest Buffer Transmitted first
      false,//LOM  // Listen only mode
      FlexCAN_C_Prop_Segment//PROPSEG  // Propagation Segment Time
   };


//=============================================================================
// Initialization Constants for Rx Global Mask Register (RXGMASK)
//=============================================================================
const FLEXCAN_MSK_T  FLEXCAN_A_RXGMASK_INIT =
{
  // FLEXCAN A
   0x7FF, 
   0x3FFFF 
};

const FLEXCAN_MSK_T  FLEXCAN_C_RXGMASK_INIT=
{
 // FLEXCAN C
  0x7FF, 
  0x3FFFF
};
//=============================================================================
// Initialization Constants for Rx 14 Mask Register (RX14MASK)
//=============================================================================
const FLEXCAN_MSK_T  FLEXCAN_A_RX14MASK_INIT =
{
  // FLEXCAN A
   0x7FF, 
   0x3FFFF 
};

const FLEXCAN_MSK_T  FLEXCAN_C_RX14MASK_INIT =
{
  // FLEXCAN C
   0x7FF, 
   0x3FFFF 
};
//=============================================================================
// Initialization Constants for Rx 15 Mask Register (RX15MASK)
//=============================================================================
const FLEXCAN_MSK_T  FLEXCAN_A_RX15MASK_INIT =
{
  // FLEXCAN A
   0x7FF, 
   0x3FFFF 
};

const FLEXCAN_MSK_T  FLEXCAN_C_RX15MASK_INIT =
{
  // FLEXCAN C
   0x7FF, 
   0x3FFFF 
};
//=============================================================================
// Initialization Constants for Individual Rx Mask Registers (RXIMR0-RXIMR63)
//=============================================================================
const FLEXCAN_MSK_T  FLEXCAN_A_RXIMR_INIT [FLEXCAN_MSG_OBJ_MAX]=
{
    // FLEXCAN A
      {0x7FF, 0x3FFFF}, //MB0
      {0x7FF, 0x3FFFF}, //MB1
      {0x7FF, 0x3FFFF}, //MB2
      {0x7FF, 0x3FFFF}, //MB3
      {0x7FF, 0x3FFFF}, //MB4
      {0x7FF, 0x3FFFF}, //MB5
      {0x7FF, 0x3FFFF}, //MB6
      {0x7FF, 0x3FFFF}, //MB7
      {0x7FF, 0x3FFFF}, //MB8
      {0x7FF, 0x3FFFF}, //MB9
      {0x7FF, 0x3FFFF}, //MB10
      {0x7FF, 0x3FFFF}, //MB11
      {0x7FF, 0x3FFFF}, //MB12
      {0x7FF, 0x3FFFF}, //MB13
      {0x7FF, 0x3FFFF}, //MB14
      {0x7FF, 0x3FFFF}, //MB15
      {0x7FF, 0x3FFFF}, //MB16
      {0x7FF, 0x3FFFF}, //MB17
      {0x7FF, 0x3FFFF}, //MB18
      {0x7FF, 0x3FFFF}, //MB19
      {0x7FF, 0x3FFFF}, //MB20
      {0x7FF, 0x3FFFF}, //MB21
      {0x7FF, 0x3FFFF}, //MB22
      {0x7FF, 0x3FFFF}, //MB23
      {0x7FF, 0x3FFFF}, //MB24
      {0x7FF, 0x3FFFF}, //MB25
      {0x7FF, 0x3FFFF}, //MB26
      {0x7FF, 0x3FFFF}, //MB27
      {0x7FF, 0x3FFFF}, //MB28
      {0x7FF, 0x3FFFF}, //MB29
      {0x7FF, 0x3FFFF}, //MB30
      {0x7FF, 0x3FFFF}, //MB31
      {0x7FF, 0x3FFFF}, //MB32
      {0x7FF, 0x3FFFF}, //MB33
      {0x7FF, 0x3FFFF}, //MB34
      {0x7FF, 0x3FFFF}, //MB35
      {0x7FF, 0x3FFFF}, //MB36
      {0x7FF, 0x3FFFF}, //MB37
      {0x7FF, 0x3FFFF}, //MB38
      {0x7FF, 0x3FFFF}, //MB39
      {0x7FF, 0x3FFFF}, //MB40
      {0x7FF, 0x3FFFF}, //MB41
      {0x7FF, 0x3FFFF}, //MB42
      {0x7FF, 0x3FFFF}, //MB43
      {0x7FF, 0x3FFFF}, //MB44
      {0x7FF, 0x3FFFF}, //MB45
      {0x7FF, 0x3FFFF}, //MB46
      {0x7FF, 0x3FFFF}, //MB47
      {0x7FF, 0x3FFFF}, //MB48
      {0x7FF, 0x3FFFF}, //MB49
      {0x7FF, 0x3FFFF}, //MB50
      {0x7FF, 0x3FFFF}, //MB51
      {0x7FF, 0x3FFFF}, //MB52
      {0x7FF, 0x3FFFF}, //MB53
      {0x7FF, 0x3FFFF}, //MB54
      {0x7FF, 0x3FFFF}, //MB55
      {0x7FF, 0x3FFFF}, //MB56
      {0x7FF, 0x3FFFF}, //MB57
      {0x7FF, 0x3FFFF}, //MB58
      {0x7FF, 0x3FFFF}, //MB59
      {0x7FF, 0x3FFFF}, //MB60
      {0x7FF, 0x3FFFF}, //MB61
      {0x7FF, 0x3FFFF}, //MB62
      {0x7FF, 0x3FFFF}  //MB63

};


 const FLEXCAN_MSK_T  FLEXCAN_C_RXIMR_INIT [FLEXCAN_MSG_OBJ_MAX]=
{
    // FLEXCAN C
      {0x7FF, 0x3FFFF}, //MB0
      {0x7FF, 0x3FFFF}, //MB1
      {0x7FF, 0x3FFFF}, //MB2
      {0x7FF, 0x3FFFF}, //MB3
      {0x7FF, 0x3FFFF}, //MB4
      {0x7FF, 0x3FFFF}, //MB5
      {0x7FF, 0x3FFFF}, //MB6
      {0x7FF, 0x3FFFF}, //MB7
      {0x7FF, 0x3FFFF}, //MB8
      {0x7FF, 0x3FFFF}, //MB9
      {0x7FF, 0x3FFFF}, //MB10
      {0x7FF, 0x3FFFF}, //MB11
      {0x7FF, 0x3FFFF}, //MB12
      {0x7FF, 0x3FFFF}, //MB13
      {0x7FF, 0x3FFFF}, //MB14
      {0x7FF, 0x3FFFF}, //MB15
      {0x7FF, 0x3FFFF}, //MB16
      {0x7FF, 0x3FFFF}, //MB17
      {0x7FF, 0x3FFFF}, //MB18
      {0x7FF, 0x3FFFF}, //MB19
      {0x7FF, 0x3FFFF}, //MB20
      {0x7FF, 0x3FFFF}, //MB21
      {0x7FF, 0x3FFFF}, //MB22
      {0x7FF, 0x3FFFF}, //MB23
      {0x7FF, 0x3FFFF}, //MB24
      {0x7FF, 0x3FFFF}, //MB25
      {0x7FF, 0x3FFFF}, //MB26
      {0x7FF, 0x3FFFF}, //MB27
      {0x7FF, 0x3FFFF}, //MB28
      {0x7FF, 0x3FFFF}, //MB29
      {0x7FF, 0x3FFFF}, //MB30
      {0x7FF, 0x3FFFF}, //MB31
      {0, 0}, //MB32
      {0, 0}, //MB33
      {0, 0}, //MB34
      {0, 0}, //MB35
      {0, 0}, //MB36
      {0, 0}, //MB37
      {0, 0}, //MB38
      {0, 0}, //MB39
      {0, 0}, //MB40
      {0, 0}, //MB41
      {0, 0}, //MB42
      {0, 0}, //MB43
      {0, 0}, //MB44
      {0, 0}, //MB45
      {0, 0}, //MB46
      {0, 0}, //MB47
      {0, 0}, //MB48
      {0, 0}, //MB49
      {0, 0}, //MB50
      {0, 0}, //MB51
      {0, 0}, //MB52
      {0, 0}, //MB53
      {0, 0}, //MB54
      {0, 0}, //MB55
      {0, 0}, //MB56
      {0, 0}, //MB57
      {0, 0}, //MB58
      {0, 0}, //MB59
      {0, 0}, //MB60
      {0, 0}, //MB61
      {0, 0}, //MB62
      {0, 0}  //MB63
 
};
//=============================================================================
// Initialization Constants for Interrupt Mask Register for MB32-MB63 (IMRH)
//=============================================================================
const FLEXCAN_IMRH_T  FLEXCAN_A_IMRH_INIT =
{
  // FLEXCAN A
  0
};

const FLEXCAN_IMRH_T  FLEXCAN_C_IMRH_INIT =
{
   // FLEXCAN C
   0
};
//=============================================================================
// Initialization Constants for Interrupt Mask Register for MB0-MB31 (IMRL)
//=============================================================================
const FLEXCAN_IMRL_T  FLEXCAN_A_IMRL_INIT =
{
  // FLEXCAN A
  0
};

const FLEXCAN_IMRL_T  FLEXCAN_C_IMRL_INIT =
{
   // FLEXCAN C
   0
};
//=============================================================================
// Initialization Constants for Interrupt Clear Register for MB32-MB63 (IFRH)
//=============================================================================
const FLEXCAN_IFRH_T  FLEXCAN_A_IFRH_INIT =
{
  // FLEXCAN A
  0 
};

const FLEXCAN_IFRH_T  FLEXCAN_C_IFRH_INIT =
{
    // FLEXCAN C
   0 
};
//=============================================================================
// Initialization Constants for Interrupt Clear Register for MB0-MB31 (IFRL)
//=============================================================================
const FLEXCAN_IFRL_T  FLEXCAN_A_IFRL_INIT =
{
  // FLEXCAN A
  0 
};

const FLEXCAN_IFRL_T  FLEXCAN_C_IFRL_INIT =
{
    // FLEXCAN C
   0 
};


//#define SIU_GPIO_INIT_88 MTSA_CONFIG_FLEXCAN_C_RXD


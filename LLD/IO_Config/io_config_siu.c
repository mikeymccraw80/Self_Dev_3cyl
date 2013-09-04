
#include "io_config_siu.h"
#include "io_config_fmpll.h"



//=============================================================================
// SIU_ECCR_INITIAL
//=============================================================================
//The SIU_ECCR controls the timing relationship between the system clock and the external clock
//CLKOUT. All bits and fields in the SIU_ECCR are read/write and are reset by the IP Green-Line
//asynchronous reset signal.
const SIU_ECCR_T SIU_INITIAL_ECCR =
{
   0,
   SIU_ECCR_EBDF_DIV_BY_2
};

const SIU_SYSDIV_T SIU_INITIAL_SYSDIV = 
{
  //Bypass bit
   SIU_BYPASS_SYS_CLOCK_DIVIDER_INIT,
  //The SYSCLKDIV bits select the divider value for the system clock, that is, the output of the
   //FMPLL. Note that the SYSCLKDIV divider is required in addition to the RFD to allow the other
  //sources for the system clock, i.e., output of the FMPLL, to be divided down to slowest frequencies
  //to improve power. The output of the clock divider is nominally a 50% duty cycle.
   SIU_SYSTEM_CLOCK_DIV_INIT
};

//=============================================================================
// SIU_INITIAL_DISR
//=============================================================================
//The DSPI Input Select Register (SIU_DISR) register specifies the source of each DSPI data input, slave
//select, clock input, and trigger input to allow serial and parallel chaining of the DSPI blocks.
//DSPI_B,DSPI_C
const SIU_DISR_T SIU_INITIAL_DISR = 
{
 //DSPI_B
   SIU_DISR_SINSELX_SINX, 
   SIU_DISR_SSSELX_PCSX0, 
   SIU_DISR_SCKSELX_SCKX,
   SIU_DISR_TRIGSELX_RESERVED_1,
   //DSPI_C
   SIU_DISR_SINSELX_SINX, 
   SIU_DISR_SSSELX_PCSX0, 
   SIU_DISR_SCKSELX_SCKX,
   SIU_DISR_TRIGSELX_RESERVED_1,
};

//=============================================================================
// SIU_INITIAL_ISEL3
//=============================================================================
//The SIU_ISEL3 register selects the source for the external eQADC trigger inputs.
const SIU_ISEL3_T SIU_ISEL3_INITIAL = 
{
   {
      QADC_TRIGGER_SELECT_1_eTRIG0,   //eTSEL5,
      QADC_TRIGGER_SELECT_1_PIT1_TRIGGER,   //eTSEL4,
      QADC_TRIGGER_SELECT_1_eTRIG0,   //eTSEL3,
      QADC_TRIGGER_SELECT_1_eTRIG0,   //eTSEL2,
      QADC_TRIGGER_SELECT_1_eTRIG0,   //eTSEL1,
      QADC_TRIGGER_SELECT_1_PIT0_TRIGGER    //eTSEL0
   }
};

//=============================================================================
// SIU_INITIAL_ETISR
//=============================================================================
//The eQADC Trigger Input Select Register (SIU_ETISR) selects the source for the eQADC trigger inputs.
const SIU_ETISR_T SIU_ETISR_INITIAL = 
{
   {
      QADC_TRIGGER_INPUT_SELECT_5_eTSEL5,   //eTSEL5,
      QADC_TRIGGER_INPUT_SELECT_4_eTSEL4,   //eTSEL4,
      QADC_TRIGGER_INPUT_SELECT_3_eTSEL3,   //eTSEL3,
      QADC_TRIGGER_INPUT_SELECT_2_eTSEL2,   //eTSEL2,
      QADC_TRIGGER_INPUT_SELECT_1_eTSEL1,   //eTSEL1,
      QADC_TRIGGER_INPUT_SELECT_0_eTSEL0    //eTSEL0
   }
};

//=============================================================================
// SIU_INITIAL_ISEL8
//=============================================================================
//The SIU_ISEL 8 register is used to multiplex the ETPU[24:29] inputs. These six eTPU channels can come
//from the output of the DSPI or the corresponding pad.
const SIU_ISEL8_T SIU_INITIAL_ISEL8 = 
{
   SIU_ETPU_CHANNEL,   //eTPU[29] input channel.  ESEL5
   SIU_ETPU_CHANNEL,   //eTPU[28] input channel   ESEL4
   SIU_ETPU_CHANNEL,   //eTPU[27] input channel   ESEL3
   SIU_ETPU_CHANNEL,   //eTPU[26] input channel   ESEL2
   SIU_ETPU_CHANNEL,   //eTPU[25] input channel   ESEL1
   SIU_ETPU_CHANNEL    //eTPU[24] input channel   ESEL0
};


//=============================================================================
// SIU_INITIAL_ISEL9
//=============================================================================
//The eQADC has a new mode of operation called ｡ｮStreaming｡ｯ. This mode requires a second trigger for
//queue0. The source pin for this trigger can come from eTPU, eMIOS or PIT channels. A mux select
//register is required to select the source of this new queue0 trigger.
const SIU_ISEL9_T SIU_INITIAL_ISEL9 = 
{
   SIU_ISEL9_eTSEL0A_eTPUB30
};

//=============================================================================
// SIU_INITIAL_CCR
//=============================================================================

const SIU_CCR_T SIU_INITIAL_CCR =
{
   //The MATCH bit is a read only bit that indicates the result of a 64-bit comparison between the
   //values in the SIU_CBRH and SIU_CBRL registers and the censorship word stored in the shadow
   //block of flash. The match input is asserted if the values are equal.
   //  1 Match input signal is asserted
   // 0 Match input signal is negated
   0,
   //  Disable Nexus
   //The DISNEX bit is a read only bit that holds the value of the Nexus disable input signal to the SIU.
   //When system reset negates, the value in this bit depends on the censorship control word and the
   //boot configuration bits.
   // 1 Nexus disable input signal is asserted
   //  0 Nexus disable input signal is negated
   0,
   //Calibration Reflection Suppression Enable
   //The CRSE bit enables the suppression of reflections from the EBI｡ｯs calibration bus onto the
  // non-calibration bus. The EBI drives some outputs to both the calibration and non-calibration
  //buses. When CRSE is asserted, the values driven onto the calibration bus pins will not be reflected
  //onto the non-calibration bus pins. When CRSE is negated, the values driven onto the calibration
  //bus pins will be reflected onto the non-calibration bus pins.
  //CRSE only enables reflection suppression for non-calibration bus pins which do not have a
  //negated state to which the pins return at the end of the access. CRSE does not enable reflection
  //suppression for the non-calibration bus pins which have a negated state to which the pins return
  //at the end of an access. Those reflections always are suppressed. Furthermore, the suppression
  //of reflections from the non-calibration bus onto the calibration bus is not enabled by CRSE. Those
  //reflections are also always suppressed.
   SIU_CALIB_REFLECTION_SUPRESSION_ENABLE
};



//The SIU_PCR83 register controls the pin function, direction, and static electrical attributes of the
//CAN_A_TX_SCI_A_TX_GPIO[83] pin.
const SIU_PCR_T SIU_INITIAL_PCR_83 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment //CAN_A_TX
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR84 register controls the function, direction, and static electrical attributes of the
//CAN_A_RX_SCI_A_RX_GPIO[84] pin.
const SIU_PCR_T SIU_INITIAL_PCR_84 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment //CAN_A_TX
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR87 register controls the function, direction, and static electrical attributes of the
//CAN_C_TX_GPIO[87] pin. This register allows selection of the CAN_C_TX and GPIO functions.

const SIU_PCR_T SIU_INITIAL_PCR_87 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR88 register controls the function, direction, and static electrical attributes of the
//CAN_C_RX_GPIO[88] pin. This register allows selection of the CAN_C_RX and GPIO functions.

const SIU_PCR_T SIU_INITIAL_PCR_88 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR89 register controls the function, direction, and static electrical attributes of the
//SCI_A_TX_eMIOS[13]_GPIO[89] pin.

const SIU_PCR_T SIU_INITIAL_PCR_89 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR90 register controls the function, direction, and static electrical attributes of the
//SCI_A_RX_eMIOS[15]_GPIO[90] pin.

const SIU_PCR_T SIU_INITIAL_PCR_90 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR91 register controls the function, direction, and static electrical attributes of the
//SCI_B_TX_GPIO[91] pin. This register allows selection of the SCI_TX_B and GPIO functions.

const SIU_PCR_T SIU_INITIAL_PCR_91 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR92 register controls the function, direction, and static electrical attributes of the
//SCI_B_RX_GPIO[92] pin. This register allows selection of the SCI_B_RX and GPIO functions.
const SIU_PCR_T SIU_INITIAL_PCR_92 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};



//The SIU_PCR102 register controls the function, direction, and static electrical attributes of the
//DSPI_B_SCK_DSPI_C_PCS[1]_GPIO[102] pin. This register allows selection of the DSPI_B_SCK,
//DSPI_C_PCS[1] and GPIO functions.
const SIU_PCR_T SIU_INITIAL_PCR_102 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR103 register controls the function, direction, and static electrical attributes of the
//DSPI_B_SIN_DSPI_C_PCS[2]_GPIO[103] pin. This register allows selection of the DSPI_B_SIN,
//DSPI_C_PCS[2] and GPIO functions.
const SIU_PCR_T SIU_INITIAL_PCR_103 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR104 register controls the function, direction, and static electrical attributes of the
//DSPI_B_SOUT_DSPI_C_PCS[5]_GPIO[104] pin. This register allows selection of the DSPI_B_SOUT,
//DSPI_C_PCS[5] and GPIO functions.

const SIU_PCR_T SIU_INITIAL_PCR_104 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR105 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[0]_GPIO[105] pin. This register allows selection of the DSPI_B_PCS[0] and GPIO
//functions.

const SIU_PCR_T SIU_INITIAL_PCR_105 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR106 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[1]_GPIO[106] pin. This register allows selection of the DSPI_B_PCS and GPIO functions.

const SIU_PCR_T SIU_INITIAL_PCR_106 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR107 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[2]_DSPI_C_SOUT_GPIO[107] pin. This register allows selection of the DSPI_B_PCS,
//DSPI_C_SOUT and GPIO functions.
const SIU_PCR_T SIU_INITIAL_PCR_107 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR108 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[3]_DSPI_C_SIN_GPIO[108] pin. This register allows selection of the DSPI_B_PCS,
//DSPI_C_SIN and GPIO functions.

const SIU_PCR_T SIU_INITIAL_PCR_108 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR109 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[4]_DSPI_C_SCK_GPIO[109] pin. This register allows selection of the DSPI_B_PCS,
//DSPI_C_SCK and GPIO functions.

const SIU_PCR_T SIU_INITIAL_PCR_109 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MAXIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR110 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[5]_DSPI_C_PCS[0]_GPIO[110] pin. This register allows selection of the DSPI_B_PCS,
//DSPI_C_PCS[0] and GPIO functions.

const SIU_PCR_T SIU_INITIAL_PCR_110 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MAXIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR114 register controls the function, direction, and static electrical attributes of the
//eTPU_A[0]_eTPU_A[12]_eTPU_A[19]_GPIO[114] pin.

const SIU_PCR_T SIU_INITIAL_PCR_114 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR115 ｨC SIU_PCR118 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[1:4]_eTPU_A[13:16]_GPIO[115:118] pins. Only the output channels of eTPU_A[13:16]
//are connected to pins. Both the input and output channels of eTPU_A[1:4] are connected to pins.

const SIU_PCR_T SIU_INITIAL_PCR_115 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

const SIU_PCR_T SIU_INITIAL_PCR_116 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

const SIU_PCR_T SIU_INITIAL_PCR_117 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

const SIU_PCR_T SIU_INITIAL_PCR_118 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};


//GPIO 119
//O2APUMP
//The SIU_PCR119 register controls the function, direction, and static electrical attributes of the
//eTPU_A[5]_eTPU_A[17]_DSPI_B_SCK_LVDSボ_GPIO[119] pin.
//It is required to program the PA field of both registers, SIU_PCR119 and SIU_PCR120, to select the
//SCK_LVDS alternate function, and then use the register SIU_PCR120 to program the SCK_LVDS
//characteristics (drive strength using the slew rate field).
const SIU_PCR_T SIU_INITIAL_PCR_119 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//GPIO 120
//O2BPUMP
//The SIU_PCR120 register controls the function, direction, and static electrical attributes of the
//eTPU_A[6]_eTPU_A[18]_DSPI_B_SCK_LVDS+_GPIO[120] pin.
const SIU_PCR_T SIU_INITIAL_PCR_120 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//GPIO 121
//BRKSWDI 
//The SIU_PCR120 register controls the function, direction, and static electrical attributes of the
//eTPU_A[7]_eTPU_A[19]_DSPI_B_SOUT_LVDSボ_eTPU_A[6]_GPIO[121] pin.
const SIU_PCR_T SIU_INITIAL_PCR_121= 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//GPIO 122
//DRTRNDI
//The SIU_PCR122 register controls the function, direction, and static electrical attributes of the
//eTPU_A[8]_eTPU_A[20]_DSPI_B_SOUT_LVDS+_GPIO[122] pin.
const SIU_PCR_T SIU_INITIAL_PCR_122 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//GPIO 123
//ETCDIS
//The SIU_PCR123 ｨC SIU_PCR125 registers control the function, direction, and static electrical attributes
//of the eTPU_A[9:11]_eTPU_A[21:23]_GPIO[123:125] pins.
const SIU_PCR_T SIU_INITIAL_PCR_123 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu10
//do not active tempoary
//The SIU_PCR123 ｨC SIU_PCR125 registers control the function, direction, and static electrical attributes
//of the eTPU_A[9:11]_eTPU_A[21:23]_GPIO[123:125] pins.
const SIU_PCR_T SIU_INITIAL_PCR_124 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu11
//do not active tempoary
//The SIU_PCR123 ｨC SIU_PCR125 registers control the function, direction, and static electrical attributes
//of the eTPU_A[9:11]_eTPU_A[21:23]_GPIO[123:125] pins.
const SIU_PCR_T SIU_INITIAL_PCR_125 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu12
//do not active tempoary
//The SIU_PCR126 register controls the function, direction, and static electrical attributes of the
//eTPU_A[12]_DSPI_B_PCS[1]_GPIO[126] pin.
const SIU_PCR_T SIU_INITIAL_PCR_126 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu13
//IMMOREQCTL
//The SIU_PCR127 register controls the function, direction, and static electrical attributes of the
//eTPU_A[13]_DSPI_B_PCS[3]_GPIO[127] pin.
const SIU_PCR_T SIU_INITIAL_PCR_127 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu14
//VGIS2CTL
//The SIU_PCR128 register controls the function, direction, and static electrical attributes of the
//eTPU_A[14]_DSPI_B_PCS[4]_eTPU_A[9]_GPIO[128] pin.
const SIU_PCR_T SIU_INITIAL_PCR_128 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu15
//VGIS1CTL
//The SIU_PCR129 register controls the function, direction, and static electrical attributes of the
//eTPU_A[15]_DSPI_B_PCS[5]_GPIO[129] pin.
const SIU_PCR_T SIU_INITIAL_PCR_129 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};


//etpu16
//CAM2
//The SIU_PCR130 ｨC SIU_PCR133 registers control the function, direction, and static electrical attributes
//of the eTPU_A[16:19]_GPIO[130:133] pins. This registers allow selection of the eTPU_A and GPIO
//functions.
const SIU_PCR_T SIU_INITIAL_PCR_130 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu17
//EST1
//The SIU_PCR130 ｨC SIU_PCR133 registers control the function, direction, and static electrical attributes
//of the eTPU_A[16:19]_GPIO[130:133] pins. This registers allow selection of the eTPU_A and GPIO
//functions.
const SIU_PCR_T SIU_INITIAL_PCR_131 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};


//etpu18
//EST SYNC
//The SIU_PCR130 ｨC SIU_PCR133 registers control the function, direction, and static electrical attributes
//of the eTPU_A[16:19]_GPIO[130:133] pins. This registers allow selection of the eTPU_A and GPIO
//functions.
const SIU_PCR_T SIU_INITIAL_PCR_132 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu19
//INJ1
//The SIU_PCR130 ｨC SIU_PCR133 registers control the function, direction, and static electrical attributes
//of the eTPU_A[16:19]_GPIO[130:133] pins. This registers allow selection of the eTPU_A and GPIO
//functions.
const SIU_PCR_T SIU_INITIAL_PCR_133 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu20
//INJ2
//The SIU_PCR134 ｨC SIU_PCR135 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[20:21]_IRQ[8:9]_GPIO[134:135] pins.
const SIU_PCR_T SIU_INITIAL_PCR_134 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu21
//INJ3
//The SIU_PCR134 ｨC SIU_PCR135 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[20:21]_IRQ[8:9]_GPIO[134:135] pins.
const SIU_PCR_T SIU_INITIAL_PCR_135 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu22
//INJ4
//The SIU_PCR136 register controls the function, direction, and static electrical attributes of the
//eTPU_A[22]_IRQ[10]_eTPU_A[17]_GPIO[136] pin. The eTPU_A[17] is an output only function.
const SIU_PCR_T SIU_INITIAL_PCR_136 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu23
//not active
//The SIU_PCR137 register controls the function, direction, and static electrical attributes of the
//eTPU_A[23]_IRQ[11]_eTPU_A[21]_GPIO[137] pin.
const SIU_PCR_T SIU_INITIAL_PCR_137 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu24
//ELOAD2DI
//The SIU_PCR138 register controls the function, direction, and static electrical attributes of the
//eTPU_A[24]_IRQ[12]_DSPI_C_SCK_LVDSボ_GPIO[138] pin.
const SIU_PCR_T SIU_INITIAL_PCR_138 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};



//etpu25
//ELOAD1DI
//The SIU_PCR139 register controls the function, direction, and static electrical attributes of the
//eTPU_A[25]_IRQ[13]_DSPI_C_SCK_LVDS+_GPIO[139] pin.
const SIU_PCR_T SIU_INITIAL_PCR_139 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu26
//SPFI
//The SIU_PCR140 register controls the function, direction, and static electrical attributes of the
//eTPU_A[26]_IRQ[14]_DSPI_C_SOUT_LVDSボ_GPIO[140] pin.
const SIU_PCR_T SIU_INITIAL_PCR_140 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu27
//VSSFI
//The SIU_PCR141 register controls the function, direction, and static electrical attributes of the
//eTPU_A[27]_IRQ[15]_DSPI_C_SOUT_LVDS+_DSPI_B_SOUT_GPIO[141] pin.
const SIU_PCR_T SIU_INITIAL_PCR_141 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu28
//WSSFI
//The SIU_PCR142 ｨC SIU_PCR143 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[28:29]_DSPI_C_PCS[1:2]_GPIO[142:143] pins. Only the output channel of
//eTPU_A[28:29] is connected to the pin. This register allows selection of the eTPU_A and GPIO functions.
const SIU_PCR_T SIU_INITIAL_PCR_142 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu29
//ENSFI
//The SIU_PCR142 ｨC SIU_PCR143 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[28:29]_DSPI_C_PCS[1:2]_GPIO[142:143] pins. Only the output channel of
//eTPU_A[28:29] is connected to the pin. This register allows selection of the eTPU_A and GPIO functions.
const SIU_PCR_T SIU_INITIAL_PCR_143 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu30
//WINGATE 
//inactive tempoary
//The SIU_PCR144 register controls the function, direction, and static electrical attributes of the
//eTPU_A[30]_DSPI_C_PCS[3]_eTPU_A[11]_GPIO[144] pin. This register allows selection of the
//eTPU_A, DSPI_C_PCS and GPIO functions. The eTPU_A[11] is an output only function.
const SIU_PCR_T SIU_INITIAL_PCR_144 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//etpu31
//not active 
//The SIU_PCR145 register controls the function, direction, and static electrical attributes of the
//eTPU_A[31]_DSPI_C_PCS[4]_eTPU_A[13]_GPIO[145] pin. This register allows selection of the
//eTPU_A, DSPI_C_PCS and GPIO functions. The eTPU_A[13] is an output only function.
const SIU_PCR_T SIU_INITIAL_PCR_145 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//emios0
//VSEPCLK
//The SIU_PCR179 register controls the function, direction, and static electrical attributes of the
//eMIOS[0]_eTPU_A[0]_eTPU_A[25]_GPIO[179] pin. This register allows selection of the eMIOS,
//eTPU_A and GPIO functions. The eTPU_A[25] is an output only function.
const SIU_PCR_T SIU_INITIAL_PCR_179 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MAXIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//emios1
//configured as input 
//The SIU_PCR180 register controls the function, direction, and static electrical attributes of the
//eMIOS[1]_eTPU_A[1]_GPIO[180] pin. This register allows selection of the eTPU_A and GPIO
//functions.
/*const SIU_PCR_T SIU_INITIAL_PCR_180 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};*/

//emios2
//GEN_ENABLE 
//The SIU_PCR181 register controls the function, direction, and static electrical attributes of the
//eMIOS[2]_eTPU_A[2]_GPIO[181] pin. This register allows selection of the eTPU_A and GPIO
//functions.
const SIU_PCR_T SIU_INITIAL_PCR_181 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//emios4
//SOHCLK 
//The SIU_PCR183 register controls the function, direction, and static electrical attributes of the
//eMIOS[4]_eTPU_A[4]_GPIO[183] pin. This register allows selection of the eTPU_A and GPIO
//functions.
const SIU_PCR_T SIU_INITIAL_PCR_183 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//emios8
//ETCCTLPWM 
//The SIU_PCR187 register controls the functions, directions, and static electrical attributes of the
//eMIOS[8]_eTPU_A[8]_SCI_B_TX_GPIO[187] pin. Both the input and output functions of eMIOS[8:9]
//are connected to pins. Only the output channels of eTPU_A[8:9] are connected to pins.
const SIU_PCR_T SIU_INITIAL_PCR_187 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//emios9
//CLTPUMPCTL 
//The SIU_PCR188 register controls the functions, directions, and static electrical attributes of the
//eMIOS[9]_eTPU_A[9]_SCI_B_RX_GPIO[188] pin. Both the input and output functions of eMIOS[8:9]
//are connected to pins. Only the output channels of eTPU_A[8:9] are connected to pins.
const SIU_PCR_T SIU_INITIAL_PCR_188 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//emios10
//CRUISICTL
//The SIU_PCR189 ｨC SIU_PCR190 registers control the pin functions, directions, and static electrical
//attributes of the eMIOS[10:11]_GPIO[189:190] pins. Both the input and output functions of
//eMIOS[10:11] are connected to pins.
const SIU_PCR_T SIU_INITIAL_PCR_189 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//emios11
//FSE_ENABLE
//The SIU_PCR189 ｨC SIU_PCR190 registers control the pin functions, directions, and static electrical
//attributes of the eMIOS[10:11]_GPIO[189:190] pins. Both the input and output functions of
//eMIOS[10:11] are connected to pins.
const SIU_PCR_T SIU_INITIAL_PCR_190 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MEDIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//emios12
//VVT2CTL
//The SIU_PCR191 register controls the function, direction, and static electrical attributes of the
//eMIOS[12]_DSPI_C_SOUT_eTPU_A[27]_GPIO[191] pin. This register allows selection of the eMIOS
//and GPIO functions.
const SIU_PCR_T SIU_INITIAL_PCR_191 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MAXIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};


//emios13
//no pin in 144 package
//The SIU_PCR192 register controls the function, direction, and static electrical attributes of the
//eMIOS[13]_GPIO[192] pin. This register allows selection of the eMIOS and GPIO functions.
/*const SIU_PCR_T SIU_INITIAL_PCR_192 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};*/


//emios14
//VVT1CTL
//The SIU_PCR193 register controls the function, direction, and static electrical attributes of the
//eMIOS[14]_IRQ[0]_eTPU_A[29]_GPIO[193] pin. Only the output functions of eMIOS[14] are
//connected to this pin.
const SIU_PCR_T SIU_INITIAL_PCR_193 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//emios15
//no pin in 144 package
//The SIU_PCR194 register controls the function, direction, and static electrical attributes of the
//eMIOS[15]_IRQ[1]_GPIO[194] pin. This register allows selection of the eMIOS and GPIO functions.
/*const SIU_PCR_T SIU_INITIAL_PCR_194 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};*/

//emios23
//FUELCONCTL
//The SIU_PCR202 register controls the function, direction, and static electrical attributes of the
//eMIOS[23]_GPIO[202] pin. Both the input and output functions of eMIOS[23] are connected to the pin.
//The eTPU_B function is not available on this device.
const SIU_PCR_T SIU_INITIAL_PCR_202 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};




//The SIU_PCR206 ｨC SIU_PCR207 registers control the function, direction, and static electrical attributes
//of the GPIO[206:207] pins.

//The SIU_PCR208 register controls the function, direction, and static electrical attributes of the
//PLLREF_IRQ[4]_ETRIG[2]_GPIO[208] pin.


//The SIU_PCR212 register controls the function, direction, and static electrical attributes of the
//BOOTCFG1_IRQ[3]_ETRIG[3]_GPIO[212] pin.

//The SIU_PCR213 register controls the function, direction, and static electrical attributes of the
//WKPCFG_NMI_DSPI_B_SOUT_GPIO[213] pin.

//The SIU_PCR215 register controls the function, direction, and static electrical attributes of the
//AN[12]_MA[0]_eTPU_A[19]_SDS pin. The AN[12] function is an analog pin on this device. This
//register allows selection of the MA[0] and SDS functions.
const SIU_PCR_T SIU_INITIAL_PCR_215 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_RESERVED_0,  //PA Pin assignment reserve is AD12
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};


//The SIU_PCR216 register controls the function, direction, and static electrical attributes of the
//AN[13]_MA[1]_eTPU_A[21]_SDO pin. The AN[13] function is not available on this device. This register
//allows selection of the MA[1] and SDO functions.

const SIU_PCR_T SIU_INITIAL_PCR_216 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_RESERVED_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR217 register controls the function, direction, and static electrical attributes of the
//AN[14]_MA[2]_eTPU_A[27]_SDI pin. The AN[14] function is an analog pin on this device. This register
//allows selection of the MA[2] and SDI functions.
const SIU_PCR_T SIU_INITIAL_PCR_217 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_RESERVED_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};


//The SIU_PCR218 register controls the function, direction, and static electrical attributes of the
//AN[15]_FCK_eTPU_A[29] pin. The AN[15] function is an analog pin on this device. This register allows
//selection of the FCK function.

const SIU_PCR_T SIU_INITIAL_PCR_218 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_RESERVED_0,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};


//The SIU_PCR219 register controls the drive strength of the MCKO_GPIO[219] pin.
//not active
const SIU_PCR_T SIU_INITIAL_PCR_219 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR220 register controls the drive strength of the MDO[0]_eTPU_A[13]_GPIO[220] pin.
//not active
const SIU_PCR_T SIU_INITIAL_PCR_220 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//not active LCI for GPIO 220
const SIU_PCR_T SIU_INITIAL_PCR_180_LCI = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};



//The SIU_PCR221 register controls the drive strength of the MDO[1]_eTPU_A[19]_GPIO[221] pin.
//not active
const SIU_PCR_T SIU_INITIAL_PCR_221 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//not active LCI for GPIO221
const SIU_PCR_T SIU_INITIAL_PCR_192_LCI = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};



//The SIU_PCR222 register controls the drive strength of the MDO[2]_eTPU_A[21]_GPIO[222] pin.
//VBATT_Det_Reset_DIO
const SIU_PCR_T SIU_INITIAL_PCR_222 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//VBATT_Det_Reset_DIO LCI for GPIO222
const SIU_PCR_T SIU_INITIAL_PCR_194_LCI = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};



//The SIU_PCR223 register controls the drive strength of the MDO[3]_eTPU_A[25]_GPIO[223] pin.
//not active
const SIU_PCR_T SIU_INITIAL_PCR_223 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//not active LCI for GPIO223
const SIU_PCR_T SIU_INITIAL_PCR_80_LCI = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR224 register controls the drive strength of the MSEO[0]_eTPU_A[27]_GPIO[224] pin.
//BRKLMPDI
const SIU_PCR_T SIU_INITIAL_PCR_224 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};


//LCI for GPIO224
const SIU_PCR_T SIU_INITIAL_PCR_81_LCI = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_DISABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_ENABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};


//The SIU_PCR225 register controls the drive strength of the MSEO[1]_eTPU_A[29]_GPIO[225] pin.
//ELOAD1DICTL
const SIU_PCR_T SIU_INITIAL_PCR_225 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//LCI for GPIO225
const SIU_PCR_T SIU_INITIAL_PCR_82_LCI = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR227 register controls the drive strength of the EVTO_eTPU_A[4]_GPIO[227] pin.
//ELOAD2DICTL
const SIU_PCR_T SIU_INITIAL_PCR_227 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//LCI for GPIO227
const SIU_PCR_T SIU_INITIAL_PCR_99_LCI = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};
//The SIU_PCR228 register controls the drive strength of the TDO_eMIOS[6]_GPIO[228] pin.

//The SIU_PCR229 register controls the enabling/disabling and drive strength of the CLKOUT pin. The
//CLKOUT pin is enabled and disabled by setting and clearing the OBE bit. The CLKOUT pin is enabled
//during reset.

//The SIU_PCR230 register controls the slew rate of the RSTOUT pin.

//The SIU_PCR231 register controls the function and drive strength of the EVTI_eTPU_A[2]_GPIO[231]
//pin.
//BRKLMPDICTL
const SIU_PCR_T SIU_INITIAL_PCR_231 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//LCI for GPIO98
const SIU_PCR_T SIU_INITIAL_PCR_98_LCI = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      SIU_GPIO_BUFFER_OUT_ENABLED, //OBE  Output buffer enable
      SIU_GPIO_BUFFER_IN_DISABLED,   //IBE    Input buffer enable
      SIU_GPIO_DRIVE_STRENGTH_10pF, //DSC  Drive strength control
      SIU_GPIO_OPEN_DRAIN_DISABLED, //ODE  Open drain output enable
      SIU_GPIO_INPUT_HYSTERESIS_DISABLED, //HYS Input hysteresis
      SIU_GPIO_SLEW_RATE_MINIMUM,  //SRC  Slew rate control
      SIU_GPIO_PULL_UP_Down_DISABLED,  //WPE  Weak pullup/down enable
      SIU_GPIO_PULL_DOWN  //WPS  Weak pullup/down select
};

//The SIU_PCR232 register controls the drive strength of the TDI_eMIOS[5]_GPIO[232] pin.

//The SIU_PCR336 register controls the drive strength of the CAL_CS[0] pin.

// The SIU_PCR338 ｨC SIU_PCR339 registers control the functions and drive strength of the
//CAL_CS[2:3]_CAL_ADDR[10:11] pins.


//The SIU_PCR340 register controls the drive strength of the CAL_ADDR[12:15] pins. Multiple pins are
//controlled by this PCR.

//The SIU_PCR341 register controls the drive strength of the CAL_DATA[0:15] pins. Multiple pins are
//controlled by this PCR.

//The SIU_PCR342 register controls the drive strength of the CAL_RD_WR, CAL_WE[0:1] and CAL_OE
//pins. Multiple pins are controlled by this one PCR. The WEBS bit in the EBI Base Register selects between
//the write enable and byte enable functions.


//The SIU_PCR343 register controls the drive strength of the CAL_TS_ALE pin.

//The SIU_PCR344 register controls the drive strength of the ALT_MCKO and ALT_EVTO pins. Multiple
//pins are controlled by this PCR.


//The SIU_PCR345 register controls the drive strength of the CAL_ADDR[16:27]_ALT_MDO[0:11],
//CAL_ADDR[28:29]_CAL_MSEO[0:1] and CAL_ADDR[30]_ALT_EVTI pins. Multiple pins are
//controlled by this PCR.


//The SIU_PCR350 ｨC SIU_PCR381 registers control the muxing of the signals to the DSPI. PA field values
//are shown in Table 138.

//The SIU_PCR382 ｨC SIU_PCR389 registers control the muxing of the signals to the DSPI. PA field values
//are shown in Table 139.


// configure for DSPI DSI mode
//=============================================================================
// SIU_GPIO_382 - EMIOS12
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_382 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};

//=============================================================================
// SIU_GPIO_383 - ETPU13
//=============================================================================

const SIU_PCR_T SIU_INITIAL_PCR_383 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};


//=============================================================================
// SIU_GPIO_384 - EMIOS14
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_384 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};


//=============================================================================
// SIU_GPIO_385 - EMIOS15
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_385 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};
//=============================================================================
// SIU_GPIO_386 - EMIOS23
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_386 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};

//=============================================================================
// SIU_GPIO_387 - EMIOS00
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_387 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};

//=============================================================================
// SIU_GPIO_388 - ETPU02
//=============================================================================

const SIU_PCR_T SIU_INITIAL_PCR_388 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};

//=============================================================================
// SIU_GPIO_389 - ETPU03
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_389 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};


//=============================================================================
// SIU_GPIO_390 - ETPU04
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_390 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};

//=============================================================================
// SIU_GPIO_391 - GPIO
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_391 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};

//=============================================================================
// SIU_GPIO_392 - GPIO
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_392 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};


//=============================================================================
// SIU_GPIO_393 - GPIO
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_393 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};


//=============================================================================
// SIU_GPIO_394 - GPIO
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_394 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};


//=============================================================================
// SIU_GPIO_395 - GPIO
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_395 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};


//=============================================================================
// SIU_GPIO_396 - EMIOS10
//=============================================================================

const SIU_PCR_T SIU_INITIAL_PCR_396 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};

//=============================================================================
// SIU_GPIO_397 - GPIO
//=============================================================================
const SIU_PCR_T SIU_INITIAL_PCR_397 = 
{
      SIU_GPIO_PIN_ASSIGNMENT_GPIO,  //PA Pin assignment 
      0, //OBE  Output buffer enable
      0,   //IBE    Input buffer enable
      0, //DSC  Drive strength control
      0, //ODE  Open drain output enable
      0, //HYS Input hysteresis
      0,  //SRC  Slew rate control
      0,  //WPE  Weak pullup/down enable
      0  //WPS  Weak pullup/down select
};


//The SIU_PCR390 ｨC SIU_PCR413 registers control the muxing of the signals to the DSPI. PA field values
//are shown in Table 140.



